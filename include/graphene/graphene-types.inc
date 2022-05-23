ifndef __GRAPHENE_TYPES_H__
define __GRAPHENE_TYPES_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

include graphene/graphene-config.inc
include graphene/graphene-macros.inc
include graphene/graphene-version-macros.inc

define GRAPHENE_VEC2_LEN       2
define GRAPHENE_VEC3_LEN       3
define GRAPHENE_VEC4_LEN       4

endif
