ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Esecurity2Ecryptography2Edataprotection_h__
define __windows2Esecurity2Ecryptography2Edataprotection_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.Streams.inc

.namespace Windows
.namespace Security
.namespace Cryptography
.namespace DataProtection

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CDataProtection_CIDataProtectionProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CDataProtection_CIDataProtectionProvider_INTERFACE_DEFINED__
DEFINE_IIDX(IDataProtectionProvider, "09639948-ED22-4270-BD1C-6D72C00F8787")

.comdef IDataProtectionProvider

    QueryInterface      proc :REFIID, :ptr
    AddRef              proc
    Release             proc
    GetIids             proc :ptr, :ptr
    GetRuntimeClassName proc :ptr
    GetTrustLevel       proc :ptr
    ProtectAsync        proc :ptr, :ptr
    UnprotectAsync      proc :ptr, :ptr
    ProtectStreamAsync  proc :ptr, :ptr, :ptr
    UnprotectStreamAsync proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CDataProtection_CIDataProtectionProviderFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CDataProtection_CIDataProtectionProviderFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_DataProtection_IDataProtectionProviderFactory <L"Windows.Security.Cryptography.DataProtection.IDataProtectionProviderFactory">
DEFINE_IIDX(IDataProtectionProviderFactory, "ADF33DAC-4932-4CDF-AC41-7214333514CA")

.comdef IDataProtectionProviderFactory : public IInspectable

    CreateOverloadExplicit proc :HSTRING, :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Security_Cryptography_DataProtection_DataProtectionProvider_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_DataProtection_DataProtectionProvider_DEFINED
define RuntimeClass_Windows_Security_Cryptography_DataProtection_DataProtectionProvider <L"Windows.Security.Cryptography.DataProtection.DataProtectionProvider">
endif

endif
