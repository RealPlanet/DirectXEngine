#include "IndexBuffer.h"
#include "RenderSystem.h"
#include <exception>

IndexBuffer::IndexBuffer(RenderSystem* system, void* list_indices, UINT list_size)
    : m_system{ system }
{
    if (m_buffer) m_buffer->Release();

    D3D11_BUFFER_DESC buffer_description = {};
    buffer_description.Usage = D3D11_USAGE_DEFAULT;
    buffer_description.ByteWidth = 4 * list_size;
    buffer_description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffer_description.CPUAccessFlags = 0;
    buffer_description.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = list_indices;

    m_size_list = list_size;


    if (FAILED(m_system->m_d3d_device->CreateBuffer(&buffer_description, &init_data, &m_buffer)))
    {
        throw std::exception("IndexBuffer not created successfully");
    }
}

IndexBuffer::~IndexBuffer()
{
    m_buffer->Release();
}

UINT IndexBuffer::getSizeIndexList()
{
    return this->m_size_list;
}
