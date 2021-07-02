ifndef __GTK_WIDGET_PATH_H__
__GTK_WIDGET_PATH_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib-object.inc
include gdk/gdk.inc
include gtk/gtkenums.inc
include gtk/gtktypes.inc

G_BEGIN_DECLS

GTK_TYPE_WIDGET_PATH    equ <gtk_widget_path_get_type>

;GType
gtk_widget_path_get_type proto __cdecl
;GtkWidgetPath
gtk_widget_path_new proto __cdecl

;GtkWidgetPath
gtk_widget_path_copy proto __cdecl \
                  path: ptr GtkWidgetPath

;GtkWidgetPath
gtk_widget_path_ref proto __cdecl \
                  path: ptr GtkWidgetPath

;void
gtk_widget_path_unref proto __cdecl \
                  path: ptr GtkWidgetPath

;void
gtk_widget_path_free proto __cdecl \
                  path: ptr GtkWidgetPath


;char
gtk_widget_path_to_string proto __cdecl \
                  path: ptr GtkWidgetPath

;gint
gtk_widget_path_length proto __cdecl \
                  path: ptr GtkWidgetPath


;gint
gtk_widget_path_append_type proto __cdecl \
                  path: ptr GtkWidgetPath,
                  type: GType

;void
gtk_widget_path_prepend_type proto __cdecl \
                  path: ptr GtkWidgetPath,
                  type: GType

;gint
gtk_widget_path_append_with_siblings proto __cdecl \
                  path: ptr GtkWidgetPath,
              siblings: ptr GtkWidgetPath,
         sibling_index: guint

;gint
gtk_widget_path_append_for_widget proto __cdecl \
                  path: ptr GtkWidgetPath,
                widget: ptr GtkWidget


;GType
gtk_widget_path_iter_get_object_type proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint

;void
gtk_widget_path_iter_set_object_type proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint,
                  type: GType

;const
gtk_widget_path_iter_get_siblings proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint

;guint
gtk_widget_path_iter_get_sibling_index proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint


;const
gtk_widget_path_iter_get_name proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint

;void
gtk_widget_path_iter_set_name proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint,
                  name: ptr gchar

;gboolean
gtk_widget_path_iter_has_name proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint,
                  name: ptr gchar

;gboolean
gtk_widget_path_iter_has_qname proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint,
                 qname: GQuark

;GtkStateFlags
gtk_widget_path_iter_get_state proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint

;void
gtk_widget_path_iter_set_state proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint,
                 state: GtkStateFlags


;void
gtk_widget_path_iter_add_class proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint,
                  name: ptr gchar

;void
gtk_widget_path_iter_remove_class proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint,
                  name: ptr gchar

;void
gtk_widget_path_iter_clear_classes proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint

;GSList
gtk_widget_path_iter_list_classes proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint

;gboolean
gtk_widget_path_iter_has_class proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint,
                  name: ptr gchar

;gboolean
gtk_widget_path_iter_has_qclass proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint,
                 qname: GQuark


;void
gtk_widget_path_iter_add_region proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint,
                  name: ptr gchar,
                 flags: GtkRegionFlags

;void
gtk_widget_path_iter_remove_region proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint,
                  name: ptr gchar

;void
gtk_widget_path_iter_clear_regions proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint


;GSList
gtk_widget_path_iter_list_regions proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint


;gboolean
gtk_widget_path_iter_has_region proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint,
                  name: ptr gchar,
                 flags: ptr GtkRegionFlags

;gboolean
gtk_widget_path_iter_has_qregion proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint,
                 qname: GQuark,
                 flags: ptr GtkRegionFlags


;GType
gtk_widget_path_get_object_type proto __cdecl \
                  path: ptr GtkWidgetPath


;gboolean
gtk_widget_path_is_type proto __cdecl \
                  path: ptr GtkWidgetPath,
                  type: GType

;gboolean
gtk_widget_path_has_parent proto __cdecl \
                  path: ptr GtkWidgetPath,
                  type: GType



;void
gtk_widget_path_iter_add_qclass proto __cdecl \
                  path: ptr GtkWidgetPath,
                   pos: gint,
                 qname: GQuark

G_END_DECLS

endif
