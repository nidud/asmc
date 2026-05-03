; MD5.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

.pragma comment(lib, crypt, ntdll)

.template MD5_CTX

    state    dd 4 dup(?)
    count    dd 2 dup(?)
    buffer   db 64 dup(?)
    digest   db 16 dup(?)
   .ends

ifdef __UNIX__
NTAPI equ <syscall>
elseifdef _WIN64
NTAPI equ <fastcall>
else
NTAPI equ <stdcall>
endif

MD5Init      proto NTAPI :ptr MD5_CTX
MD5Update    proto NTAPI :ptr MD5_CTX, :ptr byte, :dword
MD5Final     proto NTAPI :ptr MD5_CTX
