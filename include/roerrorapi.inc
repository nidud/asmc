ifndef _ROERROR_H
define _ROERROR_H

ifdef _CONTRACT_GEN
include nt.inc
include ntrtl.inc
include nturtl.inc
endif

include apiset.inc
include apisetcconv.inc
include hstring.inc
include restrictedErrorInfo.inc
include rpc.inc

include sdkddkver.inc

if (NTDDI_VERSION GE NTDDI_WIN8)

ifndef _APISET_RO_ERROR_VER
ifdef _APISET_MINCORE_VERSION
if _APISET_MINCORE_VERSION GE 0x0101
_APISET_RO_ERROR_VER	equ 0x0101
elseif _APISET_MINCORE_VERSION GE 0x0100
_APISET_RO_ERROR_VER	equ 0x0100
endif
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum RO_ERROR_REPORTING_FLAGS {
    RO_ERROR_REPORTING_NONE		  = 0x00000000,
    RO_ERROR_REPORTING_SUPPRESSEXCEPTIONS = 0x00000001,
    RO_ERROR_REPORTING_FORCEEXCEPTIONS	  = 0x00000002,
    RO_ERROR_REPORTING_USESETERRORINFO	  = 0x00000004,
    RO_ERROR_REPORTING_SUPPRESSSETERRORINFO = 0x00000008,
    }

MAX_ERROR_MESSAGE_CHARS equ 512

RoGetErrorReportingFlags proto WINAPI \
		pflags: ptr UINT32

RoSetErrorReportingFlags proto WINAPI \
		 flags: UINT32

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

RoResolveRestrictedErrorInfoReference proto WINAPI \
	     reference: PCWSTR,
 ppRestrictedErrorInfo: ptr IRestrictedErrorInfo

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

SetRestrictedErrorInfo proto WINAPI \
  pRestrictedErrorInfo: ptr IRestrictedErrorInfo

GetRestrictedErrorInfo proto WINAPI \
 ppRestrictedErrorInfo: ptr IRestrictedErrorInfo

RoOriginateErrorW proto WINAPI \
		 error: HRESULT,
		cchMax: UINT,
	       message: PCWSTR

RoOriginateError proto WINAPI \
		 error: HRESULT,
	       message: HSTRING

RoTransformErrorW proto WINAPI \
	      oldError: HRESULT,
	      newError: HRESULT,
		cchMax: UINT,
	       message: PCWSTR

RoTransformError proto WINAPI \
	      oldError: HRESULT,
	      newError: HRESULT,
	       message: HSTRING

RoCaptureErrorContext proto WINAPI \
		    hr: HRESULT

RoFailFastWithErrorContext proto WINAPI \
	       hrError: HRESULT

EXCEPTION_RO_ORIGINATEERROR equ (((0x1 SHL 30) OR (FACILITY_WINDOWS SHL 16) OR 0x201))
EXCEPTION_RO_TRANSFORMERROR equ (((0x1 SHL 30) OR (FACILITY_WINDOWS SHL 16) OR 0x202))

endif

if NOT defined(_CONTRACT_GEN) OR (_APISET_RO_ERROR_VER GE 0x0101)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

RoOriginateLanguageException proto WINAPI \
		 error: HRESULT,
	       message: HSTRING,
     languageException: ptr IUnknown

RoClearError proto WINAPI

RoReportUnhandledError proto WINAPI \
  pRestrictedErrorInfo: ptr IRestrictedErrorInfo

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

CALLBACK(PINSPECT_MEMORY_CALLBACK, :ptr, :UINT_PTR, :UINT32, :ptr BYTE)

RoInspectThreadErrorInfo proto WINAPI \
      targetTebAddress: UINT_PTR,
	       machine: USHORT,
    readMemoryCallback: PINSPECT_MEMORY_CALLBACK,
	       context: PVOID,
 targetErrorInfoAddress: ptr UINT_PTR


RoInspectCapturedStackBackTrace proto WINAPI \
targetErrorInfoAddress: UINT_PTR,
	       machine: USHORT,
    readMemoryCallback: PINSPECT_MEMORY_CALLBACK,
	       context: PVOID,
	    frameCount: ptr UINT32,
 targetBackTraceAddress: ptr UINT_PTR

RoGetMatchingRestrictedErrorInfo proto WINAPI \
		  hrIn: HRESULT,
 ppRestrictedErrorInfo: ptr IRestrictedErrorInfo

RoReportFailedDelegate proto WINAPI \
	  punkDelegate: ptr IUnknown,
  pRestrictedErrorInfo: ptr IRestrictedErrorInfo

IsErrorPropagationEnabled proto WINAPI

endif

endif

endif

endif
