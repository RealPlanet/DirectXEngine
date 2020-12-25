#include "GraphicsEngine.h"

bool GraphicsEngine::init()
{
	/* DirectX devices usable by the graphics engine (from best to worst)
	HARDWARE == GPU
	WARP == HIGH PERFORMANCE CPU INSTRUCTIONS
	REFERENCE == LOWP ERFORMANCE CPU INSTRUCTIONS
	*/
	D3D_DRIVER_TYPE driver_types[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);
		
	/*
		DirectX instruction 
		D3D_FEATURE_LEVEL_11_0 == DirectX 11.0
	*/
	D3D_FEATURE_LEVEL feature_levels[] = {
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);


	HRESULT result = 0;
	/* 
		Loop through all the available devices and stop when an usable one is found
		Creates a D3D11 Device and returns if it succeded or not
	*/

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types; ++driver_type_index)
	{
		result = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL,
							feature_levels, num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);
		if (SUCCEEDED(result))
		{
			break;
		}
	}

	if (FAILED(result))
	{
		return false;
	}
		

	return true;
}

// Release all of the resources used by the graphics engine
bool GraphicsEngine::release()
{
	m_imm_context->Release();
	m_d3d_device->Release();

	return true;
}


GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine engine;
	return &engine;
}
