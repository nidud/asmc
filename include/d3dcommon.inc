ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif
include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif
ifndef __d3dcommon_h__
__d3dcommon_h__ equ 1
include oaidl.inc
include ocidl.inc
.xlist

D3D_DRIVER_TYPE         typedef SDWORD
D3D_DRIVER_TYPE_UNKNOWN equ 0
D3D_DRIVER_TYPE_HARDWARE equ ( D3D_DRIVER_TYPE_UNKNOWN + 1 )
D3D_DRIVER_TYPE_REFERENCE equ ( D3D_DRIVER_TYPE_HARDWARE + 1 )
D3D_DRIVER_TYPE_NULL    equ ( D3D_DRIVER_TYPE_REFERENCE + 1 )
D3D_DRIVER_TYPE_SOFTWARE equ ( D3D_DRIVER_TYPE_NULL + 1 )
D3D_DRIVER_TYPE_WARP    equ ( D3D_DRIVER_TYPE_SOFTWARE + 1 )

D3D_FEATURE_LEVEL       typedef SDWORD
D3D_FEATURE_LEVEL_9_1   equ 0x9100
D3D_FEATURE_LEVEL_9_2   equ 0x9200
D3D_FEATURE_LEVEL_9_3   equ 0x9300
D3D_FEATURE_LEVEL_10_0  equ 0xa000
D3D_FEATURE_LEVEL_10_1  equ 0xa100
D3D_FEATURE_LEVEL_11_0  equ 0xb000

DEFINE_GUID(WKPDID_D3DDebugObjectName,0x429b8c22,0x9188,0x4b0c,0x87,0x42,0xac,0xb0,0xbf,0x85,0xc2,0x00);

externdef __MIDL_itf_d3dcommon_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef __MIDL_itf_d3dcommon_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

.list
endif



