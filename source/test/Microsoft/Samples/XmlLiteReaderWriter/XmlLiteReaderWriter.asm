; XMLLITEREADERWRITER.ASM--
;
; This sample shows how to use XmlLite to read an XML document, process its nodes,
; and then output the XML to another file. The sample includes an XML file from
; which it reads.The XmlLite library allows developers to build high-performance
; XML-based applications that provide a high degree of interoperability with other
; applications that adhere to the XML 1.0 standard. The primary goals of XmlLite
; are ease of use, performance, and standards compliance. XmlLite works with any
; Windows language that can use dynamic link libraries (DLLs), but Microsoft
; recommends C++. XmlLite comes with all necessary support files for use with C++,
; but if you want to use it with other languages, some additional work may be required.
;

include ole2.inc
include xmllite.inc
include stdio.inc
include shlwapi.inc
include strsafe.inc
include tchar.inc

CHKHR macro stmt
    mov hr,(stmt)
    .if (FAILED(hr))
        jmp CleanUp
    .endif
    exitm<>
    endm

HR macro stmt
    mov hr,(stmt)
    jmp CleanUp
    exitm<>
    endm

SAFE_RELEASE macro I
    .if (I)
        I.Release()
        mov I,NULL
    .endif
    exitm<>
    endm

; implement filestream that derives from IStream

.class FileStream : public IStream

    _hFile      HANDLE ?
    _refcount   LONG ?

    FileStream  proc :HANDLE
    Close       proc
   .ends

ifdef __PE__
    .data
     IID_IUnknown   GUID _IID_IUnknown
     IID_IStream    GUID _IID_IStream
     IID_IXmlReader GUID _IID_IXmlReader
     IID_IXmlWriter GUID _IID_IXmlWriter
     IID_ISequentialStream GUID _IID_ISequentialStream
endif

    .code

    assume rcx:ptr FileStream

FileStream::FileStream proc hFile:HANDLE

    @ComAlloc(FileStream)
    mov [rax].FileStream._refcount,1
    mov rdx,hFile
    mov [rax].FileStream._hFile,rdx
    ret

FileStream::FileStream endp

FileStream::Close proc

    .if ( [rcx]._hFile != INVALID_HANDLE_VALUE )
        CloseHandle([rcx]._hFile)
    .endif
    ret

FileStream::Close endp

FileStream_OpenFile proc pName:LPCWSTR, ppStream:ptr ptr IStream, fWrite:bool

    test    r8b,r8b
    mov     edx,GENERIC_READ
    mov     eax,GENERIC_WRITE
    cmovnz  edx,eax
    mov     r9d,OPEN_EXISTING
    mov     eax,CREATE_ALWAYS
    cmovnz  r9d,eax

    .new hFile:HANDLE = CreateFileW(rcx, edx, FILE_SHARE_READ, NULL, r9d, FILE_ATTRIBUTE_NORMAL, NULL)

    .if ( hFile == INVALID_HANDLE_VALUE )

        GetLastError()
       .return HRESULT_FROM_WIN32(eax)
    .endif
    .if ( FileStream(hFile) == NULL )
        CloseHandle(hFile)
    .else
        mov rcx,ppStream
        mov [rcx],rax
    .endif
    .return S_OK

FileStream_OpenFile endp

FileStream::QueryInterface proc iid:REFIID, ppvObject:ptr ptr

    .if ( r8 == NULL )

        .return E_INVALIDARG
    .endif

    xor eax,eax
    mov [r8],rax
    mov rax,[rdx]
    mov rdx,[rdx+8]

    .if ( ( rax == qword ptr IID_IUnknown && rdx == qword ptr IID_IUnknown[8] ) ||
          ( rax == qword ptr IID_IStream && rdx == qword ptr IID_IStream[8] ) ||
          ( rax == qword ptr IID_ISequentialStream && rdx == qword ptr IID_ISequentialStream[8] ) )

        mov [r8],rcx
        this.AddRef()
        .return S_OK
    .endif
    .return E_NOINTERFACE

FileStream::QueryInterface endp

FileStream::AddRef proc

    .return InterlockedIncrement(&[rcx]._refcount)

FileStream::AddRef endp

FileStream::Release proc

    .if ( InterlockedDecrement(&[rcx]._refcount) == 0 )

        free(this)
    .endif
    ret

FileStream::Release endp

; ISequentialStream Interface

FileStream::Read proc pv:ptr, cb:ULONG, pcbRead:ptr ULONG

    .if ( ReadFile([rcx]._hFile, rdx, r8d, r9, NULL) )

        .return S_OK
    .endif
    GetLastError()
   .return HRESULT_FROM_WIN32(eax)

FileStream::Read endp

FileStream::Write proc pv:ptr, cb:ULONG, pcbWritten:ptr ULONG

    .if ( WriteFile([rcx]._hFile, rdx, r8d, r9, NULL) )

        .return S_OK
    .endif
    GetLastError()
   .return HRESULT_FROM_WIN32(eax)

FileStream::Write endp

; IStream Interface

FileStream::SetSize:        ;(ULARGE_INTEGER)
FileStream::CopyTo:         ;(IStream*, ULARGE_INTEGER, ULARGE_INTEGER*, ULARGE_INTEGER*)
FileStream::Commit:         ;(DWORD)
FileStream::Revert:         ;(void)
FileStream::LockRegion:     ;(ULARGE_INTEGER, ULARGE_INTEGER, DWORD)
FileStream::UnlockRegion:   ;(ULARGE_INTEGER, ULARGE_INTEGER, DWORD)
FileStream::Clone:          ;(IStream **)
    mov eax,E_NOTIMPL
    ret


FileStream::Seek proc liDistanceToMove:LARGE_INTEGER, dwOrigin:DWORD, lpNewFilePointer:ptr ULARGE_INTEGER

    .new dwMoveMethod:DWORD

    .switch(dwOrigin)
    .case STREAM_SEEK_SET
        mov dwMoveMethod,FILE_BEGIN
       .endc
    .case STREAM_SEEK_CUR
        mov dwMoveMethod,FILE_CURRENT
       .endc
    .case STREAM_SEEK_END
        mov dwMoveMethod,FILE_END
       .endc
    .default
        .return STG_E_INVALIDFUNCTION
    .endsw

    .if ( SetFilePointerEx([rcx]._hFile, liDistanceToMove, lpNewFilePointer, dwMoveMethod) == 0 )

        GetLastError()
       .return HRESULT_FROM_WIN32(eax)
    .endif
    .return S_OK

FileStream::Seek endp

FileStream::Stat proc pStatstg:ptr STATSTG, s:DWORD

    .if ( GetFileSizeEx([rcx]._hFile, &[rdx].STATSTG.cbSize) == 0 )

        GetLastError()
       .return HRESULT_FROM_WIN32(eax)
    .endif
    .return S_OK

FileStream::Stat endp


wmain proc argc:int_t, argv:ptr ptr WCHAR

    .new hr:HRESULT = S_OK
    .new pFileStream:ptr IStream = NULL
    .new pOutFileStream:ptr IStream = NULL
    .new pReader:ptr IXmlReader = NULL
    .new pWriter:ptr IXmlWriter = NULL
    .new pReaderInput:ptr IXmlReaderInput = NULL
    .new pWriterOutput:ptr IXmlWriterOutput = NULL

    .if ( argc != 3 )

        wprintf( L"Usage: XmlReaderWriter.exe name-of-input-file name-of-output-file\n")
       .return 0
    .endif

    ; Open read-only input stream

    mov rax,argv
    mov rcx,[rax+8]
    mov hr,FileStream::OpenFile(rcx, &pFileStream, FALSE)
    .if (FAILED(hr))

        wprintf(L"Error creating file reader, error is %08.8lx", hr)
        HR(hr)
    .endif

    ; Open writeable output stream

    mov rax,argv
    mov rcx,[rax+16]
    mov hr,FileStream::OpenFile(rcx, &pOutFileStream, TRUE)
    .if (FAILED(hr))

        wprintf(L"Error creating file writer, error is %08.8lx", hr)
        HR(hr)
    .endif

    mov hr,CreateXmlReader(&IID_IXmlReader, &pReader, NULL)
    .if (FAILED(hr))

        wprintf(L"Error creating xml reader, error is %08.8lx", hr)
        HR(hr)
    .endif

    pReader.SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit)
    mov hr,CreateXmlReaderInputWithEncodingCodePage(pFileStream, NULL, 65001, FALSE, L"c:\temp", &pReaderInput)
    .if (FAILED(hr))

        wprintf(L"Error creating xml reader with encoding code page, error is %08.8lx", hr)
        HR(hr)
    .endif

    mov hr,CreateXmlWriter(&IID_IXmlWriter, &pWriter, NULL)
    .if (FAILED(hr))

        wprintf(L"Error creating xml writer, error is %08.8lx", hr)
        HR(hr)
    .endif

    mov hr,CreateXmlWriterOutputWithEncodingCodePage(pOutFileStream, NULL, 65001, &pWriterOutput)
    .if (FAILED(hr))

        wprintf(L"Error creating xml reader with encoding code page, error is %08.8lx", hr)
        HR(hr)
    .endif

    mov hr,pReader.SetInput(pReaderInput)
    .if (FAILED(hr))

        wprintf(L"Error setting input for reader, error is %08.8lx", hr)
        HR(hr)
    .endif

    mov hr,pWriter.SetOutput(pWriterOutput)
    .if (FAILED(hr))

        wprintf(L"Error setting output for writer, error is %08.8lx", hr)
        HR(hr)
    .endif

    mov hr,pWriter.SetProperty(XmlWriterProperty_Indent, TRUE)
    .if (FAILED(hr))

        wprintf(L"Error setting indent property in writer, error is %08.8lx", hr)
        HR(hr)
    .endif

    .new nodeType:XmlNodeType
    .new pQName:ptr WCHAR
    .new pValue:ptr WCHAR
    .new originalPrice:real8 = 0.0
    .new newPrice:real8 = 0.0
    .new priceString[100]:WCHAR
    .new inPrice:bool = FALSE

    ;
    ; This quick start reads an XML of the form
    ; <books>
    ;   <book name="name of book1">
    ;    <price>price-of-book1</price>
    ;   </book>
    ;   <book name="name of book2">
    ;    <price>price-of-book2</price>
    ;   </book>
    ;  </books>
    ;
    ; and applies a 25% discount to the price of the book. It also adds originalPrice and discount
    ; as two attributes to the element price. If the price is empty or an empty element, it does
    ; not make any changes. So the transformed XML will be:
    ;
    ; <books>
    ;   <book name="name of book1">
    ;    <price originalPrice="price-of-book1" discount="25%">
    ;           discounted-price-of-book1
    ;       </price>
    ;   </book>
    ;   <book name="name of book2">
    ;    <price originalPrice="price-of-book2" discount="25%">
    ;           discounted-price-of-book2
    ;       </price>
    ;   </book>
    ;  </books>
    ;


    ; read until there are no more nodes

    .while ( 1 )

        mov hr,pReader.Read(&nodeType)
        .if ( eax != S_OK )
            .break
        .endif

        ; WriteNode will move the reader to the next node, so inside the While Read loop, it is
        ; essential that we use WriteNodeShallow, which will not move the reader.
        ; If not, a node will be skipped every time you use WriteNode in the while loop.

        .switch (nodeType)

        .case XmlNodeType_Element

            .if ( pReader.IsEmptyElement() )

                mov hr,pWriter.WriteNodeShallow(pReader, FALSE)
                .if (FAILED(hr))

                    wprintf(L"Error writing WriteNodeShallow, error is %08.8lx", hr)
                    HR(hr)
                .endif

            .else

                ; if you are not interested in the length it may be faster to use
                ; NULL for the length parameter

                mov hr,pReader.GetQualifiedName(&pQName, NULL)
                .if (FAILED(hr))

                    wprintf(L"Error reading element name, error is %08.8lx", hr)
                    HR(hr)
                .endif

                ; if the element is price, then discount price by 25%

                mov eax,1
                .if ( pQName )
                    wcscmp(pQName, L"price")
                .endif

                .if ( eax == 0 )

                    mov inPrice,TRUE
                    mov hr,pWriter.WriteNodeShallow(pReader, FALSE)
                    .if (FAILED(hr))

                        wprintf(L"Error writing WriteNodeShallow, error is %08.8lx", hr)
                        HR(hr)
                    .endif

                .else

                    mov inPrice,FALSE
                    mov hr,pWriter.WriteNodeShallow(pReader, FALSE)
                    .if (FAILED(hr))

                        wprintf(L"Error writing WriteNodeShallow, error is %08.8lx", hr)
                        HR(hr)
                    .endif
                .endif
            .endif
            .endc

        .case XmlNodeType_Text

            .if ( inPrice == TRUE )

                mov hr,pReader.GetValue(&pValue, NULL)
                .if (FAILED(hr))

                    wprintf(L"Error reading value, error is %08.8lx", hr)
                    HR(hr)
                .endif

                mov rax,pValue
                .if ( !rax || word ptr [rax] == 0 )
                    HR(E_UNEXPECTED)
                .endif

                ; apply discount to the node

                movsd originalPrice,_wtof(pValue)
                mulsd xmm0,0.75
                movsd newPrice,xmm0

                mov hr,StringCchPrintfW(&priceString, sizeof(priceString), "%f", newPrice)
                .if (FAILED(hr))

                    wprintf(L"Error using StringCchPrintfW, error is %08.8lx", hr)
                    HR(hr)
                .endif

                ; write attributes if any

                mov hr,pWriter.WriteAttributeString(NULL, L"originalPrice", NULL, pValue)
                .if (FAILED(hr))

                    wprintf(L"Error writing WriteAttributeString, error is %08.8lx", hr)
                    HR(hr)
                .endif

                mov hr,pWriter.WriteAttributeString(NULL, L"discount", NULL, L"25%")
                .if (FAILED(hr))

                    wprintf(L"Error writing WriteAttributeString, error is %08.8lx", hr)
                    HR(hr)
                .endif
                mov hr,pWriter.WriteString(&priceString)
                .if (FAILED(hr))

                    wprintf(L"Error writing WriteString, error is %08.8lx", hr)
                    HR(hr)
                .endif
                mov inPrice,FALSE

            .else

                mov hr,pWriter.WriteNodeShallow(pReader, FALSE)
                .if (FAILED(hr))

                    wprintf(L"Error writing WriteNodeShallow, error is %08.8lx", hr)
                    HR(hr)
                .endif
            .endif
            .endc

        .case XmlNodeType_EndElement

            mov hr,pReader.GetQualifiedName(&pQName, NULL)
            .if (FAILED(hr))

                wprintf(L"Error reading element name, error is %08.8lx", hr)
                HR(hr)
            .endif
            mov eax,1
            .if ( pQName )
                wcscmp(pQName, L"price")
            .endif
            .if ( eax == 0 )  ; if the end element is price, then reset inPrice
                mov inPrice,FALSE
            .endif
            mov hr,pWriter.WriteFullEndElement()
            .if (FAILED(hr))

                wprintf(L"Error writing WriteFullEndElement, error is %08.8lx", hr)
                HR(hr)
            .endif
            .endc

        .default

            mov hr,pWriter.WriteNodeShallow(pReader, FALSE)
            .if (FAILED(hr))

                wprintf(L"Error writing WriteNodeShallow, error is %08.8lx", hr)
                HR(hr)
            .endif
            .endc
        .endsw
    .endw

CleanUp:
    SAFE_RELEASE(pFileStream)
    SAFE_RELEASE(pOutFileStream)
    SAFE_RELEASE(pReader)
    SAFE_RELEASE(pWriter)
    SAFE_RELEASE(pReaderInput)
    SAFE_RELEASE(pWriterOutput)
   .return hr

wmain endp

    end _tstart
