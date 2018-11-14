; DLOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code
    assume ebx: ptr S_DOBJ

dlopen proc uses ebx dobj:ptr S_DOBJ, at, ttl:LPSTR
    mov ebx,dobj
    rcopen([ebx].dl_rect, [ebx].dl_flag, at, ttl, [ebx].dl_wp)
    mov [ebx].dl_wp,eax
    .if eax
        or  [ebx].dl_flag,_D_DOPEN
        mov eax,1
    .endif
    ret
dlopen endp

    END
