include d3dx9.inc
ifndef _D3DX9MESH_H
_D3DX9MESH_H equ <>

DEFINE_GUID(IID_ID3DXBaseMesh, 0x7ed943dd, 0x52e8, 0x40b5, 0xa8, 0xd8, 0x76, 0x68, 0x5c, 0x40, 0x63, 0x30);
DEFINE_GUID(IID_ID3DXMesh,     0x4020e5c2, 0x1403, 0x4929, 0x88, 0x3f, 0xe2, 0xe8, 0x49, 0xfa, 0xc1, 0x95);
DEFINE_GUID(IID_ID3DXPMesh,    0x8875769a, 0xd579, 0x4088, 0xaa, 0xeb, 0x53, 0x4d, 0x1a, 0xd8, 0x4e, 0x96);
DEFINE_GUID(IID_ID3DXSPMesh,   0x667ea4c7, 0xf1cd, 0x4386, 0xb5, 0x23, 0x7c, 0x02, 0x90, 0xb8, 0x3c, 0xc5);
DEFINE_GUID(IID_ID3DXSkinInfo, 0x11eaa540, 0xf9a6, 0x4d49, 0xae, 0x6a, 0xe1, 0x92, 0x21, 0xf7, 0x0c, 0xc4);
DEFINE_GUID(IID_ID3DXPatchMesh,0x3ce6cc22, 0xdbf2, 0x44f4, 0x89, 0x4d, 0xf9, 0xc3, 0x4a, 0x33, 0x71, 0x39);
DEFINE_GUID(IID_ID3DXPRTBuffer,		  0xf1827e47, 0x00a8, 0x49cd, 0x90, 0x8c, 0x9d, 0x11, 0x95, 0x5f, 0x87, 0x28);
DEFINE_GUID(IID_ID3DXPRTCompBuffer,	  0xa758d465, 0xfe8d, 0x45ad, 0x9c, 0xf0, 0xd0, 0x1e, 0x56, 0x26, 0x6a, 0x07);
DEFINE_GUID(IID_ID3DXTextureGutterHelper, 0x838f01ec, 0x9729, 0x4527, 0xaa, 0xdb, 0xdf, 0x70, 0xad, 0xe7, 0xfe, 0xa9);
DEFINE_GUID(IID_ID3DXPRTEngine,		  0x683a4278, 0xcd5f, 0x4d24, 0x90, 0xad, 0xc4, 0xe1, 0xb6, 0x85, 0x5d, 0x53);

UNUSED16		equ (0xffff)
UNUSED32		equ (0xffffffff)

_MAX_FVF_DECL_SIZE	typedef sdword
MAX_FVF_DECL_SIZE	equ MAXD3DDECLLENGTH + 1

_D3DXMESH		typedef sdword
D3DXMESH_32BIT		equ 0x001
D3DXMESH_DONOTCLIP	equ 0x002
D3DXMESH_POINTS		equ 0x004
D3DXMESH_RTPATCHES	equ 0x008
D3DXMESH_NPATCHES	equ 0x4000
D3DXMESH_VB_SYSTEMMEM	equ 0x010
D3DXMESH_VB_MANAGED	equ 0x020
D3DXMESH_VB_WRITEONLY	equ 0x040
D3DXMESH_VB_DYNAMIC	equ 0x080
D3DXMESH_VB_SOFTWAREPROCESSING equ 0x8000
D3DXMESH_IB_SYSTEMMEM	equ 0x100
D3DXMESH_IB_MANAGED	equ 0x200
D3DXMESH_IB_WRITEONLY	equ 0x400
D3DXMESH_IB_DYNAMIC	equ 0x800
D3DXMESH_IB_SOFTWAREPROCESSING equ 0x10000
D3DXMESH_VB_SHARE	equ 0x1000
D3DXMESH_USEHWONLY	equ 0x2000
D3DXMESH_SYSTEMMEM	equ 0x110
D3DXMESH_MANAGED	equ 0x220
D3DXMESH_WRITEONLY	equ 0x440
D3DXMESH_DYNAMIC	equ 0x880
D3DXMESH_SOFTWAREPROCESSING equ 0x18000

_D3DXMESHOPT		typedef sdword
D3DXMESHOPT_DEVICEINDEPENDENT equ 0x00400000
D3DXMESHOPT_COMPACT	equ 0x01000000
D3DXMESHOPT_ATTRSORT	equ 0x02000000
D3DXMESHOPT_VERTEXCACHE equ 0x04000000
D3DXMESHOPT_STRIPREORDER equ 0x08000000
D3DXMESHOPT_IGNOREVERTS equ 0x10000000
D3DXMESHOPT_DONOTSPLIT	equ 0x20000000

D3DXPATCHMESHTYPE	typedef SDWORD
D3DXPATCHMESH_RECT	equ 0
D3DXPATCHMESH_TRI	equ 1
D3DXPATCHMESH_NPATCH	equ 2
D3DXPATCHMESH_FORCE_DWORD equ 0x7fffffff

_D3DXPATCHMESH		typedef SDWORD
D3DXPATCHMESH_DEFAULT	equ 0

_D3DXMESHSIMP		typedef SDWORD
D3DXMESHSIMP_VERTEX	equ 0x1
D3DXMESHSIMP_FACE	equ 0x2

D3DXCLEANTYPE		typedef SDWORD
D3DXCLEAN_BACKFACING	equ 0x00000001
D3DXCLEAN_BOWTIES	equ 0x00000002
D3DXCLEAN_SKINNING	equ D3DXCLEAN_BACKFACING
D3DXCLEAN_OPTIMIZATION	equ D3DXCLEAN_BACKFACING
D3DXCLEAN_SIMPLIFICATION equ D3DXCLEAN_BACKFACING | D3DXCLEAN_BOWTIES

D3DXTANGENT		typedef SDWORD
D3DXTANGENT_WRAP_U	equ 0x0001
D3DXTANGENT_WRAP_V	equ 0x0002
D3DXTANGENT_WRAP_UV	equ 0x0003
D3DXTANGENT_DONT_NORMALIZE_PARTIALS equ 0x0004
D3DXTANGENT_DONT_ORTHOGONALIZE equ 0x0008
D3DXTANGENT_ORTHOGONALIZE_FROM_V equ 0x0010
D3DXTANGENT_ORTHOGONALIZE_FROM_U equ 0x0020
D3DXTANGENT_WEIGHT_BY_AREA equ 0x0040
D3DXTANGENT_WEIGHT_EQUAL equ 0x0080
D3DXTANGENT_WIND_CW	equ 0x0100
D3DXTANGENT_CALCULATE_NORMALS equ 0x0200
D3DXTANGENT_GENERATE_IN_PLACE equ 0x0400

D3DXIMT			typedef SDWORD
D3DXIMT_WRAP_U		equ 0x01
D3DXIMT_WRAP_V		equ 0x02
D3DXIMT_WRAP_UV		equ 0x03

D3DXUVATLAS		typedef SDWORD
D3DXUVATLAS_DEFAULT	equ 0x00
D3DXUVATLAS_GEODESIC_FAST equ 0x01
D3DXUVATLAS_GEODESIC_QUALITY equ 0x02

D3DXEFFECTDEFAULTTYPE	typedef SDWORD
D3DXEDT_STRING		equ 1
D3DXEDT_FLOATS		equ 2
D3DXEDT_DWORD		equ 3
D3DXEDT_FORCEDWORD	equ 0x7fffffff

_D3DXWELDEPSILONSFLAGS	typedef SDWORD
D3DXWELDEPSILONS_WELDALL equ 0x1
D3DXWELDEPSILONS_WELDPARTIALMATCHES equ 0x2
D3DXWELDEPSILONS_DONOTREMOVEVERTICES equ 0x4
D3DXWELDEPSILONS_DONOTSPLIT equ 0x8

D3DXSHCOMPRESSQUALITYTYPE typedef SDWORD
D3DXSHCQUAL_FASTLOWQUALITY equ 1
D3DXSHCQUAL_SLOWHIGHQUALITY equ 2
D3DXSHCQUAL_FORCE_DWORD equ 0x7fffffff

D3DXSHGPUSIMOPT		typedef SDWORD
D3DXSHGPUSIMOPT_SHADOWRES256 equ 1
D3DXSHGPUSIMOPT_SHADOWRES512 equ 0
D3DXSHGPUSIMOPT_SHADOWRES1024 equ 2
D3DXSHGPUSIMOPT_SHADOWRES2048 equ 3
D3DXSHGPUSIMOPT_HIGHQUALITY equ 4
D3DXSHGPUSIMOPT_FORCE_DWORD equ 0x7fffffff

LPD3DXBASEMESH		typedef ptr ID3DXBaseMesh
LPD3DXMESH		typedef ptr ID3DXMesh
LPD3DXPMESH		typedef ptr ID3DXPMesh
LPD3DXSPMESH		typedef ptr ID3DXSPMesh
LPD3DXSKININFO		typedef ptr ID3DXSkinInfo
LPD3DXPATCHMESH		typedef ptr ID3DXPatchMesh
LPD3DXPRTBUFFER		typedef ptr ID3DXPRTBuffer
LPD3DXPRTCOMPBUFFER	typedef ptr ID3DXPRTCompBuffer
LPD3DXPRTENGINE		typedef ptr ID3DXPRTEngine
LPD3DXTEXTUREGUTTERHELPER typedef ptr ID3DXTextureGutterHelper

D3DXATTRIBUTERANGE	STRUC
AttribId		dd ?
FaceStart		dd ?
FaceCount		dd ?
VertexStart		dd ?
VertexCount		dd ?
D3DXATTRIBUTERANGE	ENDS

LPD3DXATTRIBUTERANGE	typedef ptr D3DXATTRIBUTERANGE

D3DXMATERIAL		STRUC
MatD3D			D3DMATERIAL9 <>
pTextureFilename	LPSTR ?
D3DXMATERIAL		ENDS
LPD3DXMATERIAL		typedef ptr D3DXMATERIAL

D3DXEFFECTDEFAULT	STRUC
pParamName		LPSTR ?
_Type			D3DXEFFECTDEFAULTTYPE ?
NumBytes		dd ?
pValue			PVOID ?
D3DXEFFECTDEFAULT	ENDS
LPD3DXEFFECTDEFAULT	typedef ptr D3DXEFFECTDEFAULT

D3DXEFFECTINSTANCE	STRUC
pEffectFilename		LPSTR ?
NumDefaults		dd ?
pDefaults		LPD3DXEFFECTDEFAULT ?
D3DXEFFECTINSTANCE	ENDS
LPD3DXEFFECTINSTANCE	typedef ptr D3DXEFFECTINSTANCE

D3DXATTRIBUTEWEIGHTS	STRUC
Position		FLOAT ?
Boundary		FLOAT ?
Normal			FLOAT ?
Diffuse			FLOAT ?
Specular		FLOAT ?
Texcoords		FLOAT 8 dup(?)
Tangent			FLOAT ?
Binormal		FLOAT ?
D3DXATTRIBUTEWEIGHTS	ENDS
LPD3DXATTRIBUTEWEIGHTS	typedef ptr D3DXATTRIBUTEWEIGHTS

D3DXWELDEPSILONS	STRUC
Position		FLOAT ?
BlendWeights		FLOAT ?
Normals			FLOAT ?
PSize			FLOAT ?
Specular		FLOAT ?
Diffuse			FLOAT ?
Texcoords		FLOAT 8 dup(?)
Tangent			FLOAT ?
Binormal		FLOAT ?
TessFactor		FLOAT ?
D3DXWELDEPSILONS	ENDS
LPD3DXWELDEPSILONS	typedef ptr D3DXWELDEPSILONS

D3DXBONECOMBINATION	STRUC
AttribId		dd ?
FaceStart		dd ?
FaceCount		dd ?
VertexStart		dd ?
VertexCout		dd ?
BoneId			LPDWORD ?
D3DXBONECOMBINATION	ENDS
LPD3DXBONECOMBINATION	typedef ptr D3DXBONECOMBINATION

D3DXPATCHINFO		STRUC
PatchType		D3DXPATCHMESHTYPE ?
Degree			D3DDEGREETYPE ?
Basis			D3DBASISTYPE ?
D3DXPATCHINFO		ENDS
LPD3DXPATCHINFO		typedef ptr D3DXPATCHINFO

D3DXINTERSECTINFO	STRUC
FaceIndex		dd ?
U			FLOAT ?
V			FLOAT ?
Dist			FLOAT ?
D3DXINTERSECTINFO	ENDS
LPD3DXINTERSECTINFO	typedef ptr D3DXINTERSECTINFO

D3DXSHMATERIAL		STRUC
Diffuse			D3DCOLORVALUE <>
bMirror			BOOL ?
bSubSurf		BOOL ?
RelativeIndexOfRefraction FLOAT ?
Absorption		D3DCOLORVALUE <>
ReducedScattering	D3DCOLORVALUE <>
D3DXSHMATERIAL		ENDS

D3DXSHPRTSPLITMESHVERTDATA STRUC
uVertRemap		UINT ?
uSubCluster		UINT ?
ucVertStatus		UCHAR ?
D3DXSHPRTSPLITMESHVERTDATA ENDS

D3DXSHPRTSPLITMESHCLUSTERDATA STRUC
uVertStart		UINT ?
uVertLength		UINT ?
uFaceStart		UINT ?
uFaceLength		UINT ?
uClusterStart		UINT ?
uClusterLength		UINT ?
D3DXSHPRTSPLITMESHCLUSTERDATA ENDS

XFILECOMPRESSEDANIMATIONSET STRUC
CompressedBlockSize	dd ?
TicksPerSec		FLOAT ?
PlaybackType		dd ?
BufferLength		dd ?
XFILECOMPRESSEDANIMATIONSET ENDS

;HRESULT

CALLBACK(LPD3DXUVATLASCB, :FLOAT, :PVOID)
CALLBACK(LPD3DXIMTSIGNALCALLBACK, :ptr D3DXVECTOR2, :UINT, :UINT, :PVOID, :ptr FLOAT)
CALLBACK(LPD3DXSHPRTSIMCB, :FLOAT, :PVOID)

.comdef ID3DXBaseMesh : public IUnknown

    DrawSubset		proc :DWORD
    GetNumFaces		proc
    GetNumVertices	proc
    GetFVF		proc
    GetDeclaration	proc :ptr
    GetNumBytesPerVertex proc
    GetOptions		proc
    GetDevice		proc :ptr
    CloneMeshFVF	proc :DWORD, :DWORD, :ptr, :ptr
    CloneMesh		proc :DWORD, :ptr, :ptr, :ptr
    GetVertexBuffer	proc :ptr
    GetIndexBuffer	proc :ptr
    LockVertexBuffer	proc :DWORD, :ptr
    UnlockVertexBuffer	proc
    LockIndexBuffer	proc :DWORD, :ptr
    UnlockIndexBuffer	proc
    GetAttributeTable	proc :ptr, :ptr
    ConvertPointRepsToAdjacency proc :ptr, :ptr
    ConvertAdjacencyToPointReps proc :ptr, :ptr
    GenerateAdjacency	proc :FLOAT, :ptr
    UpdateSemantics	proc :ptr

    .ends

.comdef ID3DXMesh : public ID3DXBaseMesh

    LockAttributeBuffer proc :DWORD, :ptr
    UnlockAttributeBuffer proc
    Optimize		proc :DWORD, :ptr, :ptr, :ptr, :ptr, :ptr
    OptimizeInplace	proc :DWORD, :ptr, :ptr, :ptr, :ptr
    SetAttributeTable	proc :ptr, :DWORD

    .ends


.comdef ID3DXPMesh : public ID3DXBaseMesh

    ClonePMeshFVF	proc :DWORD, :DWORD, :ptr, :ptr
    ClonePMesh		proc :DWORD, :ptr, :ptr, :ptr
    SetNumFaces		proc :DWORD
    SetNumVertices	proc :DWORD
    GetMaxFaces		proc
    GetMinFaces		proc
    GetMaxVertices	proc
    GetMinVertices	proc
    Save		proc :ptr, :ptr, :ptr, :DWORD
    Optimize		proc :DWORD, :ptr, :ptr, :ptr, :ptr
    OptimizeBaseLOD	proc :DWORD, :ptr
    TrimByFaces		proc :DWORD, :DWORD, :ptr, :ptr
    TrimByVertices	proc :DWORD, :DWORD, :ptr, :ptr
    GetAdjacency	proc :ptr
    GenerateVertexHistory proc :ptr

    .ends


.comdef ID3DXSPMesh : public IUnknown

    GetNumFaces		proc
    GetNumVertices	proc
    GetNumFVF		proc
    GetDeclaration	proc :ptr
    GetOptions		proc
    GetDevice		proc :ptr
    CloneMeshFVF	proc :DWORD, :DWORD, :ptr, :ptr, :ptr, :ptr
    CloneMesh		proc :DWORD, :ptr, :ptr, :ptr, :ptr, :ptr
    ClonePMeshFVF	proc :DWORD, :DWORD, :ptr, :ptr, :ptr, :ptr
    ClonePMesh		proc :DWORD, :ptr, :ptr, :ptr, :ptr, :ptr
    ReduceFaces		proc :DWORD
    ReduceVertices	proc :DWORD
    GetMaxFaces		proc
    GetMaxVertices	proc
    GetVertexAttributeWeights proc :LPD3DXATTRIBUTEWEIGHTS
    GetVertexWeights	proc :ptr

    .ends


.comdef ID3DXPatchMesh : public IUnknown

    GetNumPatches	proc
    GetNumVertices	proc
    GetDeclaration	proc :ptr
    GetControlVerticesPerPatch proc
    GetOptions		proc
    GetDevice		proc :ptr
    GetPatchInfo	proc :LPD3DXPATCHINFO
    GetVertexBuffer	proc :ptr
    GetIndexBuffer	proc :ptr
    LockVertexBuffer	proc :DWORD, :ptr
    UnlockVertexBuffer	proc
    LockIndexBuffer	proc :DWORD, :ptr
    UnlockIndexBuffer	proc
    LockAttributeBuffer proc :DWORD, :ptr
    UnlockAttributeBuffer proc
    GetTessSize		proc :FLOAT, :DWORD, :ptr, :ptr
    GenerateAdjacency	proc :FLOAT
    CloneMesh		proc :DWORD, :ptr, :ptr
    Optimize		proc :DWORD
    SetDisplaceParam	proc :ptr, :D3DTEXTUREFILTERTYPE, :D3DTEXTUREFILTERTYPE, :D3DTEXTUREFILTERTYPE, :D3DTEXTUREADDRESS, :DWORD
    GetDisplaceParam	proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    Tessellate		proc :float, :ptr
    TessellateAdaptive	proc :ptr, :DWORD, :DWORD, :ptr

    .ends


.comdef ID3DXSkinInfo : public IUnknown

    SetBoneInfluence	proc :DWORD, :DWORD, :ptr, :ptr
    SetBoneVertexInfluence proc :DWORD, :DWORD, :float
    GetNumBoneInfluences proc :DWORD
    GetBoneInfluence	proc :DWORD, :ptr, :ptr
    GetBoneVertexInfluence proc :DWORD, :DWORD, :ptr, :ptr
    GetMaxVertexInfluences proc :ptr
    GetNumBones		proc
    FindBoneVertexInfluenceIndex proc :DWORD, :DWORD, :ptr
    GetMaxFaceInfluences proc :ptr, :DWORD, :ptr
    SetMinBoneInfluence proc :FLOAT
    GetMinBoneInfluence proc
    SetBoneName		proc :DWORD, :ptr
    GetBoneName		proc :DWORD
    SetBoneOffsetMatrix proc :DWORD, :ptr
    GetBoneOffsetMatrix proc :DWORD
    Clone		proc :ptr
    Remap		proc :DWORD, :ptr
    SetFVF		proc :DWORD
    SetDeclaration	proc :ptr
    GetFVF		proc
    GetDeclaration	proc :ptr
    UpdateSkinnedMesh	proc :ptr, :ptr, :ptr, :ptr
    ConvertToBlendedMesh proc :ptr, :DWORD, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    ConvertToIndexedBlendedMesh proc :ptr, :DWORD, :DWORD, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr

    .ends


.comdef ID3DXPRTBuffer : public IUnknown

    GetNumSamples	proc
    GetNumCoeffs	proc
    GetNumChannels	proc
    IsTexture		proc
    GetWidth		proc
    GetHeight		proc
    Resize		proc :UINT
    LockBuffer		proc :UINT, :UINT, :ptr
    UnlockBuffer	proc
    ScaleBuffer		proc :FLOAT
    AddBuffer		proc :ptr
    AttachGH		proc :ptr
    ReleaseGH		proc
    EvalGH		proc
    ExtractTexture	proc :UINT, :UINT, :UINT, :ptr
    ExtractToMesh	proc :UINT, :D3DDECLUSAGE, :UINT, :ptr

    .ends


.comdef ID3DXPRTCompBuffer : public IUnknown

    GetNumSamples	proc
    GetNumCoeffs	proc
    GetNumChannels	proc
    IsTexture		proc
    GetWidth		proc
    GetHeight		proc
    GetNumClusters	proc
    GetNumPCA		proc
    NormalizeData	proc
    ExtractBasis	proc :UINT, :ptr
    ExtractClusterIDs	proc :ptr
    ExtractPCA		proc :UINT, :UINT, :ptr
    ExtractTexture	proc :UINT, :UINT, :ptr
    ExtractToMesh	proc :UINT, :D3DDECLUSAGE, :UINT, :ptr

    .ends


.comdef ID3DXTextureGutterHelper : public IUnknown

    GetWidth		proc
    GetHeight		proc
    ApplyGuttersFloat	proc :ptr, :UINT, :ptr, :UINT
    ApplyGuttersTex	proc :ptr
    ApplyGuttersPRT	proc :ptr
    ResampleTex		proc :ptr, :ptr, :D3DDECLUSAGE, :UINT, :ptr
    GetFaceMap		proc :ptr
    GetBaryMap		proc :ptr
    GetTexelMap		proc :ptr
    GetGutterMap	proc :ptr
    SetFaceMap		proc :ptr
    SetBaryMap		proc :ptr
    SetTexelMap		proc :ptr
    SetGutterMap	proc :ptr

    .ends


.comdef ID3DXPRTEngine : public IUnknown

    SetMeshMaterials	proc :ptr, :UINT, :UINT, :BOOL, :FLOAT
    SetPerVertexAlbedo	proc :ptr, :UINT, :UINT
    SetPerTexelAlbedo	proc :ptr, :UINT, :ptr
    GetVertexAlbedo	proc :ptr, :UINT
    SetPerTexelNormals	proc :ptr
    ExtractPerVertexAlbedo proc :ptr, :D3DDECLUSAGE, :UINT
    ResampleBuffer	proc :ptr, :ptr
    GetAdaptedMesh	proc :ptr, :ptr, :ptr, :ptr, :ptr
    GetNumVerts		proc
    GetNumFaces		proc
    SetMinMaxIntersection proc :FLOAT, :FLOAT
    RobustMeshRefine	proc :FLOAT, :UINT
    SetSamplingInfo	proc :UINT, :BOOL, :BOOL, :BOOL, :FLOAT
    ComputeDirectLightingSH proc :UINT, :ptr
    ComputeDirectLightingSHAdaptive proc :UINT, :float, :float, :UINT, :ptr
    ComputeDirectLightingSHGPU proc :ptr, :UINT, :UINT, :float, :float, :ptr
    ComputeSS		proc :ptr, :ptr, :ptr
    ComputeSSAdaptive	proc :ptr, :float, :float, :UINT, :ptr, :ptr
    ComputeBounce	proc :ptr, :ptr, :ptr
    ComputeBounceAdaptive proc :ptr, :float, :float, :UINT, :ptr, :ptr
    ComputeVolumeSamplesDirectSH proc :UINT, :UINT, :UINT, :ptr, :ptr
    ComputeVolumeSamples proc :ptr, :UINT, :UINT, :ptr, :ptr
    ComputeSurfSamplesDirectSH proc :UINT, :UINT, :ptr, :ptr, :ptr
    ComputeSurfSamplesBounce proc :ptr, :UINT, :ptr, :ptr, :ptr, :ptr
    FreeSSData		proc
    FreeBounceData	proc
    ComputeLDPRTCoeffs	proc :ptr, :UINT, :ptr, :ptr
    ScaleMeshChunk	proc :UINT, :float, :ptr
    MultiplyAlbedo	proc :ptr
    SetCallback		proc :LPD3DXSHPRTSIMCB, :float, :ptr
    ShadowRayIntersects proc :ptr, :ptr
    ClosestRayIntersects proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr

    .ends

;HRESULT
D3DXCreateMesh proto WINAPI \
	    face_count: DWORD,
	  vertex_count: DWORD,
		 flags: DWORD,
	   declaration: ptr D3DVERTEXELEMENT9,
		device: ptr IDirect3DDevice9,
		  mesh: ptr ID3DXMesh

;HRESULT
D3DXCreateMeshFVF proto WINAPI \
	    face_count: DWORD,
	  vertex_count: DWORD,
		 flags: DWORD,
		   fvf: DWORD,
		device: ptr IDirect3DDevice9,
		  mesh: ptr ID3DXMesh

;HRESULT
D3DXCreateBuffer proto WINAPI \
		  size: DWORD,
		buffer: ptr ID3DXBuffer

;HRESULT
D3DXCreateSPMesh proto WINAPI \
		  mesh: ptr ID3DXMesh,
	     adjacency: ptr DWORD,
     attribute_weights: ptr D3DXATTRIBUTEWEIGHTS,
	vertex_weights: ptr FLOAT,
		spmesh: ptr ID3DXSPMesh

;HRESULT
D3DXCreatePMeshFromStream proto WINAPI \
		stream: ptr IStream,
		 flags: DWORD,
		device: ptr IDirect3DDevice9,
	     materials: ptr ID3DXBuffer,
      effect_instances: ptr ID3DXBuffer,
	material_count: ptr DWORD,
		  mesh: ptr ID3DXBuffer

;HRESULT
D3DXCreateSkinInfo proto WINAPI \
	  vertex_count: DWORD,
	   declaration: ptr D3DVERTEXELEMENT9,
	    bone_count: DWORD,
	     skin_info: ptr ID3DXSkinInfo

;HRESULT
D3DXCreateSkinInfoFVF proto WINAPI \
	  vertex_count: DWORD,
		   fvf: DWORD,
	    bone_count: DWORD,
	     skin_info: ptr ID3DXSkinInfo

;HRESULT
D3DXCreateSkinInfoFromBlendedMesh proto WINAPI \
		  mesh: ptr ID3DXBaseMesh,
	    bone_count: DWORD,
bone_combination_table: ptr D3DXBONECOMBINATION,
	     skin_info: ptr ID3DXSkinInfo

;HRESULT
D3DXCreatePatchMesh proto WINAPI \
	    patch_info: ptr D3DXPATCHINFO,
	   patch_count: DWORD,
	  vertex_count: DWORD,
		 flags: DWORD,
	   declaration: ptr D3DVERTEXELEMENT9,
		device: ptr IDirect3DDevice9,
		  mesh: ptr ID3DXPatchMesh

;HRESULT
D3DXCreatePRTBuffer proto WINAPI \
	  sample_count: UINT,
	   coeff_count: UINT,
	 channel_count: UINT,
		buffer: ptr ID3DXPRTBuffer

;HRESULT
D3DXCreatePRTBufferTex proto WINAPI \
		 width: UINT,
		height: UINT,
	   coeff_count: UINT,
	 channel_count: UINT,
		buffer: ptr ID3DXPRTBuffer

;HRESULT
D3DXCreatePRTCompBuffer proto WINAPI \
	       quality: D3DXSHCOMPRESSQUALITYTYPE,
	 cluster_count: UINT,
	     pca_count: UINT,
		    cb: LPD3DXSHPRTSIMCB,
		   ctx: ptr void,
		 input: ptr ID3DXPRTBuffer,
		buffer: ptr ID3DXPRTCompBuffer

;HRESULT
D3DXCreateTextureGutterHelper proto WINAPI \
		 width: UINT,
		height: UINT,
		  mesh: ptr ID3DXMesh,
	   gutter_size: FLOAT,
		    gh: ptr ID3DXTextureGutterHelper

;HRESULT
D3DXCreatePRTEngine proto WINAPI \
		  mesh: ptr ID3DXMesh,
	     adjacency: ptr DWORD,
	    extract_uv: BOOL,
	  blocker_mesh: ptr ID3DXMesh,
		engine: ptr ID3DXPRTEngine

;HRESULT
D3DXLoadMeshFromXA proto WINAPI \
	      filename: LPSTR,
		 flags: DWORD,
		device: ptr IDirect3DDevice9,
	     adjacency: ptr ID3DXBuffer,
	     materials: ptr ID3DXBuffer,
      effect_instances: ptr ID3DXBuffer,
	material_count: ptr DWORD,
		  mesh: ptr ID3DXMesh

;HRESULT
D3DXLoadMeshFromXW proto WINAPI \
	      filename: LPWSTR,
		 flags: DWORD,
		device: ptr IDirect3DDevice9,
	     adjacency: ptr ID3DXBuffer,
	     materials: ptr ID3DXBuffer,
      effect_instances: ptr ID3DXBuffer,
	material_count: ptr DWORD,
		  mesh: ptr ID3DXMesh

D3DXLoadMeshFromX	equ __MINGW_NAME_AW(D3DXLoadMeshFromX)
;HRESULT
D3DXLoadMeshFromXInMemory proto WINAPI \
		 _data: PVOID,
	     data_size: DWORD,
		 flags: DWORD,
		device: ptr IDirect3DDevice9,
	     adjacency: ptr ID3DXBuffer,
	     materials: ptr ID3DXBuffer,
      effect_instances: ptr ID3DXBuffer,
	material_count: ptr DWORD,
		  mesh: ptr ID3DXMesh

;HRESULT
D3DXLoadMeshFromXResource proto WINAPI \
		module: HMODULE,
	      resource: LPSTR,
	 resource_type: LPSTR,
		 flags: DWORD,
		device: ptr IDirect3DDevice9,
	     adjacency: ptr ID3DXBuffer,
	     materials: ptr ID3DXBuffer,
      effect_instances: ptr ID3DXBuffer,
	material_count: ptr DWORD,
		  mesh: ptr ID3DXMesh

;HRESULT
D3DXLoadMeshFromXof proto WINAPI \
	     file_data: ptr ID3DXFileData,
		 flags: DWORD,
		device: ptr IDirect3DDevice9,
	     adjacency: ptr ID3DXBuffer,
	     materials: ptr ID3DXBuffer,
      effect_instances: ptr ID3DXBuffer,
	material_count: ptr DWORD,
		  mesh: ptr ID3DXMesh

;HRESULT
D3DXLoadPatchMeshFromXof proto WINAPI \
	     file_data: ptr ID3DXFileData,
		 flags: DWORD,
		device: ptr IDirect3DDevice9,
	     adjacency: ptr ID3DXBuffer,
	     materials: ptr ID3DXBuffer,
      effect_instances: ptr ID3DXBuffer,
	material_count: ptr DWORD,
		  mesh: ptr ID3DXPatchMesh

;HRESULT
D3DXLoadSkinMeshFromXof proto WINAPI \
	     file_data: ptr ID3DXFileData,
		 flags: DWORD,
		device: ptr IDirect3DDevice9,
	     adjacency: ptr ID3DXBuffer,
	     materials: ptr ID3DXBuffer,
      effect_instances: ptr ID3DXBuffer,
	material_count: ptr DWORD,
	     skin_info: ptr ID3DXSkinInfo,
		  mesh: ptr ID3DXMesh

;HRESULT
D3DXLoadPRTBufferFromFileA proto WINAPI \
	      filename: LPSTR,
		buffer: ptr ID3DXPRTBuffer

;HRESULT
D3DXLoadPRTBufferFromFileW proto WINAPI \
	      filename: ptr WCHAR,
		buffer: ptr ID3DXPRTBuffer

;HRESULT
D3DXLoadPRTCompBufferFromFileA proto WINAPI \
	      filename: LPSTR,
		buffer: ptr ID3DXPRTCompBuffer

;HRESULT
D3DXLoadPRTCompBufferFromFileW proto WINAPI \
	      filename: ptr WCHAR,
		buffer: ptr ID3DXPRTCompBuffer

D3DXLoadPRTCompBufferFromFile equ __MINGW_NAME_AW(D3DXLoadPRTCompBufferFromFile)
;HRESULT
D3DXSaveMeshToXA proto WINAPI \
	      filename: LPSTR,
		  mesh: ptr ID3DXMesh,
	     adjacency: ptr DWORD,
	     materials: ptr D3DXMATERIAL,
      effect_instances: ptr D3DXEFFECTINSTANCE,
	material_count: DWORD,
		format: DWORD

;HRESULT
D3DXSaveMeshToXW proto WINAPI \
	      filename: LPWSTR,
		  mesh: ptr ID3DXMesh,
	     adjacency: ptr DWORD,
	     materials: ptr D3DXMATERIAL,
      effect_instances: ptr D3DXEFFECTINSTANCE,
	material_count: DWORD,
		format: DWORD

;HRESULT
D3DXSavePRTBufferToFileA proto WINAPI \
	      filename: LPSTR,
		buffer: ptr ID3DXPRTBuffer

;HRESULT
D3DXSavePRTBufferToFileW proto WINAPI \
	      filename: LPWSTR,
		buffer: ptr ID3DXPRTBuffer

;HRESULT
D3DXSavePRTCompBufferToFileA proto WINAPI \
	      filename: LPSTR,
		buffer: ptr ID3DXPRTCompBuffer

;HRESULT
D3DXSavePRTCompBufferToFileW proto WINAPI \
	      filename: LPWSTR,
		buffer: ptr ID3DXPRTCompBuffer

;UINT
D3DXGetDeclLength proto WINAPI \
		  decl: ptr D3DVERTEXELEMENT9

;UINT
D3DXGetDeclVertexSize proto WINAPI \
		  decl: ptr D3DVERTEXELEMENT9,
	    stream_idx: DWORD

;UINT
D3DXGetFVFVertexSize proto WINAPI \
		      : DWORD

;BOOL
D3DXBoxBoundProbe proto WINAPI \
		  vmin: ptr D3DXVECTOR3,
		  vmax: ptr D3DXVECTOR3,
	       ray_pos: ptr D3DXVECTOR3,
	       ray_dir: ptr D3DXVECTOR3

;BOOL
D3DXSphereBoundProbe proto WINAPI \
		center: ptr D3DXVECTOR3,
		radius: FLOAT,
	       ray_pos: ptr D3DXVECTOR3,
	       ray_dir: ptr D3DXVECTOR3

;HRESULT
D3DXCleanMesh proto WINAPI \
	    clean_type: D3DXCLEANTYPE,
	       mesh_in: ptr ID3DXMesh,
	  adjacency_in: ptr DWORD,
	      mesh_out: ptr ID3DXMesh,
	 adjacency_out: ptr DWORD,
		errors: ptr ID3DXBuffer

;HRESULT
D3DXConcatenateMeshes proto WINAPI \
		meshes: ptr ID3DXMesh,
	    mesh_count: UINT,
		 flags: DWORD,
     geometry_matrices: ptr D3DXMATRIX,
      texture_matrices: ptr D3DXMATRIX,
	   declaration: ptr D3DVERTEXELEMENT9,
		device: ptr IDirect3DDevice9,
		  mesh: ptr ID3DXMesh

;HRESULT
D3DXComputeBoundingBox proto WINAPI \
	     first_pos: ptr D3DXVECTOR3,
	  num_vertices: DWORD,
		stride: DWORD,
		  vmin: ptr D3DXVECTOR3,
		  vmax: ptr D3DXVECTOR3

;HRESULT
D3DXComputeBoundingSphere proto WINAPI \
	     first_pos: ptr D3DXVECTOR3,
	  num_vertices: DWORD,
		stride: DWORD,
		center: ptr D3DXVECTOR3,
		radius: ptr FLOAT

;HRESULT
D3DXComputeIMTFromPerTexelSignal proto WINAPI \
		  mesh: ptr ID3DXMesh,
	   texture_idx: DWORD,
	  texel_signal: ptr float,
		 width: UINT,
		height: UINT,
      signal_dimension: UINT,
       component_count: UINT,
		 flags: DWORD,
		    cb: LPD3DXUVATLASCB,
		   ctx: ptr void,
		buffer: ptr ID3DXBuffer

;HRESULT
D3DXComputeIMTFromPerVertexSignal proto WINAPI \
		  mesh: ptr ID3DXMesh,
	 vertex_signal: ptr FLOAT,
      signal_dimension: UINT,
	 signal_stride: UINT,
		 flags: DWORD,
		    cb: LPD3DXUVATLASCB,
		   ctx: ptr void,
		buffer: ptr ID3DXBuffer

;HRESULT
D3DXComputeIMTFromSignal proto WINAPI \
		  mesh: ptr ID3DXMesh,
	   texture_idx: DWORD,
      signal_dimension: UINT,
       max_uv_distance: float,
		 flags: DWORD,
	     signal_cb: LPD3DXIMTSIGNALCALLBACK,
	    signal_ctx: ptr void,
	     status_cb: LPD3DXUVATLASCB,
	    status_ctx: ptr void,
		buffer: ptr ID3DXBuffer

;HRESULT
D3DXComputeIMTFromTexture proto WINAPI \
		  mesh: ptr ID3DXMesh,
	       texture: ptr IDirect3DTexture9,
	   texture_idx: DWORD,
	       options: DWORD,
		    cb: LPD3DXUVATLASCB,
		   ctx: PVOID,
		  _out: ptr ID3DXBuffer

;HRESULT
D3DXComputeNormals proto WINAPI \
		  mesh: ptr ID3DXBaseMesh,
	     adjacency: ptr DWORD

;HRESULT
D3DXComputeTangentFrameEx proto WINAPI \
	       mesh_in: ptr ID3DXMesh,
   texture_in_semantic: DWORD,
	texture_in_idx: DWORD,
u_partial_out_semantic: DWORD,
     u_partial_out_idx: DWORD,
v_partial_out_semantic: DWORD,
     v_partial_out_idx: DWORD,
   normal_out_semantic: DWORD,
	normal_out_idx: DWORD,
		 flags: DWORD,
	     adjacency: ptr DWORD,
partial_edge_threshold: float,
singular_point_threshold: float,
 normal_edge_threshold: float,
	      mesh_out: ptr ID3DXMesh,
		buffer: ptr ID3DXBuffer

;HRESULT
D3DXComputeTangent proto WINAPI \
		  mesh: ptr ID3DXMesh,
		 stage: DWORD,
	   tangent_idx: DWORD,
	    binorm_idx: DWORD,
		  wrap: DWORD,
	     adjacency: ptr DWORD

;HRESULT
D3DXConvertMeshSubsetToSingleStrip proto WINAPI \
	       mesh_in: ptr ID3DXBaseMesh,
	  attribute_id: DWORD,
	      ib_flags: DWORD,
	  index_buffer: ptr IDirect3DIndexBuffer9,
	   index_count: ptr DWORD

;HRESULT
D3DXConvertMeshSubsetToStrips proto WINAPI \
	       mesh_in: ptr ID3DXBaseMesh,
	  attribute_id: DWORD,
	      ib_flags: DWORD,
	  index_buffer: ptr IDirect3DIndexBuffer9,
	   index_count: ptr DWORD,
	 strip_lengths: ptr ID3DXBuffer,
	   strip_count: ptr DWORD

;HRESULT
D3DXDeclaratorFromFVF proto WINAPI \
		      : DWORD,
		      : ptr D3DVERTEXELEMENT9;[MAX_FVF_DECL_SIZE]

;HRESULT
D3DXFVFFromDeclarator proto WINAPI \
		  decl: ptr D3DVERTEXELEMENT9,
		   fvf: ptr DWORD

;HRESULT
D3DXGenerateOutputDecl proto WINAPI \
	      decl_out: ptr D3DVERTEXELEMENT9,
	       decl_in: ptr D3DVERTEXELEMENT9

;HRESULT
D3DXGeneratePMesh proto WINAPI \
		  mesh: ptr ID3DXMesh,
	     adjacency: ptr DWORD,
     attribute_weights: ptr D3DXATTRIBUTEWEIGHTS,
	vertex_weights: ptr FLOAT,
	     min_value: DWORD,
		 flags: DWORD,
		 pmesh: ptr ID3DXPMesh

;HRESULT
D3DXIntersect proto WINAPI \
		  mesh: ptr ID3DXBaseMesh,
	  ray_position: ptr D3DXVECTOR3,
	 ray_direction: ptr D3DXVECTOR3,
		   hit: ptr BOOL,
	      face_idx: ptr DWORD,
		     u: ptr float,
		     v: ptr float,
	      distance: ptr float,
		  hits: ptr ID3DXBuffer,
	     hit_count: ptr DWORD

;HRESULT
D3DXIntersectSubset proto WINAPI \
		  mesh: ptr ID3DXBaseMesh,
	  attribute_id: DWORD,
	  ray_position: ptr D3DXVECTOR3,
	 ray_direction: ptr D3DXVECTOR3,
		   hit: ptr BOOL,
	      face_idx: ptr DWORD,
		     u: ptr float,
		     v: ptr float,
	      distance: ptr float,
		  hits: ptr ID3DXBuffer,
	     hit_count: ptr DWORD

;BOOL
D3DXIntersectTri proto WINAPI \
		  vtx0: ptr D3DXVECTOR3,
		  vtx1: ptr D3DXVECTOR3,
		  vtx2: ptr D3DXVECTOR3,
	       ray_pos: ptr D3DXVECTOR3,
	       ray_dir: ptr D3DXVECTOR3,
		     u: ptr FLOAT,
		     v: ptr FLOAT,
		  dist: ptr FLOAT

;HRESULT
D3DXOptimizeFaces proto WINAPI \
	       indices: PVOID,
	    face_count: UINT,
	  vertex_count: UINT,
	     idx_32bit: BOOL,
	    face_remap: ptr DWORD

;HRESULT
D3DXOptimizeVertices proto WINAPI \
	       indices: PVOID,
	    face_count: UINT,
	  vertex_count: UINT,
	     idx_32bit: BOOL,
	  vertex_remap: ptr DWORD

;HRESULT
D3DXRectPatchSize proto WINAPI \
	 segment_count: ptr FLOAT,
	 num_triangles: ptr DWORD,
	  num_vertices: ptr DWORD

;HRESULT
D3DXSHPRTCompSuperCluster proto WINAPI \
	   cluster_ids: ptr UINT,
		 scene: ptr ID3DXMesh,
     max_cluster_count: UINT,
	 cluster_count: UINT,
	  scluster_ids: ptr UINT,
	scluster_count: ptr UINT

;HRESULT
D3DXSHPRTCompSplitMeshSC proto WINAPI \
	   cluster_idx: ptr UINT,
	  vertex_count: UINT,
	 cluster_count: UINT,
	  scluster_ids: ptr UINT,
	scluster_count: UINT,
       index_buffer_in: ptr void,
	   ib_in_32bit: BOOL,
	    face_count: UINT,
      index_buffer_out: ptr ID3DXBuffer,
     index_buffer_size: ptr UINT,
	  ib_out_32bit: BOOL,
	    face_remap: ptr ID3DXBuffer,
	   vertex_data: ptr ID3DXBuffer,
    vertex_data_length: ptr UINT,
       sc_cluster_list: ptr UINT,
	       sc_data: ptr D3DXSHPRTSPLITMESHCLUSTERDATA

;HRESULT
D3DXSimplifyMesh proto WINAPI \
	       mesh_in: ptr ID3DXMesh,
	     adjacency: ptr DWORD,
     attribute_weights: ptr D3DXATTRIBUTEWEIGHTS,
	vertex_weights: ptr FLOAT,
	     min_value: DWORD,
		 flags: DWORD,
	      mesh_out: ptr ID3DXMesh

;HRESULT
D3DXSplitMesh proto WINAPI \
	       mesh_in: ptr ID3DXMesh,
	  adjacency_in: ptr DWORD,
	      max_size: DWORD,
		 flags: DWORD,
	mesh_out_count: ptr DWORD,
	      mesh_out: ptr ID3DXBuffer,
	 adjacency_out: ptr ID3DXBuffer,
	face_remap_out: ptr ID3DXBuffer,
      vertex_remap_out: ptr ID3DXBuffer

;HRESULT
D3DXTessellateNPatches proto WINAPI \
	       mesh_in: ptr ID3DXMesh,
	  adjacency_in: ptr DWORD,
	 segment_count: float,
	   quad_interp: BOOL,
	      mesh_out: ptr ID3DXMesh,
	 adjacency_out: ptr ID3DXBuffer

;HRESULT
D3DXTessellateRectPatch proto WINAPI \
		buffer: ptr IDirect3DVertexBuffer9,
	 segment_count: ptr FLOAT,
	   declaration: ptr D3DVERTEXELEMENT9,
	    patch_info: ptr D3DVERTEXELEMENT9,
		  mesh: ptr D3DVERTEXELEMENT9

;HRESULT
D3DXTessellateTriPatch proto WINAPI \
		buffer: ptr IDirect3DVertexBuffer9,
	 segment_count: ptr FLOAT,
	   declaration: ptr D3DVERTEXELEMENT9,
	    patch_info: ptr D3DTRIPATCH_INFO,
		  mesh: ptr ID3DXMesh

;HRESULT
D3DXTriPatchSize proto WINAPI \
	 segment_count: ptr FLOAT,
	 num_triangles: ptr DWORD,
	  num_vertices: ptr DWORD

;HRESULT
D3DXUVAtlasCreate proto WINAPI \
	       mesh_in: ptr ID3DXMesh,
       max_chart_count: UINT,
	max_stretch_in: float,
		 width: UINT,
		height: UINT,
		gutter: float,
	   texture_idx: DWORD,
	     adjacency: ptr DWORD,
	   false_edges: ptr DWORD,
	     imt_array: ptr FLOAT,
		    cb: LPD3DXUVATLASCB,
	       cb_freq: float,
		   ctx: ptr void,
		 flags: DWORD,
	      mesh_out: ptr ID3DXMesh,
 face_partitioning_out: ptr ID3DXBuffer,
      vertex_remap_out: ptr ID3DXBuffer,
       max_stretch_out: ptr float,
	   chart_count: ptr UINT

;HRESULT
D3DXUVAtlasPack proto WINAPI \
		  mesh: ptr ID3DXMesh,
		 width: UINT,
		height: UINT,
		gutter: float,
	   texture_idx: DWORD,
partition_result_adjacency: ptr DWORD,
		    cb: LPD3DXUVATLASCB,
	       cb_freq: float,
		   ctx: PVOID,
		 flags: DWORD,
     face_partitioning: ptr ID3DXBuffer

;HRESULT
D3DXUVAtlasPartition proto WINAPI \
	       mesh_in: ptr ID3DXMesh,
       max_chart_count: UINT,
	max_stretch_in: float,
	   texture_idx: DWORD,
	     adjacency: ptr DWORD,
	   false_edges: ptr DWORD,
	     imt_array: ptr FLOAT,
		    cb: LPD3DXUVATLASCB,
	       cb_freq: float,
		   ctx: PVOID,
		 flags: DWORD,
	      mesh_out: ptr ID3DXMesh,
 face_partitioning_out: ptr ID3DXBuffer,
      vertex_remap_out: ptr ID3DXBuffer,
	 adjacency_out: ptr ID3DXBuffer,
       max_stretch_out: ptr float,
	   chart_count: ptr UINT

;HRESULT
D3DXValidMesh proto WINAPI \
		  mesh: ptr ID3DXMesh,
	     adjacency: ptr DWORD,
		errors: ptr ID3DXBuffer

;HRESULT
D3DXValidPatchMesh proto WINAPI \
		  mesh: ptr ID3DXPatchMesh,
degenerate_vertex_count: ptr DWORD,
degenerate_patch_count: ptr DWORD,
		errors: ptr ID3DXBuffer

;HRESULT
D3DXWeldVertices proto WINAPI \
		  mesh: ptr ID3DXMesh,
		 flags: DWORD,
	      epsilons: ptr D3DXWELDEPSILONS,
	  adjacency_in: ptr DWORD,
	 adjacency_out: ptr DWORD,
	face_remap_out: ptr DWORD,
      vertex_remap_out: ptr ID3DXBuffer


DEFINE_GUID(DXFILEOBJ_XSkinMeshHeader,		0x3cf169ce, 0xff7c, 0x44ab, 0x93, 0xc0, 0xf7, 0x8f, 0x62, 0xd1, 0x72, 0xe2);
DEFINE_GUID(DXFILEOBJ_VertexDuplicationIndices, 0xb8d65549, 0xd7c9, 0x4995, 0x89, 0xcf, 0x53, 0xa9, 0xa8, 0xb0, 0x31, 0xe3);
DEFINE_GUID(DXFILEOBJ_FaceAdjacency,		0xa64c844a, 0xe282, 0x4756, 0x8b, 0x80, 0x25, 0x0c, 0xde, 0x04, 0x39, 0x8c);
DEFINE_GUID(DXFILEOBJ_SkinWeights,		0x6f0d123b, 0xbad2, 0x4167, 0xa0, 0xd0, 0x80, 0x22, 0x4f, 0x25, 0xfa, 0xbb);
DEFINE_GUID(DXFILEOBJ_Patch,			0xa3eb5d44, 0xfc22, 0x429d, 0x9a, 0xfb, 0x32, 0x21, 0xcb, 0x97, 0x19, 0xa6);
DEFINE_GUID(DXFILEOBJ_PatchMesh,		0xd02c95cc, 0xedba, 0x4305, 0x9b, 0x5d, 0x18, 0x20, 0xd7, 0x70, 0x4d, 0xbf);
DEFINE_GUID(DXFILEOBJ_PatchMesh9,		0xb9ec94e1, 0xb9a6, 0x4251, 0xba, 0x18, 0x94, 0x89, 0x3f, 0x02, 0xc0, 0xea);
DEFINE_GUID(DXFILEOBJ_PMInfo,			0xb6c3e656, 0xec8b, 0x4b92, 0x9b, 0x62, 0x68, 0x16, 0x59, 0x52, 0x29, 0x47);
DEFINE_GUID(DXFILEOBJ_PMAttributeRange,		0x917e0427, 0xc61e, 0x4a14, 0x9c, 0x64, 0xaf, 0xe6, 0x5f, 0x9e, 0x98, 0x44);
DEFINE_GUID(DXFILEOBJ_PMVSplitRecord,		0x574ccc14, 0xf0b3, 0x4333, 0x82, 0x2d, 0x93, 0xe8, 0xa8, 0xa0, 0x8e, 0x4c);
DEFINE_GUID(DXFILEOBJ_FVFData,			0xb6e70a0e, 0x8ef9, 0x4e83, 0x94, 0xad, 0xec, 0xc8, 0xb0, 0xc0, 0x48, 0x97);
DEFINE_GUID(DXFILEOBJ_VertexElement,		0xf752461c, 0x1e23, 0x48f6, 0xb9, 0xf8, 0x83, 0x50, 0x85, 0x0f, 0x33, 0x6f);
DEFINE_GUID(DXFILEOBJ_DeclData,			0xbf22e553, 0x292c, 0x4781, 0x9f, 0xea, 0x62, 0xbd, 0x55, 0x4b, 0xdd, 0x93);
DEFINE_GUID(DXFILEOBJ_EffectFloats,		0xf1cfe2b3, 0x0de3, 0x4e28, 0xaf, 0xa1, 0x15, 0x5a, 0x75, 0x0a, 0x28, 0x2d);
DEFINE_GUID(DXFILEOBJ_EffectString,		0xd55b097e, 0xbdb6, 0x4c52, 0xb0, 0x3d, 0x60, 0x51, 0xc8, 0x9d, 0x0e, 0x42);
DEFINE_GUID(DXFILEOBJ_EffectDWord,		0x622c0ed0, 0x956e, 0x4da9, 0x90, 0x8a, 0x2a, 0xf9, 0x4f, 0x3c, 0xe7, 0x16);
DEFINE_GUID(DXFILEOBJ_EffectParamFloats,	0x3014b9a0, 0x62f5, 0x478c, 0x9b, 0x86, 0xe4, 0xac, 0x9f, 0x4e, 0x41, 0x8b);
DEFINE_GUID(DXFILEOBJ_EffectParamString,	0x1dbc4c88, 0x94c1, 0x46ee, 0x90, 0x76, 0x2c, 0x28, 0x81, 0x8c, 0x94, 0x81);
DEFINE_GUID(DXFILEOBJ_EffectParamDWord,		0xe13963bc, 0xae51, 0x4c5d, 0xb0, 0x0f, 0xcf, 0xa3, 0xa9, 0xd9, 0x7c, 0xe5);
DEFINE_GUID(DXFILEOBJ_EffectInstance,		0xe331f7e4, 0x0559, 0x4cc2, 0x8e, 0x99, 0x1c, 0xec, 0x16, 0x57, 0x92, 0x8f);
DEFINE_GUID(DXFILEOBJ_AnimTicksPerSecond,	0x9e415a43, 0x7ba6, 0x4a73, 0x87, 0x43, 0xb7, 0x3d, 0x47, 0xe8, 0x84, 0x76);
DEFINE_GUID(DXFILEOBJ_CompressedAnimationSet,	0x7f9b00b3, 0xf125, 0x4890, 0x87, 0x6e, 0x1c, 0x42, 0xbf, 0x69, 0x7c, 0x4d);

endif
