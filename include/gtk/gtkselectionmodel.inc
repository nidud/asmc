ifndef __GTK_SELECTION_MODEL_H__
define __GTK_SELECTION_MODEL_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktypes.inc

define GTK_TYPE_SELECTION_MODEL <gtk_selection_model_get_type ()>

_GtkSelectionModelInterface struct
g_iface                 GTypeInterface <>
is_selected             proc :ptr, :guint
get_selection_in_range  proc :ptr, :guint, :guint
select_item             proc :ptr, :guint, :gboolean
unselect_item           proc :ptr, :guint
select_range            proc :ptr, :guint, :guint, :gboolean
unselect_range          proc :ptr, :guint, :guint
select_all              proc :ptr
unselect_all            proc :ptr
set_selection           proc :ptr, :ptr, :ptr
_GtkSelectionModelInterface ends
GtkSelectionModelInterface typedef _GtkSelectionModelInterface

gtk_selection_model_is_selected proto :ptr, :guint
gtk_selection_model_get_selection proto :ptr
gtk_selection_model_get_selection_in_range proto :ptr, :guint, :guint

gtk_selection_model_select_item proto :ptr, :guint, :gboolean
gtk_selection_model_unselect_item proto :ptr, :guint
gtk_selection_model_select_range proto :ptr, :guint, :guint, :gboolean
gtk_selection_model_unselect_range proto :ptr, :guint, :guint
gtk_selection_model_select_all proto :ptr
gtk_selection_model_unselect_all proto :ptr
gtk_selection_model_set_selection proto :ptr, :ptr, :ptr

gtk_selection_model_selection_changed proto :ptr, :guint, :guint

endif
