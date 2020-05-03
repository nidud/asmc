
; https://docs.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-setting-jpeg-compression-level-use

include windows.inc
include gdiplus.inc
include stdio.inc
include tchar.inc

ifdef __PE__
    .data
    EncoderQuality IID _EncoderQuality
    option dllimport:none
endif

GetEncoderClsid proto :wstring_t, :ptr CLSID ;; helper function

    .code

wmain proc argc:int_t, argv:wstring_t

    ;; Initialize GDI+.

    local encoderClsid:CLSID
    local gdiplusToken:ULONG_PTR
    local encoderParameters:EncoderParameters
    local quality:ULONG

    .new gdiplusStartupInput:GdiplusStartupInput()
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL)

    ;; Get an image from the disk.
    .new image:ptr Image()
    image.FromFile("..\\image.bmp", FALSE)

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
        wprintf("%s saved successfully.\n", "Shapes001.jpg")
    .else
        wprintf("%d  Attempt to save %s failed.\n", eax, "Shapes001.jpg")
    .endif

    ;; Save the image as a JPEG with quality level 50.
    mov quality,50
    .if image.Save("Shapes050.jpg", &encoderClsid, &encoderParameters) == Ok
        wprintf("%s saved successfully.\n", "Shapes050.jpg")
    .else
        wprintf("%d  Attempt to save %s failed.\n", eax, "Shapes050.jpg")
    .endif

    ;; Save the image as a JPEG with quality level 100.
    mov quality,100
    .if image.Save("Shapes100.jpg", &encoderClsid, &encoderParameters) == Ok
        wprintf("%s saved successfully.\n", "Shapes100.jpg")
    .else
        wprintf("%d  Attempt to save %s failed.\n", eax, "Shapes100.jpg")
    .endif

    image.Release()
    GdiplusShutdown(gdiplusToken)
    .return 0

wmain endp

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

    end _tstart
