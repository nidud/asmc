ifndef __GTK_IM_MULTICONTEXT_H__
__GTK_IM_MULTICONTEXT_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkimcontext.inc
include gtk/gtkmenushell.inc

G_BEGIN_DECLS

GTK_TYPE_IM_MULTICONTEXT equ <gtk_im_multicontext_get_type>
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


GtkIMMulticontext	STRUC
object			GtkIMContext <>
priv			ptr_t ?
GtkIMMulticontext	ENDS

GtkIMMulticontextClass	STRUC
parent_class		GtkIMContextClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkIMMulticontextClass	ENDS

;GType
gtk_im_multicontext_get_type proto __cdecl
;GtkIMContext
gtk_im_multicontext_new proto __cdecl

;void
gtk_im_multicontext_append_menuitems proto __cdecl \
	       context: ptr GtkIMMulticontext,
	     menushell: ptr GtkMenuShell

;const
gtk_im_multicontext_get_context_id proto __cdecl \
	       context: ptr GtkIMMulticontext


;void
gtk_im_multicontext_set_context_id proto __cdecl \
	       context: ptr GtkIMMulticontext,
	    context_id: ptr char_t

G_END_DECLS

endif
