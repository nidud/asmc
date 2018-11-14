; _CONTROL87.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include float.inc

.code

_control87 proc __cdecl newval:UINT, unmask:UINT

  local cw:word

    fstcw cw
    movzx eax,cw

    ;; Convert into mask constants

    xor ecx,ecx
    .if eax & 0x1
        or ecx,_EM_INVALID
    .endif
    .if eax & 0x2
        or ecx,_EM_DENORMAL
    .endif
    .if eax & 0x4
        or ecx,_EM_ZERODIVIDE
    .endif
    .if eax & 0x8
        or ecx,_EM_OVERFLOW
    .endif
    .if eax & 0x10
        or ecx,_EM_UNDERFLOW
    .endif
    .if eax & 0x20
        or ecx,_EM_INEXACT
    .endif

    mov edx,eax
    and eax,0xC00
    .switch eax
      .case 0xC00: or ecx,_RC_UP or _RC_DOWN: .endc
      .case 0x800: or ecx,_RC_UP:             .endc
      .case 0x400: or ecx,_RC_DOWN:           .endc
    .endsw

    mov eax,edx
    and eax,0x300
    .switch eax
      .case 0x0:   or ecx,_PC_24: .endc
      .case 0x200: or ecx,_PC_53: .endc
      .case 0x300: or ecx,_PC_64: .endc
    .endsw

    .if edx & 0x1000
        or ecx,_IC_AFFINE
    .endif

    ;; Mask with parameters

    mov eax,unmask
    not eax
    and ecx,eax
    mov eax,newval
    and eax,unmask
    or  ecx,eax

    ;; Convert (masked) value back to fp word

    xor eax,eax
    .if ecx & _EM_INVALID
        or eax,0x1
    .endif
    .if ecx & _EM_DENORMAL
        or eax,0x2
    .endif
    .if ecx & _EM_ZERODIVIDE
        or eax,0x4
    .endif
    .if ecx & _EM_OVERFLOW
        or eax,0x8
    .endif
    .if ecx & _EM_UNDERFLOW
        or eax,0x10
    .endif
    .if ecx & _EM_INEXACT
        or eax,0x20
    .endif

    mov edx,ecx
    and edx,_RC_UP or _RC_DOWN
    .switch edx
      .case _RC_UP or _RC_DOWN: or eax,0xC00: .endc
      .case _RC_UP:             or eax,0x800: .endc
      .case _RC_DOWN:           or eax,0x400: .endc
    .endsw

    mov edx,ecx
    and edx,_PC_24 or _PC_53
    .switch edx
      .case _PC_64: or eax,0x300: .endc
      .case _PC_53: or eax,0x200: .endc
      .case _PC_24: or eax,0x0  : .endc
    .endsw

    .if ecx & _IC_AFFINE
        or eax,0x1000
    .endif

    mov cw,ax
    fldcw cw

    ret

_control87 endp

    end
