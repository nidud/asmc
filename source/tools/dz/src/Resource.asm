; RESOURCE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include doszip.inc

res macro name, lang:=<en>
IDD_&name& label RIDD
incbin <res\&lang&\&name&.idd>
align size_t
endm

.data
 res About
 res Calendar
 res CalHelp
 res CompareOptions
 res ConfirmAddFiles
 res ConfirmContinue
 res ConfirmDelete
 res ConsoleSize
 res Deflate64
 res DriveNotReady
 res CompareDirectories
 res Compression
 res Configuration
 res Confirmations
 res Copy
 res Decompress
 res DefaultColor
 res Environ
 res FFHelp
 res FileAttributes
 res FindFile
 res Help
 res History
 res MenuEdit
 res MenuFile
 res MenuHelp
 res MenuPanel
 res MenuSetup
 res MenuTools
 res MKList
 res Move
 res PanelFilter
 res PanelOptions
 res RecursiveCompare
 res SaveSetup
 res ScreenOptions
 res SubInfo
 res SystemInfo
 res SystemOptions
 res Transfer
 res ZipAttributes
 res EditColor
 res FFReplace
 res HEFormat
 res HELine
 res HEStatusline
 res Menusline
 res OperationFilters
 res Replace
 res ReplacePrompt
 res SaveScreen
 res Search
 res Statusline
 res TEOptions
 res TEQuickMenu
 res TEReload
 res TEReload2
 res TESave
 res TESeek
 res TEWindows
 res TVCopy
 res TVHelp
 res TVQuickMenu
 res TVSeek
 res TVStatusline
 res UnzipCRCError

 align size_t*2

 Resource IDD \
    { IDD_Menusline,        MKID(CT_MENUBAR, ID_MENUBAR) },
    { IDD_Statusline,       MKID(CT_KEYBAR,  ID_KEYBAR) },
    { IDD_MenuPanel,        MKID(CT_MENUDLG, ID_PANELA) },
    { IDD_MenuFile,         MKID(CT_MENUDLG, ID_FILE) },
    { IDD_MenuEdit,         MKID(CT_MENUDLG, ID_EDIT) },
    { IDD_MenuSetup,        MKID(CT_MENUDLG, ID_SETUP) },
    { IDD_MenuTools,        MKID(CT_MENUDLG, ID_TOOLS) },
    { IDD_MenuHelp,         MKID(CT_MENUDLG, ID_HELP) },
    { IDD_MenuPanel,        MKID(CT_MENUDLG, ID_PANELB) },
    { IDD_Calendar,         MKID(CT_DIALOG, ID_CALENDAR) },
    { IDD_CalHelp,          MKID(CT_DIALOG, ID_CALENDARHELP) },
    { IDD_CompareOptions,   MKID(CT_DIALOG, ID_COMPAREOPTIONS) },
    { IDD_ConfirmAddFiles,  MKID(CT_DIALOG, ID_CONFIRMADDFILES) },
    { IDD_ConfirmContinue,  MKID(CT_DIALOG, ID_CONFIRMCONTINUE) },
    { IDD_ConfirmDelete,    MKID(CT_DIALOG, ID_CONFIRMDELETE) },
    { IDD_ConsoleSize,      MKID(CT_DIALOG, ID_CONSOLESIZE) },
    { IDD_Deflate64,        MKID(CT_DIALOG, ID_DEFLATE64) },
    { IDD_DriveNotReady,    MKID(CT_DIALOG, ID_DRIVENOTREADY) },
    { IDD_CompareDirectories, MKID(CT_DIALOG, ID_COMPAREDIRECTORIES) },
    { IDD_Compression,      MKID(CT_DIALOG, ID_COMPRESSION) },
    { IDD_Configuration,    MKID(CT_DIALOG, ID_CONFIGURATION) },
    { IDD_Confirmations,    MKID(CT_DIALOG, ID_CONFIRMATIONS) },
    { IDD_Copy,             MKID(CT_DIALOG, ID_DZCOPY) },
    { IDD_Decompress,       MKID(CT_DIALOG, ID_DECOMPRESS) },
    { IDD_DefaultColor,     MKID(CT_DIALOG, ID_DEFAULTCOLOR) },
    { IDD_Environ,          MKID(CT_DIALOG, ID_ENVIRON) },
    { IDD_FindFile,         MKID(CT_DIALOG, ID_FINDFILE) },
    { IDD_FFHelp,           MKID(CT_DIALOG, ID_FINDFILEHELP) },
    { IDD_FileAttributes,   MKID(CT_DIALOG, ID_FILEATTRIBUTES) },
    { IDD_Help,             MKID(CT_DIALOG, ID_DZHELP) },
    { IDD_About,            MKID(CT_DIALOG, ID_ABOUT) },
    { IDD_History,          MKID(CT_DIALOG, ID_HISTORY) },
    { IDD_MKList,           MKID(CT_DIALOG, ID_MAKELIST) },
    { IDD_Move,             MKID(CT_DIALOG, ID_DZMOVE) },
    { IDD_PanelFilter,      MKID(CT_DIALOG, ID_PANELFILTER) },
    { IDD_PanelOptions,     MKID(CT_DIALOG, ID_PANELOPTIONS) },
    { IDD_RecursiveCompare, MKID(CT_DIALOG, ID_RECURSIVECOMPARE) },
    { IDD_SaveSetup,        MKID(CT_DIALOG, ID_SAVESETUP) },
    { IDD_ScreenOptions,    MKID(CT_DIALOG, ID_SCREENOPTIONS) },
    { IDD_SubInfo,          MKID(CT_DIALOG, ID_SUBINFO) },
    { IDD_SystemInfo,       MKID(CT_DIALOG, ID_SYSTEMINFO) },
    { IDD_SystemOptions,    MKID(CT_DIALOG, ID_SYSTEMOPTIONS) },
    { IDD_Transfer,         MKID(CT_DIALOG, ID_TRANSFER) },
    { IDD_ZipAttributes,    MKID(CT_DIALOG, ID_ZIPATTRIBUTES) },
    { IDD_EditColor,        MKID(CT_DIALOG, ID_EDITCOLOR) },
    { IDD_FFReplace,        MKID(CT_DIALOG, ID_FFREPLACE) },
    { IDD_HEFormat,         MKID(CT_DIALOG, ID_HEFORMAT) },
    { IDD_HELine,           MKID(CT_DIALOG, ID_HELINE) },
    { IDD_HEStatusline,     MKID(CT_KEYBAR, ID_HEKEYBAR) },
    { IDD_OperationFilters, MKID(CT_DIALOG, ID_OPERATIONFILTER) },
    { IDD_Replace,          MKID(CT_DIALOG, ID_REPLACE) },
    { IDD_ReplacePrompt,    MKID(CT_DIALOG, ID_REPLACEPROMPT) },
    { IDD_SaveScreen,       MKID(CT_DIALOG, ID_SAVESCREEN) },
    { IDD_Search,           MKID(CT_DIALOG, ID_SEARCH) },
    { IDD_TEOptions,        MKID(CT_DIALOG, ID_TEOPTIONS) },
    { IDD_TEQuickMenu,      MKID(CT_DIALOG, ID_TEQUICKMENU) },
    { IDD_TEReload,         MKID(CT_DIALOG, ID_TERELOAD) },
    { IDD_TEReload2,        MKID(CT_DIALOG, ID_TERELOAD2) },
    { IDD_TESave,           MKID(CT_DIALOG, ID_TESAVE) },
    { IDD_TESeek,           MKID(CT_DIALOG, ID_TESEEK) },
    { IDD_TEWindows,        MKID(CT_DIALOG, ID_TEWINDOWS) },
    { IDD_TVCopy,           MKID(CT_DIALOG, ID_TVCOPY) },
    { IDD_TVHelp,           MKID(CT_DIALOG, ID_TVHELP) },
    { IDD_TVQuickMenu,      MKID(CT_DIALOG, ID_TVQUICKMENU) },
    { IDD_TVSeek,           MKID(CT_DIALOG, ID_TVSEEK) },
    { IDD_TVStatusline,     MKID(CT_KEYBAR, ID_TVKEYBAR) },
    { IDD_UnzipCRCError,    MKID(CT_DIALOG, ID_UNZIPCRCERROR) },
    { NULL,                 0 }

 end
