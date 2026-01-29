; COMPRESSAPI.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

define NTDDI_VERSION NTDDI_WIN8

include stdio.inc
include malloc.inc
include winbase.inc
include compressapi.inc
include tchar.inc

.data
CompressedData label byte
incbin <asmc64.lzms>
CompressedDataSize equ $ - CompressedData
.code

main proc

    .new DecompressorHandle:COMPRESSOR_HANDLE = NULL
    .new UncompressedDataSize:size_t = 0
    .new UncompressedBufferSize:size_t = 400000
    .new UncompressedBuffer:ptr byte = malloc(UncompressedBufferSize)
    .ifd CreateDecompressor(COMPRESS_ALGORITHM_LZMS, NULL, &DecompressorHandle)

        .ifd Decompress(DecompressorHandle, &CompressedData, CompressedDataSize,
                UncompressedBuffer, UncompressedBufferSize, &UncompressedDataSize)

           .new fp:ptr FILE = fopen("asmc64.exe", "wb")
            fwrite(UncompressedBuffer, dword ptr UncompressedDataSize, 1, fp)
            fclose(fp)
        .endif
    .endif
    .return 0

main endp

    end _tstart

