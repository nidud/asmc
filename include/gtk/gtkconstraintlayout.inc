ifndef __GTK_CONSTRAINT_LAYOUT_H__
define __GTK_CONSTRAINT_LAYOUT_H__

include gtk/gtklayoutmanager.inc
include gtk/gtkconstraint.inc
include gtk/gtkconstraintguide.inc

define GTK_TYPE_CONSTRAINT_LAYOUT <gtk_constraint_layout_get_type ()>
define GTK_TYPE_CONSTRAINT_LAYOUT_CHILD <gtk_constraint_layout_child_get_type ()>
define GTK_CONSTRAINT_VFL_PARSER_ERROR <gtk_constraint_vfl_parser_error_quark ()>

gtk_constraint_vfl_parser_error_quark proto

gtk_constraint_layout_new proto

gtk_constraint_layout_add_constraint proto :ptr, :ptr
gtk_constraint_layout_remove_constraint proto :ptr, :ptr

gtk_constraint_layout_add_guide proto :ptr, :ptr
gtk_constraint_layout_remove_guide proto :ptr, :ptr
gtk_constraint_layout_remove_all_constraints proto :ptr

gtk_constraint_layout_add_constraints_from_description proto :ptr, :ptr, :gsize, :sdword, :sdword, :ptr, :ptr, :vararg
gtk_constraint_layout_add_constraints_from_descriptionv proto :ptr, :ptr, :gsize, :sdword, :sdword, :ptr, :ptr

gtk_constraint_layout_observe_constraints proto :ptr
gtk_constraint_layout_observe_guides proto :ptr

endif
