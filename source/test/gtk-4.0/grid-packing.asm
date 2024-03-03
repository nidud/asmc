include gtk/gtk.inc
include tchar.inc

.code

print_hello proc widget:ptr GtkWidget, data:gpointer

    g_print("Hello World\n");
    ret

print_hello endp


activate proc app:ptr GtkApplication, user_data:gpointer

    ;; create a new window, and set its title

   .new window:ptr GtkWidget = gtk_application_window_new(app)
    gtk_window_set_title(GTK_WINDOW(window), "Window")

    ;; Here we construct the container that is going pack our buttons

   .new grid:ptr GtkWidget = gtk_grid_new()

    ;; Pack the container in the window

    gtk_window_set_child(GTK_WINDOW(window), grid)

   .new button:ptr GtkWidget = gtk_button_new_with_label("Button 1")
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL)

    ;; Place the first button in the grid cell(0, 0), and make it fill
    ;; just 1 cell horizontally and vertically(ie no spanning)

    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1)

    mov button,gtk_button_new_with_label("Button 2")
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL)

    ;; Place the second button in the grid cell (1, 0), and make it fill
    ;; just 1 cell horizontally and vertically (ie no spanning)

    gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1)

    mov button,gtk_button_new_with_label("Quit")
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), window)

    ;; Place the Quit button in the grid cell (0, 1), and make it
    ;; span 2 columns.

    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1)
    gtk_widget_show(window)
    ret

activate endp


main proc argc:int_t, argv:array_t

   .new app:ptr GtkApplication
   .new status:int_t

    mov app,gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE)
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL)
    mov status,g_application_run(G_APPLICATION(app), argc, argv)
    g_object_unref(app)
    mov eax,status
    ret

main endp

end _tstart
