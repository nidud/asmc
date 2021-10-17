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

;; buffer for source lines
;; since the lines are sometimes concatenated
;; the buffer must be a multiple of MAX_LINE_LEN

srclinebuffer string_t 0

;; string buffer - token strings and other stuff are stored here.
;; must be a multiple of MAX_LINE_LEN since it is used for string expansion.

token_stringbuf string_t 0 ;; start token string buffer

;; fixme: add '|| defined(__CYGWIN__)' ?
ifdef __UNIX__
INC_PATH_DELIM      equ <':'>
INC_PATH_DELIM_STR  equ <":">
DIR_SEPARATOR       equ <'/'>
filecmp             equ <strcmp>
ISPC macro x
    exitm<( x == '/' )>
    endm
ISABS macro x
    exitm<( *x == '/' )>
    endm
else
INC_PATH_DELIM      equ <';'>
INC_PATH_DELIM_STR  equ <";">
DIR_SEPARATOR       equ <'\'>
filecmp             equ <_stricmp>
ISPC macro x
    exitm<(x == '/' || x == '\' || x == ':')>
    endm
ISABS macro x
  ifdif <x>,<eax>
    mov eax,x
  endif
    mov cl,[eax+2]
    mov eax,[eax]
    .if ( al == '/' || al == '\' || ( al &&  ah == ':' && ( cl == '/' || cl == '\' ) ) )
        mov eax,1
    .else
        xor eax,eax
    .endif
    exitm<eax>
    endm
endif

    .code

;; v2.12: function added - _splitpath()/_makepath() removed

GetFNamePart proc fname:string_t

    .for ( eax = fname, ecx = eax : byte ptr [ecx] : ecx++ )
        .if ISPC( byte ptr [ecx] )
            lea eax,[ecx+1]
        .endif
    .endf
    ret

GetFNamePart endp

;; fixme: if the dot is at pos 0 of filename, ignore it

GetExtPart proc fname:string_t

    .for( eax = NULL, ecx = fname: byte ptr [ecx]: ecx++ )
        .if byte ptr [ecx] == '.'
            mov eax,ecx
        .elseif ISPC( byte ptr [ecx] )
            mov eax,NULL
        .endif
    .endf
    .if !eax
        mov eax,ecx
    .endif
    ret

GetExtPart endp

;; check if a file is in the array of known files.
;; if no, store the file at the array's end.
;; returns array index.
;; used for the main source and all INCLUDEd files.
;; the array is stored in the standard C heap!
;; the filenames are stored in the "local" heap.

AddFile proc private uses esi edi ebx name:string_t

    .for( ebx = 0: ebx < ModuleInfo.cnt_fnames: ebx++ )

        mov eax,ModuleInfo.FNames
        .return ebx .if !filecmp(name, [eax+ebx*4])
    .endf

    mov eax,ebx
    and eax,64-1
    .if eax == 0
        mov edi,MemAlloc(&[ebx*4+64*4])
        .if ModuleInfo.FNames
            mov ecx,ebx
            mov esi,ModuleInfo.FNames
            rep movsd
            mov edi,eax
            MemFree(ModuleInfo.FNames)
        .endif
        mov ModuleInfo.FNames,edi
    .endif
    inc ModuleInfo.cnt_fnames
    LclAlloc( &[strlen(name)+1] )
    mov ecx,ModuleInfo.FNames
    mov [ecx+ebx*4],eax
    strcpy(eax, name)
    mov eax,ebx
    ret

AddFile endp

GetFName proc index:uint_t

    mov eax,index
    mov ecx,ModuleInfo.FNames
    mov eax,[ecx+eax*4]
    ret

GetFName endp

;; free the file array.
;; this is done once for each module after the last pass.

FreeFiles proc private

    ;; v2.03: set src_stack=NULL to ensure that GetCurrSrcPos()
    ;; won't find something when called from main().

    mov ModuleInfo.src_stack,NULL
    .if ModuleInfo.FNames
        MemFree(ModuleInfo.FNames)
        mov ModuleInfo.FNames,NULL
    .endif
    ret

FreeFiles endp

;; clear input source stack (include files and open macros).
;; This is done after each pass.
;; Usually the stack is empty when the END directive occurs,
;; but it isn't required that the END directive is located in
;; the main source file. Also, an END directive might be
;; simulated if a "too many errors" condition occurs.

    assume esi:ptr src_item

ClearSrcStack proc uses esi edi

    DeleteLineQueue()

    ;; dont close the last item (which is the main src file)
    mov esi,ModuleInfo.src_stack
    .for( : [esi].next : esi = edi )
        mov edi,[esi].next
        .if [esi].type == SIT_FILE
            fclose([esi].file)
        .endif
        mov [esi].next,SrcFree
        mov SrcFree,esi
    .endf
    mov ModuleInfo.src_stack,esi
    ret

ClearSrcStack endp

    assume esi:nothing

;; get/set value of predefined symbol @Line

UpdateLineNumber proc sym:asym_t, p:ptr

    .for ( eax = ModuleInfo.src_stack: eax : eax = [eax].src_item.next )
        .if [eax].src_item.type == SIT_FILE
            mov ecx,sym
            mov [ecx].asym.value,[eax].src_item.line_num
            .break
        .endif
    .endf
    ret

UpdateLineNumber endp

GetLineNumber proc

    UpdateLineNumber(LineCur, NULL)
    mov eax,LineCur
    mov eax,[eax].asym.uvalue
    ret

GetLineNumber endp

;; read one line from current source file.
;; returns NULL if EOF has been detected and no char stored in buffer
;; v2.08: 00 in the stream no longer causes an exit. Hence if the
;; char occurs in the comment part, everything is ok.

LF equ 10
CR equ 13

my_fgets proc private uses esi edi ebx buffer:string_t, max:int_t, fp:LPFILE

    mov edi,buffer
    mov esi,max
    add esi,edi
    mov ebx,fp

    dec [ebx]._iobuf._cnt
    .ifl
        _filbuf(ebx)
    .else
        inc [ebx]._iobuf._ptr
        mov eax,[ebx]._iobuf._ptr
        movzx eax,byte ptr [eax-1]
    .endif
    .while edi < esi
        .switch eax
        .case CR
            .endc ;; don't store CR
        .case LF
            mov byte ptr [edi],0
            .return buffer
if DETECTCTRLZ
        .case 0x1a
            ;; since source files are opened in binary mode, ctrl-z
            ;; handling must be done here.
            ;;
            ;; no break
endif
        .case -1
            mov byte ptr [edi],0
            xor eax,eax
            .if edi > buffer
                mov eax,buffer
            .endif
            .return
        .default
            stosb
        .endsw
        dec [ebx]._iobuf._cnt
        .ifl
            _filbuf(ebx)
        .else
            inc [ebx]._iobuf._ptr
            mov eax,[ebx]._iobuf._ptr
            movzx eax,byte ptr [eax-1]
        .endif
    .endw
    asmerr(2039)
    mov byte ptr [edi-1],0
    mov eax,buffer
    ret

my_fgets endp

if FILESEQ
AddFileSeq proc file:uint_t
    LclAlloc(file_seq)
    mov [eax].file_seq.next,NULL
    mov ecx,file
    mov [eax].file_seq.file,ecx
    .if FileSeq.head == NULL
        mov FileSeq.head,eax
        mov FileSeq.tail,eax
    .else
        mov ecx,FileSeq.tail
        mov [ecx].file_seq.next,eax
        mov FileSeq.tail,eax
    .endif
    ret
AddFileSeq endp
endif

;; push a new item onto the source stack.
;; type: SIT_FILE or SIT_MACRO

PushSrcItem proc private type:char_t, pv:ptr

    .if SrcFree
        mov eax,SrcFree
        mov ecx,[eax].src_item.next
        mov SrcFree,ecx
    .else
        LclAlloc(src_item)
    .endif
    mov ecx,ModuleInfo.src_stack
    mov [eax].src_item.next,ecx
    mov ModuleInfo.src_stack,eax
    movzx ecx,type
    mov [eax].src_item.type,cx
    mov ecx,pv
    mov [eax].src_item.content,ecx
    mov [eax].src_item.line_num,0
    ret

PushSrcItem endp

;; push a macro onto the source stack.

PushMacro proc mi:ptr macro_instance

    PushSrcItem( SIT_MACRO, mi )
    ret

PushMacro endp

get_curr_srcfile proc

    .for ( eax = ModuleInfo.src_stack: eax : eax = [eax].src_item.next )
        .if [eax].src_item.type == SIT_FILE
            movzx eax,[eax].src_item.srcfile
            .return
        .endif
    .endf
    mov eax,ModuleInfo.srcfile
    ret

get_curr_srcfile endp

set_curr_srcfile proc file:uint_t, line_num:uint_t

    mov ecx,ModuleInfo.src_stack
    mov eax,file
    mov [ecx].src_item.srcfile,ax
    mov [ecx].src_item.line_num,line_num
    ret

set_curr_srcfile endp

SetLineNumber proc line:uint_t

    mov ecx,ModuleInfo.src_stack
    mov [ecx].src_item.line_num,line
    ret

SetLineNumber endp

;; for error listing, render the current source file and line
;; this function is also called if pass is > 1,
;; which is a problem for FASTPASS because the file stack is empty.

    assume ecx:ptr src_item

GetCurrSrcPos proc private buffer:string_t

    .for ( ecx = ModuleInfo.src_stack: ecx : ecx = [ecx].next )

        .if [ecx].type == SIT_FILE

            movzx eax,[ecx].srcfile
            mov edx,ModuleInfo.FNames
            mov eax,[edx+eax*4]
            .if ModuleInfo.EndDirFound == FALSE
                lea edx,@CStr("%s(%u) : ")
            .else
                lea edx,@CStr("%s : ")
            .endif
            .return tsprintf(buffer, edx, eax, [ecx].line_num)
        .endif
    .endf
    xor eax,eax
    mov ecx,buffer
    mov [ecx],al
    ret

GetCurrSrcPos endp

    assume ecx:nothing

;; for error listing, render the source nesting structure.
;; the structure consists of include files and macros.

    assume ebx:ptr src_item

print_source_nesting_structure proc uses esi edi ebx

    mov ebx,ModuleInfo.src_stack

    ;; in main source file?
    .return .if ebx == NULL || [ebx].next == NULL

    .for ( edi = 1 : [ebx].next : ebx = [ebx].next, edi++ )

        .if [ebx].type == SIT_FILE

            PrintNote( NOTE_INCLUDED_BY, edi, "", GetFName( [ebx].srcfile ), [ebx].line_num )

        .else

            mov eax,[ebx].mi
            mov ecx,[eax].macro_instance._macro
            mov eax,[ecx].asym.name

            .if byte ptr [eax] == 0

                mov edx,[ecx].asym.value
                inc edx
                PrintNote( NOTE_ITERATION_MACRO_CALLED_FROM, edi, "",
                    "MacroLoop", [ebx].line_num, edx )
            .else
                push eax
                mov edx,[ecx].dsym.macroinfo
                mov eax,[edx].macro_info.srcfile
                GetFNamePart(GetFName(eax))
                pop ecx
                PrintNote( NOTE_MACRO_CALLED_FROM, edi, "", ecx, [ebx].line_num, eax )
            .endif
        .endif
    .endf
    PrintNote( NOTE_MAIN_LINE_CODE, edi, "", GetFName( [ebx].srcfile ), [ebx].line_num )
    ret

print_source_nesting_structure endp

    assume ebx:nothing

;; Scan the include path for a file!
;; variable ModuleInfo.g.IncludePath also contains directories set with -I cmdline option.

open_file_in_include_path proc private uses esi edi ebx name:string_t, fullpath:string_t

    local curr:string_t
    local next:string_t
    local i:int_t
    local namelen:int_t
    local file:ptr FILE

    mov file,NULL
    mov name,ltokstart(name)
    mov namelen,strlen(eax)

    .for ( ebx = ModuleInfo.IncludePath: ebx: ebx = next )

        xor eax,eax
        mov ecx,-1
        mov edi,ebx
        repnz scasb
        not ecx
        dec ecx
        mov i,ecx
        mov next,eax
        .ifnz
            mov edi,ebx
            mov eax,INC_PATH_DELIM
            repnz scasb
            .ifz
                mov next,edi ;; skip path delimiter char (; or :)
                sub edi,ebx
                dec edi
                mov i,edi
            .endif
        .endif

        ;; v2.06: ignore
        ;; - "empty" entries in PATH
        ;; - entries which would cause a buffer overflow
        mov ecx,i
        mov eax,ecx
        add eax,namelen
        .continue .if ( ecx == 0 || ( eax >= FILENAME_MAX ) )

        mov edx,fullpath
        mov esi,ebx
        mov edi,edx
        rep movsb
        mov al,[edi-1]
        .if al != '/' && al != '\' && al != ':'
            mov al,DIR_SEPARATOR
            stosb
        .endif
        mov ecx,namelen
        inc ecx
        mov esi,name
        rep movsb
        mov file,fopen(edx, "rb")
        .break .if eax
    .endf
    mov eax,file
    ret

open_file_in_include_path endp

;; the worker behind the INCLUDE directive. Also used
;; by INCBIN and the -Fi cmdline option.
;; the main source file is added in InputInit().
;; v2.12: _splitpath()/_makepath() removed

    assume ebx:ptr src_item

SearchFile proc uses esi edi ebx path:string_t, queue:int_t

    local file:ptr FILE
    local fl:ptr src_item
    local fn:string_t
    local isabs:int_t
    local fullpath[FILENAME_MAX]:char_t
    local fn2:string_t
    local src:string_t

    mov file,NULL
    mov fn,GetFNamePart(path)

    ;; if no absolute path is given, then search in the directory
    ;; of the current source file first!
    ;; v2.11: various changes because field fullpath has been removed.

    mov isabs,ISABS(path)

    .if ( !isabs )

        .for ( ebx = ModuleInfo.src_stack: ebx : ebx = [ebx].next )

            .if [ebx].type == SIT_FILE

                mov src,GetFName( [ebx].srcfile )
                mov fn2,GetFNamePart(eax)
                .if eax != src

                    sub eax,src

                    ;; v2.10: if there's a directory part, add it to the directory part of the current file.
                    ;; fixme: check that both parts won't exceed FILENAME_MAX!
                    ;; fixme: 'path' is relative, but it may contain a drive letter!

                    lea edi,fullpath
                    mov esi,src
                    mov ecx,eax
                    rep movsb
                    mov esi,path
                    .repeat
                        lodsb
                        stosb
                    .until !al
                    mov file,fopen(&fullpath, "rb")
                    .if eax
                        lea eax,fullpath
                        mov path,eax
                    .endif
                .endif
                .break
            .endif
        .endf
    .endif

    .if file == NULL

        mov fullpath,0
        mov file,fopen(path, "rb")

        ;; if the file isn't found yet and include paths have been set,
        ;; and NO absolute path is given, then search include dirs

        .if file == NULL && ModuleInfo.IncludePath != NULL && !isabs
            .if open_file_in_include_path(path, &fullpath)
                mov file,eax
                lea eax,fullpath
                mov path,eax
            .endif
        .endif
        .if file == NULL
            asmerr(1000, path)
        .endif
    .endif
    ;; is the file to be added to the file stack?
    ;; assembly files usually are, but binary files ( INCBIN ) aren't.

    .if queue
        mov ebx,PushSrcItem(SIT_FILE, file)
        AddFile(path)
        mov [ebx].srcfile,ax
        GetFName(eax)
        mov edx,FileCur
        mov [edx].asym.string_ptr,eax
if FILESEQ
        .if Options.line_numbers && Parse_Pass == PASS_1
            AddFileSeq([ebx].srcfile)
        .endif
endif
    .endif
    mov eax,file
    ret

SearchFile endp

;; get the next source line from file or macro.
;; v2.11: line queues are no longer read here,
;; this is now done in RunLineQueue().
;; Also, if EOF/EOM is reached, the function will
;; now return NULL in any case.

GetTextLine proc uses esi edi ebx buffer:string_t

    mov ebx,ModuleInfo.src_stack

    .if [ebx].type == SIT_FILE

        .if my_fgets(buffer, ModuleInfo.max_line_len, [ebx].file)

            inc [ebx].line_num
            .return buffer
        .endif

        ;; don't close and remove main source file
        .if [ebx].next
            fclose([ebx].file)
            mov ModuleInfo.src_stack,[ebx].next
            mov [ebx].next,SrcFree
            mov SrcFree,ebx
        .endif
        ;; update value of @FileCur variable
        .for ( ebx = ModuleInfo.src_stack: [ebx].type != SIT_FILE: ebx = [ebx].next )
            GetFName([ebx].srcfile)
            mov edx,FileCur
            mov [edx].asym.string_ptr,eax
        .endf
if FILESEQ
        .if Options.line_numbers && Parse_Pass == PASS_1
            AddFileSeq([ebx].srcfile)
        .endif
endif

    .else

        assume edi:ptr macro_instance
        mov edi,[ebx].mi
        .if [edi].currline
            mov ecx,[edi].currline
            mov eax,[ecx].srcline.next
        .else
            mov eax,[edi].startline
        .endif
        mov [edi].currline,eax

        .if eax
            ;; if line contains placeholders, replace them by current values
            .if [eax].srcline.ph_count
                fill_placeholders(buffer, &[eax].srcline.line, [edi].parmcnt,
                                  [edi].localstart, [edi].parm_array )
            .else
                strcpy(buffer, &[eax].srcline.line)
            .endif
            inc [ebx].line_num
            .return buffer
        .endif
        mov ModuleInfo.src_stack,[ebx].next
        mov [ebx].next,SrcFree
        mov SrcFree,ebx
    .endif
    mov eax,NULL ;; end of file or macro reached
    ret

GetTextLine endp

;; add a string to the include path.
;; called for -I cmdline options.
;; the include path is rebuilt for each assembled module.
;; it is stored in the standard C heap.

AddStringToIncludePath proc uses esi edi string:string_t

    mov esi,ltokstart(string)
    mov edi,esi
    mov ecx,-1
    xor eax,eax
    repnz scasb
    not ecx
    dec ecx
    .return .ifz

    .if ModuleInfo.IncludePath == NULL
        lea edi,[ecx+1]
        mov ModuleInfo.IncludePath,MemAlloc(edi)
        mov ecx,edi
        mov edi,eax
        rep movsb
    .else
        mov edi,ecx
        mov esi,ModuleInfo.IncludePath
        strlen(esi)
        mov ModuleInfo.IncludePath,MemAlloc(&[eax+edi+2])
        strcpy(eax, esi)
        strcat(eax, INC_PATH_DELIM_STR)
        strcat(eax, string)
        MemFree(esi)
    .endif
    ret

AddStringToIncludePath endp

;; input buffers
;; 1. src line stack ( default I86: 2*600  = 1200 )
;; 2. tokenarray     ( default I86: 150*12 = 1800 )
;; 3. string buffer  ( default I86: 2*600  = 1200 )

SIZE_SRCLINES     equ ( MAX_LINE_LEN * ( MAX_MACRO_NESTING + 1 ) )
SIZE_TOKENARRAY   equ ( asm_tok * MAX_TOKEN * MAX_MACRO_NESTING )
SIZE_STRINGBUFFER equ ( MAX_LINE_LEN * MAX_MACRO_NESTING )

;; PushInputStatus() is used whenever a macro or generated code is to be "executed".
;; after the macro/code has been assembled, PopInputStatus() is required to restore
;; the saved status.
;; the status information that is saved includes
;; - the source line ( including the comment )
;; - the token buffer
;; - the string buffer (used to store token strings)
;; - field Token_Count
;; - field line_flags

    assume esi:ptr input_status

PushInputStatus proc uses esi oldstat:ptr input_status

    mov esi,oldstat

    mov [esi].token_stringbuf,token_stringbuf
    mov [esi].token_count,Token_Count
    mov [esi].currsource,CurrSource

    ;; if there's a comment, attach it to current source

    .if ModuleInfo.CurrComment
        strlen(CurrSource)
        add eax,CurrSource
        mov [esi].CurrComment,eax
        strcpy(eax, ModuleInfo.CurrComment)
    .else
        mov [esi].CurrComment,NULL
    .endif
    mov [esi].line_flags,ModuleInfo.line_flags ;; v2.08
    mov token_stringbuf,ModuleInfo.stringbufferend
    mov eax,Token_Count
    inc eax
    shl eax,4
    add ModuleInfo.tokenarray,eax
    strlen(CurrSource)
    mov CurrSource,GetAlignedPointer(CurrSource, eax)
    mov eax,ModuleInfo.tokenarray
    ret

PushInputStatus endp

PopInputStatus proc uses esi newstat:ptr input_status

    mov esi,newstat
    mov ModuleInfo.stringbufferend,token_stringbuf
    mov token_stringbuf,[esi].token_stringbuf
    mov Token_Count,[esi].token_count
    mov CurrSource,[esi].currsource
    .if [esi].CurrComment
        mov ModuleInfo.CurrComment,commentbuffer
        strcpy(eax, [esi].CurrComment)
        mov eax,[esi].CurrComment
        mov byte ptr [eax],0
    .else
        mov ModuleInfo.CurrComment,NULL
    .endif
    mov eax,Token_Count
    inc eax
    shl eax,4
    sub ModuleInfo.tokenarray,eax
    mov ModuleInfo.line_flags,[esi].line_flags ;; v2.08
    ret

PopInputStatus endp

AllocInput proc private uses esi edi

    mov  eax,ModuleInfo.max_line_len
    imul esi,eax,MAX_MACRO_NESTING + 1  ; SIZE_SRCLINES
    imul edx,eax,MAX_MACRO_NESTING      ; SIZE_STRINGBUFFER
    shr  eax,2                          ; SIZE_TOKENARRAY
    imul edi,eax,asm_tok * MAX_MACRO_NESTING
    lea  eax,[edi+edx]
    add  eax,esi

    .return .if !LclAlloc( eax )

    mov  srclinebuffer,eax

    ;; the comment buffer is at the end of the source line buffer

    lea ecx,[eax+esi]
    sub ecx,ModuleInfo.max_line_len
    mov commentbuffer,ecx

    ;; behind the comment buffer is the token buffer
    lea ecx,[eax+esi]
    mov ModuleInfo.tokenarray,ecx
    lea eax,[ecx+edi]
    mov ecx,token_stringbuf
    mov token_stringbuf,eax
    sub ModuleInfo.stringbufferend,ecx
    add ModuleInfo.stringbufferend,eax
    ret

AllocInput endp

;; Initializer, called once for each module.

    assume esi:ptr src_item

InputInit proc uses esi

    mov SrcFree,NULL ;; v2.11
if FILESEQ
    mov FileSeq.head,NULL
endif
    mov ModuleInfo.max_line_len,MAX_LINE_LEN

    AllocInput()

    mov esi,PushSrcItem( SIT_FILE, CurrFile[ASM*4] )
    AddFile( CurrFName[ASM*4] )
    mov [esi].srcfile,ax
    mov ModuleInfo.srcfile,eax
    GetFName(eax)
    mov edx,FileCur
    mov [edx].asym.string_ptr,eax
    ret

InputInit endp

;; init for each pass

InputPassInit proc

    mov eax,ModuleInfo.src_stack
    mov [eax].src_item.line_num,0
    mov CurrSource,srclinebuffer
    mov byte ptr [eax],0
    mov ModuleInfo.stringbufferend,token_stringbuf
    ret

InputPassInit endp

    assume esi:ptr line_status

InputExtend proc uses esi edi ebx p:ptr line_status

  .new index:int_t
  .new oldsrcline:ptr
  .new oldstrings:ptr
  .new oldtok:token_t = ModuleInfo.tokenarray
  .new oldsize:uint_t = ModuleInfo.max_line_len

    add ModuleInfo.max_line_len,eax
    mov oldstrings,token_stringbuf
    mov oldsrcline,srclinebuffer

    mov esi,p
    .if ( [esi].start != eax )

        .return .if !LclAlloc( ModuleInfo.max_line_len )

        mov ebx,eax
        mov edx,[esi].start
        sub [esi].input,edx
        add [esi].input,ebx
        mov [esi].start,ebx
        mov ecx,oldsize
        mov edi,ebx
        mov esi,edx
        rep movsb
    .endif

    mov esi,srclinebuffer
    mov ebx,oldsize

    .return .if !AllocInput()
    ;
    ; copy source line buffer, token buffer, and string buffer
    ;
    mov  edi,srclinebuffer
    mov  CurrSource,edi

    imul ecx,ebx,MAX_MACRO_NESTING + 1
    rep  movsb
    mov  edi,ModuleInfo.tokenarray
    mov  eax,ebx
    shr  eax,2
    imul ecx,eax,asm_tok * MAX_MACRO_NESTING
    rep  movsb
    mov  edi,token_stringbuf
    imul ecx,ebx,MAX_MACRO_NESTING
    rep  movsb

    mov esi,p
    mov eax,[esi].outbuf
    .if ( eax == oldstrings )
        sub [esi].output,eax
        mov [esi].outbuf,token_stringbuf
        add [esi].output,eax
    .endif

    mov eax,[esi].start
    .if ( eax == oldsrcline )
        sub [esi].input,eax
        mov [esi].start,srclinebuffer
        add [esi].input,eax
    .endif

    .if ( oldtok == [esi].tokenarray )

        mov edx,ModuleInfo.tokenarray
        mov [esi].tokenarray,edx
        mov index,[esi].index
        mov edi,srclinebuffer
        sub edi,oldsrcline
        mov esi,token_stringbuf
        mov eax,oldstrings
        sub esi,eax
        add ebx,eax
        assume edx:ptr asm_tok
        .for ( ecx = 0 : ecx <= index : ecx++, edx += asm_tok )
            add [edx].tokpos,edi
            .if ( [edx].string_ptr >= eax && [edx].string_ptr <= ebx )
                add [edx].string_ptr,esi
            .endif
        .endf
    .endif
    .return( TRUE )

InputExtend endp

;; release input buffers for a module

InputFini proc

    .if ModuleInfo.IncludePath
        MemFree( ModuleInfo.IncludePath )
    .endif
    ;; free items in ModuleInfo.g.FNames ( and FreeFile, if FASTMEM==0 )
    FreeFiles()
    mov ModuleInfo.tokenarray,NULL
    ret

InputFini endp

    end
