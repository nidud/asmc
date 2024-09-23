.pragma list(push, 0)
ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 475
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

ifndef __wincodec_h__
define __wincodec_h__

include wtypes.inc
include propidl.inc
include ocidl.inc
include DirectX/dxgiformat.inc
include intsafe.inc
include DirectX/dcommon.inc

WINCODEC_SDK_VERSION1	equ 0x0236
WINCODEC_SDK_VERSION2	equ 0x0237
DEFINE_GUID(CLSID_WICImagingFactory1, 0xcacaf262, 0x9370, 0x4615, 0xa1, 0x3b, 0x9f, 0x55, 0x39, 0xda, 0x4c, 0xa);
DEFINE_GUID(CLSID_WICImagingFactory2, 0x317d06e8, 0x5f24, 0x433d, 0xbd, 0xf7, 0x79, 0xce, 0x68, 0xd8, 0xab, 0xc2);
if(_WIN32_WINNT GE _WIN32_WINNT_WIN8) OR defined(_WIN7_PLATFORM_UPDATE)
WINCODEC_SDK_VERSION	equ WINCODEC_SDK_VERSION2
DEFINE_GUID(CLSID_WICImagingFactory, 0x317d06e8, 0x5f24, 0x433d, 0xbd, 0xf7, 0x79, 0xce, 0x68, 0xd8, 0xab, 0xc2);
else
WINCODEC_SDK_VERSION	equ WINCODEC_SDK_VERSION1
DEFINE_GUID(CLSID_WICImagingFactory,  0xcacaf262, 0x9370, 0x4615, 0xa1, 0x3b, 0x9f, 0x55, 0x39, 0xda, 0x4c, 0xa);
endif
DEFINE_GUID(GUID_VendorMicrosoft, 0xf0e749ca, 0xedef, 0x4589, 0xa7, 0x3a, 0xee, 0xe, 0x62, 0x6a, 0x2a, 0x2b);
DEFINE_GUID(GUID_VendorMicrosoftBuiltIn, 0x257a30fd, 0x6b6, 0x462b, 0xae, 0xa4, 0x63, 0xf7, 0xb, 0x86, 0xe5, 0x33);
DEFINE_GUID(CLSID_WICPngDecoder1,  0x389ea17b, 0x5078, 0x4cde, 0xb6, 0xef, 0x25, 0xc1, 0x51, 0x75, 0xc7, 0x51);
DEFINE_GUID(CLSID_WICPngDecoder2,  0xe018945b, 0xaa86, 0x4008, 0x9b, 0xd4, 0x67, 0x77, 0xa1, 0xe4, 0x0c, 0x11);
if(_WIN32_WINNT GE _WIN32_WINNT_WIN8) OR defined(_WIN7_PLATFORM_UPDATE)
DEFINE_GUID(CLSID_WICPngDecoder,  0xe018945b, 0xaa86, 0x4008, 0x9b, 0xd4, 0x67, 0x77, 0xa1, 0xe4, 0x0c, 0x11);
else
DEFINE_GUID(CLSID_WICPngDecoder,   0x389ea17b, 0x5078, 0x4cde, 0xb6, 0xef, 0x25, 0xc1, 0x51, 0x75, 0xc7, 0x51);
endif
DEFINE_GUID(CLSID_WICBmpDecoder,  0x6b462062, 0x7cbf, 0x400d, 0x9f, 0xdb, 0x81, 0x3d, 0xd1, 0x0f, 0x27, 0x78);
DEFINE_GUID(CLSID_WICIcoDecoder,  0xc61bfcdf, 0x2e0f, 0x4aad, 0xa8, 0xd7, 0xe0, 0x6b, 0xaf, 0xeb, 0xcd, 0xfe);
DEFINE_GUID(CLSID_WICJpegDecoder, 0x9456a480, 0xe88b, 0x43ea, 0x9e, 0x73, 0x0b, 0x2d, 0x9b, 0x71, 0xb1, 0xca);
DEFINE_GUID(CLSID_WICGifDecoder,  0x381dda3c, 0x9ce9, 0x4834, 0xa2, 0x3e, 0x1f, 0x98, 0xf8, 0xfc, 0x52, 0xbe);
DEFINE_GUID(CLSID_WICTiffDecoder, 0xb54e85d9, 0xfe23, 0x499f, 0x8b, 0x88, 0x6a, 0xce, 0xa7, 0x13, 0x75, 0x2b);
DEFINE_GUID(CLSID_WICWmpDecoder,  0xa26cec36, 0x234c, 0x4950, 0xae, 0x16, 0xe3, 0x4a, 0xac, 0xe7, 0x1d, 0x0d);
DEFINE_GUID(CLSID_WICDdsDecoder,  0x9053699f, 0xa341, 0x429d, 0x9e, 0x90, 0xee, 0x43, 0x7c, 0xf8, 0x0c, 0x73);
DEFINE_GUID(CLSID_WICBmpEncoder,  0x69be8bb4, 0xd66d, 0x47c8, 0x86, 0x5a, 0xed, 0x15, 0x89, 0x43, 0x37, 0x82);
DEFINE_GUID(CLSID_WICPngEncoder,  0x27949969, 0x876a, 0x41d7, 0x94, 0x47, 0x56, 0x8f, 0x6a, 0x35, 0xa4, 0xdc);
DEFINE_GUID(CLSID_WICJpegEncoder, 0x1a34f5c1, 0x4a5a, 0x46dc, 0xb6, 0x44, 0x1f, 0x45, 0x67, 0xe7, 0xa6, 0x76);
DEFINE_GUID(CLSID_WICGifEncoder,  0x114f5598, 0x0b22, 0x40a0, 0x86, 0xa1, 0xc8, 0x3e, 0xa4, 0x95, 0xad, 0xbd);
DEFINE_GUID(CLSID_WICTiffEncoder, 0x0131be10, 0x2001, 0x4c5f, 0xa9, 0xb0, 0xcc, 0x88, 0xfa, 0xb6, 0x4c, 0xe8);
DEFINE_GUID(CLSID_WICWmpEncoder,  0xac4ce3cb, 0xe1c1, 0x44cd, 0x82, 0x15, 0x5a, 0x16, 0x65, 0x50, 0x9e, 0xc2);
DEFINE_GUID(CLSID_WICDdsEncoder,  0xa61dde94, 0x66ce, 0x4ac1, 0x88, 0x1b, 0x71, 0x68, 0x05, 0x88, 0x89, 0x5e);
DEFINE_GUID(GUID_ContainerFormatBmp,  0x0af1d87e, 0xfcfe, 0x4188, 0xbd, 0xeb, 0xa7, 0x90, 0x64, 0x71, 0xcb, 0xe3);
DEFINE_GUID(GUID_ContainerFormatPng,  0x1b7cfaf4, 0x713f, 0x473c, 0xbb, 0xcd, 0x61, 0x37, 0x42, 0x5f, 0xae, 0xaf);
DEFINE_GUID(GUID_ContainerFormatIco,  0xa3a860c4, 0x338f, 0x4c17, 0x91, 0x9a, 0xfb, 0xa4, 0xb5, 0x62, 0x8f, 0x21);
DEFINE_GUID(GUID_ContainerFormatJpeg, 0x19e4a5aa, 0x5662, 0x4fc5, 0xa0, 0xc0, 0x17, 0x58, 0x02, 0x8e, 0x10, 0x57);
DEFINE_GUID(GUID_ContainerFormatTiff, 0x163bcc30, 0xe2e9, 0x4f0b, 0x96, 0x1d, 0xa3, 0xe9, 0xfd, 0xb7, 0x88, 0xa3);
DEFINE_GUID(GUID_ContainerFormatGif,  0x1f8a5601, 0x7d4d, 0x4cbd, 0x9c, 0x82, 0x1b, 0xc8, 0xd4, 0xee, 0xb9, 0xa5);
DEFINE_GUID(GUID_ContainerFormatWmp,  0x57a37caa, 0x367a, 0x4540, 0x91, 0x6b, 0xf1, 0x83, 0xc5, 0x09, 0x3a, 0x4b);
DEFINE_GUID(GUID_ContainerFormatDds,  0x9967cb95, 0x2e85, 0x4ac8, 0x8c, 0xa2, 0x83, 0xd7, 0xcc, 0xd4, 0x25, 0xc9);
DEFINE_GUID(CLSID_WICImagingCategories, 0xfae3d380, 0xfea4, 0x4623, 0x8c, 0x75, 0xc6, 0xb6, 0x11, 0x10, 0xb6, 0x81);
DEFINE_GUID(CATID_WICBitmapDecoders,	0x7ed96837, 0x96f0, 0x4812, 0xb2, 0x11, 0xf1, 0x3c, 0x24, 0x11, 0x7e, 0xd3);
DEFINE_GUID(CATID_WICBitmapEncoders,	0xac757296, 0x3522, 0x4e11, 0x98, 0x62, 0xc1, 0x7b, 0xe5, 0xa1, 0x76, 0x7e);
DEFINE_GUID(CATID_WICPixelFormats,	0x2b46e70f, 0xcda7, 0x473e, 0x89, 0xf6, 0xdc, 0x96, 0x30, 0xa2, 0x39, 0x0b);
DEFINE_GUID(CATID_WICFormatConverters,	0x7835eae8, 0xbf14, 0x49d1, 0x93, 0xce, 0x53, 0x3a, 0x40, 0x7b, 0x22, 0x48);
DEFINE_GUID(CATID_WICMetadataReader,	0x05af94d8, 0x7174, 0x4cd2, 0xbe, 0x4a, 0x41, 0x24, 0xb8, 0x0e, 0xe4, 0xb8);
DEFINE_GUID(CATID_WICMetadataWriter,	0xabe3b9a4, 0x257d, 0x4b97, 0xbd, 0x1a, 0x29, 0x4a, 0xf4, 0x96, 0x22, 0x2e);
DEFINE_GUID(CLSID_WICDefaultFormatConverter, 0x1a3f11dc, 0xb514, 0x4b17, 0x8c, 0x5f, 0x21, 0x54, 0x51, 0x38, 0x52, 0xf1);
DEFINE_GUID(CLSID_WICFormatConverterHighColor, 0xac75d454, 0x9f37, 0x48f8, 0xb9, 0x72, 0x4e, 0x19, 0xbc, 0x85, 0x60, 0x11);
DEFINE_GUID(CLSID_WICFormatConverterNChannel, 0xc17cabb2, 0xd4a3, 0x47d7, 0xa5, 0x57, 0x33, 0x9b, 0x2e, 0xfb, 0xd4, 0xf1);
DEFINE_GUID(CLSID_WICFormatConverterWMPhoto, 0x9cb5172b, 0xd600, 0x46ba, 0xab, 0x77, 0x77, 0xbb, 0x7e, 0x3a, 0x00, 0xd9);
DEFINE_GUID(CLSID_WICPlanarFormatConverter, 0x184132b8, 0x32f8, 0x4784, 0x91, 0x31, 0xdd, 0x72, 0x24, 0xb2, 0x34, 0x38);

WICColor		typedef UINT32

.template WICRect
    X	   int_t ?
    Y	   int_t ?
    Width  int_t ?
    Height int_t ?
    .inline WICRect :abs, :abs, :abs, :abs, :vararg {
	mov this.X,_1
	mov this.Y,_2
	mov this.Width,_3
	mov this.Height,_4
	}
    .ends

WICInProcPointer	typedef ptr BYTE

.enum WICColorContextType {
    WICColorContextUninitialized	= 0,
    WICColorContextProfile		= 0x1,
    WICColorContextExifColorSpace	= 0x2
    }

REFWICPixelFormatGUID	typedef	 REFGUID
WICPixelFormatGUID	typedef	 GUID

GUID_WICPixelFormatUndefined equ GUID_WICPixelFormatDontCare
DEFINE_GUID(GUID_WICPixelFormatDontCare, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x00);
DEFINE_GUID(GUID_WICPixelFormat1bppIndexed, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x01);
DEFINE_GUID(GUID_WICPixelFormat2bppIndexed, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x02);
DEFINE_GUID(GUID_WICPixelFormat4bppIndexed, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x03);
DEFINE_GUID(GUID_WICPixelFormat8bppIndexed, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x04);
DEFINE_GUID(GUID_WICPixelFormatBlackWhite, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x05);
DEFINE_GUID(GUID_WICPixelFormat2bppGray,   0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x06);
DEFINE_GUID(GUID_WICPixelFormat4bppGray,   0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x07);
DEFINE_GUID(GUID_WICPixelFormat8bppGray,   0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x08);
DEFINE_GUID(GUID_WICPixelFormat8bppAlpha, 0xe6cd0116, 0xeeba, 0x4161, 0xaa, 0x85, 0x27, 0xdd, 0x9f, 0xb3, 0xa8, 0x95);
DEFINE_GUID(GUID_WICPixelFormat16bppBGR555, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x09);
DEFINE_GUID(GUID_WICPixelFormat16bppBGR565, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x0a);
DEFINE_GUID(GUID_WICPixelFormat16bppBGRA5551, 0x05ec7c2b, 0xf1e6, 0x4961, 0xad, 0x46, 0xe1, 0xcc, 0x81, 0x0a, 0x87, 0xd2);
DEFINE_GUID(GUID_WICPixelFormat16bppGray,   0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x0b);
DEFINE_GUID(GUID_WICPixelFormat24bppBGR, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x0c);
DEFINE_GUID(GUID_WICPixelFormat24bppRGB, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x0d);
DEFINE_GUID(GUID_WICPixelFormat32bppBGR,   0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x0e);
DEFINE_GUID(GUID_WICPixelFormat32bppBGRA,  0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x0f);
DEFINE_GUID(GUID_WICPixelFormat32bppPBGRA, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x10);
DEFINE_GUID(GUID_WICPixelFormat32bppGrayFloat,	0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x11);
if (_WIN32_WINNT GE _WIN32_WINNT_WIN8) OR defined(_WIN7_PLATFORM_UPDATE)
DEFINE_GUID(GUID_WICPixelFormat32bppRGB,  0xd98c6b95, 0x3efe, 0x47d6, 0xbb, 0x25, 0xeb, 0x17, 0x48, 0xab, 0x0c, 0xf1);
endif
DEFINE_GUID(GUID_WICPixelFormat32bppRGBA, 0xf5c7ad2d, 0x6a8d, 0x43dd, 0xa7, 0xa8, 0xa2, 0x99, 0x35, 0x26, 0x1a, 0xe9);
DEFINE_GUID(GUID_WICPixelFormat32bppPRGBA, 0x3cc4a650, 0xa527, 0x4d37, 0xa9, 0x16, 0x31, 0x42, 0xc7, 0xeb, 0xed, 0xba);
DEFINE_GUID(GUID_WICPixelFormat48bppRGB, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x15);
DEFINE_GUID(GUID_WICPixelFormat48bppBGR, 0xe605a384, 0xb468, 0x46ce, 0xbb, 0x2e, 0x36, 0xf1, 0x80, 0xe6, 0x43, 0x13);
if (_WIN32_WINNT GE _WIN32_WINNT_WIN8) OR defined(_WIN7_PLATFORM_UPDATE)
DEFINE_GUID(GUID_WICPixelFormat64bppRGB,   0xa1182111, 0x186d, 0x4d42, 0xbc, 0x6a, 0x9c, 0x83, 0x03, 0xa8, 0xdf, 0xf9);
endif
DEFINE_GUID(GUID_WICPixelFormat64bppRGBA,  0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x16);
DEFINE_GUID(GUID_WICPixelFormat64bppBGRA,  0x1562ff7c, 0xd352, 0x46f9, 0x97, 0x9e, 0x42, 0x97, 0x6b, 0x79, 0x22, 0x46);
DEFINE_GUID(GUID_WICPixelFormat64bppPRGBA, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x17);
DEFINE_GUID(GUID_WICPixelFormat64bppPBGRA, 0x8c518e8e, 0xa4ec, 0x468b, 0xae, 0x70, 0xc9, 0xa3, 0x5a, 0x9c, 0x55, 0x30);
DEFINE_GUID(GUID_WICPixelFormat16bppGrayFixedPoint, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x13);
DEFINE_GUID(GUID_WICPixelFormat32bppBGR101010, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x14);
DEFINE_GUID(GUID_WICPixelFormat48bppRGBFixedPoint, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x12);
DEFINE_GUID(GUID_WICPixelFormat48bppBGRFixedPoint, 0x49ca140e, 0xcab6, 0x493b, 0x9d, 0xdf, 0x60, 0x18, 0x7c, 0x37, 0x53, 0x2a);
DEFINE_GUID(GUID_WICPixelFormat96bppRGBFixedPoint, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x18);
if (_WIN32_WINNT GE _WIN32_WINNT_WIN8) OR defined(_WIN7_PLATFORM_UPDATE)
DEFINE_GUID(GUID_WICPixelFormat96bppRGBFloat, 0xe3fed78f, 0xe8db, 0x4acf, 0x84, 0xc1, 0xe9, 0x7f, 0x61, 0x36, 0xb3, 0x27);
endif
DEFINE_GUID(GUID_WICPixelFormat128bppRGBAFloat,	 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x19);
DEFINE_GUID(GUID_WICPixelFormat128bppPRGBAFloat, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x1a);
DEFINE_GUID(GUID_WICPixelFormat128bppRGBFloat,	 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x1b);
DEFINE_GUID(GUID_WICPixelFormat32bppCMYK, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x1c);
DEFINE_GUID(GUID_WICPixelFormat64bppRGBAFixedPoint, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x1d);
DEFINE_GUID(GUID_WICPixelFormat64bppBGRAFixedPoint, 0x356de33c, 0x54d2, 0x4a23, 0xbb, 0x4, 0x9b, 0x7b, 0xf9, 0xb1, 0xd4, 0x2d);
DEFINE_GUID(GUID_WICPixelFormat64bppRGBFixedPoint, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x40);
DEFINE_GUID(GUID_WICPixelFormat128bppRGBAFixedPoint, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x1e);
DEFINE_GUID(GUID_WICPixelFormat128bppRGBFixedPoint, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x41);
DEFINE_GUID(GUID_WICPixelFormat64bppRGBAHalf, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x3a);
if (_WIN32_WINNT GE _WIN32_WINNT_WIN8) OR defined(_WIN7_PLATFORM_UPDATE)
DEFINE_GUID(GUID_WICPixelFormat64bppPRGBAHalf, 0x58ad26c2, 0xc623, 0x4d9d, 0xb3, 0x20, 0x38, 0x7e, 0x49, 0xf8, 0xc4, 0x42);
endif
DEFINE_GUID(GUID_WICPixelFormat64bppRGBHalf, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x42);
DEFINE_GUID(GUID_WICPixelFormat48bppRGBHalf, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x3b);
DEFINE_GUID(GUID_WICPixelFormat32bppRGBE, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x3d);
DEFINE_GUID(GUID_WICPixelFormat16bppGrayHalf, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x3e);
DEFINE_GUID(GUID_WICPixelFormat32bppGrayFixedPoint, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x3f);
DEFINE_GUID(GUID_WICPixelFormat32bppRGBA1010102, 0x25238D72, 0xFCF9, 0x4522, 0xb5, 0x14, 0x55, 0x78, 0xe5, 0xad, 0x55, 0xe0);
DEFINE_GUID(GUID_WICPixelFormat32bppRGBA1010102XR, 0x00DE6B9A, 0xC101, 0x434b, 0xb5, 0x02, 0xd0, 0x16, 0x5e, 0xe1, 0x12, 0x2c);
DEFINE_GUID(GUID_WICPixelFormat64bppCMYK, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x1f);
DEFINE_GUID(GUID_WICPixelFormat24bpp3Channels, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x20);
DEFINE_GUID(GUID_WICPixelFormat32bpp4Channels, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x21);
DEFINE_GUID(GUID_WICPixelFormat40bpp5Channels, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x22);
DEFINE_GUID(GUID_WICPixelFormat48bpp6Channels, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x23);
DEFINE_GUID(GUID_WICPixelFormat56bpp7Channels, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x24);
DEFINE_GUID(GUID_WICPixelFormat64bpp8Channels, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x25);
DEFINE_GUID(GUID_WICPixelFormat48bpp3Channels, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x26);
DEFINE_GUID(GUID_WICPixelFormat64bpp4Channels, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x27);
DEFINE_GUID(GUID_WICPixelFormat80bpp5Channels, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x28);
DEFINE_GUID(GUID_WICPixelFormat96bpp6Channels, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x29);
DEFINE_GUID(GUID_WICPixelFormat112bpp7Channels, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x2a);
DEFINE_GUID(GUID_WICPixelFormat128bpp8Channels, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x2b);
DEFINE_GUID(GUID_WICPixelFormat40bppCMYKAlpha, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x2c);
DEFINE_GUID(GUID_WICPixelFormat80bppCMYKAlpha, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x2d);
DEFINE_GUID(GUID_WICPixelFormat32bpp3ChannelsAlpha, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x2e);
DEFINE_GUID(GUID_WICPixelFormat40bpp4ChannelsAlpha, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x2f);
DEFINE_GUID(GUID_WICPixelFormat48bpp5ChannelsAlpha, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x30);
DEFINE_GUID(GUID_WICPixelFormat56bpp6ChannelsAlpha, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x31);
DEFINE_GUID(GUID_WICPixelFormat64bpp7ChannelsAlpha, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x32);
DEFINE_GUID(GUID_WICPixelFormat72bpp8ChannelsAlpha, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x33);
DEFINE_GUID(GUID_WICPixelFormat64bpp3ChannelsAlpha, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x34);
DEFINE_GUID(GUID_WICPixelFormat80bpp4ChannelsAlpha, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x35);
DEFINE_GUID(GUID_WICPixelFormat96bpp5ChannelsAlpha, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x36);
DEFINE_GUID(GUID_WICPixelFormat112bpp6ChannelsAlpha, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x37);
DEFINE_GUID(GUID_WICPixelFormat128bpp7ChannelsAlpha, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x38);
DEFINE_GUID(GUID_WICPixelFormat144bpp8ChannelsAlpha, 0x6fddc324, 0x4e03, 0x4bfe, 0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x39);
DEFINE_GUID(GUID_WICPixelFormat8bppY,		 0x91B4DB54, 0x2DF9, 0x42F0, 0xB4, 0x49, 0x29, 0x09, 0xBB, 0x3D, 0xF8, 0x8E);
DEFINE_GUID(GUID_WICPixelFormat8bppCb,		 0x1339F224, 0x6BFE, 0x4C3E, 0x93, 0x02, 0xE4, 0xF3, 0xA6, 0xD0, 0xCA, 0x2A);
DEFINE_GUID(GUID_WICPixelFormat8bppCr,		 0xB8145053, 0x2116, 0x49F0, 0x88, 0x35, 0xED, 0x84, 0x4B, 0x20, 0x5C, 0x51);
DEFINE_GUID(GUID_WICPixelFormat16bppCbCr,	 0xFF95BA6E, 0x11E0, 0x4263, 0xBB, 0x45, 0x01, 0x72, 0x1F, 0x34, 0x60, 0xA4);

.enum WICBitmapCreateCacheOption {
    WICBitmapNoCache			= 0,
    WICBitmapCacheOnDemand		= 0x1,
    WICBitmapCacheOnLoad		= 0x2,
    WICBITMAPCREATECACHEOPTION_FORCE_DWORD = 0x7fffffff
    }

.enum WICDecodeOptions {
    WICDecodeMetadataCacheOnDemand	= 0,
    WICDecodeMetadataCacheOnLoad	= 0x1,
    WICMETADATACACHEOPTION_FORCE_DWORD	= 0x7fffffff
    }

.enum WICBitmapEncoderCacheOption {
    WICBitmapEncoderCacheInMemory	= 0,
    WICBitmapEncoderCacheTempFile	= 0x1,
    WICBitmapEncoderNoCache		= 0x2,
    WICBITMAPENCODERCACHEOPTION_FORCE_DWORD = 0x7fffffff
    }

.enum WICComponentType {
    WICDecoder			= 0x1,
    WICEncoder			= 0x2,
    WICPixelFormatConverter	= 0x4,
    WICMetadataReader		= 0x8,
    WICMetadataWriter		= 0x10,
    WICPixelFormat		= 0x20,
    WICAllComponents		= 0x3f,
    WICCOMPONENTTYPE_FORCE_DWORD= 0x7fffffff
    }

.enum WICComponentEnumerateOptions {
    WICComponentEnumerateDefault	= 0,
    WICComponentEnumerateRefresh	= 0x1,
    WICComponentEnumerateDisabled	= 0x80000000,
    WICComponentEnumerateUnsigned	= 0x40000000,
    WICComponentEnumerateBuiltInOnly	= 0x20000000,
    WICCOMPONENTENUMERATEOPTIONS_FORCE_DWORD	= 0x7fffffff
    }

WICBitmapPattern	STRUC
Position		ULARGE_INTEGER <>
Length			ULONG ?
Pattern			LPBYTE ?
Mask			LPBYTE ?
EndOfStream		BOOL ?
WICBitmapPattern	ENDS

.enum WICBitmapInterpolationMode {
    WICBitmapInterpolationModeNearestNeighbor	= 0,
    WICBitmapInterpolationModeLinear	= 0x1,
    WICBitmapInterpolationModeCubic = 0x2,
    WICBitmapInterpolationModeFant	= 0x3,
    WICBITMAPINTERPOLATIONMODE_FORCE_DWORD	= 0x7fffffff
    }

.enum WICBitmapPaletteType {
    WICBitmapPaletteTypeCustom	= 0,
    WICBitmapPaletteTypeMedianCut	= 0x1,
    WICBitmapPaletteTypeFixedBW = 0x2,
    WICBitmapPaletteTypeFixedHalftone8	= 0x3,
    WICBitmapPaletteTypeFixedHalftone27 = 0x4,
    WICBitmapPaletteTypeFixedHalftone64 = 0x5,
    WICBitmapPaletteTypeFixedHalftone125	= 0x6,
    WICBitmapPaletteTypeFixedHalftone216	= 0x7,
    WICBitmapPaletteTypeFixedWebPalette = WICBitmapPaletteTypeFixedHalftone216,
    WICBitmapPaletteTypeFixedHalftone252	= 0x8,
    WICBitmapPaletteTypeFixedHalftone256	= 0x9,
    WICBitmapPaletteTypeFixedGray4	= 0xa,
    WICBitmapPaletteTypeFixedGray16 = 0xb,
    WICBitmapPaletteTypeFixedGray256	= 0xc,
    WICBITMAPPALETTETYPE_FORCE_DWORD	= 0x7fffffff
    }

.enum WICBitmapDitherType {
    WICBitmapDitherTypeNone = 0,
    WICBitmapDitherTypeSolid	= 0,
    WICBitmapDitherTypeOrdered4x4	= 0x1,
    WICBitmapDitherTypeOrdered8x8	= 0x2,
    WICBitmapDitherTypeOrdered16x16 = 0x3,
    WICBitmapDitherTypeSpiral4x4	= 0x4,
    WICBitmapDitherTypeSpiral8x8	= 0x5,
    WICBitmapDitherTypeDualSpiral4x4	= 0x6,
    WICBitmapDitherTypeDualSpiral8x8	= 0x7,
    WICBitmapDitherTypeErrorDiffusion	= 0x8,
    WICBITMAPDITHERTYPE_FORCE_DWORD = 0x7fffffff
    }

.enum WICBitmapAlphaChannelOption {
    WICBitmapUseAlpha	= 0,
    WICBitmapUsePremultipliedAlpha	= 0x1,
    WICBitmapIgnoreAlpha	= 0x2,
    WICBITMAPALPHACHANNELOPTIONS_FORCE_DWORD	= 0x7fffffff
    }

.enum WICBitmapTransformOptions {
    WICBitmapTransformRotate0	= 0,
    WICBitmapTransformRotate90	= 0x1,
    WICBitmapTransformRotate180 = 0x2,
    WICBitmapTransformRotate270 = 0x3,
    WICBitmapTransformFlipHorizontal	= 0x8,
    WICBitmapTransformFlipVertical	= 0x10,
    WICBITMAPTRANSFORMOPTIONS_FORCE_DWORD	= 0x7fffffff
    }

.enum WICBitmapLockFlags {
    WICBitmapLockRead	= 0x1,
    WICBitmapLockWrite	= 0x2,
    WICBITMAPLOCKFLAGS_FORCE_DWORD	= 0x7fffffff
    }

.enum WICBitmapDecoderCapabilities {
    WICBitmapDecoderCapabilitySameEncoder	= 0x1,
    WICBitmapDecoderCapabilityCanDecodeAllImages	= 0x2,
    WICBitmapDecoderCapabilityCanDecodeSomeImages	= 0x4,
    WICBitmapDecoderCapabilityCanEnumerateMetadata	= 0x8,
    WICBitmapDecoderCapabilityCanDecodeThumbnail	= 0x10,
    WICBITMAPDECODERCAPABILITIES_FORCE_DWORD	= 0x7fffffff
    }

.enum WICProgressOperation {
    WICProgressOperationCopyPixels	= 0x1,
    WICProgressOperationWritePixels = 0x2,
    WICProgressOperationAll = 0xffff,
    WICPROGRESSOPERATION_FORCE_DWORD	= 0x7fffffff
    }

.enum WICProgressNotification {
    WICProgressNotificationBegin	= 0x10000,
    WICProgressNotificationEnd	= 0x20000,
    WICProgressNotificationFrequent = 0x40000,
    WICProgressNotificationAll	= 0xffff0000,
    WICPROGRESSNOTIFICATION_FORCE_DWORD = 0x7fffffff
    }

.enum WICComponentSigning {
    WICComponentSigned	= 0x1,
    WICComponentUnsigned	= 0x2,
    WICComponentSafe	= 0x4,
    WICComponentDisabled	= 0x80000000,
    WICCOMPONENTSIGNING_FORCE_DWORD = 0x7fffffff
    }

.enum WICGifLogicalScreenDescriptorProperties {
    WICGifLogicalScreenSignature	= 0x1,
    WICGifLogicalScreenDescriptorWidth	= 0x2,
    WICGifLogicalScreenDescriptorHeight = 0x3,
    WICGifLogicalScreenDescriptorGlobalColorTableFlag	= 0x4,
    WICGifLogicalScreenDescriptorColorResolution	= 0x5,
    WICGifLogicalScreenDescriptorSortFlag	= 0x6,
    WICGifLogicalScreenDescriptorGlobalColorTableSize	= 0x7,
    WICGifLogicalScreenDescriptorBackgroundColorIndex	= 0x8,
    WICGifLogicalScreenDescriptorPixelAspectRatio	= 0x9,
    WICGifLogicalScreenDescriptorProperties_FORCE_DWORD = 0x7fffffff
    }

.enum WICGifImageDescriptorProperties {
    WICGifImageDescriptorLeft	= 0x1,
    WICGifImageDescriptorTop	= 0x2,
    WICGifImageDescriptorWidth	= 0x3,
    WICGifImageDescriptorHeight = 0x4,
    WICGifImageDescriptorLocalColorTableFlag	= 0x5,
    WICGifImageDescriptorInterlaceFlag	= 0x6,
    WICGifImageDescriptorSortFlag	= 0x7,
    WICGifImageDescriptorLocalColorTableSize	= 0x8,
    WICGifImageDescriptorProperties_FORCE_DWORD = 0x7fffffff
    }

.enum WICGifGraphicControlExtensionProperties {
    WICGifGraphicControlExtensionDisposal	= 0x1,
    WICGifGraphicControlExtensionUserInputFlag	= 0x2,
    WICGifGraphicControlExtensionTransparencyFlag	= 0x3,
    WICGifGraphicControlExtensionDelay	= 0x4,
    WICGifGraphicControlExtensionTransparentColorIndex	= 0x5,
    WICGifGraphicControlExtensionProperties_FORCE_DWORD = 0x7fffffff
    }

.enum WICGifApplicationExtensionProperties {
    WICGifApplicationExtensionApplication	= 0x1,
    WICGifApplicationExtensionData	= 0x2,
    WICGifApplicationExtensionProperties_FORCE_DWORD	= 0x7fffffff
    }

.enum WICGifCommentExtensionProperties {
    WICGifCommentExtensionText	= 0x1,
    WICGifCommentExtensionProperties_FORCE_DWORD	= 0x7fffffff
    }

.enum WICJpegCommentProperties {
    WICJpegCommentText	= 0x1,
    WICJpegCommentProperties_FORCE_DWORD	= 0x7fffffff
    }

.enum WICJpegLuminanceProperties {
    WICJpegLuminanceTable	= 0x1,
    WICJpegLuminanceProperties_FORCE_DWORD	= 0x7fffffff
    }

.enum WICJpegChrominanceProperties {
    WICJpegChrominanceTable = 0x1,
    WICJpegChrominanceProperties_FORCE_DWORD	= 0x7fffffff
    }

.enum WIC8BIMIptcProperties {
    WIC8BIMIptcPString	= 0,
    WIC8BIMIptcEmbeddedIPTC = 0x1,
    WIC8BIMIptcProperties_FORCE_DWORD	= 0x7fffffff
    }

.enum WIC8BIMResolutionInfoProperties {
    WIC8BIMResolutionInfoPString	= 0x1,
    WIC8BIMResolutionInfoHResolution	= 0x2,
    WIC8BIMResolutionInfoHResolutionUnit	= 0x3,
    WIC8BIMResolutionInfoWidthUnit	= 0x4,
    WIC8BIMResolutionInfoVResolution	= 0x5,
    WIC8BIMResolutionInfoVResolutionUnit	= 0x6,
    WIC8BIMResolutionInfoHeightUnit = 0x7,
    WIC8BIMResolutionInfoProperties_FORCE_DWORD = 0x7fffffff
    }

.enum WIC8BIMIptcDigestProperties {
    WIC8BIMIptcDigestPString	= 0x1,
    WIC8BIMIptcDigestIptcDigest = 0x2,
    WIC8BIMIptcDigestProperties_FORCE_DWORD = 0x7fffffff
    }

.enum WICPngGamaProperties {
    WICPngGamaGamma = 0x1,
    WICPngGamaProperties_FORCE_DWORD	= 0x7fffffff
    }

.enum WICPngBkgdProperties {
    WICPngBkgdBackgroundColor	= 0x1,
    WICPngBkgdProperties_FORCE_DWORD	= 0x7fffffff
    }

.enum WICPngItxtProperties {
    WICPngItxtKeyword	= 0x1,
    WICPngItxtCompressionFlag	= 0x2,
    WICPngItxtLanguageTag	= 0x3,
    WICPngItxtTranslatedKeyword = 0x4,
    WICPngItxtText	= 0x5,
    WICPngItxtProperties_FORCE_DWORD	= 0x7fffffff
    }

.enum WICPngChrmProperties {
    WICPngChrmWhitePointX	= 0x1,
    WICPngChrmWhitePointY	= 0x2,
    WICPngChrmRedX	= 0x3,
    WICPngChrmRedY	= 0x4,
    WICPngChrmGreenX	= 0x5,
    WICPngChrmGreenY	= 0x6,
    WICPngChrmBlueX = 0x7,
    WICPngChrmBlueY = 0x8,
    WICPngChrmProperties_FORCE_DWORD	= 0x7fffffff
    }

.enum WICPngHistProperties {
    WICPngHistFrequencies	= 0x1,
    WICPngHistProperties_FORCE_DWORD	= 0x7fffffff
    }

.enum WICPngIccpProperties {
    WICPngIccpProfileName	= 0x1,
    WICPngIccpProfileData	= 0x2,
    WICPngIccpProperties_FORCE_DWORD	= 0x7fffffff
    }

.enum WICPngSrgbProperties {
    WICPngSrgbRenderingIntent	= 0x1,
    WICPngSrgbProperties_FORCE_DWORD	= 0x7fffffff
    }

.enum WICPngTimeProperties {
    WICPngTimeYear	= 0x1,
    WICPngTimeMonth = 0x2,
    WICPngTimeDay	= 0x3,
    WICPngTimeHour	= 0x4,
    WICPngTimeMinute	= 0x5,
    WICPngTimeSecond	= 0x6,
    WICPngTimeProperties_FORCE_DWORD	= 0x7fffffff
    }

.enum WICSectionAccessLevel {
    WICSectionAccessLevelRead	= 0x1,
    WICSectionAccessLevelReadWrite	= 0x3,
    WICSectionAccessLevel_FORCE_DWORD	= 0x7fffffff
    }

.enum WICPixelFormatNumericRepresentation {
    WICPixelFormatNumericRepresentationUnspecified	= 0,
    WICPixelFormatNumericRepresentationIndexed	= 0x1,
    WICPixelFormatNumericRepresentationUnsignedInteger	= 0x2,
    WICPixelFormatNumericRepresentationSignedInteger	= 0x3,
    WICPixelFormatNumericRepresentationFixed	= 0x4,
    WICPixelFormatNumericRepresentationFloat	= 0x5,
    WICPixelFormatNumericRepresentation_FORCE_DWORD = 0x7fffffff
    }

.enum WICPlanarOptions {
    WICPlanarOptionsDefault = 0,
    WICPlanarOptionsPreserveSubsampling = 0x1,
    WICPLANAROPTIONS_FORCE_DWORD	= 0x7fffffff
    }

if (_WIN32_WINNT GE _WIN32_WINNT_WIN8) OR defined(_WIN7_PLATFORM_UPDATE)
WICImageParameters	STRUC
pixelFormat		PVOID ?;D2D1_PIXEL_FORMAT <>
DpiX			FLOAT ?
DpiY			FLOAT ?
Top			FLOAT ?
Left			FLOAT ?
PixelWidth		UINT32 ?
PixelHeight		UINT32 ?
WICImageParameters	ENDS

endif
WICBitmapPlaneDescription STRUC
Format			WICPixelFormatGUID <>
Width			UINT ?
Height			UINT ?
WICBitmapPlaneDescription ENDS

WICBitmapPlane		STRUC
Format			WICPixelFormatGUID <>
pbBuffer		LPBYTE ?
cbStride		UINT ?
cbBufferSize		UINT ?
WICBitmapPlane		ENDS

ifndef __IWICPalette_INTERFACE_DEFINED__
define __IWICPalette_INTERFACE_DEFINED__

DEFINE_IIDX(IWICPalette, "00000040-a8f2-4877-ba0a-fd2b6645fb94")

.comdef IWICPalette : public IUnknown

    InitializePredefined proc :WICBitmapPaletteType, :BOOL
    InitializeCustom	proc
    InitializeFromBitmap proc :ptr, :UINT, :BOOL
    InitializeFromPalette proc :ptr
    GetType		proc :ptr
    GetColorCount	proc :ptr
    GetColors		proc :UINT, :ptr WICColor, :ptr UINT
    IsBlackWhite	proc :ptr
    IsGrayscale		proc :ptr
    HasAlpha		proc :ptr
   .ends

endif


ifndef __IWICBitmapSource_INTERFACE_DEFINED__
define __IWICBitmapSource_INTERFACE_DEFINED__

DEFINE_IIDX(IWICBitmapSource, "00000120-a8f2-4877-ba0a-fd2b6645fb94")

.comdef IWICBitmapSource : public IUnknown

    GetSize		proc :ptr, :ptr
    GetPixelFormat	proc :ptr
    GetResolution	proc :ptr, :ptr
    CopyPalette		proc :ptr
    CopyPixels		proc :ptr WICRect, :UINT, :UINT, :ptr byte
   .ends

endif


ifndef __IWICFormatConverter_INTERFACE_DEFINED__
define __IWICFormatConverter_INTERFACE_DEFINED__

DEFINE_IIDX(IWICFormatConverter, "00000301-a8f2-4877-ba0a-fd2b6645fb94")

.comdef IWICFormatConverter : public IWICBitmapSource

    Initialize		proc :ptr, :REFWICPixelFormatGUID, :WICBitmapDitherType, :ptr, :real8, :WICBitmapPaletteType
    CanConvert		proc :REFWICPixelFormatGUID, :REFWICPixelFormatGUID, :ptr
   .ends

endif

ifndef __IWICPlanarFormatConverter_INTERFACE_DEFINED__
define __IWICPlanarFormatConverter_INTERFACE_DEFINED__

DEFINE_IIDX(IWICPlanarFormatConverter, "BEBEE9CB-83B0-4DCC-8132-B0AAA55EAC96")

.comdef IWICPlanarFormatConverter : public IWICBitmapSource

    Initialize		proc :ptr ptr IWICBitmapSource, :UINT, :REFWICPixelFormatGUID, :WICBitmapDitherType, :ptr IWICPalette, :real8, :WICBitmapPaletteType
    CanConvert		proc :ptr WICPixelFormatGUID, :UINT, :REFWICPixelFormatGUID, :ptr BOOL
   .ends

endif

ifndef __IWICBitmapScaler_INTERFACE_DEFINED__
define __IWICBitmapScaler_INTERFACE_DEFINED__

DEFINE_IIDX(IWICBitmapScaler, "00000302-a8f2-4877-ba0a-fd2b6645fb94")

.comdef IWICBitmapScaler : public IWICBitmapSource

    Initialize		proc :ptr, :UINT, :UINT, :WICBitmapInterpolationMode
   .ends

endif

ifndef __IWICBitmapClipper_INTERFACE_DEFINED__
define __IWICBitmapClipper_INTERFACE_DEFINED__

DEFINE_IIDX(IWICBitmapClipper, "E4FBCF03-223D-4e81-9333-D635556DD1B5")

.comdef IWICBitmapClipper : public IWICBitmapSource

    Initialize		proc :ptr, :ptr WICRect
   .ends

endif

ifndef __IWICBitmapFlipRotator_INTERFACE_DEFINED__
define __IWICBitmapFlipRotator_INTERFACE_DEFINED__

DEFINE_IIDX(IWICBitmapFlipRotator, "5009834F-2D6A-41ce-9E1B-17C5AFF7A782")

.comdef IWICBitmapFlipRotator : public IWICBitmapSource

    Initialize		proc :ptr, :WICBitmapTransformOptions
   .ends

endif

ifndef __IWICBitmapLock_INTERFACE_DEFINED__
define __IWICBitmapLock_INTERFACE_DEFINED__

DEFINE_IIDX(IWICBitmapLock, "00000123-a8f2-4877-ba0a-fd2b6645fb94")

.comdef IWICBitmapLock : public IUnknown

    GetSize		proc :ptr, :ptr
    GetStride		proc :ptr
    GetDataPointer	proc :ptr, :ptr
    GetPixelFormat	proc :ptr
   .ends

endif

ifndef __IWICBitmap_INTERFACE_DEFINED__
define __IWICBitmap_INTERFACE_DEFINED__

DEFINE_IIDX(IWICBitmap, "00000121-a8f2-4877-ba0a-fd2b6645fb94")

.comdef IWICBitmap : public IWICBitmapSource

    _Lock		proc :ptr WICRect, :DWORD, :ptr
    SetPalette		proc :ptr
    SetResolution	proc :real8, :real8
   .ends

endif

ifndef __IWICColorContext_INTERFACE_DEFINED__
define __IWICColorContext_INTERFACE_DEFINED__

DEFINE_IIDX(IWICColorContext, "3C613A02-34B2-44ea-9A7C-45AEA9C6FD6D")

.comdef IWICColorContext : public IUnknown

    InitializeFromFilename proc :LPCWSTR
    InitializeFromMemory proc
    InitializeFromExifColorSpace proc :UINT
    GetType		proc :ptr
    GetProfileBytes	proc :UINT
    GetExifColorSpace	proc :ptr
   .ends

endif

ifndef __IWICColorTransform_INTERFACE_DEFINED__
define __IWICColorTransform_INTERFACE_DEFINED__

DEFINE_IIDX(IWICColorTransform, "B66F034F-D0E2-40ab-B436-6DE39E321A94")

.comdef IWICColorTransform : public IWICBitmapSource

    Initialize		proc :ptr, :ptr, :ptr, :REFWICPixelFormatGUID
   .ends

endif

ifndef __IWICFastMetadataEncoder_INTERFACE_DEFINED__
define __IWICFastMetadataEncoder_INTERFACE_DEFINED__

DEFINE_IIDX(IWICFastMetadataEncoder, "B84E2C09-78C9-4AC4-8BD3-524AE1663A2F")

.comdef IWICFastMetadataEncoder : public IUnknown

    Commit		proc
    GetMetadataQueryWriter proc :ptr
   .ends

endif

ifndef __IWICStream_INTERFACE_DEFINED__
define __IWICStream_INTERFACE_DEFINED__

DEFINE_IIDX(IWICStream, "135FF860-22B7-4ddf-B0F6-218F4F299A43")

.comdef IWICStream : public IStream

    InitializeFromIStream proc :ptr IStream
    InitializeFromFilename proc :LPCWSTR, :DWORD
    InitializeFromMemory proc :WICInProcPointer, :DWORD
    InitializeFromIStreamRegion proc :ptr IStream, :ULARGE_INTEGER, :ULARGE_INTEGER
   .ends

endif

ifndef __IWICEnumMetadataItem_INTERFACE_DEFINED__
define __IWICEnumMetadataItem_INTERFACE_DEFINED__

DEFINE_IIDX(IWICEnumMetadataItem, "DC2BB46D-3F07-481E-8625-220C4AEDBB33")

.comdef IWICEnumMetadataItem : public IUnknown

    Next		proc :ULONG, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

ifndef __IWICMetadataQueryReader_INTERFACE_DEFINED__
define __IWICMetadataQueryReader_INTERFACE_DEFINED__

DEFINE_IIDX(IWICMetadataQueryReader, "30989668-E1C9-4597-B395-458EEDB808DF")

.comdef IWICMetadataQueryReader : public IUnknown

    GetContainerFormat	proc :ptr
    GetLocation		proc :UINT
    GetMetadataByName	proc :LPCWSTR, :ptr
    GetEnumerator	proc :ptr
   .ends

endif

ifndef __IWICMetadataQueryWriter_INTERFACE_DEFINED__
define __IWICMetadataQueryWriter_INTERFACE_DEFINED__

DEFINE_IIDX(IWICMetadataQueryWriter, "A721791A-0DEF-4d06-BD91-2118BF1DB10B")

.comdef IWICMetadataQueryWriter : public IWICMetadataQueryReader

    SetMetadataByName	proc :LPCWSTR, :ptr PROPVARIANT
    RemoveMetadataByName proc :LPCWSTR
   .ends

endif

ifndef __IWICBitmapEncoder_INTERFACE_DEFINED__
define __IWICBitmapEncoder_INTERFACE_DEFINED__

DEFINE_IIDX(IWICBitmapEncoder, "00000103-a8f2-4877-ba0a-fd2b6645fb94")

.comdef IWICBitmapEncoder : public IUnknown

    Initialize		proc :ptr, :WICBitmapEncoderCacheOption
    GetContainerFormat	proc :ptr
    GetEncoderInfo	proc :ptr
    SetColorContexts	proc :UINT, :ptr
    SetPalette		proc :ptr
    SetThumbnail	proc :ptr
    SetPreview		proc :ptr
    CreateNewFrame	proc :ptr, :ptr
    Commit		proc
    GetMetadataQueryWriter proc :ptr
   .ends

endif

ifndef __IWICBitmapFrameEncode_INTERFACE_DEFINED__
define __IWICBitmapFrameEncode_INTERFACE_DEFINED__

DEFINE_IIDX(IWICBitmapFrameEncode, "00000105-a8f2-4877-ba0a-fd2b6645fb94")

.comdef IWICBitmapFrameEncode : public IUnknown

    Initialize		proc :ptr
    SetSize		proc :UINT, :UINT
    SetResolution	proc :real8, :real8
    SetPixelFormat	proc :ptr
    SetColorContexts	proc :UINT, :ptr
    SetPalette		proc :ptr
    SetThumbnail	proc :ptr
    WritePixels		proc :UINT, :UINT, :UINT, :ptr
    WriteSource		proc :ptr, :ptr
    Commit		proc
    GetMetadataQueryWriter proc :ptr
   .ends

endif

ifndef __IWICPlanarBitmapFrameEncode_INTERFACE_DEFINED__
define __IWICPlanarBitmapFrameEncode_INTERFACE_DEFINED__

DEFINE_IIDX(IWICPlanarBitmapFrameEncode, "F928B7B8-2221-40C1-B72E-7E82F1974D1A")

.comdef IWICPlanarBitmapFrameEncode : public IUnknown

    WritePixels		proc :UINT
    WriteSource		proc
   .ends

endif

if (_WIN32_WINNT GE _WIN32_WINNT_WIN8) OR defined(_WIN7_PLATFORM_UPDATE)

ifndef __IWICImageEncoder_INTERFACE_DEFINED__
define __IWICImageEncoder_INTERFACE_DEFINED__

DEFINE_IIDX(IWICImageEncoder, "04C75BF8-3CE1-473B-ACC5-3CC4F5E94999")

.comdef IWICImageEncoder : public IUnknown

    WriteFrame		proc :ptr, :ptr, :ptr
    WriteFrameThumbnail proc :ptr, :ptr, :ptr
    WriteThumbnail	proc :ptr, :ptr, :ptr
   .ends

endif
endif

ifndef __IWICBitmapDecoder_INTERFACE_DEFINED__
define __IWICBitmapDecoder_INTERFACE_DEFINED__

DEFINE_IIDX(IWICBitmapDecoder, "9EDDE9E7-8DEE-47ea-99DF-E6FAF2ED44BF")

.comdef IWICBitmapDecoder : public IUnknown

    QueryCapability	proc :ptr, :ptr
    Initialize		proc :ptr, :WICDecodeOptions
    GetContainerFormat	proc :ptr
    GetDecoderInfo	proc :ptr
    CopyPalette		proc :ptr
    GetMetadataQueryReader proc :ptr
    GetPreview		proc :ptr
    GetColorContexts	proc :UINT
    GetThumbnail	proc :ptr
    GetFrameCount	proc :ptr
    GetFrame		proc :UINT, :ptr
   .ends

endif

ifndef __IWICBitmapSourceTransform_INTERFACE_DEFINED__
define __IWICBitmapSourceTransform_INTERFACE_DEFINED__

DEFINE_IIDX(IWICBitmapSourceTransform, "3B16811B-6A43-4ec9-B713-3D5A0C13B940")

.comdef IWICBitmapSourceTransform : public IUnknown

    CopyPixels		proc :ptr WICRect, :UINT, :UINT, :ptr, :WICBitmapTransformOptions, :UINT, :UINT, :ptr
    GetClosestSize	proc :ptr, :ptr
    GetClosestPixelFormat proc :ptr
    DoesSupportTransform proc :WICBitmapTransformOptions, :ptr
   .ends

endif

ifndef __IWICPlanarBitmapSourceTransform_INTERFACE_DEFINED__
define __IWICPlanarBitmapSourceTransform_INTERFACE_DEFINED__

DEFINE_IIDX(IWICPlanarBitmapSourceTransform, "3AFF9CCE-BE95-4303-B927-E7D16FF4A613")

.comdef IWICPlanarBitmapSourceTransform : public IUnknown

    DoesSupportTransform proc :ptr, :ptr, :WICBitmapTransformOptions, :WICPlanarOptions, :ptr, :UINT, :ptr
    CopyPixels		proc :ptr WICRect, :UINT, :UINT, :WICBitmapTransformOptions, :WICPlanarOptions, :ptr WICBitmapPlane, :UINT
   .ends

endif

ifndef __IWICBitmapFrameDecode_INTERFACE_DEFINED__
define __IWICBitmapFrameDecode_INTERFACE_DEFINED__

DEFINE_IIDX(IWICBitmapFrameDecode, "3B16811B-6A43-4ec9-A813-3D930C13B940")

.comdef IWICBitmapFrameDecode : public IWICBitmapSource

    GetMetadataQueryReader proc :ptr
    GetColorContexts	proc :UINT
    GetThumbnail	proc :ptr
   .ends

endif

ifndef __IWICProgressiveLevelControl_INTERFACE_DEFINED__
define __IWICProgressiveLevelControl_INTERFACE_DEFINED__

DEFINE_IIDX(IWICProgressiveLevelControl, "DAAC296F-7AA5-4dbf-8D15-225C5976F891")

.comdef IWICProgressiveLevelControl : public IUnknown

    GetLevelCount	proc :ptr
    GetCurrentLevel	proc :ptr
    SetCurrentLevel	proc :UINT
   .ends

endif

ifndef __IWICProgressCallback_INTERFACE_DEFINED__
define __IWICProgressCallback_INTERFACE_DEFINED__

DEFINE_IIDX(IWICProgressCallback, "4776F9CD-9517-45FA-BF24-E89C5EC5C60C")

.comdef IWICProgressCallback : public IUnknown

    Notify		proc :ULONG, :WICProgressOperation, :real8
   .ends

endif

ifndef __IWICBitmapCodecProgressNotification_INTERFACE_DEFINED__
define __IWICBitmapCodecProgressNotification_INTERFACE_DEFINED__

CALLBACK(PFNProgressNotification, :LPVOID, :ULONG, :WICProgressOperation, :real8)

DEFINE_IIDX(IWICBitmapCodecProgressNotification, "64C1024E-C3CF-4462-8078-88C2B11C46D9")

.comdef IWICBitmapCodecProgressNotification : public IUnknown

    RegisterProgressNotification proc :PFNProgressNotification, :LPVOID, :DWORD
   .ends

endif


ifndef __IWICComponentInfo_INTERFACE_DEFINED__
define __IWICComponentInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IWICComponentInfo, "23BC3F0A-698B-4357-886B-F24D50671334")

.comdef IWICComponentInfo : public IUnknown

    GetComponentType	proc :ptr
    GetCLSID		proc :ptr
    GetSigningStatus	proc :ptr
    GetAuthor		proc :UINT
    GetVendorGUID	proc :ptr
    GetVersion		proc :UINT
    GetSpecVersion	proc :UINT
    GetFriendlyName	proc :UINT
   .ends

endif

ifndef __IWICFormatConverterInfo_INTERFACE_DEFINED__
define __IWICFormatConverterInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IWICFormatConverterInfo, "9F34FB65-13F4-4f15-BC57-3726B5E53D9F")

.comdef IWICFormatConverterInfo : public IWICComponentInfo

    GetPixelFormats	proc :UINT
    CreateInstance	proc :ptr
   .ends

endif

ifndef __IWICBitmapCodecInfo_INTERFACE_DEFINED__
define __IWICBitmapCodecInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IWICBitmapCodecInfo, "E87A44C4-B76E-4c47-8B09-298EB12A2714")

.comdef IWICBitmapCodecInfo : public IWICComponentInfo

    GetContainerFormat	proc :ptr
    GetPixelFormats	proc :UINT
    GetColorManagementVersion proc :UINT
    GetDeviceManufacturer proc :UINT
    GetDeviceModels	proc :UINT
    GetMimeTypes	proc :UINT
    GetFileExtensions	proc :UINT
    DoesSupportAnimation proc :ptr
    DoesSupportChromakey proc :ptr
    DoesSupportLossless proc :ptr
    DoesSupportMultiframe proc :ptr
    MatchesMimeType	proc :LPCWSTR, :ptr
   .ends

endif

ifndef __IWICBitmapEncoderInfo_INTERFACE_DEFINED__
define __IWICBitmapEncoderInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IWICBitmapEncoderInfo, "94C9B4EE-A09F-4f92-8A1E-4A9BCE7E76FB")

.comdef IWICBitmapEncoderInfo : public IWICBitmapCodecInfo

    CreateInstance	proc :ptr
   .ends

endif

ifndef __IWICBitmapDecoderInfo_INTERFACE_DEFINED__
define __IWICBitmapDecoderInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IWICBitmapDecoderInfo, "D8CD007F-D08F-4191-9BFC-236EA7F0E4B5")

.comdef IWICBitmapDecoderInfo : public IWICBitmapCodecInfo

    GetPatterns		proc :UINT, :ptr WICBitmapPattern, :ptr UINT, :ptr UINT
    MatchesPattern	proc :ptr, :ptr
    CreateInstance	proc :ptr
   .ends

endif

ifndef __IWICPixelFormatInfo_INTERFACE_DEFINED__
define __IWICPixelFormatInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IWICPixelFormatInfo, "E8EDA601-3D48-431a-AB44-69059BE88BBE")

.comdef IWICPixelFormatInfo : public IWICComponentInfo

    GetFormatGUID	proc :ptr
    GetColorContext	proc :ptr
    GetBitsPerPixel	proc :ptr
    GetChannelCount	proc :ptr
    GetChannelMask	proc :UINT, :UINT
   .ends

endif

ifndef __IWICPixelFormatInfo2_INTERFACE_DEFINED__
define __IWICPixelFormatInfo2_INTERFACE_DEFINED__

DEFINE_IIDX(IWICPixelFormatInfo2, "A9DB33A2-AF5F-43C7-B679-74F5984B5AA4")

.comdef IWICPixelFormatInfo2 : public IWICPixelFormatInfo

    SupportsTransparency proc :ptr
    GetNumericRepresentation proc :ptr
   .ends

endif

ifndef __IWICImagingFactory_INTERFACE_DEFINED__
define __IWICImagingFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IWICImagingFactory, "ec5ec8a9-c395-4314-9c77-54d7a935ff70")

.comdef IWICImagingFactory : public IUnknown

    CreateDecoderFromFilename proc :LPCWSTR, :ptr, :DWORD, :WICDecodeOptions, :ptr
    CreateDecoderFromStream proc :ptr, :ptr, :WICDecodeOptions, :ptr
    CreateDecoderFromFileHandle proc :ULONG_PTR, :ptr, :WICDecodeOptions, :ptr
    CreateComponentInfo proc :REFCLSID, :ptr
    CreateDecoder	proc :REFGUID, :ptr, :ptr
    CreateEncoder	proc :REFGUID, :ptr, :ptr
    CreatePalette	proc :ptr
    CreateFormatConverter proc :ptr
    CreateBitmapScaler	proc :ptr
    CreateBitmapClipper proc :ptr
    CreateBitmapFlipRotator proc :ptr
    CreateStream	proc :ptr
    CreateColorContext	proc :ptr
    CreateColorTransformer proc :ptr
    CreateBitmap	proc :UINT, :UINT, :REFWICPixelFormatGUID, :WICBitmapCreateCacheOption, :ptr
    CreateBitmapFromSource proc :ptr, :WICBitmapCreateCacheOption, :ptr
    CreateBitmapFromSourceRect proc :ptr, :UINT, :UINT, :UINT, :UINT, :ptr
    CreateBitmapFromMemory proc :UINT, :UINT, :REFWICPixelFormatGUID, :UINT, :UINT
    CreateBitmapFromHBITMAP proc :HBITMAP, :HPALETTE, :WICBitmapAlphaChannelOption, :ptr
    CreateBitmapFromHICON proc :HICON, :ptr
    CreateComponentEnumerator proc :DWORD, :DWORD, :ptr
    CreateFastMetadataEncoderFromDecoder proc :ptr, :ptr
    CreateFastMetadataEncoderFromFrameDecode proc :ptr, :ptr
    CreateQueryWriter	proc :REFGUID, :ptr, :ptr
    CreateQueryWriterFromReader proc :ptr, :ptr, :ptr
   .ends

endif

if (_WIN32_WINNT GE _WIN32_WINNT_WIN8) OR defined(_WIN7_PLATFORM_UPDATE)

ifndef __IWICImagingFactory2_INTERFACE_DEFINED__
define __IWICImagingFactory2_INTERFACE_DEFINED__

DEFINE_IIDX(IWICImagingFactory2, "7B816B45-1996-4476-B132-DE9E247C8AF0")

.comdef IWICImagingFactory2 : public IWICImagingFactory

    CreateImageEncoder	proc :ptr, :ptr
   .ends

endif

endif

WICConvertBitmapSource proto __cdecl :REFWICPixelFormatGUID, :ptr, :ptr
WICCreateBitmapFromSection proto __cdecl :UINT, :UINT, :REFWICPixelFormatGUID, :HANDLE, :UINT, :UINT, :ptr
WICCreateBitmapFromSectionEx proto __cdecl :UINT, :UINT, :REFWICPixelFormatGUID, :HANDLE, :UINT, :UINT, :WICSectionAccessLevel, :ptr
WICMapGuidToShortName proto __cdecl :REFGUID, :UINT, :ptr, :ptr
WICMapShortNameToGuid proto __cdecl :PCWSTR, :ptr
WICMapSchemaToName proto __cdecl :REFGUID, :LPWSTR, :UINT, :ptr, :ptr

FACILITY_WINCODEC_ERR	equ 0x898
WINCODEC_ERR_BASE	equ 0x2000

MAKE_WINCODECHR macro sev, code
	exitm<MAKE_HRESULT(sev, FACILITY_WINCODEC_ERR, (WINCODEC_ERR_BASE + code))>
	endm
MAKE_WINCODECHR_ERR macro code
	exitm<MAKE_WINCODECHR(1, code)>
	endm
WINCODEC_ERR_GENERIC_ERROR equ E_FAIL
WINCODEC_ERR_INVALIDPARAMETER equ E_INVALIDARG
WINCODEC_ERR_OUTOFMEMORY equ E_OUTOFMEMORY
WINCODEC_ERR_NOTIMPLEMENTED equ E_NOTIMPL
WINCODEC_ERR_ABORTED	equ E_ABORT
WINCODEC_ERR_ACCESSDENIED equ E_ACCESSDENIED
WINCODEC_ERR_VALUEOVERFLOW equ <INTSAFE_E_ARITHMETIC_OVERFLOW>

.enum WICTiffCompressionOption {
    WICTiffCompressionDontCare	= 0,
    WICTiffCompressionNone	= 0x1,
    WICTiffCompressionCCITT3	= 0x2,
    WICTiffCompressionCCITT4	= 0x3,
    WICTiffCompressionLZW	= 0x4,
    WICTiffCompressionRLE	= 0x5,
    WICTiffCompressionZIP	= 0x6,
    WICTiffCompressionLZWHDifferencing	= 0x7,
    WICTIFFCOMPRESSIONOPTION_FORCE_DWORD	= 0x7fffffff
    }

.enum WICJpegYCrCbSubsamplingOption {
    WICJpegYCrCbSubsamplingDefault	= 0,
    WICJpegYCrCbSubsampling420	= 0x1,
    WICJpegYCrCbSubsampling422	= 0x2,
    WICJpegYCrCbSubsampling444	= 0x3,
    WICJpegYCrCbSubsampling440	= 0x4,
    WICJPEGYCRCBSUBSAMPLING_FORCE_DWORD = 0x7fffffff
    }

.enum WICPngFilterOption {
    WICPngFilterUnspecified = 0,
    WICPngFilterNone	= 0x1,
    WICPngFilterSub = 0x2,
    WICPngFilterUp	= 0x3,
    WICPngFilterAverage = 0x4,
    WICPngFilterPaeth	= 0x5,
    WICPngFilterAdaptive	= 0x6,
    WICPNGFILTEROPTION_FORCE_DWORD	= 0x7fffffff
    }

.enum WICNamedWhitePoint {
    WICWhitePointDefault	= 0x1,
    WICWhitePointDaylight	= 0x2,
    WICWhitePointCloudy = 0x4,
    WICWhitePointShade	= 0x8,
    WICWhitePointTungsten	= 0x10,
    WICWhitePointFluorescent	= 0x20,
    WICWhitePointFlash	= 0x40,
    WICWhitePointUnderwater = 0x80,
    WICWhitePointCustom = 0x100,
    WICWhitePointAutoWhiteBalance	= 0x200,
    WICWhitePointAsShot = WICWhitePointDefault,
    WICNAMEDWHITEPOINT_FORCE_DWORD	= 0x7fffffff
    }

.enum WICRawCapabilities {
    WICRawCapabilityNotSupported	= 0,
    WICRawCapabilityGetSupported	= 0x1,
    WICRawCapabilityFullySupported	= 0x2,
    WICRAWCAPABILITIES_FORCE_DWORD	= 0x7fffffff
    }

.enum WICRawRotationCapabilities {
    WICRawRotationCapabilityNotSupported	= 0,
    WICRawRotationCapabilityGetSupported	= 0x1,
    WICRawRotationCapabilityNinetyDegreesSupported	= 0x2,
    WICRawRotationCapabilityFullySupported	= 0x3,
    WICRAWROTATIONCAPABILITIES_FORCE_DWORD	= 0x7fffffff
    }

WICRawCapabilitiesInfo	STRUC
cbSize			UINT ?
CodecMajorVersion	UINT ?
CodecMinorVersion	UINT ?
ExposureCompensationSupport WICRawCapabilities ?
ContrastSupport		WICRawCapabilities ?
RGBWhitePointSupport	WICRawCapabilities ?
NamedWhitePointSupport	WICRawCapabilities ?
NamedWhitePointSupportMask UINT ?
KelvinWhitePointSupport WICRawCapabilities ?
GammaSupport		WICRawCapabilities ?
TintSupport		WICRawCapabilities ?
SaturationSupport	WICRawCapabilities ?
SharpnessSupport	WICRawCapabilities ?
NoiseReductionSupport	WICRawCapabilities ?
DestinationColorProfileSupport WICRawCapabilities ?
ToneCurveSupport	WICRawCapabilities ?
RotationSupport		WICRawRotationCapabilities ?
RenderModeSupport	WICRawCapabilities ?
WICRawCapabilitiesInfo	ENDS

.enum WICRawParameterSet {
    WICAsShotParameterSet	= 0x1,
    WICUserAdjustedParameterSet = 0x2,
    WICAutoAdjustedParameterSet = 0x3,
    WICRAWPARAMETERSET_FORCE_DWORD	= 0x7fffffff
    }

.enum WICRawRenderMode {
    WICRawRenderModeDraft	= 0x1,
    WICRawRenderModeNormal	= 0x2,
    WICRawRenderModeBestQuality = 0x3,
    WICRAWRENDERMODE_FORCE_DWORD	= 0x7fffffff
    }


WICRawToneCurvePoint	STRUC
Input			real8 ?
Output			real8 ?
WICRawToneCurvePoint	ENDS

WICRawToneCurve		STRUC
cPoints			UINT ?
aPoints			WICRawToneCurvePoint 1 dup(<>)
WICRawToneCurve		ENDS

WICRawChangeNotification_ExposureCompensation equ 0x00000001
WICRawChangeNotification_NamedWhitePoint equ 0x00000002
WICRawChangeNotification_KelvinWhitePoint equ 0x00000004
WICRawChangeNotification_RGBWhitePoint equ 0x00000008
WICRawChangeNotification_Contrast equ 0x00000010
WICRawChangeNotification_Gamma equ 0x00000020
WICRawChangeNotification_Sharpness equ 0x00000040
WICRawChangeNotification_Saturation equ 0x00000080
WICRawChangeNotification_Tint equ 0x00000100
WICRawChangeNotification_NoiseReduction equ 0x00000200
WICRawChangeNotification_DestinationColorContext equ 0x00000400
WICRawChangeNotification_ToneCurve equ 0x00000800
WICRawChangeNotification_Rotation equ 0x00001000
WICRawChangeNotification_RenderMode equ 0x00002000

ifndef __IWICDevelopRawNotificationCallback_INTERFACE_DEFINED__
define __IWICDevelopRawNotificationCallback_INTERFACE_DEFINED__

DEFINE_IIDX(IWICDevelopRawNotificationCallback, "95c75a6e-3e8c-4ec2-85a8-aebcc551e59b")

.comdef IWICDevelopRawNotificationCallback : public IUnknown

    Notify		proc :UINT
   .ends

endif

ifndef __IWICDevelopRaw_INTERFACE_DEFINED__
define __IWICDevelopRaw_INTERFACE_DEFINED__

DEFINE_IIDX(IWICDevelopRaw, "fbec5e44-f7be-4b65-b7f8-c0c81fef026d")

.comdef IWICDevelopRaw : public IWICBitmapFrameDecode

    QueryRawCapabilitiesInfo proc :ptr WICRawCapabilitiesInfo
    LoadParameterSet	proc :WICRawParameterSet
    GetCurrentParameterSet proc :ptr
    SetExposureCompensation proc :real8
    GetExposureCompensation proc :ptr
    SetWhitePointRGB	proc :UINT, :UINT, :UINT
    GetWhitePointRGB	proc :ptr, :ptr, :ptr
    SetNamedWhitePoint	proc :WICNamedWhitePoint
    GetNamedWhitePoint	proc :ptr
    SetWhitePointKelvin proc :UINT
    GetWhitePointKelvin proc :ptr
    GetKelvinRangeInfo	proc :ptr, :ptr, :ptr
    SetContrast		proc :real8
    GetContrast		proc :ptr
    SetGamma		proc :real8
    GetGamma		proc :ptr
    SetSharpness	proc :real8
    GetSharpness	proc :ptr
    SetSaturation	proc :real8
    GetSaturation	proc :ptr
    SetTint		proc :real8
    GetTint		proc :ptr
    SetNoiseReduction	proc :real8
    GetNoiseReduction	proc :ptr
    SetDestinationColorContext proc :ptr
    SetToneCurve	proc :UINT, :ptr WICRawToneCurve
    GetToneCurve	proc :UINT, :ptr WICRawToneCurve, :ptr UINT
    SetRotation		proc :real8
    GetRotation		proc :ptr
    SetRenderMode	proc :WICRawRenderMode
    GetRenderMode	proc :ptr
    SetNotificationCallback proc :ptr
   .ends

endif

.enum WICDdsDimension {
    WICDdsTexture1D = 0,
    WICDdsTexture2D = 0x1,
    WICDdsTexture3D = 0x2,
    WICDdsTextureCube	= 0x3,
    WICDDSTEXTURE_FORCE_DWORD	= 0x7fffffff
    }

.enum WICDdsAlphaMode {
    WICDdsAlphaModeUnknown	= 0,
    WICDdsAlphaModeStraight = 0x1,
    WICDdsAlphaModePremultiplied	= 0x2,
    WICDdsAlphaModeOpaque	= 0x3,
    WICDdsAlphaModeCustom	= 0x4,
    WICDDSALPHAMODE_FORCE_DWORD = 0x7fffffff
    }

WICDdsParameters	STRUC
Width			UINT ?
Height			UINT ?
Depth			UINT ?
MipLevels		UINT ?
ArraySize		UINT ?
DxgiFormat		DXGI_FORMAT ?
Dimension		WICDdsDimension ?
AlphaMode		WICDdsAlphaMode ?
WICDdsParameters	ENDS

ifndef __IWICDdsDecoder_INTERFACE_DEFINED__
define __IWICDdsDecoder_INTERFACE_DEFINED__

DEFINE_IIDX(IWICDdsDecoder, "409cd537-8532-40cb-9774-e2feb2df4e9c")

.comdef IWICDdsDecoder : public IUnknown

    GetParameters	proc :ptr
    GetFrame		proc :UINT, :UINT, :UINT, :ptr
   .ends

endif

ifndef __IWICDdsEncoder_INTERFACE_DEFINED__
define __IWICDdsEncoder_INTERFACE_DEFINED__

DEFINE_IIDX(IWICDdsEncoder, "5cacdb4c-407e-41b3-b936-d0f010cd6732")

.comdef IWICDdsEncoder : public IUnknown

    SetParameters	proc :ptr
    GetParameters	proc :ptr
    CreateNewFrame	proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

WICDdsFormatInfo	STRUC
DxgiFormat		DXGI_FORMAT ?
BytesPerBlock		UINT ?
BlockWidth		UINT ?
BlockHeight		UINT ?
WICDdsFormatInfo	ENDS

ifndef __IWICDdsFrameDecode_INTERFACE_DEFINED__
define __IWICDdsFrameDecode_INTERFACE_DEFINED__

DEFINE_IIDX(IWICDdsFrameDecode, "3d4c0c61-18a4-41e4-bd80-481a4fc9f464")

.comdef IWICDdsFrameDecode : public IUnknown

    GetSizeInBlocks	proc :ptr, :ptr
    GetFormatInfo	proc :ptr
    CopyBlocks		proc :ptr WICRect, :UINT, :UINT, :ptr byte
   .ends

endif

BSTR_UserSize proto WINAPI :ptr, :dword, :ptr
BSTR_UserMarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserFree proto WINAPI :ptr, :ptr

HBITMAP_UserSize proto WINAPI :ptr, :dword, :ptr
HBITMAP_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HBITMAP_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HBITMAP_UserFree proto WINAPI :ptr, :ptr

HICON_UserSize proto WINAPI :ptr, :dword, :ptr
HICON_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HICON_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HICON_UserFree proto WINAPI :ptr, :ptr

HPALETTE_UserSize proto WINAPI :ptr, :DWORD, :ptr
HPALETTE_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HPALETTE_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HPALETTE_UserFree proto WINAPI :ptr, :ptr

LPSAFEARRAY_UserSize proto WINAPI :ptr, :dword, :ptr
LPSAFEARRAY_UserMarshal proto WINAPI :ptr, :ptr, :ptr
LPSAFEARRAY_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
LPSAFEARRAY_UserFree proto WINAPI :ptr, :ptr

WICInProcPointer_UserSize proto WINAPI :ptr, :DWORD, :ptr
WICInProcPointer_UserMarshal proto WINAPI :ptr, :ptr, :ptr
WICInProcPointer_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
WICInProcPointer_UserFree proto WINAPI :ptr, :ptr

endif
.pragma list(pop)
