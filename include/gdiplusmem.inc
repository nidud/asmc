ifndef _GDIPLUSMEM_H
_GDIPLUSMEM_H equ <>

ifndef WINGDIPAPI
WINGDIPAPI equ <>
ifdef __PE__
option dllimport:<gdiplus>
else
includelib gdiplus.lib
endif
endif

;void*
GdipAlloc proto WINAPI _size: size_t
;void
GdipFree proto WINAPI

endif

