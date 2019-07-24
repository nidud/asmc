.pragma list(push, 0)

ifndef __LIBC_INC
 include libc.inc
endif

JMPBUF STRUC
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
JMPBUF ENDS
jmp_buf typedef ptr JMPBUF

_setjmp PROTO __cdecl :jmp_buf
longjmp PROTO __cdecl :jmp_buf, :int_t

.pragma list(pop)
