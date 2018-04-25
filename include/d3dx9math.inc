include d3dx9.inc
ifndef __D3DX9MATH_H__
__D3DX9MATH_H__ equ <>
include math.inc
ifdef __PE__
option dllimport:<d3dx9_40>
endif

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

;D3DXCOLOR*
D3DXColorAdjustContrast proto WINAPI \
		  pout: ptr D3DXCOLOR,
		    pc: ptr D3DXCOLOR,
		     s: FLOAT

;D3DXCOLOR*
D3DXColorAdjustSaturation proto WINAPI \
		  pout: ptr D3DXCOLOR,
		    pc: ptr D3DXCOLOR,
		     s: FLOAT


;FLOAT
D3DXFresnelTerm proto WINAPI \
	      costheta: FLOAT,
       refractionindex: FLOAT


;D3DXMATRIX*
D3DXMatrixAffineTransformation proto WINAPI \
		  pout: ptr D3DXMATRIX,
	       scaling: FLOAT,
	rotationcenter: ptr D3DXVECTOR3,
	      rotation: ptr D3DXQUATERNION,
	   translation: ptr D3DXVECTOR3

;D3DXMATRIX*
D3DXMatrixAffineTransformation2D proto WINAPI \
		  pout: ptr D3DXMATRIX,
	       scaling: FLOAT,
       protationcenter: ptr D3DXVECTOR2,
	      rotation: FLOAT,
	  ptranslation: ptr D3DXVECTOR2


;HRESULT
D3DXMatrixDecompose proto WINAPI \
	     poutscale: ptr D3DXVECTOR3,
	  poutrotation: ptr D3DXQUATERNION,
       pouttranslation: ptr D3DXVECTOR3,
		    pm: ptr D3DXMATRIX

;FLOAT
D3DXMatrixDeterminant proto WINAPI \
		    pm: ptr D3DXMATRIX

;D3DXMATRIX*
D3DXMatrixInverse proto WINAPI \
		  pout: ptr D3DXMATRIX,
	  pdeterminant: ptr FLOAT,
		    pm: ptr D3DXMATRIX

;D3DXMATRIX*
D3DXMatrixLookAtLH proto WINAPI \
		  pout: ptr D3DXMATRIX,
		  peye: ptr D3DXVECTOR3,
		   pat: ptr D3DXVECTOR3,
		   pup: ptr D3DXVECTOR3

;D3DXMATRIX*
D3DXMatrixLookAtRH proto WINAPI \
		  pout: ptr D3DXMATRIX,
		  peye: ptr D3DXVECTOR3,
		   pat: ptr D3DXVECTOR3,
		   pup: ptr D3DXVECTOR3

;D3DXMATRIX*
D3DXMatrixMultiply proto WINAPI \
		  pout: ptr D3DXMATRIX,
		   pm1: ptr D3DXMATRIX,
		   pm2: ptr D3DXMATRIX

;D3DXMATRIX*
D3DXMatrixMultiplyTranspose proto WINAPI \
		  pout: ptr D3DXMATRIX,
		   pm1: ptr D3DXMATRIX,
		   pm2: ptr D3DXMATRIX

;D3DXMATRIX*
D3DXMatrixOrthoLH proto WINAPI \
		  pout: ptr D3DXMATRIX,
		     w: FLOAT,
		     h: FLOAT,
		    zn: FLOAT,
		    zf: FLOAT

;D3DXMATRIX*
D3DXMatrixOrthoOffCenterLH proto WINAPI \
		  pout: ptr D3DXMATRIX,
		     l: FLOAT,
		     r: FLOAT,
		     b: FLOAT,
		     t: FLOAT,
		    zn: FLOAT,
		    zf: FLOAT

;D3DXMATRIX*
D3DXMatrixOrthoOffCenterRH proto WINAPI \
		  pout: ptr D3DXMATRIX,
		     l: FLOAT,
		     r: FLOAT,
		     b: FLOAT,
		     t: FLOAT,
		    zn: FLOAT,
		    zf: FLOAT

;D3DXMATRIX*
D3DXMatrixOrthoRH proto WINAPI \
		  pout: ptr D3DXMATRIX,
		     w: FLOAT,
		     h: FLOAT,
		    zn: FLOAT,
		    zf: FLOAT

;D3DXMATRIX*
D3DXMatrixPerspectiveFovLH proto WINAPI \
		  pout: ptr D3DXMATRIX,
		  fovy: FLOAT,
		aspect: FLOAT,
		    zn: FLOAT,
		    zf: FLOAT

;D3DXMATRIX*
D3DXMatrixPerspectiveFovRH proto WINAPI \
		  pout: ptr D3DXMATRIX,
		  fovy: FLOAT,
		aspect: FLOAT,
		    zn: FLOAT,
		    zf: FLOAT

;D3DXMATRIX*
D3DXMatrixPerspectiveLH proto WINAPI \
		  pout: ptr D3DXMATRIX,
		     w: FLOAT,
		     h: FLOAT,
		    zn: FLOAT,
		    zf: FLOAT

;D3DXMATRIX*
D3DXMatrixPerspectiveOffCenterLH proto WINAPI \
		  pout: ptr D3DXMATRIX,
		     l: FLOAT,
		     r: FLOAT,
		     b: FLOAT,
		     t: FLOAT,
		    zn: FLOAT,
		    zf: FLOAT

;D3DXMATRIX*
D3DXMatrixPerspectiveOffCenterRH proto WINAPI \
		  pout: ptr D3DXMATRIX,
		     l: FLOAT,
		     r: FLOAT,
		     b: FLOAT,
		     t: FLOAT,
		    zn: FLOAT,
		    zf: FLOAT

;D3DXMATRIX*
D3DXMatrixPerspectiveRH proto WINAPI \
		  pout: ptr D3DXMATRIX,
		     w: FLOAT,
		     h: FLOAT,
		    zn: FLOAT,
		    zf: FLOAT

;D3DXMATRIX*
D3DXMatrixReflect proto WINAPI \
		  pout: ptr D3DXMATRIX,
		pplane: ptr D3DXPLANE

;D3DXMATRIX*
D3DXMatrixRotationAxis proto WINAPI \
		  pout: ptr D3DXMATRIX,
		    pv: ptr D3DXVECTOR3,
		 angle: FLOAT

;D3DXMATRIX*
D3DXMatrixRotationQuaternion proto WINAPI \
		  pout: ptr D3DXMATRIX,
		    pq: ptr D3DXQUATERNION

;D3DXMATRIX*
D3DXMatrixRotationX proto WINAPI \
		  pout: ptr D3DXMATRIX,
		 angle: FLOAT

;D3DXMATRIX*
D3DXMatrixRotationY proto WINAPI \
		  pout: ptr D3DXMATRIX,
		 angle: FLOAT

;D3DXMATRIX*
D3DXMatrixRotationYawPitchRoll proto WINAPI \
		  pout: ptr D3DXMATRIX,
		   yaw: FLOAT,
		 pitch: FLOAT,
		  roll: FLOAT

;D3DXMATRIX*
D3DXMatrixRotationZ proto WINAPI \
		  pout: ptr D3DXMATRIX,
		 angle: FLOAT

;D3DXMATRIX*
D3DXMatrixScaling proto WINAPI \
		  pout: ptr D3DXMATRIX,
		    sx: FLOAT,
		    sy: FLOAT,
		    sz: FLOAT

;D3DXMATRIX*
D3DXMatrixShadow proto WINAPI \
		  pout: ptr D3DXMATRIX,
		plight: ptr D3DXVECTOR4,
		pPlane: ptr D3DXPLANE

;D3DXMATRIX*
D3DXMatrixTransformation proto WINAPI \
		  pout: ptr D3DXMATRIX,
	pscalingcenter: ptr D3DXVECTOR3,
      pscalingrotation: ptr D3DXQUATERNION,
	      pscaling: ptr D3DXVECTOR3,
       protationcenter: ptr D3DXVECTOR3,
	     protation: ptr D3DXQUATERNION,
	  ptranslation: ptr D3DXVECTOR3

;D3DXMATRIX*
D3DXMatrixTransformation2D proto WINAPI \
		  pout: ptr D3DXMATRIX,
	pscalingcenter: ptr D3DXVECTOR2,
       scalingrotation: FLOAT,
	      pscaling: ptr D3DXVECTOR2,
       protationcenter: ptr D3DXVECTOR2,
	      rotation: FLOAT,
	  ptranslation: ptr D3DXVECTOR2

;D3DXMATRIX*
D3DXMatrixTranslation proto WINAPI \
		  pout: ptr D3DXMATRIX,
		     x: FLOAT,
		     y: FLOAT,
		     z: FLOAT

;D3DXMATRIX*
D3DXMatrixTranspose proto WINAPI \
		  pout: ptr D3DXMATRIX,
		    pm: ptr D3DXMATRIX


;D3DXPLANE*
D3DXPlaneFromPointNormal proto WINAPI \
		  pout: ptr D3DXPLANE,
	       pvpoint: ptr D3DXVECTOR3,
	      pvnormal: ptr D3DXVECTOR3

;D3DXPLANE*
D3DXPlaneFromPoints proto WINAPI \
		  pout: ptr D3DXPLANE,
		   pv1: ptr D3DXVECTOR3,
		   pv2: ptr D3DXVECTOR3,
		   pv3: ptr D3DXVECTOR3

;D3DXVECTOR3*
D3DXPlaneIntersectLine proto WINAPI \
		  pout: ptr D3DXVECTOR3,
		    pp: ptr D3DXPLANE,
		   pv1: ptr D3DXVECTOR3,
		   pv2: ptr D3DXVECTOR3

;D3DXPLANE*
D3DXPlaneNormalize proto WINAPI \
		  pout: ptr D3DXPLANE,
		    pp: ptr D3DXPLANE

;D3DXPLANE*
D3DXPlaneTransform proto WINAPI \
		  pout: ptr D3DXPLANE,
		pplane: ptr D3DXPLANE,
		    pm: ptr D3DXMATRIX

;D3DXPLANE*
D3DXPlaneTransformArray proto WINAPI \
		  pout: ptr D3DXPLANE,
	     outstride: UINT,
		pplane: ptr D3DXPLANE,
	       pstride: UINT,
		    pm: ptr D3DXMATRIX,
		     n: UINT


;D3DXQUATERNION*
D3DXQuaternionBaryCentric proto WINAPI \
		  pout: ptr D3DXQUATERNION,
		   pq1: ptr D3DXQUATERNION,
		   pq2: ptr D3DXQUATERNION,
		   pq3: ptr D3DXQUATERNION,
		     f: FLOAT,
		     g: FLOAT

;D3DXQUATERNION*
D3DXQuaternionExp proto WINAPI \
		  pout: ptr D3DXQUATERNION,
		    pq: ptr D3DXQUATERNION

;D3DXQUATERNION*
D3DXQuaternionInverse proto WINAPI \
		  pout: ptr D3DXQUATERNION,
		    pq: ptr D3DXQUATERNION

;D3DXQUATERNION*
D3DXQuaternionLn proto WINAPI \
		  pout: ptr D3DXQUATERNION,
		    pq: ptr D3DXQUATERNION

;D3DXQUATERNION*
D3DXQuaternionMultiply proto WINAPI \
		  pout: ptr D3DXQUATERNION,
		   pq1: ptr D3DXQUATERNION,
		   pq2: ptr D3DXQUATERNION

;D3DXQUATERNION*
D3DXQuaternionNormalize proto WINAPI \
		  pout: ptr D3DXQUATERNION,
		    pq: ptr D3DXQUATERNION

;D3DXQUATERNION*
D3DXQuaternionRotationAxis proto WINAPI \
		  pout: ptr D3DXQUATERNION,
		    pv: ptr D3DXVECTOR3,
		 angle: FLOAT

;D3DXQUATERNION*
D3DXQuaternionRotationMatrix proto WINAPI \
		  pout: ptr D3DXQUATERNION,
		    pm: ptr D3DXMATRIX

;D3DXQUATERNION*
D3DXQuaternionRotationYawPitchRoll proto WINAPI \
		  pout: ptr D3DXQUATERNION,
		   yaw: FLOAT,
		 pitch: FLOAT,
		  roll: FLOAT

;D3DXQUATERNION*
D3DXQuaternionSlerp proto WINAPI \
		  pout: ptr D3DXQUATERNION,
		   pq1: ptr D3DXQUATERNION,
		   pq2: ptr D3DXQUATERNION,
		     t: FLOAT

;D3DXQUATERNION*
D3DXQuaternionSquad proto WINAPI \
		  pout: ptr D3DXQUATERNION,
		   pq1: ptr D3DXQUATERNION,
		   pq2: ptr D3DXQUATERNION,
		   pq3: ptr D3DXQUATERNION,
		   pq4: ptr D3DXQUATERNION,
		     t: FLOAT

;void
D3DXQuaternionSquadSetup proto WINAPI \
		 paout: ptr D3DXQUATERNION,
		 pbout: ptr D3DXQUATERNION,
		 pcout: ptr D3DXQUATERNION,
		   pq0: ptr D3DXQUATERNION,
		   pq1: ptr D3DXQUATERNION,
		   pq2: ptr D3DXQUATERNION,
		   pq3: ptr D3DXQUATERNION

;void
D3DXQuaternionToAxisAngle proto WINAPI \
		    pq: ptr D3DXQUATERNION,
		 paxis: ptr D3DXVECTOR3,
		pangle: ptr FLOAT


;D3DXVECTOR2*
D3DXVec2BaryCentric proto WINAPI \
		  pout: ptr D3DXVECTOR2,
		   pv1: ptr D3DXVECTOR2,
		   pv2: ptr D3DXVECTOR2,
		   pv3: ptr D3DXVECTOR2,
		     f: FLOAT,
		     g: FLOAT

;D3DXVECTOR2*
D3DXVec2CatmullRom proto WINAPI \
		  pout: ptr D3DXVECTOR2,
		   pv0: ptr D3DXVECTOR2,
		   pv1: ptr D3DXVECTOR2,
		   pv2: ptr D3DXVECTOR2,
		   pv3: ptr D3DXVECTOR2,
		     s: FLOAT

;D3DXVECTOR2*
D3DXVec2Hermite proto WINAPI \
		  pout: ptr D3DXVECTOR2,
		   pv1: ptr D3DXVECTOR2,
		   pt1: ptr D3DXVECTOR2,
		   pv2: ptr D3DXVECTOR2,
		   pt2: ptr D3DXVECTOR2,
		     s: FLOAT

;D3DXVECTOR2*
D3DXVec2Normalize proto WINAPI \
		  pout: ptr D3DXVECTOR2,
		    pv: ptr D3DXVECTOR2

;D3DXVECTOR4*
D3DXVec2Transform proto WINAPI \
		  pout: ptr D3DXVECTOR4,
		    pv: ptr D3DXVECTOR2,
		    pm: ptr D3DXMATRIX

;D3DXVECTOR4*
D3DXVec2TransformArray proto WINAPI \
		  pout: ptr D3DXVECTOR4,
	     outstride: UINT,
		    pv: ptr D3DXVECTOR2,
	       vstride: UINT,
		    pm: ptr D3DXMATRIX,
		     n: UINT

;D3DXVECTOR2*
D3DXVec2TransformCoord proto WINAPI \
		  pout: ptr D3DXVECTOR2,
		    pv: ptr D3DXVECTOR2,
		    pm: ptr D3DXMATRIX

;D3DXVECTOR2*
D3DXVec2TransformCoordArray proto WINAPI \
		  pout: ptr D3DXVECTOR2,
	     outstride: UINT,
		    pv: ptr D3DXVECTOR2,
	       vstride: UINT,
		    pm: ptr D3DXMATRIX,
		     n: UINT

;D3DXVECTOR2*
D3DXVec2TransformNormal proto WINAPI \
		  pout: ptr D3DXVECTOR2,
		    pv: ptr D3DXVECTOR2,
		    pm: ptr D3DXVECTOR2

;D3DXVECTOR2*
D3DXVec2TransformNormalArray proto WINAPI \
		  pout: ptr D3DXVECTOR2,
	     outstride: UINT,
		    pv: ptr D3DXVECTOR2,
	       vstride: UINT,
		    pm: ptr D3DXMATRIX,
		     n: UINT


;D3DXVECTOR3*
D3DXVec3BaryCentric proto WINAPI \
		  pout: ptr D3DXVECTOR3,
		   pv1: ptr D3DXVECTOR3,
		   pv2: ptr D3DXVECTOR3,
		   pv3: ptr D3DXVECTOR3,
		     f: FLOAT,
		     g: FLOAT

;D3DXVECTOR3*
D3DXVec3CatmullRom proto WINAPI \
		  pout: ptr D3DXVECTOR3,
		   pv0: ptr D3DXVECTOR3,
		   pv1: ptr D3DXVECTOR3,
		   pv2: ptr D3DXVECTOR3,
		   pv3: ptr D3DXVECTOR3,
		     s: FLOAT

;D3DXVECTOR3*
D3DXVec3Hermite proto WINAPI \
		  pout: ptr D3DXVECTOR3,
		   pv1: ptr D3DXVECTOR3,
		   pt1: ptr D3DXVECTOR3,
		   pv2: ptr D3DXVECTOR3,
		   pt2: ptr D3DXVECTOR3,
		     s: FLOAT

;D3DXVECTOR3*
D3DXVec3Normalize proto WINAPI \
		  pout: ptr D3DXVECTOR3,
		    pv: ptr D3DXVECTOR3

;D3DXVECTOR3*
D3DXVec3Project proto WINAPI \
		  pout: ptr D3DXVECTOR3,
		    pv: ptr D3DXVECTOR3,
	     pviewport: ptr D3DVIEWPORT9,
	   pprojection: ptr D3DXMATRIX,
		 pview: ptr D3DXMATRIX,
		pworld: ptr D3DXMATRIX

;D3DXVECTOR3*
D3DXVec3ProjectArray proto WINAPI \
		  pout: ptr D3DXVECTOR3,
	     outstride: UINT,
		    pv: ptr D3DXVECTOR3,
	       vstride: UINT,
	     pviewport: ptr D3DVIEWPORT9,
	   pprojection: ptr D3DXMATRIX,
		 pview: ptr D3DXMATRIX,
		pworld: ptr D3DXMATRIX,
		     n: UINT

;D3DXVECTOR4*
D3DXVec3Transform proto WINAPI \
		  pout: ptr D3DXVECTOR4,
		    pv: ptr D3DXVECTOR3,
		    pm: ptr D3DXMATRIX

;D3DXVECTOR4*
D3DXVec3TransformArray proto WINAPI \
		  pout: ptr D3DXVECTOR4,
	     outstride: UINT,
		    pv: ptr D3DXVECTOR3,
	       vstride: UINT,
		    pm: ptr D3DXMATRIX,
		     n: UINT

;D3DXVECTOR3*
D3DXVec3TransformCoord proto WINAPI \
		  pout: ptr D3DXVECTOR3,
		    pv: ptr D3DXVECTOR3,
		    pm: ptr D3DXMATRIX

;D3DXVECTOR3*
D3DXVec3TransformCoordArray proto WINAPI \
		  pout: ptr D3DXVECTOR3,
	     outstride: UINT,
		    pv: ptr D3DXVECTOR3,
	       vstride: UINT,
		    pm: ptr D3DXMATRIX,
		     n: UINT

;D3DXVECTOR3*
D3DXVec3TransformNormal proto WINAPI \
		  pout: ptr D3DXVECTOR3,
		    pv: ptr D3DXVECTOR3,
		    pm: ptr D3DXMATRIX

;D3DXVECTOR3*
D3DXVec3TransformNormalArray proto WINAPI \
		  pout: ptr D3DXVECTOR3,
	     outstride: UINT,
		    pv: ptr D3DXVECTOR3,
	       vstride: UINT,
		    pm: ptr D3DXMATRIX,
		     n: UINT

;D3DXVECTOR3*
D3DXVec3Unproject proto WINAPI \
		  pout: ptr D3DXVECTOR3,
		    pv: ptr D3DXVECTOR3,
	     pviewport: ptr D3DVIEWPORT9,
	   pprojection: ptr D3DXMATRIX,
		 pview: ptr D3DXMATRIX,
		pworld: ptr D3DXMATRIX

;D3DXVECTOR3*
D3DXVec3UnprojectArray proto WINAPI \
		  pout: ptr D3DXVECTOR3,
	     outstride: UINT,
		    pv: ptr D3DXVECTOR3,
	       vstride: UINT,
	     pviewport: ptr D3DVIEWPORT9,
	   pprojection: ptr D3DXMATRIX,
		 pview: ptr D3DXMATRIX,
		pworld: ptr D3DXMATRIX,
		     n: UINT

;D3DXVECTOR4*
D3DXVec4BaryCentric proto WINAPI \
		  pout: ptr D3DXVECTOR4,
		   pv1: ptr D3DXVECTOR4,
		   pv2: ptr D3DXVECTOR4,
		   pv3: ptr D3DXVECTOR4,
		     f: FLOAT,
		     g: FLOAT

;D3DXVECTOR4*
D3DXVec4CatmullRom proto WINAPI \
		  pout: ptr D3DXVECTOR4,
		   pv0: ptr D3DXVECTOR4,
		   pv1: ptr D3DXVECTOR4,
		   pv2: ptr D3DXVECTOR4,
		   pv3: ptr D3DXVECTOR4,
		     s: FLOAT

;D3DXVECTOR4*
D3DXVec4Cross proto WINAPI \
		  pout: ptr D3DXVECTOR4,
		   pv1: ptr D3DXVECTOR4,
		   pv2: ptr D3DXVECTOR4,
		   pv3: ptr D3DXVECTOR4

;D3DXVECTOR4*
D3DXVec4Hermite proto WINAPI \
		  pout: ptr D3DXVECTOR4,
		   pv1: ptr D3DXVECTOR4,
		   pt1: ptr D3DXVECTOR4,
		   pv2: ptr D3DXVECTOR4,
		   pt2: ptr D3DXVECTOR4,
		     s: FLOAT

;D3DXVECTOR4*
D3DXVec4Normalize proto WINAPI \
		  pout: ptr D3DXVECTOR4,
		    pv: ptr D3DXVECTOR4

;D3DXVECTOR4*
D3DXVec4Transform proto WINAPI \
		  pout: ptr D3DXVECTOR4,
		    pv: ptr D3DXVECTOR4,
		    pm: ptr D3DXMATRIX

;D3DXVECTOR4*
D3DXVec4TransformArray proto WINAPI \
		  pout: ptr D3DXVECTOR4,
	     outstride: UINT,
		    pv: ptr D3DXVECTOR4,
	       vstride: UINT,
		    pm: ptr D3DXMATRIX,
		     n: UINT


;D3DXFLOAT16
D3DXFloat32To16Array proto WINAPI \
		  pout: ptr D3DXFLOAT16,
		   pin: ptr FLOAT,
		     n: UINT

;FLOAT
D3DXFloat16To32Array proto WINAPI \
		  pout: ptr FLOAT,
		   pin: ptr D3DXFLOAT16,
		     n: UINT


;FLOAT*
D3DXSHAdd proto WINAPI \
		  _out: ptr FLOAT,
		 order: UINT,
		     a: ptr FLOAT,
		     b: ptr FLOAT

;FLOAT
D3DXSHDot proto WINAPI \
		 order: UINT,
		     a: ptr FLOAT,
		     b: ptr FLOAT

;HRESULT
D3DXSHEvalConeLight proto WINAPI \
		 order: UINT,
		   dir: ptr D3DXVECTOR3,
		radius: FLOAT,
	    Rintensity: FLOAT,
	    Gintensity: FLOAT,
	    Bintensity: FLOAT,
		  rout: ptr FLOAT,
		  gout: ptr FLOAT,
		  bout: ptr FLOAT

;FLOAT*
D3DXSHEvalDirection proto WINAPI \
		  _out: ptr FLOAT,
		 order: UINT,
		   dir: ptr D3DXVECTOR3

;HRESULT
D3DXSHEvalDirectionalLight proto WINAPI \
		 order: UINT,
		   dir: ptr D3DXVECTOR3,
	    Rintensity: FLOAT,
	    Gintensity: FLOAT,
	    Bintensity: FLOAT,
		  rout: ptr FLOAT,
		  gout: ptr FLOAT,
		  bout: ptr FLOAT

;HRESULT
D3DXSHEvalHemisphereLight proto WINAPI \
		 order: UINT,
		   dir: ptr D3DXVECTOR3,
		   top: D3DXCOLOR,
		bottom: D3DXCOLOR,
		  rout: ptr FLOAT,
		  gout: ptr FLOAT,
		  bout: ptr FLOAT

;HRESULT
D3DXSHEvalSphericalLight proto WINAPI \
		 order: UINT,
		   dir: ptr D3DXVECTOR3,
		radius: FLOAT,
	    Rintensity: FLOAT,
	    Gintensity: FLOAT,
	    Bintensity: FLOAT,
		  rout: ptr FLOAT,
		  gout: ptr FLOAT,
		  bout: ptr FLOAT

;FLOAT*
D3DXSHMultiply2 proto WINAPI \
		  _out: ptr FLOAT,
		     a: ptr FLOAT,
		     b: ptr FLOAT

;FLOAT*
D3DXSHMultiply3 proto WINAPI \
		  _out: ptr FLOAT,
		     a: ptr FLOAT,
		     b: ptr FLOAT

;FLOAT*
D3DXSHMultiply4 proto WINAPI \
		  _out: ptr FLOAT,
		     a: ptr FLOAT,
		     b: ptr FLOAT

;FLOAT*
D3DXSHRotate proto WINAPI \
		  _out: ptr FLOAT,
		 order: UINT,
		matrix: ptr D3DXMATRIX,
		   _in: ptr FLOAT

;FLOAT*
D3DXSHRotateZ proto WINAPI \
		  _out: ptr FLOAT,
		 order: UINT,
		 angle: FLOAT,
		   _in: ptr FLOAT

;FLOAT*
D3DXSHScale proto WINAPI \
		  _out: ptr FLOAT,
		 order: UINT,
		     a: ptr FLOAT,
		 scale: FLOAT


DEFINE_GUID(IID_ID3DXMatrixStack, 0xc7885ba7, 0xf990, 0x4fe7, 0x92, 0x2d, 0x85, 0x15, 0xe4, 0x77, 0xdd, 0x85);

ID3DXMatrixStack	STRUC
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
_Pop			PVOID ?
_Push			PVOID ?
LoadIdentity		PVOID ?
LoadMatrix		PVOID ?
MultMatrix		PVOID ?
MultMatrixLocal		PVOID ?
RotateAxis		PVOID ?
RotateAxisLocal		PVOID ?
RotateYawPitchRoll	PVOID ?
RotateYawPitchRollLocal PVOID ?
Scale			PVOID ?
ScaleLocal		PVOID ?
Translate		PVOID ?
TranslateLocal		PVOID ?
GetTop			PVOID ?
ID3DXMatrixStack	ENDS


;HRESULT
D3DXCreateMatrixStack proto WINAPI \
		 flags: DWORD,
		_stack: ptr ID3DXMatrixStack

if 0
D3DXMatrixIdentity proto WINAPI \
		pOut: ptr D3DXMATRIX
else
D3DXMatrixIdentity macro pout
ifdef _WIN64
    ;mov rcx,pout
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
endif
    endm
endif

endif
