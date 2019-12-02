include string.inc
include wsub.inc

    .code

wsearch proc uses esi edi wsub:ptr S_WSUB, string:LPSTR
    mov eax,wsub
    mov esi,[eax].S_WSUB.ws_count
    mov edi,[eax].S_WSUB.ws_fcb
    .repeat
        mov eax,-1
        .break .if !esi
        dec esi
        mov eax,[edi]
        add eax,S_FBLK.fb_name
        add edi,4
        .continue(0) .if _stricmp(string, eax)
        mov eax,wsub
        mov eax,[eax].S_WSUB.ws_count
        sub eax,esi
        dec eax
    .until 1
    ret
wsearch endp

    END
