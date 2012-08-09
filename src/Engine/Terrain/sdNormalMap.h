//*************************************************************************************************
// ����:	�ر�����ͼ
//---------------------------------------------------------
// ����:		
// ����:		2012-08-08
// ����޸�:
//*************************************************************************************************
#pragma once
#ifndef _TERRAIN_NORMAL_MAP_H__
#define _TERRAIN_NORMAL_MAP_H__
#include "sdTypes.h"
#include "sdDynamicTexture.h"

// ǰ������
class sdHeightMap;

// �ر�����ͼ
class sdNormalMap : public NiRefObject
{
public:
	sdNormalMap(uint uiSize, sdHeightMap* pkHeightMap);
	~sdNormalMap();

	// ����,�ֱ����������/����ָ������(��λ1)
	void	Update();
	void	Update(uint uiX, uint uiY, uint uiW, uint uiH);

	// 
	NiTexture*	GetGBTexture() const;

protected:
	// �߶�ͼ(���ڱ༭״̬)
	sdHeightMap*	m_pkHeightMap;

	// NormalMap������
	RenderSystem::sdDynamicTexturePtr	m_pkDynamicNormalTexture;	// ���ڱ༭״̬,���ṩ��̬����
	NiTexturePtr	m_spNormalTexture;	// ������Ϸ״̬
};
NiSmartPointer(sdNormalMap);
#endif