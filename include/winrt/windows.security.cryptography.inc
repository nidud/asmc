ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Esecurity2Ecryptography_h__
define __windows2Esecurity2Ecryptography_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.Streams.inc

.namespace Windows
.namespace Security
.namespace Cryptography

.enum BinaryStringEncoding {
    BinaryStringEncoding_Utf8   = 0,
    BinaryStringEncoding_Utf16LE    = 1,
    BinaryStringEncoding_Utf16BE    = 2
    }

ifndef ____x_ABI_CWindows_CSecurity_CCryptography_CICryptographicBufferStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCryptography_CICryptographicBufferStatics_INTERFACE_DEFINED__
DEFINE_IIDX(ICryptographicBufferStatics, "320B7E22-3CB0-4CDF-8663-1D28910065EB")

.comdef ICryptographicBufferStatics : public IInspectable

    Compare             proc :ptr, :ptr, :ptr
    GenerateRandom      proc :UINT32, :ptr
    GenerateRandomNumber proc :ptr
    CreateFromByteArray proc :UINT32
    CopyToByteArray     proc :ptr, :ptr, :ptr
    DecodeFromHexString proc :HSTRING, :ptr
    EncodeToHexString   proc :ptr, :ptr
    DecodeFromBase64String proc :HSTRING, :ptr
    EncodeToBase64String proc :ptr, :ptr
    ConvertStringToBinary proc :HSTRING, :Windows::Security::Cryptography::BinaryStringEncoding, :ptr
    ConvertBinaryToString proc :Windows::Security::Cryptography::BinaryStringEncoding, :ptr, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Security_Cryptography_CryptographicBuffer_DEFINED
define RUNTIMECLASS_Windows_Security_Cryptography_CryptographicBuffer_DEFINED
define RuntimeClass_Windows_Security_Cryptography_CryptographicBuffer <L"Windows.Security.Cryptography.CryptographicBuffer">
endif


endif
