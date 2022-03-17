; MAKE.ASM--
; Copyright (c) 2016 GNU General Public License www.gnu.org/licenses
;
; Change history:
; 2022-03-16 - removed _get_pgmptr() -- Windows XP (xrayer@)
; 2019-11-28 - added %ASMCDIR% if not set
; 2017-04-20 - added line-break '\' for targets
; 2017-02-25 - added switch -I -- include path
; 2017-02-25 - fixed bug in .xxx.obj: only one cmd-line used..
; 2017-02-25 - added .EXTENSIONS and .SUFFIXES
; 2017-02-25 - added include path : %ASMCDIR%\lib | %DZ%\lib
;
include winbase.inc
include stdio.inc
include stdlib.inc
include io.inc
include tchar.inc

__MAKE__        equ 112

LINEBREAKCH     equ 0x5E ; '^'

MAXTARGET       equ 0x10000
MAXTARGETS      equ 100
MAXSYMBOLS      equ 1000
MAXMAKEFILES    equ 7
MAXLINE         equ 512

_T_TARGET       equ 0
_T_METHOD       equ 1
_T_ALL          equ 2

TARGET          STRUC
target          dd ?
string          dd ?
command         dd ?
type            dd ?
prev            dd ?
next            dd ?
srcpath         string_t ?    ; {path}.c.obj:
objpath         string_t ?    ; .c{path}.obj:
TARGET          ENDS
target_t        typedef ptr TARGET

ARGS            STRUC
name            string_t ?
next            ptr_t ?
ARGS            ENDS
args_t          typedef ptr ARGS

    .data

option_a        db 1 ; build all targets (always set)
option_d        db 0 ; debug - echo progress of work
option_h        db 0 ; do not print program header
option_s        db 0 ; silent mode (do not print commands)
option_I        db 0 ; Ignore exit codes from commands

symbol_count    dd 0
symbol_table    dd 0
target_count    dd 0
target_table    dd 0

line_fp         dd MAXMAKEFILES+1 dup(0)
line_buf        db MAXLINE dup(0)
line_ptr        dd line_buf
line_id         dd 0

if_level        db 0
if_state        db 15 dup(0)

linefeed_unix   db 10
null_string     db 0
                align 4
linefeed        dd linefeed_unix

commandfile     db _MAX_PATH dup(0)
responsefile    db _MAX_PATH dup(0)
includepath     db _MAX_PATH dup(0)
currentfile     db _MAX_PATH dup(0)

default_ext     db ".obj",0
                align 4
suffixes        dd default_ext
                dd 32 dup(0)

file_asm        db ".asm",0
file_idd        db ".idd",0
file_c          db ".c",0
                align 4
extensions      dd file_asm
                dd file_idd
                dd file_c
                dd 32 dup(0)
file_args       dd 0 ; ARGS <makefile, 0>
target_args     dd 0
token           dd 0
                db '='
token_equal     db '=',0
ctemp           db '.',0
                align 4
envtemp         dd ctemp
errorlevel      dd 0

_LABEL          equ 0x40 ; _UPPER + _LOWER + '@' + '_' + '$' + '?'
_ltype          db 0
                db 9 dup(_CONTROL)
                db 5 dup(_SPACE+_CONTROL)
                db 18 dup(_CONTROL)
                db _SPACE
                db 3 dup(_PUNCT)
                db _PUNCT+_LABEL
                db 11 dup(_PUNCT)
                db 10 dup(_DIGIT+_HEX)
                db 5 dup(_PUNCT)
                db 2 dup(_PUNCT+_LABEL)
                db 6 dup(_UPPER+_LABEL+_HEX)
                db 20 dup(_UPPER+_LABEL)
                db 4 dup(_PUNCT)
                db _PUNCT+_LABEL
                db _PUNCT
                db 6 dup(_LOWER+_LABEL+_HEX)
                db 20 dup(_LOWER+_LABEL)
                db 4 dup(_PUNCT)
                db _CONTROL     ; 7F (DEL)
                db 257 - ($ - offset _ltype) dup(0)

curr_token      string_t 0

    .code

strstart proc string:string_t

    mov eax,string
    .repeat

        add eax,1
        .continue(0) .if byte ptr [eax-1] == ' '
        .continue(0) .if byte ptr [eax-1] == 9
    .until 1
    sub eax,1
    ret

strstart endp

strspace proc string:string_t

    mov ecx,string

    .repeat
        .repeat
            mov al,[ecx]
            inc ecx
            .if al == ' ' || al == 9
                mov eax,ecx
                dec eax
                movzx ecx,byte ptr [eax]
                .break(1)
            .endif
        .until !al
        dec ecx
        xor eax,eax
    .until 1
    ret

strspace endp

strtrim proc string:string_t

    .if strlen(string)

        mov ecx,eax
        add ecx,string

        .repeat

            dec ecx
            .break .if byte ptr [ecx] > ' '

            mov byte ptr [ecx],0
            dec eax

        .untilz
    .endif
    ret

strtrim endp

strmove proc dst:string_t, src:string_t

    inc strlen(src)
    memmove(dst, src, eax)
    ret

strmove endp

memstri proc uses esi edi ebx s1:string_t, l1:int_t, s2:string_t, l2:int_t

    mov edi,s1
    mov ecx,l1
    mov esi,s2

    mov al,[esi]
    sub al,'A'
    cmp al,'Z'-'A'+1
    sbb bl,bl
    and bl,'a'-'A'
    add bl,al
    add bl,'A'

    .while 1

        .return ecx .if !ecx

        dec ecx
        mov al,[edi]
        add edi,1
        sub al,'A'
        cmp al,'Z'-'A'+1
        sbb bh,bh
        and bh,'a'-'A'
        add al,bh
        add al,'A'
        cmp al,bl

        .continue .if al != bl

        mov edx,l2
        dec edx

        .break .ifz
        .return 0 .ifs ecx < edx

        .repeat

            dec edx
            .break(1) .ifl

            mov al,[esi+edx+1]
            .continue(0) .if al == [edi+edx]

            mov ah,[edi+edx]
            sub ax,'AA'
            cmp al,'Z'-'A' + 1
            sbb bh,bh
            and bh,'a'-'A'
            add al,bh
            cmp ah,'Z'-'A' + 1
            sbb bh,bh
            and bh,'a'-'A'
            add ah,bh
            add ax,'AA'
            cmp al,ah
        .until al != ah
    .endw

    mov eax,edi
    dec eax
    ret

memstri endp

strstri proc uses ebx dst:string_t, src:string_t

    mov ebx,strlen(dst)
    memstri(dst, ebx, src, strlen(src))
    ret

strstri endp

strxchg proc uses esi edi ebx dst:string_t, old:string_t, new:string_t

    mov edi,dst
    mov esi,strlen(new)
    mov ebx,strlen(old)

    .while strstri(edi, old)    ; find token

        mov edi,eax             ; EDI to start of token
        lea ecx,[eax+esi]
        add eax,ebx
        strmove(ecx, eax)       ; move($ + len(new), $ + len(old))
        memmove(edi, new, esi)  ; copy($, new, len(new))
        inc edi                 ; $++
    .endw
    mov eax,dst
    ret

strxchg endp

strfcat proc uses esi edi buffer:string_t, path:string_t, file:string_t

    mov edx,buffer
    mov esi,path
    xor eax,eax
    lea ecx,[eax-1]

    .if esi
        mov edi,esi
        repne scasb
        mov edi,edx
        not ecx
        rep movsb
    .else
        mov edi,edx
        repne scasb
    .endif

    dec edi
    .if edi != edx
        mov al,[edi-1]
        .if !( al == '\' || al == '/' )
            mov al,'\'
            stosb
        .endif
    .endif
    mov esi,file

    .repeat
        lodsb
        stosb
    .until !eax
    mov eax,edx
    ret

strfcat endp

strfn proc path:string_t

    mov ecx,path
    .for ( eax=ecx, dl=[ecx] : dl : ecx++, dl=[ecx] )
        .if ( dl == '\' || dl == '/' )
            .if ( byte ptr [ecx+1] )
                lea eax,[ecx+1]
            .endif
        .endif
    .endf
    ret

strfn endp

strtoken proc string:string_t

    mov eax,string
    mov ecx,curr_token
    .if eax

        mov ecx,eax
        xor eax,eax
    .endif
    .repeat

        mov al,[ecx]
        inc ecx
    .until !(_ltype[eax+1] & _SPACE)

    .repeat

        dec ecx
        mov curr_token,ecx
        .break .if !al

        .repeat
            .repeat
                mov al,[ecx]
                inc ecx
                .break(1) .if !al
            .until _ltype[eax+1] & _SPACE
            mov [ecx-1],ah
            inc ecx
        .until 1
        dec ecx
        mov eax,curr_token
        mov curr_token,ecx
    .until 1
    ret

strtoken endp

strext proc string:string_t

    mov string,strfn(string)

    .if strrchr(eax, '.')

        .if eax == string

            xor eax,eax
        .endif
    .endif
    ret

strext endp

setfext proc path:string_t, ext:string_t

    .if strext(path)

        mov byte ptr [eax],0
    .endif
    strcat(path, ext)
    ret

setfext endp

strpath proc string:string_t

    .if strfn(string) != string

        mov byte ptr [eax-1],0
        mov eax,string
    .endif
    ret

strpath endp

filexist proc file:string_t

    inc GetFileAttributesA(file)
    .ifnz
        dec eax             ; 1 = file
        and eax,_A_SUBDIR   ; 2 = subdir
        shr eax,4
        inc eax
    .endif
    ret

filexist endp

MAXCMDL equ 0x8000

system proc uses edi esi ebx string:LPSTR

  local cmd[_MAX_PATH] : sbyte,
        ProcessInfo    : PROCESS_INFORMATION,
        StartUpInfo    : STARTUPINFO

    mov ebx,strcpy(malloc(MAXCMDL), "cmd.exe")
    .if !GetEnvironmentVariable("Comspec", ebx, MAXCMDL)
        SearchPath(eax, "cmd.exe", eax, MAXCMDL, ebx, eax)
    .endif

    strcat(ebx, " /C ")
    mov edi,string
    mov edx,' '
    .if byte ptr [edi] == '"'
        inc edi
        mov edx,'"'
    .endif
    push edx
    xor esi,esi
    .if strchr( edi, edx )
        mov byte ptr [eax],0
        mov esi,eax
    .endif
    strncpy(&cmd, edi, _MAX_PATH-1)
    pop edx
    .if esi
        mov [esi],dl
        .if dl == '"'
            inc esi
        .endif
    .else
        strlen(string)
        add eax,string
        mov esi,eax
    .endif
    mov edi,esi
    lea esi,cmd
    .if strchr(esi, ' ')
        strcat(strcat(strcat(ebx, "\""), esi), "\"")
    .else
        strcat(ebx, esi)
    .endif
    strcat(ebx, edi)

    xor eax,eax
    mov errorlevel,eax
    lea edi,ProcessInfo
    mov esi,edi
    mov ecx,sizeof(ProcessInfo)
    rep stosb
    lea edi,StartUpInfo
    mov ecx,sizeof(StartUpInfo)
    rep stosb
    lea edi,StartUpInfo
    mov StartUpInfo.cb,STARTUPINFO
    mov edi,CreateProcess(eax, ebx, eax, eax, eax, eax, eax, eax, edi, esi)
    mov esi,ProcessInfo.hProcess
    .if edi
        WaitForSingleObject(esi, INFINITE)
        GetExitCodeProcess(esi, &errorlevel)
        CloseHandle(esi)
        CloseHandle(ProcessInfo.hThread)
    .endif
    free(ebx)
    mov eax,edi
    ret

system endp

expenviron proc uses esi edi string:string_t

    mov esi,malloc(0x8000)
    ExpandEnvironmentStrings(string, esi, 0x8000-1)

    mov edi,esi
    .while strchr(edi, '%')

        mov edi,eax
        .break .if !strchr(&[eax+1], '%')

        strcpy(edi, &[eax+1])
    .endw
    mov edi,strcpy(string, esi)
    free(esi)
    mov eax,edi
    ret

expenviron endp

ltoken proc uses esi edi string:string_t

    mov esi,token
    .if string
        mov esi,string
    .endif

    mov esi,strstart(esi)
    mov token,esi

    xor eax,eax

    .while 1

        lodsb

        .switch

        .case !eax
            lea ecx,[esi-1]
            .break .if ecx == token

            mov eax,token
            mov token,ecx
            .break

        .case eax == '='
            lea ecx,[esi-1]
            lea eax,token_equal
            .if ecx == token
                .if byte ptr [esi] == '='
                    inc esi
                    dec eax
                .endif
                mov token,esi
                .break
            .endif
            dec esi
            mov byte ptr [esi],0
            _strdup(token)
            mov byte ptr [esi],'='
            mov token,esi
            .break

        .case _ltype[eax+1] & _SPACE
            mov eax,token
            mov token,esi
            .break
        .endsw
    .endw
    ret

ltoken endp


istarget proc uses edi ebx line:string_t

    .if !strspace(strstart(line))

        .return( &[eax+1] ) .if byte ptr [ecx-1] == ':'
        mov eax,ecx
    .endif

    mov bl,[eax]
    mov edi,eax

    .return( &[eax+1] ) .if byte ptr [ strstart(eax) ] == ':'

    mov eax,':'
    mov [edi],ah
    strchr(line, eax)

    mov [edi],bl
    .return .if !eax

    movzx eax,byte ptr [eax+1]
    .return( &[eax+1] ) .if !eax

    mov al,_ltype[eax+1]
    and al,_SPACE
    ret

istarget endp


findsymbol proc uses esi edi ebx symbol:string_t

    mov edi,symbol
    mov esi,symbol_table
    mov ebx,symbol_count

    .repeat

        .return ebx .if !ebx

        dec ebx
        mov eax,[esi]
        add esi,4
        mov dx,[eax]
        mov cx,[edi]
        or  dx,0x2020
        or  cx,0x2020
        .continue(0) .if dx != cx

    .until !_stricmp(eax, edi)

    sub esi,4
    mov edx,esi
    mov ecx,[edx]
    mov eax,[edx+MAXSYMBOLS*4]
    ret

findsymbol endp

alloc_string proc uses esi edi value:int_t

    mov edi,malloc(MAXTARGET)
    ExpandEnvironmentStrings(value, edi, MAXTARGET-1)
    mov esi,_strdup(edi)
    free(edi)
    mov eax,esi
    ret

alloc_string endp

addsymbol proc uses edi symbol:string_t, value:int_t

    .repeat

        .if findsymbol(symbol)

            mov edi,edx
            free(eax)
            .return .if !alloc_string(value)

        .else

            mov edi,symbol_table
            mov eax,symbol_count
            .break .if eax >= MAXSYMBOLS-1

            lea edi,[edi+eax*4]
            inc eax
            mov symbol_count,eax
            .break .if !_strdup(symbol)

            mov [edi],eax
            mov eax,value
            .return .if !eax

            .break .if !alloc_string(eax)
        .endif

        mov [edi+MAXSYMBOLS*4],eax
        .return
    .until 1

    perror("To many symbols..")
    exit(1)
    ret

addsymbol endp


expandsymbol proc uses esi edi ebx string:string_t

  local base:string_t
  local symbol_name:string_t
  local symbol_macro:string_t

    mov base,malloc(MAXTARGET)
    mov esi,eax
    add eax,MAXTARGET-256
    mov symbol_name,eax
    add eax,128
    mov symbol_macro,eax
    strcpy(esi, string)
    mov edi,eax
    strtrim(eax)

    .repeat

        .while 1

            .break(1) .if !strchr(edi, '$')
            lea edi,[eax+1]
            .continue(0) .if byte ptr [edi] != '('

            mov edx,symbol_macro
            mov ecx,symbol_name
            mov ebx,eax
            mov ax,[ebx]
            mov [edx],ax
            add ebx,2
            add edx,2

            .repeat

                mov al,[ebx]
                inc ebx
                .continue(0) .if al == ' '
                .continue(0) .if al == 9

                mov [ecx],al
                mov [edx],al
                inc ecx
                inc edx

                .break(1) .if !al

            .until al == ')'

            mov [edx],al
            xor eax,eax
            mov [ecx-1],al
            mov [edx],al

            .if !findsymbol(symbol_name)
                mov eax,offset null_string
            .endif

            strxchg(esi, symbol_macro, eax)
            dec edi
        .endw
        perror(string)
        exit(1)
    .until 1
    mov ebx,_strdup(esi)
    free(esi)
    mov eax,ebx
    ret

expandsymbol endp


;-------------------------------------------------------------------------------
; Read makefile
;-------------------------------------------------------------------------------

skipiftag proc uses esi edi

    lea esi,line_buf
    .repeat

        .if !fgets(esi, MAXLINE, line_fp)

            perror("Missing !else or !endif")
            exit(1)
        .endif

        inc line_id
        .continue(0) .if !strtrim(eax)

        strstart(esi)
        mov edi,eax
        mov eax,[eax]
        .continue(0) .if al != '!'

        inc edi
        strstart(edi)

        mov eax,[eax]
        or  eax,0x20202020

        .if eax == 'esle'

            movzx eax,if_level
            .continue(0) .if if_state[eax-1] == 0

        .elseif eax == 'idne'

            dec if_level
        .else

            .continue(0) .if ax != 'fi'
            movzx eax,if_level
            mov if_state[eax],0
            inc if_level
            skipiftag()
            .continue(0)
        .endif
    .until 1
    ret

skipiftag endp


syntax_error proc syntax:string_t

    perror(syntax)
    exit(1)

syntax_error endp

find_and_compare proc

    .if findsymbol(edi)
        mov edi,eax
    .endif
    .if findsymbol(esi)
        mov esi,eax
    .endif
    _stricmp(edi, esi)
    cmp eax,0
    ret

find_and_compare endp


readline proc uses esi edi ebx

  local base:string_t
  local symbol:string_t

    mov base,malloc(MAXTARGET)
    add eax,MAXTARGET-256
    mov symbol,eax

    .while 1

        mov eax,line_fp
        .break .if !eax

        mov esi,line_ptr
        mov edi,esi

        .if !fgets(edi, MAXLINE, eax)

            fclose(line_fp)
            lea edx,line_fp
            memcpy(edx, addr [edx+4], MAXMAKEFILES*4)
            .continue
        .endif

        inc line_id
        .continue .if !strtrim(eax)


        mov edi,strstart(esi)         ; EDI to start of line
        mov esi,ltoken(strcpy(base, eax)) ; ESI to first token
        mov eax,[edi]
        .continue .if al == '#'

        .if al != '!'

            mov eax,edi
            .break
        .endif

        mov edi,expandsymbol(&[edi+1])
        strcpy(base, edi)
        mov edi,strstart(edi)

        .switch

        .case !_strnicmp(edi, "include", 7)

            mov ebx,expandsymbol(strstart(addr [edi+8]))
            .if !fopen(eax, "rt") && includepath

                fopen(strfcat(addr currentfile, addr includepath, ebx), "rt")
            .endif
            xchg ebx,eax
            free(eax)
            .if !ebx

                perror(edi)
                exit(1)
            .endif
            lea edi,line_fp
            memmove(addr [edi+4], edi, MAXMAKEFILES*4-4)
            mov [edi],ebx
            .continue

        .case !_strnicmp(edi, "endif", 5)

            dec if_level
            .continue

        .case !_strnicmp(edi, "else", 4)

            movzx ebx,if_level
            .if if_state[ebx-1] == 0

                skipiftag()
            .endif
            .continue
        .endsw

        mov ax,[edi]
        or  ax,0x2020
        .if ax != 'fi'

            syntax_error(edi)
        .endif

        movzx ebx,if_level
        mov if_state[ebx],1
        inc if_level

        .if !_strnicmp(edi, "ifdef", 5)

            .if ltoken(addr [edi+6])

                .if !findsymbol(eax)

                    skipiftag()
                .else
                    mov if_state[ebx],0
                .endif
                .continue
            .endif

            syntax_error(edi)
        .endif

        .if !_strnicmp(edi,"ifndef", 6)

            .if !ltoken(addr [edi+7])

                syntax_error(edi)
            .endif
            .if findsymbol(eax)

                skipiftag()
            .else
                mov if_state[ebx],0
            .endif
            .continue
        .endif

        .if !_strnicmp(edi, "ifeq", 4)

            mov edi,expenviron(edi)

            .return syntax_error(edi) .if strtoken(&[edi+5]) == NULL
            mov edi,eax
            .return syntax_error(edi) .if strtoken(0) == NULL
            mov esi,eax
            jmp if_a_eq_b
        .endif

        mov al,[edi+2]
        .if al != ' ' && al != 9
            syntax_error(edi)
        .endif
        .if !strtoken(&[edi+3])
            syntax_error(edi)
        .endif

        mov edi,expenviron(eax)

        .while 1 ; !if <> == <> || <> ..

            .if !strtoken(0)

                .if !findsymbol(edi)
                    mov eax,edi
                .endif
                .if byte ptr [eax] != '0'
                    mov if_state[ebx],0
                .else
                    skipiftag()
                .endif
                .break
            .endif

            mov esi,eax
            .if !strtoken(0)
                syntax_error(edi)
            .endif

            xchg esi,eax
            mov eax,[eax]
            .if al < 2
                syntax_error(edi)
            .endif

            .switch al

            .case TRUE

                .if strtoken(0) == NULL || byte ptr [eax] == '|'

                    mov if_state[ebx],0

                .elseif byte ptr [eax] == '&'

                    .return syntax_error(edi) .if !strtoken(0)
                    mov edi,eax
                    .continue
                .endif
                .break

            .case FALSE

                .if strtoken(0) == NULL || byte ptr [eax] != '|'

                    skipiftag()
                    .break
                .endif
                .return syntax_error(edi) .if !strtoken(0)

                mov edi,eax
                .continue

            .case <if_a_eq_b> '='

                find_and_compare()

                .gotosw(TRUE) .ifz
                .gotosw(FALSE)

            .case '<'

                find_and_compare()

                .gotosw(TRUE) .ifl
                .gotosw(FALSE)

            .case '>'

                find_and_compare()

                .gotosw(TRUE) .ifg
                .gotosw(FALSE)

            .case '&'

                .gotosw(FALSE) .if !findsymbol(edi) || byte ptr [eax] == '0'
                .gotosw(FALSE) .if !findsymbol(esi) || byte ptr [eax] == '0'
                .gotosw(TRUE)

            .case '|'

                .gotosw(FALSE) .if !findsymbol(edi)
                .gotosw(TRUE)  .if byte ptr [eax] != '0'
                .gotosw(FALSE) .if !findsymbol(esi) || byte ptr [eax] == '0'
                .gotosw(TRUE)

            .default

                syntax_error(edi)
            .endsw
        .endw
    .endw
    mov edi,eax
    free(base)
    mov eax,edi
    ret

readline endp


issymbol proc uses esi line:string_t

    .if strchr(line, '=')

        mov esi,eax
        mov byte ptr [eax],0
        strspace(line)
        mov byte ptr [esi],'='
        .if eax
            .if strstart(eax) != esi
                mov ax,[eax]
                .if ax != '=+'
                    xor esi,esi
                .endif
            .endif
        .endif
        mov eax,esi
    .endif
    ret

issymbol endp


getline proc uses esi edi ebx

  local base:string_t
  local symbol:string_t

    mov base,malloc(MAXTARGET)
    add eax,MAXTARGET-256
    mov symbol,eax

    .while 1

        .break .if !readline()

        mov edi,eax ; EDI to start of line
        mov eax,[edi]

        .if al == '.'

            .switch
            .case !_strnicmp(edi, ".DEFAULT", 8)    ; define default rule to build target
            .case !_strnicmp(edi, ".DONE", 5)       ; target to build, after all other targets are build
            .case !_strnicmp(edi, ".IGNORE", 7)     ; ignore all error codes during building of targets
            .case !_strnicmp(edi, ".INIT", 5)       ; first target to build, before any target is build
                .continue
            .case !_strnicmp(edi, ".SILENT", 7)
                inc option_s        ; do not echo commands
                .continue
            .case !_strnicmp(edi, ".RESPONSE", 9)
                .continue           ; define a response file for long ( > 128) command lines
            .case !_strnicmp(edi, ".EXTENSIONS", 11)
                strtoken(edi)       ; add extensions to the suffixes list
                lea esi,extensions
                .while eax
                    lodsd
                .endw
                .while strtoken(0)
                    .break .if byte ptr [eax] != '.'
                    mov [esi-4],_strdup(eax)
                    add esi,4
                .endw
                .continue
            .case !_strnicmp(edi, ".SUFFIXES", 9)
                strtoken(edi)       ; the suffixes list for selecting implicit rules
                .if !strtoken(0)
                    push edi
                    lea edi,suffixes
                    xor eax,eax
                    mov ecx,32
                    rep stosd
                    pop edi
                    .continue
                .endif
                lea esi,suffixes
                mov edx,eax
                .while eax
                    lodsd
                .endw
                mov eax,edx
                .while eax
                    .break .if byte ptr [eax] != '.'
                    mov [esi-4],_strdup(eax)
                    add esi,4
                    strtoken(0)
                .endw
                .continue
            .endsw
            mov eax,edi
            .break
        .endif

        .if issymbol(edi)

            mov edx,base
            xor ecx,ecx
            mov [edx],cl
            mov [eax],cl
            lea esi,[eax+1]

            .if byte ptr [eax-1] == '+' ; case '+='

                mov [eax-1],cl
                strtrim(edi)

                .if findsymbol(edi)

                    strcat(strcpy(base, eax), " ")
                .endif
            .endif

            strtrim(edi)
            strcpy(symbol, edi)
            strtoken(esi)

            mov esi,base
            .while eax

                .while 1

                    mov cx,[eax]

                    .break .if cx == '\'
                    .break .if cx == '&'

                    strcat(esi, eax)
                    strcat(esi, " ")

                    .break(1) .if !strtoken(0)

                .endw

                .break .if !readline()
                strtoken(eax)

            .endw

            strtrim(esi)
            addsymbol(symbol, esi)
            .continue

        .endif

        mov eax,edi
        .break
    .endw
    mov edi,eax
    free(base)
    mov eax,edi
    ret

getline endp


addtarget proc uses esi edi ebx target:string_t

  local base:string_t
  local target_name:string_t
  local target_string:string_t
  local target_command:string_t
  local target_srcpath:string_t

    mov base,malloc(MAXTARGET)
    mov edi,eax
    mov esi,target
    strtrim(esi)
    mov byte ptr [edi],0

    .while byte ptr [esi+eax-1] == '\'

        mov byte ptr [esi+eax-1],0
        strcat(edi, esi)
        mov byte ptr [esi],0
        .break .if !fgets(esi, MAXLINE, line_fp)
        inc line_id
        .break .if !strtrim(esi)
    .endw
    strcat(edi, esi)
    mov esi,edi

    .repeat

        .if !_strdup(strstart(edi))

            perror("To many targets..")
            exit(1)
        .endif
        mov target_string,eax

        ltoken(edi)
        .if !strrchr(edi, ':')

            perror(esi)
            exit(1)
        .endif

        mov byte ptr [eax],0
        strtrim(edi)

        mov target_name,expandsymbol(edi)
        mov esi,line_ptr
        xor eax,eax
        mov target_srcpath,eax
        mov target_command,eax

        mov [esi],al
        mov ah,[edi]
        mov [edi],al

        .if ah == '{'

            mov ebx,target_name

            .if strchr(ebx, '}')

                mov byte ptr [eax],0
                lea edx,[eax+1]
                push edx
                .if !_strdup(addr [ebx+1])

                    perror("To many targets..")
                    exit(1)
                .endif
                pop edx
                mov target_srcpath,eax
                strcpy(ebx, strstart(edx))
            .endif
        .endif

        .while getline()

            .break .if istarget(esi)
            strcat(edi, strstart(esi))
            strcat(edi, linefeed)
        .endw
        .if !eax

            mov [esi],al
        .endif

        .if byte ptr [edi]

            .if !_strdup(edi)

                perror("To many targets..")
                exit(1)
            .endif
            mov target_command,eax
        .endif

        .if !malloc(TARGET)

            perror("To many targets..")
            exit(1)
        .endif

        mov ebx,eax
        assume ebx:target_t

        mov [ebx].next,target_table
        mov [ebx].prev,0
        .if eax
            mov [eax].TARGET.prev,ebx
        .endif

        mov [ebx].target, target_name
        mov [ebx].string, target_string
        mov [ebx].command,target_command
        mov [ebx].srcpath,target_srcpath
        inc target_count
        mov target_table,ebx

        .if !_stricmp(target_name, "all")

            mov [ebx].type,_T_ALL
            .break
        .endif

        mov [ebx].TARGET.type,_T_TARGET
        mov eax,target_name
        .break .if byte ptr [eax] != '.'

        inc  eax
        push esi
        lea  esi,suffixes
        mov  edi,eax
        lodsd
        .while eax
            .break .if strstri(edi, eax)
            lodsd
        .endw
        pop esi

        .break .if !eax
        mov [ebx].type,_T_METHOD

    .until 1

    assume ebx:nothing

    .if istarget(esi)
        addtarget(esi)
    .endif
    free(base)
    ret

addtarget endp


;-------------------------------------------------------------------------------
; Build target
;-------------------------------------------------------------------------------

findtarget proc uses esi edi ebx target:string_t

    mov edi,expandsymbol(target)
    mov esi,target_table
    xor ebx,ebx
    .repeat
        mov ebx,esi
        .break .if !esi
        mov eax,[esi].TARGET.target
        mov esi,[esi].TARGET.next
        mov dx,[eax]
        or  dx,0x2020
        mov cx,[edi]
        or  cx,0x2020
        .continue(0) .if dx != cx
        .break .if !_stricmp(eax, edi)
        xor ebx,ebx
    .until !esi

    free(edi)
    mov eax,ebx
    ret

findtarget endp


build_object proc uses esi edi ebx object:string_t

  local srcname[_MAX_PATH]:byte
  local srcfile[_MAX_PATH]:byte
  local command[_MAX_PATH]:byte
  local p:string_t,q:string_t,r:string_t

    lea ebx,srcname
    lea edi,srcfile
    lea esi,extensions
    .if strext(strcpy(ebx, object))

        mov byte ptr [eax],0
    .endif

    lea ebx,suffixes

    .repeat

        mov eax,[ebx]
        .if !eax
            perror(&srcname)
            exit(1)
        .endif

        mov p,eax
        add ebx,4
        lea esi,extensions

        .repeat

            lodsd
            .continue(01) .if !eax
            mov q,eax

            .continue(0) .if !findtarget(strcat(strcpy(edi, eax), p))

            push eax
            strcat(strcpy(edi, &srcname), q)
            pop  edx
            mov  ecx,[edx].TARGET.srcpath
            push edx

            .if ecx

                strcpy(edi, strfcat(&command, ecx, edi))
            .endif

            filexist(eax)

            pop edx
            dec eax

        .untilz
    .until 1

    lea ebx,srcname
    lea esi,command
    mov eax,[edx].TARGET.command
    .if eax == NULL
        perror(edi)
        exit(1)
    .endif

    strxchg(strcpy(esi, eax), "$*", ebx)
    strxchg(esi, "$<", edi)

    setfext(edi, suffixes)
    strxchg(esi, "$@", edi)

    mov esi,expandsymbol(esi)

    .if option_d

        printf("%s\n", esi)

    .else

        .while strchr(esi, 10)

            lea ebx,[eax+1]
            mov byte ptr [eax],0
            .if !option_s

                printf("\t%s\n", esi)
            .endif

            system(esi)
            mov byte ptr [ebx-1],10
            mov esi,ebx
        .endw

        .if !option_s

            printf("\t%s\n", esi)
        .endif

        system(esi)
        dec eax
        .if eax || eax != errorlevel
            .if ( !option_I )
                perror(edi)
                exit(1)
            .endif
        .endif
    .endif
    ret

build_object endp


opentemp proc buffer:string_t, ext:string_t

  local t:SYSTEMTIME

    GetLocalTime(&t)
    GetTickCount()
    movzx ecx,t.wMilliseconds
    add eax,ecx
    and eax,0x00FFFFFF
    sprintf(buffer, "%s\\$%06X$.%s", envtemp, eax, ext)
    fopen(buffer, "wt+")
    ret

opentemp endp


build_target proc uses esi edi ebx target:target_t

  local base:string_t,
        target_path:string_t,
        target_name:string_t,
        target_file:string_t,
        target_command:string_t,
        target_string:string_t

    mov base,malloc(MAXTARGET)
    mov edi,eax
    mov esi,target
    mov esi,expandsymbol([esi].TARGET.string)
    mov target_string,eax

    .while 1

        lodsb
        stosb

        .break .if !al
        .break .if al == ':' && byte ptr [esi] != '\'
    .endw

    mov byte ptr [edi],0
    mov edi,base
    _strdup(edi)
    mov target_path,eax
    _strdup(eax)
    mov target_name,eax
    mov ebx,eax
    .if strrchr(eax, ':')
        mov byte ptr [eax],0
    .endif

    strtrim(ebx)
    _strdup(strfn(ebx))
    mov target_file,eax
    .if strext(eax)
        mov byte ptr [eax],0
    .endif

    .while 1

        mov ax,[esi-1]
        .break .if al == 0
        .break .if ah == 0

        .repeat
            lodsb
        .until al != ' ' && al != 9
        .while 1
            stosb
            .break .if !al || al == ' ' || al == 9
            lodsb
        .endw
        mov byte ptr [edi],0

        mov edi,base
        .if findtarget(edi)
            .return .if build_target(eax)
        .else
            build_object(edi)
        .endif
    .endw

    free(target_string)
    mov esi,target
    mov eax,[esi].TARGET.command

    .return .if !eax ; all: <target1> [<target2>] ... or <no command>

    mov esi,expandsymbol(eax)
    mov edi,strcpy(base, eax)
    free(esi)
    strxchg(edi, "$@", target_name)
    strxchg(edi, "$*", target_file)

    mov esi,edi

    .repeat

        .break .if !strstr(esi, "@<<")

        lea ebx,[eax+3]
        mov byte ptr [ebx-2],0
        .if !strchr(ebx, 10)
            perror("Make execution terminated")
            exit(1)
        .endif

        lea ebx,[eax+1]
        .break .if !strstr(ebx, "<<")

        mov byte ptr [eax],0
        lea edi,[eax+2]
        .if !opentemp(&responsefile, "$$$")
            perror("Make execution terminated")
            exit(1)
        .endif

        push eax
        fprintf(eax, ebx)
        pop eax
        fclose(eax)

        .if option_d

            printf("%s:\n%s\n", addr responsefile, ebx)
        .endif
        strcat(esi, addr responsefile)
        .break .if !strchr(edi, 10)
        strcat(esi, eax)
    .until 1

    .if option_d

        printf("%s\n", esi)
        xor eax,eax
    .else
        .if !option_s

            mov edi,esi
            printf("%s\n", target_path)

            .while strchr(edi, 10)

                lea ebx,[eax+1]
                mov byte ptr [eax],0
                printf("\t%s\n", edi)
                mov byte ptr [ebx-1],10
                mov edi,ebx
            .endw
            printf("\t%s\n", edi)
        .endif

        xor edi,edi
        .if opentemp(&commandfile, "cmd")
            mov ebx,eax
            fprintf(eax, "@echo off\n%s\n", esi)
            fclose(ebx)
            dec system(&commandfile)
            add edi,eax
            add edi,errorlevel
        .endif
        remove(&responsefile)
        remove(&commandfile)
        .if ( edi && !option_I )
            perror("Make execution terminated")
            exit(1)
        .endif
    .endif
    mov edi,eax
    free(base)
    mov eax,edi
    ret

build_target endp


;-------------------------------------------------------------------------------
; MAKE
;-------------------------------------------------------------------------------

addtargetarg proc uses ebx target:string_t

    .if strlen(target)

        .if malloc(&[eax+1+ARGS])

            mov ebx,eax
            mov [ebx].ARGS.name,strcpy(&[ebx+ARGS], target)
            xor eax,eax
            mov [ebx].ARGS.next,eax

            mov ecx,target_args
            .if ecx == 0

                mov target_args,ebx

            .else

                .while eax != [ecx].ARGS.next

                    mov ecx,[ecx].ARGS.next
                .endw
                mov [ecx].ARGS.next,ebx
            .endif
        .endif
    .endif
    ret

addtargetarg endp


make proc uses esi edi ebx file:string_t, target:string_t


    .if !fopen(file, "rt")

        perror(file)
        exit(1)
    .endif

    mov line_fp,eax

    .while getline()

        mov esi,eax
        .break .if !istarget(esi)

        addtarget(esi)
    .endw

    mov esi,target_args

    .if !esi

        .if !target_count

            perror("Missing target..")
            exit(1)
        .endif

        .for eax = 0,
             ebx = 0,
             edi = 0,
             ecx = target_table : [ecx].TARGET.next : ecx = [ecx].TARGET.next
        .endf

        .for : ecx && !eax : ecx = [ecx].TARGET.prev

            mov edi,ecx
            mov eax,[ecx].TARGET.type

            .break .if eax == _T_ALL

            .if eax == _T_METHOD
                mov ebx,ecx
                xor eax,eax
            .else
                mov eax,[ecx].TARGET.command
            .endif
        .endf

        .if  !eax && !ebx

            perror([edi].TARGET.target)
            exit(1)
        .endif

        addtargetarg([edi].TARGET.target)

        mov esi,target_args
    .endif


    .for : esi: esi = [esi].ARGS.next

        .break .if !findtarget([esi].ARGS.name)

        build_target(eax)
    .endf
    ret

make endp


;-------------------------------------------------------------------------------
; MAIN
;-------------------------------------------------------------------------------

AddMakefile proc uses ebx file:string_t

    .if strlen(file)

        .if malloc(&[eax+1+ARGS])

            mov ebx,eax
            strcpy(&[ebx+ARGS], file)
            mov [ebx].ARGS.name,eax

            xor eax,eax
            mov [ebx].ARGS.next,eax
            mov ecx,file_args

            .if !ecx

                mov file_args,ebx
            .else
                .while eax != [ecx].ARGS.next

                    mov ecx,[ecx].ARGS.next
                .endw
                mov [ecx].ARGS.next,ebx
            .endif
        .endif
    .endif
    ret

AddMakefile endp


print_copyright proc
    printf(
        "Asmc Program Maintenance Utility Version %d.%d.%d.%d\n",
        __MAKE__ / 100, __MAKE__ mod 100,
        __ASMC__ / 100, __ASMC__ mod 100
    )
    ret
print_copyright endp


; Create vars32.bat and vars64.bat

install proc uses esi edi ebx

  local base[_MAX_PATH]:char_t
  local path[_MAX_PATH]:char_t

    lea esi,base
    lea edi,path

    GetModuleFileNameA(0, esi, _MAX_PATH)
    strpath(strpath(esi))
    .return .if !fopen(strfcat(edi, esi, "bin\\envars32.bat"), "wt")
    mov ebx,eax
    fprintf(eax,
        "@echo off\n"
        "set AsmcDir=%s\n"
        "set PATH=%s\\bin;%%PATH%%\n"
        "set INCLUDE=%s\\include;%%INCLUDE%%\n", esi, esi, esi)
    fprintf(ebx, "set LIB=%s\\lib\\x86;%%LIB%%\n", esi)
    fclose(ebx)
    .return .if !fopen(strfcat(edi, esi, "bin\\envars64.bat"), "wt")
    mov ebx,eax
    fprintf(eax,
        "@echo off\n"
        "set AsmcDir=%s\n"
        "set PATH=%s\\bin;%%PATH%%\n"
        "set INCLUDE=%s\\include;%%INCLUDE%%\n", esi, esi, esi)
    fprintf(ebx, "set LIB=%s\\lib\\x64;%%LIB%%\n", esi)
    fclose(ebx)
    ret

install endp

main proc argc:int_t, argv:array_t

    .if getenv("TEMP")

        mov envtemp,eax ; default to .
    .endif

    mov symbol_table,malloc(MAXSYMBOLS*4*2)

    .if !getenv("ASMCDIR")

        mov ecx,argv
        mov eax,[ecx]
        strcpy(&line_buf, eax)
        strpath(eax)
        strpath(eax)
        SetEnvironmentVariable("ASMCDIR", eax)
        lea eax,line_buf
    .endif

    strcpy(&includepath, eax)
    strcat(eax, "\\lib")


    .for esi = argv, edi = argc : edi > 1 :

        dec edi
        add esi,4
        mov ebx,[esi]
        mov eax,[ebx]

        .switch al

        .case '/'
        .case '-'

            shr eax,8

            .switch al

            .case 'a': inc option_a: .endc
            .case 'd': inc option_d: .endc
            .case 'h': inc option_h: .endc
            .case 's': inc option_s: .endc
            .case 'I'
                .if ( byte ptr [ebx+2] == 0 )
                    inc option_I
                .else
                    strcpy(&includepath, &[ebx+2])
                .endif
                .endc

            .case 'f'
                add ebx,2
                .if eax & 0xFF00
                    AddMakefile(ebx)
                    .endc
                .endif
                add esi,4
                mov edx,[esi]
                AddMakefile(edx)
                dec edi
                .break .ifz
                .endc

            .case 'i'
                .if eax == 'sni'

                    install()
                    .return 0
                .endif

            .default
                print_copyright()
                printf(
                    "Usage: MAKE [-/options] [macro=text] [target(s)]\n"
                    " Options:\n"
                    "  -a       Build all targets (always set)\n"
                    "  -d       Debug - echo progress of work\n"
                    "  -f#      Full pathname of make file\n"
                    "  -h       Do not print program header\n"
                    "  -I       Ignore exit codes from commands\n"
                    "  -I#      Set include path\n"
                    "  -s       Suppress executed-commands display\n\n"
                )
                .return 0
            .endsw
            .endc

          .default
            .if strchr(ebx, '=')
                mov byte ptr [eax],0
                inc eax
                addsymbol(ebx, eax)
            .else
                addtargetarg(ebx)
            .endif
        .endsw
    .endf

    .if !option_h && !option_s

        print_copyright()
    .endif

    mov esi,file_args

    .if !esi

        AddMakefile("makefile")
        mov esi,file_args
    .endif

    .while esi

        .break .if make([esi].ARGS.name, target_args)
        mov esi,[esi].ARGS.next
    .endw
    ret

main endp

    end _tstart
