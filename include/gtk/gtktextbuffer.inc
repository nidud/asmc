ifndef __GTK_TEXT_BUFFER_H__
__GTK_TEXT_BUFFER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
;include gtk/gtkclipboard.inc
;include gtk/gtktexttagtable.inc
;include gtk/gtktextiter.inc
;include gtk/gtktextmark.inc
;include gtk/gtktextchild.inc

.enum GtkTextBufferTargetInfo {
    GTK_TEXT_BUFFER_TARGET_INFO_BUFFER_CONTENTS = -1
    GTK_TEXT_BUFFER_TARGET_INFO_RICH_TEXT	= -2
    GTK_TEXT_BUFFER_TARGET_INFO_TEXT		= -3
}

GTK_TYPE_TEXT_BUFFER  equ <gtk_text_buffer_get_type>
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

GtkTextBuffer		STRUC
parent_instance		GObject <>
priv			ptr_t ?
GtkTextBuffer		ENDS

GtkTextBufferClass	STRUC
parent_class		GObjectClass <>
insert_text		proc :ptr GtkTextBuffer, :ptr GtkTextIter, :ptr gchar, :gint
insert_pixbuf		proc :ptr GtkTextBuffer, :ptr GtkTextIter, :ptr GdkPixbuf
insert_child_anchor	proc :ptr GtkTextBuffer, :ptr GtkTextIter, :ptr GtkTextChildAnchor
delete_range		proc :ptr GtkTextBuffer, :ptr GtkTextIter, :ptr GtkTextIter
changed			proc :ptr GtkTextBuffer
modified_changed	proc :ptr GtkTextBuffer
mark_set		proc :ptr GtkTextBuffer, :ptr GtkTextIter, :ptr GtkTextMark
mark_deleted		proc :ptr GtkTextBuffer, :ptr GtkTextMark
apply_tag		proc :ptr GtkTextBuffer, :ptr GtkTextTag, :ptr GtkTextIter, :ptr GtkTextIter
remove_tag		proc :ptr GtkTextBuffer, :ptr GtkTextTag, :ptr GtkTextIter, :ptr GtkTextIter
begin_user_action	proc :ptr GtkTextBuffer
end_user_action		proc :ptr GtkTextBuffer
paste_done		proc :ptr GtkTextBuffer, :ptr GtkClipboard
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkTextBufferClass	ENDS

;GType
gtk_text_buffer_get_type proto __cdecl



;GtkTextBuffer
gtk_text_buffer_new proto __cdecl \
		 table: ptr GtkTextTagTable

;gint
gtk_text_buffer_get_line_count proto __cdecl \
		buffer: ptr GtkTextBuffer

;gint
gtk_text_buffer_get_char_count proto __cdecl \
		buffer: ptr GtkTextBuffer



;GtkTextTagTable*
gtk_text_buffer_get_tag_table proto __cdecl \
		buffer: ptr GtkTextBuffer


;void
gtk_text_buffer_set_text proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  text: ptr gchar,
		   len: gint


;void
gtk_text_buffer_insert proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter,
		  text: ptr gchar,
		   len: gint

;void
gtk_text_buffer_insert_at_cursor proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  text: ptr gchar,
		   len: gint


;gboolean
gtk_text_buffer_insert_interactive proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter,
		  text: ptr gchar,
		   len: gint,
      default_editable: gboolean

;gboolean
gtk_text_buffer_insert_interactive_at_cursor proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  text: ptr gchar,
		   len: gint,
      default_editable: gboolean


;void
gtk_text_buffer_insert_range proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter,
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter

;gboolean
gtk_text_buffer_insert_range_interactive proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter,
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter,
      default_editable: gboolean


;void
gtk_text_buffer_insert_with_tags proto _CDecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter,
		  text: ptr gchar,
		   len: gint,
	     first_tag: ptr GtkTextTag,
		      : vararg


;void
gtk_text_buffer_insert_with_tags_by_name proto _CDecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter,
		  text: ptr gchar,
		   len: gint,
	first_tag_name: ptr gchar,
		      : vararg

;void
gtk_text_buffer_insert_markup proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter,
		markup: ptr gchar,
		   len: gint


;void
gtk_text_buffer_delete proto __cdecl \
		buffer: ptr GtkTextBuffer,
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter

;gboolean
gtk_text_buffer_delete_interactive proto __cdecl \
		buffer: ptr GtkTextBuffer,
	    start_iter: ptr GtkTextIter,
	      end_iter: ptr GtkTextIter,
      default_editable: gboolean

;gboolean
gtk_text_buffer_backspace proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter,
	   interactive: gboolean,
      default_editable: gboolean


;gchar
gtk_text_buffer_get_text proto __cdecl \
		buffer: ptr GtkTextBuffer,
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter,
  include_hidden_chars: gboolean


;gchar
gtk_text_buffer_get_slice proto __cdecl \
		buffer: ptr GtkTextBuffer,
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter,
  include_hidden_chars: gboolean


;void
gtk_text_buffer_insert_pixbuf proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter,
		pixbuf: ptr GdkPixbuf


;void
gtk_text_buffer_insert_child_anchor proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter,
		anchor: ptr GtkTextChildAnchor


;GtkTextChildAnchor
gtk_text_buffer_create_child_anchor proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter


;void
gtk_text_buffer_add_mark proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  mark: ptr GtkTextMark,
		 where: ptr GtkTextIter

;GtkTextMark
gtk_text_buffer_create_mark proto __cdecl \
		buffer: ptr GtkTextBuffer,
	     mark_name: ptr gchar,
		 where: ptr GtkTextIter,
	  left_gravity: gboolean

;void
gtk_text_buffer_move_mark proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  mark: ptr GtkTextMark,
		 where: ptr GtkTextIter

;void
gtk_text_buffer_delete_mark proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  mark: ptr GtkTextMark

;GtkTextMark*
gtk_text_buffer_get_mark proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  name: ptr gchar


;void
gtk_text_buffer_move_mark_by_name proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  name: ptr gchar,
		 where: ptr GtkTextIter

;void
gtk_text_buffer_delete_mark_by_name proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  name: ptr gchar


;GtkTextMark*
gtk_text_buffer_get_insert proto __cdecl \
		buffer: ptr GtkTextBuffer

;GtkTextMark*
gtk_text_buffer_get_selection_bound proto __cdecl \
		buffer: ptr GtkTextBuffer


;void
gtk_text_buffer_place_cursor proto __cdecl \
		buffer: ptr GtkTextBuffer,
		 where: ptr GtkTextIter

;void
gtk_text_buffer_select_range proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  _ins: ptr GtkTextIter,
		_bound: ptr GtkTextIter


;void
gtk_text_buffer_apply_tag proto __cdecl \
		buffer: ptr GtkTextBuffer,
		   tag: ptr GtkTextTag,
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter

;void
gtk_text_buffer_remove_tag proto __cdecl \
		buffer: ptr GtkTextBuffer,
		   tag: ptr GtkTextTag,
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter

;void
gtk_text_buffer_apply_tag_by_name proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  name: ptr gchar,
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter

;void
gtk_text_buffer_remove_tag_by_name proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  name: ptr gchar,
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter

;void
gtk_text_buffer_remove_all_tags proto __cdecl \
		buffer: ptr GtkTextBuffer,
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter



;GtkTextTag
gtk_text_buffer_create_tag proto _CDecl \
		buffer: ptr GtkTextBuffer,
	      tag_name: ptr gchar,
   first_property_name: ptr gchar,
		      : vararg


;void
gtk_text_buffer_get_iter_at_line_offset proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter,
	   line_number: gint,
	   char_offset: gint

;void
gtk_text_buffer_get_iter_at_line_index proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter,
	   line_number: gint,
	    byte_index: gint

;void
gtk_text_buffer_get_iter_at_offset proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter,
	   char_offset: gint

;void
gtk_text_buffer_get_iter_at_line proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter,
	   line_number: gint

;void
gtk_text_buffer_get_start_iter proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter

;void
gtk_text_buffer_get_end_iter proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter

;void
gtk_text_buffer_get_bounds proto __cdecl \
		buffer: ptr GtkTextBuffer,
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter

;void
gtk_text_buffer_get_iter_at_mark proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter,
		  mark: ptr GtkTextMark


;void
gtk_text_buffer_get_iter_at_child_anchor proto __cdecl \
		buffer: ptr GtkTextBuffer,
		  iter: ptr GtkTextIter,
		anchor: ptr GtkTextChildAnchor


;gboolean
gtk_text_buffer_get_modified proto __cdecl \
		buffer: ptr GtkTextBuffer

;void
gtk_text_buffer_set_modified proto __cdecl \
		buffer: ptr GtkTextBuffer,
	       setting: gboolean


;gboolean
gtk_text_buffer_get_has_selection proto __cdecl \
		buffer: ptr GtkTextBuffer


;void
gtk_text_buffer_add_selection_clipboard proto __cdecl \
		buffer: ptr GtkTextBuffer,
	     clipboard: ptr GtkClipboard

;void
gtk_text_buffer_remove_selection_clipboard proto __cdecl \
		buffer: ptr GtkTextBuffer,
	     clipboard: ptr GtkClipboard


;void
gtk_text_buffer_cut_clipboard proto __cdecl \
		buffer: ptr GtkTextBuffer,
	     clipboard: ptr GtkClipboard,
      default_editable: gboolean

;void
gtk_text_buffer_copy_clipboard proto __cdecl \
		buffer: ptr GtkTextBuffer,
	     clipboard: ptr GtkClipboard

;void
gtk_text_buffer_paste_clipboard proto __cdecl \
		buffer: ptr GtkTextBuffer,
	     clipboard: ptr GtkClipboard,
     override_location: ptr GtkTextIter,
      default_editable: gboolean


;gboolean
gtk_text_buffer_get_selection_bounds proto __cdecl \
		buffer: ptr GtkTextBuffer,
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter

;gboolean
gtk_text_buffer_delete_selection proto __cdecl \
		buffer: ptr GtkTextBuffer,
	   interactive: gboolean,
      default_editable: gboolean


;void
gtk_text_buffer_begin_user_action proto __cdecl \
		buffer: ptr GtkTextBuffer

;void
gtk_text_buffer_end_user_action proto __cdecl \
		buffer: ptr GtkTextBuffer


;GtkTargetList
gtk_text_buffer_get_copy_target_list proto __cdecl \
		buffer: ptr GtkTextBuffer

;GtkTargetList
gtk_text_buffer_get_paste_target_list proto __cdecl \
		buffer: ptr GtkTextBuffer


;void
_gtk_text_buffer_spew proto __cdecl \
		buffer: ptr GtkTextBuffer


;GtkTextBTree*
_gtk_text_buffer_get_btree proto __cdecl \
		buffer: ptr GtkTextBuffer

;PangoLogAttr*
_gtk_text_buffer_get_line_log_attrs proto __cdecl \
		buffer: ptr GtkTextBuffer,
      anywhere_in_line: ptr GtkTextIter,
	      char_len: ptr gint

;void
_gtk_text_buffer_notify_will_remove_tag proto __cdecl \
		buffer: ptr GtkTextBuffer,
		   tag: ptr GtkTextTag

;void
_gtk_text_buffer_get_text_before proto __cdecl \
		buffer: ptr GtkTextBuffer,
	 boundary_type: AtkTextBoundary,
	      position: ptr GtkTextIter,
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter

;void
_gtk_text_buffer_get_text_at proto __cdecl \
		buffer: ptr GtkTextBuffer,
	 boundary_type: AtkTextBoundary,
	      position: ptr GtkTextIter,
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter

;void
_gtk_text_buffer_get_text_after proto __cdecl \
		buffer: ptr GtkTextBuffer,
	 boundary_type: AtkTextBoundary,
	      position: ptr GtkTextIter,
		 start: ptr GtkTextIter,
		  _end: ptr GtkTextIter

endif
