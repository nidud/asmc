; _ISNONWRITABLEINCURRENTIMAGE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include winbase.inc
include internal.inc

externdef __ImageBase:IMAGE_DOS_HEADER

    .code

_IsNonwritableInCurrentImage proc frame:__except pTarget:PBYTE

    .repeat
        ;;
        ;; Make sure __ImageBase does address a PE image.  This is likely an
        ;; unnecessary check, since we should be running from a normal image,
        ;; but it is fast, this routine is rarely called, and the normal call
        ;; is for security purposes.  If we don't have a PE image, return
        ;; failure.
        ;;
        .break .if (!_ValidateImageBase(&__ImageBase))

        ;;
        ;; Convert the targetaddress to a Relative Virtual Address (RVA) within
        ;; the image, and find the corresponding PE section.  Return failure if
        ;; the target address is not found within the current image.
        ;;
        lea rcx,__ImageBase
        mov rdx,pTarget
        sub rdx,rcx
        .break .if !_FindPESection(rcx, rdx)

        ;;
        ;; Check the section characteristics to see if the target address is
        ;; located within a writable section, returning a failure if yes.
        ;;
        mov ecx,[rax].IMAGE_SECTION_HEADER.Characteristics
        xor eax,eax
        .if !( ecx & IMAGE_SCN_MEM_WRITE )
            inc eax
        .endif

    .until 1
    ret

__except:

    ;;
    ;; Just return failure if the PE image is corrupted in any way that
    ;; triggers an AV.
    ;;
    mov  rcx,[rcx]
    xor  eax,eax
    cmp  dword ptr [rcx],STATUS_ACCESS_VIOLATION
    sete al
    retn

_IsNonwritableInCurrentImage endp

    end
