;
; https://github.com/microsoft/Windows-classic-samples/tree/master/Samples/XmlLiteWriter
;
include ole2.inc
include xmllite.inc
include stdio.inc
include shlwapi.inc
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

    .data
     IID_IXmlWriter IID _IID_IXmlWriter

    .code

wmain proc argc:int_t, argv:ptr ptr WCHAR

    local hr:HRESULT
    local pOutFileStream:ptr IStream
    local pWriter:ptr IXmlWriter

    mov hr,S_OK
    mov pOutFileStream,NULL
    mov pWriter,NULL

    .if ecx != 2

        wprintf(L"Usage: XmlLiteWriter.exe name-of-output-file\n")
        .return 0
    .endif

    ;; Open writeable output stream

    mov rcx,[rdx+8]
    mov hr,SHCreateStreamOnFile(rcx, STGM_CREATE or STGM_WRITE, &pOutFileStream)

    .if (FAILED(hr))

        wprintf(L"Error creating file writer, error is %08.8lx", hr)
        HR(hr)
    .endif

    mov hr,CreateXmlWriter(&IID_IXmlWriter, &pWriter, NULL)
    .if (FAILED(hr))

        wprintf(L"Error creating xml writer, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.SetOutput(pOutFileStream)
    .if (FAILED(hr))

        wprintf(L"Error, Method: SetOutput, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.SetProperty(XmlWriterProperty_Indent, TRUE)
    .if (FAILED(hr))

        wprintf(L"Error, Method: SetProperty XmlWriterProperty_Indent, error is %08.8lx", hr)
        HR(hr)
    .endif

    mov hr,pWriter.WriteStartDocument(XmlStandalone_Omit)
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteStartDocument, error is %08.8lx", hr)
        HR(hr)
    .endif

    ;; if you want to use a DTD using either the SYSTEM or PUBLIC identifiers,
    ;; or if you want to use an internal DTD subset, you can modify the following
    ;; call to WriteDocType.

    mov hr,pWriter.WriteDocType(L"root", NULL, NULL, NULL)
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteDocType, error is %08.8lx", hr)
        HR(hr)
    .endif

    mov hr,pWriter.WriteProcessingInstruction(L"xml-stylesheet",
        L"href=\"mystyle.css\" title=\"Compact\" type=\"text/css\"")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteProcessingInstruction, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteStartElement(NULL, L"root", NULL)
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteStartElement(NULL, L"sub", NULL)
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteAttributeString(NULL, L"myAttr", NULL, L"1234")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteAttributeString, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteString(L"Markup is <escaped> for this string")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteString, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteFullEndElement()
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteFullEndElement, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteStartElement(NULL, L"anotherChild", NULL)
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteString(L"some text")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteString, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteFullEndElement()
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteFullEndElement, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteWhitespace(L"\n")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr)
        HR(hr)
    .endif

    mov hr,pWriter.WriteCData(L"This is CDATA text.")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteCData, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteWhitespace(L"\n")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteStartElement(NULL, L"containsCharacterEntity", NULL)
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteCharEntity('a')
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteCharEntity, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteFullEndElement()
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteFullEndElement, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteWhitespace(L"\n")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteStartElement(NULL, L"containsChars", NULL)
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteChars(L"abcdefghijklm", 5)
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteChars, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteFullEndElement()
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteFullEndElement, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteWhitespace(L"\n")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteStartElement(NULL, L"containsEntity", NULL)
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteEntityRef(L"myEntity")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteEntityRef, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteEndElement()
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteEndElement, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteWhitespace(L"\n")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr)
        HR(hr)
    .endif

    mov hr,pWriter.WriteStartElement(NULL, L"containsName", NULL)
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteName(L"myName")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteName, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteEndElement()
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteEndElement, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteWhitespace(L"\n")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteStartElement(NULL, L"containsNmToken", NULL)
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteNmToken(L"myNmToken")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteNmToken, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteEndElement()
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteEndElement, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteWhitespace(L"\n")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteComment(L"This is a comment")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteComment, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteWhitespace(L"\n")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteRaw(L"<elementWrittenRaw/>")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteRaw, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteWhitespace(L"\n")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteRawChars(L"<rawCharacters/>", 16)
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteRawChars, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteWhitespace(L"\n")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteElementString(NULL, L"myElement", NULL, L"myValue")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteElementString, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteFullEndElement()
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteFullEndElement, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.WriteWhitespace(L"\n")
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr)
        HR(hr)
    .endif

    ;; WriteEndDocument closes any open elements or attributes
    mov hr,pWriter.WriteEndDocument()
    .if (FAILED(hr))

        wprintf(L"Error, Method: WriteEndDocument, error is %08.8lx", hr)
        HR(hr)
    .endif
    mov hr,pWriter.Flush()
    .if (FAILED(hr))

        wprintf(L"Error, Method: Flush, error is %08.8lx", hr)
        HR(hr)
    .endif

CleanUp:

    SAFE_RELEASE(pOutFileStream)
    SAFE_RELEASE(pWriter)
    .return hr

wmain endp

    end _tstart
