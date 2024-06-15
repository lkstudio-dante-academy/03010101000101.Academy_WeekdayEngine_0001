float4x4 g_stWorldMatrix;
float4x4 g_stViewMatrix;
float4x4 g_stProjectionMatrix;

texture g_pCubeTexture;

float4 g_stDiffuse;
float4 g_stViewPosition;
float4 g_stLightDirection;

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
	float3 m_stViewDirection: TEXCOORD1;
	float3 m_stLightDirection: TEXCOORD2;
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

	float3 stViewDirection = stWorldPosition.xyz - g_stViewPosition.xyz;
	stOutput.m_stViewDirection = normalize(stViewDirection);

	float3 stLightDirection = g_stLightDirection.xyz;
	stOutput.m_stLightDirection = normalize(stLightDirection);

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
	float3 stViewDirection = normalize(a_stInput.m_stViewDirection);
	float3 stLightDirection = normalize(a_stInput.m_stLightDirection);

	float fDiffuse = saturate(dot(-stLightDirection, stNormal));

	float fSpecular = saturate(dot(reflect(stLightDirection, stNormal), -stViewDirection));
	fSpecular = pow(fSpecular, 20.0f);

	float4 stDiffuseColor = texCUBE(g_pCubeSampler, reflect(stViewDirection, stNormal));

	float4 stFinalColor = stDiffuseColor;
	stFinalColor.rgb = stFinalColor.rgb * fDiffuse;
	stFinalColor.rgb = stFinalColor.rgb + (g_stDiffuse.rgb * fDiffuse);
	stFinalColor.rgb = stFinalColor.rgb + (float3(1.0f, 1.0f, 1.0f) * fSpecular);
	stFinalColor.rgb = stFinalColor.rgb + (g_stDiffuse.rgb * 0.4f);

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
