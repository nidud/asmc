;
; http://ube43.wix.com/directxers/apps/blog/directx-9-tutorial-1-ein-fenster
;

;; Every windows application needs to include this
include windows.inc
include emmintrin.inc
include tchar.inc

;; Every Direct3D application this
include d3d9.inc
include d3dx9.inc

.data
g_lpEffect          LPD3DXEFFECT NULL
g_lpVertexBuffer    LPDIRECT3DVERTEXBUFFER9 NULL

;; The combined transformation will end up in this matrix:
g_ShaderMatrix      D3DXMATRIX <>
g_bContinue         dd TRUE

;; Camera Position
g_v3Position        D3DXVECTOR3 <0.0,0.0,-5.0>

;; Camera LookAt point
g_v3LookAt          D3DXVECTOR3 <0.0,0.0,0.0>
Vectors             D3DXVECTOR3 <0.0,1.0,0.0>
FL1000              FLOAT 1000.0
FL2_0               FLOAT 2.0

;; Definition of the first Vertex Format
;; including position and diffuse color
D3DFVF_COLOREDVERTEX equ (D3DFVF_XYZ or D3DFVF_DIFFUSE)

COLORED_VERTEX STRUC
x           FLOAT ?     ;; Position
y           FLOAT ?
z           FLOAT ?
color       dd ?        ;; Color
COLORED_VERTEX ENDS

.code


;; Besides the main function, there must be a message processing function
MsgProc proc WINAPI hWnd:HWND, msg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch(msg)
      .case WM_DESTROY:
        PostQuitMessage( 0 )
        xor eax,eax
        mov g_bContinue,eax
        .endc
        ;; handle keypress
      .case WM_KEYDOWN
        xor eax,eax
        lea rcx,g_v3LookAt
        assume rcx:ptr D3DXVECTOR3
        .switch(wParam)
        ;; change lookAt with arrow keys
        .case VK_UP
            _mm_store_ss([rcx].y, _mm_add_ss([rcx].y, FL2_0))
            .endc
        .case VK_DOWN
            _mm_store_ss([rcx].y,_mm_sub_ss([rcx].y, FL2_0))
            .endc
        .case VK_LEFT
            _mm_store_ss([rcx].x,_mm_add_ss([rcx].x, FL2_0))
            .endc
        .case VK_RIGHT
            _mm_store_ss([rcx].x,_mm_sub_ss([rcx].x, FL2_0))
            .endc
        .endsw
        assume rcx:nothing
        .endc
      .default
        DefWindowProc( hWnd, msg, wParam, lParam )
    .endsw
    ret

MsgProc endp

;; The entry point of a windows application is the WinMain function
WinMain proc WINAPI uses rdi hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPSTR, nShowCmd:SINT

    ;; Create a window class.
    local wc:WNDCLASSEX
    local hWnd:HWND
    local pD3D:LPDIRECT3D9
    local d3dpp:D3DPRESENT_PARAMETERS
    local pd3dDevice:LPDIRECT3DDEVICE9
    local msg:MSG
    local uiBufferSize:UINT
    local pVertices:ptr COLORED_VERTEX
    local uiPasses:UINT
    ;;the matrices:
    ;;the first transforms from world to view/camera space,
    ;;the second from camera to screen space,
    ;;the third transforms from object to world space
    local ViewMatrix:D3DXMATRIX
    local PerspectiveMatrix:D3DXMATRIX
    local WorldMatrix:D3DXMATRIX
    local temp:REAL4

    xor eax,eax
    mov pd3dDevice,rax
    lea rdi,wc
    mov ecx,sizeof(WNDCLASSEX)
    rep stosb
    mov wc.cbSize,sizeof(WNDCLASSEX)
    mov wc.style,CS_CLASSDC
    lea rax,MsgProc
    mov wc.lpfnWndProc,rax
    lea rax,@CStr("Direct3D Window")
    mov wc.lpszClassName,rax
    mov wc.hInstance,GetModuleHandle(NULL)

    ;;Register the window class.
    RegisterClassEx( &wc );

    ;; Create the application's window.
    mov rcx,GetDesktopWindow()
    mov hWnd,CreateWindowEx(0, "Direct3D Window", "DirectXers - D3D9 Tutorial 3",
        WS_OVERLAPPEDWINDOW, 100, 100, 400, 400, rcx, NULL, wc.hInstance, NULL )

    ShowWindow( hWnd, SW_SHOW )

    .repeat

        ;; Create the Direct3D Object

        .if !Direct3DCreate9( D3D_SDK_VERSION )

            mov eax,E_FAIL
            .break
        .endif
        mov pD3D,rax

        ;; Setup the device presentation parameters

        ZeroMemory( &d3dpp, sizeof(d3dpp) )
        mov d3dpp.Windowed,TRUE
        mov d3dpp.SwapEffect,D3DSWAPEFFECT_DISCARD
        mov d3dpp.BackBufferFormat,D3DFMT_UNKNOWN

        ;; The final step is to use the IDirect3D9::CreateDevice method to create the Direct3D device, as illustrated in the
        ;; following code example.

        .ifd pD3D.CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice )

            MessageBox(hWnd, "No HAL HARDWARE_VERTEXPROCESSING! Sample will exit!", NULL, 0)
            pD3D.Release()
            mov eax,E_FAIL
            .break
        .endif

        ;; set the vertex buffer size 4 vertices * vertex structure size
        mov uiBufferSize,4*sizeof(COLORED_VERTEX)

        ;; create the buffer
        .ifd pd3dDevice.CreateVertexBuffer( uiBufferSize,
            D3DUSAGE_WRITEONLY, D3DFVF_COLOREDVERTEX, D3DPOOL_DEFAULT, &g_lpVertexBuffer, NULL )

            mov eax,E_FAIL
            .break
        .endif

        ;; lock the buffer for writing
        .ifd g_lpVertexBuffer._Lock( 0, uiBufferSize, &pVertices, 0 )

            mov eax,E_FAIL
            .break
        .endif

        ;; write the vertices. Here a simple rectangle
        mov rcx,pVertices
        assume rcx: ptr COLORED_VERTEX
        mov [rcx].x,-1.0    ;; left
        mov [rcx].y,-1.0    ;; bottom
        mov [rcx].z,0.0
        mov [rcx].color,0xffff0000  ;; red
        add rcx,COLORED_VERTEX
        mov [rcx].x,-1.0    ;; left
        mov [rcx].y,1.0     ;; top
        mov [rcx].z,0.0
        mov [rcx].color,0xff0000ff  ;; blue
        add rcx,COLORED_VERTEX
        mov [rcx].x,1.0     ;; right
        mov [rcx].y,-1.0    ;; bottom
        mov [rcx].z,0.0
        mov [rcx].color,0xff00ff00  ;; green
        add rcx,COLORED_VERTEX
        mov [rcx].x,1.0     ;; right
        mov [rcx].y,1.0     ;; top
        mov [rcx].z,0.0
        mov [rcx].color,0xffffffff  ;; white
        assume rcx: nothing

        ;; unlock the buffer
        g_lpVertexBuffer.Unlock()

        ;; set the Vertex Format
        pd3dDevice.SetFVF( D3DFVF_COLOREDVERTEX )

        ;; transfer the buffer to the gpu
        pd3dDevice.SetStreamSource( 0, g_lpVertexBuffer, 0, sizeof(COLORED_VERTEX) )

        ;; create an effect
        .ifd D3DXCreateEffectFromFile( pd3dDevice, "Effect.fx", NULL,
            NULL, D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY, NULL, &g_lpEffect, NULL )
            mov eax,E_FAIL
            .break
        .endif

        ;;we initialize them with identity
        D3DXMatrixIdentity(g_ShaderMatrix)
        D3DXMatrixIdentity(g_ShaderMatrix)
        D3DXMatrixIdentity(WorldMatrix)
        D3DXMatrixIdentity(ViewMatrix)
        D3DXMatrixIdentity(PerspectiveMatrix)

        ;;calculating a perspective projection matrix
        ;;parameters besides the output matrix are:
        ;;the fovY, the aspect ration, the near and far z values(for clipping)
        D3DXMatrixPerspectiveFovLH(&PerspectiveMatrix, 0.785, 1.0, 0.01, 100.0)

        .while ( g_bContinue )

            ;;Do a little position animation here for the objects world matrix

            GetTickCount()
            _mm_cvtsi32_ss(xmm0, eax)
            _mm_cvtsi32_si128(xmm1, 1000.0)
            _mm_div_ss(xmm0, xmm1)
            _mm_store_ss(temp, xmm0)
            sinf(temp)
            _mm_store_ss(temp, xmm0)
            D3DXMatrixTranslation(&WorldMatrix, temp, 0.0, 0.0)

            ;;Calculate a view matrix with position and look at vector
            D3DXMatrixLookAtLH(&ViewMatrix, &g_v3Position, &g_v3LookAt, &Vectors)

            ;;Concatenating the matrices by multiplication.
            lea rcx,PerspectiveMatrix
            lea rdx,WorldMatrix
            lea r8,ViewMatrix
            lea r9,g_ShaderMatrix
            .for ( eax = 0: eax < 8: eax++ )
                movss xmm0,[r8+rax*4]
                movss xmm1,[rcx+rax*4]
                movss xmm2,[rdx+rax*4]
                mulss xmm0,xmm1
                mulss xmm0,xmm2
                movss [r9+rax*4],xmm0
            .endf

            ;;handover the matrix to the effect.
            g_lpEffect.SetMatrix( "ShaderMatrix", &g_ShaderMatrix )

            ;;Clear render region with blue
            pd3dDevice.Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,255), 1.0, 0 )

            ;;before rendering something, you have to call this
            pd3dDevice.BeginScene()

            ;; rendering of scene objects happens her
            mov uiPasses,0
            g_lpEffect.Begin( &uiPasses, 0 )

            .for ( edi = 0: edi < uiPasses: edi++ )

                ;; render an effect pass
                g_lpEffect.BeginPass( edi )
                ;; render the rectangle
                pd3dDevice.DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 )
                g_lpEffect.EndPass()
            .endf

            g_lpEffect._End()

            ;; now end the scene
            pd3dDevice.EndScene()

            ;; update screen = swap front and backbuffer
            pd3dDevice.Present( NULL, NULL, NULL, NULL )

            ;; A window has to handle its messages.
            TranslateMessage( &msg );
            DispatchMessage( &msg );
            PeekMessage(&msg, 0, 0, 0, PM_REMOVE)
        .endw

        ;; Do not forget to clean up here

        pd3dDevice.Release()
        pD3D.Release()
        g_lpEffect.Release()
        g_lpVertexBuffer.Release()

        xor eax,eax
    .until 1
    ret

WinMain endp

    end _tstart
