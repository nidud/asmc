ifndef __LIBC_INC
 include libc.inc
endif
.xlist
;;==========================================================================
;;
;;  Include file for Multimedia API's
;;
;;--------------------------------------------------------------------------
;;
;;  Define:	    Prevent inclusion of:
;;  --------------  --------------------------------------------------------
;;  MMNODRV	    Installable driver support
;;  MMNOSOUND	    Sound support
;;  MMNOWAVE	    Waveform support
;;  MMNOMIDI	    MIDI support
;;  MMNOAUX	    Auxiliary audio support
;;  MMNOMIXER	    Mixer support
;;  MMNOTIMER	    Timer support
;;  MMNOJOY	    Joystick support
;;  MMNOMCI	    MCI support
;;  MMNOMMIO	    Multimedia file I/O support
;;  MMNOMMSYSTEM    General MMSYSTEM functions
;;
;;==========================================================================
;;

ifndef _INC_MMSYSTEM
_INC_MMSYSTEM equ 1 ;; #defined if mmsystem.inc has been included

if defined(_WINMM_) or defined(__PE__)
option dllimport:<winmm>
endif

if 0
ifdef _WIN32
ifndef
WINMMAPI		equ DECSPEC_IMPORT
else
WINMMAPI		equ 1
endif
_loadds			equ 1
_huge			equ 1
else
WINMMAPI		equ 1
endif
endif

ifdef _WIN32_VXD

NEAR equ 1
FAR equ 1

DECLARE_HANDLE macro x
	exitm<typedef WORD x>
	endm
WINAPI equ 1

LPSTR			typedef DWORD
LPVOID			typedef DWORD
LPCSTR			typedef DWORD
LPCWSTR			typedef DWORD
LRESULT			typedef DWORD
LPARAM			typedef DWORD
WPARAM			typedef DWORD

WCHAR			typedef short

endif

;;***************************************************************************
;;
;; constants and data types General ?
;;
;;**************************************************************************

;; general constants
MAXPNAMELEN		equ 32	   ;; max product name length (including NULL)
MAXERRORLENGTH		equ 256	   ;; max error text length (including NULL)
MAX_JOYSTICKOEMVXDNAME	equ 260 ;; max oem vxd name length (including NULL)

;;
;;  Microsoft Manufacturer and Product ID's (these have been moved to
;;  MMREG.H for Windows 4.00 and above).
;;
if (WINVER LE 0x030A)
ifndef MM_MICROSOFT
MM_MICROSOFT		equ 1	;; Microsoft Corporation
endif

ifndef MM_MIDI_MAPPER
MM_MIDI_MAPPER		equ 1	;; MIDI Mapper
MM_WAVE_MAPPER		equ 2	;; Wave Mapper
MM_SNDBLST_MIDIOUT	equ 3	;; Sound Blaster MIDI output port
MM_SNDBLST_MIDIIN	equ 4	;; Sound Blaster MIDI input port
MM_SNDBLST_SYNTH	equ 5	;; Sound Blaster internal synthesizer
MM_SNDBLST_WAVEOUT	equ 6	;; Sound Blaster waveform output
MM_SNDBLST_WAVEIN	equ 7	;; Sound Blaster waveform input
MM_ADLIB		equ 9	;; Ad Lib-compatible synthesizer
MM_MPU401_MIDIOUT	equ 10	 ;; MPU401-compatible MIDI output port
MM_MPU401_MIDIIN	equ 11	 ;; MPU401-compatible MIDI input port
MM_PC_JOYSTICK		equ 12	 ;; Joystick adapter
endif
endif

;; general data types

ifdef _WIN32
MMVERSION		typedef UINT	;; major (high byte), minor (low byte)
else
VERSION			typedef UINT	;; major (high byte), minor (low byte)
endif
MMRESULT		typedef UINT	;; error return code, 0 means no error
					;; call as if(err=xxxx(...)) Error(err); else
_MMRESULT_		equ 1

LPUINT			typedef ptr UINT

;; MMTIME data structure
MMTIME			STRUC
wType			UINT ?	;; indicates the contents of the union
UNION
    ms			dd ?	;; milliseconds
    sample		dd ?	;; samples
    cb			dd ?	;; byte count
    ticks		dd ?	;; ticks in MIDI stream
    STRUC smpte
	;; SMPTE
	hour		db ?	;; hours
	min		db ?	;; minutes
	sec		db ?	;; seconds
	frame		db ?	;; frames
	fps		db ?	;; frames per second
	dummy		db ?	;; pad
ifdef _WIN32
	pad		db 2 dup(?)
endif
    ENDS
    STRUC midi
	;; MIDI
	songptrpos	dd ?	;; song pointer position
    ENDS
ENDS
MMTIME			ENDS
PMMTIME			typedef ptr MMTIME
NPMMTIME		typedef ptr MMTIME
LPMMTIME		typedef ptr MMTIME

;; types for wType field in MMTIME struct
TIME_MS			equ 0x0001  ;; time in milliseconds
TIME_SAMPLES		equ 0x0002  ;; number of wave samples
TIME_BYTES		equ 0x0004  ;; current byte offset
TIME_SMPTE		equ 0x0008  ;; SMPTE time
TIME_MIDI		equ 0x0010  ;; MIDI time
TIME_TICKS		equ 0x0020  ;; Ticks within MIDI stream

;;
;;
;;
;;
MAKEFOURCC macro ch0, ch1, ch2, ch3
	exitm<ch0 or (ch1 shl 8) or (ch2 shl 16) or (ch3 shl 24 )>
	endm


;;***************************************************************************
;;
;; Extensions Window Messages Multimedia ?
;;
;;**************************************************************************

MM_JOY1MOVE		equ 0x3A0	    ;; joystick
MM_JOY2MOVE		equ 0x3A1
MM_JOY1ZMOVE		equ 0x3A2
MM_JOY2ZMOVE		equ 0x3A3
MM_JOY1BUTTONDOWN	equ 0x3B5
MM_JOY2BUTTONDOWN	equ 0x3B6
MM_JOY1BUTTONUP		equ 0x3B7
MM_JOY2BUTTONUP		equ 0x3B8

MM_MCINOTIFY		equ 0x3B9	    ;; MCI

MM_WOM_OPEN		equ 0x3BB	    ;; waveform output
MM_WOM_CLOSE		equ 0x3BC
MM_WOM_DONE		equ 0x3BD

MM_WIM_OPEN		equ 0x3BE	    ;; waveform input
MM_WIM_CLOSE		equ 0x3BF
MM_WIM_DATA		equ 0x3C0

MM_MIM_OPEN		equ 0x3C1	    ;; MIDI input
MM_MIM_CLOSE		equ 0x3C2
MM_MIM_DATA		equ 0x3C3
MM_MIM_LONGDATA		equ 0x3C4
MM_MIM_ERROR		equ 0x3C5
MM_MIM_LONGERROR	equ 0x3C6

MM_MOM_OPEN		equ 0x3C7	    ;; MIDI output
MM_MOM_CLOSE		equ 0x3C8
MM_MOM_DONE		equ 0x3C9

;; these are also in msvideo.h
ifndef MM_DRVM_OPEN
MM_DRVM_OPEN		equ 0x3D0	    ;; installable drivers
MM_DRVM_CLOSE		equ 0x3D1
MM_DRVM_DATA		equ 0x3D2
MM_DRVM_ERROR		equ 0x3D3
endif

;; these are used by msacm.h
MM_STREAM_OPEN		equ 0x3D4
MM_STREAM_CLOSE		equ 0x3D5
MM_STREAM_DONE		equ 0x3D6
MM_STREAM_ERROR		equ 0x3D7

if(WINVER GE 0x0400)
MM_MOM_POSITIONCB	equ 0x3CA	    ;; Callback for MEVT_POSITIONCB

ifndef MM_MCISIGNAL
MM_MCISIGNAL		equ 0x3CB
endif

MM_MIM_MOREDATA		equ 0x3CC	   ;; MIM_DONE w/ pending events

endif ;; WINVER GE 0x0400
MM_MIXM_LINE_CHANGE	equ 0x3D0	;; mixer line change notify
MM_MIXM_CONTROL_CHANGE	equ 0x3D1	;; mixer control change notify

;;***************************************************************************
;;
;; String resource number bases (internal use)
;;
;;**************************************************************************

MMSYSERR_BASE		equ 0
WAVERR_BASE		equ 32
MIDIERR_BASE		equ 64
TIMERR_BASE		equ 96
JOYERR_BASE		equ 160
MCIERR_BASE		equ 256
MIXERR_BASE		equ 1024

MCI_STRING_OFFSET	equ 512
MCI_VD_OFFSET		equ 1024
MCI_CD_OFFSET		equ 1088
MCI_WAVE_OFFSET		equ 1152
MCI_SEQ_OFFSET		equ 1216

;;***************************************************************************
;;
;; General error return values
;;
;;**************************************************************************

;; general error return values
MMSYSERR_NOERROR	equ 0			 ;; no error
MMSYSERR_ERROR		equ (MMSYSERR_BASE + 1)	 ;; unspecified error
MMSYSERR_BADDEVICEID	equ (MMSYSERR_BASE + 2)	 ;; device ID out of range
MMSYSERR_NOTENABLED	equ (MMSYSERR_BASE + 3)	 ;; driver failed enable
MMSYSERR_ALLOCATED	equ (MMSYSERR_BASE + 4)	 ;; device already allocated
MMSYSERR_INVALHANDLE	equ (MMSYSERR_BASE + 5)	 ;; device handle is invalid
MMSYSERR_NODRIVER	equ (MMSYSERR_BASE + 6)	 ;; no device driver present
MMSYSERR_NOMEM		equ (MMSYSERR_BASE + 7)	 ;; memory allocation error
MMSYSERR_NOTSUPPORTED	equ (MMSYSERR_BASE + 8)	 ;; function isn't supported
MMSYSERR_BADERRNUM	equ (MMSYSERR_BASE + 9)	 ;; error value out of range
MMSYSERR_INVALFLAG	equ (MMSYSERR_BASE + 10) ;; invalid flag passed
MMSYSERR_INVALPARAM	equ (MMSYSERR_BASE + 11) ;; invalid parameter passed
MMSYSERR_HANDLEBUSY	equ (MMSYSERR_BASE + 12) ;; handle being used
;; simultaneously on another
;; thread (eg callback)
MMSYSERR_INVALIDALIAS	equ (MMSYSERR_BASE + 13) ;; specified alias not found
MMSYSERR_BADDB		equ (MMSYSERR_BASE + 14) ;; bad registry database
MMSYSERR_KEYNOTFOUND	equ (MMSYSERR_BASE + 15) ;; registry key not found
MMSYSERR_READERROR	equ (MMSYSERR_BASE + 16) ;; registry read error
MMSYSERR_WRITEERROR	equ (MMSYSERR_BASE + 17) ;; registry write error
MMSYSERR_DELETEERROR	equ (MMSYSERR_BASE + 18) ;; registry delete error
MMSYSERR_VALNOTFOUND	equ (MMSYSERR_BASE + 19) ;; registry value not found
MMSYSERR_NODRIVERCB	equ (MMSYSERR_BASE + 20) ;; driver does not call DriverCallback
MMSYSERR_LASTERROR	equ (MMSYSERR_BASE + 20) ;; last error in range

if (WINVER LT 0x030a) OR defined(_WIN32)
HDRVR			typedef HANDLE
endif ;; ifdef WINVER LT 0x030a

ifndef MMNODRV

;;***************************************************************************
;;
;; Installable driver support
;;
;;**************************************************************************

ifdef _WIN32
DRVCONFIGINFOEX		STRUC
dwDCISize		dd ?
lpszDCISectionName	LPCWSTR ?
lpszDCIAliasName	LPCWSTR ?
dnDevNode		dd ?
DRVCONFIGINFOEX		ENDS
PDRVCONFIGINFOEX	typedef ptr DRVCONFIGINFOEX
NPDRVCONFIGINFOEX	typedef ptr DRVCONFIGINFOEX
LPDRVCONFIGINFOEX	typedef ptr DRVCONFIGINFOEX

else
DRVCONFIGINFOEX		STRUC
dwDCISize		dd ?
lpszDCISectionName	LPCSTR ?
lpszDCIAliasName	LPCSTR ?
dnDevNode		dd ?
DRVCONFIGINFOEX		ENDS
PDRVCONFIGINFOEX	typedef ptr DRVCONFIGINFOEX
NPDRVCONFIGINFOEX	typedef ptr DRVCONFIGINFOEX
LPDRVCONFIGINFOEX	typedef ptr DRVCONFIGINFOEX
endif

if (WINVER LT 0x030a) OR defined(_WIN32)

ifndef DRV_LOAD

;; Driver messages
DRV_LOAD		equ 0x0001
DRV_ENABLE		equ 0x0002
DRV_OPEN		equ 0x0003
DRV_CLOSE		equ 0x0004
DRV_DISABLE		equ 0x0005
DRV_FREE		equ 0x0006
DRV_CONFIGURE		equ 0x0007
DRV_QUERYCONFIGURE	equ 0x0008
DRV_INSTALL		equ 0x0009
DRV_REMOVE		equ 0x000A
DRV_EXITSESSION		equ 0x000B
DRV_POWER		equ 0x000F
DRV_RESERVED		equ 0x0800
DRV_USER		equ 0x4000

;; LPARAM of DRV_CONFIGURE message
ifdef _WIN32
DRVCONFIGINFO		STRUC
dwDCISize		dd ?
lpszDCISectionName	LPCWSTR ?
lpszDCIAliasName	LPCWSTR ?
DRVCONFIGINFO		ENDS
PDRVCONFIGINFO		typedef ptr DRVCONFIGINFO
NPDRVCONFIGINFO		typedef ptr DRVCONFIGINFO
LPDRVCONFIGINFO		typedef ptr DRVCONFIGINFO
else
DRVCONFIGINFO		STRUC
dwDCISize		dd ?
lpszDCISectionName	LPCSTR ?
lpszDCIAliasName	LPCSTR ?
DRVCONFIGINFO		ENDS
PDRVCONFIGINFO		typedef ptr DRVCONFIGINFO
NPDRVCONFIGINFO		typedef ptr DRVCONFIGINFO
LPDRVCONFIGINFO		typedef ptr DRVCONFIGINFO
endif

;; Supported return values for DRV_CONFIGURE message
DRVCNF_CANCEL		equ 0x0000
DRVCNF_OK		equ 0x0001
DRVCNF_RESTART		equ 0x0002

;; installable driver function prototypes
ifdef _WIN32
ifndef _WIN32_VXD

DRIVERPROC_T typedef proto \
		      : DWORD,
		      : HDRVR,
		      : UINT,
		      : LPARAM,
		      : LPARAM
DRIVERPROC typedef ptr DRIVERPROC_T

;LRESULT
CloseDriver proto _CType \
	       hDriver: HDRVR,
	       lParam1: LONG,
	       lParam2: LONG
;HDRVR
OpenDriver proto _CType \
	  szDriverName: LPCWSTR,
	 szSectionName: LPCWSTR,
	       lParam2: LONG

;LRESULT
SendDriverMessage proto _CType \
	       hDriver: HDRVR,
	       message: UINT,
	       lParam1: LONG,
	       lParam2: LONG
;HMODULE
DrvGetModuleHandle proto _CType \
	       hDriver: HDRVR
;HMODULE
GetDriverModuleHandle proto _CType \
	       hDriver: HDRVR
;LRESULT
DefDriverProc proto _CType \
    dwDriverIdentifier: DWORD,
		 hdrvr: HDRVR,
		  uMsg: UINT,
	       lParam1: LPARAM,
	       lParam2: LPARAM
endif ;; _WIN32_VXD
else
;LRESULT
DrvClose proto _CType \
		 hdrvr: HDRVR,
	       lParam1: LPARAM,
	       lParam2: LPARAM

;HDRVR
DrvOpen proto _CType \
	  szDriverName: LPCSTR,
	 szSectionName: LPCSTR,
	       lParam2: LPARAM

;LRESULT
DrvSendMessage proto _CType \
		 hdrvr: HDRVR,
		  uMsg: UINT,
	       lParam1: LPARAM,
	       lParam2: LPARAM

;HINSTANCE
DrvGetModuleHandle proto _CType \
		  hdrvr: HDRVR

DrvDefDriverProc proto _CType \
    dwDriverIdentifier: DWORD,
		 hdrvr: HDRVR,
		  uMsg: UINT,
	       lParam1: LPARAM,
	       lParam2: LPARAM

DefDriverProc		equ <DrvDefDriverProc>
endif ;; ifdef _WIN32
endif ;; DRV_LOAD
endif ;; ifdef (WINVER LT 0x030a) OR defined(_WIN32)

if (WINVER GE 0x030a)
;; return values from DriverProc() function
DRV_CANCEL		equ DRVCNF_CANCE
DRV_OK			equ DRVCNF_OK
DRV_RESTART		equ DRVCNF_RESTART

endif ;; ifdef WINVER GE 0x030a

DRV_MCI_FIRST		equ DRV_RESERVED
DRV_MCI_LAST		equ (DRV_RESERVED + 0xFFF)

endif  ;; ifndef MMNODRV

;;**************************************************************************
;;
;; Driver callback support
;;
;;**************************************************************************

;; flags used with waveOutOpen(), waveInOpen(), midiInOpen(), and
;; midiOutOpen() to specify the type of the dwCallback parameter.

CALLBACK_TYPEMASK	equ 0x00070000	  ;; callback type mask
CALLBACK_NULL		equ 0x00000000	  ;; no callback
CALLBACK_WINDOW		equ 0x00010000	  ;; dwCallback is a HWND
CALLBACK_TASK		equ 0x00020000	  ;; dwCallback is a HTASK
CALLBACK_FUNCTION	equ 0x00030000	  ;; dwCallback is a FARPROC
ifdef _WIN32
CALLBACK_THREAD		equ CALLBACK_TASK  ;; thread ID replaces 16 bit task
CALLBACK_EVENT		equ 0x00050000	  ;; dwCallback is an EVENT Handle
endif

ifndef _WIN32_VXD

;void
DRVCALLBACK	typedef proto _CType \
		 hdrvr: HDRVR,
		  uMsg: UINT,
		dwUser: DWORD,
		   dw1: DWORD,
		   dw2: DWORD

LPDRVCALLBACK	typedef ptr DRVCALLBACK
ifdef _WIN32
PDRVCALLBACK	typedef ptr DRVCALLBACK
endif

endif	;; ifndef _WIN32_VXD

ifndef MMNOMMSYSTEM
ifndef _WIN32_VXD
;;**************************************************************************
;;
;; General MMSYSTEM support
;;
;;**************************************************************************

if (WINVER LE 0x030A)
;UINT
mmsystemGetVersion proto _CType
endif
ifdef _WIN32
OutputDebugStr		equ <OutputDebugString>
else
;void
OutputDebugStr proto _CType \
		      : LPCSTR
endif

endif  ;; ifndef _WIN32_VXD
endif  ;; ifndef MMNOMMSYSTEM

ifndef MMNOSOUND
ifndef _WIN32_VXD
;;**************************************************************************
;;
;; Sound support
;;
;;**************************************************************************

ifdef _WIN32

;BOOL
sndPlaySoundA proto _CType \
	      pszSound: LPCSTR,
	       fuSound: UINT
;BOOL
sndPlaySoundW proto _CType \
	      pszSound: LPCWSTR,
	       fuSound: UINT
ifdef _UNICODE
sndPlaySound	equ <sndPlaySoundW>
else
sndPlaySound	equ <sndPlaySoundA>
endif ;; NOT UNICODE

else
;BOOL
sndPlaySound proto _CType \
	      pszSound: LPCSTR,
	       fuSound: UINT
endif

;;
;;  flag values for fuSound and fdwSound arguments on [snd]PlaySound
;;
SND_SYNC		equ 0x0000  ;; play synchronously (default)
SND_ASYNC		equ 0x0001  ;; play asynchronously
SND_NODEFAULT		equ 0x0002  ;; silence ( NOT default) if sound not found
SND_MEMORY		equ 0x0004  ;; pszSound points to a memory file
SND_LOOP		equ 0x0008  ;; loop the sound until next sndPlaySound
SND_NOSTOP		equ 0x0010  ;; don't stop any currently playing sound

SND_NOWAIT		equ 0x00002000 ;; don't wait if the driver is busy
SND_ALIAS		equ 0x00010000 ;; name is a registry alias
SND_ALIAS_ID		equ 0x00110000 ;; alias is a predefined ID
SND_FILENAME		equ 0x00020000 ;; name is file name
SND_RESOURCE		equ 0x00040004 ;; name is resource name or atom
if(WINVER GE 0x0400)
SND_PURGE		equ 0x0040  ;; purge non-static events for task
SND_APPLICATION		equ 0x0080  ;; look for application specific association
endif ;; WINVER GE 0x0400

SND_ALIAS_START		equ 0		;; alias base

ifdef _WIN32
sndAlias macro ch0, ch1
	exitm<SND_ALIAS_START + ch0 OR (ch1 SHL 8)>
	endm

SND_ALIAS_SYSTEMASTERISK	equ sndAlias('S', '*')
SND_ALIAS_SYSTEMQUESTION	equ sndAlias('S', '?')
SND_ALIAS_SYSTEMHAND		equ sndAlias('S', 'H')
SND_ALIAS_SYSTEMEXIT		equ sndAlias('S', 'E')
SND_ALIAS_SYSTEMSTART		equ sndAlias('S', 'S')
SND_ALIAS_SYSTEMWELCOME		equ sndAlias('S', 'W')
SND_ALIAS_SYSTEMEXCLAMATION	equ sndAlias('S', ' NOT ')
SND_ALIAS_SYSTEMDEFAULT		equ sndAlias('S', 'D')

;BOOL
PlaySoundA proto _CType \
	      pszSound: LPCSTR,
		  hmod: HMODULE,
	      fdwSound: DWORD
;BOOL
PlaySoundW proto _CType \
	      pszSound: LPCWSTR,
		  hmod: HMODULE,
	      fdwSound: DWORD
ifdef _UNICODE
PlaySound		equ <PlaySoundW>
else
PlaySound		equ <PlaySoundA>
endif ;; NOT UNICODE

else
;BOOL
PlaySound proto _CType \
	      pszSound: LPCSTR,
		  hmod: HMODULE,
	      fdwSound: DWORD
endif

endif  ;; ifndef _WIN32_VXD
endif  ;; ifndef MMNOSOUND

ifndef MMNOWAVE
;;***************************************************************************
;;
;; Waveform audio support
;;
;;**************************************************************************

;; waveform audio error return values
WAVERR_BADFORMAT	equ (WAVERR_BASE + 0)	 ;; unsupported wave format
WAVERR_STILLPLAYING	equ (WAVERR_BASE + 1)	 ;; still something playing
WAVERR_UNPREPARED	equ (WAVERR_BASE + 2)	 ;; header not prepared
WAVERR_SYNC		equ (WAVERR_BASE + 3)	 ;; device is synchronous
WAVERR_LASTERROR	equ (WAVERR_BASE + 3)	 ;; last error in range

;; waveform audio data types
HWAVE			typedef HANDLE
HWAVEIN			typedef HANDLE
HWAVEOUT		typedef HANDLE
ifndef _WIN32_VXD
LPHWAVEIN		typedef ptr HWAVEIN
LPHWAVEOUT		typedef ptr HWAVEOUT
WAVECALLBACK		typedef DRVCALLBACK
LPWAVECALLBACK		typedef ptr WAVECALLBACK
endif

;; wave callback messages
WOM_OPEN		equ MM_WOM_OPEN
WOM_CLOSE		equ MM_WOM_COSE
WOM_DONE		equ MM_WOM_DONE
WIM_OPEN		equ MM_WIM_OPEN
WIM_CLOSE		equ MM_WIM_COSE
WIM_DATA		equ MM_WIM_DATA

;; device ID for wave device mapper
WAVE_MAPPER		equ -1

;; flags for dwFlags parameter in waveOutOpen() and waveInOpen()
WAVE_FORMAT_QUERY	equ 0x0001
WAVE_ALLOWSYNC		equ 0x0002
if(WINVER GE 0x0400)
WAVE_MAPPED		equ 0x0004
WAVE_FORMAT_DIRECT	equ 0x0008
WAVE_FORMAT_DIRECT_QUERY equ (WAVE_FORMAT_QUERY OR WAVE_FORMAT_DIRECT)
endif ;; WINVER GE 0x0400

;; wave data block header
WAVEHDR			STRUC
lpData			LPSTR ? ;; pointer to locked data buffer
dwBufferLength		dd ?	;; length of data buffer
dwBytesRecorded		dd ?	;; used for input only
dwUser			dd ?	;; for client's use
dwFlags			dd ?	;; assorted flags (see defines)
dwLoops			dd ?	;; loop control counter
lpNext			PVOID ? ;; reserved for driver
reserved		dd ?	;; reserved for driver
WAVEHDR			ENDS
PWAVEHDR		typedef ptr WAVEHDR
NPWAVEHDR		typedef ptr WAVEHDR
LPWAVEHDR		typedef ptr WAVEHDR

;; flags for dwFlags field of WAVEHDR
WHDR_DONE		equ 0x00000001	;; done bit
WHDR_PREPARED		equ 0x00000002	;; set if this header has been prepared
WHDR_BEGINLOOP		equ 0x00000004	;; loop start block
WHDR_ENDLOOP		equ 0x00000008	;; loop end block
WHDR_INQUEUE		equ 0x00000010	;; reserved for driver

;; waveform output device capabilities structure
ifdef _WIN32

WAVEOUTCAPSA		STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
vDriverVersion		MMVERSION ?	;; version of the driver
szPname			db MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
dwFormats		dd ?	;; formats supported
wChannels		dw ?	;; number of sources supported
wReserved1		dw ?	;; packing
dwSupport		dd ?	;; functionality supported by driver
WAVEOUTCAPSA		ENDS
PWAVEOUTCAPSA		typedef ptr WAVEOUTCAPSA
NPWAVEOUTCAPSA		typedef ptr WAVEOUTCAPSA
LPWAVEOUTCAPSA		typedef ptr WAVEOUTCAPSA
WAVEOUTCAPSW		STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
vDriverVersion		MMVERSION ?	;; version of the driver
szPname			dw MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
dwFormats		dd ?	;; formats supported
wChannels		dw ?	;; number of sources supported
wReserved1		dw ?	;; packing
dwSupport		dd ?	;; functionality supported by driver
WAVEOUTCAPSW		ENDS
PWAVEOUTCAPSW		typedef ptr WAVEOUTCAPSW
NPWAVEOUTCAPSW		typedef ptr WAVEOUTCAPSW
LPWAVEOUTCAPSW		typedef ptr WAVEOUTCAPSW
ifdef _UNICODE
WAVEOUTCAPS		typedef WAVEOUTCAPSW
PWAVEOUTCAPS		typedef PWAVEOUTCAPSW
NPWAVEOUTCAPS		typedef NPWAVEOUTCAPSW
LPWAVEOUTCAPS		typedef LPWAVEOUTCAPSW
else
WAVEOUTCAPS		typedef WAVEOUTCAPSA
PWAVEOUTCAPS		typedef PWAVEOUTCAPSA
NPWAVEOUTCAPS		typedef NPWAVEOUTCAPSA
LPWAVEOUTCAPS		typedef LPWAVEOUTCAPSA
endif ;; UNICODE

else
WAVEOUTCAPS		STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
vDriverVersion		VERSION ?	;; version of the driver
szPname			db MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
dwFormats		dd ?	;; formats supported
wChannels		dw ?	;; number of sources supported
dwSupport		dd ?	;; functionality supported by driver
WAVEOUTCAPS		ENDS
PWAVEOUTCAPS		typedef ptr WAVEOUTCAPS
NPWAVEOUTCAPS		typedef ptr WAVEOUTCAPS
LPWAVEOUTCAPS		typedef ptr WAVEOUTCAPS
endif

;; flags for dwSupport field of WAVEOUTCAPS
WAVECAPS_PITCH		equ 0x0001   ;; supports pitch control
WAVECAPS_PLAYBACKRATE	equ 0x0002   ;; supports playback rate control
WAVECAPS_VOLUME		equ 0x0004   ;; supports volume control
WAVECAPS_LRVOLUME	equ 0x0008   ;; separate left-right volume control
WAVECAPS_SYNC		equ 0x0010
WAVECAPS_SAMPLEACCURATE equ 0x0020
WAVECAPS_DIRECTSOUND	equ 0x0040

;; waveform input device capabilities structure
ifdef _WIN32

WAVEINCAPSA		STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
vDriverVersion		MMVERSION ?	;; version of the driver
szPname			db MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
dwFormats		dd ?	;; formats supported
wChannels		dw ?	;; number of channels supported
wReserved1		dw ?	;; structure packing
WAVEINCAPSA		ENDS
PWAVEINCAPSA		typedef ptr WAVEINCAPSA
NPWAVEINCAPSA		typedef ptr WAVEINCAPSA
LPWAVEINCAPSA		typedef ptr WAVEINCAPSA
WAVEINCAPSW		STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
vDriverVersion		MMVERSION ?	;; version of the driver
szPname			dw MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
dwFormats		dd ?	;; formats supported
wChannels		dw ?	;; number of channels supported
wReserved1		dw ?	;; structure packing
WAVEINCAPSW		ENDS
PWAVEINCAPSW		typedef ptr WAVEINCAPSW
NPWAVEINCAPSW		typedef ptr WAVEINCAPSW
LPWAVEINCAPSW		typedef ptr WAVEINCAPSW
ifdef _UNICODE
WAVEINCAPS		typedef WAVEINCAPSW
PWAVEINCAPS		typedef PWAVEINCAPSW
NPWAVEINCAPS		typedef NPWAVEINCAPSW
LPWAVEINCAPS		typedef LPWAVEINCAPSW
else
WAVEINCAPS		typedef WAVEINCAPSA
PWAVEINCAPS		typedef PWAVEINCAPSA
NPWAVEINCAPS		typedef NPWAVEINCAPSA
LPWAVEINCAPS		typedef LPWAVEINCAPSA
endif ;; UNICODE

else
WAVEINCAPS		STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
vDriverVersion		VERSION ?	;; version of the driver
szPname			db MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
dwFormats		dd ?	;; formats supported
wChannels		dw ?	;; number of channels supported
WAVEINCAPS		ENDS
PWAVEINCAPS		typedef ptr WAVEINCAPS
NPWAVEINCAPS		typedef ptr WAVEINCAPS
LPWAVEINCAPS		typedef ptr WAVEINCAPS
endif

;; defines for dwFormat field of WAVEINCAPS and WAVEOUTCAPS
WAVE_INVALIDFORMAT	equ 0x00000000	     ;; invalid format
WAVE_FORMAT_1M08	equ 0x00000001	     ;; 11.025 kHz, Mono,   8-bit
WAVE_FORMAT_1S08	equ 0x00000002	     ;; 11.025 kHz, Stereo, 8-bit
WAVE_FORMAT_1M16	equ 0x00000004	     ;; 11.025 kHz, Mono,   16-bit
WAVE_FORMAT_1S16	equ 0x00000008	     ;; 11.025 kHz, Stereo, 16-bit
WAVE_FORMAT_2M08	equ 0x00000010	     ;; 22.05  kHz, Mono,   8-bit
WAVE_FORMAT_2S08	equ 0x00000020	     ;; 22.05  kHz, Stereo, 8-bit
WAVE_FORMAT_2M16	equ 0x00000040	     ;; 22.05  kHz, Mono,   16-bit
WAVE_FORMAT_2S16	equ 0x00000080	     ;; 22.05  kHz, Stereo, 16-bit
WAVE_FORMAT_4M08	equ 0x00000100	     ;; 44.1   kHz, Mono,   8-bit
WAVE_FORMAT_4S08	equ 0x00000200	     ;; 44.1   kHz, Stereo, 8-bit
WAVE_FORMAT_4M16	equ 0x00000400	     ;; 44.1   kHz, Mono,   16-bit
WAVE_FORMAT_4S16	equ 0x00000800	     ;; 44.1   kHz, Stereo, 16-bit

;; OLD general waveform format structure (information common to all formats)
WAVEFORMAT		STRUC
wFormatTag		dw ?	;; format type
nChannels		dw ?	;; number of channels (i.e. mono, stereo, etc.)
nSamplesPerSec		dd ?	;; sample rate
nAvgBytesPerSec		dd ?	;; for buffer estimation
nBlockAlign		dw ?	;; block size of data
WAVEFORMAT		ENDS
PWAVEFORMAT		typedef ptr WAVEFORMAT
NPWAVEFORMAT		typedef ptr WAVEFORMAT
LPWAVEFORMAT		typedef ptr WAVEFORMAT

;; flags for wFormatTag field of WAVEFORMAT
WAVE_FORMAT_PCM		equ 1

;; specific waveform format structure for PCM data
PCMWAVEFORMAT		STRUC
wf			WAVEFORMAT <>
wBitsPerSample		dw ?
PCMWAVEFORMAT		ENDS
PPCMWAVEFORMAT		typedef ptr PCMWAVEFORMAT
NPPCMWAVEFORMAT		typedef ptr PCMWAVEFORMAT
LPPCMWAVEFORMAT		typedef ptr PCMWAVEFORMAT

ifndef _WAVEFORMATEX_
_WAVEFORMATEX_ equ 1

;;
;;  extended waveform format structure used for all non-PCM formats. this
;;  structure is common to all non-PCM formats.
;;
WAVEFORMATEX		STRUC
wFormatTag		dw ?	;; format type
nChannels		dw ?	;; number of channels (i.e. mono, stereo...)
nSamplesPerSec		dd ?	;; sample rate
nAvgBytesPerSec		dd ?	;; for buffer estimation
nBlockAlign		dw ?	;; block size of data
wBitsPerSample		dw ?	;; number of bits per sample of mono data
cbSize			dw ?	;; the count in bytes of the size of
;; extra information (after cbSize)
WAVEFORMATEX		ENDS
PWAVEFORMATEX		typedef ptr WAVEFORMATEX
NPWAVEFORMATEX		typedef ptr WAVEFORMATEX
LPWAVEFORMATEX		typedef ptr WAVEFORMATEX
LPCWAVEFORMATEX		typedef ptr WAVEFORMATEX

endif ;; _WAVEFORMATEX_

ifndef _WIN32_VXD
;; waveform audio function prototypes
;UINT
waveOutGetNumDevs proto _CType

ifdef _WIN32

;MMRESULT
waveOutGetDevCapsA proto _CType \
	     uDeviceID: UINT,
		  pwoc: LPWAVEOUTCAPSA,
		 cbwoc: UINT
waveOutGetDevCapsW proto _CType \
	     uDeviceID: UINT,
		  pwoc: LPWAVEOUTCAPSW,
		 cbwoc: UINT
ifdef _UNICODE
waveOutGetDevCaps	equ <waveOutGetDevCapsW>
else
waveOutGetDevCaps	equ <waveOutGetDevCapsA>
endif ;; NOT UNICODE

else
;RESULT
waveOutGetDevCaps proto _CType \
	     uDeviceID: UINT,
		  pwoc: LPWAVEOUTCAPS,
		 cbwoc: UINT
endif

if (WINVER GE 0x0400)
;RESULT
waveOutGetVolume proto _CType \
		   hwo: HWAVEOUT,
	     pdwVolume: LPDWORD
waveOutSetVolume proto _CType \
		   hwo: HWAVEOUT,
	      dwVolume: DWORD
else
waveOutGetVolume proto _CType \
		   uId: UINT,
	     pdwVolume: LPDWORD
waveOutSetVolume proto _CType \
		   uId: UINT,
	      dwVolume: DWORD
endif

ifdef _WIN32

;RESULT
waveOutGetErrorTextA proto _CType \
	      mmrError: MMRESULT,
	       pszText: LPSTR,
	       cchText: UINT
;RESULT
waveOutGetErrorTextW proto _CType \
	      mmrError: MMRESULT,
	       pszText: LPWSTR,
	       cchText: UINT
ifdef _UNICODE
waveOutGetErrorText	equ <waveOutGetErrorTextW>
else
waveOutGetErrorText	equ <waveOutGetErrorTextA>
endif ;; NOT UNICODE

else
;MMRESULT
waveOutGetErrorText proto _CType \
	      mmrError: MMRESULT,
	       pszText: LPWSTR,
	       cchText: UINT
endif

;RESULT
waveOutOpen proto _CType \
		  phwo: LPHWAVEOUT,
	     uDeviceID: UINT,
		  pwfx: LPCWAVEFORMATEX,
	    dwCallback: DWORD,
	    dwInstance: DWORD,
	       fdwOpen: DWORD

;RESULT
waveOutClose proto _CType \
		   hwo: HWAVEOUT
;RESULT
waveOutPrepareHeader proto _CType \
		   hwo: HWAVEOUT,
		   pwh: LPWAVEHDR,
		  cbwh: UINT
;RESULT
waveOutUnprepareHeader proto _CType \
		   hwo: HWAVEOUT,
		   pwh: LPWAVEHDR,
		  cbwh: UINT
;RESULT
waveOutWrite proto _CType \
		   hwo: HWAVEOUT,
		   pwh: LPWAVEHDR,
		  cbwh: UINT
;RESULT
waveOutPause proto _CType \
		   hwo: HWAVEOUT
;RESULT
waveOutRestart proto _CType \
		   hwo: HWAVEOUT
;RESULT
waveOutReset proto _CType \
		   hwo: HWAVEOUT
;RESULT
waveOutBreakLoop proto _CType \
		   hwo: HWAVEOUT
;RESULT
waveOutGetPosition proto _CType \
		   hwo: HWAVEOUT,
		  pmmt: LPMMTIME,
		 cbmmt: UINT
;RESULT
waveOutGetPitch proto _CType \
		   hwo: HWAVEOUT,
	      pdwPitch: LPDWORD
;RESULT
waveOutSetPitch proto _CType \
		   hwo: HWAVEOUT,
	       dwPitch: DWORD
;RESULT
waveOutGetPlaybackRate proto _CType \
		   hwo: HWAVEOUT,
	       pdwRate: LPDWORD
;RESULT
waveOutSetPlaybackRate proto _CType \
		   hwo: HWAVEOUT,
		dwRate: DWORD
;RESULT
waveOutGetID proto _CType \
		   hwo: HWAVEOUT,
	    puDeviceID: LPUINT

if (WINVER GE 0x030a)
ifdef _WIN32
;MRESULT
waveOutMessage proto _CType \
		   hwo: HWAVEOUT,
		  uMsg: UINT,
		   dw1: DWORD,
		   dw2: DWORD
else
;DWORD
waveOutMessage proto _CType \
		   hwo: HWAVEOUT,
		  uMsg: UINT,
		   dw1: DWORD,
		   dw2: DWORD
endif
endif ;; ifdef WINVER GE 0x030a

;UINT
waveInGetNumDevs proto _CType

ifdef _WIN32

;RESULT
waveInGetDevCapsA proto _CType \
	     uDeviceID: UINT,
		  pwic: LPWAVEINCAPSA,
		 cbwic: UINT
;RESULT
waveInGetDevCapsW proto _CType \
	     uDeviceID: UINT,
		  pwic: LPWAVEINCAPSW,
		 cbwic: UINT
ifdef _UNICODE
waveInGetDevCaps	equ <waveInGetDevCapsW>
else
waveInGetDevCaps	equ <waveInGetDevCapsA>
endif ;; NOT UNICODE

else
waveInGetDevCaps proto _CType \
	     uDeviceID: UINT,
		  pwic: LPWAVEINCAPS,
		 cbwic: UINT
endif

ifdef _WIN32

;RESULT
waveInGetErrorTextA proto _CType \
	      mmrError: MMRESULT,
	       pszText: LPSTR,
	       cchText: UINT
;RESULT
waveInGetErrorTextW proto _CType \
	      mmrError: MMRESULT,
	       pszText: LPWSTR,
	       cchText: UINT
ifdef _UNICODE
waveInGetErrorText	equ <waveInGetErrorTextW>
else
waveInGetErrorText	equ <waveInGetErrorTextA>
endif ;; NOT UNICODE

else
waveInGetErrorText proto _CType \
	      mmrError: MMRESULT,
	       pszText: LPSTR,
	       cchText: UINT
endif

;RESULT
waveInOpen proto _CType \
		  phwi: LPHWAVEIN,
	     uDeviceID: UINT,
		  pwfx: LPCWAVEFORMATEX,
	    dwCallback: DWORD,
	    dwInstance: DWORD,
	       fdwOpen: DWORD

;RESULT
waveInClose proto _CType \
		   hwi: HWAVEIN
;RESULT
waveInPrepareHeader proto _CType \
		   hwi: HWAVEIN,
		   pwh: LPWAVEHDR,
		  cbwh: UINT
;RESULT
waveInUnprepareHeader proto _CType \
		   hwi: HWAVEIN,
		   pwh: LPWAVEHDR,
		  cbwh: UINT
;RESULT
waveInAddBuffer proto _CType \
		   hwi: HWAVEIN,
		   pwh: LPWAVEHDR,
		  cbwh: UINT
;RESULT
waveInStart proto _CType \
		   hwi: HWAVEIN
;RESULT
waveInStop proto _CType \
		   hwi: HWAVEIN
;RESULT
waveInReset proto _CType \
		   hwi: HWAVEIN
;RESULT
waveInGetPosition proto _CType \
		   hwi: HWAVEIN,
		  pmmt: LPMMTIME,
		 cbmmt: UINT
;RESULT
waveInGetID proto _CType \
		   hwi: HWAVEIN,
	    puDeviceID: LPUINT

if (WINVER GE 0x030a)
ifdef _WIN32
;RESULT
waveInMessage proto _CType \
		   hwi: HWAVEIN,
		  uMsg: UINT,
		   dw1: DWORD,
		   dw2: DWORD
else
;DWORD
waveInMessage proto _CType \
		   hwi: HWAVEIN,
		  uMsg: UINT,
		   dw1: DWORD,
		   dw2: DWORD
endif
endif ;; ifdef WINVER GE 0x030a
endif ;; ifndef _WIN32_VXD
endif  ;; ifndef MMNOWAVE

ifndef MMNOMIDI
;;**************************************************************************
;;
;; MIDI audio support
;;
;;**************************************************************************

;; MIDI error return values
MIDIERR_UNPREPARED	equ (MIDIERR_BASE + 0)	 ;; header not prepared
MIDIERR_STILLPLAYING	equ (MIDIERR_BASE + 1)	 ;; still something playing
MIDIERR_NOMAP		equ (MIDIERR_BASE + 2)	 ;; no configured instruments
MIDIERR_NOTREADY	equ (MIDIERR_BASE + 3)	 ;; hardware is still busy
MIDIERR_NODEVICE	equ (MIDIERR_BASE + 4)	 ;; port no longer connected
MIDIERR_INVALIDSETUP	equ (MIDIERR_BASE + 5)	 ;; invalid MIF
MIDIERR_BADOPENMODE	equ (MIDIERR_BASE + 6)	 ;; operation unsupported w/ open mode
MIDIERR_DONT_CONTINUE	equ (MIDIERR_BASE + 7)	 ;; thru device 'eating' a message
MIDIERR_LASTERROR	equ (MIDIERR_BASE + 7)	 ;; last error in range

;; MIDI audio data types
HMIDI			typedef HANDLE
HMIDIIN			typedef HANDLE
HMIDIOUT		typedef HANDLE
HMIDISTRM		typedef HANDLE
ifndef _WIN32_VXD
LPHMIDI			typedef ptr HMIDI
LPHMIDIIN		typedef ptr HMIDIIN
LPHMIDIOUT		typedef ptr HMIDIOUT
LPHMIDISTRM		typedef ptr HMIDISTRM
MIDICALLBACK		typedef DRVCALLBACK
LPMIDICALLBACK		typedef ptr MIDICALLBACK
MIDIPATCHSIZE		equ 128
PATCHARRAY		typedef ptr ;WORD [MIDIPATCHSIZE]
LPPATCHARRAY		typedef ptr WORD
;KEYARRAY		typedef [MIDIPATCHSIZE]:WORD
LPKEYARRAY		typedef ptr WORD
endif  ;; ifndef _WIN32_VXD

;; MIDI callback messages
MIM_OPEN		equ MM_MIM_OPEN
MIM_CLOSE		equ MM_MIM_COSE
MIM_DATA		equ MM_MIM_DATA
MIM_LONGDATA		equ MM_MIM_LONGDATA
MIM_ERROR		equ MM_MIM_ERROR
MIM_LONGERROR		equ MM_MIM_LONGERROR
MOM_OPEN		equ MM_MOM_OPEN
MOM_CLOSE		equ MM_MOM_COSE
MOM_DONE		equ MM_MOM_DONE

if(WINVER GE 0x0400)
MIM_MOREDATA		equ MM_MIM_MOREDATA
MOM_POSITIONCB		equ MM_MOM_POSITIONCB
endif ;; WINVER GE 0x0400

;; device ID for MIDI mapper
MIDIMAPPER		equ -1
MIDI_MAPPER		equ -1

if(WINVER GE 0x0400)
;; flags for dwFlags parm of midiInOpen()
MIDI_IO_STATUS		equ 0x00000020
endif ;; WINVER GE 0x0400

;; flags for wFlags parm of midiOutCachePatches(), midiOutCacheDrumPatches()
MIDI_CACHE_ALL		equ 1
MIDI_CACHE_BESTFIT	equ 2
MIDI_CACHE_QUERY	equ 3
MIDI_UNCACHE		equ 4

;; MIDI output device capabilities structure
ifdef _WIN32

MIDIOUTCAPSA		STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
vDriverVersion		MMVERSION ?	;; version of the driver
szPname			db MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
wTechnology		dw ?	;; type of device
wVoices			dw ?	;; # of voices (internal synth only)
wNotes			dw ?	;; max # of notes (internal synth only)
wChannelMask		dw ?	;; channels used (internal synth only)
dwSupport		dd ?	;; functionality supported by driver
MIDIOUTCAPSA		ENDS
PMIDIOUTCAPSA		typedef ptr MIDIOUTCAPSA
NPMIDIOUTCAPSA		typedef ptr MIDIOUTCAPSA
LPMIDIOUTCAPSA		typedef ptr MIDIOUTCAPSA
MIDIOUTCAPSW		STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
vDriverVersion		MMVERSION ?	;; version of the driver
szPname			dw MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
wTechnology		dw ?	;; type of device
wVoices			dw ?	;; # of voices (internal synth only)
wNotes			dw ?	;; max # of notes (internal synth only)
wChannelMask		dw ?	;; channels used (internal synth only)
dwSupport		dd ?	;; functionality supported by driver
MIDIOUTCAPSW		ENDS
PMIDIOUTCAPSW		typedef ptr MIDIOUTCAPSW
NPMIDIOUTCAPSW		typedef ptr MIDIOUTCAPSW
LPMIDIOUTCAPSW		typedef ptr MIDIOUTCAPSW
ifdef _UNICODE
MIDIOUTCAPS		typedef MIDIOUTCAPSW
PMIDIOUTCAPS		typedef PMIDIOUTCAPSW
NPMIDIOUTCAPS		typedef NPMIDIOUTCAPSW
LPMIDIOUTCAPS		typedef LPMIDIOUTCAPSW
else
MIDIOUTCAPS		typedef MIDIOUTCAPSA
PMIDIOUTCAPS		typedef PMIDIOUTCAPSA
NPMIDIOUTCAPS		typedef NPMIDIOUTCAPSA
LPMIDIOUTCAPS		typedef LPMIDIOUTCAPSA
endif ;; UNICODE

else
MIDIOUTCAPS		STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
vDriverVersion		VERSION ?	;; version of the driver
szPname			db MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
wTechnology		dw ?	;; type of device
wVoices			dw ?	;; # of voices (internal synth only)
wNotes			dw ?	;; max # of notes (internal synth only)
wChannelMask		dw ?	;; channels used (internal synth only)
dwSupport		dd ?	;; functionality supported by driver
MIDIOUTCAPS		ENDS
PMIDIOUTCAPS		typedef ptr MIDIOUTCAPS
NPMIDIOUTCAPS		typedef ptr MIDIOUTCAPS
LPMIDIOUTCAPS		typedef ptr MIDIOUTCAPS
endif

;; flags for wTechnology field of MIDIOUTCAPS structure
MOD_MIDIPORT		equ 1  ;; output port
MOD_SYNTH		equ 2  ;; generic internal synth
MOD_SQSYNTH		equ 3  ;; square wave internal synth
MOD_FMSYNTH		equ 4  ;; FM internal synth
MOD_MAPPER		equ 5  ;; MIDI mapper

;; flags for dwSupport field of MIDIOUTCAPS structure
MIDICAPS_VOLUME		equ 0x0001  ;; supports volume control
MIDICAPS_LRVOLUME	equ 0x0002  ;; separate left-right volume control
MIDICAPS_CACHE		equ 0x0004
if(WINVER GE 0x0400)
MIDICAPS_STREAM		equ 0x0008  ;; driver supports midiStreamOut directly
endif ;; WINVER GE 0x0400

;; MIDI input device capabilities structure
ifdef _WIN32

MIDIINCAPSA		STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
vDriverVersion		MMVERSION ?	;; version of the driver
szPname			db MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
if (WINVER GE 0x0400)
dwSupport		dd ?	;; functionality supported by driver
endif
MIDIINCAPSA		ENDS
PMIDIINCAPSA		typedef ptr MIDIINCAPSA
NPMIDIINCAPSA		typedef ptr MIDIINCAPSA
LPMIDIINCAPSA		typedef ptr MIDIINCAPSA
MIDIINCAPSW		STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
vDriverVersion		MMVERSION ?	;; version of the driver
szPname			dw MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
if (WINVER GE 0x0400)
dwSupport		dd ?	;; functionality supported by driver
endif
MIDIINCAPSW		ENDS
PMIDIINCAPSW		typedef ptr MIDIINCAPSW
NPMIDIINCAPSW		typedef ptr MIDIINCAPSW
LPMIDIINCAPSW		typedef ptr MIDIINCAPSW
ifdef _UNICODE
MIDIINCAPS		typedef MIDIINCAPSW
PMIDIINCAPS		typedef PMIDIINCAPSW
NPMIDIINCAPS		typedef NPMIDIINCAPSW
LPMIDIINCAPS		typedef LPMIDIINCAPSW
else
MIDIINCAPS		typedef MIDIINCAPSA
PMIDIINCAPS		typedef PMIDIINCAPSA
NPMIDIINCAPS		typedef NPMIDIINCAPSA
LPMIDIINCAPS		typedef LPMIDIINCAPSA
endif ;; UNICODE

else
MIDIINCAPS		STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
vDriverVersion		VERSION ?	;; version of the driver
szPname			db MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
if (WINVER GE 0x0400)
dwSupport		dd ?	;; functionality supported by driver
endif
MIDIINCAPS		ENDS
PMIDIINCAPS		typedef ptr MIDIINCAPS
NPMIDIINCAPS		typedef ptr MIDIINCAPS
LPMIDIINCAPS		typedef ptr MIDIINCAPS
endif

;; MIDI data block header
MIDIHDR			STRUC
lpData			LPSTR ? ;; pointer to locked data block
dwBufferLength		dd ?	;; length of data in data block
dwBytesRecorded		dd ?	;; used for input only
dwUser			dd ?	;; for client's use
dwFlags			dd ?	;; assorted flags (see defines)
lpNext			PVOID ? ;; reserved for driver
reserved		dd ?	;; reserved for driver
if (WINVER GE 0x0400)
dwOffset		dd ?	;; Callback offset into buffer
dwReserved		dd 8 dup(?)	;; Reserved for MMSYSTEM
endif
MIDIHDR			ENDS
PMIDIHDR		typedef ptr MIDIHDR
NPMIDIHDR		typedef ptr MIDIHDR
LPMIDIHDR		typedef ptr MIDIHDR

if(WINVER GE 0x0400)
MIDIEVENT		STRUC
dwDeltaTime		dd ?	;; Ticks since last event
dwStreamID		dd ?	;; Reserved; must be zero
dwEvent			dd ?	;; Event type and parameters
dwParms			dd ?	;; Parameters if this is a long event
MIDIEVENT		ENDS

MIDISTRMBUFFVER		STRUC
dwVersion		dd ?	;; Stream buffer format version
dwMid			dd ?	;; Manufacturer ID as defined in MMREG.H
dwOEMVersion		dd ?	;; Manufacturer version for custom ext
MIDISTRMBUFFVER		ENDS
endif ;; WINVER GE 0x0400

;; flags for dwFlags field of MIDIHDR structure
MHDR_DONE		equ 0x00000001	     ;; done bit
MHDR_PREPARED		equ 0x00000002	     ;; set if header prepared
MHDR_INQUEUE		equ 0x00000004	     ;; reserved for driver
MHDR_ISSTRM		equ 0x00000008	     ;; Buffer is stream buffer

if(WINVER GE 0x0400)
;;
;; Type codes which go in the high byte of the event DWORD of a stream buffer
;;
;; Type codes 00-7F contain parameters within the low 24 bits
;; Type codes 80-FF contain a length of their parameter in the low 24
;; bits, followed by their parameter data in the buffer. The event
;; DWORD contains the exact byte length; the parm data itself must be
;; padded to be an even multiple of 4 bytes long.
;;

MEVT_F_SHORT		equ 0x00000000
MEVT_F_LONG		equ 0x80000000
MEVT_F_CALLBACK		equ 0x40000000

MEVT_EVENTTYPE macro x
	exitm<((((x) SHR 24) AND 0xFF))>
	endm
MEVT_EVENTPARM macro x
	exitm<(((x) AND 0x00FFFFFF))>
	endm

MEVT_SHORTMSG		equ (0x00)    ;; parm = shortmsg for midiOutShortMsg
MEVT_TEMPO		equ (0x01)    ;; parm = new tempo in microsec/qn
MEVT_NOP		equ (0x02)    ;; parm = unused; does nothing

;; 0x04-0x7F reserved

MEVT_LONGMSG		equ (0x80)    ;; parm = bytes to send verbatim
MEVT_COMMENT		equ (0x82)    ;; parm = comment data
MEVT_VERSION		equ (0x84)    ;; parm = MIDISTRMBUFFVER struct

;; 0x81-0xFF reserved

MIDISTRM_ERROR		equ (-2)

;;
;; Structures and defines for midiStreamProperty
;;
MIDIPROP_SET		equ 0x80000000
MIDIPROP_GET		equ 0x40000000

;; These are intentionally both non-zero so the app cannot accidentally
;; leave the operation off and happen to appear to work due to default
;; action.

MIDIPROP_TIMEDIV	equ 0x00000001
MIDIPROP_TEMPO		equ 0x00000002

MIDIPROPTIMEDIV		STRUC
cbStruct		dd ?
dwTimeDiv		dd ?
MIDIPROPTIMEDIV		ENDS
LPMIDIPROPTIMEDIV	typedef ptr MIDIPROPTIMEDIV

MIDIPROPTEMPO		STRUC
cbStruct		dd ?
dwTempo			dd ?
MIDIPROPTEMPO		ENDS
LPMIDIPROPTEMPO		typedef ptr MIDIPROPTEMPO

endif ;; WINVER GE 0x0400

ifndef _WIN32_VXD

;; MIDI function prototypes
midiOutGetNumDevs proto _CType
if(WINVER GE 0x0400)
;RESULT
midiStreamOpen proto _CType \
		  phms: LPHMIDISTRM,
	    puDeviceID: LPUINT,
		 cMidi: DWORD,
	    dwCallback: DWORD,
	    dwInstance: DWORD,
	       fdwOpen: DWORD
;RESULT
midiStreamClose proto _CType \
		   hms: HMIDISTRM

;RESULT
midiStreamProperty proto _CType \
		   hms: HMIDISTRM,
	    lppropdata: LPBYTE,
	    dwProperty: DWORD
;RESULT
midiStreamPosition proto _CType \
		   hms: HMIDISTRM,
		 lpmmt: LPMMTIME,
		 cbmmt: UINT

;RESULT
midiStreamOut proto _CType \
		   hms: HMIDISTRM,
		   pmh: LPMIDIHDR,
		  cbmh: UINT
;RESULT
midiStreamPause proto _CType \
		   hms: HMIDISTRM
;RESULT
midiStreamRestart proto _CType \
		   hms: HMIDISTRM
;RESULT
midiStreamStop proto _CType \
		   hms: HMIDISTRM

ifdef _WIN32
;RESULT
midiConnect proto _CType \
		   hmi: HMIDI,
		   hmo: HMIDIOUT,
	     pReserved: LPVOID
;RESULT
midiDisconnect proto _CType \
		   hmi: HMIDI,
		   hmo: HMIDIOUT,
	     pReserved: LPVOID

endif
endif ;; WINVER GE 0x0400

ifdef _WIN32

;RESULT
midiOutGetDevCapsA proto _CType \
	     uDeviceID: UINT,
		  pmoc: LPMIDIOUTCAPSA,
		 cbmoc: UINT
;RESULT
midiOutGetDevCapsW proto _CType \
	     uDeviceID: UINT,
		  pmoc: LPMIDIOUTCAPSW,
		 cbmoc: UINT
ifdef _UNICODE
midiOutGetDevCaps	equ <midiOutGetDevCapsW>
else
midiOutGetDevCaps	equ <midiOutGetDevCapsA>
endif ;; NOT UNICODE

else
midiOutGetDevCaps proto _CType \
	     uDeviceID: UINT,
		  pmoc: LPMIDIOUTCAPS,
		 cbmoc: UINT
endif

if (WINVER GE 0x0400)
;RESULT
midiOutGetVolume proto _CType \
		   hmo: HMIDIOUT,
	     pdwVolume: LPDWORD
;RESULT
midiOutSetVolume proto _CType \
		   hmo: HMIDIOUT,
	      dwVolume: DWORD
else
;RESULT
midiOutGetVolume proto _CType \
		   uId: UINT,
	     pdwVolume: LPDWORD
;RESULT
midiOutSetVolume proto _CType \
		   uId: UINT,
	      dwVolume: DWORD
endif

ifdef _WIN32

;RESULT
midiOutGetErrorTextA proto _CType \
	      mmrError: MMRESULT,
	       pszText: LPSTR,
	       cchText: UINT
;RESULT
midiOutGetErrorTextW proto _CType \
	      mmrError: MMRESULT,
	       pszText: LPWSTR,
	       cchText: UINT
ifdef _UNICODE
midiOutGetErrorText	equ <midiOutGetErrorTextW>
else
midiOutGetErrorText	equ <midiOutGetErrorTextA>
endif ;; NOT UNICODE

else
;RESULT
midiOutGetErrorText proto _CType \
	      mmrError: MMRESULT,
	       pszText: LPSTR,
	       cchText: UINT
endif

;RESULT
midiOutOpen proto _CType \
		  phmo: LPHMIDIOUT,
	     uDeviceID: UINT,
	    dwCallback: DWORD,
	    dwInstance: DWORD,
	       fdwOpen: DWORD
;RESULT
midiOutClose proto _CType \
		   hmo: HMIDIOUT
;RESULT
midiOutPrepareHeader proto _CType \
		   hmo: HMIDIOUT,
		   pmh: LPMIDIHDR,
		  cbmh: UINT
;RESULT
midiOutUnprepareHeader proto _CType \
		   hmo: HMIDIOUT,
		   pmh: LPMIDIHDR,
		  cbmh: UINT
;RESULT
midiOutShortMsg proto _CType \
		   hmo: HMIDIOUT,
		 dwMsg: DWORD
;RESULT
midiOutLongMsg proto _CType \
		   hmo: HMIDIOUT,
		   pmh: LPMIDIHDR,
		  cbmh: UINT
;RESULT
midiOutReset proto _CType \
		   hmo: HMIDIOUT
;RESULT
midiOutCachePatches proto _CType \
		   hmo: HMIDIOUT,
		 uBank: UINT,
		  pwpa: LPWORD,
	       fuCache: UINT
;RESULT
midiOutCacheDrumPatches proto _CType \
		   hmo: HMIDIOUT,
		uPatch: UINT,
		 pwkya: LPWORD,
	       fuCache: UINT
;RESULT
midiOutGetID proto _CType \
		   hmo: HMIDIOUT,
	    puDeviceID: LPUINT

if (WINVER GE 0x030a)
ifdef _WIN32
;RESULT
midiOutMessage proto _CType \
		   hmo: HMIDIOUT,
		  uMsg: UINT,
		   dw1: DWORD,
		   dw2: DWORD
else
;DWORD
midiOutMessage proto _CType \
		   hmo: HMIDIOUT,
		  uMsg: UINT,
		   dw1: DWORD,
		   dw2: DWORD
endif
endif ;; ifdef WINVER GE 0x030a

midiInGetNumDevs proto _CType

ifdef _WIN32
;RESULT
midiInGetDevCapsA proto _CType \
	     uDeviceID: UINT,
		  pmic: LPMIDIINCAPSA,
		 cbmic: UINT
;RESULT
midiInGetDevCapsW proto _CType \
	     uDeviceID: UINT,
		  pmic: LPMIDIINCAPSW,
		 cbmic: UINT
ifdef _UNICODE
midiInGetDevCaps	equ <midiInGetDevCapsW>
else
midiInGetDevCaps	equ <midiInGetDevCapsA>
endif ;; NOT UNICODE
;RESULT
midiInGetErrorTextA proto _CType \
	      mmrError: MMRESULT,
	       pszText: LPSTR,
	       cchText: UINT
;RESULT
midiInGetErrorTextW proto _CType \
	      mmrError: MMRESULT,
	       pszText: LPWSTR,
	       cchText: UINT
ifdef _UNICODE
midiInGetErrorText	equ <midiInGetErrorTextW>
else
midiInGetErrorText	equ <midiInGetErrorTextA>
endif ;; NOT UNICODE

else
midiInGetDevCaps proto _CType \
	     uDeviceID: UINT,
		  pmic: LPMIDIINCAPS,
		 cbmic: UINT
;RESULT
midiInGetErrorText proto _CType \
	      mmrError: MMRESULT,
	       pszText: LPSTR,
	       cchText: UINT
endif

;RESULT
midiInOpen proto _CType \
		  phmi: LPHMIDIIN,
	     uDeviceID: UINT,
	    dwCallback: DWORD,
	    dwInstance: DWORD,
	       fdwOpen: DWORD
;RESULT
midiInClose proto _CType \
		   hmi: HMIDIIN
;RESULT
midiInPrepareHeader proto _CType \
		   hmi: HMIDIIN,
		   pmh: LPMIDIHDR,
		  cbmh: UINT
;RESULT
midiInUnprepareHeader proto _CType \
		   hmi: HMIDIIN,
		   pmh: LPMIDIHDR,
		  cbmh: UINT
;RESULT
midiInAddBuffer proto _CType \
		   hmi: HMIDIIN,
		   pmh: LPMIDIHDR,
		  cbmh: UINT
;RESULT
midiInStart proto _CType \
		   hmi: HMIDIIN
;RESULT
midiInStop proto _CType \
		   hmi: HMIDIIN
;RESULT
midiInReset proto _CType \
		   hmi: HMIDIIN
;RESULT
midiInGetID proto _CType \
		   hmi: HMIDIIN,
	    puDeviceID: LPUINT

if (WINVER GE 0x030a)
ifdef _WIN32
;RESULT
midiInMessage proto _CType \
		   hmi: HMIDIIN,
		  uMsg: UINT,
		   dw1: DWORD,
		   dw2: DWORD
else
;DWORD
midiInMessage proto _CType \
		   hmi: HMIDIIN,
		  uMsg: UINT,
		   dw1: DWORD,
		   dw2: DWORD
endif
endif ;; ifdef WINVER GE 0x030a

endif ;; ifndef _WIN32_VXD

endif  ;; ifndef MMNOMIDI

ifndef MMNOAUX
;;**************************************************************************
;;
;; Auxiliary audio support
;;
;;**************************************************************************

;; device ID for aux device mapper
AUX_MAPPER		equ -1

;; Auxiliary audio device capabilities structure
ifdef _WIN32

AUXCAPSA		STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
vDriverVersion		MMVERSION ?	;; version of the driver
szPname			db MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
wTechnology		dw ?	;; type of device
wReserved1		dw ?	;; padding
dwSupport		dd ?	;; functionality supported by driver
AUXCAPSA		ENDS
PAUXCAPSA		typedef ptr AUXCAPSA
NPAUXCAPSA		typedef ptr AUXCAPSA
LPAUXCAPSA		typedef ptr AUXCAPSA
AUXCAPSW		STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
vDriverVersion		MMVERSION ?	;; version of the driver
szPname			dw MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
wTechnology		dw ?	;; type of device
wReserved1		dw ?	;; padding
dwSupport		dd ?	;; functionality supported by driver
AUXCAPSW		ENDS
PAUXCAPSW		typedef ptr AUXCAPSW
NPAUXCAPSW		typedef ptr AUXCAPSW
LPAUXCAPSW		typedef ptr AUXCAPSW
ifdef _UNICODE
AUXCAPS			typedef AUXCAPSW
PAUXCAPS		typedef PAUXCAPSW
NPAUXCAPS		typedef NPAUXCAPSW
LPAUXCAPS		typedef LPAUXCAPSW
else
AUXCAPS			typedef AUXCAPSA
PAUXCAPS		typedef PAUXCAPSA
NPAUXCAPS		typedef NPAUXCAPSA
LPAUXCAPS		typedef LPAUXCAPSA
endif ;; UNICODE

else
AUXCAPS			STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
vDriverVersion		VERSION ?	;; version of the driver
szPname			db MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
wTechnology		dw ?	;; type of device
dwSupport		dd ?	;; functionality supported by driver
AUXCAPS			ENDS
PAUXCAPS		typedef ptr AUXCAPS
NPAUXCAPS		typedef ptr AUXCAPS
LPAUXCAPS		typedef ptr AUXCAPS
endif

;; flags for wTechnology field in AUXCAPS structure
AUXCAPS_CDAUDIO		equ 1	    ;; audio from internal CD-ROM drive
AUXCAPS_AUXIN		equ 2	    ;; audio from auxiliary input jacks

;; flags for dwSupport field in AUXCAPS structure
AUXCAPS_VOLUME		equ 0x0001  ;; supports volume control
AUXCAPS_LRVOLUME	equ 0x0002  ;; separate left-right volume control

ifndef _WIN32_VXD

;; auxiliary audio function prototypes
auxGetNumDevs proto _CType
ifdef _WIN32
;RESULT
auxGetDevCapsA proto _CType \
	     uDeviceID: UINT,
		   pac: LPAUXCAPSA,
		  cbac: UINT
;RESULT
auxGetDevCapsW proto _CType \
	     uDeviceID: UINT,
		   pac: LPAUXCAPSW,
		  cbac: UINT
ifdef _UNICODE
auxGetDevCaps		equ <auxGetDevCapsW>
else
auxGetDevCaps		equ <auxGetDevCapsA>
endif ;; NOT UNICODE

else
;MMRESULT
auxGetDevCaps proto _CType \
	     uDeviceID: UINT,
		   pac: LPAUXCAPS,
		  cbac: UINT
endif
;RESULT
auxSetVolume proto _CType \
	     uDeviceID: UINT,
	      dwVolume: DWORD
;RESULT
auxGetVolume proto _CType \
	     uDeviceID: UINT,
	     pdwVolume: LPDWORD


if (WINVER GE 0x030a)
ifdef _WIN32
;RESULT
auxOutMessage proto _CType \
	     uDeviceID: UINT,
		  uMsg: UINT,
		   dw1: DWORD,
		   dw2: DWORD
else
;DWORD
auxOutMessage proto _CType \
	     uDeviceID: UINT,
		  uMsg: UINT,
		   dw1: DWORD,
		   dw2: DWORD
endif
endif ;; ifdef WINVER GE 0x030a

endif ;; ifndef _WIN32_VXD

endif  ;; ifndef MMNOAUX

ifndef MMNOMIXER
ifndef _WIN32_VXD
;;***************************************************************************
;;
;; Mixer Support
;;
;;**************************************************************************

HMIXEROBJ		typedef HANDLE
LPHMIXEROBJ		typedef ptr HMIXEROBJ

HMIXER			typedef HANDLE
LPHMIXER		typedef ptr HMIXER

MIXER_SHORT_NAME_CHARS	equ 16
MIXER_LONG_NAME_CHARS	equ 64

;;
;;  MMRESULT error return values specific to the mixer API
;;
;;
MIXERR_INVALLINE	equ (MIXERR_BASE + 0)
MIXERR_INVALCONTROL	equ (MIXERR_BASE + 1)
MIXERR_INVALVALUE	equ (MIXERR_BASE + 2)
MIXERR_LASTERROR	equ (MIXERR_BASE + 2)

MIXER_OBJECTF_HANDLE	equ 0x80000000
MIXER_OBJECTF_MIXER	equ 0x00000000
MIXER_OBJECTF_HMIXER	equ (MIXER_OBJECTF_HANDE OR MIXER_OBJECTF_MIXER)
MIXER_OBJECTF_WAVEOUT	equ 0x10000000
MIXER_OBJECTF_HWAVEOUT	equ (MIXER_OBJECTF_HANDE OR MIXER_OBJECTF_WAVEOUT)
MIXER_OBJECTF_WAVEIN	equ 0x20000000
MIXER_OBJECTF_HWAVEIN	equ (MIXER_OBJECTF_HANDE OR MIXER_OBJECTF_WAVEIN)
MIXER_OBJECTF_MIDIOUT	equ 0x30000000
MIXER_OBJECTF_HMIDIOUT	equ (MIXER_OBJECTF_HANDE OR MIXER_OBJECTF_MIDIOUT)
MIXER_OBJECTF_MIDIIN	equ 0x40000000
MIXER_OBJECTF_HMIDIIN	equ (MIXER_OBJECTF_HANDE OR MIXER_OBJECTF_MIDIIN)
MIXER_OBJECTF_AUX	equ 0x50000000

mixerGetNumDevs proto _CType

ifdef _WIN32

MIXERCAPSA		STRUC
wMid			dw ?	;; manufacturer id
wPid			dw ?	;; product id
vDriverVersion		MMVERSION ?	;; version of the driver
szPname			db MAXPNAMELEN dup(?) ;; product name
fdwSupport		dd ?	;; misc. support bits
cDestinations		dd ?	;; count of destinations
MIXERCAPSA		ENDS
PMIXERCAPSA		typedef ptr MIXERCAPSA
LPMIXERCAPSA		typedef ptr MIXERCAPSA
MIXERCAPSW		STRUC
wMid			dw ?	;; manufacturer id
wPid			dw ?	;; product id
vDriverVersion		MMVERSION ?	;; version of the driver
szPname			dw MAXPNAMELEN dup(?) ;; product name
fdwSupport		dd ?	;; misc. support bits
cDestinations		dd ?	;; count of destinations
MIXERCAPSW		ENDS
PMIXERCAPSW		typedef ptr MIXERCAPSW
LPMIXERCAPSW		typedef ptr MIXERCAPSW
ifdef _UNICODE
MIXERCAPS		typedef MIXERCAPSW
PMIXERCAPS		typedef PMIXERCAPSW
LPMIXERCAPS		typedef LPMIXERCAPSW
else
MIXERCAPS		typedef MIXERCAPSA
PMIXERCAPS		typedef PMIXERCAPSA
LPMIXERCAPS		typedef LPMIXERCAPSA
endif ;; UNICODE

else
MIXERCAPS		STRUC
wMid			dw ?	;; manufacturer id
wPid			dw ?	;; product id
vDriverVersion		VERSION ?	;; version of the driver
szPname			db MAXPNAMELEN dup(?) ;; product name
fdwSupport		dd ?	;; misc. support bits
cDestinations		dd ?	;; count of destinations
MIXERCAPS		ENDS
PMIXERCAPS		typedef ptr MIXERCAPS
LPMIXERCAPS		typedef ptr MIXERCAPS
endif

ifdef _WIN32

;RESULT
mixerGetDevCapsA proto _CType \
		 uMxId: UINT,
	       pmxcaps: LPMIXERCAPSA,
	      cbmxcaps: UINT
;RESULT
mixerGetDevCapsW proto _CType \
		 uMxId: UINT,
	       pmxcaps: LPMIXERCAPSW,
	      cbmxcaps: UINT
ifdef _UNICODE
mixerGetDevCaps		equ <mixerGetDevCapsW>
else
mixerGetDevCaps		equ <mixerGetDevCapsA>
endif ;; NOT UNICODE

else
mixerGetDevCaps proto _CType \
		 uMxId: UINT,
	       pmxcaps: LPMIXERCAPS,
	      cbmxcaps: UINT
endif

;RESULT
mixerOpen proto _CType \
		  phmx: LPHMIXER,
		 uMxId: UINT,
	    dwCallback: DWORD,
	    dwInstance: DWORD,
	       fdwOpen: DWORD

;RESULT
mixerClose proto _CType \
		   hmx: HMIXER

;ORD
mixerMessage proto _CType \
		   hmx: HMIXER,
		  uMsg: UINT,
	      dwParam1: DWORD,
	      dwParam2: DWORD

ifdef _WIN32

MIXERLINEA		STRUC
cbStruct		dd ?	;; size of MIXERLINE structure
dwDestination		dd ?	;; zero based destination index
dwSource		dd ?	;; zero based source index (if source)
dwLineID		dd ?	;; unique line id for mixer device
fdwLine			dd ?	;; state/information about line
dwUser			dd ?	;; driver specific information
dwComponentType		dd ?	;; component type line connects to
cChannels		dd ?	;; number of channels line supports
cConnections		dd ?	;; number of connections [possible]
cControls		dd ?	;; number of controls at this line
szShortName		db MIXER_SHORT_NAME_CHARS dup(?)
szName			db MIXER_LONG_NAME_CHARS dup(?)

STRUC Target
 dwType			dd ?	;; MIXERLINE_TARGETTYPE_xxxx
 dwDeviceID		dd ?	;; target device ID of device type
 wMid			dw ?	;; of target device
 wPid			dw ?	;;	"
 vDriverVersion		MMVERSION ?
 szPname		db MAXPNAMELEN dup(?)
ENDS
MIXERLINEA		ENDS

PMIXERLINEA		typedef ptr MIXERLINEA
LPMIXERLINEA		typedef ptr MIXERLINEA
MIXERLINEW		STRUC
cbStruct		dd ?	;; size of MIXERLINE structure
dwDestination		dd ?	;; zero based destination index
dwSource		dd ?	;; zero based source index (if source)
dwLineID		dd ?	;; unique line id for mixer device
fdwLine			dd ?	;; state/information about line
dwUser			dd ?	;; driver specific information
dwComponentType		dd ?	;; component type line connects to
cChannels		dd ?	;; number of channels line supports
cConnections		dd ?	;; number of connections [possible]
cControls		dd ?	;; number of controls at this line
szShortName		dw MIXER_SHORT_NAME_CHARS dup(?)
szName			dw MIXER_LONG_NAME_CHARS dup(?)
STRUC Target
dwType			dd ?	;; MIXERLINE_TARGETTYPE_xxxx
dwDeviceID		dd ?	;; target device ID of device type
wMid			dw ?	;; of target device
wPid			dw ?	;;	"
vDriverVersion		MMVERSION ?	;;	"
szPname			dw MAXPNAMELEN dup(?)
ENDS
MIXERLINEW		ENDS
PMIXERLINEW		typedef ptr MIXERLINEW
LPMIXERLINEW		typedef ptr MIXERLINEW
ifdef _UNICODE
MIXERLINE		typedef MIXERLINEW
PMIXERLINE		typedef PMIXERLINEW
LPMIXERLINE		typedef LPMIXERLINEW
else
MIXERLINE		typedef MIXERLINEA
PMIXERLINE		typedef PMIXERLINEA
LPMIXERLINE		typedef LPMIXERLINEA
endif ;; UNICODE

else
MIXERLINE		STRUC
cbStruct		dd ?	;; size of MIXERLINE structure
dwDestination		dd ?	;; zero based destination index
dwSource		dd ?	;; zero based source index (if source)
dwLineID		dd ?	;; unique line id for mixer device
fdwLine			dd ?	;; state/information about line
dwUser			dd ?	;; driver specific information
dwComponentType		dd ?	;; component type line connects to
cChannels		dd ?	;; number of channels line supports
cConnections		dd ?	;; number of connections [possible]
cControls		dd ?	;; number of controls at this line
szShortName		MIXER_SHORT_NAME_CHARS dup(?)
szName			MIXER_LONG_NAME_CHARS dup(?)
STRUC Target
dwType			dd ?	;; MIXERLINE_TARGETTYPE_xxxx
dwDeviceID		dd ?	;; target device ID of device type
wMid			dw ?	;; of target device
wPid			dw ?	;;	"
vDriverVersion		VERSION ?	;;	"
szPname			db MAXPNAMELEN dup(?)
ENDS
MIXERLINE		ENDS
PMIXERLINE		typedef ptr MIXERLINE
LPMIXERLINE		typedef ptr MIXERLINE
endif

;;
;;  MIXERLINE.fdwLine
;;
;;
MIXERLINE_LINEF_ACTIVE	equ 0x00000001
MIXERLINE_LINEF_DISCONNECTED equ 0x00008000
MIXERLINE_LINEF_SOURCE	equ 0x80000000

;;
;;  MIXERLINE.dwComponentType
;;
;;  component types for destinations and sources
;;
;;
MIXERLINE_COMPONENTTYPE_DST_FIRST equ 0x00000000
MIXERLINE_COMPONENTTYPE_DST_UNDEFINED equ (MIXERLINE_COMPONENTTYPE_DST_FIRST + 0)
MIXERLINE_COMPONENTTYPE_DST_DIGITAL equ (MIXERLINE_COMPONENTTYPE_DST_FIRST + 1)
MIXERLINE_COMPONENTTYPE_DST_LINE equ (MIXERLINE_COMPONENTTYPE_DST_FIRST + 2)
MIXERLINE_COMPONENTTYPE_DST_MONITOR equ (MIXERLINE_COMPONENTTYPE_DST_FIRST + 3)
MIXERLINE_COMPONENTTYPE_DST_SPEAKERS equ (MIXERLINE_COMPONENTTYPE_DST_FIRST + 4)
MIXERLINE_COMPONENTTYPE_DST_HEADPHONES equ (MIXERLINE_COMPONENTTYPE_DST_FIRST + 5)
MIXERLINE_COMPONENTTYPE_DST_TELEPHONE equ (MIXERLINE_COMPONENTTYPE_DST_FIRST + 6)
MIXERLINE_COMPONENTTYPE_DST_WAVEIN equ (MIXERLINE_COMPONENTTYPE_DST_FIRST + 7)
MIXERLINE_COMPONENTTYPE_DST_VOICEIN equ (MIXERLINE_COMPONENTTYPE_DST_FIRST + 8)
MIXERLINE_COMPONENTTYPE_DST_LAST equ (MIXERLINE_COMPONENTTYPE_DST_FIRST + 8)

MIXERLINE_COMPONENTTYPE_SRC_FIRST equ 0x00001000
MIXERLINE_COMPONENTTYPE_SRC_UNDEFINED equ (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 0)
MIXERLINE_COMPONENTTYPE_SRC_DIGITAL equ (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 1)
MIXERLINE_COMPONENTTYPE_SRC_LINE equ (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 2)
MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE equ (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 3)
MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER equ (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 4)
MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC equ (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 5)
MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE equ (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 6)
MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER equ (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 7)
MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT equ (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 8)
MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY equ (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 9)
MIXERLINE_COMPONENTTYPE_SRC_ANALOG equ (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 10)
MIXERLINE_COMPONENTTYPE_SRC_LAST equ (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 10)

;;
;;  MIXERLINE.Target.dwType
;;
;;
MIXERLINE_TARGETTYPE_UNDEFINED	equ 0
MIXERLINE_TARGETTYPE_WAVEOUT	equ 1
MIXERLINE_TARGETTYPE_WAVEIN	equ 2
MIXERLINE_TARGETTYPE_MIDIOUT	equ 3
MIXERLINE_TARGETTYPE_MIDIIN	equ 4
MIXERLINE_TARGETTYPE_AUX	equ 5

ifdef _WIN32

;RESULT
mixerGetLineInfoA proto _CType \
		hmxobj: HMIXEROBJ,
		  pmxl: LPMIXERLINEA,
	       fdwInfo: DWORD
;RESULT
mixerGetLineInfoW proto _CType \
		hmxobj: HMIXEROBJ,
		  pmxl: LPMIXERLINEW,
	       fdwInfo: DWORD
ifdef _UNICODE
mixerGetLineInfo	equ <mixerGetLineInfoW>
else
mixerGetLineInfo	equ <mixerGetLineInfoA>
endif ;; NOT UNICODE

else
;MMRESULT
mixerGetLineInfo proto _CType \
		hmxobj: HMIXEROBJ,
		  pmxl: LPMIXERLINE,
	       fdwInfo: DWORD
endif

MIXER_GETLINEINFOF_DESTINATION	equ 0x00000000
MIXER_GETLINEINFOF_SOURCE	equ 0x00000001
MIXER_GETLINEINFOF_LINEID	equ 0x00000002
MIXER_GETLINEINFOF_COMPONENTTYPE equ 0x00000003
MIXER_GETLINEINFOF_TARGETTYPE	equ 0x00000004

MIXER_GETLINEINFOF_QUERYMASK	equ 0x0000000F

;RESULT
mixerGetID proto _CType \
		hmxobj: HMIXEROBJ,
		puMxId: UINT,
		 fdwId: DWORD

;;
;;  MIXERCONTROL
;;
;;
ifdef _WIN32

MIXERCONTROLA		STRUC
cbStruct		dd ?	;; size in bytes of MIXERCONTROL
dwControlID		dd ?	;; unique control id for mixer device
dwControlType		dd ?	;; MIXERCONTROL_CONTROLTYPE_xxx
fdwControl		dd ?	;; MIXERCONTROL_CONTROLF_xxx
cMultipleItems		dd ?	;; if MIXERCONTROL_CONTROLF_MULTIPLE set
szShortName		db MIXER_SHORT_NAME_CHARS dup(?)
szName			db MIXER_LONG_NAME_CHARS dup(?)
UNION Bounds
    STRUC
	lMinimum	LONG ?	;; signed minimum for this control
	lMaximum	LONG ?	;; signed maximum for this control
    ENDS
    STRUC
	dwMinimum	dd ?	;; unsigned minimum for this control
	dwMaximum	dd ?	;; unsigned maximum for this control
    ENDS
dwReserved		dd 6 dup(?)
ENDS
UNION Metrics
    cSteps		dd ?	;; # of steps between min & max
    cbCustomData	dd ?	;; size in bytes of custom data
    dwReserved		dd 6 dup(?)	;; !!! needed? we have cbStruct....
ENDS
MIXERCONTROLA		ENDS
PMIXERCONTROLA		typedef ptr MIXERCONTROLA
LPMIXERCONTROLA		typedef ptr MIXERCONTROLA

MIXERCONTROLW		STRUC
cbStruct		dd ?	;; size in bytes of MIXERCONTROL
dwControlID		dd ?	;; unique control id for mixer device
dwControlType		dd ?	;; MIXERCONTROL_CONTROLTYPE_xxx
fdwControl		dd ?	;; MIXERCONTROL_CONTROLF_xxx
cMultipleItems		dd ?	;; if MIXERCONTROL_CONTROLF_MULTIPLE set
szShortName		dw MIXER_SHORT_NAME_CHARS dup(?)
szName			dw MIXER_LONG_NAME_CHARS dup(?)
UNION Bounds
    STRUC
	lMinimum	LONG ?	;; signed minimum for this control
	lMaximum	LONG ?	;; signed maximum for this control
    ENDS
    STRUC
	dwMinimum	dd ?	;; unsigned minimum for this control
	dwMaximum	dd ?	;; unsigned maximum for this control
    ENDS
    dwReserved		dd 6 dup(?)
ENDS
UNION Metrics
    cSteps		dd ?	;; # of steps between min & max
    cbCustomData	dd ?	;; size in bytes of custom data
    dwReserved		dd 6 dup(?)	;; !!! needed? we have cbStruct....
ENDS
MIXERCONTROLW		ENDS
PMIXERCONTROLW		typedef ptr MIXERCONTROLW
LPMIXERCONTROLW		typedef ptr MIXERCONTROLW
ifdef _UNICODE
MIXERCONTROL		typedef MIXERCONTROLW
PMIXERCONTROL		typedef PMIXERCONTROLW
LPMIXERCONTROL		typedef LPMIXERCONTROLW
else
MIXERCONTROL		typedef MIXERCONTROLA
PMIXERCONTROL		typedef PMIXERCONTROLA
LPMIXERCONTROL		typedef LPMIXERCONTROLA
endif ;; UNICODE

else
tMIXERCONTROL		STRUC
cbStruct		dd ?	;; size in bytes of MIXERCONTROL
dwControlID		dd ?	;; unique control id for mixer device
dwControlType		dd ?	;; MIXERCONTROL_CONTROLTYPE_xxx
fdwControl		dd ?	;; MIXERCONTROL_CONTROLF_xxx
cMultipleItems		dd ?	;; if MIXERCONTROL_CONTROLF_MULTIPLE set
szShortName		db MIXER_SHORT_NAME_CHARS dup(?)
szName			db MIXER_LONG_NAME_CHARS dup(?)
UNION Bounds
    STRUC
	lMinimum	LONG ?	;; signed minimum for this control
	lMaximum	LONG ?	;; signed maximum for this control
    ENDS
    STRUC
	dwMinimum	dd ?	;; unsigned minimum for this control
	dwMaximum	dd ?	;; unsigned maximum for this control
    ENDS
    dwReserved		dd 6 dup(?)
ENDS
UNION Metrics
    cSteps		dd ?	;; # of steps between min & max
    cbCustomData	dd ?	;; size in bytes of custom data
    dwReserved		dd 6 dup(?)	;; !!! needed? we have cbStruct....
ENDS
MIXERCONTROL		ENDS
PMIXERCONTROL		typedef ptr MIXERCONTROL
LPMIXERCONTROL		typedef ptr MIXERCONTROL
endif

;;
;;  MIXERCONTROL.fdwControl
;;
;;
MIXERCONTROL_CONTROLF_UNIFORM equ 0x00000001
MIXERCONTROL_CONTROLF_MULTIPLE equ 0x00000002
MIXERCONTROL_CONTROLF_DISABLED equ 0x80000000

;;
;;  MIXERCONTROL_CONTROLTYPE_xxx building block defines
;;
;;
MIXERCONTROL_CT_CLASS_MASK equ 0xF0000000
MIXERCONTROL_CT_CLASS_CUSTOM equ 0x00000000
MIXERCONTROL_CT_CLASS_METER equ 0x10000000
MIXERCONTROL_CT_CLASS_SWITCH equ 0x20000000
MIXERCONTROL_CT_CLASS_NUMBER equ 0x30000000
MIXERCONTROL_CT_CLASS_SLIDER equ 0x40000000
MIXERCONTROL_CT_CLASS_FADER equ 0x50000000
MIXERCONTROL_CT_CLASS_TIME equ 0x60000000
MIXERCONTROL_CT_CLASS_LIST equ 0x70000000

MIXERCONTROL_CT_SUBCLASS_MASK equ 0x0F000000

MIXERCONTROL_CT_SC_SWITCH_BOOLEAN equ 0x00000000
MIXERCONTROL_CT_SC_SWITCH_BUTTON equ 0x01000000

MIXERCONTROL_CT_SC_METER_POLLED equ 0x00000000

MIXERCONTROL_CT_SC_TIME_MICROSECS equ 0x00000000
MIXERCONTROL_CT_SC_TIME_MILLISECS equ 0x01000000

MIXERCONTROL_CT_SC_LIST_SINGLE equ 0x00000000
MIXERCONTROL_CT_SC_LIST_MULTIPLE equ 0x01000000

MIXERCONTROL_CT_UNITS_MASK equ 0x00FF0000
MIXERCONTROL_CT_UNITS_CUSTOM equ 0x00000000
MIXERCONTROL_CT_UNITS_BOOLEAN equ 0x00010000
MIXERCONTROL_CT_UNITS_SIGNED equ 0x00020000
MIXERCONTROL_CT_UNITS_UNSIGNED equ 0x00030000
MIXERCONTROL_CT_UNITS_DECIBELS equ 0x00040000 ;; in 10ths
MIXERCONTROL_CT_UNITS_PERCENT equ 0x00050000 ;; in 10ths

;;
;;  Commonly used control types for specifying MIXERCONTROL.dwControlType
;;

MIXERCONTROL_CONTROLTYPE_CUSTOM equ (MIXERCONTROL_CT_CLASS_CUSTOM OR MIXERCONTROL_CT_UNITS_CUSTOM)
MIXERCONTROL_CONTROLTYPE_BOOLEANMETER equ (MIXERCONTROL_CT_CLASS_METER OR MIXERCONTROL_CT_SC_METER_POLLED OR MIXERCONTROL_CT_UNITS_BOOLEAN)
MIXERCONTROL_CONTROLTYPE_SIGNEDMETER equ (MIXERCONTROL_CT_CLASS_METER OR MIXERCONTROL_CT_SC_METER_POLLED OR MIXERCONTROL_CT_UNITS_SIGNED)
MIXERCONTROL_CONTROLTYPE_PEAKMETER equ (MIXERCONTROL_CONTROLTYPE_SIGNEDMETER + 1)
MIXERCONTROL_CONTROLTYPE_UNSIGNEDMETER equ (MIXERCONTROL_CT_CLASS_METER OR MIXERCONTROL_CT_SC_METER_POLLED OR MIXERCONTROL_CT_UNITS_UNSIGNED)
MIXERCONTROL_CONTROLTYPE_BOOLEAN equ (MIXERCONTROL_CT_CLASS_SWITCH OR MIXERCONTROL_CT_SC_SWITCH_BOOLEAN OR MIXERCONTROL_CT_UNITS_BOOLEAN)
MIXERCONTROL_CONTROLTYPE_ONOFF equ (MIXERCONTROL_CONTROLTYPE_BOOLEAN + 1)
MIXERCONTROL_CONTROLTYPE_MUTE equ (MIXERCONTROL_CONTROLTYPE_BOOLEAN + 2)
MIXERCONTROL_CONTROLTYPE_MONO equ (MIXERCONTROL_CONTROLTYPE_BOOLEAN + 3)
MIXERCONTROL_CONTROLTYPE_LOUDNESS equ (MIXERCONTROL_CONTROLTYPE_BOOLEAN + 4)
MIXERCONTROL_CONTROLTYPE_STEREOENH equ (MIXERCONTROL_CONTROLTYPE_BOOLEAN + 5)
MIXERCONTROL_CONTROLTYPE_BUTTON equ (MIXERCONTROL_CT_CLASS_SWITCH OR MIXERCONTROL_CT_SC_SWITCH_BUTTON OR MIXERCONTROL_CT_UNITS_BOOLEAN)
MIXERCONTROL_CONTROLTYPE_DECIBELS equ (MIXERCONTROL_CT_CLASS_NUMBER OR MIXERCONTROL_CT_UNITS_DECIBES)
MIXERCONTROL_CONTROLTYPE_SIGNED equ (MIXERCONTROL_CT_CLASS_NUMBER OR MIXERCONTROL_CT_UNITS_SIGNED)
MIXERCONTROL_CONTROLTYPE_UNSIGNED equ (MIXERCONTROL_CT_CLASS_NUMBER OR MIXERCONTROL_CT_UNITS_UNSIGNED)
MIXERCONTROL_CONTROLTYPE_PERCENT equ (MIXERCONTROL_CT_CLASS_NUMBER OR MIXERCONTROL_CT_UNITS_PERCENT)
MIXERCONTROL_CONTROLTYPE_SLIDER equ (MIXERCONTROL_CT_CLASS_SLIDER OR MIXERCONTROL_CT_UNITS_SIGNED)
MIXERCONTROL_CONTROLTYPE_PAN equ (MIXERCONTROL_CONTROLTYPE_SLIDER + 1)
MIXERCONTROL_CONTROLTYPE_QSOUNDPAN equ (MIXERCONTROL_CONTROLTYPE_SLIDER + 2)
MIXERCONTROL_CONTROLTYPE_FADER equ (MIXERCONTROL_CT_CLASS_FADER OR MIXERCONTROL_CT_UNITS_UNSIGNED)
MIXERCONTROL_CONTROLTYPE_VOLUME equ (MIXERCONTROL_CONTROLTYPE_FADER + 1)
MIXERCONTROL_CONTROLTYPE_BASS equ (MIXERCONTROL_CONTROLTYPE_FADER + 2)
MIXERCONTROL_CONTROLTYPE_TREBLE equ (MIXERCONTROL_CONTROLTYPE_FADER + 3)
MIXERCONTROL_CONTROLTYPE_EQUALIZER equ (MIXERCONTROL_CONTROLTYPE_FADER + 4)
MIXERCONTROL_CONTROLTYPE_SINGLESELECT equ (MIXERCONTROL_CT_CLASS_LIST OR MIXERCONTROL_CT_SC_LIST_SINGLE OR MIXERCONTROL_CT_UNITS_BOOLEAN)
MIXERCONTROL_CONTROLTYPE_MUX equ (MIXERCONTROL_CONTROLTYPE_SINGLESEECT + 1)
MIXERCONTROL_CONTROLTYPE_MULTIPLESELECT equ (MIXERCONTROL_CT_CLASS_LIST OR MIXERCONTROL_CT_SC_LIST_MULTIPLE OR MIXERCONTROL_CT_UNITS_BOOLEAN)
MIXERCONTROL_CONTROLTYPE_MIXER equ (MIXERCONTROL_CONTROLTYPE_MULTIPLESEECT + 1)
MIXERCONTROL_CONTROLTYPE_MICROTIME equ (MIXERCONTROL_CT_CLASS_TIME OR MIXERCONTROL_CT_SC_TIME_MICROSECS OR MIXERCONTROL_CT_UNITS_UNSIGNED)
MIXERCONTROL_CONTROLTYPE_MILLITIME equ (MIXERCONTROL_CT_CLASS_TIME OR MIXERCONTROL_CT_SC_TIME_MILLISECS OR MIXERCONTROL_CT_UNITS_UNSIGNED)

;;
;;  MIXERLINECONTROLS
;;
ifdef _WIN32

MIXERLINECONTROLSA	STRUC
cbStruct		dd ?	;; size in bytes of MIXERLINECONTROLS
dwLineID		dd ?	;; line id (from MIXERLINE.dwLineID)
UNION
 dwControlID		dd ?	;; MIXER_GETLINECONTROLSF_ONEBYID
 dwControlType		dd ?	;; MIXER_GETLINECONTROLSF_ONEBYTYPE
ENDS
cControls		dd ?	;; count of controls pmxctrl points to
cbmxctrl		dd ?	;; size in bytes of _one_ MIXERCONTROL
pamxctrl		LPMIXERCONTROLA ?	;; pointer to first MIXERCONTROL array
MIXERLINECONTROLSA	ENDS
PMIXERLINECONTROLSA	typedef ptr MIXERLINECONTROLSA
LPMIXERLINECONTROLSA	typedef ptr MIXERLINECONTROLSA
MIXERLINECONTROLSW	STRUC
cbStruct		dd ?	;; size in bytes of MIXERLINECONTROLS
dwLineID		dd ?	;; line id (from MIXERLINE.dwLineID)
UNION
 dwControlID		dd ?	;; MIXER_GETLINECONTROLSF_ONEBYID
 dwControlType		dd ?	;; MIXER_GETLINECONTROLSF_ONEBYTYPE
ENDS
cControls		dd ?	;; count of controls pmxctrl points to
cbmxctrl		dd ?	;; size in bytes of _one_ MIXERCONTROL
pamxctrl		LPMIXERCONTROLW ?	;; pointer to first MIXERCONTROL array
MIXERLINECONTROLSW	ENDS
PMIXERLINECONTROLSW	typedef ptr MIXERLINECONTROLSW
LPMIXERLINECONTROLSW	typedef ptr MIXERLINECONTROLSW
ifdef _UNICODE
MIXERLINECONTROLS	typedef MIXERLINECONTROLSW
PMIXERLINECONTROLS	typedef PMIXERLINECONTROLSW
LPMIXERLINECONTROLS	typedef LPMIXERLINECONTROLSW
else
MIXERLINECONTROLS	typedef MIXERLINECONTROLSA
PMIXERLINECONTROLS	typedef PMIXERLINECONTROLSA
LPMIXERLINECONTROLS	typedef LPMIXERLINECONTROLSA
endif ;; UNICODE

else
MIXERLINECONTROLS	STRUC
cbStruct		dd ?	;; size in bytes of MIXERLINECONTROLS
dwLineID		dd ?	;; line id (from MIXERLINE.dwLineID)
UNION
 dwControlID		dd ?	;; MIXER_GETLINECONTROLSF_ONEBYID
 dwControlType		dd ?	;; MIXER_GETLINECONTROLSF_ONEBYTYPE
ENDS
cControls		dd ?	;; count of controls pmxctrl points to
cbmxctrl		dd ?	;; size in bytes of _one_ MIXERCONTROL
pamxctrl		LPMIXERCONTROL ?	;; pointer to first MIXERCONTROL array
MIXERLINECONTROLS	ENDS
PMIXERLINECONTROLS	typedef ptr MIXERLINECONTROLS
LPMIXERLINECONTROLS	typedef ptr MIXERLINECONTROLS
endif

;;
;;
;;
ifdef _WIN32

;MMRESULT
mixerGetLineControlsA proto _CType \
		hmxobj: HMIXEROBJ,
		 pmxlc: LPMIXERLINECONTROLSA,
	   fdwControls: DWORD
mixerGetLineControlsW proto _CType \
		hmxobj: HMIXEROBJ,
		 pmxlc: LPMIXERLINECONTROLSW,
	   fdwControls: DWORD
ifdef _UNICODE
mixerGetLineControls	equ <mixerGetLineControlsW>
else
mixerGetLineControls	equ <mixerGetLineControlsA>
endif ;; NOT UNICODE

else
mixerGetLineControls proto _CType \
		hmxobj: HMIXEROBJ,
		 pmxlc: LPMIXERLINECONTROLS,
	   fdwControls: DWORD
endif

MIXER_GETLINECONTROLSF_ALL equ 0x00000000
MIXER_GETLINECONTROLSF_ONEBYID equ 0x00000001
MIXER_GETLINECONTROLSF_ONEBYTYPE equ 0x00000002

MIXER_GETLINECONTROLSF_QUERYMASK equ 0x0000000F

MIXERCONTROLDETAILS	STRUC
cbStruct		dd ?	;; size in bytes of MIXERCONTROLDETAILS
dwControlID		dd ?	;; control id to get/set details on
cChannels		dd ?	;; number of channels in paDetails array
UNION
 hwndOwner		HWND ?	;; for MIXER_SETCONTROLDETAILSF_CUSTOM
 cMultipleItems		dd ?	;; if _MULTIPLE, the number of items per channel
ENDS
cbDetails		dd ?	;; size of _one_ details_XX struct
paDetails		LPVOID ?	;; pointer to array of details_XX structs
MIXERCONTROLDETAILS	ENDS
PMIXERCONTROLDETAILS	typedef ptr MIXERCONTROLDETAILS
LPMIXERCONTROLDETAILS	typedef ptr MIXERCONTROLDETAILS

;;
;;  MIXER_GETCONTROLDETAILSF_LISTTEXT
;;
;;
ifdef _WIN32

MIXERCONTROLDETAILS_LISTTEXTA  STRUC
dwParam1		dd ?
dwParam2		dd ?
szName			db MIXER_LONG_NAME_CHARS dup(?)
MIXERCONTROLDETAILS_LISTTEXTA ENDS
PMIXERCONTROLDETAILS_LISTTEXTA typedef ptr MIXERCONTROLDETAILS_LISTTEXTA
LPMIXERCONTROLDETAILS_LISTTEXTA typedef ptr MIXERCONTROLDETAILS_LISTTEXTA
MIXERCONTROLDETAILS_LISTTEXTW  STRUC
dwParam1		dd ?
dwParam2		dd ?
szName			dw MIXER_LONG_NAME_CHARS dup(?)
MIXERCONTROLDETAILS_LISTTEXTW ENDS
PMIXERCONTROLDETAILS_LISTTEXTW typedef ptr MIXERCONTROLDETAILS_LISTTEXTW
LPMIXERCONTROLDETAILS_LISTTEXTW typedef ptr MIXERCONTROLDETAILS_LISTTEXTW
ifdef _UNICODE
MIXERCONTROLDETAILS_LISTTEXT typedef MIXERCONTROLDETAILS_LISTTEXTW
PMIXERCONTROLDETAILS_LISTTEXT typedef PMIXERCONTROLDETAILS_LISTTEXTW
LPMIXERCONTROLDETAILS_LISTTEXT typedef LPMIXERCONTROLDETAILS_LISTTEXTW
else
MIXERCONTROLDETAILS_LISTTEXT typedef MIXERCONTROLDETAILS_LISTTEXTA
PMIXERCONTROLDETAILS_LISTTEXT typedef PMIXERCONTROLDETAILS_LISTTEXTA
LPMIXERCONTROLDETAILS_LISTTEXT typedef LPMIXERCONTROLDETAILS_LISTTEXTA
endif ;; UNICODE

else
tMIXERCONTROLDETAILS_LISTTEXT  STRUC
dwParam1		dd ?
dwParam2		dd ?
szName			db MIXER_LONG_NAME_CHARS dup(?)
MIXERCONTROLDETAILS_LISTTEXT ENDS
PMIXERCONTROLDETAILS_LISTTEXT typedef ptr MIXERCONTROLDETAILS_LISTTEXT
LPMIXERCONTROLDETAILS_LISTTEXT typedef ptr MIXERCONTROLDETAILS_LISTTEXT
endif

;;
;;  MIXER_GETCONTROLDETAILSF_VALUE
;;
;;
MIXERCONTROLDETAILS_BOOLEAN STRUC
fValue			LONG ?
MIXERCONTROLDETAILS_BOOLEAN ENDS
PMIXERCONTROLDETAILS_BOOLEAN typedef ptr MIXERCONTROLDETAILS_BOOLEAN
LPMIXERCONTROLDETAILS_BOOLEAN typedef ptr MIXERCONTROLDETAILS_BOOLEAN

MIXERCONTROLDETAILS_SIGNED STRUC
lValue			LONG ?
MIXERCONTROLDETAILS_SIGNED ENDS
PMIXERCONTROLDETAILS_SIGNED typedef ptr MIXERCONTROLDETAILS_SIGNED
LPMIXERCONTROLDETAILS_SIGNED typedef ptr MIXERCONTROLDETAILS_SIGNED

MIXERCONTROLDETAILS_UNSIGNED STRUC
dwValue			dd ?
MIXERCONTROLDETAILS_UNSIGNED ENDS
PMIXERCONTROLDETAILS_UNSIGNED typedef ptr MIXERCONTROLDETAILS_UNSIGNED
LPMIXERCONTROLDETAILS_UNSIGNED typedef ptr MIXERCONTROLDETAILS_UNSIGNED

ifdef _WIN32

;MMRESULT
mixerGetControlDetailsA proto _CType \
		hmxobj: HMIXEROBJ,
		 pmxcd: LPMIXERCONTROLDETAILS,
	    fdwDetails: DWORD
mixerGetControlDetailsW proto _CType \
		hmxobj: HMIXEROBJ,
		 pmxcd: LPMIXERCONTROLDETAILS,
	    fdwDetails: DWORD
ifdef _UNICODE
mixerGetControlDetails	equ <mixerGetControlDetailsW>
else
mixerGetControlDetails	equ <mixerGetControlDetailsA>
endif ;; NOT UNICODE

else
mixerGetControlDetails proto _CType \
		hmxobj: HMIXEROBJ,
		 pmxcd: LPMIXERCONTROLDETAILS,
	    fdwDetails: DWORD
endif

MIXER_GETCONTROLDETAILSF_VALUE equ 0x00000000
MIXER_GETCONTROLDETAILSF_LISTTEXT equ 0x00000001

MIXER_GETCONTROLDETAILSF_QUERYMASK equ 0x0000000F

;MMRESULT
mixerSetControlDetails proto _CType \
		hmxobj: HMIXEROBJ,
		 pmxcd: LPMIXERCONTROLDETAILS,
	    fdwDetails: DWORD

MIXER_SETCONTROLDETAILSF_VALUE equ 0x00000000
MIXER_SETCONTROLDETAILSF_CUSTOM equ 0x00000001

MIXER_SETCONTROLDETAILSF_QUERYMASK equ 0x0000000F

endif ;; ifndef _WIN32_VXD
endif ;; ifndef MMNOMIXER

ifndef MMNOTIMER
ifndef _WIN32_VXD
;;**************************************************************************
;;
;; Timer support
;;
;;**************************************************************************

;; timer error return values
TIMERR_NOERROR		equ (0)			 ;; no error
TIMERR_NOCANDO		equ (TIMERR_BASE+1)	 ;; request not completed
TIMERR_STRUCT		equ (TIMERR_BASE+33)	 ;; time struct size

;; timer data types
;void
TIMECALLBACK typedef proto _CType \
	      uTimerID: UINT,
		  uMsg: UINT,
		dwUser: DWORD,
		   dw1: DWORD,
		   dw2: DWORD
LPTIMECALLBACK		typedef ptr TIMECALLBACK

;; flags for fuEvent parameter of timeSetEvent() function
TIME_ONESHOT		equ 0x0000   ;; program timer for single event
TIME_PERIODIC		equ 0x0001   ;; program for continuous periodic event

ifdef _WIN32
TIME_CALLBACK_FUNCTION	equ 0x0000  ;; callback is function
TIME_CALLBACK_EVENT_SET equ 0x0010  ;; callback is event - use SetEvent
TIME_CALLBACK_EVENT_PULSE equ 0x0020  ;; callback is event - use PulseEvent
endif

;; timer device capabilities data structure
TIMECAPS		STRUC
wPeriodMin		UINT ?	;; minimum period supported
wPeriodMax		UINT ?	;; maximum period supported
TIMECAPS		ENDS
PTIMECAPS		typedef ptr TIMECAPS
NPTIMECAPS		typedef ptr TIMECAPS
LPTIMECAPS		typedef ptr TIMECAPS

;; timer function prototypes
;MMRESULT
timeGetSystemTime proto _CType \
		  pmmt: LPMMTIME,
		 cbmmt: UINT
;DWORD
timeGetTime proto _CType

;MMRESULT
timeSetEvent proto _CType \
		uDelay: UINT,
	   uResolution: UINT,
		  fptc: LPTIMECALLBACK,
		dwUser: DWORD,
	       fuEvent: UINT

;MMRESULT
timeKillEvent proto _CType \
	      uTimerID: UINT

;MMRESULT
timeGetDevCaps proto _CType \
		   ptc: LPTIMECAPS,
		  cbtc: UINT

;MMRESULT
timeBeginPeriod proto _CType \
	       uPeriod: UINT

;MMRESULT
timeEndPeriod proto _CType \
	       uPeriod: UINT

endif  ;; ifndef _WIN32_VXD
endif  ;; ifndef MMNOTIMER

ifndef MMNOJOY
;;**************************************************************************
;;
;; Joystick support
;;
;;**************************************************************************

;; joystick error return values
JOYERR_NOERROR		equ (0)			 ;; no error
JOYERR_PARMS		equ (JOYERR_BASE+5)	 ;; bad parameters
JOYERR_NOCANDO		equ (JOYERR_BASE+6)	 ;; request not completed
JOYERR_UNPLUGGED	equ (JOYERR_BASE+7)	 ;; joystick is unplugged

;; constants used with JOYINFO and JOYINFOEX structures and MM_JOY* messages
JOY_BUTTON1		equ 0x0001
JOY_BUTTON2		equ 0x0002
JOY_BUTTON3		equ 0x0004
JOY_BUTTON4		equ 0x0008
JOY_BUTTON1CHG		equ 0x0100
JOY_BUTTON2CHG		equ 0x0200
JOY_BUTTON3CHG		equ 0x0400
JOY_BUTTON4CHG		equ 0x0800

;; constants used with JOYINFOEX
JOY_BUTTON5		equ 0x00000010
JOY_BUTTON6		equ 0x00000020
JOY_BUTTON7		equ 0x00000040
JOY_BUTTON8		equ 0x00000080
JOY_BUTTON9		equ 0x00000100
JOY_BUTTON10		equ 0x00000200
JOY_BUTTON11		equ 0x00000400
JOY_BUTTON12		equ 0x00000800
JOY_BUTTON13		equ 0x00001000
JOY_BUTTON14		equ 0x00002000
JOY_BUTTON15		equ 0x00004000
JOY_BUTTON16		equ 0x00008000
JOY_BUTTON17		equ 0x00010000
JOY_BUTTON18		equ 0x00020000
JOY_BUTTON19		equ 0x00040000
JOY_BUTTON20		equ 0x00080000
JOY_BUTTON21		equ 0x00100000
JOY_BUTTON22		equ 0x00200000
JOY_BUTTON23		equ 0x00400000
JOY_BUTTON24		equ 0x00800000
JOY_BUTTON25		equ 0x01000000
JOY_BUTTON26		equ 0x02000000
JOY_BUTTON27		equ 0x04000000
JOY_BUTTON28		equ 0x08000000
JOY_BUTTON29		equ 0x10000000
JOY_BUTTON30		equ 0x20000000
JOY_BUTTON31		equ 0x40000000
JOY_BUTTON32		equ 0x80000000

;; constants used with JOYINFOEX structure
JOY_POVCENTERED		equ -1
JOY_POVFORWARD		equ 0
JOY_POVRIGHT		equ 9000
JOY_POVBACKWARD		equ 18000
JOY_POVLEFT		equ 27000

JOY_RETURNX		equ 0x00000001
JOY_RETURNY		equ 0x00000002
JOY_RETURNZ		equ 0x00000004
JOY_RETURNR		equ 0x00000008
JOY_RETURNU		equ 0x00000010 ;; axis 5
JOY_RETURNV		equ 0x00000020 ;; axis 6
JOY_RETURNPOV		equ 0x00000040
JOY_RETURNBUTTONS	equ 0x00000080
JOY_RETURNRAWDATA	equ 0x00000100
JOY_RETURNPOVCTS	equ 0x00000200
JOY_RETURNCENTERED	equ 0x00000400
JOY_USEDEADZONE		equ 0x00000800
JOY_RETURNALL		equ JOY_RETURNX OR JOY_RETURNY OR JOY_RETURNZ OR \
			    OR JOY_RETURNU OR JOY_RETURNV OR JOY_RETURNR \
			    OR JOY_RETURNBUTTONS OR JOY_RETURNPOV
JOY_CAL_READALWAYS	equ 0x00010000
JOY_CAL_READXYONLY	equ 0x00020000
JOY_CAL_READ3		equ 0x00040000
JOY_CAL_READ4		equ 0x00080000
JOY_CAL_READXONLY	equ 0x00100000
JOY_CAL_READYONLY	equ 0x00200000
JOY_CAL_READ5		equ 0x00400000
JOY_CAL_READ6		equ 0x00800000
JOY_CAL_READZONLY	equ 0x01000000
JOY_CAL_READRONLY	equ 0x02000000
JOY_CAL_READUONLY	equ 0x04000000
JOY_CAL_READVONLY	equ 0x08000000

;; joystick ID constants
JOYSTICKID1		equ 0
JOYSTICKID2		equ 1

;; joystick driver capabilites
JOYCAPS_HASZ		equ 0x0001
JOYCAPS_HASR		equ 0x0002
JOYCAPS_HASU		equ 0x0004
JOYCAPS_HASV		equ 0x0008
JOYCAPS_HASPOV		equ 0x0010
JOYCAPS_POV4DIR		equ 0x0020
JOYCAPS_POVCTS		equ 0x0040

;; joystick device capabilities data structure
ifdef _WIN32

JOYCAPSA		STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
szPname			db MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
wXmin			UINT ?	;; minimum x position value
wXmax			UINT ?	;; maximum x position value
wYmin			UINT ?	;; minimum y position value
wYmax			UINT ?	;; maximum y position value
wZmin			UINT ?	;; minimum z position value
wZmax			UINT ?	;; maximum z position value
wNumButtons		UINT ?	;; number of buttons
wPeriodMin		UINT ?	;; minimum message period when captured
wPeriodMax		UINT ?	;; maximum message period when captured
if (WINVER GE 0x0400)
wRmin			UINT ?	;; minimum r position value
wRmax			UINT ?	;; maximum r position value
wUmin			UINT ?	;; minimum u (5th axis) position value
wUmax			UINT ?	;; maximum u (5th axis) position value
wVmin			UINT ?	;; minimum v (6th axis) position value
wVmax			UINT ?	;; maximum v (6th axis) position value
wCaps			UINT ?	;; joystick capabilites
wMaxAxes		UINT ?	;; maximum number of axes supported
wNumAxes		UINT ?	;; number of axes in use
wMaxButtons		UINT ?	;; maximum number of buttons supported
szRegKey		db MAXPNAMELEN dup(?) ;; registry key
szOEMVxD		db MAX_JOYSTICKOEMVXDNAME dup(?) ;; OEM VxD in use
endif
JOYCAPSA		ENDS
PJOYCAPSA		typedef ptr JOYCAPSA
NPJOYCAPSA		typedef ptr JOYCAPSA
LPJOYCAPSA		typedef ptr JOYCAPSA
JOYCAPSW		STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
szPname			dw MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
wXmin			UINT ?	;; minimum x position value
wXmax			UINT ?	;; maximum x position value
wYmin			UINT ?	;; minimum y position value
wYmax			UINT ?	;; maximum y position value
wZmin			UINT ?	;; minimum z position value
wZmax			UINT ?	;; maximum z position value
wNumButtons		UINT ?	;; number of buttons
wPeriodMin		UINT ?	;; minimum message period when captured
wPeriodMax		UINT ?	;; maximum message period when captured
if (WINVER GE 0x0400)
wRmin			UINT ?	;; minimum r position value
wRmax			UINT ?	;; maximum r position value
wUmin			UINT ?	;; minimum u (5th axis) position value
wUmax			UINT ?	;; maximum u (5th axis) position value
wVmin			UINT ?	;; minimum v (6th axis) position value
wVmax			UINT ?	;; maximum v (6th axis) position value
wCaps			UINT ?	;; joystick capabilites
wMaxAxes		UINT ?	;; maximum number of axes supported
wNumAxes		UINT ?	;; number of axes in use
wMaxButtons		UINT ?	;; maximum number of buttons supported
szRegKey		dw MAXPNAMELEN dup(?) ;; registry key
szOEMVxD		dw MAX_JOYSTICKOEMVXDNAME dup(?) ;; OEM VxD in use
endif
JOYCAPSW		ENDS
PJOYCAPSW		typedef ptr JOYCAPSW
NPJOYCAPSW		typedef ptr JOYCAPSW
LPJOYCAPSW		typedef ptr JOYCAPSW
ifdef _UNICODE
JOYCAPS			typedef JOYCAPSW
PJOYCAPS		typedef PJOYCAPSW
NPJOYCAPS		typedef NPJOYCAPSW
LPJOYCAPS		typedef LPJOYCAPSW
else
JOYCAPS			typedef JOYCAPSA
PJOYCAPS		typedef PJOYCAPSA
NPJOYCAPS		typedef NPJOYCAPSA
LPJOYCAPS		typedef LPJOYCAPSA
endif ;; UNICODE

else
JOYCAPS			STRUC
wMid			dw ?	;; manufacturer ID
wPid			dw ?	;; product ID
szPname			db MAXPNAMELEN dup(?) ;; product name (NULL terminated string)
wXmin			UINT ?	;; minimum x position value
wXmax			UINT ?	;; maximum x position value
wYmin			UINT ?	;; minimum y position value
wYmax			UINT ?	;; maximum y position value
wZmin			UINT ?	;; minimum z position value
wZmax			UINT ?	;; maximum z position value
wNumButtons		UINT ?	;; number of buttons
wPeriodMin		UINT ?	;; minimum message period when captured
wPeriodMax		UINT ?	;; maximum message period when captured
if (WINVER GE 0x0400)
wRmin			UINT ?	;; minimum r position value
wRmax			UINT ?	;; maximum r position value
wUmin			UINT ?	;; minimum u (5th axis) position value
wUmax			UINT ?	;; maximum u (5th axis) position value
wVmin			UINT ?	;; minimum v (6th axis) position value
wVmax			UINT ?	;; maximum v (6th axis) position value
wCaps			UINT ?	;; joystick capabilites
wMaxAxes		UINT ?	;; maximum number of axes supported
wNumAxes		UINT ?	;; number of axes in use
wMaxButtons		UINT ?	;; maximum number of buttons supported
szRegKey		db MAXPNAMELEN dup(?) ;; registry key
szOEMVxD		db MAX_JOYSTICKOEMVXDNAME dup(?) ;; OEM VxD in use
endif
JOYCAPS			ENDS
PJOYCAPS		typedef ptr JOYCAPS
NPJOYCAPS		typedef ptr JOYCAPS
LPJOYCAPS		typedef ptr JOYCAPS
endif

;; joystick information data structure
JOYINFO			STRUC
wXpos			UINT ?	;; x position
wYpos			UINT ?	;; y position
wZpos			UINT ?	;; z position
wButtons		UINT ?	;; button states
JOYINFO			ENDS
PJOYINFO		typedef ptr JOYINFO
NPJOYINFO		typedef ptr JOYINFO
LPJOYINFO		typedef ptr JOYINFO

if(WINVER GE 0x0400)
JOYINFOEX		STRUC
dwSize			dd ?	;; size of structure
dwFlags			dd ?	;; flags to indicate what to return
dwXpos			dd ?	;; x position
dwYpos			dd ?	;; y position
dwZpos			dd ?	;; z position
dwRpos			dd ?	;; rudder/4th axis position
dwUpos			dd ?	;; 5th axis position
dwVpos			dd ?	;; 6th axis position
dwButtons		dd ?	;; button states
dwButtonNumber		dd ?	;; current button number pressed
dwPOV			dd ?	;; point of view state
dwReserved1		dd ?	;; reserved for communication between winmm & driver
dwReserved2		dd ?	;; reserved for future expansion
JOYINFOEX		ENDS
PJOYINFOEX		typedef ptr JOYINFOEX
NPJOYINFOEX		typedef ptr JOYINFOEX
LPJOYINFOEX		typedef ptr JOYINFOEX
endif ;; WINVER GE 0x0400

ifndef _WIN32_VXD

;; joystick function prototypes
;UINT
joyGetNumDevs proto _CType
ifdef _WIN32

;MMRESULT
joyGetDevCapsA proto _CType \
		uJoyID: UINT,
		   pjc: LPJOYCAPSA,
		  cbjc: UINT
joyGetDevCapsW proto _CType \
		uJoyID: UINT,
		   pjc: LPJOYCAPSW,
		  cbjc: UINT
ifdef _UNICODE
joyGetDevCaps		equ <joyGetDevCapsW>
else
joyGetDevCaps		equ <joyGetDevCapsA>
endif ;; NOT UNICODE

else
;MMRESULT
joyGetDevCaps proto _CType \
		uJoyID: UINT,
		   pjc: LPJOYCAPS,
		  cbjc: UINT
endif
;MMRESULT
joyGetPos proto _CType \
		uJoyID: UINT,
		   pji: LPJOYINFO

if(WINVER GE 0x0400)
;MMRESULT
joyGetPosEx proto _CType \
		uJoyID: UINT,
		   pji: LPJOYINFOEX
endif ;; WINVER GE 0x0400

;MMRESULT
joyGetThreshold proto _CType \
		uJoyID: UINT,
	   puThreshold: LPUINT
;MMRESULT
joyReleaseCapture proto _CType \
		uJoyID: UINT
;MMRESULT
joySetCapture proto _CType \
		  hwnd: HWND,
		uJoyID: UINT,
	       uPeriod: UINT,
	      fChanged: BOOL
;MMRESULT
joySetThreshold proto _CType \
		uJoyID: UINT,
	    uThreshold: UINT

endif ;; ifndef _WIN32_VXD

endif  ;; ifndef MMNOJOY

ifndef MMNOMMIO
ifndef _WIN32_VXD
;;**************************************************************************
;;
;; Multimedia File I/O support
;;
;;**************************************************************************

;; MMIO error return values
MMIOERR_BASE		equ 256
MMIOERR_FILENOTFOUND	equ (MMIOERR_BASE + 1)	;; file not found
MMIOERR_OUTOFMEMORY	equ (MMIOERR_BASE + 2)	;; out of memory
MMIOERR_CANNOTOPEN	equ (MMIOERR_BASE + 3)	;; cannot open
MMIOERR_CANNOTCLOSE	equ (MMIOERR_BASE + 4)	;; cannot close
MMIOERR_CANNOTREAD	equ (MMIOERR_BASE + 5)	;; cannot read
MMIOERR_CANNOTWRITE	equ (MMIOERR_BASE + 6)	;; cannot write
MMIOERR_CANNOTSEEK	equ (MMIOERR_BASE + 7)	;; cannot seek
MMIOERR_CANNOTEXPAND	equ (MMIOERR_BASE + 8)	;; cannot expand file
MMIOERR_CHUNKNOTFOUND	equ (MMIOERR_BASE + 9)	;; chunk not found
MMIOERR_UNBUFFERED	equ (MMIOERR_BASE + 10) ;;
MMIOERR_PATHNOTFOUND	equ (MMIOERR_BASE + 11) ;; path incorrect
MMIOERR_ACCESSDENIED	equ (MMIOERR_BASE + 12) ;; file was protected
MMIOERR_SHARINGVIOLATION equ (MMIOERR_BASE + 13) ;; file in use
MMIOERR_NETWORKERROR	equ (MMIOERR_BASE + 14) ;; network not responding
MMIOERR_TOOMANYOPENFILES equ (MMIOERR_BASE + 15) ;; no more file handles
MMIOERR_INVALIDFILE	equ (MMIOERR_BASE + 16) ;; default error file error

;; MMIO constants
CFSEPCHAR		equ '+'		    ;; compound file name separator char.

;; MMIO data types
FOURCC			typedef DWORD	;; a four character code
HPSTR			typedef ptr	;; a huge version of LPSTR
HMMIO			typedef HANDLE	;; a handle to an open file
;LRESULT
MMIOPROC typedef proto _CType \
	    lpmmioinfo: LPSTR,
		  uMsg: UINT,
	       lParam1: LPARAM,
	       lParam2: LPARAM
LPMMIOPROC		typedef ptr MMIOPROC

;; general MMIO information data structure
MMIOINFO		STRUC
;; general fields
dwFlags			dd ?	;; general status flags
fccIOProc		FOURCC ?	;; pointer to I/O procedure
pIOProc			LPMMIOPROC ?	;; pointer to I/O procedure
wErrorRet		UINT ?	;; place for error to be returned
htask			HTASK ? ;; alternate local task

;; fields maintained by MMIO functions during buffered I/O
cchBuffer		LONG ?	;; size of I/O buffer (or 0L)
pchBuffer		HPSTR ? ;; start of I/O buffer (or NULL)
pchNext			HPSTR ? ;; pointer to next byte to read/write
pchEndRead		HPSTR ? ;; pointer to last valid byte to read
pchEndWrite		HPSTR ? ;; pointer to last byte to write
lBufOffset		LONG ?	;; disk offset of start of buffer

;; fields maintained by I/O procedure
lDiskOffset		LONG ?	;; disk offset of next read or write
adwInfo			dd 3 dup(?)	;; data specific to type of MMIOPROC

;; other fields maintained by MMIO
dwReserved1		dd ?	;; reserved for MMIO use
dwReserved2		dd ?	;; reserved for MMIO use
hmmio			HMMIO ? ;; handle to open file
MMIOINFO		ENDS
PMMIOINFO		typedef ptr MMIOINFO
NPMMIOINFO		typedef ptr MMIOINFO
LPMMIOINFO		typedef ptr MMIOINFO
LPCMMIOINFO		typedef ptr MMIOINFO

;; RIFF chunk information data structure
MMCKINFO		STRUC
ckid			FOURCC ?	;; chunk ID
cksize			dd ?	;; chunk size
fccType			FOURCC ?	;; form type or list type
dwDataOffset		dd ?	;; offset of data portion of chunk
dwFlags			dd ?	;; flags used by MMIO functions
MMCKINFO		ENDS
PMMCKINFO		typedef ptr MMCKINFO
NPMMCKINFO		typedef ptr MMCKINFO
LPMMCKINFO		typedef ptr MMCKINFO
LPCMMCKINFO		typedef ptr MMCKINFO

;; bit field masks
MMIO_RWMODE		equ 0x00000003	    ;; open file for reading/writing/both
MMIO_SHAREMODE		equ 0x00000070	    ;; file sharing mode number

;; constants for dwFlags field of MMIOINFO
MMIO_CREATE		equ 0x00001000	    ;; create new file (or truncate file)
MMIO_PARSE		equ 0x00000100	    ;; parse new file returning path
MMIO_DELETE		equ 0x00000200	    ;; create new file (or truncate file)
MMIO_EXIST		equ 0x00004000	    ;; checks for existence of file
MMIO_ALLOCBUF		equ 0x00010000	    ;; mmioOpen() should allocate a buffer
MMIO_GETTEMP		equ 0x00020000	    ;; mmioOpen() should retrieve temp name

MMIO_DIRTY		equ 0x10000000	    ;; I/O buffer is dirty

;; read/write mode numbers (bit field MMIO_RWMODE)
MMIO_READ		equ 0x00000000	    ;; open file for reading only
MMIO_WRITE		equ 0x00000001	    ;; open file for writing only
MMIO_READWRITE		equ 0x00000002	    ;; open file for reading and writing

;; share mode numbers (bit field MMIO_SHAREMODE)
MMIO_COMPAT		equ 0x00000000	    ;; compatibility mode
MMIO_EXCLUSIVE		equ 0x00000010	    ;; exclusive-access mode
MMIO_DENYWRITE		equ 0x00000020	    ;; deny writing to other processes
MMIO_DENYREAD		equ 0x00000030	    ;; deny reading to other processes
MMIO_DENYNONE		equ 0x00000040	    ;; deny nothing to other processes

;; various MMIO flags
MMIO_FHOPEN		equ 0x0010  ;; mmioClose: keep file handle open
MMIO_EMPTYBUF		equ 0x0010  ;; mmioFlush: empty the I/O buffer
MMIO_TOUPPER		equ 0x0010  ;; mmioStringToFOURCC: to u-case
MMIO_INSTALLPROC	equ 0x00010000	;; mmioInstallIOProc: install MMIOProc
MMIO_GLOBALPROC		equ 0x10000000	;; mmioInstallIOProc: install globally
MMIO_REMOVEPROC		equ 0x00020000	;; mmioInstallIOProc: remove MMIOProc
MMIO_UNICODEPROC	equ 0x01000000	;; mmioInstallIOProc: Unicode MMIOProc
MMIO_FINDPROC		equ 0x00040000	;; mmioInstallIOProc: find an MMIOProc
MMIO_FINDCHUNK		equ 0x0010  ;; mmioDescend: find a chunk by ID
MMIO_FINDRIFF		equ 0x0020  ;; mmioDescend: find a LIST chunk
MMIO_FINDLIST		equ 0x0040  ;; mmioDescend: find a RIFF chunk
MMIO_CREATERIFF		equ 0x0020  ;; mmioCreateChunk: make a LIST chunk
MMIO_CREATELIST		equ 0x0040  ;; mmioCreateChunk: make a RIFF chunk

;; message numbers for MMIOPROC I/O procedure functions
MMIOM_READ		equ MMIO_READ	    ;; read
MMIOM_WRITE		equ MMIO_WRITE	     ;; write
MMIOM_SEEK		equ 2	    ;; seek to a new position in file
MMIOM_OPEN		equ 3	    ;; open file
MMIOM_CLOSE		equ 4	    ;; close file
MMIOM_WRITEFLUSH	equ 5	    ;; write and flush

if (WINVER GE 0x030a)
MMIOM_RENAME		equ 6	    ;; rename specified file
endif ;; ifdef WINVER GE 0x030a

MMIOM_USER		equ 0x8000	 ;; beginning of user-defined messages

;; MMIO macros
mmioFOURCC macro ch0, ch1, ch2, ch3
	exitm<MAKEFOURCC(ch0, ch1, ch2, ch3)>
	endm

;; standard four character codes
FOURCC_RIFF		equ mmioFOURCC('R', 'I', 'F', 'F')
FOURCC_LIST		equ mmioFOURCC('L', 'I', 'S', 'T')

;; four character codes used to identify standard built-in I/O procedures
FOURCC_DOS		equ mmioFOURCC('D', 'O', 'S', ' ')
FOURCC_MEM		equ mmioFOURCC('M', 'E', 'M', ' ')

;; flags for mmioSeek()
ifndef SEEK_SET
SEEK_SET		equ 0		    ;; seek to an absolute position
SEEK_CUR		equ 1		    ;; seek relative to current position
SEEK_END		equ 2		    ;; seek relative to end of file
endif  ;; ifndef SEEK_SET

;; other constants
MMIO_DEFAULTBUFFER	equ 8192    ;; default buffer size


;; MMIO function prototypes
ifdef _WIN32

;FOURCC
mmioStringToFOURCCA proto _CType \
		    sz: LPCSTR,
		uFlags: UINT
mmioStringToFOURCCW proto _CType \
		    sz: LPCWSTR,
		uFlags: UINT
ifdef _UNICODE
mmioStringToFOURCC	equ <mmioStringToFOURCCW>
else
mmioStringToFOURCC	equ <mmioStringToFOURCCA>
endif ;; NOT UNICODE
;LPMMIOPROC
mmioInstallIOProcA proto _CType \
	     fccIOProc: FOURCC,
	       pIOProc: LPMMIOPROC,
	       dwFlags: DWORD
mmioInstallIOProcW proto _CType \
	     fccIOProc: FOURCC,
	       pIOProc: LPMMIOPROC,
	       dwFlags: DWORD
ifdef _UNICODE
mmioInstallIOProc	equ <mmioInstallIOProcW>
else
mmioInstallIOProc	equ <mmioInstallIOProcA>
endif ;; NOT UNICODE
;HMMIO
mmioOpenA proto _CType \
	   pszFileName: LPSTR,
	     pmmioinfo: LPMMIOINFO,
	       fdwOpen: DWORD
mmioOpenW proto _CType \
	   pszFileName: LPWSTR,
	     pmmioinfo: LPMMIOINFO,
	       fdwOpen: DWORD
ifdef _UNICODE
mmioOpen		equ <mmioOpenW>
else
mmioOpen		equ <mmioOpenA>
endif ;; NOT UNICODE
;MMRESULT
mmioRenameA proto _CType \
	   pszFileName: LPCSTR,
	pszNewFileName: LPCSTR,
	     pmmioinfo: LPCMMIOINFO,
	     fdwRename: DWORD
mmioRenameW proto _CType \
	   pszFileName: LPCWSTR,
	pszNewFileName: LPCWSTR,
	     pmmioinfo: LPCMMIOINFO,
	     fdwRename: DWORD
ifdef _UNICODE
mmioRename		equ <mmioRenameW>
else
mmioRename		equ <mmioRenameA>
endif ;; NOT UNICODE
else
;FOURCC
mmioStringToFOURCC proto _CType \
		    sz: LPCSTR,
		uFlags: UINT
;LPMMIOPROC
mmioInstallIOProc proto _CType \
	     fccIOProc: FOURCC,
	       pIOProc: LPMMIOPROC,
	       dwFlags: DWORD
mmioOpen proto _CType \
	   pszFileName: LPSTR,
	     pmmioinfo: LPMMIOINFO,
	       fdwOpen: DWORD
if (WINVER GE 0x030a)
;MMRESULT
mmioRename proto _CType \
	   pszFileName: LPCSTR,
	pszNewFileName: LPCSTR,
	     pmmioinfo: ptr MMIOINFO,
	     fdwRename: DWORD
endif ;; ifdef WINVER GE 0x030a
endif

;MMRESULT
mmioClose proto _CType \
		 hmmio: HMMIO,
	       fuClose: UINT

;LONG
mmioRead proto _CType \
		 hmmio: HMMIO,
		   pch: HPSTR,
		   cch: LONG

;LONG
mmioWrite proto _CType \
		 hmmio: HMMIO,
		   pch: ptr,
		   cch: LONG

;LONG
mmioSeek proto _CType \
		 hmmio: HMMIO,
	       lOffset: LONG,
	       iOrigin: SINT

;MMRESULT
mmioGetInfo proto _CType \
		 hmmio: HMMIO,
	     pmmioinfo: LPMMIOINFO,
		fuInfo: UINT

;MMRESULT
mmioSetInfo proto _CType \
		 hmmio: HMMIO,
	     pmmioinfo: LPCMMIOINFO,
		fuInfo: UINT

;MMRESULT
mmioSetBuffer proto _CType \
		 hmmio: HMMIO,
	     pchBuffer: LPSTR,
	     cchBuffer: LONG,
	      fuBuffer: UINT

;MMRESULT
mmioFlush proto _CType \
		 hmmio: HMMIO,
	       fuFlush: UINT

;MMRESULT
mmioAdvance proto _CType \
		 hmmio: HMMIO,
	     pmmioinfo: LPMMIOINFO,
	     fuAdvance: UINT

;LRESULT
mmioSendMessage proto _CType \
		 hmmio: HMMIO,
		  uMsg: UINT,
	       lParam1: LPARAM,
	       lParam2: HMMIO
;MMRESULT
mmioDescend proto _CType \
		 hmmio: HMMIO,
		pmmcki: LPMMCKINFO,
	  pmmckiParent: MMCKINFO,
	     fuDescend: UINT

;MMRESULT
mmioAscend proto _CType \
		 hmmio: HMMIO,
		pmmcki: LPMMCKINFO,
	      fuAscend: UINT
;MMRESULT
mmioCreateChunk proto _CType \
		 hmmio: HMMIO,
		pmmcki: LPMMCKINFO,
	      fuCreate: UINT

endif  ;; ifndef _WIN32_VXD
endif  ;; ifndef MMNOMMIO

ifndef MMNOMCI
ifndef _WIN32_VXD
;;**************************************************************************
;;
;; MCI support
;;
;;**************************************************************************

ifndef _MCIERROR_	       ;; MCIERROR is defined in some post 3.1 apps
_MCIERROR_		equ 1
MCIERROR		typedef DWORD	     ;; error return code, 0 means no error
endif

ifndef _MCIDEVICEID_	       ;; Same with MCIDEVICEID
_MCIDEVICEID_		equ 1
MCIDEVICEID		typedef UINT	 ;; MCI device ID type
endif

;UINT
YIELDPROC_T typedef proto _CType \
		 mciId: MCIDEVICEID,
	   dwYieldData: DWORD
YIELDPROC typedef ptr YIELDPROC_T
;; MCI function prototypes
ifdef _WIN32

;MCIERROR
mciSendCommandA proto _CType \
		 mciId: MCIDEVICEID,
		  uMsg: UINT,
	      dwParam1: DWORD,
	      dwParam2: DWORD
mciSendCommandW proto _CType \
		 mciId: MCIDEVICEID,
		  uMsg: UINT,
	      dwParam1: DWORD,
	      dwParam2: DWORD
ifdef _UNICODE
mciSendCommand		equ <mciSendCommandW>
else
mciSendCommand		equ <mciSendCommandA>
endif ;; NOT UNICODE
;MCIERROR
mciSendStringA proto _CType \
	  lpstrCommand: LPCSTR,
     lpstrReturnString: LPSTR,
	 uReturnLength: UINT,
	  hwndCallback: HWND
mciSendStringW proto _CType \
	 lpstrCommand: LPCWSTR,
    lpstrReturnString: LPWSTR,
	uReturnLength: UINT,
	 hwndCallback: HWND
ifdef _UNICODE
mciSendString		equ <mciSendStringW>
else
mciSendString		equ <mciSendStringA>
endif ;; NOT UNICODE
;MCIDEVICEID
mciGetDeviceIDA proto _CType \
	     pszDevice: LPCSTR
mciGetDeviceIDW proto _CType \
	     pszDevice: LPCWSTR
ifdef _UNICODE
mciGetDeviceID		equ <mciGetDeviceIDW>
else
mciGetDeviceID		equ <mciGetDeviceIDA>
endif ;; NOT UNICODE
;MCIDEVICEID
mciGetDeviceIDFromElementIDA proto _CType \
	   dwElementID: DWORD,
	     lpstrType: LPCSTR
mciGetDeviceIDFromElementIDW proto _CType \
	   dwElementID: DWORD,
	     lpstrType: LPWSTR
ifdef _UNICODE
mciGetDeviceIDFromElementID equ <mciGetDeviceIDFromElementIDW>
else
mciGetDeviceIDFromElementID equ <mciGetDeviceIDFromElementIDA>
endif ;; NOT UNICODE

;BOOL
mciGetErrorStringA proto _CType \
		mcierr: MCIERROR,
	       pszText: LPSTR,
	       cchText: UINT
mciGetErrorStringW proto _CType \
		mcierr: MCIERROR,
	       pszText: LPWSTR,
	       cchText: UINT
ifdef _UNICODE
mciGetErrorString	equ <mciGetErrorStringW>
else
mciGetErrorString	equ <mciGetErrorStringA>
endif ;; NOT UNICODE

else
;MCIERROR
mciSendCommand proto _CType \
		 mciId: MCIDEVICEID,
		  uMsg: UINT,
	      dwParam1: DWORD,
	      dwParam2: DWORD
;MCIERROR
mciSendString proto _CType \
	  lpstrCommand: LPCSTR,
     lpstrReturnString: LPSTR,
	 uReturnLength: UINT,
	  hwndCallback: HWND
;MCIDEVICEID
mciGetDeviceID proto _CType \
	     pszDevice: LPCSTR
;BOOL
mciGetErrorString proto _CType \
		mcierr: MCIERROR,
	       pszText: LPSTR,
	       cchText: UINT
endif

;BOOL
mciSetYieldProc proto _CType \
		 mciId: MCIDEVICEID,
	   fpYieldProc: YIELDPROC,
	   dwYieldData: DWORD

if (WINVER GE 0x030a)
;HTASK
mciGetCreatorTaskg proto _CType \
		 mciId: MCIDEVICEID
;YIELDPROC
mciGetYieldProcg proto _CType \
		 mciId: MCIDEVICEID,
	  pdwYieldData: LPDWORD
endif ;; ifdef WINVER GE 0x030a

if (WINVER LT 0x030a)
WINMMAPI BOOL WINAPI mciExecute(LPCSTR pszCommand);
endif ;; ifdef WINVER LT 0x030a

;; MCI error return values
MCIERR_INVALID_DEVICE_ID equ (MCIERR_BASE + 1)
MCIERR_UNRECOGNIZED_KEYWORD equ (MCIERR_BASE + 3)
MCIERR_UNRECOGNIZED_COMMAND equ (MCIERR_BASE + 5)
MCIERR_HARDWARE		equ (MCIERR_BASE + 6)
MCIERR_INVALID_DEVICE_NAME equ (MCIERR_BASE + 7)
MCIERR_OUT_OF_MEMORY	equ (MCIERR_BASE + 8)
MCIERR_DEVICE_OPEN	equ (MCIERR_BASE + 9)
MCIERR_CANNOT_LOAD_DRIVER equ (MCIERR_BASE + 10)
MCIERR_MISSING_COMMAND_STRING equ (MCIERR_BASE + 11)
MCIERR_PARAM_OVERFLOW	equ (MCIERR_BASE + 12)
MCIERR_MISSING_STRING_ARGUMENT equ (MCIERR_BASE + 13)
MCIERR_BAD_INTEGER	equ (MCIERR_BASE + 14)
MCIERR_PARSER_INTERNAL	equ (MCIERR_BASE + 15)
MCIERR_DRIVER_INTERNAL	equ (MCIERR_BASE + 16)
MCIERR_MISSING_PARAMETER equ (MCIERR_BASE + 17)
MCIERR_UNSUPPORTED_FUNCTION equ (MCIERR_BASE + 18)
MCIERR_FILE_NOT_FOUND	equ (MCIERR_BASE + 19)
MCIERR_DEVICE_NOT_READY equ (MCIERR_BASE + 20)
MCIERR_INTERNAL		equ (MCIERR_BASE + 21)
MCIERR_DRIVER		equ (MCIERR_BASE + 22)
MCIERR_CANNOT_USE_ALL	equ (MCIERR_BASE + 23)
MCIERR_MULTIPLE		equ (MCIERR_BASE + 24)
MCIERR_EXTENSION_NOT_FOUND equ (MCIERR_BASE + 25)
MCIERR_OUTOFRANGE	equ (MCIERR_BASE + 26)
MCIERR_FLAGS_NOT_COMPATIBLE equ (MCIERR_BASE + 28)
MCIERR_FILE_NOT_SAVED	equ (MCIERR_BASE + 30)
MCIERR_DEVICE_TYPE_REQUIRED equ (MCIERR_BASE + 31)
MCIERR_DEVICE_LOCKED	equ (MCIERR_BASE + 32)
MCIERR_DUPLICATE_ALIAS	equ (MCIERR_BASE + 33)
MCIERR_BAD_CONSTANT	equ (MCIERR_BASE + 34)
MCIERR_MUST_USE_SHAREABLE equ (MCIERR_BASE + 35)
MCIERR_MISSING_DEVICE_NAME equ (MCIERR_BASE + 36)
MCIERR_BAD_TIME_FORMAT	equ (MCIERR_BASE + 37)
MCIERR_NO_CLOSING_QUOTE equ (MCIERR_BASE + 38)
MCIERR_DUPLICATE_FLAGS	equ (MCIERR_BASE + 39)
MCIERR_INVALID_FILE	equ (MCIERR_BASE + 40)
MCIERR_NULL_PARAMETER_BLOCK equ (MCIERR_BASE + 41)
MCIERR_UNNAMED_RESOURCE equ (MCIERR_BASE + 42)
MCIERR_NEW_REQUIRES_ALIAS equ (MCIERR_BASE + 43)
MCIERR_NOTIFY_ON_AUTO_OPEN equ (MCIERR_BASE + 44)
MCIERR_NO_ELEMENT_ALLOWED equ (MCIERR_BASE + 45)
MCIERR_NONAPPLICABLE_FUNCTION equ (MCIERR_BASE + 46)
MCIERR_ILLEGAL_FOR_AUTO_OPEN equ (MCIERR_BASE + 47)
MCIERR_FILENAME_REQUIRED equ (MCIERR_BASE + 48)
MCIERR_EXTRA_CHARACTERS equ (MCIERR_BASE + 49)
MCIERR_DEVICE_NOT_INSTALLED equ (MCIERR_BASE + 50)
MCIERR_GET_CD		equ (MCIERR_BASE + 51)
MCIERR_SET_CD		equ (MCIERR_BASE + 52)
MCIERR_SET_DRIVE	equ (MCIERR_BASE + 53)
MCIERR_DEVICE_LENGTH	equ (MCIERR_BASE + 54)
MCIERR_DEVICE_ORD_LENGTH equ (MCIERR_BASE + 55)
MCIERR_NO_INTEGER	equ (MCIERR_BASE + 56)

MCIERR_WAVE_OUTPUTSINUSE equ (MCIERR_BASE + 64)
MCIERR_WAVE_SETOUTPUTINUSE equ (MCIERR_BASE + 65)
MCIERR_WAVE_INPUTSINUSE equ (MCIERR_BASE + 66)
MCIERR_WAVE_SETINPUTINUSE equ (MCIERR_BASE + 67)
MCIERR_WAVE_OUTPUTUNSPECIFIED equ (MCIERR_BASE + 68)
MCIERR_WAVE_INPUTUNSPECIFIED equ (MCIERR_BASE + 69)
MCIERR_WAVE_OUTPUTSUNSUITABLE equ (MCIERR_BASE + 70)
MCIERR_WAVE_SETOUTPUTUNSUITABLE equ (MCIERR_BASE + 71)
MCIERR_WAVE_INPUTSUNSUITABLE equ (MCIERR_BASE + 72)
MCIERR_WAVE_SETINPUTUNSUITABLE equ (MCIERR_BASE + 73)

MCIERR_SEQ_DIV_INCOMPATIBLE equ (MCIERR_BASE + 80)
MCIERR_SEQ_PORT_INUSE	equ (MCIERR_BASE + 81)
MCIERR_SEQ_PORT_NONEXISTENT equ (MCIERR_BASE + 82)
MCIERR_SEQ_PORT_MAPNODEVICE equ (MCIERR_BASE + 83)
MCIERR_SEQ_PORT_MISCERROR equ (MCIERR_BASE + 84)
MCIERR_SEQ_TIMER	equ (MCIERR_BASE + 85)
MCIERR_SEQ_PORTUNSPECIFIED equ (MCIERR_BASE + 86)
MCIERR_SEQ_NOMIDIPRESENT equ (MCIERR_BASE + 87)

MCIERR_NO_WINDOW	equ (MCIERR_BASE + 90)
MCIERR_CREATEWINDOW	equ (MCIERR_BASE + 91)
MCIERR_FILE_READ	equ (MCIERR_BASE + 92)
MCIERR_FILE_WRITE	equ (MCIERR_BASE + 93)

MCIERR_NO_IDENTITY	equ (MCIERR_BASE + 94)

;; all custom device driver errors must be >= than this value
MCIERR_CUSTOM_DRIVER_BASE equ (MCIERR_BASE + 256)

MCI_FIRST		equ DRV_MCI_FIRST   ;; 0x0800
;; MCI command message identifiers
MCI_OPEN		equ 0x0803
MCI_CLOSE		equ 0x0804
MCI_ESCAPE		equ 0x0805
MCI_PLAY		equ 0x0806
MCI_SEEK		equ 0x0807
MCI_STOP		equ 0x0808
MCI_PAUSE		equ 0x0809
MCI_INFO		equ 0x080A
MCI_GETDEVCAPS		equ 0x080B
MCI_SPIN		equ 0x080C
MCI_SET			equ 0x080D
MCI_STEP		equ 0x080E
MCI_RECORD		equ 0x080F
MCI_SYSINFO		equ 0x0810
MCI_BREAK		equ 0x0811
MCI_SAVE		equ 0x0813
MCI_STATUS		equ 0x0814
MCI_CUE			equ 0x0830
MCI_REALIZE		equ 0x0840
MCI_WINDOW		equ 0x0841
MCI_PUT			equ 0x0842
MCI_WHERE		equ 0x0843
MCI_FREEZE		equ 0x0844
MCI_UNFREEZE		equ 0x0845
MCI_LOAD		equ 0x0850
MCI_CUT			equ 0x0851
MCI_COPY		equ 0x0852
MCI_PASTE		equ 0x0853
MCI_UPDATE		equ 0x0854
MCI_RESUME		equ 0x0855
MCI_DELETE		equ 0x0856

;; all custom MCI command messages must be >= than this value
MCI_USER_MESSAGES	equ (DRV_MCI_FIRST + 0x400)
MCI_LAST		equ 0x0FFF

;; device ID for "all devices"
MCI_ALL_DEVICE_ID	equ -1

;; constants for predefined MCI device types
MCI_DEVTYPE_VCR		equ 513 ;; (MCI_STRING_OFFSET + 1)
MCI_DEVTYPE_VIDEODISC	equ 514 ;; (MCI_STRING_OFFSET + 2)
MCI_DEVTYPE_OVERLAY	equ 515 ;; (MCI_STRING_OFFSET + 3)
MCI_DEVTYPE_CD_AUDIO	equ 516 ;; (MCI_STRING_OFFSET + 4)
MCI_DEVTYPE_DAT		equ 517 ;; (MCI_STRING_OFFSET + 5)
MCI_DEVTYPE_SCANNER	equ 518 ;; (MCI_STRING_OFFSET + 6)
MCI_DEVTYPE_ANIMATION	equ 519 ;; (MCI_STRING_OFFSET + 7)
MCI_DEVTYPE_DIGITAL_VIDEO equ 520 ;; (MCI_STRING_OFFSET + 8)
MCI_DEVTYPE_OTHER	equ 521 ;; (MCI_STRING_OFFSET + 9)
MCI_DEVTYPE_WAVEFORM_AUDIO equ 522 ;; (MCI_STRING_OFFSET + 10)
MCI_DEVTYPE_SEQUENCER	equ 523 ;; (MCI_STRING_OFFSET + 11)

MCI_DEVTYPE_FIRST	equ MCI_DEVTYPE_VCR
MCI_DEVTYPE_LAST	equ MCI_DEVTYPE_SEQUENCER

MCI_DEVTYPE_FIRST_USER	equ 0x1000
;; return values for 'status mode' command
MCI_MODE_NOT_READY	equ (MCI_STRING_OFFSET + 12)
MCI_MODE_STOP		equ (MCI_STRING_OFFSET + 13)
MCI_MODE_PLAY		equ (MCI_STRING_OFFSET + 14)
MCI_MODE_RECORD		equ (MCI_STRING_OFFSET + 15)
MCI_MODE_SEEK		equ (MCI_STRING_OFFSET + 16)
MCI_MODE_PAUSE		equ (MCI_STRING_OFFSET + 17)
MCI_MODE_OPEN		equ (MCI_STRING_OFFSET + 18)

;; constants used in 'set time format' and 'status time format' commands
MCI_FORMAT_MILLISECONDS equ 0
MCI_FORMAT_HMS		equ 1
MCI_FORMAT_MSF		equ 2
MCI_FORMAT_FRAMES	equ 3
MCI_FORMAT_SMPTE_24	equ 4
MCI_FORMAT_SMPTE_25	equ 5
MCI_FORMAT_SMPTE_30	equ 6
MCI_FORMAT_SMPTE_30DROP equ 7
MCI_FORMAT_BYTES	equ 8
MCI_FORMAT_SAMPLES	equ 9
MCI_FORMAT_TMSF		equ 10

;; MCI time format conversion macros
MCI_MSF_MINUTE macro msf
	exitm<msf>
	endm
MCI_MSF_SECOND macro msf
	exitm<((((msf)) SHR 8))>
	endm
MCI_MSF_FRAME macro msf
	exitm<(((msf) SHR 16))>
	endm

MCI_MAKE_MSF macro m, s, f
	exitm<m OR (s shl 8)>
	endm

MCI_TMSF_TRACK macro tmsf
	exitm<((tmsf))>
	endm
MCI_TMSF_MINUTE macro tmsf
	exitm<((((tmsf)) SHR 8))>
	endm
MCI_TMSF_SECOND macro tmsf
	exitm<(((tmsf) SHR 16))>
	endm
MCI_TMSF_FRAME macro tmsf
	exitm<(((tmsf) SHR 24))>
	endm

MCI_MAKE_TMSF macro t, m, s, f
	exitm<(((t OR (( (t or (m shl 8)) or ((s or (f shl 8)) shl 16)))>
	endm

MCI_HMS_HOUR macro hms
	exitm<((hms))>
	endm
MCI_HMS_MINUTE macro hms
	exitm<((((hms)) SHR 8))>
	endm
MCI_HMS_SECOND macro hms
	exitm<(((hms) SHR 16))>
	endm

MCI_MAKE_HMS macro h, m, s
	exitm<h OR (m shl 8) or (s shl 16)>
	endm

;; flags for wParam of MM_MCINOTIFY message
MCI_NOTIFY_SUCCESSFUL	equ 0x0001
MCI_NOTIFY_SUPERSEDED	equ 0x0002
MCI_NOTIFY_ABORTED	equ 0x0004
MCI_NOTIFY_FAILURE	equ 0x0008

;; common flags for dwFlags parameter of MCI command messages
MCI_NOTIFY		equ 0x00000001
MCI_WAIT		equ 0x00000002
MCI_FROM		equ 0x00000004
MCI_TO			equ 0x00000008
MCI_TRACK		equ 0x00000010

;; flags for dwFlags parameter of MCI_OPEN command message
MCI_OPEN_SHAREABLE	equ 0x00000100
MCI_OPEN_ELEMENT	equ 0x00000200
MCI_OPEN_ALIAS		equ 0x00000400
MCI_OPEN_ELEMENT_ID	equ 0x00000800
MCI_OPEN_TYPE_ID	equ 0x00001000
MCI_OPEN_TYPE		equ 0x00002000

;; flags for dwFlags parameter of MCI_SEEK command message
MCI_SEEK_TO_START	equ 0x00000100
MCI_SEEK_TO_END		equ 0x00000200

;; flags for dwFlags parameter of MCI_STATUS command message
MCI_STATUS_ITEM		equ 0x00000100
MCI_STATUS_START	equ 0x00000200

;; flags for dwItem field of the MCI_STATUS_PARMS parameter block
MCI_STATUS_LENGTH	equ 0x00000001
MCI_STATUS_POSITION	equ 0x00000002
MCI_STATUS_NUMBER_OF_TRACKS equ 0x00000003
MCI_STATUS_MODE		equ 0x00000004
MCI_STATUS_MEDIA_PRESENT equ 0x00000005
MCI_STATUS_TIME_FORMAT	equ 0x00000006
MCI_STATUS_READY	equ 0x00000007
MCI_STATUS_CURRENT_TRACK equ 0x00000008

;; flags for dwFlags parameter of MCI_INFO command message
MCI_INFO_PRODUCT	equ 0x00000100
MCI_INFO_FILE		equ 0x00000200
MCI_INFO_MEDIA_UPC	equ 0x00000400
MCI_INFO_MEDIA_IDENTITY equ 0x00000800
MCI_INFO_NAME		equ 0x00001000
MCI_INFO_COPYRIGHT	equ 0x00002000

;; flags for dwFlags parameter of MCI_GETDEVCAPS command message
MCI_GETDEVCAPS_ITEM	equ 0x00000100

;; flags for dwItem field of the MCI_GETDEVCAPS_PARMS parameter block
MCI_GETDEVCAPS_CAN_RECORD equ 0x00000001
MCI_GETDEVCAPS_HAS_AUDIO equ 0x00000002
MCI_GETDEVCAPS_HAS_VIDEO equ 0x00000003
MCI_GETDEVCAPS_DEVICE_TYPE equ 0x00000004
MCI_GETDEVCAPS_USES_FILES equ 0x00000005
MCI_GETDEVCAPS_COMPOUND_DEVICE equ 0x00000006
MCI_GETDEVCAPS_CAN_EJECT equ 0x00000007
MCI_GETDEVCAPS_CAN_PLAY equ 0x00000008
MCI_GETDEVCAPS_CAN_SAVE equ 0x00000009

;; flags for dwFlags parameter of MCI_SYSINFO command message
MCI_SYSINFO_QUANTITY	equ 0x00000100
MCI_SYSINFO_OPEN	equ 0x00000200
MCI_SYSINFO_NAME	equ 0x00000400
MCI_SYSINFO_INSTALLNAME equ 0x00000800

;; flags for dwFlags parameter of MCI_SET command message
MCI_SET_DOOR_OPEN	equ 0x00000100
MCI_SET_DOOR_CLOSED	equ 0x00000200
MCI_SET_TIME_FORMAT	equ 0x00000400
MCI_SET_AUDIO		equ 0x00000800
MCI_SET_VIDEO		equ 0x00001000
MCI_SET_ON		equ 0x00002000
MCI_SET_OFF		equ 0x00004000

;; flags for dwAudio field of MCI_SET_PARMS or MCI_SEQ_SET_PARMS
MCI_SET_AUDIO_ALL	equ 0x00000000
MCI_SET_AUDIO_LEFT	equ 0x00000001
MCI_SET_AUDIO_RIGHT	equ 0x00000002

;; flags for dwFlags parameter of MCI_BREAK command message
MCI_BREAK_KEY		equ 0x00000100
MCI_BREAK_HWND		equ 0x00000200
MCI_BREAK_OFF		equ 0x00000400

;; flags for dwFlags parameter of MCI_RECORD command message
MCI_RECORD_INSERT	equ 0x00000100
MCI_RECORD_OVERWRITE	equ 0x00000200

;; flags for dwFlags parameter of MCI_SAVE command message
MCI_SAVE_FILE		equ 0x00000100

;; flags for dwFlags parameter of MCI_LOAD command message
MCI_LOAD_FILE		equ 0x00000100

;; generic parameter block for MCI command messages with no special parameters
MCI_GENERIC_PARMS	STRUC
dwCallback		dd ?
MCI_GENERIC_PARMS	ENDS
PMCI_GENERIC_PARMS	typedef ptr MCI_GENERIC_PARMS
LPMCI_GENERIC_PARMS	typedef ptr MCI_GENERIC_PARMS

;; parameter block for MCI_OPEN command message
ifdef _WIN32

MCI_OPEN_PARMSA		STRUC
dwCallback		dd ?
wDeviceID		MCIDEVICEID ?
lpstrDeviceType		LPCSTR ?
lpstrElementName	LPCSTR ?
lpstrAlias		LPCSTR ?
MCI_OPEN_PARMSA		ENDS
PMCI_OPEN_PARMSA	typedef ptr MCI_OPEN_PARMSA
LPMCI_OPEN_PARMSA	typedef ptr MCI_OPEN_PARMSA
MCI_OPEN_PARMSW		STRUC
dwCallback		dd ?
wDeviceID		MCIDEVICEID ?
lpstrDeviceType		LPCWSTR ?
lpstrElementName	LPCWSTR ?
lpstrAlias		LPCWSTR ?
MCI_OPEN_PARMSW		ENDS
PMCI_OPEN_PARMSW	typedef ptr MCI_OPEN_PARMSW
LPMCI_OPEN_PARMSW	typedef ptr MCI_OPEN_PARMSW
ifdef _UNICODE
MCI_OPEN_PARMS		typedef MCI_OPEN_PARMSW
PMCI_OPEN_PARMS		typedef PMCI_OPEN_PARMSW
LPMCI_OPEN_PARMS	typedef LPMCI_OPEN_PARMSW
else
MCI_OPEN_PARMS		typedef MCI_OPEN_PARMSA
PMCI_OPEN_PARMS		typedef PMCI_OPEN_PARMSA
LPMCI_OPEN_PARMS	typedef LPMCI_OPEN_PARMSA
endif ;; UNICODE

else
MCI_OPEN_PARMS		STRUC
dwCallback		dd ?
wDeviceID		MCIDEVICEID ?
wReserved0		dw ?
lpstrDeviceType		LPCSTR ?
lpstrElementName	LPCSTR ?
lpstrAlias		LPCSTR ?
MCI_OPEN_PARMS		ENDS
LPMCI_OPEN_PARMS	typedef ptr MCI_OPEN_PARMS
endif

;; parameter block for MCI_PLAY command message
MCI_PLAY_PARMS		STRUC
dwCallback		dd ?
dwFrom			dd ?
dwTo			dd ?
MCI_PLAY_PARMS		ENDS
PMCI_PLAY_PARMS		typedef ptr MCI_PLAY_PARMS
LPMCI_PLAY_PARMS	typedef ptr MCI_PLAY_PARMS

;; parameter block for MCI_SEEK command message
MCI_SEEK_PARMS		STRUC
dwCallback		dd ?
dwTo			dd ?
MCI_SEEK_PARMS		ENDS
PMCI_SEEK_PARMS		typedef ptr MCI_SEEK_PARMS
LPMCI_SEEK_PARMS	typedef ptr MCI_SEEK_PARMS

;; parameter block for MCI_STATUS command message
MCI_STATUS_PARMS	STRUC
dwCallback		dd ?
dwReturn		dd ?
dwItem			dd ?
dwTrack			dd ?
MCI_STATUS_PARMS	ENDS
PMCI_STATUS_PARMS	typedef ptr MCI_STATUS_PARMS
LPMCI_STATUS_PARMS	typedef ptr MCI_STATUS_PARMS

;; parameter block for MCI_INFO command message
ifdef _WIN32

MCI_INFO_PARMSA		STRUC
dwCallback		dd ?
lpstrReturn		LPSTR ?
dwRetSize		dd ?
MCI_INFO_PARMSA		ENDS
 LPMCI_INFO_PARMSA	typedef ptr MCI_INFO_PARMSA
MCI_INFO_PARMSW		STRUC
dwCallback		dd ?
lpstrReturn		LPWSTR ?
dwRetSize		dd ?
MCI_INFO_PARMSW		ENDS
 LPMCI_INFO_PARMSW	typedef ptr MCI_INFO_PARMSW
ifdef _UNICODE
MCI_INFO_PARMS		typedef MCI_INFO_PARMSW
LPMCI_INFO_PARMS	typedef LPMCI_INFO_PARMSW
else
MCI_INFO_PARMS		typedef MCI_INFO_PARMSA
LPMCI_INFO_PARMS	typedef LPMCI_INFO_PARMSA
endif ;; UNICODE

else
MCI_INFO_PARMS		STRUC
dwCallback		dd ?
lpstrReturn		LPSTR ?
dwRetSize		dd ?
MCI_INFO_PARMS		ENDS
 LPMCI_INFO_PARMS	typedef ptr MCI_INFO_PARMS
endif

;; parameter block for MCI_GETDEVCAPS command message
MCI_GETDEVCAPS_PARMS	STRUC
dwCallback		dd ?
dwReturn		dd ?
dwItem			dd ?
MCI_GETDEVCAPS_PARMS	ENDS
PMCI_GETDEVCAPS_PARMS	typedef ptr MCI_GETDEVCAPS_PARMS
 LPMCI_GETDEVCAPS_PARMS typedef ptr MCI_GETDEVCAPS_PARMS

;; parameter block for MCI_SYSINFO command message
ifdef _WIN32

MCI_SYSINFO_PARMSA	STRUC
dwCallback		dd ?
lpstrReturn		LPSTR ?
dwRetSize		dd ?
dwNumber		dd ?
wDeviceType		UINT ?
MCI_SYSINFO_PARMSA	ENDS
PMCI_SYSINFO_PARMSA	typedef ptr MCI_SYSINFO_PARMSA
 LPMCI_SYSINFO_PARMSA	typedef ptr MCI_SYSINFO_PARMSA
MCI_SYSINFO_PARMSW	STRUC
dwCallback		dd ?
lpstrReturn		LPWSTR ?
dwRetSize		dd ?
dwNumber		dd ?
wDeviceType		UINT ?
MCI_SYSINFO_PARMSW	ENDS
PMCI_SYSINFO_PARMSW	typedef ptr MCI_SYSINFO_PARMSW
 LPMCI_SYSINFO_PARMSW	typedef ptr MCI_SYSINFO_PARMSW
ifdef _UNICODE
MCI_SYSINFO_PARMS	typedef MCI_SYSINFO_PARMSW
PMCI_SYSINFO_PARMS	typedef PMCI_SYSINFO_PARMSW
LPMCI_SYSINFO_PARMS	typedef LPMCI_SYSINFO_PARMSW
else
MCI_SYSINFO_PARMS	typedef MCI_SYSINFO_PARMSA
PMCI_SYSINFO_PARMS	typedef PMCI_SYSINFO_PARMSA
LPMCI_SYSINFO_PARMS	typedef LPMCI_SYSINFO_PARMSA
endif ;; UNICODE
else
MCI_SYSINFO_PARMS	STRUC
dwCallback		dd ?
lpstrReturn		LPSTR ?
dwRetSize		dd ?
dwNumber		dd ?
wDeviceType		dw ?
wReserved0		dw ?
MCI_SYSINFO_PARMS	ENDS
 LPMCI_SYSINFO_PARMS	typedef ptr MCI_SYSINFO_PARMS
endif

;; parameter block for MCI_SET command message
MCI_SET_PARMS		STRUC
dwCallback		dd ?
dwTimeFormat		dd ?
dwAudio			dd ?
MCI_SET_PARMS		ENDS
PMCI_SET_PARMS		typedef ptr MCI_SET_PARMS
LPMCI_SET_PARMS		typedef ptr MCI_SET_PARMS

;; parameter block for MCI_BREAK command message
MCI_BREAK_PARMS		STRUC
dwCallback		dd ?
ifdef _WIN32
nVirtKey		SINT ?
hwndBreak		HWND ?
else
nVirtKey		short ?
wReserved0		dw ?	;; padding for Win 16
hwndBreak		HWND ?
wReserved1		dw ?	;; padding for Win 16
endif
MCI_BREAK_PARMS		ENDS
PMCI_BREAK_PARMS	typedef ptr MCI_BREAK_PARMS
 LPMCI_BREAK_PARMS	typedef ptr MCI_BREAK_PARMS

;; parameter block for MCI_SAVE command message
ifdef _WIN32

MCI_SAVE_PARMSA		STRUC
dwCallback		dd ?
lpfilename		LPCSTR ?
MCI_SAVE_PARMSA		ENDS
PMCI_SAVE_PARMSA	typedef ptr MCI_SAVE_PARMSA
 LPMCI_SAVE_PARMSA	typedef ptr MCI_SAVE_PARMSA
MCI_SAVE_PARMSW		STRUC
dwCallback		dd ?
lpfilename		LPCWSTR ?
MCI_SAVE_PARMSW		ENDS
PMCI_SAVE_PARMSW	typedef ptr MCI_SAVE_PARMSW
 LPMCI_SAVE_PARMSW	typedef ptr MCI_SAVE_PARMSW
ifdef _UNICODE
MCI_SAVE_PARMS		typedef MCI_SAVE_PARMSW
PMCI_SAVE_PARMS		typedef PMCI_SAVE_PARMSW
LPMCI_SAVE_PARMS	typedef LPMCI_SAVE_PARMSW
else
MCI_SAVE_PARMS		typedef MCI_SAVE_PARMSA
PMCI_SAVE_PARMS		typedef PMCI_SAVE_PARMSA
LPMCI_SAVE_PARMS	typedef LPMCI_SAVE_PARMSA
endif ;; UNICODE

else
MCI_SAVE_PARMS		STRUC
dwCallback		dd ?
lpfilename		LPCSTR ?
MCI_SAVE_PARMS		ENDS
 LPMCI_SAVE_PARMS	typedef ptr MCI_SAVE_PARMS
endif

;; parameter block for MCI_LOAD command message
ifdef _WIN32

MCI_LOAD_PARMSA		STRUC
dwCallback		dd ?
lpfilename		LPCSTR ?
MCI_LOAD_PARMSA		ENDS
PMCI_LOAD_PARMSA	typedef ptr MCI_LOAD_PARMSA
 LPMCI_LOAD_PARMSA	typedef ptr MCI_LOAD_PARMSA
MCI_LOAD_PARMSW		STRUC
dwCallback		dd ?
lpfilename		LPCWSTR ?
MCI_LOAD_PARMSW		ENDS
PMCI_LOAD_PARMSW	typedef ptr MCI_LOAD_PARMSW
 LPMCI_LOAD_PARMSW	typedef ptr MCI_LOAD_PARMSW
ifdef _UNICODE
MCI_LOAD_PARMS		typedef MCI_LOAD_PARMSW
PMCI_LOAD_PARMS		typedef PMCI_LOAD_PARMSW
LPMCI_LOAD_PARMS	typedef LPMCI_LOAD_PARMSW
else
MCI_LOAD_PARMS		typedef MCI_LOAD_PARMSA
PMCI_LOAD_PARMS		typedef PMCI_LOAD_PARMSA
LPMCI_LOAD_PARMS	typedef LPMCI_LOAD_PARMSA
endif ;; UNICODE

else
MCI_LOAD_PARMS		STRUC
dwCallback		dd ?
lpfilename		LPCSTR ?
MCI_LOAD_PARMS		ENDS
 LPMCI_LOAD_PARMS	typedef ptr MCI_LOAD_PARMS
endif

;; parameter block for MCI_RECORD command message
MCI_RECORD_PARMS	STRUC
dwCallback		dd ?
dwFrom			dd ?
dwTo			dd ?
MCI_RECORD_PARMS	ENDS
LPMCI_RECORD_PARMS	typedef ptr MCI_RECORD_PARMS

;; MCI extensions for videodisc devices

;; flag for dwReturn field of MCI_STATUS_PARMS
;; MCI_STATUS command, (dwItem == MCI_STATUS_MODE)
MCI_VD_MODE_PARK	equ (MCI_VD_OFFSET + 1)

;; flag for dwReturn field of MCI_STATUS_PARMS
;; MCI_STATUS command, (dwItem == MCI_VD_STATUS_MEDIA_TYPE)
MCI_VD_MEDIA_CLV	equ (MCI_VD_OFFSET + 2)
MCI_VD_MEDIA_CAV	equ (MCI_VD_OFFSET + 3)
MCI_VD_MEDIA_OTHER	equ (MCI_VD_OFFSET + 4)

MCI_VD_FORMAT_TRACK	equ 0x4001

;; flags for dwFlags parameter of MCI_PLAY command message
MCI_VD_PLAY_REVERSE	equ 0x00010000
MCI_VD_PLAY_FAST	equ 0x00020000
MCI_VD_PLAY_SPEED	equ 0x00040000
MCI_VD_PLAY_SCAN	equ 0x00080000
MCI_VD_PLAY_SLOW	equ 0x00100000

;; flag for dwFlags parameter of MCI_SEEK command message
MCI_VD_SEEK_REVERSE	equ 0x00010000

;; flags for dwItem field of MCI_STATUS_PARMS parameter block
MCI_VD_STATUS_SPEED	equ 0x00004002
MCI_VD_STATUS_FORWARD	equ 0x00004003
MCI_VD_STATUS_MEDIA_TYPE equ 0x00004004
MCI_VD_STATUS_SIDE	equ 0x00004005
MCI_VD_STATUS_DISC_SIZE equ 0x00004006

;; flags for dwFlags parameter of MCI_GETDEVCAPS command message
MCI_VD_GETDEVCAPS_CLV	equ 0x00010000
MCI_VD_GETDEVCAPS_CAV	equ 0x00020000

MCI_VD_SPIN_UP		equ 0x00010000
MCI_VD_SPIN_DOWN	equ 0x00020000

;; flags for dwItem field of MCI_GETDEVCAPS_PARMS parameter block
MCI_VD_GETDEVCAPS_CAN_REVERSE equ 0x00004002
MCI_VD_GETDEVCAPS_FAST_RATE equ 0x00004003
MCI_VD_GETDEVCAPS_SLOW_RATE equ 0x00004004
MCI_VD_GETDEVCAPS_NORMAL_RATE equ 0x00004005

;; flags for the dwFlags parameter of MCI_STEP command message
MCI_VD_STEP_FRAMES	equ 0x00010000
MCI_VD_STEP_REVERSE	equ 0x00020000

;; flag for the MCI_ESCAPE command message
MCI_VD_ESCAPE_STRING	equ 0x00000100

;; parameter block for MCI_PLAY command message
MCI_VD_PLAY_PARMS	STRUC
dwCallback		dd ?
dwFrom			dd ?
dwTo			dd ?
dwSpeed			dd ?
MCI_VD_PLAY_PARMS	ENDS
PMCI_VD_PLAY_PARMS	typedef ptr MCI_VD_PLAY_PARMS
LPMCI_VD_PLAY_PARMS	typedef ptr MCI_VD_PLAY_PARMS

;; parameter block for MCI_STEP command message
MCI_VD_STEP_PARMS	STRUC
dwCallback		dd ?
dwFrames		dd ?
MCI_VD_STEP_PARMS	ENDS
PMCI_VD_STEP_PARMS	typedef ptr MCI_VD_STEP_PARMS
LPMCI_VD_STEP_PARMS	typedef ptr MCI_VD_STEP_PARMS

;; parameter block for MCI_ESCAPE command message
ifdef _WIN32

MCI_VD_ESCAPE_PARMSA	STRUC
dwCallback		dd ?
lpstrCommand		LPCSTR ?
MCI_VD_ESCAPE_PARMSA	ENDS
PMCI_VD_ESCAPE_PARMSA	typedef ptr MCI_VD_ESCAPE_PARMSA
LPMCI_VD_ESCAPE_PARMSA	typedef ptr MCI_VD_ESCAPE_PARMSA
MCI_VD_ESCAPE_PARMSW	STRUC
dwCallback		dd ?
lpstrCommand		LPCWSTR ?
MCI_VD_ESCAPE_PARMSW	ENDS
PMCI_VD_ESCAPE_PARMSW	typedef ptr MCI_VD_ESCAPE_PARMSW
LPMCI_VD_ESCAPE_PARMSW	typedef ptr MCI_VD_ESCAPE_PARMSW
ifdef _UNICODE
MCI_VD_ESCAPE_PARMS	typedef MCI_VD_ESCAPE_PARMSW
PMCI_VD_ESCAPE_PARMS	typedef PMCI_VD_ESCAPE_PARMSW
LPMCI_VD_ESCAPE_PARMS	typedef LPMCI_VD_ESCAPE_PARMSW
else
MCI_VD_ESCAPE_PARMS	typedef MCI_VD_ESCAPE_PARMSA
PMCI_VD_ESCAPE_PARMS	typedef PMCI_VD_ESCAPE_PARMSA
LPMCI_VD_ESCAPE_PARMS	typedef LPMCI_VD_ESCAPE_PARMSA
endif ;; UNICODE

else
MCI_VD_ESCAPE_PARMS	STRUC
dwCallback		dd ?
lpstrCommand		LPCSTR ?
MCI_VD_ESCAPE_PARMS	ENDS
LPMCI_VD_ESCAPE_PARMS	typedef ptr MCI_VD_ESCAPE_PARMS
endif

;; MCI extensions for CD audio devices

;; flags for the dwItem field of the MCI_STATUS_PARMS parameter block
MCI_CDA_STATUS_TYPE_TRACK equ 0x00004001

;; flags for the dwReturn field of MCI_STATUS_PARMS parameter block
;; MCI_STATUS command, (dwItem == MCI_CDA_STATUS_TYPE_TRACK)
MCI_CDA_TRACK_AUDIO	equ (MCI_CD_OFFSET + 0)
MCI_CDA_TRACK_OTHER	equ (MCI_CD_OFFSET + 1)

;; MCI extensions for waveform audio devices

MCI_WAVE_PCM		equ (MCI_WAVE_OFFSET + 0)
MCI_WAVE_MAPPER		equ (MCI_WAVE_OFFSET + 1)

;; flags for the dwFlags parameter of MCI_OPEN command message
MCI_WAVE_OPEN_BUFFER	equ 0x00010000

;; flags for the dwFlags parameter of MCI_SET command message
MCI_WAVE_SET_FORMATTAG	equ 0x00010000
MCI_WAVE_SET_CHANNELS	equ 0x00020000
MCI_WAVE_SET_SAMPLESPERSEC equ 0x00040000
MCI_WAVE_SET_AVGBYTESPERSEC equ 0x00080000
MCI_WAVE_SET_BLOCKALIGN equ 0x00100000
MCI_WAVE_SET_BITSPERSAMPLE equ 0x00200000

;; flags for the dwFlags parameter of MCI_STATUS, MCI_SET command messages
MCI_WAVE_INPUT		equ 0x00400000
MCI_WAVE_OUTPUT		equ 0x00800000

;; flags for the dwItem field of MCI_STATUS_PARMS parameter block
MCI_WAVE_STATUS_FORMATTAG equ 0x00004001
MCI_WAVE_STATUS_CHANNELS equ 0x00004002
MCI_WAVE_STATUS_SAMPLESPERSEC equ 0x00004003
MCI_WAVE_STATUS_AVGBYTESPERSEC equ 0x00004004
MCI_WAVE_STATUS_BLOCKALIGN equ 0x00004005
MCI_WAVE_STATUS_BITSPERSAMPLE equ 0x00004006
MCI_WAVE_STATUS_LEVEL	equ 0x00004007

;; flags for the dwFlags parameter of MCI_SET command message
MCI_WAVE_SET_ANYINPUT	equ 0x04000000
MCI_WAVE_SET_ANYOUTPUT	equ 0x08000000

;; flags for the dwFlags parameter of MCI_GETDEVCAPS command message
MCI_WAVE_GETDEVCAPS_INPUTS equ 0x00004001
MCI_WAVE_GETDEVCAPS_OUTPUTS equ 0x00004002

;; parameter block for MCI_OPEN command message
ifdef _WIN32

MCI_WAVE_OPEN_PARMSA	STRUC
dwCallback		dd ?
wDeviceID		MCIDEVICEID ?
lpstrDeviceType		LPCSTR ?
lpstrElementName	LPCSTR ?
lpstrAlias		LPCSTR ?
dwBufferSeconds		dd ?
MCI_WAVE_OPEN_PARMSA	ENDS
PMCI_WAVE_OPEN_PARMSA	typedef ptr MCI_WAVE_OPEN_PARMSA
LPMCI_WAVE_OPEN_PARMSA	typedef ptr MCI_WAVE_OPEN_PARMSA
MCI_WAVE_OPEN_PARMSW	STRUC
dwCallback		dd ?
wDeviceID		MCIDEVICEID ?
lpstrDeviceType		LPCWSTR ?
lpstrElementName	LPCWSTR ?
lpstrAlias		LPCWSTR ?
dwBufferSeconds		dd ?
MCI_WAVE_OPEN_PARMSW	ENDS
PMCI_WAVE_OPEN_PARMSW	typedef ptr MCI_WAVE_OPEN_PARMSW
LPMCI_WAVE_OPEN_PARMSW	typedef ptr MCI_WAVE_OPEN_PARMSW
ifdef _UNICODE
MCI_WAVE_OPEN_PARMS	typedef MCI_WAVE_OPEN_PARMSW
PMCI_WAVE_OPEN_PARMS	typedef PMCI_WAVE_OPEN_PARMSW
LPMCI_WAVE_OPEN_PARMS	typedef LPMCI_WAVE_OPEN_PARMSW
else
MCI_WAVE_OPEN_PARMS	typedef MCI_WAVE_OPEN_PARMSA
PMCI_WAVE_OPEN_PARMS	typedef PMCI_WAVE_OPEN_PARMSA
LPMCI_WAVE_OPEN_PARMS	typedef LPMCI_WAVE_OPEN_PARMSA
endif ;; UNICODE

else
MCI_WAVE_OPEN_PARMS	STRUC
dwCallback		dd ?
wDeviceID		MCIDEVICEID ?
wReserved0		dw ?
lpstrDeviceType		LPCSTR ?
lpstrElementName	LPCSTR ?
lpstrAlias		LPCSTR ?
dwBufferSeconds		dd ?
MCI_WAVE_OPEN_PARMS	ENDS
LPMCI_WAVE_OPEN_PARMS	typedef ptr MCI_WAVE_OPEN_PARMS
endif

;; parameter block for MCI_DELETE command message
MCI_WAVE_DELETE_PARMS	STRUC
dwCallback		dd ?
dwFrom			dd ?
dwTo			dd ?
MCI_WAVE_DELETE_PARMS	ENDS
PMCI_WAVE_DELETE_PARMS	typedef ptr MCI_WAVE_DELETE_PARMS
LPMCI_WAVE_DELETE_PARMS typedef ptr MCI_WAVE_DELETE_PARMS

;; parameter block for MCI_SET command message
MCI_WAVE_SET_PARMS	STRUC
dwCallback		dd ?
dwTimeFormat		dd ?
dwAudio			dd ?
ifdef _WIN32
wInput			UINT ?
wOutput			UINT ?
else
wInput			dw ?
wReserved0		dw ?
wOutput			dw ?
wReserved1		dw ?
endif
wFormatTag		dw ?
wReserved2		dw ?
nChannels		dw ?
wReserved3		dw ?
nSamplesPerSec		dd ?
nAvgBytesPerSec		dd ?
nBlockAlign		dw ?
wReserved4		dw ?
wBitsPerSample		dw ?
wReserved5		dw ?
MCI_WAVE_SET_PARMS	ENDS
PMCI_WAVE_SET_PARMS	typedef ptr MCI_WAVE_SET_PARMS
LPMCI_WAVE_SET_PARMS	typedef ptr MCI_WAVE_SET_PARMS

;; MCI extensions for MIDI sequencer devices

;; flags for the dwReturn field of MCI_STATUS_PARMS parameter block
;; MCI_STATUS command, (dwItem == MCI_SEQ_STATUS_DIVTYPE)
MCI_SEQ_DIV_PPQN	equ (0 + MCI_SEQ_OFFSET)
MCI_SEQ_DIV_SMPTE_24	equ (1 + MCI_SEQ_OFFSET)
MCI_SEQ_DIV_SMPTE_25	equ (2 + MCI_SEQ_OFFSET)
MCI_SEQ_DIV_SMPTE_30DROP equ (3 + MCI_SEQ_OFFSET)
MCI_SEQ_DIV_SMPTE_30	equ (4 + MCI_SEQ_OFFSET)

;; flags for the dwMaster field of MCI_SEQ_SET_PARMS parameter block
;; MCI_SET command, (dwFlags == MCI_SEQ_SET_MASTER)
MCI_SEQ_FORMAT_SONGPTR	equ 0x4001
MCI_SEQ_FILE		equ 0x4002
MCI_SEQ_MIDI		equ 0x4003
MCI_SEQ_SMPTE		equ 0x4004
MCI_SEQ_NONE		equ 65533
MCI_SEQ_MAPPER		equ 65535

;; flags for the dwItem field of MCI_STATUS_PARMS parameter block
MCI_SEQ_STATUS_TEMPO	equ 0x00004002
MCI_SEQ_STATUS_PORT	equ 0x00004003
MCI_SEQ_STATUS_SLAVE	equ 0x00004007
MCI_SEQ_STATUS_MASTER	equ 0x00004008
MCI_SEQ_STATUS_OFFSET	equ 0x00004009
MCI_SEQ_STATUS_DIVTYPE	equ 0x0000400A
MCI_SEQ_STATUS_NAME	equ 0x0000400B
MCI_SEQ_STATUS_COPYRIGHT equ 0x0000400C

;; flags for the dwFlags parameter of MCI_SET command message
MCI_SEQ_SET_TEMPO	equ 0x00010000
MCI_SEQ_SET_PORT	equ 0x00020000
MCI_SEQ_SET_SLAVE	equ 0x00040000
MCI_SEQ_SET_MASTER	equ 0x00080000
MCI_SEQ_SET_OFFSET	equ 0x01000000

;; parameter block for MCI_SET command message
MCI_SEQ_SET_PARMS	STRUC
dwCallback		dd ?
dwTimeFormat		dd ?
dwAudio			dd ?
dwTempo			dd ?
dwPort			dd ?
dwSlave			dd ?
dwMaster		dd ?
dwOffset		dd ?
MCI_SEQ_SET_PARMS	ENDS
PMCI_SEQ_SET_PARMS	typedef ptr MCI_SEQ_SET_PARMS
LPMCI_SEQ_SET_PARMS	typedef ptr MCI_SEQ_SET_PARMS

;; MCI extensions for animation devices

;; flags for dwFlags parameter of MCI_OPEN command message
MCI_ANIM_OPEN_WS	equ 0x00010000
MCI_ANIM_OPEN_PARENT	equ 0x00020000
MCI_ANIM_OPEN_NOSTATIC	equ 0x00040000

;; flags for dwFlags parameter of MCI_PLAY command message
MCI_ANIM_PLAY_SPEED	equ 0x00010000
MCI_ANIM_PLAY_REVERSE	equ 0x00020000
MCI_ANIM_PLAY_FAST	equ 0x00040000
MCI_ANIM_PLAY_SLOW	equ 0x00080000
MCI_ANIM_PLAY_SCAN	equ 0x00100000

;; flags for dwFlags parameter of MCI_STEP command message
MCI_ANIM_STEP_REVERSE	equ 0x00010000
MCI_ANIM_STEP_FRAMES	equ 0x00020000

;; flags for dwItem field of MCI_STATUS_PARMS parameter block
MCI_ANIM_STATUS_SPEED	equ 0x00004001
MCI_ANIM_STATUS_FORWARD equ 0x00004002
MCI_ANIM_STATUS_HWND	equ 0x00004003
MCI_ANIM_STATUS_HPAL	equ 0x00004004
MCI_ANIM_STATUS_STRETCH equ 0x00004005

;; flags for the dwFlags parameter of MCI_INFO command message
MCI_ANIM_INFO_TEXT	equ 0x00010000

;; flags for dwItem field of MCI_GETDEVCAPS_PARMS parameter block
MCI_ANIM_GETDEVCAPS_CAN_REVERSE equ 0x00004001
MCI_ANIM_GETDEVCAPS_FAST_RATE equ 0x00004002
MCI_ANIM_GETDEVCAPS_SLOW_RATE equ 0x00004003
MCI_ANIM_GETDEVCAPS_NORMAL_RATE equ 0x00004004
MCI_ANIM_GETDEVCAPS_PALETTES equ 0x00004006
MCI_ANIM_GETDEVCAPS_CAN_STRETCH equ 0x00004007
MCI_ANIM_GETDEVCAPS_MAX_WINDOWS equ 0x00004008

;; flags for the MCI_REALIZE command message
MCI_ANIM_REALIZE_NORM	equ 0x00010000
MCI_ANIM_REALIZE_BKGD	equ 0x00020000

;; flags for dwFlags parameter of MCI_WINDOW command message
MCI_ANIM_WINDOW_HWND	equ 0x00010000
MCI_ANIM_WINDOW_STATE	equ 0x00040000
MCI_ANIM_WINDOW_TEXT	equ 0x00080000
MCI_ANIM_WINDOW_ENABLE_STRETCH equ 0x00100000
MCI_ANIM_WINDOW_DISABLE_STRETCH equ 0x00200000

;; flags for hWnd field of MCI_ANIM_WINDOW_PARMS parameter block
;; MCI_WINDOW command message, (dwFlags == MCI_ANIM_WINDOW_HWND)
MCI_ANIM_WINDOW_DEFAULT equ 0x00000000

;; flags for dwFlags parameter of MCI_PUT command message
MCI_ANIM_RECT		equ 0x00010000
MCI_ANIM_PUT_SOURCE	equ 0x00020000
MCI_ANIM_PUT_DESTINATION equ 0x00040000

;; flags for dwFlags parameter of MCI_WHERE command message
MCI_ANIM_WHERE_SOURCE	equ 0x00020000
MCI_ANIM_WHERE_DESTINATION equ 0x00040000

;; flags for dwFlags parameter of MCI_UPDATE command message
MCI_ANIM_UPDATE_HDC	equ 0x00020000

;; parameter block for MCI_OPEN command message
ifdef _WIN32

MCI_ANIM_OPEN_PARMSA	STRUC
dwCallback		dd ?
wDeviceID		MCIDEVICEID ?
lpstrDeviceType		LPCSTR ?
lpstrElementName	LPCSTR ?
lpstrAlias		LPCSTR ?
dwStyle			dd ?
hWndParent		HWND ?
MCI_ANIM_OPEN_PARMSA	ENDS
PMCI_ANIM_OPEN_PARMSA	typedef ptr MCI_ANIM_OPEN_PARMSA
LPMCI_ANIM_OPEN_PARMSA	typedef ptr MCI_ANIM_OPEN_PARMSA
MCI_ANIM_OPEN_PARMSW	STRUC
dwCallback		dd ?
wDeviceID		MCIDEVICEID ?
lpstrDeviceType		LPCWSTR ?
lpstrElementName	LPCWSTR ?
lpstrAlias		LPCWSTR ?
dwStyle			dd ?
hWndParent		HWND ?
MCI_ANIM_OPEN_PARMSW	ENDS
PMCI_ANIM_OPEN_PARMSW	typedef ptr MCI_ANIM_OPEN_PARMSW
LPMCI_ANIM_OPEN_PARMSW	typedef ptr MCI_ANIM_OPEN_PARMSW
ifdef _UNICODE
MCI_ANIM_OPEN_PARMS	typedef MCI_ANIM_OPEN_PARMSW
PMCI_ANIM_OPEN_PARMS	typedef PMCI_ANIM_OPEN_PARMSW
LPMCI_ANIM_OPEN_PARMS	typedef LPMCI_ANIM_OPEN_PARMSW
else
MCI_ANIM_OPEN_PARMS	typedef MCI_ANIM_OPEN_PARMSA
PMCI_ANIM_OPEN_PARMS	typedef PMCI_ANIM_OPEN_PARMSA
LPMCI_ANIM_OPEN_PARMS	typedef LPMCI_ANIM_OPEN_PARMSA
endif ;; UNICODE

else
MCI_ANIM_OPEN_PARMS	STRUC
dwCallback		dd ?
wDeviceID		MCIDEVICEID ?
wReserved0		dw ?
lpstrDeviceType		LPCSTR ?
lpstrElementName	LPCSTR ?
lpstrAlias		LPCSTR ?
dwStyle			dd ?
hWndParent		HWND ?
wReserved1		dw ?
MCI_ANIM_OPEN_PARMS	ENDS
LPMCI_ANIM_OPEN_PARMS	typedef ptr MCI_ANIM_OPEN_PARMS
endif

;; parameter block for MCI_PLAY command message
MCI_ANIM_PLAY_PARMS	STRUC
dwCallback		dd ?
dwFrom			dd ?
dwTo			dd ?
dwSpeed			dd ?
MCI_ANIM_PLAY_PARMS	ENDS
PMCI_ANIM_PLAY_PARMS	typedef ptr MCI_ANIM_PLAY_PARMS
LPMCI_ANIM_PLAY_PARMS	typedef ptr MCI_ANIM_PLAY_PARMS

;; parameter block for MCI_STEP command message
MCI_ANIM_STEP_PARMS	STRUC
dwCallback		dd ?
dwFrames		dd ?
MCI_ANIM_STEP_PARMS	ENDS
PMCI_ANIM_STEP_PARMS	typedef ptr MCI_ANIM_STEP_PARMS
LPMCI_ANIM_STEP_PARMS	typedef ptr MCI_ANIM_STEP_PARMS

;; parameter block for MCI_WINDOW command message
ifdef _WIN32

MCI_ANIM_WINDOW_PARMSA	STRUC
dwCallback		dd ?
hWnd			HWND ?
nCmdShow		UINT ?
lpstrText		LPCSTR ?
MCI_ANIM_WINDOW_PARMSA	ENDS
PMCI_ANIM_WINDOW_PARMSA typedef ptr MCI_ANIM_WINDOW_PARMSA
 LPMCI_ANIM_WINDOW_PARMSA typedef ptr MCI_ANIM_WINDOW_PARMSA
MCI_ANIM_WINDOW_PARMSW	STRUC
dwCallback		dd ?
hWnd			HWND ?
nCmdShow		UINT ?
lpstrText		LPCWSTR ?
MCI_ANIM_WINDOW_PARMSW	ENDS
PMCI_ANIM_WINDOW_PARMSW typedef ptr MCI_ANIM_WINDOW_PARMSW
 LPMCI_ANIM_WINDOW_PARMSW typedef ptr MCI_ANIM_WINDOW_PARMSW
ifdef _UNICODE
MCI_ANIM_WINDOW_PARMS	typedef MCI_ANIM_WINDOW_PARMSW
PMCI_ANIM_WINDOW_PARMS	typedef PMCI_ANIM_WINDOW_PARMSW
LPMCI_ANIM_WINDOW_PARMS typedef LPMCI_ANIM_WINDOW_PARMSW
else
MCI_ANIM_WINDOW_PARMS	typedef MCI_ANIM_WINDOW_PARMSA
PMCI_ANIM_WINDOW_PARMS	typedef PMCI_ANIM_WINDOW_PARMSA
LPMCI_ANIM_WINDOW_PARMS typedef LPMCI_ANIM_WINDOW_PARMSA
endif ;; UNICODE

else
MCI_ANIM_WINDOW_PARMS	STRUC
dwCallback		dd ?
hWnd			HWND ?
wReserved1		dw ?
nCmdShow		dw ?
wReserved2		dw ?
lpstrText		LPCSTR ?
MCI_ANIM_WINDOW_PARMS	ENDS
LPMCI_ANIM_WINDOW_PARMS typedef ptr MCI_ANIM_WINDOW_PARMS
endif

;; parameter block for MCI_PUT, MCI_UPDATE, MCI_WHERE command messages
MCI_ANIM_RECT_PARMS	STRUC
dwCallback		dd ?
ifdef MCI_USE_OFFEXT
ptOffset		POINT ?
ptExtent		POINT ?
else   ;; ifdef MCI_USE_OFFEXT
rc			RECT <>
endif  ;; ifdef MCI_USE_OFFEXT
MCI_ANIM_RECT_PARMS	ENDS
PMCI_ANIM_RECT_PARMS	typedef ptr MCI_ANIM_RECT_PARMS
LPMCI_ANIM_RECT_PARMS	typedef ptr MCI_ANIM_RECT_PARMS

;; parameter block for MCI_UPDATE PARMS
MCI_ANIM_UPDATE_PARMS	STRUC
dwCallback		dd ?
rc			RECT <>
hDC			HDC ?
MCI_ANIM_UPDATE_PARMS	ENDS
PMCI_ANIM_UPDATE_PARMS	typedef ptr MCI_ANIM_UPDATE_PARMS
LPMCI_ANIM_UPDATE_PARMS typedef ptr MCI_ANIM_UPDATE_PARMS

;; MCI extensions for video overlay devices

;; flags for dwFlags parameter of MCI_OPEN command message
MCI_OVLY_OPEN_WS	equ 0x00010000
MCI_OVLY_OPEN_PARENT	equ 0x00020000

;; flags for dwFlags parameter of MCI_STATUS command message
MCI_OVLY_STATUS_HWND	equ 0x00004001
MCI_OVLY_STATUS_STRETCH equ 0x00004002

;; flags for dwFlags parameter of MCI_INFO command message
MCI_OVLY_INFO_TEXT	equ 0x00010000

;; flags for dwItem field of MCI_GETDEVCAPS_PARMS parameter block
MCI_OVLY_GETDEVCAPS_CAN_STRETCH equ 0x00004001
MCI_OVLY_GETDEVCAPS_CAN_FREEZE equ 0x00004002
MCI_OVLY_GETDEVCAPS_MAX_WINDOWS equ 0x00004003

;; flags for dwFlags parameter of MCI_WINDOW command message
MCI_OVLY_WINDOW_HWND	equ 0x00010000
MCI_OVLY_WINDOW_STATE	equ 0x00040000
MCI_OVLY_WINDOW_TEXT	equ 0x00080000
MCI_OVLY_WINDOW_ENABLE_STRETCH equ 0x00100000
MCI_OVLY_WINDOW_DISABLE_STRETCH equ 0x00200000

;; flags for hWnd parameter of MCI_OVLY_WINDOW_PARMS parameter block
MCI_OVLY_WINDOW_DEFAULT equ 0x00000000

;; flags for dwFlags parameter of MCI_PUT command message
MCI_OVLY_RECT		equ 0x00010000
MCI_OVLY_PUT_SOURCE	equ 0x00020000
MCI_OVLY_PUT_DESTINATION equ 0x00040000
MCI_OVLY_PUT_FRAME	equ 0x00080000
MCI_OVLY_PUT_VIDEO	equ 0x00100000

;; flags for dwFlags parameter of MCI_WHERE command message
MCI_OVLY_WHERE_SOURCE	equ 0x00020000
MCI_OVLY_WHERE_DESTINATION equ 0x00040000
MCI_OVLY_WHERE_FRAME	equ 0x00080000
MCI_OVLY_WHERE_VIDEO	equ 0x00100000

;; parameter block for MCI_OPEN command message
ifdef _WIN32

MCI_OVLY_OPEN_PARMSA	STRUC
dwCallback		dd ?
wDeviceID		MCIDEVICEID ?
lpstrDeviceType		LPCSTR ?
lpstrElementName	LPCSTR ?
lpstrAlias		LPCSTR ?
dwStyle			dd ?
hWndParent		HWND ?
MCI_OVLY_OPEN_PARMSA	ENDS
PMCI_OVLY_OPEN_PARMSA	typedef ptr MCI_OVLY_OPEN_PARMSA
LPMCI_OVLY_OPEN_PARMSA	typedef ptr MCI_OVLY_OPEN_PARMSA
MCI_OVLY_OPEN_PARMSW	STRUC
dwCallback		dd ?
wDeviceID		MCIDEVICEID ?
lpstrDeviceType		LPCWSTR ?
lpstrElementName	LPCWSTR ?
lpstrAlias		LPCWSTR ?
dwStyle			dd ?
hWndParent		HWND ?
MCI_OVLY_OPEN_PARMSW	ENDS
PMCI_OVLY_OPEN_PARMSW	typedef ptr MCI_OVLY_OPEN_PARMSW
LPMCI_OVLY_OPEN_PARMSW	typedef ptr MCI_OVLY_OPEN_PARMSW
ifdef _UNICODE
MCI_OVLY_OPEN_PARMS	typedef MCI_OVLY_OPEN_PARMSW
PMCI_OVLY_OPEN_PARMS	typedef PMCI_OVLY_OPEN_PARMSW
LPMCI_OVLY_OPEN_PARMS	typedef LPMCI_OVLY_OPEN_PARMSW
else
MCI_OVLY_OPEN_PARMS	typedef MCI_OVLY_OPEN_PARMSA
PMCI_OVLY_OPEN_PARMS	typedef PMCI_OVLY_OPEN_PARMSA
LPMCI_OVLY_OPEN_PARMS	typedef LPMCI_OVLY_OPEN_PARMSA
endif ;; UNICODE

else
MCI_OVLY_OPEN_PARMS	STRUC
dwCallback		dd ?
wDeviceID		MCIDEVICEID ?
wReserved0		dw ?
lpstrDeviceType		LPCSTR ?
lpstrElementName	LPCSTR ?
lpstrAlias		LPCSTR ?
dwStyle			dd ?
hWndParent		HWND ?
wReserved1		dw ?
MCI_OVLY_OPEN_PARMS	ENDS
LPMCI_OVLY_OPEN_PARMS	typedef ptr MCI_OVLY_OPEN_PARMS
endif

;; parameter block for MCI_WINDOW command message
ifdef _WIN32

MCI_OVLY_WINDOW_PARMSA	STRUC
dwCallback		dd ?
hWnd			HWND ?
nCmdShow		UINT ?
lpstrText		LPCSTR ?
MCI_OVLY_WINDOW_PARMSA	ENDS
PMCI_OVLY_WINDOW_PARMSA typedef ptr MCI_OVLY_WINDOW_PARMSA
LPMCI_OVLY_WINDOW_PARMSA typedef ptr MCI_OVLY_WINDOW_PARMSA
MCI_OVLY_WINDOW_PARMSW	STRUC
dwCallback		dd ?
hWnd			HWND ?
nCmdShow		UINT ?
lpstrText		LPCWSTR ?
MCI_OVLY_WINDOW_PARMSW	ENDS
PMCI_OVLY_WINDOW_PARMSW typedef ptr MCI_OVLY_WINDOW_PARMSW
LPMCI_OVLY_WINDOW_PARMSW typedef ptr MCI_OVLY_WINDOW_PARMSW
ifdef _UNICODE
MCI_OVLY_WINDOW_PARMS	typedef MCI_OVLY_WINDOW_PARMSW
PMCI_OVLY_WINDOW_PARMS	typedef PMCI_OVLY_WINDOW_PARMSW
LPMCI_OVLY_WINDOW_PARMS typedef LPMCI_OVLY_WINDOW_PARMSW
else
MCI_OVLY_WINDOW_PARMS	typedef MCI_OVLY_WINDOW_PARMSA
PMCI_OVLY_WINDOW_PARMS	typedef PMCI_OVLY_WINDOW_PARMSA
LPMCI_OVLY_WINDOW_PARMS typedef LPMCI_OVLY_WINDOW_PARMSA
endif ;; UNICODE
else
MCI_OVLY_WINDOW_PARMS	STRUC
dwCallback		dd ?
hWnd			HWND ?
wReserved1		dw ?
nCmdShow		UINT ?
wReserved2		dw ?
lpstrText		LPCSTR ?
MCI_OVLY_WINDOW_PARMS	ENDS
LPMCI_OVLY_WINDOW_PARMS typedef ptr MCI_OVLY_WINDOW_PARMS
endif

;; parameter block for MCI_PUT, MCI_UPDATE, and MCI_WHERE command messages
MCI_OVLY_RECT_PARMS	STRUC
dwCallback		dd ?
ifdef MCI_USE_OFFEXT
ptOffset		POINT ?
ptExtent		POINT ?
else   ;; ifdef MCI_USE_OFFEXT
rc			RECT <>
endif  ;; ifdef MCI_USE_OFFEXT
MCI_OVLY_RECT_PARMS	ENDS
PMCI_OVLY_RECT_PARMS	typedef ptr MCI_OVLY_RECT_PARMS
 LPMCI_OVLY_RECT_PARMS	typedef ptr MCI_OVLY_RECT_PARMS

;; parameter block for MCI_SAVE command message
ifdef _WIN32

MCI_OVLY_SAVE_PARMSA	STRUC
dwCallback		dd ?
lpfilename		LPCSTR ?
rc			RECT <>
MCI_OVLY_SAVE_PARMSA	ENDS
PMCI_OVLY_SAVE_PARMSA	typedef ptr MCI_OVLY_SAVE_PARMSA
 LPMCI_OVLY_SAVE_PARMSA typedef ptr MCI_OVLY_SAVE_PARMSA
MCI_OVLY_SAVE_PARMSW	STRUC
dwCallback		dd ?
lpfilename		LPCWSTR ?
rc			RECT <>
MCI_OVLY_SAVE_PARMSW	ENDS
PMCI_OVLY_SAVE_PARMSW	typedef ptr MCI_OVLY_SAVE_PARMSW
 LPMCI_OVLY_SAVE_PARMSW typedef ptr MCI_OVLY_SAVE_PARMSW
ifdef _UNICODE
MCI_OVLY_SAVE_PARMS	typedef MCI_OVLY_SAVE_PARMSW
PMCI_OVLY_SAVE_PARMS	typedef PMCI_OVLY_SAVE_PARMSW
LPMCI_OVLY_SAVE_PARMS	typedef LPMCI_OVLY_SAVE_PARMSW
else
MCI_OVLY_SAVE_PARMS	typedef MCI_OVLY_SAVE_PARMSA
PMCI_OVLY_SAVE_PARMS	typedef PMCI_OVLY_SAVE_PARMSA
LPMCI_OVLY_SAVE_PARMS	typedef LPMCI_OVLY_SAVE_PARMSA
endif ;; UNICODE
else
MCI_OVLY_SAVE_PARMS	STRUC
dwCallback		dd ?
lpfilename		LPCSTR ?
rc			RECT <>
MCI_OVLY_SAVE_PARMS	ENDS
 LPMCI_OVLY_SAVE_PARMS	typedef ptr MCI_OVLY_SAVE_PARMS
endif

;; parameter block for MCI_LOAD command message
ifdef _WIN32

MCI_OVLY_LOAD_PARMSA	STRUC
dwCallback		dd ?
lpfilename		LPCSTR ?
rc			RECT <>
MCI_OVLY_LOAD_PARMSA	ENDS
PMCI_OVLY_LOAD_PARMSA	typedef ptr MCI_OVLY_LOAD_PARMSA
 LPMCI_OVLY_LOAD_PARMSA typedef ptr MCI_OVLY_LOAD_PARMSA
MCI_OVLY_LOAD_PARMSW	STRUC
dwCallback		dd ?
lpfilename		LPCWSTR ?
rc			RECT <>
MCI_OVLY_LOAD_PARMSW	ENDS
PMCI_OVLY_LOAD_PARMSW	typedef ptr MCI_OVLY_LOAD_PARMSW
 LPMCI_OVLY_LOAD_PARMSW typedef ptr MCI_OVLY_LOAD_PARMSW
ifdef _UNICODE
MCI_OVLY_LOAD_PARMS	typedef MCI_OVLY_LOAD_PARMSW
PMCI_OVLY_LOAD_PARMS	typedef PMCI_OVLY_LOAD_PARMSW
LPMCI_OVLY_LOAD_PARMS	typedef LPMCI_OVLY_LOAD_PARMSW
else
MCI_OVLY_LOAD_PARMS	typedef MCI_OVLY_LOAD_PARMSA
PMCI_OVLY_LOAD_PARMS	typedef PMCI_OVLY_LOAD_PARMSA
LPMCI_OVLY_LOAD_PARMS	typedef LPMCI_OVLY_LOAD_PARMSA
endif ;; UNICODE
else
MCI_OVLY_LOAD_PARMS	STRUC
dwCallback		dd ?
lpfilename		LPCSTR ?
rc			RECT <>
MCI_OVLY_LOAD_PARMS	ENDS
LPMCI_OVLY_LOAD_PARMS	typedef ptr MCI_OVLY_LOAD_PARMS
endif

endif  ;; ifndef _WIN32_VXD
endif  ;; ifndef MMNOMCI

;;***************************************************************************
;;
;; Driver extensions	   DISPLAY ?
;;
;;**************************************************************************

ifndef NEWTRANSPARENT
NEWTRANSPARENT		equ 3		;; use with SetBkMode()

QUERYROPSUPPORT		equ 40		;; use to determine ROP support
endif  ;; ifndef NEWTRANSPARENT

;;***************************************************************************
;;
;; DIB Driver extensions
;;
;;**************************************************************************

SELECTDIB		equ 41			    ;; DIB.DRV select dib escape
DIBINDEX macro n
	exitm<MAKEONG(n,0x10FF)>
	endm

;;**************************************************************************
;;
;; ScreenSaver support
;;
;; current application will receive a syscommand of SC_SCREENSAVE just The ?
;; the screen saver is invoked.	 If the app wishes to prevent a before ?
;; save, return non-zero value, otherwise call DefWindowProc(). screen ?
;;
;;**************************************************************************

ifndef SC_SCREENSAVE

SC_SCREENSAVE		equ 0xF140

endif  ;; ifndef SC_SCREENSAVE
endif  ;; _INC_MMSYSTEM

.list
