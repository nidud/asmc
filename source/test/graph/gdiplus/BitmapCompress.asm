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
    local encoderParameters:EncoderParameters
    local quality:ULONG

    ;; Initialize GDI+.

    .new gdiplus:GdiPlus()

    ;; Get an image from the disk.

    .new image:Image("..\\res\\image.png", FALSE)

    ;; Get the CLSID of the PNG encoder.

    GetEncoderClsid(L"image/bmp", &encoderClsid)

    .new result:ULONG = 0
    .if image.Save(L"Shapes000.bmp", &encoderClsid, NULL) == Ok

        inc result
        image.Release()

        .new image:Image("Shapes000.bmp", FALSE)

        ;; Get the CLSID of the JPEG encoder.

        GetEncoderClsid("image/jpeg", &encoderClsid)

        ;; Before we call Image::Save, we must initialize an
        ;; EncoderParameters object. The EncoderParameters object
        ;; has an array of EncoderParameter objects. In this
        ;; case, there is only one EncoderParameter object in the array.
        ;; The one EncoderParameter object has an array of values.
        ;; In this case, there is only one value (of type ULONG)
        ;; in the array. We will let this value vary from 0 to 100.

        mov encoderParameters.Count,1
        mov encoderParameters.Parameter.Guid,EncoderQuality
        mov encoderParameters.Parameter.Type,EncoderParameterValueTypeLong
        mov encoderParameters.Parameter.NumberOfValues,1
        mov encoderParameters.Parameter.Value,&quality

        ;; Save the image as a JPEG with quality level 0.

        mov quality,0
        .if image.Save("Shapes001.jpg", &encoderClsid, &encoderParameters) == Ok

            inc result

            ;; Save the image as a JPEG with quality level 50.

            mov quality,50
            .if image.Save("Shapes050.jpg", &encoderClsid, &encoderParameters) == Ok

                inc result

                ;; Save the image as a JPEG with quality level 100.

                mov quality,100

                .if image.Save("Shapes100.jpg", &encoderClsid, &encoderParameters) == Ok

                    inc result
                .endif
            .endif
        .endif
        image.Release()
    .endif
    gdiplus.Release()

    .if result == 4
        MessageBox(0, "Files ShapesXXX.jpg was saved successfully as a JPEG", "BitmapCompress", 0)
    .else
        MessageBox(0, "Saving files ShapesXXX.jpg failed", "BitmapCompress", 0)
    .endif
    .return( 0 )

_tWinMain endp

    end _tstart
