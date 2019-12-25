ifndef __GTK_MAIN_H__
__GTK_MAIN_H__ equ <>


if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
;include gtk/gtkwidget.inc
ifdef G_PLATFORM_WIN32
;include gtk/gtkbox.inc
;include gtk/gtkwindow.inc
endif

;G_BEGIN_DECLS

GTK_PRIORITY_RESIZE	equ (G_PRIORITY_HIGH_IDLE + 10)

CALLBACKC(GtkKeySnoopFunc, :ptr GtkWidget, :ptr GdkEventKey, :gpointer)

;guint
gtk_get_major_version proto __cdecl
gtk_get_minor_version proto __cdecl
gtk_get_micro_version proto __cdecl
gtk_get_binary_age proto __cdecl
gtk_get_interface_age proto __cdecl

gtk_major_version	equ <gtk_get_major_version>
gtk_minor_version	equ <gtk_get_minor_version>
gtk_micro_version	equ <gtk_get_micro_version>
gtk_binary_age		equ <gtk_get_binary_age>
gtk_interface_age	equ <gtk_get_interface_age>

gtk_check_version proto __cdecl \
	required_major: guint,
	required_minor: guint,
	required_micro: guint




;gboolean
gtk_parse_args proto __cdecl \
		  argc: ptr int_t,
		  argv: ptr char_t


;void
gtk_init proto __cdecl \
		  argc: ptr int_t,
		  argv: ptr char_t


;gboolean
gtk_init_check proto __cdecl \
		  argc: ptr int_t,
		  argv: ptr char_t


;gboolean
gtk_init_with_args proto __cdecl \
		  argc: ptr gint,
		  argv: ptr gchar,
      parameter_string: ptr gchar,
	       entries: ptr GOptionEntry,
    translation_domain: ptr gchar,
		 error: ptr GError


;GOptionGroup
gtk_get_option_group proto __cdecl \
  open_default_display: gboolean


ifdef G_OS_WIN32

;void
gtk_init_abi_check proto __cdecl \
		  argc: ptr int_t,
		  argv: ptr char_t,
	    num_checks: int_t,
      sizeof_GtkWindow: size_t,
	 sizeof_GtkBox: size_t

;gboolean
gtk_init_check_abi_check proto __cdecl \
		  argc: ptr int_t,
		  argv: ptr char_t,
	    num_checks: int_t,
      sizeof_GtkWindow: size_t,
	 sizeof_GtkBox: size_t


gtk_init macro argc, argv
	exitm<gtk_init_abi_check (argc, argv, 2, sizeof (GtkWindow), sizeof (GtkBox))>
	endm
gtk_init_check macro argc, argv
	exitm<gtk_init_check_abi_check (argc, argv, 2, sizeof (GtkWindow), sizeof (GtkBox))>
	endm

endif

;void
gtk_disable_setlocale proto __cdecl
;PangoLanguage
gtk_get_default_language proto __cdecl
;GtkTextDirection
gtk_get_locale_direction proto __cdecl
;gboolean
gtk_events_pending proto __cdecl

;void
gtk_main_do_event proto __cdecl \
		 event: ptr GdkEvent

;void
gtk_main proto __cdecl
;guint
gtk_main_level proto __cdecl
;void
gtk_main_quit proto __cdecl
;gboolean
gtk_main_iteration proto __cdecl
;gboolean
gtk_main_iteration_do proto __cdecl \
	      blocking: gboolean


;gboolean
gtk_true proto __cdecl
;gboolean
gtk_false proto __cdecl

;void
gtk_grab_add proto __cdecl \
		widget: ptr GtkWidget

;GtkWidget*
gtk_grab_get_current proto __cdecl
;void
gtk_grab_remove proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_device_grab_add proto __cdecl \
		widget: ptr GtkWidget,
		device: ptr GdkDevice,
	  block_others: gboolean

;void
gtk_device_grab_remove proto __cdecl \
		widget: ptr GtkWidget,
		device: ptr GdkDevice


;guint
gtk_key_snooper_install proto __cdecl \
	       snooper: GtkKeySnoopFunc,
	     func_data: gpointer

;void
gtk_key_snooper_remove proto __cdecl \
    snooper_handler_id: guint


;GdkEvent
gtk_get_current_event proto __cdecl
;guint32
gtk_get_current_event_time proto __cdecl
;gboolean
gtk_get_current_event_state proto __cdecl \
		 state: ptr GdkModifierType

;GdkDevice
gtk_get_current_event_device proto __cdecl

;GtkWidget
gtk_get_event_widget proto __cdecl \
		 event: ptr GdkEvent


;void
gtk_propagate_event proto __cdecl \
		widget: ptr GtkWidget,
		 event: ptr GdkEvent



;G_END_DECLS

endif
