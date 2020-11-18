ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __wbemtran_h__
__wbemtran_h__ equ <>

ifndef __IWbemTransport_FWD_DEFINED__
__IWbemTransport_FWD_DEFINED__ equ 1
endif
ifndef __IWbemLevel1Login_FWD_DEFINED__
__IWbemLevel1Login_FWD_DEFINED__ equ 1
endif
ifndef __IWbemConnectorLogin_FWD_DEFINED__
__IWbemConnectorLogin_FWD_DEFINED__ equ 1
endif
ifndef __IWbemAddressResolution_FWD_DEFINED__
__IWbemAddressResolution_FWD_DEFINED__ equ 1
endif
ifndef __WbemLevel1Login_FWD_DEFINED__
__WbemLevel1Login_FWD_DEFINED__ equ 1
endif
ifndef __WbemLocalAddrRes_FWD_DEFINED__
__WbemLocalAddrRes_FWD_DEFINED__ equ 1
endif
ifndef __WbemUninitializedClassObject_FWD_DEFINED__
__WbemUninitializedClassObject_FWD_DEFINED__ equ 1
endif
ifndef __IWbemClientTransport_FWD_DEFINED__
__IWbemClientTransport_FWD_DEFINED__ equ 1
endif
ifndef __IWbemClientConnectionTransport_FWD_DEFINED__
__IWbemClientConnectionTransport_FWD_DEFINED__ equ 1
endif
ifndef __WbemDCOMTransport_FWD_DEFINED__
__WbemDCOMTransport_FWD_DEFINED__ equ 1
endif
ifndef __IWbemLevel1Login_FWD_DEFINED__
__IWbemLevel1Login_FWD_DEFINED__ equ 1
endif
ifndef __IWbemConnectorLogin_FWD_DEFINED__
__IWbemConnectorLogin_FWD_DEFINED__ equ 1
endif
ifndef __IWbemAddressResolution_FWD_DEFINED__
__IWbemAddressResolution_FWD_DEFINED__ equ 1
endif
ifndef __IWbemTransport_FWD_DEFINED__
__IWbemTransport_FWD_DEFINED__ equ 1
endif
ifndef __IWbemConstructClassObject_FWD_DEFINED__
__IWbemConstructClassObject_FWD_DEFINED__ equ 1
endif
ifndef __IWbemClientTransport_FWD_DEFINED__
__IWbemClientTransport_FWD_DEFINED__ equ 1
endif
ifndef __IWbemClientConnectionTransport_FWD_DEFINED__
__IWbemClientConnectionTransport_FWD_DEFINED__ equ 1
endif

include objidl.inc
include oleidl.inc
include oaidl.inc
include wbemcli.inc
include winapifamily.inc


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __WbemTransports_v1_LIBRARY_DEFINED__
__WbemTransports_v1_LIBRARY_DEFINED__ equ 1

.enum WBEM_LOGIN_TYPE {
    WBEM_FLAG_INPROC_LOGIN	= 0,
    WBEM_FLAG_LOCAL_LOGIN	= 1,
    WBEM_FLAG_REMOTE_LOGIN	= 2,
    WBEM_AUTHENTICATION_METHOD_MASK	= 0xf,
    WBEM_FLAG_USE_MULTIPLE_CHALLENGES	= 0x10
    }

WBEM_128BITS typedef ptr BYTE

externdef LIBID_WbemTransports_v1:IID

ifndef __IWbemTransport_INTERFACE_DEFINED__
__IWbemTransport_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IWbemTransport, "553fe584-2156-11d0-b6ae-00aa003240c7")

.comdef IWbemTransport : public IUnknown

    Initialize		proc
    .ends

endif

ifndef __IWbemLevel1Login_INTERFACE_DEFINED__
__IWbemLevel1Login_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IWbemLevel1Login, "F309AD18-D86A-11d0-A075-00C04FB68820")

.comdef IWbemLevel1Login : public IUnknown

    EstablishPosition	proc :LPWSTR, :DWORD, :ptr
    RequestChallenge	proc :LPWSTR, :LPWSTR, :WBEM_128BITS
    WBEMLogin		proc :LPWSTR, :WBEM_128BITS, :LONG, :ptr, :ptr
    NTLMLogin		proc :LPWSTR, :LPWSTR, :LONG, :ptr, :ptr
    .ends

endif

ifndef __IWbemConnectorLogin_INTERFACE_DEFINED__
__IWbemConnectorLogin_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IWbemConnectorLogin, "d8ec9cb1-b135-4f10-8b1b-c7188bb0d186")

.comdef IWbemConnectorLogin : public IUnknown

    ConnectorLogin	proc :LPWSTR, :LPWSTR, :LONG, :ptr, :REFIID, :ptr
    .ends

endif

ifndef __IWbemAddressResolution_INTERFACE_DEFINED__
__IWbemAddressResolution_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IWbemAddressResolution, "F7CE2E12-8C90-11d1-9E7B-00C04FC324A8")

.comdef IWbemAddressResolution : public IUnknown

    Resolve		proc :LPWSTR, :LPWSTR, :ptr, :ptr
    .ends

endif

DEFINE_GUIDS(CLSID_WbemLevel1Login, "8BC3F05E-D86B-11d0-A075-00C04FB68820")
DEFINE_GUIDS(CLSID_WbemLocalAddrRes, "A1044801-8F7E-11d1-9E7C-00C04FC324A8")
DEFINE_GUIDS(CLSID_WbemUninitializedClassObject, "7a0227f6-7108-11d1-ad90-00c04fd8fdff")

ifndef __IWbemClientTransport_INTERFACE_DEFINED__
__IWbemClientTransport_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IWbemClientTransport, "F7CE2E11-8C90-11d1-9E7B-00C04FC324A8")

.comdef IWbemClientTransport : public IUnknown

    ConnectServer	proc :BSTR, :DWORD, :ptr, :BSTR, :BSTR, :BSTR, :BSTR, :LONG, :BSTR, :ptr, :ptr
    .ends

endif

ifndef __IWbemClientConnectionTransport_INTERFACE_DEFINED__
__IWbemClientConnectionTransport_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IWbemClientConnectionTransport, "a889c72a-fcc1-4a9e-af61-ed071333fb5b")

.comdef IWbemClientConnectionTransport : public IUnknown

    Open		proc :BSTR, :DWORD, :ptr, :BSTR, :BSTR, :BSTR, :BSTR, :LONG, :ptr, :REFIID, :ptr, :ptr
    OpenAsync		proc :BSTR, :DWORD, :ptr, :BSTR, :BSTR, :BSTR, :BSTR, :LONG, :ptr, :REFIID, :ptr
    Cancel		proc :LONG, :ptr
    .ends

endif

DEFINE_GUIDS(CLSID_WbemDCOMTransport, "F7CE2E13-8C90-11d1-9E7B-00C04FC324A8")

endif

ifndef __IWbemConstructClassObject_INTERFACE_DEFINED__
__IWbemConstructClassObject_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IWbemConstructClassObject, "9ef76194-70d5-11d1-ad90-00c04fd8fdff")

.comdef IWbemConstructClassObject : public IUnknown

    SetInheritanceChain proc :LONG, :ptr
    SetPropertyOrigin	proc :LPCWSTR, :LONG
    SetMethodOrigin	proc :LPCWSTR, :LONG
    SetServerNamespace	proc :LPCWSTR, :LPCWSTR
    .ends

endif

endif

endif
