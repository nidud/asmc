ifndef __GTK_ENTRY_BUFFER_H__
__GTK_ENTRY_BUFFER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib-object.inc
include gdk/gdk.inc

G_BEGIN_DECLS

GTK_ENTRY_BUFFER_MAX_SIZE equ G_MAXUSHORT

GTK_TYPE_ENTRY_BUFFER equ <gtk_entry_buffer_get_type>
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

GtkEntryBuffer		STRUC
parent_instance		GObject <>
priv			ptr_t ?
GtkEntryBuffer		ENDS

GtkEntryBufferClass	STRUC
parent_class		GObjectClass <>
inserted_text		proc :ptr GtkEntryBuffer, :guint, :ptr gchar, :guint
deleted_text		proc :ptr GtkEntryBuffer, :guint, :guint
get_text		proc :ptr GtkEntryBuffer, :ptr gchar, :ptr gsize
get_length		proc :ptr GtkEntryBuffer
insert_text		proc :ptr GtkEntryBuffer, :guint, :ptr gchar, :guint
delete_text		proc :ptr GtkEntryBuffer, :guint, :guint
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
_gtk_reserved6		proc
_gtk_reserved7		proc
_gtk_reserved8		proc
GtkEntryBufferClass	ENDS

;GType
gtk_entry_buffer_get_type proto __cdecl

;GtkEntryBuffer*
gtk_entry_buffer_new proto __cdecl \
	 initial_chars: ptr gchar,
       n_initial_chars: gint

;gsize
gtk_entry_buffer_get_bytes proto __cdecl \
		buffer: ptr GtkEntryBuffer

;guint
gtk_entry_buffer_get_length proto __cdecl \
		buffer: ptr GtkEntryBuffer

;const
gtk_entry_buffer_get_text proto __cdecl \
		buffer: ptr GtkEntryBuffer

;void
gtk_entry_buffer_set_text proto __cdecl \
		buffer: ptr GtkEntryBuffer,
		 chars: ptr gchar,
	       n_chars: gint

;void
gtk_entry_buffer_set_max_length proto __cdecl \
		buffer: ptr GtkEntryBuffer,
	    max_length: gint

;gint
gtk_entry_buffer_get_max_length proto __cdecl \
		buffer: ptr GtkEntryBuffer

;guint
gtk_entry_buffer_insert_text proto __cdecl \
		buffer: ptr GtkEntryBuffer,
	      position: guint,
		 chars: ptr gchar,
	       n_chars: gint

;guint
gtk_entry_buffer_delete_text proto __cdecl \
		buffer: ptr GtkEntryBuffer,
	      position: guint,
	       n_chars: gint

;void
gtk_entry_buffer_emit_inserted_text proto __cdecl \
		buffer: ptr GtkEntryBuffer,
	      position: guint,
		 chars: ptr gchar,
	       n_chars: guint

;void
gtk_entry_buffer_emit_deleted_text proto __cdecl \
		buffer: ptr GtkEntryBuffer,
	      position: guint,
	       n_chars: guint

G_END_DECLS

endif
