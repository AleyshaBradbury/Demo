#pragma once
class SceneManager
{
public:
	enum class Scene {
		Menu,
		Main
	};

	static void ChangeScene(Scene scene_);
	static void ChangeScene(int index);
	static Scene GetScene();

private:
	static Scene scene;
};

