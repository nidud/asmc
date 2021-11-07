ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __windows2Eglobalization2Efonts_h__
define __windows2Eglobalization2Efonts_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.UI.Text.inc

.namespace Windows
.namespace Globalization
.namespace Fonts

ifndef ____x_ABI_CWindows_CGlobalization_CFonts_CILanguageFontGroup_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CFonts_CILanguageFontGroup_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_Fonts_ILanguageFontGroup <L"Windows.Globalization.Fonts.ILanguageFontGroup">

DEFINE_IIDX(ILanguageFontGroup, "F33A7FC3-3A5C-4AEA-B9FF-B39FB242F7F6")

.comdef ILanguageFontGroup : public IInspectable

    get_UITextFont      proc :ptr
    get_UIHeadingFont   proc :ptr
    get_UITitleFont     proc :ptr
    get_UICaptionFont   proc :ptr
    get_UINotificationHeadingFont proc :ptr
    get_TraditionalDocumentFont proc :ptr
    get_ModernDocumentFont proc :ptr
    get_DocumentHeadingFont proc :ptr
    get_FixedWidthTextFont proc :ptr
    get_DocumentAlternate1Font proc :ptr
    get_DocumentAlternate2Font proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CFonts_CILanguageFontGroupFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CFonts_CILanguageFontGroupFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_Fonts_ILanguageFontGroupFactory <L"Windows.Globalization.Fonts.ILanguageFontGroupFactory">
DEFINE_IIDX(ILanguageFontGroupFactory, "FCAEAC67-4E77-49C7-B856-DDE934FC735B")

.comdef ILanguageFontGroupFactory : public IInspectable

    CreateLanguageFontGroup proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGlobalization_CFonts_CILanguageFont_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGlobalization_CFonts_CILanguageFont_INTERFACE_DEFINED__
define InterfaceName_Windows_Globalization_Fonts_ILanguageFont <L"Windows.Globalization.Fonts.ILanguageFont">
DEFINE_IIDX(ILanguageFont, "B12E5C3A-B76D-459B-BEEB-901151CD77D1")

.comdef ILanguageFont : public IInspectable

    get_FontFamily      proc :ptr
    get_FontWeight      proc :ptr
    get_FontStretch     proc :ptr
    get_FontStyle       proc :ptr
    get_ScaleFactor     proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Globalization_Fonts_LanguageFont_DEFINED
define RUNTIMECLASS_Windows_Globalization_Fonts_LanguageFont_DEFINED
define RuntimeClass_Windows_Globalization_Fonts_LanguageFont <L"Windows.Globalization.Fonts.LanguageFont">
endif
ifndef RUNTIMECLASS_Windows_Globalization_Fonts_LanguageFontGroup_DEFINED
define RUNTIMECLASS_Windows_Globalization_Fonts_LanguageFontGroup_DEFINED
define RuntimeClass_Windows_Globalization_Fonts_LanguageFontGroup <L"Windows.Globalization.Fonts.LanguageFontGroup">
endif

endif
