ifndef __GTK_BUILDER_SCOPE_H__
define __GTK_BUILDER_SCOPE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktypes.inc

define GTK_TYPE_BUILDER_SCOPE <gtk_builder_scope_get_type>

.enum GtkBuilderClosureFlags {
  GTK_BUILDER_CLOSURE_SWAPPED = (1 shl 0)
  }

_GtkBuilderScopeInterface struct
g_iface                 GTypeInterface <>
get_type_from_name      proc :ptr, :ptr, :ptr
get_type_from_function  proc :ptr, :ptr, :ptr
create_closure          proc :ptr, :ptr, :ptr, :GtkBuilderClosureFlags, :ptr, :ptr
_GtkBuilderScopeInterface ends

_GtkBuilderCScopeClass  struct
parent_class            GObjectClass <>
_GtkBuilderCScopeClass  ends

define GTK_TYPE_BUILDER_CSCOPE <gtk_builder_cscope_get_type>

gtk_builder_cscope_new proto
gtk_builder_cscope_add_callback_symbol proto :ptr, :ptr, :GCallback
gtk_builder_cscope_add_callback_symbols proto :ptr, :ptr, :GCallback, :vararg
gtk_builder_cscope_lookup_callback_symbol proto :ptr, :ptr

endif
