;;
;; Implementation of IDWriteTextRenderer interface which builds XPS canvas with
;; multiple Glyphs
;;

    LPIXpsOMObjectFactory   typedef ptr IXpsOMObjectFactory
    LPIXpsOMCanvas          typedef ptr IXpsOMCanvas
    LPIXpsOMPartResources   typedef ptr IXpsOMPartResources
    LPIXpsOMFontResource    typedef ptr IXpsOMFontResource

.template FontMapEntry

    key          UINT_PTR ?
    fontResource LPIXpsOMFontResource ?
    .ends

.class LayoutToCanvasBuilder : public IDWriteTextRenderer

    FONT_MAP_MAX_SIZE equ 6
    GLYPH_MAPPING_MAX_COUNT equ 32

    _refCount ULONG ?

    ;; xpsFactory is stored for optimization only. Each callback method can
    ;; create an instance if so preferred.

    _xpsFactory LPIXpsOMObjectFactory ?

    ;; Result canvas and resources, empty before IDWriteTextLayout::Draw is
    ;; called with this callback object.

    _xpsCanvas LPIXpsOMCanvas ?
    _xpsResources LPIXpsOMPartResources ?

    ;; This maps COM identity of IDWriteFontFace object to IXpsOMFontResource
    ;; object

    _fontMapSize UINT ?
    _fontMap FontMapEntry FONT_MAP_MAX_SIZE dup(<>)

    ClusterMapToMappingArray proto \
                clusterMap: ptr UINT16,
                    mapLen: UINT32,     ;; number of elements in clusterMap array
            glyphsArrayLen: UINT32,     ;; number of elements in glyphs array
            resultMaxCount: UINT32,     ;; size of output buffer resultGlyphMapping (max number of elements)
        resultGlyphMapping: ptr XPS_GLYPH_MAPPING, ;; output buffer
   resultGlyphMappingCount: ptr UINT32  ;; number of elements returned in resultGlyphMapping


    ;; Constructors and destructor are private:
    ;; Instance of this object may be created only by CreateInstance static method.
    ;; It may be deleted only by Release.

    LayoutToCanvasBuilder proc :ptr IXpsOMObjectFactory
    delete proc

    ;; Internal helper methods

    CreateRootCanvasAndResources proc
    FindOrCreateFontResource proc :ptr IDWriteFontFace, :ptr ptr IXpsOMFontResource
    GenerateNewFontPartUri proc :ptr ptr IOpcPartUri
    AddLinePath proc :ptr XPS_POINT, :ptr XPS_POINT, :FLOAT

    CreateInstance proto \
        :ptr IXpsOMObjectFactory,
        :ptr ptr LayoutToCanvasBuilder

    ;; getter methods for accessing generated XPS canvas and resources.
    ;; NOTE: Returned pointer is NOT AddRef'ed by method!

    GetCanvas proc
    GetResources proc

    .ends
