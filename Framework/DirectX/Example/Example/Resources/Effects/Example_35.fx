float4x4 g_stWorldMatrix;
float4x4 g_stViewMatrix;
float4x4 g_stProjectionMatrix;

float4x4 g_stLightViewMatrix;
float4x4 g_stLightProjectionMatrix;

texture g_pShadowTexture;

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
	float4 m_stClipPosition: TEXCOORD1;
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

	stOutput.m_stClipPosition = mul(stWorldPosition, g_stLightViewMatrix);
	stOutput.m_stClipPosition = mul(stOutput.m_stClipPosition, g_stLightProjectionMatrix);

	float3 stNormal = mul(a_stInput.m_stNormal, (float3x3)g_stWorldMatrix);
	stOutput.m_stNormal = normalize(stNormal);

	float3 stViewDirection = stWorldPosition.xyz - g_stViewPosition.xyz;
	stOutput.m_stViewDirection = normalize(stViewDirection);

	float3 stLightDirection = g_stLightDirection.xyz;
	stOutput.m_stLightDirection = normalize(stLightDirection);

	return stOutput;
}

sampler2D g_pShadowSampler = sampler_state
{
	Texture = g_pShadowTexture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

/** PS Main */
float4 CreatePSMain(STOutput a_stInput): COLOR0
{
	float fDepth = a_stInput.m_stClipPosition.z / a_stInput.m_stClipPosition.w;
	return float4(fDepth, fDepth, fDepth, 1.0f);
}

/** PS Main */
float4 ApplyPSMain(STOutput a_stInput): COLOR0
{
	float3 stNormal = normalize(a_stInput.m_stNormal);
	float3 stViewDirection = normalize(a_stInput.m_stViewDirection);
	float3 stLightDirection = normalize(a_stInput.m_stLightDirection);

	float2 stUV = float2(a_stInput.m_stClipPosition.x / a_stInput.m_stClipPosition.w,
		a_stInput.m_stClipPosition.y / -a_stInput.m_stClipPosition.w);

	stUV = (stUV * 0.5f) + 0.5f;

	float fDepth = a_stInput.m_stClipPosition.z / a_stInput.m_stClipPosition.w;
	float fShadowDepth = tex2D(g_pShadowSampler, stUV).x;

	float fDiffuse = saturate(dot(-stLightDirection, stNormal));

	float fSpecular = saturate(dot(reflect(stLightDirection, stNormal), -stViewDirection));
	fSpecular = pow(fSpecular, 20.0f);

	float4 stFinalColor = g_stDiffuse;
	stFinalColor.rgb = stFinalColor.rgb * fDiffuse;
	stFinalColor.rgb = stFinalColor.rgb + (g_stDiffuse.rgb * 0.4f);

	if(fDepth > fShadowDepth + 0.000125f)
	{
		stFinalColor.rgb *= 0.5f;
	}
	else
	{
		stFinalColor.rgb += g_stDiffuse.rgb * fSpecular;
	}

	return stFinalColor;
}

technique CreateShadow
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 CreatePSMain();
	}
}

technique ApplyShadow
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 ApplyPSMain();
	}
}
