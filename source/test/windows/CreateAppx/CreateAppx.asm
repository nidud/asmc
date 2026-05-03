;
; This is a simple application which uses the Appx packaging APIs to produce
; an Appx package from a list of files on disk.
;
; For the sake of simplicity, the list of files to be packaged is hard coded
; in this sample.  A fully functional application might read its list of
; files from user input, or even generate content dynamically.
;
ifdef _LIBCMT
.pragma comment(linker,"/defaultlib:libcmtd")
.pragma comment(linker,"/defaultlib:legacy_stdio_definitions")
.pragma comment(linker,"/defaultlib:urlmon")
.pragma comment(linker,"/defaultlib:shlwapi")
endif

include stdio.inc
include windows.inc
include strsafe.inc
include shlwapi.inc
include tchar.inc

include AppxPackaging.inc  ; For Appx Packaging APIs
include CreateAppx.inc

.data
 IID_IAppxFactory  IID {0xbeb94909,0xe451,0x438b,{0xb5,0xa7,0xd7,0x9e,0x76,0x7b,0x75,0xd8}}
 CLSID_AppxFactory IID {0x5842a140,0xff9f,0x4166,{0x8f,0x5c,0x62,0xf5,0xb7,0xb0,0xc7,0x81}}

; Path where all input files are stored
define DataPath <"Data\\">

; The produced Appx package's content consists of these files, with
; corresponding content types and compression options.

define PayloadFilesCount 4

PayloadFilesName LPCWSTR \
    T("AppTile.png"),
    T("Default.html"),
    T("images\\smiley.jpg"),
    T("Error.html")

PayloadFilesContentType LPCWSTR \
    T("image/png"),
    T("text/html"),
    T("image/jpeg"),
    T("text/html")

PayloadFilesCompression APPX_COMPRESSION_OPTION \
    APPX_COMPRESSION_OPTION_NONE,
    APPX_COMPRESSION_OPTION_NORMAL,
    APPX_COMPRESSION_OPTION_NONE,
    APPX_COMPRESSION_OPTION_NORMAL

; The Appx package's manifest is read from this file
define ManifestFileName <"AppxManifest.xml">

; The hash algorithm to be used for the package's block map is SHA2-256
define Sha256AlgorithmUri <"http://www.w3.org/2001/04/xmlenc#sha256">

; The produced package will be stored under this file name
define OutputPackagePath <"HelloWorld.appx">

.code
;
; Function to create a readable IStream over the file whose name is the
; concatenation of the path and fileName parameters.  For simplicity, file
; names including path are assumed to be 100 characters or less.  A real
; application should be able to handle longer names and allocate the
; necessary buffer dynamically.
;
; Parameters:
; path - Path of the folder containing the file to be opened, ending with a
;        slash ('\') character
; fileName - Name, not including path, of the file to be opened
; stream - Output parameter pointing to the created instance of IStream over
;          the specified file when this function succeeds.
;
define MaxFileNameLength 100

GetFileStream proc path:LPCWSTR, fileName:LPCWSTR, stream:ptr ptr IStream

    .new hr:HRESULT = S_OK
    .new fullFileName[MaxFileNameLength + 1]:WCHAR

    ; Create full file name by concatenating path and fileName
    mov hr,StringCchCopyW(&fullFileName, MaxFileNameLength, path)
    .if (SUCCEEDED(hr))

        mov hr,StringCchCat(&fullFileName, MaxFileNameLength, fileName)
    .endif

    ; Create stream for reading the file

    .if (SUCCEEDED(hr))

        mov hr,SHCreateStreamOnFileEx(
                &fullFileName,
                STGM_READ or STGM_SHARE_EXCLUSIVE,
                0, ; default file attributes
                FALSE, ; do not create new file
                NULL, ; no template
                stream)
    .endif
    .return hr

GetFileStream endp

;
; Function to create an Appx package writer with default settings, given the
; output file name.
;
; Parameters:
; outputFileName - Name including path to the Appx package (.appx file) to be
;                  created.
; writer - Output parameter pointing to the created instance of
;          IAppxPackageWriter when this function succeeds.
;

GetPackageWriter proc outputFileName:LPCWSTR, writer:ptr ptr IAppxPackageWriter

    .new hr:HRESULT = S_OK
    .new outputStream:ptr IStream = NULL
    .new hashMethod:ptr IUri = NULL
    .new packageSettings:APPX_PACKAGE_SETTINGS = {0}
    .new appxFactory:ptr IAppxFactory = NULL

    ; Create a stream over the output file where the package will be written

    mov hr,SHCreateStreamOnFileEx(
            outputFileName,
            STGM_CREATE or STGM_WRITE or STGM_SHARE_EXCLUSIVE,
            0, ; default file attributes
            TRUE, ; create file if it does not exist
            NULL, ; no template
            &outputStream)

    ; Create default package writer settings, including hash algorithm URI
    ; and Zip format.

    .if (SUCCEEDED(hr))

        mov hr,CreateUri(
                Sha256AlgorithmUri,
                Uri_CREATE_CANONICALIZE,
                0, ; reserved parameter
                &hashMethod)
    .endif

    .if (SUCCEEDED(hr))

        mov packageSettings.forceZip32,TRUE
        mov packageSettings.hashMethod,hashMethod
    .endif

    ; Create a new Appx factory
    .if (SUCCEEDED(hr))

        mov hr,CoCreateInstance(
                &CLSID_AppxFactory,
                NULL,
                CLSCTX_INPROC_SERVER,
                &IID_IAppxFactory,
                &appxFactory)
    .endif

    ; Create a new package writer using the factory
    .if (SUCCEEDED(hr))

        mov hr,appxFactory.CreatePackageWriter(
                outputStream,
                &packageSettings,
                writer)
    .endif

    ; Clean up allocated resources
    .if (appxFactory != NULL)

        appxFactory.Release()
        mov appxFactory,NULL
    .endif
    .if (hashMethod != NULL)

        hashMethod.Release()
        mov hashMethod,NULL
    .endif
    .if (outputStream != NULL)

        outputStream.Release()
        mov outputStream,NULL
    .endif
    .return hr

GetPackageWriter endp

;
; Main entry point of the sample
;
wmain proc uses rsi rdi rbx

    wprintf("Copyright (c) Microsoft Corporation.  All rights reserved.\n")
    wprintf("CreateAppx sample\n\n")

    .new hr:HRESULT = CoInitializeEx(NULL, COINIT_MULTITHREADED)

    .if (SUCCEEDED(hr))

        ; Create a package writer
        .new packageWriter:ptr IAppxPackageWriter = NULL
        .new manifestStream:ptr IStream = NULL

        wprintf("\nCreating package writer\n\n")

        mov hr,GetPackageWriter(OutputPackagePath, &packageWriter)

        ; Add all payload files to the package writer

        .for (ebx = 0: SUCCEEDED(hr) && (ebx < PayloadFilesCount): ebx++)

            .new fileStream:ptr IStream = NULL

            lea rdi,PayloadFilesName
            wprintf("Adding file: %s\n", LPCWSTR ptr [rdi+rbx*LPCWSTR])

            mov hr,GetFileStream(DataPath, [rdi+rbx*LPCWSTR], &fileStream)

            .if (SUCCEEDED(hr))

                lea rcx,PayloadFilesContentType
                lea rdx,PayloadFilesCompression
                packageWriter.AddPayloadFile(
                    [rdi+rbx*LPCWSTR],
                    [rcx+rbx*LPCWSTR],
                    [rdx+rbx*APPX_COMPRESSION_OPTION],
                    fileStream)
            .endif

            .if (fileStream != NULL)

                fileStream.Release()
                mov fileStream,NULL
            .endif
        .endf

        ; Add manifest to package and close package writer
        .if (SUCCEEDED(hr))

            wprintf("\nClosing package writer and adding AppxManifest.xml as the package manifest\n")
            mov hr,GetFileStream(DataPath, ManifestFileName, &manifestStream)
        .endif
        .if (SUCCEEDED(hr))

            mov hr,packageWriter.Close(manifestStream)
        .endif

        ; Clean up allocated resources
        .if (manifestStream != NULL)

            manifestStream.Release()
            mov manifestStream,NULL
        .endif
        .if (packageWriter != NULL)

            packageWriter.Release()
            mov packageWriter,NULL
        .endif
        CoUninitialize()
    .endif

    .if (SUCCEEDED(hr))
        wprintf("\nPackage successfully saved to %s.\n", OutputPackagePath)
    .else
        wprintf("\nPackage creation failed with HRESULT 0x%08X.\n", hr)
    .endif
    .if SUCCEEDED(hr)
        .return 0
    .endif
    .return 1

wmain endp

    end _tstart
