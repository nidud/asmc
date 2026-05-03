ifndef __AMAUDIO__
define __AMAUDIO__
.pragma list(push, 0)
include mmsystem.inc
include dsound.inc

.comdef IAMDirectSound : public IUnknown

	GetDirectSoundInterface proc :ptr
	GetPrimaryBufferInterface proc :ptr
	GetSecondaryBufferInterface proc :ptr
	ReleaseDirectSoundInterface proc :LPDIRECTSOUND
	ReleasePrimaryBufferInterface proc :LPDIRECTSOUNDBUFFER
	ReleaseSecondaryBufferInterface proc :LPDIRECTSOUNDBUFFER
	SetFocusWindow	proc :HWND, :BOOL
	GetFocusWindow	proc :ptr, :ptr
	.ends

.pragma list(pop)
endif


