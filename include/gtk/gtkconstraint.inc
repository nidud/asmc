ifndef __GTK_CONSTRAINT_H__
define __GTK_CONSTRAINT_H__

include gtk/gtktypes.inc
include gtk/gtkenums.inc

define GTK_TYPE_CONSTRAINT_TARGET <gtk_constraint_target_get_type ()>
define GTK_TYPE_CONSTRAINT <gtk_constraint_get_type ()>

gtk_constraint_new proto :gpointer, :GtkConstraintAttribute, :GtkConstraintRelation, :gpointer, :GtkConstraintAttribute, :real8, :real8, :sdword
gtk_constraint_new_constant proto :gpointer, :GtkConstraintAttribute, :GtkConstraintRelation, :real8, :sdword

gtk_constraint_get_target proto :ptr
gtk_constraint_get_target_attribute proto :ptr
gtk_constraint_get_source proto :ptr
gtk_constraint_get_source_attribute proto :ptr
gtk_constraint_get_relation proto :ptr
gtk_constraint_get_multiplier proto :ptr
gtk_constraint_get_constant proto :ptr
gtk_constraint_get_strength proto :ptr

gtk_constraint_is_required proto :ptr
gtk_constraint_is_attached proto :ptr
gtk_constraint_is_constant proto :ptr

endif
