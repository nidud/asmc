ifndef __GTK_WINDOW_GROUP_H__
define __GTK_WINDOW_GROUP_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtkwindow.inc

define GTK_TYPE_WINDOW_GROUP <gtk_window_group_get_type>
GTK_WINDOW_GROUP macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GTK_TYPE_WINDOW_GROUP, GtkWindowGroup))>
  endm
GTK_WINDOW_GROUP_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_WINDOW_GROUP, GtkWindowGroupClass))>
  endm
GTK_IS_WINDOW_GROUP macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GTK_TYPE_WINDOW_GROUP))>
  endm
GTK_IS_WINDOW_GROUP_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_WINDOW_GROUP))>
  endm
GTK_WINDOW_GROUP_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_WINDOW_GROUP, GtkWindowGroupClass))>
  endm

_GtkWindowGroup         struct
parent_instance         GObject <>
priv                    ptr GtkWindowGroupPrivate ?
_GtkWindowGroup         ends

_GtkWindowGroupClass    struct
parent_class            GObjectClass <>
_gtk_reserved1          proc
_gtk_reserved2          proc
_gtk_reserved3          proc
_gtk_reserved4          proc
_GtkWindowGroupClass    ends

gtk_window_group_get_type proto
gtk_window_group_new proto
gtk_window_group_add_window proto :ptr, :ptr
gtk_window_group_remove_window proto :ptr, :ptr
gtk_window_group_list_windows proto :ptr

endif
