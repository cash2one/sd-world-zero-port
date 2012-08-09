//*************************************************************************************************
// ����:	��������
//---------------------------------------------------------
// ����:		
// ����:		2012-07-23
// ����޸�:
//*************************************************************************************************
#pragma once
#ifndef _INPUT_KEYBOARD_H__
#define _INPUT_KEYBOARD_H__

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

#include <dinput.h>

namespace GameCore
{

	class sdKeyboard : public NiRefObject
	{
	public:
		sdKeyboard();
		~sdKeyboard();

		// �豸��ʼ��/����/����
		bool	Initialize(LPDIRECTINPUT8 lpInputDevice, HWND hWnd);
		void	Update();
		void	Destroy();

		// ����״̬���
		unsigned char	IsAnyKeyDown() const;
		unsigned char	IsAnyKeyPressed() const;
		bool			IsKeyDown(unsigned char uiKey) const;
		bool			IsKeyPressed(unsigned char uiKey) const;
		bool			IsKeyReleased(unsigned char uiKey) const;
		
	private:
		LPDIRECTINPUTDEVICE8	m_lpKeyboardDevice;
		unsigned char			m_ucKeyState[256];
		unsigned char			m_ucLastKeyState[256];
	};
}
#endif