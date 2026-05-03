ifndef __GTK_IM_CONTEXT_H__
define __GTK_IM_CONTEXT_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_IM_CONTEXT <gtk_im_context_get_type ()>
GTK_IM_CONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_IM_CONTEXT, GtkIMContext))>
  endm
GTK_IM_CONTEXT_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_IM_CONTEXT, GtkIMContextClass))>
  endm
GTK_IS_IM_CONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_IM_CONTEXT))>
  endm
GTK_IS_IM_CONTEXT_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_IM_CONTEXT))>
  endm
GTK_IM_CONTEXT_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_IM_CONTEXT, GtkIMContextClass))>
  endm


GtkIMContext            struct
parent_instance         GObject <>
GtkIMContext            ends

GtkIMContextClass       struct
parent_class            GObjectClass <>
preedit_start           proc :ptr
preedit_end             proc :ptr
preedit_changed         proc :ptr
commit                  proc :ptr, :ptr
retrieve_surrounding    proc :ptr
delete_surrounding      proc :ptr, :sdword, :sdword
set_client_widget       proc :ptr, :ptr
get_preedit_string      proc :ptr, :ptr, :ptr, :ptr
filter_keypress         proc :ptr, :ptr
focus_in                proc :ptr
focus_out               proc :ptr
reset                   proc :ptr
set_cursor_location     proc :ptr, :ptr
set_use_preedit         proc :ptr, :gboolean
set_surrounding         proc :ptr, :ptr, :sdword, :sdword
get_surrounding         proc :ptr, :ptr, :ptr
set_surrounding_with_selection proc :ptr, :ptr, :sdword, :sdword, :sdword
get_surrounding_with_selection proc :ptr, :ptr, :ptr, :ptr
_gtk_reserved1          proc
_gtk_reserved2          proc
_gtk_reserved3          proc
_gtk_reserved4          proc
_gtk_reserved5          proc
GtkIMContextClass       ends

gtk_im_context_get_type proto
gtk_im_context_set_client_widget proto :ptr, :ptr
gtk_im_context_get_preedit_string proto :ptr, :ptr, :ptr, :ptr
gtk_im_context_filter_keypress proto :ptr, :ptr
gtk_im_context_filter_key proto :ptr, :gboolean, :ptr, :ptr, :guint32, :guint, :GdkModifierType, :sdword
gtk_im_context_focus_in proto :ptr
gtk_im_context_focus_out proto :ptr
gtk_im_context_reset proto :ptr
gtk_im_context_set_cursor_location proto :ptr, :ptr
gtk_im_context_set_use_preedit proto :ptr, :gboolean
gtk_im_context_set_surrounding proto :ptr, :ptr, :sdword, :sdword
gtk_im_context_get_surrounding proto :ptr, :ptr, :ptr
gtk_im_context_set_surrounding_with_selection proto :ptr, :ptr, :sdword, :sdword, :sdword
gtk_im_context_get_surrounding_with_selection proto :ptr, :ptr, :ptr, :ptr
gtk_im_context_delete_surrounding proto :ptr, :sdword, :sdword

endif
