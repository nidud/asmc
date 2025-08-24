ifndef __GTK_PAPER_SIZE_H__
define __GTK_PAPER_SIZE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkenums.inc

define GTK_TYPE_PAPER_SIZE <gtk_paper_size_get_type ()>

define GTK_PAPER_NAME_A3 <"iso_a3">
define GTK_PAPER_NAME_A4 <"iso_a4">
define GTK_PAPER_NAME_A5 <"iso_a5">
define GTK_PAPER_NAME_B5 <"iso_b5">
define GTK_PAPER_NAME_LETTER <"na_letter">
define GTK_PAPER_NAME_EXECUTIVE <"na_executive">
define GTK_PAPER_NAME_LEGAL <"na_legal">

gtk_paper_size_get_type proto
gtk_paper_size_new proto :ptr
gtk_paper_size_new_from_ppd proto :ptr, :ptr, :real8, :real8
gtk_paper_size_new_from_ipp proto :ptr, :real8, :real8
gtk_paper_size_new_custom proto :ptr, :ptr, :real8, :real8, :GtkUnit
gtk_paper_size_copy proto :ptr
gtk_paper_size_free proto :ptr
gtk_paper_size_is_equal proto :ptr, :ptr
gtk_paper_size_get_paper_sizes proto :gboolean
gtk_paper_size_get_name proto :ptr
gtk_paper_size_get_display_name proto :ptr
gtk_paper_size_get_ppd_name proto :ptr
gtk_paper_size_get_width proto :ptr, :GtkUnit
gtk_paper_size_get_height proto :ptr, :GtkUnit
gtk_paper_size_is_custom proto :ptr
gtk_paper_size_is_ipp proto :ptr
gtk_paper_size_set_size proto :ptr, :real8, :real8, :GtkUnit
gtk_paper_size_get_default_top_margin proto :ptr, :GtkUnit
gtk_paper_size_get_default_bottom_margin proto :ptr, :GtkUnit
gtk_paper_size_get_default_left_margin proto :ptr, :GtkUnit
gtk_paper_size_get_default_right_margin proto :ptr, :GtkUnit
gtk_paper_size_get_default proto
gtk_paper_size_new_from_key_file proto :ptr, :ptr, :ptr
gtk_paper_size_to_key_file proto :ptr, :ptr, :ptr
gtk_paper_size_new_from_gvariant proto :ptr
gtk_paper_size_to_gvariant proto :ptr

endif
