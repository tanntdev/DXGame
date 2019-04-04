#include "Texture.h"
CTexture::CTexture()
{
	m_lpTexture = 0;
}

CTexture::CTexture(const CTexture& Texture)
{
	m_lpTexture = LPDIRECT3DTEXTURE9(Texture.m_lpTexture);
	m_Width = Texture.m_Width;
	m_Height = Texture.m_Height;
}

CTexture::~CTexture()
{
	UnLoadTexture();
}

void CTexture::LoadTextureFromFile(LPDIRECT3DDEVICE9 _lpDirectDevice, LPCSTR fileName, D3DXCOLOR ColorKey)
{
	D3DXIMAGE_INFO _infoImg;
	HRESULT hr;
	hr = D3DXGetImageInfoFromFileA(fileName, &_infoImg);
	m_Width = _infoImg.Width;
	m_Height = _infoImg.Height;

	hr = D3DXCreateTextureFromFileExA(
		_lpDirectDevice,
		fileName,
		_infoImg.Width,
		_infoImg.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		ColorKey,
		&_infoImg,
		0,
		&m_lpTexture
		);
}

void CTexture::Render(LPD3DXSPRITE _lpDSpriteHandle, D3DXVECTOR2 position, D3DXVECTOR2 Center, D3DXVECTOR2 scale, float angle, D3DCOLOR color, RECT *srcRect, float deep)
{
	D3DXVECTOR3 currentPosition(position.x, position.y, deep);// curr pos

	D3DXMATRIX oldMatrix; 

	_lpDSpriteHandle->GetTransform(&oldMatrix);

	D3DXVECTOR2 centerScale = D3DXVECTOR2(position.x, position.y);// Toa do tam texture

	D3DXMATRIX matrixScalingRotate; //ma tran rotate, scale

	D3DXMatrixTransformation2D(&matrixScalingRotate, &centerScale, 0.0f, &scale, &Center, D3DXToRadian(angle), 0);

	D3DXMATRIX finalMatrix = matrixScalingRotate * oldMatrix;

	_lpDSpriteHandle->SetTransform(&finalMatrix); //ma tran chuyen toa do vi tri cua vat the tu the gioi thuc sang toa do trong directX de ve

	_lpDSpriteHandle->Draw(
		this->m_lpTexture,
		srcRect,
		&D3DXVECTOR3((float)(srcRect->right - srcRect->left)/2, (float)(srcRect->bottom - srcRect->top)/2, 0),
		&currentPosition,
		color);

	_lpDSpriteHandle->SetTransform(&oldMatrix);
}



void CTexture::RenderWithoutTransform(LPD3DXSPRITE _lpDSpriteHandle, D3DXVECTOR2 position, D3DXVECTOR2 Center, D3DXVECTOR2 scale, float angle, D3DCOLOR color, RECT *srcRect, float deep)
{
	D3DXVECTOR2 CamTransDistance;
	CamTransDistance.x = -Camera::getInstance()->GetMatrixTranslate()._41;
	CamTransDistance.y = Camera::getInstance()->GetMatrixTranslate()._42;

	position.y += Camera::getInstance()->getBound().bottom;
	Center.y += Camera::getInstance()->getBound().bottom;
	D3DXVECTOR3 currentPosition(position.x + CamTransDistance.x, position.y, deep); //toa do trong the gioi thuc

	D3DXMATRIX oldMatrix; //ma tran luu lai phep transform cua SpriteBatch

	_lpDSpriteHandle->GetTransform(&oldMatrix);
	
	D3DXVECTOR2 centerScale = D3DXVECTOR2(position.x, position.y);//lay vi tri cua vat the lam tam xoay(vi vi tri cua vat la vi tri chinh giua cua vat)

	D3DXMATRIX matrixScalingRotate; //ma tran rotate, scale

	D3DXMatrixTransformation2D(&matrixScalingRotate, &centerScale, 0.0f, &scale, &Center, D3DXToRadian(angle), 0);

	D3DXMATRIX finalMatrix = matrixScalingRotate * oldMatrix;

	_lpDSpriteHandle->SetTransform(&finalMatrix); //ma tran chuyen toa do vi tri cua vat the tu the gioi thuc sang toa do trong directX de ve

	_lpDSpriteHandle->Draw(
		this->m_lpTexture,
		srcRect,
		&D3DXVECTOR3((float)(srcRect->right - srcRect->left)/2, (float)(srcRect->bottom - srcRect->top)/2, 0),
		&currentPosition,
		color);

	_lpDSpriteHandle->SetTransform(&oldMatrix);
}

void CTexture::RenderTexture(LPD3DXSPRITE _lpDSpriteHandle,const RECT* sourceRect, const D3DXVECTOR3* Center, const D3DXVECTOR3* Position, D3DCOLOR Color)
{
	_lpDSpriteHandle->Draw(m_lpTexture, sourceRect, Center, Position, Color);
}

void CTexture::UnLoadTexture()
{
	SAFE_RELEASE(m_lpTexture);
	m_lpTexture = 0;
}
