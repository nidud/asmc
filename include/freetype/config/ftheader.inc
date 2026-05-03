ifndef FTHEADER_H_
define FTHEADER_H_

ifndef FT_BEGIN_HEADER
  ifdef __cplusplus
    define FT_BEGIN_HEADER <extern "C" {>
  else
    define FT_BEGIN_HEADER <>
  endif
endif

ifndef FT_END_HEADER
  ifdef __cplusplus
    define FT_END_HEADER <}>
  else
    define FT_END_HEADER <>
  endif
endif

ifndef FT_CONFIG_CONFIG_H
define FT_CONFIG_CONFIG_H <freetype/config/ftconfig.inc>
endif

ifndef FT_CONFIG_STANDARD_LIBRARY_H
define FT_CONFIG_STANDARD_LIBRARY_H <freetype/config/ftstdlib.inc>
endif

ifndef FT_CONFIG_OPTIONS_H
define FT_CONFIG_OPTIONS_H <freetype/config/ftoption.inc>
endif

ifndef FT_CONFIG_MODULES_H
define FT_CONFIG_MODULES_H <freetype/config/ftmodule.inc>
endif

define FT_FREETYPE_H <freetype/freetype.inc>
define FT_ERRORS_H <freetype/fterrors.inc>
define FT_MODULE_ERRORS_H <freetype/ftmoderr.inc>
define FT_SYSTEM_H <freetype/ftsystem.inc>
define FT_IMAGE_H <freetype/ftimage.inc>
define FT_TYPES_H <freetype/fttypes.inc>
define FT_LIST_H <freetype/ftlist.inc>
define FT_OUTLINE_H <freetype/ftoutln.inc>
define FT_SIZES_H <freetype/ftsizes.inc>
define FT_MODULE_H <freetype/ftmodapi.inc>
define FT_RENDER_H <freetype/ftrender.inc>
define FT_DRIVER_H <freetype/ftdriver.inc>
define FT_AUTOHINTER_H  FT_DRIVER_H
define FT_CFF_DRIVER_H  FT_DRIVER_H
define FT_TRUETYPE_DRIVER_H  FT_DRIVER_H
define FT_PCF_DRIVER_H  FT_DRIVER_H
define FT_TYPE1_TABLES_H <freetype/t1tables.inc>
define FT_TRUETYPE_IDS_H <freetype/ttnameid.inc>
define FT_TRUETYPE_TABLES_H <freetype/tttables.inc>
define FT_TRUETYPE_TAGS_H <freetype/tttags.inc>
define FT_BDF_H <freetype/ftbdf.inc>
define FT_CID_H <freetype/ftcid.inc>
define FT_GZIP_H <freetype/ftgzip.inc>
define FT_LZW_H <freetype/ftlzw.inc>
define FT_BZIP2_H <freetype/ftbzip2.inc>
define FT_WINFONTS_H <freetype/ftwinfnt.inc>
define FT_GLYPH_H <freetype/ftglyph.inc>
define FT_BITMAP_H <freetype/ftbitmap.inc>
define FT_BBOX_H <freetype/ftbbox.inc>
define FT_CACHE_H <freetype/ftcache.inc>
define FT_MAC_H <freetype/ftmac.inc>
define FT_MULTIPLE_MASTERS_H <freetype/ftmm.inc>
define FT_SFNT_NAMES_H <freetype/ftsnames.inc>
define FT_OPENTYPE_VALIDATE_H <freetype/ftotval.inc>
define FT_GX_VALIDATE_H <freetype/ftgxval.inc>
define FT_PFR_H <freetype/ftpfr.inc>
define FT_STROKER_H <freetype/ftstroke.inc>
define FT_SYNTHESIS_H <freetype/ftsynth.inc>
define FT_FONT_FORMATS_H <freetype/ftfntfmt.inc>
define FT_XFREE86_H  FT_FONT_FORMATS_H
define FT_TRIGONOMETRY_H <freetype/fttrigon.inc>
define FT_LCD_FILTER_H <freetype/ftlcdfil.inc>
define FT_INCREMENTAL_H <freetype/ftincrem.inc>
define FT_GASP_H <freetype/ftgasp.inc>
define FT_ADVANCES_H <freetype/ftadvanc.inc>
define FT_COLOR_H <freetype/ftcolor.inc>
define FT_OTSVG_H <freetype/otsvg.inc>

define FT_ERROR_DEFINITIONS_H <freetype/fterrdef.inc>
define FT_PARAMETER_TAGS_H <freetype/ftparams.inc>

define FT_UNPATENTED_HINTING_H <freetype/ftparams.inc>
define FT_TRUETYPE_UNPATENTED_H <freetype/ftparams.inc>

define FT_CACHE_IMAGE_H          FT_CACHE_H
define FT_CACHE_SMALL_BITMAPS_H  FT_CACHE_H
define FT_CACHE_CHARMAP_H        FT_CACHE_H

define FT_CACHE_MANAGER_H           FT_CACHE_H
define FT_CACHE_INTERNAL_MRU_H      FT_CACHE_H
define FT_CACHE_INTERNAL_MANAGER_H  FT_CACHE_H
define FT_CACHE_INTERNAL_CACHE_H    FT_CACHE_H
define FT_CACHE_INTERNAL_GLYPH_H    FT_CACHE_H
define FT_CACHE_INTERNAL_IMAGE_H    FT_CACHE_H
define FT_CACHE_INTERNAL_SBITS_H    FT_CACHE_H

ifdef FT2_BUILD_LIBRARY
ifdef _MSC_VER
endif
endif

endif
