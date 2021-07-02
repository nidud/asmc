ifndef __GTK_WIDGET_H__
__GTK_WIDGET_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkaccelgroup.inc
include gtk/gtkborder.inc
include gtk/gtktypes.inc
;include atk/atk.inc

.enum GtkWidgetHelpType {
    GTK_WIDGET_HELP_TOOLTIP,
    GTK_WIDGET_HELP_WHATS_THIS
}

GTK_TYPE_WIDGET equ <gtk_widget_get_type>
GTK_WIDGET macro widget
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((widget), GTK_TYPE_WIDGET, GtkWidget))>
	endm
GTK_WIDGET_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_WIDGET, GtkWidgetClass))>
	endm
GTK_IS_WIDGET macro widget
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((widget), GTK_TYPE_WIDGET))>
	endm
GTK_IS_WIDGET_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_WIDGET))>
	endm
GTK_WIDGET_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_WIDGET, GtkWidgetClass))>
	endm

GTK_TYPE_REQUISITION	equ <gtk_requisition_get_type>

GtkAllocation		typedef GdkRectangle

CALLBACKC(GtkCallback, :ptr GtkWidget, :gpointer)
CALLBACKC(GtkTickCallback, :ptr GtkWidget, :ptr GdkFrameClock, :gpointer)

GtkRequisition		STRUC
width			gint ?
height			gint ?
GtkRequisition		ENDS

GtkWidget		STRUC
parent_instance		GInitiallyUnowned <>
priv			ptr_t ?
GtkWidget		ENDS

GtkWidgetClass		STRUC
parent_class		GInitiallyUnownedClass <>
activate_signal		guint ?
dispatch_child_properties_changed proc :ptr GtkWidget, :guint, :ptr GParamSpec
destroy			proc :ptr GtkWidget
show			proc :ptr GtkWidget
show_all		proc :ptr GtkWidget
hide			proc :ptr GtkWidget
map			proc :ptr GtkWidget
unmap			proc :ptr GtkWidget
realize			proc :ptr GtkWidget
unrealize		proc :ptr GtkWidget
size_allocate		proc :ptr GtkWidget, :ptr GtkAllocation
state_changed		proc :ptr GtkWidget, :GtkStateType
state_flags_changed	proc :ptr GtkWidget, :GtkStateFlags
parent_set		proc :ptr GtkWidget, :ptr GtkWidget
hierarchy_changed	proc :ptr GtkWidget, :ptr GtkWidget
style_set		proc :ptr GtkWidget, :ptr GtkStyle
direction_changed	proc :ptr GtkWidget, :GtkTextDirection
grab_notify		proc :ptr GtkWidget, :gboolean
child_notify		proc :ptr GtkWidget, :ptr GParamSpec
draw			proc :ptr GtkWidget, :ptr
get_request_mode	proc :ptr GtkWidget
get_preferred_height	proc :ptr GtkWidget, :ptr gint, :ptr gint
get_preferred_width_for_height proc :ptr GtkWidget, :gint, :ptr gint, :ptr gint
get_preferred_width	proc :ptr GtkWidget, :ptr gint, :ptr gint
get_preferred_height_for_width proc :ptr GtkWidget, :gint, :ptr gint, :ptr gint
mnemonic_activate	proc :ptr GtkWidget, :gboolean
grab_focus		proc :ptr GtkWidget
focus			proc :ptr GtkWidget, :GtkDirectionType
move_focus		proc :ptr GtkWidget, :GtkDirectionType
keynav_failed		proc :ptr GtkWidget, :GtkDirectionType
event			proc :ptr GtkWidget, :ptr GdkEvent
button_press_event	proc :ptr GtkWidget, :ptr GdkEventButton
button_release_event	proc :ptr GtkWidget, :ptr GdkEventButton
scroll_event		proc :ptr GtkWidget, :ptr GdkEventScroll
motion_notify_event	proc :ptr GtkWidget, :ptr GdkEventMotion
delete_event		proc :ptr GtkWidget, :ptr GdkEventAny
destroy_event		proc :ptr GtkWidget, :ptr GdkEventAny
key_press_event		proc :ptr GtkWidget, :ptr GdkEventKey
key_release_event	proc :ptr GtkWidget, :ptr GdkEventKey
enter_notify_event	proc :ptr GtkWidget, :ptr GdkEventCrossing
leave_notify_event	proc :ptr GtkWidget, :ptr GdkEventCrossing
configure_event		proc :ptr GtkWidget, :ptr GdkEventConfigure
focus_in_event		proc :ptr GtkWidget, :ptr GdkEventFocus
focus_out_event		proc :ptr GtkWidget, :ptr GdkEventFocus
map_event		proc :ptr GtkWidget, :ptr GdkEventAny
unmap_event		proc :ptr GtkWidget, :ptr GdkEventAny
property_notify_event	proc :ptr GtkWidget, :ptr GdkEventProperty
selection_clear_event	proc :ptr GtkWidget, :ptr GdkEventSelection
selection_request_event proc :ptr GtkWidget, :ptr GdkEventSelection
selection_notify_event	proc :ptr GtkWidget, :ptr GdkEventSelection
proximity_in_event	proc :ptr GtkWidget, :ptr GdkEventProximity
proximity_out_event	proc :ptr GtkWidget, :ptr GdkEventProximity
visibility_notify_event proc :ptr GtkWidget, :ptr GdkEventVisibility
window_state_event	proc :ptr GtkWidget, :ptr GdkEventWindowState
damage_event		proc :ptr GtkWidget, :ptr GdkEventExpose
grab_broken_event	proc :ptr GtkWidget, :ptr GdkEventGrabBroken
selection_get		proc :ptr GtkWidget, :ptr GtkSelectionData, :guint, :guint
selection_received	proc :ptr GtkWidget, :ptr GtkSelectionData, :guint
drag_begin		proc :ptr GtkWidget, :ptr GdkDragContext
drag_end		proc :ptr GtkWidget, :ptr GdkDragContext
drag_data_get		proc :ptr GtkWidget, :ptr GdkDragContext, :ptr GtkSelectionData, :guint, :guint
drag_data_delete	proc :ptr GtkWidget, :ptr GdkDragContext
drag_leave		proc :ptr GtkWidget, :ptr GdkDragContext, :guint
drag_motion		proc :ptr GtkWidget, :ptr GdkDragContext, :gint, :gint, :guint
drag_drop		proc :ptr GtkWidget, :ptr GdkDragContext, :gint, :gint, :guint
drag_data_received	proc :ptr GtkWidget, :ptr GdkDragContext, :gint, :gint, :ptr GtkSelectionData, :guint, :guint
drag_failed		proc :ptr GtkWidget, :ptr GdkDragContext, :GtkDragResult
popup_menu		proc :ptr GtkWidget
show_help		proc :ptr GtkWidget, :GtkWidgetHelpType
get_accessible		proc :ptr GtkWidget
screen_changed		proc :ptr GtkWidget, :ptr GdkScreen
can_activate_accel	proc :ptr GtkWidget, :guint
composited_changed	proc :ptr GtkWidget
query_tooltip		proc :ptr GtkWidget, :gint,  :gint, :gboolean, :ptr GtkTooltip
compute_expand		proc :ptr GtkWidget, :ptr gboolean, :ptr gboolean
adjust_size_request	proc :ptr GtkWidget, :GtkOrientation, :ptr gint, :ptr gint
adjust_size_allocation	proc :ptr GtkWidget, :GtkOrientation, :ptr gint, :ptr gint, :ptr gint, :ptr gint
style_updated		proc :ptr GtkWidget
touch_event		proc :ptr GtkWidget, :ptr GdkEventTouch
get_preferred_height_and_baseline_for_width proc :ptr GtkWidget, :gint, :ptr gint, :ptr gint, :ptr gint, :ptr gint
adjust_baseline_request proc :ptr GtkWidget, :ptr gint, :ptr gint
adjust_baseline_allocation proc :ptr GtkWidget, :ptr gint
queue_draw_region	proc :ptr GtkWidget, :ptr cairo_region_t
priv			ptr_t ?
_gtk_reserved6		proc
_gtk_reserved7		proc
GtkWidgetClass		ENDS


;GType
gtk_widget_get_type proto __cdecl
;GtkWidget*
gtk_widget_new proto _CDecl \
		  type: GType,
   first_property_name: ptr gchar,
		      : vararg

;void
gtk_widget_destroy proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_destroyed proto __cdecl \
		widget: ptr GtkWidget,
	widget_pointer: ptr GtkWidget

;void
gtk_widget_unparent proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_show proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_hide proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_show_now proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_show_all proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_no_show_all proto __cdecl \
		widget: ptr GtkWidget,
	   no_show_all: gboolean

;gboolean
gtk_widget_get_no_show_all proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_map proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_unmap proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_realize proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_unrealize proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_draw proto __cdecl \
		widget: ptr GtkWidget,
		    cr: ptr cairo_t

;void
gtk_widget_queue_draw proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_queue_draw_area proto __cdecl \
		widget: ptr GtkWidget,
		     x: gint,
		     y: gint,
		 width: gint,
		height: gint

;void
gtk_widget_queue_draw_region proto __cdecl \
		widget: ptr GtkWidget,
		region: ptr cairo_region_t

;void
gtk_widget_queue_resize proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_queue_resize_no_redraw proto __cdecl \
		widget: ptr GtkWidget

;GdkFrameClock*
gtk_widget_get_frame_clock proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_size_request proto __cdecl \
		widget: ptr GtkWidget,
	   requisition: ptr GtkRequisition

;void
gtk_widget_size_allocate proto __cdecl \
		widget: ptr GtkWidget,
	    allocation: ptr GtkAllocation

;void
gtk_widget_size_allocate_with_baseline proto __cdecl \
		widget: ptr GtkWidget,
	    allocation: ptr GtkAllocation,
	      baseline: gint


;GtkSizeRequestMode
gtk_widget_get_request_mode proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_get_preferred_width proto __cdecl \
		widget: ptr GtkWidget,
	 minimum_width: ptr gint,
	 natural_width: ptr gint

;void
gtk_widget_get_preferred_height_for_width proto __cdecl \
		widget: ptr GtkWidget,
		 width: gint,
	minimum_height: ptr gint,
	natural_height: ptr gint

;void
gtk_widget_get_preferred_height proto __cdecl \
		widget: ptr GtkWidget,
	minimum_height: ptr gint,
	natural_height: ptr gint

;void
gtk_widget_get_preferred_width_for_height proto __cdecl \
		widget: ptr GtkWidget,
		height: gint,
	 minimum_width: ptr gint,
	 natural_width: ptr gint

;void
gtk_widget_get_preferred_height_and_baseline_for_width proto __cdecl \
		widget: ptr GtkWidget,
		 width: gint,
	minimum_height: ptr gint,
	natural_height: ptr gint,
      minimum_baseline: ptr gint,
      natural_baseline: ptr gint

;void
gtk_widget_get_preferred_size proto __cdecl \
		widget: ptr GtkWidget,
	  minimum_size: ptr GtkRequisition,
	  natural_size: ptr GtkRequisition


;void
gtk_widget_get_child_requisition proto __cdecl \
		widget: ptr GtkWidget,
	   requisition: ptr GtkRequisition

;void
gtk_widget_add_accelerator proto __cdecl \
		widget: ptr GtkWidget,
	  accel_signal: ptr gchar,
	   accel_group: ptr GtkAccelGroup,
	     accel_key: guint,
	    accel_mods: GdkModifierType,
	   accel_flags: GtkAccelFlags

;gboolean
gtk_widget_remove_accelerator proto __cdecl \
		widget: ptr GtkWidget,
	   accel_group: ptr GtkAccelGroup,
	     accel_key: guint,
	    accel_mods: GdkModifierType

;void
gtk_widget_set_accel_path proto __cdecl \
		widget: ptr GtkWidget,
	    accel_path: ptr gchar,
	   accel_group: ptr GtkAccelGroup

;GList*
gtk_widget_list_accel_closures proto __cdecl \
		widget: ptr GtkWidget

;gboolean
gtk_widget_can_activate_accel proto __cdecl \
		widget: ptr GtkWidget,
	     signal_id: guint

;gboolean
gtk_widget_mnemonic_activate proto __cdecl \
		widget: ptr GtkWidget,
	 group_cycling: gboolean

;gboolean
gtk_widget_event proto __cdecl \
		widget: ptr GtkWidget,
		 event: ptr GdkEvent

;gint
gtk_widget_send_expose proto __cdecl \
		widget: ptr GtkWidget,
		 event: ptr GdkEvent

;gboolean
gtk_widget_send_focus_change proto __cdecl \
		widget: ptr GtkWidget,
		 event: ptr GdkEvent


;gboolean
gtk_widget_activate proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_reparent proto __cdecl \
		widget: ptr GtkWidget,
	    new_parent: ptr GtkWidget

;gboolean
gtk_widget_intersect proto __cdecl \
		widget: ptr GtkWidget,
		  area: ptr GdkRectangle,
	  intersection: ptr GdkRectangle

;cairo_region_t
gtk_widget_region_intersect proto __cdecl \
		widget: ptr GtkWidget,
		region: ptr cairo_region_t


;void
gtk_widget_freeze_child_notify proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_child_notify proto __cdecl \
		widget: ptr GtkWidget,
	child_property: ptr gchar

;void
gtk_widget_thaw_child_notify proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_can_focus proto __cdecl \
		widget: ptr GtkWidget,
	     can_focus: gboolean

;gboolean
gtk_widget_get_can_focus proto __cdecl \
		widget: ptr GtkWidget

;gboolean
gtk_widget_has_focus proto __cdecl \
		widget: ptr GtkWidget

;gboolean
gtk_widget_is_focus proto __cdecl \
		widget: ptr GtkWidget

;gboolean
gtk_widget_has_visible_focus proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_grab_focus proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_can_default proto __cdecl \
		widget: ptr GtkWidget,
	   can_default: gboolean

;gboolean
gtk_widget_get_can_default proto __cdecl \
		widget: ptr GtkWidget

;gboolean
gtk_widget_has_default proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_grab_default proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_receives_default proto __cdecl \
		widget: ptr GtkWidget,
      receives_default: gboolean

;gboolean
gtk_widget_get_receives_default proto __cdecl \
		widget: ptr GtkWidget


;gboolean
gtk_widget_has_grab proto __cdecl \
		widget: ptr GtkWidget


;gboolean
gtk_widget_device_is_shadowed proto __cdecl \
		widget: ptr GtkWidget,
		device: ptr GdkDevice



;void
gtk_widget_set_name proto __cdecl \
		widget: ptr GtkWidget,
		  name: ptr gchar

;const
gtk_widget_get_name proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_state proto __cdecl \
		widget: ptr GtkWidget,
		 state: GtkStateType


;GtkStateType
gtk_widget_get_state proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_state_flags proto __cdecl \
		widget: ptr GtkWidget,
		 flags: GtkStateFlags,
		 clear: gboolean

;void
gtk_widget_unset_state_flags proto __cdecl \
		widget: ptr GtkWidget,
		 flags: GtkStateFlags

;GtkStateFlags
gtk_widget_get_state_flags proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_sensitive proto __cdecl \
		widget: ptr GtkWidget,
	     sensitive: gboolean

;gboolean
gtk_widget_get_sensitive proto __cdecl \
		widget: ptr GtkWidget

;gboolean
gtk_widget_is_sensitive proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_visible proto __cdecl \
		widget: ptr GtkWidget,
	       visible: gboolean

;gboolean
gtk_widget_get_visible proto __cdecl \
		widget: ptr GtkWidget

;gboolean
gtk_widget_is_visible proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_has_window proto __cdecl \
		widget: ptr GtkWidget,
	    has_window: gboolean

;gboolean
gtk_widget_get_has_window proto __cdecl \
		widget: ptr GtkWidget


;gboolean
gtk_widget_is_toplevel proto __cdecl \
		widget: ptr GtkWidget

;gboolean
gtk_widget_is_drawable proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_realized proto __cdecl \
		widget: ptr GtkWidget,
	      realized: gboolean

;gboolean
gtk_widget_get_realized proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_mapped proto __cdecl \
		widget: ptr GtkWidget,
		mapped: gboolean

;gboolean
gtk_widget_get_mapped proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_app_paintable proto __cdecl \
		widget: ptr GtkWidget,
	 app_paintable: gboolean

;gboolean
gtk_widget_get_app_paintable proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_double_buffered proto __cdecl \
		widget: ptr GtkWidget,
       double_buffered: gboolean

;gboolean
gtk_widget_get_double_buffered proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_redraw_on_allocate proto __cdecl \
		widget: ptr GtkWidget,
    redraw_on_allocate: gboolean


;void
gtk_widget_set_parent proto __cdecl \
		widget: ptr GtkWidget,
		parent: ptr GtkWidget

;GtkWidget
gtk_widget_get_parent proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_parent_window proto __cdecl \
		widget: ptr GtkWidget,
	 parent_window: ptr GdkWindow

;GdkWindow
gtk_widget_get_parent_window proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_child_visible proto __cdecl \
		widget: ptr GtkWidget,
	    is_visible: gboolean

;gboolean
gtk_widget_get_child_visible proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_window proto __cdecl \
		widget: ptr GtkWidget,
		window: ptr GdkWindow

;GdkWindow
gtk_widget_get_window proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_register_window proto __cdecl \
		widget: ptr GtkWidget,
		window: ptr GdkWindow

;void
gtk_widget_unregister_window proto __cdecl \
		widget: ptr GtkWidget,
		window: ptr GdkWindow


;int
gtk_widget_get_allocated_width proto __cdecl \
		widget: ptr GtkWidget

;int
gtk_widget_get_allocated_height proto __cdecl \
		widget: ptr GtkWidget

;int
gtk_widget_get_allocated_baseline proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_get_allocation proto __cdecl \
		widget: ptr GtkWidget,
	    allocation: ptr GtkAllocation

;void
gtk_widget_set_allocation proto __cdecl \
		widget: ptr GtkWidget,
	    allocation: ptr GtkAllocation

;void
gtk_widget_set_clip proto __cdecl \
		widget: ptr GtkWidget,
		  clip: ptr GtkAllocation

;void
gtk_widget_get_clip proto __cdecl \
		widget: ptr GtkWidget,
		  clip: ptr GtkAllocation


;&
gtk_widget_get_requisition proto __cdecl \
		widget: ptr GtkWidget,
	   requisition: ptr GtkRequisition


;gboolean
gtk_widget_child_focus proto __cdecl \
		widget: ptr GtkWidget,
	     direction: GtkDirectionType

;gboolean
gtk_widget_keynav_failed proto __cdecl \
		widget: ptr GtkWidget,
	     direction: GtkDirectionType

;void
gtk_widget_error_bell proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_size_request proto __cdecl \
		widget: ptr GtkWidget,
		 width: gint,
		height: gint

;void
gtk_widget_get_size_request proto __cdecl \
		widget: ptr GtkWidget,
		 width: ptr gint,
		height: ptr gint

;void
gtk_widget_set_events proto __cdecl \
		widget: ptr GtkWidget,
		events: gint

;void
gtk_widget_add_events proto __cdecl \
		widget: ptr GtkWidget,
		events: gint

;void
gtk_widget_set_device_events proto __cdecl \
		widget: ptr GtkWidget,
		device: ptr GdkDevice,
		events: GdkEventMask

;void
gtk_widget_add_device_events proto __cdecl \
		widget: ptr GtkWidget,
		device: ptr GdkDevice,
		events: GdkEventMask

;void
gtk_widget_set_opacity proto __cdecl \
		widget: ptr GtkWidget,
	       opacity: double

;double
gtk_widget_get_opacity proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_device_enabled proto __cdecl \
		widget: ptr GtkWidget,
		device: ptr GdkDevice,
	       enabled: gboolean

;gboolean
gtk_widget_get_device_enabled proto __cdecl \
		widget: ptr GtkWidget,
		device: ptr GdkDevice


;GtkWidget*
gtk_widget_get_toplevel proto __cdecl \
		widget: ptr GtkWidget

;GtkWidget*
gtk_widget_get_ancestor proto __cdecl \
		widget: ptr GtkWidget,
	   widget_type: GType

;GdkVisual*
gtk_widget_get_visual proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_visual proto __cdecl \
		widget: ptr GtkWidget,
		visual: ptr GdkVisual


;GdkScreen
gtk_widget_get_screen proto __cdecl \
		widget: ptr GtkWidget

;gboolean
gtk_widget_has_screen proto __cdecl \
		widget: ptr GtkWidget

;gint
gtk_widget_get_scale_factor proto __cdecl \
		widget: ptr GtkWidget

;GdkDisplay
gtk_widget_get_display proto __cdecl \
		widget: ptr GtkWidget

;GdkWindow
gtk_widget_get_root_window proto __cdecl \
		widget: ptr GtkWidget

;GtkSettings*
gtk_widget_get_settings proto __cdecl \
		widget: ptr GtkWidget

;GtkClipboard
gtk_widget_get_clipboard proto __cdecl \
		widget: ptr GtkWidget,
	     selection: GdkAtom



;gboolean
gtk_widget_get_hexpand proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_hexpand proto __cdecl \
		widget: ptr GtkWidget,
		expand: gboolean

;gboolean
gtk_widget_get_hexpand_set proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_hexpand_set proto __cdecl \
		widget: ptr GtkWidget,
		   set: gboolean

;gboolean
gtk_widget_get_vexpand proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_vexpand proto __cdecl \
		widget: ptr GtkWidget,
		expand: gboolean

;gboolean
gtk_widget_get_vexpand_set proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_vexpand_set proto __cdecl \
		widget: ptr GtkWidget,
		   set: gboolean

;void
gtk_widget_queue_compute_expand proto __cdecl \
		widget: ptr GtkWidget

;gboolean
gtk_widget_compute_expand proto __cdecl \
		widget: ptr GtkWidget,
	   orientation: GtkOrientation



;gboolean
gtk_widget_get_support_multidevice proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_support_multidevice proto __cdecl \
		widget: ptr GtkWidget,
   support_multidevice: gboolean


;void
gtk_widget_class_set_accessible_type proto __cdecl \
	  widget_class: ptr GtkWidgetClass,
		  type: GType

;void
gtk_widget_class_set_accessible_role proto __cdecl \
	  widget_class: ptr GtkWidgetClass,
		  role: int_t;AtkRole

;AtkObject*
gtk_widget_get_accessible proto __cdecl \
		widget: ptr GtkWidget



;GtkAlign
gtk_widget_get_halign proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_halign proto __cdecl \
		widget: ptr GtkWidget,
		_align: GtkAlign

;GtkAlign
gtk_widget_get_valign proto __cdecl \
		widget: ptr GtkWidget

;GtkAlign
gtk_widget_get_valign_with_baseline proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_valign proto __cdecl \
		widget: ptr GtkWidget,
		_align: GtkAlign

;gint
gtk_widget_get_margin_left proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_margin_left proto __cdecl \
		widget: ptr GtkWidget,
		margin: gint

;gint
gtk_widget_get_margin_right proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_margin_right proto __cdecl \
		widget: ptr GtkWidget,
		margin: gint

;gint
gtk_widget_get_margin_start proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_margin_start proto __cdecl \
		widget: ptr GtkWidget,
		margin: gint

;gint
gtk_widget_get_margin_end proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_margin_end proto __cdecl \
		widget: ptr GtkWidget,
		margin: gint

;gint
gtk_widget_get_margin_top proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_margin_top proto __cdecl \
		widget: ptr GtkWidget,
		margin: gint

;gint
gtk_widget_get_margin_bottom proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_margin_bottom proto __cdecl \
		widget: ptr GtkWidget,
		margin: gint



;gint
gtk_widget_get_events proto __cdecl \
		widget: ptr GtkWidget

;GdkEventMask
gtk_widget_get_device_events proto __cdecl \
		widget: ptr GtkWidget,
		device: ptr GdkDevice

;void
gtk_widget_get_pointer proto __cdecl \
		widget: ptr GtkWidget,
		     x: ptr gint,
		     y: ptr gint


;gboolean
gtk_widget_is_ancestor proto __cdecl \
		widget: ptr GtkWidget,
	      ancestor: ptr GtkWidget


;gboolean
gtk_widget_translate_coordinates proto __cdecl \
	    src_widget: ptr GtkWidget,
	   dest_widget: ptr GtkWidget,
		 src_x: gint,
		 src_y: gint,
		dest_x: ptr gint,
		dest_y: ptr gint


;gboolean
gtk_widget_hide_on_delete proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_override_color proto __cdecl \
		widget: ptr GtkWidget,
		 state: GtkStateFlags,
		 color: ptr GdkRGBA

;void
gtk_widget_override_background_color proto __cdecl \
		widget: ptr GtkWidget,
		 state: GtkStateFlags,
		 color: ptr GdkRGBA


;void
gtk_widget_override_font proto __cdecl \
		widget: ptr GtkWidget,
	     font_desc: ptr PangoFontDescription


;void
gtk_widget_override_symbolic_color proto __cdecl \
		widget: ptr GtkWidget,
		  name: ptr gchar,
		 color: ptr GdkRGBA

;void
gtk_widget_override_cursor proto __cdecl \
		widget: ptr GtkWidget,
		cursor: ptr GdkRGBA,
      secondary_cursor: ptr GdkRGBA


;void
gtk_widget_reset_style proto __cdecl \
		widget: ptr GtkWidget


;PangoContext
gtk_widget_create_pango_context proto __cdecl \
		widget: ptr GtkWidget

;PangoContext
gtk_widget_get_pango_context proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_font_options proto __cdecl \
		widget: ptr GtkWidget,
	       options: ptr cairo_font_options_t

;const
gtk_widget_get_font_options proto __cdecl \
		widget: ptr GtkWidget

;PangoLayout
gtk_widget_create_pango_layout proto __cdecl \
		widget: ptr GtkWidget,
		  text: ptr gchar


;GdkPixbuf
gtk_widget_render_icon_pixbuf proto __cdecl \
		widget: ptr GtkWidget,
	      stock_id: ptr gchar,
		  size: GtkIconSize


;void
gtk_widget_set_composite_name proto __cdecl \
		widget: ptr GtkWidget,
		  name: ptr gchar

;gchar*
gtk_widget_get_composite_name proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_push_composite_child proto __cdecl
;void
gtk_widget_pop_composite_child proto __cdecl

;void
gtk_widget_class_install_style_property proto __cdecl \
		 klass: ptr GtkWidgetClass,
		 pspec: ptr GParamSpec

;void
gtk_widget_class_install_style_property_parser proto __cdecl \
		 klass: ptr GtkWidgetClass,
		 pspec: ptr GParamSpec,
		parser: GtkRcPropertyParser

;GParamSpec*
gtk_widget_class_find_style_property proto __cdecl \
		 klass: ptr GtkWidgetClass,
	 property_name: ptr gchar

;GParamSpec**
gtk_widget_class_list_style_properties proto __cdecl \
		 klass: ptr GtkWidgetClass,
	  n_properties: ptr guint

;void
gtk_widget_style_get_property proto __cdecl \
		widget: ptr GtkWidget,
	 property_name: ptr gchar,
		 value: ptr GValue

;void
gtk_widget_style_get_valist proto __cdecl \
		widget: ptr GtkWidget,
   first_property_name: ptr gchar,
	      var_args: va_list

;void
gtk_widget_style_get proto _CDecl \
		widget: ptr GtkWidget,
   first_property_name: ptr gchar,
		      : vararg



;void
gtk_widget_set_direction proto __cdecl \
		widget: ptr GtkWidget,
		   dir: GtkTextDirection

;GtkTextDirection
gtk_widget_get_direction proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_default_direction proto __cdecl \
		   dir: GtkTextDirection

;GtkTextDirection
gtk_widget_get_default_direction proto __cdecl

;gboolean
gtk_widget_is_composited proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_shape_combine_region proto __cdecl \
		widget: ptr GtkWidget,
		region: ptr cairo_region_t

;void
gtk_widget_input_shape_combine_region proto __cdecl \
		widget: ptr GtkWidget,
		region: ptr cairo_region_t


;GList*
gtk_widget_list_mnemonic_labels proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_add_mnemonic_label proto __cdecl \
		widget: ptr GtkWidget,
		_label: ptr GtkWidget

;void
gtk_widget_remove_mnemonic_label proto __cdecl \
		widget: ptr GtkWidget,
		_label: ptr GtkWidget


;void
gtk_widget_set_tooltip_window proto __cdecl \
		widget: ptr GtkWidget,
	 custom_window: ptr GtkWindow

;GtkWindow
gtk_widget_get_tooltip_window proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_trigger_tooltip_query proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_tooltip_text proto __cdecl \
		widget: ptr GtkWidget,
		  text: ptr gchar

;gchar
gtk_widget_get_tooltip_text proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_tooltip_markup proto __cdecl \
		widget: ptr GtkWidget,
		markup: ptr gchar

;gchar
gtk_widget_get_tooltip_markup proto __cdecl \
		widget: ptr GtkWidget

;void
gtk_widget_set_has_tooltip proto __cdecl \
		widget: ptr GtkWidget,
	   has_tooltip: gboolean

;gboolean
gtk_widget_get_has_tooltip proto __cdecl \
		widget: ptr GtkWidget


;gboolean
gtk_cairo_should_draw_window proto __cdecl \
		    cr: ptr cairo_t,
		window: ptr GdkWindow

;void
gtk_cairo_transform_to_window proto __cdecl \
		    cr: ptr cairo_t,
		widget: ptr GtkWidget,
		window: ptr GdkWindow


;GType
gtk_requisition_get_type proto __cdecl
;GtkRequisition
gtk_requisition_new proto __cdecl
;GtkRequisition
gtk_requisition_copy proto __cdecl \
	   requisition: ptr GtkRequisition

;void
gtk_requisition_free proto __cdecl \
	   requisition: ptr GtkRequisition


;gboolean
gtk_widget_in_destruction proto __cdecl \
		widget: ptr GtkWidget


;GtkStyleContext
gtk_widget_get_style_context proto __cdecl \
		widget: ptr GtkWidget


;GtkWidgetPath
gtk_widget_get_path proto __cdecl \
		widget: ptr GtkWidget


;GdkModifierType
gtk_widget_get_modifier_mask proto __cdecl \
		widget: ptr GtkWidget,
		intent: GdkModifierIntent


;void
gtk_widget_insert_action_group proto __cdecl \
		widget: ptr GtkWidget,
		  name: ptr gchar,
		_group: ptr GActionGroup




;guint
gtk_widget_add_tick_callback proto __cdecl \
		widget: ptr GtkWidget,
	      callback: GtkTickCallback,
	     user_data: gpointer,
		notify: GDestroyNotify


;void
gtk_widget_remove_tick_callback proto __cdecl \
		widget: ptr GtkWidget,
		    id: guint


gtk_widget_class_bind_template_callback macro widget_class, callback
	exitm<.err>
	endm
gtk_widget_class_bind_template_child macro widget_class, TypeName, member_name
	exitm<.err>
	endm
gtk_widget_class_bind_template_child_internal macro widget_class, TypeName, member_name
	exitm<.err>
	endm
gtk_widget_class_bind_template_child_private macro widget_class, TypeName, member_name
	exitm<.err>
	endm
gtk_widget_class_bind_template_child_internal_private macro widget_class, TypeName, member_name
	exitm<.err>
	endm

;void
gtk_widget_init_template proto __cdecl \
		widget: ptr GtkWidget

;GObject
gtk_widget_get_template_child proto __cdecl \
		widget: ptr GtkWidget,
	   widget_type: GType,
		  name: ptr gchar

;void
gtk_widget_class_set_template proto __cdecl \
	  widget_class: ptr GtkWidgetClass,
	template_bytes: ptr GBytes

;void
gtk_widget_class_set_template_from_resource proto __cdecl \
	  widget_class: ptr GtkWidgetClass,
	 resource_name: ptr gchar

;void
gtk_widget_class_bind_template_callback_full proto __cdecl \
	  widget_class: ptr GtkWidgetClass,
	 callback_name: ptr gchar,
       callback_symbol: GCallback

;void
gtk_widget_class_set_connect_func proto __cdecl \
	  widget_class: ptr GtkWidgetClass,
	  connect_func: GtkBuilderConnectFunc,
	  connect_data: gpointer,
  connect_data_destroy: GDestroyNotify

;void
gtk_widget_class_bind_template_child_full proto __cdecl \
	  widget_class: ptr GtkWidgetClass,
		  name: ptr gchar,
	internal_child: gboolean,
	 struct_offset: gssize


;GActionGroup
gtk_widget_get_action_group proto __cdecl \
		widget: ptr GtkWidget,
		prefix: ptr gchar


;const
gtk_widget_list_action_prefixes proto __cdecl \
		widget: ptr GtkWidget


;void
gtk_widget_set_font_map proto __cdecl \
		widget: ptr GtkWidget,
	      font_map: ptr PangoFontMap

;PangoFontMap
gtk_widget_get_font_map proto __cdecl \
		widget: ptr GtkWidget

endif
