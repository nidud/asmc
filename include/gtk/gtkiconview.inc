ifndef __GTK_ICON_VIEW_H__
define __GTK_ICON_VIEW_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtktreemodel.inc
include gtk/gtkcellrenderer.inc
include gtk/gtkcellarea.inc
include gtk/gtktooltip.inc

define GTK_TYPE_ICON_VIEW <gtk_icon_view_get_type ()>
GTK_ICON_VIEW macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ICON_VIEW, GtkIconView))>
  endm
GTK_IS_ICON_VIEW macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ICON_VIEW))>
  endm

;GtkIconView             typedef _GtkIconView

CALLBACK(GtkIconViewForeachFunc, :ptr, :ptr, :gpointer)

.enum GtkIconViewDropPosition {
  GTK_ICON_VIEW_NO_DROP,
  GTK_ICON_VIEW_DROP_INTO,
  GTK_ICON_VIEW_DROP_LEFT,
  GTK_ICON_VIEW_DROP_RIGHT,
  GTK_ICON_VIEW_DROP_ABOVE,
  GTK_ICON_VIEW_DROP_BELOW
}

gtk_icon_view_get_type proto
gtk_icon_view_new proto
gtk_icon_view_new_with_area proto :ptr
gtk_icon_view_new_with_model proto :ptr

gtk_icon_view_set_model proto :ptr, :ptr
gtk_icon_view_get_model proto :ptr
gtk_icon_view_set_text_column proto :ptr, :sdword
gtk_icon_view_get_text_column proto :ptr
gtk_icon_view_set_markup_column proto :ptr, :sdword
gtk_icon_view_get_markup_column proto :ptr
gtk_icon_view_set_pixbuf_column proto :ptr, :sdword
gtk_icon_view_get_pixbuf_column proto :ptr

gtk_icon_view_set_item_orientation proto :ptr, :GtkOrientation
gtk_icon_view_get_item_orientation proto :ptr
gtk_icon_view_set_columns proto :ptr, :sdword
gtk_icon_view_get_columns proto :ptr
gtk_icon_view_set_item_width proto :ptr, :sdword
gtk_icon_view_get_item_width proto :ptr
gtk_icon_view_set_spacing proto :ptr, :sdword
gtk_icon_view_get_spacing proto :ptr
gtk_icon_view_set_row_spacing proto :ptr, :sdword
gtk_icon_view_get_row_spacing proto :ptr
gtk_icon_view_set_column_spacing proto :ptr, :sdword
gtk_icon_view_get_column_spacing proto :ptr
gtk_icon_view_set_margin proto :ptr, :sdword
gtk_icon_view_get_margin proto :ptr
gtk_icon_view_set_item_padding proto :ptr, :sdword
gtk_icon_view_get_item_padding proto :ptr

gtk_icon_view_get_path_at_pos proto :ptr, :sdword, :sdword
gtk_icon_view_get_item_at_pos proto :ptr, :sdword, :sdword, :ptr, :ptr
gtk_icon_view_get_visible_range proto :ptr, :ptr, :ptr
gtk_icon_view_set_activate_on_single_click proto :ptr, :gboolean
gtk_icon_view_get_activate_on_single_click proto :ptr

gtk_icon_view_selected_foreach proto :ptr, :GtkIconViewForeachFunc, :gpointer
gtk_icon_view_set_selection_mode proto :ptr, :GtkSelectionMode
gtk_icon_view_get_selection_mode proto :ptr
gtk_icon_view_select_path proto :ptr, :ptr
gtk_icon_view_unselect_path proto :ptr, :ptr
gtk_icon_view_path_is_selected proto :ptr, :ptr
gtk_icon_view_get_item_row proto :ptr, :ptr
gtk_icon_view_get_item_column proto :ptr, :ptr
gtk_icon_view_get_selected_items proto :ptr
gtk_icon_view_select_all proto :ptr
gtk_icon_view_unselect_all proto :ptr
gtk_icon_view_item_activated proto :ptr, :ptr
gtk_icon_view_set_cursor proto :ptr, :ptr, :ptr, :gboolean
gtk_icon_view_get_cursor proto :ptr, :ptr, :ptr
gtk_icon_view_scroll_to_path proto :ptr, :ptr, :gboolean, :real4, :real4

gtk_icon_view_enable_model_drag_source proto :ptr, :GdkModifierType, :ptr, :GdkDragAction
gtk_icon_view_enable_model_drag_dest proto :ptr, :ptr, :GdkDragAction
gtk_icon_view_unset_model_drag_source proto :ptr
gtk_icon_view_unset_model_drag_dest proto :ptr
gtk_icon_view_set_reorderable proto :ptr, :gboolean
gtk_icon_view_get_reorderable proto :ptr

gtk_icon_view_set_drag_dest_item proto :ptr, :ptr, :GtkIconViewDropPosition
gtk_icon_view_get_drag_dest_item proto :ptr, :ptr, :ptr
gtk_icon_view_get_dest_item_at_pos proto :ptr, :sdword, :sdword, :ptr, :ptr
gtk_icon_view_create_drag_icon proto :ptr, :ptr

gtk_icon_view_get_cell_rect proto :ptr, :ptr, :ptr, :ptr

gtk_icon_view_set_tooltip_item proto :ptr, :ptr, :ptr
gtk_icon_view_set_tooltip_cell proto :ptr, :ptr, :ptr, :ptr
gtk_icon_view_get_tooltip_context proto :ptr, :sdword, :sdword, :gboolean, :ptr, :ptr, :ptr
gtk_icon_view_set_tooltip_column proto :ptr, :sdword
gtk_icon_view_get_tooltip_column proto :ptr

endif
