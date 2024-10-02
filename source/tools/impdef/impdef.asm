; IMPDEF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdio.inc
include string.inc
include stdlib.inc
include winbase.inc
include tchar.inc

define __IMPDEF__ 100

.data
 option_p   string_t 0
 option_c   char_t 0
 option_cpp char_t 0
 option_q   char_t 0
 option_n   char_t 0
 banner     char_t 0

.code

get_module proc dll_name:string_t

    .new dll[256]:char_t

    .if !strrchr(strcpy(&dll, dll_name), '.')

        strcat(&dll, ".dll")
    .endif

    .if ( LoadLibrary(&dll) == NULL )

        strcpy(strrchr(&dll, '.'), ".drv")
        .if ( LoadLibrary(&dll) == NULL )

            strcpy(strrchr(&dll, '.'), ".exe")
            LoadLibrary(&dll)
        .endif
    .endif

    .if ( rax == NULL )
ifdef __PE__
        printf( "%s: Invalid argument\n", dll_name )
else
        _dosmaperr( GetLastError() )
        perror(dll_name)
endif
        xor eax,eax
    .endif
    ret

get_module endp

ifndef _WIN64

get_argcnt proc uses rsi rdi procaddress:ptr, size:uint_t

    mov rdx,procaddress
    mov ecx,size

    .for ( : ecx : ecx--, rdi++ )

        mov al,[rdi]

        .if ( al == 0xC3 )

            mov al,[rdi-1]

            .switch al
            .case 0x8A ; mov bl
            .case 0x8B ; mov ebx
            .case 0x3B ; cmp ebx
            .case 0x83 ; add ebx
            .case 0x03 ; add ebx
            .case 0x2B ; sub ebx
            .case 0x23 ; and ebx
            .case 0xF6 ; test bl
            .case 0xF7 ; test ebx
            .case 0xE6 ; call
            .case 0xE8 ; call
            .case 0xE9 ; jmp far
            .case 0xEB ; jmp near
            .case 0x84 ; je
            .case 0x85 ; jne
            .case 0xB6 ; movzx ,bl
            .case 0x94 ; sete bl
                .endc
            .default
                .break
            .endsw

        .elseif ( al == 0xC2 )

            mov al,[rdi-1]

            .switch al
            .case 0x8A ; mov dl
            .case 0x8B ; mov edx
            .case 0x3B ; cmp edx
            .case 0x0B ; or  edx
            .case 0x83 ; add edx
            .case 0x03 ; add edx
            .case 0x2B ; sub edx
            .case 0x23 ; and edx
            .case 0xF6 ; test dl
            .case 0xF7 ; test edx
            .case 0xB6 ; movzx ,dl
            .case 0x94 ; sete dl
            .case 0x84 ; je
            .case 0x85 ; jne
            .case 0xE6 ; call
            .case 0xE8 ; call
            .case 0xE9 ; jmp far
            .case 0xEB ; jmp near
                .endc
            .default
                movzx eax,word ptr [rdi+1]
                .if ( !ah && !( al & 3 ) )
                    .return
                .endif
            .endsw
        .endif
    .endf
    xor eax,eax
    ret

get_argcnt endp

endif

process_function proc uses rsi rdi rbx fp:LPFILE, module:HMODULE, id:int_t, rva:uint_t, fname:string_t

   .new name[256]:char_t
   .new args[16]:char_t = 0
   .new argcnt:int_t = -1

    mov rax,module
    mov esi,[rax].IMAGE_DOS_HEADER.e_lfanew
    mov esi,[rax+rsi].IMAGE_NT_HEADERS.OptionalHeader.DataDirectory.VirtualAddress
    add rsi,rax
    mov rcx,fname
    .if ( !rcx )

        mov ebx,[rsi].IMAGE_EXPORT_DIRECTORY.AddressOfNames
        add rbx,module
        mov edi,id
        mov ecx,[rbx+rdi*4]
        add rcx,module
    .endif
    strcpy( &name, rcx )
    .if ( name == '@' || ( name == '?' && !option_cpp ) )
        .return( 0 )
    .endif

ifndef _WIN64

    .if ( !option_c )

        mov rsi,module
        mov edi,rva
        add rdi,rsi
        mov edx,[rsi].IMAGE_DOS_HEADER.e_lfanew
        mov eax,[rsi+rdx].IMAGE_NT_HEADERS.OptionalHeader.BaseOfCode
        mov ecx,[rsi+rdx].IMAGE_NT_HEADERS.OptionalHeader.SizeOfCode
        add ecx,eax
        add rax,rsi
        add rcx,rsi

        .if ( rdi > rax && rdi < rcx )

            sub rcx,rdi
            mov argcnt,get_argcnt(rdi, ecx)

        .elseif ( rdi > rcx )

            .new function:string_t
            .new forward[256]:char_t

            .if strrchr(strcpy(&forward, rdi), '.')

                mov byte ptr [rax],0
                inc rax
                mov function,rax

                .if get_module(&forward)

                    .if ( rax == module )

                        FreeLibrary( rax )
                        fprintf( fp, ";%s recursive lookup: %s.%s\n", &name, &forward, function )
                       .return( 0 )
                    .endif
                    mov module,rax
                    mov esi,[rax].IMAGE_DOS_HEADER.e_lfanew
                    mov esi,[rax+rsi].IMAGE_NT_HEADERS.OptionalHeader.DataDirectory.VirtualAddress
                    add rsi,rax

                    mov ebx,[rsi].IMAGE_EXPORT_DIRECTORY.AddressOfNames
                    add rbx,rax

                    .for ( edi = 0 : edi < [rsi].IMAGE_EXPORT_DIRECTORY.NumberOfNames : edi++, rbx+=4 )

                        mov ecx,[rbx]
                        add rcx,module

                        .ifd ( strcmp(rcx, function) == 0 )

                            mov ecx,[rsi].IMAGE_EXPORT_DIRECTORY.AddressOfNameOrdinals
                            add rcx,module

                            .for ( ebx = 0 : ebx < [rsi].IMAGE_EXPORT_DIRECTORY.NumberOfFunctions : ebx++ )

                                .if ( bx == [rcx+rdi*2] )

                                    mov eax,[rsi].IMAGE_EXPORT_DIRECTORY.AddressOfFunctions
                                    add rax,module
                                    mov ecx,[rax+rbx*4]
                                    process_function( fp, module, edi, ecx, &name )
                                   .break
                                .endif
                            .endf
                            .break
                        .endif
                    .endf
                    FreeLibrary( module )
                .endif
            .endif
            .return( 0 )
        .endif
    .endif
    .if ( argcnt != -1 )
        fprintf( fp, "%s@%d\n", &name, argcnt )
    .else
endif
        fprintf( fp, "%s\n", &name )
ifndef _WIN64
    .endif
endif
    mov eax,1
    ret

process_function endp


process_module proc uses rsi rdi rbx def_name:string_t, dll_name:string_t

   .new fp:LPFILE
   .new module:HMODULE
   .new name[256]:char_t

    .if !_access(def_name, 0)
        .if ( !option_q )
            printf( " Module Exist: %s\n", def_name )
        .endif
        .return( 0 )
    .endif

    .if !get_module(dll_name)

        .return( 1 )
    .endif
    mov module,rax

    .if ( !option_q )
        printf( " Module: %s\n", def_name )
    .endif

    .if ( fopen( def_name, "wt" ) == NULL )

        perror( def_name )
        FreeLibrary( module )
       .return( 1 )
    .endif
    mov fp,rax
    fprintf( fp, "LIBRARY %s\nEXPORTS\n", dll_name )

    mov rax,module
    mov esi,[rax].IMAGE_DOS_HEADER.e_lfanew
    mov esi,[rax+rsi].IMAGE_NT_HEADERS.OptionalHeader.DataDirectory.VirtualAddress
    add rsi,rax

    .for ( ebx = 0 : ebx < [rsi].IMAGE_EXPORT_DIRECTORY.NumberOfFunctions : ebx++ )

        .for ( edi = 0 : edi < [rsi].IMAGE_EXPORT_DIRECTORY.NumberOfNames : edi++ )

            mov ecx,[rsi].IMAGE_EXPORT_DIRECTORY.AddressOfNameOrdinals
            add rcx,module

            .if ( bx == [rcx+rdi*2] )

                mov eax,[rsi].IMAGE_EXPORT_DIRECTORY.AddressOfFunctions
                add rax,module
                mov eax,[rax+rbx*4]
                process_function( fp, module, edi, eax, 0 )
               .break
            .endif
        .endf
    .endf
    fclose( fp )
    FreeLibrary( module )
    xor eax,eax
    ret

process_module endp


write_logo proc

    .if ( !banner && !option_q && !option_n )

        mov banner,1
        _tprintf(
            "Asmc Module Definition Manager %d.%d\n"
            "Copyright (C) The Asmc Contributors. All Rights Reserved.\n\n",
            __IMPDEF__ / 100, __IMPDEF__ mod 100)
    .endif
    ret

write_logo endp


write_usage proc

    write_logo()
    _tprintf("Usage: IMPDEF [ options ] <dll_file> [ [ options ] <dll_file> ... ]\n")
    ret

write_usage endp


exit_usage proc

    write_usage()
    exit(0)

exit_usage endp


exit_options proc

    write_usage()
    _tprintf(
        "\n"
        "-q         -- Operate quietly\n"
        "-nologo    -- Suppress copyright message\n"
        "-c[-]      -- Specify C calling convention\n"
        "-c++       -- Include C++ functions\n"
        "-p<path>   -- Set output directory\n"
        "\n"
        )

    exit(0)

exit_options endp


_tmain proc argc:int_t, argv:array_t

    .new def[256]:char_t
    .new dll[256]:char_t
    .new argdef:string_t = NULL
    .new argdll:string_t = NULL
    .new fp:LPFILE

    .if ( argc == 1 )
        exit_options()
    .endif
    .for ( ebx = 1 : ebx < argc : ebx++ )

        mov rdx,argv
        mov rdi,[rdx+rbx*size_t]
        mov eax,[rdi]

        .if ( al == '-' || al == '/' )
            .switch ah
            .case 'p'
                add rdi,2
                mov option_p,rdi
               .endc
            .case 'q'
                inc option_q
            .case 'n'
                inc option_n
               .endc
            .case 'c'
                shr eax,16
                .if ( eax == '++' )
                    inc option_cpp
                .elseif ( al == '-' )
                    mov option_c,0
                .else
                    mov option_c,1
                .endif
                .endc
            .default
                exit_options()
            .endsw

        .else

            .if !strrchr( strcpy( &dll, rdi ), '.' )
                strcat( &dll, ".dll" )
            .else
                mov ecx,[rax]
                or  ecx,0x20202000
                .if ( ecx == 'fed.' || ecx == 'bil.' )
                    strcpy( rax, ".dll" )
                .endif
            .endif

            .if ( option_p )
                strcat( strcat( strcpy( &def, option_p ), "\\" ), rdi )
            .else
                strcpy( &def, rdi )
            .endif
            .if strrchr( &def, '.' )
                strcpy( rax, ".def" )
            .else
                strcat( &def, ".def" )
            .endif
            write_logo()
            process_module(&def, &dll)
        .endif
    .endf
    xor eax,eax
    ret

_tmain endp

    end _tstart
