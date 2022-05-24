ifndef __GTK_COMBO_BOX_H__
define __GTK_COMBO_BOX_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtktreemodel.inc
include gtk/gtktreeview.inc

define GTK_TYPE_COMBO_BOX <gtk_combo_box_get_type ()>
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

_GtkComboBox            struct
parent_instance         GtkWidget <>
_GtkComboBox            ends
GtkComboBox             typedef _GtkComboBox


_GtkComboBoxClass       struct
parent_class            GtkWidgetClass <>
changed                 proc :ptr
format_entry_text       proc :ptr, :ptr
activate                proc :ptr
padding                 gpointer 7 dup(?)
_GtkComboBoxClass       ends
GtkComboBoxClass        typedef _GtkComboBoxClass

gtk_combo_box_get_type proto
gtk_combo_box_new proto
gtk_combo_box_new_with_entry proto
gtk_combo_box_new_with_model proto :ptr
gtk_combo_box_new_with_model_and_entry proto :ptr

gtk_combo_box_get_active proto :ptr
gtk_combo_box_set_active proto :ptr, :sdword
gtk_combo_box_get_active_iter proto :ptr, :ptr
gtk_combo_box_set_active_iter proto :ptr, :ptr

gtk_combo_box_set_model proto :ptr, :ptr
gtk_combo_box_get_model proto :ptr

gtk_combo_box_get_row_separator_func proto :ptr
gtk_combo_box_set_row_separator_func proto :ptr, :GtkTreeViewRowSeparatorFunc, :gpointer, :GDestroyNotify

gtk_combo_box_set_button_sensitivity proto :ptr, :GtkSensitivityType
gtk_combo_box_get_button_sensitivity proto :ptr

gtk_combo_box_get_has_entry proto :ptr
gtk_combo_box_set_entry_text_column proto :ptr, :sdword
gtk_combo_box_get_entry_text_column proto :ptr

gtk_combo_box_set_popup_fixed_width proto :ptr, :gboolean
gtk_combo_box_get_popup_fixed_width proto :ptr

gtk_combo_box_popup proto :ptr
gtk_combo_box_popup_for_device proto :ptr, :ptr
gtk_combo_box_popdown proto :ptr

gtk_combo_box_get_id_column proto :ptr
gtk_combo_box_set_id_column proto :ptr, :sdword
gtk_combo_box_get_active_id proto :ptr
gtk_combo_box_set_active_id proto :ptr, :ptr

gtk_combo_box_set_child proto :ptr, :ptr
gtk_combo_box_get_child proto :ptr

endif
