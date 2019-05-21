; v2.22 - .gotosw[1|2|3] [.if <condition>]
; v2.30 - .gotosw([n:] <label>) [.if <condition>]
ifndef _WIN64
    .486
    .model flat, c
endif
    .pragma warning(disable:7007)
    .code
    .switch jmp eax
      .case 1
        .gotosw
        .gotosw(2)
        .gotosw .if cl
        .endc
      .case 2
        .gotosw(1) .if cl
        .switch al
          .case 1
            .gotosw
            .gotosw .if cl
          .case 2
            .gotosw(1:)
            .gotosw(1:) .if cl
            .endc
          .case 3
            .switch al
              .case 1
                .gotosw
                .gotosw .if cl
              .case 2
                .gotosw(1:)
                .gotosw(1:) .if cl
              .case 3
                .gotosw(2:)
                .gotosw(2:) .if cl
                .endc
              .case 4
                .switch al
                  .case 1
                    .gotosw
                    .gotosw .if cl
                  .case 2
                    .gotosw(1:)
                    .gotosw(1:) .if cl
                  .case 3
                    .gotosw(2:)
                    .gotosw(2:) .if cl
                  .case 4
                    .gotosw(3:)
                    .gotosw(3:) .if cl
                  .case 5
                    .gotosw(3:1) .if cl
                    .gotosw(3:2)
                    .endc
                .endsw
            .endsw
        .endsw
    .endsw

    end
