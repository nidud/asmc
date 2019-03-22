; __CRTFLSSETVALUE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include internal.inc
include awint.inc

.code

__crtFlsSetValue proc frame dwFlsIndex:DWORD, lpFlsData:PVOID
if _CRT_NTDDI_MIN GE NTDDI_WS03
    FlsSetValue(ecx, rdx)
else
  local pfFlsSetValue:PFNFLSSETVALUE
    ;; use FlsSetValue if it is available (only on Server 2003+)...
    IFDYNAMICGETCACHEDFUNCTION(KERNEL32, PFNFLSSETVALUE, FlsSetValue, pfFlsSetValue)

        pfFlsSetValue(dwFlsIndex, lpFlsData)
    .else

        ;; ...otherwise fall back to using TlsSetValue.
        TlsSetValue(dwFlsIndex, lpFlsData)
    .endif
endif
    ret
__crtFlsSetValue endp

    end
