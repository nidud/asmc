; EXE.ASM--
;
; Locates .exe files and display some header information
;
include io.inc
include string.inc
include stdio.inc
include stdlib.inc
include winbase.inc
include fcntl.inc
include tchar.inc

    .code

_tmain proc argc:int_t, argv:array_t

  local fname[ 256]:TCHAR
  local finfo[1024]:TCHAR

    .repeat

        .if ecx != 2 ; argc

            _tprintf( "EXE Version 1.0 Public Domain\n\nUsage: EXE <filename>[.exe]\n\n" )
            mov eax,1
            .break
        .endif

        mov rdi,[rdx+8] ; argv[1]
        .if !SearchPath( NULL, rdi, ".exe", 256, &fname, NULL )

            _tprintf( "File not found: %s\n", rdi )
            mov eax,1
            .break
        .endif

        lea rdi,fname
        .if _topen( rdi, O_RDONLY or O_BINARY, 0 ) == -1

            _tperror(rdi)
            mov eax,1
            .break
        .endif

        mov ebx,eax
        lea rsi,finfo

        _read( ebx, rsi, 1024 )
        _close( ebx )
        _tprintf( "\n%s:\n Machine:", rdi )

        mov eax,[rsi].IMAGE_DOS_HEADER.e_lfanew
        add rsi,rax

        .if ( [rsi].IMAGE_NT_HEADERS.FileHeader.Machine == IMAGE_FILE_MACHINE_I386 )

            _tprintf( "\tI386\n ImageBase:\t%08X\n", [rsi].IMAGE_NT_HEADERS32.OptionalHeader.ImageBase )

        .else

            _tprintf( "\t\tAMD64\n ImageBase:\t\t%016llX\n", [rsi].IMAGE_NT_HEADERS64.OptionalHeader.ImageBase )

            lea rdi,@CStr( "No"  )
            lea rbx,@CStr( "Yes" )
            mov rax,rdi
            .if ( [rsi].IMAGE_NT_HEADERS64.FileHeader.Characteristics & IMAGE_FILE_LARGE_ADDRESS_AWARE )
                mov rax,rbx
            .endif
            _tprintf( " Large address aware:\t%s\n", rax )

            movzx esi,[rsi].IMAGE_NT_HEADERS64.OptionalHeader.DllCharacteristics
            mov rax,rdi
            .if ( esi & IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE )
                mov rax,rbx
            .endif
            _tprintf( " ASLR:\t\t\t%s\t/DYNAMICBASE\n", rax )
            mov rax,rdi
            .if ( esi & IMAGE_DLLCHARACTERISTICS_HIGH_ENTROPY_VA )
                mov rax,rbx
            .endif
            _tprintf( " ASLR^2:\t\t%s\t/HIGHENTROPYVA\n", rax )
            mov rax,rdi
            .if ( esi & IMAGE_DLLCHARACTERISTICS_NX_COMPAT )
                mov rax,rbx
            .endif
            _tprintf( " DEP:\t\t\t%s\t/NXCOMPAT\n", rax )
            mov rax,rdi
            .if ( esi & IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE )
                mov rax,rbx
            .endif
            _tprintf( " TS Aware:\t\t%s\t/GS\n\n", rax )
        .endif

    .until 1
    xor eax,eax
    ret

_tmain endp

    end _tstart
