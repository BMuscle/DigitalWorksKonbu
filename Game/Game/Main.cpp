#include <Siv3D.hpp> // OpenSiv3D v0.4.2
#include "MySceneManager.h"
#include "MySqlite3.h"
#include "Sensor.h"
#include "MySocketServer.h"
#include "User.h"

void Main()
{
	if (!MySqlite3::initialize()) {
		return; //データベースの初期化失敗
	}
	MySqlite3::DBCREATE();//データベースの作成→既にテーブルがある時は行われない
	Profiler::EnableAssetCreationWarning(false);	//アセットの警告オフ
	Window::Resize(1920, 1080);						//画面サイズを1920/1080に固定	
	Graphics::SetTargetFrameRateHz(60);				//FPSを60に固定
	MySceneManager::initialize();					//シーンの初期化処理
	Sensor::initialize(true);						//センサーデータの初期化
	MySocketServer::initialize();					//ソケット通信の初期化

	while (System::Update())//ゲームループ
	{
		ClearPrint();//簡易文字列の消去
		MySocketServer::update();
		Sensor::update();
		MySceneManager::updateScene();	//シーンの計算処理
		MySceneManager::drawScene();	//シーンの描画処理
		
		Sensor::debugPrint();

		//ClearPrint();//簡易文字列の消去　リリース時ONにする
	}
	MySocketServer::finalize();					//ソケット通信終了処理
	Sensor::finalize();							//センサーデータの終了処理
	MySceneManager::finalize();						//シーンの終了処理

	if (!MySqlite3::finalize()) {
		return;	//データベースの終了処理失敗
	}
}
