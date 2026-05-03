ifndef __GRAPHENE_MACROS_H__
define __GRAPHENE_MACROS_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

define GRAPHENE_VECTORCALL   <vectorcall>

bool typedef sdword
define false 0
define true 1

define GRAPHENE_PI             3.1415926535897932384626434f
define GRAPHENE_PI_2           1.5707963267948966192313217f

endif
