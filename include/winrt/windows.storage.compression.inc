ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Estorage2Ecompression_h__
define __windows2Estorage2Ecompression_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.Streams.inc

.namespace Windows
.namespace Storage
.namespace Compression

.enum CompressAlgorithm {
    CompressAlgorithm_InvalidAlgorithm  = 0,
    CompressAlgorithm_NullAlgorithm = 1,
    CompressAlgorithm_Mszip = 2,
    CompressAlgorithm_Xpress    = 3,
    CompressAlgorithm_XpressHuff    = 4,
    CompressAlgorithm_Lzms  = 5
    }

ifndef ____x_ABI_CWindows_CStorage_CCompression_CICompressor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CCompression_CICompressor_INTERFACE_DEFINED__
DEFINE_IIDX(ICompressor, "0AC3645A-57AC-4EE1-B702-84D39D5424E0")

.comdef ICompressor : public IInspectable

    FinishAsync         proc :ptr
    DetachStream        proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CCompression_CIDecompressor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CCompression_CIDecompressor_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_Compression_IDecompressor <L"Windows.Storage.Compression.IDecompressor">
DEFINE_IIDX(IDecompressor, "B883FE46-D68A-4C8B-ADA0-4EE813FC5283")

.comdef IDecompressor : public IInspectable

    DetachStream        proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CCompression_CICompressorFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CCompression_CICompressorFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_Compression_ICompressorFactory <L"Windows.Storage.Compression.ICompressorFactory">
DEFINE_IIDX(ICompressorFactory, "5F3D96A4-2CFB-442C-A8BA-D7D11B039DA0")

.comdef ICompressorFactory : public IInspectable

    CreateCompressor    proc :ptr, :ptr
    CreateCompressorEx  proc :ptr, :Windows::Storage::Compression::CompressAlgorithm, :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CCompression_CIDecompressorFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CCompression_CIDecompressorFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_Compression_IDecompressorFactory <L"Windows.Storage.Compression.IDecompressorFactory">
DEFINE_IIDX(IDecompressorFactory, "5337E252-1DA2-42E1-8834-0379D28D742F")

.comdef IDecompressorFactory : public IInspectable

    CreateDecompressor  proc :ptr, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Storage_Compression_Compressor_DEFINED
define RUNTIMECLASS_Windows_Storage_Compression_Compressor_DEFINED
define RuntimeClass_Windows_Storage_Compression_Compressor <L"Windows.Storage.Compression.Compressor">
endif
ifndef RUNTIMECLASS_Windows_Storage_Compression_Decompressor_DEFINED
define RUNTIMECLASS_Windows_Storage_Compression_Decompressor_DEFINED
define RuntimeClass_Windows_Storage_Compression_Decompressor <L"Windows.Storage.Compression.Decompressor">
endif

endif
