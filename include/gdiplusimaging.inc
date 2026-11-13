ifndef _GDIPLUSIMAGING_H
define _GDIPLUSIMAGING_H

DEFINE_GUIDS(ImageFormatUndefined,	"b96b3ca9-0728-11d3-9d7b-0000f81ef32e")
DEFINE_GUIDS(ImageFormatMemoryBMP,	"b96b3caa-0728-11d3-9d7b-0000f81ef32e")
DEFINE_GUIDS(ImageFormatBMP,		"b96b3cab-0728-11d3-9d7b-0000f81ef32e")
DEFINE_GUIDS(ImageFormatEMF,		"b96b3cac-0728-11d3-9d7b-0000f81ef32e")
DEFINE_GUIDS(ImageFormatWMF,		"b96b3cad-0728-11d3-9d7b-0000f81ef32e")
DEFINE_GUIDS(ImageFormatJPEG,		"b96b3cae-0728-11d3-9d7b-0000f81ef32e")
DEFINE_GUIDS(ImageFormatPNG,		"b96b3caf-0728-11d3-9d7b-0000f81ef32e")
DEFINE_GUIDS(ImageFormatGIF,		"b96b3cb0-0728-11d3-9d7b-0000f81ef32e")
DEFINE_GUIDS(ImageFormatTIFF,		"b96b3cb1-0728-11d3-9d7b-0000f81ef32e")
DEFINE_GUIDS(ImageFormatEXIF,		"b96b3cb2-0728-11d3-9d7b-0000f81ef32e")
DEFINE_GUIDS(ImageFormatIcon,		"b96b3cb5-0728-11d3-9d7b-0000f81ef32e")

DEFINE_GUIDS(FrameDimensionTime,	"6aedbd6d-3fb5-418a-83a6-7f45229dc872")
DEFINE_GUIDS(FrameDimensionResolution,	"84236f7b-3bd3-428f-8dab-4ea1439ca315")
DEFINE_GUIDS(FrameDimensionPage,	"7462dc86-6180-4c7e-8e3f-ee7333a7a483")

DEFINE_GUIDS(FormatIDImageInformation,	"e5836cbe-5eef-4f1d-acde-ae4c43b608ce")
DEFINE_GUIDS(FormatIDJpegAppHeaders,	"1c4afdcd-6177-43cf-abc7-5f51af39ee85")

DEFINE_GUIDS(EncoderCompression,	"e09d739d-ccd4-44ee-8eba-3fbf8be4fc58")
DEFINE_GUIDS(EncoderColorDepth,		"66087055-ad66-4c7c-9a18-38a2310b8337")
DEFINE_GUIDS(EncoderScanMethod,		"3a4e2661-3109-4e56-8536-42c156e7dcfa")
DEFINE_GUIDS(EncoderVersion,		"24d18c76-814a-41a4-bf53-1c219cccf797")
DEFINE_GUIDS(EncoderRenderMethod,	"6d42c53a-229a-4825-8bb7-5c99e2b9a8b8")
DEFINE_GUIDS(EncoderQuality,		"1d5be4b5-fa4a-452d-9cdd-5db35105e7eb")
DEFINE_GUIDS(EncoderTransformation,	"8d0eb2d1-a58e-4ea8-aa14-108074b7b6f9")
DEFINE_GUIDS(EncoderLuminanceTable,	"edb33bce-0266-4a77-b904-27216099e717")
DEFINE_GUIDS(EncoderChrominanceTable,	"f2e455dc-09b3-4316-8260-676ada32481c")
DEFINE_GUIDS(EncoderSaveFlag,		"292266fc-ac40-47bf-8cfc-a85b89a655de")

if (GDIPVER GE 0x0110)
DEFINE_GUIDS(EncoderColorSpace,		"ae7a62a0-ee2c-49d8-9d07-1ba8a927596e")
DEFINE_GUIDS(EncoderImageItems,		"63875e13-1f1d-45ab-9195-a29b6066a650")
DEFINE_GUIDS(EncoderSaveAsCMYK,		"a219bbc9-0a9d-4005-a3ee-3a421b8bb06c")
endif
DEFINE_GUIDS(CodecIImageBytes,		"025D1823-6C7D-447B-BBDB-A3CBC3DFA2FC")

.comdef IImageBytes : public IUnknown

    CountBytes	proc :ptr
    LockBytes	proc :UINT, :ULONG, :ptr
    UnlockBytes proc :ptr, :UINT, :ULONG
   .ends

ImageCodecInfo		STRUC
    Clsid		CLSID <>
    FormatID		GUID <>
    CodecName		LPWSTR ?
    DllName		LPWSTR ?
    FormatDescription	LPWSTR ?
    FilenameExtension	LPWSTR ?
    MimeType		LPWSTR ?
    Flags		dd ?
    Version		dd ?
    SigCount		dd ?
    SigSize		dd ?
    SigPattern		LPSTR ?
    SigMask		LPSTR ?
ImageCodecInfo		ENDS

.enum ImageCodecFlags {
    ImageCodecFlagsEncoder	      = 0x00000001,
    ImageCodecFlagsDecoder	      = 0x00000002,
    ImageCodecFlagsSupportBitmap      = 0x00000004,
    ImageCodecFlagsSupportVector      = 0x00000008,
    ImageCodecFlagsSeekableEncode     = 0x00000010,
    ImageCodecFlagsBlockingDecode     = 0x00000020,
    ImageCodecFlagsBuiltin	      = 0x00010000,
    ImageCodecFlagsSystem	      = 0x00020000,
    ImageCodecFlagsUser		      = 0x00040000
    }

.enum ImageLockMode {
    ImageLockModeRead	     = 0x0001,
    ImageLockModeWrite	     = 0x0002,
    ImageLockModeUserInputBuf= 0x0004
    }

.template BitmapData
    Width		UINT ?
    Height		UINT ?
    Stride		SINT ?
    PixelFormat		PixelFormat ?
    Scan0		PVOID ?
    Reserved		UINT_PTR ?
   .ends

.enum ImageFlags {
    ImageFlagsNone		  = 0,

    ;; Low-word: shared with SINKFLAG_x

    ImageFlagsScalable		  = 0x0001,
    ImageFlagsHasAlpha		  = 0x0002,
    ImageFlagsHasTranslucent	  = 0x0004,
    ImageFlagsPartiallyScalable	  = 0x0008,

    ;; Low-word: color space definition

    ImageFlagsColorSpaceRGB	  = 0x0010,
    ImageFlagsColorSpaceCMYK	  = 0x0020,
    ImageFlagsColorSpaceGRAY	  = 0x0040,
    ImageFlagsColorSpaceYCBCR	  = 0x0080,
    ImageFlagsColorSpaceYCCK	  = 0x0100,

    ;; Low-word: image size info

    ImageFlagsHasRealDPI	  = 0x1000,
    ImageFlagsHasRealPixelSize	  = 0x2000,

    ;; High-word

    ImageFlagsReadOnly		  = 0x00010000,
    ImageFlagsCaching		  = 0x00020000
    }

.enum RotateFlipType {
    RotateNoneFlipNone = 0,
    Rotate90FlipNone   = 1,
    Rotate180FlipNone  = 2,
    Rotate270FlipNone  = 3,

    RotateNoneFlipX    = 4,
    Rotate90FlipX      = 5,
    Rotate180FlipX     = 6,
    Rotate270FlipX     = 7,

    RotateNoneFlipY    = Rotate180FlipX,
    Rotate90FlipY      = Rotate270FlipX,
    Rotate180FlipY     = RotateNoneFlipX,
    Rotate270FlipY     = Rotate90FlipX,

    RotateNoneFlipXY   = Rotate180FlipNone,
    Rotate90FlipXY     = Rotate270FlipNone,
    Rotate180FlipXY    = RotateNoneFlipNone,
    Rotate270FlipXY    = Rotate90FlipNone
    }


.template EncoderParameter
    Guid		GUID <>
    NumberOfValues	ULONG ?
    Type		ULONG ?
    Value		PVOID ?
   .ends

.template EncoderParameters
    Count		UINT ?
    Parameter		EncoderParameter <>
   .ends

if (GDIPVER GE 0x0110)
.enum ItemDataPosition {
    ItemDataPositionAfterHeader	   = 0x0,
    ItemDataPositionAfterPalette   = 0x1,
    ItemDataPositionAfterBits	   = 0x2,
    }

.template ImageItemData
    Size		UINT ?
    Position		UINT ?
    Desc		PVOID ?
    DescSize		UINT ?
    Data		PVOID ?
    DataSize		UINT ?
    Cookie		UINT ?
   .ends
endif

PROPID	typedef ULONG

.template PropertyItem
    id			PROPID ?
    length		ULONG ?
    type		dw ?
    value		PVOID ?
   .ends

PropertyTagTypeByte		equ 1
PropertyTagTypeASCII		equ 2
PropertyTagTypeShort		equ 3
PropertyTagTypeLong		equ 4
PropertyTagTypeRational		equ 5
PropertyTagTypeUndefined	equ 7
PropertyTagTypeSLONG		equ 9
PropertyTagTypeSRational	equ 10

PropertyTagExifIFD		equ 0x8769
PropertyTagGpsIFD		equ 0x8825

PropertyTagNewSubfileType	equ 0x00FE
PropertyTagSubfileType		equ 0x00FF
PropertyTagImageWidth		equ 0x0100
PropertyTagImageHeight		equ 0x0101
PropertyTagBitsPerSample	equ 0x0102
PropertyTagCompression		equ 0x0103
PropertyTagPhotometricInterp	equ 0x0106
PropertyTagThreshHolding	equ 0x0107
PropertyTagCellWidth		equ 0x0108
PropertyTagCellHeight		equ 0x0109
PropertyTagFillOrder		equ 0x010A
PropertyTagDocumentName		equ 0x010D
PropertyTagImageDescription	equ 0x010E
PropertyTagEquipMake		equ 0x010F
PropertyTagEquipModel		equ 0x0110
PropertyTagStripOffsets		equ 0x0111
PropertyTagOrientation		equ 0x0112
PropertyTagSamplesPerPixel	equ 0x0115
PropertyTagRowsPerStrip		equ 0x0116
PropertyTagStripBytesCount	equ 0x0117
PropertyTagMinSampleValue	equ 0x0118
PropertyTagMaxSampleValue	equ 0x0119
PropertyTagXResolution		equ 0x011A
PropertyTagYResolution		equ 0x011B
PropertyTagPlanarConfig		equ 0x011C
PropertyTagPageName		equ 0x011D
PropertyTagXPosition		equ 0x011E
PropertyTagYPosition		equ 0x011F
PropertyTagFreeOffset		equ 0x0120
PropertyTagFreeByteCounts	equ 0x0121
PropertyTagGrayResponseUnit	equ 0x0122
PropertyTagGrayResponseCurve	equ 0x0123
PropertyTagT4Option		equ 0x0124
PropertyTagT6Option		equ 0x0125
PropertyTagResolutionUnit	equ 0x0128
PropertyTagPageNumber		equ 0x0129
PropertyTagTransferFuncition	equ 0x012D
PropertyTagSoftwareUsed		equ 0x0131
PropertyTagDateTime		equ 0x0132
PropertyTagArtist		equ 0x013B
PropertyTagHostComputer		equ 0x013C
PropertyTagPredictor		equ 0x013D
PropertyTagWhitePoint		equ 0x013E
PropertyTagPrimaryChromaticities equ 0x013F
PropertyTagColorMap		equ 0x0140
PropertyTagHalftoneHints	equ 0x0141
PropertyTagTileWidth		equ 0x0142
PropertyTagTileLength		equ 0x0143
PropertyTagTileOffset		equ 0x0144
PropertyTagTileByteCounts	equ 0x0145
PropertyTagInkSet		equ 0x014C
PropertyTagInkNames		equ 0x014D
PropertyTagNumberOfInks		equ 0x014E
PropertyTagDotRange		equ 0x0150
PropertyTagTargetPrinter	equ 0x0151
PropertyTagExtraSamples		equ 0x0152
PropertyTagSampleFormat		equ 0x0153
PropertyTagSMinSampleValue	equ 0x0154
PropertyTagSMaxSampleValue	equ 0x0155
PropertyTagTransferRange	equ 0x0156

PropertyTagJPEGProc		equ 0x0200
PropertyTagJPEGInterFormat	equ 0x0201
PropertyTagJPEGInterLength	equ 0x0202
PropertyTagJPEGRestartInterval	equ 0x0203
PropertyTagJPEGLosslessPredictors equ 0x0205
PropertyTagJPEGPointTransforms	equ 0x0206
PropertyTagJPEGQTables		equ 0x0207
PropertyTagJPEGDCTables		equ 0x0208
PropertyTagJPEGACTables		equ 0x0209

PropertyTagYCbCrCoefficients	equ 0x0211
PropertyTagYCbCrSubsampling	equ 0x0212
PropertyTagYCbCrPositioning	equ 0x0213
PropertyTagREFBlackWhite	equ 0x0214

PropertyTagICCProfile		equ 0x8773
PropertyTagGamma		equ 0x0301
PropertyTagICCProfileDescriptor equ 0x0302
PropertyTagSRGBRenderingIntent	equ 0x0303

PropertyTagImageTitle		equ 0x0320
PropertyTagCopyright		equ 0x8298

PropertyTagResolutionXUnit		equ 0x5001
PropertyTagResolutionYUnit		equ 0x5002
PropertyTagResolutionXLengthUnit	equ 0x5003
PropertyTagResolutionYLengthUnit	equ 0x5004
PropertyTagPrintFlags			equ 0x5005
PropertyTagPrintFlagsVersion		equ 0x5006
PropertyTagPrintFlagsCrop		equ 0x5007
PropertyTagPrintFlagsBleedWidth		equ 0x5008
PropertyTagPrintFlagsBleedWidthScale	equ 0x5009
PropertyTagHalftoneLPI			equ 0x500A
PropertyTagHalftoneLPIUnit		equ 0x500B
PropertyTagHalftoneDegree		equ 0x500C
PropertyTagHalftoneShape		equ 0x500D
PropertyTagHalftoneMisc			equ 0x500E
PropertyTagHalftoneScreen		equ 0x500F
PropertyTagJPEGQuality			equ 0x5010
PropertyTagGridSize			equ 0x5011
PropertyTagThumbnailFormat		equ 0x5012
PropertyTagThumbnailWidth		equ 0x5013
PropertyTagThumbnailHeight		equ 0x5014
PropertyTagThumbnailColorDepth		equ 0x5015
PropertyTagThumbnailPlanes		equ 0x5016
PropertyTagThumbnailRawBytes		equ 0x5017
PropertyTagThumbnailSize		equ 0x5018
PropertyTagThumbnailCompressedSize	equ 0x5019
PropertyTagColorTransferFunction	equ 0x501A
PropertyTagThumbnailData		equ 0x501B

PropertyTagThumbnailImageWidth		equ 0x5020
PropertyTagThumbnailImageHeight		equ 0x5021
PropertyTagThumbnailBitsPerSample	equ 0x5022
PropertyTagThumbnailCompression		equ 0x5023
PropertyTagThumbnailPhotometricInterp	equ 0x5024
PropertyTagThumbnailImageDescription	equ 0x5025
PropertyTagThumbnailEquipMake		equ 0x5026
PropertyTagThumbnailEquipModel		equ 0x5027
PropertyTagThumbnailStripOffsets	equ 0x5028
PropertyTagThumbnailOrientation		equ 0x5029
PropertyTagThumbnailSamplesPerPixel	equ 0x502A
PropertyTagThumbnailRowsPerStrip	equ 0x502B
PropertyTagThumbnailStripBytesCount	equ 0x502C
PropertyTagThumbnailResolutionX		equ 0x502D
PropertyTagThumbnailResolutionY		equ 0x502E
PropertyTagThumbnailPlanarConfig	equ 0x502F
PropertyTagThumbnailResolutionUnit	equ 0x5030
PropertyTagThumbnailTransferFunction	equ 0x5031
PropertyTagThumbnailSoftwareUsed	equ 0x5032
PropertyTagThumbnailDateTime		equ 0x5033
PropertyTagThumbnailArtist		equ 0x5034
PropertyTagThumbnailWhitePoint		equ 0x5035
PropertyTagThumbnailPrimaryChromaticities equ 0x5036
PropertyTagThumbnailYCbCrCoefficients	equ 0x5037
PropertyTagThumbnailYCbCrSubsampling	equ 0x5038
PropertyTagThumbnailYCbCrPositioning	equ 0x5039
PropertyTagThumbnailRefBlackWhite	equ 0x503A
PropertyTagThumbnailCopyRight		equ 0x503B

PropertyTagLuminanceTable	equ 0x5090
PropertyTagChrominanceTable	equ 0x5091

PropertyTagFrameDelay		equ 0x5100
PropertyTagLoopCount		equ 0x5101

if (GDIPVER GE 0x0110)
PropertyTagGlobalPalette	equ 0x5102
PropertyTagIndexBackground	equ 0x5103
PropertyTagIndexTransparent	equ 0x5104
endif

PropertyTagPixelUnit		equ 0x5110
PropertyTagPixelPerUnitX	equ 0x5111
PropertyTagPixelPerUnitY	equ 0x5112
PropertyTagPaletteHistogram	equ 0x5113

PropertyTagExifExposureTime	equ 0x829A
PropertyTagExifFNumber		equ 0x829D

PropertyTagExifExposureProg	equ 0x8822
PropertyTagExifSpectralSense	equ 0x8824
PropertyTagExifISOSpeed		equ 0x8827
PropertyTagExifOECF		equ 0x8828

PropertyTagExifVer		equ 0x9000
PropertyTagExifDTOrig		equ 0x9003
PropertyTagExifDTDigitized	equ 0x9004

PropertyTagExifCompConfig	equ 0x9101
PropertyTagExifCompBPP		equ 0x9102

PropertyTagExifShutterSpeed	equ 0x9201
PropertyTagExifAperture		equ 0x9202
PropertyTagExifBrightness	equ 0x9203
PropertyTagExifExposureBias	equ 0x9204
PropertyTagExifMaxAperture	equ 0x9205
PropertyTagExifSubjectDist	equ 0x9206
PropertyTagExifMeteringMode	equ 0x9207
PropertyTagExifLightSource	equ 0x9208
PropertyTagExifFlash		equ 0x9209
PropertyTagExifFocalLength	equ 0x920A
PropertyTagExifSubjectArea	equ 0x9214
PropertyTagExifMakerNote	equ 0x927C
PropertyTagExifUserComment	equ 0x9286
PropertyTagExifDTSubsec		equ 0x9290
PropertyTagExifDTOrigSS		equ 0x9291
PropertyTagExifDTDigSS		equ 0x9292

PropertyTagExifFPXVer		equ 0xA000
PropertyTagExifColorSpace	equ 0xA001
PropertyTagExifPixXDim		equ 0xA002
PropertyTagExifPixYDim		equ 0xA003
PropertyTagExifRelatedWav	equ 0xA004
PropertyTagExifInterop		equ 0xA005
PropertyTagExifFlashEnergy	equ 0xA20B
PropertyTagExifSpatialFR	equ 0xA20C
PropertyTagExifFocalXRes	equ 0xA20E
PropertyTagExifFocalYRes	equ 0xA20F
PropertyTagExifFocalResUnit	equ 0xA210
PropertyTagExifSubjectLoc	equ 0xA214
PropertyTagExifExposureIndex	equ 0xA215
PropertyTagExifSensingMethod	equ 0xA217
PropertyTagExifFileSource	equ 0xA300
PropertyTagExifSceneType	equ 0xA301
PropertyTagExifCfaPattern	equ 0xA302

PropertyTagExifCustomRendered		equ 0xA401
PropertyTagExifExposureMode		equ 0xA402
PropertyTagExifWhiteBalance		equ 0xA403
PropertyTagExifDigitalZoomRatio		equ 0xA404
PropertyTagExifFocalLengthIn35mmFilm	equ 0xA405
PropertyTagExifSceneCaptureType		equ 0xA406
PropertyTagExifGainControl		equ 0xA407
PropertyTagExifContrast			equ 0xA408
PropertyTagExifSaturation		equ 0xA409
PropertyTagExifSharpness		equ 0xA40A
PropertyTagExifDeviceSettingDesc	equ 0xA40B
PropertyTagExifSubjectDistanceRange	equ 0xA40C
PropertyTagExifUniqueImageID		equ 0xA420

PropertyTagGpsVer		equ 0x0000
PropertyTagGpsLatitudeRef	equ 0x0001
PropertyTagGpsLatitude		equ 0x0002
PropertyTagGpsLongitudeRef	equ 0x0003
PropertyTagGpsLongitude		equ 0x0004
PropertyTagGpsAltitudeRef	equ 0x0005
PropertyTagGpsAltitude		equ 0x0006
PropertyTagGpsGpsTime		equ 0x0007
PropertyTagGpsGpsSatellites	equ 0x0008
PropertyTagGpsGpsStatus		equ 0x0009
PropertyTagGpsGpsMeasureMode	equ 0x000A
PropertyTagGpsGpsDop		equ 0x000B
PropertyTagGpsSpeedRef		equ 0x000C
PropertyTagGpsSpeed		equ 0x000D
PropertyTagGpsTrackRef		equ 0x000E
PropertyTagGpsTrack		equ 0x000F
PropertyTagGpsImgDirRef		equ 0x0010
PropertyTagGpsImgDir		equ 0x0011
PropertyTagGpsMapDatum		equ 0x0012
PropertyTagGpsDestLatRef	equ 0x0013
PropertyTagGpsDestLat		equ 0x0014
PropertyTagGpsDestLongRef	equ 0x0015
PropertyTagGpsDestLong		equ 0x0016
PropertyTagGpsDestBearRef	equ 0x0017
PropertyTagGpsDestBear		equ 0x0018
PropertyTagGpsDestDistRef	equ 0x0019
PropertyTagGpsDestDist		equ 0x001A
PropertyTagGpsProcessingMethod	equ 0x001B
PropertyTagGpsAreaInformation	equ 0x001C
PropertyTagGpsDate		equ 0x001D
PropertyTagGpsDifferential	equ 0x001E

endif
