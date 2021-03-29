
;;
;; The following is a relatively simple implementation of realizations, built
;; on top of Direct2D's mesh and opacity mask primitives (meshes for aliased and
;; multi-sampled anti-aliased rendering and opacity masks for per-primitive
;; anti-aliased rendering).
;;
;; One IGeometryRealization object can hold up to 4 "sub-realizations",
;; corresponding to the matrix {Aliased, PPAA} x {Filled, Stroked}. The user
;; can specify which sub-realizations to generate by passing in the appropriate
;; REALIZATION_CREATION_OPTIONS.
;;
;; The implementation of the PPAA realizations is somewhat primitive. It will
;; attempt to reuse existing bitmaps when possible, but it will not, for
;; instance, attempt to use a single bitmap to store multiple realizations
;; ("atlasing"). An atlased implementation would be somewhat more performant,
;; as the number of state switches that Direct2D would have to make when
;; interleaving realizations of different geometries would be greatly reduced.
;;
;; Another limitation in the PPAA implementation below is that it can use very
;; large amounts of video-memory even for very simple primitives. Consider, for
;; instance, a thin diagonal line stretching from the top-left corner of the
;; render-target to the bottom-right. To store this as a single opacity mask, a
;; bitmap the size of the entire render target must be created, even though the
;; area of the stroke is very small. This can also have a severe impact on
;; performance, as the video card has to waste numerous cycles rendering fully-
;; transparent pixels.
;;
;; A more sophisticated implementation of PPAA realizations would divide the
;; geometry up into a grid of bitmaps. Grid cells that contained no
;; content or were fully covered by the geometry could be optimized away. The
;; partially covered grid cells could be atlased for a further boost in
;; performance.
;;

ifndef _MSVCRT
ifndef _NO_PRECOMPILED_HEADER_
include stdafx.inc
endif
end_module equ <end>
else
end_module equ <>
endif


;;+-----------------------------------------------------------------------------
;;
;;  Class:
;;      GeometryRealization
;;
;;------------------------------------------------------------------------------

    LPID2D1Mesh                 typedef ptr ID2D1Mesh
    LPID2D1BitmapRenderTarget   typedef ptr ID2D1BitmapRenderTarget
    LPID2D1StrokeStyle          typedef ptr ID2D1StrokeStyle
    LPID2D1RenderTarget         typedef ptr ID2D1RenderTarget

.class GeometryRealization : public IGeometryRealization

    m_pFillMesh                 LPID2D1Mesh ?
    m_pStrokeMesh               LPID2D1Mesh ?
    m_pFillRT                   LPID2D1BitmapRenderTarget ?
    m_pStrokeRT                 LPID2D1BitmapRenderTarget ?
    m_pGeometry                 LPID2D1Geometry ?
    m_pStrokeStyle              LPID2D1StrokeStyle ?
    m_strokeWidth               float ?
    m_fillMaskDestBounds        D2D1_RECT_F <>
    m_fillMaskSourceBounds      D2D1_RECT_F <>
    m_strokeMaskDestBounds      D2D1_RECT_F <>
    m_strokeMaskSourceBounds    D2D1_RECT_F <>
    m_pRT                       LPID2D1RenderTarget ?
    m_realizationTransformIsIdentity BOOL ?
    m_realizationTransform      D2D1_MATRIX_3X2_F <>
    m_realizationTransformInv   D2D1_MATRIX_3X2_F <>
    m_swRT                      BOOL ?
    m_maxRealizationDimension   UINT ?
    m_cRef                      ULONG ?

    GeometryRealization proc

    Initialize proc \
            :ptr ID2D1RenderTarget,
            :UINT,
            :ptr ID2D1Geometry,
            :REALIZATION_CREATION_OPTIONS,
            :ptr D2D1_MATRIX_3X2_F,
            :float,
            :ptr ID2D1StrokeStyle

    GenerateOpacityMask proto \
            :BOOL,
            :ptr ID2D1RenderTarget,
            :UINT,
            :ptr ptr ID2D1BitmapRenderTarget,
            :ptr ID2D1Geometry,
            :ptr D2D1_MATRIX_3X2_F,
            :float,
            :ptr ID2D1StrokeStyle,
            :ptr D2D1_RECT_F,
            :ptr D2D1_RECT_F

    RenderToTarget proc \
            :BOOL,
            :ptr ID2D1RenderTarget,
            :ptr ID2D1Brush,
            :REALIZATION_RENDER_MODE

    .ends


;;+-----------------------------------------------------------------------------
;;
;;  Class:
;;      GeometryRealizationFactory
;;
;;------------------------------------------------------------------------------

.class GeometryRealizationFactory : public IGeometryRealizationFactory

    m_pRT                       LPID2D1RenderTarget ?
    m_cRef                      ULONG ?
    m_maxRealizationDimension   UINT ?

    GeometryRealizationFactory  proc
    Initialize                  proc :ptr ID2D1RenderTarget, :UINT
    .ends

    .code

;; The maximum granularity of bitmap sizes we allow for AA realizations.

sc_bitmapChunkSize equ 64.0

;;+-----------------------------------------------------------------------------
;;
;;  Function:
;;      CreateGeometryRealizationFactory
;;
;;------------------------------------------------------------------------------

CreateGeometryRealizationFactory proc \
    pRT:ptr ID2D1RenderTarget,
    maxRealizationDimension:UINT,
    ppFactory:ptr ptr IGeometryRealizationFactory

  local hr:HRESULT

   .new pFactory:ptr GeometryRealizationFactory()
    mov hr,E_OUTOFMEMORY
    .if rax
        mov hr,S_OK
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pFactory.Initialize(pRT, maxRealizationDimension)

        .if (SUCCEEDED(hr))

            mov rax,ppFactory
            mov rcx,pFactory
            mov [rax],rcx
            [rcx].IGeometryRealizationFactory.AddRef()
        .endif

        pFactory.Release()
    .endif

    .return hr

CreateGeometryRealizationFactory endp


;;+-----------------------------------------------------------------------------
;;
;;  Method:
;;      GeometryRealizationFactory::GeometryRealizationFactory
;;
;;------------------------------------------------------------------------------

GeometryRealizationFactory::GeometryRealizationFactory proc uses rdi

   .return .if !malloc(GeometryRealizationFactory + GeometryRealizationFactoryVtbl)

    mov rdx,rax
    add rax,GeometryRealizationFactory
    mov [rdx],rax
    lea rdi,[rdx+8]
    xor eax,eax
    mov ecx,(GeometryRealizationFactory - 8) / 8
    rep stosq
    inc [rdx].GeometryRealizationFactory.m_cRef

    for q,<Release,
           AddRef,
           Initialize,
           CreateGeometryRealization>
        lea rax,GeometryRealizationFactory_&q
        mov [rdi].GeometryRealizationFactoryVtbl.&q,rax
        endm

    mov rax,rdx
    ret

GeometryRealizationFactory::GeometryRealizationFactory endp

    assume rcx:ptr GeometryRealizationFactory


;;+-----------------------------------------------------------------------------
;;
;;  Method:
;;      GeometryRealizationFactory::Initialize
;;
;;------------------------------------------------------------------------------

GeometryRealizationFactory::Initialize proc uses rsi rdi pRT:ptr ID2D1RenderTarget,
    maxRealizationDimension:UINT

  local hr:HRESULT

    mov hr,S_OK

    .if r8d == 0

        ;;
        ;; 0-sized bitmaps aren't very useful for realizations, and
        ;; DXGI surface render targets don't support them, anyway.
        ;;
        mov hr,E_INVALIDARG
    .endif

    .if (SUCCEEDED(hr))

        mov [rcx].m_pRT,rdx
        mov rsi,rcx
        mov rdi,rdx

        [rdi].ID2D1RenderTarget.AddRef()
        .ifd [rdi].ID2D1RenderTarget.GetMaximumBitmapSize() > maxRealizationDimension
            mov eax,maxRealizationDimension
        .endif
        mov rcx,rsi
        mov [rcx].m_maxRealizationDimension,eax
    .endif

    .return hr

GeometryRealizationFactory::Initialize endp

;;+-----------------------------------------------------------------------------
;;
;;  Method:
;;      GeometryRealizationFactory::CreateGeometryRealization
;;
;;------------------------------------------------------------------------------

GeometryRealizationFactory::CreateGeometryRealization proc ppRealization:ptr ptr IGeometryRealization

  local hr:HRESULT

   .new pRealization:ptr GeometryRealization()
    mov hr,E_OUTOFMEMORY
    .if rax
        mov hr,S_OK
    .endif

    .if (SUCCEEDED(hr))

        mov rcx,this
        mov hr,pRealization.Initialize(
            [rcx].m_pRT,
            [rcx].m_maxRealizationDimension,
            NULL,
            REALIZATION_CREATION_OPTIONS_ALIASED,
            NULL,
            0.0,
            NULL
            )

        .if (SUCCEEDED(hr))

            mov rcx,ppRealization
            mov [rcx],pRealization
            pRealization.AddRef()
        .endif

        pRealization.Release()
    .endif

    .return hr

GeometryRealizationFactory::CreateGeometryRealization endp

;;+----------------------------------------------------------------------------
;;
;;  Method:
;;      GeometryRealization::GeometryRealization
;;
;;-----------------------------------------------------------------------------

    assume rcx:ptr GeometryRealization

GeometryRealization::GeometryRealization proc uses rdi

   .return .if !malloc(GeometryRealization + GeometryRealizationVtbl)

    mov rdx,rax
    add rax,GeometryRealization
    mov [rdx],rax
    lea rdi,[rdx+8]
    xor eax,eax
    mov ecx,(GeometryRealization - 8) / 8
    rep stosq
    inc [rdx].GeometryRealization.m_cRef
    for q,<Release,AddRef,Initialize,Fill,Draw,Update,RenderToTarget>
        lea rax,GeometryRealization_&q
        mov [rdi].GeometryRealizationVtbl.&q,rax
        endm
    mov rax,rdx
    ret

GeometryRealization::GeometryRealization endp

;;+-----------------------------------------------------------------------------
;;
;;  Method:
;;      GeometryRealization::Fill
;;
;;------------------------------------------------------------------------------

GeometryRealization::Fill proc \
    pRT     : ptr ID2D1RenderTarget,
    pBrush  : ptr ID2D1Brush,
    mode    : REALIZATION_RENDER_MODE

    [rcx].RenderToTarget(TRUE, rdx, r8, r9d)
    ret

GeometryRealization::Fill endp


;;+-----------------------------------------------------------------------------
;;
;;  Method:
;;      GeometryRealization::Draw
;;
;;------------------------------------------------------------------------------

GeometryRealization::Draw proc \
    pRT     : ptr ID2D1RenderTarget,
    pBrush  : ptr ID2D1Brush,
    mode    : REALIZATION_RENDER_MODE

    [rcx].RenderToTarget(FALSE, rdx, r8, r9d)
    ret

GeometryRealization::Draw endp


;;+-----------------------------------------------------------------------------
;;
;;  Method:
;;      GeometryRealization::Update
;;
;;  Description:
;;      Discard the current realization's contents and replace with new
;;      contents.
;;
;;      Note: This method attempts to reuse the existing bitmaps (but will
;;      replace the bitmaps if they aren't large enough). Since the cost of
;;      destroying a texture can be surprisingly astronomical, using this
;;      method can be substantially more performant than recreating a new
;;      realization every time.
;;
;;      Note: Here, pWorldTransform is the transform that the realization will
;;      be optimized for. If, at the time of rendering, the render target's
;;      transform is the same as the pWorldTransform passed in here then the
;;      realization will look identical to the unrealized version. Otherwise,
;;      quality will be degraded.
;;
;;------------------------------------------------------------------------------

    assume rcx:nothing
    assume rsi:ptr GeometryRealization

GeometryRealization::Update proc uses rsi rdi rbx \
    pGeometry       : ptr ID2D1Geometry,
    options         : REALIZATION_CREATION_OPTIONS,
    pWorldTransform : ptr D2D1_MATRIX_3X2_F,
    strokeWidth     : real4,
    pIStrokeStyle   : ptr ID2D1StrokeStyle


  local hr:HRESULT

    mov rsi,rcx
    mov hr,S_OK
    lea rcx,[rsi].m_realizationTransform
    .if r9
        mov [rsi].m_realizationTransform,[r9]
        mov [rsi].m_realizationTransformIsIdentity,[rcx].Matrix3x2F.IsIdentity()
    .else
        [rcx].Matrix3x2F.Identity()
        mov [rsi].m_realizationTransformIsIdentity,TRUE
    .endif

    ;;
    ;; We're about to create our realizations with the world transform applied
    ;; to them.  When we go to actually render the realization, though, we'll
    ;; want to "undo" this realization and instead apply the render target's
    ;; current transform.
    ;;
    ;; Note: we keep track to see if the passed in realization transform is the
    ;; identity.  This is a small optimization that saves us from having to
    ;; multiply matrices when we go to draw the realization.
    ;;

    mov [rsi].m_realizationTransformInv,[rcx]
    lea rcx,[rsi].m_realizationTransformInv
    [rcx].Matrix3x2F.Invert()

    .if ((options & REALIZATION_CREATION_OPTIONS_UNREALIZED) || [rsi].m_swRT)

        SafeReplace(&[rsi].m_pGeometry, pGeometry)
        SafeReplace(&[rsi].m_pStrokeStyle, pIStrokeStyle)
        mov [rsi].m_strokeWidth,strokeWidth
    .endif

    .if (options & REALIZATION_CREATION_OPTIONS_ANTI_ALIASED)

        ;;
        ;; Antialiased realizations are implemented using opacity masks.
        ;;

        .if (options & REALIZATION_CREATION_OPTIONS_FILLED)

            mov hr,GenerateOpacityMask(
                    TRUE, ;; => filled
                    [rsi].m_pRT,
                    [rsi].m_maxRealizationDimension,
                    &[rsi].m_pFillRT,
                    pGeometry,
                    pWorldTransform,
                    strokeWidth,
                    pIStrokeStyle,
                    &[rsi].m_fillMaskDestBounds,
                    &[rsi].m_fillMaskSourceBounds
                    )
        .endif

        .if (SUCCEEDED(hr) && options & REALIZATION_CREATION_OPTIONS_STROKED)

            mov hr,GenerateOpacityMask(
                    FALSE, ;; => stroked
                    [rsi].m_pRT,
                    [rsi].m_maxRealizationDimension,
                    &[rsi].m_pStrokeRT,
                    pGeometry,
                    pWorldTransform,
                    strokeWidth,
                    pIStrokeStyle,
                    &[rsi].m_strokeMaskDestBounds,
                    &[rsi].m_strokeMaskSourceBounds
                    )
        .endif
    .endif

    .if (SUCCEEDED(hr) && options & REALIZATION_CREATION_OPTIONS_ALIASED)

        ;;
        ;; Aliased realizations are implemented using meshes.
        ;;

        .if (options & REALIZATION_CREATION_OPTIONS_FILLED)

           .new pMesh:ptr ID2D1Mesh
            mov pMesh,NULL

            mov hr,this.m_pRT.CreateMesh(&pMesh)
            .if (SUCCEEDED(hr))

               .new pSink:ptr ID2D1TessellationSink
                mov pSink,NULL
                mov hr,pMesh.Open(&pSink)
                .if (SUCCEEDED(hr))

                    mov hr,pGeometry.Tessellate(
                            pWorldTransform,
                            0.25,
                            pSink
                            )
                    .if (SUCCEEDED(hr))

                        mov hr,pSink.Close()
                        .if (SUCCEEDED(hr))

                            SafeReplace(&[rsi].m_pFillMesh, pMesh)
                        .endif
                    .endif
                    pSink.Release()
                .endif
                pMesh.Release()
            .endif
        .endif

        .if (SUCCEEDED(hr) && options & REALIZATION_CREATION_OPTIONS_STROKED)

            ;;
            ;; In order generate the mesh corresponding to the stroke of a
            ;; geometry, we first "widen" the geometry and then tessellate the
            ;; result.
            ;;
           .new pFactory:ptr ID2D1Factory
            mov pFactory,NULL

            this.m_pRT.GetFactory(&pFactory)

           .new pPathGeometry:ptr ID2D1PathGeometry
            mov pPathGeometry,NULL
            mov hr,pFactory.CreatePathGeometry(&pPathGeometry)

            .if (SUCCEEDED(hr))

               .new pGeometrySink:ptr ID2D1GeometrySink
                mov pGeometrySink,NULL
                mov hr,pPathGeometry.Open(&pGeometrySink)
                .if (SUCCEEDED(hr))

                    mov hr,pGeometry.Widen(
                            strokeWidth,
                            pIStrokeStyle,
                            pWorldTransform,
                            0.25,
                            pGeometrySink
                            )

                    .if (SUCCEEDED(hr))

                        mov hr,pGeometrySink.Close()
                        .if (SUCCEEDED(hr))

                           .new pMesh:ptr ID2D1Mesh
                            mov pMesh,NULL

                            mov hr,this.m_pRT.CreateMesh(&pMesh)
                            .if (SUCCEEDED(hr))

                               .new pSink:ptr ID2D1TessellationSink
                                mov pSink,NULL
                                mov hr,pMesh.Open(&pSink)
                                .if (SUCCEEDED(hr))

                                    mov hr,pPathGeometry.Tessellate(
                                            NULL, ;; world transform (already handled in Widen)
                                            0.25,
                                            pSink
                                            )
                                    .if (SUCCEEDED(hr))

                                        mov hr,pSink.Close()
                                        .if (SUCCEEDED(hr))

                                            SafeReplace(&[rsi].m_pStrokeMesh, pMesh)
                                        .endif
                                    .endif
                                    pSink.Release()
                                .endif
                                pMesh.Release()
                            .endif
                        .endif
                    .endif
                    pGeometrySink.Release()
                .endif
                pPathGeometry.Release()
            .endif
            pFactory.Release()
        .endif
    .endif

    .return hr

GeometryRealization::Update endp

;;+-----------------------------------------------------------------------------
;;
;;  Method:
;;      GeometryRealization::RenderToTarget
;;
;;------------------------------------------------------------------------------

GeometryRealization::RenderToTarget proc uses rsi \
    fill        : BOOL,
    pRT         : ptr ID2D1RenderTarget,
    pBrush      : ptr ID2D1Brush,
    mode        : REALIZATION_RENDER_MODE

  local hr:HRESULT
  local originalAAMode:D2D1_ANTIALIAS_MODE
  local originalTransform:D2D1_MATRIX_3X2_F

    mov rsi,rcx
    mov hr,S_OK
    mov originalAAMode,pRT.GetAntialiasMode()

    .if ( ( ( mode == REALIZATION_RENDER_MODE_DEFAULT ) && [rsi].m_swRT ) || \
            ( mode == REALIZATION_RENDER_MODE_FORCE_UNREALIZED ) )

        .if ![rsi].m_pGeometry

            ;; We're being asked to render the geometry unrealized, but we
            ;; weren't created with REALIZATION_CREATION_OPTIONS_UNREALIZED.
            mov hr,E_FAIL
        .endif

        .if (SUCCEEDED(hr))

            .if fill

                pRT.FillGeometry([rsi].m_pGeometry, pBrush, NULL)

            .else

                pRT.DrawGeometry(
                    [rsi].m_pGeometry,
                    pBrush,
                    [rsi].m_strokeWidth,
                    [rsi].m_pStrokeStyle
                    )
            .endif
        .endif

    .else

        .if (originalAAMode != D2D1_ANTIALIAS_MODE_ALIASED)

            pRT.SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED)
        .endif

        .if (![rsi].m_realizationTransformIsIdentity)

            pRT.GetTransform(&originalTransform)
            lea rcx,[rsi].m_realizationTransformInv
            [rcx].Matrix3x2F.SetProduct(rcx, &originalTransform)
            pRT.SetTransform(rax)
        .endif

        .if (originalAAMode == D2D1_ANTIALIAS_MODE_PER_PRIMITIVE)

            .if fill

                .if ![rsi].m_pFillRT

                    mov hr,E_FAIL
                .endif
                .if (SUCCEEDED(hr))

                   .new pBitmap:ptr ID2D1Bitmap = NULL

                    this.m_pFillRT.GetBitmap(&pBitmap)

                    ;;
                    ;; Note: The antialias mode must be set to aliased prior to calling
                    ;; FillOpacityMask.
                    ;;
                    pRT.FillOpacityMask?(
                        pBitmap,
                        pBrush,
                        D2D1_OPACITY_MASK_CONTENT_GRAPHICS,
                        &[rsi].m_fillMaskDestBounds,
                        &[rsi].m_fillMaskSourceBounds
                        )

                    pBitmap.Release()
                .endif

            .else

                .if (![rsi].m_pStrokeRT)

                    mov hr,E_FAIL
                .endif
                .if (SUCCEEDED(hr))

                   .new pBitmap:ptr ID2D1Bitmap = NULL

                    this.m_pStrokeRT.GetBitmap(&pBitmap)

                    ;;
                    ;; Note: The antialias mode must be set to aliased prior to calling
                    ;; FillOpacityMask.
                    ;;
                    pRT.FillOpacityMask?(
                        pBitmap,
                        pBrush,
                        D2D1_OPACITY_MASK_CONTENT_GRAPHICS,
                        &[rsi].m_strokeMaskDestBounds,
                        &[rsi].m_strokeMaskSourceBounds
                        )

                    pBitmap.Release()
                .endif
            .endif

        .else

            .if fill

                .if ![rsi].m_pFillMesh

                    mov hr,E_FAIL
                .endif
                .if (SUCCEEDED(hr))

                    pRT.FillMesh([rsi].m_pFillMesh, pBrush)
                .endif

            .else

                .if (![rsi].m_pStrokeMesh)

                    mov hr,E_FAIL
                .endif
                .if (SUCCEEDED(hr))

                    pRT.FillMesh([rsi].m_pStrokeMesh, pBrush)
                .endif
            .endif
        .endif

        .if (SUCCEEDED(hr))

            pRT.SetAntialiasMode(originalAAMode)

            .if (![rsi].m_realizationTransformIsIdentity)

                pRT.SetTransform(&originalTransform)
            .endif
        .endif
    .endif

    .return hr

GeometryRealization::RenderToTarget endp

;;+-----------------------------------------------------------------------------
;;
;;  Method:
;;      GeometryRealization::Initialize
;;
;;------------------------------------------------------------------------------

GeometryRealization::Initialize proc uses rsi \
    pRT                     : ptr ID2D1RenderTarget,
    maxRealizationDimension : UINT,
    pGeometry               : ptr ID2D1Geometry,
    options                 : REALIZATION_CREATION_OPTIONS,
    pWorldTransform         : ptr D2D1_MATRIX_3X2_F,
    strokeWidth             : float,
    pIStrokeStyle           : ptr ID2D1StrokeStyle

  local hr:HRESULT

    mov rsi,rcx
    mov hr,S_OK
    mov [rsi].m_pRT,rdx
    pRT.AddRef()

   .new rtp:D2D1_RENDER_TARGET_PROPERTIES(D2D1_RENDER_TARGET_TYPE_SOFTWARE)

    mov [rsi].m_swRT,pRT.IsSupported(&rtp)
    mov [rsi].m_maxRealizationDimension,maxRealizationDimension

    .if (pGeometry)

        mov hr,[rsi].Update(pGeometry, options, pWorldTransform, strokeWidth, pIStrokeStyle)
    .endif

    .return hr

GeometryRealization::Initialize endp

;;+-----------------------------------------------------------------------------
;;
;;  Method:
;;      GeometryRealization::GenerateOpacityMask
;;
;;  Notes:
;;      This method is the trickiest part of doing realizations. Conceptually,
;;      we're creating a grayscale bitmap that represents the geometry. We'll
;;      reuse an existing bitmap if we can, but if not, we'll create the
;;      smallest possible bitmap that contains the geometry. In either, case,
;;      though, we'll keep track of the portion of the bitmap we actually used
;;      (the source bounds), so when we go to draw the realization, we don't
;;      end up drawing a bunch of superfluous transparent pixels.
;;
;;      We also have to keep track of the "dest" bounds, as more than likely
;;      the bitmap has to be translated by some amount before being drawn.
;;
;;------------------------------------------------------------------------------

GenerateOpacityMask proc \
    fill                    : BOOL,
    pBaseRT                 : ptr ID2D1RenderTarget,
    maxRealizationDimension : UINT,
    ppBitmapRT              : ptr ptr ID2D1BitmapRenderTarget,
    pIGeometry              : ptr ID2D1Geometry,
    pWorldTransform         : ptr D2D1_MATRIX_3X2_F,
    strokeWidth             : float,
    pStrokeStyle            : ptr ID2D1StrokeStyle,
    pMaskDestBounds         : ptr D2D1_RECT_F,
    pMaskSourceBounds       : ptr D2D1_RECT_F

  .new hr:HRESULT = S_OK
  .new bounds:D2D1_RECT_F
  .new inflatedPixelBounds:D2D1_RECT_F
  .new inflatedIntegerPixelSize:D2D1_SIZE_U
  .new currentRTSize:D2D1_SIZE_U
  .new dpiX:float, dpiY:float
  .new scaleX:float = 1.0
  .new scaleY:float = 1.0
  .new pCompatRT:ptr ID2D1BitmapRenderTarget = NULL
  .new pBrush:ptr ID2D1SolidColorBrush = NULL
  .new color:D3DCOLORVALUE = { 1.0, 1.0, 1.0, 1.0 }

    mov rax,ppBitmapRT
    mov rdx,[rax]
    SafeReplace(&pCompatRT, rdx)

    mov hr,pBaseRT.CreateSolidColorBrush(&color, NULL, &pBrush)

    .if (SUCCEEDED(hr))

        pBaseRT.GetDpi(&dpiX, &dpiY)

        .if fill
            mov hr,pIGeometry.GetBounds(pWorldTransform, &bounds)
        .else
            mov hr,pIGeometry.GetWidenedBounds(strokeWidth, pStrokeStyle, pWorldTransform, 0.25, &bounds)
        .endif

        .if (SUCCEEDED(hr))

            ;;
            ;; A rect where left > right is defined to be empty.
            ;;
            ;; The slightly baroque expression used below is an idiom that also
            ;; correctly handles NaNs (i.e., if any of the coordinates of the bounds is
            ;; a NaN, we want to treat the bounds as empty)
            ;;

            xor     eax,eax
            movss   xmm0,bounds.left
            comiss  xmm0,bounds.right
            setbe   al
            xor     ecx,ecx
            movss   xmm0,bounds.top
            comiss  xmm0,bounds.bottom
            setbe   cl

            .if ( !( eax ) || !( ecx ) )

                ;; Bounds are empty or ill-defined.

                ;; Make up a fake bounds
                mov inflatedPixelBounds.top,0.0
                mov inflatedPixelBounds.left,0.0
                mov inflatedPixelBounds.bottom,1.0
                mov inflatedPixelBounds.right,1.0

            .else

                ;;
                ;; We inflate the pixel bounds by 1 in each direction to ensure we have
                ;; a border of completely transparent pixels around the geometry.  This
                ;; ensures that when the realization is stretched the alpha ramp still
                ;; smoothly falls off to 0 rather than being clipped by the rect.
                ;;

                movss       xmm1,1.0
                movss       xmm3,96.0

                movss       xmm0,bounds.top
                mulss       xmm0,dpiY
                divss       xmm0,xmm3
                movss       xmm2,xmm0
                cvttps2dq   xmm0,xmm0
                cvtdq2ps    xmm0,xmm0
                cmpltps     xmm2,xmm0
                andps       xmm2,xmm1
                subss       xmm0,xmm2
                subss       xmm0,xmm1
                movss       inflatedPixelBounds.top,xmm0

                movss       xmm0,bounds.left
                mulss       xmm0,dpiX
                divss       xmm0,xmm3
                movss       xmm2,xmm0
                cvttps2dq   xmm0,xmm0
                cvtdq2ps    xmm0,xmm0
                cmpltps     xmm2,xmm0
                andps       xmm2,xmm1
                subss       xmm0,xmm2
                subss       xmm0,xmm1
                movss       inflatedPixelBounds.left,xmm0

                movss       xmm0,bounds.bottom
                mulss       xmm0,dpiY
                divss       xmm0,xmm3
                movd        edx,xmm0
                xor         edx,-0.0
                movd        xmm0,edx
                shr         edx,31
                cvttss2si   eax,xmm0
                sub         eax,edx
                neg         eax
                cvtsi2ss    xmm0,eax
                addss       xmm0,xmm1
                movss       inflatedPixelBounds.bottom,xmm0

                movss       xmm0,bounds.right
                mulss       xmm0,dpiX
                divss       xmm0,xmm3
                movd        edx,xmm0
                xor         edx,-0.0
                movd        xmm0,edx
                shr         edx,31
                cvttss2si   eax,xmm0
                sub         eax,edx
                neg         eax
                cvtsi2ss    xmm0,eax
                addss       xmm0,xmm1
                movss       inflatedPixelBounds.right,xmm0

            .endif


            ;;
            ;; Compute the width and height of the underlying bitmap we will need.
            ;; Note: We round up the width and height to be a multiple of
            ;; sc_bitmapChunkSize. We do this primarily to ensure that we aren't
            ;; constantly reallocating bitmaps in the case where a realization is being
            ;; zoomed in on slowly and updated frequently.
            ;;

            ;; Round up

            movss       xmm0,inflatedPixelBounds.right
            subss       xmm0,inflatedPixelBounds.left
            addss       xmm0,sc_bitmapChunkSize
            subss       xmm0,1.0
            divss       xmm0,sc_bitmapChunkSize
            mulss       xmm0,sc_bitmapChunkSize
            cvtss2si    eax,xmm0
            mov         inflatedIntegerPixelSize.width,eax

            movss       xmm0,inflatedPixelBounds.bottom
            subss       xmm0,inflatedPixelBounds.top
            addss       xmm0,sc_bitmapChunkSize
            subss       xmm0,1.0
            divss       xmm0,sc_bitmapChunkSize
            mulss       xmm0,sc_bitmapChunkSize
            cvtss2si    eax,xmm0
            mov         inflatedIntegerPixelSize.height,eax

            ;;
            ;; Compute the bounds we will pass to FillOpacityMask (which are in Device
            ;; Independent Pixels).
            ;;
            ;; Note: The DIP bounds do *not* use the rounded coordinates, since this
            ;; would cause us to render superfluous, fully-transparent pixels, which
            ;; would hurt fill rate.
            ;;
           .new inflatedDipBounds:D2D1_RECT_F

            movss xmm0,inflatedPixelBounds.left
            mulss xmm0,96.0
            divss xmm0,dpiX
            movss inflatedDipBounds.left,xmm0

            movss xmm0,inflatedPixelBounds.top
            mulss xmm0,96.0
            divss xmm0,dpiY
            movss inflatedDipBounds.top,xmm0

            movss xmm0,inflatedPixelBounds.right
            mulss xmm0,96.0
            divss xmm0,dpiX
            movss inflatedDipBounds.right,xmm0

            movss xmm0,inflatedPixelBounds.bottom
            mulss xmm0,96.0
            divss xmm0,dpiY
            movss inflatedDipBounds.bottom,xmm0

            .if pCompatRT

                pCompatRT.GetPixelSize(&currentRTSize)

            .else

                ;; This will force the creation of a new target
                mov currentRTSize.width,0
                mov currentRTSize.height,0
            .endif

            ;;
            ;; We need to ensure that our desired render target size isn't larger than
            ;; the max allowable bitmap size. If it is, we need to scale the bitmap
            ;; down by the appropriate amount.
            ;;
            mov eax,maxRealizationDimension
            .if inflatedIntegerPixelSize.width > eax

                cvtsi2ss    xmm0,eax
                cvtsi2ss    xmm1,inflatedIntegerPixelSize.width
                divss       xmm0,xmm1
                movss       scaleX,xmm0
                mov         inflatedIntegerPixelSize.width,eax
            .endif

            .if inflatedIntegerPixelSize.height > eax

                cvtsi2ss    xmm0,eax
                cvtsi2ss    xmm1,inflatedIntegerPixelSize.height
                divss       xmm0,xmm1
                movss       scaleY,xmm0
                mov         inflatedIntegerPixelSize.height,eax
            .endif


            ;;
            ;; If the necessary pixel dimensions are less than half the existing
            ;; bitmap's dimensions (in either direction), force the bitmap to be
            ;; reallocated to save memory.
            ;;
            ;; Note: The fact that we use > rather than >= is important for a subtle
            ;; reason: We'd like to have the property that repeated small changes in
            ;; geometry size do not cause repeated reallocations of memory. >= does not
            ;; ensure this property in the case where the geometry size is close to
            ;; sc_bitmapChunkSize, but > does.
            ;;
            ;; Example:
            ;;
            ;; Assume sc_bitmapChunkSize is 64 and the initial geometry width is 63
            ;; pixels. This will get rounded up to 64, and we will allocate a bitmap
            ;; with width 64. Now, say, we zoom in slightly, so the new geometry width
            ;; becomes 65 pixels. This will get rounded up to 128 pixels, and a new
            ;; bitmap will be allocated. Now, say the geometry drops back down to 63
            ;; pixels. This will get rounded up to 64. If we used >=, this would cause
            ;; another reallocation.  Since we use >, on the other hand, the 128 pixel
            ;; bitmap will be reused.
            ;;

            mov eax,inflatedIntegerPixelSize.width
            mov edx,inflatedIntegerPixelSize.height
            shl eax,1
            shl edx,1

            .if (currentRTSize.width > eax || currentRTSize.height > edx)

                SafeRelease(&pCompatRT, ID2D1BitmapRenderTarget)
                mov currentRTSize.width,0
                mov currentRTSize.height,0
            .endif

            .if (inflatedIntegerPixelSize.width > currentRTSize.width || \
                inflatedIntegerPixelSize.height > currentRTSize.height)

                SafeRelease(&pCompatRT, ID2D1BitmapRenderTarget)
            .endif

            .if !pCompatRT

                ;;
                ;; Make sure our new rendertarget is strictly larger than before.
                ;;
                mov eax,inflatedIntegerPixelSize.width
                .if currentRTSize.width < eax
                    mov currentRTSize.width,eax
                .endif

                mov eax,inflatedIntegerPixelSize.height
                .if currentRTSize.height < eax
                    mov currentRTSize.height,eax
                .endif

               .new alphaOnlyFormat:D2D1_PIXEL_FORMAT = {
                    DXGI_FORMAT_A8_UNORM,
                    D2D1_ALPHA_MODE_PREMULTIPLIED
                    }

                mov hr,pBaseRT.CreateCompatibleRenderTarget(
                    NULL, ;; desiredSize
                    &currentRTSize,
                    &alphaOnlyFormat,
                    D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE,
                    &pCompatRT
                    )
            .endif

            .if (SUCCEEDED(hr))

                ;;
                ;; Translate the geometry so it is flush against the left and top
                ;; sides of the render target.
                ;;
                movss xmm0,-0.0
                movss xmm1,inflatedDipBounds.left
                xorps xmm1,xmm0
                movss xmm2,inflatedDipBounds.top
                xorps xmm2,xmm0

               .new scale:Matrix3x2F
               .new translateMatrix:Matrix3x2F

                translateMatrix.Translation(xmm1, xmm2)
                scale.Scale(scaleX, scaleY)
                translateMatrix.SetProduct(&translateMatrix, &scale)

                .if pWorldTransform

                    translateMatrix.SetProduct(pWorldTransform, &translateMatrix)
                .endif
                pCompatRT.SetTransform(&translateMatrix)

                ;;
                ;; Render the geometry.
                ;;

                pCompatRT.BeginDraw()

                mov color.r,0.0
                mov color.g,0.0
                mov color.b,0.0
                mov color.a,0.0

                pCompatRT.Clear(&color)

                .if fill

                    pCompatRT.FillGeometry(pIGeometry, pBrush, NULL)

                .else

                    pCompatRT.DrawGeometry(pIGeometry, pBrush, strokeWidth, pStrokeStyle)
                .endif

                mov hr,pCompatRT.EndDraw(NULL, NULL)
                .if (SUCCEEDED(hr))

                    ;;
                    ;; Report back the source and dest bounds (to be used as input parameters
                    ;; to FillOpacityMask.
                    ;;

                    mov rdx,pMaskDestBounds
                    lea rcx,inflatedDipBounds

                    mov rax,[rcx]
                    mov [rdx],rax
                    mov rax,[rcx+8]
                    mov [rdx+8],rax

                    mov rdx,pMaskSourceBounds
                    xor eax,eax
                    mov [rdx],rax

                    movss xmm0,inflatedDipBounds.right
                    subss xmm0,inflatedDipBounds.left
                    mulss xmm0,scaleX
                    movss [rdx+8],xmm0
                    movss xmm0,inflatedDipBounds.bottom
                    subss xmm0,inflatedDipBounds.top
                    mulss xmm0,scaleY
                    movss [rdx+12],xmm0

                    mov rcx,ppBitmapRT
                    mov rax,[rcx]
                    .if rax != pCompatRT

                        SafeReplace(ppBitmapRT, pCompatRT)
                    .endif
                .endif
            .endif
        .endif
        pBrush.Release()
    .endif

    SafeRelease(&pCompatRT, ID2D1BitmapRenderTarget)

    .return hr

GenerateOpacityMask endp

;;+-----------------------------------------------------------------------------
;;
;;  Method:
;;      GeometryRealizationFactory::AddRef
;;
;;------------------------------------------------------------------------------

    assume rcx:ptr GeometryRealizationFactory

GeometryRealizationFactory::AddRef proc

    InterlockedIncrement(&[rcx].m_cRef)
    ret

GeometryRealizationFactory::AddRef endp

;;+-----------------------------------------------------------------------------
;;
;;  Method:
;;      GeometryRealizationFactory::Release
;;
;;------------------------------------------------------------------------------

GeometryRealizationFactory::Release proc

    .if !InterlockedDecrement(&[rcx].m_cRef)

        SafeRelease(&[rcx].m_pRT, ID2D1RenderTarget)
        free(this)
    .endif
    ret

GeometryRealizationFactory::Release endp

;;+-----------------------------------------------------------------------------
;;
;;  Method:
;;      GeometryRealizationFactory::QueryInterface
;;
;;------------------------------------------------------------------------------

GeometryRealizationFactory::QueryInterface proc iid:REFIID, ppvObject:ptr ptr
    ret
GeometryRealizationFactory::QueryInterface endp

;;+-----------------------------------------------------------------------------
;;
;;  Method:
;;      GeometryRealization::AddRef
;;
;;------------------------------------------------------------------------------

    assume rcx:ptr GeometryRealization

GeometryRealization::AddRef proc

    InterlockedIncrement(&[rcx].m_cRef)
    mov eax,[rcx].m_cRef
    ret

GeometryRealization::AddRef endp

;;+-----------------------------------------------------------------------------
;;
;;  Method:
;;      GeometryRealization::Release
;;
;;------------------------------------------------------------------------------

GeometryRealization::Release proc uses rsi

    mov rsi,rcx
    .if !InterlockedDecrement(&[rcx].m_cRef)

        SafeRelease(&[rsi].m_pFillMesh,     ID2D1Mesh)
        SafeRelease(&[rsi].m_pStrokeMesh,   ID2D1Mesh)
        SafeRelease(&[rsi].m_pFillRT,       ID2D1BitmapRenderTarget)
        SafeRelease(&[rsi].m_pStrokeRT,     ID2D1BitmapRenderTarget)
        SafeRelease(&[rsi].m_pGeometry,     ID2D1Geometry)
        SafeRelease(&[rsi].m_pStrokeStyle,  ID2D1StrokeStyle)
        SafeRelease(&[rsi].m_pRT,           ID2D1RenderTarget)
        free(rsi)
    .endif
    ret

GeometryRealization::Release endp

;;+-----------------------------------------------------------------------------
;;
;;  Method:
;;      GeometryRealization::QueryInterface
;;
;;------------------------------------------------------------------------------

GeometryRealization::QueryInterface proc iid:REFIID, ppvObject:ptr ptr
    ret
GeometryRealization::QueryInterface endp

    assume rcx:nothing
    assume rsi:nothing

end_module
