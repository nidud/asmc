ifndef __GTK_DND_H__
__GTK_DND_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtkselection.inc

G_BEGIN_DECLS

.enum GtkDestDefaults {
  GTK_DEST_DEFAULT_MOTION     = 1 shl 0,
  GTK_DEST_DEFAULT_HIGHLIGHT  = 1 shl 1,
  GTK_DEST_DEFAULT_DROP       = 1 shl 2,
  GTK_DEST_DEFAULT_ALL        = 0x07
}

.enum GtkTargetFlags {
  GTK_TARGET_SAME_APP       = 1 shl 0,
  GTK_TARGET_SAME_WIDGET    = 1 shl 1,
  GTK_TARGET_OTHER_APP      = 1 shl 2,
  GTK_TARGET_OTHER_WIDGET   = 1 shl 3
}


;void
gtk_drag_get_data proto __cdecl \
                widget: ptr GtkWidget,
               context: ptr GdkDragContext,
                target: GdkAtom,
                 time_: guint32

;void
gtk_drag_finish proto __cdecl \
               context: ptr GdkDragContext,
               success: gboolean,
                   del: gboolean,
                 time_: guint32


;GtkWidget
gtk_drag_get_source_widget proto __cdecl \
               context: ptr GdkDragContext


;void
gtk_drag_highlight proto __cdecl \
                widget: ptr GtkWidget

;void
gtk_drag_unhighlight proto __cdecl \
                widget: ptr GtkWidget


;void
gtk_drag_dest_set proto __cdecl \
                widget: ptr GtkWidget,
                 flags: GtkDestDefaults,
               targets: ptr GtkTargetEntry,
             n_targets: gint,
               actions: GdkDragAction


;void
gtk_drag_dest_set_proxy proto __cdecl \
                widget: ptr GtkWidget,
          proxy_window: ptr GdkWindow,
              protocol: GdkDragProtocol,
       use_coordinates: gboolean


;void
gtk_drag_dest_unset proto __cdecl \
                widget: ptr GtkWidget


;GdkAtom
gtk_drag_dest_find_target proto __cdecl \
                widget: ptr GtkWidget,
               context: ptr GdkDragContext,
           target_list: ptr GtkTargetList

;GtkTargetList*
gtk_drag_dest_get_target_list proto __cdecl \
                widget: ptr GtkWidget

;void
gtk_drag_dest_set_target_list proto __cdecl \
                widget: ptr GtkWidget,
           target_list: ptr GtkTargetList

;void
gtk_drag_dest_add_text_targets proto __cdecl \
                widget: ptr GtkWidget

;void
gtk_drag_dest_add_image_targets proto __cdecl \
                widget: ptr GtkWidget

;void
gtk_drag_dest_add_uri_targets proto __cdecl \
                widget: ptr GtkWidget


;void
gtk_drag_dest_set_track_motion proto __cdecl \
                widget: ptr GtkWidget,
          track_motion: gboolean

;gboolean
gtk_drag_dest_get_track_motion proto __cdecl \
                widget: ptr GtkWidget



;void
gtk_drag_source_set proto __cdecl \
                widget: ptr GtkWidget,
     start_button_mask: GdkModifierType,
               targets: ptr GtkTargetEntry,
             n_targets: gint,
               actions: GdkDragAction


;void
gtk_drag_source_unset proto __cdecl \
                widget: ptr GtkWidget


;GtkTargetList*
gtk_drag_source_get_target_list proto __cdecl \
                widget: ptr GtkWidget

;void
gtk_drag_source_set_target_list proto __cdecl \
                widget: ptr GtkWidget,
           target_list: ptr GtkTargetList

;void
gtk_drag_source_add_text_targets proto __cdecl \
                widget: ptr GtkWidget

;void
gtk_drag_source_add_image_targets proto __cdecl \
                widget: ptr GtkWidget

;void
gtk_drag_source_add_uri_targets proto __cdecl \
                widget: ptr GtkWidget


;void
gtk_drag_source_set_icon_pixbuf proto __cdecl \
                widget: ptr GtkWidget,
                pixbuf: ptr GdkPixbuf

;void
gtk_drag_source_set_icon_stock proto __cdecl \
                widget: ptr GtkWidget,
              stock_id: ptr gchar

;void
gtk_drag_source_set_icon_name proto __cdecl \
                widget: ptr GtkWidget,
             icon_name: ptr gchar

;void
gtk_drag_source_set_icon_gicon proto __cdecl \
                widget: ptr GtkWidget,
                  icon: ptr GIcon


;GdkDragContext
gtk_drag_begin_with_coordinates proto __cdecl \
                widget: ptr GtkWidget,
               targets: ptr GtkTargetList,
               actions: GdkDragAction,
                button: gint,
                 event: ptr GdkEvent,
                     x: gint,
                     y: gint


;GdkDragContext
gtk_drag_begin proto __cdecl \
                widget: ptr GtkWidget,
               targets: ptr GtkTargetList,
               actions: GdkDragAction,
                button: gint,
                 event: ptr GdkEvent


;void
gtk_drag_cancel proto __cdecl \
               context: ptr GdkDragContext


;void
gtk_drag_set_icon_widget proto __cdecl \
               context: ptr GdkDragContext,
                widget: ptr GtkWidget,
                 hot_x: gint,
                 hot_y: gint

;void
gtk_drag_set_icon_pixbuf proto __cdecl \
               context: ptr GdkDragContext,
                pixbuf: ptr GdkPixbuf,
                 hot_x: gint,
                 hot_y: gint

;void
gtk_drag_set_icon_stock proto __cdecl \
               context: ptr GdkDragContext,
              stock_id: ptr gchar,
                 hot_x: gint,
                 hot_y: gint

;void
gtk_drag_set_icon_surface proto __cdecl \
               context: ptr GdkDragContext,
               surface: ptr cairo_surface_t

;void
gtk_drag_set_icon_name proto __cdecl \
               context: ptr GdkDragContext,
             icon_name: ptr gchar,
                 hot_x: gint,
                 hot_y: gint

;void
gtk_drag_set_icon_gicon proto __cdecl \
               context: ptr GdkDragContext,
                  icon: ptr GIcon,
                 hot_x: gint,
                 hot_y: gint


;void
gtk_drag_set_icon_default proto __cdecl \
               context: ptr GdkDragContext


;gboolean
gtk_drag_check_threshold proto __cdecl \
                widget: ptr GtkWidget,
               start_x: gint,
               start_y: gint,
             current_x: gint,
             current_y: gint


G_END_DECLS

endif
