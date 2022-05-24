ifndef __GTK_STYLE_CONTEXT_H__
define __GTK_STYLE_CONTEXT_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/css/gtkcss.inc

include gtk/gtkborder.inc
include gtk/gtkstyleprovider.inc
include gtk/gtktypes.inc

define GTK_TYPE_STYLE_CONTEXT <gtk_style_context_get_type ()>
GTK_STYLE_CONTEXT macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_STYLE_CONTEXT, GtkStyleContext))>
  endm
GTK_STYLE_CONTEXT_CLASS macro c
  exitm<(G_TYPE_CHECK_CLASS_CAST    ((c), GTK_TYPE_STYLE_CONTEXT, GtkStyleContextClass))>
  endm
GTK_IS_STYLE_CONTEXT macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_STYLE_CONTEXT))>
  endm
GTK_IS_STYLE_CONTEXT_CLASS macro c
  exitm<(G_TYPE_CHECK_CLASS_TYPE    ((c), GTK_TYPE_STYLE_CONTEXT))>
  endm
GTK_STYLE_CONTEXT_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS  ((o), GTK_TYPE_STYLE_CONTEXT, GtkStyleContextClass))>
  endm

_GtkStyleContext        struct
parent_object           GObject <>
_GtkStyleContext        ends

_GtkStyleContextClass   struct
parent_class            GObjectClass <>
changed                 proc :ptr
_gtk_reserved1          proc
_gtk_reserved2          proc
_gtk_reserved3          proc
_gtk_reserved4          proc
_GtkStyleContextClass   ends
GtkStyleContextClass    typedef _GtkStyleContextClass


gtk_style_context_get_type proto
gtk_style_context_add_provider_for_display proto :ptr, :ptr, :guint
gtk_style_context_remove_provider_for_display proto :ptr, :ptr
gtk_style_context_add_provider proto :ptr, :ptr, :guint
gtk_style_context_remove_provider proto :ptr, :ptr
gtk_style_context_save proto :ptr
gtk_style_context_restore proto :ptr
gtk_style_context_set_state proto :ptr, :GtkStateFlags
gtk_style_context_get_state proto :ptr
gtk_style_context_set_scale proto :ptr, :sdword
gtk_style_context_get_scale proto :ptr
gtk_style_context_add_class proto :ptr, :ptr
gtk_style_context_remove_class proto :ptr, :ptr
gtk_style_context_has_class proto :ptr, :ptr
gtk_style_context_set_display proto :ptr, :ptr
gtk_style_context_get_display proto :ptr
gtk_style_context_lookup_color proto :ptr, :ptr, :ptr
gtk_style_context_get_color proto :ptr, :ptr
gtk_style_context_get_border proto :ptr, :ptr
gtk_style_context_get_padding proto :ptr, :ptr
gtk_style_context_get_margin proto :ptr, :ptr

.enum GtkStyleContextPrintFlags {
  GTK_STYLE_CONTEXT_PRINT_NONE         = 0,
  GTK_STYLE_CONTEXT_PRINT_RECURSE      = 1 shl 0,
  GTK_STYLE_CONTEXT_PRINT_SHOW_STYLE   = 1 shl 1,
  GTK_STYLE_CONTEXT_PRINT_SHOW_CHANGE  = 1 shl 2
  }

gtk_style_context_to_string proto :ptr, :GtkStyleContextPrintFlags

endif
