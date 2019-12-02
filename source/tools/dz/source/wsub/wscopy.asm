include io.inc
include errno.inc
include wsub.inc

extrn copy_jump:dword

.code

wscopyremove proc file:LPSTR
    ioclose(&STDO)
    remove(file)
    or eax,-1
    ret
wscopyremove endp

wscopyopen proc srcfile:LPSTR, outfile:LPSTR

    mov errno,0
    .if !ioopen(&STDO, outfile, M_WRONLY, OO_MEM64K)
        mov copy_jump,1
    .elseif eax != -1

        ioopen(&STDI, srcfile, M_RDONLY, OO_MEM64K)
        or STDI.S_IOST.ios_flag,IO_USECRC

        .if eax == -1

            eropen(srcfile)
            wscopyremove(outfile)
        .endif
    .endif
    ret

wscopyopen endp

    end
