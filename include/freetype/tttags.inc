ifndef TTAGS_H_
define TTAGS_H_

include freetype/freetype.inc

ifdef FREETYPE_H
.err <"freetype.h of FreeType 1 has been loaded!">
.err <"Please fix the directory search order for header files">
.err <"so that freetype.h of FreeType 2 is found first.">
endif

TTAG_avar               equ FT_MAKE_TAG( 'a', 'v', 'a', 'r' )
TTAG_BASE               equ FT_MAKE_TAG( 'B', 'A', 'S', 'E' )
TTAG_bdat               equ FT_MAKE_TAG( 'b', 'd', 'a', 't' )
TTAG_BDF                equ FT_MAKE_TAG( 'B', 'D', 'F', ' ' )
TTAG_bhed               equ FT_MAKE_TAG( 'b', 'h', 'e', 'd' )
TTAG_bloc               equ FT_MAKE_TAG( 'b', 'l', 'o', 'c' )
TTAG_bsln               equ FT_MAKE_TAG( 'b', 's', 'l', 'n' )
TTAG_CBDT               equ FT_MAKE_TAG( 'C', 'B', 'D', 'T' )
TTAG_CBLC               equ FT_MAKE_TAG( 'C', 'B', 'L', 'C' )
TTAG_CFF                equ FT_MAKE_TAG( 'C', 'F', 'F', ' ' )
TTAG_CFF2               equ FT_MAKE_TAG( 'C', 'F', 'F', '2' )
TTAG_CID                equ FT_MAKE_TAG( 'C', 'I', 'D', ' ' )
TTAG_cmap               equ FT_MAKE_TAG( 'c', 'm', 'a', 'p' )
TTAG_COLR               equ FT_MAKE_TAG( 'C', 'O', 'L', 'R' )
TTAG_CPAL               equ FT_MAKE_TAG( 'C', 'P', 'A', 'L' )
TTAG_cvar               equ FT_MAKE_TAG( 'c', 'v', 'a', 'r' )
TTAG_cvt                equ FT_MAKE_TAG( 'c', 'v', 't', ' ' )
TTAG_DSIG               equ FT_MAKE_TAG( 'D', 'S', 'I', 'G' )
TTAG_EBDT               equ FT_MAKE_TAG( 'E', 'B', 'D', 'T' )
TTAG_EBLC               equ FT_MAKE_TAG( 'E', 'B', 'L', 'C' )
TTAG_EBSC               equ FT_MAKE_TAG( 'E', 'B', 'S', 'C' )
TTAG_feat               equ FT_MAKE_TAG( 'f', 'e', 'a', 't' )
TTAG_FOND               equ FT_MAKE_TAG( 'F', 'O', 'N', 'D' )
TTAG_fpgm               equ FT_MAKE_TAG( 'f', 'p', 'g', 'm' )
TTAG_fvar               equ FT_MAKE_TAG( 'f', 'v', 'a', 'r' )
TTAG_gasp               equ FT_MAKE_TAG( 'g', 'a', 's', 'p' )
TTAG_GDEF               equ FT_MAKE_TAG( 'G', 'D', 'E', 'F' )
TTAG_glyf               equ FT_MAKE_TAG( 'g', 'l', 'y', 'f' )
TTAG_GPOS               equ FT_MAKE_TAG( 'G', 'P', 'O', 'S' )
TTAG_GSUB               equ FT_MAKE_TAG( 'G', 'S', 'U', 'B' )
TTAG_gvar               equ FT_MAKE_TAG( 'g', 'v', 'a', 'r' )
TTAG_HVAR               equ FT_MAKE_TAG( 'H', 'V', 'A', 'R' )
TTAG_hdmx               equ FT_MAKE_TAG( 'h', 'd', 'm', 'x' )
TTAG_head               equ FT_MAKE_TAG( 'h', 'e', 'a', 'd' )
TTAG_hhea               equ FT_MAKE_TAG( 'h', 'h', 'e', 'a' )
TTAG_hmtx               equ FT_MAKE_TAG( 'h', 'm', 't', 'x' )
TTAG_JSTF               equ FT_MAKE_TAG( 'J', 'S', 'T', 'F' )
TTAG_just               equ FT_MAKE_TAG( 'j', 'u', 's', 't' )
TTAG_kern               equ FT_MAKE_TAG( 'k', 'e', 'r', 'n' )
TTAG_lcar               equ FT_MAKE_TAG( 'l', 'c', 'a', 'r' )
TTAG_loca               equ FT_MAKE_TAG( 'l', 'o', 'c', 'a' )
TTAG_LTSH               equ FT_MAKE_TAG( 'L', 'T', 'S', 'H' )
TTAG_LWFN               equ FT_MAKE_TAG( 'L', 'W', 'F', 'N' )
TTAG_MATH               equ FT_MAKE_TAG( 'M', 'A', 'T', 'H' )
TTAG_maxp               equ FT_MAKE_TAG( 'm', 'a', 'x', 'p' )
TTAG_META               equ FT_MAKE_TAG( 'M', 'E', 'T', 'A' )
TTAG_MMFX               equ FT_MAKE_TAG( 'M', 'M', 'F', 'X' )
TTAG_MMSD               equ FT_MAKE_TAG( 'M', 'M', 'S', 'D' )
TTAG_mort               equ FT_MAKE_TAG( 'm', 'o', 'r', 't' )
TTAG_morx               equ FT_MAKE_TAG( 'm', 'o', 'r', 'x' )
TTAG_MVAR               equ FT_MAKE_TAG( 'M', 'V', 'A', 'R' )
TTAG_name               equ FT_MAKE_TAG( 'n', 'a', 'm', 'e' )
TTAG_opbd               equ FT_MAKE_TAG( 'o', 'p', 'b', 'd' )
TTAG_OS2                equ FT_MAKE_TAG( 'O', 'S', '/', '2' )
TTAG_OTTO               equ FT_MAKE_TAG( 'O', 'T', 'T', 'O' )
TTAG_PCLT               equ FT_MAKE_TAG( 'P', 'C', 'L', 'T' )
TTAG_POST               equ FT_MAKE_TAG( 'P', 'O', 'S', 'T' )
TTAG_post               equ FT_MAKE_TAG( 'p', 'o', 's', 't' )
TTAG_prep               equ FT_MAKE_TAG( 'p', 'r', 'e', 'p' )
TTAG_prop               equ FT_MAKE_TAG( 'p', 'r', 'o', 'p' )
TTAG_sbix               equ FT_MAKE_TAG( 's', 'b', 'i', 'x' )
TTAG_sfnt               equ FT_MAKE_TAG( 's', 'f', 'n', 't' )
TTAG_SING               equ FT_MAKE_TAG( 'S', 'I', 'N', 'G' )
TTAG_SVG                equ FT_MAKE_TAG( 'S', 'V', 'G', ' ' )
TTAG_trak               equ FT_MAKE_TAG( 't', 'r', 'a', 'k' )
TTAG_true               equ FT_MAKE_TAG( 't', 'r', 'u', 'e' )
TTAG_ttc                equ FT_MAKE_TAG( 't', 't', 'c', ' ' )
TTAG_ttcf               equ FT_MAKE_TAG( 't', 't', 'c', 'f' )
TTAG_TYP1               equ FT_MAKE_TAG( 'T', 'Y', 'P', '1' )
TTAG_typ1               equ FT_MAKE_TAG( 't', 'y', 'p', '1' )
TTAG_VDMX               equ FT_MAKE_TAG( 'V', 'D', 'M', 'X' )
TTAG_vhea               equ FT_MAKE_TAG( 'v', 'h', 'e', 'a' )
TTAG_vmtx               equ FT_MAKE_TAG( 'v', 'm', 't', 'x' )
TTAG_VVAR               equ FT_MAKE_TAG( 'V', 'V', 'A', 'R' )
TTAG_wOFF               equ FT_MAKE_TAG( 'w', 'O', 'F', 'F' )
TTAG_wOF2               equ FT_MAKE_TAG( 'w', 'O', 'F', '2' )

TTAG_0xA5kbd            equ FT_MAKE_TAG( 0xA5, 'k', 'b', 'd' )
TTAG_0xA5lst            equ FT_MAKE_TAG( 0xA5, 'l', 's', 't' )

endif
