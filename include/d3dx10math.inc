include d3dx10.inc

ifndef __D3DX9MATH_H__
__D3DX9MATH_H__ equ <>

include math.inc

ifndef D3DVECTOR_DEFINED
D3DVECTOR_DEFINED equ <>
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


D3DXFloat16To32Array proto WINAPI \
		  pOut: ptr FLOAT,
		   pIn: ptr D3DXFLOAT16,
		     n: UINT


D3DXVec2Length proto WINAPI \
		    pV: ptr D3DXVECTOR2


D3DXVec2LengthSq proto WINAPI \
		    pV: ptr D3DXVECTOR2


D3DXVec2Dot proto WINAPI \
		   pV1: ptr D3DXVECTOR2,
		   pV2: ptr D3DXVECTOR2


D3DXVec2CCW proto WINAPI \
		   pV1: ptr D3DXVECTOR2,
		   pV2: ptr D3DXVECTOR2


D3DXVec3Length proto WINAPI \
		    pV: ptr D3DXVECTOR3


D3DXVec3LengthSq proto WINAPI \
		    pV: ptr D3DXVECTOR3


D3DXVec3Dot proto WINAPI \
		   pV1: ptr D3DXVECTOR3,
		   pV2: ptr D3DXVECTOR3


D3DXVec4Length proto WINAPI \
		    pV: ptr D3DXVECTOR4

D3DXVec4LengthSq proto WINAPI \
		    pV: ptr D3DXVECTOR4

D3DXVec4Dot proto WINAPI \
		   pV1: ptr D3DXVECTOR4,
		   pV2: ptr D3DXVECTOR4


D3DXMatrixIsIdentity proto WINAPI \
		    pM: ptr D3DXMATRIX


D3DXMatrixDeterminant proto WINAPI \
		    pM: ptr D3DXMATRIX


D3DXMatrixDecompose proto WINAPI \
	     pOutScale: ptr D3DXVECTOR3,
	  pOutRotation: ptr D3DXQUATERNION,
       pOutTranslation: ptr D3DXVECTOR3,
		    pM: ptr D3DXMATRIX


D3DXQuaternionLength proto WINAPI \
		    pQ: ptr D3DXQUATERNION


D3DXQuaternionLengthSq proto WINAPI \
		    pQ: ptr D3DXQUATERNION


D3DXQuaternionDot proto WINAPI \
		   pQ1: ptr D3DXQUATERNION,
		   pQ2: ptr D3DXQUATERNION


D3DXQuaternionToAxisAngle proto WINAPI \
		    pQ: ptr D3DXQUATERNION,
		 pAxis: ptr D3DXVECTOR3,
		pAngle: ptr FLOAT


D3DXQuaternionSquadSetup proto WINAPI \
		 pAOut: ptr D3DXQUATERNION,
		 pBOut: ptr D3DXQUATERNION,
		 pCOut: ptr D3DXQUATERNION,
		   pQ0: ptr D3DXQUATERNION,
		   pQ1: ptr D3DXQUATERNION,
		   pQ2: ptr D3DXQUATERNION,
		   pQ3: ptr D3DXQUATERNION


D3DXPlaneDot proto WINAPI \
		    pP: ptr D3DXPLANE,
		    pV: ptr D3DXVECTOR4

D3DXPlaneDotCoord proto WINAPI \
		    pP: ptr D3DXPLANE,
		    pV: ptr D3DXVECTOR3

D3DXPlaneDotNormal proto WINAPI \
		    pP: ptr D3DXPLANE,
		    pV: ptr D3DXVECTOR3


D3DXFresnelTerm proto WINAPI \
	      CosTheta: FLOAT,
       RefractionIndex: FLOAT


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

D3DXCreateMatrixStack proto WINAPI \
		 Flags: UINT,
	       ppStack: ptr LPD3DXMATRIXSTACK


D3DXSH_MINORDER		equ 2
D3DXSH_MAXORDER		equ 6

D3DXSHEvalDirection proto WINAPI \
		  pOut: ptr FLOAT,
		 Order: UINT,
		  pDir: ptr D3DXVECTOR3

D3DXSHRotate proto WINAPI \
		  pOut: ptr FLOAT,
		 Order: UINT,
	       pMatrix: ptr D3DXMATRIX,
		   pIn: ptr FLOAT

D3DXSHRotateZ proto WINAPI \
		  pOut: ptr FLOAT,
		 Order: UINT,
		 Angle: FLOAT,
		   pIn: ptr FLOAT

D3DXSHAdd proto WINAPI \
		  pOut: ptr FLOAT,
		 Order: UINT,
		    pA: ptr FLOAT,
		    pB: ptr FLOAT

D3DXSHScale proto WINAPI \
		  pOut: ptr FLOAT,
		 Order: UINT,
		   pIn: ptr FLOAT,
		 Scale: FLOAT

D3DXSHDot proto WINAPI \
		 Order: UINT,
		    pA: ptr FLOAT,
		    pB: ptr FLOAT


D3DXSHMultiply2 proto WINAPI :ptr FLOAT, :ptr FLOAT, :ptr FLOAT
D3DXSHMultiply3 proto WINAPI :ptr FLOAT, :ptr FLOAT, :ptr FLOAT
D3DXSHMultiply4 proto WINAPI :ptr FLOAT, :ptr FLOAT, :ptr FLOAT
D3DXSHMultiply5 proto WINAPI :ptr FLOAT, :ptr FLOAT, :ptr FLOAT
D3DXSHMultiply6 proto WINAPI :ptr FLOAT, :ptr FLOAT, :ptr FLOAT


D3DXSHEvalDirectionalLight proto WINAPI \
		 Order: UINT,
		  pDir: ptr D3DXVECTOR3,
	    RIntensity: FLOAT,
	    GIntensity: FLOAT,
	    BIntensity: FLOAT,
		 pROut: ptr FLOAT,
		 pGOut: ptr FLOAT,
		 pBOut: ptr FLOAT

D3DXSHEvalSphericalLight proto WINAPI \
		 Order: UINT,
		  pPos: ptr D3DXVECTOR3,
		Radius: FLOAT,
	    RIntensity: FLOAT,
	    GIntensity: FLOAT,
	    BIntensity: FLOAT,
		 pROut: ptr FLOAT,
		 pGOut: ptr FLOAT,
		 pBOut: ptr FLOAT

D3DXSHEvalConeLight proto WINAPI \
		 Order: UINT,
		  pDir: ptr D3DXVECTOR3,
		Radius: FLOAT,
	    RIntensity: FLOAT,
	    GIntensity: FLOAT,
	    BIntensity: FLOAT,
		 pROut: ptr FLOAT,
		 pGOut: ptr FLOAT,
		 pBOut: ptr FLOAT

D3DXSHEvalHemisphereLight proto WINAPI \
		 Order: UINT,
		  pDir: ptr D3DXVECTOR3,
		   Top: D3DXCOLOR,
		Bottom: D3DXCOLOR,
		 pROut: ptr FLOAT,
		 pGOut: ptr FLOAT,
		 pBOut: ptr FLOAT


D3DXIntersectTri proto WINAPI \
		    p0: ptr D3DXVECTOR3,
		    p1: ptr D3DXVECTOR3,
		    p2: ptr D3DXVECTOR3,
	       pRayPos: ptr D3DXVECTOR3,
	       pRayDir: ptr D3DXVECTOR3,
		    pU: ptr FLOAT,
		    pV: ptr FLOAT,
		 pDist: ptr FLOAT


D3DXSphereBoundProbe proto WINAPI \
	       pCenter: ptr D3DXVECTOR3,
		Radius: FLOAT,
	  pRayPosition: ptr D3DXVECTOR3,
	 pRayDirection: ptr D3DXVECTOR3


D3DXBoxBoundProbe proto WINAPI \
		  pMin: ptr D3DXVECTOR3,
		  pMax: ptr D3DXVECTOR3,
	  pRayPosition: ptr D3DXVECTOR3,
	 pRayDirection: ptr D3DXVECTOR3

D3DXComputeBoundingSphere proto WINAPI \
	pFirstPosition: ptr D3DXVECTOR3,
	   NumVertices: DWORD,
	      dwStride: DWORD,
	       pCenter: ptr D3DXVECTOR3,
	       pRadius: ptr FLOAT

D3DXComputeBoundingBox proto WINAPI \
	pFirstPosition: ptr D3DXVECTOR3,
	   NumVertices: DWORD,
	      dwStride: DWORD,
		  pMin: ptr D3DXVECTOR3,
		  pMax: ptr D3DXVECTOR3

.enum D3DX_CPU_OPTIMIZATION {
    D3DX_NOT_OPTIMIZED = 0,
    D3DX_3DNOW_OPTIMIZED,
    D3DX_SSE2_OPTIMIZED,
    D3DX_SSE_OPTIMIZED
    }

include d3dx10math.inl

endif
