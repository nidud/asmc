ifndef __GTK_RENDER_H__
define __GTK_RENDER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include cairo.inc
include pango/pango.inc
include gdk/gdk.inc

include gtk/gtkenums.inc
include gtk/gtktypes.inc

gtk_render_check proto :ptr, :ptr, :real8, :real8, :real8, :real8
gtk_render_option proto :ptr, :ptr, :real8, :real8, :real8, :real8
gtk_render_arrow proto :ptr, :ptr, :real8, :real8, :real8, :real8
gtk_render_background proto :ptr, :ptr, :real8, :real8, :real8, :real8

gtk_render_frame proto :ptr, :ptr, :real8, :real8, :real8, :real8
gtk_render_expander proto :ptr, :ptr, :real8, :real8, :real8, :real8
gtk_render_focus proto :ptr, :ptr, :real8, :real8, :real8, :real8
gtk_render_layout proto :ptr, :ptr, :real8, :real8, :ptr
gtk_render_line proto :ptr, :ptr, :real8, :real8, :real8, :real8
gtk_render_handle proto :ptr, :ptr, :real8, :real8, :real8, :real8
gtk_render_activity proto :ptr, :ptr, :real8, :real8, :real8, :real8
gtk_render_icon proto :ptr, :ptr, :ptr, :real8, :real8

endif
