ifndef _GLAUX_H
define _GLAUX_H

include windows.inc
include gl/gl.inc
include gl/glu.inc

;externdef		 auxRGBMap[20][3]:float

AUX_RGB			equ 0
AUX_RGBA		equ AUX_RGB
AUX_INDEX		equ 1
AUX_SINGLE		equ 0
AUX_DOUBLE		equ 2
AUX_DIRECT		equ 0
AUX_INDIRECT		equ 4

AUX_ACCUM		equ 8
AUX_ALPHA		equ 16
AUX_DEPTH24		equ 32
AUX_STENCIL		equ 64
AUX_AUX			equ 128
AUX_DEPTH16		equ 256
AUX_FIXED_332_PAL	equ 512
AUX_DEPTH		equ AUX_DEPTH16

AUX_WIND_IS_RGB macro x
	exitm<(((x) AND AUX_INDEX) EQ 0)>
	endm
AUX_WIND_IS_INDEX macro x
	exitm<(((x) AND AUX_INDEX) NOT =0)>
	endm
AUX_WIND_IS_SINGLE macro x
	exitm<(((x) AND AUX_DOUBLE) EQ 0)>
	endm
AUX_WIND_IS_DOUBLE macro x
	exitm<(((x) AND AUX_DOUBLE) NOT =0)>
	endm
AUX_WIND_IS_INDIRECT macro x
	exitm<(((x) AND AUX_INDIRECT) NOT =0)>
	endm
AUX_WIND_IS_DIRECT macro x
	exitm<(((x) AND AUX_INDIRECT) EQ 0)>
	endm
AUX_WIND_HAS_ACCUM macro x
	exitm<(((x) AND AUX_ACCUM) NOT =0)>
	endm
AUX_WIND_HAS_ALPHA macro x
	exitm<(((x) AND AUX_ALPHA) NOT =0)>
	endm
AUX_WIND_HAS_DEPTH macro x
	exitm<(((x) AND (AUX_DEPTH24 OR AUX_DEPTH16)) NOT =0)>
	endm
AUX_WIND_HAS_STENCIL macro x
	exitm<(((x) AND AUX_STENCIL) NOT =0)>
	endm
AUX_WIND_USES_FIXED_332_PAL macro x
	exitm<(((x) AND AUX_FIXED_332_PAL) NOT =0)>
	endm

AUX_EXPOSE		equ 1
AUX_CONFIG		equ 2
AUX_DRAW		equ 4
AUX_KEYEVENT		equ 8
AUX_MOUSEDOWN		equ 16
AUX_MOUSEUP		equ 32
AUX_MOUSELOC		equ 64

AUX_WINDOWX		equ 0
AUX_WINDOWY		equ 1
AUX_MOUSEX		equ 0
AUX_MOUSEY		equ 1
AUX_MOUSESTATUS		equ 3
AUX_KEY			equ 0
AUX_KEYSTATUS		equ 1

AUX_LEFTBUTTON		equ 1
AUX_RIGHTBUTTON		equ 2
AUX_MIDDLEBUTTON	equ 4
AUX_SHIFT		equ 1
AUX_CONTROL		equ 2

AUX_RETURN		equ 0x0D
AUX_ESCAPE		equ 0x1B
AUX_SPACE		equ 0x20
AUX_LEFT		equ 0x25
AUX_UP			equ 0x26
AUX_RIGHT		equ 0x27
AUX_DOWN		equ 0x28
AUX_A			equ 'A'
AUX_B			equ 'B'
AUX_C			equ 'C'
AUX_D			equ 'D'
AUX_E			equ 'E'
AUX_F			equ 'F'
AUX_G			equ 'G'
AUX_H			equ 'H'
AUX_I			equ 'I'
AUX_J			equ 'J'
AUX_K			equ 'K'
AUX_L			equ 'L'
AUX_M			equ 'M'
AUX_N			equ 'N'
AUX_O			equ 'O'
AUX_P			equ 'P'
AUX_Q			equ 'Q'
AUX_R			equ 'R'
AUX_S			equ 'S'
AUX_T			equ 'T'
AUX_U			equ 'U'
AUX_V			equ 'V'
AUX_W			equ 'W'
AUX_X			equ 'X'
AUX_Y			equ 'Y'
AUX_Z			equ 'Z'
AUX_a			equ 'a'
AUX_b			equ 'b'
AUX_c			equ 'c'
AUX_d			equ 'd'
AUX_e			equ 'e'
AUX_f			equ 'f'
AUX_g			equ 'g'
AUX_h			equ 'h'
AUX_i			equ 'i'
AUX_j			equ 'j'
AUX_k			equ 'k'
AUX_l			equ 'l'
AUX_m			equ 'm'
AUX_n			equ 'n'
AUX_o			equ 'o'
AUX_p			equ 'p'
AUX_q			equ 'q'
AUX_r			equ 'r'
AUX_s			equ 's'
AUX_t			equ 't'
AUX_u			equ 'u'
AUX_v			equ 'v'
AUX_w			equ 'w'
AUX_x			equ 'x'
AUX_y			equ 'y'
AUX_z			equ 'z'
AUX_0			equ '0'
AUX_1			equ '1'
AUX_2			equ '2'
AUX_3			equ '3'
AUX_4			equ '4'
AUX_5			equ '5'
AUX_6			equ '6'
AUX_7			equ '7'
AUX_8			equ '8'
AUX_9			equ '9'

AUX_FD			equ 1
AUX_COLORMAP		equ 3
AUX_GREYSCALEMAP	equ 4
AUX_FOGMAP		equ 5
AUX_ONECOLOR		equ 6

AUX_BLACK		equ 0
AUX_RED			equ 13
AUX_GREEN		equ 14
AUX_YELLOW		equ 15
AUX_BLUE		equ 16
AUX_MAGENTA		equ 17
AUX_CYAN		equ 18
AUX_WHITE		equ 19

AUX_SETCOLOR macro x,y
	exitm<(AUX_WIND_IS_RGB((x)) ? glColor3fv(auxRGBMap[(y)]) : glIndexf((y)))>
	endm

AUX_EVENTREC		STRUC
event			GLint ?
data			GLint 4 dup(?)
AUX_EVENTREC		ENDS

AUX_RGBImageRec		STRUC
sizeX			GLint ?
sizeY			GLint ?
AUX_RGBImageRec		ENDS

CALLBACK(AUXMAINPROC)
CALLBACK(AUXEXPOSEPROC, :int_t, :int_t)
CALLBACK(AUXRESHAPEPROC, :GLsizei, :GLsizei)
CALLBACK(AUXIDLEPROC)
CALLBACK(AUXKEYPROC)
CALLBACK(AUXMOUSEPROC, :ptr AUX_EVENTREC)

.enum {
    AUX_USE_ID = 1,
    AUX_EXACT_MATCH,
    AUX_MINIMUM_CRITERIA
    }

;void
auxInitDisplayMode	proto WINAPI :GLenum
auxInitPosition		proto WINAPI :SINT, :SINT, :SINT, :SINT
;GLenum
auxInitWindowA		proto WINAPI :LPCSTR
auxInitWindowW		proto WINAPI :LPCWSTR
;void
auxCloseWindow		proto WINAPI
auxQuit			proto WINAPI
auxSwapBuffers		proto WINAPI
auxMainLoop		proto WINAPI :AUXMAINPROC
auxExposeFunc		proto WINAPI :AUXEXPOSEPROC
auxReshapeFunc		proto WINAPI :AUXRESHAPEPROC
auxIdleFunc		proto WINAPI :AUXIDLEPROC
auxKeyFunc		proto WINAPI :SINT, :AUXKEYPROC
auxMouseFunc		proto WINAPI :SINT, :SINT, :AUXMOUSEPROC
;int
auxGetColorMapSize	proto WINAPI
;void
auxGetMouseLoc		proto WINAPI :ptr, :ptr
auxSetOneColor		proto WINAPI :SINT, :float, :float, :float
auxSetFogRamp		proto WINAPI :SINT, :SINT
auxSetGreyRamp		proto WINAPI
auxSetRGBMap		proto WINAPI :SINT, :ptr float
;AUX_RGBImageRec*
auxRGBImageLoadA	proto WINAPI :LPCSTR
auxRGBImageLoadW	proto WINAPI :LPCWSTR
auxDIBImageLoadA	proto WINAPI :LPCSTR
auxDIBImageLoadW	proto WINAPI :LPCWSTR
;void
auxCreateFont		proto WINAPI
auxDrawStrA		proto WINAPI :LPCSTR
auxDrawStrW		proto WINAPI :LPCWSTR
auxWireSphere		proto WINAPI :GLdouble
auxSolidSphere		proto WINAPI :GLdouble
auxWireCube		proto WINAPI :GLdouble
auxSolidCube		proto WINAPI :GLdouble
auxWireBox		proto WINAPI :GLdouble, :GLdouble, :GLdouble
auxSolidBox		proto WINAPI :GLdouble, :GLdouble, :GLdouble
auxWireTorus		proto WINAPI :GLdouble, :GLdouble
auxSolidTorus		proto WINAPI :GLdouble, :GLdouble
auxWireCylinder		proto WINAPI :GLdouble, :GLdouble
auxSolidCylinder	proto WINAPI :GLdouble, :GLdouble
auxWireIcosahedron	proto WINAPI :GLdouble
auxSolidIcosahedron	proto WINAPI :GLdouble
auxWireOctahedron	proto WINAPI :GLdouble
auxSolidOctahedron	proto WINAPI :GLdouble
auxWireTetrahedron	proto WINAPI :GLdouble
auxSolidTetrahedron	proto WINAPI :GLdouble
auxWireDodecahedron	proto WINAPI :GLdouble
auxSolidDodecahedron	proto WINAPI :GLdouble
auxWireCone		proto WINAPI :GLdouble, :GLdouble
auxSolidCone		proto WINAPI :GLdouble, :GLdouble
auxWireTeapot		proto WINAPI :GLdouble
auxSolidTeapot		proto WINAPI :GLdouble

;HWND
auxGetHWND		proto WINAPI
;HDC APIENTRY
auxGetHDC		proto WINAPI
;HGLRC APIENTRY
auxGetHGLRC		proto WINAPI
;void
auxInitDisplayModePolicy proto WINAPI :GLenum

;GLenum APIENTRY
auxInitDisplayModeID	proto WINAPI :GLint
auxGetDisplayModePolicy proto WINAPI
auxGetDisplayModeID	proto WINAPI
auxGetDisplayMode	proto WINAPI

ifdef _UNICODE
auxInitWindow		equ <auxInitWindowW>
auxRGBImageLoad		equ <auxRGBImageLoadW>
auxDIBImageLoad		equ <auxDIBImageLoadW>
auxDrawStr		equ <auxDrawStrW>
else
auxInitWindow		equ <auxInitWindowA>
auxRGBImageLoad		equ <auxRGBImageLoadA>
auxDIBImageLoad		equ <auxDIBImageLoadA>
auxDrawStr		equ <auxDrawStrA>
endif

endif
