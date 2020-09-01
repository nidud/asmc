include rpc.inc
include rpcndr.inc

INITGUID equ 1
include guiddef.inc

MIDL_DEFINE_GUID macro _type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8
        exitm<DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)>
        endm

MIDL_DEFINE_GUID(IID, IID_IWTSSBPlugin,0xDC44BE78,0xB18D,0x4399,0xB2,0x10,0x64,0x1B,0xF6,0x7A,0x00,0x2C);
