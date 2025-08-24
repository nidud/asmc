ifndef __GTK_IM_MULTICONTEXT_H__
define __GTK_IM_MULTICONTEXT_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkimcontext.inc

define GTK_TYPE_IM_MULTICONTEXT <gtk_im_multicontext_get_type ()>
GTK_IM_MULTICONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_IM_MULTICONTEXT, GtkIMMulticontext))>
  endm
GTK_IM_MULTICONTEXT_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_IM_MULTICONTEXT, GtkIMMulticontextClass))>
  endm
GTK_IS_IM_MULTICONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_IM_MULTICONTEXT))>
  endm
GTK_IS_IM_MULTICONTEXT_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_IM_MULTICONTEXT))>
  endm
GTK_IM_MULTICONTEXT_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_IM_MULTICONTEXT, GtkIMMulticontextClass))>
  endm


GtkIMMulticontext       struct
object                  GtkIMContext <>
priv                    ptr GtkIMMulticontextPrivate ?
GtkIMMulticontext       ends

GtkIMMulticontextClass  struct
parent_class            GtkIMContextClass <>
_gtk_reserved1          proc
_gtk_reserved2          proc
_gtk_reserved3          proc
_gtk_reserved4          proc
GtkIMMulticontextClass  ends

gtk_im_multicontext_get_type proto
gtk_im_multicontext_new proto
gtk_im_multicontext_get_context_id proto :ptr
gtk_im_multicontext_set_context_id proto :ptr, :ptr

endif
