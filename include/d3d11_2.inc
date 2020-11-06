ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
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

ifndef __d3d11_2_h__
__d3d11_2_h__ equ <>

ifndef __ID3D11DeviceContext2_FWD_DEFINED__
__ID3D11DeviceContext2_FWD_DEFINED__ equ 1
endif
ifndef __ID3D11Device2_FWD_DEFINED__
__ID3D11Device2_FWD_DEFINED__ equ 1
endif

include oaidl.inc
include ocidl.inc
include dxgi1_3.inc
include d3dcommon.inc
include d3d11_1.inc

D3D11_TILED_RESOURCE_COORDINATE STRUC
X			UINT ?
Y			UINT ?
Z			UINT ?
Subresource		UINT ?
D3D11_TILED_RESOURCE_COORDINATE ENDS

D3D11_TILE_REGION_SIZE	STRUC
NumTiles		UINT ?
bUseBox			BOOL ?
Width			UINT ?
Height			UINT16 ?
Depth			UINT16 ?
D3D11_TILE_REGION_SIZE	ENDS

.enum D3D11_TILE_MAPPING_FLAG {
    D3D11_TILE_MAPPING_NO_OVERWRITE	= 0x1
    }

.enum D3D11_TILE_RANGE_FLAG {
    D3D11_TILE_RANGE_NULL	= 0x1,
    D3D11_TILE_RANGE_SKIP	= 0x2,
    D3D11_TILE_RANGE_REUSE_SINGLE_TILE	= 0x4
    }

D3D11_SUBRESOURCE_TILING STRUC
WidthInTiles		UINT ?
HeightInTiles		UINT16 ?
DepthInTiles		UINT16 ?
StartTileIndexInOverallResource UINT ?
D3D11_SUBRESOURCE_TILING ENDS

D3D11_PACKED_TILE	equ ( 0xffffffff )

D3D11_TILE_SHAPE	STRUC
WidthInTexels		UINT ?
HeightInTexels		UINT ?
DepthInTexels		UINT ?
D3D11_TILE_SHAPE	ENDS

D3D11_PACKED_MIP_DESC	STRUC
NumStandardMips		UINT8 ?
NumPackedMips		UINT8 ?
NumTilesForPackedMips	UINT ?
StartTileIndexInOverallResource UINT ?
D3D11_PACKED_MIP_DESC	ENDS

.enum D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_FLAG {
    D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_TILED_RESOURCE	= 0x1
    }

.enum D3D11_TILE_COPY_FLAG {
    D3D11_TILE_COPY_NO_OVERWRITE	= 0x1,
    D3D11_TILE_COPY_LINEAR_BUFFER_TO_SWIZZLED_TILED_RESOURCE	= 0x2,
    D3D11_TILE_COPY_SWIZZLED_TILED_RESOURCE_TO_LINEAR_BUFFER	= 0x4
    }

ifndef __ID3D11DeviceContext2_INTERFACE_DEFINED__
__ID3D11DeviceContext2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ID3D11DeviceContext2, "420d5b32-b90c-4da4-bef0-359f6a24a83a")

.comdef ID3D11DeviceContext2 : public ID3D11DeviceContext1

    UpdateTileMappings	proc :ptr, :UINT, :ptr, :ptr, :UINT, :ptr
    CopyTileMappings	proc :ptr, :ptr, :ptr, :ptr, :ptr, :UINT
    CopyTiles		proc :ptr, :ptr, :ptr, :ptr, :UINT64, :UINT
    UpdateTiles		proc :ptr, :ptr, :ptr, :ptr, :UINT
    ResizeTilePool	proc :ptr, :UINT64
    TiledResourceBarrier proc :ptr, :ptr
    IsAnnotationEnabled proc
    SetMarkerInt	proc :LPCWSTR, :int_t
    BeginEventInt	proc :LPCWSTR, :int_t
    EndEvent		proc

    .ends

endif


ifndef __ID3D11Device2_INTERFACE_DEFINED__
__ID3D11Device2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ID3D11Device2, "9d06dffa-d1e5-4d07-83a8-1bb123f2f841")

.comdef ID3D11Device2 : public ID3D11Device1

    GetImmediateContext2 proc :ptr
    CreateDeferredContext2 proc :UINT, :ptr
    GetResourceTiling	proc :ptr, :ptr, :ptr, :ptr, :ptr, :UINT, :ptr
    CheckMultisampleQualityLevels1 proc :DXGI_FORMAT, :UINT, :UINT, :ptr

    .ends

endif

endif
