ifndef __GTK_CONSTRAINT_GUIDE_H__
define __GTK_CONSTRAINT_GUIDE_H__

include gtk/gtktypes.inc
include gtk/gtkenums.inc
include gtk/gtktypebuiltins.inc

define GTK_TYPE_CONSTRAINT_GUIDE <gtk_constraint_guide_get_type>

gtk_constraint_guide_new proto

gtk_constraint_guide_set_min_size proto :ptr, :sdword, :sdword
gtk_constraint_guide_get_min_size proto :ptr, :ptr, :ptr
gtk_constraint_guide_set_nat_size proto :ptr, :sdword, :sdword
gtk_constraint_guide_get_nat_size proto :ptr, :ptr, :ptr
gtk_constraint_guide_set_max_size proto :ptr, :sdword, :sdword
gtk_constraint_guide_get_max_size proto :ptr, :ptr, :ptr

gtk_constraint_guide_get_strength proto :ptr
gtk_constraint_guide_set_strength proto :ptr, :GtkConstraintStrength

gtk_constraint_guide_set_name proto :ptr, :ptr
gtk_constraint_guide_get_name proto :ptr

endif
