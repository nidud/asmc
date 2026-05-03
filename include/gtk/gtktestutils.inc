ifndef __GTK_TEST_UTILS_H__
define __GTK_TEST_UTILS_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtkspinbutton.inc

gtk_test_init proto :ptr, :ptr, :vararg
gtk_test_register_all_types proto
gtk_test_list_all_types proto :ptr
gtk_test_widget_wait_for_draw proto :ptr

endif
