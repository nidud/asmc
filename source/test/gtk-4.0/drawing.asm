include gtk/gtk.inc
include tchar.inc

;; Surface to store current scribbles

.data
 surface ptr cairo_surface_t NULL

.code

clear_surface proc

   .new cr:ptr cairo_t = cairo_create(surface)

    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0)
    cairo_paint(cr)
    cairo_destroy(cr)
    ret

clear_surface endp

;; Create a new surface of the appropriate size to store our scribbles

resize_cb proc widget:ptr GtkWidget, width:int_t, height:int_t, data:gpointer

    .if ( surface )

        cairo_surface_destroy(surface)
        mov surface,NULL
    .endif
    .new native_surface:ptr cairo_surface_t = gtk_native_get_surface(gtk_widget_get_native(widget))

    .if ( native_surface  )

       .new w:int_t = gtk_widget_get_width(widget)
       .new h:int_t = gtk_widget_get_height(widget)
        mov surface,gdk_surface_create_similar_surface(native_surface, CAIRO_CONTENT_COLOR, w, h)

        ;; Initialize the surface to white

        clear_surface ()
    .endif
    ret

resize_cb endp


;; Redraw the screen from the surface. Note that the draw
;; callback receives a ready-to-be-used cairo_t that is already
;; clipped to only draw the exposed areas of the widget

draw_cb proc drawing_area:ptr GtkDrawingArea, cr:ptr cairo_t, width:int_t, height:int_t, data:gpointer

    cairo_set_source_surface (cr, surface, 0.0, 0.0)
    cairo_paint (cr)
    ret

draw_cb endp

;; Draw a rectangle on the surface at the given position

draw_brush proc widget:ptr GtkWidget, _x:double, _y:double

    ;; Paint to the surface, where we store our state

    subsd xmm1,3.0
ifdef __UNIX__
    subsd xmm0,3.0
   .new x:double = xmm0
   .new y:double = xmm1
else
    subsd xmm2,3.0
   .new x:double = xmm1
   .new y:double = xmm2
endif

   .new cr:ptr cairo_t = cairo_create(surface)

    cairo_rectangle(cr, x, y, 6.0, 6.0)
    cairo_fill(cr)
    cairo_destroy(cr)

    ;; Now invalidate the drawing area.

    gtk_widget_queue_draw(widget)
    ret

draw_brush endp

.data
 start_x double 0.0
 start_y double 0.0

.code

drag_begin proc gesture:ptr GtkGestureDrag, x:double, y:double, area:ptr GtkWidget

ifdef __UNIX__
    movsd start_x,xmm0
    movsd start_y,xmm1
    draw_brush (area, xmm0, xmm1)
else
    movsd start_x,xmm1
    movsd start_y,xmm2
    draw_brush (area, xmm1, xmm2)
endif
    ret

drag_begin endp


drag_update proc gesture:ptr GtkGestureDrag, x:double, y:double, area:ptr GtkWidget

ifdef __UNIX__
    addsd xmm0,start_x
    addsd xmm1,start_y
    draw_brush(area, xmm0, xmm1)
else
    addsd xmm1,start_x
    addsd xmm2,start_y
    draw_brush (area, xmm1, xmm2)
endif
    ret

drag_update endp


drag_end proc gesture:ptr GtkGestureDrag, x:double, y:double, area:ptr GtkWidget

ifdef __UNIX__
    addsd xmm0,start_x
    addsd xmm1,start_y
    draw_brush (area, xmm0, xmm1)
else
    addsd xmm1,start_x
    addsd xmm2,start_y
    draw_brush (area, xmm1, xmm2)
endif
    ret

drag_end endp


pressed proc gesture:ptr GtkGestureClick, n_press:int_t, x:double, y:double, area:ptr GtkWidget

    clear_surface()
    gtk_widget_queue_draw(area)
    ret

pressed endp


close_window proc

    .if ( surface )

        cairo_surface_destroy(surface)
        mov surface,NULL
    .endif
    ret

close_window endp


activate proc app:ptr GtkApplication, user_data:gpointer

   .new window:ptr GtkWidget = gtk_application_window_new(app)
    gtk_window_set_title(GTK_WINDOW(window), "Drawing Area")

    g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL)

   .new drawing_area:ptr GtkWidget = gtk_drawing_area_new()

    ;; set a minimum size

    gtk_widget_set_size_request(drawing_area, 100, 100)
    gtk_window_set_child(GTK_WINDOW(window), drawing_area)

    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), G_CALLBACK(draw_cb), NULL, NULL)
    g_signal_connect_after(drawing_area, "resize", G_CALLBACK(resize_cb), NULL)

   .new drag:ptr GtkGesture = gtk_gesture_drag_new()
    gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(drag), GDK_BUTTON_PRIMARY)
    gtk_widget_add_controller(drawing_area, GTK_EVENT_CONTROLLER(drag))
    g_signal_connect(drag, "drag-begin", G_CALLBACK(drag_begin), drawing_area)
    g_signal_connect(drag, "drag-update", G_CALLBACK(drag_update), drawing_area)
    g_signal_connect(drag, "drag-end", G_CALLBACK(drag_end), drawing_area)

   .new press:ptr GtkGesture = gtk_gesture_click_new()
    gtk_gesture_single_set_button (GTK_GESTURE_SINGLE(press), GDK_BUTTON_SECONDARY)
    gtk_widget_add_controller(drawing_area, GTK_EVENT_CONTROLLER(press))

    g_signal_connect(press, "pressed", G_CALLBACK(pressed), drawing_area)
    gtk_widget_show(window)
    ret

activate endp


main proc argc:int_t, argv:array_t

   .new application:ptr GtkApplication
   .new status:int_t

    mov application,gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE)
    g_signal_connect(application, "activate", G_CALLBACK(activate), NULL)
    mov status,g_application_run(G_APPLICATION(application), argc, argv)
    g_object_unref(application)
    mov eax,status
    ret

main endp

end _tstart
