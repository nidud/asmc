ifndef __GTK_WIDGET_H__
define __GTK_WIDGET_H__

if not defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
;include gsk/gsk.inc
include gtk/gtkaccelgroup.inc
include gtk/gtkborder.inc
include gtk/gtkshortcut.inc
include gtk/gtkshortcutaction.inc
include gtk/gtktypes.inc

define GTK_TYPE_WIDGET <gtk_widget_get_type ()>
GTK_WIDGET macro widget
  exitm<G_TYPE_CHECK_INSTANCE_CAST (widget, GTK_TYPE_WIDGET, GtkWidget)>
  endm
GTK_WIDGET_CLASS macro klass
  exitm<G_TYPE_CHECK_CLASS_CAST (klass, GTK_TYPE_WIDGET, GtkWidgetClass)>
  endm
GTK_IS_WIDGET macro widget
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((widget), GTK_TYPE_WIDGET))>
  endm
GTK_IS_WIDGET_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_WIDGET))>
  endm
GTK_WIDGET_GET_CLASS macro obj
  exitm<G_TYPE_INSTANCE_GET_CLASS (obj, GTK_TYPE_WIDGET, GtkWidgetClass)>
  endm

define GTK_TYPE_REQUISITION <gtk_requisition_get_type ()>

GtkAllocation		typedef GdkRectangle

CALLBACK(GtkTickCallback, :ptr, :ptr, :gpointer)

GtkRequisition		STRUC
width			sdword ?
height			sdword ?
GtkRequisition		ENDS

GtkWidget		STRUC
parent_instance		GInitiallyUnowned <>
priv			ptr GtkWidgetPrivate ?
GtkWidget		ENDS

GtkWidgetClass		struct
parent_class		GInitiallyUnownedClass <>
show			proc :ptr
hide			proc :ptr
map			proc :ptr
unmap			proc :ptr
realize			proc :ptr
unrealize		proc :ptr
root			proc :ptr
unroot			proc :ptr
size_allocate		proc :ptr, :sdword, :sdword, :sdword
state_flags_changed	proc :ptr, :GtkStateFlags
direction_changed	proc :ptr, :GtkTextDirection
get_request_mode	proc :ptr
measure			proc :ptr, :GtkOrientation, :sdword, :ptr, :ptr, :ptr, :ptr
mnemonic_activate	proc :ptr, :gboolean
grab_focus		proc :ptr
focus			proc :ptr, :GtkDirectionType
set_focus_child		proc :ptr, :ptr
move_focus		proc :ptr, :GtkDirectionType
keynav_failed		proc :ptr, :GtkDirectionType
query_tooltip		proc :ptr, :sdword, :sdword, :gboolean, :ptr
compute_expand		proc :ptr, :ptr, :ptr
css_changed		proc :ptr, :ptr
system_setting_changed	proc :ptr, :GtkSystemSetting
snapshot		proc :ptr, :ptr
contains		proc :ptr, :real8, :real8
priv			ptr GtkWidgetClassPrivate ?
padding			gpointer 8 dup(?)
GtkWidgetClass		ends


gtk_widget_get_type proto
gtk_widget_unparent proto :ptr
gtk_widget_show proto :ptr
gtk_widget_hide proto :ptr
gtk_widget_map proto :ptr
gtk_widget_unmap proto :ptr
gtk_widget_realize proto :ptr
gtk_widget_unrealize proto :ptr


gtk_widget_queue_draw proto :ptr
gtk_widget_queue_resize proto :ptr
gtk_widget_queue_allocate proto :ptr
gtk_widget_get_frame_clock proto :ptr

gtk_widget_size_allocate proto :ptr, :ptr, :sdword
gtk_widget_allocate proto :ptr, :sdword, :sdword, :sdword, :ptr

gtk_widget_get_request_mode proto :ptr
gtk_widget_measure proto :ptr, :GtkOrientation, :sdword, :ptr, :ptr, :ptr, :ptr
gtk_widget_get_preferred_size proto :ptr, :ptr, :ptr

gtk_widget_set_layout_manager proto :ptr, :ptr
gtk_widget_get_layout_manager proto :ptr

gtk_widget_class_set_layout_manager_type proto :ptr, :GType
gtk_widget_class_get_layout_manager_type proto :ptr

gtk_widget_class_add_binding proto :ptr, :guint, :GdkModifierType, :GtkShortcutFunc, :ptr, :vararg
gtk_widget_class_add_binding_signal proto :ptr, :guint, :GdkModifierType, :ptr, :ptr, :vararg
gtk_widget_class_add_binding_action proto :ptr, :guint, :GdkModifierType, :ptr, :ptr, :vararg
gtk_widget_class_add_shortcut proto :ptr, :ptr

gtk_widget_class_set_activate_signal proto :ptr, :guint
gtk_widget_class_set_activate_signal_from_name proto :ptr, :ptr
gtk_widget_class_get_activate_signal proto :ptr

gtk_widget_mnemonic_activate proto :ptr, :gboolean
gtk_widget_activate proto :ptr

gtk_widget_set_can_focus proto :ptr, :gboolean
gtk_widget_get_can_focus proto :ptr
gtk_widget_set_focusable proto :ptr, :gboolean
gtk_widget_get_focusable proto :ptr
gtk_widget_has_focus proto :ptr
gtk_widget_is_focus proto :ptr
gtk_widget_has_visible_focus proto :ptr
gtk_widget_grab_focus proto :ptr
gtk_widget_set_focus_on_click proto :ptr, :gboolean
gtk_widget_get_focus_on_click proto :ptr

gtk_widget_set_can_target proto :ptr, :gboolean
gtk_widget_get_can_target proto :ptr

gtk_widget_has_default proto :ptr

gtk_widget_set_receives_default proto :ptr, :gboolean
gtk_widget_get_receives_default proto :ptr


gtk_widget_set_name proto :ptr, :ptr
gtk_widget_get_name proto :ptr


gtk_widget_set_state_flags proto :ptr, :GtkStateFlags, :gboolean
gtk_widget_unset_state_flags proto :ptr, :GtkStateFlags
gtk_widget_get_state_flags proto :ptr

gtk_widget_set_sensitive proto :ptr, :gboolean
gtk_widget_get_sensitive proto :ptr
gtk_widget_is_sensitive proto :ptr

gtk_widget_set_visible proto :ptr, :gboolean
gtk_widget_get_visible proto :ptr
gtk_widget_is_visible proto :ptr

gtk_widget_is_drawable proto :ptr
gtk_widget_get_realized proto :ptr
gtk_widget_get_mapped proto :ptr

gtk_widget_set_parent proto :ptr, :ptr
gtk_widget_get_parent proto :ptr

gtk_widget_get_root proto :ptr

gtk_widget_get_native proto :ptr

gtk_widget_set_child_visible proto :ptr, :gboolean
gtk_widget_get_child_visible proto :ptr

gtk_widget_get_allocated_width proto :ptr
gtk_widget_get_allocated_height proto :ptr
gtk_widget_get_allocated_baseline proto :ptr

gtk_widget_get_allocation proto :ptr, :ptr
gtk_widget_compute_transform proto :ptr, :ptr, :ptr
gtk_widget_compute_bounds proto :ptr, :ptr, :ptr
gtk_widget_compute_point proto :ptr, :ptr, :ptr, :ptr

gtk_widget_get_width proto :ptr
gtk_widget_get_height proto :ptr
gtk_widget_get_size proto :ptr, :GtkOrientation

gtk_widget_child_focus proto :ptr, :GtkDirectionType
gtk_widget_keynav_failed proto :ptr, :GtkDirectionType
gtk_widget_error_bell proto :ptr

gtk_widget_set_size_request proto :ptr, :sdword, :sdword
gtk_widget_get_size_request proto :ptr, :ptr, :ptr
gtk_widget_set_opacity proto :ptr, :real8
gtk_widget_get_opacity proto :ptr
gtk_widget_set_overflow proto :ptr, :GtkOverflow
gtk_widget_get_overflow proto :ptr

gtk_widget_get_ancestor proto :ptr, :GType

gtk_widget_get_scale_factor proto :ptr
gtk_widget_get_display proto :ptr
gtk_widget_get_settings proto :ptr
gtk_widget_get_clipboard proto :ptr
gtk_widget_get_primary_clipboard proto :ptr

gtk_widget_get_hexpand proto :ptr
gtk_widget_set_hexpand proto :ptr, :gboolean
gtk_widget_get_hexpand_set proto :ptr
gtk_widget_set_hexpand_set proto :ptr, :gboolean
gtk_widget_get_vexpand proto :ptr
gtk_widget_set_vexpand proto :ptr, :gboolean
gtk_widget_get_vexpand_set proto :ptr
gtk_widget_set_vexpand_set proto :ptr, :gboolean
gtk_widget_compute_expand proto :ptr, :GtkOrientation

gtk_widget_get_halign proto :ptr
gtk_widget_set_halign proto :ptr, :GtkAlign
gtk_widget_get_valign proto :ptr
gtk_widget_set_valign proto :ptr, :GtkAlign
gtk_widget_get_margin_start proto :ptr
gtk_widget_set_margin_start proto :ptr, :sdword
gtk_widget_get_margin_end proto :ptr
gtk_widget_set_margin_end proto :ptr, :sdword
gtk_widget_get_margin_top proto :ptr
gtk_widget_set_margin_top proto :ptr, :sdword
gtk_widget_get_margin_bottom proto :ptr
gtk_widget_set_margin_bottom proto :ptr, :sdword

gtk_widget_is_ancestor proto :ptr, :ptr

gtk_widget_translate_coordinates proto :ptr, :ptr, :real8, :real8, :ptr, :ptr

gtk_widget_contains proto :ptr, :real8, :real8
gtk_widget_pick proto :ptr, :real8, :real8, :GtkPickFlags

gtk_widget_add_controller proto :ptr, :ptr
gtk_widget_remove_controller proto :ptr, :ptr

gtk_widget_create_pango_context proto :ptr
gtk_widget_get_pango_context proto :ptr
gtk_widget_set_font_options proto :ptr, :ptr
gtk_widget_get_font_options proto :ptr
gtk_widget_create_pango_layout proto :ptr, :ptr

gtk_widget_set_direction proto :ptr, :GtkTextDirection
gtk_widget_get_direction proto :ptr

gtk_widget_set_default_direction proto :GtkTextDirection
gtk_widget_get_default_direction proto

gtk_widget_set_cursor proto :ptr, :ptr
gtk_widget_set_cursor_from_name proto :ptr, :ptr
gtk_widget_get_cursor proto :ptr

gtk_widget_list_mnemonic_labels proto :ptr
gtk_widget_add_mnemonic_label proto :ptr, :ptr
gtk_widget_remove_mnemonic_label proto :ptr, :ptr

gtk_widget_trigger_tooltip_query proto :ptr
gtk_widget_set_tooltip_text proto :ptr, :ptr
gtk_widget_get_tooltip_text proto :ptr
gtk_widget_set_tooltip_markup proto :ptr, :ptr
gtk_widget_get_tooltip_markup proto :ptr
gtk_widget_set_has_tooltip proto :ptr, :gboolean
gtk_widget_get_has_tooltip proto :ptr

gtk_requisition_get_type proto
gtk_requisition_new proto
gtk_requisition_copy proto :ptr
gtk_requisition_free proto :ptr

gtk_widget_in_destruction proto :ptr

gtk_widget_get_style_context proto :ptr

gtk_widget_class_set_css_name proto :ptr, :ptr
gtk_widget_class_get_css_name proto :ptr

gtk_widget_add_tick_callback proto :ptr, :GtkTickCallback, :gpointer, :GDestroyNotify

gtk_widget_remove_tick_callback proto :ptr, :guint

gtk_widget_class_bind_template_child macro widget_class, TypeName, member_name
  exitm<gtk_widget_class_bind_template_child_full(widget_class, @CatStr(<!">, member_name, <!">), FALSE, TypeName.member_name)>
  endm

gtk_widget_init_template proto :ptr
gtk_widget_get_template_child proto :ptr, :GType, :ptr
gtk_widget_class_set_template proto :ptr, :ptr
gtk_widget_class_set_template_from_resource proto :ptr, :ptr
gtk_widget_class_bind_template_callback_full proto :ptr, :ptr, :GCallback
gtk_widget_class_set_template_scope proto :ptr, :ptr
gtk_widget_class_bind_template_child_full proto :ptr, :ptr, :gboolean, :gssize

gtk_widget_insert_action_group proto :ptr, :ptr, :ptr

gtk_widget_activate_action proto :ptr, :ptr, :ptr, :vararg
gtk_widget_activate_action_variant proto :ptr, :ptr, :ptr

gtk_widget_activate_default proto :ptr

gtk_widget_set_font_map proto :ptr, :ptr
gtk_widget_get_font_map proto :ptr

gtk_widget_get_first_child proto :ptr
gtk_widget_get_last_child proto :ptr
gtk_widget_get_next_sibling proto :ptr
gtk_widget_get_prev_sibling proto :ptr
gtk_widget_observe_children proto :ptr
gtk_widget_observe_controllers proto :ptr
gtk_widget_insert_after proto :ptr, :ptr, :ptr
gtk_widget_insert_before proto :ptr, :ptr, :ptr
gtk_widget_set_focus_child proto :ptr, :ptr
gtk_widget_get_focus_child proto :ptr

gtk_widget_snapshot_child proto :ptr, :ptr, :ptr
gtk_widget_should_layout proto :ptr
gtk_widget_get_css_name proto :ptr
gtk_widget_add_css_class proto :ptr, :ptr
gtk_widget_remove_css_class proto :ptr, :ptr
gtk_widget_has_css_class proto :ptr, :ptr
gtk_widget_get_css_classes proto :ptr
gtk_widget_set_css_classes proto :ptr, :ptr

CALLBACK(GtkWidgetActionActivateFunc, :ptr, :ptr, :ptr)

gtk_widget_class_install_action proto :ptr, :ptr, :ptr, :GtkWidgetActionActivateFunc
gtk_widget_class_install_property_action proto :ptr, :ptr, :ptr
gtk_widget_class_query_action proto :ptr, :guint, :ptr, :ptr, :ptr, :ptr
gtk_widget_action_set_enabled proto :ptr, :ptr, :gboolean

gtk_widget_class_set_accessible_role proto :ptr, :GtkAccessibleRole
gtk_widget_class_get_accessible_role proto :ptr

endif
