ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif

ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __windows2Eui_h__
define __windows2Eui_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include windows.foundation.collections.inc

ifndef ____FIReference_1_Windows__CUI__CColor_INTERFACE_DEFINED__
define ____FIReference_1_Windows__CUI__CColor_INTERFACE_DEFINED__

DEFINE_IIDX(__FIReference_1_Windows__CUI__CColor, "ab8e5d11-b0c1-5a21-95ae-f16bf3a37624")

.comdef __FIReference_1_Windows__CUI__CColor : public IInspectable

    get_Value		proc :ptr
   .ends

endif

.namespace Windows
.namespace UI

.template Color
    A	db ?
    R	db ?
    G	db ?
    B	db ?
   .ends

ifndef ____x_ABI_CWindows_CUI_CIColorHelper_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CIColorHelper_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_IColorHelper <L"Windows.UI.IColorHelper">

DEFINE_IIDX(IColorHelper, "193CFBE7-65C7-4540-AD08-6283BA76879A")

.comdef IColorHelper : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CIColorHelperStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CIColorHelperStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_IColorHelperStatics <L"Windows.UI.IColorHelperStatics">

DEFINE_IIDX(IColorHelperStatics, "8504DBEA-FB6A-4144-A6C2-33499C9284F5")

.comdef IColorHelperStatics : public IInspectable

    FromArgb		proc :BYTE, :BYTE, :BYTE, :BYTE, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CIColors_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CIColors_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_IColors <L"Windows.UI.IColors">

DEFINE_IIDX(IColors, "9B8C9326-4CA6-4CE5-8994-9EFF65CABDCC")

.comdef IColors : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CIColorsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CIColorsStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_IColorsStatics <L"Windows.UI.IColorsStatics">

DEFINE_IIDX(IColorsStatics, "CFF52E04-CCA6-4614-A17E-754910C84A99")

.comdef IColorsStatics : public IInspectable

    get_AliceBlue	proc :ptr
    get_AntiqueWhite	proc :ptr
    get_Aqua		proc :ptr
    get_Aquamarine	proc :ptr
    get_Azure		proc :ptr
    get_Beige		proc :ptr
    get_Bisque		proc :ptr
    get_Black		proc :ptr
    get_BlanchedAlmond	proc :ptr
    get_Blue		proc :ptr
    get_BlueViolet	proc :ptr
    get_Brown		proc :ptr
    get_BurlyWood	proc :ptr
    get_CadetBlue	proc :ptr
    get_Chartreuse	proc :ptr
    get_Chocolate	proc :ptr
    get_Coral		proc :ptr
    get_CornflowerBlue	proc :ptr
    get_Cornsilk	proc :ptr
    get_Crimson		proc :ptr
    get_Cyan		proc :ptr
    get_DarkBlue	proc :ptr
    get_DarkCyan	proc :ptr
    get_DarkGoldenrod	proc :ptr
    get_DarkGray	proc :ptr
    get_DarkGreen	proc :ptr
    get_DarkKhaki	proc :ptr
    get_DarkMagenta	proc :ptr
    get_DarkOliveGreen	proc :ptr
    get_DarkOrange	proc :ptr
    get_DarkOrchid	proc :ptr
    get_DarkRed		proc :ptr
    get_DarkSalmon	proc :ptr
    get_DarkSeaGreen	proc :ptr
    get_DarkSlateBlue	proc :ptr
    get_DarkSlateGray	proc :ptr
    get_DarkTurquoise	proc :ptr
    get_DarkViolet	proc :ptr
    get_DeepPink	proc :ptr
    get_DeepSkyBlue	proc :ptr
    get_DimGray		proc :ptr
    get_DodgerBlue	proc :ptr
    get_Firebrick	proc :ptr
    get_FloralWhite	proc :ptr
    get_ForestGreen	proc :ptr
    get_Fuchsia		proc :ptr
    get_Gainsboro	proc :ptr
    get_GhostWhite	proc :ptr
    get_Gold		proc :ptr
    get_Goldenrod	proc :ptr
    get_Gray		proc :ptr
    get_Green		proc :ptr
    get_GreenYellow	proc :ptr
    get_Honeydew	proc :ptr
    get_HotPink		proc :ptr
    get_IndianRed	proc :ptr
    get_Indigo		proc :ptr
    get_Ivory		proc :ptr
    get_Khaki		proc :ptr
    get_Lavender	proc :ptr
    get_LavenderBlush	proc :ptr
    get_LawnGreen	proc :ptr
    get_LemonChiffon	proc :ptr
    get_LightBlue	proc :ptr
    get_LightCoral	proc :ptr
    get_LightCyan	proc :ptr
    get_LightGoldenrodYellow proc :ptr
    get_LightGreen	proc :ptr
    get_LightGray	proc :ptr
    get_LightPink	proc :ptr
    get_LightSalmon	proc :ptr
    get_LightSeaGreen	proc :ptr
    get_LightSkyBlue	proc :ptr
    get_LightSlateGray	proc :ptr
    get_LightSteelBlue	proc :ptr
    get_LightYellow	proc :ptr
    get_Lime		proc :ptr
    get_LimeGreen	proc :ptr
    get_Linen		proc :ptr
    get_Magenta		proc :ptr
    get_Maroon		proc :ptr
    get_MediumAquamarine proc :ptr
    get_MediumBlue	proc :ptr
    get_MediumOrchid	proc :ptr
    get_MediumPurple	proc :ptr
    get_MediumSeaGreen	proc :ptr
    get_MediumSlateBlue proc :ptr
    get_MediumSpringGreen proc :ptr
    get_MediumTurquoise proc :ptr
    get_MediumVioletRed proc :ptr
    get_MidnightBlue	proc :ptr
    get_MintCream	proc :ptr
    get_MistyRose	proc :ptr
    get_Moccasin	proc :ptr
    get_NavajoWhite	proc :ptr
    get_Navy		proc :ptr
    get_OldLace		proc :ptr
    get_Olive		proc :ptr
    get_OliveDrab	proc :ptr
    get_Orange		proc :ptr
    get_OrangeRed	proc :ptr
    get_Orchid		proc :ptr
    get_PaleGoldenrod	proc :ptr
    get_PaleGreen	proc :ptr
    get_PaleTurquoise	proc :ptr
    get_PaleVioletRed	proc :ptr
    get_PapayaWhip	proc :ptr
    get_PeachPuff	proc :ptr
    get_Peru		proc :ptr
    get_Pink		proc :ptr
    get_Plum		proc :ptr
    get_PowderBlue	proc :ptr
    get_Purple		proc :ptr
    get_Red		proc :ptr
    get_RosyBrown	proc :ptr
    get_RoyalBlue	proc :ptr
    get_SaddleBrown	proc :ptr
    get_Salmon		proc :ptr
    get_SandyBrown	proc :ptr
    get_SeaGreen	proc :ptr
    get_SeaShell	proc :ptr
    get_Sienna		proc :ptr
    get_Silver		proc :ptr
    get_SkyBlue		proc :ptr
    get_SlateBlue	proc :ptr
    get_SlateGray	proc :ptr
    get_Snow		proc :ptr
    get_SpringGreen	proc :ptr
    get_SteelBlue	proc :ptr
    get_Tan		proc :ptr
    get_Teal		proc :ptr
    get_Thistle		proc :ptr
    get_Tomato		proc :ptr
    get_Transparent	proc :ptr
    get_Turquoise	proc :ptr
    get_Violet		proc :ptr
    get_Wheat		proc :ptr
    get_White		proc :ptr
    get_WhiteSmoke	proc :ptr
    get_Yellow		proc :ptr
    get_YellowGreen	proc :ptr
   .ends

endif

.endn
.endn

define RuntimeClass_Windows_UI_ColorHelper <L"Windows.UI.ColorHelper">
define RuntimeClass_Windows_UI_Colors <L"Windows.UI.Colors">

endif
