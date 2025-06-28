; _ARGV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include winbase.inc

.data
 __argv LPSTR 0

.code

__initargv proc private

  local pgname[260]:TCHAR

    ret

__initargv endp

.pragma init(__initargv, 4)

    end
