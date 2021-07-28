ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
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
define __shobjidl_h__

ifndef __IContextMenu_FWD_DEFINED__
define __IContextMenu_FWD_DEFINED__
endif
ifndef __IContextMenu2_FWD_DEFINED__
define __IContextMenu2_FWD_DEFINED__
endif
ifndef __IContextMenu3_FWD_DEFINED__
define __IContextMenu3_FWD_DEFINED__
endif
ifndef __IExecuteCommand_FWD_DEFINED__
define __IExecuteCommand_FWD_DEFINED__
endif
ifndef __IPersistFolder_FWD_DEFINED__
define __IPersistFolder_FWD_DEFINED__
endif
ifndef __IRunnableTask_FWD_DEFINED__
define __IRunnableTask_FWD_DEFINED__
endif
ifndef __IShellTaskScheduler_FWD_DEFINED__
define __IShellTaskScheduler_FWD_DEFINED__
endif
ifndef __IQueryCodePage_FWD_DEFINED__
define __IQueryCodePage_FWD_DEFINED__
endif
ifndef __IPersistFolder2_FWD_DEFINED__
define __IPersistFolder2_FWD_DEFINED__
endif
ifndef __IPersistFolder3_FWD_DEFINED__
define __IPersistFolder3_FWD_DEFINED__
endif
ifndef __IPersistIDList_FWD_DEFINED__
define __IPersistIDList_FWD_DEFINED__
endif
ifndef __IEnumIDList_FWD_DEFINED__
define __IEnumIDList_FWD_DEFINED__
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
endif
ifndef __ShellFSFolder_FWD_DEFINED__
__ShellFSFolder_FWD_DEFINED__ equ 1
endif
ifndef __NetworkPlaces_FWD_DEFINED__
__NetworkPlaces_FWD_DEFINED__ equ 1
endif
ifndef __ShellLink_FWD_DEFINED__
__ShellLink_FWD_DEFINED__ equ 1
endif
ifndef __QueryCancelAutoPlay_FWD_DEFINED__
__QueryCancelAutoPlay_FWD_DEFINED__ equ 1
endif
ifndef __DriveSizeCategorizer_FWD_DEFINED__
__DriveSizeCategorizer_FWD_DEFINED__ equ 1
endif
ifndef __DriveTypeCategorizer_FWD_DEFINED__
__DriveTypeCategorizer_FWD_DEFINED__ equ 1
endif
ifndef __FreeSpaceCategorizer_FWD_DEFINED__
__FreeSpaceCategorizer_FWD_DEFINED__ equ 1
endif
ifndef __TimeCategorizer_FWD_DEFINED__
__TimeCategorizer_FWD_DEFINED__ equ 1
endif
ifndef __SizeCategorizer_FWD_DEFINED__
__SizeCategorizer_FWD_DEFINED__ equ 1
endif
ifndef __AlphabeticalCategorizer_FWD_DEFINED__
__AlphabeticalCategorizer_FWD_DEFINED__ equ 1
endif
ifndef __MergedCategorizer_FWD_DEFINED__
__MergedCategorizer_FWD_DEFINED__ equ 1
endif
ifndef __ImageProperties_FWD_DEFINED__
__ImageProperties_FWD_DEFINED__ equ 1
endif
ifndef __PropertiesUI_FWD_DEFINED__
__PropertiesUI_FWD_DEFINED__ equ 1
endif
ifndef __UserNotification_FWD_DEFINED__
__UserNotification_FWD_DEFINED__ equ 1
endif
ifndef __CDBurn_FWD_DEFINED__
__CDBurn_FWD_DEFINED__ equ 1
endif
ifndef __TaskbarList_FWD_DEFINED__
__TaskbarList_FWD_DEFINED__ equ 1
endif
ifndef __StartMenuPin_FWD_DEFINED__
__StartMenuPin_FWD_DEFINED__ equ 1
endif
ifndef __WebWizardHost_FWD_DEFINED__
__WebWizardHost_FWD_DEFINED__ equ 1
endif
ifndef __PublishDropTarget_FWD_DEFINED__
__PublishDropTarget_FWD_DEFINED__ equ 1
endif
ifndef __PublishingWizard_FWD_DEFINED__
__PublishingWizard_FWD_DEFINED__ equ 1
endif
ifndef __InternetPrintOrdering_FWD_DEFINED__
__InternetPrintOrdering_FWD_DEFINED__ equ 1
endif
ifndef __FolderViewHost_FWD_DEFINED__
__FolderViewHost_FWD_DEFINED__ equ 1
endif
ifndef __ExplorerBrowser_FWD_DEFINED__
__ExplorerBrowser_FWD_DEFINED__ equ 1
endif
ifndef __ImageRecompress_FWD_DEFINED__
__ImageRecompress_FWD_DEFINED__ equ 1
endif
ifndef __TrayBandSiteService_FWD_DEFINED__
__TrayBandSiteService_FWD_DEFINED__ equ 1
endif
ifndef __TrayDeskBand_FWD_DEFINED__
__TrayDeskBand_FWD_DEFINED__ equ 1
endif
ifndef __AttachmentServices_FWD_DEFINED__
__AttachmentServices_FWD_DEFINED__ equ 1
endif
ifndef __DocPropShellExtension_FWD_DEFINED__
__DocPropShellExtension_FWD_DEFINED__ equ 1
endif
ifndef __ShellItem_FWD_DEFINED__
__ShellItem_FWD_DEFINED__ equ 1
endif
ifndef __NamespaceWalker_FWD_DEFINED__
__NamespaceWalker_FWD_DEFINED__ equ 1
endif
ifndef __FileOperation_FWD_DEFINED__
__FileOperation_FWD_DEFINED__ equ 1
endif
ifndef __FileOpenDialog_FWD_DEFINED__
__FileOpenDialog_FWD_DEFINED__ equ 1
endif
ifndef __FileSaveDialog_FWD_DEFINED__
__FileSaveDialog_FWD_DEFINED__ equ 1
endif
ifndef __KnownFolderManager_FWD_DEFINED__
__KnownFolderManager_FWD_DEFINED__ equ 1
endif
ifndef __FSCopyHandler_FWD_DEFINED__
__FSCopyHandler_FWD_DEFINED__ equ 1
endif
ifndef __SharingConfigurationManager_FWD_DEFINED__
__SharingConfigurationManager_FWD_DEFINED__ equ 1
endif
ifndef __PreviousVersions_FWD_DEFINED__
__PreviousVersions_FWD_DEFINED__ equ 1
endif
ifndef __NetworkConnections_FWD_DEFINED__
__NetworkConnections_FWD_DEFINED__ equ 1
endif
ifndef __NamespaceTreeControl_FWD_DEFINED__
__NamespaceTreeControl_FWD_DEFINED__ equ 1
endif
ifndef __IENamespaceTreeControl_FWD_DEFINED__
__IENamespaceTreeControl_FWD_DEFINED__ equ 1
endif
ifndef __ScheduledTasks_FWD_DEFINED__
__ScheduledTasks_FWD_DEFINED__ equ 1
endif
ifndef __ApplicationAssociationRegistration_FWD_DEFINED__
__ApplicationAssociationRegistration_FWD_DEFINED__ equ 1
endif
ifndef __ApplicationAssociationRegistrationUI_FWD_DEFINED__
__ApplicationAssociationRegistrationUI_FWD_DEFINED__ equ 1
endif
ifndef __SearchFolderItemFactory_FWD_DEFINED__
__SearchFolderItemFactory_FWD_DEFINED__ equ 1
endif
ifndef __OpenControlPanel_FWD_DEFINED__
__OpenControlPanel_FWD_DEFINED__ equ 1
endif
ifndef __MailRecipient_FWD_DEFINED__
__MailRecipient_FWD_DEFINED__ equ 1
endif
ifndef __NetworkExplorerFolder_FWD_DEFINED__
__NetworkExplorerFolder_FWD_DEFINED__ equ 1
endif
ifndef __DestinationList_FWD_DEFINED__
__DestinationList_FWD_DEFINED__ equ 1
endif
ifndef __ApplicationDestinations_FWD_DEFINED__
__ApplicationDestinations_FWD_DEFINED__ equ 1
endif
ifndef __ApplicationDocumentLists_FWD_DEFINED__
__ApplicationDocumentLists_FWD_DEFINED__ equ 1
endif
ifndef __HomeGroup_FWD_DEFINED__
__HomeGroup_FWD_DEFINED__ equ 1
endif
ifndef __ShellLibrary_FWD_DEFINED__
__ShellLibrary_FWD_DEFINED__ equ 1
endif
ifndef __AppStartupLink_FWD_DEFINED__
__AppStartupLink_FWD_DEFINED__ equ 1
endif
ifndef __EnumerableObjectCollection_FWD_DEFINED__
__EnumerableObjectCollection_FWD_DEFINED__ equ 1
endif
ifndef __DesktopGadget_FWD_DEFINED__
__DesktopGadget_FWD_DEFINED__ equ 1
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

.pragma comment(lib, shell32)

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

.pragma pack(push, 8)

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

.pragma pack(pop)

ifndef __IContextMenu_INTERFACE_DEFINED__
__IContextMenu_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IContextMenu, "000214e4-0000-0000-c000-000000000046")

.comdef IContextMenu : public IUnknown

    QueryContextMenu	proc :HMENU, :UINT, :UINT, :UINT, :UINT
    InvokeCommand	proc :ptr
    GetCommandString	proc :UINT_PTR, :UINT, :ptr, :LPSTR, :UINT

    .ends

LPCONTEXTMENU		typedef ptr IContextMenu
endif

ifndef __IContextMenu2_INTERFACE_DEFINED__
__IContextMenu2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IContextMenu2, "000214f4-0000-0000-c000-000000000046")

.comdef IContextMenu2 : public IContextMenu

    HandleMenuMsg	proc :UINT, :WPARAM, :LPARAM

    .ends

LPCONTEXTMENU2		typedef ptr IContextMenu2
endif

ifndef __IContextMenu3_INTERFACE_DEFINED__
__IContextMenu3_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IContextMenu3, "BCFCE0A0-EC17-11d0-8D10-00A0C90F2719")

.comdef IContextMenu3 : public IContextMenu2

    HandleMenuMsg2	proc :UINT, :WPARAM, :LPARAM, :ptr

    .ends

LPCONTEXTMENU3		typedef ptr IContextMenu3

endif

ifndef __IExecuteCommand_INTERFACE_DEFINED__
__IExecuteCommand_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IExecuteCommand, "7F9185B0-CB92-43c5-80A9-92277A4F7B54")

.comdef IExecuteCommand : public IUnknown

    SetKeyState		proc :DWORD
    SetParameters	proc :LPCWSTR
    SetPosition		proc :POINT
    SetShowWindow	proc :SINT
    SetNoShowUI		proc :BOOL
    SetDirectory	proc :LPCWSTR
    Execute		proc

    .ends

endif

ifndef __IPersistFolder_INTERFACE_DEFINED__
__IPersistFolder_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPersistFolder, "000214EA-0000-0000-C000-000000000046")

.comdef IPersistFolder : public IPersist

    Initialize		proc :PCIDLIST_ABSOLUTE

    .ends

LPPERSISTFOLDER		typedef ptr IPersistFolder

endif

if (_WIN32_IE GE 0x0400)
IRTIR_TASK_NOT_RUNNING	equ 0
IRTIR_TASK_RUNNING	equ 1
IRTIR_TASK_SUSPENDED	equ 2
IRTIR_TASK_PENDING	equ 3
IRTIR_TASK_FINISHED	equ 4

ifndef __IRunnableTask_INTERFACE_DEFINED__
__IRunnableTask_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRunnableTask, "85788d00-6807-11d0-b810-00c04fd706ec")

.comdef IRunnableTask : public IUnknown

    Run			proc
    Kill		proc :BOOL
    Suspend		proc
    Resume		proc
    IsRunning		proc

    .ends

endif

TOID_NULL		equ <GUID_NULL>
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


ifndef __IShellTaskScheduler_INTERFACE_DEFINED__
__IShellTaskScheduler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellTaskScheduler, "6CCB7BE0-6807-11d0-B810-00C04FD706EC")

.comdef IShellTaskScheduler : public IUnknown

    AddTask		proc :ptr, :REFTASKOWNERID, :DWORD_PTR, :DWORD
    RemoveTasks		proc :REFTASKOWNERID, :DWORD_PTR, :BOOL
    CountTasks		proc :REFTASKOWNERID
    Status		proc :DWORD, :DWORD

    .ends

endif

SID_ShellTaskScheduler	equ <IID_IShellTaskScheduler>

ifndef __IQueryCodePage_INTERFACE_DEFINED__
__IQueryCodePage_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IQueryCodePage, "C7B236CE-EE80-11D0-985F-006008059382")

.comdef IQueryCodePage : public IUnknown

    GetCodePage		proc :ptr
    SetCodePage		proc :UINT

    .ends

endif

ifndef __IPersistFolder2_INTERFACE_DEFINED__
__IPersistFolder2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPersistFolder2, "1AC3D9F0-175C-11d1-95BE-00609797EA4F")

.comdef IPersistFolder2 : public IPersistFolder

    GetCurFolder	proc :ptr

    .ends

endif
endif ; (_WIN32_IE GE 0x0400)

if (_WIN32_IE GE 0x0500)
CSIDL_FLAG_PFTI_TRACKTARGET equ CSIDL_FAG_DONT_VERIFY

.pragma pack(push, 8)

PERSIST_FOLDER_TARGET_INFO STRUC
pidlTargetFolder	PIDLIST_ABSOLUTE ?
szTargetParsingName	WCHAR  260  dup(?)
szNetworkProvider	WCHAR  260  dup(?)
dwAttributes		dd ?
csidl			SINT ?
PERSIST_FOLDER_TARGET_INFO ENDS

.pragma pack(pop)


ifndef __IPersistFolder3_INTERFACE_DEFINED__
__IPersistFolder3_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPersistFolder3, "CEF04FDF-FE72-11d2-87A5-00C04F6837CF")

.comdef IPersistFolder3 : public IPersistFolder2

    InitializeEx	proc :ptr, :PCIDLIST_ABSOLUTE, :ptr
    GetFolderTargetInfo proc :ptr

    .ends

endif
endif

if (NTDDI_VERSION GE NTDDI_WINXP) OR (_WIN32_IE GE _WIN32_IE_IE70)

ifndef __IPersistIDList_INTERFACE_DEFINED__
__IPersistIDList_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPersistIDList, "1079acfc-29bd-11d3-8e0d-00c04f6837d5")

.comdef IPersistIDList : public IPersist

    SetIDList		proc :PCIDLIST_ABSOLUTE
    GetIDList		proc :ptr

    .ends

endif
endif

ifndef __IEnumIDList_INTERFACE_DEFINED__
__IEnumIDList_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEnumIDList, "000214F2-0000-0000-C000-000000000046")

.comdef IEnumIDList : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr

    .ends

LPENUMIDLIST		typedef ptr IEnumIDList
endif

ifndef __IEnumFullIDList_INTERFACE_DEFINED__
__IEnumFullIDList_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEnumFullIDList, "d0191542-7954-4908-bc06-b2360bbe45ba")

.comdef IEnumFullIDList : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr

    .ends

endif

ifndef __IFileSyncMergeHandler_INTERFACE_DEFINED__
__IFileSyncMergeHandler_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IFileSyncMergeHandler, "d97b5aac-c792-433c-975d-35c4eadc7a9d")

.comdef IFileSyncMergeHandler : public IUnknown

    Merge		proc :LPCWSTR, :LPCWSTR, :ptr MERGE_UPDATE_STATUS
    ShowResolveConflictUIAsync proc :LPCWSTR, :HMONITOR

    .ends

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

ifndef __IObjectWithFolderEnumMode_INTERFACE_DEFINED__
__IObjectWithFolderEnumMode_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IObjectWithFolderEnumMode, "6a9d9026-0e6e-464c-b000-42ecc07de673")

.comdef IObjectWithFolderEnumMode : public IUnknown

    SetMode		proc :FOLDER_ENUM_MODE
    GetMode		proc :ptr

    .ends

endif


STR_PARSE_WITH_EXPLICIT_PROGID equ <L"ExplicitProgid">
STR_PARSE_WITH_EXPLICIT_ASSOCAPP equ <L"ExplicitAssociationApp">
STR_PARSE_EXPLICIT_ASSOCIATION_SUCCESSFUL equ <L"ExplicitAssociationSuccessful">
STR_PARSE_AND_CREATE_ITEM equ <L"ParseAndCreateItem">

ifndef __IParseAndCreateItem_INTERFACE_DEFINED__
__IParseAndCreateItem_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IParseAndCreateItem, "67efed0e-e827-4408-b493-78f3982b685c")

.comdef IParseAndCreateItem : public IUnknown

    SetItem		proc :ptr
    GetItem		proc :REFIID, :ptr

    .ends

endif

STR_ITEM_CACHE_CONTEXT	equ <L"ItemCacheContext">
endif ; (NTDDI_VERSION GE NTDDI_WIN7)

ifndef __IShellFolder_INTERFACE_DEFINED__
__IShellFolder_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellFolder, "000214E6-0000-0000-C000-000000000046")

.comdef IShellFolder : public IUnknown

    ParseDisplayName	proc :HWND, :ptr, :LPWSTR, :ptr, :ptr, :ptr
    EnumObjects		proc :HWND, :SHCONTF, :ptr
    BindToObject	proc :PCUIDLIST_RELATIVE, :ptr, :REFIID, :ptr
    BindToStorage	proc :PCUIDLIST_RELATIVE, :ptr, :REFIID, :ptr
    CompareIDs		proc :LPARAM, :PCUIDLIST_RELATIVE, :PCUIDLIST_RELATIVE
    CreateViewObject	proc :HWND, :REFIID, :ptr
    GetAttributesOf	proc :UINT, :PCUITEMID_CHILD_ARRAY, :ptr
    GetUIObjectOf	proc :HWND, :UINT, :PCUITEMID_CHILD_ARRAY, :REFIID, :ptr, :ptr
    GetDisplayNameOf	proc :PCUITEMID_CHILD, :SHGDNF, :ptr
    SetNameOf		proc :HWND, :PCUITEMID_CHILD, :LPCWSTR, :SHGDNF, :ptr

    .ends

LPIShellFolder		typedef ptr IShellFolder
LPSHELLFOLDER		typedef ptr IShellFolder

endif

EXTRASEARCH		STRUC
guidSearch		GUID <>
wszFriendlyName		WCHAR  80  dup(?)
wszUrl			WCHAR  2084  dup(?)
EXTRASEARCH		ENDS

LPEXTRASEARCH		typedef ptr EXTRASEARCH

ifndef __IEnumExtraSearch_INTERFACE_DEFINED__
__IEnumExtraSearch_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEnumExtraSearch, "0E700BE1-9DB6-11d1-A1CE-00C04FD75D13")

.comdef IEnumExtraSearch : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr

    .ends
    LPENUMEXTRASEARCH	typedef ptr IEnumExtraSearch
endif

ifndef __IShellFolder2_INTERFACE_DEFINED__
__IShellFolder2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellFolder2, "93F2F68C-1D1B-11d3-A30E-00C04F79ABD1")

.comdef IShellFolder2 : public IShellFolder

    GetDefaultSearchGUID proc :ptr
    EnumSearches	proc :ptr
    GetDefaultColumn	proc :DWORD, :ptr, :ptr
    GetDefaultColumnState proc :UINT, :ptr
    GetDetailsEx	proc :PCUITEMID_CHILD, :ptr, :ptr
    GetDetailsOf	proc :PCUITEMID_CHILD, :UINT, :ptr
    MapColumnToSCID	proc :UINT, :ptr

    .ends

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

DEFINE_IIDX(IFolderViewOptions, "3cc974d2-b302-4d36-ad3e-06d93f695d3f")

.comdef IFolderViewOptions : public IUnknown

    SetFolderViewOptions proc :FOLDERVIEWOPTIONS, :FOLDERVIEWOPTIONS
    GetFolderViewOptions proc :ptr

    .ends

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
LPFNSVADDPROPSHEETPAGE	typedef LPFNADDPROPSHEETPAGE
endif

ifndef __IShellView_INTERFACE_DEFINED__
__IShellView_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellView, "000214E3-0000-0000-C000-000000000046")

.comdef IShellView : public IOleWindow

    TranslateAccelerator proc :ptr
    EnableModeless	proc :BOOL
    UIActivate		proc :UINT
    Refresh		proc
    CreateViewWindow	proc :ptr, :LPCFOLDERSETTINGS, :ptr, :ptr, :ptr
    DestroyViewWindow	proc
    GetCurrentInfo	proc :LPFOLDERSETTINGS
    AddPropertySheetPages proc :DWORD, :LPFNSVADDPROPSHEETPAGE, :LPARAM
    SaveViewState	proc
    SelectItem		proc :PCUITEMID_CHILD, :SVSIF
    GetItemObject	proc :UINT, :REFIID, :ptr

    .ends
    LPSHELLVIEW		typedef ptr IShellView
endif

ifndef __IShellView2_INTERFACE_DEFINED__
__IShellView2_INTERFACE_DEFINED__ equ 1

SHELLVIEWID		typedef GUID
LPSHELLVIEWID		typedef ptr SHELLVIEWID
LPIShellBrowser		typedef ptr IShellBrowser

SV2GV_CURRENTVIEW	equ -1
SV2GV_DEFAULTVIEW	equ -2

.pragma pack(push, 8)

SV2CVW2_PARAMS		STRUC
cbSize			dd ?
psvPrev			LPSHELLVIEW ?
pfs			LPCFOLDERSETTINGS ?
psbOwner		LPIShellBrowser ?
prcView			LPRECT ?
pvid			LPSHELLVIEWID ?
hwndView		HWND ?
SV2CVW2_PARAMS		ENDS
LPSV2CVW2_PARAMS	typedef ptr SV2CVW2_PARAMS

.pragma pack(pop)

DEFINE_IIDX(IShellView2, "88E39E80-3578-11CF-AE69-08002B2E1262")

.comdef IShellView2 : public IShellView

    GetView		proc :ptr, :ULONG
    CreateViewWindow2	proc :LPSV2CVW2_PARAMS
    HandleRename	proc :PCUITEMID_CHILD
    SelectAndPositionItem proc :PCUITEMID_CHILD, :UINT, :ptr

    .ends

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

ifndef __IShellView3_INTERFACE_DEFINED__
__IShellView3_INTERFACE_DEFINED__ equ 1

SV3CVW3_DEFAULT		equ 0
SV3CVW3_NONINTERACTIVE	equ 0x1
SV3CVW3_FORCEVIEWMODE	equ 0x2
SV3CVW3_FORCEFOLDERFLAGS equ 0x4
SV3CVW3_FLAGS		typedef DWORD

DEFINE_IIDX(IShellView3, "ec39fa88-f8af-41c5-8421-38bed28f4673")

.comdef IShellView3 : public IShellView2

    CreateViewWindow3	proc :ptr, :ptr, :SV3CVW3_FLAGS, :FOLDERFLAGS,
		:FOLDERFLAGS, :FOLDERVIEWMODE, :ptr, :ptr, :ptr

    .ends

endif
endif

ifdef _FIX_ENABLEMODELESS_CONFLICT
undef	  EnableModeless
endif

ifndef __IFolderView_INTERFACE_DEFINED__
__IFolderView_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFolderView, "cde725b0-ccc9-4519-917e-325d72fab4ce")

.comdef IFolderView : public IUnknown

    GetCurrentViewMode	proc :ptr
    SetCurrentViewMode	proc :UINT
    GetFolder		proc :REFIID, :ptr
    Item		proc :SINT, :ptr
    ItemCount		proc :UINT, :ptr
    Items		proc :UINT, :REFIID, :ptr
    GetSelectionMarkedItem proc :ptr
    GetFocusedItem	proc :ptr
    GetItemPosition	proc :PCUITEMID_CHILD, :ptr
    GetSpacing		proc :ptr
    GetDefaultSpacing	proc :ptr
    GetAutoArrange	proc
    SelectItem		proc :SINT, :DWORD
    SelectAndPositionItems proc :UINT, :PCUITEMID_CHILD_ARRAY, :ptr, :DWORD

    .ends

endif

SID_SFolderView		equ <IID_IFolderView>
if (NTDDI_VERSION GE NTDDI_WIN7)

ifndef __ISearchBoxInfo_INTERFACE_DEFINED__
__ISearchBoxInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISearchBoxInfo, "6af6e03f-d664-4ef4-9626-f7e0ed36755e")

.comdef ISearchBoxInfo : public IUnknown

    GetCondition	proc :REFIID, :ptr
    GetText		proc :ptr

    .ends

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

DEFINE_IIDX(IFolderView2, "1af3a467-214f-4298-908e-06b03e0b39f9")

.comdef IFolderView2 : public IFolderView

    SetGroupBy		proc :REFPROPERTYKEY, :BOOL
    GetGroupBy		proc :ptr, :ptr
    SetViewProperty	proc :PCUITEMID_CHILD, :REFPROPERTYKEY, :REFPROPVARIANT
    GetViewProperty	proc :PCUITEMID_CHILD, :REFPROPERTYKEY, :ptr
    SetTileViewProperties proc :PCUITEMID_CHILD, :LPCWSTR
    SetExtendedTileViewProperties proc :PCUITEMID_CHILD, :LPCWSTR
    SetText		proc :FVTEXTTYPE, :LPCWSTR
    SetCurrentFolderFlags proc :DWORD, :DWORD
    GetCurrentFolderFlags proc :ptr
    GetSortColumnCount	proc :ptr
    SetSortColumns	proc :ptr, :SINT
    GetSortColumns	proc :ptr, :SINT
    GetItem		proc :SINT, :REFIID, :ptr
    GetVisibleItem	proc :SINT, :BOOL, :ptr
    GetSelectedItem	proc :SINT, :ptr
    GetSelection	proc :BOOL, :ptr
    GetSelectionState	proc :PCUITEMID_CHILD, :ptr
    InvokeVerbOnSelection proc :LPCSTR
    SetViewModeAndIconSize proc :FOLDERVIEWMODE, :SINT
    GetViewModeAndIconSize proc :ptr, :ptr
    SetGroupSubsetCount proc :UINT
    GetGroupSubsetCount proc :ptr
    SetRedraw		proc :BOOL
    IsMoveInSameFolder	proc
    DoRename		proc

    .ends

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

ifndef __IFolderViewSettings_INTERFACE_DEFINED__
__IFolderViewSettings_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFolderViewSettings, "ae8c987d-8797-4ed3-be72-2a47dd938db0")

.comdef IFolderViewSettings : public IUnknown

    GetColumnPropertyList proc :REFIID, :ptr
    GetGroupByProperty	proc :ptr, :ptr
    GetViewMode		proc :ptr
    GetIconSize		proc :ptr
    GetFolderFlags	proc :ptr, :ptr
    GetSortColumns	proc :ptr, :UINT, :ptr
    GetGroupSubsetCount proc :ptr

    .ends

endif ; __IFolderViewSettings_INTERFACE_DEFINED__
endif ; (NTDDI_VERSION GE NTDDI_VISTA)

if (_WIN32_IE GE _WIN32_IE_IE70)

ifndef __IPreviewHandlerVisuals_INTERFACE_DEFINED__
__IPreviewHandlerVisuals_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPreviewHandlerVisuals, "196bf9a5-b346-4ef0-aa1e-5dcdb76768b1")

.comdef IPreviewHandlerVisuals : public IUnknown

    SetBackgroundColor	proc :COLORREF
    SetFont		proc :ptr
    SetTextColor	proc :COLORREF

    .ends

endif

ifndef __IVisualProperties_INTERFACE_DEFINED__
__IVisualProperties_INTERFACE_DEFINED__ equ 1

VPWATERMARKFLAGS	typedef SDWORD
VPWF_DEFAULT		equ 0
VPWF_ALPHABLEND		equ 0x1

VPCOLORFLAGS		typedef SDWORD
VPCF_TEXT		equ 1
VPCF_BACKGROUND		equ 2
VPCF_SORTCOLUMN		equ 3
VPCF_SUBTEXT		equ 4
VPCF_TEXTBACKGROUND	equ 5

DEFINE_IIDX(IVisualProperties, "e693cf68-d967-4112-8763-99172aee5e5a")

.comdef IVisualProperties : public IUnknown

    SetWatermark	proc :HBITMAP, :VPWATERMARKFLAGS
    SetColor		proc :VPCOLORFLAGS, :COLORREF
    GetColor		proc :VPCOLORFLAGS, :ptr
    SetItemHeight	proc :SINT
    GetItemHeight	proc :ptr
    SetFont		proc :ptr, :BOOL
    GetFont		proc :ptr
    SetTheme		proc :LPCWSTR, :LPCWSTR

    .ends

endif

endif

CDBOSC_SETFOCUS		equ 0x00000000
CDBOSC_KILLFOCUS	equ 0x00000001
CDBOSC_SELCHANGE	equ 0x00000002
CDBOSC_RENAME		equ 0x00000003
CDBOSC_STATECHANGE	equ 0x00000004

ifndef __ICommDlgBrowser_INTERFACE_DEFINED__
__ICommDlgBrowser_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICommDlgBrowser, "000214F1-0000-0000-C000-000000000046")

.comdef ICommDlgBrowser : public IUnknown

    OnDefaultCommand	proc :ptr
    OnStateChange	proc :ptr, :ULONG
    IncludeObject	proc :ptr, :PCUITEMID_CHILD

    .ends

endif

LPCOMMDLGBROWSER	typedef ptr ICommDlgBrowser

SID_SExplorerBrowserFrame equ <IID_ICommDlgBrowser>
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

ifndef __ICommDlgBrowser2_INTERFACE_DEFINED__
__ICommDlgBrowser2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICommDlgBrowser2, "10339516-2894-11d2-9039-00C04F8EEB3E")

.comdef ICommDlgBrowser2 : public ICommDlgBrowser

    Notify		proc :ptr, :DWORD
    GetDefaultMenuText	proc :ptr, :LPWSTR, :SINT
    GetViewFlags	proc :ptr

    .ends

LPCOMMDLGBROWSER2	typedef ptr ICommDlgBrowser2

endif

endif
if (_WIN32_IE GE _WIN32_IE_IE70)

ifndef __ICommDlgBrowser3_INTERFACE_DEFINED__
__ICommDlgBrowser3_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICommDlgBrowser3, "c8ad25a1-3294-41ee-8165-71174bd01c57")

.comdef ICommDlgBrowser3 : public ICommDlgBrowser2

    OnColumnClicked	proc :ptr, :SINT
    GetCurrentFilter	proc :LPWSTR, :SINT
    OnPreViewCreated	proc :ptr

    .ends

endif

CM_MASK			typedef SDWORD
CM_MASK_WIDTH		equ 0x1
CM_MASK_DEFAULTWIDTH	equ 0x2
CM_MASK_IDEALWIDTH	equ 0x4
CM_MASK_NAME		equ 0x8
CM_MASK_STATE		equ 0x10

CM_STATE		typedef SDWORD
CM_STATE_NONE		equ 0
CM_STATE_VISIBLE	equ 0x1
CM_STATE_FIXEDWIDTH	equ 0x2
CM_STATE_NOSORTBYFOLDERNESS equ 0x4
CM_STATE_ALWAYSVISIBLE	equ 0x8

CM_ENUM_FLAGS		typedef SDWORD
CM_ENUM_ALL		equ 0x1
CM_ENUM_VISIBLE		equ 0x2

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

ifndef __IColumnManager_INTERFACE_DEFINED__
__IColumnManager_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IColumnManager, "d8ec27bb-3f3b-4042-b10a-4acfd924d453")

.comdef IColumnManager : public IUnknown

    SetColumnInfo	proc :REFPROPERTYKEY, :ptr
    GetColumnInfo	proc :REFPROPERTYKEY, :ptr
    GetColumnCount	proc :CM_ENUM_FLAGS, :ptr
    GetColumns		proc :CM_ENUM_FLAGS, :ptr, :UINT
    SetColumns		proc :ptr, :UINT

    .ends

endif
endif

ifndef __IFolderFilterSite_INTERFACE_DEFINED__
__IFolderFilterSite_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFolderFilterSite, "C0A651F5-B48B-11d2-B5ED-006097C686F6")

.comdef IFolderFilterSite : public IUnknown

    SetFilter		proc :ptr

    .ends

endif

ifndef __IFolderFilter_INTERFACE_DEFINED__
__IFolderFilter_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFolderFilter, "9CC22886-DC8E-11d2-B1D0-00C04F8EEB3E")

.comdef IFolderFilter : public IUnknown

    ShouldShow		proc :ptr, :PCIDLIST_ABSOLUTE, :PCUITEMID_CHILD
    GetEnumFlags	proc :ptr, :PCIDLIST_ABSOLUTE, :ptr, :ptr

    .ends

endif

ifndef __IInputObjectSite_INTERFACE_DEFINED__
__IInputObjectSite_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInputObjectSite, "F1DB8392-7331-11D0-8C99-00A0C92DBFE8")

.comdef IInputObjectSite : public IUnknown

    OnFocusChangeIS	proc :ptr, :BOOL

    .ends

endif

ifndef __IInputObject_INTERFACE_DEFINED__
__IInputObject_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInputObject, "68284fAA-6A48-11D0-8c78-00C04fd918b4")

.comdef IInputObject : public IUnknown

    UIActivateIO	proc :BOOL, :ptr
    HasFocusIO		proc
    TranslateAcceleratorIO proc :ptr

    .ends

endif

ifndef __IInputObject2_INTERFACE_DEFINED__
__IInputObject2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInputObject2, "6915C085-510B-44cd-94AF-28DFA56CF92B")

.comdef IInputObject2 : public IInputObject

    TranslateAcceleratorGlobal proc :ptr

    .ends

endif

ifndef __IShellIcon_INTERFACE_DEFINED__
__IShellIcon_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellIcon, "000214E5-0000-0000-C000-000000000046")

.comdef IShellIcon : public IUnknown

    GetIconOf		proc :PCUITEMID_CHILD, :UINT, :ptr

    .ends

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


ifndef __IShellBrowser_INTERFACE_DEFINED__
__IShellBrowser_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellBrowser, "000214E2-0000-0000-C000-000000000046")

.comdef IShellBrowser : public IOleWindow

    InsertMenusSB	proc :HMENU, :LPOLEMENUGROUPWIDTHS
    SetMenuSB		proc :HMENU, :HOLEMENU, :HWND
    RemoveMenusSB	proc :HMENU
    SetStatusTextSB	proc :LPCWSTR
    EnableModelessSB	proc :BOOL
    TranslateAcceleratorSB proc :ptr, :WORD
    BrowseObject	proc :PCUIDLIST_RELATIVE, :UINT
    GetViewStateStream	proc :DWORD, :ptr
    GetControlWindow	proc :UINT, :ptr
    SendControlMsg	proc :UINT, :UINT, :WPARAM, :LPARAM, :ptr
    QueryActiveShellView proc :ptr
    OnViewWindowActive	proc :ptr
    SetToolbarItems	proc :LPTBBUTTONSB, :UINT, :UINT

    .ends

endif

LPSHELLBROWSER		typedef ptr IShellBrowser

ifndef __IProfferService_INTERFACE_DEFINED__
__IProfferService_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IProfferService, "cb728b20-f786-11ce-92ad-00aa00a74cd0")

.comdef IProfferService : public IUnknown

    ProfferService	proc :REFGUID, :ptr, :ptr
    RevokeService	proc :DWORD

    .ends

endif

SID_SProfferService	equ <IID_IProfferService>
STR_DONT_RESOLVE_LINK	equ <L"Don't Resolve Link">
STR_GET_ASYNC_HANDLER	equ <L"GetAsyncHandler">

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

DEFINE_IIDX(IShellItem, "43826d1e-e718-42ee-bc55-a1e261c37bfe")

.comdef IShellItem : public IUnknown

    BindToHandler	proc :ptr, :REFGUID, :REFIID, :ptr
    GetParent		proc :ptr
    GetDisplayName	proc :SIGDN, :ptr
    GetAttributes	proc :SFGAOF, :ptr
    Compare		proc :ptr, :SICHINTF, :ptr

    .ends

LPIShellItem		typedef ptr IShellItem
endif

.pragma comment(lib, shell32)

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

ifndef __IShellItem2_INTERFACE_DEFINED__
__IShellItem2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellItem2, "7e9fb0d3-919f-4307-ab2e-9b1860310c93")

.comdef IShellItem2 : public IShellItem

    GetPropertyStore	proc :GETPROPERTYSTOREFLAGS, :REFIID, :ptr
    GetPropertyStoreWithCreateObject proc :GETPROPERTYSTOREFLAGS, :ptr, :REFIID, :ptr
    GetPropertyStoreForKeys proc :ptr, :UINT, :GETPROPERTYSTOREFLAGS, :REFIID, :ptr
    GetPropertyDescriptionList proc :REFPROPERTYKEY, :REFIID, :ptr
    Update		proc :ptr
    GetProperty		proc :REFPROPERTYKEY, :ptr
    GetCLSID		proc :REFPROPERTYKEY, :ptr
    GetFileTime		proc :REFPROPERTYKEY, :ptr
    GetInt32		proc :REFPROPERTYKEY, :ptr
    GetString		proc :REFPROPERTYKEY, :ptr
    GetUInt32		proc :REFPROPERTYKEY, :ptr
    GetUInt64		proc :REFPROPERTYKEY, :ptr
    GetBool		proc :REFPROPERTYKEY, :ptr

    .ends

endif

SIIGBF_RESIZETOFIT	equ 0
SIIGBF_BIGGERSIZEOK	equ 0x1
SIIGBF_MEMORYONLY	equ 0x2
SIIGBF_ICONONLY		equ 0x4
SIIGBF_THUMBNAILONLY	equ 0x8
SIIGBF_INCACHEONLY	equ 0x10
SIIGBF			typedef SINT

ifndef __IShellItemImageFactory_INTERFACE_DEFINED__
__IShellItemImageFactory_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellItemImageFactory, "bcc18b79-ba16-442f-80c4-8a59c30c463b")

.comdef IShellItemImageFactory : public IUnknown

    GetImage		proc :SIZEL, :SIIGBF, :ptr

    .ends

endif

ifndef __IUserAccountChangeCallback_INTERFACE_DEFINED__
__IUserAccountChangeCallback_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IUserAccountChangeCallback, "a561e69a-b4b8-4113-91a5-64c6bcca3430")

.comdef IUserAccountChangeCallback : public IUnknown

    OnPictureChange	proc :LPCWSTR

    .ends

endif

if (NTDDI_VERSION GE NTDDI_WINXP)

ifndef __IEnumShellItems_INTERFACE_DEFINED__
__IEnumShellItems_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEnumShellItems, "70629033-e363-4a28-a567-0db78006e6d7")

.comdef IEnumShellItems : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr

    .ends

LPIEnumShellItems	typedef ptr IEnumShellItems

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

ifndef __ITransferAdviseSink_INTERFACE_DEFINED__
__ITransferAdviseSink_INTERFACE_DEFINED__ equ 1

TS_NONE			equ 0
TS_PERFORMING		equ 0x1
TS_PREPARING		equ 0x2
TS_INDETERMINATE	equ 0x4
TRANSFER_ADVISE_STATE	typedef DWORD

DEFINE_IIDX(ITransferAdviseSink, "d594d0d8-8da7-457b-b3b4-ce5dbaac0b88")

.comdef ITransferAdviseSink : public IUnknown

    UpdateProgress	proc :ULONGLONG, :ULONGLONG, :SINT, :SINT, :SINT, :SINT
    UpdateTransferState proc :TRANSFER_ADVISE_STATE
    ConfirmOverwrite	proc :ptr, :ptr, :LPCWSTR
    ConfirmEncryptionLoss proc :ptr
    FileFailure		proc :ptr, :LPCWSTR, :HRESULT, :LPWSTR, :ULONG
    SubStreamFailure	proc :ptr, :LPCWSTR, :HRESULT
    PropertyFailure	proc :ptr, :ptr, :HRESULT

    .ends

endif

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

ifndef __ITransferSource_INTERFACE_DEFINED__
__ITransferSource_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ITransferSource, "00adb003-bde9-45c6-8e29-d09f9353e108")

.comdef ITransferSource : public IUnknown

    Advise		proc :ptr, :ptr
    Unadvise		proc :DWORD
    SetProperties	proc :ptr
    OpenItem		proc :ptr, :TRANSFER_SOURCE_FLAGS, :REFIID, :ptr
    MoveItem		proc :ptr, :ptr, :LPCWSTR, :TRANSFER_SOURCE_FLAGS, :ptr
    RecycleItem		proc :ptr, :ptr, :TRANSFER_SOURCE_FLAGS, :ptr
    RemoveItem		proc :ptr, :TRANSFER_SOURCE_FLAGS
    RenameItem		proc :ptr, :LPCWSTR, :TRANSFER_SOURCE_FLAGS, :ptr
    LinkItem		proc :ptr, :ptr, :LPCWSTR, :TRANSFER_SOURCE_FLAGS, :ptr
    ApplyPropertiesToItem proc :ptr, :ptr
    GetDefaultDestinationName proc :ptr, :ptr, :ptr
    EnterFolder		proc :ptr
    LeaveFolder		proc :ptr

    .ends

endif
endif

SHELL_ITEM_RESOURCE	STRUC
guidType		GUID <>
szName			WCHAR  260  dup(?)
SHELL_ITEM_RESOURCE	ENDS

ifndef __IEnumResources_INTERFACE_DEFINED__
__IEnumResources_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEnumResources, "2dd81fe3-a83c-4da9-a330-47249d345ba1")

.comdef IEnumResources : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr

    .ends

endif

ifndef __IShellItemResources_INTERFACE_DEFINED__
__IShellItemResources_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellItemResources, "ff5693be-2ce0-4d48-b5c5-40817d1acdb9")

.comdef IShellItemResources : public IUnknown

    GetAttributes	proc :ptr
    GetSize		proc :ptr
    GetTimes		proc :ptr, :ptr, :ptr
    SetTimes		proc :ptr, :ptr, :ptr
    GetResourceDescription proc :ptr, :ptr
    EnumResources	proc :ptr
    SupportsResource	proc :ptr
    OpenResource	proc :ptr, :REFIID, :ptr
    CreateResource	proc :ptr, :REFIID, :ptr
    MarkForDelete	proc

    .ends

endif

ifndef __ITransferDestination_INTERFACE_DEFINED__
__ITransferDestination_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ITransferDestination, "48addd32-3ca5-4124-abe3-b5a72531b207")

.comdef ITransferDestination : public IUnknown

    Advise		proc :ptr, :ptr
    Unadvise		proc :DWORD
    CreateItem		proc :LPCWSTR, :DWORD, :ULONGLONG, :TRANSFER_SOURCE_FLAGS, :REFIID, :ptr, :REFIID, :ptr

    .ends

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

ifndef __IStreamAsync_INTERFACE_DEFINED__
__IStreamAsync_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IStreamAsync, "fe0b6665-e0ca-49b9-a178-2b5cb48d92a5")

.comdef IStreamAsync : public IStream

    ReadAsync		proc :ptr, :DWORD, :LPDWORD, :LPOVERLAPPED
    WriteAsync		proc :ptr, :DWORD, :LPDWORD, :LPOVERLAPPED
    OverlappedResult	proc :LPOVERLAPPED, :LPDWORD, :BOOL
    CancelIo		proc

    .ends

endif

ifndef __IStreamUnbufferedInfo_INTERFACE_DEFINED__
__IStreamUnbufferedInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IStreamUnbufferedInfo, "8a68fdda-1fdc-4c20-8ceb-416643b5a625")

.comdef IStreamUnbufferedInfo : public IUnknown

    GetSectorSize	proc :ptr

    .ends

endif

if (_WIN32_IE GE _WIN32_IE_IE70)

ifndef __IFileOperationProgressSink_INTERFACE_DEFINED__
__IFileOperationProgressSink_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFileOperationProgressSink, "04b0f1a7-9490-44bc-96e1-4296a31252e2")

.comdef IFileOperationProgressSink : public IUnknown

    StartOperations	proc
    FinishOperations	proc :HRESULT
    PreRenameItem	proc :DWORD, :ptr, :LPCWSTR
    PostRenameItem	proc :DWORD, :ptr, :LPCWSTR, :HRESULT, :ptr
    PreMoveItem		proc :DWORD, :ptr, :ptr, :LPCWSTR
    PostMoveItem	proc :DWORD, :ptr, :ptr, :LPCWSTR, :HRESULT, :ptr
    PreCopyItem		proc :DWORD, :ptr, :ptr, :LPCWSTR
    PostCopyItem	proc :DWORD, :ptr, :ptr, :LPCWSTR, :HRESULT, :ptr
    PreDeleteItem	proc :DWORD, :ptr
    PostDeleteItem	proc :DWORD, :ptr, :HRESULT, :ptr
    PreNewItem		proc :DWORD, :ptr, :LPCWSTR
    PostNewItem		proc :DWORD, :ptr, :LPCWSTR, :LPCWSTR, :DWORD, :HRESULT, :ptr
    UpdateProgress	proc :UINT, :UINT
    ResetTimer		proc
    PauseTimer		proc
    ResumeTimer		proc

    .ends

endif
endif

ifndef __IShellItemArray_INTERFACE_DEFINED__
__IShellItemArray_INTERFACE_DEFINED__ equ 1

SIATTRIBFLAGS		typedef DWORD
SIATTRIBFLAGS_AND	equ 0x1
SIATTRIBFLAGS_OR	equ 0x2
SIATTRIBFLAGS_APPCOMPAT equ 0x3
SIATTRIBFLAGS_MASK	equ 0x3
SIATTRIBFLAGS_ALLITEMS	equ 0x4000


DEFINE_IIDX(IShellItemArray, "b63ea76d-1f85-456f-a19c-48159efa858b")

.comdef IShellItemArray : public IUnknown

    BindToHandler	proc :ptr, :REFGUID, :REFIID, :ptr
    GetPropertyStore	proc :GETPROPERTYSTOREFLAGS, :REFIID, :ptr
    GetPropertyDescriptionList proc :REFPROPERTYKEY, :REFIID, :ptr
    GetAttributes	proc :SIATTRIBFLAGS, :SFGAOF, :ptr
    GetCount		proc :ptr
    GetItemAt		proc :DWORD, :ptr
    EnumItems		proc :ptr

    .ends

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


ifndef __IInitializeWithItem_INTERFACE_DEFINED__
__IInitializeWithItem_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInitializeWithItem, "7f73be3f-fb79-493c-a6c7-7ee14e245841")

.comdef IInitializeWithItem : public IUnknown

    Initialize		proc :ptr, :DWORD

    .ends

endif

ifndef __IObjectWithSelection_INTERFACE_DEFINED__
__IObjectWithSelection_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IObjectWithSelection, "1c9cd5bb-98e9-4491-a60f-31aacc72b83c")

.comdef IObjectWithSelection : public IUnknown

    SetSelection	proc :ptr
    GetSelection	proc :REFIID, :ptr

    .ends

endif

ifndef __IObjectWithBackReferences_INTERFACE_DEFINED__
__IObjectWithBackReferences_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IObjectWithBackReferences, "321a6a6a-d61f-4bf3-97ae-14be2986bb36")

.comdef IObjectWithBackReferences : public IUnknown

    RemoveBackReferences proc

    .ends

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

ifndef __IPropertyUI_INTERFACE_DEFINED__
__IPropertyUI_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPropertyUI, "757a7d9f-919a-4118-99d7-dbb208c8cc66")

.comdef IPropertyUI : public IUnknown

    ParsePropertyName	proc :LPCWSTR, :ptr, :ptr, :ptr
    GetCannonicalName	proc :REFFMTID, :PROPID, :LPWSTR, :DWORD
    GetDisplayName	proc :REFFMTID, :PROPID, :PROPERTYUI_NAME_FLAGS, :LPWSTR, :DWORD
    GetPropertyDescription proc :REFFMTID, :PROPID, :LPWSTR, :DWORD
    GetDefaultWidth	proc :REFFMTID, :PROPID, :ptr
    GetFlags		proc :REFFMTID, :PROPID, :ptr
    FormatForDisplay	proc :REFFMTID, :PROPID, :ptr, :PROPERTYUI_FORMAT_FLAGS, :LPWSTR, :DWORD
    GetHelpInfo		proc :REFFMTID, :PROPID, :LPWSTR, :DWORD, :ptr

    .ends

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

ifndef __ICategoryProvider_INTERFACE_DEFINED__
__ICategoryProvider_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICategoryProvider, "9af64809-5864-4c26-a720-c1f78c086ee3")

.comdef ICategoryProvider : public IUnknown

    CanCategorizeOnSCID proc :ptr
    GetDefaultCategory	proc :ptr, :ptr
    GetCategoryForSCID	proc :ptr, :ptr
    EnumCategories	proc :ptr
    GetCategoryName	proc :ptr, :LPWSTR, :UINT
    CreateCategory	proc :ptr, :REFIID, :ptr

    .ends

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

CATSORT_FLAGS		typedef SDWORD
CATSORT_DEFAULT		equ 0
CATSORT_NAME		equ 0x1

CATEGORY_INFO		STRUC
cif			CATEGORYINFO_FLAGS ?
wszName			WCHAR  260  dup(?)
CATEGORY_INFO		ENDS

ifndef __ICategorizer_INTERFACE_DEFINED__
__ICategorizer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICategorizer, "a3b14589-9174-49a8-89a3-06a1ae2b9ba7")

.comdef ICategorizer : public IUnknown

    GetDescription	proc :LPWSTR, :UINT
    GetCategory		proc :UINT, :PCUITEMID_CHILD_ARRAY, :ptr
    GetCategoryInfo	proc :DWORD, :ptr
    CompareCategory	proc :CATSORT_FLAGS, :DWORD, :DWORD

    .ends

endif

endif
if (NTDDI_VERSION GE NTDDI_WIN2K)
.pragma pack(push, 8)
SHDRAGIMAGE		STRUC
sizeDragImage		SIZEL <>
ptOffset		POINT <>
hbmpDragImage		HBITMAP ?
crColorKey		COLORREF ?
SHDRAGIMAGE		ENDS

LPSHDRAGIMAGE		typedef ptr SHDRAGIMAGE

.pragma pack(pop)
DI_GETDRAGIMAGE		equ TEXT("ShellGetDragImage")

ifndef __IDropTargetHelper_INTERFACE_DEFINED__
__IDropTargetHelper_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDropTargetHelper, "4657278B-411B-11D2-839A-00C04FD918D0")

.comdef IDropTargetHelper : public IUnknown

    DragEnter		proc :HWND, :ptr, :ptr, :DWORD
    DragLeave		proc
    DragOver		proc :ptr, :DWORD
    Drop		proc :ptr, :ptr, :DWORD
    Show		proc :BOOL

    .ends

endif

ifndef __IDragSourceHelper_INTERFACE_DEFINED__
__IDragSourceHelper_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDragSourceHelper, "DE5BF786-477A-11D2-839D-00C04FD918D0")

.comdef IDragSourceHelper : public IUnknown

    InitializeFromBitmap proc :LPSHDRAGIMAGE, :ptr
    InitializeFromWindow proc :HWND, :ptr, :ptr

    .ends

endif

if (NTDDI_VERSION GE NTDDI_VISTA)
DSH_FLAGS		typedef SDWORD
DSH_ALLOWDROPDESCRIPTIONTEXT	equ 0x1


ifndef __IDragSourceHelper2_INTERFACE_DEFINED__
__IDragSourceHelper2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDragSourceHelper2, "83E07D0D-0C5F-4163-BF1A-60B274051E40")

.comdef IDragSourceHelper2 : public IDragSourceHelper

    SetFlags		proc :DWORD

    .ends

endif
endif
endif

ifdef _UNICODE
IShellLink		equ <IShellLinkW>
IID_IShellLink		equ <IID_IShellLinkW>
else
IShellLink		equ <IShellLinkA>
IID_IShellLink		equ <IID_IShellLinkA>
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

SLGP_FLAGS		typedef SDWORD
SLGP_SHORTPATH		equ 0x1
SLGP_UNCPRIORITY	equ 0x2
SLGP_RAWPATH		equ 0x4
SLGP_RELATIVEPRIORITY	equ 0x8


ifndef __IShellLinkA_INTERFACE_DEFINED__
__IShellLinkA_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellLinkA, "000214EE-0000-0000-C000-000000000046")

.comdef IShellLinkA : public IUnknown

    GetPath		proc :LPSTR, :SINT, :ptr, :DWORD
    GetIDList		proc :ptr
    SetIDList		proc :PCIDLIST_ABSOLUTE
    GetDescription	proc :LPSTR, :SINT
    SetDescription	proc :LPCSTR
    GetWorkingDirectory proc :LPSTR, :SINT
    SetWorkingDirectory proc :LPCSTR
    GetArguments	proc :LPSTR, :SINT
    SetArguments	proc :LPCSTR
    GetHotkey		proc :ptr
    SetHotkey		proc :WORD
    GetShowCmd		proc :ptr
    SetShowCmd		proc :SINT
    GetIconLocation	proc :LPSTR, :SINT, :ptr
    SetIconLocation	proc :LPCSTR, :SINT
    SetRelativePath	proc :LPCSTR, :DWORD
    Resolve		proc :HWND, :DWORD
    SetPath		proc :LPCSTR

    .ends

endif

ifndef __IShellLinkW_INTERFACE_DEFINED__
__IShellLinkW_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellLinkW, "000214F9-0000-0000-C000-000000000046")

.comdef IShellLinkW : public IUnknown

    GetPath		proc :LPWSTR, :SINT, :ptr, :DWORD
    GetIDList		proc :ptr
    SetIDList		proc :PCIDLIST_ABSOLUTE
    GetDescription	proc :LPWSTR, :SINT
    SetDescription	proc :LPCWSTR
    GetWorkingDirectory proc :LPWSTR, :SINT
    SetWorkingDirectory proc :LPCWSTR
    GetArguments	proc :LPWSTR, :SINT
    SetArguments	proc :LPCWSTR
    GetHotkey		proc :ptr
    SetHotkey		proc :WORD
    GetShowCmd		proc :ptr
    SetShowCmd		proc :SINT
    GetIconLocation	proc :LPWSTR, :SINT, :ptr
    SetIconLocation	proc :LPCWSTR, :SINT
    SetRelativePath	proc :LPCWSTR, :DWORD
    Resolve		proc :HWND, :DWORD
    SetPath		proc :LPCWSTR

    .ends

endif

ifndef __IShellLinkDataList_INTERFACE_DEFINED__
__IShellLinkDataList_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellLinkDataList, "45e2b4ae-b1c3-11d0-b92f-00a0c90312e1")

.comdef IShellLinkDataList : public IUnknown

    AddDataBlock	proc :ptr
    CopyDataBlock	proc :DWORD, :ptr
    RemoveDataBlock	proc :DWORD
    GetFlags		proc :ptr
    SetFlags		proc :DWORD

    .ends

endif

if (NTDDI_VERSION GE NTDDI_WIN2K)

ifndef __IResolveShellLink_INTERFACE_DEFINED__
__IResolveShellLink_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IResolveShellLink, "5cd52983-9449-11d2-963a-00c04f79adf0")

.comdef IResolveShellLink : public IUnknown

    ResolveShellLink	proc :ptr, :HWND, :DWORD

    .ends

endif
endif

ifndef __IActionProgressDialog_INTERFACE_DEFINED__
__IActionProgressDialog_INTERFACE_DEFINED__ equ 1

SPINITF_NORMAL		equ 0
SPINITF_MODAL		equ 0x1
SPINITF_NOMINIMIZE	equ 0x8
SPINITF			typedef DWORD

DEFINE_IIDX(IActionProgressDialog, "49ff1172-eadc-446d-9285-156453a6431c")

.comdef IActionProgressDialog : public IUnknown

    Initialize		proc :SPINITF, :LPCWSTR, :LPCWSTR
    Stop		proc

    .ends

endif

ifndef __IHWEventHandler_INTERFACE_DEFINED__
__IHWEventHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IHWEventHandler, "C1FB73D0-EC3A-4ba2-B512-8CDB9187B6D1")

.comdef IHWEventHandler : public IUnknown

    Initialize		proc :LPCWSTR
    HandleEvent		proc :LPCWSTR, :LPCWSTR, :LPCWSTR
    HandleEventWithContent proc :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPCWSTR, :ptr

    .ends

endif

ifndef __IHWEventHandler2_INTERFACE_DEFINED__
__IHWEventHandler2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IHWEventHandler2, "CFCC809F-295D-42e8-9FFC-424B33C487E6")

.comdef IHWEventHandler2 : public IHWEventHandler

    HandleEventWithHWND proc :LPCWSTR, :LPCWSTR, :LPCWSTR, :HWND

    .ends

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

ifndef __IQueryCancelAutoPlay_INTERFACE_DEFINED__
__IQueryCancelAutoPlay_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IQueryCancelAutoPlay, "DDEFE873-6997-4e68-BE26-39B633ADBE12")

.comdef IQueryCancelAutoPlay : public IUnknown

    AllowAutoPlay	proc :LPCWSTR, :DWORD, :LPCWSTR, :DWORD

    .ends

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

ifndef __IDynamicHWHandler_INTERFACE_DEFINED__
__IDynamicHWHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDynamicHWHandler, "DC2601D7-059E-42fc-A09D-2AFD21B6D5F7")

.comdef IDynamicHWHandler : public IUnknown

    GetDynamicInfo	proc :LPCWSTR, :DWORD, :ptr

    .ends

endif
endif

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

DEFINE_IIDX(IActionProgress, "49ff1173-eadc-446d-9285-156453a6431c")

.comdef IActionProgress : public IUnknown

    Begin		proc :SPACTION, :SPBEGINF
    UpdateProgress	proc :ULONGLONG, :ULONGLONG
    UpdateText		proc :SPTEXT, :LPCWSTR, :BOOL
    QueryCancel		proc :ptr
    ResetCancel		proc
    _End		proc

    .ends

endif

ifndef __IShellExtInit_INTERFACE_DEFINED__
__IShellExtInit_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellExtInit, "000214E8-0000-0000-C000-000000000046")

.comdef IShellExtInit : public IUnknown

    Initialize		proc :PCIDLIST_ABSOLUTE, :ptr, :HKEY

    .ends

LPSHELLEXTINIT		typedef ptr IShellExtInit

endif

ifndef __IShellPropSheetExt_INTERFACE_DEFINED__
__IShellPropSheetExt_INTERFACE_DEFINED__ equ 1

EXPPS_FILETYPES		equ 0x1
EXPPS			typedef UINT

DEFINE_IIDX(IShellPropSheetExt, "000214E9-0000-0000-C000-000000000046")

.comdef IShellPropSheetExt : public IUnknown

    AddPages		proc :LPFNSVADDPROPSHEETPAGE, :LPARAM
    ReplacePage		proc :EXPPS, :LPFNSVADDPROPSHEETPAGE, :LPARAM

    .ends

endif

LPSHELLPROPSHEETEXT	typedef ptr IShellPropSheetExt

ifndef __IRemoteComputer_INTERFACE_DEFINED__
__IRemoteComputer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRemoteComputer, "000214FE-0000-0000-C000-000000000046")

.comdef IRemoteComputer : public IUnknown

    Initialize		proc :LPCWSTR, :BOOL

    .ends

endif

ifndef __IQueryContinue_INTERFACE_DEFINED__
__IQueryContinue_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IQueryContinue, "7307055c-b24a-486b-9f25-163e597a28a9")

.comdef IQueryContinue : public IUnknown

    QueryContinue	proc

    .ends

endif

ifndef __IObjectWithCancelEvent_INTERFACE_DEFINED__
__IObjectWithCancelEvent_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IObjectWithCancelEvent, "F279B885-0AE9-4b85-AC06-DDECF9408941")

.comdef IObjectWithCancelEvent : public IUnknown

    GetCancelEvent	proc :ptr

    .ends

endif

ifndef __IUserNotification_INTERFACE_DEFINED__
__IUserNotification_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IUserNotification, "ba9711ba-5893-4787-a7e1-41277151550b")

.comdef IUserNotification : public IUnknown

    SetBalloonInfo	proc :LPCWSTR, :LPCWSTR, :DWORD
    SetBalloonRetry	proc :DWORD, :DWORD, :UINT
    SetIconInfo		proc :HICON, :LPCWSTR
    Show		proc :ptr, :DWORD
    PlaySound		proc :LPCWSTR

    .ends

endif

ifndef __IUserNotificationCallback_INTERFACE_DEFINED__
__IUserNotificationCallback_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IUserNotificationCallback, "19108294-0441-4AFF-8013-FA0A730B0BEA")

.comdef IUserNotificationCallback : public IUnknown

    OnBalloonUserClick	proc :ptr
    OnLeftClick		proc :ptr
    OnContextMenu	proc :ptr

    .ends

endif

ifndef __IUserNotification2_INTERFACE_DEFINED__
__IUserNotification2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IUserNotification2, "215913CC-57EB-4FAB-AB5A-E5FA7BEA2A6C")

.comdef IUserNotification2 : public IUnknown

    SetBalloonInfo	proc :LPCWSTR, :LPCWSTR, :DWORD
    SetBalloonRetry	proc :DWORD, :DWORD, :UINT
    SetIconInfo		proc :HICON, :LPCWSTR
    Show		proc :ptr, :DWORD, :ptr
    PlaySound		proc :LPCWSTR

    .ends

endif

ifndef __IItemNameLimits_INTERFACE_DEFINED__
__IItemNameLimits_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IItemNameLimits, "1df0d7f1-b267-4d28-8b10-12e23202a5c4")

.comdef IItemNameLimits : public IUnknown

    GetValidCharacters	proc :ptr, :ptr
    GetMaxLength	proc :LPCWSTR, :ptr

    .ends

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

ifndef __ISearchFolderItemFactory_INTERFACE_DEFINED__
__ISearchFolderItemFactory_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISearchFolderItemFactory, "a0ffbc28-5482-4366-be27-3e81e78e06c2")

.comdef ISearchFolderItemFactory : public IUnknown

    SetDisplayName	proc :LPCWSTR
    SetFolderTypeID	proc :FOLDERTYPEID
    SetFolderLogicalViewMode proc :FOLDERLOGICALVIEWMODE
    SetIconSize		proc :SINT
    SetVisibleColumns	proc :UINT, :ptr
    SetSortColumns	proc :UINT, :ptr
    SetGroupColumn	proc :REFPROPERTYKEY
    SetStacks		proc :UINT, :ptr
    SetScope		proc :ptr
    SetCondition	proc :ptr
    GetShellItem	proc :REFIID, :ptr
    GetIDList		proc :ptr

    .ends

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

ifndef __IExtractImage_INTERFACE_DEFINED__
__IExtractImage_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IExtractImage, "BB2E617C-0920-11d1-9A0B-00C04FC2D6C1")

.comdef IExtractImage : public IUnknown

    GetLocation		proc :LPWSTR, :DWORD, :ptr, :ptr, :DWORD, :ptr
    Extract		proc :ptr

    .ends

LPEXTRACTIMAGE		typedef ptr IExtractImage

endif

endif
if (_WIN32_IE GE 0x0500)

ifndef __IExtractImage2_INTERFACE_DEFINED__
__IExtractImage2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IExtractImage2, "953BB1EE-93B4-11d1-98A3-00C04FB687DA")

.comdef IExtractImage2 : public IExtractImage

    GetDateStamp	proc :ptr

    .ends

LPEXTRACTIMAGE2		typedef ptr IExtractImage2

endif

ifndef __IThumbnailHandlerFactory_INTERFACE_DEFINED__
__IThumbnailHandlerFactory_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IThumbnailHandlerFactory, "e35b4b2e-00da-4bc1-9f13-38bc11f5d417")

.comdef IThumbnailHandlerFactory : public IUnknown

    GetThumbnailHandler proc :PCUITEMID_CHILD, :ptr, :REFIID, :ptr

    .ends

endif

ifndef __IParentAndItem_INTERFACE_DEFINED__
__IParentAndItem_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IParentAndItem, "b3a4b685-b685-4805-99d9-5dead2873236")

.comdef IParentAndItem : public IUnknown

    SetParentAndItem	proc :PCIDLIST_ABSOLUTE, :ptr, :PCUITEMID_CHILD
    GetParentAndItem	proc :ptr, :ptr, :ptr

    .ends

endif
endif

ifndef __IDockingWindow_INTERFACE_DEFINED__
__IDockingWindow_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDockingWindow, "012dd920-7b26-11d0-8ca9-00a0c92dbfe8")

.comdef IDockingWindow : public IOleWindow

    ShowDW		proc :BOOL
    CloseDW		proc :DWORD
    ResizeBorderDW	proc :LPCRECT, :ptr, :BOOL

    .ends

endif

DBIM_MINSIZE		equ 0x0001
DBIM_MAXSIZE		equ 0x0002
DBIM_INTEGRAL		equ 0x0004
DBIM_ACTUAL		equ 0x0008
DBIM_TITLE		equ 0x0010
DBIM_MODEFLAGS		equ 0x0020
DBIM_BKCOLOR		equ 0x0040

.pragma pack(push, 8)

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

.pragma pack(pop)

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


ifndef __IDeskBand_INTERFACE_DEFINED__
__IDeskBand_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDeskBand, "EB0FE172-1A3A-11D0-89B3-00A0C90A90AC")

.comdef IDeskBand : public IDockingWindow

    GetBandInfo		proc :DWORD, :DWORD, :ptr

    .ends

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

ifndef __IDeskBandInfo_INTERFACE_DEFINED__
__IDeskBandInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDeskBandInfo, "77E425FC-CBF9-4307-BA6A-BB5727745661")

.comdef IDeskBandInfo : public IUnknown

    GetDefaultBandWidth proc :DWORD, :DWORD, :ptr

    .ends

endif

ifndef __IDeskBand2_INTERFACE_DEFINED__
__IDeskBand2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDeskBand2, "79D16DE4-ABEE-4021-8D9D-9169B261D657")

.comdef IDeskBand2 : public IDeskBand

    CanRenderComposited proc :ptr
    SetCompositionState proc :BOOL
    GetCompositionState proc :ptr

    .ends

endif
endif

ifndef __ITaskbarList_INTERFACE_DEFINED__
__ITaskbarList_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ITaskbarList, "56FDF342-FD6D-11d0-958A-006097C9A090")

.comdef ITaskbarList : public IUnknown

    HrInit		proc
    AddTab		proc :HWND
    DeleteTab		proc :HWND
    ActivateTab		proc :HWND
    SetActiveAlt	proc :HWND

    .ends

endif

ifndef __ITaskbarList2_INTERFACE_DEFINED__
__ITaskbarList2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ITaskbarList2, "602D4995-B13A-429b-A66E-1935E44F4317")

.comdef ITaskbarList2 : public ITaskbarList

    MarkFullscreenWindow proc :HWND, :BOOL

    .ends

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

THUMBBUTTONMASK		typedef SDWORD
THB_BITMAP		equ 0x1
THB_ICON		equ 0x2
THB_TOOLTIP		equ 0x4
THB_FLAGS		equ 0x8

.pragma pack(push, 8)

THUMBBUTTON		STRUC
dwMask			THUMBBUTTONMASK ?
iId			UINT ?
iBitmap			UINT ?
hIcon			HICON ?
szTip			WCHAR  260  dup(?)
dwFlags			THUMBBUTTONFLAGS ?
THUMBBUTTON		ENDS
LPTHUMBBUTTON		typedef ptr THUMBBUTTON

.pragma pack(pop)
THBN_CLICKED		equ 0x1800

ifndef __ITaskbarList3_INTERFACE_DEFINED__
__ITaskbarList3_INTERFACE_DEFINED__ equ 1

TBPFLAG			typedef SDWORD
TBPF_NOPROGRESS		equ 0
TBPF_INDETERMINATE	equ 0x1
TBPF_NORMAL		equ 0x2
TBPF_ERROR		equ 0x4
TBPF_PAUSED		equ 0x8


DEFINE_IIDX(ITaskbarList3, "ea1afb91-9e28-4b86-90e9-9e9f8a5eefaf")

.comdef ITaskbarList3 : public ITaskbarList2

    SetProgressValue	proc :HWND, :ULONGLONG, :ULONGLONG
    SetProgressState	proc :HWND, :TBPFLAG
    RegisterTab		proc :HWND, :HWND
    UnregisterTab	proc :HWND
    SetTabOrder		proc :HWND, :HWND
    SetTabActive	proc :HWND, :HWND, :DWORD
    ThumbBarAddButtons	proc :HWND, :UINT, :LPTHUMBBUTTON
    ThumbBarUpdateButtons proc :HWND, :UINT, :LPTHUMBBUTTON
    ThumbBarSetImageList proc :HWND, :HIMAGELIST
    SetOverlayIcon	proc :HWND, :HICON, :LPCWSTR
    SetThumbnailTooltip proc :HWND, :LPCWSTR
    SetThumbnailClip	proc :HWND, :ptr

    .ends

endif

ifndef __ITaskbarList4_INTERFACE_DEFINED__
__ITaskbarList4_INTERFACE_DEFINED__ equ 1

STPFLAG			typedef SDWORD
STPF_NONE		equ 0
STPF_USEAPPTHUMBNAILALWAYS equ 0x1
STPF_USEAPPTHUMBNAILWHENACTIVE	equ 0x2
STPF_USEAPPPEEKALWAYS	equ 0x4
STPF_USEAPPPEEKWHENACTIVE equ 0x8

DEFINE_IIDX(ITaskbarList4, "c43dc798-95d1-4bea-9030-bb99e2983a1a")

.comdef ITaskbarList4 : public ITaskbarList3

    SetTabProperties	proc :HWND, :STPFLAG

    .ends

endif

ifndef __IStartMenuPinnedList_INTERFACE_DEFINED__
__IStartMenuPinnedList_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IStartMenuPinnedList, "4CD19ADA-25A5-4A32-B3B7-347BEE5BE36B")

.comdef IStartMenuPinnedList : public IUnknown

    RemoveFromList	proc :ptr

    .ends

endif

ifndef __ICDBurn_INTERFACE_DEFINED__
__ICDBurn_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICDBurn, "3d73a659-e5d0-4d42-afc0-5121ba425c8d")

.comdef ICDBurn : public IUnknown

    GetRecorderDriveLetter proc :LPWSTR, :UINT
    Burn		proc :HWND
    HasRecordableDrive	proc :ptr

    .ends

endif

IDD_WIZEXTN_FIRST	equ 0x5000
IDD_WIZEXTN_LAST	equ 0x5100

ifndef __IWizardSite_INTERFACE_DEFINED__
__IWizardSite_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IWizardSite, "88960f5b-422f-4e7b-8013-73415381c3c3")

.comdef IWizardSite : public IUnknown

    GetPreviousPage	proc :ptr
    GetNextPage		proc :ptr
    GetCancelledPage	proc :ptr

    .ends

endif

SID_WizardSite		equ <IID_IWizardSite>

ifndef __IWizardExtension_INTERFACE_DEFINED__
__IWizardExtension_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IWizardExtension, "c02ea696-86cc-491e-9b23-74394a0444a8")

.comdef IWizardExtension : public IUnknown

    AddPages		proc :ptr, :UINT, :ptr
    GetFirstPage	proc :ptr
    GetLastPage		proc :ptr

    .ends
endif


ifndef __IWebWizardExtension_INTERFACE_DEFINED__
__IWebWizardExtension_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IWebWizardExtension, "0e6b3f66-98d1-48c0-a222-fbde74e2fbc5")

.comdef IWebWizardExtension : public IWizardExtension

    SetInitialURL	proc :LPCWSTR
    SetErrorURL		proc :LPCWSTR

    .ends
endif

SID_WebWizardHost	equ <IID_IWebWizardExtension>
SHPWHF_NORECOMPRESS	equ 0x00000001
SHPWHF_NONETPLACECREATE equ 0x00000002
SHPWHF_NOFILESELECTOR	equ 0x00000004
SHPWHF_USEMRU		equ 0x00000008
if (NTDDI_VERSION GE NTDDI_VISTA)
SHPWHF_ANYLOCATION	equ 0x00000100
endif
SHPWHF_VALIDATEVIAWEBFOLDERS equ 0x00010000

ifndef __IPublishingWizard_INTERFACE_DEFINED__
__IPublishingWizard_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPublishingWizard, "aa9198bb-ccec-472d-beed-19a4f6733f7a")

.comdef IPublishingWizard : public IWizardExtension

    Initialize		proc :ptr, :DWORD, :LPCWSTR
    GetTransferManifest proc :ptr, :ptr

    .ends
endif


if (NTDDI_VERSION GE NTDDI_WINXP) OR (_WIN32_IE GE _WIN32_IE_IE70)

ifndef __IFolderViewHost_INTERFACE_DEFINED__
__IFolderViewHost_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFolderViewHost, "1ea58f02-d55a-411d-b09e-9e65ac21605b")

.comdef IFolderViewHost : public IUnknown

    Initialize		proc :HWND, :ptr, :ptr

    .ends

endif

if (_WIN32_IE GE _WIN32_IE_IE70)

ifndef __IExplorerBrowserEvents_INTERFACE_DEFINED__
__IExplorerBrowserEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IExplorerBrowserEvents, "361bbdc7-e6ee-4e13-be58-58e2240c810f")

.comdef IExplorerBrowserEvents : public IUnknown

    OnNavigationPending proc :PCIDLIST_ABSOLUTE
    OnViewCreated	proc :ptr
    OnNavigationComplete proc :PCIDLIST_ABSOLUTE
    OnNavigationFailed	proc :PCIDLIST_ABSOLUTE

    .ends

endif

EXPLORER_BROWSER_OPTIONS typedef SDWORD
EBO_NONE		equ 0
EBO_NAVIGATEONCE	equ 0x1
EBO_SHOWFRAMES		equ 0x2
EBO_ALWAYSNAVIGATE	equ 0x4
EBO_NOTRAVELLOG		equ 0x8
EBO_NOWRAPPERWINDOW	equ 0x10
EBO_HTMLSHAREPOINTVIEW	equ 0x20

EXPLORER_BROWSER_FILL_FLAGS typedef SDWORD
EBF_NONE		equ 0
EBF_SELECTFROMDATAOBJECT equ 0x100
EBF_NODROPTARGET	equ 0x200


ifndef __IExplorerBrowser_INTERFACE_DEFINED__
__IExplorerBrowser_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IExplorerBrowser, "dfd3b6b5-c10c-4be9-85f6-a66969f402f6")

.comdef IExplorerBrowser : public IUnknown

    Initialize		proc :HWND, :ptr, :ptr
    Destroy		proc
    SetRect		proc :ptr, :RECT
    SetPropertyBag	proc :LPCWSTR
    SetEmptyText	proc :LPCWSTR
    SetFolderSettings	proc :ptr
    Advise		proc :ptr, :ptr
    Unadvise		proc :DWORD
    SetOptions		proc :EXPLORER_BROWSER_OPTIONS
    GetOptions		proc :ptr
    BrowseToIDList	proc :PCUIDLIST_RELATIVE, :UINT
    BrowseToObject	proc :ptr, :UINT
    FillFromObject	proc :ptr, :EXPLORER_BROWSER_FILL_FLAGS
    RemoveAll		proc
    GetCurrentView	proc :REFIID, :ptr

    .ends

endif

ifndef __IAccessibleObject_INTERFACE_DEFINED__
__IAccessibleObject_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAccessibleObject, "95A391C5-9ED4-4c28-8401-AB9E06719E11")

.comdef IAccessibleObject : public IUnknown

    SetAccessibleName	proc :LPCWSTR

    .ends

endif
endif

ifndef __IResultsFolder_INTERFACE_DEFINED__
__IResultsFolder_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IResultsFolder, "96E5AE6D-6AE1-4b1c-900C-C6480EAA8828")

.comdef IResultsFolder : public IUnknown

    AddItem		proc :ptr
    AddIDList		proc :PCIDLIST_ABSOLUTE, :ptr
    RemoveItem		proc :ptr
    RemoveIDList	proc :PCIDLIST_ABSOLUTE
    RemoveAll		proc

    .ends

endif

if (_WIN32_IE GE _WIN32_IE_IE70)

ifndef __IEnumObjects_INTERFACE_DEFINED__
__IEnumObjects_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEnumObjects, "2c1c7e2e-2d0e-4059-831e-1e6f82335c2e")

.comdef IEnumObjects : public IUnknown

    Next		proc :ULONG, :REFIID, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr

    .ends

endif

OPPROGDLG_DEFAULT	equ 0
OPPROGDLG_ENABLEPAUSE	equ 0x80
OPPROGDLG_ALLOWUNDO	equ 0x100
OPPROGDLG_DONTDISPLAYSOURCEPATH equ 0x200
OPPROGDLG_DONTDISPLAYDESTPATH equ 0x400
OPPROGDLG_NOMULTIDAYESTIMATES equ 0x800
OPPROGDLG_DONTDISPLAYLOCATIONS equ 0x1000
OPPROGDLGF		typedef DWORD

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

DEFINE_IIDX(IOperationsProgressDialog, "0C9FB851-E5C9-43EB-A370-F0677B13874C")

.comdef IOperationsProgressDialog : public IUnknown

    StartProgressDialog proc :HWND, :OPPROGDLGF
    StopProgressDialog	proc
    SetOperation	proc :SPACTION
    SetMode		proc :PDMODE
    UpdateProgress	proc :ULONGLONG, :ULONGLONG, :ULONGLONG, :ULONGLONG, :ULONGLONG, :ULONGLONG
    UpdateLocations	proc :ptr, :ptr, :ptr
    ResetTimer		proc
    PauseTimer		proc
    ResumeTimer		proc
    GetMilliseconds	proc :ptr, :ptr
    GetOperationStatus	proc :ptr

    .ends

endif

ifndef __IIOCancelInformation_INTERFACE_DEFINED__
__IIOCancelInformation_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IIOCancelInformation, "f5b0bf81-8cb5-4b1b-9449-1a159e0c733c")

.comdef IIOCancelInformation : public IUnknown

    SetCancelInformation proc :DWORD, :UINT
    GetCancelInformation proc :ptr, :ptr

    .ends

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

ifndef __IFileOperation_INTERFACE_DEFINED__
__IFileOperation_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFileOperation, "947aab5f-0a5c-4c13-b4d6-4bf7836fc9f8")

.comdef IFileOperation : public IUnknown

    Advise		proc :ptr, :ptr
    Unadvise		proc :DWORD
    SetOperationFlags	proc :DWORD
    SetProgressMessage	proc :LPCWSTR
    SetProgressDialog	proc :ptr
    SetProperties	proc :ptr
    SetOwnerWindow	proc :HWND
    ApplyPropertiesToItem proc :ptr
    ApplyPropertiesToItems proc :ptr
    RenameItem		proc :ptr, :LPCWSTR, :ptr
    RenameItems		proc :ptr, :LPCWSTR
    MoveItem		proc :ptr, :ptr, :LPCWSTR, :ptr
    MoveItems		proc :ptr, :ptr
    CopyItem		proc :ptr, :ptr, :LPCWSTR, :ptr
    CopyItems		proc :ptr, :ptr
    DeleteItem		proc :ptr, :ptr
    DeleteItems		proc :ptr
    NewItem		proc :ptr, :DWORD, :LPCWSTR, :LPCWSTR, :ptr
    PerformOperations	proc
    GetAnyOperationsAborted proc :ptr

    .ends

endif

ifndef __IObjectProvider_INTERFACE_DEFINED__
__IObjectProvider_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IObjectProvider, "a6087428-3be3-4d73-b308-7c04a540bf1a")

.comdef IObjectProvider : public IUnknown

    QueryObject		proc :REFGUID, :REFIID, :ptr

    .ends

endif
endif

ifndef __INamespaceWalkCB_INTERFACE_DEFINED__
__INamespaceWalkCB_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(INamespaceWalkCB, "d92995f8-cf5e-4a76-bf59-ead39ea2b97e")

.comdef INamespaceWalkCB : public IUnknown

    FoundItem		proc :ptr, :PCUITEMID_CHILD
    EnterFolder		proc :ptr, :PCUITEMID_CHILD
    LeaveFolder		proc :ptr, :PCUITEMID_CHILD
    InitializeProgressDialog proc :ptr, :ptr

    .ends

endif

if (_WIN32_IE GE _WIN32_IE_IE70)

ifndef __INamespaceWalkCB2_INTERFACE_DEFINED__
__INamespaceWalkCB2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(INamespaceWalkCB2, "7ac7492b-c38e-438a-87db-68737844ff70")

.comdef INamespaceWalkCB2 : public INamespaceWalkCB

    WalkComplete	proc :HRESULT

    .ends

endif
endif

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


DEFINE_IIDX(INamespaceWalk, "57ced8a7-3f4a-432c-9350-30f24483f74f")

.comdef INamespaceWalk : public IUnknown

    Walk		proc :ptr, :DWORD, :SINT, :ptr
    GetIDArrayResult	proc :ptr, :ptr

    .ends

endif
endif

FreeIDListArrayFull	equ FreeIDistArray
FreeIDListArrayChild	equ FreeIDistArray
ACDD_VISIBLE		equ 0x0001

ifndef __IAutoCompleteDropDown_INTERFACE_DEFINED__
__IAutoCompleteDropDown_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAutoCompleteDropDown, "3CD141F4-3C6A-11d2-BCAA-00C04FD929DB")

.comdef IAutoCompleteDropDown : public IUnknown

    GetDropDownStatus	proc :ptr, :ptr
    ResetEnumerator	proc

    .ends

endif

if (_WIN32_IE GE _WIN32_IE_IE40)
.pragma pack(push, 8)
BANDSITEINFO		STRUC
dwMask			dd ?
dwState			dd ?
dwStyle			dd ?
BANDSITEINFO		ENDS

.pragma pack(pop)

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

ifndef __IBandSite_INTERFACE_DEFINED__
__IBandSite_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IBandSite, "4CF504B0-DE96-11D0-8B3F-00A0C911E8E5")

.comdef IBandSite : public IUnknown

    AddBand		proc :ptr
    EnumBands		proc :UINT, :ptr
    QueryBand		proc :DWORD, :ptr, :ptr, :LPWSTR, :SINT
    SetBandState	proc :DWORD, :DWORD, :DWORD
    RemoveBand		proc :DWORD
    GetBandObject	proc :DWORD, :REFIID, :ptr
    SetBandSiteInfo	proc :ptr
    GetBandSiteInfo	proc :ptr

    .ends

endif
endif

if (NTDDI_VERSION GE NTDDI_WINXP)

ifndef __IModalWindow_INTERFACE_DEFINED__
__IModalWindow_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IModalWindow, "b4db1657-70d7-485e-8e3e-6fcb5a5c1802")

.comdef IModalWindow : public IUnknown

    Show		proc :HWND

    .ends

endif

PROPSTR_EXTENSIONCOMPLETIONSTATE equ <L"ExtensionCompletionState">

tagCDBURNINGEXTENSIONRET typedef SDWORD
CDBE_RET_DEFAULT	equ 0
CDBE_RET_DONTRUNOTHEREXTS equ 0x1
CDBE_RET_STOPWIZARD	equ 0x2
SID_CDWizardHost	equ IID_ICDBurnExt

CDBE_TYPE_MUSIC		equ 0x1
CDBE_TYPE_DATA		equ 0x2
CDBE_TYPE_ALL		equ 0xffffffff
CDBE_ACTIONS		typedef DWORD

ifndef __ICDBurnExt_INTERFACE_DEFINED__
__ICDBurnExt_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICDBurnExt, "2271dcca-74fc-4414-8fb7-c56b05ace2d7")

.comdef ICDBurnExt : public IUnknown

    GetSupportedActionTypes proc :ptr

    .ends

endif
endif

ifndef __IContextMenuSite_INTERFACE_DEFINED__
__IContextMenuSite_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IContextMenuSite, "0811AEBE-0B87-4C54-9E72-548CF649016B")

.comdef IContextMenuSite : public IUnknown

    DoContextMenuPopup	proc :ptr, :UINT, :POINT

    .ends
endif

ifndef __IEnumReadyCallback_INTERFACE_DEFINED__
__IEnumReadyCallback_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEnumReadyCallback, "61E00D45-8FFF-4e60-924E-6537B61612DD")

.comdef IEnumReadyCallback : public IUnknown

    EnumReady		proc

    .ends

endif

ifndef __IEnumerableView_INTERFACE_DEFINED__
__IEnumerableView_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEnumerableView, "8C8BF236-1AEC-495f-9894-91D57C3C686F")

.comdef IEnumerableView : public IUnknown

    SetEnumReadyCallback proc :ptr
    CreateEnumIDListFromContents proc :PCIDLIST_ABSOLUTE, :DWORD, :ptr

    .ends

endif

SID_EnumerableView	equ <IID_IEnumerableView>
if (NTDDI_VERSION GE NTDDI_WINXP) OR (_WIN32_IE GE _WIN32_IE_IE70)

ifndef __IInsertItem_INTERFACE_DEFINED__
__IInsertItem_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInsertItem, "D2B57227-3D23-4b95-93C0-492BD454C356")

.comdef IInsertItem : public IUnknown

    InsertItem		proc :PCUIDLIST_RELATIVE

    .ends

endif

if (NTDDI_VERSION GE NTDDI_WINXP)

ifndef __IMenuBand_INTERFACE_DEFINED__
__IMenuBand_INTERFACE_DEFINED__ equ 1

MENUBANDHANDLERCID	typedef SDWORD
MBHANDCID_PIDLSELECT	equ 0

DEFINE_IIDX(IMenuBand, "568804CD-CBD7-11d0-9816-00C04FD91972")

.comdef IMenuBand : public IUnknown

    IsMenuMessage	proc :ptr
    TranslateMenuMessage proc :ptr, :ptr

    .ends

endif

ifndef __IFolderBandPriv_INTERFACE_DEFINED__
__IFolderBandPriv_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFolderBandPriv, "47c01f95-e185-412c-b5c5-4f27df965aea")

.comdef IFolderBandPriv : public IUnknown

    SetCascade		proc :BOOL
    SetAccelerators	proc :BOOL
    SetNoIcons		proc :BOOL
    SetNoText		proc :BOOL

    .ends

endif

ifndef __IRegTreeItem_INTERFACE_DEFINED__
__IRegTreeItem_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRegTreeItem, "A9521922-0812-4d44-9EC3-7FD38C726F3D")

.comdef IRegTreeItem : public IUnknown

    GetCheckState	proc :ptr
    SetCheckState	proc :BOOL

    .ends

endif

ifndef __IImageRecompress_INTERFACE_DEFINED__
__IImageRecompress_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IImageRecompress, "505f1513-6b3e-4892-a272-59f8889a4d3e")

.comdef IImageRecompress : public IUnknown

    RecompressImage	proc :ptr, :SINT, :SINT, :SINT, :ptr, :ptr

    .ends

endif
endif
endif

if (_WIN32_IE GE _WIN32_IE_IE60)

ifndef __IDeskBar_INTERFACE_DEFINED__
__IDeskBar_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDeskBar, "EB0FE173-1A3A-11D0-89B3-00A0C90A90AC")

.comdef IDeskBar : public IOleWindow

    SetClient		proc :ptr
    GetClient		proc :ptr
    OnPosRectChangeDB	proc :ptr

    .ends

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
MPPF_BOTTOM		equ 0x80000000
MPPF_POS_MASK		equ 0xe0000000
MPPF_ALIGN_LEFT		equ 0x2000000
MPPF_ALIGN_RIGHT	equ 0x4000000
MP_POPUPFLAGS		typedef SINT

DEFINE_IIDX(IMenuPopup, "D1E7AFEB-6A2E-11d0-8C78-00C04FD918B4")

.comdef IMenuPopup : public IDeskBar

    Popup		proc :ptr, :ptr, :MP_POPUPFLAGS
    OnSelect		proc :DWORD
    SetSubMenu		proc :ptr, :BOOL

    .ends

endif
endif

if (NTDDI_VERSION GE NTDDI_VISTA)
FILE_USAGE_TYPE		typedef SDWORD
FUT_PLAYING		equ 0
FUT_EDITING		equ ( FUT_PLAYING + 1 )
FUT_GENERIC		equ ( FUT_EDITING + 1 )

OF_CAP_CANSWITCHTO	equ 0x0001
OF_CAP_CANCLOSE		equ 0x0002


ifndef __IFileIsInUse_INTERFACE_DEFINED__
__IFileIsInUse_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFileIsInUse, "64a1cbf0-3a1a-4461-9158-376969693950")

.comdef IFileIsInUse : public IUnknown

    GetAppName		proc :ptr
    GetUsage		proc :ptr
    GetCapabilities	proc :ptr
    GetSwitchToHWND	proc :ptr
    CloseFile		proc

    .ends

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

ifndef __IFileDialogEvents_INTERFACE_DEFINED__
__IFileDialogEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFileDialogEvents, "973510db-7d7f-452b-8975-74a85828d354")

.comdef IFileDialogEvents : public IUnknown

    OnFileOk		proc :ptr
    OnFolderChanging	proc :ptr, :ptr
    OnFolderChange	proc :ptr
    OnSelectionChange	proc :ptr
    OnShareViolation	proc :ptr, :ptr, :ptr
    OnTypeChange	proc :ptr
    OnOverwrite		proc :ptr, :ptr, :ptr

    .ends

endif

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


DEFINE_IIDX(IFileDialog, "42f85136-db7e-439c-85f1-e4075d135fc8")

.comdef IFileDialog : public IModalWindow

    SetFileTypes	proc :UINT, :ptr
    SetFileTypeIndex	proc :UINT
    GetFileTypeIndex	proc :ptr
    Advise		proc :ptr, :ptr
    Unadvise		proc :DWORD
    SetOptions		proc :FILEOPENDIALOGOPTIONS
    GetOptions		proc :ptr
    SetDefaultFolder	proc :ptr
    SetFolder		proc :ptr
    GetFolder		proc :ptr
    GetCurrentSelection proc :ptr
    SetFileName		proc :LPCWSTR
    GetFileName		proc :ptr
    SetTitle		proc :LPCWSTR
    SetOkButtonLabel	proc :LPCWSTR
    SetFileNameLabel	proc :LPCWSTR
    GetResult		proc :ptr
    AddPlace		proc :ptr, :FDAP
    SetDefaultExtension proc :LPCWSTR
    Close		proc :HRESULT
    SetClientGuid	proc :REFGUID
    ClearClientData	proc
    SetFilter		proc :ptr

    .ends

endif

ifndef __IFileSaveDialog_INTERFACE_DEFINED__
__IFileSaveDialog_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFileSaveDialog, "84bccd23-5fde-4cdb-aea4-af64b83d78ab")

.comdef IFileSaveDialog : public IFileDialog

    SetSaveAsItem	proc :ptr
    SetProperties	proc :ptr
    SetCollectedProperties proc :ptr, :BOOL
    GetProperties	proc :ptr
    ApplyProperties	proc :ptr, :ptr, :HWND, :ptr

    .ends

endif

ifndef __IFileOpenDialog_INTERFACE_DEFINED__
__IFileOpenDialog_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFileOpenDialog, "d57c7288-d4ad-4768-be02-9d969532d960")

.comdef IFileOpenDialog : public IFileDialog

    GetResults		proc :ptr
    GetSelectedItems	proc :ptr

    .ends

endif

CDCONTROLSTATEF		typedef SDWORD
CDCS_INACTIVE		equ 0
CDCS_ENABLED		equ 0x1
CDCS_VISIBLE		equ 0x2
CDCS_ENABLEDVISIBLE	equ 0x3


ifndef __IFileDialogCustomize_INTERFACE_DEFINED__
__IFileDialogCustomize_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFileDialogCustomize, "e6fdd21a-163f-4975-9c8c-a69f1ba37034")

.comdef IFileDialogCustomize : public IUnknown

    EnableOpenDropDown	proc :DWORD
    AddMenu		proc :DWORD, :LPCWSTR
    AddPushButton	proc :DWORD, :LPCWSTR
    AddComboBox		proc :DWORD
    AddRadioButtonList	proc :DWORD
    AddCheckButton	proc :DWORD, :LPCWSTR, :BOOL
    AddEditBox		proc :DWORD, :LPCWSTR
    AddSeparator	proc :DWORD
    AddText		proc :DWORD, :LPCWSTR
    SetControlLabel	proc :DWORD, :LPCWSTR
    GetControlState	proc :DWORD, :ptr
    SetControlState	proc :DWORD, :CDCONTROLSTATEF
    GetEditBoxText	proc :DWORD, :ptr
    SetEditBoxText	proc :DWORD, :LPCWSTR
    GetCheckButtonState proc :DWORD, :ptr
    SetCheckButtonState proc :DWORD, :BOOL
    AddControlItem	proc :DWORD, :DWORD, :LPCWSTR
    RemoveControlItem	proc :DWORD, :DWORD
    RemoveAllControlItems proc :DWORD
    GetControlItemState proc :DWORD, :DWORD, :ptr
    SetControlItemState proc :DWORD, :DWORD, :CDCONTROLSTATEF
    GetSelectedControlItem proc :DWORD, :ptr
    SetSelectedControlItem proc :DWORD, :DWORD
    StartVisualGroup	proc :DWORD, :LPCWSTR
    EndVisualGroup	proc
    MakeProminent	proc :DWORD
    SetControlItemText	proc :DWORD, :DWORD, :LPCWSTR

    .ends

endif

ifndef __IFileDialogControlEvents_INTERFACE_DEFINED__
__IFileDialogControlEvents_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFileDialogControlEvents, "36116642-D713-4b97-9B83-7484A9D00433")

.comdef IFileDialogControlEvents : public IUnknown

    OnItemSelected	proc :ptr, :DWORD, :DWORD
    OnButtonClicked	proc :ptr, :DWORD
    OnCheckButtonToggled proc :ptr, :DWORD, :BOOL
    OnControlActivating proc :ptr, :DWORD

    .ends

endif

ifndef __IFileDialog2_INTERFACE_DEFINED__
__IFileDialog2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFileDialog2, "61744fc7-85b5-4791-a9b0-272276309b13")

.comdef IFileDialog2 : public IFileDialog

    SetCancelButtonLabel proc :LPCWSTR
    SetNavigationRoot	proc :ptr

    .ends

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

ifndef __IApplicationAssociationRegistration_INTERFACE_DEFINED__
__IApplicationAssociationRegistration_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IApplicationAssociationRegistration, "4e530b0a-e611-4c77-a3ac-9031d022281b")

.comdef IApplicationAssociationRegistration : public IUnknown

    QueryCurrentDefault proc :LPCWSTR, :ASSOCIATIONTYPE, :ASSOCIATIONLEVEL, :ptr
    QueryAppIsDefault	proc :LPCWSTR, :ASSOCIATIONTYPE, :ASSOCIATIONLEVEL, :LPCWSTR, :ptr
    QueryAppIsDefaultAll proc :ASSOCIATIONLEVEL, :LPCWSTR, :ptr
    SetAppAsDefault	proc :LPCWSTR, :LPCWSTR, :ASSOCIATIONTYPE
    SetAppAsDefaultAll	proc :LPCWSTR
    ClearUserAssociations proc

    .ends

endif

;SHSTDAPI
SHCreateAssociationRegistration proto WINAPI \
		  riid: REFIID,
		   ppv: PVOID

ifndef __IApplicationAssociationRegistrationUI_INTERFACE_DEFINED__
__IApplicationAssociationRegistrationUI_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IApplicationAssociationRegistrationUI, "1f76a169-f994-40ac-8fc8-0959e8874710")

.comdef IApplicationAssociationRegistrationUI : public IUnknown

    LaunchAdvancedAssociationUI proc :LPCWSTR

    .ends

endif
endif

.pragma pack(push, 1)

DELEGATEITEMID		STRUC
cbSize			dw ?
wOuter			dw ?
cbInner			dw ?
rgb			db  1  dup(?)
DELEGATEITEMID		ENDS

.pragma pack(pop)

PCDELEGATEITEMID	typedef ptr DELEGATEITEMID
PDELEGATEITEMID		typedef ptr DELEGATEITEMID

ifndef __IDelegateFolder_INTERFACE_DEFINED__
__IDelegateFolder_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDelegateFolder, "ADD8BA80-002B-11D0-8F0F-00C04FD7D062")

.comdef IDelegateFolder : public IUnknown

    SetItemAlloc	proc :ptr

    .ends

endif

if (_WIN32_IE GE _WIN32_IE_IE60)

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
BFO_QUERY_ALL		equ 0xffffffff
BROWSERFRAMEOPTIONS	typedef DWORD

DEFINE_IIDX(IBrowserFrameOptions, "10DF43C8-1DBE-11d3-8B34-006097DF5BD4")

.comdef IBrowserFrameOptions : public IUnknown

    GetFrameOptions	proc :BROWSERFRAMEOPTIONS, :ptr

    .ends

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

SID_SNewWindowManager	equ <IID_INewWindowManager>

ifndef __INewWindowManager_INTERFACE_DEFINED__
__INewWindowManager_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(INewWindowManager, "D2BC4C84-3F72-4a52-A604-7BCBF3982CBB")

.comdef INewWindowManager : public IUnknown

    EvaluateNewWindow	proc :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPCWSTR, :BOOL, :DWORD, :DWORD

    .ends

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

DEFINE_IIDX(IAttachmentExecute, "73db1241-1e85-4581-8e4f-a81e1d0f8c57")

.comdef IAttachmentExecute : public IUnknown

    SetClientTitle	proc :LPCWSTR
    SetClientGuid	proc :REFGUID
    SetLocalPath	proc :LPCWSTR
    SetFileName		proc :LPCWSTR
    SetSource		proc :LPCWSTR
    SetReferrer		proc :LPCWSTR
    CheckPolicy		proc
    Prompt		proc :HWND, :ATTACHMENT_PROMPT, :ptr
    Save		proc
    Execute		proc :HWND, :LPCWSTR, :ptr
    SaveWithUI		proc :HWND
    ClearClientState	proc

    .ends

endif
endif

if (_WIN32_IE GE _WIN32_IE_IE60)

.pragma pack(push, 8)

SMDATA			STRUC
dwMask			dd ?
dwFlags			dd ?
hmenu			HMENU ?
hwnd			HWND ?
uId			UINT ?
uIdParent		UINT ?
uIdAncestor		UINT ?
punk			LPUNKNOWN ?
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

.pragma pack(pop)

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


ifndef __IShellMenuCallback_INTERFACE_DEFINED__
__IShellMenuCallback_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellMenuCallback, "4CA300A1-9B8D-11d1-8B22-00C04FD918D0")

.comdef IShellMenuCallback : public IUnknown

    CallbackSM		proc :LPSMDATA, :UINT, :WPARAM, :LPARAM

    .ends

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

ifndef __IShellMenu_INTERFACE_DEFINED__
__IShellMenu_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellMenu, "EE1F7637-E138-11d1-8379-00C04FD918D0")

.comdef IShellMenu : public IUnknown

    Initialize		proc :ptr, :UINT, :UINT, :DWORD
    GetMenuInfo		proc :ptr, :ptr, :ptr, :ptr
    SetShellFolder	proc :ptr, :PCIDLIST_ABSOLUTE, :HKEY, :DWORD
    GetShellFolder	proc :ptr, :ptr, :REFIID, :ptr
    SetMenu		proc :HMENU, :HWND, :DWORD
    GetMenu		proc :ptr, :ptr, :ptr
    InvalidateItem	proc :LPSMDATA, :DWORD
    GetState		proc :LPSMDATA
    SetMenuToolbar	proc :ptr, :DWORD

    .ends

endif
endif

ifndef __IShellRunDll_INTERFACE_DEFINED__
__IShellRunDll_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellRunDll, "fce4bde0-4b68-4b80-8e9c-7426315a7388")

.comdef IShellRunDll : public IUnknown

    Run			proc :LPCWSTR

    .ends

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

ifndef __IKnownFolder_INTERFACE_DEFINED__
__IKnownFolder_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IKnownFolder, "3AA7AF7E-9B36-420c-A8E3-F77D4674A488")

.comdef IKnownFolder : public IUnknown

    GetId		proc :ptr
    GetCategory		proc :ptr
    GetShellItem	proc :DWORD, :REFIID, :ptr
    GetPath		proc :DWORD, :ptr
    SetPath		proc :DWORD, :LPCWSTR
    GetIDList		proc :DWORD, :ptr
    GetFolderType	proc :ptr
    GetRedirectionCapabilities proc :ptr
    GetFolderDefinition proc :ptr

    .ends

endif

ifndef __IKnownFolderManager_INTERFACE_DEFINED__
__IKnownFolderManager_INTERFACE_DEFINED__ equ 1

FFFP_MODE		typedef SDWORD
FFFP_EXACTMATCH		equ 0
FFFP_NEARESTPARENTMATCH equ ( FFFP_EXACTMATCH + 1 )

DEFINE_IIDX(IKnownFolderManager, "8BE2D872-86AA-4d47-B776-32CCA40C7018")

.comdef IKnownFolderManager : public IUnknown

    FolderIdFromCsidl	proc :SINT, :ptr
    FolderIdToCsidl	proc :REFKNOWNFOLDERID, :ptr
    GetFolderIds	proc :ptr, :ptr
    GetFolder		proc :REFKNOWNFOLDERID, :ptr
    GetFolderByName	proc :LPCWSTR, :ptr
    RegisterFolder	proc :REFKNOWNFOLDERID, :ptr
    UnregisterFolder	proc :REFKNOWNFOLDERID
    FindFolderFromPath	proc :LPCWSTR, :FFFP_MODE, :ptr
    FindFolderFromIDList proc :PCIDLIST_ABSOLUTE, :ptr
    Redirect		proc :REFKNOWNFOLDERID, :HWND, :KF_REDIRECT_FLAGS, :LPCWSTR, :UINT, :ptr, :ptr

    .ends

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

ifndef __ISharingConfigurationManager_INTERFACE_DEFINED__
__ISharingConfigurationManager_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISharingConfigurationManager, "B4CD448A-9C86-4466-9201-2E62105B87AE")

.comdef ISharingConfigurationManager : public IUnknown

    CreateShare		proc :DEF_SHARE_ID, :SHARE_ROLE
    DeleteShare		proc :DEF_SHARE_ID
    ShareExists		proc :DEF_SHARE_ID
    GetSharePermissions proc :DEF_SHARE_ID, :ptr
    SharePrinters	proc
    StopSharingPrinters proc
    ArePrintersShared	proc

    .ends

endif
endif

ifndef __IPreviousVersionsInfo_INTERFACE_DEFINED__
__IPreviousVersionsInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPreviousVersionsInfo, "76e54780-ad74-48e3-a695-3ba9a0aff10d")

.comdef IPreviousVersionsInfo : public IUnknown

    AreSnapshotsAvailable proc :LPCWSTR, :BOOL, :ptr

    .ends

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

ifndef __IRelatedItem_INTERFACE_DEFINED__
__IRelatedItem_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRelatedItem, "a73ce67a-8ab1-44f1-8d43-d2fcbf6b1cd0")

.comdef IRelatedItem : public IUnknown

    GetItemIDList	proc :ptr
    GetItem		proc :ptr

    .ends

endif

ifndef __IIdentityName_INTERFACE_DEFINED__
__IIdentityName_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IIdentityName, "7d903fca-d6f9-4810-8332-946c0177e247")

.comdef IIdentityName : public IRelatedItem

    .ends

endif

ifndef __IDelegateItem_INTERFACE_DEFINED__
__IDelegateItem_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDelegateItem, "3c5a1c94-c951-4cb7-bb6d-3b93f30cce93")

.comdef IDelegateItem : public IRelatedItem

    .ends

endif

ifndef __ICurrentItem_INTERFACE_DEFINED__
__ICurrentItem_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICurrentItem, "240a7174-d653-4a1d-a6d3-d4943cfbfe3d")

.comdef ICurrentItem : public IRelatedItem

    .ends

endif

ifndef __ITransferMediumItem_INTERFACE_DEFINED__
__ITransferMediumItem_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ITransferMediumItem, "77f295d5-2d6f-4e19-b8ae-322f3e721ab5")

.comdef ITransferMediumItem : public IRelatedItem

    .ends

endif

ifndef __IUseToBrowseItem_INTERFACE_DEFINED__
__IUseToBrowseItem_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IUseToBrowseItem, "05edda5c-98a3-4717-8adb-c5e7da991eb1")

.comdef IUseToBrowseItem : public IRelatedItem

    .ends

endif

ifndef __IDisplayItem_INTERFACE_DEFINED__
__IDisplayItem_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDisplayItem, "c6fd5997-9f6b-4888-8703-94e80e8cde3f")

.comdef IDisplayItem : public IRelatedItem

    .ends

endif

ifndef __IViewStateIdentityItem_INTERFACE_DEFINED__
__IViewStateIdentityItem_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IViewStateIdentityItem, "9D264146-A94F-4195-9F9F-3BB12CE0C955")

.comdef IViewStateIdentityItem : public IRelatedItem

    .ends

endif

ifndef __IPreviewItem_INTERFACE_DEFINED__
__IPreviewItem_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPreviewItem, "36149969-0A8F-49c8-8B00-4AECB20222FB")

.comdef IPreviewItem : public IRelatedItem

    .ends

endif
endif

ifndef __IDestinationStreamFactory_INTERFACE_DEFINED__
__IDestinationStreamFactory_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDestinationStreamFactory, "8a87781b-39a7-4a1f-aab3-a39b9c34a7d9")

.comdef IDestinationStreamFactory : public IUnknown

    GetDestinationStream proc :ptr

    .ends

endif

NMCII_FLAGS		typedef SDWORD
NMCII_ITEMS		equ 0x1
NMCII_FOLDERS		equ 0x2
NMCII_FLAGS		typedef SINT

NMCSAEI_FLAGS		typedef SDWORD
NMCSAEI_SELECT		equ 0
NMCSAEI_EDIT		equ 0x1
NMCSAEI_FLAGS		typedef SINT

ifndef __INewMenuClient_INTERFACE_DEFINED__
__INewMenuClient_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(INewMenuClient, "dcb07fdc-3bb5-451c-90be-966644fed7b0")

.comdef INewMenuClient : public IUnknown

    IncludeItems	proc :ptr
    SelectAndEditItem	proc :PCIDLIST_ABSOLUTE, :NMCSAEI_FLAGS

    .ends

endif

SID_SNewMenuClient	equ <IID_INewMenuClient>
DEFINE_GUID(SID_SCommandBarState, 0xB99EAA5C, 0x3850, 0x4400, 0xBC, 0x33, 0x2C, 0xE5, 0x34, 0x04, 0x8B, 0xF8);

if (_WIN32_IE GE _WIN32_IE_IE70)

ifndef __IInitializeWithBindCtx_INTERFACE_DEFINED__
__IInitializeWithBindCtx_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInitializeWithBindCtx, "71c0d2bc-726d-45cc-a6c0-2e31c1db2159")

.comdef IInitializeWithBindCtx : public IUnknown

    Initialize		proc :ptr

    .ends

endif

ifndef __IShellItemFilter_INTERFACE_DEFINED__
__IShellItemFilter_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellItemFilter, "2659B475-EEB8-48b7-8F07-B378810F48CF")

.comdef IShellItemFilter : public IUnknown

    IncludeItem		proc :ptr
    GetEnumFlagsForItem proc :ptr, :ptr

    .ends

endif
endif

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

DEFINE_IIDX(INameSpaceTreeControl, "028212A3-B627-47e9-8856-C14265554E4F")

.comdef INameSpaceTreeControl : public IUnknown

    Initialize		proc :HWND, :ptr, :NSTCSTYLE
    TreeAdvise		proc :ptr, :ptr
    TreeUnadvise	proc :DWORD
    AppendRoot		proc :ptr, :SHCONTF, :NSTCROOTSTYLE, :ptr
    InsertRoot		proc :SINT, :ptr, :SHCONTF, :NSTCROOTSTYLE, :ptr
    RemoveRoot		proc :ptr
    RemoveAllRoots	proc
    GetRootItems	proc :ptr
    SetItemState	proc :ptr, :NSTCITEMSTATE, :NSTCITEMSTATE
    GetItemState	proc :ptr, :NSTCITEMSTATE, :ptr
    GetSelectedItems	proc :ptr
    GetItemCustomState	proc :ptr, :ptr
    SetItemCustomState	proc :ptr, :SINT
    EnsureItemVisible	proc :ptr
    SetTheme		proc :LPCWSTR
    GetNextItem		proc :ptr, :NSTCGNI, :ptr
    HitTest		proc :ptr, :ptr
    GetItemRect		proc :ptr, :ptr
    CollapseAll		proc

    .ends

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

DEFINE_IIDX(INameSpaceTreeControl2, "7cc7aed8-290e-49bc-8945-c1401cc9306c")

.comdef INameSpaceTreeControl2 : public INameSpaceTreeControl

    SetControlStyle	proc :NSTCSTYLE, :NSTCSTYLE
    GetControlStyle	proc :NSTCSTYLE, :ptr
    SetControlStyle2	proc :NSTCSTYLE2, :NSTCSTYLE2
    GetControlStyle2	proc :NSTCSTYLE2, :ptr

    .ends

endif

NSTCS2_ALLMASK		equ (NSTCS2_INTERRUPTNOTIFICATIONS OR NSTCS2_SHOWNULLSPACEMENU OR NSTCS2_DISPLAYPADDING)
SID_SNavigationPane	equ <IID_INameSpaceTreeControl>
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

DEFINE_IIDX(INameSpaceTreeControlEvents, "93D77985-B3D8-4484-8318-672CDDA002CE")

.comdef INameSpaceTreeControlEvents : public IUnknown

    OnItemClick		proc :ptr, :NSTCEHITTEST, :NSTCECLICKTYPE
    OnPropertyItemCommit proc :ptr
    OnItemStateChanging proc :ptr, :NSTCITEMSTATE, :NSTCITEMSTATE
    OnItemStateChanged	proc :ptr, :NSTCITEMSTATE, :NSTCITEMSTATE
    OnSelectionChanged	proc :ptr
    OnKeyboardInput	proc :UINT, :WPARAM, :LPARAM
    OnBeforeExpand	proc :ptr
    OnAfterExpand	proc :ptr
    OnBeginLabelEdit	proc :ptr
    OnEndLabelEdit	proc :ptr
    OnGetToolTip	proc :ptr, :LPWSTR, :SINT
    OnBeforeItemDelete	proc :ptr
    OnItemAdded		proc :ptr, :BOOL
    OnItemDeleted	proc :ptr, :BOOL
    OnBeforeContextMenu proc :ptr, :REFIID, :ptr
    OnAfterContextMenu	proc :ptr, :ptr, :REFIID, :ptr
    OnBeforeStateImageChange proc :ptr
    OnGetDefaultIconIndex proc :ptr, :ptr, :ptr
    .ends

endif


NSTCDHPOS_ONTOP		equ -1

ifndef __INameSpaceTreeControlDropHandler_INTERFACE_DEFINED__
__INameSpaceTreeControlDropHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(INameSpaceTreeControlDropHandler, "F9C665D6-C2F2-4c19-BF33-8322D7352F51")

.comdef INameSpaceTreeControlDropHandler : public IUnknown

    OnDragEnter		proc :ptr, :ptr, :BOOL, :DWORD, :ptr
    OnDragOver		proc :ptr, :ptr, :DWORD, :ptr
    OnDragPosition	proc :ptr, :ptr, :SINT, :SINT
    OnDrop		proc :ptr, :ptr, :SINT, :DWORD, :ptr
    OnDropPosition	proc :ptr, :ptr, :SINT, :SINT
    OnDragLeave		proc :ptr

    .ends

endif

ifndef __INameSpaceTreeAccessible_INTERFACE_DEFINED__
__INameSpaceTreeAccessible_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(INameSpaceTreeAccessible, "71f312de-43ed-4190-8477-e9536b82350b")

.comdef INameSpaceTreeAccessible : public IUnknown

    OnGetDefaultAccessibilityAction proc :ptr, :ptr
    OnDoDefaultAccessibilityAction proc :ptr
    OnGetAccessibilityRole proc :ptr, :ptr

    .ends

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

DEFINE_IIDX(INameSpaceTreeControlCustomDraw, "2D3BA758-33EE-42d5-BB7B-5F3431D86C78")

.comdef INameSpaceTreeControlCustomDraw : public IUnknown

    PrePaSINT		proc :HDC, :ptr, :ptr
    PostPaSINT		proc :HDC, :ptr
    ItemPrePaSINT	proc :HDC, :ptr, :ptr, :ptr, :ptr, :ptr
    ItemPostPaSINT	proc :HDC, :ptr, :ptr

    .ends

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

ifndef __INameSpaceTreeControlFolderCapabilities_INTERFACE_DEFINED__
__INameSpaceTreeControlFolderCapabilities_INTERFACE_DEFINED__ equ 1

NSTCFOLDERCAPABILITIES	typedef SDWORD
NSTCFC_NONE		equ 0
NSTCFC_PINNEDITEMFILTERING equ 0x1
NSTCFC_DELAY_REGISTER_NOTIFY equ 0x2

DEFINE_IIDX(INameSpaceTreeControlFolderCapabilities, "e9701183-e6b3-4ff2-8568-813615fec7be")

.comdef INameSpaceTreeControlFolderCapabilities : public IUnknown

    GetFolderCapabilities proc :NSTCFOLDERCAPABILITIES, :ptr

    .ends

endif
endif

E_PREVIEWHANDLER_DRM_FAIL equ _HRESULT_TYPEDEF_(0x86420001)
E_PREVIEWHANDLER_NOAUTH equ _HRESULT_TYPEDEF_(0x86420002)
E_PREVIEWHANDLER_NOTFOUND equ _HRESULT_TYPEDEF_(0x86420003)
E_PREVIEWHANDLER_CORRUPT equ _HRESULT_TYPEDEF_(0x86420004)

ifndef __IPreviewHandler_INTERFACE_DEFINED__
__IPreviewHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPreviewHandler, "8895b1c6-b41f-4c1c-a562-0d564250836f")

.comdef IPreviewHandler : public IUnknown

    SetWindow		proc :HWND, :ptr
    SetRect		proc :ptr
    DoPreview		proc
    Unload		proc
    SetFocus		proc
    QueryFocus		proc :ptr
    TranslateAccelerator proc :ptr

    .ends

endif

ifndef __IPreviewHandlerFrame_INTERFACE_DEFINED__
__IPreviewHandlerFrame_INTERFACE_DEFINED__ equ 1

PREVIEWHANDLERFRAMEINFO STRUC
haccel			HACCEL ?
cAccelEntries		UINT ?
PREVIEWHANDLERFRAMEINFO ENDS

DEFINE_IIDX(IPreviewHandlerFrame, "fec87aaf-35f9-447a-adb7-20234491401a")

.comdef IPreviewHandlerFrame : public IUnknown

    GetWindowContext	proc :ptr
    TranslateAccelerator proc :ptr

    .ends

endif

if (NTDDI_VERSION GE NTDDI_VISTA)

ifndef __ITrayDeskBand_INTERFACE_DEFINED__
__ITrayDeskBand_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ITrayDeskBand, "6D67E846-5B9C-4db8-9CBC-DDE12F4254F1")

.comdef ITrayDeskBand : public IUnknown

    ShowDeskBand	proc :REFCLSID
    HideDeskBand	proc :REFCLSID
    IsDeskBandShown	proc :REFCLSID
    DeskBandRegistrationChanged proc

    .ends

endif

ifndef __IBandHost_INTERFACE_DEFINED__
define __IBandHost_INTERFACE_DEFINED__

DEFINE_IIDX(IBandHost, "B9075C7C-D48E-403f-AB99-D6C77A1084AC")

.comdef IBandHost : public IUnknown

    CreateBand		proc :REFCLSID, :BOOL, :BOOL, :REFIID, :ptr
    SetBandAvailability proc :REFCLSID, :BOOL
    DestroyBand		proc :REFCLSID

    .ends

endif

SID_SBandHost		equ <IID_IBandHost>
EXPLORERPANE		typedef GUID
REFEXPLORERPANE		typedef ptr EXPLORERPANE

ifndef __IExplorerPaneVisibility_INTERFACE_DEFINED__
define __IExplorerPaneVisibility_INTERFACE_DEFINED__

.enum EXPLORERPANESTATE {
    EPS_DONTCARE	= 0,
    EPS_DEFAULT_ON	= 0x1,
    EPS_DEFAULT_OFF	= 0x2,
    EPS_STATEMASK	= 0xffff,
    EPS_INITIALSTATE	= 0x10000,
    EPS_FORCE		= 0x20000
    }

DEFINE_IIDX(IExplorerPaneVisibility, "e07010ec-bc17-44c0-97b0-46c7c95b9edc")

.comdef IExplorerPaneVisibility : public IUnknown

    GetPaneState	proc :REFEXPLORERPANE, :ptr

    .ends

endif

SID_ExplorerPaneVisibility equ <IID_IExplorerPaneVisibility>

ifndef __IContextMenuCB_INTERFACE_DEFINED__
define __IContextMenuCB_INTERFACE_DEFINED__

DEFINE_IIDX(IContextMenuCB, "3409E930-5A39-11d1-83FA-00A0C90DC849")

.comdef IContextMenuCB : public IUnknown

    CallBack		proc :ptr, :HWND, :ptr, :UINT, :WPARAM, :LPARAM

    .ends

LPIContextMenuCB	typedef ptr IContextMenuCB

endif
endif

ifndef __IDefaultExtractIconInit_INTERFACE_DEFINED__
define __IDefaultExtractIconInit_INTERFACE_DEFINED__

DEFINE_IIDX(IDefaultExtractIconInit, "41ded17d-d6b3-4261-997d-88c60e4b1d58")

.comdef IDefaultExtractIconInit : public IUnknown

    SetFlags		proc :UINT
    SetKey		proc :HKEY
    SetNormalIcon	proc :LPCWSTR, :SINT
    SetOpenIcon		proc :LPCWSTR, :SINT
    SetShortcutIcon	proc :LPCWSTR, :SINT
    SetDefaultIcon	proc :LPCWSTR, :SINT

    .ends

endif

;STDAPI
SHCreateDefaultExtractIcon proto WINAPI \
		  riid: REFIID,
		   ppv: PVOID

ifndef __IExplorerCommand_INTERFACE_DEFINED__
define __IExplorerCommand_INTERFACE_DEFINED__

.enum EXPCMDSTATE {
    ECS_ENABLED		= 0,
    ECS_DISABLED	= 0x1,
    ECS_HIDDEN		= 0x2,
    ECS_CHECKBOX	= 0x4,
    ECS_CHECKED		= 0x8,
    ECS_RADIOCHECK	= 0x10
    }

.enum EXPCMDFLAGS {
    ECF_DEFAULT		= 0,
    ECF_HASSUBCOMMANDS	= 0x1,
    ECF_HASSPLITBUTTON	= 0x2,
    ECF_HIDELABEL	= 0x4,
    ECF_ISSEPARATOR	= 0x8,
    ECF_HASLUASHIELD	= 0x10,
    ECF_SEPARATORBEFORE = 0x20,
    ECF_SEPARATORAFTER	= 0x40,
    ECF_ISDROPDOWN	= 0x80
    }

DEFINE_IIDX(IExplorerCommand, "a08ce4d0-fa25-44ab-b57c-c7b1c323e0b9")

.comdef IExplorerCommand : public IUnknown

    GetTitle		proc :ptr, :ptr
    GetIcon		proc :ptr, :ptr
    GetToolTip		proc :ptr, :ptr
    GetCanonicalName	proc :ptr
    GetState		proc :ptr, :BOOL, :ptr
    _Invoke		proc :ptr, :ptr
    GetFlags		proc :ptr
    EnumSubCommands	proc :ptr

    .ends

endif

ifndef __IExplorerCommandState_INTERFACE_DEFINED__
define __IExplorerCommandState_INTERFACE_DEFINED__

DEFINE_IIDX(IExplorerCommandState, "bddacb60-7657-47ae-8445-d23e1acf82ae")

.comdef IExplorerCommandState : public IUnknown

    GetState		proc :ptr, :BOOL, :ptr

    .ends

endif

ifndef __IInitializeCommand_INTERFACE_DEFINED__
define __IInitializeCommand_INTERFACE_DEFINED__

DEFINE_IIDX(IInitializeCommand, "85075acf-231f-40ea-9610-d26b7b58f638")

.comdef IInitializeCommand : public IUnknown

    Initialize		proc :LPCWSTR, :ptr

    .ends

endif

ifndef __IEnumExplorerCommand_INTERFACE_DEFINED__
define __IEnumExplorerCommand_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumExplorerCommand, "a88826f8-186f-4987-aade-ea0cef8fbfe8")

.comdef IEnumExplorerCommand : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr

    .ends

endif

ifndef __IExplorerCommandProvider_INTERFACE_DEFINED__
define __IExplorerCommandProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IExplorerCommandProvider, "64961751-0835-43c0-8ffe-d57686530e64")

.comdef IExplorerCommandProvider : public IUnknown

    GetCommands		proc :ptr, :REFIID, :ptr
    GetCommand		proc :REFGUID, :REFIID, :ptr

    .ends

endif

ifndef __IMarkupCallback_INTERFACE_DEFINED__
define __IMarkupCallback_INTERFACE_DEFINED__

DEFINE_IIDX(IMarkupCallback, "4440306e-d79a-48d0-88e6-a42692279bfb")

.comdef IMarkupCallback : public IUnknown

    GetState		proc :DWORD, :UINT
    Notify		proc :DWORD, :SINT, :SINT
    InvalidateRect	proc :DWORD, :ptr
    OnCustomDraw	proc :DWORD, :HDC, :ptr, :DWORD, :SINT, :UINT, :ptr
    CustomDrawText	proc :HDC, :LPCWSTR, :SINT, :ptr, :UINT, :BOOL

    .ends

endif

HTHEME			typedef HANDLE

ifndef __IControlMarkup_INTERFACE_DEFINED__
define __IControlMarkup_INTERFACE_DEFINED__

.enum MARKUPSIZE {
    MARKUPSIZE_CALCWIDTH  = 0,
    MARKUPSIZE_CALCHEIGHT = ( MARKUPSIZE_CALCWIDTH + 1 )
    }

.enum MARKUPLINKTEXT {
    MARKUPLINKTEXT_URL	= 0,
    MARKUPLINKTEXT_ID	= ( MARKUPLINKTEXT_URL + 1 ),
    MARKUPLINKTEXT_TEXT = ( MARKUPLINKTEXT_ID + 1 )
    }

.enum MARKUPSTATE {
    MARKUPSTATE_FOCUSED = 0x1,
    MARKUPSTATE_ENABLED = 0x2,
    MARKUPSTATE_VISITED = 0x4,
    MARKUPSTATE_HOT	= 0x8,
    MARKUPSTATE_DEFAULTCOLORS = 0x10,
    MARKUPSTATE_ALLOWMARKUP = 0x40000000
    }

.enum MARKUPMESSAGE {
    MARKUPMESSAGE_KEYEXECUTE   = 0,
    MARKUPMESSAGE_CLICKEXECUTE = ( MARKUPMESSAGE_KEYEXECUTE + 1 ),
    MARKUPMESSAGE_WANTFOCUS    = ( MARKUPMESSAGE_CLICKEXECUTE + 1 )
    }

DEFINE_IIDX(IControlMarkup, "D6D2FBAE-F116-458c-8C34-03569877A2D2")

.comdef IControlMarkup : public IUnknown

    SetCallback		proc :ptr
    GetCallback		proc :REFIID, :ptr
    SetId		proc :DWORD
    GetId		proc :ptr
    SetFonts		proc :HFONT, :HFONT
    GetFonts		proc :ptr, :ptr
    SetText		proc :LPCWSTR
    GetText		proc :BOOL, :LPWSTR, :ptr
    SetLinkText		proc :SINT, :UINT, :LPCWSTR
    GetLinkText		proc :SINT, :UINT, :LPWSTR, :ptr
    SetRenderFlags	proc :UINT
    GetRenderFlags	proc :ptr, :ptr, :ptr, :ptr, :ptr
    SetThemeRenderFlags proc :UINT, :HTHEME, :SINT, :SINT, :SINT
    GetState		proc :SINT, :UINT, :ptr
    SetState		proc :SINT, :UINT, :UINT
    DrawText		proc :HDC, :LPCRECT
    SetLinkCursor	proc
    CalcIdealSize	proc :HDC, :UINT, :ptr
    SetFocus		proc
    KillFocus		proc
    IsTabbable		proc
    OnButtonDown	proc :POINT
    OnButtonUp		proc :POINT
    OnKeyDown		proc :UINT
    HitTest		proc :POINT, :ptr
    GetLinkRect		proc :SINT, :ptr
    GetControlRect	proc :ptr
    GetLinkCount	proc :ptr

    .ends

endif

ifndef __IInitializeNetworkFolder_INTERFACE_DEFINED__
define __IInitializeNetworkFolder_INTERFACE_DEFINED__

DEFINE_IIDX(IInitializeNetworkFolder, "6e0f9881-42a8-4f2a-97f8-8af4e026d92d")

.comdef IInitializeNetworkFolder : public IUnknown

    Initialize		proc :PCIDLIST_ABSOLUTE, :PCIDLIST_ABSOLUTE, :UINT, :LPCWSTR, :LPCWSTR

    .ends

endif

.enum CPVIEW {
    CPVIEW_CLASSIC	= 0,
    CPVIEW_ALLITEMS	= CPVIEW_CLASSIC,
    CPVIEW_CATEGORY	= 1,
    CPVIEW_HOME		= CPVIEW_CATEGORY
    }

ifndef __IOpenControlPanel_INTERFACE_DEFINED__
define __IOpenControlPanel_INTERFACE_DEFINED__

DEFINE_IIDX(IOpenControlPanel, "D11AD862-66DE-4DF4-BF6C-1F5621996AF1")

.comdef IOpenControlPanel : public IUnknown

    Open		proc :LPCWSTR, :LPCWSTR, :ptr
    GetPath		proc :LPCWSTR, :LPWSTR, :UINT
    GetCurrentView	proc :ptr

    .ends

endif

ifndef __IComputerInfoChangeNotify_INTERFACE_DEFINED__
define __IComputerInfoChangeNotify_INTERFACE_DEFINED__

DEFINE_IIDX(IComputerInfoChangeNotify, "0DF60D92-6818-46d6-B358-D66170DDE466")

.comdef IComputerInfoChangeNotify : public IUnknown

    ComputerInfoChanged proc

    .ends

endif

STR_FILE_SYS_BIND_DATA	equ <L"File System Bind Data">

ifndef __IFileSystemBindData_INTERFACE_DEFINED__
define __IFileSystemBindData_INTERFACE_DEFINED__

DEFINE_IIDX(IFileSystemBindData, "01E18D10-4D8B-11d2-855D-006008059367")

.comdef IFileSystemBindData : public IUnknown

    SetFindData		proc :ptr
    GetFindData		proc :ptr

    .ends

endif

ifndef __IFileSystemBindData2_INTERFACE_DEFINED__
define __IFileSystemBindData2_INTERFACE_DEFINED__

DEFINE_IIDX(IFileSystemBindData2, "3acf075f-71db-4afa-81f0-3fc4fdf2a5b8")

.comdef IFileSystemBindData2 : public IFileSystemBindData

    SetFileID		proc :LARGE_INTEGER
    GetFileID		proc :ptr
    SetJunctionCLSID	proc :REFCLSID
    GetJunctionCLSID	proc :ptr

    .ends

endif

if (NTDDI_VERSION GE NTDDI_WIN7)

ifndef __ICustomDestinationList_INTERFACE_DEFINED__
define __ICustomDestinationList_INTERFACE_DEFINED__

.enum KNOWNDESTCATEGORY {
    KDC_FREQUENT	= 1,
    KDC_RECENT		= ( KDC_FREQUENT + 1 )
    }

DEFINE_IIDX(ICustomDestinationList, "6332debf-87b5-4670-90c0-5e57b408a49e")

.comdef ICustomDestinationList : public IUnknown

    SetAppID		proc :LPCWSTR
    BeginList		proc :ptr, :REFIID, :ptr
    AppendCategory	proc :LPCWSTR, :ptr
    AppendKnownCategory proc :KNOWNDESTCATEGORY
    AddUserTasks	proc :ptr
    CommitList		proc
    GetRemovedDestinations proc :REFIID, :ptr
    DeleteList		proc :LPCWSTR
    AbortList		proc

    .ends

endif

ifndef __IApplicationDestinations_INTERFACE_DEFINED__
define __IApplicationDestinations_INTERFACE_DEFINED__

DEFINE_IIDX(IApplicationDestinations, "12337d35-94c6-48a0-bce7-6a9c69d4d600")

.comdef IApplicationDestinations : public IUnknown

    SetAppID		proc :LPCWSTR
    RemoveDestination	proc :ptr
    RemoveAllDestinations proc

    .ends

endif

ifndef __IApplicationDocumentLists_INTERFACE_DEFINED__
define __IApplicationDocumentLists_INTERFACE_DEFINED__

.enum APPDOCLISTTYPE {
    ADLT_RECENT		= 0,
    ADLT_FREQUENT	= ( ADLT_RECENT + 1 )
    }

DEFINE_IIDX(IApplicationDocumentLists, "3c594f9f-9f30-47a1-979a-c9e83d3d0a06")

.comdef IApplicationDocumentLists : public IUnknown

    SetAppID		proc :LPCWSTR
    GetList		proc :APPDOCLISTTYPE, :UINT, :REFIID, :ptr

    .ends

endif

ifndef __IObjectWithAppUserModelID_INTERFACE_DEFINED__
define __IObjectWithAppUserModelID_INTERFACE_DEFINED__

DEFINE_IIDX(IObjectWithAppUserModelID, "36db0196-9665-46d1-9ba7-d3709eecf9ed")

.comdef IObjectWithAppUserModelID : public IUnknown

    SetAppID		proc :LPCWSTR
    GetAppID		proc :ptr

    .ends

endif

ifndef __IObjectWithProgID_INTERFACE_DEFINED__
define __IObjectWithProgID_INTERFACE_DEFINED__

DEFINE_IIDX(IObjectWithProgID, "71e806fb-8dee-46fc-bf8c-7748a8a1ae13")

.comdef IObjectWithProgID : public IUnknown

    SetProgID		proc :LPCWSTR
    GetProgID		proc :ptr

    .ends

endif

ifndef __IUpdateIDList_INTERFACE_DEFINED__
define __IUpdateIDList_INTERFACE_DEFINED__

DEFINE_IIDX(IUpdateIDList, "6589b6d2-5f8d-4b9e-b7e0-23cdd9717d8c")

.comdef IUpdateIDList : public IUnknown

    Update		proc :ptr, :PCUITEMID_CHILD, :ptr

    .ends

endif

;SHSTDAPI
SetCurrentProcessExplicitAppUserModelID proto WINAPI \
		 AppID: PCWSTR

;SHSTDAPI
GetCurrentProcessExplicitAppUserModelID proto WINAPI \
		 AppID: ptr PWSTR

endif


ifndef __IDesktopGadget_INTERFACE_DEFINED__
define __IDesktopGadget_INTERFACE_DEFINED__

DEFINE_IIDX(IDesktopGadget, "c1646bc4-f298-4f91-a204-eb2dd1709d1a")

.comdef IDesktopGadget : public IUnknown

    RunGadget		proc :LPCWSTR

    .ends

endif

if (NTDDI_VERSION GE NTDDI_WIN8)

ifndef __IDesktopWallpaper_INTERFACE_DEFINED__
define __IDesktopWallpaper_INTERFACE_DEFINED__

.enum DESKTOP_SLIDESHOW_OPTIONS {
    DSO_SHUFFLEIMAGES	= 0x1
    }

.enum DESKTOP_SLIDESHOW_STATE {
    DSS_ENABLED		= 0x1,
    DSS_SLIDESHOW	= 0x2,
    DSS_DISABLED_BY_REMOTE_SESSION = 0x4
    }

.enum DESKTOP_SLIDESHOW_DIRECTION {
    DSD_FORWARD		= 0,
    DSD_BACKWARD	= 1
    }

.enum DESKTOP_WALLPAPER_POSITION {
    DWPOS_CENTER	= 0,
    DWPOS_TILE		= 1,
    DWPOS_STRETCH	= 2,
    DWPOS_FIT		= 3,
    DWPOS_FILL		= 4,
    DWPOS_SPAN		= 5
    }

DEFINE_IIDX(IDesktopWallpaper, "B92B56A9-8B55-4E14-9A89-0199BBB6F93B")

.comdef IDesktopWallpaper : public IUnknown

    SetWallpaper	proc :LPCWSTR, :LPCWSTR
    GetWallpaper	proc :LPCWSTR, :ptr LPWSTR
    GetMonitorDevicePathAt proc :UINT, :ptr LPWSTR
    GetMonitorDevicePathCount proc :ptr UINT
    GetMonitorRECT	proc :LPCWSTR, :ptr RECT
    SetBackgroundColor	proc :COLORREF
    GetBackgroundColor	proc :ptr COLORREF
    SetPosition		proc :DESKTOP_WALLPAPER_POSITION
    GetPosition		proc :DESKTOP_WALLPAPER_POSITION
    SetSlideshow	proc :ptr IShellItemArray
    GetSlideshow	proc :ptr ptr IShellItemArray
    SetSlideshowOptions proc :DESKTOP_SLIDESHOW_OPTIONS, :UINT
    GetSlideshowOptions proc :ptr DESKTOP_SLIDESHOW_OPTIONS, :ptr UINT
    AdvanceSlideshow	proc :LPCWSTR, :DESKTOP_SLIDESHOW_DIRECTION
    GetStatus		proc :ptr DESKTOP_SLIDESHOW_STATE
    Enable		proc :BOOL

    .ends

endif
endif

HOMEGROUP_SECURITY_GROUP equ <L"HomeUsers">

ifndef __IHomeGroup_INTERFACE_DEFINED__
define __IHomeGroup_INTERFACE_DEFINED__

.enum HOMEGROUPSHARINGCHOICES {
    HGSC_NONE			= 0x0,
    HGSC_MUSICLIBRARY		= 0x1,
    HGSC_PICTURESLIBRARY	= 0x2,
    HGSC_VIDEOSLIBRARY		= 0x4,
    HGSC_DOCUMENTSLIBRARY	= 0x8,
    HGSC_PRINTERS		= 0x10
    }


DEFINE_IIDX(IHomeGroup, "7a3bd1d9-35a9-4fb3-a467-f48cac35e2d0")

.comdef IHomeGroup : public IUnknown

    IsMember		proc :ptr
    ShowSharingWizard	proc :HWND, :ptr

    .ends

endif

ifndef __IInitializeWithPropertyStore_INTERFACE_DEFINED__
__IInitializeWithPropertyStore_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInitializeWithPropertyStore, "C3E12EB5-7D8D-44f8-B6DD-0E77B34D6DE4")

.comdef IInitializeWithPropertyStore : public IUnknown

    Initialize		proc :ptr

    .ends

endif

ifndef __IOpenSearchSource_INTERFACE_DEFINED__
__IOpenSearchSource_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IOpenSearchSource, "F0EE7333-E6FC-479b-9F25-A860C234A38E")

.comdef IOpenSearchSource : public IUnknown

    GetResults		proc :HWND, :LPCWSTR, :DWORD, :DWORD, :REFIID, :ptr

    .ends

endif

ifndef __IShellLibrary_INTERFACE_DEFINED__
define __IShellLibrary_INTERFACE_DEFINED__


.enum LIBRARYFOLDERFILTER {
    LFF_FORCEFILESYSTEM = 1,
    LFF_STORAGEITEMS = 2,
    LFF_ALLITEMS = 3
    }

.enum LIBRARYOPTIONFLAGS {
    LOF_DEFAULT,
    LOF_PINNEDTONAVPANE,
    LOF_MASK_ALL = 1
    }

.enum DEFAULTSAVEFOLDERTYPE {
    DSFT_DETECT = 1,
    DSFT_PRIVATE = ( DSFT_DETECT + 1 ),
    DSFT_PUBLIC = ( DSFT_PRIVATE + 1 )
    }

.enum LIBRARYSAVEFLAGS {
    LSF_FAILIFTHERE,
    LSF_OVERRIDEEXISTING,
    LSF_MAKEUNIQUENAME
    }


DEFINE_IIDX(IShellLibrary, "11a66efa-382e-451a-9234-1e0e12ef3085")

.comdef IShellLibrary : public IUnknown

    LoadLibraryFromItem proc :ptr, :DWORD
    LoadLibraryFromKnownFolder proc :REFKNOWNFOLDERID, :DWORD
    AddFolder		proc :ptr
    RemoveFolder	proc :ptr
    GetFolders		proc :LIBRARYFOLDERFILTER, :REFIID, :ptr
    ResolveFolder	proc :ptr, :DWORD, :REFIID, :ptr
    GetDefaultSaveFolder proc :DEFAULTSAVEFOLDERTYPE, :REFIID, :ptr
    SetDefaultSaveFolder proc :DEFAULTSAVEFOLDERTYPE, :ptr
    GetOptions		proc :ptr
    SetOptions		proc :LIBRARYOPTIONFLAGS, :LIBRARYOPTIONFLAGS
    GetFolderType	proc :ptr
    SetFolderType	proc :REFFOLDERTYPEID
    GetIcon		proc :ptr
    SetIcon		proc :LPCWSTR
    Commit		proc
    Save		proc :ptr, :LPCWSTR, :LIBRARYSAVEFLAGS, :ptr
    SaveInKnownFolder	proc :REFKNOWNFOLDERID, :LPCWSTR, :LIBRARYSAVEFLAGS, :ptr

    .ends

endif

DEFAULT_FOLDER_MENU_RESTRICTIONS typedef sdword
DFMR_DEFAULT		equ 0
DFMR_NO_STATIC_VERBS	equ 0x8
DFMR_STATIC_VERBS_ONLY	equ 0x10
DFMR_NO_RESOURCE_VERBS	equ 0x20
DFMR_OPTIN_HANDLERS_ONLY equ 0x40
DFMR_RESOURCE_AND_FOLDER_VERBS_ONLY equ 0x80
DFMR_USE_SPECIFIED_HANDLERS equ 0x100
DFMR_USE_SPECIFIED_VERBS equ 0x200
DFMR_NO_ASYNC_VERBS	equ 0x400


ifndef __IDefaultFolderMenuInitialize_INTERFACE_DEFINED__
__IDefaultFolderMenuInitialize_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IDefaultFolderMenuInitialize, "7690aa79-f8fc-4615-a327-36f7d18f5d91")

.comdef IDefaultFolderMenuInitialize : public IUnknown

    Initialize		proc :HWND, :ptr, :ptr, :ptr, :UINT, :ptr, :ptr, :UINT, :ptr
    SetMenuRestrictions proc :DEFAULT_FOLDER_MENU_RESTRICTIONS
    GetMenuRestrictions proc :DEFAULT_FOLDER_MENU_RESTRICTIONS, :ptr DEFAULT_FOLDER_MENU_RESTRICTIONS
    SetHandlerClsid	proc :REFCLSID

    .ends

endif

if (NTDDI_VERSION GE NTDDI_WIN8)

.enum ACTIVATEOPTIONS {
    AO_NONE		= 0,
    AO_DESIGNMODE	= 0x1,
    AO_NOERRORUI	= 0x2,
    AO_NOSPLASHSCREEN	= 0x4
    }


ifndef __IApplicationActivationManager_INTERFACE_DEFINED__
define __IApplicationActivationManager_INTERFACE_DEFINED__

DEFINE_IIDX(IApplicationActivationManager, "2e941141-7f97-4756-ba1d-9decde894a3d")

.comdef IApplicationActivationManager : public IUnknown

    ActivateApplication proc :LPCWSTR, :LPCWSTR, :ACTIVATEOPTIONS, :ptr DWORD
    ActivateForFile	proc :LPCWSTR, :ptr IShellItemArray, :LPCWSTR, :ptr DWORD
    ActivateForProtocol proc :LPCWSTR, :ptr IShellItemArray, :ptr DWORD

    .ends

endif
endif

ifndef __ShellObjects_LIBRARY_DEFINED__
define __ShellObjects_LIBRARY_DEFINED__

externdef LIBID_ShellObjects:IID

define SID_PublishingWizard <CSID_PublishingWizard>

DEFINE_GUIDS(CLSID_DesktopWallpaper, "C2CF3110-460E-4fc1-B9D0-8A1C0C9CC4BD")
DEFINE_GUIDS(CLSID_ShellDesktop, "00021400-0000-0000-C000-000000000046")
DEFINE_GUIDS(CLSID_ShellFSFolder, "F3364BA0-65B9-11CE-A9BA-00AA004AE837")
DEFINE_GUIDS(CLSID_NetworkPlaces, "208D2C60-3AEA-1069-A2D7-08002B30309D")
DEFINE_GUIDS(CLSID_ShellLink, "00021401-0000-0000-C000-000000000046")
DEFINE_GUIDS(CLSID_QueryCancelAutoPlay, "331F1768-05A9-4ddd-B86E-DAE34DDC998A")
DEFINE_GUIDS(CLSID_DriveSizeCategorizer, "94357B53-CA29-4b78-83AE-E8FE7409134F")
DEFINE_GUIDS(CLSID_DriveTypeCategorizer, "B0A8F3CF-4333-4bab-8873-1CCB1CADA48B")
DEFINE_GUIDS(CLSID_FreeSpaceCategorizer, "B5607793-24AC-44c7-82E2-831726AA6CB7")
DEFINE_GUIDS(CLSID_TimeCategorizer, "3bb4118f-ddfd-4d30-a348-9fb5d6bf1afe")
DEFINE_GUIDS(CLSID_SizeCategorizer, "55d7b852-f6d1-42f2-aa75-8728a1b2d264")
DEFINE_GUIDS(CLSID_AlphabeticalCategorizer, "3c2654c6-7372-4f6b-b310-55d6128f49d2")
DEFINE_GUIDS(CLSID_MergedCategorizer, "8e827c11-33e7-4bc1-b242-8cd9a1c2b304")
DEFINE_GUIDS(CLSID_ImageProperties, "7ab770c7-0e23-4d7a-8aa2-19bfad479829")
DEFINE_GUIDS(CLSID_PropertiesUI, "d912f8cf-0396-4915-884e-fb425d32943b")
DEFINE_GUIDS(CLSID_UserNotification, "0010890e-8789-413c-adbc-48f5b511b3af")
DEFINE_GUIDS(CLSID_CDBurn, "fbeb8a05-beee-4442-804e-409d6c4515e9")
DEFINE_GUIDS(CLSID_TaskbarList, "56FDF344-FD6D-11d0-958A-006097C9A090")
DEFINE_GUIDS(CLSID_StartMenuPin, "a2a9545d-a0c2-42b4-9708-a0b2badd77c8")
DEFINE_GUIDS(CLSID_WebWizardHost, "c827f149-55c1-4d28-935e-57e47caed973")
DEFINE_GUIDS(CLSID_PublishDropTarget, "CC6EEFFB-43F6-46c5-9619-51D571967F7D")
DEFINE_GUIDS(CLSID_PublishingWizard, "6b33163c-76a5-4b6c-bf21-45de9cd503a1")
DEFINE_GUIDS(CLSID_InternetPrintOrdering, "add36aa8-751a-4579-a266-d66f5202ccbb")
DEFINE_GUIDS(CLSID_FolderViewHost, "20b1cb23-6968-4eb9-b7d4-a66d00d07cee")
DEFINE_GUIDS(CLSID_ExplorerBrowser, "71f96385-ddd6-48d3-a0c1-ae06e8b055fb")
DEFINE_GUIDS(CLSID_ImageRecompress, "6e33091c-d2f8-4740-b55e-2e11d1477a2c")
DEFINE_GUIDS(CLSID_TrayBandSiteService, "F60AD0A0-E5E1-45cb-B51A-E15B9F8B2934")
DEFINE_GUIDS(CLSID_TrayDeskBand, "E6442437-6C68-4f52-94DD-2CFED267EFB9")
DEFINE_GUIDS(CLSID_AttachmentServices, "4125dd96-e03a-4103-8f70-e0597d803b9c")
DEFINE_GUIDS(CLSID_DocPropShellExtension, "883373C3-BF89-11D1-BE35-080036B11A03")
DEFINE_GUIDS(CLSID_ShellItem, "9ac9fbe1-e0a2-4ad6-b4ee-e212013ea917")
DEFINE_GUIDS(CLSID_NamespaceWalker, "72eb61e0-8672-4303-9175-f2e4c68b2e7c")
DEFINE_GUIDS(CLSID_FileOperation, "3ad05575-8857-4850-9277-11b85bdb8e09")
DEFINE_GUIDS(CLSID_FileOpenDialog, "DC1C5A9C-E88A-4dde-A5A1-60F82A20AEF7")
DEFINE_GUIDS(CLSID_FileSaveDialog, "C0B4E2F3-BA21-4773-8DBA-335EC946EB8B")
DEFINE_GUIDS(CLSID_KnownFolderManager, "4df0c730-df9d-4ae3-9153-aa6b82e9795a")
DEFINE_GUIDS(CLSID_FSCopyHandler, "D197380A-0A79-4dc8-A033-ED882C2FA14B")
DEFINE_GUIDS(CLSID_SharingConfigurationManager, "49F371E1-8C5C-4d9c-9A3B-54A6827F513C")
DEFINE_GUIDS(CLSID_PreviousVersions, "596AB062-B4D2-4215-9F74-E9109B0A8153")
DEFINE_GUIDS(CLSID_NetworkConnections, "7007ACC7-3202-11D1-AAD2-00805FC1270E")
DEFINE_GUIDS(CLSID_NamespaceTreeControl, "AE054212-3535-4430-83ED-D501AA6680E6")
DEFINE_GUIDS(CLSID_IENamespaceTreeControl, "ACE52D03-E5CD-4b20-82FF-E71B11BEAE1D")
DEFINE_GUIDS(CLSID_ScheduledTasks, "D6277990-4C6A-11CF-8D87-00AA0060F5BF")
DEFINE_GUIDS(CLSID_ApplicationAssociationRegistration, "591209c7-767b-42b2-9fba-44ee4615f2c7")
DEFINE_GUIDS(CLSID_ApplicationAssociationRegistrationUI, "1968106d-f3b5-44cf-890e-116fcb9ecef1")
DEFINE_GUIDS(CLSID_SearchFolderItemFactory, "14010e02-bbbd-41f0-88e3-eda371216584")
DEFINE_GUIDS(CLSID_OpenControlPanel, "06622D85-6856-4460-8DE1-A81921B41C4B")
DEFINE_GUIDS(CLSID_MailRecipient, "9E56BE60-C50F-11CF-9A2C-00A0C90A90CE")
DEFINE_GUIDS(CLSID_NetworkExplorerFolder, "F02C1A0D-BE21-4350-88B0-7367FC96EF3C")
DEFINE_GUIDS(CLSID_DestinationList, "77f10cf0-3db5-4966-b520-b7c54fd35ed6")
DEFINE_GUIDS(CLSID_ApplicationDestinations, "86c14003-4d6b-4ef3-a7b4-0506663b2e68")
DEFINE_GUIDS(CLSID_ApplicationDocumentLists, "86bec222-30f2-47e0-9f25-60d11cd75c28")
DEFINE_GUIDS(CLSID_HomeGroup, "DE77BA04-3C92-4d11-A1A5-42352A53E0E3")
DEFINE_GUIDS(CLSID_ShellLibrary, "d9b3211d-e57f-4426-aaef-30a806add397")
DEFINE_GUIDS(CLSID_AppStartupLink, "273eb5e7-88b0-4843-bfef-e2c81d43aae5")
DEFINE_GUIDS(CLSID_EnumerableObjectCollection, "2d3468c1-36a7-43b6-ac24-d3f02fd9607a")
DEFINE_GUIDS(CLSID_DesktopGadget, "924ccc1b-6562-4c85-8657-d177925222b6")
DEFINE_GUIDS(CLSID_AccessibilityDockingService, "29CE1D46-B481-4AA0-A08A-D3EBC8ACA402")
DEFINE_GUIDS(CLSID_FrameworkInputPane, "D5120AA3-46BA-44C5-822D-CA8092C1FC72")
DEFINE_GUIDS(CLSID_DefFolderMenu, "c63382be-7933-48d0-9ac8-85fb46be2fdd")
DEFINE_GUIDS(CLSID_AppVisibility, "7E5FE3D9-985F-4908-91F9-EE19F9FD1514")
DEFINE_GUIDS(CLSID_AppShellVerbHandler, "4ED3A719-CEA8-4BD9-910D-E252F997AFC2")
DEFINE_GUIDS(CLSID_ExecuteUnknown, "e44e9428-bdbc-4987-a099-40dc8fd255e7")
DEFINE_GUIDS(CLSID_PackageDebugSettings, "B1AEC16F-2383-4852-B0E9-8F0B1DC66B4D")
DEFINE_GUIDS(CLSID_SuspensionDependencyManager, "6B273FC5-61FD-4918-95A2-C3B5E9D7F581")
DEFINE_GUIDS(CLSID_ApplicationActivationManager, "45BA127D-10A8-46EA-8AB7-56EA9078943C")
DEFINE_GUIDS(CLSID_ApplicationDesignModeSettings, "958a6fb5-dcb2-4faf-aafd-7fb054ad1a3b")
DEFINE_GUIDS(CLSID_ExecuteFolder, "11dbb47c-a525-400b-9e80-a54615a090c0")

endif

if (NTDDI_VERSION GE NTDDI_VISTA)
;SHSTDAPI
SHGetTemporaryPropertyForItem proto WINAPI \
		   psi: ptr IShellItem,
	       propkey: REFPROPERTYKEY,
	      ppropvar: ptr PROPVARIANT

SHSetTemporaryPropertyForItem proto WINAPI \
		   psi: ptr IShellItem,
	       propkey: REFPROPERTYKEY,
	       propvar: REFPROPVARIANT

endif

if (NTDDI_VERSION GE NTDDI_WIN7)
if (_WIN32_IE GE _WIN32_IE_IE70)

.enum LIBRARYMANAGEDIALOGOPTIONS {
    LMD_DEFAULT,
    LMD_ALLOWUNINDEXABLENETWORKLOCATIONS
    }

SHShowManageLibraryUI proto WINAPI \
	    psiLibrary: ptr IShellItem,
	     hwndOwner: HWND,
	      pszTitle: LPCWSTR,
	pszInstruction: LPCWSTR,
	    lmdOptions: LIBRARYMANAGEDIALOGOPTIONS

SHResolveLibrary proto WINAPI \
	    psiLibrary: ptr IShellItem

SHCreateLibrary macro riid, ppv
    exitm<CoCreateInstance(addr CLSID_ShellLibrary, NULL, CLSCTX_INPROC_SERVER, riid, ppv)>
    endm

endif ; if (_WIN32_IE GE _WIN32_IE_IE70)
endif ; if (NTDDI_VERSION GE NTDDI_WIN7)



if (NTDDI_VERSION GE NTDDI_VISTA)

ifndef __IAssocHandlerInvoker_INTERFACE_DEFINED__
define __IAssocHandlerInvoker_INTERFACE_DEFINED__

DEFINE_IIDX(IAssocHandlerInvoker, "92218CAB-ECAA-4335-8133-807FD234C2EE")

.comdef IAssocHandlerInvoker : public IUnknown

    SupportsSelection	proc
    _Invoke		proc

    .ends

endif

ifndef __IAssocHandler_INTERFACE_DEFINED__
define __IAssocHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IAssocHandler, "F04061AC-1659-4a3f-A954-775AA57FC083")

.comdef IAssocHandler : public IUnknown

    GetName		proc :ptr
    GetUIName		proc :ptr
    GetIconLocation	proc :ptr, :ptr
    IsRecommended	proc
    MakeDefault		proc :LPCWSTR
    _Invoke		proc :ptr
    CreateInvoker	proc :ptr, :ptr

    .ends

endif

ifndef __IEnumAssocHandlers_INTERFACE_DEFINED__
define __IEnumAssocHandlers_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumAssocHandlers, "973810ae-9599-4b88-9e4d-6ee98c9552da")

.comdef IEnumAssocHandlers : public IUnknown

    Next		proc :ULONG, :ptr, :ptr

    .ends

endif

.enum ASSOC_FILTER {
    ASSOC_FILTER_NONE,
    ASSOC_FILTER_RECOMMENDED
    }

;SHSTDAPI
SHAssocEnumHandlers proto WINAPI \
	      pszExtra: LPCWSTR,
	      afFilter: ASSOC_FILTER,
	 ppEnumHandler: ptr IEnumAssocHandlers

endif ;; NTDDI_VISTA

if (NTDDI_VERSION GE NTDDI_WIN7)
;SHSTDAPI
SHAssocEnumHandlersForProtocolByApplication proto WINAPI \
	      protocol: PCWSTR,
		  riid: REFIID,
	  enumHandlers: PVOID

endif

if (NTDDI_VERSION GE NTDDI_WIN8)

ifndef __IDataObjectProvider_INTERFACE_DEFINED__
__IDataObjectProvider_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IDataObjectProvider, "3D25F6D6-4B2A-433c-9184-7C33AD35D001")

.comdef IDataObjectProvider : public IUnknown

    GetDataObject	proc :ptr ptr IDataObject
    SetDataObject	proc :ptr IDataObject

    .ends

endif

ifndef __IDataTransferManagerInterop_INTERFACE_DEFINED__
define __IDataTransferManagerInterop_INTERFACE_DEFINED__

DEFINE_IIDX(IDataTransferManagerInterop, "3A3DCD6C-3EAB-43DC-BCDE-45671CE800C8")

.comdef IDataTransferManagerInterop : public IUnknown

    GetForWindow	proc :HWND, :REFIID, :ptr ptr
    ShowShareUIForWindow proc :HWND

    .ends

endif

endif ;; NTDDI_WIN8

if (NTDDI_VERSION GE NTDDI_WIN8)

ifndef __IFrameworkInputPaneHandler_INTERFACE_DEFINED__
define __IFrameworkInputPaneHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IFrameworkInputPaneHandler, "226C537B-1E76-4D9E-A760-33DB29922F18")

.comdef IFrameworkInputPaneHandler : public IUnknown

    Showing		proc :ptr RECT, :BOOL
    Hiding		proc :BOOL

    .ends

endif

ifndef __IFrameworkInputPane_INTERFACE_DEFINED__
define __IFrameworkInputPane_INTERFACE_DEFINED__

DEFINE_IIDX(IFrameworkInputPane, "5752238B-24F0-495A-82F1-2FD593056796")

.comdef IFrameworkInputPane : public IUnknown

    Advise		proc :ptr IUnknown, :ptr IFrameworkInputPaneHandler, :ptr DWORD
    AdviseWithHWND	proc :HWND, :ptr IFrameworkInputPaneHandler, :ptr DWORD
    Unadvise		proc :DWORD
    Location		proc :ptr RECT

    .ends

endif

ifndef PROP_CONTRACT_DELEGATE
PROP_CONTRACT_DELEGATE	equ <L"ContractDelegate">
endif

;; For applications that use modern APIs and use a child or owned window
;; that run on different threads this API must be used to indicate which
;; window is the current main window. Call this API when those windows change their state.

SetContractDelegateWindow macro hwndSource, hwndDelegate
    .if (hwndDelegate != NULL)
	SetPropW(hwndSource, PROP_CONTRACT_DELEGATE, hwndDelegate)
    .else
	RemovePropW(hwndSource, PROP_CONTRACT_DELEGATE)
    .endif
    retm<>
    endm

endif ;; NTDDI_WIN8

if (NTDDI_VERSION GE NTDDI_WIN8)

.enum UNDOCK_REASON {
    UR_RESOLUTION_CHANGE,
    UR_MONITOR_DISCONNECT
    }

ifndef __IAccessibilityDockingServiceCallback_INTERFACE_DEFINED__
define __IAccessibilityDockingServiceCallback_INTERFACE_DEFINED__

DEFINE_IIDX(IAccessibilityDockingServiceCallback, "157733FD-A592-42E5-B594-248468C5A81B")

.comdef IAccessibilityDockingServiceCallback : public IUnknown

    Undocked		proc :UNDOCK_REASON

    .ends

endif

ifndef __IAccessibilityDockingService_INTERFACE_DEFINED__
define __IAccessibilityDockingService_INTERFACE_DEFINED__

DEFINE_IIDX(IAccessibilityDockingService, "8849DC22-CEDF-4C95-998D-051419DD3F76")

.comdef IAccessibilityDockingService : public IUnknown

    GetAvailableSize	proc :HMONITOR, :ptr UINT, :ptr UINT
    DockWindow		proc :HWND, :HMONITOR, :UINT, :ptr IAccessibilityDockingServiceCallback
    UndockWindow	proc :HWND

    .ends

endif

.enum MONITOR_APP_VISIBILITY {
    MAV_UNKNOWN,
    MAV_NO_APP_VISIBLE,
    MAV_APP_VISIBLE
    }

ifndef __IAppVisibilityEvents_INTERFACE_DEFINED__
define __IAppVisibilityEvents_INTERFACE_DEFINED__

DEFINE_IIDX(IAppVisibilityEvents, "6584CE6B-7D82-49C2-89C9-C6BC02BA8C38")

.comdef IAppVisibilityEvents : public IUnknown

    AppVisibilityOnMonitorChanged proc :HMONITOR, :MONITOR_APP_VISIBILITY, :MONITOR_APP_VISIBILITY
    LauncherVisibilityChange proc :BOOL

    .ends

endif

ifndef __IAppVisibility_INTERFACE_DEFINED__
define __IAppVisibility_INTERFACE_DEFINED__

DEFINE_IIDX(IAppVisibility, "2246EA2D-CAEA-4444-A3C4-6DE827E44313")

.comdef IAppVisibility : public IUnknown

    GetAppVisibilityOnMonitor proc :HMONITOR, :ptr MONITOR_APP_VISIBILITY
    IsLauncherVisible	proc :ptr BOOL
    Advise		proc :ptr IAppVisibilityEvents, :ptr DWORD
    Unadvise		proc :DWORD

    .ends

endif

.enum PACKAGE_EXECUTION_STATE {
    PES_UNKNOWN,
    PES_RUNNING,
    PES_SUSPENDING,
    PES_SUSPENDED,
    PES_TERMINATED
    }

ifndef __IPackageExecutionStateChangeNotification_INTERFACE_DEFINED__
define __IPackageExecutionStateChangeNotification_INTERFACE_DEFINED__

DEFINE_IIDX(IPackageExecutionStateChangeNotification, "1BB12A62-2AD8-432B-8CCF-0C2C52AFCD5B")

.comdef IPackageExecutionStateChangeNotification : public IUnknown

    OnStateChanged	proc :LPCWSTR, :PACKAGE_EXECUTION_STATE

    .ends

endif

ifndef __IPackageDebugSettings_INTERFACE_DEFINED__
define __IPackageDebugSettings_INTERFACE_DEFINED__

DEFINE_IIDX(IPackageDebugSettings, "F27C3930-8029-4AD1-94E3-3DBA417810C1")

.comdef IPackageDebugSettings : public IUnknown

    EnableDebugging	proc :LPCWSTR, :LPCWSTR, :PZZWSTR
    DisableDebugging	proc :LPCWSTR
    Suspend		proc :LPCWSTR
    Resume		proc :LPCWSTR
    TerminateAllProcesses proc :LPCWSTR
    SetTargetSessionId	proc :ULONG
    EnumerateBackgroundTasks proc :LPCWSTR, :ptr, :ptr
    ActivateBackgroundTask proc :LPCGUID
    StartServicing	proc :LPCWSTR
    StopServicing	proc :LPCWSTR
    StartSessionRedirection proc :LPCWSTR, :ULONG
    StopSessionRedirection proc :LPCWSTR
    GetPackageExecutionState proc :LPCWSTR, :ptr
    RegisterForPackageStateChanges proc :LPCWSTR, :ptr, :ptr
    UnregisterForPackageStateChanges proc :DWORD

    .ends

endif

ifndef __ISuspensionDependencyManager_INTERFACE_DEFINED__
define __ISuspensionDependencyManager_INTERFACE_DEFINED__

DEFINE_IIDX(ISuspensionDependencyManager, "52B83A42-2543-416A-81D9-C0DE7969C8B3")

.comdef ISuspensionDependencyManager : public IUnknown

    RegisterAsChild	proc :HANDLE
    GroupChildWithParent proc :HANDLE
    UngroupChildFromParent proc :HANDLE

    .ends

endif

.enum AHE_TYPE {
    AHE_DESKTOP,
    AHE_IMMERSIVE
    }

ifndef __IExecuteCommandApplicationHostEnvironment_INTERFACE_DEFINED__
define __IExecuteCommandApplicationHostEnvironment_INTERFACE_DEFINED__

DEFINE_IIDX(IExecuteCommandApplicationHostEnvironment, "18B21AA9-E184-4FF0-9F5E-F882D03771B3")

.comdef IExecuteCommandApplicationHostEnvironment : public IUnknown

    GetValue		proc :ptr

    .ends

endif

.enum EC_HOST_UI_MODE {
    ECHUIM_DESKTOP,
    ECHUIM_IMMERSIVE = ( ECHUIM_DESKTOP + 1 ),
    ECHUIM_SYSTEM_LAUNCHER = ( ECHUIM_IMMERSIVE + 1 )
    }

ifndef __IExecuteCommandHost_INTERFACE_DEFINED__
define __IExecuteCommandHost_INTERFACE_DEFINED__

DEFINE_IIDX(IExecuteCommandHost, "4b6832a2-5f04-4c9d-b89d-727a15d103e7")

.comdef IExecuteCommandHost : public IUnknown

    GetUIMode		proc :ptr

    .ends

endif

SID_ExecuteCommandHost	equ <IID_IExecuteCommandHost>

.enum APPLICATION_VIEW_STATE {
    AVS_FULLSCREEN_LANDSCAPE,
    AVS_FILLED = ( AVS_FULLSCREEN_LANDSCAPE + 1 ),
    AVS_SNAPPED = ( AVS_FILLED + 1 ),
    AVS_FULLSCREEN_PORTRAIT = ( AVS_SNAPPED + 1 )
    }

.enum EDGE_GESTURE_KIND {
    EGK_TOUCH,
    EGK_KEYBOARD = ( EGK_TOUCH + 1 ),
    EGK_MOUSE = ( EGK_KEYBOARD + 1 )
    }

ifndef __IApplicationDesignModeSettings_INTERFACE_DEFINED__
define __IApplicationDesignModeSettings_INTERFACE_DEFINED__

DEFINE_IIDX(IApplicationDesignModeSettings, "2A3DEE9A-E31D-46D6-8508-BCC597DB3557")

.comdef IApplicationDesignModeSettings : public IUnknown

    SetNativeDisplaySize proc :SIZEL
    SetScaleFactor	proc :DEVICE_SCALE_FACTOR
    SetApplicationViewState proc :APPLICATION_VIEW_STATE
    ComputeApplicationSize proc :ptr
    IsApplicationViewStateSupported proc :APPLICATION_VIEW_STATE, :SIZEL, :DEVICE_SCALE_FACTOR, :ptr
    TriggerEdgeGesture	proc :EDGE_GESTURE_KIND

    .ends

endif

NATIVE_DISPLAY_ORIENTATION typedef SDWORD
NDO_LANDSCAPE		equ 0
NDO_PORTRAIT		equ ( NDO_LANDSCAPE + 1 )

APPLICATION_VIEW_ORIENTATION typedef SDWORD
AVO_LANDSCAPE		equ 0
AVO_PORTRAIT		equ ( AVO_LANDSCAPE + 1 )

ADJACENT_DISPLAY_EDGES	typedef SDWORD
ADE_NONE		equ 0
ADE_LEFT		equ 0x1
ADE_RIGHT		equ 0x2


if (NTDDI_VERSION GE NTDDI_WINBLUE)

APPLICATION_VIEW_MIN_WIDTH typedef SDWORD
AVMW_DEFAULT		equ 0
AVMW_320		equ 1
AVMW_500		equ 2

ifndef __IApplicationDesignModeSettings2_INTERFACE_DEFINED__
__IApplicationDesignModeSettings2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IApplicationDesignModeSettings2, "490514E1-675A-4D6E-A58D-E54901B4CA2F")

.comdef IApplicationDesignModeSettings2 : public IApplicationDesignModeSettings

    SetNativeDisplayOrientation proc :NATIVE_DISPLAY_ORIENTATION
    SetApplicationViewOrientation proc :APPLICATION_VIEW_ORIENTATION
    SetAdjacentDisplayEdges proc :ADJACENT_DISPLAY_EDGES
    SetIsOnLockScreen	proc :BOOL
    SetApplicationViewMinWidth proc :APPLICATION_VIEW_MIN_WIDTH
    GetApplicationSizeBounds proc :ptr, :ptr
    GetApplicationViewOrientation proc :SIZEL, :ptr

    .ends

endif

DEFINE_GUID(SID_URLExecutionContext, 0xFB5F8EBC, 0xBBB6, 0x4D10, 0xA4, 0x61, 0x77, 0x72, 0x91, 0xA0, 0x90, 0x30)
STR_TAB_REUSE_IDENTIFIER equ <L"Tab Reuse Identifier">
STR_REFERRER_IDENTIFIER equ <L"Referrer Identifier">

ifndef __ILaunchTargetMonitor_INTERFACE_DEFINED__
define __ILaunchTargetMonitor_INTERFACE_DEFINED__

DEFINE_IIDX(ILaunchTargetMonitor,"266FBC7E-490D-46ED-A96B-2274DB252003")

.comdef ILaunchTargetMonitor : public IUnknown

    GetMonitor		proc :ptr

    .ends

endif

DEFINE_GUID(SID_LaunchTargetMonitor, 0x8d547fa1, 0xcc45, 0x40c8, 0xb7, 0xc1, 0xd4, 0x8c, 0x18, 0x3f, 0x13, 0xf3);

.enum APPLICATION_VIEW_SIZE_PREFERENCE {
    AVSP_DEFAULT,
    AVSP_USE_LESS,
    AVSP_USE_HALF,
    AVSP_USE_MORE,
    AVSP_USE_MINIMUM,
    AVSP_USE_NONE
    }

ifndef __ILaunchSourceViewSizePreference_INTERFACE_DEFINED__
define __ILaunchSourceViewSizePreference_INTERFACE_DEFINED__

DEFINE_IIDX(ILaunchSourceViewSizePreference, "E5AA01F7-1FB8-4830-8720-4E6734CBD5F3")

.comdef ILaunchSourceViewSizePreference : public IUnknown

    GetSourceViewToPosition proc :ptr
    GetSourceViewSizePreference proc :ptr

    .ends

endif

DEFINE_GUID(SID_LaunchSourceViewSizePreference, 0x80605492, 0x67d9, 0x414f, 0xaf, 0x89, 0xa1, 0xcd, 0xf1, 0x24, 0x2b, 0xc1);

ifndef __ILaunchTargetViewSizePreference_INTERFACE_DEFINED__
define __ILaunchTargetViewSizePreference_INTERFACE_DEFINED__

DEFINE_IIDX(ILaunchTargetViewSizePreference, "2F0666C6-12F7-4360-B511-A394A0553725")

.comdef ILaunchTargetViewSizePreference : public IUnknown

    GetTargetViewSizePreference proc :ptr

    .ends

endif

DEFINE_GUID(SID_LaunchTargetViewSizePreference, 0x26db2472, 0xb7b7, 0x406b, 0x97, 0x2, 0x73, 0xa, 0x4e, 0x20, 0xd3, 0xbf);

ifndef __ILaunchSourceAppUserModelId_INTERFACE_DEFINED__
define __ILaunchSourceAppUserModelId_INTERFACE_DEFINED__

DEFINE_IIDX(ILaunchSourceAppUserModelId, "989191AC-28FF-4CF0-9584-E0D078BC2396")

.comdef ILaunchSourceAppUserModelId : public IUnknown

    GetAppUserModelId	proc :ptr

    .ends

endif

DEFINE_GUID(SID_LaunchSourceAppUserModelId, 0x2ce78010, 0x74db, 0x48bc, 0x9c, 0x6a, 0x10, 0xf3, 0x72, 0x49, 0x57, 0x23);

endif ;; NTDDI_WINBLUE


ifndef __IInitializeWithWindow_INTERFACE_DEFINED__
define __IInitializeWithWindow_INTERFACE_DEFINED__

DEFINE_IIDX(IInitializeWithWindow, "3E68D4BD-7135-4D10-8018-9FB6D9F33FA1")

.comdef IInitializeWithWindow : public IUnknown

    Initialize		proc :HWND

    .ends

endif

ifndef __IHandlerInfo_INTERFACE_DEFINED__
__IHandlerInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IHandlerInfo, "997706ef-f880-453b-8118-39e1a2d2655a")

.comdef IHandlerInfo : public IUnknown

    GetApplicationDisplayName proc :ptr
    GetApplicationPublisher proc :ptr
    GetApplicationIconReference proc :ptr

    .ends

endif

ifndef __IHandlerActivationHost_INTERFACE_DEFINED__
__IHandlerActivationHost_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IHandlerActivationHost, "35094a87-8bb1-4237-96c6-c417eebdb078")

.comdef IHandlerActivationHost : public IUnknown

    BeforeCoCreateInstance proc :REFCLSID, :ptr, :ptr
    BeforeCreateProcess proc :LPCWSTR, :LPCWSTR, :ptr

    .ends

endif

SID_SHandlerActivationHost equ <IID_IHandlerActivationHost>
DEFINE_GUID(SID_ShellExecuteNamedPropertyStore, 0xeb84ada2, 0x00ff, 0x4992, 0x83, 0x24, 0xed, 0x5c, 0xe0, 0x61, 0xcb, 0x29);

endif ;; NTDDI_WIN8

if (NTDDI_VERSION GE NTDDI_WINBLUE)

.enum FLYOUT_PLACEMENT {
    FP_DEFAULT,
    FP_ABOVE = ( FP_DEFAULT + 1 ),
    FP_BELOW = ( FP_ABOVE + 1 ),
    FP_LEFT = ( FP_BELOW + 1 ),
    FP_RIGHT = ( FP_LEFT + 1 )
    }

ifndef __IContactManagerInterop_INTERFACE_DEFINED__
__IContactManagerInterop_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IContactManagerInterop, "99eacba7-e073-43b6-a896-55afe48a0833")

.comdef IContactManagerInterop : public IUnknown

    ShowContactCardForWindow proc :HWND, :ptr, :ptr, :FLYOUT_PLACEMENT

    .ends

endif

endif ;; NTDDI_WINBLUE

;; Additional Prototypes for ALL interfaces

BSTR_UserSize		proto WINAPI :ptr DWORD, :DWORD, :ptr BSTR
BSTR_UserMarshal	proto WINAPI :ptr DWORD, :LPSTR, :ptr BSTR
BSTR_UserUnmarshal	proto WINAPI :ptr DWORD, :LPSTR, :ptr BSTR
BSTR_UserFree		proto WINAPI :ptr DWORD, :ptr BSTR
HACCEL_UserSize		proto WINAPI :ptr DWORD, :DWORD, :ptr HACCEL
HACCEL_UserMarshal	proto WINAPI :ptr DWORD, :LPSTR, :ptr HACCEL
HACCEL_UserUnmarshal	proto WINAPI :ptr DWORD, :LPSTR, :ptr HACCEL
HACCEL_UserFree		proto WINAPI :ptr DWORD, :ptr HACCEL
HBITMAP_UserSize	proto WINAPI :ptr DWORD, :DWORD, :ptr HBITMAP
HBITMAP_UserMarshal	proto WINAPI :ptr DWORD, :LPSTR, :ptr HBITMAP
HBITMAP_UserUnmarshal	proto WINAPI :ptr DWORD, :LPSTR, :ptr HBITMAP
HBITMAP_UserFree	proto WINAPI :ptr DWORD, :ptr HBITMAP
HGLOBAL_UserSize	proto WINAPI :ptr DWORD, :DWORD, :ptr HGLOBAL
HGLOBAL_UserMarshal	proto WINAPI :ptr DWORD, :LPSTR, :ptr HGLOBAL
HGLOBAL_UserUnmarshal	proto WINAPI :ptr DWORD, :LPSTR, :ptr HGLOBAL
HGLOBAL_UserFree	proto WINAPI :ptr DWORD, :ptr HGLOBAL
HICON_UserSize		proto WINAPI :ptr DWORD, :DWORD, :ptr HICON
HICON_UserMarshal	proto WINAPI :ptr DWORD, :LPSTR, :ptr HICON
HICON_UserUnmarshal	proto WINAPI :ptr DWORD, :LPSTR, :ptr HICON
HICON_UserFree		proto WINAPI :ptr DWORD, :ptr HICON
HMENU_UserSize		proto WINAPI :ptr DWORD, :DWORD, :ptr HMENU
HMENU_UserMarshal	proto WINAPI :ptr DWORD, :LPSTR, :ptr HMENU
HMENU_UserUnmarshal	proto WINAPI :ptr DWORD, :LPSTR, :ptr HMENU
HMENU_UserFree		proto WINAPI :ptr DWORD, :ptr HMENU
HWND_UserSize		proto WINAPI :ptr DWORD, :DWORD, :ptr HWND
HWND_UserMarshal	proto WINAPI :ptr DWORD, :LPSTR, :ptr HWND
HWND_UserUnmarshal	proto WINAPI :ptr DWORD, :LPSTR, :ptr HWND
HWND_UserFree		proto WINAPI :ptr DWORD, :ptr HWND
LPSAFEARRAY_UserSize	proto WINAPI :ptr DWORD, :DWORD, :ptr LPSAFEARRAY
LPSAFEARRAY_UserMarshal proto WINAPI :ptr DWORD, :LPSTR, :ptr LPSAFEARRAY
LPSAFEARRAY_UserUnmarshal proto WINAPI :ptr DWORD, :LPSTR, :ptr LPSAFEARRAY
LPSAFEARRAY_UserFree	proto WINAPI :ptr DWORD, :ptr LPSAFEARRAY
PCIDLIST_ABSOLUTE_UserSize proto WINAPI :ptr DWORD, :DWORD, :ptr PCIDLIST_ABSOLUTE
PCIDLIST_ABSOLUTE_UserMarshal proto WINAPI :ptr DWORD, :LPSTR, :ptr PCIDLIST_ABSOLUTE
PCIDLIST_ABSOLUTE_UserUnmarshal proto WINAPI :ptr DWORD, :LPSTR, :ptr PCIDLIST_ABSOLUTE
PCIDLIST_ABSOLUTE_UserFree proto WINAPI :ptr DWORD, :ptr PCIDLIST_ABSOLUTE
PCUIDLIST_RELATIVE_UserSize proto WINAPI :ptr DWORD, :DWORD, :ptr PCUIDLIST_RELATIVE
PCUIDLIST_RELATIVE_UserMarshal proto WINAPI :ptr DWORD, :LPSTR, :ptr PCUIDLIST_RELATIVE
PCUIDLIST_RELATIVE_UserUnmarshal proto WINAPI :ptr DWORD, :LPSTR, :ptr PCUIDLIST_RELATIVE
PCUIDLIST_RELATIVE_UserFree proto WINAPI :ptr DWORD, :ptr PCUIDLIST_RELATIVE
PCUITEMID_CHILD_UserSize proto WINAPI :ptr DWORD, :DWORD, :ptr PCUITEMID_CHILD
PCUITEMID_CHILD_UserMarshal proto WINAPI :ptr DWORD, :LPSTR, :ptr PCUITEMID_CHILD
PCUITEMID_CHILD_UserUnmarshal proto WINAPI :ptr DWORD, :LPSTR, :ptr PCUITEMID_CHILD
PCUITEMID_CHILD_UserFree proto WINAPI :ptr DWORD, :ptr PCUITEMID_CHILD
PIDLIST_ABSOLUTE_UserSize proto WINAPI :ptr DWORD, :DWORD, :ptr PIDLIST_ABSOLUTE
PIDLIST_ABSOLUTE_UserMarshal proto WINAPI :ptr DWORD, :LPSTR, :ptr PIDLIST_ABSOLUTE
PIDLIST_ABSOLUTE_UserUnmarshal proto WINAPI :ptr DWORD, :LPSTR, :ptr PIDLIST_ABSOLUTE
PIDLIST_ABSOLUTE_UserFree proto WINAPI :ptr DWORD, :ptr PIDLIST_ABSOLUTE
PIDLIST_RELATIVE_UserSize proto WINAPI :ptr DWORD, :DWORD, :ptr PIDLIST_RELATIVE
PIDLIST_RELATIVE_UserMarshal proto WINAPI :ptr DWORD, :LPSTR, :ptr PIDLIST_RELATIVE
PIDLIST_RELATIVE_UserUnmarshal proto WINAPI :ptr DWORD, :LPSTR, :ptr PIDLIST_RELATIVE
PIDLIST_RELATIVE_UserFree proto WINAPI :ptr DWORD, :ptr PIDLIST_RELATIVE
PITEMID_CHILD_UserSize	proto WINAPI :ptr DWORD, :DWORD, :ptr PITEMID_CHILD
PITEMID_CHILD_UserMarshal proto WINAPI :ptr DWORD, :LPSTR, :ptr PITEMID_CHILD
PITEMID_CHILD_UserUnmarshal proto WINAPI :ptr DWORD, :LPSTR, :ptr PITEMID_CHILD
PITEMID_CHILD_UserFree	proto WINAPI :ptr DWORD, :ptr PITEMID_CHILD
VARIANT_UserSize	proto WINAPI :ptr DWORD, :DWORD, :ptr VARIANT
VARIANT_UserMarshal	proto WINAPI :ptr DWORD, :LPSTR, :ptr VARIANT
VARIANT_UserUnmarshal	proto WINAPI :ptr DWORD, :LPSTR, :ptr VARIANT
VARIANT_UserFree	proto WINAPI :ptr DWORD, :ptr VARIANT
BSTR_UserSize64		proto WINAPI :ptr DWORD, :DWORD, :ptr BSTR
BSTR_UserMarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr BSTR
BSTR_UserUnmarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr BSTR
BSTR_UserFree64		proto WINAPI :ptr DWORD, :ptr BSTR
HACCEL_UserSize64	proto WINAPI :ptr DWORD, :DWORD, :ptr HACCEL
HACCEL_UserMarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr HACCEL
HACCEL_UserUnmarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr HACCEL
HACCEL_UserFree64	proto WINAPI :ptr DWORD, :ptr HACCEL
HBITMAP_UserSize64	proto WINAPI :ptr DWORD, :DWORD, :ptr HBITMAP
HBITMAP_UserMarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr HBITMAP
HBITMAP_UserUnmarshal64 proto WINAPI :ptr DWORD, :LPSTR, :ptr HBITMAP
HBITMAP_UserFree64	proto WINAPI :ptr DWORD, :ptr HBITMAP
HGLOBAL_UserSize64	proto WINAPI :ptr DWORD, :DWORD, :ptr HGLOBAL
HGLOBAL_UserMarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr HGLOBAL
HGLOBAL_UserUnmarshal64 proto WINAPI :ptr DWORD, :LPSTR, :ptr HGLOBAL
HGLOBAL_UserFree64	proto WINAPI :ptr DWORD, :ptr HGLOBAL
HICON_UserSize64	proto WINAPI :ptr DWORD, :DWORD, :ptr HICON
HICON_UserMarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr HICON
HICON_UserUnmarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr HICON
HICON_UserFree64	proto WINAPI :ptr DWORD, :ptr HICON
HMENU_UserSize64	proto WINAPI :ptr DWORD, :DWORD, :ptr HMENU
HMENU_UserMarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr HMENU
HMENU_UserUnmarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr HMENU
HMENU_UserFree64	proto WINAPI :ptr DWORD, :ptr HMENU
HWND_UserSize64		proto WINAPI :ptr DWORD, :DWORD, :ptr HWND
HWND_UserMarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr HWND
HWND_UserUnmarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr HWND
HWND_UserFree64		proto WINAPI :ptr DWORD, :ptr HWND

LPSAFEARRAY_UserSize64		proto WINAPI :ptr DWORD, :DWORD, :ptr LPSAFEARRAY
LPSAFEARRAY_UserMarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr LPSAFEARRAY
LPSAFEARRAY_UserUnmarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr LPSAFEARRAY
LPSAFEARRAY_UserFree64		proto WINAPI :ptr DWORD, :ptr LPSAFEARRAY
PCIDLIST_ABSOLUTE_UserSize64	proto WINAPI :ptr DWORD, :DWORD, :ptr PCIDLIST_ABSOLUTE
PCIDLIST_ABSOLUTE_UserMarshal64 proto WINAPI :ptr DWORD, :LPSTR, :ptr PCIDLIST_ABSOLUTE
PCIDLIST_ABSOLUTE_UserUnmarshal64 proto WINAPI :ptr DWORD, :LPSTR, :ptr PCIDLIST_ABSOLUTE
PCIDLIST_ABSOLUTE_UserFree64	proto WINAPI :ptr DWORD, :ptr PCIDLIST_ABSOLUTE
PCUIDLIST_RELATIVE_UserSize64	proto WINAPI :ptr DWORD, :DWORD, :ptr PCUIDLIST_RELATIVE
PCUIDLIST_RELATIVE_UserMarshal64 proto WINAPI :ptr DWORD, :LPSTR, :ptr PCUIDLIST_RELATIVE
PCUIDLIST_RELATIVE_UserUnmarshal64 proto WINAPI :ptr DWORD, :LPSTR, :ptr PCUIDLIST_RELATIVE
PCUIDLIST_RELATIVE_UserFree64	proto WINAPI :ptr DWORD, :ptr PCUIDLIST_RELATIVE
PCUITEMID_CHILD_UserSize64	proto WINAPI :ptr DWORD, :DWORD, :ptr PCUITEMID_CHILD
PCUITEMID_CHILD_UserMarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr PCUITEMID_CHILD
PCUITEMID_CHILD_UserUnmarshal64 proto WINAPI :ptr DWORD, :LPSTR, :ptr PCUITEMID_CHILD
PCUITEMID_CHILD_UserFree64	proto WINAPI :ptr DWORD, :ptr PCUITEMID_CHILD
PIDLIST_ABSOLUTE_UserSize64	proto WINAPI :ptr DWORD, :DWORD, :ptr PIDLIST_ABSOLUTE
PIDLIST_ABSOLUTE_UserMarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr PIDLIST_ABSOLUTE
PIDLIST_ABSOLUTE_UserUnmarshal64 proto WINAPI :ptr DWORD, :LPSTR, :ptr PIDLIST_ABSOLUTE
PIDLIST_ABSOLUTE_UserFree64	proto WINAPI :ptr DWORD, :ptr PIDLIST_ABSOLUTE
PIDLIST_RELATIVE_UserSize64	proto WINAPI :ptr DWORD, :DWORD, :ptr PIDLIST_RELATIVE
PIDLIST_RELATIVE_UserMarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr PIDLIST_RELATIVE
PIDLIST_RELATIVE_UserUnmarshal64 proto WINAPI :ptr DWORD, :LPSTR, :ptr PIDLIST_RELATIVE
PIDLIST_RELATIVE_UserFree64	proto WINAPI :ptr DWORD, :ptr PIDLIST_RELATIVE
PITEMID_CHILD_UserSize64	proto WINAPI :ptr DWORD, :DWORD, :ptr PITEMID_CHILD
PITEMID_CHILD_UserMarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr PITEMID_CHILD
PITEMID_CHILD_UserUnmarshal64	proto WINAPI :ptr DWORD, :LPSTR, :ptr PITEMID_CHILD
PITEMID_CHILD_UserFree64	proto WINAPI :ptr DWORD, :ptr PITEMID_CHILD
VARIANT_UserSize64		proto WINAPI :ptr DWORD, :DWORD, :ptr VARIANT
VARIANT_UserMarshal64		proto WINAPI :ptr DWORD, :LPSTR, :ptr VARIANT
VARIANT_UserUnmarshal64		proto WINAPI :ptr DWORD, :LPSTR, :ptr VARIANT
VARIANT_UserFree64		proto WINAPI :ptr DWORD, :ptr VARIANT

endif
