//*************************************************************************************************
// ����:	(û�õ�)
//---------------------------------------------------------
// ����:		
// ����:		2012-11-08
// ����޸�:
//*************************************************************************************************
#include "environment_common.h"

//---------------------------------------------------------------------------------------
// �������
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// ��������������
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// ������ɫ������������
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// ������ɫ�����������
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// ������ɫ��
//---------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------
float4	VS_Main_MaskOpaqueFog(float3 vPos : POSITION)	: POSITION
{
	return float4(vPos.xy, g_fFogEndHeight, 1.f);
}
//---------------------------------------------------------------------------------------
float4	VS_Main_ShadeOpaqueFog(float3 vPos : POSITION)	: POSITION
{
	return float4(vPos.xy, 1.f, 1.f);
}

//---------------------------------------------------------------------------------------
// ������ɫ��
//---------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------
float4 	PS_Main_MaskOpaqueFog() : COLOR0
{
	return 0;
}
//---------------------------------------------------------------------------------------
float4 	PS_Main_ShadeOpaqueFog() : COLOR0
{
	return float4(g_vFogColor, 1.f);
}

//---------------------------------------------------------------------------------------
// ��ɫ����
//---------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------
technique Environment_MaskOpaqueFog
<
	string	Description 		= "Environment_MaskOpaqueFog";
	bool	UsesNiRenderState 	= false;
	bool	UsesNiLightState	= false;
>
{
	pass P0
	{
		VertexShader	= compile 	vs_2_0	VS_Main_MaskOpaqueFog();
		PixelShader		= compile	ps_2_0 	PS_Main_MaskOpaqueFog();
	}
}
//---------------------------------------------------------------------------------------
technique Environment_ShadeOpaqueFog
<
	string	Description 		= "Environment_ShadeOpaqueFog";
	bool	UsesNiRenderState 	= false;
	bool	UsesNiLightState	= false;
>
{
	pass P0
	{
		VertexShader	= compile 	vs_2_0	VS_Main_ShadeOpaqueFog();
		PixelShader		= compile	ps_2_0 	PS_Main_ShadeOpaqueFog();
	}
}
//---------------------------------------------------------------------------------------