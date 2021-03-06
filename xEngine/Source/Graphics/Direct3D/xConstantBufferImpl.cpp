#include "xEngine.h"
#include "../xConstantBuffer.h"
#include "xConstantBufferImpl.h"

xConstantBuffer::xConstantBuffer(size_t size_in_bytes)
	: xBuffer(size_in_bytes)
{
	pImpl = new Impl();	

	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = mSizeInBytes;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;	

	gDevice->CreateBuffer(&desc, 0, &pImpl->mBuffer);	
}

xConstantBuffer::~xConstantBuffer()
{
	if (pImpl->mBuffer)
		pImpl->mBuffer->Release();
	xSAFE_DELETE(pImpl);
}

void xConstantBuffer::Flush()
{
	gDeviceContext->UpdateSubresource(pImpl->mBuffer, 0, 0, mData, 0, 0);
}