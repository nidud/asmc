ifndef DWRITE_3_H_INCLUDED
define DWRITE_3_H_INCLUDED
.pragma list(push, 0)
include dwrite_2.inc
include d2d1.inc

ifndef DWRITE_E_REMOTEFONT
define DWRITE_E_REMOTEFONT 0x8898500D
endif
ifndef DWRITE_E_DOWNLOADCANCELLED
define DWRITE_E_DOWNLOADCANCELLED 0x8898500E
endif
ifndef DWRITE_E_DOWNLOADFAILED
define DWRITE_E_DOWNLOADFAILED 0x8898500F
endif
ifndef DWRITE_E_TOOMANYDOWNLOADS
define DWRITE_E_TOOMANYDOWNLOADS 0x88985010
endif

.enum DWRITE_FONT_PROPERTY_ID {
    DWRITE_FONT_PROPERTY_ID_NONE,
    DWRITE_FONT_PROPERTY_ID_WEIGHT_STRETCH_STYLE_FAMILY_NAME,
    DWRITE_FONT_PROPERTY_ID_TYPOGRAPHIC_FAMILY_NAME,
    DWRITE_FONT_PROPERTY_ID_WEIGHT_STRETCH_STYLE_FACE_NAME,
    DWRITE_FONT_PROPERTY_ID_FULL_NAME,
    DWRITE_FONT_PROPERTY_ID_WIN32_FAMILY_NAME,
    DWRITE_FONT_PROPERTY_ID_POSTSCRIPT_NAME,
    DWRITE_FONT_PROPERTY_ID_DESIGN_SCRIPT_LANGUAGE_TAG,
    DWRITE_FONT_PROPERTY_ID_SUPPORTED_SCRIPT_LANGUAGE_TAG,
    DWRITE_FONT_PROPERTY_ID_SEMANTIC_TAG,
    DWRITE_FONT_PROPERTY_ID_WEIGHT,
    DWRITE_FONT_PROPERTY_ID_STRETCH,
    DWRITE_FONT_PROPERTY_ID_STYLE,
    DWRITE_FONT_PROPERTY_ID_TYPOGRAPHIC_FACE_NAME,
    DWRITE_FONT_PROPERTY_ID_TOTAL = DWRITE_FONT_PROPERTY_ID_STYLE + 1,
    DWRITE_FONT_PROPERTY_ID_TOTAL_RS3 = DWRITE_FONT_PROPERTY_ID_TYPOGRAPHIC_FACE_NAME + 1,
    DWRITE_FONT_PROPERTY_ID_PREFERRED_FAMILY_NAME = DWRITE_FONT_PROPERTY_ID_TYPOGRAPHIC_FAMILY_NAME,
    DWRITE_FONT_PROPERTY_ID_FAMILY_NAME = DWRITE_FONT_PROPERTY_ID_WEIGHT_STRETCH_STYLE_FAMILY_NAME,
    DWRITE_FONT_PROPERTY_ID_FACE_NAME = DWRITE_FONT_PROPERTY_ID_WEIGHT_STRETCH_STYLE_FACE_NAME,
    }


DWRITE_FONT_PROPERTY	STRUC
propertyId		DWRITE_FONT_PROPERTY_ID ?
propertyValue		LPWSTR ?
localeName		LPWSTR ?
DWRITE_FONT_PROPERTY	ENDS


.enum DWRITE_LOCALITY {
    DWRITE_LOCALITY_REMOTE,
    DWRITE_LOCALITY_PARTIAL,
    DWRITE_LOCALITY_LOCAL,
    }


.enum DWRITE_RENDERING_MODE1 {
    DWRITE_RENDERING_MODE1_DEFAULT = DWRITE_RENDERING_MODE_DEFAULT,
    DWRITE_RENDERING_MODE1_ALIASED = DWRITE_RENDERING_MODE_ALIASED,
    DWRITE_RENDERING_MODE1_GDI_CLASSIC = DWRITE_RENDERING_MODE_GDI_CLASSIC,
    DWRITE_RENDERING_MODE1_GDI_NATURAL = DWRITE_RENDERING_MODE_GDI_NATURAL,
    DWRITE_RENDERING_MODE1_NATURAL = DWRITE_RENDERING_MODE_NATURAL,
    DWRITE_RENDERING_MODE1_NATURAL_SYMMETRIC = DWRITE_RENDERING_MODE_NATURAL_SYMMETRIC,
    DWRITE_RENDERING_MODE1_OUTLINE = DWRITE_RENDERING_MODE_OUTLINE,
    DWRITE_RENDERING_MODE1_NATURAL_SYMMETRIC_DOWNSAMPLED,
    }


DEFINE_IIDX(IDWriteRenderingParams3, "B7924BAA-391B-412A-8C5C-E44CC2D867DC")

.comdef IDWriteRenderingParams3 : public IDWriteRenderingParams2

     GetRenderingMode1	proc
    .ENDS

DEFINE_IIDX(IDWriteFactory3, "9A1B41C3-D3BB-466A-87FC-FE67556A3B65")

.comdef IDWriteFactory3 : public IDWriteFactory2

    CreateGlyphRunAnalysis3		proc :ptr, :ptr, :DWRITE_RENDERING_MODE1, :DWRITE_MEASURING_MODE, :DWRITE_GRID_FIT_MODE, :DWRITE_TEXT_ANTIALIAS_MODE, :FLOAT, :FLOAT, :ptr
    CreateCustomRenderingParams3	proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :DWRITE_PIXEL_GEOMETRY, :DWRITE_RENDERING_MODE1, :DWRITE_GRID_FIT_MODE, :ptr
    CreateFontFaceReference?		proc :ptr, :ptr, :UINT32, :DWRITE_FONT_SIMULATIONS, :ptr
    CreateFontFaceReference		proc :ptr, :UINT32, :DWRITE_FONT_SIMULATIONS, :ptr
    GetSystemFontSet			proc :ptr
    CreateFontSetBuilder		proc :ptr
    CreateFontCollectionFromFontSet	proc :ptr, :ptr
    GetSystemFontCollection3		proc :BOOL, :ptr, :BOOL
    GetFontDownloadQueue		proc :ptr
   .ENDS


DEFINE_IIDX(IDWriteFontSet, "53585141-D9F8-4095-8321-D73CF6BD116B")

.comdef IDWriteFontSet : public IUnknown

    GetFontCount		proc
    GetFontFaceReference	proc :UINT32, :ptr
    FindFontFaceReference	proc :ptr, :ptr, :ptr
    FindFontFace		proc :ptr, :ptr, :ptr
    GetPropertyValues		proc :DWRITE_FONT_PROPERTY_ID, :ptr
    GetPropertyValues_2		proc :DWRITE_FONT_PROPERTY_ID, :ptr, :ptr
    GetPropertyValues_3		proc :UINT32, :DWRITE_FONT_PROPERTY_ID, :ptr, :ptr
    GetPropertyOccurrenceCount	proc :ptr, :ptr
    GetMatchingFonts		proc :ptr, :DWRITE_FONT_WEIGHT, :DWRITE_FONT_STRETCH, :DWRITE_FONT_STYLE, :ptr
    GetMatchingFonts_2		proc :ptr, :UINT32, :ptr
   .ENDS


DEFINE_IIDX(IDWriteFontSetBuilder, "2F642AFE-9C68-4F40-B8BE-457401AFCB3D")

.comdef IDWriteFontSetBuilder : public IUnknown

    AddFontFaceReference	proc :ptr
    AddFontFaceReference2	proc :ptr, :UINT32
    AddFontSet			proc :ptr
    CreateFontSet		proc :ptr
   .ENDS


DEFINE_IIDX(IDWriteFontCollection1, "53585141-D9F8-4095-8321-D73CF6BD116C")

.comdef IDWriteFontCollection1 : public IDWriteFontCollection

    GetFontSet		proc :ptr
    GetFontFamily1	proc :UINT32, :ptr
   .ENDS


DEFINE_IIDX(IDWriteFontFamily1, "DA20D8EF-812A-4C43-9802-62EC4ABD7ADF")

.comdef IDWriteFontFamily1 : public IDWriteFontFamily

    GetFontLocality		proc :UINT32
    GetFont1			proc :UINT32, :ptr
    GetFontFaceReference	proc :UINT32, :ptr
   .ENDS


DEFINE_IIDX(IDWriteFontList1, "DA20D8EF-812A-4C43-9802-62EC4ABD7ADE")

.comdef IDWriteFontList1 : public IDWriteFontList

    GetFontLocality		proc :UINT32
    GetFont1			proc :UINT32, :ptr
    GetFontFaceReference	proc :UINT32, :ptr
   .ENDS


DEFINE_IIDX(IDWriteFontFaceReference, "5E7FA7CA-DDE3-424C-89F0-9FCD6FED58CD")

.comdef IDWriteFontFaceReference : public IUnknown

    CreateFontFace			proc :ptr
    CreateFontFaceWithSimulations	proc :DWRITE_FONT_SIMULATIONS, :ptr
    Equals				proc :ptr
    GetFontFaceIndex			proc
    GetSimulations			proc
    GetFontFile				proc :ptr
    GetLocalFileSize			proc
    GetFileSize				proc
    GetFileTime				proc :ptr
    GetLocality				proc
    EnqueueFontDownloadRequest		proc
    EnqueueCharacterDownloadRequest	proc :UINT32
    EnqueueGlyphDownloadRequest		proc :UINT32
    EnqueueFileFragmentDownloadRequest	proc :UINT64, :UINT64
   .ENDS


DEFINE_IIDX(IDWriteFont3, "29748ED6-8C9C-4A6A-BE0B-D912E8538944")

.comdef IDWriteFont3 : public IDWriteFont2

    CreateFontFace3		proc :ptr
    Equals			proc :ptr
    GetFontFaceReference	proc :ptr
    HasCharacter3		proc :UINT32
    GetLocality			proc
   .ENDS


DEFINE_IIDX(IDWriteFontFace3, "D37D7598-09BE-4222-A236-2081341CC1F2")

.comdef IDWriteFontFace3 : public IDWriteFontFace2

    GetFontFaceReference	proc :ptr
    GetPanose			proc :ptr
    GetWeight			proc
    GetStretch			proc
    GetStyle			proc
    GetFamilyNames		proc :ptr
    GetFaceNames		proc :ptr
    GetInformationalStrings	proc :DWRITE_INFORMATIONAL_STRING_ID, :ptr, :ptr
    HasCharacter		proc :UINT32
    GetRecommendedRenderingMode3 proc :FLOAT, :FLOAT, :FLOAT, :ptr, :BOOL, :DWRITE_OUTLINE_THRESHOLD, :DWRITE_MEASURING_MODE, :ptr, :ptr, :ptr
    IsCharacterLocal		proc :UINT32
    IsGlyphLocal		proc :UINT16
    AreCharactersLocal		proc :UINT32, :BOOL, :ptr
    AreGlyphsLocal		proc :UINT32, :BOOL, :ptr
   .ENDS


DEFINE_IIDX(IDWriteStringList, "CFEE3140-1157-47CA-8B85-31BFCF3F2D0E")

.comdef IDWriteStringList : public IUnknown

    GetCount		proc
    GetLocaleNameLength proc :UINT32, :ptr
    GetLocaleName	proc :UINT32, :ptr, :UINT32
    GetStringLength	proc :UINT32, :ptr
    GetString		proc :UINT32, :ptr, :UINT32
   .ENDS


DEFINE_IIDX(IDWriteFontDownloadListener, "B06FE5B9-43EC-4393-881B-DBE4DC72FDA7")

.comdef IDWriteFontDownloadListener : public IUnknown

     DownloadCompleted	proc :ptr, :ptr, :HRESULT
    .ENDS


DEFINE_IIDX(IDWriteFontDownloadQueue, "B71E6052-5AEA-4FA3-832E-F60D431F7E91")

.comdef IDWriteFontDownloadQueue : public IUnknown

    AddListener		proc :ptr, :ptr
    RemoveListener	proc :UINT32
    IsEmpty		proc
    BeginDownload	proc :ptr
    CancelDownload	proc
    GetGenerationCount	proc
   .ENDS

DEFINE_IIDX(IDWriteGdiInterop1, "4556BE70-3ABD-4F70-90BE-421780A6F515")

.comdef IDWriteGdiInterop1 : public IDWriteGdiInterop

    CreateFontFromLOGFONT1	proc :ptr, :ptr, :ptr
    GetFontSignature		proc :ptr, :ptr
    GetFontSignature_2		proc :ptr, :ptr
    GetMatchingFontsByLOGFONT	proc :ptr, :ptr, :ptr
   .ENDS

.template DWRITE_LINE_METRICS1 : public DWRITE_LINE_METRICS

    leadingBefore	FLOAT ?
    leadingAfter	FLOAT ?
   .ENDS

.enum DWRITE_FONT_LINE_GAP_USAGE {
    DWRITE_FONT_LINE_GAP_USAGE_DEFAULT,
    DWRITE_FONT_LINE_GAP_USAGE_DISABLED,
    DWRITE_FONT_LINE_GAP_USAGE_ENABLED
    }

DWRITE_LINE_SPACING	STRUC
method			DWRITE_LINE_SPACING_METHOD ?
height			FLOAT ?
baseline		FLOAT ?
leadingBefore		FLOAT ?
fontLineGapUsage	DWRITE_FONT_LINE_GAP_USAGE ?
DWRITE_LINE_SPACING	ENDS


DEFINE_IIDX(IDWriteTextFormat2, "F67E0EDD-9E3D-4ECC-8C32-4183253DFE70")

.comdef IDWriteTextFormat2 : public IDWriteTextFormat1

    SetLineSpacing2	proc :ptr
    GetLineSpacing2	proc :ptr
   .ENDS

DEFINE_IIDX(IDWriteTextLayout3, "07DDCD52-020E-4DE8-AC33-6C953D83F92D")

.comdef IDWriteTextLayout3 : public IDWriteTextLayout2

    InvalidateLayout	proc
    SetLineSpacing3	proc :ptr
    GetLineSpacing3	proc :ptr
    GetLineMetrics3	proc :UINT32, :ptr
   .ENDS


if NTDDI_VERSION GE NTDDI_WIN10_RS1


;.template DWRITE_COLOR_GLYPH_RUN1 : public DWRITE_COLOR_GLYPH_RUN
;    glyphImageFormat	DWRITE_GLYPH_IMAGE_FORMATS ?
;    measuringMode	DWRITE_MEASURING_MODE ?
;.ENDS

D2D1_POINT_2L typedef POINT

DWRITE_GLYPH_IMAGE_DATA STRUC
imageData		PVOID ?
imageDataSize		UINT32 ?
uniqueDataId		UINT32 ?
pixelsPerEm		UINT32 ?
pixelSize		D2D1_SIZE_U <>
horizontalLeftOrigin	D2D1_POINT_2L <>
horizontalRightOrigin	D2D1_POINT_2L <>
verticalTopOrigin	D2D1_POINT_2L <>
verticalBottomOrigin	D2D1_POINT_2L <>
DWRITE_GLYPH_IMAGE_DATA ENDS


DEFINE_IIDX(IDWriteColorGlyphRunEnumerator1, "7C5F86DA-C7A1-4F05-B8E1-55A179FE5A35")

.comdef IDWriteColorGlyphRunEnumerator1 : public IDWriteColorGlyphRunEnumerator

    GetCurrentRun1	proc :ptr
    .ENDS


DEFINE_IIDX(IDWriteFontFace4, "27F2A904-4EB8-441D-9678-0563F53E3E2F")

.comdef IDWriteFontFace4 : public IDWriteFontFace3

    GetGlyphImageFormats	proc
    GetGlyphImageFormats_2	proc :UINT16, :UINT32, :UINT32, :ptr
    GetGlyphImageData		proc :UINT16, :UINT32, :DWRITE_GLYPH_IMAGE_FORMATS, :ptr, :ptr
    ReleaseGlyphImageData	proc :ptr
   .ENDS

DEFINE_IIDX(IDWriteFactory4, "4B0B5BD3-0797-4549-8AC5-FE915CC53856")

.comdef IDWriteFactory4 : public IDWriteFactory3

    TranslateColorGlyphRun4	proc :D2D1_POINT_2F, :ptr, :ptr, :DWRITE_GLYPH_IMAGE_FORMATS, :DWRITE_MEASURING_MODE, :ptr, :UINT32, :ptr
    ComputeGlyphOrigins		proc :ptr, :DWRITE_MEASURING_MODE, :D2D1_POINT_2F, :ptr
    ComputeGlyphOrigins_2	proc :ptr, :D2D1_POINT_2F
   .ENDS

endif

if NTDDI_VERSION GE NTDDI_WIN10_RS2

DEFINE_IIDX(IDWriteFontSetBuilder1, "3FF7715F-3CDC-4DC6-9B72-EC5621DCCAFD")

.comdef IDWriteFontSetBuilder1 : public IDWriteFontSetBuilder

    AddFontFile		proc :ptr
   .ENDS

DEFINE_IIDX(IDWriteAsyncResult, "CE25F8FD-863B-4D13-9651-C1F88DC73FE2")

.comdef IDWriteAsyncResult : public IUnknown

    GetWaitHandle	proc
    GetResult		proc
   .ENDS


DWRITE_FILE_FRAGMENT	STRUC
fileOffset		UINT64 ?
fragmentSize		UINT64 ?
DWRITE_FILE_FRAGMENT	ENDS


DEFINE_IIDX(IDWriteRemoteFontFileStream, "4DB3757A-2C72-4ED9-B2B6-1ABABE1AFF9C")

.comdef IDWriteRemoteFontFileStream : public IDWriteFontFileStream

    GetLocalFileSize		proc :ptr
    GetFileFragmentLocality	proc :UINT64, :UINT64, :ptr
    GetLocality			proc
    BeginDownload		proc :ptr, :UINT32, :ptr
   .ENDS


.enum DWRITE_CONTAINER_TYPE {
    DWRITE_CONTAINER_TYPE_UNKNOWN,
    DWRITE_CONTAINER_TYPE_WOFF,
    DWRITE_CONTAINER_TYPE_WOFF2
    }


DEFINE_IIDX(IDWriteRemoteFontFileLoader, "68648C83-6EDE-46C0-AB46-20083A887FDE")

.comdef IDWriteRemoteFontFileLoader : public IDWriteFontFileLoader

    CreateRemoteStreamFromKey		proc :UINT32, :ptr
    GetLocalityFromKey			proc :UINT32, :ptr
    CreateFontFileReferenceFromUrl	proc :ptr, :ptr, :ptr, :ptr
   .ENDS


DEFINE_IIDX(IDWriteInMemoryFontFileLoader, "DC102F47-A12D-4B1C-822D-9E117E33043F")

.comdef IDWriteInMemoryFontFileLoader : public IDWriteFontFileLoader

    CreateInMemoryFontFileReference	proc :ptr, :UINT32, :ptr, :ptr
    GetFileCount			proc
   .ENDS


DEFINE_IIDX(IDWriteFactory5, "958DB99A-BE2A-4F09-AF7D-65189803D1D3")

.comdef IDWriteFactory5 : public IDWriteFactory4

    CreateFontSetBuilder5	    proc :ptr
    CreateInMemoryFontFileLoader    proc :ptr
    CreateHttpFontFileLoader	    proc :ptr, :ptr, :ptr
    AnalyzeContainerType	    proc :UINT32
    UnpackFontFile		    proc :DWRITE_CONTAINER_TYPE, :UINT32, :ptr
   .ends

endif

if NTDDI_VERSION GE NTDDI_WIN10_RS3

DWRITE_MAKE_FONT_AXIS_TAG macro a,b,c,d
	exitm<DWRITE_MAKE_OPENTYPE_TAG(a,b,c,d)>
	endm


.enum DWRITE_FONT_AXIS_TAG : UINT32 {
    DWRITE_FONT_AXIS_TAG_WEIGHT		= DWRITE_MAKE_FONT_AXIS_TAG('w','g','h','t'),
    DWRITE_FONT_AXIS_TAG_WIDTH		= DWRITE_MAKE_FONT_AXIS_TAG('w','d','t','h'),
    DWRITE_FONT_AXIS_TAG_SLANT		= DWRITE_MAKE_FONT_AXIS_TAG('s','l','n','t'),
    DWRITE_FONT_AXIS_TAG_OPTICAL_SIZE	= DWRITE_MAKE_FONT_AXIS_TAG('o','p','s','z'),
    DWRITE_FONT_AXIS_TAG_ITALIC		= DWRITE_MAKE_FONT_AXIS_TAG('i','t','a','l'),
    }


DWRITE_FONT_AXIS_VALUE	STRUC
axisTag			DWRITE_FONT_AXIS_TAG ?
value			FLOAT ?
DWRITE_FONT_AXIS_VALUE	ENDS


DWRITE_FONT_AXIS_RANGE	STRUC
axisTag			DWRITE_FONT_AXIS_TAG ?
minValue		FLOAT ?
maxValue		FLOAT ?
DWRITE_FONT_AXIS_RANGE	ENDS


.enum DWRITE_FONT_FAMILY_MODEL {
    DWRITE_FONT_FAMILY_MODEL_TYPOGRAPHIC,
    DWRITE_FONT_FAMILY_MODEL_WEIGHT_STRETCH_STYLE,
    }


.enum DWRITE_AUTOMATIC_FONT_AXES {
    DWRITE_AUTOMATIC_FONT_AXES_NONE	    = 0x0000,
    DWRITE_AUTOMATIC_FONT_AXES_OPTICAL_SIZE = 0x0001,
    }

.enum DWRITE_FONT_AXIS_ATTRIBUTES {
    DWRITE_FONT_AXIS_ATTRIBUTES_NONE	 = 0x0000,
    DWRITE_FONT_AXIS_ATTRIBUTES_VARIABLE = 0x0001,
    DWRITE_FONT_AXIS_ATTRIBUTES_HIDDEN	 = 0x0002,
    }


DEFINE_IIDX(IDWriteFactory6, "F3744D80-21F7-42EB-B35D-995BC72FC223")

.comdef IDWriteFactory6 : public IDWriteFactory5

    CreateFontFaceReference6		proc :ptr, :UINT32, :DWRITE_FONT_SIMULATIONS, :UINT32, :ptr
    CreateFontResource			proc :ptr, :UINT32, :ptr
    GetSystemFontSet6			proc :BOOL, :ptr
    GetSystemFontCollection6		proc :BOOL, :DWRITE_FONT_FAMILY_MODEL, :ptr
    CreateFontCollectionFromFontSet6	proc :ptr, :DWRITE_FONT_FAMILY_MODEL, :ptr
    CreateFontSetBuilder6		proc :ptr
    CreateTextFormat6			proc :ptr, :ptr, :UINT32, :FLOAT, :ptr, :ptr
   .ENDS


DEFINE_IIDX(IDWriteFontFace5, "98EFF3A5-B667-479A-B145-E2FA5B9FDC29")

.comdef IDWriteFontFace5 : public IDWriteFontFace4

    GetFontAxisValueCount	proc
    GetFontAxisValues		proc :UINT32
    HasVariations		proc
    GetFontResource		proc :ptr
    Equals			proc :ptr
   .ENDS

DEFINE_IIDX(IDWriteFontResource, "1F803A76-6871-48E8-987F-B975551C50F2")

.comdef IDWriteFontResource : public IUnknown

    GetFontFile			proc :ptr
    GetFontFaceIndex		proc
    GetFontAxisCount		proc
    GetDefaultFontAxisValues	proc :UINT32
    GetFontAxisRanges		proc :UINT32
    GetFontAxisAttributes	proc :UINT32
    GetAxisNames		proc :UINT32, :ptr
    GetAxisValueNameCount	proc :UINT32
    GetAxisValueNames		proc :UINT32, :UINT32, :ptr, :ptr
    HasVariations		proc
    CreateFontFace		proc :DWRITE_FONT_SIMULATIONS, :UINT32, ptr ptr IDWriteFontFace5
    CreateFontFaceReference	proc :DWRITE_FONT_SIMULATIONS, :UINT32, :ptr
   .ENDS


DEFINE_IIDX(IDWriteFontFaceReference1, "C081FE77-2FD1-41AC-A5A3-34983C4BA61A")

.comdef IDWriteFontFaceReference1 : public IDWriteFontFaceReference

    CreateFontFace1		proc :ptr
    GetFontAxisValueCount	proc
    GetFontAxisValues		proc :UINT32
   .ENDS


DEFINE_IIDX(IDWriteFontSetBuilder2, "EE5BA612-B131-463C-8F4F-3189B9401E45")

.comdef IDWriteFontSetBuilder2 : public IDWriteFontSetBuilder1

    AddFont		proc :ptr, :UINT32, :DWRITE_FONT_SIMULATIONS, :UINT32, :ptr, :UINT32, :ptr, :UINT32
    AddFontFile2	proc :ptr
   .ENDS

DEFINE_IIDX(IDWriteFontSet1, "7E9FDA85-6C92-4053-BC47-7AE3530DB4D3")

.comdef IDWriteFontSet1 : public IDWriteFontSet

    GetMatchingFonts1		proc :ptr, :ptr, :UINT32, :ptr
    GetFirstFontResources	proc :ptr
    GetFilteredFonts		proc :UINT32, :BOOL, :ptr
    GetFilteredFonts_2		proc :UINT32, :BOOL, :ptr
    GetFilteredFonts_3		proc :UINT32, :ptr
    GetFilteredFontIndices	proc :UINT32, :BOOL, :ptr, :UINT32, :ptr
    GetFilteredFontIndices_2	proc :UINT32, :BOOL, :ptr, :UINT32, :ptr
    GetFontAxisRanges		proc :UINT32, :ptr
    GetFontAxisRanges_2		proc :UINT32, :UINT32, :ptr
    GetFontFaceReference1	proc :UINT32, :ptr
    CreateFontResource		proc :UINT32, :ptr
    CreateFontFace		proc :UINT32, :ptr
    GetFontLocality		proc :UINT32
   .ENDS


DEFINE_IIDX(IDWriteFontList2, "C0763A34-77AF-445A-B735-08C37B0A5BF5")

.comdef IDWriteFontList2 : public IDWriteFontList1

    GetFontSet		proc :ptr
   .ENDS


DEFINE_IIDX(IDWriteFontFamily2, "3ED49E77-A398-4261-B9CF-C126C2131EF3")

.comdef IDWriteFontFamily2 : public IDWriteFontFamily1

    GetMatchingFonts2	proc :UINT32, :ptr
    GetFontSet		proc :ptr
   .ENDS


DEFINE_IIDX(IDWriteFontCollection2, "514039C6-4617-4064-BF8B-92EA83E506E0")

.comdef IDWriteFontCollection2 : public IDWriteFontCollection1

    GetFontFamily2	proc :UINT32, :ptr
    GetMatchingFonts	proc :ptr, :UINT32, :ptr
    GetFontFamilyModel	proc
    GetFontSet2		proc :ptr
   .ENDS


DEFINE_IIDX(IDWriteTextLayout4, "05A9BF42-223F-4441-B5FB-8263685F55E9")

.comdef IDWriteTextLayout4 : public IDWriteTextLayout3

    SetFontAxisValues		proc :UINT32, :DWRITE_TEXT_RANGE
    GetFontAxisValueCount	proc :UINT32
    GetFontAxisValues		proc :UINT32, :UINT32, :ptr
    GetAutomaticFontAxes	proc
    SetAutomaticFontAxes	proc :DWRITE_AUTOMATIC_FONT_AXES
   .ENDS


DEFINE_IIDX(IDWriteTextFormat3, "6D3B5641-E550-430D-A85B-B7BF48A93427")

.comdef IDWriteTextFormat3 : public IDWriteTextFormat2

    SetFontAxisValues		proc :ptr, :UINT32
    GetFontAxisValueCount	proc
    GetFontAxisValues		proc :ptr, :UINT32
    GetAutomaticFontAxes	proc
    SetAutomaticFontAxes	proc :DWRITE_AUTOMATIC_FONT_AXES
   .ENDS


DEFINE_IIDX(IDWriteFontFallback1, "2397599D-DD0D-4681-BD6A-F4F31EAADE77")

.comdef IDWriteFontFallback1 : public IDWriteFontFallback

    MapCharacters1	proc :ptr, :UINT32, :UINT32, :ptr, :ptr, :UINT32, :ptr, :ptr, :ptr
   .ENDS

endif

if NTDDI_VERSION GE NTDDI_WIN10_RS4

DEFINE_IIDX(IDWriteFontSet2, "DC7EAD19-E54C-43AF-B2DA-4E2B79BA3F7F")

.comdef IDWriteFontSet2 : public IDWriteFontSet1

    GetExpirationEvent	proc
   .ENDS


DEFINE_IIDX(IDWriteFontCollection3, "A4D055A6-F9E3-4E25-93B7-9E309F3AF8E9")

.comdef IDWriteFontCollection3 : public IDWriteFontCollection2

    GetExpirationEvent	proc
   .ENDS

DEFINE_IIDX(IDWriteFactory7, "35D0E0B3-9076-4D2E-A016-A91B568A06B4")

.comdef IDWriteFactory7 : public IDWriteFactory6

    GetSystemFontSet7		proc :BOOL, :ptr
    GetSystemFontCollection7	proc :BOOL, :DWRITE_FONT_FAMILY_MODEL, :ptr
   .ENDS

endif

if NTDDI_VERSION GE NTDDI_WIN10_RS5

.enum DWRITE_FONT_SOURCE_TYPE {
    DWRITE_FONT_SOURCE_TYPE_UNKNOWN,
    DWRITE_FONT_SOURCE_TYPE_PER_MACHINE,
    DWRITE_FONT_SOURCE_TYPE_PER_USER,
    DWRITE_FONT_SOURCE_TYPE_APPX_PACKAGE,
    DWRITE_FONT_SOURCE_TYPE_REMOTE_FONT_PROVIDER
    }


DEFINE_IIDX(IDWriteFontSet3, "7C073EF2-A7F4-4045-8C32-8AB8AE640F90")

.comdef IDWriteFontSet3 : public IDWriteFontSet2

    GetFontSourceType		proc :UINT32
    GetFontSourceNameLength	proc :UINT32
    GetFontSourceName		proc :UINT32, :UINT32
   .ENDS

endif

if NTDDI_VERSION ge NTDDI_WIN10_MN

DEFINE_IIDX(IDWriteFontFace6, "C4B1FE1B-6E84-47D5-B54C-A597981B06AD")

.comdef IDWriteFontFace6 : public IDWriteFontFace5

    GetFamilyNames6	proc :DWRITE_FONT_FAMILY_MODEL, :ptr ptr
    GetFaceNames6	proc :DWRITE_FONT_FAMILY_MODEL, :ptr ptr
   .ends

endif
.pragma list(pop)
endif
