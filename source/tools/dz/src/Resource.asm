; RESOURCE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

res macro name, lang:=<en>
public IDD_&name&
IDD_&name& PIDD &name&_RC
&name&_RC label RIDD
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
 res DZCompareDirectories
 res DZCompression
 res DZConfiguration
 res DZConfirmations
 res DZCopy
 res DZDecompress
 res DZDefaultColor
 res DZEnviron
 res DZFFHelp
 res DZFileAttributes
 res DZFindFile
 res DZHelp
 res DZHistory
 res DZMenuEdit
 res DZMenuFile
 res DZMenuHelp
 res DZMenuPanel
 res DZMenuSetup
 res DZMenuTools
 res DZMKList
 res DZMove
 res DZPanelFilter
 res DZPanelOptions
 res DZRecursiveCompare
 res DZSaveSetup
 res DZScreenOptions
 res DZSubInfo
 res DZSystemInfo
 res DZSystemOptions
 res DZTransfer
 res DZZipAttributes
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

 end
