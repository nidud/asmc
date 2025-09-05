ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Emedia2Eplaylists_h__
define __windows2Emedia2Eplaylists_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.inc

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CPlaylists__CPlaylist_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CPlaylists__CPlaylist_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CMedia__CPlaylists__CPlaylist, "427deafd-b226-5ef0-9320-c9f325e37474")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CMedia__CPlaylists__CPlaylist : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CMedia__CPlaylists__CPlaylist_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CMedia__CPlaylists__CPlaylist_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CMedia__CPlaylists__CPlaylist, "8ffb74ab-912f-5bc1-87fa-2865f673cbfc")

.comdef __FIAsyncOperation_1_Windows__CMedia__CPlaylists__CPlaylist : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Media
.namespace Playlists

.enum PlaylistFormat {
    PlaylistFormat_WindowsMedia = 0,
    PlaylistFormat_Zune = 1,
    PlaylistFormat_M3u	= 2
    }

ifndef ____x_ABI_CWindows_CMedia_CPlaylists_CIPlaylist_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlaylists_CIPlaylist_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Playlists_IPlaylist <L"Windows.Media.Playlists.IPlaylist">
DEFINE_IIDX(IPlaylist, "803736F5-CF44-4D97-83B3-7A089E9AB663")

.comdef IPlaylist : public IInspectable

    get_Files		proc :ptr
    SaveAsync		proc :ptr
    SaveAsAsync		proc :ptr, :HSTRING, :Windows::Storage::NameCollisionOption, :ptr
    SaveAsWithFormatAsync proc :ptr, :HSTRING, :Windows::Storage::NameCollisionOption, :Windows::Media::Playlists::PlaylistFormat, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlaylists_CIPlaylistStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlaylists_CIPlaylistStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Playlists_IPlaylistStatics <L"Windows.Media.Playlists.IPlaylistStatics">
DEFINE_IIDX(IPlaylistStatics, "C5C331CD-81F9-4FF3-95B9-70B6FF046B68")

.comdef IPlaylistStatics : public IInspectable

    LoadAsync		proc :ptr, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Media_Playlists_Playlist_DEFINED
define RUNTIMECLASS_Windows_Media_Playlists_Playlist_DEFINED
define RuntimeClass_Windows_Media_Playlists_Playlist <L"Windows.Media.Playlists.Playlist">
endif

endif
