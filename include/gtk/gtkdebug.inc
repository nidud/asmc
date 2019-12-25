ifndef __GTK_DEBUG_H__
__GTK_DEBUG_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib.inc
include gdk/gdk.inc

G_BEGIN_DECLS

.enum GtkDebugFlag {
  GTK_DEBUG_MISC	    = 1 shl 0,
  GTK_DEBUG_PLUGSOCKET	    = 1 shl 1,
  GTK_DEBUG_TEXT	    = 1 shl 2,
  GTK_DEBUG_TREE	    = 1 shl 3,
  GTK_DEBUG_UPDATES	    = 1 shl 4,
  GTK_DEBUG_KEYBINDINGS	    = 1 shl 5,
  GTK_DEBUG_MULTIHEAD	    = 1 shl 6,
  GTK_DEBUG_MODULES	    = 1 shl 7,
  GTK_DEBUG_GEOMETRY	    = 1 shl 8,
  GTK_DEBUG_ICONTHEME	    = 1 shl 9,
  GTK_DEBUG_PRINTING	    = 1 shl 10,
  GTK_DEBUG_BUILDER	    = 1 shl 11,
  GTK_DEBUG_SIZE_REQUEST    = 1 shl 12,
  GTK_DEBUG_NO_CSS_CACHE    = 1 shl 13,
  GTK_DEBUG_BASELINES	    = 1 shl 14,
  GTK_DEBUG_PIXEL_CACHE	    = 1 shl 15,
  GTK_DEBUG_NO_PIXEL_CACHE  = 1 shl 16,
  GTK_DEBUG_INTERACTIVE	    = 1 shl 17,
  GTK_DEBUG_TOUCHSCREEN	    = 1 shl 18,
  GTK_DEBUG_ACTIONS	    = 1 shl 19
}

ifdef G_ENABLE_DEBUG

GTK_DEBUG_CHECK macro type
	exitm<G_UNLIKELY (gtk_get_debug_flags () AND GTK_DEBUG_##type)>
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

;guint
gtk_get_debug_flags proto __cdecl
;void
gtk_set_debug_flags proto __cdecl \
		 flags: guint

G_END_DECLS

endif
