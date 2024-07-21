ifndef _FLATAPI_H
define _FLATAPI_H

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

GdipCreatePath proto WINAPI :sdword, :ptr
GdipCreatePath2 proto WINAPI :ptr, :ptr, :sdword, :sdword, :ptr
GdipCreatePath2I proto WINAPI :ptr, :ptr, :sdword, :sdword, :ptr
GdipClonePath proto WINAPI :ptr, :ptr
GdipDeletePath proto WINAPI :ptr
GdipResetPath proto WINAPI :ptr
GdipGetPointCount proto WINAPI :ptr, :ptr
GdipGetPathTypes proto WINAPI :ptr, :ptr, :sdword
GdipGetPathPoints proto WINAPI :ptr, :ptr, :sdword
GdipGetPathPointsI proto WINAPI :ptr, :ptr, :sdword
GdipGetPathFillMode proto WINAPI :ptr, :ptr
GdipSetPathFillMode proto WINAPI :ptr, :sdword
GdipGetPathData proto WINAPI :ptr, :ptr
GdipStartPathFigure proto WINAPI :ptr
GdipClosePathFigure proto WINAPI :ptr
GdipClosePathFigures proto WINAPI :ptr
GdipSetPathMarker proto WINAPI :ptr
GdipClearPathMarkers proto WINAPI :ptr
GdipReversePath proto WINAPI :ptr
GdipGetPathLastPoint proto WINAPI :ptr, :ptr
GdipAddPathLine proto WINAPI :ptr, :real4, :real4, :real4, :real4
GdipAddPathLine2 proto WINAPI :ptr, :ptr, :sdword
GdipAddPathArc proto WINAPI :ptr, :real4, :real4, :real4, :real4, :real4, :real4
GdipAddPathBezier proto WINAPI :ptr, :real4, :real4, :real4, :real4, :real4, :real4, :real4, :real4
GdipAddPathBeziers proto WINAPI :ptr, :ptr, :sdword
GdipAddPathCurve proto WINAPI :ptr, :ptr, :sdword
GdipAddPathCurve2 proto WINAPI :ptr, :ptr, :sdword, :real4
GdipAddPathCurve3 proto WINAPI :ptr, :ptr, :sdword, :sdword, :sdword, :real4
GdipAddPathClosedCurve proto WINAPI :ptr, :ptr, :sdword
GdipAddPathClosedCurve2 proto WINAPI :ptr, :ptr, :sdword, :real4
GdipAddPathRectangle proto WINAPI :ptr, :real4, :real4, :real4, :real4
GdipAddPathRectangles proto WINAPI :ptr, :ptr, :sdword
GdipAddPathEllipse proto WINAPI :ptr, :real4, :real4, :real4, :real4
GdipAddPathPie proto WINAPI :ptr, :real4, :real4, :real4, :real4, :real4, :real4
GdipAddPathPolygon proto WINAPI :ptr, :ptr, :sdword
GdipAddPathPath proto WINAPI :ptr, :ptr, :BOOL
GdipAddPathString proto WINAPI :ptr, :ptr, :sdword, :ptr, :sdword, :real4, :ptr, :ptr
GdipAddPathStringI proto WINAPI :ptr, :ptr, :sdword, :ptr, :sdword, :real4, :ptr, :ptr
GdipAddPathLineI proto WINAPI :ptr, :sdword, :sdword, :sdword, :sdword
GdipAddPathLine2I proto WINAPI :ptr, :ptr, :sdword
GdipAddPathArcI proto WINAPI :ptr, :sdword, :sdword, :sdword, :sdword, :real4, :real4
GdipAddPathBezierI proto WINAPI :ptr, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword
GdipAddPathBeziersI proto WINAPI :ptr, :ptr, :sdword
GdipAddPathCurveI proto WINAPI :ptr, :ptr, :sdword
GdipAddPathCurve2I proto WINAPI :ptr, :ptr, :sdword, :real4
GdipAddPathCurve3I proto WINAPI :ptr, :ptr, :sdword, :sdword, :sdword, :real4
GdipAddPathClosedCurveI proto WINAPI :ptr, :ptr, :sdword
GdipAddPathClosedCurve2I proto WINAPI :ptr, :ptr, :sdword, :real4
GdipAddPathRectangleI proto WINAPI :ptr, :sdword, :sdword, :sdword, :sdword
GdipAddPathRectanglesI proto WINAPI :ptr, :ptr, :sdword
GdipAddPathEllipseI proto WINAPI :ptr, :sdword, :sdword, :sdword, :sdword
GdipAddPathPieI proto WINAPI :ptr, :sdword, :sdword, :sdword, :sdword, :real4, :real4
GdipAddPathPolygonI proto WINAPI :ptr, :ptr, :sdword
GdipFlattenPath proto WINAPI :ptr, :ptr, :real4
GdipWindingModeOutline proto WINAPI :ptr, :ptr, :real4
GdipWidenPath proto WINAPI :ptr, :ptr, :ptr, :real4
GdipWarpPath proto WINAPI :ptr, :ptr, :ptr, :sdword, :real4, :real4, :real4, :real4, :sdword, :real4
GdipTransformPath proto WINAPI :ptr, :ptr
GdipGetPathWorldBounds proto WINAPI :ptr, :ptr, :ptr, :ptr
GdipGetPathWorldBoundsI proto WINAPI :ptr, :ptr, :ptr, :ptr
GdipIsVisiblePathPoint proto WINAPI :ptr, :real4, :real4, :ptr, :ptr
GdipIsVisiblePathPointI proto WINAPI :ptr, :sdword, :sdword, :ptr, :ptr
GdipIsOutlineVisiblePathPoint proto WINAPI :ptr, :real4, :real4, :ptr, :ptr, :ptr
GdipIsOutlineVisiblePathPointI proto WINAPI :ptr, :sdword, :sdword, :ptr, :ptr, :ptr
GdipCreatePathIter proto WINAPI :ptr, :ptr
GdipDeletePathIter proto WINAPI :ptr
GdipPathIterNextSubpath proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr
GdipPathIterNextSubpathPath proto WINAPI :ptr, :ptr, :ptr, :ptr
GdipPathIterNextPathType proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr
GdipPathIterNextMarker proto WINAPI :ptr, :ptr, :ptr, :ptr
GdipPathIterNextMarkerPath proto WINAPI :ptr, :ptr, :ptr
GdipPathIterGetCount proto WINAPI :ptr, :ptr
GdipPathIterGetSubpathCount proto WINAPI :ptr, :ptr
GdipPathIterIsValid proto WINAPI :ptr, :ptr
GdipPathIterHasCurve proto WINAPI :ptr, :ptr
GdipPathIterRewind proto WINAPI :ptr
GdipPathIterEnumerate proto WINAPI :ptr, :ptr, :ptr, :ptr, :sdword
GdipPathIterCopyData proto WINAPI :ptr, :ptr, :ptr, :ptr, :sdword, :sdword
GdipCreateMatrix proto WINAPI :ptr
GdipCreateMatrix2 proto WINAPI :real4, :real4, :real4, :real4, :real4, :real4, :ptr
GdipCreateMatrix3 proto WINAPI :ptr, :ptr, :ptr
GdipCreateMatrix3I proto WINAPI :ptr, :ptr, :ptr
GdipCloneMatrix proto WINAPI :ptr, :ptr
GdipDeleteMatrix proto WINAPI :ptr
GdipSetMatrixElements proto WINAPI :ptr, :real4, :real4, :real4, :real4, :real4, :real4
GdipMultiplyMatrix proto WINAPI :ptr, :ptr, :sdword
GdipTranslateMatrix proto WINAPI :ptr, :real4, :real4, :sdword
GdipScaleMatrix proto WINAPI :ptr, :real4, :real4, :sdword
GdipRotateMatrix proto WINAPI :ptr, :real4, :sdword
GdipShearMatrix proto WINAPI :ptr, :real4, :real4, :sdword
GdipInvertMatrix proto WINAPI :ptr
GdipTransformMatrixPoints proto WINAPI :ptr, :ptr, :sdword
GdipTransformMatrixPointsI proto WINAPI :ptr, :ptr, :sdword
GdipVectorTransformMatrixPoints proto WINAPI :ptr, :ptr, :sdword
GdipVectorTransformMatrixPointsI proto WINAPI :ptr, :ptr, :sdword
GdipGetMatrixElements proto WINAPI :ptr, :ptr
GdipIsMatrixInvertible proto WINAPI :ptr, :ptr
GdipIsMatrixIdentity proto WINAPI :ptr, :ptr
GdipIsMatrixEqual proto WINAPI :ptr, :ptr, :ptr
GdipCreateRegion proto WINAPI :ptr
GdipCreateRegionRect proto WINAPI :ptr, :ptr
GdipCreateRegionRectI proto WINAPI :ptr, :ptr
GdipCreateRegionPath proto WINAPI :ptr, :ptr
GdipCreateRegionRgnData proto WINAPI :ptr, :sdword, :ptr
GdipCreateRegionHrgn proto WINAPI :HRGN, :ptr
GdipCloneRegion proto WINAPI :ptr, :ptr
GdipDeleteRegion proto WINAPI :ptr
GdipSetInfinite proto WINAPI :ptr
GdipSetEmpty proto WINAPI :ptr
GdipCombineRegionRect proto WINAPI :ptr, :ptr, :sdword
GdipCombineRegionRectI proto WINAPI :ptr, :ptr, :sdword
GdipCombineRegionPath proto WINAPI :ptr, :ptr, :sdword
GdipCombineRegionRegion proto WINAPI :ptr, :ptr, :sdword
GdipTranslateRegion proto WINAPI :ptr, :real4, :real4
GdipTranslateRegionI proto WINAPI :ptr, :sdword, :sdword
GdipTransformRegion proto WINAPI :ptr, :ptr
GdipGetRegionBounds proto WINAPI :ptr, :ptr, :ptr
GdipGetRegionBoundsI proto WINAPI :ptr, :ptr, :ptr
GdipGetRegionHRgn proto WINAPI :ptr, :ptr, :ptr
GdipIsEmptyRegion proto WINAPI :ptr, :ptr, :ptr
GdipIsInfiniteRegion proto WINAPI :ptr, :ptr, :ptr
GdipIsEqualRegion proto WINAPI :ptr, :ptr, :ptr, :ptr
GdipGetRegionDataSize proto WINAPI :ptr, :ptr
GdipGetRegionData proto WINAPI :ptr, :ptr, :UINT, :ptr
GdipIsVisibleRegionPoint proto WINAPI :ptr, :real4, :real4, :ptr, :ptr
GdipIsVisibleRegionPointI proto WINAPI :ptr, :sdword, :sdword, :ptr, :ptr
GdipIsVisibleRegionRect proto WINAPI :ptr, :real4, :real4, :real4, :real4, :ptr, :ptr
GdipIsVisibleRegionRectI proto WINAPI :ptr, :sdword, :sdword, :sdword, :sdword, :ptr, :ptr
GdipGetRegionScansCount proto WINAPI :ptr, :ptr, :ptr
GdipGetRegionScans proto WINAPI :ptr, :ptr, :ptr, :ptr
GdipGetRegionScansI proto WINAPI :ptr, :ptr, :ptr, :ptr
GdipCloneBrush proto WINAPI :ptr, :ptr
GdipDeleteBrush proto WINAPI :ptr
GdipGetBrushType proto WINAPI :ptr, :ptr
GdipCreateHatchBrush proto WINAPI :sdword, :ARGB, :ARGB, :ptr
GdipGetHatchStyle proto WINAPI :ptr, :ptr
GdipGetHatchForegroundColor proto WINAPI :ptr, :ptr
GdipGetHatchBackgroundColor proto WINAPI :ptr, :ptr
GdipCreateTexture proto WINAPI :ptr, :sdword, :ptr
GdipCreateTexture2 proto WINAPI :ptr, :sdword, :real4, :real4, :real4, :real4, :ptr
GdipCreateTextureIA proto WINAPI :ptr, :ptr, :real4, :real4, :real4, :real4, :ptr
GdipCreateTexture2I proto WINAPI :ptr, :sdword, :sdword, :sdword, :sdword, :sdword, :ptr
GdipCreateTextureIAI proto WINAPI :ptr, :ptr, :sdword, :sdword, :sdword, :sdword, :ptr
GdipGetTextureTransform proto WINAPI :ptr, :ptr
GdipSetTextureTransform proto WINAPI :ptr, :ptr
GdipResetTextureTransform proto WINAPI :ptr
GdipMultiplyTextureTransform proto WINAPI :ptr, :ptr, :sdword
GdipTranslateTextureTransform proto WINAPI :ptr, :real4, :real4, :sdword
GdipScaleTextureTransform proto WINAPI :ptr, :real4, :real4, :sdword
GdipRotateTextureTransform proto WINAPI :ptr, :real4, :sdword
GdipSetTextureWrapMode proto WINAPI :ptr, :sdword
GdipGetTextureWrapMode proto WINAPI :ptr, :ptr
GdipGetTextureImage proto WINAPI :ptr, :ptr
GdipCreateSolidFill proto WINAPI :ARGB, :ptr
GdipSetSolidFillColor proto WINAPI :ptr, :ARGB
GdipGetSolidFillColor proto WINAPI :ptr, :ptr
GdipCreateLineBrush proto WINAPI :ptr, :ptr, :ARGB, :ARGB, :sdword, :ptr
GdipCreateLineBrushI proto WINAPI :ptr, :ptr, :ARGB, :ARGB, :sdword, :ptr
GdipCreateLineBrushFromRect proto WINAPI :ptr, :ARGB, :ARGB, :sdword, :sdword, :ptr
GdipCreateLineBrushFromRectI proto WINAPI :ptr, :ARGB, :ARGB, :sdword, :sdword, :ptr
GdipCreateLineBrushFromRectWithAngle proto WINAPI :ptr, :ARGB, :ARGB, :real4, :BOOL, :sdword, :ptr
GdipCreateLineBrushFromRectWithAngleI proto WINAPI :ptr, :ARGB, :ARGB, :real4, :BOOL, :sdword, :ptr
GdipSetLineColors proto WINAPI :ptr, :ARGB, :ARGB
GdipGetLineColors proto WINAPI :ptr, :ptr
GdipGetLineRect proto WINAPI :ptr, :ptr
GdipGetLineRectI proto WINAPI :ptr, :ptr
GdipSetLineGammaCorrection proto WINAPI :ptr, :BOOL
GdipGetLineGammaCorrection proto WINAPI :ptr, :ptr
GdipGetLineBlendCount proto WINAPI :ptr, :ptr
GdipGetLineBlend proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipSetLineBlend proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipGetLinePresetBlendCount proto WINAPI :ptr, :ptr
GdipGetLinePresetBlend proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipSetLinePresetBlend proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipSetLineSigmaBlend proto WINAPI :ptr, :real4, :real4
GdipSetLineLinearBlend proto WINAPI :ptr, :real4, :real4
GdipSetLineWrapMode proto WINAPI :ptr, :sdword
GdipGetLineWrapMode proto WINAPI :ptr, :ptr
GdipGetLineTransform proto WINAPI :ptr, :ptr
GdipSetLineTransform proto WINAPI :ptr, :ptr
GdipResetLineTransform proto WINAPI :ptr
GdipMultiplyLineTransform proto WINAPI :ptr, :ptr, :sdword
GdipTranslateLineTransform proto WINAPI :ptr, :real4, :real4, :sdword
GdipScaleLineTransform proto WINAPI :ptr, :real4, :real4, :sdword
GdipRotateLineTransform proto WINAPI :ptr, :real4, :sdword
GdipCreatePathGradient proto WINAPI :ptr, :sdword, :sdword, :ptr
GdipCreatePathGradientI proto WINAPI :ptr, :sdword, :sdword, :ptr
GdipCreatePathGradientFromPath proto WINAPI :ptr, :ptr
GdipGetPathGradientCenterColor proto WINAPI :ptr, :ptr
GdipSetPathGradientCenterColor proto WINAPI :ptr, :ARGB
GdipGetPathGradientSurroundColorsWithCount proto WINAPI :ptr, :ptr, :ptr
GdipSetPathGradientSurroundColorsWithCount proto WINAPI :ptr, :ptr, :ptr
GdipGetPathGradientPath proto WINAPI :ptr, :ptr
GdipSetPathGradientPath proto WINAPI :ptr, :ptr
GdipGetPathGradientCenterPoint proto WINAPI :ptr, :ptr
GdipGetPathGradientCenterPointI proto WINAPI :ptr, :ptr
GdipSetPathGradientCenterPoint proto WINAPI :ptr, :ptr
GdipSetPathGradientCenterPointI proto WINAPI :ptr, :ptr
GdipGetPathGradientRect proto WINAPI :ptr, :ptr
GdipGetPathGradientRectI proto WINAPI :ptr, :ptr
GdipGetPathGradientPointCount proto WINAPI :ptr, :ptr
GdipGetPathGradientSurroundColorCount proto WINAPI :ptr, :ptr
GdipSetPathGradientGammaCorrection proto WINAPI :ptr, :BOOL
GdipGetPathGradientGammaCorrection proto WINAPI :ptr, :ptr
GdipGetPathGradientBlendCount proto WINAPI :ptr, :ptr
GdipGetPathGradientBlend proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipSetPathGradientBlend proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipGetPathGradientPresetBlendCount proto WINAPI :ptr, :ptr
GdipGetPathGradientPresetBlend proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipSetPathGradientPresetBlend proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipSetPathGradientSigmaBlend proto WINAPI :ptr, :real4, :real4
GdipSetPathGradientLinearBlend proto WINAPI :ptr, :real4, :real4
GdipGetPathGradientWrapMode proto WINAPI :ptr, :ptr
GdipSetPathGradientWrapMode proto WINAPI :ptr, :sdword
GdipGetPathGradientTransform proto WINAPI :ptr, :ptr
GdipSetPathGradientTransform proto WINAPI :ptr, :ptr
GdipResetPathGradientTransform proto WINAPI :ptr
GdipMultiplyPathGradientTransform proto WINAPI :ptr, :ptr, :sdword
GdipTranslatePathGradientTransform proto WINAPI :ptr, :real4, :real4, :sdword
GdipScalePathGradientTransform proto WINAPI :ptr, :real4, :real4, :sdword
GdipRotatePathGradientTransform proto WINAPI :ptr, :real4, :sdword
GdipGetPathGradientFocusScales proto WINAPI :ptr, :ptr, :ptr
GdipSetPathGradientFocusScales proto WINAPI :ptr, :real4, :real4

GdipCreatePen1 proto WINAPI :ARGB, :real4, :sdword, :ptr
GdipCreatePen2 proto WINAPI :ptr, :real4, :sdword, :ptr
GdipClonePen proto WINAPI :ptr, :ptr
GdipDeletePen proto WINAPI :ptr
GdipSetPenWidth proto WINAPI :ptr, :real4
GdipGetPenWidth proto WINAPI :ptr, :ptr
GdipSetPenUnit proto WINAPI :ptr, :sdword
GdipGetPenUnit proto WINAPI :ptr, :ptr
GdipSetPenLineCap197819 proto WINAPI :ptr, :sdword, :sdword, :sdword
GdipSetPenStartCap proto WINAPI :ptr, :sdword
GdipSetPenEndCap proto WINAPI :ptr, :sdword
GdipSetPenDashCap197819 proto WINAPI :ptr, :sdword
GdipGetPenStartCap proto WINAPI :ptr, :ptr
GdipGetPenEndCap proto WINAPI :ptr, :ptr
GdipGetPenDashCap197819 proto WINAPI :ptr, :ptr
GdipSetPenLineJoin proto WINAPI :ptr, :sdword
GdipGetPenLineJoin proto WINAPI :ptr, :ptr
GdipSetPenCustomStartCap proto WINAPI :ptr, :ptr
GdipGetPenCustomStartCap proto WINAPI :ptr, :ptr
GdipSetPenCustomEndCap proto WINAPI :ptr, :ptr
GdipGetPenCustomEndCap proto WINAPI :ptr, :ptr
GdipSetPenMiterLimit proto WINAPI :ptr, :real4
GdipGetPenMiterLimit proto WINAPI :ptr, :ptr
GdipSetPenMode proto WINAPI :ptr, :sdword
GdipGetPenMode proto WINAPI :ptr, :ptr
GdipSetPenTransform proto WINAPI :ptr, :ptr
GdipGetPenTransform proto WINAPI :ptr, :ptr
GdipResetPenTransform proto WINAPI :ptr
GdipMultiplyPenTransform proto WINAPI :ptr, :ptr, :sdword
GdipTranslatePenTransform proto WINAPI :ptr, :real4, :real4, :sdword
GdipScalePenTransform proto WINAPI :ptr, :real4, :real4, :sdword
GdipRotatePenTransform proto WINAPI :ptr, :real4, :sdword
GdipSetPenColor proto WINAPI :ptr, :ARGB
GdipGetPenColor proto WINAPI :ptr, :ptr
GdipSetPenBrushFill proto WINAPI :ptr, :ptr
GdipGetPenBrushFill proto WINAPI :ptr, :ptr
GdipGetPenFillType proto WINAPI :ptr, :ptr
GdipGetPenDashStyle proto WINAPI :ptr, :ptr
GdipSetPenDashStyle proto WINAPI :ptr, :sdword
GdipGetPenDashOffset proto WINAPI :ptr, :ptr
GdipSetPenDashOffset proto WINAPI :ptr, :real4
GdipGetPenDashCount proto WINAPI :ptr, :ptr
GdipSetPenDashArray proto WINAPI :ptr, :ptr, :sdword
GdipGetPenDashArray proto WINAPI :ptr, :ptr, :sdword
GdipGetPenCompoundCount proto WINAPI :ptr, :ptr
GdipSetPenCompoundArray proto WINAPI :ptr, :ptr, :sdword
GdipGetPenCompoundArray proto WINAPI :ptr, :ptr, :sdword

GdipCreateCustomLineCap proto WINAPI :ptr, :ptr, :sdword, :real4, :ptr
GdipDeleteCustomLineCap proto WINAPI :ptr
GdipCloneCustomLineCap proto WINAPI :ptr, :ptr
GdipGetCustomLineCapType proto WINAPI :ptr, :ptr
GdipSetCustomLineCapStrokeCaps proto WINAPI :ptr, :sdword, :sdword
GdipGetCustomLineCapStrokeCaps proto WINAPI :ptr, :ptr, :ptr
GdipSetCustomLineCapStrokeJoin proto WINAPI :ptr, :sdword
GdipGetCustomLineCapStrokeJoin proto WINAPI :ptr, :ptr
GdipSetCustomLineCapBaseCap proto WINAPI :ptr, :sdword
GdipGetCustomLineCapBaseCap proto WINAPI :ptr, :ptr
GdipSetCustomLineCapBaseInset proto WINAPI :ptr, :real4
GdipGetCustomLineCapBaseInset proto WINAPI :ptr, :ptr
GdipSetCustomLineCapWidthScale proto WINAPI :ptr, :real4
GdipGetCustomLineCapWidthScale proto WINAPI :ptr, :ptr

GdipCreateAdjustableArrowCap proto WINAPI :real4, :real4, :BOOL, :ptr ptr
GdipSetAdjustableArrowCapHeight proto WINAPI :ptr, :real4
GdipGetAdjustableArrowCapHeight proto WINAPI :ptr, :ptr
GdipSetAdjustableArrowCapWidth proto WINAPI :ptr, :real4
GdipGetAdjustableArrowCapWidth proto WINAPI :ptr, :ptr
GdipSetAdjustableArrowCapMiddleInset proto WINAPI :ptr, :real4
GdipGetAdjustableArrowCapMiddleInset proto WINAPI :ptr, :ptr
GdipSetAdjustableArrowCapFillState proto WINAPI :ptr, :BOOL
GdipGetAdjustableArrowCapFillState proto WINAPI :ptr, :ptr

GdipLoadImageFromStream proto WINAPI :ptr, :ptr
GdipLoadImageFromFile proto WINAPI :ptr, :ptr
GdipLoadImageFromStreamICM proto WINAPI :ptr, :ptr
GdipLoadImageFromFileICM proto WINAPI :ptr, :ptr
GdipCloneImage proto WINAPI :ptr, :ptr
GdipDisposeImage proto WINAPI :ptr
GdipSaveImageToFile proto WINAPI :ptr, :ptr, :ptr, :ptr
GdipSaveImageToStream proto WINAPI :ptr, :ptr, :ptr, :ptr
GdipSaveAdd proto WINAPI :ptr, :ptr
GdipSaveAddImage proto WINAPI :ptr, :ptr, :ptr
GdipGetImageGraphicsContext proto WINAPI :ptr, :ptr
GdipGetImageBounds proto WINAPI :ptr, :ptr, :ptr
GdipGetImageDimension proto WINAPI :ptr, :ptr, :ptr
GdipGetImageType proto WINAPI :ptr, :ptr
GdipGetImageWidth proto WINAPI :ptr, :ptr
GdipGetImageHeight proto WINAPI :ptr, :ptr
GdipGetImageHorizontalResolution proto WINAPI :ptr, :ptr
GdipGetImageVerticalResolution proto WINAPI :ptr, :ptr
GdipGetImageFlags proto WINAPI :ptr, :ptr
GdipGetImageRawFormat proto WINAPI :ptr, :ptr
GdipGetImagePixelFormat proto WINAPI :ptr, :ptr
GdipGetImageThumbnail proto WINAPI :ptr, :dword, :dword, :ptr, :ptr, :ptr
GdipGetEncoderParameterListSize proto WINAPI :ptr, :ptr, :ptr
GdipGetEncoderParameterList proto WINAPI :ptr, :ptr, :dword, :ptr
GdipImageGetFrameDimensionsCount proto WINAPI :ptr, :ptr
GdipImageGetFrameDimensionsList proto WINAPI :ptr, :ptr, :dword
GdipImageGetFrameCount proto WINAPI :ptr, :ptr, :ptr
GdipImageSelectActiveFrame proto WINAPI :ptr, :ptr, :dword
GdipImageRotateFlip proto WINAPI :ptr, :sdword
GdipGetImagePalette proto WINAPI :ptr, :ptr, :sdword
GdipSetImagePalette proto WINAPI :ptr, :ptr
GdipGetImagePaletteSize proto WINAPI :ptr, :ptr
GdipGetPropertyCount proto WINAPI :ptr, :ptr
GdipGetPropertyIdList proto WINAPI :ptr, :dword, :ptr
GdipGetPropertyItemSize proto WINAPI :ptr, :dword, :ptr
GdipGetPropertyItem proto WINAPI :ptr, :dword, :dword, :ptr
GdipGetPropertySize proto WINAPI :ptr, :ptr, :ptr
GdipGetAllPropertyItems proto WINAPI :ptr, :dword, :dword, :ptr
GdipRemovePropertyItem proto WINAPI :ptr, :dword
GdipSetPropertyItem proto WINAPI :ptr, :ptr
if (GDIPVER GE 0x0110)
GdipFindFirstImageItem proto WINAPI :ptr, :ptr
GdipFindNextImageItem proto WINAPI :ptr, :ptr
GdipGetImageItemData proto WINAPI :ptr, :ptr
endif
GdipImageForceValidation proto WINAPI :ptr
GdipCreateBitmapFromStream proto WINAPI :ptr, :ptr
GdipCreateBitmapFromFile proto WINAPI :ptr, :ptr

GdipCreateBitmapFromStreamICM proto WINAPI :ptr, :ptr
GdipCreateBitmapFromFileICM proto WINAPI :ptr, :ptr
GdipCreateBitmapFromScan0 proto WINAPI :sdword, :sdword, :sdword, :sdword, :ptr, :ptr
GdipCreateBitmapFromGraphics proto WINAPI :sdword, :sdword, :ptr, :ptr
GdipCreateBitmapFromDirectDrawSurface proto WINAPI :ptr, :ptr
GdipCreateBitmapFromGdiDib proto WINAPI :ptr, :ptr, :ptr
GdipCreateBitmapFromHBITMAP proto WINAPI :HBITMAP, :HPALETTE, :ptr
GdipCreateHBITMAPFromBitmap proto WINAPI :ptr, :ptr, :ARGB
GdipCreateBitmapFromHICON proto WINAPI :HICON, :ptr
GdipCreateHICONFromBitmap proto WINAPI :ptr, :ptr
GdipCreateBitmapFromResource proto WINAPI :HINSTANCE, :ptr, :ptr
GdipCloneBitmapArea proto WINAPI :real4, :real4, :real4, :real4, :sdword, :ptr, :ptr
GdipCloneBitmapAreaI proto WINAPI :sdword, :sdword, :sdword, :sdword, :sdword, :ptr, :ptr
GdipBitmapLockBits proto WINAPI :ptr, :ptr, :dword, :sdword, :ptr
GdipBitmapUnlockBits proto WINAPI :ptr, :ptr
GdipBitmapGetPixel proto WINAPI :ptr, :sdword, :sdword, :ptr
GdipBitmapSetPixel proto WINAPI :ptr, :sdword, :sdword, :ARGB

if (GDIPVER GE 0x0110)
GdipImageSetAbort proto WINAPI :ptr, :ptr
GdipGraphicsSetAbort proto WINAPI :ptr, :ptr
GdipBitmapConvertFormat proto WINAPI :ptr, :sdword, :sdword, :sdword, :ptr, :real4
GdipInitializePalette proto WINAPI :ptr, :sdword, :sdword, :BOOL, :ptr
GdipBitmapApplyEffect proto WINAPI :ptr, :ptr, :ptr, :BOOL, :ptr, :ptr
GdipBitmapCreateApplyEffect proto WINAPI :ptr, :sdword, :ptr, :ptr, :ptr, :ptr, :BOOL, :ptr, :ptr
GdipBitmapGetHistogram proto WINAPI :ptr, :sdword, :dword, :ptr, :ptr, :ptr, :ptr
GdipBitmapGetHistogramSize proto WINAPI :sdword, :ptr
endif
GdipBitmapSetResolution proto WINAPI :ptr, :real4, :real4

GdipCreateImageAttributes proto WINAPI :ptr
GdipCloneImageAttributes proto WINAPI :ptr, :ptr
GdipDisposeImageAttributes proto WINAPI :ptr
GdipSetImageAttributesToIdentity proto WINAPI :ptr, :sdword
GdipResetImageAttributes proto WINAPI :ptr, :sdword
GdipSetImageAttributesColorMatrix proto WINAPI :ptr, :sdword, :BOOL, :ptr, :ptr, :sdword
GdipSetImageAttributesThreshold proto WINAPI :ptr, :sdword, :BOOL, :real4
GdipSetImageAttributesGamma proto WINAPI :ptr, :sdword, :BOOL, :real4
GdipSetImageAttributesNoOp proto WINAPI :ptr, :sdword, :BOOL
GdipSetImageAttributesColorKeys proto WINAPI :ptr, :sdword, :BOOL, :ARGB, :ARGB
GdipSetImageAttributesOutputChannel proto WINAPI :ptr, :sdword, :BOOL, :sdword
GdipSetImageAttributesOutputChannelColorProfile proto WINAPI :ptr, :sdword, :BOOL, :ptr
GdipSetImageAttributesRemapTable proto WINAPI :ptr, :sdword, :BOOL, :UINT, :ptr
GdipSetImageAttributesWrapMode proto WINAPI :ptr, :sdword, :ARGB, :BOOL
GdipSetImageAttributesICMMode proto WINAPI :ptr, :BOOL
GdipGetImageAttributesAdjustedPalette proto WINAPI :ptr, :ptr, :sdword

GdipFlush proto WINAPI :ptr, :sdword
GdipCreateFromHDC proto WINAPI :HDC, :ptr
GdipCreateFromHDC2 proto WINAPI :HDC, :HANDLE, :ptr
GdipCreateFromHWND proto WINAPI :HWND, :ptr
GdipCreateFromHWNDICM proto WINAPI :HWND, :ptr
GdipDeleteGraphics proto WINAPI :ptr
GdipGetDC proto WINAPI :ptr, :ptr
GdipReleaseDC proto WINAPI :ptr, :HDC
GdipSetCompositingMode proto WINAPI :ptr, :sdword
GdipGetCompositingMode proto WINAPI :ptr, :ptr
GdipSetRenderingOrigin proto WINAPI :ptr, :sdword, :sdword
GdipGetRenderingOrigin proto WINAPI :ptr, :ptr, :ptr
GdipSetCompositingQuality proto WINAPI :ptr, :sdword
GdipGetCompositingQuality proto WINAPI :ptr, :ptr
GdipSetSmoothingMode proto WINAPI :ptr, :sdword
GdipGetSmoothingMode proto WINAPI :ptr, :ptr
GdipSetPixelOffsetMode proto WINAPI :ptr, :sdword
GdipGetPixelOffsetMode proto WINAPI :ptr, :ptr
GdipSetTextRenderingHint proto WINAPI :ptr, :sdword
GdipGetTextRenderingHint proto WINAPI :ptr, :ptr
GdipSetTextContrast proto WINAPI :ptr, :dword
GdipGetTextContrast proto WINAPI :ptr, :ptr
GdipSetInterpolationMode proto WINAPI :ptr, :sdword
GdipGetInterpolationMode proto WINAPI :ptr, :ptr
GdipSetWorldTransform proto WINAPI :ptr, :ptr
GdipResetWorldTransform proto WINAPI :ptr
GdipMultiplyWorldTransform proto WINAPI :ptr, :ptr, :sdword
GdipTranslateWorldTransform proto WINAPI :ptr, :real4, :real4, :sdword
GdipScaleWorldTransform proto WINAPI :ptr, :real4, :real4, :sdword
GdipRotateWorldTransform proto WINAPI :ptr, :real4, :sdword
GdipGetWorldTransform proto WINAPI :ptr, :ptr
GdipResetPageTransform proto WINAPI :ptr
GdipGetPageUnit proto WINAPI :ptr, :ptr
GdipGetPageScale proto WINAPI :ptr, :ptr
GdipSetPageUnit proto WINAPI :ptr, :sdword
GdipSetPageScale proto WINAPI :ptr, :real4
GdipGetDpiX proto WINAPI :ptr, :ptr
GdipGetDpiY proto WINAPI :ptr, :ptr
GdipTransformPoints proto WINAPI :ptr, :sdword, :sdword, :ptr, :sdword
GdipTransformPointsI proto WINAPI :ptr, :sdword, :sdword, :ptr, :sdword
GdipGetNearestColor proto WINAPI :ptr, :ptr
GdipCreateHalftonePalette proto WINAPI
GdipDrawLine proto WINAPI :ptr, :ptr, :real4, :real4, :real4, :real4
GdipDrawLineI proto WINAPI :ptr, :ptr, :sdword, :sdword, :sdword, :sdword
GdipDrawLines proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipDrawLinesI proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipDrawArc proto WINAPI :ptr, :ptr, :real4, :real4, :real4, :real4, :real4, :real4
GdipDrawArcI proto WINAPI :ptr, :ptr, :sdword, :sdword, :sdword, :sdword, :real4, :real4
GdipDrawBezier proto WINAPI :ptr, :ptr, :real4, :real4, :real4, :real4, :real4, :real4, :real4, :real4
GdipDrawBezierI proto WINAPI :ptr, :ptr, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword
GdipDrawBeziers proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipDrawBeziersI proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipDrawRectangle proto WINAPI :ptr, :ptr, :real4, :real4, :real4, :real4
GdipDrawRectangleI proto WINAPI :ptr, :ptr, :sdword, :sdword, :sdword, :sdword
GdipDrawRectangles proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipDrawRectanglesI proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipDrawEllipse proto WINAPI :ptr, :ptr, :real4, :real4, :real4, :real4
GdipDrawEllipseI proto WINAPI :ptr, :ptr, :sdword, :sdword, :sdword, :sdword
GdipDrawPie proto WINAPI :ptr, :ptr, :real4, :real4, :real4, :real4, :real4, :real4
GdipDrawPieI proto WINAPI :ptr, :ptr, :sdword, :sdword, :sdword, :sdword, :real4, :real4
GdipDrawPolygon proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipDrawPolygonI proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipDrawPath proto WINAPI :ptr, :ptr, :ptr
GdipDrawCurve proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipDrawCurveI proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipDrawCurve2 proto WINAPI :ptr, :ptr, :ptr, :sdword, :real4
GdipDrawCurve2I proto WINAPI :ptr, :ptr, :ptr, :sdword, :real4
GdipDrawCurve3 proto WINAPI :ptr, :ptr, :ptr, :sdword, :sdword, :sdword, :real4
GdipDrawCurve3I proto WINAPI :ptr, :ptr, :ptr, :sdword, :sdword, :sdword, :real4
GdipDrawClosedCurve proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipDrawClosedCurveI proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipDrawClosedCurve2 proto WINAPI :ptr, :ptr, :ptr, :sdword, :real4
GdipDrawClosedCurve2I proto WINAPI :ptr, :ptr, :ptr, :sdword, :real4
GdipGraphicsClear proto WINAPI :ptr, :ARGB
GdipFillRectangle proto WINAPI :ptr, :ptr, :real4, :real4, :real4, :real4
GdipFillRectangleI proto WINAPI :ptr, :ptr, :sdword, :sdword, :sdword, :sdword
GdipFillRectangles proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipFillRectanglesI proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipFillPolygon proto WINAPI :ptr, :ptr, :ptr, :sdword, :sdword
GdipFillPolygonI proto WINAPI :ptr, :ptr, :ptr, :sdword, :sdword
GdipFillPolygon2 proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipFillPolygon2I proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipFillEllipse proto WINAPI :ptr, :ptr, :real4, :real4, :real4, :real4
GdipFillEllipseI proto WINAPI :ptr, :ptr, :sdword, :sdword, :sdword, :sdword
GdipFillPie proto WINAPI :ptr, :ptr, :real4, :real4, :real4, :real4, :real4, :real4
GdipFillPieI proto WINAPI :ptr, :ptr, :sdword, :sdword, :sdword, :sdword, :real4, :real4
GdipFillPath proto WINAPI :ptr, :ptr, :ptr
GdipFillClosedCurve proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipFillClosedCurveI proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipFillClosedCurve2 proto WINAPI :ptr, :ptr, :ptr, :sdword, :real4, :sdword
GdipFillClosedCurve2I proto WINAPI :ptr, :ptr, :ptr, :sdword, :real4, :sdword
GdipFillRegion proto WINAPI :ptr, :ptr, :ptr

if (GDIPVER GE 0x0110)
GdipDrawImageFX proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :sdword
endif
GdipDrawImage proto WINAPI :ptr, :ptr, :real4, :real4
GdipDrawImageI proto WINAPI :ptr, :ptr, :sdword, :sdword
GdipDrawImageRect proto WINAPI :ptr, :ptr, :real4, :real4, :real4, :real4
GdipDrawImageRectI proto WINAPI :ptr, :ptr, :sdword, :sdword, :sdword, :sdword
GdipDrawImagePoints proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipDrawImagePointsI proto WINAPI :ptr, :ptr, :ptr, :sdword
GdipDrawImagePointRect proto WINAPI :ptr, :ptr, :real4, :real4, :real4, :real4, :real4, :real4, :sdword
GdipDrawImagePointRectI proto WINAPI :ptr, :ptr, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword
GdipDrawImageRectRect proto WINAPI :ptr, :ptr, :real4, :real4, :real4, :real4, :real4, :real4, :real4, :real4, :sdword, :ptr, :ptr, :ptr
GdipDrawImageRectRectI proto WINAPI :ptr, :ptr, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :ptr, :ptr, :ptr
GdipDrawImagePointsRect proto WINAPI :ptr, :ptr, :ptr, :sdword, :real4, :real4, :real4, :real4, :sdword, :ptr, :ptr, :ptr
GdipDrawImagePointsRectI proto WINAPI :ptr, :ptr, :ptr, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :ptr, :ptr, :ptr

GdipEnumerateMetafileDestPoint proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
GdipEnumerateMetafileDestPointI proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
GdipEnumerateMetafileDestRect proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
GdipEnumerateMetafileDestRectI proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
GdipEnumerateMetafileDestPoints proto WINAPI :ptr, :ptr, :ptr, :sdword, :ptr, :ptr, :ptr
GdipEnumerateMetafileDestPointsI proto WINAPI :ptr, :ptr, :ptr, :sdword, :ptr, :ptr, :ptr
GdipEnumerateMetafileSrcRectDestPoint proto WINAPI :ptr, :ptr, :ptr, :ptr, :sdword, :ptr, :ptr, :ptr
GdipEnumerateMetafileSrcRectDestPointI proto WINAPI :ptr, :ptr, :ptr, :ptr, :sdword, :ptr, :ptr, :ptr
GdipEnumerateMetafileSrcRectDestRect proto WINAPI :ptr, :ptr, :ptr, :ptr, :sdword, :ptr, :ptr, :ptr
GdipEnumerateMetafileSrcRectDestRectI proto WINAPI :ptr, :ptr, :ptr, :ptr, :sdword, :ptr, :ptr, :ptr
GdipEnumerateMetafileSrcRectDestPoints proto WINAPI :ptr, :ptr, :ptr, :sdword, :ptr, :sdword, :ptr, :ptr, :ptr
GdipEnumerateMetafileSrcRectDestPointsI proto WINAPI :ptr, :ptr, :ptr, :sdword, :ptr, :sdword, :ptr, :ptr, :ptr

GdipPlayMetafileRecord proto WINAPI :ptr, :sdword, :dword, :dword, :ptr
GdipSetClipGraphics proto WINAPI :ptr, :ptr, :sdword
GdipSetClipRect proto WINAPI :ptr, :real4, :real4, :real4, :real4, :sdword
GdipSetClipRectI proto WINAPI :ptr, :sdword, :sdword, :sdword, :sdword, :sdword
GdipSetClipPath proto WINAPI :ptr, :ptr, :sdword
GdipSetClipRegion proto WINAPI :ptr, :ptr, :sdword
GdipSetClipHrgn proto WINAPI :ptr, :HRGN, :sdword
GdipResetClip proto WINAPI :ptr
GdipTranslateClip proto WINAPI :ptr, :real4, :real4
GdipTranslateClipI proto WINAPI :ptr, :sdword, :sdword
GdipGetClip proto WINAPI :ptr, :ptr
GdipGetClipBounds proto WINAPI :ptr, :ptr
GdipGetClipBoundsI proto WINAPI :ptr, :ptr
GdipIsClipEmpty proto WINAPI :ptr, :ptr
GdipGetVisibleClipBounds proto WINAPI :ptr, :ptr
GdipGetVisibleClipBoundsI proto WINAPI :ptr, :ptr
GdipIsVisibleClipEmpty proto WINAPI :ptr, :ptr
GdipIsVisiblePoint proto WINAPI :ptr, :real4, :real4, :ptr
GdipIsVisiblePointI proto WINAPI :ptr, :sdword, :sdword, :ptr
GdipIsVisibleRect proto WINAPI :ptr, :real4, :real4, :real4, :real4, :ptr
GdipIsVisibleRectI proto WINAPI :ptr, :sdword, :sdword, :sdword, :sdword, :ptr

GdipSaveGraphics proto WINAPI :ptr, :ptr
GdipRestoreGraphics proto WINAPI :ptr, :sdword
GdipBeginContainer proto WINAPI :ptr, :ptr, :ptr, :sdword, :ptr
GdipBeginContainerI proto WINAPI :ptr, :ptr, :ptr, :sdword, :ptr
GdipBeginContainer2 proto WINAPI :ptr, :ptr
GdipEndContainer proto WINAPI :ptr, :sdword

GdipGetMetafileHeaderFromWmf proto WINAPI :HMETAFILE, :ptr, :ptr
GdipGetMetafileHeaderFromEmf proto WINAPI :HENHMETAFILE, :ptr
GdipGetMetafileHeaderFromFile proto WINAPI :ptr, :ptr
GdipGetMetafileHeaderFromStream proto WINAPI :ptr, :ptr
GdipGetMetafileHeaderFromMetafile proto WINAPI :ptr, :ptr
GdipGetHemfFromMetafile proto WINAPI :ptr, :ptr
GdipCreateStreamOnFile proto WINAPI :ptr, :dword, :ptr
GdipCreateMetafileFromWmf proto WINAPI :HMETAFILE, :BOOL, :ptr, :ptr
GdipCreateMetafileFromEmf proto WINAPI :HENHMETAFILE, :BOOL, :ptr
GdipCreateMetafileFromFile proto WINAPI :ptr, :ptr
GdipCreateMetafileFromWmfFile proto WINAPI :ptr, :ptr, :ptr
GdipCreateMetafileFromStream proto WINAPI :ptr, :ptr

GdipRecordMetafile proto WINAPI :HDC, :sdword, :ptr, :sdword, :ptr, :ptr ptr
GdipRecordMetafileI proto WINAPI :HDC, :sdword, :ptr, :sdword, :ptr, :ptr ptr
GdipRecordMetafileFileName proto WINAPI :ptr, :HDC, :sdword, :ptr, :sdword, :ptr, :ptr ptr
GdipRecordMetafileFileNameI proto WINAPI :ptr, :HDC, :sdword, :ptr, :sdword, :ptr, :ptr ptr
GdipRecordMetafileStream proto WINAPI :ptr, :HDC, :sdword, :ptr, :sdword, :ptr, :ptr ptr
GdipRecordMetafileStreamI proto WINAPI :ptr, :HDC, :sdword, :ptr, :sdword, :ptr, :ptr ptr
GdipSetMetafileDownLevelRasterizationLimit proto WINAPI :ptr, :dword
GdipGetMetafileDownLevelRasterizationLimit proto WINAPI :ptr, :ptr
GdipGetImageDecodersSize proto WINAPI :ptr, :ptr
GdipGetImageDecoders proto WINAPI :dword, :dword, :ptr
GdipGetImageEncodersSize proto WINAPI :ptr, :ptr
GdipGetImageEncoders proto WINAPI :dword, :dword, :ptr
GdipComment proto WINAPI :ptr, :dword, :ptr

GdipCreateFontFamilyFromName proto WINAPI :ptr, :ptr, :ptr
GdipDeleteFontFamily proto WINAPI :ptr
GdipCloneFontFamily proto WINAPI :ptr, :ptr
GdipGetGenericFontFamilySansSerif proto WINAPI :ptr
GdipGetGenericFontFamilySerif proto WINAPI :ptr
GdipGetGenericFontFamilyMonospace proto WINAPI :ptr
GdipGetFamilyName proto WINAPI :ptr, :ptr, :LANGID
GdipIsStyleAvailable proto WINAPI :ptr, :sdword, :ptr
GdipFontCollectionEnumerable proto WINAPI :ptr, :ptr, :ptr
GdipFontCollectionEnumerate proto WINAPI :ptr, :sdword, :ptr, :ptr, :ptr
GdipGetEmHeight proto WINAPI :ptr, :sdword, :ptr
GdipGetCellAscent proto WINAPI :ptr, :sdword, :ptr
GdipGetCellDescent proto WINAPI :ptr, :sdword, :ptr
GdipGetLineSpacing proto WINAPI :ptr, :sdword, :ptr

GdipCreateFontFromDC proto WINAPI :HDC, :ptr
GdipCreateFontFromLogfontA proto WINAPI :HDC, :ptr, :ptr
GdipCreateFontFromLogfontW proto WINAPI :HDC, :ptr, :ptr
GdipCreateFont proto WINAPI :ptr, :real4, :sdword, :sdword, :ptr
GdipCloneFont proto WINAPI :ptr, :ptr
GdipDeleteFont proto WINAPI :ptr
GdipGetFamily proto WINAPI :ptr, :ptr
GdipGetFontStyle proto WINAPI :ptr, :ptr
GdipGetFontSize proto WINAPI :ptr, :ptr
GdipGetFontUnit proto WINAPI :ptr, :ptr
GdipGetFontHeight proto WINAPI :ptr, :ptr, :ptr
GdipGetFontHeightGivenDPI proto WINAPI :ptr, :real4, :ptr
GdipGetLogFontA proto WINAPI :ptr, :ptr, :ptr
GdipGetLogFontW proto WINAPI :ptr, :ptr, :ptr
GdipNewInstalledFontCollection proto WINAPI :ptr
GdipNewPrivateFontCollection proto WINAPI :ptr
GdipDeletePrivateFontCollection proto WINAPI :ptr
GdipGetFontCollectionFamilyCount proto WINAPI :ptr, :ptr
GdipGetFontCollectionFamilyList proto WINAPI :ptr, :sdword, :ptr, :ptr
GdipPrivateAddFontFile proto WINAPI :ptr, :ptr
GdipPrivateAddMemoryFont proto WINAPI :ptr, :ptr, :sdword

GdipDrawString proto WINAPI :ptr, :ptr, :sdword, :ptr, :ptr, :ptr, :ptr
GdipMeasureString proto WINAPI :ptr, :ptr, :sdword, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
GdipMeasureCharacterRanges proto WINAPI :ptr, :ptr, :sdword, :ptr, :ptr, :ptr, :sdword, :ptr ptr
GdipDrawDriverString proto WINAPI :ptr, :ptr, :sdword, :ptr, :ptr, :ptr, :sdword, :ptr
GdipMeasureDriverString proto WINAPI :ptr, :ptr, :sdword, :ptr, :ptr, :sdword, :ptr, :ptr

GdipCreateStringFormat proto WINAPI :sdword, :LANGID, :ptr
GdipStringFormatGetGenericDefault proto WINAPI :ptr
GdipStringFormatGetGenericTypographic proto WINAPI :ptr
GdipDeleteStringFormat proto WINAPI :ptr
GdipCloneStringFormat proto WINAPI :ptr, :ptr
GdipSetStringFormatFlags proto WINAPI :ptr, :sdword
GdipGetStringFormatFlags proto WINAPI :ptr, :ptr
GdipSetStringFormatAlign proto WINAPI :ptr, :sdword
GdipGetStringFormatAlign proto WINAPI :ptr, :ptr
GdipSetStringFormatLineAlign proto WINAPI :ptr, :sdword
GdipGetStringFormatLineAlign proto WINAPI :ptr, :ptr
GdipSetStringFormatTrimming proto WINAPI :ptr, :sdword
GdipGetStringFormatTrimming proto WINAPI :ptr, :ptr
GdipSetStringFormatHotkeyPrefix proto WINAPI :ptr, :sdword
GdipGetStringFormatHotkeyPrefix proto WINAPI :ptr, :ptr
GdipSetStringFormatTabStops proto WINAPI :ptr, :real4, :sdword, :ptr
GdipGetStringFormatTabStops proto WINAPI :ptr, :sdword, :ptr, :ptr
GdipGetStringFormatTabStopCount proto WINAPI :ptr, :ptr
GdipSetStringFormatDigitSubstitution proto WINAPI :ptr, :LANGID, :sdword
GdipGetStringFormatDigitSubstitution proto WINAPI :ptr, :ptr, :ptr
GdipGetStringFormatMeasurableCharacterRangeCount proto WINAPI :ptr, :ptr
GdipSetStringFormatMeasurableCharacterRanges proto WINAPI :ptr, :sdword, :ptr

GdipCreateCachedBitmap proto WINAPI :ptr, :ptr, :ptr
GdipDeleteCachedBitmap proto WINAPI :ptr
GdipDrawCachedBitmap proto WINAPI :ptr, :ptr, :sdword, :sdword
GdipEmfToWmfBits proto WINAPI :HENHMETAFILE, :dword, :ptr, :sdword, :sdword
GdipSetImageAttributesCachedBackground proto WINAPI :ptr, :BOOL
GdipTestControl proto WINAPI :sdword, :ptr
GdiplusNotificationHook proto WINAPI :ptr
GdiplusNotificationUnhook proto WINAPI :ULONG_PTR

if (GDIPVER GE 0x0110)
GdipConvertToEmfPlus proto WINAPI :ptr, :ptr, :ptr, :sdword, :ptr, :ptr
GdipConvertToEmfPlusToFile proto WINAPI :ptr, :ptr, :ptr, :ptr, :sdword, :ptr, :ptr
GdipConvertToEmfPlusToStream proto WINAPI :ptr, :ptr, :ptr, :ptr, :sdword, :ptr, :ptr
endif
endif
endif
