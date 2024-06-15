float4x4 g_stWorldMatrix;
float4x4 g_stViewMatrix;
float4x4 g_stProjectionMatrix;

texture g_pCubeTexture;

/** VS Input */
struct STInput
{
	float3 m_stPosition: POSITION0;
	float3 m_stNormal: NORMAL0;
};

/** VS Output */
struct STOutput
{
	float4 m_stPosition: POSITION0;
	float3 m_stNormal: TEXCOORD0;
};

/** VS Main */
STOutput VSMain(STInput a_stInput)
{
	STOutput stOutput = (STOutput)0;
	float4 stWorldPosition = mul(float4(a_stInput.m_stPosition, 1.0f), g_stWorldMatrix);

	stOutput.m_stPosition = mul(stWorldPosition, g_stViewMatrix);
	stOutput.m_stPosition = mul(stOutput.m_stPosition, g_stProjectionMatrix);

	float3 stNormal = mul(a_stInput.m_stNormal, (float3x3)g_stWorldMatrix);
	stOutput.m_stNormal = normalize(stNormal);

	return stOutput;
}

samplerCUBE g_pCubeSampler = sampler_state
{
	Texture = g_pCubeTexture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

/** PS Main */
float4 PSMain(STOutput a_stInput): COLOR0
{
	float3 stNormal = normalize(a_stInput.m_stNormal);
	return texCUBE(g_pCubeSampler, stNormal);
}

technique MyTechnique
{
	pass P0
	{
		ZWriteEnable = FALSE;
		CullMode = CW;

		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}
