ifndef __GTK_STACK_SIDEBAR_H__
define __GTK_STACK_SIDEBAR_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkstack.inc

define GTK_TYPE_STACK_SIDEBAR <gtk_stack_sidebar_get_type ()>
GTK_STACK_SIDEBAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_STACK_SIDEBAR, GtkStackSidebar))>
  endm
GTK_IS_STACK_SIDEBAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_STACK_SIDEBAR))>
  endm

gtk_stack_sidebar_get_type proto
gtk_stack_sidebar_new proto
gtk_stack_sidebar_set_stack proto :ptr, :ptr
gtk_stack_sidebar_get_stack proto :ptr

endif
