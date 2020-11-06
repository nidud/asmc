ifndef DWRITE_2_H_INCLUDED
DWRITE_2_H_INCLUDED equ <>

include dwrite_1.inc

.enum DWRITE_OPTICAL_ALIGNMENT {
    DWRITE_OPTICAL_ALIGNMENT_NONE,
    DWRITE_OPTICAL_ALIGNMENT_NO_SIDE_BEARINGS,
    }

.enum DWRITE_GRID_FIT_MODE {
    DWRITE_GRID_FIT_MODE_DEFAULT,
    DWRITE_GRID_FIT_MODE_DISABLED,
    DWRITE_GRID_FIT_MODE_ENABLED
    }

.template DWRITE_TEXT_METRICS1 : DWRITE_TEXT_METRICS STRUC
    heightIncludingTrailingWhitespace FLOAT ?
    .ENDS


DEFINE_IIDX(IDWriteTextRenderer1, "D3E0E934-22A0-427E-AAE4-7D9574B59DB1")

.comdef IDWriteTextRenderer1 : public IDWriteTextRenderer

    DrawGlyphRun2	proc :ptr, :FLOAT, :FLOAT, :DWRITE_GLYPH_ORIENTATION_ANGLE, :DWRITE_MEASURING_MODE, :ptr DWRITE_GLYPH_RUN, :ptr DWRITE_GLYPH_RUN_DESCRIPTION, :ptr IUnknown
    DrawUnderline2	proc :ptr, :FLOAT, :FLOAT, :DWRITE_GLYPH_ORIENTATION_ANGLE, :ptr DWRITE_UNDERLINE, :ptr IUnknown
    DrawStrikethrough2	proc :ptr, :FLOAT, :FLOAT, :DWRITE_GLYPH_ORIENTATION_ANGLE, :ptr DWRITE_STRIKETHROUGH, :ptr IUnknown
    DrawInlineObject2	proc :ptr, :FLOAT, :FLOAT, :DWRITE_GLYPH_ORIENTATION_ANGLE, :ptr IDWriteInlineObject, :BOOL, :BOOL, :ptr IUnknown
    .ENDS


DEFINE_IIDX(IDWriteTextFormat1, "5F174B49-0D8B-4CFB-8BCA-F1CCE9D06C67")

.comdef IDWriteTextFormat1 : public IDWriteTextFormat

    SetVerticalGlyphOrientation proc :DWRITE_VERTICAL_GLYPH_ORIENTATION
    GetVerticalGlyphOrientation proc
    SetLastLineWrapping proc :BOOL
    GetLastLineWrapping proc
    SetOpticalAlignment proc :DWRITE_OPTICAL_ALIGNMENT
    GetOpticalAlignment proc
    SetFontFallback	proc :ptr IDWriteFontFallback
    GetFontFallback	proc :ptr ptr IDWriteFontFallback
    .ENDS


DEFINE_IIDX(IDWriteTextLayout2, "1093C18F-8D5E-43F0-B064-0917311B525E")

.comdef IDWriteTextLayout2 : public IDWriteTextLayout1

    GetMetrics2		proc :ptr DWRITE_TEXT_METRICS1
    SetVerticalGlyphOrientation proc :DWRITE_VERTICAL_GLYPH_ORIENTATION
    GetVerticalGlyphOrientation proc
    SetLastLineWrapping proc :BOOL
    GetLastLineWrapping proc
    SetOpticalAlignment proc :DWRITE_OPTICAL_ALIGNMENT
    GetOpticalAlignment proc
    SetFontFallback	proc :ptr IDWriteFontFallback
    GetFontFallback	proc :ptr ptr IDWriteFontFallback
    .ENDS


DEFINE_IIDX(IDWriteTextAnalyzer2, "553A9FF3-5693-4DF7-B52B-74806F7F2EB9")

.comdef IDWriteTextAnalyzer2 : public IDWriteTextAnalyzer1

    GetGlyphOrientationTransform2 proc :DWRITE_GLYPH_ORIENTATION_ANGLE, :BOOL, :FLOAT, :FLOAT, :ptr DWRITE_MATRIX
    GetTypographicFeatures proc :ptr IDWriteFontFace, :DWRITE_SCRIPT_ANALYSIS, :ptr WCHAR, :UINT32, :ptr UINT32
    CheckTypographicFeature proc :ptr IDWriteFontFace, :DWRITE_SCRIPT_ANALYSIS, :ptr WCHAR, :DWRITE_FONT_FEATURE_TAG, :UINT32
    .ENDS


DEFINE_IIDX(IDWriteFontFallback, "EFA008F9-F7A1-48BF-B05C-F224713CC0FF")

.comdef IDWriteFontFallback : public IUnknown

    MapCharacters proc :ptr IDWriteTextAnalysisSource, :UINT32, :UINT32,
	:ptr IDWriteFontCollection, :ptr wchar_t, :DWRITE_FONT_WEIGHT, :DWRITE_FONT_STYLE,
	:DWRITE_FONT_STRETCH, :ptr ptr IDWriteFont, :ptr FLOAT
    .ENDS


DEFINE_IIDX(IDWriteFontFallbackBuilder, "FD882D06-8ABA-4FB8-B849-8BE8B73E14DE")

.comdef IDWriteFontFallbackBuilder : public IUnknown

    AddMapping proc :UINT32, :ptr ptr WCHAR, :UINT32, :ptr IDWriteFontCollection, :ptr WCHAR, :ptr WCHAR, :FLOAT
    AddMappings proc :ptr IDWriteFontFallback
    CreateFontFallback proc :ptr ptr IDWriteFontFallback
    .ENDS

ifndef D3DCOLORVALUE_DEFINED

D3DCOLORVALUE		STRUC
UNION ; {
r			FLOAT ?
dvR			FLOAT ?
ENDS ;
UNION ; {
g			FLOAT ?
dvG			FLOAT ?
ENDS ;
UNION ; {
b			FLOAT ?
dvB			FLOAT ?
ENDS ;
UNION ; {
a			FLOAT ?
dvA			FLOAT ?
ENDS ;
D3DCOLORVALUE		ENDS

D3DCOLORVALUE_DEFINED equ 1
endif

DWRITE_COLOR_F		typedef D3DCOLORVALUE

DEFINE_IIDX(IDWriteFont2, "29748ed6-8c9c-4a6a-be0b-d912e8538944")

.comdef IDWriteFont2 : public IDWriteFont1

     IsColorFont	proc
     .ENDS

DEFINE_IIDX(IDWriteFontFace2, "d8b768ff-64bc-4e66-982b-ec8e87f693f7")

.comdef IDWriteFontFace2 : public IDWriteFontFace1

    IsColorFont proc
    GetColorPaletteCount proc
    GetPaletteEntryCount proc
    GetPaletteEntries	proc :UINT32, :UINT32, :UINT32
    ;GetRecommendedRenderingMode proc :FLOAT, :FLOAT, :FLOAT, :ptr DWRITE_MATRIX, :BOOL, :DWRITE_OUTLINE_THRESHOLD, :DWRITE_MEASURING_MODE, :ptr IDWriteRenderingParams, :ptr DWRITE_RENDERING_MODE, :ptr DWRITE_GRID_FIT_MODE
    .ENDS

DWRITE_COLOR_GLYPH_RUN	STRUC
glyphRun		DWRITE_GLYPH_RUN <>
glyphRunDescription	PVOID ? ; DWRITE_GLYPH_RUN_DESCRIPTION*
baselineOriginX		FLOAT ?
baselineOriginY		FLOAT ?
runColor		DWRITE_COLOR_F <>
paletteIndex		UINT16 ?
DWRITE_COLOR_GLYPH_RUN	ENDS


DEFINE_IIDX(IDWriteColorGlyphRunEnumerator, "d31fbe17-f157-41a2-8d24-cb779e0560e8")

.comdef IDWriteColorGlyphRunEnumerator : public IUnknown

    MoveNext		proc :ptr BOOL
    GetCurrentRun	proc :ptr ptr DWRITE_COLOR_GLYPH_RUN
    .ENDS

DEFINE_IIDX(IDWriteRenderingParams2, "F9D711C3-9777-40AE-87E8-3E5AF9BF0948")

.comdef IDWriteRenderingParams2 : public IDWriteRenderingParams1

     GetGridFitMode proc
     .ENDS


DEFINE_IIDX(IDWriteFactory2, "0439fc60-ca44-4994-8dee-3a9af7b732ec")

.comdef IDWriteFactory2 : public IDWriteFactory1

    GetSystemFontFallback proc :ptr ptr IDWriteFontFallback
    CreateFontFallbackBuilder proc :ptr ptr IDWriteFontFallbackBuilder
    TranslateColorGlyphRun proc :FLOAT, :FLOAT, :ptr DWRITE_GLYPH_RUN, :ptr DWRITE_GLYPH_RUN_DESCRIPTION, :DWRITE_MEASURING_MODE, :ptr DWRITE_MATRIX, :UINT32, :ptr ptr IDWriteColorGlyphRunEnumerator
    ;CreateCustomRenderingParams proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :DWRITE_PIXEL_GEOMETRY, :DWRITE_RENDERING_MODE, :DWRITE_GRID_FIT_MODE, :ptr ptr IDWriteRenderingParams2
    ;CreateGlyphRunAnalysis proc :ptr DWRITE_GLYPH_RUN, :ptr DWRITE_MATRIX, :DWRITE_RENDERING_MODE, :DWRITE_MEASURING_MODE, :DWRITE_GRID_FIT_MODE, :DWRITE_TEXT_ANTIALIAS_MODE, :FLOAT, :FLOAT, :ptr ptr IDWriteGlyphRunAnalysis
    .ENDS

endif
