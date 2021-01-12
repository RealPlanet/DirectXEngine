#include "IndexBuffer.h"
#include "GraphicsEngine.h"

bool IndexBuffer::load(void* list_indices, UINT list_size)
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


    if (FAILED(GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buffer_description, &init_data, &m_buffer)))
    {
        return false;
    }


    return true;
}

bool IndexBuffer::release()
{
    m_buffer->Release();
    delete this;
    return true;
}

UINT IndexBuffer::getSizeIndexList()
{
    return this->m_size_list;
}
