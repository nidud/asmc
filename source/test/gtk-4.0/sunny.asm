include stdlib.inc
include gtk/gtk.inc
include tchar.inc

option proc:private

.code

new_window proc app:ptr GApplication, file:ptr GFile

   .new window:ptr GtkWidget
   .new header:ptr GtkWidget
   .new overlay:ptr GtkWidget
   .new scrolled:ptr GtkWidget
   .new view:ptr GtkWidget
   .new contents:ptr char_t
   .new length:gsize
   .new buffer:ptr GtkTextBuffer

    mov window,gtk_application_window_new(app)
    gtk_application_window_set_show_menubar(window, TRUE)
    gtk_window_set_default_size(window, 640, 480)
    gtk_window_set_title(window, "Sunny")
    gtk_window_set_icon_name(window, "weather-clear-symbolic")

    mov header,gtk_header_bar_new()
    gtk_window_set_titlebar(window, header)

    mov overlay,gtk_overlay_new()
    gtk_window_set_child(window, overlay)

    mov scrolled,gtk_scrolled_window_new()
    gtk_widget_set_hexpand(scrolled, TRUE)
    gtk_widget_set_vexpand(scrolled, TRUE)
    mov view,gtk_text_view_new()

    gtk_scrolled_window_set_child(scrolled, view)
    gtk_overlay_set_child(overlay, scrolled)

    .if ( file != NULL )

        .if ( g_file_load_contents(file, NULL, &contents, &length, NULL, NULL) )

            mov buffer,gtk_text_view_get_buffer(view)
            gtk_text_buffer_set_text(buffer, contents, int_t ptr length)
            g_free(contents)
        .endif
        .endif

    gtk_widget_show(window)
    ret

new_window endp

activate proc application:ptr GApplication

    new_window(application, NULL)
    ret

activate endp

openfiles proc uses rbx application:ptr GApplication, files:ptr ptr GFile, n_files:int_t, hint:ptr char_t

    .new i:int_t
    .for ( rbx=files, i=0 : i < n_files : i++, rbx+=size_t )

        new_window(application, [rbx])
    .endf
    ret

openfiles endp

MenuButton      typedef GtkApplication
MenuButtonClass typedef GtkApplicationClass

menu_button_get_type proto

G_DEFINE_TYPE(MenuButton, menu_button, GTK_TYPE_APPLICATION)

show_about proc action:ptr GSimpleAction, parameter:ptr GVariant, user_data:gpointer

  .return gtk_show_about_dialog(NULL,
        "program-name", "Sunny",
        "title", "About Sunny",
        "logo-icon-name", "weather-clear-symbolic",
        "comments", "A cheap Bloatpad clone.", NULL)

show_about endp


quit_app proc uses rbx action:GSimpleAction, parameter:ptr GVariant, user_data:gpointer

    g_print("Going down...\n")

    mov rbx,gtk_application_get_windows(g_application_get_default())
    .while rbx
        mov rcx,[rbx].GList.data
        mov rbx,[rbx].GList.next
        gtk_window_destroy(rcx)
    .endw
    ret

quit_app endp


new_activated proc action:ptr GSimpleAction, parameter:ptr GVariant, user_data:gpointer

    g_application_activate(user_data)
    ret

new_activated endp

startup proc application:ptr GApplication

   .new applicationClass:ptr GApplicationClass = G_APPLICATION_CLASS(menu_button_parent_class)
   .new app_entries[3]:GActionEntry = {
        { "about", &show_about, NULL, NULL, NULL },
        { "quit", &quit_app, NULL, NULL, NULL },
        { "new", &new_activated, NULL, NULL, NULL } }

    applicationClass.startup(application)
    g_action_map_add_action_entries(G_ACTION_MAP(application), &app_entries, G_N_ELEMENTS(app_entries), application)

    .if (g_getenv("APP_MENU_FALLBACK"))
        g_object_set(gtk_settings_get_default(), "gtk-shell-shows-app-menu", FALSE, NULL)
    .endif

   .new builder:ptr GtkBuilder = gtk_builder_new()
    gtk_builder_add_from_string(builder,
                               "<interface>"
                               "  <menu id='menubar'>"
                               "    <submenu>"
                               "      <attribute name='label' translatable='yes'>Sunny</attribute>"
                               "      <section>"
                               "        <item>"
                               "          <attribute name='label' translatable='yes'>_New Window</attribute>"
                               "          <attribute name='action'>app.new</attribute>"
                               "        </item>"
                               "        <item>"
                               "          <attribute name='label' translatable='yes'>_About Sunny</attribute>"
                               "          <attribute name='action'>app.about</attribute>"
                               "        </item>"
                               "        <item>"
                               "          <attribute name='label' translatable='yes'>_Quit</attribute>"
                               "          <attribute name='action'>app.quit</attribute>"
                               "          <attribute name='accel'>&lt;Primary&gt;q</attribute>"
                               "        </item>"
                               "      </section>"
                               "    </submenu>"
                               "  </menu>"
                               "</interface>", -1, NULL);

    gtk_application_set_menubar(application, gtk_builder_get_object(builder, "menubar"))
    g_object_unref(builder)
    ret

startup endp

option proc:public

menu_button_init proc app:ptr MenuButton
    ret
menu_button_init endp

menu_button_class_init proc class:ptr MenuButtonClass

 .new button_class:ptr MenuButtonClass = class
  mov rcx,G_APPLICATION_CLASS(button_class)
  mov [rcx].GApplicationClass.startup,&startup
  mov [rcx].GApplicationClass.activate,&activate
  mov [rcx].GApplicationClass.open,&openfiles
  ret
menu_button_class_init endp


menu_button_new proc

  .return g_object_new(menu_button_get_type(),
                       "application-id", "org.gtk.Test.Sunny",
                       "flags", G_APPLICATION_HANDLES_OPEN, NULL)
menu_button_new endp


main proc argc:int_t, argv:array_t

   .new menu_button:ptr MenuButton
   .new status:int_t

    mov menu_button,menu_button_new()
    mov status,g_application_run(menu_button, argc, argv)
    g_object_unref(menu_button)
    mov eax,status
    ret

main endp

    end _tstart
