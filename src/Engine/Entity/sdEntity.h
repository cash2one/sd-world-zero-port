//*************************************************************************************************
// 内容:	场景对象节点抽象类,用于构建场景图
//---------------------------------------------------------
// 作者:		
// 创建:		2012-07-31
// 最后修改:
//*************************************************************************************************
#pragma once
#ifndef _ENTITY_H__
#define _ENTITY_H__
#include "sdGameObject.h"

class sdEntity : public sdGameObject
{


public:
	sdEntity();
	virtual ~sdEntity();

};
#include "sdEntity.inl"

#endif