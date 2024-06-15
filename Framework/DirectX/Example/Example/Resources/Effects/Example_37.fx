float4x4 g_stWorldMatrix;
float4x4 g_stViewMatrix;
float4x4 g_stProjectionMatrix;

texture g_pDiffuseTexture;
texture g_pSpecularTexture;

float4 g_stViewPosition;
float4 g_stLightDirection;

/** VS Input */
struct STInput
{
	float3 m_stPosition: POSITION0;
	float3 m_stNormal: NORMAL0;
	float2 m_stUV: TEXCOORD0;
};

/** VS Output */
struct STOutput
{
	float4 m_stPosition: POSITION0;
	float3 m_stNormal: TEXCOORD0;
	float2 m_stUV: TEXCOORD1;
	float3 m_stViewDirection: TEXCOORD2;
	float3 m_stLightDirection: TEXCOORD3;
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

	float3 stViewDirection = g_stViewPosition.xyz - stWorldPosition.xyz;
	stOutput.m_stViewDirection = normalize(stViewDirection);

	float3 stLightDirection = g_stLightDirection.xyz;
	stOutput.m_stLightDirection = normalize(stLightDirection);

	stOutput.m_stUV = a_stInput.m_stUV;
	return stOutput;
}

sampler2D g_pDiffuseSampler = sampler_state
{
	Texture = g_pDiffuseTexture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

sampler2D g_pSpecularSampler = sampler_state
{
	Texture = g_pSpecularTexture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

/** PS Main */
float4 PSMain(STOutput a_stInput): COLOR0
{
	float3 stNormal = normalize(a_stInput.m_stNormal);
	float3 stViewDirection = normalize(a_stInput.m_stViewDirection);
	float3 stLightDirection = normalize(a_stInput.m_stLightDirection);

	float fDiffuse = saturate(dot(-stLightDirection, stNormal));

	float fSpecular = saturate(dot(reflect(stLightDirection, stNormal), -stViewDirection));
	fSpecular = pow(fSpecular, 20.0f);

	float4 stDiffuseColor = tex2D(g_pDiffuseSampler, a_stInput.m_stUV);
	float4 stSpecularColor = tex2D(g_pSpecularSampler, a_stInput.m_stUV);

	float4 stFinalColor = stDiffuseColor;
	stFinalColor.rgb = stFinalColor.rgb * fDiffuse;
	stFinalColor.rgb = stFinalColor.rgb + (stSpecularColor.rgb * fSpecular);
	stFinalColor.rgb = stFinalColor.rgb + (stDiffuseColor.rgb * 0.4f);

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
