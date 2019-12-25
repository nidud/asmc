ifndef __GTK_TOOL_SHELL_H__
__GTK_TOOL_SHELL_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkenums.inc
;include pango/pango.inc
include gtk/gtksizegroup.inc

G_BEGIN_DECLS

GTK_TYPE_TOOL_SHELL equ <gtk_tool_shell_get_type>
GTK_TOOL_SHELL macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TOOL_SHELL, GtkToolShell))>
	endm
GTK_IS_TOOL_SHELL macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TOOL_SHELL))>
	endm
GTK_TOOL_SHELL_GET_IFACE macro obj
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTK_TYPE_TOOL_SHELL, GtkToolShellIface))>
	endm

GtkToolShellIface	STRUC
g_iface			GTypeInterface <>
get_icon_size		proc :ptr GtkToolShell
get_orientation		proc :ptr GtkToolShell
get_style		proc :ptr GtkToolShell
get_relief_style	proc :ptr GtkToolShell
rebuild_menu		proc :ptr GtkToolShell
get_text_orientation	proc :ptr GtkToolShell
get_text_alignment	proc :ptr GtkToolShell
get_ellipsize_mode	proc :ptr GtkToolShell
get_text_size_group	proc :ptr GtkToolShell
GtkToolShellIface	ENDS

;GType
gtk_tool_shell_get_type proto __cdecl

;GtkIconSize
gtk_tool_shell_get_icon_size proto __cdecl \
		 shell: ptr GtkToolShell

;GtkOrientation
gtk_tool_shell_get_orientation proto __cdecl \
		 shell: ptr GtkToolShell

;GtkToolbarStyle
gtk_tool_shell_get_style proto __cdecl \
		 shell: ptr GtkToolShell

;GtkReliefStyle
gtk_tool_shell_get_relief_style proto __cdecl \
		 shell: ptr GtkToolShell

;void
gtk_tool_shell_rebuild_menu proto __cdecl \
		 shell: ptr GtkToolShell

;GtkOrientation
gtk_tool_shell_get_text_orientation proto __cdecl \
		 shell: ptr GtkToolShell

;gfloat
gtk_tool_shell_get_text_alignment proto __cdecl \
		 shell: ptr GtkToolShell

;PangoEllipsizeMode
gtk_tool_shell_get_ellipsize_mode proto __cdecl \
		 shell: ptr GtkToolShell

;GtkSizeGroup
gtk_tool_shell_get_text_size_group proto __cdecl \
		 shell: ptr GtkToolShell


G_END_DECLS

endif
