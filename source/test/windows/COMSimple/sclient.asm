
define INC_OLE2

include stdio.inc
include windows.inc
include tchar.inc
include conio.inc
include winnls.inc

.data
 CLSID_SimpleObject  GUID {0x5e9ddec7,0x5767,0x11cf,{0xbe,0xab,0x0,0xaa,0x0,0x6c,0x36,0x6}}
ifdef __PE__
 IID_IStream         GUID _IID_IStream
endif
 cbDefault = 4096 ;; default # of bytes to Read/Write

.code

Message proc szPrefix:LPTSTR, hr:HRESULT

  local szMessage:LPTSTR

    ldr edx,hr
    .if ( edx == S_OK )
        wprintf(ldr(szPrefix))
        .return
    .endif
    .if (HRESULT_FACILITY(edx) == FACILITY_WINDOWS)
        mov hr,HRESULT_CODE(edx)
    .endif
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER or \
        FORMAT_MESSAGE_FROM_SYSTEM or \
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        hr,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), ;;The user default language
        &szMessage,
        0,
        NULL)
    wprintf(L"%s: %s(%lx)\n", szPrefix, szMessage, hr)
    LocalFree(szMessage)
    ret
    endp


OutputTime proc pliStart:ptr LARGE_INTEGER, pliFinish:ptr LARGE_INTEGER

  local liFreq:LARGE_INTEGER

    QueryPerformanceFrequency(&liFreq)

    mov         rcx,pliStart
    mov         rdx,pliFinish
    cvtsi2sd    xmm1,[rdx].LARGE_INTEGER.LowPart
    cvtsi2sd    xmm0,[rcx].LARGE_INTEGER.LowPart
    subsd       xmm1,xmm0
    cvtsi2sd    xmm0,liFreq.LowPart
    divsd       xmm1,xmm0
    wprintf(L"%0.4f seconds\n", xmm1)
    ret
    endp


main proc argc:SINT, argv:array_t

  local hr:HRESULT,
        mq:MULTI_QI,
        csi:COSERVERINFO, pcsi:ptr COSERVERINFO,
        wsz[MAX_PATH]:WCHAR,
        cb:ULONG,
        liStart:LARGE_INTEGER, liFinish:LARGE_INTEGER

    mov pcsi,NULL
    mov cb,cbDefault

    ;; allow a machine-name as the command-line argument

    .if argc > 1

        mov rcx,argv
        MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, [rcx+size_t], -1, &wsz, lengthof(wsz))
        mov pcsi,memset(&csi, 0, COSERVERINFO)
        mov csi.pwszName,&wsz
    .endif

    ;; allow a byte-size to be passed on the command-line

    .if argc > 2
        mov rcx,argv
        mov cb,atol([rcx+size_t*2])
    .endif

    ;; initialize COM for free-threaded use

    mov hr,CoInitializeEx(NULL, COINIT_MULTITHREADED)
    .if (FAILED(hr))
        Message(L"Client: CoInitializeEx", hr)
        exit(hr)
    .endif

    ;; create a remote instance of the object on the argv[1] machine

    Message(L"Client: Creating Instance...", S_OK)

    mov mq.pIID,&IID_IStream
    mov mq.pItf,NULL
    mov mq.hr,S_OK
    QueryPerformanceCounter(&liStart)

    mov hr,CoCreateInstanceEx(&CLSID_SimpleObject, NULL, CLSCTX_SERVER, pcsi, 1, &mq)
    QueryPerformanceCounter(&liFinish)
    OutputTime(&liStart, &liFinish)

    .if (FAILED(hr))
        Message(L"Client: CoCreateInstanceEx", hr)
    .else
       .new pv:LPVOID
       .new pstm:LPSTREAM
        mov pstm,mq.pItf

         ;; make prefast "happy"

        .if pstm == NULL
            Message(L"Client: NULL Interface pointer", E_FAIL)
            exit(E_FAIL)
        .endif

        ;; "read" some data from the object

        Message(L"Client: Reading data...", S_OK)

        mov pv,CoTaskMemAlloc(cb)
        QueryPerformanceCounter(&liStart)
        mov hr,pstm.Read(pv, cb, NULL)
        QueryPerformanceCounter(&liFinish)
        OutputTime(&liStart, &liFinish)
        .if (FAILED(hr))
            Message(L"Client: IStream::Read", hr)
        .endif

        ;; "write" some data to the object

        Message(L"Client: Writing data...", S_OK)
        QueryPerformanceCounter(&liStart)
        mov hr,pstm.Write(pv, cb, NULL)
        QueryPerformanceCounter(&liFinish)
        OutputTime(&liStart, &liFinish)
        .if (FAILED(hr))
            Message(L"Client: IStream::Write", hr)
        .endif
        pstm.Release()
    .endif
    CoUninitialize()
    Message(L"Client: Done", S_OK)
    ret
    endp

    end _tstart
