Asmc Macro Assembler Reference

## .COMDEF

.COMDEF _name_ [[ : public _class_ ]]

Declares a structure type for a [COM interface](https://en.wikipedia.org/wiki/Component_Object_Model).

A typical C declaration for a COM interface:

    typedef struct IShellFolderVtbl {
    BEGIN_INTERFACE
    HRESULT ( STDMETHODCALLTYPE *QueryInterface )(
      IShellFolder * _This, REFIID riid, void **ppvObject);
    ...
    END_INTERFACE
    } IShellFolderVtbl;
    interface IShellFolder {
	CONST_VTBL struct IShellFolderVtbl *lpVtbl;
    };

Same using .COMDEF:

    .comdef IShellFolder
    QueryInterface proc :REFIID, :ptr
    ...
    .ends

The objects are normally instantiated with a CreateInstance() function that takes the class as argument and we end up with a pointer or just AX. The call to the method is then something like this:

    mov rcx,rax	  ; load args
    mov rdx,riid
    mov r8,ppvObject
    mov rax,[rcx] ; make the call
    call [rax].IShellFolderVtbl.QueryInterface

The assembler needs to know the name of the base class in order to use these methods. If the method name is not found in the base class, 'Vtbl' is added to the class name. If method exist in classVtbl the pointer is assumed to be the first member of the base (lpVtbl).

    local s:IShellFolder
    s.QueryInterface(riid, ppvObject)
    * lea rcx,s

    local p:ptr IShellFolder
    p.QueryInterface(riid, ppvObject)
    * mov rcx,p

    assume rbx:ptr IShellFolder
    [rbx].QueryInterface(riid, ppvObject)
    * mov rcx,rbx

If PROC is used inside a structure (normally an error) Asmc assumes this to be a pointer to a function.

    * T$0001 typedef proto WINAPI :REFIID, :ptr
    * P$0001 typedef ptr T$0001
    * QueryInterface P$0001 ?

The first method close the base class and open (in this case) the IShellFolderVtbl structure and .ENDS will then close the current struct.

    .ends
    * IShellFolderVtbl ends

#### See Also

[.ENDS](dot_ends.md) | [.CLASS](dot_class.md)
