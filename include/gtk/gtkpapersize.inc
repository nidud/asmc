ifndef __GTK_PAPER_SIZE_H__
__GTK_PAPER_SIZE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkenums.inc

G_BEGIN_DECLS

GTK_TYPE_PAPER_SIZE     equ <gtk_paper_size_get_type>
GTK_PAPER_NAME_A3       equ <"iso_a3">
GTK_PAPER_NAME_A4       equ <"iso_a4">
GTK_PAPER_NAME_A5       equ <"iso_a5">
GTK_PAPER_NAME_B5       equ <"iso_b5">
GTK_PAPER_NAME_LETTER   equ <"na_letter">
GTK_PAPER_NAME_EXECUTIVE equ <"na_executive">
GTK_PAPER_NAME_LEGAL    equ <"na_legal">

;GType
gtk_paper_size_get_type proto __cdecl

;GtkPaperSize
gtk_paper_size_new proto __cdecl \
                  name: ptr gchar

;GtkPaperSize
gtk_paper_size_new_from_ppd proto __cdecl \
              ppd_name: ptr gchar,
      ppd_display_name: ptr gchar,
                 width: gdouble,
                height: gdouble

;GtkPaperSize
gtk_paper_size_new_from_ipp proto __cdecl \
              ipp_name: ptr gchar,
                 width: gdouble,
                height: gdouble

;GtkPaperSize
gtk_paper_size_new_custom proto __cdecl \
                  name: ptr gchar,
          display_name: ptr gchar,
                 width: gdouble,
                height: gdouble,
                  unit: GtkUnit

;GtkPaperSize
gtk_paper_size_copy proto __cdecl \
                 other: ptr GtkPaperSize

;void
gtk_paper_size_free proto __cdecl \
                  size: ptr GtkPaperSize

;gboolean
gtk_paper_size_is_equal proto __cdecl \
                 size1: ptr GtkPaperSize,
                 size2: ptr GtkPaperSize


;GList
gtk_paper_size_get_paper_sizes proto __cdecl \
        include_custom: gboolean


;const
gtk_paper_size_get_name proto __cdecl \
                  size: ptr GtkPaperSize

;const
gtk_paper_size_get_display_name proto __cdecl \
                  size: ptr GtkPaperSize

;const
gtk_paper_size_get_ppd_name proto __cdecl \
                  size: ptr GtkPaperSize


;gdouble
gtk_paper_size_get_width proto __cdecl \
                  size: ptr GtkPaperSize,
                  unit: GtkUnit

;gdouble
gtk_paper_size_get_height proto __cdecl \
                  size: ptr GtkPaperSize,
                  unit: GtkUnit

;gboolean
gtk_paper_size_is_custom proto __cdecl \
                  size: ptr GtkPaperSize

;gboolean
gtk_paper_size_is_ipp proto __cdecl \
                  size: ptr GtkPaperSize


;void
gtk_paper_size_set_size proto __cdecl \
                  size: ptr GtkPaperSize,
                 width: gdouble,
                height: gdouble,
                  unit: GtkUnit


;gdouble
gtk_paper_size_get_default_top_margin proto __cdecl \
                  size: ptr GtkPaperSize,
                  unit: GtkUnit

;gdouble
gtk_paper_size_get_default_bottom_margin proto __cdecl \
                  size: ptr GtkPaperSize,
                  unit: GtkUnit

;gdouble
gtk_paper_size_get_default_left_margin proto __cdecl \
                  size: ptr GtkPaperSize,
                  unit: GtkUnit

;gdouble
gtk_paper_size_get_default_right_margin proto __cdecl \
                  size: ptr GtkPaperSize,
                  unit: GtkUnit


;const
gtk_paper_size_get_default proto __cdecl

;GtkPaperSize
gtk_paper_size_new_from_key_file proto __cdecl \
              key_file: ptr GKeyFile,
            group_name: ptr gchar,
                 error: ptr GError

;void
gtk_paper_size_to_key_file proto __cdecl \
                  size: ptr GtkPaperSize,
              key_file: ptr GKeyFile,
            group_name: ptr gchar


G_END_DECLS

endif
