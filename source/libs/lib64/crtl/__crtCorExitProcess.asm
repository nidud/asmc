; __CRTCOREXITPROCESS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include winbase.inc

.code

CALLBACK(PFN_EXIT_PROCESS, :UINT)

__crtCorExitProcess proc status:int_t

  local hmod:HMODULE
  local pfn:PFN_EXIT_PROCESS

    .if GetModuleHandleExW(0, L"mscoree.dll", &hmod)

        .if GetProcAddress(hmod, "CorExitProcess")

            mov pfn,rax
            pfn(status)
        .endif

        ;;
        ;; Either mscoree.dll isn't loaded,
        ;; or CorExitProcess isn't exported from mscoree.dll,
        ;; or CorExitProcess returned (should never happen).
        ;; Just call return.
        ;;
    .endif
    ret

__crtCorExitProcess endp

    end
