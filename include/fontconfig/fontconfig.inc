
ifndef _FONTCONFIG_H_
define _FONTCONFIG_H_

;include sys/types.inc
include sys/stat.inc
include stdarg.inc
include limits.inc

ifndef FcPublic
define FcPublic
endif

FcChar8			typedef byte
FcChar16		typedef word
FcChar32		typedef dword
FcBool			typedef sdword


define FC_MAJOR		2
define FC_MINOR		14
define FC_REVISION	0

FC_VERSION		equ ((FC_MAJOR * 10000) + (FC_MINOR * 100) + (FC_REVISION))


define FC_CACHE_VERSION_NUMBER	8
_FC_STRINGIFY_ macro s
	exitm<@CatStr(<!">, s, <!">)>
	endm
_FC_STRINGIFY macro s
	exitm<_FC_STRINGIFY_(s)>
	endm
FC_CACHE_VERSION	equ <_FC_STRINGIFY(FC_CACHE_VERSION_NUMBER)>

define FcFalse		0
define FcTrue		1
define FcDontCare	2

define FC_FAMILY	<"family">
define FC_STYLE		<"style">
define FC_SLANT		<"slant">
define FC_WEIGHT	<"weight">
define FC_SIZE		<"size">
define FC_ASPECT	<"aspect">
define FC_PIXEL_SIZE	<"pixelsize">
define FC_SPACING	<"spacing">
define FC_FOUNDRY	<"foundry">
define FC_ANTIALIAS	<"antialias">
define FC_HINTING	<"hinting">
define FC_HINT_STYLE	<"hintstyle">
define FC_VERTICAL_LAYOUT <"verticallayout">
define FC_AUTOHINT	<"autohint">

define FC_GLOBAL_ADVANCE <"globaladvance">
define FC_WIDTH		<"width">
define FC_FILE		<"file">
define FC_INDEX		<"index">
define FC_FT_FACE	<"ftface">
define FC_RASTERIZER	<"rasterizer">
define FC_OUTLINE	"outline">
define FC_SCALABLE	"scalable">
define FC_COLOR		"color">
define FC_VARIABLE	"variable">
define FC_SCALE		<"scale">
define FC_SYMBOL	<"symbol">
define FC_DPI		<"dpi">
define FC_RGBA		<"rgba">
define FC_MINSPACE	<"minspace">
define FC_SOURCE	<"source">
define FC_CHARSET	<"charset">
define FC_LANG		<"lang">
define FC_FONTVERSION	<"fontversion">
define FC_FULLNAME	<"fullname">
define FC_FAMILYLANG	<"familylang">
define FC_STYLELANG	<"stylelang">
define FC_FULLNAMELANG	<"fullnamelang">
define FC_CAPABILITY	<"capability">
define FC_FONTFORMAT	<"fontformat">
define FC_EMBOLDEN	<"embolden">
define FC_EMBEDDED_BITMAP <"embeddedbitmap">
define FC_DECORATIVE	<"decorative">
define FC_LCD_FILTER	<"lcdfilter">
define FC_FONT_FEATURES <"fontfeatures">
define FC_FONT_VARIATIONS <"fontvariations">
define FC_NAMELANG	<"namelang">
define FC_PRGNAME	<"prgname">
define FC_HASH		<"hash">
define FC_POSTSCRIPT_NAME <"postscriptname">
define FC_FONT_HAS_HINT <"fonthashint">
define FC_ORDER		<"order">

define FC_CACHE_SUFFIX	<".cache-" FC_CACHE_VERSION>
define FC_DIR_CACHE_FILE <"fonts.cache-" FC_CACHE_VERSION>
define FC_USER_CACHE_FILE <".fonts.cache-" FC_CACHE_VERSION>


define FC_CHARWIDTH	<"charwidth">
define FC_CHAR_WIDTH	FC_CHARWIDTH
define FC_CHAR_HEIGHT	<"charheight">
define FC_MATRIX	<"matrix">

define FC_WEIGHT_THIN		0
define FC_WEIGHT_EXTRALIGHT	40
define FC_WEIGHT_ULTRALIGHT	FC_WEIGHT_EXTRALIGHT
define FC_WEIGHT_LIGHT		50
define FC_WEIGHT_DEMILIGHT	55
define FC_WEIGHT_SEMILIGHT	FC_WEIGHT_DEMILIGHT
define FC_WEIGHT_BOOK		75
define FC_WEIGHT_REGULAR	80
define FC_WEIGHT_NORMAL		FC_WEIGHT_REGULAR
define FC_WEIGHT_MEDIUM		100
define FC_WEIGHT_DEMIBOLD	180
define FC_WEIGHT_SEMIBOLD	FC_WEIGHT_DEMIBOLD
define FC_WEIGHT_BOLD		200
define FC_WEIGHT_EXTRABOLD	205
define FC_WEIGHT_ULTRABOLD	FC_WEIGHT_EXTRABOLD
define FC_WEIGHT_BLACK		210
define FC_WEIGHT_HEAVY		FC_WEIGHT_BLACK
define FC_WEIGHT_EXTRABLACK	215
define FC_WEIGHT_ULTRABLACK	FC_WEIGHT_EXTRABLACK

define FC_SLANT_ROMAN		0
define FC_SLANT_ITALIC		100
define FC_SLANT_OBLIQUE		110

define FC_WIDTH_ULTRACONDENSED	50
define FC_WIDTH_EXTRACONDENSED	63
define FC_WIDTH_CONDENSED	75
define FC_WIDTH_SEMICONDENSED	87
define FC_WIDTH_NORMAL		100
define FC_WIDTH_SEMIEXPANDED	113
define FC_WIDTH_EXPANDED	125
define FC_WIDTH_EXTRAEXPANDED	150
define FC_WIDTH_ULTRAEXPANDED	200

define FC_PROPORTIONAL		0
define FC_DUAL			90
define FC_MONO			100
define FC_CHARCELL		110


define FC_RGBA_UNKNOWN		0
define FC_RGBA_RGB		1
define FC_RGBA_BGR		2
define FC_RGBA_VRGB		3
define FC_RGBA_VBGR		4
define FC_RGBA_NONE		5


define FC_HINT_NONE		0
define FC_HINT_SLIGHT		1
define FC_HINT_MEDIUM		2
define FC_HINT_FULL		3


define FC_LCD_NONE		0
define FC_LCD_DEFAULT		1
define FC_LCD_LIGHT		2
define FC_LCD_LEGACY		3

.enum FcType {
    FcTypeUnknown = -1,
    FcTypeVoid,
    FcTypeInteger,
    FcTypeDouble,
    FcTypeString,
    FcTypeBool,
    FcTypeMatrix,
    FcTypeCharSet,
    FcTypeFTFace,
    FcTypeLangSet,
    FcTypeRange
    }

FcMatrix		STRUC
xx			double ?
xy			double ?
yx			double ?
yy			double ?
FcMatrix		ENDS

FcMatrixInit macro m
	exitm<.err>
	endm

FcCharSet		typedef FcCharSet

FcObjectType		STRUC
object			ptr ?
type			FcType ?
FcObjectType		ENDS

FcConstant		STRUC
name			ptr FcChar8 ?
object			ptr char_t ?
value			SINT ?
FcConstant		ENDS

.enum FcResult {
    FcResultMatch,
    FcResultNoMatch,
    FcResultTypeMismatch,
    FcResultNoId,
    FcResultOutOfMemory
    }

.enum FcValueBinding {
    FcValueBindingWeak,
    FcValueBindingStrong,
    FcValueBindingSame,
    FcValueBindingEnd = INT_MAX
    }

FcPattern		typedef FcPattern

FcPatternIter		STRUC
dummy1			ptr ?
dummy2			ptr ?
FcPatternIter		ENDS

FcLangSet		typedef FcLangSet
FcRange			typedef FcRange

FcValue			STRUC
type			FcType ?
UNION u
s			ptr FcChar8 ?
i			SINT ?
b			FcBool ?
d			double ?
m			ptr FcMatrix ?
c			ptr FcCharSet ?
f			ptr ?
l			ptr FcLangSet ?
r			ptr FcRange ?
ENDS
FcValue			ENDS

FcFontSet		STRUC
nfont			SINT ?
sfont			SINT ?
fonts			ptr FcPattern ?
FcFontSet		ENDS

FcObjectSet		STRUC
nobject			SINT ?
sobject			SINT ?
objects			ptr char_t ?
FcObjectSet		ENDS

.enum FcMatchKind {
    FcMatchPattern,
    FcMatchFont,
    FcMatchScan,
    FcMatchKindEnd,
    FcMatchKindBegin = FcMatchPattern
    }

.enum FcLangResult {
    FcLangEqual = 0,
    FcLangDifferentCountry = 1,
    FcLangDifferentTerritory = 1,
    FcLangDifferentLang = 2
    }

.enum FcSetName {
    FcSetSystem = 0,
    FcSetApplication = 1
    }

FcConfigFileInfoIter	STRUC
dummy1			ptr ?
dummy2			ptr ?
dummy3			ptr ?
FcConfigFileInfoIter	ENDS

.enum FcEndian {
    FcEndianBig,
    FcEndianLittle
    }

FcConfig		typedef byte ; _FcConfig
FcFileCache		typedef byte ; _FcGlobalCache
FcBlanks		typedef byte ; _FcBlanks
FcStrList		typedef byte ; _FcStrList
FcStrSet		typedef byte ; _FcStrSet
FcCache			typedef byte ; _FcCache

FcBlanksCreate		proto
FcBlanksDestroy		proto :ptr cBlanks
FcBlanksAdd		proto :ptr cBlanks, :FcChar32
FcBlanksIsMember	proto :ptr cBlanks, :FcChar32

FcCacheDir		proto :ptr FcCache
FcCacheCopySet		proto :ptr FcCache
FcCacheSubdir		proto :ptr cCache, :int_t
FcCacheNumSubdir	proto :ptr cCache
FcCacheNumFont		proto :ptr cCache
FcDirCacheUnlink	proto :ptr cChar8, :ptr FcConfig
FcDirCacheValid		proto :ptr cChar8
FcDirCacheClean		proto :ptr cChar8, :FcBool
FcCacheCreateTagFile	proto :ptr cConfig
FcDirCacheCreateUUID	proto :ptr cChar8, :FcBool, :ptr FcConfig
FcDirCacheDeleteUUID	proto :ptr cChar8, :ptr FcConfig

FcConfigHome		proto
FcConfigEnableHome	proto :FcBool
FcConfigGetFilename	proto :ptr cConfig, :ptr FcChar8
FcConfigFilename	proto :ptr cChar8
FcConfigCreate		proto
FcConfigReference	proto :ptr cConfig
FcConfigDestroy		proto :ptr cConfig
FcConfigSetCurrent	proto :ptr cConfig
FcConfigGetCurrent	proto
FcConfigUptoDate	proto :ptr cConfig
FcConfigBuildFonts	proto :ptr cConfig
FcConfigGetFontDirs	proto :ptr cConfig
FcConfigGetConfigDirs	proto :ptr cConfig
FcConfigGetConfigFiles	proto :ptr cConfig
FcConfigGetCache	proto :ptr cConfig
FcConfigGetBlanks	proto :ptr cConfig
FcConfigGetCacheDirs	proto :ptr cConfig
FcConfigGetRescanInterval proto :ptr cConfig
FcConfigSetRescanInterval proto :ptr cConfig, :int_t
FcConfigGetFonts	proto :ptr cConfig, :FcSetName
FcConfigAppFontAddFile	proto :ptr cConfig, :ptr FcChar8
FcConfigAppFontAddDir	proto :ptr cConfig, :ptr FcChar8
FcConfigAppFontClear	proto :ptr cConfig
FcConfigSubstituteWithPat proto :ptr cConfig, :ptr FcPattern, :ptr FcPattern, :FcMatchKind
FcConfigSubstitute	proto :ptr cConfig, :ptr FcPattern, :FcMatchKind
FcConfigGetSysRoot	proto :ptr cConfig
FcConfigSetSysRoot	proto :ptr cConfig, :ptr FcChar8
FcConfigFileInfoIterInit proto :ptr cConfig, :ptr FcConfigFileInfoIter
FcConfigFileInfoIterNext proto :ptr cConfig, :ptr FcConfigFileInfoIter
FcConfigFileInfoIterGet proto :ptr cConfig, :ptr FcConfigFileInfoIter, :ptr FcChar8, :ptr FcChar8, :ptr FcBool

FcCharSetCreate		proto

FcCharSetNew		proto
FcCharSetDestroy	proto :ptr cCharSet
FcCharSetAddChar	proto :ptr cCharSet, :FcChar32
FcCharSetDelChar	proto :ptr cCharSet, :FcChar32
FcCharSetCopy		proto :ptr cCharSet
FcCharSetEqual		proto :ptr cCharSet, :ptr FcCharSet
FcCharSetIntersect	proto :ptr cCharSet, :ptr FcCharSet
FcCharSetUnion		proto :ptr cCharSet, :ptr FcCharSet
FcCharSetSubtract	proto :ptr cCharSet, :ptr FcCharSet
FcCharSetMerge		proto :ptr cCharSet, :ptr FcCharSet, :ptr FcBool
FcCharSetHasChar	proto :ptr cCharSet, :FcChar32
FcCharSetCount		proto :ptr cCharSet
FcCharSetIntersectCount proto :ptr cCharSet, :ptr FcCharSet
FcCharSetSubtractCount	proto :ptr cCharSet, :ptr FcCharSet
FcCharSetIsSubset	proto :ptr cCharSet, :ptr FcCharSet

FC_CHARSET_MAP_SIZE	equ (256/32)
FC_CHARSET_DONE		equ (-1)

FcCharSetFirstPage	proto :ptr cCharSet, :ptr FcChar32, :ptr FcChar32
FcCharSetNextPage	proto :ptr cCharSet, :ptr FcChar32, :ptr FcChar32

FcCharSetCoverage	proto :ptr cCharSet, :FcChar32, :ptr FcChar32

FcValuePrint		proto :FcValue
FcPatternPrint		proto :ptr cPattern
FcFontSetPrint		proto :ptr cFontSet

FcGetDefaultLangs	proto
FcDefaultSubstitute	proto :ptr cPattern

FcFileIsDir		proto :ptr cChar8
FcFileScan		proto :ptr cFontSet, :ptr FcStrSet, :ptr FcFileCache, :ptr FcBlanks, :ptr FcChar8, :FcBool
FcDirScan		proto :ptr cFontSet, :ptr FcStrSet, :ptr FcFileCache, :ptr FcBlanks, :ptr FcChar8, :FcBool

FcDirSave		proto :ptr cFontSet, :ptr FcStrSet, :ptr FcChar8
FcDirCacheLoad		proto :ptr cChar8, :ptr FcConfig, :ptr FcChar8
FcDirCacheRescan	proto :ptr cChar8, :ptr FcConfig
FcDirCacheRead		proto :ptr cChar8, :FcBool, :ptr FcConfig
FcDirCacheLoadFile	proto :ptr cChar8, :ptr
FcDirCacheUnload	proto :ptr cCache

FcFreeTypeQuery		proto :ptr cChar8, :uint_t, :ptr FcBlanks, :ptr
FcFreeTypeQueryAll	proto :ptr FcChar8, :uint_t, :ptr FcBlanks, :ptr, :ptr FcFontSet

FcFontSetCreate		proto
FcFontSetDestroy	proto :ptr cFontSet
FcFontSetAdd		proto :ptr cFontSet, :ptr FcPattern

FcInitLoadConfig	proto
FcInitLoadConfigAndFonts proto
FcInit			proto
FcFini			proto
FcGetVersion		proto
FcInitReinitialize	proto
FcInitBringUptoDate	proto

FcGetLangs		proto
FcLangNormalize		proto :ptr cChar8
FcLangGetCharSet	proto :ptr cChar8
FcLangSetCreate		proto
FcLangSetDestroy	proto :ptr cLangSet
FcLangSetCopy		proto :ptr cLangSet
FcLangSetAdd		proto :ptr cLangSet, :ptr FcChar8
FcLangSetDel		proto :ptr cLangSet, :ptr FcChar8
FcLangSetHasLang	proto :ptr cLangSet, :ptr FcChar8
FcLangSetCompare	proto :ptr cLangSet, :ptr FcLangSet
FcLangSetContains	proto :ptr cLangSet, :ptr FcLangSet
FcLangSetEqual		proto :ptr cLangSet, :ptr FcLangSet
FcLangSetHash		proto :ptr cLangSet
FcLangSetGetLangs	proto :ptr cLangSet
FcLangSetUnion		proto :ptr cLangSet, :ptr FcLangSet
FcLangSetSubtract	proto :ptr cLangSet, :ptr FcLangSet

FcObjectSetCreate	proto
FcObjectSetAdd		proto :ptr cObjectSet, :ptr
FcObjectSetDestroy	proto :ptr cObjectSet
FcObjectSetVaBuild	proto :ptr, :va_list
FcObjectSetBuild	proto :ptr, :vararg
FcFontSetList		proto :ptr cConfig, :ptr FcFontSet, :SINT, :ptr FcPattern, :ptr FcObjectSet
FcFontList		proto :ptr cConfig, :ptr FcPattern, :ptr FcObjectSet

FcAtomicCreate		proto :ptr cChar8
FcAtomicLock		proto :ptr cAtomic
FcAtomicNewFile		proto :ptr cAtomic
FcAtomicOrigFile	proto :ptr cAtomic
FcAtomicReplaceOrig	proto :ptr cAtomic
FcAtomicDeleteNew	proto :ptr cAtomic
FcAtomicUnlock		proto :ptr cAtomic
FcAtomicDestroy		proto :ptr cAtomic

FcFontSetMatch		proto :ptr cConfig, :ptr, :SINT, :ptr FcPattern, :ptr FcResult
FcFontMatch		proto :ptr cConfig, :ptr FcPattern, :ptr FcResult
FcFontRenderPrepare	proto :ptr cConfig, :ptr FcPattern, :ptr FcPattern
FcFontSetSort		proto :ptr cConfig, :ptr FcFontSet, :SINT, :ptr FcPattern, :FcBool, :ptr FcCharSet, :ptr FcResult
FcFontSort		proto :ptr cConfig, :ptr FcPattern, :FcBool, :ptr FcCharSet, :ptr FcResult

FcFontSetSortDestroy	proto :ptr cFontSet

FcMatrixCopy		proto :ptr cMatrix
FcMatrixEqual		proto :ptr cMatrix, :ptr FcMatrix
FcMatrixMultiply	proto :ptr cMatrix, :ptr FcMatrix, :ptr FcMatrix
FcMatrixRotate		proto :ptr cMatrix, :double, :double
FcMatrixScale		proto :ptr cMatrix, :double, :double
FcMatrixShear		proto :ptr cMatrix, :double, :double

FcNameRegisterObjectTypes proto :ptr cObjectType, :int_t

FcNameUnregisterObjectTypes proto :ptr cObjectType, :int_t
FcNameGetObjectType	proto :ptr

FcNameRegisterConstants proto :ptr cConstant, :int_t

FcNameUnregisterConstants proto :ptr cConstant, :int_t
FcNameGetConstant	proto :ptr cChar8
FcNameConstant		proto :ptr cChar8, :ptr
FcNameParse		proto :ptr cChar8
FcNameUnparse		proto :ptr cPattern

FcPatternCreate		proto
FcPatternDuplicate	proto :ptr cPattern
FcPatternReference	proto :ptr cPattern
FcPatternFilter		proto :ptr cPattern, :ptr FcObjectSet
FcValueDestroy		proto :FcValue

FcValueEqual		proto :FcValue, :FcValue
FcValueSave		proto :FcValue
FcPatternDestroy	proto :ptr cPattern

FcPatternObjectCount	proto :ptr FcPattern

FcPatternEqual		proto :ptr cPattern, :ptr FcPattern
FcPatternEqualSubset	proto :ptr cPattern, :ptr FcPattern, :ptr FcObjectSet
FcPatternHash		proto :ptr cPattern
FcPatternAdd		proto :ptr cPattern, :ptr, :FcValue, :FcBool
FcPatternAddWeak	proto :ptr cPattern, :ptr, :FcValue, :FcBool
FcPatternGet		proto :ptr cPattern, :ptr, :int_t, :ptr FcValue
FcPatternGetWithBinding proto :ptr cPattern, :ptr, :int_t, :ptr FcValue, :ptr FcValueBinding
FcPatternDel		proto :ptr cPattern, :ptr
FcPatternRemove		proto :ptr cPattern, :ptr, :int_t
FcPatternAddInteger	proto :ptr cPattern, :ptr, :int_t
FcPatternAddDouble	proto :ptr cPattern, :ptr, :double
FcPatternAddString	proto :ptr cPattern, :ptr, :ptr FcChar8
FcPatternAddMatrix	proto :ptr cPattern, :ptr, :ptr FcMatrix
FcPatternAddCharSet	proto :ptr cPattern, :ptr, :ptr FcCharSet
FcPatternAddBool	proto :ptr cPattern, :ptr, :FcBool
FcPatternAddLangSet	proto :ptr cPattern, :ptr, :ptr FcLangSet
FcPatternAddRange	proto :ptr cPattern, :ptr, :ptr FcRange
FcPatternGetInteger	proto :ptr cPattern, :ptr, :int_t, :ptr
FcPatternGetDouble	proto :ptr cPattern, :ptr, :int_t, :ptr double
FcPatternGetString	proto :ptr cPattern, :ptr, :int_t, :ptr FcChar8
FcPatternGetMatrix	proto :ptr cPattern, :ptr, :int_t, :ptr FcMatrix
FcPatternGetCharSet	proto :ptr cPattern, :ptr, :int_t, :ptr FcCharSet
FcPatternGetBool	proto :ptr cPattern, :ptr, :int_t, :ptr FcBool
FcPatternGetLangSet	proto :ptr cPattern, :ptr, :int_t, :ptr FcLangSet
FcPatternGetRange	proto :ptr cPattern, :ptr, :int_t, :ptr FcRange
FcPatternVaBuild	proto :ptr cPattern, :ptr
FcPatternBuild		proto :ptr cPattern, :vararg
FcPatternFormat		proto :ptr cPattern, :ptr FcChar8

FcRangeCreateDouble	proto :double, :double
FcRangeCreateInteger	proto :FcChar32, :FcChar32
FcRangeDestroy		proto :ptr cRange
FcRangeCopy		proto :ptr cRange
FcRangeGetDouble	proto :ptr FcRange, :ptr double, :ptr double
FcPatternIterStart	proto :ptr cPattern, :ptr FcPatternIter
FcPatternIterNext	proto :ptr cPattern, :ptr FcPatternIter
FcPatternIterEqual	proto :ptr cPattern, :ptr FcPatternIter, :ptr, :ptr
FcPatternFindIter	proto :ptr cPattern, :ptr FcPatternIter, :ptr
FcPatternIterIsValid	proto :ptr cPattern, :ptr FcPatternIter
FcPatternIterGetObject	proto :ptr cPattern, :ptr FcPatternIter
FcPatternIterValueCount proto :ptr cPattern, :ptr FcPatternIter

FcPatternIterGetValue	proto :ptr cPattern, :ptr FcPatternIter, :int_t, :ptr FcValue, :ptr FcValueBinding

FcWeightFromOpenType	proto :int_t
FcWeightFromOpenTypeDouble proto :double
FcWeightToOpenType	proto :int_t
FcWeightToOpenTypeDouble proto :double

FcStrCopy		proto :ptr cChar8
FcStrCopyFilename	proto :ptr cChar8
FcStrPlus		proto :ptr cChar8, :ptr FcChar8
FcStrFree		proto :ptr cChar8

FcIsUpper macro c
	exitm<((0101 LE (c) AND (c) LE 0132))>
	endm
FcIsLower macro c
	exitm<((0141 LE (c) AND (c) LE 0172))>
	endm
FcToLower macro c
	exitm<(FcIsUpper(c) ? (c) - 0101 + 0141 : (c))>
	endm

FcStrDowncase		proto :ptr cChar8
FcStrCmpIgnoreCase	proto :ptr cChar8, :ptr FcChar8
FcStrCmp		proto :ptr cChar8, :ptr FcChar8
FcStrStrIgnoreCase	proto :ptr cChar8, :ptr FcChar8
FcStrStr		proto :ptr cChar8, :ptr FcChar8
FcUtf8ToUcs4		proto :ptr cChar8, :ptr FcChar32, :SINT
FcUtf8Len		proto :ptr cChar8, :SINT, :ptr, :ptr

define FC_UTF8_MAX_LEN	6

FcUcs4ToUtf8		proto :FcChar32, :ptr
FcUtf16ToUcs4		proto :ptr cChar8, :FcEndian, :ptr FcChar32, :SINT
FcUtf16Len		proto :ptr cChar8, :FcEndian, :SINT, :ptr, :ptr
FcStrBuildFilename	proto :ptr cChar8, :vararg
FcStrDirname		proto :ptr cChar8
FcStrBasename		proto :ptr cChar8
FcStrSetCreate		proto
FcStrSetMember		proto :ptr cStrSet, :ptr FcChar8
FcStrSetEqual		proto :ptr cStrSet, :ptr FcStrSet
FcStrSetAdd		proto :ptr cStrSet, :ptr FcChar8
FcStrSetAddFilename	proto :ptr cStrSet, :ptr FcChar8
FcStrSetDel		proto :ptr cStrSet, :ptr FcChar8
FcStrSetDestroy		proto :ptr cStrSet
FcStrListCreate		proto :ptr cStrSet
FcStrListFirst		proto :ptr cStrList
FcStrListNext		proto :ptr cStrList
FcStrListDone		proto :ptr cStrList

FcConfigParseAndLoad	proto :ptr cConfig, :ptr FcChar8, :FcBool
FcConfigParseAndLoadFromMemory proto :ptr cConfig, :ptr FcChar8, :FcBool

undef FC_ATTRIBUTE_SENTINEL

ifndef _FCINT_H_
define FcConfigGetRescanInverval <FcConfigGetRescanInverval_REPLACE_BY_FcConfigGetRescanInterval>
define FcConfigSetRescanInverval <FcConfigSetRescanInverval_REPLACE_BY_FcConfigSetRescanInterval>
endif

endif
