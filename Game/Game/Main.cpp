#include <Siv3D.hpp> // OpenSiv3D v0.4.2
#include "MySceneManager.h"

void Main()
{
	Profiler::EnableAssetCreationWarning(false);
	Window::Resize(1920, 1080);
	Graphics::SetTargetFrameRateHz(60);
	MySceneManager::initialize();
	while (System::Update())
	{
		ClearPrint();
		MySceneManager::updateScene();
		MySceneManager::drawScene();
	}
	MySceneManager::finalize();
}
