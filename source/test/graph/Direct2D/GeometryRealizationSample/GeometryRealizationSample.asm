; GEOMETRYREALIZATIONSAMPLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; From: https://github.com/microsoft/Windows-classic-samples/
;

include stdafx.inc

.code

CreateGeometryRealizationFactory proc pRT:ptr ID2D1RenderTarget, maxRealizationDimension:UINT, ppFactory:ptr ptr IGeometryRealizationFactory

   .new hr:HRESULT = E_OUTOFMEMORY
   .new pFactory:ptr GeometryRealizationFactory()

    .if rax
        mov hr,S_OK
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pFactory.Initialize(pRT, maxRealizationDimension)

        .if (SUCCEEDED(eax))

            mov rax,ppFactory
            mov rcx,pFactory
            mov [rax],rcx
            [rcx].IGeometryRealizationFactory.AddRef()
        .endif
        pFactory.Release()
    .endif
    .return hr
    endp


GeometryRealizationFactory::GeometryRealizationFactory proc

    .if @ComAlloc(GeometryRealizationFactory)
        inc [rax].GeometryRealizationFactory.m_cRef
    .endif
    ret
    endp


GeometryRealization::GeometryRealization proc

    .if @ComAlloc(GeometryRealization)
        inc [rax].GeometryRealization.m_cRef
    .endif
    ret
    endp


    assume class:rbx

GeometryRealizationFactory::Initialize proc pRT:ptr ID2D1RenderTarget, maxRealizationDimension:UINT

    .new hr:HRESULT = S_OK

    .if ( ldr(maxRealizationDimension) == 0 )
        ;
        ; 0-sized bitmaps aren't very useful for realizations, and
        ; DXGI surface render targets don't support them, anyway.
        ;
        mov hr,E_INVALIDARG
    .endif

    .if (SUCCEEDED(hr))

        mov m_pRT,ldr(pRT)

        m_pRT.AddRef()
        .ifd ( m_pRT.GetMaximumBitmapSize() > maxRealizationDimension )
            mov eax,maxRealizationDimension
        .endif
        mov m_maxRealizationDimension,eax
    .endif
    .return hr
    endp


GeometryRealizationFactory::CreateGeometryRealization proc ppRealization:ptr ptr IGeometryRealization

   .new hr:HRESULT = E_OUTOFMEMORY
   .new pRealization:ptr GeometryRealization()

    .if rax
        mov hr,S_OK
    .endif

    .if (SUCCEEDED(hr))

        mov hr,pRealization.Initialize(m_pRT, m_maxRealizationDimension,
                NULL, REALIZATION_CREATION_OPTIONS_ALIASED, NULL, 0.0, NULL)

        .if (SUCCEEDED(hr))

            mov rcx,ppRealization
            mov [rcx],pRealization
            pRealization.AddRef()
        .endif
        pRealization.Release()
    .endif
    .return hr
    endp



GeometryRealization::Fill proc pRT:ptr ID2D1RenderTarget, pBrush:ptr ID2D1Brush, mode:REALIZATION_RENDER_MODE

    RenderToTarget(TRUE, ldr(pRT), ldr(pBrush), ldr(mode))
    ret
    endp


GeometryRealization::Draw proc pRT:ptr ID2D1RenderTarget, pBrush:ptr ID2D1Brush, mode:REALIZATION_RENDER_MODE

    RenderToTarget(FALSE, ldr(pRT), ldr(pBrush), ldr(mode))
    ret
    endp


;
;  Description:
;      Discard the current realization's contents and replace with new
;      contents.
;
;      Note: This method attempts to reuse the existing bitmaps (but will
;      replace the bitmaps if they aren't large enough). Since the cost of
;      destroying a texture can be surprisingly astronomical, using this
;      method can be substantially more performant than recreating a new
;      realization every time.
;
;      Note: Here, pWorldTransform is the transform that the realization will
;      be optimized for. If, at the time of rendering, the render target's
;      transform is the same as the pWorldTransform passed in here then the
;      realization will look identical to the unrealized version. Otherwise,
;      quality will be degraded.
;

GeometryRealization::Update proc \
    pGeometry       : ptr ID2D1Geometry,
    options         : REALIZATION_CREATION_OPTIONS,
    pWorldTransform : ptr D2D1_MATRIX_3X2_F,
    strokeWidth     : real4,
    pIStrokeStyle   : ptr ID2D1StrokeStyle


   .new hr:HRESULT = S_OK

    ldr rcx,pWorldTransform
    .if rcx
        mov m_realizationTransform,[rcx]
        mov m_realizationTransformIsIdentity,m_realizationTransform.IsIdentity()
    .else
        m_realizationTransform.Identity()
        mov m_realizationTransformIsIdentity,TRUE
    .endif
    mov m_realizationTransformInv,m_realizationTransform
    m_realizationTransformInv.Invert()

    ;
    ; We're about to create our realizations with the world transform applied
    ; to them.  When we go to actually render the realization, though, we'll
    ; want to "undo" this realization and instead apply the render target's
    ; current transform.
    ;
    ; Note: we keep track to see if the passed in realization transform is the
    ; identity.  This is a small optimization that saves us from having to
    ; multiply matrices when we go to draw the realization.
    ;

    .if ( ( options & REALIZATION_CREATION_OPTIONS_UNREALIZED ) || m_swRT )

        SafeReplace(&m_pGeometry, pGeometry)
        SafeReplace(&m_pStrokeStyle, pIStrokeStyle)
        mov m_strokeWidth,strokeWidth
    .endif

    .if ( options & REALIZATION_CREATION_OPTIONS_ANTI_ALIASED )

        ; Antialiased realizations are implemented using opacity masks.

        .if ( options & REALIZATION_CREATION_OPTIONS_FILLED )

            ; => filled

            mov hr,GenerateOpacityMask(TRUE, m_pRT, m_maxRealizationDimension, &m_pFillRT, pGeometry,
                    pWorldTransform, strokeWidth, pIStrokeStyle, &m_fillMaskDestBounds, &m_fillMaskSourceBounds)
        .endif

        .if (SUCCEEDED(hr) && options & REALIZATION_CREATION_OPTIONS_STROKED)

            ; => stroked

            mov hr,GenerateOpacityMask(FALSE, m_pRT, m_maxRealizationDimension, &m_pStrokeRT, pGeometry,
                    pWorldTransform, strokeWidth, pIStrokeStyle, &m_strokeMaskDestBounds, &m_strokeMaskSourceBounds)
        .endif
    .endif

    .if ( SUCCEEDED(hr) && options & REALIZATION_CREATION_OPTIONS_ALIASED )

        ; Aliased realizations are implemented using meshes.

        .if ( options & REALIZATION_CREATION_OPTIONS_FILLED )

           .new pMesh:ptr ID2D1Mesh = NULL
            mov hr,m_pRT.CreateMesh(&pMesh)
            .if (SUCCEEDED(hr))

               .new pSink:ptr ID2D1TessellationSink = NULL
                mov hr,pMesh.Open(&pSink)
                .if (SUCCEEDED(hr))
                    mov hr,pGeometry.Tessellate(pWorldTransform, 0.25, pSink)
                    .if (SUCCEEDED(hr))
                        mov hr,pSink.Close()
                        .if (SUCCEEDED(hr))
                            SafeReplace(&m_pFillMesh, pMesh)
                        .endif
                    .endif
                    pSink.Release()
                .endif
                pMesh.Release()
            .endif
        .endif

        .if ( SUCCEEDED(hr) && options & REALIZATION_CREATION_OPTIONS_STROKED )

            ;
            ; In order generate the mesh corresponding to the stroke of a
            ; geometry, we first "widen" the geometry and then tessellate the
            ; result.
            ;
           .new pFactory:ptr ID2D1Factory = NULL
           .new pPathGeometry:ptr ID2D1PathGeometry = NULL

            m_pRT.GetFactory(&pFactory)

            mov hr,pFactory.CreatePathGeometry(&pPathGeometry)

            .if (SUCCEEDED(hr))

               .new pGeometrySink:ptr ID2D1GeometrySink = NULL
                mov hr,pPathGeometry.Open(&pGeometrySink)
                .if (SUCCEEDED(hr))

                    mov hr,pGeometry.Widen(strokeWidth, pIStrokeStyle, pWorldTransform, 0.25, pGeometrySink)

                    .if (SUCCEEDED(hr))

                        mov hr,pGeometrySink.Close()
                        .if (SUCCEEDED(hr))

                           .new pMesh:ptr ID2D1Mesh = NULL
                            mov hr,m_pRT.CreateMesh(&pMesh)
                            .if (SUCCEEDED(hr))
                               .new pSink:ptr ID2D1TessellationSink = NULL
                                mov hr,pMesh.Open(&pSink)
                                .if (SUCCEEDED(hr))

                                    ; world transform (already handled in Widen)

                                    mov hr,pPathGeometry.Tessellate(NULL, 0.25, pSink)
                                    .if (SUCCEEDED(hr))
                                        mov hr,pSink.Close()
                                        .if (SUCCEEDED(hr))
                                            SafeReplace(&m_pStrokeMesh, pMesh)
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
    endp


GeometryRealization::RenderToTarget proc fill:BOOL, pRT:ptr ID2D1RenderTarget, pBrush:ptr ID2D1Brush, mode:REALIZATION_RENDER_MODE

    .new hr:HRESULT = S_OK
    .new originalTransform:D2D1_MATRIX_3X2_F
    .new originalAAMode:D2D1_ANTIALIAS_MODE = pRT.GetAntialiasMode()


    .if ( ( ( mode == REALIZATION_RENDER_MODE_DEFAULT ) && m_swRT ) ||
            ( mode == REALIZATION_RENDER_MODE_FORCE_UNREALIZED ) )

        .if !m_pGeometry

            ; We're being asked to render the geometry unrealized, but we
            ; weren't created with REALIZATION_CREATION_OPTIONS_UNREALIZED.

            mov hr,E_FAIL
        .endif

        .if (SUCCEEDED(hr))

            .if ( fill )
                pRT.FillGeometry(m_pGeometry, pBrush, NULL)
            .else
                pRT.DrawGeometry(m_pGeometry, pBrush, m_strokeWidth, m_pStrokeStyle)
            .endif
        .endif

    .else

        .if ( originalAAMode != D2D1_ANTIALIAS_MODE_ALIASED )
            pRT.SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED)
        .endif

        .if ( !m_realizationTransformIsIdentity )

            pRT.GetTransform(&originalTransform)
            m_realizationTransformInv.SetProduct(&m_realizationTransformInv, &originalTransform)
            pRT.SetTransform(&m_realizationTransformInv)
        .endif

        .if ( originalAAMode == D2D1_ANTIALIAS_MODE_PER_PRIMITIVE )

            .if ( fill )

                .if ( !m_pFillRT )

                    mov hr,E_FAIL
                .endif

                .if ( SUCCEEDED(hr) )

                   .new pBitmap:ptr ID2D1Bitmap = NULL

                    m_pFillRT.GetBitmap(&pBitmap)

                    ;
                    ; Note: The antialias mode must be set to aliased prior to calling
                    ; FillOpacityMask.
                    ;

                    pRT.FillOpacityMask(pBitmap, pBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS,
                        &m_fillMaskDestBounds, &m_fillMaskSourceBounds)

                    pBitmap.Release()
                .endif

            .else

                .if ( !m_pStrokeRT )

                    mov hr,E_FAIL
                .endif

                .if (SUCCEEDED(hr))

                   .new pBitmap:ptr ID2D1Bitmap = NULL

                    m_pStrokeRT.GetBitmap(&pBitmap)

                    ;
                    ; Note: The antialias mode must be set to aliased prior to calling
                    ; FillOpacityMask.
                    ;
                    pRT.FillOpacityMask(pBitmap, pBrush, D2D1_OPACITY_MASK_CONTENT_GRAPHICS,
                        &m_strokeMaskDestBounds, &m_strokeMaskSourceBounds)

                    pBitmap.Release()
                .endif
            .endif

        .else

            .if ( fill )

                .if ( !m_pFillMesh )

                    mov hr,E_FAIL
                .endif
                .if (SUCCEEDED(hr))

                    pRT.FillMesh(m_pFillMesh, pBrush)
                .endif

            .else

                .if ( !m_pStrokeMesh )

                    mov hr,E_FAIL
                .endif
                .if (SUCCEEDED(hr))

                    pRT.FillMesh(m_pStrokeMesh, pBrush)
                .endif
            .endif
        .endif

        .if (SUCCEEDED(hr))

            pRT.SetAntialiasMode(originalAAMode)

            .if ( !m_realizationTransformIsIdentity )

                pRT.SetTransform(&originalTransform)
            .endif
        .endif
    .endif
    .return hr

GeometryRealization::RenderToTarget endp


GeometryRealization::Initialize proc \
    pRT                     : ptr ID2D1RenderTarget,
    maxRealizationDimension : UINT,
    pGeometry               : ptr ID2D1Geometry,
    options                 : REALIZATION_CREATION_OPTIONS,
    pWorldTransform         : ptr D2D1_MATRIX_3X2_F,
    strokeWidth             : float,
    pIStrokeStyle           : ptr ID2D1StrokeStyle

   .new hr:HRESULT = S_OK

    mov m_pRT,ldr(pRT)
    pRT.AddRef()

   .new rtp:D2D1_RENDER_TARGET_PROPERTIES(D2D1_RENDER_TARGET_TYPE_SOFTWARE)
    mov m_swRT,pRT.IsSupported(&rtp)
    mov m_maxRealizationDimension,maxRealizationDimension
    .if ( pGeometry )
        mov hr,Update(pGeometry, options, pWorldTransform, strokeWidth, pIStrokeStyle)
    .endif
    .return hr
    endp

;
;  Notes:
;      This method is the trickiest part of doing realizations. Conceptually,
;      we're creating a grayscale bitmap that represents the geometry. We'll
;      reuse an existing bitmap if we can, but if not, we'll create the
;      smallest possible bitmap that contains the geometry. In either, case,
;      though, we'll keep track of the portion of the bitmap we actually used
;      (the source bounds), so when we go to draw the realization, we don't
;      end up drawing a bunch of superfluous transparent pixels.
;
;      We also have to keep track of the "dest" bounds, as more than likely
;      the bitmap has to be translated by some amount before being drawn.
;

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

            ;
            ; A rect where left > right is defined to be empty.
            ;
            ; The slightly baroque expression used below is an idiom that also
            ; correctly handles NaNs (i.e., if any of the coordinates of the bounds is
            ; a NaN, we want to treat the bounds as empty)
            ;

            xor     eax,eax
            movss   xmm0,bounds.left
            comiss  xmm0,bounds.right
            setbe   al
            xor     ecx,ecx
            movss   xmm0,bounds.top
            comiss  xmm0,bounds.bottom
            setbe   cl

            .if ( !( eax ) || !( ecx ) )

                ; Bounds are empty or ill-defined.

                ; Make up a fake bounds

                mov inflatedPixelBounds.top,0.0
                mov inflatedPixelBounds.left,0.0
                mov inflatedPixelBounds.bottom,1.0
                mov inflatedPixelBounds.right,1.0

            .else

                ;
                ; We inflate the pixel bounds by 1 in each direction to ensure we have
                ; a border of completely transparent pixels around the geometry.  This
                ; ensures that when the realization is stretched the alpha ramp still
                ; smoothly falls off to 0 rather than being clipped by the rect.
                ;

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


            ;
            ; Compute the width and height of the underlying bitmap we will need.
            ; Note: We round up the width and height to be a multiple of
            ; sc_bitmapChunkSize. We do this primarily to ensure that we aren't
            ; constantly reallocating bitmaps in the case where a realization is being
            ; zoomed in on slowly and updated frequently.
            ;

            ; Round up

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

            ;
            ; Compute the bounds we will pass to FillOpacityMask (which are in Device
            ; Independent Pixels).
            ;
            ; Note: The DIP bounds do *not* use the rounded coordinates, since this
            ; would cause us to render superfluous, fully-transparent pixels, which
            ; would hurt fill rate.
            ;
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

            ;
            ; We need to ensure that our desired render target size isn't larger than
            ; the max allowable bitmap size. If it is, we need to scale the bitmap
            ; down by the appropriate amount.
            ;

            .if ( inflatedIntegerPixelSize.width > maxRealizationDimension )

                cvtsi2ss    xmm0,eax
                cvtsi2ss    xmm1,inflatedIntegerPixelSize.width
                divss       xmm0,xmm1
                movss       scaleX,xmm0
                mov         inflatedIntegerPixelSize.width,eax
            .endif

            .if ( inflatedIntegerPixelSize.height > eax )

                cvtsi2ss    xmm0,eax
                cvtsi2ss    xmm1,inflatedIntegerPixelSize.height
                divss       xmm0,xmm1
                movss       scaleY,xmm0
                mov         inflatedIntegerPixelSize.height,eax
            .endif


            ;
            ; If the necessary pixel dimensions are less than half the existing
            ; bitmap's dimensions (in either direction), force the bitmap to be
            ; reallocated to save memory.
            ;
            ; Note: The fact that we use > rather than >= is important for a subtle
            ; reason: We'd like to have the property that repeated small changes in
            ; geometry size do not cause repeated reallocations of memory. >= does not
            ; ensure this property in the case where the geometry size is close to
            ; sc_bitmapChunkSize, but > does.
            ;
            ; Example:
            ;
            ; Assume sc_bitmapChunkSize is 64 and the initial geometry width is 63
            ; pixels. This will get rounded up to 64, and we will allocate a bitmap
            ; with width 64. Now, say, we zoom in slightly, so the new geometry width
            ; becomes 65 pixels. This will get rounded up to 128 pixels, and a new
            ; bitmap will be allocated. Now, say the geometry drops back down to 63
            ; pixels. This will get rounded up to 64. If we used >=, this would cause
            ; another reallocation.  Since we use >, on the other hand, the 128 pixel
            ; bitmap will be reused.
            ;

            mov eax,inflatedIntegerPixelSize.width
            mov edx,inflatedIntegerPixelSize.height
            shl eax,1
            shl edx,1

            .if ( currentRTSize.width > eax || currentRTSize.height > edx )

                SafeRelease(pCompatRT)
                mov currentRTSize.width,0
                mov currentRTSize.height,0
            .endif

            .if ( inflatedIntegerPixelSize.width > currentRTSize.width || \
                    inflatedIntegerPixelSize.height > currentRTSize.height )

                SafeRelease(pCompatRT)
            .endif

            .if ( !pCompatRT )

                ;
                ; Make sure our new rendertarget is strictly larger than before.
                ;

                .if ( currentRTSize.width < inflatedIntegerPixelSize.width )
                    mov currentRTSize.width,eax
                .endif

                .if ( currentRTSize.height < inflatedIntegerPixelSize.height )
                    mov currentRTSize.height,eax
                .endif

               .new alphaOnlyFormat:D2D1_PIXEL_FORMAT = {
                    DXGI_FORMAT_A8_UNORM,
                    D2D1_ALPHA_MODE_PREMULTIPLIED
                    }

                mov hr,pBaseRT.CreateCompatibleRenderTarget(
                    NULL, ; desiredSize
                    &currentRTSize,
                    &alphaOnlyFormat,
                    D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE,
                    &pCompatRT
                    )
            .endif

            .if (SUCCEEDED(hr))

                ;
                ; Translate the geometry so it is flush against the left and top
                ; sides of the render target.
                ;
                movss xmm2,-0.0
                movss xmm0,inflatedDipBounds.left
                xorps xmm0,xmm2
                movss xmm1,inflatedDipBounds.top
                xorps xmm1,xmm2

               .new scale:Matrix3x2F
               .new translateMatrix:Matrix3x2F

                translateMatrix.Translation(xmm0, xmm1)
                scale.Scale(scaleX, scaleY)
                translateMatrix.SetProduct(&translateMatrix, &scale)

                .if pWorldTransform

                    translateMatrix.SetProduct(pWorldTransform, &translateMatrix)
                .endif
                pCompatRT.SetTransform(&translateMatrix)

                ;
                ; Render the geometry.
                ;

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

                    ;
                    ; Report back the source and dest bounds (to be used as input parameters
                    ; to FillOpacityMask.
                    ;

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

    SafeRelease(pCompatRT)
   .return hr

GenerateOpacityMask endp


GeometryRealizationFactory::AddRef proc

    InterlockedIncrement(&m_cRef)
    ret
    endp


GeometryRealizationFactory::Release proc

    .ifd ( !InterlockedDecrement(&m_cRef) )

        SafeRelease(m_pRT)
        free(rbx)
    .endif
    ret
    endp


GeometryRealizationFactory::QueryInterface proc iid:REFIID, ppvObject:ptr ptr
    ret
    endp


GeometryRealization::AddRef proc

    InterlockedIncrement(&m_cRef)
    ret
    endp


GeometryRealization::Release proc

    .if ( !InterlockedDecrement(&m_cRef) )

        SafeRelease(m_pFillMesh)
        SafeRelease(m_pStrokeMesh)
        SafeRelease(m_pFillRT)
        SafeRelease(m_pStrokeRT)
        SafeRelease(m_pGeometry)
        SafeRelease(m_pStrokeStyle)
        SafeRelease(m_pRT)
        free(rbx)
    .endif
    ret
    endp


GeometryRealization::QueryInterface proc iid:REFIID, ppvObject:ptr ptr
    ret
    endp



DemoApp::DemoApp proc tmring:ptr

  local time:LARGE_INTEGER

    ldr rbx,tmring
    @ComAlloc(DemoApp)
    xchg rax,rbx
    mov m_times,rax
    mov m_updateRealization,TRUE
    mov m_autoGeometryRegen,TRUE
    mov m_numSquares,sc_defaultNumSquares
    mov m_targetZoomFactor,1.0
    mov m_currentZoomFactor,1.0

    QueryPerformanceCounter(&time)
    mov rax,time.QuadPart
    neg rax
    mov m_timeDelta,rax
    mov rax,rbx
    ret
    endp


DemoApp::Release proc

    SafeRelease(m_pD2DFactory)
    SafeRelease(m_pWICFactory)
    SafeRelease(m_pDWriteFactory)
    SafeRelease(m_pRT)
    SafeRelease(m_pTextFormat)
    SafeRelease(m_pSolidColorBrush)
    SafeRelease(m_pRealization)
    SafeRelease(m_pGeometry)
    ret
    endp


DemoApp::Initialize proc

  local wcex:WNDCLASSEX
  local dpiX:float, dpiY:float

    ; Initialize device-indpendent resources, such
    ; as the Direct2D factory.

    .ifd ( !CreateDeviceIndependentResources() )

        ; Register the window class.

        mov wcex.cbSize,        WNDCLASSEX
        mov wcex.style,         CS_HREDRAW or CS_VREDRAW
        mov wcex.lpfnWndProc,   &WndProc
        mov wcex.cbClsExtra,    0
        mov wcex.cbWndExtra,    sizeof(LONG_PTR)
        mov wcex.hInstance,     HINST_THISCOMPONENT
        mov wcex.hIcon,         NULL
        mov wcex.hIconSm,       NULL
        mov wcex.hbrBackground, NULL
        mov wcex.lpszMenuName,  NULL
        mov wcex.hCursor,       LoadCursor(NULL, IDC_ARROW)
        mov wcex.lpszClassName, &@CStr("D2DDemoApp")

        RegisterClassEx(&wcex)

        ; Create the application window.
        ;
        ; Because the CreateWindow function takes its size in pixels, we
        ; obtain the system DPI and use it to scale the window size.

        m_pD2DFactory.GetDesktopDpi(&dpiX, &dpiY)

        movss       xmm0,dpiX
        mulss       xmm0,640.0
        divss       xmm0,96.0
        movd        eax,xmm0
        xor         eax,-0.0
        movd        xmm0,eax
        shr         eax,31
        cvttss2si   ecx,xmm0
        sub         ecx,eax
        neg         ecx

        movss       xmm0,dpiY
        mulss       xmm0,480.0
        divss       xmm0,96.0
        movd        eax,xmm0
        xor         eax,-0.0
        movd        xmm0,eax
        shr         eax,31
        cvttss2si   edx,xmm0
        sub         edx,eax
        neg         edx

        .if CreateWindowEx(0, "D2DDemoApp", "D2D Demo App", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                CW_USEDEFAULT, ecx, edx, NULL, NULL, HINST_THISCOMPONENT, rbx)

            mov m_hwnd,rax
            ShowWindow(m_hwnd, SW_SHOWNORMAL)
            UpdateWindow(m_hwnd)
            mov eax,S_OK
        .else
            mov eax,E_FAIL
        .endif
    .endif
    ret
    endp

;
;  This method is used to create resources which are not bound
;  to any device. Their lifetime effectively extends for the
;  duration of the app. These resources include the D2D,
;  DWrite, and WIC factories; and a DWrite Text Format object
;  (used for identifying particular font characteristics) and
;  a D2D geometry.
;

DemoApp::CreateDeviceIndependentResources proc

  local hr:HRESULT

    ; Create the Direct2D factory.

    mov hr,D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &IID_ID2D1Factory, NULL, &m_pD2DFactory)

    .if (SUCCEEDED(hr))

        ; Create WIC factory.

        mov hr,CoCreateInstance(&CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, &IID_IWICImagingFactory, &m_pWICFactory)
    .endif

    .if (SUCCEEDED(hr))

        ; Create a DirectWrite factory.

        mov hr,DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, &IID_IDWriteFactory, &m_pDWriteFactory)
    .endif


    .if (SUCCEEDED(hr))

        ; Create a DirectWrite text format object.

        mov hr,m_pDWriteFactory.CreateTextFormat(sc_fontName, NULL, DWRITE_FONT_WEIGHT_NORMAL,
                DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, sc_fontSize, L"", &m_pTextFormat)
    .endif
    .return hr
    endp

;
;  This method creates resources which are bound to a particular
;  D3D device. It's all centralized here, in case the resources
;  need to be recreated in case of D3D device loss (eg. display
;  change, remoting, removal of video card, etc).
;

DemoApp::CreateDeviceResources proc

    .new hr:HRESULT = S_OK
    .new rc:RECT
    .new pRealizationFactory:ptr IGeometryRealizationFactory = NULL

    .if ( !m_pRT )

        GetClientRect(m_hwnd, &rc)

        ; Create a Direct2D render target.

       .new p:D2D1_RENDER_TARGET_PROPERTIES
        mov p.type,     D2D1_RENDER_TARGET_TYPE_DEFAULT
        mov p.dpiX,     0.0
        mov p.dpiY,     0.0
        mov p.usage,    D2D1_RENDER_TARGET_USAGE_NONE
        mov p.minLevel, D2D1_FEATURE_LEVEL_DEFAULT
        mov p.pixelFormat.format,DXGI_FORMAT_UNKNOWN
        mov p.pixelFormat.alphaMode,D2D1_ALPHA_MODE_UNKNOWN

       .new h:D2D1_HWND_RENDER_TARGET_PROPERTIES
        mov h.hwnd,m_hwnd
        mov eax,rc.bottom
        sub eax,rc.top
        mov h.pixelSize.height,eax
        mov eax,rc.right
        sub eax,rc.left
        mov h.pixelSize.width,eax
        mov h.presentOptions,D2D1_PRESENT_OPTIONS_NONE

        mov hr,m_pD2DFactory.CreateHwndRenderTarget(&p, &h, &m_pRT)

        .if (SUCCEEDED(hr))

            ; Create brushes.

           .new color:D3DCOLORVALUE(White, 1.0)
            mov hr,m_pRT.CreateSolidColorBrush(&color, NULL, &m_pSolidColorBrush)
        .endif

        .if (SUCCEEDED(hr))
            mov hr,CreateGeometryRealizationFactory(m_pRT, sc_maxRealizationDimension, &pRealizationFactory)
        .endif
        .if (SUCCEEDED(hr))
            mov hr,pRealizationFactory.CreateGeometryRealization(&m_pRealization)
        .endif
        .if (SUCCEEDED(hr))
            mov m_updateRealization,TRUE
        .endif
        SafeRelease(pRealizationFactory)
    .endif
    .return hr
    endp

;
; Discard device-specific resources which need to be recreated
; when a Direct3D device is lost.
;

DemoApp::DiscardDeviceResources proc

    SafeRelease(m_pRT)
    SafeRelease(m_pSolidColorBrush)
    SafeRelease(m_pRealization)
    ret
    endp


DemoApp::DiscardGeometryData proc

    mov m_updateRealization,TRUE
    SafeRelease(m_pGeometry)
    ret
    endp


DemoApp::RunMessageLoop proc

  local msg:MSG

    .while GetMessage(&msg, NULL, 0, 0)

        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    ret
    endp


DemoApp::CreateGeometries proc

    .new hr:HRESULT = S_OK

    .if ( m_pGeometry == NULL )

       .new squareWidth:float
       .new pFactory:ptr ID2D1Factory
       .new pRealization:ptr IGeometryRealization = NULL
       .new pGeometry:ptr ID2D1TransformedGeometry = NULL
       .new pPathGeometry:ptr ID2D1PathGeometry = NULL
       .new pSink:ptr ID2D1GeometrySink = NULL

        movss       xmm0,0.9 * sc_boardWidth
        cvtsi2ss    xmm1,m_numSquares
        divss       xmm0,xmm1
        movss       squareWidth,xmm0
        mov         pFactory,m_pD2DFactory

        ; Create the path geometry.

        mov hr,pFactory.CreatePathGeometry(&pPathGeometry)

        .if (SUCCEEDED(hr))

            ; Write to the path geometry using the geometry sink to
            ; create an hour glass shape.

            mov hr,pPathGeometry.Open(&pSink)
        .endif

        .if (SUCCEEDED(hr))

            pSink.SetFillMode(D2D1_FILL_MODE_ALTERNATE)
            pSink.BeginFigure(0, D2D1_FIGURE_BEGIN_FILLED)

            mov edx,1.0
            pSink.AddLine(rdx)

           .new b:D2D1_BEZIER_SEGMENT = {
                { 0.75, 0.25 },
                { 0.75, 0.75 },
                { 1.0, 1.0 } }

            pSink.AddBezier(&b)

            mov edx,1.0
            shl rdx,32
            pSink.AddLine(rdx)

            mov b.point1.x,0.25
            mov b.point1.y,0.75
            mov b.point2.x,0.25
            mov b.point2.y,0.25
            mov b.point3.x,0.0
            mov b.point3.y,0.0
            pSink.AddBezier(&b)

            pSink.EndFigure(D2D1_FIGURE_END_CLOSED)

            mov hr,pSink.Close()
        .endif

        .if (SUCCEEDED(hr))

           .new scale:Matrix3x2F
           .new translation:Matrix3x2F

            scale.Scale(squareWidth, squareWidth)

            movss xmm0,squareWidth
            movss xmm1,-0.0
            xorps xmm0,xmm1
            divss xmm0,2.0

            translation.Translation(xmm0, xmm0)
            translation.SetProduct(&scale, &translation)
            mov hr,pFactory.CreateTransformedGeometry(pPathGeometry, &translation, &pGeometry)
        .endif

        .if (SUCCEEDED(hr))

            ; Transfer the reference.
            mov m_pGeometry,pGeometry
            mov pGeometry,NULL
        .endif

        SafeRelease(pRealization)
        SafeRelease(pGeometry)
        SafeRelease(pPathGeometry)
        SafeRelease(pSink)
    .endif
    .return hr
    endp


DemoApp::RenderMainContent proc uses rsi rdi time:float

  local hr                  : HRESULT
  local rtSize              : D2D1_SIZE_F
  local squareWidth         : float
  local currentTransform    : Matrix3x2F
  local worldTransform      : Matrix3x2F
  local m                   : Matrix3x2F
  local point               : D2D1_POINT_2F
  local color               : D3DCOLORVALUE
  local pRT                 : ptr ID2D1HwndRenderTarget
  local pSB                 : ptr ID2D1SolidColorBrush
  local pRZ                 : ptr IGeometryRealization

    .data
     dwTimeStart dd 0
     dwTimeLast  dd 0
    .code

    mov         hr,S_OK
    mov         pRT,m_pRT
    movss       xmm0,sc_boardWidth
    cvtsi2ss    xmm1,m_numSquares
    divss       xmm0,xmm1
    movss       squareWidth,xmm0

    color.Init(Black, 1.0)
    pRT.GetSize(&rtSize)
    pRT.SetAntialiasMode(m_antialiasMode)
    pRT.Clear(&color)
    pRT.GetTransform(&currentTransform)

    cvtsi2ss    xmm2,m_numSquares
    mulss       xmm2,squareWidth
    movss       xmm0,rtSize.width
    subss       xmm0,xmm2
    mulss       xmm0,0.5
    movss       xmm1,rtSize.height
    subss       xmm1,xmm2
    mulss       xmm1,0.5

    m.Translation(xmm0, xmm1)
    worldTransform.SetProduct(&m, &currentTransform)

    .for ( esi = 0 : hr == S_OK && esi < m_numSquares : ++esi )

        .for ( edi = 0 : hr == S_OK && edi < m_numSquares : ++edi )

           .new x           : float
           .new y           : float
           .new length      : float
           .new intensity   : float

            cvtsi2ss    xmm1,m_numSquares
            mulss       xmm1,0.5
            cvtsi2ss    xmm0,esi
            addss       xmm0,0.5
            subss       xmm0,xmm1
            movss       x,xmm0
            cvtsi2ss    xmm0,edi
            addss       xmm0,0.5
            subss       xmm0,xmm1
            movss       y,xmm0

            cvtsi2ss    xmm0,m_numSquares
            mulss       xmm0,1.4142135623730950488016887242097
            movss       length,xmm0

            ;
            ; The intensity variable determines the color and speed of rotation of the
            ; realization instance. We choose a function that is rotationaly
            ; symmetric about the center of the grid, which produces a nice
            ; effect.
            ;

            movss       xmm0,x
            mulss       xmm0,xmm0
            movss       xmm1,y
            mulss       xmm1,xmm1
            addss       xmm0,xmm1
            sqrtss      xmm0,xmm0
            mulss       xmm0,10.0
            divss       xmm0,length
            movss       xmm1,0.2
            mulss       xmm1,time
            addss       xmm0,xmm1
            sinf(xmm0)
            addss       xmm0,1.0
            mulss       xmm0,0.5
            movss       intensity,xmm0

           .new rotateTransform:Matrix3x2F

            mulss       xmm0,sc_rotationSpeed
            mulss       xmm0,time
            mulss       xmm0,360.0
            mulss       xmm0,M_PI / 180.0

            rotateTransform.Rotation(xmm0)

           .new newWorldTransform:Matrix3x2F

            cvtsi2ss    xmm0,esi
            addss       xmm0,0.5
            mulss       xmm0,squareWidth
            cvtsi2ss    xmm1,edi
            addss       xmm1,0.5
            mulss       xmm1,squareWidth

            m.Translation(xmm0, xmm1)
            m.SetProduct(&rotateTransform, &m)
            newWorldTransform.SetProduct(&m, &worldTransform)

            mov pRZ,m_pRealization

            .if m_updateRealization

                ;
                ; Note: It would actually be a little simpler to generate our
                ; realizations prior to entering RenderMainContent. We instead
                ; generate the realizations based on the top-left primitive in
                ; the grid, so we can illustrate the fact that realizations
                ; appear identical to their unrealized counter-parts when the
                ; exact same world transform is supplied. Only the top left
                ; realization will look identical, though, as shifting or
                ; rotating an AA realization can introduce fuzziness.
                ;
                ; Realizations are regenerated every frame, so to
                ; demonstrate that the realization geometry produces identical
                ; results, you actually need to pause (<space>), which forces
                ; a regeneration.
                ;

                mov hr,pRZ.Update(
                    m_pGeometry,
                    REALIZATION_CREATION_OPTIONS_ANTI_ALIASED or \
                    REALIZATION_CREATION_OPTIONS_ALIASED or \
                    REALIZATION_CREATION_OPTIONS_FILLED or \
                    REALIZATION_CREATION_OPTIONS_STROKED or \
                    REALIZATION_CREATION_OPTIONS_UNREALIZED,
                    &newWorldTransform,
                    sc_strokeWidth,
                    NULL ;;pIStrokeStyle
                    )

                .if (SUCCEEDED(hr))

                    mov m_updateRealization,FALSE
                .endif
            .endif

            .if (SUCCEEDED(hr))

                pRT.SetTransform(&newWorldTransform)

                mov     color.r,0.0
                mov     color.g,intensity
                mov     color.a,1.0
                movss   xmm0,1.0
                subss   xmm0,intensity
                movss   color.b,xmm0
                mov     pSB,m_pSolidColorBrush

                pSB.SetColor(&color)

                mov     r9d,REALIZATION_RENDER_MODE_DEFAULT
                mov     eax,REALIZATION_RENDER_MODE_FORCE_UNREALIZED
                cmp     m_useRealizations,0
                cmove   r9d,eax

                mov hr,pRZ.Fill(pRT, pSB, r9d)

                .if SUCCEEDED(hr) && m_drawStroke

                    color.Init(White, 1.0)
                    pSB.SetColor(&color)

                    mov     r9d,REALIZATION_RENDER_MODE_DEFAULT
                    mov     eax,REALIZATION_RENDER_MODE_FORCE_UNREALIZED
                    cmp     m_useRealizations,NULL
                    cmove   r9d,eax

                    mov hr,pRZ.Draw(pRT, pSB, r9d)
                .endif
            .endif
        .endf
    .endf
    .return hr
    endp

;
;  Called whenever the application needs to display the client
;  window. This method draws the main content (a 2D array of
;  spinning geometries) and some perf statistics.
;
;  Note that this function will not render anything if the window
;  is occluded (e.g. when the screen is locked).
;  Also, this function will automatically discard device-specific
;  resources if the D3D device disappears during function
;  invocation, and will recreate the resources the next time it's
;  invoked.
;

DemoApp::OnRender proc

   .new hr:HRESULT = S_OK
   .new time:LARGE_INTEGER
   .new frequency:LARGE_INTEGER
   .new floatTime:float

    QueryPerformanceCounter(&time)
    QueryPerformanceFrequency(&frequency)

    mov hr,CreateDeviceResources()

    .if (SUCCEEDED(hr))

        cmp         m_paused,0
        mov         rax,m_pausedTime
        cmove       rax,time.QuadPart
        add         rax,m_timeDelta
        cvtsi2sd    xmm0,rax
        cvtsi2sd    xmm1,frequency.QuadPart
        divsd       xmm0,xmm1
        cvtsd2ss    xmm0,xmm0
        movss       floatTime,xmm0

        m_times.AddT(time.QuadPart)

        movss   xmm0,m_currentZoomFactor
        comiss  xmm0,m_targetZoomFactor

        .ifb

            mulss   xmm0,sc_zoomSubStep
            movss   m_currentZoomFactor,xmm0
            comiss  xmm0,m_targetZoomFactor

            .ifa
                mov m_currentZoomFactor,m_targetZoomFactor
                .if ( m_autoGeometryRegen )
                    mov m_updateRealization,TRUE
                .endif
            .endif

        .elseif !ZERO?

            divss   xmm0,sc_zoomSubStep
            movss   m_currentZoomFactor,xmm0
            comiss  xmm0,m_targetZoomFactor

            .ifb
                mov m_currentZoomFactor,m_targetZoomFactor
                .if ( m_autoGeometryRegen )
                    mov m_updateRealization,TRUE
                .endif
            .endif
        .endif

       .new m:Matrix3x2F
        m_pRT.SetTransform(
            m.Scale(m_currentZoomFactor, m_currentZoomFactor, m_mousePos.x, m_mousePos.y)
            )

        mov hr,CreateGeometries()

        .if SUCCEEDED(hr)

            .if !( m_pRT.CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED )

                m_pRT.BeginDraw()
                mov hr,RenderMainContent(floatTime)
                .if (SUCCEEDED(hr))
                    mov hr,RenderTextInfo()
                    .if (SUCCEEDED(hr))
                        mov hr,m_pRT.EndDraw(NULL, NULL)
                        .if (SUCCEEDED(hr))
                            .if (hr == D2DERR_RECREATE_TARGET)
                                DiscardDeviceResources()
                            .endif
                        .endif
                    .endif
                .endif
            .endif
        .endif
    .endif
    .return hr

DemoApp::OnRender endp

;
;  Draw the stats text (AA type, fps, etc...).
;

DemoApp::RenderTextInfo proc uses rdi

   .new hr:HRESULT = S_OK
   .new textBuffer[400]:WCHAR
   .new frequency:LARGE_INTEGER
   .new fps:float = 0.0
   .new primsPerSecond:float = 0.0
   .new numPrimitives:UINT
   .new pRB:ptr RingBuffer

    QueryPerformanceFrequency(&frequency)

    mov eax,m_numSquares
    mul m_numSquares
    .if m_drawStroke
        shl eax,1
    .endif
    mov numPrimitives,eax
    mov pRB,m_times

    .if ( pRB.GetCount() > 0 )

        dec         eax
        mul         frequency.QuadPart
        cvtsi2ss    xmm0,eax
        mov         edi,pRB.GetLast()
        sub         edi,pRB.GetFirst()
        cvtsi2ss    xmm1,edi
        divss       xmm0,xmm1
        movss       fps,xmm0
        cvtsi2ss    xmm1,numPrimitives
        mulss       xmm0,xmm1
        movss       primsPerSecond,xmm0
    .endif

    cmp         m_antialiasMode,D2D1_ANTIALIAS_MODE_ALIASED
    lea         rax,@CStr("Aliased")
    lea         rcx,@CStr("PerPrimitive")
    cmove       rcx,rax
    cmp         m_useRealizations,0
    lea         rdx,@CStr("Realized")
    lea         rax,@CStr("Unrealized")
    cmove       rdx,rax
    cmp         m_autoGeometryRegen,0
    lea         r8,@CStr("Auto Realization Regeneration")
    lea         rax,@CStr("No Auto Realization Regeneration")
    cmove       r8,rax
    cmp         m_drawStroke,0
    lea         rax,@CStr("")
    lea         r9,@CStr(" x 2")
    cmove       r9,rax

    movss       xmm0,fps
    cvtss2sd    xmm0,xmm0
    movq        r10,xmm0

    movss       xmm0,primsPerSecond
    cvtss2sd    xmm0,xmm0
    movq        r11,xmm0

    mov hr,swprintf(
            &textBuffer,
            "%s\n"
            "%s\n"
            "%s\n"
            "# primitives: %d x %d%s = %d\n"
            "Fps: %.2f\n"
            "Primitives / sec : %.0f\n"
            "Keys: Space Up Down A R G S",
            rcx,
            rdx,
            r8,
            m_numSquares,
            m_numSquares,
            r9,
            numPrimitives,
            r10,
            r11
            )

    .if (SUCCEEDED(hr))

       .new m:Matrix3x2F
        m_pRT.SetTransform(m.Identity())

       .new c:D3DCOLORVALUE(Black, 0.5)
        m_pSolidColorBrush.SetColor(&c)

       .new rr:D2D1_ROUNDED_RECT = {
            { 10.0, 10.0, 350.0, 210.0 },
            sc_textInfoBoxInset,
            sc_textInfoBoxInset
            }

        m_pRT.FillRoundedRectangle(&rr, m_pSolidColorBrush)

        movss xmm0,rr.rect.left
        addss xmm0,sc_textInfoBoxInset
        movss rr.rect.left,xmm0
        movss xmm0,rr.rect.top
        addss xmm0,sc_textInfoBoxInset
        movss rr.rect.top,xmm0
        movss xmm0,rr.rect.right
        subss xmm0,sc_textInfoBoxInset
        movss rr.rect.right,xmm0
        movss xmm0,rr.rect.bottom
        subss xmm0,sc_textInfoBoxInset
        movss rr.rect.bottom,xmm0

        m_pSolidColorBrush.SetColor(c.Init(White, 1.0))
        mov ecx,wcsnlen(&textBuffer, ARRAYSIZE(textBuffer))
        m_pRT.DrawText(&textBuffer, ecx, m_pTextFormat, &rr, m_pSolidColorBrush, D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL)
    .endif
    .return hr
    endp

;
;  If the application receives a WM_SIZE message, this method
;  resizes the render target appropriately.
;

DemoApp::OnResize proc width:UINT, height:UINT

    .if m_pRT

       .new size:D2D1_SIZE_U

        mov size.width,ldr(width)
        mov size.height,ldr(height)

        ; Note: This method can fail, but it's okay to ignore the
        ; error here -- it will be repeated on the next call to
        ; EndDraw.

        m_pRT.Resize(&size)
    .endif
    ret
    endp


DemoApp::OnKeyDown proc vkey:SWORD

    .switch dx
    .case 'A'
        mov eax,D2D1_ANTIALIAS_MODE_ALIASED
        .if ( m_antialiasMode == D2D1_ANTIALIAS_MODE_ALIASED )
            mov eax,D2D1_ANTIALIAS_MODE_PER_PRIMITIVE
        .endif
        mov m_antialiasMode,eax
       .endc
    .case 'R'
        xor m_useRealizations,1
       .endc
    .case 'G'
        xor m_autoGeometryRegen,1
       .endc
    .case 'S'
        xor m_drawStroke,1
       .endc
    .case VK_SPACE
       .new time:LARGE_INTEGER
        QueryPerformanceCounter(&time)
        .if !m_paused
            mov m_pausedTime,time.QuadPart
        .else
            mov rax,m_pausedTime
            sub rax,time.QuadPart
            add m_timeDelta,rax
        .endif
        xor m_paused,1
        mov m_updateRealization,TRUE
       .endc
    .case VK_UP
        mov eax,m_numSquares
        shl eax,1
        .if eax > sc_maxNumSquares
            mov eax,sc_maxNumSquares
        .endif
        mov m_numSquares,eax

        ; Regenerate the geometries.

        DiscardGeometryData()
       .endc
    .case VK_DOWN
        mov eax,m_numSquares
        shr eax,1
        .if eax < sc_minNumSquares
            mov eax,sc_minNumSquares
        .endif
        mov m_numSquares,eax

        ; Regenerate the geometries.

        DiscardGeometryData()
       .endc
    .endsw
    ret
    endp


DemoApp::OnMouseMove proc lParam:LPARAM

  local dpiX:float
  local dpiY:float

    mov dpiX,96.0
    mov dpiY,96.0

    .if m_pRT
        m_pRT.GetDpi(&dpiX, &dpiY)
    .endif

    movsx       eax,word ptr lParam
    cvtsi2ss    xmm0,eax
    mulss       xmm0,96.0
    divss       xmm0,dpiX
    movss       m_mousePos.x,xmm0

    movsx       eax,word ptr lParam[2]
    cvtsi2ss    xmm0,eax
    mulss       xmm0,96.0
    divss       xmm0,dpiY
    movss       m_mousePos.y,xmm0
    ret
    endp


DemoApp::OnWheel proc wParam:WPARAM

    shr         edx,16
    movsx       rdx,dx
    cvtsi2sd    xmm1,rdx
    divsd       xmm1,120.0
    pow(sc_zoomStep, xmm1)
    cvtsd2ss    xmm0,xmm0

    mulss       xmm0,m_targetZoomFactor
    movss       xmm1,sc_minZoom
    maxss       xmm0,xmm1
    movss       xmm1,sc_maxZoom
    minss       xmm0,xmm1
    movss       m_targetZoomFactor,xmm0
    ret
    endp


WndProc proc WINAPI hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local result:LRESULT
  local wasHandled:BOOL
  local pDemoApp:ptr DemoApp

     mov result,0

    .if edx == WM_CREATE

        SetWindowLongPtrW(rcx, GWLP_USERDATA, [r9].CREATESTRUCT.lpCreateParams)
        mov result,1

    .else

        mov pDemoApp,GetWindowLongPtrW(rcx, GWLP_USERDATA)
        mov wasHandled,FALSE

        .if rax

            .switch(message)

            .case WM_SIZE

                movzx edx,word ptr lParam
                movzx r8d,word ptr lParam[2]
                pDemoApp.OnResize(edx, r8d)

                mov result,0
                mov wasHandled,TRUE
                .endc

            .case WM_PAINT
            .case WM_DISPLAYCHANGE

               .new ps:PAINTSTRUCT
                BeginPaint(hwnd, &ps)
                pDemoApp.OnRender()
                EndPaint(hwnd, &ps)
                InvalidateRect(hwnd, NULL, FALSE)

                mov result,0
                mov wasHandled,TRUE
                .endc

            .case WM_KEYDOWN
                movzx edx,word ptr wParam
                pDemoApp.OnKeyDown(dx)

                mov result,0
                mov wasHandled,TRUE
                .endc

            .case WM_MOUSEMOVE
                pDemoApp.OnMouseMove(lParam)

                mov result,0
                mov wasHandled,TRUE
                .endc

            .case WM_MOUSEWHEEL
                pDemoApp.OnWheel(wParam)

                mov result,0
                mov wasHandled,TRUE
                .endc

            .case WM_DESTROY
                PostQuitMessage(0)

                mov result,1
                mov wasHandled,TRUE
                .endc
            .case WM_CHAR
                .gotosw(WM_DESTROY) .if wParam == VK_ESCAPE
                .endc
            .endsw
        .endif

        .if (!wasHandled)

            mov result,DefWindowProc(hwnd, message, wParam, lParam)
        .endif
    .endif

    .return result

WndProc endp


wWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, nCmdShow:SINT

  local tmring:RingBuffer

    ; Ignore the return value because we want to continue running even in the
    ; unlikely event that HeapSetInformation fails.

    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0)

    .if (SUCCEEDED(CoInitialize(NULL)))

        .new app:ptr DemoApp(&tmring)

        .if (SUCCEEDED(app.Initialize()))

            app.RunMessageLoop()
        .endif
        app.Release()
        CoUninitialize()
    .endif
    .return 0
    endp

    end _tstart
