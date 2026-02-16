;
; https://devblogs.microsoft.com/oldnewthing/20230208-00/?p=107807
;
; This will return 'C:\Program Files' for 32-bit and 64-bit
;
include windows.inc
include shlobj.inc
include stdio.inc
include tchar.inc

ifdef _WIN64
define BITS <"64">
else
define BITS <"32">
endif

ifdef _MSVCRT
.data
 CLSID_ShellLink        GUID _CLSID_ShellLink
 IID_IShellLink         GUID _IID_IShellLinkW
 IID_IPersistFile       GUID _IID_IPersistFile
 IID_IShellLinkDataList GUID _IID_IShellLinkDataList
 IID_IPersistStream     GUID _IID_IPersistStream
endif

.code

wmain proc argc:int_t, argv:ptr wchar_t

    .new hr:HRESULT = CoInitialize(NULL)

    .if (SUCCEEDED(hr))

       .new pShellLink:ptr IShellLinkW = NULL
        mov hr,CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, &IID_IShellLink, &pShellLink )
    .endif
    .if (SUCCEEDED(hr))
       .new pPersistFile:ptr IPersistFile = NULL
        mov hr,pShellLink.QueryInterface(&IID_IPersistFile, &pPersistFile)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,E_INVALIDARG
        .if ( argc == 2 )
            mov rax,argv
            mov hr,pPersistFile.Load([rax+size_t], STGM_READ)
        .endif
    .endif
    .if (SUCCEEDED(hr))
       .new pShellLinkDataList:ptr IShellLinkDataList = NULL
        mov hr,pShellLink.QueryInterface(&IID_IShellLinkDataList, &pShellLinkDataList)
    .endif

    .new flags:DWORD = 0
    .if (SUCCEEDED(hr))
        mov hr,pShellLinkDataList.GetFlags(&flags)
    .endif
    .if (SUCCEEDED(hr))
        or flags,SLDF_DISABLE_KNOWNFOLDER_RELATIVE_TRACKING
        pShellLinkDataList.SetFlags(flags)
    .endif
    .if (SUCCEEDED(hr))
       .new stm:ptr IStream
        mov hr,CreateStreamOnHGlobal(NULL, TRUE, &stm)
    .endif
    .if (SUCCEEDED(hr))
       .new pPersistStream:ptr IPersistStream = NULL
        mov hr,pShellLink.QueryInterface(&IID_IPersistStream, &pPersistStream)
    .endif
    .if (SUCCEEDED(hr))
        mov hr,pPersistStream.Save(stm, true)
    .endif
    .if (SUCCEEDED(hr))
        stm.Seek(0, 0, NULL)
    .endif
    .if (SUCCEEDED(hr))
        pPersistStream.Load(stm)
    .endif

    .if (SUCCEEDED(hr))

        .new buffer[MAX_PATH]:wchar_t
        .new wfd:WIN32_FIND_DATA

        mov hr,pShellLink.GetPath(&buffer, MAX_PATH, &wfd, 0)
        .if (SUCCEEDED(hr))
            wprintf("TEST2" BITS ": Path is %s\n", &buffer)
        .endif

    .else

       .new szMessage:ptr wchar_t
        mov edx,hr
        .if (HRESULT_FACILITY(edx) == FACILITY_WINDOWS)
            mov hr,HRESULT_CODE(edx)
        .endif
        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER or \
            FORMAT_MESSAGE_FROM_SYSTEM or \
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            hr,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            &szMessage,
            0,
            NULL)

        wprintf("Error code: %08X\n\n%s", hr, szMessage)
        LocalFree(szMessage)
    .endif
    .return( 0 )
    endp

    end _tstart
