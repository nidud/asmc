
ifndef _WIN64
define _STDCALL_SUPPORTED
endif
include lang/en.txt
include windows.inc
include richedit.inc
include ltype.inc
include winres.inc
include tchar.inc

IDR_MAINMENU        equ 100
IDM_OPEN            equ 40001
IDM_SAVE            equ 40002
IDM_CLOSE           equ 40003
IDM_SAVEAS          equ 40004
IDM_EXIT            equ 40005
IDM_UNDO            equ 40006
IDM_REDO            equ 40007
IDM_COPY            equ 40008
IDM_CUT             equ 40009
IDM_PASTE           equ 40010
IDM_DELETE          equ 40011
IDM_SELECTALL       equ 40012
IDM_FIND            equ 40013
IDM_FINDNEXT        equ 40014
IDM_FINDPREV        equ 40015
IDM_REPLACE         equ 40016
IDM_GOTOLINE        equ 40017
IDM_FONT            equ 40018
IDM_COLOR           equ 40019
IDM_STATUSBAR       equ 40020
IDM_VIEWHELP        equ 40021
IDM_ABOUT           equ 40022

IDD_OPTIONDLG       equ 101
IDC_BACKCOLORBOX    equ 1000
IDC_TEXTCOLORBOX    equ 1001
IDR_MAINACCEL       equ 105
IDD_FINDDLG         equ 102
IDD_GOTODLG         equ 103
IDD_REPLACEDLG      equ 104
IDC_FINDEDIT        equ 1000
IDC_MATCHCASE       equ 1001
IDC_REPLACEEDIT     equ 1001
IDC_WHOLEWORD       equ 1002
IDC_DOWN            equ 1003
IDC_UP              equ 1004
IDC_LINENO          equ 1005
RichEditID          equ 300
;
; Attrib  A - Set forground color
; Quote   Q - Set color of quoted text
; Digit   D - Set color of numbers
; Char    C - Set color of chars
; Start   S - Set color from start of string
; Word    W - Set color of words
; Nested  N - Set color of nested strings
;
ST_ATTRIB           equ 1   ; attrib    <at>
ST_QUOTE            equ 2   ; quote     <at>
ST_NUMBER           equ 3   ; number    <at>
ST_CHAR             equ 4   ; char      <at> <chars>
ST_START            equ 5   ; start     <at> <string>
ST_WORD             equ 6   ; word      <at> <words> ...
ST_NESTED           equ 7   ; nested    <at> <string1> <string2>
ST_COUNT            equ 7

STYLESIZE           equ 0x4000
MAX_ENTRY           equ 256

