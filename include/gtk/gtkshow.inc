ifndef __GTK_SHOW_H__
__GTK_SHOW_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

G_BEGIN_DECLS

;gboolean
gtk_show_uri proto __cdecl \
                screen: ptr GdkScreen,
                   uri: ptr gchar,
             timestamp: guint32,
                 error: ptr GError


G_END_DECLS

endif
