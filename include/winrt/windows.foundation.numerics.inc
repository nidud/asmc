ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Efoundation2Enumerics_h__
define __windows2Efoundation2Enumerics_h__

ifndef __windows2Efoundation2Enumerics_p_h__
define __windows2Efoundation2Enumerics_p_h__

ifndef SPECIFIC_API_CONTRACT_DEFINITIONS
ifndef WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION
define WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION 0x40000
endif
ifndef WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION
define WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION 0x130000
endif
endif
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
ifndef __windowscontracts_h__
include windowscontracts.inc
endif

.namespace Windows
.namespace Foundation
.namespace Numerics

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000

.template Matrix3x2
    M11		real4 ?
    M12		real4 ?
    M21		real4 ?
    M22		real4 ?
    M31		real4 ?
    M32		real4 ?
   .ends

.template Matrix4x4
    M11		real4 ?
    M12		real4 ?
    M13		real4 ?
    M14		real4 ?
    M21		real4 ?
    M22		real4 ?
    M23		real4 ?
    M24		real4 ?
    M31		real4 ?
    M32		real4 ?
    M33		real4 ?
    M34		real4 ?
    M41		real4 ?
    M42		real4 ?
    M43		real4 ?
    M44		real4 ?
   .ends

.template Vector3
    X		real4 ?
    Y		real4 ?
    Z		real4 ?
   .ends

.template Plane
    Numerics	Windows::Foundation::Numerics::Vector3 <>
    D		real4 ?
   .ends

.template Quaternion
    X		real4 ?
    Y		real4 ?
    Z		real4 ?
    W		real4 ?
   .ends

.template Rational
    Numerator	UINT32 ?
    Denominator UINT32 ?
   .ends

.template Vector2
    X		real4 ?
    Y		real4 ?
   .ends

.template Vector4
    X		real4 ?
    Y		real4 ?
    Z		real4 ?
    W		real4 ?
   .ends

endif

.endn
.endn
.endn

endif

endif
