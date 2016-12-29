ifndef __LIBC_INC
 include libc.inc
endif

.xlist

S_JMPBUF STRUC
IFDEF _WIN64
 J_RBP	dq ?
 J_RBX	dq ?
 J_RDI	dq ?
 J_RSI	dq ?
 J_R12	dq ?
 J_R13	dq ?
 J_R14	dq ?
 J_R15	dq ?
 J_RSP	dq ?
 J_RIP	dq ?
ELSE
 J_EBP	dd ?
 J_EBX	dd ?
 J_EDI	dd ?
 J_ESI	dd ?
 J_ESP	dd ?
 J_EIP	dd ?
 J_EDX	dd ?
 J_ECX	dd ?
ENDIF
S_JMPBUF ENDS

setjmp	PROTO _CDecl :PTR S_JMPBUF
longjmp PROTO _CDecl :PTR S_JMPBUF, :SIZE_T

.list
