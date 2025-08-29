ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __wmdmlog_h__
define __wmdmlog_h__

include oaidl.inc
include ocidl.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

define WMDM_LOG_SEV_INFO             0x00000001
define WMDM_LOG_SEV_WARN             0x00000002
define WMDM_LOG_SEV_ERROR            0x00000004
define WMDM_LOG_NOTIMESTAMP          0x00000010

ifndef __IWMDMLogger_INTERFACE_DEFINED__
define __IWMDMLogger_INTERFACE_DEFINED__

DEFINE_IIDX(IWMDMLogger, "110A3200-5A79-11d3-8D78-444553540000")

.comdef IWMDMLogger : public IUnknown
    IsEnabled           proc :ptr
    Enable              proc :BOOL
    GetLogFileName      proc :LPSTR, :UINT
    SetLogFileName      proc :LPSTR
    LogString           proc :DWORD, :LPSTR, :LPSTR
    LogDword            proc :DWORD, :LPSTR, :LPSTR, :DWORD
    Reset               proc
    GetSizeParams       proc :LPDWORD, :LPDWORD
    SetSizeParams       proc :DWORD, :DWORD
   .ends

endif

ifndef __WMDMLogLib_LIBRARY_DEFINED__
define __WMDMLogLib_LIBRARY_DEFINED__

DEFINE_GUID(LIBID_WMDMLogLib, 0x110A3201,0x5A79,0x11d3,0x8D,0x78,0x44,0x45,0x53,0x54,0x00,0x00)
DEFINE_GUID(CLSID_WMDMLogger, 0x110A3202,0x5A79,0x11d3,0x8D,0x78,0x44,0x45,0x53,0x54,0x00,0x00)

endif

endif

endif
