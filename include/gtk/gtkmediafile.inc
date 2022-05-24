ifndef __GTK_MEDIA_FILE_H__
define __GTK_MEDIA_FILE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkmediastream.inc

define GTK_MEDIA_FILE_EXTENSION_POINT_NAME <"gtk-media-file">
define GTK_TYPE_MEDIA_FILE <gtk_media_file_get_type ()>


_GtkMediaFileClass      struct
parent_class            GtkMediaStreamClass <>
open                    proc :ptr
close                   proc :ptr
_gtk_reserved1          proc
_gtk_reserved2          proc
_gtk_reserved3          proc
_gtk_reserved4          proc
_GtkMediaFileClass      ends

gtk_media_file_new proto
gtk_media_file_new_for_filename proto :ptr
gtk_media_file_new_for_resource proto :ptr
gtk_media_file_new_for_file proto :ptr
gtk_media_file_new_for_input_stream proto :ptr

gtk_media_file_clear proto :ptr

gtk_media_file_set_filename proto :ptr, :ptr
gtk_media_file_set_resource proto :ptr, :ptr
gtk_media_file_set_file proto :ptr, :ptr
gtk_media_file_get_file proto :ptr
gtk_media_file_set_input_stream proto :ptr, :ptr
gtk_media_file_get_input_stream proto :ptr

endif
