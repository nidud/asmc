; OSFILETYPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include winbase.inc

.code

osfiletype proc h:SINT
    mov eax,h
    mov eax,_osfhnd[eax*4]
    GetFileType(eax)
    ret
osfiletype endp

    end
