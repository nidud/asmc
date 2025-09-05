ifndef _RPC500_
include rpc500.inc
endif
ifndef __tsuserex_h__
define __tsuserex_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
include mmc.inc
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __TSUSEREXLib_LIBRARY_DEFINED__
define __TSUSEREXLib_LIBRARY_DEFINED__

DEFINE_GUID(LIBID_TSUSEREXLib, 0x45413F04,0xDF86,0x11D1,0xAE,0x27,0x00,0xC0,0x4F,0xA3,0x58,0x13)

DEFINE_GUIDS(CLSID_TSUserExInterfaces, "0910dd01-df8c-11d1-ae27-00c04fa35813")

ifndef __IADsTSUserEx_INTERFACE_DEFINED__
define __IADsTSUserEx_INTERFACE_DEFINED__

DEFINE_IIDX(IADsTSUserEx, "C4930E79-2989-4462-8A60-2FCF2F2955EF")

.comdef IADsTSUserEx : public IDispatch
    get_TerminalServicesProfilePath proc :ptr
    put_TerminalServicesProfilePath proc :BSTR
    get_TerminalServicesHomeDirectory proc :ptr
    put_TerminalServicesHomeDirectory proc :BSTR
    get_TerminalServicesHomeDrive proc :ptr
    put_TerminalServicesHomeDrive proc :BSTR
    get_AllowLogon      proc :ptr
    put_AllowLogon      proc :LONG
    get_EnableRemoteControl proc :ptr
    put_EnableRemoteControl proc :LONG
    get_MaxDisconnectionTime proc :ptr
    put_MaxDisconnectionTime proc :LONG
    get_MaxConnectionTime proc :ptr
    put_MaxConnectionTime proc :LONG
    get_MaxIdleTime     proc :ptr
    put_MaxIdleTime     proc :LONG
    get_ReconnectionAction proc :ptr
    put_ReconnectionAction proc :LONG
    get_BrokenConnectionAction proc :ptr
    put_BrokenConnectionAction proc :LONG
    get_ConnectClientDrivesAtLogon proc :ptr
    put_ConnectClientDrivesAtLogon proc :LONG
    get_ConnectClientPrintersAtLogon proc :ptr
    put_ConnectClientPrintersAtLogon proc :LONG
    get_DefaultToMainPrinter proc :ptr
    put_DefaultToMainPrinter proc :LONG
    get_TerminalServicesWorkDirectory proc :ptr
    put_TerminalServicesWorkDirectory proc :BSTR
    get_TerminalServicesInitialProgram proc :ptr
    put_TerminalServicesInitialProgram proc :BSTR
   .ends

endif

DEFINE_GUIDS(CLSID_ADsTSUserEx, "E2E9CAE6-1E7B-4B8E-BABD-E9BF6292AC29")

endif

endif

endif
