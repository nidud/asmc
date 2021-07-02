ifndef __GTK_TEXT_ATTRIBUTES_H__
__GTK_TEXT_ATTRIBUTES_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkenums.inc

GTK_TYPE_TEXT_ATTRIBUTES equ <gtk_text_attributes_get_type>

GtkTextAppearance	STRUC
bg_color		GdkColor <>
fg_color		GdkColor <>
rise			gint ?
underline		guint ? ; : 4
;strikethrough : 1	 guint ?
;draw_bg : 1		 guint ?
;inside_selection : 1	 guint ?
;is_text : 1		 guint ?
ifdef __GI_SCANNER__
UNION
rgba			ptr_t 2 dup(?)
padding			guint 4 dup(?)
ENDS
else
rgba			ptr_t 2 dup(?)
if (defined(__SIZEOF_INT__) AND defined(__SIZEOF_POINTER__))
if (__SIZEOF_INT__ EQ __SIZEOF_POINTER__)
padding			guint 2 dup(?)
endif
endif
endif
GtkTextAppearance	ENDS

GtkTextAttributes	STRUC
refcount		guint ?
appearance		GtkTextAppearance <>
justification		GtkJustification ?
direction		GtkTextDirection ?
font			ptr_t ?
font_scale		gdouble ?
left_margin		gint ?
right_margin		gint ?
indent			gint ?
pixels_above_lines	gint ?
pixels_below_lines	gint ?
pixels_inside_wrap	gint ?
tabs			ptr_t ?
wrap_mode		GtkWrapMode ?
language		ptr_t ?
pg_bg_color		ptr_t ?
invisible		guint ? ; : 1
;bg_full_height : 1	guint ?
;editable : 1		guint ?
;no_fallback: 1		guint ?
pg_bg_rgba		ptr_t ?
letter_spacing		gint ?
ifdef __GI_SCANNER__
UNION ; {
font_features		ptr_t ?
padding			guint 2 dup(?)
ENDS ;
else
font_features		ptr_t ?
if (defined(__SIZEOF_INT__) AND defined(__SIZEOF_POINTER__))
if (__SIZEOF_INT__ EQ __SIZEOF_POINTER__)
padding			guint 1 dup(?)
endif
endif
endif
GtkTextAttributes	ENDS

;GtkTextAttributes*
gtk_text_attributes_new proto __cdecl
;GtkTextAttributes*
gtk_text_attributes_copy proto __cdecl \
		   src: ptr GtkTextAttributes

;void
gtk_text_attributes_copy_values proto __cdecl \
		   src: ptr GtkTextAttributes,
		  dest: ptr GtkTextAttributes

;void
gtk_text_attributes_unref proto __cdecl \
		values: ptr GtkTextAttributes

;GtkTextAttributes
gtk_text_attributes_ref proto __cdecl \
		values: ptr GtkTextAttributes


;GType
gtk_text_attributes_get_type proto __cdecl


endif

