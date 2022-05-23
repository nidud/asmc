ifndef __GTK_DEBUG_H__
define __GTK_DEBUG_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib.inc
include gdk/gdk.inc

.enum GtkDebugFlags {
  GTK_DEBUG_TEXT            = 1 shl 0,
  GTK_DEBUG_TREE            = 1 shl 1,
  GTK_DEBUG_KEYBINDINGS     = 1 shl 2,
  GTK_DEBUG_MODULES         = 1 shl 3,
  GTK_DEBUG_GEOMETRY        = 1 shl 4,
  GTK_DEBUG_ICONTHEME       = 1 shl 5,
  GTK_DEBUG_PRINTING        = 1 shl 6,
  GTK_DEBUG_BUILDER         = 1 shl 7,
  GTK_DEBUG_SIZE_REQUEST    = 1 shl 8,
  GTK_DEBUG_NO_CSS_CACHE    = 1 shl 9,
  GTK_DEBUG_INTERACTIVE     = 1 shl 10,
  GTK_DEBUG_TOUCHSCREEN     = 1 shl 11,
  GTK_DEBUG_ACTIONS         = 1 shl 12,
  GTK_DEBUG_LAYOUT          = 1 shl 13,
  GTK_DEBUG_SNAPSHOT        = 1 shl 14,
  GTK_DEBUG_CONSTRAINTS     = 1 shl 15,
  GTK_DEBUG_BUILDER_OBJECTS = 1 shl 16,
  GTK_DEBUG_A11Y            = 1 shl 17,
  GTK_DEBUG_ICONFALLBACK    = 1 shl 18,
}

ifdef G_ENABLE_DEBUG

GTK_DEBUG_CHECK macro type
  exitm<G_UNLIKELY (gtk_get_debug_flags () & GTK_DEBUG_&type&)>
  endm

GTK_NOTE macro type,action
  exitm<.err>
  endm

else

GTK_DEBUG_CHECK macro type
  exitm<0>
  endm
GTK_NOTE macro type, action
  exitm<>
  endm

endif

gtk_get_debug_flags proto
gtk_set_debug_flags proto :GtkDebugFlags

endif
