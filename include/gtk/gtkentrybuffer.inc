ifndef __GTK_ENTRY_BUFFER_H__
define __GTK_ENTRY_BUFFER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib-object.inc
include gdk/gdk.inc

define GTK_ENTRY_BUFFER_MAX_SIZE        G_MAXUSHORT
define GTK_TYPE_ENTRY_BUFFER            <gtk_entry_buffer_get_type>
GTK_ENTRY_BUFFER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ENTRY_BUFFER, GtkEntryBuffer))>
  endm
GTK_ENTRY_BUFFER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ENTRY_BUFFER, GtkEntryBufferClass))>
  endm
GTK_IS_ENTRY_BUFFER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ENTRY_BUFFER))>
  endm
GTK_IS_ENTRY_BUFFER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ENTRY_BUFFER))>
  endm
GTK_ENTRY_BUFFER_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ENTRY_BUFFER, GtkEntryBufferClass))>
  endm

_GtkEntryBuffer         struct
parent_instance         GObject <>
_GtkEntryBuffer         ends
GtkEntryBuffer          typedef _GtkEntryBuffer
_GtkEntryBufferClass    struct
parent_class            GObjectClass <>
inserted_text           proc :ptr, :guint, :ptr, :guint
deleted_text            proc :ptr, :guint, :guint
get_text                proc :ptr, :ptr
get_length              proc :ptr
insert_text             proc :ptr, :guint, :ptr, :guint
delete_text             proc :ptr, :guint, :guint
_gtk_reserved1          proc
_gtk_reserved2          proc
_gtk_reserved3          proc
_gtk_reserved4          proc
_gtk_reserved5          proc
_gtk_reserved6          proc
_gtk_reserved7          proc
_gtk_reserved8          proc
_GtkEntryBufferClass    ends
GtkEntryBufferClass     typedef _GtkEntryBufferClass

gtk_entry_buffer_get_type proto
gtk_entry_buffer_new proto :ptr, :sdword
gtk_entry_buffer_get_bytes proto :ptr
gtk_entry_buffer_get_length proto :ptr
gtk_entry_buffer_get_text proto :ptr
gtk_entry_buffer_set_text proto :ptr, :ptr, :sdword
gtk_entry_buffer_set_max_length proto :ptr, :sdword
gtk_entry_buffer_get_max_length proto :ptr
gtk_entry_buffer_insert_text proto :ptr, :guint, :ptr, :sdword
gtk_entry_buffer_delete_text proto :ptr, :guint, :sdword
gtk_entry_buffer_emit_inserted_text proto :ptr, :guint, :ptr, :guint
gtk_entry_buffer_emit_deleted_text proto :ptr, :guint, :guint

endif
