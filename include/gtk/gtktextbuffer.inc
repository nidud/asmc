ifndef __GTK_TEXT_BUFFER_H__
define __GTK_TEXT_BUFFER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtktexttagtable.inc
include gtk/gtktextiter.inc
include gtk/gtktextmark.inc
include gtk/gtktextchild.inc

define GTK_TYPE_TEXT_BUFFER <gtk_text_buffer_get_type>
GTK_TEXT_BUFFER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TEXT_BUFFER, GtkTextBuffer))>
  endm
GTK_TEXT_BUFFER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TEXT_BUFFER, GtkTextBufferClass))>
  endm
GTK_IS_TEXT_BUFFER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TEXT_BUFFER))>
  endm
GTK_IS_TEXT_BUFFER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TEXT_BUFFER))>
  endm
GTK_TEXT_BUFFER_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TEXT_BUFFER, GtkTextBufferClass))>
  endm

;GtkTextBufferPrivate    typedef _GtkTextBufferPrivate

_GtkTextBuffer          struct
parent_instance         GObject <>
priv                    ptr GtkTextBufferPrivate ?
_GtkTextBuffer          ends
GtkTextBuffer           typedef _GtkTextBuffer

_GtkTextBufferClass     struct
parent_class            GObjectClass <>
insert_text             proc :ptr, :ptr, :ptr, :sdword
insert_paintable        proc :ptr, :ptr, :ptr
insert_child_anchor     proc :ptr, :ptr, :ptr
delete_range            proc :ptr, :ptr, :ptr
changed                 proc :ptr
modified_changed        proc :ptr
mark_set                proc :ptr, :ptr, :ptr
mark_deleted            proc :ptr, :ptr
apply_tag               proc :ptr, :ptr, :ptr, :ptr
remove_tag              proc :ptr, :ptr, :ptr, :ptr
begin_user_action       proc :ptr
end_user_action         proc :ptr
paste_done              proc :ptr, :ptr
undo                    proc :ptr
redo                    proc :ptr
_gtk_reserved1          proc
_gtk_reserved2          proc
_gtk_reserved3          proc
_gtk_reserved4          proc
_GtkTextBufferClass     ends
GtkTextBufferClass      typedef _GtkTextBufferClass

gtk_text_buffer_get_type proto
gtk_text_buffer_new proto :ptr
gtk_text_buffer_get_line_count proto :ptr
gtk_text_buffer_get_char_count proto :ptr
gtk_text_buffer_get_tag_table proto :ptr
gtk_text_buffer_set_text proto :ptr, :ptr, :sdword
gtk_text_buffer_insert proto :ptr, :ptr, :ptr, :sdword
gtk_text_buffer_insert_at_cursor proto :ptr, :ptr, :sdword
gtk_text_buffer_insert_interactive proto :ptr, :ptr, :ptr, :sdword, :gboolean
gtk_text_buffer_insert_interactive_at_cursor proto :ptr, :ptr, :sdword, :gboolean
gtk_text_buffer_insert_range proto :ptr, :ptr, :ptr, :ptr
gtk_text_buffer_insert_range_interactive proto :ptr, :ptr, :ptr, :ptr, :gboolean
gtk_text_buffer_insert_with_tags proto :ptr, :ptr, :ptr, :sdword, :ptr, :vararg
gtk_text_buffer_insert_with_tags_by_name proto :ptr, :ptr, :ptr, :sdword, :ptr, :vararg
gtk_text_buffer_insert_markup proto :ptr, :ptr, :ptr, :sdword
gtk_text_buffer_delete proto :ptr, :ptr, :ptr
gtk_text_buffer_delete_interactive proto :ptr, :ptr, :ptr, :gboolean
gtk_text_buffer_backspace proto :ptr, :ptr, :gboolean, :gboolean
gtk_text_buffer_get_text proto :ptr, :ptr, :ptr, :gboolean
gtk_text_buffer_get_slice proto :ptr, :ptr, :ptr, :gboolean
gtk_text_buffer_insert_paintable proto :ptr, :ptr, :ptr
gtk_text_buffer_insert_child_anchor proto :ptr, :ptr, :ptr
gtk_text_buffer_create_child_anchor proto :ptr, :ptr
gtk_text_buffer_add_mark proto :ptr, :ptr, :ptr
gtk_text_buffer_create_mark proto :ptr, :ptr, :ptr, :gboolean
gtk_text_buffer_move_mark proto :ptr, :ptr, :ptr
gtk_text_buffer_delete_mark proto :ptr, :ptr
gtk_text_buffer_get_mark proto :ptr, :ptr
gtk_text_buffer_move_mark_by_name proto :ptr, :ptr, :ptr
gtk_text_buffer_delete_mark_by_name proto :ptr, :ptr
gtk_text_buffer_get_insert proto :ptr
gtk_text_buffer_get_selection_bound proto :ptr
gtk_text_buffer_place_cursor proto :ptr, :ptr
gtk_text_buffer_select_range proto :ptr, :ptr, :ptr
gtk_text_buffer_apply_tag proto :ptr, :ptr, :ptr, :ptr
gtk_text_buffer_remove_tag proto :ptr, :ptr, :ptr, :ptr
gtk_text_buffer_apply_tag_by_name proto :ptr, :ptr, :ptr, :ptr
gtk_text_buffer_remove_tag_by_name proto :ptr, :ptr, :ptr, :ptr
gtk_text_buffer_remove_all_tags proto :ptr, :ptr, :ptr
gtk_text_buffer_create_tag proto :ptr, :ptr, :ptr, :vararg
gtk_text_buffer_get_iter_at_line_offset proto :ptr, :ptr, :sdword, :sdword
gtk_text_buffer_get_iter_at_line_index proto :ptr, :ptr, :sdword, :sdword
gtk_text_buffer_get_iter_at_offset proto :ptr, :ptr, :sdword
gtk_text_buffer_get_iter_at_line proto :ptr, :ptr, :sdword
gtk_text_buffer_get_start_iter proto :ptr, :ptr
gtk_text_buffer_get_end_iter proto :ptr, :ptr
gtk_text_buffer_get_bounds proto :ptr, :ptr, :ptr
gtk_text_buffer_get_iter_at_mark proto :ptr, :ptr, :ptr
gtk_text_buffer_get_iter_at_child_anchor proto :ptr, :ptr, :ptr
gtk_text_buffer_get_modified proto :ptr
gtk_text_buffer_set_modified proto :ptr, :gboolean
gtk_text_buffer_get_has_selection proto :ptr
gtk_text_buffer_add_selection_clipboard proto :ptr, :ptr
gtk_text_buffer_remove_selection_clipboard proto :ptr, :ptr
gtk_text_buffer_cut_clipboard proto :ptr, :ptr, :gboolean
gtk_text_buffer_copy_clipboard proto :ptr, :ptr
gtk_text_buffer_paste_clipboard proto :ptr, :ptr, :ptr, :gboolean
gtk_text_buffer_get_selection_bounds proto :ptr, :ptr, :ptr
gtk_text_buffer_delete_selection proto :ptr, :gboolean, :gboolean
gtk_text_buffer_get_selection_content proto :ptr
gtk_text_buffer_get_can_undo proto :ptr
gtk_text_buffer_get_can_redo proto :ptr
gtk_text_buffer_get_enable_undo proto :ptr
gtk_text_buffer_set_enable_undo proto :ptr, :gboolean
gtk_text_buffer_get_max_undo_levels proto :ptr
gtk_text_buffer_set_max_undo_levels proto :ptr, :guint
gtk_text_buffer_undo proto :ptr
gtk_text_buffer_redo proto :ptr
gtk_text_buffer_begin_irreversible_action proto :ptr
gtk_text_buffer_end_irreversible_action proto :ptr
gtk_text_buffer_begin_user_action proto :ptr
gtk_text_buffer_end_user_action proto :ptr

endif
