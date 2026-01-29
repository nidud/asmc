;;
;; The file defines the wallpaper helper functions.
;;
;;    BOOL SupportJpgAsWallpaper();
;;    BOOL SupportFitFillWallpaperStyles();
;;    HRESULT SetDesktopWallpaper(PWSTR pszFile, WallpaperStyle style);
;;
;; SetDesktopWallpaper is the key function that sets the desktop wallpaper. The
;; function body is composed of configuring the wallpaper style in the registry
;; and setting the wallpaper with SystemParametersInfo.
;;

include stdio.inc
include windows.inc
include winreg.inc
include Wallpaper.inc

.code

;;
;;   FUNCTION: SupportJpgAsWallpaper()
;;
;;   PURPOSE: Determine if .jpg files are supported as wallpaper in the
;;   current operating system. The .jpg wallpapers are not supported before
;;   Windows Vista.
;;
SupportJpgAsWallpaper proc

   .new osVersionInfoToCompare:OSVERSIONINFOEX = { sizeof(OSVERSIONINFOEX) }
    mov osVersionInfoToCompare.dwMajorVersion,6
    mov osVersionInfoToCompare.dwMinorVersion,0

    .new comparisonInfo:ULONGLONG = 0
    .new conditionMask:BYTE = VER_GREATER_EQUAL

    VER_SET_CONDITION(comparisonInfo, VER_MAJORVERSION, conditionMask)
    VER_SET_CONDITION(comparisonInfo, VER_MINORVERSION, conditionMask)

    .return VerifyVersionInfo(&osVersionInfoToCompare,
        VER_MAJORVERSION or VER_MINORVERSION, comparisonInfo)

SupportJpgAsWallpaper endp


;;
;;   FUNCTION: SupportFitFillWallpaperStyles()
;;
;;   PURPOSE: Determine if the fit and fill wallpaper styles are supported in
;;   the current operating system. The styles are not supported before
;;   Windows 7.
;;

SupportFitFillWallpaperStyles proc

   .new osVersionInfoToCompare:OSVERSIONINFOEX = { sizeof(OSVERSIONINFOEX) }
    mov osVersionInfoToCompare.dwMajorVersion,6
    mov osVersionInfoToCompare.dwMinorVersion,1

   .new comparisonInfo:ULONGLONG = 0
   .new conditionMask:BYTE = VER_GREATER_EQUAL

    VER_SET_CONDITION(comparisonInfo, VER_MAJORVERSION, conditionMask)
    VER_SET_CONDITION(comparisonInfo, VER_MINORVERSION, conditionMask)

   .return VerifyVersionInfo(&osVersionInfoToCompare,
        VER_MAJORVERSION or VER_MINORVERSION, comparisonInfo)

SupportFitFillWallpaperStyles endp


;;
;;   FUNCTION: SetDesktopWallpaper(PCWSTR, WallpaperStyle)
;;
;;   PURPOSE: Set the desktop wallpaper.
;;
;;   PARAMETERS:
;;   * pszFile - Path of the wallpaper
;;   * style - Wallpaper style
;;

SetDesktopWallpaper proc pszFile:PWSTR, style:WallpaperStyle

    .new hr:HRESULT = S_OK

    ;; Set the wallpaper style and tile.
    ;; Two registry values are set in the Control Panel\Desktop key.
    ;; TileWallpaper
    ;;  0: The wallpaper picture should not be tiled
    ;;  1: The wallpaper picture should be tiled
    ;; WallpaperStyle
    ;;  0:  The image is centered if TileWallpaper=0 or tiled if TileWallpaper=1
    ;;  2:  The image is stretched to fill the screen
    ;;  6:  The image is resized to fit the screen while maintaining the aspect
    ;;      ratio. (Windows 7 and later)
    ;;  10: The image is resized and cropped to fill the screen while
    ;;      maintaining the aspect ratio. (Windows 7 and later)

    ;; Open the HKCU\Control Panel\Desktop registry key.

    .new hKey:HKEY = NULL

    RegOpenKeyEx(HKEY_CURRENT_USER,
        L"Control Panel\\Desktop", 0, KEY_READ or KEY_WRITE, &hKey)

    mov hr,HRESULT_FROM_WIN32(eax)

    .if (SUCCEEDED(hr))

        .new pszWallpaperStyle:PWSTR
        .new pszTileWallpaper:PWSTR

        .switch (style)

        .case Tile
            mov pszWallpaperStyle,&@CStr(L"0")
            mov pszTileWallpaper,&@CStr(L"1")
            .endc

        .case Center
            mov pszWallpaperStyle,&@CStr(L"0")
            mov pszTileWallpaper,&@CStr(L"0")
            .endc

        .case Stretch
            mov pszWallpaperStyle,&@CStr(L"2")
            mov pszTileWallpaper,&@CStr(L"0")
            .endc

        .case Fit ;; (Windows 7 and later)
            mov pszWallpaperStyle,&@CStr(L"6")
            mov pszTileWallpaper,&@CStr(L"0")
            .endc

        .case Fill ;; (Windows 7 and later)
            mov pszWallpaperStyle,&@CStr(L"10")
            mov pszTileWallpaper,&@CStr(L"0")
            .endc
        .endsw

        ;; Set the WallpaperStyle and TileWallpaper registry values.

        shl lstrlen(pszWallpaperStyle),1
       .new cbData:DWORD = eax

        RegSetValueEx(hKey, L"WallpaperStyle", 0, REG_SZ,
            pszWallpaperStyle, cbData)
        mov hr,HRESULT_FROM_WIN32(eax)

        .if (SUCCEEDED(hr))

            shl lstrlen(pszTileWallpaper),1
            mov cbData,eax

            RegSetValueEx(hKey, L"TileWallpaper", 0, REG_SZ,
                pszTileWallpaper, cbData)
            mov hr,HRESULT_FROM_WIN32(eax)
        .endif

        RegCloseKey(hKey)
    .endif

    ;; Set the desktop wallpapaer by calling the Win32 API SystemParametersInfo
    ;; with the SPI_SETDESKWALLPAPER desktop parameter. The changes should
    ;; persist, and also be immediately visible.
    .if (SUCCEEDED(hr))

        .if ( !SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, pszFile,
                SPIF_UPDATEINIFILE or SPIF_SENDWININICHANGE))

            mov hr,HRESULT_FROM_WIN32(GetLastError())
        .endif
    .endif

    .return hr

SetDesktopWallpaper endp

    end
