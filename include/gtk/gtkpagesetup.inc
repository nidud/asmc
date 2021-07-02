ifndef __GTK_PAGE_SETUP_H__
__GTK_PAGE_SETUP_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkpapersize.inc

G_BEGIN_DECLS

GTK_TYPE_PAGE_SETUP equ <gtk_page_setup_get_type>
GTK_PAGE_SETUP macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_PAGE_SETUP, GtkPageSetup))>
	endm
GTK_IS_PAGE_SETUP macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_PAGE_SETUP))>
	endm

;GType
gtk_page_setup_get_type proto __cdecl
;GtkPageSetup
gtk_page_setup_new proto __cdecl
;GtkPageSetup
gtk_page_setup_copy proto __cdecl \
		 other: ptr GtkPageSetup

;GtkPageOrientation
gtk_page_setup_get_orientation proto __cdecl \
		 setup: ptr GtkPageSetup

;void
gtk_page_setup_set_orientation proto __cdecl \
		 setup: ptr GtkPageSetup,
	   orientation: GtkPageOrientation

;GtkPaperSize
gtk_page_setup_get_paper_size proto __cdecl \
		 setup: ptr GtkPageSetup

;void
gtk_page_setup_set_paper_size proto __cdecl \
		 setup: ptr GtkPageSetup,
		  size: ptr GtkPaperSize

;gdouble
gtk_page_setup_get_top_margin proto __cdecl \
		 setup: ptr GtkPageSetup,
		  unit: GtkUnit

;void
gtk_page_setup_set_top_margin proto __cdecl \
		 setup: ptr GtkPageSetup,
		margin: gdouble,
		  unit: GtkUnit

;gdouble
gtk_page_setup_get_bottom_margin proto __cdecl \
		 setup: ptr GtkPageSetup,
		  unit: GtkUnit

;void
gtk_page_setup_set_bottom_margin proto __cdecl \
		 setup: ptr GtkPageSetup,
		margin: gdouble,
		  unit: GtkUnit

;gdouble
gtk_page_setup_get_left_margin proto __cdecl \
		 setup: ptr GtkPageSetup,
		  unit: GtkUnit

;void
gtk_page_setup_set_left_margin proto __cdecl \
		 setup: ptr GtkPageSetup,
		margin: gdouble,
		  unit: GtkUnit

;gdouble
gtk_page_setup_get_right_margin proto __cdecl \
		 setup: ptr GtkPageSetup,
		  unit: GtkUnit

;void
gtk_page_setup_set_right_margin proto __cdecl \
		 setup: ptr GtkPageSetup,
		margin: gdouble,
		  unit: GtkUnit


;void
gtk_page_setup_set_paper_size_and_default_margins proto __cdecl \
		 setup: ptr GtkPageSetup,
		  size: ptr GtkPaperSize


;gdouble
gtk_page_setup_get_paper_width proto __cdecl \
		 setup: ptr GtkPageSetup,
		  unit: GtkUnit

;gdouble
gtk_page_setup_get_paper_height proto __cdecl \
		 setup: ptr GtkPageSetup,
		  unit: GtkUnit



;gdouble
gtk_page_setup_get_page_width proto __cdecl \
		 setup: ptr GtkPageSetup,
		  unit: GtkUnit

;gdouble
gtk_page_setup_get_page_height proto __cdecl \
		 setup: ptr GtkPageSetup,
		  unit: GtkUnit


;GtkPageSetup
gtk_page_setup_new_from_file proto __cdecl \
	     file_name: ptr gchar,
		 error: ptr GError

;gboolean
gtk_page_setup_load_file proto __cdecl \
		 setup: ptr GtkPageSetup,
	     file_name: ptr char_t,
		 error: ptr GError

;gboolean
gtk_page_setup_to_file proto __cdecl \
		 setup: ptr GtkPageSetup,
	     file_name: ptr char_t,
		 error: ptr GError

;GtkPageSetup
gtk_page_setup_new_from_key_file proto __cdecl \
	      key_file: ptr GKeyFile,
	    group_name: ptr gchar,
		 error: ptr GError

;gboolean
gtk_page_setup_load_key_file proto __cdecl \
		 setup: ptr GtkPageSetup,
	      key_file: ptr GKeyFile,
	    group_name: ptr gchar,
		 error: ptr GError

;void
gtk_page_setup_to_key_file proto __cdecl \
		 setup: ptr GtkPageSetup,
	      key_file: ptr GKeyFile,
	    group_name: ptr gchar


G_END_DECLS

endif
