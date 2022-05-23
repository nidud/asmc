ifndef FTMODERR_H_
define FTMODERR_H_

undef  FT_NEED_EXTERN_C

ifndef FT_MODERRDEF
ifdef FT_CONFIG_OPTION_USE_MODULE_ERRORS
FT_MODERRDEF macro e, v, s
	exitm<FT_Mod_Err_&e& = v,>
	endm
else
FT_MODERRDEF macro e, v, s
	exitm<FT_Mod_Err_&e& = 0,>
	endm
endif
define FT_MODERR_START_LIST  <.enum {>
define FT_MODERR_END_LIST    <FT_Mod_Err_Max }>
ifdef __cplusplus
define FT_NEED_EXTERN_C
endif
endif

ifdef FT_MODERR_START_LIST
FT_MODERR_START_LIST
endif

FT_MODERRDEF(Base,	0x000, "base module" )
FT_MODERRDEF(Autofit,	0x100, "autofitter module" )
FT_MODERRDEF(BDF,	0x200, "BDF module" )
FT_MODERRDEF(Bzip2,	0x300, "Bzip2 module" )
FT_MODERRDEF(Cache,	0x400, "cache module" )
FT_MODERRDEF(CFF,	0x500, "CFF module" )
FT_MODERRDEF(CID,	0x600, "CID module" )
FT_MODERRDEF(Gzip,	0x700, "Gzip module" )
FT_MODERRDEF(LZW,	0x800, "LZW module" )
FT_MODERRDEF(OTvalid,	0x900, "OpenType validation module" )
FT_MODERRDEF(PCF,	0xA00, "PCF module" )
FT_MODERRDEF(PFR,	0xB00, "PFR module" )
FT_MODERRDEF(PSaux,	0xC00, "PS auxiliary module" )
FT_MODERRDEF(PShinter,	0xD00, "PS hinter module" )
FT_MODERRDEF(PSnames,	0xE00, "PS names module" )
FT_MODERRDEF(Raster,	0xF00, "raster module" )
FT_MODERRDEF(SFNT,     0x1000, "SFNT module" )
FT_MODERRDEF(Smooth,   0x1100, "smooth raster module" )
FT_MODERRDEF(TrueType, 0x1200, "TrueType module" )
FT_MODERRDEF(Type1,    0x1300, "Type 1 module" )
FT_MODERRDEF(Type42,   0x1400, "Type 42 module" )
FT_MODERRDEF(Winfonts, 0x1500, "Windows FON/FNT module" )
FT_MODERRDEF(GXvalid,  0x1600, "GX validation module" )
FT_MODERRDEF(Sdf,      0x1700, "Signed distance field raster module" )

ifdef FT_MODERR_END_LIST
FT_MODERR_END_LIST
endif
ifdef FT_NEED_EXTERN_C
endif

undef FT_MODERR_START_LIST
undef FT_MODERR_END_LIST
undef FT_MODERRDEF
undef FT_NEED_EXTERN_C

endif
