;--- v2.13: 16-bit index register was accepted.
    .x64
    .model flat
    .code
    lea rdx,[bx*4] ;should throw error
    end
