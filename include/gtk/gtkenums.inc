ifndef __GTK_ENUMS_H__
__GTK_ENUMS_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib-object.inc

.enum GtkAlign {
  GTK_ALIGN_FILL,
  GTK_ALIGN_START,
  GTK_ALIGN_END,
  GTK_ALIGN_CENTER,
  GTK_ALIGN_BASELINE
}

.enum GtkArrowType {
  GTK_ARROW_UP,
  GTK_ARROW_DOWN,
  GTK_ARROW_LEFT,
  GTK_ARROW_RIGHT,
  GTK_ARROW_NONE
}

.enum GtkBaselinePosition {
  GTK_BASELINE_POSITION_TOP,
  GTK_BASELINE_POSITION_CENTER,
  GTK_BASELINE_POSITION_BOTTOM
}

.enum GtkDeleteType {
  GTK_DELETE_CHARS,
  GTK_DELETE_WORD_ENDS,
  GTK_DELETE_WORDS,
  GTK_DELETE_DISPLAY_LINES,
  GTK_DELETE_DISPLAY_LINE_ENDS,
  GTK_DELETE_PARAGRAPH_ENDS,
  GTK_DELETE_PARAGRAPHS,
  GTK_DELETE_WHITESPACE
}

.enum GtkDirectionType {
  GTK_DIR_TAB_FORWARD,
  GTK_DIR_TAB_BACKWARD,
  GTK_DIR_UP,
  GTK_DIR_DOWN,
  GTK_DIR_LEFT,
  GTK_DIR_RIGHT
}


.enum GtkIconSize {
  GTK_ICON_SIZE_INVALID,
  GTK_ICON_SIZE_MENU,
  GTK_ICON_SIZE_SMALL_TOOLBAR,
  GTK_ICON_SIZE_LARGE_TOOLBAR,
  GTK_ICON_SIZE_BUTTON,
  GTK_ICON_SIZE_DND,
  GTK_ICON_SIZE_DIALOG
}

.enum GtkSensitivityType {
  GTK_SENSITIVITY_AUTO,
  GTK_SENSITIVITY_ON,
  GTK_SENSITIVITY_OFF
}

.enum GtkTextDirection {
  GTK_TEXT_DIR_NONE,
  GTK_TEXT_DIR_LTR,
  GTK_TEXT_DIR_RTL
}

.enum GtkJustification {
  GTK_JUSTIFY_LEFT,
  GTK_JUSTIFY_RIGHT,
  GTK_JUSTIFY_CENTER,
  GTK_JUSTIFY_FILL
}

.enum GtkMenuDirectionType {
  GTK_MENU_DIR_PARENT,
  GTK_MENU_DIR_CHILD,
  GTK_MENU_DIR_NEXT,
  GTK_MENU_DIR_PREV
}

.enum GtkMessageType {
  GTK_MESSAGE_INFO,
  GTK_MESSAGE_WARNING,
  GTK_MESSAGE_QUESTION,
  GTK_MESSAGE_ERROR,
  GTK_MESSAGE_OTHER
}

.enum GtkMovementStep {
  GTK_MOVEMENT_LOGICAL_POSITIONS,
  GTK_MOVEMENT_VISUAL_POSITIONS,
  GTK_MOVEMENT_WORDS,
  GTK_MOVEMENT_DISPLAY_LINES,
  GTK_MOVEMENT_DISPLAY_LINE_ENDS,
  GTK_MOVEMENT_PARAGRAPHS,
  GTK_MOVEMENT_PARAGRAPH_ENDS,
  GTK_MOVEMENT_PAGES,
  GTK_MOVEMENT_BUFFER_ENDS,
  GTK_MOVEMENT_HORIZONTAL_PAGES
}

.enum GtkScrollStep {
  GTK_SCROLL_STEPS,
  GTK_SCROLL_PAGES,
  GTK_SCROLL_ENDS,
  GTK_SCROLL_HORIZONTAL_STEPS,
  GTK_SCROLL_HORIZONTAL_PAGES,
  GTK_SCROLL_HORIZONTAL_ENDS
}

.enum GtkOrientation {
  GTK_ORIENTATION_HORIZONTAL,
  GTK_ORIENTATION_VERTICAL
}

.enum GtkPackType {
  GTK_PACK_START,
  GTK_PACK_END
}

.enum GtkPositionType {
  GTK_POS_LEFT,
  GTK_POS_RIGHT,
  GTK_POS_TOP,
  GTK_POS_BOTTOM
}

.enum GtkReliefStyle {
  GTK_RELIEF_NORMAL,
  GTK_RELIEF_HALF,
  GTK_RELIEF_NONE
}

.enum GtkScrollType {
  GTK_SCROLL_NONE,
  GTK_SCROLL_JUMP,
  GTK_SCROLL_STEP_BACKWARD,
  GTK_SCROLL_STEP_FORWARD,
  GTK_SCROLL_PAGE_BACKWARD,
  GTK_SCROLL_PAGE_FORWARD,
  GTK_SCROLL_STEP_UP,
  GTK_SCROLL_STEP_DOWN,
  GTK_SCROLL_PAGE_UP,
  GTK_SCROLL_PAGE_DOWN,
  GTK_SCROLL_STEP_LEFT,
  GTK_SCROLL_STEP_RIGHT,
  GTK_SCROLL_PAGE_LEFT,
  GTK_SCROLL_PAGE_RIGHT,
  GTK_SCROLL_START,
  GTK_SCROLL_END
}

.enum GtkSelectionMode {
  GTK_SELECTION_NONE,
  GTK_SELECTION_SINGLE,
  GTK_SELECTION_BROWSE,
  GTK_SELECTION_MULTIPLE
}

.enum GtkShadowType {
  GTK_SHADOW_NONE,
  GTK_SHADOW_IN,
  GTK_SHADOW_OUT,
  GTK_SHADOW_ETCHED_IN,
  GTK_SHADOW_ETCHED_OUT
}

.enum GtkStateType {
  GTK_STATE_NORMAL,
  GTK_STATE_ACTIVE,
  GTK_STATE_PRELIGHT,
  GTK_STATE_SELECTED,
  GTK_STATE_INSENSITIVE,
  GTK_STATE_INCONSISTENT,
  GTK_STATE_FOCUSED
}

.enum GtkToolbarStyle {
  GTK_TOOLBAR_ICONS,
  GTK_TOOLBAR_TEXT,
  GTK_TOOLBAR_BOTH,
  GTK_TOOLBAR_BOTH_HORIZ
}

.enum GtkWrapMode {
  GTK_WRAP_NONE,
  GTK_WRAP_CHAR,
  GTK_WRAP_WORD,
  GTK_WRAP_WORD_CHAR
}

.enum GtkSortType {
  GTK_SORT_ASCENDING,
  GTK_SORT_DESCENDING
}

.enum GtkIMPreeditStyle {
  GTK_IM_PREEDIT_NOTHING,
  GTK_IM_PREEDIT_CALLBACK,
  GTK_IM_PREEDIT_NONE
}

.enum GtkIMStatusStyle {
  GTK_IM_STATUS_NOTHING,
  GTK_IM_STATUS_CALLBACK,
  GTK_IM_STATUS_NONE
}

.enum GtkPackDirection {
  GTK_PACK_DIRECTION_LTR,
  GTK_PACK_DIRECTION_RTL,
  GTK_PACK_DIRECTION_TTB,
  GTK_PACK_DIRECTION_BTT
}

.enum GtkPrintPages {
  GTK_PRINT_PAGES_ALL,
  GTK_PRINT_PAGES_CURRENT,
  GTK_PRINT_PAGES_RANGES,
  GTK_PRINT_PAGES_SELECTION
}

.enum GtkPageSet {
  GTK_PAGE_SET_ALL,
  GTK_PAGE_SET_EVEN,
  GTK_PAGE_SET_ODD
}

.enum GtkNumberUpLayout {
  GTK_NUMBER_UP_LAYOUT_LEFT_TO_RIGHT_TOP_TO_BOTTOM,
  GTK_NUMBER_UP_LAYOUT_LEFT_TO_RIGHT_BOTTOM_TO_TOP,
  GTK_NUMBER_UP_LAYOUT_RIGHT_TO_LEFT_TOP_TO_BOTTOM,
  GTK_NUMBER_UP_LAYOUT_RIGHT_TO_LEFT_BOTTOM_TO_TOP,
  GTK_NUMBER_UP_LAYOUT_TOP_TO_BOTTOM_LEFT_TO_RIGHT,
  GTK_NUMBER_UP_LAYOUT_TOP_TO_BOTTOM_RIGHT_TO_LEFT,
  GTK_NUMBER_UP_LAYOUT_BOTTOM_TO_TOP_LEFT_TO_RIGHT,
  GTK_NUMBER_UP_LAYOUT_BOTTOM_TO_TOP_RIGHT_TO_LEFT
}

.enum GtkPageOrientation {
  GTK_PAGE_ORIENTATION_PORTRAIT,
  GTK_PAGE_ORIENTATION_LANDSCAPE,
  GTK_PAGE_ORIENTATION_REVERSE_PORTRAIT,
  GTK_PAGE_ORIENTATION_REVERSE_LANDSCAPE
}

.enum GtkPrintQuality {
  GTK_PRINT_QUALITY_LOW,
  GTK_PRINT_QUALITY_NORMAL,
  GTK_PRINT_QUALITY_HIGH,
  GTK_PRINT_QUALITY_DRAFT
}

.enum GtkPrintDuplex {
  GTK_PRINT_DUPLEX_SIMPLEX,
  GTK_PRINT_DUPLEX_HORIZONTAL,
  GTK_PRINT_DUPLEX_VERTICAL
}


.enum GtkUnit {
  GTK_UNIT_NONE,
  GTK_UNIT_POINTS,
  GTK_UNIT_INCH,
  GTK_UNIT_MM
}

GTK_UNIT_PIXEL equ GTK_UNIT_NONE

.enum GtkTreeViewGridLines {
  GTK_TREE_VIEW_GRID_LINES_NONE,
  GTK_TREE_VIEW_GRID_LINES_HORIZONTAL,
  GTK_TREE_VIEW_GRID_LINES_VERTICAL,
  GTK_TREE_VIEW_GRID_LINES_BOTH
}

.enum GtkDragResult {
  GTK_DRAG_RESULT_SUCCESS,
  GTK_DRAG_RESULT_NO_TARGET,
  GTK_DRAG_RESULT_USER_CANCELLED,
  GTK_DRAG_RESULT_TIMEOUT_EXPIRED,
  GTK_DRAG_RESULT_GRAB_BROKEN,
  GTK_DRAG_RESULT_ERROR
}

.enum GtkSizeGroupMode {
  GTK_SIZE_GROUP_NONE,
  GTK_SIZE_GROUP_HORIZONTAL,
  GTK_SIZE_GROUP_VERTICAL,
  GTK_SIZE_GROUP_BOTH
}

.enum GtkSizeRequestMode {
  GTK_SIZE_REQUEST_HEIGHT_FOR_WIDTH = 0,
  GTK_SIZE_REQUEST_WIDTH_FOR_HEIGHT,
  GTK_SIZE_REQUEST_CONSTANT_SIZE
}

.enum GtkScrollablePolicy {
  GTK_SCROLL_MINIMUM = 0,
  GTK_SCROLL_NATURAL
}

.enum GtkStateFlags {
  GTK_STATE_FLAG_NORMAL       = 0,
  GTK_STATE_FLAG_ACTIVE       = 1 shl 0,
  GTK_STATE_FLAG_PRELIGHT     = 1 shl 1,
  GTK_STATE_FLAG_SELECTED     = 1 shl 2,
  GTK_STATE_FLAG_INSENSITIVE  = 1 shl 3,
  GTK_STATE_FLAG_INCONSISTENT = 1 shl 4,
  GTK_STATE_FLAG_FOCUSED      = 1 shl 5,
  GTK_STATE_FLAG_BACKDROP     = 1 shl 6,
  GTK_STATE_FLAG_DIR_LTR      = 1 shl 7,
  GTK_STATE_FLAG_DIR_RTL      = 1 shl 8,
  GTK_STATE_FLAG_LINK         = 1 shl 9,
  GTK_STATE_FLAG_VISITED      = 1 shl 10,
  GTK_STATE_FLAG_CHECKED      = 1 shl 11
}

.enum GtkRegionFlags {
  GTK_REGION_EVEN    = 1 shl 0,
  GTK_REGION_ODD     = 1 shl 1,
  GTK_REGION_FIRST   = 1 shl 2,
  GTK_REGION_LAST    = 1 shl 3,
  GTK_REGION_ONLY    = 1 shl 4,
  GTK_REGION_SORTED  = 1 shl 5
}

.enum GtkJunctionSides {
  GTK_JUNCTION_NONE   = 0,
  GTK_JUNCTION_CORNER_TOPLEFT = 1 shl 0,
  GTK_JUNCTION_CORNER_TOPRIGHT = 1 shl 1,
  GTK_JUNCTION_CORNER_BOTTOMLEFT = 1 shl 2,
  GTK_JUNCTION_CORNER_BOTTOMRIGHT = 1 shl 3,
  GTK_JUNCTION_TOP    = (GTK_JUNCTION_CORNER_TOPLEFT or GTK_JUNCTION_CORNER_TOPRIGHT),
  GTK_JUNCTION_BOTTOM = (GTK_JUNCTION_CORNER_BOTTOMLEFT or GTK_JUNCTION_CORNER_BOTTOMRIGHT),
  GTK_JUNCTION_LEFT   = (GTK_JUNCTION_CORNER_TOPLEFT or GTK_JUNCTION_CORNER_BOTTOMLEFT),
  GTK_JUNCTION_RIGHT  = (GTK_JUNCTION_CORNER_TOPRIGHT or GTK_JUNCTION_CORNER_BOTTOMRIGHT)
}

.enum GtkBorderStyle {
  GTK_BORDER_STYLE_NONE,
  GTK_BORDER_STYLE_SOLID,
  GTK_BORDER_STYLE_INSET,
  GTK_BORDER_STYLE_OUTSET,
  GTK_BORDER_STYLE_HIDDEN,
  GTK_BORDER_STYLE_DOTTED,
  GTK_BORDER_STYLE_DASHED,
  GTK_BORDER_STYLE_DOUBLE,
  GTK_BORDER_STYLE_GROOVE,
  GTK_BORDER_STYLE_RIDGE
}

.enum GtkLevelBarMode {
  GTK_LEVEL_BAR_MODE_CONTINUOUS,
  GTK_LEVEL_BAR_MODE_DISCRETE
}

.enum GtkInputPurpose {
  GTK_INPUT_PURPOSE_FREE_FORM,
  GTK_INPUT_PURPOSE_ALPHA,
  GTK_INPUT_PURPOSE_DIGITS,
  GTK_INPUT_PURPOSE_NUMBER,
  GTK_INPUT_PURPOSE_PHONE,
  GTK_INPUT_PURPOSE_URL,
  GTK_INPUT_PURPOSE_EMAIL,
  GTK_INPUT_PURPOSE_NAME,
  GTK_INPUT_PURPOSE_PASSWORD,
  GTK_INPUT_PURPOSE_PIN
}

.enum GtkInputHints {
  GTK_INPUT_HINT_NONE                = 0,
  GTK_INPUT_HINT_SPELLCHECK          = 1 shl 0,
  GTK_INPUT_HINT_NO_SPELLCHECK       = 1 shl 1,
  GTK_INPUT_HINT_WORD_COMPLETION     = 1 shl 2,
  GTK_INPUT_HINT_LOWERCASE           = 1 shl 3,
  GTK_INPUT_HINT_UPPERCASE_CHARS     = 1 shl 4,
  GTK_INPUT_HINT_UPPERCASE_WORDS     = 1 shl 5,
  GTK_INPUT_HINT_UPPERCASE_SENTENCES = 1 shl 6,
  GTK_INPUT_HINT_INHIBIT_OSK         = 1 shl 7,
  GTK_INPUT_HINT_VERTICAL_WRITING    = 1 shl 8
}

.enum GtkPropagationPhase {
  GTK_PHASE_NONE,
  GTK_PHASE_CAPTURE,
  GTK_PHASE_BUBBLE,
  GTK_PHASE_TARGET
}

.enum GtkEventSequenceState {
  GTK_EVENT_SEQUENCE_NONE,
  GTK_EVENT_SEQUENCE_CLAIMED,
  GTK_EVENT_SEQUENCE_DENIED
}

.enum GtkPanDirection {
  GTK_PAN_DIRECTION_LEFT,
  GTK_PAN_DIRECTION_RIGHT,
  GTK_PAN_DIRECTION_UP,
  GTK_PAN_DIRECTION_DOWN
}

endif
