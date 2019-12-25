ifndef __GTK_COMBO_BOX_H__
__GTK_COMBO_BOX_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbin.inc
include gtk/gtktreemodel.inc
include gtk/gtktreeview.inc

G_BEGIN_DECLS

GTK_TYPE_COMBO_BOX equ <gtk_combo_box_get_type>
GTK_COMBO_BOX macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_COMBO_BOX, GtkComboBox))>
	endm
GTK_COMBO_BOX_CLASS macro vtable
	exitm<(G_TYPE_CHECK_CLASS_CAST ((vtable), GTK_TYPE_COMBO_BOX, GtkComboBoxClass))>
	endm
GTK_IS_COMBO_BOX macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_COMBO_BOX))>
	endm
GTK_IS_COMBO_BOX_CLASS macro vtable
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((vtable), GTK_TYPE_COMBO_BOX))>
	endm
GTK_COMBO_BOX_GET_CLASS macro inst
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), GTK_TYPE_COMBO_BOX, GtkComboBoxClass))>
	endm

GtkComboBox		STRUC
parent_instance		GtkBin <>
priv			ptr_t ?
GtkComboBox		ENDS

GtkComboBoxClass	STRUC
parent_class		GtkBinClass <>
changed			proc :ptr GtkComboBox
format_entry_text	proc :ptr GtkComboBox, :ptr
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
GtkComboBoxClass	ENDS

;GType
gtk_combo_box_get_type proto __cdecl
;GtkWidget
gtk_combo_box_new proto __cdecl
;GtkWidget
gtk_combo_box_new_with_area proto __cdecl \
		  area: ptr GtkCellArea

;GtkWidget
gtk_combo_box_new_with_area_and_entry proto __cdecl \
		  area: ptr GtkCellArea

;GtkWidget
gtk_combo_box_new_with_entry proto __cdecl
;GtkWidget
gtk_combo_box_new_with_model proto __cdecl \
		 model: ptr GtkTreeModel

;GtkWidget
gtk_combo_box_new_with_model_and_entry proto __cdecl \
		 model: ptr GtkTreeModel


;gint
gtk_combo_box_get_wrap_width proto __cdecl \
	     combo_box: ptr GtkComboBox

;void
gtk_combo_box_set_wrap_width proto __cdecl \
	     combo_box: ptr GtkComboBox,
		 width: gint

;gint
gtk_combo_box_get_row_span_column proto __cdecl \
	     combo_box: ptr GtkComboBox

;void
gtk_combo_box_set_row_span_column proto __cdecl \
	     combo_box: ptr GtkComboBox,
	      row_span: gint

;gint
gtk_combo_box_get_column_span_column proto __cdecl \
	     combo_box: ptr GtkComboBox

;void
gtk_combo_box_set_column_span_column proto __cdecl \
	     combo_box: ptr GtkComboBox,
	   column_span: gint


;gboolean
gtk_combo_box_get_add_tearoffs proto __cdecl \
	     combo_box: ptr GtkComboBox

;void
gtk_combo_box_set_add_tearoffs proto __cdecl \
	     combo_box: ptr GtkComboBox,
	  add_tearoffs: gboolean


;const
gtk_combo_box_get_title proto __cdecl \
	     combo_box: ptr GtkComboBox

;void
gtk_combo_box_set_title proto __cdecl \
	     combo_box: ptr GtkComboBox,
		 title: ptr gchar


;gboolean
gtk_combo_box_get_focus_on_click proto __cdecl \
		 combo: ptr GtkComboBox

;void
gtk_combo_box_set_focus_on_click proto __cdecl \
		 combo: ptr GtkComboBox,
	focus_on_click: gboolean


;gint
gtk_combo_box_get_active proto __cdecl \
	     combo_box: ptr GtkComboBox

;void
gtk_combo_box_set_active proto __cdecl \
	     combo_box: ptr GtkComboBox,
		index_: gint

;gboolean
gtk_combo_box_get_active_iter proto __cdecl \
	     combo_box: ptr GtkComboBox,
		  iter: ptr GtkTreeIter

;void
gtk_combo_box_set_active_iter proto __cdecl \
	     combo_box: ptr GtkComboBox,
		  iter: ptr GtkTreeIter


;void
gtk_combo_box_set_model proto __cdecl \
	     combo_box: ptr GtkComboBox,
		 model: ptr GtkTreeModel

;GtkTreeModel
gtk_combo_box_get_model proto __cdecl \
	     combo_box: ptr GtkComboBox


;GtkTreeViewRowSeparatorFunc
gtk_combo_box_get_row_separator_func proto __cdecl \
	     combo_box: ptr GtkComboBox

;void
gtk_combo_box_set_row_separator_func proto __cdecl \
	     combo_box: ptr GtkComboBox,
		  func: GtkTreeViewRowSeparatorFunc,
		  data: gpointer,
	       destroy: GDestroyNotify


;void
gtk_combo_box_set_button_sensitivity proto __cdecl \
	     combo_box: ptr GtkComboBox,
	   sensitivity: GtkSensitivityType

;GtkSensitivityType
gtk_combo_box_get_button_sensitivity proto __cdecl \
	     combo_box: ptr GtkComboBox


;gboolean
gtk_combo_box_get_has_entry proto __cdecl \
	     combo_box: ptr GtkComboBox

;void
gtk_combo_box_set_entry_text_column proto __cdecl \
	     combo_box: ptr GtkComboBox,
	   text_column: gint

;gint
gtk_combo_box_get_entry_text_column proto __cdecl \
	     combo_box: ptr GtkComboBox


;void
gtk_combo_box_set_popup_fixed_width proto __cdecl \
	     combo_box: ptr GtkComboBox,
		 fixed: gboolean

;gboolean
gtk_combo_box_get_popup_fixed_width proto __cdecl \
	     combo_box: ptr GtkComboBox


;void
gtk_combo_box_popup proto __cdecl \
	     combo_box: ptr GtkComboBox

;void
gtk_combo_box_popup_for_device proto __cdecl \
	     combo_box: ptr GtkComboBox,
		device: ptr GdkDevice

;void
gtk_combo_box_popdown proto __cdecl \
	     combo_box: ptr GtkComboBox

;AtkObject*
gtk_combo_box_get_popup_accessible proto __cdecl \
	     combo_box: ptr GtkComboBox


;gint
gtk_combo_box_get_id_column proto __cdecl \
	     combo_box: ptr GtkComboBox

;void
gtk_combo_box_set_id_column proto __cdecl \
	     combo_box: ptr GtkComboBox,
	     id_column: gint

;const
gtk_combo_box_get_active_id proto __cdecl \
	     combo_box: ptr GtkComboBox

;gboolean
gtk_combo_box_set_active_id proto __cdecl \
	     combo_box: ptr GtkComboBox,
	     active_id: ptr gchar


G_END_DECLS

endif
