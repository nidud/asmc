ifndef __GTK_SHORTCUTS_GROUP_H__
define __GTK_SHORTCUTS_GROUP_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc

define GTK_TYPE_SHORTCUTS_GROUP <gtk_shortcuts_group_get_type ()>
GTK_SHORTCUTS_GROUP macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SHORTCUTS_GROUP, GtkShortcutsGroup))>
  endm
GTK_IS_SHORTCUTS_GROUP macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SHORTCUTS_GROUP))>
  endm

gtk_shortcuts_group_get_type proto

endif
