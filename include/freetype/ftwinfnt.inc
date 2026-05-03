ifndef FTWINFNT_H_
define FTWINFNT_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

define FT_WinFNT_ID_CP1252    0
define FT_WinFNT_ID_DEFAULT   1
define FT_WinFNT_ID_SYMBOL    2
define FT_WinFNT_ID_MAC	     77
define FT_WinFNT_ID_CP932   128
define FT_WinFNT_ID_CP949   129
define FT_WinFNT_ID_CP1361  130
define FT_WinFNT_ID_CP936   134
define FT_WinFNT_ID_CP950   136
define FT_WinFNT_ID_CP1253  161
define FT_WinFNT_ID_CP1254  162
define FT_WinFNT_ID_CP1258  163
define FT_WinFNT_ID_CP1255  177
define FT_WinFNT_ID_CP1256  178
define FT_WinFNT_ID_CP1257  186
define FT_WinFNT_ID_CP1251  204
define FT_WinFNT_ID_CP874   222
define FT_WinFNT_ID_CP1250  238
define FT_WinFNT_ID_OEM	    255

FT_WinFNT_HeaderRec	STRUC
version			FT_UShort ?
file_size		FT_ULong ?
copyright		FT_Byte 60 dup(?)
file_type		FT_UShort ?
nominal_point_size	FT_UShort ?
vertical_resolution	FT_UShort ?
horizontal_resolution	FT_UShort ?
ascent			FT_UShort ?
internal_leading	FT_UShort ?
external_leading	FT_UShort ?
italic			FT_Byte ?
underline		FT_Byte ?
strike_out		FT_Byte ?
weight			FT_UShort ?
charset			FT_Byte ?
pixel_width		FT_UShort ?
pixel_height		FT_UShort ?
pitch_and_family	FT_Byte ?
avg_width		FT_UShort ?
max_width		FT_UShort ?
first_char		FT_Byte ?
last_char		FT_Byte ?
default_char		FT_Byte ?
break_char		FT_Byte ?
bytes_per_row		FT_UShort ?
device_offset		FT_ULong ?
face_name_offset	FT_ULong ?
bits_pointer		FT_ULong ?
bits_offset		FT_ULong ?
reserved		FT_Byte ?
flags			FT_ULong ?
A_space			FT_UShort ?
B_space			FT_UShort ?
C_space			FT_UShort ?
color_table_offset	FT_UShort ?
reserved1		FT_ULong 4 dup(?)
FT_WinFNT_HeaderRec	ENDS

FT_WinFNT_Header	typedef ptr FT_WinFNT_HeaderRec

FT_Get_WinFNT_Header proto :FT_Face, :ptr

endif
