ifndef __GTK_BUILDABLE_H__
define __GTK_BUILDABLE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbuilder.inc

define GTK_TYPE_BUILDABLE            <gtk_buildable_get_type>
GTK_BUILDABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_BUILDABLE, GtkBuildable))>
  endm
GTK_IS_BUILDABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_BUILDABLE))>
  endm
GTK_BUILDABLE_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTK_TYPE_BUILDABLE, GtkBuildableIface))>
  endm

;GtkBuildable            typedef _GtkBuildable
;GtkBuildableParseContext typedef _GtkBuildableParseContext

_GtkBuildableParser     struct
start_element           proc :ptr, :ptr, :ptr, :ptr, :gpointer, :ptr
end_element             proc :ptr, :ptr, :gpointer, :ptr
text                    proc :ptr, :ptr, :gsize, :gpointer, :ptr
error                   proc :ptr, :ptr, :gpointer
padding                 gpointer 4 dup(?)
_GtkBuildableParser     ends
GtkBuildableParser      typedef _GtkBuildableParser

_GtkBuildableIface      struct
g_iface                 GTypeInterface <>
set_id                  proc :ptr, :ptr
get_id                  proc :ptr
add_child               proc :ptr, :ptr, :ptr, :ptr
set_buildable_property  proc :ptr, :ptr, :ptr, :ptr
construct_child         proc :ptr, :ptr, :ptr
custom_tag_start        proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
custom_tag_end          proc :ptr, :ptr, :ptr, :ptr, :gpointer
custom_finished         proc :ptr, :ptr, :ptr, :ptr, :gpointer
parser_finished         proc :ptr, :ptr
get_internal_child      proc :ptr, :ptr, :ptr
_GtkBuildableIface      ends
GtkBuildableIface       typedef _GtkBuildableIface


gtk_buildable_get_type proto

gtk_buildable_get_buildable_id proto :ptr

gtk_buildable_parse_context_push proto :ptr, :ptr, :gpointer
gtk_buildable_parse_context_pop proto :ptr
gtk_buildable_parse_context_get_element proto :ptr
gtk_buildable_parse_context_get_element_stack proto :ptr
gtk_buildable_parse_context_get_position proto :ptr, :ptr, :ptr

endif
