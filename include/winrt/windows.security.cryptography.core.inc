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

ifndef __windows2Esecurity2Ecryptography2Ecore_h__
define __windows2Esecurity2Ecryptography2Ecore_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Security.Cryptography.Certificates.inc
include windows.foundation.collections.inc

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCryptography__CCore__CCryptographicKey_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCryptography__CCore__CCryptographicKey_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCryptography__CCore__CCryptographicKey, "04ca4378-f594-5de6-a555-304f62cb4faf")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCryptography__CCore__CCryptographicKey : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CSecurity__CCryptography__CCore__CCryptographicKey_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CSecurity__CCryptography__CCore__CCryptographicKey_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CSecurity__CCryptography__CCore__CCryptographicKey, "81ca789b-98df-5c6a-9531-966238e3e7ae")

.comdef __FIAsyncOperation_1_Windows__CSecurity__CCryptography__CCore__CCryptographicKey : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Security
.namespace Cryptography
.namespace Core

.enum CryptographicPrivateKeyBlobType {
    CryptographicPrivateKeyBlobType_Pkcs8RawPrivateKeyInfo	= 0,
    CryptographicPrivateKeyBlobType_Pkcs1RsaPrivateKey	= 1,
    CryptographicPrivateKeyBlobType_BCryptPrivateKey	= 2,
    CryptographicPrivateKeyBlobType_Capi1PrivateKey	= 3
    }

.enum CryptographicPublicKeyBlobType {
    CryptographicPublicKeyBlobType_X509SubjectPublicKeyInfo	= 0,
    CryptographicPublicKeyBlobType_Pkcs1RsaPublicKey	= 1,
    CryptographicPublicKeyBlobType_BCryptPublicKey	= 2,
    CryptographicPublicKeyBlobType_Capi1PublicKey	= 3
    }

.enum CryptographicPadding {
    CryptographicPadding_None	= 0,
    CryptographicPadding_RsaOaep	= 1,
    CryptographicPadding_RsaPkcs1V15	= 2,
    CryptographicPadding_RsaPss = 3
    }

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIKeyDerivationParameters_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIKeyDerivationParameters_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IKeyDerivationParameters <L"Windows.Security.Cryptography.Core.IKeyDerivationParameters">
DEFINE_IIDX(IKeyDerivationParameters, "7BF05967-047B-4A8C-964A-469FFD5522E2")

.comdef IKeyDerivationParameters : public IInspectable

    get_KdfGenericBinary proc :ptr
    put_KdfGenericBinary proc :ptr
    get_IterationCount	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIKeyDerivationParametersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIKeyDerivationParametersStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IKeyDerivationParametersStatics <L"Windows.Security.Cryptography.Core.IKeyDerivationParametersStatics">
DEFINE_IIDX(IKeyDerivationParametersStatics, "EA961FBE-F37F-4146-9DFE-A456F1735F4B")

.comdef IKeyDerivationParametersStatics : public IInspectable

    BuildForPbkdf2	proc :ptr, :UINT32, :ptr
    BuildForSP800108	proc :ptr, :ptr, :ptr
    BuildForSP80056a	proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CICryptographicKey_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CICryptographicKey_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_ICryptographicKey <L"Windows.Security.Cryptography.Core.ICryptographicKey">
DEFINE_IIDX(ICryptographicKey, "ED2A3B70-8E7B-4009-8401-FFD1A62EEB27")

.comdef ICryptographicKey : public IInspectable

    get_KeySize		proc :ptr
    ExportDefaultPrivateKeyBlobType proc :ptr
    ExportPrivateKeyWithBlobType proc :Windows::Security::Cryptography::Core::CryptographicPrivateKeyBlobType, :ptr
    ExportDefaultPublicKeyBlobType proc :ptr
    ExportPublicKeyWithBlobType proc :Windows::Security::Cryptography::Core::CryptographicPublicKeyBlobType, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIHashComputation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIHashComputation_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IHashComputation <L"Windows.Security.Cryptography.Core.IHashComputation">
DEFINE_IIDX(IHashComputation, "5904D1B6-AD31-4603-A3A4-B1BDA98E2562")

.comdef IHashComputation : public IInspectable

    Append		proc :ptr
    GetValueAndReset	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIHashAlgorithmProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIHashAlgorithmProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IHashAlgorithmProvider <L"Windows.Security.Cryptography.Core.IHashAlgorithmProvider">
DEFINE_IIDX(IHashAlgorithmProvider, "BE9B3080-B2C3-422B-BCE1-EC90EFB5D7B5")

.comdef IHashAlgorithmProvider : public IInspectable

    get_AlgorithmName	proc :ptr
    get_HashLength	proc :ptr
    HashData		proc :ptr, :ptr
    CreateHash		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIMacAlgorithmProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIMacAlgorithmProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IMacAlgorithmProvider <L"Windows.Security.Cryptography.Core.IMacAlgorithmProvider">
DEFINE_IIDX(IMacAlgorithmProvider, "4A3FC5C3-1CBD-41CE-A092-AA0BC5D2D2F5")

.comdef IMacAlgorithmProvider : public IInspectable

    get_AlgorithmName	proc :ptr
    get_MacLength	proc :ptr
    CreateKey		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIMacAlgorithmProvider2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIMacAlgorithmProvider2_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IMacAlgorithmProvider2 <L"Windows.Security.Cryptography.Core.IMacAlgorithmProvider2">
DEFINE_IIDX(IMacAlgorithmProvider2, "6DA32A15-D931-42ED-8E7E-C301CAEE119C")

.comdef IMacAlgorithmProvider2 : public IInspectable

    CreateHash		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIKeyDerivationAlgorithmProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIKeyDerivationAlgorithmProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IKeyDerivationAlgorithmProvider <L"Windows.Security.Cryptography.Core.IKeyDerivationAlgorithmProvider">
DEFINE_IIDX(IKeyDerivationAlgorithmProvider, "E1FBA83B-4671-43B7-9158-763AAA98B6BF")

.comdef IKeyDerivationAlgorithmProvider : public IInspectable

    get_AlgorithmName	proc :ptr
    CreateKey		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CISymmetricKeyAlgorithmProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CISymmetricKeyAlgorithmProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_ISymmetricKeyAlgorithmProvider <L"Windows.Security.Cryptography.Core.ISymmetricKeyAlgorithmProvider">
DEFINE_IIDX(ISymmetricKeyAlgorithmProvider, "3D7E4A33-3BD0-4902-8AC8-470D50D21376")

.comdef ISymmetricKeyAlgorithmProvider : public IInspectable

    get_AlgorithmName	proc :ptr
    get_BlockLength	proc :ptr
    CreateSymmetricKey	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIAsymmetricKeyAlgorithmProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIAsymmetricKeyAlgorithmProvider_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IAsymmetricKeyAlgorithmProvider <L"Windows.Security.Cryptography.Core.IAsymmetricKeyAlgorithmProvider">
DEFINE_IIDX(IAsymmetricKeyAlgorithmProvider, "E8D2FF37-6259-4E88-B7E0-94191FDE699E")

.comdef IAsymmetricKeyAlgorithmProvider : public IInspectable

    get_AlgorithmName	proc :ptr
    CreateKeyPair	proc :UINT32, :ptr
    ImportDefaultPrivateKeyBlob proc :ptr, :ptr
    ImportKeyPairWithBlobType proc :ptr, :Windows::Security::Cryptography::Core::CryptographicPrivateKeyBlobType, :ptr
    ImportDefaultPublicKeyBlob proc :ptr, :ptr
    ImportPublicKeyWithBlobType proc :ptr, :Windows::Security::Cryptography::Core::CryptographicPublicKeyBlobType, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIPersistedKeyProviderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIPersistedKeyProviderStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IPersistedKeyProviderStatics <L"Windows.Security.Cryptography.Core.IPersistedKeyProviderStatics">
DEFINE_IIDX(IPersistedKeyProviderStatics, "77274814-D9D4-4CF5-B668-E0457DF30894")

.comdef IPersistedKeyProviderStatics : public IInspectable

    OpenKeyPairFromCertificateAsync proc :ptr, :HSTRING, :Windows::Security::Cryptography::Core::CryptographicPadding, :ptr
    OpenPublicKeyFromCertificate proc :ptr, :HSTRING, :Windows::Security::Cryptography::Core::CryptographicPadding, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIEncryptedAndAuthenticatedData_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIEncryptedAndAuthenticatedData_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IEncryptedAndAuthenticatedData <L"Windows.Security.Cryptography.Core.IEncryptedAndAuthenticatedData">
DEFINE_IIDX(IEncryptedAndAuthenticatedData, "6FA42FE7-1ECB-4B00-BEA5-60B83F862F17")

.comdef IEncryptedAndAuthenticatedData : public IInspectable

    get_EncryptedData	proc :ptr
    get_AuthenticationTag proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CICryptographicEngineStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CICryptographicEngineStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_ICryptographicEngineStatics <L"Windows.Security.Cryptography.Core.ICryptographicEngineStatics">
DEFINE_IIDX(ICryptographicEngineStatics, "9FEA0639-6FF7-4C85-A095-95EB31715EB9")

.comdef ICryptographicEngineStatics : public IInspectable

    Encrypt		proc :ptr, :ptr, :ptr, :ptr
    Decrypt		proc :ptr, :ptr, :ptr, :ptr
    EncryptAndAuthenticate proc :ptr, :ptr, :ptr, :ptr, :ptr
    DecryptAndAuthenticate proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    Sign		proc :ptr, :ptr, :ptr
    VerifySignature	proc :ptr, :ptr, :ptr, :ptr
    DeriveKeyMaterial	proc :ptr, :ptr, :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CICryptographicEngineStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CICryptographicEngineStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_ICryptographicEngineStatics2 <L"Windows.Security.Cryptography.Core.ICryptographicEngineStatics2">
DEFINE_IIDX(ICryptographicEngineStatics2, "675948FE-DF9F-4191-92C7-6CE6F58420E0")

.comdef ICryptographicEngineStatics2 : public IInspectable

    SignHashedData	proc :ptr, :ptr, :ptr
    VerifySignatureWithHashInput proc :ptr, :ptr, :ptr, :ptr
    DecryptAsync	proc :ptr, :ptr, :ptr, :ptr
    SignAsync		proc :ptr, :ptr, :ptr
    SignHashedDataAsync proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIHashAlgorithmProviderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIHashAlgorithmProviderStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IHashAlgorithmProviderStatics <L"Windows.Security.Cryptography.Core.IHashAlgorithmProviderStatics">
DEFINE_IIDX(IHashAlgorithmProviderStatics, "9FAC9741-5CC4-4336-AE38-6212B75A915A")

.comdef IHashAlgorithmProviderStatics : public IInspectable

    OpenAlgorithm	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIMacAlgorithmProviderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIMacAlgorithmProviderStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IMacAlgorithmProviderStatics <L"Windows.Security.Cryptography.Core.IMacAlgorithmProviderStatics">
DEFINE_IIDX(IMacAlgorithmProviderStatics, "C9BDC147-CC77-4DF0-9E4E-B921E080644C")

.comdef IMacAlgorithmProviderStatics : public IInspectable

    OpenAlgorithm	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIKeyDerivationAlgorithmProviderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIKeyDerivationAlgorithmProviderStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IKeyDerivationAlgorithmProviderStatics <L"Windows.Security.Cryptography.Core.IKeyDerivationAlgorithmProviderStatics">
DEFINE_IIDX(IKeyDerivationAlgorithmProviderStatics, "0A22097A-0A1C-443B-9418-B9498AEB1603")

.comdef IKeyDerivationAlgorithmProviderStatics : public IInspectable

    OpenAlgorithm	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CISymmetricKeyAlgorithmProviderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CISymmetricKeyAlgorithmProviderStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_ISymmetricKeyAlgorithmProviderStatics <L"Windows.Security.Cryptography.Core.ISymmetricKeyAlgorithmProviderStatics">
DEFINE_IIDX(ISymmetricKeyAlgorithmProviderStatics, "8D3B2326-1F37-491F-B60E-F5431B26B483")

.comdef ISymmetricKeyAlgorithmProviderStatics : public IInspectable

    OpenAlgorithm	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIAsymmetricKeyAlgorithmProviderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIAsymmetricKeyAlgorithmProviderStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IAsymmetricKeyAlgorithmProviderStatics <L"Windows.Security.Cryptography.Core.IAsymmetricKeyAlgorithmProviderStatics">
DEFINE_IIDX(IAsymmetricKeyAlgorithmProviderStatics, "425BDE18-A7F3-47A6-A8D2-C48D6033A65C")

.comdef IAsymmetricKeyAlgorithmProviderStatics : public IInspectable

    OpenAlgorithm	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIHashAlgorithmNamesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIHashAlgorithmNamesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IHashAlgorithmNamesStatics <L"Windows.Security.Cryptography.Core.IHashAlgorithmNamesStatics">
DEFINE_IIDX(IHashAlgorithmNamesStatics, "6B5E0516-DE96-4F0A-8D57-DCC9DAE36C76")

.comdef IHashAlgorithmNamesStatics : public IInspectable

    get_Md5		proc :ptr
    get_Sha1		proc :ptr
    get_Sha256		proc :ptr
    get_Sha384		proc :ptr
    get_Sha512		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIMacAlgorithmNamesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIMacAlgorithmNamesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IMacAlgorithmNamesStatics <L"Windows.Security.Cryptography.Core.IMacAlgorithmNamesStatics">
DEFINE_IIDX(IMacAlgorithmNamesStatics, "41412678-FB1E-43A4-895E-A9026E4390A3")

.comdef IMacAlgorithmNamesStatics : public IInspectable

    get_HmacMd5		proc :ptr
    get_HmacSha1	proc :ptr
    get_HmacSha256	proc :ptr
    get_HmacSha384	proc :ptr
    get_HmacSha512	proc :ptr
    get_AesCmac		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CISymmetricAlgorithmNamesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CISymmetricAlgorithmNamesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_ISymmetricAlgorithmNamesStatics <L"Windows.Security.Cryptography.Core.ISymmetricAlgorithmNamesStatics">
DEFINE_IIDX(ISymmetricAlgorithmNamesStatics, "6870727B-C996-4EAE-84D7-79B2AEB73B9C")

.comdef ISymmetricAlgorithmNamesStatics : public IInspectable

    get_DesCbc		proc :ptr
    get_DesEcb		proc :ptr
    get_TripleDesCbc	proc :ptr
    get_TripleDesEcb	proc :ptr
    get_Rc2Cbc		proc :ptr
    get_Rc2Ecb		proc :ptr
    get_AesCbc		proc :ptr
    get_AesEcb		proc :ptr
    get_AesGcm		proc :ptr
    get_AesCcm		proc :ptr
    get_AesCbcPkcs7	proc :ptr
    get_AesEcbPkcs7	proc :ptr
    get_DesCbcPkcs7	proc :ptr
    get_DesEcbPkcs7	proc :ptr
    get_TripleDesCbcPkcs7 proc :ptr
    get_TripleDesEcbPkcs7 proc :ptr
    get_Rc2CbcPkcs7	proc :ptr
    get_Rc2EcbPkcs7	proc :ptr
    get_Rc4		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIAsymmetricAlgorithmNamesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIAsymmetricAlgorithmNamesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IAsymmetricAlgorithmNamesStatics <L"Windows.Security.Cryptography.Core.IAsymmetricAlgorithmNamesStatics">
DEFINE_IIDX(IAsymmetricAlgorithmNamesStatics, "CAF6FCE4-67C0-46AA-84F9-752E77449F9B")

.comdef IAsymmetricAlgorithmNamesStatics : public IInspectable

    get_RsaPkcs1	proc :ptr
    get_RsaOaepSha1	proc :ptr
    get_RsaOaepSha256	proc :ptr
    get_RsaOaepSha384	proc :ptr
    get_RsaOaepSha512	proc :ptr
    get_EcdsaP256Sha256 proc :ptr
    get_EcdsaP384Sha384 proc :ptr
    get_EcdsaP521Sha512 proc :ptr
    get_DsaSha1		proc :ptr
    get_DsaSha256	proc :ptr
    get_RsaSignPkcs1Sha1 proc :ptr
    get_RsaSignPkcs1Sha256 proc :ptr
    get_RsaSignPkcs1Sha384 proc :ptr
    get_RsaSignPkcs1Sha512 proc :ptr
    get_RsaSignPssSha1	proc :ptr
    get_RsaSignPssSha256 proc :ptr
    get_RsaSignPssSha384 proc :ptr
    get_RsaSignPssSha512 proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIKeyDerivationAlgorithmNamesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CCore_CIKeyDerivationAlgorithmNamesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Cryptography_Core_IKeyDerivationAlgorithmNamesStatics <L"Windows.Security.Cryptography.Core.IKeyDerivationAlgorithmNamesStatics">
DEFINE_IIDX(IKeyDerivationAlgorithmNamesStatics, "7B6E363E-94D2-4739-A57B-022E0C3A402A")

.comdef IKeyDerivationAlgorithmNamesStatics : public IInspectable

    get_Pbkdf2Md5	proc :ptr
    get_Pbkdf2Sha1	proc :ptr
    get_Pbkdf2Sha256	proc :ptr
    get_Pbkdf2Sha384	proc :ptr
    get_Pbkdf2Sha512	proc :ptr
    get_Sp800108CtrHmacMd5 proc :ptr
    get_Sp800108CtrHmacSha1 proc :ptr
    get_Sp800108CtrHmacSha256 proc :ptr
    get_Sp800108CtrHmacSha384 proc :ptr
    get_Sp800108CtrHmacSha512 proc :ptr
    get_Sp80056aConcatMd5 proc :ptr
    get_Sp80056aConcatSha1 proc :ptr
    get_Sp80056aConcatSha256 proc :ptr
    get_Sp80056aConcatSha384 proc :ptr
    get_Sp80056aConcatSha512 proc :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Security_Cryptography_Core_KeyDerivationParameters_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Core_KeyDerivationParameters_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Core_KeyDerivationParameters <L"Windows.Security.Cryptography.Core.KeyDerivationParameters">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Core_CryptographicKey_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Core_CryptographicKey_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Core_CryptographicKey <L"Windows.Security.Cryptography.Core.CryptographicKey">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Core_CryptographicHash_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Core_CryptographicHash_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Core_CryptographicHash <L"Windows.Security.Cryptography.Core.CryptographicHash">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Core_PersistedKeyProvider_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Core_PersistedKeyProvider_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Core_PersistedKeyProvider <L"Windows.Security.Cryptography.Core.PersistedKeyProvider">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Core_EncryptedAndAuthenticatedData_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Core_EncryptedAndAuthenticatedData_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Core_EncryptedAndAuthenticatedData <L"Windows.Security.Cryptography.Core.EncryptedAndAuthenticatedData">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Core_CryptographicEngine_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Core_CryptographicEngine_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Core_CryptographicEngine <L"Windows.Security.Cryptography.Core.CryptographicEngine">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Core_HashAlgorithmProvider_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Core_HashAlgorithmProvider_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Core_HashAlgorithmProvider <L"Windows.Security.Cryptography.Core.HashAlgorithmProvider">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Core_MacAlgorithmProvider_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Core_MacAlgorithmProvider_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Core_MacAlgorithmProvider <L"Windows.Security.Cryptography.Core.MacAlgorithmProvider">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Core_KeyDerivationAlgorithmProvider_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Core_KeyDerivationAlgorithmProvider_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Core_KeyDerivationAlgorithmProvider <L"Windows.Security.Cryptography.Core.KeyDerivationAlgorithmProvider">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Core_SymmetricKeyAlgorithmProvider_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Core_SymmetricKeyAlgorithmProvider_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Core_SymmetricKeyAlgorithmProvider <L"Windows.Security.Cryptography.Core.SymmetricKeyAlgorithmProvider">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Core_AsymmetricKeyAlgorithmProvider_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Core_AsymmetricKeyAlgorithmProvider_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Core_AsymmetricKeyAlgorithmProvider <L"Windows.Security.Cryptography.Core.AsymmetricKeyAlgorithmProvider">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Core_HashAlgorithmNames_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Core_HashAlgorithmNames_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Core_HashAlgorithmNames <L"Windows.Security.Cryptography.Core.HashAlgorithmNames">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Core_MacAlgorithmNames_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Core_MacAlgorithmNames_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Core_MacAlgorithmNames <L"Windows.Security.Cryptography.Core.MacAlgorithmNames">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Core_SymmetricAlgorithmNames_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Core_SymmetricAlgorithmNames_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Core_SymmetricAlgorithmNames <L"Windows.Security.Cryptography.Core.SymmetricAlgorithmNames">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Core_AsymmetricAlgorithmNames_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Core_AsymmetricAlgorithmNames_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Core_AsymmetricAlgorithmNames <L"Windows.Security.Cryptography.Core.AsymmetricAlgorithmNames">
endif
ifndef RUNTIMECLASS_Windows_Security_Cryptography_Core_KeyDerivationAlgorithmNames_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_Core_KeyDerivationAlgorithmNames_DEFINED
define RuntimeClass_Windows_Security_Cryptography_Core_KeyDerivationAlgorithmNames <L"Windows.Security.Cryptography.Core.KeyDerivationAlgorithmNames">
endif

endif
