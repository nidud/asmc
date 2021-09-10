;;
;; https://docs.microsoft.com/en-us/samples/microsoft/windows-classic-samples/audioclip/
;;
;; This console application demonstrates using the Media Foundation
;; source reader to extract decoded audio from an audio/video file.
;;
;; The application reads audio data from an input file and writes
;; uncompressed PCM audio to a WAVE file.
;;
;; The input file must be a media format supported by Media Foundation,
;; and must have         an audio stream. The audio stream can be an encoded
;; format, such as Windows Media Audio.
;;
WINVER equ _WIN32_WINNT_WIN7

include windows.inc
include mfapi.inc
include mfidl.inc
include mfreadwrite.inc
include stdio.inc
include mferror.inc
include tchar.inc

option dllimport:none


SafeRelease proto T:abs {
    .if T
        T.Release()
        mov T,NULL
    .endif
    }

WriteWaveFile               proto :ptr IMFSourceReader, :HANDLE, :LONG
ConfigureAudioStream        proto :ptr IMFSourceReader, :ptr ptr IMFMediaType
WriteWaveHeader             proto :HANDLE, :ptr IMFMediaType, :ptr DWORD
CalculateMaxAudioDataSize   proto :ptr IMFMediaType, :DWORD, :DWORD
WriteWaveData               proto :HANDLE, :ptr IMFSourceReader, :DWORD, :ptr DWORD
FixUpChunkSizes             proto :HANDLE, :DWORD, :DWORD
WriteToFile                 proto :HANDLE, :ptr, :DWORD

.data
ifdef __PE__
MF_MT_AUDIO_BLOCK_ALIGNMENT IID _MF_MT_AUDIO_BLOCK_ALIGNMENT
MF_MT_AUDIO_AVG_BYTES_PER_SECOND IID _MF_MT_AUDIO_AVG_BYTES_PER_SECOND
MFMediaType_Audio           IID _MFMediaType_Audio
MF_MT_MAJOR_TYPE            IID _MF_MT_MAJOR_TYPE
MFAudioFormat_PCM           IID _MFAudioFormat_PCM
MF_MT_SUBTYPE               IID _MF_MT_SUBTYPE
endif
.code

wmain proc argc:int_t, argv:ptr ptr wchar_t

  local hr:HRESULT
  local wszSourceFile:ptr WCHAR
  local wszTargetFile:ptr WCHAR

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

    ;; Initialize the COM library.
    mov hr,CoInitializeEx(NULL, COINIT_APARTMENTTHREADED or COINIT_DISABLE_OLE1DDE)

    ;; Intialize the Media Foundation platform.
    .if (SUCCEEDED(hr))

        mov hr,MFStartup(MF_VERSION, 0)
    .endif

    ;; Create the source reader to read the input file.
    .if (SUCCEEDED(hr))

        mov hr,MFCreateSourceReaderFromURL(
            wszSourceFile,
            NULL,
            &pReader
            )

        .if (FAILED(hr))

            _tprintf("Error opening input file: %S\n", &wszSourceFile)
        .endif
    .endif

    ;; Open the output file for writing.
    .if (SUCCEEDED(hr))

        mov hFile,CreateFile(
            wszTargetFile,
            GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            CREATE_ALWAYS,
            0,
            NULL
            )

        .if (hFile == INVALID_HANDLE_VALUE)

            mov hr,HRESULT_FROM_WIN32R(GetLastError())
            _tprintf("Cannot create output file: %S\n", &wszTargetFile)
        .endif
    .endif

    ;; Write the WAVE file.
    .if (SUCCEEDED(hr))

        mov hr,WriteWaveFile(pReader, hFile, MAX_AUDIO_DURATION_MSEC)
    .endif

    .if (FAILED(hr))

        _tprintf("Failed, hr = 0x%X\n", hr)
    .endif

    ;; Clean up.
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

wmain endp


;;-------------------------------------------------------------------
;; WriteWaveFile
;;
;; Writes a WAVE file by getting audio data from the source reader.
;;
;;-------------------------------------------------------------------

WriteWaveFile proc \
    pReader:ptr IMFSourceReader,    ;; Pointer to the source reader.
    hFile:HANDLE,                   ;; Handle to the output file.
    msecAudioData:LONG              ;; Maximum amount of audio data to write, in msec.

  .new hr:HRESULT = S_OK
  .new cbHeader:DWORD = 0           ;; Size of the WAVE file header, in bytes.
  .new cbAudioData:DWORD = 0        ;; Total bytes of PCM audio data written to the file.
  .new cbMaxAudioData:DWORD = 0
  .new pAudioType:ptr IMFMediaType = NULL   ;; Represents the PCM audio format.

    ;; Configure the source reader to get uncompressed PCM audio from the source file.

    mov hr,ConfigureAudioStream(pReader, &pAudioType)

    ;; Write the WAVE file header.
    .if (SUCCEEDED(hr))

        mov hr,WriteWaveHeader(hFile, pAudioType, &cbHeader)
    .endif

    ;; Calculate the maximum amount of audio to decode, in bytes.
    .if (SUCCEEDED(hr))

        mov cbMaxAudioData,CalculateMaxAudioDataSize(pAudioType, cbHeader, msecAudioData)

        ;; Decode audio data to the file.
        mov hr,WriteWaveData(hFile, pReader, cbMaxAudioData, &cbAudioData)
    .endif

    ;; Fix up the RIFF headers with the correct sizes.
    .if (SUCCEEDED(hr))

        mov hr,FixUpChunkSizes(hFile, cbHeader, cbAudioData)
    .endif

    SafeRelease(pAudioType)
    .return hr

WriteWaveFile endp


;;-------------------------------------------------------------------
;; CalculateMaxAudioDataSize
;;
;; Calculates how much audio to write to the WAVE file, given the
;; audio format and the maximum duration of the WAVE file.
;;-------------------------------------------------------------------

CalculateMaxAudioDataSize proc \
    pAudioType:ptr IMFMediaType,    ;; The PCM audio format.
    cbHeader:DWORD,                 ;; The size of the WAVE file header.
    msecAudioData:DWORD             ;; Maximum duration, in milliseconds.

  .new cbBlockSize:UINT32 = 0       ;; Audio frame size, in bytes.
  .new cbBytesPerSecond:UINT32 = 0  ;; Bytes per second.
  .new cbAudioClipSize:DWORD
  .new cbMaxSize:DWORD

    ;; Get the audio block size and number of bytes/second from the audio format.

    mov cbBlockSize,MFGetAttributeUINT32(pAudioType, &MF_MT_AUDIO_BLOCK_ALIGNMENT, 0)
    mov cbBytesPerSecond,MFGetAttributeUINT32(pAudioType, &MF_MT_AUDIO_AVG_BYTES_PER_SECOND, 0)

    ;; Calculate the maximum amount of audio data to write.
    ;; This value equals (duration in seconds x bytes/second), but cannot
    ;; exceed the maximum size of the data chunk in the WAVE file.

    ;; Size of the desired audio clip in bytes:
    mov cbAudioClipSize,MulDiv(cbBytesPerSecond, msecAudioData, 1000)

    ;; Largest possible size of the data chunk:
    mov cbMaxSize,MAXDWORD
    sub cbMaxSize,cbHeader

    ;; Maximum size altogether.
    .if cbAudioClipSize > cbMaxSize
        mov cbAudioClipSize,cbMaxSize
    .endif

    ;; Round to the audio block size, so that we do not write a partial audio frame.
    mov eax,cbAudioClipSize
    xor edx,edx
    div cbBlockSize
    mul cbBlockSize
    ret

CalculateMaxAudioDataSize endp


;;-------------------------------------------------------------------
;; ConfigureAudioStream
;;
;; Selects an audio stream from the source file, and configures the
;; stream to deliver decoded PCM audio.
;;-------------------------------------------------------------------

ConfigureAudioStream proc \
    pReader:ptr IMFSourceReader,    ;; Pointer to the source reader.
    ppPCMAudio:ptr ptr IMFMediaType ;; Receives the audio format.


  local hr:HRESULT

  .new pUncompressedAudioType:ptr IMFMediaType = NULL
  .new pPartialType:ptr IMFMediaType = NULL

    ;; Create a partial media type that specifies uncompressed PCM audio.

    mov hr,MFCreateMediaType(&pPartialType)

    .if (SUCCEEDED(hr))

        mov hr,pPartialType.SetGUID(&MF_MT_MAJOR_TYPE, &MFMediaType_Audio)
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pPartialType.SetGUID(&MF_MT_SUBTYPE, &MFAudioFormat_PCM)
    .endif

    ;; Set this type on the source reader. The source reader will
    ;; load the necessary decoder.
    .if (SUCCEEDED(hr))

        mov hr,pReader.SetCurrentMediaType(
            MF_SOURCE_READER_FIRST_AUDIO_STREAM,
            NULL,
            pPartialType
            )
    .endif

    ;; Get the complete uncompressed format.
    .if (SUCCEEDED(hr))

        mov hr,pReader.GetCurrentMediaType(
            MF_SOURCE_READER_FIRST_AUDIO_STREAM,
            &pUncompressedAudioType
            )
    .endif

    ;; Ensure the stream is selected.
    .if (SUCCEEDED(hr))

        mov hr,pReader.SetStreamSelection(
            MF_SOURCE_READER_FIRST_AUDIO_STREAM,
            TRUE
            )
    .endif

    ;; Return the PCM format to the caller.
    .if (SUCCEEDED(hr))

        mov rax,ppPCMAudio
        mov rcx,pUncompressedAudioType
        mov [rax],rcx
        [rcx].IMFMediaType.AddRef()
    .endif

    SafeRelease(pUncompressedAudioType)
    SafeRelease(pPartialType)
    .return hr

ConfigureAudioStream endp

;;-------------------------------------------------------------------
;; WriteWaveHeader
;;
;; Write the WAVE file header.
;;
;; Note: This function writes placeholder values for the file size
;; and data size, as these values will need to be filled in later.
;;-------------------------------------------------------------------

WriteWaveHeader proc \
    hFile:HANDLE,                ;; Output file.
    pMediaType:ptr IMFMediaType, ;; PCM audio format.
    pcbWritten:ptr DWORD         ;; Receives the size of the header.


  local hr:HRESULT
  local cbFormat:UINT32
  local pWav:ptr WAVEFORMATEX

    xor eax,eax
    mov hr,eax
    mov pWav,rax
    mov cbFormat,eax
    mov [r8],eax

    ;; Convert the PCM audio format into a WAVEFORMATEX structure.
    mov hr,MFCreateWaveFormatExFromMFMediaType(
        pMediaType,
        &pWav,
        &cbFormat,
        MFWaveFormatExConvertFlag_Normal
        )

    ;; Write the 'RIFF' header and the start of the 'fmt ' chunk.

    .if (SUCCEEDED(hr))

       .new header[5]:DWORD = {
            FCC('RIFF'), ;; RIFF header
            0,
            FCC('WAVE'),
            FCC('fmt '), ;; Start of 'fmt ' chunk
            cbFormat
            }

       .new dataHeader[2]:DWORD = {
            FCC('data'),
            0
            }

        mov hr,WriteToFile(hFile, &header, sizeof(header))

        ;; Write the WAVEFORMATEX structure.
        .if (SUCCEEDED(hr))

            mov hr,WriteToFile(hFile, pWav, cbFormat)
        .endif

        ;; Write the start of the 'data' chunk

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

WriteWaveHeader endp

;;-------------------------------------------------------------------
;; WriteWaveData
;;
;; Decodes PCM audio data from the source file and writes it to
;; the WAVE file.
;;-------------------------------------------------------------------

WriteWaveData proc \
    hFile:HANDLE,                   ;; Output file.
    pReader:ptr IMFSourceReader,    ;; Source reader.
    cbMaxAudioData:DWORD,           ;; Maximum amount of audio data (bytes).
    pcbDataWritten:ptr DWORD        ;; Receives the amount of data written.


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

    ;; Get audio samples from the source reader.
    .while (TRUE)

        ;; Read the next sample.
        mov hr,pReader.ReadSample(
            MF_SOURCE_READER_FIRST_AUDIO_STREAM,
            0,
            NULL,
            &dwFlags,
            NULL,
            &pSample
            )

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

        ;; Get a pointer to the audio data in the sample.

        mov hr,pSample.ConvertToContiguousBuffer(&pBuffer)

        .break .if (FAILED(hr))

        mov hr,pBuffer._Lock(&pAudioData, NULL, &cbBuffer)

        .break .if (FAILED(hr))

        ;; Make sure not to exceed the specified maximum size.
        mov eax,cbMaxAudioData
        sub eax,cbAudioData
        .if (eax < cbBuffer)

            mov cbBuffer,eax
        .endif

        ;; Write this data to the output file.
        mov hr,WriteToFile(hFile, pAudioData, cbBuffer)

        .break .if (FAILED(hr))

        ;; Unlock the buffer.
        mov hr,pBuffer.Unlock()
        mov pAudioData,NULL

        .break .if (FAILED(hr))

        ;; Update running total of audio data.
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

WriteWaveData endp

;;-------------------------------------------------------------------
;; FixUpChunkSizes
;;
;; Writes the file-size information into the WAVE file header.
;;
;; WAVE files use the RIFF file format. Each RIFF chunk has a data
;; size, and the RIFF header has a total file size.
;;-------------------------------------------------------------------

FixUpChunkSizes proc \
    hFile:HANDLE,           ;; Output file.
    cbHeader:DWORD,         ;; Size of the 'fmt ' chuck.
    cbAudioData:DWORD       ;; Size of the 'data' chunk.


  local hr:HRESULT
  local ll:LARGE_INTEGER

    mov hr,S_OK
    sub edx,sizeof(DWORD)
    mov ll.QuadPart,rdx

    .if !SetFilePointerEx(hFile, ll, NULL, FILE_BEGIN)

        GetLastError()
        mov hr,HRESULT_FROM_WIN32R(eax)
    .endif

    ;; Write the data size.

    .if (SUCCEEDED(hr))

        mov hr,WriteToFile(hFile, &cbAudioData, sizeof(cbAudioData))
    .endif

    .if (SUCCEEDED(hr))

        ;; Write the file size.
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

        ;; NOTE: The "size" field in the RIFF header does not include
        ;; the first 8 bytes of the file. i.e., it is the size of the
        ;; data that appears _after_ the size field.

        mov hr,WriteToFile(hFile, &cbRiffFileSize, sizeof(cbRiffFileSize))
    .endif

    .return hr

FixUpChunkSizes endp

;;-------------------------------------------------------------------
;;
;; Writes a block of data to a file
;;
;; hFile: Handle to the file.
;; p: Pointer to the buffer to write.
;; cb: Size of the buffer, in bytes.
;;
;;-------------------------------------------------------------------

WriteToFile proc hFile:HANDLE , p:ptr, cb:DWORD

  .new cbWritten:DWORD = 0
  .new hr:HRESULT = S_OK

    .ifd !WriteFile(hFile, p, cb, &cbWritten, NULL)

        GetLastError()
        mov hr,HRESULT_FROM_WIN32R(eax)
    .endif
    .return hr

WriteToFile endp

    end _tstart
