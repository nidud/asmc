ifndef __GTK_NO_SELECTION_H__
define __GTK_NO_SELECTION_H__

include gtk/gtktypes.inc

define GTK_TYPE_NO_SELECTION <gtk_no_selection_get_type ()>

gtk_no_selection_new proto :ptr
gtk_no_selection_get_model proto :ptr
gtk_no_selection_set_model proto :ptr, :ptr

endif
