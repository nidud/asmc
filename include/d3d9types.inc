ifndef _d3d9TYPES_H_
_d3d9TYPES_H_ equ <>
.xlist

ifndef DIRECT3D_VERSION
DIRECT3D_VERSION	equ 0x0900
endif  ;;DIRECT3D_VERSION

;; include this file content only if compiling for DX9 interfaces
if (DIRECT3D_VERSION GE 0x0900)

include float.inc
.xlist

;; D3DCOLOR is equivalent to D3DFMT_A8R8G8B8
ifndef D3DCOLOR_DEFINED
D3DCOLOR		typedef DWORD
D3DCOLOR_DEFINED equ 1
endif

;; maps unsigned 8 bits/channel to D3DCOLOR
D3DCOLOR_ARGB macro a,r,g,b
	exitm<(((((a) and 0xff) shl 24) or (((r) and 0xff) shl 16) or (((g) and 0xff) shl 8) or ((b) and 0xff)))>
	endm
D3DCOLOR_RGBA macro r,g,b,a
	exitm<D3DCOLOR_ARGB(a,r,g,b)>
	endm
D3DCOLOR_XRGB macro r,g,b
	exitm<D3DCOLOR_ARGB(0xff,r,g,b)>
	endm

D3DCOLOR_XYUV macro y,u,v
	exitm<D3DCOLOR_ARGB(0xff,y,u,v)>
	endm
D3DCOLOR_AYUV macro a,y,u,v
	exitm<D3DCOLOR_ARGB(a,y,u,v)>
	endm

;; maps floating point channels (0.f to 1.f range) to D3DCOLOR
D3DCOLOR_COLORVALUE macro r,g,b,a
	exitm<D3DCOLOR_RGBA(r*255.f),g*255.f,b*255.f,a*255.f)>
	endm


ifndef D3DVECTOR_DEFINED
D3DVECTOR		STRUC
x			REAL4 ?
y			REAL4 ?
z			REAL4 ?
D3DVECTOR		ENDS
D3DVECTOR_DEFINED equ 1
endif

ifndef D3DCOLORVALUE_DEFINED
D3DCOLORVALUE		STRUC
r			REAL4 ?
g			REAL4 ?
b			REAL4 ?
a			REAL4 ?
D3DCOLORVALUE		ENDS
D3DCOLORVALUE_DEFINED equ 1
endif

ifndef D3DRECT_DEFINED
D3DRECT			STRUC
x1			LONG ?
y1			LONG ?
x2			LONG ?
y2			LONG ?
D3DRECT			ENDS
D3DRECT_DEFINED equ 1
endif

ifndef D3DMATRIX_DEFINED
D3DMATRIX		STRUC
UNION
STRUC
_11			REAL4 ?
_12			REAL4 ?
_13			REAL4 ?
_14			REAL4 ?
_21			REAL4 ?
_22			REAL4 ?
_23			REAL4 ?
_24			REAL4 ?
_31			REAL4 ?
_32			REAL4 ?
_33			REAL4 ?
_34			REAL4 ?
_41			REAL4 ?
_42			REAL4 ?
_43			REAL4 ?
_44			REAL4 ?
ENDS
m			REAL4 4*4 dup(?)
ENDS
D3DMATRIX		ENDS
D3DMATRIX_DEFINED equ 1
endif

D3DVIEWPORT9		STRUC
X			dd ?
Y			dd ?	;; Viewport Top left
_Width			dd ?
Height			dd ?	;; Viewport Dimensions
MinZ			REAL4 ? ;; Min/max of clip Volume
MaxZ			REAL4 ?
D3DVIEWPORT9		ENDS

;;
;; Values for clip fields.
;;

;; Max number of user clipping planes, supported in D3D.
D3DMAXUSERCLIPPLANES	equ 32

;; These bits could be ORed together to use with D3DRS_CLIPPLANEENABLE
;;
D3DCLIPPLANE0		equ (1 SHL 0)
D3DCLIPPLANE1		equ (1 SHL 1)
D3DCLIPPLANE2		equ (1 SHL 2)
D3DCLIPPLANE3		equ (1 SHL 3)
D3DCLIPPLANE4		equ (1 SHL 4)
D3DCLIPPLANE5		equ (1 SHL 5)

;; The following bits are used in the ClipUnion and ClipIntersection
;; members of the D3DCLIPSTATUS9
;;

D3DCS_LEFT		equ 0x00000001
D3DCS_RIGHT		equ 0x00000002
D3DCS_TOP		equ 0x00000004
D3DCS_BOTTOM		equ 0x00000008
D3DCS_FRONT		equ 0x00000010
D3DCS_BACK		equ 0x00000020
D3DCS_PLANE0		equ 0x00000040
D3DCS_PLANE1		equ 0x00000080
D3DCS_PLANE2		equ 0x00000100
D3DCS_PLANE3		equ 0x00000200
D3DCS_PLANE4		equ 0x00000400
D3DCS_PLANE5		equ 0x00000800

D3DCS_ALL		equ D3DCS_LEFT OR \
			    D3DCS_RIGHT OR \
			    D3DCS_TOP OR \
			    D3DCS_BOTTOM OR \
			    D3DCS_FRONT OR \
			    D3DCS_BACK OR \
			    D3DCS_PLANE0 OR \
			    D3DCS_PLANE1 OR \
			    D3DCS_PLANE2 OR \
			    D3DCS_PLANE3 OR \
			    D3DCS_PLANE4

D3DCLIPSTATUS9		STRUC
ClipUnion		dd ?
ClipIntersection	dd ?
D3DCLIPSTATUS9		ENDS

D3DMATERIAL9		STRUC
Diffuse			D3DCOLORVALUE <> ;; Diffuse color RGBA
Ambient			D3DCOLORVALUE <> ;; Ambient color RGB
Specular		D3DCOLORVALUE <> ;; Specular 'shininess'
Emissive		D3DCOLORVALUE <> ;; Emissive color RGB
Power			REAL4 ? ;; Sharpness if specular highlight
D3DMATERIAL9		ENDS

D3DLIGHTTYPE		typedef SDWORD
D3DLIGHT_POINT		equ 1
D3DLIGHT_SPOT		equ 2
D3DLIGHT_DIRECTIONAL	equ 3
D3DLIGHT_FORCE_DWORD	equ 0x7fffffff


D3DLIGHT9		STRUC
_Type			D3DLIGHTTYPE ? ;; Type of light source
Diffuse			D3DCOLORVALUE <> ;; Diffuse color of light
Specular		D3DCOLORVALUE <> ;; Specular color of light
Ambient			D3DCOLORVALUE <> ;; Ambient color of light
Position		D3DVECTOR <>	;; Position in world space
Direction		D3DVECTOR <>	;; Direction in world space
Range			REAL4 ? ;; Cutoff range
Falloff			REAL4 ? ;; Falloff
Attenuation0		REAL4 ? ;; Constant attenuation
Attenuation1		REAL4 ? ;; Linear attenuation
Attenuation2		REAL4 ? ;; Quadratic attenuation
Theta			REAL4 ? ;; Inner angle of spotlight cone
Phi			REAL4 ? ;; Outer angle of spotlight cone
D3DLIGHT9		ENDS

;;
;; Options for clearing
;;
D3DCLEAR_TARGET		equ 0x00000001	;; Clear target surface
D3DCLEAR_ZBUFFER	equ 0x00000002	;; Clear target z buffer
D3DCLEAR_STENCIL	equ 0x00000004	;; Clear stencil planes

;;
;; The following defines the rendering states
;;

D3DSHADEMODE		typedef SDWORD
D3DSHADE_FLAT		equ 1
D3DSHADE_GOURAUD	equ 2
D3DSHADE_PHONG		equ 3
D3DSHADE_FORCE_DWORD	equ 0x7fffffff


D3DFILLMODE		typedef SDWORD
D3DFILL_POINT		equ 1
D3DFILL_WIREFRAME	equ 2
D3DFILL_SOLID		equ 3
D3DFILL_FORCE_DWORD	equ 0x7fffffff


D3DBLEND		typedef SDWORD
D3DBLEND_ZERO		equ 1
D3DBLEND_ONE		equ 2
D3DBLEND_SRCCOLOR	equ 3
D3DBLEND_INVSRCCOLOR	equ 4
D3DBLEND_SRCALPHA	equ 5
D3DBLEND_INVSRCALPHA	equ 6
D3DBLEND_DESTALPHA	equ 7
D3DBLEND_INVDESTALPHA	equ 8
D3DBLEND_DESTCOLOR	equ 9
D3DBLEND_INVDESTCOLOR	equ 10
D3DBLEND_SRCALPHASAT	equ 11
D3DBLEND_BOTHSRCALPHA	equ 12
D3DBLEND_BOTHINVSRCALPHA equ 13
D3DBLEND_BLENDFACTOR	equ 14
D3DBLEND_INVBLENDFACTOR equ 15 /* Only supported if D3DPBLENDCAPS_BLENDFACTOR is on */
;; D3D9Ex only --
ifndef D3D_DISABLE_9EX

D3DBLEND_SRCCOLOR2	equ 16
D3DBLEND_INVSRCCOLOR2	equ 17

endif ;; NOT D3D_DISABLE_9EX
;; -- D3D9Ex only
D3DBLEND_FORCE_DWORD	equ 0x7fffffff ;; force 32-bit size enum


D3DBLENDOP		typedef SDWORD
D3DBLENDOP_ADD		equ 1
D3DBLENDOP_SUBTRACT	equ 2
D3DBLENDOP_REVSUBTRACT	equ 3
D3DBLENDOP_MIN		equ 4
D3DBLENDOP_MAX		equ 5
D3DBLENDOP_FORCE_DWORD	equ 0x7fffffff


D3DTEXTUREADDRESS	typedef SDWORD
D3DTADDRESS_WRAP	equ 1
D3DTADDRESS_MIRROR	equ 2
D3DTADDRESS_CLAMP	equ 3
D3DTADDRESS_BORDER	equ 4
D3DTADDRESS_MIRRORONCE	equ 5
D3DTADDRESS_FORCE_DWORD equ 0x7fffffff


D3DCULL			typedef SDWORD
D3DCULL_NONE		equ 1
D3DCULL_CW		equ 2
D3DCULL_CCW		equ 3
D3DCULL_FORCE_DWORD	equ 0x7fffffff


D3DCMPFUNC		typedef SDWORD
D3DCMP_NEVER		equ 1
D3DCMP_LESS		equ 2
D3DCMP_EQUAL		equ 3
D3DCMP_LESSEQUAL	equ 4
D3DCMP_GREATER		equ 5
D3DCMP_NOTEQUAL		equ 6
D3DCMP_GREATEREQUAL	equ 7
D3DCMP_ALWAYS		equ 8
D3DCMP_FORCE_DWORD	equ 0x7fffffff


D3DSTENCILOP		typedef SDWORD
D3DSTENCILOP_KEEP	equ 1
D3DSTENCILOP_ZERO	equ 2
D3DSTENCILOP_REPLACE	equ 3
D3DSTENCILOP_INCRSAT	equ 4
D3DSTENCILOP_DECRSAT	equ 5
D3DSTENCILOP_INVERT	equ 6
D3DSTENCILOP_INCR	equ 7
D3DSTENCILOP_DECR	equ 8
D3DSTENCILOP_FORCE_DWORD equ 0x7fffffff


D3DFOGMODE		typedef SDWORD
D3DFOG_NONE		equ 0
D3DFOG_EXP		equ 1
D3DFOG_EXP2		equ 2
D3DFOG_LINEAR		equ 3
D3DFOG_FORCE_DWORD	equ 0x7fffffff


D3DZBUFFERTYPE		typedef SDWORD
D3DZB_FALSE		equ 0
D3DZB_TRUE		equ 1
D3DZB_USEW		equ 2 ;; W buffering
D3DZB_FORCE_DWORD	equ 0x7fffffff ;; force 32-bit size enum


;; Primitives supported by draw-primitive API
D3DPRIMITIVETYPE	typedef SDWORD
D3DPT_POINTLIST		equ 1
D3DPT_LINELIST		equ 2
D3DPT_LINESTRIP		equ 3
D3DPT_TRIANGLELIST	equ 4
D3DPT_TRIANGLESTRIP	equ 5
D3DPT_TRIANGLEFAN	equ 6
D3DPT_FORCE_DWORD	equ 0x7fffffff


D3DTRANSFORMSTATETYPE	typedef SDWORD
D3DTS_VIEW		equ 2
D3DTS_PROJECTION	equ 3
D3DTS_TEXTURE0		equ 16
D3DTS_TEXTURE1		equ 17
D3DTS_TEXTURE2		equ 18
D3DTS_TEXTURE3		equ 19
D3DTS_TEXTURE4		equ 20
D3DTS_TEXTURE5		equ 21
D3DTS_TEXTURE6		equ 22
D3DTS_TEXTURE7		equ 23
D3DTS_FORCE_DWORD	equ 0x7fffffff


D3DTS_WORLDMATRIX macro index
	exitm<(D3DTRANSFORMSTATETYPE)(index + 256)>
	endm
D3DTS_WORLD		equ D3DTS_WORLDMATRIX(0)
D3DTS_WORLD1		equ D3DTS_WORLDMATRIX(1)
D3DTS_WORLD2		equ D3DTS_WORLDMATRIX(2)
D3DTS_WORLD3		equ D3DTS_WORLDMATRIX(3)

D3DRENDERSTATETYPE	typedef SDWORD
D3DRS_ZENABLE			equ 7  ;;
D3DRS_FILLMODE			equ 8  ;; D3DFILLMODE
D3DRS_SHADEMODE			equ 9  ;; D3DSHADEMODE
D3DRS_ZWRITEENABLE		equ 14 ;; TRUE to enable z writes */
D3DRS_ALPHATESTENABLE		equ 15 ;; TRUE to enable alpha tests */
D3DRS_LASTPIXEL			equ 16 ;; TRUE for last-pixel on lines */
D3DRS_SRCBLEND			equ 19 ;; D3DBLEND */
D3DRS_DESTBLEND			equ 20 ;; D3DBLEND */
D3DRS_CULLMODE			equ 22 ;; D3DCULL */
D3DRS_ZFUNC			equ 23 ;; D3DCMPFUNC */
D3DRS_ALPHAREF			equ 24 ;; D3DFIXED */
D3DRS_ALPHAFUNC			equ 25 ;; D3DCMPFUNC */
D3DRS_DITHERENABLE		equ 26 ;; TRUE to enable dithering */
D3DRS_ALPHABLENDENABLE		equ 27 ;; TRUE to enable alpha blending */
D3DRS_FOGENABLE			equ 28 ;; TRUE to enable fog blending */
D3DRS_SPECULARENABLE		equ 29 ;; TRUE to enable specular */
D3DRS_FOGCOLOR			equ 34 ;; D3DCOLOR */
D3DRS_FOGTABLEMODE		equ 35 ;; D3DFOGMODE */
D3DRS_FOGSTART			equ 36 ;; Fog start (for both vertex and pixel fog) */
D3DRS_FOGEND			equ 37 ;; Fog end	 */
D3DRS_FOGDENSITY		equ 38 ;; Fog density	 */
D3DRS_RANGEFOGENABLE		equ 48 ;; Enables range-based fog */
D3DRS_STENCILENABLE		equ 52 ;; BOOL enable/disable stenciling */
D3DRS_STENCILFAIL		equ 53 ;; D3DSTENCILOP to do if stencil test fails */
D3DRS_STENCILZFAIL		equ 54 ;; D3DSTENCILOP to do if stencil test passes and Z test fails */
D3DRS_STENCILPASS		equ 55 ;; D3DSTENCILOP to do if both stencil and Z tests pass */
D3DRS_STENCILFUNC		equ 56 ;; D3DCMPFUNC fn. Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true */
D3DRS_STENCILREF		equ 57 ;; Reference value used in stencil test */
D3DRS_STENCILMASK		equ 58 ;; Mask value used in stencil test */
D3DRS_STENCILWRITEMASK		equ 59 ;; Write mask applied to values written to stencil buffer */
D3DRS_TEXTUREFACTOR		equ 60 ;; D3DCOLOR used for multi-texture blend */
D3DRS_WRAP0			equ 128 ;; wrap for 1st texture coord. set */
D3DRS_WRAP1			equ 129 ;; wrap for 2nd texture coord. set */
D3DRS_WRAP2			equ 130 ;; wrap for 3rd texture coord. set */
D3DRS_WRAP3			equ 131 ;; wrap for 4th texture coord. set */
D3DRS_WRAP4			equ 132 ;; wrap for 5th texture coord. set */
D3DRS_WRAP5			equ 133 ;; wrap for 6th texture coord. set */
D3DRS_WRAP6			equ 134 ;; wrap for 7th texture coord. set */
D3DRS_WRAP7			equ 135 ;; wrap for 8th texture coord. set */
D3DRS_CLIPPING			equ 136
D3DRS_LIGHTING			equ 137
D3DRS_AMBIENT			equ 139
D3DRS_FOGVERTEXMODE		equ 140
D3DRS_COLORVERTEX		equ 141
D3DRS_LOCALVIEWER		equ 142
D3DRS_NORMALIZENORMALS		equ 143
D3DRS_DIFFUSEMATERIALSOURCE	equ 145
D3DRS_SPECULARMATERIALSOURCE	equ 146
D3DRS_AMBIENTMATERIALSOURCE	equ 147
D3DRS_EMISSIVEMATERIALSOURCE	equ 148
D3DRS_VERTEXBLEND		equ 151
D3DRS_CLIPPLANEENABLE		equ 152
D3DRS_POINTSIZE			equ 154 ;; REAL4 point size */
D3DRS_POINTSIZE_MIN		equ 155 ;; REAL4 point size min threshold */
D3DRS_POINTSPRITEENABLE		equ 156 ;; BOOL point texture coord control */
D3DRS_POINTSCALEENABLE		equ 157 ;; BOOL point size scale enable */
D3DRS_POINTSCALE_A		equ 158 ;; REAL4 point attenuation A value */
D3DRS_POINTSCALE_B		equ 159 ;; REAL4 point attenuation B value */
D3DRS_POINTSCALE_C		equ 160 ;; REAL4 point attenuation C value */
D3DRS_MULTISAMPLEANTIALIAS	equ 161 ;; BOOL - set to do FSAA with multisample buffer
D3DRS_MULTISAMPLEMASK		equ 162 ;; DWORD - per-sample enable/disable
D3DRS_PATCHEDGESTYLE		equ 163 ;; Sets whether patch edges will use REAL4 style tessellation
D3DRS_DEBUGMONITORTOKEN		equ 165 ;; DEBUG ONLY - token to debug monitor
D3DRS_POINTSIZE_MAX		equ 166 ;; REAL4 point size max threshold */
D3DRS_INDEXEDVERTEXBLENDENABLE	equ 167
D3DRS_COLORWRITEENABLE		equ 168 ;; per-channel write enable
D3DRS_TWEENFACTOR		equ 170 ;; REAL4 tween factor
D3DRS_BLENDOP			equ 171 ;; D3DBLENDOP setting
D3DRS_POSITIONDEGREE		equ 172 ;; NPatch position interpolation degree. D3DDEGREE_LINEAR or D3DDEGREE_CUBIC (default)
D3DRS_NORMALDEGREE		equ 173 ;; NPatch normal interpolation degree. D3DDEGREE_LINEAR (default) or D3DDEGREE_QUADRATIC
D3DRS_SCISSORTESTENABLE		equ 174
D3DRS_SLOPESCALEDEPTHBIAS	equ 175
D3DRS_ANTIALIASEDLINEENABLE	equ 176
D3DRS_MINTESSELLATIONLEVEL	equ 178
D3DRS_MAXTESSELLATIONLEVEL	equ 179
D3DRS_ADAPTIVETESS_X		equ 180
D3DRS_ADAPTIVETESS_Y		equ 181
D3DRS_ADAPTIVETESS_Z		equ 182
D3DRS_ADAPTIVETESS_W		equ 183
D3DRS_ENABLEADAPTIVETESSELLATION equ 184
D3DRS_TWOSIDEDSTENCILMODE	equ 185 ;; BOOL enable/disable 2 sided stenciling */
D3DRS_CCW_STENCILFAIL		equ 186 ;; D3DSTENCILOP to do if ccw stencil test fails */
D3DRS_CCW_STENCILZFAIL		equ 187 ;; D3DSTENCILOP to do if ccw stencil test passes and Z test fails */
D3DRS_CCW_STENCILPASS		equ 188 ;; D3DSTENCILOP to do if both ccw stencil and Z tests pass */
D3DRS_CCW_STENCILFUNC		equ 189 ;; D3DCMPFUNC fn.  ccw Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true */
D3DRS_COLORWRITEENABLE1		equ 190 ;; Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
D3DRS_COLORWRITEENABLE2		equ 191 ;; Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
D3DRS_COLORWRITEENABLE3		equ 192 ;; Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
D3DRS_BLENDFACTOR		equ 193 ;; D3DCOLOR used for a constant blend factor during alpha blending for devices that support D3DPBLENDCAPS_BLENDFACTOR */
D3DRS_SRGBWRITEENABLE		equ 194 ;; Enable rendertarget writes to be DE-linearized to SRGB (for formats that expose D3DUSAGE_QUERY_SRGBWRITE) */
D3DRS_DEPTHBIAS			equ 195
D3DRS_WRAP8			equ 198 ;; Additional wrap states for vs_3_0+ attributes with D3DDECLUSAGE_TEXCOORD */
D3DRS_WRAP9			equ 199
D3DRS_WRAP10			equ 200
D3DRS_WRAP11			equ 201
D3DRS_WRAP12			equ 202
D3DRS_WRAP13			equ 203
D3DRS_WRAP14			equ 204
D3DRS_WRAP15			equ 205
D3DRS_SEPARATEALPHABLENDENABLE	equ 206 ;; TRUE to enable a separate blending function for the alpha channel */
D3DRS_SRCBLENDALPHA		equ 207 ;; SRC blend factor for the alpha channel when D3DRS_SEPARATEDESTALPHAENABLE is TRUE */
D3DRS_DESTBLENDALPHA		equ 208 ;; DST blend factor for the alpha channel when D3DRS_SEPARATEDESTALPHAENABLE is TRUE */
D3DRS_BLENDOPALPHA		equ 209 ;; Blending operation for the alpha channel when D3DRS_SEPARATEDESTALPHAENABLE is TRUE */


D3DRS_FORCE_DWORD		equ 0x7fffffff ;; force 32-bit size enum


;; Maximum number of simultaneous render targets D3D supports
D3D_MAX_SIMULTANEOUS_RENDERTARGETS equ 4

;; Values for material source
D3DMATERIALCOLORSOURCE	typedef SDWORD
D3DMCS_MATERIAL		equ 0
D3DMCS_COLOR1		equ 1				; Diffuse vertex color is used
D3DMCS_COLOR2		equ 2				; Specular vertex color is used
D3DMCS_FORCE_DWORD	equ 0x7fffffff			; force 32-bit size enum


;; Bias to apply to the texture coordinate set to apply a wrap to.
D3DRENDERSTATE_WRAPBIAS equ 128

;; Flags to construct the WRAP render states
D3DWRAP_U		equ 0x00000001
D3DWRAP_V		equ 0x00000002
D3DWRAP_W		equ 0x00000004

;; Flags to construct the WRAP render states for 1D thru 4D texture coordinates
D3DWRAPCOORD_0		equ 0x00000001	  ;; same as D3DWRAP_U
D3DWRAPCOORD_1		equ 0x00000002	  ;; same as D3DWRAP_V
D3DWRAPCOORD_2		equ 0x00000004	  ;; same as D3DWRAP_W
D3DWRAPCOORD_3		equ 0x00000008

;; Flags to construct D3DRS_COLORWRITEENABLE
D3DCOLORWRITEENABLE_RED		equ (1 SHL 0)
D3DCOLORWRITEENABLE_GREEN	equ (1 SHL 1)
D3DCOLORWRITEENABLE_BLUE	equ (1 SHL 2)
D3DCOLORWRITEENABLE_ALPHA	equ (1 SHL 3)

;;
;; State enumerants for per-stage processing of fixed function pixel processing
;; Two of these affect fixed function vertex processing as well: TEXTURETRANSFORMFLAGS and TEXCOORDINDEX.
;;
D3DTEXTURESTAGESTATETYPE typedef SDWORD
D3DTSS_COLOROP		equ  1
D3DTSS_COLORARG1	equ  2 ;; D3DTA_* (texture arg)
D3DTSS_COLORARG2	equ  3 ;; D3DTA_* (texture arg)
D3DTSS_ALPHAOP		equ  4 ;; D3DTEXTUREOP - per-stage blending controls for alpha channel
D3DTSS_ALPHAARG1	equ  5 ;; D3DTA_* (texture arg)
D3DTSS_ALPHAARG2	equ  6 ;; D3DTA_* (texture arg)
D3DTSS_BUMPENVMAT00	equ  7 ;; REAL4 (bump mapping matrix)
D3DTSS_BUMPENVMAT01	equ  8 ;; REAL4 (bump mapping matrix)
D3DTSS_BUMPENVMAT10	equ  9 ;; REAL4 (bump mapping matrix)
D3DTSS_BUMPENVMAT11	equ 10 ;; REAL4 (bump mapping matrix)
D3DTSS_TEXCOORDINDEX	equ 11 ;; identifies which set of texture coordinates index this texture
D3DTSS_BUMPENVLSCALE	equ 22 ;; REAL4 scale for bump map luminance
D3DTSS_BUMPENVLOFFSET	equ 23 ;; REAL4 offset for bump map luminance
D3DTSS_TEXTURETRANSFORMFLAGS equ 24 ;; D3DTEXTURETRANSFORMFLAGS controls texture transform
D3DTSS_COLORARG0	equ 26 ;; D3DTA_* third arg for triadic ops
D3DTSS_ALPHAARG0	equ 27 ;; D3DTA_* third arg for triadic ops
D3DTSS_RESULTARG	equ 28 ;; D3DTA_* arg for result (CURRENT or TEMP)
D3DTSS_CONSTANT		equ 32 ;; Per-stage constant D3DTA_CONSTANT
D3DTSS_FORCE_DWORD	equ 0x7fffffff ;; force 32-bit size enum


;;
;; State enumerants for per-sampler texture processing.
;;
D3DSAMPLERSTATETYPE	typedef SDWORD
D3DSAMP_ADDRESSU	equ  1
D3DSAMP_ADDRESSV	equ  2 ;; D3DTEXTUREADDRESS for V coordinate
D3DSAMP_ADDRESSW	equ  3 ;; D3DTEXTUREADDRESS for W coordinate
D3DSAMP_BORDERCOLOR	equ  4 ;; D3DCOLOR
D3DSAMP_MAGFILTER	equ  5 ;; D3DTEXTUREFILTER filter to use for magnification
D3DSAMP_MINFILTER	equ  6 ;; D3DTEXTUREFILTER filter to use for minification
D3DSAMP_MIPFILTER	equ  7 ;; D3DTEXTUREFILTER filter to use between mipmaps during minification
D3DSAMP_MIPMAPLODBIAS	equ  8 ;; float Mipmap LOD bias
D3DSAMP_MAXMIPLEVEL	equ  9 ;; DWORD 0..(n-1) LOD index of largest map to use (0 == largest)
D3DSAMP_MAXANISOTROPY	equ 10 ;; DWORD maximum anisotropy
D3DSAMP_SRGBTEXTURE	equ 11 ;; Default = 0 (which means Gamma 1.0,
			       ;; no correction required.) else correct for
			       ;; Gamma = 2.2
D3DSAMP_ELEMENTINDEX	equ 12 ;; When multi-element texture is assigned to sampler, this
			       ;; indicates which element index to use.	 Default = 0.
D3DSAMP_DMAPOFFSET	equ 13 ;; Offset in vertices in the pre-sampled displacement map.
			       ;; Only valid for D3DDMAPSAMPLER sampler
D3DSAMP_FORCE_DWORD	equ 0x7fffffff ;; force 32-bit size enum


;; Special sampler which is used in the tesselator
D3DDMAPSAMPLER		equ 256

;; Samplers used in vertex shaders
D3DVERTEXTEXTURESAMPLER0 equ (D3DDMAPSAMPLER+1)
D3DVERTEXTEXTURESAMPLER1 equ (D3DDMAPSAMPLER+2)
D3DVERTEXTEXTURESAMPLER2 equ (D3DDMAPSAMPLER+3)
D3DVERTEXTEXTURESAMPLER3 equ (D3DDMAPSAMPLER+4)

;; Values, used with D3DTSS_TEXCOORDINDEX, to specify that the vertex data(position
;; and normal in the camera space) should be taken as texture coordinates
;; Low 16 bits are used to specify texture coordinate index, to take the WRAP mode from
;;
D3DTSS_TCI_PASSTHRU		equ 0x00000000
D3DTSS_TCI_CAMERASPACENORMAL	equ 0x00010000
D3DTSS_TCI_CAMERASPACEPOSITION	equ 0x00020000
D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR equ 0x00030000
D3DTSS_TCI_SPHEREMAP		equ 0x00040000

;;
;; Enumerations for COLOROP and ALPHAOP texture blending operations set in
;; texture processing stage controls in D3DTSS.
;;
D3DTEXTUREOP		typedef SDWORD

;; Control
D3DTOP_DISABLE			equ 1 ;; disables stage
D3DTOP_SELECTARG1		equ 2 ;; the default
D3DTOP_SELECTARG2		equ 3

;; Modulate
D3DTOP_MODULATE			equ 4 ;; multiply args together
D3DTOP_MODULATE2X		equ 5 ;; multiply and  1 bit
D3DTOP_MODULATE4X		equ 6 ;; multiply and  2 bits

;; Add
D3DTOP_ADD			equ  7 ;; add arguments together
D3DTOP_ADDSIGNED		equ  8 ;; add with -0.5 bias
D3DTOP_ADDSIGNED2X		equ  9 ;; as above but left  1 bit
D3DTOP_SUBTRACT			equ 10 ;; Arg1 - Arg2, with no saturation
D3DTOP_ADDSMOOTH		equ 11 ;; add 2 args, subtract product
				       ;; Arg1 + Arg2 - Arg1*Arg2
				       ;; = Arg1 + (1-Arg1)*Arg2

;; Linear alpha blend: Arg1*(Alpha) + Arg2*(1-Alpha)
D3DTOP_BLENDDIFFUSEALPHA	equ 12 ;; iterated alpha
D3DTOP_BLENDTEXTUREALPHA	equ 13 ;; texture alpha
D3DTOP_BLENDFACTORALPHA		equ 14 ;; alpha from D3DRS_TEXTUREFACTOR

;; Linear alpha blend with pre-multiplied arg1 input: Arg1 + Arg2*(1-Alpha)
D3DTOP_BLENDTEXTUREALPHAPM	equ 15 ;; texture alpha
D3DTOP_BLENDCURRENTALPHA	equ 16	;; by alpha of current color

;; Specular mapping
D3DTOP_PREMODULATE		equ 17	    ;; modulate with next texture before use
D3DTOP_MODULATEALPHA_ADDCOLOR	equ 18	    ;; Arg1.RGB + Arg1.A*Arg2.RGB
					    ;; COLOROP only
D3DTOP_MODULATECOLOR_ADDALPHA	equ 19	    ;; Arg1.RGB*Arg2.RGB + Arg1.A
					    ;; COLOROP only
D3DTOP_MODULATEINVALPHA_ADDCOLOR equ 20	    ;; (1-Arg1.A)*Arg2.RGB + Arg1.RGB
					    ;; COLOROP only
D3DTOP_MODULATEINVCOLOR_ADDALPHA equ 21	    ;; (1-Arg1.RGB)*Arg2.RGB + Arg1.A
					    ;; COLOROP only

;; Bump mapping
D3DTOP_BUMPENVMAP		equ 22 ;; per pixel env map perturbation
D3DTOP_BUMPENVMAPLUMINANCE	equ 23 ;; with luminance channel

;; This can do either diffuse or specular bump mapping with correct input.
;; Performs the function (Arg1.R*Arg2.R + Arg1.G*Arg2.G + Arg1.B*Arg2.B)
;; where each component has been scaled and offset to make it signed.
;; The result is replicated into all four (including alpha) channels.
;; This is a valid COLOROP only.
D3DTOP_DOTPRODUCT3		equ 24

;; Triadic ops
D3DTOP_MULTIPLYADD		equ 25 ;; Arg0 + Arg1*Arg2
D3DTOP_LERP			equ 26 ;; (Arg0)*Arg1 + (1-Arg0)*Arg2
D3DTOP_FORCE_DWORD		equ 0x7fffffff

;;
;; Values for COLORARG0,1,2, ALPHAARG0,1,2, and RESULTARG texture blending
;; operations set in texture processing stage controls in D3DRENDERSTATE.
;;
D3DTA_SELECTMASK	equ 0x0000000f	;; mask for arg selector
D3DTA_DIFFUSE		equ 0x00000000	;; select diffuse color (read only)
D3DTA_CURRENT		equ 0x00000001	;; select stage destination register (read/write)
D3DTA_TEXTURE		equ 0x00000002	;; select texture color (read only)
D3DTA_TFACTOR		equ 0x00000003	;; select D3DRS_TEXTUREFACTOR (read only)
D3DTA_SPECULAR		equ 0x00000004	;; select specular color (read only)
D3DTA_TEMP		equ 0x00000005	;; select temporary register color (read/write)
D3DTA_CONSTANT		equ 0x00000006	;; select texture stage constant
D3DTA_COMPLEMENT	equ 0x00000010	;; take 1.0 - x (read modifier)
D3DTA_ALPHAREPLICATE	equ 0x00000020	;; replicate alpha to color components (read modifier)

;;
;; Values for D3DSAMP_***FILTER texture stage states
;;
D3DTEXTUREFILTERTYPE	typedef SDWORD
D3DTEXF_NONE		equ 0
D3DTEXF_POINT		equ 1	; nearest
D3DTEXF_LINEAR		equ 2	; linear interpolation
D3DTEXF_ANISOTROPIC	equ 3	; anisotropic
D3DTEXF_PYRAMIDALQUAD	equ 6	; 4-sample tent
D3DTEXF_GAUSSIANQUAD	equ 7	; 4-sample gaussian
;; D3D9Ex only --
ifndef D3D_DISABLE_9EX

D3DTEXF_CONVOLUTIONMONO equ 8	; Convolution filter for monochrome textures

endif ;; NOT D3D_DISABLE_9EX
;; -- D3D9Ex only
D3DTEXF_FORCE_DWORD	equ 0x7fffffff	; force 32-bit size enum


;; Bits for Flags in ProcessVertices call

D3DPV_DONOTCOPYDATA	equ (1 SHL 0)

;;-------------------------------------------------------------------

;; Flexible vertex format bits
;;
D3DFVF_RESERVED0	equ 0x001
D3DFVF_POSITION_MASK	equ 0x400E
D3DFVF_XYZ		equ 0x002
D3DFVF_XYZRHW		equ 0x004
D3DFVF_XYZB1		equ 0x006
D3DFVF_XYZB2		equ 0x008
D3DFVF_XYZB3		equ 0x00a
D3DFVF_XYZB4		equ 0x00c
D3DFVF_XYZB5		equ 0x00e
D3DFVF_XYZW		equ 0x4002

D3DFVF_NORMAL		equ 0x010
D3DFVF_PSIZE		equ 0x020
D3DFVF_DIFFUSE		equ 0x040
D3DFVF_SPECULAR		equ 0x080

D3DFVF_TEXCOUNT_MASK	equ 0xf00
D3DFVF_TEXCOUNT_SHIFT	equ 8
D3DFVF_TEX0		equ 0x000
D3DFVF_TEX1		equ 0x100
D3DFVF_TEX2		equ 0x200
D3DFVF_TEX3		equ 0x300
D3DFVF_TEX4		equ 0x400
D3DFVF_TEX5		equ 0x500
D3DFVF_TEX6		equ 0x600
D3DFVF_TEX7		equ 0x700
D3DFVF_TEX8		equ 0x800

D3DFVF_LASTBETA_UBYTE4	equ 0x1000
D3DFVF_LASTBETA_D3DCOLOR equ 0x8000

D3DFVF_RESERVED2	equ 0x6000  ;; 2 reserved bits

;;---------------------------------------------------------------------
;; Vertex Shaders
;;

;; Vertex shader declaration

;; Vertex element semantics
;;
D3DDECLUSAGE		typedef SDWORD
D3DDECLUSAGE_POSITION	equ 0
D3DDECLUSAGE_BLENDWEIGHT equ 1
D3DDECLUSAGE_BLENDINDICES equ 2
D3DDECLUSAGE_NORMAL	equ 3
D3DDECLUSAGE_PSIZE	equ 4
D3DDECLUSAGE_TEXCOORD	equ 5
D3DDECLUSAGE_TANGENT	equ 6
D3DDECLUSAGE_BINORMAL	equ 7
D3DDECLUSAGE_TESSFACTOR equ 8
D3DDECLUSAGE_POSITIONT	equ 9
D3DDECLUSAGE_COLOR	equ 10
D3DDECLUSAGE_FOG	equ 11
D3DDECLUSAGE_DEPTH	equ 12
D3DDECLUSAGE_SAMPLE	equ 13


MAXD3DDECLUSAGE		equ D3DDECLUSAGE_SAMPLE
MAXD3DDECLUSAGEINDEX	equ 15
MAXD3DDECLLENGTH	equ 64 ;; does not include "end" marker vertex element

D3DDECLMETHOD		typedef SDWORD
D3DDECLMETHOD_DEFAULT	equ 0
D3DDECLMETHOD_PARTIALU	equ 2
D3DDECLMETHOD_PARTIALV	equ 3
D3DDECLMETHOD_CROSSUV	equ 4
D3DDECLMETHOD_LOOKUP	equ 5		; Lookup a displacement map
D3DDECLMETHOD_LOOKUPPRESAMPLED equ 6	; Lookup a pre-sampled displacement map

MAXD3DDECLMETHOD	equ D3DDECLMETHOD_LOOKUPPRESAMPLED

;; Declarations for _Type fields
;;
D3DDECLTYPE		typedef SDWORD
D3DDECLTYPE_FLOAT1	equ 0
D3DDECLTYPE_FLOAT2	equ 1	; 2D REAL4 expanded to (value, value, 0., 1.)
D3DDECLTYPE_FLOAT3	equ 2	; 3D REAL4 expanded to (value, value, value, 1.)
D3DDECLTYPE_FLOAT4	equ 3	; 4D REAL4
D3DDECLTYPE_D3DCOLOR	equ 4	; 4D packed unsigned bytes mapped to 0. to 1. range
				; Input is in D3DCOLOR format (ARGB) expanded to (R, G, B, A)
D3DDECLTYPE_UBYTE4	equ 5	; 4D unsigned byte
D3DDECLTYPE_SHORT2	equ 6	; 2D signed short expanded to (value, value, 0., 1.)
D3DDECLTYPE_SHORT4	equ 7	; 4D signed short

;; The following types are valid only with vertex shaders >= 2.0


D3DDECLTYPE_UBYTE4N	equ 8	; Each of 4 bytes is normalized by dividing to 255.0
D3DDECLTYPE_SHORT2N	equ 9	; 2D signed short normalized (v[0]/32767.0,v[1]/32767.0,0,1)
D3DDECLTYPE_SHORT4N	equ 10	; 4D signed short normalized (v[0]/32767.0,v[1]/32767.0,v[2]/32767.0,v[3]/32767.0)
D3DDECLTYPE_USHORT2N	equ 11	; 2D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,0,1)
D3DDECLTYPE_USHORT4N	equ 12	; 4D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,v[2]/65535.0,v[3]/65535.0)
D3DDECLTYPE_UDEC3	equ 13	; 3D unsigned 10 10 10 format expanded to (value, value, value, 1)
D3DDECLTYPE_DEC3N	equ 14	; 3D signed 10 10 10 format normalized and expanded to (v[0]/511.0, v[1]/511.0, v[2]/511.0, 1)
D3DDECLTYPE_FLOAT16_2	equ 15	; Two 16-bit REAL4ing point values, expanded to (value, value, 0, 1)
D3DDECLTYPE_FLOAT16_4	equ 16	; Four 16-bit REAL4ing point values
D3DDECLTYPE_UNUSED	equ 17	; When the type field in a decl is unused.


MAXD3DDECLTYPE		equ D3DDECTYPE_UNUSED

D3DVERTEXELEMENT9	STRUC
Stream			dw ?	;; Stream index
_Offset			dw ?	;; Offset in the stream in bytes
_Type			db ?	;; Data type
Method			db ?	;; Processing method
Usage			db ?	;; Semantics
UsageIndex		db ?	;; Semantic index
D3DVERTEXELEMENT9	ENDS
LPD3DVERTEXELEMENT9	typedef ptr D3DVERTEXELEMENT9

;; This is used to initialize the last vertex element in a vertex declaration
;; array
;;
D3DDECL_END macro
	exitm<{0xFF,0,D3DDECTYPE_UNUSED,0,0,0}>
	endm

;; Maximum supported number of texture coordinate sets
D3DDP_MAXTEXCOORD	equ 8

;;---------------------------------------------------------------------
;; Values for IDirect3DDevice9::SetStreamSourceFreq's Setting parameter
;;---------------------------------------------------------------------
D3DSTREAMSOURCE_INDEXEDDATA equ (1 SHL 30)
D3DSTREAMSOURCE_INSTANCEDATA equ (2 SHL 30)



;;---------------------------------------------------------------------
;;
;; The internal format of Pixel Shader (PS) & Vertex Shader (VS)
;; Instruction Tokens is defined in the Direct3D Device Driver Kit
;;
;;---------------------------------------------------------------------

;;
;; Instruction Token Bit Definitions
;;
D3DSI_OPCODE_MASK	equ 0x0000FFFF

D3DSI_INSTLENGTH_MASK	equ 0x0F000000
D3DSI_INSTLENGTH_SHIFT	equ 24

D3DSHADER_INSTRUCTION_OPCODE_TYPE typedef SDWORD
D3DSIO_NOP		equ 0
D3DSIO_MOV		equ 2
D3DSIO_ADD		equ 3
D3DSIO_SUB		equ 4
D3DSIO_MAD		equ 5
D3DSIO_MUL		equ 6
D3DSIO_RCP		equ 7
D3DSIO_RSQ		equ 8
D3DSIO_DP3		equ 9
D3DSIO_DP4		equ 10
D3DSIO_MIN		equ 11
D3DSIO_MAX		equ 12
D3DSIO_SLT		equ 13
D3DSIO_SGE		equ 14
D3DSIO_EXP		equ 15
D3DSIO_LOG		equ 16
D3DSIO_LIT		equ 17
D3DSIO_DST		equ 18
D3DSIO_LRP		equ 19
D3DSIO_FRC		equ 20
D3DSIO_M4x4		equ 21
D3DSIO_M4x3		equ 22
D3DSIO_M3x4		equ 23
D3DSIO_M3x3		equ 24
D3DSIO_M3x2		equ 25
D3DSIO_CALL		equ 26
D3DSIO_CALLNZ		equ 27
D3DSIO_LOOP		equ 28
D3DSIO_RET		equ 29
D3DSIO_ENDLOOP		equ 30
D3DSIO_LABEL		equ 31
D3DSIO_DCL		equ 32
D3DSIO_POW		equ 33
D3DSIO_CRS		equ 34
D3DSIO_SGN		equ 35
D3DSIO_ABS		equ 36
D3DSIO_NRM		equ 37
D3DSIO_SINCOS		equ 38
D3DSIO_REP		equ 39
D3DSIO_ENDREP		equ 40
D3DSIO_IF		equ 41
D3DSIO_IFC		equ 42
D3DSIO_ELSE		equ 43
D3DSIO_ENDIF		equ 44
D3DSIO_BREAK		equ 45
D3DSIO_BREAKC		equ 46
D3DSIO_MOVA		equ 47
D3DSIO_DEFB		equ 48
D3DSIO_DEFI		equ 49
D3DSIO_TEXCOORD		equ 64
D3DSIO_TEXKILL		equ 51
D3DSIO_TEX		equ 52
D3DSIO_TEXBEM		equ 53
D3DSIO_TEXBEML		equ 54
D3DSIO_TEXREG2AR	equ 55
D3DSIO_TEXREG2GB	equ 56
D3DSIO_TEXM3x2PAD	equ 57
D3DSIO_TEXM3x2TEX	equ 58
D3DSIO_TEXM3x3PAD	equ 59
D3DSIO_TEXM3x3TEX	equ 60
D3DSIO_RESERVED0	equ 61
D3DSIO_TEXM3x3SPEC	equ 62
D3DSIO_TEXM3x3VSPEC	equ 63
D3DSIO_EXPP		equ 64
D3DSIO_LOGP		equ 65
D3DSIO_CND		equ 66
D3DSIO_DEF		equ 67
D3DSIO_TEXREG2RGB	equ 68
D3DSIO_TEXDP3TEX	equ 69
D3DSIO_TEXM3x2DEPTH	equ 70
D3DSIO_TEXDP3		equ 71
D3DSIO_TEXM3x3		equ 72
D3DSIO_TEXDEPTH		equ 73
D3DSIO_CMP		equ 74
D3DSIO_BEM		equ 75
D3DSIO_DP2ADD		equ 76
D3DSIO_DSX		equ 77
D3DSIO_DSY		equ 78
D3DSIO_TEXLDD		equ 79
D3DSIO_SETP		equ 80
D3DSIO_TEXLDL		equ 81
D3DSIO_BREAKP		equ 82
D3DSIO_PHASE		equ 0xFFFD
D3DSIO_COMMENT		equ 0xFFFE
D3DSIO_END		equ 0xFFFF
D3DSIO_FORCE_DWORD	equ 0x7fffffff


;;---------------------------------------------------------------------
;; Use these constants with D3DSIO_SINCOS macro as SRC2, SRC3
;;
D3DSINCOSCONST1		equ <-1.5500992e-006f, -2.1701389e-005f, 0.0026041667f, 0.00026041668f>
D3DSINCOSCONST2		equ <-0.020833334f, -0.12500000f, 1.0f, 0.50000000f>

;;---------------------------------------------------------------------
;; Co-Issue Instruction Modifier - if set then this instruction is to be
;; issued in parallel with the previous instruction(s) for which this bit
;; is not set.
;;
D3DSI_COISSUE		equ 0x40000000

;;---------------------------------------------------------------------
;; Opcode specific controls

D3DSP_OPCODESPECIFICCONTROL_MASK equ 0x00ff0000
D3DSP_OPCODESPECIFICCONTROL_SHIFT equ 16

;; ps_2_0 texld controls
D3DSI_TEXLD_PROJECT	equ (0x01 SHL D3DSP_OPCODESPECIFICCONTROL_SHIFT)
D3DSI_TEXLD_BIAS	equ (0x02 SHL D3DSP_OPCODESPECIFICCONTROL_SHIFT)

;; Comparison for dynamic conditional instruction opcodes (i.e. if, breakc)
D3DSHADER_COMPARISON	typedef SDWORD
D3DSPC_RESERVED0	equ 0
D3DSPC_GT		equ 1 ; 0 0 1
D3DSPC_EQ		equ 2 ; 0 1 0
D3DSPC_GE		equ 3 ; 0 1 1
D3DSPC_LT		equ 4 ; 1 0 0
D3DSPC_NE		equ 5 ; 1 0 1
D3DSPC_LE		equ 6 ; 1 1 0
D3DSPC_RESERVED1	equ 7 ; 1 1 1


;; Comparison is part of instruction opcode token:
D3DSHADER_COMPARISON_SHIFT equ D3DSP_OPCODESPECIFICCONTROL_SHIFT
D3DSHADER_COMPARISON_MASK equ (0x7 SHL D3DSHADER_COMPARISON_SHIFT)

;;---------------------------------------------------------------------
;; Predication flags on instruction token
D3DSHADER_INSTRUCTION_PREDICATED equ (0x1 SHL 28)

;;---------------------------------------------------------------------
;; DCL Info Token Controls

;; For dcl info tokens requiring a semantic (usage + index)
D3DSP_DCL_USAGE_SHIFT	equ 0
D3DSP_DCL_USAGE_MASK	equ 0x0000000f

D3DSP_DCL_USAGEINDEX_SHIFT equ 16
D3DSP_DCL_USAGEINDEX_MASK equ 0x000f0000

;; DCL pixel shader sampler info token.
D3DSP_TEXTURETYPE_SHIFT equ 27
D3DSP_TEXTURETYPE_MASK	equ 0x78000000

D3DSAMPLER_TEXTURE_TYPE typedef SDWORD
D3DSTT_UNKNOWN		equ (0 shl D3DSP_TEXTURETYPE_SHIFT)
D3DSTT_2D		equ (2 shl D3DSP_TEXTURETYPE_SHIFT) ; dcl_2d s# (for declaring a 2-D texture)
D3DSTT_CUBE		equ (3 shl D3DSP_TEXTURETYPE_SHIFT) ; dcl_cube s# (for declaring a cube texture)
D3DSTT_VOLUME		equ (4 shl D3DSP_TEXTURETYPE_SHIFT) ; dcl_volume s# (for declaring a volume texture)
D3DSTT_FORCE_DWORD	equ 0x7fffffff	; force 32-bit size enum


;;---------------------------------------------------------------------
;; Parameter Token Bit Definitions
;;
D3DSP_REGNUM_MASK	equ 0x000007FF

;; destination parameter write mask
D3DSP_WRITEMASK_0	equ 0x00010000	;; Component 0 (X;Red)
D3DSP_WRITEMASK_1	equ 0x00020000	;; Component 1 (Y;Green)
D3DSP_WRITEMASK_2	equ 0x00040000	;; Component 2 (Z;Blue)
D3DSP_WRITEMASK_3	equ 0x00080000	;; Component 3 (W;Alpha)
D3DSP_WRITEMASK_ALL	equ 0x000F0000	;; All Components

;; destination parameter modifiers
D3DSP_DSTMOD_SHIFT	equ 20
D3DSP_DSTMOD_MASK	equ 0x00F00000

;; Bit masks for destination parameter modifiers
D3DSPDM_NONE		equ (0 SHL D3DSP_DSTMOD_SHIFT) ;; nop
D3DSPDM_SATURATE	equ (1 SHL D3DSP_DSTMOD_SHIFT) ;; clamp to 0. to 1. range
D3DSPDM_PARTIALPRECISION equ (2 SHL D3DSP_DSTMOD_SHIFT) ;; Partial precision hint
D3DSPDM_MSAMPCENTROID	equ (4 SHL D3DSP_DSTMOD_SHIFT) ;; Relevant to multisampling only:
					    ;; When the pixel center is not covered, sample
					    ;; attribute or compute gradients/LOD
					    ;; using multisample "centroid" location.
					    ;; "Centroid" is some location within the covered
					    ;; region of the pixel.

;; destination parameter
D3DSP_DSTSHIFT_SHIFT	equ 24
D3DSP_DSTSHIFT_MASK	equ 0x0F000000

;; destination/source parameter register type
D3DSP_REGTYPE_SHIFT	equ 28
D3DSP_REGTYPE_SHIFT2	equ 8
D3DSP_REGTYPE_MASK	equ 0x70000000
D3DSP_REGTYPE_MASK2	equ 0x00001800

D3DSHADER_PARAM_REGISTER_TYPE typedef SDWORD
D3DSPR_TEMP		equ  0
D3DSPR_INPUT		equ  1	; Input Register File
D3DSPR_CONST		equ  2	; Constant Register File
D3DSPR_ADDR		equ  3	; Address Register (VS)
D3DSPR_TEXTURE		equ  3	; Texture Register File (PS)
D3DSPR_RASTOUT		equ  4	; Rasterizer Register File
D3DSPR_ATTROUT		equ  5	; Attribute Output Register File
D3DSPR_TEXCRDOUT	equ  6	; Texture Coordinate Output Register File
D3DSPR_OUTPUT		equ  6	; Output register file for VS3.0+
D3DSPR_CONSTINT		equ  7	; Constant Integer Vector Register File
D3DSPR_COLOROUT		equ  8	; Color Output Register File
D3DSPR_DEPTHOUT		equ  9	; Depth Output Register File
D3DSPR_SAMPLER		equ 10	; Sampler State Register File
D3DSPR_CONST2		equ 11	; Constant Register File  2048 - 4095
D3DSPR_CONST3		equ 12	; Constant Register File  4096 - 6143
D3DSPR_CONST4		equ 13	; Constant Register File  6144 - 8191
D3DSPR_CONSTBOOL	equ 14	; Constant Boolean register file
D3DSPR_LOOP		equ 15	; Loop counter register file
D3DSPR_TEMPFLOAT16	equ 16	; 16-bit REAL4 temp register file
D3DSPR_MISCTYPE		equ 17	; Miscellaneous (single) registers.
D3DSPR_LABEL		equ 18	; Label
D3DSPR_PREDICATE	equ 19	; Predicate register
D3DSPR_FORCE_DWORD	equ 0x7fffffff	; force 32-bit size enum


;; The miscellaneous register file (D3DSPR_MISCTYPES)
;; contains register types for which there is only ever one
;; register (i.e. the register # is not needed).
;; Rather than use up additional register types for such
;; registers, they are defined
;; as particular offsets into the misc. register file:
D3DSHADER_MISCTYPE_OFFSETS typedef SDWORD
D3DSMO_POSITION		equ 0
D3DSMO_FACE		equ 1	; Floating point primitive area (PS)


;; Register offsets in the Rasterizer Register File
;;
D3DVS_RASTOUT_OFFSETS	typedef SDWORD
D3DSRO_POSITION		equ 0
D3DSRO_FOG		equ 2
D3DSRO_POINT_SIZE	equ 3
D3DSRO_FORCE_DWORD	equ 0x7fffffff


;; Source operand addressing modes

D3DVS_ADDRESSMODE_SHIFT equ 13
D3DVS_ADDRESSMODE_MASK	equ (1 SHL D3DVS_ADDRESSMODE_SHIFT)

D3DVS_ADDRESSMODE_TYPE	typedef SDWORD
D3DVS_ADDRMODE_ABSOLUTE equ (0 shl D3DVS_ADDRESSMODE_SHIFT)
D3DVS_ADDRMODE_RELATIVE equ (1 shl D3DVS_ADDRESSMODE_SHIFT)
D3DVS_ADDRMODE_FORCE_DWORD equ 0x7fffffff


D3DSHADER_ADDRESSMODE_SHIFT equ 13
D3DSHADER_ADDRESSMODE_MASK equ (1 SHL D3DSHADER_ADDRESSMODE_SHIFT)

D3DSHADER_ADDRESSMODE_TYPE typedef SDWORD
D3DSHADER_ADDRMODE_ABSOLUTE equ (0 shl D3DSHADER_ADDRESSMODE_SHIFT)
D3DSHADER_ADDRMODE_RELATIVE equ (1 shl D3DSHADER_ADDRESSMODE_SHIFT)
D3DSHADER_ADDRMODE_FORCE_DWORD equ 0x7fffffff


;; Source operand swizzle definitions
;;
D3DVS_SWIZZLE_SHIFT	equ 16
D3DVS_SWIZZLE_MASK	equ 0x00FF0000

;; The following bits define where to take component X from:

D3DVS_X_X		equ (0 SHL D3DVS_SWIZZLE_SHIFT)
D3DVS_X_Y		equ (1 SHL D3DVS_SWIZZLE_SHIFT)
D3DVS_X_Z		equ (2 SHL D3DVS_SWIZZLE_SHIFT)
D3DVS_X_W		equ (3 SHL D3DVS_SWIZZLE_SHIFT)

;; The following bits define where to take component Y from:

D3DVS_Y_X		equ (0 SHL (D3DVS_SWIZZLE_SHIFT + 2))
D3DVS_Y_Y		equ (1 SHL (D3DVS_SWIZZLE_SHIFT + 2))
D3DVS_Y_Z		equ (2 SHL (D3DVS_SWIZZLE_SHIFT + 2))
D3DVS_Y_W		equ (3 SHL (D3DVS_SWIZZLE_SHIFT + 2))

;; The following bits define where to take component Z from:

D3DVS_Z_X		equ (0 SHL (D3DVS_SWIZZLE_SHIFT + 4))
D3DVS_Z_Y		equ (1 SHL (D3DVS_SWIZZLE_SHIFT + 4))
D3DVS_Z_Z		equ (2 SHL (D3DVS_SWIZZLE_SHIFT + 4))
D3DVS_Z_W		equ (3 SHL (D3DVS_SWIZZLE_SHIFT + 4))

;; The following bits define where to take component W from:

D3DVS_W_X		equ (0 SHL (D3DVS_SWIZZLE_SHIFT + 6))
D3DVS_W_Y		equ (1 SHL (D3DVS_SWIZZLE_SHIFT + 6))
D3DVS_W_Z		equ (2 SHL (D3DVS_SWIZZLE_SHIFT + 6))
D3DVS_W_W		equ (3 SHL (D3DVS_SWIZZLE_SHIFT + 6))

;; Value when there is no swizzle (X is taken from X, Y is taken from Y,
;; Z is taken from Z, W is taken from W
;;
D3DVS_NOSWIZZLE		equ (D3DVS_X_X OR D3DVS_Y_Y OR D3DVS_Z_Z OR D3DVS_W_W)

;; source parameter swizzle
D3DSP_SWIZZLE_SHIFT	equ 16
D3DSP_SWIZZLE_MASK	equ 0x00FF0000

D3DSP_NOSWIZZLE		equ (0 shl (D3DSP_SWIZZLE_SHIFT + 0)) or \
			    (1 shl (D3DSP_SWIZZLE_SHIFT + 2)) or \
			    (2 shl (D3DSP_SWIZZLE_SHIFT + 4)) or \
			    (3 shl (D3DSP_SWIZZLE_SHIFT + 6))

;; pixel-shader swizzle ops
D3DSP_REPLICATERED	equ (0 shl (D3DSP_SWIZZLE_SHIFT + 0)) or \
			    (0 shl (D3DSP_SWIZZLE_SHIFT + 2)) or \
			    (0 shl (D3DSP_SWIZZLE_SHIFT + 4)) or \
			    (0 shl (D3DSP_SWIZZLE_SHIFT + 6))

D3DSP_REPLICATEGREEN	equ (1 shl (D3DSP_SWIZZLE_SHIFT + 0)) or \
			    (1 shl (D3DSP_SWIZZLE_SHIFT + 2)) or \
			    (1 shl (D3DSP_SWIZZLE_SHIFT + 4)) or \
			    (1 shl (D3DSP_SWIZZLE_SHIFT + 6))

D3DSP_REPLICATEBLUE	equ (2 shl (D3DSP_SWIZZLE_SHIFT + 0)) or \
			    (2 shl (D3DSP_SWIZZLE_SHIFT + 2)) or \
			    (2 shl (D3DSP_SWIZZLE_SHIFT + 4)) or \
			    (2 shl (D3DSP_SWIZZLE_SHIFT + 6))

D3DSP_REPLICATEALPHA	equ (3 shl (D3DSP_SWIZZLE_SHIFT + 0)) or \
			    (3 shl (D3DSP_SWIZZLE_SHIFT + 2)) or \
			    (3 shl (D3DSP_SWIZZLE_SHIFT + 4)) or \
			    (3 shl (D3DSP_SWIZZLE_SHIFT + 6))

;; source parameter modifiers
D3DSP_SRCMOD_SHIFT	equ 24
D3DSP_SRCMOD_MASK	equ 0x0F000000

D3DSHADER_PARAM_SRCMOD_TYPE typedef SDWORD
D3DSPSM_NONE		equ 0 shl D3DSP_SRCMOD_SHIFT
D3DSPSM_NEG		equ 1 shl D3DSP_SRCMOD_SHIFT	; negate
D3DSPSM_BIAS		equ 2 shl D3DSP_SRCMOD_SHIFT	; bias
D3DSPSM_BIASNEG		equ 3 shl D3DSP_SRCMOD_SHIFT	; bias and negate
D3DSPSM_SIGN		equ 4 shl D3DSP_SRCMOD_SHIFT	; sign
D3DSPSM_SIGNNEG		equ 5 shl D3DSP_SRCMOD_SHIFT	; sign and negate
D3DSPSM_COMP		equ 6 shl D3DSP_SRCMOD_SHIFT	; complement
D3DSPSM_X2		equ 7 shl D3DSP_SRCMOD_SHIFT	; *2
D3DSPSM_X2NEG		equ 8 shl D3DSP_SRCMOD_SHIFT	; *2 and negate
D3DSPSM_DZ		equ 9 shl D3DSP_SRCMOD_SHIFT	; divide through by z component
D3DSPSM_DW		equ 10 shl D3DSP_SRCMOD_SHIFT	; divide through by w component
D3DSPSM_ABS		equ 11 shl D3DSP_SRCMOD_SHIFT	; abs()
D3DSPSM_ABSNEG		equ 12 shl D3DSP_SRCMOD_SHIFT	; -abs()
D3DSPSM_NOT		equ 13 shl D3DSP_SRCMOD_SHIFT	; for predicate register: "!p0"
D3DSPSM_FORCE_DWORD	equ 0x7fffffff			; force 32-bit size enum


;; pixel shader version token
D3DPS_VERSION macro _Major,_Minor
	exitm<(0xFFFF0000 OR ((_Major) SHL 8) OR (_Minor))>
	endm

;; vertex shader version token
D3DVS_VERSION macro _Major,_Minor
	exitm<(0xFFFE0000 OR ((_Major) SHL 8) OR (_Minor))>
	endm

;; extract major/minor from version cap
D3DSHADER_VERSION_MAJOR macro _Version
	exitm<(((_Version) SHR 8) AND 0xFF)>
	endm
D3DSHADER_VERSION_MINOR macro _Version
	exitm<(((_Version) SHR 0) AND 0xFF)>
	endm

;; destination/source parameter register type
D3DSI_COMMENTSIZE_SHIFT equ 16
D3DSI_COMMENTSIZE_MASK	equ 0x7FFF0000
D3DSHADER_COMMENT macro _DWordSize
	exitm<((((_DWordSize) shl D3DSI_COMMENTSIZE_SHIFT) and D3DSI_COMMENTSIZE_MASK) or D3DSIO_COMMENT)>
	endm

;; pixel/vertex shader end token
D3DPS_END macro
	exitm<0x0000FFFF>
	endm
D3DVS_END macro
	exitm<0x0000FFFF>
	endm


;;---------------------------------------------------------------------

;; High order surfaces
;;
D3DBASISTYPE		typedef SDWORD
D3DBASIS_BEZIER		equ 0
D3DBASIS_BSPLINE	equ 1
D3DBASIS_CATMULL_ROM	equ 2
D3DBASIS_FORCE_DWORD	equ 0x7fffffff

D3DDEGREETYPE		typedef SDWORD
D3DDEGREE_LINEAR	equ 1
D3DDEGREE_QUADRATIC	equ 2
D3DDEGREE_CUBIC		equ 3
D3DDEGREE_QUINTIC	equ 5
D3DDEGREE_FORCE_DWORD	equ 0x7fffffff

D3DPATCHEDGESTYLE	typedef SDWORD
D3DPATCHEDGE_DISCRETE	equ 0
D3DPATCHEDGE_CONTINUOUS equ 1
D3DPATCHEDGE_FORCE_DWORD equ 0x7fffffff

D3DSTATEBLOCKTYPE	typedef SDWORD
D3DSBT_ALL		equ 1
D3DSBT_PIXELSTATE	equ 2		; capture pixel state
D3DSBT_VERTEXSTATE	equ 3		; capture vertex state
D3DSBT_FORCE_DWORD	equ 0x7fffffff

;; The D3DVERTEXBLENDFLAGS type is used with D3DRS_VERTEXBLEND state.
;;
D3DVERTEXBLENDFLAGS	typedef SDWORD
D3DVBF_DISABLE		equ 0
D3DVBF_1WEIGHTS		equ 1		; 2 matrix blending
D3DVBF_2WEIGHTS		equ 2		; 3 matrix blending
D3DVBF_3WEIGHTS		equ 3		; 4 matrix blending
D3DVBF_TWEENING		equ 255		; blending using D3DRS_TWEENFACTOR
D3DVBF_0WEIGHTS		equ 256		; one matrix is used with weight 1.0
D3DVBF_FORCE_DWORD	equ 0x7fffffff	; force 32-bit size enum


D3DTEXTURETRANSFORMFLAGS typedef SDWORD
D3DTTFF_DISABLE		equ 0
D3DTTFF_COUNT1		equ 1	; rasterizer should expect 1-D texture coords
D3DTTFF_COUNT2		equ 2	; rasterizer should expect 2-D texture coords
D3DTTFF_COUNT3		equ 3	; rasterizer should expect 3-D texture coords
D3DTTFF_COUNT4		equ 4	; rasterizer should expect 4-D texture coords
D3DTTFF_PROJECTED	equ 256 ; texcoords to be divided by COUNTth element
D3DTTFF_FORCE_DWORD	equ 0x7fffffff

;; Macros to set texture coordinate format bits in the FVF id

D3DFVF_TEXTUREFORMAT2	equ 0	      ;; Two REAL4ing point values
D3DFVF_TEXTUREFORMAT1	equ 3	      ;; One floating point value
D3DFVF_TEXTUREFORMAT3	equ 1	      ;; Three floating point values
D3DFVF_TEXTUREFORMAT4	equ 2	      ;; Four floating point values

D3DFVF_TEXCOORDSIZE3 macro CoordIndex
	exitm<(D3DFVF_TEXTUREFORMAT3 SHL (CoordIndex*2 + 16))>
	endm
D3DFVF_TEXCOORDSIZE2 macro CoordIndex
	exitm<(D3DFVF_TEXTUREFORMAT2)>
	endm
D3DFVF_TEXCOORDSIZE4 macro CoordIndex
	exitm<(D3DFVF_TEXTUREFORMAT4 SHL (CoordIndex*2 + 16))>
	endm
D3DFVF_TEXCOORDSIZE1 macro CoordIndex
	exitm<(D3DFVF_TEXTUREFORMAT1 SHL (CoordIndex*2 + 16))>
	endm


;;---------------------------------------------------------------------

;; Direct3D9 Device types
D3DDEVTYPE		typedef SDWORD
D3DDEVTYPE_HAL		equ 1
D3DDEVTYPE_REF		equ 2
D3DDEVTYPE_SW		equ 3
D3DDEVTYPE_NULLREF	equ 4
D3DDEVTYPE_FORCE_DWORD	equ 0x7fffffff

;; Multi-Sample buffer types
D3DMULTISAMPLE_TYPE	typedef SDWORD
D3DMULTISAMPLE_NONE	equ 0
D3DMULTISAMPLE_NONMASKABLE equ 1
D3DMULTISAMPLE_2_SAMPLES equ 2
D3DMULTISAMPLE_3_SAMPLES equ 3
D3DMULTISAMPLE_4_SAMPLES equ 4
D3DMULTISAMPLE_5_SAMPLES equ 5
D3DMULTISAMPLE_6_SAMPLES equ 6
D3DMULTISAMPLE_7_SAMPLES equ 7
D3DMULTISAMPLE_8_SAMPLES equ 8
D3DMULTISAMPLE_9_SAMPLES equ 9
D3DMULTISAMPLE_10_SAMPLES equ 10
D3DMULTISAMPLE_11_SAMPLES equ 11
D3DMULTISAMPLE_12_SAMPLES equ 12
D3DMULTISAMPLE_13_SAMPLES equ 13
D3DMULTISAMPLE_14_SAMPLES equ 14
D3DMULTISAMPLE_15_SAMPLES equ 15
D3DMULTISAMPLE_16_SAMPLES equ 16
D3DMULTISAMPLE_FORCE_DWORD equ 0x7fffffff

;; Formats
;; Most of these names have the following convention:
;;	A = Alpha
;;	R = Red
;;	G = Green
;;	B = Blue
;;	X = Unused Bits
;;	P = Palette
;;	L = Luminance
;;	U = dU coordinate for BumpMap
;;	V = dV coordinate for BumpMap
;;	S = Stencil
;;	D = Depth (e.g. Z or W buffer)
;;	C = Computed from other channels (typically on certain read operations)
;;
;;	Further, the order of the pieces are from MSB first; hence
;;	D3DFMT_A8L8 indicates that the high byte of this two byte
;;	format is alpha.
;;
;;	D3DFMT_D16_LOCKABLE indicates:
;;	     - An integer 16-bit value.
;;	     - An app-lockable surface.
;;
;;	D3DFMT_D32F_LOCKABLE indicates:
;;	     - An IEEE 754 floating-point value.
;;	     - An app-lockable surface.
;;
;;	All Depth/Stencil formats except D3DFMT_D16_LOCKABLE and D3DFMT_D32F_LOCKABLE indicate:
;;	    - no particular bit ordering per pixel, and
;;	    - are not app lockable, and
;;	    - the driver is allowed to consume more than the indicated
;;	      number of bits per Depth channel (but not Stencil channel).
;;
ifndef MAKEFOURCC
MAKEFOURCC macro ch0, ch1, ch2, ch3
	exitm<(ch0 or (ch1 shl 8) or (ch2 shl 16) or (ch3 shl 24 ))>
	endm
endif ;; defined(MAKEFOURCC)


D3DFORMAT		typedef SDWORD
D3DFMT_UNKNOWN		equ 0
D3DFMT_R8G8B8		equ 20
D3DFMT_A8R8G8B8		equ 21
D3DFMT_X8R8G8B8		equ 22
D3DFMT_R5G6B5		equ 23
D3DFMT_X1R5G5B5		equ 24
D3DFMT_A1R5G5B5		equ 25
D3DFMT_A4R4G4B4		equ 26
D3DFMT_R3G3B2		equ 27
D3DFMT_A8		equ 28
D3DFMT_A8R3G3B2		equ 29
D3DFMT_X4R4G4B4		equ 30
D3DFMT_A2B10G10R10	equ 31
D3DFMT_A8B8G8R8		equ 32
D3DFMT_X8B8G8R8		equ 33
D3DFMT_G16R16		equ 34
D3DFMT_A2R10G10B10	equ 35
D3DFMT_A16B16G16R16	equ 36
D3DFMT_A8P8		equ 40
D3DFMT_P8		equ 41
D3DFMT_L8		equ 50
D3DFMT_A8L8		equ 51
D3DFMT_A4L4		equ 52
D3DFMT_V8U8		equ 60
D3DFMT_L6V5U5		equ 61
D3DFMT_X8L8V8U8		equ 62
D3DFMT_Q8W8V8U8		equ 63
D3DFMT_V16U16		equ 64
D3DFMT_A2W10V10U10	equ 67
D3DFMT_UYVY		equ MAKEFOURCC('U', 'Y', 'V', 'Y')
D3DFMT_R8G8_B8G8	equ MAKEFOURCC('R', 'G', 'B', 'G')
D3DFMT_YUY2		equ MAKEFOURCC('Y', 'U', 'Y', '2')
D3DFMT_G8R8_G8B8	equ MAKEFOURCC('G', 'R', 'G', 'B')
D3DFMT_DXT1		equ MAKEFOURCC('D', 'X', 'T', '1')
D3DFMT_DXT2		equ MAKEFOURCC('D', 'X', 'T', '2')
D3DFMT_DXT3		equ MAKEFOURCC('D', 'X', 'T', '3')
D3DFMT_DXT4		equ MAKEFOURCC('D', 'X', 'T', '4')
D3DFMT_DXT5		equ MAKEFOURCC('D', 'X', 'T', '5')
D3DFMT_D16_LOCKABLE	equ 70
D3DFMT_D32		equ 71
D3DFMT_D15S1		equ 73
D3DFMT_D24S8		equ 75
D3DFMT_D24X8		equ 77
D3DFMT_D24X4S4		equ 79
D3DFMT_D16		equ 80
D3DFMT_D32F_LOCKABLE	equ 82
D3DFMT_D24FS8		equ 83
;; D3D9Ex only --	equ 48
if NOT defined(D3D_DISABLE_9EX)

;; Z-Stencil formats valid for CPU access
D3DFMT_D32_LOCKABLE	equ 84
D3DFMT_S8_LOCKABLE	equ 85

endif ;; NOT D3D_DISABLE_9EX
;; -- D3D9Ex only

D3DFMT_L16		equ 81

D3DFMT_VERTEXDATA	equ 100
D3DFMT_INDEX16		equ 101
D3DFMT_INDEX32		equ 102

D3DFMT_Q16W16V16U16	equ 110

D3DFMT_MULTI2_ARGB8	equ MAKEFOURCC('M','E','T','1')

    ;; Floating point surface formats

    ;; s10e5 formats (16-bits per channel)
D3DFMT_R16F		equ 111
D3DFMT_G16R16F		equ 112
D3DFMT_A16B16G16R16F	equ 113

    ;; IEEE s23e8 formats (32-bits per channel)
D3DFMT_R32F		equ 114
D3DFMT_G32R32F		equ 115
D3DFMT_A32B32G32R32F	equ 116

D3DFMT_CxV8U8		equ 117

;; D3D9Ex only --
if NOT defined(D3D_DISABLE_9EX)

    ;; Monochrome 1 bit per pixel format
D3DFMT_A1		equ 118

    ;; 2.8 biased fixed point
D3DFMT_A2B10G10R10_XR_BIAS equ 119


    ;; Binary format indicating that the data has no inherent type
D3DFMT_BINARYBUFFER	equ 199

endif ;; NOT D3D_DISABLE_9EX
;; -- D3D9Ex only

D3DFMT_FORCE_DWORD	equ 0x7fffffff


;; Display Modes
D3DDISPLAYMODE		STRUC
_Width			UINT ?
Height			UINT ?
RefreshRate		UINT ?
Format			D3DFORMAT ?
D3DDISPLAYMODE		ENDS

;; Creation Parameters
D3DDEVICE_CREATION_PARAMETERS STRUC
AdapterOrdinal		UINT ?
DeviceType		D3DDEVTYPE ?
hFocusWindow		HWND ?
BehaviorFlags		dd ?
D3DDEVICE_CREATION_PARAMETERS ENDS


;; SwapEffects
D3DSWAPEFFECT		typedef SDWORD
D3DSWAPEFFECT_DISCARD	equ 1
D3DSWAPEFFECT_FLIP	equ 2
D3DSWAPEFFECT_COPY	equ 3
D3DSWAPEFFECT_OVERLAY	equ 4
D3DSWAPEFFECT_FLIPEX	equ 5
D3DSWAPEFFECT_FORCE_DWORD equ 0x7fffffff

;; Pool types
D3DPOOL			typedef SDWORD
D3DPOOL_DEFAULT		equ 0
D3DPOOL_MANAGED		equ 1
D3DPOOL_SYSTEMMEM	equ 2
D3DPOOL_SCRATCH		equ 3
D3DPOOL_FORCE_DWORD	equ 0x7fffffff


;; RefreshRate pre-defines
D3DPRESENT_RATE_DEFAULT equ 0x00000000


;; Resize Optional Parameters
D3DPRESENT_PARAMETERS	STRUC
BackBufferWidth		UINT ?
BackBufferHeight	UINT ?
BackBufferFormat	D3DFORMAT ?
BackBufferCount		UINT ?
MultiSampleType		D3DMULTISAMPLE_TYPE ?
MultiSampleQuality	dd ?
SwapEffect		D3DSWAPEFFECT ?
hDeviceWindow		HWND ?
Windowed		BOOL ?
EnableAutoDepthStencil	BOOL ?
AutoDepthStencilFormat	D3DFORMAT ?
Flags			dd ?
;; FullScreen_RefreshRateInHz must be zero for Windowed mode
FullScreen_RefreshRateInHz UINT ?
PresentationInterval	UINT ?
D3DPRESENT_PARAMETERS	ENDS

;; Values for D3DPRESENT_PARAMETERS.Flags

D3DPRESENTFLAG_LOCKABLE_BACKBUFFER equ 0x00000001
D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL equ 0x00000002
D3DPRESENTFLAG_DEVICECLIP equ 0x00000004
D3DPRESENTFLAG_VIDEO	equ 0x00000010

;; D3D9Ex only --
if NOT defined(D3D_DISABLE_9EX)

D3DPRESENTFLAG_NOAUTOROTATE equ 0x00000020
D3DPRESENTFLAG_UNPRUNEDMODE equ 0x00000040
D3DPRESENTFLAG_OVERLAY_LIMITEDRGB equ 0x00000080
D3DPRESENTFLAG_OVERLAY_YCbCr_BT709 equ 0x00000100
D3DPRESENTFLAG_OVERLAY_YCbCr_xvYCC equ 0x00000200
D3DPRESENTFLAG_RESTRICTED_CONTENT equ 0x00000400
D3DPRESENTFLAG_RESTRICT_SHARED_RESOURCE_DRIVER equ 0x00000800

endif ;; NOT D3D_DISABLE_9EX
;; -- D3D9Ex only

;; Gamma Ramp: Same as DX7

D3DGAMMARAMP		STRUC
red			dw 256 dup(?)
green			dw 256 dup(?)
blue			dw 256 dup(?)
D3DGAMMARAMP		ENDS

;; Back buffer types
D3DBACKBUFFER_TYPE	typedef SDWORD
D3DBACKBUFFER_TYPE_MONO equ 0
D3DBACKBUFFER_TYPE_LEFT equ 1
D3DBACKBUFFER_TYPE_RIGHT equ 2
D3DBACKBUFFER_TYPE_FORCE_DWORD equ 0x7fffffff


;; Types
D3DRESOURCETYPE		typedef SDWORD
D3DRTYPE_SURFACE	equ 1
D3DRTYPE_VOLUME		equ 2
D3DRTYPE_TEXTURE	equ 3
D3DRTYPE_VOLUMETEXTURE	equ 4
D3DRTYPE_CUBETEXTURE	equ 5
D3DRTYPE_VERTEXBUFFER	equ 6
D3DRTYPE_INDEXBUFFER	equ 7
D3DRTYPE_FORCE_DWORD	equ 0x7fffffff


;; Usages
D3DUSAGE_RENDERTARGET	equ (0x00000001)
D3DUSAGE_DEPTHSTENCIL	equ (0x00000002)
D3DUSAGE_DYNAMIC	equ (0x00000200)

;; D3D9Ex only --
if NOT defined(D3D_DISABLE_9EX)

D3DUSAGE_NONSECURE	equ (0x00800000)

endif ;; NOT D3D_DISABLE_9EX
;; -- D3D9Ex only

;; When passed to CheckDeviceFormat, D3DUSAGE_AUTOGENMIPMAP may return
;; D3DOK_NOAUTOGEN if the device doesn't support autogeneration for that format.
;; D3DOK_NOAUTOGEN is a success code, not a failure code... the SUCCEEDED and FAILED macros
;; will return true and false respectively for this code.
D3DUSAGE_AUTOGENMIPMAP	equ (0x00000400)
D3DUSAGE_DMAP		equ (0x00004000)

;; The following usages are valid only for querying CheckDeviceFormat
D3DUSAGE_QUERY_LEGACYBUMPMAP equ (0x00008000)
D3DUSAGE_QUERY_SRGBREAD equ (0x00010000)
D3DUSAGE_QUERY_FILTER	equ (0x00020000)
D3DUSAGE_QUERY_SRGBWRITE equ (0x00040000)
D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING equ (0x00080000)
D3DUSAGE_QUERY_VERTEXTEXTURE equ (0x00100000)
D3DUSAGE_QUERY_WRAPANDMIP equ (0x00200000)

;; Usages for Vertex/Index buffers
D3DUSAGE_WRITEONLY	equ (0x00000008)
D3DUSAGE_SOFTWAREPROCESSING equ (0x00000010)
D3DUSAGE_DONOTCLIP	equ (0x00000020)
D3DUSAGE_POINTS		equ (0x00000040)
D3DUSAGE_RTPATCHES	equ (0x00000080)
D3DUSAGE_NPATCHES	equ (0x00000100)

;; D3D9Ex only --
if NOT defined(D3D_DISABLE_9EX)

D3DUSAGE_TEXTAPI	equ (0x10000000)
D3DUSAGE_RESTRICTED_CONTENT equ (0x00000800)
D3DUSAGE_RESTRICT_SHARED_RESOURCE equ (0x00002000)
D3DUSAGE_RESTRICT_SHARED_RESOURCE_DRIVER equ (0x00001000)

endif ;; NOT D3D_DISABLE_9EX
;; -- D3D9Ex only


;; CubeMap Face identifiers
D3DCUBEMAP_FACES	typedef SDWORD
D3DCUBEMAP_FACE_POSITIVE_X equ 0
D3DCUBEMAP_FACE_NEGATIVE_X equ 1
D3DCUBEMAP_FACE_POSITIVE_Y equ 2
D3DCUBEMAP_FACE_NEGATIVE_Y equ 3
D3DCUBEMAP_FACE_POSITIVE_Z equ 4
D3DCUBEMAP_FACE_NEGATIVE_Z equ 5
D3DCUBEMAP_FACE_FORCE_DWORD equ 0x7fffffff


;; Lock flags

D3DLOCK_READONLY	equ 0x00000010
D3DLOCK_DISCARD		equ 0x00002000
D3DLOCK_NOOVERWRITE	equ 0x00001000
D3DLOCK_NOSYSLOCK	equ 0x00000800
D3DLOCK_DONOTWAIT	equ 0x00004000

D3DLOCK_NO_DIRTY_UPDATE equ 0x00008000


;; Vertex Buffer Description
D3DVERTEXBUFFER_DESC	STRUC
Format			D3DFORMAT ?
_Type			D3DRESOURCETYPE ?
Usage			dd ?
Pool			D3DPOOL ?
_Size			UINT ?
FVF			dd ?
D3DVERTEXBUFFER_DESC	ENDS

;; Index Buffer Description
D3DINDEXBUFFER_DESC	STRUC
Format			D3DFORMAT ?
_Type			D3DRESOURCETYPE ?
Usage			dd ?
Pool			D3DPOOL ?
_Size			UINT ?
D3DINDEXBUFFER_DESC	ENDS


;; Surface Description
D3DSURFACE_DESC		STRUC
Format			D3DFORMAT ?
_Type			D3DRESOURCETYPE ?
Usage			dd ?
Pool			D3DPOOL ?
MultiSampleType		D3DMULTISAMPLE_TYPE ?
MultiSampleQuality	dd ?
_Width			UINT ?
Height			UINT ?
D3DSURFACE_DESC		ENDS

D3DVOLUME_DESC		STRUC
Format			D3DFORMAT ?
_Type			D3DRESOURCETYPE ?
Usage			dd ?
Pool			D3DPOOL ?
_Width			UINT ?
Height			UINT ?
Depth			UINT ?
D3DVOLUME_DESC		ENDS

;; Structure for LockRect
D3DLOCKED_RECT		STRUC
Pitch			SINT ?
pBits			PVOID ?
D3DLOCKED_RECT		ENDS

;; Structures for LockBox
D3DBOX			STRUC
Left			UINT ?
Top			UINT ?
Right			UINT ?
Bottom			UINT ?
Front			UINT ?
Back			UINT ?
D3DBOX			ENDS

D3DLOCKED_BOX		STRUC
RowPitch		SINT ?
SlicePitch		SINT ?
pBits			PVOID ?
D3DLOCKED_BOX		ENDS

;; Structures for LockRange
D3DRANGE		STRUC
_Offset			UINT ?
_Size			UINT ?
D3DRANGE		ENDS

;; Structures for high order primitives
D3DRECTPATCH_INFO	STRUC
StartVertexOffsetWidth	UINT ?
StartVertexOffsetHeight UINT ?
_Width			UINT ?
Height			UINT ?
Stride			UINT ?
Basis			D3DBASISTYPE ?
Degree			D3DDEGREETYPE ?
D3DRECTPATCH_INFO	ENDS

D3DTRIPATCH_INFO	STRUC
StartVertexOffset	UINT ?
NumVertices		UINT ?
Basis			D3DBASISTYPE ?
Degree			D3DDEGREETYPE ?
D3DTRIPATCH_INFO	ENDS

;; Adapter Identifier

MAX_DEVICE_IDENTIFIER_STRING equ 512
D3DADAPTER_IDENTIFIER9	STRUC
Driver			db MAX_DEVICE_IDENTIFIER_STRING dup(?)
Description		db MAX_DEVICE_IDENTIFIER_STRING dup(?)
DeviceName		db 32 dup(?)	;; Device name for GDI (ex. \\.\DISPLAY1)

ifdef _WIN32
DriverVersion		LARGE_INTEGER <>;; Defined for 32 bit components
else
DriverVersionLowPart	dd ?	;; Defined for 16 bit driver components
DriverVersionHighPart	dd ?
endif
VendorId		dd ?
DeviceId		dd ?
SubSysId		dd ?
Revision		dd ?
DeviceIdentifier	GUID <>
WHQLLevel		dd ?
D3DADAPTER_IDENTIFIER9	ENDS


;; Raster Status structure returned by GetRasterStatus
D3DRASTER_STATUS	STRUC
InVBlank		BOOL ?
ScanLine		UINT ?
D3DRASTER_STATUS	ENDS



;; Debug monitor tokens (DEBUG only)
;;
;; Note that if D3DRS_DEBUGMONITORTOKEN is set, the call is treated as
;; passing a token to the debug monitor. For example, if, after passing
;; D3DDMT_ENABLE/DISABLE to D3DRS_DEBUGMONITORTOKEN other token values
;; are passed in, the enabled/disabled state of the debug
;; monitor will still persist.
;;
;; debug monitor defaults to enabled. The ?
;;
;; GetRenderState on D3DRS_DEBUGMONITORTOKEN is not of any use. Calling ?
;;
D3DDEBUGMONITORTOKENS	typedef SDWORD
D3DDMT_ENABLE		equ 0
D3DDMT_DISABLE		equ 1	; disable debug monitor
D3DDMT_FORCE_DWORD	equ 0x7fffffff

;; Async feedback

D3DQUERYTYPE		typedef SDWORD
D3DQUERYTYPE_VCACHE		equ 4
D3DQUERYTYPE_RESOURCEMANAGER	equ 5  ;; D3DISSUE_END
D3DQUERYTYPE_VERTEXSTATS	equ 6  ;; D3DISSUE_END
D3DQUERYTYPE_EVENT		equ 8  ;; D3DISSUE_END
D3DQUERYTYPE_OCCLUSION		equ 9  ;; D3DISSUE_BEGIN, D3DISSUE_END
D3DQUERYTYPE_TIMESTAMP		equ 10 ;; D3DISSUE_END
D3DQUERYTYPE_TIMESTAMPDISJOINT	equ 11 ;; D3DISSUE_BEGIN, D3DISSUE_END
D3DQUERYTYPE_TIMESTAMPFREQ	equ 12 ;; D3DISSUE_END
D3DQUERYTYPE_PIPELINETIMINGS	equ 13 ;; D3DISSUE_BEGIN, D3DISSUE_END
D3DQUERYTYPE_INTERFACETIMINGS	equ 14 ;; D3DISSUE_BEGIN, D3DISSUE_END
D3DQUERYTYPE_VERTEXTIMINGS	equ 15 ;; D3DISSUE_BEGIN, D3DISSUE_END
D3DQUERYTYPE_PIXELTIMINGS	equ 16 ;; D3DISSUE_BEGIN, D3DISSUE_END
D3DQUERYTYPE_BANDWIDTHTIMINGS	equ 17 ;; D3DISSUE_BEGIN, D3DISSUE_END
D3DQUERYTYPE_CACHEUTILIZATION	equ 18 ;; D3DISSUE_BEGIN, D3DISSUE_END
;; D3D9Ex only --
if NOT defined(D3D_DISABLE_9EX)
D3DQUERYTYPE_MEMORYPRESSURE	equ 19 ;; D3DISSUE_BEGIN, D3DISSUE_END
endif ;; NOT D3D_DISABLE_9EX


;; Flags field for Issue
D3DISSUE_END		equ (1 SHL 0) ;; Tells the runtime to issue the end of a query, changing it's state to "non-signaled".
D3DISSUE_BEGIN		equ (1 SHL 1) ;; Tells the runtime to issue the beginng of a query.


;; Flags field for GetData
D3DGETDATA_FLUSH	equ (1 SHL 0) ;; Tells the runtime to flush if the query is outstanding.


D3DRESOURCESTATS	STRUC
;; Data collected since last Present()
bThrashing		BOOL ?	;; indicates if thrashing
ApproxBytesDownloaded	dd ?	;; Approximate number of bytes downloaded by resource manager
NumEvicts		dd ?	;; number of objects evicted
NumVidCreates		dd ?	;; number of objects created in video memory
LastPri			dd ?	;; priority of last object evicted
NumUsed			dd ?	;; number of objects set to the device
NumUsedInVidMem		dd ?	;; number of objects set to the device, which are already in video memory
;; Persistent data
WorkingSet		dd ?	;; number of objects in video memory
WorkingSetBytes		dd ?	;; number of bytes in video memory
TotalManaged		dd ?	;; total number of managed objects
TotalBytes		dd ?	;; total number of bytes of managed objects
D3DRESOURCESTATS	ENDS

D3DRTYPECOUNT		equ (D3DRTYPE_INDEXBUFFER+1)

D3DDEVINFO_RESOURCEMANAGER STRUC
ifndef WOW64_ENUM_WORKAROUND
stats			D3DRESOURCESTATS D3DRTYPECOUNT dup(<?>)
else
stats			D3DRESOURCESTATS 8 dup(<?>)
endif
D3DDEVINFO_RESOURCEMANAGER ENDS
LPD3DDEVINFO_RESOURCEMANAGER typedef ptr D3DDEVINFO_RESOURCEMANAGER

D3DDEVINFO_D3DVERTEXSTATS STRUC
NumRenderedTriangles	dd ?	;; total number of triangles that are not clipped in this frame
NumExtraClippingTriangles dd ?	;; Number of new triangles generated by clipping
D3DDEVINFO_D3DVERTEXSTATS ENDS
LPD3DDEVINFO_D3DVERTEXSTATS typedef ptr D3DDEVINFO_D3DVERTEXSTATS


D3DDEVINFO_VCACHE	STRUC
Pattern			dd ?	;; bit pattern, return value must be FOUR_CC('C', 'A', 'C', 'H')
OptMethod		dd ?	;; optimization method 0 means longest strips, 1 means vertex cache based
CacheSize		dd ?	;; cache size to optimize for  (only required if type is 1)
MagicNumber		dd ?	;; used to determine when to restart strips (only required if type is 1)
D3DDEVINFO_VCACHE	ENDS
LPD3DDEVINFO_VCACHE	typedef ptr D3DDEVINFO_VCACHE

D3DDEVINFO_D3D9PIPELINETIMINGS STRUC
VertexProcessingTimePercent FLOAT ?
PixelProcessingTimePercent FLOAT ?
OtherGPUProcessingTimePercent FLOAT ?
GPUIdleTimePercent	FLOAT ?
D3DDEVINFO_D3D9PIPELINETIMINGS ENDS

D3DDEVINFO_D3D9INTERFACETIMINGS STRUC
WaitingForGPUToUseApplicationResourceTimePercent FLOAT ?
WaitingForGPUToAcceptMoreCommandsTimePercent FLOAT ?
WaitingForGPUToStayWithinLatencyTimePercent FLOAT ?
WaitingForGPUExclusiveResourceTimePercent FLOAT ?
WaitingForGPUOtherTimePercent FLOAT ?
D3DDEVINFO_D3D9INTERFACETIMINGS ENDS

D3DDEVINFO_D3D9STAGETIMINGS STRUC
MemoryProcessingPercent FLOAT ?
ComputationProcessingPercent FLOAT ?
D3DDEVINFO_D3D9STAGETIMINGS ENDS

D3DDEVINFO_D3D9BANDWIDTHTIMINGS STRUC
MaxBandwidthUtilized	FLOAT ?
FrontEndUploadMemoryUtilizedPercent FLOAT ?
VertexRateUtilizedPercent FLOAT ?
TriangleSetupRateUtilizedPercent FLOAT ?
FillRateUtilizedPercent FLOAT ?
D3DDEVINFO_D3D9BANDWIDTHTIMINGS ENDS

D3DDEVINFO_D3D9CACHEUTILIZATION STRUC
TextureCacheHitRate	FLOAT ? ;; Percentage of cache hits
PostTransformVertexCacheHitRate FLOAT ?
D3DDEVINFO_D3D9CACHEUTILIZATION ENDS

if NOT defined(D3D_DISABLE_9EX)

D3DMEMORYPRESSURE	STRUC
BytesEvictedFromProcess UINT64 ?
SizeOfInefficientAllocation UINT64 ?
LevelOfEfficiency	dd ?
D3DMEMORYPRESSURE	ENDS

endif

;; D3D9Ex only --
if NOT defined(D3D_DISABLE_9EX)

D3DCOMPOSERECTSOP	typedef SDWORD
D3DCOMPOSERECTS_COPY	equ 1
D3DCOMPOSERECTS_OR	equ 2
D3DCOMPOSERECTS_AND	equ 3
D3DCOMPOSERECTS_NEG	equ 4
D3DCOMPOSERECTS_FORCE_DWORD equ 0x7fffffff


D3DCOMPOSERECTDESC	STRUC
X			USHORT ?
Y			USHORT ?	;; Top-left coordinates of a rect in the source surface
_Width			USHORT ?
Height			USHORT ?	;; Dimensions of the rect
D3DCOMPOSERECTDESC	ENDS

D3DCOMPOSERECTDESTINATION STRUC
SrcRectIndex		USHORT ?	;; Index of D3DCOMPOSERECTDESC
Reserved		USHORT ?	;; For alignment
X			USHORT ?
Y			WORD ?		;; Top-left coordinates of the rect in the destination surface
D3DCOMPOSERECTDESTINATION ENDS

D3DCOMPOSERECTS_MAXNUMRECTS	equ 0xFFFF
D3DCONVOLUTIONMONO_MAXWIDTH	equ 7
D3DCONVOLUTIONMONO_MAXHEIGHT	equ D3DCONVOLUTIONMONO_MAXWIDTH
D3DFMT_A1_SURFACE_MAXWIDTH	equ 8192
D3DFMT_A1_SURFACE_MAXHEIGHT	equ 2048


D3DPRESENTSTATS		STRUC
PresentCount		UINT ?
PresentRefreshCount	UINT ?
SyncRefreshCount	UINT ?
SyncQPCTime		LARGE_INTEGER <>
SyncGPUTime		LARGE_INTEGER <>
D3DPRESENTSTATS		ENDS

D3DSCANLINEORDERING	typedef SDWORD
D3DSCANLINEORDERING_UNKNOWN	equ 0
D3DSCANLINEORDERING_PROGRESSIVE equ 1
D3DSCANLINEORDERING_INTERLACED	equ 2


D3DDISPLAYMODEEX	STRUC
_Size			UINT ?
_Width			UINT ?
Height			UINT ?
RefreshRate		UINT ?
Format			D3DFORMAT ?
ScanLineOrdering	D3DSCANLINEORDERING ?
D3DDISPLAYMODEEX	ENDS

D3DDISPLAYMODEFILTER	STRUC
_Size			UINT ?
Format			D3DFORMAT ?
ScanLineOrdering	D3DSCANLINEORDERING ?
D3DDISPLAYMODEFILTER	ENDS


D3DDISPLAYROTATION	typedef SDWORD
D3DDISPLAYROTATION_IDENTITY	equ 1
D3DDISPLAYROTATION_90		equ 2	; Rotated 90 degrees.
D3DDISPLAYROTATION_180		equ 3	; Rotated 180 degrees.
D3DDISPLAYROTATION_270		equ 4	; Rotated 270 degrees.


;; For use in ID3DResource9::SetPriority calls
D3D9_RESOURCE_PRIORITY_MINIMUM	equ 0x28000000
D3D9_RESOURCE_PRIORITY_LOW	equ 0x50000000
D3D9_RESOURCE_PRIORITY_NORMAL	equ 0x78000000
D3D9_RESOURCE_PRIORITY_HIGH	equ 0xa0000000
D3D9_RESOURCE_PRIORITY_MAXIMUM	equ 0xc8000000

D3D_OMAC_SIZE		equ 16

D3D_OMAC		STRUC
Omac			db D3D_OMAC_SIZE dup(?)
D3D_OMAC		ENDS

D3DAUTHENTICATEDCHANNELTYPE typedef SDWORD
D3DAUTHENTICATEDCHANNEL_D3D9 equ 1
D3DAUTHENTICATEDCHANNEL_DRIVER_SOFTWARE equ 2
D3DAUTHENTICATEDCHANNEL_DRIVER_HARDWARE equ 3

D3DAUTHENTICATEDCHANNEL_QUERY_INPUT STRUC
QueryType		GUID <>
hChannel		HANDLE ?
SequenceNumber		UINT ?
D3DAUTHENTICATEDCHANNEL_QUERY_INPUT ENDS

D3DAUTHENTICATEDCHANNEL_QUERY_OUTPUT STRUC
omac			D3D_OMAC <>
QueryType		GUID <>
hChannel		HANDLE ?
SequenceNumber		UINT ?
ReturnCode		HRESULT ?
D3DAUTHENTICATEDCHANNEL_QUERY_OUTPUT ENDS

DEFINE_GUID(D3DAUTHENTICATEDQUERY_PROTECTION, 0xa84eb584, 0xc495, 0x48aa, 0xb9, 0x4d, 0x8b, 0xd2, 0xd6, 0xfb, 0xce, 0x5);

D3DAUTHENTICATEDCHANNEL_PROTECTION_FLAGS STRUC
UNION
 STRUC
  ProtectionEnabled	UINT ? ;	 : 1 UINT ?
;  OverlayOrFullscreenRequired		 : 1 UINT ?
;  Reserved				 : 30 UINT ?
 ENDS
 Value			UINT ?
ENDS
D3DAUTHENTICATEDCHANNEL_PROTECTION_FLAGS ENDS

D3DAUTHENTICATEDCHANNEL_QUERYPROTECTION_OUTPUT STRUC
Output			D3DAUTHENTICATEDCHANNEL_QUERY_OUTPUT <>
ProtectionFlags		D3DAUTHENTICATEDCHANNEL_PROTECTION_FLAGS <>
D3DAUTHENTICATEDCHANNEL_QUERYPROTECTION_OUTPUT ENDS


DEFINE_GUID(D3DAUTHENTICATEDQUERY_CHANNELTYPE, 0xbc1b18a5, 0xb1fb, 0x42ab, 0xbd, 0x94, 0xb5, 0x82, 0x8b, 0x4b, 0xf7, 0xbe);

D3DAUTHENTICATEDCHANNEL_QUERYCHANNELTYPE_OUTPUT STRUC
Output			D3DAUTHENTICATEDCHANNEL_QUERY_OUTPUT <>
ChannelType		D3DAUTHENTICATEDCHANNELTYPE ?
D3DAUTHENTICATEDCHANNEL_QUERYCHANNELTYPE_OUTPUT ENDS


DEFINE_GUID(D3DAUTHENTICATEDQUERY_DEVICEHANDLE, 0xec1c539d, 0x8cff, 0x4e2a, 0xbc, 0xc4, 0xf5, 0x69, 0x2f, 0x99, 0xf4, 0x80);

D3DAUTHENTICATEDCHANNEL_QUERYDEVICEHANDLE_OUTPUT STRUC
Output			D3DAUTHENTICATEDCHANNEL_QUERY_OUTPUT <>
DeviceHandle		HANDLE ?
D3DAUTHENTICATEDCHANNEL_QUERYDEVICEHANDLE_OUTPUT ENDS


DEFINE_GUID(D3DAUTHENTICATEDQUERY_CRYPTOSESSION, 0x2634499e, 0xd018, 0x4d74, 0xac, 0x17, 0x7f, 0x72, 0x40, 0x59, 0x52, 0x8d);

D3DAUTHENTICATEDCHANNEL_QUERYCRYPTOSESSION_INPUT STRUC
Input			D3DAUTHENTICATEDCHANNEL_QUERY_INPUT <>
DXVA2DecodeHandle	HANDLE ?
D3DAUTHENTICATEDCHANNEL_QUERYCRYPTOSESSION_INPUT ENDS

D3DAUTHENTICATEDCHANNEL_QUERYCRYPTOSESSION_OUTPUT STRUC
Output			D3DAUTHENTICATEDCHANNEL_QUERY_OUTPUT <>
DXVA2DecodeHandle	HANDLE ?
CryptoSessionHandle	HANDLE ?
DeviceHandle		HANDLE ?
D3DAUTHENTICATEDCHANNEL_QUERYCRYPTOSESSION_OUTPUT ENDS


DEFINE_GUID(D3DAUTHENTICATEDQUERY_RESTRICTEDSHAREDRESOURCEPROCESSCOUNT, 0xdb207b3, 0x9450, 0x46a6, 0x82, 0xde, 0x1b, 0x96, 0xd4, 0x4f, 0x9c, 0xf2);

D3DAUTHENTICATEDCHANNEL_QUERYRESTRICTEDSHAREDRESOURCEPROCESSCOUNT_OUTPUT STRUC
Output			D3DAUTHENTICATEDCHANNEL_QUERY_OUTPUT <>
NumRestrictedSharedResourceProcesses UINT ?
D3DAUTHENTICATEDCHANNEL_QUERYRESTRICTEDSHAREDRESOURCEPROCESSCOUNT_OUTPUT ENDS


DEFINE_GUID(D3DAUTHENTICATEDQUERY_RESTRICTEDSHAREDRESOURCEPROCESS, 0x649bbadb, 0xf0f4, 0x4639, 0xa1, 0x5b, 0x24, 0x39, 0x3f, 0xc3, 0xab, 0xac);

D3DAUTHENTICATEDCHANNEL_QUERYRESTRICTEDSHAREDRESOURCEPROCESS_INPUT STRUC
Input			D3DAUTHENTICATEDCHANNEL_QUERY_INPUT <>
ProcessIndex		UINT ?
D3DAUTHENTICATEDCHANNEL_QUERYRESTRICTEDSHAREDRESOURCEPROCESS_INPUT ENDS

D3DAUTHENTICATEDCHANNEL_PROCESSIDENTIFIERTYPE typedef SDWORD
PROCESSIDTYPE_UNKNOWN	equ 0
PROCESSIDTYPE_DWM	equ 1
PROCESSIDTYPE_HANDLE	equ 2

D3DAUTHENTICATEDCHANNEL_QUERYRESTRICTEDSHAREDRESOURCEPROCESS_OUTPUT STRUC
Output			D3DAUTHENTICATEDCHANNEL_QUERY_OUTPUT <>
ProcessIndex		UINT ?
ProcessIdentifer	D3DAUTHENTICATEDCHANNEL_PROCESSIDENTIFIERTYPE ?
ProcessHandle		HANDLE ?
D3DAUTHENTICATEDCHANNEL_QUERYRESTRICTEDSHAREDRESOURCEPROCESS_OUTPUT ENDS


DEFINE_GUID(D3DAUTHENTICATEDQUERY_UNRESTRICTEDPROTECTEDSHAREDRESOURCECOUNT, 0x12f0bd6, 0xe662, 0x4474, 0xbe, 0xfd, 0xaa, 0x53, 0xe5, 0x14, 0x3c, 0x6d)

D3DAUTHENTICATEDCHANNEL_QUERYUNRESTRICTEDPROTECTEDSHAREDRESOURCECOUNT_OUTPUT STRUC
Output			D3DAUTHENTICATEDCHANNEL_QUERY_OUTPUT <>
NumUnrestrictedProtectedSharedResources UINT ?
D3DAUTHENTICATEDCHANNEL_QUERYUNRESTRICTEDPROTECTEDSHAREDRESOURCECOUNT_OUTPUT ENDS


DEFINE_GUID(D3DAUTHENTICATEDQUERY_OUTPUTIDCOUNT, 0x2c042b5e, 0x8c07, 0x46d5, 0xaa, 0xbe, 0x8f, 0x75, 0xcb, 0xad, 0x4c, 0x31);

D3DAUTHENTICATEDCHANNEL_QUERYOUTPUTIDCOUNT_INPUT STRUC
Input			D3DAUTHENTICATEDCHANNEL_QUERY_INPUT <>
DeviceHandle		HANDLE ?
CryptoSessionHandle	HANDLE ?
D3DAUTHENTICATEDCHANNEL_QUERYOUTPUTIDCOUNT_INPUT ENDS

D3DAUTHENTICATEDCHANNEL_QUERYOUTPUTIDCOUNT_OUTPUT STRUC
Output			D3DAUTHENTICATEDCHANNEL_QUERY_OUTPUT <>
DeviceHandle		HANDLE ?
CryptoSessionHandle	HANDLE ?
NumOutputIDs		UINT ?
D3DAUTHENTICATEDCHANNEL_QUERYOUTPUTIDCOUNT_OUTPUT ENDS


DEFINE_GUID(D3DAUTHENTICATEDQUERY_OUTPUTID, 0x839ddca3, 0x9b4e, 0x41e4, 0xb0, 0x53, 0x89, 0x2b, 0xd2, 0xa1, 0x1e, 0xe7);

D3DAUTHENTICATEDCHANNEL_QUERYOUTPUTID_INPUT STRUC
Input			D3DAUTHENTICATEDCHANNEL_QUERY_INPUT <>
DeviceHandle		HANDLE ?
CryptoSessionHandle	HANDLE ?
OutputIDIndex		UINT ?
D3DAUTHENTICATEDCHANNEL_QUERYOUTPUTID_INPUT ENDS

D3DAUTHENTICATEDCHANNEL_QUERYOUTPUTID_OUTPUT STRUC
Output			D3DAUTHENTICATEDCHANNEL_QUERY_OUTPUT <>
DeviceHandle		HANDLE ?
CryptoSessionHandle	HANDLE ?
OutputIDIndex		UINT ?
OutputID		UINT64 ?
D3DAUTHENTICATEDCHANNEL_QUERYOUTPUTID_OUTPUT ENDS


DEFINE_GUID(D3DAUTHENTICATEDQUERY_ACCESSIBILITYATTRIBUTES, 0x6214d9d2, 0x432c, 0x4abb, 0x9f, 0xce, 0x21, 0x6e, 0xea, 0x26, 0x9e, 0x3b);

D3DBUSTYPE		typedef SDWORD
D3DBUSTYPE_OTHER	equ 0x00000000
D3DBUSTYPE_PCI		equ 0x00000001
D3DBUSTYPE_PCIX		equ 0x00000002
D3DBUSTYPE_PCIEXPRESS	equ 0x00000003
D3DBUSTYPE_AGP		equ 0x00000004
D3DBUSIMPL_MODIFIER_INSIDE_OF_CHIPSET equ 0x00010000
D3DBUSIMPL_MODIFIER_TRACKS_ON_MOTHER_BOARD_TO_CHIP equ 0x00020000
D3DBUSIMPL_MODIFIER_TRACKS_ON_MOTHER_BOARD_TO_SOCKET equ 0x00030000
D3DBUSIMPL_MODIFIER_DAUGHTER_BOARD_CONNECTOR equ 0x00040000
D3DBUSIMPL_MODIFIER_DAUGHTER_BOARD_CONNECTOR_INSIDE_OF_NUAE equ 0x00050000
D3DBUSIMPL_MODIFIER_NON_STANDARD equ 0x80000000

D3DAUTHENTICATEDCHANNEL_QUERYINFOBUSTYPE_OUTPUT STRUC
Output			D3DAUTHENTICATEDCHANNEL_QUERY_OUTPUT <>
BusType			D3DBUSTYPE ?
bAccessibleInContiguousBlocks BOOL ?
bAccessibleInNonContiguousBlocks BOOL ?
D3DAUTHENTICATEDCHANNEL_QUERYINFOBUSTYPE_OUTPUT ENDS


DEFINE_GUID(D3DAUTHENTICATEDQUERY_ENCRYPTIONWHENACCESSIBLEGUIDCOUNT, 0xb30f7066, 0x203c, 0x4b07, 0x93, 0xfc, 0xce, 0xaa, 0xfd, 0x61, 0x24, 0x1e);

D3DAUTHENTICATEDCHANNEL_QUERYEVICTIONENCRYPTIONGUIDCOUNT_OUTPUT STRUC
Output			D3DAUTHENTICATEDCHANNEL_QUERY_OUTPUT <>
NumEncryptionGuids	UINT ?
D3DAUTHENTICATEDCHANNEL_QUERYEVICTIONENCRYPTIONGUIDCOUNT_OUTPUT ENDS


DEFINE_GUID(D3DAUTHENTICATEDQUERY_ENCRYPTIONWHENACCESSIBLEGUID, 0xf83a5958, 0xe986, 0x4bda, 0xbe, 0xb0, 0x41, 0x1f, 0x6a, 0x7a, 0x1, 0xb7);

D3DAUTHENTICATEDCHANNEL_QUERYEVICTIONENCRYPTIONGUID_INPUT STRUC
Input			D3DAUTHENTICATEDCHANNEL_QUERY_INPUT <>
EncryptionGuidIndex	UINT ?
D3DAUTHENTICATEDCHANNEL_QUERYEVICTIONENCRYPTIONGUID_INPUT ENDS

D3DAUTHENTICATEDCHANNEL_QUERYEVICTIONENCRYPTIONGUID_OUTPUT STRUC
Output			D3DAUTHENTICATEDCHANNEL_QUERY_OUTPUT <>
EncryptionGuidIndex	UINT ?
EncryptionGuid		GUID <>
D3DAUTHENTICATEDCHANNEL_QUERYEVICTIONENCRYPTIONGUID_OUTPUT ENDS


DEFINE_GUID(D3DAUTHENTICATEDQUERY_CURRENTENCRYPTIONWHENACCESSIBLE, 0xec1791c7, 0xdad3, 0x4f15, 0x9e, 0xc3, 0xfa, 0xa9, 0x3d, 0x60, 0xd4, 0xf0);

D3DAUTHENTICATEDCHANNEL_QUERYUNCOMPRESSEDENCRYPTIONLEVEL_OUTPUT STRUC
Output			D3DAUTHENTICATEDCHANNEL_QUERY_OUTPUT <>
EncryptionGuid		GUID <>
D3DAUTHENTICATEDCHANNEL_QUERYUNCOMPRESSEDENCRYPTIONLEVEL_OUTPUT ENDS


D3DAUTHENTICATEDCHANNEL_CONFIGURE_INPUT STRUC
omac			D3D_OMAC <>
ConfigureType		GUID <>
hChannel		HANDLE ?
SequenceNumber		UINT ?
D3DAUTHENTICATEDCHANNEL_CONFIGURE_INPUT ENDS

D3DAUTHENTICATEDCHANNEL_CONFIGURE_OUTPUT STRUC
omac			D3D_OMAC <>
ConfigureType		GUID <>
hChannel		HANDLE ?
SequenceNumber		UINT ?
ReturnCode		HRESULT ?
D3DAUTHENTICATEDCHANNEL_CONFIGURE_OUTPUT ENDS

DEFINE_GUID(D3DAUTHENTICATEDCONFIGURE_INITIALIZE, 0x6114bdb, 0x3523, 0x470a, 0x8d, 0xca, 0xfb, 0xc2, 0x84, 0x51, 0x54, 0xf0)

D3DAUTHENTICATEDCHANNEL_CONFIGUREINITIALIZE STRUC
Parameters		D3DAUTHENTICATEDCHANNEL_CONFIGURE_INPUT <>
StartSequenceQuery	UINT ?
StartSequenceConfigure	UINT ?
D3DAUTHENTICATEDCHANNEL_CONFIGUREINITIALIZE ENDS


DEFINE_GUID(D3DAUTHENTICATEDCONFIGURE_PROTECTION, 0x50455658, 0x3f47, 0x4362, 0xbf, 0x99, 0xbf, 0xdf, 0xcd, 0xe9, 0xed, 0x29);

D3DAUTHENTICATEDCHANNEL_CONFIGUREPROTECTION STRUC
Parameters		D3DAUTHENTICATEDCHANNEL_CONFIGURE_INPUT <>
Protections		D3DAUTHENTICATEDCHANNEL_PROTECTION_FLAGS <>
D3DAUTHENTICATEDCHANNEL_CONFIGUREPROTECTION ENDS


DEFINE_GUID(D3DAUTHENTICATEDCONFIGURE_CRYPTOSESSION, 0x6346cc54, 0x2cfc, 0x4ad4, 0x82, 0x24, 0xd1, 0x58, 0x37, 0xde, 0x77, 0x0);

D3DAUTHENTICATEDCHANNEL_CONFIGURECRYPTOSESSION STRUC
Parameters		D3DAUTHENTICATEDCHANNEL_CONFIGURE_INPUT <>
DXVA2DecodeHandle	HANDLE ?
CryptoSessionHandle	HANDLE ?
DeviceHandle		HANDLE ?
D3DAUTHENTICATEDCHANNEL_CONFIGURECRYPTOSESSION ENDS


DEFINE_GUID(D3DAUTHENTICATEDCONFIGURE_SHAREDRESOURCE, 0x772d047, 0x1b40, 0x48e8, 0x9c, 0xa6, 0xb5, 0xf5, 0x10, 0xde, 0x9f, 0x1);

D3DAUTHENTICATEDCHANNEL_CONFIGURESHAREDRESOURCE STRUC
Parameters		D3DAUTHENTICATEDCHANNEL_CONFIGURE_INPUT <>
ProcessIdentiferType	D3DAUTHENTICATEDCHANNEL_PROCESSIDENTIFIERTYPE ?
ProcessHandle		HANDLE ?
AllowAccess		BOOL ?
D3DAUTHENTICATEDCHANNEL_CONFIGURESHAREDRESOURCE ENDS

DEFINE_GUID(D3DAUTHENTICATEDCONFIGURE_ENCRYPTIONWHENACCESSIBLE, 0x41fff286, 0x6ae0, 0x4d43, 0x9d, 0x55, 0xa4, 0x6e, 0x9e, 0xfd, 0x15, 0x8a);

D3DAUTHENTICATEDCHANNEL_CONFIGUREUNCOMPRESSEDENCRYPTION STRUC
Parameters		D3DAUTHENTICATEDCHANNEL_CONFIGURE_INPUT <>
EncryptionGuid		GUID <>
D3DAUTHENTICATEDCHANNEL_CONFIGUREUNCOMPRESSEDENCRYPTION ENDS

D3DENCRYPTED_BLOCK_INFO STRUC
NumEncryptedBytesAtBeginning UINT ?
NumBytesInSkipPattern	UINT ?
NumBytesInEncryptPattern UINT ?
D3DENCRYPTED_BLOCK_INFO ENDS

D3DAES_CTR_IV		STRUC
IV			UINT64 ?	;; Big-Endian IV
Count			UINT64 ?	;; Big-Endian Block Count
D3DAES_CTR_IV		ENDS

endif ;; NOT D3D_DISABLE_9EX
;; -- D3D9Ex only
endif ;; (DIRECT3D_VERSION GE 0x0900)
.list
endif ;; _d3d9TYPES(P)_H_


