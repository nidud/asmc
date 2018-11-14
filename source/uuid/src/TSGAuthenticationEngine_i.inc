include rpc.inc
include rpcndr.inc

INITGUID equ 1
include guiddef.inc

MIDL_DEFINE_GUID macro _type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8
        exitm<DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)>
        endm

MIDL_DEFINE_GUID(IID, IID_ITSGAuthenticateUserSink,0x2c3e2e73,0xa782,0x47f9,0x8d,0xfb,0x77,0xee,0x1e,0xd2,0x7a,0x03);
MIDL_DEFINE_GUID(IID, IID_ITSGAuthenticationEngine,0x9ee3e5bf,0x04ab,0x4691,0x99,0x8c,0xd7,0xf6,0x22,0x32,0x1a,0x56);
