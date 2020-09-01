; IMPORT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdio.inc
include stdlib.inc
include winbase.inc
include tchar.inc

    .code

BuildImportLib proc uses rsi rdi rbx dll_name:string_t, dll_path:string_t

  local dll[256] :char_t,
        def[256] :char_t,
        cmd[256] :char_t,
        count    :uint_t,
        module   :HMODULE,
        fp       :LPFILE

    lea rdi,dll
    .if !strrchr(strcpy(rdi, dll_name), '.')
        strcat(rdi, ".dll")
    .endif
    .if !LoadLibrary(rdi)
        perror(rdi)
        .return 1
    .endif
    mov module,rax

    mov rcx,rax
    mov eax,[rcx].IMAGE_DOS_HEADER.e_lfanew
    mov esi,[rcx+rax].IMAGE_NT_HEADERS.OptionalHeader.DataDirectory.VirtualAddress
    add rsi,rcx
    mov count,[rsi].IMAGE_EXPORT_DIRECTORY.NumberOfNames
    mov ebx,[rsi].IMAGE_EXPORT_DIRECTORY.AddressOfNames
    add rbx,rcx

    strcpy(strrchr(strcpy(&def, rdi), '.'), ".def")

    .if fopen(&def, "wt")

        mov fp,rax

        .for esi = 0 : esi < count : esi++

            mov eax,[rbx+rsi*4]
            add rax,module
            .continue .if byte ptr [rax] == '?'

            fprintf(fp, "++%s.'%s'\n", rax, rdi)
        .endf

        fclose(fp)

        lea rsi,cmd
        mov byte ptr [strrchr(rdi, '.')],0
        sprintf(rsi, "libw /n /c /q /b /fac /i6 %s\\%s.lib @%s.def", dll_path, rdi, rdi)
        system(rsi)
        remove(&def)

    .else

        perror(&def)
    .endif

    FreeLibrary(module)
    xor eax,eax
    ret

BuildImportLib endp


main proc argc:int_t, argv:array_t

  local lbuf[256]:char_t
  local list:string_t
  local path:string_t

    .if ecx < 2

        printf("Usage: import <list> [<out_path>]\n")
        .return 1
    .endif

    mov list,[rdx+8]
    .if ecx > 2
        mov rax,[rdx+16]
    .else
        lea rax,@CStr(".")
    .endif
    mov path,rax

    .if fopen(list, "rt")

        mov rsi,rax
        lea rdi,lbuf

        .while fgets(rdi, 256, rsi)

            mov al,[rdi]
            .if al == ' ' || al == 9 || al == ';'

                xor eax,eax

            .elseif strlen(rdi)

                lea rcx,[rdi+rax]
                .repeat
                    dec rcx
                    .break .if byte ptr [rcx] > ' '
                    mov byte ptr [rcx],0
                    dec rax
                .untilz
            .endif
            .if eax
                printf("  %s.lib\n", rdi)
                BuildImportLib(rdi, path)
            .endif
        .endw
        xor eax,eax
    .else

        perror(list)
        mov eax,1
    .endif
    ret

main endp

    end _tstart
