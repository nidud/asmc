include consx.inc

.code

getkey proc

    ReadEvent()
    PopEvent()
    ret

getkey endp

    END
