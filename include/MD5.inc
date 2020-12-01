; MD5.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

.pragma comment(lib, ntdll)

MD5_CTX         STRUC
state           dd 4 dup(?)
count           dd 2 dup(?)
buffer          db 64 dup(?)
digest          db 16 dup(?)
MD5_CTX         ENDS

MD5Init         proto WINAPI :ptr MD5_CTX
MD5Update       proto WINAPI :ptr MD5_CTX, :ptr byte, :dword
MD5Final        proto WINAPI :ptr MD5_CTX
MD5Transform    proto WINAPI :ptr dword, :ptr byte, :ptr MD5_CTX
