
; https://docs.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-converting-a-bmp-image-to-a-png-image-use

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

main proc argc:int_t, argv:wstring_t

    ;; Initialize GDI+.
    local encoderClsid:CLSID
    local gdiplusToken:ULONG_PTR

    .new gdiplusStartupInput:GdiplusStartupInput()
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL)

    ;; Get an image from the disk.
    .new image:ptr Image()
    image.FromFile(L"image.bmp", FALSE)

    ;; Get the CLSID of the PNG encoder.
    GetEncoderClsid(L"image/png", &encoderClsid)

    .if image.Save(L"image.png", &encoderClsid, NULL) == Ok
        printf("image.png was saved successfully\n")
    .else
        printf("Failure: stat = %d\n", eax)
    .endif
    image.Release()

    GdiplusShutdown(gdiplusToken)
    xor eax,eax
    ret

main endp

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
