ifndef _D3DX9ANIM_H
_D3DX9ANIM_H equ <>
.xlist

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
Value			D3DXVECTOR3 ?
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

ID3DXAnimationSet	STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** ID3DXAnimationSet methods **
GetName			PVOID ?
GetPeriod		PVOID ?
GetPeriodicPosition	PVOID ?
GetNumAnimations	PVOID ?
GetAnimationNameByIndex PVOID ?
GetAnimationIndexByName PVOID ?
GetSRT			PVOID ?
GetCallback		PVOID ?
ID3DXAnimationSet	ENDS

ID3DXKeyframedAnimationSet STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** ID3DXAnimationSet methods **
GetName			PVOID ?
GetPeriod		PVOID ?
GetPeriodicPosition	PVOID ?
GetNumAnimations	PVOID ?
GetAnimationNameByIndex PVOID ?
GetAnimationIndexByName PVOID ?
GetSRT			PVOID ?
GetCallback		PVOID ?
;;** ID3DXKeyframedAnimationSet methods **
GetPlaybackType		PVOID ?
GetSourceTicksPerSecond PVOID ?
GetNumScaleKeys		PVOID ?
GetScaleKeys		PVOID ?
GetScaleKey		PVOID ?
SetScaleKey		PVOID ?
GetNumRotationKeys	PVOID ?
GetRotationKeys		PVOID ?
GetRotationKey		PVOID ?
SetRotationKey		PVOID ?
GetNumTranslationKeys	PVOID ?
GetTranslationKeys	PVOID ?
GetTranslationKey	PVOID ?
SetTranslationKey	PVOID ?
GetNumCallbackKeys	PVOID ?
GetCallbackKeys		PVOID ?
GetCallbackKey		PVOID ?
SetCallbackKey		PVOID ?
UnregisterScaleKey	PVOID ?
UnregisterRotationKey	PVOID ?
UnregisterTranslationKey PVOID ?
RegisterAnimationSRTKeys PVOID ?
Compress		PVOID ?
UnregisterAnimation	PVOID ?
ID3DXKeyframedAnimationSet ENDS

ID3DXCompressedAnimationSet STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** ID3DXAnimationSet methods **
GetName			PVOID ?
GetPeriod		PVOID ?
GetPeriodicPosition	PVOID ?
GetNumAnimations	PVOID ?
GetAnimationNameByIndex PVOID ?
GetAnimationIndexByName PVOID ?
GetSRT			PVOID ?
GetCallback		PVOID ?
;;** ID3DXCompressedAnimationSet methods **
GetPlaybackType		PVOID ?
GetSourceTicksPerSecond PVOID ?
GetCompressedData	PVOID ?
GetNumCallbackKeys	PVOID ?
GetCallbackKeys		PVOID ?
ID3DXCompressedAnimationSet ENDS

ID3DXAnimationCallbackHandler STRUC
HandleCallbac		PVOID ?
ID3DXAnimationCallbackHandler ENDS

ID3DXAnimationController STRUC
;;** IUnknown methods **
QueryInterface		PVOID ?
AddRef			PVOID ?
Release			PVOID ?
;;** ID3DXAnimationController methods **
GetMaxNumAnimationOutputs PVOID ?
GetMaxNumAnimationSets	PVOID ?
GetMaxNumTracks		PVOID ?
GetMaxNumEvents		PVOID ?
RegisterAnimationOutput PVOID ?
RegisterAnimationSet	PVOID ?
UnregisterAnimationSet	PVOID ?
GetNumAnimationSets	PVOID ?
GetAnimationSet		PVOID ?
GetAnimationSetByName	PVOID ?
AdvanceTime		PVOID ?
ResetTime		PVOID ?
GetTime			PVOID ?
SetTrackAnimationSet	PVOID ?
GetTrackAnimationSet	PVOID ?
SetTrackPriority	PVOID ?
SetTrackSpeed		PVOID ?
SetTrackWeight		PVOID ?
SetTrackPosition	PVOID ?
SetTrackEnable		PVOID ?
SetTrackDesc		PVOID ?
GetTrackDesc		PVOID ?
SetPriorityBlend	PVOID ?
GetPriorityBlend	PVOID ?
KeyTrackSpeed		PVOID ?
KeyTrackWeight		PVOID ?
KeyTrackPosition	PVOID ?
KeyTrackEnable		PVOID ?
KeyPriorityBlend	PVOID ?
UnkeyEvent		PVOID ?
UnkeyAllTrackEvents	PVOID ?
UnkeyAllPriorityBlends	PVOID ?
GetCurrentTrackEvent	PVOID ?
GetCurrentPriorityBlend PVOID ?
GetUpcomingTrackEvent	PVOID ?
GetUpcomingPriorityBlend PVOID ?
ValidateEvent		PVOID ?
GetEventDesc		PVOID ?
CloneAnimationController PVOID ?
ID3DXAnimationController ENDS

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

.list
endif ;; _D3DX9ANIM_H
