ifndef __GTK_TEST_UTILS_H__
__GTK_TEST_UTILS_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtkspinbutton.inc

G_BEGIN_DECLS

;void
gtk_test_init proto _CDecl \
                 argcp: ptr int_t,
                 argvp: ptr char_t,
                      : vararg

;void
gtk_test_register_all_types proto __cdecl
;const
gtk_test_list_all_types proto __cdecl \
               n_types: ptr guint

;GtkWidget*
gtk_test_find_widget proto __cdecl \
                widget: ptr GtkWidget,
         label_pattern: ptr gchar,
           widget_type: GType

;GtkWidget*
gtk_test_create_widget proto _CDecl \
           widget_type: GType,
   first_property_name: ptr gchar,
                      : vararg

;GtkWidget*
gtk_test_create_simple_window proto __cdecl \
          window_title: ptr gchar,
           dialog_text: ptr gchar

;GtkWidget*
gtk_test_display_button_window proto _CDecl \
          window_title: ptr gchar,
           dialog_text: ptr gchar,
                      : vararg

;void
gtk_test_slider_set_perc proto __cdecl \
                widget: ptr GtkWidget,
            percentage: double

;double
gtk_test_slider_get_value proto __cdecl \
                widget: ptr GtkWidget

;gboolean
gtk_test_spin_button_click proto __cdecl \
               spinner: ptr GtkSpinButton,
                button: guint,
               upwards: gboolean

;void
gtk_test_widget_wait_for_draw proto __cdecl \
                widget: ptr GtkWidget

;gboolean
gtk_test_widget_click proto __cdecl \
                widget: ptr GtkWidget,
                button: guint,
             modifiers: GdkModifierType

;gboolean
gtk_test_widget_send_key proto __cdecl \
                widget: ptr GtkWidget,
                keyval: guint,
             modifiers: GdkModifierType

;void
gtk_test_text_set proto __cdecl \
                widget: ptr GtkWidget,
                string: ptr gchar

;gchar*
gtk_test_text_get proto __cdecl \
                widget: ptr GtkWidget


;GtkWidget*
gtk_test_find_sibling proto __cdecl \
           base_widget: ptr GtkWidget,
           widget_type: GType

;GtkWidget*
gtk_test_find_label proto __cdecl \
                widget: ptr GtkWidget,
         label_pattern: ptr gchar

G_END_DECLS

endif
