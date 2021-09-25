ifndef __AMAUDIO__
define __AMAUDIO__
.pragma list(push, 0)
include mmsystem.inc
include dsound.inc

.comdef IAMDirectSound : public IUnknown

	GetDirectSoundInterface proc :ptr LPDIRECTSOUND
	GetPrimaryBufferInterface proc :ptr LPDIRECTSOUNDBUFFER
	GetSecondaryBufferInterface proc :ptr LPDIRECTSOUNDBUFFER
	ReleaseDirectSoundInterface proc :LPDIRECTSOUND
	ReleasePrimaryBufferInterface proc :LPDIRECTSOUNDBUFFER
	ReleaseSecondaryBufferInterface proc :LPDIRECTSOUNDBUFFER
	SetFocusWindow	proc :HWND, :BOOL
	GetFocusWindow	proc :ptr HWND, :ptr BOOL
	.ends

.pragma list(pop)
endif


