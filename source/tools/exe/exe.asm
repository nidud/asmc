; EXE.ASM--
; Locates .exe files and display some header information
include io.inc
include string.inc
include stdio.inc
include stdlib.inc
include winbase.inc
include fcntl.inc
include tchar.inc

    .code

main proc argc:SINT, argv:PVOID

  local fname[256]:BYTE
  local finfo[1024]:BYTE

    .repeat

        .if rcx != 2 ; argc

            printf(
                "EXE Version 1.0 Copyright (c) 2017 GNU General Public License\n"
                "\nUsage: EXE <filename>[.exe]\n\n")
            mov eax,1
            .break
        .endif

        mov rdi,[rdx+8] ; argv[1]

        .if !SearchPath(NULL, rdi, ".exe", 256, &fname, NULL)

            printf("File not found: %s\n", rdi)
            mov eax,1
            .break
        .endif

        lea rdi,fname
        .if _open(rdi, O_RDONLY or O_BINARY, 0) == -1

            perror(rdi)
            mov eax,1
            .break
        .endif
        mov ebx,eax
        lea rsi,finfo

        _read(ebx, rsi, 1024)
        _close(ebx)

        printf("\n%s:\n Machine:", rdi)

        mov eax,[rsi].IMAGE_DOS_HEADER.e_lfanew
        add rsi,rax
        movzx eax,[rsi].IMAGE_NT_HEADERS.FileHeader.Machine
        .switch eax
        .case IMAGE_FILE_MACHINE_I386
            printf("\tI386\n")
            mov eax,[rsi].IMAGE_NT_HEADERS32.OptionalHeader.ImageBase
            printf(" ImageBase:\t%08X\n", eax)
            .endc
        .default
            printf("\t\tAMD64\n")
            mov rax,[rsi].IMAGE_NT_HEADERS64.OptionalHeader.ImageBase
            printf(" ImageBase:\t\t%016llX\n", rax)

            movzx ebx,[rsi].IMAGE_NT_HEADERS64.FileHeader.Characteristics
            lea rax,@CStr("No")
            .if ebx & IMAGE_FILE_LARGE_ADDRESS_AWARE
                lea rax,@CStr("Yes")
            .endif
            printf(" Large address aware:\t%s\n", rax)

            movzx ebx,[rsi].IMAGE_NT_HEADERS64.OptionalHeader.DllCharacteristics
            lea rax,@CStr("No")
            .if ebx & IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE
                lea rax,@CStr("Yes")
            .endif
            printf(" ASLR:\t\t\t%s\t/DYNAMICBASE\n", rax)
            lea rax,@CStr("No")
            .if ebx & IMAGE_DLLCHARACTERISTICS_HIGH_ENTROPY_VA
                lea rax,@CStr("Yes")
            .endif
            printf(" ASLR^2:\t\t%s\t/HIGHENTROPYVA\n", rax)
            lea rax,@CStr("No")
            .if ebx & IMAGE_DLLCHARACTERISTICS_NX_COMPAT
                lea rax,@CStr("Yes")
            .endif
            printf(" DEP:\t\t\t%s\t/NXCOMPAT\n", rax)
            lea rax,@CStr("No")
            .if ebx & IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE
                lea rax,@CStr("Yes")
            .endif
            printf(" TS Aware:\t\t%s\t/GS\n\n", rax)
        .endsw
    .until 1
    xor eax,eax
    ret

main endp

    end _tstart
