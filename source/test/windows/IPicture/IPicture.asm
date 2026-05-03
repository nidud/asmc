include windows.inc
include olectl.inc
include tchar.inc

.data
ifdef _MSVCRT
IID_IPicture IID _IID_IPicture
endif
regedit TCHAR @CatStr(<!">, @Environ(SystemRoot),<!">),"\regedit.exe",0

.code

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE,
        lpCmdLine:LPTSTR, nCmdShow:int_t

  local pd          : PICTDESC,
        pBitmap     : ptr IPicture,
        pStream     : ptr IStream,
        pcbSize     : int_t,
        hGlobal     : HGLOBAL,
        IconAddr    : ptr_t,
        hFile       : HANDLE,
        bWritten    : uint_t,
        retval      : int_t

    mov retval,1

    ;; Extract the first icon stored in the executable file.

    .if ExtractIcon(hInstance, &regedit, 0)

        ;; initialize the PICTDESC structure

        mov pd.cbSizeofstruct,PICTDESC
        mov pd.picType,PICTYPE_ICON
        mov pd.icon.hicon,rax

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

            mov hFile,CreateFile("result.ico", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0)
            WriteFile(hFile, IconAddr, pcbSize, &bWritten, 0)
            CloseHandle(hFile)

            ;; release the pointers

            pBitmap.Release()
            pStream.Release()
            mov retval,0

        .endif
        DestroyIcon(pd.icon.hicon)
    .endif

    mov eax,retval
    ret

_tWinMain endp

    end _tstart
