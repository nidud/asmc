include gtk/gtk.inc
include tchar.inc

.code

action_activated proc action:ptr GSimpleAction, parameter:ptr GVariant, user_data:gpointer

   .new dialog:ptr GtkWidget = gtk_message_dialog_new(user_data,
                                                      GTK_DIALOG_DESTROY_WITH_PARENT,
                                                      GTK_MESSAGE_INFO,
                                                      GTK_BUTTONS_CLOSE,
                                                      "Activated action `%s`",
                                                      g_action_get_name(action))

    g_signal_connect_swapped(dialog, "response", &gtk_window_destroy, dialog)
    gtk_widget_show(dialog)
    ret

action_activated endp

.data
 doc_entries GActionEntry \
  { @CStr("save"), action_activated },
  { @CStr("print"), action_activated },
  { @CStr("share"), action_activated }

 win_entries GActionEntry \
  { @CStr("fullscreen"), action_activated },
  { @CStr("close"), action_activated }

 menu_ui string_t @CStr(
  "<interface>"
  "  <menu id='doc-menu'>"
  "    <section>"
  "      <item>"
  "        <attribute name='label'>_Save</attribute>"
  "        <attribute name='action'>save</attribute>"
  "      </item>"
  "      <item>"
  "        <attribute name='label'>_Print</attribute>"
  "        <attribute name='action'>print</attribute>"
  "      </item>"
  "      <item>"
  "        <attribute name='label'>_Share</attribute>"
  "        <attribute name='action'>share</attribute>"
  "      </item>"
  "    </section>"
  "  </menu>"
  "  <menu id='win-menu'>"
  "    <section>"
  "      <item>"
  "        <attribute name='label'>_Fullscreen</attribute>"
  "        <attribute name='action'>fullscreen</attribute>"
  "      </item>"
  "      <item>"
  "        <attribute name='label'>_Close</attribute>"
  "        <attribute name='action'>close</attribute>"
  "      </item>"
  "    </section>"
  "  </menu>"
  "</interface>" )

.code

activate proc application:ptr GApplication, user_data:gpointer

    .if ( gtk_application_get_windows(GTK_APPLICATION(application)) != NULL )

        .return
    .endif

   .new win:ptr GtkWidget = gtk_application_window_new(GTK_APPLICATION(application))
    gtk_window_set_default_size(GTK_WINDOW(win), 200, 300)

   .new doc_actions:ptr GSimpleActionGroup = g_simple_action_group_new()
    g_action_map_add_action_entries(G_ACTION_MAP(doc_actions), &doc_entries,
                                    G_N_ELEMENTS(doc_entries), win)

    g_action_map_add_action_entries(G_ACTION_MAP(win), &win_entries,
                                    G_N_ELEMENTS(win_entries), win)

   .new builder:ptr GtkBuilder = gtk_builder_new()
    gtk_builder_add_from_string(builder, menu_ui, -1, NULL)

   .new doc_menu:ptr GMenuModel = gtk_builder_get_object(builder, "doc-menu")
   .new win_menu:ptr GMenuModel = gtk_builder_get_object(builder, "win-menu")

   .new button_menu:ptr GMenu = g_menu_new()
   .new section:ptr GMenuItem = g_menu_item_new_section(NULL, doc_menu)
    g_menu_item_set_attribute(section, "action-namespace", "s", "doc")
    g_menu_append_item(button_menu, section)
    g_object_unref(section)

    mov section,g_menu_item_new_section(NULL, win_menu)
    g_menu_item_set_attribute(section, "action-namespace", "s", "win")
    g_menu_append_item(button_menu, section)
    g_object_unref(section)

   .new button:ptr GtkWidget = gtk_menu_button_new()
    gtk_button_set_label(GTK_MENU_BUTTON(button), "Menu")
    gtk_widget_insert_action_group(button, "doc", G_ACTION_GROUP(doc_actions))
    gtk_menu_button_set_menu_model(button, G_MENU_MODEL(button_menu))
    gtk_widget_set_halign(GTK_WIDGET(button), GTK_ALIGN_CENTER)
    gtk_widget_set_valign(GTK_WIDGET(button), GTK_ALIGN_START)
    gtk_window_set_child(GTK_WINDOW(win), button)
    gtk_widget_show(win)

    g_object_unref(button_menu)
    g_object_unref(doc_actions)
    g_object_unref(builder)
    ret

activate endp


main proc argc:int_t, argv:array_t

   .new application:ptr GtkApplication = gtk_application_new("org.gtk.Example", 0)

    g_signal_connect(application, "activate", G_CALLBACK(activate), NULL)
    g_application_run(G_APPLICATION(application), argc, argv)
    ret

main endp

end _tstart
