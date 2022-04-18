;;
;; The file declares the wallpaper helper functions.
;;
;;    BOOL SupportJpgAsWallpaper();
;;    BOOL SupportFitFillWallpaperStyles();
;;    HRESULT SetDesktopWallpaper(PWSTR pszFile, WallpaperStyle style);
;;
;; SetDesktopWallpaper is the key function that sets the desktop wallpaper. The
;; function body is composed of configuring the wallpaper style in the registry
;; and setting the wallpaper with SystemParametersInfo.
;;


;;
;;   FUNCTION: SupportJpgAsWallpaper()
;;
;;   PURPOSE: Determine if .jpg files are supported as wallpaper in the
;;   current operating system. The .jpg wallpapers are not supported before
;;   Windows Vista.
;;
SupportJpgAsWallpaper proto


;;
;;   FUNCTION: SupportFitFillWallpaperStyles()
;;
;;   PURPOSE: Determine if the fit and fill wallpaper styles are supported in
;;   the current operating system. The styles are not supported before
;;   Windows 7.
;;
SupportFitFillWallpaperStyles proto


.enum WallpaperStyle {
    Tile,
    Center,
    Stretch,
    Fit,
    Fill
    }


;;
;;   FUNCTION: SetDesktopWallpaper(PCWSTR, WallpaperStyle)
;;
;;   PURPOSE: Set the desktop wallpaper.
;;
;;   PARAMETERS:
;;   * pszFile - Path of the wallpaper
;;   * style - Wallpaper style
;;
SetDesktopWallpaper proto pszFile:PWSTR, style:WallpaperStyle
