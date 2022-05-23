ifndef __GTK_CELL_AREA_H__
define __GTK_CELL_AREA_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellrenderer.inc
include gtk/gtkwidget.inc
include gtk/gtktreemodel.inc

define GTK_TYPE_CELL_AREA                <gtk_cell_area_get_type>
GTK_CELL_AREA macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_AREA, GtkCellArea))>
  endm
GTK_CELL_AREA_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CELL_AREA, GtkCellAreaClass))>
  endm
GTK_IS_CELL_AREA macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_AREA))>
  endm
GTK_IS_CELL_AREA_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CELL_AREA))>
  endm
GTK_CELL_AREA_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CELL_AREA, GtkCellAreaClass))>
  endm

;GtkCellAreaContext      typedef _GtkCellAreaContext

GTK_CELL_AREA_WARN_INVALID_CELL_PROPERTY_ID macro object, property_id, pspec
  exitm<G_OBJECT_WARN_INVALID_PSPEC ((object), "cell property id", (property_id), (pspec))>
  endm


CALLBACK(GtkCellCallback, :ptr, :gpointer)
CALLBACK(GtkCellAllocCallback, :ptr, :ptr, :ptr, :gpointer)

_GtkCellArea            struct
parent_instance         GInitiallyUnowned <>
_GtkCellArea            ends
GtkCellArea             typedef _GtkCellArea

_GtkCellAreaClass       struct
parent_class            GInitiallyUnownedClass <>
_add                    proc :ptr, :ptr
remove                  proc :ptr, :ptr
foreach                 proc :ptr, :GtkCellCallback, :gpointer
foreach_alloc           proc :ptr, :ptr, :ptr, :ptr, :ptr, :GtkCellAllocCallback, :gpointer
event                   proc :ptr, :ptr, :ptr, :ptr, :ptr, :GtkCellRendererState
snapshot                proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :GtkCellRendererState, :gboolean
apply_attributes        proc :ptr, :ptr, :ptr, :gboolean, :gboolean
create_context          proc :ptr
copy_context            proc :ptr, :ptr
get_request_mode        proc :ptr
get_preferred_width     proc :ptr, :ptr, :ptr, :ptr, :ptr
get_preferred_height_for_width proc :ptr, :ptr, :ptr, :sdword, :ptr, :ptr
get_preferred_height    proc :ptr, :ptr, :ptr, :ptr, :ptr
get_preferred_width_for_height proc :ptr, :ptr, :ptr, :sdword, :ptr, :ptr
set_cell_property       proc :ptr, :ptr, :guint, :ptr, :ptr
get_cell_property       proc :ptr, :ptr, :guint, :ptr, :ptr
focus                   proc :ptr, :GtkDirectionType
is_activatable          proc :ptr
activate                proc :ptr, :ptr, :ptr, :ptr, :GtkCellRendererState, :gboolean
padding                 gpointer 8 dup(?)
_GtkCellAreaClass       ends
GtkCellAreaClass        typedef _GtkCellAreaClass

gtk_cell_area_get_type proto


gtk_cell_area_add proto :ptr, :ptr
gtk_cell_area_remove proto :ptr, :ptr
gtk_cell_area_has_renderer proto :ptr, :ptr
gtk_cell_area_foreach proto :ptr, :GtkCellCallback, :gpointer
gtk_cell_area_foreach_alloc proto :ptr, :ptr, :ptr, :ptr, :ptr, :GtkCellAllocCallback, :gpointer
gtk_cell_area_event proto :ptr, :ptr, :ptr, :ptr, :ptr, :GtkCellRendererState
gtk_cell_area_snapshot proto :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :GtkCellRendererState, :gboolean

gtk_cell_area_get_cell_allocation proto :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
gtk_cell_area_get_cell_at_position proto :ptr, :ptr, :ptr, :ptr, :sdword, :sdword, :ptr

gtk_cell_area_create_context proto :ptr
gtk_cell_area_copy_context proto :ptr, :ptr
gtk_cell_area_get_request_mode proto :ptr
gtk_cell_area_get_preferred_width proto :ptr, :ptr, :ptr, :ptr, :ptr
gtk_cell_area_get_preferred_height_for_width proto :ptr, :ptr, :ptr, :sdword, :ptr, :ptr
gtk_cell_area_get_preferred_height proto :ptr, :ptr, :ptr, :ptr, :ptr
gtk_cell_area_get_preferred_width_for_height proto :ptr, :ptr, :ptr, :sdword, :ptr, :ptr
gtk_cell_area_get_current_path_string proto :ptr

gtk_cell_area_apply_attributes proto :ptr, :ptr, :ptr, :gboolean, :gboolean
gtk_cell_area_attribute_connect proto :ptr, :ptr, :ptr, :sdword
gtk_cell_area_attribute_disconnect proto :ptr, :ptr, :ptr
gtk_cell_area_attribute_get_column proto :ptr, :ptr, :ptr

gtk_cell_area_class_install_cell_property proto :ptr, :guint, :ptr
gtk_cell_area_class_find_cell_property proto :ptr, :ptr
gtk_cell_area_class_list_cell_properties proto :ptr, :ptr
gtk_cell_area_add_with_properties proto :ptr, :ptr, :ptr, :vararg
gtk_cell_area_cell_set proto :ptr, :ptr, :ptr, :vararg
gtk_cell_area_cell_get proto :ptr, :ptr, :ptr, :vararg
gtk_cell_area_cell_set_valist proto :ptr, :ptr, :ptr, :va_list
gtk_cell_area_cell_get_valist proto :ptr, :ptr, :ptr, :va_list
gtk_cell_area_cell_set_property proto :ptr, :ptr, :ptr, :ptr
gtk_cell_area_cell_get_property proto :ptr, :ptr, :ptr, :ptr

gtk_cell_area_is_activatable proto :ptr
gtk_cell_area_activate proto :ptr, :ptr, :ptr, :ptr, :GtkCellRendererState, :gboolean
gtk_cell_area_focus proto :ptr, :GtkDirectionType
gtk_cell_area_set_focus_cell proto :ptr, :ptr
gtk_cell_area_get_focus_cell proto :ptr

gtk_cell_area_add_focus_sibling proto :ptr, :ptr, :ptr
gtk_cell_area_remove_focus_sibling proto :ptr, :ptr, :ptr
gtk_cell_area_is_focus_sibling proto :ptr, :ptr, :ptr
gtk_cell_area_get_focus_siblings proto :ptr, :ptr
gtk_cell_area_get_focus_from_sibling proto :ptr, :ptr

gtk_cell_area_get_edited_cell proto :ptr
gtk_cell_area_get_edit_widget proto :ptr
gtk_cell_area_activate_cell proto :ptr, :ptr, :ptr, :ptr, :ptr, :GtkCellRendererState
gtk_cell_area_stop_editing proto :ptr, :gboolean

gtk_cell_area_inner_cell_area proto :ptr, :ptr, :ptr, :ptr

gtk_cell_area_request_renderer proto :ptr, :ptr, :GtkOrientation, :ptr, :sdword, :ptr, :ptr

_gtk_cell_area_set_cell_data_func_with_proxy proto :ptr, :ptr, :GFunc, :gpointer, :GDestroyNotify, :gpointer

endif
