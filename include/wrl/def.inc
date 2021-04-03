ifndef _WRL_DEF_H_
_WRL_DEF_H_ equ <>

include sdkddkver.inc
include sal.inc

if _MSC_VER LT 1600
;.err <WRL requires compiler version 16.00 or greater>
endif

if NTDDI_VERSION LT NTDDI_VISTA
.err <WRL requires NTDDI_VERSION to be #defined at least to NTDDI_VISTA or greater>
endif

ifdef _M_IA64
.err <WRL doesn't support IA64 architecture>
endif

if (( not defined(_PREFAST_) or (_MSC_FULL_VER ge 160021202)) )
else
nullptr  equ 0
endif

endif
