ifndef __GTK_ENTRY_H__
define __GTK_ENTRY_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkeditable.inc
include gtk/gtkimcontext.inc
include gtk/gtkentrybuffer.inc
include gtk/gtkentrycompletion.inc
include gtk/gtkimage.inc

define GTK_TYPE_ENTRY <gtk_entry_get_type>
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

_GtkEntry               struct
parent_instance         GtkWidget <>
_GtkEntry               ends
GtkEntry                typedef _GtkEntry


_GtkEntryClass          struct
parent_class            GtkWidgetClass <>
activate                proc :ptr
padding                 gpointer 8 dup(?)
_GtkEntryClass          ends
GtkEntryClass           typedef _GtkEntryClass

gtk_entry_get_type proto
gtk_entry_new proto
gtk_entry_new_with_buffer proto :ptr

gtk_entry_get_buffer proto :ptr
gtk_entry_set_buffer proto :ptr, :ptr

gtk_entry_set_visibility proto :ptr, :gboolean
gtk_entry_get_visibility proto :ptr

gtk_entry_set_invisible_char proto :ptr, :gunichar
gtk_entry_get_invisible_char proto :ptr
gtk_entry_unset_invisible_char proto :ptr

gtk_entry_set_has_frame proto :ptr, :gboolean
gtk_entry_get_has_frame proto :ptr

gtk_entry_set_overwrite_mode proto :ptr, :gboolean
gtk_entry_get_overwrite_mode proto :ptr


gtk_entry_set_max_length proto :ptr, :sdword
gtk_entry_get_max_length proto :ptr
gtk_entry_get_text_length proto :ptr

gtk_entry_set_activates_default proto :ptr, :gboolean
gtk_entry_get_activates_default proto :ptr

gtk_entry_set_alignment proto :ptr, :real4
gtk_entry_get_alignment proto :ptr

gtk_entry_set_completion proto :ptr, :ptr
gtk_entry_get_completion proto :ptr


gtk_entry_set_progress_fraction proto :ptr, :real8
gtk_entry_get_progress_fraction proto :ptr

gtk_entry_set_progress_pulse_step proto :ptr, :real8
gtk_entry_get_progress_pulse_step proto :ptr

gtk_entry_progress_pulse proto :ptr
gtk_entry_get_placeholder_text proto :ptr
gtk_entry_set_placeholder_text proto :ptr, :ptr

gtk_entry_set_icon_from_paintable proto :ptr, :GtkEntryIconPosition, :ptr
gtk_entry_set_icon_from_icon_name proto :ptr, :GtkEntryIconPosition, :ptr
gtk_entry_set_icon_from_gicon proto :ptr, :GtkEntryIconPosition, :ptr
gtk_entry_get_icon_storage_type proto :ptr, :GtkEntryIconPosition
gtk_entry_get_icon_paintable proto :ptr, :GtkEntryIconPosition
gtk_entry_get_icon_name proto :ptr, :GtkEntryIconPosition
gtk_entry_get_icon_gicon proto :ptr, :GtkEntryIconPosition
gtk_entry_set_icon_activatable proto :ptr, :GtkEntryIconPosition, :gboolean
gtk_entry_get_icon_activatable proto :ptr, :GtkEntryIconPosition
gtk_entry_set_icon_sensitive proto :ptr, :GtkEntryIconPosition, :gboolean
gtk_entry_get_icon_sensitive proto :ptr, :GtkEntryIconPosition
gtk_entry_get_icon_at_pos proto :ptr, :sdword, :sdword
gtk_entry_set_icon_tooltip_text proto :ptr, :GtkEntryIconPosition, :ptr
gtk_entry_get_icon_tooltip_text proto :ptr, :GtkEntryIconPosition
gtk_entry_set_icon_tooltip_markup proto :ptr, :GtkEntryIconPosition, :ptr
gtk_entry_get_icon_tooltip_markup proto :ptr, :GtkEntryIconPosition
gtk_entry_set_icon_drag_source proto :ptr, :GtkEntryIconPosition, :ptr, :GdkDragAction
gtk_entry_get_current_icon_drag_source proto :ptr
gtk_entry_get_icon_area proto :ptr, :GtkEntryIconPosition, :ptr

gtk_entry_reset_im_context proto :ptr

gtk_entry_set_input_purpose proto :ptr, :GtkInputPurpose
gtk_entry_get_input_purpose proto :ptr

gtk_entry_set_input_hints proto :ptr, :GtkInputHints
gtk_entry_get_input_hints proto :ptr

gtk_entry_set_attributes proto :ptr, :ptr
gtk_entry_get_attributes proto :ptr

gtk_entry_set_tabs proto :ptr, :ptr

gtk_entry_get_tabs proto :ptr

gtk_entry_grab_focus_without_selecting proto :ptr

gtk_entry_set_extra_menu proto :ptr, :ptr
gtk_entry_get_extra_menu proto :ptr

endif
