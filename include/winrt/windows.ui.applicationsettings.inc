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

ifndef __windows2Eui2Eapplicationsettings_h__
define __windows2Eui2Eapplicationsettings_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Security.Credentials.inc
include Windows.UI.Popups.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CUI__CApplicationSettings__CCredentialCommand_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CApplicationSettings__CCredentialCommand_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CApplicationSettings__CCredentialCommand, "9f1177f1-85bb-5cd0-9b08-a0b47a764c75")

.comdef __FIIterator_1_Windows__CUI__CApplicationSettings__CCredentialCommand : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CApplicationSettings__CCredentialCommand_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CApplicationSettings__CCredentialCommand_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CApplicationSettings__CCredentialCommand, "883ed18d-4dbb-58f2-8fd2-e4b018509553")

.comdef __FIIterable_1_Windows__CUI__CApplicationSettings__CCredentialCommand : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CApplicationSettings__CSettingsCommand_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CApplicationSettings__CSettingsCommand_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CApplicationSettings__CSettingsCommand, "2f071c24-4a58-5a00-a294-c7162e98c2a0")

.comdef __FIIterator_1_Windows__CUI__CApplicationSettings__CSettingsCommand : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CApplicationSettings__CSettingsCommand_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CApplicationSettings__CSettingsCommand_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CApplicationSettings__CSettingsCommand, "6308e7e8-cb85-5339-a3e9-9a7500d19c68")

.comdef __FIIterable_1_Windows__CUI__CApplicationSettings__CSettingsCommand : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CApplicationSettings__CWebAccountCommand_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CApplicationSettings__CWebAccountCommand_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CApplicationSettings__CWebAccountCommand, "8cbb62b6-bd9c-5486-9d14-9cc4627b32d4")

.comdef __FIIterator_1_Windows__CUI__CApplicationSettings__CWebAccountCommand : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CApplicationSettings__CWebAccountCommand_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CApplicationSettings__CWebAccountCommand_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CApplicationSettings__CWebAccountCommand, "bd0d999c-b2ba-51b2-bcc0-d4a5cd821555")

.comdef __FIIterable_1_Windows__CUI__CApplicationSettings__CWebAccountCommand : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CApplicationSettings__CWebAccountProviderCommand_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CApplicationSettings__CWebAccountProviderCommand_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CApplicationSettings__CWebAccountProviderCommand, "82d7cd74-8e33-5f06-92fc-915138aacbde")

.comdef __FIIterator_1_Windows__CUI__CApplicationSettings__CWebAccountProviderCommand : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CApplicationSettings__CWebAccountProviderCommand_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CApplicationSettings__CWebAccountProviderCommand_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CApplicationSettings__CWebAccountProviderCommand, "15165367-2e93-59a6-b5c7-16d3b58fd2e7")

.comdef __FIIterable_1_Windows__CUI__CApplicationSettings__CWebAccountProviderCommand : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CApplicationSettings__CCredentialCommand_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CApplicationSettings__CCredentialCommand_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CApplicationSettings__CCredentialCommand, "95cc1bba-c279-5ee5-a524-78012b7fe17e")

.comdef __FIVectorView_1_Windows__CUI__CApplicationSettings__CCredentialCommand : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CApplicationSettings__CSettingsCommand_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CApplicationSettings__CSettingsCommand_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CApplicationSettings__CSettingsCommand, "67b64d17-4245-5d7c-bfb4-6b68dd525877")

.comdef __FIVectorView_1_Windows__CUI__CApplicationSettings__CSettingsCommand : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CApplicationSettings__CWebAccountCommand_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CApplicationSettings__CWebAccountCommand_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CApplicationSettings__CWebAccountCommand, "207eaa3e-5ec9-5bd4-a1d2-73179a8128a8")

.comdef __FIVectorView_1_Windows__CUI__CApplicationSettings__CWebAccountCommand : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CApplicationSettings__CWebAccountProviderCommand_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CApplicationSettings__CWebAccountProviderCommand_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CApplicationSettings__CWebAccountProviderCommand, "b2d19260-1827-5d88-b948-9688cfcd63ae")

.comdef __FIVectorView_1_Windows__CUI__CApplicationSettings__CWebAccountProviderCommand : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CApplicationSettings__CCredentialCommand_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CApplicationSettings__CCredentialCommand_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CApplicationSettings__CCredentialCommand, "b6af1cb5-f60e-5b08-b312-2eb51135cfc6")

.comdef __FIVector_1_Windows__CUI__CApplicationSettings__CCredentialCommand : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CApplicationSettings__CSettingsCommand_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CApplicationSettings__CSettingsCommand_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CApplicationSettings__CSettingsCommand, "10bd9cdd-3767-5e96-9022-f00f9cbd6241")

.comdef __FIVector_1_Windows__CUI__CApplicationSettings__CSettingsCommand : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CApplicationSettings__CWebAccountCommand_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CApplicationSettings__CWebAccountCommand_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CApplicationSettings__CWebAccountCommand, "64e864c8-7fef-5df5-a624-50b577f48554")

.comdef __FIVector_1_Windows__CUI__CApplicationSettings__CWebAccountCommand : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CApplicationSettings__CWebAccountProviderCommand_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CApplicationSettings__CWebAccountProviderCommand_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CApplicationSettings__CWebAccountProviderCommand, "d376abf3-f0c1-5233-9f42-de531884963e")

.comdef __FIVector_1_Windows__CUI__CApplicationSettings__CWebAccountProviderCommand : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CApplicationSettings__CAccountsSettingsPane_Windows__CUI__CApplicationSettings__CAccountsSettingsPaneCommandsRequestedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CApplicationSettings__CAccountsSettingsPane_Windows__CUI__CApplicationSettings__CAccountsSettingsPaneCommandsRequestedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CApplicationSettings__CAccountsSettingsPane_Windows__CUI__CApplicationSettings__CAccountsSettingsPaneCommandsRequestedEventArgs, "69b8847e-7d72-5a15-bc1c-4ca39c93b162")

.comdef __FITypedEventHandler_2_Windows__CUI__CApplicationSettings__CAccountsSettingsPane_Windows__CUI__CApplicationSettings__CAccountsSettingsPaneCommandsRequestedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CApplicationSettings__CSettingsPane_Windows__CUI__CApplicationSettings__CSettingsPaneCommandsRequestedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CApplicationSettings__CSettingsPane_Windows__CUI__CApplicationSettings__CSettingsPaneCommandsRequestedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CApplicationSettings__CSettingsPane_Windows__CUI__CApplicationSettings__CSettingsPaneCommandsRequestedEventArgs, "f39a56a2-7db1-5c48-9e13-7dc485a4a99e")

.comdef __FITypedEventHandler_2_Windows__CUI__CApplicationSettings__CSettingsPane_Windows__CUI__CApplicationSettings__CSettingsPaneCommandsRequestedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace UI
.namespace ApplicationSettings

.enum SettingsEdgeLocation {
    SettingsEdgeLocation_Right	= 0,
    SettingsEdgeLocation_Left	= 1
    }

.enum SupportedWebAccountActions {
    SupportedWebAccountActions_None	= 0,
    SupportedWebAccountActions_Reconnect	= 0x1,
    SupportedWebAccountActions_Remove	= 0x2,
    SupportedWebAccountActions_ViewDetails	= 0x4,
    SupportedWebAccountActions_Manage	= 0x8,
    SupportedWebAccountActions_More	= 0x10
    }

.enum WebAccountAction {
    WebAccountAction_Reconnect	= 0,
    WebAccountAction_Remove	= 1,
    WebAccountAction_ViewDetails	= 2,
    WebAccountAction_Manage	= 3,
    WebAccountAction_More	= 4
    }

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CIWebAccountProviderCommandInvokedHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CIWebAccountProviderCommandInvokedHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IWebAccountProviderCommandInvokedHandler, "B7DE5527-4C8F-42DD-84DA-5EC493ABDB9A")

.comdef IWebAccountProviderCommandInvokedHandler : public IUnknown

    _Invoke		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CIWebAccountCommandInvokedHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CIWebAccountCommandInvokedHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IWebAccountCommandInvokedHandler, "1EE6E459-1705-4A9A-B599-A0C3D6921973")

.comdef IWebAccountCommandInvokedHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CICredentialCommandCredentialDeletedHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CICredentialCommandCredentialDeletedHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ICredentialCommandCredentialDeletedHandler, "61C0E185-0977-4678-B4E2-98727AFBEED9")

.comdef ICredentialCommandCredentialDeletedHandler : public IUnknown

    _Invoke		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CISettingsCommandFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CISettingsCommandFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ApplicationSettings_ISettingsCommandFactory <L"Windows.UI.ApplicationSettings.ISettingsCommandFactory">
DEFINE_IIDX(ISettingsCommandFactory, "68E15B33-1C83-433A-AA5A-CEEEA5BD4764")

.comdef ISettingsCommandFactory : public IInspectable

    CreateSettingsCommand proc :ptr, :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CISettingsCommandStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CISettingsCommandStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ApplicationSettings_ISettingsCommandStatics <L"Windows.UI.ApplicationSettings.ISettingsCommandStatics">
DEFINE_IIDX(ISettingsCommandStatics, "749AE954-2F69-4B17-8ABA-D05CE5778E46")

.comdef ISettingsCommandStatics : public IInspectable

    get_AccountsCommand proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CISettingsPaneCommandsRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CISettingsPaneCommandsRequest_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ApplicationSettings_ISettingsPaneCommandsRequest <L"Windows.UI.ApplicationSettings.ISettingsPaneCommandsRequest">
DEFINE_IIDX(ISettingsPaneCommandsRequest, "44DF23AE-5D6E-4068-A168-F47643182114")

.comdef ISettingsPaneCommandsRequest : public IInspectable

    get_ApplicationCommands proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CISettingsPaneCommandsRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CISettingsPaneCommandsRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ApplicationSettings_ISettingsPaneCommandsRequestedEventArgs <L"Windows.UI.ApplicationSettings.ISettingsPaneCommandsRequestedEventArgs">
DEFINE_IIDX(ISettingsPaneCommandsRequestedEventArgs, "205F5D24-1B48-4629-A6CA-2FDFEDAFB75D")

.comdef ISettingsPaneCommandsRequestedEventArgs : public IInspectable

    get_Request		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CISettingsPaneStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CISettingsPaneStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ApplicationSettings_ISettingsPaneStatics <L"Windows.UI.ApplicationSettings.ISettingsPaneStatics">
DEFINE_IIDX(ISettingsPaneStatics, "1C6A52C5-FF19-471B-BA6B-F8F35694AD9A")

.comdef ISettingsPaneStatics : public IInspectable

    GetForCurrentView	proc :ptr
    Show		proc
    get_Edge		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CISettingsPane_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CISettingsPane_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ApplicationSettings_ISettingsPane <L"Windows.UI.ApplicationSettings.ISettingsPane">
DEFINE_IIDX(ISettingsPane, "B1CD0932-4570-4C69-8D38-89446561ACE0")

.comdef ISettingsPane : public IInspectable

    add_CommandsRequested proc :ptr, :ptr
    remove_CommandsRequested proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CIWebAccountProviderCommandFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CIWebAccountProviderCommandFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ApplicationSettings_IWebAccountProviderCommandFactory <L"Windows.UI.ApplicationSettings.IWebAccountProviderCommandFactory">
DEFINE_IIDX(IWebAccountProviderCommandFactory, "D5658A1B-B176-4776-8469-A9D3FF0B3F59")

.comdef IWebAccountProviderCommandFactory : public IInspectable

    CreateWebAccountProviderCommand proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CIWebAccountCommandFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CIWebAccountCommandFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ApplicationSettings_IWebAccountCommandFactory <L"Windows.UI.ApplicationSettings.IWebAccountCommandFactory">
DEFINE_IIDX(IWebAccountCommandFactory, "BFA6CDFF-2F2D-42F5-81DE-1D56BAFC496D")

.comdef IWebAccountCommandFactory : public IInspectable

    CreateWebAccountCommand proc :ptr, :ptr, :Windows::UI::ApplicationSettings::SupportedWebAccountActions, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CICredentialCommandFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CICredentialCommandFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ApplicationSettings_ICredentialCommandFactory <L"Windows.UI.ApplicationSettings.ICredentialCommandFactory">
DEFINE_IIDX(ICredentialCommandFactory, "27E88C17-BC3E-4B80-9495-4ED720E48A91")

.comdef ICredentialCommandFactory : public IInspectable

    CreateCredentialCommand proc :ptr, :ptr
    CreateCredentialCommandWithHandler proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CIWebAccountProviderCommand_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CIWebAccountProviderCommand_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ApplicationSettings_IWebAccountProviderCommand <L"Windows.UI.ApplicationSettings.IWebAccountProviderCommand">
DEFINE_IIDX(IWebAccountProviderCommand, "D69BDD9A-A0A6-4E9B-88DC-C71E757A3501")

.comdef IWebAccountProviderCommand : public IInspectable

    get_WebAccountProvider proc :ptr
    get_Invoked		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CIWebAccountInvokedArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CIWebAccountInvokedArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ApplicationSettings_IWebAccountInvokedArgs <L"Windows.UI.ApplicationSettings.IWebAccountInvokedArgs">
DEFINE_IIDX(IWebAccountInvokedArgs, "E7ABCC40-A1D8-4C5D-9A7F-1D34B2F90AD2")

.comdef IWebAccountInvokedArgs : public IInspectable

    get_Action		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CIWebAccountCommand_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CIWebAccountCommand_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ApplicationSettings_IWebAccountCommand <L"Windows.UI.ApplicationSettings.IWebAccountCommand">
DEFINE_IIDX(IWebAccountCommand, "CAA39398-9CFA-4246-B0C4-A913A3896541")

.comdef IWebAccountCommand : public IInspectable

    get_WebAccount	proc :ptr
    get_Invoked		proc :ptr
    get_Actions		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CICredentialCommand_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CICredentialCommand_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ApplicationSettings_ICredentialCommand <L"Windows.UI.ApplicationSettings.ICredentialCommand">
DEFINE_IIDX(ICredentialCommand, "A5F665E6-6143-4A7A-A971-B017BA978CE2")

.comdef ICredentialCommand : public IInspectable

    get_PasswordCredential proc :ptr
    get_CredentialDeleted proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CIAccountsSettingsPaneEventDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CIAccountsSettingsPaneEventDeferral_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ApplicationSettings_IAccountsSettingsPaneEventDeferral <L"Windows.UI.ApplicationSettings.IAccountsSettingsPaneEventDeferral">
DEFINE_IIDX(IAccountsSettingsPaneEventDeferral, "CBF25D3F-E5BA-40EF-93DA-65E096E5FB04")

.comdef IAccountsSettingsPaneEventDeferral : public IInspectable

    Complete		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CIAccountsSettingsPaneCommandsRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CIAccountsSettingsPaneCommandsRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs <L"Windows.UI.ApplicationSettings.IAccountsSettingsPaneCommandsRequestedEventArgs">
DEFINE_IIDX(IAccountsSettingsPaneCommandsRequestedEventArgs, "3B68C099-DB19-45D0-9ABF-95D3773C9330")

.comdef IAccountsSettingsPaneCommandsRequestedEventArgs : public IInspectable

    get_WebAccountProviderCommands proc :ptr
    get_WebAccountCommands proc :ptr
    get_CredentialCommands proc :ptr
    get_Commands	proc :ptr
    get_HeaderText	proc :ptr
    put_HeaderText	proc :HSTRING
    GetDeferral		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CIAccountsSettingsPaneStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CIAccountsSettingsPaneStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ApplicationSettings_IAccountsSettingsPaneStatics <L"Windows.UI.ApplicationSettings.IAccountsSettingsPaneStatics">
DEFINE_IIDX(IAccountsSettingsPaneStatics, "561F8B60-B0EC-4150-A8DC-208EE44B068A")

.comdef IAccountsSettingsPaneStatics : public IInspectable

    GetForCurrentView	proc :ptr
    Show		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CApplicationSettings_CIAccountsSettingsPane_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CApplicationSettings_CIAccountsSettingsPane_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ApplicationSettings_IAccountsSettingsPane <L"Windows.UI.ApplicationSettings.IAccountsSettingsPane">
DEFINE_IIDX(IAccountsSettingsPane, "81EA942C-4F09-4406-A538-838D9B14B7E6")

.comdef IAccountsSettingsPane : public IInspectable

    add_AccountCommandsRequested proc :ptr, :ptr
    remove_AccountCommandsRequested proc :EventRegistrationToken
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_ApplicationSettings_SettingsCommand_DEFINED
define RUNTIMECLASS_Windows_UI_ApplicationSettings_SettingsCommand_DEFINED
define RuntimeClass_Windows_UI_ApplicationSettings_SettingsCommand <L"Windows.UI.ApplicationSettings.SettingsCommand">
endif
ifndef RUNTIMECLASS_Windows_UI_ApplicationSettings_SettingsPaneCommandsRequest_DEFINED
define RUNTIMECLASS_Windows_UI_ApplicationSettings_SettingsPaneCommandsRequest_DEFINED
define RuntimeClass_Windows_UI_ApplicationSettings_SettingsPaneCommandsRequest <L"Windows.UI.ApplicationSettings.SettingsPaneCommandsRequest">
endif
ifndef RUNTIMECLASS_Windows_UI_ApplicationSettings_SettingsPaneCommandsRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_ApplicationSettings_SettingsPaneCommandsRequestedEventArgs_DEFINED
define RuntimeClass_Windows_UI_ApplicationSettings_SettingsPaneCommandsRequestedEventArgs <L"Windows.UI.ApplicationSettings.SettingsPaneCommandsRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_ApplicationSettings_SettingsPane_DEFINED
define RUNTIMECLASS_Windows_UI_ApplicationSettings_SettingsPane_DEFINED
define RuntimeClass_Windows_UI_ApplicationSettings_SettingsPane <L"Windows.UI.ApplicationSettings.SettingsPane">
endif
ifndef RUNTIMECLASS_Windows_UI_ApplicationSettings_WebAccountProviderCommand_DEFINED
define RUNTIMECLASS_Windows_UI_ApplicationSettings_WebAccountProviderCommand_DEFINED
define RuntimeClass_Windows_UI_ApplicationSettings_WebAccountProviderCommand <L"Windows.UI.ApplicationSettings.WebAccountProviderCommand">
endif
ifndef RUNTIMECLASS_Windows_UI_ApplicationSettings_WebAccountCommand_DEFINED
define RUNTIMECLASS_Windows_UI_ApplicationSettings_WebAccountCommand_DEFINED
define RuntimeClass_Windows_UI_ApplicationSettings_WebAccountCommand <L"Windows.UI.ApplicationSettings.WebAccountCommand">
endif
ifndef RUNTIMECLASS_Windows_UI_ApplicationSettings_WebAccountInvokedArgs_DEFINED
define RUNTIMECLASS_Windows_UI_ApplicationSettings_WebAccountInvokedArgs_DEFINED
define RuntimeClass_Windows_UI_ApplicationSettings_WebAccountInvokedArgs <L"Windows.UI.ApplicationSettings.WebAccountInvokedArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_ApplicationSettings_CredentialCommand_DEFINED
define RUNTIMECLASS_Windows_UI_ApplicationSettings_CredentialCommand_DEFINED
define RuntimeClass_Windows_UI_ApplicationSettings_CredentialCommand <L"Windows.UI.ApplicationSettings.CredentialCommand">
endif
ifndef RUNTIMECLASS_Windows_UI_ApplicationSettings_AccountsSettingsPaneEventDeferral_DEFINED
define RUNTIMECLASS_Windows_UI_ApplicationSettings_AccountsSettingsPaneEventDeferral_DEFINED
define RuntimeClass_Windows_UI_ApplicationSettings_AccountsSettingsPaneEventDeferral <L"Windows.UI.ApplicationSettings.AccountsSettingsPaneEventDeferral">
endif
ifndef RUNTIMECLASS_Windows_UI_ApplicationSettings_AccountsSettingsPaneCommandsRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_ApplicationSettings_AccountsSettingsPaneCommandsRequestedEventArgs_DEFINED
define RuntimeClass_Windows_UI_ApplicationSettings_AccountsSettingsPaneCommandsRequestedEventArgs <L"Windows.UI.ApplicationSettings.AccountsSettingsPaneCommandsRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_ApplicationSettings_AccountsSettingsPane_DEFINED
define RUNTIMECLASS_Windows_UI_ApplicationSettings_AccountsSettingsPane_DEFINED
define RuntimeClass_Windows_UI_ApplicationSettings_AccountsSettingsPane <L"Windows.UI.ApplicationSettings.AccountsSettingsPane">
endif

endif
