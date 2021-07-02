ifndef __GTK_TEXT_TAG_H__
__GTK_TEXT_TAG_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkenums.inc

GTK_TYPE_TEXT_TAG  equ <gtk_text_tag_get_type>
GTK_TEXT_TAG macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TEXT_TAG, GtkTextTag))>
	endm
GTK_TEXT_TAG_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TEXT_TAG, GtkTextTagClass))>
	endm
GTK_IS_TEXT_TAG macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TEXT_TAG))>
	endm
GTK_IS_TEXT_TAG_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TEXT_TAG))>
	endm
GTK_TEXT_TAG_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TEXT_TAG, GtkTextTagClass))>
	endm

GtkTextTag		STRUC
parent_instance		GObject <>
priv			ptr_t ?
GtkTextTag		ENDS

GtkTextTagClass		STRUC
parent_class		GObjectClass <>
event			proc :ptr GtkTextTag, :ptr GObject, :ptr GdkEvent, :ptr GtkTextIter
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkTextTagClass		ENDS

;GType
gtk_text_tag_get_type proto __cdecl
;GtkTextTag
gtk_text_tag_new proto __cdecl \
		  name: ptr gchar

;gint
gtk_text_tag_get_priority proto __cdecl \
		   tag: ptr GtkTextTag

;void
gtk_text_tag_set_priority proto __cdecl \
		   tag: ptr GtkTextTag,
	      priority: gint

;gboolean
gtk_text_tag_event proto __cdecl \
		   tag: ptr GtkTextTag,
	  event_object: ptr GObject,
		 event: ptr GdkEvent,
		  iter: ptr GtkTextIter

endif

