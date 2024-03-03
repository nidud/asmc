include gtk/gtk.inc
include glib/gstdio.inc
include tchar.inc

.code

print_hello proc widget:ptr GtkWidget, data:gpointer

    g_print("Hello World\n")
    ret

print_hello endp


quit_cb proc widget:ptr GtkWidget, data:gpointer

   .new window:ptr GtkWindow = data
    gtk_window_close(window)
    ret

quit_cb endp


activate proc application:ptr GtkApplication, user_data:gpointer

    ;; Construct a GtkBuilder instance and load our UI description

   .new builder:ptr GtkBuilder = gtk_builder_new()
    gtk_builder_add_from_file(builder, "builder.ui", NULL)

    ;; Connect signal handlers to the constructed widgets.

   .new window:ptr GObject = gtk_builder_get_object(builder, "window")
    gtk_window_set_application(GTK_WINDOW(window), application)

   .new button:ptr GObject = gtk_builder_get_object(builder, "button1")
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL)

    mov button,gtk_builder_get_object(builder, "button2")
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL)

    mov button,gtk_builder_get_object(builder, "quit")
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(quit_cb), window)

    gtk_widget_show(GTK_WIDGET(window))
    g_object_unref(builder)
    ret

activate endp


main proc argc:int_t, argv:array_t

ifdef GTK_SRCDIR
    g_chdir(GTK_SRCDIR)
endif

   .new app:ptr GtkApplication = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE)
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL)

   .new status:int_t = g_application_run(G_APPLICATION(app), argc, argv)
    g_object_unref(app)
    mov eax,status
    ret

main endp

end _tstart
