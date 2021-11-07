ifndef DWRITE_H_INCLUDED
DWRITE_H_INCLUDED equ 1

ifndef DWRITE_NO_WINDOWS_H

include specstrings.inc
include unknwn.inc

endif

include dcommon.inc

.pragma comment(lib, dwrite)
.pragma pack(push, size_t)

ifndef DWRITE_DECLARE_INTERFACE
DWRITE_DECLARE_INTERFACE macro iid
	exitm<DECLSPEC_UUID(iid) DECLSPEC_NOVTABLE>
	endm
endif

.enum DWRITE_FONT_FILE_TYPE {
    DWRITE_FONT_FILE_TYPE_UNKNOWN,
    DWRITE_FONT_FILE_TYPE_CFF,
    DWRITE_FONT_FILE_TYPE_TRUETYPE,
    DWRITE_FONT_FILE_TYPE_TRUETYPE_COLLECTION,
    DWRITE_FONT_FILE_TYPE_TYPE1_PFM,
    DWRITE_FONT_FILE_TYPE_TYPE1_PFB,
    DWRITE_FONT_FILE_TYPE_VECTOR,
    DWRITE_FONT_FILE_TYPE_BITMAP
    }

.enum DWRITE_FONT_FACE_TYPE {
    DWRITE_FONT_FACE_TYPE_CFF,
    DWRITE_FONT_FACE_TYPE_TRUETYPE,
    DWRITE_FONT_FACE_TYPE_TRUETYPE_COLLECTION,
    DWRITE_FONT_FACE_TYPE_TYPE1,
    DWRITE_FONT_FACE_TYPE_VECTOR,
    DWRITE_FONT_FACE_TYPE_BITMAP,
    DWRITE_FONT_FACE_TYPE_UNKNOWN,
    DWRITE_FONT_FACE_TYPE_RAW_CFF
    }

.enum DWRITE_FONT_SIMULATIONS {
    DWRITE_FONT_SIMULATIONS_NONE    = 0x0000,
    DWRITE_FONT_SIMULATIONS_BOLD    = 0x0001,
    DWRITE_FONT_SIMULATIONS_OBLIQUE = 0x0002
    }

.enum DWRITE_FONT_WEIGHT {
    DWRITE_FONT_WEIGHT_THIN = 100,
    DWRITE_FONT_WEIGHT_EXTRA_LIGHT = 200,
    DWRITE_FONT_WEIGHT_ULTRA_LIGHT = 200,
    DWRITE_FONT_WEIGHT_LIGHT = 300,
    DWRITE_FONT_WEIGHT_SEMI_LIGHT = 350,
    DWRITE_FONT_WEIGHT_NORMAL = 400,
    DWRITE_FONT_WEIGHT_REGULAR = 400,
    DWRITE_FONT_WEIGHT_MEDIUM = 500,
    DWRITE_FONT_WEIGHT_DEMI_BOLD = 600,
    DWRITE_FONT_WEIGHT_SEMI_BOLD = 600,
    DWRITE_FONT_WEIGHT_BOLD = 700,
    DWRITE_FONT_WEIGHT_EXTRA_BOLD = 800,
    DWRITE_FONT_WEIGHT_ULTRA_BOLD = 800,
    DWRITE_FONT_WEIGHT_BLACK = 900,
    DWRITE_FONT_WEIGHT_HEAVY = 900,
    DWRITE_FONT_WEIGHT_EXTRA_BLACK = 950,
    DWRITE_FONT_WEIGHT_ULTRA_BLACK = 950
    }

.enum DWRITE_FONT_STRETCH {
    DWRITE_FONT_STRETCH_UNDEFINED = 0,
    DWRITE_FONT_STRETCH_ULTRA_CONDENSED = 1,
    DWRITE_FONT_STRETCH_EXTRA_CONDENSED = 2,
    DWRITE_FONT_STRETCH_CONDENSED = 3,
    DWRITE_FONT_STRETCH_SEMI_CONDENSED = 4,
    DWRITE_FONT_STRETCH_NORMAL = 5,
    DWRITE_FONT_STRETCH_MEDIUM = 5,
    DWRITE_FONT_STRETCH_SEMI_EXPANDED = 6,
    DWRITE_FONT_STRETCH_EXPANDED = 7,
    DWRITE_FONT_STRETCH_EXTRA_EXPANDED = 8,
    DWRITE_FONT_STRETCH_ULTRA_EXPANDED = 9
    }

.enum DWRITE_FONT_STYLE {
    DWRITE_FONT_STYLE_NORMAL,
    DWRITE_FONT_STYLE_OBLIQUE,
    DWRITE_FONT_STYLE_ITALIC
    }

.enum DWRITE_INFORMATIONAL_STRING_ID {
    DWRITE_INFORMATIONAL_STRING_NONE,
    DWRITE_INFORMATIONAL_STRING_COPYRIGHT_NOTICE,
    DWRITE_INFORMATIONAL_STRING_VERSION_STRINGS,
    DWRITE_INFORMATIONAL_STRING_TRADEMARK,
    DWRITE_INFORMATIONAL_STRING_MANUFACTURER,
    DWRITE_INFORMATIONAL_STRING_DESIGNER,
    DWRITE_INFORMATIONAL_STRING_DESIGNER_URL,
    DWRITE_INFORMATIONAL_STRING_DESCRIPTION,
    DWRITE_INFORMATIONAL_STRING_FONT_VENDOR_URL,
    DWRITE_INFORMATIONAL_STRING_LICENSE_DESCRIPTION,
    DWRITE_INFORMATIONAL_STRING_LICENSE_INFO_URL,
    DWRITE_INFORMATIONAL_STRING_WIN32_FAMILY_NAMES,
    DWRITE_INFORMATIONAL_STRING_WIN32_SUBFAMILY_NAMES,
    DWRITE_INFORMATIONAL_STRING_PREFERRED_FAMILY_NAMES,
    DWRITE_INFORMATIONAL_STRING_PREFERRED_SUBFAMILY_NAMES,
    DWRITE_INFORMATIONAL_STRING_SAMPLE_TEXT,
    DWRITE_INFORMATIONAL_STRING_FULL_NAME,
    DWRITE_INFORMATIONAL_STRING_POSTSCRIPT_NAME,
    DWRITE_INFORMATIONAL_STRING_POSTSCRIPT_CID_NAME
    }


DWRITE_FONT_METRICS	STRUC
designUnitsPerEm	UINT16 ?
ascent			UINT16 ?
descent			UINT16 ?
lineGap			INT16 ?
capHeight		UINT16 ?
xHeight			UINT16 ?
underlinePosition	INT16 ?
underlineThickness	UINT16 ?
strikethroughPosition	INT16 ?
strikethroughThickness	UINT16 ?
DWRITE_FONT_METRICS	ENDS

DWRITE_GLYPH_METRICS	STRUC
leftSideBearing		INT32 ?
advanceWidth		UINT32 ?
rightSideBearing	INT32 ?
topSideBearing		INT32 ?
advanceHeight		UINT32 ?
bottomSideBearing	INT32 ?
verticalOriginY		INT32 ?
DWRITE_GLYPH_METRICS	ENDS

DWRITE_GLYPH_OFFSET	STRUC
advanceOffset		FLOAT ?
ascenderOffset		FLOAT ?
DWRITE_GLYPH_OFFSET	ENDS

.enum DWRITE_FACTORY_TYPE {
    DWRITE_FACTORY_TYPE_SHARED,
    DWRITE_FACTORY_TYPE_ISOLATED
    }

DWRITE_MAKE_OPENTYPE_TAG macro a,b,c,d
	exitm<((d) shr 24 or (c) shr 16 or (b) shr 8 or (a))>
	endm


DEFINE_IIDX(IDWriteFontFileLoader, "727cad4e-d6af-4c9e-8a08-d695b11caa49")

.comdef IDWriteFontFileLoader : public IUnknown

    CreateStreamFromKey proc :ptr, :UINT32, :ptr ptr IDWriteFontFileStream
    .ends


DEFINE_IIDX(IDWriteLocalFontFileLoader, "b2d9f3ec-c9fe-4a11-a2ec-d86208f7c0a2")

.comdef IDWriteLocalFontFileLoader : public IDWriteFontFileLoader

    GetFilePathLengthFromKey	proc :ptr, :UINT32, :ptr UINT32
    GetFilePathFromKey		proc :ptr, :UINT32, :ptr WCHAR, :UINT32
    GetLastWriteTimeFromKey	proc :ptr, :UINT32, :ptr FILETIME
    .ends

DEFINE_IIDX(IDWriteFontFileStream, "6d4865fe-0ab8-4d91-8f62-5dd6be34a3e0")

.comdef IDWriteFontFileStream : public IUnknown

    ReadFileFragment		proc :ptr, :UINT64, :UINT64, :ptr ptr
    ReleaseFileFragment		proc :ptr
    GetFileSize			proc :ptr UINT64
    GetLastWriteTime		proc :ptr UINT64
    .ends

DEFINE_IIDX(IDWriteFontFile, "739d886a-cef5-47dc-8769-1a8b41bebbb0")

.comdef IDWriteFontFile : public IUnknown

    GetReferenceKey	proc :ptr ptr, :ptr UINT32
    GetLoader		proc :ptr ptr IDWriteFontFileLoader
    Analyze		proc :ptr, :ptr, :ptr, :ptr UINT32
    .ends


ifndef DWRITE_PIXEL_GEOMETRY_DEFINED
.enum DWRITE_PIXEL_GEOMETRY {
    DWRITE_PIXEL_GEOMETRY_FLAT,
    DWRITE_PIXEL_GEOMETRY_RGB,
    DWRITE_PIXEL_GEOMETRY_BGR
    }
DWRITE_PIXEL_GEOMETRY_DEFINED equ 1
endif

.enum DWRITE_RENDERING_MODE {
    DWRITE_RENDERING_MODE_DEFAULT,
    DWRITE_RENDERING_MODE_ALIASED,
    DWRITE_RENDERING_MODE_GDI_CLASSIC,
    DWRITE_RENDERING_MODE_GDI_NATURAL,
    DWRITE_RENDERING_MODE_NATURAL,
    DWRITE_RENDERING_MODE_NATURAL_SYMMETRIC,
    DWRITE_RENDERING_MODE_OUTLINE,
    DWRITE_RENDERING_MODE_CLEARTYPE_GDI_CLASSIC		= DWRITE_RENDERING_MODE_GDI_CLASSIC,
    DWRITE_RENDERING_MODE_CLEARTYPE_GDI_NATURAL		= DWRITE_RENDERING_MODE_GDI_NATURAL,
    DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL		= DWRITE_RENDERING_MODE_NATURAL,
    DWRITE_RENDERING_MODE_CLEARTYPE_NATURAL_SYMMETRIC	= DWRITE_RENDERING_MODE_NATURAL_SYMMETRIC
    }

DWRITE_MATRIX		STRUC
m11			FLOAT ?
m12			FLOAT ?
m21			FLOAT ?
m22			FLOAT ?
x			FLOAT ?
y			FLOAT ?
DWRITE_MATRIX		ENDS

DEFINE_IIDX(IDWriteRenderingParams, "2f0da53a-2add-47cd-82ee-d9ec34688e75")

.comdef IDWriteRenderingParams : public IUnknown

     GetGamma		proc
     GetEnhancedContrast proc
     GetClearTypeLevel	proc
     GetPixelGeometry	proc
     GetRenderingMode	proc
     .ends

DEFINE_IIDX(IDWriteFontFace, "5f49804d-7024-4d43-bfa9-d25984f53849")

.comdef IDWriteFontFace : public IUnknown

    GetType		proc
    GetFiles		proc :ptr UINT32, :ptr ptr IDWriteFontFile
    GetIndex		proc
    GetSimulations	proc
    IsSymbolFont	proc
    GetMetrics		proc :ptr
    GetGlyphCount	proc
    GetDesignGlyphMetrics proc :ptr UINT16, :UINT32, :ptr DWRITE_GLYPH_METRICS, :BOOL
    GetGlyphIndices	proc :ptr UINT32, :UINT32, :ptr UINT16
    TryGetFontTable	proc :UINT32, :ptr ptr, :ptr UINT32, :ptr ptr, :ptr BOOL
    ReleaseFontTable	proc :ptr
    GetGlyphRunOutline	proc :FLOAT, :ptr UINT16, :ptr FLOAT, :ptr DWRITE_GLYPH_OFFSET, :UINT32, :BOOL, :BOOL, :ptr IDWriteGeometrySink
    GetRecommendedRenderingMode proc :FLOAT, :FLOAT, :DWRITE_MEASURING_MODE, :ptr IDWriteRenderingParams, :ptr DWRITE_RENDERING_MODE
    GetGdiCompatibleMetrics proc :FLOAT, :FLOAT, :ptr, :ptr
    GetGdiCompatibleGlyphMetrics proc :FLOAT, :FLOAT, :ptr, :BOOL, :UINT32, :ptr, :BOOL
    .ends
    LPIDWriteFontFace	typedef ptr IDWriteFontFace


DEFINE_IIDX(IDWriteFontCollectionLoader, "cca920e4-52f0-492b-bfa8-29c72ee0a468")

.comdef IDWriteFontCollectionLoader : public IUnknown

    CreateEnumeratorFromKey proc :ptr IDWriteFactory, :ptr, :UINT32, :ptr ptr IDWriteFontFileEnumerator
    .ends

DEFINE_IIDX(IDWriteFontFileEnumerator, "72755049-5ff7-435d-8348-4be97cfa6c7c")

.comdef IDWriteFontFileEnumerator : public IUnknown

    MoveNext		proc :ptr BOOL
    GetCurrentFontFile	proc :ptr ptr IDWriteFontFile
    .ends

DEFINE_IIDX(IDWriteLocalizedStrings, "08256209-099a-4b34-b86d-c22b110e7771")

.comdef IDWriteLocalizedStrings : public IUnknown

    GetCount		proc
    FindLocaleName	proc :ptr WCHAR, :ptr UINT32, :ptr BOOL
    GetLocaleNameLength proc :UINT32, :ptr UINT32
    GetLocaleName	proc :UINT32, :ptr WCHAR, :UINT32
    GetStringLength	proc :UINT32, :ptr UINT32
    GetString		proc :UINT32, :ptr WCHAR, :UINT32
    .ends

DEFINE_IIDX(IDWriteFontCollection, "a84cee02-3eea-4eee-a827-87c1a02a0fcc")

.comdef IDWriteFontCollection : public IUnknown

    GetFontFamilyCount	proc
    GetFontFamily	proc :UINT32, :ptr ptr IDWriteFontFamily
    FindFamilyName	proc :ptr WCHAR, :ptr UINT32, :ptr BOOL
    GetFontFromFontFace proc :ptr IDWriteFontFace, :ptr ptr IDWriteFont
    .ends

DEFINE_IIDX(IDWriteFontList, "1a0d8438-1d97-4ec1-aef9-a2fb86ed6acb")

.comdef IDWriteFontList : public IUnknown

    GetFontCollection	proc :ptr ptr IDWriteFontCollection
    GetFontCount	proc
    GetFont		proc :UINT32, :ptr ptr IDWriteFont
    .ends

DEFINE_IIDX(IDWriteFontFamily, "da20d8ef-812a-4c43-9802-62ec4abd7add")

.comdef IDWriteFontFamily : public IDWriteFontList

    GetFamilyNames	proc :ptr ptr IDWriteLocalizedStrings
    GetFirstMatchingFont proc :DWRITE_FONT_WEIGHT, :DWRITE_FONT_STRETCH, :DWRITE_FONT_STYLE, :ptr ptr IDWriteFont
    GetMatchingFonts	proc :DWRITE_FONT_WEIGHT, :DWRITE_FONT_STRETCH, :DWRITE_FONT_STYLE, :ptr ptr IDWriteFontList
    .ends

DEFINE_IIDX(IDWriteFont, "acd16696-8c14-4f5d-877e-fe3fc1d32737")

.comdef IDWriteFont : public IUnknown

    GetFontFamily	proc :ptr ptr IDWriteFontFamily
    GetWeight		proc
    GetStretch		proc
    GetStyle		proc
    IsSymbolFont	proc
    GetFaceNames	proc :ptr ptr IDWriteLocalizedStrings
    GetInformationalStrings proc :DWRITE_INFORMATIONAL_STRING_ID, :ptr ptr IDWriteLocalizedStrings, :ptr BOOL
    GetSimulations	proc
    GetMetrics		proc :ptr
    HasCharacter	proc :UINT32, :ptr BOOL
    CreateFontFace	proc :ptr
    .ends


.enum DWRITE_READING_DIRECTION {
    DWRITE_READING_DIRECTION_LEFT_TO_RIGHT = 0,
    DWRITE_READING_DIRECTION_RIGHT_TO_LEFT = 1,
    DWRITE_READING_DIRECTION_TOP_TO_BOTTOM = 2,
    DWRITE_READING_DIRECTION_BOTTOM_TO_TOP = 3,
    }

.enum DWRITE_FLOW_DIRECTION {
    DWRITE_FLOW_DIRECTION_TOP_TO_BOTTOM = 0,
    DWRITE_FLOW_DIRECTION_BOTTOM_TO_TOP = 1,
    DWRITE_FLOW_DIRECTION_LEFT_TO_RIGHT = 2,
    DWRITE_FLOW_DIRECTION_RIGHT_TO_LEFT = 3,
    }

.enum DWRITE_TEXT_ALIGNMENT {
    DWRITE_TEXT_ALIGNMENT_LEADING,
    DWRITE_TEXT_ALIGNMENT_TRAILING,
    DWRITE_TEXT_ALIGNMENT_CENTER,
    DWRITE_TEXT_ALIGNMENT_JUSTIFIED
    }

.enum DWRITE_PARAGRAPH_ALIGNMENT {
    DWRITE_PARAGRAPH_ALIGNMENT_NEAR,
    DWRITE_PARAGRAPH_ALIGNMENT_FAR,
    DWRITE_PARAGRAPH_ALIGNMENT_CENTER
    }

.enum DWRITE_WORD_WRAPPING {
    DWRITE_WORD_WRAPPING_WRAP = 0,
    DWRITE_WORD_WRAPPING_NO_WRAP = 1,
    DWRITE_WORD_WRAPPING_EMERGENCY_BREAK = 2,
    DWRITE_WORD_WRAPPING_WHOLE_WORD = 3,
    DWRITE_WORD_WRAPPING_CHARACTER = 4,
    }

.enum DWRITE_LINE_SPACING_METHOD {
    DWRITE_LINE_SPACING_METHOD_DEFAULT,
    DWRITE_LINE_SPACING_METHOD_UNIFORM
    }

.enum DWRITE_TRIMMING_GRANULARITY {
    DWRITE_TRIMMING_GRANULARITY_NONE,
    DWRITE_TRIMMING_GRANULARITY_CHARACTER,
    DWRITE_TRIMMING_GRANULARITY_WORD
    }

.enum DWRITE_FONT_FEATURE_TAG {
    DWRITE_FONT_FEATURE_TAG_ALTERNATIVE_FRACTIONS		= 0x63726661,
    DWRITE_FONT_FEATURE_TAG_PETITE_CAPITALS_FROM_CAPITALS	= 0x63703263,
    DWRITE_FONT_FEATURE_TAG_SMALL_CAPITALS_FROM_CAPITALS	= 0x63733263,
    DWRITE_FONT_FEATURE_TAG_CONTEXTUAL_ALTERNATES		= 0x746c6163,
    DWRITE_FONT_FEATURE_TAG_CASE_SENSITIVE_FORMS		= 0x65736163,
    DWRITE_FONT_FEATURE_TAG_GLYPH_COMPOSITION_DECOMPOSITION	= 0x706d6363,
    DWRITE_FONT_FEATURE_TAG_CONTEXTUAL_LIGATURES		= 0x67696c63,
    DWRITE_FONT_FEATURE_TAG_CAPITAL_SPACING			= 0x70737063,
    DWRITE_FONT_FEATURE_TAG_CONTEXTUAL_SWASH			= 0x68777363,
    DWRITE_FONT_FEATURE_TAG_CURSIVE_POSITIONING			= 0x73727563,
    DWRITE_FONT_FEATURE_TAG_DEFAULT				= 0x746c6664,
    DWRITE_FONT_FEATURE_TAG_DISCRETIONARY_LIGATURES		= 0x67696c64,
    DWRITE_FONT_FEATURE_TAG_EXPERT_FORMS			= 0x74707865,
    DWRITE_FONT_FEATURE_TAG_FRACTIONS				= 0x63617266,
    DWRITE_FONT_FEATURE_TAG_FULL_WIDTH				= 0x64697766,
    DWRITE_FONT_FEATURE_TAG_HALF_FORMS				= 0x666c6168,
    DWRITE_FONT_FEATURE_TAG_HALANT_FORMS			= 0x6e6c6168,
    DWRITE_FONT_FEATURE_TAG_ALTERNATE_HALF_WIDTH		= 0x746c6168,
    DWRITE_FONT_FEATURE_TAG_HISTORICAL_FORMS			= 0x74736968,
    DWRITE_FONT_FEATURE_TAG_HORIZONTAL_KANA_ALTERNATES		= 0x616e6b68,
    DWRITE_FONT_FEATURE_TAG_HISTORICAL_LIGATURES		= 0x67696c68,
    DWRITE_FONT_FEATURE_TAG_HALF_WIDTH				= 0x64697768,
    DWRITE_FONT_FEATURE_TAG_HOJO_KANJI_FORMS			= 0x6f6a6f68,
    DWRITE_FONT_FEATURE_TAG_JIS04_FORMS				= 0x3430706a,
    DWRITE_FONT_FEATURE_TAG_JIS78_FORMS				= 0x3837706a,
    DWRITE_FONT_FEATURE_TAG_JIS83_FORMS				= 0x3338706a,
    DWRITE_FONT_FEATURE_TAG_JIS90_FORMS				= 0x3039706a,
    DWRITE_FONT_FEATURE_TAG_KERNING				= 0x6e72656b,
    DWRITE_FONT_FEATURE_TAG_STANDARD_LIGATURES			= 0x6167696c,
    DWRITE_FONT_FEATURE_TAG_LINING_FIGURES			= 0x6d756e6c,
    DWRITE_FONT_FEATURE_TAG_LOCALIZED_FORMS			= 0x6c636f6c,
    DWRITE_FONT_FEATURE_TAG_MARK_POSITIONING			= 0x6b72616d,
    DWRITE_FONT_FEATURE_TAG_MATHEMATICAL_GREEK			= 0x6b72676d,
    DWRITE_FONT_FEATURE_TAG_MARK_TO_MARK_POSITIONING		= 0x6b6d6b6d,
    DWRITE_FONT_FEATURE_TAG_ALTERNATE_ANNOTATION_FORMS		= 0x746c616e,
    DWRITE_FONT_FEATURE_TAG_NLC_KANJI_FORMS			= 0x6b636c6e,
    DWRITE_FONT_FEATURE_TAG_OLD_STYLE_FIGURES			= 0x6d756e6f,
    DWRITE_FONT_FEATURE_TAG_ORDINALS				= 0x6e64726f,
    DWRITE_FONT_FEATURE_TAG_PROPORTIONAL_ALTERNATE_WIDTH	= 0x746c6170,
    DWRITE_FONT_FEATURE_TAG_PETITE_CAPITALS			= 0x70616370,
    DWRITE_FONT_FEATURE_TAG_PROPORTIONAL_FIGURES		= 0x6d756e70,
    DWRITE_FONT_FEATURE_TAG_PROPORTIONAL_WIDTHS			= 0x64697770,
    DWRITE_FONT_FEATURE_TAG_QUARTER_WIDTHS			= 0x64697771,
    DWRITE_FONT_FEATURE_TAG_REQUIRED_LIGATURES			= 0x67696c72,
    DWRITE_FONT_FEATURE_TAG_RUBY_NOTATION_FORMS			= 0x79627572,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_ALTERNATES		= 0x746c6173,
    DWRITE_FONT_FEATURE_TAG_SCIENTIFIC_INFERIORS		= 0x666e6973,
    DWRITE_FONT_FEATURE_TAG_SMALL_CAPITALS			= 0x70636d73,
    DWRITE_FONT_FEATURE_TAG_SIMPLIFIED_FORMS			= 0x6c706d73,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_1			= 0x31307373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_2			= 0x32307373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_3			= 0x33307373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_4			= 0x34307373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_5			= 0x35307373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_6			= 0x36307373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_7			= 0x37307373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_8			= 0x38307373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_9			= 0x39307373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_10			= 0x30317373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_11			= 0x31317373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_12			= 0x32317373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_13			= 0x33317373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_14			= 0x34317373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_15			= 0x35317373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_16			= 0x36317373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_17			= 0x37317373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_18			= 0x38317373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_19			= 0x39317373,
    DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_20			= 0x30327373,
    DWRITE_FONT_FEATURE_TAG_SUBSCRIPT				= 0x73627573,
    DWRITE_FONT_FEATURE_TAG_SUPERSCRIPT				= 0x73707573,
    DWRITE_FONT_FEATURE_TAG_SWASH				= 0x68737773,
    DWRITE_FONT_FEATURE_TAG_TITLING				= 0x6c746974,
    DWRITE_FONT_FEATURE_TAG_TRADITIONAL_NAME_FORMS		= 0x6d616e74,
    DWRITE_FONT_FEATURE_TAG_TABULAR_FIGURES			= 0x6d756e74,
    DWRITE_FONT_FEATURE_TAG_TRADITIONAL_FORMS			= 0x64617274,
    DWRITE_FONT_FEATURE_TAG_THIRD_WIDTHS			= 0x64697774,
    DWRITE_FONT_FEATURE_TAG_UNICASE				= 0x63696e75,
    DWRITE_FONT_FEATURE_TAG_VERTICAL_WRITING			= 0x74726576,
    DWRITE_FONT_FEATURE_TAG_VERTICAL_ALTERNATES_AND_ROTATION	= 0x32747276,
    DWRITE_FONT_FEATURE_TAG_SLASHED_ZERO			= 0x6f72657a,
    }

DWRITE_TEXT_RANGE	STRUC
startPosition		UINT32 ?
length			UINT32 ?
DWRITE_TEXT_RANGE	ENDS

DWRITE_FONT_FEATURE	STRUC
nameTag			DWRITE_FONT_FEATURE_TAG ?
parameter		UINT32 ?
DWRITE_FONT_FEATURE	ENDS

DWRITE_TYPOGRAPHIC_FEATURES STRUC
features		PVOID ?
featureCount		UINT32 ?
DWRITE_TYPOGRAPHIC_FEATURES ENDS

DWRITE_TRIMMING		STRUC
granularity		DWRITE_TRIMMING_GRANULARITY ?
delimiter		UINT32 ?
delimiterCount		UINT32 ?
DWRITE_TRIMMING		ENDS


DEFINE_IIDX(IDWriteTextFormat, "9c906818-31d7-4fd3-a151-7c5e225db55a")

.comdef IDWriteTextFormat : public IUnknown

    SetTextAlignment	proc :DWRITE_TEXT_ALIGNMENT
    SetParagraphAlignment proc :DWRITE_PARAGRAPH_ALIGNMENT
    SetWordWrapping	proc :DWRITE_WORD_WRAPPING
    SetReadingDirection proc :DWRITE_READING_DIRECTION
    SetFlowDirection	proc :DWRITE_FLOW_DIRECTION
    SetIncrementalTabStop proc :FLOAT
    SetTrimming		proc :ptr DWRITE_TRIMMING, :ptr IDWriteInlineObject
    SetLineSpacing	proc :DWRITE_LINE_SPACING_METHOD, :FLOAT, :FLOAT
    GetTextAlignment	proc
    GetParagraphAlignment proc
    GetWordWrapping	proc
    GetReadingDirection proc
    GetFlowDirection	proc
    GetIncrementalTabStop proc
    GetTrimming		proc :ptr DWRITE_TRIMMING, :ptr ptr
    GetLineSpacing	proc :ptr DWRITE_LINE_SPACING_METHOD, :ptr FOAT, :ptr LOAT
    GetFontCollection	proc :ptr ptr IDWriteFontCollection
    GetFontFamilyNameLength proc
    GetFontFamilyName	proc :UINT32
    GetFontWeight	proc
    GetFontStyle	proc
    GetFontStretch	proc
    GetFontSize		proc
    GetLocaleNameLength proc
    GetLocaleName	proc :UINT32
    .ends


DEFINE_IIDX(IDWriteTypography, "55f1112b-1dc2-4b3c-9541-f46894ed85b6")

.comdef IDWriteTypography : public IUnknown
    AddFontFeature	proc :DWRITE_FONT_FEATURE
    GetFontFeatureCount proc
    GetFontFeature	proc :UINT32, :ptr DWRITE_FONT_FEATURE
    .ends

.enum DWRITE_SCRIPT_SHAPES {
    DWRITE_SCRIPT_SHAPES_DEFAULT = 0,
    DWRITE_SCRIPT_SHAPES_NO_VISUAL = 1
    }

DWRITE_SCRIPT_ANALYSIS	STRUC
script			UINT16 ?
shapes			DWRITE_SCRIPT_SHAPES ?
DWRITE_SCRIPT_ANALYSIS	ENDS

.enum DWRITE_BREAK_CONDITION {
    DWRITE_BREAK_CONDITION_NEUTRAL,
    DWRITE_BREAK_CONDITION_CAN_BREAK,
    DWRITE_BREAK_CONDITION_MAY_NOT_BREAK,
    DWRITE_BREAK_CONDITION_MUST_BREAK
    }

DWRITE_LINE_BREAKPOINT STRUC
;breakConditionBefore : 2 UINT8 ?
;breakConditionAfter  : 2 UINT8 ?
;isWhitespace	      : 1 UINT8 ?
;isSoftHyphen	      : 1 UINT8 ?
;padding	      : 2 UINT8 ?
flags		      UINT8 ?
DWRITE_LINE_BREAKPOINT ENDS

.enum DWRITE_NUMBER_SUBSTITUTION_METHOD {
    DWRITE_NUMBER_SUBSTITUTION_METHOD_FROM_CULTURE,
    DWRITE_NUMBER_SUBSTITUTION_METHOD_CONTEXTUAL,
    DWRITE_NUMBER_SUBSTITUTION_METHOD_NONE,
    DWRITE_NUMBER_SUBSTITUTION_METHOD_NATIONAL,
    DWRITE_NUMBER_SUBSTITUTION_METHOD_TRADITIONAL
    }


DEFINE_IIDX(IDWriteNumberSubstitution, "14885CC9-BAB0-4f90-B6ED-5C366A2CD03D")

.comdef IDWriteNumberSubstitution : public IUnknown
    .ends

DWRITE_SHAPING_TEXT_PROPERTIES STRUC
;isShapedAlone	    : 1 UINT16 ?
;reserved	    : 15 UINT16 ?
flags		      UINT16 ?
DWRITE_SHAPING_TEXT_PROPERTIES ENDS

DWRITE_SHAPING_GLYPH_PROPERTIES STRUC
;justification	    : 4 UINT16 ?
;isClusterStart	    : 1 UINT16 ?
;isDiacritic	    : 1 UINT16 ?
;isZeroWidthSpace    : 1 UINT16 ?
;reserved	    : 9 UINT16 ?
flags		      UINT16 ?
DWRITE_SHAPING_GLYPH_PROPERTIES ENDS

DEFINE_IIDX(IDWriteTextAnalysisSource, "688e1a58-5094-47c8-adc8-fbcea60ae92b")

.comdef IDWriteTextAnalysisSource : public IUnknown

    GetTextAtPosition	proc :UINT32, :ptr UINT32
    GetTextBeforePosition proc :UINT32, :ptr UINT32
    GetParagraphReadingDirection proc
    GetLocaleName	proc :UINT32, :ptr UINT32, :ptr WCHAR
    GetNumberSubstitution proc :UINT32, :ptr UINT32, :ptr ptr IDWriteNumberSubstitution
    .ends

DEFINE_IIDX(IDWriteTextAnalysisSink, "5810cd44-0ca0-4701-b3fa-bec5182ae4f6")

.comdef IDWriteTextAnalysisSink : public IUnknown

    SetScriptAnalysis	proc :UINT32, :UINT32, :ptr DWRITE_SCRIPT_ANALYSIS
    SetLineBreakpoints	proc :UINT32, :UINT32
    SetBidiLevel	proc :UINT32, :UINT32, :UINT8, :UINT8
    SetNumberSubstitution proc :UINT32, :UINT32, :ptr IDWriteNumberSubstitution
    .ends

DEFINE_IIDX(IDWriteTextAnalyzer, "b7e6163e-7f46-43b4-84b3-e4e6249c365d")

.comdef IDWriteTextAnalyzer : public IUnknown

    AnalyzeScript proc \
	:ptr IDWriteTextAnalysisSource,
	:UINT32,
	:UINT32,
	:ptr IDWriteTextAnalysisSink
    AnalyzeBidi proc \
	:ptr IDWriteTextAnalysisSource,
	:UINT32,
	:UINT32,
	:ptr IDWriteTextAnalysisSink
    AnalyzeNumberSubstitution proc \
	:ptr IDWriteTextAnalysisSource,
	:UINT32,
	:UINT32,
	:ptr IDWriteTextAnalysisSink
    AnalyzeLineBreakpoints proc \
	:ptr IDWriteTextAnalysisSource,
	:UINT32,
	:UINT32,
	:ptr IDWriteTextAnalysisSink
    GetGlyphs proc \
	:UINT32,
	:ptr IDWriteFontFace,
	:BOOL,
	:BOOL,
	:ptr, :ptr WCHAR,
	:ptr IDWriteNumberSubstitution,
	:ptr DWRITE_TYPOGRAPHIC_FEATURES,
	:ptr UINT32,
	:UINT32,
	:UINT32,
	:ptr UINT16,
	:ptr DWRITE_SHAPING_TEXT_PROPERTIES,
	:ptr UINT16,
	:ptr DWRITE_SHAPING_GLYPH_PROPERTIES,
	:ptr UINT32
    GetGlyphPlacements proc \
	:ptr UINT16,
	:ptr DWRITE_SHAPING_TEXT_PROPERTIES,
	:UINT32,
	:ptr UINT16,
	:ptr DWRITE_SHAPING_GLYPH_PROPERTIES,
	:UINT32,
	:ptr IDWriteFontFace,
	:FLOAT,
	:BOOL,
	:BOOL,
	:ptr DWRITE_SCRIPT_ANALYSIS,
	:ptr WCHAR,
	:ptr ptr DWRITE_TYPOGRAPHIC_FEATURES,
	:ptr UINT32,
	:UINT32,
	:ptr FLOAT,
	:ptr DWRITE_GLYPH_OFFSET
    GetGdiCompatibleGlyphPlacements proc \
	:ptr UINT16,
	:ptr DWRITE_SHAPING_TEXT_PROPERTIES,
	:UINT32,
	:ptr UINT16,
	:ptr DWRITE_SHAPING_GLYPH_PROPERTIES,
	:UINT32,
	:ptr IDWriteFontFace,
	:FLOAT,
	:FLOAT,
	:ptr DWRITE_MATRIX,
	:BOOL,
	:BOOL,
	:BOOL,
	:ptr DWRITE_SCRIPT_ANALYSIS,
	:ptr WCHAR,
	:ptr ptr DWRITE_TYPOGRAPHIC_FEATURES,
	:ptr UINT32,
	:UINT32,
	:ptr FLOAT,
	:ptr DWRITE_GLYPH_OFFSET
    .ends


DWRITE_GLYPH_RUN	STRUC
fontFace		LPIDWriteFontFace ?
fontEmSize		FLOAT ?
glyphCount		UINT32 ?
glyphIndices		PVOID ? ; WORD
glyphAdvances		PVOID ? ; FLOAT
glyphOffsets		PVOID ? ; DWRITE_GLYPH_OFFSET
isSideways		BOOL ?
bidiLevel		UINT32 ?
DWRITE_GLYPH_RUN	ENDS

DWRITE_GLYPH_RUN_DESCRIPTION STRUC
localeName		LPWSTR ?
string			LPWSTR ?
stringLength		UINT32 ?
clusterMap		PVOID ?
textPosition		UINT32 ?
DWRITE_GLYPH_RUN_DESCRIPTION ENDS

DWRITE_UNDERLINE	STRUC
width			FLOAT ?
thickness		FLOAT ?
offs			FLOAT ?
runHeight		FLOAT ?
readingDirection	DWRITE_READING_DIRECTION ?
flowDirection		DWRITE_FLOW_DIRECTION ?
localeName		LPWSTR ?
measuringMode		DWRITE_MEASURING_MODE ?
DWRITE_UNDERLINE	ENDS

DWRITE_STRIKETHROUGH	STRUC
width			FLOAT ?
thickness		FLOAT ?
offs			FLOAT ?
readingDirection	DWRITE_READING_DIRECTION ?
flowDirection		DWRITE_FLOW_DIRECTION ?
localeName		LPWSTR ?
measuringMode		DWRITE_MEASURING_MODE ?
DWRITE_STRIKETHROUGH	ENDS

DWRITE_LINE_METRICS	STRUC
length			UINT32 ?
trailingWhitespaceLength UINT32 ?
newlineLength		UINT32 ?
height			FLOAT ?
baseline		FLOAT ?
isTrimmed		BOOL ?
DWRITE_LINE_METRICS	ENDS


DWRITE_CLUSTER_METRICS	STRUC
width			FLOAT ?
length			UINT16 ?
;canWrapLineAfter : 1	UINT16 ?
;isWhitespace : 1	UINT16 ?
;isNewline : 1		UINT16 ?
;isSoftHyphen : 1	UINT16 ?
;isRightToLeft : 1	UINT16 ?
;padding : 11		UINT16 ?
flags			UINT16 ?
DWRITE_CLUSTER_METRICS	ENDS


DWRITE_TEXT_METRICS	STRUC
left			FLOAT ?
top			FLOAT ?
width			FLOAT ?
widthIncludingTrailingWhitespace FLOAT ?
height			FLOAT ?
layoutWidth		FLOAT ?
layoutHeight		FLOAT ?
maxBidiReorderingDepth	UINT32 ?
lineCount		UINT32 ?
DWRITE_TEXT_METRICS	ENDS


DWRITE_INLINE_OBJECT_METRICS STRUC
width			FLOAT ?
height			FLOAT ?
baseline		FLOAT ?
supportsSideways	BOOL ?
DWRITE_INLINE_OBJECT_METRICS ENDS


DWRITE_OVERHANG_METRICS STRUC
left			FLOAT ?
top			FLOAT ?
right			FLOAT ?
bottom			FLOAT ?
DWRITE_OVERHANG_METRICS ENDS


DWRITE_HIT_TEST_METRICS STRUC
textPosition		UINT32 ?
length			UINT32 ?
left			FLOAT ?
top			FLOAT ?
width			FLOAT ?
height			FLOAT ?
bidiLevel		UINT32 ?
isText			BOOL ?
isTrimmed		BOOL ?
DWRITE_HIT_TEST_METRICS ENDS

DEFINE_IIDX(IDWriteInlineObject, "8339FDE3-106F-47ab-8373-1C6295EB10B3")

.comdef IDWriteInlineObject : public IUnknown

    Draw		proc :ptr, :ptr IDWriteTextRenderer, :FLOAT, :FLOAT, :BOOL, :BOOL, :ptr IUnknown
    GetMetrics		proc :ptr DWRITE_INLINE_OBJECT_METRICS
    GetOverhangMetrics	proc :ptr DWRITE_OVERHANG_METRICS
    GetBreakConditions	proc :ptr DWRITE_BREAK_CONDITION, :ptr DWRITE_BREAK_CONDITION
    .ends


DEFINE_IIDX(IDWritePixelSnapping, "eaf3a2da-ecf4-4d24-b644-b34f6842024b")

.comdef IDWritePixelSnapping : public IUnknown

    IsPixelSnappingDisabled proc :ptr, :ptr
    GetCurrentTransform proc :ptr, :ptr
    GetPixelsPerDip	proc :ptr, :ptr
    .ends


DEFINE_IIDX(IDWriteTextRenderer, "ef8a8135-5cc6-45fe-8825-c5a0724eb819")

.comdef IDWriteTextRenderer : public IDWritePixelSnapping

    DrawGlyphRun	proc :ptr, :FLOAT, :FLOAT, :DWRITE_MEASURING_MODE, :ptr DWRITE_GLYPH_RUN, :ptr DWRITE_GLYPH_RUN_DESCRIPTION, :ptr IUnknown
    DrawUnderline	proc :ptr, :FLOAT, :FLOAT, :ptr DWRITE_UNDERLINE, :ptr IUnknown
    DrawStrikethrough	proc :ptr, :FLOAT, :FLOAT, :ptr DWRITE_STRIKETHROUGH, :ptr IUnknown
    DrawInlineObject	proc :ptr, :FLOAT, :FLOAT, :ptr IDWriteInlineObject, :BOOL, :BOOL, :ptr IUnknown
    .ends


DEFINE_IIDX(IDWriteTextLayout, "53737037-6d14-410b-9bfe-0b182bb70961")

.comdef IDWriteTextLayout : public IUnknown

    SetTextAlignment	proc :DWRITE_TEXT_ALIGNMENT
    SetParagraphAlignment proc :DWRITE_PARAGRAPH_ALIGNMENT
    SetWordWrapping	proc :DWRITE_WORD_WRAPPING
    SetReadingDirection proc :DWRITE_READING_DIRECTION
    SetFlowDirection	proc :DWRITE_FLOW_DIRECTION
    SetIncrementalTabStop proc :FLOAT
    SetTrimming		proc :ptr DWRITE_TRIMMING, :ptr IDWriteInlineObject
    SetLineSpacing	proc :DWRITE_LINE_SPACING_METHOD, :FLOAT, :FLOAT
    GetTextAlignment	proc
    GetParagraphAlignment proc
    GetWordWrapping	proc
    GetReadingDirection proc
    GetFlowDirection	proc
    GetIncrementalTabStop proc
    GetTrimming		proc :ptr DWRITE_TRIMMING, :ptr ptr
    GetLineSpacing	proc :ptr DWRITE_LINE_SPACING_METHOD, :ptr FOAT, :ptr LOAT
    GetFontCollection?	proc :ptr ptr IDWriteFontCollection
    GetFontFamilyNameLength? proc
    GetFontFamilyName?	proc :UINT32
    GetFontWeight?	proc
    GetFontStyle?	proc
    GetFontStretch?	proc
    GetFontSize?	proc
    GetLocaleNameLength? proc
    GetLocaleName	proc :UINT32

    SetMaxWidth		proc :FLOAT
    SetMaxHeight	proc :FLOAT
    SetFontCollection	proc :ptr IDWriteFontCollection, :DWRITE_TEXT_RANGE
    SetFontFamilyName	proc :ptr WCHAR, :DWRITE_TEXT_RANGE
    SetFontWeight	proc :DWRITE_FONT_WEIGHT, :DWRITE_TEXT_RANGE
    SetFontStyle	proc :DWRITE_FONT_STYLE, :DWRITE_TEXT_RANGE
    SetFontStretch	proc :DWRITE_FONT_STRETCH, :DWRITE_TEXT_RANGE
    SetFontSize		proc :FLOAT, :DWRITE_TEXT_RANGE
    SetUnderline	proc :BOOL, :DWRITE_TEXT_RANGE
    SetStrikethrough	proc :BOOL, :DWRITE_TEXT_RANGE
    SetDrawingEffect	proc :ptr IUnknown, :DWRITE_TEXT_RANGE
    SetInlineObject	proc :ptr IDWriteInlineObject, :DWRITE_TEXT_RANGE
    SetTypography	proc :ptr IDWriteTypography, :DWRITE_TEXT_RANGE
    SetLocaleName	proc :ptr WCHAR, :DWRITE_TEXT_RANGE
    GetMaxWidth		proc
    GetMaxHeight	proc

    GetFontCollection	proc :UINT32, :ptr ptr IDWriteFontCollection, :ptr DWRITE_TEXT_RANGE
    GetFontFamilyNameLength proc :UINT32, :ptr UINT32, :ptr DWRITE_TEXT_RANGE
    GetFontFamilyName	proc :UINT32, :UINT32, :ptr DWRITE_TEXT_RANGE
    GetFontWeight	proc :UINT32, :ptr DWRITE_FONT_WEIGHT, :ptr DWRITE_TEXT_RANGE
    GetFontStyle	proc :UINT32, :ptr DWRITE_FONT_STYLE, :ptr DWRITE_TEXT_RANGE
    GetFontStretch	proc :UINT32, :ptr DWRITE_FONT_STRETCH, :ptr DWRITE_TEXT_RANGE
    GetFontSize		proc :UINT32, :ptr FLOAT, :ptr DWRITE_TEXT_RANGE

    GetUnderline	proc :UINT32, :ptr BOOL, :ptr DWRITE_TEXT_RANGE
    GetStrikethrough	proc :UINT32, :ptr BOOL, :ptr DWRITE_TEXT_RANGE
    GetDrawingEffect	proc :UINT32, :ptr IUnknown, :ptr DWRITE_TEXT_RANGE
    GetInlineObject	proc :UINT32, :ptr IDWriteInlineObject, :ptr DWRITE_TEXT_RANGE
    GetTypography	proc :UINT32, :ptr IDWriteTypography, :ptr DWRITE_TEXT_RANGE

    GetLocaleNameLength proc :UINT32, :ptr UINT32, :ptr DWRITE_TEXT_RANGE
    GetLocaleName2	proc :UINT32, :UINT32, :ptr DWRITE_TEXT_RANGE
    Draw		proc :ptr, :ptr IDWriteTextRenderer, :FLOAT, :FLOAT
    GetLineMetrics	proc :UINT32, :ptr UINT32
    GetMetrics		proc :ptr DWRITE_TEXT_METRICS
    GetOverhangMetrics	proc :ptr DWRITE_OVERHANG_METRICS
    GetClusterMetrics	proc :UINT32, :ptr UINT32
    DetermineMinWidth	proc :ptr FLOAT
    HitTestPoint	proc :FLOAT, :FLOAT, :ptr BOOL, :ptr BOOL, :ptr DWRITE_HIT_TEST_METRICS
    HitTestTextPosition proc :UINT32, :BOOL, :ptr FLOAT, :ptr FLOAT, :ptr DWRITE_HIT_TEST_METRICS
    HitTestTextRange	proc :UINT32, :UINT32, :FLOAT, :FLOAT, :UINT32, :ptr UINT32
    .ends


DEFINE_IIDX(IDWriteBitmapRenderTarget, "5e5a32a3-8dff-4773-9ff6-0696eab77267")

.comdef IDWriteBitmapRenderTarget : public IUnknown

    DrawGlyphRun	proc :FLOAT, :FLOAT, :DWRITE_MEASURING_MODE, :ptr DWRITE_GLYPH_RUN, :ptr IDWriteRenderingParams, :COLORREF, :ptr RECT
    GetMemoryDC		proc
    GetPixelsPerDip	proc
    SetPixelsPerDip	proc :FLOAT
    GetCurrentTransform proc :ptr DWRITE_MATRIX
    SetCurrentTransform proc :ptr DWRITE_MATRIX
    GetSize		proc :ptr
    Resize		proc :UINT32, :UINT32
    .ends


DEFINE_IIDX(IDWriteGdiInterop, "1edd9491-9853-4299-898f-6432983b6f3a")

.comdef IDWriteGdiInterop : public IUnknown

    CreateFontFromLOGFONT	proc :ptr LOGFONTW, :ptr ptr IDWriteFont
    ConvertFontToLOGFONT	proc :ptr IDWriteFont, :ptr LOGFONTW, :ptr BOOL
    ConvertFontFaceToLOGFONT	proc :ptr IDWriteFontFace, :ptr LOGFONTW
    CreateFontFaceFromHdc	proc :HDC, :ptr ptr IDWriteFontFace
    CreateBitmapRenderTarget	proc :HDC, :UINT32, :UINT32, :ptr ptr IDWriteBitmapRenderTarget
    .ends

.enum DWRITE_TEXTURE_TYPE {
    DWRITE_TEXTURE_ALIASED_1x1,
    DWRITE_TEXTURE_CLEARTYPE_3x1
    }

DWRITE_ALPHA_MAX	equ 255

DEFINE_IIDX(IDWriteGlyphRunAnalysis, "7d97dbf7-e085-42d4-81e3-6a883bded118")

.comdef IDWriteGlyphRunAnalysis : public IUnknown

    GetAlphaTextureBounds	proc :DWRITE_TEXTURE_TYPE, :ptr RECT
    CreateAlphaTexture		proc :DWRITE_TEXTURE_TYPE, :ptr RECT, :UINT32
    GetAlphaBlendParams		proc :ptr IDWriteRenderingParams, :ptr FLOAT, :ptr FLOAT, :ptr FLOAT
    .ends

DEFINE_IIDX(IDWriteFactory, "b859ee5a-d838-4b5b-a2e8-1adc7d93db48")

.comdef IDWriteFactory : public IUnknown

    GetSystemFontCollection	proc :ptr ptr IDWriteFontCollection, :BOOL
    CreateCustomFontCollection	proc :ptr IDWriteFontCollectionLoader, :UINT32, :ptr ptr IDWriteFontCollection
    RegisterFontCollectionLoader proc :ptr IDWriteFontCollectionLoader
    UnregisterFontCollectionLoader proc :ptr IDWriteFontCollectionLoader
    CreateFontFileReference	proc :ptr WCHAR, :ptr FILETIME, :ptr ptr IDWriteFontFile
    CreateCustomFontFileReference proc :UINT32, :ptr IDWriteFontFileLoader, :ptr ptr IDWriteFontFile
    CreateFontFace		proc :DWRITE_FONT_FACE_TYPE, :UINT32, :UINT32, :DWRITE_FONT_SIMULATIONS, :ptr ptr IDWriteFontFace
    CreateRenderingParams	proc :ptr ptr IDWriteRenderingParams
    CreateMonitorRenderingParams proc :HMONITOR, :ptr ptr IDWriteRenderingParams
    CreateCustomRenderingParams proc :FLOAT, :FLOAT, :FLOAT, :DWRITE_PIXEL_GEOMETRY, :DWRITE_RENDERING_MODE, :ptr ptr IDWriteRenderingParams
    RegisterFontFileLoader	proc :ptr IDWriteFontFileLoader
    UnregisterFontFileLoader	proc :ptr IDWriteFontFileLoader
    CreateTextFormat		proc :ptr ptr WCHAR, :ptr IDWriteFontCollection, :DWRITE_FONT_WEIGHT, :DWRITE_FONT_STYLE, :DWRITE_FONT_STRETCH, :FLOAT, :ptr WCHAR, :ptr ptr IDWriteTextFormat
    CreateTypography		proc :ptr ptr IDWriteTypography
    GetGdiInterop		proc :ptr ptr IDWriteGdiInterop
    CreateTextLayout		proc :ptr WCHAR, :UINT32, :ptr IDWriteTextFormat,  :FLOAT, :FLOAT, :ptr ptr IDWriteTextLayout
    CreateGdiCompatibleTextLayout proc :UINT32, :ptr IDWriteTextFormat, :FLOAT, :FLOAT, :FLOAT, :ptr DWRITE_MATRIX, :BOOL, :ptr ptr IDWriteTextLayout
    CreateEllipsisTrimmingSign	proc :ptr IDWriteTextFormat, :ptr ptr IDWriteInlineObject
    CreateTextAnalyzer		proc :ptr ptr IDWriteTextAnalyzer
    CreateNumberSubstitution	proc :DWRITE_NUMBER_SUBSTITUTION_METHOD, :ptr WCHAR, :BOOL, :ptr ptr IDWriteNumberSubstitution
    CreateGlyphRunAnalysis	proc :ptr DWRITE_GLYPH_RUN, :FLOAT, :ptr DWRITE_MATRIX, :DWRITE_RENDERING_MODE, :DWRITE_MEASURING_MODE, :FLOAT, :FLOAT, :ptr ptr IDWriteGlyphRunAnalysis
    .ends


DWriteCreateFactory proto :DWRITE_FACTORY_TYPE, :REFIID, :ptr ptr IUnknown

FACILITY_DWRITE		equ 0x898
DWRITE_ERR_BASE		equ 0x5000
MAKE_DWRITE_HR macro severity, code
	exitm<MAKE_HRESULT(severity, FACILITY_DWRITE, (DWRITE_ERR_BASE + code))>
	endm
MAKE_DWRITE_HR_ERR macro code
	exitm<MAKE_DWRITE_HR(SEVERITY_ERROR, code)>
	endm

.pragma pack(pop)

endif
