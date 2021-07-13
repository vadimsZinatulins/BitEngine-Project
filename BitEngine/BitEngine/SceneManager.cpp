#include "SceneManager.h"

namespace BE
{

SceneManager SceneManager::m_instance;

SceneManager &SceneManager::getInstance()
{
	return m_instance;
}

void SceneManager::quit()
{
	m_isRunning = false;
}

bool SceneManager::isRunning() const
{
	return m_isRunning;
}

std::shared_ptr<IScene> SceneManager::getCurrentScene()
{
	return m_currentScene;
}

void SceneManager::updateSceneState()
{
	if (m_nextScene)
	{
		if (!m_isRunning)
		{
			m_isRunning = true;
		}

		if (m_currentScene)
		{
			m_currentScene->shutdown();
			m_currentScene.reset();
		}

		m_currentScene.swap(m_nextScene);
		m_currentScene->initialize();
	}
}

}