ifdef  __D3DX11_INTERNAL__
.err <Incorrect D3DX11 header used>
endif

ifndef __D3DX11_H__
define __D3DX11_H__

include limits.inc
include float.inc

ifdef ALLOW_THROWING_NEW
;include neinc
endif

D3DX11_DEFAULT		equ (-1)
D3DX11_FROM_FILE	equ (-3)
DXGI_FORMAT_FROM_FILE	equ (-3)

ifndef D3DX11INLINE
ifdef _MSC_VER
if (_MSC_VER GE 1200)
D3DX11INLINE		equ <__forceinline>
else
D3DX11INLINE		equ <__inline>
endif
else
ifdef __cplusplus
D3DX11INLINE		equ <inline>
else
D3DX11INLINE		equ <>
endif
endif
endif

include d3d11.inc
include d3dx11.inc
include d3dx11core.inc
include d3dx11tex.inc
include d3dx11async.inc

_FACDD equ 0x876
MAKE_DDHRESULT macro code
	exitm<MAKE_HRESULT( 1, _FACDD, code )>
	endm

.enum D3DX11_ERR {
    D3DX11_ERR_CANNOT_MODIFY_INDEX_BUFFER	= MAKE_DDHRESULT(2900),
    D3DX11_ERR_INVALID_MESH			= MAKE_DDHRESULT(2901),
    D3DX11_ERR_CANNOT_ATTR_SORT			= MAKE_DDHRESULT(2902),
    D3DX11_ERR_SKINNING_NOT_SUPPORTED		= MAKE_DDHRESULT(2903),
    D3DX11_ERR_TOO_MANY_INFLUENCES		= MAKE_DDHRESULT(2904),
    D3DX11_ERR_INVALID_DATA			= MAKE_DDHRESULT(2905),
    D3DX11_ERR_LOADED_MESH_HAS_NO_DATA		= MAKE_DDHRESULT(2906),
    D3DX11_ERR_DUPLICATE_NAMED_FRAGMENT		= MAKE_DDHRESULT(2907),
    D3DX11_ERR_CANNOT_REMOVE_LAST_ITEM		= MAKE_DDHRESULT(2908),
    }


endif
