#include "VertexBuffer.h"
#include "GraphicsEngine.h"

bool VertexBuffer::load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_bytecode, UINT size_byte_shader)
{
    if (m_buffer) m_buffer->Release();
    if (m_layout) m_layout->Release();

    D3D11_BUFFER_DESC buffer_description = {};
    buffer_description.Usage = D3D11_USAGE_DEFAULT;
    buffer_description.ByteWidth = size_vertex * size_list;
    buffer_description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffer_description.CPUAccessFlags = 0;
    buffer_description.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = list_vertices;

    m_size_vertex = size_vertex;
    m_size_list = size_list;


    if ( FAILED( GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buffer_description, &init_data, &m_buffer) ) )
    {
        return false;
    }

    D3D11_INPUT_ELEMENT_DESC layout[] = {
        // SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT- ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    UINT layout_size = ARRAYSIZE(layout);

    if ( FAILED(GraphicsEngine::get()->m_d3d_device->CreateInputLayout(layout, layout_size, shader_bytecode, size_byte_shader, &m_layout)) )
    {
        return false;
    }

    return true;
}

bool VertexBuffer::release()
{
    m_layout->Release();
    m_buffer->Release();
    delete this;
    return true;
}

UINT VertexBuffer::getSizeVertexList()
{
    return this->m_size_list;
}
