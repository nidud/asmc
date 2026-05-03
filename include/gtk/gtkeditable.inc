ifndef __GTK_EDITABLE_H__
define __GTK_EDITABLE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_EDITABLE <gtk_editable_get_type ()>
GTK_EDITABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_EDITABLE, GtkEditable))>
  endm
GTK_IS_EDITABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_EDITABLE))>
  endm
GTK_EDITABLE_GET_IFACE macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), GTK_TYPE_EDITABLE, GtkEditableInterface))>
  endm

GtkEditableInterface    struct
base_iface              GTypeInterface <>
insert_text             proc :ptr, :ptr, :sdword, :ptr
delete_text             proc :ptr, :sdword, :sdword
changed                 proc :ptr
get_text                proc :ptr
do_insert_text          proc :ptr, :ptr, :sdword, :ptr
do_delete_text          proc :ptr, :sdword, :sdword
get_selection_bounds    proc :ptr, :ptr, :ptr
set_selection_bounds    proc :ptr, :sdword, :sdword
get_delegate            proc :ptr
GtkEditableInterface    ends

gtk_editable_get_type proto
gtk_editable_get_text proto :ptr
gtk_editable_set_text proto :ptr, :ptr
gtk_editable_get_chars proto :ptr, :sdword, :sdword
gtk_editable_insert_text proto :ptr, :ptr, :sdword, :ptr
gtk_editable_delete_text proto :ptr, :sdword, :sdword
gtk_editable_get_selection_bounds proto :ptr, :ptr, :ptr
gtk_editable_delete_selection proto :ptr
gtk_editable_select_region proto :ptr, :sdword, :sdword
gtk_editable_set_position proto :ptr, :sdword
gtk_editable_get_position proto :ptr
gtk_editable_get_editable proto :ptr
gtk_editable_set_editable proto :ptr, :gboolean
gtk_editable_get_alignment proto :ptr
gtk_editable_set_alignment proto :ptr, :real4
gtk_editable_get_width_chars proto :ptr
gtk_editable_set_width_chars proto :ptr, :sdword
gtk_editable_get_max_width_chars proto :ptr
gtk_editable_set_max_width_chars proto :ptr, :sdword
gtk_editable_get_enable_undo proto :ptr
gtk_editable_set_enable_undo proto :ptr, :gboolean

.enum GtkEditableProperties {
  GTK_EDITABLE_PROP_TEXT,
  GTK_EDITABLE_PROP_CURSOR_POSITION,
  GTK_EDITABLE_PROP_SELECTION_BOUND,
  GTK_EDITABLE_PROP_EDITABLE,
  GTK_EDITABLE_PROP_WIDTH_CHARS,
  GTK_EDITABLE_PROP_MAX_WIDTH_CHARS,
  GTK_EDITABLE_PROP_XALIGN,
  GTK_EDITABLE_PROP_ENABLE_UNDO,
  GTK_EDITABLE_NUM_PROPERTIES
}

gtk_editable_install_properties proto :ptr, :guint
gtk_editable_get_delegate proto :ptr
gtk_editable_init_delegate proto :ptr
gtk_editable_finish_delegate proto :ptr
gtk_editable_delegate_set_property proto :ptr, :guint, :ptr, :ptr
gtk_editable_delegate_get_property proto :ptr, :guint, :ptr, :ptr

endif
