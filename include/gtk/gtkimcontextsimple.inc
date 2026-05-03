ifndef __GTK_IM_CONTEXT_SIMPLE_H__
define __GTK_IM_CONTEXT_SIMPLE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkimcontext.inc

define GTK_MAX_COMPOSE_LEN 7

define GTK_TYPE_IM_CONTEXT_SIMPLE <gtk_im_context_simple_get_type ()>
GTK_IM_CONTEXT_SIMPLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_IM_CONTEXT_SIMPLE, GtkIMContextSimple))>
  endm
GTK_IM_CONTEXT_SIMPLE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_IM_CONTEXT_SIMPLE, GtkIMContextSimpleClass))>
  endm
GTK_IS_IM_CONTEXT_SIMPLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_IM_CONTEXT_SIMPLE))>
  endm
GTK_IS_IM_CONTEXT_SIMPLE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_IM_CONTEXT_SIMPLE))>
  endm
GTK_IM_CONTEXT_SIMPLE_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_IM_CONTEXT_SIMPLE, GtkIMContextSimpleClass))>
  endm

GtkIMContextSimple      struct
object                  GtkIMContext <>
priv                    ptr GtkIMContextSimplePrivate ?
GtkIMContextSimple      ends

GtkIMContextSimpleClass struct
parent_class            GtkIMContextClass <>
GtkIMContextSimpleClass ends

gtk_im_context_simple_get_type proto
gtk_im_context_simple_new proto
gtk_im_context_simple_add_table proto :ptr, :ptr, :sdword, :sdword
gtk_im_context_simple_add_compose_file proto :ptr, :ptr

endif
