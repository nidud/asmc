ifndef _FCFREETYPE_H_
define _FCFREETYPE_H_
include ft2build.inc
%include FT_FREETYPE_H

ifndef FcPublic
define FcPublic
endif

FcFreeTypeCharIndex		proto :FT_Face, :FcChar32
FcFreeTypeCharSetAndSpacing	proto :FT_Face, :ptr FcBlanks, :ptr
FcFreeTypeCharSet		proto :FT_Face, :ptr FcBlanks
FcPatternGetFTFace		proto :ptr FcPattern, :ptr, :int_t, :ptr FT_Face
FcPatternAddFTFace		proto :ptr FcPattern, :ptr, :FT_Face
FcFreeTypeQueryFace		proto :FT_Face, :ptr FcChar8, :uint_t, :ptr FcBlanks

endif
