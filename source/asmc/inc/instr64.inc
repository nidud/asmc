; INSTR64.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; instructions which are to be replaced in long-mode

; tok (suffix) op1-3 byte1_info opnd_dir rm_info opcode rm_byte cpu  prefix evex

insa(CALL, call,  1, OpCls( I32,     NONE,	  NONE ), 0,	   0,  no_RM,  0xE8, 0x00, P_64,  0, 0, 0, 0)
insa(CALL, 1,	  0, OpCls( R64_M64, NONE,	  NONE ), 0,	   0,  no_WDS, 0xFF, 0x10, P_64,  0, 0, 0, 0)

; FAR call
insa(CALL, 3,	  3, OpCls( M32,     NONE,	  NONE ), F_16,	   0,  no_WDS, 0xFF, 0x18, P_64,  0, 0, 0, 0)
insa(CALL, 4,	  0, OpCls( M48,     NONE,	  NONE ), 0,	   0,  no_WDS, 0xFF, 0x18, P_64,  0, 0, 0, 0)
insa(CALL, 5,	  0, OpCls( M80,     NONE,	  NONE ), F_48,	   0,  no_WDS, 0xFF, 0x18, P_64,  0, 0, 0, 0)
insa(JMP, jmp,	  1, OpCls( I8,	     NONE,	  NONE ), 0,	   0,  no_RM,  0xEB, 0x00, P_86,  0, 0, 0, 0)
insa(JMP, 1,	  0, OpCls( I32,     NONE,	  NONE ), 0,	   0,  no_RM,  0xE9, 0x00, P_64,  0, 0, 0, 0)
insa(JMP, 2,	  0, OpCls( R64_M64, NONE,	  NONE ), 0,	   0,  no_WDS, 0xFF, 0x20, P_64,  0, 0, 0, 0)

; FAR jmp
insa(JMP, 4,	  3, OpCls( M32,     NONE,	  NONE ), F_16,	   0,  no_WDS, 0xFF, 0x28, P_64,  0, 0, 0, 0)
insa(JMP, 5,	  0, OpCls( M48,     NONE,	  NONE ), 0,	   0,  no_WDS, 0xFF, 0x28, P_64,  0, 0, 0, 0)
insa(JMP, 6,	  0, OpCls( M80,     NONE,	  NONE ), F_48,	   0,  no_WDS, 0xFF, 0x28, P_64,  0, 0, 0, 0)
insa(LGDT, lgdt,  1, OpCls( M80,     NONE,	  NONE ), F_0F,	   0,  no_WDS, 0x01, 0x10, P_64,  0, 0, 0, 0)
insa(LIDT, lidt,  1, OpCls( M80,     NONE,	  NONE ), F_0F,	   0,  no_WDS, 0x01, 0x18, P_64,  0, 0, 0, 0)

insa(SLDT, sldt,  1, OpCls( RGT8,    NONE,	  NONE ), F_0F,	   0,  no_WDS, 0x00, 0x00, P_64,  0, 0, 0, 0)
insa(SLDT, 1,	  0, OpCls( M16,     NONE,	  NONE ), F_0FNO66,0,  no_WDS, 0x00, 0x00, P_286, 0, 0, 0, 0)
insa(SMSW, smsw,  1, OpCls( RGT8,    NONE,	  NONE ), F_0F,	   0,  no_WDS, 0x01, 0x20, P_64,  0, 0, 0, 0)
insa(SMSW, 1,	  0, OpCls( M16,     NONE,	  NONE ), F_0FNO66,0,  no_WDS, 0x01, 0x20, P_286, 0, 0, 0, 0)
insa(STR,  str,	  1, OpCls( RGT8,    NONE,	  NONE ), F_0F,	   0,  no_WDS, 0x00, 0x08, P_64,  0, 0, 0, 0)
insa(STR,  1,	  0, OpCls( M16,     NONE,	  NONE ), F_0FNO66,0,  no_WDS, 0x00, 0x08, P_286, 0, 0, 0, 0)

; v2.06: POP/PUSH added
insa(POP, pop,	  1, OpCls( R16_R64, NONE,	  NONE ), 0,	   0,  R_in_OP,0x58, 0x00, P_86,  0, 0, 0, 0)
insa(POP, 1,	  0, OpCls( M16_M64, NONE,	  NONE ), 0,	   0,  0,      0x8F, 0x00, P_86,  0, 0, 0, 0)
insa(POP, 2,	  0, OpCls( SR386,   NONE,	  NONE ), F_0F,	   1,  R_in_OP,0x81, 0x00, P_386, 0, 0, 0, 0)
insa(PUSH, push,  1, OpCls( R16_R64, NONE,	  NONE ), 0,	   0,  R_in_OP,0x50, 0x00, P_86,  0, 0, 0, 0)
insa(PUSH, 1,	  0, OpCls( I8,	     NONE,	  NONE ), 0,	   0,  no_RM,  0x6A, 0x00, P_186, 0, 0, 0, 0)
insa(PUSH, 2,	  0, OpCls( I,	     NONE,	  NONE ), 0,	   0,  no_RM,  0x68, 0x00, P_186, 0, 0, 0, 0)
insa(PUSH, 3,	  0, OpCls( M16_M64, NONE,	  NONE ), 0,	   0,  0,      0xFF, 0x30, P_86,  0, 0, 0, 0)
insa(PUSH, 4,	  0, OpCls( SR386,   NONE,	  NONE ), F_0F,	   1,  R_in_OP,0x80, 0x00, P_386, 0, 0, 0, 0)
insa(VMREAD,  vmread,  1, OpCls( R64_M64, R64,	  NONE ), F_0F,	   0,  no_WDS, 0x78, 0x00, P_686p,0, 0, 0, 0)
insa(VMWRITE, vmwrite, 1, OpCls( R64, R64_M64,	  NONE ), F_0F,	   1,  no_WDS, 0x79, 0x00, P_686p,0, 0, 0, 0)
