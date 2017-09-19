include string.inc
include alloc.inc
include wsub.inc
include direct.inc
include dzlib.inc

WSSIZE equ WMAXPATH + _MAX_PATH*3

    .code

    assume esi:ptr S_WSUB

wsopen proc uses esi wsub:ptr S_WSUB

    mov esi,wsub

    .repeat

        .if !([esi].ws_flag & _W_MALLOC)

            malloc(WSSIZE)
            .break .ifz
            memset(eax, 0, WSSIZE)
            mov [esi].ws_path,eax
            add eax,WMAXPATH
            mov [esi].ws_arch,eax
            add eax,_MAX_PATH
            mov [esi].ws_file,eax
            add eax,_MAX_PATH
            mov [esi].ws_mask,eax
            xor eax,eax
            mov [esi].ws_count,eax
            mov [esi].ws_fcb,eax
            or  [esi].ws_flag,_W_MALLOC
        .endif

        free([esi].ws_fcb)
        mov eax,[esi].ws_maxfb
        shl eax,2
        push eax
        malloc(eax)
        pop ecx
        mov [esi].ws_fcb,eax
        .ifnz
            memset(eax, 0, ecx)
            xor eax,eax
            inc eax
        .endif
    .until 1
    ret

wsopen endp

    END
