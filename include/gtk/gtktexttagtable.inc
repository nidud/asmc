ifndef __GTK_TEXT_TAG_TABLE_H__
__GTK_TEXT_TAG_TABLE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktexttag.inc

G_BEGIN_DECLS

CALLBACKC(GtkTextTagTableForeach, :ptr GtkTextTag, :gpointer)

GTK_TYPE_TEXT_TAG_TABLE equ <gtk_text_tag_table_get_type>
GTK_TEXT_TAG_TABLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TEXT_TAG_TABLE, GtkTextTagTable))>
	endm
GTK_TEXT_TAG_TABLE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TEXT_TAG_TABLE, GtkTextTagTableClass))>
	endm
GTK_IS_TEXT_TAG_TABLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TEXT_TAG_TABLE))>
	endm
GTK_IS_TEXT_TAG_TABLE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TEXT_TAG_TABLE))>
	endm
GTK_TEXT_TAG_TABLE_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TEXT_TAG_TABLE, GtkTextTagTableClass))>
	endm

GtkTextTagTable		STRUC
parent_instance		GObject <>
priv			ptr_t ?
GtkTextTagTable		ENDS

GtkTextTagTableClass	STRUC
parent_class		GObjectClass <>
tag_changed		proc :ptr GtkTextTagTable, :ptr GtkTextTag, :gboolean
tag_added		proc :ptr GtkTextTagTable, :ptr GtkTextTag
tag_removed		proc :ptr GtkTextTagTable, :ptr GtkTextTag
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkTextTagTableClass	ENDS

;GType
gtk_text_tag_table_get_type proto __cdecl

;GtkTextTagTable
gtk_text_tag_table_new proto __cdecl
;gboolean
gtk_text_tag_table_add proto __cdecl \
		 table: ptr GtkTextTagTable,
		   tag: ptr GtkTextTag

;void
gtk_text_tag_table_remove proto __cdecl \
		 table: ptr GtkTextTagTable,
		   tag: ptr GtkTextTag

;GtkTextTag
gtk_text_tag_table_lookup proto __cdecl \
		 table: ptr GtkTextTagTable,
		  name: ptr gchar

;void
gtk_text_tag_table_foreach proto __cdecl \
		 table: ptr GtkTextTagTable,
		  func: GtkTextTagTableForeach,
		  data: gpointer

;gint
gtk_text_tag_table_get_size proto __cdecl \
		 table: ptr GtkTextTagTable

;void
_gtk_text_tag_table_add_buffer proto __cdecl \
		 table: ptr GtkTextTagTable,
		buffer: gpointer

;void
_gtk_text_tag_table_remove_buffer proto __cdecl \
		 table: ptr GtkTextTagTable,
		buffer: gpointer

G_END_DECLS

endif

