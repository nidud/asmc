ifndef _D2D1_EFFECT_AUTHOR_H_
define _D2D1_EFFECT_AUTHOR_H_

ifndef _D2D1_1_H_
include d2d1_1.inc
endif


CALLBACK(PD2D1_PROPERTY_SET_FUNCTION, :ptr IUnknown, :LPBYTE, :UINT32)
CALLBACK(PD2D1_PROPERTY_GET_FUNCTION, :ptr IUnknown, :LPBYTE, :UINT32, :ptr UINT32)

ifndef D2D_USE_C_DEFINITIONS
else
endif


.enum D2D1_CHANGE_TYPE {
    D2D1_CHANGE_TYPE_NONE = 0,
    D2D1_CHANGE_TYPE_PROPERTIES = 1,
    D2D1_CHANGE_TYPE_CONTEXT = 2,
    D2D1_CHANGE_TYPE_GRAPH = 3,
    D2D1_CHANGE_TYPE_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_PIXEL_OPTIONS {
    D2D1_PIXEL_OPTIONS_NONE = 0,
    D2D1_PIXEL_OPTIONS_TRIVIAL_SAMPLING = 1,
    D2D1_PIXEL_OPTIONS_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_VERTEX_OPTIONS {
    D2D1_VERTEX_OPTIONS_NONE = 0,
    D2D1_VERTEX_OPTIONS_DO_NOT_CLEAR = 1,
    D2D1_VERTEX_OPTIONS_USE_DEPTH_BUFFER = 2,
    D2D1_VERTEX_OPTIONS_ASSUME_NO_OVERLAP = 4,
    D2D1_VERTEX_OPTIONS_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_VERTEX_USAGE {
    D2D1_VERTEX_USAGE_STATIC = 0,
    D2D1_VERTEX_USAGE_DYNAMIC = 1,
    D2D1_VERTEX_USAGE_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_BLEND_OPERATION {
    D2D1_BLEND_OPERATION_ADD = 1,
    D2D1_BLEND_OPERATION_SUBTRACT = 2,
    D2D1_BLEND_OPERATION_REV_SUBTRACT = 3,
    D2D1_BLEND_OPERATION_MIN = 4,
    D2D1_BLEND_OPERATION_MAX = 5,
    D2D1_BLEND_OPERATION_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_BLEND {
    D2D1_BLEND_ZERO = 1,
    D2D1_BLEND_ONE = 2,
    D2D1_BLEND_SRC_COLOR = 3,
    D2D1_BLEND_INV_SRC_COLOR = 4,
    D2D1_BLEND_SRC_ALPHA = 5,
    D2D1_BLEND_INV_SRC_ALPHA = 6,
    D2D1_BLEND_DEST_ALPHA = 7,
    D2D1_BLEND_INV_DEST_ALPHA = 8,
    D2D1_BLEND_DEST_COLOR = 9,
    D2D1_BLEND_INV_DEST_COLOR = 10,
    D2D1_BLEND_SRC_ALPHA_SAT = 11,
    D2D1_BLEND_BLEND_FACTOR = 14,
    D2D1_BLEND_INV_BLEND_FACTOR = 15,
    D2D1_BLEND_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_CHANNEL_DEPTH {
    D2D1_CHANNEL_DEPTH_DEFAULT = 0,
    D2D1_CHANNEL_DEPTH_1 = 1,
    D2D1_CHANNEL_DEPTH_4 = 4,
    D2D1_CHANNEL_DEPTH_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_FILTER {
    D2D1_FILTER_MIN_MAG_MIP_POINT = 0x00,
    D2D1_FILTER_MIN_MAG_POINT_MIP_LINEAR = 0x01,
    D2D1_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x04,
    D2D1_FILTER_MIN_POINT_MAG_MIP_LINEAR = 0x05,
    D2D1_FILTER_MIN_LINEAR_MAG_MIP_POINT = 0x10,
    D2D1_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x11,
    D2D1_FILTER_MIN_MAG_LINEAR_MIP_POINT = 0x14,
    D2D1_FILTER_MIN_MAG_MIP_LINEAR = 0x15,
    D2D1_FILTER_ANISOTROPIC = 0x55,
    D2D1_FILTER_FORCE_DWORD = 0xffffffff
    }


.enum D2D1_FEATURE {
    D2D1_FEATURE_DOUBLES = 0,
    D2D1_FEATURE_D3D10_X_HARDWARE_OPTIONS = 1,
    D2D1_FEATURE_FORCE_DWORD = 0xffffffff
    }


D2D1_PROPERTY_BINDING	STRUC
propertyName		PCWSTR ?
setFunction		PD2D1_PROPERTY_SET_FUNCTION ?
getFunction		PD2D1_PROPERTY_GET_FUNCTION ?
D2D1_PROPERTY_BINDING	ENDS

PD2D1_EXTEND_MODE	typedef ptr D2D1_EXTEND_MODE
D2D1_RESOURCE_TEXTURE_PROPERTIES STRUC
extents			LPUINT ?
dimensions		UINT32 ?
bufferPrecision		D2D1_BUFFER_PRECISION ?
channelDepth		D2D1_CHANNEL_DEPTH ?
filter			D2D1_FILTER ?
extendModes		PD2D1_EXTEND_MODE ?
D2D1_RESOURCE_TEXTURE_PROPERTIES ENDS


D2D1_INPUT_ELEMENT_DESC STRUC
semanticName		PCSTR ?
semanticIndex		UINT32 ?
format			DXGI_FORMAT ?
inputSlot		UINT32 ?
alignedByteOffset	UINT32 ?
D2D1_INPUT_ELEMENT_DESC ENDS


D2D1_APPEND_ALIGNED_ELEMENT equ ( 0xffffffff )


D2D1_VERTEX_BUFFER_PROPERTIES STRUC
inputCount		UINT32 ?
usage			D2D1_VERTEX_USAGE ?
data			LPBYTE ?
byteWidth		UINT32 ?
D2D1_VERTEX_BUFFER_PROPERTIES ENDS


PD2D1_INPUT_ELEMENT_DESC typedef ptr D2D1_INPUT_ELEMENT_DESC
D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES STRUC
shaderBufferWithInputSignature LPBYTE ?
shaderBufferSize	UINT32 ?
inputElements		PD2D1_INPUT_ELEMENT_DESC ?
elementCount		UINT32 ?
stride			UINT32 ?
D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES ENDS


D2D1_VERTEX_RANGE	STRUC
startVertex		UINT32 ?
vertexCount		UINT32 ?
D2D1_VERTEX_RANGE	ENDS


D2D1_BLEND_DESCRIPTION	STRUC
sourceBlend		D2D1_BLEND ?
destinationBlend	D2D1_BLEND ?
blendOperation		D2D1_BLEND_OPERATION ?
sourceBlendAlpha	D2D1_BLEND ?
destinationBlendAlpha	D2D1_BLEND ?
blendOperationAlpha	D2D1_BLEND_OPERATION ?
blendFactor		FLOAT 4 dup(?)
D2D1_BLEND_DESCRIPTION	ENDS


D2D1_INPUT_DESCRIPTION	STRUC
filter			D2D1_FILTER ?
levelOfDetailCount	UINT32 ?
D2D1_INPUT_DESCRIPTION	ENDS


D2D1_FEATURE_DATA_DOUBLES STRUC
doublePrecisionFloatShaderOps BOOL ?
D2D1_FEATURE_DATA_DOUBLES ENDS

D2D1_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS STRUC
computeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x BOOL ?
D2D1_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS ENDS

ifndef D2D_USE_C_DEFINITIONS

DEFINE_IIDX(ID2D1VertexBuffer, "9b8b1336-00a5-4668-92b7-ced5d8bf9b7b")

.comdef ID2D1VertexBuffer : public IUnknown

    Map			proc :ptr LPBYTE, :UINT32
    Unmap		proc

    .ends


DEFINE_IIDX(ID2D1ResourceTexture, "688d15c3-02b0-438d-b13a-d1b44c32c39a")

.comdef ID2D1ResourceTexture : public IUnknown

    Update		proc :ptr UINT32, :ptr UINT32, :ptr UINT32, :UINT32, :LPBYTE, :UINT32
    .ends


DEFINE_IIDX(ID2D1RenderInfo, "519ae1bd-d19a-420d-b849-364f594776b7")

.comdef ID2D1RenderInfo : public IUnknown

    SetInputDescription proc :UINT32, :D2D1_INPUT_DESCRIPTION
    SetOutputBuffer	proc :D2D1_BUFFER_PRECISION, :D2D1_CHANNEL_DEPTH
    SetCached		proc :BOOL
    SetInstructionCountHint proc :UINT32

    .ends


DEFINE_IIDX(ID2D1DrawInfo, "693ce632-7f2f-45de-93fe-18d88b37aa21")

.comdef ID2D1DrawInfo : public ID2D1RenderInfo

    SetPixelShaderConstantBuffer proc :LPBYTE, :UINT32
    SetResourceTexture	proc :UINT32, :ptr D2D1ResourceTexture
    SetVertexShaderConstantBuffer proc :LPBYTE, :UINT32
    SetPixelShader	proc :REFGUID, :D2D1_PIXEL_OPTIONS
    SetVertexProcessing proc :ptr ID2D1VertexBuffer, :D2D1_VERTEX_OPTIONS, :ptr D2D1_BLEND_DESCRIPTION, :ptr D2D1_VERTEX_RANGE, :ptr GUID

    .ends


DEFINE_IIDX(ID2D1ComputeInfo, "5598b14b-9fd7-48b7-9bdb-8f0964eb38bc")

.comdef ID2D1ComputeInfo : public ID2D1RenderInfo

    SetComputeShaderConstantBuffer proc :LPBYTE, :UINT32
    SetComputeShader	proc :REFGUID
    SetResourceTexture	proc :UINT32, :ptr ID2D1ResourceTexture

    .ends


DEFINE_IIDX(ID2D1TransformNode, "b2efe1e7-729f-4102-949f-505fa21bf666")

.comdef ID2D1TransformNode : public IUnknown

    GetInputCount	proc

    .ends


DEFINE_IIDX(ID2D1TransformGraph, "13d29038-c3e6-4034-9081-13b53a417992")

.comdef ID2D1TransformGraph : public IUnknown

    GetInputCount	proc
    SetSingleTransformNode proc :ptr ID2D1TransformNode
    AddNode		proc :ptr ID2D1TransformNode
    RemoveNode		proc :ptr ID2D1TransformNode
    SetOutputNode	proc :ptr ID2D1TransformNode
    ConnectNode		proc :ptr ID2D1TransformNode, :ptr ID2D1TransformNode, :UINT32
    ConnectToEffectInput proc :UINT32, :ptr ID2D1TransformNode, :UINT32
    Clear		proc
    SetPassthroughGraph proc :UINT32

    .ends


DEFINE_IIDX(ID2D1Transform, "ef1a287d-342a-4f76-8fdb-da0d6ea9f92b")

.comdef ID2D1Transform : public ID2D1TransformNode

    MapOutputRectToInputRects proc :ptr D2D1_RECT_L, :ptr D2D1_RECT_L, :UINT32
    MapInputRectsToOutputRect proc :ptr D2D1_RECT_L, :ptr D2D1_RECT_L, :UINT32, :ptr D2D1_RECT_L, :ptr D2D1_RECT_L
    MapInvalidRect	proc :UINT32, :D2D1_RECT_L, :ptr D2D1_RECT_L

    .ends


DEFINE_IIDX(ID2D1DrawTransform, "36bfdcb6-9739-435d-a30d-a653beff6a6f")

.comdef ID2D1DrawTransform : public ID2D1Transform

    SetDrawInfo		proc :ptr ID2D1DrawInfo

    .ends


DEFINE_IIDX(ID2D1ComputeTransform, "0d85573c-01e3-4f7d-bfd9-0d60608bf3c3")

.comdef ID2D1ComputeTransform : public ID2D1Transform

    SetComputeInfo	proc :ptr ID2D1ComputeInfo
    CalculateThreadgroups proc :ptr D2D1_RECT_L, :ptr UINT32, :ptr UINT32, :ptr UINT32

    .ends


DEFINE_IIDX(ID2D1AnalysisTransform, "0359dc30-95e6-4568-9055-27720d130e93")

.comdef ID2D1AnalysisTransform : public IUnknown

    ProcessAnalysisResults proc :LPBYTE, :UINT32

    .ends


DEFINE_IIDX(ID2D1SourceTransform, "db1800dd-0c34-4cf9-be90-31cc0a5653e1")

.comdef ID2D1SourceTransform : public ID2D1Transform

    SetRenderInfo	proc :ptr ID2D1RenderInfo
    Draw		proc :ptr ID2D1Bitmap1, :ptr D2D1_RECT_L, :D2D1_POINT_2U

    .ends


DEFINE_IIDX(ID2D1ConcreteTransform, "1a799d8a-69f7-4e4c-9fed-437ccc6684cc")

.comdef ID2D1ConcreteTransform : public ID2D1TransformNode

    SetOutputBuffer	proc :D2D1_BUFFER_PRECISION, :D2D1_CHANNEL_DEPTH
    SetCached		proc :BOOL

    .ends


DEFINE_IIDX(ID2D1BlendTransform, "63ac0b32-ba44-450f-8806-7f4ca1ff2f1b")

.comdef ID2D1BlendTransform : public ID2D1ConcreteTransform

    SetDescription	proc :ptr D2D1_BLEND_DESCRIPTION
    GetDescription	proc :ptr D2D1_BLEND_DESCRIPTION

    .ends


DEFINE_IIDX(ID2D1BorderTransform, "4998735c-3a19-473c-9781-656847e3a347")

.comdef ID2D1BorderTransform : public ID2D1ConcreteTransform

    SetExtendModeX	proc :D2D1_EXTEND_MODE
    SetExtendModeY	proc :D2D1_EXTEND_MODE
    GetExtendModeX	proc
    GetExtendModeY	proc

    .ends


DEFINE_IIDX(ID2D1OffsetTransform, "3fe6adea-7643-4f53-bd14-a0ce63f24042")

.comdef ID2D1OffsetTransform : public ID2D1TransformNode

    SetOffset		proc :D2D1_POINT_2L
    GetOffset		proc

    .ends


DEFINE_IIDX(ID2D1BoundsAdjustmentTransform, "90f732e2-5092-4606-a819-8651970baccd")

.comdef ID2D1BoundsAdjustmentTransform : public ID2D1TransformNode

    SetOutputBounds	proc :ptr D2D1_RECT_L
    GetOutputBounds	proc :ptr D2D1_RECT_L

    .ends


DEFINE_IIDX(ID2D1EffectImpl, "a248fd3f-3e6c-4e63-9f03-7f68ecc91db9")

.comdef ID2D1EffectImpl : public IUnknown

    Initialize		proc :ptr ID2D1EffectContext, :ptr ID2D1TransformGraph
    PrepareForRender	proc :D2D1_CHANGE_TYPE
    SetGraph		proc :ptr ID2D1TransformGraph

    .ends


DEFINE_IIDX(ID2D1EffectContext, "3d9f916b-27dc-4ad7-b4f1-64945340f563")

.comdef ID2D1EffectContext : public IUnknown

    GetDpi		proc :ptr FLOAT, :ptr FLOAT
    CreateEffect	proc :REFCLSID, :ptr ptr ID2D1Effect
    GetMaximumSupportedFeatureLevel proc :ptr D3D_FEATURE_LEVEL, :UINT32, :ptr D3D_FEATURE_LEVEL
    CreateTransformNodeFromEffect proc :ptr ID2D1Effect, :ptr ptr ID2D1TransformNode
    CreateBlendTransform proc :UINT32, :ptr D2D1_BLEND_DESCRIPTION, :ptr ptr ID2D1BlendTransform
    CreateBorderTransform proc :D2D1_EXTEND_MODE, :D2D1_EXTEND_MODE, :ptr ptr ID2D1BorderTransform
    CreateOffsetTransform proc :D2D1_POINT_2L, :ptr ptr ID2D1OffsetTransform
    CreateBoundsAdjustmentTransform proc :ptr D2D1_RECT_L, :ptr ptr ID2D1BoundsAdjustmentTransform
    LoadPixelShader	proc :REFGUID, :LPBYTE, :UINT32
    LoadVertexShader	proc :REFGUID, :LPBYTE, :UINT32
    LoadComputeShader	proc :REFGUID, :LPBYTE, :UINT32
    IsShaderLoaded	proc :REFGUID
    CreateResourceTexture proc :ptr GUID, :ptr D2D1_RESOURCE_TEXTURE_PROPERTIES, :LPBYTE, :ptr UINT32, :UINT32, :ptr ptr ID2D1ResourceTexture
    FindResourceTexture proc :ptr GUID, :ptr ptr ID2D1ResourceTexture
    CreateVertexBuffer	proc :ptr D2D1_VERTEX_BUFFER_PROPERTIES, :ptr GUID, :ptr D2D1_CUSTOM_VERTEX_BUFFER_PROPERTIES, :ptr ptr ID2D1VertexBuffer
    FindVertexBuffer	proc :ptr GUID, :ptr ptr ID2D1VertexBuffer
    CreateColorContext	proc :D2D1_COLOR_SPACE, :LPBYTE, :UINT32, :ptr ptr ID2D1ColorContext
    CreateColorContextFromFilename proc :PCWSTR, :ptr ptr ID2D1ColorContext
    CreateColorContextFromWicColorContext proc :ptr IWICColorContext, :ptr ptr ID2D1ColorContext
    CheckFeatureSupport proc :D2D1_FEATURE, :ptr, :UINT32
    IsBufferPrecisionSupported proc :D2D1_BUFFER_PRECISION

    .ends

endif


ifdef D2D_USE_C_DEFINITIONS
endif

include d2d1_1helper.inc
endif
