ifndef __GDK_DISPLAY_MANAGER_H__
__GDK_DISPLAY_MANAGER_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdktypes.inc
include gdk/gdkdisplay.inc

GDK_TYPE_DISPLAY_MANAGER equ <gdk_display_manager_get_type>
GDK_DISPLAY_MANAGER macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_DISPLAY_MANAGER, GdkDisplayManager))>
	endm
GDK_IS_DISPLAY_MANAGER macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_DISPLAY_MANAGER))>
	endm


;GType
gdk_display_manager_get_type proto __cdecl

;GdkDisplayManager
gdk_display_manager_get proto __cdecl
;GdkDisplay
gdk_display_manager_get_default_display proto __cdecl \
	       manager: ptr GdkDisplayManager

;void
gdk_display_manager_set_default_display proto __cdecl \
	       manager: ptr GdkDisplayManager,
	       display: ptr GdkDisplay

;GSList
gdk_display_manager_list_displays proto __cdecl \
	       manager: ptr GdkDisplayManager

;GdkDisplay
gdk_display_manager_open_display proto __cdecl \
	       manager: ptr GdkDisplayManager,
		  name: ptr gchar

endif
