ifndef _D2D1_HELPER_H_
_D2D1_HELPER_H_ equ <>

ifndef _D2D1_H_
include d2d1.inc
endif

ifdef _WIN64


    D2D1        typedef ptr
    Matrix3x2F  typedef ptr

.template MATRIX3X2F

    _11 real4 ?
    _12 real4 ?
    _21 real4 ?
    _22 real4 ?
    _31 real4 ?
    _32 real4 ?

    .operator Identity {
        xor eax,eax
        mov [rcx].MATRIX3X2F._11,1.0
        mov [rcx].MATRIX3X2F._12,eax
        mov [rcx].MATRIX3X2F._21,eax
        mov [rcx].MATRIX3X2F._22,1.0
        mov [rcx].MATRIX3X2F._31,eax
        mov [rcx].MATRIX3X2F._32,eax
        mov rax,rcx
        }

    .operator Rotation :abs, :abs=<0> {
        D2D1MakeRotateMatrix(_1, _2, rcx)
        }

    .operator Translation :real4, :real4 {
        mov   [rcx].MATRIX3X2F._11,1.0
        mov   [rcx].MATRIX3X2F._12,0.0
        mov   [rcx].MATRIX3X2F._21,0.0
        mov   [rcx].MATRIX3X2F._22,1.0
        movss [rcx].MATRIX3X2F._31,xmm1
        movss [rcx].MATRIX3X2F._32,xmm2
        mov   rax,rcx
        }

    .operator Scale :real4, :real4, :abs, :abs {
        movss [rcx].MATRIX3X2F._11,xmm1
        mov   [rcx].MATRIX3X2F._12,0.0
        mov   [rcx].MATRIX3X2F._21,0.0
        movss [rcx].MATRIX3X2F._22,xmm2
        ifb <_3>
           mov [rcx].MATRIX3X2F._31,0.0
           mov [rcx].MATRIX3X2F._32,0.0
        else
           movss xmm0,_3
           mulss xmm1,xmm0
           subss xmm0,xmm1
           movss [rcx].MATRIX3X2F._31,xmm0
           movss xmm0,_4
           mulss xmm2,xmm0
           subss xmm0,xmm2
           movss [rcx].MATRIX3X2F._32,xmm0
        endif
        mov rax,rcx
        }

    .operator Invert {
        xor D2D1InvertMatrix(rcx),1
        }

    .operator IsIdentity {
        xor eax,eax
        mov edx,1.0
        .if [rcx].MATRIX3X2F._11 == edx && \
            [rcx].MATRIX3X2F._12 == eax && \
            [rcx].MATRIX3X2F._21 == eax && \
            [rcx].MATRIX3X2F._22 == edx && \
            [rcx].MATRIX3X2F._31 == eax && \
            [rcx].MATRIX3X2F._32 == eax
            inc eax
        .endif
        }

    .operator SetProduct :ptr, :ptr {

        assume rdx:ptr MATRIX3X2F
        assume r8:ptr MATRIX3X2F

        movss xmm2,[rdx]._11 ; a._11 * b._11 + a._12 * b._21
        mulss xmm2,[r8]._11
        movss xmm1,[rdx]._12
        mulss xmm1,[r8]._21
        addss xmm2,xmm1

        movss xmm3,[rdx]._11 ; a._11 * b._12 + a._12 * b._22
        mulss xmm3,[r8]._12
        movss xmm1,[rdx]._12
        mulss xmm1,[r8]._22
        addss xmm3,xmm1

        movss xmm4,[rdx]._21 ; a._21 * b._11 + a._22 * b._21
        mulss xmm4,[r8]._11
        movss xmm1,[rdx]._22
        mulss xmm1,[r8]._21
        addss xmm4,xmm1

        movss xmm5,[rdx]._21 ; a._21 * b._12 + a._22 * b._22
        mulss xmm5,[r8]._12
        movss xmm1,[rdx]._22
        mulss xmm1,[r8]._22
        addss xmm5,xmm1

        movss xmm6,[rdx]._31 ; a._31 * b._11 + a._32 * b._21 + b._31
        mulss xmm6,[r8]._11
        movss xmm1,[rdx]._32
        mulss xmm1,[r8]._21
        addss xmm6,xmm1
        addss xmm6,[r8]._31

        movss xmm0,[rdx]._31 ; a._31 * b._12 + a._32 * b._22 + b._32
        mulss xmm0,[r8]._12
        movss xmm1,[rdx]._32
        mulss xmm1,[r8]._22
        addss xmm0,xmm1
        addss xmm0,[r8]._32

        movss [rcx+0x00],xmm2
        movss [rcx+0x04],xmm3
        movss [rcx+0x08],xmm4
        movss [rcx+0x0C],xmm5
        movss [rcx+0x10],xmm6
        movss [rcx+0x14],xmm0

        assume rdx:nothing
        assume r8:nothing
        }

    .ends

.template Matrix3x2F


    .operator Identity {

      local T
       .new T:D2D1_MATRIX_3X2_F

        xor eax,eax
        mov T._11,1.0
        mov T._12,eax
        mov T._21,eax
        mov T._22,1.0
        mov T._31,eax
        mov T._32,eax
        lea rax,T
        }


    .operator Translation :real4, :real4 {

      local T
       .new T:D2D1_MATRIX_3X2_F

        mov   T._11,1.0
        mov   T._12,0.0
        mov   T._21,0.0
        mov   T._22,1.0
        movss T._31,xmm0
        movss T._32,xmm1
        lea   rax,T
        }


    .operator Scale :real4, :real4, :abs, :abs {

      local T
       .new T:D2D1_MATRIX_3X2_F

        movss T._11,xmm0
        mov   T._12,0.0
        mov   T._21,0.0
        movss T._22,xmm1
        ifb <_3>
           mov T._31,0.0
           mov T._32,0.0
        else
           movss xmm1,_3
           mulss xmm1,T._11
           subss xmm0,xmm1
           movss T._31,xmm0
           movss xmm1,_4
           mulss xmm1,T._22
           subss xmm0,xmm1
           movss T._32,xmm0
        endif
        lea rax,T
        }


    .operator Rotation :abs, :abs=<0> {

       local T
        .new T:D2D1_MATRIX_3X2_F

        D2D1MakeRotateMatrix(_1, _2, addr T)
        lea rax,T
        }


    .operator Skew :abs, :abs, :abs=<0> {

       local T
        .new T:D2D1_MATRIX_3X2_F

        D2D1MakeSkewMatrix(_1, _2, _3, addr T)
        lea rax,T
        }


    .operator ReinterpretBaseType :ptr D2D1_MATRIX_3X2_F {
        mov rax,rcx
        }


    .operator Determinant :ptr D2D1_MATRIX_3X2_F {
        movss xmm0,[rcx]
        mulss xmm0,[rcx+12]
        movss xmm1,[rcx+4]
        mulss xmm1,[rcx+8]
        subss xmm0,xmm1
        }


    .operator Invert :ptr D2D1_MATRIX_3X2_F {
        xor D2D1InvertMatrix(rcx),1
        }


    .operator IsIdentity :ptr D2D1_MATRIX_3X2_F {

        xor eax,eax
        mov edx,1.0
        assume rcx:ptr D2D1_MATRIX_3X2_F
        .if [rcx]._11 == edx && \
            [rcx]._12 == eax && \
            [rcx]._21 == eax && \
            [rcx]._22 == edx && \
            [rcx]._31 == eax && \
            [rcx]._32 == eax
            inc eax
        .endif
        assume rcx:nothing
        }


    .operator SetProduct :ptr, :ptr {

       local T
        .new T:D2D1_MATRIX_3X2_F

        assume rcx:ptr D2D1_MATRIX_3X2_F
        assume rdx:ptr D2D1_MATRIX_3X2_F

        movss xmm0,[rcx]._11 ; a._11 * b._11 + a._12 * b._21
        mulss xmm0,[rdx]._11
        movss xmm1,[rcx]._12
        mulss xmm1,[rdx]._21
        addss xmm0,xmm1
        movss T._11,xmm0

        movss xmm0,[rcx]._11 ; a._11 * b._12 + a._12 * b._22
        mulss xmm0,[rdx]._12
        movss xmm1,[rcx]._12
        mulss xmm1,[rdx]._22
        addss xmm0,xmm1
        movss T._12,xmm0

        movss xmm0,[rcx]._21 ; a._21 * b._11 + a._22 * b._21
        mulss xmm0,[rdx]._11
        movss xmm1,[rcx]._22
        mulss xmm1,[rdx]._21
        addss xmm0,xmm1
        movss T._21,xmm0

        movss xmm0,[rcx]._21 ; a._21 * b._12 + a._22 * b._22
        mulss xmm0,[rdx]._12
        movss xmm1,[rcx]._22
        mulss xmm1,[rdx]._22
        addss xmm0,xmm1
        movss T._22,xmm0

        movss xmm0,[rcx]._31 ; a._31 * b._11 + a._32 * b._21 + b._31
        mulss xmm0,[rdx]._11
        movss xmm1,[rcx]._32
        mulss xmm1,[rdx]._21
        addss xmm0,xmm1
        addss xmm0,[rdx]._31
        movss T._31,xmm0

        movss xmm0,[rcx]._31 ; a._31 * b._12 + a._32 * b._22 + b._32
        mulss xmm0,[rdx]._12
        movss xmm1,[rcx]._32
        mulss xmm1,[rdx]._22
        addss xmm0,xmm1
        addss xmm0,[rdx]._32
        movss T._32,xmm0

        assume rcx:nothing
        assume rdx:nothing

        lea rax,T
        }

    .ends


.template D2D1


    .operator FloatMax {
        ifdef FLT_MAX
            movss xmm0,FLT_MAX
        else
            movss xmm0,3.402823466e+38
        endif
        }


    .operator Point2 :dword, :dword {

       local T
        .new T:Point

        mov T.x,_1
        mov T.y,_2
        lea _3,T
        }

    .operator Point2F :abs=<0.0>, :abs=<0.0> {

       local T
        .new T:D2D1_POINT_2F

        ifidn typeid(?, _1),<?r128>
            movss T.x,_1
        else
            mov T.x,_1
        endif
        ifidn typeid(?, _2),<?r128>
            movss T.y,_2
        else
            mov T.y,_2
        endif
        lea rax,T
        }

    .operator Point2U :abs=<0>, :abs=<0> {

       local T
        .new T:D2D1_POINT_2U

        mov T.x,_1
        mov T.y,_2
        lea rax,T
        }

    .operator Size :uint_t, :uint_t {

       local T
        .new T:Size

        mov T.width,ecx
        mov T.height,edx
        lea rax,T
        }

    .operator SizeF :abs=<0.0>, :abs=<0.0> {

       local T
        .new T:D2D1_SIZE_F
        ifidn typeid(?, _1),<?r128>
            movss T.width, _1
        else
            mov T.width, _1
        endif
        ifidn typeid(?, _2),<?r128>
            movss T.height,_2
        else
            mov T.height,_2
        endif
        lea rax,T
        }

    .operator SizeU :abs=<0>, :abs=<0> {

       local T
        .new T:D2D1_SIZE_U

        mov T.width, _1
        mov T.height,_2
        lea rax,T
        }

    .operator Rect :uint_t, :uint_t, :uint_t, :uint_t {

       local T
        .new T:Rect

        mov T.left,   ecx
        mov T.top,    edx
        mov T.right,  r8d
        mov T.bottom, r9d
        lea rax,T
        }

    .operator RectF :abs=<0.0>, :abs=<0.0>, :abs=<0.0>, :abs=<0.0> {

       local T
        .new T:D2D1_RECT_F

        ifidn typeid(?, _1),<?r128>
            movss T.left,_1
        else
            mov T.left,_1
        endif
        ifidn typeid(?, _2),<?r128>
            movss T.top,_2
        else
            mov T.top,_2
        endif
        ifidn typeid(?, _3),<?r128>
            movss T.right,_3
        else
            mov T.right,_3
        endif
        ifidn typeid(?, _4),<?r128>
            movss T.bottom,_4
        else
            mov T.bottom,_4
        endif
        lea rax,T
        }

    .operator RectU :abs=<0>, :abs=<0>, :abs=<0>, :abs=<0> {

       local T
        .new T:D2D1_RECT_U

        mov T.left,   _1
        mov T.top,    _2
        mov T.right,  _3
        mov T.bottom, _4
        lea rax,T
        }

    .operator InfiniteRect {

       local T
        .new T:D2D1_RECT_F

        ifdef FLT_MAX
            mov T.left,   -FLT_MAX
            mov T.top,    -FLT_MAX
            mov T.right,  FLT_MAX
            mov T.bottom, FLT_MAX
        else
            mov T.left,   -3.402823466e+38
            mov T.top,    -3.402823466e+38
            mov T.right,  3.402823466e+38
            mov T.bottom, 3.402823466e+38
        endif
        lea rax,T
        }


    .operator ArcSegment :ptr D2D1_POINT_2F, :ptr D2D1_SIZE_F, :abs, :abs, :abs {

       local T
        .new T:D2D1_ARC_SEGMENT

        mov T.point,[rcx]
        mov T.size, [rdx]
        mov T.rotationAngle,_3
        mov T.sweepDirection,_4
        mov T.arcSize,_5
        lea rax,T
        }

    .operator BezierSegment :ptr D2D1_POINT_2F, :ptr D2D1_POINT_2F, :ptr D2D1_POINT_2F {

       local T
        .new T:D2D1_BEZIER_SEGMENT

        mov T.point1,[rcx]
        mov T.point2,[rdx]
        mov T.point3,[r8]
        lea rax,T
        }


    .operator Ellipse :ptr D2D1_POINT_2F, :FLOAT, :FLOAT {

       local T
        .new T:D2D1_ELLIPSE

        mov   T.point,[rcx]
        movss T.radiusX,xmm1
        movss T.radiusY,xmm2
        lea   rax,T
        }

    .operator RoundedRect :ptr D2D1_RECT_F, :FLOAT, :FLOAT {

       local T
        .new T:D2D1_ROUNDED_RECT

        mov   T.rect,[rcx]
        movss T.radiusX,xmm1
        movss T.radiusY,xmm2
        lea   rax,T
        }

    .operator BrushProperties :abs=<1.0>, :abs {

       local T
        .new T:D2D1_BRUSH_PROPERTIES

        mov T.opacity,_1
        ifb <_2>
            xor eax,eax
            mov T.transform._11,1.0
            mov T.transform._12,eax
            mov T.transform._21,eax
            mov T.transform._22,1.0
            mov T.transform._31,eax
            mov T.transform._32,eax
        else
            mov T.transform,[rdx]
        endif
        lea rax,T
        }

    .operator GradientStop :FLOAT, :ptr D2D1_COLOR_F {

       local T
        .new T:D2D1_GRADIENT_STOP

        movss T.position,xmm0
        mov   T.color,[rdx]
        lea   rax,T
        }

    .operator QuadraticBezierSegment :ptr D2D1_POINT_2F, :ptr D2D1_POINT_2F {

       local T
        .new T:D2D1_QUADRATIC_BEZIER_SEGMENT

        mov T.point1,[rcx]
        mov T.point2,[rdx]
        lea rax,T
        }

    .operator StrokeStyleProperties :abs=<D2D1_CAP_STYLE_FLAT>,
                                    :abs=<D2D1_CAP_STYLE_FLAT>,
                                    :abs=<D2D1_CAP_STYLE_FLAT>,
                                    :abs=<D2D1_LINE_JOIN_MITER>,
                                    :abs=<10.0>,
                                    :abs=<D2D1_DASH_STYLE_SOLID>,
                                    :abs=<0.0> {

       local T
        .new T:D2D1_STROKE_STYLE_PROPERTIES

        mov T.startCap,   _1
        mov T.endCap,     _2
        mov T.dashCap,    _3
        mov T.lineJoin,   _4
        mov T.miterLimit, _5
        mov T.dashStyle,  _6
        mov T.dashOffset, _7
        lea rax,T
        }

    .operator BitmapBrushProperties :abs=<D2D1_EXTEND_MODE_CLAMP>, :abs=<D2D1_EXTEND_MODE_CLAMP>,
        :abs=<D2D1_BITMAP_INTERPOLATION_MODE_LINEAR> {

       local T
        .new T:D2D1_BITMAP_BRUSH_PROPERTIES

        mov T.extendModeX,_1
        mov T.extendModeY,_2
        mov T.interpolationMode,_3
        lea rax,T
        }

    .operator LinearGradientBrushProperties :ptr D2D1_POINT_2F, :ptr D2D1_POINT_2F {

       local T
        .new T:D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES

        mov T.startPoint, [rcx]
        mov T.endPoint,   [rdx]
        lea rax,T
        }

    .operator RadialGradientBrushProperties :ptr D2D1_POINT_2F, :ptr D2D1_POINT_2F, :FLOAT, :FLOAT {

       local T
        .new T:D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES

        mov   T.center,[rcx]
        mov   T.gradientOriginOffset,[rdx]
        movss T.radiusX,xmm2
        movss T.radiusY,xmm3
        lea   rax,T
        }


    ;;
    ;; PixelFormat
    ;;
    .operator PixelFormat :abs=<DXGI_FORMAT_UNKNOWN>, :abs=<D2D1_ALPHA_MODE_UNKNOWN> {

       local T
        .new T:D2D1_PIXEL_FORMAT

        mov T.format,_1
        mov T.alphaMode,_2
        lea rax,T
        }


    ;;
    ;; Bitmaps
    ;;
    .operator BitmapProperties :ptr D2D1_PIXEL_FORMAT, :abs=<96.0>, :abs=<96.0> {

       local T
        .new T:D2D1_BITMAP_PROPERTIES

        mov T.pixelFormat,[rcx]
        mov T.dpiX,_2
        mov T.dpiY,_3
        lea rax,T
        }


    ;;
    ;; Render Targets
    ;;
    .operator RenderTargetProperties \
            :abs=<D2D1_RENDER_TARGET_TYPE_DEFAULT>,
            :abs,
            :abs=<0.0>,
            :abs=<0.0>,
            :abs=<D2D1_RENDER_TARGET_USAGE_NONE>,
            :abs=<D2D1_FEATURE_LEVEL_DEFAULT> {

       local T
        .new T:D2D1_RENDER_TARGET_PROPERTIES

        mov T.type,     _1
        mov T.dpiX,     _3
        mov T.dpiY,     _4
        mov T.usage,    _5
        mov T.minLevel, _6
        ifb <_2>
            mov T.pixelFormat.format,DXGI_FORMAT_UNKNOWN
            mov T.pixelFormat.alphaMode,D2D1_ALPHA_MODE_UNKNOWN
        else
            ifdif <_2>,<rdx>
                mov rdx,_2
            endif
            mov T.pixelFormat,[rdx]
        endif
        lea rax,T
        }


    .operator HwndRenderTargetProperties :HWND, :D2D1_SIZE_U, :abs=<D2D1_PRESENT_OPTIONS_NONE> {

       local T
        .new T:D2D1_HWND_RENDER_TARGET_PROPERTIES

        mov T.hwnd,rcx
        mov T.pixelSize,rdx
        mov T.presentOptions,_3
        lea rax,T
        }


    .operator LayerParameters :ptr D2D1_RECT_F,
        :ptr,
        :abs=<D2D1_ANTIALIAS_MODE_PER_PRIMITIVE>,
        :D2D1_MATRIX_3X2_F,
        :abs=<1.0>,
        :ptr ID2D1Brush,
        :abs=<D2D1_LAYER_OPTIONS_NONE> {

       local T
        .new T:D2D1_LAYER_PARAMETERS ; { 0 }

        mov T.contentBounds,     [rcx]
        mov T.geometricMask,     [rdx]
        mov T.maskAntialiasMode, _3
        mov T.maskTransform,     _4
        mov T.opacity,           _5
        mov T.opacityBrush,      _6
        mov T.layerOptions,      _7
        lea rax,T
        }


    .operator DrawingStateDescription \
        :abs=<D2D1_ANTIALIAS_MODE_PER_PRIMITIVE>,
        :abs=<D2D1_TEXT_ANTIALIAS_MODE_DEFAULT>,
        :abs=<0>,
        :abs=<0>,
        :abs=<0> {

       local T
        .new T:D2D1_DRAWING_STATE_DESCRIPTION

        mov T.antialiasMode,     _1
        mov T.textAntialiasMode, _2
        mov T.tag1,              _3
        mov T.tag2,              _4
        mov T.transform,         _5
        lea rax,T
        }


    .operator IdentityMatrix {
        Matrix3x2F::Identity()
        }

    .ends

endif

;; Common color constants

.enum {

        AliceBlue            = 0xFFF0F8FF,
        AntiqueWhite         = 0xFFFAEBD7,
        Aqua                 = 0xFF00FFFF,
        Aquamarine           = 0xFF7FFFD4,
        Azure                = 0xFFF0FFFF,
        Beige                = 0xFFF5F5DC,
        Bisque               = 0xFFFFE4C4,
        Black                = 0xFF000000,
        BlanchedAlmond       = 0xFFFFEBCD,
        Blue                 = 0xFF0000FF,
        BlueViolet           = 0xFF8A2BE2,
        Brown                = 0xFFA52A2A,
        BurlyWood            = 0xFFDEB887,
        CadetBlue            = 0xFF5F9EA0,
        Chartreuse           = 0xFF7FFF00,
        Chocolate            = 0xFFD2691E,
        Coral                = 0xFFFF7F50,
        CornflowerBlue       = 0xFF6495ED,
        Cornsilk             = 0xFFFFF8DC,
        Crimson              = 0xFFDC143C,
        Cyan                 = 0xFF00FFFF,
        DarkBlue             = 0xFF00008B,
        DarkCyan             = 0xFF008B8B,
        DarkGoldenrod        = 0xFFB8860B,
        DarkGray             = 0xFFA9A9A9,
        DarkGreen            = 0xFF006400,
        DarkKhaki            = 0xFFBDB76B,
        DarkMagenta          = 0xFF8B008B,
        DarkOliveGreen       = 0xFF556B2F,
        DarkOrange           = 0xFFFF8C00,
        DarkOrchid           = 0xFF9932CC,
        DarkRed              = 0xFF8B0000,
        DarkSalmon           = 0xFFE9967A,
        DarkSeaGreen         = 0xFF8FBC8B,
        DarkSlateBlue        = 0xFF483D8B,
        DarkSlateGray        = 0xFF2F4F4F,
        DarkTurquoise        = 0xFF00CED1,
        DarkViolet           = 0xFF9400D3,
        DeepPink             = 0xFFFF1493,
        DeepSkyBlue          = 0xFF00BFFF,
        DimGray              = 0xFF696969,
        DodgerBlue           = 0xFF1E90FF,
        Firebrick            = 0xFFB22222,
        FloralWhite          = 0xFFFFFAF0,
        ForestGreen          = 0xFF228B22,
        Fuchsia              = 0xFFFF00FF,
        Gainsboro            = 0xFFDCDCDC,
        GhostWhite           = 0xFFF8F8FF,
        Gold                 = 0xFFFFD700,
        Goldenrod            = 0xFFDAA520,
        Gray                 = 0xFF808080,
        Green                = 0xFF008000,
        GreenYellow          = 0xFFADFF2F,
        Honeydew             = 0xFFF0FFF0,
        HotPink              = 0xFFFF69B4,
        IndianRed            = 0xFFCD5C5C,
        Indigo               = 0xFF4B0082,
        Ivory                = 0xFFFFFFF0,
        Khaki                = 0xFFF0E68C,
        Lavender             = 0xFFE6E6FA,
        LavenderBlush        = 0xFFFFF0F5,
        LawnGreen            = 0xFF7CFC00,
        LemonChiffon         = 0xFFFFFACD,
        LightBlue            = 0xFFADD8E6,
        LightCoral           = 0xFFF08080,
        LightCyan            = 0xFFE0FFFF,
        LightGoldenrodYellow = 0xFFFAFAD2,
        LightGray            = 0xFFD3D3D3,
        LightGreen           = 0xFF90EE90,
        LightPink            = 0xFFFFB6C1,
        LightSalmon          = 0xFFFFA07A,
        LightSeaGreen        = 0xFF20B2AA,
        LightSkyBlue         = 0xFF87CEFA,
        LightSlateGray       = 0xFF778899,
        LightSteelBlue       = 0xFFB0C4DE,
        LightYellow          = 0xFFFFFFE0,
        Lime                 = 0xFF00FF00,
        LimeGreen            = 0xFF32CD32,
        Linen                = 0xFFFAF0E6,
        Magenta              = 0xFFFF00FF,
        Maroon               = 0xFF800000,
        MediumAquamarine     = 0xFF66CDAA,
        MediumBlue           = 0xFF0000CD,
        MediumOrchid         = 0xFFBA55D3,
        MediumPurple         = 0xFF9370DB,
        MediumSeaGreen       = 0xFF3CB371,
        MediumSlateBlue      = 0xFF7B68EE,
        MediumSpringGreen    = 0xFF00FA9A,
        MediumTurquoise      = 0xFF48D1CC,
        MediumVioletRed      = 0xFFC71585,
        MidnightBlue         = 0xFF191970,
        MintCream            = 0xFFF5FFFA,
        MistyRose            = 0xFFFFE4E1,
        Moccasin             = 0xFFFFE4B5,
        NavajoWhite          = 0xFFFFDEAD,
        Navy                 = 0xFF000080,
        OldLace              = 0xFFFDF5E6,
        Olive                = 0xFF808000,
        OliveDrab            = 0xFF6B8E23,
        Orange               = 0xFFFFA500,
        OrangeRed            = 0xFFFF4500,
        Orchid               = 0xFFDA70D6,
        PaleGoldenrod        = 0xFFEEE8AA,
        PaleGreen            = 0xFF98FB98,
        PaleTurquoise        = 0xFFAFEEEE,
        PaleVioletRed        = 0xFFDB7093,
        PapayaWhip           = 0xFFFFEFD5,
        PeachPuff            = 0xFFFFDAB9,
        Peru                 = 0xFFCD853F,
        Pink                 = 0xFFFFC0CB,
        Plum                 = 0xFFDDA0DD,
        PowderBlue           = 0xFFB0E0E6,
        Purple               = 0xFF800080,
        Red                  = 0xFFFF0000,
        RosyBrown            = 0xFFBC8F8F,
        RoyalBlue            = 0xFF4169E1,
        SaddleBrown          = 0xFF8B4513,
        Salmon               = 0xFFFA8072,
        SandyBrown           = 0xFFF4A460,
        SeaGreen             = 0xFF2E8B57,
        SeaShell             = 0xFFFFF5EE,
        Sienna               = 0xFFA0522D,
        Silver               = 0xFFC0C0C0,
        SkyBlue              = 0xFF87CEEB,
        SlateBlue            = 0xFF6A5ACD,
        SlateGray            = 0xFF708090,
        Snow                 = 0xFFFFFAFA,
        SpringGreen          = 0xFF00FF7F,
        SteelBlue            = 0xFF4682B4,
        Tan                  = 0xFFD2B48C,
        Teal                 = 0xFF008080,
        Thistle              = 0xFFD8BFD8,
        Tomato               = 0xFFFF6347,
        Transparent          = 0x00FFFFFF,
        Turquoise            = 0xFF40E0D0,
        Violet               = 0xFFEE82EE,
        Wheat                = 0xFFF5DEB3,
        White                = 0xFFFFFFFF,
        WhiteSmoke           = 0xFFF5F5F5,
        Yellow               = 0xFFFFFF00,
        YellowGreen          = 0xFF9ACD32
        }

endif


