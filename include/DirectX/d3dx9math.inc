include d3dx9.inc
ifndef __D3DX9MATH_H__
define __D3DX9MATH_H__
include math.inc
.pragma comment(lib, d3dx9_40)

D3DX_PI			equ 3.141592654
D3DX_1BYPI		equ 0.318309886

D3DXSH_MINORDER		equ 2
D3DXSH_MAXORDER		equ 6

D3DXToRadian macro degree
	exitm<((degree) * (D3DX_PI / 180.0))>
	endm
D3DXToDegree macro radian
	exitm<((radian) * (180.0 / D3DX_PI))>
	endm

D3DXVECTOR2		STRUC
x			FLOAT ?
y			FLOAT ?
D3DXVECTOR2		ENDS
LPD3DXVECTOR2		typedef ptr D3DXVECTOR2

D3DXVECTOR3		typedef D3DVECTOR
LPD3DXVECTOR3		typedef ptr D3DVECTOR

D3DXVECTOR4		STRUC
x			FLOAT ?
y			FLOAT ?
z			FLOAT ?
w			FLOAT ?
D3DXVECTOR4		ENDS
LPD3DXVECTOR4		typedef ptr D3DXVECTOR4

D3DXMATRIX		typedef D3DMATRIX
LPD3DXMATRIX		typedef ptr D3DMATRIX

D3DXQUATERNION		STRUC
x			FLOAT ?
y			FLOAT ?
z			FLOAT ?
w			FLOAT ?
D3DXQUATERNION		ENDS
LPD3DXQUATERNION	typedef ptr D3DXQUATERNION

D3DXPLANE		STRUC
a			FLOAT ?
b			FLOAT ?
_c			FLOAT ?
d			FLOAT ?
D3DXPLANE		ENDS
LPD3DXPLANE		typedef ptr D3DXPLANE

D3DXCOLOR		STRUC
r			FLOAT ?
g			FLOAT ?
b			FLOAT ?
a			FLOAT ?
D3DXCOLOR		ENDS
LPD3DXCOLOR		typedef ptr D3DXCOLOR

D3DXFLOAT16		STRUC
value			dw ?
D3DXFLOAT16		ENDS
LPD3DXFLOAT16		typedef ptr D3DXFLOAT16

D3DXColorAdjustContrast proto WINAPI :ptr, :ptr, :FLOAT
D3DXColorAdjustSaturation proto WINAPI :ptr, :ptr, :FLOAT
D3DXFresnelTerm proto WINAPI :FLOAT, :FLOAT
D3DXMatrixAffineTransformation proto WINAPI :ptr, :FLOAT, :ptr, :ptr, :ptr
D3DXMatrixAffineTransformation2D proto WINAPI :ptr, :FLOAT, :ptr, :FLOAT, :ptr
D3DXMatrixDecompose proto WINAPI :ptr, :ptr, :ptr, :ptr
D3DXMatrixDeterminant proto WINAPI :ptr
D3DXMatrixInverse proto WINAPI :ptr, :ptr, :ptr
D3DXMatrixLookAtLH proto WINAPI :ptr, :ptr, :ptr, :ptr
D3DXMatrixLookAtRH proto WINAPI :ptr, :ptr, :ptr, :ptr
D3DXMatrixMultiply proto WINAPI :ptr, :ptr, :ptr
D3DXMatrixMultiplyTranspose proto WINAPI :ptr, :ptr, :ptr
D3DXMatrixOrthoLH proto WINAPI :ptr, :FLOAT, :FLOAT, :FLOAT, :FLOAT
D3DXMatrixOrthoOffCenterLH proto WINAPI :ptr, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT
D3DXMatrixOrthoOffCenterRH proto WINAPI :ptr, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT
D3DXMatrixOrthoRH proto WINAPI :ptr, :FLOAT, :FLOAT, :FLOAT, :FLOAT
D3DXMatrixPerspectiveFovLH proto WINAPI :ptr, :FLOAT, :FLOAT, :FLOAT, :FLOAT
D3DXMatrixPerspectiveFovRH proto WINAPI :ptr, :FLOAT, :FLOAT, :FLOAT, :FLOAT
D3DXMatrixPerspectiveLH proto WINAPI :ptr, :FLOAT, :FLOAT, :FLOAT, :FLOAT
D3DXMatrixPerspectiveOffCenterLH proto WINAPI :ptr, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT
D3DXMatrixPerspectiveOffCenterRH proto WINAPI :ptr, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT
D3DXMatrixPerspectiveRH proto WINAPI :ptr, :FLOAT, :FLOAT, :FLOAT, :FLOAT
D3DXMatrixReflect proto WINAPI :ptr, :ptr
D3DXMatrixRotationAxis proto WINAPI :ptr, :ptr, :FLOAT
D3DXMatrixRotationQuaternion proto WINAPI :ptr, :ptr
D3DXMatrixRotationX proto WINAPI :ptr, :FLOAT
D3DXMatrixRotationY proto WINAPI :ptr, :FLOAT
D3DXMatrixRotationYawPitchRoll proto WINAPI :ptr, :FLOAT, :FLOAT, :FLOAT
D3DXMatrixRotationZ proto WINAPI :ptr, :FLOAT
D3DXMatrixScaling proto WINAPI :ptr, :FLOAT, :FLOAT, :FLOAT
D3DXMatrixShadow proto WINAPI :ptr, :ptr, :ptr
D3DXMatrixTransformation proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DXMatrixTransformation2D proto WINAPI :ptr, :ptr, :FLOAT, :ptr, :ptr, :FLOAT, :ptr
D3DXMatrixTranslation proto WINAPI :ptr, :FLOAT, :FLOAT, :FLOAT
D3DXMatrixTranspose proto WINAPI :ptr, :ptr
D3DXPlaneFromPointNormal proto WINAPI :ptr, :ptr, :ptr
D3DXPlaneFromPoints proto WINAPI :ptr, :ptr, :ptr, :ptr
D3DXPlaneIntersectLine proto WINAPI :ptr, :ptr, :ptr, :ptr
D3DXPlaneNormalize proto WINAPI :ptr, :ptr
D3DXPlaneTransform proto WINAPI :ptr, :ptr, :ptr
D3DXPlaneTransformArray proto WINAPI :ptr, :UINT, :ptr, :UINT, :ptr, :UINT
D3DXQuaternionBaryCentric proto WINAPI :ptr, :ptr, :ptr, :ptr, :FLOAT, :FLOAT
D3DXQuaternionExp proto WINAPI :ptr, :ptr
D3DXQuaternionInverse proto WINAPI :ptr, :ptr
D3DXQuaternionLn proto WINAPI :ptr, :ptr
D3DXQuaternionMultiply proto WINAPI :ptr, :ptr, :ptr
D3DXQuaternionNormalize proto WINAPI :ptr, :ptr
D3DXQuaternionRotationAxis proto WINAPI :ptr, :ptr, :FLOAT
D3DXQuaternionRotationMatrix proto WINAPI :ptr, :ptr
D3DXQuaternionRotationYawPitchRoll proto WINAPI :ptr, :FLOAT, :FLOAT, :FLOAT
D3DXQuaternionSlerp proto WINAPI :ptr, :ptr, :ptr, :FLOAT
D3DXQuaternionSquad proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :FLOAT
D3DXQuaternionSquadSetup proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DXQuaternionToAxisAngle proto WINAPI :ptr, :ptr, :ptr
D3DXVec2BaryCentric proto WINAPI :ptr, :ptr, :ptr, :ptr, :FLOAT, :FLOAT
D3DXVec2CatmullRom proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :FLOAT
D3DXVec2Hermite proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :FLOAT
D3DXVec2Normalize proto WINAPI :ptr, :ptr
D3DXVec2Transform proto WINAPI :ptr, :ptr, :ptr
D3DXVec2TransformArray proto WINAPI :ptr, :UINT, :ptr, :UINT, :ptr, :UINT
D3DXVec2TransformCoord proto WINAPI :ptr, :ptr, :ptr
D3DXVec2TransformCoordArray proto WINAPI :ptr, :UINT, :ptr, :UINT, :ptr, :UINT
D3DXVec2TransformNormal proto WINAPI :ptr, :ptr, :ptr
D3DXVec2TransformNormalArray proto WINAPI :ptr, :UINT, :ptr, :UINT, :ptr, :UINT
D3DXVec3BaryCentric proto WINAPI :ptr, :ptr, :ptr, :ptr, :FLOAT, :FLOAT
D3DXVec3CatmullRom proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :FLOAT
D3DXVec3Hermite proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :FLOAT
D3DXVec3Normalize proto WINAPI :ptr, :ptr
D3DXVec3Project proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DXVec3ProjectArray proto WINAPI :ptr, :UINT, :ptr, :UINT, :ptr, :ptr, :ptr, :ptr, :UINT
D3DXVec3Transform proto WINAPI :ptr, :ptr, :ptr
D3DXVec3TransformArray proto WINAPI :ptr, :UINT, :ptr, :UINT, :ptr, :UINT
D3DXVec3TransformCoord proto WINAPI :ptr, :ptr, :ptr
D3DXVec3TransformCoordArray proto WINAPI :ptr, :UINT, :ptr, :UINT, :ptr, :UINT
D3DXVec3TransformNormal proto WINAPI :ptr, :ptr, :ptr
D3DXVec3TransformNormalArray proto WINAPI :ptr, :UINT, :ptr, :UINT, :ptr, :UINT
D3DXVec3Unproject proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
D3DXVec3UnprojectArray proto WINAPI :ptr, :UINT, :ptr, :UINT, :ptr, :ptr, :ptr, :ptr, :UINT
D3DXVec4BaryCentric proto WINAPI :ptr, :ptr, :ptr, :ptr, :FLOAT, :FLOAT
D3DXVec4CatmullRom proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :FLOAT
D3DXVec4Cross proto WINAPI :ptr, :ptr, :ptr, :ptr
D3DXVec4Hermite proto WINAPI :ptr, :ptr, :ptr, :ptr, :ptr, :FLOAT
D3DXVec4Normalize proto WINAPI :ptr, :ptr
D3DXVec4Transform proto WINAPI :ptr, :ptr, :ptr
D3DXVec4TransformArray proto WINAPI :ptr, :UINT, :ptr, :UINT, :ptr, :UINT
D3DXFloat32To16Array proto WINAPI :ptr, :ptr, :UINT
D3DXFloat16To32Array proto WINAPI :ptr, :ptr, :UINT
D3DXSHAdd proto WINAPI :ptr, :UINT, :ptr, :ptr
D3DXSHDot proto WINAPI :UINT, :ptr, :ptr
D3DXSHEvalConeLight proto WINAPI :UINT, :ptr, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :ptr, :ptr, :ptr
D3DXSHEvalDirection proto WINAPI :ptr, :UINT, :ptr
D3DXSHEvalDirectionalLight proto WINAPI :UINT, :ptr, :FLOAT, :FLOAT, :FLOAT, :ptr, :ptr, :ptr
D3DXSHEvalHemisphereLight proto WINAPI :UINT, :ptr, :D3DXCOLOR, :D3DXCOLOR, :ptr, :ptr, :ptr
D3DXSHEvalSphericalLight proto WINAPI :UINT, :ptr, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :ptr, :ptr, :ptr
D3DXSHMultiply2 proto WINAPI :ptr, :ptr, :ptr
D3DXSHMultiply3 proto WINAPI :ptr, :ptr, :ptr
D3DXSHMultiply4 proto WINAPI :ptr, :ptr, :ptr
D3DXSHRotate proto WINAPI :ptr, :UINT, :ptr, :ptr
D3DXSHRotateZ proto WINAPI :ptr, :UINT, :FLOAT, :ptr
D3DXSHScale proto WINAPI :ptr, :UINT, :ptr, :FLOAT

DEFINE_GUID(IID_ID3DXMatrixStack, 0xc7885ba7, 0xf990, 0x4fe7, 0x92, 0x2d, 0x85, 0x15, 0xe4, 0x77, 0xdd, 0x85);

.comdef ID3DXMatrixStack : public IUnknown

    _Pop			proc
    _Push			proc
    LoadIdentity		proc
    LoadMatrix			proc :ptr D3DXMATRIX
    MultMatrix			proc :ptr D3DXMATRIX
    MultMatrixLocal		proc :ptr D3DXMATRIX
    RotateAxis			proc :ptr D3DXVECTOR3, :FLOAT
    RotateAxisLocal		proc
    RotateYawPitchRoll		proc :FLOAT, :FLOAT, :FLOAT
    RotateYawPitchRollLocal	proc :FLOAT, :FLOAT, :FLOAT
    Scale			proc :FLOAT, :FLOAT, :FLOAT
    ScaleLocal			proc :FLOAT, :FLOAT, :FLOAT
    Translate			proc :FLOAT, :FLOAT, :FLOAT
    TranslateLocal		proc :FLOAT, :FLOAT, :FLOAT
    GetTop			proc :ptr D3DXMATRIX
   .ends

D3DXCreateMatrixStack proto WINAPI :DWORD, :ptr

D3DXMatrixIdentity proto fastcall :ptr D3DMATRIX {
    mov [rcx].D3DMATRIX._12,0.0
    mov [rcx].D3DMATRIX._13,0.0
    mov [rcx].D3DMATRIX._14,0.0
    mov [rcx].D3DMATRIX._21,0.0
    mov [rcx].D3DMATRIX._23,0.0
    mov [rcx].D3DMATRIX._24,0.0
    mov [rcx].D3DMATRIX._31,0.0
    mov [rcx].D3DMATRIX._32,0.0
    mov [rcx].D3DMATRIX._34,0.0
    mov [rcx].D3DMATRIX._41,0.0
    mov [rcx].D3DMATRIX._42,0.0
    mov [rcx].D3DMATRIX._43,0.0
    mov [rcx].D3DMATRIX._11,1.0
    mov [rcx].D3DMATRIX._22,1.0
    mov [rcx].D3DMATRIX._33,1.0
    mov [rcx].D3DMATRIX._44,1.0
    }

endif
