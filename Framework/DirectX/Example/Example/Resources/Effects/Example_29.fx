float4x4 g_stViewMatrix;
float4x4 g_stProjectionMatrix;

float4x4 g_stLightViewMatrix;
float4x4 g_stLightProjectionMatrix;

float4x4 g_stShadowMatrix;
texture g_pTexture;

int g_nNumBlends;
bool g_bIsDrawingShadow;

float4 g_stDiffuse;
float4 g_stViewPosition;
float4 g_stLightDirection;
float4x4 g_astBlendMatrices[4];

/** VS Input */
struct STInput
{
	float3 m_stPosition: POSITION0;
	float3 m_stNormal: NORMAL0;
	float3 m_stTangent: TANGENT0;
	float3 m_stBinormal: BINORMAL0;
	float2 m_stUV: TEXCOORD0;
	float4 m_stBlendWeight: BLENDWEIGHT0;
};

/** VS Output */
struct STOutput
{
	float4 m_stPosition: POSITION0;
	float3 m_stNormal: TEXCOORD0;
	float3 m_stTangent: TEXCOORD1;
	float3 m_stBinormal: TEXCOORD2;
	float2 m_stUV: TEXCOORD3;
	float4 m_stClipPosition: TEXCOORD4;
	float3 m_stViewDirection: TEXCOORD5;
	float3 m_stLightDirection: TEXCOORD6;
};

/** VS Main */
STOutput VSMain(STInput a_stInput)
{
	STOutput stOutput = (STOutput)0;
	float fLeftWeight = 1.0f;

	for(int i = 1; i <= g_nNumBlends; ++i)
	{
		float fWeight = a_stInput.m_stBlendWeight[i];
		float4x4 stBlendMatrix = g_astBlendMatrices[i];

		fLeftWeight -= fWeight;

		stOutput.m_stPosition += mul(float4(a_stInput.m_stPosition, 1.0f), stBlendMatrix) * fWeight;
		stOutput.m_stNormal += mul(a_stInput.m_stNormal, (float3x3)stBlendMatrix) * fWeight;
		stOutput.m_stTangent += mul(a_stInput.m_stTangent, (float3x3)stBlendMatrix) * fWeight;
		stOutput.m_stBinormal += mul(a_stInput.m_stBinormal, (float3x3)stBlendMatrix) * fWeight;
	}

	stOutput.m_stPosition += mul(float4(a_stInput.m_stPosition, 1.0f), g_astBlendMatrices[0]) * fLeftWeight;
	stOutput.m_stNormal += mul(a_stInput.m_stNormal, (float3x3)g_astBlendMatrices[0]) * fLeftWeight;
	stOutput.m_stTangent += mul(a_stInput.m_stTangent, (float3x3)g_astBlendMatrices[0]) * fLeftWeight;
	stOutput.m_stBinormal += mul(a_stInput.m_stBinormal, (float3x3)g_astBlendMatrices[0]) * fLeftWeight;

	stOutput.m_stPosition.w = 1.0f;
	float4 stWorldPosition = stOutput.m_stPosition;
	
	if(g_bIsDrawingShadow)
	{
		stOutput.m_stPosition = mul(stWorldPosition, g_stShadowMatrix);
		stOutput.m_stPosition = mul(stOutput.m_stPosition, g_stViewMatrix);
		stOutput.m_stPosition = mul(stOutput.m_stPosition, g_stProjectionMatrix);
	}
	else
	{
		stOutput.m_stPosition = mul(stWorldPosition, g_stViewMatrix);
		stOutput.m_stPosition = mul(stOutput.m_stPosition, g_stProjectionMatrix);

		float3 stViewDirection = stWorldPosition.xyz - g_stViewPosition.xyz;
		stOutput.m_stViewDirection = normalize(stViewDirection);

		float3 stLightDirection = g_stLightDirection.xyz;
		stOutput.m_stLightDirection = normalize(stLightDirection);

		stOutput.m_stNormal = normalize(stOutput.m_stNormal);
		stOutput.m_stTangent = normalize(stOutput.m_stTangent);
		stOutput.m_stBinormal = normalize(stOutput.m_stBinormal);
	}

	stOutput.m_stClipPosition = mul(stWorldPosition, g_stLightViewMatrix);
	stOutput.m_stClipPosition = mul(stOutput.m_stClipPosition, g_stLightProjectionMatrix);

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
	if(g_bIsDrawingShadow)
	{
		return g_stDiffuse;
	}

	float3 stNormal = normalize(a_stInput.m_stNormal);
	float3 stViewDirection = normalize(a_stInput.m_stViewDirection);
	float3 stLightDirection = normalize(a_stInput.m_stLightDirection);

	float fDiffuse = saturate(dot(-stLightDirection, stNormal));

	float fSpecular = saturate(dot(reflect(stLightDirection, stNormal), -stViewDirection));
	fSpecular = pow(fSpecular, 20.0f);

	float4 stDiffuseColor = tex2D(g_pSampler, a_stInput.m_stUV);

	float4 stFinalColor = stDiffuseColor;
	stFinalColor.rgb = stFinalColor.rgb * fDiffuse;
	stFinalColor.rgb = stFinalColor.rgb + (stDiffuseColor.rgb * fSpecular);
	stFinalColor.rgb = stFinalColor.rgb + (stDiffuseColor.rgb * 0.4f);

	return stFinalColor * g_stDiffuse;
}

technique MyTechnique
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}
