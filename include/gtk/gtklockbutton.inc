ifndef __GTK_LOCK_BUTTON_H__
define __GTK_LOCK_BUTTON_H__

include gtk/gtkbutton.inc
include gio/gio.inc

define GTK_TYPE_LOCK_BUTTON <gtk_lock_button_get_type>
GTK_LOCK_BUTTON macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_LOCK_BUTTON, GtkLockButton))>
  endm
GTK_IS_LOCK_BUTTON macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_LOCK_BUTTON))>
  endm

;GtkLockButton           typedef _GtkLockButton

gtk_lock_button_get_type proto
gtk_lock_button_new proto :ptr
gtk_lock_button_get_permission proto :ptr
gtk_lock_button_set_permission proto :ptr, :ptr

endif
