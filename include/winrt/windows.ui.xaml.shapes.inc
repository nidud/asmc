ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Examl2Eshapes_h__
define __windows2Eui2Examl2Eshapes_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.UI.Xaml.inc

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Shapes

ifndef ____x_ABI_CWindows_CUI_CXaml_CShapes_CIEllipse_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CShapes_CIEllipse_INTERFACE_DEFINED__
DEFINE_IIDX(IEllipse, "70E05AC4-D38D-4BAB-831F-4A22EF52AC86")

.comdef IEllipse : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CShapes_CILine_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CShapes_CILine_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Shapes_ILine <L"Windows.UI.Xaml.Shapes.ILine">
DEFINE_IIDX(ILine, "46A5433D-4FFB-48DF-8732-4E15C834816B")

.comdef ILine : public IInspectable

    get_X1              proc :ptr
    put_X1              proc :DOUBLE
    get_Y1              proc :ptr
    put_Y1              proc :DOUBLE
    get_X2              proc :ptr
    put_X2              proc :DOUBLE
    get_Y2              proc :ptr
    put_Y2              proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CShapes_CILineStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CShapes_CILineStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Shapes_ILineStatics <L"Windows.UI.Xaml.Shapes.ILineStatics">
DEFINE_IIDX(ILineStatics, "267C123D-6EA4-4C50-8B1D-50207AFF1E8A")

.comdef ILineStatics : public IInspectable

    get_X1Property      proc :ptr
    get_Y1Property      proc :ptr
    get_X2Property      proc :ptr
    get_Y2Property      proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CShapes_CIPath_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CShapes_CIPath_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Shapes_IPath <L"Windows.UI.Xaml.Shapes.IPath">
DEFINE_IIDX(IPath, "78883609-3D57-4F3C-B8A5-6CABCAC9711F")

.comdef IPath : public IInspectable

    get_Data            proc :ptr
    put_Data            proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CShapes_CIPathStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CShapes_CIPathStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Shapes_IPathStatics <L"Windows.UI.Xaml.Shapes.IPathStatics">
DEFINE_IIDX(IPathStatics, "F627E59D-87DC-4142-81F1-97FC7FF8641C")

.comdef IPathStatics : public IInspectable

    get_DataProperty    proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CShapes_CIPathFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CShapes_CIPathFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Shapes_IPathFactory <L"Windows.UI.Xaml.Shapes.IPathFactory">
DEFINE_IIDX(IPathFactory, "2340A4E3-5A86-4FC6-9A50-CBB93B828766")

.comdef IPathFactory : public IInspectable

    CreateInstance      proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CShapes_CIPolygon_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CShapes_CIPolygon_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Shapes_IPolygon <L"Windows.UI.Xaml.Shapes.IPolygon">
DEFINE_IIDX(IPolygon, "E3755C19-2E4D-4BCC-8D34-86871957FA01")

.comdef IPolygon : public IInspectable

    get_FillRule        proc :ptr
    put_FillRule        proc :Windows::UI::Xaml::Media::FillRule
    get_Points          proc :ptr
    put_Points          proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CShapes_CIPolygonStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CShapes_CIPolygonStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Shapes_IPolygonStatics <L"Windows.UI.Xaml.Shapes.IPolygonStatics">
DEFINE_IIDX(IPolygonStatics, "362A8AAB-D463-4366-9E1A-BEBA72810FB7")

.comdef IPolygonStatics : public IInspectable

    get_FillRuleProperty proc :ptr
    get_PointsProperty  proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CShapes_CIPolyline_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CShapes_CIPolyline_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Shapes_IPolyline <L"Windows.UI.Xaml.Shapes.IPolyline">
DEFINE_IIDX(IPolyline, "91DC62F8-42B3-47F3-8476-C55124A7C4C6")

.comdef IPolyline : public IInspectable

    get_FillRule        proc :ptr
    put_FillRule        proc :Windows::UI::Xaml::Media::FillRule
    get_Points          proc :ptr
    put_Points          proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CShapes_CIPolylineStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CShapes_CIPolylineStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Shapes_IPolylineStatics <L"Windows.UI.Xaml.Shapes.IPolylineStatics">
DEFINE_IIDX(IPolylineStatics, "C7AA2CD1-A26C-43B0-AAA5-822FA64A11B9")

.comdef IPolylineStatics : public IInspectable

    get_FillRuleProperty proc :ptr
    get_PointsProperty  proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CShapes_CIRectangle_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CShapes_CIRectangle_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Shapes_IRectangle <L"Windows.UI.Xaml.Shapes.IRectangle">
DEFINE_IIDX(IRectangle, "855BC230-8A11-4E18-A136-4BC21C7827B0")

.comdef IRectangle : public IInspectable

    get_RadiusX         proc :ptr
    put_RadiusX         proc :DOUBLE
    get_RadiusY         proc :ptr
    put_RadiusY         proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CShapes_CIRectangleStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CShapes_CIRectangleStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Shapes_IRectangleStatics <L"Windows.UI.Xaml.Shapes.IRectangleStatics">
DEFINE_IIDX(IRectangleStatics, "9F25AA53-BB3A-4C3C-89DB-6FBC0D1FA0CC")

.comdef IRectangleStatics : public IInspectable

    get_RadiusXProperty proc :ptr
    get_RadiusYProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CShapes_CIShape_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CShapes_CIShape_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Shapes_IShape <L"Windows.UI.Xaml.Shapes.IShape">
DEFINE_IIDX(IShape, "786F2B75-9AA0-454D-AE06-A2466E37C832")

.comdef IShape : public IInspectable

    get_Fill            proc :ptr
    put_Fill            proc :ptr
    get_Stroke          proc :ptr
    put_Stroke          proc :ptr
    get_StrokeMiterLimit proc :ptr
    put_StrokeMiterLimit proc :DOUBLE
    get_StrokeThickness proc :ptr
    put_StrokeThickness proc :DOUBLE
    get_StrokeStartLineCap proc :ptr
    put_StrokeStartLineCap proc :Windows::UI::Xaml::Media::PenLineCap
    get_StrokeEndLineCap proc :ptr
    put_StrokeEndLineCap proc :Windows::UI::Xaml::Media::PenLineCap
    get_StrokeLineJoin  proc :ptr
    put_StrokeLineJoin  proc :Windows::UI::Xaml::Media::PenLineJoin
    get_StrokeDashOffset proc :ptr
    put_StrokeDashOffset proc :DOUBLE
    get_StrokeDashCap   proc :ptr
    put_StrokeDashCap   proc :Windows::UI::Xaml::Media::PenLineCap
    get_StrokeDashArray proc :ptr
    put_StrokeDashArray proc :ptr
    get_Stretch         proc :ptr
    put_Stretch         proc :Windows::UI::Xaml::Media::Stretch
    get_GeometryTransform proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CShapes_CIShapeStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CShapes_CIShapeStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Shapes_IShapeStatics <L"Windows.UI.Xaml.Shapes.IShapeStatics">
DEFINE_IIDX(IShapeStatics, "1D7B4C55-9DF3-48DC-9194-9D306FAA6089")

.comdef IShapeStatics : public IInspectable

    get_FillProperty    proc :ptr
    get_StrokeProperty  proc :ptr
    get_StrokeMiterLimitProperty proc :ptr
    get_StrokeThicknessProperty proc :ptr
    get_StrokeStartLineCapProperty proc :ptr
    get_StrokeEndLineCapProperty proc :ptr
    get_StrokeLineJoinProperty proc :ptr
    get_StrokeDashOffsetProperty proc :ptr
    get_StrokeDashCapProperty proc :ptr
    get_StrokeDashArrayProperty proc :ptr
    get_StretchProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CShapes_CIShapeFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CShapes_CIShapeFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Shapes_IShapeFactory <L"Windows.UI.Xaml.Shapes.IShapeFactory">
DEFINE_IIDX(IShapeFactory, "4B717613-F6AA-48D5-9588-E1D188EACBC9")

.comdef IShapeFactory : public IInspectable

    CreateInstance      proc :ptr, :ptr, :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Shapes_Shape_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Shapes_Shape_DEFINED
define RuntimeClass_Windows_UI_Xaml_Shapes_Shape <L"Windows.UI.Xaml.Shapes.Shape">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Shapes_Ellipse_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Shapes_Ellipse_DEFINED
define RuntimeClass_Windows_UI_Xaml_Shapes_Ellipse <L"Windows.UI.Xaml.Shapes.Ellipse">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Shapes_Line_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Shapes_Line_DEFINED
define RuntimeClass_Windows_UI_Xaml_Shapes_Line <L"Windows.UI.Xaml.Shapes.Line">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Shapes_Path_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Shapes_Path_DEFINED
define RuntimeClass_Windows_UI_Xaml_Shapes_Path <L"Windows.UI.Xaml.Shapes.Path">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Shapes_Polygon_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Shapes_Polygon_DEFINED
define RuntimeClass_Windows_UI_Xaml_Shapes_Polygon <L"Windows.UI.Xaml.Shapes.Polygon">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Shapes_Polyline_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Shapes_Polyline_DEFINED
define RuntimeClass_Windows_UI_Xaml_Shapes_Polyline <L"Windows.UI.Xaml.Shapes.Polyline">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Shapes_Rectangle_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Shapes_Rectangle_DEFINED
define RuntimeClass_Windows_UI_Xaml_Shapes_Rectangle <L"Windows.UI.Xaml.Shapes.Rectangle">
endif

endif
