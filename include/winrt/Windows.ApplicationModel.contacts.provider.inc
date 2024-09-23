ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __windows2Eapplicationmodel2Econtacts2Eprovider_h__
define __windows2Eapplicationmodel2Econtacts2Eprovider_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.ApplicationModel.Contacts.inc
include windows.foundation.collections.inc

ifndef ____FITypedEventHandler_2_Windows__CApplicationModel__CContacts__CProvider__CContactPickerUI_Windows__CApplicationModel__CContacts__CProvider__CContactRemovedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CApplicationModel__CContacts__CProvider__CContactPickerUI_Windows__CApplicationModel__CContacts__CProvider__CContactRemovedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CApplicationModel__CContacts__CProvider__CContactPickerUI_Windows__CApplicationModel__CContacts__CProvider__CContactRemovedEventArgs, "a39aeb7e-765c-5e83-b231-84bead98e9a0")

.comdef __FITypedEventHandler_2_Windows__CApplicationModel__CContacts__CProvider__CContactPickerUI_Windows__CApplicationModel__CContacts__CProvider__CContactRemovedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif


.namespace Windows
.namespace ApplicationModel
.namespace Contacts
.namespace Provider

.enum AddContactResult {
    AddContactResult_Added,
    AddContactResult_AlreadyAdded,
    AddContactResult_Unavailable
    }

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CProvider_CIContactRemovedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CProvider_CIContactRemovedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_Provider_IContactRemovedEventArgs <L"Windows.ApplicationModel.Contacts.Provider.IContactRemovedEventArgs">

DEFINE_IIDX(IContactRemovedEventArgs, "6F354338-3302-4D13-AD8D-ADCC0FF9E47C")

.comdef IContactRemovedEventArgs : public IInspectable

    get_Id		proc :ptr
   .ends

endif


ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CProvider_CIContactPickerUI_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CProvider_CIContactPickerUI_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_Provider_IContactPickerUI <L"Windows.ApplicationModel.Contacts.Provider.IContactPickerUI">

DEFINE_IIDX(IContactPickerUI, "E2CC1366-CF66-43C4-A96A-A5A112DB4746")

.comdef IContactPickerUI : public IInspectable

    AddContact		proc :HSTRING, :ptr, :ptr
    RemoveContact	proc :HSTRING
    ContainsContact	proc :HSTRING, :ptr
    get_DesiredFields	proc :ptr
    get_SelectionMode	proc :ptr
    add_ContactRemoved	proc :ptr, :ptr
    remove_ContactRemoved proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CContacts_CProvider_CIContactPickerUI2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CContacts_CProvider_CIContactPickerUI2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Contacts_Provider_IContactPickerUI2 <L"Windows.ApplicationModel.Contacts.Provider.IContactPickerUI2">

DEFINE_IIDX(IContactPickerUI2, "6E449E28-7B25-4999-9B0B-875400A1E8C8")

.comdef IContactPickerUI2 : public IInspectable

    AddContact		proc :ptr, :ptr
    get_DesiredFieldsWithContactFieldType proc :ptr
   .ends

endif

.endn
.endn
.endn
.endn

define RuntimeClass_Windows_ApplicationModel_Contacts_Provider_ContactRemovedEventArgs <L"Windows.ApplicationModel.Contacts.Provider.ContactRemovedEventArgs">
define RuntimeClass_Windows_ApplicationModel_Contacts_Provider_ContactPickerUI <L"Windows.ApplicationModel.Contacts.Provider.ContactPickerUI">

HSTRING_UserSize	proto WINAPI :ptr, :DWORD, :ptr
HSTRING_UserMarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree	proto WINAPI :ptr, :ptr

HSTRING_UserSize64	proto WINAPI :ptr, :DWORD, :ptr
HSTRING_UserMarshal64	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree64	proto WINAPI :ptr, :ptr

endif

