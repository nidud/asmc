ifndef __GTK_SIZE_GROUP_H__
define __GTK_SIZE_GROUP_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_SIZE_GROUP <gtk_size_group_get_type>
GTK_SIZE_GROUP macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SIZE_GROUP, GtkSizeGroup))>
  endm
GTK_IS_SIZE_GROUP macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SIZE_GROUP))>
  endm

_GtkSizeGroup           struct
parent_instance         GObject <>
_GtkSizeGroup           ends
GtkSizeGroup            typedef _GtkSizeGroup

gtk_size_group_get_type proto
gtk_size_group_new proto :GtkSizeGroupMode
gtk_size_group_set_mode proto :ptr, :GtkSizeGroupMode
gtk_size_group_get_mode proto :ptr
gtk_size_group_add_widget proto :ptr, :ptr
gtk_size_group_remove_widget proto :ptr, :ptr
gtk_size_group_get_widgets proto :ptr

endif
