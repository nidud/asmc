ifndef _D3DX9ANIM_H
_D3DX9ANIM_H equ <>

DEFINE_GUID(IID_ID3DXAnimationSet,	     0x698cfb3f, 0x9289, 0x4d95, 0x9a, 0x57, 0x33, 0xa9, 0x4b, 0x5a, 0x65, 0xf9);
DEFINE_GUID(IID_ID3DXKeyframedAnimationSet,  0xfa4e8e3a, 0x9786, 0x407d, 0x8b, 0x4c, 0x59, 0x95, 0x89, 0x37, 0x64, 0xaf);
DEFINE_GUID(IID_ID3DXCompressedAnimationSet, 0x6cc2480d, 0x3808, 0x4739, 0x9f, 0x88, 0xde, 0x49, 0xfa, 0xcd, 0x8d, 0x4c);
DEFINE_GUID(IID_ID3DXAnimationController,    0xac8948ec, 0xf86d, 0x43e2, 0x96, 0xde, 0x31, 0xfc, 0x35, 0xf9, 0x6d, 0x9e);

D3DXMESHDATATYPE	typedef SDWORD
D3DXMESHTYPE_MESH	equ 1
D3DXMESHTYPE_PMESH	equ 2
D3DXMESHTYPE_PATCHMESH	equ 3
D3DXMESHTYPE_FORCE_DWORD equ 0x7fffffff

D3DXCALLBACK_SEARCH_FLAGS typedef SDWORD
D3DXCALLBACK_SEARCH_EXCLUDING_INITIAL_POSITION equ 0x00000001
D3DXCALLBACK_SEARCH_BEHIND_INITIAL_POSITION equ 0x00000002
D3DXCALLBACK_SEARCH_FORCE_DWORD equ 0x7fffffff

D3DXPLAYBACK_TYPE	typedef SDWORD
D3DXPLAY_LOOP		equ 0
D3DXPLAY_ONCE		equ 1
D3DXPLAY_PINGPONG	equ 2
D3DXPLAY_FORCE_DWORD	equ 0x7fffffff

D3DXCOMPRESSION_FLAGS	typedef SDWORD
D3DXCOMPRESSION_DEFAULT equ 0x00000000
D3DXCOMPRESSION_FORCE_DWORD equ 0x7fffffff

D3DXPRIORITY_TYPE	typedef SDWORD
D3DXPRIORITY_LOW	equ 0
D3DXPRIORITY_HIGH	equ 1
D3DXPRIORITY_FORCE_DWORD equ 0x7fffffff

D3DXEVENT_TYPE		typedef SDWORD
D3DXEVENT_TRACKSPEED	equ 0
D3DXEVENT_TRACKWEIGHT	equ 1
D3DXEVENT_TRACKPOSITION equ 2
D3DXEVENT_TRACKENABLE	equ 3
D3DXEVENT_PRIORITYBLEND equ 4
D3DXEVENT_FORCE_DWORD	equ 0x7fffffff

D3DXTRANSITION_TYPE	typedef SDWORD
D3DXTRANSITION_LINEAR	equ 0
D3DXTRANSITION_EASEINEASEOUT equ 1
D3DXTRANSITION_FORCE_DWORD equ 0x7fffffff

LPID3DXMesh		typedef ptr ID3DXMesh
LPID3DXPMesh		typedef ptr ID3DXPMesh
LPID3DXPatchMesh	typedef ptr ID3DXPatchMesh

D3DXMESHDATA		STRUC
_Type			D3DXMESHDATATYPE ?
UNION
 pMesh			LPID3DXMesh ?
 pPMesh			LPID3DXPMesh ?
 pPatchMesh		LPID3DXPatchMesh ?
ENDS
D3DXMESHDATA		ENDS
LPD3DXMESHDATA		typedef ptr D3DXMESHDATA

LPID3DXSkinInfo		typedef ptr ID3DXSkinInfo
D3DXMESHCONTAINER	STRUC
_Name			LPSTR ?
MeshData		D3DXMESHDATA <>
pMaterials		LPD3DXMATERIAL ?
pEffects		LPD3DXEFFECTINSTANCE ?
NumMaterials		dd ?
pAdjacency		LPDWORD ?
pSkinInfo		LPID3DXSkinInfo ?
pNextMeshContainer	typedef ptr D3DXMESHCONTAINER
D3DXMESHCONTAINER	ENDS
LPD3DXMESHCONTAINER	typedef ptr D3DXMESHCONTAINER

D3DXFRAME		STRUC
_Name			LPSTR ?
TransformationMatrix	D3DXMATRIX <>
pMeshContainer		LPD3DXMESHCONTAINER ?
pFrameSibling		typedef ptr D3DXFRAME
pFrameFirstChild	typedef ptr D3DXFRAME
D3DXFRAME		ENDS
LPD3DXFRAME		typedef ptr D3DXFRAME

D3DXKEY_VECTOR3		STRUC
Time			FLOAT ?
Value			D3DXVECTOR3 <>
D3DXKEY_VECTOR3		ENDS
LPD3DXKEY_VECTOR3	typedef ptr D3DXKEY_VECTOR3

D3DXKEY_QUATERNION	STRUC
Time			FLOAT ?
Value			D3DXQUATERNION <>
D3DXKEY_QUATERNION	ENDS
LPD3DXKEY_QUATERNION	typedef ptr D3DXKEY_QUATERNION

D3DXKEY_CALLBACK	STRUC
Time			float ?
pCallbackData		PVOID ?
D3DXKEY_CALLBACK	ENDS
LPD3DXKEY_CALLBACK	typedef ptr D3DXKEY_CALLBACK

D3DXTRACK_DESC		STRUC
Priority		D3DXPRIORITY_TYPE ?
Weight			FLOAT ?
Speed			FLOAT ?
Position		DOUBLE ?
Enable			BOOL ?
D3DXTRACK_DESC		ENDS
LPD3DXTRACK_DESC	typedef ptr D3DXTRACK_DESC

D3DXEVENT_DESC		STRUC
_Type			D3DXEVENT_TYPE ?
Track			UINT ?
StartTime		DOUBLE ?
Duration		DOUBLE ?
Transition		D3DXTRANSITION_TYPE ?
UNION
 Weight			FLOAT ?
 Speed			FLOAT ?
 Position		DOUBLE ?
 Enable			BOOL ?
ENDS
D3DXEVENT_DESC		ENDS
LPD3DXEVENT_DESC	typedef ptr D3DXEVENT_DESC

D3DXEVENTHANDLE		typedef DWORD
LPD3DXEVENTHANDLE	typedef ptr DWORD

ID3DXAllocateHierarchy	STRUC
CreateFrame		PVOID ?
CreateMeshContainer	PVOID ?
DestroyFrame		PVOID ?
DestroyMeshContainer	PVOID ?
ID3DXAllocateHierarchy	ENDS

ID3DXLoadUserData	STRUC
LoadTopLevelData	PVOID ?
LoadFrameChildData	PVOID ?
LoadMeshChildData	PVOID ?
ID3DXLoadUserData	ENDS

ID3DXSaveUserData	STRUC
AddFrameChildData	PVOID ?
AddMeshChildData	PVOID ?
AddTopLevelDataObjectsPre PVOID ?
AddTopLevelDataObjectsPost PVOID ?
RegisterTemplates	PVOID ?
SaveTemplates		PVOID ?
ID3DXSaveUserData	ENDS

.comdef ID3DXAnimationSet
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetName		proc
    GetPeriod		proc
    GetPeriodicPosition proc :DOUBLE
    GetNumAnimations	proc
    GetAnimationNameByIndex proc :UINT, :ptr
    GetAnimationIndexByName proc :ptr, :ptr
    GetSRT		proc :DOUBLE, :UINT, :ptr, :ptr, :ptr
    GetCallback		proc :double, :DWORD, :ptr, :ptr
    .ends

.comdef ID3DXKeyframedAnimationSet
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetName		proc
    GetPeriod		proc
    GetPeriodicPosition proc :DOUBLE
    GetNumAnimations	proc
    GetAnimationNameByIndex proc :UINT, :ptr
    GetAnimationIndexByName proc :ptr, :ptr
    GetSRT		proc :DOUBLE, :UINT, :ptr, :ptr, :ptr
    GetCallback		proc :double, :DWORD, :ptr, :ptr
    GetPlaybackType	proc
    GetSourceTicksPerSecond proc
    GetNumScaleKeys	proc :UINT
    GetScaleKeys	proc :UINT, :LPD3DXKEY_VECTOR3
    GetScaleKey		proc :UINT, :UINT, :LPD3DXKEY_VECTOR3
    SetScaleKey		proc :UINT, :UINT, :LPD3DXKEY_VECTOR3
    GetNumRotationKeys	proc :UINT
    GetRotationKeys	proc :UINT, :LPD3DXKEY_QUATERNION
    GetRotationKey	proc :UINT, :UINT, :LPD3DXKEY_QUATERNION
    SetRotationKey	proc :UINT, :UINT, :LPD3DXKEY_QUATERNION
    GetNumTranslationKeys proc :UINT
    GetTranslationKeys	proc :UINT, :LPD3DXKEY_VECTOR3
    GetTranslationKey	proc :UINT, :UINT, :LPD3DXKEY_VECTOR3
    SetTranslationKey	proc :UINT, :UINT, :LPD3DXKEY_VECTOR3
    GetNumCallbackKeys	proc
    GetCallbackKeys	proc :LPD3DXKEY_CALLBACK
    GetCallbackKey	proc :UINT, :LPD3DXKEY_CALLBACK
    SetCallbackKey	proc :UINT, :LPD3DXKEY_CALLBACK
    UnregisterScaleKey	proc :UINT, :UINT
    UnregisterRotationKey proc :UINT, :UINT
    UnregisterTranslationKey proc :UINT, :UINT
    RegisterAnimationSRTKeys proc :ptr, :UINT, :UINT, :UINT, :ptr, :ptr, :ptr, :ptr
    Compress		proc :DWORD, :float, :ptr, :ptr
    UnregisterAnimation proc :UINT
    .ends

.comdef ID3DXCompressedAnimationSet
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetName		proc
    GetPeriod		proc
    GetPeriodicPosition proc :DOUBLE
    GetNumAnimations	proc
    GetAnimationNameByIndex proc :UINT, :ptr
    GetAnimationIndexByName proc :ptr, :ptr
    GetSRT		proc :DOUBLE, :UINT, :ptr, :ptr, :ptr
    GetCallback		proc :double, :DWORD, :ptr, :ptr
    GetPlaybackType	proc
    GetSourceTicksPerSecond proc
    GetCompressedData	proc :ptr
    GetNumCallbackKeys	proc
    GetCallbackKeys	proc :LPD3DXKEY_CALLBACK
    .ends

.comdef ID3DXAnimationCallbackHandler
    HandleCallback	proc :UINT, :ptr
    .ends

.comdef ID3DXAnimationController
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetMaxNumAnimationOutputs proc
    GetMaxNumAnimationSets proc
    GetMaxNumTracks	proc
    GetMaxNumEvents	proc
    RegisterAnimationOutput proc :ptr, :ptr, :ptr, :ptr, :ptr
    RegisterAnimationSet proc :ptr
    UnregisterAnimationSet proc :ptr
    GetNumAnimationSets proc
    GetAnimationSet	proc :UINT, :ptr
    GetAnimationSetByName proc :ptr, :ptr
    AdvanceTime		proc :double, :ptr
    ResetTime		proc
    GetTime		proc
    SetTrackAnimationSet proc :UINT, :ptr
    GetTrackAnimationSet proc :UINT, :ptr
    SetTrackPriority	proc :UINT, :D3DXPRIORITY_TYPE
    SetTrackSpeed	proc :UINT, :float
    SetTrackWeight	proc :UINT, :float
    SetTrackPosition	proc :UINT, :double
    SetTrackEnable	proc :UINT, :BOOL
    SetTrackDesc	proc :UINT, :ptr
    GetTrackDesc	proc :UINT, :ptr
    SetPriorityBlend	proc :float
    GetPriorityBlend	proc
    KeyTrackSpeed	proc :UINT, :float, :double, :double, :D3DXTRANSITION_TYPE
    KeyTrackWeight	proc :UINT, :float, :double, :double, :D3DXTRANSITION_TYPE
    KeyTrackPosition	proc :UINT, :double, :double
    KeyTrackEnable	proc :UINT, :BOOL, :double
    KeyPriorityBlend	proc :float, :double, :double, :D3DXTRANSITION_TYPE
    UnkeyEvent		proc :D3DXEVENTHANDLE
    UnkeyAllTrackEvents proc :UINT
    UnkeyAllPriorityBlends proc
    GetCurrentTrackEvent proc :UINT, :D3DXEVENT_TYPE
    GetCurrentPriorityBlend proc
    GetUpcomingTrackEvent proc :UINT, :D3DXEVENTHANDLE
    GetUpcomingPriorityBlend proc :D3DXEVENTHANDLE
    ValidateEvent	proc :D3DXEVENTHANDLE
    GetEventDesc	proc :D3DXEVENTHANDLE, :ptr
    CloneAnimationController proc :UINT, :UINT, :UINT, :UINT, :ptr
    .ends

;HRESULT
D3DXLoadMeshHierarchyFromXA proto WINAPI \
	      filename: LPSTR,
		 flags: DWORD,
		device: ptr IDirect3DDevice9,
		 alloc: ptr ID3DXAllocateHierarchy,
      user_data_loader: ptr ID3DXLoadUserData,
       frame_hierarchy: ptr D3DXFRAME,
  animation_controller: ptr ID3DXAnimationController

;HRESULT
D3DXLoadMeshHierarchyFromXW proto WINAPI \
	      filename: LPWSTR,
		 flags: DWORD,
		device: ptr IDirect3DDevice9,
		 alloc: ptr ID3DXAllocateHierarchy,
      user_data_loader: ptr ID3DXLoadUserData,
       frame_hierarchy: ptr D3DXFRAME,
  animation_controller: ptr ID3DXAnimationController

D3DXLoadMeshHierarchyFromX equ __MINGW_NAME_AW(D3DXLoadMeshHierarchyFromX)
;HRESULT
D3DXLoadMeshHierarchyFromXInMemory proto WINAPI \
		 _data: PVOID,
	     data_size: DWORD,
		 flags: DWORD,
		device: ptr IDirect3DDevice9,
		 alloc: ptr ID3DXAllocateHierarchy,
      user_data_loader: ptr ID3DXLoadUserData,
       frame_hierarchy: ptr D3DXFRAME,
  animation_controller: ptr ID3DXAnimationController

;HRESULT
D3DXSaveMeshHierarchyToFileA proto WINAPI \
	      filename: LPSTR,
		format: DWORD,
	    frame_root: ptr D3DXFRAME,
  animation_controller: ptr ID3DXAnimationController,
       user_data_saver: ptr ID3DXSaveUserData

;HRESULT
D3DXSaveMeshHierarchyToFileW proto WINAPI \
	      filename: LPWSTR,
		format: DWORD,
	    frame_root: ptr D3DXFRAME,
  animation_controller: ptr ID3DXAnimationController,
       user_data_saver: ptr ID3DXSaveUserData

;HRESULT
D3DXFrameDestroy proto WINAPI \
	    frame_root: ptr D3DXFRAME,
		 alloc: ptr ID3DXAllocateHierarchy

;HRESULT
D3DXFrameAppendChild proto WINAPI \
		parent: ptr D3DXFRAME,
		 child: ptr D3DXFRAME

;D3DXFRAME *
D3DXFrameFind proto WINAPI \
		  root: ptr D3DXFRAME,
		 _name: LPSTR

;HRESULT
D3DXFrameRegisterNamedMatrices proto WINAPI \
	    frame_root: ptr D3DXFRAME,
  animation_controller: ptr ID3DXAnimationController

;UINT
D3DXFrameNumNamedMatrices proto WINAPI \
	    frame_root: ptr D3DXFRAME

;HRESULT
D3DXFrameCalculateBoundingSphere proto WINAPI \
	    frame_root: ptr D3DXFRAME,
		center: ptr D3DXVECTOR3,
		radius: ptr FLOAT

;HRESULT
D3DXCreateKeyframedAnimationSet proto WINAPI \
		 _name: LPSTR,
      ticks_per_second: double,
	 playback_type: D3DXPLAYBACK_TYPE,
       animation_count: UINT,
    callback_key_count: UINT,
	 callback_keys: ptr D3DXKEY_CALLBACK,
	 animation_set: ptr ID3DXKeyframedAnimationSet

;HRESULT
D3DXCreateCompressedAnimationSet proto WINAPI \
		 _name: LPSTR,
      ticks_per_second: double,
	 playback_type: D3DXPLAYBACK_TYPE,
       compressed_data: ptr ID3DXBuffer,
    callback_key_count: UINT,
	 callback_keys: ptr D3DXKEY_CALLBACK,
	 animation_set: ptr ID3DXCompressedAnimationSet

;HRESULT
D3DXCreateAnimationController proto WINAPI \
max_animation_output_count: UINT,
max_animation_set_count: UINT,
       max_track_count: UINT,
       max_event_count: UINT,
  animation_controller: ptr ID3DXAnimationController

endif
