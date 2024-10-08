ifndef	 __BTHDEF_H__
__BTHDEF_H__ equ 1
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

if (NTDDI_VERSION GT NTDDI_VISTASP1 OR (NTDDI_VERSION EQ NTDDI_VISTASP1 AND defined(VISTA_KB942567)))

BTH_MAJORVERSION	equ 2
BTH_MINORVERSION	equ 1

elseif (NTDDI_VERSION GE NTDDI_WINXPSP2)

BTH_MAJORVERSION	equ 2
BTH_MINORVERSION	equ 0

endif

if (NTDDI_VERSION GE NTDDI_WINXPSP2)

ifndef GUID_DEFS_ONLY
ifndef NO_BTHSDPDEF_INC
include bthsdpdef.inc
endif
endif

ifndef NO_GUID_DEFS

DEFINE_GUID(GUID_BTHPORT_DEVICE_INTERFACE,		0x0850302a, 0xb344, 0x4fda, 0x9b, 0xe9, 0x90, 0x57, 0x6b, 0x8d, 0x46, 0xf0)
DEFINE_GUID(GUID_BTH_RFCOMM_SERVICE_DEVICE_INTERFACE,	0xb142fc3e, 0xfa4e, 0x460b, 0x8a, 0xbc, 0x07, 0x2b, 0x62, 0x8b, 0x3c, 0x70)
DEFINE_GUID(GUID_BLUETOOTH_RADIO_IN_RANGE,		0xea3b5b82, 0x26ee, 0x450e, 0xb0, 0xd8, 0xd2, 0x6f, 0xe3, 0x0a, 0x38, 0x69)
DEFINE_GUID(GUID_BLUETOOTH_RADIO_OUT_OF_RANGE,		0xe28867c9, 0xc2aa, 0x4ced, 0xb9, 0x69, 0x45, 0x70, 0x86, 0x60, 0x37, 0xc4)
DEFINE_GUID(GUID_BLUETOOTH_L2CAP_EVENT,			0x7eae4030, 0xb709, 0x4aa8, 0xac, 0x55, 0xe9, 0x53, 0x82, 0x9c, 0x9d, 0xaa)
DEFINE_GUID(GUID_BLUETOOTH_HCI_EVENT,			0xfc240062, 0x1541, 0x49be, 0xb4, 0x63, 0x84, 0xc4, 0xdc, 0xd7, 0xbf, 0x7f)

if (NTDDI_VERSION GT NTDDI_VISTASP1 OR (NTDDI_VERSION EQ NTDDI_VISTASP1 AND defined(VISTA_KB942567)))

DEFINE_GUID(GUID_BLUETOOTH_AUTHENTICATION_REQUEST,	0x5DC9136D, 0x996C, 0x46DB, 0x84, 0xF5, 0x32, 0xC0, 0xA3, 0xF4, 0x73, 0x52)
DEFINE_GUID(GUID_BLUETOOTH_KEYPRESS_EVENT,		0xD668DFCD, 0x0F4E, 0x4EFC, 0xBF, 0xE0, 0x39, 0x2E, 0xEE, 0xC5, 0x10, 0x9C)
DEFINE_GUID(GUID_BLUETOOTH_HCI_VENDOR_EVENT,		0x547247e6, 0x45bb, 0x4c33, 0xaf, 0x8c, 0xc0, 0x0e, 0xfe, 0x15, 0xa7, 0x1d)

endif


DEFINE_GUID(Bluetooth_Base_UUID,   0x00000000, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)

DEFINE_GUID(SDP_PROTOCOL_UUID,	  0x00000001, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(UDP_PROTOCOL_UUID,	  0x00000002, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(RFCOMM_PROTOCOL_UUID, 0x00000003, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(TCP_PROTOCOL_UUID,	  0x00000004, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(TCSBIN_PROTOCOL_UUID, 0x00000005, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(TCSAT_PROTOCOL_UUID,  0x00000006, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(OBEX_PROTOCOL_UUID,	  0x00000008, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(IP_PROTOCOL_UUID,	  0x00000009, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(FTP_PROTOCOL_UUID,	  0x0000000A, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(HTTP_PROTOCOL_UUID,	  0x0000000C, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(WSP_PROTOCOL_UUID,	  0x0000000E, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(BNEP_PROTOCOL_UUID,	  0x0000000F, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(UPNP_PROTOCOL_UUID,	  0x00000010, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(HID_PROTOCOL_UUID,	  0x00000011, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(HCCC_PROTOCOL_UUID,	  0x00000012, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(HCDC_PROTOCOL_UUID,	  0x00000014, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(HN_PROTOCOL_UUID,	  0x00000016, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(AVCTP_PROTOCOL_UUID,  0x00000017, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(AVDTP_PROTOCOL_UUID,  0x00000019, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(CMPT_PROTOCOL_UUID,	  0x0000001B, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(UDI_C_PLANE_PROTOCOL_UUID, 0x0000001D, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(L2CAP_PROTOCOL_UUID,  0x00000100, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)

SDP_PROTOCOL_UUID16	equ (0x0001)
UDP_PROTOCOL_UUID16	equ (0x0002)
RFCOMM_PROTOCOL_UUID16	equ (0x0003)
TCP_PROTOCOL_UUID16	equ (0x0004)
TCSBIN_PROTOCOL_UUID16	equ (0x0005)
TCSAT_PROTOCOL_UUID16	equ (0x0006)
OBEX_PROTOCOL_UUID16	equ (0x0008)
IP_PROTOCOL_UUID16	equ (0x0009)
FTP_PROTOCOL_UUID16	equ (0x000A)
HTTP_PROTOCOL_UUID16	equ (0x000C)
WSP_PROTOCOL_UUID16	equ (0x000E)
BNEP_PROTOCOL_UUID16	equ (0x000F)
UPNP_PROTOCOL_UUID16	equ (0x0010)
HID_PROTOCOL_UUID16	equ (0x0011)
HCCC_PROTOCOL_UUID16	equ (0x0012)
HCDC_PROTOCOL_UUID16	equ (0x0014)
HCN_PROTOCOL_UUID16	equ (0x0016)
AVCTP_PROTOCOL_UUID16	equ (0x0017)
AVDTP_PROTOCOL_UUID16	equ (0x0019)
CMPT_PROTOCOL_UUID16	equ (0x001B)
UDI_C_PLANE_PROTOCOL_UUID16 equ (0x001D)
L2CAP_PROTOCOL_UUID16	equ (0x0100)

DEFINE_GUID(ServiceDiscoveryServerServiceClassID_UUID, 0x00001000, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(BrowseGroupDescriptorServiceClassID_UUID,  0x00001001, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(PublicBrowseGroupServiceClass_UUID,	       0x00001002, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(SerialPortServiceClass_UUID,	       0x00001101, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(LANAccessUsingPPPServiceClass_UUID,	       0x00001102, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(DialupNetworkingServiceClass_UUID,	       0x00001103, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(IrMCSyncServiceClass_UUID,		       0x00001104, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(OBEXObjectPushServiceClass_UUID,	       0x00001105, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(OBEXFileTransferServiceClass_UUID,	       0x00001106, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(IrMCSyncCommandServiceClass_UUID,	       0x00001107, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(HeadsetServiceClass_UUID,		       0x00001108, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(CordlessTelephonyServiceClass_UUID,	       0x00001109, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(AudioSourceServiceClass_UUID,	       0x0000110A, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(AudioSinkServiceClass_UUID,		       0x0000110B, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(AVRemoteControlTargetServiceClass_UUID,    0x0000110C, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(AdvancedAudioDistributionServiceClass_UUID,0x0000110D, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(AVRemoteControlServiceClass_UUID,	       0x0000110E, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(AVRemoteControlControllerServiceClass_UUID,0x0000110F, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(IntercomServiceClass_UUID,		       0x00001110, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(FaxServiceClass_UUID,		       0x00001111, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(HeadsetAudioGatewayServiceClass_UUID,      0x00001112, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(WAPServiceClass_UUID,		       0x00001113, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(WAPClientServiceClass_UUID,		       0x00001114, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(PANUServiceClass_UUID,		       0x00001115, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(NAPServiceClass_UUID,		       0x00001116, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(GNServiceClass_UUID,		       0x00001117, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(DirectPrintingServiceClass_UUID,	       0x00001118, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(ReferencePrintingServiceClass_UUID,	       0x00001119, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(ImagingServiceClass_UUID,		       0x0000111A, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(ImagingResponderServiceClass_UUID,	       0x0000111B, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(ImagingAutomaticArchiveServiceClass_UUID,  0x0000111C, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(ImagingReferenceObjectsServiceClass_UUID,  0x0000111D, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(HandsfreeServiceClass_UUID,		       0x0000111E, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(HandsfreeAudioGatewayServiceClass_UUID,    0x0000111F, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(DirectPrintingReferenceObjectsServiceClass_UUID, 0x00001120, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(ReflectedUIServiceClass_UUID,	       0x00001121, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(BasicPringingServiceClass_UUID,	       0x00001122, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(PrintingStatusServiceClass_UUID,	       0x00001123, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(HumanInterfaceDeviceServiceClass_UUID,     0x00001124, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(HardcopyCableReplacementServiceClass_UUID, 0x00001125, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(HCRPrintServiceClass_UUID,		       0x00001126, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(HCRScanServiceClass_UUID,		       0x00001127, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(CommonISDNAccessServiceClass_UUID,	       0x00001128, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(VideoConferencingGWServiceClass_UUID,      0x00001129, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(UDIMTServiceClass_UUID,		       0x0000112A, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(UDITAServiceClass_UUID,		       0x0000112B, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(AudioVideoServiceClass_UUID,	       0x0000112C, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)

DEFINE_GUID(SimAccessServiceClass_UUID,		       0x0000112D, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(PhonebookAccessPceServiceClass_UUID,       0x0000112E, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(PhonebookAccessPseServiceClass_UUID,       0x0000112F, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(PnPInformationServiceClass_UUID,	       0x00001200, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(GenericNetworkingServiceClass_UUID,	       0x00001201, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(GenericFileTransferServiceClass_UUID,      0x00001202, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(GenericAudioServiceClass_UUID,	       0x00001203, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(GenericTelephonyServiceClass_UUID,	       0x00001204, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(UPnpServiceClass_UUID,		       0x00001205, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(UPnpIpServiceClass_UUID,		       0x00001206, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(ESdpUpnpIpPanServiceClass_UUID,	       0x00001300, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(ESdpUpnpIpLapServiceClass_UUID,	       0x00001301, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(ESdpUpnpL2capServiceClass_UUID,	       0x00001302, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(VideoSourceServiceClass_UUID,	       0x00001303, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(VideoSinkServiceClass_UUID,		       0x00001304, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)
DEFINE_GUID(VideoDistributionServiceClass_UUID,	       0x00001305, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)

BasicPrintingServiceClass_UUID equ <BasicPringingServiceClass_UUID>

ServiceDiscoveryServerServiceClassID_UUID16 equ (0x1000)
BrowseGroupDescriptorServiceClassID_UUID16 equ (0x1001)
PublicBrowseGroupServiceClassID_UUID16 equ (0x1002)
SerialPortServiceClassID_UUID16 equ (0x1101)
LANAccessUsingPPPServiceClassID_UUID16 equ (0x1102)
DialupNetworkingServiceClassID_UUID16 equ (0x1103)
IrMCSyncServiceClassID_UUID16 equ (0x1104)
OBEXObjectPushServiceClassID_UUID16 equ (0x1105)
OBEXFileTransferServiceClassID_UUID16 equ (0x1106)
IrMcSyncCommandServiceClassID_UUID16 equ (0x1107)
HeadsetServiceClassID_UUID16 equ (0x1108)
CordlessServiceClassID_UUID16 equ (0x1109)
AudioSourceServiceClassID_UUID16 equ (0x110A)
AudioSinkSourceServiceClassID_UUID16 equ (0x110B)
AVRemoteControlTargetServiceClassID_UUID16 equ (0x110C)
AdvancedAudioDistributionServiceClassID_UUID16 equ (0x110D)
AVRemoteControlServiceClassID_UUID16 equ (0x110E)
AVRemoteControlControllerServiceClass_UUID16 equ (0x110F)
IntercomServiceClassID_UUID16 equ (0x1110)
FaxServiceClassID_UUID16 equ (0x1111)
HeadsetAudioGatewayServiceClassID_UUID16 equ (0x1112)
WAPServiceClassID_UUID16 equ (0x1113)
WAPClientServiceClassID_UUID16 equ (0x1114)
PANUServiceClassID_UUID16 equ (0x1115)
NAPServiceClassID_UUID16 equ (0x1116)
GNServiceClassID_UUID16 equ (0x1117)
DirectPrintingServiceClassID_UUID16 equ (0x1118)
ReferencePrintingServiceClassID_UUID16 equ (0x1119)
ImagingServiceClassID_UUID16 equ (0x111A)
ImagingResponderServiceClassID_UUID16 equ (0x111B)
ImagingAutomaticArchiveServiceClassID_UUID16 equ (0x111C)
ImagingReferenceObjectsServiceClassID_UUID16 equ (0x111D)
HandsfreeServiceClassID_UUID16 equ (0x111E)
HandsfreeAudioGatewayServiceClassID_UUID16 equ (0x111F)
DirectPrintingReferenceObjectsServiceClassID_UUID16 equ (0x1120)
ReflectsUIServiceClassID_UUID16 equ (0x1121)
BasicPrintingServiceClassID_UUID16 equ (0x1122)
PrintingStatusServiceClassID_UUID16 equ (0x1123)
HumanInterfaceDeviceServiceClassID_UUID16 equ (0x1124)
HardcopyCableReplacementServiceClassID_UUID16 equ (0x1125)
HCRPrintServiceClassID_UUID16 equ (0x1126)
HCRScanServiceClassID_UUID16 equ (0x1127)
CommonISDNAccessServiceClass_UUID16 equ (0x1128)
VideoConferencingGWServiceClass_UUID16 equ (0x1129)
UDIMTServiceClass_UUID16 equ (0x112A)
UDITAServiceClass_UUID16 equ (0x112B)
AudioVideoServiceClass_UUID16 equ (0x112C)

PnPInformationServiceClassID_UUID16 equ (0x1200)
GenericNetworkingServiceClassID_UUID16 equ (0x1201)
GenericFileTransferServiceClassID_UUID16 equ (0x1202)
GenericAudioServiceClassID_UUID16 equ (0x1203)
GenericTelephonyServiceClassID_UUID16 equ (0x1204)

VideoConferencingServiceClass_UUID equ <AVRemoteControlControllerServiceClass_UUID>
VideoConferencingServiceClassID_UUID16 equ <AVRemoteControlControllerServiceClass_UUID16>

endif ;;  NO_GUID_DEFS

ifndef GUID_DEFS_ONLY

BTH_MAX_NAME_SIZE	equ (248)

BTH_MAX_PIN_SIZE	equ (16)
BTH_LINK_KEY_LENGTH	equ (16)

BTH_MFG_ERICSSON	equ (0)
BTH_MFG_NOKIA		equ (1)
BTH_MFG_INTEL		equ (2)
BTH_MFG_IBM		equ (3)
BTH_MFG_TOSHIBA		equ (4)
BTH_MFG_3COM		equ (5)
BTH_MFG_MICROSOFT	equ (6)
BTH_MFG_LUCENT		equ (7)
BTH_MFG_MOTOROLA	equ (8)
BTH_MFG_INFINEON	equ (9)
BTH_MFG_CSR		equ (10)
BTH_MFG_SILICONWAVE	equ (11)
BTH_MFG_DIGIANSWER	equ (12)
BTH_MFG_TI		equ (13)
BTH_MFG_PARTHUS		equ (14)
BTH_MFG_BROADCOM	equ (15)
BTH_MFG_MITEL		equ (16)
BTH_MFG_WIDCOMM		equ (17)
BTH_MFG_ZEEVO		equ (18)
BTH_MFG_ATMEL		equ (19)
BTH_MFG_MITSIBUSHI	equ (20)
BTH_MFG_RTX_TELECOM	equ (21)
BTH_MFG_KC_TECHNOLOGY	equ (22)
BTH_MFG_NEWLOGIC	equ (23)
BTH_MFG_TRANSILICA	equ (24)
BTH_MFG_ROHDE_SCHWARZ	equ (25)
BTH_MFG_TTPCOM		equ (26)
BTH_MFG_SIGNIA		equ (27)
BTH_MFG_CONEXANT	equ (28)
BTH_MFG_QUALCOMM	equ (29)
BTH_MFG_INVENTEL	equ (30)
BTH_MFG_AVM_BERLIN	equ (31)
BTH_MFG_BANDSPEED	equ (32)
BTH_MFG_MANSELLA	equ (33)
BTH_MFG_NEC		equ (34)
BTH_MFG_WAVEPLUS_TECHNOLOGY_CO equ (35)
BTH_MFG_ALCATEL		equ (36)
BTH_MFG_PHILIPS_SEMICONDUCTOR equ (37)
BTH_MFG_C_TECHNOLOGIES	equ (38)
BTH_MFG_OPEN_INTERFACE	equ (39)
BTH_MFG_RF_MICRO_DEVICES equ (40)
BTH_MFG_HITACHI		equ (41)
BTH_MFG_SYMBOL_TECHNOLOGIES equ (42)
BTH_MFG_TENOVIS		equ (43)
BTH_MFG_MACRONIX_INTERNATIONAL equ (44)
BTH_MFG_NORDIC_SEMICONDUCTORS_ASA equ (89)
BTH_MFG_INTERNAL_USE	equ (65535)

BTH_ADDR		typedef ULONGLONG
BTH_COD			typedef ULONG
BTH_LAP			typedef ULONG
PBTH_ADDR		typedef ptr ULONGLONG
PBTH_COD		typedef ptr ULONG
PBTH_LAP		typedef ptr ULONG

BTH_ADDR_NULL		equ (0x0000000000000000)

NAP_MASK		equ (0xFFFF00000000)
SAP_MASK		equ (0x0000FFFFFFFF)

NAP_BIT_OFFSET		equ (8 * 4)
SAP_BIT_OFFSET		equ (0)

GET_NAP macro _bth_addr
	exitm<((((_bth_addr) AND NAP_MASK) SHR NAP_BIT_OFFSET))>
	endm
GET_SAP macro _bth_addr
	exitm<((((_bth_addr) AND SAP_MASK) SHR SAP_BIT_OFFSET))>
	endm

SET_NAP macro _nap
	exitm<((((_nap))) SHL NAP_BIT_OFFSET)>
	endm
SET_SAP macro _sap
	exitm<((((_sap))) SHL SAP_BIT_OFFSET)>
	endm

SET_NAP_SAP macro _nap, _sap
	exitm<(SET_NAP(_nap) OR SET_SAP(_sap))>
	endm

COD_FORMAT_BIT_OFFSET	equ (0)
COD_MINOR_BIT_OFFSET	equ (2)
COD_MAJOR_BIT_OFFSET	equ (8 * 1)
COD_SERVICE_BIT_OFFSET	equ (8 * 1 + 5)

COD_FORMAT_MASK		equ (0x000003)
COD_MINOR_MASK		equ (0x0000FC)
COD_MAJOR_MASK		equ (0x001F00)
COD_SERVICE_MASK	equ (0xFFE000)


GET_COD_FORMAT macro _cod
	exitm<( (_cod) AND COD_FORMAT_MASK SHR COD_FORMAT_BIT_OFFSET)>
	endm
GET_COD_MINOR macro _cod
	exitm<(((_cod) AND COD_MINOR_MASK) SHR COD_MINOR_BIT_OFFSET)>
	endm
GET_COD_MAJOR macro _cod
	exitm<(((_cod) AND COD_MAJOR_MASK) SHR COD_MAJOR_BIT_OFFSET)>
	endm
GET_COD_SERVICE macro _cod
	exitm<(((_cod) AND COD_SERVICE_MASK) SHR COD_SERVICE_BIT_OFFSET)>
	endm

SET_COD_MINOR macro _cod, _minor
	exitm<(_cod) equ ((_cod) AND NOT COD_MINOR_MASK) OR ((_minor) SHL COD_MINOR_BIT_OFFSET)>
	endm
SET_COD_MAJOR macro _cod, _major
	exitm<(_cod) equ ((_cod) AND NOT COD_MAJOR_MASK) OR ((_major) SHL COD_MAJOR_BIT_OFFSET)>
	endm
SET_COD_SERVICE macro _cod, _service
	exitm<(_cod) equ ((_cod) AND NOT COD_SERVICE_MASK) OR ((_service) SHL COD_SERVICE_BIT_OFFSET)>
	endm

COD_VERSION		equ (0x0)

COD_SERVICE_LIMITED	equ (0x0001)
COD_SERVICE_POSITIONING equ (0x0008)
COD_SERVICE_NETWORKING	equ (0x0010)
COD_SERVICE_RENDERING	equ (0x0020)
COD_SERVICE_CAPTURING	equ (0x0040)
COD_SERVICE_OBJECT_XFER equ (0x0080)
COD_SERVICE_AUDIO	equ (0x0100)
COD_SERVICE_TELEPHONY	equ (0x0200)
COD_SERVICE_INFORMATION equ (0x0400)

COD_SERVICE_VALID_MASK	equ (COD_SERVICE_LIMITED OR COD_SERVICE_POSITIONING OR COD_SERVICE_NETWORKING OR COD_SERVICE_RENDERING OR COD_SERVICE_CAPTURING OR COD_SERVICE_OBJECT_XFER OR COD_SERVICE_AUDIO OR COD_SERVICE_TELEPHONY)
COD_SERVICE_MAX_COUNT	equ (9)

COD_MAJOR_MISCELLANEOUS equ (0x00)
COD_MAJOR_COMPUTER	equ (0x01)
COD_MAJOR_PHONE		equ (0x02)
COD_MAJOR_LAN_ACCESS	equ (0x03)
COD_MAJOR_AUDIO		equ (0x04)
COD_MAJOR_PERIPHERAL	equ (0x05)
COD_MAJOR_IMAGING	equ (0x06)
COD_MAJOR_WEARABLE	equ (0x07)
COD_MAJOR_TOY		equ (0x08)
COD_MAJOR_HEALTH	equ (0x09)
COD_MAJOR_UNCLASSIFIED	equ (0x1F)

COD_COMPUTER_MINOR_UNCLASSIFIED equ (0x00)
COD_COMPUTER_MINOR_DESKTOP equ (0x01)
COD_COMPUTER_MINOR_SERVER equ (0x02)
COD_COMPUTER_MINOR_LAPTOP equ (0x03)
COD_COMPUTER_MINOR_HANDHELD equ (0x04)
COD_COMPUTER_MINOR_PALM equ (0x05)
COD_COMPUTER_MINOR_WEARABLE equ (0x06)

COD_PHONE_MINOR_UNCLASSIFIED equ (0x00)
COD_PHONE_MINOR_CELLULAR equ (0x01)
COD_PHONE_MINOR_CORDLESS equ (0x02)
COD_PHONE_MINOR_SMART	equ (0x03)
COD_PHONE_MINOR_WIRED_MODEM equ (0x04)

COD_AUDIO_MINOR_UNCLASSIFIED equ (0x00)
COD_AUDIO_MINOR_HEADSET equ (0x01)
COD_AUDIO_MINOR_HANDS_FREE equ (0x02)
COD_AUDIO_MINOR_HEADSET_HANDS_FREE equ (0x03)
COD_AUDIO_MINOR_MICROPHONE equ (0x04)
COD_AUDIO_MINOR_LOUDSPEAKER equ (0x05)
COD_AUDIO_MINOR_HEADPHONES equ (0x06)
COD_AUDIO_MINOR_PORTABLE_AUDIO equ (0x07)
COD_AUDIO_MINOR_CAR_AUDIO equ (0x08)
COD_AUDIO_MINOR_SET_TOP_BOX equ (0x09)
COD_AUDIO_MINOR_HIFI_AUDIO equ (0x0A)
COD_AUDIO_MINOR_VCR	equ (0x0B)
COD_AUDIO_MINOR_VIDEO_CAMERA equ (0x0C)
COD_AUDIO_MINOR_CAMCORDER equ (0x0D)
COD_AUDIO_MINOR_VIDEO_MONITOR equ (0x0E)
COD_AUDIO_MINOR_VIDEO_DISPLAY_LOUDSPEAKER equ (0x0F)
COD_AUDIO_MINOR_VIDEO_DISPLAY_CONFERENCING equ (0x10)
;; COD_AUDIO_MINOR_RESERVED equ (0x11)
COD_AUDIO_MINOR_GAMING_TOY equ (0x12)

COD_PERIPHERAL_MINOR_KEYBOARD_MASK equ (0x10)
COD_PERIPHERAL_MINOR_POINTER_MASK equ (0x20)

COD_PERIPHERAL_MINOR_NO_CATEGORY equ (0x00)
COD_PERIPHERAL_MINOR_JOYSTICK equ (0x01)
COD_PERIPHERAL_MINOR_GAMEPAD equ (0x02)
COD_PERIPHERAL_MINOR_REMOTE_CONTROL equ (0x03)
COD_PERIPHERAL_MINOR_SENSING equ (0x04)

COD_IMAGING_MINOR_DISPLAY_MASK equ (0x04)
COD_IMAGING_MINOR_CAMERA_MASK equ (0x08)
COD_IMAGING_MINOR_SCANNER_MASK equ (0x10)
COD_IMAGING_MINOR_PRINTER_MASK equ (0x20)

COD_WEARABLE_MINOR_WRIST_WATCH equ (0x01)
COD_WEARABLE_MINOR_PAGER equ (0x02)
COD_WEARABLE_MINOR_JACKET equ (0x03)
COD_WEARABLE_MINOR_HELMET equ (0x04)
COD_WEARABLE_MINOR_GLASSES equ (0x05)

COD_TOY_MINOR_ROBOT	equ (0x01)
COD_TOY_MINOR_VEHICLE	equ (0x02)
COD_TOY_MINOR_DOLL_ACTION_FIGURE equ (0x03)
COD_TOY_MINOR_CONTROLLER equ (0x04)
COD_TOY_MINOR_GAME	equ (0x05)

COD_HEALTH_MINOR_BLOOD_PRESSURE_MONITOR equ (0x01)
COD_HEALTH_MINOR_THERMOMETER equ (0x02)
COD_HEALTH_MINOR_WEIGHING_SCALE equ (0x03)
COD_HEALTH_MINOR_GLUCOSE_METER equ (0x04)
COD_HEALTH_MINOR_PULSE_OXIMETER equ (0x05)
COD_HEALTH_MINOR_HEART_PULSE_MONITOR equ (0x06)
COD_HEALTH_MINOR_HEALTH_DATA_DISPLAY equ (0x07)
COD_HEALTH_MINOR_STEP_COUNTER equ (0x08)

COD_LAN_ACCESS_BIT_OFFSET equ (5)

COD_LAN_MINOR_MASK	equ (0x00001C)
COD_LAN_ACCESS_MASK	equ (0x0000E0)

GET_COD_LAN_MINOR macro _cod
	exitm<(((_cod) AND COD_LAN_MINOR_MASK) SHR COD_MINOR_BIT_OFFSET)>
	endm
GET_COD_LAN_ACCESS macro _cod
	exitm<(((_cod) AND COD_LAN_ACCESS_MASK) SHR COD_LAN_ACCESS_BIT_OFFSET)>
	endm

COD_LAN_MINOR_UNCLASSIFIED equ (0x00)

COD_LAN_ACCESS_0_USED	equ (0x00)
COD_LAN_ACCESS_17_USED	equ (0x01)
COD_LAN_ACCESS_33_USED	equ (0x02)
COD_LAN_ACCESS_50_USED	equ (0x03)
COD_LAN_ACCESS_67_USED	equ (0x04)
COD_LAN_ACCESS_83_USED	equ (0x05)
COD_LAN_ACCESS_99_USED	equ (0x06)
COD_LAN_ACCESS_FULL	equ (0x07)

BTH_EIR_FLAGS_ID	equ (0x01)
BTH_EIR_16_UUIDS_PARTIAL_ID equ (0x02)
BTH_EIR_16_UUIDS_COMPLETE_ID equ (0x03)
BTH_EIR_32_UUIDS_PARTIAL_ID equ (0x04)
BTH_EIR_32_UUIDS_COMPLETE_ID equ (0x05)
BTH_EIR_128_UUIDS_PARTIAL_ID equ (0x06)
BTH_EIR_128_UUIDS_COMPLETE_ID equ (0x07)
BTH_EIR_LOCAL_NAME_PARTIAL_ID equ (0x08)
BTH_EIR_LOCAL_NAME_COMPLETE_ID equ (0x09)
BTH_EIR_TX_POWER_LEVEL_ID equ (0x0A)
BTH_EIR_OOB_OPT_DATA_LEN_ID equ (0x0B)
BTH_EIR_OOB_BD_ADDR_ID	equ (0x0C)
BTH_EIR_OOB_COD_ID	equ (0x0D)
BTH_EIR_OOB_SP_HASH_ID	equ (0x0E)
BTH_EIR_OOB_SP_RANDOMIZER_ID equ (0x0F)
BTH_EIR_MANUFACTURER_ID equ (0xFF)

BTH_EIR_SIZE		equ (240)

LAP_GIAC_INIT		equ <{ 0x33, 0x8B, 0x9E }>
LAP_LIAC_INIT		equ <{ 0x00, 0x8B, 0x9E }>

LAP_GIAC_VALUE		equ (0x009E8B33)

LAP_LIAC_VALUE		equ (0x009E8B00)

BTH_ADDR_IAC_FIRST	equ (0x9E8B00)
BTH_ADDR_IAC_LAST	equ (0x9E8B3f)
BTH_ADDR_LIAC		equ (0x9E8B00)
BTH_ADDR_GIAC		equ (0x9E8B33)

BTHSTATUS		typedef UCHAR
PBTHSTATUS		typedef ptr UCHAR

BTH_ERROR macro _btStatus
	exitm<((_btStatus) NOT EQ BTH_ERROR_SUCCESS)>
	endm
BTH_SUCCESS macro _btStatus
	exitm<((_btStatus) EQ BTH_ERROR_SUCCESS)>
	endm

BTH_ERROR_SUCCESS	equ (0x00)
BTH_ERROR_UNKNOWN_HCI_COMMAND equ (0x01)
BTH_ERROR_NO_CONNECTION equ (0x02)
BTH_ERROR_HARDWARE_FAILURE equ (0x03)
BTH_ERROR_PAGE_TIMEOUT	equ (0x04)
BTH_ERROR_AUTHENTICATION_FAILURE equ (0x05)
BTH_ERROR_KEY_MISSING	equ (0x06)
BTH_ERROR_MEMORY_FULL	equ (0x07)
BTH_ERROR_CONNECTION_TIMEOUT equ (0x08)
BTH_ERROR_MAX_NUMBER_OF_CONNECTIONS equ (0x09)
BTH_ERROR_MAX_NUMBER_OF_SCO_CONNECTIONS equ (0x0a)
BTH_ERROR_ACL_CONNECTION_ALREADY_EXISTS equ (0x0b)
BTH_ERROR_COMMAND_DISALLOWED equ (0x0c)
BTH_ERROR_HOST_REJECTED_LIMITED_RESOURCES equ (0x0d)
BTH_ERROR_HOST_REJECTED_SECURITY_REASONS equ (0x0e)
BTH_ERROR_HOST_REJECTED_PERSONAL_DEVICE equ (0x0f)
BTH_ERROR_HOST_TIMEOUT	equ (0x10)
BTH_ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER equ (0x11)
BTH_ERROR_INVALID_HCI_PARAMETER equ (0x12)
BTH_ERROR_REMOTE_USER_ENDED_CONNECTION equ (0x13)
BTH_ERROR_REMOTE_LOW_RESOURCES equ (0x14)
BTH_ERROR_REMOTE_POWERING_OFF equ (0x15)
BTH_ERROR_LOCAL_HOST_TERMINATED_CONNECTION equ (0x16)
BTH_ERROR_REPEATED_ATTEMPTS equ (0x17)
BTH_ERROR_PAIRING_NOT_ALLOWED equ (0x18)
BTH_ERROR_UKNOWN_LMP_PDU equ (0x19)
BTH_ERROR_UNSUPPORTED_REMOTE_FEATURE equ (0x1a)
BTH_ERROR_SCO_OFFSET_REJECTED equ (0x1b)
BTH_ERROR_SCO_INTERVAL_REJECTED equ (0x1c)
BTH_ERROR_SCO_AIRMODE_REJECTED equ (0x1d)
BTH_ERROR_INVALID_LMP_PARAMETERS equ (0x1e)
BTH_ERROR_UNSPECIFIED_ERROR equ (0x1f)
BTH_ERROR_UNSUPPORTED_LMP_PARM_VALUE equ (0x20)
BTH_ERROR_ROLE_CHANGE_NOT_ALLOWED equ (0x21)
BTH_ERROR_LMP_RESPONSE_TIMEOUT equ (0x22)
BTH_ERROR_LMP_TRANSACTION_COLLISION equ (0x23)
BTH_ERROR_LMP_PDU_NOT_ALLOWED equ (0x24)
BTH_ERROR_ENCRYPTION_MODE_NOT_ACCEPTABLE equ (0x25)
BTH_ERROR_UNIT_KEY_NOT_USED equ (0x26)
BTH_ERROR_QOS_IS_NOT_SUPPORTED equ (0x27)
BTH_ERROR_INSTANT_PASSED equ (0x28)
BTH_ERROR_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED equ (0x29)
BTH_ERROR_DIFFERENT_TRANSACTION_COLLISION equ (0x2a)
BTH_ERROR_QOS_UNACCEPTABLE_PARAMETER equ (0x2c)
BTH_ERROR_QOS_REJECTED	equ (0x2d)
BTH_ERROR_CHANNEL_CLASSIFICATION_NOT_SUPPORTED equ (0x2e)
BTH_ERROR_INSUFFICIENT_SECURITY equ (0x2f)
BTH_ERROR_PARAMETER_OUT_OF_MANDATORY_RANGE equ (0x30)
BTH_ERROR_ROLE_SWITCH_PENDING equ (0x32)
BTH_ERROR_RESERVED_SLOT_VIOLATION equ (0x34)
BTH_ERROR_ROLE_SWITCH_FAILED equ (0x35)
BTH_ERROR_EXTENDED_INQUIRY_RESPONSE_TOO_LARGE equ (0x36)
BTH_ERROR_SECURE_SIMPLE_PAIRING_NOT_SUPPORTED_BY_HOST equ (0x37)
BTH_ERROR_HOST_BUSY_PAIRING equ (0x38)
BTH_ERROR_CONNECTION_REJECTED_DUE_TO_NO_SUITABLE_CHANNEL_FOUND equ (0x39)
BTH_ERROR_CONTROLLER_BUSY equ (0x3a)
BTH_ERROR_UNACCEPTABLE_CONNECTION_INTERVAL equ (0x3b)
BTH_ERROR_DIRECTED_ADVERTISING_TIMEOUT equ (0x3c)
BTH_ERROR_CONNECTION_TERMINATED_DUE_TO_MIC_FAILURE equ (0x3d)
BTH_ERROR_CONNECTION_FAILED_TO_BE_ESTABLISHED equ (0x3e)
BTH_ERROR_MAC_CONNECTION_FAILED equ (0x3f)

BTH_ERROR_UNSPECIFIED	equ 0xFF

L2CAP_MIN_MTU		equ 48
L2CAP_MAX_MTU		equ 0xFFFF
L2CAP_DEFAULT_MTU	equ 672

MAX_L2CAP_PING_DATA_LENGTH equ 44
MAX_L2CAP_INFO_DATA_LENGTH equ 44

BDIF_ADDRESS		equ 0x00000001
BDIF_COD		equ 0x00000002
BDIF_NAME		equ 0x00000004
BDIF_PAIRED		equ 0x00000008
BDIF_PERSONAL		equ 0x00000010
BDIF_CONNECTED		equ 0x00000020

if (NTDDI_VERSION GT NTDDI_VISTASP1 OR (NTDDI_VERSION EQ NTDDI_VISTASP1 AND defined(VISTA_KB942567)))
BDIF_SHORT_NAME		equ 0x00000040
BDIF_VISIBLE		equ 0x00000080
BDIF_SSP_SUPPORTED	equ 0x00000100
BDIF_SSP_PAIRED		equ 0x00000200
BDIF_SSP_MITM_PROTECTED equ 0x00000400
BDIF_RSSI		equ 0x00001000
BDIF_EIR		equ 0x00002000
if  (NTDDI_VERSION GE NTDDI_WIN8)
BDIF_BR			equ 0x00004000
BDIF_LE			equ 0x00008000
BDIF_LE_PAIRED		equ 0x00010000
BDIF_LE_PERSONAL	equ 0x00020000
BDIF_LE_MITM_PROTECTED	equ 0x00040000
BDIF_LE_PRIVACY_ENABLED equ 0x00080000
BDIF_LE_RANDOM_ADDRESS_TYPE equ 0x00100000
BDIF_VALID_FLAGS	equ (BDIF_COD or BDIF_NAME or BDIF_PAIRED or BDIF_PERSONAL or BDIF_ADDRESS or BDIF_SHORT_NAME or BDIF_VISIBLE or BDIF_RSSI or BDIF_EIR or BDIF_SSP_PAIRED or BDIF_SSP_MITM_PROTECTED or BDIF_CONNECTED or BDIF_LE or BDIF_LE_PAIRED or BDIF_LE_PERSONAL or BDIF_LE_MITM_PROTECTED or BDIF_LE_PRIVACY_ENABLED or BDIF_LE_RANDOM_ADDRESS_TYPE or BDIF_BR)
else
BDIF_VALID_FLAGS	equ (BDIF_ADDRESS or BDIF_COD or BDIF_NAME or BDIF_PAIRED or BDIF_PERSONAL or BDIF_SHORT_NAME or BDIF_VISIBLE or BDIF_RSSI or BDIF_EIR or BDIF_SSP_PAIRED or BDIF_SSP_MITM_PROTECTED or BDIF_CONNECTED)
endif
else
BDIF_VALID_FLAGS	equ (BDIF_ADDRESS or BDIF_COD or BDIF_NAME or BDIF_PAIRED or BDIF_PERSONAL)
endif


BTH_DEVICE_INFO		STRUC
flags			ULONG ?
address			BTH_ADDR ?
classOfDevice		BTH_COD ?
name			CHAR BTH_MAX_NAME_SIZE dup(?)
BTH_DEVICE_INFO		ENDS
PBTH_DEVICE_INFO	typedef ptr BTH_DEVICE_INFO

BTH_RADIO_IN_RANGE	STRUC
deviceInfo		BTH_DEVICE_INFO <>
previousDeviceFlags	ULONG ?
BTH_RADIO_IN_RANGE	ENDS
PBTH_RADIO_IN_RANGE	typedef ptr BTH_RADIO_IN_RANGE

BTH_L2CAP_EVENT_INFO	STRUC
bthAddress		BTH_ADDR ?
psm			USHORT ?
connected		UCHAR ?
initiated		UCHAR ?
BTH_L2CAP_EVENT_INFO	ENDS
PBTH_L2CAP_EVENT_INFO	typedef ptr BTH_L2CAP_EVENT_INFO

HCI_CONNECTION_TYPE_ACL equ (1)
HCI_CONNECTION_TYPE_SCO equ (2)
HCI_CONNECTION_TYPE_LE	equ (3)

HCI_CONNNECTION_TYPE_ACL equ HCI_CONNECTION_TYPE_AC
HCI_CONNNECTION_TYPE_SCO equ HCI_CONNECTION_TYPE_SCO


BTH_HCI_EVENT_INFO	STRUC
bthAddress		BTH_ADDR ?
connectionType		UCHAR ?
connected		UCHAR ?
BTH_HCI_EVENT_INFO	ENDS
PBTH_HCI_EVENT_INFO	typedef ptr BTH_HCI_EVENT_INFO


if (NTDDI_VERSION GT NTDDI_VISTASP1 OR (NTDDI_VERSION EQ NTDDI_VISTASP1 AND defined(VISTA_KB942567)))

.enum IO_CAPABILITY {
    IoCaps_DisplayOnly	   = 0x00,
    IoCaps_DisplayYesNo	   = 0x01,
    IoCaps_KeyboardOnly	   = 0x02,
    IoCaps_NoInputNoOutput = 0x03,
    IoCaps_Undefined	   = 0xff
    }

.enum AUTHENTICATION_REQUIREMENTS {
    MITMProtectionNotRequired		    = 0x00,
    MITMProtectionRequired		    = 0x01,
    MITMProtectionNotRequiredBonding	    = 0x02,
    MITMProtectionRequiredBonding	    = 0x03,
    MITMProtectionNotRequiredGeneralBonding = 0x04,
    MITMProtectionRequiredGeneralBonding    = 0x05,
    MITMProtectionNotDefined		    = 0xff
    }

IsMITMProtectionRequired macro requirements
	exitm<((MITMProtectionRequired == requirements) || (MITMProtectionRequiredBonding == requirements) || (MITMProtectionRequiredGeneralBonding == requirements))>
	endm

endif

BTH_MAX_SERVICE_NAME_SIZE equ (256)
MAX_UUIDS_IN_QUERY	equ (12)
BTH_VID_DEFAULT_VALUE	equ (0xFFFF)

SDP_ERROR_INVALID_SDP_VERSION equ (0x0001)
SDP_ERROR_INVALID_RECORD_HANDLE equ (0x0002)
SDP_ERROR_INVALID_REQUEST_SYNTAX equ (0x0003)
SDP_ERROR_INVALID_PDU_SIZE equ (0x0004)
SDP_ERROR_INVALID_CONTINUATION_STATE equ (0x0005)
SDP_ERROR_INSUFFICIENT_RESOURCES equ (0x0006)
SDP_ERROR_SUCCESS	equ (0x0000)
SDP_ERROR_SERVER_INVALID_RESPONSE equ (0x0100)
SDP_ERROR_SERVER_RESPONSE_DID_NOT_PARSE equ (0x0200)
SDP_ERROR_SERVER_BAD_FORMAT equ (0x0300)
SDP_ERROR_COULD_NOT_SEND_CONTINUE equ (0x0400)
SDP_ERROR_RESPONSE_TOO_LARGE equ (0x0500)


SDP_ATTRIB_RECORD_HANDLE equ (0x0000)
SDP_ATTRIB_CLASS_ID_LIST equ (0x0001)
SDP_ATTRIB_RECORD_STATE equ (0x0002)
SDP_ATTRIB_SERVICE_ID	equ (0x0003)
SDP_ATTRIB_PROTOCOL_DESCRIPTOR_LIST equ (0x0004)
SDP_ATTRIB_BROWSE_GROUP_LIST equ (0x0005)
SDP_ATTRIB_LANG_BASE_ATTRIB_ID_LIST equ (0x0006)
SDP_ATTRIB_INFO_TIME_TO_LIVE equ (0x0007)
SDP_ATTRIB_AVAILABILITY equ (0x0008)
SDP_ATTRIB_PROFILE_DESCRIPTOR_LIST equ (0x0009)
SDP_ATTRIB_DOCUMENTATION_URL equ (0x000A)
SDP_ATTRIB_CLIENT_EXECUTABLE_URL equ (0x000B)
SDP_ATTRIB_ICON_URL	equ (0x000C)
SDP_ATTRIB_ADDITIONAL_PROTOCOL_DESCRIPTOR_LIST equ (0x000D)

SDP_ATTRIB_PROFILE_SPECIFIC equ (0x0200)

LANG_BASE_LANGUAGE_INDEX equ (0x0000)
LANG_BASE_ENCODING_INDEX equ (0x0001)
LANG_BASE_OFFSET_INDEX	equ (0x0002)
LANG_DEFAULT_ID		equ (0x0100)

LANGUAGE_EN_US		equ (0x656E)
ENCODING_UTF_8		equ (0x006A)

STRING_NAME_OFFSET	equ (0x0000)
STRING_DESCRIPTION_OFFSET equ (0x0001)
STRING_PROVIDER_NAME_OFFSET equ (0x0002)

SDP_ATTRIB_SDP_VERSION_NUMBER_LIST equ (0x0200)
SDP_ATTRIB_SDP_DATABASE_STATE equ (0x0201)

SDP_ATTRIB_BROWSE_GROUP_ID equ (0x0200)

SDP_ATTRIB_CORDLESS_EXTERNAL_NETWORK equ (0x0301)

SDP_ATTRIB_FAX_CLASS_1_SUPPORT equ (0x0302)
SDP_ATTRIB_FAX_CLASS_2_0_SUPPORT equ (0x0303)
SDP_ATTRIB_FAX_CLASS_2_SUPPORT equ (0x0304)
SDP_ATTRIB_FAX_AUDIO_FEEDBACK_SUPPORT equ (0x0305)

SDP_ATTRIB_HEADSET_REMOTE_AUDIO_VOLUME_CONTROL equ (0x0302)

SDP_ATTRIB_LAN_LPSUBNET equ (0x0200)

SDP_ATTRIB_OBJECT_PUSH_SUPPORTED_FORMATS_LIST equ (0x0303)

SDP_ATTRIB_SYNCH_SUPPORTED_DATA_STORES_LIST equ (0x0301)

SDP_ATTRIB_SERVICE_VERSION equ (0x0300)

SDP_ATTRIB_PAN_NETWORK_ADDRESS equ (0x0306)
SDP_ATTRIB_PAN_WAP_GATEWAY equ (0x0307)
SDP_ATTRIB_PAN_HOME_PAGE_URL equ (0x0308)
SDP_ATTRIB_PAN_WAP_STACK_TYPE equ (0x0309)
SDP_ATTRIB_PAN_SECURITY_DESCRIPTION equ (0x030A)
SDP_ATTRIB_PAN_NET_ACCESS_TYPE equ (0x030B)
SDP_ATTRIB_PAN_MAX_NET_ACCESS_RATE equ (0x030C)

SDP_ATTRIB_IMAGING_SUPPORTED_CAPABILITIES equ (0x0310)
SDP_ATTRIB_IMAGING_SUPPORTED_FEATURES equ (0x0311)
SDP_ATTRIB_IMAGING_SUPPORTED_FUNCTIONS equ (0x0312)
SDP_ATTRIB_IMAGING_TOTAL_DATA_CAPACITY equ (0x0313)

SDP_ATTRIB_DI_SPECIFICATION_ID equ (0x0200)
SDP_ATTRIB_DI_VENDOR_ID equ (0x0201)
SDP_ATTRIB_DI_PRODUCT_ID equ (0x0202)
SDP_ATTRIB_DI_VERSION	equ (0x0203)
SDP_ATTRIB_DI_PRIMARY_RECORD equ (0x0204)
SDP_ATTRIB_DI_VENDOR_ID_SOURCE equ (0x0205)

SDP_ATTRIB_HID_DEVICE_RELEASE_NUMBER equ (0x0200)
SDP_ATTRIB_HID_PARSER_VERSION equ (0x0201)
SDP_ATTRIB_HID_DEVICE_SUBCLASS equ (0x0202)
SDP_ATTRIB_HID_COUNTRY_CODE equ (0x0203)
SDP_ATTRIB_HID_VIRTUAL_CABLE equ (0x0204)
SDP_ATTRIB_HID_RECONNECT_INITIATE equ (0x0205)
SDP_ATTRIB_HID_DESCRIPTOR_LIST equ (0x0206)
SDP_ATTRIB_HID_LANG_ID_BASE_LIST equ (0x0207)
SDP_ATTRIB_HID_SDP_DISABLE equ (0x0208)
SDP_ATTRIB_HID_BATTERY_POWER equ (0x0209)
SDP_ATTRIB_HID_REMOTE_WAKE equ (0x020A)
SDP_ATTRIB_HID_PROFILE_VERSION equ (0x020B)
SDP_ATTRIB_HID_SUPERVISION_TIMEOUT equ (0x020C)
SDP_ATTRIB_HID_NORMALLY_CONNECTABLE equ (0x020D)
SDP_ATTRIB_HID_BOOT_DEVICE equ (0x020E)
SDP_ATTRIB_HID_SSR_HOST_MAX_LATENCY equ (0x020F)
SDP_ATTRIB_HID_SSR_HOST_MIN_TIMEOUT equ (0x0210)

CORDLESS_EXTERNAL_NETWORK_PSTN equ (0x01)
CORDLESS_EXTERNAL_NETWORK_ISDN equ (0x02)
CORDLESS_EXTERNAL_NETWORK_GSM equ (0x03)
CORDLESS_EXTERNAL_NETWORK_CDMA equ (0x04)
CORDLESS_EXTERNAL_NETWORK_ANALOG_CELLULAR equ (0x05)
CORDLESS_EXTERNAL_NETWORK_PACKET_SWITCHED equ (0x06)
CORDLESS_EXTERNAL_NETWORK_OTHER equ (0x07)

OBJECT_PUSH_FORMAT_VCARD_2_1 equ (0x01)
OBJECT_PUSH_FORMAT_VCARD_3_0 equ (0x02)
OBJECT_PUSH_FORMAT_VCAL_1_0 equ (0x03)
OBJECT_PUSH_FORMAT_ICAL_2_0 equ (0x04)
OBJECT_PUSH_FORMAT_VNOTE equ (0x05)
OBJECT_PUSH_FORMAT_VMESSAGE equ (0x06)
OBJECT_PUSH_FORMAT_ANY	equ (0xFF)

SYNCH_DATA_STORE_PHONEBOOK equ (0x01)
SYNCH_DATA_STORE_CALENDAR equ (0x03)
SYNCH_DATA_STORE_NOTES	equ (0x05)
SYNCH_DATA_STORE_MESSAGES equ (0x06)

DI_VENDOR_ID_SOURCE_BLUETOOTH_SIG equ (0x0001)
DI_VENDOR_ID_SOURCE_USB_IF equ (0x0002)

PSM_SDP			equ (0x0001)
PSM_RFCOMM		equ (0x0003)
PSM_TCS_BIN		equ (0x0005)
PSM_TCS_BIN_CORDLESS	equ (0x0007)
PSM_BNEP		equ (0x000F)
PSM_HID_CONTROL		equ (0x0011)
PSM_HID_INTERRUPT	equ (0x0013)
PSM_AVCTP		equ (0x0017)
PSM_AVDTP		equ (0x0019)
PSM_UDI_C_PLANE		equ (0x001D)

STR_ADDR_FMTA		equ <"(%02x:%02x:%02x:%02x:%02x:%02x)">
STR_ADDR_FMTW		equ <L"(%02x:%02x:%02x:%02x:%02x:%02x)">

STR_ADDR_SHORT_FMTA	equ <"%04x%08x">
STR_ADDR_SHORT_FMTW	equ <L"%04x%08x">

STR_USBHCI_CLASS_HARDWAREIDA equ <"USB\\Class_E0 AND SubClass_01 AND Prot_01">
STR_USBHCI_CLASS_HARDWAREIDW equ <L"USB\\Class_E0 AND SubClass_01 AND Prot_01">

if defined(_UNICODE) OR defined(BTH_KERN)
STR_ADDR_FMT		equ <STR_ADDR_FMTW>
STR_ADDR_SHORT_FMT	equ <STR_ADDR_SHORT_FMTW>
STR_USBHCI_CLASS_HARDWAREID equ <STR_USBHCI_CLASS_HARDWAREIDW>
else
STR_ADDR_FMT		equ <STR_ADDR_FMTA>
STR_ADDR_SHORT_FMT	equ <STR_ADDR_SHORT_FMTA>
STR_USBHCI_CLASS_HARDWAREID equ <STR_USBHCI_CLASS_HARDWAREIDA>
endif

GET_BITS macro field,offset,mask
	exitm<( ( (field) SHR (offset) ) AND (mask) )>
	endm
GET_BIT macro field,offset
	exitm<( GET_BITS(field,offset,0x1) )>
	endm

LMP_3_SLOT_PACKETS macro x
	exitm<(GET_BIT(x, 0))>
	endm
LMP_5_SLOT_PACKETS macro x
	exitm<(GET_BIT(x, 1))>
	endm
LMP_ENCRYPTION macro x
	exitm<(GET_BIT(x, 2))>
	endm
LMP_SLOT_OFFSET macro x
	exitm<(GET_BIT(x, 3))>
	endm
LMP_TIMING_ACCURACY macro x
	exitm<(GET_BIT(x, 4))>
	endm
LMP_SWITCH macro x
	exitm<(GET_BIT(x, 5))>
	endm
LMP_HOLD_MODE macro x
	exitm<(GET_BIT(x, 6))>
	endm
LMP_SNIFF_MODE macro x
	exitm<(GET_BIT(x, 7))>
	endm
LMP_PARK_MODE macro x
	exitm<(GET_BIT(x, 8))>
	endm
LMP_RSSI macro x
	exitm<(GET_BIT(x, 9))>
	endm
LMP_CHANNEL_QUALITY_DRIVEN_MODE macro x
	exitm<(GET_BIT(x,10))>
	endm
LMP_SCO_LINK macro x
	exitm<(GET_BIT(x,11))>
	endm
LMP_HV2_PACKETS macro x
	exitm<(GET_BIT(x,12))>
	endm
LMP_HV3_PACKETS macro x
	exitm<(GET_BIT(x,13))>
	endm
LMP_MU_LAW_LOG macro x
	exitm<(GET_BIT(x,14))>
	endm
LMP_A_LAW_LOG macro x
	exitm<(GET_BIT(x,15))>
	endm
LMP_CVSD macro x
	exitm<(GET_BIT(x,16))>
	endm
LMP_PAGING_SCHEME macro x
	exitm<(GET_BIT(x,17))>
	endm
LMP_POWER_CONTROL macro x
	exitm<(GET_BIT(x,18))>
	endm
LMP_TRANSPARENT_SCO_DATA macro x
	exitm<(GET_BIT(x,19))>
	endm
LMP_FLOW_CONTROL_LAG macro x
	exitm<(GET_BITS(x,20,0x3))>
	endm
LMP_BROADCAST_ENCRYPTION macro x
	exitm<(GET_BIT(x,23))>
	endm
LMP_ENHANCED_DATA_RATE_ACL_2MBPS_MODE macro x
	exitm<(GET_BIT(x,25))>
	endm
LMP_ENHANCED_DATA_RATE_ACL_3MBPS_MODE macro x
	exitm<(GET_BIT(x,26))>
	endm
LMP_ENHANCED_INQUIRY_SCAN macro x
	exitm<(GET_BIT(x,27))>
	endm
LMP_INTERLACED_INQUIRY_SCAN macro x
	exitm<(GET_BIT(x,28))>
	endm
LMP_INTERLACED_PAGE_SCAN macro x
	exitm<(GET_BIT(x,29))>
	endm
LMP_RSSI_WITH_INQUIRY_RESULTS macro x
	exitm<(GET_BIT(x,30))>
	endm
LMP_ESCO_LINK macro x
	exitm<(GET_BIT(x,31))>
	endm
LMP_EV4_PACKETS macro x
	exitm<(GET_BIT(x,32))>
	endm
LMP_EV5_PACKETS macro x
	exitm<(GET_BIT(x,33))>
	endm
LMP_AFH_CAPABLE_SLAVE macro x
	exitm<(GET_BIT(x,35))>
	endm
LMP_AFH_CLASSIFICATION_SLAVE macro x
	exitm<(GET_BIT(x,36))>
	endm
LMP_BR_EDR_NOT_SUPPORTED macro x
	exitm<(GET_BIT(x,37))>
	endm
LMP_LE_SUPPORTED macro x
	exitm<(GET_BIT(x,38))>
	endm
LMP_3SLOT_EDR_ACL_PACKETS macro x
	exitm<(GET_BIT(x,39))>
	endm
LMP_5SLOT_EDR_ACL_PACKETS macro x
	exitm<(GET_BIT(x,40))>
	endm
LMP_SNIFF_SUBRATING macro x
	exitm<(GET_BIT(x,41))>
	endm
LMP_PAUSE_ENCRYPTION macro x
	exitm<(GET_BIT(x,42))>
	endm
LMP_AFH_CAPABLE_MASTER macro x
	exitm<(GET_BIT(x,43))>
	endm
LMP_AFH_CLASSIFICATION_MASTER macro x
	exitm<(GET_BIT(x,44))>
	endm
LMP_EDR_ESCO_2MBPS_MODE macro x
	exitm<(GET_BIT(x,45))>
	endm
LMP_EDR_ESCO_3MBPS_MODE macro x
	exitm<(GET_BIT(x,46))>
	endm
LMP_3SLOT_EDR_ESCO_PACKETS macro x
	exitm<(GET_BIT(x,47))>
	endm
LMP_EXTENDED_INQUIRY_RESPONSE macro x
	exitm<(GET_BIT(x,48))>
	endm
LMP_SIMULT_LE_BR_TO_SAME_DEV macro x
	exitm<(GET_BIT(x,49))>
	endm
LMP_SECURE_SIMPLE_PAIRING macro x
	exitm<(GET_BIT(x,51))>
	endm
LMP_ENCAPSULATED_PDU macro x
	exitm<(GET_BIT(x,52))>
	endm
LMP_ERRONEOUS_DATA_REPORTING macro x
	exitm<(GET_BIT(x,53))>
	endm
LMP_NON_FLUSHABLE_PACKET_BOUNDARY_FLAG macro x
	exitm<(GET_BIT(x,54))>
	endm
LMP_LINK_SUPERVISION_TIMEOUT_CHANGED_EVENT macro x
	exitm<(GET_BIT(x,56))>
	endm
LMP_INQUIRY_RESPONSE_TX_POWER_LEVEL macro x
	exitm<(GET_BIT(x,57))>
	endm
LMP_EXTENDED_FEATURES macro x
	exitm<(GET_BIT(x,63))>
	endm

endif ;; GUID_DEFS_ONLY
endif ;; (NTDDI_VERSION GE NTDDI_WINXPSP2)
endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif ;; __BTHDEF_H__

