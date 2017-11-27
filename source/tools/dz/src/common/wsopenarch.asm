include string.inc
include io.inc
include errno.inc
include wsub.inc
include dzlib.inc

    .code

wsopenarch proc wsub:ptr S_WSUB

  local arcname[1024]:byte

    mov edx,wsub
    .if osopen(
        strfcat(
            &arcname,
            [edx].S_WSUB.ws_path,
            [edx].S_WSUB.ws_file),
        _A_ARCH,
        M_RDONLY, A_OPEN) == -1
        eropen(&arcname)
    .endif
    ret

wsopenarch endp

    END
