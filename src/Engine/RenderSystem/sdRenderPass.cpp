#include "Stdafx.h"
#include "sdRenderPass.h"
#include "sdRenderObject.h"
#include "sdRenderObjectAlloc.h"
#include "sdRenderSystem.h"

namespace RenderSystem
{

//-------------------------------------------------------------------------------------------------
bool sdRenderPass::Comparator(sdRenderObject* lhs, sdRenderObject* rhs)
{
	NIASSERT(lhs);
	NIASSERT(rhs);

	if (lhs->GetType() != rhs->GetType())
		return (uint)lhs->GetType() < (uint)rhs->GetType();

	return lhs->GetSortKey() < rhs->GetSortKey();
}
//-------------------------------------------------------------------------------------------------
sdRenderPass::sdRenderPass(sdRenderObjectAlloc* pkAlloc)
: m_bInitialized(false)
, m_bActived(true)
, m_pkAlloc(pkAlloc)
{
	NIASSERT(pkAlloc && "Invalid Render Object Alloc");

	m_pkRenderParams = NiNew sdRenderParams;
	NIASSERT(m_pkRenderParams);
}
//-------------------------------------------------------------------------------------------------
sdRenderPass::~sdRenderPass()
{
	ClearObjects();

	m_pkAlloc = NULL;

	if (m_pkRenderParams)
	{
		NiDelete m_pkRenderParams;
		m_pkRenderParams = NULL;
	}
}
//-------------------------------------------------------------------------------------------------
void sdRenderPass::SetRenderParams(const sdRenderParams* pkRenderParams)
{
	*m_pkRenderParams = *pkRenderParams;
}
//-------------------------------------------------------------------------------------------------
void sdRenderPass::Begin()
{
	ClearObjects();
}
//-------------------------------------------------------------------------------------------------
void sdRenderPass::Draw()
{
	if (!m_bInitialized || !m_bActived)
		return;

	// 对渲染对象进行排序
	Sort();

	// 对渲染对象依次调用绘制函数
	RenderObjectVecItr itr = m_kRenderObjectVec.begin();
	RenderObjectVecItr itr_end = m_kRenderObjectVec.end();
	for (; itr!=itr_end; ++itr)
	{
		(*itr)->Draw();
	}
}
//-------------------------------------------------------------------------------------------------
void sdRenderPass::End()
{
	ClearObjects();
}
//-------------------------------------------------------------------------------------------------
sdRenderObject::ShaderParamItem* sdRenderPass::CloneShaderParams(sdRenderObject::ShaderParamItem* pkParams)
{
	typedef sdRenderObject::ShaderParamItem	ShaderParamItem;

	// 拷贝着色器参数数组,是一个以空元素结束的数组
	if (NULL == pkParams || NULL == pkParams[0].szName)
		return NULL;

	// 计算数组大小
	uint uiNum = 0;
	uint uiByteSize = 0;
	while(NULL != pkParams[uiNum].szName)
	{
		uiByteSize += pkParams[uiNum].uiByteSize;
		++uiNum;
	}

	// 在缓存池创建对象并拷贝之
	//  1.前一部分放置以空元素结束的ShaderParam数组
	//  2.后一部分放置ShaderParam指向的参数
	char* pcMemBuf = (char*)m_pkAlloc->Alloc((uiNum+1) * sizeof(ShaderParamItem) + uiByteSize);
	ShaderParamItem* pkDstParams = (ShaderParamItem*)pcMemBuf;
	char* pkDstData = pcMemBuf + (uiNum+1) * sizeof(ShaderParamItem);

	ShaderParamItem* pkCurSrcParam = pkParams;
	ShaderParamItem* pkCurDstParam = pkDstParams;
	char* pkCurDstData = pkDstData;
	for (uint i = 0; i < uiNum; ++i)
	{
		pkDstParams->szName = pkCurSrcParam->szName;
		pkDstParams->uiByteSize = pkCurSrcParam->uiByteSize;
		memcpy(pkCurDstData, pkCurSrcParam->pData, pkCurSrcParam->uiByteSize);
		pkCurDstParam->pData = (void*)pkCurDstData;

		++pkCurSrcParam;
		++pkCurDstParam;
		pkDstData += pkCurSrcParam->uiByteSize;
	}

	pkDstParams[uiNum].szName = NULL;
	pkDstParams[uiNum].uiByteSize = 0;
	pkDstParams[uiNum].pData = NULL;

	return pkDstParams;
	
}
//-------------------------------------------------------------------------------------------------
void sdRenderPass::InsertRenderObject(sdRenderObject* pkObject)
{
	NIASSERT(pkObject);
	m_kRenderObjectVec.push_back(pkObject);
}
//-------------------------------------------------------------------------------------------------
void sdRenderPass::InsertStaticObject(NiMesh* spMesh, NiMaterial* spMaterial,
	NiPropertyList* spRenderProps, sdRenderObject::ShaderParamItem* pkShaderParams)
{
	NIASSERT(spMesh);

	sdRenderObject::ShaderParamItem* pkCloneParams = CloneShaderParams(pkShaderParams);
	void* pkMemBuf = m_pkAlloc->Alloc(sizeof(StaticMeshRenderObject));
	new (pkMemBuf) StaticMeshRenderObject(spMesh, spMaterial, spRenderProps, pkCloneParams);
	InsertRenderObject((sdRenderObject*)pkMemBuf);
}
//-------------------------------------------------------------------------------------------------
void sdRenderPass::ClearObjects()
{
	m_kRenderObjectVec.clear();
}
//-------------------------------------------------------------------------------------------------
sdRenderPass::RenderObjectComparator sdRenderPass::GetComparator()
{
	return sdRenderPass::Comparator;
}
//-------------------------------------------------------------------------------------------------
void sdRenderPass::Sort()
{
	std::sort(m_kRenderObjectVec.begin(), m_kRenderObjectVec.end(), GetComparator());
}
//-------------------------------------------------------------------------------------------------
}