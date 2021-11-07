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

ifndef __windows2Esecurity2Ecryptography_h__
define __windows2Esecurity2Ecryptography_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
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
