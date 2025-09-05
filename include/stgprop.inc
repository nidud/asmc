ifndef _STGPROP_H_
define _STGPROP_H_

ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

PSGUID_STORAGE equ <{ 0xb725f130, 0x47ef, 0x101a, { 0xa5, 0xf1, 0x02, 0x60, 0x8c, 0x9e, 0xeb, 0xac } }>

PID_STG_DIRECTORY               equ 0x00000002

PID_STG_CLASSID                 equ 0x00000003
PID_STG_STORAGETYPE             equ 0x00000004

PID_STG_VOLUME_ID               equ 0x00000005
PID_STG_PARENT_WORKID           equ 0x00000006
PID_STG_SECONDARYSTORE          equ 0x00000007

PID_STG_FILEINDEX               equ 0x00000008
PID_STG_LASTCHANGEUSN           equ 0x00000009
PID_STG_NAME                    equ 0x0000000a
PID_STG_PATH                    equ 0x0000000b

PID_STG_SIZE                    equ 0x0000000c
PID_STG_ATTRIBUTES              equ 0x0000000d
PID_STG_WRITETIME               equ 0x0000000e
PID_STG_CREATETIME              equ 0x0000000f
PID_STG_ACCESSTIME              equ 0x00000010
PID_STG_CHANGETIME              equ 0x00000011
PID_STG_ALLOCSIZE               equ 0x00000012

PID_STG_CONTENTS                equ 0x00000013
PID_STG_SHORTNAME               equ 0x00000014

PID_STG_FRN                     equ 0x00000015
PID_STG_SCOPE                   equ 0x00000016

PID_STG_MAX                     equ PID_STG_SCOPE

CSTORAGEPROPERTY                equ 0x17

endif
endif
