ifndef __GTK_TYPE_BUILTINS_H__
__GTK_TYPE_BUILTINS_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib-object.inc
include gdk/gdk.inc

G_BEGIN_DECLS

;GType
gtk_license_get_type proto __cdecl
GTK_TYPE_LICENSE        equ <gtk_license_get_type>

;GType
gtk_accel_flags_get_type proto __cdecl
GTK_TYPE_ACCEL_FLAGS    equ <gtk_accel_flags_get_type>

;GType
gtk_application_inhibit_flags_get_type proto __cdecl
GTK_TYPE_APPLICATION_INHIBIT_FLAGS equ <gtk_application_inhibit_flags_get_type>

;GType
gtk_assistant_page_type_get_type proto __cdecl
GTK_TYPE_ASSISTANT_PAGE_TYPE equ <gtk_assistant_page_type_get_type>

;GType
gtk_button_box_style_get_type proto __cdecl
GTK_TYPE_BUTTON_BOX_STYLE equ <gtk_button_box_style_get_type>

;GType
gtk_builder_error_get_type proto __cdecl
GTK_TYPE_BUILDER_ERROR  equ <gtk_builder_error_get_type>

;GType
gtk_calendar_display_options_get_type proto __cdecl
GTK_TYPE_CALENDAR_DISPLAY_OPTIONS equ <gtk_calendar_display_options_get_type>

;GType
gtk_cell_renderer_state_get_type proto __cdecl
GTK_TYPE_CELL_RENDERER_STATE equ <gtk_cell_renderer_state_get_type>
;GType
gtk_cell_renderer_mode_get_type proto __cdecl
GTK_TYPE_CELL_RENDERER_MODE equ <gtk_cell_renderer_mode_get_type>

;GType
gtk_cell_renderer_accel_mode_get_type proto __cdecl
GTK_TYPE_CELL_RENDERER_ACCEL_MODE equ <gtk_cell_renderer_accel_mode_get_type>

;GType
gtk_resize_mode_get_type proto __cdecl
GTK_TYPE_RESIZE_MODE    equ <gtk_resize_mode_get_type>

;GType
gtk_css_provider_error_get_type proto __cdecl
GTK_TYPE_CSS_PROVIDER_ERROR equ <gtk_css_provider_error_get_type>

;GType
gtk_css_section_type_get_type proto __cdecl
GTK_TYPE_CSS_SECTION_TYPE equ <gtk_css_section_type_get_type>

;GType
gtk_debug_flag_get_type proto __cdecl
GTK_TYPE_DEBUG_FLAG     equ <gtk_debug_flag_get_type>

;GType
gtk_dialog_flags_get_type proto __cdecl
GTK_TYPE_DIALOG_FLAGS   equ <gtk_dialog_flags_get_type>
;GType
gtk_response_type_get_type proto __cdecl
GTK_TYPE_RESPONSE_TYPE  equ <gtk_response_type_get_type>

;GType
gtk_dest_defaults_get_type proto __cdecl
GTK_TYPE_DEST_DEFAULTS  equ <gtk_dest_defaults_get_type>
;GType
gtk_target_flags_get_type proto __cdecl
GTK_TYPE_TARGET_FLAGS   equ <gtk_target_flags_get_type>

;GType
gtk_entry_icon_position_get_type proto __cdecl
GTK_TYPE_ENTRY_ICON_POSITION equ <gtk_entry_icon_position_get_type>

;GType
gtk_align_get_type proto __cdecl
GTK_TYPE_ALIGN          equ <gtk_align_get_type>
;GType
gtk_arrow_type_get_type proto __cdecl
GTK_TYPE_ARROW_TYPE     equ <gtk_arrow_type_get_type>
;GType
gtk_baseline_position_get_type proto __cdecl
GTK_TYPE_BASELINE_POSITION equ <gtk_baseline_position_get_type>
;GType
gtk_delete_type_get_type proto __cdecl
GTK_TYPE_DELETE_TYPE    equ <gtk_delete_type_get_type>
;GType
gtk_direction_type_get_type proto __cdecl
GTK_TYPE_DIRECTION_TYPE equ <gtk_direction_type_get_type>
;GType
gtk_icon_size_get_type proto __cdecl
GTK_TYPE_ICON_SIZE      equ <gtk_icon_size_get_type>
;GType
gtk_sensitivity_type_get_type proto __cdecl
GTK_TYPE_SENSITIVITY_TYPE equ <gtk_sensitivity_type_get_type>
;GType
gtk_text_direction_get_type proto __cdecl
GTK_TYPE_TEXT_DIRECTION equ <gtk_text_direction_get_type>
;GType
gtk_justification_get_type proto __cdecl
GTK_TYPE_JUSTIFICATION  equ <gtk_justification_get_type>
;GType
gtk_menu_direction_type_get_type proto __cdecl
GTK_TYPE_MENU_DIRECTION_TYPE equ <gtk_menu_direction_type_get_type>
;GType
gtk_message_type_get_type proto __cdecl
GTK_TYPE_MESSAGE_TYPE   equ <gtk_message_type_get_type>
;GType
gtk_movement_step_get_type proto __cdecl
GTK_TYPE_MOVEMENT_STEP  equ <gtk_movement_step_get_type>
;GType
gtk_scroll_step_get_type proto __cdecl
GTK_TYPE_SCROLL_STEP    equ <gtk_scroll_step_get_type>
;GType
gtk_orientation_get_type proto __cdecl
GTK_TYPE_ORIENTATION    equ <gtk_orientation_get_type>
;GType
gtk_pack_type_get_type proto __cdecl
GTK_TYPE_PACK_TYPE      equ <gtk_pack_type_get_type>
;GType
gtk_position_type_get_type proto __cdecl
GTK_TYPE_POSITION_TYPE  equ <gtk_position_type_get_type>
;GType
gtk_relief_style_get_type proto __cdecl
GTK_TYPE_RELIEF_STYLE   equ <gtk_relief_style_get_type>
;GType
gtk_scroll_type_get_type proto __cdecl
GTK_TYPE_SCROLL_TYPE    equ <gtk_scroll_type_get_type>
;GType
gtk_selection_mode_get_type proto __cdecl
GTK_TYPE_SELECTION_MODE equ <gtk_selection_mode_get_type>
;GType
gtk_shadow_type_get_type proto __cdecl
GTK_TYPE_SHADOW_TYPE    equ <gtk_shadow_type_get_type>
;GType
gtk_state_type_get_type proto __cdecl
GTK_TYPE_STATE_TYPE     equ <gtk_state_type_get_type>
;GType
gtk_toolbar_style_get_type proto __cdecl
GTK_TYPE_TOOLBAR_STYLE  equ <gtk_toolbar_style_get_type>
;GType
gtk_wrap_mode_get_type proto __cdecl
GTK_TYPE_WRAP_MODE      equ <gtk_wrap_mode_get_type>
;GType
gtk_sort_type_get_type proto __cdecl
GTK_TYPE_SORT_TYPE      equ <gtk_sort_type_get_type>
;GType
gtk_im_preedit_style_get_type proto __cdecl
GTK_TYPE_IM_PREEDIT_STYLE equ <gtk_im_preedit_style_get_type>
;GType
gtk_im_status_style_get_type proto __cdecl
GTK_TYPE_IM_STATUS_STYLE equ <gtk_im_status_style_get_type>
;GType
gtk_pack_direction_get_type proto __cdecl
GTK_TYPE_PACK_DIRECTION equ <gtk_pack_direction_get_type>
;GType
gtk_print_pages_get_type proto __cdecl
GTK_TYPE_PRINT_PAGES    equ <gtk_print_pages_get_type>
;GType
gtk_page_set_get_type proto __cdecl
GTK_TYPE_PAGE_SET       equ <gtk_page_set_get_type>
;GType
gtk_number_up_layout_get_type proto __cdecl
GTK_TYPE_NUMBER_UP_LAYOUT equ <gtk_number_up_layout_get_type>
;GType
gtk_page_orientation_get_type proto __cdecl
GTK_TYPE_PAGE_ORIENTATION equ <gtk_page_orientation_get_type>
;GType
gtk_print_quality_get_type proto __cdecl
GTK_TYPE_PRINT_QUALITY  equ <gtk_print_quality_get_type>
;GType
gtk_print_duplex_get_type proto __cdecl
GTK_TYPE_PRINT_DUPLEX   equ <gtk_print_duplex_get_type>
;GType
gtk_unit_get_type proto __cdecl
GTK_TYPE_UNIT           equ <gtk_unit_get_type>
;GType
gtk_tree_view_grid_lines_get_type proto __cdecl
GTK_TYPE_TREE_VIEW_GRID_LINES equ <gtk_tree_view_grid_lines_get_type>
;GType
gtk_drag_result_get_type proto __cdecl
GTK_TYPE_DRAG_RESULT    equ <gtk_drag_result_get_type>
;GType
gtk_size_group_mode_get_type proto __cdecl
GTK_TYPE_SIZE_GROUP_MODE equ <gtk_size_group_mode_get_type>
;GType
gtk_size_request_mode_get_type proto __cdecl
GTK_TYPE_SIZE_REQUEST_MODE equ <gtk_size_request_mode_get_type>
;GType
gtk_scrollable_policy_get_type proto __cdecl
GTK_TYPE_SCROLLABLE_POLICY equ <gtk_scrollable_policy_get_type>
;GType
gtk_state_flags_get_type proto __cdecl
GTK_TYPE_STATE_FLAGS    equ <gtk_state_flags_get_type>
;GType
gtk_region_flags_get_type proto __cdecl
GTK_TYPE_REGION_FLAGS   equ <gtk_region_flags_get_type>
;GType
gtk_junction_sides_get_type proto __cdecl
GTK_TYPE_JUNCTION_SIDES equ <gtk_junction_sides_get_type>
;GType
gtk_border_style_get_type proto __cdecl
GTK_TYPE_BORDER_STYLE   equ <gtk_border_style_get_type>
;GType
gtk_level_bar_mode_get_type proto __cdecl
GTK_TYPE_LEVEL_BAR_MODE equ <gtk_level_bar_mode_get_type>
;GType
gtk_input_purpose_get_type proto __cdecl
GTK_TYPE_INPUT_PURPOSE  equ <gtk_input_purpose_get_type>
;GType
gtk_input_hints_get_type proto __cdecl
GTK_TYPE_INPUT_HINTS    equ <gtk_input_hints_get_type>
;GType
gtk_propagation_phase_get_type proto __cdecl
GTK_TYPE_PROPAGATION_PHASE equ <gtk_propagation_phase_get_type>
;GType
gtk_event_sequence_state_get_type proto __cdecl
GTK_TYPE_EVENT_SEQUENCE_STATE equ <gtk_event_sequence_state_get_type>
;GType
gtk_pan_direction_get_type proto __cdecl
GTK_TYPE_PAN_DIRECTION  equ <gtk_pan_direction_get_type>

;GType
gtk_file_chooser_action_get_type proto __cdecl
GTK_TYPE_FILE_CHOOSER_ACTION equ <gtk_file_chooser_action_get_type>
;GType
gtk_file_chooser_confirmation_get_type proto __cdecl
GTK_TYPE_FILE_CHOOSER_CONFIRMATION equ <gtk_file_chooser_confirmation_get_type>
;GType
gtk_file_chooser_error_get_type proto __cdecl
GTK_TYPE_FILE_CHOOSER_ERROR equ <gtk_file_chooser_error_get_type>

;GType
gtk_file_filter_flags_get_type proto __cdecl
GTK_TYPE_FILE_FILTER_FLAGS equ <gtk_file_filter_flags_get_type>

;GType
gtk_icon_lookup_flags_get_type proto __cdecl
GTK_TYPE_ICON_LOOKUP_FLAGS equ <gtk_icon_lookup_flags_get_type>
;GType
gtk_icon_theme_error_get_type proto __cdecl
GTK_TYPE_ICON_THEME_ERROR equ <gtk_icon_theme_error_get_type>

;GType
gtk_icon_view_drop_position_get_type proto __cdecl
GTK_TYPE_ICON_VIEW_DROP_POSITION equ <gtk_icon_view_drop_position_get_type>

;GType
gtk_image_type_get_type proto __cdecl
GTK_TYPE_IMAGE_TYPE     equ <gtk_image_type_get_type>

;GType
gtk_arrow_placement_get_type proto __cdecl
GTK_TYPE_ARROW_PLACEMENT equ <gtk_arrow_placement_get_type>

;GType
gtk_buttons_type_get_type proto __cdecl
GTK_TYPE_BUTTONS_TYPE   equ <gtk_buttons_type_get_type>

;GType
gtk_button_role_get_type proto __cdecl
GTK_TYPE_BUTTON_ROLE    equ <gtk_button_role_get_type>

;GType
gtk_notebook_tab_get_type proto __cdecl
GTK_TYPE_NOTEBOOK_TAB   equ <gtk_notebook_tab_get_type>

;GType
gtk_places_open_flags_get_type proto __cdecl
GTK_TYPE_PLACES_OPEN_FLAGS equ <gtk_places_open_flags_get_type>

;GType
gtk_print_status_get_type proto __cdecl
GTK_TYPE_PRINT_STATUS   equ <gtk_print_status_get_type>
;GType
gtk_print_operation_result_get_type proto __cdecl
GTK_TYPE_PRINT_OPERATION_RESULT equ <gtk_print_operation_result_get_type>
;GType
gtk_print_operation_action_get_type proto __cdecl
GTK_TYPE_PRINT_OPERATION_ACTION equ <gtk_print_operation_action_get_type>
;GType
gtk_print_error_get_type proto __cdecl
GTK_TYPE_PRINT_ERROR    equ <gtk_print_error_get_type>

;GType
gtk_recent_sort_type_get_type proto __cdecl
GTK_TYPE_RECENT_SORT_TYPE equ <gtk_recent_sort_type_get_type>
;GType
gtk_recent_chooser_error_get_type proto __cdecl
GTK_TYPE_RECENT_CHOOSER_ERROR equ <gtk_recent_chooser_error_get_type>

;GType
gtk_recent_filter_flags_get_type proto __cdecl
GTK_TYPE_RECENT_FILTER_FLAGS equ <gtk_recent_filter_flags_get_type>

;GType
gtk_recent_manager_error_get_type proto __cdecl
GTK_TYPE_RECENT_MANAGER_ERROR equ <gtk_recent_manager_error_get_type>

;GType
gtk_revealer_transition_type_get_type proto __cdecl
GTK_TYPE_REVEALER_TRANSITION_TYPE equ <gtk_revealer_transition_type_get_type>

;GType
gtk_corner_type_get_type proto __cdecl
GTK_TYPE_CORNER_TYPE    equ <gtk_corner_type_get_type>
;GType
gtk_policy_type_get_type proto __cdecl
GTK_TYPE_POLICY_TYPE    equ <gtk_policy_type_get_type>

;GType
gtk_spin_button_update_policy_get_type proto __cdecl
GTK_TYPE_SPIN_BUTTON_UPDATE_POLICY equ <gtk_spin_button_update_policy_get_type>
;GType
gtk_spin_type_get_type proto __cdecl
GTK_TYPE_SPIN_TYPE      equ <gtk_spin_type_get_type>

;GType
gtk_stack_transition_type_get_type proto __cdecl
GTK_TYPE_STACK_TRANSITION_TYPE equ <gtk_stack_transition_type_get_type>

;GType
gtk_text_buffer_target_info_get_type proto __cdecl
GTK_TYPE_TEXT_BUFFER_TARGET_INFO equ <gtk_text_buffer_target_info_get_type>

;GType
gtk_text_search_flags_get_type proto __cdecl
GTK_TYPE_TEXT_SEARCH_FLAGS equ <gtk_text_search_flags_get_type>

;GType
gtk_text_window_type_get_type proto __cdecl
GTK_TYPE_TEXT_WINDOW_TYPE equ <gtk_text_window_type_get_type>
;GType
gtk_text_view_layer_get_type proto __cdecl
GTK_TYPE_TEXT_VIEW_LAYER equ <gtk_text_view_layer_get_type>
;GType
gtk_text_extend_selection_get_type proto __cdecl
GTK_TYPE_TEXT_EXTEND_SELECTION equ <gtk_text_extend_selection_get_type>

;GType
gtk_toolbar_space_style_get_type proto __cdecl
GTK_TYPE_TOOLBAR_SPACE_STYLE equ <gtk_toolbar_space_style_get_type>

;GType
gtk_tool_palette_drag_targets_get_type proto __cdecl
GTK_TYPE_TOOL_PALETTE_DRAG_TARGETS equ <gtk_tool_palette_drag_targets_get_type>

;GType
gtk_tree_model_flags_get_type proto __cdecl
GTK_TYPE_TREE_MODEL_FLAGS equ <gtk_tree_model_flags_get_type>

;GType
gtk_tree_view_drop_position_get_type proto __cdecl
GTK_TYPE_TREE_VIEW_DROP_POSITION equ <gtk_tree_view_drop_position_get_type>

;GType
gtk_tree_view_column_sizing_get_type proto __cdecl
GTK_TYPE_TREE_VIEW_COLUMN_SIZING equ <gtk_tree_view_column_sizing_get_type>

;GType
gtk_widget_help_type_get_type proto __cdecl
GTK_TYPE_WIDGET_HELP_TYPE equ <gtk_widget_help_type_get_type>

;GType
gtk_window_type_get_type proto __cdecl
GTK_TYPE_WINDOW_TYPE    equ <gtk_window_type_get_type>
;GType
gtk_window_position_get_type proto __cdecl
GTK_TYPE_WINDOW_POSITION equ <gtk_window_position_get_type>

;GType
gtk_rc_flags_get_type proto __cdecl
GTK_TYPE_RC_FLAGS       equ <gtk_rc_flags_get_type>
;GType
gtk_rc_token_type_get_type proto __cdecl
GTK_TYPE_RC_TOKEN_TYPE  equ <gtk_rc_token_type_get_type>
;GType
gtk_path_priority_type_get_type proto __cdecl
GTK_TYPE_PATH_PRIORITY_TYPE equ <gtk_path_priority_type_get_type>
;GType
gtk_path_type_get_type proto __cdecl
GTK_TYPE_PATH_TYPE      equ <gtk_path_type_get_type>

;GType
gtk_expander_style_get_type proto __cdecl
GTK_TYPE_EXPANDER_STYLE equ <gtk_expander_style_get_type>

;GType
gtk_attach_options_get_type proto __cdecl
GTK_TYPE_ATTACH_OPTIONS equ <gtk_attach_options_get_type>

;GType
gtk_ui_manager_item_type_get_type proto __cdecl
GTK_TYPE_UI_MANAGER_ITEM_TYPE equ <gtk_ui_manager_item_type_get_type>
G_END_DECLS

endif


