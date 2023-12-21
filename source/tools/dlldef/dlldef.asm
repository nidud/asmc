include string.inc
include stdio.inc
include stdlib.inc
include winbase.inc
include tchar.inc

    .code

main proc argc:SINT, argv:ptr

    .new fp:ptr FILE
    .new dll:string_t
    .new def[128]:char_t
    .new ms:char_t = 0

    .if ( argc >= 2 )

        mov rdx,argv
        mov rsi,[rdx+size_t]
        mov eax,[rsi]
        .if eax == 'sm-'
            inc ms
            mov rsi,[rdx+size_t*2]
        .endif
        mov dll,rsi
        .if LoadLibrary(rsi)

            mov rdi,rax
            strcpy(strrchr(strcpy(&def, rsi), '.'), ".def")

            .if fopen(&def,"wt")

                mov fp,rax
                .if ( ms )
                    fprintf(fp, "LIBRARY %s\nEXPORTS\n", rsi)
                .endif
                mov eax,[rdi].IMAGE_DOS_HEADER.e_lfanew
                mov eax,[rdi+rax].IMAGE_NT_HEADERS.OptionalHeader.DataDirectory.VirtualAddress
                mov ebx,[rdi+rax].IMAGE_EXPORT_DIRECTORY.NumberOfNames
                mov esi,[rdi+rax].IMAGE_EXPORT_DIRECTORY.AddressOfNames
                add rsi,rdi

                .while ebx

                    lodsd
ifdef _WIN64
                    .if ( ms )
                        fprintf(fp, "%s\n", addr [rax+rdi])
                    .else
                        fprintf(fp, "++%s.'%s'\n", addr [rax+rdi], dll)
                    .endif
else
                   .new name:string_t
                   .new args:int_t

                    mov args,0
                    add eax,edi
                    mov name,eax
                    push edi

                    .repeat

                        .if ( GetProcAddress(edi, name) )

                            mov edx,eax
                            mov ecx,[edi].IMAGE_DOS_HEADER.e_lfanew
                            mov ecx,[edi+ecx].IMAGE_NT_HEADERS.OptionalHeader.SizeOfImage
                            sub eax,edi
                           .break .ifs
                            sub ecx,eax
                           .break .ifs
                            mov edi,edx
                            mov eax,0xC2 ; ret

                            .while 1

                                repnz scasb
                                .break .ifnz

                                mov edx,[edi]
                                .continue .if ( dh || ( dl & 3 ) )

                                movzx ecx,byte ptr [edi]
                                mov args,ecx
                               .break
                            .endw
                        .endif
                    .until 1
                    pop edi
                    .if ( ms )
                        fprintf( fp, "%s@%d\n", name, args )
                    .else
                        fprintf( fp, "++_%s@%d.'%s'\n", name, args, dll )
                    .endif
endif
                    dec ebx
                .endw
                fclose(fp)
            .endif
            FreeLibrary(rdi)
        .endif
    .else
        printf("\nUsage: DLLDEF [-ms] <dll_name>\n\n")
    .endif
    .return(0)

main endp

    end _tstart
