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
UncompressedData label byte
incbin <..\..\..\..\bin\asmc64.exe>
UncompressedDataSize equ $ - UncompressedData
.code

main proc

    .new CompressorHandle:COMPRESSOR_HANDLE = NULL
    .new CompressedDataSize:size_t = 0
    .new CompressedBufferSize:size_t = 400000
    .new CompressedBuffer:ptr byte = malloc(CompressedBufferSize)
    .ifd CreateCompressor(COMPRESS_ALGORITHM_LZMS, NULL, &CompressorHandle)

        .ifd Compress(CompressorHandle, &UncompressedData, UncompressedDataSize,
                CompressedBuffer, CompressedBufferSize, &CompressedDataSize)

           .new fp:ptr FILE = fopen("asmc64.lzms", "wb")
            fwrite(CompressedBuffer, dword ptr CompressedDataSize, 1, fp)
            fclose(fp)
        .endif
    .endif
    .return 0

main endp

    end _tstart
