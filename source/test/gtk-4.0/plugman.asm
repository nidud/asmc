include stdlib.inc
include gtk/gtk.inc
include string.inc
include tchar.inc

.data
 red_css string_t @CStr(
    "textview {"
    "  color: red;"
    "}")
 black_css string_t @CStr(
    "textview {"
    "  color: black;"
    "}")

.code

activate_toggle proc action:ptr GSimpleAction, parameter:ptr GVariant, user_data:gpointer

   .new state:ptr GVariant
   .new variant:gboolean
   .new newstate:ptr GVariant

    mov state,g_action_get_state(G_ACTION(action))
    mov variant,g_variant_get_boolean(state)
    xor variant,TRUE
    mov newstate,g_variant_new_boolean(variant)

    g_action_change_state(G_ACTION(action), newstate)
    g_variant_unref(state)
    ret

activate_toggle endp


change_fullscreen_state proc action:ptr GSimpleAction, state:ptr GVariant, user_data:gpointer

    .if ( g_variant_get_boolean(state) )
        gtk_window_fullscreen(user_data)
    .else
        gtk_window_unfullscreen(user_data)
    .endif
    g_simple_action_set_state(action, state)
    ret

change_fullscreen_state endp


window_copy proc action:ptr GSimpleAction, parameter:ptr GVariant, user_data:gpointer

   .new window:ptr GtkWindow = GTK_WINDOW(user_data)
   .new text:ptr GtkTextView = g_object_get_data(window, "plugman-text")
   .new buffer:string_t = gtk_text_view_get_buffer(text)

    gtk_text_buffer_copy_clipboard(buffer, gtk_widget_get_clipboard(GTK_WIDGET(text)))
    ret

window_copy endp


window_paste proc action:ptr GSimpleAction, parameter:ptr GVariant, user_data:gpointer

   .new window:ptr GtkWindow = GTK_WINDOW(user_data)
   .new text:ptr GtkTextView = g_object_get_data(window, "plugman-text")
   .new buffer:string_t = gtk_text_view_get_buffer(text)

    gtk_text_buffer_paste_clipboard(buffer, gtk_widget_get_clipboard(GTK_WIDGET(text)), NULL, TRUE)
    ret

window_paste endp


new_window proc app:ptr GApplication, file:ptr GFile

   .new contents:string_t
   .new length:gsize
   .new buffer:ptr GtkTextBuffer
   .new view:ptr GtkWidget
   .new scrolled:ptr GtkWidget
   .new grid:ptr GtkWidget
   .new window:ptr GtkWidget
   .new win_entries[3]:GActionEntry = {
        { "copy", &window_copy, NULL, NULL, NULL },
        { "paste", &window_paste, NULL, NULL, NULL },
        { "fullscreen", &activate_toggle, NULL, "false", &change_fullscreen_state } }

    mov window,gtk_application_window_new(GTK_APPLICATION(app))
    gtk_window_set_default_size(window, 640, 480)
    g_action_map_add_action_entries(G_ACTION_MAP(window), &win_entries, G_N_ELEMENTS(win_entries), window)
    gtk_window_set_title(GTK_WINDOW(window), "Plugman")
    gtk_application_window_set_show_menubar(GTK_APPLICATION_WINDOW(window), TRUE)

    mov grid,gtk_grid_new()
    gtk_window_set_child(GTK_WINDOW(window), grid)

    mov scrolled,gtk_scrolled_window_new()
    gtk_widget_set_hexpand(scrolled, TRUE)
    gtk_widget_set_vexpand(scrolled, TRUE)
    mov view,gtk_text_view_new()

    g_object_set_data(window, "plugman-text", view)

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), view)

    gtk_grid_attach(GTK_GRID(grid), scrolled, 0, 0, 1, 1)

    .if ( file != NULL )

        .if (g_file_load_contents(file, NULL, &contents, &length, NULL, NULL))

            mov buffer,gtk_text_view_get_buffer(GTK_TEXT_VIEW(view))
            gtk_text_buffer_set_text(buffer, contents, gint ptr length)
            g_free(contents)
        .endif
    .endif

    gtk_widget_show(GTK_WIDGET(window))
    ret

new_window endp


plug_man_activate proc application:ptr GApplication

    new_window(application, NULL)
    ret

plug_man_activate endp


plug_man_open proc uses rbx application:ptr GApplication, files:ptr ptr GFile, n_files:int_t, hint:string_t

    .new i:int_t
    .for ( rbx=files, i=0 : i < n_files : i++, rbx+=size_t )

        new_window(application, [rbx])
    .endf
    ret

plug_man_open endp

PlugMan typedef GtkApplication
PlugManClass typedef GtkApplicationClass

plug_man_get_type proto
G_DEFINE_TYPE(PlugMan, plug_man, GTK_TYPE_APPLICATION)


plug_man_finalize proc curobject:ptr GObject

   .new object:ptr GObject = curobject
   .new objectClass:ptr GObjectClass = G_OBJECT_CLASS(plug_man_parent_class)
    objectClass.finalize(object)
    ret

plug_man_finalize endp


show_about proc action:ptr GSimpleAction,
                parameter:ptr GVariant,
                user_data:gpointer

   .return gtk_show_about_dialog(
        NULL,
        "program-name", "Plugman",
        "title", "About Plugman",
        "comments", "A cheap Bloatpad clone.",
        NULL)

show_about endp



quit_app proc uses rbx action:ptr GSimpleAction, parameter:ptr GVariant, user_data:gpointer

    g_print("Going down...\n")
   .new app:ptr = g_application_get_default()

    mov rbx,gtk_application_get_windows(GTK_APPLICATION(app))
    .while rbx
        mov rcx,[rbx].GList.data
        mov rbx,[rbx].GList.next
        gtk_window_destroy(rcx)
    .endw
    ret

quit_app endp

 .data
  align 8
  is_red_plugin_enabled gboolean FALSE
  is_black_plugin_enabled gboolean FALSE
 .code

plugin_enabled proc name:string_t

    .if (g_strcmp0(name, "red") == 0)
        .return is_red_plugin_enabled
    .endif
    .return is_black_plugin_enabled

plugin_enabled endp


find_plugin_menu proc

   .new app:ptr = g_application_get_default()
    g_object_get_data(G_OBJECT(app), "plugin-menu")
    ret

find_plugin_menu endp


plugin_action proc action:ptr GAction, parameter:ptr GVariant, data:gpointer

    .new css_to_load:string_t
    .new action_name:string_t = g_action_get_name(action)
    .new css_provider:ptr GtkCssProvider
    .new display:ptr

    .if (strcmp(action_name, "red") == 0)
        mov css_to_load,red_css
    .elseif(strcmp(action_name, "black") == 0)
        mov css_to_load,black_css
    .else
        g_critical("Unknown action name: %s", action_name)
       .return
    .endif

    g_message("Color: %s", g_action_get_name(action))

    mov css_provider,gtk_css_provider_new()
    gtk_css_provider_load_from_data(css_provider, css_to_load, -1)
    mov display,gdk_display_get_default()
    gtk_style_context_add_provider_for_display(display,GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION)
    ret

plugin_action endp


enable_plugin proc name:string_t

   .new action:ptr GAction
   .new app:ptr
   .new plugin_menu:ptr GMenuModel
   .new section:ptr GMenu
   .new slabel:string_t
   .new action_name:string_t
   .new item:ptr GMenuItem

    g_print("Enabling '%s' plugin\n", name)

    mov action,g_simple_action_new(name, NULL)
    g_signal_connect(action, "activate", G_CALLBACK(plugin_action), name)

    mov app,g_application_get_default()
    g_action_map_add_action(G_ACTION_MAP(app), action)
    g_print("Actions of '%s' plugin added\n", name)
    g_object_unref(action)

    mov plugin_menu,find_plugin_menu()
    .if ( plugin_menu )

        mov section,g_menu_new()
        mov slabel,g_strdup_printf("Turn text %s", name)
        mov action_name,g_strconcat("app.", name, NULL)
        g_menu_insert(section, 0, slabel, action_name)
        g_free(slabel)
        g_free(action_name)
        mov item,g_menu_item_new_section(NULL, section)
        g_menu_item_set_attribute(item, "id", "s", name)
        g_menu_append_item(G_MENU(plugin_menu), item)
        g_object_unref(item)
        g_object_unref(section)
        g_print("Menus of '%s' plugin added\n", name)
    .else
        g_warning("Plugin menu not found")
    .endif

    .if (g_strcmp0(name, "red") == 0)
        mov is_red_plugin_enabled,TRUE
    .else
        mov is_black_plugin_enabled,TRUE
    .endif
    ret

enable_plugin endp


disable_plugin proc name:string_t

   .new plugin_menu:ptr GMenuModel
   .new id:string_t
   .new i:int_t
   .new n_items:int_t

    g_print("Disabling '%s' plugin\n", name)

    mov plugin_menu,find_plugin_menu()

    .if ( plugin_menu )

        mov n_items,g_menu_model_get_n_items(plugin_menu)

        .for ( i = 0 : i < n_items : i++ )

            .if ( g_menu_model_get_item_attribute(plugin_menu, i, "id", "s", &id) )

                .if (g_strcmp0(id, name) == 0)

                    g_menu_remove(G_MENU(plugin_menu), i)
                    g_print("Menus of '%s' plugin removed\n", name)
                .endif
                g_free(id)
            .endif
        .endf
    .else
        g_warning("Plugin menu not found")
    .endif

    g_action_map_remove_action(G_ACTION_MAP(g_application_get_default()), name)
    g_print("Actions of '%s' plugin removed\n", name)

    .if (g_strcmp0(name, "red") == 0)
        mov is_red_plugin_enabled,FALSE
    .else
        mov is_black_plugin_enabled,FALSE
    .endif
    ret

disable_plugin endp


enable_or_disable_plugin proc button:ptr GtkToggleButton, name:string_t

    .if (plugin_enabled(name))
        disable_plugin(name)
    .else
        enable_plugin(name)
    .endif
    ret

enable_or_disable_plugin endp



configure_plugins proc action:ptr GSimpleAction,
                       parameter:ptr GVariant,
                       user_data:gpointer

   .new error:ptr GError = NULL
   .new builder:ptr GtkBuilder = gtk_builder_new()

    gtk_builder_add_from_string(builder,
                               "<interface>"
                               "  <object class='GtkDialog' id='plugin-dialog'>"
                               "    <property name='title'>Plugins</property>"
                               "    <child internal-child='content_area'>"
                               "      <object class='GtkBox' id='content-area'>"
                               "        <property name='visible'>True</property>"
                               "        <property name='orientation'>vertical</property>"
                               "        <child>"
                               "          <object class='GtkCheckButton' id='red-plugin'>"
                               "            <property name='label' translatable='yes'>Red Plugin - turn your text red</property>"
                               "            <property name='visible'>True</property>"
                               "          </object>"
                               "        </child>"
                               "        <child>"
                               "          <object class='GtkCheckButton' id='black-plugin'>"
                               "            <property name='label' translatable='yes'>Black Plugin - turn your text black</property>"
                               "            <property name='visible'>True</property>"
                               "          </object>"
                               "        </child>"
                               "      </object>"
                               "    </child>"
                               "    <child internal-child='action_area'>"
                               "      <object class='GtkBox' id='action-area'>"
                               "        <property name='visible'>True</property>"
                               "        <child>"
                               "          <object class='GtkButton' id='close-button'>"
                               "            <property name='label' translatable='yes'>Close</property>"
                               "            <property name='visible'>True</property>"
                               "          </object>"
                               "        </child>"
                               "      </object>"
                               "    </child>"
                               "    <action-widgets>"
                               "      <action-widget response='-5'>close-button</action-widget>"
                               "    </action-widgets>"
                               "  </object>"
                               "</interface>", -1, &error)

    .if ( error )

        mov rcx,error
        g_warning("%s", [rcx].GError.message)
        g_error_free(error)
        jmp getout
    .endif

    .new dialog:ptr GtkWidget = gtk_builder_get_object(builder, "plugin-dialog")
    .new check:ptr GtkWidget = gtk_builder_get_object(builder, "red-plugin")
    .new enabled:gboolean = plugin_enabled("red")

    gtk_check_button_set_active(GTK_CHECK_BUTTON(check), enabled)
    g_signal_connect(check, "toggled", G_CALLBACK(enable_or_disable_plugin), "red")
    mov check,gtk_builder_get_object(builder, "black-plugin")
    mov enabled,plugin_enabled("black")
    gtk_check_button_set_active(GTK_CHECK_BUTTON(check), enabled)
    g_signal_connect(check, "toggled", G_CALLBACK(enable_or_disable_plugin), "black")

    g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_destroy), NULL)

    gtk_window_present(GTK_WINDOW(dialog))

getout:
    g_object_unref(builder)
    ret

configure_plugins endp

plug_man_startup proc application:ptr GApplication

   .new app_entries[3]:GActionEntry = {
        { "about", &show_about, NULL, NULL, NULL },
        { "quit", &quit_app, NULL, NULL, NULL },
        { "plugins", &configure_plugins, NULL, NULL, NULL } }

   .new applicationClass:ptr GApplicationClass = G_APPLICATION_CLASS(plug_man_parent_class)
    applicationClass.startup(application)

    g_action_map_add_action_entries(G_ACTION_MAP(application), &app_entries, G_N_ELEMENTS(app_entries), application)

   .new builder:ptr GtkBuilder = gtk_builder_new()
    gtk_builder_add_from_string(builder,
                               "<interface>"
                               "  <menu id='menubar'>"
                               "    <submenu>"
                               "      <attribute name='label' translatable='yes'>_Plugman</attribute>"
                               "      <section>"
                               "        <item>"
                               "          <attribute name='label' translatable='yes'>_About Plugman</attribute>"
                               "          <attribute name='action'>app.about</attribute>"
                               "        </item>"
                               "      </section>"
                               "      <section>"
                               "        <item>"
                               "          <attribute name='label' translatable='yes'>_Quit</attribute>"
                               "          <attribute name='action'>app.quit</attribute>"
                               "          <attribute name='accel'>&lt;Primary&gt;q</attribute>"
                               "        </item>"
                               "      </section>"
                               "    </submenu>"
                               "    <submenu>"
                               "      <attribute name='label' translatable='yes'>_Edit</attribute>"
                               "      <section>"
                               "        <item>"
                               "          <attribute name='label' translatable='yes'>_Copy</attribute>"
                               "          <attribute name='action'>win.copy</attribute>"
                               "        </item>"
                               "        <item>"
                               "          <attribute name='label' translatable='yes'>_Paste</attribute>"
                               "          <attribute name='action'>win.paste</attribute>"
                               "        </item>"
                               "      </section>"
                               "      <item><link name='section' id='plugins'>"
                               "      </link></item>"
                               "      <section>"
                               "        <item>"
                               "          <attribute name='label' translatable='yes'>Plugins</attribute>"
                               "          <attribute name='action'>app.plugins</attribute>"
                               "        </item>"
                               "      </section>"
                               "    </submenu>"
                               "    <submenu>"
                               "      <attribute name='label' translatable='yes'>_View</attribute>"
                               "      <section>"
                               "        <item>"
                               "          <attribute name='label' translatable='yes'>_Fullscreen</attribute>"
                               "          <attribute name='action'>win.fullscreen</attribute>"
                               "        </item>"
                               "      </section>"
                               "    </submenu>"
                               "  </menu>"
                               "</interface>", -1, NULL)

   .new object:ptr = gtk_builder_get_object(builder, "menubar")
    gtk_application_set_menubar(GTK_APPLICATION(application), object)
    mov object,gtk_builder_get_object(builder, "plugins")
    g_object_set_data_full(G_OBJECT(application), "plugin-menu", object, &g_object_unref)
    g_object_unref(builder)
    ret

plug_man_startup endp



plug_man_init proc app:ptr PlugMan
    ret
plug_man_init endp


plug_man_class_init proc uses rbx class:ptr PlugManClass

   .new application_class:ptr GApplicationClass
   .new object_class:ptr GObjectClass

    ldr rbx,class
    mov application_class,G_APPLICATION_CLASS(rbx)
    mov object_class,G_OBJECT_CLASS(rbx)

    mov rbx,application_class
    mov [rbx].GApplicationClass.startup,&plug_man_startup
    mov [rbx].GApplicationClass.activate,&plug_man_activate
    mov [rbx].GApplicationClass.open,&plug_man_open

    mov rbx,object_class
    mov [rbx].GObjectClass.finalize,&plug_man_finalize
    ret

plug_man_class_init endp

plug_man_new proc

    g_object_new(plug_man_get_type(), "application-id", "org.gtk.Test.plugman",
        "flags", G_APPLICATION_HANDLES_OPEN, NULL)
    ret

plug_man_new endp

main proc argc:int_t, argv:array_t

   .new accels[2]:string_t = { "F11", NULL }
   .new plug_man:ptr PlugMan = plug_man_new()
    gtk_application_set_accels_for_action(GTK_APPLICATION(plug_man),
                                         "win.fullscreen", &accels)
   .new status:int_t = g_application_run(G_APPLICATION(plug_man), argc, argv)
    g_object_unref(plug_man)
    mov eax,status
    ret

main endp

end _tstart
