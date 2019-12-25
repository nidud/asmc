ifndef __GDK_WINDOW_H__
__GDK_WINDOW_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc
include gdk/gdkevents.inc
include gdk/gdkframeclock.inc

.enum GdkWindowWindowClass {
  GDK_INPUT_OUTPUT,
  GDK_INPUT_ONLY
}

.enum GdkWindowType {
  GDK_WINDOW_ROOT,
  GDK_WINDOW_TOPLEVEL,
  GDK_WINDOW_CHILD,
  GDK_WINDOW_TEMP,
  GDK_WINDOW_FOREIGN,
  GDK_WINDOW_OFFSCREEN,
  GDK_WINDOW_SUBSURFACE
}

.enum GdkWindowAttributesType {
  GDK_WA_TITLE	   = 1 shl 1,
  GDK_WA_X	   = 1 shl 2,
  GDK_WA_Y	   = 1 shl 3,
  GDK_WA_CURSOR	   = 1 shl 4,
  GDK_WA_VISUAL	   = 1 shl 5,
  GDK_WA_WMCLASS   = 1 shl 6,
  GDK_WA_NOREDIR   = 1 shl 7,
  GDK_WA_TYPE_HINT = 1 shl 8
}

.enum GdkWindowHints {
  GDK_HINT_POS	       = 1 shl 0,
  GDK_HINT_MIN_SIZE    = 1 shl 1,
  GDK_HINT_MAX_SIZE    = 1 shl 2,
  GDK_HINT_BASE_SIZE   = 1 shl 3,
  GDK_HINT_ASPECT      = 1 shl 4,
  GDK_HINT_RESIZE_INC  = 1 shl 5,
  GDK_HINT_WIN_GRAVITY = 1 shl 6,
  GDK_HINT_USER_POS    = 1 shl 7,
  GDK_HINT_USER_SIZE   = 1 shl 8
}

.enum GdkWindowTypeHint {
  GDK_WINDOW_TYPE_HINT_NORMAL,
  GDK_WINDOW_TYPE_HINT_DIALOG,
  GDK_WINDOW_TYPE_HINT_MENU,
  GDK_WINDOW_TYPE_HINT_TOOLBAR,
  GDK_WINDOW_TYPE_HINT_SPLASHSCREEN,
  GDK_WINDOW_TYPE_HINT_UTILITY,
  GDK_WINDOW_TYPE_HINT_DOCK,
  GDK_WINDOW_TYPE_HINT_DESKTOP,
  GDK_WINDOW_TYPE_HINT_DROPDOWN_MENU,
  GDK_WINDOW_TYPE_HINT_POPUP_MENU,
  GDK_WINDOW_TYPE_HINT_TOOLTIP,
  GDK_WINDOW_TYPE_HINT_NOTIFICATION,
  GDK_WINDOW_TYPE_HINT_COMBO,
  GDK_WINDOW_TYPE_HINT_DND
}

.enum GdkWMDecoration {
  GDK_DECOR_ALL		= 1 shl 0,
  GDK_DECOR_BORDER	= 1 shl 1,
  GDK_DECOR_RESIZEH	= 1 shl 2,
  GDK_DECOR_TITLE	= 1 shl 3,
  GDK_DECOR_MENU	= 1 shl 4,
  GDK_DECOR_MINIMIZE	= 1 shl 5,
  GDK_DECOR_MAXIMIZE	= 1 shl 6
}

.enum GdkWMFunction {
  GDK_FUNC_ALL		= 1 shl 0,
  GDK_FUNC_RESIZE	= 1 shl 1,
  GDK_FUNC_MOVE		= 1 shl 2,
  GDK_FUNC_MINIMIZE	= 1 shl 3,
  GDK_FUNC_MAXIMIZE	= 1 shl 4,
  GDK_FUNC_CLOSE	= 1 shl 5
}

.enum GdkGravity {
  GDK_GRAVITY_NORTH_WEST = 1,
  GDK_GRAVITY_NORTH,
  GDK_GRAVITY_NORTH_EAST,
  GDK_GRAVITY_WEST,
  GDK_GRAVITY_CENTER,
  GDK_GRAVITY_EAST,
  GDK_GRAVITY_SOUTH_WEST,
  GDK_GRAVITY_SOUTH,
  GDK_GRAVITY_SOUTH_EAST,
  GDK_GRAVITY_STATIC
}

.enum GdkWindowEdge {
  GDK_WINDOW_EDGE_NORTH_WEST,
  GDK_WINDOW_EDGE_NORTH,
  GDK_WINDOW_EDGE_NORTH_EAST,
  GDK_WINDOW_EDGE_WEST,
  GDK_WINDOW_EDGE_EAST,
  GDK_WINDOW_EDGE_SOUTH_WEST,
  GDK_WINDOW_EDGE_SOUTH,
  GDK_WINDOW_EDGE_SOUTH_EAST
}

.enum GdkFullscreenMode {
  GDK_FULLSCREEN_ON_CURRENT_MONITOR,
  GDK_FULLSCREEN_ON_ALL_MONITORS
}

GdkWindowAttr		STRUC
title			string_t ?
event_mask		gint ?
x			gint ?
y			gint ?
width			gint ?
height			gint ?
wclass			GdkWindowWindowClass ?
visual			ptr_t ?
window_type		GdkWindowType ?
cursor			ptr_t ?
wmclass_name		string_t ?
wmclass_class		string_t ?
override_redirect	gboolean ?
type_hint		GdkWindowTypeHint ?
GdkWindowAttr		ENDS

GdkGeometry		STRUC
min_width		gint ?
min_height		gint ?
max_width		gint ?
max_height		gint ?
base_width		gint ?
base_height		gint ?
width_inc		gint ?
height_inc		gint ?
min_aspect		gdouble ?
max_aspect		gdouble ?
win_gravity		GdkGravity ?
GdkGeometry		ENDS

GDK_TYPE_WINDOW equ <gdk_window_get_type>
GDK_WINDOW macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_WINDOW, GdkWindow))>
	endm
GDK_WINDOW_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_WINDOW, GdkWindowClass))>
	endm
GDK_IS_WINDOW macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_WINDOW))>
	endm
GDK_IS_WINDOW_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_WINDOW))>
	endm
GDK_WINDOW_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_WINDOW, GdkWindowClass))>
	endm

GdkWindowClass		STRUC
parent_class		GObjectClass <>
pick_embedded_child	proc :ptr GdkWindow, :gdouble, :gdouble
to_embedder		proc :ptr GdkWindow, :gdouble, :gdouble, :ptr, :ptr
from_embedder		proc :ptr GdkWindow, :gdouble, :gdouble, :ptr, :ptr
create_surface		proc :ptr GdkWindow, :gint, :gint
_gdk_reserved1		proc
_gdk_reserved2		proc
_gdk_reserved3		proc
_gdk_reserved4		proc
_gdk_reserved5		proc
_gdk_reserved6		proc
_gdk_reserved7		proc
_gdk_reserved8		proc
GdkWindowClass		ENDS

;GType
gdk_window_get_type proto __cdecl
;GdkWindow*
gdk_window_new proto __cdecl \
		parent: ptr GdkWindow,
	    attributes: ptr GdkWindowAttr,
       attributes_mask: gint

;void
gdk_window_destroy proto __cdecl \
		window: ptr GdkWindow

;GdkWindowType
gdk_window_get_window_type proto __cdecl \
		window: ptr GdkWindow

;gboolean
gdk_window_is_destroyed proto __cdecl \
		window: ptr GdkWindow


;GdkVisual
gdk_window_get_visual proto __cdecl \
		window: ptr GdkWindow

;GdkScreen
gdk_window_get_screen proto __cdecl \
		window: ptr GdkWindow

;GdkDisplay
gdk_window_get_display proto __cdecl \
		window: ptr GdkWindow

ifndef GDK_MULTIDEVICE_SAFE
;GdkWindow*
gdk_window_at_pointer proto __cdecl \
		 win_x: ptr gint,
		 win_y: ptr gint

endif
;void
gdk_window_show proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_hide proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_withdraw proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_show_unraised proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_move proto __cdecl \
		window: ptr GdkWindow,
		     x: gint,
		     y: gint

;void
gdk_window_resize proto __cdecl \
		window: ptr GdkWindow,
		 width: gint,
		height: gint

;void
gdk_window_move_resize proto __cdecl \
		window: ptr GdkWindow,
		     x: gint,
		     y: gint,
		 width: gint,
		height: gint

;void
gdk_window_reparent proto __cdecl \
		window: ptr GdkWindow,
	    new_parent: ptr GdkWindow,
		     x: gint,
		     y: gint

;void
gdk_window_raise proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_lower proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_restack proto __cdecl \
		window: ptr GdkWindow,
	       sibling: ptr GdkWindow,
		 above: gboolean

;void
gdk_window_focus proto __cdecl \
		window: ptr GdkWindow,
	     timestamp: guint32

;void
gdk_window_set_user_data proto __cdecl \
		window: ptr GdkWindow,
	     user_data: gpointer

;void
gdk_window_set_override_redirect proto __cdecl \
		window: ptr GdkWindow,
     override_redirect: gboolean

;gboolean
gdk_window_get_accept_focus proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_set_accept_focus proto __cdecl \
		window: ptr GdkWindow,
	  accept_focus: gboolean

;gboolean
gdk_window_get_focus_on_map proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_set_focus_on_map proto __cdecl \
		window: ptr GdkWindow,
	  focus_on_map: gboolean

;void
gdk_window_add_filter proto __cdecl \
		window: ptr GdkWindow,
	      function: GdkFilterFunc,
		  data: gpointer

;void
gdk_window_remove_filter proto __cdecl \
		window: ptr GdkWindow,
	      function: GdkFilterFunc,
		  data: gpointer

;void
gdk_window_scroll proto __cdecl \
		window: ptr GdkWindow,
		   _dx: gint,
		    dy: gint

;void
gdk_window_move_region proto __cdecl \
		window: ptr GdkWindow,
		region: ptr cairo_region_t,
		   _dx: gint,
		    dy: gint

;gboolean
gdk_window_ensure_native proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_shape_combine_region proto __cdecl \
		window: ptr GdkWindow,
	  shape_region: ptr cairo_region_t,
	      offset_x: gint,
	      offset_y: gint


;void
gdk_window_set_child_shapes proto __cdecl \
		window: ptr GdkWindow


;gboolean
gdk_window_get_composited proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_set_composited proto __cdecl \
		window: ptr GdkWindow,
	    composited: gboolean

;void
gdk_window_merge_child_shapes proto __cdecl \
		window: ptr GdkWindow


;void
gdk_window_input_shape_combine_region proto __cdecl \
		window: ptr GdkWindow,
	  shape_region: ptr cairo_region_t,
	      offset_x: gint,
	      offset_y: gint

;void
gdk_window_set_child_input_shapes proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_merge_child_input_shapes proto __cdecl \
		window: ptr GdkWindow



;void
gdk_window_set_pass_through proto __cdecl \
		window: ptr GdkWindow,
	  pass_through: gboolean

;gboolean
gdk_window_get_pass_through proto __cdecl \
		window: ptr GdkWindow

;gboolean
gdk_window_is_visible proto __cdecl \
		window: ptr GdkWindow

;gboolean
gdk_window_is_viewable proto __cdecl \
		window: ptr GdkWindow

;gboolean
gdk_window_is_input_only proto __cdecl \
		window: ptr GdkWindow

;gboolean
gdk_window_is_shaped proto __cdecl \
		window: ptr GdkWindow

;GdkWindowState
gdk_window_get_state proto __cdecl \
		window: ptr GdkWindow

;gboolean
gdk_window_set_static_gravities proto __cdecl \
		window: ptr GdkWindow,
	    use_static: gboolean


CALLBACKC(GdkWindowInvalidateHandlerFunc, :ptr GdkWindow, :ptr)


gdk_window_set_invalidate_handler proto __cdecl \
		window: ptr GdkWindow,
	       handler: GdkWindowInvalidateHandlerFunc


;gboolean
gdk_window_has_native proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_set_type_hint proto __cdecl \
		window: ptr GdkWindow,
		  hint: GdkWindowTypeHint

;GdkWindowTypeHint
gdk_window_get_type_hint proto __cdecl \
		window: ptr GdkWindow


;gboolean
gdk_window_get_modal_hint proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_set_modal_hint proto __cdecl \
		window: ptr GdkWindow,
		 modal: gboolean


;void
gdk_window_set_skip_taskbar_hint proto __cdecl \
		window: ptr GdkWindow,
	 skips_taskbar: gboolean

;void
gdk_window_set_skip_pager_hint proto __cdecl \
		window: ptr GdkWindow,
	   skips_pager: gboolean

;void
gdk_window_set_urgency_hint proto __cdecl \
		window: ptr GdkWindow,
		urgent: gboolean


;void
gdk_window_set_geometry_hints proto __cdecl \
		window: ptr GdkWindow,
	      geometry: ptr GdkGeometry,
	     geom_mask: GdkWindowHints


;cairo_region_t
gdk_window_get_clip_region proto __cdecl \
		window: ptr GdkWindow

;cairo_region_t
gdk_window_get_visible_region proto __cdecl \
		window: ptr GdkWindow



;void
gdk_window_begin_paint_rect proto __cdecl \
		window: ptr GdkWindow,
	     rectangle: ptr GdkRectangle

;void
gdk_window_mark_paint_from_clip proto __cdecl \
		window: ptr GdkWindow,
		    cr: ptr cairo_t

;void
gdk_window_begin_paint_region proto __cdecl \
		window: ptr GdkWindow,
		region: ptr cairo_region_t

;void
gdk_window_end_paint proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_flush proto __cdecl \
		window: ptr GdkWindow


;void
gdk_window_set_title proto __cdecl \
		window: ptr GdkWindow,
		 title: ptr gchar

;void
gdk_window_set_role proto __cdecl \
		window: ptr GdkWindow,
		  role: ptr gchar

;void
gdk_window_set_startup_id proto __cdecl \
		window: ptr GdkWindow,
	    startup_id: ptr gchar

;void
gdk_window_set_transient_for proto __cdecl \
		window: ptr GdkWindow,
		parent: ptr GdkWindow

;void
gdk_window_set_background proto __cdecl \
		window: ptr GdkWindow,
		 color: ptr GdkColor

;void
gdk_window_set_background_rgba proto __cdecl \
		window: ptr GdkWindow,
		  rgba: ptr GdkRGBA

;void
gdk_window_set_background_pattern proto __cdecl \
		window: ptr GdkWindow,
	       pattern: ptr cairo_pattern_t

;cairo_pattern_t
gdk_window_get_background_pattern proto __cdecl \
		window: ptr GdkWindow


;void
gdk_window_set_cursor proto __cdecl \
		window: ptr GdkWindow,
		cursor: ptr GdkCursor

;GdkCursor
gdk_window_get_cursor proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_set_device_cursor proto __cdecl \
		window: ptr GdkWindow,
		device: ptr GdkDevice,
		cursor: ptr GdkCursor

;GdkCursor
gdk_window_get_device_cursor proto __cdecl \
		window: ptr GdkWindow,
		device: ptr GdkDevice

;void
gdk_window_get_user_data proto __cdecl \
		window: ptr GdkWindow,
		  data: ptr gpointer

;void
gdk_window_get_geometry proto __cdecl \
		window: ptr GdkWindow,
		     x: ptr gint,
		     y: ptr gint,
		 width: ptr gint,
		height: ptr gint

;int
gdk_window_get_width proto __cdecl \
		window: ptr GdkWindow

;int
gdk_window_get_height proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_get_position proto __cdecl \
		window: ptr GdkWindow,
		     x: ptr gint,
		     y: ptr gint

;gint
gdk_window_get_origin proto __cdecl \
		window: ptr GdkWindow,
		     x: ptr gint,
		     y: ptr gint

;void
gdk_window_get_root_coords proto __cdecl \
		window: ptr GdkWindow,
		     x: gint,
		     y: gint,
		root_x: ptr gint,
		root_y: ptr gint

;void
gdk_window_coords_to_parent proto __cdecl \
		window: ptr GdkWindow,
		     x: gdouble,
		     y: gdouble,
	      parent_x: ptr gdouble,
	      parent_y: ptr gdouble

;void
gdk_window_coords_from_parent proto __cdecl \
		window: ptr GdkWindow,
	      parent_x: gdouble,
	      parent_y: gdouble,
		     x: ptr gdouble,
		     y: ptr gdouble


;void
gdk_window_get_root_origin proto __cdecl \
		window: ptr GdkWindow,
		     x: ptr gint,
		     y: ptr gint

;void
gdk_window_get_frame_extents proto __cdecl \
		window: ptr GdkWindow,
		  rect: ptr GdkRectangle


;gint
gdk_window_get_scale_factor proto __cdecl \
		window: ptr GdkWindow


ifndef GDK_MULTIDEVICE_SAFE
;GdkWindow
gdk_window_get_pointer proto __cdecl \
		window: ptr GdkWindow,
		     x: ptr gint,
		     y: ptr gint,
		  mask: ptr GdkModifierType

endif
;GdkWindow
gdk_window_get_device_position proto __cdecl \
		window: ptr GdkWindow,
		device: ptr GdkDevice,
		     x: ptr gint,
		     y: ptr gint,
		  mask: ptr GdkModifierType

;GdkWindow
gdk_window_get_device_position_double proto __cdecl \
		window: ptr GdkWindow,
		device: ptr GdkDevice,
		     x: ptr gdouble,
		     y: ptr gdouble,
		  mask: ptr GdkModifierType

;GdkWindow
gdk_window_get_parent proto __cdecl \
		window: ptr GdkWindow

;GdkWindow
gdk_window_get_toplevel proto __cdecl \
		window: ptr GdkWindow


;GdkWindow
gdk_window_get_effective_parent proto __cdecl \
		window: ptr GdkWindow

;GdkWindow
gdk_window_get_effective_toplevel proto __cdecl \
		window: ptr GdkWindow


;GList
gdk_window_get_children proto __cdecl \
		window: ptr GdkWindow

;GList
gdk_window_peek_children proto __cdecl \
		window: ptr GdkWindow

;GList
gdk_window_get_children_with_user_data proto __cdecl \
		window: ptr GdkWindow,
	     user_data: gpointer


;GdkEventMask
gdk_window_get_events proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_set_events proto __cdecl \
		window: ptr GdkWindow,
	    event_mask: GdkEventMask

;void
gdk_window_set_device_events proto __cdecl \
		window: ptr GdkWindow,
		device: ptr GdkDevice,
	    event_mask: GdkEventMask

;GdkEventMask
gdk_window_get_device_events proto __cdecl \
		window: ptr GdkWindow,
		device: ptr GdkDevice


;void
gdk_window_set_source_events proto __cdecl \
		window: ptr GdkWindow,
		source: GdkInputSource,
	    event_mask: GdkEventMask

;GdkEventMask
gdk_window_get_source_events proto __cdecl \
		window: ptr GdkWindow,
		source: GdkInputSource


;void
gdk_window_set_icon_list proto __cdecl \
		window: ptr GdkWindow,
	       pixbufs: ptr GList

;void
gdk_window_set_icon_name proto __cdecl \
		window: ptr GdkWindow,
		  name: ptr gchar

;void
gdk_window_set_group proto __cdecl \
		window: ptr GdkWindow,
		leader: ptr GdkWindow

;GdkWindow*
gdk_window_get_group proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_set_decorations proto __cdecl \
		window: ptr GdkWindow,
	   decorations: GdkWMDecoration

;gboolean
gdk_window_get_decorations proto __cdecl \
		window: ptr GdkWindow,
	   decorations: ptr GdkWMDecoration

;void
gdk_window_set_functions proto __cdecl \
		window: ptr GdkWindow,
	     functions: GdkWMFunction


;cairo_surface_t
gdk_window_create_similar_surface proto __cdecl \
		window: ptr GdkWindow,
	       content: ptr, ;cairo_content_t,
		 width: int_t,
		height: int_t

;cairo_surface_t
gdk_window_create_similar_image_surface proto __cdecl \
		window: ptr GdkWindow,
		format: ptr, ;cairo_content_t,
		 width: int_t,
		height: int_t,
		 scale: int_t


;void
gdk_window_beep proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_iconify proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_deiconify proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_stick proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_unstick proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_maximize proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_unmaximize proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_fullscreen proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_fullscreen_on_monitor proto __cdecl \
		window: ptr GdkWindow,
	      _monitor: gint

;void
gdk_window_set_fullscreen_mode proto __cdecl \
		window: ptr GdkWindow,
		  mode: GdkFullscreenMode

;GdkFullscreenMode
gdk_window_get_fullscreen_mode proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_unfullscreen proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_set_keep_above proto __cdecl \
		window: ptr GdkWindow,
	       setting: gboolean

;void
gdk_window_set_keep_below proto __cdecl \
		window: ptr GdkWindow,
	       setting: gboolean

;void
gdk_window_set_opacity proto __cdecl \
		window: ptr GdkWindow,
	       opacity: gdouble

;void
gdk_window_register_dnd proto __cdecl \
		window: ptr GdkWindow


;GdkDragProtocol
gdk_window_get_drag_protocol proto __cdecl \
		window: ptr GdkWindow,
		target: ptr GdkWindow


;void
gdk_window_begin_resize_drag proto __cdecl \
		window: ptr GdkWindow,
		  edge: GdkWindowEdge,
		button: gint,
		root_x: gint,
		root_y: gint,
	     timestamp: guint32

;void
gdk_window_begin_resize_drag_for_device proto __cdecl \
		window: ptr GdkWindow,
		  edge: GdkWindowEdge,
		device: ptr GdkDevice,
		button: gint,
		root_x: gint,
		root_y: gint,
	     timestamp: guint32

;void
gdk_window_begin_move_drag proto __cdecl \
		window: ptr GdkWindow,
		button: gint,
		root_x: gint,
		root_y: gint,
	     timestamp: guint32

;void
gdk_window_begin_move_drag_for_device proto __cdecl \
		window: ptr GdkWindow,
		device: ptr GdkDevice,
		button: gint,
		root_x: gint,
		root_y: gint,
	     timestamp: guint32


;void
gdk_window_invalidate_rect proto __cdecl \
		window: ptr GdkWindow,
		  rect: ptr GdkRectangle,
   invalidate_children: gboolean

;void
gdk_window_invalidate_region proto __cdecl \
		window: ptr GdkWindow,
		region: ptr cairo_region_t,
   invalidate_children: gboolean


CALLBACKC(GdkWindowChildFunc, :ptr GdkWindow, :gpointer)

;void
gdk_window_invalidate_maybe_recurse proto __cdecl \
		window: ptr GdkWindow,
		region: ptr cairo_region_t,
	    child_func: GdkWindowChildFunc,
	     user_data: gpointer

;cairo_region_t
gdk_window_get_update_area proto __cdecl \
		window: ptr GdkWindow


;void
gdk_window_freeze_updates proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_thaw_updates proto __cdecl \
		window: ptr GdkWindow


;void
gdk_window_freeze_toplevel_updates_libgtk_only proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_thaw_toplevel_updates_libgtk_only proto __cdecl \
		window: ptr GdkWindow


;void
gdk_window_process_all_updates proto __cdecl
;void
gdk_window_process_updates proto __cdecl \
		window: ptr GdkWindow,
       update_children: gboolean


;void
gdk_window_set_debug_updates proto __cdecl \
	       setting: gboolean


;void
gdk_window_constrain_size proto __cdecl \
	      geometry: ptr GdkGeometry,
		 flags: GdkWindowHints,
		 width: gint,
		height: gint,
	     new_width: ptr gint,
	    new_height: ptr gint


;void
gdk_window_enable_synchronized_configure proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_configure_finished proto __cdecl \
		window: ptr GdkWindow


;GdkWindow
gdk_get_default_root_window proto __cdecl

;cairo_surface_t
gdk_offscreen_window_get_surface proto __cdecl \
		window: ptr GdkWindow

;void
gdk_offscreen_window_set_embedder proto __cdecl \
		window: ptr GdkWindow,
	      embedder: ptr GdkWindow

;GdkWindow
gdk_offscreen_window_get_embedder proto __cdecl \
		window: ptr GdkWindow

;void
gdk_window_geometry_changed proto __cdecl \
		window: ptr GdkWindow


;void
gdk_window_set_support_multidevice proto __cdecl \
		window: ptr GdkWindow,
   support_multidevice: gboolean

;gboolean
gdk_window_get_support_multidevice proto __cdecl \
		window: ptr GdkWindow


;GdkFrameClock*
gdk_window_get_frame_clock proto __cdecl \
		window: ptr GdkWindow


;void
gdk_window_set_opaque_region proto __cdecl \
		window: ptr GdkWindow,
		region: ptr cairo_region_t


;void
gdk_window_set_event_compression proto __cdecl \
		window: ptr GdkWindow,
     event_compression: gboolean

;gboolean
gdk_window_get_event_compression proto __cdecl \
		window: ptr GdkWindow


;void
gdk_window_set_shadow_width proto __cdecl \
		window: ptr GdkWindow,
		  left: gint,
		 right: gint,
		   top: gint,
		bottom: gint

;gboolean
gdk_window_show_window_menu proto __cdecl \
		window: ptr GdkWindow,
		 event: ptr GdkEvent


;GdkGLContext
gdk_window_create_gl_context proto __cdecl \
		window: ptr GdkWindow,
		 error: ptr GError


endif
