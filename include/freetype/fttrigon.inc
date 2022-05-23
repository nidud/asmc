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

FT_Sin proto \
                 angle: FT_Angle

FT_Cos proto \
                 angle: FT_Angle

FT_Tan proto \
                 angle: FT_Angle

FT_Atan2 proto \
                     x: FT_Fixed,
                     y: FT_Fixed

FT_Angle_Diff proto \
                angle1: FT_Angle,
                angle2: FT_Angle

FT_Vector_Unit proto \
                   vec: ptr FT_Vector,
                 angle: FT_Angle

FT_Vector_Rotate proto \
                   vec: ptr FT_Vector,
                 angle: FT_Angle

FT_Vector_Length proto \
                   vec: ptr FT_Vector

FT_Vector_Polarize proto \
                   vec: ptr FT_Vector,
                length: ptr FT_Fixed,
                 angle: ptr FT_Angle

FT_Vector_From_Polar proto \
                   vec: ptr FT_Vector,
                length: FT_Fixed,
                 angle: FT_Angle

endif
