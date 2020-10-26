;;
;; Example of a Windows OpenGL program.
;; The OpenGL code is the same as that used in
;; the X Window System sample
;;
;; https://docs.microsoft.com/en-us/windows/win32/opengl/the-program-ported-to-win32
;;
include windows.inc
include GL/gl.inc
include GL/glu.inc
include tchar.inc

.pragma warning(disable: 6004) ; procedure argument or local not referenced

if defined(__PE__) or not defined(_WIN64)
GLUAPI equ <WINAPI>
else
GLUAPI equ <WINAPI frame>
endif

szAppName equ <"Win OpenGL">

BLACK_INDEX     equ 0
RED_INDEX       equ 13
GREEN_INDEX     equ 14
BLUE_INDEX      equ 16
WIDTH           equ 640
HEIGHT          equ 480

GLOBE           equ 1
CYLINDER        equ 2
CONE            equ 3

    .data

    ;; Windows globals, defines, and prototypes

    ghWnd   HWND 0
    ghDC    HDC 0
    ghRC    HGLRC 0

    SWAPBUFFERS macro
        SwapBuffers(ghDC)
        endm


    ;; OpenGL globals, defines, and prototypes

    latitude        GLdouble 0.0
    longitude       GLdouble 0.0
    latinc          GLdouble 0.0
    longinc         GLdouble 0.0
    radius          GLdouble 0.0
    stepsize        GLdouble 0.5

    .code

ifndef _WIN64

    .686
    .xmm

endif

bSetupPixelFormat proc GLUAPI hdc:HDC

  local pfd:PIXELFORMATDESCRIPTOR
  local pixelformat:int_t

    ZeroMemory(&pfd, PIXELFORMATDESCRIPTOR)

    mov pfd.nSize,      PIXELFORMATDESCRIPTOR
    mov pfd.nVersion,   1
    mov pfd.dwFlags,    PFD_DRAW_TO_WINDOW or PFD_SUPPORT_OPENGL or PFD_DOUBLEBUFFER
    mov pfd.dwLayerMask,PFD_MAIN_PLANE
    mov pfd.iPixelType, PFD_TYPE_COLORINDEX
    mov pfd.cColorBits, 8
    mov pfd.cDepthBits, 16

    mov pixelformat,ChoosePixelFormat(hdc, &pfd)
    .if ( pixelformat == 0 )

        MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK)
        .return FALSE
    .endif

    .if SetPixelFormat(hdc, pixelformat, &pfd) == FALSE

        MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK)
        .return FALSE
    .endif

    .return TRUE

bSetupPixelFormat endp

;; OpenGL code

resize proc GLUAPI width:GLsizei, height:GLsizei

  local aspect:GLdouble

    glViewport( 0, 0, width, height )

    cvtsi2sd xmm0,width
    cvtsi2sd xmm1,height
    divsd xmm0,xmm1
    movsd aspect,xmm0

    glMatrixMode( GL_PROJECTION )
    glLoadIdentity()
    gluPerspective( 45.0, aspect, 3.0, 7.0 )
    glMatrixMode( GL_MODELVIEW )
    ret

resize endp

createObjects proc GLUAPI

  local quadObj:ptr GLUquadricObj

    glNewList(GLOBE, GL_COMPILE)
        mov quadObj,gluNewQuadric ()
        gluQuadricDrawStyle (quadObj, GLU_LINE)
        gluSphere (quadObj, 1.5, 16, 16)
    glEndList()

    glNewList(CONE, GL_COMPILE)
        mov quadObj,gluNewQuadric ()
        gluQuadricDrawStyle (quadObj, GLU_FILL)
        gluQuadricNormals (quadObj, GLU_SMOOTH)
        gluCylinder(quadObj, 0.3, 0.0, 0.6, 15, 10)
    glEndList()

    glNewList(CYLINDER, GL_COMPILE)
        glPushMatrix ()
        glRotatef (90.0, 1.0, 0.0, 0.0)
        glTranslatef (0.0, 0.0, -1.0)
        mov quadObj,gluNewQuadric ()
        gluQuadricDrawStyle (quadObj, GLU_FILL)
        gluQuadricNormals (quadObj, GLU_SMOOTH)
        gluCylinder (quadObj, 0.3, 0.3, 0.6, 12, 2)
        glPopMatrix ()
    glEndList()
    ret

createObjects endp

initializeGL proc GLUAPI width:GLsizei, height:GLsizei

  local aspect:GLdouble

    glClearIndex( @CatStr(%BLACK_INDEX, <.0>) )
    glClearDepth( 1.0 )

    glEnable(GL_DEPTH_TEST)

    glMatrixMode( GL_PROJECTION )

    cvtsi2sd xmm0,width
    cvtsi2sd xmm1,height
    divsd xmm0,xmm1
    movsd aspect,xmm0

    gluPerspective( 45.0, aspect, 3.0, 7.0 )
    glMatrixMode( GL_MODELVIEW )

    movsd xmm0,3.0 + 3.0 / 2.0
    movsd radius,xmm0
    xorps xmm0,xmm0
    movsd latitude,xmm0
    movsd longitude,xmm0
    movsd xmm0,6.0
    movsd latinc,xmm0
    movsd xmm0,2.5
    movsd longinc,xmm0

    createObjects()
    ret

initializeGL endp

polarView proc GLUAPI _radius:GLdouble, _twist:GLdouble, _latitude:GLdouble,
           _longitude:GLdouble

    movsd xmm4,-0.0
    xorpd xmm0,xmm4
    xorpd xmm1,xmm4
    xorpd xmm2,xmm4
    movsd _radius,xmm0
    movsd _twist,xmm1
    movsd _latitude,xmm2

    glTranslated(0.0, 0.0, _radius)
    glRotated(_twist, 0.0, 0.0, 1.0)
    glRotated(_latitude, 1.0, 0.0, 0.0)
    glRotated(_longitude, 0.0, 0.0, 1.0)
    ret

polarView endp

drawScene proc GLUAPI

    glClear( GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT )

    glPushMatrix()

        movsd xmm2,latinc
        addsd xmm2,latitude
        movsd latitude,xmm2

        movsd xmm3,longinc
        addsd xmm3,longitude
        movsd longitude,xmm3

        polarView( radius, 0.0, latitude, longitude )

        glIndexi(RED_INDEX)
        glCallList(CONE)

        glIndexi(BLUE_INDEX)
        glCallList(GLOBE)

    glIndexi(GREEN_INDEX)
        glPushMatrix()
            glTranslatef(0.8, -0.65, 0.0)
            glRotatef(30.0, 1.0, 0.5, 1.0)
            glCallList(CYLINDER)
        glPopMatrix()

    glPopMatrix()

    SWAPBUFFERS
    ret

drawScene endp

;; main window procedure

MainWndProc proc GLUAPI hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

  local lRet:LONG
  local ps:PAINTSTRUCT
  local rect:RECT

    mov lRet,1

    .switch (uMsg)

    .case WM_CREATE
        mov ghDC,GetDC(hWnd)
        .if !bSetupPixelFormat(ghDC)
            PostQuitMessage (0)
        .endif
        mov ghRC,wglCreateContext(ghDC)
        wglMakeCurrent(ghDC, ghRC)
        GetClientRect(hWnd, &rect)
        initializeGL(rect.right, rect.bottom)
        .endc

    .case WM_PAINT
        BeginPaint(hWnd, &ps)
        EndPaint(hWnd, &ps)
        .endc

    .case WM_SIZE
        GetClientRect(hWnd, &rect)
        resize(rect.right, rect.bottom)
        .endc

    .case WM_CLOSE
        .if (ghRC)
            wglDeleteContext(ghRC)
        .endif
        .if (ghDC)
            ReleaseDC(hWnd, ghDC)
        .endif
        mov ghRC,0
        mov ghDC,0
        DestroyWindow (hWnd)
        .endc

    .case WM_DESTROY
        .if ghRC
            wglDeleteContext(ghRC)
        .endif
        .if ghDC
            ReleaseDC(hWnd, ghDC)
        .endif
        PostQuitMessage (0)
        .endc

    .case WM_CHAR
        .gotosw(WM_DESTROY) .if wParam == VK_ESCAPE
        .endc

    .case WM_KEYDOWN
        movsd xmm0,longinc
        movsd xmm1,latinc
        .switch (wParam)
        .case VK_LEFT
            addsd xmm0,stepsize
            .endc
        .case VK_RIGHT
            subsd xmm0,stepsize
            .endc
        .case VK_UP
            addsd xmm1,stepsize
            .endc
        .case VK_DOWN
            subsd xmm1,stepsize
            .endc
        .endsw
        movsd longinc,xmm0
        movsd latinc,xmm1
        .endc

    .default
        mov lRet,DefWindowProc(hWnd, uMsg, wParam, lParam)
        .endc
    .endsw
    .return lRet

MainWndProc endp

_tWinMain proc GLUAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nCmdShow:SINT

  local msg:MSG
  local wndclass:WNDCLASSEX

    ;; Register the frame class

    ZeroMemory(&wndclass, WNDCLASSEX)

    mov wndclass.cbSize,        WNDCLASSEX
    mov wndclass.lpfnWndProc,   &MainWndProc
    mov wndclass.hInstance,     hInstance
    mov wndclass.hCursor,       LoadCursor (NULL,IDC_ARROW)
    mov wndclass.lpszClassName, &@CStr(szAppName)

    .return FALSE .if !RegisterClassEx (&wndclass)

    ;; Create the frame

    mov ghWnd,CreateWindowEx(0,
            szAppName,
            "Generic OpenGL Sample",
            WS_OVERLAPPEDWINDOW or WS_CLIPSIBLINGS or WS_CLIPCHILDREN,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            WIDTH,
            HEIGHT,
            NULL,
            NULL,
            hInstance,
            NULL)

    ;; make sure window was created

    .return FALSE .if (!ghWnd)

    ;; show and update main window

    ShowWindow(ghWnd, nCmdShow)
    UpdateWindow(ghWnd)

    ;; animation loop

    .while 1

        ;;  Process all pending messages

        .while PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE

            .if GetMessage(&msg, NULL, 0, 0)

                TranslateMessage(&msg)
                DispatchMessage(&msg)
            .else
                .return TRUE
            .endif
        .endw
        drawScene()
    .endw
    ret

_tWinMain endp

    end _tstart
