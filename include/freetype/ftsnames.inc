ifndef FTSNAMES_H_
define FTSNAMES_H_

include freetype/freetype.inc
include freetype/ftparams.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_SfntName		STRUC
platform_id		FT_UShort ?
encoding_id		FT_UShort ?
language_id		FT_UShort ?
name_id			FT_UShort ?
string			ptr FT_Byte ?
string_len		FT_UInt ?
FT_SfntName		ENDS

FT_Get_Sfnt_Name_Count proto \
		  face: FT_Face

FT_Get_Sfnt_Name proto \
		  face: FT_Face,
		   idx: FT_UInt,
		 aname: ptr FT_SfntName

FT_SfntLangTag		STRUC
string			ptr FT_Byte ?
string_len		FT_UInt ?
FT_SfntLangTag		ENDS

FT_Get_Sfnt_LangTag proto \
		  face: FT_Face,
		langID: FT_UInt,
	      alangTag: ptr FT_SfntLangTag

endif
