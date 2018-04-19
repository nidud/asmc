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
ifndef __adhoc_h__
__adhoc_h__ equ 1

ifndef __IDot11AdHocManager_FWD_DEFINED__
__IDot11AdHocManager_FWD_DEFINED__ equ 1
endif
ifndef __IDot11AdHocManagerNotificationSink_FWD_DEFINED__
__IDot11AdHocManagerNotificationSink_FWD_DEFINED__ equ 1
endif
ifndef __IEnumDot11AdHocNetworks_FWD_DEFINED__
__IEnumDot11AdHocNetworks_FWD_DEFINED__ equ 1
endif
ifndef __IDot11AdHocNetwork_FWD_DEFINED__
__IDot11AdHocNetwork_FWD_DEFINED__ equ 1
endif
ifndef __IDot11AdHocNetworkNotificationSink_FWD_DEFINED__
__IDot11AdHocNetworkNotificationSink_FWD_DEFINED__ equ 1
endif
ifndef __IDot11AdHocInterface_FWD_DEFINED__
__IDot11AdHocInterface_FWD_DEFINED__ equ 1
endif
ifndef __IEnumDot11AdHocInterfaces_FWD_DEFINED__
__IEnumDot11AdHocInterfaces_FWD_DEFINED__ equ 1
endif
ifndef __IEnumDot11AdHocSecuritySettings_FWD_DEFINED__
__IEnumDot11AdHocSecuritySettings_FWD_DEFINED__ equ 1
endif
ifndef __IDot11AdHocSecuritySettings_FWD_DEFINED__
__IDot11AdHocSecuritySettings_FWD_DEFINED__ equ 1
endif
ifndef __IDot11AdHocInterfaceNotificationSink_FWD_DEFINED__
__IDot11AdHocInterfaceNotificationSink_FWD_DEFINED__ equ 1
endif
ifndef __Dot11AdHocManager_FWD_DEFINED__
__Dot11AdHocManager_FWD_DEFINED__ equ 1
Dot11AdHocManager typedef Dot11AdHocManager
endif

include oaidl.inc

externdef		CLSID_AdHocManager:CLSID

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

externdef		__MIDL_itf_adhoc_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_adhoc_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDot11AdHocManager_INTERFACE_DEFINED__
__IDot11AdHocManager_INTERFACE_DEFINED__ equ 1

externdef		IID_IDot11AdHocManager:IID

.comdef IDot11AdHocManager

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CreateNetwork	proc :LPCWSTR, :LPCWSTR, :LONG, :ptr, :ptr, :ptr, :ptr
    CommitCreatedNetwork proc :ptr, :BOOLEAN, :BOOLEAN
    GetIEnumDot11AdHocNetworks proc :ptr, :ptr
    GetIEnumDot11AdHocInterfaces proc :ptr
    GetNetwork		proc :ptr, :ptr
    .ends

endif

ifndef __IDot11AdHocManagerNotificationSink_INTERFACE_DEFINED__
__IDot11AdHocManagerNotificationSink_INTERFACE_DEFINED__ equ 1

externdef		IID_IDot11AdHocManagerNotificationSink:IID

.comdef IDot11AdHocManagerNotificationSink

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    OnNetworkAdd	proc :ptr
    OnNetworkRemove	proc :ptr
    OnInterfaceAdd	proc :ptr
    OnInterfaceRemove	proc :ptr
    .ends

endif

ifndef __IEnumDot11AdHocNetworks_INTERFACE_DEFINED__
__IEnumDot11AdHocNetworks_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumDot11AdHocNetworks:IID

.comdef IEnumDot11AdHocNetworks

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

ifndef __IDot11AdHocNetwork_INTERFACE_DEFINED__
__IDot11AdHocNetwork_INTERFACE_DEFINED__ equ 1

externdef		IID_IDot11AdHocNetwork:IID

.comdef IDot11AdHocNetwork

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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
__IDot11AdHocNetworkNotificationSink_INTERFACE_DEFINED__ equ 1

externdef		IID_IDot11AdHocNetworkNotificationSink:IID

.comdef IDot11AdHocNetworkNotificationSink

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    OnStatusChange	proc :DOT11_ADHOC_NETWORK_CONNECTION_STATUS
    OnConnectFail	proc :DOT11_ADHOC_CONNECT_FAIL_REASON
    .ends

endif

ifndef __IDot11AdHocInterface_INTERFACE_DEFINED__
__IDot11AdHocInterface_INTERFACE_DEFINED__ equ 1

externdef		IID_IDot11AdHocInterface:IID

.comdef IDot11AdHocInterface

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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
__IEnumDot11AdHocInterfaces_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumDot11AdHocInterfaces:IID

.comdef IEnumDot11AdHocInterfaces

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

ifndef __IEnumDot11AdHocSecuritySettings_INTERFACE_DEFINED__
__IEnumDot11AdHocSecuritySettings_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumDot11AdHocSecuritySettings:IID

.comdef IEnumDot11AdHocSecuritySettings

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

ifndef __IDot11AdHocSecuritySettings_INTERFACE_DEFINED__
__IDot11AdHocSecuritySettings_INTERFACE_DEFINED__ equ 1

externdef		IID_IDot11AdHocSecuritySettings:IID

.comdef IDot11AdHocSecuritySettings

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDot11AuthAlgorithm proc :ptr
    GetDot11CipherAlgorithm proc :ptr
    .ends

endif

ifndef __IDot11AdHocInterfaceNotificationSink_INTERFACE_DEFINED__
__IDot11AdHocInterfaceNotificationSink_INTERFACE_DEFINED__ equ 1

externdef		IID_IDot11AdHocInterfaceNotificationSink:IID

.comdef IDot11AdHocInterfaceNotificationSink

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    OnConnectionStatusChange proc :DOT11_ADHOC_NETWORK_CONNECTION_STATUS
    .ends

endif

ifndef __ADHOCLib_LIBRARY_DEFINED__
__ADHOCLib_LIBRARY_DEFINED__ equ 1

externdef		LIBID_ADHOCLib:IID
externdef		CLSID_Dot11AdHocManager:CLSID

ifdef __cplusplus
DECLSPEC_UUID("DD06A84F-83BD-4d01-8AB9-2389FEA0869E")
endif
endif

endif
