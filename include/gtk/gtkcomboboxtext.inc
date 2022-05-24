ifndef __GTK_COMBO_BOX_TEXT_H__
define __GTK_COMBO_BOX_TEXT_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcombobox.inc

define GTK_TYPE_COMBO_BOX_TEXT <gtk_combo_box_text_get_type ()>
GTK_COMBO_BOX_TEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_COMBO_BOX_TEXT, GtkComboBoxText))>
  endm
GTK_IS_COMBO_BOX_TEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_COMBO_BOX_TEXT))>
  endm

;GtkComboBoxText         typedef _GtkComboBoxText

gtk_combo_box_text_get_type proto
gtk_combo_box_text_new proto
gtk_combo_box_text_new_with_entry proto
gtk_combo_box_text_append_text proto :ptr, :ptr
gtk_combo_box_text_insert_text proto :ptr, :sdword, :ptr
gtk_combo_box_text_prepend_text proto :ptr, :ptr
gtk_combo_box_text_remove proto :ptr, :sdword
gtk_combo_box_text_remove_all proto :ptr
gtk_combo_box_text_get_active_text proto :ptr
gtk_combo_box_text_insert proto :ptr, :sdword, :ptr, :ptr
gtk_combo_box_text_append proto :ptr, :ptr, :ptr
gtk_combo_box_text_prepend proto :ptr, :ptr, :ptr

endif
