

ifndef __GTK_TEXT_VIEW_H__
__GTK_TEXT_VIEW_H__ equ 1

if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcontainer.inc
;include gtk/gtkimcontext.inc
include gtk/gtktextbuffer.inc
;include gtk/gtkmenu.inc

GTK_TYPE_TEXT_VIEW equ <gtk_text_view_get_type>
GTK_TEXT_VIEW macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TEXT_VIEW, GtkTextView))>
	endm
GTK_TEXT_VIEW_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TEXT_VIEW, GtkTextViewClass))>
	endm
GTK_IS_TEXT_VIEW macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TEXT_VIEW))>
	endm
GTK_IS_TEXT_VIEW_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TEXT_VIEW))>
	endm
GTK_TEXT_VIEW_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TEXT_VIEW, GtkTextViewClass))>
	endm

.enum GtkTextWindowType {
    GTK_TEXT_WINDOW_PRIVATE,
    GTK_TEXT_WINDOW_WIDGET,
    GTK_TEXT_WINDOW_TEXT,
    GTK_TEXT_WINDOW_LEFT,
    GTK_TEXT_WINDOW_RIGHT,
    GTK_TEXT_WINDOW_TOP,
    GTK_TEXT_WINDOW_BOTTOM
}

.enum GtkTextViewLayer {
    GTK_TEXT_VIEW_LAYER_BELOW,
    GTK_TEXT_VIEW_LAYER_ABOVE
}

.enum GtkTextExtendSelection {
    GTK_TEXT_EXTEND_SELECTION_WORD,
    GTK_TEXT_EXTEND_SELECTION_LINE
}

GTK_TEXT_VIEW_PRIORITY_VALIDATE equ (GDK_PRIORITY_REDRAW + 5)

GtkTextView		STRUC
parent_instance		GtkContainer <>
priv			ptr_t ?
GtkTextView		ENDS

GtkTextViewClass	STRUC
parent_class		GtkContainerClass <>
populate_popup		proc :ptr GtkTextView, :ptr GtkWidget
move_cursor		proc :ptr GtkTextView, :GtkMovementStep, :gint, :gboolean
set_anchor		proc :ptr GtkTextView
insert_at_cursor	proc :ptr GtkTextView, :ptr gchar
delete_from_cursor	proc :ptr GtkTextView, :GtkDeleteType, :gint
backspace		proc :ptr GtkTextView
cut_clipboard		proc :ptr GtkTextView
copy_clipboard		proc :ptr GtkTextView
paste_clipboard		proc :ptr GtkTextView
toggle_overwrite	proc :ptr GtkTextView
create_buffer		proc :ptr GtkTextView
draw_layer		proc :ptr GtkTextView, :GtkTextViewLayer, :ptr cairo_t
extend_selection	proc :ptr GtkTextView, :gboolean, :GtkTextExtendSelection, :ptr, :ptr, :ptr
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
GtkTextViewClass	ENDS

;GType
gtk_text_view_get_type proto __cdecl
;GtkWidget
gtk_text_view_new proto __cdecl
;GtkWidget
gtk_text_view_new_with_buffer proto __cdecl \
		buffer: ptr GtkTextBuffer

;void
gtk_text_view_set_buffer proto __cdecl \
	     text_view: ptr GtkTextView,
		buffer: ptr GtkTextBuffer

;GtkTextBuffer
gtk_text_view_get_buffer proto __cdecl \
	     text_view: ptr GtkTextView

;gboolean
gtk_text_view_scroll_to_iter proto __cdecl \
	     text_view: ptr GtkTextView,
		  iter: ptr GtkTextIter,
	 within_margin: gdouble,
	     use_align: gboolean,
		xalign: gdouble,
		yalign: gdouble

;void
gtk_text_view_scroll_to_mark proto __cdecl \
	     text_view: ptr GtkTextView,
		  mark: ptr GtkTextMark,
	 within_margin: gdouble,
	     use_align: gboolean,
		xalign: gdouble,
		yalign: gdouble

;void
gtk_text_view_scroll_mark_onscreen proto __cdecl \
	     text_view: ptr GtkTextView,
		  mark: ptr GtkTextMark

;gboolean
gtk_text_view_move_mark_onscreen proto __cdecl \
	     text_view: ptr GtkTextView,
		  mark: ptr GtkTextMark

;gboolean
gtk_text_view_place_cursor_onscreen proto __cdecl \
	     text_view: ptr GtkTextView


;void
gtk_text_view_get_visible_rect proto __cdecl \
	     text_view: ptr GtkTextView,
	  visible_rect: ptr GdkRectangle

;void
gtk_text_view_set_cursor_visible proto __cdecl \
	     text_view: ptr GtkTextView,
	       setting: gboolean

;gboolean
gtk_text_view_get_cursor_visible proto __cdecl \
	     text_view: ptr GtkTextView


;void
gtk_text_view_get_cursor_locations proto __cdecl \
	     text_view: ptr GtkTextView,
		  iter: ptr GtkTextIter,
		strong: ptr GdkRectangle,
		  weak: ptr GdkRectangle

;void
gtk_text_view_get_iter_location proto __cdecl \
	     text_view: ptr GtkTextView,
		  iter: ptr GtkTextIter,
	      location: ptr GdkRectangle

;void
gtk_text_view_get_iter_at_location proto __cdecl \
	     text_view: ptr GtkTextView,
		  iter: ptr GtkTextIter,
		     x: gint,
		     y: gint

;void
gtk_text_view_get_iter_at_position proto __cdecl \
	     text_view: ptr GtkTextView,
		  iter: ptr GtkTextIter,
	      trailing: ptr gint,
		     x: gint,
		     y: gint

;void
gtk_text_view_get_line_yrange proto __cdecl \
	     text_view: ptr GtkTextView,
		  iter: ptr GtkTextIter,
		     y: ptr gint,
		height: ptr gint


;void
gtk_text_view_get_line_at_y proto __cdecl \
	     text_view: ptr GtkTextView,
	   target_iter: ptr GtkTextIter,
		     y: gint,
	      line_top: ptr gint


;void
gtk_text_view_buffer_to_window_coords proto __cdecl \
	     text_view: ptr GtkTextView,
		   win: GtkTextWindowType,
	      buffer_x: gint,
	      buffer_y: gint,
	      window_x: ptr gint,
	      window_y: ptr gint

;void
gtk_text_view_window_to_buffer_coords proto __cdecl \
	     text_view: ptr GtkTextView,
		   win: GtkTextWindowType,
	      window_x: gint,
	      window_y: gint,
	      buffer_x: ptr gint,
	      buffer_y: ptr gint


;GtkAdjustment*
gtk_text_view_get_hadjustment proto __cdecl \
	     text_view: ptr GtkTextView

;GtkAdjustment*
gtk_text_view_get_vadjustment proto __cdecl \
	     text_view: ptr GtkTextView


;GdkWindow*
gtk_text_view_get_window proto __cdecl \
	     text_view: ptr GtkTextView,
		   win: GtkTextWindowType

;GtkTextWindowType
gtk_text_view_get_window_type proto __cdecl \
	     text_view: ptr GtkTextView,
		window: ptr GdkWindow


;void
gtk_text_view_set_border_window_size proto __cdecl \
	     text_view: ptr GtkTextView,
		  type: GtkTextWindowType,
		  size: gint

;gint
gtk_text_view_get_border_window_size proto __cdecl \
	     text_view: ptr GtkTextView,
		  type: GtkTextWindowType


;gboolean
gtk_text_view_forward_display_line proto __cdecl \
	     text_view: ptr GtkTextView,
		  iter: ptr GtkTextIter

;gboolean
gtk_text_view_backward_display_line proto __cdecl \
	     text_view: ptr GtkTextView,
		  iter: ptr GtkTextIter

;gboolean
gtk_text_view_forward_display_line_end proto __cdecl \
	     text_view: ptr GtkTextView,
		  iter: ptr GtkTextIter

;gboolean
gtk_text_view_backward_display_line_start proto __cdecl \
	     text_view: ptr GtkTextView,
		  iter: ptr GtkTextIter

;gboolean
gtk_text_view_starts_display_line proto __cdecl \
	     text_view: ptr GtkTextView,
		  iter: ptr GtkTextIter

;gboolean
gtk_text_view_move_visually proto __cdecl \
	     text_view: ptr GtkTextView,
		  iter: ptr GtkTextIter,
		 count: gint


;gboolean
gtk_text_view_im_context_filter_keypress proto __cdecl \
	     text_view: ptr GtkTextView,
		 event: ptr GdkEventKey

;void
gtk_text_view_reset_im_context proto __cdecl \
	     text_view: ptr GtkTextView


;void
gtk_text_view_add_child_at_anchor proto __cdecl \
	     text_view: ptr GtkTextView,
		 child: ptr GtkWidget,
		anchor: ptr GtkTextChildAnchor


;void
gtk_text_view_add_child_in_window proto __cdecl \
	     text_view: ptr GtkTextView,
		 child: ptr GtkWidget,
	  which_window: GtkTextWindowType,
		  xpos: gint,
		  ypos: gint


;void
gtk_text_view_move_child proto __cdecl \
	     text_view: ptr GtkTextView,
		 child: ptr GtkWidget,
		  xpos: gint,
		  ypos: gint



;void
gtk_text_view_set_wrap_mode proto __cdecl \
	     text_view: ptr GtkTextView,
	     wrap_mode: GtkWrapMode

;GtkWrapMode
gtk_text_view_get_wrap_mode proto __cdecl \
	     text_view: ptr GtkTextView

;void
gtk_text_view_set_editable proto __cdecl \
	     text_view: ptr GtkTextView,
	       setting: gboolean

;gboolean
gtk_text_view_get_editable proto __cdecl \
	     text_view: ptr GtkTextView

;void
gtk_text_view_set_overwrite proto __cdecl \
	     text_view: ptr GtkTextView,
	     overwrite: gboolean

;gboolean
gtk_text_view_get_overwrite proto __cdecl \
	     text_view: ptr GtkTextView

;void
gtk_text_view_set_accepts_tab proto __cdecl \
	     text_view: ptr GtkTextView,
	   accepts_tab: gboolean

;gboolean
gtk_text_view_get_accepts_tab proto __cdecl \
	     text_view: ptr GtkTextView

;void
gtk_text_view_set_pixels_above_lines proto __cdecl \
	     text_view: ptr GtkTextView,
    pixels_above_lines: gint

;gint
gtk_text_view_get_pixels_above_lines proto __cdecl \
	     text_view: ptr GtkTextView

;void
gtk_text_view_set_pixels_below_lines proto __cdecl \
	     text_view: ptr GtkTextView,
    pixels_below_lines: gint

;gint
gtk_text_view_get_pixels_below_lines proto __cdecl \
	     text_view: ptr GtkTextView

;void
gtk_text_view_set_pixels_inside_wrap proto __cdecl \
	     text_view: ptr GtkTextView,
    pixels_inside_wrap: gint

;gint
gtk_text_view_get_pixels_inside_wrap proto __cdecl \
	     text_view: ptr GtkTextView

;void
gtk_text_view_set_justification proto __cdecl \
	     text_view: ptr GtkTextView,
	 justification: GtkJustification

;GtkJustification
gtk_text_view_get_justification proto __cdecl \
	     text_view: ptr GtkTextView

;void
gtk_text_view_set_left_margin proto __cdecl \
	     text_view: ptr GtkTextView,
	   left_margin: gint

;gint
gtk_text_view_get_left_margin proto __cdecl \
	     text_view: ptr GtkTextView

;void
gtk_text_view_set_right_margin proto __cdecl \
	     text_view: ptr GtkTextView,
	  right_margin: gint

;gint
gtk_text_view_get_right_margin proto __cdecl \
	     text_view: ptr GtkTextView

;void
gtk_text_view_set_top_margin proto __cdecl \
	     text_view: ptr GtkTextView,
	    top_margin: gint

;gint
gtk_text_view_get_top_margin proto __cdecl \
	     text_view: ptr GtkTextView

;void
gtk_text_view_set_bottom_margin proto __cdecl \
	     text_view: ptr GtkTextView,
	 bottom_margin: gint

;gint
gtk_text_view_get_bottom_margin proto __cdecl \
	     text_view: ptr GtkTextView

;void
gtk_text_view_set_indent proto __cdecl \
	     text_view: ptr GtkTextView,
		indent: gint

;gint
gtk_text_view_get_indent proto __cdecl \
	     text_view: ptr GtkTextView

;void
gtk_text_view_set_tabs proto __cdecl \
	     text_view: ptr GtkTextView,
		  tabs: ptr PangoTabArray

;PangoTabArray*
gtk_text_view_get_tabs proto __cdecl \
	     text_view: ptr GtkTextView


;GtkTextAttributes*
gtk_text_view_get_default_attributes proto __cdecl \
	     text_view: ptr GtkTextView


;void
gtk_text_view_set_input_purpose proto __cdecl \
	     text_view: ptr GtkTextView,
	       purpose: GtkInputPurpose

;GtkInputPurpose
gtk_text_view_get_input_purpose proto __cdecl \
	     text_view: ptr GtkTextView


;void
gtk_text_view_set_input_hints proto __cdecl \
	     text_view: ptr GtkTextView,
		 hints: GtkInputHints

;GtkInputHints
gtk_text_view_get_input_hints proto __cdecl \
	     text_view: ptr GtkTextView


;void
gtk_text_view_set_monospace proto __cdecl \
	     text_view: ptr GtkTextView,
	     monospace: gboolean

;gboolean
gtk_text_view_get_monospace proto __cdecl \
	     text_view: ptr GtkTextView

endif
