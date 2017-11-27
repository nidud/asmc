include io.inc
include winbase.inc

.code

remove proc file:LPSTR

    .if DeleteFileA(file)

        xor eax,eax
ifdef __DZ__
        mov _diskflag,1
endif
    .else
        osmaperr()
    .endif
    ret

remove endp

    end
