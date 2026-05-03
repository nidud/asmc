
include resource.inc

; DPI Helper Class - functions to manage the state of DPI awareness, and scale
; values used for window size and rendering.
;
; Scale, GetScale, SetScale
; GetAwareness, SetAwareness
; SetDPIChanged, GetDPIChanged

; Constants for UI size

define MAX_LOADSTRING     100
define PADDING            10
define WINDOW_HEIGHT      400 ; Default size of window for a standard display (96 DPI, 100% scaling)
define WINDOW_WIDTH       600
define BUTTON_HEIGHT      (WINDOW_HEIGHT / 8)
define BUTTON_WIDTH       (WINDOW_WIDTH  / 5)
define BUTTON_FONT_HEIGHT (BUTTON_HEIGHT / 2)

; Forward declarations

MyRegisterClass  proto :HINSTANCE
InitInstance     proto :HINSTANCE, :int_t
CreateScaledFont proto :int_t
CreateFonts      proto :HWND
WndProc          proto :HWND, :UINT, :WPARAM, :LPARAM

; Rectangle helper functions

RectHeight proto Rect:abs {
    mov eax,Rect.bottom
    sub eax,Rect.top
    }

RectWidth proto Rect:abs {
    mov eax,Rect.right
    sub eax,Rect.left
    }

.template CDPI

    m_nScaleFactor UINT ?
    m_nScaleFactorSDA UINT ?
    m_Awareness PROCESS_DPI_AWARENESS ?

    .static CDPI {
        mov m_nScaleFactor,0
        mov m_nScaleFactorSDA,0
        mov m_Awareness,PROCESS_DPI_UNAWARE
        }

    .static Scale x:int_t {

        ; DPI Unaware:  Return the input value with no scaling.
        ; These apps are always virtualized to 96 DPI and scaled by the system
        ; for the DPI of the monitor where shown.

        .if (this.m_Awareness == PROCESS_DPI_UNAWARE)

            mov eax,x

        .elseif (this.m_Awareness == PROCESS_SYSTEM_DPI_AWARE)

            ; System DPI Aware:  Return the input value scaled by the factor
            ; determined by the system DPI when the app was launched. These apps
            ; render themselves according to the DPI of the display where they
            ; are launched, and they expect that scaling to remain constant for
            ; all displays on the system. These apps are scaled up or down when
            ; moved to a display with a different DPI from the system DPI.


            MulDiv(x, this.m_nScaleFactorSDA, 100)

        .else

            ; Per-Monitor DPI Aware:  Return the input value scaled by the factor
            ; for the display which contains most of the window. These apps render
            ; themselves for any DPI, and re-render when the DPI changes (as
            ; indicated by the WM_DPICHANGED window message).

            MulDiv(x, this.m_nScaleFactor, 100)
        .endif
        }

    .static GetScale {
        .if (this.m_Awareness == PROCESS_DPI_UNAWARE)
            mov eax,100
        .elseif (this.m_Awareness == PROCESS_SYSTEM_DPI_AWARE)
            mov eax,this.m_nScaleFactorSDA
        .else
            mov eax,this.m_nScaleFactor
        .endif
        }

    .static SetScale iDPI:UINT {

        mov this.m_nScaleFactor,MulDiv(iDPI, 100, 96)

        .if (this.m_nScaleFactorSDA == 0)

            ; Save the first scale factor, which is all that SDA apps know about

            mov this.m_nScaleFactorSDA,this.m_nScaleFactor
        .endif
        }

    .static GetAwareness {

       .new hProcess:HANDLE = OpenProcess(PROCESS_ALL_ACCESS, false, GetCurrentProcessId())
        GetProcessDpiAwareness(hProcess, addr this.m_Awareness)
        mov eax,this.m_Awareness
        }

    .static SetAwareness :PROCESS_DPI_AWARENESS {

        .new awareness:PROCESS_DPI_AWARENESS = _1

        .if ( SetProcessDpiAwareness(_1) == S_OK )

            mov this.m_Awareness,awareness
        .else
            MessageBox(NULL, "SetProcessDpiAwareness Error", "Error", MB_OK)
        .endif
        }


    ; Scale rectangle from raw pixels to relative pixels.

    .static ScaleRect pRect:ptr RECT {

        .new pRect:ptr RECT = rsi

        mov [rsi].RECT.left,   this.Scale([rsi].RECT.left)
        mov [rsi].RECT.right,  this.Scale([rsi].RECT.right)
        mov [rsi].RECT.top,    this.Scale([rsi].RECT.top)
        mov [rsi].RECT.bottom, this.Scale([rsi].RECT.bottom)
        mov rsi,pRect
        }

    ; Scale Point from raw pixels to relative pixels.

    .static ScalePoint :ptr POINT {
       .new pPoint:ptr POINT = rsi
        mov rsi,_1
        mov [rsi].POINT.x, this.Scale([rsi].POINT.x)
        mov [rsi].POINT.y, this.Scale([rsi].POINT.y)
        mov rsi,pPoint
        }

    .ends
