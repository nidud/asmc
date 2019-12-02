; __MKTEMPNAME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *GetTempName(char *buffer, char *type);
;

include stdio.inc
include time.inc
include winbase.inc
include stdlib.inc

    .code

__mktempname proc buffer:string_t, type:string_t

  local t:SYSTEMTIME

    GetLocalTime(&t)

    .if !getenv("TEMP")

        lea eax,@CStr(".")
    .endif

    mov cx,t.wYear
    sub cx,2000
    shl ecx,4
    or  cx,t.wMonth
    shl ecx,5
    or  cx,t.wDay
    shl ecx,5
    or  cx,t.wHour
    shl ecx,6
    or  cx,t.wMinute
    shl ecx,6
    or  cx,t.wSecond
    shl ecx,3
    mov dx,t.wMilliseconds
    and edx,111B
    or  ecx,edx

    sprintf(buffer, "%s\\tmp_%08X.%s", eax, ecx, type)
    mov eax,buffer
    ret

__mktempname endp

    end
