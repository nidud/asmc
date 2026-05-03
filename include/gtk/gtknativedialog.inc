ifndef __GTK_NATIVE_DIALOG_H__
define __GTK_NATIVE_DIALOG_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwindow.inc

define GTK_TYPE_NATIVE_DIALOG <gtk_native_dialog_get_type ()>

GtkNativeDialogClass    struct
parent_class            GObjectClass <>
response                proc :ptr, :sdword
show                    proc :ptr
hide                    proc :ptr
_gtk_reserved1          proc
_gtk_reserved2          proc
_gtk_reserved3          proc
_gtk_reserved4          proc
GtkNativeDialogClass    ends

gtk_native_dialog_show proto :ptr
gtk_native_dialog_hide proto :ptr
gtk_native_dialog_destroy proto :ptr
gtk_native_dialog_get_visible proto :ptr
gtk_native_dialog_set_modal proto :ptr, :gboolean
gtk_native_dialog_get_modal proto :ptr
gtk_native_dialog_set_title proto :ptr, :ptr
gtk_native_dialog_get_title proto :ptr
gtk_native_dialog_set_transient_for proto :ptr, :ptr
gtk_native_dialog_get_transient_for proto :ptr

endif
