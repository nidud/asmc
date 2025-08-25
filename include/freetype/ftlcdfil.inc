ifndef FTLCDFIL_H_
define FTLCDFIL_H_

include freetype/freetype.inc
include freetype/ftparams.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

.enum FT_LcdFilter {
    FT_LCD_FILTER_NONE    = 0,
    FT_LCD_FILTER_DEFAULT = 1,
    FT_LCD_FILTER_LIGHT   = 2,
    FT_LCD_FILTER_LEGACY1 = 3,
    FT_LCD_FILTER_LEGACY  = 16,
    FT_LCD_FILTER_MAX
    }

FT_Library_SetLcdFilter proto :FT_Library, :FT_LcdFilter
FT_Library_SetLcdFilterWeights proto :FT_Library, :ptr

define FT_LCD_FILTER_FIVE_TAPS  5

FT_Library_SetLcdGeometry proto :FT_Library, :ptr

endif

