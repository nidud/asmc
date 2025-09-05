ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eapplicationmodel2Eresources2Ecore_h__
define __windows2Eapplicationmodel2Eresources2Ecore_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.inc

ifndef ____FIIterator_1_Windows__CApplicationModel__CResources__CCore__CResourceCandidate_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CResources__CCore__CResourceCandidate_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CResources__CCore__CResourceCandidate, "e151bd8c-a286-57ab-bcea-79b7bc2687a1")

.comdef __FIIterator_1_Windows__CApplicationModel__CResources__CCore__CResourceCandidate : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CResources__CCore__CResourceCandidate_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CResources__CCore__CResourceCandidate_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CResources__CCore__CResourceCandidate, "d89c9498-8869-57f8-a883-9c2dfeecb6c6")

.comdef __FIIterable_1_Windows__CApplicationModel__CResources__CCore__CResourceCandidate : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CApplicationModel__CResources__CCore__CResourceQualifier_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CResources__CCore__CResourceQualifier_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CResources__CCore__CResourceQualifier, "fedb74db-e74f-597a-b9bf-704b0dadca38")

.comdef __FIIterator_1_Windows__CApplicationModel__CResources__CCore__CResourceQualifier : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CResources__CCore__CResourceQualifier_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CResources__CCore__CResourceQualifier_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CResources__CCore__CResourceQualifier, "2eee68e2-687c-5f7a-a14e-588c4d3089e1")

.comdef __FIIterable_1_Windows__CApplicationModel__CResources__CCore__CResourceQualifier : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CNamedResource_INTERFACE_DEFINED__
define ____FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CNamedResource_INTERFACE_DEFINED__
DEFINE_IIDX(__FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CNamedResource, "bd4b0143-3a22-5ee2-92ed-7bc3c129e52b")

.comdef __FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CNamedResource : public IInspectable

    get_Key             proc :ptr
    get_Value           proc :ptr
   .ends

endif

ifndef ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CNamedResource_INTERFACE_DEFINED__
define ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CNamedResource_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CNamedResource, "7fdcc3d7-e13e-5f76-afc6-0769c4086399")

.comdef __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CNamedResource : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CNamedResource_INTERFACE_DEFINED__
define ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CNamedResource_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CNamedResource, "bf16482e-80ed-51f0-b9c9-3a804e2d6403")

.comdef __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CNamedResource : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIMapView_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CNamedResource_INTERFACE_DEFINED__
define ____FIMapView_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CNamedResource_INTERFACE_DEFINED__
DEFINE_IIDX(__FIMapView_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CNamedResource, "4825d6c4-835a-5da1-9bdd-12e97e16fb7a")

.comdef __FIMapView_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CNamedResource : public IInspectable

    Lookup              proc :HSTRING, :ptr
    get_Size            proc :ptr
    HasKey              proc :HSTRING, :ptr
    Split               proc :ptr, :ptr
   .ends

endif

ifndef ____FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CResourceMap_INTERFACE_DEFINED__
define ____FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CResourceMap_INTERFACE_DEFINED__
DEFINE_IIDX(__FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CResourceMap, "159782ba-798d-5ae6-85c7-c7bb551aae61")

.comdef __FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CResourceMap : public IInspectable

    get_Key             proc :ptr
    get_Value           proc :ptr
   .ends

endif

ifndef ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CResourceMap_INTERFACE_DEFINED__
define ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CResourceMap_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CResourceMap, "28cf8d5e-69f6-59f6-9865-bca97d59f74f")

.comdef __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CResourceMap : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CResourceMap_INTERFACE_DEFINED__
define ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CResourceMap_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CResourceMap, "9895431e-a817-5509-91e6-d90a933ed830")

.comdef __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CResourceMap : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIMapView_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CResourceMap_INTERFACE_DEFINED__
define ____FIMapView_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CResourceMap_INTERFACE_DEFINED__
DEFINE_IIDX(__FIMapView_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CResourceMap, "d4349ade-93b1-5325-ba5c-05f35eeffc55")

.comdef __FIMapView_2_HSTRING_Windows__CApplicationModel__CResources__CCore__CResourceMap : public IInspectable

    Lookup              proc :HSTRING, :ptr
    get_Size            proc :ptr
    HasKey              proc :HSTRING, :ptr
    Split               proc :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CResources__CCore__CResourceCandidate_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CResources__CCore__CResourceCandidate_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CResources__CCore__CResourceCandidate, "e28e92f0-9ffb-5ea7-9fc9-a73bda471886")

.comdef __FIVectorView_1_Windows__CApplicationModel__CResources__CCore__CResourceCandidate : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CResources__CCore__CResourceQualifier_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CResources__CCore__CResourceQualifier_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CResources__CCore__CResourceQualifier, "b82c58dc-1cc0-53f0-b0f4-66ef39a81cd6")

.comdef __FIVectorView_1_Windows__CApplicationModel__CResources__CCore__CResourceQualifier : public IInspectable

    GetAt               proc :UINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :UINT, :UINT, :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace ApplicationModel
.namespace Resources
.namespace Core

ifndef ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CIResourceManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CIResourceManager_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Resources_Core_IResourceManager <L"Windows.ApplicationModel.Resources.Core.IResourceManager">
DEFINE_IIDX(IResourceManager, "F744D97B-9988-44FB-ABD6-5378844CFA8B")

.comdef IResourceManager : public IInspectable

    get_MainResourceMap proc :ptr
    get_AllResourceMaps proc :ptr
    get_DefaultContext  proc :ptr
    LoadPriFiles        proc :ptr
    UnloadPriFiles      proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CIResourceManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CIResourceManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Resources_Core_IResourceManagerStatics <L"Windows.ApplicationModel.Resources.Core.IResourceManagerStatics">
DEFINE_IIDX(IResourceManagerStatics, "1CC0FDFC-69EE-4E43-9901-47F12687BAF7")

.comdef IResourceManagerStatics : public IInspectable

    get_Current         proc :ptr
    IsResourceReference proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CIResourceQualifier_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CIResourceQualifier_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Resources_Core_IResourceQualifier <L"Windows.ApplicationModel.Resources.Core.IResourceQualifier">
DEFINE_IIDX(IResourceQualifier, "785DA5B2-4AFD-4376-A888-C5F9A6B7A05C")

.comdef IResourceQualifier : public IInspectable

    get_QualifierName   proc :ptr
    get_QualifierValue  proc :ptr
    get_IsDefault       proc :ptr
    get_IsMatch         proc :ptr
    get_Score           proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CIResourceContext_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CIResourceContext_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Resources_Core_IResourceContext <L"Windows.ApplicationModel.Resources.Core.IResourceContext">
DEFINE_IIDX(IResourceContext, "2FA22F4B-707E-4B27-AD0D-D0D8CD468FD2")

.comdef IResourceContext : public IInspectable

    get_QualifierValues proc :ptr
    Reset               proc
    ResetQualifierValues proc :ptr
    OverrideToMatch     proc :ptr
    Clone               proc :ptr
    get_Languages       proc :ptr
    put_Languages       proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CIResourceContextStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CIResourceContextStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Resources_Core_IResourceContextStatics <L"Windows.ApplicationModel.Resources.Core.IResourceContextStatics">
DEFINE_IIDX(IResourceContextStatics, "98BE9D6C-6338-4B31-99DF-B2B442F17149")

.comdef IResourceContextStatics : public IInspectable

    CreateMatchingContext proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CIResourceContextStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CIResourceContextStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Resources_Core_IResourceContextStatics2 <L"Windows.ApplicationModel.Resources.Core.IResourceContextStatics2">
DEFINE_IIDX(IResourceContextStatics2, "41F752EF-12AF-41B9-AB36-B1EB4B512460")

.comdef IResourceContextStatics2 : public IInspectable

    GetForCurrentView   proc :ptr
    SetGlobalQualifierValue proc :HSTRING, :HSTRING
    ResetGlobalQualifierValues proc
    ResetGlobalQualifierValuesForSpecifiedQualifiers proc :ptr
    GetForViewIndependentUse proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CIResourceCandidate_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CIResourceCandidate_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Resources_Core_IResourceCandidate <L"Windows.ApplicationModel.Resources.Core.IResourceCandidate">
DEFINE_IIDX(IResourceCandidate, "AF5207D9-C433-4764-B3FD-8FA6BFBCBADC")

.comdef IResourceCandidate : public IInspectable

    get_Qualifiers      proc :ptr
    get_IsMatch         proc :ptr
    get_IsMatchAsDefault proc :ptr
    get_IsDefault       proc :ptr
    get_ValueAsString   proc :ptr
    GetValueAsFileAsync proc :ptr
    GetQualifierValue   proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CINamedResource_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CINamedResource_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Resources_Core_INamedResource <L"Windows.ApplicationModel.Resources.Core.INamedResource">
DEFINE_IIDX(INamedResource, "1C98C219-0B13-4240-89A5-D495DC189A00")

.comdef INamedResource : public IInspectable

    get_Uri             proc :ptr
    get_Candidates      proc :ptr
    Resolve             proc :ptr
    ResolveForContext   proc :ptr, :ptr
    ResolveAll          proc :ptr
    ResolveAllForContext proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CIResourceMap_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CResources_CCore_CIResourceMap_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Resources_Core_IResourceMap <L"Windows.ApplicationModel.Resources.Core.IResourceMap">
DEFINE_IIDX(IResourceMap, "72284824-DB8C-42F8-B08C-53FF357DAD82")

.comdef IResourceMap : public IInspectable

    get_Uri             proc :ptr
    GetValue            proc :HSTRING, :ptr
    GetValueForContext  proc :HSTRING, :ptr, :ptr
    GetSubtree          proc :HSTRING, :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceMap_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceMap_DEFINED
define RuntimeClass_Windows_ApplicationModel_Resources_Core_ResourceMap <L"Windows.ApplicationModel.Resources.Core.ResourceMap">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceContext_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceContext_DEFINED
define RuntimeClass_Windows_ApplicationModel_Resources_Core_ResourceContext <L"Windows.ApplicationModel.Resources.Core.ResourceContext">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceManager_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceManager_DEFINED
define RuntimeClass_Windows_ApplicationModel_Resources_Core_ResourceManager <L"Windows.ApplicationModel.Resources.Core.ResourceManager">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceQualifier_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceQualifier_DEFINED
define RuntimeClass_Windows_ApplicationModel_Resources_Core_ResourceQualifier <L"Windows.ApplicationModel.Resources.Core.ResourceQualifier">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceCandidate_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceCandidate_DEFINED
define RuntimeClass_Windows_ApplicationModel_Resources_Core_ResourceCandidate <L"Windows.ApplicationModel.Resources.Core.ResourceCandidate">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_NamedResource_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_NamedResource_DEFINED
define RuntimeClass_Windows_ApplicationModel_Resources_Core_NamedResource <L"Windows.ApplicationModel.Resources.Core.NamedResource">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceMapIterator_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceMapIterator_DEFINED
define RuntimeClass_Windows_ApplicationModel_Resources_Core_ResourceMapIterator <L"Windows.ApplicationModel.Resources.Core.ResourceMapIterator">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceMapMapView_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceMapMapView_DEFINED
define RuntimeClass_Windows_ApplicationModel_Resources_Core_ResourceMapMapView <L"Windows.ApplicationModel.Resources.Core.ResourceMapMapView">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceMapMapViewIterator_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceMapMapViewIterator_DEFINED
define RuntimeClass_Windows_ApplicationModel_Resources_Core_ResourceMapMapViewIterator <L"Windows.ApplicationModel.Resources.Core.ResourceMapMapViewIterator">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceQualifierObservableMap_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceQualifierObservableMap_DEFINED
define RuntimeClass_Windows_ApplicationModel_Resources_Core_ResourceQualifierObservableMap <L"Windows.ApplicationModel.Resources.Core.ResourceQualifierObservableMap">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceQualifierMapView_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceQualifierMapView_DEFINED
define RuntimeClass_Windows_ApplicationModel_Resources_Core_ResourceQualifierMapView <L"Windows.ApplicationModel.Resources.Core.ResourceQualifierMapView">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceQualifierVectorView_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceQualifierVectorView_DEFINED
define RuntimeClass_Windows_ApplicationModel_Resources_Core_ResourceQualifierVectorView <L"Windows.ApplicationModel.Resources.Core.ResourceQualifierVectorView">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceCandidateVectorView_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceCandidateVectorView_DEFINED
define RuntimeClass_Windows_ApplicationModel_Resources_Core_ResourceCandidateVectorView <L"Windows.ApplicationModel.Resources.Core.ResourceCandidateVectorView">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceContextLanguagesVectorView_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Resources_Core_ResourceContextLanguagesVectorView_DEFINED
define RuntimeClass_Windows_ApplicationModel_Resources_Core_ResourceContextLanguagesVectorView <L"Windows.ApplicationModel.Resources.Core.ResourceContextLanguagesVectorView">
endif

endif

