ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
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

ifndef __credentialprovider_h__
define __credentialprovider_h__

include wtypes.inc
include shobjidl.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum CREDENTIAL_PROVIDER_USAGE_SCENARIO {
    CPUS_INVALID	= 0,
    CPUS_LOGON	= ( CPUS_INVALID + 1 ) ,
    CPUS_UNLOCK_WORKSTATION	= ( CPUS_LOGON + 1 ) ,
    CPUS_CHANGE_PASSWORD	= ( CPUS_UNLOCK_WORKSTATION + 1 ) ,
    CPUS_CREDUI = ( CPUS_CHANGE_PASSWORD + 1 ) ,
    CPUS_PLAP	= ( CPUS_CREDUI + 1 )
    }

.enum CREDENTIAL_PROVIDER_FIELD_TYPE {
    CPFT_INVALID	= 0,
    CPFT_LARGE_TEXT	= ( CPFT_INVALID + 1 ) ,
    CPFT_SMALL_TEXT	= ( CPFT_LARGE_TEXT + 1 ) ,
    CPFT_COMMAND_LINK	= ( CPFT_SMALL_TEXT + 1 ) ,
    CPFT_EDIT_TEXT	= ( CPFT_COMMAND_LINK + 1 ) ,
    CPFT_PASSWORD_TEXT	= ( CPFT_EDIT_TEXT + 1 ) ,
    CPFT_TILE_IMAGE	= ( CPFT_PASSWORD_TEXT + 1 ) ,
    CPFT_CHECKBOX	= ( CPFT_TILE_IMAGE + 1 ) ,
    CPFT_COMBOBOX	= ( CPFT_CHECKBOX + 1 ) ,
    CPFT_SUBMIT_BUTTON	= ( CPFT_COMBOBOX + 1 )
    }

.enum CREDENTIAL_PROVIDER_FIELD_STATE {
    CPFS_HIDDEN = 0,
    CPFS_DISPLAY_IN_SELECTED_TILE	= ( CPFS_HIDDEN + 1 ) ,
    CPFS_DISPLAY_IN_DESELECTED_TILE	= ( CPFS_DISPLAY_IN_SELECTED_TILE + 1 ) ,
    CPFS_DISPLAY_IN_BOTH	= ( CPFS_DISPLAY_IN_DESELECTED_TILE + 1 )
    }

.enum CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE {
    CPFIS_NONE	= 0,
    CPFIS_READONLY	= ( CPFIS_NONE + 1 ) ,
    CPFIS_DISABLED	= ( CPFIS_READONLY + 1 ) ,
    CPFIS_FOCUSED	= ( CPFIS_DISABLED + 1 )
    }

CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR STRUC
dwFieldID		dd ?
cpft			CREDENTIAL_PROVIDER_FIELD_TYPE ?
pszLabel		LPWSTR ?
guidFieldType		GUID <>
CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR ENDS

.enum CREDENTIAL_PROVIDER_GET_SERIALIZATION_RESPONSE {
    CPGSR_NO_CREDENTIAL_NOT_FINISHED	= 0,
    CPGSR_NO_CREDENTIAL_FINISHED	= ( CPGSR_NO_CREDENTIAL_NOT_FINISHED + 1 ) ,
    CPGSR_RETURN_CREDENTIAL_FINISHED	= ( CPGSR_NO_CREDENTIAL_FINISHED + 1 ) ,
    CPGSR_RETURN_NO_CREDENTIAL_FINISHED = ( CPGSR_RETURN_CREDENTIAL_FINISHED + 1 )
    }

.enum CREDENTIAL_PROVIDER_STATUS_ICON {
    CPSI_NONE	= 0,
    CPSI_ERROR	= ( CPSI_NONE + 1 ) ,
    CPSI_WARNING	= ( CPSI_ERROR + 1 ) ,
    CPSI_SUCCESS	= ( CPSI_WARNING + 1 )
    }

CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION STRUC
ulAuthenticationPackage ULONG ?
clsidCredentialProvider GUID <>
cbSerialization		ULONG ?
rgbSerialization	LPBYTE ?
CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION ENDS

if (NTDDI_VERSION GE NTDDI_WIN8)
.enum CREDENTIAL_PROVIDER_ACCOUNT_OPTIONS {
    CPAO_NONE	= 0,
    CPAO_EMPTY_LOCAL	= 0x1,
    CPAO_EMPTY_CONNECTED	= 0x2
    }

.enum CREDENTIAL_PROVIDER_CREDENTIAL_FIELD_OPTIONS {
    CPCFO_NONE	= 0,
    CPCFO_ENABLE_PASSWORD_REVEAL	= 0x1,
    CPCFO_IS_EMAIL_ADDRESS	= 0x2,
    CPCFO_ENABLE_TOUCH_KEYBOARD_AUTO_INVOKE	= 0x4,
    CPCFO_NUMBERS_ONLY	= 0x8
    }

endif
NTSTATUS		typedef LONG

CREDENTIAL_PROVIDER_NO_DEFAULT equ (-1)


ifndef __ICredentialProviderCredential_INTERFACE_DEFINED__
define __ICredentialProviderCredential_INTERFACE_DEFINED__

DEFINE_IIDX(ICredentialProviderCredential, "63913a93-40c1-481a-818d-4072ff8c70cc")

.comdef ICredentialProviderCredential : public IUnknown

    Advise		proc :ptr
    UnAdvise		proc
    SetSelected		proc :ptr
    SetDeselected	proc
    GetFieldState	proc :DWORD, :ptr, :ptr
    GetStringValue	proc :DWORD, :ptr
    GetBitmapValue	proc :DWORD, :ptr
    GetCheckboxValue	proc :DWORD, :ptr, :ptr
    GetSubmitButtonValue proc :DWORD, :ptr
    GetComboBoxValueCount proc :DWORD, :ptr, :ptr
    GetComboBoxValueAt	proc :DWORD, :DWORD, :ptr
    SetStringValue	proc :DWORD, :LPCWSTR
    SetCheckboxValue	proc :DWORD, :BOOL
    SetComboBoxSelectedValue proc :DWORD, :DWORD
    CommandLinkClicked	proc :DWORD
    GetSerialization	proc :ptr, :ptr, :ptr, :ptr
    ReportResult	proc :NTSTATUS, :NTSTATUS, :ptr, :ptr
    .ends

endif


ifndef __IQueryContinueWithStatus_INTERFACE_DEFINED__
define __IQueryContinueWithStatus_INTERFACE_DEFINED__

DEFINE_IIDX(IQueryContinueWithStatus, "9090be5b-502b-41fb-bccc-0049a6c7254b")

.comdef IQueryContinueWithStatus : public IQueryContinue

    SetStatusMessage	proc :LPCWSTR
   .ends

endif


ifndef __IConnectableCredentialProviderCredential_INTERFACE_DEFINED__
define __IConnectableCredentialProviderCredential_INTERFACE_DEFINED__

DEFINE_IIDX(IConnectableCredentialProviderCredential, "9387928b-ac75-4bf9-8ab2-2b93c4a55290")

.comdef IConnectableCredentialProviderCredential : public ICredentialProviderCredential

    Connect		proc :ptr
    Disconnect		proc
   .ends

endif

ifndef __ICredentialProviderCredentialEvents_INTERFACE_DEFINED__
define __ICredentialProviderCredentialEvents_INTERFACE_DEFINED__

DEFINE_IIDX(ICredentialProviderCredentialEvents, "fa6fa76b-66b7-4b11-95f1-86171118e816")

.comdef ICredentialProviderCredentialEvents : public IUnknown

    SetFieldState	proc :ptr, :DWORD, :CREDENTIAL_PROVIDER_FIELD_STATE
    SetFieldInteractiveState proc :ptr, :DWORD, :CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE
    SetFieldString	proc :ptr, :DWORD, :LPCWSTR
    SetFieldCheckbox	proc :ptr, :DWORD, :BOOL, :LPCWSTR
    SetFieldBitmap	proc :ptr, :DWORD, :HBITMAP
    SetFieldComboBoxSelectedItem proc :ptr, :DWORD, :DWORD
    DeleteFieldComboBoxItem proc :ptr, :DWORD, :DWORD
    AppendFieldComboBoxItem proc :ptr, :DWORD, :LPCWSTR
    SetFieldSubmitButton proc :ptr, :DWORD, :DWORD
    OnCreatingWindow	proc :ptr
   .ends

endif

ifndef __ICredentialProvider_INTERFACE_DEFINED__
define __ICredentialProvider_INTERFACE_DEFINED__

DEFINE_IIDX(ICredentialProvider, "d27c3481-5a1c-45b2-8aaa-c20ebbe8229e")

.comdef ICredentialProvider : public IUnknown

    SetUsageScenario	proc :CREDENTIAL_PROVIDER_USAGE_SCENARIO, :DWORD
    SetSerialization	proc :ptr
    Advise		proc :ptr, :UINT_PTR
    UnAdvise		proc
    GetFieldDescriptorCount proc :ptr
    GetFieldDescriptorAt proc :DWORD, :ptr
    GetCredentialCount	proc :ptr, :ptr, :ptr
    GetCredentialAt	proc :DWORD, :ptr
   .ends

endif

ifndef __ICredentialProviderEvents_INTERFACE_DEFINED__
define __ICredentialProviderEvents_INTERFACE_DEFINED__

DEFINE_IIDX(ICredentialProviderEvents, "34201e5a-a787-41a3-a5a4-bd6dcf2a854e")

.comdef ICredentialProviderEvents : public IUnknown

    CredentialsChanged	proc :UINT_PTR
   .ends

endif

ifndef __ICredentialProviderFilter_INTERFACE_DEFINED__
define __ICredentialProviderFilter_INTERFACE_DEFINED__

DEFINE_IIDX(ICredentialProviderFilter, "a5da53f9-d475-4080-a120-910c4a739880")

.comdef ICredentialProviderFilter : public IUnknown

    Filter		proc :CREDENTIAL_PROVIDER_USAGE_SCENARIO, :DWORD, :ptr, :ptr, :DWORD
    UpdateRemoteCredential proc :ptr, :ptr
   .ends

endif

if (NTDDI_VERSION GE NTDDI_WIN8)

ifndef __ICredentialProviderCredential2_INTERFACE_DEFINED__
define __ICredentialProviderCredential2_INTERFACE_DEFINED__

DEFINE_IIDX(ICredentialProviderCredential2, "fd672c54-40ea-4d6e-9b49-cfb1a7507bd7")

.comdef ICredentialProviderCredential2 : public ICredentialProviderCredential

    GetUserSid		proc :ptr
   .ends

endif

ifndef __ICredentialProviderCredentialWithFieldOptions_INTERFACE_DEFINED__
define __ICredentialProviderCredentialWithFieldOptions_INTERFACE_DEFINED__

DEFINE_IIDX(ICredentialProviderCredentialWithFieldOptions, "DBC6FB30-C843-49E3-A645-573E6F39446A")

.comdef ICredentialProviderCredentialWithFieldOptions : public IUnknown

    GetFieldOptions	proc :DWORD, :ptr
   .ends

endif

ifndef __ICredentialProviderCredentialEvents2_INTERFACE_DEFINED__
define __ICredentialProviderCredentialEvents2_INTERFACE_DEFINED__

DEFINE_IIDX(ICredentialProviderCredentialEvents2, "B53C00B6-9922-4B78-B1F4-DDFE774DC39B")

.comdef ICredentialProviderCredentialEvents2 : public ICredentialProviderCredentialEvents

    BeginFieldUpdates	proc
    EndFieldUpdates	proc
    SetFieldOptions	proc :ptr, :DWORD, :CREDENTIAL_PROVIDER_CREDENTIAL_FIELD_OPTIONS
   .ends

endif

ifndef __ICredentialProviderUser_INTERFACE_DEFINED__
define __ICredentialProviderUser_INTERFACE_DEFINED__

DEFINE_IIDX(ICredentialProviderUser, "13793285-3ea6-40fd-b420-15f47da41fbb")

.comdef ICredentialProviderUser : public IUnknown

    GetSid		proc :ptr
    GetProviderID	proc :ptr
    GetStringValue	proc :REFPROPERTYKEY, :ptr
    GetValue		proc :REFPROPERTYKEY, :ptr
   .ends

endif

DEFINE_GUID(Identity_LocalUserProvider, 0xA198529B, 0x730F, 0x4089, 0xB6, 0x46, 0xA1, 0x25, 0x57, 0xF5, 0x66, 0x5E)


ifndef __ICredentialProviderUserArray_INTERFACE_DEFINED__
define __ICredentialProviderUserArray_INTERFACE_DEFINED__

DEFINE_IIDX(ICredentialProviderUserArray, "90C119AE-0F18-4520-A1F1-114366A40FE8")

.comdef ICredentialProviderUserArray : public IUnknown

    SetProviderFilter	proc :REFGUID
    GetAccountOptions	proc :ptr
    GetCount		proc :ptr
    GetAt		proc :DWORD, :ptr
   .ends

endif

ifndef __ICredentialProviderSetUserArray_INTERFACE_DEFINED__
define __ICredentialProviderSetUserArray_INTERFACE_DEFINED__

DEFINE_IIDX(ICredentialProviderSetUserArray, "095c1484-1c0c-4388-9c6d-500e61bf84bd")

.comdef ICredentialProviderSetUserArray : public IUnknown

    SetUserArray	proc :ptr
   .ends

endif

endif

ifndef __CredentialProviders_LIBRARY_DEFINED__
define __CredentialProviders_LIBRARY_DEFINED__

externdef LIBID_CredentialProviders:IID

DEFINE_GUIDS(CLSID_PasswordCredentialProvider, "60b78e88-ead8-445c-9cfd-0b87f74ea6cd")
DEFINE_GUIDS(CLSID_V1PasswordCredentialProvider, "6f45dc1e-5384-457a-bc13-2cd81b0d28ed")
DEFINE_GUIDS(CLSID_PINLogonCredentialProvider, "cb82ea12-9f71-446d-89e1-8d0924e1256e")
DEFINE_GUIDS(CLSID_NPCredentialProvider, "3dd6bec0-8193-4ffe-ae25-e08e39ea4063")
DEFINE_GUIDS(CLSID_SmartcardCredentialProvider, "8FD7E19C-3BF7-489B-A72C-846AB3678C96")
DEFINE_GUIDS(CLSID_V1SmartcardCredentialProvider, "8bf9a910-a8ff-457f-999f-a5ca10b4a885")
DEFINE_GUIDS(CLSID_SmartcardPinProvider, "94596c7e-3744-41ce-893e-bbf09122f76a")
DEFINE_GUIDS(CLSID_SmartcardReaderSelectionProvider, "1b283861-754f-4022-ad47-a5eaaa618894")
DEFINE_GUIDS(CLSID_SmartcardWinRTProvider, "1ee7337f-85ac-45e2-a23c-37c753209769")
DEFINE_GUIDS(CLSID_GenericCredentialProvider, "25CBB996-92ED-457e-B28C-4774084BD562")
DEFINE_GUIDS(CLSID_RASProvider, "5537E283-B1E7-4EF8-9C6E-7AB0AFE5056D")
DEFINE_GUIDS(CLSID_OnexCredentialProvider, "07AA0886-CC8D-4e19-A410-1C75AF686E62")
DEFINE_GUIDS(CLSID_OnexPlapSmartcardCredentialProvider, "33c86cd6-705f-4ba1-9adb-67070b837775")
DEFINE_GUIDS(CLSID_VaultProvider, "503739d0-4c5e-4cfd-b3ba-d881334f0df2")
DEFINE_GUIDS(CLSID_WinBioCredentialProvider, "BEC09223-B018-416D-A0AC-523971B639F5")
DEFINE_GUIDS(CLSID_V1WinBioCredentialProvider, "AC3AC249-E820-4343-A65B-377AC634DC09")
endif

endif

HBITMAP_UserSize proto WINAPI :ptr, :dword, :ptr
HBITMAP_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HBITMAP_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HBITMAP_UserFree proto WINAPI :ptr, :ptr

HWND_UserSize proto WINAPI :ptr, :dword, :ptr
HWND_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HWND_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HWND_UserFree proto WINAPI :ptr, :ptr

HBITMAP_UserSize64 proto WINAPI :ptr, :dword, :ptr
HBITMAP_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
HBITMAP_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HBITMAP_UserFree64 proto WINAPI :ptr, :ptr

HWND_UserSize64 proto WINAPI :ptr, :dword, :ptr
HWND_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
HWND_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HWND_UserFree64 proto WINAPI :ptr, :ptr

endif
