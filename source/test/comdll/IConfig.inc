
.comdef IConfig

    QueryInterface  proc :REFIID, :ptr
    AddRef          proc
    Release         proc
    read            proc :string_t
    write           proc :string_t
    find            proc :string_t
    create          proc :string_t, :vararg
    getvalue        proc :string_t, :string_t
    delete          proc :string_t
    .ends

