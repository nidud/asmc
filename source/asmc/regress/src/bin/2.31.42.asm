
    ; @CStr( L"A\0" L"B\0" )

    .x64
    .model flat, fastcall
    .code

    lea rax,@CStr(
        L"All Image Files\0"               L"*.bmp;*.dib;*.wdp;*.mdp;*.hdp;*.gif;*.png;*.jpg;*.jpeg;*.tif;*.ico\0"
        L"Windows Bitmap\0"                L"*.bmp;*.dib\0"
        L"High Definition Photo\0"         L"*.wdp;*.mdp;*.hdp\0"
        L"Graphics Interchange Format\0"   L"*.gif\0"
        L"Portable Network Graphics\0"     L"*.png\0"
        L"JPEG File Interchange Format\0"  L"*.jpg;*.jpeg\0"
        L"Tiff File\0"                     L"*.tif\0"
        L"Icon\0"                          L"*.ico\0"
        L"All Files\0"                     L"*.*\0" )

    lea rax,@CStr(
        "All Image Files\0"               "*.bmp;*.dib;*.wdp;*.mdp;*.hdp;*.gif;*.png;*.jpg;*.jpeg;*.tif;*.ico\0"
        "Windows Bitmap\0"                "*.bmp;*.dib\0"
        "High Definition Photo\0"         "*.wdp;*.mdp;*.hdp\0"
        "Graphics Interchange Format\0"   "*.gif\0"
        "Portable Network Graphics\0"     "*.png\0"
        "JPEG File Interchange Format\0"  "*.jpg;*.jpeg\0"
        "Tiff File\0"                     "*.tif\0"
        "Icon\0"                          "*.ico\0"
        "All Files\0"                     "*.*\0" )

    lea rax,@CStr(
        L"All Image Files\0"               L"*.bmp;*.dib;*.wdp;*.mdp;*.hdp;*.gif;*.png;*.jpg;*.jpeg;*.tif;*.ico\0"
        L"Windows Bitmap\0"                L"*.bmp;*.dib\0"
        L"High Definition Photo\0"         L"*.wdp;*.mdp;*.hdp\0"
        L"Graphics Interchange Format\0"   L"*.gif\0"
        L"Portable Network Graphics\0"     L"*.png\0"
        L"JPEG File Interchange Format\0"  L"*.jpg;*.jpeg\0"
        L"Tiff File\0"                     L"*.tif\0"
        L"Icon\0"                          L"*.ico\0"
        L"All Files\0"                     L"*.*\0" )

    lea rax,@CStr(
        "All Image Files\0"               "*.bmp;*.dib;*.wdp;*.mdp;*.hdp;*.gif;*.png;*.jpg;*.jpeg;*.tif;*.ico\0"
        "Windows Bitmap\0"                "*.bmp;*.dib\0"
        "High Definition Photo\0"         "*.wdp;*.mdp;*.hdp\0"
        "Graphics Interchange Format\0"   "*.gif\0"
        "Portable Network Graphics\0"     "*.png\0"
        "JPEG File Interchange Format\0"  "*.jpg;*.jpeg\0"
        "Tiff File\0"                     "*.tif\0"
        "Icon\0"                          "*.ico\0"
        "All Files\0"                     "*.*\0" )


    end
