ifndef __GTK_ACCEL_LABEL_H__
__GTK_ACCEL_LABEL_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtklabel.inc


G_BEGIN_DECLS

GTK_TYPE_ACCEL_LABEL equ <gtk_accel_label_get_type>
GTK_ACCEL_LABEL macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ACCEL_LABEL, GtkAccelLabel))>
	endm
GTK_ACCEL_LABEL_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ACCEL_LABEL, GtkAccelLabelClass))>
	endm
GTK_IS_ACCEL_LABEL macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ACCEL_LABEL))>
	endm
GTK_IS_ACCEL_LABEL_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ACCEL_LABEL))>
	endm
GTK_ACCEL_LABEL_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ACCEL_LABEL, GtkAccelLabelClass))>
	endm

GtkAccelLabel		STRUC
_label			GtkLabel <>
priv			ptr_t ?
GtkAccelLabel		ENDS

GtkAccelLabelClass	STRUC
parent_class		GtkLabelClass <>
signal_quote1		string_t ?
signal_quote2		string_t ?
mod_name_shift		string_t ?
mod_name_control	string_t ?
mod_name_alt		string_t ?
mod_separator		string_t ?
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkAccelLabelClass	ENDS


;GType
gtk_accel_label_get_type proto __cdecl
;GtkWidget*
gtk_accel_label_new proto __cdecl \
		string: ptr gchar

;GtkWidget*
gtk_accel_label_get_accel_widget proto __cdecl \
	   accel_label: ptr GtkAccelLabel

;guint
gtk_accel_label_get_accel_width proto __cdecl \
	   accel_label: ptr GtkAccelLabel

;void
gtk_accel_label_set_accel_widget proto __cdecl \
	   accel_label: ptr GtkAccelLabel,
	  accel_widget: ptr GtkWidget

;void
gtk_accel_label_set_accel_closure proto __cdecl \
	   accel_label: ptr GtkAccelLabel,
	 accel_closure: ptr GClosure

;gboolean
gtk_accel_label_refetch proto __cdecl \
	   accel_label: ptr GtkAccelLabel

;void
gtk_accel_label_set_accel proto __cdecl \
	   accel_label: ptr GtkAccelLabel,
       accelerator_key: guint,
      accelerator_mods: GdkModifierType

;void
gtk_accel_label_get_accel proto __cdecl \
	   accel_label: ptr GtkAccelLabel,
       accelerator_key: ptr guint,
      accelerator_mods: ptr GdkModifierType


;*
_gtk_accel_label_class_get_accelerator_label proto __cdecl \
		 klass: ptr GtkAccelLabelClass,
       accelerator_key: guint,
      accelerator_mods: GdkModifierType


G_END_DECLS

endif
