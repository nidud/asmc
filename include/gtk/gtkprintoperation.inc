ifndef __GTK_PRINT_OPERATION_H__
__GTK_PRINT_OPERATION_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

;include cairo.inc
include gtk/gtkmain.inc
include gtk/gtkwindow.inc
include gtk/gtkpagesetup.inc
include gtk/gtkprintsettings.inc
include gtk/gtkprintcontext.inc
include gtk/gtkprintoperationpreview.inc

G_BEGIN_DECLS

GTK_TYPE_PRINT_OPERATION equ <gtk_print_operation_get_type>
GTK_PRINT_OPERATION macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_PRINT_OPERATION, GtkPrintOperation))>
	endm
GTK_PRINT_OPERATION_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_PRINT_OPERATION, GtkPrintOperationClass))>
	endm
GTK_IS_PRINT_OPERATION macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_PRINT_OPERATION))>
	endm
GTK_IS_PRINT_OPERATION_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_PRINT_OPERATION))>
	endm
GTK_PRINT_OPERATION_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_PRINT_OPERATION, GtkPrintOperationClass))>
	endm

.enum GtkPrintStatus {
  GTK_PRINT_STATUS_INITIAL,
  GTK_PRINT_STATUS_PREPARING,
  GTK_PRINT_STATUS_GENERATING_DATA,
  GTK_PRINT_STATUS_SENDING_DATA,
  GTK_PRINT_STATUS_PENDING,
  GTK_PRINT_STATUS_PENDING_ISSUE,
  GTK_PRINT_STATUS_PRINTING,
  GTK_PRINT_STATUS_FINISHED,
  GTK_PRINT_STATUS_FINISHED_ABORTED
}

.enum GtkPrintOperationResult {
  GTK_PRINT_OPERATION_RESULT_ERROR,
  GTK_PRINT_OPERATION_RESULT_APPLY,
  GTK_PRINT_OPERATION_RESULT_CANCEL,
  GTK_PRINT_OPERATION_RESULT_IN_PROGRESS
}

.enum GtkPrintOperationAction {
  GTK_PRINT_OPERATION_ACTION_PRINT_DIALOG,
  GTK_PRINT_OPERATION_ACTION_PRINT,
  GTK_PRINT_OPERATION_ACTION_PREVIEW,
  GTK_PRINT_OPERATION_ACTION_EXPORT
}

GtkPrintOperation	STRUC
parent_instance		GObject <>
priv			ptr_t ?
GtkPrintOperation	ENDS

GtkPrintOperationClass	STRUC
parent_class		GObjectClass <>
done			proc :ptr GtkPrintOperation, :ptr GtkPrintOperationResult
begin_print		proc :ptr GtkPrintOperation, :ptr GtkPrintContext
paginate		proc :ptr GtkPrintOperation, :ptr GtkPrintContext
request_page_setup	proc :ptr GtkPrintOperation, :ptr GtkPrintContext, :gint, :ptr GtkPageSetup
draw_page		proc :ptr GtkPrintOperation, :ptr GtkPrintContext, :gint
end_print		proc :ptr GtkPrintOperation, :ptr GtkPrintContext
status_changed		proc :ptr GtkPrintOperation
create_custom_widget	proc :ptr GtkPrintOperation
custom_widget_apply	proc :ptr GtkPrintOperation, :ptr GtkWidget
preview			proc :ptr GtkPrintOperation, :ptr GtkPrintOperationPreview, :ptr GtkPrintContext, :ptr GtkWindow
update_custom_widget	proc :ptr GtkPrintOperation, :ptr GtkWidget, :ptr GtkPageSetup, :ptr GtkPrintSettings
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
_gtk_reserved6		proc
_gtk_reserved7		proc
_gtk_reserved8		proc
GtkPrintOperationClass	ENDS

GTK_PRINT_ERROR		equ <gtk_print_error_quark>

.enum GtkPrintError {
  GTK_PRINT_ERROR_GENERAL,
  GTK_PRINT_ERROR_INTERNAL_ERROR,
  GTK_PRINT_ERROR_NOMEM,
  GTK_PRINT_ERROR_INVALID_FILE
}

;GQuark
gtk_print_error_quark proto __cdecl

;GType
gtk_print_operation_get_type proto __cdecl
;GtkPrintOperation
gtk_print_operation_new proto __cdecl
;void
gtk_print_operation_set_default_page_setup proto __cdecl \
		    op: ptr GtkPrintOperation,
    default_page_setup: ptr GtkPageSetup

;GtkPageSetup
gtk_print_operation_get_default_page_setup proto __cdecl \
		    op: ptr GtkPrintOperation

;void
gtk_print_operation_set_print_settings proto __cdecl \
		    op: ptr GtkPrintOperation,
	print_settings: ptr GtkPrintSettings

;GtkPrintSettings
gtk_print_operation_get_print_settings proto __cdecl \
		    op: ptr GtkPrintOperation

;void
gtk_print_operation_set_job_name proto __cdecl \
		    op: ptr GtkPrintOperation,
	      job_name: ptr gchar

;void
gtk_print_operation_set_n_pages proto __cdecl \
		    op: ptr GtkPrintOperation,
	       n_pages: gint

;void
gtk_print_operation_set_current_page proto __cdecl \
		    op: ptr GtkPrintOperation,
	  current_page: gint

;void
gtk_print_operation_set_use_full_page proto __cdecl \
		    op: ptr GtkPrintOperation,
	     full_page: gboolean

;void
gtk_print_operation_set_unit proto __cdecl \
		    op: ptr GtkPrintOperation,
		  unit: GtkUnit

;void
gtk_print_operation_set_export_filename proto __cdecl \
		    op: ptr GtkPrintOperation,
	      filename: ptr gchar

;void
gtk_print_operation_set_track_print_status proto __cdecl \
		    op: ptr GtkPrintOperation,
	  track_status: gboolean

;void
gtk_print_operation_set_show_progress proto __cdecl \
		    op: ptr GtkPrintOperation,
	 show_progress: gboolean

;void
gtk_print_operation_set_allow_async proto __cdecl \
		    op: ptr GtkPrintOperation,
	   allow_async: gboolean

;void
gtk_print_operation_set_custom_tab_label proto __cdecl \
		    op: ptr GtkPrintOperation,
		_label: ptr gchar

;GtkPrintOperationResult
gtk_print_operation_run proto __cdecl \
		    op: ptr GtkPrintOperation,
		action: GtkPrintOperationAction,
		parent: ptr GtkWindow,
		 error: ptr GError

;void
gtk_print_operation_get_error proto __cdecl \
		    op: ptr GtkPrintOperation,
		 error: ptr GError

;GtkPrintStatus
gtk_print_operation_get_status proto __cdecl \
		    op: ptr GtkPrintOperation

;const
gtk_print_operation_get_status_string proto __cdecl \
		    op: ptr GtkPrintOperation

;gboolean
gtk_print_operation_is_finished proto __cdecl \
		    op: ptr GtkPrintOperation

;void
gtk_print_operation_cancel proto __cdecl \
		    op: ptr GtkPrintOperation

;void
gtk_print_operation_draw_page_finish proto __cdecl \
		    op: ptr GtkPrintOperation

;void
gtk_print_operation_set_defer_drawing proto __cdecl \
		    op: ptr GtkPrintOperation

;void
gtk_print_operation_set_support_selection proto __cdecl \
		    op: ptr GtkPrintOperation,
     support_selection: gboolean

;gboolean
gtk_print_operation_get_support_selection proto __cdecl \
		    op: ptr GtkPrintOperation

;void
gtk_print_operation_set_has_selection proto __cdecl \
		    op: ptr GtkPrintOperation,
	 has_selection: gboolean

;gboolean
gtk_print_operation_get_has_selection proto __cdecl \
		    op: ptr GtkPrintOperation

;void
gtk_print_operation_set_embed_page_setup proto __cdecl \
		    op: ptr GtkPrintOperation,
		 embed: gboolean

;gboolean
gtk_print_operation_get_embed_page_setup proto __cdecl \
		    op: ptr GtkPrintOperation

;gint
gtk_print_operation_get_n_pages_to_print proto __cdecl \
		    op: ptr GtkPrintOperation


;GtkPageSetup
gtk_print_run_page_setup_dialog proto __cdecl \
		parent: ptr GtkWindow,
	    page_setup: ptr GtkPageSetup,
	      settings: ptr GtkPrintSettings


CALLBACKC(GtkPageSetupDoneFunc, :ptr GtkPageSetup, :gpointer)

;void
gtk_print_run_page_setup_dialog_async proto __cdecl \
		parent: ptr GtkWindow,
	    page_setup: ptr GtkPageSetup,
	      settings: ptr GtkPrintSettings,
	       done_cb: GtkPageSetupDoneFunc,
		  data: gpointer


G_END_DECLS

endif
