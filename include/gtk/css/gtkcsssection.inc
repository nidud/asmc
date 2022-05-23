ifndef __GTK_CSS_SECTION_H__
define __GTK_CSS_SECTION_H__

if not defined (__GTK_CSS_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/css/gtkcss.h can be included directly.">
endif

include gio/gio.inc
include gdk/gdkversionmacros.inc
include gtk/css/gtkcsslocation.inc

define GTK_TYPE_CSS_SECTION <gtk_css_section_get_type>

;GtkCssSection typedef _GtkCssSection

gtk_css_section_get_type proto

gtk_css_section_new proto :ptr, :ptr, :ptr
gtk_css_section_ref proto :ptr
gtk_css_section_unref proto :ptr

gtk_css_section_print proto :ptr, :ptr
gtk_css_section_to_string proto :ptr

gtk_css_section_get_parent proto :ptr
gtk_css_section_get_file proto :ptr
gtk_css_section_get_start_location proto :ptr
gtk_css_section_get_end_location proto :ptr

endif
