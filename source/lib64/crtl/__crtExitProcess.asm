; __CRTEXITPROCESS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include winbase.inc

__crtCorExitProcess proto status:int_t

.code

__crtExitProcess proc status:int_t

if defined (_CRT_APP) and ( defined(_KERNELX) EQ 0)

    __crtExitProcessWinRT()
else

if not defined(_KERNELX)
    __crtCorExitProcess(ecx)
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
