include gtk/gtk.inc
include tchar.inc

.code

activate_cb proc app:ptr GtkApplication, user_data:gpointer

   .new window:ptr GtkWidget
   .new search_bar:ptr GtkWidget
   .new box:ptr GtkWidget
   .new entry:ptr GtkWidget
   .new menu_button:ptr GtkWidget
   .new searchbar:ptr GtkSearchBar

    mov window,gtk_application_window_new(app)
    gtk_widget_show(window)

    mov search_bar,gtk_search_bar_new()
    gtk_widget_set_valign(search_bar, GTK_ALIGN_START)
    gtk_window_set_child(GTK_WINDOW(window), search_bar)
    gtk_widget_show(search_bar)

    mov box,gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6)
    gtk_search_bar_set_child(GTK_SEARCH_BAR(search_bar), box)

    mov entry,gtk_search_entry_new()
    gtk_widget_set_hexpand(entry, TRUE)
    gtk_box_append(GTK_BOX(box), entry)

    mov menu_button,gtk_menu_button_new()
    gtk_box_append(GTK_BOX(box), menu_button)
    mov searchbar,GTK_SEARCH_BAR(search_bar)
    gtk_search_bar_connect_entry(searchbar, GTK_EDITABLE(entry))
    gtk_search_bar_set_key_capture_widget(searchbar, window)
    ret

activate_cb endp

main proc argc:int_t, argv:array_t

   .new app:ptr GtkApplication

    mov app,gtk_application_new("org.gtk.Example.GtkSearchBar", G_APPLICATION_FLAGS_NONE)
    g_signal_connect(app, "activate", G_CALLBACK(activate_cb), NULL)
    g_application_run(G_APPLICATION(app), argc, argv)
    ret

main endp

    end _tstart
