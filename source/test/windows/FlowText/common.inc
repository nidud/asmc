
;; The following macros define the minimum required platform.  The minimum required platform
;; is the earliest version of Windows, Internet Explorer etc. that has the necessary features to run
;; your application.  The macros work by enabling all features available on platform versions up to and
;; including the version specified.

;; Specifies that the minimum required platform is Windows 7

ifndef _WIN32_WINNT
define _WIN32_WINNT 0x0601
endif

include stdio.inc
include windows.inc
include StrSafe.inc
include shlobj.inc

include XpsObjectModel.inc
include dwrite.inc
include strsafe.inc

SafeRelease proto T:abs {
    .if T
        T.Release()
        mov T,NULL
    .endif
    }
