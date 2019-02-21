include rpc.inc
include rpcndr.inc

INITGUID equ 1
include guiddef.inc

MIDL_DEFINE_GUID macro _type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8
        exitm<DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)>
        endm

MIDL_DEFINE_GUID(IID, IID_IDataSource,0xCD000029,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(IID, IID_IMessage,0xCD000020,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(IID, IID_IBodyPart,0xCD000021,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(IID, IID_IConfiguration,0xCD000022,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(IID, IID_IMessages,0xCD000025,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(IID, IID_IDropDirectory,0xCD000024,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(IID, IID_IBodyParts,0xCD000023,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(IID, IID_ISMTPScriptConnector,0xCD000030,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(IID, IID_INNTPEarlyScriptConnector,0xCD000034,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(IID, IID_INNTPPostScriptConnector,0xCD000031,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(IID, IID_INNTPFinalScriptConnector,0xCD000032,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(IID, IID_ISMTPOnArrival,0xCD000026,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(IID, IID_INNTPOnPostEarly,0xCD000033,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(IID, IID_INNTPOnPost,0xCD000027,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(IID, IID_INNTPOnPostFinal,0xCD000028,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(IID, IID_IProxyObject,0xCD000083,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(IID, IID_IGetInterface,0xCD0ff000,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(IID, LIBID_CDO,0xCD000000,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(CLSID, CLSID_Message,0xCD000001,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(CLSID, CLSID_Configuration,0xCD000002,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(CLSID, CLSID_DropDirectory,0xCD000004,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(CLSID, CLSID_SMTPConnector,0xCD000008,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(CLSID, CLSID_NNTPEarlyConnector,0xCD000011,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(CLSID, CLSID_NNTPPostConnector,0xCD000009,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);
MIDL_DEFINE_GUID(CLSID, CLSID_NNTPFinalConnector,0xCD000010,0x8B95,0x11D1,0x82,0xDB,0x00,0xC0,0x4F,0xB1,0x62,0x5D);