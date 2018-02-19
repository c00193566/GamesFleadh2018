#pragma once
#include <iostream>
#include <vector>
#include "RenderSystem.h"
#include "Scene.h"
#include "Level1.h"

using namespace std;

class SceneManager
{
public:
	enum Scenes
	{
		level1 = 0
	};

	SceneManager();
	~SceneManager();
	//Switches between the scenes
	static void ChangeStates(Scenes newScene);
	void LoadNextLevel();


	Scenes GetCurrentState()
	{
		return m_currentScene;
	}
	void EventScene();
	void UpdateScene();
	void RenderScene();

	Scene* getScene()
	{
		return m_scene;
	};

private:
	static Scenes m_currentScene;
	static Scene* m_scene;
	static vector<Scene*> m_sceneList;
};