ifndef _RPC500_
include rpc500.inc
endif
ifndef __manipulations_h__
define __manipulations_h__
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum MANIPULATION_PROCESSOR_MANIPULATIONS {
	MANIPULATION_NONE		= 0,
	MANIPULATION_TRANSLATE_X	= 0x1,
	MANIPULATION_TRANSLATE_Y	= 0x2,
	MANIPULATION_SCALE		= 0x4,
	MANIPULATION_ROTATE		= 0x8,
	MANIPULATION_ALL		= 0xf
	}


MANIPULATOR_ID typedef dword

ifndef __ManipulationsLib_LIBRARY_DEFINED__
define __ManipulationsLib_LIBRARY_DEFINED__

externdef LIBID_ManipulationsLib:IID

ifndef ___IManipulationEvents_INTERFACE_DEFINED__
define ___IManipulationEvents_INTERFACE_DEFINED__

DEFINE_IIDX(_IManipulationEvents, "4f62c8da-9c53-4b22-93df-927a862bbb03")

.comdef _IManipulationEvents : public IUnknown
    ManipulationStarted proc :real4, :real4
    ManipulationDelta	proc :real4, :real4, :real4, :real4, :real4, :real4, :real4, :real4, :real4, :real4, :real4, :real4
    ManipulationCompleted proc :real4, :real4, :real4, :real4, :real4, :real4, :real4
   .ends

endif

ifndef __IInertiaProcessor_INTERFACE_DEFINED__
define __IInertiaProcessor_INTERFACE_DEFINED__

DEFINE_IIDX(IInertiaProcessor, "18b00c6d-c5ee-41b1-90a9-9d4a929095ad")

.comdef IInertiaProcessor : public IUnknown
    get_InitialOriginX	proc :ptr
    put_InitialOriginX	proc :real4
    get_InitialOriginY	proc :ptr
    put_InitialOriginY	proc :real4
    get_InitialVelocityX proc :ptr
    put_InitialVelocityX proc :real4
    get_InitialVelocityY proc :ptr
    put_InitialVelocityY proc :real4
    get_InitialAngularVelocity proc :ptr
    put_InitialAngularVelocity proc :real4
    get_InitialExpansionVelocity proc :ptr
    put_InitialExpansionVelocity proc :real4
    get_InitialRadius	proc :ptr
    put_InitialRadius	proc :real4
    get_BoundaryLeft	proc :ptr
    put_BoundaryLeft	proc :real4
    get_BoundaryTop	proc :ptr
    put_BoundaryTop	proc :real4
    get_BoundaryRight	proc :ptr
    put_BoundaryRight	proc :real4
    get_BoundaryBottom	proc :ptr
    put_BoundaryBottom	proc :real4
    get_ElasticMarginLeft proc :ptr
    put_ElasticMarginLeft proc :real4
    get_ElasticMarginTop proc :ptr
    put_ElasticMarginTop proc :real4
    get_ElasticMarginRight proc :ptr
    put_ElasticMarginRight proc :real4
    get_ElasticMarginBottom proc :ptr
    put_ElasticMarginBottom proc :real4
    get_DesiredDisplacement proc :ptr
    put_DesiredDisplacement proc :real4
    get_DesiredRotation proc :ptr
    put_DesiredRotation proc :real4
    get_DesiredExpansion proc :ptr
    put_DesiredExpansion proc :real4
    get_DesiredDeceleration proc :ptr
    put_DesiredDeceleration proc :real4
    get_DesiredAngularDeceleration proc :ptr
    put_DesiredAngularDeceleration proc :real4
    get_DesiredExpansionDeceleration proc :ptr
    put_DesiredExpansionDeceleration proc :real4
    get_InitialTimestamp proc :ptr
    put_InitialTimestamp proc :DWORD
    Reset		proc
    Process		proc :ptr
    ProcessTime		proc :DWORD, :ptr
    Complete		proc
    CompleteTime	proc :DWORD
   .ends

endif

ifndef __IManipulationProcessor_INTERFACE_DEFINED__
define __IManipulationProcessor_INTERFACE_DEFINED__

DEFINE_IIDX(IManipulationProcessor, "A22AC519-8300-48a0-BEF4-F1BE8737DBA4")

.comdef IManipulationProcessor : public IUnknown
    get_SupportedManipulations proc :ptr
    put_SupportedManipulations proc :MANIPULATION_PROCESSOR_MANIPULATIONS
    get_PivotPointX	proc :ptr
    put_PivotPointX	proc :real4
    get_PivotPointY	proc :ptr
    put_PivotPointY	proc :real4
    get_PivotRadius	proc :ptr
    put_PivotRadius	proc :real4
    CompleteManipulation proc
    ProcessDown		proc :MANIPULATOR_ID, :real4, :real4
    ProcessMove		proc :MANIPULATOR_ID, :real4, :real4
    ProcessUp		proc :MANIPULATOR_ID, :real4, :real4
    ProcessDownWithTime proc :MANIPULATOR_ID, :real4, :real4, :DWORD
    ProcessMoveWithTime proc :MANIPULATOR_ID, :real4, :real4, :DWORD
    ProcessUpWithTime	proc :MANIPULATOR_ID, :real4, :real4, :DWORD
    GetVelocityX	proc :ptr
    GetVelocityY	proc :ptr
    GetExpansionVelocity proc :ptr
    GetAngularVelocity	proc :ptr
    get_MinimumScaleRotateRadius proc :ptr
    put_MinimumScaleRotateRadius proc :real4
   .ends

endif

DEFINE_IIDX(CLSID_InertiaProcessor, "abb27087-4ce0-4e58-a0cb-e24df96814be")
DEFINE_GUIDS(CLSID_ManipulationProcessor, "597D4FB0-47FD-4aff-89B9-C6CFAE8CF08E")

endif

endif

endif
