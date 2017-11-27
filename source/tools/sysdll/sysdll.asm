include io.inc
include direct.inc
include string.inc
include stdio.inc
include stdlib.inc
include winbase.inc
include tchar.inc

    .code

exit_usage proc
    printf(
        "SYSDLL creates import from %%windir%%/system32/[<mask>|*].dll\n"
        "\n"
        "Usage: SYSDLL <options> [<mask>]\n"
        "\n"
        " /def - create .def files\n"
        " /lib - create .lib files\n"
        " /inc - create .inc files\n"
    )
    exit(0)
exit_usage endp

BuildInc proc uses rsi rdi rbx r12 dll:LPSTR
local fn_inc[128]:sbyte
local fn_dll[128]:sbyte

    lea rdi,fn_dll
    mov rdx,rcx
    .if strrchr(strcpy(rdi, rdx), '.')
        mov byte ptr [rax],0
    .endif
    .if LoadLibrary(strcat(rdi, ".dll"))

        mov rbx,rax
        strrchr(rdi, '.')
        mov byte ptr [rax],0

        lea rsi,fn_inc
        sprintf(rsi, "inc\\%s.inc", rdi)

        .if fopen(rsi, "wt")

            mov r12,rax
            fprintf(r12, "\nincludelib %s.lib\n\n", rdi)

            mov eax,[rbx].IMAGE_DOS_HEADER.e_lfanew
            mov eax,[rbx+rax].IMAGE_NT_HEADERS.OptionalHeader.DataDirectory.VirtualAddress
            mov edi,[rbx+rax].IMAGE_EXPORT_DIRECTORY.NumberOfNames
            mov esi,[rbx+rax].IMAGE_EXPORT_DIRECTORY.AddressOfNames
            .if esi && eax
                add rsi,rbx
                .while edi
                    lodsd
                    lea r8,[rax+rbx]
                    .if byte ptr [r8] != '?'
                        fprintf(r12, "%s proto :vararg\n", r8)
                    .endif
                    dec edi
                .endw
            .endif
            fclose(r12)
        .else
            perror(rsi)
        .endif
        FreeLibrary(rbx)
        xor eax,eax
    .else
        perror(rdi)
        mov eax,1
    .endif
    ret

BuildInc endp

BuildDef proc uses rsi rdi rbx r12 dll:LPSTR
local fn_def[128]:sbyte
local fn_dll[128]:sbyte

    lea rdi,fn_dll
    mov rdx,rcx
    .if strrchr(strcpy(rdi, rdx), '.')
        mov byte ptr [rax],0
    .endif
    .if LoadLibrary(strcat(rdi, ".dll"))

        mov rbx,rax
        strrchr(rdi, '.')
        mov byte ptr [rax],0

        lea rsi,fn_def
        sprintf(rsi, "def\\%s.def", rdi)

        .if fopen(rsi, "wt")

            mov r12,rax
            fprintf(r12,"LIBRARY %s\nEXPORTS\n", rdi)

            mov eax,[rbx].IMAGE_DOS_HEADER.e_lfanew
            mov eax,[rbx+rax].IMAGE_NT_HEADERS.OptionalHeader.DataDirectory.VirtualAddress
            mov edi,[rbx+rax].IMAGE_EXPORT_DIRECTORY.NumberOfNames
            mov esi,[rbx+rax].IMAGE_EXPORT_DIRECTORY.AddressOfNames
            .if esi && eax
                add rsi,rbx
                .while edi
                    lodsd
                    lea r8,[rax+rbx]
                    .if byte ptr [r8] != '?'
                        fprintf(r12, "\"%s\"\n", r8)
                    .endif
                    dec edi
                .endw
            .endif
            fclose(r12)
        .else
            perror(rsi)
        .endif
        FreeLibrary(rbx)
        xor eax,eax
    .else
        perror(rdi)
        mov eax,1
    .endif
    ret

BuildDef endp

BuildLib proc uses rsi rdi rbx r12 r13 dll:LPSTR
local buffer[256]:sbyte
local fn_dll[128]:sbyte

    lea rdi,fn_dll
    mov rdx,rcx
    .if strrchr(strcpy(rdi, rdx), '.')
        mov byte ptr [rax],0
    .endif

    .if LoadLibrary(strcat(rdi, ".dll"))

        mov rbx,rax
        strcpy(strrchr(rdi, '.'), ".def")
        .if fopen(rdi, "wt")

            mov r12,rax
            strrchr(rdi, '.')
            mov byte ptr [rax],0
            mov eax,[rbx].IMAGE_DOS_HEADER.e_lfanew
            mov eax,[rbx+rax].IMAGE_NT_HEADERS.OptionalHeader.DataDirectory.VirtualAddress
            mov r13d,[rbx+rax].IMAGE_EXPORT_DIRECTORY.NumberOfNames
            mov esi,[rbx+rax].IMAGE_EXPORT_DIRECTORY.AddressOfNames
            .if esi && eax
                add rsi,rbx
                .while r13d
                    lodsd
                    fprintf(r12, "++%s.\'%s.dll\'\n", addr [rax+rbx], rdi)
                    dec r13d
                .endw
                fclose(r12)
                lea r12,buffer
                sprintf(r12, "libw /n /c /q /b /fac /i6 lib\\%s.lib @%s.def", rdi, rdi)
                system(r12)
            .else
                fclose(r12)
            .endif
            strcat(rdi, ".def")
            remove(rdi)
        .else
            perror(rdi)
        .endif
        FreeLibrary(rbx)
        xor eax,eax
    .else
        perror(rdi)
        mov eax,1
    .endif
    ret

BuildLib endp

main proc

    local wild[128]:sbyte
    local path[_MAX_PATH]:sbyte
    local ff:_finddata_t
    local option_def:byte
    local option_lib:byte
    local option_inc:byte

    xor eax,eax
    mov option_def,al
    mov option_lib,al
    mov option_inc,al
    mov wild,al

    lea edi,[ecx-1] ; argc
    lea rsi,[rdx+8] ; argv

    .while edi
        lodsq
        mov rbx,rax
        mov eax,[rbx]
        .switch al
          .case '/'
          .case '-'
            .if ah == 'd'
                inc option_def
                .endc
            .elseif ah == 'l'
                inc option_lib
                .endc
            .elseif ah == 'i'
                inc option_inc
                .endc
            .endif
            exit_usage()
          .default
            strcpy(&wild, rbx)
            .endc
        .endsw
        dec edi
    .endw

    .if !option_inc && !option_def && !option_lib
        exit_usage()
    .endif
    .if !wild
        mov word ptr wild,'*'
    .endif

    .if option_inc
        _mkdir("inc")
    .endif
    .if option_def
        _mkdir("def")
    .endif
    .if option_lib
        _mkdir("lib")
    .endif

    .if getenv("windir")

        lea rbx,ff._name
        lea rdi,path
        sprintf(rdi, "%s\\system32\\%s.dll", rax, &wild)

        .ifd _findfirst(rdi, &ff) != -1
            mov rsi,rax
            .repeat
                .if !( ff.attrib & _A_SUBDIR )

                    .if option_inc
                        BuildInc(rbx)
                    .endif
                    .if option_def
                        BuildDef(rbx)
                    .endif
                    .if option_lib
                        BuildLib(rbx)
                    .endif
                .endif
            .until _findnext(rsi, &ff)
            _findclose(rsi)
        .endif
    .endif
    xor eax,eax
    ret

main endp

    end _tstart
