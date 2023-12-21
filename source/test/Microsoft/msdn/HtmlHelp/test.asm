; TEST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include htmlhelp.inc
include conio.inc
include tchar.inc

.code

_tmain proc

    HtmlHelp(GetDesktopWindow(),
            "..\\..\\..\\..\\..\\bin\\asmc.chm::/index.htm>Mainwin", HH_DISPLAY_TOPIC, NULL )

    _getch()
    .return(0)

_tmain endp

    end _tstart
