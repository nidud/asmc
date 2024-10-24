; _TSYSTEMDATETOSTRING.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winnls.inc

    .code

SystemDateToString proc uses rbx string:LPTSTR, date:ptr SYSTEMTIME

    ldr rbx,string

ifndef __UNIX__
ifdef _UNICODE
    GetDateFormatEx(NULL, DATE_SHORTDATE, ldr(date), NULL, rbx, 11, NULL)
else
   .new dateString[64]:wchar_t

    GetDateFormatEx(NULL, DATE_SHORTDATE, ldr(date), NULL, &dateString, lengthof(dateString), NULL)

    .for ( ecx = 0 : ecx < 10 : ecx++ )

        mov al,byte ptr dateString[rcx*2]
        mov [rbx+rcx],al
    .endf
    mov byte ptr [rbx+rcx],0
endif
endif
   mov rax,rbx
   ret

SystemDateToString endp

    end
