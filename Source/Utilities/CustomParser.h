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

#include <vector>
#include <string>

#include "Engine/Scene.h"

namespace Settings { struct Rendering; }


class Parser
{
public:
	Parser();
	~Parser();

	static Settings::Engine ReadSettings(const std::string& settingsFileName);
	static void ParseSetting(const std::vector<std::string>& line, Settings::Engine& settings);

	static SerializedScene ReadScene(Renderer* pRenderer, const std::string& sceneFileName);

	// Object initializations
	// ---------------------------------------------------------------------------------------------------------------
	// Transform	: pos(3), rot(3:euler), scale(1:uniform|3:xyz)
	// Camera		: near far vfov  pos(3:xyz)  yaw pitch
	// Light		: [p]oint/[s]pot,  color,   shadowing?  brightness,  range/angle,      pos(3),            rot(X>Y>Z)
	// BRDF			:
	// Phong		:
	// Object		: transform, brdf/phong, mesh
	static void ParseScene(Renderer* pRenderer, const std::vector<std::string>& command, SerializedScene& scene);
private:

};

