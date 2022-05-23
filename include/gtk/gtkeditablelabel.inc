ifndef __GTK_EDITABLE_LABEL_H__
define __GTK_EDITABLE_LABEL_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_EDITABLE_LABEL <gtk_editable_label_get_type>

gtk_editable_label_new proto :ptr
gtk_editable_label_get_editing proto :ptr
gtk_editable_label_start_editing proto :ptr
gtk_editable_label_stop_editing proto :ptr, :gboolean

endif
