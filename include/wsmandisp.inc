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

ifndef __wsmandisp_h__
define __wsmandisp_h__

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_PKG_WINMGMT)

ifndef __WSManAutomation_LIBRARY_DEFINED__
define __WSManAutomation_LIBRARY_DEFINED__

.enum WSManSessionFlags {
	WSManFlagUTF8	= 0x1,
	WSManFlagCredUsernamePassword	= 0x1000,
	WSManFlagSkipCACheck	= 0x2000,
	WSManFlagSkipCNCheck	= 0x4000,
	WSManFlagUseNoAuthentication	= 0x8000,
	WSManFlagUseDigest	= 0x10000,
	WSManFlagUseNegotiate	= 0x20000,
	WSManFlagUseBasic	= 0x40000,
	WSManFlagUseKerberos	= 0x80000,
	WSManFlagNoEncryption	= 0x100000,
	WSManFlagUseClientCertificate	= 0x200000,
	WSManFlagEnableSPNServerPort	= 0x400000,
	WSManFlagUTF16	= 0x800000,
	WSManFlagUseCredSsp	= 0x1000000,
	WSManFlagSkipRevocationCheck	= 0x2000000,
	WSManFlagAllowNegotiateImplicitCredentials	= 0x4000000,
	WSManFlagUseSsl = 0x8000000
	}

.enum WSManEnumFlags {
	WSManFlagNonXmlText	= 0x1,
	WSManFlagReturnObject	= 0,
	WSManFlagReturnEPR	= 0x2,
	WSManFlagReturnObjectAndEPR	= 0x4,
	WSManFlagHierarchyDeep	= 0,
	WSManFlagHierarchyShallow	= 0x20,
	WSManFlagHierarchyDeepBasePropsOnly	= 0x40,
	WSManFlagAssociatedInstance	= 0,
	WSManFlagAssociationInstance	= 0x80
	}

.enum WSManProxyAccessTypeFlags {
	WSManProxyIEConfig	= 0x1,
	WSManProxyWinHttpConfig = 0x2,
	WSManProxyAutoDetect	= 0x4,
	WSManProxyNoProxyServer = 0x8
	}

.enum WSManProxyAuthenticationFlags {
	WSManFlagProxyAuthenticationUseNegotiate	= 0x1,
	WSManFlagProxyAuthenticationUseBasic	= 0x2,
	WSManFlagProxyAuthenticationUseDigest	= 0x4
	}

DEFINE_GUID(LIBID_WSManAutomation, 0xF010BE25,0x296D,0x4036,0x98,0x0F,0x5A,0x06,0x69,0xA1,0x75,0x77)

ifndef __IWSMan_INTERFACE_DEFINED__
define __IWSMan_INTERFACE_DEFINED__

DEFINE_IIDX(IWSMan, "190D8637-5CD3-496d-AD24-69636BB5A3B5")

.comdef IWSMan : public IDispatch
    CreateSession	proc :BSTR, :LONG, :ptr, :ptr ptr
    CreateConnectionOptions proc :ptr ptr
    get_CommandLine	proc :ptr
    get_Error		proc :ptr
   .ends

endif

ifndef __IWSManEx_INTERFACE_DEFINED__
define __IWSManEx_INTERFACE_DEFINED__

DEFINE_IIDX(IWSManEx, "2D53BDAA-798E-49e6-A1AA-74D01256F411")

.comdef IWSManEx : public IWSMan
    CreateResourceLocator proc :BSTR, :ptr ptr
    SessionFlagUTF8	proc :ptr
    SessionFlagCredUsernamePassword proc :ptr
    SessionFlagSkipCACheck proc :ptr
    SessionFlagSkipCNCheck proc :ptr
    SessionFlagUseDigest proc :ptr
    SessionFlagUseNegotiate proc :ptr
    SessionFlagUseBasic proc :ptr
    SessionFlagUseKerberos proc :ptr
    SessionFlagNoEncryption proc :ptr
    SessionFlagEnableSPNServerPort proc :ptr
    SessionFlagUseNoAuthentication proc :ptr
    EnumerationFlagNonXmlText proc :ptr
    EnumerationFlagReturnEPR proc :ptr
    EnumerationFlagReturnObjectAndEPR proc :ptr
    GetErrorMessage	proc :DWORD, :ptr
    EnumerationFlagHierarchyDeep proc :ptr
    EnumerationFlagHierarchyShallow proc :ptr
    EnumerationFlagHierarchyDeepBasePropsOnly proc :ptr
    EnumerationFlagReturnObject proc :ptr
   .ends

endif

ifndef __IWSManEx2_INTERFACE_DEFINED__
define __IWSManEx2_INTERFACE_DEFINED__

DEFINE_IIDX(IWSManEx2, "1D1B5AE0-42D9-4021-8261-3987619512E9")

.comdef IWSManEx2 : public IWSManEx
    SessionFlagUseClientCertificate proc :ptr
   .ends

endif

ifndef __IWSManEx3_INTERFACE_DEFINED__
define __IWSManEx3_INTERFACE_DEFINED__

DEFINE_IIDX(IWSManEx3, "6400E966-011D-4eac-8474-049E0848AFAD")

.comdef IWSManEx3 : public IWSManEx2
    SessionFlagUTF16	proc :ptr
    SessionFlagUseCredSsp proc :ptr
    EnumerationFlagAssociationInstance proc :ptr
    EnumerationFlagAssociatedInstance proc :ptr
    SessionFlagSkipRevocationCheck proc :ptr
    SessionFlagAllowNegotiateImplicitCredentials proc :ptr
    SessionFlagUseSsl	proc :ptr
   .ends

endif

ifndef __IWSManConnectionOptions_INTERFACE_DEFINED__
define __IWSManConnectionOptions_INTERFACE_DEFINED__

DEFINE_IIDX(IWSManConnectionOptions, "F704E861-9E52-464f-B786-DA5EB2320FDD")

.comdef IWSManConnectionOptions : public IDispatch
    get_UserName	proc :ptr
    put_UserName	proc :BSTR
    put_Password	proc :BSTR
   .ends

endif

ifndef __IWSManConnectionOptionsEx_INTERFACE_DEFINED__
define __IWSManConnectionOptionsEx_INTERFACE_DEFINED__

DEFINE_IIDX(IWSManConnectionOptionsEx, "EF43EDF7-2A48-4d93-9526-8BD6AB6D4A6B")

.comdef IWSManConnectionOptionsEx : public IWSManConnectionOptions
    get_CertificateThumbprint proc :ptr
    put_CertificateThumbprint proc :BSTR
   .ends

endif

ifndef __IWSManConnectionOptionsEx2_INTERFACE_DEFINED__
define __IWSManConnectionOptionsEx2_INTERFACE_DEFINED__

DEFINE_IIDX(IWSManConnectionOptionsEx2, "F500C9EC-24EE-48ab-B38D-FC9A164C658E")

.comdef IWSManConnectionOptionsEx2 : public IWSManConnectionOptionsEx
    SetProxy		proc :LONG, :LONG, :BSTR, :BSTR
    ProxyIEConfig	proc :ptr
    ProxyWinHttpConfig	proc :ptr
    ProxyAutoDetect	proc :ptr
    ProxyNoProxyServer	proc :ptr
    ProxyAuthenticationUseNegotiate proc :ptr
    ProxyAuthenticationUseBasic proc :ptr
    ProxyAuthenticationUseDigest proc :ptr
   .ends

endif

ifndef __IWSManSession_INTERFACE_DEFINED__
define __IWSManSession_INTERFACE_DEFINED__

DEFINE_IIDX(IWSManSession, "FC84FC58-1286-40c4-9DA0-C8EF6EC241E0")

.comdef IWSManSession : public IDispatch
    Get			proc :VARIANT, :LONG, :ptr
    Put			proc :VARIANT, :BSTR, :LONG, :ptr
    Create		proc :VARIANT, :BSTR, :LONG, :ptr
    Delete		proc :VARIANT, :LONG
    _Invoke		proc :BSTR, :VARIANT, :BSTR, :LONG, :ptr
    Enumerate		proc :VARIANT, :BSTR, :BSTR, :LONG, :ptr ptr
    Identify		proc :LONG, :ptr
    get_Error		proc :ptr
    get_BatchItems	proc :ptr
    put_BatchItems	proc :LONG
    get_Timeout		proc :ptr
    put_Timeout		proc :LONG
   .ends

endif

ifndef __IWSManEnumerator_INTERFACE_DEFINED__
define __IWSManEnumerator_INTERFACE_DEFINED__

DEFINE_IIDX(IWSManEnumerator, "F3457CA9-ABB9-4fa5-B850-90E8CA300E7F")

.comdef IWSManEnumerator : public IDispatch
    ReadItem		proc :ptr
    get_AtEndOfStream	proc :ptr
    get_Error		proc :ptr
   .ends

endif

ifndef __IWSManResourceLocator_INTERFACE_DEFINED__
define __IWSManResourceLocator_INTERFACE_DEFINED__

DEFINE_IIDX(IWSManResourceLocator, "A7A1BA28-DE41-466a-AD0A-C4059EAD7428")

.comdef IWSManResourceLocator : public IDispatch
    put_ResourceURI	proc :BSTR
    get_ResourceURI	proc :ptr
    AddSelector		proc :BSTR, :VARIANT
    ClearSelectors	proc
    get_FragmentPath	proc :ptr
    put_FragmentPath	proc :BSTR
    get_FragmentDialect proc :ptr
    put_FragmentDialect proc :BSTR
    AddOption		proc :BSTR, :VARIANT, :BOOL
    put_MustUnderstandOptions proc :BOOL
    get_MustUnderstandOptions proc :ptr
    ClearOptions	proc
    get_Error		proc :ptr
   .ends

endif

ifndef __IWSManResourceLocatorInternal_INTERFACE_DEFINED__
define __IWSManResourceLocatorInternal_INTERFACE_DEFINED__

DEFINE_IIDX(IWSManResourceLocatorInternal, "EFFAEAD7-7EC8-4716-B9BE-F2E7E9FB4ADB")

.comdef IWSManResourceLocatorInternal : public IUnknown
   .ends

endif

DEFINE_GUID(CLSID_WSMan, 0xBCED617B,0xEC03,0x420b,0x85,0x08,0x97,0x7D,0xC7,0xA6,0x86,0xBD)

ifndef __IWSManInternal_INTERFACE_DEFINED__
define __IWSManInternal_INTERFACE_DEFINED__

DEFINE_IIDX(IWSManInternal, "04AE2B1D-9954-4D99-94A9-A961E72C3A13")

.comdef IWSManInternal : public IDispatch
    ConfigSDDL		proc :ptr, :VARIANT, :LONG, :ptr
   .ends

endif

DEFINE_GUID(CLSID_WSManInternal, 0x7DE087A5,0x5DCB,0x4df7,0xBB,0x12,0x09,0x24,0xAD,0x8F,0xBD,0x9A)

endif

endif

endif

