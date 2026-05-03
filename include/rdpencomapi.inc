ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __rdpencomapi_h__
define __rdpencomapi_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

define	DISPID_RDPSRAPI_METHOD_OPEN	( 100 )
define	DISPID_RDPSRAPI_METHOD_CLOSE	( 101 )
define	DISPID_RDPSRAPI_METHOD_SETSHAREDRECT	( 102 )
define	DISPID_RDPSRAPI_METHOD_GETSHAREDRECT	( 103 )
define	DISPID_RDPSRAPI_METHOD_VIEWERCONNECT	( 104 )
define	DISPID_RDPSRAPI_METHOD_VIEWERDISCONNECT ( 105 )
define	DISPID_RDPSRAPI_METHOD_TERMINATE_CONNECTION	( 106 )
define	DISPID_RDPSRAPI_METHOD_CREATE_INVITATION	( 107 )
define	DISPID_RDPSRAPI_METHOD_REQUEST_CONTROL	( 108 )
define	DISPID_RDPSRAPI_METHOD_VIRTUAL_CHANNEL_CREATE	( 109 )
define	DISPID_RDPSRAPI_METHOD_VIRTUAL_CHANNEL_SEND_DATA	( 110 )
define	DISPID_RDPSRAPI_METHOD_VIRTUAL_CHANNEL_SET_ACCESS	( 111 )
define	DISPID_RDPSRAPI_METHOD_PAUSE	( 112 )
define	DISPID_RDPSRAPI_METHOD_RESUME	( 113 )
define	DISPID_RDPSRAPI_METHOD_SHOW_WINDOW	( 114 )
define	DISPID_RDPSRAPI_METHOD_REQUEST_COLOR_DEPTH_CHANGE	( 115 )
define	DISPID_RDPSRAPI_METHOD_STARTREVCONNECTLISTENER	( 116 )
define	DISPID_RDPSRAPI_METHOD_CONNECTTOCLIENT	( 117 )
define	DISPID_RDPSRAPI_METHOD_SET_RENDERING_SURFACE	( 118 )
define	DISPID_RDPSRAPI_METHOD_SEND_MOUSE_BUTTON_EVENT	( 119 )
define	DISPID_RDPSRAPI_METHOD_SEND_MOUSE_MOVE_EVENT	( 120 )
define	DISPID_RDPSRAPI_METHOD_SEND_MOUSE_WHEEL_EVENT	( 121 )
define	DISPID_RDPSRAPI_METHOD_SEND_KEYBOARD_EVENT	( 122 )
define	DISPID_RDPSRAPI_METHOD_SEND_SYNC_EVENT	( 123 )
define	DISPID_RDPSRAPI_METHOD_BEGIN_TOUCH_FRAME	( 124 )
define	DISPID_RDPSRAPI_METHOD_ADD_TOUCH_INPUT	( 125 )
define	DISPID_RDPSRAPI_METHOD_END_TOUCH_FRAME	( 126 )
define	DISPID_RDPSRAPI_METHOD_CONNECTUSINGTRANSPORTSTREAM	( 127 )
define	DISPID_RDPSRAPI_METHOD_SENDCONTROLLEVELCHANGERESPONSE	( 148 )
define	DISPID_RDPSRAPI_METHOD_GETFRAMEBUFFERBITS	( 149 )
define	DISPID_RDPSRAPI_PROP_DISPIDVALUE	( 200 )
define	DISPID_RDPSRAPI_PROP_ID ( 201 )
define	DISPID_RDPSRAPI_PROP_SESSION_PROPERTIES ( 202 )
define	DISPID_RDPSRAPI_PROP_ATTENDEES	( 203 )
define	DISPID_RDPSRAPI_PROP_INVITATIONS	( 204 )
define	DISPID_RDPSRAPI_PROP_INVITATION ( 205 )
define	DISPID_RDPSRAPI_PROP_CHANNELMANAGER	( 206 )
define	DISPID_RDPSRAPI_PROP_VIRTUAL_CHANNEL_GETNAME	( 207 )
define	DISPID_RDPSRAPI_PROP_VIRTUAL_CHANNEL_GETFLAGS	( 208 )
define	DISPID_RDPSRAPI_PROP_VIRTUAL_CHANNEL_GETPRIORITY	( 209 )
define	DISPID_RDPSRAPI_PROP_WINDOWID	( 210 )
define	DISPID_RDPSRAPI_PROP_APPLICATION	( 211 )
define	DISPID_RDPSRAPI_PROP_WINDOWSHARED	( 212 )
define	DISPID_RDPSRAPI_PROP_WINDOWNAME ( 213 )
define	DISPID_RDPSRAPI_PROP_APPNAME	( 214 )
define	DISPID_RDPSRAPI_PROP_APPLICATION_FILTER ( 215 )
define	DISPID_RDPSRAPI_PROP_WINDOW_LIST	( 216 )
define	DISPID_RDPSRAPI_PROP_APPLICATION_LIST	( 217 )
define	DISPID_RDPSRAPI_PROP_APPFILTER_ENABLED	( 218 )
define	DISPID_RDPSRAPI_PROP_APPFILTERENABLED	( 219 )
define	DISPID_RDPSRAPI_PROP_SHARED	( 220 )
define	DISPID_RDPSRAPI_PROP_INVITATIONITEM	( 221 )
define	DISPID_RDPSRAPI_PROP_DBG_CLX_CMDLINE	( 222 )
define	DISPID_RDPSRAPI_PROP_APPFLAGS	( 223 )
define	DISPID_RDPSRAPI_PROP_WNDFLAGS	( 224 )
define	DISPID_RDPSRAPI_PROP_PROTOCOL_TYPE	( 225 )
define	DISPID_RDPSRAPI_PROP_LOCAL_PORT ( 226 )
define	DISPID_RDPSRAPI_PROP_LOCAL_IP	( 227 )
define	DISPID_RDPSRAPI_PROP_PEER_PORT	( 228 )
define	DISPID_RDPSRAPI_PROP_PEER_IP	( 229 )
define	DISPID_RDPSRAPI_PROP_ATTENDEE_FLAGS	( 230 )
define	DISPID_RDPSRAPI_PROP_CONINFO	( 231 )
define	DISPID_RDPSRAPI_PROP_CONNECTION_STRING	( 232 )
define	DISPID_RDPSRAPI_PROP_GROUP_NAME ( 233 )
define	DISPID_RDPSRAPI_PROP_PASSWORD	( 234 )
define	DISPID_RDPSRAPI_PROP_ATTENDEELIMIT	( 235 )
define	DISPID_RDPSRAPI_PROP_REVOKED	( 236 )
define	DISPID_RDPSRAPI_PROP_DISCONNECTED_STRING	( 237 )
define	DISPID_RDPSRAPI_PROP_USESMARTSIZING	( 238 )
define	DISPID_RDPSRAPI_PROP_SESSION_COLORDEPTH ( 239 )
define	DISPID_RDPSRAPI_PROP_REASON	( 240 )
define	DISPID_RDPSRAPI_PROP_CODE	( 241 )
define	DISPID_RDPSRAPI_PROP_CTRL_LEVEL ( 242 )
define	DISPID_RDPSRAPI_PROP_REMOTENAME ( 243 )
define	DISPID_RDPSRAPI_PROP_COUNT	( 244 )
define	DISPID_RDPSRAPI_PROP_FRAMEBUFFER_HEIGHT ( 251 )
define	DISPID_RDPSRAPI_PROP_FRAMEBUFFER_WIDTH	( 252 )
define	DISPID_RDPSRAPI_PROP_FRAMEBUFFER_BPP	( 253 )
define	DISPID_RDPSRAPI_PROP_FRAMEBUFFER	( 254 )
define	DISPID_RDPSRAPI_EVENT_ON_ATTENDEE_CONNECTED	( 301 )
define	DISPID_RDPSRAPI_EVENT_ON_ATTENDEE_DISCONNECTED	( 302 )
define	DISPID_RDPSRAPI_EVENT_ON_ATTENDEE_UPDATE	( 303 )
define	DISPID_RDPSRAPI_EVENT_ON_ERROR	( 304 )
define	DISPID_RDPSRAPI_EVENT_ON_VIEWER_CONNECTED	( 305 )
define	DISPID_RDPSRAPI_EVENT_ON_VIEWER_DISCONNECTED	( 306 )
define	DISPID_RDPSRAPI_EVENT_ON_VIEWER_AUTHENTICATED	( 307 )
define	DISPID_RDPSRAPI_EVENT_ON_VIEWER_CONNECTFAILED	( 308 )
define	DISPID_RDPSRAPI_EVENT_ON_CTRLLEVEL_CHANGE_REQUEST	( 309 )
define	DISPID_RDPSRAPI_EVENT_ON_GRAPHICS_STREAM_PAUSED ( 310 )
define	DISPID_RDPSRAPI_EVENT_ON_GRAPHICS_STREAM_RESUMED	( 311 )
define	DISPID_RDPSRAPI_EVENT_ON_VIRTUAL_CHANNEL_JOIN	( 312 )
define	DISPID_RDPSRAPI_EVENT_ON_VIRTUAL_CHANNEL_LEAVE	( 313 )
define	DISPID_RDPSRAPI_EVENT_ON_VIRTUAL_CHANNEL_DATARECEIVED	( 314 )
define	DISPID_RDPSRAPI_EVENT_ON_VIRTUAL_CHANNEL_SENDCOMPLETED	( 315 )
define	DISPID_RDPSRAPI_EVENT_ON_APPLICATION_OPEN	( 316 )
define	DISPID_RDPSRAPI_EVENT_ON_APPLICATION_CLOSE	( 317 )
define	DISPID_RDPSRAPI_EVENT_ON_APPLICATION_UPDATE	( 318 )
define	DISPID_RDPSRAPI_EVENT_ON_WINDOW_OPEN	( 319 )
define	DISPID_RDPSRAPI_EVENT_ON_WINDOW_CLOSE	( 320 )
define	DISPID_RDPSRAPI_EVENT_ON_WINDOW_UPDATE	( 321 )
define	DISPID_RDPSRAPI_EVENT_ON_APPFILTER_UPDATE	( 322 )
define	DISPID_RDPSRAPI_EVENT_ON_SHARED_RECT_CHANGED	( 323 )
define	DISPID_RDPSRAPI_EVENT_ON_FOCUSRELEASED	( 324 )
define	DISPID_RDPSRAPI_EVENT_ON_SHARED_DESKTOP_SETTINGS_CHANGED	( 325 )
define	DISPID_RDPSRAPI_EVENT_ON_CTRLLEVEL_CHANGE_RESPONSE	( 338 )
define	DISPID_RDPAPI_EVENT_ON_BOUNDING_RECT_CHANGED	( 340 )
define	DISPID_RDPSRAPI_METHOD_STREAM_ALLOCBUFFER	( 421 )
define	DISPID_RDPSRAPI_METHOD_STREAM_FREEBUFFER	( 422 )
define	DISPID_RDPSRAPI_METHOD_STREAMSENDDATA	( 423 )
define	DISPID_RDPSRAPI_METHOD_STREAMREADDATA	( 424 )
define	DISPID_RDPSRAPI_METHOD_STREAMOPEN	( 425 )
define	DISPID_RDPSRAPI_METHOD_STREAMCLOSE	( 426 )
define	DISPID_RDPSRAPI_PROP_STREAMBUFFER_STORAGE	( 555 )
define	DISPID_RDPSRAPI_PROP_STREAMBUFFER_PAYLOADSIZE	( 558 )
define	DISPID_RDPSRAPI_PROP_STREAMBUFFER_PAYLOADOFFSET ( 559 )
define	DISPID_RDPSRAPI_PROP_STREAMBUFFER_CONTEXT	( 560 )
define	DISPID_RDPSRAPI_PROP_STREAMBUFFER_FLAGS ( 561 )
define	DISPID_RDPSRAPI_PROP_STREAMBUFFER_STORESIZE	( 562 )
define	DISPID_RDPSRAPI_EVENT_ON_STREAM_SENDCOMPLETED	( 632 )
define	DISPID_RDPSRAPI_EVENT_ON_STREAM_DATARECEIVED	( 633 )
define	DISPID_RDPSRAPI_EVENT_ON_STREAM_CLOSED	( 634 )
define	DISPID_RDPSRAPI_EVENT_VIEW_MOUSE_BUTTON_RECEIVED	( 700 )
define	DISPID_RDPSRAPI_EVENT_VIEW_MOUSE_MOVE_RECEIVED	( 701 )
define	DISPID_RDPSRAPI_EVENT_VIEW_MOUSE_WHEEL_RECEIVED ( 702 )

.enum CTRL_LEVEL {
	CTRL_LEVEL_MIN		= 0,
	CTRL_LEVEL_INVALID	= 0,
	CTRL_LEVEL_NONE		= 1,
	CTRL_LEVEL_VIEW		= 2,
	CTRL_LEVEL_INTERACTIVE	= 3,
	CTRL_LEVEL_REQCTRL_VIEW = 4,
	CTRL_LEVEL_REQCTRL_INTERACTIVE	= 5,
	CTRL_LEVEL_MAX		= 5
	}

.enum ATTENDEE_DISCONNECT_REASON {
	ATTENDEE_DISCONNECT_REASON_MIN	= 0,
	ATTENDEE_DISCONNECT_REASON_APP	= 0,
	ATTENDEE_DISCONNECT_REASON_ERR	= 1,
	ATTENDEE_DISCONNECT_REASON_CLI	= 2,
	ATTENDEE_DISCONNECT_REASON_MAX	= 2
	}

.enum CHANNEL_PRIORITY {
	CHANNEL_PRIORITY_LO,
	CHANNEL_PRIORITY_MED,
	CHANNEL_PRIORITY_HI
	}

.enum CHANNEL_FLAGS {
	CHANNEL_FLAGS_LEGACY		= 0x1,
	CHANNEL_FLAGS_UNCOMPRESSED	= 0x2,
	CHANNEL_FLAGS_DYNAMIC		= 0x4
	}

.enum CHANNEL_ACCESS_ENUM {
	CHANNEL_ACCESS_ENUM_NONE,
	CHANNEL_ACCESS_ENUM_SENDRECEIVE
	}

.enum RDPENCOMAPI_ATTENDEE_FLAGS {
	ATTENDEE_FLAGS_LOCAL	= 1
	}

.enum RDPSRAPI_WND_FLAGS {
	WND_FLAG_PRIVILEGED	= 1
	}

.enum RDPSRAPI_APP_FLAGS {
	APP_FLAG_PRIVILEGED	= 1
	}

.enum RDPSRAPI_MOUSE_BUTTON_TYPE {
	RDPSRAPI_MOUSE_BUTTON_BUTTON1,
	RDPSRAPI_MOUSE_BUTTON_BUTTON2,
	RDPSRAPI_MOUSE_BUTTON_BUTTON3,
	RDPSRAPI_MOUSE_BUTTON_XBUTTON1,
	RDPSRAPI_MOUSE_BUTTON_XBUTTON2,
	RDPSRAPI_MOUSE_BUTTON_XBUTTON3
	}

.enum RDPSRAPI_KBD_CODE_TYPE {
	RDPSRAPI_KBD_CODE_SCANCODE,
	RDPSRAPI_KBD_CODE_UNICODE
	}

.enum RDPSRAPI_KBD_SYNC_FLAG {
	RDPSRAPI_KBD_SYNC_FLAG_SCROLL_LOCK	= 1,
	RDPSRAPI_KBD_SYNC_FLAG_NUM_LOCK		= 2,
	RDPSRAPI_KBD_SYNC_FLAG_CAPS_LOCK	= 4,
	RDPSRAPI_KBD_SYNC_FLAG_KANA_LOCK	= 8
	}

ifndef __IRDPSRAPIDebug_INTERFACE_DEFINED__
define __IRDPSRAPIDebug_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIDebug, "aa1e42b5-496d-4ca4-a690-348dcb2ec4ad")

.comdef IRDPSRAPIDebug : public IUnknown
    put_CLXCmdLine	proc :BSTR
    get_CLXCmdLine	proc :ptr
   .ends

endif

ifndef __IRDPSRAPIPerfCounterLogger_INTERFACE_DEFINED__
define __IRDPSRAPIPerfCounterLogger_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIPerfCounterLogger, "071c2533-0fa4-4e8f-ae83-9c10b4305ab5")

.comdef IRDPSRAPIPerfCounterLogger : public IUnknown
    LogValue		proc :int64_t
   .ends

endif

ifndef __IRDPSRAPIPerfCounterLoggingManager_INTERFACE_DEFINED__
define __IRDPSRAPIPerfCounterLoggingManager_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIPerfCounterLoggingManager, "9a512c86-ac6e-4a8e-b1a4-fcef363f6e64")

.comdef IRDPSRAPIPerfCounterLoggingManager : public IUnknown
    CreateLogger	proc :BSTR, :ptr ptr
   .ends

endif

ifndef __IRDPSRAPIAudioStream_INTERFACE_DEFINED__
define __IRDPSRAPIAudioStream_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIAudioStream, "e3e30ef9-89c6-4541-ba3b-19336ac6d31c")

.comdef IRDPSRAPIAudioStream : public IUnknown
    Initialize		proc :ptr
    Start		proc
    Stop		proc
    GetBuffer		proc :ptr ptr, :ptr, :ptr
    FreeBuffer		proc
   .ends

endif

ifndef __IRDPSRAPIClipboardUseEvents_INTERFACE_DEFINED__
define __IRDPSRAPIClipboardUseEvents_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIClipboardUseEvents, "D559F59A-7A27-4138-8763-247CE5F659A8")

.comdef IRDPSRAPIClipboardUseEvents : public IUnknown
    OnPasteFromClipboard proc :UINT, :ptr, :ptr
   .ends

endif

ifndef __IRDPSRAPIWindow_INTERFACE_DEFINED__
define __IRDPSRAPIWindow_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIWindow, "beafe0f9-c77b-4933-ba9f-a24cddcc27cf")

.comdef IRDPSRAPIWindow : public IDispatch
    get_Id		proc :ptr
    get_Application	proc :ptr ptr
    get_Shared		proc :ptr
    put_Shared		proc :VARIANT_BOOL
    get_Name		proc :ptr
    Show		proc
    get_Flags		proc :ptr
   .ends

endif

ifndef __IRDPSRAPIWindowList_INTERFACE_DEFINED__
define __IRDPSRAPIWindowList_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIWindowList, "8a05ce44-715a-4116-a189-a118f30a07bd")

.comdef IRDPSRAPIWindowList : public IDispatch
    get__NewEnum	proc :ptr ptr
    get_Item		proc :LONG, :ptr ptr
   .ends

endif

ifndef __IRDPSRAPIApplication_INTERFACE_DEFINED__
define __IRDPSRAPIApplication_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIApplication, "41e7a09d-eb7a-436e-935d-780ca2628324")

.comdef IRDPSRAPIApplication : public IDispatch
    get_Windows		proc :ptr ptr
    get_Id		proc :ptr
    get_Shared		proc :ptr
    put_Shared		proc :VARIANT_BOOL
    get_Name		proc :ptr
    get_Flags		proc :ptr
   .ends

endif

ifndef __IRDPSRAPIApplicationList_INTERFACE_DEFINED__
define __IRDPSRAPIApplicationList_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIApplicationList, "d4b4aeb3-22dc-4837-b3b6-42ea2517849a")

.comdef IRDPSRAPIApplicationList : public IDispatch
    get__NewEnum	proc :ptr ptr
    get_Item		proc :LONG, :ptr ptr
   .ends

endif

ifndef __IRDPSRAPIApplicationFilter_INTERFACE_DEFINED__
define __IRDPSRAPIApplicationFilter_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIApplicationFilter, "d20f10ca-6637-4f06-b1d5-277ea7e5160d")

.comdef IRDPSRAPIApplicationFilter : public IDispatch
    get_Applications	proc :ptr ptr
    get_Windows		proc :ptr ptr
    get_Enabled		proc :ptr
    put_Enabled		proc :VARIANT_BOOL
   .ends

endif

ifndef __IRDPSRAPISessionProperties_INTERFACE_DEFINED__
define __IRDPSRAPISessionProperties_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPISessionProperties, "339b24f2-9bc0-4f16-9aac-f165433d13d4")

.comdef IRDPSRAPISessionProperties : public IDispatch
    get_Property	proc :BSTR, :ptr
    put_Property	proc :BSTR, :VARIANT
   .ends

endif

ifndef __IRDPSRAPIInvitation_INTERFACE_DEFINED__
define __IRDPSRAPIInvitation_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIInvitation, "4fac1d43-fc51-45bb-b1b4-2b53aa562fa3")

.comdef IRDPSRAPIInvitation : public IDispatch
    get_ConnectionString proc :ptr
    get_GroupName	proc :ptr
    get_Password	proc :ptr
    get_AttendeeLimit	proc :ptr
    put_AttendeeLimit	proc :LONG
    get_Revoked		proc :ptr
    put_Revoked		proc :VARIANT_BOOL
   .ends

endif

ifndef __IRDPSRAPIInvitationManager_INTERFACE_DEFINED__
define __IRDPSRAPIInvitationManager_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIInvitationManager, "4722b049-92c3-4c2d-8a65-f7348f644dcf")

.comdef IRDPSRAPIInvitationManager : public IDispatch
    get__NewEnum	proc :ptr ptr
    get_Item		proc :VARIANT, :ptr ptr
    get_Count		proc :ptr
    CreateInvitation	proc :BSTR, :BSTR, :BSTR, :LONG, :ptr ptr
   .ends

endif

ifndef __IRDPSRAPITcpConnectionInfo_INTERFACE_DEFINED__
define __IRDPSRAPITcpConnectionInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPITcpConnectionInfo, "f74049a4-3d06-4028-8193-0a8c29bc2452")

.comdef IRDPSRAPITcpConnectionInfo : public IDispatch
    get_Protocol	proc :ptr
    get_LocalPort	proc :ptr
    get_LocalIP		proc :ptr
    get_PeerPort	proc :ptr
    get_PeerIP		proc :ptr
   .ends

endif

ifndef __IRDPSRAPIAttendee_INTERFACE_DEFINED__
define __IRDPSRAPIAttendee_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIAttendee, "ec0671b3-1b78-4b80-a464-9132247543e3")

.comdef IRDPSRAPIAttendee : public IDispatch
    get_Id		proc :ptr
    get_RemoteName	proc :ptr
    get_ControlLevel	proc :ptr
    put_ControlLevel	proc :CTRL_LEVEL
    get_Invitation	proc :ptr ptr
    TerminateConnection proc
    get_Flags		proc :ptr
    get_ConnectivityInfo proc :ptr ptr
   .ends

endif

ifndef __IRDPSRAPIAttendeeManager_INTERFACE_DEFINED__
define __IRDPSRAPIAttendeeManager_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIAttendeeManager, "ba3a37e8-33da-4749-8da0-07fa34da7944")

.comdef IRDPSRAPIAttendeeManager : public IDispatch
    get__NewEnum	proc :ptr ptr
    get_Item		proc :LONG, :ptr ptr
   .ends

endif

ifndef __IRDPSRAPIAttendeeDisconnectInfo_INTERFACE_DEFINED__
define __IRDPSRAPIAttendeeDisconnectInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIAttendeeDisconnectInfo, "c187689f-447c-44a1-9c14-fffbb3b7ec17")

.comdef IRDPSRAPIAttendeeDisconnectInfo : public IDispatch
    get_Attendee	proc :ptr ptr
    get_Reason		proc :ptr
    get_Code		proc :ptr
   .ends

endif

ifndef __IRDPSRAPIVirtualChannel_INTERFACE_DEFINED__
define __IRDPSRAPIVirtualChannel_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIVirtualChannel, "05e12f95-28b3-4c9a-8780-d0248574a1e0")

.comdef IRDPSRAPIVirtualChannel : public IDispatch
    SendData		proc :BSTR, :LONG, :LONG
    SetAccess		proc :LONG, :CHANNEL_ACCESS_ENUM
    get_Name		proc :ptr
    get_Flags		proc :ptr
    get_Priority	proc :ptr
   .ends

endif

ifndef __IRDPSRAPIVirtualChannelManager_INTERFACE_DEFINED__
define __IRDPSRAPIVirtualChannelManager_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIVirtualChannelManager, "0d11c661-5d0d-4ee4-89df-2166ae1fdfed")

.comdef IRDPSRAPIVirtualChannelManager : public IDispatch
    get__NewEnum	proc :ptr ptr
    get_Item		proc :VARIANT, :ptr ptr
    CreateVirtualChannel proc :BSTR, :CHANNEL_PRIORITY, :LONG, :ptr ptr
   .ends

endif

ifndef __IRDPSRAPIViewer_INTERFACE_DEFINED__
define __IRDPSRAPIViewer_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIViewer, "c6bfcd38-8ce9-404d-8ae8-f31d00c65cb5")

.comdef IRDPSRAPIViewer : public IDispatch
    Connect		proc :BSTR, :BSTR, :BSTR
    Disconnect		proc
    get_Attendees	proc :ptr ptr
    get_Invitations	proc :ptr ptr
    get_ApplicationFilter proc :ptr ptr
    get_VirtualChannelManager proc :ptr ptr
    put_SmartSizing	proc :VARIANT_BOOL
    get_SmartSizing	proc :ptr
    RequestControl	proc :CTRL_LEVEL
    put_DisconnectedText proc :BSTR
    get_DisconnectedText proc :ptr
    RequestColorDepthChange proc :LONG
    get_Properties	proc :ptr ptr
    StartReverseConnectListener proc :BSTR, :BSTR, :BSTR, :ptr
   .ends

endif

ifndef __IRDPViewerInputSink_INTERFACE_DEFINED__
define __IRDPViewerInputSink_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPViewerInputSink, "BB590853-A6C5-4A7B-8DD4-76B69EEA12D5")

.comdef IRDPViewerInputSink : public IUnknown
    SendMouseButtonEvent proc :RDPSRAPI_MOUSE_BUTTON_TYPE, :VARIANT_BOOL, :ULONG, :ULONG
    SendMouseMoveEvent	proc :ULONG, :ULONG
    SendMouseWheelEvent proc :UINT16
    SendKeyboardEvent	proc :RDPSRAPI_KBD_CODE_TYPE, :UINT16, :VARIANT_BOOL, :VARIANT_BOOL, :VARIANT_BOOL
    SendSyncEvent	proc :ULONG
    BeginTouchFrame	proc
    AddTouchInput	proc :UINT32, :UINT32, :INT32, :INT32
    EndTouchFrame	proc
   .ends

endif

ifndef __IRDPSRAPIFrameBuffer_INTERFACE_DEFINED__
define __IRDPSRAPIFrameBuffer_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPIFrameBuffer, "3D67E7D2-B27B-448E-81B3-C6110ED8B4BE")

.comdef IRDPSRAPIFrameBuffer : public IDispatch
    get_Width		proc :ptr
    get_Height		proc :ptr
    get_Bpp		proc :ptr
    GetFrameBufferBits	proc :LONG, :LONG, :LONG, :LONG, :ptr
   .ends

endif

ifndef __IRDPSRAPITransportStreamBuffer_INTERFACE_DEFINED__
define __IRDPSRAPITransportStreamBuffer_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPITransportStreamBuffer, "81c80290-5085-44b0-b460-f865c39cb4a9")

.comdef IRDPSRAPITransportStreamBuffer : public IUnknown
    get_Storage		proc :ptr ptr
    get_StorageSize	proc :ptr
    get_PayloadSize	proc :ptr
    put_PayloadSize	proc :LONG
    get_PayloadOffset	proc :ptr
    put_PayloadOffset	proc :LONG
    get_Flags		proc :ptr
    put_Flags		proc :LONG
    get_Context		proc :ptr ptr
    put_Context		proc :ptr
   .ends

endif

ifndef __IRDPSRAPITransportStreamEvents_INTERFACE_DEFINED__
define __IRDPSRAPITransportStreamEvents_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPITransportStreamEvents, "ea81c254-f5af-4e40-982e-3e63bb595276")

.comdef IRDPSRAPITransportStreamEvents : public IUnknown
    OnWriteCompleted	proc :ptr
    OnReadCompleted	proc :ptr
    OnStreamClosed	proc :HRESULT
   .ends

endif

ifndef __IRDPSRAPITransportStream_INTERFACE_DEFINED__
define __IRDPSRAPITransportStream_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPITransportStream, "36cfa065-43bb-4ef7-aed7-9b88a5053036")

.comdef IRDPSRAPITransportStream : public IUnknown
    AllocBuffer		proc :LONG, :ptr ptr
    FreeBuffer		proc :ptr
    WriteBuffer		proc :ptr
    ReadBuffer		proc :ptr
    Open		proc :ptr
    Close		proc
   .ends

endif

ifndef __IRDPSRAPISharingSession_INTERFACE_DEFINED__
define __IRDPSRAPISharingSession_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPISharingSession, "eeb20886-e470-4cf6-842b-2739c0ec5cfb")

.comdef IRDPSRAPISharingSession : public IDispatch
    Open		proc
    Close		proc
    put_ColorDepth	proc :LONG
    get_ColorDepth	proc :ptr
    get_Properties	proc :ptr ptr
    get_Attendees	proc :ptr ptr
    get_Invitations	proc :ptr ptr
    get_ApplicationFilter proc :ptr ptr
    get_VirtualChannelManager proc :ptr ptr
    _Pause		proc
    Resume		proc
    ConnectToClient	proc :BSTR
    SetDesktopSharedRect proc :LONG, :LONG, :LONG, :LONG
    GetDesktopSharedRect proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef __IRDPSRAPISharingSession2_INTERFACE_DEFINED__
define __IRDPSRAPISharingSession2_INTERFACE_DEFINED__

DEFINE_IIDX(IRDPSRAPISharingSession2, "fee4ee57-e3e8-4205-8fb0-8fd1d0675c21")

.comdef IRDPSRAPISharingSession2 : public IRDPSRAPISharingSession
    ConnectUsingTransportStream proc :ptr, :BSTR, :BSTR
    get_FrameBuffer	proc :ptr ptr
    SendControlLevelChangeResponse proc :ptr, :CTRL_LEVEL, :LONG
   .ends

endif

ifndef __RDPCOMAPILib_LIBRARY_DEFINED__
define __RDPCOMAPILib_LIBRARY_DEFINED__

.enum RDPENCOMAPI_CONSTANTS {
	CONST_MAX_CHANNEL_MESSAGE_SIZE		= 1024,
	CONST_MAX_CHANNEL_NAME_LEN		= 8,
	CONST_MAX_LEGACY_CHANNEL_MESSAGE_SIZE	= 409600,
	CONST_ATTENDEE_ID_EVERYONE		= -1,
	CONST_ATTENDEE_ID_HOST			= 0,
	CONST_CONN_INTERVAL			= 50,
	CONST_ATTENDEE_ID_DEFAULT		= 0xffffffff
	}

__ReferenceRemainingTypes__ struct
__ctrlLevel__		CTRL_LEVEL ?
__attendeeDisconnectReason__ ATTENDEE_DISCONNECT_REASON ?
__channelPriority__	CHANNEL_PRIORITY ?
__channelFlags__	CHANNEL_FLAGS ?
__channelAccessEnum__	CHANNEL_ACCESS_ENUM ?
__rdpencomapiAttendeeFlags__ RDPENCOMAPI_ATTENDEE_FLAGS ?
__rdpsrapiWndFlags__	RDPSRAPI_WND_FLAGS ?
__rdpsrapiAppFlags__	RDPSRAPI_APP_FLAGS ?
__ReferenceRemainingTypes__ ends

externdef LIBID_RDPCOMAPILib:IID

ifndef ___IRDPSessionEvents_DISPINTERFACE_DEFINED__
define ___IRDPSessionEvents_DISPINTERFACE_DEFINED__

DEFINE_IIDX(_IRDPSessionEvents, "98a97042-6698-40e9-8efd-b3200990004b")

.comdef _IRDPSessionEvents : public IDispatch
   .ends

endif

DEFINE_GUIDS(CLSID_RDPViewer, "32be5ed2-5c86-480f-a914-0ff8885a1b3f")
DEFINE_GUIDS(CLSID_RDPSRAPISessionProperties, "dd7594ff-ea2a-4c06-8fdf-132de48b6510")
DEFINE_GUIDS(CLSID_RDPSRAPIInvitationManager, "53d9c9db-75ab-4271-948a-4c4eb36a8f2b")
DEFINE_GUIDS(CLSID_RDPSRAPIInvitation, "49174dc6-0731-4b5e-8ee1-83a63d3868fa")
DEFINE_GUIDS(CLSID_RDPSRAPIAttendeeManager, "d7b13a01-f7d4-42a6-8595-12fc8c24e851")
DEFINE_GUIDS(CLSID_RDPSRAPIAttendee, "74f93bb5-755f-488e-8a29-2390108aef55")
DEFINE_GUIDS(CLSID_RDPSRAPIAttendeeDisconnectInfo, "b47d7250-5bdb-405d-b487-caad9c56f4f8")
DEFINE_GUIDS(CLSID_RDPSRAPIApplicationFilter, "e35ace89-c7e8-427e-a4f9-b9da072826bd")
DEFINE_GUIDS(CLSID_RDPSRAPIApplicationList, "9e31c815-7433-4876-97fb-ed59fe2baa22")
DEFINE_GUIDS(CLSID_RDPSRAPIApplication, "c116a484-4b25-4b9f-8a54-b934b06e57fa")
DEFINE_GUIDS(CLSID_RDPSRAPIWindowList, "9c21e2b8-5dd4-42cc-81ba-1c099852e6fa")
DEFINE_GUIDS(CLSID_RDPSRAPIWindow, "03cf46db-ce45-4d36-86ed-ed28b74398bf")
DEFINE_GUIDS(CLSID_RDPSRAPITcpConnectionInfo, "be49db3f-ebb6-4278-8ce0-d5455833eaee")
DEFINE_GUIDS(CLSID_RDPSession, "9B78F0E6-3E05-4A5B-B2E8-E743A8956B65")
DEFINE_GUIDS(CLSID_RDPSRAPIFrameBuffer, "a4f66bcc-538e-4101-951d-30847adb5101")
DEFINE_GUIDS(CLSID_RDPTransportStreamBuffer, "8D4A1C69-F17F-4549-A699-761C6E6B5C0A")
DEFINE_GUIDS(CLSID_RDPTransportStreamEvents, "31E3AB20-5350-483f-9DC6-6748665EFDEB")

endif

endif

endif
