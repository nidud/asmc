ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __windows2Estorage2Efileproperties_h__
define __windows2Estorage2Efileproperties_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.Streams.inc
include windows.foundation.collections.inc

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CBasicProperties_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CBasicProperties_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CBasicProperties, "c8659aae-4926-52ad-8f60-d89fe5a8df5f")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CBasicProperties : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CBasicProperties_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CBasicProperties_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CFileProperties__CBasicProperties, "5186131a-4467-504b-977a-0785a8230485")

.comdef __FIAsyncOperation_1_Windows__CStorage__CFileProperties__CBasicProperties : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CDocumentProperties_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CDocumentProperties_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CDocumentProperties, "4452ed4c-642b-501b-9617-7d68b4ac3c66")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CDocumentProperties : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CDocumentProperties_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CDocumentProperties_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CFileProperties__CDocumentProperties, "6c86e97c-5699-5700-8d35-d350ad3e4df2")

.comdef __FIAsyncOperation_1_Windows__CStorage__CFileProperties__CDocumentProperties : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CImageProperties_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CImageProperties_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CImageProperties, "c63729bc-e4c3-564c-b137-2cb4f5966a83")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CImageProperties : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CImageProperties_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CImageProperties_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CFileProperties__CImageProperties, "fcd07511-e7f8-5bda-8c04-795a639dae8f")

.comdef __FIAsyncOperation_1_Windows__CStorage__CFileProperties__CImageProperties : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CMusicProperties_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CMusicProperties_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CMusicProperties, "d84e1312-d661-5b7f-9566-7421bdedc1ea")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CMusicProperties : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CMusicProperties_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CMusicProperties_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CFileProperties__CMusicProperties, "0d023b76-20a7-56f3-84ab-ce31e6544b71")

.comdef __FIAsyncOperation_1_Windows__CStorage__CFileProperties__CMusicProperties : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CStorageItemThumbnail_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CStorageItemThumbnail_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CStorageItemThumbnail, "6d0036f2-a8a8-505d-b042-d087dc1fc1b7")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CStorageItemThumbnail : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CStorageItemThumbnail_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CStorageItemThumbnail_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CFileProperties__CStorageItemThumbnail, "11c7cc5e-c04e-50e7-a65e-6f6903690c16")

.comdef __FIAsyncOperation_1_Windows__CStorage__CFileProperties__CStorageItemThumbnail : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CVideoProperties_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CVideoProperties_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CVideoProperties, "43401d34-61ab-5cf2-921f-55b616631d1d")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CVideoProperties : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CVideoProperties_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CVideoProperties_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CFileProperties__CVideoProperties, "447d4590-d3f9-58bf-ac58-6f9a50839efe")

.comdef __FIAsyncOperation_1_Windows__CStorage__CFileProperties__CVideoProperties : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Storage
.namespace FileProperties

.enum PropertyPrefetchOptions {
    PropertyPrefetchOptions_None	= 0,
    PropertyPrefetchOptions_MusicProperties	= 0x1,
    PropertyPrefetchOptions_VideoProperties	= 0x2,
    PropertyPrefetchOptions_ImageProperties	= 0x4,
    PropertyPrefetchOptions_DocumentProperties	= 0x8,
    PropertyPrefetchOptions_BasicProperties	= 0x10
    }

.enum ThumbnailType {
    ThumbnailType_Image,
    ThumbnailType_Icon
    }

.enum ThumbnailMode {
    ThumbnailMode_PicturesView,
    ThumbnailMode_VideosView,
    ThumbnailMode_MusicView,
    ThumbnailMode_DocumentsView,
    ThumbnailMode_ListView,
    ThumbnailMode_SingleItem
    }

.enum ThumbnailOptions {
    ThumbnailOptions_None	= 0,
    ThumbnailOptions_ReturnOnlyIfCached = 0x1,
    ThumbnailOptions_ResizeThumbnail	= 0x2,
    ThumbnailOptions_UseCurrentScale	= 0x4
    }

.enum PhotoOrientation {
    PhotoOrientation_Unspecified,
    PhotoOrientation_Normal,
    PhotoOrientation_FlipHorizontal,
    PhotoOrientation_Rotate180,
    PhotoOrientation_FlipVertical,
    PhotoOrientation_Transpose,
    PhotoOrientation_Rotate270,
    PhotoOrientation_Transverse,
    PhotoOrientation_Rotate90
    }

.enum VideoOrientation {
    VideoOrientation_Normal	= 0,
    VideoOrientation_Rotate90	= 90,
    VideoOrientation_Rotate180	= 180,
    VideoOrientation_Rotate270	= 270
    }


ifndef ____x_ABI_CWindows_CStorage_CFileProperties_CIThumbnailProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CFileProperties_CIThumbnailProperties_INTERFACE_DEFINED__

DEFINE_IIDX(IThumbnailProperties, "693DD42F-DBE7-49B5-B3B3-2893AC5D3423")

.comdef IThumbnailProperties : public IInspectable

    get_OriginalWidth	proc :ptr
    get_OriginalHeight	proc :ptr
    get_ReturnedSmallerCachedSize proc :ptr
    get_Type		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CFileProperties_CIStorageItemExtraProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CFileProperties_CIStorageItemExtraProperties_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageItemExtraProperties, "C54361B2-54CD-432B-BDBC-4B19C4B470D7")

.comdef IStorageItemExtraProperties : public IInspectable

    RetrievePropertiesAsync proc :ptr, :ptr
    SavePropertiesAsync proc :ptr, :ptr
    SavePropertiesAsyncOverloadDefault proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CFileProperties_CIStorageItemContentProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CFileProperties_CIStorageItemContentProperties_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageItemContentProperties, "05294BAD-BC38-48BF-85D7-770E0E2AE0BA")

.comdef IStorageItemContentProperties : public IInspectable

    GetMusicPropertiesAsync proc :ptr
    GetVideoPropertiesAsync proc :ptr
    GetImagePropertiesAsync proc :ptr
    GetDocumentPropertiesAsync proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CFileProperties_CIMusicProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CFileProperties_CIMusicProperties_INTERFACE_DEFINED__

DEFINE_IIDX(IMusicProperties, "BC8AAB62-66EC-419A-BC5D-CA65A4CB46DA")

.comdef IMusicProperties : public IInspectable

    get_Album		proc :ptr
    put_Album		proc :HSTRING
    get_Artist		proc :ptr
    put_Artist		proc :HSTRING
    get_Genre		proc :ptr
    get_TrackNumber	proc :ptr
    put_TrackNumber	proc :UINT32
    get_Title		proc :ptr
    put_Title		proc :HSTRING
    get_Rating		proc :ptr
    put_Rating		proc :UINT32
    get_Duration	proc :ptr
    get_Bitrate		proc :ptr
    get_AlbumArtist	proc :ptr
    put_AlbumArtist	proc :HSTRING
    get_Composers	proc :ptr
    get_Conductors	proc :ptr
    get_Subtitle	proc :ptr
    put_Subtitle	proc :HSTRING
    get_Producers	proc :ptr
    get_Publisher	proc :ptr
    put_Publisher	proc :HSTRING
    get_Writers		proc :ptr
    get_Year		proc :ptr
    put_Year		proc :UINT32
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CFileProperties_CIImageProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CFileProperties_CIImageProperties_INTERFACE_DEFINED__

DEFINE_IIDX(IImageProperties, "523C9424-FCFF-4275-AFEE-ECDB9AB47973")

.comdef IImageProperties : public IInspectable

    get_Rating		proc :ptr
    put_Rating		proc :UINT32
    get_Keywords	proc :ptr
    get_DateTaken	proc :ptr
    put_DateTaken	proc :ptr
    get_Width		proc :ptr
    get_Height		proc :ptr
    get_Title		proc :ptr
    put_Title		proc :HSTRING
    get_Latitude	proc :ptr
    get_Longitude	proc :ptr
    get_CameraManufacturer proc :ptr
    put_CameraManufacturer proc :HSTRING
    get_CameraModel	proc :ptr
    put_CameraModel	proc :HSTRING
    get_Orientation	proc :ptr
    get_PeopleNames	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CFileProperties_CIVideoProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CFileProperties_CIVideoProperties_INTERFACE_DEFINED__

DEFINE_IIDX(IVideoProperties, "719AE507-68DE-4DB8-97DE-49998C059F2F")

.comdef IVideoProperties : public IInspectable

    get_Rating		proc :ptr
    put_Rating		proc :UINT32
    get_Keywords	proc :ptr
    get_Width		proc :ptr
    get_Height		proc :ptr
    get_Duration	proc :ptr
    get_Latitude	proc :ptr
    get_Longitude	proc :ptr
    get_Title		proc :ptr
    put_Title		proc :HSTRING
    get_Subtitle	proc :ptr
    put_Subtitle	proc :HSTRING
    get_Producers	proc :ptr
    get_Publisher	proc :ptr
    put_Publisher	proc :HSTRING
    get_Writers		proc :ptr
    get_Year		proc :ptr
    put_Year		proc :UINT32
    get_Bitrate		proc :ptr
    get_Directors	proc :ptr
    get_Orientation	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CFileProperties_CIDocumentProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CFileProperties_CIDocumentProperties_INTERFACE_DEFINED__

DEFINE_IIDX(IDocumentProperties, "7EAB19BC-1821-4923-B4A9-0AEA404D0070")

.comdef IDocumentProperties : public IInspectable

    get_Author		proc :ptr
    get_Title		proc :ptr
    put_Title		proc :HSTRING
    get_Keywords	proc :ptr
    get_Comment		proc :ptr
    put_Comment		proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CFileProperties_CIBasicProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CFileProperties_CIBasicProperties_INTERFACE_DEFINED__

DEFINE_IIDX(IBasicProperties, "D05D55DB-785E-4A66-BE02-9BEEC58AEA81")

.comdef IBasicProperties : public IInspectable

    get_Size		proc :ptr
    get_DateModified	proc :ptr
    get_ItemDate	proc :ptr
   .ends

endif

.endn
.endn
.endn

HSTRING_UserSize	proto WINAPI :ptr, :ULONG, :ptr
HSTRING_UserMarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree	proto WINAPI :ptr, :ptr

HSTRING_UserSize64	proto WINAPI :ptr, :ULONG, :ptr
HSTRING_UserMarshal64	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree64	proto WINAPI :ptr, :ptr

endif
