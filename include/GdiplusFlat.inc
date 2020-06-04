ifndef _FLATAPI_H
_FLATAPI_H equ <>

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;WINGDIPAPI		 equ __stdcall
;GDIPCONST		 equ <>

;GpStatus
GdipCreatePath proto WINAPI \
	     brushMode: FillMode,
		  path: ptr


;GpStatus
GdipCreatePath2 proto WINAPI \
		      : ptr,
		      : ptr,
		      : SINT,
		      : FillMode,
		  path: ptr


;GpStatus
GdipCreatePath2I proto WINAPI \
		      : ptr,
		      : ptr,
		      : SINT,
		      : FillMode,
		  path: ptr


;GpStatus
GdipClonePath proto WINAPI \
		  path: ptr,
	     clonePath: ptr


;GpStatus
GdipDeletePath proto WINAPI \
		  path: ptr


;GpStatus
GdipResetPath proto WINAPI \
		  path: ptr


;GpStatus
GdipGetPointCount proto WINAPI \
		  path: ptr,
		 count: ptr SINT


;GpStatus
GdipGetPathTypes proto WINAPI \
		  path: ptr,
		 types: ptr,
		 count: SINT


;GpStatus
GdipGetPathPoints proto WINAPI \
		      : ptr,
		points: ptr,
		 count: SINT


;GpStatus
GdipGetPathPointsI proto WINAPI \
		      : ptr,
		points: ptr,
		 count: SINT


;GpStatus
GdipGetPathFillMode proto WINAPI \
		  path: ptr,
	      fillmode: ptr GpFillMode


;GpStatus
GdipSetPathFillMode proto WINAPI \
		  path: ptr,
	      fillmode: GpFillMode


;GpStatus
GdipGetPathData proto WINAPI \
		  path: ptr,
	      pathData: ptr


;GpStatus
GdipStartPathFigure proto WINAPI \
		  path: ptr


;GpStatus
GdipClosePathFigure proto WINAPI \
		  path: ptr


;GpStatus
GdipClosePathFigures proto WINAPI \
		  path: ptr


;GpStatus
GdipSetPathMarker proto WINAPI \
		  path: ptr


;GpStatus
GdipClearPathMarkers proto WINAPI \
		  path: ptr


;GpStatus
GdipReversePath proto WINAPI \
		  path: ptr


;GpStatus
GdipGetPathLastPoint proto WINAPI \
		  path: ptr,
	     lastPoint: ptr


;GpStatus
GdipAddPathLine proto WINAPI \
		  path: ptr,
		    x1: REAL,
		    y1: REAL,
		    x2: REAL,
		    y2: REAL


;GpStatus
GdipAddPathLine2 proto WINAPI \
		  path: ptr,
		points: ptr GpPointF,
		 count: SINT


;GpStatus
GdipAddPathArc proto WINAPI \
		  path: ptr,
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL,
	    startAngle: REAL,
	    sweepAngle: REAL


;GpStatus
GdipAddPathBezier proto WINAPI \
		  path: ptr,
		    x1: REAL,
		    y1: REAL,
		    x2: REAL,
		    y2: REAL,
		    x3: REAL,
		    y3: REAL,
		    x4: REAL,
		    y4: REAL


;GpStatus
GdipAddPathBeziers proto WINAPI \
		  path: ptr,
		points: ptr GpPointF,
		 count: SINT


;GpStatus
GdipAddPathCurve proto WINAPI \
		  path: ptr,
		points: ptr GpPointF,
		 count: SINT


;GpStatus
GdipAddPathCurve2 proto WINAPI \
		  path: ptr,
		points: ptr GpPointF,
		 count: SINT,
	       tension: REAL


;GpStatus
GdipAddPathCurve3 proto WINAPI \
		  path: ptr,
		points: ptr GpPointF,
		 count: SINT,
	       _offset: SINT,
      numberOfSegments: SINT,
	       tension: REAL


;GpStatus
GdipAddPathClosedCurve proto WINAPI \
		  path: ptr,
		points: ptr GpPointF,
		 count: SINT


;GpStatus
GdipAddPathClosedCurve2 proto WINAPI \
		  path: ptr,
		points: ptr GpPointF,
		 count: SINT,
	       tension: REAL


;GpStatus
GdipAddPathRectangle proto WINAPI \
		  path: ptr,
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL


;GpStatus
GdipAddPathRectangles proto WINAPI \
		  path: ptr,
		 rects: ptr GpRectF,
		 count: SINT


;GpStatus
GdipAddPathEllipse proto WINAPI \
		  path: ptr,
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL


;GpStatus
GdipAddPathPie proto WINAPI \
		  path: ptr,
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL,
	    startAngle: REAL,
	    sweepAngle: REAL


;GpStatus
GdipAddPathPolygon proto WINAPI \
		  path: ptr,
		points: ptr GpPointF,
		 count: SINT


;GpStatus
GdipAddPathPath proto WINAPI \
		  path: ptr,
	    addingPath: ptr,
	       connect: BOOL


;GpStatus
GdipAddPathString proto WINAPI \
		  path: ptr,
		string: ptr WCHAR,
		length: SINT,
		family: ptr GpFontFamily,
		 style: SINT,
		emSize: REAL,
	    layoutRect: ptr RectF,
		format: ptr GpStringFormat


;GpStatus
GdipAddPathStringI proto WINAPI \
		  path: ptr,
		string: ptr WCHAR,
		length: SINT,
		family: ptr GpFontFamily,
		 style: SINT,
		emSize: REAL,
	    layoutRect: ptr Rect,
		format: ptr GpStringFormat


;GpStatus
GdipAddPathLineI proto WINAPI \
		  path: ptr,
		    x1: SINT,
		    y1: SINT,
		    x2: SINT,
		    y2: SINT


;GpStatus
GdipAddPathLine2I proto WINAPI \
		  path: ptr,
		points: ptr GpPoint,
		 count: SINT


;GpStatus
GdipAddPathArcI proto WINAPI \
		  path: ptr,
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT,
	    startAngle: REAL,
	    sweepAngle: REAL


;GpStatus
GdipAddPathBezierI proto WINAPI \
		  path: ptr,
		    x1: SINT,
		    y1: SINT,
		    x2: SINT,
		    y2: SINT,
		    x3: SINT,
		    y3: SINT,
		    x4: SINT,
		    y4: SINT


;GpStatus
GdipAddPathBeziersI proto WINAPI \
		  path: ptr,
		points: ptr GpPoint,
		 count: SINT


;GpStatus
GdipAddPathCurveI proto WINAPI \
		  path: ptr,
		points: ptr GpPoint,
		 count: SINT


;GpStatus
GdipAddPathCurve2I proto WINAPI \
		  path: ptr,
		points: ptr GpPoint,
		 count: SINT,
	       tension: REAL


;GpStatus
GdipAddPathCurve3I proto WINAPI \
		  path: ptr,
		points: ptr GpPoint,
		 count: SINT,
	       _offset: SINT,
      numberOfSegments: SINT,
	       tension: REAL


;GpStatus
GdipAddPathClosedCurveI proto WINAPI \
		  path: ptr,
		points: ptr GpPoint,
		 count: SINT


;GpStatus
GdipAddPathClosedCurve2I proto WINAPI \
		  path: ptr,
		points: ptr GpPoint,
		 count: SINT,
	       tension: REAL


;GpStatus
GdipAddPathRectangleI proto WINAPI \
		  path: ptr,
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT


;GpStatus
GdipAddPathRectanglesI proto WINAPI \
		  path: ptr,
		 rects: ptr GpRect,
		 count: SINT


;GpStatus
GdipAddPathEllipseI proto WINAPI \
		  path: ptr,
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT


;GpStatus
GdipAddPathPieI proto WINAPI \
		  path: ptr,
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT,
	    startAngle: REAL,
	    sweepAngle: REAL


;GpStatus
GdipAddPathPolygonI proto WINAPI \
		  path: ptr,
		points: ptr GpPoint,
		 count: SINT


;GpStatus
GdipFlattenPath proto WINAPI \
		  path: ptr,
		matrix: ptr,
	      flatness: REAL


;GpStatus
GdipWindingModeOutline proto WINAPI \
		  path: ptr,
		matrix: ptr GpMatrix,
	      flatness: REAL


;GpStatus
GdipWidenPath proto WINAPI \
	    nativePath: ptr,
		   pen: ptr GpPen,
		matrix: ptr GpMatrix,
	      flatness: REAL


;GpStatus
GdipWarpPath proto WINAPI \
		  path: ptr,
		matrix: ptr,
		points: ptr GpPointF,
		 count: SINT,
		  srcx: REAL,
		  srcy: REAL,
	      srcwidth: REAL,
	     srcheight: REAL,
	      warpMode: WarpMode,
	      flatness: REAL


;GpStatus
GdipTransformPath proto WINAPI \
		  path: ptr,
		matrix: ptr


;GpStatus
GdipGetPathWorldBounds proto WINAPI \
		  path: ptr,
		bounds: ptr,
		matrix: ptr GpMatrix,
		   pen: ptr GpPen


;GpStatus
GdipGetPathWorldBoundsI proto WINAPI \
		  path: ptr,
		bounds: ptr,
		matrix: ptr GpMatrix,
		   pen: ptr GpPen


;GpStatus
GdipIsVisiblePathPoint proto WINAPI \
		  path: ptr,
		     x: REAL,
		     y: REAL,
	      graphics: ptr GpGraphics,
		result: ptr BOOL


;GpStatus
GdipIsVisiblePathPointI proto WINAPI \
		  path: ptr,
		     x: SINT,
		     y: SINT,
	      graphics: ptr GpGraphics,
		result: ptr BOOL


;GpStatus
GdipIsOutlineVisiblePathPoint proto WINAPI \
		  path: ptr,
		     x: REAL,
		     y: REAL,
		   pen: ptr GpPen,
	      graphics: ptr GpGraphics,
		result: ptr BOOL


;GpStatus
GdipIsOutlineVisiblePathPointI proto WINAPI \
		  path: ptr,
		     x: SINT,
		     y: SINT,
		   pen: ptr GpPen,
	      graphics: ptr GpGraphics,
		result: ptr BOOL


;GpStatus
GdipCreatePathIter proto WINAPI \
	      iterator: ptr,
		  path: ptr


;GpStatus
GdipDeletePathIter proto WINAPI \
	      iterator: ptr


;GpStatus
GdipPathIterNextSubpath proto WINAPI \
	      iterator: ptr,
	   resultCount: ptr SINT,
	    startIndex: ptr,
	      endIndex: ptr,
	      isClosed: ptr


;GpStatus
GdipPathIterNextSubpathPath proto WINAPI \
	      iterator: ptr,
	   resultCount: ptr,
		  path: ptr,
	      isClosed: ptr


;GpStatus
GdipPathIterNextPathType proto WINAPI \
	      iterator: ptr,
	   resultCount: ptr,
	      pathType: ptr,
	    startIndex: ptr,
	      endIndex: ptr


;GpStatus
GdipPathIterNextMarker proto WINAPI \
	      iterator: ptr,
	   resultCount: ptr SINT,
	    startIndex: ptr,
	      endIndex: ptr


;GpStatus
GdipPathIterNextMarkerPath proto WINAPI \
	      iterator: ptr,
	   resultCount: ptr,
		  path: ptr


;GpStatus
GdipPathIterGetCount proto WINAPI \
	      iterator: ptr,
		 count: ptr


;GpStatus
GdipPathIterGetSubpathCount proto WINAPI \
	      iterator: ptr,
		 count: ptr


;GpStatus
GdipPathIterIsValid proto WINAPI \
	      iterator: ptr,
		 valid: ptr


;GpStatus
GdipPathIterHasCurve proto WINAPI \
	      iterator: ptr,
	      hasCurve: ptr


;GpStatus
GdipPathIterRewind proto WINAPI \
	      iterator: ptr


;GpStatus
GdipPathIterEnumerate proto WINAPI \
	      iterator: ptr,
	   resultCount: ptr,
		points: ptr GpPointF,
		 types: ptr BYTE,
		 count: SINT


;GpStatus
GdipPathIterCopyData proto WINAPI \
	      iterator: ptr,
	   resultCount: ptr,
		points: ptr,
		 types: ptr,
	    startIndex: SINT,
	      endIndex: SINT


;;----------------------------------------------------------------------------
;; Matrix APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipCreateMatrix proto WINAPI \
		matrix: ptr GpMatrix


;GpStatus
GdipCreateMatrix2 proto WINAPI \
		   m11: REAL,
		   m12: REAL,
		   m21: REAL,
		   m22: REAL,
		   _dx: REAL,
		    dy: REAL,
		matrix: ptr GpMatrix


;GpStatus
GdipCreateMatrix3 proto WINAPI \
		  rect: ptr GpRectF,
		dstplg: ptr GpPointF,
		matrix: ptr GpMatrix


;GpStatus
GdipCreateMatrix3I proto WINAPI \
		  rect: ptr GpRect,
		dstplg: ptr GpPoint,
		matrix: ptr GpMatrix


;GpStatus
GdipCloneMatrix proto WINAPI \
		matrix: ptr GpMatrix,
	   cloneMatrix: ptr GpMatrix


;GpStatus
GdipDeleteMatrix proto WINAPI \
		matrix: ptr GpMatrix


;GpStatus
GdipSetMatrixElements proto WINAPI \
		matrix: ptr GpMatrix,
		   m11: REAL,
		   m12: REAL,
		   m21: REAL,
		   m22: REAL,
		   _dx: REAL,
		    dy: REAL


;GpStatus
GdipMultiplyMatrix proto WINAPI \
		matrix: ptr GpMatrix,
	       matrix2: ptr,
		 order: ptr


;GpStatus
GdipTranslateMatrix proto WINAPI \
		matrix: ptr GpMatrix,
	       offsetX: REAL,
	       offsetY: REAL,
		 order: ptr


;GpStatus
GdipScaleMatrix proto WINAPI \
		matrix: ptr GpMatrix,
		scaleX: REAL,
		scaleY: REAL,
		 order: ptr


;GpStatus
GdipRotateMatrix proto WINAPI \
		matrix: ptr GpMatrix,
		 angle: REAL,
		 order: ptr


;GpStatus
GdipShearMatrix proto WINAPI \
		matrix: ptr GpMatrix,
		shearX: REAL,
		shearY: REAL,
		 order: ptr


;GpStatus
GdipInvertMatrix proto WINAPI \
		matrix: ptr GpMatrix


;GpStatus
GdipTransformMatrixPoints proto WINAPI \
		matrix: ptr GpMatrix,
		   pts: ptr GpPointF,
		 count: SINT


;GpStatus
GdipTransformMatrixPointsI proto WINAPI \
		matrix: ptr GpMatrix,
		   pts: ptr GpPoint,
		 count: SINT


;GpStatus
GdipVectorTransformMatrixPoints proto WINAPI \
		matrix: ptr GpMatrix,
		   pts: ptr GpPointF,
		 count: SINT


;GpStatus
GdipVectorTransformMatrixPointsI proto WINAPI \
		matrix: ptr GpMatrix,
		   pts: ptr GpPoint,
		 count: SINT


;GpStatus
GdipGetMatrixElements proto WINAPI \
		matrix: ptr GpMatrix,
	     matrixOut: ptr REAL


;GpStatus
GdipIsMatrixInvertible proto WINAPI \
		matrix: ptr GpMatrix,
		result: ptr BOOL


;GpStatus
GdipIsMatrixIdentity proto WINAPI \
		matrix: ptr GpMatrix,
		result: ptr BOOL


;GpStatus
GdipIsMatrixEqual proto WINAPI \
		matrix: ptr GpMatrix,
	       matrix2: ptr GpMatrix,
		result: ptr BOOL


;;----------------------------------------------------------------------------
;; Region APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipCreateRegion proto WINAPI \
		region: ptr GpRegion


;GpStatus
GdipCreateRegionRect proto WINAPI \
		  rect: ptr GpRectF,
		region: ptr GpRegion


;GpStatus
GdipCreateRegionRectI proto WINAPI \
		  rect: ptr GpRect,
		region: ptr GpRegion


;GpStatus
GdipCreateRegionPath proto WINAPI \
		  path: ptr,
		region: ptr GpRegion


;GpStatus
GdipCreateRegionRgnData proto WINAPI \
	    regionData: ptr BYTE,
		  size: SINT,
		region: ptr GpRegion


;GpStatus
GdipCreateRegionHrgn proto WINAPI \
		  hRgn: HRGN,
		region: ptr GpRegion


;GpStatus
GdipCloneRegion proto WINAPI \
		region: ptr GpRegion,
	   cloneRegion: ptr GpRegion


;GpStatus
GdipDeleteRegion proto WINAPI \
		region: ptr GpRegion


;GpStatus
GdipSetInfinite proto WINAPI \
		region: ptr GpRegion


;GpStatus
GdipSetEmpty proto WINAPI \
		region: ptr GpRegion


;GpStatus
GdipCombineRegionRect proto WINAPI \
		region: ptr GpRegion,
		  rect: ptr GpRectF,
	   combineMode: CombineMode


;GpStatus
GdipCombineRegionRectI proto WINAPI \
		region: ptr GpRegion,
		  rect: ptr GpRect,
	   combineMode: CombineMode


;GpStatus
GdipCombineRegionPath proto WINAPI \
		region: ptr GpRegion,
		  path: ptr,
	   combineMode: CombineMode


;GpStatus
GdipCombineRegionRegion proto WINAPI \
		region: ptr GpRegion,
	       region2: ptr GpRegion,
	   combineMode: CombineMode


;GpStatus
GdipTranslateRegion proto WINAPI \
		region: ptr GpRegion,
		   _dx: REAL,
		    dy: REAL


;GpStatus
GdipTranslateRegionI proto WINAPI \
		region: ptr GpRegion,
		   _dx: SINT,
		    dy: SINT


;GpStatus
GdipTransformRegion proto WINAPI \
		region: ptr GpRegion,
		matrix: ptr GpMatrix


;GpStatus
GdipGetRegionBounds proto WINAPI \
		region: ptr GpRegion,
	      graphics: ptr GpGraphics,
		  rect: ptr GpRectF


;GpStatus
GdipGetRegionBoundsI proto WINAPI \
		region: ptr GpRegion,
	      graphics: ptr GpGraphics,
		  rect: ptr GpRect


;GpStatus
GdipGetRegionHRgn proto WINAPI \
		region: ptr GpRegion,
	      graphics: ptr GpGraphics,
		  hRgn: ptr HRGN


;GpStatus
GdipIsEmptyRegion proto WINAPI \
		region: ptr GpRegion,
	      graphics: ptr GpGraphics,
		result: ptr BOOL


;GpStatus
GdipIsInfiniteRegion proto WINAPI \
		region: ptr GpRegion,
	      graphics: ptr GpGraphics,
		result: ptr BOOL


;GpStatus
GdipIsEqualRegion proto WINAPI \
		region: ptr GpRegion,
	       region2: ptr GpRegion,
	      graphics: ptr GpGraphics,
		result: ptr BOOL


;GpStatus
GdipGetRegionDataSize proto WINAPI \
		region: ptr GpRegion,
	    bufferSize: ptr


;GpStatus
GdipGetRegionData proto WINAPI \
		region: ptr GpRegion,
		buffer: ptr,
	    bufferSize: UINT,
	    sizeFilled: ptr UINT


;GpStatus
GdipIsVisibleRegionPoint proto WINAPI \
		region: ptr GpRegion,
		     x: REAL,
		     y: REAL,
	      graphics: ptr GpGraphics,
		result: ptr BOOL


;GpStatus
GdipIsVisibleRegionPointI proto WINAPI \
		region: ptr GpRegion,
		     x: SINT,
		     y: SINT,
	      graphics: ptr GpGraphics,
		result: ptr BOOL


;GpStatus
GdipIsVisibleRegionRect proto WINAPI \
		region: ptr GpRegion,
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL,
	      graphics: ptr GpGraphics,
		result: ptr BOOL


;GpStatus
GdipIsVisibleRegionRectI proto WINAPI \
		region: ptr GpRegion,
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT,
	      graphics: ptr GpGraphics,
		result: ptr BOOL


;GpStatus
GdipGetRegionScansCount proto WINAPI \
		region: ptr GpRegion,
		 count: ptr,
		matrix: ptr


;GpStatus
GdipGetRegionScans proto WINAPI \
		region: ptr GpRegion,
		 rects: ptr,
		 count: ptr,
		matrix: ptr


;GpStatus
GdipGetRegionScansI proto WINAPI \
		region: ptr GpRegion,
		 rects: ptr,
		 count: ptr,
		matrix: ptr


;;----------------------------------------------------------------------------
;; Brush APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipCloneBrush proto WINAPI \
		 brush: ptr GpBrush,
	    cloneBrush: ptr GpBrush


;GpStatus
GdipDeleteBrush proto WINAPI \
		 brush: ptr GpBrush


;GpStatus
GdipGetBrushType proto WINAPI \
		 brush: ptr GpBrush,
		  type: ptr GpBrushType


;;----------------------------------------------------------------------------
;; HatchBrush APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipCreateHatchBrush proto WINAPI \
	    hatchstyle: HatchStyle,
	       forecol: ARGB,
	       backcol: ARGB,
		 brush: ptr GpHatch


;GpStatus
GdipGetHatchStyle proto WINAPI \
		 brush: ptr GpHatch,
	    hatchstyle: ptr GpHatchStyle


;GpStatus
GdipGetHatchForegroundColor proto WINAPI \
		 brush: ptr GpHatch,
	       forecol: ptr


;GpStatus
GdipGetHatchBackgroundColor proto WINAPI \
		 brush: ptr GpHatch,
	       backcol: ptr


;;----------------------------------------------------------------------------
;; TextureBrush APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipCreateTexture proto WINAPI \
		 image: ptr GpImage,
	      wrapmode: GpWrapMode,
	       texture: ptr GpTexture


;GpStatus
GdipCreateTexture2 proto WINAPI \
		 image: ptr GpImage,
	      wrapmode: GpWrapMode,
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL,
	       texture: ptr GpTexture


;GpStatus
GdipCreateTextureIA proto WINAPI \
		 image: ptr GpImage,
       imageAttributes: ptr GpImageAttributes,
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL,
	       texture: ptr GpTexture


;GpStatus
GdipCreateTexture2I proto WINAPI \
		 image: ptr GpImage,
	      wrapmode: GpWrapMode,
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT,
	       texture: ptr GpTexture


;GpStatus
GdipCreateTextureIAI proto WINAPI \
		 image: ptr GpImage,
       imageAttributes: ptr GpImageAttributes,
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT,
	       texture: ptr GpTexture



;GpStatus
GdipGetTextureTransform proto WINAPI \
		 brush: ptr GpTexture,
		matrix: ptr GpMatrix


;GpStatus
GdipSetTextureTransform proto WINAPI \
		 brush: ptr GpTexture,
		matrix: ptr GpMatrix


;GpStatus
GdipResetTextureTransform proto WINAPI \
		 brush: ptr


;GpStatus
GdipMultiplyTextureTransform proto WINAPI \
		 brush: ptr,
		matrix: ptr GpMatrix,
		 order: GpMatrixOrder


;GpStatus
GdipTranslateTextureTransform proto WINAPI \
		 brush: ptr,
		   _dx: REAL,
		    dy: REAL,
		 order: GpMatrixOrder


;GpStatus
GdipScaleTextureTransform proto WINAPI \
		 brush: ptr,
		    sx: REAL,
		    sy: REAL,
		 order: GpMatrixOrder


;GpStatus
GdipRotateTextureTransform proto WINAPI \
		 brush: ptr,
		 angle: REAL,
		 order: GpMatrixOrder


;GpStatus
GdipSetTextureWrapMode proto WINAPI \
		 brush: ptr GpTexture,
	      wrapmode: GpWrapMode


;GpStatus
GdipGetTextureWrapMode proto WINAPI \
		 brush: ptr GpTexture,
	      wrapmode: ptr GpWrapMode


;GpStatus
GdipGetTextureImage proto WINAPI \
		 brush: ptr GpTexture,
		 image: ptr GpImage


;;----------------------------------------------------------------------------
;; SolidBrush APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipCreateSolidFill proto WINAPI \
		 color: ARGB,
		 brush: ptr GpSolidFill


;GpStatus
GdipSetSolidFillColor proto WINAPI \
		 brush: ptr GpSolidFill,
		 color: ARGB


;GpStatus
GdipGetSolidFillColor proto WINAPI \
		 brush: ptr GpSolidFill,
		 color: ptr ARGB


;;----------------------------------------------------------------------------
;; LineBrush APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipCreateLineBrush proto WINAPI \
		point1: ptr,
		point2: ptr,
		color1: ARGB,
		color2: ARGB,
	      wrapMode: GpWrapMode,
	  lineGradient: ptr GpLineGradient


;GpStatus
GdipCreateLineBrushI proto WINAPI \
		point1: ptr,
		point2: ptr,
		color1: ARGB,
		color2: ARGB,
	      wrapMode: GpWrapMode,
	  lineGradient: ptr GpLineGradient


;GpStatus
GdipCreateLineBrushFromRect proto WINAPI \
		  rect: ptr,
		color1: ARGB,
		color2: ARGB,
		  mode: LinearGradientMode,
	      wrapMode: GpWrapMode,
	  lineGradient: ptr GpLineGradient


;GpStatus
GdipCreateLineBrushFromRectI proto WINAPI \
		  rect: ptr,
		color1: ARGB,
		color2: ARGB,
		  mode: LinearGradientMode,
	      wrapMode: GpWrapMode,
	  lineGradient: ptr GpLineGradient


;GpStatus
GdipCreateLineBrushFromRectWithAngle proto WINAPI \
		  rect: ptr,
		color1: ARGB,
		color2: ARGB,
		 angle: REAL,
       isAngleScalable: BOOL,
	      wrapMode: GpWrapMode,
	  lineGradient: ptr GpLineGradient


;GpStatus
GdipCreateLineBrushFromRectWithAngleI proto WINAPI \
		  rect: ptr,
		color1: ARGB,
		color2: ARGB,
		 angle: REAL,
       isAngleScalable: BOOL,
	      wrapMode: GpWrapMode,
	  lineGradient: ptr GpLineGradient


;GpStatus
GdipSetLineColors proto WINAPI \
		 brush: ptr GpLineGradient,
		color1: ARGB,
		color2: ARGB


;GpStatus
GdipGetLineColors proto WINAPI \
		 brush: ptr GpLineGradient,
		colors: ptr


;GpStatus
GdipGetLineRect proto WINAPI \
		 brush: ptr GpLineGradient,
		  rect: ptr GpRectF


;GpStatus
GdipGetLineRectI proto WINAPI \
		 brush: ptr GpLineGradient,
		  rect: ptr GpRect


;GpStatus
GdipSetLineGammaCorrection proto WINAPI \
		 brush: ptr GpLineGradient,
    useGammaCorrection: BOOL


;GpStatus
GdipGetLineGammaCorrection proto WINAPI \
		 brush: ptr GpLineGradient,
    useGammaCorrection: ptr BOOL


;GpStatus
GdipGetLineBlendCount proto WINAPI \
		 brush: ptr GpLineGradient,
		 count: ptr SINT


;GpStatus
GdipGetLineBlend proto WINAPI \
		 brush: ptr GpLineGradient,
		 blend: ptr REAL,
	     positions: ptr,
		 count: SINT


;GpStatus
GdipSetLineBlend proto WINAPI \
		 brush: ptr GpLineGradient,
		 blend: ptr REAL,
	     positions: ptr,
		 count: SINT


;GpStatus
GdipGetLinePresetBlendCount proto WINAPI \
		 brush: ptr GpLineGradient,
		 count: ptr SINT


;GpStatus
GdipGetLinePresetBlend proto WINAPI \
		 brush: ptr GpLineGradient,
		 blend: ptr ARGB,
	     positions: ptr,
		 count: SINT


;GpStatus
GdipSetLinePresetBlend proto WINAPI \
		 brush: ptr GpLineGradient,
		 blend: ptr ARGB,
	     positions: ptr,
		 count: SINT


;GpStatus
GdipSetLineSigmaBlend proto WINAPI \
		 brush: ptr GpLineGradient,
		 focus: REAL,
		 scale: REAL


;GpStatus
GdipSetLineLinearBlend proto WINAPI \
		 brush: ptr GpLineGradient,
		 focus: REAL,
		 scale: REAL


;GpStatus
GdipSetLineWrapMode proto WINAPI \
		 brush: ptr GpLineGradient,
	      wrapmode: GpWrapMode


;GpStatus
GdipGetLineWrapMode proto WINAPI \
		 brush: ptr GpLineGradient,
	      wrapmode: ptr GpWrapMode


;GpStatus
GdipGetLineTransform proto WINAPI \
		 brush: ptr GpLineGradient,
		matrix: ptr GpMatrix


;GpStatus
GdipSetLineTransform proto WINAPI \
		 brush: ptr GpLineGradient,
		matrix: ptr GpMatrix


;GpStatus
GdipResetLineTransform proto WINAPI \
		 brush: ptr


;GpStatus
GdipMultiplyLineTransform proto WINAPI \
		 brush: ptr,
		matrix: ptr GpMatrix,
		 order: GpMatrixOrder


;GpStatus
GdipTranslateLineTransform proto WINAPI \
		 brush: ptr,
		   _dx: REAL,
		    dy: REAL,
		 order: GpMatrixOrder


;GpStatus
GdipScaleLineTransform proto WINAPI \
		 brush: ptr,
		    sx: REAL,
		    sy: REAL,
		 order: GpMatrixOrder


;GpStatus
GdipRotateLineTransform proto WINAPI \
		 brush: ptr,
		 angle: REAL,
		 order: GpMatrixOrder


;;----------------------------------------------------------------------------
;; PathGradientBrush APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipCreatePathGradient proto WINAPI \
		points: ptr,
		 count: SINT,
	      wrapMode: GpWrapMode,
	  polyGradient: ptr


;GpStatus
GdipCreatePathGradientI proto WINAPI \
		points: ptr,
		 count: SINT,
	      wrapMode: GpWrapMode,
	  polyGradient: ptr


;GpStatus
GdipCreatePathGradientFromPath proto WINAPI \
		  path: ptr,
	  polyGradient: ptr


;GpStatus
GdipGetPathGradientCenterColor proto WINAPI \
		 brush: ptr,
		colors: ptr


;GpStatus
GdipSetPathGradientCenterColor proto WINAPI \
		 brush: ptr,
		colors: ARGB


;GpStatus
GdipGetPathGradientSurroundColorsWithCount proto WINAPI \
		 brush: ptr,
		 color: ptr,
		 count: ptr


;GpStatus
GdipSetPathGradientSurroundColorsWithCount proto WINAPI \
		 brush: ptr,
		 color: ptr,
		 count: ptr


;GpStatus
GdipGetPathGradientPath proto WINAPI \
		 brush: ptr,
		  path: ptr


;GpStatus
GdipSetPathGradientPath proto WINAPI \
		 brush: ptr,
		  path: ptr


;GpStatus
GdipGetPathGradientCenterPoint proto WINAPI \
		 brush: ptr,
		points: ptr


;GpStatus
GdipGetPathGradientCenterPointI proto WINAPI \
		 brush: ptr,
		points: ptr


;GpStatus
GdipSetPathGradientCenterPoint proto WINAPI \
		 brush: ptr,
		points: ptr


;GpStatus
GdipSetPathGradientCenterPointI proto WINAPI \
		 brush: ptr,
		points: ptr


;GpStatus
GdipGetPathGradientRect proto WINAPI \
		 brush: ptr,
		  rect: ptr GpRectF


;GpStatus
GdipGetPathGradientRectI proto WINAPI \
		 brush: ptr,
		  rect: ptr GpRect


;GpStatus
GdipGetPathGradientPointCount proto WINAPI \
		 brush: ptr,
		 count: ptr


;GpStatus
GdipGetPathGradientSurroundColorCount proto WINAPI \
		 brush: ptr,
		 count: ptr


;GpStatus
GdipSetPathGradientGammaCorrection proto WINAPI \
		 brush: ptr,
    useGammaCorrection: BOOL


;GpStatus
GdipGetPathGradientGammaCorrection proto WINAPI \
		 brush: ptr,
    useGammaCorrection: ptr BOOL


;GpStatus
GdipGetPathGradientBlendCount proto WINAPI \
		 brush: ptr,
		 count: ptr SINT


;GpStatus
GdipGetPathGradientBlend proto WINAPI \
		 brush: ptr,
		 blend: ptr REAL,
	     positions: ptr REAL,
		 count: SINT


;GpStatus
GdipSetPathGradientBlend proto WINAPI \
		 brush: ptr,
		 blend: ptr REAL,
	     positions: ptr REAL,
		 count: SINT


;GpStatus
GdipGetPathGradientPresetBlendCount proto WINAPI \
		 brush: ptr,
		 count: ptr SINT


;GpStatus
GdipGetPathGradientPresetBlend proto WINAPI \
		 brush: ptr,
		 blend: ptr ARGB,
	     positions: ptr,
		 count: SINT


;GpStatus
GdipSetPathGradientPresetBlend proto WINAPI \
		 brush: ptr,
		 blend: ptr ARGB,
	     positions: ptr,
		 count: SINT


;GpStatus
GdipSetPathGradientSigmaBlend proto WINAPI \
		 brush: ptr,
		 focus: REAL,
		 scale: REAL


;GpStatus
GdipSetPathGradientLinearBlend proto WINAPI \
		 brush: ptr,
		 focus: REAL,
		 scale: REAL


;GpStatus
GdipGetPathGradientWrapMode proto WINAPI \
		 brush: ptr,
	      wrapmode: ptr GpWrapMode


;GpStatus
GdipSetPathGradientWrapMode proto WINAPI \
		 brush: ptr,
	      wrapmode: GpWrapMode


;GpStatus
GdipGetPathGradientTransform proto WINAPI \
		 brush: ptr,
		matrix: ptr GpMatrix


;GpStatus
GdipSetPathGradientTransform proto WINAPI \
		 brush: ptr,
		matrix: ptr GpMatrix


;GpStatus
GdipResetPathGradientTransform proto WINAPI \
		 brush: ptr


;GpStatus
GdipMultiplyPathGradientTransform proto WINAPI \
		 brush: ptr,
		matrix: ptr GpMatrix,
		 order: GpMatrixOrder


;GpStatus
GdipTranslatePathGradientTransform proto WINAPI \
		 brush: ptr,
		   _dx: REAL,
		    dy: REAL,
		 order: GpMatrixOrder


;GpStatus
GdipScalePathGradientTransform proto WINAPI \
		 brush: ptr,
		    sx: REAL,
		    sy: REAL,
		 order: GpMatrixOrder


;GpStatus
GdipRotatePathGradientTransform proto WINAPI \
		 brush: ptr,
		 angle: REAL,
		 order: GpMatrixOrder


;GpStatus
GdipGetPathGradientFocusScales proto WINAPI \
		 brush: ptr,
		xScale: ptr,
		yScale: ptr


;GpStatus
GdipSetPathGradientFocusScales proto WINAPI \
		 brush: ptr,
		xScale: REAL,
		yScale: REAL


;;----------------------------------------------------------------------------
;; Pen APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipCreatePen1 proto WINAPI \
		 color: ARGB,
		 width: REAL,
		  unit: GpUnit,
		   pen: ptr GpPen


;GpStatus
GdipCreatePen2 proto WINAPI \
		 brush: ptr GpBrush,
		 width: REAL,
		  unit: GpUnit,
		   pen: ptr GpPen


;GpStatus
GdipClonePen proto WINAPI \
		   pen: ptr GpPen,
	      clonepen: ptr GpPen


;GpStatus
GdipDeletePen proto WINAPI \
		   pen: ptr GpPen


;GpStatus
GdipSetPenWidth proto WINAPI \
		   pen: ptr GpPen,
		 width: REAL


;GpStatus
GdipGetPenWidth proto WINAPI \
		   pen: ptr GpPen,
		 width: ptr REAL


;GpStatus
GdipSetPenUnit proto WINAPI \
		   pen: ptr GpPen,
		  unit: ptr


;GpStatus
GdipGetPenUnit proto WINAPI \
		   pen: ptr GpPen,
		  unit: ptr GpUnit


;GpStatus
GdipSetPenLineCap197819 proto WINAPI \
		   pen: ptr GpPen,
	      startCap: GpLineCap,
		endCap: GpLineCap,
	       dashCap: GpDashCap


;GpStatus
GdipSetPenStartCap proto WINAPI \
		   pen: ptr GpPen,
	      startCap: GpLineCap


;GpStatus
GdipSetPenEndCap proto WINAPI \
		   pen: ptr GpPen,
		endCap: GpLineCap


;GpStatus
GdipSetPenDashCap197819 proto WINAPI \
		   pen: ptr GpPen,
	       dashCap: GpDashCap


;GpStatus
GdipGetPenStartCap proto WINAPI \
		   pen: ptr GpPen,
	      startCap: GpLineCap


;GpStatus
GdipGetPenEndCap proto WINAPI \
		   pen: ptr GpPen,
		endCap: GpLineCap


;GpStatus
GdipGetPenDashCap197819 proto WINAPI \
		   pen: ptr GpPen,
	       dashCap: GpDashCap


;GpStatus
GdipSetPenLineJoin proto WINAPI \
		   pen: ptr GpPen,
	      lineJoin: GpLineJoin


;GpStatus
GdipGetPenLineJoin proto WINAPI \
		   pen: ptr GpPen,
	      lineJoin: GpLineJoin


;GpStatus
GdipSetPenCustomStartCap proto WINAPI \
		   pen: ptr GpPen,
	     customCap: ptr


;GpStatus
GdipGetPenCustomStartCap proto WINAPI \
		   pen: ptr GpPen,
	     customCap: ptr


;GpStatus
GdipSetPenCustomEndCap proto WINAPI \
		   pen: ptr GpPen,
	     customCap: ptr


;GpStatus
GdipGetPenCustomEndCap proto WINAPI \
		   pen: ptr GpPen,
	     customCap: ptr


;GpStatus
GdipSetPenMiterLimit proto WINAPI \
		   pen: ptr GpPen,
	    miterLimit: REAL


;GpStatus
GdipGetPenMiterLimit proto WINAPI \
		   pen: ptr GpPen,
	    miterLimit: ptr REAL


;GpStatus
GdipSetPenMode proto WINAPI \
		   pen: ptr GpPen,
	       penMode: GpPenAlignment


;GpStatus
GdipGetPenMode proto WINAPI \
		   pen: ptr GpPen,
	       penMode: ptr GpPenAlignment


;GpStatus
GdipSetPenTransform proto WINAPI \
		   pen: ptr GpPen,
		matrix: ptr GpMatrix


;GpStatus
GdipGetPenTransform proto WINAPI \
		   pen: ptr GpPen,
		matrix: ptr GpMatrix


;GpStatus
GdipResetPenTransform proto WINAPI \
		   pen: ptr GpPen


;GpStatus
GdipMultiplyPenTransform proto WINAPI \
		   pen: ptr GpPen,
		matrix: ptr GpMatrix,
		 order: GpMatrixOrder


;GpStatus
GdipTranslatePenTransform proto WINAPI \
		   pen: ptr GpPen,
		   _dx: REAL,
		    dy: REAL,
		 order: GpMatrixOrder


;GpStatus
GdipScalePenTransform proto WINAPI \
		   pen: ptr GpPen,
		    sx: REAL,
		    sy: REAL,
		 order: GpMatrixOrder


;GpStatus
GdipRotatePenTransform proto WINAPI \
		   pen: ptr GpPen,
		 angle: REAL,
		 order: GpMatrixOrder


;GpStatus
GdipSetPenColor proto WINAPI \
		   pen: ptr GpPen,
		  argb: ARGB


;GpStatus
GdipGetPenColor proto WINAPI \
		   pen: ptr GpPen,
		  argb: ptr ARGB


;GpStatus
GdipSetPenBrushFill proto WINAPI \
		   pen: ptr GpPen,
		 brush: ptr GpBrush


;GpStatus
GdipGetPenBrushFill proto WINAPI \
		   pen: ptr GpPen,
		 brush: ptr GpBrush


;GpStatus
GdipGetPenFillType proto WINAPI \
		   pen: ptr GpPen,
		  type: ptr


;GpStatus
GdipGetPenDashStyle proto WINAPI \
		   pen: ptr GpPen,
	     dashstyle: GpDashStyle


;GpStatus
GdipSetPenDashStyle proto WINAPI \
		   pen: ptr GpPen,
	     dashstyle: GpDashStyle


;GpStatus
GdipGetPenDashOffset proto WINAPI \
		   pen: ptr GpPen,
	       _offset: ptr REAL


;GpStatus
GdipSetPenDashOffset proto WINAPI \
		   pen: ptr GpPen,
	       _offset: REAL


;GpStatus
GdipGetPenDashCount proto WINAPI \
		   pen: ptr GpPen,
		 count: ptr SINT


;GpStatus
GdipSetPenDashArray proto WINAPI \
		   pen: ptr GpPen,
		  dash: ptr REAL,
		 count: SINT


;GpStatus
GdipGetPenDashArray proto WINAPI \
		   pen: ptr GpPen,
		  dash: ptr REAL,
		 count: SINT


;GpStatus
GdipGetPenCompoundCount proto WINAPI \
		   pen: ptr GpPen,
		 count: ptr SINT


;GpStatus
GdipSetPenCompoundArray proto WINAPI \
		   pen: ptr GpPen,
		  dash: ptr REAL,
		 count: SINT


;GpStatus
GdipGetPenCompoundArray proto WINAPI \
		   pen: ptr GpPen,
		  dash: ptr REAL,
		 count: SINT


;;----------------------------------------------------------------------------
;; CustomLineCap APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipCreateCustomLineCap proto WINAPI \
	      fillPath: ptr,
	    strokePath: ptr,
	       baseCap: GpLineCap,
	     baseInset: REAL,
	     customCap: ptr GpCustomLineCap


;GpStatus
GdipDeleteCustomLineCap proto WINAPI \
	     customCap: ptr


;GpStatus
GdipCloneCustomLineCap proto WINAPI \
	     customCap: ptr,
	     clonedCap: ptr


;GpStatus
GdipGetCustomLineCapType proto WINAPI \
	     customCap: ptr,
	       capType: ptr


;GpStatus
GdipSetCustomLineCapStrokeCaps proto WINAPI \
	     customCap: ptr,
	      startCap: GpLineCap,
		endCap: GpLineCap


;GpStatus
GdipGetCustomLineCapStrokeCaps proto WINAPI \
	     customCap: ptr,
	      startCap: ptr GpLineCap,
		endCap: ptr GpLineCap


;GpStatus
GdipSetCustomLineCapStrokeJoin proto WINAPI \
	     customCap: ptr,
	      lineJoin: GpLineJoin


;GpStatus
GdipGetCustomLineCapStrokeJoin proto WINAPI \
	     customCap: ptr,
	      lineJoin: ptr


;GpStatus
GdipSetCustomLineCapBaseCap proto WINAPI \
	     customCap: ptr,
	       baseCap: GpLineCap


;GpStatus
GdipGetCustomLineCapBaseCap proto WINAPI \
	     customCap: ptr,
	       baseCap: ptr


;GpStatus
GdipSetCustomLineCapBaseInset proto WINAPI \
	     customCap: ptr,
		 inset: REAL


;GpStatus
GdipGetCustomLineCapBaseInset proto WINAPI \
	     customCap: ptr,
		 inset: ptr


;GpStatus
GdipSetCustomLineCapWidthScale proto WINAPI \
	     customCap: ptr,
	    widthScale: REAL


;GpStatus
GdipGetCustomLineCapWidthScale proto WINAPI \
	     customCap: ptr,
	    widthScale: ptr


;;----------------------------------------------------------------------------
;; AdjustableArrowCap APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipCreateAdjustableArrowCap proto WINAPI \
		height: REAL,
		 width: REAL,
	      isFilled: BOOL,
		   cap: ptr GpAdjustableArrowCap


;GpStatus
GdipSetAdjustableArrowCapHeight proto WINAPI \
		   cap: ptr,
		height: REAL


;GpStatus
GdipGetAdjustableArrowCapHeight proto WINAPI \
		   cap: ptr,
		height: ptr


;GpStatus
GdipSetAdjustableArrowCapWidth proto WINAPI \
		   cap: ptr,
		 width: REAL


;GpStatus
GdipGetAdjustableArrowCapWidth proto WINAPI \
		   cap: ptr,
		 width: ptr


;GpStatus
GdipSetAdjustableArrowCapMiddleInset proto WINAPI \
		   cap: ptr,
	   middleInset: REAL


;GpStatus
GdipGetAdjustableArrowCapMiddleInset proto WINAPI \
		   cap: ptr,
	   middleInset: ptr


;GpStatus
GdipSetAdjustableArrowCapFillState proto WINAPI \
		   cap: ptr,
	     fillState: BOOL


;GpStatus
GdipGetAdjustableArrowCapFillState proto WINAPI \
		   cap: ptr,
	     fillState: ptr


;;----------------------------------------------------------------------------
;; Image APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipLoadImageFromStream proto WINAPI \
		stream: ptr,
		 image: ptr GpImage


;GpStatus
GdipLoadImageFromFile proto WINAPI \
	      filename: ptr,
		 image: ptr GpImage


;GpStatus
GdipLoadImageFromStreamICM proto WINAPI \
		stream: ptr,
		 image: ptr GpImage


;GpStatus
GdipLoadImageFromFileICM proto WINAPI \
	      filename: ptr,
		 image: ptr GpImage


;GpStatus
GdipCloneImage proto WINAPI \
		 image: ptr GpImage,
	    cloneImage: ptr GpImage


;GpStatus
GdipDisposeImage proto WINAPI \
		 image: ptr GpImage


;GpStatus
GdipSaveImageToFile proto WINAPI \
		 image: ptr GpImage,
	      filename: ptr,
	  clsidEncoder: ptr,
	 encoderParams: ptr


;GpStatus
GdipSaveImageToStream proto WINAPI \
		 image: ptr GpImage,
		stream: ptr,
	  clsidEncoder: ptr,
	 encoderParams: ptr


;GpStatus
GdipSaveAdd proto WINAPI \
		 image: ptr GpImage,
	 encoderParams: ptr


;GpStatus
GdipSaveAddImage proto WINAPI \
		 image: ptr GpImage,
	      newImage: ptr,
	 encoderParams: ptr


;GpStatus
GdipGetImageGraphicsContext proto WINAPI \
		 image: ptr GpImage,
	      graphics: ptr GpGraphics


;GpStatus
GdipGetImageBounds proto WINAPI \
		 image: ptr GpImage,
	       srcRect: ptr GpRectF,
	       srcUnit: ptr GpUnit


;GpStatus
GdipGetImageDimension proto WINAPI \
		 image: ptr GpImage,
		 width: ptr REAL,
		height: ptr REAL


;GpStatus
GdipGetImageType proto WINAPI \
		 image: ptr GpImage,
		  type: ptr ImageType


;GpStatus
GdipGetImageWidth proto WINAPI \
		 image: ptr GpImage,
		 width: ptr UINT


;GpStatus
GdipGetImageHeight proto WINAPI \
		 image: ptr GpImage,
		height: ptr UINT


;GpStatus
GdipGetImageHorizontalResolution proto WINAPI \
		 image: ptr GpImage,
	    resolution: ptr REAL


;GpStatus
GdipGetImageVerticalResolution proto WINAPI \
		 image: ptr GpImage,
	    resolution: ptr REAL


;GpStatus
GdipGetImageFlags proto WINAPI \
		 image: ptr GpImage,
		 flags: ptr UINT


;GpStatus
GdipGetImageRawFormat proto WINAPI \
		 image: ptr GpImage,
		format: ptr GUID


;GpStatus
GdipGetImagePixelFormat proto WINAPI \
		 image: ptr GpImage,
		format: ptr PixelFormat


;GpStatus
GdipGetImageThumbnail proto WINAPI \
		 image: ptr GpImage,
	    thumbWidth: UINT,
	   thumbHeight: UINT,
	    thumbImage: ptr GpImage,
	      callback: ptr,
	  callbackData: ptr


;GpStatus
GdipGetEncoderParameterListSize proto WINAPI \
		 image: ptr GpImage,
	  clsidEncoder: ptr,
		  size: ptr


;GpStatus
GdipGetEncoderParameterList proto WINAPI \
		 image: ptr GpImage,
	  clsidEncoder: ptr,
		  size: UINT,
		buffer: ptr


;GpStatus
GdipImageGetFrameDimensionsCount proto WINAPI \
		 image: ptr,
		 count: ptr


;GpStatus
GdipImageGetFrameDimensionsList proto WINAPI \
		 image: ptr,
	  dimensionIDs: ptr,
		 count: UINT


;GpStatus
GdipImageGetFrameCount proto WINAPI \
		 image: ptr GpImage,
	   dimensionID: ptr,
		 count: ptr


;GpStatus
GdipImageSelectActiveFrame proto WINAPI \
		 image: ptr GpImage,
	   dimensionID: ptr,
	    frameIndex: UINT


;GpStatus
GdipImageRotateFlip proto WINAPI \
		 image: ptr GpImage,
		rfType: RotateFlipType


;GpStatus
GdipGetImagePalette proto WINAPI \
		 image: ptr GpImage,
	       palette: ptr ColorPalette,
		  size: SINT


;GpStatus
GdipSetImagePalette proto WINAPI \
		 image: ptr GpImage,
	       palette: ptr ColorPalette


;GpStatus
GdipGetImagePaletteSize proto WINAPI \
		 image: ptr GpImage,
		  size: ptr SINT


;GpStatus
GdipGetPropertyCount proto WINAPI \
		 image: ptr GpImage,
	 numOfProperty: ptr


;GpStatus
GdipGetPropertyIdList proto WINAPI \
		 image: ptr GpImage,
	 numOfProperty: UINT,
		  list: ptr


;GpStatus
GdipGetPropertyItemSize proto WINAPI \
		 image: ptr GpImage,
		propId: PROPID,
		  size: ptr


;GpStatus
GdipGetPropertyItem proto WINAPI \
		 image: ptr GpImage,
		propId: PROPID,
	      propSize: UINT,
		buffer: ptr


;GpStatus
GdipGetPropertySize proto WINAPI \
		 image: ptr GpImage,
       totalBufferSize: ptr,
	 numProperties: ptr


;GpStatus
GdipGetAllPropertyItems proto WINAPI \
		 image: ptr GpImage,
       totalBufferSize: UINT,
	 numProperties: UINT,
	      allItems: ptr


;GpStatus
GdipRemovePropertyItem proto WINAPI \
		 image: ptr GpImage,
		propId: PROPID


;GpStatus
GdipSetPropertyItem proto WINAPI \
		 image: ptr GpImage,
		  item: ptr


if (GDIPVER GE 0x0110)
;GpStatus
GdipFindFirstImageItem proto WINAPI \
		 image: ptr GpImage,
		  item: ptr


;GpStatus
GdipFindNextImageItem proto WINAPI \
		 image: ptr GpImage,
		  item: ptr


;GpStatus
GdipGetImageItemData proto WINAPI \
		 image: ptr GpImage,
		  item: ptr

endif ;;(GDIPVER GE 0x0110)

;GpStatus
GdipImageForceValidation proto WINAPI \
		 image: ptr GpImage


;;----------------------------------------------------------------------------
;; Bitmap APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipCreateBitmapFromStream proto WINAPI \
		stream: ptr,
		bitmap: ptr GpBitmap


;GpStatus
GdipCreateBitmapFromFile proto WINAPI \
	      filename: ptr,
		bitmap: ptr GpBitmap


;GpStatus
GdipCreateBitmapFromStreamICM proto WINAPI \
		stream: ptr,
		bitmap: ptr GpBitmap


;GpStatus
GdipCreateBitmapFromFileICM proto WINAPI \
	      filename: ptr,
		bitmap: ptr GpBitmap


;GpStatus
GdipCreateBitmapFromScan0 proto WINAPI \
		 width: SINT,
		height: SINT,
		stride: SINT,
		format: PixelFormat,
		 scan0: ptr,
		bitmap: ptr


;GpStatus
GdipCreateBitmapFromGraphics proto WINAPI \
		 width: SINT,
		height: SINT,
		target: ptr,
		bitmap: ptr


;GpStatus
GdipCreateBitmapFromDirectDrawSurface proto WINAPI \
	       surface: ptr,
		bitmap: ptr


;GpStatus
GdipCreateBitmapFromGdiDib proto WINAPI \
	 gdiBitmapInfo: ptr,
	 gdiBitmapData: ptr,
		bitmap: ptr


;GpStatus
GdipCreateBitmapFromHBITMAP proto WINAPI \
		   hbm: HBITMAP,
		  hpal: HPALETTE,
		bitmap: ptr


;GpStatus
GdipCreateHBITMAPFromBitmap proto WINAPI \
		bitmap: ptr,
	     hbmReturn: ptr,
	    background: ARGB


;GpStatus
GdipCreateBitmapFromHICON proto WINAPI \
		 hicon: HICON,
		bitmap: ptr


;GpStatus
GdipCreateHICONFromBitmap proto WINAPI \
		bitmap: ptr,
	     hbmReturn: ptr


;GpStatus
GdipCreateBitmapFromResource proto WINAPI \
	     hInstance: HINSTANCE,
	  lpBitmapName: ptr,
		bitmap: ptr


;GpStatus
GdipCloneBitmapArea proto WINAPI \
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL,
		format: PixelFormat,
	     srcBitmap: ptr GpBitmap,
	     dstBitmap: ptr GpBitmap


;GpStatus
GdipCloneBitmapAreaI proto WINAPI \
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT,
		format: PixelFormat,
	     srcBitmap: ptr GpBitmap,
	     dstBitmap: ptr GpBitmap


;GpStatus
GdipBitmapLockBits proto WINAPI \
		bitmap: ptr,
		  rect: ptr,
		 flags: UINT,
		format: PixelFormat,
      lockedBitmapData: ptr


;GpStatus
GdipBitmapUnlockBits proto WINAPI \
		bitmap: ptr,
      lockedBitmapData: ptr


;GpStatus
GdipBitmapGetPixel proto WINAPI \
		bitmap: ptr,
		     x: SINT,
		     y: SINT,
		 color: ptr ARGB


;GpStatus
GdipBitmapSetPixel proto WINAPI \
		bitmap: ptr,
		     x: SINT,
		     y: SINT,
		 color: ARGB


if (GDIPVER GE 0x0110)
;GpStatus
GdipImageSetAbort proto WINAPI \
		pImage: ptr GpImage,
	       pIAbort: ptr GdiplusAbort


;GpStatus
GdipGraphicsSetAbort proto WINAPI \
	     pGraphics: ptr GpGraphics,
	       pIAbort: ptr GdiplusAbort


;GpStatus
GdipBitmapConvertFormat proto WINAPI \
	  pInputBitmap: ptr GpBitmap,
		format: PixelFormat,
	    dithertype: DitherType,
	   palettetype: PaletteType,
	       palette: ptr ColorPalette,
 alphaThresholdPercent: REAL


;GpStatus
GdipInitializePalette proto WINAPI \
	       palette: ptr ColorPalette,
	   palettetype: PaletteType,
	 optimalColors: SINT,
   useTransparentColor: BOOL,
		bitmap: ptr GpBitmap


;GpStatus
GdipBitmapApplyEffect proto WINAPI \
		bitmap: ptr,
		effect: ptr CGpEffect,
		   roi: ptr RECT,
	    useAuxData: BOOL,
	       auxData: ptr VOID,
	   auxDataSize: ptr SINT


;GpStatus
GdipBitmapCreateApplyEffect proto WINAPI \
	  inputBitmaps: ptr GpBitmap,
	     numInputs: SINT,
		effect: ptr CGpEffect,
		   roi: ptr RECT,
	    outputRect: ptr RECT,
	  outputBitmap: ptr GpBitmap,
	    useAuxData: BOOL,
	       auxData: ptr VOID,
	   auxDataSize: ptr SINT


;GpStatus
GdipBitmapGetHistogram proto WINAPI \
		bitmap: ptr,
		format: HistogramFormat,
       NumberOfEntries: UINT,
	      channel0: ptr UINT,
	      channel1: ptr UINT,
	      channel2: ptr UINT,
		      : ptr

;GpStatus
GdipBitmapGetHistogramSize proto WINAPI \
		format: HistogramFormat,
       NumberOfEntries: ptr UINT

endif

;GpStatus
GdipBitmapSetResolution proto WINAPI \
		bitmap: ptr,
		  xdpi: REAL,
		  ydpi: REAL


;;----------------------------------------------------------------------------
;; ImageAttributes APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipCreateImageAttributes proto WINAPI \
	     imageattr: ptr GpImageAttributes


;GpStatus
GdipCloneImageAttributes proto WINAPI \
	     imageattr: ptr GpImageAttributes,
	cloneImageattr: ptr GpImageAttributes


;GpStatus
GdipDisposeImageAttributes proto WINAPI \
	     imageattr: ptr GpImageAttributes


;GpStatus
GdipSetImageAttributesToIdentity proto WINAPI \
	     imageattr: ptr GpImageAttributes,
		  type: ColorAdjustType

;GpStatus
GdipResetImageAttributes proto WINAPI \
	     imageattr: ptr GpImageAttributes,
		  type: ColorAdjustType


;GpStatus
GdipSetImageAttributesColorMatrix proto WINAPI \
	     imageattr: ptr GpImageAttributes,
		  type: ColorAdjustType,
	    enableFlag: BOOL,
	   colorMatrix: ptr,
	    grayMatrix: ptr,
		 flags: ColorMatrixFlags


;GpStatus
GdipSetImageAttributesThreshold proto WINAPI \
	     imageattr: ptr GpImageAttributes,
		  type: ColorAdjustType,
	    enableFlag: BOOL,
	     threshold: REAL


;GpStatus
GdipSetImageAttributesGamma proto WINAPI \
	     imageattr: ptr GpImageAttributes,
		  type: ColorAdjustType,
	    enableFlag: BOOL,
		 gamma: REAL


;GpStatus
GdipSetImageAttributesNoOp proto WINAPI \
	     imageattr: ptr GpImageAttributes,
		  type: ColorAdjustType,
	    enableFlag: BOOL


;GpStatus
GdipSetImageAttributesColorKeys proto WINAPI \
	     imageattr: ptr GpImageAttributes,
		  type: ColorAdjustType,
	    enableFlag: BOOL,
	      colorLow: ARGB,
	     colorHigh: ARGB


;GpStatus
GdipSetImageAttributesOutputChannel proto WINAPI \
	     imageattr: ptr GpImageAttributes,
		  type: ColorAdjustType,
	    enableFlag: BOOL,
	  channelFlags: ColorChannelFlags


;GpStatus
GdipSetImageAttributesOutputChannelColorProfile proto WINAPI \
	     imageattr: ptr GpImageAttributes,
		  type: ColorAdjustType,
	    enableFlag: BOOL,
  colorProfileFilename: ptr WCHAR


;GpStatus
GdipSetImageAttributesRemapTable proto WINAPI \
	     imageattr: ptr GpImageAttributes,
		  type: ColorAdjustType,
	    enableFlag: BOOL,
	       mapSize: UINT,
		   map: ptr ColorMap

;GpStatus
GdipSetImageAttributesWrapMode proto WINAPI \
	     imageAttr: ptr GpImageAttributes,
		  wrap: WrapMode,
		  argb: ARGB,
		 clamp: BOOL


;GpStatus
GdipSetImageAttributesICMMode proto WINAPI \
	     imageAttr: ptr GpImageAttributes,
		    on: BOOL


;GpStatus
GdipGetImageAttributesAdjustedPalette proto WINAPI \
	     imageAttr: ptr GpImageAttributes,
	  colorPalette: ptr,
       colorAdjustType: ColorAdjustType


;;----------------------------------------------------------------------------
;; Graphics APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipFlush proto WINAPI \
	      graphics: ptr GpGraphics,
	     intention: FlushIntention


;GpStatus
GdipCreateFromHDC proto WINAPI \
		   hdc: HDC,
	      graphics: ptr GpGraphics


;GpStatus
GdipCreateFromHDC2 proto WINAPI \
		   hdc: HDC,
	       hDevice: HANDLE,
	      graphics: ptr GpGraphics


;GpStatus
GdipCreateFromHWND proto WINAPI \
		  hwnd: HWND,
	      graphics: ptr GpGraphics


;GpStatus
GdipCreateFromHWNDICM proto WINAPI \
		  hwnd: HWND,
	      graphics: ptr GpGraphics


;GpStatus
GdipDeleteGraphics proto WINAPI \
	      graphics: ptr GpGraphics


;GpStatus
GdipGetDC proto WINAPI \
	      graphics: ptr,
		   hdc: ptr


;GpStatus
GdipReleaseDC proto WINAPI \
	      graphics: ptr,
		   hdc: HDC


;GpStatus
GdipSetCompositingMode proto WINAPI \
	      graphics: ptr GpGraphics,
       compositingMode: CompositingMode


;GpStatus
GdipGetCompositingMode proto WINAPI \
	      graphics: ptr GpGraphics,
       compositingMode: ptr CompositingMode


;GpStatus
GdipSetRenderingOrigin proto WINAPI \
	      graphics: ptr GpGraphics,
		     x: SINT,
		     y: SINT


;GpStatus
GdipGetRenderingOrigin proto WINAPI \
	      graphics: ptr GpGraphics,
		     x: ptr SINT,
		     y: ptr SINT


;GpStatus
GdipSetCompositingQuality proto WINAPI \
	      graphics: ptr GpGraphics,
    compositingQuality: CompositingQuality


;GpStatus
GdipGetCompositingQuality proto WINAPI \
	      graphics: ptr GpGraphics,
    compositingQuality: ptr CompositingQuality


;GpStatus
GdipSetSmoothingMode proto WINAPI \
	      graphics: ptr GpGraphics,
	 smoothingMode: SmoothingMode


;GpStatus
GdipGetSmoothingMode proto WINAPI \
	      graphics: ptr GpGraphics,
	 smoothingMode: ptr SmoothingMode


;GpStatus
GdipSetPixelOffsetMode proto WINAPI \
	      graphics: ptr,
       pixelOffsetMode: PixelOffsetMode


;GpStatus
GdipGetPixelOffsetMode proto WINAPI \
	      graphics: ptr GpGraphics,
       pixelOffsetMode: ptr PixelOffsetMode


;GpStatus
GdipSetTextRenderingHint proto WINAPI \
	      graphics: ptr GpGraphics,
		  mode: TextRenderingHint


;GpStatus
GdipGetTextRenderingHint proto WINAPI \
	      graphics: ptr GpGraphics,
		  mode: ptr TextRenderingHint


;GpStatus
GdipSetTextContrast proto WINAPI \
	      graphics: ptr GpGraphics,
	      contrast: UINT


;GpStatus
GdipGetTextContrast proto WINAPI \
	      graphics: ptr GpGraphics,
	      contrast: ptr


;GpStatus
GdipSetInterpolationMode proto WINAPI \
	      graphics: ptr GpGraphics,
     interpolationMode: InterpolationMode


;GpStatus
GdipGetInterpolationMode proto WINAPI \
	      graphics: ptr GpGraphics,
     interpolationMode: ptr InterpolationMode


;GpStatus
GdipSetWorldTransform proto WINAPI \
	      graphics: ptr GpGraphics,
		matrix: ptr GpMatrix


;GpStatus
GdipResetWorldTransform proto WINAPI \
	      graphics: ptr GpGraphics


;GpStatus
GdipMultiplyWorldTransform proto WINAPI \
	      graphics: ptr GpGraphics,
		matrix: ptr GpMatrix,
		 order: GpMatrixOrder


;GpStatus
GdipTranslateWorldTransform proto WINAPI \
	      graphics: ptr GpGraphics,
		   _dx: REAL,
		    dy: REAL,
		 order: GpMatrixOrder


;GpStatus
GdipScaleWorldTransform proto WINAPI \
	      graphics: ptr GpGraphics,
		    sx: REAL,
		    sy: REAL,
		 order: GpMatrixOrder


;GpStatus
GdipRotateWorldTransform proto WINAPI \
	      graphics: ptr GpGraphics,
		 angle: REAL,
		 order: GpMatrixOrder


;GpStatus
GdipGetWorldTransform proto WINAPI \
	      graphics: ptr GpGraphics,
		matrix: ptr GpMatrix


;GpStatus
GdipResetPageTransform proto WINAPI \
	      graphics: ptr GpGraphics


;GpStatus
GdipGetPageUnit proto WINAPI \
	      graphics: ptr GpGraphics,
		  unit: ptr GpUnit


;GpStatus
GdipGetPageScale proto WINAPI \
	      graphics: ptr GpGraphics,
		 scale: ptr REAL


;GpStatus
GdipSetPageUnit proto WINAPI \
	      graphics: ptr GpGraphics,
		  unit: GpUnit


;GpStatus
GdipSetPageScale proto WINAPI \
	      graphics: ptr GpGraphics,
		 scale: REAL


;GpStatus
GdipGetDpiX proto WINAPI \
	      graphics: ptr GpGraphics,
		   dpi: ptr


;GpStatus
GdipGetDpiY proto WINAPI \
	      graphics: ptr GpGraphics,
		   dpi: ptr


;GpStatus
GdipTransformPoints proto WINAPI \
	      graphics: ptr GpGraphics,
	     destSpace: CoordinateSpace,
	      srcSpace: CoordinateSpace,
		points: ptr GpPointF,
		 count: SINT


;GpStatus
GdipTransformPointsI proto WINAPI \
	      graphics: ptr GpGraphics,
	     destSpace: CoordinateSpace,
	      srcSpace: CoordinateSpace,
		points: ptr GpPoint,
		 count: SINT


;GpStatus
GdipGetNearestColor proto WINAPI \
	      graphics: ptr GpGraphics,
		  argb: ptr


;; Creates the Win9x Halftone Palette (even on NT) with correct Desktop colors
;HPALETTE WINGDIPAPI
GdipCreateHalftonePalette proto WINAPI

;GpStatus
GdipDrawLine proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		    x1: REAL,
		    y1: REAL,
		    x2: REAL,
		    y2: REAL


;GpStatus
GdipDrawLineI proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		    x1: SINT,
		    y1: SINT,
		    x2: SINT,
		    y2: SINT


;GpStatus
GdipDrawLines proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		points: ptr GpPointF,
		 count: SINT


;GpStatus
GdipDrawLinesI proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		points: ptr GpPoint,
		 count: SINT


;GpStatus
GdipDrawArc proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL,
	    startAngle: REAL,
	    sweepAngle: REAL


;GpStatus
GdipDrawArcI proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT,
	    startAngle: REAL,
	    sweepAngle: REAL


;GpStatus
GdipDrawBezier proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		    x1: REAL,
		    y1: REAL,
		    x2: REAL,
		    y2: REAL,
		    x3: REAL,
		    y3: REAL,
		    x4: REAL,
		    y4: REAL


;GpStatus
GdipDrawBezierI proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		    x1: SINT,
		    y1: SINT,
		    x2: SINT,
		    y2: SINT,
		    x3: SINT,
		    y3: SINT,
		    x4: SINT,
		    y4: SINT


;GpStatus
GdipDrawBeziers proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		points: ptr GpPointF,
		 count: SINT


;GpStatus
GdipDrawBeziersI proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		points: ptr GpPoint,
		 count: SINT


;GpStatus
GdipDrawRectangle proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL


;GpStatus
GdipDrawRectangleI proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT


;GpStatus
GdipDrawRectangles proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		 rects: ptr GpRectF,
		 count: SINT


;GpStatus
GdipDrawRectanglesI proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		 rects: ptr GpRect,
		 count: SINT


;GpStatus
GdipDrawEllipse proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL


;GpStatus
GdipDrawEllipseI proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT


;GpStatus
GdipDrawPie proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL,
	    startAngle: REAL,
	    sweepAngle: REAL


;GpStatus
GdipDrawPieI proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT,
	    startAngle: REAL,
	    sweepAngle: REAL


;GpStatus
GdipDrawPolygon proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		points: ptr GpPointF,
		 count: SINT


;GpStatus
GdipDrawPolygonI proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		points: ptr GpPoint,
		 count: SINT


;GpStatus
GdipDrawPath proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		  path: ptr


;GpStatus
GdipDrawCurve proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		points: ptr GpPointF,
		 count: SINT


;GpStatus
GdipDrawCurveI proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		points: ptr GpPoint,
		 count: SINT


;GpStatus
GdipDrawCurve2 proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		points: ptr GpPointF,
		 count: SINT,
	       tension: REAL


;GpStatus
GdipDrawCurve2I proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		points: ptr GpPoint,
		 count: SINT,
	       tension: REAL


;GpStatus
GdipDrawCurve3 proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		points: ptr GpPointF,
		 count: SINT,
	       _offset: SINT,
      numberOfSegments: SINT,
	       tension: REAL


;GpStatus
GdipDrawCurve3I proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		points: ptr GpPoint,
		 count: SINT,
	       _offset: SINT,
      numberOfSegments: SINT,
	       tension: REAL


;GpStatus
GdipDrawClosedCurve proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		points: ptr GpPointF,
		 count: SINT


;GpStatus
GdipDrawClosedCurveI proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		points: ptr GpPoint,
		 count: SINT


;GpStatus
GdipDrawClosedCurve2 proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		points: ptr GpPointF,
		 count: SINT,
	       tension: REAL


;GpStatus
GdipDrawClosedCurve2I proto WINAPI \
	      graphics: ptr GpGraphics,
		   pen: ptr GpPen,
		points: ptr GpPoint,
		 count: SINT,
	       tension: REAL


;GpStatus
GdipGraphicsClear proto WINAPI \
	      graphics: ptr GpGraphics,
		 color: ARGB


;GpStatus
GdipFillRectangle proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL


;GpStatus
GdipFillRectangleI proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT


;GpStatus
GdipFillRectangles proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		 rects: ptr GpRectF,
		 count: SINT


;GpStatus
GdipFillRectanglesI proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		 rects: ptr GpRect,
		 count: SINT


;GpStatus
GdipFillPolygon proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		points: ptr GpPointF,
		 count: SINT,
	      fillMode: GpFillMode


;GpStatus
GdipFillPolygonI proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		points: ptr GpPoint,
		 count: SINT,
	      fillMode: GpFillMode


;GpStatus
GdipFillPolygon2 proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		points: ptr GpPointF,
		 count: SINT


;GpStatus
GdipFillPolygon2I proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		points: ptr GpPoint,
		 count: SINT


;GpStatus
GdipFillEllipse proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL


;GpStatus
GdipFillEllipseI proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT


;GpStatus
GdipFillPie proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL,
	    startAngle: REAL,
	    sweepAngle: REAL


;GpStatus
GdipFillPieI proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT,
	    startAngle: REAL,
	    sweepAngle: REAL


;GpStatus
GdipFillPath proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		  path: ptr


;GpStatus
GdipFillClosedCurve proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		points: ptr GpPointF,
		 count: SINT


;GpStatus
GdipFillClosedCurveI proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		points: ptr GpPoint,
		 count: SINT


;GpStatus
GdipFillClosedCurve2 proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		points: ptr GpPointF,
		 count: SINT,
	       tension: REAL,
	      fillMode: GpFillMode


;GpStatus
GdipFillClosedCurve2I proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		points: ptr GpPoint,
		 count: SINT,
	       tension: REAL,
	      fillMode: GpFillMode


;GpStatus
GdipFillRegion proto WINAPI \
	      graphics: ptr GpGraphics,
		 brush: ptr GpBrush,
		region: ptr GpRegion


if (GDIPVER GE 0x0110)
;GpStatus
GdipDrawImageFX proto WINAPI \
	      graphics: ptr GpGraphics,
		 image: ptr GpImage,
		source: ptr GpRectF,
		 xForm: ptr GpMatrix,
		effect: ptr CGpEffect,
       imageAttributes: ptr GpImageAttributes,
	       srcUnit: GpUnit

endif ;;(GDIPVER GE 0x0110)

;GpStatus
GdipDrawImage proto WINAPI \
	      graphics: ptr GpGraphics,
		 image: ptr GpImage,
		     x: REAL,
		     y: REAL


;GpStatus
GdipDrawImageI proto WINAPI \
	      graphics: ptr GpGraphics,
		 image: ptr GpImage,
		     x: SINT,
		     y: SINT


;GpStatus
GdipDrawImageRect proto WINAPI \
	      graphics: ptr GpGraphics,
		 image: ptr GpImage,
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL


;GpStatus
GdipDrawImageRectI proto WINAPI \
	      graphics: ptr GpGraphics,
		 image: ptr GpImage,
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT


;GpStatus
GdipDrawImagePoints proto WINAPI \
	      graphics: ptr GpGraphics,
		 image: ptr GpImage,
	     dstpoints: ptr GpPointF,
		 count: SINT


;GpStatus
GdipDrawImagePointsI proto WINAPI \
	      graphics: ptr GpGraphics,
		 image: ptr GpImage,
	     dstpoints: ptr GpPoint,
		 count: SINT


;GpStatus
GdipDrawImagePointRect proto WINAPI \
	      graphics: ptr GpGraphics,
		 image: ptr GpImage,
		     x: REAL,
		     y: REAL,
		  srcx: REAL,
		  srcy: REAL,
	      srcwidth: REAL,
	     srcheight: REAL,
	       srcUnit: GpUnit


;GpStatus
GdipDrawImagePointRectI proto WINAPI \
	      graphics: ptr GpGraphics,
		 image: ptr GpImage,
		     x: SINT,
		     y: SINT,
		  srcx: SINT,
		  srcy: SINT,
	      srcwidth: SINT,
	     srcheight: SINT,
	       srcUnit: GpUnit


;GpStatus
GdipDrawImageRectRect proto WINAPI \
	      graphics: ptr GpGraphics,
		 image: ptr GpImage,
		  dstx: REAL,
		  dsty: REAL,
	      dstwidth: REAL,
	     dstheight: REAL,
		  srcx: REAL,
		  srcy: REAL,
	      srcwidth: REAL,
	     srcheight: REAL,
	       srcUnit: GpUnit,
       imageAttributes: ptr,
	      callback: ptr,
	  callbackData: ptr


;GpStatus
GdipDrawImageRectRectI proto WINAPI \
	      graphics: ptr GpGraphics,
		 image: ptr GpImage,
		  dstx: SINT,
		  dsty: SINT,
	      dstwidth: SINT,
	     dstheight: SINT,
		  srcx: SINT,
		  srcy: SINT,
	      srcwidth: SINT,
	     srcheight: SINT,
	       srcUnit: GpUnit,
       imageAttributes: ptr,
	      callback: ptr,
	  callbackData: ptr


;GpStatus
GdipDrawImagePointsRect proto WINAPI \
	      graphics: ptr GpGraphics,
		 image: ptr GpImage,
		points: ptr GpPointF,
		 count: SINT,
		  srcx: REAL,
		  srcy: REAL,
	      srcwidth: REAL,
	     srcheight: REAL,
	       srcUnit: GpUnit,
       imageAttributes: ptr,
	      callback: ptr,
	  callbackData: ptr


;GpStatus
GdipDrawImagePointsRectI proto WINAPI \
	      graphics: ptr GpGraphics,
		 image: ptr GpImage,
		points: ptr GpPoint,
		 count: SINT,
		  srcx: SINT,
		  srcy: SINT,
	      srcwidth: SINT,
	     srcheight: SINT,
	       srcUnit: GpUnit,
       imageAttributes: ptr,
	      callback: ptr,
	  callbackData: ptr


;GpStatus
GdipEnumerateMetafileDestPoint proto WINAPI \
	      graphics: ptr,
	      metafile: ptr GpMetafile,
	     destPoint: ptr,
	      callback: EnumerateMetafileProc,
	  callbackData: ptr,
       imageAttributes: ptr GpImageAttributes


;GpStatus
GdipEnumerateMetafileDestPointI proto WINAPI \
	      graphics: ptr,
	      metafile: ptr GpMetafile,
	     destPoint: ptr,
	      callback: EnumerateMetafileProc,
	  callbackData: ptr,
       imageAttributes: ptr GpImageAttributes


;GpStatus
GdipEnumerateMetafileDestRect proto WINAPI \
	      graphics: ptr,
	      metafile: ptr GpMetafile,
	      destRect: ptr RectF,
	      callback: EnumerateMetafileProc,
	  callbackData: ptr,
       imageAttributes: ptr GpImageAttributes


;GpStatus
GdipEnumerateMetafileDestRectI proto WINAPI \
	      graphics: ptr,
	      metafile: ptr GpMetafile,
	      destRect: ptr Rect,
	      callback: EnumerateMetafileProc,
	  callbackData: ptr,
       imageAttributes: ptr GpImageAttributes


;GpStatus
GdipEnumerateMetafileDestPoints proto WINAPI \
	      graphics: ptr,
	      metafile: ptr GpMetafile,
	    destPoints: ptr PointF,
		 count: SINT,
	      callback: EnumerateMetafileProc,
	  callbackData: ptr,
       imageAttributes: ptr GpImageAttributes


;GpStatus
GdipEnumerateMetafileDestPointsI proto WINAPI \
	      graphics: ptr,
	      metafile: ptr GpMetafile,
	    destPoints: ptr Point,
		 count: SINT,
	      callback: EnumerateMetafileProc,
	  callbackData: ptr,
       imageAttributes: ptr GpImageAttributes


;GpStatus
GdipEnumerateMetafileSrcRectDestPoint proto WINAPI \
	      graphics: ptr,
	      metafile: ptr GpMetafile,
	     destPoint: ptr PointF,
	       srcRect: ptr RectF,
	       srcUnit: Unit,
	      callback: EnumerateMetafileProc,
	  callbackData: ptr,
       imageAttributes: ptr GpImageAttributes


;GpStatus
GdipEnumerateMetafileSrcRectDestPointI proto WINAPI \
	      graphics: ptr,
	      metafile: ptr GpMetafile,
	     destPoint: ptr Point,
	       srcRect: ptr Rect,
	       srcUnit: Unit,
	      callback: EnumerateMetafileProc,
	  callbackData: ptr,
       imageAttributes: ptr GpImageAttributes


;GpStatus
GdipEnumerateMetafileSrcRectDestRect proto WINAPI \
	      graphics: ptr,
	      metafile: ptr GpMetafile,
	      destRect: ptr RectF,
	       srcRect: ptr RectF,
	       srcUnit: Unit,
	      callback: EnumerateMetafileProc,
	  callbackData: ptr,
       imageAttributes: ptr GpImageAttributes


;GpStatus
GdipEnumerateMetafileSrcRectDestRectI proto WINAPI \
	      graphics: ptr,
	      metafile: ptr GpMetafile,
	      destRect: ptr Rect,
	       srcRect: ptr Rect,
	       srcUnit: Unit,
	      callback: EnumerateMetafileProc,
	  callbackData: ptr,
       imageAttributes: ptr GpImageAttributes


;GpStatus
GdipEnumerateMetafileSrcRectDestPoints proto WINAPI \
	      graphics: ptr,
	      metafile: ptr GpMetafile,
	    destPoints: ptr PointF,
		 count: SINT,
	       srcRect: ptr RectF,
	       srcUnit: Unit,
	      callback: EnumerateMetafileProc,
	  callbackData: ptr,
       imageAttributes: ptr GpImageAttributes


;GpStatus
GdipEnumerateMetafileSrcRectDestPointsI proto WINAPI \
	      graphics: ptr,
	      metafile: ptr GpMetafile,
	    destPoints: ptr Point,
		 count: SINT,
	       srcRect: ptr Rect,
	       srcUnit: Unit,
	      callback: EnumerateMetafileProc,
	  callbackData: ptr,
       imageAttributes: ptr GpImageAttributes


;GpStatus
GdipPlayMetafileRecord proto WINAPI \
	      metafile: ptr GpMetafile,
	    recordType: EmfPlusRecordType,
		 flags: UINT,
	      dataSize: UINT,
		  data: ptr BYTE


;GpStatus
GdipSetClipGraphics proto WINAPI \
	      graphics: ptr GpGraphics,
	   srcgraphics: ptr GpGraphics,
	   combineMode: CombineMode


;GpStatus
GdipSetClipRect proto WINAPI \
	      graphics: ptr GpGraphics,
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL,
	   combineMode: CombineMode


;GpStatus
GdipSetClipRectI proto WINAPI \
	      graphics: ptr GpGraphics,
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT,
	   combineMode: CombineMode


;GpStatus
GdipSetClipPath proto WINAPI \
	      graphics: ptr GpGraphics,
		  path: ptr,
	   combineMode: CombineMode


;GpStatus
GdipSetClipRegion proto WINAPI \
	      graphics: ptr GpGraphics,
		region: ptr GpRegion,
	   combineMode: CombineMode


;GpStatus
GdipSetClipHrgn proto WINAPI \
	      graphics: ptr GpGraphics,
		  hRgn: HRGN,
	   combineMode: CombineMode


;GpStatus
GdipResetClip proto WINAPI \
	      graphics: ptr GpGraphics


;GpStatus
GdipTranslateClip proto WINAPI \
	      graphics: ptr GpGraphics,
		   _dx: REAL,
		    dy: REAL


;GpStatus
GdipTranslateClipI proto WINAPI \
	      graphics: ptr GpGraphics,
		   _dx: SINT,
		    dy: SINT


;GpStatus
GdipGetClip proto WINAPI \
	      graphics: ptr GpGraphics,
		region: ptr GpRegion


;GpStatus
GdipGetClipBounds proto WINAPI \
	      graphics: ptr GpGraphics,
		  rect: ptr GpRectF


;GpStatus
GdipGetClipBoundsI proto WINAPI \
	      graphics: ptr GpGraphics,
		  rect: ptr GpRect


;GpStatus
GdipIsClipEmpty proto WINAPI \
	      graphics: ptr GpGraphics,
		result: ptr BOOL


;GpStatus
GdipGetVisibleClipBounds proto WINAPI \
	      graphics: ptr GpGraphics,
		  rect: ptr GpRectF


;GpStatus
GdipGetVisibleClipBoundsI proto WINAPI \
	      graphics: ptr GpGraphics,
		  rect: ptr GpRect


;GpStatus
GdipIsVisibleClipEmpty proto WINAPI \
	      graphics: ptr GpGraphics,
		result: ptr BOOL


;GpStatus
GdipIsVisiblePoint proto WINAPI \
	      graphics: ptr GpGraphics,
		     x: REAL,
		     y: REAL,
		result: ptr BOOL


;GpStatus
GdipIsVisiblePointI proto WINAPI \
	      graphics: ptr GpGraphics,
		     x: SINT,
		     y: SINT,
		result: ptr BOOL


;GpStatus
GdipIsVisibleRect proto WINAPI \
	      graphics: ptr GpGraphics,
		     x: REAL,
		     y: REAL,
		 width: REAL,
		height: REAL,
		result: ptr BOOL


;GpStatus
GdipIsVisibleRectI proto WINAPI \
	      graphics: ptr GpGraphics,
		     x: SINT,
		     y: SINT,
		 width: SINT,
		height: SINT,
		result: ptr BOOL


;GpStatus
GdipSaveGraphics proto WINAPI \
	      graphics: ptr GpGraphics,
		 state: ptr GraphicsState


;GpStatus
GdipRestoreGraphics proto WINAPI \
	      graphics: ptr GpGraphics,
		 state: GraphicsState


;GpStatus
GdipBeginContainer proto WINAPI \
	      graphics: ptr GpGraphics,
	       dstrect: ptr,
	       srcrect: ptr GpRectF,
		  unit: GpUnit,
		 state: ptr GraphicsContainer


;GpStatus
GdipBeginContainerI proto WINAPI \
	      graphics: ptr GpGraphics,
	       dstrect: ptr,
	       srcrect: ptr GpRect,
		  unit: GpUnit,
		 state: ptr GraphicsContainer


;GpStatus
GdipBeginContainer2 proto WINAPI \
	      graphics: ptr GpGraphics,
		 state: ptr


;GpStatus
GdipEndContainer proto WINAPI \
	      graphics: ptr GpGraphics,
		 state: GraphicsContainer


;GpStatus
GdipGetMetafileHeaderFromWmf proto WINAPI \
		  hWmf: HMETAFILE,
     wmfPlaceableFileHeader: ptr WmfPlaceableFileHeader,
		header: ptr


;GpStatus
GdipGetMetafileHeaderFromEmf proto WINAPI \
		  hEmf: HENHMETAFILE,
		header: ptr


;GpStatus
GdipGetMetafileHeaderFromFile proto WINAPI \
	      filename: ptr,
		header: ptr


;GpStatus
GdipGetMetafileHeaderFromStream proto WINAPI \
		stream: ptr,
		header: ptr


;GpStatus
GdipGetMetafileHeaderFromMetafile proto WINAPI \
	      metafile: ptr,
		header: ptr


;GpStatus
GdipGetHemfFromMetafile proto WINAPI \
	      metafile: ptr,
		  hEmf: ptr


;GpStatus
GdipCreateStreamOnFile proto WINAPI \
	      filename: ptr WCHAR,
		access: UINT,
		stream: ptr IStream


;GpStatus
GdipCreateMetafileFromWmf proto WINAPI \
		  hWmf: HMETAFILE,
	     deleteWmf: BOOL,
 wmfPlaceableFileHeader: ptr WmfPlaceableFileHeader,
	      metafile: ptr GpMetafile


;GpStatus
GdipCreateMetafileFromEmf proto WINAPI \
		  hEmf: HENHMETAFILE,
	     deleteEmf: BOOL,
	      metafile: ptr GpMetafile


;GpStatus
GdipCreateMetafileFromFile proto WINAPI \
		  file: ptr,
	      metafile: ptr GpMetafile


;GpStatus
GdipCreateMetafileFromWmfFile proto WINAPI \
		  file: ptr,
 wmfPlaceableFileHeader: ptr WmfPlaceableFileHeader,
	      metafile: ptr GpMetafile


;GpStatus
GdipCreateMetafileFromStream proto WINAPI \
		stream: ptr,
	      metafile: ptr GpMetafile



;GpStatus
GdipRecordMetafile proto WINAPI \
	  referenceHdc: HDC,
		  type: EmfType,
	     frameRect: ptr GpRectF,
	     frameUnit: MetafileFrameUnit,
	   description: ptr WCHAR,
	      metafile: ptr


;GpStatus
GdipRecordMetafileI proto WINAPI \
	  referenceHdc: HDC,
		  type: EmfType,
	     frameRect: ptr GpRect,
	     frameUnit: MetafileFrameUnit,
	   description: ptr WCHAR,
	      metafile: ptr


;GpStatus
GdipRecordMetafileFileName proto WINAPI \
	      fileName: ptr,
	  referenceHdc: HDC,
		  type: EmfType,
	     frameRect: ptr GpRectF,
	     frameUnit: MetafileFrameUnit,
	   description: ptr WCHAR,
	      metafile: ptr


;GpStatus
GdipRecordMetafileFileNameI proto WINAPI \
	      fileName: ptr,
	  referenceHdc: HDC,
		  type: EmfType,
	     frameRect: ptr GpRect,
	     frameUnit: MetafileFrameUnit,
	   description: ptr WCHAR,
	      metafile: ptr


;GpStatus
GdipRecordMetafileStream proto WINAPI \
		stream: ptr,
	  referenceHdc: HDC,
		  type: EmfType,
	     frameRect: ptr GpRectF,
	     frameUnit: MetafileFrameUnit,
	   description: ptr WCHAR,
	      metafile: ptr


;GpStatus
GdipRecordMetafileStreamI proto WINAPI \
		stream: ptr,
	  referenceHdc: HDC,
		  type: EmfType,
	     frameRect: ptr GpRect,
	     frameUnit: MetafileFrameUnit,
	   description: ptr WCHAR,
	      metafile: ptr


;GpStatus
GdipSetMetafileDownLevelRasterizationLimit proto WINAPI \
	      metafile: ptr,
metafileRasterizationLimitDpi: UINT


;GpStatus
GdipGetMetafileDownLevelRasterizationLimit proto WINAPI \
	      metafile: ptr GpMetafile,
metafileRasterizationLimitDpi: ptr


;GpStatus
GdipGetImageDecodersSize proto WINAPI \
	   numDecoders: ptr UINT,
		      : ptr

;GpStatus
GdipGetImageDecoders proto WINAPI \
	   numDecoders: UINT,
		  size: UINT,
		      : ptr

;GpStatus
GdipGetImageEncodersSize proto WINAPI \
	   numEncoders: ptr UINT,
		      : ptr

;GpStatus
GdipGetImageEncoders proto WINAPI \
	   numEncoders: UINT,
		  size: UINT,
		      : ptr

;GpStatus
GdipComment proto WINAPI \
	      graphics: ptr,
	      sizeData: UINT,
		 _data: ptr BYTE


;;----------------------------------------------------------------------------
;; FontFamily APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipCreateFontFamilyFromName proto WINAPI \
		  name: ptr WCHAR,
	fontCollection: ptr GpFontCollection,
	    fontFamily: ptr GpFontFamily


;GpStatus
GdipDeleteFontFamily proto WINAPI \
	    fontFamily: ptr GpFontFamily


;GpStatus
GdipCloneFontFamily proto WINAPI \
	    fontFamily: ptr GpFontFamily,
      clonedFontFamily: ptr GpFontFamily


;GpStatus
GdipGetGenericFontFamilySansSerif proto WINAPI \
	  nativeFamily: ptr GpFontFamily


;GpStatus
GdipGetGenericFontFamilySerif proto WINAPI \
	  nativeFamily: ptr GpFontFamily


;GpStatus
GdipGetGenericFontFamilyMonospace proto WINAPI \
	  nativeFamily: ptr GpFontFamily



;GpStatus
GdipGetFamilyName proto WINAPI \
		family: ptr GpFontFamily,
		  name: LPWSTR,
	      language: LANGID


;GpStatus
GdipIsStyleAvailable proto WINAPI \
		family: ptr GpFontFamily,
		 style: SINT,
      IsStyleAvailable: ptr


;GpStatus
GdipFontCollectionEnumerable proto WINAPI \
	fontCollection: ptr,
	      graphics: ptr,
	      numFound: ptr


;GpStatus
GdipFontCollectionEnumerate proto WINAPI \
	fontCollection: ptr,
	     numSought: SINT,
	    gpfamilies: ptr,
	      numFound: ptr,
	      graphics: ptr


;GpStatus
GdipGetEmHeight proto WINAPI \
		family: ptr GpFontFamily,
		 style: SINT,
	      EmHeight: ptr


;GpStatus
GdipGetCellAscent proto WINAPI \
		family: ptr GpFontFamily,
		 style: SINT,
	    CellAscent: ptr


;GpStatus
GdipGetCellDescent proto WINAPI \
		family: ptr GpFontFamily,
		 style: SINT,
	   CellDescent: ptr


;GpStatus
GdipGetLineSpacing proto WINAPI \
		family: ptr GpFontFamily,
		 style: SINT,
	   LineSpacing: ptr



;;----------------------------------------------------------------------------
;; Font APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipCreateFontFromDC proto WINAPI \
		   hdc: HDC,
		  font: ptr GpFont


;GpStatus
GdipCreateFontFromLogfontA proto WINAPI \
		   hdc: HDC,
	       logfont: ptr LOGFONTA,
		  font: ptr GpFont


;GpStatus
GdipCreateFontFromLogfontW proto WINAPI \
		   hdc: HDC,
	       logfont: ptr LOGFONTW,
		  font: ptr GpFont


;GpStatus
GdipCreateFont proto WINAPI \
	    fontFamily: ptr GpFontFamily,
		emSize: REAL,
		 style: SINT,
		  unit: Unit,
		  font: ptr GpFont


;GpStatus
GdipCloneFont proto WINAPI \
		  font: ptr,
	     cloneFont: ptr


;GpStatus
GdipDeleteFont proto WINAPI \
		  font: ptr


;GpStatus
GdipGetFamily proto WINAPI \
		  font: ptr GpFont,
		family: ptr GpFontFamily


;GpStatus
GdipGetFontStyle proto WINAPI \
		  font: ptr GpFont,
		 style: ptr SINT


;GpStatus
GdipGetFontSize proto WINAPI \
		  font: ptr GpFont,
		  size: ptr REAL


;GpStatus
GdipGetFontUnit proto WINAPI \
		  font: ptr GpFont,
		  unit: ptr Unit


;GpStatus
GdipGetFontHeight proto WINAPI \
		  font: ptr GpFont,
	      graphics: ptr GpGraphics,
		height: ptr REAL


;GpStatus
GdipGetFontHeightGivenDPI proto WINAPI \
		  font: ptr GpFont,
		   dpi: REAL,
		height: ptr REAL


;GpStatus
GdipGetLogFontA proto WINAPI \
		  font: ptr,
	      graphics: ptr GpGraphics,
	      logfontA: ptr


;GpStatus
GdipGetLogFontW proto WINAPI \
		  font: ptr,
	      graphics: ptr GpGraphics,
	      logfontW: ptr


;GpStatus
GdipNewInstalledFontCollection proto WINAPI \
	fontCollection: ptr


;GpStatus
GdipNewPrivateFontCollection proto WINAPI \
	fontCollection: ptr


;GpStatus
GdipDeletePrivateFontCollection proto WINAPI \
	fontCollection: ptr


;GpStatus
GdipGetFontCollectionFamilyCount proto WINAPI \
	fontCollection: ptr,
	      numFound: ptr


;GpStatus
GdipGetFontCollectionFamilyList proto WINAPI \
	fontCollection: ptr,
	     numSought: SINT,
	    gpfamilies: ptr,
	      numFound: ptr


;GpStatus
GdipPrivateAddFontFile proto WINAPI \
	fontCollection: ptr,
	      filename: ptr


;GpStatus
GdipPrivateAddMemoryFont proto WINAPI \
	fontCollection: ptr,
		memory: ptr,
		length: SINT


;;----------------------------------------------------------------------------
;; Text APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipDrawString proto WINAPI \
	      graphics: ptr GpGraphics,
		string: ptr WCHAR,
		length: SINT,
		  font: ptr GpFont,
	    layoutRect: ptr RectF,
	  stringFormat: ptr GpStringFormat,
		 brush: ptr GpBrush


;GpStatus
GdipMeasureString proto WINAPI \
	      graphics: ptr GpGraphics,
		string: ptr WCHAR,
		length: SINT,
		  font: ptr GpFont,
	    layoutRect: ptr RectF,
	  stringFormat: ptr GpStringFormat,
	   boundingBox: ptr RectF,
      codepointsFitted: ptr SINT,
	   linesFilled: ptr SINT


;GpStatus
GdipMeasureCharacterRanges proto WINAPI \
	      graphics: ptr GpGraphics,
		string: ptr WCHAR,
		length: SINT,
		  font: ptr GpFont,
	    layoutRect: ptr,
	  stringFormat: ptr GpStringFormat,
	   regionCount: SINT,
	       regions: ptr GpRegion


;GpStatus
GdipDrawDriverString proto WINAPI \
	      graphics: ptr GpGraphics,
		  text: ptr UINT16,
		length: SINT,
		  font: ptr GpFont,
		 brush: ptr GpBrush,
	     positions: ptr PointF,
		 flags: SINT,
		matrix: ptr GpMatrix


;GpStatus
GdipMeasureDriverString proto WINAPI \
	      graphics: ptr GpGraphics,
		  text: ptr UINT16,
		length: SINT,
		  font: ptr GpFont,
	     positions: ptr PointF,
		 flags: SINT,
		matrix: ptr GpMatrix,
	   boundingBox: ptr RectF


;;----------------------------------------------------------------------------
;; String format APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipCreateStringFormat proto WINAPI \
      formatAttributes: SINT,
	      language: LANGID,
		format: ptr GpStringFormat


;GpStatus
GdipStringFormatGetGenericDefault proto WINAPI \
		format: ptr GpStringFormat


;GpStatus
GdipStringFormatGetGenericTypographic proto WINAPI \
		format: ptr GpStringFormat


;GpStatus
GdipDeleteStringFormat proto WINAPI \
		format: ptr GpStringFormat


;GpStatus
GdipCloneStringFormat proto WINAPI \
		format: ptr GpStringFormat,
	     newFormat: ptr GpStringFormat


;GpStatus
GdipSetStringFormatFlags proto WINAPI \
		format: ptr GpStringFormat,
		 flags: SINT


;GpStatus
GdipGetStringFormatFlags proto WINAPI \
		format: ptr GpStringFormat,
		 flags: ptr SINT


;GpStatus
GdipSetStringFormatAlign proto WINAPI \
		format: ptr GpStringFormat,
		_align: StringAlignment


;GpStatus
GdipGetStringFormatAlign proto WINAPI \
		format: ptr GpStringFormat,
		_align: ptr StringAlignment


;GpStatus
GdipSetStringFormatLineAlign proto WINAPI \
		format: ptr GpStringFormat,
		_align: StringAlignment


;GpStatus
GdipGetStringFormatLineAlign proto WINAPI \
		format: ptr GpStringFormat,
		_align: ptr StringAlignment


;GpStatus
GdipSetStringFormatTrimming proto WINAPI \
		format: ptr GpStringFormat,
	      trimming: StringTrimming


;GpStatus
GdipGetStringFormatTrimming proto WINAPI \
		format: ptr GpStringFormat,
	      trimming: ptr StringTrimming


;GpStatus
GdipSetStringFormatHotkeyPrefix proto WINAPI \
		format: ptr GpStringFormat,
	  hotkeyPrefix: SINT


;GpStatus
GdipGetStringFormatHotkeyPrefix proto WINAPI \
		format: ptr GpStringFormat,
	  hotkeyPrefix: ptr SINT


;GpStatus
GdipSetStringFormatTabStops proto WINAPI \
		format: ptr GpStringFormat,
	firstTabOffset: REAL,
		 count: SINT,
	      tabStops: ptr REAL


;GpStatus
GdipGetStringFormatTabStops proto WINAPI \
		format: ptr GpStringFormat,
		 count: SINT,
	firstTabOffset: ptr REAL,
	      tabStops: ptr REAL


;GpStatus
GdipGetStringFormatTabStopCount proto WINAPI \
		format: ptr GpStringFormat,
		 count: ptr


;GpStatus
GdipSetStringFormatDigitSubstitution proto WINAPI \
		format: ptr GpStringFormat,
	      language: LANGID,
	    substitute: StringDigitSubstitute


;GpStatus
GdipGetStringFormatDigitSubstitution proto WINAPI \
		format: ptr GpStringFormat,
	      language: ptr LANGID,
	    substitute: ptr StringDigitSubstitute


;GpStatus
GdipGetStringFormatMeasurableCharacterRangeCount proto WINAPI \
		format: ptr GpStringFormat,
		 count: ptr SINT


;GpStatus
GdipSetStringFormatMeasurableCharacterRanges proto WINAPI \
		format: ptr GpStringFormat,
	    rangeCount: SINT,
		ranges: ptr CharacterRange


;;----------------------------------------------------------------------------
;; Cached Bitmap APIs
;;----------------------------------------------------------------------------

;GpStatus
GdipCreateCachedBitmap proto WINAPI \
		bitmap: ptr GpBitmap,
	      graphics: ptr GpGraphics,
	  cachedBitmap: ptr GpCachedBitmap


;GpStatus
GdipDeleteCachedBitmap proto WINAPI \
	  cachedBitmap: ptr GpCachedBitmap


;GpStatus
GdipDrawCachedBitmap proto WINAPI \
	      graphics: ptr GpGraphics,
	  cachedBitmap: ptr GpCachedBitmap,
		     x: SINT,
		     y: SINT


;UINT
GdipEmfToWmfBits proto WINAPI \
		  hemf: HENHMETAFILE,
	      cbData16: UINT,
	       pData16: LPBYTE,
	      iMapMode: SINT,
		eFlags: SINT


;GpStatus
GdipSetImageAttributesCachedBackground proto WINAPI \
	     imageattr: ptr GpImageAttributes,
	    enableFlag: BOOL


;GpStatus
GdipTestControl proto WINAPI \
	       control: GpTestControlEnum,


;GpStatus
GdiplusNotificationHook proto WINAPI \
		 token: ptr ULONG_PTR


;VOID
GdiplusNotificationUnhook proto WINAPI \
		 token: ULONG_PTR


if (GDIPVER GE 0x0110)
;GpStatus
GdipConvertToEmfPlus proto WINAPI \
	   refGraphics: ptr,
	      metafile: ptr,
 conversionFailureFlag: ptr,
	       emfType: EmfType,
	   description: ptr,
	  out_metafile: ptr


;GpStatus
GdipConvertToEmfPlusToFile proto WINAPI \
	   refGraphics: ptr,
	      metafile: ptr,
 conversionFailureFlag: ptr,
	      filename: ptr,
	       emfType: EmfType,
	   description: ptr,
	  out_metafile: ptr


;GpStatus
GdipConvertToEmfPlusToStream proto WINAPI \
	   refGraphics: ptr,
	      metafile: ptr,
 conversionFailureFlag: ptr,
		stream: ptr,
	       emfType: EmfType,
	   description: ptr,
	  out_metafile: ptr

endif ;;(GDIPVER GE 0x0110)

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif ;; NOT _FLATAPI_H
