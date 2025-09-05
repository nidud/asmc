ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Esecurity2Ecredentials_h__
define __windows2Esecurity2Ecredentials_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

ifndef ____FIIterator_1_Windows__CSecurity__CCredentials__CPasswordCredential_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CSecurity__CCredentials__CPasswordCredential_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CSecurity__CCredentials__CPasswordCredential, "b01093d8-4f52-50f0-9aa4-e22639111162")

.comdef __FIIterator_1_Windows__CSecurity__CCredentials__CPasswordCredential : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CSecurity__CCredentials__CPasswordCredential_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CSecurity__CCredentials__CPasswordCredential_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CSecurity__CCredentials__CPasswordCredential, "0d224a66-bad5-5ad5-9ade-1e9f5a60fe73")

.comdef __FIIterable_1_Windows__CSecurity__CCredentials__CPasswordCredential : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CSecurity__CCredentials__CPasswordCredential_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CSecurity__CCredentials__CPasswordCredential_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CSecurity__CCredentials__CPasswordCredential, "4e6185ad-a6df-5428-aff5-17e45f3f476f")

.comdef __FIVectorView_1_Windows__CSecurity__CCredentials__CPasswordCredential : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Security
.namespace Credentials

.enum WebAccountState {
    WebAccountState_None	= 0,
    WebAccountState_Connected	= 1,
    WebAccountState_Error	= 2
    }

ifndef ____x_ABI_CWindows_CSecurity_CCredentials_CIPasswordCredential_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCredentials_CIPasswordCredential_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Credentials_IPasswordCredential <L"Windows.Security.Credentials.IPasswordCredential">
DEFINE_IIDX(IPasswordCredential, "6AB18989-C720-41A7-A6C1-FEADB36329A0")

.comdef IPasswordCredential : public IInspectable

    get_Resource	proc :ptr
    put_Resource	proc :HSTRING
    get_UserName	proc :ptr
    put_UserName	proc :HSTRING
    get_Password	proc :ptr
    put_Password	proc :HSTRING
    RetrievePassword	proc
    get_Properties	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCredentials_CICredentialFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCredentials_CICredentialFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Credentials_ICredentialFactory <L"Windows.Security.Credentials.ICredentialFactory">
DEFINE_IIDX(ICredentialFactory, "54EF13A1-BF26-47B5-97DD-DE779B7CAD58")

.comdef ICredentialFactory : public IInspectable

    CreatePasswordCredential proc :HSTRING, :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCredentials_CIPasswordVault_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCredentials_CIPasswordVault_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Credentials_IPasswordVault <L"Windows.Security.Credentials.IPasswordVault">
DEFINE_IIDX(IPasswordVault, "61FD2C0B-C8D4-48C1-A54F-BC5A64205AF2")

.comdef IPasswordVault : public IInspectable

    _Add		proc :ptr
    Remove		proc :ptr
    Retrieve		proc :HSTRING, :HSTRING, :ptr
    FindAllByResource	proc :HSTRING, :ptr
    FindAllByUserName	proc :HSTRING, :ptr
    RetrieveAll		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCredentials_CIWebAccountProviderFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCredentials_CIWebAccountProviderFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Credentials_IWebAccountProviderFactory <L"Windows.Security.Credentials.IWebAccountProviderFactory">
DEFINE_IIDX(IWebAccountProviderFactory, "1D767DF1-E1E1-4B9A-A774-5C7C7E3BF371")

.comdef IWebAccountProviderFactory : public IInspectable

    CreateWebAccountProvider proc :HSTRING, :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCredentials_CIWebAccountFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCredentials_CIWebAccountFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Credentials_IWebAccountFactory <L"Windows.Security.Credentials.IWebAccountFactory">
DEFINE_IIDX(IWebAccountFactory, "AC9AFB39-1DE9-4E92-B78F-0581A87F6E5C")

.comdef IWebAccountFactory : public IInspectable

    CreateWebAccount	proc :ptr, :HSTRING, :Windows::Security::Credentials::WebAccountState, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCredentials_CIWebAccountProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCredentials_CIWebAccountProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Credentials_IWebAccountProvider <L"Windows.Security.Credentials.IWebAccountProvider">
DEFINE_IIDX(IWebAccountProvider, "29DCC8C3-7AB9-4A7C-A336-B942F9DBF7C7")

.comdef IWebAccountProvider : public IInspectable

    get_Id		proc :ptr
    get_DisplayName	proc :ptr
    get_IconUri		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCredentials_CIWebAccount_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCredentials_CIWebAccount_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Credentials_IWebAccount <L"Windows.Security.Credentials.IWebAccount">
DEFINE_IIDX(IWebAccount, "69473EB2-8031-49BE-80BB-96CB46D99ABA")

.comdef IWebAccount : public IInspectable

    get_WebAccountProvider proc :ptr
    get_UserName	proc :ptr
    get_State		proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Security_Credentials_PasswordCredential_DEFINED
define RUNTIMECLASS_Windows_Security_Credentials_PasswordCredential_DEFINED
define RuntimeClass_Windows_Security_Credentials_PasswordCredential <L"Windows.Security.Credentials.PasswordCredential">
endif
ifndef RUNTIMECLASS_Windows_Security_Credentials_PasswordVault_DEFINED
define RUNTIMECLASS_Windows_Security_Credentials_PasswordVault_DEFINED
define RuntimeClass_Windows_Security_Credentials_PasswordVault <L"Windows.Security.Credentials.PasswordVault">
endif
ifndef RUNTIMECLASS_Windows_Security_Credentials_PasswordCredentialPropertyStore_DEFINED
define RUNTIMECLASS_Windows_Security_Credentials_PasswordCredentialPropertyStore_DEFINED
define RuntimeClass_Windows_Security_Credentials_PasswordCredentialPropertyStore <L"Windows.Security.Credentials.PasswordCredentialPropertyStore">
endif
ifndef RUNTIMECLASS_Windows_Security_Credentials_WebAccountProvider_DEFINED
define RUNTIMECLASS_Windows_Security_Credentials_WebAccountProvider_DEFINED
define RuntimeClass_Windows_Security_Credentials_WebAccountProvider <L"Windows.Security.Credentials.WebAccountProvider">
endif
ifndef RUNTIMECLASS_Windows_Security_Credentials_WebAccount_DEFINED
define RUNTIMECLASS_Windows_Security_Credentials_WebAccount_DEFINED
define RuntimeClass_Windows_Security_Credentials_WebAccount <L"Windows.Security.Credentials.WebAccount">
endif

endif
