#include "Input.h"

CInput::CInput() :
	m_lpDirectInput(0),
	m_lpKeyBoardDevice(0),
	m_lpMouseDevice(0)
{
	m_cursorLocation.x = 0;
	m_cursorLocation.y = 0;
}

CInput* CInput::s_Instance = 0;

CInput* CInput::getInstance()
{
	if (s_Instance == 0)
	{
		s_Instance = new CInput();
	}
	return s_Instance;
}

void CInput::InitializeInput()
{
	HRESULT result;

	result = DirectInput8Create(
		GetModuleHandle(0),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_lpDirectInput,
		0);


	result = m_lpDirectInput->CreateDevice(GUID_SysKeyboard, &m_lpKeyBoardDevice, 0);


	DIPROPDWORD dipdw;

    dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    dipdw.dwData            = 1024; // Arbitary buffer size

	HRESULT hr = m_lpKeyBoardDevice->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
	if (hr != DI_OK) return;

	result = m_lpDirectInput->CreateDevice(GUID_SysMouse, &m_lpMouseDevice, 0);

	for (int i = 0; i < 256; i++)
	{
		m_PressKey[i] = false;
		m_currentBuffer[i] = 0;
		m_previousBuffer[i] = 0;
	}
}

void CInput::InitializeKeyBoardDevice(HWND handleWindow)
{
	HRESULT result;
	result = m_lpKeyBoardDevice->SetDataFormat(&c_dfDIKeyboard);

	result = m_lpKeyBoardDevice->SetCooperativeLevel(handleWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	result = m_lpKeyBoardDevice->Acquire();
}

void CInput::InitializeMouseDevice(HWND handleWindow)
{
	HRESULT result;

	ZeroMemory(&m_mouseState, sizeof(m_mouseState));

	result = m_lpMouseDevice->SetDataFormat(&c_dfDIMouse2);


	result=m_lpMouseDevice->SetCooperativeLevel(handleWindow,DISCL_NONEXCLUSIVE|DISCL_FOREGROUND);

	result = m_lpMouseDevice->Acquire();
}

bool CInput::IsMouseRightDown()
{
	return ((m_mouseState.rgbButtons[1] & 0x80)!=0);
}

bool CInput::IsMouseLeftDown()
{
	return ((m_mouseState.rgbButtons[0] & 0x80)!=0);
}

bool CInput::IsMouseRightPress()
{
	return (((m_previousMouseState.rgbButtons[1] & 0x80) == 0) && ((m_mouseState.rgbButtons[1] & 0x80) != 0));
}

bool CInput::IsMouseLeftPress()
{
	return (((m_previousMouseState.rgbButtons[0] & 0x80) == 0) && ((m_mouseState.rgbButtons[0] & 0x80) != 0));
}

void CInput::UpdateKeyBoard()
{
	memcpy(m_previousBuffer, m_currentBuffer, 256);
	m_lpKeyBoardDevice->Acquire(); // Acquire device
	m_lpKeyBoardDevice->GetDeviceState(sizeof(m_currentBuffer), (LPVOID)&m_currentBuffer);

	DWORD dwElements = 1024;
	HRESULT hr = m_lpKeyBoardDevice->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), m_KeyEvents, &dwElements, 0);

	if (!FAILED(hr))
	{
		for( DWORD i = 0; i < dwElements; i++ ) 
		{
			int KeyCode = m_KeyEvents[i].dwOfs;
			int KeyState = m_KeyEvents[i].dwData;
			if ( (KeyState & 0x80) > 0)
				m_PressKey[KeyCode] = true;
			else 
				m_PressKey[KeyCode] = false;
		}
	}
	else
	{
		for (int i = 0; i < 256; i++)
		{
			m_PressKey[i] = false;
		}
	}
}

bool CInput::IsKeyDown(int keyCode)
{
	if (m_currentBuffer[keyCode] & 0x00000080)
	{
		return true;
	}
	return false;
}

bool CInput::IsKeyUp(int keyCode)
{
	if (m_currentBuffer[keyCode] & 0x00000080)
	{
		return false;
	}
	return true;
}

void CInput::SetKeyDown(int keyCode)
{
	m_currentBuffer[keyCode] |= 0x00000080;
}

void CInput::SetKeyUp(int keyCode)
{
	m_currentBuffer[keyCode] &= 0x00000000;
}

bool CInput::IsKeyLeftUpAndKeyRightDown()
{
	return IsKeyUp(DIK_LEFT) && IsKeyDown(DIK_RIGHT);
}

bool CInput::IsKeyLeftDownAndKeyRightUp()
{
	return IsKeyDown(DIK_LEFT) && IsKeyUp(DIK_RIGHT);
}

bool CInput::IsKeyLeftDownAndKeyRightDown()
{
	return IsKeyDown(DIK_LEFT) && IsKeyDown(DIK_RIGHT);
}

bool CInput::IsKeyLeftUpAndKeyRightUp()
{
	return IsKeyUp(DIK_LEFT) && IsKeyUp(DIK_RIGHT);
}

bool CInput::IsKeyUpUpAndKeyDownUp()
{
	return IsKeyUp(DIK_UP) && IsKeyUp(DIK_DOWN);
}

bool CInput::IsKeyUpDownAndKeyDownDown()
{
	return IsKeyDown(DIK_UP) && IsKeyDown(DIK_DOWN);
}

bool CInput::IsKeyUpDownAndKeyDownUp()
{
	return IsKeyDown(DIK_UP) && IsKeyUp(DIK_DOWN);
}

bool CInput::IsKeyUpUpAndKeyDownDown()
{
	return IsKeyUp(DIK_UP) && IsKeyDown(DIK_DOWN);
}


bool CInput::IsKeyPress(int keyCode)
{
	if(
		(m_currentBuffer[keyCode] & 0x00000080) &&
		!(m_previousBuffer[keyCode] & 0x00000080))
	{
		return true;
	}
	return false;
}

bool CInput::IsKeyRelease(int keyCode)
{
	if(
		!(m_currentBuffer[keyCode] & 0x00000080) &&
		(m_previousBuffer[keyCode]	& 0x00000080))
	{
		return true;
	}
	return false;
	/*return !m_PressKey[keyCode];*/
}

void CInput::UpdateMouse()
{
	memcpy(m_previousMouseState.rgbButtons, m_mouseState.rgbButtons, 8);
	ZeroMemory(&m_mouseState, sizeof(m_mouseState));
	HRESULT result = m_lpMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), (LPVOID)&m_mouseState);

	m_cursorLocation.x += m_mouseState.lX;
	m_cursorLocation.y += m_mouseState.lY;

	if(FAILED(result))
	{
		ZeroMemory(&m_mouseState, sizeof(m_mouseState));
		m_lpMouseDevice->Acquire();
	}

}

D3DXVECTOR2 CInput::GetCursorLocation()
{
	return D3DXVECTOR2((float)m_mouseState.lX, (float)m_mouseState.lY);
}

void CInput::Release()
{
	SAFE_RELEASE(m_lpDirectInput);
	SAFE_RELEASE(m_lpKeyBoardDevice);
	SAFE_RELEASE(m_lpMouseDevice);
}

CInput::~CInput()
{
	Release();
}