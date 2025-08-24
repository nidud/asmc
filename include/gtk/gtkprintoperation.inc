ifndef __GTK_PRINT_OPERATION_H__
define __GTK_PRINT_OPERATION_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include cairo.inc
include gtk/gtkmain.inc
include gtk/gtkwindow.inc
include gtk/gtkpagesetup.inc
include gtk/gtkprintsettings.inc
include gtk/gtkprintcontext.inc
include gtk/gtkprintoperationpreview.inc

define GTK_TYPE_PRINT_OPERATION <gtk_print_operation_get_type ()>
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


GtkPrintOperation       struct
parent_instance         GObject <>
priv                    ptr GtkPrintOperationPrivate ?
GtkPrintOperation       ends

GtkPrintOperationClass  struct
parent_class            GObjectClass <>
done                    proc :ptr, :GtkPrintOperationResult
begin_print             proc :ptr, :ptr
paginate                proc :ptr, :ptr
request_page_setup      proc :ptr, :ptr, :sdword, :ptr
draw_page               proc :ptr, :ptr, :sdword
end_print               proc :ptr, :ptr
status_changed          proc :ptr
create_custom_widget    proc :ptr
custom_widget_apply     proc :ptr, :ptr
preview                 proc :ptr, :ptr, :ptr, :ptr
update_custom_widget    proc :ptr, :ptr, :ptr, :ptr
padding                 gpointer 8 dup(?)
GtkPrintOperationClass  ends

define GTK_PRINT_ERROR <gtk_print_error_quark ()>

.enum GtkPrintError {
  GTK_PRINT_ERROR_GENERAL,
  GTK_PRINT_ERROR_INTERNAL_ERROR,
  GTK_PRINT_ERROR_NOMEM,
  GTK_PRINT_ERROR_INVALID_FILE
}

gtk_print_error_quark proto

gtk_print_operation_get_type proto
gtk_print_operation_new proto
gtk_print_operation_set_default_page_setup proto :ptr, :ptr
gtk_print_operation_get_default_page_setup proto :ptr
gtk_print_operation_set_print_settings proto :ptr, :ptr
gtk_print_operation_get_print_settings proto :ptr
gtk_print_operation_set_job_name proto :ptr, :ptr
gtk_print_operation_set_n_pages proto :ptr, :sdword
gtk_print_operation_set_current_page proto :ptr, :sdword
gtk_print_operation_set_use_full_page proto :ptr, :gboolean
gtk_print_operation_set_unit proto :ptr, :GtkUnit
gtk_print_operation_set_export_filename proto :ptr, :ptr
gtk_print_operation_set_track_print_status proto :ptr, :gboolean
gtk_print_operation_set_show_progress proto :ptr, :gboolean
gtk_print_operation_set_allow_async proto :ptr, :gboolean
gtk_print_operation_set_custom_tab_label proto :ptr, :ptr
gtk_print_operation_run proto :ptr, :GtkPrintOperationAction, :ptr, :ptr
gtk_print_operation_get_error proto :ptr, :ptr
gtk_print_operation_get_status proto :ptr
gtk_print_operation_get_status_string proto :ptr
gtk_print_operation_is_finished proto :ptr
gtk_print_operation_cancel proto :ptr
gtk_print_operation_draw_page_finish proto :ptr
gtk_print_operation_set_defer_drawing proto :ptr
gtk_print_operation_set_support_selection proto :ptr, :gboolean
gtk_print_operation_get_support_selection proto :ptr
gtk_print_operation_set_has_selection proto :ptr, :gboolean
gtk_print_operation_get_has_selection proto :ptr
gtk_print_operation_set_embed_page_setup proto :ptr, :gboolean
gtk_print_operation_get_embed_page_setup proto :ptr
gtk_print_operation_get_n_pages_to_print proto :ptr

gtk_print_run_page_setup_dialog proto :ptr, :ptr, :ptr

CALLBACK(GtkPageSetupDoneFunc, :ptr, :gpointer)

gtk_print_run_page_setup_dialog_async proto :ptr, :ptr, :ptr, :GtkPageSetupDoneFunc, :gpointer

endif
