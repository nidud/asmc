ifndef _RPC500_
include rpc500.inc
endif
ifndef __uiautomationclient_h__
define __uiautomationclient_h__

include uiautomationcore.inc
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef _INC_UIAUTOMATIONCOREAPI

.enum TreeScope {
    TreeScope_Element	= 0x1,
    TreeScope_Children	= 0x2,
    TreeScope_Descendants	= 0x4,
    TreeScope_Parent	= 0x8,
    TreeScope_Ancestors = 0x10,
    TreeScope_Subtree	= ( ( TreeScope_Element or TreeScope_Children ) or TreeScope_Descendants )
    }

.enum PropertyConditionFlags {
    PropertyConditionFlags_None,
    PropertyConditionFlags_IgnoreCase
    }

.enum AutomationElementMode {
    AutomationElementMode_None,
    AutomationElementMode_Full
    }
endif

ExtendedProperty	STRUC
PropertyName		BSTR ?
PropertyValue		BSTR ?
ExtendedProperty	ENDS
UIA_HWND		typedef ptr

ifndef __UIAutomationClient_LIBRARY_DEFINED__
define __UIAutomationClient_LIBRARY_DEFINED__

externdef		LIBID_UIAutomationClient:IID

ifndef __UIA_PatternIds_MODULE_DEFINED__
define __UIA_PatternIds_MODULE_DEFINED__

define UIA_InvokePatternId		10000
define UIA_SelectionPatternId		10001
define UIA_ValuePatternId		10002
define UIA_RangeValuePatternId		10003
define UIA_ScrollPatternId		10004
define UIA_ExpandCollapsePatternId	10005
define UIA_GridPatternId		10006
define UIA_GridItemPatternId		10007
define UIA_MultipleViewPatternId	10008
define UIA_WindowPatternId		10009
define UIA_SelectionItemPatternId	10010
define UIA_DockPatternId		10011
define UIA_TablePatternId		10012
define UIA_TableItemPatternId		10013
define UIA_TextPatternId		10014
define UIA_TogglePatternId		10015
define UIA_TransformPatternId		10016
define UIA_ScrollItemPatternId		10017
define UIA_LegacyIAccessiblePatternId	10018
define UIA_ItemContainerPatternId	10019
define UIA_VirtualizedItemPatternId	10020
define UIA_SynchronizedInputPatternId	10021
define UIA_ObjectModelPatternId		10022
define UIA_AnnotationPatternId		10023
define UIA_TextPattern2Id		10024
define UIA_StylesPatternId		10025
define UIA_SpreadsheetPatternId		10026
define UIA_SpreadsheetItemPatternId	10027
define UIA_TransformPattern2Id		10028
define UIA_TextChildPatternId		10029
define UIA_DragPatternId		10030
define UIA_DropTargetPatternId		10031
define UIA_TextEditPatternId		10032

endif

ifndef __UIA_EventIds_MODULE_DEFINED__
define __UIA_EventIds_MODULE_DEFINED__

define UIA_ToolTipOpenedEventId		20000
define UIA_ToolTipClosedEventId		20001
define UIA_StructureChangedEventId	20002
define UIA_MenuOpenedEventId		20003
define UIA_AutomationPropertyChangedEventId 20004
define UIA_AutomationFocusChangedEventId 20005
define UIA_AsyncContentLoadedEventId	20006
define UIA_MenuClosedEventId		20007
define UIA_LayoutInvalidatedEventId	20008
define UIA_Invoke_InvokedEventId	20009
define UIA_SelectionItem_ElementAddedToSelectionEventId 20010
define UIA_SelectionItem_ElementRemovedFromSelectionEventId 20011
define UIA_SelectionItem_ElementSelectedEventId 20012
define UIA_Selection_InvalidatedEventId 20013
define UIA_Text_TextSelectionChangedEventId 20014
define UIA_Text_TextChangedEventId	20015
define UIA_Window_WindowOpenedEventId	20016
define UIA_Window_WindowClosedEventId	20017
define UIA_MenuModeStartEventId		20018
define UIA_MenuModeEndEventId		20019
define UIA_InputReachedTargetEventId	20020
define UIA_InputReachedOtherElementEventId 20021
define UIA_InputDiscardedEventId	20022
define UIA_SystemAlertEventId		20023
define UIA_LiveRegionChangedEventId	20024
define UIA_HostedFragmentRootsInvalidatedEventId 20025
define UIA_Drag_DragStartEventId	20026
define UIA_Drag_DragCancelEventId	20027
define UIA_Drag_DragCompleteEventId	20028
define UIA_DropTarget_DragEnterEventId	20029
define UIA_DropTarget_DragLeaveEventId	20030
define UIA_DropTarget_DroppedEventId	20031
define UIA_TextEdit_TextChangedEventId	20032
define UIA_TextEdit_ConversionTargetChangedEventId 20033

endif

ifndef __UIA_PropertyIds_MODULE_DEFINED__
define __UIA_PropertyIds_MODULE_DEFINED__

define UIA_RuntimeIdPropertyId			30000
define UIA_BoundingRectanglePropertyId		30001
define UIA_ProcessIdPropertyId			30002
define UIA_ControlTypePropertyId		30003
define UIA_LocalizedControlTypePropertyId	30004
define UIA_NamePropertyId			30005
define UIA_AcceleratorKeyPropertyId		30006
define UIA_AccessKeyPropertyId			30007
define UIA_HasKeyboardFocusPropertyId		30008
define UIA_IsKeyboardFocusablePropertyId	30009
define UIA_IsEnabledPropertyId			30010
define UIA_AutomationIdPropertyId		30011
define UIA_ClassNamePropertyId			30012
define UIA_HelpTextPropertyId			30013
define UIA_ClickablePointPropertyId		30014
define UIA_CulturePropertyId			30015
define UIA_IsControlElementPropertyId		30016
define UIA_IsContentElementPropertyId		30017
define UIA_LabeledByPropertyId			30018
define UIA_IsPasswordPropertyId			30019
define UIA_NativeWindowHandlePropertyId		30020
define UIA_ItemTypePropertyId			30021
define UIA_IsOffscreenPropertyId		30022
define UIA_OrientationPropertyId		30023
define UIA_FrameworkIdPropertyId		30024
define UIA_IsRequiredForFormPropertyId		30025
define UIA_ItemStatusPropertyId			30026
define UIA_IsDockPatternAvailablePropertyId	30027
define UIA_IsExpandCollapsePatternAvailablePropertyId 30028
define UIA_IsGridItemPatternAvailablePropertyId 30029
define UIA_IsGridPatternAvailablePropertyId	30030
define UIA_IsInvokePatternAvailablePropertyId	30031
define UIA_IsMultipleViewPatternAvailablePropertyId 30032
define UIA_IsRangeValuePatternAvailablePropertyId 30033
define UIA_IsScrollPatternAvailablePropertyId	30034
define UIA_IsScrollItemPatternAvailablePropertyId 30035
define UIA_IsSelectionItemPatternAvailablePropertyId 30036
define UIA_IsSelectionPatternAvailablePropertyId 30037
define UIA_IsTablePatternAvailablePropertyId	30038
define UIA_IsTableItemPatternAvailablePropertyId 30039
define UIA_IsTextPatternAvailablePropertyId	30040
define UIA_IsTogglePatternAvailablePropertyId	30041
define UIA_IsTransformPatternAvailablePropertyId 30042
define UIA_IsValuePatternAvailablePropertyId	30043
define UIA_IsWindowPatternAvailablePropertyId	30044
define UIA_ValueValuePropertyId			30045
define UIA_ValueIsReadOnlyPropertyId		30046
define UIA_RangeValueValuePropertyId		30047
define UIA_RangeValueIsReadOnlyPropertyId	30048
define UIA_RangeValueMinimumPropertyId		30049
define UIA_RangeValueMaximumPropertyId		30050
define UIA_RangeValueLargeChangePropertyId	30051
define UIA_RangeValueSmallChangePropertyId	30052
define UIA_ScrollHorizontalScrollPercentPropertyId 30053
define UIA_ScrollHorizontalViewSizePropertyId	30054
define UIA_ScrollVerticalScrollPercentPropertyId 30055
define UIA_ScrollVerticalViewSizePropertyId	30056
define UIA_ScrollHorizontallyScrollablePropertyId 30057
define UIA_ScrollVerticallyScrollablePropertyId 30058
define UIA_SelectionSelectionPropertyId		30059
define UIA_SelectionCanSelectMultiplePropertyId 30060
define UIA_SelectionIsSelectionRequiredPropertyId 30061
define UIA_GridRowCountPropertyId		30062
define UIA_GridColumnCountPropertyId		30063
define UIA_GridItemRowPropertyId		30064
define UIA_GridItemColumnPropertyId		30065
define UIA_GridItemRowSpanPropertyId		30066
define UIA_GridItemColumnSpanPropertyId		30067
define UIA_GridItemContainingGridPropertyId	30068
define UIA_DockDockPositionPropertyId		30069
define UIA_ExpandCollapseExpandCollapseStatePropertyId 30070
define UIA_MultipleViewCurrentViewPropertyId	30071
define UIA_MultipleViewSupportedViewsPropertyId 30072
define UIA_WindowCanMaximizePropertyId		30073
define UIA_WindowCanMinimizePropertyId		30074
define UIA_WindowWindowVisualStatePropertyId	30075
define UIA_WindowWindowInteractionStatePropertyId 30076
define UIA_WindowIsModalPropertyId		30077
define UIA_WindowIsTopmostPropertyId		30078
define UIA_SelectionItemIsSelectedPropertyId	30079
define UIA_SelectionItemSelectionContainerPropertyId 30080
define UIA_TableRowHeadersPropertyId		30081
define UIA_TableColumnHeadersPropertyId		30082
define UIA_TableRowOrColumnMajorPropertyId	30083
define UIA_TableItemRowHeaderItemsPropertyId	30084
define UIA_TableItemColumnHeaderItemsPropertyId 30085
define UIA_ToggleToggleStatePropertyId		30086
define UIA_TransformCanMovePropertyId		30087
define UIA_TransformCanResizePropertyId		30088
define UIA_TransformCanRotatePropertyId		30089
define UIA_IsLegacyIAccessiblePatternAvailablePropertyId 30090
define UIA_LegacyIAccessibleChildIdPropertyId	30091
define UIA_LegacyIAccessibleNamePropertyId	30092
define UIA_LegacyIAccessibleValuePropertyId	30093
define UIA_LegacyIAccessibleDescriptionPropertyId 30094
define UIA_LegacyIAccessibleRolePropertyId	30095
define UIA_LegacyIAccessibleStatePropertyId	30096
define UIA_LegacyIAccessibleHelpPropertyId	30097
define UIA_LegacyIAccessibleKeyboardShortcutPropertyId 30098
define UIA_LegacyIAccessibleSelectionPropertyId 30099
define UIA_LegacyIAccessibleDefaultActionPropertyId 30100
define UIA_AriaRolePropertyId			30101
define UIA_AriaPropertiesPropertyId		30102
define UIA_IsDataValidForFormPropertyId		30103
define UIA_ControllerForPropertyId		30104
define UIA_DescribedByPropertyId		30105
define UIA_FlowsToPropertyId			30106
define UIA_ProviderDescriptionPropertyId	30107
define UIA_IsItemContainerPatternAvailablePropertyId 30108
define UIA_IsVirtualizedItemPatternAvailablePropertyId 30109
define UIA_IsSynchronizedInputPatternAvailablePropertyId 30110
define UIA_OptimizeForVisualContentPropertyId	30111
define UIA_IsObjectModelPatternAvailablePropertyId 30112
define UIA_AnnotationAnnotationTypeIdPropertyId 30113
define UIA_AnnotationAnnotationTypeNamePropertyId 30114
define UIA_AnnotationAuthorPropertyId		30115
define UIA_AnnotationDateTimePropertyId		30116
define UIA_AnnotationTargetPropertyId		30117
define UIA_IsAnnotationPatternAvailablePropertyId 30118
define UIA_IsTextPattern2AvailablePropertyId	30119
define UIA_StylesStyleIdPropertyId		30120
define UIA_StylesStyleNamePropertyId		30121
define UIA_StylesFillColorPropertyId		30122
define UIA_StylesFillPatternStylePropertyId	30123
define UIA_StylesShapePropertyId		30124
define UIA_StylesFillPatternColorPropertyId	30125
define UIA_StylesExtendedPropertiesPropertyId	30126
define UIA_IsStylesPatternAvailablePropertyId	30127
define UIA_IsSpreadsheetPatternAvailablePropertyId 30128
define UIA_SpreadsheetItemFormulaPropertyId	30129
define UIA_SpreadsheetItemAnnotationObjectsPropertyId 30130
define UIA_SpreadsheetItemAnnotationTypesPropertyId 30131
define UIA_IsSpreadsheetItemPatternAvailablePropertyId 30132
define UIA_Transform2CanZoomPropertyId		30133
define UIA_IsTransformPattern2AvailablePropertyId 30134
define UIA_LiveSettingPropertyId		30135
define UIA_IsTextChildPatternAvailablePropertyId 30136
define UIA_IsDragPatternAvailablePropertyId	30137
define UIA_DragIsGrabbedPropertyId		30138
define UIA_DragDropEffectPropertyId		30139
define UIA_DragDropEffectsPropertyId		30140
define UIA_IsDropTargetPatternAvailablePropertyId 30141
define UIA_DropTargetDropTargetEffectPropertyId 30142
define UIA_DropTargetDropTargetEffectsPropertyId 30143
define UIA_DragGrabbedItemsPropertyId		30144
define UIA_Transform2ZoomLevelPropertyId	30145
define UIA_Transform2ZoomMinimumPropertyId	30146
define UIA_Transform2ZoomMaximumPropertyId	30147
define UIA_FlowsFromPropertyId			30148
define UIA_IsTextEditPatternAvailablePropertyId 30149
define UIA_IsPeripheralPropertyId		30150

endif

ifndef __UIA_TextAttributeIds_MODULE_DEFINED__
define __UIA_TextAttributeIds_MODULE_DEFINED__

define UIA_AnimationStyleAttributeId	40000
define UIA_BackgroundColorAttributeId	40001
define UIA_BulletStyleAttributeId	40002
define UIA_CapStyleAttributeId		40003
define UIA_CultureAttributeId		40004
define UIA_FontNameAttributeId		40005
define UIA_FontSizeAttributeId		40006
define UIA_FontWeightAttributeId	40007
define UIA_ForegroundColorAttributeId	40008
define UIA_HorizontalTextAlignmentAttributeId 40009
define UIA_IndentationFirstLineAttributeId 40010
define UIA_IndentationLeadingAttributeId 40011
define UIA_IndentationTrailingAttributeId 40012
define UIA_IsHiddenAttributeId		40013
define UIA_IsItalicAttributeId		40014
define UIA_IsReadOnlyAttributeId	40015
define UIA_IsSubscriptAttributeId	40016
define UIA_IsSuperscriptAttributeId	40017
define UIA_MarginBottomAttributeId	40018
define UIA_MarginLeadingAttributeId	40019
define UIA_MarginTopAttributeId		40020
define UIA_MarginTrailingAttributeId	40021
define UIA_OutlineStylesAttributeId	40022
define UIA_OverlineColorAttributeId	40023
define UIA_OverlineStyleAttributeId	40024
define UIA_StrikethroughColorAttributeId 40025
define UIA_StrikethroughStyleAttributeId 40026
define UIA_TabsAttributeId		40027
define UIA_TextFlowDirectionsAttributeId 40028
define UIA_UnderlineColorAttributeId	40029
define UIA_UnderlineStyleAttributeId	40030
define UIA_AnnotationTypesAttributeId	40031
define UIA_AnnotationObjectsAttributeId 40032
define UIA_StyleNameAttributeId		40033
define UIA_StyleIdAttributeId		40034
define UIA_LinkAttributeId		40035
define UIA_IsActiveAttributeId		40036
define UIA_SelectionActiveEndAttributeId 40037
define UIA_CaretPositionAttributeId	40038
define UIA_CaretBidiModeAttributeId	40039

endif

ifndef __UIA_ControlTypeIds_MODULE_DEFINED__
define __UIA_ControlTypeIds_MODULE_DEFINED__

define UIA_ButtonControlTypeId		50000
define UIA_CalendarControlTypeId	50001
define UIA_CheckBoxControlTypeId	50002
define UIA_ComboBoxControlTypeId	50003
define UIA_EditControlTypeId		50004
define UIA_HyperlinkControlTypeId	50005
define UIA_ImageControlTypeId		50006
define UIA_ListItemControlTypeId	50007
define UIA_ListControlTypeId		50008
define UIA_MenuControlTypeId		50009
define UIA_MenuBarControlTypeId		50010
define UIA_MenuItemControlTypeId	50011
define UIA_ProgressBarControlTypeId	50012
define UIA_RadioButtonControlTypeId	50013
define UIA_ScrollBarControlTypeId	50014
define UIA_SliderControlTypeId		50015
define UIA_SpinnerControlTypeId		50016
define UIA_StatusBarControlTypeId	50017
define UIA_TabControlTypeId		50018
define UIA_TabItemControlTypeId		50019
define UIA_TextControlTypeId		50020
define UIA_ToolBarControlTypeId		50021
define UIA_ToolTipControlTypeId		50022
define UIA_TreeControlTypeId		50023
define UIA_TreeItemControlTypeId	50024
define UIA_CustomControlTypeId		50025
define UIA_GroupControlTypeId		50026
define UIA_ThumbControlTypeId		50027
define UIA_DataGridControlTypeId	50028
define UIA_DataItemControlTypeId	50029
define UIA_DocumentControlTypeId	50030
define UIA_SplitButtonControlTypeId	50031
define UIA_WindowControlTypeId		50032
define UIA_PaneControlTypeId		50033
define UIA_HeaderControlTypeId		50034
define UIA_HeaderItemControlTypeId	50035
define UIA_TableControlTypeId		50036
define UIA_TitleBarControlTypeId	50037
define UIA_SeparatorControlTypeId	50038
define UIA_SemanticZoomControlTypeId	50039
define UIA_AppBarControlTypeId		50040

endif

ifndef __UIA_AnnotationTypes_MODULE_DEFINED__
define __UIA_AnnotationTypes_MODULE_DEFINED__

define AnnotationType_Unknown		60000
define AnnotationType_SpellingError	60001
define AnnotationType_GrammarError	60002
define AnnotationType_Comment		60003
define AnnotationType_FormulaError	60004
define AnnotationType_TrackChanges	60005
define AnnotationType_Header		60006
define AnnotationType_Footer		60007
define AnnotationType_Highlighted	60008

endif

ifndef __UIA_StyleIds_MODULE_DEFINED__
define __UIA_StyleIds_MODULE_DEFINED__

define StyleId_Custom		70000
define StyleId_Heading1		70001
define StyleId_Heading2		70002
define StyleId_Heading3		70003
define StyleId_Heading4		70004
define StyleId_Heading5		70005
define StyleId_Heading6		70006
define StyleId_Heading7		70007
define StyleId_Heading8		70008
define StyleId_Heading9		70009
define StyleId_Title		70010
define StyleId_Subtitle		70011
define StyleId_Normal		70012
define StyleId_Emphasis		70013
define StyleId_Quote		70014
define StyleId_BulletedList	70015
define StyleId_NumberedList	70016

endif

ifndef __IUIAutomationElement_INTERFACE_DEFINED__
define __IUIAutomationElement_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationElement, "d22108aa-8ac5-49a5-837b-37bbb3d7591e")

.comdef IUIAutomationElement : public IUnknown

    SetFocus		proc
    GetRuntimeId	proc :ptr
    FindFirst		proc :TreeScope, :ptr, :ptr
    FindAll		proc :TreeScope, :ptr, :ptr
    FindFirstBuildCache proc :TreeScope, :ptr, :ptr, :ptr
    FindAllBuildCache	proc :TreeScope, :ptr, :ptr, :ptr
    BuildUpdatedCache	proc :ptr, :ptr
    GetCurrentPropertyValue proc :PROPERTYID, :ptr
    GetCurrentPropertyValueEx proc :PROPERTYID, :BOOL, :ptr
    GetCachedPropertyValue proc :PROPERTYID, :ptr
    GetCachedPropertyValueEx proc :PROPERTYID, :BOOL, :ptr
    GetCurrentPatternAs proc :PATTERNID, :REFIID, :ptr
    GetCachedPatternAs	proc :PATTERNID, :REFIID, :ptr
    GetCurrentPattern	proc :PATTERNID, :ptr
    GetCachedPattern	proc :PATTERNID, :ptr
    GetCachedParent	proc :ptr
    GetCachedChildren	proc :ptr
    get_CurrentProcessId proc :ptr
    get_CurrentControlType proc :ptr
    get_CurrentLocalizedControlType proc :ptr
    get_CurrentName	proc :ptr
    get_CurrentAcceleratorKey proc :ptr
    get_CurrentAccessKey proc :ptr
    get_CurrentHasKeyboardFocus proc :ptr
    get_CurrentIsKeyboardFocusable proc :ptr
    get_CurrentIsEnabled proc :ptr
    get_CurrentAutomationId proc :ptr
    get_CurrentClassName proc :ptr
    get_CurrentHelpText proc :ptr
    get_CurrentCulture	proc :ptr
    get_CurrentIsControlElement proc :ptr
    get_CurrentIsContentElement proc :ptr
    get_CurrentIsPassword proc :ptr
    get_CurrentNativeWindowHandle proc :ptr
    get_CurrentItemType proc :ptr
    get_CurrentIsOffscreen proc :ptr
    get_CurrentOrientation proc :ptr
    get_CurrentFrameworkId proc :ptr
    get_CurrentIsRequiredForForm proc :ptr
    get_CurrentItemStatus proc :ptr
    get_CurrentBoundingRectangle proc :ptr
    get_CurrentLabeledBy proc :ptr
    get_CurrentAriaRole proc :ptr
    get_CurrentAriaProperties proc :ptr
    get_CurrentIsDataValidForForm proc :ptr
    get_CurrentControllerFor proc :ptr
    get_CurrentDescribedBy proc :ptr
    get_CurrentFlowsTo	proc :ptr
    get_CurrentProviderDescription proc :ptr
    get_CachedProcessId proc :ptr
    get_CachedControlType proc :ptr
    get_CachedLocalizedControlType proc :ptr
    get_CachedName	proc :ptr
    get_CachedAcceleratorKey proc :ptr
    get_CachedAccessKey proc :ptr
    get_CachedHasKeyboardFocus proc :ptr
    get_CachedIsKeyboardFocusable proc :ptr
    get_CachedIsEnabled proc :ptr
    get_CachedAutomationId proc :ptr
    get_CachedClassName proc :ptr
    get_CachedHelpText	proc :ptr
    get_CachedCulture	proc :ptr
    get_CachedIsControlElement proc :ptr
    get_CachedIsContentElement proc :ptr
    get_CachedIsPassword proc :ptr
    get_CachedNativeWindowHandle proc :ptr
    get_CachedItemType	proc :ptr
    get_CachedIsOffscreen proc :ptr
    get_CachedOrientation proc :ptr
    get_CachedFrameworkId proc :ptr
    get_CachedIsRequiredForForm proc :ptr
    get_CachedItemStatus proc :ptr
    get_CachedBoundingRectangle proc :ptr
    get_CachedLabeledBy proc :ptr
    get_CachedAriaRole	proc :ptr
    get_CachedAriaProperties proc :ptr
    get_CachedIsDataValidForForm proc :ptr
    get_CachedControllerFor proc :ptr
    get_CachedDescribedBy proc :ptr
    get_CachedFlowsTo	proc :ptr
    get_CachedProviderDescription proc :ptr
    GetClickablePoint	proc :ptr, :ptr
   .ends

endif

ifndef __IUIAutomationElementArray_INTERFACE_DEFINED__
define __IUIAutomationElementArray_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationElementArray, "14314595-b4bc-4055-95f2-58f2e42c9855")

.comdef IUIAutomationElementArray : public IUnknown

    get_Length		proc :ptr
    GetElement		proc :SINT, :ptr
   .ends

endif

ifndef __IUIAutomationCondition_INTERFACE_DEFINED__
define __IUIAutomationCondition_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationCondition, "352ffba8-0973-437c-a61f-f64cafd81df9")

.comdef IUIAutomationCondition : public IUnknown

   .ends

endif

ifndef __IUIAutomationBoolCondition_INTERFACE_DEFINED__
define __IUIAutomationBoolCondition_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationBoolCondition, "1b4e1f2e-75eb-4d0b-8952-5a69988e2307")

.comdef IUIAutomationBoolCondition : public IUIAutomationCondition

    get_BooleanValue	proc :ptr
   .ends

endif

ifndef __IUIAutomationPropertyCondition_INTERFACE_DEFINED__
define __IUIAutomationPropertyCondition_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationPropertyCondition, "99ebf2cb-5578-4267-9ad4-afd6ea77e94b")

.comdef IUIAutomationPropertyCondition : public IUIAutomationCondition

    get_PropertyId	proc :ptr
    get_PropertyValue	proc :ptr
    get_PropertyConditionFlags proc :ptr
   .ends

endif

ifndef __IUIAutomationAndCondition_INTERFACE_DEFINED__
define __IUIAutomationAndCondition_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationAndCondition, "a7d0af36-b912-45fe-9855-091ddc174aec")

.comdef IUIAutomationAndCondition : public IUIAutomationCondition

    get_ChildCount	proc :ptr
    GetChildrenAsNativeArray proc
    GetChildren		proc :ptr
   .ends

endif

ifndef __IUIAutomationOrCondition_INTERFACE_DEFINED__
define __IUIAutomationOrCondition_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationOrCondition, "8753f032-3db1-47b5-a1fc-6e34a266c712")

.comdef IUIAutomationOrCondition : public IUIAutomationCondition

    get_ChildCount	proc :ptr
    GetChildrenAsNativeArray proc
    GetChildren		proc :ptr
   .ends

endif

ifndef __IUIAutomationNotCondition_INTERFACE_DEFINED__
define __IUIAutomationNotCondition_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationNotCondition, "f528b657-847b-498c-8896-d52b565407a1")

.comdef IUIAutomationNotCondition : public IUIAutomationCondition

    GetChild		proc :ptr
   .ends

endif

ifndef __IUIAutomationCacheRequest_INTERFACE_DEFINED__
define __IUIAutomationCacheRequest_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationCacheRequest, "b32a92b5-bc25-4078-9c08-d7ee95c48e03")

.comdef IUIAutomationCacheRequest : public IUnknown

    AddProperty		proc :PROPERTYID
    AddPattern		proc :PATTERNID
    Clone		proc :ptr
    get_TreeScope	proc :ptr
    put_TreeScope	proc :TreeScope
    get_TreeFilter	proc :ptr
    put_TreeFilter	proc :ptr
    get_AutomationElementMode proc :ptr
    put_AutomationElementMode proc :AutomationElementMode
   .ends

endif

ifndef __IUIAutomationTreeWalker_INTERFACE_DEFINED__
define __IUIAutomationTreeWalker_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationTreeWalker, "4042c624-389c-4afc-a630-9df854a541fc")

.comdef IUIAutomationTreeWalker : public IUnknown

    GetParentElement	proc :ptr, :ptr
    GetFirstChildElement proc :ptr, :ptr
    GetLastChildElement proc :ptr, :ptr
    GetNextSiblingElement proc :ptr, :ptr
    GetPreviousSiblingElement proc :ptr, :ptr
    NormalizeElement	proc :ptr, :ptr
    GetParentElementBuildCache proc :ptr, :ptr, :ptr
    GetFirstChildElementBuildCache proc :ptr, :ptr, :ptr
    GetLastChildElementBuildCache proc :ptr, :ptr, :ptr
    GetNextSiblingElementBuildCache proc :ptr, :ptr, :ptr
    GetPreviousSiblingElementBuildCache proc :ptr, :ptr, :ptr
    NormalizeElementBuildCache proc :ptr, :ptr, :ptr
    get_Condition	proc :ptr
   .ends

endif

ifndef __IUIAutomationEventHandler_INTERFACE_DEFINED__
define __IUIAutomationEventHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationEventHandler, "146c3c17-f12e-4e22-8c27-f894b9b79c69")

.comdef IUIAutomationEventHandler : public IUnknown

    HandleAutomationEvent proc :ptr, :EVENTID
   .ends

endif

ifndef __IUIAutomationPropertyChangedEventHandler_INTERFACE_DEFINED__
define __IUIAutomationPropertyChangedEventHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationPropertyChangedEventHandler, "40cd37d4-c756-4b0c-8c6f-bddfeeb13b50")

.comdef IUIAutomationPropertyChangedEventHandler : public IUnknown

    HandlePropertyChangedEvent proc :ptr, :PROPERTYID, :VARIANT
   .ends

endif

ifndef __IUIAutomationStructureChangedEventHandler_INTERFACE_DEFINED__
define __IUIAutomationStructureChangedEventHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationStructureChangedEventHandler, "e81d1b4e-11c5-42f8-9754-e7036c79f054")

.comdef IUIAutomationStructureChangedEventHandler : public IUnknown

    HandleStructureChangedEvent proc :ptr, :StructureChangeType, :ptr
   .ends

endif

ifndef __IUIAutomationFocusChangedEventHandler_INTERFACE_DEFINED__
define __IUIAutomationFocusChangedEventHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationFocusChangedEventHandler, "c270f6b5-5c69-4290-9745-7a7f97169468")

.comdef IUIAutomationFocusChangedEventHandler : public IUnknown

    HandleFocusChangedEvent proc :ptr
   .ends

endif

ifndef __IUIAutomationTextEditTextChangedEventHandler_INTERFACE_DEFINED__
define __IUIAutomationTextEditTextChangedEventHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationTextEditTextChangedEventHandler, "92FAA680-E704-4156-931A-E32D5BB38F3F")

.comdef IUIAutomationTextEditTextChangedEventHandler : public IUnknown

    HandleTextEditTextChangedEvent proc :ptr, :TextEditChangeType, :ptr
   .ends

endif

ifndef __IUIAutomationInvokePattern_INTERFACE_DEFINED__
define __IUIAutomationInvokePattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationInvokePattern, "fb377fbe-8ea6-46d5-9c73-6499642d3059")

.comdef IUIAutomationInvokePattern : public IUnknown

    _Invoke		proc
   .ends

endif

ifndef __IUIAutomationDockPattern_INTERFACE_DEFINED__
define __IUIAutomationDockPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationDockPattern, "fde5ef97-1464-48f6-90bf-43d0948e86ec")

.comdef IUIAutomationDockPattern : public IUnknown

    SetDockPosition	proc :DockPosition
    get_CurrentDockPosition proc :ptr
    get_CachedDockPosition proc :ptr
   .ends

endif

ifndef __IUIAutomationExpandCollapsePattern_INTERFACE_DEFINED__
define __IUIAutomationExpandCollapsePattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationExpandCollapsePattern, "619be086-1f4e-4ee4-bafa-210128738730")

.comdef IUIAutomationExpandCollapsePattern : public IUnknown

    Expand		proc
    Collapse		proc
    get_CurrentExpandCollapseState proc :ptr
    get_CachedExpandCollapseState proc :ptr
   .ends

endif

ifndef __IUIAutomationGridPattern_INTERFACE_DEFINED__
define __IUIAutomationGridPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationGridPattern, "414c3cdc-856b-4f5b-8538-3131c6302550")

.comdef IUIAutomationGridPattern : public IUnknown

    GetItem		proc :SINT, :SINT, :ptr
    get_CurrentRowCount proc :ptr
    get_CurrentColumnCount proc :ptr
    get_CachedRowCount	proc :ptr
    get_CachedColumnCount proc :ptr
   .ends

endif

ifndef __IUIAutomationGridItemPattern_INTERFACE_DEFINED__
define __IUIAutomationGridItemPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationGridItemPattern, "78f8ef57-66c3-4e09-bd7c-e79b2004894d")

.comdef IUIAutomationGridItemPattern : public IUnknown

    get_CurrentContainingGrid proc :ptr
    get_CurrentRow	proc :ptr
    get_CurrentColumn	proc :ptr
    get_CurrentRowSpan	proc :ptr
    get_CurrentColumnSpan proc :ptr
    get_CachedContainingGrid proc :ptr
    get_CachedRow	proc :ptr
    get_CachedColumn	proc :ptr
    get_CachedRowSpan	proc :ptr
    get_CachedColumnSpan proc :ptr
   .ends

endif

ifndef __IUIAutomationMultipleViewPattern_INTERFACE_DEFINED__
define __IUIAutomationMultipleViewPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationMultipleViewPattern, "8d253c91-1dc5-4bb5-b18f-ade16fa495e8")

.comdef IUIAutomationMultipleViewPattern : public IUnknown

    GetViewName		proc :SINT, :ptr
    SetCurrentView	proc :SINT
    get_CurrentCurrentView proc :ptr
    GetCurrentSupportedViews proc :ptr
    get_CachedCurrentView proc :ptr
    GetCachedSupportedViews proc :ptr
   .ends

endif

ifndef __IUIAutomationObjectModelPattern_INTERFACE_DEFINED__
define __IUIAutomationObjectModelPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationObjectModelPattern, "71c284b3-c14d-4d14-981e-19751b0d756d")

.comdef IUIAutomationObjectModelPattern : public IUnknown

    GetUnderlyingObjectModel proc :ptr
   .ends

endif

ifndef __IUIAutomationRangeValuePattern_INTERFACE_DEFINED__
define __IUIAutomationRangeValuePattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationRangeValuePattern, "59213f4f-7346-49e5-b120-80555987a148")

.comdef IUIAutomationRangeValuePattern : public IUnknown

    SetValue		proc :real8
    get_CurrentValue	proc :ptr
    get_CurrentIsReadOnly proc :ptr
    get_CurrentMaximum	proc :ptr
    get_CurrentMinimum	proc :ptr
    get_CurrentLargeChange proc :ptr
    get_CurrentSmallChange proc :ptr
    get_CachedValue	proc :ptr
    get_CachedIsReadOnly proc :ptr
    get_CachedMaximum	proc :ptr
    get_CachedMinimum	proc :ptr
    get_CachedLargeChange proc :ptr
    get_CachedSmallChange proc :ptr
   .ends

endif

ifndef __IUIAutomationScrollPattern_INTERFACE_DEFINED__
define __IUIAutomationScrollPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationScrollPattern, "88f4d42a-e881-459d-a77c-73bbbb7e02dc")

.comdef IUIAutomationScrollPattern : public IUnknown

    Scroll		proc :ScrollAmount, :ScrollAmount
    SetScrollPercent	proc :real8, :real8
    get_CurrentHorizontalScrollPercent proc :ptr
    get_CurrentVerticalScrollPercent proc :ptr
    get_CurrentHorizontalViewSize proc :ptr
    get_CurrentVerticalViewSize proc :ptr
    get_CurrentHorizontallyScrollable proc :ptr
    get_CurrentVerticallyScrollable proc :ptr
    get_CachedHorizontalScrollPercent proc :ptr
    get_CachedVerticalScrollPercent proc :ptr
    get_CachedHorizontalViewSize proc :ptr
    get_CachedVerticalViewSize proc :ptr
    get_CachedHorizontallyScrollable proc :ptr
    get_CachedVerticallyScrollable proc :ptr
   .ends

endif

ifndef __IUIAutomationScrollItemPattern_INTERFACE_DEFINED__
define __IUIAutomationScrollItemPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationScrollItemPattern, "b488300f-d015-4f19-9c29-bb595e3645ef")

.comdef IUIAutomationScrollItemPattern : public IUnknown

    ScrollIntoView	proc
   .ends

endif

ifndef __IUIAutomationSelectionPattern_INTERFACE_DEFINED__
define __IUIAutomationSelectionPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationSelectionPattern, "5ed5202e-b2ac-47a6-b638-4b0bf140d78e")

.comdef IUIAutomationSelectionPattern : public IUnknown

    GetCurrentSelection proc :ptr
    get_CurrentCanSelectMultiple proc :ptr
    get_CurrentIsSelectionRequired proc :ptr
    GetCachedSelection	proc :ptr
    get_CachedCanSelectMultiple proc :ptr
    get_CachedIsSelectionRequired proc :ptr
   .ends

endif

ifndef __IUIAutomationSelectionItemPattern_INTERFACE_DEFINED__
define __IUIAutomationSelectionItemPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationSelectionItemPattern, "a8efa66a-0fda-421a-9194-38021f3578ea")

.comdef IUIAutomationSelectionItemPattern : public IUnknown

    Select		proc
    AddToSelection	proc
    RemoveFromSelection proc
    get_CurrentIsSelected proc :ptr
    get_CurrentSelectionContainer proc :ptr
    get_CachedIsSelected proc :ptr
    get_CachedSelectionContainer proc :ptr
   .ends

endif

ifndef __IUIAutomationSynchronizedInputPattern_INTERFACE_DEFINED__
define __IUIAutomationSynchronizedInputPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationSynchronizedInputPattern, "2233be0b-afb7-448b-9fda-3b378aa5eae1")

.comdef IUIAutomationSynchronizedInputPattern : public IUnknown

    StartListening	proc :SynchronizedInputType
    Cancel		proc
   .ends

endif

ifndef __IUIAutomationTablePattern_INTERFACE_DEFINED__
define __IUIAutomationTablePattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationTablePattern, "620e691c-ea96-4710-a850-754b24ce2417")

.comdef IUIAutomationTablePattern : public IUnknown

    GetCurrentRowHeaders proc :ptr
    GetCurrentColumnHeaders proc :ptr
    get_CurrentRowOrColumnMajor proc :ptr
    GetCachedRowHeaders proc :ptr
    GetCachedColumnHeaders proc :ptr
    get_CachedRowOrColumnMajor proc :ptr
   .ends

endif

ifndef __IUIAutomationTableItemPattern_INTERFACE_DEFINED__
define __IUIAutomationTableItemPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationTableItemPattern, "0b964eb3-ef2e-4464-9c79-61d61737a27e")

.comdef IUIAutomationTableItemPattern : public IUnknown

    GetCurrentRowHeaderItems proc :ptr
    GetCurrentColumnHeaderItems proc :ptr
    GetCachedRowHeaderItems proc :ptr
    GetCachedColumnHeaderItems proc :ptr
   .ends

endif

ifndef __IUIAutomationTogglePattern_INTERFACE_DEFINED__
define __IUIAutomationTogglePattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationTogglePattern, "94cf8058-9b8d-4ab9-8bfd-4cd0a33c8c70")

.comdef IUIAutomationTogglePattern : public IUnknown

    Toggle		proc
    get_CurrentToggleState proc :ptr
    get_CachedToggleState proc :ptr
   .ends

endif

ifndef __IUIAutomationTransformPattern_INTERFACE_DEFINED__
define __IUIAutomationTransformPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationTransformPattern, "a9b55844-a55d-4ef0-926d-569c16ff89bb")

.comdef IUIAutomationTransformPattern : public IUnknown

    Move		proc :real8, :real8
    Resize		proc :real8, :real8
    Rotate		proc :real8
    get_CurrentCanMove	proc :ptr
    get_CurrentCanResize proc :ptr
    get_CurrentCanRotate proc :ptr
    get_CachedCanMove	proc :ptr
    get_CachedCanResize proc :ptr
    get_CachedCanRotate proc :ptr
   .ends

endif

ifndef __IUIAutomationValuePattern_INTERFACE_DEFINED__
define __IUIAutomationValuePattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationValuePattern, "a94cd8b1-0844-4cd6-9d2d-640537ab39e9")

.comdef IUIAutomationValuePattern : public IUnknown

    SetValue		proc :BSTR
    get_CurrentValue	proc :ptr
    get_CurrentIsReadOnly proc :ptr
    get_CachedValue	proc :ptr
    get_CachedIsReadOnly proc :ptr
   .ends

endif

ifndef __IUIAutomationWindowPattern_INTERFACE_DEFINED__
define __IUIAutomationWindowPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationWindowPattern, "0faef453-9208-43ef-bbb2-3b485177864f")

.comdef IUIAutomationWindowPattern : public IUnknown

    Close		proc
    WaitForInputIdle	proc :SINT, :ptr
    SetWindowVisualState proc :WindowVisualState
    get_CurrentCanMaximize proc :ptr
    get_CurrentCanMinimize proc :ptr
    get_CurrentIsModal	proc :ptr
    get_CurrentIsTopmost proc :ptr
    get_CurrentWindowVisualState proc :ptr
    get_CurrentWindowInteractionState proc :ptr
    get_CachedCanMaximize proc :ptr
    get_CachedCanMinimize proc :ptr
    get_CachedIsModal	proc :ptr
    get_CachedIsTopmost proc :ptr
    get_CachedWindowVisualState proc :ptr
    get_CachedWindowInteractionState proc :ptr
   .ends

endif

ifndef __IUIAutomationTextRange_INTERFACE_DEFINED__
define __IUIAutomationTextRange_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationTextRange, "a543cc6a-f4ae-494b-8239-c814481187a8")

.comdef IUIAutomationTextRange : public IUnknown

    Clone		proc :ptr
    Compare		proc :ptr, :ptr
    CompareEndpoints	proc :TextPatternRangeEndpoint, :ptr, :TextPatternRangeEndpoint, :ptr
    ExpandToEnclosingUnit proc :TextUnit
    FindAttribute	proc :TEXTATTRIBUTEID, :VARIANT, :BOOL, :ptr
    FindText		proc :BSTR, :BOOL, :BOOL, :ptr
    GetAttributeValue	proc :TEXTATTRIBUTEID, :ptr
    GetBoundingRectangles proc :ptr
    GetEnclosingElement proc :ptr
    GetText		proc :SINT, :ptr
    Move		proc :TextUnit, :SINT, :ptr
    MoveEndpointByUnit	proc :TextPatternRangeEndpoint, :TextUnit, :SINT, :ptr
    MoveEndpointByRange proc :TextPatternRangeEndpoint, :ptr, :TextPatternRangeEndpoint
    Select		proc
    AddToSelection	proc
    RemoveFromSelection proc
    ScrollIntoView	proc :BOOL
    GetChildren		proc :ptr
   .ends

endif

ifndef __IUIAutomationTextRange2_INTERFACE_DEFINED__
define __IUIAutomationTextRange2_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationTextRange2, "BB9B40E0-5E04-46BD-9BE0-4B601B9AFAD4")

.comdef IUIAutomationTextRange2 : public IUnknown

    Clone		proc :ptr
    Compare		proc :ptr, :ptr
    CompareEndpoints	proc :TextPatternRangeEndpoint, :ptr, :TextPatternRangeEndpoint, :ptr
    ExpandToEnclosingUnit proc :TextUnit
    FindAttribute	proc :TEXTATTRIBUTEID, :VARIANT, :BOOL, :ptr
    FindText		proc :BSTR, :BOOL, :BOOL, :ptr
    GetAttributeValue	proc :TEXTATTRIBUTEID, :ptr
    GetBoundingRectangles proc :ptr
    GetEnclosingElement proc :ptr
    GetText		proc :SINT, :ptr
    Move		proc :TextUnit, :SINT, :ptr
    MoveEndpointByUnit	proc :TextPatternRangeEndpoint, :TextUnit, :SINT, :ptr
    MoveEndpointByRange proc :TextPatternRangeEndpoint, :ptr, :TextPatternRangeEndpoint
    Select		proc
    AddToSelection	proc
    RemoveFromSelection proc
    ScrollIntoView	proc :BOOL
    GetChildren		proc :ptr
    ShowContextMenu	proc
   .ends

endif

ifndef __IUIAutomationTextRangeArray_INTERFACE_DEFINED__
define __IUIAutomationTextRangeArray_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationTextRangeArray, "ce4ae76a-e717-4c98-81ea-47371d028eb6")

.comdef IUIAutomationTextRangeArray : public IUnknown

    get_Length		proc :ptr
    GetElement		proc :SINT, :ptr
   .ends

endif

ifndef __IUIAutomationTextPattern_INTERFACE_DEFINED__
define __IUIAutomationTextPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationTextPattern, "32eba289-3583-42c9-9c59-3b6d9a1e9b6a")

.comdef IUIAutomationTextPattern : public IUnknown

    RangeFromPoint	proc :POINT, :ptr
    RangeFromChild	proc :ptr, :ptr
    GetSelection	proc :ptr
    GetVisibleRanges	proc :ptr
    get_DocumentRange	proc :ptr
    get_SupportedTextSelection proc :ptr
   .ends

endif

ifndef __IUIAutomationTextPattern2_INTERFACE_DEFINED__
define __IUIAutomationTextPattern2_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationTextPattern2, "506a921a-fcc9-409f-b23b-37eb74106872")

.comdef IUIAutomationTextPattern2 : public IUnknown

    RangeFromPoint	proc :POINT, :ptr
    RangeFromChild	proc :ptr, :ptr
    GetSelection	proc :ptr
    GetVisibleRanges	proc :ptr
    get_DocumentRange	proc :ptr
    get_SupportedTextSelection proc :ptr
    RangeFromAnnotation proc :ptr, :ptr
    GetCaretRange	proc :ptr, :ptr
   .ends

endif

ifndef __IUIAutomationTextEditPattern_INTERFACE_DEFINED__
define __IUIAutomationTextEditPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationTextEditPattern, "17E21576-996C-4870-99D9-BFF323380C06")

.comdef IUIAutomationTextEditPattern : public IUnknown

    RangeFromPoint	proc :POINT, :ptr
    RangeFromChild	proc :ptr, :ptr
    GetSelection	proc :ptr
    GetVisibleRanges	proc :ptr
    get_DocumentRange	proc :ptr
    get_SupportedTextSelection proc :ptr
    GetActiveComposition proc :ptr
    GetConversionTarget proc :ptr
   .ends

endif

ifndef __IUIAutomationLegacyIAccessiblePattern_INTERFACE_DEFINED__
define __IUIAutomationLegacyIAccessiblePattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationLegacyIAccessiblePattern, "828055ad-355b-4435-86d5-3b51c14a9b1b")

.comdef IUIAutomationLegacyIAccessiblePattern : public IUnknown

    Select		proc :LONG
    DoDefaultAction	proc
    SetValue		proc :LPCWSTR
    get_CurrentChildId	proc :ptr
    get_CurrentName	proc :ptr
    get_CurrentValue	proc :ptr
    get_CurrentDescription proc :ptr
    get_CurrentRole	proc :ptr
    get_CurrentState	proc :ptr
    get_CurrentHelp	proc :ptr
    get_CurrentKeyboardShortcut proc :ptr
    GetCurrentSelection proc :ptr
    get_CurrentDefaultAction proc :ptr
    get_CachedChildId	proc :ptr
    get_CachedName	proc :ptr
    get_CachedValue	proc :ptr
    get_CachedDescription proc :ptr
    get_CachedRole	proc :ptr
    get_CachedState	proc :ptr
    get_CachedHelp	proc :ptr
    get_CachedKeyboardShortcut proc :ptr
    GetCachedSelection	proc :ptr
    get_CachedDefaultAction proc :ptr
    GetIAccessible	proc :ptr
   .ends

endif

ifndef __IUIAutomationItemContainerPattern_INTERFACE_DEFINED__
define __IUIAutomationItemContainerPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationItemContainerPattern, "c690fdb2-27a8-423c-812d-429773c9084e")

.comdef IUIAutomationItemContainerPattern : public IUnknown

    FindItemByProperty	proc :ptr, :PROPERTYID, :VARIANT, :ptr
   .ends

endif

ifndef __IUIAutomationVirtualizedItemPattern_INTERFACE_DEFINED__
define __IUIAutomationVirtualizedItemPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationVirtualizedItemPattern, "6ba3d7a6-04cf-4f11-8793-a8d1cde9969f")

.comdef IUIAutomationVirtualizedItemPattern : public IUnknown

    Realize		proc
   .ends

endif

ifndef __IUIAutomationAnnotationPattern_INTERFACE_DEFINED__
define __IUIAutomationAnnotationPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationAnnotationPattern, "9a175b21-339e-41b1-8e8b-623f6b681098")

.comdef IUIAutomationAnnotationPattern : public IUnknown

    get_CurrentAnnotationTypeId proc :ptr
    get_CurrentAnnotationTypeName proc :ptr
    get_CurrentAuthor	proc :ptr
    get_CurrentDateTime proc :ptr
    get_CurrentTarget	proc :ptr
    get_CachedAnnotationTypeId proc :ptr
    get_CachedAnnotationTypeName proc :ptr
    get_CachedAuthor	proc :ptr
    get_CachedDateTime	proc :ptr
    get_CachedTarget	proc :ptr
   .ends

endif

ifndef __IUIAutomationStylesPattern_INTERFACE_DEFINED__
define __IUIAutomationStylesPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationStylesPattern, "85b5f0a2-bd79-484a-ad2b-388c9838d5fb")

.comdef IUIAutomationStylesPattern : public IUnknown

    get_CurrentStyleId	proc :ptr
    get_CurrentStyleName proc :ptr
    get_CurrentFillColor proc :ptr
    get_CurrentFillPatternStyle proc :ptr
    get_CurrentShape	proc :ptr
    get_CurrentFillPatternColor proc :ptr
    get_CurrentExtendedProperties proc :ptr
    GetCurrentExtendedPropertiesAsArray proc
    get_CachedStyleId	proc :ptr
    get_CachedStyleName proc :ptr
    get_CachedFillColor proc :ptr
    get_CachedFillPatternStyle proc :ptr
    get_CachedShape	proc :ptr
    get_CachedFillPatternColor proc :ptr
    get_CachedExtendedProperties proc :ptr
    GetCachedExtendedPropertiesAsArray proc
   .ends

endif

ifndef __IUIAutomationSpreadsheetPattern_INTERFACE_DEFINED__
define __IUIAutomationSpreadsheetPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationSpreadsheetPattern, "7517a7c8-faae-4de9-9f08-29b91e8595c1")

.comdef IUIAutomationSpreadsheetPattern : public IUnknown

    GetItemByName	proc :BSTR, :ptr
   .ends

endif

ifndef __IUIAutomationSpreadsheetItemPattern_INTERFACE_DEFINED__
define __IUIAutomationSpreadsheetItemPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationSpreadsheetItemPattern, "7d4fb86c-8d34-40e1-8e83-62c15204e335")

.comdef IUIAutomationSpreadsheetItemPattern : public IUnknown

    get_CurrentFormula	proc :ptr
    GetCurrentAnnotationObjects proc :ptr
    GetCurrentAnnotationTypes proc :ptr
    get_CachedFormula	proc :ptr
    GetCachedAnnotationObjects proc :ptr
    GetCachedAnnotationTypes proc :ptr
   .ends

endif

ifndef __IUIAutomationTransformPattern2_INTERFACE_DEFINED__
define __IUIAutomationTransformPattern2_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationTransformPattern2, "6d74d017-6ecb-4381-b38b-3c17a48ff1c2")

.comdef IUIAutomationTransformPattern2 : public IUnknown

    Move		proc :real8, :real8
    Resize		proc :real8, :real8
    Rotate		proc :real8
    get_CurrentCanMove	proc :ptr
    get_CurrentCanResize proc :ptr
    get_CurrentCanRotate proc :ptr
    get_CachedCanMove	proc :ptr
    get_CachedCanResize proc :ptr
    get_CachedCanRotate proc :ptr
    Zoom		proc :real8
    ZoomByUnit		proc :ZoomUnit
    get_CurrentCanZoom	proc :ptr
    get_CachedCanZoom	proc :ptr
    get_CurrentZoomLevel proc :ptr
    get_CachedZoomLevel proc :ptr
    get_CurrentZoomMinimum proc :ptr
    get_CachedZoomMinimum proc :ptr
    get_CurrentZoomMaximum proc :ptr
    get_CachedZoomMaximum proc :ptr
   .ends

endif

ifndef __IUIAutomationTextChildPattern_INTERFACE_DEFINED__
define __IUIAutomationTextChildPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationTextChildPattern, "6552b038-ae05-40c8-abfd-aa08352aab86")

.comdef IUIAutomationTextChildPattern : public IUnknown

    get_TextContainer	proc :ptr
    get_TextRange	proc :ptr
   .ends

endif

ifndef __IUIAutomationDragPattern_INTERFACE_DEFINED__
define __IUIAutomationDragPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationDragPattern, "1dc7b570-1f54-4bad-bcda-d36a722fb7bd")

.comdef IUIAutomationDragPattern : public IUnknown

    get_CurrentIsGrabbed proc :ptr
    get_CachedIsGrabbed proc :ptr
    get_CurrentDropEffect proc :ptr
    get_CachedDropEffect proc :ptr
    get_CurrentDropEffects proc :ptr
    get_CachedDropEffects proc :ptr
    GetCurrentGrabbedItems proc :ptr
    GetCachedGrabbedItems proc :ptr
   .ends

endif

ifndef __IUIAutomationDropTargetPattern_INTERFACE_DEFINED__
define __IUIAutomationDropTargetPattern_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationDropTargetPattern, "69a095f7-eee4-430e-a46b-fb73b1ae39a5")

.comdef IUIAutomationDropTargetPattern : public IUnknown

    get_CurrentDropTargetEffect proc :ptr
    get_CachedDropTargetEffect proc :ptr
    get_CurrentDropTargetEffects proc :ptr
    get_CachedDropTargetEffects proc :ptr
   .ends

endif

ifndef __IUIAutomationElement2_INTERFACE_DEFINED__
define __IUIAutomationElement2_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationElement2, "6749c683-f70d-4487-a698-5f79d55290d6")

.comdef IUIAutomationElement2 : public IUIAutomationElement

    get_CurrentOptimizeForVisualContent proc :ptr
    get_CachedOptimizeForVisualContent proc :ptr
    get_CurrentLiveSetting proc :ptr
    get_CachedLiveSetting proc :ptr
    get_CurrentFlowsFrom proc :ptr
    get_CachedFlowsFrom proc :ptr
   .ends

endif

ifndef __IUIAutomationElement3_INTERFACE_DEFINED__
define __IUIAutomationElement3_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationElement3, "8471DF34-AEE0-4A01-A7DE-7DB9AF12C296")

.comdef IUIAutomationElement3 : public IUIAutomationElement2

    ShowContextMenu	proc
    get_CurrentIsPeripheral proc :ptr
    get_CachedIsPeripheral proc :ptr
   .ends

endif

ifndef __IUIAutomationProxyFactory_INTERFACE_DEFINED__
define __IUIAutomationProxyFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationProxyFactory, "85b94ecd-849d-42b6-b94d-d6db23fdf5a4")

.comdef IUIAutomationProxyFactory : public IUnknown

    CreateProvider	proc :UIA_HWND, :LONG, :LONG, :ptr
    get_ProxyFactoryId	proc :ptr
   .ends

endif

ifndef __IUIAutomationProxyFactoryEntry_INTERFACE_DEFINED__
define __IUIAutomationProxyFactoryEntry_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationProxyFactoryEntry, "d50e472e-b64b-490c-bca1-d30696f9f289")

.comdef IUIAutomationProxyFactoryEntry : public IUnknown

    get_ProxyFactory	proc :ptr
    get_ClassName	proc :ptr
    get_ImageName	proc :ptr
    get_AllowSubstringMatch proc :ptr
    get_CanCheckBaseClass proc :ptr
    get_NeedsAdviseEvents proc :ptr
    put_ClassName	proc :LPCWSTR
    put_ImageName	proc :LPCWSTR
    put_AllowSubstringMatch proc :BOOL
    put_CanCheckBaseClass proc :BOOL
    put_NeedsAdviseEvents proc :BOOL
    SetWinEventsForAutomationEvent proc :EVENTID, :PROPERTYID, :ptr
    GetWinEventsForAutomationEvent proc :EVENTID, :PROPERTYID, :ptr
   .ends

endif

ifndef __IUIAutomationProxyFactoryMapping_INTERFACE_DEFINED__
define __IUIAutomationProxyFactoryMapping_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationProxyFactoryMapping, "09e31e18-872d-4873-93d1-1e541ec133fd")

.comdef IUIAutomationProxyFactoryMapping : public IUnknown

    get_Count		proc :ptr
    GetTable		proc :ptr
    GetEntry		proc :UINT, :ptr
    SetTable		proc :ptr
    InsertEntries	proc :UINT, :ptr
    InsertEntry		proc :UINT, :ptr
    RemoveEntry		proc :UINT
    ClearTable		proc
    RestoreDefaultTable proc
   .ends

endif

ifndef __IUIAutomation_INTERFACE_DEFINED__
define __IUIAutomation_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomation, "30cbe57d-d9d0-452a-ab13-7ac5ac4825ee")

.comdef IUIAutomation : public IUnknown

    CompareElements	proc :ptr, :ptr, :ptr
    CompareRuntimeIds	proc :ptr, :ptr, :ptr
    GetRootElement	proc :ptr
    ElementFromHandle	proc :UIA_HWND, :ptr
    ElementFromPoint	proc :POINT, :ptr
    GetFocusedElement	proc :ptr
    GetRootElementBuildCache proc :ptr, :ptr
    ElementFromHandleBuildCache proc :UIA_HWND, :ptr, :ptr
    ElementFromPointBuildCache proc :POINT, :ptr, :ptr
    GetFocusedElementBuildCache proc :ptr, :ptr
    CreateTreeWalker	proc :ptr, :ptr
    get_ControlViewWalker proc :ptr
    get_ContentViewWalker proc :ptr
    get_RawViewWalker	proc :ptr
    get_RawViewCondition proc :ptr
    get_ControlViewCondition proc :ptr
    get_ContentViewCondition proc :ptr
    CreateCacheRequest	proc :ptr
    CreateTrueCondition proc :ptr
    CreateFalseCondition proc :ptr
    CreatePropertyCondition proc :PROPERTYID, :VARIANT, :ptr
    CreatePropertyConditionEx proc :PROPERTYID, :VARIANT, :PropertyConditionFlags, :ptr
    CreateAndCondition	proc :ptr, :ptr, :ptr
    CreateAndConditionFromArray proc :ptr, :ptr
    CreateAndConditionFromNativeArray proc
    CreateOrCondition	proc :ptr, :ptr, :ptr
    CreateOrConditionFromArray proc :ptr, :ptr
    CreateOrConditionFromNativeArray proc
    CreateNotCondition	proc :ptr, :ptr
    AddAutomationEventHandler proc :EVENTID, :ptr, :TreeScope, :ptr, :ptr
    RemoveAutomationEventHandler proc :EVENTID, :ptr, :ptr
    AddPropertyChangedEventHandlerNativeArray proc :ptr, :TreeScope, :ptr, :ptr
    AddPropertyChangedEventHandler proc :ptr, :TreeScope, :ptr, :ptr, :ptr
    RemovePropertyChangedEventHandler proc :ptr, :ptr
    AddStructureChangedEventHandler proc :ptr, :TreeScope, :ptr, :ptr
    RemoveStructureChangedEventHandler proc :ptr, :ptr
    AddFocusChangedEventHandler proc :ptr, :ptr
    RemoveFocusChangedEventHandler proc :ptr
    RemoveAllEventHandlers proc
    IntNativeArrayToSafeArray proc
    IntSafeArrayToNativeArray proc :ptr
    RectToVariant	proc :RECT, :ptr
    VariantToRect	proc :VARIANT, :ptr
    SafeArrayToRectNativeArray proc :ptr
    CreateProxyFactoryEntry proc :ptr, :ptr
    get_ProxyFactoryMapping proc :ptr
    GetPropertyProgrammaticName proc :PROPERTYID, :ptr
    GetPatternProgrammaticName proc :PATTERNID, :ptr
    PollForPotentialSupportedPatterns proc :ptr, :ptr, :ptr
    PollForPotentialSupportedProperties proc :ptr, :ptr, :ptr
    CheckNotSupported	proc :VARIANT, :ptr
    get_ReservedNotSupportedValue proc :ptr
    get_ReservedMixedAttributeValue proc :ptr
    ElementFromIAccessible proc :ptr, :SINT, :ptr
    ElementFromIAccessibleBuildCache proc :ptr, :SINT, :ptr, :ptr
   .ends

endif

ifndef __IUIAutomation2_INTERFACE_DEFINED__
define __IUIAutomation2_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomation2, "34723aff-0c9d-49d0-9896-7ab52df8cd8a")

.comdef IUIAutomation2 : public IUIAutomation

    get_AutoSetFocus	proc :ptr
    put_AutoSetFocus	proc :BOOL
    get_ConnectionTimeout proc :ptr
    put_ConnectionTimeout proc :DWORD
    get_TransactionTimeout proc :ptr
    put_TransactionTimeout proc :DWORD
   .ends

endif

ifndef __IUIAutomation3_INTERFACE_DEFINED__
define __IUIAutomation3_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomation3, "73D768DA-9B51-4B89-936E-C209290973E7")

.comdef IUIAutomation3 : public IUIAutomation2

    AddTextEditTextChangedEventHandler proc :ptr, :TreeScope, :TextEditChangeType, :ptr, :ptr
    RemoveTextEditTextChangedEventHandler proc :ptr, :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_CUIAutomation, "ff48dba4-60ef-4201-aa87-54103eef594e")
DEFINE_GUIDS(CLSID_CUIAutomation8, "e22ad333-b25f-460c-83d0-0581107395c9")

endif
endif
endif
