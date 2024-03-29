ifndef _DLNAERROR_H
define _DLNAERROR_H

STATUS_SEVERITY macro hr
	exitm<(((hr) SHR 30) AND 0x3)>
	endm

define FACILITY_NS_WIN32		0x7
define FACILITY_NS			0xD
define STATUS_SEVERITY_WARNING		0x2
define STATUS_SEVERITY_SUCCESS		0x0
define STATUS_SEVERITY_INFORMATIONAL	0x1
define STATUS_SEVERITY_ERROR		0x3
define DLNA_E_NOT_FOUND			0xC00DC350
define DLNA_E_NOT_AVAILABLE		0xC00DC351
define DLNA_E_OPERATION_CANCELLED	0xC00DC352
define DLNA_E_UNAUTHORIZED		0xC00DC353
define DLNA_E_OUT_OF_RANGE		0xC00DC354
define DLNA_E_INVALID_DIDL_LITE_RESPONSE 0xC00DC355
define DLNA_E_DIDL_VALUE_NOT_FOUND	0xC00DC356
define DLNA_E_DIDL_VALUE_INVALID	0xC00DC357
define DLNA_E_INVALID_DEVICE_RESPONSE	0xC00DC358
define DLNA_E_INVALID_LAST_CHANGE_RESPONSE 0xC00DC359
define DLNA_E_INVALID_PROTOCOL_INFO	0xC00DC35A
define DLNA_E_SERVICE_NOT_FOUND		0xC00DC35B
define DLNA_E_NO_SERVICES_ON_DEVICE	0xC00DC35C
define DLNA_E_DEVICE_UNAVAILABLE	0xC00DC35D
define DLNA_E_DEVICE_NOT_FOUND		0xC00DC35E
define DLNA_E_SERVER_NOT_FOUND		0xC00DC35F
define DLNA_E_RENDERER_NOT_FOUND	0xC00DC360
define DLNA_E_NO_COMPATIBLE_RES_ELEMENT_FOUND 0xC00DC3B4
define DLNA_E_UNSUPPORTED_FORMAT	0xC00DC3B5
define DLNA_E_RENDERER_FAILED_TO_PLAY	0xC00DC3B6
define DLNA_E_DRM_PLAYBACK_FAILURE	0xC00DC3B7

endif
