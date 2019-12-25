ifndef __GTK_CSS_SECTION_H__
__GTK_CSS_SECTION_H__ equ <>

include gio/gio.inc
include gdk/gdk.inc

G_BEGIN_DECLS

GTK_TYPE_CSS_SECTION equ <gtk_css_section_get_type>

.enum GtkCssSectionType {
  GTK_CSS_SECTION_DOCUMENT,
  GTK_CSS_SECTION_IMPORT,
  GTK_CSS_SECTION_COLOR_DEFINITION,
  GTK_CSS_SECTION_BINDING_SET,
  GTK_CSS_SECTION_RULESET,
  GTK_CSS_SECTION_SELECTOR,
  GTK_CSS_SECTION_DECLARATION,
  GTK_CSS_SECTION_VALUE,
  GTK_CSS_SECTION_KEYFRAMES
}

;GType
gtk_css_section_get_type proto __cdecl

;GtkCssSection
gtk_css_section_ref proto __cdecl \
               section: ptr GtkCssSection

;void
gtk_css_section_unref proto __cdecl \
               section: ptr GtkCssSection


;GtkCssSectionType
gtk_css_section_get_section_type proto __cdecl \
               section: ptr GtkCssSection

;GtkCssSection
gtk_css_section_get_parent proto __cdecl \
               section: ptr GtkCssSection

;GFile
gtk_css_section_get_file proto __cdecl \
               section: ptr GtkCssSection

;guint
gtk_css_section_get_start_line proto __cdecl \
               section: ptr GtkCssSection

;guint
gtk_css_section_get_start_position proto __cdecl \
               section: ptr GtkCssSection

;guint
gtk_css_section_get_end_line proto __cdecl \
               section: ptr GtkCssSection

;guint
gtk_css_section_get_end_position proto __cdecl \
               section: ptr GtkCssSection

G_END_DECLS

endif
