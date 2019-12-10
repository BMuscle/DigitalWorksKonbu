#include <Siv3D.hpp> // OpenSiv3D v0.4.2
#include "MySceneManager.h"
#include "MySqlite3.h"

void Main()
{
	if (!MySqlite3::initialize()) {
		return; //データベースの初期化失敗
	}
	Profiler::EnableAssetCreationWarning(false);	//アセットの警告オフ
	Window::Resize(1920, 1080);						//画面サイズを1920/1080に固定	
	Graphics::SetTargetFrameRateHz(60);				//FPSを60に固定
	MySceneManager::initialize();					//シーンの初期化処理
	

	while (System::Update())//ゲームループ
	{
		ClearPrint();//簡易文字列の消去
		MySceneManager::updateScene();	//シーンの計算処理
		MySceneManager::drawScene();	//シーンの描画処理
		//ClearPrint();//簡易文字列の消去　リリース時ONにする
	}

	MySceneManager::finalize();//シーンの終了処理

	if (!MySqlite3::finalize()) {
		return;	//データベースの終了処理失敗
	}
}
