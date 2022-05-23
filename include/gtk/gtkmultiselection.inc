ifndef __GTK_MULTI_SELECTION_H__
define __GTK_MULTI_SELECTION_H__

include gtk/gtktypes.inc
include gtk/gtkselectionmodel.inc

define GTK_TYPE_MULTI_SELECTION <gtk_multi_selection_get_type>

gtk_multi_selection_new proto :ptr
gtk_multi_selection_get_model proto :ptr
gtk_multi_selection_set_model proto :ptr, :ptr

endif
