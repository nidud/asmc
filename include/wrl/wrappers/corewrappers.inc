ifndef _WRL_COREWRAPPERS_H_
_WRL_COREWRAPPERS_H_ equ <>

include windows.inc
include intsafe.inc
include winstring.inc
include roapi.inc
ifdef BUILD_WINDOWS
include winrt.inc
endif

include wrl\def.inc
include wrl\internal.inc

endif
