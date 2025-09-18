; INPUT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; processing file/macro input data.
;

include asmc.inc
include memalloc.inc
include macro.inc
include input.inc
include tokenize.inc
include lqueue.inc

public FileCur
public LineCur

externdef strFILE:sbyte

DETECTCTRLZ equ 1 ;; 1=Ctrl-Z in input stream will skip rest of the file

;; FILESEQ: if 1, stores a linked list of source files, ordered
;; by usage. Masm stores such a list in the COFF symbol table
;; when -Zd/-Zi is set. It isn't necessary, however, and JWasm's
;; COFF code currently will ignore the list.

FILESEQ     equ 0

.data

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
StringBuffer  string_t 0
CommentBuffer string_t 0

token_buffer  string_t 0
string_buffer string_t 0

; string buffer - token strings and other stuff are stored here.
; must be a multiple of MAX_LINE_LEN since it is used for string expansion.

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

GetFNamePart proc fastcall fname:string_t

    .for ( rax = rcx : byte ptr [rcx] : rcx++ )

        .if ISPC( byte ptr [rcx] )
            lea rax,[rcx+1]
        .endif
    .endf
    ret

GetFNamePart endp


; fixme: if the dot is at pos 0 of filename, ignore it

GetExtPart proc fastcall fname:string_t

    .for ( eax = NULL : byte ptr [rcx] : rcx++ )

        .if ( byte ptr [rcx] == '.' )
            mov rax,rcx
        .elseif ISPC( byte ptr [rcx] )
            xor eax,eax
        .endif
    .endf
    .if ( rax == NULL )
        mov rax,rcx
    .endif
    ret

GetExtPart endp


; check if a file is in the array of known files.
; if no, store the file at the array's end.
; returns array index.
; used for the main source and all INCLUDEd files.
; the array is stored in the standard C heap!
; the filenames are stored in the "local" heap.

AddFile proc __ccall private uses rsi rbx name:string_t

    mov rsi,MODULE.FNames
    .for ( ebx = 0 : ebx < MODULE.cnt_fnames : ebx++ )
        .if ( filecmp( name, [rsi+rbx*string_t] ) == 0 )
            .return( ebx )
        .endif
    .endf

    .if ( !( ebx & 64-1 ) )

        mov MODULE.FNames,MemAlloc( &[rbx*string_t+64*string_t] )
        .if ( rsi != NULL )
            lea ecx,[rbx*string_t]
            tmemcpy( rax, rsi, ecx )
            MemFree( rsi )
        .endif
    .endif

    inc MODULE.cnt_fnames
    mov rsi,MODULE.FNames
    mov [rsi+rbx*string_t],LclDup( name )
   .return( ebx )

AddFile endp


GetFName proc fastcall index:uint_t

    and ecx,0xFFFF
    mov rax,MODULE.FNames
    mov rax,[rax+rcx*size_t]
    ret

GetFName endp


; free the file array.
; this is done once for each module after the last pass.

FreeFiles proc __ccall private

    ; v2.03: set src_stack=NULL to ensure that GetCurrSrcPos()
    ; won't find something when called from main().

    mov MODULE.src_stack,NULL
    .if ( MODULE.FNames )

        MemFree( MODULE.FNames )
        mov MODULE.FNames,NULL
    .endif
    ret

FreeFiles endp


; clear input source stack (include files and open macros).
; This is done after each pass.
; Usually the stack is empty when the END directive occurs,
; but it isn't required that the END directive is located in
; the main source file. Also, an END directive might be
; simulated if a "too many errors" condition occurs.

    assume rbx:ptr src_item

ClearSrcStack proc __ccall uses rsi rdi rbx

    DeleteLineQueue()

    ; dont close the last item (which is the main src file)

    mov rbx,MODULE.src_stack
    .new next:ptr
    .for( : [rbx].next : rbx = next )

        mov next,[rbx].next
        .if [rbx].type == SIT_FILE

            fclose([rbx].file)
        .endif
        mov [rbx].next,SrcFree
        mov SrcFree,rbx
    .endf
    mov MODULE.src_stack,rbx
    ret

ClearSrcStack endp

    assume rbx:nothing


UpdateFileCur proc fastcall private path:string_t

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

UpdateLineNumber proc fastcall sym:asym_t, p:ptr

    .for ( rax = MODULE.src_stack: rax : rax = [rax].src_item.next )

        .if ( [rax].src_item.type == SIT_FILE )

            mov [rcx].asym.value,[rax].src_item.line_num
           .break
        .endif
    .endf
    ret

UpdateLineNumber endp


GetLineNumber proc __ccall

    UpdateLineNumber( LineCur, NULL )
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

my_fgets proc __ccall private uses rsi rdi rbx buffer:string_t, max:int_t, fp:LPFILE

    ldr rdi,buffer
    ldr rbx,fp
    ldr edx,max

    lea rsi,[rdi+rdx]

    .while ( rdi < rsi )

ifdef __UNIX__
ifdef _WIN64
       .new _rsi:qword = rsi
       .new _rdi:qword = rdi
endif
        fgetc(rbx)
ifdef _WIN64
        mov rsi,_rsi
        mov rdi,_rdi
endif
else
        .if ( [rbx].FILE._cnt > 0 )

            dec [rbx].FILE._cnt
            mov rdx,[rbx].FILE._ptr
            inc [rbx].FILE._ptr
            movzx eax,byte ptr [rdx]
        .else
            _filbuf(rbx)
        .endif
endif
        .switch eax
        .case CR
            .continue ; don't store CR
        .case LF
            mov byte ptr [rdi],0
            .return( buffer )
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
            .if ( rdi > buffer )
                mov rax,buffer
            .endif
            .return
        .endsw
        stosb
    .endw
    asmerr( 2039 )
    mov byte ptr [rdi-1],0
    mov rax,buffer
    ret

my_fgets endp


if FILESEQ

AddFileSeq proc __ccall file:uint_t

    LclAlloc( ldr(file) )

    mov ecx,file
    mov [rax].file_seq.file,ecx
    .if ( FileSeq.head == NULL )

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

    mov rax,SrcFree
    .if ( rax )
        mov rcx,[rax].src_item.next
        mov SrcFree,rcx
    .else
        LclAlloc( src_item )
    .endif
    mov rcx,MODULE.src_stack
    mov [rax].src_item.next,rcx
    mov MODULE.src_stack,rax
    movzx ecx,type
    mov [rax].src_item.type,cx
    mov rcx,pv
    mov [rax].src_item.content,rcx
    mov [rax].src_item.line_num,0
    ret

PushSrcItem endp


; push a macro onto the source stack.

PushMacro proc fastcall mi:ptr macro_instance

    PushSrcItem( SIT_MACRO, rcx )
    ret

PushMacro endp


get_curr_srcfile proc __ccall

    .for ( rax = MODULE.src_stack: rax : rax = [rax].src_item.next )

        .if ( [rax].src_item.type == SIT_FILE )
            movzx eax,[rax].src_item.srcfile
           .return
        .endif
    .endf
    .return( MODULE.srcfile )

get_curr_srcfile endp


set_curr_srcfile proc fastcall file:uint_t, line:uint_t

    mov rax,MODULE.src_stack
    mov [rax].src_item.srcfile,cx
    mov [rax].src_item.line_num,edx
    ret

set_curr_srcfile endp


SetLineNumber proc fastcall line:uint_t

    mov rax,MODULE.src_stack
    mov [rax].src_item.line_num,ecx
    ret

SetLineNumber endp

if 0
; for error listing, render the current source file and line
; this function is also called if pass is > 1,
; which is a problem for FASTPASS because the file stack is empty.

    assume rcx:ptr src_item

GetCurrSrcPos proc fastcall private uses rbx buffer:string_t

    .for ( rbx = rcx, rcx = MODULE.src_stack: rcx : rcx = [rcx].next )

        .if ( [rcx].type == SIT_FILE )

            movzx eax,[rcx].srcfile
            mov rax,MODULE.FNames
            mov rax,[rdx+rax*string_t]
            lea rdx,@CStr("%s : ")

            .if ( MODULE.EndDirFound == FALSE )
                lea rdx,@CStr("%s(%u) : ")
            .endif
            .return tsprintf( rbx, rdx, rax, [rcx].line_num )
        .endif
    .endf
    xor eax,eax
    mov [rbx],al
    ret

GetCurrSrcPos endp

    assume rcx:nothing
endif

; for error listing, render the source nesting structure.
; the structure consists of include files and macros.

    assume rbx:ptr src_item

print_source_nesting_structure proc __ccall uses rsi rdi rbx

   .new name:string_t
    mov rbx,MODULE.src_stack

    ; in main source file?

    .if ( rbx == NULL || [rbx].next == NULL )
        .return
    .endif

    .for ( edi = 1 : [rbx].next : rbx = [rbx].next, edi++ )

        .if ( [rbx].type == SIT_FILE )

            mov name,GetFName( [rbx].srcfile )
            PrintNote( NOTE_INCLUDED_BY, edi, "", name, [rbx].line_num )

        .else

            mov rax,[rbx].mi
            mov rcx,[rax].macro_instance._macro
            mov rax,[rcx].asym.name

            .if ( byte ptr [rax] == 0 )

                mov edx,[rcx].asym.value
                inc edx
                PrintNote( NOTE_ITERATION_MACRO_CALLED_FROM, edi, "",
                    "MacroLoop", [rbx].line_num, edx )
            .else

                mov name,rax
                mov rdx,[rcx].asym.macroinfo
                mov eax,[rdx].macro_info.srcfile
                GetFNamePart( GetFName( eax ) )
                PrintNote( NOTE_MACRO_CALLED_FROM, edi, "", name, [rbx].line_num, rax )
            .endif
        .endif
    .endf
    mov name,GetFName( [rbx].srcfile )
    PrintNote( NOTE_MAIN_LINE_CODE, edi, "", name, [rbx].line_num )
    ret

print_source_nesting_structure endp

    assume rbx:nothing


; Scan the include path for a file!
; variable ModuleInfo.g.IncludePath also contains directories set with -I cmdline option.

open_file_in_include_path proc __ccall private uses rsi rdi rbx name:string_t, fullpath:string_t

   .new next:string_t
   .new namelen:int_t

    mov name,ltokstart( name )
    mov namelen,tstrlen( rax )

    .for ( eax = 0, rbx = MODULE.IncludePath : rbx && !rax : rbx = next )

        mov next,tstrchr( rbx, INC_PATH_DELIM )

        .if ( rax )
            sub rax,rbx
            inc next ; skip path delimiter char (; or :)
        .else
            tstrlen( rbx )
        .endif
        mov edi,eax

        ; v2.06: ignore
        ; - "empty" entries in PATH
        ; - entries which would cause a buffer overflow

        mov ecx,namelen
        add ecx,edi
        .if ( edi == 0 || ( ecx >= FILENAME_MAX ) )
            .continue
        .endif
        tmemcpy( fullpath, rbx, edi )

        mov cl,[rax+rdi-1]
ifndef __UNIX__
        .if ( cl != '/' && cl != '\' && cl != ':' )
else
        .if ( cl != '/' )
endif
            mov byte ptr [rax+rdi],DIR_SEPARATOR
            inc edi
        .endif

        mov rcx,fullpath
        tstrcpy( &[rcx+rdi], name )
        fopen( fullpath, "rb" )
    .endf
    ret

open_file_in_include_path endp


; the worker behind the INCLUDE directive. Also used
; by INCBIN and the -Fi cmdline option.
; the main source file is added in InputInit().
; v2.12: _splitpath()/_makepath() removed

    assume rbx:ptr src_item

SearchFile proc __ccall uses rsi rdi rbx path:string_t, queue:int_t

   .new fullpath[FILENAME_MAX]:char_t
   .new file:ptr FILE = NULL
   .new isabs:int_t = ISABS( path )

    ; if no absolute path is given, then search in the directory
    ; of the current source file first!
    ; v2.11: various changes because field fullpath has been removed.

    .if ( isabs == 0 )

        .for ( rbx = MODULE.src_stack: rbx : rbx = [rbx].next )

            .if ( [rbx].type == SIT_FILE )

                mov rsi,GetFName( [rbx].srcfile )

                .if ( rsi != GetFNamePart( rsi ) )

                    sub rax,rsi

                    ; v2.10: if there's a directory part, add it to the directory part of the current file.
                    ; fixme: check that both parts won't exceed FILENAME_MAX!
                    ; fixme: 'path' is relative, but it may contain a drive letter!

                    lea rdi,fullpath
                    mov ecx,eax
                    rep movsb
                    mov rsi,path
                    .repeat
                        lodsb
                        stosb
                    .until !al

                    mov file,fopen( &fullpath, "rb" )
                    .if rax
                        mov path,&fullpath
                    .endif
                .endif
                .break
            .endif
        .endf
    .endif

    .if ( file == NULL )

        mov fullpath,0
        mov file,fopen( path, "rb" )

        ; if the file isn't found yet and include paths have been set,
        ; and NO absolute path is given, then search include dirs

        .if ( file == NULL && MODULE.IncludePath != NULL && !isabs )
            .if ( open_file_in_include_path( path, &fullpath ) )

                mov file,rax
                mov path,&fullpath
            .endif
        .endif
        .if ( file == NULL )
            asmerr( 1000, path )
        .endif
    .endif

    ; is the file to be added to the file stack?
    ; assembly files usually are, but binary files ( INCBIN ) aren't.

    .if ( queue )

        mov rbx,PushSrcItem( SIT_FILE, file )
        AddFile( path )
        mov [rbx].srcfile,ax
        UpdateFileCur( GetFName( eax ) )
if FILESEQ
        .if ( Options.line_numbers && Parse_Pass == PASS_1 )
            AddFileSeq( [rbx].srcfile )
        .endif
endif
    .endif
    .return( file )

SearchFile endp


; get the next source line from file or macro.
; v2.11: line queues are no longer read here,
; this is now done in RunLineQueue().
; Also, if EOF/EOM is reached, the function will
; now return NULL in any case.

GetTextLine proc __ccall uses rsi rdi rbx buffer:string_t

    mov rbx,MODULE.src_stack

    .if ( [rbx].type == SIT_FILE )

        .if my_fgets( buffer, MaxLineLength, [rbx].file )

            inc [rbx].line_num
           .return( buffer )
        .endif

        ; don't close and remove main source file

        .if ( [rbx].next )

            fclose( [rbx].file )

            mov MODULE.src_stack,[rbx].next
            mov [rbx].next,SrcFree
            mov SrcFree,rbx
        .endif

        ; update value of @FileCur variable

        .for ( rbx = MODULE.src_stack: [rbx].type != SIT_FILE: rbx = [rbx].next )
        .endf
        UpdateFileCur( GetFName( [rbx].srcfile ) )

if FILESEQ
        .if ( Options.line_numbers && Parse_Pass == PASS_1 )
            AddFileSeq( [rbx].srcfile )
        .endif
endif

    .else

        assume rdi:ptr macro_instance

        mov rdi,[rbx].mi
        .if ( [rdi].currline )
            mov rcx,[rdi].currline
            mov rax,[rcx].srcline.next
        .else
            mov rax,[rdi].startline
        .endif
        mov [rdi].currline,rax

        .if ( rax )

            ; if line contains placeholders, replace them by current values

            .if ( [rax].srcline.ph_count )

                lea rdx,[rax].srcline.line
                fill_placeholders( buffer, rdx, [rdi].parmcnt,
                                  [rdi].localstart, [rdi].parm_array )
            .else
                tstrcpy( buffer, &[rax].srcline.line )
            .endif
            inc [rbx].line_num
           .return( buffer )
        .endif
        mov MODULE.src_stack,[rbx].next
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

    mov rsi,tstrstart( string )

    .if ( tstrlen( rsi ) )

        .if ( MODULE.IncludePath == NULL )

            mov MODULE.IncludePath,MemDup( rsi )

        .else

            mov edi,eax
            mov rbx,MODULE.IncludePath
            tstrlen( rbx )
            mov MODULE.IncludePath,MemAlloc( &[rax + rdi + 2] )
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
; - field TokenCount
; - field line_flags

    assume rbx:ptr input_status

GetInputState proc __ccall uses rbx p:ptr InputState

    ldr rbx,p
    mov rax,CurrSource
    sub rax,srclinebuffer
    mov [rbx].scr_pos,eax
    mov rax,StringBufferEnd
    sub rax,StringBuffer
    mov [rbx].end_off,eax
    mov rax,TokenArray
    sub rax,token_buffer
    mov [rbx].arr_pos,eax
    mov rax,StringBuffer
    sub rax,string_buffer
    mov [rbx].str_pos,eax
    mov rax,rbx
    ret

GetInputState endp

SetInputState proc __ccall p:ptr InputState

    ldr rbx,p
    mov eax,[rbx].scr_pos
    add rax,srclinebuffer
    mov CurrSource,rax
    mov eax,[rbx].arr_pos
    add rax,token_buffer
    mov TokenArray,rax
    mov eax,[rbx].str_pos
    add rax,string_buffer
    mov StringBuffer,rax
    mov ecx,[rbx].end_off
    add rax,rcx
    mov StringBufferEnd,rax
    mov rax,rbx
    ret

SetInputState endp

PushInputStatus proc __ccall uses rbx oldstat:ptr input_status

    ldr rbx,oldstat

    mov [rbx].flags,MODULE.line_flags
    mov [rbx].tok_cnt,TokenCount
    mov rax,CurrSource
    sub rax,srclinebuffer
    mov [rbx].scr_pos,eax
    mov rax,StringBufferEnd
    sub rax,StringBuffer
    mov [rbx].end_off,eax
    mov rax,TokenArray
    sub rax,token_buffer
    mov [rbx].arr_pos,eax
    mov rax,StringBuffer
    sub rax,string_buffer
    mov [rbx].str_pos,eax

    ; if there's a comment, attach it to current source

    mov rax,CurrComment
    .if ( rax )

        tstrlen( CurrSource )
        add rax,CurrSource
        tstrcpy( rax, CurrComment )
    .endif
    mov [rbx].currcomment,rax

    mov StringBuffer,StringBufferEnd
    mov  eax,TokenCount
    inc  eax
    imul eax,eax,asm_tok
    add  TokenArray,rax
    tstrlen( CurrSource )
    mov CurrSource,GetAlignedPointer( CurrSource, eax )
   .return( TokenArray )

PushInputStatus endp

PopInputStatus proc __ccall uses rbx newstat:ptr input_status

    ldr rbx,newstat

    mov MODULE.line_flags,[rbx].flags ; v2.08
    mov TokenCount,[rbx].tok_cnt

    mov eax,[rbx].scr_pos
    add rax,srclinebuffer
    mov CurrSource,rax
    mov eax,[rbx].arr_pos
    add rax,token_buffer
    mov TokenArray,rax
    mov eax,[rbx].str_pos
    add rax,string_buffer
    mov StringBuffer,rax
    mov ecx,[rbx].end_off
    add rax,rcx
    mov StringBufferEnd,rax

    .if ( [rbx].currcomment )

        mov CurrComment,CommentBuffer
        tstrcpy(rax, [rbx].currcomment)
        mov rax,[rbx].currcomment
        mov byte ptr [rax],0
    .else
        mov CurrComment,NULL
    .endif
    ret

PopInputStatus endp

;
; Input:
;   srcline     [MAX_MACRO_NESTING*MAX_LINE_LEN]
;   comment     [MAX_LINE_LEN]
;   tokenarray  [asm_tok*(MAX_LINE_LEN/4)*MAX_MACRO_NESTING]
;   stringbuff  [MAX_MACRO_NESTING*MAX_LINE_LEN]
;

AllocInput proc __ccall private uses rsi rdi

    mov     eax,MaxLineLength
    imul    rsi,rax,MAX_MACRO_NESTING + 1  ; SIZE_SRCLINES
    imul    rdx,rax,MAX_MACRO_NESTING      ; SIZE_STRINGBUFFER
    shr     rax,2                          ; SIZE_TOKENARRAY
    imul    rdi,rax,asm_tok * MAX_MACRO_NESTING
    add     rdx,rdi
    add     rdx,rsi
    shl     rax,2
    add     rax,rdx
    mov     srclinebuffer,MemAlloc( eax )

    ; the comment buffer is at the end of the source line buffer
    ; behind the comment buffer is the token buffer

    lea     rcx,[rax+rsi]
    mov     TokenArray,rcx
    mov     token_buffer,rcx
    add     rdi,rcx
    mov     string_buffer,rdi
    mov     StringBuffer,rdi
    mov     StringBufferEnd,rdi
    mov     edx,MaxLineLength
    sub     rcx,rdx
    mov     CommentBuffer,rcx
    ret

AllocInput endp


; Initializer, called once for each module.

    assume rsi:ptr src_item

InputInit proc __ccall uses rsi

    mov SrcFree,NULL ;; v2.11
if FILESEQ
    mov FileSeq.head,NULL
endif
    mov MaxLineLength,MAX_LINE_LEN

    AllocInput()

    mov rsi,PushSrcItem( SIT_FILE, CurrFile[ASM*size_t] )
    AddFile( CurrFName[ASM*size_t] )
    mov [rsi].srcfile,ax
    mov MODULE.srcfile,eax

    UpdateFileCur( GetFName( eax ) )
    ret

InputInit endp


; init for each pass

InputPassInit proc __ccall

    mov rax,MODULE.src_stack
    mov [rax].src_item.line_num,0
    mov CurrSource,srclinebuffer
    mov byte ptr [rax],0
    mov StringBufferEnd,StringBuffer
    ret

InputPassInit endp


    assume rsi:ptr line_status

InputExtend proc __ccall uses rsi rdi rbx p:ptr line_status

  .new index:int_t
  .new oldsrcline:ptr = srclinebuffer
  .new oldstrings:ptr = StringBuffer
  .new oldend:ptr     = StringBufferEnd
  .new oldtok:token_t = TokenArray
  .new oldsize:uint_t = MaxLineLength

    .if ( eax > _HEAP_GROWSIZE )
        mov eax,_HEAP_GROWSIZE
    .endif
    add MaxLineLength,eax

    mov rax,srclinebuffer
    ldr rsi,p
    .if ( [rsi].start != rax )

        mov rbx,LclAlloc( MaxLineLength )
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
    mov  rdi,TokenArray
    mov  eax,ebx
    shr  eax,2
    imul ecx,eax,asm_tok * MAX_MACRO_NESTING
    rep  movsb
    mov  rdi,StringBuffer
    mov  rax,oldend
    sub  rax,oldstrings
    add  StringBufferEnd,rax
    imul ecx,ebx,MAX_MACRO_NESTING
    rep  movsb

    mov rsi,p
    mov rax,[rsi].outbuf
    .if ( rax == oldstrings )
        sub [rsi].output,rax
        mov [rsi].outbuf,StringBuffer
        add [rsi].output,rax
    .endif

    mov rax,[rsi].start
    .if ( rax == oldsrcline )
        sub [rsi].input,rax
        mov [rsi].start,srclinebuffer
        add [rsi].input,rax
    .endif

    .if ( oldtok == [rsi].tokenarray )

        mov rdx,TokenArray
        mov [rsi].tokenarray,rdx
        mov index,[rsi].index
        mov rdi,srclinebuffer
        sub rdi,oldsrcline
        mov rsi,StringBuffer
        mov rax,oldstrings
        sub rsi,rax
        imul ebx,ebx,MAX_MACRO_NESTING+1
        add rbx,rax

        assume rdx:token_t

        .for ( ecx = 0 : ecx <= index : ecx++, rdx += asm_tok )

            add [rdx].tokpos,rdi
            .if ( [rdx].string_ptr >= rax && [rdx].string_ptr <= rbx )
                add [rdx].string_ptr,rsi
            .endif
        .endf
        MemFree( oldsrcline )
    .endif
    .return( TRUE )

InputExtend endp


; release input buffers for a module

InputFini proc __ccall

    mov rcx,MODULE.IncludePath
    .if ( rcx )

        MemFree( rcx )
    .endif
    mov rcx,srclinebuffer
    .if ( rcx )

        MemFree( rcx )
        mov srclinebuffer,NULL
    .endif

    ; free items in ModuleInfo.g.FNames ( and FreeFile, if FASTMEM==0 )

    FreeFiles()
    mov TokenArray,NULL
    ret

InputFini endp

    end
