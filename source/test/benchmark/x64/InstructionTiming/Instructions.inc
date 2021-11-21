
TI("adc", reg64, reg64, 0, 0)
TI("adc", reg64, mem64, 0, 0)
TI("adc", reg64, imm8, 0, 1)
TI("adc", mem64, reg64, 0, 0)
TI("adc", mem64, imm8, 0, 1)

TI("add", reg64, reg64, 0, 0)
TI("add", reg64, mem64, 0, 0)
TI("add", reg64, imm8, 0, 1)
TI("add", mem64, reg64, 0, 0)
TI("add", mem64, imm8, 0, 1)

TI("and", reg64, reg64, 0, 0)
TI("and", reg64, mem64, 0, 0)
TI("and", reg64, imm8, 0, 1)
TI("and", mem64, reg64, 0, 0)
TI("and", mem64, imm8, 0, 1)

TI("bsf", reg64, reg64, 0, 0)
TI("bsf", reg64, mem64, 0, 0)

TI("bsr", reg64, reg64, 0, 0)
TI("bsr", reg64, mem64, 0, 0)

TI("bswap", reg32, 0, 0, 0)
TI("bswap", reg64, 0, 0, 0)

TI("bt", reg64, reg64, 0, 0)
TI("bt", reg64, imm8, 0, 1)
TI("bt", mem16, reg16, 0, 0)
TI("bt", mem16, imm8, 0, 1)

TI("btc", reg64, reg64, 0, 0)
TI("btc", reg64, imm8, 0, 1)
TI("btc", mem16, imm8, 0, 1)

TI("btr", reg64, reg64, 0, 0)
TI("btr", reg64, imm8, 0, 1)
TI("btr", mem16, imm8, 0, 1)

TI("bts", reg64, reg64, 0, 0)
TI("bts", reg64, imm8, 0, 1)
TI("bts", mem16, imm8, 0, 1)

TI("call", reg64, 0, 0, 0) ; *

TI("cbw", 0, 0, 0, 0)
TI("cdq", 0, 0, 0, 0)
TI("clc", 0, 0, 0, 0)
TI("cld", 0, 0, 0, 0)

TI("cmp", reg64, reg64, 0, 0)
TI("cmp", reg64, imm8, 0, 1)
TI("cmp", mem64, reg64, 0, 0)
TI("cmp", mem64, imm8, 0, 1)

TI("cmpsb", 0, 0, 0, 0)
TI("cmpsw", 0, 0, 0, 0)
TI("cmpsd", 0, 0, 0, 0)

TI("cmpxchg", reg64, reg64, 0, 0)
TI("cmpxchg", mem64, reg64, 0, 0)

TI("cwd", 0, 0, 0, 0)
TI("cwde", 0, 0, 0, 0)

TI("dec", reg8, 0, 0, 0)
TI("dec", reg64, 0, 0, 0)
TI("dec", mem8, 0, 0, 0)
TI("dec", mem64, 0, 0, 0)

TI("div", reg64, 0, 0, 0) ;*
TI("enter", imm8, imm8, 0, 8) ;*

TI("idiv", reg8, 0, 0, 0) ;*
TI("idiv", reg16, 0, 0, 0) ;*
TI("idiv", reg32, 0, 0, 0) ;*

TI("imul", reg8, 0, 0, 0)
TI("imul", reg16, 0, 0, 0)
TI("imul", reg32, 0, 0, 0)
TI("imul", reg64, 0, 0, 0)
TI("imul", mem8, 0, 0, 0)
TI("imul", mem16, 0, 0, 0)
TI("imul", mem32, 0, 0, 0)
TI("imul", mem64, 0, 0, 0)
TI("imul", reg16, reg16, 0, 0)
TI("imul", reg32, reg32, 0, 0)
TI("imul", reg64, reg64, 0, 0)
TI("imul", reg16, reg16, imm8, 2)
TI("imul", reg32, reg32, imm8, 2)
TI("imul", reg64, reg64, imm8, 2)

TI("inc", reg8, 0, 0, 0)
TI("inc", reg64, 0, 0, 0)
TI("inc", mem8, 0, 0, 0)
TI("inc", mem64, 0, 0, 0)

TI("lahf", 0, 0, 0, 0)
TI("lar", reg16, reg16, 0, 0)
TI("lar", reg32, reg32, 0, 0)

TI("lea", reg64, mem64, 0, 0)

TI("lodsb", 0, 0, 0, 0)
TI("lodsw", 0, 0, 0, 0)
TI("lodsd", 0, 0, 0, 0)

TI("mov", reg64, reg64, 0, 0)
TI("mov", reg64, mem64, 0, 0)
TI("mov", reg64, imm8, 0, 10)
TI("mov", mem64, reg64, 0, 0)
TI("mov", mem64, imm8, 0, 0)

TI("movsb", 0, 0, 0, 0)
TI("movsw", 0, 0, 0, 0)
TI("movsd", 0, 0, 0, 0)

TI("movsx", reg32, reg8, 0, 0)
TI("movsx", reg32, mem8, 0, 0)
TI("movsx", reg64, reg16, 0, 0)
TI("movsx", reg64, mem16, 0, 0)

TI("movzx", reg32, reg8, 0, 0)
TI("movzx", reg32, mem8, 0, 0)
TI("movzx", reg64, reg16, 0, 0)
TI("movzx", reg64, mem16, 0, 0)

TI("mul", reg8, 0, 0, 0)
TI("mul", reg16, 0, 0, 0)
TI("mul", reg32, 0, 0, 0)
TI("mul", reg64, 0, 0, 0)
TI("mul", mem8, 0, 0, 0)
TI("mul", mem16, 0, 0, 0)
TI("mul", mem32, 0, 0, 0)
TI("mul", mem64, 0, 0, 0)

TI("neg", reg8, 0, 0, 0)
TI("neg", reg64, 0, 0, 0)
TI("neg", mem8, 0, 0, 0)
TI("neg", mem64, 0, 0, 0)

TI("nop", 0, 0, 0, 0)

TI("not", reg8, 0, 0, 0)
TI("not", reg64, 0, 0, 0)
TI("not", mem32, 0, 0, 0)
TI("not", mem64, 0, 0, 0)

TI("or", reg8, reg8, 0, 0)
TI("or", reg64, reg64, 0, 0)
TI("or", reg64, mem64, 0, 0)
TI("or", reg64, imm8, 0, 8)
TI("or", mem8, reg8, 0, 0)
TI("or", mem64, reg64, 0, 0)
TI("or", mem64, imm8, 0, 8)

TI("pop", reg64, 0, 0, 8)
TI("popfq", 0, 0, 0, 8)
TI("push", reg64, 0, 0, 8)

TI("push", mem64, 0, 0, 8)
TI("pushfq", 0, 0, 0, 8)

TI("rcl", reg8,  imm8, 0, 1)
TI("rcl", reg64, imm8, 0, 1)
TI("rcl", reg8,  reg8, 0, 1)
TI("rcl", reg64, reg8, 0, 1)
TI("rcl", mem8,  imm8, 0, 1)
TI("rcl", mem64, imm8, 0, 1)

TI("rcr", reg8,  imm8, 0, 1)
TI("rcr", reg64, imm8, 0, 1)
TI("rcr", reg8,  reg8, 0, 1)
TI("rcr", reg64, reg8, 0, 1)
TI("rcr", mem8,  imm8, 0, 1)
TI("rcr", mem64, imm8, 0, 1)

TI("rol", reg8,  imm8, 0, 1)
TI("rol", reg64, imm8, 0, 1)
TI("rol", reg8,  reg8, 0, 1)
TI("rol", reg64, reg8, 0, 1)
TI("rol", mem8,  imm8, 0, 1)
TI("rol", mem64, imm8, 0, 1)

TI("ror", reg8,  imm8, 0, 1)
TI("ror", reg64, imm8, 0, 1)
TI("ror", reg8,  reg8, 0, 1)
TI("ror", reg64, reg8, 0, 1)
TI("ror", mem8,  imm8, 0, 1)
TI("ror", mem64, imm8, 0, 1)

TI("shl", reg8,  imm8, 0, 1)
TI("shl", reg64, imm8, 0, 1)
TI("shl", reg8,  reg8, 0, 1)
TI("shl", reg64, reg8, 0, 1)
TI("shl", mem8,  imm8, 0, 1)
TI("shl", mem64, imm8, 0, 1)

TI("sar", reg8,  imm8, 0, 1)
TI("sar", reg64, imm8, 0, 1)
TI("sar", reg8,  reg8, 0, 1)
TI("sar", reg64, reg8, 0, 1)
TI("sar", mem8,  imm8, 0, 1)
TI("sar", mem64, imm8, 0, 1)

TI("sbb", reg8,  reg8, 0, 0)
TI("sbb", reg64, reg64, 0, 0)
TI("sbb", reg8,  imm8, 0, 1)
TI("sbb", reg64, imm8, 0, 1)
TI("sbb", mem8,  reg8, 0, 0)
TI("sbb", mem64, reg64, 0, 0)
TI("sbb", mem8,  imm8, 0, 1)
TI("sbb", mem64, imm8, 0, 1)

TI("scasb", 0, 0, 0, 0)
TI("scasw", 0, 0, 0, 0)
TI("scasd", 0, 0, 0, 0)

TI("setae", reg8, 0, 0, 0)
TI("setae", mem8, 0, 0, 0)
TI("setb", reg8, 0, 0, 0)
TI("setb", mem8, 0, 0, 0)
TI("setg", reg8, 0, 0, 0)
TI("setg", mem8, 0, 0, 0)
TI("setng", reg8, 0, 0, 0)
TI("setng", mem8, 0, 0, 0)

TI("shr", reg8,  imm8, 0, 1)
TI("shr", reg64, imm8, 0, 1)
TI("shr", reg8,  reg8, 0, 1)
TI("shr", reg64, reg8, 0, 1)
TI("shr", mem8,  imm8, 0, 1)
TI("shr", mem64, imm8, 0, 1)

TI("shld", reg16, reg16, imm8, 1)
TI("shld", reg32, reg32, imm8, 1)
TI("shld", reg64, reg64, imm8, 1)
TI("shld", mem16, reg16, imm8, 1)
TI("shld", mem64, reg64, imm8, 1)

TI("shrd", reg16, reg16, imm8, 1)
TI("shrd", reg32, reg32, imm8, 1)
TI("shrd", reg64, reg64, imm8, 1)
TI("shrd", mem16, reg16, imm8, 1)
TI("shrd", mem64, reg64, imm8, 1)

TI("smsw", reg32, 0, 0, 0)
TI("smsw", reg64, 0, 0, 0)
TI("stc", 0, 0, 0, 0)
TI("std", 0, 0, 0, 0) ; *

TI("stosb", 0, 0, 0, 0)
TI("stosw", 0, 0, 0, 0)
TI("stosd", 0, 0, 0, 0)

TI("str", reg16, 0, 0, 0)
TI("str", reg32, 0, 0, 0)

TI("sub", reg8, reg8, 0, 0)
TI("sub", reg64, reg64, 0, 0)
TI("sub", reg64, imm8, 0, 0)
TI("sub", reg64, mem64, 0, 0)
TI("sub", mem64, imm8, 0, 0)
TI("sub", mem64, reg64, 0, 0)

TI("test", reg8, reg8, 0, 0)
TI("test", reg64, reg64, 0, 0)
TI("test", reg64, imm8, 0, 0)
TI("test", reg64, mem64, 0, 0)
TI("test", mem64, imm8, 0, 0)
TI("test", mem64, reg64, 0, 0)

TI("xchg", reg8,  reg8, 0, 0)
TI("xchg", reg64, reg64, 0, 0)
TI("xchg", reg64, mem64, 0, 0)
TI("xchg", mem64, reg64, 0, 0)

TI("xlat", 0, 0, 0, 0) ; *
TI("xlatb", 0, 0, 0, 0) ; *

TI("xor", reg8, reg8, 0, 0)
TI("xor", reg64, reg64, 0, 0)
TI("xor", reg64, mem64, 0, 0)
TI("xor", reg64, imm8, 0, 8)
TI("xor", mem8, reg8, 0, 0)
TI("xor", mem64, reg64, 0, 0)
TI("xor", mem64, imm8, 0, 8)
