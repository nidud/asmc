ifndef _WRL_MODULE_H_
_WRL_MODULE_H_ equ <>

include roapi.inc
ifdef BUILD_WINDOWS
include winrt.inc
endif
include activation.inc
include WinString.inc
include intrin.inc
include winapifamily.inc

include wrl\def.inc
include wrl\internal.inc
include wrl\client.inc
include wrl\implements.inc
include wrl\ftm.inc
include wrl\wrappers\corewrappers.inc

.enum ModuleType {
    InProc		     = 0x1,
    OutOfProc		     = 0x2,
    DisableCaching	     = 0x4,
    InProcDisableCaching     = InProc or DisableCaching,
    OutOfProcDisableCaching  = OutOfProc or DisableCaching
    }

.enum FactoryCacheFlags {
    FactoryCacheDefault,
    FactoryCacheEnabled,
    FactoryCacheDisabled
    }

endif
