#include "Soccer.h"
#include <Siv3D.hpp>
#include "MyKey.h"
#include <windows.h>
#include "MySocketServer.h"


Soccer::Soccer(void) {
	loadEffect = new SimpleLoadEffect();

	//アセットへロード
	FontAsset::Register(U"soccerfont", 70);
	FontAsset::Preload(U"soccerfont");
	TextureAsset::Register(U"soccerback", U"resources/images/backs/soccer.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"soccertitle", U"resources/images/items/game/soccer/title.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"soccerchoice", U"resources/images/items/game/soccer/choice.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"soccerkick", U"resources/images/items/game/soccer/kick.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"soccerresult", U"resources/images/items/game/soccer/result.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"soccerkicker1", U"resources/images/items/game/soccer/soccerkick1.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"soccerkicker2", U"resources/images/items/game/soccer/soccerkick2.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"soccerkeeper1", U"resources/images/items/game/soccer/soccerkeap1.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"soccerkeeper2", U"resources/images/items/game/soccer/soccerkeap2.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"backgameselect1", U"resources/images/items/game/soccer/So_backgameselect1.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"backgameselect2", U"resources/images/items/game/soccer/So_backgameselect2.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"startgame1", U"resources/images/items/game/soccer/So_startgame1.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"startgame2", U"resources/images/items/game/soccer/So_startgame2.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"black", U"resources/images/items/game/soccer/black.png", AssetParameter::LoadAsync());
	TextureAsset::Register(U"inter", U"resources/images/items/game/soccer/inter.png", AssetParameter::LoadAsync());

	nowScene = Soccer::TITLE;
	nextScene = Soccer::TITLE;
	oldNowScene = Soccer::INTERRUPTION;


}
Soccer::~Soccer(void) {
	//アセットからアンロード
	FontAsset::Unregister(U"soccerfont");
	TextureAsset::Unregister(U"soccerback");
	delete backAudio;
}
bool Soccer::isReady(void) {	//ロード終了してもいいかどうか
	if (TextureAsset::IsReady(U"soccerback")) {
		return true;
	}
	return false;
}
void Soccer::start(void) {	//ロード空けた後に実行されるもの
	//BGM再生開始
	backAudio = new Audio(U"resources/musics/backs/soccer.wav");
	backAudio->setLoop(true);
	backAudio->play();
}
void Soccer::update(void) {	//計算処理
	/*
	if (loadEffect->isEnd()) {//完全に明るくなったら1回実行される
		scene->start();//キーボードのロックが解除される
	}
	if (nowScene != nextScene) {//シーンの変更要求が行われていれば切り替える
		changeScene();
	}
	*/

	loadEffect->update();//ロードの計算処理
	if (nowScene != nextScene) {
		if (!loadEffect->isLoad()) {//ロード中ではないなら
			loadEffect->start();//ロードstart
		}
		if (loadEffect->isDark()) {//真っ暗の画面になっているかどうか
			loadEffect->nextState();//真っ暗の画面で停止させる
		}
		else if (loadEffect->isDarkWait()) {//ロード待機→明るくなり始め
			loadEffect->nextState();//画面を明るくし始める
			changeScene();//ゲームで作成したシーン移行関数
		}
	}
	if (loadEffect->isEnd()) {//完全に明るくなったら1回実行される
		startScene();
	}



	if (MyKey::getUpKeyDown()) {			//上キーが押されたときは接続が切れたと仮定する
		conecttingflag = 1;					//切断されたらconecttingflagを①にする
		stopGame();
	}
	else if (conecttingflag == 1) {
		stopGame();
	}

	if (MyKey::getDownKeyDown()) {
		conecttingflag = 0;
	}

	if (conecttingflag == 0) {
		switch (nowScene)//シーンによって計算処理を切り替える
		{
		case Soccer::TITLE: //タイトル
			updateTitle();
			break;
		case Soccer::SELECT_MODE: //キーパーかキッカーか
			updateSelect();
			break;
		case Soccer::THINKING: //うつところ　けってー！みたいな　角を狙うために振りぬこうてきなでけって加速度とる
			updateThinking();
			break;
		case Soccer::PRACTICAL_SKILL: //どこにうったかをはんだんする　対戦相手も判断するじっそうできるならやさしいとかつくりたいエフェクト
			updatePractical_skill();
			if (MyKey::getDecisionKey()) {
				setNextScene(RESULT);
			}
			break;
		case Soccer::RESULT: //
			updateResult();
			break;

			/*
			case Soccer::INTERRUPTION:
				stopGame();
				break;
				*/
		}
	}




	//nowScene = nextScene;

}

void Soccer::draw(void) {	//描画処理


	Vec3 vec = Sensor::getAcceleration();//加速度取得
	int x, y, z;
	x = vec.x;
	y = vec.y;
	z = vec.z;
	Print(U"SensorData" + Format(x));

	if (conecttingflag == 0) {
		TextureAsset(U"soccerback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		switch (nowScene)//シーンによって描画処理を切り替える
		{
		case Soccer::TITLE:
			drawTitle();
			break;
		case Soccer::SELECT_MODE:
			drawSelect();
			break;
		case Soccer::THINKING:
			//TextureAsset(U"soccerkick").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
			//drawThinking();
			break;
		case Soccer::PRACTICAL_SKILL:
			TextureAsset(U"soccerback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
			break;

		case Soccer::RESULT:
			TextureAsset(U"soccerresult").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
			//drawResult();
			break;
			/*
		case Soccer::INTERRUPTION:
			stopGame();
			break;
			*/
		default:
			TextureAsset(U"soccerresult").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
			break;
		}
	}

	loadEffect->draw();

}
void Soccer::outputResult(void) {//結果をDBへ出力する

}
void Soccer::changeScene() {//シーンを変更する
	switch (nowScene)
	{
	case Soccer::TITLE:
		//シーンを変更する前に処理したい内容を書く
		break;
	case Soccer::SELECT_MODE:
		break;
	case Soccer::THINKING:
		break;
	case Soccer::PRACTICAL_SKILL:
		break;
	case Soccer::RESULT:
		break;
	case Soccer::INTERRUPTION:
		break;
	default:
		break;
	}
	switch (nextScene)//初期化処理
	{
	case Soccer::TITLE:
		break;
	case Soccer::SELECT_MODE:
		break;
	case Soccer::THINKING:
		break;
	case Soccer::PRACTICAL_SKILL:
		break;
	case Soccer::RESULT:
		break;
	case Soccer::INTERRUPTION:
		break;
	}
	nowScene = nextScene;//切り替える
}
void Soccer::setNextScene(SOCCER_SCENE next) {//次のシーンへの移行要求を行う
	nextScene = next;
}
void Soccer::startScene() {
	switch (nowScene)
	{
	case Soccer::TITLE:
		//画面が明るくなってから1回だけ処理したい内容を書く。BGMなど
		break;
	case Soccer::SELECT_MODE:
		break;
	case Soccer::THINKING:
		break;
	case Soccer::PRACTICAL_SKILL:
		break;
	case Soccer::RESULT:
		break;
	default:
		break;
	}
}

//計算
void Soccer::updateTitle() {//できるならエンター押してにしたい
	if (MyKey::getLeftKeyDown()) {//セレクトモードへ
		inputBotton = 1;
	}
	else if (MyKey::getRightKeyDown()) {//家へ
		inputBotton = 2;
	}

	if (MyKey::getDecisionKey()) {
		if (inputBotton == 1) {
			setNextScene(SELECT_MODE);
		}
		else if (inputBotton == 2) {
			MySceneManager::setNextScene(SCENE::SELECT_MODE);
		}
	}

}


void Soccer::updateSelect() {      //キーパーかどっちかえらびたい
	static int flag = 0;
	if (MyKey::getLeftKeyDown()) {  //キッカー
		flag = 1;
		selecttype = 0;
		//setNextScene(THINKING);
	}

	else if (MyKey::getRightKeyDown()) {//キーパー
		flag = 1;
		selecttype = 1;
		//setNextScene(THINKING);

	}
	if (MyKey::getDecisionKey()) {
		if (flag == 1) {
			setNextScene(THINKING);
		}
	}


}
void Soccer::updateThinking() {   //準備のじかん
	if (MyKey::getDecisionKey()) {
		setNextScene(PRACTICAL_SKILL);
	}

}
void Soccer::updatePractical_skill() { //けったとき

	Vec3 vec = Sensor::getAcceleration();//加速度取得
	int x, y, z;
	x = vec.x;
	y = vec.y;
	z = vec.z;
	Print(U"SensorData" + Format(x));



	//どっちが勝ったか
	if (whichWin(z) == 1) {



	}


	//xがーのときと
	//yがーのときではんていかえるｘとｙで四つ方向きめて、あとは足した値のでかいほうで決める？？？
	//

		/*vec.x//X方向の加速度
		vec.y//Y方向の加速度
		vec.z//Z方向の加速度*/


}
void Soccer::updateResult() {  //つづけるかいなか
	static int inputRBotton = 0;
	if (MyKey::getLeftKeyDown()) {//セレクトモードへ
		inputRBotton = 1;

	}
	else if (MyKey::getRightKeyDown()) {//家へ
		inputRBotton = 2;

	}

	if (MyKey::getDecisionKey()) {
		if (inputRBotton == 1) {
			setNextScene(SELECT_MODE);
		}
		else if (inputRBotton == 2) {
			outputResult();
			MySceneManager::setNextScene(SCENE::SELECT_MODE);
		}
	}

}

bool Soccer::whichWin(int total) {  //どっちがかったか判断する関数
	int keepnumber, kicknumber;
	keepnumber = total;
	kicknumber = total;

	if (keepnumber > kicknumber) {
		return false;
	}

	return true;
}



//描画

void Soccer::drawTitle() {
	TextureAsset(U"soccertitle").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	if (inputBotton == 1) {
		TextureAsset(U"backgameselect1").drawAt(1400, 700);
		TextureAsset(U"startgame2").drawAt(600, 700);
	}
	else if (inputBotton == 2) {
		TextureAsset(U"backgameselect2").drawAt(1400, 700);
		TextureAsset(U"startgame1").drawAt(600, 700);
	}
}
void Soccer::drawSelect() {
	TextureAsset(U"soccerchoice").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	if (selecttype == 1) {
		TextureAsset(U"soccerkicker2").drawAt(1400, 700);
		TextureAsset(U"soccerkeeper1").drawAt(600, 700);
	}
	else if (selecttype == 2) {
		TextureAsset(U"soccerkicker1").drawAt(1400, 700);
		TextureAsset(U"soccerkeeper2").drawAt(600, 700);
	}
}
void Soccer::drawThinking() {
	switch (selecttype)
	{
	case 0:
		TextureAsset(U"soccerkicker1").drawAt(800, 800);
		TextureAsset(U"soccerkeeper2").drawAt(1500, 800);

	case 1:
		TextureAsset(U"soccerkicker2").drawAt(800, 800);
		TextureAsset(U"soccerkeeper1").drawAt(1500, 800);
		break;
	}
}
void Soccer::drawPractical_skill() {
}
void Soccer::drawResult() {

}


void Soccer::stopGame() {	//ゲームを一時中断する
	TextureAsset(U"inter").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);

}

//フレーム管理～～～～


