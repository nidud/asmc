ifndef __GDK_DND_H__
__GDK_DND_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdktypes.inc
include gdk/gdkdevice.inc

GDK_TYPE_DRAG_CONTEXT	equ <gdk_drag_context_get_type>
GDK_DRAG_CONTEXT macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_DRAG_CONTEXT, GdkDragContext))>
	endm
GDK_IS_DRAG_CONTEXT macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_DRAG_CONTEXT))>
	endm

.enum GdkDragAction {
  GDK_ACTION_DEFAULT = 1 shl 0,
  GDK_ACTION_COPY    = 1 shl 1,
  GDK_ACTION_MOVE    = 1 shl 2,
  GDK_ACTION_LINK    = 1 shl 3,
  GDK_ACTION_PRIVATE = 1 shl 4,
  GDK_ACTION_ASK     = 1 shl 5
}

.enum GdkDragProtocol {
  GDK_DRAG_PROTO_NONE = 0,
  GDK_DRAG_PROTO_MOTIF,
  GDK_DRAG_PROTO_XDND,
  GDK_DRAG_PROTO_ROOTWIN,
  GDK_DRAG_PROTO_WIN32_DROPFILES,
  GDK_DRAG_PROTO_OLE2,
  GDK_DRAG_PROTO_LOCAL,
  GDK_DRAG_PROTO_WAYLAND
}


;GType
gdk_drag_context_get_type proto __cdecl

;void
gdk_drag_context_set_device proto __cdecl \
	       context: ptr GdkDragContext,
		device: ptr GdkDevice

;GdkDevice
gdk_drag_context_get_device proto __cdecl \
	       context: ptr GdkDragContext


;GList
gdk_drag_context_list_targets proto __cdecl \
	       context: ptr GdkDragContext

;GdkDragAction
gdk_drag_context_get_actions proto __cdecl \
	       context: ptr GdkDragContext

;GdkDragAction
gdk_drag_context_get_suggested_action proto __cdecl \
	       context: ptr GdkDragContext

;GdkDragAction
gdk_drag_context_get_selected_action proto __cdecl \
	       context: ptr GdkDragContext


;GdkWindow
gdk_drag_context_get_source_window proto __cdecl \
	       context: ptr GdkDragContext

;GdkWindow
gdk_drag_context_get_dest_window proto __cdecl \
	       context: ptr GdkDragContext

;GdkDragProtocol
gdk_drag_context_get_protocol proto __cdecl \
	       context: ptr GdkDragContext



;void
gdk_drag_status proto __cdecl \
	       context: ptr GdkDragContext,
		action: GdkDragAction,
		 time_: guint32

;void
gdk_drop_reply proto __cdecl \
	       context: ptr GdkDragContext,
	      accepted: gboolean,
		 time_: guint32

;void
gdk_drop_finish proto __cdecl \
	       context: ptr GdkDragContext,
	       success: gboolean,
		 time_: guint32

;GdkAtom
gdk_drag_get_selection proto __cdecl \
	       context: ptr GdkDragContext



;GdkDragContext
gdk_drag_begin proto __cdecl \
		window: ptr GdkWindow,
	       targets: ptr GList


;GdkDragContext
gdk_drag_begin_for_device proto __cdecl \
		window: ptr GdkWindow,
		device: ptr GdkDevice,
	       targets: ptr GList


;void
gdk_drag_find_window_for_screen proto __cdecl \
	       context: ptr GdkDragContext,
	   drag_window: ptr GdkWindow,
		screen: ptr GdkScreen,
		x_root: gint,
		y_root: gint,
	   dest_window: ptr GdkWindow,
	      protocol: ptr GdkDragProtocol


;gboolean
gdk_drag_motion proto __cdecl \
	       context: ptr GdkDragContext,
	   dest_window: ptr GdkWindow,
	      protocol: GdkDragProtocol,
		x_root: gint,
		y_root: gint,
      suggested_action: GdkDragAction,
      possible_actions: GdkDragAction,
		 time_: guint32

;void
gdk_drag_drop proto __cdecl \
	       context: ptr GdkDragContext,
		 time_: guint32

;void
gdk_drag_abort proto __cdecl \
	       context: ptr GdkDragContext,
		 time_: guint32

;gboolean
gdk_drag_drop_succeeded proto __cdecl \
	       context: ptr GdkDragContext

endif
