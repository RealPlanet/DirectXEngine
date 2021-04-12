#pragma once
/*
*	Generics header containing includes and structs used frequently
*/

#include <memory>
#include "..\Utility\Vector2.h"
#include "..\Utility\Vector3.h"
#include "..\Utility\Vector4.h"
#include "..\Utility\Matrix4x4.h"

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
class Material;

typedef std::shared_ptr<SwapChain>		SwapChainPtr;
typedef std::shared_ptr<DeviceContext>	DeviceContextPtr;
typedef std::shared_ptr<VertexBuffer>	VertexBufferPtr;
typedef std::shared_ptr<IndexBuffer>	IndexBufferPtr;
typedef std::shared_ptr<ConstantBuffer>	ConstantBufferPtr;
typedef std::shared_ptr<VertexShader>	VertexShaderPtr;
typedef std::shared_ptr<PixelShader>	PixelShaderPtr;

typedef std::shared_ptr<Resource>		ResourcePtr;
typedef std::shared_ptr<Texture>		TexturePtr;
typedef std::shared_ptr<Mesh>			MeshPtr;
typedef std::shared_ptr<Material>		MaterialPtr;

