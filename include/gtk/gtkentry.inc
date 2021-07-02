ifndef __GTK_ENTRY_H__
__GTK_ENTRY_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkeditable.inc
include gtk/gtkimcontext.inc
include gtk/gtkmenu.inc
include gtk/gtkentrybuffer.inc
include gtk/gtkentrycompletion.inc
include gtk/gtkimage.inc
include gtk/gtkselection.inc

G_BEGIN_DECLS

GTK_TYPE_ENTRY equ <gtk_entry_get_type>
GTK_ENTRY macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ENTRY, GtkEntry))>
	endm
GTK_ENTRY_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ENTRY, GtkEntryClass))>
	endm
GTK_IS_ENTRY macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ENTRY))>
	endm
GTK_IS_ENTRY_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ENTRY))>
	endm
GTK_ENTRY_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ENTRY, GtkEntryClass))>
	endm

.enum GtkEntryIconPosition {
  GTK_ENTRY_ICON_PRIMARY,
  GTK_ENTRY_ICON_SECONDARY
}

GtkEntry		STRUC
parent_instance		GtkWidget <>
priv			ptr_t ?
GtkEntry		ENDS

GtkEntryClass		STRUC
parent_class		GtkWidgetClass <>
populate_popup		proc :ptr GtkEntry, :ptr GtkWidget
activate		proc :ptr GtkEntry
move_cursor		proc :ptr GtkEntry, :GtkMovementStep, :gint, :gboolean
insert_at_cursor	proc :ptr GtkEntry, :ptr gchar
delete_from_cursor	proc :ptr GtkEntry, :GtkDeleteType, :gint
backspace		proc :ptr GtkEntry
cut_clipboard		proc :ptr GtkEntry
copy_clipboard		proc :ptr GtkEntry
paste_clipboard		proc :ptr GtkEntry
toggle_overwrite	proc :ptr GtkEntry
get_text_area_size	proc :ptr GtkEntry, :ptr gint, :ptr gint, :ptr gint, :ptr gint
get_frame_size		proc :ptr GtkEntry, :ptr gint, :ptr gint, :ptr gint, :ptr gint
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
_gtk_reserved6		proc
_gtk_reserved7		proc
GtkEntryClass		ENDS

;GType
gtk_entry_get_type proto __cdecl
;GtkWidget*
gtk_entry_new proto __cdecl
;GtkWidget*
gtk_entry_new_with_buffer proto __cdecl \
		buffer: ptr GtkEntryBuffer


;GtkEntryBuffer*
gtk_entry_get_buffer proto __cdecl \
		 entry: ptr GtkEntry

;void
gtk_entry_set_buffer proto __cdecl \
		 entry: ptr GtkEntry,
		buffer: ptr GtkEntryBuffer


;void
gtk_entry_get_text_area proto __cdecl \
		 entry: ptr GtkEntry,
	     text_area: ptr GdkRectangle


;void
gtk_entry_set_visibility proto __cdecl \
		 entry: ptr GtkEntry,
	       visible: gboolean

;gboolean
gtk_entry_get_visibility proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_set_invisible_char proto __cdecl \
		 entry: ptr GtkEntry,
		   _ch: gunichar

;gunichar
gtk_entry_get_invisible_char proto __cdecl \
		 entry: ptr GtkEntry

;void
gtk_entry_unset_invisible_char proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_set_has_frame proto __cdecl \
		 entry: ptr GtkEntry,
	       setting: gboolean

;gboolean
gtk_entry_get_has_frame proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_set_inner_border proto __cdecl \
		 entry: ptr GtkEntry,
		border: ptr GtkBorder

;const
gtk_entry_get_inner_border proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_set_overwrite_mode proto __cdecl \
		 entry: ptr GtkEntry,
	     overwrite: gboolean

;gboolean
gtk_entry_get_overwrite_mode proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_set_max_length proto __cdecl \
		 entry: ptr GtkEntry,
		   max: gint

;gint
gtk_entry_get_max_length proto __cdecl \
		 entry: ptr GtkEntry

;guint16
gtk_entry_get_text_length proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_set_activates_default proto __cdecl \
		 entry: ptr GtkEntry,
	       setting: gboolean

;gboolean
gtk_entry_get_activates_default proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_set_width_chars proto __cdecl \
		 entry: ptr GtkEntry,
	       n_chars: gint

;gint
gtk_entry_get_width_chars proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_set_max_width_chars proto __cdecl \
		 entry: ptr GtkEntry,
	       n_chars: gint

;gint
gtk_entry_get_max_width_chars proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_set_text proto __cdecl \
		 entry: ptr GtkEntry,
		  text: ptr gchar

;const
gtk_entry_get_text proto __cdecl \
		 entry: ptr GtkEntry


;PangoLayout*
gtk_entry_get_layout proto __cdecl \
		 entry: ptr GtkEntry

;void
gtk_entry_get_layout_offsets proto __cdecl \
		 entry: ptr GtkEntry,
		     x: ptr gint,
		     y: ptr gint

;void
gtk_entry_set_alignment proto __cdecl \
		 entry: ptr GtkEntry,
		xalign: gfloat

;gfloat
gtk_entry_get_alignment proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_set_completion proto __cdecl \
		 entry: ptr GtkEntry,
	    completion: ptr GtkEntryCompletion

;GtkEntryCompletion
gtk_entry_get_completion proto __cdecl \
		 entry: ptr GtkEntry


;gint
gtk_entry_layout_index_to_text_index proto __cdecl \
		 entry: ptr GtkEntry,
	  layout_index: gint

;gint
gtk_entry_text_index_to_layout_index proto __cdecl \
		 entry: ptr GtkEntry,
	    text_index: gint


;void
gtk_entry_set_cursor_hadjustment proto __cdecl \
		 entry: ptr GtkEntry,
	    adjustment: ptr GtkAdjustment

;GtkAdjustment*
gtk_entry_get_cursor_hadjustment proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_set_progress_fraction proto __cdecl \
		 entry: ptr GtkEntry,
	      fraction: gdouble

;gdouble
gtk_entry_get_progress_fraction proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_set_progress_pulse_step proto __cdecl \
		 entry: ptr GtkEntry,
	      fraction: gdouble

;gdouble
gtk_entry_get_progress_pulse_step proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_progress_pulse proto __cdecl \
		 entry: ptr GtkEntry

;const
gtk_entry_get_placeholder_text proto __cdecl \
		 entry: ptr GtkEntry

;void
gtk_entry_set_placeholder_text proto __cdecl \
		 entry: ptr GtkEntry,
		  text: ptr gchar

;void
gtk_entry_set_icon_from_pixbuf proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition,
		pixbuf: ptr GdkPixbuf

;void
gtk_entry_set_icon_from_stock proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition,
	      stock_id: ptr gchar

;void
gtk_entry_set_icon_from_icon_name proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition,
	     icon_name: ptr gchar

;void
gtk_entry_set_icon_from_gicon proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition,
		  icon: ptr GIcon

;GtkImageType
gtk_entry_get_icon_storage_type proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition

;GdkPixbuf*
gtk_entry_get_icon_pixbuf proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition

;const
gtk_entry_get_icon_stock proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition

;const
gtk_entry_get_icon_name proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition

;GIcon*
gtk_entry_get_icon_gicon proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition

;void
gtk_entry_set_icon_activatable proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition,
	   activatable: gboolean

;gboolean
gtk_entry_get_icon_activatable proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition

;void
gtk_entry_set_icon_sensitive proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition,
	     sensitive: gboolean

;gboolean
gtk_entry_get_icon_sensitive proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition

;gint
gtk_entry_get_icon_at_pos proto __cdecl \
		 entry: ptr GtkEntry,
		     x: gint,
		     y: gint

;void
gtk_entry_set_icon_tooltip_text proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition,
	       tooltip: ptr gchar

;gchar
gtk_entry_get_icon_tooltip_text proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition

;void
gtk_entry_set_icon_tooltip_markup proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition,
	       tooltip: ptr gchar

;gchar
gtk_entry_get_icon_tooltip_markup proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition

;void
gtk_entry_set_icon_drag_source proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition,
	   target_list: ptr GtkTargetList,
	       actions: GdkDragAction

;gint
gtk_entry_get_current_icon_drag_source proto __cdecl \
		 entry: ptr GtkEntry

;void
gtk_entry_get_icon_area proto __cdecl \
		 entry: ptr GtkEntry,
	      icon_pos: GtkEntryIconPosition,
	     icon_area: ptr GdkRectangle


;gboolean
gtk_entry_im_context_filter_keypress proto __cdecl \
		 entry: ptr GtkEntry,
		 event: ptr GdkEventKey

;void
gtk_entry_reset_im_context proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_set_input_purpose proto __cdecl \
		 entry: ptr GtkEntry,
	       purpose: GtkInputPurpose

;GtkInputPurpose
gtk_entry_get_input_purpose proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_set_input_hints proto __cdecl \
		 entry: ptr GtkEntry,
		 hints: GtkInputHints

;GtkInputHints
gtk_entry_get_input_hints proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_set_attributes proto __cdecl \
		 entry: ptr GtkEntry,
		 attrs: ptr PangoAttrList

;PangoAttrList
gtk_entry_get_attributes proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_set_tabs proto __cdecl \
		 entry: ptr GtkEntry,
		  tabs: ptr PangoTabArray


;PangoTabArray
gtk_entry_get_tabs proto __cdecl \
		 entry: ptr GtkEntry


;void
gtk_entry_grab_focus_without_selecting proto __cdecl \
		 entry: ptr GtkEntry


G_END_DECLS

endif
