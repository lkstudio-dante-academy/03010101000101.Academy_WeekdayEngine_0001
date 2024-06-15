float4x4 g_stWorldMatrix;
float4x4 g_stViewMatrix;
float4x4 g_stProjectionMatrix;

texture g_pTexture;
float g_fOpacity;

/** VS Input */
struct STInput
{
	float3 m_stPosition: POSITION0;
	float2 m_stUV: TEXCOORD0;
};

/** VS Output */
struct STOutput
{
	float4 m_stPosition: POSITION0;
	float2 m_stUV: TEXCOORD0;
};

/** VS Main */
STOutput VSMain(STInput a_stInput)
{
	STOutput stOutput = (STOutput)0;
	float4 stWorldPosition = mul(float4(a_stInput.m_stPosition, 1.0f), g_stWorldMatrix);

	stOutput.m_stPosition = mul(stWorldPosition, g_stViewMatrix);
	stOutput.m_stPosition = mul(stOutput.m_stPosition, g_stProjectionMatrix);

	stOutput.m_stUV = a_stInput.m_stUV;
	return stOutput;
}

sampler2D g_pSampler = sampler_state
{
	Texture = g_pTexture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

/** PS Main */
float4 PSMain(STOutput a_stInput): COLOR0
{
	float4 stFinalColor = tex2D(g_pSampler, a_stInput.m_stUV);
	stFinalColor.a = g_fOpacity;

	return stFinalColor;
}

technique MyTechnique
{
	pass P0
	{
		AlphaBlendEnable = TRUE;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;

		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}
