ifndef __D3DX9_H__
__D3DX9_H__ equ <>
.pragma list(push, 0)
include limits.inc

D3DX_DEFAULT		equ (-1)
D3DX_DEFAULT_NONPOW2	equ (-2)
D3DX_DEFAULT_FLOAT	equ FT_MAX
D3DX_FROM_FILE		equ (-3)
D3DFMT_FROM_FILE	equ (-3)

.pragma pack(push,8)

include d3d9.inc
.pragma comment(lib, d3dx9_40)

include d3dx9math.inc
include d3dx9core.inc
include d3dx9xof.inc
include d3dx9mesh.inc
include d3dx9shader.inc
include d3dx9effect.inc
include d3dx9shape.inc
include d3dx9anim.inc
include d3dx9tex.inc

.pragma pack(pop)

_FACDD	equ 0x876
MAKE_DDHRESULT macro code
	exitm<MAKE_HRESULT(1, _FACDD, code)>
	endm

_D3DXERR typedef sdword
D3DXERR_CANNOTMODIFYINDEXBUFFER equ MAKE_DDHRESULT(2900)
D3DXERR_INVALIDMESH		equ MAKE_DDHRESULT(2901)
D3DXERR_CANNOTATTRSORT		equ MAKE_DDHRESULT(2902)
D3DXERR_SKINNINGNOTSUPPORTED	equ MAKE_DDHRESULT(2903)
D3DXERR_TOOMANYINFLUENCES	equ MAKE_DDHRESULT(2904)
D3DXERR_INVALIDDATA		equ MAKE_DDHRESULT(2905)
D3DXERR_LOADEDMESHASNODATA	equ MAKE_DDHRESULT(2906)
D3DXERR_DUPLICATENAMEDFRAGMENT	equ MAKE_DDHRESULT(2907)
D3DXERR_CANNOTREMOVELASTITEM	equ MAKE_DDHRESULT(2908)

.pragma list(pop)
endif
