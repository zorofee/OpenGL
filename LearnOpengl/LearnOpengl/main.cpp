#pragma once
//
//#ifndef STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_IMPLEMENTATION
//#endif // !STB_IMAGE_IMPLEMENTATION
//

//----------------GetStarted--------------
//#include "GetStarted/Triangle.h"
//#include "GetStarted/Triangle_Practice.h"
//#include "GetStarted/Shader_Practice.h"
//#include "GetStarted/Textures.h"
//#include "GetStarted/HelloWindow.h"
//#include "GetStarted/HelloWindow_Practice.h"
//#include "GetStarted/Transformations.h"
//#include "GetStarted/CoordinateSystems.h"

//----------------Lighting--------------
//#include "Lighting/LightColors.h"
//#include "Lighting/BasicLighting.h"
//#include "Lighting/4.2Materials.h"
//#include "Lighting/4.3LightingMaps.h"
//#include "Lighting/LightCasters.h"

//----------------AdvancedOpengl--------------
//#include "AdvancedOpengl/DepthTest.h"
//#include "AdvancedOpengl/GeometryShader.h"
//#include "AdvancedOpengl/MSAA.h"
//#include "AdvancedOpengl/MSAA_off_screen.h"
//#include "AdvancedOpengl/FrameBuffers.h"

//----------------AdvancedLighting--------------
#include "AdvancedLighting/SSAO.h"
//#include "AdvancedLighting/StencilTesting.h"
//#include "AdvancedLighting/ShadowMap.h"
//#include "AdvancedLighting/DepthMap.h"
//#include "AdvancedLighting/NormalMap.h"
//#include "AdvancedLighting/Hdr.h"
//#include "AdvancedLighting/DeferredShading.h"

//----------------PBR--------------
//#include "PBR/PBR_Lighting.h"
//#include "PBR/PBR_Texture.h"

int main()
{
	//HelloWindow_Practice::main();
	//Triangle::main();
	//Triangle_Practice::main();
	//Textures::main();
	//ShaderPractice::main();
	//Transformations::main();
	//CoordinateSystems::main();


	//LightColors::main();
	//BasicLighting::main();
	//Materials::main();
	//LightingMaps::main();
	//LightCasters::main();

	//GeometryShader::main();
	//DepthTest::main();
	//MSAA::main();
	//MSAA_off_screen::main();
	//FrameBuffers::main();

	//DeferredShading::main();
	ssao::ssao_main();
	//StencilTesting::main();
	//ShadowMap::main();
	//DepthMap::main();
	//HDR::main();
	//NormalMap::main();

	//PBR::pbr_main();
	//PBR_Texture::main();
	
	return 0;
}
