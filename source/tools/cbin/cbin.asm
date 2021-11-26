; CBIN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include io.inc
include stdio.inc
include stdlib.inc
include winnt.inc
include tchar.inc

    .code

    assume rsi:ptr IMAGE_RELOCATION
    assume rdi:ptr IMAGE_SECTION_HEADER
    assume rbx:ptr IMAGE_FILE_HEADER
    assume r13:ptr IMAGE_SYMBOL
    assume r14:ptr IMAGE_RELOCATION

main proc uses rsi rdi rbx r12 r13 r14 r15 argc:int_t, argv:array_t

  local DestFile[MAX_PATH]:char_t

    .if ecx < 2
        printf(
            "Coff to BINary\n"
            "Usage: CBIN <source> [<dest>]\n"
            )
        exit(1)
    .endif
    mov rsi,rdx
    mov rbx,[rsi+8]
    lea rdi,DestFile
    .if ecx == 3
        mov rdi,[rsi+8*2]
    .else
        .if ( strrchr(strcpy(rdi, rbx), '.') == NULL )
            strcat(rdi, ".bin")
        .else
            strcpy(rax, ".bin")
        .endif
    .endif
    .if !fopen(rbx, "rb")
        perror(rbx)
       .return 2
    .endif
    mov r12,rax
    mov r13,_filelength([r12].FILE._file)
    mov rsi,malloc(r13)
    .if ( !rsi || !r13 )
        fclose(r12)
        perror(rbx)
       .return 2
    .endif
    .if !fread(rsi, r13d, 1, r12)
        fclose(r12)
        perror(rbx)
       .return 3
    .endif
    fclose(r12)
    mov r12,fopen(rdi, "wb")
    .if ( !r12 )
        perror(rdi)
       .return 4
    .endif

    mov rax,0xCCCCCCCCCCCCCCCC
    lea rdx,DestFile
    mov [rdx],rax
    mov [rdx+8],rax

    mov rbx,rsi
    mov r13d,[rbx].PointerToSymbolTable
    add r13,rbx
    movzx edi,[rbx].SizeOfOptionalHeader
    lea rdi,[rdi+rbx+IMAGE_FILE_HEADER]

    .new i:uint_t
    .for ( esi = 0, i = 0: i < [rbx].NumberOfSections: i++, rdi += IMAGE_SECTION_HEADER )

        .new segtype:byte = 0
        .if ( !memcmp(&[rdi].Name, ".text", 5) )
            mov segtype,1
        .elseif ( !memcmp(&[rdi].Name, ".data", 5) )
            mov segtype,2
        .endif

        .if ( segtype && [rdi].SizeOfRawData )

            mov r15d,[rdi].PointerToRawData
            add r15,rbx

            .if ( segtype == 1 )

                mov r14d,[rdi].PointerToRelocations
                add r14,rbx

                .new n:uint_t
                .for ( n = 0: n < [rdi].NumberOfRelocations: n++, r14 += IMAGE_RELOCATION )

                    mov eax,[r14].VirtualAddress
                    sub eax,[rdi].VirtualAddress

                    .continue .if ( eax > [rdi].SizeOfRawData )

                    imul ecx,[r14].SymbolTableIndex,IMAGE_SYMBOL
                    mov edx,[r13+rcx].IMAGE_SYMBOL.Value
                    movzx ecx,[r13+rcx].IMAGE_SYMBOL.SectionNumber
                    dec ecx
                    add edx,esi
                    .if ( ecx != i )
                        mov ecx,[rdi].SizeOfRawData
                        add ecx,15
                        and ecx,-16
                        add edx,ecx
                    .endif
                    sub edx,eax
                    add rax,r15
                    .switch [r14].Type
                    .case IMAGE_REL_I386_DIR32
                    .case IMAGE_REL_IA64_DIR32
                        sub edx,4
                        add [rax],edx
                       .endc
                    .default
                        printf("Unknown relocation type %u, address 0x%x\n", [r14].Type, [r14].VirtualAddress)
                    .endsw
                .endf
            .endif
            .if ( esi )
                lea rdx,[rsi+15]
                and edx,-16
                .if ( esi != edx )
                    sub edx,esi
                    add esi,edx
                    fwrite(&DestFile, edx, 1, r12)
                .endif
            .endif
            .if ( !fwrite(r15, [rdi].SizeOfRawData, 1, r12) )
                fclose(r12)
                perror("Write")
               .return 5
            .endif
            add esi,[rdi].SizeOfRawData
        .endif
    .endf
    fclose(r12)
   .return 0

main endp

    end _tstart
