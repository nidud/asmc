include gtk/gtk.inc
include tchar.inc

.code

print_hello proc widget:ptr GtkWidget, data:gpointer

  g_print("Hello World\n")
  ret

print_hello endp

activate proc app:ptr GtkApplication, user_data:gpointer

   .new window:ptr GtkWidget = gtk_application_window_new(app)
    gtk_window_set_title(window, "Window")
    gtk_window_set_default_size(window, 200, 200)

   .new button:ptr GtkWidget = gtk_button_new_with_label("Hello World")
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER)
    gtk_widget_set_valign(button, GTK_ALIGN_CENTER)

    g_signal_connect(button, "clicked", &print_hello, NULL)
    g_signal_connect_swapped(button, "clicked", &gtk_window_destroy, window)

    gtk_window_set_child(window, button)
    gtk_widget_show(window)
    ret

activate endp

main proc _argc:int_t, _argv:array_t

   .new argc:int_t = _argc
   .new argv:array_t = _argv

   .new app:ptr GtkApplication = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE)
    g_signal_connect(app, "activate", &activate, NULL)

   .new status:int_t = g_application_run(app, argc, argv)
    g_object_unref(app)

   .return status

main endp

    end _tstart
