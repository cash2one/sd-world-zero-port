//*************************************************************************************************
// 内容:	AxisAlignedBox,抽取自Ogre
//---------------------------------------------------------
// 作者:		
// 创建:		2012-08-03
// 最后修改:
//*************************************************************************************************
#pragma once
#ifndef _MATH_AxisAlignedBox_H__
#define _MATH_AxisAlignedBox_H__
#include "sdMath.h"
#include "sdVector3.h"

namespace Base
{
	namespace Math
	{
		// 
		class sdAxisAlignedBox
		{
		public:
			enum eExtent
			{
				E_EXTENT_NULL,		// 空
				E_EXTENT_FINITE,	// 有限
				E_EXTENT_INFINITE,	// 无限
			};


		protected:
			sdVector3 m_kMinimum;
			sdVector3 m_kMaximum;
			eExtent	m_eExtent;

		public:
			// 特殊值
			static const sdAxisAlignedBox BOX_NULL;
			static const sdAxisAlignedBox BOX_INFINITE;

		public:
			inline sdAxisAlignedBox() 
			{
				SetMinimum(-0.5, -0.5, -0.5);
				SetMaximum(0.5, 0.5, 0.5);
				m_eExtent = E_EXTENT_NULL;
			}

			inline sdAxisAlignedBox(eExtent eExtentType) 
			{
				SetMinimum(-0.5, -0.5, -0.5);
				SetMaximum(0.5, 0.5, 0.5);
				m_eExtent = E_EXTENT_NULL;
			}

			inline sdAxisAlignedBox(const sdVector3& kMin, const sdVector3& kMax) 
			{
				SetExtents(kMin, kMax);
			}

			// 设置与获取范围
			// @{
			inline const sdVector3& GetMinimum() const
			{ 
				return m_kMinimum; 
			}

			inline sdVector3& GetMinimum()
			{ 
				return m_kMinimum; 
			}

			inline const sdVector3& GetMaximum() const
			{ 
				return m_kMaximum;
			}

			inline sdVector3& GetMaximum()
			{ 
				return m_kMaximum;
			}

			inline void SetMinimum(const sdVector3& vec)
			{
				m_eExtent = E_EXTENT_FINITE;
				m_kMinimum = vec;
			}

			inline void SetMinimum(float fX, float fY, float fZ)
			{
				m_eExtent = E_EXTENT_FINITE;
				m_kMinimum.m_fX = fX;
				m_kMinimum.m_fY = fY;
				m_kMinimum.m_fZ = fZ;
			}

			inline void SetMinimumX(float fX)
			{
				m_kMinimum.m_fX = fX;
			}

			inline void SetMinimumY(float fY)
			{
				m_kMinimum.m_fY = fY;
			}

			inline void SetMinimumZ(float fZ)
			{
				m_kMinimum.m_fZ = fZ;
			}

			inline void SetMaximum(const sdVector3& vec)
			{
				m_eExtent = E_EXTENT_FINITE;
				m_kMaximum = vec;
			}

			inline void SetMaximum(float fX, float fY, float fZ)
			{
				m_eExtent = E_EXTENT_FINITE;
				m_kMaximum.m_fX = fX;
				m_kMaximum.m_fY = fY;
				m_kMaximum.m_fZ = fZ;
			}

			inline void SetMaximumX(float fX)
			{
				m_kMaximum.m_fX = fX;
			}

			inline void SetMaximumY(float fY)
			{
				m_kMaximum.m_fY = fY;
			}

			inline void SetMaximumZ(float fZ)
			{
				m_kMaximum.m_fZ = fZ;
			}

			inline void SetExtents(const sdVector3& kMin, const sdVector3& kMax)
			{
				assert(kMin.m_fX <= kMax.m_fX && kMin.m_fY <= kMax.m_fY && kMin.m_fZ <= kMax.m_fZ);

				m_eExtent = E_EXTENT_FINITE;
				m_kMinimum = kMin;
				m_kMaximum = kMax;
			}

			inline void SetExtents(
				float mx, float my, float mz,
				float Mx, float My, float Mz)
			{
				assert(mx <= Mx && my <= My && mz <= Mz);

				m_eExtent = E_EXTENT_FINITE;

				m_kMinimum.m_fX = mx;
				m_kMinimum.m_fY = my;
				m_kMinimum.m_fZ = mz;

				m_kMaximum.m_fX = Mx;
				m_kMaximum.m_fY = My;
				m_kMaximum.m_fZ = Mz;
			}

			void GetCenter(sdVector3& kVector) const
			{
				kVector.m_fX = (m_kMinimum.m_fX + m_kMaximum.m_fX) * 0.5f;
				kVector.m_fY = (m_kMinimum.m_fY + m_kMaximum.m_fY) * 0.5f;
				kVector.m_fZ = (m_kMinimum.m_fZ + m_kMaximum.m_fZ) * 0.5f;
			}

			void GetSize(sdVector3& kVector) const
			{
				switch (m_eExtent)
				{
				case E_EXTENT_NULL:
					kVector = sdVector3::ZERO;
					break;

				case E_EXTENT_FINITE:
					kVector = m_kMaximum - m_kMinimum;
					break;

				case E_EXTENT_INFINITE:
					kVector.m_fX = sdMath::POS_INFINITY;
					kVector.m_fY = sdMath::POS_INFINITY;
					kVector.m_fZ = sdMath::POS_INFINITY;
					break;
				}
			}

			void GetHalfSize(sdVector3& kVector) const
			{
				switch (m_eExtent)
				{
				case E_EXTENT_NULL:
					kVector = sdVector3::ZERO;
					break;

				case E_EXTENT_FINITE:
					kVector = (m_kMaximum - m_kMinimum) * 0.5f;
					break;

				case E_EXTENT_INFINITE:
					kVector.m_fX = sdMath::POS_INFINITY;
					kVector.m_fY = sdMath::POS_INFINITY;
					kVector.m_fZ = sdMath::POS_INFINITY;
					break;
				}
			}
			// @}


			// 包围盒类型
			// @{
			inline void setNull()
			{
				m_eExtent = E_EXTENT_NULL;
			}

			inline bool isNull() const
			{
				return (m_eExtent == E_EXTENT_NULL);
			}

			bool isFinite() const
			{
				return (m_eExtent == E_EXTENT_FINITE);
			}

			inline void setInfinite()
			{
				m_eExtent = E_EXTENT_INFINITE;
			}

			bool isInfinite() const
			{
				return (m_eExtent == E_EXTENT_INFINITE);
			}
			// @}


			// 合并
			// @{
			void Merge(const sdAxisAlignedBox& kAABB)
			{
				// 两个AABB合并一共有9种情况
				if ((kAABB.m_eExtent == E_EXTENT_NULL) || (m_eExtent == E_EXTENT_INFINITE))
				{
					// Do nothing if rhs null, or this is infinite
					//	E_EXTENT_INFINITE	E_EXTENT_NULL
					//	E_EXTENT_INFINITE	E_EXTENT_FINITE
					//	E_EXTENT_INFINITE	E_EXTENT_INFINITE
					//  E_EXTENT_NULL		E_EXTENT_NULL
					//	E_EXTENT_FINITE		E_EXTENT_NULL
					return;
				}
				else if (kAABB.m_eExtent == E_EXTENT_INFINITE)
				{
					// Otherwise if rhs is infinite, make this infinite, too
					//	E_EXTENT_FINITE		E_EXTENT_INFINITE
					m_eExtent = E_EXTENT_INFINITE;
				}
				else if (m_eExtent == E_EXTENT_NULL)
				{
					// Otherwise if current null, just take rhs
					//	E_EXTENT_NULL		E_EXTENT_FINITE
					//	E_EXTENT_NULL		E_EXTENT_INFINITE			
					SetExtents(kAABB.m_kMinimum, kAABB.m_kMaximum);
				}
				else
				{
					// Otherwise merge
					//	E_EXTENT_FINITE		E_EXTENT_FINITE
					sdVector3 kMin = m_kMinimum;
					sdVector3 kMax = m_kMaximum;
					kMin.MakeMinimum(kAABB.m_kMinimum);
					kMax.MakeMaximum(kAABB.m_kMaximum);

					SetExtents(kMin, kMax);
				}
			}
			// @}

			// 求交
			// @{
			
			// @}
		};
	}
}
#endif