ifndef FREETYPE_CONFIG_MAC_SUPPORT_H_
define FREETYPE_CONFIG_MAC_SUPPORT_H_

if defined( __APPLE__ ) OR ( defined( __MWERKS__ ) AND defined( macintosh ) )
include errno.inc
ifdef ECANCELED
include AvailabilityMacros.inc
endif
if defined( __LP64__ ) AND ( MAC_OS_X_VERSION_MIN_REQUIRED LE MAC_OS_X_VERSION_10_4 )
undef FT_MACINTOSH
endif
elseif defined( __SC__ ) OR defined( __MRC__ )
include ConditionalMacros.inc
if TARGET_OS_MAC
define FT_MACINTOSH 1
endif
endif
endif
