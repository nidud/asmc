; SYSTEMDATETOSTRINGA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; DMY:dd.mm.yyyy, MDY:mm/dd/yyyy, YMD:yyyy/mm/dd
;
include time.inc
include winnls.inc

    .code

SystemDateToStringA proc string:ptr char_t, date:ptr SYSTEMTIME
if (_WIN32_WINNT GE _WIN32_WINNT_VISTA)
   .new dateString[64]:wchar_t
    GetDateFormatEx(NULL, DATE_SHORTDATE, date, NULL, &dateString, lengthof(dateString), NULL)
    .for ( edx = string, ecx = 0 : ecx < 10 : ecx++ )
        mov al,byte ptr dateString[ecx*2]
        mov [edx+ecx],al
    .endf
    mov byte ptr [edx+ecx],0
else
    mov ecx,GetUserDefaultLCID()
    GetDateFormatA(ecx, DATE_SHORTDATE, date, NULL, string, 11)
endif
    .return( string )

SystemDateToStringA endp

    END
