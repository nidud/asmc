ifndef __GTK_MODEL_BUTTON_H__
__GTK_MODEL_BUTTON_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_MODEL_BUTTON equ <gtk_model_button_get_type>
GTK_MODEL_BUTTON macro inst
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), GTK_TYPE_MODEL_BUTTON, GtkModelButton))>
	endm
GTK_IS_MODEL_BUTTON macro inst
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), GTK_TYPE_MODEL_BUTTON))>
	endm

.enum GtkButtonRole {
  GTK_BUTTON_ROLE_NORMAL,
  GTK_BUTTON_ROLE_CHECK,
  GTK_BUTTON_ROLE_RADIO
}

;GType
gtk_model_button_get_type proto __cdecl

;GtkWidget
gtk_model_button_new proto __cdecl

G_END_DECLS

endif
