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

#include "Engine/Settings.h"

#include "Renderer/Light.h"

#include "Utilities/Camera.h"

#include "Skybox.h"
#include "GameObject.h"

struct SerializedScene;
class SceneManager;
class Renderer;
class TextRenderer;
struct SceneView;

// https://en.wikipedia.org/wiki/Template_method_pattern
// https://stackoverflow.com/questions/9724371/force-calling-base-class-virtual-function
// https://isocpp.org/wiki/faq/strange-inheritance#two-strategies-for-virtuals
// template method seems like a good idea here.
// the idea is that base class takes care of the common tasks among all scenes and calls the 
// customized functions of the derived classes through pure virtual functions

// Base class for scenes
class Scene
{
	friend class Engine;
public:
	Scene(SceneManager& sceneManager, std::vector<Light>& lights);
	~Scene() = default;

	// sets mpRenderer and moves objects from serializedScene into objects vector
	//
	void LoadScene(Renderer* pRenderer, TextRenderer* pTextRenderer, SerializedScene& scene, const Settings::Window& windowSettings);

	// clears object/light containers and camera settings
	//
	void UnloadScene();

	// updates selected camera and calls overridden Update from derived scene class
	//
	void UpdateScene(float dt);

	// calls .Render() on objects and calls derived class RenderSceneSpecific()
	//
	int Render(const SceneView& sceneView) const;
	virtual void RenderUI() const = 0;

	void ResetActiveCamera();

	inline void RenderSkybox(const XMMATRIX& viewProj) const { mSkybox.Render(viewProj); }

	// puts objects into provided vector if the RenderSetting.bRenderDepth is true
	//
	virtual void GetShadowCasters(std::vector<const GameObject*>& casters) const;

	// puts addresses of game objects in provided vector
	//
	virtual void GetSceneObjects(std::vector<const GameObject*>& objs) const;


	inline const EnvironmentMap& GetEnvironmentMap() const { return mSkybox.GetEnvironmentMap(); }
	inline const Camera& GetActiveCamera() const	{ return mCameras[mSelectedCamera]; }
	inline const Settings::SceneRender& GetSceneRenderSettings() const { return mSceneRenderSettings; }
	inline bool  HasSkybox() const { return mSkybox.GetSkyboxTexture() != -1; }

	EEnvironmentMapPresets GetActiveEnvironmentMapPreset() const { return mActiveSkyboxPreset; }
	void SetEnvironmentMap(EEnvironmentMapPresets preset);

protected:	// customization functions for derived classes
	// note:
	// int Render() is not a good idea for the derived classes: to leave the responsiblity to the implementor to count the 
	// number of objects rendered in a scene. this definitely needs refactoring... A game object factory might be a good idea.
	virtual void Update(float dt) = 0;
	virtual int Render(const SceneView& sceneView, bool bSendMaterialData) const = 0;
	virtual void Load(SerializedScene& scene) = 0;
	virtual void Unload() = 0;
	
protected:
	SceneManager&			mSceneManager;
	Renderer*				mpRenderer;
	TextRenderer*			mpTextRenderer;

	Skybox					mSkybox;
	EEnvironmentMapPresets	mActiveSkyboxPreset;	// dynamic skybox changing

	std::vector<Camera>		mCameras;
	std::vector<Light>&		mLights;
	std::vector<GameObject> mObjects;

	int mSelectedCamera;

	Settings::SceneRender	mSceneRenderSettings;
};

struct SerializedScene
{
	std::vector<Settings::Camera>	cameras;
	std::vector<Light>				lights;
	std::vector<GameObject>			objects;
	Settings::SceneRender			settings;
	char loadSuccess = '0';
};