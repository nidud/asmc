ifndef __GTK_TYPE_BUILTINS_H__
define __GTK_TYPE_BUILTINS_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib-object.inc
include gdk/gdk.inc

gtk_license_get_type proto
define GTK_TYPE_LICENSE <gtk_license_get_type ()>

gtk_application_inhibit_flags_get_type proto
define GTK_TYPE_APPLICATION_INHIBIT_FLAGS <gtk_application_inhibit_flags_get_type ()>

gtk_assistant_page_type_get_type proto
define GTK_TYPE_ASSISTANT_PAGE_TYPE <gtk_assistant_page_type_get_type ()>

gtk_builder_error_get_type proto
define GTK_TYPE_BUILDER_ERROR <gtk_builder_error_get_type ()>

gtk_builder_closure_flags_get_type proto
define GTK_TYPE_BUILDER_CLOSURE_FLAGS <gtk_builder_closure_flags_get_type ()>

gtk_cell_renderer_state_get_type proto
define GTK_TYPE_CELL_RENDERER_STATE <gtk_cell_renderer_state_get_type ()>
gtk_cell_renderer_mode_get_type proto
define GTK_TYPE_CELL_RENDERER_MODE <gtk_cell_renderer_mode_get_type ()>

gtk_cell_renderer_accel_mode_get_type proto
define GTK_TYPE_CELL_RENDERER_ACCEL_MODE <gtk_cell_renderer_accel_mode_get_type ()>

gtk_debug_flags_get_type proto
define GTK_TYPE_DEBUG_FLAGS <gtk_debug_flags_get_type ()>

gtk_dialog_flags_get_type proto
define GTK_TYPE_DIALOG_FLAGS <gtk_dialog_flags_get_type ()>
gtk_response_type_get_type proto
define GTK_TYPE_RESPONSE_TYPE <gtk_response_type_get_type ()>

gtk_editable_properties_get_type proto
define GTK_TYPE_EDITABLE_PROPERTIES <gtk_editable_properties_get_type ()>

gtk_entry_icon_position_get_type proto
define GTK_TYPE_ENTRY_ICON_POSITION <gtk_entry_icon_position_get_type ()>

gtk_align_get_type proto
define GTK_TYPE_ALIGN <gtk_align_get_type ()>
gtk_arrow_type_get_type proto
define GTK_TYPE_ARROW_TYPE <gtk_arrow_type_get_type ()>
gtk_baseline_position_get_type proto
define GTK_TYPE_BASELINE_POSITION <gtk_baseline_position_get_type ()>
gtk_delete_type_get_type proto
define GTK_TYPE_DELETE_TYPE <gtk_delete_type_get_type ()>
gtk_direction_type_get_type proto
define GTK_TYPE_DIRECTION_TYPE <gtk_direction_type_get_type ()>
gtk_icon_size_get_type proto
define GTK_TYPE_ICON_SIZE <gtk_icon_size_get_type ()>
gtk_sensitivity_type_get_type proto
define GTK_TYPE_SENSITIVITY_TYPE <gtk_sensitivity_type_get_type ()>
gtk_text_direction_get_type proto
define GTK_TYPE_TEXT_DIRECTION <gtk_text_direction_get_type ()>
gtk_justification_get_type proto
define GTK_TYPE_JUSTIFICATION <gtk_justification_get_type ()>
gtk_message_type_get_type proto
define GTK_TYPE_MESSAGE_TYPE <gtk_message_type_get_type ()>
gtk_movement_step_get_type proto
define GTK_TYPE_MOVEMENT_STEP <gtk_movement_step_get_type ()>
gtk_natural_wrap_mode_get_type proto
define GTK_TYPE_NATURAL_WRAP_MODE <gtk_natural_wrap_mode_get_type ()>
gtk_scroll_step_get_type proto
define GTK_TYPE_SCROLL_STEP <gtk_scroll_step_get_type ()>
gtk_orientation_get_type proto
define GTK_TYPE_ORIENTATION <gtk_orientation_get_type ()>
gtk_overflow_get_type proto
define GTK_TYPE_OVERFLOW <gtk_overflow_get_type ()>
gtk_pack_type_get_type proto
define GTK_TYPE_PACK_TYPE <gtk_pack_type_get_type ()>
gtk_position_type_get_type proto
define GTK_TYPE_POSITION_TYPE <gtk_position_type_get_type ()>
gtk_scroll_type_get_type proto
define GTK_TYPE_SCROLL_TYPE <gtk_scroll_type_get_type ()>
gtk_selection_mode_get_type proto
define GTK_TYPE_SELECTION_MODE <gtk_selection_mode_get_type ()>
gtk_wrap_mode_get_type proto
define GTK_TYPE_WRAP_MODE <gtk_wrap_mode_get_type ()>
gtk_sort_type_get_type proto
define GTK_TYPE_SORT_TYPE <gtk_sort_type_get_type ()>
gtk_print_pages_get_type proto
define GTK_TYPE_PRINT_PAGES <gtk_print_pages_get_type ()>
gtk_page_set_get_type proto
define GTK_TYPE_PAGE_SET <gtk_page_set_get_type ()>
gtk_number_up_layout_get_type proto
define GTK_TYPE_NUMBER_UP_LAYOUT <gtk_number_up_layout_get_type ()>
gtk_ordering_get_type proto
define GTK_TYPE_ORDERING <gtk_ordering_get_type ()>
gtk_page_orientation_get_type proto
define GTK_TYPE_PAGE_ORIENTATION <gtk_page_orientation_get_type ()>
gtk_print_quality_get_type proto
define GTK_TYPE_PRINT_QUALITY <gtk_print_quality_get_type ()>
gtk_print_duplex_get_type proto
define GTK_TYPE_PRINT_DUPLEX <gtk_print_duplex_get_type ()>
gtk_unit_get_type proto
define GTK_TYPE_UNIT <gtk_unit_get_type ()>
gtk_tree_view_grid_lines_get_type proto
define GTK_TYPE_TREE_VIEW_GRID_LINES <gtk_tree_view_grid_lines_get_type ()>
gtk_size_group_mode_get_type proto
define GTK_TYPE_SIZE_GROUP_MODE <gtk_size_group_mode_get_type ()>
gtk_size_request_mode_get_type proto
define GTK_TYPE_SIZE_REQUEST_MODE <gtk_size_request_mode_get_type ()>
gtk_scrollable_policy_get_type proto
define GTK_TYPE_SCROLLABLE_POLICY <gtk_scrollable_policy_get_type ()>
gtk_state_flags_get_type proto
define GTK_TYPE_STATE_FLAGS <gtk_state_flags_get_type ()>
gtk_border_style_get_type proto
define GTK_TYPE_BORDER_STYLE <gtk_border_style_get_type ()>
gtk_level_bar_mode_get_type proto
define GTK_TYPE_LEVEL_BAR_MODE <gtk_level_bar_mode_get_type ()>
gtk_input_purpose_get_type proto
define GTK_TYPE_INPUT_PURPOSE <gtk_input_purpose_get_type ()>
gtk_input_hints_get_type proto
define GTK_TYPE_INPUT_HINTS <gtk_input_hints_get_type ()>
gtk_propagation_phase_get_type proto
define GTK_TYPE_PROPAGATION_PHASE <gtk_propagation_phase_get_type ()>
gtk_propagation_limit_get_type proto
define GTK_TYPE_PROPAGATION_LIMIT <gtk_propagation_limit_get_type ()>
gtk_event_sequence_state_get_type proto
define GTK_TYPE_EVENT_SEQUENCE_STATE <gtk_event_sequence_state_get_type ()>
gtk_pan_direction_get_type proto
define GTK_TYPE_PAN_DIRECTION <gtk_pan_direction_get_type ()>
gtk_shortcut_scope_get_type proto
define GTK_TYPE_SHORTCUT_SCOPE <gtk_shortcut_scope_get_type ()>
gtk_pick_flags_get_type proto
define GTK_TYPE_PICK_FLAGS <gtk_pick_flags_get_type ()>
gtk_constraint_relation_get_type proto
define GTK_TYPE_CONSTRAINT_RELATION <gtk_constraint_relation_get_type ()>
gtk_constraint_strength_get_type proto
define GTK_TYPE_CONSTRAINT_STRENGTH <gtk_constraint_strength_get_type ()>
gtk_constraint_attribute_get_type proto
define GTK_TYPE_CONSTRAINT_ATTRIBUTE <gtk_constraint_attribute_get_type ()>
gtk_constraint_vfl_parser_error_get_type proto
define GTK_TYPE_CONSTRAINT_VFL_PARSER_ERROR <gtk_constraint_vfl_parser_error_get_type ()>
gtk_system_setting_get_type proto
define GTK_TYPE_SYSTEM_SETTING <gtk_system_setting_get_type ()>
gtk_symbolic_color_get_type proto
define GTK_TYPE_SYMBOLIC_COLOR <gtk_symbolic_color_get_type ()>
gtk_accessible_role_get_type proto
define GTK_TYPE_ACCESSIBLE_ROLE <gtk_accessible_role_get_type ()>
gtk_accessible_state_get_type proto
define GTK_TYPE_ACCESSIBLE_STATE <gtk_accessible_state_get_type ()>
gtk_accessible_property_get_type proto
define GTK_TYPE_ACCESSIBLE_PROPERTY <gtk_accessible_property_get_type ()>
gtk_accessible_relation_get_type proto
define GTK_TYPE_ACCESSIBLE_RELATION <gtk_accessible_relation_get_type ()>
gtk_accessible_tristate_get_type proto
define GTK_TYPE_ACCESSIBLE_TRISTATE <gtk_accessible_tristate_get_type ()>
gtk_accessible_invalid_state_get_type proto
define GTK_TYPE_ACCESSIBLE_INVALID_STATE <gtk_accessible_invalid_state_get_type ()>
gtk_accessible_autocomplete_get_type proto
define GTK_TYPE_ACCESSIBLE_AUTOCOMPLETE <gtk_accessible_autocomplete_get_type ()>
gtk_accessible_sort_get_type proto
define GTK_TYPE_ACCESSIBLE_SORT <gtk_accessible_sort_get_type ()>

gtk_event_controller_scroll_flags_get_type proto
define GTK_TYPE_EVENT_CONTROLLER_SCROLL_FLAGS <gtk_event_controller_scroll_flags_get_type ()>

gtk_file_chooser_action_get_type proto
define GTK_TYPE_FILE_CHOOSER_ACTION <gtk_file_chooser_action_get_type ()>
gtk_file_chooser_error_get_type proto
define GTK_TYPE_FILE_CHOOSER_ERROR <gtk_file_chooser_error_get_type ()>

gtk_filter_match_get_type proto
define GTK_TYPE_FILTER_MATCH <gtk_filter_match_get_type ()>
gtk_filter_change_get_type proto
define GTK_TYPE_FILTER_CHANGE <gtk_filter_change_get_type ()>

gtk_font_chooser_level_get_type proto
define GTK_TYPE_FONT_CHOOSER_LEVEL <gtk_font_chooser_level_get_type ()>

gtk_icon_lookup_flags_get_type proto
define GTK_TYPE_ICON_LOOKUP_FLAGS <gtk_icon_lookup_flags_get_type ()>
gtk_icon_theme_error_get_type proto
define GTK_TYPE_ICON_THEME_ERROR <gtk_icon_theme_error_get_type ()>

gtk_icon_view_drop_position_get_type proto
define GTK_TYPE_ICON_VIEW_DROP_POSITION <gtk_icon_view_drop_position_get_type ()>

gtk_image_type_get_type proto
define GTK_TYPE_IMAGE_TYPE <gtk_image_type_get_type ()>

gtk_buttons_type_get_type proto
define GTK_TYPE_BUTTONS_TYPE <gtk_buttons_type_get_type ()>

gtk_notebook_tab_get_type proto
define GTK_TYPE_NOTEBOOK_TAB <gtk_notebook_tab_get_type ()>

gtk_pad_action_type_get_type proto
define GTK_TYPE_PAD_ACTION_TYPE <gtk_pad_action_type_get_type ()>

gtk_popover_menu_flags_get_type proto
define GTK_TYPE_POPOVER_MENU_FLAGS <gtk_popover_menu_flags_get_type ()>

gtk_print_status_get_type proto
define GTK_TYPE_PRINT_STATUS <gtk_print_status_get_type ()>
gtk_print_operation_result_get_type proto
define GTK_TYPE_PRINT_OPERATION_RESULT <gtk_print_operation_result_get_type ()>
gtk_print_operation_action_get_type proto
define GTK_TYPE_PRINT_OPERATION_ACTION <gtk_print_operation_action_get_type ()>
gtk_print_error_get_type proto
define GTK_TYPE_PRINT_ERROR <gtk_print_error_get_type ()>

gtk_recent_manager_error_get_type proto
define GTK_TYPE_RECENT_MANAGER_ERROR <gtk_recent_manager_error_get_type ()>

gtk_revealer_transition_type_get_type proto
define GTK_TYPE_REVEALER_TRANSITION_TYPE <gtk_revealer_transition_type_get_type ()>

gtk_corner_type_get_type proto
define GTK_TYPE_CORNER_TYPE <gtk_corner_type_get_type ()>
gtk_policy_type_get_type proto
define GTK_TYPE_POLICY_TYPE <gtk_policy_type_get_type ()>

gtk_shortcut_action_flags_get_type proto
define GTK_TYPE_SHORTCUT_ACTION_FLAGS <gtk_shortcut_action_flags_get_type ()>

gtk_shortcut_type_get_type proto
define GTK_TYPE_SHORTCUT_TYPE <gtk_shortcut_type_get_type ()>

gtk_sorter_order_get_type proto
define GTK_TYPE_SORTER_ORDER <gtk_sorter_order_get_type ()>
gtk_sorter_change_get_type proto
define GTK_TYPE_SORTER_CHANGE <gtk_sorter_change_get_type ()>

gtk_spin_button_update_policy_get_type proto
define GTK_TYPE_SPIN_BUTTON_UPDATE_POLICY <gtk_spin_button_update_policy_get_type ()>
gtk_spin_type_get_type proto
define GTK_TYPE_SPIN_TYPE <gtk_spin_type_get_type ()>

gtk_stack_transition_type_get_type proto
define GTK_TYPE_STACK_TRANSITION_TYPE <gtk_stack_transition_type_get_type ()>

gtk_string_filter_match_mode_get_type proto
define GTK_TYPE_STRING_FILTER_MATCH_MODE <gtk_string_filter_match_mode_get_type ()>

gtk_style_context_print_flags_get_type proto
define GTK_TYPE_STYLE_CONTEXT_PRINT_FLAGS <gtk_style_context_print_flags_get_type ()>

gtk_text_search_flags_get_type proto
define GTK_TYPE_TEXT_SEARCH_FLAGS <gtk_text_search_flags_get_type ()>

gtk_text_window_type_get_type proto
define GTK_TYPE_TEXT_WINDOW_TYPE <gtk_text_window_type_get_type ()>
gtk_text_view_layer_get_type proto
define GTK_TYPE_TEXT_VIEW_LAYER <gtk_text_view_layer_get_type ()>
gtk_text_extend_selection_get_type proto
define GTK_TYPE_TEXT_EXTEND_SELECTION <gtk_text_extend_selection_get_type ()>

gtk_tree_model_flags_get_type proto
define GTK_TYPE_TREE_MODEL_FLAGS <gtk_tree_model_flags_get_type ()>

gtk_tree_view_drop_position_get_type proto
define GTK_TYPE_TREE_VIEW_DROP_POSITION <gtk_tree_view_drop_position_get_type ()>

gtk_tree_view_column_sizing_get_type proto
define GTK_TYPE_TREE_VIEW_COLUMN_SIZING <gtk_tree_view_column_sizing_get_type ()>

endif



