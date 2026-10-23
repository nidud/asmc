define NTDDI_VERSION NTDDI_WIN8
include stdio.inc
include malloc.inc
include winbase.inc
include compressapi.inc
include tchar.inc

.code
_tmain proc
    .new hr:HRESULT = E_FAIL
    .new fp:LPFILE
    .new file:LPTSTR = "..\\..\\..\\..\\bin\\asmc64.exe"
    .new CompressorHandle:COMPRESSOR_HANDLE = NULL
    .new CompressedDataSize:size_t = 0
    .new UncompressedDataSize:size_t = 0
    .new DecompressedDataSize:size_t = 0
    .new CompressedBufferSize:size_t = 450000
    .new UncompressedBufferSize:size_t = 450000
    .new CompressedBuffer:LPBYTE = malloc(CompressedBufferSize)
    .new UncompressedData:LPBYTE = malloc(UncompressedBufferSize)
    .if _tfopen(file, "rb")
        mov fp,rax
        .for ( ebx = 0, rdi = UncompressedData : fread(rdi, 1, 1024, fp) : rdi += 1024 )
            add rbx,rax
        .endf
        mov UncompressedDataSize,rbx
        fclose(fp)
        .ifd CreateCompressor(COMPRESS_ALGORITHM_LZMS, NULL, &CompressorHandle)
            .ifd Compress(CompressorHandle, UncompressedData, UncompressedDataSize,
                    CompressedBuffer, CompressedBufferSize, &CompressedDataSize)
                _tprintf("asmc64.exe Comressed using LZMS from %d to %d byte\n", UncompressedDataSize, CompressedDataSize)
                mov hr,S_OK
            .endif
            CloseCompressor(CompressorHandle)
        .endif
        .if (SUCCEEDED(hr))
            .ifd CreateDecompressor(COMPRESS_ALGORITHM_LZMS, NULL, &CompressorHandle)
                .ifd Decompress(CompressorHandle, CompressedBuffer, CompressedDataSize,
                        UncompressedData, UncompressedBufferSize, &DecompressedDataSize)
                    _tprintf("Decomressed asmc64.exe to %d byte\n", DecompressedDataSize)
                    .if _tfopen("asmc64.exe", "wb")
                        mov fp,rax
                        fwrite(UncompressedData, dword ptr DecompressedDataSize, 1, fp)
                        fclose(fp)
                    .endif
                .endif
                CloseCompressor(CompressorHandle)
            .endif
        .endif
    .else
        _tperror(file)
    .endif
    .return 0
    endp
    end _tstart
