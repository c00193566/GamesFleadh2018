#include "SceneManager.h"

SceneManager::Scenes SceneManager::m_currentScene;
Scene* SceneManager::m_scene;
vector<Scene*> SceneManager::m_sceneList;

SceneManager::SceneManager()
{
	m_sceneList.push_back(new Level1);
	m_scene = m_sceneList.at(SceneManager::level1);
	m_currentScene = Scenes::level1;
}

SceneManager::~SceneManager() {}

void SceneManager::EventScene()
{
	m_scene->Event();
}

void SceneManager::ChangeStates(SceneManager::Scenes newScene)
{
	switch (newScene)
	{
	case SceneManager::level1:
		cout << "going to: Level 1!" << endl;
		m_scene = m_sceneList.at(SceneManager::level1);
		m_currentScene = Scenes::level1;
		break;
	}
}

void SceneManager::LoadNextLevel()
{
	m_scene->Initialise();
}

void SceneManager::UpdateScene()
{
	m_scene->Update();
}

void SceneManager::RenderScene()
{
	if (m_scene != nullptr)
	{
		m_scene->Render();
	}
}