#ifndef __BE_SCENE_MANAGER_H__
#define __BE_SCENE_MANAGER_H__

#include <memory>

#include "IScene.h"

namespace BE
{

class SceneManager
{
public:
	static SceneManager &getInstance();

	template<typename Scene>
	void changeScene()
	{
		m_nextScene = std::make_shared<Scene>();
	}

	void quit();
	bool isRunning() const;

	std::shared_ptr<IScene> getCurrentScene();
private:
	friend class Engine;

	SceneManager() = default;
	~SceneManager() = default;

	void updateSceneState();

	static SceneManager m_instance;

	std::shared_ptr<IScene> m_currentScene;
	std::shared_ptr<IScene> m_nextScene;

	bool m_isRunning{ false };
};

}

#endif // !__BE_SCENE_MANAGER_H__
