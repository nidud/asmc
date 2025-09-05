ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Examl2Emedia2Emedia3d_h__
define __windows2Eui2Examl2Emedia2Emedia3d_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Media
.namespace Media3D

.template Matrix3D
    M11     DOUBLE ?
    M12     DOUBLE ?
    M13     DOUBLE ?
    M14     DOUBLE ?
    M21     DOUBLE ?
    M22     DOUBLE ?
    M23     DOUBLE ?
    M24     DOUBLE ?
    M31     DOUBLE ?
    M32     DOUBLE ?
    M33     DOUBLE ?
    M34     DOUBLE ?
    OffsetX DOUBLE ?
    OffsetY DOUBLE ?
    OffsetZ DOUBLE ?
    M44     DOUBLE ?
   .ends


ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelper_INTERFACE_DEFINED__
DEFINE_IIDX(IMatrix3DHelper, "E48C10EF-9927-4C9B-8213-07775512BA04")

.comdef IMatrix3DHelper : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CMedia_CMedia3D_CIMatrix3DHelperStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Media_Media3D_IMatrix3DHelperStatics <L"Windows.UI.Xaml.Media.Media3D.IMatrix3DHelperStatics">
DEFINE_IIDX(IMatrix3DHelperStatics, "9264545E-E158-4E74-8899-689160BD2F8C")

.comdef IMatrix3DHelperStatics : public IInspectable

    get_Identity        proc :ptr
    Multiply            proc :Windows::UI::Xaml::Media::Media3D::Matrix3D, :Windows::UI::Xaml::Media::Media3D::Matrix3D, :ptr
    FromElements        proc :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :DOUBLE, :ptr
    GetHasInverse       proc :Windows::UI::Xaml::Media::Media3D::Matrix3D, :ptr
    GetIsIdentity       proc :Windows::UI::Xaml::Media::Media3D::Matrix3D, :ptr
    Invert              proc :Windows::UI::Xaml::Media::Media3D::Matrix3D, :ptr
   .ends

endif

.endn
.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Media_Media3D_Matrix3DHelper_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Media_Media3D_Matrix3DHelper_DEFINED
define RuntimeClass_Windows_UI_Xaml_Media_Media3D_Matrix3DHelper <L"Windows.UI.Xaml.Media.Media3D.Matrix3DHelper">
endif

endif
