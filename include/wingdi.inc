ifndef _WINGDI_
define _WINGDI_
.pragma list(push, 0)

include winapifamily.inc

ifdef _MAC
include macwin32.inc
endif

ifndef WINVER
define WINVER 0x0500
endif

ifndef NOGDI

ifndef NORASTEROPS

define R2_BLACK            1
define R2_NOTMERGEPEN      2
define R2_MASKNOTPEN       3
define R2_NOTCOPYPEN       4
define R2_MASKPENNOT       5
define R2_NOT              6
define R2_XORPEN           7
define R2_NOTMASKPEN       8
define R2_MASKPEN          9
define R2_NOTXORPEN        10
define R2_NOP              11
define R2_MERGENOTPEN      12
define R2_COPYPEN          13
define R2_MERGEPENNOT      14
define R2_MERGEPEN         15
define R2_WHITE            16
define R2_LAST             16

define SRCCOPY             0x00CC0020
define SRCPAINT            0x00EE0086
define SRCAND              0x008800C6
define SRCINVERT           0x00660046
define SRCERASE            0x00440328
define NOTSRCCOPY          0x00330008
define NOTSRCERASE         0x001100A6
define MERGECOPY           0x00C000CA
define MERGEPAINT          0x00BB0226
define PATCOPY             0x00F00021
define PATPAINT            0x00FB0A09
define PATINVERT           0x005A0049
define DSTINVERT           0x00550009
define BLACKNESS           0x00000042
define WHITENESS           0x00FF0062
if(WINVER ge 0x0500)

define NOMIRRORBITMAP               0x80000000
define CAPTUREBLT                   0x40000000
endif

MAKEROP4 macro fore,back
  local ta,tb
    if inl_loadtypes_2(fore, back, ta, tb)
        exitm<((((back) SHL 8) AND 0xFF000000) OR (fore))>
    endif
    inl_loadargs_2(fore,back,ta,tb)
    shl  edx,8
    and  edx,0xFF000000
    or   eax,edx
    retm <eax>
    endm

endif

define GDI_ERROR (0xFFFFFFFF)
if (_WIN32_WINNT ge _WIN32_WINNT_WINXP)
define HGDI_ERROR (LongToHandle(0xFFFFFFFF))
else
define HGDI_ERROR (-1)
endif

define ERROR               0
define NULLREGION          1
define SIMPLEREGION        2
define COMPLEXREGION       3
define RGN_ERROR ERROR

define RGN_AND             1
define RGN_OR              2
define RGN_XOR             3
define RGN_DIFF            4
define RGN_COPY            5
define RGN_MIN             RGN_AND
define RGN_MAX             RGN_COPY

define BLACKONWHITE                 1
define WHITEONBLACK                 2
define COLORONCOLOR                 3
define HALFTONE                     4
define MAXSTRETCHBLTMODE            4

if(WINVER ge 0x0400)
define STRETCH_ANDSCANS    BLACKONWHITE
define STRETCH_ORSCANS     WHITEONBLACK
define STRETCH_DELETESCANS COLORONCOLOR
define STRETCH_HALFTONE    HALFTONE
endif

define ALTERNATE                    1
define WINDING                      2
define POLYFILL_LAST                2

if(WINVER ge 0x0500)
define LAYOUT_RTL                         0x00000001
define LAYOUT_BTT                         0x00000002
define LAYOUT_VBH                         0x00000004
define LAYOUT_ORIENTATIONMASK             (LAYOUT_RTL or LAYOUT_BTT or LAYOUT_VBH)
define LAYOUT_BITMAPORIENTATIONPRESERVED  0x00000008
endif

define TA_NOUPDATECP                0
define TA_UPDATECP                  1

define TA_LEFT                      0
define TA_RIGHT                     2
define TA_CENTER                    6

define TA_TOP                       0
define TA_BOTTOM                    8
define TA_BASELINE                  24
if (WINVER ge 0x0400)
define TA_RTLREADING                256
define TA_MASK       (TA_BASELINE+TA_CENTER+TA_UPDATECP+TA_RTLREADING)
else
define TA_MASK       (TA_BASELINE+TA_CENTER+TA_UPDATECP)
endif

define VTA_BASELINE TA_BASELINE
define VTA_LEFT     TA_BOTTOM
define VTA_RIGHT    TA_TOP
define VTA_CENTER   TA_CENTER
define VTA_BOTTOM   TA_RIGHT
define VTA_TOP      TA_LEFT

define ETO_OPAQUE                   0x0002
define ETO_CLIPPED                  0x0004
if(WINVER ge 0x0400)
define ETO_GLYPH_INDEX              0x0010
define ETO_RTLREADING               0x0080
define ETO_NUMERICSLOCAL            0x0400
define ETO_NUMERICSLATIN            0x0800
define ETO_IGNORELANGUAGE           0x1000
endif
if (_WIN32_WINNT ge _WIN32_WINNT_WIN2K)
define ETO_PDY                      0x2000
endif
if (_WIN32_WINNT ge _WIN32_WINNT_LONGHORN)
define ETO_REVERSE_INDEX_MAP        0x10000
endif

define ASPECT_FILTERING             0x0001

define DCB_RESET       0x0001
define DCB_ACCUMULATE  0x0002
define DCB_DIRTY       DCB_ACCUMULATE
define DCB_SET         (DCB_RESET or DCB_ACCUMULATE)
define DCB_ENABLE      0x0004
define DCB_DISABLE     0x0008

ifndef NOMETAFILE

define META_SETBKCOLOR              0x0201
define META_SETBKMODE               0x0102
define META_SETMAPMODE              0x0103
define META_SETROP2                 0x0104
define META_SETRELABS               0x0105
define META_SETPOLYFILLMODE         0x0106
define META_SETSTRETCHBLTMODE       0x0107
define META_SETTEXTCHAREXTRA        0x0108
define META_SETTEXTCOLOR            0x0209
define META_SETTEXTJUSTIFICATION    0x020A
define META_SETWINDOWORG            0x020B
define META_SETWINDOWEXT            0x020C
define META_SETVIEWPORTORG          0x020D
define META_SETVIEWPORTEXT          0x020E
define META_OFFSETWINDOWORG         0x020F
define META_SCALEWINDOWEXT          0x0410
define META_OFFSETVIEWPORTORG       0x0211
define META_SCALEVIEWPORTEXT        0x0412
define META_LINETO                  0x0213
define META_MOVETO                  0x0214
define META_EXCLUDECLIPRECT         0x0415
define META_INTERSECTCLIPRECT       0x0416
define META_ARC                     0x0817
define META_ELLIPSE                 0x0418
define META_FLOODFILL               0x0419
define META_PIE                     0x081A
define META_RECTANGLE               0x041B
define META_ROUNDRECT               0x061C
define META_PATBLT                  0x061D
define META_SAVEDC                  0x001E
define META_SETPIXEL                0x041F
define META_OFFSETCLIPRGN           0x0220
define META_TEXTOUT                 0x0521
define META_BITBLT                  0x0922
define META_STRETCHBLT              0x0B23
define META_POLYGON                 0x0324
define META_POLYLINE                0x0325
define META_ESCAPE                  0x0626
define META_RESTOREDC               0x0127
define META_FILLREGION              0x0228
define META_FRAMEREGION             0x0429
define META_INVERTREGION            0x012A
define META_PAINTREGION             0x012B
define META_SELECTCLIPREGION        0x012C
define META_SELECTOBJECT            0x012D
define META_SETTEXTALIGN            0x012E
define META_CHORD                   0x0830
define META_SETMAPPERFLAGS          0x0231
define META_EXTTEXTOUT              0x0a32
define META_SETDIBTODEV             0x0d33
define META_SELECTPALETTE           0x0234
define META_REALIZEPALETTE          0x0035
define META_ANIMATEPALETTE          0x0436
define META_SETPALENTRIES           0x0037
define META_POLYPOLYGON             0x0538
define META_RESIZEPALETTE           0x0139
define META_DIBBITBLT               0x0940
define META_DIBSTRETCHBLT           0x0b41
define META_DIBCREATEPATTERNBRUSH   0x0142
define META_STRETCHDIB              0x0f43
define META_EXTFLOODFILL            0x0548
if(WINVER ge 0x0500)
define META_SETLAYOUT               0x0149
endif
define META_DELETEOBJECT            0x01f0
define META_CREATEPALETTE           0x00f7
define META_CREATEPATTERNBRUSH      0x01F9
define META_CREATEPENINDIRECT       0x02FA
define META_CREATEFONTINDIRECT      0x02FB
define META_CREATEBRUSHINDIRECT     0x02FC
define META_CREATEREGION            0x06FF

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

if(WINVER ge 0x0400)
_DRAWPATRECT            struct
ptPosition              POINT <>
ptSize                  POINT <>
wStyle                  WORD ?
wPattern                WORD ?
_DRAWPATRECT            ends
DRAWPATRECT             typedef _DRAWPATRECT
PDRAWPATRECT            typedef ptr _DRAWPATRECT
endif

endif

endif

define NEWFRAME                     1
define ABORTDOC                     2
define NEXTBAND                     3
define SETCOLORTABLE                4
define GETCOLORTABLE                5
define FLUSHOUTPUT                  6
define DRAFTMODE                    7
define QUERYESCSUPPORT              8
define SETABORTPROC                 9
define STARTDOC                     10
define ENDDOC                       11
define GETPHYSPAGESIZE              12
define GETPRINTINGOFFSET            13
define GETSCALINGFACTOR             14
define MFCOMMENT                    15
define GETPENWIDTH                  16
define SETCOPYCOUNT                 17
define SELECTPAPERSOURCE            18
define DEVICEDATA                   19
define PASSTHROUGH                  19
define GETTECHNOLGY                 20
define GETTECHNOLOGY                20
define SETLINECAP                   21
define SETLINEJOIN                  22
define SETMITERLIMIT                23
define BANDINFO                     24
define DRAWPATTERNRECT              25
define GETVECTORPENSIZE             26
define GETVECTORBRUSHSIZE           27
define ENABLEDUPLEX                 28
define GETSETPAPERBINS              29
define GETSETPRINTORIENT            30
define ENUMPAPERBINS                31
define SETDIBSCALING                32
define EPSPRINTING                  33
define ENUMPAPERMETRICS             34
define GETSETPAPERMETRICS           35
define POSTSCRIPT_DATA              37
define POSTSCRIPT_IGNORE            38
define MOUSETRAILS                  39
define GETDEVICEUNITS               42

define GETEXTENDEDTEXTMETRICS       256
define GETEXTENTTABLE               257
define GETPAIRKERNTABLE             258
define GETTRACKKERNTABLE            259
define EXTTEXTOUT                   512
define GETFACENAME                  513
define DOWNLOADFACE                 514
define ENABLERELATIVEWIDTHS         768
define ENABLEPAIRKERNING            769
define SETKERNTRACK                 770
define SETALLJUSTVALUES             771
define SETCHARSET                   772

define STRETCHBLT                   2048
define METAFILE_DRIVER              2049
define GETSETSCREENPARAMS           3072
define QUERYDIBSUPPORT              3073
define BEGIN_PATH                   4096
define CLIP_TO_PATH                 4097
define END_PATH                     4098
define EXT_DEVICE_CAPS              4099
define RESTORE_CTM                  4100
define SAVE_CTM                     4101
define SET_ARC_DIRECTION            4102
define SET_BACKGROUND_COLOR         4103
define SET_POLY_MODE                4104
define SET_SCREEN_ANGLE             4105
define SET_SPREAD                   4106
define TRANSFORM_CTM                4107
define SET_CLIP_BOX                 4108
define SET_BOUNDS                   4109
define SET_MIRROR_MODE              4110
define OPENCHANNEL                  4110
define DOWNLOADHEADER               4111
define CLOSECHANNEL                 4112
define POSTSCRIPT_PASSTHROUGH       4115
define ENCAPSULATED_POSTSCRIPT      4116

define POSTSCRIPT_IDENTIFY          4117
define POSTSCRIPT_INJECTION         4118

define CHECKJPEGFORMAT              4119
define CHECKPNGFORMAT               4120

define GET_PS_FEATURESETTING        4121

define GDIPLUS_TS_QUERYVER          4122
define GDIPLUS_TS_RECORD            4123

if (_WIN32_WINNT ge _WIN32_WINNT_LONGHORN)
define MILCORE_TS_QUERYVER_RESULT_FALSE        0x0
define MILCORE_TS_QUERYVER_RESULT_TRUE  0x7FFFFFFF
endif

define SPCLPASSTHROUGH2             4568

define PSIDENT_GDICENTRIC    0
define PSIDENT_PSCENTRIC     1

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

_PSINJECTDATA           struct
DataBytes               DWORD ?
InjectionPoint          WORD ?
PageNumber              WORD ?
_PSINJECTDATA           ends
PSINJECTDATA            typedef _PSINJECTDATA
PPSINJECTDATA           typedef ptr _PSINJECTDATA

endif

define PSINJECT_BEGINSTREAM                1
define PSINJECT_PSADOBE                    2
define PSINJECT_PAGESATEND                 3
define PSINJECT_PAGES                      4

define PSINJECT_DOCNEEDEDRES               5
define PSINJECT_DOCSUPPLIEDRES             6
define PSINJECT_PAGEORDER                  7
define PSINJECT_ORIENTATION                8
define PSINJECT_BOUNDINGBOX                9
define PSINJECT_DOCUMENTPROCESSCOLORS      10

define PSINJECT_COMMENTS                   11
define PSINJECT_BEGINDEFAULTS              12
define PSINJECT_ENDDEFAULTS                13
define PSINJECT_BEGINPROLOG                14
define PSINJECT_ENDPROLOG                  15
define PSINJECT_BEGINSETUP                 16
define PSINJECT_ENDSETUP                   17
define PSINJECT_TRAILER                    18
define PSINJECT_EOF                        19
define PSINJECT_ENDSTREAM                  20
define PSINJECT_DOCUMENTPROCESSCOLORSATEND 21

define PSINJECT_PAGENUMBER                 100
define PSINJECT_BEGINPAGESETUP             101
define PSINJECT_ENDPAGESETUP               102
define PSINJECT_PAGETRAILER                103
define PSINJECT_PLATECOLOR                 104

define PSINJECT_SHOWPAGE                   105
define PSINJECT_PAGEBBOX                   106
define PSINJECT_ENDPAGECOMMENTS            107

define PSINJECT_VMSAVE                     200
define PSINJECT_VMRESTORE                  201

define PSINJECT_DLFONT                     0xdddddddd

define FEATURESETTING_NUP                  0
define FEATURESETTING_OUTPUT               1
define FEATURESETTING_PSLEVEL              2
define FEATURESETTING_CUSTPAPER            3
define FEATURESETTING_MIRROR               4
define FEATURESETTING_NEGATIVE             5
define FEATURESETTING_PROTOCOL             6

if (_WIN32_WINNT ge _WIN32_WINNT_WINXP)
define FEATURESETTING_PRIVATE_BEGIN 0x1000
define FEATURESETTING_PRIVATE_END   0x1FFF
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

_PSFEATURE_OUTPUT       struct
bPageIndependent        BOOL ?
bSetPageDevice          BOOL ?
_PSFEATURE_OUTPUT       ends
PSFEATURE_OUTPUT        typedef _PSFEATURE_OUTPUT
PPSFEATURE_OUTPUT       typedef ptr _PSFEATURE_OUTPUT

_PSFEATURE_CUSTPAPER    struct
lOrientation            LONG ?
lWidth                  LONG ?
lHeight                 LONG ?
lWidthOffset            LONG ?
lHeightOffset           LONG ?
_PSFEATURE_CUSTPAPER    ends
PSFEATURE_CUSTPAPER     typedef _PSFEATURE_CUSTPAPER
PPSFEATURE_CUSTPAPER    typedef ptr _PSFEATURE_CUSTPAPER

endif

define PSPROTOCOL_ASCII             0
define PSPROTOCOL_BCP               1
define PSPROTOCOL_TBCP              2
define PSPROTOCOL_BINARY            3

define QDI_SETDIBITS                1
define QDI_GETDIBITS                2
define QDI_DIBTOSCREEN              4
define QDI_STRETCHDIB               8

define SP_NOTREPORTED               0x4000
define SP_ERROR                     (-1)
define SP_APPABORT                  (-2)
define SP_USERABORT                 (-3)
define SP_OUTOFDISK                 (-4)
define SP_OUTOFMEMORY               (-5)

define PR_JOBSTATUS                 0x0000

define OBJ_PEN             1
define OBJ_BRUSH           2
define OBJ_DC              3
define OBJ_METADC          4
define OBJ_PAL             5
define OBJ_FONT            6
define OBJ_BITMAP          7
define OBJ_REGION          8
define OBJ_METAFILE        9
define OBJ_MEMDC           10
define OBJ_EXTPEN          11
define OBJ_ENHMETADC       12
define OBJ_ENHMETAFILE     13
define OBJ_COLORSPACE      14

define GDI_OBJ_LAST        OBJ_COLORSPACE

define MWT_IDENTITY        1
define MWT_LEFTMULTIPLY    2
define MWT_RIGHTMULTIPLY   3

define MWT_MIN             MWT_IDENTITY
define MWT_MAX             MWT_RIGHTMULTIPLY

define _XFORM_

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

tagXFORM                struct
eM11                    FLOAT ?
eM12                    FLOAT ?
eM21                    FLOAT ?
eM22                    FLOAT ?
_eDx                    FLOAT ?
eDy                     FLOAT ?
tagXFORM                ends
XFORM                   typedef tagXFORM
PXFORM                  typedef ptr tagXFORM
LPXFORM                 typedef ptr tagXFORM

tagBITMAP               struct
bmType                  LONG ?
bmWidth                 LONG ?
bmHeight                LONG ?
bmWidthBytes            LONG ?
bmPlanes                WORD ?
bmBitsPixel             WORD ?
bmBits                  LPVOID ?
tagBITMAP               ends
BITMAP                  typedef tagBITMAP
PBITMAP                 typedef ptr tagBITMAP
NPBITMAP                typedef ptr tagBITMAP
LPBITMAP                typedef ptr tagBITMAP

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

tagRGBTRIPLE            struct 1
rgbtBlue                BYTE ?
rgbtGreen               BYTE ?
rgbtRed                 BYTE ?
tagRGBTRIPLE            ends
RGBTRIPLE               typedef tagRGBTRIPLE
PRGBTRIPLE              typedef ptr tagRGBTRIPLE
NPRGBTRIPLE             typedef ptr tagRGBTRIPLE
LPRGBTRIPLE             typedef ptr tagRGBTRIPLE

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

tagRGBQUAD              struct
rgbBlue                 BYTE ?
rgbGreen                BYTE ?
rgbRed                  BYTE ?
rgbReserved             BYTE ?
tagRGBQUAD              ends
RGBQUAD                 typedef tagRGBQUAD

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
LPRGBQUAD               typedef ptr
endif

if(WINVER ge 0x0400)

define CS_ENABLE                       0x00000001
define CS_DISABLE                      0x00000002
define CS_DELETE_TRANSFORM             0x00000003

define LCS_SIGNATURE           'PSOC'

define LCS_sRGB                'sRGB'
define LCS_WINDOWS_COLOR_SPACE 'Win '

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

LCSCSTYPE               typedef LONG

define LCS_CALIBRATED_RGB              0x00000000

LCSGAMUTMATCH           typedef LONG

define LCS_GM_BUSINESS                 0x00000001
define LCS_GM_GRAPHICS                 0x00000002
define LCS_GM_IMAGES                   0x00000004
define LCS_GM_ABS_COLORIMETRIC         0x00000008

define CM_OUT_OF_GAMUT                 255
define CM_IN_GAMUT                     0

define ICM_ADDPROFILE                  1
define ICM_DELETEPROFILE               2
define ICM_QUERYPROFILE                3
define ICM_SETDEFAULTPROFILE           4
define ICM_REGISTERICMATCHER           5
define ICM_UNREGISTERICMATCHER         6
define ICM_QUERYMATCH                  7

GetKValue macro cmyk
ifidn typeid(cmyk),<imm>
  exitm<(cmyk)>
endif
  mov eax,cmyk
  retm    <al>
  endm
GetYValue macro cmyk
ifidn typeid(cmyk),<imm>
  exitm<((cmyk) SHR 8)>
endif
  mov eax,cmyk
  shr eax,8
  retm    <al>
  endm
GetMValue macro cmyk
ifidn typeid(cmyk),<imm>
  exitm<((cmyk) SHR 16)>
endif
  mov eax,cmyk
  shr eax,16
  retm    <al>
  endm
GetCValue macro cmyk
ifidn typeid(cmyk),<imm>
  exitm<((cmyk) SHR 24)>
endif
  mov eax,cmyk
  shr eax,24
  retm    <al>
  endm

CMYK macro c,m,y,k
ifidn typeid(c),<imm>
ifidn typeid(m),<imm>
ifidn typeid(y),<imm>
ifidn typeid(k),<imm>
  exitm<(((((k) OR ((y) SHL 8)) OR ((m) SHL 16)) OR ((c) SHL 24)))>
endif
endif
endif
endif
ifdef _WIN64
ifdif <c>,<al>
  mov al,c
endif
  shl eax,8
  mov al,m
  shl eax,8
  mov al,y
  shl eax,8
else
  mov ah,c
  mov al,m
  shl eax,16
  mov ah,y
endif
  mov al,k
  retm    <eax>
  endm

FXPT16DOT16             typedef LONG
FXPT2DOT30              typedef LONG
LPFXPT16DOT16           typedef ptr
LPFXPT2DOT30            typedef ptr

tagCIEXYZ               struct
ciexyzX                 FXPT2DOT30 ?
ciexyzY                 FXPT2DOT30 ?
ciexyzZ                 FXPT2DOT30 ?
tagCIEXYZ               ends
CIEXYZ                  typedef tagCIEXYZ

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

LPCIEXYZ                typedef ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

tagICEXYZTRIPLE         struct
ciexyzRed               CIEXYZ <>
ciexyzGreen             CIEXYZ <>
ciexyzBlue              CIEXYZ <>
tagICEXYZTRIPLE         ends
CIEXYZTRIPLE            typedef tagICEXYZTRIPLE

endif
;.pragma endregion

;.pragma region Desktop Family
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

LPCIEXYZTRIPLE          typedef ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

tagLOGCOLORSPACEA       struct
lcsSignature            DWORD ?
lcsVersion              DWORD ?
lcsSize                 DWORD ?
lcsCSType               LCSCSTYPE ?
lcsIntent               LCSGAMUTMATCH ?
lcsEndpoints            CIEXYZTRIPLE <>
lcsGammaRed             DWORD ?
lcsGammaGreen           DWORD ?
lcsGammaBlue            DWORD ?
lcsFilename             CHAR MAX_PATH dup(?)
tagLOGCOLORSPACEA       ends
LOGCOLORSPACEA          typedef tagLOGCOLORSPACEA
LPLOGCOLORSPACEA        typedef ptr tagLOGCOLORSPACEA
tagLOGCOLORSPACEW       struct
lcsSignature            DWORD ?
lcsVersion              DWORD ?
lcsSize                 DWORD ?
lcsCSType               LCSCSTYPE ?
lcsIntent               LCSGAMUTMATCH ?
lcsEndpoints            CIEXYZTRIPLE <>
lcsGammaRed             DWORD ?
lcsGammaGreen           DWORD ?
lcsGammaBlue            DWORD ?
lcsFilename             WCHAR MAX_PATH dup(?)
tagLOGCOLORSPACEW       ends
LOGCOLORSPACEW          typedef tagLOGCOLORSPACEW
LPLOGCOLORSPACEW        typedef ptr tagLOGCOLORSPACEW
ifdef _UNICODE
LOGCOLORSPACE           typedef LOGCOLORSPACEW
LPLOGCOLORSPACE         typedef LPLOGCOLORSPACEW
else
LOGCOLORSPACE           typedef LOGCOLORSPACEA
LPLOGCOLORSPACE         typedef LPLOGCOLORSPACEA
endif

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

tagBITMAPCOREHEADER     struct
bcSize                  DWORD ?
bcWidth                 WORD ?
bcHeight                WORD ?
bcPlanes                WORD ?
bcBitCount              WORD ?
tagBITMAPCOREHEADER     ends
BITMAPCOREHEADER        typedef tagBITMAPCOREHEADER
LPBITMAPCOREHEADER      typedef ptr tagBITMAPCOREHEADER
PBITMAPCOREHEADER       typedef ptr tagBITMAPCOREHEADER

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

tagBITMAPINFOHEADER     struct
biSize                  DWORD ?
biWidth                 LONG ?
biHeight                LONG ?
biPlanes                WORD ?
biBitCount              WORD ?
biCompression           DWORD ?
biSizeImage             DWORD ?
biXPelsPerMeter         LONG ?
biYPelsPerMeter         LONG ?
biClrUsed               DWORD ?
biClrImportant          DWORD ?
tagBITMAPINFOHEADER     ends
BITMAPINFOHEADER        typedef tagBITMAPINFOHEADER
LPBITMAPINFOHEADER      typedef ptr tagBITMAPINFOHEADER
PBITMAPINFOHEADER       typedef ptr tagBITMAPINFOHEADER

endif

if(WINVER ge 0x0400)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

BITMAPV4HEADER          struct
bV4Size                 DWORD ?
bV4Width                LONG ?
bV4Height               LONG ?
bV4Planes               WORD ?
bV4BitCount             WORD ?
bV4V4Compression        DWORD ?
bV4SizeImage            DWORD ?
bV4XPelsPerMeter        LONG ?
bV4YPelsPerMeter        LONG ?
bV4ClrUsed              DWORD ?
bV4ClrImportant         DWORD ?
bV4RedMask              DWORD ?
bV4GreenMask            DWORD ?
bV4BlueMask             DWORD ?
bV4AlphaMask            DWORD ?
bV4CSType               DWORD ?
bV4Endpoints            CIEXYZTRIPLE <>
bV4GammaRed             DWORD ?
bV4GammaGreen           DWORD ?
bV4GammaBlue            DWORD ?
BITMAPV4HEADER          ends
LPBITMAPV4HEADER        typedef ptr BITMAPV4HEADER
PBITMAPV4HEADER         typedef ptr BITMAPV4HEADER

endif
endif

if (WINVER ge 0x0500)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
BITMAPV5HEADER          struct
bV5Size                 DWORD ?
bV5Width                LONG ?
bV5Height               LONG ?
bV5Planes               WORD ?
bV5BitCount             WORD ?
bV5Compression          DWORD ?
bV5SizeImage            DWORD ?
bV5XPelsPerMeter        LONG ?
bV5YPelsPerMeter        LONG ?
bV5ClrUsed              DWORD ?
bV5ClrImportant         DWORD ?
bV5RedMask              DWORD ?
bV5GreenMask            DWORD ?
bV5BlueMask             DWORD ?
bV5AlphaMask            DWORD ?
bV5CSType               DWORD ?
bV5Endpoints            CIEXYZTRIPLE <>
bV5GammaRed             DWORD ?
bV5GammaGreen           DWORD ?
bV5GammaBlue            DWORD ?
bV5Intent               DWORD ?
bV5ProfileData          DWORD ?
bV5ProfileSize          DWORD ?
bV5Reserved             DWORD ?
BITMAPV5HEADER          ends
LPBITMAPV5HEADER        typedef ptr BITMAPV5HEADER
PBITMAPV5HEADER         typedef ptr BITMAPV5HEADER

endif

define PROFILE_LINKED          'LINK'
define PROFILE_EMBEDDED        'MBED'
endif

define BI_RGB        0
define BI_RLE8       1
define BI_RLE4       2
define BI_BITFIELDS  3
define BI_JPEG       4
define BI_PNG        5
if (_WIN32_WINNT ge _WIN32_WINNT_NT4)
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

tagBITMAPINFO           struct
bmiHeader               BITMAPINFOHEADER <>
bmiColors               RGBQUAD 1 dup(<>)
tagBITMAPINFO           ends
BITMAPINFO              typedef tagBITMAPINFO
LPBITMAPINFO            typedef ptr tagBITMAPINFO
PBITMAPINFO             typedef ptr tagBITMAPINFO

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

tagBITMAPCOREINFO       struct
bmciHeader              BITMAPCOREHEADER <>
bmciColors              RGBTRIPLE 1 dup(<>)
tagBITMAPCOREINFO       ends
BITMAPCOREINFO          typedef tagBITMAPCOREINFO
LPBITMAPCOREINFO        typedef ptr tagBITMAPCOREINFO
PBITMAPCOREINFO         typedef ptr tagBITMAPCOREINFO

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

tagBITMAPFILEHEADER     struct 2
bfType                  WORD ?
bfSize                  DWORD ?
bfReserved1             WORD ?
bfReserved2             WORD ?
bfOffBits               DWORD ?
tagBITMAPFILEHEADER     ends
BITMAPFILEHEADER        typedef tagBITMAPFILEHEADER
LPBITMAPFILEHEADER      typedef ptr tagBITMAPFILEHEADER
PBITMAPFILEHEADER       typedef ptr tagBITMAPFILEHEADER

endif

MAKEPOINTS macro l
  exitm<[l]>
  endm

if(WINVER ge 0x0400)
ifndef NOFONTSIG

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

tagFONTSIGNATURE        struct
fsUsb                   DWORD 4 dup(?)
fsCsb                   DWORD 2 dup(?)
tagFONTSIGNATURE        ends
FONTSIGNATURE           typedef tagFONTSIGNATURE
PFONTSIGNATURE          typedef ptr tagFONTSIGNATURE
LPFONTSIGNATURE         typedef ptr tagFONTSIGNATURE

tagCHARSETINFO          struct
ciCharset               UINT ?
ciACP                   UINT ?
_fs                     FONTSIGNATURE <>
tagCHARSETINFO          ends
CHARSETINFO             typedef tagCHARSETINFO
PCHARSETINFO            typedef ptr tagCHARSETINFO
NPCHARSETINFO           typedef ptr tagCHARSETINFO
LPCHARSETINFO           typedef ptr tagCHARSETINFO

endif

define TCI_SRCCHARSET  1
define TCI_SRCCODEPAGE 2
define TCI_SRCFONTSIG  3
if (_WIN32_WINNT ge _WIN32_WINNT_WINXP)
define TCI_SRCLOCALE   0x1000
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

tagLOCALESIGNATURE      struct
lsUsb                   DWORD 4 dup(?)
lsCsbDefault            DWORD 2 dup(?)
lsCsbSupported          DWORD 2 dup(?)
tagLOCALESIGNATURE      ends
LOCALESIGNATURE         typedef tagLOCALESIGNATURE
PLOCALESIGNATURE        typedef ptr tagLOCALESIGNATURE
LPLOCALESIGNATURE       typedef ptr tagLOCALESIGNATURE

endif

endif
endif

ifndef NOMETAFILE

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

tagHANDLETABLE          struct
objectHandle            HGDIOBJ 1 dup(?)
tagHANDLETABLE          ends
HANDLETABLE             typedef tagHANDLETABLE
PHANDLETABLE            typedef ptr tagHANDLETABLE
LPHANDLETABLE           typedef ptr tagHANDLETABLE

tagMETARECORD           struct
rdSize                  DWORD ?
rdFunction              WORD ?
rdParm                  WORD 1 dup(?)
tagMETARECORD           ends
METARECORD              typedef tagMETARECORD

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

PMETARECORD             typedef ptr tagMETARECORD

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

LPMETARECORD            typedef ptr tagMETARECORD

tagMETAFILEPICT         struct
mm                      LONG ?
xExt                    LONG ?
yExt                    LONG ?
hMF                     HMETAFILE ?
tagMETAFILEPICT         ends
METAFILEPICT            typedef tagMETAFILEPICT
LPMETAFILEPICT          typedef ptr tagMETAFILEPICT

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

tagMETAHEADER           struct 2
mtType                  WORD ?
mtHeaderSize            WORD ?
mtVersion               WORD ?
mtSize                  DWORD ?
mtNoObjects             WORD ?
mtMaxRecord             DWORD ?
mtNoParameters          WORD ?
tagMETAHEADER           ends
METAHEADER              typedef tagMETAHEADER
PMETAHEADER             typedef ptr tagMETAHEADER
LPMETAHEADER            typedef ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

tagENHMETARECORD        struct
iType                   DWORD ?
nSize                   DWORD ?
dParm                   DWORD 1 dup(?)
tagENHMETARECORD        ends
ENHMETARECORD           typedef tagENHMETARECORD
PENHMETARECORD          typedef ptr tagENHMETARECORD
LPENHMETARECORD         typedef ptr tagENHMETARECORD

tagENHMETAHEADER        struct
iType                   DWORD ?
nSize                   DWORD ?
rclBounds               RECTL <>
rclFrame                RECTL <>
dSignature              DWORD ?
nVersion                DWORD ?
nBytes                  DWORD ?
nRecords                DWORD ?
nHandles                WORD ?
sReserved               WORD ?
nDescription            DWORD ?
offDescription          DWORD ?
nPalEntries             DWORD ?
szlDevice               SIZEL <>
szlMillimeters          SIZEL <>
if(WINVER ge 0x0400)
cbPixelFormat           DWORD ?
offPixelFormat          DWORD ?
bOpenGL                 DWORD ?
endif
if(WINVER ge 0x0500)
szlMicrometers          SIZEL <>
endif
tagENHMETAHEADER        ends
ENHMETAHEADER           typedef tagENHMETAHEADER
PENHMETAHEADER          typedef ptr tagENHMETAHEADER
LPENHMETAHEADER         typedef ptr tagENHMETAHEADER

endif

endif

ifndef NOTEXTMETRIC

define TMPF_FIXED_PITCH    0x01
define TMPF_VECTOR             0x02
define TMPF_DEVICE             0x08
define TMPF_TRUETYPE       0x04

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifdef _UNICODE
BCHAR                   typedef WCHAR
else
BCHAR                   typedef BYTE
endif

endif

ifndef _TEXTMETRIC_DEFINED
define _TEXTMETRIC_DEFINED

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

tagTEXTMETRICA          struct 4
tmHeight                LONG ?
tmAscent                LONG ?
tmDescent               LONG ?
tmInternalLeading       LONG ?
tmExternalLeading       LONG ?
tmAveCharWidth          LONG ?
tmMaxCharWidth          LONG ?
tmWeight                LONG ?
tmOverhang              LONG ?
tmDigitizedAspectX      LONG ?
tmDigitizedAspectY      LONG ?
tmFirstChar             BYTE ?
tmLastChar              BYTE ?
tmDefaultChar           BYTE ?
tmBreakChar             BYTE ?
tmItalic                BYTE ?
tmUnderlined            BYTE ?
tmStruckOut             BYTE ?
tmPitchAndFamily        BYTE ?
tmCharSet               BYTE ?
tagTEXTMETRICA          ends
TEXTMETRICA             typedef tagTEXTMETRICA
PTEXTMETRICA            typedef ptr tagTEXTMETRICA
NPTEXTMETRICA           typedef ptr tagTEXTMETRICA
LPTEXTMETRICA           typedef ptr tagTEXTMETRICA
tagTEXTMETRICW          struct
tmHeight                LONG ?
tmAscent                LONG ?
tmDescent               LONG ?
tmInternalLeading       LONG ?
tmExternalLeading       LONG ?
tmAveCharWidth          LONG ?
tmMaxCharWidth          LONG ?
tmWeight                LONG ?
tmOverhang              LONG ?
tmDigitizedAspectX      LONG ?
tmDigitizedAspectY      LONG ?
tmFirstChar             WCHAR ?
tmLastChar              WCHAR ?
tmDefaultChar           WCHAR ?
tmBreakChar             WCHAR ?
tmItalic                BYTE ?
tmUnderlined            BYTE ?
tmStruckOut             BYTE ?
tmPitchAndFamily        BYTE ?
tmCharSet               BYTE ?
tagTEXTMETRICW          ends
TEXTMETRICW             typedef tagTEXTMETRICW
PTEXTMETRICW            typedef ptr tagTEXTMETRICW
NPTEXTMETRICW           typedef ptr tagTEXTMETRICW
LPTEXTMETRICW           typedef ptr tagTEXTMETRICW
ifdef _UNICODE
TEXTMETRIC              typedef TEXTMETRICW
PTEXTMETRIC             typedef PTEXTMETRICW
NPTEXTMETRIC            typedef NPTEXTMETRICW
LPTEXTMETRIC            typedef LPTEXTMETRICW
else
TEXTMETRIC              typedef TEXTMETRICA
PTEXTMETRIC             typedef PTEXTMETRICA
NPTEXTMETRIC            typedef NPTEXTMETRICA
LPTEXTMETRIC            typedef LPTEXTMETRICA
endif

endif

endif

define NTM_REGULAR     0x00000040
define NTM_BOLD        0x00000020
define NTM_ITALIC      0x00000001

define NTM_NONNEGATIVE_AC  0x00010000
define NTM_PS_OPENTYPE     0x00020000
define NTM_TT_OPENTYPE     0x00040000
define NTM_MULTIPLEMASTER  0x00080000
define NTM_TYPE1           0x00100000
define NTM_DSIG            0x00200000

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

tagNEWTEXTMETRICA       struct 4
tmHeight                LONG ?
tmAscent                LONG ?
tmDescent               LONG ?
tmInternalLeading       LONG ?
tmExternalLeading       LONG ?
tmAveCharWidth          LONG ?
tmMaxCharWidth          LONG ?
tmWeight                LONG ?
tmOverhang              LONG ?
tmDigitizedAspectX      LONG ?
tmDigitizedAspectY      LONG ?
tmFirstChar             BYTE ?
tmLastChar              BYTE ?
tmDefaultChar           BYTE ?
tmBreakChar             BYTE ?
tmItalic                BYTE ?
tmUnderlined            BYTE ?
tmStruckOut             BYTE ?
tmPitchAndFamily        BYTE ?
tmCharSet               BYTE ?
ntmFlags                DWORD ?
ntmSizeEM               UINT ?
ntmCellHeight           UINT ?
ntmAvgWidth             UINT ?
tagNEWTEXTMETRICA       ends
NEWTEXTMETRICA          typedef tagNEWTEXTMETRICA
PNEWTEXTMETRICA         typedef ptr tagNEWTEXTMETRICA
NPNEWTEXTMETRICA        typedef ptr tagNEWTEXTMETRICA
LPNEWTEXTMETRICA        typedef ptr tagNEWTEXTMETRICA
tagNEWTEXTMETRICW       struct
tmHeight                LONG ?
tmAscent                LONG ?
tmDescent               LONG ?
tmInternalLeading       LONG ?
tmExternalLeading       LONG ?
tmAveCharWidth          LONG ?
tmMaxCharWidth          LONG ?
tmWeight                LONG ?
tmOverhang              LONG ?
tmDigitizedAspectX      LONG ?
tmDigitizedAspectY      LONG ?
tmFirstChar             WCHAR ?
tmLastChar              WCHAR ?
tmDefaultChar           WCHAR ?
tmBreakChar             WCHAR ?
tmItalic                BYTE ?
tmUnderlined            BYTE ?
tmStruckOut             BYTE ?
tmPitchAndFamily        BYTE ?
tmCharSet               BYTE ?
ntmFlags                DWORD ?
ntmSizeEM               UINT ?
ntmCellHeight           UINT ?
ntmAvgWidth             UINT ?
tagNEWTEXTMETRICW       ends
NEWTEXTMETRICW          typedef tagNEWTEXTMETRICW
PNEWTEXTMETRICW         typedef ptr tagNEWTEXTMETRICW
NPNEWTEXTMETRICW        typedef ptr tagNEWTEXTMETRICW
LPNEWTEXTMETRICW        typedef ptr tagNEWTEXTMETRICW
ifdef _UNICODE
NEWTEXTMETRIC           typedef NEWTEXTMETRICW
PNEWTEXTMETRIC          typedef PNEWTEXTMETRICW
NPNEWTEXTMETRIC         typedef NPNEWTEXTMETRICW
LPNEWTEXTMETRIC         typedef LPNEWTEXTMETRICW
else
NEWTEXTMETRIC           typedef NEWTEXTMETRICA
PNEWTEXTMETRIC          typedef PNEWTEXTMETRICA
NPNEWTEXTMETRIC         typedef NPNEWTEXTMETRICA
LPNEWTEXTMETRIC         typedef LPNEWTEXTMETRICA
endif

endif

if(WINVER ge 0x0400)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

tagNEWTEXTMETRICEXA     struct
ntmTm                   NEWTEXTMETRICA <>
ntmFontSig              FONTSIGNATURE <>
tagNEWTEXTMETRICEXA     ends
NEWTEXTMETRICEXA        typedef tagNEWTEXTMETRICEXA
tagNEWTEXTMETRICEXW     struct
ntmTm                   NEWTEXTMETRICW <>
ntmFontSig              FONTSIGNATURE <>
tagNEWTEXTMETRICEXW     ends
NEWTEXTMETRICEXW        typedef tagNEWTEXTMETRICEXW
ifdef _UNICODE
NEWTEXTMETRICEX         typedef NEWTEXTMETRICEXW
else
NEWTEXTMETRICEX         typedef NEWTEXTMETRICEXA
endif

endif
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

tagPELARRAY             struct
paXCount                LONG ?
paYCount                LONG ?
paXExt                  LONG ?
paYExt                  LONG ?
paRGBs                  BYTE ?
tagPELARRAY             ends
PELARRAY                typedef tagPELARRAY
PPELARRAY               typedef ptr tagPELARRAY
NPPELARRAY              typedef ptr tagPELARRAY
LPPELARRAY              typedef ptr tagPELARRAY

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

tagLOGBRUSH             struct
lbStyle                 UINT ?
lbColor                 COLORREF ?
lbHatch                 ULONG_PTR ?
tagLOGBRUSH             ends
LOGBRUSH                typedef tagLOGBRUSH
PLOGBRUSH               typedef ptr tagLOGBRUSH
NPLOGBRUSH              typedef ptr tagLOGBRUSH
LPLOGBRUSH              typedef ptr tagLOGBRUSH

tagLOGBRUSH32           struct
lbStyle                 UINT ?
lbColor                 COLORREF ?
lbHatch                 ULONG ?
tagLOGBRUSH32           ends
LOGBRUSH32              typedef tagLOGBRUSH32
PLOGBRUSH32             typedef ptr tagLOGBRUSH32
NPLOGBRUSH32            typedef ptr tagLOGBRUSH32
LPLOGBRUSH32            typedef ptr tagLOGBRUSH32

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

PATTERN                 typedef LOGBRUSH
PPATTERN                typedef ptr PATTERN
NPPATTERN               typedef ptr
LPPATTERN               typedef ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

tagLOGPEN               struct
lopnStyle               UINT ?
lopnWidth               POINT <>
lopnColor               COLORREF ?
tagLOGPEN               ends
LOGPEN                  typedef tagLOGPEN
PLOGPEN                 typedef ptr tagLOGPEN
NPLOGPEN                typedef ptr tagLOGPEN
LPLOGPEN                typedef ptr tagLOGPEN

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

tagEXTLOGPEN            struct
elpPenStyle             DWORD ?
elpWidth                DWORD ?
elpBrushStyle           UINT ?
elpColor                COLORREF ?
elpHatch                ULONG_PTR ?
elpNumEntries           DWORD ?
elpStyleEntry           DWORD 1 dup(?)
tagEXTLOGPEN            ends
EXTLOGPEN               typedef tagEXTLOGPEN
PEXTLOGPEN              typedef ptr tagEXTLOGPEN
NPEXTLOGPEN             typedef ptr tagEXTLOGPEN
LPEXTLOGPEN             typedef ptr tagEXTLOGPEN

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

tagEXTLOGPEN32          struct
elpPenStyle             DWORD ?
elpWidth                DWORD ?
elpBrushStyle           UINT ?
elpColor                COLORREF ?
elpHatch                ULONG ?
elpNumEntries           DWORD ?
elpStyleEntry           DWORD 1 dup(?)
tagEXTLOGPEN32          ends
EXTLOGPEN32             typedef tagEXTLOGPEN32
PEXTLOGPEN32            typedef ptr tagEXTLOGPEN32
NPEXTLOGPEN32           typedef ptr tagEXTLOGPEN32
LPEXTLOGPEN32           typedef ptr tagEXTLOGPEN32

ifndef _PALETTEENTRY_DEFINED
define _PALETTEENTRY_DEFINED
tagPALETTEENTRY         struct
peRed                   BYTE ?
peGreen                 BYTE ?
peBlue                  BYTE ?
peFlags                 BYTE ?
tagPALETTEENTRY         ends
PALETTEENTRY            typedef tagPALETTEENTRY
PPALETTEENTRY           typedef ptr tagPALETTEENTRY
LPPALETTEENTRY          typedef ptr tagPALETTEENTRY
endif

ifndef _LOGPALETTE_DEFINED
define _LOGPALETTE_DEFINED
tagLOGPALETTE           struct
palVersion              WORD ?
palNumEntries           WORD ?
palPalEntry             PALETTEENTRY 1 dup(<>)
tagLOGPALETTE           ends
LOGPALETTE              typedef tagLOGPALETTE
PLOGPALETTE             typedef ptr tagLOGPALETTE
NPLOGPALETTE            typedef ptr tagLOGPALETTE
LPLOGPALETTE            typedef ptr tagLOGPALETTE
endif

define LF_FACESIZE      32

tagLOGFONTA             struct
lfHeight                LONG ?
lfWidth                 LONG ?
lfEscapement            LONG ?
lfOrientation           LONG ?
lfWeight                LONG ?
lfItalic                BYTE ?
lfUnderline             BYTE ?
lfStrikeOut             BYTE ?
lfCharSet               BYTE ?
lfOutPrecision          BYTE ?
lfClipPrecision         BYTE ?
lfQuality               BYTE ?
lfPitchAndFamily        BYTE ?
lfFaceName              CHAR LF_FACESIZE dup(?)
tagLOGFONTA             ends
LOGFONTA                typedef tagLOGFONTA
PLOGFONTA               typedef ptr tagLOGFONTA
NPLOGFONTA              typedef ptr tagLOGFONTA
LPLOGFONTA              typedef ptr tagLOGFONTA
tagLOGFONTW             struct
lfHeight                LONG ?
lfWidth                 LONG ?
lfEscapement            LONG ?
lfOrientation           LONG ?
lfWeight                LONG ?
lfItalic                BYTE ?
lfUnderline             BYTE ?
lfStrikeOut             BYTE ?
lfCharSet               BYTE ?
lfOutPrecision          BYTE ?
lfClipPrecision         BYTE ?
lfQuality               BYTE ?
lfPitchAndFamily        BYTE ?
lfFaceName              WCHAR LF_FACESIZE dup(?)
tagLOGFONTW             ends
LOGFONTW                typedef tagLOGFONTW
PLOGFONTW               typedef ptr tagLOGFONTW
NPLOGFONTW              typedef ptr tagLOGFONTW
LPLOGFONTW              typedef ptr tagLOGFONTW
ifdef _UNICODE
LOGFONT                 typedef LOGFONTW
PLOGFONT                typedef PLOGFONTW
NPLOGFONT               typedef NPLOGFONTW
LPLOGFONT               typedef LPLOGFONTW
else
LOGFONT                 typedef LOGFONTA
PLOGFONT                typedef PLOGFONTA
NPLOGFONT               typedef NPLOGFONTA
LPLOGFONT               typedef LPLOGFONTA
endif

endif

define LF_FULLFACESIZE     64

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

tagENUMLOGFONTA         struct
elfLogFont              LOGFONTA <>
elfFullName             BYTE LF_FULLFACESIZE dup(?)
elfStyle                BYTE LF_FACESIZE dup(?)
tagENUMLOGFONTA         ends
ENUMLOGFONTA            typedef tagENUMLOGFONTA
 LPENUMLOGFONTA         typedef ptr tagENUMLOGFONTA
tagENUMLOGFONTW         struct
elfLogFont              LOGFONTW <>
elfFullName             WCHAR LF_FULLFACESIZE dup(?)
elfStyle                WCHAR LF_FACESIZE dup(?)
tagENUMLOGFONTW         ends
ENUMLOGFONTW            typedef tagENUMLOGFONTW
 LPENUMLOGFONTW         typedef ptr tagENUMLOGFONTW
ifdef _UNICODE
ENUMLOGFONT             typedef ENUMLOGFONTW
LPENUMLOGFONT           typedef LPENUMLOGFONTW
else
ENUMLOGFONT             typedef ENUMLOGFONTA
LPENUMLOGFONT           typedef LPENUMLOGFONTA
endif

if(WINVER ge 0x0400)
tagENUMLOGFONTEXA       struct
elfLogFont              LOGFONTA <>
elfFullName             BYTE LF_FULLFACESIZE dup(?)
elfStyle                BYTE LF_FACESIZE dup(?)
elfScript               BYTE LF_FACESIZE dup(?)
tagENUMLOGFONTEXA       ends
ENUMLOGFONTEXA          typedef tagENUMLOGFONTEXA
LPENUMLOGFONTEXA        typedef ptr tagENUMLOGFONTEXA
tagENUMLOGFONTEXW       struct
elfLogFont              LOGFONTW <>
elfFullName             WCHAR LF_FULLFACESIZE dup(?)
elfStyle                WCHAR LF_FACESIZE dup(?)
elfScript               WCHAR LF_FACESIZE dup(?)
tagENUMLOGFONTEXW       ends
ENUMLOGFONTEXW          typedef tagENUMLOGFONTEXW
LPENUMLOGFONTEXW        typedef ptr tagENUMLOGFONTEXW
ifdef _UNICODE
ENUMLOGFONTEX           typedef ENUMLOGFONTEXW
LPENUMLOGFONTEX         typedef LPENUMLOGFONTEXW
else
ENUMLOGFONTEX           typedef ENUMLOGFONTEXA
LPENUMLOGFONTEX         typedef LPENUMLOGFONTEXA
endif
endif

endif

define OUT_DEFAULT_PRECIS          0
define OUT_STRING_PRECIS           1
define OUT_CHARACTER_PRECIS        2
define OUT_STROKE_PRECIS           3
define OUT_TT_PRECIS               4
define OUT_DEVICE_PRECIS           5
define OUT_RASTER_PRECIS           6
define OUT_TT_ONLY_PRECIS          7
define OUT_OUTLINE_PRECIS          8
define OUT_SCREEN_OUTLINE_PRECIS   9
define OUT_PS_ONLY_PRECIS          10

define CLIP_DEFAULT_PRECIS     0
define CLIP_CHARACTER_PRECIS   1
define CLIP_STROKE_PRECIS      2
define CLIP_MASK               0xf
define CLIP_LH_ANGLES          (1 shl 4)
define CLIP_TT_ALWAYS          (2 shl 4)
if (_WIN32_WINNT ge _WIN32_WINNT_LONGHORN)
define CLIP_DFA_DISABLE        (4 shl 4)
endif
define CLIP_EMBEDDED           (8 shl 4)

define DEFAULT_QUALITY         0
define DRAFT_QUALITY           1
define PROOF_QUALITY           2
if(WINVER ge 0x0400)
define NONANTIALIASED_QUALITY  3
define ANTIALIASED_QUALITY     4
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WINXP)
define CLEARTYPE_QUALITY       5
define CLEARTYPE_NATURAL_QUALITY       6
endif

define DEFAULT_PITCH           0
define FIXED_PITCH             1
define VARIABLE_PITCH          2
if(WINVER ge 0x0400)
define MONO_FONT               8
endif

define ANSI_CHARSET            0
define DEFAULT_CHARSET         1
define SYMBOL_CHARSET          2
define SHIFTJIS_CHARSET        128
define HANGEUL_CHARSET         129
define HANGUL_CHARSET          129
define GB2312_CHARSET          134
define CHINESEBIG5_CHARSET     136
define OEM_CHARSET             255
if(WINVER ge 0x0400)
define JOHAB_CHARSET           130
define HEBREW_CHARSET          177
define ARABIC_CHARSET          178
define GREEK_CHARSET           161
define TURKISH_CHARSET         162
define VIETNAMESE_CHARSET      163
define THAI_CHARSET            222
define EASTEUROPE_CHARSET      238
define RUSSIAN_CHARSET         204

define MAC_CHARSET             77
define BALTIC_CHARSET          186

define FS_LATIN1               0x00000001
define FS_LATIN2               0x00000002
define FS_CYRILLIC             0x00000004
define FS_GREEK                0x00000008
define FS_TURKISH              0x00000010
define FS_HEBREW               0x00000020
define FS_ARABIC               0x00000040
define FS_BALTIC               0x00000080
define FS_VIETNAMESE           0x00000100
define FS_THAI                 0x00010000
define FS_JISJAPAN             0x00020000
define FS_CHINESESIMP          0x00040000
define FS_WANSUNG              0x00080000
define FS_CHINESETRAD          0x00100000
define FS_JOHAB                0x00200000
define FS_SYMBOL               0x80000000
endif

define FF_DONTCARE         (0 shl 4)
define FF_ROMAN            (1 shl 4)
define FF_SWISS            (2 shl 4)
define FF_MODERN           (3 shl 4)
define FF_SCRIPT           (4 shl 4)
define FF_DECORATIVE       (5 shl 4)

define FW_DONTCARE         0
define FW_THIN             100
define FW_EXTRALIGHT       200
define FW_LIGHT            300
define FW_NORMAL           400
define FW_MEDIUM           500
define FW_SEMIBOLD         600
define FW_BOLD             700
define FW_EXTRABOLD        800
define FW_HEAVY            900

define FW_ULTRALIGHT       FW_EXTRALIGHT
define FW_REGULAR          FW_NORMAL
define FW_DEMIBOLD         FW_SEMIBOLD
define FW_ULTRABOLD        FW_EXTRABOLD
define FW_BLACK            FW_HEAVY

define PANOSE_COUNT               10
define PAN_FAMILYTYPE_INDEX        0
define PAN_SERIFSTYLE_INDEX        1
define PAN_WEIGHT_INDEX            2
define PAN_PROPORTION_INDEX        3
define PAN_CONTRAST_INDEX          4
define PAN_STROKEVARIATION_INDEX   5
define PAN_ARMSTYLE_INDEX          6
define PAN_LETTERFORM_INDEX        7
define PAN_MIDLINE_INDEX           8
define PAN_XHEIGHT_INDEX           9

define PAN_CULTURE_LATIN           0

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

tagPANOSE               struct
bFamilyType             BYTE ?
bSerifStyle             BYTE ?
bWeight                 BYTE ?
bProportion             BYTE ?
bContrast               BYTE ?
bStrokeVariation        BYTE ?
bArmStyle               BYTE ?
bLetterform             BYTE ?
bMidline                BYTE ?
bXHeight                BYTE ?
tagPANOSE               ends
PANOSE                  typedef tagPANOSE
LPPANOSE                typedef ptr tagPANOSE

define PAN_ANY                         0
define PAN_NO_FIT                      1

define PAN_FAMILY_TEXT_DISPLAY         2
define PAN_FAMILY_SCRIPT               3
define PAN_FAMILY_DECORATIVE           4
define PAN_FAMILY_PICTORIAL            5

define PAN_SERIF_COVE                  2
define PAN_SERIF_OBTUSE_COVE           3
define PAN_SERIF_SQUARE_COVE           4
define PAN_SERIF_OBTUSE_SQUARE_COVE    5
define PAN_SERIF_SQUARE                6
define PAN_SERIF_THIN                  7
define PAN_SERIF_BONE                  8
define PAN_SERIF_EXAGGERATED           9
define PAN_SERIF_TRIANGLE             10
define PAN_SERIF_NORMAL_SANS          11
define PAN_SERIF_OBTUSE_SANS          12
define PAN_SERIF_PERP_SANS            13
define PAN_SERIF_FLARED               14
define PAN_SERIF_ROUNDED              15

define PAN_WEIGHT_VERY_LIGHT           2
define PAN_WEIGHT_LIGHT                3
define PAN_WEIGHT_THIN                 4
define PAN_WEIGHT_BOOK                 5
define PAN_WEIGHT_MEDIUM               6
define PAN_WEIGHT_DEMI                 7
define PAN_WEIGHT_BOLD                 8
define PAN_WEIGHT_HEAVY                9
define PAN_WEIGHT_BLACK               10
define PAN_WEIGHT_NORD                11

define PAN_PROP_OLD_STYLE              2
define PAN_PROP_MODERN                 3
define PAN_PROP_EVEN_WIDTH             4
define PAN_PROP_EXPANDED               5
define PAN_PROP_CONDENSED              6
define PAN_PROP_VERY_EXPANDED          7
define PAN_PROP_VERY_CONDENSED         8
define PAN_PROP_MONOSPACED             9

define PAN_CONTRAST_NONE               2
define PAN_CONTRAST_VERY_LOW           3
define PAN_CONTRAST_LOW                4
define PAN_CONTRAST_MEDIUM_LOW         5
define PAN_CONTRAST_MEDIUM             6
define PAN_CONTRAST_MEDIUM_HIGH        7
define PAN_CONTRAST_HIGH               8
define PAN_CONTRAST_VERY_HIGH          9

define PAN_STROKE_GRADUAL_DIAG         2
define PAN_STROKE_GRADUAL_TRAN         3
define PAN_STROKE_GRADUAL_VERT         4
define PAN_STROKE_GRADUAL_HORZ         5
define PAN_STROKE_RAPID_VERT           6
define PAN_STROKE_RAPID_HORZ           7
define PAN_STROKE_INSTANT_VERT         8

define PAN_STRAIGHT_ARMS_HORZ          2
define PAN_STRAIGHT_ARMS_WEDGE         3
define PAN_STRAIGHT_ARMS_VERT          4
define PAN_STRAIGHT_ARMS_SINGLE_SERIF  5
define PAN_STRAIGHT_ARMS_DOUBLE_SERIF  6
define PAN_BENT_ARMS_HORZ              7
define PAN_BENT_ARMS_WEDGE             8
define PAN_BENT_ARMS_VERT              9
define PAN_BENT_ARMS_SINGLE_SERIF     10
define PAN_BENT_ARMS_DOUBLE_SERIF     11

define PAN_LETT_NORMAL_CONTACT         2
define PAN_LETT_NORMAL_WEIGHTED        3
define PAN_LETT_NORMAL_BOXED           4
define PAN_LETT_NORMAL_FLATTENED       5
define PAN_LETT_NORMAL_ROUNDED         6
define PAN_LETT_NORMAL_OFF_CENTER      7
define PAN_LETT_NORMAL_SQUARE          8
define PAN_LETT_OBLIQUE_CONTACT        9
define PAN_LETT_OBLIQUE_WEIGHTED      10
define PAN_LETT_OBLIQUE_BOXED         11
define PAN_LETT_OBLIQUE_FLATTENED     12
define PAN_LETT_OBLIQUE_ROUNDED       13
define PAN_LETT_OBLIQUE_OFF_CENTER    14
define PAN_LETT_OBLIQUE_SQUARE        15

define PAN_MIDLINE_STANDARD_TRIMMED    2
define PAN_MIDLINE_STANDARD_POINTED    3
define PAN_MIDLINE_STANDARD_SERIFED    4
define PAN_MIDLINE_HIGH_TRIMMED        5
define PAN_MIDLINE_HIGH_POINTED        6
define PAN_MIDLINE_HIGH_SERIFED        7
define PAN_MIDLINE_CONSTANT_TRIMMED    8
define PAN_MIDLINE_CONSTANT_POINTED    9
define PAN_MIDLINE_CONSTANT_SERIFED   10
define PAN_MIDLINE_LOW_TRIMMED        11
define PAN_MIDLINE_LOW_POINTED        12
define PAN_MIDLINE_LOW_SERIFED        13

define PAN_XHEIGHT_CONSTANT_SMALL      2
define PAN_XHEIGHT_CONSTANT_STD        3
define PAN_XHEIGHT_CONSTANT_LARGE      4
define PAN_XHEIGHT_DUCKING_SMALL       5
define PAN_XHEIGHT_DUCKING_STD         6
define PAN_XHEIGHT_DUCKING_LARGE       7

define ELF_VENDOR_SIZE     4

tagEXTLOGFONTA          struct
elfLogFont              LOGFONTA <>
elfFullName             BYTE LF_FULLFACESIZE dup(?)
elfStyle                BYTE LF_FACESIZE dup(?)
elfVersion              DWORD ?
elfStyleSize            DWORD ?
elfMatch                DWORD ?
elfReserved             DWORD ?
elfVendorId             BYTE ELF_VENDOR_SIZE dup(?)
elfCulture              DWORD ?
elfPanose               PANOSE <>
tagEXTLOGFONTA          ends
EXTLOGFONTA             typedef tagEXTLOGFONTA
PEXTLOGFONTA            typedef ptr tagEXTLOGFONTA
NPEXTLOGFONTA           typedef ptr tagEXTLOGFONTA
LPEXTLOGFONTA           typedef ptr tagEXTLOGFONTA
tagEXTLOGFONTW          struct
elfLogFont              LOGFONTW <>
elfFullName             WCHAR LF_FULLFACESIZE dup(?)
elfStyle                WCHAR LF_FACESIZE dup(?)
elfVersion              DWORD ?
elfStyleSize            DWORD ?
elfMatch                DWORD ?
elfReserved             DWORD ?
elfVendorId             BYTE ELF_VENDOR_SIZE dup(?)
elfCulture              DWORD ?
elfPanose               PANOSE <>
tagEXTLOGFONTW          ends
EXTLOGFONTW             typedef tagEXTLOGFONTW
PEXTLOGFONTW            typedef ptr tagEXTLOGFONTW
NPEXTLOGFONTW           typedef ptr tagEXTLOGFONTW
LPEXTLOGFONTW           typedef ptr tagEXTLOGFONTW
ifdef _UNICODE
EXTLOGFONT              typedef EXTLOGFONTW
PEXTLOGFONT             typedef PEXTLOGFONTW
NPEXTLOGFONT            typedef NPEXTLOGFONTW
LPEXTLOGFONT            typedef LPEXTLOGFONTW
else
EXTLOGFONT              typedef EXTLOGFONTA
PEXTLOGFONT             typedef PEXTLOGFONTA
NPEXTLOGFONT            typedef NPEXTLOGFONTA
LPEXTLOGFONT            typedef LPEXTLOGFONTA
endif

endif

define ELF_VERSION         0
define ELF_CULTURE_LATIN   0

define RASTER_FONTTYPE     0x0001
define DEVICE_FONTTYPE     0x0002
define TRUETYPE_FONTTYPE   0x0004

RGB macro r,g,b
ifidn typeid(r),<imm>
ifidn typeid(g),<imm>
ifidn typeid(b),<imm>
  exitm<((((r) OR (((g)) SHL 8)) OR (((b)) SHL 16)))>
endif
endif
endif
  mov   ah,0
  mov   al,b
  shl   eax,8
  mov   al,g
  shl   eax,8
  mov   al,r
  retm  <eax>
  endm

PALETTERGB macro r,g,b
ifidn typeid(r),<imm>
ifidn typeid(g),<imm>
ifidn typeid(b),<imm>
  exitm<(0x02000000 OR RGB(r,g,b))>
endif
endif
endif
  or    RGB(r,g,b),0x02000000
  retm  <eax>
  endm
PALETTEINDEX macro i
ifidn typeid(i),<imm>
  exitm<((0x01000000 OR (i)))>
endif
  mov   eax,i
  or    eax,0x02000000
  retm  <eax>
  endm

define PC_RESERVED     0x01
define PC_EXPLICIT     0x02
define PC_NOCOLLAPSE   0x04

GetRValue macro rgb
  mov   eax,rgb
  retm  <al>
  endm
GetGValue macro rgb
  mov   eax,rgb
  shr   eax,8
  retm  <al>
  endm
GetBValue macro rgb
  mov   eax,rgb
  shr   eax,16
  retm  <al>
  endm

define TRANSPARENT         1
define OPAQUE              2
define BKMODE_LAST         2

define GM_COMPATIBLE       1
define GM_ADVANCED         2
define GM_LAST             2

define PT_CLOSEFIGURE      0x01
define PT_LINETO           0x02
define PT_BEZIERTO         0x04
define PT_MOVETO           0x06

define MM_TEXT             1
define MM_LOMETRIC         2
define MM_HIMETRIC         3
define MM_LOENGLISH        4
define MM_HIENGLISH        5
define MM_TWIPS            6
define MM_ISOTROPIC        7
define MM_ANISOTROPIC      8

define MM_MIN              MM_TEXT
define MM_MAX              MM_ANISOTROPIC
define MM_MAX_FIXEDSCALE   MM_TWIPS

define ABSOLUTE            1
define RELATIVE            2

define WHITE_BRUSH         0
define LTGRAY_BRUSH        1
define GRAY_BRUSH          2
define DKGRAY_BRUSH        3
define BLACK_BRUSH         4
define NULL_BRUSH          5
define HOLLOW_BRUSH        NULL_BRUSH
define WHITE_PEN           6
define BLACK_PEN           7
define NULL_PEN            8
define OEM_FIXED_FONT      10
define ANSI_FIXED_FONT     11
define ANSI_VAR_FONT       12
define SYSTEM_FONT         13
define DEVICE_DEFAULT_FONT 14
define DEFAULT_PALETTE     15
define SYSTEM_FIXED_FONT   16

if(WINVER ge 0x0400)
define DEFAULT_GUI_FONT    17
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN2K)
define DC_BRUSH            18
define DC_PEN              19
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN2K)
define STOCK_LAST          19
elseif (WINVER ge 0x0400)
define STOCK_LAST          17
else
define STOCK_LAST          16
endif

define CLR_INVALID     0xFFFFFFFF

define BS_SOLID            0
define BS_NULL             1
define BS_HOLLOW           BS_NULL
define BS_HATCHED          2
define BS_PATTERN          3
define BS_INDEXED          4
define BS_DIBPATTERN       5
define BS_DIBPATTERNPT     6
define BS_PATTERN8X8       7
define BS_DIBPATTERN8X8    8
define BS_MONOPATTERN      9

define HS_HORIZONTAL       0
define HS_VERTICAL         1
define HS_FDIAGONAL        2
define HS_BDIAGONAL        3
define HS_CROSS            4
define HS_DIAGCROSS        5
define HS_API_MAX          12

define PS_SOLID            0
define PS_DASH             1
define PS_DOT              2
define PS_DASHDOT          3
define PS_DASHDOTDOT       4
define PS_NULL             5
define PS_INSIDEFRAME      6
define PS_USERSTYLE        7
define PS_ALTERNATE        8
define PS_STYLE_MASK       0x0000000F

define PS_ENDCAP_ROUND     0x00000000
define PS_ENDCAP_SQUARE    0x00000100
define PS_ENDCAP_FLAT      0x00000200
define PS_ENDCAP_MASK      0x00000F00

define PS_JOIN_ROUND       0x00000000
define PS_JOIN_BEVEL       0x00001000
define PS_JOIN_MITER       0x00002000
define PS_JOIN_MASK        0x0000F000

define PS_COSMETIC         0x00000000
define PS_GEOMETRIC        0x00010000
define PS_TYPE_MASK        0x000F0000

define AD_COUNTERCLOCKWISE 1
define AD_CLOCKWISE        2

define DRIVERVERSION 0
define TECHNOLOGY    2
define HORZSIZE      4
define VERTSIZE      6
define HORZRES       8
define VERTRES       10
define BITSPIXEL     12
define PLANES        14
define NUMBRUSHES    16
define NUMPENS       18
define NUMMARKERS    20
define NUMFONTS      22
define NUMCOLORS     24
define PDEVICESIZE   26
define CURVECAPS     28
define LINECAPS      30
define POLYGONALCAPS 32
define TEXTCAPS      34
define CLIPCAPS      36
define RASTERCAPS    38
define ASPECTX       40
define ASPECTY       42
define ASPECTXY      44

define LOGPIXELSX    88
define LOGPIXELSY    90

define SIZEPALETTE  104
define NUMRESERVED  106
define COLORRES     108

define PHYSICALWIDTH   110
define PHYSICALHEIGHT  111
define PHYSICALOFFSETX 112
define PHYSICALOFFSETY 113
define SCALINGFACTORX  114
define SCALINGFACTORY  115

define VREFRESH        116
define DESKTOPVERTRES  117
define DESKTOPHORZRES  118
define BLTALIGNMENT    119

if(WINVER ge 0x0500)
define SHADEBLENDCAPS  120
define COLORMGMTCAPS   121
endif

ifndef NOGDICAPMASKS

define DT_PLOTTER          0
define DT_RASDISPLAY       1
define DT_RASPRINTER       2
define DT_RASCAMERA        3
define DT_CHARSTREAM       4
define DT_METAFILE         5
define DT_DISPFILE         6

define CC_NONE             0
define CC_CIRCLES          1
define CC_PIE              2
define CC_CHORD            4
define CC_ELLIPSES         8
define CC_WIDE             16
define CC_STYLED           32
define CC_WIDESTYLED       64
define CC_INTERIORS        128
define CC_ROUNDRECT        256

define LC_NONE             0
define LC_POLYLINE         2
define LC_MARKER           4
define LC_POLYMARKER       8
define LC_WIDE             16
define LC_STYLED           32
define LC_WIDESTYLED       64
define LC_INTERIORS        128

define PC_NONE             0
define PC_POLYGON          1
define PC_RECTANGLE        2
define PC_WINDPOLYGON      4
define PC_TRAPEZOID        4
define PC_SCANLINE         8
define PC_WIDE             16
define PC_STYLED           32
define PC_WIDESTYLED       64
define PC_INTERIORS        128
define PC_POLYPOLYGON      256
define PC_PATHS            512

define CP_NONE             0
define CP_RECTANGLE        1
define CP_REGION           2

define TC_OP_CHARACTER     0x00000001
define TC_OP_STROKE        0x00000002
define TC_CP_STROKE        0x00000004
define TC_CR_90            0x00000008
define TC_CR_ANY           0x00000010
define TC_SF_X_YINDEP      0x00000020
define TC_SA_DOUBLE        0x00000040
define TC_SA_INTEGER       0x00000080
define TC_SA_CONTIN        0x00000100
define TC_EA_DOUBLE        0x00000200
define TC_IA_ABLE          0x00000400
define TC_UA_ABLE          0x00000800
define TC_SO_ABLE          0x00001000
define TC_RA_ABLE          0x00002000
define TC_VA_ABLE          0x00004000
define TC_RESERVED         0x00008000
define TC_SCROLLBLT        0x00010000

endif

define RC_NONE
define RC_BITBLT           1
define RC_BANDING          2
define RC_SCALING          4
define RC_BITMAP64         8
define RC_GDI20_OUTPUT     0x0010
define RC_GDI20_STATE      0x0020
define RC_SAVEBITMAP       0x0040
define RC_DI_BITMAP        0x0080
define RC_PALETTE          0x0100
define RC_DIBTODEV         0x0200
define RC_BIGFONT          0x0400
define RC_STRETCHBLT       0x0800
define RC_FLOODFILL        0x1000
define RC_STRETCHDIB       0x2000
define RC_OP_DX_OUTPUT     0x4000
define RC_DEVBITS          0x8000

if(WINVER ge 0x0500)

define SB_NONE             0x00000000
define SB_CONST_ALPHA      0x00000001
define SB_PIXEL_ALPHA      0x00000002
define SB_PREMULT_ALPHA    0x00000004

define SB_GRAD_RECT        0x00000010
define SB_GRAD_TRI         0x00000020

define CM_NONE             0x00000000
define CM_DEVICE_ICM       0x00000001
define CM_GAMMA_RAMP       0x00000002
define CM_CMYK_COLOR       0x00000004

endif

define DIB_RGB_COLORS      0
define DIB_PAL_COLORS      1

define SYSPAL_ERROR    0
define SYSPAL_STATIC   1
define SYSPAL_NOSTATIC 2
define SYSPAL_NOSTATIC256 3

define CBM_INIT        0x04

define  FLOODFILLBORDER   0
define  FLOODFILLSURFACE  1

define CCHDEVICENAME 32

define CCHFORMNAME 32

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

if (_WIN32_WINNT ge ((OSVER(NTDDI_WINXPSP2)) shr 16))
_devicemodeA            struct
dmDeviceName            BYTE CCHDEVICENAME dup(?)
dmSpecVersion           WORD ?
dmDriverVersion         WORD ?
dmSize                  WORD ?
dmDriverExtra           WORD ?
dmFields                DWORD ?
union
 struct
  dmOrientation         sword ?
  dmPaperSize           sword ?
  dmPaperLength         sword ?
  dmPaperWidth          sword ?
  dmScale               sword ?
  dmCopies              sword ?
  dmDefaultSource       sword ?
  dmPrintQuality        sword ?
 ends
 struct
  dmPosition            POINTL <>
  dmDisplayOrientation  DWORD ?
  dmDisplayFixedOutput  DWORD ?
 ends
ends
dmColor                 sword ?
dmDuplex                sword ?
dmYResolution           sword ?
dmTTOption              sword ?
dmCollate               sword ?
dmFormName              BYTE CCHFORMNAME dup(?)
dmLogPixels             WORD ?
dmBitsPerPel            DWORD ?
dmPelsWidth             DWORD ?
dmPelsHeight            DWORD ?
union
 dmDisplayFlags         DWORD ?
 dmNup                  DWORD ?
ends
dmDisplayFrequency      DWORD ?
if(WINVER ge 0x0400)
dmICMMethod             DWORD ?
dmICMIntent             DWORD ?
dmMediaType             DWORD ?
dmDitherType            DWORD ?
dmReserved1             DWORD ?
dmReserved2             DWORD ?
if (WINVER ge 0x0500) or (_WIN32_WINNT ge _WIN32_WINNT_NT4)
dmPanningWidth          DWORD ?
dmPanningHeight         DWORD ?
endif
endif
_devicemodeA            ends
DEVMODEA                typedef _devicemodeA
PDEVMODEA               typedef ptr _devicemodeA
NPDEVMODEA              typedef ptr _devicemodeA
LPDEVMODEA              typedef ptr _devicemodeA
_devicemodeW            struct
dmDeviceName            WCHAR CCHDEVICENAME dup(?)
dmSpecVersion           WORD ?
dmDriverVersion         WORD ?
dmSize                  WORD ?
dmDriverExtra           WORD ?
dmFields                DWORD ?
union
 struct
  dmOrientation         sword ?
  dmPaperSize           sword ?
  dmPaperLength         sword ?
  dmPaperWidth          sword ?
  dmScale               sword ?
  dmCopies              sword ?
  dmDefaultSource       sword ?
  dmPrintQuality        sword ?
 ends
 struct
  dmPosition            POINTL <>
  dmDisplayOrientation  DWORD ?
  dmDisplayFixedOutput  DWORD ?
 ends
ends
dmColor                 sword ?
dmDuplex                sword ?
dmYResolution           sword ?
dmTTOption              sword ?
dmCollate               sword ?
dmFormName              WCHAR CCHFORMNAME dup(?)
dmLogPixels             WORD ?
dmBitsPerPel            DWORD ?
dmPelsWidth             DWORD ?
dmPelsHeight            DWORD ?
union
 dmDisplayFlags         DWORD ?
 dmNup                  DWORD ?
ends
dmDisplayFrequency      DWORD ?
if(WINVER ge 0x0400)
dmICMMethod             DWORD ?
dmICMIntent             DWORD ?
dmMediaType             DWORD ?
dmDitherType            DWORD ?
dmReserved1             DWORD ?
dmReserved2             DWORD ?
if (WINVER ge 0x0500) or (_WIN32_WINNT ge _WIN32_WINNT_NT4)
dmPanningWidth          DWORD ?
dmPanningHeight         DWORD ?
endif
endif
_devicemodeW            ends
DEVMODEW                typedef _devicemodeW
PDEVMODEW               typedef ptr _devicemodeW
NPDEVMODEW              typedef ptr _devicemodeW
LPDEVMODEW              typedef ptr _devicemodeW
ifdef _UNICODE
DEVMODE                 typedef DEVMODEW
PDEVMODE                typedef PDEVMODEW
NPDEVMODE               typedef NPDEVMODEW
LPDEVMODE               typedef LPDEVMODEW
else
DEVMODE                 typedef DEVMODEA
PDEVMODE                typedef PDEVMODEA
NPDEVMODE               typedef NPDEVMODEA
LPDEVMODE               typedef LPDEVMODEA
endif
else
_devicemodeA            struct
dmDeviceName            BYTE CCHDEVICENAME dup(?)
dmSpecVersion           WORD ?
dmDriverVersion         WORD ?
dmSize                  WORD ?
dmDriverExtra           WORD ?
dmFields                DWORD ?
union
 struct
  dmOrientation         sword ?
  dmPaperSize           sword ?
  dmPaperLength         sword ?
  dmPaperWidth          sword ?
 ends
 dmPosition             POINTL <>
ends
dmScale                 sword ?
dmCopies                sword ?
dmDefaultSource         sword ?
dmPrintQuality          sword ?
dmColor                 sword ?
dmDuplex                sword ?
dmYResolution           sword ?
dmTTOption              sword ?
dmCollate               sword ?
dmFormName              BYTE CCHFORMNAME dup(?)
dmLogPixels             WORD ?
dmBitsPerPel            DWORD ?
dmPelsWidth             DWORD ?
dmPelsHeight            DWORD ?
union
 dmDisplayFlags         DWORD ?
 dmNup                  DWORD ?
ends
dmDisplayFrequency      DWORD ?
if(WINVER ge 0x0400)
dmICMMethod             DWORD ?
dmICMIntent             DWORD ?
dmMediaType             DWORD ?
dmDitherType            DWORD ?
dmReserved1             DWORD ?
dmReserved2             DWORD ?
if (WINVER ge 0x0500) or (_WIN32_WINNT ge _WIN32_WINNT_NT4)
dmPanningWidth          DWORD ?
dmPanningHeight         DWORD ?
endif
endif
_devicemodeA            ends
DEVMODEA                typedef _devicemodeA
PDEVMODEA               typedef ptr _devicemodeA
NPDEVMODEA              typedef ptr _devicemodeA
LPDEVMODEA              typedef ptr _devicemodeA
_devicemodeW            struct
dmDeviceName            WCHAR CCHDEVICENAME dup(?)
dmSpecVersion           WORD ?
dmDriverVersion         WORD ?
dmSize                  WORD ?
dmDriverExtra           WORD ?
dmFields                DWORD ?
union
 struct
  dmOrientation         sword ?
  dmPaperSize           sword ?
  dmPaperLength         sword ?
  dmPaperWidth          sword ?
 ends
 dmPosition             POINTL <>
ends
dmScale                 sword ?
dmCopies                sword ?
dmDefaultSource         sword ?
dmPrintQuality          sword ?
dmColor                 sword ?
dmDuplex                sword ?
dmYResolution           sword ?
dmTTOption              sword ?
dmCollate               sword ?
dmFormName              WCHAR CCHFORMNAME dup(?)
dmLogPixels             WORD ?
dmBitsPerPel            DWORD ?
dmPelsWidth             DWORD ?
dmPelsHeight            DWORD ?
union
 dmDisplayFlags         DWORD ?
 dmNup                  DWORD ?
ends
dmDisplayFrequency      DWORD ?
if(WINVER ge 0x0400)
dmICMMethod             DWORD ?
dmICMIntent             DWORD ?
dmMediaType             DWORD ?
dmDitherType            DWORD ?
dmReserved1             DWORD ?
dmReserved2             DWORD ?
if (WINVER ge 0x0500) or (_WIN32_WINNT ge _WIN32_WINNT_NT4)
dmPanningWidth          DWORD ?
dmPanningHeight         DWORD ?
endif
endif
_devicemodeW            ends
DEVMODEW                typedef _devicemodeW
PDEVMODEW               typedef ptr _devicemodeW
NPDEVMODEW              typedef ptr _devicemodeW
LPDEVMODEW              typedef ptr _devicemodeW
ifdef _UNICODE
DEVMODE                 typedef DEVMODEW
PDEVMODE                typedef PDEVMODEW
NPDEVMODE               typedef NPDEVMODEW
LPDEVMODE               typedef LPDEVMODEW
else
DEVMODE                 typedef DEVMODEA
PDEVMODE                typedef PDEVMODEA
NPDEVMODE               typedef NPDEVMODEA
LPDEVMODE               typedef LPDEVMODEA
endif
endif

endif

if (WINVER ge 0x0500) or (_WIN32_WINNT ge _WIN32_WINNT_NT4)
define DM_SPECVERSION 0x0401
elseif (WINVER ge 0x0400)
define DM_SPECVERSION 0x0400
else
define DM_SPECVERSION 0x0320
endif

define DM_ORIENTATION          0x00000001
define DM_PAPERSIZE            0x00000002
define DM_PAPERLENGTH          0x00000004
define DM_PAPERWIDTH           0x00000008
define DM_SCALE                0x00000010
if(WINVER ge 0x0500)
define DM_POSITION             0x00000020
define DM_NUP                  0x00000040
endif
if(WINVER ge 0x0501)
define DM_DISPLAYORIENTATION   0x00000080
endif
define DM_COPIES               0x00000100
define DM_DEFAULTSOURCE        0x00000200
define DM_PRINTQUALITY         0x00000400
define DM_COLOR                0x00000800
define DM_DUPLEX               0x00001000
define DM_YRESOLUTION          0x00002000
define DM_TTOPTION             0x00004000
define DM_COLLATE              0x00008000
define DM_FORMNAME             0x00010000
define DM_LOGPIXELS            0x00020000
define DM_BITSPERPEL           0x00040000
define DM_PELSWIDTH            0x00080000
define DM_PELSHEIGHT           0x00100000
define DM_DISPLAYFLAGS         0x00200000
define DM_DISPLAYFREQUENCY     0x00400000
if(WINVER ge 0x0400)
define DM_ICMMETHOD            0x00800000
define DM_ICMINTENT            0x01000000
define DM_MEDIATYPE            0x02000000
define DM_DITHERTYPE           0x04000000
define DM_PANNINGWIDTH         0x08000000
define DM_PANNINGHEIGHT        0x10000000
endif
if(WINVER ge 0x0501)
define DM_DISPLAYFIXEDOUTPUT   0x20000000
endif

define DMORIENT_PORTRAIT   1
define DMORIENT_LANDSCAPE  2

define DMPAPER_FIRST                DMPAPER_LETTER
define DMPAPER_LETTER               1
define DMPAPER_LETTERSMALL          2
define DMPAPER_TABLOID              3
define DMPAPER_LEDGER               4
define DMPAPER_LEGAL                5
define DMPAPER_STATEMENT            6
define DMPAPER_EXECUTIVE            7
define DMPAPER_A3                   8
define DMPAPER_A4                   9
define DMPAPER_A4SMALL             10
define DMPAPER_A5                  11
define DMPAPER_B4                  12
define DMPAPER_B5                  13
define DMPAPER_FOLIO               14
define DMPAPER_QUARTO              15
define DMPAPER_10X14               16
define DMPAPER_11X17               17
define DMPAPER_NOTE                18
define DMPAPER_ENV_9               19
define DMPAPER_ENV_10              20
define DMPAPER_ENV_11              21
define DMPAPER_ENV_12              22
define DMPAPER_ENV_14              23
define DMPAPER_CSHEET              24
define DMPAPER_DSHEET              25
define DMPAPER_ESHEET              26
define DMPAPER_ENV_DL              27
define DMPAPER_ENV_C5              28
define DMPAPER_ENV_C3              29
define DMPAPER_ENV_C4              30
define DMPAPER_ENV_C6              31
define DMPAPER_ENV_C65             32
define DMPAPER_ENV_B4              33
define DMPAPER_ENV_B5              34
define DMPAPER_ENV_B6              35
define DMPAPER_ENV_ITALY           36
define DMPAPER_ENV_MONARCH         37
define DMPAPER_ENV_PERSONAL        38
define DMPAPER_FANFOLD_US          39
define DMPAPER_FANFOLD_STD_GERMAN  40
define DMPAPER_FANFOLD_LGL_GERMAN  41
if(WINVER ge 0x0400)
define DMPAPER_ISO_B4              42
define DMPAPER_JAPANESE_POSTCARD   43
define DMPAPER_9X11                44
define DMPAPER_10X11               45
define DMPAPER_15X11               46
define DMPAPER_ENV_INVITE          47
define DMPAPER_RESERVED_48         48
define DMPAPER_RESERVED_49         49
define DMPAPER_LETTER_EXTRA        50
define DMPAPER_LEGAL_EXTRA         51
define DMPAPER_TABLOID_EXTRA       52
define DMPAPER_A4_EXTRA            53
define DMPAPER_LETTER_TRANSVERSE   54
define DMPAPER_A4_TRANSVERSE       55
define DMPAPER_LETTER_EXTRA_TRANSVERSE 56
define DMPAPER_A_PLUS              57
define DMPAPER_B_PLUS              58
define DMPAPER_LETTER_PLUS         59
define DMPAPER_A4_PLUS             60
define DMPAPER_A5_TRANSVERSE       61
define DMPAPER_B5_TRANSVERSE       62
define DMPAPER_A3_EXTRA            63
define DMPAPER_A5_EXTRA            64
define DMPAPER_B5_EXTRA            65
define DMPAPER_A2                  66
define DMPAPER_A3_TRANSVERSE       67
define DMPAPER_A3_EXTRA_TRANSVERSE 68
endif

if(WINVER ge 0x0500)
define DMPAPER_DBL_JAPANESE_POSTCARD 69
define DMPAPER_A6                  70
define DMPAPER_JENV_KAKU2          71
define DMPAPER_JENV_KAKU3          72
define DMPAPER_JENV_CHOU3          73
define DMPAPER_JENV_CHOU4          74
define DMPAPER_LETTER_ROTATED      75
define DMPAPER_A3_ROTATED          76
define DMPAPER_A4_ROTATED          77
define DMPAPER_A5_ROTATED          78
define DMPAPER_B4_JIS_ROTATED      79
define DMPAPER_B5_JIS_ROTATED      80
define DMPAPER_JAPANESE_POSTCARD_ROTATED 81
define DMPAPER_DBL_JAPANESE_POSTCARD_ROTATED 82
define DMPAPER_A6_ROTATED          83
define DMPAPER_JENV_KAKU2_ROTATED  84
define DMPAPER_JENV_KAKU3_ROTATED  85
define DMPAPER_JENV_CHOU3_ROTATED  86
define DMPAPER_JENV_CHOU4_ROTATED  87
define DMPAPER_B6_JIS              88
define DMPAPER_B6_JIS_ROTATED      89
define DMPAPER_12X11               90
define DMPAPER_JENV_YOU4           91
define DMPAPER_JENV_YOU4_ROTATED   92
define DMPAPER_P16K                93
define DMPAPER_P32K                94
define DMPAPER_P32KBIG             95
define DMPAPER_PENV_1              96
define DMPAPER_PENV_2              97
define DMPAPER_PENV_3              98
define DMPAPER_PENV_4              99
define DMPAPER_PENV_5              100
define DMPAPER_PENV_6              101
define DMPAPER_PENV_7              102
define DMPAPER_PENV_8              103
define DMPAPER_PENV_9              104
define DMPAPER_PENV_10             105
define DMPAPER_P16K_ROTATED        106
define DMPAPER_P32K_ROTATED        107
define DMPAPER_P32KBIG_ROTATED     108
define DMPAPER_PENV_1_ROTATED      109
define DMPAPER_PENV_2_ROTATED      110
define DMPAPER_PENV_3_ROTATED      111
define DMPAPER_PENV_4_ROTATED      112
define DMPAPER_PENV_5_ROTATED      113
define DMPAPER_PENV_6_ROTATED      114
define DMPAPER_PENV_7_ROTATED      115
define DMPAPER_PENV_8_ROTATED      116
define DMPAPER_PENV_9_ROTATED      117
define DMPAPER_PENV_10_ROTATED     118
endif

if (WINVER ge 0x0500)
define DMPAPER_LAST                DMPAPER_PENV_10_ROTATED
elseif (WINVER ge 0x0400)
define DMPAPER_LAST                DMPAPER_A3_EXTRA_TRANSVERSE
else
define DMPAPER_LAST                DMPAPER_FANFOLD_LGL_GERMAN
endif

define DMPAPER_USER                256

define DMBIN_FIRST         DMBIN_UPPER
define DMBIN_UPPER         1
define DMBIN_ONLYONE       1
define DMBIN_LOWER         2
define DMBIN_MIDDLE        3
define DMBIN_MANUAL        4
define DMBIN_ENVELOPE      5
define DMBIN_ENVMANUAL     6
define DMBIN_AUTO          7
define DMBIN_TRACTOR       8
define DMBIN_SMALLFMT      9
define DMBIN_LARGEFMT      10
define DMBIN_LARGECAPACITY 11
define DMBIN_CASSETTE      14
define DMBIN_FORMSOURCE    15
define DMBIN_LAST          DMBIN_FORMSOURCE

define DMBIN_USER          256

define DMRES_DRAFT         (-1)
define DMRES_LOW           (-2)
define DMRES_MEDIUM        (-3)
define DMRES_HIGH          (-4)

define DMCOLOR_MONOCHROME  1
define DMCOLOR_COLOR       2

define DMDUP_SIMPLEX    1
define DMDUP_VERTICAL   2
define DMDUP_HORIZONTAL 3

define DMTT_BITMAP     1
define DMTT_DOWNLOAD   2
define DMTT_SUBDEV     3
if(WINVER ge 0x0400)
define DMTT_DOWNLOAD_OUTLINE 4
endif

define DMCOLLATE_FALSE  0
define DMCOLLATE_TRUE   1

if(WINVER ge 0x0501)
define DMDO_DEFAULT    0
define DMDO_90         1
define DMDO_180        2
define DMDO_270        3

define DMDFO_DEFAULT   0
define DMDFO_STRETCH   1
define DMDFO_CENTER    2
endif

define DM_INTERLACED           0x00000002
define DMDISPLAYFLAGS_TEXTMODE 0x00000004

define DMNUP_SYSTEM        1
define DMNUP_ONEUP         2

if(WINVER ge 0x0400)
define DMICMMETHOD_NONE    1
define DMICMMETHOD_SYSTEM  2
define DMICMMETHOD_DRIVER  3
define DMICMMETHOD_DEVICE  4

define DMICMMETHOD_USER  256

define DMICM_SATURATE          1
define DMICM_CONTRAST          2
define DMICM_COLORIMETRIC       3
define DMICM_ABS_COLORIMETRIC   4

define DMICM_USER        256

define DMMEDIA_STANDARD      1
define DMMEDIA_TRANSPARENCY  2
define DMMEDIA_GLOSSY        3

define DMMEDIA_USER        256

define DMDITHER_NONE       1
define DMDITHER_COARSE     2
define DMDITHER_FINE       3
define DMDITHER_LINEART    4
define DMDITHER_ERRORDIFFUSION 5
define DMDITHER_RESERVED6      6
define DMDITHER_RESERVED7      7
define DMDITHER_RESERVED8      8
define DMDITHER_RESERVED9      9
define DMDITHER_GRAYSCALE  10

define DMDITHER_USER     256
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

_DISPLAY_DEVICEA        struct
cb                      DWORD ?
DeviceName              CHAR 32 dup(?)
DeviceString            CHAR 128 dup(?)
StateFlags              DWORD ?
DeviceID                CHAR 128 dup(?)
DeviceKey               CHAR 128 dup(?)
_DISPLAY_DEVICEA        ends
DISPLAY_DEVICEA         typedef _DISPLAY_DEVICEA
PDISPLAY_DEVICEA        typedef ptr _DISPLAY_DEVICEA
LPDISPLAY_DEVICEA       typedef ptr _DISPLAY_DEVICEA
_DISPLAY_DEVICEW        struct
cb                      DWORD ?
DeviceName              WCHAR 32 dup(?)
DeviceString            WCHAR 128 dup(?)
StateFlags              DWORD ?
DeviceID                WCHAR 128 dup(?)
DeviceKey               WCHAR 128 dup(?)
_DISPLAY_DEVICEW        ends
DISPLAY_DEVICEW         typedef _DISPLAY_DEVICEW
PDISPLAY_DEVICEW        typedef ptr _DISPLAY_DEVICEW
LPDISPLAY_DEVICEW       typedef ptr _DISPLAY_DEVICEW
ifdef _UNICODE
DISPLAY_DEVICE          typedef DISPLAY_DEVICEW
PDISPLAY_DEVICE         typedef PDISPLAY_DEVICEW
LPDISPLAY_DEVICE        typedef LPDISPLAY_DEVICEW
else
DISPLAY_DEVICE          typedef DISPLAY_DEVICEA
PDISPLAY_DEVICE         typedef PDISPLAY_DEVICEA
LPDISPLAY_DEVICE        typedef LPDISPLAY_DEVICEA
endif

endif

define DISPLAY_DEVICE_ATTACHED_TO_DESKTOP      0x00000001
define DISPLAY_DEVICE_MULTI_DRIVER             0x00000002
define DISPLAY_DEVICE_PRIMARY_DEVICE           0x00000004
define DISPLAY_DEVICE_MIRRORING_DRIVER         0x00000008
define DISPLAY_DEVICE_VGA_COMPATIBLE           0x00000010
if (_WIN32_WINNT ge _WIN32_WINNT_WIN2K)
define DISPLAY_DEVICE_REMOVABLE                0x00000020
endif
if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)
define DISPLAY_DEVICE_ACC_DRIVER               0x00000040
endif
define DISPLAY_DEVICE_MODESPRUNED              0x08000000
if (_WIN32_WINNT ge _WIN32_WINNT_WIN2K)
define DISPLAY_DEVICE_REMOTE                   0x04000000
define DISPLAY_DEVICE_DISCONNECT               0x02000000
endif
define DISPLAY_DEVICE_TS_COMPATIBLE            0x00200000
if (_WIN32_WINNT ge _WIN32_WINNT_LONGHORN)
define DISPLAY_DEVICE_UNSAFE_MODES_ON          0x00080000
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN2K)
define DISPLAY_DEVICE_ACTIVE              0x00000001
define DISPLAY_DEVICE_ATTACHED            0x00000002
endif

if(WINVER ge 0x0601)

define DISPLAYCONFIG_MAXPATH 1024

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

DISPLAYCONFIG_RATIONAL  struct
Numerator               UINT32 ?
Denominator             UINT32 ?
DISPLAYCONFIG_RATIONAL  ends

.enum DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY {
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_OTHER                   = -1,
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_HD15                    =  0,
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_SVIDEO                  =  1,
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_COMPOSITE_VIDEO         =  2,
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_COMPONENT_VIDEO         =  3,
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_DVI                     =  4,
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_HDMI                    =  5,
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_LVDS                    =  6,
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_D_JPN                   =  8,
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_SDI                     =  9,
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_DISPLAYPORT_EXTERNAL    = 10,
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_DISPLAYPORT_EMBEDDED    = 11,
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_UDI_EXTERNAL            = 12,
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_UDI_EMBEDDED            = 13,
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_SDTVDONGLE              = 14,
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_MIRACAST                = 15,
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_INTERNAL                = 0x80000000,
    DISPLAYCONFIG_OUTPUT_TECHNOLOGY_FORCE_UINT32            = 0xFFFFFFFF
}

.enum DISPLAYCONFIG_SCANLINE_ORDERING {
    DISPLAYCONFIG_SCANLINE_ORDERING_UNSPECIFIED                 = 0,
    DISPLAYCONFIG_SCANLINE_ORDERING_PROGRESSIVE                 = 1,
    DISPLAYCONFIG_SCANLINE_ORDERING_INTERLACED                  = 2,
    DISPLAYCONFIG_SCANLINE_ORDERING_INTERLACED_UPPERFIELDFIRST  = DISPLAYCONFIG_SCANLINE_ORDERING_INTERLACED,
    DISPLAYCONFIG_SCANLINE_ORDERING_INTERLACED_LOWERFIELDFIRST  = 3,
    DISPLAYCONFIG_SCANLINE_ORDERING_FORCE_UINT32                = 0xFFFFFFFF
}

DISPLAYCONFIG_2DREGION  struct
_cx                     UINT32 ?
cy                      UINT32 ?
DISPLAYCONFIG_2DREGION  ends

DISPLAYCONFIG_VIDEO_SIGNAL_INFO struct
pixelRate               UINT64 ?
hSyncFreq               DISPLAYCONFIG_RATIONAL <>
vSyncFreq               DISPLAYCONFIG_RATIONAL <>
activeSize              DISPLAYCONFIG_2DREGION <>
totalSize               DISPLAYCONFIG_2DREGION <>
union
 record AdditionalSignalInfo
  videoStandard         UINT32 : 16 ?
  vSyncFreqDivider      UINT32 :  6 ?
  reserved              UINT32 : 10 ?
 ends
 videoStandard          UINT32 ?
ends
scanLineOrdering        DISPLAYCONFIG_SCANLINE_ORDERING ?
DISPLAYCONFIG_VIDEO_SIGNAL_INFO ends

.enum DISPLAYCONFIG_SCALING {
    DISPLAYCONFIG_SCALING_IDENTITY                  = 1,
    DISPLAYCONFIG_SCALING_CENTERED                  = 2,
    DISPLAYCONFIG_SCALING_STRETCHED                 = 3,
    DISPLAYCONFIG_SCALING_ASPECTRATIOCENTEREDMAX    = 4,
    DISPLAYCONFIG_SCALING_CUSTOM                    = 5,
    DISPLAYCONFIG_SCALING_PREFERRED                 = 128,
    DISPLAYCONFIG_SCALING_FORCE_UINT32              = 0xFFFFFFFF
}

.enum DISPLAYCONFIG_ROTATION {
    DISPLAYCONFIG_ROTATION_IDENTITY     = 1,
    DISPLAYCONFIG_ROTATION_ROTATE90     = 2,
    DISPLAYCONFIG_ROTATION_ROTATE180    = 3,
    DISPLAYCONFIG_ROTATION_ROTATE270    = 4,
    DISPLAYCONFIG_ROTATION_FORCE_UINT32 = 0xFFFFFFFF
}

.enum DISPLAYCONFIG_MODE_INFO_TYPE {
    DISPLAYCONFIG_MODE_INFO_TYPE_SOURCE = 1,
    DISPLAYCONFIG_MODE_INFO_TYPE_TARGET = 2,
    DISPLAYCONFIG_MODE_INFO_TYPE_FORCE_UINT32 = 0xFFFFFFFF
}

.enum DISPLAYCONFIG_PIXELFORMAT {
    DISPLAYCONFIG_PIXELFORMAT_8BPP          = 1,
    DISPLAYCONFIG_PIXELFORMAT_16BPP         = 2,
    DISPLAYCONFIG_PIXELFORMAT_24BPP         = 3,
    DISPLAYCONFIG_PIXELFORMAT_32BPP         = 4,
    DISPLAYCONFIG_PIXELFORMAT_NONGDI        = 5,
    DISPLAYCONFIG_PIXELFORMAT_FORCE_UINT32  = 0xffffffff
}

DISPLAYCONFIG_SOURCE_MODE struct
width                   UINT32 ?
height                  UINT32 ?
pixelFormat             DISPLAYCONFIG_PIXELFORMAT ?
position                POINTL <>
DISPLAYCONFIG_SOURCE_MODE ends

DISPLAYCONFIG_TARGET_MODE struct
targetVideoSignalInfo   DISPLAYCONFIG_VIDEO_SIGNAL_INFO <>
DISPLAYCONFIG_TARGET_MODE ends

DISPLAYCONFIG_MODE_INFO struct
infoType                DISPLAYCONFIG_MODE_INFO_TYPE ?
id                      UINT32 ?
adapterId               LUID <>
union
 targetMode             DISPLAYCONFIG_TARGET_MODE <>
 sourceMode             DISPLAYCONFIG_SOURCE_MODE <>
ends
DISPLAYCONFIG_MODE_INFO ends

define DISPLAYCONFIG_PATH_MODE_IDX_INVALID     0xffffffff

DISPLAYCONFIG_PATH_SOURCE_INFO struct
adapterId               LUID <>
id                      UINT32 ?
modeInfoIdx             UINT32 ?
statusFlags             UINT32 ?
DISPLAYCONFIG_PATH_SOURCE_INFO ends

define DISPLAYCONFIG_SOURCE_IN_USE     0x00000001

DISPLAYCONFIG_PATH_TARGET_INFO struct
adapterId               LUID <>
id                      UINT32 ?
modeInfoIdx             UINT32 ?
outputTechnology        DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY ?
rotation                DISPLAYCONFIG_ROTATION ?
scaling                 DISPLAYCONFIG_SCALING ?
refreshRate             DISPLAYCONFIG_RATIONAL <>
scanLineOrdering        DISPLAYCONFIG_SCANLINE_ORDERING ?
targetAvailable         BOOL ?
statusFlags             UINT32 ?
DISPLAYCONFIG_PATH_TARGET_INFO ends

define DISPLAYCONFIG_TARGET_IN_USE                         0x00000001
define DISPLAYCONFIG_TARGET_FORCIBLE                       0x00000002
define DISPLAYCONFIG_TARGET_FORCED_AVAILABILITY_BOOT       0x00000004
define DISPLAYCONFIG_TARGET_FORCED_AVAILABILITY_PATH       0x00000008
define DISPLAYCONFIG_TARGET_FORCED_AVAILABILITY_SYSTEM     0x00000010

DISPLAYCONFIG_PATH_INFO struct
sourceInfo              DISPLAYCONFIG_PATH_SOURCE_INFO <>
targetInfo              DISPLAYCONFIG_PATH_TARGET_INFO <>
flags                   UINT32 ?
DISPLAYCONFIG_PATH_INFO ends

define DISPLAYCONFIG_PATH_ACTIVE       0x00000001

.enum DISPLAYCONFIG_TOPOLOGY_ID {
      DISPLAYCONFIG_TOPOLOGY_INTERNAL       = 0x00000001,
      DISPLAYCONFIG_TOPOLOGY_CLONE          = 0x00000002,
      DISPLAYCONFIG_TOPOLOGY_EXTEND         = 0x00000004,
      DISPLAYCONFIG_TOPOLOGY_EXTERNAL       = 0x00000008,
      DISPLAYCONFIG_TOPOLOGY_FORCE_UINT32   = 0xFFFFFFFF
}

.enum DISPLAYCONFIG_DEVICE_INFO_TYPE {
      DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME             = 1,
      DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME             = 2,
      DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_PREFERRED_MODE   = 3,
      DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME            = 4,
      DISPLAYCONFIG_DEVICE_INFO_SET_TARGET_PERSISTENCE      = 5,
      DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_BASE_TYPE        = 6,
      DISPLAYCONFIG_DEVICE_INFO_FORCE_UINT32                = 0xFFFFFFFF
}

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

DISPLAYCONFIG_DEVICE_INFO_HEADER struct
type                    DISPLAYCONFIG_DEVICE_INFO_TYPE ?
size                    UINT32 ?
adapterId               LUID <>
id                      UINT32 ?
DISPLAYCONFIG_DEVICE_INFO_HEADER ends

endif
;.pragma endregion

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

DISPLAYCONFIG_SOURCE_DEVICE_NAME struct
header                  DISPLAYCONFIG_DEVICE_INFO_HEADER <>
viewGdiDeviceName       WCHAR CCHDEVICENAME dup(?)
DISPLAYCONFIG_SOURCE_DEVICE_NAME ends

DISPLAYCONFIG_TARGET_DEVICE_NAME_FLAGS struct
union
 record
  friendlyNameFromEdid  UINT32 :  1 ?
  friendlyNameForced    UINT32 :  1 ?
  edidIdsValid          UINT32 :  1 ?
  reserved              UINT32 : 29 ?
 ends
 value                  UINT32 ?
ends
DISPLAYCONFIG_TARGET_DEVICE_NAME_FLAGS ends

DISPLAYCONFIG_TARGET_DEVICE_NAME struct
header                  DISPLAYCONFIG_DEVICE_INFO_HEADER <>
flags                   DISPLAYCONFIG_TARGET_DEVICE_NAME_FLAGS <>
outputTechnology        DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY ?
edidManufactureId       UINT16 ?
edidProductCodeId       UINT16 ?
connectorInstance       UINT32 ?
monitorFriendlyDeviceNameW CHAR 64 dup(?)
monitorDevicePath       WCHAR 128 dup(?)
DISPLAYCONFIG_TARGET_DEVICE_NAME ends

DISPLAYCONFIG_TARGET_PREFERRED_MODE struct
header                  DISPLAYCONFIG_DEVICE_INFO_HEADER <>
width                   UINT32 ?
height                  UINT32 ?
targetMode              DISPLAYCONFIG_TARGET_MODE <>
DISPLAYCONFIG_TARGET_PREFERRED_MODE ends

DISPLAYCONFIG_ADAPTER_NAME struct
header                  DISPLAYCONFIG_DEVICE_INFO_HEADER <>
adapterDevicePath       WCHAR 128 dup(?)
DISPLAYCONFIG_ADAPTER_NAME ends

DISPLAYCONFIG_TARGET_BASE_TYPE struct
header                  DISPLAYCONFIG_DEVICE_INFO_HEADER <>
baseOutputTechnology    DISPLAYCONFIG_VIDEO_OUTPUT_TECHNOLOGY ?
DISPLAYCONFIG_TARGET_BASE_TYPE ends

DISPLAYCONFIG_SET_TARGET_PERSISTENCE struct
header                  DISPLAYCONFIG_DEVICE_INFO_HEADER <>
union
 record
  bootPersistenceOn     UINT32 :  1 ?
  reserved              UINT32 : 31 ?
 ends
 value                  UINT32 ?
ends
DISPLAYCONFIG_SET_TARGET_PERSISTENCE ends

endif

define QDC_ALL_PATHS                   0x00000001
define QDC_ONLY_ACTIVE_PATHS           0x00000002
define QDC_DATABASE_CURRENT            0x00000004

define SDC_TOPOLOGY_INTERNAL           0x00000001
define SDC_TOPOLOGY_CLONE              0x00000002
define SDC_TOPOLOGY_EXTEND             0x00000004
define SDC_TOPOLOGY_EXTERNAL           0x00000008
define SDC_TOPOLOGY_SUPPLIED           0x00000010
define SDC_USE_DATABASE_CURRENT        (SDC_TOPOLOGY_INTERNAL or SDC_TOPOLOGY_CLONE or SDC_TOPOLOGY_EXTEND or SDC_TOPOLOGY_EXTERNAL)

define SDC_USE_SUPPLIED_DISPLAY_CONFIG 0x00000020
define SDC_VALIDATE                    0x00000040
define SDC_APPLY                       0x00000080
define SDC_NO_OPTIMIZATION             0x00000100
define SDC_SAVE_TO_DATABASE            0x00000200
define SDC_ALLOW_CHANGES               0x00000400
define SDC_PATH_PERSIST_IF_REQUIRED    0x00000800
define SDC_FORCE_MODE_ENUMERATION      0x00001000
define SDC_ALLOW_PATH_ORDER_CHANGES    0x00002000

endif

define RDH_RECTANGLES  1

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

_RGNDATAHEADER          struct
dwSize                  DWORD ?
iType                   DWORD ?
nCount                  DWORD ?
nRgnSize                DWORD ?
rcBound                 RECT <>
_RGNDATAHEADER          ends
RGNDATAHEADER           typedef _RGNDATAHEADER
PRGNDATAHEADER          typedef ptr _RGNDATAHEADER

_RGNDATA                struct
rdh                     RGNDATAHEADER <>
Buffer                  sbyte 1 dup(?)
_RGNDATA                ends
RGNDATA                 typedef _RGNDATA
PRGNDATA                typedef ptr _RGNDATA
NPRGNDATA               typedef ptr _RGNDATA
LPRGNDATA               typedef ptr _RGNDATA

endif

define SYSRGN  4

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

_ABC                    struct
abcA                    sdword ?
abcB                    UINT ?
abcC                    sdword ?
_ABC                    ends
ABC                     typedef _ABC
PABC                    typedef ptr _ABC
NPABC                   typedef ptr _ABC
LPABC                   typedef ptr _ABC

_ABCFLOAT               struct
abcfA                   FLOAT ?
abcfB                   FLOAT ?
abcfC                   FLOAT ?
_ABCFLOAT               ends
ABCFLOAT                typedef _ABCFLOAT
PABCFLOAT               typedef ptr _ABCFLOAT
NPABCFLOAT              typedef ptr _ABCFLOAT
LPABCFLOAT              typedef ptr _ABCFLOAT

endif

ifndef NOTEXTMETRIC

ifdef _MAC
.pragma pack(push, 4)
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

_OUTLINETEXTMETRICA     struct
otmSize                 UINT ?
otmTextMetrics          TEXTMETRICA <>
otmFiller               BYTE ?
otmPanoseNumber         PANOSE <>
otmfsSelection          UINT ?
otmfsType               UINT ?
otmsCharSlopeRise       sdword ?
otmsCharSlopeRun        sdword ?
otmItalicAngle          sdword ?
otmEMSquare             UINT ?
otmAscent               sdword ?
otmDescent              sdword ?
otmLineGap              UINT ?
otmsCapEmHeight         UINT ?
otmsXHeight             UINT ?
otmrcFontBox            RECT <>
otmMacAscent            sdword ?
otmMacDescent           sdword ?
otmMacLineGap           UINT ?
otmusMinimumPPEM        UINT ?
otmptSubscriptSize      POINT <>
otmptSubscriptOffset    POINT <>
otmptSuperscriptSize    POINT <>
otmptSuperscriptOffset  POINT <>
otmsStrikeoutSize       UINT ?
otmsStrikeoutPosition   sdword ?
otmsUnderscoreSize      sdword ?
otmsUnderscorePosition  sdword ?
otmpFamilyName          PSTR ?
otmpFaceName            PSTR ?
otmpStyleName           PSTR ?
otmpFullName            PSTR ?
_OUTLINETEXTMETRICA     ends
OUTLINETEXTMETRICA      typedef _OUTLINETEXTMETRICA
POUTLINETEXTMETRICA     typedef ptr _OUTLINETEXTMETRICA
NPOUTLINETEXTMETRICA    typedef ptr _OUTLINETEXTMETRICA
LPOUTLINETEXTMETRICA    typedef ptr _OUTLINETEXTMETRICA
_OUTLINETEXTMETRICW     struct
otmSize                 UINT ?
otmTextMetrics          TEXTMETRICW <>
otmFiller               BYTE ?
otmPanoseNumber         PANOSE <>
otmfsSelection          UINT ?
otmfsType               UINT ?
otmsCharSlopeRise       sdword ?
otmsCharSlopeRun        sdword ?
otmItalicAngle          sdword ?
otmEMSquare             UINT ?
otmAscent               sdword ?
otmDescent              sdword ?
otmLineGap              UINT ?
otmsCapEmHeight         UINT ?
otmsXHeight             UINT ?
otmrcFontBox            RECT <>
otmMacAscent            sdword ?
otmMacDescent           sdword ?
otmMacLineGap           UINT ?
otmusMinimumPPEM        UINT ?
otmptSubscriptSize      POINT <>
otmptSubscriptOffset    POINT <>
otmptSuperscriptSize    POINT <>
otmptSuperscriptOffset  POINT <>
otmsStrikeoutSize       UINT ?
otmsStrikeoutPosition   sdword ?
otmsUnderscoreSize      sdword ?
otmsUnderscorePosition  sdword ?
otmpFamilyName          PSTR ?
otmpFaceName            PSTR ?
otmpStyleName           PSTR ?
otmpFullName            PSTR ?
_OUTLINETEXTMETRICW     ends
OUTLINETEXTMETRICW      typedef _OUTLINETEXTMETRICW
POUTLINETEXTMETRICW     typedef ptr _OUTLINETEXTMETRICW
NPOUTLINETEXTMETRICW    typedef ptr _OUTLINETEXTMETRICW
LPOUTLINETEXTMETRICW    typedef ptr _OUTLINETEXTMETRICW
ifdef _UNICODE
OUTLINETEXTMETRIC       typedef OUTLINETEXTMETRICW
POUTLINETEXTMETRIC      typedef POUTLINETEXTMETRICW
NPOUTLINETEXTMETRIC     typedef NPOUTLINETEXTMETRICW
LPOUTLINETEXTMETRIC     typedef LPOUTLINETEXTMETRICW
else
OUTLINETEXTMETRIC       typedef OUTLINETEXTMETRICA
POUTLINETEXTMETRIC      typedef POUTLINETEXTMETRICA
NPOUTLINETEXTMETRIC     typedef NPOUTLINETEXTMETRICA
LPOUTLINETEXTMETRIC     typedef LPOUTLINETEXTMETRICA
endif

endif

ifdef _MAC
.pragma pack(pop)
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

tagPOLYTEXTA            struct
x                       sdword ?
y                       sdword ?
n                       UINT ?
lpstr                   LPCSTR ?
uiFlags                 UINT ?
_rcl                    RECT <>
pdx                     ptr sdword ?
tagPOLYTEXTA            ends
POLYTEXTA               typedef tagPOLYTEXTA
PPOLYTEXTA              typedef ptr tagPOLYTEXTA
NPPOLYTEXTA             typedef ptr tagPOLYTEXTA
LPPOLYTEXTA             typedef ptr tagPOLYTEXTA
tagPOLYTEXTW            struct
x                       sdword ?
y                       sdword ?
n                       UINT ?
lpstr                   LPCWSTR ?
uiFlags                 UINT ?
_rcl                    RECT <>
pdx                     ptr sdword ?
tagPOLYTEXTW            ends
POLYTEXTW               typedef tagPOLYTEXTW
PPOLYTEXTW              typedef ptr tagPOLYTEXTW
NPPOLYTEXTW             typedef ptr tagPOLYTEXTW
LPPOLYTEXTW             typedef ptr tagPOLYTEXTW
ifdef _UNICODE
POLYTEXT                typedef POLYTEXTW
PPOLYTEXT               typedef PPOLYTEXTW
NPPOLYTEXT              typedef NPPOLYTEXTW
LPPOLYTEXT              typedef LPPOLYTEXTW
else
POLYTEXT                typedef POLYTEXTA
PPOLYTEXT               typedef PPOLYTEXTA
NPPOLYTEXT              typedef NPPOLYTEXTA
LPPOLYTEXT              typedef LPPOLYTEXTA
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

_FIXED                  struct
ifndef _MAC
fract                   WORD ?
value                   sword ?
else
value                   sword ?
fract                   WORD ?
endif
_FIXED                  ends
FIXED                   typedef _FIXED

_MAT2                   struct
eM11                    FIXED <>
eM12                    FIXED <>
eM21                    FIXED <>
eM22                    FIXED <>
_MAT2                   ends
MAT2                    typedef _MAT2
LPMAT2                  typedef ptr _MAT2

_GLYPHMETRICS           struct
gmBlackBoxX             UINT ?
gmBlackBoxY             UINT ?
gmptGlyphOrigin         POINT <>
gmCellIncX              sword ?
gmCellIncY              sword ?
_GLYPHMETRICS           ends
GLYPHMETRICS            typedef _GLYPHMETRICS
LPGLYPHMETRICS          typedef ptr _GLYPHMETRICS

endif

define GGO_METRICS        0
define GGO_BITMAP         1
define GGO_NATIVE         2
define GGO_BEZIER         3

if(WINVER ge 0x0400)
define  GGO_GRAY2_BITMAP   4
define  GGO_GRAY4_BITMAP   5
define  GGO_GRAY8_BITMAP   6
define  GGO_GLYPH_INDEX    0x0080
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN2K)
define  GGO_UNHINTED       0x0100
endif

define TT_POLYGON_TYPE   24

define TT_PRIM_LINE       1
define TT_PRIM_QSPLINE    2
define TT_PRIM_CSPLINE    3

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

tagPOINTFX              struct
x                       FIXED <>
y                       FIXED <>
tagPOINTFX              ends
POINTFX                 typedef tagPOINTFX
LPPOINTFX               typedef ptr tagPOINTFX

tagTTPOLYCURVE          struct
wType                   WORD ?
cpfx                    WORD ?
apfx                    POINTFX 1 dup(<>)
tagTTPOLYCURVE          ends
TTPOLYCURVE             typedef tagTTPOLYCURVE
LPTTPOLYCURVE           typedef ptr tagTTPOLYCURVE

tagTTPOLYGONHEADER      struct
cb                      DWORD ?
dwType                  DWORD ?
pfxStart                POINTFX <>
tagTTPOLYGONHEADER      ends
TTPOLYGONHEADER         typedef tagTTPOLYGONHEADER
LPTTPOLYGONHEADER       typedef ptr tagTTPOLYGONHEADER

endif

if(WINVER ge 0x0400)
define GCP_DBCS           0x0001
define GCP_REORDER        0x0002
define GCP_USEKERNING     0x0008
define GCP_GLYPHSHAPE     0x0010
define GCP_LIGATE         0x0020
define GCP_DIACRITIC      0x0100
define GCP_KASHIDA        0x0400
define GCP_ERROR          0x8000
define FLI_MASK           0x103B

define GCP_JUSTIFY        0x00010000
define FLI_GLYPHS         0x00040000
define GCP_CLASSIN        0x00080000
define GCP_MAXEXTENT      0x00100000
define GCP_JUSTIFYIN      0x00200000
define GCP_DISPLAYZWG      0x00400000
define GCP_SYMSWAPOFF      0x00800000
define GCP_NUMERICOVERRIDE 0x01000000
define GCP_NEUTRALOVERRIDE 0x02000000
define GCP_NUMERICSLATIN   0x04000000
define GCP_NUMERICSLOCAL   0x08000000

define GCPCLASS_LATIN                  1
define GCPCLASS_HEBREW                 2
define GCPCLASS_ARABIC                 2
define GCPCLASS_NEUTRAL                3
define GCPCLASS_LOCALNUMBER            4
define GCPCLASS_LATINNUMBER            5
define GCPCLASS_LATINNUMERICTERMINATOR 6
define GCPCLASS_LATINNUMERICSEPARATOR  7
define GCPCLASS_NUMERICSEPARATOR       8
define GCPCLASS_PREBOUNDLTR         0x80
define GCPCLASS_PREBOUNDRTL         0x40
define GCPCLASS_POSTBOUNDLTR        0x20
define GCPCLASS_POSTBOUNDRTL        0x10

define GCPGLYPH_LINKBEFORE          0x8000
define GCPGLYPH_LINKAFTER           0x4000

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

tagGCP_RESULTSA         struct
lStructSize             DWORD ?
lpOutString             LPSTR ?
lpOrder                 ptr ?
lpDx                    ptr ?
lpCaretPos              ptr ?
lpClass                 LPSTR ?
lpGlyphs                LPWSTR ?
nGlyphs                 UINT ?
nMaxFit                 sdword ?
tagGCP_RESULTSA         ends
GCP_RESULTSA            typedef tagGCP_RESULTSA
LPGCP_RESULTSA          typedef ptr tagGCP_RESULTSA
tagGCP_RESULTSW         struct
lStructSize             DWORD ?
lpOutString             LPWSTR ?
lpOrder                 ptr ?
lpDx                    ptr ?
lpCaretPos              ptr ?
lpClass                 LPSTR ?
lpGlyphs                LPWSTR ?
nGlyphs                 UINT ?
nMaxFit                 sdword ?
tagGCP_RESULTSW         ends
GCP_RESULTSW            typedef tagGCP_RESULTSW
 LPGCP_RESULTSW         typedef ptr tagGCP_RESULTSW
ifdef _UNICODE
GCP_RESULTS             typedef GCP_RESULTSW
LPGCP_RESULTS           typedef LPGCP_RESULTSW
else
GCP_RESULTS             typedef GCP_RESULTSA
LPGCP_RESULTS           typedef LPGCP_RESULTSA
endif

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

_RASTERIZER_STATUS      struct
nSize                   sword ?
wFlags                  sword ?
nLanguageID             sword ?
_RASTERIZER_STATUS      ends
RASTERIZER_STATUS       typedef _RASTERIZER_STATUS
LPRASTERIZER_STATUS     typedef ptr _RASTERIZER_STATUS

endif

define TT_AVAILABLE    0x0001
define TT_ENABLED      0x0002

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

tagPIXELFORMATDESCRIPTOR struct
nSize                   WORD ?
nVersion                WORD ?
dwFlags                 DWORD ?
iPixelType              BYTE ?
cColorBits              BYTE ?
cRedBits                BYTE ?
cRedShift               BYTE ?
cGreenBits              BYTE ?
cGreenShift             BYTE ?
cBlueBits               BYTE ?
cBlueShift              BYTE ?
cAlphaBits              BYTE ?
cAlphaShift             BYTE ?
cAccumBits              BYTE ?
cAccumRedBits           BYTE ?
cAccumGreenBits         BYTE ?
cAccumBlueBits          BYTE ?
cAccumAlphaBits         BYTE ?
cDepthBits              BYTE ?
cStencilBits            BYTE ?
cAuxBuffers             BYTE ?
iLayerType              BYTE ?
bReserved               BYTE ?
dwLayerMask             DWORD ?
dwVisibleMask           DWORD ?
dwDamageMask            DWORD ?
tagPIXELFORMATDESCRIPTOR ends
PIXELFORMATDESCRIPTOR   typedef tagPIXELFORMATDESCRIPTOR
PPIXELFORMATDESCRIPTOR  typedef ptr tagPIXELFORMATDESCRIPTOR
LPPIXELFORMATDESCRIPTOR typedef ptr tagPIXELFORMATDESCRIPTOR

endif

define PFD_TYPE_RGBA        0
define PFD_TYPE_COLORINDEX  1

define PFD_MAIN_PLANE       0
define PFD_OVERLAY_PLANE    1
define PFD_UNDERLAY_PLANE   (-1)

define PFD_DOUBLEBUFFER            0x00000001
define PFD_STEREO                  0x00000002
define PFD_DRAW_TO_WINDOW          0x00000004
define PFD_DRAW_TO_BITMAP          0x00000008
define PFD_SUPPORT_GDI             0x00000010
define PFD_SUPPORT_OPENGL          0x00000020
define PFD_GENERIC_FORMAT          0x00000040
define PFD_NEED_PALETTE            0x00000080
define PFD_NEED_SYSTEM_PALETTE     0x00000100
define PFD_SWAP_EXCHANGE           0x00000200
define PFD_SWAP_COPY               0x00000400
define PFD_SWAP_LAYER_BUFFERS      0x00000800
define PFD_GENERIC_ACCELERATED     0x00001000
define PFD_SUPPORT_DIRECTDRAW      0x00002000
define PFD_DIRECT3D_ACCELERATED    0x00004000
define PFD_SUPPORT_COMPOSITION     0x00008000

define PFD_DEPTH_DONTCARE          0x20000000
define PFD_DOUBLEBUFFER_DONTCARE   0x40000000
define PFD_STEREO_DONTCARE         0x80000000

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifdef STRICT

if not defined(NOTEXTMETRIC)
CALLBACK(OLDFONTENUMPROCA, :ptr, :ptr, :DWORD, :LPARAM)
CALLBACK(OLDFONTENUMPROCW, :ptr, :ptr, :DWORD, :LPARAM)
ifdef _UNICODE
define OLDFONTENUMPROC  <OLDFONTENUMPROCW>
else
define OLDFONTENUMPROC  <OLDFONTENUMPROCA>
endif
else
CALLBACK(OLDFONTENUMPROCA, :ptr, :ptr, :DWORD, :LPARAM)
CALLBACK(OLDFONTENUMPROCW, :ptr, :ptr, :DWORD, :LPARAM)
ifdef _UNICODE
define OLDFONTENUMPROC  <OLDFONTENUMPROCW>
else
define OLDFONTENUMPROC  <OLDFONTENUMPROCA>
endif
endif

FONTENUMPROCA           typedef OLDFONTENUMPROCA
FONTENUMPROCW           typedef OLDFONTENUMPROCW
ifdef _UNICODE
FONTENUMPROC            typedef FONTENUMPROCW
else
FONTENUMPROC            typedef FONTENUMPROCA
endif

CALLBACK(GOBJENUMPROC, :LPVOID, :LPARAM)
CALLBACK(LINEDDAPROC, :sdword, :sdword, :LPARAM)
else
OLDFONTENUMPROC         typedef FARPROC
FONTENUMPROCA           typedef FARPROC
FONTENUMPROCW           typedef FARPROC
ifdef _UNICODE
FONTENUMPROC            typedef FONTENUMPROCW
else
FONTENUMPROC            typedef FONTENUMPROCA
endif
GOBJENUMPROC            typedef FARPROC
LINEDDAPROC             typedef FARPROC
endif

endif

.pragma comment(lib, gdi32)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

AddFontResourceA proto WINAPI :LPCSTR
AddFontResourceW proto WINAPI :LPCWSTR
ifdef _UNICODE
define AddFontResource  <AddFontResourceW>
else
define AddFontResource  <AddFontResourceA>
endif

AnimatePalette proto WINAPI :HPALETTE, :UINT, :UINT, :ptr
Arc proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword
BitBlt proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword, :HDC, :sdword, :sdword, :DWORD
CancelDC proto WINAPI :HDC
Chord proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword
ChoosePixelFormat proto WINAPI :HDC, :ptr
CloseMetaFile proto WINAPI :HDC
CombineRgn proto WINAPI :HRGN, :HRGN, :HRGN, :sdword
CopyMetaFileA proto WINAPI :HMETAFILE, :LPCSTR
CopyMetaFileW proto WINAPI :HMETAFILE, :LPCWSTR
ifdef _UNICODE
define CopyMetaFile  <CopyMetaFileW>
else
define CopyMetaFile  <CopyMetaFileA>
endif
CreateBitmap proto WINAPI :sdword, :sdword, :UINT, :UINT, :ptr
CreateBitmapIndirect proto WINAPI :ptr
CreateBrushIndirect proto WINAPI :ptr
CreateCompatibleBitmap proto WINAPI :HDC, :sdword, :sdword
CreateDiscardableBitmap proto WINAPI :HDC, :sdword, :sdword
CreateCompatibleDC proto WINAPI :HDC
CreateDCA proto WINAPI :LPCSTR, :LPCSTR, :LPCSTR, :ptr
CreateDCW proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR, :ptr
ifdef _UNICODE
define CreateDC  <CreateDCW>
else
define CreateDC  <CreateDCA>
endif
CreateDIBitmap proto WINAPI :HDC, :ptr, :DWORD, :ptr, :ptr, :UINT
CreateDIBPatternBrush proto WINAPI :HGLOBAL, :UINT
CreateDIBPatternBrushPt proto WINAPI :ptr, :UINT
CreateEllipticRgn proto WINAPI :sdword, :sdword, :sdword, :sdword
CreateEllipticRgnIndirect proto WINAPI :ptr
CreateFontIndirectA proto WINAPI :ptr
CreateFontIndirectW proto WINAPI :ptr
ifdef _UNICODE
define CreateFontIndirect  <CreateFontIndirectW>
else
define CreateFontIndirect  <CreateFontIndirectA>
endif
CreateFontA proto WINAPI :sdword, :sdword, :sdword, :sdword, :sdword, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :LPCSTR
CreateFontW proto WINAPI :sdword, :sdword, :sdword, :sdword, :sdword, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :LPCWSTR
ifdef _UNICODE
define CreateFont  <CreateFontW>
else
define CreateFont  <CreateFontA>
endif

CreateHatchBrush proto WINAPI :sdword, :COLORREF
CreateICA proto WINAPI :LPCSTR, :LPCSTR, :LPCSTR, :ptr
CreateICW proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR, :ptr
ifdef _UNICODE
define CreateIC  <CreateICW>
else
define CreateIC  <CreateICA>
endif
CreateMetaFileA proto WINAPI :LPCSTR
CreateMetaFileW proto WINAPI :LPCWSTR
ifdef _UNICODE
define CreateMetaFile  <CreateMetaFileW>
else
define CreateMetaFile  <CreateMetaFileA>
endif
CreatePalette proto WINAPI :ptr
CreatePen proto WINAPI :sdword, :sdword, :COLORREF
CreatePenIndirect proto WINAPI :ptr
CreatePolyPolygonRgn proto WINAPI :ptr, :ptr, :sdword, :sdword
CreatePatternBrush proto WINAPI :HBITMAP
CreateRectRgn proto WINAPI :sdword, :sdword, :sdword, :sdword
CreateRectRgnIndirect proto WINAPI :ptr
CreateRoundRectRgn proto WINAPI :sdword, :sdword, :sdword, :sdword, :sdword, :sdword
CreateScalableFontResourceA proto WINAPI :DWORD, :LPCSTR, :LPCSTR, :LPCSTR
CreateScalableFontResourceW proto WINAPI :DWORD, :LPCWSTR, :LPCWSTR, :LPCWSTR
ifdef _UNICODE
define CreateScalableFontResource  <CreateScalableFontResourceW>
else
define CreateScalableFontResource  <CreateScalableFontResourceA>
endif
CreateSolidBrush proto WINAPI :COLORREF

DeleteDC proto WINAPI :HDC
DeleteMetaFile proto WINAPI :HMETAFILE
DeleteObject proto WINAPI :HGDIOBJ
DescribePixelFormat proto WINAPI :HDC, :SINT, :UINT, :LPPIXELFORMATDESCRIPTOR

CALLBACK(LPFNDEVMODE, :HWND, :HMODULE, :LPDEVMODE, :LPSTR, :LPSTR, :LPDEVMODE, :LPSTR, :UINT)

CALLBACK(LPFNDEVCAPS, :LPSTR, :LPSTR, :UINT, :LPSTR, :LPDEVMODE)

endif

define DM_UPDATE           1
define DM_COPY             2
define DM_PROMPT           4
define DM_MODIFY           8

define DM_IN_BUFFER        DM_MODIFY
define DM_IN_PROMPT        DM_PROMPT
define DM_OUT_BUFFER       DM_COPY
define DM_OUT_DEFAULT      DM_UPDATE

define DC_FIELDS           1
define DC_PAPERS           2
define DC_PAPERSIZE        3
define DC_MINEXTENT        4
define DC_MAXEXTENT        5
define DC_BINS             6
define DC_DUPLEX           7
define DC_SIZE             8
define DC_EXTRA            9
define DC_VERSION          10
define DC_DRIVER           11
define DC_BINNAMES         12
define DC_ENUMRESOLUTIONS  13
define DC_FILEDEPENDENCIES 14
define DC_TRUETYPE         15
define DC_PAPERNAMES       16
define DC_ORIENTATION      17
define DC_COPIES           18
if(WINVER ge 0x0400)
define DC_BINADJUST            19
define DC_EMF_COMPLIANT        20
define DC_DATATYPE_PRODUCED    21
define DC_COLLATE              22
define DC_MANUFACTURER         23
define DC_MODEL                24
endif

if(WINVER ge 0x0500)
define DC_PERSONALITY          25
define DC_PRINTRATE            26
define DC_PRINTRATEUNIT        27
define   PRINTRATEUNIT_PPM     1
define   PRINTRATEUNIT_CPS     2
define   PRINTRATEUNIT_LPM     3
define   PRINTRATEUNIT_IPM     4
define DC_PRINTERMEM           28
define DC_MEDIAREADY           29
define DC_STAPLE               30
define DC_PRINTRATEPPM         31
define DC_COLORDEVICE          32
define DC_NUP                  33
if (_WIN32_WINNT ge _WIN32_WINNT_WIN2K)
define DC_MEDIATYPENAMES       34
define DC_MEDIATYPES           35
endif
endif

define DCTT_BITMAP             0x0000001
define DCTT_DOWNLOAD           0x0000002
define DCTT_SUBDEV             0x0000004
if(WINVER ge 0x0400)
define DCTT_DOWNLOAD_OUTLINE   0x0000008

define DCBA_FACEUPNONE       0x0000
define DCBA_FACEUPCENTER     0x0001
define DCBA_FACEUPLEFT       0x0002
define DCBA_FACEUPRIGHT      0x0003
define DCBA_FACEDOWNNONE     0x0100
define DCBA_FACEDOWNCENTER   0x0101
define DCBA_FACEDOWNLEFT     0x0102
define DCBA_FACEDOWNRIGHT    0x0103
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.pragma comment(lib, winspool)

DeviceCapabilitiesA proto WINAPI :LPCSTR, :LPCSTR, :WORD, :LPSTR, :ptr
DeviceCapabilitiesW proto WINAPI :LPCWSTR, :LPCWSTR, :WORD, :LPWSTR, :ptr
ifdef _UNICODE
define DeviceCapabilities  <DeviceCapabilitiesW>
else
define DeviceCapabilities  <DeviceCapabilitiesA>
endif

.pragma comment(lib, gdi32)

DrawEscape proto WINAPI :HDC, :SINT, :SINT, :LPCSTR
Ellipse proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword

if(WINVER ge 0x0400)
EnumFontFamiliesExA proto WINAPI :HDC, :LPLOGFONTA, :FONTENUMPROCA, :LPARAM, :DWORD
EnumFontFamiliesExW proto WINAPI :HDC, :LPLOGFONTW, :FONTENUMPROCW, :LPARAM, :DWORD
ifdef _UNICODE
define EnumFontFamiliesEx  <EnumFontFamiliesExW>
else
define EnumFontFamiliesEx  <EnumFontFamiliesExA>
endif
endif

EnumFontFamiliesA proto WINAPI :HDC, :LPCSTR, :FONTENUMPROCA, :LPARAM
EnumFontFamiliesW proto WINAPI :HDC, :LPCWSTR, :FONTENUMPROCW, :LPARAM
ifdef _UNICODE
define EnumFontFamilies  <EnumFontFamiliesW>
else
define EnumFontFamilies  <EnumFontFamiliesA>
endif
EnumFontsA proto WINAPI :HDC, :LPCSTR, :FONTENUMPROCA, :LPARAM
EnumFontsW proto WINAPI :HDC, :LPCWSTR, :FONTENUMPROCW, :LPARAM
ifdef _UNICODE
define EnumFonts  <EnumFontsW>
else
define EnumFonts  <EnumFontsA>
endif

ifdef STRICT
EnumObjects proto WINAPI :HDC, :sdword, :GOBJENUMPROC, :LPARAM
else
EnumObjects proto WINAPI :HDC, :sdword, :GOBJENUMPROC, :LPVOID
endif

EqualRgn proto WINAPI :HRGN, :HRGN
Escape proto WINAPI :HDC, :SINT, :SINT, :LPCSTR, :LPVOID
ExtEscape proto WINAPI :HDC, :SINT, :SINT, :LPCSTR, :SINT, :LPSTR
ExcludeClipRect proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword
ExtCreateRegion proto WINAPI :ptr, :DWORD, :ptr
ExtFloodFill proto WINAPI :HDC, :sdword, :sdword, :COLORREF, :UINT
FillRgn proto WINAPI :HDC, :HRGN, :HBRUSH
FloodFill proto WINAPI :HDC, :sdword, :sdword, :COLORREF
FrameRgn proto WINAPI :HDC, :HRGN, :HBRUSH, :sdword, :sdword
GetROP2 proto WINAPI :HDC
GetAspectRatioFilterEx proto WINAPI :HDC, :LPSIZE
GetBkColor proto WINAPI :HDC

if (_WIN32_WINNT ge _WIN32_WINNT_WIN2K)
GetDCBrushColor proto WINAPI :HDC
GetDCPenColor proto WINAPI :HDC
endif

GetBkMode proto WINAPI :HDC

GetBitmapBits proto WINAPI :HBITMAP, :LONG, :LPVOID

GetBitmapDimensionEx proto WINAPI :HBITMAP, :LPSIZE
GetBoundsRect proto WINAPI :HDC, :LPRECT, :UINT

GetBrushOrgEx proto WINAPI :HDC, :LPPOINT

GetCharWidthA proto WINAPI :HDC, :UINT, :UINT, :LPINT
GetCharWidthW proto WINAPI :HDC, :UINT, :UINT, :LPINT
ifdef _UNICODE
define GetCharWidth  <GetCharWidthW>
else
define GetCharWidth  <GetCharWidthA>
endif
GetCharWidth32A proto WINAPI :HDC, :UINT, :UINT, :LPINT
GetCharWidth32W proto WINAPI :HDC, :UINT, :UINT, :LPINT
ifdef _UNICODE
define GetCharWidth32  <GetCharWidth32W>
else
define GetCharWidth32  <GetCharWidth32A>
endif
GetCharWidthFloatA proto WINAPI :HDC, :UINT, :UINT, :PFLOAT
GetCharWidthFloatW proto WINAPI :HDC, :UINT, :UINT, :PFLOAT
ifdef _UNICODE
define GetCharWidthFloat  <GetCharWidthFloatW>
else
define GetCharWidthFloat  <GetCharWidthFloatA>
endif

GetCharABCWidthsA proto WINAPI :HDC, :UINT, :UINT, :LPABC
GetCharABCWidthsW proto WINAPI :HDC, :UINT, :UINT, :LPABC
ifdef _UNICODE
define GetCharABCWidths  <GetCharABCWidthsW>
else
define GetCharABCWidths  <GetCharABCWidthsA>
endif

GetCharABCWidthsFloatA proto WINAPI :HDC, :UINT, :UINT, :LPABCFLOAT
GetCharABCWidthsFloatW proto WINAPI :HDC, :UINT, :UINT, :LPABCFLOAT
ifdef _UNICODE
define GetCharABCWidthsFloat  <GetCharABCWidthsFloatW>
else
define GetCharABCWidthsFloat  <GetCharABCWidthsFloatA>
endif
GetClipBox proto WINAPI :HDC, :LPRECT
GetClipRgn proto WINAPI :HDC, :HRGN
GetMetaRgn proto WINAPI :HDC, :HRGN
GetCurrentObject proto WINAPI :HDC, :UINT
GetCurrentPositionEx proto WINAPI :HDC, :LPPOINT
GetDeviceCaps proto WINAPI :HDC, :sdword
GetDIBits proto WINAPI :HDC, :HBITMAP, :UINT, :UINT, :LPVOID, :LPBITMAPINFO, :UINT
GetFontData proto WINAPI :HDC, :DWORD, :DWORD, :LPVOID, :DWORD

GetGlyphOutlineA proto WINAPI :HDC, :UINT, :UINT, :LPGLYPHMETRICS, :DWORD, :LPVOID, :LPMAT2
GetGlyphOutlineW proto WINAPI :HDC, :UINT, :UINT, :LPGLYPHMETRICS, :DWORD, :LPVOID, :LPMAT2
ifdef _UNICODE
define GetGlyphOutline  <GetGlyphOutlineW>
else
define GetGlyphOutline  <GetGlyphOutlineA>
endif

GetGraphicsMode proto WINAPI :HDC
GetMapMode proto WINAPI :HDC
GetMetaFileBitsEx proto WINAPI :HMETAFILE, :UINT, :LPVOID
GetMetaFileA proto WINAPI :LPCSTR
GetMetaFileW proto WINAPI :LPCWSTR
ifdef _UNICODE
define GetMetaFile  <GetMetaFileW>
else
define GetMetaFile  <GetMetaFileA>
endif
GetNearestColor proto WINAPI :HDC, :COLORREF
GetNearestPaletteIndex proto WINAPI :HPALETTE, :COLORREF
GetObjectType proto WINAPI :HGDIOBJ

ifndef NOTEXTMETRIC

GetOutlineTextMetricsA proto WINAPI :HDC, :UINT, :LPOUTLINETEXTMETRICA
GetOutlineTextMetricsW proto WINAPI :HDC, :UINT, :LPOUTLINETEXTMETRICW
ifdef _UNICODE
define GetOutlineTextMetrics  <GetOutlineTextMetricsW>
else
define GetOutlineTextMetrics  <GetOutlineTextMetricsA>
endif

endif

GetPaletteEntries proto WINAPI :HPALETTE, :UINT, :UINT, :LPPALETTEENTRY
GetPixel proto WINAPI :HDC, :sdword, :sdword
GetPixelFormat proto WINAPI :HDC
GetPolyFillMode proto WINAPI :HDC
GetRasterizerCaps proto WINAPI :LPRASTERIZER_STATUS, :UINT

GetRandomRgn proto WINAPI :HDC, :HRGN, :SINT
GetRegionData proto WINAPI :HRGN, :DWORD, :LPRGNDATA
GetRgnBox proto WINAPI :HRGN, :LPRECT
GetStockObject proto WINAPI :sdword
GetStretchBltMode proto WINAPI :HDC
GetSystemPaletteEntries proto WINAPI :HDC, :UINT, :UINT, :LPPALETTEENTRY

GetSystemPaletteUse proto WINAPI :HDC
GetTextCharacterExtra proto WINAPI :HDC
GetTextAlign proto WINAPI :HDC
GetTextColor proto WINAPI :HDC

GetTextExtentPointA proto WINAPI :HDC, :LPCSTR, :sdword, :LPSIZE
GetTextExtentPointW proto WINAPI :HDC, :LPCWSTR, :sdword, :LPSIZE
ifdef _UNICODE
define GetTextExtentPoint  <GetTextExtentPointW>
else
define GetTextExtentPoint  <GetTextExtentPointA>
endif

GetTextExtentPoint32A proto WINAPI :HDC, :LPCSTR, :sdword, :LPSIZE
GetTextExtentPoint32W proto WINAPI :HDC, :LPCWSTR, :sdword, :LPSIZE
ifdef _UNICODE
define GetTextExtentPoint32  <GetTextExtentPoint32W>
else
define GetTextExtentPoint32  <GetTextExtentPoint32A>
endif

GetTextExtentExPointA proto WINAPI :HDC, :LPCSTR, :sdword, :sdword, :LPINT, :LPINT, :LPSIZE
GetTextExtentExPointW proto WINAPI :HDC, :LPCWSTR, :sdword, :sdword, :LPINT, :LPINT, :LPSIZE
ifdef _UNICODE
define GetTextExtentExPoint  <GetTextExtentExPointW>
else
define GetTextExtentExPoint  <GetTextExtentExPointA>
endif

if(WINVER ge 0x0400)
GetTextCharset proto WINAPI :HDC
GetTextCharsetInfo proto WINAPI :HDC, :LPFONTSIGNATURE, :DWORD
TranslateCharsetInfo proto WINAPI :ptr, :LPCHARSETINFO, :DWORD
GetFontLanguageInfo proto WINAPI :HDC
GetCharacterPlacementA proto WINAPI :HDC, :LPCSTR, :sdword, :sdword, :LPGCP_RESULTSA, :DWORD
GetCharacterPlacementW proto WINAPI :HDC, :LPCWSTR, :sdword, :sdword, :LPGCP_RESULTSW, :DWORD
ifdef _UNICODE
define GetCharacterPlacement  <GetCharacterPlacementW>
else
define GetCharacterPlacement  <GetCharacterPlacementA>
endif
endif

endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN2K)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

tagWCRANGE              struct
wcLow                   WCHAR ?
cGlyphs                 USHORT ?
tagWCRANGE              ends
WCRANGE                 typedef tagWCRANGE
PWCRANGE                typedef ptr tagWCRANGE
LPWCRANGE               typedef ptr tagWCRANGE

tagGLYPHSET             struct
cbThis                  DWORD ?
flAccel                 DWORD ?
cGlyphsSupported        DWORD ?
cRanges                 DWORD ?
ranges                  WCRANGE 1 dup(<>)
tagGLYPHSET             ends
GLYPHSET                typedef tagGLYPHSET
PGLYPHSET               typedef ptr tagGLYPHSET
LPGLYPHSET              typedef ptr tagGLYPHSET

define GS_8BIT_INDICES     0x00000001

define GGI_MARK_NONEXISTING_GLYPHS  0

GetFontUnicodeRanges proto WINAPI :HDC, :LPGLYPHSET
GetGlyphIndicesA proto WINAPI :HDC, :LPCSTR, :SINT, :LPWORD, :DWORD
GetGlyphIndicesW proto WINAPI :HDC, :LPCWSTR, :SINT, :LPWORD, :DWORD
ifdef _UNICODE
define GetGlyphIndices  <GetGlyphIndicesW>
else
define GetGlyphIndices  <GetGlyphIndicesA>
endif
GetTextExtentPointI proto WINAPI :HDC, :LPWORD, :sdword, :LPSIZE
GetTextExtentExPointI proto WINAPI :HDC, :LPWORD, :sdword, :sdword, :LPINT, :LPINT, :LPSIZE

GetCharWidthI proto WINAPI :HDC, :UINT, :UINT, :LPWORD, :LPINT
GetCharABCWidthsI proto WINAPI :HDC, :UINT , :UINT , :LPWORD, :LPABC

define STAMP_DESIGNVECTOR  (0x8000000 + 'd' + ('v' shl 8))
define STAMP_AXESLIST      (0x8000000 + 'a' + ('l' shl 8))
define MM_MAX_NUMAXES      16

tagDESIGNVECTOR         struct
dvReserved              DWORD ?
dvNumAxes               DWORD ?
dvValues                LONG MM_MAX_NUMAXES dup(?)
tagDESIGNVECTOR         ends
DESIGNVECTOR            typedef tagDESIGNVECTOR
PDESIGNVECTOR           typedef ptr tagDESIGNVECTOR
LPDESIGNVECTOR          typedef ptr tagDESIGNVECTOR

AddFontResourceExA proto WINAPI :LPCSTR, :DWORD, :PVOID
AddFontResourceExW proto WINAPI :LPCWSTR, :DWORD, :PVOID
ifdef _UNICODE
define AddFontResourceEx  <AddFontResourceExW>
else
define AddFontResourceEx  <AddFontResourceExA>
endif
RemoveFontResourceExA proto WINAPI :LPCSTR, :DWORD, :PVOID
RemoveFontResourceExW proto WINAPI :LPCWSTR, :DWORD, :PVOID
ifdef _UNICODE
define RemoveFontResourceEx  <RemoveFontResourceExW>
else
define RemoveFontResourceEx  <RemoveFontResourceExA>
endif
AddFontMemResourceEx proto WINAPI :PVOID, :DWORD, :PVOID, :ptr

RemoveFontMemResourceEx proto WINAPI :HANDLE
define FR_PRIVATE     0x10
define FR_NOT_ENUM    0x20

define MM_MAX_AXES_NAMELEN 16

tagAXISINFOA            struct
axMinValue              LONG ?
axMaxValue              LONG ?
axAxisName              BYTE MM_MAX_AXES_NAMELEN dup(?)
tagAXISINFOA            ends
AXISINFOA               typedef tagAXISINFOA
PAXISINFOA              typedef ptr tagAXISINFOA
LPAXISINFOA             typedef ptr tagAXISINFOA
tagAXISINFOW            struct
axMinValue              LONG ?
axMaxValue              LONG ?
axAxisName              WCHAR MM_MAX_AXES_NAMELEN dup(?)
tagAXISINFOW            ends
AXISINFOW               typedef tagAXISINFOW
PAXISINFOW              typedef ptr tagAXISINFOW
LPAXISINFOW             typedef ptr tagAXISINFOW
ifdef _UNICODE
AXISINFO                typedef AXISINFOW
PAXISINFO               typedef PAXISINFOW
LPAXISINFO              typedef LPAXISINFOW
else
AXISINFO                typedef AXISINFOA
PAXISINFO               typedef PAXISINFOA
LPAXISINFO              typedef LPAXISINFOA
endif

tagAXESLISTA            struct
axlReserved             DWORD ?
axlNumAxes              DWORD ?
axlAxisInfo             AXISINFOA MM_MAX_NUMAXES dup(<>)
tagAXESLISTA            ends
AXESLISTA               typedef tagAXESLISTA
PAXESLISTA              typedef ptr tagAXESLISTA
LPAXESLISTA             typedef ptr tagAXESLISTA
tagAXESLISTW            struct
axlReserved             DWORD ?
axlNumAxes              DWORD ?
axlAxisInfo             AXISINFOW MM_MAX_NUMAXES dup(<>)
tagAXESLISTW            ends
AXESLISTW               typedef tagAXESLISTW
PAXESLISTW              typedef ptr tagAXESLISTW
LPAXESLISTW             typedef ptr tagAXESLISTW
ifdef _UNICODE
AXESLIST                typedef AXESLISTW
PAXESLIST               typedef PAXESLISTW
LPAXESLIST              typedef LPAXESLISTW
else
AXESLIST                typedef AXESLISTA
PAXESLIST               typedef PAXESLISTA
LPAXESLIST              typedef LPAXESLISTA
endif

tagENUMLOGFONTEXDVA     struct
elfEnumLogfontEx        ENUMLOGFONTEXA <>
elfDesignVector         DESIGNVECTOR <>
tagENUMLOGFONTEXDVA     ends
ENUMLOGFONTEXDVA        typedef tagENUMLOGFONTEXDVA
PENUMLOGFONTEXDVA       typedef ptr tagENUMLOGFONTEXDVA
LPENUMLOGFONTEXDVA      typedef ptr tagENUMLOGFONTEXDVA
tagENUMLOGFONTEXDVW     struct
elfEnumLogfontEx        ENUMLOGFONTEXW <>
elfDesignVector         DESIGNVECTOR <>
tagENUMLOGFONTEXDVW     ends
ENUMLOGFONTEXDVW        typedef tagENUMLOGFONTEXDVW
PENUMLOGFONTEXDVW       typedef ptr tagENUMLOGFONTEXDVW
LPENUMLOGFONTEXDVW      typedef ptr tagENUMLOGFONTEXDVW
ifdef _UNICODE
ENUMLOGFONTEXDV         typedef ENUMLOGFONTEXDVW
PENUMLOGFONTEXDV        typedef PENUMLOGFONTEXDVW
LPENUMLOGFONTEXDV       typedef LPENUMLOGFONTEXDVW
else
ENUMLOGFONTEXDV         typedef ENUMLOGFONTEXDVA
PENUMLOGFONTEXDV        typedef PENUMLOGFONTEXDVA
LPENUMLOGFONTEXDV       typedef LPENUMLOGFONTEXDVA
endif

CreateFontIndirectExA proto WINAPI :ptr
CreateFontIndirectExW proto WINAPI :ptr
ifdef _UNICODE
define CreateFontIndirectEx  <CreateFontIndirectExW>
else
define CreateFontIndirectEx  <CreateFontIndirectExA>
endif

ifndef NOTEXTMETRIC
tagENUMTEXTMETRICA      struct
etmNewTextMetricEx      NEWTEXTMETRICEXA <>
etmAxesList             AXESLISTA <>
tagENUMTEXTMETRICA      ends
ENUMTEXTMETRICA         typedef tagENUMTEXTMETRICA
PENUMTEXTMETRICA        typedef ptr tagENUMTEXTMETRICA
LPENUMTEXTMETRICA       typedef ptr tagENUMTEXTMETRICA
tagENUMTEXTMETRICW      struct
etmNewTextMetricEx      NEWTEXTMETRICEXW <>
etmAxesList             AXESLISTW <>
tagENUMTEXTMETRICW      ends
ENUMTEXTMETRICW         typedef tagENUMTEXTMETRICW
PENUMTEXTMETRICW        typedef ptr tagENUMTEXTMETRICW
LPENUMTEXTMETRICW       typedef ptr tagENUMTEXTMETRICW
ifdef _UNICODE
ENUMTEXTMETRIC          typedef ENUMTEXTMETRICW
PENUMTEXTMETRIC         typedef PENUMTEXTMETRICW
LPENUMTEXTMETRIC        typedef LPENUMTEXTMETRICW
else
ENUMTEXTMETRIC          typedef ENUMTEXTMETRICA
PENUMTEXTMETRIC         typedef PENUMTEXTMETRICA
LPENUMTEXTMETRIC        typedef LPENUMTEXTMETRICA
endif
endif

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

GetViewportExtEx proto WINAPI :HDC, :LPSIZE
GetViewportOrgEx proto WINAPI :HDC, :LPPOINT
GetWindowExtEx proto WINAPI :HDC, :LPSIZE
GetWindowOrgEx proto WINAPI :HDC, :LPPOINT

IntersectClipRect proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword
InvertRgn proto WINAPI :HDC, :HRGN
LineDDA proto WINAPI :sdword, :sdword, :sdword, :sdword, :LINEDDAPROC, :LPARAM
LineTo proto WINAPI :HDC, :sdword, :sdword
MaskBlt proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword, :HDC, :sdword, :sdword, :HBITMAP, :sdword, :sdword, :DWORD
PlgBlt proto WINAPI :HDC, :ptr, :HDC, :sdword, :sdword, :sdword, :sdword, :HBITMAP, :sdword, :sdword

OffsetClipRgn proto WINAPI :HDC, :sdword, :sdword
OffsetRgn proto WINAPI :HRGN, :sdword, :sdword
PatBlt proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword, :DWORD
Pie proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword
PlayMetaFile proto WINAPI :HDC, :HMETAFILE
PaintRgn proto WINAPI :HDC, :HRGN
PolyPolygon proto WINAPI :HDC, :ptr, :ptr, :sdword
PtInRegion proto WINAPI :HRGN, :sdword, :sdword
PtVisible proto WINAPI :HDC, :sdword, :sdword
RectInRegion proto WINAPI :HRGN, :ptr
RectVisible proto WINAPI :HDC, :ptr
Rectangle proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword
RestoreDC proto WINAPI :HDC, :sdword
ResetDCA proto WINAPI :HDC, :ptr
ResetDCW proto WINAPI :HDC, :ptr
ifdef _UNICODE
define ResetDC  <ResetDCW>
else
define ResetDC  <ResetDCA>
endif
RealizePalette proto WINAPI :HDC
RemoveFontResourceA proto WINAPI :LPCSTR
RemoveFontResourceW proto WINAPI :LPCWSTR
ifdef _UNICODE
define RemoveFontResource  <RemoveFontResourceW>
else
define RemoveFontResource  <RemoveFontResourceA>
endif
RoundRect proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword
ResizePalette proto WINAPI :HPALETTE, :UINT

SaveDC proto WINAPI :HDC
SelectClipRgn proto WINAPI :HDC, :HRGN
ExtSelectClipRgn proto WINAPI :HDC, :HRGN, :sdword
SetMetaRgn proto WINAPI :HDC
SelectObject proto WINAPI :HDC, :HGDIOBJ
SelectPalette proto WINAPI :HDC, :HPALETTE, :BOOL
SetBkColor proto WINAPI :HDC, :COLORREF

if (_WIN32_WINNT ge _WIN32_WINNT_WIN2K)
SetDCBrushColor proto WINAPI :HDC, :COLORREF
SetDCPenColor proto WINAPI :HDC, :COLORREF
endif

SetBkMode proto WINAPI :HDC, :sdword

SetBitmapBits proto WINAPI :HBITMAP, :DWORD, :ptr

SetBoundsRect proto WINAPI :HDC, :ptr, :UINT
SetDIBits proto WINAPI :HDC, :HBITMAP, :UINT, :UINT, :ptr, :ptr, :UINT
SetDIBitsToDevice proto WINAPI :HDC, :sdword, :sdword, :DWORD, :DWORD, :sdword, :sdword, :UINT, :UINT, :ptr, :ptr, :UINT
SetMapperFlags proto WINAPI :HDC, :DWORD
SetGraphicsMode proto WINAPI :HDC, :sdword
SetMapMode proto WINAPI :HDC, :sdword

if(WINVER ge 0x0500)
SetLayout proto WINAPI :HDC, :DWORD
GetLayout proto WINAPI :HDC
endif

SetMetaFileBitsEx proto WINAPI :UINT, :ptr
SetPaletteEntries proto WINAPI :HPALETTE, :UINT, :UINT, :ptr
SetPixel proto WINAPI :HDC, :sdword, :sdword, :COLORREF
SetPixelV proto WINAPI :HDC, :sdword, :sdword, :COLORREF
SetPixelFormat proto WINAPI :HDC, :sdword, :ptr
SetPolyFillMode proto WINAPI :HDC, :sdword
StretchBlt proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword, :HDC, :sdword, :sdword, :sdword, :sdword, :DWORD
SetRectRgn proto WINAPI :HRGN, :sdword, :sdword, :sdword, :sdword
StretchDIBits proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :ptr, :ptr, :UINT, :DWORD
SetROP2 proto WINAPI :HDC, :sdword
SetStretchBltMode proto WINAPI :HDC, :sdword
SetSystemPaletteUse proto WINAPI :HDC, :UINT
SetTextCharacterExtra proto WINAPI :HDC, :sdword
SetTextColor proto WINAPI :HDC, :COLORREF
SetTextAlign proto WINAPI :HDC, :UINT
SetTextJustification proto WINAPI :HDC, :sdword, :sdword
UpdateColors proto WINAPI :HDC

endif

ifdef  COMBOX_SANDBOX

if (_WIN32_WINNT ge 0x0600)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

CALLBACK(GDIMARSHALLOC, :DWORD, :LPVOID)

CALLBACK(DDRAWMARSHCALLBACKMARSHAL, :HGDIOBJ, :LPVOID, :ptr)
CALLBACK(DDRAWMARSHCALLBACKUNMARSHAL, :LPVOID, :ptr, :ptr)
CALLBACK(DDRAWMARSHCALLBACKRELEASE, :LPVOID)

define GDIREGISTERDDRAWPACKETVERSION   0x1

GDIREGISTERDDRAWPACKET  struct
dwSize                  DWORD ?
dwVersion               DWORD ?
pfnDdMarshal            DDRAWMARSHCALLBACKMARSHAL ?
pfnDdUnmarshal          DDRAWMARSHCALLBACKUNMARSHAL ?
pfnDdRelease            DDRAWMARSHCALLBACKRELEASE ?
GDIREGISTERDDRAWPACKET  ends
PGDIREGISTERDDRAWPACKET typedef ptr GDIREGISTERDDRAWPACKET

GdiRegisterDdraw proto WINAPI :PGDIREGISTERDDRAWPACKET, :ptr

GdiMarshalSize proto WINAPI :VOID
GdiMarshal proto WINAPI :DWORD, :HGDIOBJ, :PVOID, :ULONG
GdiUnmarshal proto WINAPI :PVOID, :ULONG

endif

endif

endif

if (WINVER ge 0x0400)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

COLOR16                 typedef USHORT

_TRIVERTEX              struct
x                       LONG ?
y                       LONG ?
Red                     COLOR16 ?
Green                   COLOR16 ?
Blue                    COLOR16 ?
Alpha                   COLOR16 ?
_TRIVERTEX              ends
TRIVERTEX               typedef _TRIVERTEX
PTRIVERTEX              typedef ptr _TRIVERTEX
LPTRIVERTEX             typedef ptr _TRIVERTEX

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

_GRADIENT_TRIANGLE      struct
Vertex1                 ULONG ?
Vertex2                 ULONG ?
Vertex3                 ULONG ?
_GRADIENT_TRIANGLE      ends
GRADIENT_TRIANGLE       typedef _GRADIENT_TRIANGLE
PGRADIENT_TRIANGLE      typedef ptr _GRADIENT_TRIANGLE
LPGRADIENT_TRIANGLE     typedef ptr _GRADIENT_TRIANGLE

_GRADIENT_RECT          struct
UpperLeft               ULONG ?
LowerRight              ULONG ?
_GRADIENT_RECT          ends
GRADIENT_RECT           typedef _GRADIENT_RECT
PGRADIENT_RECT          typedef ptr _GRADIENT_RECT
LPGRADIENT_RECT         typedef ptr _GRADIENT_RECT

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

_BLENDFUNCTION          struct
BlendOp                 BYTE ?
BlendFlags              BYTE ?
SourceConstantAlpha     BYTE ?
AlphaFormat             BYTE ?
_BLENDFUNCTION          ends
BLENDFUNCTION           typedef _BLENDFUNCTION
PBLENDFUNCTION          typedef ptr _BLENDFUNCTION

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

define AC_SRC_OVER                 0x00
define AC_SRC_ALPHA                0x01

.pragma comment(lib, msimg32)

AlphaBlend proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword, :HDC, :sdword, :sdword, :sdword, :sdword, :BLENDFUNCTION

TransparentBlt proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword, :HDC, :sdword, :sdword, :sdword, :sdword, :UINT

define GRADIENT_FILL_RECT_H    0x00000000
define GRADIENT_FILL_RECT_V    0x00000001
define GRADIENT_FILL_TRIANGLE  0x00000002
define GRADIENT_FILL_OP_FLAG   0x000000ff

GradientFill proto WINAPI :HDC, :PTRIVERTEX, :ULONG, :PVOID, :ULONG, :ULONG

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

if (_WIN32_WINNT ge _WIN32_WINNT_WIN2K)

GdiAlphaBlend proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword, :HDC, :sdword, :sdword, :sdword, :sdword, :BLENDFUNCTION

GdiTransparentBlt proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword, :HDC, :sdword, :sdword, :sdword, :sdword, :UINT

GdiGradientFill proto WINAPI :HDC, :PTRIVERTEX, :ULONG, :PVOID, :ULONG, :ULONG

endif

.pragma comment(lib, gdi32)

ifndef NOMETAFILE

PlayMetaFileRecord proto WINAPI :HDC, :LPHANDLETABLE, :LPMETARECORD, :UINT

CALLBACK(MFENUMPROC, :HDC, :ptr, :ptr, :sdword, :LPARAM)
EnumMetaFile proto WINAPI :HDC, :HMETAFILE, :MFENUMPROC, :LPARAM

CALLBACK(ENHMFENUMPROC, :HDC, :ptr, :ptr, :sdword, :LPARAM)

CloseEnhMetaFile proto WINAPI :HDC
CopyEnhMetaFileA proto WINAPI :HENHMETAFILE, :LPCSTR
CopyEnhMetaFileW proto WINAPI :HENHMETAFILE, :LPCWSTR
ifdef _UNICODE
define CopyEnhMetaFile  <CopyEnhMetaFileW>
else
define CopyEnhMetaFile  <CopyEnhMetaFileA>
endif
CreateEnhMetaFileA proto WINAPI :HDC, :LPCSTR, :ptr, :LPCSTR
CreateEnhMetaFileW proto WINAPI :HDC, :LPCWSTR, :ptr, :LPCWSTR
ifdef _UNICODE
define CreateEnhMetaFile  <CreateEnhMetaFileW>
else
define CreateEnhMetaFile  <CreateEnhMetaFileA>
endif
DeleteEnhMetaFile proto WINAPI :HENHMETAFILE
EnumEnhMetaFile proto WINAPI :HDC, :HENHMETAFILE, :ENHMFENUMPROC, :LPVOID, :ptr
GetEnhMetaFileA proto WINAPI :LPCSTR
GetEnhMetaFileW proto WINAPI :LPCWSTR
ifdef _UNICODE
define GetEnhMetaFile  <GetEnhMetaFileW>
else
define GetEnhMetaFile  <GetEnhMetaFileA>
endif
GetEnhMetaFileBits proto WINAPI :HENHMETAFILE, :UINT, :LPBYTE
GetEnhMetaFileDescriptionA proto WINAPI :HENHMETAFILE, :UINT, :LPSTR
GetEnhMetaFileDescriptionW proto WINAPI :HENHMETAFILE, :UINT, :LPWSTR
ifdef _UNICODE
define GetEnhMetaFileDescription  <GetEnhMetaFileDescriptionW>
else
define GetEnhMetaFileDescription  <GetEnhMetaFileDescriptionA>
endif
GetEnhMetaFileHeader proto WINAPI :HENHMETAFILE, :UINT, :LPENHMETAHEADER
GetEnhMetaFilePaletteEntries proto WINAPI :HENHMETAFILE, :UINT, :LPPALETTEENTRY

GetEnhMetaFilePixelFormat proto WINAPI :HENHMETAFILE, :UINT, :LPPIXELFORMATDESCRIPTOR
GetWinMetaFileBits proto WINAPI :HENHMETAFILE, :UINT, :LPBYTE, :SINT, :HDC
PlayEnhMetaFile proto WINAPI :HDC, :HENHMETAFILE, :ptr
PlayEnhMetaFileRecord proto WINAPI :HDC, :LPHANDLETABLE, :ptr, :UINT

SetEnhMetaFileBits proto WINAPI :UINT, :ptr

SetWinMetaFileBits proto WINAPI :UINT, :ptr, :HDC, :ptr
GdiComment proto WINAPI :HDC, :UINT, :ptr

endif

ifndef NOTEXTMETRIC

GetTextMetricsA proto WINAPI :HDC, :LPTEXTMETRICA
GetTextMetricsW proto WINAPI :HDC, :LPTEXTMETRICW
ifdef _UNICODE
define GetTextMetrics  <GetTextMetricsW>
else
define GetTextMetrics  <GetTextMetricsA>
endif

if defined(_M_CEE)
undef GetTextMetrics
GetTextMetricsA proto WINAPI :endif, :lptm
endif

endif

tagDIBSECTION           struct
dsBm                    BITMAP <>
dsBmih                  BITMAPINFOHEADER <>
dsBitfields             DWORD 3 dup(?)
dshSection              HANDLE ?
dsOffset                DWORD ?
tagDIBSECTION           ends
DIBSECTION              typedef tagDIBSECTION
LPDIBSECTION            typedef ptr tagDIBSECTION
PDIBSECTION             typedef ptr tagDIBSECTION

AngleArc proto WINAPI :HDC, :sdword, :sdword, :DWORD, :FLOAT, :FLOAT
PolyPolyline proto WINAPI :HDC, :ptr, :ptr, :DWORD
GetWorldTransform proto WINAPI :HDC, :LPXFORM
SetWorldTransform proto WINAPI :HDC, :ptr
ModifyWorldTransform proto WINAPI :HDC, :ptr, :DWORD
CombineTransform proto WINAPI :LPXFORM, :ptr, :ptr

GDI_WIDTHBYTES proto watcall bits:LONG {
  add   eax,31
  and   eax,not 31
  shr   eax,3
  }
GDI_DIBWIDTHBYTES proto fastcall bi:ptr BITMAPINFOHEADER {
  movzx eax,[rcx].BITMAPINFOHEADER.biBitCount
  mul   [rcx].BITMAPINFOHEADER.biWidth
  GDI_WIDTHBYTES(eax)
  }
GDI__DIBSIZE proto fastcall bi:ptr BITMAPINFOHEADER {
  GDI_DIBWIDTHBYTES(bi)
  mul   [rcx].BITMAPINFOHEADER.biHeight
  }
GDI_DIBSIZE proto fastcall bi:ptr BITMAPINFOHEADER {
  GDI__DIBSIZE(bi)
  .if ( [rcx].BITMAPINFOHEADER.biHeight < 0 )
    imul eax,eax,-1
  .endif
  }

CreateDIBSection proto WINAPI :HDC, :LPBITMAPINFO, :UINT, :PVOID, :HANDLE, :DWORD
GetDIBColorTable proto WINAPI :HDC, :UINT, :UINT, :RGBQUAD
SetDIBColorTable proto WINAPI :HDC, :UINT, :UINT, :ptr

define CA_NEGATIVE                 0x0001
define CA_LOG_FILTER               0x0002

define ILLUMINANT_DEVICE_DEFAULT   0
define ILLUMINANT_A                1
define ILLUMINANT_B                2
define ILLUMINANT_C                3
define ILLUMINANT_D50              4
define ILLUMINANT_D55              5
define ILLUMINANT_D65              6
define ILLUMINANT_D75              7
define ILLUMINANT_F2               8
define ILLUMINANT_MAX_INDEX        ILLUMINANT_F2

define ILLUMINANT_TUNGSTEN         ILLUMINANT_A
define ILLUMINANT_DAYLIGHT         ILLUMINANT_C
define ILLUMINANT_FLUORESCENT      ILLUMINANT_F2
define ILLUMINANT_NTSC             ILLUMINANT_C

define RGB_GAMMA_MIN               02500
define RGB_GAMMA_MAX               65000

define REFERENCE_WHITE_MIN         6000
define REFERENCE_WHITE_MAX         10000
define REFERENCE_BLACK_MIN         0
define REFERENCE_BLACK_MAX         4000

define COLOR_ADJ_MIN               -100
define COLOR_ADJ_MAX               100

tagCOLORADJUSTMENT      struct
caSize                  WORD ?
caFlags                 WORD ?
caIlluminantIndex       WORD ?
caRedGamma              WORD ?
caGreenGamma            WORD ?
caBlueGamma             WORD ?
caReferenceBlack        WORD ?
caReferenceWhite        WORD ?
caContrast              SWORD ?
caBrightness            SWORD ?
caColorfulness          SWORD ?
caRedGreenTint          SWORD ?
tagCOLORADJUSTMENT      ends
COLORADJUSTMENT         typedef tagCOLORADJUSTMENT
PCOLORADJUSTMENT        typedef ptr tagCOLORADJUSTMENT
LPCOLORADJUSTMENT       typedef ptr tagCOLORADJUSTMENT

SetColorAdjustment proto WINAPI :HDC, :ptr
GetColorAdjustment proto WINAPI :HDC, :LPCOLORADJUSTMENT
CreateHalftonePalette proto WINAPI :HDC

ifdef STRICT
CALLBACK(ABORTPROC, :HDC, :sdword)
else
ABORTPROC               typedef FARPROC
endif

_DOCINFOA               struct
cbSize                  sdword ?
lpszDocName             LPCSTR ?
lpszOutput              LPCSTR ?
if (WINVER ge 0x0400)
lpszDatatype            LPCSTR ?
fwType                  DWORD ?
endif
_DOCINFOA               ends
DOCINFOA                typedef _DOCINFOA
LPDOCINFOA              typedef ptr _DOCINFOA
_DOCINFOW               struct
cbSize                  sdword ?
lpszDocName             LPCWSTR ?
lpszOutput              LPCWSTR ?
if (WINVER ge 0x0400)
lpszDatatype            LPCWSTR ?
fwType                  DWORD ?
endif
_DOCINFOW               ends
DOCINFOW                typedef _DOCINFOW
LPDOCINFOW              typedef ptr _DOCINFOW
ifdef _UNICODE
DOCINFO                 typedef DOCINFOW
LPDOCINFO               typedef LPDOCINFOW
else
DOCINFO                 typedef DOCINFOA
LPDOCINFO               typedef LPDOCINFOA
endif

if(WINVER ge 0x0400)
define DI_APPBANDING               0x00000001
define DI_ROPS_READ_DESTINATION    0x00000002
endif

StartDocA proto WINAPI :HDC, :ptr
StartDocW proto WINAPI :HDC, :ptr
ifdef _UNICODE
define StartDoc  <StartDocW>
else
define StartDoc  <StartDocA>
endif
EndDoc proto WINAPI :HDC
StartPage proto WINAPI :HDC
EndPage proto WINAPI :HDC
AbortDoc proto WINAPI :HDC
SetAbortProc proto WINAPI :HDC, :ABORTPROC

AbortPath proto WINAPI :HDC
ArcTo proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword
BeginPath proto WINAPI :HDC
CloseFigure proto WINAPI :HDC
EndPath proto WINAPI :HDC
FillPath proto WINAPI :HDC
FlattenPath proto WINAPI :HDC
GetPath proto WINAPI :HDC, :LPPOINT, :LPBYTE, :SINT
PathToRegion proto WINAPI :HDC
PolyDraw proto WINAPI :HDC, :LPPOINT, :LPBYTE, :SINT
SelectClipPath proto WINAPI :HDC, :sdword
SetArcDirection proto WINAPI :HDC, :sdword
SetMiterLimit proto WINAPI :HDC, :FLOAT, :PFLOAT
StrokeAndFillPath proto WINAPI :HDC
StrokePath proto WINAPI :HDC
WidenPath proto WINAPI :HDC
ExtCreatePen proto WINAPI :DWORD, :DWORD, :LPLOGBRUSH, :DWORD, :LPDWORD
GetMiterLimit proto WINAPI :HDC, :PFLOAT
GetArcDirection proto WINAPI :HDC

GetObjectA proto WINAPI :HGDIOBJ, :SINT, :LPVOID
GetObjectW proto WINAPI :HGDIOBJ, :SINT, :LPVOID
ifdef _UNICODE
define GetObject  <GetObjectW>
else
define GetObject  <GetObjectA>
endif

MoveToEx proto WINAPI :HDC, :sdword, :sdword, :LPPOINT
TextOutA proto WINAPI :HDC, :sdword, :sdword, :LPCSTR, :sdword
TextOutW proto WINAPI :HDC, :sdword, :sdword, :LPCWSTR, :sdword
ifdef _UNICODE
define TextOut  <TextOutW>
else
define TextOut  <TextOutA>
endif
ExtTextOutA proto WINAPI :HDC, :SINT, :SINT, :UINT, :LPRECT, :LPCSTR, :UINT, :LPINT
ExtTextOutW proto WINAPI :HDC, :SINT, :SINT, :UINT, :LPRECT, :LPCWSTR, :UINT, :LPINT
ifdef _UNICODE
define ExtTextOut  <ExtTextOutW>
else
define ExtTextOut  <ExtTextOutA>
endif
PolyTextOutA proto WINAPI :HDC, :ptr, :sdword
PolyTextOutW proto WINAPI :HDC, :ptr, :sdword
ifdef _UNICODE
define PolyTextOut  <PolyTextOutW>
else
define PolyTextOut  <PolyTextOutA>
endif

CreatePolygonRgn proto WINAPI :ptr, :sdword, :sdword
DPtoLP proto WINAPI :HDC, :LPPOINT, :SINT
LPtoDP proto WINAPI :HDC, :LPPOINT, :SINT
Polygon proto WINAPI :HDC, :ptr, :sdword
Polyline proto WINAPI :HDC, :ptr, :sdword

PolyBezier proto WINAPI :HDC, :ptr, :DWORD
PolyBezierTo proto WINAPI :HDC, :ptr, :DWORD
PolylineTo proto WINAPI :HDC, :ptr, :DWORD

SetViewportExtEx proto WINAPI :HDC, :sdword, :sdword, :LPSIZE
SetViewportOrgEx proto WINAPI :HDC, :sdword, :sdword, :LPPOINT
SetWindowExtEx proto WINAPI :HDC, :sdword, :sdword, :LPSIZE
SetWindowOrgEx proto WINAPI :HDC, :sdword, :sdword, :LPPOINT

OffsetViewportOrgEx proto WINAPI :HDC, :sdword, :sdword, :LPPOINT
OffsetWindowOrgEx proto WINAPI :HDC, :sdword, :sdword, :LPPOINT
ScaleViewportExtEx proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword, :LPSIZE
ScaleWindowExtEx proto WINAPI :HDC, :sdword, :sdword, :sdword, :sdword, :LPSIZE
SetBitmapDimensionEx proto WINAPI :HBITMAP, :sdword, :sdword, :LPSIZE
SetBrushOrgEx proto WINAPI :HDC, :sdword, :sdword, :LPPOINT

GetTextFaceA proto WINAPI :HDC, :sdword, :LPSTR
GetTextFaceW proto WINAPI :HDC, :sdword, :LPWSTR
ifdef _UNICODE
define GetTextFace  <GetTextFaceW>
else
define GetTextFace  <GetTextFaceA>
endif

define FONTMAPPER_MAX 10

tagKERNINGPAIR          struct
wFirst                  WORD ?
wSecond                 WORD ?
iKernAmount             sdword ?
tagKERNINGPAIR          ends
KERNINGPAIR             typedef tagKERNINGPAIR
LPKERNINGPAIR           typedef ptr tagKERNINGPAIR

GetKerningPairsA proto WINAPI :HDC, :DWORD, :LPKERNINGPAIR
GetKerningPairsW proto WINAPI :HDC, :DWORD, :LPKERNINGPAIR
ifdef _UNICODE
define GetKerningPairs  <GetKerningPairsW>
else
define GetKerningPairs  <GetKerningPairsA>
endif

GetDCOrgEx proto WINAPI :HDC, :LPPOINT
FixBrushOrgEx proto WINAPI :HDC, :sdword, :sdword, :LPPOINT
UnrealizeObject proto WINAPI :HGDIOBJ

GdiFlush proto WINAPI
GdiSetBatchLimit proto WINAPI :DWORD
GdiGetBatchLimit proto WINAPI

if(WINVER ge 0x0400)

define ICM_OFF               1
define ICM_ON                2
define ICM_QUERY             3
define ICM_DONE_OUTSIDEDC    4

CALLBACK(ICMENUMPROCA, :LPSTR, :LPARAM)
CALLBACK(ICMENUMPROCW, :LPWSTR, :LPARAM)
ifdef _UNICODE
define ICMENUMPROC  <ICMENUMPROCW>
else
define ICMENUMPROC  <ICMENUMPROCA>
endif

SetICMMode proto WINAPI :HDC, :sdword
CheckColorsInGamut proto WINAPI :HDC, :LPRGBTRIPLE, :LPVOID, :DWORD

GetColorSpace proto WINAPI :HDC
GetLogColorSpaceA proto WINAPI :HCOLORSPACE, :LPLOGCOLORSPACEA, :DWORD
GetLogColorSpaceW proto WINAPI :HCOLORSPACE, :LPLOGCOLORSPACEW, :DWORD
ifdef _UNICODE
define GetLogColorSpace  <GetLogColorSpaceW>
else
define GetLogColorSpace  <GetLogColorSpaceA>
endif

CreateColorSpaceA proto WINAPI :LPLOGCOLORSPACEA
CreateColorSpaceW proto WINAPI :LPLOGCOLORSPACEW
ifdef _UNICODE
define CreateColorSpace  <CreateColorSpaceW>
else
define CreateColorSpace  <CreateColorSpaceA>
endif
SetColorSpace proto WINAPI :HDC, :HCOLORSPACE
DeleteColorSpace proto WINAPI :HCOLORSPACE
GetICMProfileA proto WINAPI :HDC, :LPDWORD, :LPSTR
GetICMProfileW proto WINAPI :HDC, :LPDWORD, :LPWSTR
ifdef _UNICODE
define GetICMProfile  <GetICMProfileW>
else
define GetICMProfile  <GetICMProfileA>
endif

SetICMProfileA proto WINAPI :HDC, :LPSTR
SetICMProfileW proto WINAPI :HDC, :LPWSTR
ifdef _UNICODE
define SetICMProfile  <SetICMProfileW>
else
define SetICMProfile  <SetICMProfileA>
endif
GetDeviceGammaRamp proto WINAPI :HDC, :LPVOID
SetDeviceGammaRamp proto WINAPI :HDC, :LPVOID
ColorMatchToTarget proto WINAPI :HDC, :HDC, :DWORD
EnumICMProfilesA proto WINAPI :HDC, :ICMENUMPROCA, :LPARAM
EnumICMProfilesW proto WINAPI :HDC, :ICMENUMPROCW, :LPARAM
ifdef _UNICODE
define EnumICMProfiles  <EnumICMProfilesW>
else
define EnumICMProfiles  <EnumICMProfilesA>
endif
UpdateICMRegKeyA proto WINAPI :DWORD, :LPSTR, :LPSTR, :UINT
UpdateICMRegKeyW proto WINAPI :DWORD, :LPWSTR, :LPWSTR, :UINT
ifdef _UNICODE
define UpdateICMRegKey  <UpdateICMRegKeyW>
else
define UpdateICMRegKey  <UpdateICMRegKeyA>
endif
;.pragma deprecated (UpdateICMRegKeyW)
;.pragma deprecated (UpdateICMRegKeyA)

endif

if (WINVER ge 0x0500)
ColorCorrectPalette proto WINAPI :HDC, :HPALETTE, :DWORD, :DWORD
endif

ifndef NOMETAFILE

ifndef _MAC
define ENHMETA_SIGNATURE       0x464D4520
else
define ENHMETA_SIGNATURE       0x20454D46
endif

define ENHMETA_STOCK_OBJECT    0x80000000

define EMR_HEADER                      1
define EMR_POLYBEZIER                  2
define EMR_POLYGON                     3
define EMR_POLYLINE                    4
define EMR_POLYBEZIERTO                5
define EMR_POLYLINETO                  6
define EMR_POLYPOLYLINE                7
define EMR_POLYPOLYGON                 8
define EMR_SETWINDOWEXTEX              9
define EMR_SETWINDOWORGEX              10
define EMR_SETVIEWPORTEXTEX            11
define EMR_SETVIEWPORTORGEX            12
define EMR_SETBRUSHORGEX               13
define EMR_EOF                         14
define EMR_SETPIXELV                   15
define EMR_SETMAPPERFLAGS              16
define EMR_SETMAPMODE                  17
define EMR_SETBKMODE                   18
define EMR_SETPOLYFILLMODE             19
define EMR_SETROP2                     20
define EMR_SETSTRETCHBLTMODE           21
define EMR_SETTEXTALIGN                22
define EMR_SETCOLORADJUSTMENT          23
define EMR_SETTEXTCOLOR                24
define EMR_SETBKCOLOR                  25
define EMR_OFFSETCLIPRGN               26
define EMR_MOVETOEX                    27
define EMR_SETMETARGN                  28
define EMR_EXCLUDECLIPRECT             29
define EMR_INTERSECTCLIPRECT           30
define EMR_SCALEVIEWPORTEXTEX          31
define EMR_SCALEWINDOWEXTEX            32
define EMR_SAVEDC                      33
define EMR_RESTOREDC                   34
define EMR_SETWORLDTRANSFORM           35
define EMR_MODIFYWORLDTRANSFORM        36
define EMR_SELECTOBJECT                37
define EMR_CREATEPEN                   38
define EMR_CREATEBRUSHINDIRECT         39
define EMR_DELETEOBJECT                40
define EMR_ANGLEARC                    41
define EMR_ELLIPSE                     42
define EMR_RECTANGLE                   43
define EMR_ROUNDRECT                   44
define EMR_ARC                         45
define EMR_CHORD                       46
define EMR_PIE                         47
define EMR_SELECTPALETTE               48
define EMR_CREATEPALETTE               49
define EMR_SETPALETTEENTRIES           50
define EMR_RESIZEPALETTE               51
define EMR_REALIZEPALETTE              52
define EMR_EXTFLOODFILL                53
define EMR_LINETO                      54
define EMR_ARCTO                       55
define EMR_POLYDRAW                    56
define EMR_SETARCDIRECTION             57
define EMR_SETMITERLIMIT               58
define EMR_BEGINPATH                   59
define EMR_ENDPATH                     60
define EMR_CLOSEFIGURE                 61
define EMR_FILLPATH                    62
define EMR_STROKEANDFILLPATH           63
define EMR_STROKEPATH                  64
define EMR_FLATTENPATH                 65
define EMR_WIDENPATH                   66
define EMR_SELECTCLIPPATH              67
define EMR_ABORTPATH                   68

define EMR_GDICOMMENT                  70
define EMR_FILLRGN                     71
define EMR_FRAMERGN                    72
define EMR_INVERTRGN                   73
define EMR_PAINTRGN                    74
define EMR_EXTSELECTCLIPRGN            75
define EMR_BITBLT                      76
define EMR_STRETCHBLT                  77
define EMR_MASKBLT                     78
define EMR_PLGBLT                      79
define EMR_SETDIBITSTODEVICE           80
define EMR_STRETCHDIBITS               81
define EMR_EXTCREATEFONTINDIRECTW      82
define EMR_EXTTEXTOUTA                 83
define EMR_EXTTEXTOUTW                 84
define EMR_POLYBEZIER16                85
define EMR_POLYGON16                   86
define EMR_POLYLINE16                  87
define EMR_POLYBEZIERTO16              88
define EMR_POLYLINETO16                89
define EMR_POLYPOLYLINE16              90
define EMR_POLYPOLYGON16               91
define EMR_POLYDRAW16                  92
define EMR_CREATEMONOBRUSH             93
define EMR_CREATEDIBPATTERNBRUSHPT     94
define EMR_EXTCREATEPEN                95
define EMR_POLYTEXTOUTA                96
define EMR_POLYTEXTOUTW                97

if(WINVER ge 0x0400)
define EMR_SETICMMODE                  98
define EMR_CREATECOLORSPACE            99
define EMR_SETCOLORSPACE              100
define EMR_DELETECOLORSPACE           101
define EMR_GLSRECORD                  102
define EMR_GLSBOUNDEDRECORD           103
define EMR_PIXELFORMAT                104
endif

if(WINVER ge 0x0500)
define EMR_RESERVED_105               105
define EMR_RESERVED_106               106
define EMR_RESERVED_107               107
define EMR_RESERVED_108               108
define EMR_RESERVED_109               109
define EMR_RESERVED_110               110
define EMR_COLORCORRECTPALETTE        111
define EMR_SETICMPROFILEA             112
define EMR_SETICMPROFILEW             113
define EMR_ALPHABLEND                 114
define EMR_SETLAYOUT                  115
define EMR_TRANSPARENTBLT             116
if (_WIN32_WINNT ge _WIN32_WINNT_WIN2K)
define EMR_RESERVED_117               117
endif
define EMR_GRADIENTFILL               118
define EMR_RESERVED_119               119
define EMR_RESERVED_120               120
define EMR_COLORMATCHTOTARGETW        121
define EMR_CREATECOLORSPACEW          122
endif

define EMR_MIN                          1

if (WINVER ge 0x0500)
define EMR_MAX                        122
elseif (WINVER ge 0x0400)
define EMR_MAX                        104
else
define EMR_MAX                         97
endif

tagEMR                  struct
iType                   DWORD ?
nSize                   DWORD ?
tagEMR                  ends
EMR                     typedef tagEMR
PEMR                    typedef ptr tagEMR

tagEMRTEXT              struct
ptlReference            POINTL <>
nChars                  DWORD ?
offString               DWORD ?
fOptions                DWORD ?
_rcl                    RECTL <>
offDx                   DWORD ?
tagEMRTEXT              ends
EMRTEXT                 typedef tagEMRTEXT
PEMRTEXT                typedef ptr tagEMRTEXT

tagABORTPATH            struct
emr                     EMR <>
tagABORTPATH            ends
EMRABORTPATH            typedef tagABORTPATH
PEMRABORTPATH           typedef ptr tagABORTPATH
EMRBEGINPATH            typedef tagABORTPATH
PEMRBEGINPATH           typedef ptr tagABORTPATH
EMRENDPATH              typedef tagABORTPATH
PEMRENDPATH             typedef ptr tagABORTPATH
EMRCLOSEFIGURE          typedef tagABORTPATH
PEMRCLOSEFIGURE         typedef ptr tagABORTPATH
EMRFLATTENPATH          typedef tagABORTPATH
PEMRFLATTENPATH         typedef ptr tagABORTPATH
EMRWIDENPATH            typedef tagABORTPATH
PEMRWIDENPATH           typedef ptr tagABORTPATH
EMRSETMETARGN           typedef tagABORTPATH
PEMRSETMETARGN          typedef ptr tagABORTPATH
EMRSAVEDC               typedef tagABORTPATH
PEMRSAVEDC              typedef ptr tagABORTPATH
EMRREALIZEPALETTE       typedef tagABORTPATH
PEMRREALIZEPALETTE      typedef ptr tagABORTPATH

tagEMRSELECTCLIPPATH    struct
emr                     EMR <>
iMode                   DWORD ?
tagEMRSELECTCLIPPATH    ends
EMRSELECTCLIPPATH       typedef tagEMRSELECTCLIPPATH
PEMRSELECTCLIPPATH      typedef ptr tagEMRSELECTCLIPPATH
EMRSETBKMODE            typedef tagEMRSELECTCLIPPATH
PEMRSETBKMODE           typedef ptr tagEMRSELECTCLIPPATH
EMRSETMAPMODE           typedef tagEMRSELECTCLIPPATH
PEMRSETMAPMODE          typedef ptr tagEMRSELECTCLIPPATH
if(WINVER ge 0x0500)
EMRSETLAYOUT            typedef tagEMRSELECTCLIPPATH
PEMRSETLAYOUT           typedef ptr tagEMRSELECTCLIPPATH
endif
EMRSETPOLYFILLMODE      typedef tagEMRSELECTCLIPPATH
PEMRSETPOLYFILLMODE     typedef ptr tagEMRSELECTCLIPPATH
EMRSETROP2              typedef tagEMRSELECTCLIPPATH
PEMRSETROP2             typedef ptr tagEMRSELECTCLIPPATH
EMRSETSTRETCHBLTMODE    typedef tagEMRSELECTCLIPPATH
PEMRSETSTRETCHBLTMODE   typedef ptr tagEMRSELECTCLIPPATH
EMRSETICMMODE           typedef tagEMRSELECTCLIPPATH
PEMRSETICMMODE          typedef ptr tagEMRSELECTCLIPPATH
EMRSETTEXTALIGN         typedef tagEMRSELECTCLIPPATH
PEMRSETTEXTALIGN        typedef ptr tagEMRSELECTCLIPPATH

tagEMRSETMITERLIMIT     struct
emr                     EMR <>
eMiterLimit             FLOAT ?
tagEMRSETMITERLIMIT     ends
EMRSETMITERLIMIT        typedef tagEMRSETMITERLIMIT
PEMRSETMITERLIMIT       typedef ptr tagEMRSETMITERLIMIT

tagEMRRESTOREDC         struct
emr                     EMR <>
iRelative               LONG ?
tagEMRRESTOREDC         ends
EMRRESTOREDC            typedef tagEMRRESTOREDC
PEMRRESTOREDC           typedef ptr tagEMRRESTOREDC

tagEMRSETARCDIRECTION   struct
emr                     EMR <>
iArcDirection           DWORD ?
tagEMRSETARCDIRECTION   ends
EMRSETARCDIRECTION      typedef tagEMRSETARCDIRECTION
PEMRSETARCDIRECTION     typedef ptr tagEMRSETARCDIRECTION

tagEMRSETMAPPERFLAGS    struct
emr                     EMR <>
dwFlags                 DWORD ?
tagEMRSETMAPPERFLAGS    ends
EMRSETMAPPERFLAGS       typedef tagEMRSETMAPPERFLAGS
PEMRSETMAPPERFLAGS      typedef ptr tagEMRSETMAPPERFLAGS

tagEMRSETTEXTCOLOR      struct
emr                     EMR <>
crColor                 COLORREF ?
tagEMRSETTEXTCOLOR      ends
EMRSETBKCOLOR           typedef tagEMRSETTEXTCOLOR
PEMRSETBKCOLOR          typedef ptr tagEMRSETTEXTCOLOR
EMRSETTEXTCOLOR         typedef tagEMRSETTEXTCOLOR
PEMRSETTEXTCOLOR        typedef ptr tagEMRSETTEXTCOLOR

tagEMRSELECTOBJECT      struct
emr                     EMR <>
ihObject                DWORD ?
tagEMRSELECTOBJECT      ends
EMRSELECTOBJECT         typedef tagEMRSELECTOBJECT
PEMRSELECTOBJECT        typedef ptr tagEMRSELECTOBJECT
EMRDELETEOBJECT         typedef tagEMRSELECTOBJECT
PEMRDELETEOBJECT        typedef ptr tagEMRSELECTOBJECT

tagEMRSELECTPALETTE     struct
emr                     EMR <>
ihPal                   DWORD ?
tagEMRSELECTPALETTE     ends
EMRSELECTPALETTE        typedef tagEMRSELECTPALETTE
PEMRSELECTPALETTE       typedef ptr tagEMRSELECTPALETTE

tagEMRRESIZEPALETTE     struct
emr                     EMR <>
ihPal                   DWORD ?
cEntries                DWORD ?
tagEMRRESIZEPALETTE     ends
EMRRESIZEPALETTE        typedef tagEMRRESIZEPALETTE
PEMRRESIZEPALETTE       typedef ptr tagEMRRESIZEPALETTE

tagEMRSETPALETTEENTRIES struct
emr                     EMR <>
ihPal                   DWORD ?
iStart                  DWORD ?
cEntries                DWORD ?
aPalEntries             PALETTEENTRY 1 dup(<>)
tagEMRSETPALETTEENTRIES ends
EMRSETPALETTEENTRIES    typedef tagEMRSETPALETTEENTRIES
PEMRSETPALETTEENTRIES   typedef ptr tagEMRSETPALETTEENTRIES

tagEMRSETCOLORADJUSTMENT struct
emr                     EMR <>
ColorAdjustment         COLORADJUSTMENT <>
tagEMRSETCOLORADJUSTMENT ends
EMRSETCOLORADJUSTMENT   typedef tagEMRSETCOLORADJUSTMENT
PEMRSETCOLORADJUSTMENT  typedef ptr tagEMRSETCOLORADJUSTMENT

tagEMRGDICOMMENT        struct
emr                     EMR <>
cbData                  DWORD ?
Data                    BYTE 1 dup(?)
tagEMRGDICOMMENT        ends
EMRGDICOMMENT           typedef tagEMRGDICOMMENT
PEMRGDICOMMENT          typedef ptr tagEMRGDICOMMENT

tagEMREOF               struct
emr                     EMR <>
nPalEntries             DWORD ?
offPalEntries           DWORD ?
nSizeLast               DWORD ?
tagEMREOF               ends
EMREOF                  typedef tagEMREOF
PEMREOF                 typedef ptr tagEMREOF

tagEMRLINETO            struct
emr                     EMR <>
ptl                     POINTL <>
tagEMRLINETO            ends
EMRLINETO               typedef tagEMRLINETO
PEMRLINETO              typedef ptr tagEMRLINETO
EMRMOVETOEX             typedef tagEMRLINETO
PEMRMOVETOEX            typedef ptr tagEMRLINETO

tagEMROFFSETCLIPRGN     struct
emr                     EMR <>
ptlOffset               POINTL <>
tagEMROFFSETCLIPRGN     ends
EMROFFSETCLIPRGN        typedef tagEMROFFSETCLIPRGN
PEMROFFSETCLIPRGN       typedef ptr tagEMROFFSETCLIPRGN

tagEMRFILLPATH          struct
emr                     EMR <>
rclBounds               RECTL <>
tagEMRFILLPATH          ends
EMRFILLPATH             typedef tagEMRFILLPATH
PEMRFILLPATH            typedef ptr tagEMRFILLPATH
EMRSTROKEANDFILLPATH    typedef tagEMRFILLPATH
PEMRSTROKEANDFILLPATH   typedef ptr tagEMRFILLPATH
EMRSTROKEPATH           typedef tagEMRFILLPATH
PEMRSTROKEPATH          typedef ptr tagEMRFILLPATH

tagEMREXCLUDECLIPRECT   struct
emr                     EMR <>
rclClip                 RECTL <>
tagEMREXCLUDECLIPRECT   ends
EMREXCLUDECLIPRECT      typedef tagEMREXCLUDECLIPRECT
PEMREXCLUDECLIPRECT     typedef ptr tagEMREXCLUDECLIPRECT
EMRINTERSECTCLIPRECT    typedef tagEMREXCLUDECLIPRECT
PEMRINTERSECTCLIPRECT   typedef ptr tagEMREXCLUDECLIPRECT

tagEMRSETVIEWPORTORGEX  struct
emr                     EMR <>
ptlOrigin               POINTL <>
tagEMRSETVIEWPORTORGEX  ends
EMRSETVIEWPORTORGEX     typedef tagEMRSETVIEWPORTORGEX
PEMRSETVIEWPORTORGEX    typedef ptr tagEMRSETVIEWPORTORGEX
EMRSETWINDOWORGEX       typedef tagEMRSETVIEWPORTORGEX
PEMRSETWINDOWORGEX      typedef ptr tagEMRSETVIEWPORTORGEX
EMRSETBRUSHORGEX        typedef tagEMRSETVIEWPORTORGEX
PEMRSETBRUSHORGEX       typedef ptr tagEMRSETVIEWPORTORGEX

tagEMRSETVIEWPORTEXTEX  struct
emr                     EMR <>
szlExtent               SIZEL <>
tagEMRSETVIEWPORTEXTEX  ends
EMRSETVIEWPORTEXTEX     typedef tagEMRSETVIEWPORTEXTEX
PEMRSETVIEWPORTEXTEX    typedef ptr tagEMRSETVIEWPORTEXTEX
EMRSETWINDOWEXTEX       typedef tagEMRSETVIEWPORTEXTEX
PEMRSETWINDOWEXTEX      typedef ptr tagEMRSETVIEWPORTEXTEX

tagEMRSCALEVIEWPORTEXTEX struct
emr                     EMR <>
xNum                    LONG ?
xDenom                  LONG ?
yNum                    LONG ?
yDenom                  LONG ?
tagEMRSCALEVIEWPORTEXTEX ends
EMRSCALEVIEWPORTEXTEX   typedef tagEMRSCALEVIEWPORTEXTEX
PEMRSCALEVIEWPORTEXTEX  typedef ptr tagEMRSCALEVIEWPORTEXTEX
EMRSCALEWINDOWEXTEX     typedef tagEMRSCALEVIEWPORTEXTEX
PEMRSCALEWINDOWEXTEX    typedef ptr tagEMRSCALEVIEWPORTEXTEX

tagEMRSETWORLDTRANSFORM struct
emr                     EMR <>
xform                   XFORM <>
tagEMRSETWORLDTRANSFORM ends
EMRSETWORLDTRANSFORM    typedef tagEMRSETWORLDTRANSFORM
PEMRSETWORLDTRANSFORM   typedef ptr tagEMRSETWORLDTRANSFORM

tagEMRMODIFYWORLDTRANSFORM struct
emr                     EMR <>
xform                   XFORM <>
iMode                   DWORD ?
tagEMRMODIFYWORLDTRANSFORM ends
EMRMODIFYWORLDTRANSFORM typedef tagEMRMODIFYWORLDTRANSFORM
PEMRMODIFYWORLDTRANSFORM typedef ptr tagEMRMODIFYWORLDTRANSFORM

tagEMRSETPIXELV         struct
emr                     EMR <>
ptlPixel                POINTL <>
crColor                 COLORREF ?
tagEMRSETPIXELV         ends
EMRSETPIXELV            typedef tagEMRSETPIXELV
PEMRSETPIXELV           typedef ptr tagEMRSETPIXELV

tagEMREXTFLOODFILL      struct
emr                     EMR <>
ptlStart                POINTL <>
crColor                 COLORREF ?
iMode                   DWORD ?
tagEMREXTFLOODFILL      ends
EMREXTFLOODFILL         typedef tagEMREXTFLOODFILL
PEMREXTFLOODFILL        typedef ptr tagEMREXTFLOODFILL

tagEMRELLIPSE           struct
emr                     EMR <>
rclBox                  RECTL <>
tagEMRELLIPSE           ends
EMRELLIPSE              typedef tagEMRELLIPSE
PEMRELLIPSE             typedef ptr tagEMRELLIPSE
EMRRECTANGLE            typedef tagEMRELLIPSE
PEMRRECTANGLE           typedef ptr tagEMRELLIPSE

tagEMRROUNDRECT         struct
emr                     EMR <>
rclBox                  RECTL <>
szlCorner               SIZEL <>
tagEMRROUNDRECT         ends
EMRROUNDRECT            typedef tagEMRROUNDRECT
PEMRROUNDRECT           typedef ptr tagEMRROUNDRECT

tagEMRARC               struct
emr                     EMR <>
rclBox                  RECTL <>
ptlStart                POINTL <>
ptlEnd                  POINTL <>
tagEMRARC               ends
EMRARC                  typedef tagEMRARC
PEMRARC                 typedef ptr tagEMRARC
EMRARCTO                typedef tagEMRARC
PEMRARCTO               typedef ptr tagEMRARC
EMRCHORD                typedef tagEMRARC
PEMRCHORD               typedef ptr tagEMRARC
EMRPIE                  typedef tagEMRARC
PEMRPIE                 typedef ptr tagEMRARC

tagEMRANGLEARC          struct
emr                     EMR <>
ptlCenter               POINTL <>
nRadius                 DWORD ?
eStartAngle             FLOAT ?
eSweepAngle             FLOAT ?
tagEMRANGLEARC          ends
EMRANGLEARC             typedef tagEMRANGLEARC
PEMRANGLEARC            typedef ptr tagEMRANGLEARC

tagEMRPOLYLINE          struct
emr                     EMR <>
rclBounds               RECTL <>
cptl                    DWORD ?
aptl                    POINTL 1 dup(<>)
tagEMRPOLYLINE          ends
EMRPOLYLINE             typedef tagEMRPOLYLINE
PEMRPOLYLINE            typedef ptr tagEMRPOLYLINE
EMRPOLYBEZIER           typedef tagEMRPOLYLINE
PEMRPOLYBEZIER          typedef ptr tagEMRPOLYLINE
EMRPOLYGON              typedef tagEMRPOLYLINE
PEMRPOLYGON             typedef ptr tagEMRPOLYLINE
EMRPOLYBEZIERTO         typedef tagEMRPOLYLINE
PEMRPOLYBEZIERTO        typedef ptr tagEMRPOLYLINE
EMRPOLYLINETO           typedef tagEMRPOLYLINE
PEMRPOLYLINETO          typedef ptr tagEMRPOLYLINE

tagEMRPOLYLINE16        struct
emr                     EMR <>
rclBounds               RECTL <>
cpts                    DWORD ?
apts                    POINTS 1 dup(<>)
tagEMRPOLYLINE16        ends
EMRPOLYLINE16           typedef tagEMRPOLYLINE16
PEMRPOLYLINE16          typedef ptr tagEMRPOLYLINE16
EMRPOLYBEZIER16         typedef tagEMRPOLYLINE16
PEMRPOLYBEZIER16        typedef ptr tagEMRPOLYLINE16
EMRPOLYGON16            typedef tagEMRPOLYLINE16
PEMRPOLYGON16           typedef ptr tagEMRPOLYLINE16
EMRPOLYBEZIERTO16       typedef tagEMRPOLYLINE16
PEMRPOLYBEZIERTO16      typedef ptr tagEMRPOLYLINE16
EMRPOLYLINETO16         typedef tagEMRPOLYLINE16
PEMRPOLYLINETO16        typedef ptr tagEMRPOLYLINE16

tagEMRPOLYDRAW          struct
emr                     EMR <>
rclBounds               RECTL <>
cptl                    DWORD ?
aptl                    POINTL 1 dup(<>)
abTypes                 BYTE 1 dup(?)
tagEMRPOLYDRAW          ends
EMRPOLYDRAW             typedef tagEMRPOLYDRAW
PEMRPOLYDRAW            typedef ptr tagEMRPOLYDRAW

tagEMRPOLYDRAW16        struct
emr                     EMR <>
rclBounds               RECTL <>
cpts                    DWORD ?
apts                    POINTS 1 dup(<>)
abTypes                 BYTE 1 dup(?)
tagEMRPOLYDRAW16        ends
EMRPOLYDRAW16           typedef tagEMRPOLYDRAW16
PEMRPOLYDRAW16          typedef ptr tagEMRPOLYDRAW16

tagEMRPOLYPOLYLINE      struct
emr                     EMR <>
rclBounds               RECTL <>
nPolys                  DWORD ?
cptl                    DWORD ?
aPolyCounts             DWORD 1 dup(?)
aptl                    POINTL 1 dup(<>)
tagEMRPOLYPOLYLINE      ends
EMRPOLYPOLYLINE         typedef tagEMRPOLYPOLYLINE
PEMRPOLYPOLYLINE        typedef ptr tagEMRPOLYPOLYLINE
EMRPOLYPOLYGON          typedef tagEMRPOLYPOLYLINE
PEMRPOLYPOLYGON         typedef ptr tagEMRPOLYPOLYLINE

tagEMRPOLYPOLYLINE16    struct
emr                     EMR <>
rclBounds               RECTL <>
nPolys                  DWORD ?
cpts                    DWORD ?
aPolyCounts             DWORD 1 dup(?)
apts                    POINTS 1 dup(<>)
tagEMRPOLYPOLYLINE16    ends
EMRPOLYPOLYLINE16       typedef tagEMRPOLYPOLYLINE16
PEMRPOLYPOLYLINE16      typedef ptr tagEMRPOLYPOLYLINE16
EMRPOLYPOLYGON16        typedef tagEMRPOLYPOLYLINE16
PEMRPOLYPOLYGON16       typedef ptr tagEMRPOLYPOLYLINE16

tagEMRINVERTRGN         struct
emr                     EMR <>
rclBounds               RECTL <>
cbRgnData               DWORD ?
RgnData                 BYTE 1 dup(?)
tagEMRINVERTRGN         ends
EMRINVERTRGN            typedef tagEMRINVERTRGN
PEMRINVERTRGN           typedef ptr tagEMRINVERTRGN
EMRPAINTRGN             typedef tagEMRINVERTRGN
PEMRPAINTRGN            typedef ptr tagEMRINVERTRGN

tagEMRFILLRGN           struct
emr                     EMR <>
rclBounds               RECTL <>
cbRgnData               DWORD ?
ihBrush                 DWORD ?
RgnData                 BYTE 1 dup(?)
tagEMRFILLRGN           ends
EMRFILLRGN              typedef tagEMRFILLRGN
PEMRFILLRGN             typedef ptr tagEMRFILLRGN

tagEMRFRAMERGN          struct
emr                     EMR <>
rclBounds               RECTL <>
cbRgnData               DWORD ?
ihBrush                 DWORD ?
szlStroke               SIZEL <>
RgnData                 BYTE 1 dup(?)
tagEMRFRAMERGN          ends
EMRFRAMERGN             typedef tagEMRFRAMERGN
PEMRFRAMERGN            typedef ptr tagEMRFRAMERGN

tagEMREXTSELECTCLIPRGN  struct
emr                     EMR <>
cbRgnData               DWORD ?
iMode                   DWORD ?
RgnData                 BYTE 1 dup(?)
tagEMREXTSELECTCLIPRGN  ends
EMREXTSELECTCLIPRGN     typedef tagEMREXTSELECTCLIPRGN
PEMREXTSELECTCLIPRGN    typedef ptr tagEMREXTSELECTCLIPRGN

tagEMREXTTEXTOUTA       struct
emr                     EMR <>
rclBounds               RECTL <>
iGraphicsMode           DWORD ?
exScale                 FLOAT ?
eyScale                 FLOAT ?
emrtext                 EMRTEXT <>
tagEMREXTTEXTOUTA       ends
EMREXTTEXTOUTA          typedef tagEMREXTTEXTOUTA
PEMREXTTEXTOUTA         typedef ptr tagEMREXTTEXTOUTA
EMREXTTEXTOUTW          typedef tagEMREXTTEXTOUTA
PEMREXTTEXTOUTW         typedef ptr tagEMREXTTEXTOUTA

tagEMRPOLYTEXTOUTA      struct
emr                     EMR <>
rclBounds               RECTL <>
iGraphicsMode           DWORD ?
exScale                 FLOAT ?
eyScale                 FLOAT ?
cStrings                LONG ?
aemrtext                EMRTEXT 1 dup(<>)
tagEMRPOLYTEXTOUTA      ends
EMRPOLYTEXTOUTA         typedef tagEMRPOLYTEXTOUTA
PEMRPOLYTEXTOUTA        typedef ptr tagEMRPOLYTEXTOUTA
EMRPOLYTEXTOUTW         typedef tagEMRPOLYTEXTOUTA
PEMRPOLYTEXTOUTW        typedef ptr tagEMRPOLYTEXTOUTA

tagEMRBITBLT            struct
emr                     EMR <>
rclBounds               RECTL <>
xDest                   LONG ?
yDest                   LONG ?
cxDest                  LONG ?
cyDest                  LONG ?
dwRop                   DWORD ?
xSrc                    LONG ?
ySrc                    LONG ?
xformSrc                XFORM <>
crBkColorSrc            COLORREF ?
iUsageSrc               DWORD ?
offBmiSrc               DWORD ?
cbBmiSrc                DWORD ?
offBitsSrc              DWORD ?
cbBitsSrc               DWORD ?
tagEMRBITBLT            ends
EMRBITBLT               typedef tagEMRBITBLT
PEMRBITBLT              typedef ptr tagEMRBITBLT

tagEMRSTRETCHBLT        struct
emr                     EMR <>
rclBounds               RECTL <>
xDest                   LONG ?
yDest                   LONG ?
cxDest                  LONG ?
cyDest                  LONG ?
dwRop                   DWORD ?
xSrc                    LONG ?
ySrc                    LONG ?
xformSrc                XFORM <>
crBkColorSrc            COLORREF ?
iUsageSrc               DWORD ?
offBmiSrc               DWORD ?
cbBmiSrc                DWORD ?
offBitsSrc              DWORD ?
cbBitsSrc               DWORD ?
cxSrc                   LONG ?
cySrc                   LONG ?
tagEMRSTRETCHBLT        ends
EMRSTRETCHBLT           typedef tagEMRSTRETCHBLT
PEMRSTRETCHBLT          typedef ptr tagEMRSTRETCHBLT

tagEMRMASKBLT           struct
emr                     EMR <>
rclBounds               RECTL <>
xDest                   LONG ?
yDest                   LONG ?
cxDest                  LONG ?
cyDest                  LONG ?
dwRop                   DWORD ?
xSrc                    LONG ?
ySrc                    LONG ?
xformSrc                XFORM <>
crBkColorSrc            COLORREF ?
iUsageSrc               DWORD ?
offBmiSrc               DWORD ?
cbBmiSrc                DWORD ?
offBitsSrc              DWORD ?
cbBitsSrc               DWORD ?
xMask                   LONG ?
yMask                   LONG ?
iUsageMask              DWORD ?
offBmiMask              DWORD ?
cbBmiMask               DWORD ?
offBitsMask             DWORD ?
cbBitsMask              DWORD ?
tagEMRMASKBLT           ends
EMRMASKBLT              typedef tagEMRMASKBLT
PEMRMASKBLT             typedef ptr tagEMRMASKBLT

tagEMRPLGBLT            struct
emr                     EMR <>
rclBounds               RECTL <>
aptlDest                POINTL 3 dup(<>)
xSrc                    LONG ?
ySrc                    LONG ?
cxSrc                   LONG ?
cySrc                   LONG ?
xformSrc                XFORM <>
crBkColorSrc            COLORREF ?
iUsageSrc               DWORD ?
offBmiSrc               DWORD ?
cbBmiSrc                DWORD ?
offBitsSrc              DWORD ?
cbBitsSrc               DWORD ?
xMask                   LONG ?
yMask                   LONG ?
iUsageMask              DWORD ?
offBmiMask              DWORD ?
cbBmiMask               DWORD ?
offBitsMask             DWORD ?
cbBitsMask              DWORD ?
tagEMRPLGBLT            ends
EMRPLGBLT               typedef tagEMRPLGBLT
PEMRPLGBLT              typedef ptr tagEMRPLGBLT

tagEMRSETDIBITSTODEVICE struct
emr                     EMR <>
rclBounds               RECTL <>
xDest                   LONG ?
yDest                   LONG ?
xSrc                    LONG ?
ySrc                    LONG ?
cxSrc                   LONG ?
cySrc                   LONG ?
offBmiSrc               DWORD ?
cbBmiSrc                DWORD ?
offBitsSrc              DWORD ?
cbBitsSrc               DWORD ?
iUsageSrc               DWORD ?
iStartScan              DWORD ?
cScans                  DWORD ?
tagEMRSETDIBITSTODEVICE ends
EMRSETDIBITSTODEVICE    typedef tagEMRSETDIBITSTODEVICE
PEMRSETDIBITSTODEVICE   typedef ptr tagEMRSETDIBITSTODEVICE

tagEMRSTRETCHDIBITS     struct
emr                     EMR <>
rclBounds               RECTL <>
xDest                   LONG ?
yDest                   LONG ?
xSrc                    LONG ?
ySrc                    LONG ?
cxSrc                   LONG ?
cySrc                   LONG ?
offBmiSrc               DWORD ?
cbBmiSrc                DWORD ?
offBitsSrc              DWORD ?
cbBitsSrc               DWORD ?
iUsageSrc               DWORD ?
dwRop                   DWORD ?
cxDest                  LONG ?
cyDest                  LONG ?
tagEMRSTRETCHDIBITS     ends
EMRSTRETCHDIBITS        typedef tagEMRSTRETCHDIBITS
PEMRSTRETCHDIBITS       typedef ptr tagEMRSTRETCHDIBITS

tagEMREXTCREATEFONTINDIRECTW struct
emr                     EMR <>
ihFont                  DWORD ?
elfw                    EXTLOGFONTW <>
tagEMREXTCREATEFONTINDIRECTW ends
EMREXTCREATEFONTINDIRECTW typedef tagEMREXTCREATEFONTINDIRECTW
PEMREXTCREATEFONTINDIRECTW typedef ptr tagEMREXTCREATEFONTINDIRECTW

tagEMRCREATEPALETTE     struct
emr                     EMR <>
ihPal                   DWORD ?
lgpl                    LOGPALETTE <>
tagEMRCREATEPALETTE     ends
EMRCREATEPALETTE        typedef tagEMRCREATEPALETTE
PEMRCREATEPALETTE       typedef ptr tagEMRCREATEPALETTE

tagEMRCREATEPEN         struct
emr                     EMR <>
ihPen                   DWORD ?
lopn                    LOGPEN <>
tagEMRCREATEPEN         ends
EMRCREATEPEN            typedef tagEMRCREATEPEN
PEMRCREATEPEN           typedef ptr tagEMRCREATEPEN

tagEMREXTCREATEPEN      struct
emr                     EMR <>
ihPen                   DWORD ?
offBmi                  DWORD ?
cbBmi                   DWORD ?
offBits                 DWORD ?
cbBits                  DWORD ?
elp                     EXTLOGPEN32 <>
tagEMREXTCREATEPEN      ends
EMREXTCREATEPEN         typedef tagEMREXTCREATEPEN
PEMREXTCREATEPEN        typedef ptr tagEMREXTCREATEPEN

tagEMRCREATEBRUSHINDIRECT struct
emr                     EMR <>
ihBrush                 DWORD ?
lb                      LOGBRUSH32 <>
tagEMRCREATEBRUSHINDIRECT ends
EMRCREATEBRUSHINDIRECT  typedef tagEMRCREATEBRUSHINDIRECT
PEMRCREATEBRUSHINDIRECT typedef ptr tagEMRCREATEBRUSHINDIRECT

tagEMRCREATEMONOBRUSH   struct
emr                     EMR <>
ihBrush                 DWORD ?
iUsage                  DWORD ?
offBmi                  DWORD ?
cbBmi                   DWORD ?
offBits                 DWORD ?
cbBits                  DWORD ?
tagEMRCREATEMONOBRUSH   ends
EMRCREATEMONOBRUSH      typedef tagEMRCREATEMONOBRUSH
PEMRCREATEMONOBRUSH     typedef ptr tagEMRCREATEMONOBRUSH

tagEMRCREATEDIBPATTERNBRUSHPT struct
emr                     EMR <>
ihBrush                 DWORD ?
iUsage                  DWORD ?
offBmi                  DWORD ?
cbBmi                   DWORD ?
offBits                 DWORD ?
cbBits                  DWORD ?
tagEMRCREATEDIBPATTERNBRUSHPT ends
EMRCREATEDIBPATTERNBRUSHPT typedef tagEMRCREATEDIBPATTERNBRUSHPT
PEMRCREATEDIBPATTERNBRUSHPT typedef ptr tagEMRCREATEDIBPATTERNBRUSHPT

tagEMRFORMAT            struct
dSignature              DWORD ?
nVersion                DWORD ?
cbData                  DWORD ?
offData                 DWORD ?
tagEMRFORMAT            ends
EMRFORMAT               typedef tagEMRFORMAT
PEMRFORMAT              typedef ptr tagEMRFORMAT

if(WINVER ge 0x0400)

tagEMRGLSRECORD         struct
emr                     EMR <>
cbData                  DWORD ?
Data                    BYTE 1 dup(?)
tagEMRGLSRECORD         ends
EMRGLSRECORD            typedef tagEMRGLSRECORD
PEMRGLSRECORD           typedef ptr tagEMRGLSRECORD

tagEMRGLSBOUNDEDRECORD  struct
emr                     EMR <>
rclBounds               RECTL <>
cbData                  DWORD ?
Data                    BYTE 1 dup(?)
tagEMRGLSBOUNDEDRECORD  ends
EMRGLSBOUNDEDRECORD     typedef tagEMRGLSBOUNDEDRECORD
PEMRGLSBOUNDEDRECORD    typedef ptr tagEMRGLSBOUNDEDRECORD

tagEMRPIXELFORMAT       struct
emr                     EMR <>
pfd                     PIXELFORMATDESCRIPTOR <>
tagEMRPIXELFORMAT       ends
EMRPIXELFORMAT          typedef tagEMRPIXELFORMAT
PEMRPIXELFORMAT         typedef ptr tagEMRPIXELFORMAT

tagEMRCREATECOLORSPACE  struct
emr                     EMR <>
ihCS                    DWORD ?
lcs                     LOGCOLORSPACEA <>
tagEMRCREATECOLORSPACE  ends
EMRCREATECOLORSPACE     typedef tagEMRCREATECOLORSPACE
PEMRCREATECOLORSPACE    typedef ptr tagEMRCREATECOLORSPACE

tagEMRSETCOLORSPACE     struct
emr                     EMR <>
ihCS                    DWORD ?
tagEMRSETCOLORSPACE     ends
EMRSETCOLORSPACE        typedef tagEMRSETCOLORSPACE
PEMRSETCOLORSPACE       typedef ptr tagEMRSETCOLORSPACE
EMRSELECTCOLORSPACE     typedef tagEMRSETCOLORSPACE
PEMRSELECTCOLORSPACE    typedef ptr tagEMRSETCOLORSPACE
EMRDELETECOLORSPACE     typedef tagEMRSETCOLORSPACE
PEMRDELETECOLORSPACE    typedef ptr tagEMRSETCOLORSPACE

endif

if(WINVER ge 0x0500)

tagEMREXTESCAPE         struct
emr                     EMR <>
iEscape                 SINT ?
cbEscData               SINT ?
EscData                 BYTE 1 dup(?)
tagEMREXTESCAPE         ends
EMREXTESCAPE            typedef tagEMREXTESCAPE
PEMREXTESCAPE           typedef ptr tagEMREXTESCAPE
EMRDRAWESCAPE           typedef tagEMREXTESCAPE
PEMRDRAWESCAPE          typedef ptr tagEMREXTESCAPE

tagEMRNAMEDESCAPE       struct
emr                     EMR <>
iEscape                 SINT ?
cbDriver                SINT ?
cbEscData               SINT ?
EscData                 BYTE 1 dup(?)
tagEMRNAMEDESCAPE       ends
EMRNAMEDESCAPE          typedef tagEMRNAMEDESCAPE
PEMRNAMEDESCAPE         typedef ptr tagEMRNAMEDESCAPE

define SETICMPROFILE_EMBEDED           0x00000001

tagEMRSETICMPROFILE     struct
emr                     EMR <>
dwFlags                 DWORD ?
cbName                  DWORD ?
cbData                  DWORD ?
Data                    BYTE 1 dup(?)
tagEMRSETICMPROFILE     ends
EMRSETICMPROFILE        typedef tagEMRSETICMPROFILE
PEMRSETICMPROFILE       typedef ptr tagEMRSETICMPROFILE
EMRSETICMPROFILEA       typedef tagEMRSETICMPROFILE
PEMRSETICMPROFILEA      typedef ptr tagEMRSETICMPROFILE
EMRSETICMPROFILEW       typedef tagEMRSETICMPROFILE
PEMRSETICMPROFILEW      typedef ptr tagEMRSETICMPROFILE

define CREATECOLORSPACE_EMBEDED        0x00000001

tagEMRCREATECOLORSPACEW struct
emr                     EMR <>
ihCS                    DWORD ?
lcs                     LOGCOLORSPACEW <>
dwFlags                 DWORD ?
cbData                  DWORD ?
Data                    BYTE 1 dup(?)
tagEMRCREATECOLORSPACEW ends
EMRCREATECOLORSPACEW    typedef tagEMRCREATECOLORSPACEW
PEMRCREATECOLORSPACEW   typedef ptr tagEMRCREATECOLORSPACEW

define COLORMATCHTOTARGET_EMBEDED      0x00000001

tagCOLORMATCHTOTARGET   struct
emr                     EMR <>
dwAction                DWORD ?
dwFlags                 DWORD ?
cbName                  DWORD ?
cbData                  DWORD ?
Data                    BYTE 1 dup(?)
tagCOLORMATCHTOTARGET   ends
EMRCOLORMATCHTOTARGET   typedef tagCOLORMATCHTOTARGET
PEMRCOLORMATCHTOTARGET  typedef ptr tagCOLORMATCHTOTARGET

tagCOLORCORRECTPALETTE  struct
emr                     EMR <>
ihPalette               DWORD ?
nFirstEntry             DWORD ?
nPalEntries             DWORD ?
nReserved               DWORD ?
tagCOLORCORRECTPALETTE  ends
EMRCOLORCORRECTPALETTE  typedef tagCOLORCORRECTPALETTE
PEMRCOLORCORRECTPALETTE typedef ptr tagCOLORCORRECTPALETTE

tagEMRALPHABLEND        struct
emr                     EMR <>
rclBounds               RECTL <>
xDest                   LONG ?
yDest                   LONG ?
cxDest                  LONG ?
cyDest                  LONG ?
dwRop                   DWORD ?
xSrc                    LONG ?
ySrc                    LONG ?
xformSrc                XFORM <>
crBkColorSrc            COLORREF ?
iUsageSrc               DWORD ?
offBmiSrc               DWORD ?
cbBmiSrc                DWORD ?
offBitsSrc              DWORD ?
cbBitsSrc               DWORD ?
cxSrc                   LONG ?
cySrc                   LONG ?
tagEMRALPHABLEND        ends
EMRALPHABLEND           typedef tagEMRALPHABLEND
PEMRALPHABLEND          typedef ptr tagEMRALPHABLEND

tagEMRGRADIENTFILL      struct
emr                     EMR <>
rclBounds               RECTL <>
nVer                    DWORD ?
nTri                    DWORD ?
ulMode                  ULONG ?
Ver                     TRIVERTEX 1 dup(<>)
tagEMRGRADIENTFILL      ends
EMRGRADIENTFILL         typedef tagEMRGRADIENTFILL
PEMRGRADIENTFILL        typedef ptr tagEMRGRADIENTFILL

tagEMRTRANSPARENTBLT    struct
emr                     EMR <>
rclBounds               RECTL <>
xDest                   LONG ?
yDest                   LONG ?
cxDest                  LONG ?
cyDest                  LONG ?
dwRop                   DWORD ?
xSrc                    LONG ?
ySrc                    LONG ?
xformSrc                XFORM <>
crBkColorSrc            COLORREF ?
iUsageSrc               DWORD ?
offBmiSrc               DWORD ?
cbBmiSrc                DWORD ?
offBitsSrc              DWORD ?
cbBitsSrc               DWORD ?
cxSrc                   LONG ?
cySrc                   LONG ?
tagEMRTRANSPARENTBLT    ends
EMRTRANSPARENTBLT       typedef tagEMRTRANSPARENTBLT
PEMRTRANSPARENTBLT      typedef ptr tagEMRTRANSPARENTBLT

endif

define GDICOMMENT_IDENTIFIER           0x43494447
define GDICOMMENT_WINDOWS_METAFILE     0x80000001
define GDICOMMENT_BEGINGROUP           0x00000002
define GDICOMMENT_ENDGROUP             0x00000003
define GDICOMMENT_MULTIFORMATS         0x40000004
define EPS_SIGNATURE                   0x46535045
define GDICOMMENT_UNICODE_STRING       0x00000040
define GDICOMMENT_UNICODE_END          0x00000080

endif

.pragma comment(lib, opengl32)

wglCopyContext proto WINAPI :HGLRC, :HGLRC, :UINT
wglCreateContext proto WINAPI :HDC
wglCreateLayerContext proto WINAPI :HDC, :sdword
wglDeleteContext proto WINAPI :HGLRC
wglGetCurrentContext proto WINAPI
wglGetCurrentDC proto WINAPI
wglGetProcAddress proto WINAPI :LPCSTR
wglMakeCurrent proto WINAPI :HDC, :HGLRC
wglShareLists proto WINAPI :HGLRC, :HGLRC
wglUseFontBitmapsA proto WINAPI :HDC, :DWORD, :DWORD, :DWORD
wglUseFontBitmapsW proto WINAPI :HDC, :DWORD, :DWORD, :DWORD
ifdef _UNICODE
define wglUseFontBitmaps  <wglUseFontBitmapsW>
else
define wglUseFontBitmaps  <wglUseFontBitmapsA>
endif

.pragma comment(lib, gdi32)

SwapBuffers proto WINAPI :HDC

_POINTFLOAT             struct
x                       FLOAT ?
y                       FLOAT ?
_POINTFLOAT             ends
POINTFLOAT              typedef _POINTFLOAT
PPOINTFLOAT             typedef ptr _POINTFLOAT

_GLYPHMETRICSFLOAT      struct
gmfBlackBoxX            FLOAT ?
gmfBlackBoxY            FLOAT ?
gmfptGlyphOrigin        POINTFLOAT <>
gmfCellIncX             FLOAT ?
gmfCellIncY             FLOAT ?
_GLYPHMETRICSFLOAT      ends
GLYPHMETRICSFLOAT       typedef _GLYPHMETRICSFLOAT
PGLYPHMETRICSFLOAT      typedef ptr _GLYPHMETRICSFLOAT
LPGLYPHMETRICSFLOAT     typedef ptr _GLYPHMETRICSFLOAT

.pragma comment(lib, opengl32)

define WGL_FONT_LINES      0
define WGL_FONT_POLYGONS   1
wglUseFontOutlinesA proto WINAPI :HDC, :DWORD, :DWORD, :DWORD, :FLOAT, :FLOAT, :sdword, :LPGLYPHMETRICSFLOAT
wglUseFontOutlinesW proto WINAPI :HDC, :DWORD, :DWORD, :DWORD, :FLOAT, :FLOAT, :sdword, :LPGLYPHMETRICSFLOAT
ifdef _UNICODE
define wglUseFontOutlines  <wglUseFontOutlinesW>
else
define wglUseFontOutlines  <wglUseFontOutlinesA>
endif

tagLAYERPLANEDESCRIPTOR struct
nSize                   WORD ?
nVersion                WORD ?
dwFlags                 DWORD ?
iPixelType              BYTE ?
cColorBits              BYTE ?
cRedBits                BYTE ?
cRedShift               BYTE ?
cGreenBits              BYTE ?
cGreenShift             BYTE ?
cBlueBits               BYTE ?
cBlueShift              BYTE ?
cAlphaBits              BYTE ?
cAlphaShift             BYTE ?
cAccumBits              BYTE ?
cAccumRedBits           BYTE ?
cAccumGreenBits         BYTE ?
cAccumBlueBits          BYTE ?
cAccumAlphaBits         BYTE ?
cDepthBits              BYTE ?
cStencilBits            BYTE ?
cAuxBuffers             BYTE ?
iLayerPlane             BYTE ?
bReserved               BYTE ?
crTransparent           COLORREF ?
tagLAYERPLANEDESCRIPTOR ends
LAYERPLANEDESCRIPTOR    typedef tagLAYERPLANEDESCRIPTOR
PLAYERPLANEDESCRIPTOR   typedef ptr tagLAYERPLANEDESCRIPTOR
LPLAYERPLANEDESCRIPTOR  typedef ptr tagLAYERPLANEDESCRIPTOR

define LPD_DOUBLEBUFFER        0x00000001
define LPD_STEREO              0x00000002
define LPD_SUPPORT_GDI         0x00000010
define LPD_SUPPORT_OPENGL      0x00000020
define LPD_SHARE_DEPTH         0x00000040
define LPD_SHARE_STENCIL       0x00000080
define LPD_SHARE_ACCUM         0x00000100
define LPD_SWAP_EXCHANGE       0x00000200
define LPD_SWAP_COPY           0x00000400
define LPD_TRANSPARENT         0x00001000

define LPD_TYPE_RGBA        0
define LPD_TYPE_COLORINDEX  1

define WGL_SWAP_MAIN_PLANE     0x00000001
define WGL_SWAP_OVERLAY1       0x00000002
define WGL_SWAP_OVERLAY2       0x00000004
define WGL_SWAP_OVERLAY3       0x00000008
define WGL_SWAP_OVERLAY4       0x00000010
define WGL_SWAP_OVERLAY5       0x00000020
define WGL_SWAP_OVERLAY6       0x00000040
define WGL_SWAP_OVERLAY7       0x00000080
define WGL_SWAP_OVERLAY8       0x00000100
define WGL_SWAP_OVERLAY9       0x00000200
define WGL_SWAP_OVERLAY10      0x00000400
define WGL_SWAP_OVERLAY11      0x00000800
define WGL_SWAP_OVERLAY12      0x00001000
define WGL_SWAP_OVERLAY13      0x00002000
define WGL_SWAP_OVERLAY14      0x00004000
define WGL_SWAP_OVERLAY15      0x00008000
define WGL_SWAP_UNDERLAY1      0x00010000
define WGL_SWAP_UNDERLAY2      0x00020000
define WGL_SWAP_UNDERLAY3      0x00040000
define WGL_SWAP_UNDERLAY4      0x00080000
define WGL_SWAP_UNDERLAY5      0x00100000
define WGL_SWAP_UNDERLAY6      0x00200000
define WGL_SWAP_UNDERLAY7      0x00400000
define WGL_SWAP_UNDERLAY8      0x00800000
define WGL_SWAP_UNDERLAY9      0x01000000
define WGL_SWAP_UNDERLAY10     0x02000000
define WGL_SWAP_UNDERLAY11     0x04000000
define WGL_SWAP_UNDERLAY12     0x08000000
define WGL_SWAP_UNDERLAY13     0x10000000
define WGL_SWAP_UNDERLAY14     0x20000000
define WGL_SWAP_UNDERLAY15     0x40000000

wglDescribeLayerPlane proto WINAPI :HDC, :sdword, :sdword, :UINT, :LPLAYERPLANEDESCRIPTOR
wglSetLayerPaletteEntries proto WINAPI :HDC, :sdword, :sdword, :sdword, :ptr
wglGetLayerPaletteEntries proto WINAPI :HDC, :sdword, :sdword, :sdword, :ptr
wglRealizeLayerPalette proto WINAPI :HDC, :sdword, :BOOL
wglSwapLayerBuffers proto WINAPI :HDC, :UINT

if (WINVER ge 0x0500)

_WGLSWAP                struct
hdc                     HDC ?
uiFlags                 UINT ?
_WGLSWAP                ends
WGLSWAP                 typedef _WGLSWAP
PWGLSWAP                typedef ptr _WGLSWAP
LPWGLSWAP               typedef ptr _WGLSWAP

define WGL_SWAPMULTIPLE_MAX 16

wglSwapMultipleBuffers proto WINAPI :UINT, :ptr

endif

endif

endif

.pragma list(pop)
endif

