ifndef __GTK_IM_CONTEXT_SIMPLE_H__
__GTK_IM_CONTEXT_SIMPLE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkimcontext.inc

G_BEGIN_DECLS

GTK_MAX_COMPOSE_LEN	equ 7

GTK_TYPE_IM_CONTEXT_SIMPLE equ <gtk_im_context_simple_get_type>
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


GtkIMContextSimple	STRUC
object			GtkIMContext <>
priv			ptr_t ?
GtkIMContextSimple	ENDS

GtkIMContextSimpleClass STRUC
parent_class		GtkIMContextClass <>
GtkIMContextSimpleClass ENDS

;GType
gtk_im_context_simple_get_type proto __cdecl
;GtkIMContext
gtk_im_context_simple_new proto __cdecl

;void
gtk_im_context_simple_add_table proto __cdecl \
	context_simple: ptr GtkIMContextSimple,
		  data: ptr guint16,
	   max_seq_len: gint,
		n_seqs: gint


G_END_DECLS

endif
