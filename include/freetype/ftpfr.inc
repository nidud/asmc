ifndef FTPFR_H_
define FTPFR_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

FT_Get_PFR_Metrics proto \
                  face: FT_Face,
   aoutline_resolution: ptr FT_UInt,
   ametrics_resolution: ptr FT_UInt,
      ametrics_x_scale: ptr FT_Fixed,
      ametrics_y_scale: ptr FT_Fixed

FT_Get_PFR_Kerning proto \
                  face: FT_Face,
                  left: FT_UInt,
                 right: FT_UInt,
               avector: ptr FT_Vector

FT_Get_PFR_Advance proto \
                  face: FT_Face,
                gindex: FT_UInt,
              aadvance: ptr FT_Pos

endif
