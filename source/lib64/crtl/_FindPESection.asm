; _FINDPESECTION.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include winbase.inc

    .code

    option win64:rsp nosave noauto

_FindPESection proc pImageBase:PBYTE, rva:DWORD_PTR

    .repeat

        mov r8d,[rcx].IMAGE_DOS_HEADER.e_lfanew
        add r8,rcx
        ;;
        ;; Find the section holding the desired address.  We make no assumptions
        ;; here about the sort order of the section descriptors (though they
        ;; always appear to be sorted by ascending section RVA).
        ;;
        assume r8 :ptr IMAGE_NT_HEADERS
        assume r10:ptr IMAGE_SECTION_HEADER

        .for ( r9d = 0, r10 = IMAGE_FIRST_SECTION(r8) : r9w < [r8].FileHeader.NumberOfSections :,
               r9d++, r10 += sizeof(IMAGE_SECTION_HEADER) )

            mov eax,[r10].VirtualAddress
            add eax,[r10].Misc.VirtualSize
            .if (edx >= [r10].VirtualAddress && edx <  eax)

                ;;
                ;; Section found
                ;;
                mov rax,r10
                .break(1)
            .endif
        .endf
        ;;
        ;; Section not found
        ;;
        xor eax,eax
    .until 1
    ret

_FindPESection endp

    end
