ifndef __GTK_PRINT_SETTINGS_H__
define __GTK_PRINT_SETTINGS_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkpapersize.inc

;GtkPrintSettings        typedef _GtkPrintSettings

define GTK_TYPE_PRINT_SETTINGS <gtk_print_settings_get_type ()>
GTK_PRINT_SETTINGS macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_PRINT_SETTINGS, GtkPrintSettings))>
  endm
GTK_IS_PRINT_SETTINGS macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_PRINT_SETTINGS))>
  endm

CALLBACK(GtkPrintSettingsFunc, :ptr, :ptr, :gpointer)

_GtkPageRange           struct
start                   sdword ?
_end                    sdword ?
_GtkPageRange           ends
GtkPageRange            typedef _GtkPageRange

gtk_print_settings_get_type proto
gtk_print_settings_new proto

gtk_print_settings_copy proto :ptr

gtk_print_settings_new_from_file proto :ptr, :ptr
gtk_print_settings_load_file proto :ptr, :ptr, :ptr
gtk_print_settings_to_file proto :ptr, :ptr, :ptr
gtk_print_settings_new_from_key_file proto :ptr, :ptr, :ptr
gtk_print_settings_load_key_file proto :ptr, :ptr, :ptr, :ptr
gtk_print_settings_to_key_file proto :ptr, :ptr, :ptr
gtk_print_settings_has_key proto :ptr, :ptr
gtk_print_settings_get proto :ptr, :ptr
gtk_print_settings_set proto :ptr, :ptr, :ptr
gtk_print_settings_unset proto :ptr, :ptr
gtk_print_settings_foreach proto :ptr, :GtkPrintSettingsFunc, :gpointer
gtk_print_settings_get_bool proto :ptr, :ptr
gtk_print_settings_set_bool proto :ptr, :ptr, :gboolean
gtk_print_settings_get_double proto :ptr, :ptr
gtk_print_settings_get_double_with_default proto :ptr, :ptr, :real8
gtk_print_settings_set_double proto :ptr, :ptr, :real8
gtk_print_settings_get_length proto :ptr, :ptr, :GtkUnit
gtk_print_settings_set_length proto :ptr, :ptr, :real8, :GtkUnit
gtk_print_settings_get_int proto :ptr, :ptr
gtk_print_settings_get_int_with_default proto :ptr, :ptr, :sdword
gtk_print_settings_set_int proto :ptr, :ptr, :sdword

define GTK_PRINT_SETTINGS_PRINTER          <"printer">
define GTK_PRINT_SETTINGS_ORIENTATION      <"orientation">
define GTK_PRINT_SETTINGS_PAPER_FORMAT     <"paper-format">
define GTK_PRINT_SETTINGS_PAPER_WIDTH      <"paper-width">
define GTK_PRINT_SETTINGS_PAPER_HEIGHT     <"paper-height">
define GTK_PRINT_SETTINGS_N_COPIES         <"n-copies">
define GTK_PRINT_SETTINGS_DEFAULT_SOURCE   <"default-source">
define GTK_PRINT_SETTINGS_QUALITY          <"quality">
define GTK_PRINT_SETTINGS_RESOLUTION       <"resolution">
define GTK_PRINT_SETTINGS_USE_COLOR        <"use-color">
define GTK_PRINT_SETTINGS_DUPLEX           <"duplex">
define GTK_PRINT_SETTINGS_COLLATE          <"collate">
define GTK_PRINT_SETTINGS_REVERSE          <"reverse">
define GTK_PRINT_SETTINGS_MEDIA_TYPE       <"media-type">
define GTK_PRINT_SETTINGS_DITHER           <"dither">
define GTK_PRINT_SETTINGS_SCALE            <"scale">
define GTK_PRINT_SETTINGS_PRINT_PAGES      <"print-pages">
define GTK_PRINT_SETTINGS_PAGE_RANGES      <"page-ranges">
define GTK_PRINT_SETTINGS_PAGE_SET         <"page-set">
define GTK_PRINT_SETTINGS_FINISHINGS       <"finishings">
define GTK_PRINT_SETTINGS_NUMBER_UP        <"number-up">
define GTK_PRINT_SETTINGS_NUMBER_UP_LAYOUT <"number-up-layout">
define GTK_PRINT_SETTINGS_OUTPUT_BIN       <"output-bin">
define GTK_PRINT_SETTINGS_RESOLUTION_X     <"resolution-x">
define GTK_PRINT_SETTINGS_RESOLUTION_Y     <"resolution-y">
define GTK_PRINT_SETTINGS_PRINTER_LPI      <"printer-lpi">
define GTK_PRINT_SETTINGS_OUTPUT_DIR       <"output-dir">
define GTK_PRINT_SETTINGS_OUTPUT_BASENAME  <"output-basename">
define GTK_PRINT_SETTINGS_OUTPUT_FILE_FORMAT  <"output-file-format">
define GTK_PRINT_SETTINGS_OUTPUT_URI          <"output-uri">
define GTK_PRINT_SETTINGS_WIN32_DRIVER_VERSION <"win32-driver-version">
define GTK_PRINT_SETTINGS_WIN32_DRIVER_EXTRA   <"win32-driver-extra">

gtk_print_settings_get_printer proto :ptr
gtk_print_settings_set_printer proto :ptr, :ptr
gtk_print_settings_get_orientation proto :ptr
gtk_print_settings_set_orientation proto :ptr, :GtkPageOrientation
gtk_print_settings_get_paper_size proto :ptr
gtk_print_settings_set_paper_size proto :ptr, :ptr
gtk_print_settings_get_paper_width proto :ptr, :GtkUnit
gtk_print_settings_set_paper_width proto :ptr, :real8, :GtkUnit
gtk_print_settings_get_paper_height proto :ptr, :GtkUnit
gtk_print_settings_set_paper_height proto :ptr, :real8, :GtkUnit
gtk_print_settings_get_use_color proto :ptr
gtk_print_settings_set_use_color proto :ptr, :gboolean
gtk_print_settings_get_collate proto :ptr
gtk_print_settings_set_collate proto :ptr, :gboolean
gtk_print_settings_get_reverse proto :ptr
gtk_print_settings_set_reverse proto :ptr, :gboolean
gtk_print_settings_get_duplex proto :ptr
gtk_print_settings_set_duplex proto :ptr, :GtkPrintDuplex
gtk_print_settings_get_quality proto :ptr
gtk_print_settings_set_quality proto :ptr, :GtkPrintQuality
gtk_print_settings_get_n_copies proto :ptr
gtk_print_settings_set_n_copies proto :ptr, :sdword
gtk_print_settings_get_number_up proto :ptr
gtk_print_settings_set_number_up proto :ptr, :sdword
gtk_print_settings_get_number_up_layout proto :ptr
gtk_print_settings_set_number_up_layout proto :ptr, :GtkNumberUpLayout
gtk_print_settings_get_resolution proto :ptr
gtk_print_settings_set_resolution proto :ptr, :sdword
gtk_print_settings_get_resolution_x proto :ptr
gtk_print_settings_get_resolution_y proto :ptr
gtk_print_settings_set_resolution_xy proto :ptr, :sdword, :sdword
gtk_print_settings_get_printer_lpi proto :ptr
gtk_print_settings_set_printer_lpi proto :ptr, :real8
gtk_print_settings_get_scale proto :ptr
gtk_print_settings_set_scale proto :ptr, :real8
gtk_print_settings_get_print_pages proto :ptr
gtk_print_settings_set_print_pages proto :ptr, :GtkPrintPages
gtk_print_settings_get_page_ranges proto :ptr, :ptr
gtk_print_settings_set_page_ranges proto :ptr, :ptr, :sdword
gtk_print_settings_get_page_set proto :ptr
gtk_print_settings_set_page_set proto :ptr, :GtkPageSet
gtk_print_settings_get_default_source proto :ptr
gtk_print_settings_set_default_source proto :ptr, :ptr
gtk_print_settings_get_media_type proto :ptr
gtk_print_settings_set_media_type proto :ptr, :ptr
gtk_print_settings_get_dither proto :ptr
gtk_print_settings_set_dither proto :ptr, :ptr
gtk_print_settings_get_finishings proto :ptr
gtk_print_settings_set_finishings proto :ptr, :ptr
gtk_print_settings_get_output_bin proto :ptr
gtk_print_settings_set_output_bin proto :ptr, :ptr

gtk_print_settings_to_gvariant proto :ptr
gtk_print_settings_new_from_gvariant proto :ptr

endif
