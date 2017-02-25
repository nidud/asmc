ifndef __LIBC_INC
 include libc.inc
endif

.xlist
;
; Master include file for Windows applications.
;
ifndef _WINDOWS_
_WINDOWS_ equ 1

_X86_	  equ 1
__STDC__  equ 1
_MSC_VER  equ 1000

_INTEGRAL_MAX_BITS equ 64

ifndef _M_IX86
_M_IX86 equ 300
endif

ifndef _WIN32_WINNT
ifndef WINVER
_WIN32_WINNT	equ 400h
else
_WIN32_WINNT	equ WINVER
endif
endif
ifndef _WIN32_WINDOWS
ifndef WINVER
_WIN32_WINDOWS	equ 400h
else
_WIN32_WINDOWS	equ WINVER
endif
endif

ifndef _WIN32_FUSION
_WIN32_FUSION	equ 0
endif

ifndef _WIN32_WCE
_WIN32_WCE	equ 0
endif

ifndef ISOLATION_AWARE_ENABLED
ISOLATION_AWARE_ENABLED equ 0
endif

ifndef WINVER
WINVER equ 0x0400
else
if defined(_WIN32_WINNT) and (WINVER LT 0x0400) and (_WIN32_WINNT GT 0x0400)
.err <WINVER setting conflicts with _WIN32_WINNT setting>
endif
endif

if WINVER GE 0x0500
echo
echo NOTE: WINVER has been defined as 0x0500 or greater which enables
echo Windows NT 5.0 and Windows 98 features. When these headers were released,
echo Windows NT 5.0 beta 1 and Windows 98 beta 2.1 were the current versions.
echo
echo For this release when WINVER is defined as 0x0500 or greater, you can only
echo build beta or test applications.  To build a retail application,
echo set WINVER to 0x0400 or visit http://www.microsoft.com/msdn/sdk
echo to see if retail Windows NT 5.0 or Windows 98 headers are available.
echo
echo See the SDK release notes for more information.
echo
endif

ifndef _INC_WINDOWS
_INC_WINDOWS equ 1
;
;  If defined, the following flags inhibit definition
;     of the indicated items.
;
;  NOGDICAPMASKS     - CC_*, LC_*, PC_*, CP_*, TC_*, RC_
;  NOVIRTUALKEYCODES - VK_*
;  NOWINMESSAGES     - WM_*, EM_*, LB_*, CB_*
;  NOWINSTYLES	     - WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
;  NOSYSMETRICS	     - SM_*
;  NOMENUS	     - MF_*
;  NOICONS	     - IDI_*
;  NOKEYSTATES	     - MK_*
;  NOSYSCOMMANDS     - SC_*
;  NORASTEROPS	     - Binary and Tertiary raster ops
;  NOSHOWWINDOW	     - SW_*
;  OEMRESOURCE	     - OEM Resource values
;  NOATOM	     - Atom Manager routines
;  NOCLIPBOARD	     - Clipboard routines
;  NOCOLOR	     - Screen colors
;  NOCTLMGR	     - Control and Dialog routines
;  NODRAWTEXT	     - DrawText() and DT_*
;  NOGDI	     - All GDI defines and routines
;  NOKERNEL	     - All KERNEL defines and routines
;  NOUSER	     - All USER defines and routines
;  NONLS	     - All NLS defines and routines
;  NOMB		     - MB_* and MessageBox()
;  NOMEMMGR	     - GMEM_*, LMEM_*, GHND, LHND, associated routines
;  NOMETAFILE	     - typedef METAFILEPICT
;  NOMINMAX	     - Macros min(a,b) and max(a,b)
;  NOMSG	     - typedef MSG and associated routines
;  NOOPENFILE	     - OpenFile(), OemToAnsi, AnsiToOem, and OF_*
;  NOSCROLL	     - SB_* and scrolling routines
;  NOSERVICE	     - All Service Controller routines, SERVICE_ equates, etc.
;  NOSOUND	     - Sound driver routines
;  NOTEXTMETRIC	     - typedef TEXTMETRIC and associated routines
;  NOWH		     - SetWindowsHook and WH_*
;  NOWINOFFSETS	     - GWL_*, GCL_*, associated routines
;  NOCOMM	     - COMM driver routines
;  NOKANJI	     - Kanji support stuff.
;  NOHELP	     - Help engine interface.
;  NOPROFILER	     - Profiler interface.
;  NODEFERWINDOWPOS  - DeferWindowPos routines
;  NOMCX	     - Modem Configuration Extensions
;

include excpt.inc
include stdarg.inc

include windef.inc
include winbase.inc
include wingdi.inc
include winuser.inc

ifdef _WIN32NLS
include winnls.inc
endif

include wincon.inc
include winver.inc

ifdef _WIN32REG
include winreg.inc
endif

include winnetwk.inc


ifndef WIN32_LEAN_AND_MEAN
include cderr.inc
include dde.inc
include ddeml.inc
include dlgs.inc

include lzexpand.inc
include mmsystem.inc
include nb30.inc
include rpc.inc

include shellapi.inc

include winperf.inc

if _WIN32_WINNT GE 0x0400
include winsock2.inc
include mswsock.inc
else
include winsock.inc
endif

ifndef NOCRYPT
include wincrypt.inc
endif

ifndef NOGDI
include commdlg.inc
include winspool.inc
ifdef INC_OLE1
include ole.inc
else
include ole2.inc
endif
endif
endif ; WIN32_LEAN_AND_MEAN

ifdef INC_OLE2
include ole2.inc
endif

ifndef NOSERVICE
include winsvc.inc
endif

if WINVER GE 0x0400
ifndef NOMCX
include mcx.inc
endif
ifndef NOIME
include imm.inc
endif
endif ; WINVER >= 0x0400

endif ; _INC_WINDOWS
endif ; _WINDOWS_

.list
