include windows.inc
include gdiplus.inc
include stdio.inc
include tchar.inc

ifdef __PE__
    .data
    EncoderQuality IID _EncoderQuality
    option dllimport:none
endif

    .code

GetEncoderClsid proc uses rsi rdi rbx format:wstring_t, pClsid:ptr CLSID

  local num:UINT  ; number of image encoders
  local size:UINT ; size of the image encoder array in bytes

    xor edi,edi
    mov num,edi
    mov size,edi

    GdipGetImageEncodersSize(&num, &size)
    .return -1 .if ( size == 0 )

    mov rdi,malloc(size)
    .return -1 .if ( rax == NULL ) ;; Failure

    GdipGetImageEncoders(num, size, rdi)

    .for ( esi = 0: esi < num: ++esi )

        imul ebx,esi,ImageCodecInfo

        .if ( wcscmp( [rdi+rbx].ImageCodecInfo.MimeType, format ) == 0 )

            mov rdx,pClsid
            mov oword ptr [rdx],[rdi+rbx].ImageCodecInfo.Clsid

            free(rdi)
            .return esi ;; Success
        .endif
    .endf

   free(rdi)
  .return -1 ;; Failure

GetEncoderClsid endp

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

    local encoderClsid:CLSID

    ;; Initialize GDI+.

    .new gdiplus:GdiPlus()

    ;; Get an image from the disk.

    .new image:Image(L"..\\res\\image.png", FALSE)

    ;; Get the CLSID of the PNG encoder.

    GetEncoderClsid(L"image/bmp", &encoderClsid)

    .if image.Save(L"image.bmp", &encoderClsid, NULL) == Ok
        MessageBox(0, "image.bmp was saved successfully", "BitmapSave", 0)
    .else
        MessageBox(0, "Saving image.bmp failed", "BitmapSave", 0)
    .endif
    image.Release()
    gdiplus.Release()
   .return( 0 )

_tWinMain endp

    end _tstart
