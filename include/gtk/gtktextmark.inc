ifndef __GTK_TEXT_MARK_H__
__GTK_TEXT_MARK_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

G_BEGIN_DECLS

GTK_TYPE_TEXT_MARK equ <gtk_text_mark_get_type>
GTK_TEXT_MARK macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GTK_TYPE_TEXT_MARK, GtkTextMark))>
	endm
GTK_TEXT_MARK_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TEXT_MARK, GtkTextMarkClass))>
	endm
GTK_IS_TEXT_MARK macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GTK_TYPE_TEXT_MARK))>
	endm
GTK_IS_TEXT_MARK_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TEXT_MARK))>
	endm
GTK_TEXT_MARK_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TEXT_MARK, GtkTextMarkClass))>
	endm

GtkTextMark		STRUC
parent_instance		GObject <>
_segment		gpointer ?
GtkTextMark		ENDS

GtkTextMarkClass	STRUC
parent_class		GObjectClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkTextMarkClass	ENDS

;GType
gtk_text_mark_get_type proto __cdecl

;GtkTextMark
gtk_text_mark_new proto __cdecl \
		  name: ptr gchar,
	  left_gravity: gboolean

;void
gtk_text_mark_set_visible proto __cdecl \
		  mark: ptr GtkTextMark,
	       setting: gboolean

;gboolean
gtk_text_mark_get_visible proto __cdecl \
		  mark: ptr GtkTextMark


;const
gtk_text_mark_get_name proto __cdecl \
		  mark: ptr GtkTextMark

;gboolean
gtk_text_mark_get_deleted proto __cdecl \
		  mark: ptr GtkTextMark

;GtkTextBuffer*
gtk_text_mark_get_buffer proto __cdecl \
		  mark: ptr GtkTextMark

;gboolean
gtk_text_mark_get_left_gravity proto __cdecl \
		  mark: ptr GtkTextMark


G_END_DECLS

endif
