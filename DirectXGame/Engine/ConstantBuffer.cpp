#include "ConstantBuffer.h"
#include "GraphicsEngine.h"

bool ConstantBuffer::load(void* buffer, UINT buffer_size)
{
    if (m_buffer) m_buffer->Release();

    D3D11_BUFFER_DESC buffer_description = {};
    buffer_description.Usage = D3D11_USAGE_DEFAULT;
    buffer_description.ByteWidth = buffer_size;
    buffer_description.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    buffer_description.CPUAccessFlags = 0;
    buffer_description.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = buffer;

    if (FAILED(GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buffer_description, &init_data, &m_buffer)))
    {
        return false;
    }

    return true;
}

void ConstantBuffer::update(DeviceContext* context, void* buffer)
{
    context->m_device_context->UpdateSubresource(this->m_buffer, NULL, NULL, buffer, NULL, NULL);
}

bool ConstantBuffer::release()
{
    if(m_buffer) m_buffer->Release();
    delete this;
    return true;
}