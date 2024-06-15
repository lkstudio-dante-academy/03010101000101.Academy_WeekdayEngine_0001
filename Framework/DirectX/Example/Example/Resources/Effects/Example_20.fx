float4x4 g_stWorldMatrix;
float4x4 g_stViewMatrix;
float4x4 g_stProjectionMatrix;

texture g_pTexture;
bool g_bIsGrayscale;

float g_fTileSizeX;
float g_fTileSizeY;

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

	stOutput.m_stUV = float2(a_stInput.m_stUV.x * g_fTileSizeX, a_stInput.m_stUV.y * g_fTileSizeY);
	return stOutput;
}

sampler2D g_pSampler = sampler_state
{
	Texture = g_pTexture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;

	AddressU = WRAP;
	AddressV = WRAP;
};

/** PS Main */
float4 PSMain(STOutput a_stInput): COLOR0
{
	float4 stDiffuseColor = tex2D(g_pSampler, a_stInput.m_stUV);
	float4 stFinalColor = stDiffuseColor;

	if(g_bIsGrayscale)
	{
		stFinalColor.rgb = dot(stDiffuseColor.rgb, float3(0.3f, 0.59f, 0.11f));
	}
	else
	{
		stFinalColor.rgb = float3(dot(stDiffuseColor.rgb, float3(0.393f, 0.769f, 0.189f)),
			dot(stDiffuseColor.rgb, float3(0.349f, 0.686f, 0.168f)), dot(stDiffuseColor.rgb, float3(0.272f, 0.534f, 0.131f)));
	}

	return stFinalColor;
}

technique MyTechnique
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}
