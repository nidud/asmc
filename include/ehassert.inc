
ifndef __EHASSERT_H
define __EHASSERT_H

include windef.inc

dprintf equ <>

DASSERT macro _c
    .if _c == 0
	_inconsistency()
    .endif
    endm

DEXPECT macro c
    exitm<(c)>
    endm

CHECKPTR macro p
	exitm<_ValidateRead((p), sizeof(p))>
	endm
CHECKCODE macro p
	exitm<_ValidateExecute(p)>
	endm

;BOOL
_ValidateRead		proto WINAPI :ptr, :UINT
_ValidateWrite		proto WINAPI :ptr, :UINT
_ValidateExecute	proto WINAPI :FARPROC

endif ;; __EHASSERT_H
