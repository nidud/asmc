include d3dx10.inc

ifndef __D3DX10MESH_H__
define __D3DX10MESH_H__

DEFINE_GUID(IID_ID3DX10BaseMesh, 0x7ed943dd, 0x52e8, 0x40b5, 0xa8, 0xd8, 0x76, 0x68, 0x5c, 0x40, 0x63, 0x30)
DEFINE_GUID(IID_ID3DX10MeshBuffer, 0x4b0d117, 0x1041, 0x46b1, 0xaa, 0x8a, 0x39, 0x52, 0x84, 0x8b, 0xa2, 0x2e);
DEFINE_GUID(IID_ID3DX10Mesh, 0x4020e5c2, 0x1403, 0x4929, 0x88, 0x3f, 0xe2, 0xe8, 0x49, 0xfa, 0xc1, 0x95);
DEFINE_GUID(IID_ID3DX10PMesh, 0x8875769a, 0xd579, 0x4088, 0xaa, 0xeb, 0x53, 0x4d, 0x1a, 0xd8, 0x4e, 0x96);
DEFINE_GUID(IID_ID3DX10SPMesh, 0x667ea4c7, 0xf1cd, 0x4386, 0xb5, 0x23, 0x7c, 0x2, 0x90, 0xb8, 0x3c, 0xc5);
DEFINE_GUID(IID_ID3DX10PatchMesh, 0x3ce6cc22, 0xdbf2, 0x44f4, 0x89, 0x4d, 0xf9, 0xc3, 0x4a, 0x33, 0x71, 0x39);

.enum D3DX10_MESH {
    D3DX10_MESH_32_BIT = 0x001,
    D3DX10_MESH_GS_ADJACENCY = 0x004,
    }

D3DX10_ATTRIBUTE_RANGE	STRUC
AttribId		UINT ?
FaceStart		UINT ?
FaceCount		UINT ?
VertexStart		UINT ?
VertexCount		UINT ?
D3DX10_ATTRIBUTE_RANGE	ENDS
LPD3DX10_ATTRIBUTE_RANGE typedef ptr D3DX10_ATTRIBUTE_RANGE

.enum D3DX10_MESH_DISCARD_FLAGS {
    D3DX10_MESH_DISCARD_ATTRIBUTE_BUFFER = 0x01,
    D3DX10_MESH_DISCARD_ATTRIBUTE_TABLE = 0x02,
    D3DX10_MESH_DISCARD_POINTREPS = 0x04,
    D3DX10_MESH_DISCARD_ADJACENCY = 0x08,
    D3DX10_MESH_DISCARD_DEVICE_BUFFERS = 0x10,
    }

D3DX10_WELD_EPSILONS	STRUC
Position		FLOAT ?
BlendWeights		FLOAT ?
Normal			FLOAT ?
PSize			FLOAT ?
Specular		FLOAT ?
Diffuse			FLOAT ?
Texcoord		FLOAT 8 dup(?)
Tangent			FLOAT ?
Binormal		FLOAT ?
TessFactor		FLOAT ?
D3DX10_WELD_EPSILONS	ENDS
LPD3DX10_WELD_EPSILONS	typedef ptr D3DX10_WELD_EPSILONS

D3DX10_INTERSECT_INFO	STRUC
FaceIndex		UINT ?
U			FLOAT ?
V			FLOAT ?
Dist			FLOAT ?
D3DX10_INTERSECT_INFO	ENDS
LPD3DX10_INTERSECT_INFO typedef ptr D3DX10_INTERSECT_INFO


.comdef ID3DX10MeshBuffer : public IUnknown

    Map			proc :ptr ptr, :ptr SIZE_T
    Unmap		proc
    GetSize		proc
    .ENDS


.comdef ID3DX10Mesh : public IUnknown

    GetFaceCount	proc
    GetVertexCount	proc
    GetVertexBufferCount proc
    GetFlags		proc
    GetVertexDescription proc :ptr ptr D3D10_INPUT_ELEMENT_DESC, :ptr UINT
    SetVertexData	proc :UINT, :ptr
    GetVertexBuffer	proc :UINT, :ptr ptr ID3DX10MeshBuffer
    SetIndexData	proc :ptr , :UINT
    GetIndexBuffer	proc :ptr ptr ID3DX10MeshBuffer
    SetAttributeData	proc :ptr UINT
    GetAttributeBuffer	proc :ptr ptr ID3DX10MeshBuffer
    SetAttributeTable	proc :ptr D3DX10_ATTRIBUTE_RANGE, :UINT
    GetAttributeTable	proc :ptr D3DX10_ATTRIBUTE_RANGE, :ptr UINT
    GenerateAdjacencyAndPointReps proc :FLOAT
    GenerateGSAdjacency proc
    SetAdjacencyData	proc :ptr UINT
    GetAdjacencyBuffer	proc :ptr ptr ID3DX10MeshBuffer
    SetPointRepData	proc :ptr UINT
    GetPointRepBuffer	proc :ptr ptr ID3DX10MeshBuffer
    Discard		proc :D3DX10_MESH_DISCARD_FLAGS
    CloneMesh		proc :UINT, :LPCSTR, :ptr D3D10_INPUT_ELEMENT_DESC, :UINT, :ptr ptr ID3DX10Mesh
    Optimize		proc :UINT, :ptr UINT, :ptr LPD3D10BLOB
    GenerateAttributeBufferFromTable proc
    Intersect		proc :ptr D3DXVECTOR3, :ptr D3DXVECTOR3, :ptr UINT, :ptr UINT, :ptr float, :ptr float, :ptr float, :ptr ptr ID3D10Blob
    IntersectSubset	proc :UINT, :ptr D3DXVECTOR3, :ptr D3DXVECTOR3, :ptr UINT, :ptr UINT, :ptr float, :ptr float, :ptr float, :ptr ptr ID3D10Blob
    CommitToDevice	proc
    DrawSubset		proc :UINT
    DrawSubsetInstanced proc :UINT, :UINT, :UINT
    GetDeviceVertexBuffer proc :UINT, :ptr ptr ID3D10Buffer
    GetDeviceIndexBuffer proc :ptr ptr ID3D10Buffer
    .ENDS

D3DX10CreateMesh proto WINAPI \
	       pDevice: ptr ID3D10Device,
	  pDeclaration: ptr D3D10_INPUT_ELEMENT_DESC,
	     DeclCount: UINT,
     pPositionSemantic: LPCSTR,
	   VertexCount: UINT,
	     FaceCount: UINT,
	       Options: UINT,
		ppMesh: ptr ID3DX10Mesh


.enum D3DX10_MESHOPT {
    D3DX10_MESHOPT_COMPACT	 = 0x01000000,
    D3DX10_MESHOPT_ATTR_SORT	 = 0x02000000,
    D3DX10_MESHOPT_VERTEX_CACHE	  = 0x04000000,
    D3DX10_MESHOPT_STRIP_REORDER  = 0x08000000,
    D3DX10_MESHOPT_IGNORE_VERTS	  = 0x10000000,
    D3DX10_MESHOPT_DO_NOT_SPLIT	   = 0x20000000,
    D3DX10_MESHOPT_DEVICE_INDEPENDENT = 0x00400000,
    }

DEFINE_GUID(IID_ID3DX10SkinInfo, 0x420bd604, 0x1c76, 0x4a34, 0xa4, 0x66, 0xe4, 0x5d, 0x6, 0x58, 0xa3, 0x2c);

D3DX10_SKININFO_NO_SCALING equ 0
D3DX10_SKININFO_SCALE_TO_1 equ 1
D3DX10_SKININFO_SCALE_TO_TOTAL equ 2

D3DX10_SKINNING_CHANNEL STRUC
SrcOffset		UINT ?
DestOffset		UINT ?
IsNormal		BOOL ?
D3DX10_SKINNING_CHANNEL ENDS
LPD3DX10SKININFO	typedef ptr ID3DX10SkinInfo

.comdef ID3DX10SkinInfo : public IUnknown

    GetNumVertices	proc
    GetNumBones		proc
    GetMaxBoneInfluences proc
    AddVertices		proc :UINT
    RemapVertices	proc :UINT, :ptr UINT
    AddBones		proc :UINT
    RemoveBone		proc :UINT
    RemapBones		proc :UINT, :ptr UINT
    AddBoneInfluences	proc :UINT, :UINT, :ptr UINT, :ptr float
    ClearBoneInfluences proc :UINT
    GetBoneInfluenceCount proc :UINT
    GetBoneInfluences	proc :UINT, :UINT, :UINT, :ptr UINT, :ptr float
    FindBoneInfluenceIndex proc :UINT, :UINT, :ptr UINT
    SetBoneInfluence	proc :UINT, :UINT, :float
    GetBoneInfluence	proc :UINT, :UINT, :ptr float
    Compact		proc :UINT, :UINT, :float
    DoSoftwareSkinning	proc :UINT, :UINT, :ptr, :UINT, :ptr, :UINT, :ptr D3DXMATRIX, :ptr D3DXMATRIX, :ptr D3DX10_SKINNING_CHANNEL, :UINT
    .ENDS

D3DX10CreateSkinInfo proto WINAPI \
	    ppSkinInfo: ptr LPD3DX10SKININFO


D3DX10_ATTRIBUTE_WEIGHTS STRUC
Position		FLOAT ?
Boundary		FLOAT ?
Normal			FLOAT ?
Diffuse			FLOAT ?
Specular		FLOAT ?
Texcoord		FLOAT 8 dup(?)
Tangent			FLOAT ?
Binormal		FLOAT ?
D3DX10_ATTRIBUTE_WEIGHTS ENDS
LPD3DX10_ATTRIBUTE_WEIGHTS typedef ptr D3DX10_ATTRIBUTE_WEIGHTS

endif
