include windef.inc

.pragma comment(lib, cabinet)

if (NTDDI_VERSION GE NTDDI_WIN8)

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP OR WINAPI_PARTITION_SYSTEM)

COMPRESSOR_HANDLE	typedef HANDLE
PCOMPRESSOR_HANDLE	typedef ptr COMPRESSOR_HANDLE

DECOMPRESSOR_HANDLE	typedef COMPRESSOR_HANDLE
PDECOMPRESSOR_HANDLE	typedef ptr COMPRESSOR_HANDLE

define COMPRESS_ALGORITHM_INVALID      0
define COMPRESS_ALGORITHM_NULL	       1
define COMPRESS_ALGORITHM_MSZIP	       2
define COMPRESS_ALGORITHM_XPRESS       3
define COMPRESS_ALGORITHM_XPRESS_HUFF  4
define COMPRESS_ALGORITHM_LZMS	       5
define COMPRESS_ALGORITHM_MAX	       6

define COMPRESS_RAW (1 SHL 29)

CALLBACKC(PFN_COMPRESS_ALLOCATE, :ptr, :SIZE_T)
CALLBACKC(PFN_COMPRESS_FREE, :ptr, :ptr)

COMPRESS_ALLOCATION_ROUTINES  STRUC
Allocate		PFN_COMPRESS_ALLOCATE ?
Free			PFN_COMPRESS_FREE ?
UserContext		PVOID ?
COMPRESS_ALLOCATION_ROUTINES ENDS
PCOMPRESS_ALLOCATION_ROUTINES typedef ptr COMPRESS_ALLOCATION_ROUTINES

.enum COMPRESS_INFORMATION_CLASS {
    COMPRESS_INFORMATION_CLASS_INVALID,
    COMPRESS_INFORMATION_CLASS_BLOCK_SIZE,
    COMPRESS_INFORMATION_CLASS_LEVEL
    }

;BOOL
CreateCompressor proto WINAPI \
	     Algorithm: DWORD,
    AllocationRoutines: PCOMPRESS_ALLOCATION_ROUTINES,
      CompressorHandle: PCOMPRESSOR_HANDLE


SetCompressorInformation proto WINAPI \
      CompressorHandle: COMPRESSOR_HANDLE,
CompressInformationClass: COMPRESS_INFORMATION_CLASS,
   CompressInformation: LPCVOID,
CompressInformationSize: SIZE_T


QueryCompressorInformation proto WINAPI \
      CompressorHandle: COMPRESSOR_HANDLE,
CompressInformationClass: COMPRESS_INFORMATION_CLASS,
   CompressInformation: PVOID,
CompressInformationSize: SIZE_T


Compress proto WINAPI \
      CompressorHandle: COMPRESSOR_HANDLE,
      UncompressedData: LPCVOID,
  UncompressedDataSize: SIZE_T,
      CompressedBuffer: PVOID,
  CompressedBufferSize: SIZE_T,
    CompressedDataSize: PSIZE_T


ResetCompressor proto WINAPI \
      CompressorHandle: COMPRESSOR_HANDLE

CloseCompressor proto WINAPI \
      CompressorHandle: COMPRESSOR_HANDLE

CreateDecompressor proto WINAPI \
	     Algorithm: DWORD,
    AllocationRoutines: PCOMPRESS_ALLOCATION_ROUTINES,
    DecompressorHandle: PDECOMPRESSOR_HANDLE

SetDecompressorInformation proto WINAPI \
    DecompressorHandle: DECOMPRESSOR_HANDLE,
CompressInformationClass: COMPRESS_INFORMATION_CLASS,
   CompressInformation: LPCVOID,
CompressInformationSize: SIZE_T


QueryDecompressorInformation proto WINAPI \
    DecompressorHandle: DECOMPRESSOR_HANDLE,
CompressInformationClass: COMPRESS_INFORMATION_CLASS,
   CompressInformation: PVOID,
CompressInformationSize: SIZE_T


Decompress proto WINAPI \
    DecompressorHandle: DECOMPRESSOR_HANDLE,
	CompressedData: LPCVOID,
    CompressedDataSize: SIZE_T,
    UncompressedBuffer: PVOID,
UncompressedBufferSize: SIZE_T,
  UncompressedDataSize: PSIZE_T


ResetDecompressor proto WINAPI \
    DecompressorHandle: DECOMPRESSOR_HANDLE

CloseDecompressor proto WINAPI \
    DecompressorHandle: DECOMPRESSOR_HANDLE


endif

endif
