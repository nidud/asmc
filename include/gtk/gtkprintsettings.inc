ifndef __GTK_PRINT_SETTINGS_H__
__GTK_PRINT_SETTINGS_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkpapersize.inc

G_BEGIN_DECLS

GTK_TYPE_PRINT_SETTINGS equ <gtk_print_settings_get_type>
GTK_PRINT_SETTINGS macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_PRINT_SETTINGS, GtkPrintSettings))>
	endm
GTK_IS_PRINT_SETTINGS macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_PRINT_SETTINGS))>
	endm

CALLBACKC(GtkPrintSettingsFunc, :ptr gchar, :ptr, :gpointer)

GtkPageRange		STRUC
start			gint ?
_end			gint ?
GtkPageRange		ENDS

;GType
gtk_print_settings_get_type proto __cdecl
;GtkPrintSettings
gtk_print_settings_new proto __cdecl

;GtkPrintSettings
gtk_print_settings_copy proto __cdecl \
		 other: ptr GtkPrintSettings


;GtkPrintSettings
gtk_print_settings_new_from_file proto __cdecl \
	     file_name: ptr gchar,
		 error: ptr GError

;gboolean
gtk_print_settings_load_file proto __cdecl \
	      settings: ptr GtkPrintSettings,
	     file_name: ptr gchar,
		 error: ptr GError

;gboolean
gtk_print_settings_to_file proto __cdecl \
	      settings: ptr GtkPrintSettings,
	     file_name: ptr gchar,
		 error: ptr GError

;GtkPrintSettings
gtk_print_settings_new_from_key_file proto __cdecl \
	      key_file: ptr GKeyFile,
	    group_name: ptr gchar,
		 error: ptr GError

;gboolean
gtk_print_settings_load_key_file proto __cdecl \
	      settings: ptr GtkPrintSettings,
	      key_file: ptr GKeyFile,
	    group_name: ptr gchar,
		 error: ptr GError

;void
gtk_print_settings_to_key_file proto __cdecl \
	      settings: ptr GtkPrintSettings,
	      key_file: ptr GKeyFile,
	    group_name: ptr gchar

;gboolean
gtk_print_settings_has_key proto __cdecl \
	      settings: ptr GtkPrintSettings,
		   key: ptr gchar

;const
gtk_print_settings_get proto __cdecl \
	      settings: ptr GtkPrintSettings,
		   key: ptr gchar

;void
gtk_print_settings_set proto __cdecl \
	      settings: ptr GtkPrintSettings,
		   key: ptr gchar,
		 value: ptr gchar

;void
gtk_print_settings_unset proto __cdecl \
	      settings: ptr GtkPrintSettings,
		   key: ptr gchar

;void
gtk_print_settings_foreach proto __cdecl \
	      settings: ptr GtkPrintSettings,
		  func: GtkPrintSettingsFunc,
	     user_data: gpointer

;gboolean
gtk_print_settings_get_bool proto __cdecl \
	      settings: ptr GtkPrintSettings,
		   key: ptr gchar

;void
gtk_print_settings_set_bool proto __cdecl \
	      settings: ptr GtkPrintSettings,
		   key: ptr gchar,
		 value: gboolean

;gdouble
gtk_print_settings_get_double proto __cdecl \
	      settings: ptr GtkPrintSettings,
		   key: ptr gchar

;gdouble
gtk_print_settings_get_double_with_default proto __cdecl \
	      settings: ptr GtkPrintSettings,
		   key: ptr gchar,
		   def: gdouble

;void
gtk_print_settings_set_double proto __cdecl \
	      settings: ptr GtkPrintSettings,
		   key: ptr gchar,
		 value: gdouble

;gdouble
gtk_print_settings_get_length proto __cdecl \
	      settings: ptr GtkPrintSettings,
		   key: ptr gchar,
		  unit: GtkUnit

;void
gtk_print_settings_set_length proto __cdecl \
	      settings: ptr GtkPrintSettings,
		   key: ptr gchar,
		 value: gdouble,
		  unit: GtkUnit

;gint
gtk_print_settings_get_int proto __cdecl \
	      settings: ptr GtkPrintSettings,
		   key: ptr gchar

;gint
gtk_print_settings_get_int_with_default proto __cdecl \
	      settings: ptr GtkPrintSettings,
		   key: ptr gchar,
		   def: gint

;void
gtk_print_settings_set_int proto __cdecl \
	      settings: ptr GtkPrintSettings,
		   key: ptr gchar,
		 value: gint


GTK_PRINT_SETTINGS_PRINTER equ <"printer">
GTK_PRINT_SETTINGS_ORIENTATION equ <"orientation">
GTK_PRINT_SETTINGS_PAPER_FORMAT equ <"paper-format">
GTK_PRINT_SETTINGS_PAPER_WIDTH equ <"paper-width">
GTK_PRINT_SETTINGS_PAPER_HEIGHT equ <"paper-height">
GTK_PRINT_SETTINGS_N_COPIES equ <"n-copies">
GTK_PRINT_SETTINGS_DEFAULT_SOURCE equ <"default-source">
GTK_PRINT_SETTINGS_QUALITY equ <"quality">
GTK_PRINT_SETTINGS_RESOLUTION equ <"resolution">
GTK_PRINT_SETTINGS_USE_COLOR equ <"use-color">
GTK_PRINT_SETTINGS_DUPLEX equ <"duplex">
GTK_PRINT_SETTINGS_COLLATE equ <"collate">
GTK_PRINT_SETTINGS_REVERSE equ <"reverse">
GTK_PRINT_SETTINGS_MEDIA_TYPE equ <"media-type">
GTK_PRINT_SETTINGS_DITHER equ <"dither">
GTK_PRINT_SETTINGS_SCALE equ <"scale">
GTK_PRINT_SETTINGS_PRINT_PAGES equ <"print-pages">
GTK_PRINT_SETTINGS_PAGE_RANGES equ <"page-ranges">
GTK_PRINT_SETTINGS_PAGE_SET equ <"page-set">
GTK_PRINT_SETTINGS_FINISHINGS equ <"finishings">
GTK_PRINT_SETTINGS_NUMBER_UP equ <"number-up">
GTK_PRINT_SETTINGS_NUMBER_UP_LAYOUT equ <"number-up-layout">
GTK_PRINT_SETTINGS_OUTPUT_BIN equ <"output-bin">
GTK_PRINT_SETTINGS_RESOLUTION_X equ <"resolution-x">
GTK_PRINT_SETTINGS_RESOLUTION_Y equ <"resolution-y">
GTK_PRINT_SETTINGS_PRINTER_LPI equ <"printer-lpi">

GTK_PRINT_SETTINGS_OUTPUT_DIR equ <"output-dir">

GTK_PRINT_SETTINGS_OUTPUT_BASENAME equ <"output-basename">

GTK_PRINT_SETTINGS_OUTPUT_FILE_FORMAT equ <"output-file-format">

GTK_PRINT_SETTINGS_OUTPUT_URI equ <"output-uri">

GTK_PRINT_SETTINGS_WIN32_DRIVER_VERSION equ <"win32-driver-version">
GTK_PRINT_SETTINGS_WIN32_DRIVER_EXTRA equ <"win32-driver-extra">


;const
gtk_print_settings_get_printer proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_printer proto __cdecl \
	      settings: ptr GtkPrintSettings,
	       printer: ptr gchar

;GtkPageOrientation
gtk_print_settings_get_orientation proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_orientation proto __cdecl \
	      settings: ptr GtkPrintSettings,
	   orientation: GtkPageOrientation

;GtkPaperSize
gtk_print_settings_get_paper_size proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_paper_size proto __cdecl \
	      settings: ptr GtkPrintSettings,
	    paper_size: ptr GtkPaperSize

;gdouble
gtk_print_settings_get_paper_width proto __cdecl \
	      settings: ptr GtkPrintSettings,
		  unit: GtkUnit

;void
gtk_print_settings_set_paper_width proto __cdecl \
	      settings: ptr GtkPrintSettings,
		 width: gdouble,
		  unit: GtkUnit

;gdouble
gtk_print_settings_get_paper_height proto __cdecl \
	      settings: ptr GtkPrintSettings,
		  unit: GtkUnit

;void
gtk_print_settings_set_paper_height proto __cdecl \
	      settings: ptr GtkPrintSettings,
		height: gdouble,
		  unit: GtkUnit

;gboolean
gtk_print_settings_get_use_color proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_use_color proto __cdecl \
	      settings: ptr GtkPrintSettings,
	     use_color: gboolean

;gboolean
gtk_print_settings_get_collate proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_collate proto __cdecl \
	      settings: ptr GtkPrintSettings,
	       collate: gboolean

;gboolean
gtk_print_settings_get_reverse proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_reverse proto __cdecl \
	      settings: ptr GtkPrintSettings,
	       reverse: gboolean

;GtkPrintDuplex
gtk_print_settings_get_duplex proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_duplex proto __cdecl \
	      settings: ptr GtkPrintSettings,
		duplex: GtkPrintDuplex

;GtkPrintQuality
gtk_print_settings_get_quality proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_quality proto __cdecl \
	      settings: ptr GtkPrintSettings,
	       quality: GtkPrintQuality

;gint
gtk_print_settings_get_n_copies proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_n_copies proto __cdecl \
	      settings: ptr GtkPrintSettings,
	    num_copies: gint

;gint
gtk_print_settings_get_number_up proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_number_up proto __cdecl \
	      settings: ptr GtkPrintSettings,
	     number_up: gint

;GtkNumberUpLayout
gtk_print_settings_get_number_up_layout proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_number_up_layout proto __cdecl \
	      settings: ptr GtkPrintSettings,
      number_up_layout: GtkNumberUpLayout

;gint
gtk_print_settings_get_resolution proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_resolution proto __cdecl \
	      settings: ptr GtkPrintSettings,
	    resolution: gint

;gint
gtk_print_settings_get_resolution_x proto __cdecl \
	      settings: ptr GtkPrintSettings

;gint
gtk_print_settings_get_resolution_y proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_resolution_xy proto __cdecl \
	      settings: ptr GtkPrintSettings,
	  resolution_x: gint,
	  resolution_y: gint

;gdouble
gtk_print_settings_get_printer_lpi proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_printer_lpi proto __cdecl \
	      settings: ptr GtkPrintSettings,
		   lpi: gdouble

;gdouble
gtk_print_settings_get_scale proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_scale proto __cdecl \
	      settings: ptr GtkPrintSettings,
		 scale: gdouble

;GtkPrintPages
gtk_print_settings_get_print_pages proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_print_pages proto __cdecl \
	      settings: ptr GtkPrintSettings,
		 pages: GtkPrintPages

;GtkPageRange
gtk_print_settings_get_page_ranges proto __cdecl \
	      settings: ptr GtkPrintSettings,
	    num_ranges: ptr gint

;void
gtk_print_settings_set_page_ranges proto __cdecl \
	      settings: ptr GtkPrintSettings,
	   page_ranges: ptr GtkPageRange,
	    num_ranges: gint

;GtkPageSet
gtk_print_settings_get_page_set proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_page_set proto __cdecl \
	      settings: ptr GtkPrintSettings,
	      page_set: GtkPageSet

;const
gtk_print_settings_get_default_source proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_default_source proto __cdecl \
	      settings: ptr GtkPrintSettings,
	default_source: ptr gchar

;const
gtk_print_settings_get_media_type proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_media_type proto __cdecl \
	      settings: ptr GtkPrintSettings,
	    media_type: ptr gchar

;const
gtk_print_settings_get_dither proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_dither proto __cdecl \
	      settings: ptr GtkPrintSettings,
		dither: ptr gchar

;const
gtk_print_settings_get_finishings proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_finishings proto __cdecl \
	      settings: ptr GtkPrintSettings,
	    finishings: ptr gchar

;const
gtk_print_settings_get_output_bin proto __cdecl \
	      settings: ptr GtkPrintSettings

;void
gtk_print_settings_set_output_bin proto __cdecl \
	      settings: ptr GtkPrintSettings,
	    output_bin: ptr gchar


G_END_DECLS

endif
