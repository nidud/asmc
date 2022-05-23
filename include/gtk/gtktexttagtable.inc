ifndef __GTK_TEXT_TAG_TABLE_H__
define __GTK_TEXT_TAG_TABLE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktexttag.inc

CALLBACK(GtkTextTagTableForeach, :ptr, :gpointer)

define GTK_TYPE_TEXT_TAG_TABLE <gtk_text_tag_table_get_type>
GTK_TEXT_TAG_TABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TEXT_TAG_TABLE, GtkTextTagTable))>
  endm
GTK_IS_TEXT_TAG_TABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TEXT_TAG_TABLE))>
  endm

gtk_text_tag_table_get_type proto
gtk_text_tag_table_new proto
gtk_text_tag_table_add proto :ptr, :ptr
gtk_text_tag_table_remove proto :ptr, :ptr
gtk_text_tag_table_lookup proto :ptr, :ptr
gtk_text_tag_table_foreach proto :ptr, :GtkTextTagTableForeach, :gpointer
gtk_text_tag_table_get_size proto :ptr

endif
