ifndef FTTRIGON_H_
define FTTRIGON_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_Angle                typedef FT_Fixed

FT_ANGLE_PI             equ ( 180 SHL 16 )
FT_ANGLE_2PI            equ ( FT_ANGLE_PI * 2 )
FT_ANGLE_PI2            equ ( FT_ANGLE_PI / 2 )
FT_ANGLE_PI4            equ ( FT_ANGLE_PI / 4 )

FT_Sin proto :FT_Angle
FT_Cos proto :FT_Angle
FT_Tan proto :FT_Angle
FT_Atan2 proto :FT_Fixed, :FT_Fixed
FT_Angle_Diff proto :FT_Angle, :FT_Angle
FT_Vector_Unit proto :ptr, :FT_Angle
FT_Vector_Rotate proto :ptr, :FT_Angle
FT_Vector_Length proto :ptr
FT_Vector_Polarize proto :ptr, :ptr, :ptr
FT_Vector_From_Polar proto :ptr, :FT_Fixed, :FT_Angle

endif
