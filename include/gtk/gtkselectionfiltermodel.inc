ifndef __GTK_SELECTION_FILTER_MODEL_H__
define __GTK_SELECTION_FILTER_MODEL_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gio/gio.inc
include gtk/gtkselectionmodel.inc

define GTK_TYPE_SELECTION_FILTER_MODEL <gtk_selection_filter_model_get_type>

gtk_selection_filter_model_new proto :ptr
gtk_selection_filter_model_set_model proto :ptr, :ptr
gtk_selection_filter_model_get_model proto :ptr

endif
