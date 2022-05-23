ifndef __GDK_WIN32_MISC_H__
define __GDK_WIN32_MISC_H__

if not defined (__GDKWIN32_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdkwin32.h can be included directly.">
endif

include gdk/gdk.inc

ifndef STRICT
define STRICT
endif
include windows.inc
include commctrl.inc

ifdef INSIDE_GDK_WIN32

include gdkprivate-win32.inc

GDK_SURFACE_HWND macro win
  exitm<(GDK_WIN32_SURFACE(win)->handle)>
  endm
else

GDK_SURFACE_HWND macro d
  exitm<(gdk_win32_surface_get_handle (d))>
  endm

endif


ifndef WM_XBUTTONDOWN
define WM_XBUTTONDOWN 0x020B
endif
ifndef WM_XBUTTONUP
define WM_XBUTTONUP 0x020C
endif
ifndef GET_XBUTTON_WPARAM
GET_XBUTTON_WPARAM macro w
  exitm<(HIWORD(w))>
  endm
endif
ifndef XBUTTON1
define XBUTTON1 1
endif
ifndef XBUTTON2
define XBUTTON2 2
endif

gdk_win32_surface_is_win32 proto :ptr
gdk_win32_surface_get_impl_hwnd proto :ptr
gdk_win32_handle_table_lookup proto :HWND
gdk_win32_surface_get_handle proto :ptr
gdk_win32_surface_lookup_for_display proto :ptr, :HWND

if defined (INSIDE_GDK_WIN32) or defined (GTK_COMPILATION) or defined (GTK_COMPILATION)

gdk_win32_icon_to_pixbuf_libgtk_only proto :HICON, :ptr, :ptr
gdk_win32_pixbuf_to_hicon_libgtk_only proto :ptr
gdk_win32_set_modal_dialog_libgtk_only proto :HWND

endif

endif
