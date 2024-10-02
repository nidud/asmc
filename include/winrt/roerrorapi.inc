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

if (NTDDI_VERSION ge NTDDI_WIN8)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

.enum RO_ERROR_REPORTING_FLAGS {
        RO_ERROR_REPORTING_NONE               = 0x00000000,
        RO_ERROR_REPORTING_SUPPRESSEXCEPTIONS = 0x00000001,
        RO_ERROR_REPORTING_FORCEEXCEPTIONS    = 0x00000002,
        RO_ERROR_REPORTING_USESETERRORINFO    = 0x00000004,
        RO_ERROR_REPORTING_SUPPRESSSETERRORINFO = 0x00000008,
}

define MAX_ERROR_MESSAGE_CHARS 512

RoGetErrorReportingFlags proto WINAPI :ptr
RoSetErrorReportingFlags proto WINAPI :UINT32

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RoResolveRestrictedErrorInfoReference proto WINAPI :PCWSTR, :ptr ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

SetRestrictedErrorInfo proto WINAPI :ptr
GetRestrictedErrorInfo proto WINAPI :ptr ptr
RoOriginateErrorW proto WINAPI :HRESULT, :UINT, :PCWSTR
RoOriginateError proto WINAPI :HRESULT, :HSTRING
RoTransformErrorW proto WINAPI :HRESULT, :HRESULT, :UINT, :PCWSTR
RoTransformError proto WINAPI :HRESULT, :HRESULT, :HSTRING
RoCaptureErrorContext proto WINAPI :HRESULT
RoFailFastWithErrorContext proto WINAPI :HRESULT

define EXCEPTION_RO_ORIGINATEERROR  (((0x1 shl 30) or (FACILITY_WINDOWS shl 16) or 0x201))
define EXCEPTION_RO_TRANSFORMERROR  (((0x1 shl 30) or (FACILITY_WINDOWS shl 16) or 0x202))

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

RoOriginateLanguageException proto WINAPI :HRESULT, :HSTRING, :ptr
RoClearError proto WINAPI
RoReportUnhandledError proto WINAPI :ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

CALLBACK(PINSPECT_MEMORY_CALLBACK, :ptr)

RoInspectThreadErrorInfo proto WINAPI :UINT_PTR, :USHORT, :PINSPECT_MEMORY_CALLBACK, :PVOID, :ptr
RoInspectCapturedStackBackTrace proto WINAPI :UINT_PTR, :USHORT, :PINSPECT_MEMORY_CALLBACK, :PVOID, :ptr, :ptr
RoGetMatchingRestrictedErrorInfo proto WINAPI :HRESULT, :ptr ptr
RoReportFailedDelegate proto WINAPI :ptr, :ptr
IsErrorPropagationEnabled proto WINAPI

endif

endif

endif
