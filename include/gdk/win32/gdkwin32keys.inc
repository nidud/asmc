ifndef __GDK_WIN32_KEYS_H__
define __GDK_WIN32_KEYS_H__

if not defined (__GDKWIN32_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdkwin32.h can be included directly.">
endif

include gdk/gdk.inc
include gdkkeysprivate.inc

.enum GdkWin32KeymapMatch {
  GDK_WIN32_KEYMAP_MATCH_NONE,
  GDK_WIN32_KEYMAP_MATCH_INCOMPLETE,
  GDK_WIN32_KEYMAP_MATCH_PARTIAL,
  GDK_WIN32_KEYMAP_MATCH_EXACT
}

ifdef GTK_COMPILATION
GdkWin32Keymap          typedef _GdkWin32Keymap
else
GdkWin32Keymap          typedef GdkKeymap
endif
GdkWin32KeymapClass     typedef _GdkWin32KeymapClass

define GDK_TYPE_WIN32_KEYMAP              <gdk_win32_keymap_get_type>
GDK_WIN32_KEYMAP macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_WIN32_KEYMAP, GdkWin32Keymap))>
  endm
GDK_WIN32_KEYMAP_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_WIN32_KEYMAP, GdkWin32KeymapClass))>
  endm
GDK_IS_WIN32_KEYMAP macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_WIN32_KEYMAP))>
  endm
GDK_IS_WIN32_KEYMAP_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_WIN32_KEYMAP))>
  endm
GDK_WIN32_KEYMAP_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_WIN32_KEYMAP, GdkWin32KeymapClass))>
  endm

gdk_win32_keymap_get_type proto
gdk_win32_keymap_check_compose proto :ptr, :ptr, :gsize, :ptr, :ptr

endif
