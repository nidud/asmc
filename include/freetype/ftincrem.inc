ifndef FTINCREM_H_
define FTINCREM_H_

include freetype/freetype.inc
include freetype/ftparams.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_Incremental		typedef ptr FT_IncrementalRec

FT_Incremental_MetricsRec STRUC
bearing_x		FT_Long ?
bearing_y		FT_Long ?
advance			FT_Long ?
advance_v		FT_Long ?
FT_Incremental_MetricsRec ENDS
FT_Incremental_Metrics	typedef ptr FT_Incremental_MetricsRec

CALLBACKC(FT_Incremental_GetGlyphDataFunc, :FT_Incremental, :FT_UInt, :ptr FT_Data)
CALLBACKC(FT_Incremental_FreeGlyphDataFunc, :FT_Incremental, :ptr FT_Data)
CALLBACKC(FT_Incremental_GetGlyphMetricsFunc, :FT_Incremental, :FT_UInt, :FT_Bool, :ptr FT_Incremental_MetricsRec)

FT_Incremental_FuncsRec STRUC
get_glyph_data		FT_Incremental_GetGlyphDataFunc ?
free_glyph_data		FT_Incremental_FreeGlyphDataFunc ?
get_glyph_metrics	FT_Incremental_GetGlyphMetricsFunc ?
FT_Incremental_FuncsRec ENDS

FT_Incremental_InterfaceRec STRUC
funcs			ptr FT_Incremental_FuncsRec ?
object			FT_Incremental ?
FT_Incremental_InterfaceRec ENDS
FT_Incremental_Interface typedef ptr FT_Incremental_InterfaceRec

endif
