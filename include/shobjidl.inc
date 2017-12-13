ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif
include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
 .err <this stub requires an updated version of rpcndr>
endif
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif
ifndef __shobjidl_h__
__shobjidl_h__ equ 1
.xlist

ifndef __IContextMenu_FWD_DEFINED__
__IContextMenu_FWD_DEFINED__ equ 1
endif
ifndef __IContextMenu2_FWD_DEFINED__
__IContextMenu2_FWD_DEFINED__ equ 1
endif
ifndef __IContextMenu3_FWD_DEFINED__
__IContextMenu3_FWD_DEFINED__ equ 1
endif
ifndef __IExecuteCommand_FWD_DEFINED__
__IExecuteCommand_FWD_DEFINED__ equ 1
endif
ifndef __IPersistFolder_FWD_DEFINED__
__IPersistFolder_FWD_DEFINED__ equ 1
endif
ifndef __IRunnableTask_FWD_DEFINED__
__IRunnableTask_FWD_DEFINED__ equ 1
endif
ifndef __IShellTaskScheduler_FWD_DEFINED__
__IShellTaskScheduler_FWD_DEFINED__ equ 1
endif
ifndef __IQueryCodePage_FWD_DEFINED__
__IQueryCodePage_FWD_DEFINED__ equ 1
endif
ifndef __IPersistFolder2_FWD_DEFINED__
__IPersistFolder2_FWD_DEFINED__ equ 1
endif
ifndef __IPersistFolder3_FWD_DEFINED__
__IPersistFolder3_FWD_DEFINED__ equ 1
endif
ifndef __IPersistIDList_FWD_DEFINED__
__IPersistIDList_FWD_DEFINED__ equ 1
endif
ifndef __IEnumIDList_FWD_DEFINED__
__IEnumIDList_FWD_DEFINED__ equ 1
endif
ifndef __IEnumFullIDList_FWD_DEFINED__
__IEnumFullIDList_FWD_DEFINED__ equ 1
endif
ifndef __IObjectWithFolderEnumMode_FWD_DEFINED__
__IObjectWithFolderEnumMode_FWD_DEFINED__ equ 1
endif
ifndef __IParseAndCreateItem_FWD_DEFINED__
__IParseAndCreateItem_FWD_DEFINED__ equ 1
endif
ifndef __IShellFolder_FWD_DEFINED__
__IShellFolder_FWD_DEFINED__ equ 1
endif
ifndef __IEnumExtraSearch_FWD_DEFINED__
__IEnumExtraSearch_FWD_DEFINED__ equ 1
endif
ifndef __IShellFolder2_FWD_DEFINED__
__IShellFolder2_FWD_DEFINED__ equ 1
endif
ifndef __IFolderViewOptions_FWD_DEFINED__
__IFolderViewOptions_FWD_DEFINED__ equ 1
endif
ifndef __IShellView_FWD_DEFINED__
__IShellView_FWD_DEFINED__ equ 1
endif
ifndef __IShellView2_FWD_DEFINED__
__IShellView2_FWD_DEFINED__ equ 1
endif
ifndef __IShellView3_FWD_DEFINED__
__IShellView3_FWD_DEFINED__ equ 1
endif
ifndef __IFolderView_FWD_DEFINED__
__IFolderView_FWD_DEFINED__ equ 1
endif
ifndef __ISearchBoxInfo_FWD_DEFINED__
__ISearchBoxInfo_FWD_DEFINED__ equ 1
endif
ifndef __IFolderView2_FWD_DEFINED__
__IFolderView2_FWD_DEFINED__ equ 1
endif
ifndef __IFolderViewSettings_FWD_DEFINED__
__IFolderViewSettings_FWD_DEFINED__ equ 1
endif
ifndef __IPreviewHandlerVisuals_FWD_DEFINED__
__IPreviewHandlerVisuals_FWD_DEFINED__ equ 1
endif
ifndef __IVisualProperties_FWD_DEFINED__
__IVisualProperties_FWD_DEFINED__ equ 1
endif
ifndef __ICommDlgBrowser_FWD_DEFINED__
__ICommDlgBrowser_FWD_DEFINED__ equ 1
endif
ifndef __ICommDlgBrowser2_FWD_DEFINED__
__ICommDlgBrowser2_FWD_DEFINED__ equ 1
endif
ifndef __ICommDlgBrowser3_FWD_DEFINED__
__ICommDlgBrowser3_FWD_DEFINED__ equ 1
endif
ifndef __IColumnManager_FWD_DEFINED__
__IColumnManager_FWD_DEFINED__ equ 1
endif
ifndef __IFolderFilterSite_FWD_DEFINED__
__IFolderFilterSite_FWD_DEFINED__ equ 1
endif
ifndef __IFolderFilter_FWD_DEFINED__
__IFolderFilter_FWD_DEFINED__ equ 1
endif
ifndef __IInputObjectSite_FWD_DEFINED__
__IInputObjectSite_FWD_DEFINED__ equ 1
endif
ifndef __IInputObject_FWD_DEFINED__
__IInputObject_FWD_DEFINED__ equ 1
endif
ifndef __IInputObject2_FWD_DEFINED__
__IInputObject2_FWD_DEFINED__ equ 1
endif
ifndef __IShellIcon_FWD_DEFINED__
__IShellIcon_FWD_DEFINED__ equ 1
endif
ifndef __IShellBrowser_FWD_DEFINED__
__IShellBrowser_FWD_DEFINED__ equ 1
endif
ifndef __IProfferService_FWD_DEFINED__
__IProfferService_FWD_DEFINED__ equ 1
endif
ifndef __IShellItem_FWD_DEFINED__
__IShellItem_FWD_DEFINED__ equ 1
endif
ifndef __IShellItem2_FWD_DEFINED__
__IShellItem2_FWD_DEFINED__ equ 1
endif
ifndef __IShellItemImageFactory_FWD_DEFINED__
__IShellItemImageFactory_FWD_DEFINED__ equ 1
endif
ifndef __IUserAccountChangeCallback_FWD_DEFINED__
__IUserAccountChangeCallback_FWD_DEFINED__ equ 1
endif
ifndef __IEnumShellItems_FWD_DEFINED__
__IEnumShellItems_FWD_DEFINED__ equ 1
endif
ifndef __ITransferAdviseSink_FWD_DEFINED__
__ITransferAdviseSink_FWD_DEFINED__ equ 1
endif
ifndef __ITransferSource_FWD_DEFINED__
__ITransferSource_FWD_DEFINED__ equ 1
endif
ifndef __IEnumResources_FWD_DEFINED__
__IEnumResources_FWD_DEFINED__ equ 1
endif
ifndef __IShellItemResources_FWD_DEFINED__
__IShellItemResources_FWD_DEFINED__ equ 1
endif
ifndef __ITransferDestination_FWD_DEFINED__
__ITransferDestination_FWD_DEFINED__ equ 1
endif
ifndef __IStreamAsync_FWD_DEFINED__
__IStreamAsync_FWD_DEFINED__ equ 1
endif
ifndef __IStreamUnbufferedInfo_FWD_DEFINED__
__IStreamUnbufferedInfo_FWD_DEFINED__ equ 1
endif
ifndef __IFileOperationProgressSink_FWD_DEFINED__
__IFileOperationProgressSink_FWD_DEFINED__ equ 1
endif
ifndef __IShellItemArray_FWD_DEFINED__
__IShellItemArray_FWD_DEFINED__ equ 1
endif
ifndef __IInitializeWithItem_FWD_DEFINED__
__IInitializeWithItem_FWD_DEFINED__ equ 1
endif
ifndef __IObjectWithSelection_FWD_DEFINED__
__IObjectWithSelection_FWD_DEFINED__ equ 1
endif
ifndef __IObjectWithBackReferences_FWD_DEFINED__
__IObjectWithBackReferences_FWD_DEFINED__ equ 1
endif
ifndef __IPropertyUI_FWD_DEFINED__
__IPropertyUI_FWD_DEFINED__ equ 1
endif
ifndef __ICategoryProvider_FWD_DEFINED__
__ICategoryProvider_FWD_DEFINED__ equ 1
endif
ifndef __ICategorizer_FWD_DEFINED__
__ICategorizer_FWD_DEFINED__ equ 1
endif
ifndef __IDropTargetHelper_FWD_DEFINED__
__IDropTargetHelper_FWD_DEFINED__ equ 1
endif
ifndef __IDragSourceHelper_FWD_DEFINED__
__IDragSourceHelper_FWD_DEFINED__ equ 1
endif
ifndef __IDragSourceHelper2_FWD_DEFINED__
__IDragSourceHelper2_FWD_DEFINED__ equ 1
endif
ifndef __IShellLinkA_FWD_DEFINED__
__IShellLinkA_FWD_DEFINED__ equ 1
endif
ifndef __IShellLinkW_FWD_DEFINED__
__IShellLinkW_FWD_DEFINED__ equ 1
endif
ifndef __IShellLinkDataList_FWD_DEFINED__
__IShellLinkDataList_FWD_DEFINED__ equ 1
endif
ifndef __IResolveShellLink_FWD_DEFINED__
__IResolveShellLink_FWD_DEFINED__ equ 1
endif
ifndef __IActionProgressDialog_FWD_DEFINED__
__IActionProgressDialog_FWD_DEFINED__ equ 1
endif
ifndef __IHWEventHandler_FWD_DEFINED__
__IHWEventHandler_FWD_DEFINED__ equ 1
endif
ifndef __IHWEventHandler2_FWD_DEFINED__
__IHWEventHandler2_FWD_DEFINED__ equ 1
endif
ifndef __IQueryCancelAutoPlay_FWD_DEFINED__
__IQueryCancelAutoPlay_FWD_DEFINED__ equ 1
endif
ifndef __IDynamicHWHandler_FWD_DEFINED__
__IDynamicHWHandler_FWD_DEFINED__ equ 1
endif
ifndef __IActionProgress_FWD_DEFINED__
__IActionProgress_FWD_DEFINED__ equ 1
endif
ifndef __IShellExtInit_FWD_DEFINED__
__IShellExtInit_FWD_DEFINED__ equ 1
endif
ifndef __IShellPropSheetExt_FWD_DEFINED__
__IShellPropSheetExt_FWD_DEFINED__ equ 1
endif
ifndef __IRemoteComputer_FWD_DEFINED__
__IRemoteComputer_FWD_DEFINED__ equ 1
endif
ifndef __IQueryContinue_FWD_DEFINED__
__IQueryContinue_FWD_DEFINED__ equ 1
endif
ifndef __IObjectWithCancelEvent_FWD_DEFINED__
__IObjectWithCancelEvent_FWD_DEFINED__ equ 1
endif
ifndef __IUserNotification_FWD_DEFINED__
__IUserNotification_FWD_DEFINED__ equ 1
endif
ifndef __IUserNotificationCallback_FWD_DEFINED__
__IUserNotificationCallback_FWD_DEFINED__ equ 1
endif
ifndef __IUserNotification2_FWD_DEFINED__
__IUserNotification2_FWD_DEFINED__ equ 1
endif
ifndef __IItemNameLimits_FWD_DEFINED__
__IItemNameLimits_FWD_DEFINED__ equ 1
endif
ifndef __ISearchFolderItemFactory_FWD_DEFINED__
__ISearchFolderItemFactory_FWD_DEFINED__ equ 1
endif
ifndef __IExtractImage_FWD_DEFINED__
__IExtractImage_FWD_DEFINED__ equ 1
endif
ifndef __IExtractImage2_FWD_DEFINED__
__IExtractImage2_FWD_DEFINED__ equ 1
endif
ifndef __IThumbnailHandlerFactory_FWD_DEFINED__
__IThumbnailHandlerFactory_FWD_DEFINED__ equ 1
endif
ifndef __IParentAndItem_FWD_DEFINED__
__IParentAndItem_FWD_DEFINED__ equ 1
endif
ifndef __IDockingWindow_FWD_DEFINED__
__IDockingWindow_FWD_DEFINED__ equ 1
endif
ifndef __IDeskBand_FWD_DEFINED__
__IDeskBand_FWD_DEFINED__ equ 1
endif
ifndef __IDeskBandInfo_FWD_DEFINED__
__IDeskBandInfo_FWD_DEFINED__ equ 1
endif
ifndef __IDeskBand2_FWD_DEFINED__
__IDeskBand2_FWD_DEFINED__ equ 1
endif
ifndef __ITaskbarList_FWD_DEFINED__
__ITaskbarList_FWD_DEFINED__ equ 1
endif
ifndef __ITaskbarList2_FWD_DEFINED__
__ITaskbarList2_FWD_DEFINED__ equ 1
endif
ifndef __ITaskbarList3_FWD_DEFINED__
__ITaskbarList3_FWD_DEFINED__ equ 1
endif
ifndef __ITaskbarList4_FWD_DEFINED__
__ITaskbarList4_FWD_DEFINED__ equ 1
endif
ifndef __IStartMenuPinnedList_FWD_DEFINED__
__IStartMenuPinnedList_FWD_DEFINED__ equ 1
endif
ifndef __ICDBurn_FWD_DEFINED__
__ICDBurn_FWD_DEFINED__ equ 1
endif
ifndef __IWizardSite_FWD_DEFINED__
__IWizardSite_FWD_DEFINED__ equ 1
endif
ifndef __IWizardExtension_FWD_DEFINED__
__IWizardExtension_FWD_DEFINED__ equ 1
endif
ifndef __IWebWizardExtension_FWD_DEFINED__
__IWebWizardExtension_FWD_DEFINED__ equ 1
endif
ifndef __IPublishingWizard_FWD_DEFINED__
__IPublishingWizard_FWD_DEFINED__ equ 1
endif
ifndef __IFolderViewHost_FWD_DEFINED__
__IFolderViewHost_FWD_DEFINED__ equ 1
endif
ifndef __IExplorerBrowserEvents_FWD_DEFINED__
__IExplorerBrowserEvents_FWD_DEFINED__ equ 1
endif
ifndef __IExplorerBrowser_FWD_DEFINED__
__IExplorerBrowser_FWD_DEFINED__ equ 1
endif
ifndef __IAccessibleObject_FWD_DEFINED__
__IAccessibleObject_FWD_DEFINED__ equ 1
endif
ifndef __IResultsFolder_FWD_DEFINED__
__IResultsFolder_FWD_DEFINED__ equ 1
endif
ifndef __IEnumObjects_FWD_DEFINED__
__IEnumObjects_FWD_DEFINED__ equ 1
endif
ifndef __IOperationsProgressDialog_FWD_DEFINED__
__IOperationsProgressDialog_FWD_DEFINED__ equ 1
endif
ifndef __IIOCancelInformation_FWD_DEFINED__
__IIOCancelInformation_FWD_DEFINED__ equ 1
endif
ifndef __IFileOperation_FWD_DEFINED__
__IFileOperation_FWD_DEFINED__ equ 1
endif
ifndef __IObjectProvider_FWD_DEFINED__
__IObjectProvider_FWD_DEFINED__ equ 1
endif
ifndef __INamespaceWalkCB_FWD_DEFINED__
__INamespaceWalkCB_FWD_DEFINED__ equ 1
endif
ifndef __INamespaceWalkCB2_FWD_DEFINED__
__INamespaceWalkCB2_FWD_DEFINED__ equ 1
endif
ifndef __INamespaceWalk_FWD_DEFINED__
__INamespaceWalk_FWD_DEFINED__ equ 1
endif
ifndef __IAutoCompleteDropDown_FWD_DEFINED__
__IAutoCompleteDropDown_FWD_DEFINED__ equ 1
endif
ifndef __IBandSite_FWD_DEFINED__
__IBandSite_FWD_DEFINED__ equ 1
endif
ifndef __IModalWindow_FWD_DEFINED__
__IModalWindow_FWD_DEFINED__ equ 1
endif
ifndef __ICDBurnExt_FWD_DEFINED__
__ICDBurnExt_FWD_DEFINED__ equ 1
endif
ifndef __IContextMenuSite_FWD_DEFINED__
__IContextMenuSite_FWD_DEFINED__ equ 1
endif
ifndef __IEnumReadyCallback_FWD_DEFINED__
__IEnumReadyCallback_FWD_DEFINED__ equ 1
endif
ifndef __IEnumerableView_FWD_DEFINED__
__IEnumerableView_FWD_DEFINED__ equ 1
endif
ifndef __IInsertItem_FWD_DEFINED__
__IInsertItem_FWD_DEFINED__ equ 1
endif
ifndef __IMenuBand_FWD_DEFINED__
__IMenuBand_FWD_DEFINED__ equ 1
endif
ifndef __IFolderBandPriv_FWD_DEFINED__
__IFolderBandPriv_FWD_DEFINED__ equ 1
endif
ifndef __IRegTreeItem_FWD_DEFINED__
__IRegTreeItem_FWD_DEFINED__ equ 1
endif
ifndef __IImageRecompress_FWD_DEFINED__
__IImageRecompress_FWD_DEFINED__ equ 1
endif
ifndef __IDeskBar_FWD_DEFINED__
__IDeskBar_FWD_DEFINED__ equ 1
endif
ifndef __IMenuPopup_FWD_DEFINED__
__IMenuPopup_FWD_DEFINED__ equ 1
endif
ifndef __IFileIsInUse_FWD_DEFINED__
__IFileIsInUse_FWD_DEFINED__ equ 1
endif
ifndef __IFileDialogEvents_FWD_DEFINED__
__IFileDialogEvents_FWD_DEFINED__ equ 1
endif
ifndef __IFileDialog_FWD_DEFINED__
__IFileDialog_FWD_DEFINED__ equ 1
endif
ifndef __IFileSaveDialog_FWD_DEFINED__
__IFileSaveDialog_FWD_DEFINED__ equ 1
endif
ifndef __IFileOpenDialog_FWD_DEFINED__
__IFileOpenDialog_FWD_DEFINED__ equ 1
endif
ifndef __IFileDialogCustomize_FWD_DEFINED__
__IFileDialogCustomize_FWD_DEFINED__ equ 1
endif
ifndef __IFileDialogControlEvents_FWD_DEFINED__
__IFileDialogControlEvents_FWD_DEFINED__ equ 1
endif
ifndef __IFileDialog2_FWD_DEFINED__
__IFileDialog2_FWD_DEFINED__ equ 1
endif
ifndef __IApplicationAssociationRegistration_FWD_DEFINED__
__IApplicationAssociationRegistration_FWD_DEFINED__ equ 1
endif
ifndef __IApplicationAssociationRegistrationUI_FWD_DEFINED__
__IApplicationAssociationRegistrationUI_FWD_DEFINED__ equ 1
endif
ifndef __IDelegateFolder_FWD_DEFINED__
__IDelegateFolder_FWD_DEFINED__ equ 1
endif
ifndef __IBrowserFrameOptions_FWD_DEFINED__
__IBrowserFrameOptions_FWD_DEFINED__ equ 1
endif
ifndef __INewWindowManager_FWD_DEFINED__
__INewWindowManager_FWD_DEFINED__ equ 1
endif
ifndef __IAttachmentExecute_FWD_DEFINED__
__IAttachmentExecute_FWD_DEFINED__ equ 1
endif
ifndef __IShellMenuCallback_FWD_DEFINED__
__IShellMenuCallback_FWD_DEFINED__ equ 1
endif
ifndef __IShellMenu_FWD_DEFINED__
__IShellMenu_FWD_DEFINED__ equ 1
endif
ifndef __IShellRunDll_FWD_DEFINED__
__IShellRunDll_FWD_DEFINED__ equ 1
endif
ifndef __IKnownFolder_FWD_DEFINED__
__IKnownFolder_FWD_DEFINED__ equ 1
endif
ifndef __IKnownFolderManager_FWD_DEFINED__
__IKnownFolderManager_FWD_DEFINED__ equ 1
endif
ifndef __ISharingConfigurationManager_FWD_DEFINED__
__ISharingConfigurationManager_FWD_DEFINED__ equ 1
endif
ifndef __IPreviousVersionsInfo_FWD_DEFINED__
__IPreviousVersionsInfo_FWD_DEFINED__ equ 1
endif
ifndef __IRelatedItem_FWD_DEFINED__
__IRelatedItem_FWD_DEFINED__ equ 1
endif
ifndef __IIdentityName_FWD_DEFINED__
__IIdentityName_FWD_DEFINED__ equ 1
endif
ifndef __IDelegateItem_FWD_DEFINED__
__IDelegateItem_FWD_DEFINED__ equ 1
endif
ifndef __ICurrentItem_FWD_DEFINED__
__ICurrentItem_FWD_DEFINED__ equ 1
endif
ifndef __ITransferMediumItem_FWD_DEFINED__
__ITransferMediumItem_FWD_DEFINED__ equ 1
endif
ifndef __IUseToBrowseItem_FWD_DEFINED__
__IUseToBrowseItem_FWD_DEFINED__ equ 1
endif
ifndef __IDisplayItem_FWD_DEFINED__
__IDisplayItem_FWD_DEFINED__ equ 1
endif
ifndef __IViewStateIdentityItem_FWD_DEFINED__
__IViewStateIdentityItem_FWD_DEFINED__ equ 1
endif
ifndef __IPreviewItem_FWD_DEFINED__
__IPreviewItem_FWD_DEFINED__ equ 1
endif
ifndef __IDestinationStreamFactory_FWD_DEFINED__
__IDestinationStreamFactory_FWD_DEFINED__ equ 1
endif
ifndef __INewMenuClient_FWD_DEFINED__
__INewMenuClient_FWD_DEFINED__ equ 1
endif
ifndef __IInitializeWithBindCtx_FWD_DEFINED__
__IInitializeWithBindCtx_FWD_DEFINED__ equ 1
endif
ifndef __IShellItemFilter_FWD_DEFINED__
__IShellItemFilter_FWD_DEFINED__ equ 1
endif
ifndef __INameSpaceTreeControl_FWD_DEFINED__
__INameSpaceTreeControl_FWD_DEFINED__ equ 1
endif
ifndef __INameSpaceTreeControl2_FWD_DEFINED__
__INameSpaceTreeControl2_FWD_DEFINED__ equ 1
endif
ifndef __INameSpaceTreeControlEvents_FWD_DEFINED__
__INameSpaceTreeControlEvents_FWD_DEFINED__ equ 1
endif
ifndef __INameSpaceTreeControlDropHandler_FWD_DEFINED__
__INameSpaceTreeControlDropHandler_FWD_DEFINED__ equ 1
endif
ifndef __INameSpaceTreeAccessible_FWD_DEFINED__
__INameSpaceTreeAccessible_FWD_DEFINED__ equ 1
endif
ifndef __INameSpaceTreeControlCustomDraw_FWD_DEFINED__
__INameSpaceTreeControlCustomDraw_FWD_DEFINED__ equ 1
endif
ifndef __INameSpaceTreeControlFolderCapabilities_FWD_DEFINED__
__INameSpaceTreeControlFolderCapabilities_FWD_DEFINED__ equ 1
endif
ifndef __IPreviewHandler_FWD_DEFINED__
__IPreviewHandler_FWD_DEFINED__ equ 1
endif
ifndef __IPreviewHandlerFrame_FWD_DEFINED__
__IPreviewHandlerFrame_FWD_DEFINED__ equ 1
endif
ifndef __ITrayDeskBand_FWD_DEFINED__
__ITrayDeskBand_FWD_DEFINED__ equ 1
endif
ifndef __IBandHost_FWD_DEFINED__
__IBandHost_FWD_DEFINED__ equ 1
endif
ifndef __IExplorerPaneVisibility_FWD_DEFINED__
__IExplorerPaneVisibility_FWD_DEFINED__ equ 1
endif
ifndef __IContextMenuCB_FWD_DEFINED__
__IContextMenuCB_FWD_DEFINED__ equ 1
endif
ifndef __IDefaultExtractIconInit_FWD_DEFINED__
__IDefaultExtractIconInit_FWD_DEFINED__ equ 1
endif
ifndef __IExplorerCommand_FWD_DEFINED__
__IExplorerCommand_FWD_DEFINED__ equ 1
endif
ifndef __IExplorerCommandState_FWD_DEFINED__
__IExplorerCommandState_FWD_DEFINED__ equ 1
endif
ifndef __IInitializeCommand_FWD_DEFINED__
__IInitializeCommand_FWD_DEFINED__ equ 1
endif
ifndef __IEnumExplorerCommand_FWD_DEFINED__
__IEnumExplorerCommand_FWD_DEFINED__ equ 1
endif
ifndef __IExplorerCommandProvider_FWD_DEFINED__
__IExplorerCommandProvider_FWD_DEFINED__ equ 1
endif
ifndef __IMarkupCallback_FWD_DEFINED__
__IMarkupCallback_FWD_DEFINED__ equ 1
endif
ifndef __IControlMarkup_FWD_DEFINED__
__IControlMarkup_FWD_DEFINED__ equ 1
endif
ifndef __IInitializeNetworkFolder_FWD_DEFINED__
__IInitializeNetworkFolder_FWD_DEFINED__ equ 1
endif
ifndef __IOpenControlPanel_FWD_DEFINED__
__IOpenControlPanel_FWD_DEFINED__ equ 1
endif
ifndef __IComputerInfoChangeNotify_FWD_DEFINED__
__IComputerInfoChangeNotify_FWD_DEFINED__ equ 1
endif
ifndef __IFileSystemBindData_FWD_DEFINED__
__IFileSystemBindData_FWD_DEFINED__ equ 1
endif
ifndef __IFileSystemBindData2_FWD_DEFINED__
__IFileSystemBindData2_FWD_DEFINED__ equ 1
endif
ifndef __ICustomDestinationList_FWD_DEFINED__
__ICustomDestinationList_FWD_DEFINED__ equ 1
endif
ifndef __IApplicationDestinations_FWD_DEFINED__
__IApplicationDestinations_FWD_DEFINED__ equ 1
endif
ifndef __IApplicationDocumentLists_FWD_DEFINED__
__IApplicationDocumentLists_FWD_DEFINED__ equ 1
endif
ifndef __IObjectWithAppUserModelID_FWD_DEFINED__
__IObjectWithAppUserModelID_FWD_DEFINED__ equ 1
endif
ifndef __IObjectWithProgID_FWD_DEFINED__
__IObjectWithProgID_FWD_DEFINED__ equ 1
endif
ifndef __IUpdateIDList_FWD_DEFINED__
__IUpdateIDList_FWD_DEFINED__ equ 1
endif
ifndef __IDesktopGadget_FWD_DEFINED__
__IDesktopGadget_FWD_DEFINED__ equ 1
endif
ifndef __IHomeGroup_FWD_DEFINED__
__IHomeGroup_FWD_DEFINED__ equ 1
endif
ifndef __IInitializeWithPropertyStore_FWD_DEFINED__
__IInitializeWithPropertyStore_FWD_DEFINED__ equ 1
endif
ifndef __IOpenSearchSource_FWD_DEFINED__
__IOpenSearchSource_FWD_DEFINED__ equ 1
endif
ifndef __IShellLibrary_FWD_DEFINED__
__IShellLibrary_FWD_DEFINED__ equ 1
endif
ifndef __ShellDesktop_FWD_DEFINED__
__ShellDesktop_FWD_DEFINED__ equ 1
ShellDesktop		typedef ShellDesktop
endif
ifndef __ShellFSFolder_FWD_DEFINED__
__ShellFSFolder_FWD_DEFINED__ equ 1
ShellFSFolder		typedef ShellFSFolder
endif
ifndef __NetworkPlaces_FWD_DEFINED__
__NetworkPlaces_FWD_DEFINED__ equ 1
NetworkPlaces		typedef NetworkPlaces
endif
ifndef __ShellLink_FWD_DEFINED__
__ShellLink_FWD_DEFINED__ equ 1
ShellLink		typedef ShellLink
endif
ifndef __QueryCancelAutoPlay_FWD_DEFINED__
__QueryCancelAutoPlay_FWD_DEFINED__ equ 1
QueryCancelAutoPlay	typedef QueryCancelAutoPlay
endif
ifndef __DriveSizeCategorizer_FWD_DEFINED__
__DriveSizeCategorizer_FWD_DEFINED__ equ 1
DriveSizeCategorizer	typedef DriveSizeCategorizer
endif
ifndef __DriveTypeCategorizer_FWD_DEFINED__
__DriveTypeCategorizer_FWD_DEFINED__ equ 1
DriveTypeCategorizer	typedef DriveTypeCategorizer
endif
ifndef __FreeSpaceCategorizer_FWD_DEFINED__
__FreeSpaceCategorizer_FWD_DEFINED__ equ 1
FreeSpaceCategorizer	typedef FreeSpaceCategorizer
endif
ifndef __TimeCategorizer_FWD_DEFINED__
__TimeCategorizer_FWD_DEFINED__ equ 1
TimeCategorizer		typedef TimeCategorizer
endif
ifndef __SizeCategorizer_FWD_DEFINED__
__SizeCategorizer_FWD_DEFINED__ equ 1
SizeCategorizer		typedef SizeCategorizer
endif
ifndef __AlphabeticalCategorizer_FWD_DEFINED__
__AlphabeticalCategorizer_FWD_DEFINED__ equ 1
AlphabeticalCategorizer typedef AlphabeticalCategorizer
endif
ifndef __MergedCategorizer_FWD_DEFINED__
__MergedCategorizer_FWD_DEFINED__ equ 1
MergedCategorizer	typedef MergedCategorizer
endif
ifndef __ImageProperties_FWD_DEFINED__
__ImageProperties_FWD_DEFINED__ equ 1
ImageProperties		typedef ImageProperties
endif
ifndef __PropertiesUI_FWD_DEFINED__
__PropertiesUI_FWD_DEFINED__ equ 1
PropertiesUI		typedef PropertiesUI
endif
ifndef __UserNotification_FWD_DEFINED__
__UserNotification_FWD_DEFINED__ equ 1
UserNotification	typedef UserNotification
endif
ifndef __CDBurn_FWD_DEFINED__
__CDBurn_FWD_DEFINED__ equ 1
CDBurn			typedef CDBurn
endif
ifndef __TaskbarList_FWD_DEFINED__
__TaskbarList_FWD_DEFINED__ equ 1
TaskbarList		typedef TaskbarList
endif
ifndef __StartMenuPin_FWD_DEFINED__
__StartMenuPin_FWD_DEFINED__ equ 1
StartMenuPin		typedef StartMenuPin
endif
ifndef __WebWizardHost_FWD_DEFINED__
__WebWizardHost_FWD_DEFINED__ equ 1
WebWizardHost		typedef WebWizardHost
endif
ifndef __PublishDropTarget_FWD_DEFINED__
__PublishDropTarget_FWD_DEFINED__ equ 1
PublishDropTarget	typedef PublishDropTarget
endif
ifndef __PublishingWizard_FWD_DEFINED__
__PublishingWizard_FWD_DEFINED__ equ 1
PublishingWizard	typedef PublishingWizard
endif
ifndef __InternetPrintOrdering_FWD_DEFINED__
__InternetPrintOrdering_FWD_DEFINED__ equ 1
InternetPrintOrdering	typedef InternetPrintOrdering
endif
ifndef __FolderViewHost_FWD_DEFINED__
__FolderViewHost_FWD_DEFINED__ equ 1
FolderViewHost		typedef FolderViewHost
endif
ifndef __ExplorerBrowser_FWD_DEFINED__
__ExplorerBrowser_FWD_DEFINED__ equ 1
ExplorerBrowser		typedef ExplorerBrowser
endif
ifndef __ImageRecompress_FWD_DEFINED__
__ImageRecompress_FWD_DEFINED__ equ 1
ImageRecompress		typedef ImageRecompress
endif
ifndef __TrayBandSiteService_FWD_DEFINED__
__TrayBandSiteService_FWD_DEFINED__ equ 1
TrayBandSiteService	typedef TrayBandSiteService
endif
ifndef __TrayDeskBand_FWD_DEFINED__
__TrayDeskBand_FWD_DEFINED__ equ 1
TrayDeskBand		typedef TrayDeskBand
endif
ifndef __AttachmentServices_FWD_DEFINED__
__AttachmentServices_FWD_DEFINED__ equ 1
AttachmentServices	typedef AttachmentServices
endif
ifndef __DocPropShellExtension_FWD_DEFINED__
__DocPropShellExtension_FWD_DEFINED__ equ 1
DocPropShellExtension	typedef DocPropShellExtension
endif
ifndef __ShellItem_FWD_DEFINED__
__ShellItem_FWD_DEFINED__ equ 1
ShellItem		typedef ShellItem
endif
ifndef __NamespaceWalker_FWD_DEFINED__
__NamespaceWalker_FWD_DEFINED__ equ 1
NamespaceWalker		typedef NamespaceWalker
endif
ifndef __FileOperation_FWD_DEFINED__
__FileOperation_FWD_DEFINED__ equ 1
FileOperation		typedef FileOperation
endif
ifndef __FileOpenDialog_FWD_DEFINED__
__FileOpenDialog_FWD_DEFINED__ equ 1
FileOpenDialog		typedef FileOpenDialog
endif
ifndef __FileSaveDialog_FWD_DEFINED__
__FileSaveDialog_FWD_DEFINED__ equ 1
FileSaveDialog		typedef FileSaveDialog
endif
ifndef __KnownFolderManager_FWD_DEFINED__
__KnownFolderManager_FWD_DEFINED__ equ 1
KnownFolderManager	typedef KnownFolderManager
endif
ifndef __FSCopyHandler_FWD_DEFINED__
__FSCopyHandler_FWD_DEFINED__ equ 1
FSCopyHandler		typedef FSCopyHandler
endif
ifndef __SharingConfigurationManager_FWD_DEFINED__
__SharingConfigurationManager_FWD_DEFINED__ equ 1
SharingConfigurationManager typedef SharingConfigurationManager
endif
ifndef __PreviousVersions_FWD_DEFINED__
__PreviousVersions_FWD_DEFINED__ equ 1
PreviousVersions	typedef PreviousVersions
endif
ifndef __NetworkConnections_FWD_DEFINED__
__NetworkConnections_FWD_DEFINED__ equ 1
NetworkConnections	typedef NetworkConnections
endif
ifndef __NamespaceTreeControl_FWD_DEFINED__
__NamespaceTreeControl_FWD_DEFINED__ equ 1
NamespaceTreeControl	typedef NamespaceTreeControl
endif
ifndef __IENamespaceTreeControl_FWD_DEFINED__
__IENamespaceTreeControl_FWD_DEFINED__ equ 1
IENamespaceTreeControl	typedef IENamespaceTreeControl
endif
ifndef __ScheduledTasks_FWD_DEFINED__
__ScheduledTasks_FWD_DEFINED__ equ 1
ScheduledTasks		typedef ScheduledTasks
endif
ifndef __ApplicationAssociationRegistration_FWD_DEFINED__
__ApplicationAssociationRegistration_FWD_DEFINED__ equ 1
ApplicationAssociationRegistration typedef ApplicationAssociationRegistration
endif
ifndef __ApplicationAssociationRegistrationUI_FWD_DEFINED__
__ApplicationAssociationRegistrationUI_FWD_DEFINED__ equ 1
ApplicationAssociationRegistrationUI typedef ApplicationAssociationRegistrationUI
endif
ifndef __SearchFolderItemFactory_FWD_DEFINED__
__SearchFolderItemFactory_FWD_DEFINED__ equ 1
SearchFolderItemFactory typedef SearchFolderItemFactory
endif
ifndef __OpenControlPanel_FWD_DEFINED__
__OpenControlPanel_FWD_DEFINED__ equ 1
OpenControlPanel	typedef OpenControlPanel
endif
ifndef __MailRecipient_FWD_DEFINED__
__MailRecipient_FWD_DEFINED__ equ 1
MailRecipient		typedef MailRecipient
endif
ifndef __NetworkExplorerFolder_FWD_DEFINED__
__NetworkExplorerFolder_FWD_DEFINED__ equ 1
NetworkExplorerFolder	typedef NetworkExplorerFolder
endif
ifndef __DestinationList_FWD_DEFINED__
__DestinationList_FWD_DEFINED__ equ 1
DestinationList		typedef DestinationList
endif
ifndef __ApplicationDestinations_FWD_DEFINED__
__ApplicationDestinations_FWD_DEFINED__ equ 1
ApplicationDestinations typedef ApplicationDestinations
endif
ifndef __ApplicationDocumentLists_FWD_DEFINED__
__ApplicationDocumentLists_FWD_DEFINED__ equ 1
ApplicationDocumentLists typedef ApplicationDocumentLists
endif
ifndef __HomeGroup_FWD_DEFINED__
__HomeGroup_FWD_DEFINED__ equ 1
HomeGroup		typedef HomeGroup
endif
ifndef __ShellLibrary_FWD_DEFINED__
__ShellLibrary_FWD_DEFINED__ equ 1
ShellLibrary		typedef ShellLibrary
endif
ifndef __AppStartupLink_FWD_DEFINED__
__AppStartupLink_FWD_DEFINED__ equ 1
AppStartupLink		typedef AppStartupLink
endif
ifndef __EnumerableObjectCollection_FWD_DEFINED__
__EnumerableObjectCollection_FWD_DEFINED__ equ 1
EnumerableObjectCollection typedef EnumerableObjectCollection
endif
ifndef __DesktopGadget_FWD_DEFINED__
__DesktopGadget_FWD_DEFINED__ equ 1
DesktopGadget		typedef DesktopGadget
endif
ifndef __IAssocHandlerInvoker_FWD_DEFINED__
__IAssocHandlerInvoker_FWD_DEFINED__ equ 1
endif
ifndef __IAssocHandler_FWD_DEFINED__
__IAssocHandler_FWD_DEFINED__ equ 1
endif
ifndef __IEnumAssocHandlers_FWD_DEFINED__
__IEnumAssocHandlers_FWD_DEFINED__ equ 1
endif

include objidl.inc
include oleidl.inc
include oaidl.inc
include docobj.inc
include shtypes.inc
include comcat.inc
include propidl.inc
include prsht.inc
include propsys.inc ;
include ObjectArray.inc
include sherrors.inc
.xlist

ifdef __PE__
option	dllimport:<shell32>
else
includelib shell32.lib
endif

CMF_NORMAL		equ 0x00000000
CMF_DEFAULTONLY		equ 0x00000001
CMF_VERBSONLY		equ 0x00000002
CMF_EXPLORE		equ 0x00000004
CMF_NOVERBS		equ 0x00000008
CMF_CANRENAME		equ 0x00000010
CMF_NODEFAULT		equ 0x00000020
if (NTDDI_VERSION LT NTDDI_VISTA)
CMF_INCLUDESTATIC	equ 0x00000040
endif
if (NTDDI_VERSION GE NTDDI_VISTA)
CMF_ITEMMENU		equ 0x00000080
endif
CMF_EXTENDEDVERBS	equ 0x00000100
if (NTDDI_VERSION GE NTDDI_VISTA)
CMF_DISABLEDVERBS	equ 0x00000200
endif
CMF_ASYNCVERBSTATE	equ 0x00000400
CMF_OPTIMIZEFORINVOKE	equ 0x00000800
CMF_SYNCCASCADEMENU	equ 0x00001000
CMF_DONOTPICKDEFAULT	equ 0x00002000
CMF_RESERVED		equ 0xffff0000

GCS_VERBA		equ 0x00000000
GCS_HELPTEXTA		equ 0x00000001
GCS_VALIDATEA		equ 0x00000002
GCS_VERBW		equ 0x00000004
GCS_HELPTEXTW		equ 0x00000005
GCS_VALIDATEW		equ 0x00000006
GCS_VERBICONW		equ 0x00000014
GCS_UNICODE		equ 0x00000004

ifdef _UNICODE
GCS_VERB		equ GCS_VERBW
GCS_HELPTEXT		equ GCS_HEPTEXTW
GCS_VALIDATE		equ GCS_VAIDATEW
else
GCS_VERB		equ GCS_VERBA
GCS_HELPTEXT		equ GCS_HEPTEXTA
GCS_VALIDATE		equ GCS_VAIDATEA
endif

CMDSTR_NEWFOLDERA	equ <"NewFolder">
CMDSTR_VIEWLISTA	equ <"ViewList">
CMDSTR_VIEWDETAILSA	equ <"ViewDetails">
CMDSTR_NEWFOLDERW	equ <L"NewFolder">
CMDSTR_VIEWLISTW	equ <L"ViewList">
CMDSTR_VIEWDETAILSW	equ <L"ViewDetails">

ifdef _UNICODE
CMDSTR_NEWFOLDER	equ CMDSTR_NEWFOLDERW
CMDSTR_VIEWLIST		equ CMDSTR_VIEWLISTW
CMDSTR_VIEWDETAILS	equ CMDSTR_VIEWDETAILSW
else
CMDSTR_NEWFOLDER	equ CMDSTR_NEWFOLDERA
CMDSTR_VIEWLIST		equ CMDSTR_VIEWLISTA
CMDSTR_VIEWDETAILS	equ CMDSTR_VIEWDETAILSA
endif

CMIC_MASK_HOTKEY	equ SEE_MASK_HOTKEY
CMIC_MASK_ICON		equ SEE_MASK_ICON
CMIC_MASK_FLAG_NO_UI	equ SEE_MASK_FAG_NO_UI
CMIC_MASK_UNICODE	equ SEE_MASK_UNICODE
CMIC_MASK_NO_CONSOLE	equ SEE_MASK_NO_CONSOLE
if (NTDDI_VERSION LT NTDDI_VISTA)
CMIC_MASK_HASLINKNAME	equ SEE_MASK_HASLINKNAME
CMIC_MASK_HASTITLE	equ SEE_MASK_HASTITLE
endif
CMIC_MASK_FLAG_SEP_VDM	equ SEE_MASK_FAG_SEPVDM
CMIC_MASK_ASYNCOK	equ SEE_MASK_ASYNCOK
if (NTDDI_VERSION GE NTDDI_VISTA)
CMIC_MASK_NOASYNC	equ SEE_MASK_NOASYNC
endif
if (_WIN32_IE GE _WIN32_IE_IE501)
CMIC_MASK_SHIFT_DOWN	equ 0x10000000
CMIC_MASK_CONTROL_DOWN	equ 0x40000000
endif
if (_WIN32_IE GE 0x0560)
CMIC_MASK_FLAG_LOG_USAGE equ SEE_MASK_FLAG_LOG_USAGE
CMIC_MASK_NOZONECHECKS	equ SEE_MASK_NOZONECHECKS
endif

if (_WIN32_IE GE _WIN32_IE_IE40)
CMIC_MASK_PTINVOKE	equ 0x20000000
endif

;include pshpack8.inc

CMINVOKECOMMANDINFO	STRUC
cbSize			dd ?
fMask			dd ?
hwnd			HWND ?
lpVerb			LPCSTR ?
lpParameters		LPCSTR ?
lpDirectory		LPCSTR ?
nShow			SINT ?
dwHotKey		dd ?
hIcon			HANDLE ?
CMINVOKECOMMANDINFO	ENDS
LPCMINVOKECOMMANDINFO	typedef ptr CMINVOKECOMMANDINFO
PCCMINVOKECOMMANDINFO	typedef ptr CMINVOKECOMMANDINFO

if (_WIN32_IE GE _WIN32_IE_IE40)
CMINVOKECOMMANDINFOEX	STRUC
cbSize			dd ?
fMask			dd ?
hwnd			HWND ?
lpVerb			LPCSTR ?
lpParameters		LPCSTR ?
lpDirectory		LPCSTR ?
nShow			SINT ?
dwHotKey		dd ?
hIcon			HANDLE ?
lpTitle			LPCSTR ?
lpVerbW			LPCWSTR ?
lpParametersW		LPCWSTR ?
lpDirectoryW		LPCWSTR ?
lpTitleW		LPCWSTR ?
ptInvoke		POINT <>
CMINVOKECOMMANDINFOEX	ENDS

else
PRE_IE4_CMINVOKECOMMANDINFOEX STRUC
cbSize			dd ?
fMask			dd ?
hwnd			HWND ?
lpVerb			LPCSTR ?
lpParameters		LPCSTR ?
lpDirectory		LPCSTR ?
nShow			SINT ?
dwHotKey		dd ?
hIcon			HANDLE ?
lpTitle			LPCSTR ?
lpVerbW			LPCWSTR ?
lpParametersW		LPCWSTR ?
lpDirectoryW		LPCWSTR ?
lpTitleW		LPCWSTR ?
CMINVOKECOMMANDINFOEX	ENDS
endif
LPCMINVOKECOMMANDINFOEX typedef ptr CMINVOKECOMMANDINFOEX

PCCMINVOKECOMMANDINFOEX typedef ptr CMINVOKECOMMANDINFOEX

;include poppack.inc

externdef		__MIDL_itf_shobjidl_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IContextMenu_INTERFACE_DEFINED__
__IContextMenu_INTERFACE_DEFINED__ equ 1

externdef		IID_IContextMenu:IID
IContextMenu		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	QueryContextMenu, :HMENU, :UINT, :UINT, :UINT, :UINT
	STDMETHOD	InvokeCommand, :ptr
	STDMETHOD	GetCommandString, :UINT_PTR, :UINT, :ptr, :LPSTR, :UINT


IContextMenu		ENDS

endif

LPCONTEXTMENU		typedef ptr IContextMenu

externdef		__MIDL_itf_shobjidl_0000_0001_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0001_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IContextMenu2_INTERFACE_DEFINED__
__IContextMenu2_INTERFACE_DEFINED__ equ 1

externdef		IID_IContextMenu2:IID
IContextMenu2		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	QueryContextMenu, :HMENU, :UINT, :UINT, :UINT, :UINT
	STDMETHOD	InvokeCommand, :ptr
	STDMETHOD	GetCommandString, :UINT_PTR, :UINT, :ptr, :LPSTR, :UINT
	STDMETHOD	HandleMenuMsg, :UINT, :WPARAM, :LPARAM


IContextMenu2		ENDS

endif

LPCONTEXTMENU2		typedef ptr IContextMenu2

externdef		__MIDL_itf_shobjidl_0000_0002_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0002_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IContextMenu3_INTERFACE_DEFINED__
__IContextMenu3_INTERFACE_DEFINED__ equ 1

externdef		IID_IContextMenu3:IID
IContextMenu3		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	QueryContextMenu, :HMENU, :UINT, :UINT, :UINT, :UINT
	STDMETHOD	InvokeCommand, :ptr
	STDMETHOD	GetCommandString, :UINT_PTR, :UINT, :ptr, :LPSTR, :UINT
	STDMETHOD	HandleMenuMsg, :UINT, :WPARAM, :LPARAM
	STDMETHOD	HandleMenuMsg2, :UINT, :WPARAM, :LPARAM, :ptr


IContextMenu3		ENDS

endif

LPCONTEXTMENU3		typedef ptr IContextMenu3

externdef		__MIDL_itf_shobjidl_0000_0003_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0003_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IExecuteCommand_INTERFACE_DEFINED__
__IExecuteCommand_INTERFACE_DEFINED__ equ 1

externdef		IID_IExecuteCommand:IID
IExecuteCommand		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetKeyState, :DWORD
	STDMETHOD	SetParameters, :LPCWSTR
	STDMETHOD	SetPosition, :POINT
	STDMETHOD	SetShowWindow, :SINT
	STDMETHOD	SetNoShowUI, :BOOL
	STDMETHOD	SetDirectory, :LPCWSTR
	STDMETHOD	Execute


IExecuteCommand		ENDS

endif

ifndef __IPersistFolder_INTERFACE_DEFINED__
__IPersistFolder_INTERFACE_DEFINED__ equ 1

externdef		IID_IPersistFolder:IID
IPersistFolder		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetClassID, :ptr
	STDMETHOD	Initialize, :PCIDLIST_ABSOLUTE


IPersistFolder		ENDS

endif

LPPERSISTFOLDER		typedef ptr IPersistFolder

if (_WIN32_IE GE 0x0400)
IRTIR_TASK_NOT_RUNNING	equ 0
IRTIR_TASK_RUNNING	equ 1
IRTIR_TASK_SUSPENDED	equ 2
IRTIR_TASK_PENDING	equ 3
IRTIR_TASK_FINISHED	equ 4

externdef		__MIDL_itf_shobjidl_0000_0005_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0005_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IRunnableTask_INTERFACE_DEFINED__
__IRunnableTask_INTERFACE_DEFINED__ equ 1

externdef		IID_IRunnableTask:IID
IRunnableTask		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Run
	STDMETHOD	Kill, :BOOL
	STDMETHOD	Suspend
	STDMETHOD	Resume
	STDMETHOD	IsRunning


IRunnableTask		ENDS

endif

TOID_NULL		equ GUID_NULL
ITSAT_DEFAULT_LPARAM	equ (-1)
ITSAT_DEFAULT_PRIORITY	equ 0x10000000
ITSAT_MAX_PRIORITY	equ 0x7fffffff
ITSAT_MIN_PRIORITY	equ 0x00000000
ITSSFLAG_COMPLETE_ON_DESTROY equ 0x0000
ITSSFLAG_KILL_ON_DESTROY equ 0x0001
ITSSFLAG_FLAGS_MASK	equ 0x0003
ITSS_THREAD_DESTROY_DEFAULT_TIMEOUT equ (10*1000)
ITSS_THREAD_TERMINATE_TIMEOUT equ (INFINITE)
ITSS_THREAD_TIMEOUT_NO_CHANGE equ (INFINITE - 1)


externdef		__MIDL_itf_shobjidl_0000_0006_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0006_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IShellTaskScheduler_INTERFACE_DEFINED__
__IShellTaskScheduler_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_IShellTaskScheduler, 0x6ccb7be0, 0x6807, 0x11d0, 0xb8,0x10, 0x00,0xc0,0x4f,0xd7,0x06,0xec)

externdef		IID_IShellTaskScheduler:IID
IShellTaskScheduler	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	AddTask, :ptr, :REFTASKOWNERID, :DWORD_PTR, :DWORD
	STDMETHOD	RemoveTasks, :REFTASKOWNERID, :DWORD_PTR, :BOOL
	STDMETHOD	CountTasks, :REFTASKOWNERID
	STDMETHOD	Status, :DWORD, :DWORD


IShellTaskScheduler	ENDS

endif

SID_ShellTaskScheduler	equ IID_IShellTaskScheduler

externdef		__MIDL_itf_shobjidl_0000_0007_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0007_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IQueryCodePage_INTERFACE_DEFINED__
__IQueryCodePage_INTERFACE_DEFINED__ equ 1

externdef		IID_IQueryCodePage:IID
IQueryCodePage		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetCodePage, :ptr
	STDMETHOD	SetCodePage, :UINT


IQueryCodePage		ENDS

endif

ifndef __IPersistFolder2_INTERFACE_DEFINED__
__IPersistFolder2_INTERFACE_DEFINED__ equ 1

externdef		IID_IPersistFolder2:IID
IPersistFolder2		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetClassID, :ptr
	STDMETHOD	Initialize, :PCIDLIST_ABSOLUTE
	STDMETHOD	GetCurFolder, :ptr


IPersistFolder2		ENDS

endif
endif ; (_WIN32_IE GE 0x0400)

if (_WIN32_IE GE 0x0500)
CSIDL_FLAG_PFTI_TRACKTARGET equ CSIDL_FAG_DONT_VERIFY

;include pshpack8.inc

PERSIST_FOLDER_TARGET_INFO STRUC
pidlTargetFolder	PIDLIST_ABSOLUTE ?
szTargetParsingName	WCHAR  260  dup(?)
szNetworkProvider	WCHAR  260  dup(?)
dwAttributes		dd ?
csidl			SINT ?
PERSIST_FOLDER_TARGET_INFO ENDS

;include poppack.inc


externdef		__MIDL_itf_shobjidl_0000_0009_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0009_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IPersistFolder3_INTERFACE_DEFINED__
__IPersistFolder3_INTERFACE_DEFINED__ equ 1

externdef		IID_IPersistFolder3:IID
IPersistFolder3		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetClassID, :ptr
	STDMETHOD	Initialize, :PCIDLIST_ABSOLUTE
	STDMETHOD	GetCurFolder, :ptr
	STDMETHOD	InitializeEx, :ptr, :PCIDLIST_ABSOLUTE, :ptr
	STDMETHOD	GetFolderTargetInfo, :ptr


IPersistFolder3		ENDS

endif
endif

if (NTDDI_VERSION GE NTDDI_WINXP) OR (_WIN32_IE GE _WIN32_IE_IE70)

externdef		__MIDL_itf_shobjidl_0000_0010_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0010_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IPersistIDList_INTERFACE_DEFINED__
__IPersistIDList_INTERFACE_DEFINED__ equ 1

externdef		IID_IPersistIDList:IID
IPersistIDList		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetClassID, :ptr
	STDMETHOD	SetIDList, :PCIDLIST_ABSOLUTE
	STDMETHOD	GetIDList, :ptr


IPersistIDList		ENDS

endif
endif

externdef		__MIDL_itf_shobjidl_0000_0011_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0011_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumIDList_INTERFACE_DEFINED__
__IEnumIDList_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumIDList:IID
IEnumIDList		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :ULONG, :ptr, :ptr
	STDMETHOD	Skip, :ULONG
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr


IEnumIDList		ENDS
LPIEnumIDList		typedef ptr IEnumIDList

IEnumIDList_RemoteNext_Proxy proto WINAPI \
		 _This: LPIEnumIDList,
		  celt: ULONG,
		 rgelt: ptr PITEMID_CHILD,
	  pceltFetched: LPULONG

;void
IEnumIDList_RemoteNext_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

LPENUMIDLIST		typedef ptr IEnumIDList

externdef		__MIDL_itf_shobjidl_0000_0012_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0012_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumFullIDList_INTERFACE_DEFINED__
__IEnumFullIDList_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumFullIDList:IID
IEnumFullIDList		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :ULONG, :ptr, :ptr
	STDMETHOD	Skip, :ULONG
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr


IEnumFullIDList		ENDS

IEnumFullIDList_RemoteNext_Proxy proto WINAPI \
		 _This: ptr IEnumFullIDList,
		  celt: ULONG,
		 rgelt: ptr PIDLIST_ABSOLUTE,
	  pceltFetched: LPULONG

;void
IEnumFullIDList_RemoteNext_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

SHGDN_NORMAL		equ 0
SHGDN_INFOLDER		equ 0x1
SHGDN_FOREDITING	equ 0x1000
SHGDN_FORADDRESSBAR	equ 0x4000
SHGDN_FORPARSING	equ 0x8000
SHGDNF			typedef DWORD

SHCONTF_CHECKING_FOR_CHILDREN equ 0x10
SHCONTF_FOLDERS		equ 0x20
SHCONTF_NONFOLDERS	equ 0x40
SHCONTF_INCLUDEHIDDEN	equ 0x80
SHCONTF_INIT_ON_FIRST_NEXT equ 0x100
SHCONTF_NETPRINTERSRCH	equ 0x200
SHCONTF_SHAREABLE	equ 0x400
SHCONTF_STORAGE		equ 0x800
SHCONTF_NAVIGATION_ENUM equ 0x1000
SHCONTF_FASTITEMS	equ 0x2000
SHCONTF_FLATLIST	equ 0x4000
SHCONTF_ENABLE_ASYNC	equ 0x8000
SHCONTF_INCLUDESUPERHIDDEN equ 0x10000
SHCONTF			typedef DWORD

SHCIDS_ALLFIELDS	equ 0x80000000
SHCIDS_CANONICALONLY	equ 0x10000000
SHCIDS_BITMASK		equ 0xFFFF0000
SHCIDS_COLUMNMASK	equ 0x0000FFFF
SFGAO_CANCOPY		equ DROPEFFECT_COPY
SFGAO_CANMOVE		equ DROPEFFECT_MOVE
SFGAO_CANLINK		equ DROPEFFECT_LINK
SFGAO_STORAGE		equ 0x00000008
SFGAO_CANRENAME		equ 0x00000010
SFGAO_CANDELETE		equ 0x00000020
SFGAO_HASPROPSHEET	equ 0x00000040
SFGAO_DROPTARGET	equ 0x00000100
SFGAO_CAPABILITYMASK	equ 0x00000177
SFGAO_SYSTEM		equ 0x00001000
SFGAO_ENCRYPTED		equ 0x00002000
SFGAO_ISSLOW		equ 0x00004000
SFGAO_GHOSTED		equ 0x00008000
SFGAO_LINK		equ 0x00010000
SFGAO_SHARE		equ 0x00020000
SFGAO_READONLY		equ 0x00040000
SFGAO_HIDDEN		equ 0x00080000
SFGAO_DISPLAYATTRMASK	equ 0x000FC000
SFGAO_FILESYSANCESTOR	equ 0x10000000
SFGAO_FOLDER		equ 0x20000000
SFGAO_FILESYSTEM	equ 0x40000000
SFGAO_HASSUBFOLDER	equ 0x80000000
SFGAO_CONTENTSMASK	equ 0x80000000
SFGAO_VALIDATE		equ 0x01000000
SFGAO_REMOVABLE		equ 0x02000000
SFGAO_COMPRESSED	equ 0x04000000
SFGAO_BROWSABLE		equ 0x08000000
SFGAO_NONENUMERATED	equ 0x00100000
SFGAO_NEWCONTENT	equ 0x00200000
SFGAO_CANMONIKER	equ 0x00400000
SFGAO_HASSTORAGE	equ 0x00400000
SFGAO_STREAM		equ 0x00400000
SFGAO_STORAGEANCESTOR	equ 0x00800000
SFGAO_STORAGECAPMASK	equ 0x70C50008
SFGAO_PKEYSFGAOMASK	equ 0x81044000
SFGAOF			typedef ULONG

STR_BIND_FORCE_FOLDER_SHORTCUT_RESOLVE equ <L"Force Folder Shortcut Resolve">
STR_AVOID_DRIVE_RESTRICTION_POLICY equ <L"Avoid Drive Restriction Policy">
STR_AVOID_DRIVE_RESTRICTION_POLICY equ <L"Avoid Drive Restriction Policy">
STR_SKIP_BINDING_CLSID	equ <L"Skip Binding CSID">
STR_PARSE_PREFER_FOLDER_BROWSING equ <L"Parse Prefer Folder Browsing">
STR_DONT_PARSE_RELATIVE equ <L"Don't Parse Relative">
STR_PARSE_TRANSLATE_ALIASES equ <L"Parse Translate Aliases">
STR_PARSE_SKIP_NET_CACHE equ <L"Skip Net Resource Cache">
STR_PARSE_SHELL_PROTOCOL_TO_FILE_OBJECTS equ <L"Parse Shell Protocol To File Objects">
if (_WIN32_IE GE 0x0700)
STR_TRACK_CLSID		equ <L"Track the CSID">
STR_INTERNAL_NAVIGATE	equ <L"Internal Navigation">
STR_PARSE_PROPERTYSTORE equ <L"DelegateNamedProperties">
STR_NO_VALIDATE_FILENAME_CHARS equ <L"NoValidateFilenameChars">
STR_BIND_DELEGATE_CREATE_OBJECT equ <L"Delegate Object Creation">
STR_PARSE_ALLOW_INTERNET_SHELL_FOLDERS equ <L"Allow binding to Internet shell folder handlers and negate STR_PARSE_PREFER_WEB_BROWSING">
STR_PARSE_PREFER_WEB_BROWSING equ <L"Do not bind to Internet shell folder handlers">
STR_PARSE_SHOW_NET_DIAGNOSTICS_UI equ <L"Show network diagnostics UI">
STR_PARSE_DONT_REQUIRE_VALIDATED_URLS equ <L"Do not require validated URLs">
STR_INTERNETFOLDER_PARSE_ONLY_URLMON_BINDABLE equ <L"Validate URL">
endif

if (NTDDI_VERSION GE NTDDI_WIN7)
STR_BIND_FOLDERS_READ_ONLY equ <L"Folders As Read Only">
STR_BIND_FOLDER_ENUM_MODE equ <L"Folder Enum Mode">

FOLDER_ENUM_MODE	typedef SDWORD
FEM_VIEWRESULT		equ 0
FEM_NAVIGATION		equ 1

externdef		__MIDL_itf_shobjidl_0000_0013_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0013_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IObjectWithFolderEnumMode_INTERFACE_DEFINED__
__IObjectWithFolderEnumMode_INTERFACE_DEFINED__ equ 1

externdef		IID_IObjectWithFolderEnumMode:IID
IObjectWithFolderEnumMode STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetMode, :FOLDER_ENUM_MODE
	STDMETHOD	GetMode, :ptr


IObjectWithFolderEnumMode ENDS

endif


STR_PARSE_WITH_EXPLICIT_PROGID equ <L"ExplicitProgid">
STR_PARSE_WITH_EXPLICIT_ASSOCAPP equ <L"ExplicitAssociationApp">
STR_PARSE_EXPLICIT_ASSOCIATION_SUCCESSFUL equ <L"ExplicitAssociationSuccessful">
STR_PARSE_AND_CREATE_ITEM equ <L"ParseAndCreateItem">

externdef		__MIDL_itf_shobjidl_0000_0014_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0014_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IParseAndCreateItem_INTERFACE_DEFINED__
__IParseAndCreateItem_INTERFACE_DEFINED__ equ 1

externdef		IID_IParseAndCreateItem:IID
IParseAndCreateItem	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetItem, :ptr
	STDMETHOD	GetItem, :REFIID, :ptr


IParseAndCreateItem	ENDS

endif

STR_ITEM_CACHE_CONTEXT	equ <L"ItemCacheContext">
endif ; (NTDDI_VERSION GE NTDDI_WIN7)

externdef		__MIDL_itf_shobjidl_0000_0015_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0015_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IShellFolder_INTERFACE_DEFINED__
__IShellFolder_INTERFACE_DEFINED__ equ 1

externdef		IID_IShellFolder:IID
IShellFolder		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	ParseDisplayName, :HWND, :ptr, :LPWSTR, :ptr, :ptr, :ptr
	STDMETHOD	EnumObjects, :HWND, :SHCONTF, :ptr
	STDMETHOD	BindToObject, :PCUIDLIST_RELATIVE, :ptr, :REFIID, :ptr
	STDMETHOD	BindToStorage, :PCUIDLIST_RELATIVE, :ptr, :REFIID, :ptr
	STDMETHOD	CompareIDs, :LPARAM, :PCUIDLIST_RELATIVE, :PCUIDLIST_RELATIVE
	STDMETHOD	CreateViewObject, :HWND, :REFIID, :ptr
	STDMETHOD	GetAttributesOf, :UINT, :PCUITEMID_CHILD_ARRAY, :ptr
	STDMETHOD	GetUIObjectOf, :HWND, :UINT, :PCUITEMID_CHILD_ARRAY, :REFIID, :ptr, :ptr
	STDMETHOD	GetDisplayNameOf, :PCUITEMID_CHILD, :SHGDNF, :ptr
	STDMETHOD	SetNameOf, :HWND, :PCUITEMID_CHILD, :LPCWSTR, :SHGDNF, :ptr


IShellFolder		ENDS
LPIShellFolder		typedef ptr IShellFolder

IShellFolder_RemoteSetNameOf_Proxy proto WINAPI \
		 _This: ptr IShellFolder,
		  hwnd: HWND,
		  pidl: PCUITEMID_CHILD,
	       pszName: LPCWSTR,
		uFlags: SHGDNF,
	      ppidlOut: ptr PITEMID_CHILD

;void
IShellFolder_RemoteSetNameOf_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD


endif

LPSHELLFOLDER		typedef ptr IShellFolder

EXTRASEARCH		STRUC
guidSearch		GUID <>
wszFriendlyName		WCHAR  80  dup(?)
wszUrl			WCHAR  2084  dup(?)
EXTRASEARCH		ENDS

LPEXTRASEARCH		typedef ptr EXTRASEARCH

externdef		__MIDL_itf_shobjidl_0000_0016_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0016_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumExtraSearch_INTERFACE_DEFINED__
__IEnumExtraSearch_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumExtraSearch:IID
IEnumExtraSearch	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :ULONG, :ptr, :ptr
	STDMETHOD	Skip, :ULONG
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr


IEnumExtraSearch	ENDS

endif

LPENUMEXTRASEARCH	typedef ptr IEnumExtraSearch

externdef		__MIDL_itf_shobjidl_0000_0017_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0017_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IShellFolder2_INTERFACE_DEFINED__
__IShellFolder2_INTERFACE_DEFINED__ equ 1

externdef		IID_IShellFolder2:IID
IShellFolder2		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	ParseDisplayName, :HWND, :ptr, :LPWSTR, :ptr, :ptr, :ptr
	STDMETHOD	EnumObjects, :HWND, :SHCONTF, :ptr
	STDMETHOD	BindToObject, :PCUIDLIST_RELATIVE, :ptr, :REFIID, :ptr
	STDMETHOD	BindToStorage, :PCUIDLIST_RELATIVE, :ptr, :REFIID, :ptr
	STDMETHOD	CompareIDs, :LPARAM, :PCUIDLIST_RELATIVE, :PCUIDLIST_RELATIVE
	STDMETHOD	CreateViewObject, :HWND, :REFIID, :ptr
	STDMETHOD	GetAttributesOf, :UINT, :PCUITEMID_CHILD_ARRAY, :ptr
	STDMETHOD	GetUIObjectOf, :HWND, :UINT, :PCUITEMID_CHILD_ARRAY, :REFIID, :ptr, :ptr
	STDMETHOD	GetDisplayNameOf, :PCUITEMID_CHILD, :SHGDNF, :ptr
	STDMETHOD	SetNameOf, :HWND, :PCUITEMID_CHILD, :LPCWSTR, :SHGDNF, :ptr
	STDMETHOD	GetDefaultSearchGUID, :ptr
	STDMETHOD	EnumSearches, :ptr
	STDMETHOD	GetDefaultColumn, :DWORD, :ptr, :ptr
	STDMETHOD	GetDefaultColumnState, :UINT, :ptr
	STDMETHOD	GetDetailsEx, :PCUITEMID_CHILD, :ptr, :ptr
	STDMETHOD	GetDetailsOf, :PCUITEMID_CHILD, :UINT, :ptr
	STDMETHOD	MapColumnToSCID, :UINT, :ptr


IShellFolder2		ENDS

endif

LPVIEWSETTINGS		typedef ptr sbyte

FOLDERFLAGS		typedef SDWORD
FWF_NONE		equ 0
FWF_AUTOARRANGE		equ 0x1
FWF_ABBREVIATEDNAMES	equ 0x2
FWF_SNAPTOGRID		equ 0x4
FWF_OWNERDATA		equ 0x8
FWF_BESTFITWINDOW	equ 0x10
FWF_DESKTOP		equ 0x20
FWF_SINGLESEL		equ 0x40
FWF_NOSUBFOLDERS	equ 0x80
FWF_TRANSPARENT		equ 0x100
FWF_NOCLIENTEDGE	equ 0x200
FWF_NOSCROLL		equ 0x400
FWF_ALIGNLEFT		equ 0x800
FWF_NOICONS		equ 0x1000
FWF_SHOWSELALWAYS	equ 0x2000
FWF_NOVISIBLE		equ 0x4000
FWF_SINGLECLICKACTIVATE equ 0x8000
FWF_NOWEBVIEW		equ 0x10000
FWF_HIDEFILENAMES	equ 0x20000
FWF_CHECKSELECT		equ 0x40000
FWF_NOENUMREFRESH	equ 0x80000
FWF_NOGROUPING		equ 0x100000
FWF_FULLROWSELECT	equ 0x200000
FWF_NOFILTERS		equ 0x400000
FWF_NOCOLUMNHEADER	equ 0x800000
FWF_NOHEADERINALLVIEWS	equ 0x1000000
FWF_EXTENDEDTILES	equ 0x2000000
FWF_TRICHECKSELECT	equ 0x4000000
FWF_AUTOCHECKSELECT	equ 0x8000000
FWF_NOBROWSERVIEWSTATE	equ 0x10000000
FWF_SUBSETGROUPS	equ 0x20000000
FWF_USESEARCHFOLDER	equ 0x40000000
FWF_ALLOWRTLREADING	equ 0x80000000

DEFINE_ENUM_FLAG_OPERATORS(FOLDERFLAGS)
FOLDERVIEWMODE		typedef SDWORD
FVM_AUTO		equ -1
FVM_FIRST		equ 1
FVM_ICON		equ 1
FVM_SMALLICON		equ 2
FVM_LIST		equ 3
FVM_DETAILS		equ 4
FVM_THUMBNAIL		equ 5
FVM_TILE		equ 6
FVM_THUMBSTRIP		equ 7
FVM_CONTENT		equ 8
FVM_LAST		equ 8

if (NTDDI_VERSION GE NTDDI_VISTA)
FOLDERLOGICALVIEWMODE	typedef SDWORD
FLVM_UNSPECIFIED	equ -1
FLVM_FIRST		equ 1
FLVM_DETAILS		equ 1
FLVM_TILES		equ 2
FLVM_ICONS		equ 3
FLVM_LIST		equ 4
FLVM_CONTENT		equ 5
FLVM_LAST		equ 5

endif
FOLDERSETTINGS		STRUC
ViewMode		UINT ?
fFlags			UINT ?
FOLDERSETTINGS		ENDS

LPFOLDERSETTINGS	typedef ptr FOLDERSETTINGS
LPCFOLDERSETTINGS	typedef ptr FOLDERSETTINGS
PFOLDERSETTINGS		typedef ptr FOLDERSETTINGS

externdef		__MIDL_itf_shobjidl_0000_0018_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0018_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFolderViewOptions_INTERFACE_DEFINED__
__IFolderViewOptions_INTERFACE_DEFINED__ equ 1

FOLDERVIEWOPTIONS	typedef SDWORD
FVO_DEFAULT		equ 0
FVO_VISTALAYOUT		equ 0x1
FVO_CUSTOMPOSITION	equ 0x2
FVO_CUSTOMORDERING	equ 0x4
FVO_SUPPORTHYPERLINKS	equ 0x8
FVO_NOANIMATIONS	equ 0x10
FVO_NOSCROLLTIPS	equ 0x20

DEFINE_ENUM_FLAG_OPERATORS(FOLDERVIEWOPTIONS)

externdef		IID_IFolderViewOptions:IID
IFolderViewOptions	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetFolderViewOptions, :FOLDERVIEWOPTIONS, :FOLDERVIEWOPTIONS
	STDMETHOD	GetFolderViewOptions, :ptr


IFolderViewOptions	ENDS

endif


_SVSIF			typedef SDWORD
SVSI_DESELECT		equ 0
SVSI_SELECT		equ 0x1
SVSI_EDIT		equ 0x3
SVSI_DESELECTOTHERS	equ 0x4
SVSI_ENSUREVISIBLE	equ 0x8
SVSI_FOCUSED		equ 0x10
SVSI_TRANSLATEPT	equ 0x20
SVSI_SELECTIONMARK	equ 0x40
SVSI_POSITIONITEM	equ 0x80
SVSI_CHECK		equ 0x100
SVSI_CHECK2		equ 0x200
SVSI_KEYBOARDSELECT	equ 0x401
SVSI_NOTAKEFOCUS	equ 0x40000000

SVSI_NOSTATECHANGE	equ 0x80000000
SVSIF			typedef UINT

_SVGIO			typedef SDWORD
SVGIO_BACKGROUND	equ 0
SVGIO_SELECTION		equ 0x1
SVGIO_ALLVIEW		equ 0x2
SVGIO_CHECKED		equ 0x3
SVGIO_TYPE_MASK		equ 0xf
SVGIO_FLAG_VIEWORDER	equ 0x80000000

DEFINE_ENUM_FLAG_OPERATORS(_SVGIO)
SVGIO			typedef SINT

SVUIA_STATUS		typedef SDWORD
SVUIA_DEACTIVATE	equ 0
SVUIA_ACTIVATE_NOFOCUS	equ 1
SVUIA_ACTIVATE_FOCUS	equ 2
SVUIA_INPLACEACTIVATE	equ 3

ifdef _FIX_ENABLEMODELESS_CONFLICT
EnableModeless		equ <EnableModelessSV>
endif

ifdef _NEVER_
LPFNSVADDPROPSHEETPAGE	typedef LPARAM
else
include prsht.inc
.xlist
LPFNSVADDPROPSHEETPAGE	typedef LPFNADDPROPSHEETPAGE
endif

externdef		__MIDL_itf_shobjidl_0000_0019_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0019_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IShellView_INTERFACE_DEFINED__
__IShellView_INTERFACE_DEFINED__ equ 1

externdef		IID_IShellView:IID
IShellView		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow, :ptr
	STDMETHOD	ContextSensitiveHelp, :BOOL
	STDMETHOD	TranslateAccelerator, :ptr
	STDMETHOD	EnableModeless, :BOOL
	STDMETHOD	UIActivate, :UINT
	STDMETHOD	Refresh
	STDMETHOD	CreateViewWindow, :ptr, :LPCFOLDERSETTINGS, :ptr, :ptr, :ptr
	STDMETHOD	DestroyViewWindow
	STDMETHOD	GetCurrentInfo, :LPFOLDERSETTINGS
	STDMETHOD	AddPropertySheetPages, :DWORD, :LPFNSVADDPROPSHEETPAGE, :LPARAM
	STDMETHOD	SaveViewState
	STDMETHOD	SelectItem, :PCUITEMID_CHILD, :SVSIF
	STDMETHOD	GetItemObject, :UINT, :REFIID, :ptr


IShellView		ENDS
LPIShellView		typedef ptr IShellView
LPSHELLVIEW		typedef ptr IShellView

endif

ifndef __IShellView2_INTERFACE_DEFINED__
__IShellView2_INTERFACE_DEFINED__ equ 1

SHELLVIEWID		typedef GUID
LPSHELLVIEWID		typedef ptr SHELLVIEWID
LPIShellBrowser		typedef ptr IShellBrowser

SV2GV_CURRENTVIEW	equ -1
SV2GV_DEFAULTVIEW	equ -2
;include pshpack8.inc
SV2CVW2_PARAMS		STRUC
cbSize			dd ?
psvPrev			LPIShellView ?
pfs			LPCFOLDERSETTINGS ?
psbOwner		LPIShellBrowser ?
prcView			LPRECT ?
pvid			LPSHELLVIEWID ?
hwndView		HWND ?
SV2CVW2_PARAMS		ENDS
LPSV2CVW2_PARAMS	typedef ptr SV2CVW2_PARAMS

;include poppack.inc

externdef		IID_IShellView2:IID
IShellView2		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow, :ptr
	STDMETHOD	ContextSensitiveHelp, :BOOL
	STDMETHOD	TranslateAccelerator, :ptr
	STDMETHOD	EnableModeless, :BOOL
	STDMETHOD	UIActivate, :UINT
	STDMETHOD	Refresh
	STDMETHOD	CreateViewWindow, :ptr, :LPCFOLDERSETTINGS, :ptr, :ptr, :ptr
	STDMETHOD	DestroyViewWindow
	STDMETHOD	GetCurrentInfo, :LPFOLDERSETTINGS
	STDMETHOD	AddPropertySheetPages, :DWORD, :LPFNSVADDPROPSHEETPAGE, :LPARAM
	STDMETHOD	SaveViewState
	STDMETHOD	SelectItem, :PCUITEMID_CHILD, :SVSIF
	STDMETHOD	GetItemObject, :UINT, :REFIID, :ptr
	STDMETHOD	GetView, :ptr, :ULONG
	STDMETHOD	CreateViewWindow2, :LPSV2CVW2_PARAMS
	STDMETHOD	HandleRename, :PCUITEMID_CHILD
	STDMETHOD	SelectAndPositionItem, :PCUITEMID_CHILD, :UINT, :ptr


IShellView2		ENDS

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

externdef		__MIDL_itf_shobjidl_0000_0021_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0021_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IShellView3_INTERFACE_DEFINED__
__IShellView3_INTERFACE_DEFINED__ equ 1

SV3CVW3_DEFAULT		equ 0
SV3CVW3_NONINTERACTIVE	equ 0x1
SV3CVW3_FORCEVIEWMODE	equ 0x2
SV3CVW3_FORCEFOLDERFLAGS equ 0x4
SV3CVW3_FLAGS		typedef DWORD

externdef		IID_IShellView3:IID
IShellView3		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow, :ptr
	STDMETHOD	ContextSensitiveHelp, :BOOL
	STDMETHOD	TranslateAccelerator, :ptr
	STDMETHOD	EnableModeless, :BOOL
	STDMETHOD	UIActivate, :UINT
	STDMETHOD	Refresh
	STDMETHOD	CreateViewWindow, :ptr, :LPCFOLDERSETTINGS, :ptr, :ptr, :ptr
	STDMETHOD	DestroyViewWindow
	STDMETHOD	GetCurrentInfo, :LPFOLDERSETTINGS
	STDMETHOD	AddPropertySheetPages, :DWORD, :LPFNSVADDPROPSHEETPAGE, :LPARAM
	STDMETHOD	SaveViewState
	STDMETHOD	SelectItem, :PCUITEMID_CHILD, :SVSIF
	STDMETHOD	GetItemObject, :UINT, :REFIID, :ptr
	STDMETHOD	GetView, :ptr, :ULONG
	STDMETHOD	CreateViewWindow2, :LPSV2CVW2_PARAMS
	STDMETHOD	HandleRename, :PCUITEMID_CHILD
	STDMETHOD	SelectAndPositionItem, :PCUITEMID_CHILD, :UINT, :ptr
	STDMETHOD	CreateViewWindow3, :ptr, :ptr, :SV3CVW3_FLAGS, :FOLDERFLAGS, :FOLDERFLAGS, :FOLDERVIEWMODE, :ptr, :ptr, :ptr


IShellView3		ENDS

endif
endif

ifdef _FIX_ENABLEMODELESS_CONFLICT
;undef	  EnableModeless
endif

externdef		__MIDL_itf_shobjidl_0000_0022_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0022_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFolderView_INTERFACE_DEFINED__
__IFolderView_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_IFolderView, 0xcde725b0, 0xccc9, 0x4519, 0x91,0x7e, 0x32,0x5d,0x72,0xfa,0xb4,0xce)

externdef		IID_IFolderView:IID
IFolderView		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetCurrentViewMode, :ptr
	STDMETHOD	SetCurrentViewMode, :UINT
	STDMETHOD	GetFolder, :REFIID, :ptr
	STDMETHOD	Item, :SINT, :ptr
	STDMETHOD	ItemCount, :UINT, :ptr
	STDMETHOD	Items, :UINT, :REFIID, :ptr
	STDMETHOD	GetSelectionMarkedItem, :ptr
	STDMETHOD	GetFocusedItem, :ptr
	STDMETHOD	GetItemPosition, :PCUITEMID_CHILD, :ptr
	STDMETHOD	GetSpacing, :ptr
	STDMETHOD	GetDefaultSpacing, :ptr
	STDMETHOD	GetAutoArrange
	STDMETHOD	SelectItem, :SINT, :DWORD
	STDMETHOD	SelectAndPositionItems, :UINT, :PCUITEMID_CHILD_ARRAY, :ptr, :DWORD


IFolderView		ENDS

endif

SID_SFolderView		equ IID_IFolderView
if (NTDDI_VERSION GE NTDDI_WIN7)

externdef		__MIDL_itf_shobjidl_0000_0023_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0023_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ISearchBoxInfo_INTERFACE_DEFINED__
__ISearchBoxInfo_INTERFACE_DEFINED__ equ 1

externdef		IID_ISearchBoxInfo:IID
ISearchBoxInfo		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetCondition, :REFIID, :ptr
	STDMETHOD	GetText, :ptr


ISearchBoxInfo		ENDS

endif
endif

if (NTDDI_VERSION GE NTDDI_VISTA) OR (_WIN32_IE GE _WIN32_IE_IE70)

ifndef NO_SHOBJIDL_SORTDIRECTION
tagSORTDIRECTION	typedef SDWORD
SORT_DESCENDING		equ -1
SORT_ASCENDING		equ 1
endif

SORTDIRECTION		typedef SINT

SORTCOLUMN		STRUC
propkey			PROPERTYKEY <>
direction		SORTDIRECTION ?
SORTCOLUMN		ENDS

FVTEXTTYPE		typedef SDWORD
FVST_EMPTYTEXT		equ 0

DEPRECATED_HRESULT	typedef HRESULT

IFolderView2		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetCurrentViewMode, :ptr
	STDMETHOD	SetCurrentViewMode, :UINT
	STDMETHOD	GetFolder, :REFIID, :ptr
	STDMETHOD	Item, :SINT, :ptr
	STDMETHOD	ItemCount, :UINT, :ptr
	STDMETHOD	Items, :UINT, :REFIID, :ptr
	STDMETHOD	GetSelectionMarkedItem, :ptr
	STDMETHOD	GetFocusedItem, :ptr
	STDMETHOD	GetItemPosition, :PCUITEMID_CHILD, :ptr
	STDMETHOD	GetSpacing, :ptr
	STDMETHOD	GetDefaultSpacing, :ptr
	STDMETHOD	GetAutoArrange
	STDMETHOD	SelectItem, :SINT, :DWORD
	STDMETHOD	SelectAndPositionItems, :UINT, :PCUITEMID_CHILD_ARRAY, :ptr, :DWORD
	STDMETHOD	SetGroupBy, :REFPROPERTYKEY, :BOOL
	STDMETHOD	GetGroupBy, :ptr, :ptr
	STDMETHOD	SetViewProperty, :PCUITEMID_CHILD, :REFPROPERTYKEY, :REFPROPVARIANT
	STDMETHOD	GetViewProperty, :PCUITEMID_CHILD, :REFPROPERTYKEY, :ptr
	STDMETHOD	SetTileViewProperties, :PCUITEMID_CHILD, :LPCWSTR
	STDMETHOD	SetExtendedTileViewProperties, :PCUITEMID_CHILD, :LPCWSTR
	STDMETHOD	SetText, :FVTEXTTYPE, :LPCWSTR
	STDMETHOD	SetCurrentFolderFlags, :DWORD, :DWORD
	STDMETHOD	GetCurrentFolderFlags, :ptr
	STDMETHOD	GetSortColumnCount, :ptr
	STDMETHOD	SetSortColumns, :ptr, :SINT
	STDMETHOD	GetSortColumns, :ptr, :SINT
	STDMETHOD	GetItem, :SINT, :REFIID, :ptr
	STDMETHOD	GetVisibleItem, :SINT, :BOOL, :ptr
	STDMETHOD	GetSelectedItem, :SINT, :ptr
	STDMETHOD	GetSelection, :BOOL, :ptr
	STDMETHOD	GetSelectionState, :PCUITEMID_CHILD, :ptr
	STDMETHOD	InvokeVerbOnSelection, :LPCSTR
	STDMETHOD	SetViewModeAndIconSize, :FOLDERVIEWMODE, :SINT
	STDMETHOD	GetViewModeAndIconSize, :ptr, :ptr
	STDMETHOD	SetGroupSubsetCount, :UINT
	STDMETHOD	GetGroupSubsetCount, :ptr
	STDMETHOD	SetRedraw, :BOOL
	STDMETHOD	IsMoveInSameFolder
	STDMETHOD	DoRename


IFolderView2		ENDS

;STDMETHODCALLTYPE
IFolderView2_RemoteGetGroupBy_Proxy proto WINAPI \
		 _This: ptr IFolderView2,
		  pkey: ptr PROPERTYKEY,
	   pfAscending: LPBOOL
;void
IFolderView2_RemoteGetGroupBy_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

externdef		__MIDL_itf_shobjidl_0000_0025_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0025_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFolderViewSettings_INTERFACE_DEFINED__
__IFolderViewSettings_INTERFACE_DEFINED__ equ 1

externdef		IID_IFolderViewSettings:IID
IFolderViewSettings	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetColumnPropertyList, :REFIID, :ptr
	STDMETHOD	GetGroupByProperty, :ptr, :ptr
	STDMETHOD	GetViewMode, :ptr
	STDMETHOD	GetIconSize, :ptr
	STDMETHOD	GetFolderFlags, :ptr, :ptr
	STDMETHOD	GetSortColumns, :ptr, :UINT, :ptr
	STDMETHOD	GetGroupSubsetCount, :ptr


IFolderViewSettings	ENDS

endif ; __IFolderViewSettings_INTERFACE_DEFINED__
endif ; (NTDDI_VERSION GE NTDDI_VISTA)

if (_WIN32_IE GE _WIN32_IE_IE70)

externdef		__MIDL_itf_shobjidl_0000_0026_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0026_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IPreviewHandlerVisuals_INTERFACE_DEFINED__
__IPreviewHandlerVisuals_INTERFACE_DEFINED__ equ 1

externdef		IID_IPreviewHandlerVisuals:IID
IPreviewHandlerVisuals	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetBackgroundColor, :COLORREF
	STDMETHOD	SetFont, :ptr
	STDMETHOD	SetTextColor, :COLORREF


IPreviewHandlerVisuals	ENDS

endif

ifndef __IVisualProperties_INTERFACE_DEFINED__
__IVisualProperties_INTERFACE_DEFINED__ equ 1

VPWATERMARKFLAGS	typedef SDWORD
VPWF_DEFAULT		equ 0
VPWF_ALPHABLEND		equ 0x1

DEFINE_ENUM_FLAG_OPERATORS(VPWATERMARKFLAGS)
VPCOLORFLAGS		typedef SDWORD
VPCF_TEXT		equ 1
VPCF_BACKGROUND		equ 2
VPCF_SORTCOLUMN		equ 3
VPCF_SUBTEXT		equ 4
VPCF_TEXTBACKGROUND	equ 5

externdef		IID_IVisualProperties:IID
IVisualProperties	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetWatermark, :HBITMAP, :VPWATERMARKFLAGS
	STDMETHOD	SetColor, :VPCOLORFLAGS, :COLORREF
	STDMETHOD	GetColor, :VPCOLORFLAGS, :ptr
	STDMETHOD	SetItemHeight, :SINT
	STDMETHOD	GetItemHeight, :ptr
	STDMETHOD	SetFont, :ptr, :BOOL
	STDMETHOD	GetFont, :ptr
	STDMETHOD	SetTheme, :LPCWSTR, :LPCWSTR


IVisualProperties	ENDS

endif

endif

CDBOSC_SETFOCUS		equ 0x00000000
CDBOSC_KILLFOCUS	equ 0x00000001
CDBOSC_SELCHANGE	equ 0x00000002
CDBOSC_RENAME		equ 0x00000003
CDBOSC_STATECHANGE	equ 0x00000004

externdef		__MIDL_itf_shobjidl_0000_0028_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0028_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ICommDlgBrowser_INTERFACE_DEFINED__
__ICommDlgBrowser_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_ICommDlgBrowser, 0x000214f1, 0x0000, 0x0000, 0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46)

externdef		IID_ICommDlgBrowser:IID
ICommDlgBrowser		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	OnDefaultCommand, :ptr
	STDMETHOD	OnStateChange, :ptr, :ULONG
	STDMETHOD	IncludeObject, :ptr, :PCUITEMID_CHILD


ICommDlgBrowser		ENDS

endif

LPCOMMDLGBROWSER	typedef ptr ICommDlgBrowser

SID_SExplorerBrowserFrame equ IID_ICommDlgBrowser
if (NTDDI_VERSION GE NTDDI_WIN2K)
CDB2N_CONTEXTMENU_DONE	equ 0x00000001
CDB2N_CONTEXTMENU_START equ 0x00000002
CDB2GVF_SHOWALLFILES	equ 0x00000001
if (NTDDI_VERSION GE NTDDI_VISTA)
CDB2GVF_ISFILESAVE	equ 0x00000002
CDB2GVF_ALLOWPREVIEWPANE equ 0x00000004
CDB2GVF_NOSELECTVERB	equ 0x00000008
CDB2GVF_NOINCLUDEITEM	equ 0x00000010
CDB2GVF_ISFOLDERPICKER	equ 0x00000020
CDB2GVF_ADDSHIELD	equ 0x00000040
endif

externdef		__MIDL_itf_shobjidl_0000_0029_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0029_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ICommDlgBrowser2_INTERFACE_DEFINED__
__ICommDlgBrowser2_INTERFACE_DEFINED__ equ 1

externdef		IID_ICommDlgBrowser2:IID
ICommDlgBrowser2	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	OnDefaultCommand, :ptr
	STDMETHOD	OnStateChange, :ptr, :ULONG
	STDMETHOD	IncludeObject, :ptr, :PCUITEMID_CHILD
	STDMETHOD	Notify, :ptr, :DWORD
	STDMETHOD	GetDefaultMenuText, :ptr, :LPWSTR, :SINT
	STDMETHOD	GetViewFlags, :ptr


ICommDlgBrowser2	ENDS

endif

LPCOMMDLGBROWSER2	typedef ptr ICommDlgBrowser2

endif
if (_WIN32_IE GE _WIN32_IE_IE70)

externdef		__MIDL_itf_shobjidl_0000_0030_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0030_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ICommDlgBrowser3_INTERFACE_DEFINED__
__ICommDlgBrowser3_INTERFACE_DEFINED__ equ 1

externdef		IID_ICommDlgBrowser3:IID
ICommDlgBrowser3	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	OnDefaultCommand, :ptr
	STDMETHOD	OnStateChange, :ptr, :ULONG
	STDMETHOD	IncludeObject, :ptr, :PCUITEMID_CHILD
	STDMETHOD	Notify, :ptr, :DWORD
	STDMETHOD	GetDefaultMenuText, :ptr, :LPWSTR, :SINT
	STDMETHOD	GetViewFlags, :ptr
	STDMETHOD	OnColumnClicked, :ptr, :SINT
	STDMETHOD	GetCurrentFilter, :LPWSTR, :SINT
	STDMETHOD	OnPreViewCreated, :ptr


ICommDlgBrowser3	ENDS

endif

CM_MASK			typedef SDWORD
CM_MASK_WIDTH		equ 0x1
CM_MASK_DEFAULTWIDTH	equ 0x2
CM_MASK_IDEALWIDTH	equ 0x4
CM_MASK_NAME		equ 0x8
CM_MASK_STATE		equ 0x10

DEFINE_ENUM_FLAG_OPERATORS(CM_MASK)
CM_STATE		typedef SDWORD
CM_STATE_NONE		equ 0
CM_STATE_VISIBLE	equ 0x1
CM_STATE_FIXEDWIDTH	equ 0x2
CM_STATE_NOSORTBYFOLDERNESS equ 0x4
CM_STATE_ALWAYSVISIBLE	equ 0x8

DEFINE_ENUM_FLAG_OPERATORS(CM_STATE)
CM_ENUM_FLAGS		typedef SDWORD
CM_ENUM_ALL		equ 0x1
CM_ENUM_VISIBLE		equ 0x2

DEFINE_ENUM_FLAG_OPERATORS(CM_ENUM_FLAGS)
CM_SET_WIDTH_VALUE	typedef SDWORD
CM_WIDTH_USEDEFAULT	equ -1
CM_WIDTH_AUTOSIZE	equ -2

CM_COLUMNINFO		STRUC
cbSize			dd ?
dwMask			dd ?
dwState			dd ?
uWidth			UINT ?
uDefaultWidth		UINT ?
uIdealWidth		UINT ?
wszName			WCHAR  80  dup(?)
CM_COLUMNINFO		ENDS

externdef		__MIDL_itf_shobjidl_0000_0031_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0031_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IColumnManager_INTERFACE_DEFINED__
__IColumnManager_INTERFACE_DEFINED__ equ 1

externdef		IID_IColumnManager:IID
IColumnManager		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetColumnInfo, :REFPROPERTYKEY, :ptr
	STDMETHOD	GetColumnInfo, :REFPROPERTYKEY, :ptr
	STDMETHOD	GetColumnCount, :CM_ENUM_FLAGS, :ptr
	STDMETHOD	GetColumns, :CM_ENUM_FLAGS, :ptr, :UINT
	STDMETHOD	SetColumns, :ptr, :UINT


IColumnManager		ENDS

endif
endif

externdef		__MIDL_itf_shobjidl_0000_0032_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0032_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFolderFilterSite_INTERFACE_DEFINED__
__IFolderFilterSite_INTERFACE_DEFINED__ equ 1

externdef		IID_IFolderFilterSite:IID
IFolderFilterSite	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetFilter, :ptr


IFolderFilterSite	ENDS

endif

ifndef __IFolderFilter_INTERFACE_DEFINED__
__IFolderFilter_INTERFACE_DEFINED__ equ 1

externdef		IID_IFolderFilter:IID
IFolderFilter		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	ShouldShow, :ptr, :PCIDLIST_ABSOLUTE, :PCUITEMID_CHILD
	STDMETHOD	GetEnumFlags, :ptr, :PCIDLIST_ABSOLUTE, :ptr, :ptr


IFolderFilter		ENDS

endif

ifndef __IInputObjectSite_INTERFACE_DEFINED__
__IInputObjectSite_INTERFACE_DEFINED__ equ 1

externdef		IID_IInputObjectSite:IID
IInputObjectSite	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	OnFocusChangeIS, :ptr, :BOOL


IInputObjectSite	ENDS

endif

ifndef __IInputObject_INTERFACE_DEFINED__
__IInputObject_INTERFACE_DEFINED__ equ 1

externdef		IID_IInputObject:IID
IInputObject		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	UIActivateIO, :BOOL, :ptr
	STDMETHOD	HasFocusIO
	STDMETHOD	TranslateAcceleratorIO, :ptr


IInputObject		ENDS

endif

ifndef __IInputObject2_INTERFACE_DEFINED__
__IInputObject2_INTERFACE_DEFINED__ equ 1

externdef		IID_IInputObject2:IID
IInputObject2		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	UIActivateIO, :BOOL, :ptr
	STDMETHOD	HasFocusIO
	STDMETHOD	TranslateAcceleratorIO, :ptr
	STDMETHOD	TranslateAcceleratorGlobal, :ptr


IInputObject2		ENDS

endif

ifndef __IShellIcon_INTERFACE_DEFINED__
__IShellIcon_INTERFACE_DEFINED__ equ 1

externdef		IID_IShellIcon:IID
IShellIcon		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetIconOf, :PCUITEMID_CHILD, :UINT, :ptr


IShellIcon		ENDS

endif

SBSP_DEFBROWSER		equ 0x0000
SBSP_SAMEBROWSER	equ 0x0001
SBSP_NEWBROWSER		equ 0x0002
SBSP_DEFMODE		equ 0x0000
SBSP_OPENMODE		equ 0x0010
SBSP_EXPLOREMODE	equ 0x0020
SBSP_HELPMODE		equ 0x0040
SBSP_NOTRANSFERHIST	equ 0x0080
SBSP_ABSOLUTE		equ 0x0000
SBSP_RELATIVE		equ 0x1000
SBSP_PARENT		equ 0x2000
SBSP_NAVIGATEBACK	equ 0x4000
SBSP_NAVIGATEFORWARD	equ 0x8000
SBSP_ALLOW_AUTONAVIGATE equ 0x00010000
if (NTDDI_VERSION GE NTDDI_VISTA)
SBSP_KEEPSAMETEMPLATE	equ 0x00020000
SBSP_KEEPWORDWHEELTEXT	equ 0x00040000
SBSP_ACTIVATE_NOFOCUS	equ 0x00080000
SBSP_CREATENOHISTORY	equ 0x00100000
SBSP_PLAYNOSOUND	equ 0x00200000
endif
if (_WIN32_IE GE _WIN32_IE_IE60SP2)
SBSP_CALLERUNTRUSTED	equ 0x00800000
SBSP_TRUSTFIRSTDOWNLOAD equ 0x01000000
SBSP_UNTRUSTEDFORDOWNLOAD equ 0x02000000
endif
SBSP_NOAUTOSELECT	equ 0x04000000
SBSP_WRITENOHISTORY	equ 0x08000000
if (_WIN32_IE GE _WIN32_IE_IE60SP2)
SBSP_TRUSTEDFORACTIVEX	equ 0x10000000
endif
if (_WIN32_IE GE _WIN32_IE_IE70)
SBSP_FEEDNAVIGATION	equ 0x20000000
endif
SBSP_REDIRECT		equ 0x40000000
SBSP_INITIATEDBYHLINKFRAME equ 0x80000000
FCW_STATUS		equ 0x0001
FCW_TOOLBAR		equ 0x0002
FCW_TREE		equ 0x0003
FCW_INTERNETBAR		equ 0x0006
FCW_PROGRESS		equ 0x0008
if (_WIN32_IE GE 0x0700)
endif
FCT_MERGE		equ 0x0001
FCT_CONFIGABLE		equ 0x0002
FCT_ADDTOEND		equ 0x0004
ifdef _NEVER_
LPTBBUTTONSB		typedef LPARAM

else
include commctrl.inc
LPTBBUTTONSB		typedef LPTBBUTTON
endif


externdef		__MIDL_itf_shobjidl_0000_0038_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0038_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IShellBrowser_INTERFACE_DEFINED__
__IShellBrowser_INTERFACE_DEFINED__ equ 1

externdef		IID_IShellBrowser:IID
IShellBrowser		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow, :ptr
	STDMETHOD	ContextSensitiveHelp, :BOOL
	STDMETHOD	InsertMenusSB, :HMENU, :LPOLEMENUGROUPWIDTHS
	STDMETHOD	SetMenuSB, :HMENU, :HOLEMENU, :HWND
	STDMETHOD	RemoveMenusSB, :HMENU
	STDMETHOD	SetStatusTextSB, :LPCWSTR
	STDMETHOD	EnableModelessSB, :BOOL
	STDMETHOD	TranslateAcceleratorSB, :ptr, :WORD
	STDMETHOD	BrowseObject, :PCUIDLIST_RELATIVE, :UINT
	STDMETHOD	GetViewStateStream, :DWORD, :ptr
	STDMETHOD	GetControlWindow, :UINT, :ptr
	STDMETHOD	SendControlMsg, :UINT, :UINT, :WPARAM, :LPARAM, :ptr
	STDMETHOD	QueryActiveShellView, :ptr
	STDMETHOD	OnViewWindowActive, :ptr
	STDMETHOD	SetToolbarItems, :LPTBBUTTONSB, :UINT, :UINT


IShellBrowser		ENDS

endif

LPSHELLBROWSER		typedef ptr IShellBrowser

externdef		__MIDL_itf_shobjidl_0000_0039_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0039_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IProfferService_INTERFACE_DEFINED__
__IProfferService_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_IProfferService, 0xcb728b20, 0xf786, 0x11ce, 0x92,0xad, 0x00,0xaa,0x00,0xa7,0x4c,0xd0)

externdef		IID_IProfferService:IID
IProfferService		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	ProfferService, :REFGUID, :ptr, :ptr
	STDMETHOD	RevokeService, :DWORD


IProfferService		ENDS

endif

SID_SProfferService	equ IID_IProfferService
STR_DONT_RESOLVE_LINK	equ <L"Don't Resolve Link">
STR_GET_ASYNC_HANDLER	equ <L"GetAsyncHandler">

externdef		__MIDL_itf_shobjidl_0000_0040_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0040_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IShellItem_INTERFACE_DEFINED__
__IShellItem_INTERFACE_DEFINED__ equ 1

SIGDN			typedef SDWORD
SIGDN_NORMALDISPLAY		equ 0
SIGDN_PARENTRELATIVEPARSING	equ 0x80018001
SIGDN_DESKTOPABSOLUTEPARSING	equ 0x80028000
SIGDN_PARENTRELATIVEEDITING	equ 0x80031001
SIGDN_DESKTOPABSOLUTEEDITING	equ 0x8004c000
SIGDN_FILESYSPATH		equ 0x80058000
SIGDN_URL			equ 0x80068000
SIGDN_PARENTRELATIVEFORADDRESSBAR equ 0x8007c001
SIGDN_PARENTRELATIVE		equ 0x80080001


SICHINT_DISPLAY		equ 0
SICHINT_ALLFIELDS	equ 0x80000000
SICHINT_CANONICAL	equ 0x10000000
SICHINT_TEST_FILESYSPATH_IF_NOT_EQUAL equ 0x20000000
SICHINTF		typedef DWORD

externdef		IID_IShellItem:IID
IShellItem		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	BindToHandler, :ptr, :REFGUID, :REFIID, :ptr
	STDMETHOD	GetParent, :ptr
	STDMETHOD	GetDisplayName, :SIGDN, :ptr
	STDMETHOD	GetAttributes, :SFGAOF, :ptr
	STDMETHOD	Compare, :ptr, :SICHINTF, :ptr


IShellItem		ENDS
LPIShellItem		typedef ptr IShellItem

endif

;SHSTDAPI_(PIDLIST_ABSOLUTE)
SHSimpleIDListFromPath proto WINAPI \
	       pszPath: LPCWSTR

if (_WIN32_IE GE _WIN32_IE_IE70)
;SHSTDAPI
SHCreateItemFromIDList proto WINAPI \
		  pidl: PCIDLIST_ABSOLUTE,
		  riid: REFIID,
		   ppv: PVOID

;SHSTDAPI
SHCreateItemFromParsingName proto WINAPI \
	       pszPath: PCWSTR,
		   pbc: ptr IBindCtx,
		  riid: REFIID,
		   ppv: PVOID

;SHSTDAPI
SHCreateItemWithParent proto WINAPI \
	    pidlParent: PCIDLIST_ABSOLUTE,
	     psfParent: ptr IShellFolder,
		  pidl: PCUITEMID_CHILD,
		  riid: REFIID,
		   ppv: PVOID

;SHSTDAPI
SHCreateItemFromRelativeName proto WINAPI \
	     psiParent: ptr IShellItem,
	       pszName: PCWSTR,
		   pbc: ptr IBindCtx,
		  riid: REFIID,
		   ppv: PVOID

endif
if (NTDDI_VERSION GE NTDDI_VISTA)
;SHSTDAPI
SHCreateItemInKnownFolder proto WINAPI \
		  kfid: REFKNOWNFOLDERID,
	     dwKFFlags: DWORD,
	       pszItem: PCWSTR,
		  riid: REFIID,
		   ppv: PVOID

;SHSTDAPI
SHGetIDListFromObject proto WINAPI \
		  punk: ptr IUnknown,
		 ppidl: ptr PIDLIST_ABSOLUTE

;SHSTDAPI
SHGetItemFromObject proto WINAPI \
		  punk: ptr IUnknown,
		  riid: REFIID,
		   ppv: PVOID

;SHSTDAPI
SHGetPropertyStoreFromIDList proto WINAPI \
		  pidl: PCIDLIST_ABSOLUTE,
		 flags: GETPROPERTYSTOREFLAGS,
		  riid: REFIID,
		   ppv: PVOID

;SHSTDAPI
SHGetPropertyStoreFromParsingName proto WINAPI \
	       pszPath: PCWSTR,
		   pbc: ptr IBindCtx,
		 flags: GETPROPERTYSTOREFLAGS,
		  riid: REFIID,
		   ppv: PVOID

;SHSTDAPI
SHGetNameFromIDList proto WINAPI \
		  pidl: PCIDLIST_ABSOLUTE,
	     sigdnName: SIGDN,
	      ppszName: PWSTR

endif
if (NTDDI_VERSION GE NTDDI_WIN7)
DATAOBJ_GET_ITEM_FLAGS	typedef SDWORD
DOGIF_DEFAULT		equ 0
DOGIF_TRAVERSE_LINK	equ 0x1
DOGIF_NO_HDROP		equ 0x2
DOGIF_NO_URL		equ 0x4
DOGIF_ONLY_IF_ONE	equ 0x8

DEFINE_ENUM_FLAG_OPERATORS(DATAOBJ_GET_ITEM_FLAGS)
;STDAPI
SHGetItemFromDataObject proto WINAPI \
		pdtobj: ptr IDataObject,
	       dwFlags: DATAOBJ_GET_ITEM_FLAGS,
		  riid: REFIID,
		   ppv: PVOID

endif
STR_GPS_HANDLERPROPERTIESONLY equ <L"GPS_HANDLERPROPERTIESONLY">
STR_GPS_FASTPROPERTIESONLY equ <L"GPS_FASTPROPERTIESONLY">
STR_GPS_OPENSLOWITEM	equ <L"GPS_OPENSLOWITEM">
STR_GPS_DELAYCREATION	equ <L"GPS_DEAYCREATION">
STR_GPS_BESTEFFORT	equ <L"GPS_BESTEFFORT">
STR_GPS_NO_OPLOCK	equ <L"GPS_NO_OPLOCK">

externdef		__MIDL_itf_shobjidl_0000_0041_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0041_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IShellItem2_INTERFACE_DEFINED__
__IShellItem2_INTERFACE_DEFINED__ equ 1

externdef		IID_IShellItem2:IID
IShellItem2		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	BindToHandler, :ptr, :REFGUID, :REFIID, :ptr
	STDMETHOD	GetParent, :ptr
	STDMETHOD	GetDisplayName, :SIGDN, :ptr
	STDMETHOD	GetAttributes, :SFGAOF, :ptr
	STDMETHOD	Compare, :ptr, :SICHINTF, :ptr
	STDMETHOD	GetPropertyStore, :GETPROPERTYSTOREFLAGS, :REFIID, :ptr
	STDMETHOD	GetPropertyStoreWithCreateObject, :GETPROPERTYSTOREFLAGS, :ptr, :REFIID, :ptr
	STDMETHOD	GetPropertyStoreForKeys, :ptr, :UINT, :GETPROPERTYSTOREFLAGS, :REFIID, :ptr
	STDMETHOD	GetPropertyDescriptionList, :REFPROPERTYKEY, :REFIID, :ptr
	STDMETHOD	Update, :ptr
	STDMETHOD	GetProperty, :REFPROPERTYKEY, :ptr
	STDMETHOD	GetCLSID, :REFPROPERTYKEY, :ptr
	STDMETHOD	GetFileTime, :REFPROPERTYKEY, :ptr
	STDMETHOD	GetInt32, :REFPROPERTYKEY, :ptr
	STDMETHOD	GetString, :REFPROPERTYKEY, :ptr
	STDMETHOD	GetUInt32, :REFPROPERTYKEY, :ptr
	STDMETHOD	GetUInt64, :REFPROPERTYKEY, :ptr
	STDMETHOD	GetBool, :REFPROPERTYKEY, :ptr


IShellItem2		ENDS

endif

SIIGBF_RESIZETOFIT	equ 0
SIIGBF_BIGGERSIZEOK	equ 0x1
SIIGBF_MEMORYONLY	equ 0x2
SIIGBF_ICONONLY		equ 0x4
SIIGBF_THUMBNAILONLY	equ 0x8
SIIGBF_INCACHEONLY	equ 0x10
SIIGBF			typedef SINT

externdef		__MIDL_itf_shobjidl_0000_0042_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0042_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IShellItemImageFactory_INTERFACE_DEFINED__
__IShellItemImageFactory_INTERFACE_DEFINED__ equ 1

externdef		IID_IShellItemImageFactory:IID
IShellItemImageFactory	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetImage, :SIZEL, :SIIGBF, :ptr


IShellItemImageFactory	ENDS

endif

ifndef __IUserAccountChangeCallback_INTERFACE_DEFINED__
__IUserAccountChangeCallback_INTERFACE_DEFINED__ equ 1

externdef		IID_IUserAccountChangeCallback:IID
IUserAccountChangeCallback STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	OnPictureChange, :LPCWSTR


IUserAccountChangeCallback ENDS

endif

if (NTDDI_VERSION GE NTDDI_WINXP)

externdef		__MIDL_itf_shobjidl_0000_0044_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0044_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumShellItems_INTERFACE_DEFINED__
__IEnumShellItems_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumShellItems:IID
IEnumShellItems		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :ULONG, :ptr, :ptr
	STDMETHOD	Skip, :ULONG
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr


IEnumShellItems		ENDS
LPIEnumShellItems	typedef ptr IEnumShellItems

;STDMETHODCALLTYPE
IEnumShellItems_RemoteNext_Proxy proto WINAPI \
		 _This: ptr IEnumShellItems,
		  celt: ULONG,
		 rgelt: ptr IShellItem,
	  pceltFetched: LPULONG

;void
IEnumShellItems_RemoteNext_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

STGTRANSCONFIRMATION	typedef GUID
LPSTGTRANSCONFIRMATION	typedef ptr GUID
STGOP			typedef SDWORD
STGOP_MOVE		equ 1
STGOP_COPY		equ 2
STGOP_SYNC		equ 3
STGOP_REMOVE		equ 5
STGOP_RENAME		equ 6
STGOP_APPLYPROPERTIES	equ 8
STGOP_NEW		equ 10

endif

TSF_NORMAL		equ 0
TSF_FAIL_EXIST		equ 0
TSF_RENAME_EXIST	equ 0x1
TSF_OVERWRITE_EXIST	equ 0x2
TSF_ALLOW_DECRYPTION	equ 0x4
TSF_NO_SECURITY		equ 0x8
TSF_COPY_CREATION_TIME	equ 0x10
TSF_COPY_WRITE_TIME	equ 0x20
TSF_USE_FULL_ACCESS	equ 0x40
TSF_DELETE_RECYCLE_IF_POSSIBLE equ 0x80
TSF_COPY_HARD_LINK	equ 0x100
TSF_COPY_LOCALIZED_NAME equ 0x200
TSF_MOVE_AS_COPY_DELETE equ 0x400
TSF_SUSPEND_SHELLEVENTS equ 0x800
TRANSFER_SOURCE_FLAGS	typedef DWORD

if (_WIN32_IE GE _WIN32_IE_IE70)

externdef		__MIDL_itf_shobjidl_0000_0045_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0045_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ITransferAdviseSink_INTERFACE_DEFINED__
__ITransferAdviseSink_INTERFACE_DEFINED__ equ 1

TS_NONE			equ 0
TS_PERFORMING		equ 0x1
TS_PREPARING		equ 0x2
TS_INDETERMINATE	equ 0x4
TRANSFER_ADVISE_STATE	typedef DWORD

externdef		IID_ITransferAdviseSink:IID
ITransferAdviseSink	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	UpdateProgress, :ULONGLONG, :ULONGLONG, :SINT, :SINT, :SINT, :SINT
	STDMETHOD	UpdateTransferState, :TRANSFER_ADVISE_STATE
	STDMETHOD	ConfirmOverwrite, :ptr, :ptr, :LPCWSTR
	STDMETHOD	ConfirmEncryptionLoss, :ptr
	STDMETHOD	FileFailure, :ptr, :LPCWSTR, :HRESULT, :LPWSTR, :ULONG
	STDMETHOD	SubStreamFailure, :ptr, :LPCWSTR, :HRESULT
	STDMETHOD	PropertyFailure, :ptr, :ptr, :HRESULT


ITransferAdviseSink	ENDS

endif

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

externdef		__MIDL_itf_shobjidl_0000_0046_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0046_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ITransferSource_INTERFACE_DEFINED__
__ITransferSource_INTERFACE_DEFINED__ equ 1

externdef		IID_ITransferSource:IID
ITransferSource		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Advise, :ptr, :ptr
	STDMETHOD	Unadvise, :DWORD
	STDMETHOD	SetProperties, :ptr
	STDMETHOD	OpenItem, :ptr, :TRANSFER_SOURCE_FLAGS, :REFIID, :ptr
	STDMETHOD	MoveItem, :ptr, :ptr, :LPCWSTR, :TRANSFER_SOURCE_FLAGS, :ptr
	STDMETHOD	RecycleItem, :ptr, :ptr, :TRANSFER_SOURCE_FLAGS, :ptr
	STDMETHOD	RemoveItem, :ptr, :TRANSFER_SOURCE_FLAGS
	STDMETHOD	RenameItem, :ptr, :LPCWSTR, :TRANSFER_SOURCE_FLAGS, :ptr
	STDMETHOD	LinkItem, :ptr, :ptr, :LPCWSTR, :TRANSFER_SOURCE_FLAGS, :ptr
	STDMETHOD	ApplyPropertiesToItem, :ptr, :ptr
	STDMETHOD	GetDefaultDestinationName, :ptr, :ptr, :ptr
	STDMETHOD	EnterFolder, :ptr
	STDMETHOD	LeaveFolder, :ptr


ITransferSource		ENDS

endif
endif

SHELL_ITEM_RESOURCE	STRUC
guidType		GUID <>
szName			WCHAR  260  dup(?)
SHELL_ITEM_RESOURCE	ENDS

externdef		__MIDL_itf_shobjidl_0000_0047_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0047_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumResources_INTERFACE_DEFINED__
__IEnumResources_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumResources:IID
IEnumResources		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :ULONG, :ptr, :ptr
	STDMETHOD	Skip, :ULONG
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr


IEnumResources		ENDS

endif

ifndef __IShellItemResources_INTERFACE_DEFINED__
__IShellItemResources_INTERFACE_DEFINED__ equ 1

externdef		IID_IShellItemResources:IID
IShellItemResources	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetAttributes, :ptr
	STDMETHOD	GetSize, :ptr
	STDMETHOD	GetTimes, :ptr, :ptr, :ptr
	STDMETHOD	SetTimes, :ptr, :ptr, :ptr
	STDMETHOD	GetResourceDescription, :ptr, :ptr
	STDMETHOD	EnumResources, :ptr
	STDMETHOD	SupportsResource, :ptr
	STDMETHOD	OpenResource, :ptr, :REFIID, :ptr
	STDMETHOD	CreateResource, :ptr, :REFIID, :ptr
	STDMETHOD	MarkForDelete


IShellItemResources	ENDS

endif

ifndef __ITransferDestination_INTERFACE_DEFINED__
__ITransferDestination_INTERFACE_DEFINED__ equ 1

externdef		IID_ITransferDestination:IID
ITransferDestination	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Advise, :ptr, :ptr
	STDMETHOD	Unadvise, :DWORD
	STDMETHOD	CreateItem, :LPCWSTR, :DWORD, :ULONGLONG, :TRANSFER_SOURCE_FLAGS, :REFIID, :ptr, :REFIID, :ptr


ITransferDestination	ENDS

endif

ifdef MIDL_PASS
OVERLAPPED		STRUC
Internal		ULONG_PTR ?
InternalHigh		ULONG_PTR ?
UNION
 STRUC
  Offset		dd ?
  OffsetHigh		dd ?
 ENDS
 Pointer		PVOID ?
ENDS
hEvent			HANDLE ?
OVERLAPPED		ENDS
LPOVERLAPPED		typedef ptr OVERLAPPED

endif

externdef		__MIDL_itf_shobjidl_0000_0050_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0050_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IStreamAsync_INTERFACE_DEFINED__
__IStreamAsync_INTERFACE_DEFINED__ equ 1

externdef		IID_IStreamAsync:IID
IStreamAsync		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Read, :ptr, :ULONG, :ptr
	STDMETHOD	Write, :ptr, :ULONG, :ptr
	STDMETHOD	Seek, :LARGE_INTEGER, :DWORD, :ptr
	STDMETHOD	SetSize, :ULARGE_INTEGER
	STDMETHOD	CopyTo, :ptr, :ULARGE_INTEGER, :ptr, :ptr
	STDMETHOD	Commit, :DWORD
	STDMETHOD	Revert
	STDMETHOD	LockRegion, :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
	STDMETHOD	UnlockRegion, :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
	STDMETHOD	Stat, :ptr, :DWORD
	STDMETHOD	Clone, :ptr
	STDMETHOD	ReadAsync, :ptr, :DWORD, :LPDWORD, :LPOVERLAPPED
	STDMETHOD	WriteAsync, :ptr, :DWORD, :LPDWORD, :LPOVERLAPPED
	STDMETHOD	OverlappedResult, :LPOVERLAPPED, :LPDWORD, :BOOL
	STDMETHOD	CancelIo


IStreamAsync		ENDS

endif

ifndef __IStreamUnbufferedInfo_INTERFACE_DEFINED__
__IStreamUnbufferedInfo_INTERFACE_DEFINED__ equ 1

externdef		IID_IStreamUnbufferedInfo:IID
IStreamUnbufferedInfo	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetSectorSize, :ptr


IStreamUnbufferedInfo	ENDS

endif

if (_WIN32_IE GE _WIN32_IE_IE70)

externdef		__MIDL_itf_shobjidl_0000_0052_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0052_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFileOperationProgressSink_INTERFACE_DEFINED__
__IFileOperationProgressSink_INTERFACE_DEFINED__ equ 1

externdef		IID_IFileOperationProgressSink:IID
IFileOperationProgressSink STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	StartOperations
	STDMETHOD	FinishOperations, :HRESULT
	STDMETHOD	PreRenameItem, :DWORD, :ptr, :LPCWSTR
	STDMETHOD	PostRenameItem, :DWORD, :ptr, :LPCWSTR, :HRESULT, :ptr
	STDMETHOD	PreMoveItem, :DWORD, :ptr, :ptr, :LPCWSTR
	STDMETHOD	PostMoveItem, :DWORD, :ptr, :ptr, :LPCWSTR, :HRESULT, :ptr
	STDMETHOD	PreCopyItem, :DWORD, :ptr, :ptr, :LPCWSTR
	STDMETHOD	PostCopyItem, :DWORD, :ptr, :ptr, :LPCWSTR, :HRESULT, :ptr
	STDMETHOD	PreDeleteItem, :DWORD, :ptr
	STDMETHOD	PostDeleteItem, :DWORD, :ptr, :HRESULT, :ptr
	STDMETHOD	PreNewItem, :DWORD, :ptr, :LPCWSTR
	STDMETHOD	PostNewItem, :DWORD, :ptr, :LPCWSTR, :LPCWSTR, :DWORD, :HRESULT, :ptr
	STDMETHOD	UpdateProgress, :UINT, :UINT
	STDMETHOD	ResetTimer
	STDMETHOD	PauseTimer
	STDMETHOD	ResumeTimer


IFileOperationProgressSink ENDS

endif
endif

externdef		__MIDL_itf_shobjidl_0000_0053_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0053_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IShellItemArray_INTERFACE_DEFINED__
__IShellItemArray_INTERFACE_DEFINED__ equ 1

SIATTRIBFLAGS		typedef DWORD
SIATTRIBFLAGS_AND	equ 0x1
SIATTRIBFLAGS_OR	equ 0x2
SIATTRIBFLAGS_APPCOMPAT equ 0x3
SIATTRIBFLAGS_MASK	equ 0x3
SIATTRIBFLAGS_ALLITEMS	equ 0x4000

DEFINE_ENUM_FLAG_OPERATORS(SIATTRIBFLAGS)

externdef		IID_IShellItemArray:IID
IShellItemArray		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	BindToHandler, :ptr, :REFGUID, :REFIID, :ptr
	STDMETHOD	GetPropertyStore, :GETPROPERTYSTOREFLAGS, :REFIID, :ptr
	STDMETHOD	GetPropertyDescriptionList, :REFPROPERTYKEY, :REFIID, :ptr
	STDMETHOD	GetAttributes, :SIATTRIBFLAGS, :SFGAOF, :ptr
	STDMETHOD	GetCount, :ptr
	STDMETHOD	GetItemAt, :DWORD, :ptr
	STDMETHOD	EnumItems, :ptr


IShellItemArray		ENDS

endif

if (_WIN32_IE GE _WIN32_IE_IE70)
;SHSTDAPI
SHCreateShellItemArray proto WINAPI \
	    pidlParent: PCIDLIST_ABSOLUTE,
		   psf: ptr IShellFolder,
		  cidl: UINT,
		 ppidl: PCUITEMID_CHILD_ARRAY,
	 ppsiItemArray: ptr IShellItemArray

;SHSTDAPI
SHCreateShellItemArrayFromDataObject proto WINAPI \
		   pdo: ptr IDataObject,
		  riid: REFIID,
		   ppv: PVOID
;SHSTDAPI
SHCreateShellItemArrayFromIDLists proto WINAPI \
		  cidl: UINT,
		rgpidl: PCIDLIST_ABSOLUTE_ARRAY,
	 ppsiItemArray: ptr IShellItemArray

;SHSTDAPI
SHCreateShellItemArrayFromShellItem proto WINAPI \
		   psi: ptr IShellItem,
		  riid: REFIID,
		   ppv: PVOID

endif


externdef		__MIDL_itf_shobjidl_0000_0054_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0054_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInitializeWithItem_INTERFACE_DEFINED__
__IInitializeWithItem_INTERFACE_DEFINED__ equ 1

externdef		IID_IInitializeWithItem:IID
IInitializeWithItem	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Initialize, :ptr, :DWORD


IInitializeWithItem	ENDS

endif

ifndef __IObjectWithSelection_INTERFACE_DEFINED__
__IObjectWithSelection_INTERFACE_DEFINED__ equ 1

externdef		IID_IObjectWithSelection:IID
IObjectWithSelection	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetSelection, :ptr
	STDMETHOD	GetSelection, :REFIID, :ptr


IObjectWithSelection	ENDS

endif

ifndef __IObjectWithBackReferences_INTERFACE_DEFINED__
__IObjectWithBackReferences_INTERFACE_DEFINED__ equ 1

externdef		IID_IObjectWithBackReferences:IID
IObjectWithBackReferences STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	RemoveBackReferences


IObjectWithBackReferences ENDS

endif

PUIFNF_DEFAULT		equ 0
PUIFNF_MNEMONIC		equ 0x1
PROPERTYUI_NAME_FLAGS	typedef DWORD

PUIF_DEFAULT		equ 0
PUIF_RIGHTALIGN		equ 0x1
PUIF_NOLABELININFOTIP	equ 0x2
PROPERTYUI_FLAGS	typedef DWORD

PUIFFDF_DEFAULT		equ 0
PUIFFDF_RIGHTTOLEFT	equ 0x1
PUIFFDF_SHORTFORMAT	equ 0x2
PUIFFDF_NOTIME		equ 0x4
PUIFFDF_FRIENDLYDATE	equ 0x8
PROPERTYUI_FORMAT_FLAGS typedef DWORD

externdef		__MIDL_itf_shobjidl_0000_0057_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0057_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IPropertyUI_INTERFACE_DEFINED__
__IPropertyUI_INTERFACE_DEFINED__ equ 1

externdef		IID_IPropertyUI:IID
IPropertyUI		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	ParsePropertyName, :LPCWSTR, :ptr, :ptr, :ptr
	STDMETHOD	GetCannonicalName, :REFFMTID, :PROPID, :LPWSTR, :DWORD
	STDMETHOD	GetDisplayName, :REFFMTID, :PROPID, :PROPERTYUI_NAME_FLAGS, :LPWSTR, :DWORD
	STDMETHOD	GetPropertyDescription, :REFFMTID, :PROPID, :LPWSTR, :DWORD
	STDMETHOD	GetDefaultWidth, :REFFMTID, :PROPID, :ptr
	STDMETHOD	GetFlags, :REFFMTID, :PROPID, :ptr
	STDMETHOD	FormatForDisplay, :REFFMTID, :PROPID, :ptr, :PROPERTYUI_FORMAT_FLAGS, :LPWSTR, :DWORD
	STDMETHOD	GetHelpInfo, :REFFMTID, :PROPID, :LPWSTR, :DWORD, :ptr


IPropertyUI		ENDS

endif

if (_WIN32_IE GE _WIN32_IE_IE70)
;SHSTDAPI
SHRemovePersonalPropertyValues proto WINAPI \
		  psia: ptr IShellItemArray

;SHSTDAPI
SHAddDefaultPropertiesByExt proto WINAPI \
		pszExt: PCWSTR,
	    pPropStore: ptr IPropertyStore

;SHSTDAPI
SHCreateDefaultPropertiesOp proto WINAPI \
		   psi: ptr IShellItem,
	      ppFileOp: ptr IFileOperation

;SHSTDAPI
SHSetDefaultProperties proto WINAPI \
		  hwnd: HWND,
		   psi: ptr IShellItem,
	 dwFileOpFlags: DWORD,
		 pfops: ptr IFileOperationProgressSink

endif
if (_WIN32_IE GE 0x0500)

externdef		__MIDL_itf_shobjidl_0000_0058_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0058_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ICategoryProvider_INTERFACE_DEFINED__
__ICategoryProvider_INTERFACE_DEFINED__ equ 1

externdef		IID_ICategoryProvider:IID
ICategoryProvider	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	CanCategorizeOnSCID, :ptr
	STDMETHOD	GetDefaultCategory, :ptr, :ptr
	STDMETHOD	GetCategoryForSCID, :ptr, :ptr
	STDMETHOD	EnumCategories, :ptr
	STDMETHOD	GetCategoryName, :ptr, :LPWSTR, :UINT
	STDMETHOD	CreateCategory, :ptr, :REFIID, :ptr


ICategoryProvider	ENDS

endif

CATEGORYINFO_FLAGS	typedef SDWORD
CATINFO_NORMAL		equ 0
CATINFO_COLLAPSED	equ 0x1
CATINFO_HIDDEN		equ 0x2
CATINFO_EXPANDED	equ 0x4
CATINFO_NOHEADER	equ 0x8
CATINFO_NOTCOLLAPSIBLE	equ 0x10
CATINFO_NOHEADERCOUNT	equ 0x20
CATINFO_SUBSETTED	equ 0x40

DEFINE_ENUM_FLAG_OPERATORS(CATEGORYINFO_FLAGS)
CATSORT_FLAGS		typedef SDWORD
CATSORT_DEFAULT		equ 0
CATSORT_NAME		equ 0x1

DEFINE_ENUM_FLAG_OPERATORS(CATSORT_FLAGS)
CATEGORY_INFO		STRUC
cif			CATEGORYINFO_FLAGS ?
wszName			WCHAR  260  dup(?)
CATEGORY_INFO		ENDS

externdef		__MIDL_itf_shobjidl_0000_0059_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0059_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ICategorizer_INTERFACE_DEFINED__
__ICategorizer_INTERFACE_DEFINED__ equ 1

externdef		IID_ICategorizer:IID
ICategorizer		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDescription, :LPWSTR, :UINT
	STDMETHOD	GetCategory, :UINT, :PCUITEMID_CHILD_ARRAY, :ptr
	STDMETHOD	GetCategoryInfo, :DWORD, :ptr
	STDMETHOD	CompareCategory, :CATSORT_FLAGS, :DWORD, :DWORD


ICategorizer		ENDS

endif

endif
if (NTDDI_VERSION GE NTDDI_WIN2K)
;include pshpack8.inc
SHDRAGIMAGE		STRUC
sizeDragImage		SIZEL <>
ptOffset		POINT <>
hbmpDragImage		HBITMAP ?
crColorKey		COLORREF ?
SHDRAGIMAGE		ENDS

LPSHDRAGIMAGE		typedef ptr SHDRAGIMAGE

;include poppack.inc
DI_GETDRAGIMAGE		equ TEXT("ShellGetDragImage")

externdef		__MIDL_itf_shobjidl_0000_0060_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0060_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDropTargetHelper_INTERFACE_DEFINED__
__IDropTargetHelper_INTERFACE_DEFINED__ equ 1

externdef		IID_IDropTargetHelper:IID
IDropTargetHelper	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	DragEnter, :HWND, :ptr, :ptr, :DWORD
	STDMETHOD	DragLeave
	STDMETHOD	DragOver, :ptr, :DWORD
	STDMETHOD	Drop, :ptr, :ptr, :DWORD
	STDMETHOD	Show, :BOOL


IDropTargetHelper	ENDS

endif

ifndef __IDragSourceHelper_INTERFACE_DEFINED__
__IDragSourceHelper_INTERFACE_DEFINED__ equ 1

externdef		IID_IDragSourceHelper:IID
IDragSourceHelper	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	InitializeFromBitmap, :LPSHDRAGIMAGE, :ptr
	STDMETHOD	InitializeFromWindow, :HWND, :ptr, :ptr


IDragSourceHelper	ENDS

endif

if (NTDDI_VERSION GE NTDDI_VISTA)
DSH_FLAGS		typedef SDWORD
DSH_ALLOWDROPDESCRIPTIONTEXT	equ 0x1

DEFINE_ENUM_FLAG_OPERATORS(DSH_FLAGS)

externdef		__MIDL_itf_shobjidl_0000_0062_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0062_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDragSourceHelper2_INTERFACE_DEFINED__
__IDragSourceHelper2_INTERFACE_DEFINED__ equ 1

externdef		IID_IDragSourceHelper2:IID
IDragSourceHelper2	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	InitializeFromBitmap, :LPSHDRAGIMAGE, :ptr
	STDMETHOD	InitializeFromWindow, :HWND, :ptr, :ptr
	STDMETHOD	SetFlags, :DWORD


IDragSourceHelper2	ENDS

endif
endif
endif

ifdef _UNICODE
IShellLink		equ <IShellLinkW>
else
IShellLink		equ <IShellLinkA>
endif
SLR_FLAGS		typedef SDWORD
SLR_NO_UI		equ 0x1
SLR_ANY_MATCH		equ 0x2
SLR_UPDATE		equ 0x4
SLR_NOUPDATE		equ 0x8
SLR_NOSEARCH		equ 0x10
SLR_NOTRACK		equ 0x20
SLR_NOLINKINFO		equ 0x40
SLR_INVOKE_MSI		equ 0x80
SLR_NO_UI_WITH_MSG_PUMP equ 0x101
SLR_OFFER_DELETE_WITHOUT_FILE equ 0x200
SLR_KNOWNFOLDER		equ 0x400
SLR_MACHINE_IN_LOCAL_TARGET equ 0x800
SLR_UPDATE_MACHINE_AND_SID equ 0x1000

DEFINE_ENUM_FLAG_OPERATORS(SLR_FLAGS)
SLGP_FLAGS		typedef SDWORD
SLGP_SHORTPATH		equ 0x1
SLGP_UNCPRIORITY	equ 0x2
SLGP_RAWPATH		equ 0x4
SLGP_RELATIVEPRIORITY	equ 0x8

DEFINE_ENUM_FLAG_OPERATORS(SLGP_FLAGS)

externdef		__MIDL_itf_shobjidl_0000_0063_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0063_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IShellLinkA_INTERFACE_DEFINED__
__IShellLinkA_INTERFACE_DEFINED__ equ 1

externdef		IID_IShellLinkA:IID
IShellLinkA		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetPath, :LPSTR, :SINT, :ptr, :DWORD
	STDMETHOD	GetIDList, :ptr
	STDMETHOD	SetIDList, :PCIDLIST_ABSOLUTE
	STDMETHOD	GetDescription, :LPSTR, :SINT
	STDMETHOD	SetDescription, :LPCSTR
	STDMETHOD	GetWorkingDirectory, :LPSTR, :SINT
	STDMETHOD	SetWorkingDirectory, :LPCSTR
	STDMETHOD	GetArguments, :LPSTR, :SINT
	STDMETHOD	SetArguments, :LPCSTR
	STDMETHOD	GetHotkey, :ptr
	STDMETHOD	SetHotkey, :WORD
	STDMETHOD	GetShowCmd, :ptr
	STDMETHOD	SetShowCmd, :SINT
	STDMETHOD	GetIconLocation, :LPSTR, :SINT, :ptr
	STDMETHOD	SetIconLocation, :LPCSTR, :SINT
	STDMETHOD	SetRelativePath, :LPCSTR, :DWORD
	STDMETHOD	Resolve, :HWND, :DWORD
	STDMETHOD	SetPath, :LPCSTR


IShellLinkA		ENDS

endif

ifndef __IShellLinkW_INTERFACE_DEFINED__
__IShellLinkW_INTERFACE_DEFINED__ equ 1

externdef		IID_IShellLinkW:IID
IShellLinkW		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetPath, :LPWSTR, :SINT, :ptr, :DWORD
	STDMETHOD	GetIDList, :ptr
	STDMETHOD	SetIDList, :PCIDLIST_ABSOLUTE
	STDMETHOD	GetDescription, :LPWSTR, :SINT
	STDMETHOD	SetDescription, :LPCWSTR
	STDMETHOD	GetWorkingDirectory, :LPWSTR, :SINT
	STDMETHOD	SetWorkingDirectory, :LPCWSTR
	STDMETHOD	GetArguments, :LPWSTR, :SINT
	STDMETHOD	SetArguments, :LPCWSTR
	STDMETHOD	GetHotkey, :ptr
	STDMETHOD	SetHotkey, :WORD
	STDMETHOD	GetShowCmd, :ptr
	STDMETHOD	SetShowCmd, :SINT
	STDMETHOD	GetIconLocation, :LPWSTR, :SINT, :ptr
	STDMETHOD	SetIconLocation, :LPCWSTR, :SINT
	STDMETHOD	SetRelativePath, :LPCWSTR, :DWORD
	STDMETHOD	Resolve, :HWND, :DWORD
	STDMETHOD	SetPath, :LPCWSTR


IShellLinkW		ENDS

endif

ifndef __IShellLinkDataList_INTERFACE_DEFINED__
__IShellLinkDataList_INTERFACE_DEFINED__ equ 1

externdef		IID_IShellLinkDataList:IID
IShellLinkDataList	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	AddDataBlock, :ptr
	STDMETHOD	CopyDataBlock, :DWORD, :ptr
	STDMETHOD	RemoveDataBlock, :DWORD
	STDMETHOD	GetFlags, :ptr
	STDMETHOD	SetFlags, :DWORD


IShellLinkDataList	ENDS

endif

if (NTDDI_VERSION GE NTDDI_WIN2K)

externdef		__MIDL_itf_shobjidl_0000_0066_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0066_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IResolveShellLink_INTERFACE_DEFINED__
__IResolveShellLink_INTERFACE_DEFINED__ equ 1

externdef		IID_IResolveShellLink:IID
IResolveShellLink	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	ResolveShellLink, :ptr, :HWND, :DWORD


IResolveShellLink	ENDS

endif
endif

externdef		__MIDL_itf_shobjidl_0000_0067_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0067_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IActionProgressDialog_INTERFACE_DEFINED__
__IActionProgressDialog_INTERFACE_DEFINED__ equ 1

SPINITF_NORMAL		equ 0
SPINITF_MODAL		equ 0x1
SPINITF_NOMINIMIZE	equ 0x8
SPINITF			typedef DWORD

externdef		IID_IActionProgressDialog:IID
IActionProgressDialog	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Initialize, :SPINITF, :LPCWSTR, :LPCWSTR
	STDMETHOD	Stop


IActionProgressDialog	ENDS

endif

ifndef __IHWEventHandler_INTERFACE_DEFINED__
__IHWEventHandler_INTERFACE_DEFINED__ equ 1

externdef		IID_IHWEventHandler:IID
IHWEventHandler		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Initialize, :LPCWSTR
	STDMETHOD	HandleEvent, :LPCWSTR, :LPCWSTR, :LPCWSTR
	STDMETHOD	HandleEventWithContent, :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPCWSTR, :ptr


IHWEventHandler		ENDS

endif

ifndef __IHWEventHandler2_INTERFACE_DEFINED__
__IHWEventHandler2_INTERFACE_DEFINED__ equ 1

externdef		IID_IHWEventHandler2:IID
IHWEventHandler2	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Initialize, :LPCWSTR
	STDMETHOD	HandleEvent, :LPCWSTR, :LPCWSTR, :LPCWSTR
	STDMETHOD	HandleEventWithContent, :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPCWSTR, :ptr
	STDMETHOD	HandleEventWithHWND, :LPCWSTR, :LPCWSTR, :LPCWSTR, :HWND


IHWEventHandler2	ENDS

endif

ARCONTENT_AUTORUNINF	equ 0x00000002
ARCONTENT_AUDIOCD	equ 0x00000004
ARCONTENT_DVDMOVIE	equ 0x00000008
ARCONTENT_BLANKCD	equ 0x00000010
ARCONTENT_BLANKDVD	equ 0x00000020
ARCONTENT_UNKNOWNCONTENT equ 0x00000040
ARCONTENT_AUTOPLAYPIX	equ 0x00000080
ARCONTENT_AUTOPLAYMUSIC equ 0x00000100
ARCONTENT_AUTOPLAYVIDEO equ 0x00000200
if (NTDDI_VERSION GE NTDDI_VISTA)
ARCONTENT_VCD		equ 0x00000400
ARCONTENT_SVCD		equ 0x00000800
ARCONTENT_DVDAUDIO	equ 0x00001000
ARCONTENT_BLANKBD	equ 0x00002000
ARCONTENT_BLURAY	equ 0x00004000
ARCONTENT_NONE		equ 0x00000000
ARCONTENT_MASK		equ 0x00007FFE
ARCONTENT_PHASE_UNKNOWN equ 0x00000000
ARCONTENT_PHASE_PRESNIFF equ 0x10000000
ARCONTENT_PHASE_SNIFFING equ 0x20000000
ARCONTENT_PHASE_FINAL	equ 0x40000000
ARCONTENT_PHASE_MASK	equ 0x70000000
endif

externdef		__MIDL_itf_shobjidl_0000_0070_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0070_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IQueryCancelAutoPlay_INTERFACE_DEFINED__
__IQueryCancelAutoPlay_INTERFACE_DEFINED__ equ 1

externdef		IID_IQueryCancelAutoPlay:IID
IQueryCancelAutoPlay	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	AllowAutoPlay, :LPCWSTR, :DWORD, :LPCWSTR, :DWORD


IQueryCancelAutoPlay	ENDS

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

externdef		__MIDL_itf_shobjidl_0000_0071_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0071_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDynamicHWHandler_INTERFACE_DEFINED__
__IDynamicHWHandler_INTERFACE_DEFINED__ equ 1

externdef		IID_IDynamicHWHandler:IID
IDynamicHWHandler	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDynamicInfo, :LPCWSTR, :DWORD, :ptr


IDynamicHWHandler	ENDS

endif
endif

externdef		__MIDL_itf_shobjidl_0000_0072_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0072_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IActionProgress_INTERFACE_DEFINED__
__IActionProgress_INTERFACE_DEFINED__ equ 1

SPBEGINF_NORMAL		equ 0
SPBEGINF_AUTOTIME	equ 0x2
SPBEGINF_NOPROGRESSBAR	equ 0x10
SPBEGINF_MARQUEEPROGRESS equ 0x20
SPBEGINF_NOCANCELBUTTON equ 0x40
SPBEGINF		typedef DWORD

SPACTION		typedef SDWORD
SPACTION_NONE		equ 0
SPACTION_MOVING		equ ( SPACTION_NONE + 1 )
SPACTION_COPYING	equ ( SPACTION_MOVING + 1 )
SPACTION_RECYCLING	equ ( SPACTION_COPYING + 1 )
SPACTION_APPLYINGATTRIBS equ ( SPACTION_RECYCLING + 1 )
SPACTION_DOWNLOADING	equ ( SPACTION_APPLYINGATTRIBS + 1 )
SPACTION_SEARCHING_INTERNET equ ( SPACTION_DOWNLOADING + 1 )
SPACTION_CALCULATING	equ ( SPACTION_SEARCHING_INTERNET + 1 )
SPACTION_UPLOADING	equ ( SPACTION_CALCULATING + 1 )
SPACTION_SEARCHING_FILES equ ( SPACTION_UPLOADING + 1 )
SPACTION_DELETING	equ ( SPACTION_SEARCHING_FILES + 1 )
SPACTION_RENAMING	equ ( SPACTION_DELETING + 1 )
SPACTION_FORMATTING	equ ( SPACTION_RENAMING + 1 )
SPACTION_COPY_MOVING	equ ( SPACTION_FORMATTING + 1 )

SPTEXT			typedef SDWORD
SPTEXT_ACTIONDESCRIPTION equ 1
SPTEXT_ACTIONDETAIL	equ ( SPTEXT_ACTIONDESCRIPTION + 1 )

externdef		IID_IActionProgress:IID
IActionProgress		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Begin, :SPACTION, :SPBEGINF
	STDMETHOD	UpdateProgress, :ULONGLONG, :ULONGLONG
	STDMETHOD	UpdateText, :SPTEXT, :LPCWSTR, :BOOL
	STDMETHOD	QueryCancel, :ptr
	STDMETHOD	ResetCancel
	STDMETHOD	_End


IActionProgress		ENDS

endif

ifndef __IShellExtInit_INTERFACE_DEFINED__
__IShellExtInit_INTERFACE_DEFINED__ equ 1

externdef		IID_IShellExtInit:IID
IShellExtInit		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Initialize, :PCIDLIST_ABSOLUTE, :ptr, :HKEY


IShellExtInit		ENDS

endif

LPSHELLEXTINIT		typedef ptr IShellExtInit

externdef		__MIDL_itf_shobjidl_0000_0074_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0074_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IShellPropSheetExt_INTERFACE_DEFINED__
__IShellPropSheetExt_INTERFACE_DEFINED__ equ 1

EXPPS_FILETYPES		equ 0x1
EXPPS			typedef UINT

externdef		IID_IShellPropSheetExt:IID
IShellPropSheetExt	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	AddPages, :LPFNSVADDPROPSHEETPAGE, :LPARAM
	STDMETHOD	ReplacePage, :EXPPS, :LPFNSVADDPROPSHEETPAGE, :LPARAM


IShellPropSheetExt	ENDS

endif

LPSHELLPROPSHEETEXT	typedef ptr IShellPropSheetExt

externdef		__MIDL_itf_shobjidl_0000_0075_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0075_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IRemoteComputer_INTERFACE_DEFINED__
__IRemoteComputer_INTERFACE_DEFINED__ equ 1

externdef		IID_IRemoteComputer:IID
IRemoteComputer		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Initialize, :LPCWSTR, :BOOL


IRemoteComputer		ENDS

endif

ifndef __IQueryContinue_INTERFACE_DEFINED__
__IQueryContinue_INTERFACE_DEFINED__ equ 1

externdef		IID_IQueryContinue:IID
IQueryContinue		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	QueryContinue


IQueryContinue		ENDS

endif

ifndef __IObjectWithCancelEvent_INTERFACE_DEFINED__
__IObjectWithCancelEvent_INTERFACE_DEFINED__ equ 1

externdef		IID_IObjectWithCancelEvent:IID
IObjectWithCancelEvent	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetCancelEvent, :ptr


IObjectWithCancelEvent	ENDS

endif

ifndef __IUserNotification_INTERFACE_DEFINED__
__IUserNotification_INTERFACE_DEFINED__ equ 1

externdef		IID_IUserNotification:IID
IUserNotification	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetBalloonInfo, :LPCWSTR, :LPCWSTR, :DWORD
	STDMETHOD	SetBalloonRetry, :DWORD, :DWORD, :UINT
	STDMETHOD	SetIconInfo, :HICON, :LPCWSTR
	STDMETHOD	Show, :ptr, :DWORD
	STDMETHOD	PlaySound, :LPCWSTR


IUserNotification	ENDS

endif

ifndef __IUserNotificationCallback_INTERFACE_DEFINED__
__IUserNotificationCallback_INTERFACE_DEFINED__ equ 1

externdef		IID_IUserNotificationCallback:IID
IUserNotificationCallback STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	OnBalloonUserClick, :ptr
	STDMETHOD	OnLeftClick, :ptr
	STDMETHOD	OnContextMenu, :ptr


IUserNotificationCallback ENDS

endif

ifndef __IUserNotification2_INTERFACE_DEFINED__
__IUserNotification2_INTERFACE_DEFINED__ equ 1

externdef		IID_IUserNotification2:IID
IUserNotification2	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetBalloonInfo, :LPCWSTR, :LPCWSTR, :DWORD
	STDMETHOD	SetBalloonRetry, :DWORD, :DWORD, :UINT
	STDMETHOD	SetIconInfo, :HICON, :LPCWSTR
	STDMETHOD	Show, :ptr, :DWORD, :ptr
	STDMETHOD	PlaySound, :LPCWSTR


IUserNotification2	ENDS

endif

ifndef __IItemNameLimits_INTERFACE_DEFINED__
__IItemNameLimits_INTERFACE_DEFINED__ equ 1

externdef		IID_IItemNameLimits:IID
IItemNameLimits		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetValidCharacters, :ptr, :ptr
	STDMETHOD	GetMaxLength, :LPCWSTR, :ptr


IItemNameLimits		ENDS

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

externdef		__MIDL_itf_shobjidl_0000_0082_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0082_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ISearchFolderItemFactory_INTERFACE_DEFINED__
__ISearchFolderItemFactory_INTERFACE_DEFINED__ equ 1

externdef		IID_ISearchFolderItemFactory:IID
ISearchFolderItemFactory STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetDisplayName, :LPCWSTR
	STDMETHOD	SetFolderTypeID, :FOLDERTYPEID
	STDMETHOD	SetFolderLogicalViewMode, :FOLDERLOGICALVIEWMODE
	STDMETHOD	SetIconSize, :SINT
	STDMETHOD	SetVisibleColumns, :UINT, :ptr
	STDMETHOD	SetSortColumns, :UINT, :ptr
	STDMETHOD	SetGroupColumn, :REFPROPERTYKEY
	STDMETHOD	SetStacks, :UINT, :ptr
	STDMETHOD	SetScope, :ptr
	STDMETHOD	SetCondition, :ptr
	STDMETHOD	GetShellItem, :REFIID, :ptr
	STDMETHOD	GetIDList, :ptr


ISearchFolderItemFactory ENDS

endif
endif

if (_WIN32_IE GE 0x0400)
IEI_PRIORITY_MAX	equ ITSAT_MAX_PRIORITY
IEI_PRIORITY_MIN	equ ITSAT_MIN_PRIORITY
IEIT_PRIORITY_NORMAL	equ ITSAT_DEFAULT_PRIORITY
IEIFLAG_ASYNC		equ 0x0001
IEIFLAG_CACHE		equ 0x0002
IEIFLAG_ASPECT		equ 0x0004
IEIFLAG_OFFLINE		equ 0x0008
IEIFLAG_GLEAM		equ 0x0010
IEIFLAG_SCREEN		equ 0x0020
IEIFLAG_ORIGSIZE	equ 0x0040
IEIFLAG_NOSTAMP		equ 0x0080
IEIFLAG_NOBORDER	equ 0x0100
IEIFLAG_QUALITY		equ 0x0200
IEIFLAG_REFRESH		equ 0x0400

externdef		__MIDL_itf_shobjidl_0000_0083_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0083_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IExtractImage_INTERFACE_DEFINED__
__IExtractImage_INTERFACE_DEFINED__ equ 1

externdef		IID_IExtractImage:IID
IExtractImage		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetLocation, :LPWSTR, :DWORD, :ptr, :ptr, :DWORD, :ptr
	STDMETHOD	Extract, :ptr


IExtractImage		ENDS

endif

LPEXTRACTIMAGE		typedef ptr IExtractImage

endif
if (_WIN32_IE GE 0x0500)

externdef		__MIDL_itf_shobjidl_0000_0084_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0084_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IExtractImage2_INTERFACE_DEFINED__
__IExtractImage2_INTERFACE_DEFINED__ equ 1

externdef		IID_IExtractImage2:IID
IExtractImage2		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetLocation, :LPWSTR, :DWORD, :ptr, :ptr, :DWORD, :ptr
	STDMETHOD	Extract, :ptr
	STDMETHOD	GetDateStamp, :ptr


IExtractImage2		ENDS

endif

LPEXTRACTIMAGE2		typedef ptr IExtractImage2

externdef		__MIDL_itf_shobjidl_0000_0085_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0085_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IThumbnailHandlerFactory_INTERFACE_DEFINED__
__IThumbnailHandlerFactory_INTERFACE_DEFINED__ equ 1

externdef		IID_IThumbnailHandlerFactory:IID
IThumbnailHandlerFactory STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetThumbnailHandler, :PCUITEMID_CHILD, :ptr, :REFIID, :ptr


IThumbnailHandlerFactory ENDS

endif

ifndef __IParentAndItem_INTERFACE_DEFINED__
__IParentAndItem_INTERFACE_DEFINED__ equ 1

externdef		IID_IParentAndItem:IID
IParentAndItem		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetParentAndItem, :PCIDLIST_ABSOLUTE, :ptr, :PCUITEMID_CHILD
	STDMETHOD	GetParentAndItem, :ptr, :ptr, :ptr


IParentAndItem		ENDS

;STDMETHODCALLTYPE
IParentAndItem_RemoteGetParentAndItem_Proxy proto WINAPI \
		 _This: ptr IParentAndItem,
	   ppidlParent: ptr PIDLIST_ABSOLUTE,
		  ppsf: ptr IShellFolder,
	    ppidlChild: ptr PITEMID_CHILD

;void
IParentAndItem_RemoteGetParentAndItem_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif
endif

externdef		__MIDL_itf_shobjidl_0000_0087_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0087_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDockingWindow_INTERFACE_DEFINED__
__IDockingWindow_INTERFACE_DEFINED__ equ 1

externdef		IID_IDockingWindow:IID
IDockingWindow		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow, :ptr
	STDMETHOD	ContextSensitiveHelp, :BOOL
	STDMETHOD	ShowDW, :BOOL
	STDMETHOD	CloseDW, :DWORD
	STDMETHOD	ResizeBorderDW, :LPCRECT, :ptr, :BOOL


IDockingWindow		ENDS

endif

DBIM_MINSIZE		equ 0x0001
DBIM_MAXSIZE		equ 0x0002
DBIM_INTEGRAL		equ 0x0004
DBIM_ACTUAL		equ 0x0008
DBIM_TITLE		equ 0x0010
DBIM_MODEFLAGS		equ 0x0020
DBIM_BKCOLOR		equ 0x0040
;include pshpack8.inc
DESKBANDINFO		STRUC
dwMask			dd ?
ptMinSize		POINTL <>
ptMaxSize		POINTL <>
ptIntegral		POINTL <>
ptActual		POINTL <>
wszTitle		WCHAR  256  dup(?)
dwModeFlags		dd ?
crBkgnd			COLORREF ?
DESKBANDINFO		ENDS

;include poppack.inc
DBIMF_NORMAL		equ 0x0000
DBIMF_FIXED		equ 0x0001
DBIMF_FIXEDBMP		equ 0x0004
DBIMF_VARIABLEHEIGHT	equ 0x0008
DBIMF_UNDELETEABLE	equ 0x0010
DBIMF_DEBOSSED		equ 0x0020
DBIMF_BKCOLOR		equ 0x0040
DBIMF_USECHEVRON	equ 0x0080
DBIMF_BREAK		equ 0x0100
DBIMF_ADDTOFRONT	equ 0x0200
DBIMF_TOPALIGN		equ 0x0400
if (NTDDI_VERSION GE NTDDI_VISTA)
DBIMF_NOGRIPPER		equ 0x0800
DBIMF_ALWAYSGRIPPER	equ 0x1000
DBIMF_NOMARGINS		equ 0x2000
endif
DBIF_VIEWMODE_NORMAL	equ 0x0000
DBIF_VIEWMODE_VERTICAL	equ 0x0001
DBIF_VIEWMODE_FLOATING	equ 0x0002
DBIF_VIEWMODE_TRANSPARENT equ 0x0004

tagDESKBANDCID		typedef SDWORD
DBID_BANDINFOCHANGED	equ 0
DBID_SHOWONLY		equ 1
DBID_MAXIMIZEBAND	equ 2
DBID_PUSHCHEVRON	equ 3
DBID_DELAYINIT		equ 4
DBID_FINISHINIT		equ 5
DBID_SETWINDOWTHEME	equ 6
DBID_PERMITAUTOHIDE	equ 7
DBPC_SELECTFIRST	equ -1
DBPC_SELECTLAST		equ -2
CGID_DeskBand		equ IID_IDeskBand


externdef		__MIDL_itf_shobjidl_0000_0088_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0088_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDeskBand_INTERFACE_DEFINED__
__IDeskBand_INTERFACE_DEFINED__ equ 1

externdef		IID_IDeskBand:IID
IDeskBand		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow, :ptr
	STDMETHOD	ContextSensitiveHelp, :BOOL
	STDMETHOD	ShowDW, :BOOL
	STDMETHOD	CloseDW, :DWORD
	STDMETHOD	ResizeBorderDW, :LPCRECT, :ptr, :BOOL
	STDMETHOD	GetBandInfo, :DWORD, :DWORD, :ptr


IDeskBand		ENDS

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

externdef		__MIDL_itf_shobjidl_0000_0089_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0089_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDeskBandInfo_INTERFACE_DEFINED__
__IDeskBandInfo_INTERFACE_DEFINED__ equ 1

externdef		IID_IDeskBandInfo:IID
IDeskBandInfo		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDefaultBandWidth, :DWORD, :DWORD, :ptr


IDeskBandInfo		ENDS

endif

ifndef __IDeskBand2_INTERFACE_DEFINED__
__IDeskBand2_INTERFACE_DEFINED__ equ 1

externdef		IID_IDeskBand2:IID
IDeskBand2		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow, :ptr
	STDMETHOD	ContextSensitiveHelp, :BOOL
	STDMETHOD	ShowDW, :BOOL
	STDMETHOD	CloseDW, :DWORD
	STDMETHOD	ResizeBorderDW, :LPCRECT, :ptr, :BOOL
	STDMETHOD	GetBandInfo, :DWORD, :DWORD, :ptr
	STDMETHOD	CanRenderComposited, :ptr
	STDMETHOD	SetCompositionState, :BOOL
	STDMETHOD	GetCompositionState, :ptr


IDeskBand2		ENDS

endif
endif

externdef		__MIDL_itf_shobjidl_0000_0091_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0091_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ITaskbarList_INTERFACE_DEFINED__
__ITaskbarList_INTERFACE_DEFINED__ equ 1

externdef		IID_ITaskbarList:IID
ITaskbarList		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	HrInit
	STDMETHOD	AddTab, :HWND
	STDMETHOD	DeleteTab, :HWND
	STDMETHOD	ActivateTab, :HWND
	STDMETHOD	SetActiveAlt, :HWND


ITaskbarList		ENDS

endif

ifndef __ITaskbarList2_INTERFACE_DEFINED__
__ITaskbarList2_INTERFACE_DEFINED__ equ 1

externdef		IID_ITaskbarList2:IID
ITaskbarList2		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	HrInit
	STDMETHOD	AddTab, :HWND
	STDMETHOD	DeleteTab, :HWND
	STDMETHOD	ActivateTab, :HWND
	STDMETHOD	SetActiveAlt, :HWND
	STDMETHOD	MarkFullscreenWindow, :HWND, :BOOL


ITaskbarList2		ENDS

endif

ifdef MIDL_PASS
HIMAGELIST		typedef ptr IUnknown

endif
THUMBBUTTONFLAGS	typedef SDWORD
THBF_ENABLED		equ 0
THBF_DISABLED		equ 0x1
THBF_DISMISSONCLICK	equ 0x2
THBF_NOBACKGROUND	equ 0x4
THBF_HIDDEN		equ 0x8
THBF_NONINTERACTIVE	equ 0x10

DEFINE_ENUM_FLAG_OPERATORS(THUMBBUTTONFLAGS)
THUMBBUTTONMASK		typedef SDWORD
THB_BITMAP		equ 0x1
THB_ICON		equ 0x2
THB_TOOLTIP		equ 0x4
THB_FLAGS		equ 0x8

DEFINE_ENUM_FLAG_OPERATORS(THUMBBUTTONMASK)
;include pshpack8.inc
THUMBBUTTON		STRUC
dwMask			THUMBBUTTONMASK ?
iId			UINT ?
iBitmap			UINT ?
hIcon			HICON ?
szTip			WCHAR  260  dup(?)
dwFlags			THUMBBUTTONFLAGS ?
THUMBBUTTON		ENDS

LPTHUMBBUTTON		typedef ptr THUMBBUTTON

;include poppack.inc
THBN_CLICKED		equ 0x1800

externdef		__MIDL_itf_shobjidl_0000_0093_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0093_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ITaskbarList3_INTERFACE_DEFINED__
__ITaskbarList3_INTERFACE_DEFINED__ equ 1

TBPFLAG			typedef SDWORD
TBPF_NOPROGRESS		equ 0
TBPF_INDETERMINATE	equ 0x1
TBPF_NORMAL		equ 0x2
TBPF_ERROR		equ 0x4
TBPF_PAUSED		equ 0x8

DEFINE_ENUM_FLAG_OPERATORS(TBPFLAG)

externdef		IID_ITaskbarList3:IID
ITaskbarList3		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	HrInit
	STDMETHOD	AddTab, :HWND
	STDMETHOD	DeleteTab, :HWND
	STDMETHOD	ActivateTab, :HWND
	STDMETHOD	SetActiveAlt, :HWND
	STDMETHOD	MarkFullscreenWindow, :HWND, :BOOL
	STDMETHOD	SetProgressValue, :HWND, :ULONGLONG, :ULONGLONG
	STDMETHOD	SetProgressState, :HWND, :TBPFLAG
	STDMETHOD	RegisterTab, :HWND, :HWND
	STDMETHOD	UnregisterTab, :HWND
	STDMETHOD	SetTabOrder, :HWND, :HWND
	STDMETHOD	SetTabActive, :HWND, :HWND, :DWORD
	STDMETHOD	ThumbBarAddButtons, :HWND, :UINT, :LPTHUMBBUTTON
	STDMETHOD	ThumbBarUpdateButtons, :HWND, :UINT, :LPTHUMBBUTTON
	STDMETHOD	ThumbBarSetImageList, :HWND, :HIMAGELIST
	STDMETHOD	SetOverlayIcon, :HWND, :HICON, :LPCWSTR
	STDMETHOD	SetThumbnailTooltip, :HWND, :LPCWSTR
	STDMETHOD	SetThumbnailClip, :HWND, :ptr


ITaskbarList3		ENDS

endif

ifndef __ITaskbarList4_INTERFACE_DEFINED__
__ITaskbarList4_INTERFACE_DEFINED__ equ 1

STPFLAG			typedef SDWORD
STPF_NONE		equ 0
STPF_USEAPPTHUMBNAILALWAYS equ 0x1
STPF_USEAPPTHUMBNAILWHENACTIVE	equ 0x2
STPF_USEAPPPEEKALWAYS	equ 0x4
STPF_USEAPPPEEKWHENACTIVE equ 0x8

DEFINE_ENUM_FLAG_OPERATORS(STPFLAG)

externdef		IID_ITaskbarList4:IID
ITaskbarList4		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	HrInit
	STDMETHOD	AddTab, :HWND
	STDMETHOD	DeleteTab, :HWND
	STDMETHOD	ActivateTab, :HWND
	STDMETHOD	SetActiveAlt, :HWND
	STDMETHOD	MarkFullscreenWindow, :HWND, :BOOL
	STDMETHOD	SetProgressValue, :HWND, :ULONGLONG, :ULONGLONG
	STDMETHOD	SetProgressState, :HWND, :TBPFLAG
	STDMETHOD	RegisterTab, :HWND, :HWND
	STDMETHOD	UnregisterTab, :HWND
	STDMETHOD	SetTabOrder, :HWND, :HWND
	STDMETHOD	SetTabActive, :HWND, :HWND, :DWORD
	STDMETHOD	ThumbBarAddButtons, :HWND, :UINT, :LPTHUMBBUTTON
	STDMETHOD	ThumbBarUpdateButtons, :HWND, :UINT, :LPTHUMBBUTTON
	STDMETHOD	ThumbBarSetImageList, :HWND, :HIMAGELIST
	STDMETHOD	SetOverlayIcon, :HWND, :HICON, :LPCWSTR
	STDMETHOD	SetThumbnailTooltip, :HWND, :LPCWSTR
	STDMETHOD	SetThumbnailClip, :HWND, :ptr
	STDMETHOD	SetTabProperties, :HWND, :STPFLAG


ITaskbarList4		ENDS

endif

ifndef __IStartMenuPinnedList_INTERFACE_DEFINED__
__IStartMenuPinnedList_INTERFACE_DEFINED__ equ 1

externdef		IID_IStartMenuPinnedList:IID
IStartMenuPinnedList	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	RemoveFromList, :ptr


IStartMenuPinnedList	ENDS

endif

ifndef __ICDBurn_INTERFACE_DEFINED__
__ICDBurn_INTERFACE_DEFINED__ equ 1

externdef		IID_ICDBurn:IID
ICDBurn			STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetRecorderDriveLetter, :LPWSTR, :UINT
	STDMETHOD	Burn, :HWND
	STDMETHOD	HasRecordableDrive, :ptr


ICDBurn			ENDS

endif

IDD_WIZEXTN_FIRST	equ 0x5000
IDD_WIZEXTN_LAST	equ 0x5100

externdef		__MIDL_itf_shobjidl_0000_0097_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0097_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IWizardSite_INTERFACE_DEFINED__
__IWizardSite_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_IWizardSite, 0x88960f5b, 0x422f, 0x4e7b, 0x80,0x13, 0x73,0x41,0x53,0x81,0xc3,0xc3)

externdef		IID_IWizardSite:IID
IWizardSite		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetPreviousPage, :ptr
	STDMETHOD	GetNextPage, :ptr
	STDMETHOD	GetCancelledPage, :ptr


IWizardSite		ENDS

endif

SID_WizardSite		equ IID_IWizardSite

externdef		__MIDL_itf_shobjidl_0000_0098_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0098_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IWizardExtension_INTERFACE_DEFINED__
__IWizardExtension_INTERFACE_DEFINED__ equ 1

externdef		IID_IWizardExtension:IID
IWizardExtension	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	AddPages, :ptr, :UINT, :ptr
	STDMETHOD	GetFirstPage, :ptr
	STDMETHOD	GetLastPage, :ptr


IWizardExtension	ENDS

endif


ifndef __IWebWizardExtension_INTERFACE_DEFINED__
__IWebWizardExtension_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_IWebWizardExtension, 0x0e6b3f66, 0x98d1, 0x48c0, 0xa2,0x22, 0xfb,0xde,0x74,0xe2,0xfb,0xc5)

externdef		IID_IWebWizardExtension:IID
IWebWizardExtension	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	AddPages, :ptr, :UINT, :ptr
	STDMETHOD	GetFirstPage, :ptr
	STDMETHOD	GetLastPage, :ptr
	STDMETHOD	SetInitialURL, :LPCWSTR
	STDMETHOD	SetErrorURL, :LPCWSTR


IWebWizardExtension	ENDS

endif

SID_WebWizardHost	equ IID_IWebWizardExtension
SHPWHF_NORECOMPRESS	equ 0x00000001
SHPWHF_NONETPLACECREATE equ 0x00000002
SHPWHF_NOFILESELECTOR	equ 0x00000004
SHPWHF_USEMRU		equ 0x00000008
if (NTDDI_VERSION GE NTDDI_VISTA)
SHPWHF_ANYLOCATION	equ 0x00000100
endif
SHPWHF_VALIDATEVIAWEBFOLDERS equ 0x00010000

externdef		__MIDL_itf_shobjidl_0000_0100_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0100_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IPublishingWizard_INTERFACE_DEFINED__
__IPublishingWizard_INTERFACE_DEFINED__ equ 1

externdef		IID_IPublishingWizard:IID
IPublishingWizard	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	AddPages, :ptr, :UINT, :ptr
	STDMETHOD	GetFirstPage, :ptr
	STDMETHOD	GetLastPage, :ptr
	STDMETHOD	Initialize, :ptr, :DWORD, :LPCWSTR
	STDMETHOD	GetTransferManifest, :ptr, :ptr


IPublishingWizard	ENDS

endif


if (NTDDI_VERSION GE NTDDI_WINXP) OR (_WIN32_IE GE _WIN32_IE_IE70)

externdef		__MIDL_itf_shobjidl_0000_0101_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0101_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFolderViewHost_INTERFACE_DEFINED__
__IFolderViewHost_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_IFolderViewHost, 0x1ea58f02, 0xd55a, 0x411d, 0xb0,0x9e, 0x9e,0x65,0xac,0x21,0x60,0x5b)

externdef		IID_IFolderViewHost:IID
IFolderViewHost		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Initialize, :HWND, :ptr, :ptr


IFolderViewHost		ENDS

endif

if (_WIN32_IE GE _WIN32_IE_IE70)

externdef		__MIDL_itf_shobjidl_0000_0102_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0102_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IExplorerBrowserEvents_INTERFACE_DEFINED__
__IExplorerBrowserEvents_INTERFACE_DEFINED__ equ 1

externdef		IID_IExplorerBrowserEvents:IID
IExplorerBrowserEvents	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	OnNavigationPending, :PCIDLIST_ABSOLUTE
	STDMETHOD	OnViewCreated, :ptr
	STDMETHOD	OnNavigationComplete, :PCIDLIST_ABSOLUTE
	STDMETHOD	OnNavigationFailed, :PCIDLIST_ABSOLUTE


IExplorerBrowserEvents	ENDS

endif

EXPLORER_BROWSER_OPTIONS typedef SDWORD
EBO_NONE		equ 0
EBO_NAVIGATEONCE	equ 0x1
EBO_SHOWFRAMES		equ 0x2
EBO_ALWAYSNAVIGATE	equ 0x4
EBO_NOTRAVELLOG		equ 0x8
EBO_NOWRAPPERWINDOW	equ 0x10
EBO_HTMLSHAREPOINTVIEW	equ 0x20

DEFINE_ENUM_FLAG_OPERATORS(EXPLORER_BROWSER_OPTIONS)
EXPLORER_BROWSER_FILL_FLAGS typedef SDWORD
EBF_NONE		equ 0
EBF_SELECTFROMDATAOBJECT equ 0x100
EBF_NODROPTARGET	equ 0x200

DEFINE_ENUM_FLAG_OPERATORS(EXPLORER_BROWSER_FILL_FLAGS)

externdef		__MIDL_itf_shobjidl_0000_0103_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0103_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IExplorerBrowser_INTERFACE_DEFINED__
__IExplorerBrowser_INTERFACE_DEFINED__ equ 1

externdef		IID_IExplorerBrowser:IID
IExplorerBrowser	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Initialize, :HWND, :ptr, :ptr
	STDMETHOD	Destroy
	STDMETHOD	SetRect, :ptr, :RECT
	STDMETHOD	SetPropertyBag, :LPCWSTR
	STDMETHOD	SetEmptyText, :LPCWSTR
	STDMETHOD	SetFolderSettings, :ptr
	STDMETHOD	Advise, :ptr, :ptr
	STDMETHOD	Unadvise, :DWORD
	STDMETHOD	SetOptions, :EXPLORER_BROWSER_OPTIONS
	STDMETHOD	GetOptions, :ptr
	STDMETHOD	BrowseToIDList, :PCUIDLIST_RELATIVE, :UINT
	STDMETHOD	BrowseToObject, :ptr, :UINT
	STDMETHOD	FillFromObject, :ptr, :EXPLORER_BROWSER_FILL_FLAGS
	STDMETHOD	RemoveAll
	STDMETHOD	GetCurrentView, :REFIID, :ptr


IExplorerBrowser	ENDS

endif

ifndef __IAccessibleObject_INTERFACE_DEFINED__
__IAccessibleObject_INTERFACE_DEFINED__ equ 1

externdef		IID_IAccessibleObject:IID
IAccessibleObject	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetAccessibleName, :LPCWSTR


IAccessibleObject	ENDS

endif
endif

externdef		__MIDL_itf_shobjidl_0000_0105_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0105_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IResultsFolder_INTERFACE_DEFINED__
__IResultsFolder_INTERFACE_DEFINED__ equ 1

externdef		IID_IResultsFolder:IID
IResultsFolder		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	AddItem, :ptr
	STDMETHOD	AddIDList, :PCIDLIST_ABSOLUTE, :ptr
	STDMETHOD	RemoveItem, :ptr
	STDMETHOD	RemoveIDList, :PCIDLIST_ABSOLUTE
	STDMETHOD	RemoveAll


IResultsFolder		ENDS

;STDMETHODCALLTYPE
IResultsFolder_RemoteAddIDList_Proxy proto WINAPI \
		 _This: ptr IResultsFolder,
		  pidl: PCIDLIST_ABSOLUTE,
	    ppidlAdded: ptr PITEMID_CHILD

;void
IResultsFolder_RemoteAddIDList_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

if (_WIN32_IE GE _WIN32_IE_IE70)

externdef		__MIDL_itf_shobjidl_0000_0106_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0106_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumObjects_INTERFACE_DEFINED__
__IEnumObjects_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumObjects:IID
IEnumObjects		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :ULONG, :REFIID, :ptr, :ptr
	STDMETHOD	Skip, :ULONG
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr


IEnumObjects		ENDS

;STDMETHODCALLTYPE
IEnumObjects_RemoteNext_Proxy proto WINAPI \
		 _This: ptr IEnumObjects,
		  celt: ULONG,
		  riid: REFIID,
		 rgelt: PVOID,
	  pceltFetched: LPULONG

;void
IEnumObjects_RemoteNext_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

OPPROGDLG_DEFAULT	equ 0
OPPROGDLG_ENABLEPAUSE	equ 0x80
OPPROGDLG_ALLOWUNDO	equ 0x100
OPPROGDLG_DONTDISPLAYSOURCEPATH equ 0x200
OPPROGDLG_DONTDISPLAYDESTPATH equ 0x400
OPPROGDLG_NOMULTIDAYESTIMATES equ 0x800
OPPROGDLG_DONTDISPLAYLOCATIONS equ 0x1000
OPPROGDLGF		typedef DWORD

externdef		__MIDL_itf_shobjidl_0000_0107_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0107_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IOperationsProgressDialog_INTERFACE_DEFINED__
__IOperationsProgressDialog_INTERFACE_DEFINED__ equ 1

PDM_DEFAULT		equ 0
PDM_RUN			equ 0x1
PDM_PREFLIGHT		equ 0x2
PDM_UNDOING		equ 0x4
PDM_ERRORSBLOCKING	equ 0x8
PDM_INDETERMINATE	equ 0x10
PDMODE			typedef DWORD

PDOPSTATUS		typedef SDWORD
PDOPS_RUNNING		equ 1
PDOPS_PAUSED		equ 2
PDOPS_CANCELLED		equ 3
PDOPS_STOPPED		equ 4
PDOPS_ERRORS		equ 5

externdef		IID_IOperationsProgressDialog:IID
IOperationsProgressDialog STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	StartProgressDialog, :HWND, :OPPROGDLGF
	STDMETHOD	StopProgressDialog
	STDMETHOD	SetOperation, :SPACTION
	STDMETHOD	SetMode, :PDMODE
	STDMETHOD	UpdateProgress, :ULONGLONG, :ULONGLONG, :ULONGLONG, :ULONGLONG, :ULONGLONG, :ULONGLONG
	STDMETHOD	UpdateLocations, :ptr, :ptr, :ptr
	STDMETHOD	ResetTimer
	STDMETHOD	PauseTimer
	STDMETHOD	ResumeTimer
	STDMETHOD	GetMilliseconds, :ptr, :ptr
	STDMETHOD	GetOperationStatus, :ptr


IOperationsProgressDialog ENDS

endif

ifndef __IIOCancelInformation_INTERFACE_DEFINED__
__IIOCancelInformation_INTERFACE_DEFINED__ equ 1

externdef		IID_IIOCancelInformation:IID
IIOCancelInformation	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetCancelInformation, :DWORD, :UINT
	STDMETHOD	GetCancelInformation, :ptr, :ptr


IIOCancelInformation	ENDS

endif

FOFX_NOSKIPJUNCTIONS	equ 0x00010000
FOFX_PREFERHARDLINK	equ 0x00020000
FOFX_SHOWELEVATIONPROMPT equ 0x00040000
FOFX_EARLYFAILURE	equ 0x00100000
FOFX_PRESERVEFILEEXTENSIONS equ 0x00200000
FOFX_KEEPNEWERFILE	equ 0x00400000
FOFX_NOCOPYHOOKS	equ 0x00800000
FOFX_NOMINIMIZEBOX	equ 0x01000000
FOFX_MOVEACLSACROSSVOLUMES equ 0x02000000
FOFX_DONTDISPLAYSOURCEPATH equ 0x04000000
FOFX_DONTDISPLAYDESTPATH equ 0x08000000
FOFX_REQUIREELEVATION	equ 0x10000000
FOFX_COPYASDOWNLOAD	equ 0x40000000
FOFX_DONTDISPLAYLOCATIONS equ 0x80000000

externdef		__MIDL_itf_shobjidl_0000_0109_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0109_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFileOperation_INTERFACE_DEFINED__
__IFileOperation_INTERFACE_DEFINED__ equ 1

externdef		IID_IFileOperation:IID
IFileOperation		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Advise, :ptr, :ptr
	STDMETHOD	Unadvise, :DWORD
	STDMETHOD	SetOperationFlags, :DWORD
	STDMETHOD	SetProgressMessage, :LPCWSTR
	STDMETHOD	SetProgressDialog, :ptr
	STDMETHOD	SetProperties, :ptr
	STDMETHOD	SetOwnerWindow, :HWND
	STDMETHOD	ApplyPropertiesToItem, :ptr
	STDMETHOD	ApplyPropertiesToItems, :ptr
	STDMETHOD	RenameItem, :ptr, :LPCWSTR, :ptr
	STDMETHOD	RenameItems, :ptr, :LPCWSTR
	STDMETHOD	MoveItem, :ptr, :ptr, :LPCWSTR, :ptr
	STDMETHOD	MoveItems, :ptr, :ptr
	STDMETHOD	CopyItem, :ptr, :ptr, :LPCWSTR, :ptr
	STDMETHOD	CopyItems, :ptr, :ptr
	STDMETHOD	DeleteItem, :ptr, :ptr
	STDMETHOD	DeleteItems, :ptr
	STDMETHOD	NewItem, :ptr, :DWORD, :LPCWSTR, :LPCWSTR, :ptr
	STDMETHOD	PerformOperations
	STDMETHOD	GetAnyOperationsAborted, :ptr


IFileOperation		ENDS

endif

ifndef __IObjectProvider_INTERFACE_DEFINED__
__IObjectProvider_INTERFACE_DEFINED__ equ 1

externdef		IID_IObjectProvider:IID
IObjectProvider		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	QueryObject, :REFGUID, :REFIID, :ptr


IObjectProvider		ENDS

endif
endif

externdef		__MIDL_itf_shobjidl_0000_0111_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0111_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __INamespaceWalkCB_INTERFACE_DEFINED__
__INamespaceWalkCB_INTERFACE_DEFINED__ equ 1

externdef		IID_INamespaceWalkCB:IID
INamespaceWalkCB	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	FoundItem, :ptr, :PCUITEMID_CHILD
	STDMETHOD	EnterFolder, :ptr, :PCUITEMID_CHILD
	STDMETHOD	LeaveFolder, :ptr, :PCUITEMID_CHILD
	STDMETHOD	InitializeProgressDialog, :ptr, :ptr


INamespaceWalkCB	ENDS

endif

if (_WIN32_IE GE _WIN32_IE_IE70)

externdef		__MIDL_itf_shobjidl_0000_0112_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0112_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __INamespaceWalkCB2_INTERFACE_DEFINED__
__INamespaceWalkCB2_INTERFACE_DEFINED__ equ 1

externdef		IID_INamespaceWalkCB2:IID
INamespaceWalkCB2	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	FoundItem, :ptr, :PCUITEMID_CHILD
	STDMETHOD	EnterFolder, :ptr, :PCUITEMID_CHILD
	STDMETHOD	LeaveFolder, :ptr, :PCUITEMID_CHILD
	STDMETHOD	InitializeProgressDialog, :ptr, :ptr
	STDMETHOD	WalkComplete, :HRESULT


INamespaceWalkCB2	ENDS

endif
endif

externdef		__MIDL_itf_shobjidl_0000_0113_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0113_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __INamespaceWalk_INTERFACE_DEFINED__
__INamespaceWalk_INTERFACE_DEFINED__ equ 1

NAMESPACEWALKFLAG	typedef SDWORD
NSWF_DEFAULT		equ 0
NSWF_NONE_IMPLIES_ALL	equ 0x1
NSWF_ONE_IMPLIES_ALL	equ 0x2
NSWF_DONT_TRAVERSE_LINKS equ 0x4
NSWF_DONT_ACCUMULATE_RESULT equ 0x8
NSWF_TRAVERSE_STREAM_JUNCTIONS equ 0x10
NSWF_FILESYSTEM_ONLY	equ 0x20
NSWF_SHOW_PROGRESS	equ 0x40
NSWF_FLAG_VIEWORDER	equ 0x80
NSWF_IGNORE_AUTOPLAY_HIDA equ 0x100
NSWF_ASYNC		equ 0x200
NSWF_DONT_RESOLVE_LINKS equ 0x400
NSWF_ACCUMULATE_FOLDERS equ 0x800
NSWF_DONT_SORT		equ 0x1000
NSWF_USE_TRANSFER_MEDIUM equ 0x2000
NSWF_DONT_TRAVERSE_STREAM_JUNCTIONS equ 0x4000


DEFINE_ENUM_FLAG_OPERATORS(NAMESPACEWALKFLAG)

externdef		IID_INamespaceWalk:IID


INamespaceWalk		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Walk, :ptr, :DWORD, :SINT, :ptr
	STDMETHOD	GetIDArrayResult, :ptr, :ptr


INamespaceWalk		ENDS

endif
endif

FreeIDListArrayFull	equ FreeIDistArray
FreeIDListArrayChild	equ FreeIDistArray
ACDD_VISIBLE		equ 0x0001

externdef		__MIDL_itf_shobjidl_0000_0114_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0114_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAutoCompleteDropDown_INTERFACE_DEFINED__
__IAutoCompleteDropDown_INTERFACE_DEFINED__ equ 1

externdef		IID_IAutoCompleteDropDown:IID
IAutoCompleteDropDown	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDropDownStatus, :ptr, :ptr
	STDMETHOD	ResetEnumerator


IAutoCompleteDropDown	ENDS

endif

if (_WIN32_IE GE _WIN32_IE_IE40)
;include pshpack8.inc
BANDSITEINFO		STRUC
dwMask			dd ?
dwState			dd ?
dwStyle			dd ?
BANDSITEINFO		ENDS

;include poppack.inc

tagBANDSITECID		typedef SDWORD
BSID_BANDADDED		equ 0
BSID_BANDREMOVED	equ ( BSID_BANDADDED + 1 )
BSIM_STATE		equ 0x00000001
BSIM_STYLE		equ 0x00000002
BSSF_VISIBLE		equ 0x00000001
BSSF_NOTITLE		equ 0x00000002
BSSF_UNDELETEABLE	equ 0x00001000
BSIS_AUTOGRIPPER	equ 0x00000000
BSIS_NOGRIPPER		equ 0x00000001
BSIS_ALWAYSGRIPPER	equ 0x00000002
BSIS_LEFTALIGN		equ 0x00000004
BSIS_SINGLECLICK	equ 0x00000008
BSIS_NOCONTEXTMENU	equ 0x00000010
BSIS_NODROPTARGET	equ 0x00000020
BSIS_NOCAPTION		equ 0x00000040
BSIS_PREFERNOLINEBREAK	equ 0x00000080
BSIS_LOCKED		equ 0x00000100
if (_WIN32_IE GE _WIN32_IE_IE70)
BSIS_PRESERVEORDERDURINGLAYOUT equ 0x00000200
BSIS_FIXEDORDER		equ 0x00000400
endif
SID_SBandSite		equ IID_IBandSite
CGID_BandSite		equ IID_IBandSite

externdef		__MIDL_itf_shobjidl_0000_0115_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0115_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IBandSite_INTERFACE_DEFINED__
__IBandSite_INTERFACE_DEFINED__ equ 1

externdef		IID_IBandSite:IID
IBandSite		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	AddBand, :ptr
	STDMETHOD	EnumBands, :UINT, :ptr
	STDMETHOD	QueryBand, :DWORD, :ptr, :ptr, :LPWSTR, :SINT
	STDMETHOD	SetBandState, :DWORD, :DWORD, :DWORD
	STDMETHOD	RemoveBand, :DWORD
	STDMETHOD	GetBandObject, :DWORD, :REFIID, :ptr
	STDMETHOD	SetBandSiteInfo, :ptr
	STDMETHOD	GetBandSiteInfo, :ptr


IBandSite		ENDS
LPIDeskBand		typedef ptr IDeskBand

;STDMETHODCALLTYPE
IBandSite_RemoteQueryBand_Proxy proto WINAPI \
		 _This: ptr IBandSite,
	      dwBandID: DWORD,
		 ppstb: LPIDeskBand,
	      pdwState: LPDWORD,
	       pszName: LPWSTR,
	       cchName: SINT

;void
IBandSite_RemoteQueryBand_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif
endif

if (NTDDI_VERSION GE NTDDI_WINXP)

externdef		__MIDL_itf_shobjidl_0000_0116_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0116_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IModalWindow_INTERFACE_DEFINED__
__IModalWindow_INTERFACE_DEFINED__ equ 1

externdef		IID_IModalWindow:IID
IModalWindow		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Show, :HWND


IModalWindow		ENDS

;STDMETHODCALLTYPE
IModalWindow_RemoteShow_Proxy proto WINAPI \
		 _This: ptr IModalWindow,
	     hwndOwner: HWND

;void
IModalWindow_RemoteShow_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

PROPSTR_EXTENSIONCOMPLETIONSTATE equ <L"ExtensionCompletionState">

tagCDBURNINGEXTENSIONRET typedef SDWORD
CDBE_RET_DEFAULT	equ 0
CDBE_RET_DONTRUNOTHEREXTS equ 0x1
CDBE_RET_STOPWIZARD	equ 0x2
SID_CDWizardHost	equ IID_ICDBurnExt

CDBE_TYPE_MUSIC		equ 0x1
CDBE_TYPE_DATA		equ 0x2
CDBE_TYPE_ALL		equ ( SINT  )0xffffffff
CDBE_ACTIONS		typedef DWORD

externdef		__MIDL_itf_shobjidl_0000_0117_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0117_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ICDBurnExt_INTERFACE_DEFINED__
__ICDBurnExt_INTERFACE_DEFINED__ equ 1

externdef		IID_ICDBurnExt:IID
ICDBurnExt		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetSupportedActionTypes, :ptr


ICDBurnExt		ENDS

endif
endif

externdef		__MIDL_itf_shobjidl_0000_0118_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0118_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IContextMenuSite_INTERFACE_DEFINED__
__IContextMenuSite_INTERFACE_DEFINED__ equ 1

externdef		IID_IContextMenuSite:IID
IContextMenuSite	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	DoContextMenuPopup, :ptr, :UINT, :POINT


IContextMenuSite	ENDS
endif

ifndef __IEnumReadyCallback_INTERFACE_DEFINED__
__IEnumReadyCallback_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumReadyCallback:IID
IEnumReadyCallback	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	EnumReady


IEnumReadyCallback	ENDS

endif

ifndef __IEnumerableView_INTERFACE_DEFINED__
__IEnumerableView_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_IEnumerableView, 0x8c8bf236, 0x1aec, 0x495f, 0x98,0x94, 0x91,0xd5,0x7c,0x3c,0x68,0x6f)

externdef		IID_IEnumerableView:IID
IEnumerableView		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetEnumReadyCallback, :ptr
	STDMETHOD	CreateEnumIDListFromContents, :PCIDLIST_ABSOLUTE, :DWORD, :ptr


IEnumerableView		ENDS

endif

SID_EnumerableView	equ IID_IEnumerableView
if (NTDDI_VERSION GE NTDDI_WINXP) OR (_WIN32_IE GE _WIN32_IE_IE70)

externdef		__MIDL_itf_shobjidl_0000_0121_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0121_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInsertItem_INTERFACE_DEFINED__
__IInsertItem_INTERFACE_DEFINED__ equ 1

externdef		IID_IInsertItem:IID
IInsertItem		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	InsertItem, :PCUIDLIST_RELATIVE


IInsertItem		ENDS

endif

if (NTDDI_VERSION GE NTDDI_WINXP)

externdef		__MIDL_itf_shobjidl_0000_0122_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0122_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IMenuBand_INTERFACE_DEFINED__
__IMenuBand_INTERFACE_DEFINED__ equ 1

tagMENUBANDHANDLERCID	typedef SDWORD
MBHANDCID_PIDLSELECT	equ 0

externdef		IID_IMenuBand:IID
IMenuBand		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	IsMenuMessage, :ptr
	STDMETHOD	TranslateMenuMessage, :ptr, :ptr


IMenuBand		ENDS

endif

ifndef __IFolderBandPriv_INTERFACE_DEFINED__
__IFolderBandPriv_INTERFACE_DEFINED__ equ 1

externdef		IID_IFolderBandPriv:IID
IFolderBandPriv		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetCascade, :BOOL
	STDMETHOD	SetAccelerators, :BOOL
	STDMETHOD	SetNoIcons, :BOOL
	STDMETHOD	SetNoText, :BOOL


IFolderBandPriv		ENDS

endif

ifndef __IRegTreeItem_INTERFACE_DEFINED__
__IRegTreeItem_INTERFACE_DEFINED__ equ 1

externdef		IID_IRegTreeItem:IID
IRegTreeItem		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetCheckState, :ptr
	STDMETHOD	SetCheckState, :BOOL


IRegTreeItem		ENDS

endif

ifndef __IImageRecompress_INTERFACE_DEFINED__
__IImageRecompress_INTERFACE_DEFINED__ equ 1

externdef		IID_IImageRecompress:IID
IImageRecompress	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	RecompressImage, :ptr, :SINT, :SINT, :SINT, :ptr, :ptr


IImageRecompress	ENDS

endif
endif
endif

if (_WIN32_IE GE _WIN32_IE_IE60)

externdef		__MIDL_itf_shobjidl_0000_0126_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0126_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDeskBar_INTERFACE_DEFINED__
__IDeskBar_INTERFACE_DEFINED__ equ 1

externdef		IID_IDeskBar:IID
IDeskBar		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow, :ptr
	STDMETHOD	ContextSensitiveHelp, :BOOL
	STDMETHOD	SetClient, :ptr
	STDMETHOD	GetClient, :ptr
	STDMETHOD	OnPosRectChangeDB, :ptr


IDeskBar		ENDS

endif

ifndef __IMenuPopup_INTERFACE_DEFINED__
__IMenuPopup_INTERFACE_DEFINED__ equ 1

tagMENUPOPUPSELECT	typedef SDWORD
MPOS_EXECUTE		equ 0
MPOS_FULLCANCEL		equ ( MPOS_EXECUTE + 1 )
MPOS_CANCELLEVEL	equ ( MPOS_FULLCANCEL + 1 )
MPOS_SELECTLEFT		equ ( MPOS_CANCELLEVEL + 1 )
MPOS_SELECTRIGHT	equ ( MPOS_SELECTLEFT + 1 )
MPOS_CHILDTRACKING	equ ( MPOS_SELECTRIGHT + 1 )

tagMENUPOPUPPOPUPFLAGS	typedef SDWORD
MPPF_SETFOCUS		equ 0x1
MPPF_INITIALSELECT	equ 0x2
MPPF_NOANIMATE		equ 0x4
MPPF_KEYBOARD		equ 0x10
MPPF_REPOSITION		equ 0x20
MPPF_FORCEZORDER	equ 0x40
MPPF_FINALSELECT	equ 0x80
MPPF_TOP		equ 0x20000000
MPPF_LEFT		equ 0x40000000
MPPF_RIGHT		equ 0x60000000
MPPF_BOTTOM		equ ( SINT  )0x80000000
MPPF_POS_MASK		equ ( SINT  )0xe0000000
MPPF_ALIGN_LEFT		equ 0x2000000
MPPF_ALIGN_RIGHT	equ 0x4000000
MP_POPUPFLAGS		typedef SINT

externdef		IID_IMenuPopup:IID
IMenuPopup		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow, :ptr
	STDMETHOD	ContextSensitiveHelp, :BOOL
	STDMETHOD	SetClient, :ptr
	STDMETHOD	GetClient, :ptr
	STDMETHOD	OnPosRectChangeDB, :ptr
	STDMETHOD	Popup, :ptr, :ptr, :MP_POPUPFLAGS
	STDMETHOD	OnSelect, :DWORD
	STDMETHOD	SetSubMenu, :ptr, :BOOL


IMenuPopup		ENDS

endif
endif

if (NTDDI_VERSION GE NTDDI_VISTA)
FILE_USAGE_TYPE		typedef SDWORD
FUT_PLAYING		equ 0
FUT_EDITING		equ ( FUT_PLAYING + 1 )
FUT_GENERIC		equ ( FUT_EDITING + 1 )

OF_CAP_CANSWITCHTO	equ 0x0001
OF_CAP_CANCLOSE		equ 0x0002


externdef		__MIDL_itf_shobjidl_0000_0128_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0128_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFileIsInUse_INTERFACE_DEFINED__
__IFileIsInUse_INTERFACE_DEFINED__ equ 1

externdef		IID_IFileIsInUse:IID
IFileIsInUse		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetAppName, :ptr
	STDMETHOD	GetUsage, :ptr
	STDMETHOD	GetCapabilities, :ptr
	STDMETHOD	GetSwitchToHWND, :ptr
	STDMETHOD	CloseFile


IFileIsInUse		ENDS

endif

FDE_OVERWRITE_RESPONSE	typedef SDWORD
FDEOR_DEFAULT		equ 0
FDEOR_ACCEPT		equ 1
FDEOR_REFUSE		equ 2

FDE_SHAREVIOLATION_RESPONSE typedef SDWORD
FDESVR_DEFAULT		equ 0
FDESVR_ACCEPT		equ 1
FDESVR_REFUSE		equ 2

FDAP			typedef SDWORD
FDAP_BOTTOM		equ 0
FDAP_TOP		equ 1

externdef		__MIDL_itf_shobjidl_0000_0129_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0129_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFileDialogEvents_INTERFACE_DEFINED__
__IFileDialogEvents_INTERFACE_DEFINED__ equ 1

externdef		IID_IFileDialogEvents:IID
IFileDialogEvents	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	OnFileOk, :ptr
	STDMETHOD	OnFolderChanging, :ptr, :ptr
	STDMETHOD	OnFolderChange, :ptr
	STDMETHOD	OnSelectionChange, :ptr
	STDMETHOD	OnShareViolation, :ptr, :ptr, :ptr
	STDMETHOD	OnTypeChange, :ptr
	STDMETHOD	OnOverwrite, :ptr, :ptr, :ptr


IFileDialogEvents	ENDS

endif

externdef		__MIDL_itf_shobjidl_0000_0130_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0130_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFileDialog_INTERFACE_DEFINED__
__IFileDialog_INTERFACE_DEFINED__ equ 1

FOS_OVERWRITEPROMPT	equ 0x2
FOS_STRICTFILETYPES	equ 0x4
FOS_NOCHANGEDIR		equ 0x8
FOS_PICKFOLDERS		equ 0x20
FOS_FORCEFILESYSTEM	equ 0x40
FOS_ALLNONSTORAGEITEMS	equ 0x80
FOS_NOVALIDATE		equ 0x100
FOS_ALLOWMULTISELECT	equ 0x200
FOS_PATHMUSTEXIST	equ 0x800
FOS_FILEMUSTEXIST	equ 0x1000
FOS_CREATEPROMPT	equ 0x2000
FOS_SHAREAWARE		equ 0x4000
FOS_NOREADONLYRETURN	equ 0x8000
FOS_NOTESTFILECREATE	equ 0x10000
FOS_HIDEMRUPLACES	equ 0x20000
FOS_HIDEPINNEDPLACES	equ 0x40000
FOS_NODEREFERENCELINKS	equ 0x100000
FOS_DONTADDTORECENT	equ 0x2000000
FOS_FORCESHOWHIDDEN	equ 0x10000000
FOS_DEFAULTNOMINIMODE	equ 0x20000000
FOS_FORCEPREVIEWPANEON	equ 0x40000000
FILEOPENDIALOGOPTIONS	typedef DWORD


externdef		IID_IFileDialog:IID
IFileDialog		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Show, :HWND
	STDMETHOD	SetFileTypes, :UINT, :ptr
	STDMETHOD	SetFileTypeIndex, :UINT
	STDMETHOD	GetFileTypeIndex, :ptr
	STDMETHOD	Advise, :ptr, :ptr
	STDMETHOD	Unadvise, :DWORD
	STDMETHOD	SetOptions, :FILEOPENDIALOGOPTIONS
	STDMETHOD	GetOptions, :ptr
	STDMETHOD	SetDefaultFolder, :ptr
	STDMETHOD	SetFolder, :ptr
	STDMETHOD	GetFolder, :ptr
	STDMETHOD	GetCurrentSelection, :ptr
	STDMETHOD	SetFileName, :LPCWSTR
	STDMETHOD	GetFileName, :ptr
	STDMETHOD	SetTitle, :LPCWSTR
	STDMETHOD	SetOkButtonLabel, :LPCWSTR
	STDMETHOD	SetFileNameLabel, :LPCWSTR
	STDMETHOD	GetResult, :ptr
	STDMETHOD	AddPlace, :ptr, :FDAP
	STDMETHOD	SetDefaultExtension, :LPCWSTR
	STDMETHOD	Close, :HRESULT
	STDMETHOD	SetClientGuid, :REFGUID
	STDMETHOD	ClearClientData
	STDMETHOD	SetFilter, :ptr


IFileDialog		ENDS

endif

ifndef __IFileSaveDialog_INTERFACE_DEFINED__
__IFileSaveDialog_INTERFACE_DEFINED__ equ 1

externdef		IID_IFileSaveDialog:IID
IFileSaveDialog		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Show, :HWND
	STDMETHOD	SetFileTypes, :UINT, :ptr
	STDMETHOD	SetFileTypeIndex, :UINT
	STDMETHOD	GetFileTypeIndex, :ptr
	STDMETHOD	Advise, :ptr, :ptr
	STDMETHOD	Unadvise, :DWORD
	STDMETHOD	SetOptions, :FILEOPENDIALOGOPTIONS
	STDMETHOD	GetOptions, :ptr
	STDMETHOD	SetDefaultFolder, :ptr
	STDMETHOD	SetFolder, :ptr
	STDMETHOD	GetFolder, :ptr
	STDMETHOD	GetCurrentSelection, :ptr
	STDMETHOD	SetFileName, :LPCWSTR
	STDMETHOD	GetFileName, :ptr
	STDMETHOD	SetTitle, :LPCWSTR
	STDMETHOD	SetOkButtonLabel, :LPCWSTR
	STDMETHOD	SetFileNameLabel, :LPCWSTR
	STDMETHOD	GetResult, :ptr
	STDMETHOD	AddPlace, :ptr, :FDAP
	STDMETHOD	SetDefaultExtension, :LPCWSTR
	STDMETHOD	Close, :HRESULT
	STDMETHOD	SetClientGuid, :REFGUID
	STDMETHOD	ClearClientData
	STDMETHOD	SetFilter, :ptr
	STDMETHOD	SetSaveAsItem, :ptr
	STDMETHOD	SetProperties, :ptr
	STDMETHOD	SetCollectedProperties, :ptr, :BOOL
	STDMETHOD	GetProperties, :ptr
	STDMETHOD	ApplyProperties, :ptr, :ptr, :HWND, :ptr


IFileSaveDialog		ENDS

endif

ifndef __IFileOpenDialog_INTERFACE_DEFINED__
__IFileOpenDialog_INTERFACE_DEFINED__ equ 1

externdef		IID_IFileOpenDialog:IID
IFileOpenDialog		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Show, :HWND
	STDMETHOD	SetFileTypes, :UINT, :ptr
	STDMETHOD	SetFileTypeIndex, :UINT
	STDMETHOD	GetFileTypeIndex, :ptr
	STDMETHOD	Advise, :ptr, :ptr
	STDMETHOD	Unadvise, :DWORD
	STDMETHOD	SetOptions, :FILEOPENDIALOGOPTIONS
	STDMETHOD	GetOptions, :ptr
	STDMETHOD	SetDefaultFolder, :ptr
	STDMETHOD	SetFolder, :ptr
	STDMETHOD	GetFolder, :ptr
	STDMETHOD	GetCurrentSelection, :ptr
	STDMETHOD	SetFileName, :LPCWSTR
	STDMETHOD	GetFileName, :ptr
	STDMETHOD	SetTitle, :LPCWSTR
	STDMETHOD	SetOkButtonLabel, :LPCWSTR
	STDMETHOD	SetFileNameLabel, :LPCWSTR
	STDMETHOD	GetResult, :ptr
	STDMETHOD	AddPlace, :ptr, :FDAP
	STDMETHOD	SetDefaultExtension, :LPCWSTR
	STDMETHOD	Close, :HRESULT
	STDMETHOD	SetClientGuid, :REFGUID
	STDMETHOD	ClearClientData
	STDMETHOD	SetFilter, :ptr
	STDMETHOD	GetResults, :ptr
	STDMETHOD	GetSelectedItems, :ptr


IFileOpenDialog		ENDS

endif

CDCONTROLSTATEF		typedef SDWORD
CDCS_INACTIVE		equ 0
CDCS_ENABLED		equ 0x1
CDCS_VISIBLE		equ 0x2
CDCS_ENABLEDVISIBLE	equ 0x3

DEFINE_ENUM_FLAG_OPERATORS(CDCONTROLSTATEF)

externdef		__MIDL_itf_shobjidl_0000_0133_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0133_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFileDialogCustomize_INTERFACE_DEFINED__
__IFileDialogCustomize_INTERFACE_DEFINED__ equ 1

externdef		IID_IFileDialogCustomize:IID
IFileDialogCustomize	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	EnableOpenDropDown, :DWORD
	STDMETHOD	AddMenu, :DWORD, :LPCWSTR
	STDMETHOD	AddPushButton, :DWORD, :LPCWSTR
	STDMETHOD	AddComboBox, :DWORD
	STDMETHOD	AddRadioButtonList, :DWORD
	STDMETHOD	AddCheckButton, :DWORD, :LPCWSTR, :BOOL
	STDMETHOD	AddEditBox, :DWORD, :LPCWSTR
	STDMETHOD	AddSeparator, :DWORD
	STDMETHOD	AddText, :DWORD, :LPCWSTR
	STDMETHOD	SetControlLabel, :DWORD, :LPCWSTR
	STDMETHOD	GetControlState, :DWORD, :ptr
	STDMETHOD	SetControlState, :DWORD, :CDCONTROLSTATEF
	STDMETHOD	GetEditBoxText, :DWORD, :ptr
	STDMETHOD	SetEditBoxText, :DWORD, :LPCWSTR
	STDMETHOD	GetCheckButtonState, :DWORD, :ptr
	STDMETHOD	SetCheckButtonState, :DWORD, :BOOL
	STDMETHOD	AddControlItem, :DWORD, :DWORD, :LPCWSTR
	STDMETHOD	RemoveControlItem, :DWORD, :DWORD
	STDMETHOD	RemoveAllControlItems, :DWORD
	STDMETHOD	GetControlItemState, :DWORD, :DWORD, :ptr
	STDMETHOD	SetControlItemState, :DWORD, :DWORD, :CDCONTROLSTATEF
	STDMETHOD	GetSelectedControlItem, :DWORD, :ptr
	STDMETHOD	SetSelectedControlItem, :DWORD, :DWORD
	STDMETHOD	StartVisualGroup, :DWORD, :LPCWSTR
	STDMETHOD	EndVisualGroup
	STDMETHOD	MakeProminent, :DWORD
	STDMETHOD	SetControlItemText, :DWORD, :DWORD, :LPCWSTR


IFileDialogCustomize	ENDS

endif

ifndef __IFileDialogControlEvents_INTERFACE_DEFINED__
__IFileDialogControlEvents_INTERFACE_DEFINED__ equ 1

externdef		IID_IFileDialogControlEvents:IID
IFileDialogControlEvents STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	OnItemSelected, :ptr, :DWORD, :DWORD
	STDMETHOD	OnButtonClicked, :ptr, :DWORD
	STDMETHOD	OnCheckButtonToggled, :ptr, :DWORD, :BOOL
	STDMETHOD	OnControlActivating, :ptr, :DWORD


IFileDialogControlEvents ENDS

endif

ifndef __IFileDialog2_INTERFACE_DEFINED__
__IFileDialog2_INTERFACE_DEFINED__ equ 1

externdef		IID_IFileDialog2:IID
IFileDialog2		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Show, :HWND
	STDMETHOD	SetFileTypes, :UINT, :ptr
	STDMETHOD	SetFileTypeIndex, :UINT
	STDMETHOD	GetFileTypeIndex, :ptr
	STDMETHOD	Advise, :ptr, :ptr
	STDMETHOD	Unadvise, :DWORD
	STDMETHOD	SetOptions, :FILEOPENDIALOGOPTIONS
	STDMETHOD	GetOptions, :ptr
	STDMETHOD	SetDefaultFolder, :ptr
	STDMETHOD	SetFolder, :ptr
	STDMETHOD	GetFolder, :ptr
	STDMETHOD	GetCurrentSelection, :ptr
	STDMETHOD	SetFileName, :LPCWSTR
	STDMETHOD	GetFileName, :ptr
	STDMETHOD	SetTitle, :LPCWSTR
	STDMETHOD	SetOkButtonLabel, :LPCWSTR
	STDMETHOD	SetFileNameLabel, :LPCWSTR
	STDMETHOD	GetResult, :ptr
	STDMETHOD	AddPlace, :ptr, :FDAP
	STDMETHOD	SetDefaultExtension, :LPCWSTR
	STDMETHOD	Close, :HRESULT
	STDMETHOD	SetClientGuid, :REFGUID
	STDMETHOD	ClearClientData
	STDMETHOD	SetFilter, :ptr
	STDMETHOD	SetCancelButtonLabel, :LPCWSTR
	STDMETHOD	SetNavigationRoot, :ptr


IFileDialog2		ENDS

endif

ASSOCIATIONLEVEL	typedef SDWORD
AL_MACHINE		equ 0
AL_EFFECTIVE		equ ( AL_MACHINE + 1 )
AL_USER			equ ( AL_EFFECTIVE + 1 )

ASSOCIATIONTYPE		typedef SDWORD
AT_FILEEXTENSION	equ 0
AT_URLPROTOCOL		equ ( AT_FILEEXTENSION + 1 )
AT_STARTMENUCLIENT	equ ( AT_URLPROTOCOL + 1 )
AT_MIMETYPE		equ ( AT_STARTMENUCLIENT + 1 )

externdef		__MIDL_itf_shobjidl_0000_0136_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0136_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IApplicationAssociationRegistration_INTERFACE_DEFINED__
__IApplicationAssociationRegistration_INTERFACE_DEFINED__ equ 1

externdef		IID_IApplicationAssociationRegistration:IID
IApplicationAssociationRegistration STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	QueryCurrentDefault, :LPCWSTR, :ASSOCIATIONTYPE, :ASSOCIATIONLEVEL, :ptr
	STDMETHOD	QueryAppIsDefault, :LPCWSTR, :ASSOCIATIONTYPE, :ASSOCIATIONLEVEL, :LPCWSTR, :ptr
	STDMETHOD	QueryAppIsDefaultAll, :ASSOCIATIONLEVEL, :LPCWSTR, :ptr
	STDMETHOD	SetAppAsDefault, :LPCWSTR, :LPCWSTR, :ASSOCIATIONTYPE
	STDMETHOD	SetAppAsDefaultAll, :LPCWSTR
	STDMETHOD	ClearUserAssociations


IApplicationAssociationRegistration ENDS

endif

;SHSTDAPI
SHCreateAssociationRegistration proto WINAPI \
		  riid: REFIID,
		   ppv: PVOID

externdef		__MIDL_itf_shobjidl_0000_0137_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0137_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IApplicationAssociationRegistrationUI_INTERFACE_DEFINED__
__IApplicationAssociationRegistrationUI_INTERFACE_DEFINED__ equ 1

externdef		IID_IApplicationAssociationRegistrationUI:IID
IApplicationAssociationRegistrationUI STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	LaunchAdvancedAssociationUI, :LPCWSTR


IApplicationAssociationRegistrationUI ENDS

endif
endif
;include pshpack1.inc
DELEGATEITEMID		STRUC
cbSize			dw ?
wOuter			dw ?
cbInner			dw ?
rgb			db  1  dup(?)
DELEGATEITEMID		ENDS

;include poppack.inc
PCDELEGATEITEMID	typedef ptr DELEGATEITEMID
PDELEGATEITEMID		typedef ptr DELEGATEITEMID

externdef		__MIDL_itf_shobjidl_0000_0138_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0138_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDelegateFolder_INTERFACE_DEFINED__
__IDelegateFolder_INTERFACE_DEFINED__ equ 1

externdef		IID_IDelegateFolder:IID
IDelegateFolder		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetItemAlloc, :ptr


IDelegateFolder		ENDS

endif

if (_WIN32_IE GE _WIN32_IE_IE60)

externdef		__MIDL_itf_shobjidl_0000_0139_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0139_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IBrowserFrameOptions_INTERFACE_DEFINED__
__IBrowserFrameOptions_INTERFACE_DEFINED__ equ 1

BFO_NONE		equ 0
BFO_BROWSER_PERSIST_SETTINGS equ 0x1
BFO_RENAME_FOLDER_OPTIONS_TOINTERNET equ 0x2
BFO_BOTH_OPTIONS	equ 0x4
BIF_PREFER_INTERNET_SHORTCUT equ 0x8
BFO_BROWSE_NO_IN_NEW_PROCESS equ 0x10
BFO_ENABLE_HYPERLINK_TRACKING equ 0x20
BFO_USE_IE_OFFLINE_SUPPORT equ 0x40
BFO_SUBSTITUE_INTERNET_START_PAGE equ 0x80
BFO_USE_IE_LOGOBANDING	equ 0x100
BFO_ADD_IE_TOCAPTIONBAR equ 0x200
BFO_USE_DIALUP_REF	equ 0x400
BFO_USE_IE_TOOLBAR	equ 0x800
BFO_NO_PARENT_FOLDER_SUPPORT equ 0x1000
BFO_NO_REOPEN_NEXT_RESTART equ 0x2000
BFO_GO_HOME_PAGE	equ 0x4000
BFO_PREFER_IEPROCESS	equ 0x8000
BFO_SHOW_NAVIGATION_CANCELLED equ 0x10000
BFO_USE_IE_STATUSBAR	equ 0x20000
BFO_QUERY_ALL		equ ( SINT  )0xffffffff
BROWSERFRAMEOPTIONS	typedef DWORD

externdef		IID_IBrowserFrameOptions:IID
IBrowserFrameOptions	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetFrameOptions, :BROWSERFRAMEOPTIONS, :ptr


IBrowserFrameOptions	ENDS
LPBROWSERFRAMEOPTIONS	typedef ptr IBrowserFrameOptions

endif
endif

if (_WIN32_IE GE _WIN32_IE_IE60SP2)
NWMF			typedef SDWORD
NWMF_UNLOADING		equ 0x1
NWMF_USERINITED		equ 0x2
NWMF_FIRST		equ 0x4
NWMF_OVERRIDEKEY	equ 0x8
NWMF_SHOWHELP		equ 0x10
NWMF_HTMLDIALOG		equ 0x20
NWMF_FROMDIALOGCHILD	equ 0x40
NWMF_USERREQUESTED	equ 0x80
NWMF_USERALLOWED	equ 0x100
NWMF_FORCEWINDOW	equ 0x10000
NWMF_FORCETAB		equ 0x20000
NWMF_SUGGESTWINDOW	equ 0x40000
NWMF_SUGGESTTAB		equ 0x80000
NWMF_INACTIVETAB	equ 0x100000

DEFINE_ENUM_FLAG_OPERATORS(NWMF)
SID_SNewWindowManager	equ IID_INewWindowManager

externdef		__MIDL_itf_shobjidl_0000_0140_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0140_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __INewWindowManager_INTERFACE_DEFINED__
__INewWindowManager_INTERFACE_DEFINED__ equ 1

externdef		IID_INewWindowManager:IID
INewWindowManager	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	EvaluateNewWindow, :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPCWSTR, :BOOL, :DWORD, :DWORD


INewWindowManager	ENDS

endif

ifndef __IAttachmentExecute_INTERFACE_DEFINED__
__IAttachmentExecute_INTERFACE_DEFINED__ equ 1

ATTACHMENT_PROMPT	typedef SDWORD
ATTACHMENT_PROMPT_NONE	equ 0
ATTACHMENT_PROMPT_SAVE	equ 0x1
ATTACHMENT_PROMPT_EXEC	equ 0x2
ATTACHMENT_PROMPT_EXEC_OR_SAVE	equ 0x3

ATTACHMENT_ACTION	typedef SDWORD
ATTACHMENT_ACTION_CANCEL	equ 0
ATTACHMENT_ACTION_SAVE	equ 0x1
ATTACHMENT_ACTION_EXEC	equ 0x2

externdef		IID_IAttachmentExecute:IID
IAttachmentExecute	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetClientTitle, :LPCWSTR
	STDMETHOD	SetClientGuid, :REFGUID
	STDMETHOD	SetLocalPath, :LPCWSTR
	STDMETHOD	SetFileName, :LPCWSTR
	STDMETHOD	SetSource, :LPCWSTR
	STDMETHOD	SetReferrer, :LPCWSTR
	STDMETHOD	CheckPolicy
	STDMETHOD	Prompt, :HWND, :ATTACHMENT_PROMPT, :ptr
	STDMETHOD	Save
	STDMETHOD	Execute, :HWND, :LPCWSTR, :ptr
	STDMETHOD	SaveWithUI, :HWND
	STDMETHOD	ClearClientState


IAttachmentExecute	ENDS

endif
endif

if (_WIN32_IE GE _WIN32_IE_IE60)
;include pshpack8.inc
SMDATA			STRUC
dwMask			dd ?
dwFlags			dd ?
hmenu			HMENU ?
hwnd			HWND ?
uId			UINT ?
uIdParent		UINT ?
uIdAncestor		UINT ?
punk			LPIUnknown ?
pidlFolder		PIDLIST_ABSOLUTE ?
pidlItem		PUITEMID_CHILD ?
psf			LPIShellFolder ?
pvUserData		PVOID ?
SMDATA			ENDS
LPSMDATA		typedef ptr SMDATA

SMDM_SHELLFOLDER	equ 0x00000001
SMDM_HMENU		equ 0x00000002
SMDM_TOOLBAR		equ 0x00000004
SMINFO			STRUC
dwMask			dd ?
dwType			dd ?
dwFlags			dd ?
iIcon			SINT ?
SMINFO			ENDS
PSMINFO			typedef ptr SMINFO

SHCSCHANGENOTIFYSTRUCT	STRUC
lEvent			LONG ?
pidl1			PCIDLIST_ABSOLUTE ?
pidl2			PCIDLIST_ABSOLUTE ?
SHCSCHANGENOTIFYSTRUCT	ENDS
SMCSHCHANGENOTIFYSTRUCT	 typedef SHCSCHANGENOTIFYSTRUCT
PSMCSHCHANGENOTIFYSTRUCT typedef ptr SHCSCHANGENOTIFYSTRUCT

;include poppack.inc

tagSMINFOMASK		typedef SDWORD
SMIM_TYPE		equ 0x1
SMIM_FLAGS		equ 0x2
SMIM_ICON		equ 0x4

tagSMINFOTYPE		typedef SDWORD
SMIT_SEPARATOR		equ 0x1
SMIT_STRING		equ 0x2

tagSMINFOFLAGS		typedef SDWORD
SMIF_ICON		equ 0x1
SMIF_ACCELERATOR	equ 0x2
SMIF_DROPTARGET		equ 0x4
SMIF_SUBMENU		equ 0x8
SMIF_CHECKED		equ 0x20
SMIF_DROPCASCADE	equ 0x40
SMIF_HIDDEN		equ 0x80
SMIF_DISABLED		equ 0x100
SMIF_TRACKPOPUP		equ 0x200
SMIF_DEMOTED		equ 0x400
SMIF_ALTSTATE		equ 0x800
SMIF_DRAGNDROP		equ 0x1000
SMIF_NEW		equ 0x2000
SMC_INITMENU		equ 0x00000001
SMC_CREATE		equ 0x00000002
SMC_EXITMENU		equ 0x00000003
SMC_GETINFO		equ 0x00000005
SMC_GETSFINFO		equ 0x00000006
SMC_GETOBJECT		equ 0x00000007
SMC_GETSFOBJECT		equ 0x00000008
SMC_SFEXEC		equ 0x00000009
SMC_SFSELECTITEM	equ 0x0000000A
SMC_REFRESH		equ 0x00000010
SMC_DEMOTE		equ 0x00000011
SMC_PROMOTE		equ 0x00000012
SMC_DEFAULTICON		equ 0x00000016
SMC_NEWITEM		equ 0x00000017
SMC_CHEVRONEXPAND	equ 0x00000019
SMC_DISPLAYCHEVRONTIP	equ 0x0000002A
SMC_SETSFOBJECT		equ 0x0000002D
SMC_SHCHANGENOTIFY	equ 0x0000002E
SMC_CHEVRONGETTIP	equ 0x0000002F
SMC_SFDDRESTRICTED	equ 0x00000030
if (_WIN32_IE GE _WIN32_IE_IE70)
SMC_SFEXEC_MIDDLE	equ 0x00000031
SMC_GETAUTOEXPANDSTATE	equ 0x00000041
SMC_AUTOEXPANDCHANGE	equ 0x00000042
SMC_GETCONTEXTMENUMODIFIER equ 0x00000043
SMC_GETBKCONTEXTMENU	equ 0x00000044
SMC_OPEN		equ 0x00000045
SMAE_EXPANDED		equ 0x00000001
SMAE_CONTRACTED		equ 0x00000002
SMAE_USER		equ 0x00000004
SMAE_VALID		equ 0x00000007
endif


externdef		__MIDL_itf_shobjidl_0000_0142_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0142_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IShellMenuCallback_INTERFACE_DEFINED__
__IShellMenuCallback_INTERFACE_DEFINED__ equ 1

externdef		IID_IShellMenuCallback:IID
IShellMenuCallback	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	CallbackSM, :LPSMDATA, :UINT, :WPARAM, :LPARAM


IShellMenuCallback	ENDS

endif

SMINIT_DEFAULT		equ 0x00000000
SMINIT_RESTRICT_DRAGDROP equ 0x00000002
SMINIT_TOPLEVEL		equ 0x00000004
SMINIT_CACHED		equ 0x00000010
if (_WIN32_IE GE _WIN32_IE_IE70)
SMINIT_AUTOEXPAND	equ 0x00000100
SMINIT_AUTOTOOLTIP	equ 0x00000200
SMINIT_DROPONCONTAINER	equ 0x00000400
endif
SMINIT_VERTICAL		equ 0x10000000
SMINIT_HORIZONTAL	equ 0x20000000
ANCESTORDEFAULT		equ -1
SMSET_TOP		equ 0x10000000
SMSET_BOTTOM		equ 0x20000000
SMSET_DONTOWN		equ 0x00000001
SMINV_REFRESH		equ 0x00000001
SMINV_ID		equ 0x00000008

externdef		__MIDL_itf_shobjidl_0000_0143_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0143_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IShellMenu_INTERFACE_DEFINED__
__IShellMenu_INTERFACE_DEFINED__ equ 1

externdef		IID_IShellMenu:IID
IShellMenu		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Initialize, :ptr, :UINT, :UINT, :DWORD
	STDMETHOD	GetMenuInfo, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	SetShellFolder, :ptr, :PCIDLIST_ABSOLUTE, :HKEY, :DWORD
	STDMETHOD	GetShellFolder, :ptr, :ptr, :REFIID, :ptr
	STDMETHOD	SetMenu, :HMENU, :HWND, :DWORD
	STDMETHOD	GetMenu, :ptr, :ptr, :ptr
	STDMETHOD	InvalidateItem, :LPSMDATA, :DWORD
	STDMETHOD	GetState, :LPSMDATA
	STDMETHOD	SetMenuToolbar, :ptr, :DWORD


IShellMenu		ENDS

endif
endif

externdef		__MIDL_itf_shobjidl_0000_0144_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0144_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IShellRunDll_INTERFACE_DEFINED__
__IShellRunDll_INTERFACE_DEFINED__ equ 1

externdef		IID_IShellRunDll:IID
IShellRunDll		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Run, :LPCWSTR


IShellRunDll		ENDS

endif

if (NTDDI_VERSION GE NTDDI_VISTA)
KF_CATEGORY		typedef SDWORD
KF_CATEGORY_VIRTUAL	equ 1
KF_CATEGORY_FIXED	equ 2
KF_CATEGORY_COMMON	equ 3
KF_CATEGORY_PERUSER	equ 4

KFDF_LOCAL_REDIRECT_ONLY equ 0x2
KFDF_ROAMABLE		equ 0x4
KFDF_PRECREATE		equ 0x8
KFDF_STREAM		equ 0x10
KFDF_PUBLISHEXPANDEDPATH equ 0x20
KF_DEFINITION_FLAGS	typedef DWORD

KF_REDIRECT_USER_EXCLUSIVE equ 0x1
KF_REDIRECT_COPY_SOURCE_DACL equ 0x2
KF_REDIRECT_OWNER_USER	equ 0x4
KF_REDIRECT_SET_OWNER_EXPLICIT equ 0x8
KF_REDIRECT_CHECK_ONLY	equ 0x10
KF_REDIRECT_WITH_UI	equ 0x20
KF_REDIRECT_UNPIN	equ 0x40
KF_REDIRECT_PIN		equ 0x80
KF_REDIRECT_COPY_CONTENTS equ 0x200
KF_REDIRECT_DEL_SOURCE_CONTENTS equ 0x400
KF_REDIRECT_EXCLUDE_ALL_KNOWN_SUBFOLDERS equ 0x800
KF_REDIRECT_FLAGS	typedef DWORD

KF_REDIRECTION_CAPABILITIES_ALLOW_ALL equ 0xff
KF_REDIRECTION_CAPABILITIES_REDIRECTABLE equ 0x1
KF_REDIRECTION_CAPABILITIES_DENY_ALL equ 0xfff00
KF_REDIRECTION_CAPABILITIES_DENY_POLICY_REDIRECTED equ 0x100
KF_REDIRECTION_CAPABILITIES_DENY_POLICY equ 0x200
KF_REDIRECTION_CAPABILITIES_DENY_PERMISSIONS equ 0x400
KF_REDIRECTION_CAPABILITIES typedef DWORD

KNOWNFOLDER_DEFINITION	STRUC
category		KF_CATEGORY ?
pszName			LPWSTR ?
pszDescription		LPWSTR ?
fidParent		KNOWNFOLDERID <>
pszRelativePath		LPWSTR ?
pszParsingName		LPWSTR ?
pszTooltip		LPWSTR ?
pszLocalizedName	LPWSTR ?
pszIcon			LPWSTR ?
pszSecurity		LPWSTR ?
dwAttributes		dd ?
kfdFlags		KF_DEFINITION_FLAGS ?
ftidType		FOLDERTYPEID <>
KNOWNFOLDER_DEFINITION	ENDS

externdef		__MIDL_itf_shobjidl_0000_0145_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0145_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IKnownFolder_INTERFACE_DEFINED__
__IKnownFolder_INTERFACE_DEFINED__ equ 1

externdef		IID_IKnownFolder:IID
IKnownFolder		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetId, :ptr
	STDMETHOD	GetCategory, :ptr
	STDMETHOD	GetShellItem, :DWORD, :REFIID, :ptr
	STDMETHOD	GetPath, :DWORD, :ptr
	STDMETHOD	SetPath, :DWORD, :LPCWSTR
	STDMETHOD	GetIDList, :DWORD, :ptr
	STDMETHOD	GetFolderType, :ptr
	STDMETHOD	GetRedirectionCapabilities, :ptr
	STDMETHOD	GetFolderDefinition, :ptr


IKnownFolder		ENDS

endif

ifndef __IKnownFolderManager_INTERFACE_DEFINED__
__IKnownFolderManager_INTERFACE_DEFINED__ equ 1

FFFP_MODE		typedef SDWORD
FFFP_EXACTMATCH		equ 0
FFFP_NEARESTPARENTMATCH equ ( FFFP_EXACTMATCH + 1 )

externdef		IID_IKnownFolderManager:IID
IKnownFolderManager	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	FolderIdFromCsidl, :SINT, :ptr
	STDMETHOD	FolderIdToCsidl, :REFKNOWNFOLDERID, :ptr
	STDMETHOD	GetFolderIds, :ptr, :ptr
	STDMETHOD	GetFolder, :REFKNOWNFOLDERID, :ptr
	STDMETHOD	GetFolderByName, :LPCWSTR, :ptr
	STDMETHOD	RegisterFolder, :REFKNOWNFOLDERID, :ptr
	STDMETHOD	UnregisterFolder, :REFKNOWNFOLDERID
	STDMETHOD	FindFolderFromPath, :LPCWSTR, :FFFP_MODE, :ptr
	STDMETHOD	FindFolderFromIDList, :PCIDLIST_ABSOLUTE, :ptr
	STDMETHOD	Redirect, :REFKNOWNFOLDERID, :HWND, :KF_REDIRECT_FLAGS, :LPCWSTR, :UINT, :ptr, :ptr


IKnownFolderManager	ENDS

;HRESULT
IKnownFolderManager_RemoteRedirect_Proxy proto WINAPI \
		 _This: ptr IKnownFolderManager,
		  rfid: REFKNOWNFOLDERID,
		  hwnd: HWND,
		 flags: KF_REDIRECT_FLAGS,
	 pszTargetPath: LPCWSTR,
	      cFolders: UINT,
	    pExclusion: ptr GUID,
	     ppszError: ptr LPWSTR

;void
IKnownFolderManager_RemoteRedirect_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

SHARE_ROLE		typedef SDWORD
SHARE_ROLE_INVALID	equ -1
SHARE_ROLE_READER	equ 0
SHARE_ROLE_CONTRIBUTOR	equ 1
SHARE_ROLE_CO_OWNER	equ 2
SHARE_ROLE_OWNER	equ 3
SHARE_ROLE_CUSTOM	equ 4
SHARE_ROLE_MIXED	equ 5

DEF_SHARE_ID		typedef SDWORD
DEFSHAREID_USERS	equ 1
DEFSHAREID_PUBLIC	equ 2

externdef		__MIDL_itf_shobjidl_0000_0147_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0147_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ISharingConfigurationManager_INTERFACE_DEFINED__
__ISharingConfigurationManager_INTERFACE_DEFINED__ equ 1

externdef		IID_ISharingConfigurationManager:IID
ISharingConfigurationManager STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	CreateShare, :DEF_SHARE_ID, :SHARE_ROLE
	STDMETHOD	DeleteShare, :DEF_SHARE_ID
	STDMETHOD	ShareExists, :DEF_SHARE_ID
	STDMETHOD	GetSharePermissions, :DEF_SHARE_ID, :ptr
	STDMETHOD	SharePrinters
	STDMETHOD	StopSharingPrinters
	STDMETHOD	ArePrintersShared


ISharingConfigurationManager ENDS

endif
endif

externdef		__MIDL_itf_shobjidl_0000_0148_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0148_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IPreviousVersionsInfo_INTERFACE_DEFINED__
__IPreviousVersionsInfo_INTERFACE_DEFINED__ equ 1

externdef		IID_IPreviousVersionsInfo:IID
IPreviousVersionsInfo	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	AreSnapshotsAvailable, :LPCWSTR, :BOOL, :ptr


IPreviousVersionsInfo	ENDS

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

externdef		__MIDL_itf_shobjidl_0000_0149_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0149_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IRelatedItem_INTERFACE_DEFINED__
__IRelatedItem_INTERFACE_DEFINED__ equ 1

externdef		IID_IRelatedItem:IID
IRelatedItem		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetItemIDList, :ptr
	STDMETHOD	GetItem, :ptr


IRelatedItem		ENDS

endif

ifndef __IIdentityName_INTERFACE_DEFINED__
__IIdentityName_INTERFACE_DEFINED__ equ 1

externdef		IID_IIdentityName:IID
IIdentityName		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetItemIDList, :ptr
	STDMETHOD	GetItem, :ptr


IIdentityName		ENDS

endif

ifndef __IDelegateItem_INTERFACE_DEFINED__
__IDelegateItem_INTERFACE_DEFINED__ equ 1

externdef		IID_IDelegateItem:IID
IDelegateItem		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetItemIDList, :ptr
	STDMETHOD	GetItem, :ptr


IDelegateItem		ENDS

endif

ifndef __ICurrentItem_INTERFACE_DEFINED__
__ICurrentItem_INTERFACE_DEFINED__ equ 1

externdef		IID_ICurrentItem:IID
ICurrentItem		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetItemIDList, :ptr
	STDMETHOD	GetItem, :ptr


ICurrentItem		ENDS

endif

ifndef __ITransferMediumItem_INTERFACE_DEFINED__
__ITransferMediumItem_INTERFACE_DEFINED__ equ 1

externdef		IID_ITransferMediumItem:IID
ITransferMediumItem	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetItemIDList, :ptr
	STDMETHOD	GetItem, :ptr


ITransferMediumItem	ENDS

endif

ifndef __IUseToBrowseItem_INTERFACE_DEFINED__
__IUseToBrowseItem_INTERFACE_DEFINED__ equ 1

externdef		IID_IUseToBrowseItem:IID
IUseToBrowseItem	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetItemIDList, :ptr
	STDMETHOD	GetItem, :ptr


IUseToBrowseItem	ENDS

endif

ifndef __IDisplayItem_INTERFACE_DEFINED__
__IDisplayItem_INTERFACE_DEFINED__ equ 1

externdef		IID_IDisplayItem:IID
IDisplayItem		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetItemIDList, :ptr
	STDMETHOD	GetItem, :ptr


IDisplayItem		ENDS

endif

ifndef __IViewStateIdentityItem_INTERFACE_DEFINED__
__IViewStateIdentityItem_INTERFACE_DEFINED__ equ 1

externdef		IID_IViewStateIdentityItem:IID
IViewStateIdentityItem	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetItemIDList, :ptr
	STDMETHOD	GetItem, :ptr


IViewStateIdentityItem	ENDS

endif

ifndef __IPreviewItem_INTERFACE_DEFINED__
__IPreviewItem_INTERFACE_DEFINED__ equ 1

externdef		IID_IPreviewItem:IID
IPreviewItem		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetItemIDList, :ptr
	STDMETHOD	GetItem, :ptr


IPreviewItem		ENDS

endif
endif

externdef		__MIDL_itf_shobjidl_0000_0158_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0158_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDestinationStreamFactory_INTERFACE_DEFINED__
__IDestinationStreamFactory_INTERFACE_DEFINED__ equ 1

externdef		IID_IDestinationStreamFactory:IID
IDestinationStreamFactory STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetDestinationStream, :ptr


IDestinationStreamFactory ENDS

endif

NMCII_FLAGS		typedef SDWORD
NMCII_ITEMS		equ 0x1
NMCII_FOLDERS		equ 0x2
NMCII_FLAGS		typedef SINT

NMCSAEI_FLAGS		typedef SDWORD
NMCSAEI_SELECT		equ 0
NMCSAEI_EDIT		equ 0x1
NMCSAEI_FLAGS		typedef SINT

externdef		__MIDL_itf_shobjidl_0000_0159_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0159_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __INewMenuClient_INTERFACE_DEFINED__
__INewMenuClient_INTERFACE_DEFINED__ equ 1

externdef		IID_INewMenuClient:IID
INewMenuClient		STRUC

	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	IncludeItems, :ptr
	STDMETHOD	SelectAndEditItem, :PCIDLIST_ABSOLUTE, :NMCSAEI_FLAGS

INewMenuClient		ENDS

endif

SID_SNewMenuClient	equ IID_INewMenuClient
DEFINE_GUID(SID_SCommandBarState, 0xB99EAA5C, 0x3850, 0x4400, 0xBC, 0x33, 0x2C, 0xE5, 0x34, 0x04, 0x8B, 0xF8);
DEFINE_GUID(IID_INewMenuClient, 0xdcb07fdc, 0x3bb5, 0x451c, 0x90,0xbe, 0x96,0x66,0x44,0xfe,0xd7,0xb0)

if (_WIN32_IE GE _WIN32_IE_IE70)

externdef		__MIDL_itf_shobjidl_0000_0160_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0160_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInitializeWithBindCtx_INTERFACE_DEFINED__
__IInitializeWithBindCtx_INTERFACE_DEFINED__ equ 1

externdef		IID_IInitializeWithBindCtx:IID
IInitializeWithBindCtx	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Initialize, :ptr


IInitializeWithBindCtx	ENDS

endif

ifndef __IShellItemFilter_INTERFACE_DEFINED__
__IShellItemFilter_INTERFACE_DEFINED__ equ 1

externdef		IID_IShellItemFilter:IID
IShellItemFilter	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	IncludeItem, :ptr
	STDMETHOD	GetEnumFlagsForItem, :ptr, :ptr


IShellItemFilter	ENDS

endif
endif

externdef		__MIDL_itf_shobjidl_0000_0162_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0162_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __INameSpaceTreeControl_INTERFACE_DEFINED__
__INameSpaceTreeControl_INTERFACE_DEFINED__ equ 1

NSTCS_HASEXPANDOS	equ 0x1
NSTCS_HASLINES		equ 0x2
NSTCS_SINGLECLICKEXPAND equ 0x4
NSTCS_FULLROWSELECT	equ 0x8
NSTCS_SPRINGEXPAND	equ 0x10
NSTCS_HORIZONTALSCROLL	equ 0x20
NSTCS_ROOTHASEXPANDO	equ 0x40
NSTCS_SHOWSELECTIONALWAYS equ 0x80
NSTCS_NOINFOTIP		equ 0x200
NSTCS_EVENHEIGHT	equ 0x400
NSTCS_NOREPLACEOPEN	equ 0x800
NSTCS_DISABLEDRAGDROP	equ 0x1000
NSTCS_NOORDERSTREAM	equ 0x2000
NSTCS_RICHTOOLTIP	equ 0x4000
NSTCS_BORDER		equ 0x8000
NSTCS_NOEDITLABELS	equ 0x10000
NSTCS_TABSTOP		equ 0x20000
NSTCS_FAVORITESMODE	equ 0x80000
NSTCS_AUTOHSCROLL	equ 0x100000
NSTCS_FADEINOUTEXPANDOS equ 0x200000
NSTCS_EMPTYTEXT		equ 0x400000
NSTCS_CHECKBOXES	equ 0x800000
NSTCS_PARTIALCHECKBOXES equ 0x1000000
NSTCS_EXCLUSIONCHECKBOXES equ 0x2000000
NSTCS_DIMMEDCHECKBOXES	equ 0x4000000
NSTCS_NOINDENTCHECKS	equ 0x8000000
NSTCS_ALLOWJUNCTIONS	equ 0x10000000
NSTCS_SHOWTABSBUTTON	equ 0x20000000
NSTCS_SHOWDELETEBUTTON	equ 0x40000000
NSTCS_SHOWREFRESHBUTTON equ 0x80000000
NSTCSTYLE		typedef DWORD

NSTCRS_VISIBLE		equ 0
NSTCRS_HIDDEN		equ 0x1
NSTCRS_EXPANDED		equ 0x2
NSTCROOTSTYLE		typedef DWORD

NSTCIS_NONE		equ 0
NSTCIS_SELECTED		equ 0x1
NSTCIS_EXPANDED		equ 0x2
NSTCIS_BOLD		equ 0x4
NSTCIS_DISABLED		equ 0x8
NSTCIS_SELECTEDNOEXPAND equ 0x10
NSTCITEMSTATE		typedef DWORD

NSTCGNI			typedef SDWORD
NSTCGNI_NEXT		equ 0
NSTCGNI_NEXTVISIBLE	equ 1
NSTCGNI_PREV		equ 2
NSTCGNI_PREVVISIBLE	equ 3
NSTCGNI_PARENT		equ 4
NSTCGNI_CHILD		equ 5
NSTCGNI_FIRSTVISIBLE	equ 6
NSTCGNI_LASTVISIBLE	equ 7

DEFINE_GUID(IID_INameSpaceTreeControl, 0x028212a3, 0xb627, 0x47e9, 0x88,0x56, 0xc1,0x42,0x65,0x55,0x4e,0x4f)

externdef		IID_INameSpaceTreeControl:IID
INameSpaceTreeControl	STRUC

	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Initialize, :HWND, :ptr, :NSTCSTYLE
	STDMETHOD	TreeAdvise, :ptr, :ptr
	STDMETHOD	TreeUnadvise, :DWORD
	STDMETHOD	AppendRoot, :ptr, :SHCONTF, :NSTCROOTSTYLE, :ptr
	STDMETHOD	InsertRoot, :SINT, :ptr, :SHCONTF, :NSTCROOTSTYLE, :ptr
	STDMETHOD	RemoveRoot, :ptr
	STDMETHOD	RemoveAllRoots
	STDMETHOD	GetRootItems, :ptr
	STDMETHOD	SetItemState, :ptr, :NSTCITEMSTATE, :NSTCITEMSTATE
	STDMETHOD	GetItemState, :ptr, :NSTCITEMSTATE, :ptr
	STDMETHOD	GetSelectedItems, :ptr
	STDMETHOD	GetItemCustomState, :ptr, :ptr
	STDMETHOD	SetItemCustomState, :ptr, :SINT
	STDMETHOD	EnsureItemVisible, :ptr
	STDMETHOD	SetTheme, :LPCWSTR
	STDMETHOD	GetNextItem, :ptr, :NSTCGNI, :ptr
	STDMETHOD	HitTest, :ptr, :ptr
	STDMETHOD	GetItemRect, :ptr, :ptr
	STDMETHOD	CollapseAll

INameSpaceTreeControl	ENDS

endif

ifndef __INameSpaceTreeControl2_INTERFACE_DEFINED__
__INameSpaceTreeControl2_INTERFACE_DEFINED__ equ 1

NSTCSTYLE2		typedef SDWORD
NSTCS2_DEFAULT		equ 0
NSTCS2_INTERRUPTNOTIFICATIONS	equ 0x1
NSTCS2_SHOWNULLSPACEMENU equ 0x2
NSTCS2_DISPLAYPADDING	equ 0x4
NSTCS2_DISPLAYPINNEDONLY equ 0x8
NTSCS2_NOSINGLETONAUTOEXPAND	equ 0x10
NTSCS2_NEVERINSERTNONENUMERATED equ 0x20

DEFINE_ENUM_FLAG_OPERATORS(NSTCSTYLE2)

externdef		IID_INameSpaceTreeControl2:IID
INameSpaceTreeControl2	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Initialize, :HWND, :ptr, :NSTCSTYLE
	STDMETHOD	TreeAdvise, :ptr, :ptr
	STDMETHOD	TreeUnadvise, :DWORD
	STDMETHOD	AppendRoot, :ptr, :SHCONTF, :NSTCROOTSTYLE, :ptr
	STDMETHOD	InsertRoot, :SINT, :ptr, :SHCONTF, :NSTCROOTSTYLE, :ptr
	STDMETHOD	RemoveRoot, :ptr
	STDMETHOD	RemoveAllRoots
	STDMETHOD	GetRootItems, :ptr
	STDMETHOD	SetItemState, :ptr, :NSTCITEMSTATE, :NSTCITEMSTATE
	STDMETHOD	GetItemState, :ptr, :NSTCITEMSTATE, :ptr
	STDMETHOD	GetSelectedItems, :ptr
	STDMETHOD	GetItemCustomState, :ptr, :ptr
	STDMETHOD	SetItemCustomState, :ptr, :SINT
	STDMETHOD	EnsureItemVisible, :ptr
	STDMETHOD	SetTheme, :LPCWSTR
	STDMETHOD	GetNextItem, :ptr, :NSTCGNI, :ptr
	STDMETHOD	HitTest, :ptr, :ptr
	STDMETHOD	GetItemRect, :ptr, :ptr
	STDMETHOD	CollapseAll
	STDMETHOD	SetControlStyle, :NSTCSTYLE, :NSTCSTYLE
	STDMETHOD	GetControlStyle, :NSTCSTYLE, :ptr
	STDMETHOD	SetControlStyle2, :NSTCSTYLE2, :NSTCSTYLE2
	STDMETHOD	GetControlStyle2, :NSTCSTYLE2, :ptr


INameSpaceTreeControl2	ENDS

endif

NSTCS2_ALLMASK		equ (NSTCS2_INTERRUPTNOTIFICATIONS OR NSTCS2_SHOWNULLSPACEMENU OR NSTCS2_DISPLAYPADDING)
SID_SNavigationPane	equ IID_INameSpaceTreeControl
ISLBUTTON macro x
	exitm<(NSTCECT_LBUTTON EQ ((x) AND NSTCECT_BUTTON))>
	endm
ISMBUTTON macro x
	exitm<(NSTCECT_MBUTTON EQ ((x) AND NSTCECT_BUTTON))>
	endm
ISRBUTTON macro x
	exitm<(NSTCECT_RBUTTON EQ ((x) AND NSTCECT_BUTTON))>
	endm
ISDBLCLICK macro x
	exitm<(NSTCECT_DBLCLICK EQ ((x) AND NSTCECT_DBLCICK))>
	endm


externdef		__MIDL_itf_shobjidl_0000_0164_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0164_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __INameSpaceTreeControlEvents_INTERFACE_DEFINED__
__INameSpaceTreeControlEvents_INTERFACE_DEFINED__ equ 1

NSTCEHT_NOWHERE		equ 0x1
NSTCEHT_ONITEMICON	equ 0x2
NSTCEHT_ONITEMLABEL	equ 0x4
NSTCEHT_ONITEMINDENT	equ 0x8
NSTCEHT_ONITEMBUTTON	equ 0x10
NSTCEHT_ONITEMRIGHT	equ 0x20
NSTCEHT_ONITEMSTATEICON equ 0x40
NSTCEHT_ONITEM		equ 0x46
NSTCEHT_ONITEMTABBUTTON equ 0x1000
NSTCEHITTEST		typedef DWORD

NSTCECT_LBUTTON		equ 0x1
NSTCECT_MBUTTON		equ 0x2
NSTCECT_RBUTTON		equ 0x3
NSTCECT_BUTTON		equ 0x3
NSTCECT_DBLCLICK	equ 0x4
NSTCECLICKTYPE		typedef DWORD

externdef		IID_INameSpaceTreeControlEvents:IID
INameSpaceTreeControlEvents STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	OnItemClick, :ptr, :NSTCEHITTEST, :NSTCECLICKTYPE
	STDMETHOD	OnPropertyItemCommit, :ptr
	STDMETHOD	OnItemStateChanging, :ptr, :NSTCITEMSTATE, :NSTCITEMSTATE
	STDMETHOD	OnItemStateChanged, :ptr, :NSTCITEMSTATE, :NSTCITEMSTATE
	STDMETHOD	OnSelectionChanged, :ptr
	STDMETHOD	OnKeyboardInput, :UINT, :WPARAM, :LPARAM
	STDMETHOD	OnBeforeExpand, :ptr
	STDMETHOD	OnAfterExpand, :ptr
	STDMETHOD	OnBeginLabelEdit, :ptr
	STDMETHOD	OnEndLabelEdit, :ptr
	STDMETHOD	OnGetToolTip, :ptr, :LPWSTR, :SINT
	STDMETHOD	OnBeforeItemDelete, :ptr
	STDMETHOD	OnItemAdded, :ptr, :BOOL
	STDMETHOD	OnItemDeleted, :ptr, :BOOL
	STDMETHOD	OnBeforeContextMenu, :ptr, :REFIID, :ptr
	STDMETHOD	OnAfterContextMenu, :ptr, :ptr, :REFIID, :ptr
	STDMETHOD	OnBeforeStateImageChange, :ptr
	STDMETHOD	OnGetDefaultIconIndex, :ptr, :ptr, :ptr


INameSpaceTreeControlEvents ENDS

endif


NSTCDHPOS_ONTOP		equ -1

externdef		__MIDL_itf_shobjidl_0000_0165_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0165_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __INameSpaceTreeControlDropHandler_INTERFACE_DEFINED__
__INameSpaceTreeControlDropHandler_INTERFACE_DEFINED__ equ 1

externdef		IID_INameSpaceTreeControlDropHandler:IID
INameSpaceTreeControlDropHandler STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	OnDragEnter, :ptr, :ptr, :BOOL, :DWORD, :ptr
	STDMETHOD	OnDragOver, :ptr, :ptr, :DWORD, :ptr
	STDMETHOD	OnDragPosition, :ptr, :ptr, :SINT, :SINT
	STDMETHOD	OnDrop, :ptr, :ptr, :SINT, :DWORD, :ptr
	STDMETHOD	OnDropPosition, :ptr, :ptr, :SINT, :SINT
	STDMETHOD	OnDragLeave, :ptr


INameSpaceTreeControlDropHandler ENDS

endif

ifndef __INameSpaceTreeAccessible_INTERFACE_DEFINED__
__INameSpaceTreeAccessible_INTERFACE_DEFINED__ equ 1

externdef		IID_INameSpaceTreeAccessible:IID
INameSpaceTreeAccessible STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	OnGetDefaultAccessibilityAction, :ptr, :ptr
	STDMETHOD	OnDoDefaultAccessibilityAction, :ptr
	STDMETHOD	OnGetAccessibilityRole, :ptr, :ptr


INameSpaceTreeAccessible ENDS

endif

ifndef __INameSpaceTreeControlCustomDraw_INTERFACE_DEFINED__
__INameSpaceTreeControlCustomDraw_INTERFACE_DEFINED__ equ 1

NSTCCUSTOMDRAW		STRUC
psi			LPIShellItem ?
uItemState		UINT ?
nstcis			NSTCITEMSTATE ?
pszText			LPCWSTR ?
iImage			SINT ?
himl			HIMAGELIST ?
iLevel			SINT ?
iIndent			SINT ?
NSTCCUSTOMDRAW		ENDS

externdef		IID_INameSpaceTreeControlCustomDraw:IID
INameSpaceTreeControlCustomDraw STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	PrePaSINT, :HDC, :ptr, :ptr
	STDMETHOD	PostPaSINT, :HDC, :ptr
	STDMETHOD	ItemPrePaSINT, :HDC, :ptr, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	ItemPostPaSINT, :HDC, :ptr, :ptr


INameSpaceTreeControlCustomDraw ENDS

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

externdef		__MIDL_itf_shobjidl_0000_0168_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0168_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __INameSpaceTreeControlFolderCapabilities_INTERFACE_DEFINED__
__INameSpaceTreeControlFolderCapabilities_INTERFACE_DEFINED__ equ 1

NSTCFOLDERCAPABILITIES	typedef SDWORD
NSTCFC_NONE		equ 0
NSTCFC_PINNEDITEMFILTERING equ 0x1
NSTCFC_DELAY_REGISTER_NOTIFY equ 0x2

DEFINE_ENUM_FLAG_OPERATORS(NSTCFOLDERCAPABILITIES)

externdef		IID_INameSpaceTreeControlFolderCapabilities:IID
INameSpaceTreeControlFolderCapabilities STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetFolderCapabilities, :NSTCFOLDERCAPABILITIES, :ptr


INameSpaceTreeControlFolderCapabilities ENDS

endif
endif

E_PREVIEWHANDLER_DRM_FAIL equ _HRESULT_TYPEDEF_(0x86420001)
E_PREVIEWHANDLER_NOAUTH equ _HRESULT_TYPEDEF_(0x86420002)
E_PREVIEWHANDLER_NOTFOUND equ _HRESULT_TYPEDEF_(0x86420003)
E_PREVIEWHANDLER_CORRUPT equ _HRESULT_TYPEDEF_(0x86420004)

externdef		__MIDL_itf_shobjidl_0000_0169_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0169_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IPreviewHandler_INTERFACE_DEFINED__
__IPreviewHandler_INTERFACE_DEFINED__ equ 1

externdef		IID_IPreviewHandler:IID
IPreviewHandler		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetWindow, :HWND, :ptr
	STDMETHOD	SetRect, :ptr
	STDMETHOD	DoPreview
	STDMETHOD	Unload
	STDMETHOD	SetFocus
	STDMETHOD	QueryFocus, :ptr
	STDMETHOD	TranslateAccelerator, :ptr


IPreviewHandler		ENDS

endif

ifndef __IPreviewHandlerFrame_INTERFACE_DEFINED__
__IPreviewHandlerFrame_INTERFACE_DEFINED__ equ 1

PREVIEWHANDLERFRAMEINFO STRUC
haccel			HACCEL ?
cAccelEntries		UINT ?
PREVIEWHANDLERFRAMEINFO ENDS

externdef		IID_IPreviewHandlerFrame:IID
IPreviewHandlerFrame	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindowContext, :ptr
	STDMETHOD	TranslateAccelerator, :ptr


IPreviewHandlerFrame	ENDS

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

externdef		__MIDL_itf_shobjidl_0000_0171_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0171_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ITrayDeskBand_INTERFACE_DEFINED__
__ITrayDeskBand_INTERFACE_DEFINED__ equ 1

externdef		IID_ITrayDeskBand:IID
ITrayDeskBand		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	ShowDeskBand, :REFCLSID
	STDMETHOD	HideDeskBand, :REFCLSID
	STDMETHOD	IsDeskBandShown, :REFCLSID
	STDMETHOD	DeskBandRegistrationChanged


ITrayDeskBand		ENDS

endif

ifndef __IBandHost_INTERFACE_DEFINED__
__IBandHost_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_IBandHost, 0xb9075c7c, 0xd48e, 0x403f, 0xab,0x99, 0xd6,0xc7,0x7a,0x10,0x84,0xac)

externdef		IID_IBandHost:IID
IBandHost		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	CreateBand, :REFCLSID, :BOOL, :BOOL, :REFIID, :ptr
	STDMETHOD	SetBandAvailability, :REFCLSID, :BOOL
	STDMETHOD	DestroyBand, :REFCLSID


IBandHost		ENDS

endif

SID_SBandHost		equ IID_IBandHost
EXPLORERPANE		typedef GUID
REFEXPLORERPANE		typedef ptr EXPLORERPANE

externdef		__MIDL_itf_shobjidl_0000_0173_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0173_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IExplorerPaneVisibility_INTERFACE_DEFINED__
__IExplorerPaneVisibility_INTERFACE_DEFINED__ equ 1

EPS_DONTCARE		equ 0
EPS_DEFAULT_ON		equ 0x1
EPS_DEFAULT_OFF		equ 0x2
EPS_STATEMASK		equ 0xffff
EPS_INITIALSTATE	equ 0x10000
EPS_FORCE		equ 0x20000
EXPLORERPANESTATE	typedef DWORD

DEFINE_GUID(IID_IExplorerPaneVisibility, 0xe07010ec, 0xbc17, 0x44c0, 0x97,0xb0, 0x46,0xc7,0xc9,0x5b,0x9e,0xdc)

externdef		IID_IExplorerPaneVisibility:IID
IExplorerPaneVisibility STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetPaneState, :REFEXPLORERPANE, :ptr


IExplorerPaneVisibility ENDS

endif

SID_ExplorerPaneVisibility equ IID_IExplorerPaneVisibility

externdef		__MIDL_itf_shobjidl_0000_0174_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0174_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IContextMenuCB_INTERFACE_DEFINED__
__IContextMenuCB_INTERFACE_DEFINED__ equ 1

externdef		IID_IContextMenuCB:IID
IContextMenuCB		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	CallBack, :ptr, :HWND, :ptr, :UINT, :WPARAM, :LPARAM


IContextMenuCB		ENDS
LPIContextMenuCB	typedef ptr IContextMenuCB

endif
endif

externdef		__MIDL_itf_shobjidl_0000_0175_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0175_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDefaultExtractIconInit_INTERFACE_DEFINED__
__IDefaultExtractIconInit_INTERFACE_DEFINED__ equ 1

externdef		IID_IDefaultExtractIconInit:IID
IDefaultExtractIconInit STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetFlags, :UINT
	STDMETHOD	SetKey, :HKEY
	STDMETHOD	SetNormalIcon, :LPCWSTR, :SINT
	STDMETHOD	SetOpenIcon, :LPCWSTR, :SINT
	STDMETHOD	SetShortcutIcon, :LPCWSTR, :SINT
	STDMETHOD	SetDefaultIcon, :LPCWSTR, :SINT


IDefaultExtractIconInit ENDS

endif

;STDAPI
SHCreateDefaultExtractIcon proto WINAPI \
		  riid: REFIID,
		   ppv: PVOID

externdef		__MIDL_itf_shobjidl_0000_0176_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0176_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IExplorerCommand_INTERFACE_DEFINED__
__IExplorerCommand_INTERFACE_DEFINED__ equ 1

ECS_ENABLED		equ 0
ECS_DISABLED		equ 0x1
ECS_HIDDEN		equ 0x2
ECS_CHECKBOX		equ 0x4
ECS_CHECKED		equ 0x8
ECS_RADIOCHECK		equ 0x10
EXPCMDSTATE		typedef DWORD

ECF_DEFAULT		equ 0
ECF_HASSUBCOMMANDS	equ 0x1
ECF_HASSPLITBUTTON	equ 0x2
ECF_HIDELABEL		equ 0x4
ECF_ISSEPARATOR		equ 0x8
ECF_HASLUASHIELD	equ 0x10
ECF_SEPARATORBEFORE	equ 0x20
ECF_SEPARATORAFTER	equ 0x40
ECF_ISDROPDOWN		equ 0x80
EXPCMDFLAGS		typedef DWORD

externdef		IID_IExplorerCommand:IID
IExplorerCommand	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTitle, :ptr, :ptr
	STDMETHOD	GetIcon, :ptr, :ptr
	STDMETHOD	GetToolTip, :ptr, :ptr
	STDMETHOD	GetCanonicalName, :ptr
	STDMETHOD	GetState, :ptr, :BOOL, :ptr
	STDMETHOD	_Invoke, :ptr, :ptr
	STDMETHOD	GetFlags, :ptr
	STDMETHOD	EnumSubCommands, :ptr


IExplorerCommand	ENDS

endif

ifndef __IExplorerCommandState_INTERFACE_DEFINED__
__IExplorerCommandState_INTERFACE_DEFINED__ equ 1

externdef		IID_IExplorerCommandState:IID
IExplorerCommandState	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetState, :ptr, :BOOL, :ptr


IExplorerCommandState	ENDS

endif

ifndef __IInitializeCommand_INTERFACE_DEFINED__
__IInitializeCommand_INTERFACE_DEFINED__ equ 1

externdef		IID_IInitializeCommand:IID
IInitializeCommand	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Initialize, :LPCWSTR, :ptr


IInitializeCommand	ENDS

endif

ifndef __IEnumExplorerCommand_INTERFACE_DEFINED__
__IEnumExplorerCommand_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumExplorerCommand:IID
IEnumExplorerCommand	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :ULONG, :ptr, :ptr
	STDMETHOD	Skip, :ULONG
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr


IEnumExplorerCommand	ENDS

;STDMETHODCALLTYPE
IEnumExplorerCommand_RemoteNext_Proxy proto WINAPI \
		 _This: ptr IEnumExplorerCommand,
		  celt: ULONG,
	    pUICommand: ptr IExplorerCommand,
	  pceltFetched: LPULONG

;void
IEnumExplorerCommand_RemoteNext_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

ifndef __IExplorerCommandProvider_INTERFACE_DEFINED__
__IExplorerCommandProvider_INTERFACE_DEFINED__ equ 1

externdef		IID_IExplorerCommandProvider:IID
IExplorerCommandProvider STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetCommands, :ptr, :REFIID, :ptr
	STDMETHOD	GetCommand, :REFGUID, :REFIID, :ptr


IExplorerCommandProvider ENDS

endif

ifndef __IMarkupCallback_INTERFACE_DEFINED__
__IMarkupCallback_INTERFACE_DEFINED__ equ 1

externdef		IID_IMarkupCallback:IID
IMarkupCallback		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetState, :DWORD, :UINT
	STDMETHOD	Notify, :DWORD, :SINT, :SINT
	STDMETHOD	InvalidateRect, :DWORD, :ptr
	STDMETHOD	OnCustomDraw, :DWORD, :HDC, :ptr, :DWORD, :SINT, :UINT, :ptr
	STDMETHOD	CustomDrawText, :HDC, :LPCWSTR, :SINT, :ptr, :UINT, :BOOL


IMarkupCallback		ENDS

endif

HTHEME			typedef HANDLE

externdef		__MIDL_itf_shobjidl_0000_0182_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0182_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IControlMarkup_INTERFACE_DEFINED__
__IControlMarkup_INTERFACE_DEFINED__ equ 1

MARKUPSIZE		typedef SDWORD
MARKUPSIZE_CALCWIDTH	equ 0
MARKUPSIZE_CALCHEIGHT	equ ( MARKUPSIZE_CALCWIDTH + 1 )

MARKUPLINKTEXT		typedef SDWORD
MARKUPLINKTEXT_URL	equ 0
MARKUPLINKTEXT_ID	equ ( MARKUPLINKTEXT_URL + 1 )
MARKUPLINKTEXT_TEXT	equ ( MARKUPLINKTEXT_ID + 1 )

MARKUPSTATE_FOCUSED	equ 0x1
MARKUPSTATE_ENABLED	equ 0x2
MARKUPSTATE_VISITED	equ 0x4
MARKUPSTATE_HOT		equ 0x8
MARKUPSTATE_DEFAULTCOLORS equ 0x10
MARKUPSTATE_ALLOWMARKUP equ 0x40000000
MARKUPSTATE		typedef DWORD

MARKUPMESSAGE		typedef SDWORD
MARKUPMESSAGE_KEYEXECUTE  equ 0
MARKUPMESSAGE_CLICKEXECUTE equ ( MARKUPMESSAGE_KEYEXECUTE + 1 )
MARKUPMESSAGE_WANTFOCUS equ ( MARKUPMESSAGE_CLICKEXECUTE + 1 )

externdef		IID_IControlMarkup:IID
IControlMarkup		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetCallback, :ptr
	STDMETHOD	GetCallback, :REFIID, :ptr
	STDMETHOD	SetId, :DWORD
	STDMETHOD	GetId, :ptr
	STDMETHOD	SetFonts, :HFONT, :HFONT
	STDMETHOD	GetFonts, :ptr, :ptr
	STDMETHOD	SetText, :LPCWSTR
	STDMETHOD	GetText, :BOOL, :LPWSTR, :ptr
	STDMETHOD	SetLinkText, :SINT, :UINT, :LPCWSTR
	STDMETHOD	GetLinkText, :SINT, :UINT, :LPWSTR, :ptr
	STDMETHOD	SetRenderFlags, :UINT
	STDMETHOD	GetRenderFlags, :ptr, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	SetThemeRenderFlags, :UINT, :HTHEME, :SINT, :SINT, :SINT
	STDMETHOD	GetState, :SINT, :UINT, :ptr
	STDMETHOD	SetState, :SINT, :UINT, :UINT
	STDMETHOD	DrawText, :HDC, :LPCRECT
	STDMETHOD	SetLinkCursor
	STDMETHOD	CalcIdealSize, :HDC, :UINT, :ptr
	STDMETHOD	SetFocus
	STDMETHOD	KillFocus
	STDMETHOD	IsTabbable
	STDMETHOD	OnButtonDown, :POINT
	STDMETHOD	OnButtonUp, :POINT
	STDMETHOD	OnKeyDown, :UINT
	STDMETHOD	HitTest, :POINT, :ptr
	STDMETHOD	GetLinkRect, :SINT, :ptr
	STDMETHOD	GetControlRect, :ptr
	STDMETHOD	GetLinkCount, :ptr


IControlMarkup		ENDS

endif

ifndef __IInitializeNetworkFolder_INTERFACE_DEFINED__
__IInitializeNetworkFolder_INTERFACE_DEFINED__ equ 1

externdef		IID_IInitializeNetworkFolder:IID
IInitializeNetworkFolder STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Initialize, :PCIDLIST_ABSOLUTE, :PCIDLIST_ABSOLUTE, :UINT, :LPCWSTR, :LPCWSTR


IInitializeNetworkFolder ENDS

endif

CPVIEW			typedef SDWORD
CPVIEW_CLASSIC		equ 0
CPVIEW_ALLITEMS		equ CPVIEW_CLASSIC
CPVIEW_CATEGORY		equ 1
CPVIEW_HOME		equ CPVIEW_CATEGORY

externdef		__MIDL_itf_shobjidl_0000_0184_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0184_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IOpenControlPanel_INTERFACE_DEFINED__
__IOpenControlPanel_INTERFACE_DEFINED__ equ 1

externdef		IID_IOpenControlPanel:IID
IOpenControlPanel	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Open, :LPCWSTR, :LPCWSTR, :ptr
	STDMETHOD	GetPath, :LPCWSTR, :LPWSTR, :UINT
	STDMETHOD	GetCurrentView, :ptr


IOpenControlPanel	ENDS

endif

ifndef __IComputerInfoChangeNotify_INTERFACE_DEFINED__
__IComputerInfoChangeNotify_INTERFACE_DEFINED__ equ 1

externdef		IID_IComputerInfoChangeNotify:IID
IComputerInfoChangeNotify STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	ComputerInfoChanged


IComputerInfoChangeNotify ENDS

endif

STR_FILE_SYS_BIND_DATA	equ <L"File System Bind Data">

externdef		__MIDL_itf_shobjidl_0000_0186_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0186_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFileSystemBindData_INTERFACE_DEFINED__
__IFileSystemBindData_INTERFACE_DEFINED__ equ 1

externdef		IID_IFileSystemBindData:IID
IFileSystemBindData	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetFindData, :ptr
	STDMETHOD	GetFindData, :ptr


IFileSystemBindData	ENDS

endif

ifndef __IFileSystemBindData2_INTERFACE_DEFINED__
__IFileSystemBindData2_INTERFACE_DEFINED__ equ 1

externdef		IID_IFileSystemBindData2:IID
IFileSystemBindData2	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetFindData, :ptr
	STDMETHOD	GetFindData, :ptr
	STDMETHOD	SetFileID, :LARGE_INTEGER
	STDMETHOD	GetFileID, :ptr
	STDMETHOD	SetJunctionCLSID, :REFCLSID
	STDMETHOD	GetJunctionCLSID, :ptr


IFileSystemBindData2	ENDS

endif

if (NTDDI_VERSION GE NTDDI_WIN7)

externdef		__MIDL_itf_shobjidl_0000_0188_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0188_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ICustomDestinationList_INTERFACE_DEFINED__
__ICustomDestinationList_INTERFACE_DEFINED__ equ 1

KNOWNDESTCATEGORY	typedef SDWORD
KDC_FREQUENT		equ 1
KDC_RECENT		equ ( KDC_FREQUENT + 1 )

externdef		IID_ICustomDestinationList:IID
ICustomDestinationList	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetAppID, :LPCWSTR
	STDMETHOD	BeginList, :ptr, :REFIID, :ptr
	STDMETHOD	AppendCategory, :LPCWSTR, :ptr
	STDMETHOD	AppendKnownCategory, :KNOWNDESTCATEGORY
	STDMETHOD	AddUserTasks, :ptr
	STDMETHOD	CommitList
	STDMETHOD	GetRemovedDestinations, :REFIID, :ptr
	STDMETHOD	DeleteList, :LPCWSTR
	STDMETHOD	AbortList


ICustomDestinationList	ENDS

endif

ifndef __IApplicationDestinations_INTERFACE_DEFINED__
__IApplicationDestinations_INTERFACE_DEFINED__ equ 1

externdef		IID_IApplicationDestinations:IID
IApplicationDestinations STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetAppID, :LPCWSTR
	STDMETHOD	RemoveDestination, :ptr
	STDMETHOD	RemoveAllDestinations


IApplicationDestinations ENDS

endif

ifndef __IApplicationDocumentLists_INTERFACE_DEFINED__
__IApplicationDocumentLists_INTERFACE_DEFINED__ equ 1

APPDOCLISTTYPE		typedef SDWORD
ADLT_RECENT		equ 0
ADLT_FREQUENT		equ ( ADLT_RECENT + 1 )

externdef		IID_IApplicationDocumentLists:IID
IApplicationDocumentLists STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetAppID, :LPCWSTR
	STDMETHOD	GetList, :APPDOCLISTTYPE, :UINT, :REFIID, :ptr


IApplicationDocumentLists ENDS

endif

ifndef __IObjectWithAppUserModelID_INTERFACE_DEFINED__
__IObjectWithAppUserModelID_INTERFACE_DEFINED__ equ 1

externdef		IID_IObjectWithAppUserModelID:IID
IObjectWithAppUserModelID STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetAppID, :LPCWSTR
	STDMETHOD	GetAppID, :ptr


IObjectWithAppUserModelID ENDS

endif

ifndef __IObjectWithProgID_INTERFACE_DEFINED__
__IObjectWithProgID_INTERFACE_DEFINED__ equ 1

externdef		IID_IObjectWithProgID:IID
IObjectWithProgID	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetProgID, :LPCWSTR
	STDMETHOD	GetProgID, :ptr


IObjectWithProgID	ENDS

endif

ifndef __IUpdateIDList_INTERFACE_DEFINED__
__IUpdateIDList_INTERFACE_DEFINED__ equ 1

externdef		IID_IUpdateIDList:IID
IUpdateIDList		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Update, :ptr, :PCUITEMID_CHILD, :ptr


IUpdateIDList		ENDS

endif

;SHSTDAPI
SetCurrentProcessExplicitAppUserModelID proto WINAPI \
		 AppID: PCWSTR

;SHSTDAPI
GetCurrentProcessExplicitAppUserModelID proto WINAPI \
		 AppID: ptr PWSTR

endif


externdef		__MIDL_itf_shobjidl_0000_0194_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0194_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDesktopGadget_INTERFACE_DEFINED__
__IDesktopGadget_INTERFACE_DEFINED__ equ 1

externdef		IID_IDesktopGadget:IID
IDesktopGadget		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	RunGadget, :LPCWSTR


IDesktopGadget		ENDS

endif

HOMEGROUP_SECURITY_GROUP equ <L"HomeUsers">

externdef		__MIDL_itf_shobjidl_0000_0195_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0195_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IHomeGroup_INTERFACE_DEFINED__
__IHomeGroup_INTERFACE_DEFINED__ equ 1

HOMEGROUPSHARINGCHOICES typedef SDWORD
HGSC_NONE		equ 0
HGSC_MUSICLIBRARY	equ 0x1
HGSC_PICTURESLIBRARY	equ 0x2
HGSC_VIDEOSLIBRARY	equ 0x4
HGSC_DOCUMENTSLIBRARY	equ 0x8
HGSC_PRINTERS		equ 0x10

DEFINE_ENUM_FLAG_OPERATORS(HOMEGROUPSHARINGCHOICES)

externdef		IID_IHomeGroup:IID
IHomeGroup		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	IsMember, :ptr
	STDMETHOD	ShowSharingWizard, :HWND, :ptr


IHomeGroup		ENDS

endif

ifndef __IInitializeWithPropertyStore_INTERFACE_DEFINED__
__IInitializeWithPropertyStore_INTERFACE_DEFINED__ equ 1

externdef		IID_IInitializeWithPropertyStore:IID
IInitializeWithPropertyStore STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Initialize, :ptr


IInitializeWithPropertyStore ENDS

endif

ifndef __IOpenSearchSource_INTERFACE_DEFINED__
__IOpenSearchSource_INTERFACE_DEFINED__ equ 1

externdef		IID_IOpenSearchSource:IID
IOpenSearchSource	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetResults, :HWND, :LPCWSTR, :DWORD, :DWORD, :REFIID, :ptr


IOpenSearchSource	ENDS

endif

ifndef __IShellLibrary_INTERFACE_DEFINED__
__IShellLibrary_INTERFACE_DEFINED__ equ 1


LIBRARYFOLDERFILTER	typedef SDWORD
LFF_FORCEFILESYSTEM	equ 1
LFF_STORAGEITEMS	equ 2
LFF_ALLITEMS		equ 3

LIBRARYOPTIONFLAGS	typedef SDWORD
LOF_DEFAULT		equ 0
LOF_PINNEDTONAVPANE	equ 0x1
LOF_MASK_ALL		equ 0x1

DEFINE_ENUM_FLAG_OPERATORS(LIBRARYOPTIONFLAGS)
DEFAULTSAVEFOLDERTYPE	typedef SDWORD
DSFT_DETECT		equ 1
DSFT_PRIVATE		equ ( DSFT_DETECT + 1 )
DSFT_PUBLIC		equ ( DSFT_PRIVATE + 1 )

LIBRARYSAVEFLAGS	typedef SDWORD
LSF_FAILIFTHERE		equ 0
LSF_OVERRIDEEXISTING	equ 0x1
LSF_MAKEUNIQUENAME	equ 0x2

DEFINE_ENUM_FLAG_OPERATORS(LIBRARYSAVEFLAGS)

externdef		IID_IShellLibrary:IID
IShellLibrary		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	LoadLibraryFromItem, :ptr, :DWORD
	STDMETHOD	LoadLibraryFromKnownFolder, :REFKNOWNFOLDERID, :DWORD
	STDMETHOD	AddFolder, :ptr
	STDMETHOD	RemoveFolder, :ptr
	STDMETHOD	GetFolders, :LIBRARYFOLDERFILTER, :REFIID, :ptr
	STDMETHOD	ResolveFolder, :ptr, :DWORD, :REFIID, :ptr
	STDMETHOD	GetDefaultSaveFolder, :DEFAULTSAVEFOLDERTYPE, :REFIID, :ptr
	STDMETHOD	SetDefaultSaveFolder, :DEFAULTSAVEFOLDERTYPE, :ptr
	STDMETHOD	GetOptions, :ptr
	STDMETHOD	SetOptions, :LIBRARYOPTIONFLAGS, :LIBRARYOPTIONFLAGS
	STDMETHOD	GetFolderType, :ptr
	STDMETHOD	SetFolderType, :REFFOLDERTYPEID
	STDMETHOD	GetIcon, :ptr
	STDMETHOD	SetIcon, :LPCWSTR
	STDMETHOD	Commit
	STDMETHOD	Save, :ptr, :LPCWSTR, :LIBRARYSAVEFLAGS, :ptr
	STDMETHOD	SaveInKnownFolder, :REFKNOWNFOLDERID, :LPCWSTR, :LIBRARYSAVEFLAGS, :ptr


IShellLibrary		ENDS

endif

ifndef __ShellObjects_LIBRARY_DEFINED__
__ShellObjects_LIBRARY_DEFINED__ equ 1

SID_PublishingWizard	equ CSID_PublishingWizard

externdef		LIBID_ShellObjects:IID
externdef		CLSID_ShellDesktop:CLSID
externdef		CLSID_ShellFSFolder:CLSID
externdef		CLSID_NetworkPlaces:CLSID
externdef		CLSID_ShellLink:CLSID
externdef		CLSID_QueryCancelAutoPlay:CLSID
externdef		CLSID_DriveSizeCategorizer:CLSID
externdef		CLSID_DriveTypeCategorizer:CLSID
externdef		CLSID_FreeSpaceCategorizer:CLSID
externdef		CLSID_TimeCategorizer:CLSID
externdef		CLSID_SizeCategorizer:CLSID
externdef		CLSID_AlphabeticalCategorizer:CLSID
externdef		CLSID_MergedCategorizer:CLSID
externdef		CLSID_ImageProperties:CLSID
externdef		CLSID_PropertiesUI:CLSID
externdef		CLSID_UserNotification:CLSID
externdef		CLSID_CDBurn:CLSID
externdef		CLSID_TaskbarList:CLSID
externdef		CLSID_StartMenuPin:CLSID
externdef		CLSID_WebWizardHost:CLSID
externdef		CLSID_PublishDropTarget:CLSID
externdef		CLSID_PublishingWizard:CLSID
externdef		CLSID_InternetPrintOrdering:CLSID
externdef		CLSID_ExplorerBrowser:CLSID
externdef		CLSID_ImageRecompress:CLSID
externdef		CLSID_TrayBandSiteService:CLSID
externdef		CLSID_TrayDeskBand:CLSID
externdef		CLSID_AttachmentServices:CLSID
externdef		CLSID_DocPropShellExtension:CLSID
externdef		CLSID_ShellItem:CLSID
externdef		CLSID_NamespaceWalker:CLSID
externdef		CLSID_FileOperation:CLSID
externdef		CLSID_FileOpenDialog:CLSID
externdef		CLSID_FileSaveDialog:CLSID
externdef		CLSID_KnownFolderManager:CLSID
externdef		CLSID_FSCopyHandler:CLSID
externdef		CLSID_SharingConfigurationManager:CLSID
externdef		CLSID_PreviousVersions:CLSID
externdef		CLSID_NetworkConnections:CLSID
externdef		CLSID_NamespaceTreeControl:CLSID
externdef		CLSID_IENamespaceTreeControl:CLSID
externdef		CLSID_ScheduledTasks:CLSID
externdef		CLSID_ApplicationAssociationRegistration:CLSID
externdef		CLSID_ApplicationAssociationRegistrationUI:CLSID
externdef		CLSID_SearchFolderItemFactory:CLSID
externdef		CLSID_OpenControlPanel:CLSID
externdef		CLSID_MailRecipient:CLSID
externdef		CLSID_NetworkExplorerFolder:CLSID
externdef		CLSID_DestinationList:CLSID
externdef		CLSID_ApplicationDestinations:CLSID
externdef		CLSID_ApplicationDocumentLists:CLSID
externdef		CLSID_HomeGroup:CLSID
externdef		CLSID_ShellLibrary:CLSID
externdef		CLSID_AppStartupLink:CLSID
externdef		CLSID_EnumerableObjectCollection:CLSID
externdef		CLSID_DesktopGadget:CLSID

endif



if (NTDDI_VERSION GE NTDDI_VISTA)
;SHSTDAPI
SHGetTemporaryPropertyForItem proto WINAPI \
		   psi: ptr IShellItem,
	       propkey: REFPROPERTYKEY,
	      ppropvar: ptr PROPVARIANT

;SHSTDAPI
SHSetTemporaryPropertyForItem proto WINAPI \
		   psi: ptr IShellItem,
	       propkey: REFPROPERTYKEY,
	       propvar: REFPROPVARIANT

endif
if (NTDDI_VERSION GE NTDDI_WIN7)
if (_WIN32_IE GE _WIN32_IE_IE70)
LIBRARYMANAGEDIALOGOPTIONS typedef sdword
LMD_DEFAULT		equ 0
LMD_ALLOWUNINDEXABLENETWORKLOCATIONS equ 0x1

DEFINE_ENUM_FLAG_OPERATORS(LIBRARYMANAGEDIALOGOPTIONS)
;SHSTDAPI
SHShowManageLibraryUI proto WINAPI \
	    psiLibrary: ptr IShellItem,
	     hwndOwner: HWND,
	      pszTitle: LPCWSTR,
	pszInstruction: LPCWSTR,
	    lmdOptions: LIBRARYMANAGEDIALOGOPTIONS

;SHSTDAPI
SHResolveLibrary proto WINAPI \
	    psiLibrary: ptr IShellItem

endif
endif
if (NTDDI_VERSION GE NTDDI_VISTA)


externdef		__MIDL_itf_shobjidl_0000_0199_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0199_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAssocHandlerInvoker_INTERFACE_DEFINED__
__IAssocHandlerInvoker_INTERFACE_DEFINED__ equ 1



externdef		IID_IAssocHandlerInvoker:IID


IAssocHandlerInvoker	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SupportsSelection
	STDMETHOD	_Invoke


IAssocHandlerInvoker	ENDS

endif

ifndef __IAssocHandler_INTERFACE_DEFINED__
__IAssocHandler_INTERFACE_DEFINED__ equ 1

externdef		IID_IAssocHandler:IID
IAssocHandler		STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetName, :ptr
	STDMETHOD	GetUIName, :ptr
	STDMETHOD	GetIconLocation, :ptr, :ptr
	STDMETHOD	IsRecommended
	STDMETHOD	MakeDefault, :LPCWSTR
	STDMETHOD	_Invoke, :ptr
	STDMETHOD	CreateInvoker, :ptr, :ptr


IAssocHandler		ENDS

endif

ifndef __IEnumAssocHandlers_INTERFACE_DEFINED__
__IEnumAssocHandlers_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumAssocHandlers:IID
IEnumAssocHandlers	STRUC


	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :ULONG, :ptr, :ptr


IEnumAssocHandlers	ENDS

endif

ASSOC_FILTER		typedef SDWORD
ASSOC_FILTER_NONE	equ 0
ASSOC_FILTER_RECOMMENDED equ 0x1
ASSOC_FILTER		typedef SINT

;SHSTDAPI
SHAssocEnumHandlers proto WINAPI \
	      pszExtra: LPCWSTR,
	      afFilter: ASSOC_FILTER,
	 ppEnumHandler: ptr IEnumAssocHandlers

endif
if (NTDDI_VERSION GE NTDDI_WIN7)
;SHSTDAPI
SHAssocEnumHandlersForProtocolByApplication proto WINAPI \
	      protocol: PCWSTR,
		  riid: REFIID,
	  enumHandlers: PVOID

endif

externdef		__MIDL_itf_shobjidl_0000_0202_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shobjidl_0000_0202_v0_0_s_ifspec:RPC_IF_HANDLE


;DWORD
BSTR_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPSTR
BSTR_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;LPSTR
BSTR_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;void
BSTR_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR


;DWORD
HACCEL_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HACCEL

;LPSTR
HACCEL_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HACCEL

;LPSTR
HACCEL_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HACCEL

;void
HACCEL_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr HACCEL


;DWORD
HBITMAP_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HBITMAP

;LPSTR
HBITMAP_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HBITMAP

;LPSTR
HBITMAP_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HBITMAP

;void
HBITMAP_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr HBITMAP


;DWORD
HGLOBAL_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HGLOBAL

;LPSTR
HGLOBAL_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HGLOBAL

;LPSTR
HGLOBAL_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HGLOBAL

;void
HGLOBAL_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr HGLOBAL


;DWORD
HICON_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HICON

;LPSTR
HICON_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HICON

;LPSTR
HICON_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HICON

;void
HICON_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr HICON


;DWORD
HMENU_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HMENU

;LPSTR
HMENU_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HMENU

;LPSTR
HMENU_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HMENU

;void
HMENU_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr HMENU


;DWORD
HWND_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HWND

;LPSTR
HWND_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HWND

;LPSTR
HWND_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HWND

;void
HWND_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr HWND


;DWORD
LPSAFEARRAY_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr LPSAFEARRAY

;LPSTR
LPSAFEARRAY_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr LPSAFEARRAY

;LPSTR
LPSAFEARRAY_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr LPSAFEARRAY

;void
LPSAFEARRAY_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr LPSAFEARRAY


;DWORD
PCIDLIST_ABSOLUTE_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr PCIDLIST_ABSOLUTE

;LPSTR
PCIDLIST_ABSOLUTE_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PCIDLIST_ABSOLUTE

;LPSTR
PCIDLIST_ABSOLUTE_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PCIDLIST_ABSOLUTE

;void
PCIDLIST_ABSOLUTE_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr PCIDLIST_ABSOLUTE


;DWORD
PCUIDLIST_RELATIVE_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr PCUIDLIST_RELATIVE

;LPSTR
PCUIDLIST_RELATIVE_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PCUIDLIST_RELATIVE

;LPSTR
PCUIDLIST_RELATIVE_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PCUIDLIST_RELATIVE

;void
PCUIDLIST_RELATIVE_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr PCUIDLIST_RELATIVE


;DWORD
PCUITEMID_CHILD_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr PCUITEMID_CHILD

;LPSTR
PCUITEMID_CHILD_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PCUITEMID_CHILD

;LPSTR
PCUITEMID_CHILD_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PCUITEMID_CHILD

;void
PCUITEMID_CHILD_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr PCUITEMID_CHILD


;DWORD
PIDLIST_ABSOLUTE_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr PIDLIST_ABSOLUTE

;LPSTR
PIDLIST_ABSOLUTE_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PIDLIST_ABSOLUTE

;LPSTR
PIDLIST_ABSOLUTE_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PIDLIST_ABSOLUTE

;void
PIDLIST_ABSOLUTE_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr PIDLIST_ABSOLUTE


;DWORD
PIDLIST_RELATIVE_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr PIDLIST_RELATIVE

;LPSTR
PIDLIST_RELATIVE_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PIDLIST_RELATIVE

;LPSTR
PIDLIST_RELATIVE_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PIDLIST_RELATIVE

;void
PIDLIST_RELATIVE_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr PIDLIST_RELATIVE


;DWORD
PITEMID_CHILD_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr PITEMID_CHILD

;LPSTR
PITEMID_CHILD_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PITEMID_CHILD

;LPSTR
PITEMID_CHILD_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PITEMID_CHILD

;void
PITEMID_CHILD_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr PITEMID_CHILD


;DWORD
VARIANT_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr VARIANT

;LPSTR
VARIANT_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr VARIANT

;LPSTR
VARIANT_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr VARIANT

;void
VARIANT_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr VARIANT


;DWORD
BSTR_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPSTR
BSTR_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;LPSTR
BSTR_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;void
BSTR_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR


;DWORD
HACCEL_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HACCEL

;LPSTR
HACCEL_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HACCEL

;LPSTR
HACCEL_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HACCEL

;void
HACCEL_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr HACCEL


;DWORD
HBITMAP_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HBITMAP

;LPSTR
HBITMAP_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HBITMAP

;LPSTR
HBITMAP_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HBITMAP

;void
HBITMAP_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr HBITMAP


;DWORD
HGLOBAL_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HGLOBAL

;LPSTR
HGLOBAL_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HGLOBAL

;LPSTR
HGLOBAL_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HGLOBAL

;void
HGLOBAL_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr HGLOBAL


;DWORD
HICON_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HICON

;LPSTR
HICON_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HICON

;LPSTR
HICON_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HICON

;void
HICON_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr HICON


;DWORD
HMENU_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HMENU

;LPSTR
HMENU_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HMENU

;LPSTR
HMENU_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HMENU

;void
HMENU_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr HMENU


;DWORD
HWND_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HWND

;LPSTR
HWND_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HWND

;LPSTR
HWND_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HWND

;void
HWND_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr HWND


;DWORD
LPSAFEARRAY_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr LPSAFEARRAY

;LPSTR
LPSAFEARRAY_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr LPSAFEARRAY

;LPSTR
LPSAFEARRAY_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr LPSAFEARRAY

;void
LPSAFEARRAY_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr LPSAFEARRAY


;DWORD
PCIDLIST_ABSOLUTE_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr PCIDLIST_ABSOLUTE

;LPSTR
PCIDLIST_ABSOLUTE_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PCIDLIST_ABSOLUTE

;LPSTR
PCIDLIST_ABSOLUTE_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PCIDLIST_ABSOLUTE

;void
PCIDLIST_ABSOLUTE_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr PCIDLIST_ABSOLUTE


;DWORD
PCUIDLIST_RELATIVE_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr PCUIDLIST_RELATIVE

;LPSTR
PCUIDLIST_RELATIVE_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PCUIDLIST_RELATIVE

;LPSTR
PCUIDLIST_RELATIVE_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PCUIDLIST_RELATIVE

;void
PCUIDLIST_RELATIVE_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr PCUIDLIST_RELATIVE


;DWORD
PCUITEMID_CHILD_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr PCUITEMID_CHILD

;LPSTR
PCUITEMID_CHILD_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PCUITEMID_CHILD

;LPSTR
PCUITEMID_CHILD_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PCUITEMID_CHILD

;void
PCUITEMID_CHILD_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr PCUITEMID_CHILD


;DWORD
PIDLIST_ABSOLUTE_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr PIDLIST_ABSOLUTE

;LPSTR
PIDLIST_ABSOLUTE_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PIDLIST_ABSOLUTE

;LPSTR
PIDLIST_ABSOLUTE_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PIDLIST_ABSOLUTE

;void
PIDLIST_ABSOLUTE_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr PIDLIST_ABSOLUTE


;DWORD
PIDLIST_RELATIVE_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr PIDLIST_RELATIVE

;LPSTR
PIDLIST_RELATIVE_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PIDLIST_RELATIVE

;LPSTR
PIDLIST_RELATIVE_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PIDLIST_RELATIVE

;void
PIDLIST_RELATIVE_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr PIDLIST_RELATIVE


;DWORD
PITEMID_CHILD_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr PITEMID_CHILD

;LPSTR
PITEMID_CHILD_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PITEMID_CHILD

;LPSTR
PITEMID_CHILD_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr PITEMID_CHILD

;void
PITEMID_CHILD_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr PITEMID_CHILD


;DWORD
VARIANT_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr VARIANT

;LPSTR
VARIANT_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr VARIANT

;LPSTR
VARIANT_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr VARIANT

;void
VARIANT_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr VARIANT


;HRESULT
IEnumIDList_Next_Proxy proto WINAPI \
		 _This: ptr IEnumIDList,
		  celt: ULONG,
		 rgelt: ptr PITEMID_CHILD,
	  pceltFetched: ptr ULONG



;HRESULT
IEnumIDList_Next_Stub proto WINAPI \
		 _This: ptr IEnumIDList,
		  celt: ULONG,
		 rgelt: ptr PITEMID_CHILD,
	  pceltFetched: ptr ULONG


;HRESULT
IEnumFullIDList_Next_Proxy proto WINAPI \
		 _This: ptr IEnumFullIDList,
		  celt: ULONG,
		 rgelt: ptr PIDLIST_ABSOLUTE,
	  pceltFetched: ptr ULONG



;HRESULT
IEnumFullIDList_Next_Stub proto WINAPI \
		 _This: ptr IEnumFullIDList,
		  celt: ULONG,
		 rgelt: ptr PIDLIST_ABSOLUTE,
	  pceltFetched: ptr ULONG


;HRESULT
IShellFolder_SetNameOf_Proxy proto WINAPI \
		 _This: ptr IShellFolder,
		  hwnd: HWND,
		  pidl: PCUITEMID_CHILD,
	       pszName: LPCWSTR,
		uFlags: SHGDNF,
	      ppidlOut: ptr PITEMID_CHILD



;HRESULT
IShellFolder_SetNameOf_Stub proto WINAPI \
		 _This: ptr IShellFolder,
		  hwnd: HWND,
		  pidl: PCUITEMID_CHILD,
	       pszName: LPCWSTR,
		uFlags: SHGDNF,
	      ppidlOut: ptr PITEMID_CHILD


;HRESULT
IFolderView2_GetGroupBy_Proxy proto WINAPI \
		 _This: ptr IFolderView2,
		  pkey: ptr PROPERTYKEY,
	   pfAscending: ptr BOOL



;HRESULT
IFolderView2_GetGroupBy_Stub proto WINAPI \
		 _This: ptr IFolderView2,
		  pkey: ptr PROPERTYKEY,
	   pfAscending: ptr BOOL

;HRESULT
IEnumShellItems_Next_Proxy proto WINAPI \
		 _This: ptr IEnumShellItems,
		  celt: ULONG,
		 rgelt: ptr IShellItem,
	  pceltFetched: ptr ULONG

;HRESULT
IEnumShellItems_Next_Stub proto WINAPI \
		 _This: ptr IEnumShellItems,
		  celt: ULONG,
		 rgelt: ptr IShellItem,
	  pceltFetched: ptr ULONG

;HRESULT
IParentAndItem_GetParentAndItem_Proxy proto WINAPI \
		 _This: ptr IParentAndItem,
	   ppidlParent: ptr PIDLIST_ABSOLUTE,
		  ppsf: ptr IShellFolder,
	    ppidlChild: ptr PITEMID_CHILD

;HRESULT
IParentAndItem_GetParentAndItem_Stub proto WINAPI \
		 _This: ptr IParentAndItem,
	   ppidlParent: ptr PIDLIST_ABSOLUTE,
		  ppsf: ptr IShellFolder,
	    ppidlChild: ptr PITEMID_CHILD


;HRESULT
IResultsFolder_AddIDList_Proxy proto WINAPI \
		 _This: ptr IResultsFolder,
		  pidl: PCIDLIST_ABSOLUTE,
	    ppidlAdded: ptr PITEMID_CHILD



;HRESULT
IResultsFolder_AddIDList_Stub proto WINAPI \
		 _This: ptr IResultsFolder,
		  pidl: PCIDLIST_ABSOLUTE,
	    ppidlAdded: ptr PITEMID_CHILD


;HRESULT
IEnumObjects_Next_Proxy proto WINAPI \
		 _This: ptr IEnumObjects,
		  celt: ULONG,
		  riid: REFIID,
		 rgelt: ptr void,
	  pceltFetched: ptr ULONG

;HRESULT
IEnumObjects_Next_Stub proto WINAPI \
		 _This: ptr IEnumObjects,
		  celt: ULONG,
		  riid: REFIID,
		 rgelt: ptr void,
	  pceltFetched: ptr ULONG
;HRESULT
IBandSite_QueryBand_Proxy proto WINAPI \
		 _This: ptr IBandSite,
	      dwBandID: DWORD,
		 ppstb: ptr IDeskBand,
	      pdwState: ptr DWORD,
	       pszName: LPWSTR,
	       cchName: SINT

;HRESULT
IBandSite_QueryBand_Stub proto WINAPI \
		 _This: ptr IBandSite,
	      dwBandID: DWORD,
		 ppstb: ptr IDeskBand,
	      pdwState: ptr DWORD,
	       pszName: LPWSTR,
	       cchName: SINT

;HRESULT
IModalWindow_Show_Proxy proto WINAPI \
		 _This: ptr IModalWindow,
	     hwndOwner: HWND

;HRESULT
IModalWindow_Show_Stub proto WINAPI \
		 _This: ptr IModalWindow,
	     hwndOwner: HWND

;HRESULT
IKnownFolderManager_Redirect_Proxy proto WINAPI \
		 _This: ptr IKnownFolderManager,
		  rfid: REFKNOWNFOLDERID,
		  hwnd: HWND,
		 flags: KF_REDIRECT_FLAGS,
	 pszTargetPath: LPCWSTR,
	      cFolders: UINT,
	    pExclusion: ptr KNOWNFOLDERID,
	     ppszError: ptr LPWSTR

;HRESULT
IKnownFolderManager_Redirect_Stub proto WINAPI \
		 _This: ptr IKnownFolderManager,
		  rfid: REFKNOWNFOLDERID,
		  hwnd: HWND,
		 flags: KF_REDIRECT_FLAGS,
	 pszTargetPath: LPCWSTR,
	      cFolders: UINT,
	    pExclusion: ptr GUID,
	     ppszError: ptr LPWSTR

;HRESULT
IEnumExplorerCommand_Next_Proxy proto WINAPI \
		 _This: ptr IEnumExplorerCommand,
		  celt: ULONG,
	    pUICommand: ptr IExplorerCommand,
	  pceltFetched: ptr ULONG

;HRESULT
IEnumExplorerCommand_Next_Stub proto WINAPI \
		 _This: ptr IEnumExplorerCommand,
		  celt: ULONG,
	    pUICommand: ptr IExplorerCommand,
	  pceltFetched: ptr ULONG

.list
endif ; __shobjidl_h__
