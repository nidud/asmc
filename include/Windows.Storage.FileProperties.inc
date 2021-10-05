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

ifndef DEF___FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CBasicProperties_USE
DEF___FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CBasicProperties_USE equ 1

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CBasicProperties, "c8659aae-4926-52ad-8f60-d89fe5a8df5f")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CBasicProperties : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CBasicProperties_INTERFACE_DEFINED__
____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CBasicProperties_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CFileProperties__CBasicProperties, "5186131a-4467-504b-977a-0785a8230485")

.comdef __FIAsyncOperation_1_Windows__CStorage__CFileProperties__CBasicProperties : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CDocumentProperties_INTERFACE_DEFINED__
____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CDocumentProperties_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CDocumentProperties, "4452ed4c-642b-501b-9617-7d68b4ac3c66")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CDocumentProperties : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CDocumentProperties_INTERFACE_DEFINED__
____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CDocumentProperties_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CFileProperties__CDocumentProperties, "6c86e97c-5699-5700-8d35-d350ad3e4df2")

.comdef __FIAsyncOperation_1_Windows__CStorage__CFileProperties__CDocumentProperties : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CImageProperties_INTERFACE_DEFINED__
____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CImageProperties_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CImageProperties, "c63729bc-e4c3-564c-b137-2cb4f5966a83")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CImageProperties : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CImageProperties_INTERFACE_DEFINED__
____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CImageProperties_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CFileProperties__CImageProperties, "fcd07511-e7f8-5bda-8c04-795a639dae8f")

.comdef __FIAsyncOperation_1_Windows__CStorage__CFileProperties__CImageProperties : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CMusicProperties_INTERFACE_DEFINED__
____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CMusicProperties_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CMusicProperties, "d84e1312-d661-5b7f-9566-7421bdedc1ea")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CMusicProperties : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CMusicProperties_INTERFACE_DEFINED__
____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CMusicProperties_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CFileProperties__CMusicProperties, "0d023b76-20a7-56f3-84ab-ce31e6544b71")

.comdef __FIAsyncOperation_1_Windows__CStorage__CFileProperties__CMusicProperties : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CStorageItemThumbnail_INTERFACE_DEFINED__
____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CStorageItemThumbnail_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CStorageItemThumbnail, "6d0036f2-a8a8-505d-b042-d087dc1fc1b7")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CStorageItemThumbnail : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CStorageItemThumbnail_INTERFACE_DEFINED__
____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CStorageItemThumbnail_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CFileProperties__CStorageItemThumbnail, "11c7cc5e-c04e-50e7-a65e-6f6903690c16")

.comdef __FIAsyncOperation_1_Windows__CStorage__CFileProperties__CStorageItemThumbnail : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CVideoProperties_INTERFACE_DEFINED__
____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CVideoProperties_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CVideoProperties, "43401d34-61ab-5cf2-921f-55b616631d1d")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CFileProperties__CVideoProperties : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CVideoProperties_INTERFACE_DEFINED__
____FIAsyncOperation_1_Windows__CStorage__CFileProperties__CVideoProperties_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CFileProperties__CVideoProperties, "447d4590-d3f9-58bf-ac58-6f9a50839efe")

.comdef __FIAsyncOperation_1_Windows__CStorage__CFileProperties__CVideoProperties : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

.enum _x_ABI_CWindows_CStorage_CFileProperties_CPropertyPrefetchOptions {
    PropertyPrefetchOptions_None	= 0,
    PropertyPrefetchOptions_MusicProperties	= 0x1,
    PropertyPrefetchOptions_VideoProperties	= 0x2,
    PropertyPrefetchOptions_ImageProperties	= 0x4,
    PropertyPrefetchOptions_DocumentProperties	= 0x8,
    PropertyPrefetchOptions_BasicProperties	= 0x10
    }

.enum _x_ABI_CWindows_CStorage_CFileProperties_CThumbnailType {
    ThumbnailType_Image = 0,
    ThumbnailType_Icon	= 1
    }

.enum _x_ABI_CWindows_CStorage_CFileProperties_CThumbnailMode {
    ThumbnailMode_PicturesView	= 0,
    ThumbnailMode_VideosView	= 1,
    ThumbnailMode_MusicView	= 2,
    ThumbnailMode_DocumentsView = 3,
    ThumbnailMode_ListView	= 4,
    ThumbnailMode_SingleItem	= 5
    }

.enum _x_ABI_CWindows_CStorage_CFileProperties_CThumbnailOptions {
    ThumbnailOptions_None	= 0,
    ThumbnailOptions_ReturnOnlyIfCached = 0x1,
    ThumbnailOptions_ResizeThumbnail	= 0x2,
    ThumbnailOptions_UseCurrentScale	= 0x4
    }

.enum _x_ABI_CWindows_CStorage_CFileProperties_CPhotoOrientation {
    PhotoOrientation_Unspecified	= 0,
    PhotoOrientation_Normal	= 1,
    PhotoOrientation_FlipHorizontal	= 2,
    PhotoOrientation_Rotate180	= 3,
    PhotoOrientation_FlipVertical	= 4,
    PhotoOrientation_Transpose	= 5,
    PhotoOrientation_Rotate270	= 6,
    PhotoOrientation_Transverse = 7,
    PhotoOrientation_Rotate90	= 8
    }

.enum _x_ABI_CWindows_CStorage_CFileProperties_CVideoOrientation {
    VideoOrientation_Normal	= 0,
    VideoOrientation_Rotate90	= 90,
    VideoOrientation_Rotate180	= 180,
    VideoOrientation_Rotate270	= 270
    }


ifndef __IThumbnailProperties_INTERFACE_DEFINED__
__IThumbnailProperties_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IThumbnailProperties, "693DD42F-DBE7-49B5-B3B3-2893AC5D3423")

.comdef IThumbnailProperties : public IInspectable

    get_OriginalWidth	proc :ptr
    get_OriginalHeight	proc :ptr
    get_ReturnedSmallerCachedSize proc :ptr
    get_Type		proc :ptr
    .ends

endif

ifndef __IStorageItemExtraProperties_INTERFACE_DEFINED__
__IStorageItemExtraProperties_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IStorageItemExtraProperties, "C54361B2-54CD-432B-BDBC-4B19C4B470D7")

.comdef IStorageItemExtraProperties : public IInspectable

    RetrievePropertiesAsync proc :ptr, :ptr
    SavePropertiesAsync proc :ptr, :ptr
    SavePropertiesAsyncOverloadDefault proc :ptr
    .ends

endif

ifndef __IStorageItemContentProperties_INTERFACE_DEFINED__
__IStorageItemContentProperties_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IStorageItemContentProperties, "05294BAD-BC38-48BF-85D7-770E0E2AE0BA")

.comdef IStorageItemContentProperties : public IInspectable

    GetMusicPropertiesAsync proc :ptr
    GetVideoPropertiesAsync proc :ptr
    GetImagePropertiesAsync proc :ptr
    GetDocumentPropertiesAsync proc :ptr
    .ends

endif

ifndef __IMusicProperties_INTERFACE_DEFINED__
__IMusicProperties_INTERFACE_DEFINED__ equ 1

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

ifndef __IImageProperties_INTERFACE_DEFINED__
__IImageProperties_INTERFACE_DEFINED__ equ 1

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

ifndef __IVideoProperties_INTERFACE_DEFINED__
__IVideoProperties_INTERFACE_DEFINED__ equ 1

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

ifndef __IDocumentProperties_INTERFACE_DEFINED__
__IDocumentProperties_INTERFACE_DEFINED__ equ 1

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

ifndef __IBasicProperties_INTERFACE_DEFINED__
__IBasicProperties_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IBasicProperties, "D05D55DB-785E-4A66-BE02-9BEEC58AEA81")

.comdef IBasicProperties : public IInspectable

    get_Size		proc :ptr
    get_DateModified	proc :ptr
    get_ItemDate	proc :ptr
    .ends

endif


HSTRING_UserSize	proto WINAPI :ptr ULONG, :ULONG, :ptr HSTRING
HSTRING_UserMarshal	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserUnmarshal	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserFree	proto WINAPI :ptr ULONG, :ptr HSTRING

HSTRING_UserSize64	proto WINAPI :ptr ULONG, :ULONG, :ptr HSTRING
HSTRING_UserMarshal64	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserUnmarshal64 proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserFree64	proto WINAPI :ptr ULONG, :ptr HSTRING

endif
