;
; http://masm32.com/board/index.php?topic=7684.msg84163#msg84163
;
include windows.inc
include olectl.inc

    .code

WinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPSTR, nCmdShow:int_t

  local pd:PICTDESC, pBitmap:ptr IPicture, pStream:ptr IStream,
        pcbSize:LONG, hGlobal:HGLOBAL, IconAddr:LPVOID, hFile:HANDLE, bWritten:DWORD

    ;; load the test executable and the associated icon

    .if LoadLibrary("C:\\Windows\\regedit.exe")

        ;; initialize the PICTDESC structure

        mov pd.cbSizeofstruct,sizeof(PICTDESC)
        mov pd.picType,PICTYPE_ICON
        mov pd.icon.hicon,LoadIcon(rax, MAKEINTRESOURCE(100))

        ;; create the OLE image

        .ifd OleCreatePictureIndirect(&pd, &IID_IPicture, TRUE, &pBitmap) == S_OK

            ;; create the destination stream to save the icon

            CreateStreamOnHGlobal(NULL, TRUE, &pStream)

            ;; save the icon to the stream

            pBitmap.SaveAsFile(pStream, TRUE, &pcbSize)

            ;; get the address of the icon in memory

            GetHGlobalFromStream(pStream, &hGlobal)
            mov IconAddr,GlobalLock(hGlobal)

            ;; write the icon to disc

            mov hFile,CreateFile("regedit.ico", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0)
            WriteFile(hFile, IconAddr, pcbSize, &bWritten, 0)
            CloseHandle(hFile)

            ;; release the pointers

            pBitmap.Release()
            pStream.Release()

            xor eax,eax

        .endif
    .endif
    ret

WinMain endp

    end
