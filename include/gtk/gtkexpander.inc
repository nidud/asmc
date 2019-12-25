ifndef __GTK_EXPANDER_H__
__GTK_EXPANDER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbin.inc

G_BEGIN_DECLS

GTK_TYPE_EXPANDER equ <gtk_expander_get_type>
GTK_EXPANDER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_EXPANDER, GtkExpander))>
	endm
GTK_EXPANDER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_EXPANDER, GtkExpanderClass))>
	endm
GTK_IS_EXPANDER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_EXPANDER))>
	endm
GTK_IS_EXPANDER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_EXPANDER))>
	endm
GTK_EXPANDER_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_EXPANDER, GtkExpanderClass))>
	endm

GtkExpander		STRUC
bin			GtkBin <>
priv			ptr_t ?
GtkExpander		ENDS

GtkExpanderClass	STRUC
parent_class		GtkBinClass <>
 activate		proc :ptr GtkExpander
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkExpanderClass	ENDS

;GType
gtk_expander_get_type proto __cdecl

;GtkWidget
gtk_expander_new proto __cdecl \
		_label: ptr gchar

;GtkWidget
gtk_expander_new_with_mnemonic proto __cdecl \
		_label: ptr gchar

;void
gtk_expander_set_expanded proto __cdecl \
	      expander: ptr GtkExpander,
	      expanded: gboolean

;gboolean
gtk_expander_get_expanded proto __cdecl \
	      expander: ptr GtkExpander


;void
gtk_expander_set_spacing proto __cdecl \
	      expander: ptr GtkExpander,
	       spacing: gint

;gint
gtk_expander_get_spacing proto __cdecl \
	      expander: ptr GtkExpander

;void
gtk_expander_set_label proto __cdecl \
	      expander: ptr GtkExpander,
		_label: ptr gchar

;const
gtk_expander_get_label proto __cdecl \
	      expander: ptr GtkExpander

;void
gtk_expander_set_use_underline proto __cdecl \
	      expander: ptr GtkExpander,
	 use_underline: gboolean

;gboolean
gtk_expander_get_use_underline proto __cdecl \
	      expander: ptr GtkExpander

;void
gtk_expander_set_use_markup proto __cdecl \
	      expander: ptr GtkExpander,
	    use_markup: gboolean

;gboolean
gtk_expander_get_use_markup proto __cdecl \
	      expander: ptr GtkExpander

;void
gtk_expander_set_label_widget proto __cdecl \
	      expander: ptr GtkExpander,
	  label_widget: ptr GtkWidget

;GtkWidget
gtk_expander_get_label_widget proto __cdecl \
	      expander: ptr GtkExpander

;void
gtk_expander_set_label_fill proto __cdecl \
	      expander: ptr GtkExpander,
	    label_fill: gboolean

;gboolean
gtk_expander_get_label_fill proto __cdecl \
	      expander: ptr GtkExpander

;void
gtk_expander_set_resize_toplevel proto __cdecl \
	      expander: ptr GtkExpander,
       resize_toplevel: gboolean

;gboolean
gtk_expander_get_resize_toplevel proto __cdecl \
	      expander: ptr GtkExpander

G_END_DECLS

endif
