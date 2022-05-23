ifndef __GTK_PASSWORD_ENTRY_H__
define __GTK_PASSWORD_ENTRY_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkentry.inc

define GTK_TYPE_PASSWORD_ENTRY <gtk_password_entry_get_type>
GTK_PASSWORD_ENTRY macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_PASSWORD_ENTRY, GtkPasswordEntry))>
  endm
GTK_IS_PASSWORD_ENTRY macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_PASSWORD_ENTRY))>
  endm

;GtkPasswordEntry        typedef _GtkPasswordEntry
;GtkPasswordEntryClass   typedef _GtkPasswordEntryClass

gtk_password_entry_get_type proto
gtk_password_entry_new proto
gtk_password_entry_set_show_peek_icon proto :ptr, :gboolean
gtk_password_entry_get_show_peek_icon proto :ptr
gtk_password_entry_set_extra_menu proto :ptr, :ptr
gtk_password_entry_get_extra_menu proto :ptr

endif
