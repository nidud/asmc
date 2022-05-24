ifndef __GTK_DIALOG_H__
define __GTK_DIALOG_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwindow.inc

.enum GtkDialogFlags {
  GTK_DIALOG_MODAL               = 1 shl 0,
  GTK_DIALOG_DESTROY_WITH_PARENT = 1 shl 1,
  GTK_DIALOG_USE_HEADER_BAR      = 1 shl 2
}

.enum GtkResponseType {
  GTK_RESPONSE_NONE         = -1,
  GTK_RESPONSE_REJECT       = -2,
  GTK_RESPONSE_ACCEPT       = -3,
  GTK_RESPONSE_DELETE_EVENT = -4,
  GTK_RESPONSE_OK           = -5,
  GTK_RESPONSE_CANCEL       = -6,
  GTK_RESPONSE_CLOSE        = -7,
  GTK_RESPONSE_YES          = -8,
  GTK_RESPONSE_NO           = -9,
  GTK_RESPONSE_APPLY        = -10,
  GTK_RESPONSE_HELP         = -11
}

define GTK_TYPE_DIALOG <gtk_dialog_get_type ()>
GTK_DIALOG macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_DIALOG, GtkDialog))>
  endm
GTK_DIALOG_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_DIALOG, GtkDialogClass))>
  endm
GTK_IS_DIALOG macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_DIALOG))>
  endm
GTK_IS_DIALOG_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_DIALOG))>
  endm
GTK_DIALOG_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_DIALOG, GtkDialogClass))>
  endm


_GtkDialog              struct
parent_instance         GtkWindow <>
_GtkDialog              ends
GtkDialog               typedef _GtkDialog

_GtkDialogClass         struct
parent_class            GtkWindowClass <>
response                proc :ptr, :sdword
close                   proc :ptr
padding                 gpointer 8 dup(?)
_GtkDialogClass         ends
GtkDialogClass          typedef _GtkDialogClass


gtk_dialog_get_type proto
gtk_dialog_new proto
gtk_dialog_new_with_buttons proto :ptr, :ptr, :GtkDialogFlags, :ptr, :vararg
gtk_dialog_add_action_widget proto :ptr, :ptr, :sdword
gtk_dialog_add_button proto :ptr, :ptr, :sdword
gtk_dialog_add_buttons proto :ptr, :ptr, :vararg
gtk_dialog_set_response_sensitive proto :ptr, :sdword, :gboolean
gtk_dialog_set_default_response proto :ptr, :sdword
gtk_dialog_get_widget_for_response proto :ptr, :sdword
gtk_dialog_get_response_for_widget proto :ptr, :ptr
gtk_dialog_response proto :ptr, :sdword
gtk_dialog_get_content_area proto :ptr
gtk_dialog_get_header_bar proto :ptr

endif
