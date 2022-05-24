ifndef __GTK_PAGE_SETUP_H__
define __GTK_PAGE_SETUP_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkpapersize.inc

;GtkPageSetup            typedef _GtkPageSetup

define GTK_TYPE_PAGE_SETUP <gtk_page_setup_get_type ()>
GTK_PAGE_SETUP macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_PAGE_SETUP, GtkPageSetup))>
  endm
GTK_IS_PAGE_SETUP macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_PAGE_SETUP))>
  endm

gtk_page_setup_get_type proto
gtk_page_setup_new proto
gtk_page_setup_copy proto :ptr
gtk_page_setup_get_orientation proto :ptr
gtk_page_setup_set_orientation proto :ptr, :GtkPageOrientation
gtk_page_setup_get_paper_size proto :ptr
gtk_page_setup_set_paper_size proto :ptr, :ptr
gtk_page_setup_get_top_margin proto :ptr, :GtkUnit
gtk_page_setup_set_top_margin proto :ptr, :real8, :GtkUnit
gtk_page_setup_get_bottom_margin proto :ptr, :GtkUnit
gtk_page_setup_set_bottom_margin proto :ptr, :real8, :GtkUnit
gtk_page_setup_get_left_margin proto :ptr, :GtkUnit
gtk_page_setup_set_left_margin proto :ptr, :real8, :GtkUnit
gtk_page_setup_get_right_margin proto :ptr, :GtkUnit
gtk_page_setup_set_right_margin proto :ptr, :real8, :GtkUnit
gtk_page_setup_set_paper_size_and_default_margins proto :ptr, :ptr
gtk_page_setup_get_paper_width proto :ptr, :GtkUnit
gtk_page_setup_get_paper_height proto :ptr, :GtkUnit
gtk_page_setup_get_page_width proto :ptr, :GtkUnit
gtk_page_setup_get_page_height proto :ptr, :GtkUnit
gtk_page_setup_new_from_file proto :ptr, :ptr
gtk_page_setup_load_file proto :ptr, :ptr, :ptr
gtk_page_setup_to_file proto :ptr, :ptr, :ptr
gtk_page_setup_new_from_key_file proto :ptr, :ptr, :ptr
gtk_page_setup_load_key_file proto :ptr, :ptr, :ptr, :ptr
gtk_page_setup_to_key_file proto :ptr, :ptr, :ptr
gtk_page_setup_to_gvariant proto :ptr
gtk_page_setup_new_from_gvariant proto :ptr

endif
