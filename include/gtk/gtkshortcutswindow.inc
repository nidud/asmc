ifndef __GTK_SHORTCUTS_WINDOW_H__
define __GTK_SHORTCUTS_WINDOW_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwindow.inc

define GTK_TYPE_SHORTCUTS_WINDOW <gtk_shortcuts_window_get_type>
GTK_SHORTCUTS_WINDOW macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SHORTCUTS_WINDOW, GtkShortcutsWindow))>
  endm
GTK_IS_SHORTCUTS_WINDOW macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SHORTCUTS_WINDOW))>
  endm

;GtkShortcutsWindow      typedef _GtkShortcutsWindow

gtk_shortcuts_window_get_type proto

endif
