; MAKE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Change history:
; 2024-03-30 - added 64-bit support
; 2024-01-29 - allow if/else syntax without the ! prefix
;            - added $(error text...)
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
define LTYPE_INLINE
include ltype.inc

define __MAKE__        201

define LINEBREAKCH     0x5E ; '^'

define MAXTARGET       0x10000
define MAXTARGETS      100
define MAXSYMBOLS      1000
define MAXMAKEFILES    7
define MAXLINE         512

.enum TargetType { T_TARGET, T_METHOD, T_ALL }

target_t        typedef ptr TARGET
TARGET          STRUC
target          string_t ?
string          string_t ?
command         string_t ?
type            TargetType ?
prev            target_t ?
next            target_t ?
srcpath         string_t ?    ; {path}.c.obj:
objpath         string_t ?    ; .c{path}.obj:
TARGET          ENDS

args_t          typedef ptr ARGS
ARGS            STRUC
name            string_t ?
next            args_t ?
ARGS            ENDS

.data

option_a        db 1 ; build all targets (always set)
option_d        db 0 ; debug - echo progress of work
option_h        db 0 ; do not print program header
option_s        db 0 ; silent mode (do not print commands)
option_I        db 0 ; Ignore exit codes from commands

                align size_t
symbol_count    int_t 0
target_count    int_t 0
symbol_table    array_t 0
target_table    target_t 0

line_fp         LPFILE MAXMAKEFILES+1 dup(0)
line_buf        db MAXLINE dup(0)
line_ptr        string_t line_buf
line_id         int_t 0

if_level        db 0
if_state        db 15 dup(0)

linefeed_unix   db 10
null_string     db 0
                align size_t
linefeed        string_t linefeed_unix

commandfile     db _MAX_PATH dup(0)
responsefile    db _MAX_PATH dup(0)
includepath     db _MAX_PATH dup(0)
currentfile     db _MAX_PATH dup(0)

default_ext     db ".obj",0
                align size_t
suffixes        string_t default_ext
                string_t 32 dup(0)

file_asm        db ".asm",0
file_idd        db ".idd",0
file_c          db ".c",0
                align size_t
extensions      string_t file_asm
                string_t file_idd
                string_t file_c
                string_t 32 dup(0)
file_args       args_t 0 ; ARGS <makefile, 0>
target_args     args_t 0
token           string_t 0
                db '='
token_equal     db '=',0
ctemp           db '.',0
                align size_t
envtemp         string_t ctemp
curr_token      string_t 0
errorlevel      int_t 0

    .code

strstart proc string:string_t

    ldr rax,string

    .while ( byte ptr [rax] == ' ' || byte ptr [rax] == 9 )
        inc rax
    .endw
    ret

strstart endp


strspace proc string:string_t

    ldr rcx,string

    .repeat
        mov al,[rcx]
        inc rcx
        .if ( al == ' ' || al == 9 )

            lea rax,[rcx-1]
            movzx ecx,byte ptr [rax]
           .return
        .endif
    .until !al
    dec rcx
    xor eax,eax
    ret

strspace endp


strtrim proc string:string_t

    .if strlen(string)

        mov ecx,eax
        add rcx,string
        .repeat

            dec rcx
            .break .if byte ptr [rcx] > ' '

            mov byte ptr [rcx],0
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


memstri proc uses rsi rdi rbx s1:string_t, l1:int_t, s2:string_t, l2:int_t

    ldr rdi,s1
    ldr ecx,l1
    ldr rsi,s2

    mov al,[rsi]
    sub al,'A'
    cmp al,'Z'-'A'+1
    sbb bl,bl
    and bl,'a'-'A'
    add bl,al
    add bl,'A'

    .while 1

        .return ecx .if !ecx

        dec ecx
        mov al,[rdi]
        inc rdi
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

            mov al,[rsi+rdx+1]
            .continue(0) .if al == [rdi+rdx]

            mov ah,[rdi+rdx]
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

    mov rax,rdi
    dec rax
    ret

memstri endp


strstri proc uses rbx dst:string_t, src:string_t

    mov ebx,strlen(dst)
    memstri(dst, ebx, src, strlen(src))
    ret

strstri endp


strxchg proc uses rsi rdi rbx dst:string_t, old:string_t, new:string_t

    ldr rdi,dst
    mov esi,strlen(new)
    mov ebx,strlen(old)

    .while strstri(rdi, old)    ; find token

        mov rdi,rax             ; EDI to start of token
        lea rcx,[rax+rsi]
        add rax,rbx
        strmove(rcx, rax)       ; move($ + len(new), $ + len(old))
        memmove(rdi, new, esi)  ; copy($, new, len(new))
        inc rdi                 ; $++
    .endw
    mov rax,dst
    ret

strxchg endp


strfcat proc uses rsi rdi buffer:string_t, path:string_t, file:string_t

    mov rdx,buffer
    mov rsi,path
    xor eax,eax
    mov ecx,-1

    .if rsi
        mov rdi,rsi
        repne scasb
        mov rdi,rdx
        not ecx
        rep movsb
    .else
        mov rdi,rdx
        repne scasb
    .endif

    dec rdi
    .if rdi != rdx
        mov al,[rdi-1]
        .if !( al == '\' || al == '/' )
            mov al,'\'
            stosb
        .endif
    .endif
    mov rsi,file

    .repeat
        lodsb
        stosb
    .until !eax
    mov rax,rdx
    ret

strfcat endp


strfn proc path:string_t

    ldr rcx,path
    .for ( rax = rcx, dl = [rcx] : dl : rcx++, dl=[rcx] )

        .if ( dl == '\' || dl == '/' )

            .if ( byte ptr [rcx+1] )

                lea rax,[rcx+1]
            .endif
        .endif
    .endf
    ret

strfn endp


strtoken proc string:string_t

    ldr rax,string
    mov rcx,curr_token
    .if rax

        mov rcx,rax
        xor eax,eax
    .endif
    .while islspace([rcx])
        inc rcx
    .endw
    mov curr_token,rcx
    .if ( eax == 0 )
        .return
    .endif
    .while 1

        .if islspace([rcx])

            mov [rcx],ah
            inc rcx
           .break
        .endif
        .break .if !eax
        inc rcx
    .endw
    mov rax,curr_token
    mov curr_token,rcx
    ret

strtoken endp


strext proc uses rbx string:string_t

    ldr rbx,string
    mov rbx,strfn(rbx)
    .if strrchr(rax, '.')
        .if rax == rbx
            xor eax,eax
        .endif
    .endif
    ret

strext endp


setfext proc path:string_t, ext:string_t

    .if strext(path)
        mov byte ptr [rax],0
    .endif
    strcat(path, ext)
    ret

setfext endp


strpath proc uses rbx string:string_t

    ldr rbx,string
    .if strfn(rbx) != rbx

        mov byte ptr [rax-1],0
        mov rax,rbx
    .endif
    ret

strpath endp


filexist proc file:string_t

    .ifd ( GetFileAttributes(file) == -1 )
        .return( 0 )
    .endif
    and eax,_A_SUBDIR   ; 1 = file
    shr eax,4           ; 2 = subdir
    inc eax
    ret

filexist endp


MAXCMDL equ 0x8000

system proc uses rdi rsi rbx string:LPSTR

  local cmd[_MAX_PATH] : sbyte,
        ProcessInfo    : PROCESS_INFORMATION,
        StartUpInfo    : STARTUPINFO,
        quote          : int_t

    mov rbx,strcpy(malloc(MAXCMDL), "cmd.exe")
    .if !GetEnvironmentVariable("Comspec", rbx, MAXCMDL)
        SearchPath(rax, "cmd.exe", rax, MAXCMDL, rbx, rax)
    .endif

    strcat(rbx, " /C ")
    mov rdi,string
    mov edx,' '
    .if byte ptr [rdi] == '"'
        inc rdi
        mov edx,'"'
    .endif
    mov quote,edx
    xor esi,esi
    .if strchr( rdi, edx )
        mov byte ptr [rax],0
        mov rsi,rax
    .endif
    strncpy(&cmd, rdi, _MAX_PATH-1)
    mov edx,quote
    .if rsi
        mov [rsi],dl
        .if dl == '"'
            inc rsi
        .endif
    .else
        strlen(string)
        add rax,string
        mov rsi,rax
    .endif
    mov rdi,rsi
    lea rsi,cmd
    .if strchr(rsi, ' ')
        strcat(strcat(strcat(rbx, "\""), rsi), "\"")
    .else
        strcat(rbx, rsi)
    .endif
    strcat(rbx, rdi)

    xor eax,eax
    mov errorlevel,eax
    lea rdi,ProcessInfo
    mov rsi,rdi
    mov ecx,sizeof(ProcessInfo)
    rep stosb
    lea rdi,StartUpInfo
    mov ecx,sizeof(StartUpInfo)
    rep stosb
    lea rdi,StartUpInfo
    mov StartUpInfo.cb,STARTUPINFO
    mov edi,CreateProcess(rax, rbx, rax, rax, eax, eax, rax, rax, rdi, rsi)
    mov rsi,ProcessInfo.hProcess
    .if edi
        WaitForSingleObject(rsi, INFINITE)
        GetExitCodeProcess(rsi, &errorlevel)
        CloseHandle(rsi)
        CloseHandle(ProcessInfo.hThread)
    .endif
    free(rbx)
    mov eax,edi
    ret

system endp


expenviron proc uses rsi rdi string:string_t

    mov rsi,malloc(0x8000)
    ExpandEnvironmentStrings(string, rsi, 0x8000-1)

    mov rdi,rsi
    .while strchr(rdi, '%')

        mov rdi,rax
        .break .if !strchr(&[rax+1], '%')

        strcpy(rdi, &[rax+1])
    .endw
    mov rdi,strcpy(string, rsi)
    free(rsi)
    mov rax,rdi
    ret

expenviron endp


ltoken proc uses rsi rdi string:string_t

    ldr rcx,string
    mov rsi,token
    .if rcx
        mov rsi,rcx
    .endif

    mov rsi,strstart(rsi)
    mov token,rsi

    xor eax,eax

    .while 1

        lodsb

        .switch

        .case !eax
            lea rcx,[rsi-1]
           .break .if rcx == token

            mov rax,token
            mov token,rcx
           .break

        .case eax == '='
            lea rcx,[rsi-1]
            lea rax,token_equal
            .if rcx == token
                .if byte ptr [rsi] == '='
                    inc rsi
                    dec rax
                .endif
                mov token,rsi
               .break
            .endif
            dec rsi
            mov byte ptr [rsi],0
            _strdup(token)
            mov byte ptr [rsi],'='
            mov token,rsi
           .break

        .case islspace(eax)
            mov rax,token
            mov token,rsi
           .break
        .endsw
    .endw
    ret

ltoken endp


istarget proc uses rdi rbx line:string_t

    .if !strspace(strstart(line))

        .return( 1 ) .if byte ptr [rcx-1] == ':'
        mov rax,rcx
    .endif

    mov bl,[rax]
    mov rdi,rax

    .return( &[rax+1] ) .if byte ptr [ strstart(rax) ] == ':'

    mov eax,':'
    mov [rdi],ah
    strchr(line, eax)

    mov [rdi],bl
    .return .if !rax

    movzx eax,byte ptr [rax+1]
    .return( 1 ) .if !eax

    .if islspace(eax)
        mov eax,1
    .else
        xor eax,eax
    .endif
    ret

istarget endp


findsymbol proc uses rsi rdi rbx symbol:string_t

    ldr rdi,symbol
    mov rsi,symbol_table
    mov ebx,symbol_count

    .repeat

        .return ebx .if !ebx

        dec ebx
        mov rax,[rsi]
        add rsi,size_t
        mov dx,[rax]
        mov cx,[rdi]
        or  dx,0x2020
        or  cx,0x2020
       .continue( 0 ) .if dx != cx
    .until !_stricmp(rax, rdi)

    sub rsi,size_t
    mov rdx,rsi
    mov rcx,[rdx]
    mov rax,[rdx+MAXSYMBOLS*size_t]
    ret

findsymbol endp


alloc_string proc uses rsi rdi value:string_t

    mov rdi,malloc(MAXTARGET)
    ExpandEnvironmentStrings(value, rdi, MAXTARGET-1)
    mov rsi,_strdup(rdi)
    free(rdi)
    mov rax,rsi
    ret

alloc_string endp


addsymbol proc uses rdi symbol:string_t, value:string_t

    .repeat

        .if findsymbol(symbol)

            mov rdi,rdx
            free(rax)
            .return .if !alloc_string(value)

        .else

            mov rdi,symbol_table
            mov eax,symbol_count
            .break .if eax >= MAXSYMBOLS-1

            lea rdi,[rdi+rax*size_t]
            inc eax
            mov symbol_count,eax
            .break .if !_strdup(symbol)

            mov [rdi],rax
            mov rax,value
            .return .if !rax
            .break .if !alloc_string(rax)
        .endif

        mov [rdi+MAXSYMBOLS*size_t],rax
       .return
    .until 1

    perror("To many symbols..")
    exit(1)
    ret

addsymbol endp


expandsymbol proc uses rsi rdi rbx string:string_t

  local base:string_t
  local symbol_name:string_t
  local symbol_macro:string_t

    mov base,malloc(MAXTARGET)
    mov rsi,rax
    add rax,MAXTARGET-256
    mov symbol_name,rax
    add rax,128
    mov symbol_macro,rax
    strcpy(rsi, string)
    mov rdi,rax
    strtrim(rax)

    .repeat

        .while 1

            .break(1) .if !strchr(rdi, '$')
            lea rdi,[rax+1]
            .continue(0) .if byte ptr [rdi] != '('

            mov rbx,rax

            .if ( memcmp(rdi, "(error ", 7) == 0 )
                .if strrchr(rdi, ')')
                    mov byte ptr [rax],0
                .endif
                perror( &[rdi+7] )
                exit(1)
            .endif

            mov rdx,symbol_macro
            mov rcx,symbol_name

            mov ax,[rbx]
            mov [rdx],ax
            add rbx,2
            add rdx,2

            .repeat

                mov al,[rbx]
                inc rbx
                .continue(0) .if al == ' '
                .continue(0) .if al == 9

                mov [rcx],al
                mov [rdx],al
                inc rcx
                inc rdx

                .break(1) .if !al

            .until al == ')'

            xor eax,eax
            mov [rcx-1],al
            mov [rdx],al

            .if !findsymbol(symbol_name)
                lea rax,null_string
            .endif

            strxchg(rsi, symbol_macro, rax)
            dec rdi
        .endw
        perror(string)
        exit(1)
    .until 1
    mov rbx,_strdup(rsi)
    free(rsi)
    mov rax,rbx
    ret

expandsymbol endp


;-------------------------------------------------------------------------------
; Read makefile
;-------------------------------------------------------------------------------

; return
;  1 if[n]def/ifeq
;  2 else
;  3 endif
;  4 include
;
gnumake proc string:string_t

    ldr rax,string
    mov ecx,[rax]
    mov edx,[rax+4]
    or  edx,0x20202020
    or  ecx,0x20202020
    xor eax,eax

    .switch
    .case ecx == 'qefi'
    .case ecx == 'esle'
        .if ( dl <= ' ' )
            inc eax
            .if ( cl == 'e' )
                inc eax
            .endif
        .endif
        .endc
    .case ecx == 'edfi'
    .case ecx == 'idne'
        .if ( dl == 'f' && dh <= ' ' )
            inc eax
            .if ( cl == 'e' )
                mov eax,3
            .endif
        .endif
        .endc
    .case ecx == 'dnfi'
        .if ( dx == 'fe' )
            inc eax
        .endif
        .endc
    .case cx == 'fi'
        shr ecx,16
        .if ( cl <= ' ' )
            inc eax
        .endif
        .endc
    .case ecx == 'lcni'
        .if ( dx == 'du' )
            shr edx,16
            .if ( dl == 'e' && dh <= ' ' )
                mov eax,4
            .endif
        .endif
        .endc
    .endsw
    ret

gnumake endp


skipiftag proc uses rsi rdi

    lea rsi,line_buf
    .repeat

        .if !fgets(rsi, MAXLINE, line_fp)

            perror("Missing !else or !endif")
            exit(1)
        .endif

        inc line_id
        .continue(0) .if !strtrim(rax)

        strstart(rsi)
        mov rdi,rax
        mov eax,[rax]

        .if ( al != '!' )

            gnumake(rsi)
            .if ( !eax || eax == 4 )
                .continue(0)
            .endif
        .else
            inc rdi
        .endif
        strstart(rdi)

        mov eax,[rax]
        or  eax,0x20202020

        .if eax == 'esle'

            movzx eax,if_level
            lea rcx,if_state
            .continue(0) .if byte ptr [rcx+rax-1] == 0

        .elseif eax == 'idne'

            dec if_level
        .else

            .continue(0) .if ax != 'fi'
            movzx eax,if_level
            lea rcx,if_state
            mov byte ptr [rcx+rax],0
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

    .if findsymbol(rdi)
        mov rdi,rax
    .endif
    .if findsymbol(rsi)
        mov rsi,rax
    .endif
    _stricmp(rdi, rsi)
    ret

find_and_compare endp


readline proc uses rsi rdi rbx

  local base:string_t
  local symbol:string_t

    mov base,malloc(MAXTARGET)
    add rax,MAXTARGET-256
    mov symbol,rax

    .while 1

        mov rax,line_fp
        .break .if !rax

        mov rsi,line_ptr
        mov rdi,rsi

        .if !fgets(rdi, MAXLINE, rax)

            fclose(line_fp)
            lea rcx,line_fp
            memcpy(rcx, addr [rcx+size_t], MAXMAKEFILES*size_t)
           .continue
        .endif

        inc line_id
        .continue .if !strtrim(rax)


        mov rdi,strstart(rsi)               ; EDI to start of line
        mov rsi,ltoken(strcpy(base, rax))   ; ESI to first token
        mov eax,[rdi]
        .continue .if al == '#'

        .if al != '!'

            .if ( gnumake(line_ptr) == 0 )
                mov rax,rdi
               .break
            .endif
            dec rdi
        .endif

        mov rdi,expandsymbol(&[rdi+1])
        strcpy(base, rdi)
        mov rdi,strstart(rdi)

        .switch

        .case !_strnicmp(rdi, "include", 7)

            mov rbx,expandsymbol(strstart(addr [rdi+8]))
            .if !fopen(rax, "rt") && includepath

                fopen(strfcat(addr currentfile, addr includepath, rbx), "rt")
            .endif
            xchg rbx,rax
            free(rax)
            .if !rbx

                perror(rdi)
                exit(1)
            .endif
            lea rdi,line_fp
            memmove(addr [rdi+size_t], rdi, MAXMAKEFILES*size_t-size_t)
            mov [rdi],rbx
           .continue

        .case !_strnicmp(rdi, "endif", 5)

            dec if_level
           .continue

        .case !_strnicmp(rdi, "else", 4)

            movzx ebx,if_level
            lea rcx,if_state
            .if byte ptr [rcx+rbx-1] == 0

                skipiftag()
            .endif
            .continue
        .endsw

        mov ax,[rdi]
        or  ax,0x2020
        .if ax != 'fi'

            syntax_error(rdi)
        .endif

        movzx ebx,if_level
        lea rcx,if_state
        mov byte ptr [rcx+rbx],1
        inc if_level

        .if !_strnicmp(rdi, "ifdef", 5)

            .if ltoken(addr [rdi+6])

                .if !findsymbol(rax)

                    skipiftag()
                .else
                    lea rcx,if_state
                    mov byte ptr [rcx+rbx],0
                .endif
                .continue
            .endif

            syntax_error(rdi)
        .endif

        .if !_strnicmp(rdi,"ifndef", 6)

            .if !ltoken(addr [rdi+7])

                syntax_error(rdi)
            .endif
            .if findsymbol(rax)

                skipiftag()
            .else
                lea rcx,if_state
                mov byte ptr [rcx+rbx],0
            .endif
            .continue
        .endif

        .if !_strnicmp(rdi, "ifeq", 4)

            mov rdi,expenviron(rdi)

            .return syntax_error(rdi) .if strtoken(&[rdi+5]) == NULL
            mov rdi,rax
            .return syntax_error(rdi) .if strtoken(0) == NULL
            mov rsi,rax
            jmp if_a_eq_b
        .endif

        mov al,[rdi+2]
        .if al != ' ' && al != 9
            syntax_error(rdi)
        .endif
        .if !strtoken(&[rdi+3])
            syntax_error(rdi)
        .endif

        mov rdi,expenviron(rax)

        .while 1 ; !if <> == <> || <> ..

            .if !strtoken(0)

                .if !findsymbol(rdi)
                    mov rax,rdi
                .endif
                .if byte ptr [rax] != '0'
                    lea rcx,if_state
                    mov byte ptr [rcx+rbx],0
                .else
                    skipiftag()
                .endif
                .break
            .endif

            mov rsi,rax
            .if !strtoken(0)
                syntax_error(rdi)
            .endif

            xchg rdi,rax
            mov eax,[rax]
            .if al < 2
                syntax_error(rdi)
            .endif

            .switch al

            .case TRUE

                .if strtoken(0) == NULL || byte ptr [rax] == '|'

                    lea rcx,if_state
                    mov byte ptr [rcx+rbx],0

                .elseif byte ptr [rax] == '&'

                    .return syntax_error(rdi) .if !strtoken(0)
                     mov rdi,rax
                    .continue
                .endif
                .break

            .case FALSE

                .if strtoken(0) == NULL || byte ptr [rax] != '|'

                    skipiftag()
                   .break
                .endif
                .return syntax_error(rdi) .if !strtoken(0)
                 mov rdi,rax
                .continue

            .case <if_a_eq_b> '='

                .ifd !find_and_compare()
                    .gotosw(TRUE)
                .endif
                .gotosw(FALSE)

            .case '<'

                .ifsd ( find_and_compare() < 0 )
                    .gotosw(TRUE)
                .endif
                .gotosw(FALSE)

            .case '>'

                .ifsd ( find_and_compare() > 0 )
                    .gotosw(TRUE)
                .endif
                .gotosw(FALSE)

            .case '&'

                .gotosw(FALSE) .if !findsymbol(rdi) || byte ptr [rax] == '0'
                .gotosw(FALSE) .if !findsymbol(rsi) || byte ptr [rax] == '0'
                .gotosw(TRUE)

            .case '|'

                .gotosw(FALSE) .if !findsymbol(rdi)
                .gotosw(TRUE)  .if byte ptr [rax] != '0'
                .gotosw(FALSE) .if !findsymbol(rsi) || byte ptr [rax] == '0'
                .gotosw(TRUE)

            .default

                syntax_error(rdi)
            .endsw
        .endw
    .endw
    mov rdi,rax
    free(base)
    mov rax,rdi
    ret

readline endp


issymbol proc uses rsi line:string_t

    .if strchr(line, '=')

        mov rsi,rax
        mov byte ptr [rax],0
        strspace(line)
        mov byte ptr [rsi],'='
        .if rax
            .if strstart(rax) != rsi
                mov ax,[rax]
                .if ax != '=+'
                    xor esi,esi
                .endif
            .endif
        .endif
        mov rax,rsi
    .endif
    ret

issymbol endp


getline proc uses rsi rdi rbx

  local base:string_t
  local symbol:string_t

    mov base,malloc(MAXTARGET)
    add rax,MAXTARGET-256
    mov symbol,rax

    .while 1

        .break .if !readline()

        mov rdi,rax ; EDI to start of line
        mov eax,[rdi]

        .if al == '.'

            .switch
            .case !_strnicmp(rdi, ".DEFAULT", 8)    ; define default rule to build target
            .case !_strnicmp(rdi, ".DONE", 5)       ; target to build, after all other targets are build
            .case !_strnicmp(rdi, ".IGNORE", 7)     ; ignore all error codes during building of targets
            .case !_strnicmp(rdi, ".INIT", 5)       ; first target to build, before any target is build
               .continue
            .case !_strnicmp(rdi, ".SILENT", 7)
                inc option_s        ; do not echo commands
               .continue
            .case !_strnicmp(rdi, ".RESPONSE", 9)
               .continue            ; define a response file for long ( > 128) command lines
            .case !_strnicmp(rdi, ".EXTENSIONS", 11)
                strtoken(rdi)       ; add extensions to the suffixes list
                lea rsi,extensions
                .while rax
                    mov rax,[rsi]
                    add rsi,size_t
                .endw
                .while strtoken(0)
                    .break .if byte ptr [rax] != '.'
                    mov [rsi-size_t],_strdup(rax)
                    add rsi,size_t
                .endw
                .continue
            .case !_strnicmp(rdi, ".SUFFIXES", 9)
                strtoken(rdi)       ; the suffixes list for selecting implicit rules
                .if !strtoken(0)
                    mov rdx,rdi
                    lea rdi,suffixes
                    xor eax,eax
                    mov ecx,32*size_t
                    rep stosb
                    mov rdi,rdx
                   .continue
                .endif
                lea rsi,suffixes
                mov rdx,rax
                .while rax
                    mov rax,[rsi]
                    add rsi,size_t
                .endw
                mov rax,rdx
                .while rax
                    .break .if byte ptr [rax] != '.'
                    mov [rsi-size_t],_strdup(rax)
                    add rsi,size_t
                    strtoken(0)
                .endw
                .continue
            .endsw
            mov rax,rdi
           .break
        .endif

        .if issymbol(rdi)

            mov rdx,base
            xor ecx,ecx
            mov [rdx],cl
            mov [rax],cl
            lea rsi,[rax+1]

            .if byte ptr [rax-1] == '+' ; case '+='

                mov [rax-1],cl
                strtrim(rdi)

                .if findsymbol(rdi)

                    strcat(strcpy(base, rax), " ")
                .endif
            .endif

            strtrim(rdi)
            strcpy(symbol, rdi)
            strtoken(rsi)

            mov rsi,base
            .while rax

                .while 1

                    mov cx,[rax]

                    .break .if cx == '\'
                    .break .if cx == '&'

                    strcat(rsi, rax)
                    strcat(rsi, " ")

                    .break(1) .if !strtoken(0)

                .endw

                .break .if !readline()
                strtoken(rax)

            .endw

            strtrim(rsi)
            addsymbol(symbol, rsi)
            .continue

        .endif

        mov rax,rdi
       .break
    .endw
    mov rdi,rax
    free(base)
    mov rax,rdi
    ret

getline endp


addtarget proc uses rsi rdi rbx target:string_t

  local base:string_t
  local target_name:string_t
  local target_string:string_t
  local target_command:string_t
  local target_srcpath:string_t
  local p:string_t

    mov base,malloc(MAXTARGET)
    mov rdi,rax
    mov rsi,target
    strtrim(rsi)
    mov byte ptr [rdi],0

    .while byte ptr [rsi+rax-1] == '\'

        mov byte ptr [rsi+rax-1],0
        strcat(rdi, rsi)
        mov byte ptr [rsi],0
        .break .if !fgets(rsi, MAXLINE, line_fp)
        inc line_id
        .break .if !strtrim(rsi)
    .endw
    strcat(rdi, rsi)
    mov rsi,rdi

    .repeat

        .if !_strdup(strstart(rdi))

            perror("To many targets..")
            exit(1)
        .endif
        mov target_string,rax

        ltoken(rdi)
        .if !strrchr(rdi, ':')

            perror(rsi)
            exit(1)
        .endif

        mov byte ptr [rax],0
        strtrim(rdi)

        mov target_name,expandsymbol(rdi)
        mov rsi,line_ptr
        xor eax,eax
        mov target_srcpath,rax
        mov target_command,rax

        mov [rsi],al
        mov ah,[rdi]
        mov [rdi],al

        .if ah == '{'

            mov rbx,target_name

            .if strchr(rbx, '}')

                mov byte ptr [rax],0
                lea rdx,[rax+1]
                mov p,rdx
                .if !_strdup(addr [rbx+1])

                    perror("To many targets..")
                    exit(1)
                .endif
                mov target_srcpath,rax
                strcpy(rbx, strstart(p))
            .endif
        .endif

        .while getline()

            .break .if istarget(rsi)
            strcat(rdi, strstart(rsi))
            strcat(rdi, linefeed)
        .endw
        .if !rax

            mov [rsi],al
        .endif

        .if byte ptr [rdi]

            .if !_strdup(rdi)

                perror("To many targets..")
                exit(1)
            .endif
            mov target_command,rax
        .endif

        .if !malloc(TARGET)

            perror("To many targets..")
            exit(1)
        .endif

        mov rbx,rax
        assume rbx:target_t

        mov [rbx].next,target_table
        mov [rbx].prev,0
        .if rax
            mov [rax].TARGET.prev,rbx
        .endif

        mov [rbx].target, target_name
        mov [rbx].string, target_string
        mov [rbx].command,target_command
        mov [rbx].srcpath,target_srcpath
        inc target_count
        mov target_table,rbx

        .if !_stricmp(target_name, "all")

            mov [rbx].type,T_ALL
           .break
        .endif

        mov [rbx].TARGET.type,T_TARGET
        mov rax,target_name
        .break .if byte ptr [rax] != '.'

        inc rax
        mov p,rsi
        lea rsi,suffixes
        mov rdi,rax
        mov rax,[rsi]
        add rsi,size_t
        .while rax
            .break .if strstri(rdi, rax)
            mov rax,[rsi]
            add rsi,size_t
        .endw
        mov rsi,p

        .break .if !rax
        mov [rbx].type,T_METHOD
    .until 1

    assume rbx:nothing

    .if istarget(rsi)
        addtarget(rsi)
    .endif
    free(base)
    ret

addtarget endp


;-------------------------------------------------------------------------------
; Build target
;-------------------------------------------------------------------------------

findtarget proc uses rsi rdi rbx target:string_t

    mov rdi,expandsymbol(target)
    mov rsi,target_table
    xor ebx,ebx
    .repeat
        mov rbx,rsi
        .break .if !rsi
        mov rax,[rsi].TARGET.target
        mov rsi,[rsi].TARGET.next
        mov dx,[rax]
        or  dx,0x2020
        mov cx,[rdi]
        or  cx,0x2020
        .continue(0) .if dx != cx
        .break .if !_stricmp(rax, rdi)
        xor ebx,ebx
    .until !rsi

    free(rdi)
    mov rax,rbx
    ret

findtarget endp


build_object proc uses rsi rdi rbx object:string_t

  local srcname[_MAX_PATH]:byte
  local srcfile[_MAX_PATH]:byte
  local command[_MAX_PATH]:byte
  local p:string_t,q:string_t,r:string_t

    lea rbx,srcname
    lea rdi,srcfile
    lea rsi,extensions
    .if strext(strcpy(rbx, object))

        mov byte ptr [rax],0
    .endif

    lea rbx,suffixes

    .repeat

        mov rax,[rbx]
        .if !rax
            perror(&srcname)
            exit(1)
        .endif

        mov p,rax
        add rbx,size_t
        lea rsi,extensions

        .repeat

            mov rax,[rsi]
            add rsi,size_t
            .continue(01) .if !rax
            mov q,rax

            .continue(0) .if !findtarget(strcat(strcpy(rdi, rax), p))

            mov r,rax
            strcat(strcpy(rdi, &srcname), q)
            mov rdx,r
            mov rcx,[rdx].TARGET.srcpath
            .if rcx

                strcpy(rdi, strfcat(&command, rcx, rdi))
            .endif

            filexist(rax)
            mov rdx,r
            dec eax
        .untilz
    .until 1

    lea rbx,srcname
    lea rsi,command
    mov rax,[rdx].TARGET.command
    .if rax == NULL
        perror(rdi)
        exit(1)
    .endif

    strxchg(strcpy(rsi, rax), "$*", rbx)
    strxchg(rsi, "$<", rdi)

    setfext(rdi, suffixes)
    strxchg(rsi, "$@", rdi)

    mov rsi,expandsymbol(rsi)

    .if option_d

        printf("%s\n", rsi)

    .else

        .while strchr(rsi, 10)

            lea rbx,[rax+1]
            mov byte ptr [rax],0
            .if !option_s

                printf("\t%s\n", rsi)
            .endif

            system(rsi)
            mov byte ptr [rbx-1],10
            mov rsi,rbx
        .endw

        .if !option_s

            printf("\t%s\n", rsi)
        .endif

        system(rsi)
        dec eax
        .if eax || eax != errorlevel
            .if ( !option_I )
                perror(rdi)
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
    add ecx,eax
    and ecx,0x00FFFFFF
    sprintf(buffer, "%s\\$%06X$.%s", envtemp, ecx, ext)
    fopen(buffer, "wt+")
    ret

opentemp endp


build_target proc uses rsi rdi rbx target:target_t

  local base:string_t,
        target_path:string_t,
        target_name:string_t,
        target_file:string_t,
        target_command:string_t,
        target_string:string_t,
        fp:LPFILE

    mov base,malloc(MAXTARGET)
    mov rdi,rax
    mov rsi,target
    mov rsi,expandsymbol([rsi].TARGET.string)
    mov target_string,rax

    .while 1

        lodsb
        stosb

        .break .if !al
        .break .if al == ':' && byte ptr [rsi] != '\'
    .endw

    mov byte ptr [rdi],0
    mov rdi,base
    _strdup(rdi)
    mov target_path,rax
    _strdup(rax)
    mov target_name,rax
    mov rbx,rax
    .if strrchr(rax, ':')
        mov byte ptr [rax],0
    .endif

    strtrim(rbx)
    _strdup(strfn(rbx))
    mov target_file,rax
    .if strext(rax)
        mov byte ptr [rax],0
    .endif

    .while 1

        mov ax,[rsi-1]
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
        mov byte ptr [rdi],0

        mov rdi,base
        .if findtarget(rdi)
            .return .if build_target(rax)
        .else
            build_object(rdi)
        .endif
    .endw

    free(target_string)
    mov rsi,target
    mov rax,[rsi].TARGET.command

    .return .if !rax ; all: <target1> [<target2>] ... or <no command>

    mov rsi,expandsymbol(rax)
    mov rdi,strcpy(base, rax)
    free(rsi)
    strxchg(rdi, "$@", target_name)
    strxchg(rdi, "$*", target_file)

    mov rsi,rdi

    .repeat

        .break .if !strstr(rsi, "@<<")

        lea rbx,[rax+3]
        mov byte ptr [rbx-2],0
        .if !strchr(rbx, 10)
            perror("Make execution terminated")
            exit(1)
        .endif

        lea rbx,[rax+1]
        .break .if !strstr(rbx, "<<")

        mov byte ptr [rax],0
        lea rdi,[rax+2]
        .if !opentemp(&responsefile, "$$$")
            perror("Make execution terminated")
            exit(1)
        .endif

        mov fp,rax
        fprintf(rax, rbx)
        fclose(fp)

        .if option_d

            printf("%s:\n%s\n", addr responsefile, rbx)
        .endif
        strcat(rsi, addr responsefile)
        .break .if !strchr(rdi, 10)
        strcat(rsi, rax)
    .until 1

    .if option_d

        printf("%s\n", rsi)
        xor eax,eax
    .else
        .if !option_s

            mov rdi,rsi
            printf("%s\n", target_path)

            .while strchr(rdi, 10)

                lea rbx,[rax+1]
                mov byte ptr [rax],0
                printf("\t%s\n", rdi)
                mov byte ptr [rbx-1],10
                mov rdi,rbx
            .endw
            printf("\t%s\n", rdi)
        .endif

        xor edi,edi
        .if opentemp(&commandfile, "cmd")
            mov rbx,rax
            fprintf(rax, "@echo off\n%s\n", rsi)
            fclose(rbx)
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

addtargetarg proc uses rbx target:string_t

    .if strlen(target)

        .if malloc(&[rax+1+ARGS])

            mov rbx,rax
            mov [rbx].ARGS.name,strcpy(&[rbx+ARGS], target)
            xor eax,eax
            mov [rbx].ARGS.next,rax

            mov rcx,target_args
            .if rcx == 0

                mov target_args,rbx

            .else

                .while rax != [rcx].ARGS.next

                    mov rcx,[rcx].ARGS.next
                .endw
                mov [rcx].ARGS.next,rbx
            .endif
        .endif
    .endif
    ret

addtargetarg endp


make proc uses rsi rdi rbx file:string_t, target:string_t


    .if !fopen(file, "rt")

        perror(file)
        exit(1)
    .endif

    mov line_fp,rax

    .while getline()

        mov rsi,rax
        .break .if !istarget(rsi)

        addtarget(rsi)
    .endw

    mov rsi,target_args

    .if !rsi

        .if !target_count

            perror("Missing target..")
            exit(1)
        .endif

        .for eax = 0,
             ebx = 0,
             edi = 0,
             rcx = target_table : [rcx].TARGET.next : rcx = [rcx].TARGET.next
        .endf

        .for ( : rcx && !eax : rcx = [rcx].TARGET.prev )

            mov rdi,rcx
            mov eax,[rcx].TARGET.type

            .break .if eax == T_ALL

            .if eax == T_METHOD
                mov rbx,rcx
                xor eax,eax
            .else
                mov rax,[rcx].TARGET.command
            .endif
        .endf

        .if  !rax && !rbx

            perror([rdi].TARGET.target)
            exit(1)
        .endif

        addtargetarg([rdi].TARGET.target)

        mov rsi,target_args
    .endif


    .for ( : rsi : rsi = [rsi].ARGS.next )

        .break .if !findtarget([rsi].ARGS.name)

        build_target(rax)
    .endf
    ret

make endp


;-------------------------------------------------------------------------------
; MAIN
;-------------------------------------------------------------------------------

AddMakefile proc uses rbx file:string_t

    .if strlen(file)

        .if malloc(&[rax+1+ARGS])

            mov rbx,rax
            strcpy(&[rbx+ARGS], file)
            mov [rbx].ARGS.name,rax

            xor eax,eax
            mov [rbx].ARGS.next,rax
            mov rcx,file_args

            .if !rcx

                mov file_args,rbx
            .else
                .while rax != [rcx].ARGS.next

                    mov rcx,[rcx].ARGS.next
                .endw
                mov [rcx].ARGS.next,rbx
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

install proc uses rsi rdi rbx

  local base[_MAX_PATH]:char_t
  local path[_MAX_PATH]:char_t

    lea rsi,base
    lea rdi,path

    GetModuleFileNameA(0, rsi, _MAX_PATH)
    strpath(strpath(rsi))
    .return .if !fopen(strfcat(rdi, rsi, "bin\\envars32.bat"), "wt")
    mov rbx,rax
    fprintf(rax,
        "@echo off\n"
        "set AsmcDir=%s\n"
        "set PATH=%s\\bin;%%PATH%%\n"
        "set INCLUDE=%s\\include;%%INCLUDE%%\n", rsi, rsi, rsi)
    fprintf(rbx, "set LIB=%s\\lib\\x86;%%LIB%%\n", rsi)
    fclose(rbx)
    .return .if !fopen(strfcat(rdi, rsi, "bin\\envars64.bat"), "wt")
    mov rbx,rax
    fprintf(rax,
        "@echo off\n"
        "set AsmcDir=%s\n"
        "set PATH=%s\\bin;%%PATH%%\n"
        "set INCLUDE=%s\\include;%%INCLUDE%%\n", rsi, rsi, rsi)
    fprintf(rbx, "set LIB=%s\\lib\\x64;%%LIB%%\n", rsi)
    fclose(rbx)
    ret

install endp

main proc argc:int_t, argv:array_t

    .if getenv("TEMP")

        mov envtemp,rax ; default to .
    .endif

    mov symbol_table,malloc(MAXSYMBOLS*size_t*2)

    .if !getenv("ASMCDIR")

        mov rcx,argv
        mov rax,[rcx]
        strcpy(&line_buf, rax)
        strpath(rax)
        strpath(rax)
        SetEnvironmentVariable("ASMCDIR", rax)
        lea rax,line_buf
    .endif

    strcpy(&includepath, rax)
    strcat(rax, "\\lib")

ifdef _WIN64
    lea r15,_ltype
endif

    .for rsi = argv, edi = argc : edi > 1 :

        dec edi
        add rsi,size_t
        mov rbx,[rsi]
        mov eax,[rbx]

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
                .if ( byte ptr [rbx+2] == 0 )
                    inc option_I
                .else
                    strcpy(&includepath, &[rbx+2])
                .endif
                .endc

            .case 'f'
                add rbx,2
                .if eax & 0xFF00
                    AddMakefile(rbx)
                   .endc
                .endif
                add rsi,size_t
                mov rdx,[rsi]
                AddMakefile(rdx)
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
            .if strchr(rbx, '=')
                mov byte ptr [rax],0
                inc rax
                addsymbol(rbx, rax)
            .else
                addtargetarg(rbx)
            .endif
        .endsw
    .endf

    .if !option_h && !option_s

        print_copyright()
    .endif

    mov rsi,file_args

    .if !rsi

        AddMakefile("makefile")
        mov rsi,file_args
    .endif

    .while rsi

        .break .if make([rsi].ARGS.name, target_args)
        mov rsi,[rsi].ARGS.next
    .endw
    xor eax,eax
    ret

main endp

    end _tstart
