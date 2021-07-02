ifndef __GTK_COMBO_BOX_TEXT_H__
__GTK_COMBO_BOX_TEXT_H__ equ <>
if defined(GTK_DISABLE_SINGLE_INCLUDES) AND NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcombobox.inc

G_BEGIN_DECLS

GTK_TYPE_COMBO_BOX_TEXT equ <gtk_combo_box_text_get_type>
GTK_COMBO_BOX_TEXT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_COMBO_BOX_TEXT, GtkComboBoxText))>
	endm
GTK_COMBO_BOX_TEXT_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_COMBO_BOX_TEXT, GtkComboBoxTextClass))>
	endm
GTK_IS_COMBO_BOX_TEXT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_COMBO_BOX_TEXT))>
	endm
GTK_IS_COMBO_BOX_TEXT_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_COMBO_BOX_TEXT))>
	endm
GTK_COMBO_BOX_TEXT_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_COMBO_BOX_TEXT, GtkComboBoxTextClass))>
	endm

GtkComboBoxText		STRUC
parent_instance		GtkComboBox <>
priv			ptr_t ?
GtkComboBoxText		ENDS

GtkComboBoxTextClass	STRUC
parent_class		GtkComboBoxClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkComboBoxTextClass	ENDS

;GType
gtk_combo_box_text_get_type proto __cdecl
;GtkWidget*
gtk_combo_box_text_new proto __cdecl
;GtkWidget*
gtk_combo_box_text_new_with_entry proto __cdecl
;void
gtk_combo_box_text_append_text proto __cdecl \
	     combo_box: ptr GtkComboBoxText,
		  text: ptr gchar

;void
gtk_combo_box_text_insert_text proto __cdecl \
	     combo_box: ptr GtkComboBoxText,
	      position: gint,
		  text: ptr gchar

;void
gtk_combo_box_text_prepend_text proto __cdecl \
	     combo_box: ptr GtkComboBoxText,
		  text: ptr gchar

;void
gtk_combo_box_text_remove proto __cdecl \
	     combo_box: ptr GtkComboBoxText,
	      position: gint

;void
gtk_combo_box_text_remove_all proto __cdecl \
	     combo_box: ptr GtkComboBoxText

;gchar
gtk_combo_box_text_get_active_text proto __cdecl \
	     combo_box: ptr GtkComboBoxText


;void
gtk_combo_box_text_insert proto __cdecl \
	     combo_box: ptr GtkComboBoxText,
	      position: gint,
		    id: ptr gchar,
		  text: ptr gchar

;void
gtk_combo_box_text_append proto __cdecl \
	     combo_box: ptr GtkComboBoxText,
		    id: ptr gchar,
		  text: ptr gchar

;void
gtk_combo_box_text_prepend proto __cdecl \
	     combo_box: ptr GtkComboBoxText,
		    id: ptr gchar,
		  text: ptr gchar

G_END_DECLS

endif
