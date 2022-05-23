ifndef __GTK_LABEL_H__
define __GTK_LABEL_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_LABEL <gtk_label_get_type>
GTK_LABEL macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_LABEL, GtkLabel))>
  endm
GTK_IS_LABEL macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_LABEL))>
  endm

;GtkLabel		 typedef _GtkLabel

gtk_label_get_type proto
gtk_label_new proto :ptr
gtk_label_new_with_mnemonic proto :ptr
gtk_label_set_text proto :ptr, :ptr
gtk_label_get_text proto :ptr
gtk_label_set_attributes proto :ptr, :ptr
gtk_label_get_attributes proto :ptr
gtk_label_set_label proto :ptr, :ptr
gtk_label_get_label proto :ptr
gtk_label_set_markup proto :ptr, :ptr
gtk_label_set_use_markup proto :ptr, :gboolean
gtk_label_get_use_markup proto :ptr
gtk_label_set_use_underline proto :ptr, :gboolean
gtk_label_get_use_underline proto :ptr

gtk_label_set_markup_with_mnemonic proto :ptr, :ptr
gtk_label_get_mnemonic_keyval proto :ptr
gtk_label_set_mnemonic_widget proto :ptr, :ptr
gtk_label_get_mnemonic_widget proto :ptr
gtk_label_set_text_with_mnemonic proto :ptr, :ptr
gtk_label_set_justify proto :ptr, :GtkJustification
gtk_label_get_justify proto :ptr
gtk_label_set_ellipsize proto :ptr, :PangoEllipsizeMode
gtk_label_get_ellipsize proto :ptr
gtk_label_set_width_chars proto :ptr, :sdword
gtk_label_get_width_chars proto :ptr
gtk_label_set_max_width_chars proto :ptr, :sdword
gtk_label_get_max_width_chars proto :ptr
gtk_label_set_lines proto :ptr, :sdword
gtk_label_get_lines proto :ptr
gtk_label_set_wrap proto :ptr, :gboolean
gtk_label_get_wrap proto :ptr
gtk_label_set_wrap_mode proto :ptr, :PangoWrapMode
gtk_label_get_wrap_mode proto :ptr
gtk_label_set_natural_wrap_mode proto :ptr, :GtkNaturalWrapMode
gtk_label_get_natural_wrap_mode proto :ptr
gtk_label_set_selectable proto :ptr, :gboolean
gtk_label_get_selectable proto :ptr
gtk_label_select_region proto :ptr, :sdword, :sdword
gtk_label_get_selection_bounds proto :ptr, :ptr, :ptr

gtk_label_get_layout proto :ptr
gtk_label_get_layout_offsets proto :ptr, :ptr, :ptr

gtk_label_set_single_line_mode proto :ptr, :gboolean
gtk_label_get_single_line_mode proto :ptr

gtk_label_get_current_uri proto :ptr
gtk_label_set_xalign proto :ptr, :real4
gtk_label_get_xalign proto :ptr
gtk_label_set_yalign proto :ptr, :real4
gtk_label_get_yalign proto :ptr
gtk_label_set_extra_menu proto :ptr, :ptr
gtk_label_get_extra_menu proto :ptr

endif
