include d3dx10.inc

ifndef __D3DX9MATH_H__
define __D3DX9MATH_H__

include math.inc

ifndef D3DVECTOR_DEFINED
define D3DVECTOR_DEFINED
.template D3DVECTOR
    x	float ?
    y	float ?
    z	float ?
    .static D3DVECTOR :abs=<0.0>, :abs=<0.0>, :abs=<0.0> {
	mov this.x,_1
	mov this.y,_2
	mov this.z,_3
	}
    .ENDS
endif

ifndef D3DMATRIX_DEFINED
D3DMATRIX		STRUC
UNION
STRUC
_11			float ?
_12			float ?
_13			float ?
_14			float ?
_21			float ?
_22			float ?
_23			float ?
_24			float ?
_31			float ?
_32			float ?
_33			float ?
_34			float ?
_41			float ?
_42			float ?
_43			float ?
_44			float ?
ENDS
m			float 4 dup(?)
ENDS
D3DMATRIX		ENDS
D3DMATRIX_DEFINED equ 1
endif

D3DX_PI			equ (3.14159265358979323846)
D3DX_1BYPI		equ ( 1.0 / D3DX_PI )

D3DXToRadian macro degree
	exitm<((degree) * (D3DX_PI / 180.0))>
	endm
D3DXToDegree macro radian
	exitm<((radian) * (180.0 / D3DX_PI))>
	endm


D3DX_16F_DIG		equ 3
D3DX_16F_EPSILON	equ 4.8875809e-4
D3DX_16F_MANT_DIG	equ 11
D3DX_16F_MAX		equ 6.550400e+004
D3DX_16F_MAX_10_EXP	equ 4
D3DX_16F_MAX_EXP	equ 15
D3DX_16F_MIN		equ 6.1035156e-5
D3DX_16F_MIN_10_EXP	equ (-4)
D3DX_16F_MIN_EXP	equ (-14)
D3DX_16F_RADIX		equ 2
D3DX_16F_ROUNDS		equ 1
D3DX_16F_SIGN_MASK	equ 0x8000
D3DX_16F_EXP_MASK	equ 0x7C00
D3DX_16F_FRAC_MASK	equ 0x03FF

D3DXFLOAT16		STRUC
ifdef __cplusplus
endif
value			dw ?
D3DXFLOAT16		ENDS
LPD3DXFLOAT16		typedef ptr D3DXFLOAT16

D3DXVECTOR2		STRUC
ifdef __cplusplus
endif
x			FLOAT ?
y			FLOAT ?
D3DXVECTOR2		ENDS
LPD3DXVECTOR2		typedef ptr D3DXVECTOR2

D3DXVECTOR2_16F		STRUC
ifdef __cplusplus
endif
x			D3DXFLOAT16 <>
y			D3DXFLOAT16 <>
D3DXVECTOR2_16F		ENDS
LPD3DXVECTOR2_16F	typedef ptr D3DXVECTOR2_16F

ifdef __cplusplus
else
D3DXVECTOR3		typedef D3DVECTOR
LPD3DXVECTOR3		typedef ptr D3DVECTOR
endif

D3DXVECTOR3_16F		STRUC
ifdef __cplusplus
endif
x			D3DXFLOAT16 <>
y			D3DXFLOAT16 <>
z			D3DXFLOAT16 <>
D3DXVECTOR3_16F		ENDS
LPD3DXVECTOR3_16F	typedef ptr D3DXVECTOR3_16F

D3DXVECTOR4		STRUC
ifdef __cplusplus
endif
x			FLOAT ?
y			FLOAT ?
z			FLOAT ?
w			FLOAT ?
D3DXVECTOR4		ENDS
LPD3DXVECTOR4		typedef ptr D3DXVECTOR4

D3DXVECTOR4_16F		STRUC
ifdef __cplusplus
endif
x			D3DXFLOAT16 <>
y			D3DXFLOAT16 <>
z			D3DXFLOAT16 <>
w			D3DXFLOAT16 <>
D3DXVECTOR4_16F		ENDS
LPD3DXVECTOR4_16F	typedef ptr D3DXVECTOR4_16F


ifdef __cplusplus
else
D3DXMATRIX		typedef D3DMATRIX
LPD3DXMATRIX		typedef ptr D3DMATRIX
endif


ifdef __cplusplus
else
_D3DXMATRIXA16		typedef D3DXMATRIX
endif

if _MSC_VER GE 1300
D3DX_ALIGN16		equ <>;__declspec(align(16))>
else
D3DX_ALIGN16		equ <>
endif

LPD3DXMATRIXA16		typedef ptr D3DX_ALIGN16
;_D3DXMATRIXA16		 typedef D3DX_ALIGN16
;D3DXMATRIXA16		 typedef D3DX_ALIGN16

D3DXQUATERNION		STRUC
ifdef __cplusplus
endif
x			FLOAT ?
y			FLOAT ?
z			FLOAT ?
w			FLOAT ?
D3DXQUATERNION		ENDS
LPD3DXQUATERNION	typedef ptr D3DXQUATERNION

D3DXPLANE		STRUC
ifdef __cplusplus
endif
a			FLOAT ?
b			FLOAT ?
c			FLOAT ?
d			FLOAT ?
D3DXPLANE		ENDS
LPD3DXPLANE		typedef ptr D3DXPLANE

D3DXCOLOR		STRUC
ifdef __cplusplus
endif
r			FLOAT ?
g			FLOAT ?
b			FLOAT ?
a			FLOAT ?
D3DXCOLOR		ENDS
LPD3DXCOLOR		typedef ptr D3DXCOLOR

D3DXFloat16To32Array proto WINAPI :ptr, :ptr, :UINT
D3DXVec2Length proto WINAPI :ptr
D3DXVec2LengthSq proto WINAPI :ptr
D3DXVec2Dot proto WINAPI :ptr, :ptr
D3DXVec2CCW proto WINAPI :ptr, :ptr
D3DXVec3Length proto WINAPI :ptr
D3DXVec3LengthSq proto WINAPI :ptr
D3DXVec3Dot proto WINAPI :ptr, :ptr
D3DXVec4Length proto WINAPI :ptr
D3DXVec4LengthSq proto WINAPI :ptr
D3DXVec4Dot proto WINAPI :ptr, :ptr
D3DXMatrixIsIdentity proto WINAPI :ptr
D3DXMatrixDeterminant proto WINAPI :ptr
D3DXMatrixDecompose proto WINAPI :ptr, :ptr, :ptr, :ptr
D3DXQuaternionLength proto WINAPI :ptr
D3DXQuaternionLengthSq proto WINAPI :ptr
D3DXQuaternionDot proto WINAPI :ptr, :ptr
D3DXQuaternionToAxisAngle proto WINAPI :ptr, :ptr, :ptr
D3DXQuaternionSquadSetup proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DXPlaneDot proto WINAPI :ptr, :ptr
D3DXPlaneDotCoord proto WINAPI :ptr, :ptr
D3DXPlaneDotNormal proto WINAPI :ptr, :ptr
D3DXFresnelTerm proto WINAPI :FLOAT, :FLOAT

DEFINE_GUID(IID_ID3DXMatrixStack, 0xc7885ba7, 0xf990, 0x4fe7, 0x92, 0x2d, 0x85, 0x15, 0xe4, 0x77, 0xdd, 0x85)

.comdef ID3DXMatrixStack :public IUnknown

    _Pop		proc
    _Push		proc
    LoadIdentity	proc
    LoadMatrix		proc :ptr D3DXMATRIX
    MultMatrix		proc :ptr D3DXMATRIX
    MultMatrixLocal	proc :ptr D3DXMATRIX
    RotateAxis		proc :ptr D3DXVECTOR3, :FLOAT
    RotateAxisLocal	proc :ptr D3DXVECTOR3, :FLOAT
    RotateYawPitchRoll	proc :FLOAT, :FLOAT, :FLOAT
    RotateYawPitchRollLocal proc :FLOAT, :FLOAT, :FLOAT
    Scale		proc :FLOAT, :FLOAT, :FLOAT
    ScaleLocal		proc :FLOAT, :FLOAT, :FLOAT
    Translate		proc :FLOAT, :FLOAT, :FLOAT
    TranslateLocal	proc :FLOAT, :FLOAT, :FLOAT
    GetTop		proc
   .ENDS

D3DXCreateMatrixStack proto WINAPI :UINT, :ptr

D3DXSH_MINORDER		equ 2
D3DXSH_MAXORDER		equ 6

D3DXSHEvalDirection proto WINAPI :ptr, :UINT, :ptr
D3DXSHRotate proto WINAPI :ptr, :UINT, :ptr, :ptr
D3DXSHRotateZ proto WINAPI :ptr, :UINT, :FLOAT, :ptr
D3DXSHAdd proto WINAPI :ptr, :UINT, :ptr, :ptr
D3DXSHScale proto WINAPI :ptr, :UINT, :ptr, :FLOAT
D3DXSHDot proto WINAPI :UINT, :ptr, :ptr

D3DXSHMultiply2 proto WINAPI :ptr, :ptr, :ptr
D3DXSHMultiply3 proto WINAPI :ptr, :ptr, :ptr
D3DXSHMultiply4 proto WINAPI :ptr, :ptr, :ptr
D3DXSHMultiply5 proto WINAPI :ptr, :ptr, :ptr
D3DXSHMultiply6 proto WINAPI :ptr, :ptr, :ptr

D3DXSHEvalDirectionalLight proto WINAPI :UINT, :ptr, :FLOAT, :FLOAT, :FLOAT, :ptr, :ptr, :ptr
D3DXSHEvalSphericalLight proto WINAPI :UINT, :ptr, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :ptr, :ptr, :ptr
D3DXSHEvalConeLight proto WINAPI :UINT, :ptr, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :ptr, :ptr, :ptr
D3DXSHEvalHemisphereLight proto WINAPI :UINT, :ptr, :D3DXCOLOR, :D3DXCOLOR, :ptr, :ptr, :ptr
D3DXIntersectTri proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DXSphereBoundProbe proto WINAPI :ptr, :FLOAT, :ptr, :ptr
D3DXBoxBoundProbe proto WINAPI :ptr, :ptr, :ptr, :ptr
D3DXComputeBoundingSphere proto WINAPI :ptr, :DWORD, :DWORD, :ptr, :ptr

D3DXComputeBoundingBox proto WINAPI :ptr, :DWORD, :DWORD, :ptr, :ptr

.enum D3DX_CPU_OPTIMIZATION {
    D3DX_NOT_OPTIMIZED = 0,
    D3DX_3DNOW_OPTIMIZED,
    D3DX_SSE2_OPTIMIZED,
    D3DX_SSE_OPTIMIZED
    }

include d3dx10math.inl

endif
