;; https://docs.microsoft.com/en-us/samples/microsoft/windows-classic-samples/audioclip/
include windows.inc
include mfapi.inc
include mfidl.inc
include mfreadwrite.inc
include stdio.inc
include mferror.inc
include tchar.inc
option dllimport:none

ifdef _MSVCRT
.data
MF_MT_AUDIO_BLOCK_ALIGNMENT IID _MF_MT_AUDIO_BLOCK_ALIGNMENT
MF_MT_AUDIO_AVG_BYTES_PER_SECOND IID _MF_MT_AUDIO_AVG_BYTES_PER_SECOND
MFMediaType_Audio           IID _MFMediaType_Audio
MF_MT_MAJOR_TYPE            IID _MF_MT_MAJOR_TYPE
MFAudioFormat_PCM           IID _MFAudioFormat_PCM
MF_MT_SUBTYPE               IID _MF_MT_SUBTYPE
endif

.code

ConfigureAudioStream proc pReader:ptr IMFSourceReader, ppPCMAudio:ptr ptr IMFMediaType
   .new hr:HRESULT
   .new pUncompressedAudioType:ptr IMFMediaType = NULL
   .new pPartialType:ptr IMFMediaType = NULL
    mov hr,MFCreateMediaType(&pPartialType)
    .if (SUCCEEDED(hr))
        mov hr,pPartialType.SetGUID(&MF_MT_MAJOR_TYPE, &MFMediaType_Audio)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,pPartialType.SetGUID(&MF_MT_SUBTYPE, &MFAudioFormat_PCM)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,pReader.SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, NULL, pPartialType)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,pReader.GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &pUncompressedAudioType)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,pReader.SetStreamSelection(MF_SOURCE_READER_FIRST_AUDIO_STREAM, TRUE)
    .endif
    .if (SUCCEEDED(hr))
        mov rax,ppPCMAudio
        mov rcx,pUncompressedAudioType
        mov [rax],rcx
        [rcx].IMFMediaType.AddRef()
    .endif
    SafeRelease(pUncompressedAudioType)
    SafeRelease(pPartialType)
    .return hr
    endp

CalculateMaxAudioDataSize proc pAudioType:ptr IMFMediaType, cbHeader:DWORD, msecAudioData:DWORD
   .new cbBlockSize:UINT32 = 0
   .new cbBytesPerSecond:UINT32 = 0
   .new cbAudioClipSize:DWORD
   .new cbMaxSize:DWORD
    mov cbBlockSize,MFGetAttributeUINT32(pAudioType, &MF_MT_AUDIO_BLOCK_ALIGNMENT, 0)
    mov cbBytesPerSecond,MFGetAttributeUINT32(pAudioType, &MF_MT_AUDIO_AVG_BYTES_PER_SECOND, 0)
    mov cbAudioClipSize,MulDiv(cbBytesPerSecond, msecAudioData, 1000)
    mov cbMaxSize,MAXDWORD
    sub cbMaxSize,cbHeader
    .if cbAudioClipSize > cbMaxSize
        mov cbAudioClipSize,cbMaxSize
    .endif
    mov eax,cbAudioClipSize
    xor edx,edx
    div cbBlockSize
    mul cbBlockSize
    ret
    endp

WriteToFile proc hFile:HANDLE , p:ptr, cb:DWORD
    .new cbWritten:DWORD = 0
    .new hr:HRESULT = S_OK
    .ifd !WriteFile(hFile, p, cb, &cbWritten, NULL)
        GetLastError()
        mov hr,HRESULT_FROM_WIN32R(eax)
    .endif
    .return hr
    endp

FixUpChunkSizes proc hFile:HANDLE, cbHeader:DWORD, cbAudioData:DWORD
  local hr:HRESULT
  local ll:LARGE_INTEGER
    mov hr,S_OK
    sub edx,sizeof(DWORD)
    mov ll.QuadPart,rdx
    .if !SetFilePointerEx(hFile, ll, NULL, FILE_BEGIN)
        GetLastError()
        mov hr,HRESULT_FROM_WIN32R(eax)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,WriteToFile(hFile, &cbAudioData, sizeof(cbAudioData))
    .endif
    .if (SUCCEEDED(hr))
        mov ll.QuadPart,sizeof(FOURCC)
        .if !SetFilePointerEx(hFile, ll, NULL, FILE_BEGIN)
            GetLastError()
            mov hr,HRESULT_FROM_WIN32R(eax)
        .endif
    .endif
    .if (SUCCEEDED(hr))
       .new cbRiffFileSize:DWORD
        mov eax,cbHeader
        add eax,cbAudioData
        sub eax,8
        mov cbRiffFileSize,eax
        mov hr,WriteToFile(hFile, &cbRiffFileSize, sizeof(cbRiffFileSize))
    .endif
    .return hr
    endp

WriteWaveHeader proc hFile:HANDLE, pMediaType:ptr IMFMediaType, pcbWritten:ptr DWORD
  local hr:HRESULT, cbFormat:UINT32, pWav:ptr WAVEFORMATEX
    xor eax,eax
    mov hr,eax
    mov pWav,rax
    mov cbFormat,eax
    mov [r8],eax
    mov hr,MFCreateWaveFormatExFromMFMediaType(pMediaType, &pWav, &cbFormat, MFWaveFormatExConvertFlag_Normal)
    .if (SUCCEEDED(hr))
       .new header[5]:DWORD = { FCC('RIFF'), 0, FCC('WAVE'), FCC('fmt '), cbFormat }
       .new dataHeader[2]:DWORD = { FCC('data'), 0 }
        mov hr,WriteToFile(hFile, &header, sizeof(header))
        .if (SUCCEEDED(hr))
            mov hr,WriteToFile(hFile, pWav, cbFormat)
        .endif
        .if (SUCCEEDED(hr))
            mov hr,WriteToFile(hFile, &dataHeader, sizeof(dataHeader))
        .endif
        .if (SUCCEEDED(hr))
            mov eax,cbFormat
            add eax,sizeof(header) + sizeof(dataHeader)
            mov rcx,pcbWritten
            mov [rcx],eax
        .endif
    .endif
    CoTaskMemFree(pWav)
   .return hr
    endp

WriteWaveData proc hFile:HANDLE, pReader:ptr IMFSourceReader, cbMaxAudioData:DWORD, pcbDataWritten:ptr DWORD
  local hr:HRESULT
  local cbAudioData:DWORD
  local cbBuffer:DWORD
  local pAudioData:ptr BYTE
  local pSample:ptr IMFSample
  local pBuffer:ptr IMFMediaBuffer
  local dwFlags:DWORD
    xor eax,eax
    mov hr,eax
    mov cbAudioData,eax
    mov cbBuffer,eax
    mov pAudioData,rax
    mov dwFlags,eax
    mov pSample,rax
    mov pBuffer,rax
    .while (TRUE)
        mov hr,pReader.ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, NULL, &dwFlags, NULL, &pSample)
        .break .if (FAILED(hr))
        .if (dwFlags & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED)
            _tprintf("Type change - not supported by WAVE file format.\n")
            .break
        .endif
        .if (dwFlags & MF_SOURCE_READERF_ENDOFSTREAM)
            _tprintf("End of input file.\n")
            .break
        .endif
        .if (pSample == NULL)
            _tprintf("No sample\n")
            .continue
        .endif
        mov hr,pSample.ConvertToContiguousBuffer(&pBuffer)
        .break .if (FAILED(hr))
        mov hr,pBuffer._Lock(&pAudioData, NULL, &cbBuffer)
        .break .if (FAILED(hr))
        mov eax,cbMaxAudioData
        sub eax,cbAudioData
        .if (eax < cbBuffer)
            mov cbBuffer,eax
        .endif
        mov hr,WriteToFile(hFile, pAudioData, cbBuffer)
        .break .if (FAILED(hr))
        mov hr,pBuffer.Unlock()
        mov pAudioData,NULL
        .break .if (FAILED(hr))
        mov eax,cbAudioData
        add eax,cbBuffer
        mov cbAudioData,eax
        .if (eax >= cbMaxAudioData)
            .break
        .endif
        SafeRelease(pSample)
        SafeRelease(pBuffer)
    .endw
    .if (SUCCEEDED(hr))
        _tprintf("Wrote %d bytes of audio data.\n", cbAudioData)
        mov rcx,pcbDataWritten
        mov eax,cbAudioData
        mov [rcx],eax
    .endif
    .if (pAudioData)
        pBuffer.Unlock()
    .endif
    SafeRelease(pBuffer)
    SafeRelease(pSample)
   .return hr
    endp

WriteWaveFile proc pReader:ptr IMFSourceReader, hFile:HANDLE, msecAudioData:LONG
   .new hr:HRESULT = S_OK
   .new cbHeader:DWORD = 0
   .new cbAudioData:DWORD = 0
   .new cbMaxAudioData:DWORD = 0
   .new pAudioType:ptr IMFMediaType = NULL
    mov hr,ConfigureAudioStream(pReader, &pAudioType)
    .if (SUCCEEDED(hr))
        mov hr,WriteWaveHeader(hFile, pAudioType, &cbHeader)
    .endif
    .if (SUCCEEDED(hr))
        mov cbMaxAudioData,CalculateMaxAudioDataSize(pAudioType, cbHeader, msecAudioData)
        mov hr,WriteWaveData(hFile, pReader, cbMaxAudioData, &cbAudioData)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,FixUpChunkSizes(hFile, cbHeader, cbAudioData)
    .endif
    SafeRelease(pAudioType)
    .return hr
    endp

_tmain proc argc:int_t, argv:ptr ptr wchar_t

  local hr:HRESULT, wszSourceFile:ptr WCHAR, wszTargetFile:ptr WCHAR

    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0)
    .if (argc != 3)
        _tprintf("arguments: input_file output_file.wav\n")
        .return 1
    .endif
    mov rdx,argv
    mov wszSourceFile,[rdx+8]
    mov wszTargetFile,[rdx+16]
    MAX_AUDIO_DURATION_MSEC equ 5000 ;; 5 seconds
   .new pReader:ptr IMFSourceReader = NULL
   .new hFile:HANDLE = INVALID_HANDLE_VALUE
    mov hr,CoInitializeEx(NULL, COINIT_APARTMENTTHREADED or COINIT_DISABLE_OLE1DDE)
    .if (SUCCEEDED(hr))
        mov hr,MFStartup(MF_VERSION, 0)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,MFCreateSourceReaderFromURL(wszSourceFile, NULL, &pReader)
        .if (FAILED(hr))
            _tprintf("Error opening input file: %S\n", &wszSourceFile)
        .endif
    .endif
    .if (SUCCEEDED(hr))
        mov hFile,CreateFile(wszTargetFile, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, 0, NULL)
        .if (hFile == INVALID_HANDLE_VALUE)
            mov hr,HRESULT_FROM_WIN32R(GetLastError())
            _tprintf("Cannot create output file: %S\n", &wszTargetFile)
        .endif
    .endif
    .if (SUCCEEDED(hr))
        mov hr,WriteWaveFile(pReader, hFile, MAX_AUDIO_DURATION_MSEC)
    .endif
    .if (FAILED(hr))
        _tprintf("Failed, hr = 0x%X\n", hr)
    .endif
    .if (hFile != INVALID_HANDLE_VALUE)
        CloseHandle(hFile)
    .endif
    SafeRelease(pReader)
    MFShutdown()
    CoUninitialize()
    mov eax,1
    .if SUCCEEDED(hr)
        xor eax,eax
    .endif
    ret
    endp

    end _tstart
