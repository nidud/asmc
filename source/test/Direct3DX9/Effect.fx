float4x4 ShaderMatrix;

struct VS_OUTPUT
{
	float4 PositionOut : POSITION;
	float4 ColorOut : COLOR;
};

//Vertex Shader
VS_OUTPUT VS(float4 PositionIn : POSITION, float4 ColorIn : COLOR)
{
	VS_OUTPUT VertexOut;
	VertexOut.PositionOut = mul(PositionIn, ShaderMatrix);
	VertexOut.ColorOut = ColorIn;
	return VertexOut;
}

//Pixel Shader
float4 PS(float4 Color : COLOR) : COLOR
{
    return Color;
}

technique RenderScene
{
    pass P0
    {
	VertexShader = compile vs_1_1 VS();
	PixelShader  = compile ps_1_1 PS();
    }
}
