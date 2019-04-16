; __CRTEXITPROCESS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include winbase.inc

__crtCorExitProcess proto WINAPI status:int_t

.code

__crtExitProcess proc WINAPI status:int_t

if defined (_CRT_APP) and not defined(_KERNELX)

    __crtExitProcessWinRT()
else

ifndef _KERNELX
    __crtCorExitProcess(status)
endif

    ;;
    ;; Either mscoree.dll isn't loaded,
    ;; or CorExitProcess isn't exported from mscoree.dll,
    ;; or CorExitProcess returned (should never happen).
    ;; Just call ExitProcess.
    ;;
    ExitProcess(status)
endif
__crtExitProcess endp

    end
