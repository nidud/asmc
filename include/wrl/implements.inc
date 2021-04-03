ifndef _WRL_IMPLEMENTS_H_
_WRL_IMPLEMENTS_H_ equ <>

include inspectable.inc
include roapi.inc
ifdef BUILD_WINDOWS
include winrt.inc
endif
include activation.inc
include WinString.inc

include new.inc
include weakreference.inc
include objbase.inc
include cguid.inc
include intrin.inc

include wrl\def.inc
include wrl\client.inc

if (NTDDI_VERSION GE NTDDI_WINBLUE)
include roerrorapi.inc
endif

ifndef __WRL_NO_DEFAULT_LIB__
.pragma comment(lib, ole32)
endif

.enum RuntimeClassType {
    WinRt		    = 0x0001,
    ClassicCom		    = 0x0002,
    WinRtClassicComMix	    = WinRt or ClassicCom,
    InhibitWeakReference    = 0x0004,
    Delegate		    = ClassicCom,
    InhibitFtmBase	    = 0x0008,
    InhibitRoOriginateError = 0x0010
    }


endif
