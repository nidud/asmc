; _VALIDATEIMAGEBASE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include winbase.inc

    .code

    option win64:rsp nosave noauto

_ValidateImageBase proc pImageBase:PBYTE

    .repeat

        xor eax,eax
        .break .if ([rcx].IMAGE_DOS_HEADER.e_magic != IMAGE_DOS_SIGNATURE)
        mov edx,[rcx].IMAGE_DOS_HEADER.e_lfanew
        add rdx,rcx
        .break .if ([rdx].IMAGE_NT_HEADERS.Signature != IMAGE_NT_SIGNATURE)
        lea rdx,[rdx].IMAGE_NT_HEADERS.OptionalHeader
        .break .if ([rdx].IMAGE_OPTIONAL_HEADER.Magic != IMAGE_NT_OPTIONAL_HDR_MAGIC)
        inc eax

    .until 1
    ret

_ValidateImageBase endp

    end
