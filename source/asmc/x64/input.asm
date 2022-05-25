; INPUT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; processing file/macro input data.
;

include asmc.inc
include memalloc.inc
include parser.inc
include macro.inc
include input.inc
include lqueue.inc
include tokenize.inc

public FileCur
public LineCur

public token_stringbuf
public commentbuffer

externdef strFILE:sbyte

DETECTCTRLZ equ 1 ;; 1=Ctrl-Z in input stream will skip rest of the file

;; FILESEQ: if 1, stores a linked list of source files, ordered
;; by usage. Masm stores such a list in the COFF symbol table
;; when -Zd/-Zi is set. It isn't necessary, however, and JWasm's
;; COFF code currently will ignore the list.

FILESEQ     equ 0

.data

commentbuffer string_t 0
FileCur     asym_t 0 ;; @FileCur symbol, created in SymInit()
LineCur     asym_t 0 ;; @Line symbol, created in SymInit()

SIT_FILE    equ 0
SIT_MACRO   equ 1


;; item on src stack ( contains currently open source files & macros )
source_t    typedef ptr src_item
minstance_t typedef ptr macro_instance
src_item    struct
next        source_t ?
type        dw ?        ;; item type ( see enum src_item_type )
srcfile     dw ?        ;; index of file in ModuleInfo.g.FNames
union
 content    ptr_t ?     ;; generic
 file       LPFILE ?    ;; if item is a file
 mi         minstance_t ? ;; if item is a macro
ends
line_num    dd ?        ;; current line
src_item    ends

SrcFree     source_t 0
if FILESEQ
FileSeq     qdesc <>
endif

; buffer for source lines
; since the lines are sometimes concatenated
; the buffer must be a multiple of MAX_LINE_LEN

srclinebuffer string_t 0

; string buffer - token strings and other stuff are stored here.
; must be a multiple of MAX_LINE_LEN since it is used for string expansion.

token_stringbuf string_t 0 ;; start token string buffer


ifdef __UNIX__
INC_PATH_DELIM      equ <':'>
INC_PATH_DELIM_STR  equ <":">
DIR_SEPARATOR       equ <'/'>
filecmp             equ <tstrcmp>
ISPC macro x
    exitm<(x == '/')>
    endm
ISABS proto watcall x:ptr {
    cmp  byte ptr [rax],'/'
    mov  eax,0
    setz al
    }
else
INC_PATH_DELIM      equ <';'>
INC_PATH_DELIM_STR  equ <";">
DIR_SEPARATOR       equ <'\'>
filecmp             equ <tstricmp>
ISPC macro x
    exitm<(x == '/' || x == '\' || x == ':')>
    endm
ISABS proto watcall x:ptr {
    mov cl,[rax+2]
    mov eax,[rax]
    .if ( al == '/' || al == '\' || ( al &&  ah == ':' && ( cl == '/' || cl == '\' ) ) )
        mov eax,1
    .else
        xor eax,eax
    .endif
    }
endif

    .code

; v2.12: function added - _splitpath()/_makepath() removed

GetFNamePart proc __ccall fname:string_t

    .for ( rax = rcx : byte ptr [rcx] : rcx++ )
        .if ISPC( byte ptr [rcx] )
            lea rax,[rcx+1]
        .endif
    .endf
    ret

GetFNamePart endp

; fixme: if the dot is at pos 0 of filename, ignore it

GetExtPart proc __ccall fname:string_t

    .for( eax = NULL : byte ptr [rcx] : rcx++ )
        .if byte ptr [rcx] == '.'
            mov rax,rcx
        .elseif ISPC( byte ptr [rcx] )
            xor eax,eax
        .endif
    .endf
    test  rax,rax
    cmovz rax,rcx
    ret

GetExtPart endp

; check if a file is in the array of known files.
; if no, store the file at the array's end.
; returns array index.
; used for the main source and all INCLUDEd files.
; the array is stored in the standard C heap!
; the filenames are stored in the "local" heap.

AddFile proc __ccall private uses rsi rbx name:string_t

    mov rsi,ModuleInfo.FNames
    .for ( ebx = 0 : ebx < ModuleInfo.cnt_fnames : ebx++ )
        .if ( filecmp( name, [rsi+rbx*string_t] ) == 0 )
            .return( ebx )
        .endif
    .endf

    .if ( !( ebx & 64-1 ) )

        mov ModuleInfo.FNames,MemAlloc( &[rbx*string_t+64*string_t] )
        .if ( rsi != NULL )
            tmemcpy( rax, rsi, &[rbx*string_t] )
            MemFree( rsi )
        .endif
    .endif

    inc ModuleInfo.cnt_fnames
    mov rsi,ModuleInfo.FNames
    mov [rsi+rbx*string_t],LclDup( name )
   .return( ebx )

AddFile endp

GetFName proc __ccall index:uint_t

    mov rax,ModuleInfo.FNames
    mov rax,[rax+rcx*8]
    ret

GetFName endp

; free the file array.
; this is done once for each module after the last pass.

FreeFiles proc __ccall private

    ; v2.03: set src_stack=NULL to ensure that GetCurrSrcPos()
    ; won't find something when called from main().

    mov ModuleInfo.src_stack,NULL
    .if ModuleInfo.FNames
        MemFree(ModuleInfo.FNames)
        mov ModuleInfo.FNames,NULL
    .endif
    ret

FreeFiles endp

; clear input source stack (include files and open macros).
; This is done after each pass.
; Usually the stack is empty when the END directive occurs,
; but it isn't required that the END directive is located in
; the main source file. Also, an END directive might be
; simulated if a "too many errors" condition occurs.

    assume r12:ptr src_item

ifdef __UNIX__
ClearSrcStack proc __ccall uses rsi rdi r12 r13
else
ClearSrcStack proc __ccall uses r12 r13
endif

    DeleteLineQueue()

    ; dont close the last item (which is the main src file)

    mov r12,ModuleInfo.src_stack
    .for( : [r12].next : r12 = r13 )
        mov r13,[r12].next
        .if [r12].type == SIT_FILE
            fclose([r12].file)
        .endif
        mov [r12].next,SrcFree
        mov SrcFree,r12
    .endf
    mov ModuleInfo.src_stack,r12
    ret

ClearSrcStack endp

    assume r12:nothing

UpdateFileCur proc __ccall path:string_t

    mov rdx,FileCur
    mov [rdx].asym.string_ptr,rcx

    lea rdx,strFILE
    mov byte ptr [rdx],'"'
    inc rdx
    .while ( byte ptr [rcx] )
        mov al,[rcx]
        mov [rdx],al
        inc rcx
        inc rdx
        .if ( al == '\' )
            mov [rdx],al
            inc rdx
        .endif
    .endw
    mov word ptr [rdx],'"'
    ret

UpdateFileCur endp

; get/set value of predefined symbol @Line

UpdateLineNumber proc __ccall sym:asym_t, p:ptr

    .for ( rax = ModuleInfo.src_stack: rax : rax = [rax].src_item.next )
        .if [rax].src_item.type == SIT_FILE
            mov [rcx].asym.value,[rax].src_item.line_num
           .break
        .endif
    .endf
    ret

UpdateLineNumber endp

GetLineNumber proc __ccall

    UpdateLineNumber(LineCur, NULL)
    mov rax,LineCur
    mov eax,[rax].asym.uvalue
    ret

GetLineNumber endp

; read one line from current source file.
; returns NULL if EOF has been detected and no char stored in buffer
; v2.08: 00 in the stream no longer causes an exit. Hence if the
; char occurs in the comment part, everything is ok.

LF equ 10
CR equ 13

ifdef __UNIX__
my_fgetc proc __ccall uses rsi rdi fp:ptr FILE
    fgetc(rcx)
    ret
my_fgetc endp
else
my_fgetc equ <fgetc>
endif

my_fgets proc __ccall private uses rsi rdi rbx r12 buffer:string_t, max:int_t, fp:LPFILE

    UNREFERENCED_PARAMETER(buffer)
    UNREFERENCED_PARAMETER(max)
    UNREFERENCED_PARAMETER(fp)

    mov rdi,rcx
    mov r12,rcx
    lea rsi,[rcx+rdx]
    mov rbx,r8

    my_fgetc(rbx)
    .while rdi < rsi
        .switch eax
        .case CR
            .endc ; don't store CR
        .case LF
            mov [rdi],ah
            .return( r12 )
if DETECTCTRLZ
        .case 0x1a

            ; since source files are opened in binary mode, ctrl-z
            ; handling must be done here.
            ;
            ; no break
endif
        .case -1
            xor eax,eax
            mov [rdi],al
            cmp rdi,r12
            cmova rax,r12
           .return
        .default
            stosb
        .endsw
        my_fgetc(rbx)
    .endw
    asmerr(2039)
    mov byte ptr [rdi-1],0
   .return( r12 )
my_fgets endp

if FILESEQ

AddFileSeq proc __ccall file:uint_t

    LclAlloc( ecx )

    mov [rax].file_seq.next,NULL
    mov ecx,file
    mov [rax].file_seq.file,ecx
    .if FileSeq.head == NULL
        mov FileSeq.head,rax
        mov FileSeq.tail,rax
    .else
        mov rcx,FileSeq.tail
        mov [rcx].file_seq.next,rax
        mov FileSeq.tail,rax
    .endif
    ret

AddFileSeq endp

endif

; push a new item onto the source stack.
; type: SIT_FILE or SIT_MACRO

PushSrcItem proc __ccall private type:char_t, pv:ptr

    .if ( SrcFree )

        mov rax,SrcFree
        mov rcx,[rax].src_item.next
        mov SrcFree,rcx
    .else
        LclAlloc( src_item )
    .endif

    mov rcx,ModuleInfo.src_stack
    mov [rax].src_item.next,rcx
    mov ModuleInfo.src_stack,rax
    movzx ecx,type
    mov [rax].src_item.type,cx
    mov rcx,pv
    mov [rax].src_item.content,rcx
    mov [rax].src_item.line_num,0
    ret

PushSrcItem endp

; push a macro onto the source stack.

PushMacro proc __ccall mi:ptr macro_instance

    PushSrcItem( SIT_MACRO, rcx )
    ret

PushMacro endp

get_curr_srcfile proc __ccall

    .for ( rax = ModuleInfo.src_stack: rax : rax = [rax].src_item.next )
        .if [rax].src_item.type == SIT_FILE
            movzx eax,[rax].src_item.srcfile
            .return
        .endif
    .endf
    mov eax,ModuleInfo.srcfile
    ret

get_curr_srcfile endp

set_curr_srcfile proc __ccall file:uint_t, line_num:uint_t

    mov r8,ModuleInfo.src_stack
    mov [r8].src_item.srcfile,cx
    mov [r8].src_item.line_num,edx
    ret

set_curr_srcfile endp

SetLineNumber proc __ccall line:uint_t

    mov rdx,ModuleInfo.src_stack
    mov [rdx].src_item.line_num,ecx
    ret

SetLineNumber endp

; for error listing, render the current source file and line
; this function is also called if pass is > 1,
; which is a problem for FASTPASS because the file stack is empty.

    assume rcx:ptr src_item

GetCurrSrcPos proc __ccall private buffer:string_t

    .for ( rcx = ModuleInfo.src_stack: rcx : rcx = [rcx].next )

        .if [rcx].type == SIT_FILE

            movzx eax,[rcx].srcfile
            mov rax,ModuleInfo.FNames
            mov rax,[rdx+rax*8]

            .if ModuleInfo.EndDirFound == FALSE
                lea rdx,@CStr("%s(%u) : ")
            .else
                lea rdx,@CStr("%s : ")
            .endif
            .return tsprintf(buffer, rdx, rax, [rcx].line_num)
        .endif
    .endf
    xor eax,eax
    mov rcx,buffer
    mov [rcx],al
    ret

GetCurrSrcPos endp

    assume rcx:nothing

; for error listing, render the source nesting structure.
; the structure consists of include files and macros.

    assume rbx:ptr src_item

print_source_nesting_structure proc __ccall uses rsi rdi rbx

    mov rbx,ModuleInfo.src_stack

    ; in main source file?
    .return .if rbx == NULL || [rbx].next == NULL

    .for ( edi = 1 : [rbx].next : rbx = [rbx].next, edi++ )

        .if [rbx].type == SIT_FILE

            mov r9,GetFName([rbx].srcfile)
            PrintNote( NOTE_INCLUDED_BY, edi, "", r9, [rbx].line_num )

        .else

            mov rax,[rbx].mi
            mov rcx,[rax].macro_instance._macro
            mov rax,[rcx].asym.name

            .if byte ptr [rax] == 0

                mov edx,[rcx].asym.value
                inc edx
                PrintNote( NOTE_ITERATION_MACRO_CALLED_FROM, edi, "",
                    "MacroLoop", [rbx].line_num, edx )
            .else
                .new name:ptr = rax
                mov rdx,[rcx].dsym.macroinfo
                mov eax,[rdx].macro_info.srcfile
                GetFNamePart(GetFName(eax))
                PrintNote(NOTE_MACRO_CALLED_FROM, edi, "", name, [rbx].line_num, rax)
            .endif
        .endif
    .endf
    mov r9,GetFName([rbx].srcfile)
    PrintNote(NOTE_MAIN_LINE_CODE, edi, "", r9, [rbx].line_num)
    ret

print_source_nesting_structure endp

    assume rbx:nothing

; Scan the include path for a file!
; variable ModuleInfo.g.IncludePath also contains directories set with -I cmdline option.

open_file_in_include_path proc __ccall private uses rsi rdi rbx r12 r13 r14 r15 name:string_t, fullpath:string_t

    UNREFERENCED_PARAMETER(name)
    UNREFERENCED_PARAMETER(fullpath)

    mov r12,rdx ; fullpath
    mov r13,tstrstart( rcx )
    mov r14,tstrlen( rax )

    .for ( eax = 0, rbx = ModuleInfo.IncludePath : rbx && rax == NULL : rbx = r15 )

        mov   ecx,-1
        mov   rdi,rbx
        repnz scasb
        not   ecx
        dec   ecx
        mov   edx,ecx ; len
        mov   r15,rax ; next

        .ifnz
            mov rdi,rbx
            mov al,INC_PATH_DELIM
            repnz scasb
            .ifz
                mov r15,rdi ; skip path delimiter char (; or :)
                sub rdi,rbx
                lea edx,[rdi-1]
            .endif
        .endif

        ; v2.06: ignore
        ; - "empty" entries in PATH
        ; - entries which would cause a buffer overflow

        xor eax,eax
        mov ecx,edx
        lea edx,[r14+rcx]
        .continue .if ( ecx == 0 || ( edx >= FILENAME_MAX ) )

        mov rsi,rbx
        mov rdi,r12
        rep movsb
        mov al,[rdi-1]

        .if ( !ISPC( al ) )

            mov byte ptr [rdi],DIR_SEPARATOR
            inc rdi
        .endif
        lea ecx,[r14+1]
        mov rsi,r13
        rep movsb
        fopen( r12, "rb" )
    .endf
    ret

open_file_in_include_path endp

; the worker behind the INCLUDE directive. Also used
; by INCBIN and the -Fi cmdline option.
; the main source file is added in InputInit().
; v2.12: _splitpath()/_makepath() removed

    assume rbx:ptr src_item

SearchFile proc __ccall uses rsi rdi rbx r12 r13 r14 r15 path:string_t, queue:int_t

  local fullpath[FILENAME_MAX]:char_t

    UNREFERENCED_PARAMETER(path)

    xor r12,r12 ; file
    mov r13,rcx ; path
    lea r14,fullpath

    ; if no absolute path is given, then search in the directory
    ; of the current source file first!
    ; v2.11: various changes because field fullpath has been removed.

    mov r15d,ISABS(r13)

    .if ( !eax )

        .for ( rbx = ModuleInfo.src_stack: rbx : rbx = [rbx].next )

            .if ( [rbx].type == SIT_FILE )

                mov rsi,GetFName( [rbx].srcfile )

                .if ( rsi != GetFNamePart( rsi ) )

                    sub rax,rsi

                    ; v2.10: if there's a directory part, add it to the directory part of the current file.
                    ; fixme: check that both parts won't exceed FILENAME_MAX!
                    ; fixme: 'path' is relative, but it may contain a drive letter!

                    mov rdi,r14
                    mov ecx,eax
                    rep movsb
                    mov rsi,r13
                    .repeat
                        lodsb
                        stosb
                    .until !al
                    mov r12,fopen( r14, "rb" )
                    .if rax
                        mov r13,r14
                    .endif
                .endif
                .break
            .endif
        .endf
    .endif

    .if ( r12 == NULL )

        mov fullpath,0
        mov r12,fopen( r13, "rb" )

        ; if the file isn't found yet and include paths have been set,
        ; and NO absolute path is given, then search include dirs

        .if ( r12 == NULL && ModuleInfo.IncludePath != NULL && !r15d )
            .if ( open_file_in_include_path( r13, r14 ) )

                mov r12,rax
                mov r13,r14
            .endif
        .endif
        .if ( r12 == NULL )
            asmerr( 1000, r13 )
        .endif
    .endif

    ; is the file to be added to the file stack?
    ; assembly files usually are, but binary files ( INCBIN ) aren't.

    .if ( queue )

        mov rbx,PushSrcItem( SIT_FILE, r12 )
        AddFile( r13 )
        mov [rbx].srcfile,ax
        UpdateFileCur(GetFName( eax ))
if FILESEQ
        .if ( Options.line_numbers && Parse_Pass == PASS_1 )
            AddFileSeq( [rbx].srcfile )
        .endif
endif
    .endif
    .return( r12 )

SearchFile endp

; get the next source line from file or macro.
; v2.11: line queues are no longer read here,
; this is now done in RunLineQueue().
; Also, if EOF/EOM is reached, the function will
; now return NULL in any case.

GetTextLine proc __ccall uses rsi rdi rbx buffer:string_t

    mov rbx,ModuleInfo.src_stack

    .if ( [rbx].type == SIT_FILE )

        .if my_fgets(rcx, ModuleInfo.max_line_len, [rbx].file)

            inc [rbx].line_num
           .return buffer
        .endif

        ; don't close and remove main source file

        .if ( [rbx].next )

            fclose([rbx].file)

            mov ModuleInfo.src_stack,[rbx].next
            mov [rbx].next,SrcFree
            mov SrcFree,rbx
        .endif

        ; update value of @FileCur variable

        .for ( rbx = ModuleInfo.src_stack: [rbx].type != SIT_FILE: rbx = [rbx].next )

            UpdateFileCur(GetFName([rbx].srcfile))
        .endf
if FILESEQ
        .if Options.line_numbers && Parse_Pass == PASS_1
            AddFileSeq([rbx].srcfile)
        .endif
endif

    .else

        assume rdi:ptr macro_instance

        mov rdi,[rbx].mi
        .if [rdi].currline
            mov rcx,[rdi].currline
            mov rax,[rcx].srcline.next
        .else
            mov rax,[rdi].startline
        .endif
        mov [rdi].currline,rax

        .if rax

            ; if line contains placeholders, replace them by current values

            .if [rax].srcline.ph_count
                lea rdx,[rax].srcline.line
                fill_placeholders(buffer, rdx, [rdi].parmcnt,
                                  [rdi].localstart, [rdi].parm_array )
            .else
                tstrcpy(buffer, &[rax].srcline.line)
            .endif
            inc [rbx].line_num
            .return buffer
        .endif
        mov ModuleInfo.src_stack,[rbx].next
        mov [rbx].next,SrcFree
        mov SrcFree,rbx
    .endif
    .return( NULL ) ; end of file or macro reached

GetTextLine endp

; add a string to the include path.
; called for -I cmdline options.
; the include path is rebuilt for each assembled module.
; it is stored in the standard C heap.

AddStringToIncludePath proc __ccall uses rsi rdi rbx string:string_t

    mov rsi,tstrstart(rcx)
    .if ( tstrlen( rsi ) )

        .if ( ModuleInfo.IncludePath == NULL )

            mov ModuleInfo.IncludePath,MemDup( rsi )

        .else

            mov edi,eax
            mov rbx,ModuleInfo.IncludePath
            tstrlen( rbx )
            mov ModuleInfo.IncludePath,MemAlloc( &[rax + rdi + 2] )
            tstrcat( tstrcat( tstrcpy( rax, rbx ), INC_PATH_DELIM_STR ), rsi )
            MemFree( rbx )
        .endif
    .endif
    ret

AddStringToIncludePath endp

; input buffers
; 1. src line stack ( default I86: 2*600  = 1200 )
; 2. tokenarray     ( default I86: 150*12 = 1800 )
; 3. string buffer  ( default I86: 2*600  = 1200 )

SIZE_SRCLINES     equ ( MAX_LINE_LEN * ( MAX_MACRO_NESTING + 1 ) )
SIZE_TOKENARRAY   equ ( asm_tok * MAX_TOKEN * MAX_MACRO_NESTING )
SIZE_STRINGBUFFER equ ( MAX_LINE_LEN * MAX_MACRO_NESTING )

; PushInputStatus() is used whenever a macro or generated code is to be "executed".
; after the macro/code has been assembled, PopInputStatus() is required to restore
; the saved status.
; the status information that is saved includes
; - the source line ( including the comment )
; - the token buffer
; - the string buffer (used to store token strings)
; - field Token_Count
; - field line_flags

    assume rsi:ptr input_status

PushInputStatus proc __ccall uses rsi oldstat:ptr input_status

    mov rsi,rcx

    mov [rsi].token_stringbuf,token_stringbuf
    mov [rsi].token_count,Token_Count
    mov [rsi].currsource,CurrSource

    ; if there's a comment, attach it to current source

    .if ModuleInfo.CurrComment
        tstrlen(CurrSource)
        add rax,CurrSource
        mov [rsi].CurrComment,rax
        tstrcpy(rax, ModuleInfo.CurrComment)
    .else
        mov [rsi].CurrComment,NULL
    .endif
    mov [rsi].line_flags,ModuleInfo.line_flags ;; v2.08
    mov token_stringbuf,ModuleInfo.stringbufferend
    mov eax,Token_Count
    inc eax
    imul eax,eax,asm_tok
    add ModuleInfo.tokenarray,rax
    tstrlen(CurrSource)
    mov CurrSource,GetAlignedPointer(CurrSource, eax)
   .return( ModuleInfo.tokenarray )

PushInputStatus endp

PopInputStatus proc __ccall uses rsi newstat:ptr input_status

    mov rsi,rcx
    mov ModuleInfo.stringbufferend,token_stringbuf
    mov token_stringbuf,[rsi].token_stringbuf
    mov Token_Count,[rsi].token_count
    mov CurrSource,[rsi].currsource
    .if [rsi].CurrComment
        mov ModuleInfo.CurrComment,commentbuffer
        tstrcpy(rax, [rsi].CurrComment)
        mov rax,[rsi].CurrComment
        mov byte ptr [rax],0
    .else
        mov ModuleInfo.CurrComment,NULL
    .endif
    mov eax,Token_Count
    inc eax
    imul eax,eax,asm_tok
    sub ModuleInfo.tokenarray,rax
    mov ModuleInfo.line_flags,[rsi].line_flags ;; v2.08
    ret

PopInputStatus endp

AllocInput proc __ccall private uses rsi rdi

    mov  eax,ModuleInfo.max_line_len
    imul esi,eax,MAX_MACRO_NESTING + 1  ; SIZE_SRCLINES
    imul edx,eax,MAX_MACRO_NESTING      ; SIZE_STRINGBUFFER
    shr  eax,2                          ; SIZE_TOKENARRAY
    imul edi,eax,asm_tok * MAX_MACRO_NESTING
    lea  eax,[rdi+rdx]
    add  eax,esi
    mov  srclinebuffer,LclAlloc( eax )

    ; the comment buffer is at the end of the source line buffer

    lea rcx,[rax+rsi]
    mov edx,ModuleInfo.max_line_len
    sub rcx,rdx
    mov commentbuffer,rcx

    ; behind the comment buffer is the token buffer

    lea rcx,[rax+rsi]
    mov ModuleInfo.tokenarray,rcx
    lea rax,[rcx+rdi]
    mov rcx,token_stringbuf
    mov token_stringbuf,rax
    sub ModuleInfo.stringbufferend,rcx
    add ModuleInfo.stringbufferend,rax
    ret

AllocInput endp

; Initializer, called once for each module.

    assume rsi:ptr src_item

InputInit proc __ccall uses rsi

    mov SrcFree,NULL ;; v2.11
if FILESEQ
    mov FileSeq.head,NULL
endif
    mov ModuleInfo.max_line_len,MAX_LINE_LEN

    AllocInput()

    mov rsi,PushSrcItem( SIT_FILE, CurrFile[ASM*8] )
    AddFile( CurrFName[ASM*8] )
    mov [rsi].srcfile,ax
    mov ModuleInfo.srcfile,eax
    UpdateFileCur(GetFName(eax))
    ret

InputInit endp

;; init for each pass

InputPassInit proc __ccall

    mov rax,ModuleInfo.src_stack
    mov [rax].src_item.line_num,0
    mov CurrSource,srclinebuffer
    mov byte ptr [rax],0
    mov ModuleInfo.stringbufferend,token_stringbuf
    ret

InputPassInit endp

    assume rsi:ptr line_status

InputExtend proc __ccall uses rsi rdi rbx p:ptr line_status

  .new index:int_t
  .new oldsrcline:ptr
  .new oldstrings:ptr
  .new oldtok:token_t = ModuleInfo.tokenarray
  .new oldsize:uint_t = ModuleInfo.max_line_len

    add ModuleInfo.max_line_len,eax
    mov oldstrings,token_stringbuf
    mov oldsrcline,srclinebuffer

    mov rsi,rcx
    .if ( [rsi].start != rax )

        mov rbx,LclAlloc( ModuleInfo.max_line_len )
        mov rdx,[rsi].start
        sub [rsi].input,rdx
        add [rsi].input,rbx
        mov [rsi].start,rbx
        mov ecx,oldsize
        mov rdi,rbx
        mov rsi,rdx
        rep movsb
    .endif

    mov rsi,srclinebuffer
    mov ebx,oldsize

    AllocInput()
    ;
    ; copy source line buffer, token buffer, and string buffer
    ;
    mov  rdi,srclinebuffer
    mov  CurrSource,rdi

    imul ecx,ebx,MAX_MACRO_NESTING + 1
    rep  movsb
    mov  rdi,ModuleInfo.tokenarray
    mov  eax,ebx
    shr  eax,2
    imul ecx,eax,asm_tok * MAX_MACRO_NESTING
    rep  movsb
    mov  rdi,token_stringbuf
    imul ecx,ebx,MAX_MACRO_NESTING
    rep  movsb

    mov rsi,p
    mov rax,[rsi].outbuf
    .if ( rax == oldstrings )
        sub [rsi].output,rax
        mov [rsi].outbuf,token_stringbuf
        add [rsi].output,rax
    .endif

    mov rax,[rsi].start
    .if ( rax == oldsrcline )
        sub [rsi].input,rax
        mov [rsi].start,srclinebuffer
        add [rsi].input,rax
    .endif

    .if ( oldtok == [rsi].tokenarray )

        mov rdx,ModuleInfo.tokenarray
        mov [rsi].tokenarray,rdx
        mov index,[rsi].index
        mov rdi,srclinebuffer
        sub rdi,oldsrcline
        mov rsi,token_stringbuf
        mov rax,oldstrings
        sub rsi,rax
        add rbx,rax
        assume rdx:ptr asm_tok
        .for ( ecx = 0 : ecx <= index : ecx++, rdx += asm_tok )
            add [rdx].tokpos,rdi
            .if ( [rdx].string_ptr >= rax && [rdx].string_ptr <= rbx )
                add [rdx].string_ptr,rsi
            .endif
        .endf
    .endif
    .return( TRUE )

InputExtend endp

; release input buffers for a module

InputFini proc __ccall

    .if ModuleInfo.IncludePath

        MemFree( ModuleInfo.IncludePath )
    .endif

    ; free items in ModuleInfo.g.FNames ( and FreeFile, if FASTMEM==0 )

    FreeFiles()
    mov ModuleInfo.tokenarray,NULL
    ret

InputFini endp

    end
