ifndef _GDIPLUSIMAGING_H
_GDIPLUSIMAGING_H equ <>

DEFINE_GUID(ImageFormatUndefined, 0xb96b3ca9,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
DEFINE_GUID(ImageFormatMemoryBMP, 0xb96b3caa,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
DEFINE_GUID(ImageFormatBMP, 0xb96b3cab,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
DEFINE_GUID(ImageFormatEMF, 0xb96b3cac,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
DEFINE_GUID(ImageFormatWMF, 0xb96b3cad,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
DEFINE_GUID(ImageFormatJPEG, 0xb96b3cae,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
DEFINE_GUID(ImageFormatPNG, 0xb96b3caf,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
DEFINE_GUID(ImageFormatGIF, 0xb96b3cb0,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
DEFINE_GUID(ImageFormatTIFF, 0xb96b3cb1,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
DEFINE_GUID(ImageFormatEXIF, 0xb96b3cb2,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);
DEFINE_GUID(ImageFormatIcon, 0xb96b3cb5,0x0728,0x11d3,0x9d,0x7b,0x00,0x00,0xf8,0x1e,0xf3,0x2e);

DEFINE_GUID(FrameDimensionTime, 0x6aedbd6d,0x3fb5,0x418a,0x83,0xa6,0x7f,0x45,0x22,0x9d,0xc8,0x72);
DEFINE_GUID(FrameDimensionResolution, 0x84236f7b,0x3bd3,0x428f,0x8d,0xab,0x4e,0xa1,0x43,0x9c,0xa3,0x15);
DEFINE_GUID(FrameDimensionPage, 0x7462dc86,0x6180,0x4c7e,0x8e,0x3f,0xee,0x73,0x33,0xa7,0xa4,0x83);

DEFINE_GUID(FormatIDImageInformation, 0xe5836cbe,0x5eef,0x4f1d,0xac,0xde,0xae,0x4c,0x43,0xb6,0x08,0xce);
DEFINE_GUID(FormatIDJpegAppHeaders, 0x1c4afdcd,0x6177,0x43cf,0xab,0xc7,0x5f,0x51,0xaf,0x39,0xee,0x85);

DEFINE_GUID(EncoderCompression, 0xe09d739d,0xccd4,0x44ee,0x8e,0xba,0x3f,0xbf,0x8b,0xe4,0xfc,0x58);
DEFINE_GUID(EncoderColorDepth, 0x66087055,0xad66,0x4c7c,0x9a,0x18,0x38,0xa2,0x31,0x0b,0x83,0x37);
DEFINE_GUID(EncoderScanMethod, 0x3a4e2661,0x3109,0x4e56,0x85,0x36,0x42,0xc1,0x56,0xe7,0xdc,0xfa);
DEFINE_GUID(EncoderVersion, 0x24d18c76,0x814a,0x41a4,0xbf,0x53,0x1c,0x21,0x9c,0xcc,0xf7,0x97);
DEFINE_GUID(EncoderRenderMethod, 0x6d42c53a,0x229a,0x4825,0x8b,0xb7,0x5c,0x99,0xe2,0xb9,0xa8,0xb8);
DEFINE_GUID(EncoderQuality, 0x1d5be4b5,0xfa4a,0x452d,0x9c,0xdd,0x5d,0xb3,0x51,0x05,0xe7,0xeb);
DEFINE_GUID(EncoderTransformation,0x8d0eb2d1,0xa58e,0x4ea8,0xaa,0x14,0x10,0x80,0x74,0xb7,0xb6,0xf9);
DEFINE_GUID(EncoderLuminanceTable,0xedb33bce,0x0266,0x4a77,0xb9,0x04,0x27,0x21,0x60,0x99,0xe7,0x17);
DEFINE_GUID(EncoderChrominanceTable,0xf2e455dc,0x09b3,0x4316,0x82,0x60,0x67,0x6a,0xda,0x32,0x48,0x1c);
DEFINE_GUID(EncoderSaveFlag,0x292266fc,0xac40,0x47bf,0x8c, 0xfc, 0xa8, 0x5b, 0x89, 0xa6, 0x55, 0xde);

if (GDIPVER GE 0x0110)
DEFINE_GUID(EncoderColorSpace,0xae7a62a0,0xee2c,0x49d8,0x9d,0x7,0x1b,0xa8,0xa9,0x27,0x59,0x6e);
DEFINE_GUID(EncoderImageItems,0x63875e13,0x1f1d,0x45ab,0x91, 0x95, 0xa2, 0x9b, 0x60, 0x66, 0xa6, 0x50);
DEFINE_GUID(EncoderSaveAsCMYK,0xa219bbc9, 0xa9d, 0x4005, 0xa3, 0xee, 0x3a, 0x42, 0x1b, 0x8b, 0xb0, 0x6c);
endif ;;(GDIPVER GE 0x0110)

DEFINE_GUID(CodecIImageBytes,0x025d1823,0x6c7d,0x447b,0xbb, 0xdb, 0xa3, 0xcb, 0xc3, 0xdf, 0xa2, 0xfc);

;MIDL_INTERFACE("025D1823-6C7D-447B-BBDB-A3CBC3DFA2FC")

.comdef IImageBytes

	QueryInterface	proc :REFIID, :ptr
	AddRef		proc
	Release		proc

	CountBytes	proc :ptr
	LockBytes	proc :UINT, :ULONG, :ptr
	UnlockBytes	proc :ptr, :UINT, :ULONG
	.ends

ImageCodecInfo		STRUC
Clsid			CLSID <>
FormatID		GUID <>
CodecName		LPWSTR ?
DllName			LPWSTR ?
FormatDescription	LPWSTR ?
FilenameExtension	LPWSTR ?
MimeType		LPWSTR ?
Flags			dd ?
Version			dd ?
SigCount		dd ?
SigSize			dd ?
SigPattern		db ?
SigMask			db ?
ImageCodecInfo		ENDS

ImageCodecFlags		typedef SDWORD
ImageCodecFlagsEncoder	equ 0x00000001
ImageCodecFlagsDecoder	equ 0x00000002
ImageCodecFlagsSupportBitmap equ 0x00000004
ImageCodecFlagsSupportVector equ 0x00000008
ImageCodecFlagsSeekableEncode equ 0x00000010
ImageCodecFlagsBlockingDecode equ 0x00000020
ImageCodecFlagsBuiltin	equ 0x00010000
ImageCodecFlagsSystem	equ 0x00020000
ImageCodecFlagsUser	equ 0x00040000

ImageLockMode		typedef SDWORD
ImageLockModeRead	equ 0x0001
ImageLockModeWrite	equ 0x0002
ImageLockModeUserInputBuf equ 0x0004

BitmapData		STRUC
_Width			UINT ?
Height			UINT ?
Stride			SINT ?
PixelFormat		PixelFormat ?
Scan0			PVOID ?
Reserved		UINT_PTR ?
BitmapData		ENDS

ImageFlags		typedef SDWORD
ImageFlagsNone		equ 0
ImageFlagsScalable	equ 0x0001
ImageFlagsHasAlpha	equ 0x0002
ImageFlagsHasTranslucent equ 0x0004
ImageFlagsPartiallyScalable equ 0x0008
ImageFlagsColorSpaceRGB equ 0x0010
ImageFlagsColorSpaceCMYK equ 0x0020
ImageFlagsColorSpaceGRAY equ 0x0040
ImageFlagsColorSpaceYCBCR equ 0x0080
ImageFlagsColorSpaceYCCK equ 0x0100
ImageFlagsHasRealDPI	equ 0x1000
ImageFlagsHasRealPixelSize equ 0x2000
ImageFlagsReadOnly	equ 0x00010000
ImageFlagsCaching	equ 0x00020000

RotateFlipType		typedef SDWORD
RotateNoneFlipNone	equ 0
Rotate90FlipNone	equ 1
Rotate180FlipNone	equ 2
Rotate270FlipNone	equ 3
RotateNoneFlipX		equ 4
Rotate90FlipX		equ 5
Rotate180FlipX		equ 6
Rotate270FlipX		equ 7
RotateNoneFlipY		equ Rotate180FlipX
Rotate90FlipY		equ Rotate270FlipX
Rotate180FlipY		equ RotateNoneFlipX
Rotate270FlipY		equ Rotate90FlipX
RotateNoneFlipXY	equ Rotate180FlipNone
Rotate90FlipXY		equ Rotate270FlipNone
Rotate180FlipXY		equ RotateNoneFlipNone
Rotate270FlipXY		equ Rotate90FlipNone

EncoderParameter	STRUC
Guid			GUID <>
NumberOfValues		ULONG ?
_Type			ULONG ?
Value			PVOID ?
EncoderParameter	ENDS

EncoderParameters	STRUC
Count			UINT ?
Parameter		EncoderParameter <>
EncoderParameters	ENDS

if (GDIPVER GE 0x0110)
ItemDataPosition	typedef SDWORD
ItemDataPositionAfterHeader equ 0x0
ItemDataPositionAfterPalette equ 0x1
ItemDataPositionAfterBits equ 0x2

ImageItemData		STRUC
_Size			UINT ?
Position		UINT ?
Desc			PVOID ?
DescSize		UINT ?
Data			PVOID ?
DataSize		UINT ?
Cookie			UINT ?
ImageItemData		ENDS
endif

PROPID			typedef ULONG

PropertyItem		STRUC
id			PROPID ?
_length			ULONG ?
_type			dw ?
value			PVOID ?
PropertyItem		ENDS

PropertyTagTypeByte	equ 1
PropertyTagTypeASCII	equ 2
PropertyTagTypeShort	equ 3
PropertyTagTypeLong	equ 4
PropertyTagTypeRational equ 5
PropertyTagTypeUndefined equ 7
PropertyTagTypeSLONG	equ 9
PropertyTagTypeSRational equ 10

PropertyTagExifIFD	equ 0x8769
PropertyTagGpsIFD	equ 0x8825

PropertyTagNewSubfileType equ 0x00FE
PropertyTagSubfileType	equ 0x00FF
PropertyTagImageWidth	equ 0x0100
PropertyTagImageHeight	equ 0x0101
PropertyTagBitsPerSample equ 0x0102
PropertyTagCompression	equ 0x0103
PropertyTagPhotometricInterp equ 0x0106
PropertyTagThreshHolding equ 0x0107
PropertyTagCellWidth	equ 0x0108
PropertyTagCellHeight	equ 0x0109
PropertyTagFillOrder	equ 0x010A
PropertyTagDocumentName equ 0x010D
PropertyTagImageDescription equ 0x010E
PropertyTagEquipMake	equ 0x010F
PropertyTagEquipModel	equ 0x0110
PropertyTagStripOffsets equ 0x0111
PropertyTagOrientation	equ 0x0112
PropertyTagSamplesPerPixel equ 0x0115
PropertyTagRowsPerStrip equ 0x0116
PropertyTagStripBytesCount equ 0x0117
PropertyTagMinSampleValue equ 0x0118
PropertyTagMaxSampleValue equ 0x0119
PropertyTagXResolution	equ 0x011A
PropertyTagYResolution	equ 0x011B
PropertyTagPlanarConfig equ 0x011C
PropertyTagPageName	equ 0x011D
PropertyTagXPosition	equ 0x011E
PropertyTagYPosition	equ 0x011F
PropertyTagFreeOffset	equ 0x0120
PropertyTagFreeByteCounts equ 0x0121
PropertyTagGrayResponseUnit equ 0x0122
PropertyTagGrayResponseCurve equ 0x0123
PropertyTagT4Option	equ 0x0124
PropertyTagT6Option	equ 0x0125
PropertyTagResolutionUnit equ 0x0128
PropertyTagPageNumber	equ 0x0129
PropertyTagTransferFuncition equ 0x012D
PropertyTagSoftwareUsed equ 0x0131
PropertyTagDateTime	equ 0x0132
PropertyTagArtist	equ 0x013B
PropertyTagHostComputer equ 0x013C
PropertyTagPredictor	equ 0x013D
PropertyTagWhitePoint	equ 0x013E
PropertyTagPrimaryChromaticities equ 0x013F
PropertyTagColorMap	equ 0x0140
PropertyTagHalftoneHints equ 0x0141
PropertyTagTileWidth	equ 0x0142
PropertyTagTileLength	equ 0x0143
PropertyTagTileOffset	equ 0x0144
PropertyTagTileByteCounts equ 0x0145
PropertyTagInkSet	equ 0x014C
PropertyTagInkNames	equ 0x014D
PropertyTagNumberOfInks equ 0x014E
PropertyTagDotRange	equ 0x0150
PropertyTagTargetPrinter equ 0x0151
PropertyTagExtraSamples equ 0x0152
PropertyTagSampleFormat equ 0x0153
PropertyTagSMinSampleValue equ 0x0154
PropertyTagSMaxSampleValue equ 0x0155
PropertyTagTransferRange equ 0x0156

PropertyTagJPEGProc	equ 0x0200
PropertyTagJPEGInterFormat equ 0x0201
PropertyTagJPEGInterLength equ 0x0202
PropertyTagJPEGRestartInterval equ 0x0203
PropertyTagJPEGLosslessPredictors equ 0x0205
PropertyTagJPEGPointTransforms equ 0x0206
PropertyTagJPEGQTables	equ 0x0207
PropertyTagJPEGDCTables equ 0x0208
PropertyTagJPEGACTables equ 0x0209

PropertyTagYCbCrCoefficients equ 0x0211
PropertyTagYCbCrSubsampling equ 0x0212
PropertyTagYCbCrPositioning equ 0x0213
PropertyTagREFBlackWhite equ 0x0214

PropertyTagICCProfile	equ 0x8773
PropertyTagGamma	equ 0x0301
PropertyTagICCProfileDescriptor equ 0x0302
PropertyTagSRGBRenderingIntent equ 0x0303

PropertyTagImageTitle	equ 0x0320
PropertyTagCopyright	equ 0x8298

PropertyTagResolutionXUnit equ 0x5001
PropertyTagResolutionYUnit equ 0x5002
PropertyTagResolutionXLengthUnit equ 0x5003
PropertyTagResolutionYLengthUnit equ 0x5004
PropertyTagPrintFlags	equ 0x5005
PropertyTagPrintFlagsVersion equ 0x5006
PropertyTagPrintFlagsCrop equ 0x5007
PropertyTagPrintFlagsBleedWidth equ 0x5008
PropertyTagPrintFlagsBleedWidthScale equ 0x5009
PropertyTagHalftoneLPI	equ <0x500A>
PropertyTagHalftoneLPIUnit equ 0x500B
PropertyTagHalftoneDegree equ 0x500C
PropertyTagHalftoneShape equ 0x500D
PropertyTagHalftoneMisc equ 0x500E
PropertyTagHalftoneScreen equ 0x500F
PropertyTagJPEGQuality	equ 0x5010
PropertyTagGridSize	equ 0x5011
PropertyTagThumbnailFormat equ 0x5012
PropertyTagThumbnailWidth equ 0x5013
PropertyTagThumbnailHeight equ 0x5014
PropertyTagThumbnailColorDepth equ 0x5015
PropertyTagThumbnailPlanes equ 0x5016
PropertyTagThumbnailRawBytes equ 0x5017
PropertyTagThumbnailSize equ 0x5018
PropertyTagThumbnailCompressedSize equ 0x5019
PropertyTagColorTransferFunction equ 0x501A
PropertyTagThumbnailData equ 0x501B

PropertyTagThumbnailImageWidth equ 0x5020
PropertyTagThumbnailImageHeight equ 0x5021
PropertyTagThumbnailBitsPerSample equ 0x5022
PropertyTagThumbnailCompression equ 0x5023
PropertyTagThumbnailPhotometricInterp equ 0x5024
PropertyTagThumbnailImageDescription equ 0x5025
PropertyTagThumbnailEquipMake equ 0x5026
PropertyTagThumbnailEquipModel equ 0x5027
PropertyTagThumbnailStripOffsets equ 0x5028
PropertyTagThumbnailOrientation equ 0x5029
PropertyTagThumbnailSamplesPerPixel equ 0x502A
PropertyTagThumbnailRowsPerStrip equ 0x502B
PropertyTagThumbnailStripBytesCount equ 0x502C
PropertyTagThumbnailResolutionX equ 0x502D
PropertyTagThumbnailResolutionY equ 0x502E
PropertyTagThumbnailPlanarConfig equ 0x502F
PropertyTagThumbnailResolutionUnit equ 0x5030
PropertyTagThumbnailTransferFunction equ 0x5031
PropertyTagThumbnailSoftwareUsed equ 0x5032
PropertyTagThumbnailDateTime equ 0x5033
PropertyTagThumbnailArtist equ 0x5034
PropertyTagThumbnailWhitePoint equ 0x5035
PropertyTagThumbnailPrimaryChromaticities equ 0x5036
PropertyTagThumbnailYCbCrCoefficients equ 0x5037
PropertyTagThumbnailYCbCrSubsampling equ 0x5038
PropertyTagThumbnailYCbCrPositioning equ 0x5039
PropertyTagThumbnailRefBlackWhite equ 0x503A
PropertyTagThumbnailCopyRight equ 0x503B

PropertyTagLuminanceTable equ 0x5090
PropertyTagChrominanceTable equ 0x5091

PropertyTagFrameDelay	equ 0x5100
PropertyTagLoopCount	equ 0x5101

if (GDIPVER GE 0x0110)
PropertyTagGlobalPalette equ 0x5102
PropertyTagIndexBackground equ 0x5103
PropertyTagIndexTransparent equ 0x5104
endif ;;(GDIPVER GE 0x0110)

PropertyTagPixelUnit	equ 0x5110
PropertyTagPixelPerUnitX equ 0x5111
PropertyTagPixelPerUnitY equ 0x5112
PropertyTagPaletteHistogram equ 0x5113

PropertyTagExifExposureTime equ 0x829A
PropertyTagExifFNumber	equ 0x829D

PropertyTagExifExposureProg equ 0x8822
PropertyTagExifSpectralSense equ 0x8824
PropertyTagExifISOSpeed equ 0x8827
PropertyTagExifOECF	equ 0x8828

PropertyTagExifVer	equ 0x9000
PropertyTagExifDTOrig	equ 0x9003
PropertyTagExifDTDigitized equ 0x9004

PropertyTagExifCompConfig equ 0x9101
PropertyTagExifCompBPP	equ 0x9102

PropertyTagExifShutterSpeed equ 0x9201
PropertyTagExifAperture equ 0x9202
PropertyTagExifBrightness equ 0x9203
PropertyTagExifExposureBias equ 0x9204
PropertyTagExifMaxAperture equ 0x9205
PropertyTagExifSubjectDist equ 0x9206
PropertyTagExifMeteringMode equ 0x9207
PropertyTagExifLightSource equ 0x9208
PropertyTagExifFlash	equ 0x9209
PropertyTagExifFocalLength equ 0x920A
PropertyTagExifSubjectArea equ 0x9214
PropertyTagExifMakerNote equ 0x927C
PropertyTagExifUserComment equ 0x9286
PropertyTagExifDTSubsec equ 0x9290
PropertyTagExifDTOrigSS equ 0x9291
PropertyTagExifDTDigSS	equ 0x9292

PropertyTagExifFPXVer	equ 0xA000
PropertyTagExifColorSpace equ 0xA001
PropertyTagExifPixXDim	equ 0xA002
PropertyTagExifPixYDim	equ 0xA003
PropertyTagExifRelatedWav equ 0xA004
PropertyTagExifInterop	equ 0xA005
PropertyTagExifFlashEnergy equ 0xA20B
PropertyTagExifSpatialFR equ 0xA20C
PropertyTagExifFocalXRes equ 0xA20E
PropertyTagExifFocalYRes equ 0xA20F
PropertyTagExifFocalResUnit equ 0xA210
PropertyTagExifSubjectLoc equ 0xA214
PropertyTagExifExposureIndex equ 0xA215
PropertyTagExifSensingMethod equ 0xA217
PropertyTagExifFileSource equ 0xA300
PropertyTagExifSceneType equ 0xA301
PropertyTagExifCfaPattern equ 0xA302

PropertyTagExifCustomRendered equ 0xA401
PropertyTagExifExposureMode equ 0xA402
PropertyTagExifWhiteBalance equ 0xA403
PropertyTagExifDigitalZoomRatio equ 0xA404
PropertyTagExifFocalLengthIn35mmFilm equ 0xA405
PropertyTagExifSceneCaptureType equ 0xA406
PropertyTagExifGainControl equ 0xA407
PropertyTagExifContrast equ 0xA408
PropertyTagExifSaturation equ 0xA409
PropertyTagExifSharpness equ 0xA40A
PropertyTagExifDeviceSettingDesc equ 0xA40B
PropertyTagExifSubjectDistanceRange equ 0xA40C
PropertyTagExifUniqueImageID equ 0xA420

PropertyTagGpsVer	equ 0x0000
PropertyTagGpsLatitudeRef equ 0x0001
PropertyTagGpsLatitude	equ 0x0002
PropertyTagGpsLongitudeRef equ 0x0003
PropertyTagGpsLongitude equ 0x0004
PropertyTagGpsAltitudeRef equ 0x0005
PropertyTagGpsAltitude	equ 0x0006
PropertyTagGpsGpsTime	equ 0x0007
PropertyTagGpsGpsSatellites equ 0x0008
PropertyTagGpsGpsStatus equ 0x0009
PropertyTagGpsGpsMeasureMode equ 0x00A
PropertyTagGpsGpsDop	equ 0x000B
PropertyTagGpsSpeedRef	equ 0x000C
PropertyTagGpsSpeed	equ 0x000D
PropertyTagGpsTrackRef	equ 0x000E
PropertyTagGpsTrack	equ 0x000F
PropertyTagGpsImgDirRef equ 0x0010
PropertyTagGpsImgDir	equ 0x0011
PropertyTagGpsMapDatum	equ 0x0012
PropertyTagGpsDestLatRef equ 0x0013
PropertyTagGpsDestLat	equ 0x0014
PropertyTagGpsDestLongRef equ 0x0015
PropertyTagGpsDestLong	equ 0x0016
PropertyTagGpsDestBearRef equ 0x0017
PropertyTagGpsDestBear	equ 0x0018
PropertyTagGpsDestDistRef equ 0x0019
PropertyTagGpsDestDist	equ 0x001A
PropertyTagGpsProcessingMethod equ 0x001B
PropertyTagGpsAreaInformation equ 0x001C
PropertyTagGpsDate	equ 0x001D
PropertyTagGpsDifferential equ 0x001E

endif
