
ifndef FTGXVAL_H_
define FTGXVAL_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

define FT_VALIDATE_feat_INDEX	  0
define FT_VALIDATE_mort_INDEX	  1
define FT_VALIDATE_morx_INDEX	  2
define FT_VALIDATE_bsln_INDEX	  3
define FT_VALIDATE_just_INDEX	  4
define FT_VALIDATE_kern_INDEX	  5
define FT_VALIDATE_opbd_INDEX	  6
define FT_VALIDATE_trak_INDEX	  7
define FT_VALIDATE_prop_INDEX	  8
define FT_VALIDATE_lcar_INDEX	  9
define FT_VALIDATE_GX_LAST_INDEX  FT_VALIDATE_lcar_INDEX


FT_VALIDATE_GX_LENGTH	equ ( FT_VALIDATE_GX_LAST_INDEX + 1 )

define FT_VALIDATE_GX_START  0x4000
FT_VALIDATE_GX_BITFIELD macro tag
	exitm<( FT_VALIDATE_GX_START SHL FT_VALIDATE_&tag&_INDEX )>
	endm


FT_VALIDATE_feat	equ FT_VALIDATE_GX_BITFIELD( feat )
FT_VALIDATE_mort	equ FT_VALIDATE_GX_BITFIELD( mort )
FT_VALIDATE_morx	equ FT_VALIDATE_GX_BITFIELD( morx )
FT_VALIDATE_bsln	equ FT_VALIDATE_GX_BITFIELD( bsln )
FT_VALIDATE_just	equ FT_VALIDATE_GX_BITFIELD( just )
FT_VALIDATE_kern	equ FT_VALIDATE_GX_BITFIELD( kern )
FT_VALIDATE_opbd	equ FT_VALIDATE_GX_BITFIELD( opbd )
FT_VALIDATE_trak	equ FT_VALIDATE_GX_BITFIELD( trak )
FT_VALIDATE_prop	equ FT_VALIDATE_GX_BITFIELD( prop )
FT_VALIDATE_lcar	equ FT_VALIDATE_GX_BITFIELD( lcar )

FT_VALIDATE_GX		equ ( FT_VALIDATE_feat OR FT_VALIDATE_mort OR FT_VALIDATE_morx OR FT_VALIDATE_bsln OR FT_VALIDATE_just OR FT_VALIDATE_kern OR FT_VALIDATE_opbd OR FT_VALIDATE_trak OR FT_VALIDATE_prop OR FT_VALIDATE_lcar )

FT_TrueTypeGX_Validate proto \
		  face: FT_Face,
      validation_flags: FT_UInt,
		tables: ptr FT_Bytes,
	  table_length: FT_UInt

FT_TrueTypeGX_Free proto \
		  face: FT_Face,
		 table: FT_Bytes


FT_VALIDATE_MS		equ ( FT_VALIDATE_GX_START SHL 0 )
FT_VALIDATE_APPLE	equ ( FT_VALIDATE_GX_START SHL 1 )
FT_VALIDATE_CKERN	equ ( FT_VALIDATE_MS OR FT_VALIDATE_APPLE )


FT_ClassicKern_Validate proto \
		  face: FT_Face,
      validation_flags: FT_UInt,
	   ckern_table: ptr FT_Bytes

FT_ClassicKern_Free proto \
		  face: FT_Face,
		 table: FT_Bytes

endif
