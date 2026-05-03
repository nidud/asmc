.pragma list(push, 0)
ifndef _GDIPLUS_H
define _GDIPLUS_H
include windef.inc

INT16           typedef sword
UINT16          typedef word
ifndef GDIPVER
GDIPVER         equ 0x0110;0x0100
endif

.pragma comment(lib, gdiplus)

.pragma pack(push, size_t)

include gdiplusmem.inc
include gdiplusbase.inc
include gdiplusenums.inc
include gdiplustypes.inc
include gdiplusinit.inc
include gdipluspixelformats.inc
include gdipluscolor.inc
include gdiplusmetaheader.inc
include gdiplusimaging.inc
include gdipluscolormatrix.inc
if (GDIPVER GE 0x0110)
include gdipluseffects.inc
endif
include gdiplusgpstubs.inc
include gdiplusheaders.inc
include gdiplusflat.inc
include gdiplusimageattributes.inc
include gdiplusmatrix.inc
include gdiplusbrush.inc
include gdipluspen.inc
include gdiplusstringformat.inc
include gdipluspath.inc
include gdipluslinecaps.inc
include gdiplusgraphics.inc
include gdiplusmetafile.inc
include gdipluscachedbitmap.inc
include gdiplusregion.inc
include gdiplusfontcollection.inc
include gdiplusfontfamily.inc
include gdiplusfont.inc
include gdiplusbitmap.inc
include gdiplusimagecodec.inc

.pragma pack(pop)
endif
.pragma list(pop)
