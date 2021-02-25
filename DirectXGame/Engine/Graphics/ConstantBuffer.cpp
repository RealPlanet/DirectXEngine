#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "RenderSystem.h"
#include <exception>

ConstantBuffer::ConstantBuffer(RenderSystem* system, void* buffer, UINT buffer_size)
    : m_system{ system }, m_buffer{nullptr}
{
    D3D11_BUFFER_DESC buffer_description = {};
    buffer_description.Usage = D3D11_USAGE_DEFAULT;
    buffer_description.ByteWidth = buffer_size;
    buffer_description.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    buffer_description.CPUAccessFlags = 0;
    buffer_description.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = buffer;

    if (FAILED(m_system->m_d3d_device->CreateBuffer(&buffer_description, &init_data, &m_buffer)))
    {
        throw std::exception("ConstantBuffer not created successfully");
    }
}

ConstantBuffer::~ConstantBuffer()
{
    if (m_buffer) m_buffer->Release();
}

void ConstantBuffer::update(DeviceContext* context, void* buffer)
{
    context->m_device_context->UpdateSubresource(this->m_buffer, NULL, NULL, buffer, NULL, NULL);
}