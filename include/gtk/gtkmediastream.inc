ifndef __GTK_MEDIA_STREAM_H__
define __GTK_MEDIA_STREAM_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc

define GTK_TYPE_MEDIA_STREAM <gtk_media_stream_get_type>

_GtkMediaStreamClass    struct
parent_class            GObjectClass <>
play                    proc :ptr
_pause                  proc :ptr
seek                    proc :ptr, :gint64
update_audio            proc :ptr, :gboolean, :real8
realize                 proc :ptr, :ptr
unrealize               proc :ptr, :ptr
_gtk_reserved1          proc
_gtk_reserved2          proc
_gtk_reserved3          proc
_gtk_reserved4          proc
_gtk_reserved5          proc
_gtk_reserved6          proc
_gtk_reserved7          proc
_gtk_reserved8          proc
_GtkMediaStreamClass    ends
GtkMediaStreamClass     typedef _GtkMediaStreamClass

gtk_media_stream_is_prepared proto :ptr
gtk_media_stream_get_error proto :ptr
gtk_media_stream_has_audio proto :ptr
gtk_media_stream_has_video proto :ptr

gtk_media_stream_play proto :ptr
gtk_media_stream_pause proto :ptr
gtk_media_stream_get_playing proto :ptr
gtk_media_stream_set_playing proto :ptr, :gboolean
gtk_media_stream_get_ended proto :ptr

gtk_media_stream_get_timestamp proto :ptr
gtk_media_stream_get_duration proto :ptr

gtk_media_stream_is_seekable proto :ptr
gtk_media_stream_is_seeking proto :ptr
gtk_media_stream_seek proto :ptr, :gint64
gtk_media_stream_get_loop proto :ptr
gtk_media_stream_set_loop proto :ptr, :gboolean
gtk_media_stream_get_muted proto :ptr
gtk_media_stream_set_muted proto :ptr, :gboolean
gtk_media_stream_get_volume proto :ptr
gtk_media_stream_set_volume proto :ptr, :real8
gtk_media_stream_realize proto :ptr, :ptr
gtk_media_stream_unrealize proto :ptr, :ptr


gtk_media_stream_error proto :ptr, :GQuark, :sdword, :ptr, :vararg
gtk_media_stream_prepared proto :ptr, :gboolean, :gboolean, :gboolean, :gint64
gtk_media_stream_unprepared proto :ptr

gtk_media_stream_stream_prepared proto :ptr, :gboolean, :gboolean, :gboolean, :gint64
gtk_media_stream_stream_unprepared proto :ptr

gtk_media_stream_update proto :ptr, :gint64
gtk_media_stream_ended proto :ptr
gtk_media_stream_stream_ended proto :ptr
gtk_media_stream_seek_success proto :ptr
gtk_media_stream_seek_failed proto :ptr
gtk_media_stream_gerror proto :ptr, :ptr

endif
