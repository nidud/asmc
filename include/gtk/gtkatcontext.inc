ifndef __GTKATCONTEXT_INC
define __GTKATCONTEXT_INC

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktypes.inc
include gtk/gtkenums.inc
include gtk/gtkaccessible.inc

define GTK_TYPE_AT_CONTEXT (gtk_at_context_get_type())

gtk_at_context_get_accessible proto :ptr
gtk_at_context_get_accessible_role proto :ptr
gtk_at_context_create proto :GtkAccessibleRole, :ptr, :ptr

endif
