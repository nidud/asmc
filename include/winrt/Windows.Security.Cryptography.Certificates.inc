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

ifndef __windows2Esecurity2Ecryptography2Ecertificates_h__
define __windows2Esecurity2Ecryptography2Ecertificates_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Networking.inc
include Windows.Storage.Streams.inc
include windows.foundation.collections.inc

.namespace Windows
.namespace Security
.namespace Cryptography
.namespace Certificates

.enum EnrollKeyUsages {
    EnrollKeyUsages_None	= 0,
    EnrollKeyUsages_Decryption	= 0x1,
    EnrollKeyUsages_Signing	= 0x2,
    EnrollKeyUsages_KeyAgreement	= 0x4,
    EnrollKeyUsages_All = 0xffffff
    }

.enum KeyProtectionLevel {
    KeyProtectionLevel_NoConsent	= 0,
    KeyProtectionLevel_ConsentOnly	= 1,
    KeyProtectionLevel_ConsentWithPassword	= 2,
    KeyProtectionLevel_ConsentWithFingerprint	= 3
    }

.enum ExportOption {
    ExportOption_NotExportable	= 0,
    ExportOption_Exportable	= 1
    }

.enum KeySize {
    KeySize_Invalid	= 0,
    KeySize_Rsa2048	= 2048,
    KeySize_Rsa4096	= 4096
    }

.enum InstallOptions {
    InstallOptions_None = 0,
    InstallOptions_DeleteExpired	= 0x1
    }

.enum CertificateChainPolicy {
    CertificateChainPolicy_Base = 0,
    CertificateChainPolicy_Ssl	= 1,
    CertificateChainPolicy_NTAuthentication	= 2,
    CertificateChainPolicy_MicrosoftRoot	= 3
    }

.enum ChainValidationResult {
    ChainValidationResult_Success	= 0,
    ChainValidationResult_Untrusted	= 1,
    ChainValidationResult_Revoked	= 2,
    ChainValidationResult_Expired	= 3,
    ChainValidationResult_IncompleteChain	= 4,
    ChainValidationResult_InvalidSignature	= 5,
    ChainValidationResult_WrongUsage	= 6,
    ChainValidationResult_InvalidName	= 7,
    ChainValidationResult_InvalidCertificateAuthorityPolicy	= 8,
    ChainValidationResult_BasicConstraintsError = 9,
    ChainValidationResult_UnknownCriticalExtension	= 10,
    ChainValidationResult_RevocationInformationMissing	= 11,
    ChainValidationResult_RevocationFailure	= 12,
    ChainValidationResult_OtherErrors	= 13
    }

.enum SignatureValidationResult {
    SignatureValidationResult_Success	= 0,
    SignatureValidationResult_InvalidParameter	= 1,
    SignatureValidationResult_BadMessage	= 2,
    SignatureValidationResult_InvalidSignature	= 3,
    SignatureValidationResult_OtherErrors	= 4
    }

.endn
.endn
.endn
.endn

ifndef ____FIIterator_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate_INTERFACE_DEFINED__

.comdef __FIIterator_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate : public IInspectable
DEFINE_IIDX(__FIIterator_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate, "676fc159-f15c-58bd-91a7-28f7e795c756")

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate, "0c7d1423-e8fd-5a91-b55c-8bfbe7ac2d40")

.comdef __FIIterable_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CSecurity__CCryptography__CCertificates__CChainValidationResult_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CSecurity__CCryptography__CCertificates__CChainValidationResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CSecurity__CCryptography__CCertificates__CChainValidationResult, "8bcad2b7-0e3b-5eae-bf69-e1f6d9c888f8")

.comdef __FIIterator_1_Windows__CSecurity__CCryptography__CCertificates__CChainValidationResult : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CSecurity__CCryptography__CCertificates__CChainValidationResult_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CSecurity__CCryptography__CCertificates__CChainValidationResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CSecurity__CCryptography__CCertificates__CChainValidationResult, "2628f58f-3f02-54f2-808f-e1117709d6d0")

.comdef __FIIterable_1_Windows__CSecurity__CCryptography__CCertificates__CChainValidationResult : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CSecurity__CCryptography__CCertificates__CCmsSignerInfo_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CSecurity__CCryptography__CCertificates__CCmsSignerInfo_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CSecurity__CCryptography__CCertificates__CCmsSignerInfo, "ba691628-d419-5e0a-b924-03ebc236b11e")

.comdef __FIIterator_1_Windows__CSecurity__CCryptography__CCertificates__CCmsSignerInfo : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CSecurity__CCryptography__CCertificates__CCmsSignerInfo_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CSecurity__CCryptography__CCertificates__CCmsSignerInfo_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CSecurity__CCryptography__CCertificates__CCmsSignerInfo, "6af24174-2dda-5a54-a0b9-4d6690059427")

.comdef __FIIterable_1_Windows__CSecurity__CCryptography__CCertificates__CCmsSignerInfo : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate, "963f7013-77c2-51c5-8038-b5bcef633edb")

.comdef __FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CChainValidationResult_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CChainValidationResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CChainValidationResult, "cb383486-c2bc-5756-912d-6a708a07e5bd")

.comdef __FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CChainValidationResult : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :Windows::Security::Cryptography::Certificates::ChainValidationResult, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CCmsSignerInfo_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CCmsSignerInfo_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CCmsSignerInfo, "f46bcaa8-747c-5a93-82fe-85d63549fe81")

.comdef __FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CCmsSignerInfo : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate, "36282c0f-2f1f-57f4-b2b1-867af90c3d13")

.comdef __FIVector_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate : public IInspectable

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

ifndef ____FIVector_1_Windows__CSecurity__CCryptography__CCertificates__CChainValidationResult_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CSecurity__CCryptography__CCertificates__CChainValidationResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CSecurity__CCryptography__CCertificates__CChainValidationResult, "d7828cf7-4301-58d3-aab5-06e5eefcf79f")

.comdef __FIVector_1_Windows__CSecurity__CCryptography__CCertificates__CChainValidationResult : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :Windows::Security::Cryptography::Certificates::ChainValidationResult, :ptr, :ptr
    SetAt		proc :SINT, :Windows::Security::Cryptography::Certificates::ChainValidationResult
    InsertAt		proc :SINT, :Windows::Security::Cryptography::Certificates::ChainValidationResult
    RemoveAt		proc :SINT
    Append		proc :Windows::Security::Cryptography::Certificates::ChainValidationResult
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate, "1896faee-23e2-59ca-9802-0f48eed98ef4")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate, "9b26648e-b32f-5909-a635-78e6d3bb4067")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CSecurity__CCryptography__CCertificates__CCertificate : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCryptography__CCertificates__CCertificateChain_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCryptography__CCertificates__CCertificateChain_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCryptography__CCertificates__CCertificateChain, "4c3f50e9-90e3-5a30-9015-4aa0376904f3")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCryptography__CCertificates__CCertificateChain : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CSecurity__CCryptography__CCertificates__CCertificateChain_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CSecurity__CCryptography__CCertificates__CCertificateChain_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CSecurity__CCryptography__CCertificates__CCertificateChain, "f618c7d4-aee1-58ae-afe8-fc336daf0395")

.comdef __FIAsyncOperation_1_Windows__CSecurity__CCryptography__CCertificates__CCertificateChain : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCryptography__CCertificates__CSignatureValidationResult_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCryptography__CCertificates__CSignatureValidationResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCryptography__CCertificates__CSignatureValidationResult, "dff50005-78ad-5f4f-a085-cb614a674a25")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCryptography__CCertificates__CSignatureValidationResult : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CSecurity__CCryptography__CCertificates__CSignatureValidationResult_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CSecurity__CCryptography__CCertificates__CSignatureValidationResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CSecurity__CCryptography__CCertificates__CSignatureValidationResult, "f09c0bcf-ce3b-5dff-971f-2c3ffe6fd04d")

.comdef __FIAsyncOperation_1_Windows__CSecurity__CCryptography__CCertificates__CSignatureValidationResult : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Security
.namespace Cryptography
.namespace Certificates

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateRequestProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateRequestProperties_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICertificateRequestProperties <L"Windows.Security.Cryptography.Certificates.ICertificateRequestProperties">
DEFINE_IIDX(ICertificateRequestProperties, "487E84F6-94E2-4DCE-8833-1A700A37A29A")

.comdef ICertificateRequestProperties : public IInspectable

    get_Subject		proc :ptr
    put_Subject		proc :HSTRING
    get_KeyAlgorithmName proc :ptr
    put_KeyAlgorithmName proc :HSTRING
    get_KeySize		proc :ptr
    put_KeySize		proc :UINT32
    get_FriendlyName	proc :ptr
    put_FriendlyName	proc :HSTRING
    get_HashAlgorithmName proc :ptr
    put_HashAlgorithmName proc :HSTRING
    get_Exportable	proc :ptr
    put_Exportable	proc :Windows::Security::Cryptography::Certificates::ExportOption
    get_KeyUsages	proc :ptr
    put_KeyUsages	proc :Windows::Security::Cryptography::Certificates::EnrollKeyUsages
    get_KeyProtectionLevel proc :ptr
    put_KeyProtectionLevel proc :Windows::Security::Cryptography::Certificates::KeyProtectionLevel
    get_KeyStorageProviderName proc :ptr
    put_KeyStorageProviderName proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateRequestProperties2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateRequestProperties2_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICertificateRequestProperties2 <L"Windows.Security.Cryptography.Certificates.ICertificateRequestProperties2">
DEFINE_IIDX(ICertificateRequestProperties2, "3DA0C954-D73F-4FF3-A0A6-0677C0ADA05B")

.comdef ICertificateRequestProperties2 : public IInspectable

    get_SmartcardReaderName proc :ptr
    put_SmartcardReaderName proc :HSTRING
    get_SigningCertificate proc :ptr
    put_SigningCertificate proc :ptr
    get_AttestationCredentialCertificate proc :ptr
    put_AttestationCredentialCertificate proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateEnrollmentManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateEnrollmentManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICertificateEnrollmentManagerStatics <L"Windows.Security.Cryptography.Certificates.ICertificateEnrollmentManagerStatics">
DEFINE_IIDX(ICertificateEnrollmentManagerStatics, "8846EF3F-A986-48FB-9FD7-9AEC06935BF1")

.comdef ICertificateEnrollmentManagerStatics : public IInspectable

    CreateRequestAsync	proc :ptr, :ptr
    InstallCertificateAsync proc :HSTRING, :Windows::Security::Cryptography::Certificates::InstallOptions, :ptr
    ImportPfxDataAsync	proc :HSTRING, :HSTRING, :Windows::Security::Cryptography::Certificates::ExportOption, :Windows::Security::Cryptography::Certificates::KeyProtectionLevel, :Windows::Security::Cryptography::Certificates::InstallOptions, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateEnrollmentManagerStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateEnrollmentManagerStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICertificateEnrollmentManagerStatics2 <L"Windows.Security.Cryptography.Certificates.ICertificateEnrollmentManagerStatics2">
DEFINE_IIDX(ICertificateEnrollmentManagerStatics2, "DC5B1C33-6429-4014-999C-5D9735802D1D")

.comdef ICertificateEnrollmentManagerStatics2 : public IInspectable

    get_UserCertificateEnrollmentManager proc :ptr
    ImportPfxDataToKspAsync proc :HSTRING, :HSTRING, :Windows::Security::Cryptography::Certificates::ExportOption, :Windows::Security::Cryptography::Certificates::KeyProtectionLevel, :Windows::Security::Cryptography::Certificates::InstallOptions, :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CIKeyAttestationHelperStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CIKeyAttestationHelperStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_IKeyAttestationHelperStatics <L"Windows.Security.Cryptography.Certificates.IKeyAttestationHelperStatics">
DEFINE_IIDX(IKeyAttestationHelperStatics, "1648E246-F644-4326-88BE-3AF102D30E0C")

.comdef IKeyAttestationHelperStatics : public IInspectable

    DecryptTpmAttestationCredentialAsync proc :HSTRING, :ptr
    GetTpmAttestationCredentialId proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateStoresStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateStoresStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICertificateStoresStatics <L"Windows.Security.Cryptography.Certificates.ICertificateStoresStatics">
DEFINE_IIDX(ICertificateStoresStatics, "FBECC739-C6FE-4DE7-99CF-74C3E596E032")

.comdef ICertificateStoresStatics : public IInspectable

    FindAllAsync	proc :ptr
    FindAllWithQueryAsync proc :ptr, :ptr
    get_TrustedRootCertificationAuthorities proc :ptr
    get_IntermediateCertificationAuthorities proc :ptr
    GetStoreByName	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CIUserCertificateEnrollmentManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CIUserCertificateEnrollmentManager_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_IUserCertificateEnrollmentManager <L"Windows.Security.Cryptography.Certificates.IUserCertificateEnrollmentManager">
DEFINE_IIDX(IUserCertificateEnrollmentManager, "96313718-22E1-4819-B20B-AB46A6ECA06E")

.comdef IUserCertificateEnrollmentManager : public IInspectable

    CreateRequestAsync	proc :ptr, :ptr
    InstallCertificateAsync proc :HSTRING, :Windows::Security::Cryptography::Certificates::InstallOptions, :ptr
    ImportPfxDataAsync	proc :HSTRING, :HSTRING, :Windows::Security::Cryptography::Certificates::ExportOption, :Windows::Security::Cryptography::Certificates::KeyProtectionLevel, :Windows::Security::Cryptography::Certificates::InstallOptions, :HSTRING, :ptr
    ImportPfxDataToKspAsync proc :HSTRING, :HSTRING, :Windows::Security::Cryptography::Certificates::ExportOption, :Windows::Security::Cryptography::Certificates::KeyProtectionLevel, :Windows::Security::Cryptography::Certificates::InstallOptions, :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateStore_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateStore_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICertificateStore <L"Windows.Security.Cryptography.Certificates.ICertificateStore">
DEFINE_IIDX(ICertificateStore, "B0BFF720-344E-4331-AF14-A7F7A7EBC93A")

.comdef ICertificateStore : public IInspectable

    _Add		proc :ptr
    Delete		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CIKeyAlgorithmNamesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CIKeyAlgorithmNamesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_IKeyAlgorithmNamesStatics <L"Windows.Security.Cryptography.Certificates.IKeyAlgorithmNamesStatics">
DEFINE_IIDX(IKeyAlgorithmNamesStatics, "479065D7-7AC7-4581-8C3B-D07027140448")

.comdef IKeyAlgorithmNamesStatics : public IInspectable

    get_Rsa		proc :ptr
    get_Dsa		proc :ptr
    get_Ecdh256		proc :ptr
    get_Ecdh384		proc :ptr
    get_Ecdh521		proc :ptr
    get_Ecdsa256	proc :ptr
    get_Ecdsa384	proc :ptr
    get_Ecdsa521	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CIKeyStorageProviderNamesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CIKeyStorageProviderNamesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_IKeyStorageProviderNamesStatics <L"Windows.Security.Cryptography.Certificates.IKeyStorageProviderNamesStatics">
DEFINE_IIDX(IKeyStorageProviderNamesStatics, "AF186AE0-5529-4602-BD94-0AAB91957B5C")

.comdef IKeyStorageProviderNamesStatics : public IInspectable

    get_SoftwareKeyStorageProvider proc :ptr
    get_SmartcardKeyStorageProvider proc :ptr
    get_PlatformKeyStorageProvider proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CIChainBuildingParameters_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CIChainBuildingParameters_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_IChainBuildingParameters <L"Windows.Security.Cryptography.Certificates.IChainBuildingParameters">
DEFINE_IIDX(IChainBuildingParameters, "422BA922-7C8D-47B7-B59B-B12703733AC3")

.comdef IChainBuildingParameters : public IInspectable

    get_EnhancedKeyUsages proc :ptr
    get_ValidationTimestamp proc :ptr
    put_ValidationTimestamp proc :Windows::Foundation::DateTime
    get_RevocationCheckEnabled proc :ptr
    put_RevocationCheckEnabled proc :boolean
    get_NetworkRetrievalEnabled proc :ptr
    put_NetworkRetrievalEnabled proc :boolean
    get_AuthorityInformationAccessEnabled proc :ptr
    put_AuthorityInformationAccessEnabled proc :boolean
    get_CurrentTimeValidationEnabled proc :ptr
    put_CurrentTimeValidationEnabled proc :boolean
    get_ExclusiveTrustRoots proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CIChainValidationParameters_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CIChainValidationParameters_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_IChainValidationParameters <L"Windows.Security.Cryptography.Certificates.IChainValidationParameters">
DEFINE_IIDX(IChainValidationParameters, "C4743B4A-7EB0-4B56-A040-B9C8E655DDF3")

.comdef IChainValidationParameters : public IInspectable

    get_CertificateChainPolicy proc :ptr
    put_CertificateChainPolicy proc :Windows::Security::Cryptography::Certificates::CertificateChainPolicy
    get_ServerDnsName	proc :ptr
    put_ServerDnsName	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateQuery_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateQuery_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICertificateQuery <L"Windows.Security.Cryptography.Certificates.ICertificateQuery">
DEFINE_IIDX(ICertificateQuery, "5B082A31-A728-4916-B5EE-FFCB8ACF2417")

.comdef ICertificateQuery : public IInspectable

    get_EnhancedKeyUsages proc :ptr
    get_IssuerName	proc :ptr
    put_IssuerName	proc :HSTRING
    get_FriendlyName	proc :ptr
    put_FriendlyName	proc :HSTRING
    get_Thumbprint	proc :ptr, :ptr
    put_Thumbprint	proc :UINT32, :ptr
    get_HardwareOnly	proc :ptr
    put_HardwareOnly	proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateChain_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateChain_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICertificateChain <L"Windows.Security.Cryptography.Certificates.ICertificateChain">
DEFINE_IIDX(ICertificateChain, "20BF5385-3691-4501-A62C-FD97278B31EE")

.comdef ICertificateChain : public IInspectable

    Validate		proc :ptr
    ValidateWithParameters proc :ptr, :ptr
    GetCertificates	proc :boolean, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificate_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificate_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICertificate <L"Windows.Security.Cryptography.Certificates.ICertificate">
DEFINE_IIDX(ICertificate, "333F740C-04D8-43B3-B278-8C5FCC9BE5A0")

.comdef ICertificate : public IInspectable

    BuildChainAsync	proc :ptr, :ptr
    BuildChainWithParametersAsync proc :ptr, :ptr, :ptr
    get_SerialNumber	proc :ptr, :ptr
    GetHashValue	proc :ptr, :ptr
    GetHashValueWithAlgorithm proc :HSTRING, :ptr, :ptr
    GetCertificateBlob	proc :ptr
    get_Subject		proc :ptr
    get_Issuer		proc :ptr
    get_HasPrivateKey	proc :ptr
    get_IsStronglyProtected proc :ptr
    get_ValidFrom	proc :ptr
    get_ValidTo		proc :ptr
    get_EnhancedKeyUsages proc :ptr
    put_FriendlyName	proc :HSTRING
    get_FriendlyName	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICertificateFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICertificateFactory <L"Windows.Security.Cryptography.Certificates.ICertificateFactory">
DEFINE_IIDX(ICertificateFactory, "17B4221C-4BAF-44A2-9608-04FB62B16942")

.comdef ICertificateFactory : public IInspectable

    CreateCertificate	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICmsTimestampInfo_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICmsTimestampInfo_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICmsTimestampInfo <L"Windows.Security.Cryptography.Certificates.ICmsTimestampInfo">
DEFINE_IIDX(ICmsTimestampInfo, "2F5F00F2-2C18-4F88-8435-C534086076F5")

.comdef ICmsTimestampInfo : public IInspectable

    get_SigningCertificate proc :ptr
    get_Certificates	proc :ptr
    get_Timestamp	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICmsSignerInfo_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICmsSignerInfo_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICmsSignerInfo <L"Windows.Security.Cryptography.Certificates.ICmsSignerInfo">
DEFINE_IIDX(ICmsSignerInfo, "50D020DB-1D2F-4C1A-B5C5-D0188FF91F47")

.comdef ICmsSignerInfo : public IInspectable

    get_Certificate	proc :ptr
    put_Certificate	proc :ptr
    get_HashAlgorithmName proc :ptr
    put_HashAlgorithmName proc :HSTRING
    get_TimestampInfo	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICmsAttachedSignature_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICmsAttachedSignature_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICmsAttachedSignature <L"Windows.Security.Cryptography.Certificates.ICmsAttachedSignature">
DEFINE_IIDX(ICmsAttachedSignature, "61899D9D-3757-4ECB-BDDC-0CA357D7A936")

.comdef ICmsAttachedSignature : public IInspectable

    get_Certificates	proc :ptr
    get_Content		proc :ptr, :ptr
    get_Signers		proc :ptr
    VerifySignature	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICmsAttachedSignatureFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICmsAttachedSignatureFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICmsAttachedSignatureFactory <L"Windows.Security.Cryptography.Certificates.ICmsAttachedSignatureFactory">
DEFINE_IIDX(ICmsAttachedSignatureFactory, "D0C8FC15-F757-4C64-A362-52CC1C77CFFB")

.comdef ICmsAttachedSignatureFactory : public IInspectable

    CreateCmsAttachedSignature proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICmsAttachedSignatureStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICmsAttachedSignatureStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICmsAttachedSignatureStatics <L"Windows.Security.Cryptography.Certificates.ICmsAttachedSignatureStatics">
DEFINE_IIDX(ICmsAttachedSignatureStatics, "87989C8E-B0AD-498D-A7F5-78B59BCE4B36")

.comdef ICmsAttachedSignatureStatics : public IInspectable

    GenerateSignatureAsync proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICmsDetachedSignature_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICmsDetachedSignature_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICmsDetachedSignature <L"Windows.Security.Cryptography.Certificates.ICmsDetachedSignature">
DEFINE_IIDX(ICmsDetachedSignature, "0F1EF154-F65E-4536-8339-5944081DB2CA")

.comdef ICmsDetachedSignature : public IInspectable

    get_Certificates	proc :ptr
    get_Signers		proc :ptr
    VerifySignatureAsync proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICmsDetachedSignatureFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICmsDetachedSignatureFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICmsDetachedSignatureFactory <L"Windows.Security.Cryptography.Certificates.ICmsDetachedSignatureFactory">
DEFINE_IIDX(ICmsDetachedSignatureFactory, "C4AB3503-AE7F-4387-AD19-00F150E48EBB")

.comdef ICmsDetachedSignatureFactory : public IInspectable

    CreateCmsDetachedSignature proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICmsDetachedSignatureStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCertificates_CICmsDetachedSignatureStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Certificates_ICmsDetachedSignatureStatics <L"Windows.Security.Cryptography.Certificates.ICmsDetachedSignatureStatics">
DEFINE_IIDX(ICmsDetachedSignatureStatics, "3D114CFD-BF9B-4682-9BE6-91F57C053808")

.comdef ICmsDetachedSignatureStatics : public IInspectable

    GenerateSignatureAsync proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Security_Cryptography_Certificates_Certificate_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Certificates_Certificate_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Certificates_Certificate <L"Windows.Security.Cryptography.Certificates.Certificate">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CertificateRequestProperties_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CertificateRequestProperties_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Certificates_CertificateRequestProperties <L"Windows.Security.Cryptography.Certificates.CertificateRequestProperties">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Certificates_UserCertificateEnrollmentManager_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Certificates_UserCertificateEnrollmentManager_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Certificates_UserCertificateEnrollmentManager <L"Windows.Security.Cryptography.Certificates.UserCertificateEnrollmentManager">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CertificateEnrollmentManager_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CertificateEnrollmentManager_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Certificates_CertificateEnrollmentManager <L"Windows.Security.Cryptography.Certificates.CertificateEnrollmentManager">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Certificates_KeyAttestationHelper_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Certificates_KeyAttestationHelper_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Certificates_KeyAttestationHelper <L"Windows.Security.Cryptography.Certificates.KeyAttestationHelper">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CertificateQuery_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CertificateQuery_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Certificates_CertificateQuery <L"Windows.Security.Cryptography.Certificates.CertificateQuery">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CertificateStore_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CertificateStore_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Certificates_CertificateStore <L"Windows.Security.Cryptography.Certificates.CertificateStore">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CertificateStores_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CertificateStores_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Certificates_CertificateStores <L"Windows.Security.Cryptography.Certificates.CertificateStores">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Certificates_KeyAlgorithmNames_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Certificates_KeyAlgorithmNames_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Certificates_KeyAlgorithmNames <L"Windows.Security.Cryptography.Certificates.KeyAlgorithmNames">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Certificates_KeyStorageProviderNames_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Certificates_KeyStorageProviderNames_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Certificates_KeyStorageProviderNames <L"Windows.Security.Cryptography.Certificates.KeyStorageProviderNames">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Certificates_ChainBuildingParameters_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Certificates_ChainBuildingParameters_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Certificates_ChainBuildingParameters <L"Windows.Security.Cryptography.Certificates.ChainBuildingParameters">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Certificates_ChainValidationParameters_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Certificates_ChainValidationParameters_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Certificates_ChainValidationParameters <L"Windows.Security.Cryptography.Certificates.ChainValidationParameters">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CertificateChain_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CertificateChain_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Certificates_CertificateChain <L"Windows.Security.Cryptography.Certificates.CertificateChain">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CmsTimestampInfo_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CmsTimestampInfo_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Certificates_CmsTimestampInfo <L"Windows.Security.Cryptography.Certificates.CmsTimestampInfo">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CmsSignerInfo_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CmsSignerInfo_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Certificates_CmsSignerInfo <L"Windows.Security.Cryptography.Certificates.CmsSignerInfo">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CmsAttachedSignature_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CmsAttachedSignature_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Certificates_CmsAttachedSignature <L"Windows.Security.Cryptography.Certificates.CmsAttachedSignature">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CmsDetachedSignature_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Certificates_CmsDetachedSignature_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Certificates_CmsDetachedSignature <L"Windows.Security.Cryptography.Certificates.CmsDetachedSignature">
endif

endif
