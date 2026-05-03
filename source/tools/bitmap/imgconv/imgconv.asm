; IMGCONV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Convert image using GDI+ based on target extension
;

include windows.inc
include gdiplus.inc
include stdio.inc
include tchar.inc

.data
 EncoderQuality GUID {0x1d5be4b5,0xfa4a,0x452d,{0x9c,0xdd,0x5d,0xb3,0x51,0x05,0xe7,0xeb}}

.code

GetEncoderClsid proc uses rsi rdi rbx format:wstring_t, pClsid:ptr CLSID

    .new num:UINT  = 0 ; number of image encoders
    .new size:UINT = 0 ; size of the image encoder array in bytes

    GdipGetImageEncodersSize(&num, &size)
    .if ( size == 0 )
        .return(-1)
    .endif

    mov rdi,malloc(size)
    .if ( rax == NULL )
        .return(-1)
    .endif

    GdipGetImageEncoders(num, size, rdi)

    .for ( esi = 0: esi < num: ++esi )

        imul ebx,esi,ImageCodecInfo
        .if ( wcscmp( [rdi+rbx].ImageCodecInfo.MimeType, format ) == 0 )

            mov rdx,pClsid
            mov oword ptr [rdx],[rdi+rbx].ImageCodecInfo.Clsid

            free(rdi)
           .return(esi)
        .endif
    .endf
    free(rdi)
   .return(-1)

GetEncoderClsid endp


wmain proc argc:int_t, argv:ptr ptr wchar_t

    .if ( argc != 3 )

        wprintf("Usage: imgconv <src_file> <target_file.ext>\n")
       .return(0)
    .endif

    mov rcx,argv
   .new src_file:ptr wchar_t = [rcx+1*size_t]
   .new dst_file:ptr wchar_t = [rcx+2*size_t]
   .new encoderClsid:CLSID
   .new format[64]:wchar_t

    wcscpy(&format, "image/")
    .if ( wcsrchr(dst_file, '.') == NULL )

        wprintf("Error: Missing target type: %s\n", dst_file)
       .return(0)
    .endif
    lea rdx,[rax+2]
    .if ( word ptr [rdx] == 'j' && dword ptr [rdx+4] == 'g' )
        wcscat(&format, "jpeg")
    .else
        wcscat(&format, rdx)
    .endif
    .new gdiplus:GdiPlus()
    .new image:Image(src_file, FALSE)
    .ifd ( GetEncoderClsid(&format, &encoderClsid) == -1 )
        wprintf("Error: Missing GDI Image Encoder\n")
    .elseif ( image.Save(dst_file, &encoderClsid, NULL) == Ok )
        wprintf("%s was saved successfully\n", dst_file)
    .else
        wprintf("Saving %s failed\n", dst_file)
    .endif
    image.Release()
    gdiplus.Release()
   .return( 0 )

wmain endp

    end _tstart
