ifndef __GTKACCESSIBLE_INC
define __GTKACCESSIBLE_INC

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib-object.inc
include gtk/gtktypes.inc
include gtk/gtkenums.inc

define GTK_TYPE_ACCESSIBLE <gtk_accessible_get_type ()>

gtk_accessible_get_accessible_role proto :ptr

gtk_accessible_update_state proto :ptr, :GtkAccessibleState, :vararg
gtk_accessible_update_property proto :ptr, :GtkAccessibleProperty, :vararg
gtk_accessible_update_relation proto :ptr, :GtkAccessibleRelation, :vararg
gtk_accessible_update_state_value proto :ptr, :sdword, :GtkAccessibleState, :GValue
gtk_accessible_update_property_value proto :ptr, :sdword, :GtkAccessibleProperty, :GValue
gtk_accessible_update_relation_value proto :ptr, :sdword, :GtkAccessibleRelation, :GValue

gtk_accessible_reset_state proto :ptr, :GtkAccessibleState
gtk_accessible_reset_property proto :ptr, :GtkAccessibleProperty
gtk_accessible_reset_relation proto :ptr, :GtkAccessibleRelation

gtk_accessible_state_init_value proto :GtkAccessibleState, :ptr
gtk_accessible_property_init_value proto :GtkAccessibleProperty, :ptr
gtk_accessible_relation_init_value proto :GtkAccessibleRelation, :ptr

endif
