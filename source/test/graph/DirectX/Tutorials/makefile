!include srcpath

aflags = -nologo -ws -peg -I$(inc_dir)

CreateDevice.exe:
    asmc64 $(aflags) CreateDevice.asm
    asmc64 $(aflags) Vertices.asm
    asmc64 $(aflags) Matrices.asm
    asmc64 $(aflags) Lights.asm
    asmc64 $(aflags) Textures.asm
    asmc64 $(aflags) Meshes.asm
