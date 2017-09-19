; CMCLRCMDL.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

    .code

cmclrcmdl proc
    .if cflag & _C_ESCUSERSCR
	cmtoggleon()
    .endif
    clrcmdl()
    ret
cmclrcmdl endp

    END
