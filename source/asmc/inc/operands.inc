; OPERANDS.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; parser/code generator operand definitions.
; This file is included by parser.inc
;
.pragma list(push, 0)
ifndef OPERANDS_H
define OPERANDS_H

; v1.96: OP_J32 (for far CALL/JMP) has been removed, now used for OP_I64.
; v2.04: 2 bits freed ( OP_CR, OP_DR and OP_TR replaced by OP_SPECREG )
; Also OP_SPECREG, OP_SRxx and OP_STxx moved just behind the other
; register operands.
; Note: register-related flags must be in bits 0-15, because register items
; in SpecialTable[] have these bits stored in a uint field (JWASMR!).


OP_NONE		equ 0x00000000
OP_R8		equ 0x00000001
OP_R16		equ 0x00000002
OP_R32		equ 0x00000004
OP_R64		equ 0x00000008
OP_XMM		equ 0x00000010
OP_YMM		equ 0x00000020
OP_ZMM		equ 0x00000040
OP_A		equ 0x00000080 ; AL, AX, EAX, RAX registers
OP_M08		equ 0x00000100
OP_M16		equ 0x00000200
OP_M32		equ 0x00000400
OP_M64		equ 0x00000800
OP_M128		equ 0x00001000
OP_M256		equ 0x00002000
OP_M512		equ 0x00004000
OP_MMX		equ 0x00008000
OP_I8		equ 0x00010000
OP_I16		equ 0x00020000
OP_I32		equ 0x00040000
OP_I64		equ 0x00080000
OP_K		equ 0x00100000 ; Mask reg
OP_M48		equ 0x00200000
OP_M80		equ 0x00400000
OP_CL_ONLY	equ 0x00800000 ; CL register
OP_DX_ONLY	equ 0x01000000 ; DX register
OP_RSPEC	equ 0x02000000 ; CRx, DRx, TRx registers
OP_SR86		equ 0x04000000 ; CS, DS, ES, SS registers
OP_SR386	equ 0x08000000 ; FS, GS registers
OP_ST		equ 0x10000000 ; ST0 register
OP_ST_REG	equ 0x20000000 ; ST1-ST7 registers
OP_I48		equ 0x40000000 ; used for immediate FAR call/jmp

; OP_I_1, OP_I_3 and OP_I8_U aren't flags. They are
; used as values in SWITCH statements only. It's possible to
; "compress" them if room for another flag is needed

OP_I_1		equ 0x00200000 or OP_I8
OP_I_3		equ 0x00400000 or OP_I8
OP_I8_U		equ 0x00800000 or OP_I8 or OP_I16 or OP_I32

OP_AL		equ OP_A or OP_R8
OP_AX		equ OP_A or OP_R16
OP_EAX		equ OP_A or OP_R32
OP_RAX		equ OP_A or OP_R64
OP_RIP		equ 16 or OP_RSPEC
OP_CL		equ OP_CL_ONLY or OP_R8
OP_DX		equ OP_DX_ONLY or OP_R16
OP_RGT8		equ OP_R16 or OP_R32 or OP_R64
OP_RGT16	equ OP_R32 or OP_R64
OP_R		equ OP_R8 or OP_R16 or OP_R32 or OP_R64
OP_SR		equ OP_SR86 or OP_SR386
OP_STI		equ OP_ST or OP_ST_REG

OP_I		equ OP_I8 or OP_I16 or OP_I32
OP_IGE8		equ OP_I8 or OP_I16 or OP_I32
OP_IGE16	equ OP_I16 or OP_I32
OP_I_ANY	equ OP_I or OP_I64 or OP_I48
OP_IS		equ OP_I or OP_I64 ; crecord

OP_MGT8		equ OP_M16 or OP_M32 or OP_M64
OP_MGT16	equ OP_M32 or OP_M64
OP_MFPTR	equ OP_M32 or OP_M48 or OP_M80
OP_M_ANY	equ OP_M08 or OP_M16 or OP_M32 or OP_M64 or OP_M128 or OP_M256 or OP_M512 or OP_M48 or OP_M80
OP_M		equ OP_M08 or OP_M16 or OP_M32 or OP_M64 or OP_M80 or OP_M128

; v2.06: items in instruction table now use OP_MS instead of OP_M
OP_MS		equ OP_M08 or OP_M16 or OP_M32 or OP_M64

; since v2.06, this is a 8-bit field. Previously it was 4-bit only.

OP3_NONE	equ 0		; must be 0, identical to OP_NONE
OP3_CL		equ 1
OP3_I8_U	equ 2		; this is also used for signed values (IMUL)
OP3_XMM0	equ 3		; v2.01: introduced with SSE4.1
OP3_I		equ 4		; v2.06: added to avoid the IMUL hack
OP3_HID		equ 5		; hidden data ( CMPxxx[PD|PS|SD|SS]

OP3_XMM		equ OP3_XMM0	; for VEX encoding only
OP3_YMM		equ OP3_XMM0
OP3_ZMM		equ OP3_XMM0
OP3_K		equ OP3_XMM0
OP3_RGT16	equ OP3_XMM0
OP3_R_MS	equ OP3_XMM0
OP3_XMM_M128	equ OP3_XMM0

endif
.pragma list(pop)
