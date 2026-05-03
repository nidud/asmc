.pragma list(push, 0)
ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __adhoc_h__
define __adhoc_h__
ifndef __oaidl_h__
include oaidl.inc
endif

externdef CLSID_AdHocManager:CLSID

DOT11_ADHOC_CIPHER_ALGORITHM typedef SDWORD
DOT11_ADHOC_CIPHER_ALGO_INVALID equ -1
DOT11_ADHOC_CIPHER_ALGO_NONE equ 0
DOT11_ADHOC_CIPHER_ALGO_CCMP equ 0x4
DOT11_ADHOC_CIPHER_ALGO_WEP equ 0x101

DOT11_ADHOC_AUTH_ALGORITHM typedef SDWORD
DOT11_ADHOC_AUTH_ALGO_INVALID equ -1
DOT11_ADHOC_AUTH_ALGO_80211_OPEN equ 1
DOT11_ADHOC_AUTH_ALGO_RSNA_PSK equ 7

DOT11_ADHOC_NETWORK_CONNECTION_STATUS typedef SDWORD
DOT11_ADHOC_NETWORK_CONNECTION_STATUS_INVALID equ 0
DOT11_ADHOC_NETWORK_CONNECTION_STATUS_DISCONNECTED equ 11
DOT11_ADHOC_NETWORK_CONNECTION_STATUS_CONNECTING equ 12
DOT11_ADHOC_NETWORK_CONNECTION_STATUS_CONNECTED equ 13
DOT11_ADHOC_NETWORK_CONNECTION_STATUS_FORMED equ 14

DOT11_ADHOC_CONNECT_FAIL_REASON typedef SDWORD
DOT11_ADHOC_CONNECT_FAIL_DOMAIN_MISMATCH equ 0
DOT11_ADHOC_CONNECT_FAIL_PASSPHRASE_MISMATCH equ 1
DOT11_ADHOC_CONNECT_FAIL_OTHER equ 2

ifndef __IDot11AdHocManager_INTERFACE_DEFINED__
define __IDot11AdHocManager_INTERFACE_DEFINED__

DEFINE_IIDX(IDot11AdHocManager, "8F10CC26-CF0D-42a0-ACBE-E2DE7007384D")

.comdef IDot11AdHocManager : public IUnknown

    CreateNetwork	proc :LPCWSTR, :LPCWSTR, :LONG, :ptr, :ptr, :ptr, :ptr
    CommitCreatedNetwork proc :ptr, :BOOLEAN, :BOOLEAN
    GetIEnumDot11AdHocNetworks proc :ptr, :ptr
    GetIEnumDot11AdHocInterfaces proc :ptr
    GetNetwork		proc :ptr, :ptr
   .ends

endif

ifndef __IDot11AdHocManagerNotificationSink_INTERFACE_DEFINED__
define __IDot11AdHocManagerNotificationSink_INTERFACE_DEFINED__

DEFINE_IIDX(IDot11AdHocManagerNotificationSink, "8F10CC27-CF0D-42a0-ACBE-E2DE7007384D")

.comdef IDot11AdHocManagerNotificationSink : public IUnknown

    OnNetworkAdd	proc :ptr
    OnNetworkRemove	proc :ptr
    OnInterfaceAdd	proc :ptr
    OnInterfaceRemove	proc :ptr
   .ends

endif

ifndef __IEnumDot11AdHocNetworks_INTERFACE_DEFINED__
define __IEnumDot11AdHocNetworks_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumDot11AdHocNetworks, "8F10CC28-CF0D-42a0-ACBE-E2DE7007384D")

.comdef IEnumDot11AdHocNetworks : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

ifndef __IDot11AdHocNetwork_INTERFACE_DEFINED__
define __IDot11AdHocNetwork_INTERFACE_DEFINED__

DEFINE_IIDX(IDot11AdHocNetwork, "8F10CC29-CF0D-42a0-ACBE-E2DE7007384D")

.comdef IDot11AdHocNetwork : public IUnknown

    GetStatus		proc :ptr
    GetSSID		proc :ptr
    HasProfile		proc :ptr
    GetProfileName	proc :ptr
    DeleteProfile	proc
    GetSignalQuality	proc :ptr, :ptr
    GetSecuritySetting	proc :ptr
    GetContextGuid	proc :ptr
    GetSignature	proc :ptr
    GetInterface	proc :ptr
    Connect		proc :LPCWSTR, :LONG, :BOOLEAN, :BOOLEAN
    Disconnect		proc
   .ends

endif

ifndef __IDot11AdHocNetworkNotificationSink_INTERFACE_DEFINED__
define __IDot11AdHocNetworkNotificationSink_INTERFACE_DEFINED__

DEFINE_IIDX(IDot11AdHocNetworkNotificationSink, "8F10CC2A-CF0D-42a0-ACBE-E2DE7007384D")

.comdef IDot11AdHocNetworkNotificationSink : public IUnknown

    OnStatusChange	proc :DOT11_ADHOC_NETWORK_CONNECTION_STATUS
    OnConnectFail	proc :DOT11_ADHOC_CONNECT_FAIL_REASON
   .ends

endif

ifndef __IDot11AdHocInterface_INTERFACE_DEFINED__
define __IDot11AdHocInterface_INTERFACE_DEFINED__

DEFINE_IIDX(IDot11AdHocInterface, "8F10CC2B-CF0D-42a0-ACBE-E2DE7007384D")

.comdef IDot11AdHocInterface : public IUnknown

    GetDeviceSignature	proc :ptr
    GetFriendlyName	proc :ptr
    IsDot11d		proc :ptr
    IsAdHocCapable	proc :ptr
    IsRadioOn		proc :ptr
    GetActiveNetwork	proc :ptr
    GetIEnumSecuritySettings proc :ptr
    GetIEnumDot11AdHocNetworks proc :ptr, :ptr
    GetStatus		proc :ptr
   .ends

endif

ifndef __IEnumDot11AdHocInterfaces_INTERFACE_DEFINED__
define __IEnumDot11AdHocInterfaces_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumDot11AdHocInterfaces, "8F10CC2C-CF0D-42a0-ACBE-E2DE7007384D")

.comdef IEnumDot11AdHocInterfaces : public IEnumDot11AdHocNetworks
   .ends

endif

ifndef __IEnumDot11AdHocSecuritySettings_INTERFACE_DEFINED__
define __IEnumDot11AdHocSecuritySettings_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumDot11AdHocSecuritySettings, "8F10CC2D-CF0D-42a0-ACBE-E2DE7007384D")

.comdef IEnumDot11AdHocSecuritySettings : public IEnumDot11AdHocNetworks
   .ends

endif

ifndef __IDot11AdHocSecuritySettings_INTERFACE_DEFINED__
define __IDot11AdHocSecuritySettings_INTERFACE_DEFINED__

DEFINE_IIDX(IDot11AdHocSecuritySettings, "8F10CC2E-CF0D-42a0-ACBE-E2DE7007384D")

.comdef IDot11AdHocSecuritySettings : public IUnknown

    GetDot11AuthAlgorithm proc :ptr
    GetDot11CipherAlgorithm proc :ptr
   .ends

endif

ifndef __IDot11AdHocInterfaceNotificationSink_INTERFACE_DEFINED__
define __IDot11AdHocInterfaceNotificationSink_INTERFACE_DEFINED__

DEFINE_IIDX(IDot11AdHocInterfaceNotificationSink, "8F10CC2F-CF0D-42a0-ACBE-E2DE7007384D")

.comdef IDot11AdHocInterfaceNotificationSink : public IUnknown

    OnConnectionStatusChange proc :DOT11_ADHOC_NETWORK_CONNECTION_STATUS
   .ends

endif

ifndef __ADHOCLib_LIBRARY_DEFINED__
define __ADHOCLib_LIBRARY_DEFINED__

DEFINE_GUID(LIBID_ADHOCLib,		0xDD06A84F,0x83BD,0x4d01,0x8A,0xB9,0x23,0x89,0xFE,0xA0,0x86,0x9E)
DEFINE_GUID(CLSID_Dot11AdHocManager,	0xDD06A84F,0x83BD,0x4d01,0x8A,0xB9,0x23,0x89,0xFE,0xA0,0x86,0x9E)

endif
endif
.pragma list(pop)
