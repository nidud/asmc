include gtk/gtk.inc
include tchar.inc

.code

activate proc app:ptr GtkApplication, user_data:gpointer

   .new window:ptr GtkWidget = gtk_application_window_new(app)
    gtk_window_set_title(window, "Window")
    gtk_window_set_default_size(window, 200, 200)
    gtk_widget_show(window)
    ret

activate endp

main proc argc:int_t, argv:array_t

   .new app:ptr GtkApplication
   .new status:int_t

    mov app,gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE)
    g_signal_connect(app, "activate", &activate, NULL)
    mov status,g_application_run(app, argc, argv)
    g_object_unref(app)
    mov eax,status
    ret

main endp

    end _tstart
