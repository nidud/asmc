ifndef __AMAUDIO__
__AMAUDIO__ equ <>

include mmsystem.inc
include dsound.inc

.comdef IAMDirectSound

	QueryInterface	proc :REFIID, :PVOID
	AddRef		proc
	Release		proc

	GetDirectSoundInterface proc :ptr LPDIRECTSOUND
	GetPrimaryBufferInterface proc :ptr LPDIRECTSOUNDBUFFER
	GetSecondaryBufferInterface proc :ptr LPDIRECTSOUNDBUFFER
	ReleaseDirectSoundInterface proc :LPDIRECTSOUND
	ReleasePrimaryBufferInterface proc :LPDIRECTSOUNDBUFFER
	ReleaseSecondaryBufferInterface proc :LPDIRECTSOUNDBUFFER
	SetFocusWindow	proc :HWND, :BOOL
	GetFocusWindow	proc :ptr HWND, :ptr BOOL
	.ends

endif


