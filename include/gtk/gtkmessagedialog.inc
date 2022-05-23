ifndef __GTK_MESSAGE_DIALOG_H__
define __GTK_MESSAGE_DIALOG_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkdialog.inc
include gtk/gtkenums.inc

define GTK_TYPE_MESSAGE_DIALOG <gtk_message_dialog_get_type>
GTK_MESSAGE_DIALOG macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_MESSAGE_DIALOG, GtkMessageDialog))>
  endm
GTK_IS_MESSAGE_DIALOG macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_MESSAGE_DIALOG))>
  endm

;GtkMessageDialogClass   typedef _GtkMessageDialogClass

_GtkMessageDialog       struct
parent_instance         GtkDialog <>
_GtkMessageDialog       ends
GtkMessageDialog        typedef _GtkMessageDialog

.enum GtkButtonsType {
  GTK_BUTTONS_NONE,
  GTK_BUTTONS_OK,
  GTK_BUTTONS_CLOSE,
  GTK_BUTTONS_CANCEL,
  GTK_BUTTONS_YES_NO,
  GTK_BUTTONS_OK_CANCEL
}

gtk_message_dialog_get_type proto
gtk_message_dialog_new proto :ptr, :GtkDialogFlags, :GtkMessageType, :GtkButtonsType, :ptr, :vararg
gtk_message_dialog_new_with_markup proto :ptr, :GtkDialogFlags, :GtkMessageType, :GtkButtonsType, :ptr, :vararg
gtk_message_dialog_set_markup proto :ptr, :ptr
gtk_message_dialog_format_secondary_text proto :ptr, :ptr, :vararg
gtk_message_dialog_format_secondary_markup proto :ptr, :ptr, :vararg
gtk_message_dialog_get_message_area proto :ptr

endif
