; DLLSUPP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include crtl.inc

public  _except_list
public  _fltused
public  _ldused
public  _8087
public  _real87
public  fltused_
public  _init_387_emulator

    .data

     _8087     label byte
     _real87   label byte
     fltused_  label dword
     _init_387_emulator dd 1
     _8087cw            dw 0x127F

     _except_list       equ 0
     _fltused           equ 0x9876
     _ldused            equ 0x9876

    .code

_fltinit:

    fninit
    fwait

    fldcw _8087cw
    ret

.pragma init(_fltinit, 20)

    end
