ifndef __GTK_STACK_SWITCHER_H__
define __GTK_STACK_SWITCHER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkstack.inc

define GTK_TYPE_STACK_SWITCHER <gtk_stack_switcher_get_type ()>
GTK_STACK_SWITCHER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_STACK_SWITCHER, GtkStackSwitcher))>
  endm
GTK_IS_STACK_SWITCHER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_STACK_SWITCHER))>
  endm

;GtkStackSwitcher        typedef _GtkStackSwitcher

gtk_stack_switcher_get_type proto
gtk_stack_switcher_new proto
gtk_stack_switcher_set_stack proto :ptr, :ptr
gtk_stack_switcher_get_stack proto :ptr

endif
