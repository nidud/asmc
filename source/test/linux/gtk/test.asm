; build:
; asmc64 test.asm
; gcc -o test test.o `pkg-config --cflags --libs gtk+-3.0`

include stdio.inc
include gtk/gtk.inc

.code

main proc _argc:int_t, _argv:array_t

  local argc    :int_t,
        argv    :array_t,
        window  :ptr GtkWidget,
        table   :ptr GtkWidget,
        tlabel  :ptr GtkWidget,
        button  :ptr GtkWidget

    mov argc,edi
    mov argv,rsi
    .ifd !gtk_init_check(&argc, &argv)
        perror("gtk_init_check")
        .return 1
    .endif
    .if !gtk_window_new(0)
        perror("gtk_window_new")
        .return 1
    .endif
    mov window,rax
    gtk_window_set_title(window, "Hello Linux!")
    mov table,gtk_table_new(15, 15, 1)
    gtk_container_add(window, table)
    mov tlabel,gtk_label_new("Asmc gtk example")
    gtk_table_attach_defaults(table, tlabel, 1, 8, 3, 7)
    mov button,gtk_button_new_from_stock("gtk-quit")
    gtk_table_attach_defaults(table, button, 10, 14, 12, 14)
    gtk_widget_show_all(window)
    g_signal_connect_data(window, "delete-event", &exit_prog, 0, 0, 0)
    g_signal_connect_data(button, "clicked", &exit_prog, 0, 0, 0)
    gtk_main()
    ret

main endp

exit_prog proc
    gtk_main_quit()
exit_prog endp

    end
