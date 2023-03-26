; _MSGBOX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include conio.inc
include tchar.inc

.code

_tmain proc argc:int_t, argv:array_t


    _msgbox(MB_CANCELTRYCONTINUE or MB_DEFBUTTON3,
            "_msgbox()",
            "MB_CANCELTRYCONTINUE or MB_DEFBUTTON3\n"
            "\n"
            "Return value:    \n"
            "\n"
            "IDCANCEL      %2d\n"
            "IDTRYAGAIN    %2d\n"
            "IDCONTINUE    %2d\n",
            IDCANCEL, IDTRYAGAIN, IDCONTINUE )

    _msgbox(MB_OK or MB_USERICON, "_msgbox()", "return value: %d", eax )

    .return(0)

_tmain endp

    end
