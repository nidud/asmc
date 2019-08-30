.pragma list(push, 0)
ifndef __ELF_INC
__ELF_INC equ <>

;; prototypes of functions defined in elf.asm

elf_init proto :ptr module_info

endif
.pragma list(pop)
