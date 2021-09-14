ifndef __glut_h__
define __glut_h__
ifndef _CRT_TERMINATE_DEFINED
 include stdlib.inc
endif

include gl/gl.inc
include gl/glu.inc

ifdef _WIN32
 if NOT defined(GLUT_BUILDING_LIB) AND NOT defined(GLUT_NO_LIB_PRAGMA)
  ;.pragma comment(lib, winmm)
  ifdef GLUT_USE_SGI_OPENGL
   ;.pragma comment(lib, opengl)
   ;.pragma comment(lib, glu)
   .pragma comment(lib, glut)
  else
   ;.pragma comment(lib, opengl32)
   ;.pragma comment(lib, glu32)
   .pragma comment(lib, glut32)
  endif
 endif
endif ;; _WIN32


ifdef _GLPE
ifndef _WIN64
ifndef _REGS6432
define _REGS6432
    rax equ <eax>
    rbx equ <ebx>
    rcx equ <ecx>
    rdx equ <edx>
    rdi equ <edi>
    rsi equ <esi>
    rbp equ <ebp>
    rsp equ <esp>
endif
endif

    option win64:3

    .data
    __argc    int_t 0,0
  ifdef _UNICODE
    __argv    warray_t 0
    __environ warray_t 0
  else
    __argv    array_t 0
    __environ array_t 0
  endif
    _startup  db 128 dup(0)

    .code

glutStartup proc
    .if !__getmainargs( addr __argc, addr __argv, addr __environ, 0, addr _startup )
        mov ecx,__argc
ifdef _WIN64
        mov rdx,__argv
        mov r8,__environ
else
        mov edx,__argv
        mov ebx,__environ
        push    ebx
        push    edx
        push    ecx
endif
        main()
    .endif
    ret

glutStartup endp

glutExit proc retval:int_t

    exit(retval)

glutExit endp

_tstart equ <glutStartup>
endif ; _GLPE

ifndef GLUT_API_VERSION
GLUT_API_VERSION equ 3
endif

ifndef GLUT_XLIB_IMPLEMENTATION
GLUT_XLIB_IMPLEMENTATION equ 15
endif

GLUT_RGB                equ 0
GLUT_RGBA               equ GLUT_RGB
GLUT_INDEX              equ 1
GLUT_SINGLE             equ 0
GLUT_DOUBLE             equ 2
GLUT_ACCUM              equ 4
GLUT_ALPHA              equ 8
GLUT_DEPTH              equ 16
GLUT_STENCIL            equ 32
if (GLUT_API_VERSION GE 2)
GLUT_MULTISAMPLE        equ 128
GLUT_STEREO             equ 256
endif
if (GLUT_API_VERSION GE 3)
GLUT_LUMINANCE          equ 512
endif

GLUT_LEFT_BUTTON        equ 0
GLUT_MIDDLE_BUTTON      equ 1
GLUT_RIGHT_BUTTON       equ 2

GLUT_DOWN               equ 0
GLUT_UP                 equ 1

if (GLUT_API_VERSION GE 2)

GLUT_KEY_F1             equ 1
GLUT_KEY_F2             equ 2
GLUT_KEY_F3             equ 3
GLUT_KEY_F4             equ 4
GLUT_KEY_F5             equ 5
GLUT_KEY_F6             equ 6
GLUT_KEY_F7             equ 7
GLUT_KEY_F8             equ 8
GLUT_KEY_F9             equ 9
GLUT_KEY_F10            equ 10
GLUT_KEY_F11            equ 11
GLUT_KEY_F12            equ 12

GLUT_KEY_LEFT           equ 100
GLUT_KEY_UP             equ 101
GLUT_KEY_RIGHT          equ 102
GLUT_KEY_DOWN           equ 103
GLUT_KEY_PAGE_UP        equ 104
GLUT_KEY_PAGE_DOWN      equ 105
GLUT_KEY_HOME           equ 106
GLUT_KEY_END            equ 107
GLUT_KEY_INSERT         equ 108
endif

GLUT_LEFT               equ 0
GLUT_ENTERED            equ 1

GLUT_MENU_NOT_IN_USE    equ 0
GLUT_MENU_IN_USE        equ 1

GLUT_NOT_VISIBLE        equ 0
GLUT_VISIBLE            equ 1

GLUT_HIDDEN             equ 0
GLUT_FULLY_RETAINED     equ 1
GLUT_PARTIALLY_RETAINED equ 2
GLUT_FULLY_COVERED      equ 3

GLUT_RED                equ 0
GLUT_GREEN              equ 1
GLUT_BLUE               equ 2

if defined(_WIN32)
GLUT_STROKE_ROMAN       equ 0
GLUT_STROKE_MONO_ROMAN  equ 1

GLUT_BITMAP_9_BY_15     equ 2
GLUT_BITMAP_8_BY_13     equ 3
GLUT_BITMAP_TIMES_ROMAN_10 equ 4
GLUT_BITMAP_TIMES_ROMAN_24 equ 5
if (GLUT_API_VERSION GE 3)
GLUT_BITMAP_HELVETICA_10 equ 6
GLUT_BITMAP_HELVETICA_12 equ 7
GLUT_BITMAP_HELVETICA_18 equ 8
endif
else

GLUT_STROKE_ROMAN       equ <&glutStrokeRoman>
GLUT_STROKE_MONO_ROMAN  equ <&glutStrokeMonoRoman>

GLUT_BITMAP_9_BY_15     equ <&glutBitmap9By15>
GLUT_BITMAP_8_BY_13     equ <&glutBitmap8By13>
GLUT_BITMAP_TIMES_ROMAN_10 equ <&glutBitmapTimesRoman10>
GLUT_BITMAP_TIMES_ROMAN_24 equ <&glutBitmapTimesRoman24>
if (GLUT_API_VERSION GE 3)
GLUT_BITMAP_HELVETICA_10 equ <&glutBitmapHelvetica10>
GLUT_BITMAP_HELVETICA_12 equ <&glutBitmapHelvetica12>
GLUT_BITMAP_HELVETICA_18 equ <&glutBitmapHelvetica18>
endif
endif

GLUT_WINDOW_X           equ 100
GLUT_WINDOW_Y           equ 101
GLUT_WINDOW_WIDTH       equ 102
GLUT_WINDOW_HEIGHT      equ 103
GLUT_WINDOW_BUFFER_SIZE equ 104
GLUT_WINDOW_STENCIL_SIZE equ 105
GLUT_WINDOW_DEPTH_SIZE  equ 106
GLUT_WINDOW_RED_SIZE    equ 107
GLUT_WINDOW_GREEN_SIZE  equ 108
GLUT_WINDOW_BLUE_SIZE   equ 109
GLUT_WINDOW_ALPHA_SIZE  equ 110
GLUT_WINDOW_ACCUM_RED_SIZE equ 111
GLUT_WINDOW_ACCUM_GREEN_SIZE equ 112
GLUT_WINDOW_ACCUM_BLUE_SIZE equ 113
GLUT_WINDOW_ACCUM_ALPHA_SIZE equ 114
GLUT_WINDOW_DOUBLEBUFFER equ 115
GLUT_WINDOW_RGBA        equ 116
GLUT_WINDOW_PARENT      equ 117
GLUT_WINDOW_NUM_CHILDREN equ 118
GLUT_WINDOW_COLORMAP_SIZE equ 119
if (GLUT_API_VERSION GE 2)
GLUT_WINDOW_NUM_SAMPLES equ 120
GLUT_WINDOW_STEREO      equ 121
endif
if (GLUT_API_VERSION GE 3)
GLUT_WINDOW_CURSOR      equ 122
endif
GLUT_SCREEN_WIDTH       equ 200
GLUT_SCREEN_HEIGHT      equ 201
GLUT_SCREEN_WIDTH_MM    equ 202
GLUT_SCREEN_HEIGHT_MM   equ 203
GLUT_MENU_NUM_ITEMS     equ 300
GLUT_DISPLAY_MODE_POSSIBLE equ 400
GLUT_INIT_WINDOW_X      equ 500
GLUT_INIT_WINDOW_Y      equ 501
GLUT_INIT_WINDOW_WIDTH  equ 502
GLUT_INIT_WINDOW_HEIGHT equ 503
GLUT_INIT_DISPLAY_MODE  equ 504
if (GLUT_API_VERSION GE 2)
GLUT_ELAPSED_TIME       equ 700
endif
if (GLUT_API_VERSION GE 4 OR GLUT_XLIB_IMPLEMENTATION GE 13)
GLUT_WINDOW_FORMAT_ID   equ 123
endif

if (GLUT_API_VERSION GE 2)
GLUT_HAS_KEYBOARD       equ 600
GLUT_HAS_MOUSE          equ 601
GLUT_HAS_SPACEBALL      equ 602
GLUT_HAS_DIAL_AND_BUTTON_BOX equ 603
GLUT_HAS_TABLET         equ 604
GLUT_NUM_MOUSE_BUTTONS  equ 605
GLUT_NUM_SPACEBALL_BUTTONS equ 606
GLUT_NUM_BUTTON_BOX_BUTTONS equ 607
GLUT_NUM_DIALS          equ 608
GLUT_NUM_TABLET_BUTTONS equ 609
endif
if (GLUT_API_VERSION GE 4 OR GLUT_XLIB_IMPLEMENTATION GE 13)
GLUT_DEVICE_IGNORE_KEY_REPEAT equ 610
GLUT_DEVICE_KEY_REPEAT  equ 611
GLUT_HAS_JOYSTICK       equ 612
GLUT_OWNS_JOYSTICK      equ 613
GLUT_JOYSTICK_BUTTONS   equ 614
GLUT_JOYSTICK_AXES      equ 615
GLUT_JOYSTICK_POLL_RATE equ 616
endif

if (GLUT_API_VERSION GE 3)
GLUT_OVERLAY_POSSIBLE   equ 800
GLUT_LAYER_IN_USE       equ 801
GLUT_HAS_OVERLAY        equ 802
GLUT_TRANSPARENT_INDEX  equ 803
GLUT_NORMAL_DAMAGED     equ 804
GLUT_OVERLAY_DAMAGED    equ 805

if (GLUT_API_VERSION GE 4 OR GLUT_XLIB_IMPLEMENTATION GE 9)

GLUT_VIDEO_RESIZE_POSSIBLE equ 900
GLUT_VIDEO_RESIZE_IN_USE equ 901
GLUT_VIDEO_RESIZE_X_DELTA equ 902
GLUT_VIDEO_RESIZE_Y_DELTA equ 903
GLUT_VIDEO_RESIZE_WIDTH_DELTA equ 904
GLUT_VIDEO_RESIZE_HEIGHT_DELTA equ 905
GLUT_VIDEO_RESIZE_X     equ 906
GLUT_VIDEO_RESIZE_Y     equ 907
GLUT_VIDEO_RESIZE_WIDTH equ 908
GLUT_VIDEO_RESIZE_HEIGHT equ 909
endif

GLUT_NORMAL             equ 0
GLUT_OVERLAY            equ 1

GLUT_ACTIVE_SHIFT       equ 1
GLUT_ACTIVE_CTRL        equ 2
GLUT_ACTIVE_ALT         equ 4

GLUT_CURSOR_RIGHT_ARROW equ 0
GLUT_CURSOR_LEFT_ARROW  equ 1

GLUT_CURSOR_INFO        equ 2
GLUT_CURSOR_DESTROY     equ 3
GLUT_CURSOR_HELP        equ 4
GLUT_CURSOR_CYCLE       equ 5
GLUT_CURSOR_SPRAY       equ 6
GLUT_CURSOR_WAIT        equ 7
GLUT_CURSOR_TEXT        equ 8
GLUT_CURSOR_CROSSHAIR   equ 9

GLUT_CURSOR_UP_DOWN     equ 10
GLUT_CURSOR_LEFT_RIGHT  equ 11

GLUT_CURSOR_TOP_SIDE    equ 12
GLUT_CURSOR_BOTTOM_SIDE equ 13
GLUT_CURSOR_LEFT_SIDE   equ 14
GLUT_CURSOR_RIGHT_SIDE  equ 15
GLUT_CURSOR_TOP_LEFT_CORNER equ 16
GLUT_CURSOR_TOP_RIGHT_CORNER equ 17
GLUT_CURSOR_BOTTOM_RIGHT_CORNER equ 18
GLUT_CURSOR_BOTTOM_LEFT_CORNER equ 19

GLUT_CURSOR_INHERIT     equ 100

GLUT_CURSOR_NONE        equ 101

GLUT_CURSOR_FULL_CROSSHAIR equ 102
endif

if defined(_WIN32) AND NOT defined(GLUT_DISABLE_ATEXIT_HACK)
__glutInitWithExit proto WINAPI :ptr int_t, :array_t, :ptr
ifndef GLUT_BUILDING_LIB
glutInit macro argcp, argv
ifdef _MSVCRT
    exitm<__glutInitWithExit(argcp, argv, &glutExit)>
else
    exitm<__glutInitWithExit(argcp, argv, &exit)>
endif
    endm
endif
else
glutInit proto WINAPI :ptr int_t, :array_t
endif

glutInitDisplayMode proto WINAPI :SINT

if (GLUT_API_VERSION GE 4 OR GLUT_XLIB_IMPLEMENTATION GE 9)

glutInitDisplayString proto WINAPI :string_t

endif

glutInitWindowPosition proto WINAPI :SINT, :SINT
glutInitWindowSize proto WINAPI :SINT, :SINT
glutMainLoop proto WINAPI

if defined(_WIN32) AND NOT defined(GLUT_DISABLE_ATEXIT_HACK)
__glutCreateWindowWithExit proto WINAPI :string_t, :ptr
ifndef GLUT_BUILDING_LIB
glutCreateWindow macro title
ifdef _MSVCRT
    exitm<__glutCreateWindowWithExit(title, &glutExit)>
else
    exitm<__glutCreateWindowWithExit(title, &exit)>
endif
    endm
endif
else
glutCreateWindow proto WINAPI :string_t
endif

glutCreateSubWindow proto WINAPI \
                   win: SINT,
                     x: SINT,
                     y: SINT,
                 width: SINT,
                height: SINT

glutDestroyWindow proto WINAPI \
                   win: SINT

glutPostRedisplay proto WINAPI
if (GLUT_API_VERSION GE 4 OR GLUT_XLIB_IMPLEMENTATION GE 11)

glutPostWindowRedisplay proto WINAPI \
                   win: SINT

endif

glutSwapBuffers proto WINAPI

glutGetWindow proto WINAPI

glutSetWindow proto WINAPI \
                   win: SINT

glutSetWindowTitle proto WINAPI \
                 title: ptr char_t

glutSetIconTitle proto WINAPI \
                 title: ptr char_t

glutPositionWindow proto WINAPI \
                     x: SINT,
                     y: SINT

glutReshapeWindow proto WINAPI \
                 width: SINT,
                height: SINT

glutPopWindow proto WINAPI
glutPushWindow proto WINAPI
glutIconifyWindow proto WINAPI
glutShowWindow proto WINAPI
glutHideWindow proto WINAPI
if (GLUT_API_VERSION GE 3)

glutFullScreen proto WINAPI
glutSetCursor proto WINAPI \
                cursor: SINT

if (GLUT_API_VERSION GE 4 OR GLUT_XLIB_IMPLEMENTATION GE 9)

glutWarpPointer proto WINAPI \
                     x: SINT,
                     y: SINT

endif

glutEstablishOverlay proto WINAPI
glutRemoveOverlay proto WINAPI
glutUseLayer proto WINAPI \
                 layer: GLenum

glutPostOverlayRedisplay proto WINAPI
if (GLUT_API_VERSION GE 4 OR GLUT_XLIB_IMPLEMENTATION GE 11)

glutPostWindowOverlayRedisplay proto WINAPI \
                   win: SINT
endif

glutShowOverlay proto WINAPI
glutHideOverlay proto WINAPI
endif

if defined(_WIN32) AND NOT defined(GLUT_DISABLE_ATEXIT_HACK)
__glutCreateMenuWithExit proto WINAPI :ptr, :ptr
ifndef GLUT_BUILDING_LIB
glutCreateMenu macro func
ifdef _MSVCRT
    exitm<__glutCreateMenuWithExit(func, &glutExit)>
else
    exitm<__glutCreateMenuWithExit(func, &exit)>
endif
    endm
endif
else
glutCreateMenu proto WINAPI :ptr_t
endif

glutDestroyMenu proto WINAPI \
                  menu: SINT
glutGetMenu proto WINAPI
glutSetMenu proto WINAPI \
                  menu: SINT

glutAddMenuEntry proto WINAPI \
                 _label: ptr char_t,
                 value: SINT

glutAddSubMenu proto WINAPI \
                _label: ptr char_t,
               submenu: SINT

glutChangeToMenuEntry proto WINAPI \
                  item: SINT,
                _label: ptr char_t,
                 value: SINT

glutChangeToSubMenu proto WINAPI \
                  item: SINT,
                _label: ptr char_t,
               submenu: SINT

glutRemoveMenuItem proto WINAPI \
                  item: SINT

glutAttachMenu proto WINAPI \
                button: SINT

glutDetachMenu proto WINAPI \
                button: SINT


glutDisplayFunc proto WINAPI :ptr
glutReshapeFunc proto WINAPI :ptr
glutKeyboardFunc proto WINAPI :ptr
glutMouseFunc proto WINAPI :ptr
glutMotionFunc proto WINAPI :ptr
glutPassiveMotionFunc proto WINAPI :ptr
glutEntryFunc proto WINAPI :ptr
glutVisibilityFunc proto WINAPI :ptr
glutIdleFunc proto WINAPI :ptr
glutTimerFunc proto WINAPI :ptr
glutMenuStateFunc proto WINAPI :ptr
if (GLUT_API_VERSION GE 2)

glutSpecialFunc proto WINAPI :ptr
glutSpaceballMotionFunc proto WINAPI :ptr
glutSpaceballRotateFunc proto WINAPI :ptr
glutSpaceballButtonFunc proto WINAPI :ptr
glutButtonBoxFunc proto WINAPI :ptr
glutDialsFunc proto WINAPI :ptr
glutTabletMotionFunc proto WINAPI :ptr
glutTabletButtonFunc proto WINAPI :ptr

if (GLUT_API_VERSION GE 3)

glutMenuStatusFunc proto WINAPI :ptr
glutOverlayDisplayFunc proto WINAPI :ptr
if (GLUT_API_VERSION GE 4 OR GLUT_XLIB_IMPLEMENTATION GE 9)
glutWindowStatusFunc proto WINAPI :ptr
endif
if (GLUT_API_VERSION GE 4 or GLUT_XLIB_IMPLEMENTATION GE 13)
glutKeyboardUpFunc proto WINAPI :ptr
glutSpecialUpFunc proto WINAPI :ptr
glutJoystickFunc proto WINAPI :ptr
endif
endif
endif

glutSetColor proto WINAPI \
                      : SINT,
                   red: GLfloat,
                 green: GLfloat,
                  blue: GLfloat

glutGetColor proto WINAPI \
                   ndx: int_t,
             component: int_t

glutCopyColormap proto WINAPI \
                   win: SINT


glutGet proto WINAPI \
                  type: GLenum

glutDeviceGet proto WINAPI \
                  type: GLenum

if (GLUT_API_VERSION GE 2)
glutExtensionSupported proto WINAPI \
                  name: ptr char_t

endif
if (GLUT_API_VERSION GE 3)

glutGetModifiers proto WINAPI
glutLayerGet proto WINAPI \
                  type: GLenum

endif

glutBitmapCharacter proto WINAPI \
                  font: ptr,
             character: SINT

glutBitmapWidth proto WINAPI \
                  font: ptr,
             character: SINT

glutStrokeCharacter proto WINAPI \
                  font: ptr,
             character: SINT

glutStrokeWidth proto WINAPI \
                  font: ptr,
             character: SINT

if (GLUT_API_VERSION GE 4 OR GLUT_XLIB_IMPLEMENTATION GE 9)

glutBitmapLength proto WINAPI \
                  font: ptr,
                      : LPSTR

glutStrokeLength proto WINAPI \
                  font: ptr,
                      : LPSTR

endif

glutWireSphere proto WINAPI \
                radius: GLdouble,
                slices: GLint,
                stacks: GLint

glutSolidSphere proto WINAPI \
                radius: GLdouble,
                slices: GLint,
                stacks: GLint

glutWireCone proto WINAPI \
                  base: GLdouble,
                height: GLdouble,
                slices: GLint,
                stacks: GLint

glutSolidCone proto WINAPI \
                  base: GLdouble,
                height: GLdouble,
                slices: GLint,
                stacks: GLint

glutWireCube proto WINAPI \
                  size: GLdouble

glutSolidCube proto WINAPI \
                  size: GLdouble

glutWireTorus proto WINAPI \
           innerRadius: GLdouble,
           outerRadius: GLdouble,
                 sides: GLint,
                 rings: GLint

glutSolidTorus proto WINAPI \
           innerRadius: GLdouble,
           outerRadius: GLdouble,
                 sides: GLint,
                 rings: GLint

glutWireDodecahedron proto WINAPI
glutSolidDodecahedron proto WINAPI
glutWireTeapot proto WINAPI \
                  size: GLdouble

glutSolidTeapot proto WINAPI \
                  size: GLdouble

glutWireOctahedron proto WINAPI
glutSolidOctahedron proto WINAPI
glutWireTetrahedron proto WINAPI
glutSolidTetrahedron proto WINAPI
glutWireIcosahedron proto WINAPI
glutSolidIcosahedron proto WINAPI

if (GLUT_API_VERSION GE 4 OR GLUT_XLIB_IMPLEMENTATION GE 9)
glutVideoResizeGet proto WINAPI \
                 param: GLenum

glutSetupVideoResizing proto WINAPI
glutStopVideoResizing proto WINAPI
glutVideoResize proto WINAPI \
                     x: SINT,
                     y: SINT,
                 width: SINT,
                height: SINT

glutVideoPan proto WINAPI \
                     x: SINT,
                     y: SINT,
                 width: SINT,
                height: SINT


glutReportErrors proto WINAPI
endif

if (GLUT_API_VERSION GE 4 OR GLUT_XLIB_IMPLEMENTATION GE 13)
GLUT_KEY_REPEAT_OFF     equ 0
GLUT_KEY_REPEAT_ON      equ 1
GLUT_KEY_REPEAT_DEFAULT equ 2

GLUT_JOYSTICK_BUTTON_A  equ 1
GLUT_JOYSTICK_BUTTON_B  equ 2
GLUT_JOYSTICK_BUTTON_C  equ 4
GLUT_JOYSTICK_BUTTON_D  equ 8

glutIgnoreKeyRepeat proto WINAPI \
                ignore: SINT

glutSetKeyRepeat proto WINAPI \
            repeatMode: SINT

glutForceJoystickFunc proto WINAPI

GLUT_GAME_MODE_ACTIVE   equ 0
GLUT_GAME_MODE_POSSIBLE equ 1
GLUT_GAME_MODE_WIDTH    equ 2
GLUT_GAME_MODE_HEIGHT   equ 3
GLUT_GAME_MODE_PIXEL_DEPTH equ 4
GLUT_GAME_MODE_REFRESH_RATE equ 5
GLUT_GAME_MODE_DISPLAY_CHANGED equ 6

glutGameModeString proto WINAPI :string_t

glutEnterGameMode proto WINAPI
glutLeaveGameMode proto WINAPI
glutGameModeGet proto WINAPI :GLenum

endif
endif ;; __glut_h__
