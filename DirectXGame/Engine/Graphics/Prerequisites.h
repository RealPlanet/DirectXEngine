#pragma once
/*
*	Generics header containing includes and structs used frequently
*/

#include <memory>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix4x4.h"

class SwapChain;
class DeviceContext;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class RenderSystem;
class GraphicsEngine;
class Resource;
class ResourceManager;
class Texture;
class TextureManager;
class Mesh;
class MeshManager;

typedef std::shared_ptr<SwapChain>		SwapChainPtr;
typedef std::shared_ptr<DeviceContext>	DeviceContextPtr;
typedef std::shared_ptr<VertexBuffer>	VertexBufferPtr;
typedef std::shared_ptr<IndexBuffer>	IndexBufferPtr;
typedef std::shared_ptr<ConstantBuffer>	ConstantBufferPtr;
typedef std::shared_ptr<VertexShader>	VertexShaderPtr;
typedef std::shared_ptr<PixelShader>	PixelShaderPtr;

typedef std::shared_ptr<Resource>	ResourcePtr;
typedef std::shared_ptr<Texture>	TexturePtr;
typedef std::shared_ptr<Mesh>		MeshPtr;

struct vertex
{
	Vector3D position;
	Vector2D texcoord;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world = {};
	Matrix4x4 m_view = {};
	Matrix4x4 m_projection = {};

	Vector4D m_light_direction;
	Vector4D m_camera_position;

	unsigned int m_time = 0;
};

