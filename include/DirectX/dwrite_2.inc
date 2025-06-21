ifndef DWRITE_2_H_INCLUDED
define DWRITE_2_H_INCLUDED

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

.template DWRITE_TEXT_METRICS1 : public DWRITE_TEXT_METRICS
    heightIncludingTrailingWhitespace FLOAT ?
   .ENDS


DEFINE_IIDX(IDWriteTextRenderer1, "D3E0E934-22A0-427E-AAE4-7D9574B59DB1")

.comdef IDWriteTextRenderer1 : public IDWritePixelSnapping

    DrawGlyphRun0	proc :ptr, :FLOAT, :FLOAT, :DWRITE_MEASURING_MODE, :ptr, :ptr, :ptr
    DrawUnderline0	proc :ptr, :FLOAT, :FLOAT, :ptr, :ptr
    DrawStrikethrough0	proc :ptr, :FLOAT, :FLOAT, :ptr, :ptr
    DrawInlineObject0	proc :ptr, :FLOAT, :FLOAT, :ptr, :BOOL, :BOOL, :ptr

    DrawGlyphRun	proc :ptr, :FLOAT, :FLOAT, :DWRITE_GLYPH_ORIENTATION_ANGLE, :DWRITE_MEASURING_MODE, :ptr, :ptr, :ptr
    DrawUnderline	proc :ptr, :FLOAT, :FLOAT, :DWRITE_GLYPH_ORIENTATION_ANGLE, :ptr, :ptr
    DrawStrikethrough	proc :ptr, :FLOAT, :FLOAT, :DWRITE_GLYPH_ORIENTATION_ANGLE, :ptr, :ptr
    DrawInlineObject	proc :ptr, :FLOAT, :FLOAT, :DWRITE_GLYPH_ORIENTATION_ANGLE, :ptr, :BOOL, :BOOL, :ptr
    .ENDS


DEFINE_IIDX(IDWriteTextFormat1, "5F174B49-0D8B-4CFB-8BCA-F1CCE9D06C67")

.comdef IDWriteTextFormat1 : public IDWriteTextFormat

    SetVerticalGlyphOrientation proc :DWRITE_VERTICAL_GLYPH_ORIENTATION
    GetVerticalGlyphOrientation proc
    SetLastLineWrapping proc :BOOL
    GetLastLineWrapping proc
    SetOpticalAlignment proc :DWRITE_OPTICAL_ALIGNMENT
    GetOpticalAlignment proc
    SetFontFallback	proc :ptr
    GetFontFallback	proc :ptr
    .ENDS


DEFINE_IIDX(IDWriteTextLayout2, "1093C18F-8D5E-43F0-B064-0917311B525E")

.comdef IDWriteTextLayout2 : public IUnknown

    SetTextAlignment	proc :DWRITE_TEXT_ALIGNMENT
    SetParagraphAlignment proc :DWRITE_PARAGRAPH_ALIGNMENT
    SetWordWrapping	proc :DWRITE_WORD_WRAPPING
    SetReadingDirection proc :DWRITE_READING_DIRECTION
    SetFlowDirection	proc :DWRITE_FLOW_DIRECTION
    SetIncrementalTabStop proc :FLOAT
    SetTrimming		proc :ptr, :ptr
    SetLineSpacing	proc :DWRITE_LINE_SPACING_METHOD, :FLOAT, :FLOAT
    GetTextAlignment	proc
    GetParagraphAlignment proc
    GetWordWrapping	proc
    GetReadingDirection proc
    GetFlowDirection	proc
    GetIncrementalTabStop proc
    GetTrimming		proc :ptr, :ptr
    GetLineSpacing	proc :ptr, :ptr, :ptr
    GetFontCollection?	proc :ptr
    GetFontFamilyNameLength? proc
    GetFontFamilyName?	proc :UINT32
    GetFontWeight?	proc
    GetFontStyle?	proc
    GetFontStretch?	proc
    GetFontSize?	proc
    GetLocaleNameLength? proc
    GetLocaleName?	proc :UINT32

    SetMaxWidth		proc :FLOAT
    SetMaxHeight	proc :FLOAT
    SetFontCollection	proc :ptr, :DWRITE_TEXT_RANGE
    SetFontFamilyName	proc :ptr, :DWRITE_TEXT_RANGE
    SetFontWeight	proc :DWRITE_FONT_WEIGHT, :DWRITE_TEXT_RANGE
    SetFontStyle	proc :DWRITE_FONT_STYLE, :DWRITE_TEXT_RANGE
    SetFontStretch	proc :DWRITE_FONT_STRETCH, :DWRITE_TEXT_RANGE
    SetFontSize		proc :FLOAT, :DWRITE_TEXT_RANGE
    SetUnderline	proc :BOOL, :DWRITE_TEXT_RANGE
    SetStrikethrough	proc :BOOL, :DWRITE_TEXT_RANGE
    SetDrawingEffect	proc :ptr, :DWRITE_TEXT_RANGE
    SetInlineObject	proc :ptr, :DWRITE_TEXT_RANGE
    SetTypography	proc :ptr, :DWRITE_TEXT_RANGE
    SetLocaleName	proc :ptr, :DWRITE_TEXT_RANGE
    GetMaxWidth		proc
    GetMaxHeight	proc

    GetFontCollection	proc :UINT32, :ptr, :ptr
    GetFontFamilyNameLength proc :UINT32, :ptr, :ptr
    GetFontFamilyName	proc :UINT32, :UINT32, :ptr
    GetFontWeight	proc :UINT32, :ptr, :ptr
    GetFontStyle	proc :UINT32, :ptr, :ptr
    GetFontStretch	proc :UINT32, :ptr, :ptr
    GetFontSize		proc :UINT32, :ptr, :ptr

    GetUnderline	proc :UINT32, :ptr, :ptr
    GetStrikethrough	proc :UINT32, :ptr, :ptr
    GetDrawingEffect	proc :UINT32, :ptr, :ptr
    GetInlineObject	proc :UINT32, :ptr, :ptr
    GetTypography	proc :UINT32, :ptr, :ptr

    GetLocaleNameLength proc :UINT32, :ptr, :ptr
    GetLocaleName	proc :UINT32, :UINT32, :ptr
    Draw		proc :ptr, :ptr, :FLOAT, :FLOAT
    GetLineMetrics	proc :UINT32, :ptr
    GetMetrics?		proc :ptr
    GetOverhangMetrics	proc :ptr
    GetClusterMetrics	proc :UINT32, :ptr
    DetermineMinWidth	proc :ptr
    HitTestPoint	proc :FLOAT, :FLOAT, :ptr, :ptr, :ptr
    HitTestTextPosition proc :UINT32, :BOOL, :ptr, :ptr, :ptr
    HitTestTextRange	proc :UINT32, :UINT32, :FLOAT, :FLOAT, :UINT32, :ptr
; 1
    SetPairKerning	proc :BOOL, :DWRITE_TEXT_RANGE
    GetPairKerning	proc :UINT32, :ptr, :ptr
    SetCharacterSpacing proc :FLOAT, :FLOAT, :FLOAT, :DWRITE_TEXT_RANGE
    GetCharacterSpacing proc :UINT32, :ptr, :ptr, :ptr, :ptr
; 2
    GetMetrics		proc :ptr
    SetVerticalGlyphOrientation proc :DWRITE_VERTICAL_GLYPH_ORIENTATION
    GetVerticalGlyphOrientation proc
    SetLastLineWrapping proc :BOOL
    GetLastLineWrapping proc
    SetOpticalAlignment proc :DWRITE_OPTICAL_ALIGNMENT
    GetOpticalAlignment proc
    SetFontFallback	proc :ptr
    GetFontFallback	proc :ptr
    .ENDS


DEFINE_IIDX(IDWriteTextAnalyzer2, "553A9FF3-5693-4DF7-B52B-74806F7F2EB9")

.comdef IDWriteTextAnalyzer2 : public IDWriteTextAnalyzer1

    GetGlyphOrientationTransform2 proc :DWRITE_GLYPH_ORIENTATION_ANGLE, :BOOL, :FLOAT, :FLOAT, :ptr
    GetTypographicFeatures proc :ptr, :DWRITE_SCRIPT_ANALYSIS, :ptr, :UINT32, :ptr
    CheckTypographicFeature proc :ptr, :DWRITE_SCRIPT_ANALYSIS, :ptr, :DWRITE_FONT_FEATURE_TAG, :UINT32
    .ENDS


DEFINE_IIDX(IDWriteFontFallback, "EFA008F9-F7A1-48BF-B05C-F224713CC0FF")

.comdef IDWriteFontFallback : public IUnknown

    MapCharacters proc :ptr, :UINT32, :UINT32, :ptr, :ptr, :DWRITE_FONT_WEIGHT, :DWRITE_FONT_STYLE, :DWRITE_FONT_STRETCH, :ptr, :ptr
    .ENDS


DEFINE_IIDX(IDWriteFontFallbackBuilder, "FD882D06-8ABA-4FB8-B849-8BE8B73E14DE")

.comdef IDWriteFontFallbackBuilder : public IUnknown

    AddMapping proc :UINT32, :ptr, :UINT32, :ptr, :ptr, :ptr, :FLOAT
    AddMappings proc :ptr
    CreateFontFallback proc :ptr
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
    ;GetRecommendedRenderingMode proc :FLOAT, :FLOAT, :FLOAT, :ptr, :BOOL, :DWRITE_OUTLINE_THRESHOLD, :DWRITE_MEASURING_MODE, :ptr, :ptr, :ptr
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

    MoveNext		proc :ptr
    GetCurrentRun	proc :ptr
    .ENDS

DEFINE_IIDX(IDWriteRenderingParams2, "F9D711C3-9777-40AE-87E8-3E5AF9BF0948")

.comdef IDWriteRenderingParams2 : public IDWriteRenderingParams1

     GetGridFitMode proc
     .ENDS


DEFINE_IIDX(IDWriteFactory2, "0439fc60-ca44-4994-8dee-3a9af7b732ec")

.comdef IDWriteFactory2 : public IUnknown
; 0
    GetSystemFontCollection0	proc :ptr, :BOOL
    CreateCustomFontCollection	proc :ptr, :UINT32, :ptr
    RegisterFontCollectionLoader proc :ptr
    UnregisterFontCollectionLoader proc :ptr
    CreateFontFileReference	proc :ptr, :ptr, :ptr
    CreateCustomFontFileReference proc :UINT32, :ptr, :ptr
    CreateFontFace		proc :DWRITE_FONT_FACE_TYPE, :UINT32, :UINT32, :DWRITE_FONT_SIMULATIONS, :ptr
    CreateRenderingParams	proc :ptr
    CreateMonitorRenderingParams proc :HMONITOR, :ptr
    CreateCustomRenderingParams0 proc :FLOAT, :FLOAT, :FLOAT, :DWRITE_PIXEL_GEOMETRY, :DWRITE_RENDERING_MODE, :ptr
    RegisterFontFileLoader	proc :ptr
    UnregisterFontFileLoader	proc :ptr
    CreateTextFormat		proc :ptr, :ptr, :DWRITE_FONT_WEIGHT, :DWRITE_FONT_STYLE, :DWRITE_FONT_STRETCH, :FLOAT, :ptr, :ptr
    CreateTypography		proc :ptr
    GetGdiInterop		proc :ptr
    CreateTextLayout		proc :ptr, :UINT32, :ptr,  :FLOAT, :FLOAT, :ptr
    CreateGdiCompatibleTextLayout proc :UINT32, :ptr, :FLOAT, :FLOAT, :FLOAT, :ptr, :BOOL, :ptr
    CreateEllipsisTrimmingSign	proc :ptr, :ptr
    CreateTextAnalyzer		proc :ptr
    CreateNumberSubstitution	proc :DWRITE_NUMBER_SUBSTITUTION_METHOD, :ptr, :BOOL, :ptr
    CreateGlyphRunAnalysis0	proc :ptr, :FLOAT, :ptr, :DWRITE_RENDERING_MODE, :DWRITE_MEASURING_MODE, :FLOAT, :FLOAT, :ptr
; 1
    GetEudcFontCollection	proc :ptr, :BOOL
    CreateCustomRenderingParams1 proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :DWRITE_PIXEL_GEOMETRY, :DWRITE_RENDERING_MODE, :ptr
; 2
    GetSystemFontFallback	proc :ptr
    CreateFontFallbackBuilder	proc :ptr
    TranslateColorGlyphRun	proc :FLOAT, :FLOAT, :ptr, :ptr, :DWRITE_MEASURING_MODE, :ptr, :UINT32, :ptr
    CreateCustomRenderingParams proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :DWRITE_PIXEL_GEOMETRY, :DWRITE_RENDERING_MODE, :DWRITE_GRID_FIT_MODE, :ptr
    CreateGlyphRunAnalysis	proc :ptr, :ptr, :DWRITE_RENDERING_MODE, :DWRITE_MEASURING_MODE, :DWRITE_GRID_FIT_MODE, :DWRITE_TEXT_ANTIALIAS_MODE, :FLOAT, :FLOAT, :ptr
    .ENDS

endif
