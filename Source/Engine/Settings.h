//	DX11Renderer - VDemo | DirectX11 Renderer
//	Copyright(C) 2016  - Volkan Ilbeyli
//
//	This program is free software : you can redistribute it and / or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.If not, see <http://www.gnu.org/licenses/>.
//
//	Contact: volkanilbeyli@gmail.com

#pragma once

namespace Settings
{
	struct Window
	{
		int		width;
		int		height;
		int		fullscreen;
		int		vsync;
	};

	struct Camera 
	{
		union
		{
			float		fovH;
			float		fovV;
		};
		float		nearPlane;
		float		farPlane;
		float		aspect;
		float		x, y, z;
		float		yaw, pitch;
	};

	struct ShadowMap 
	{
		size_t	dimension;
	};

	struct PostProcess 
	{
		struct Bloom 
		{
			float	threshold_brdf;
			float	threshold_phong;
			int     blurPassCount;
		} bloom;

		struct Tonemapping 
		{
			float	exposure;
		} toneMapping;

		bool HDREnabled = false;
	};
	
	struct Rendering
	{
		ShadowMap	shadowMap;
		PostProcess postProcess;
		bool		bUseDeferredRendering;
		bool		bUseBRDFLighting;	// should use enums when there's more than brdf and blinn-phong lighting
		bool		bAmbientOcclusion;
		bool		bEnableEnvironmentLighting;
		bool		bPreLoadEnvironmentMaps;
	};

	struct Engine 
	{
		Window window;
		Rendering rendering;
		int levelToLoad;
	};

	struct SceneRender
	{
		bool bAmbientOcclusionEnabled;	// screen-space ambient occlusion
		float ambientFactor;			// ambient lighting scalar
		bool bSkylightEnabled;			// ambient environment map lighting
		bool bBloomEnabled;				// bloom post effect
	};
};