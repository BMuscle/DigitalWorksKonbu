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
	TextureAsset::Register(U"soccerback", U"resources/images/backs/soccer.png");
	TextureAsset::Register(U"soccerback1", U"resources/images/items/game/soccer/soccer.png");
	TextureAsset::Register(U"soccerkicker1", U"resources/images/items/game/soccer/kicker.png");
	TextureAsset::Register(U"soccerkicker2", U"resources/images/items/game/soccer/kicker2.png");
	TextureAsset::Register(U"soccerkeeper1", U"resources/images/items/game/soccer/keeper.png");
	TextureAsset::Register(U"soccerkeeper2", U"resources/images/items/game/soccer/keeper2.png");
	TextureAsset::Register(U"backgameselect1", U"resources/images/items/game/soccer/So_backgameselect1.png");
	TextureAsset::Register(U"backgameselect2", U"resources/images/items/game/soccer/So_backgameselect2.png");
	TextureAsset::Register(U"startgame1", U"resources/images/items/game/soccer/So_startgame1.png");
	TextureAsset::Register(U"startgame2", U"resources/images/items/game/soccer/So_startgame2.png");
	TextureAsset::Register(U"inter", U"resources/images/items/game/soccer/inter.png");
	TextureAsset::Register(U"replay1", U"resources/images/items/game/soccer/replay1.png");
	TextureAsset::Register(U"replay2", U"resources/images/items/game/soccer/replay2.png");
	
	TextureAsset::Register(U"wearleg", U"resources/images/items/game/soccer/ashitukeru.png");
	TextureAsset::Register(U"wearhand", U"resources/images/items/game/soccer/tekubitukeru.png");
	TextureAsset::Register(U"s_setu0", U"resources/images/items/game/soccer/setumei0.png");
	TextureAsset::Register(U"s_setu1", U"resources/images/items/game/soccer/setumei1.png");
	TextureAsset::Register(U"s_setu2", U"resources/images/items/game/soccer/setumei2.png");
	TextureAsset::Register(U"s_setu3", U"resources/images/items/game/soccer/setumei3.png");

	TextureAsset::Register(U"three", U"resources/images/items/game/soccer/three.png");
	TextureAsset::Register(U"two", U"resources/images/items/game/soccer/two.png");
	TextureAsset::Register(U"one", U"resources/images/items/game/soccer/one.png");
	TextureAsset::Register(U"shoot", U"resources/images/items/game/soccer/shoot.png");
	TextureAsset::Register(U"titlemesse", U"resources/images/items/game/soccer/soccertitle.png");
	TextureAsset::Register(U"selectpoji", U"resources/images/items/game/soccer/selectpoji.png");
	TextureAsset::Register(U"soccerboal", U"resources/images/items/game/soccer/soccerboal.png");
	TextureAsset::Register(U"soccerboal2", U"resources/images/items/game/soccer/soccerboal2.png");
	TextureAsset::Register(U"soccerboal3", U"resources/images/items/game/soccer/soccerboal3.png");
	TextureAsset::Register(U"soccerboal4", U"resources/images/items/game/soccer/soccerboal4.png");
	TextureAsset::Register(U"gameback", U"resources/images/items/game/soccer/gameback.png");
	TextureAsset::Register(U"gatya200", U"resources/images/items/game/soccer/resultwin.png");
	TextureAsset::Register(U"gatya50", U"resources/images/items/game/soccer/resultlose.png");
	TextureAsset::Register(U"soccerboal1", U"resources/images/items/game/soccer/soccerboal1.png");
	TextureAsset::Register(U"soccerboal2", U"resources/images/items/game/soccer/soccerboal2.png");
	TextureAsset::Register(U"soccerboal3", U"resources/images/items/game/soccer/soccerboal3.png");
	TextureAsset::Register(U"soccerboal4", U"resources/images/items/game/soccer/soccerboal4.png");
	TextureAsset::Register(U"soccerboal5", U"resources/images/items/game/soccer/soccerboal5.png");
	TextureAsset::Register(U"soccerboal6", U"resources/images/items/game/soccer/soccerboal6.png");
	TextureAsset::Register(U"soccerboal7", U"resources/images/items/game/soccer/soccerboal7.png");
	TextureAsset::Register(U"soccerboal8", U"resources/images/items/game/soccer/soccerboal8.png");
	TextureAsset::Register(U"saveright", U"resources/images/items/game/soccer/saveright.png");
	TextureAsset::Register(U"saveleft", U"resources/images/items/game/soccer/saveleft.png");
	TextureAsset::Register(U"goalright", U"resources/images/items/game/soccer/goalright.png");
	TextureAsset::Register(U"goalleft", U"resources/images/items/game/soccer/goalleft.png");
	
	
	AudioAsset::Register(U"whistle", U"resources/musics/items/game/soccer/whistle.wav");
	AudioAsset::Register(U"drum", U"resources/musics/items/game/soccer/drum.wav");
	AudioAsset::Register(U"kick", U"resources/musics/items/game/soccer/kick.wav");
	AudioAsset::Register(U"goal", U"resources/musics/items/game/soccer/goal.wav");
	AudioAsset::Register(U"miss", U"resources/musics/items/game/soccer/miss.wav");

	AudioAsset::Register(U"clear", U"resources/musics/items/game/soccer/clear.mp3");
	AudioAsset::Register(U"zannen", U"resources/musics/items/game/soccer/zannen.mp3");


	nowScene = Soccer::TITLE;
	nextScene = Soccer::TITLE;
	oldNowScene = Soccer::INTERRUPTION;

	endMusic = false;
}
Soccer::~Soccer(void) {
	//アセットからアンロード
	FontAsset::Unregister(U"soccerfont");
	TextureAsset::Unregister(U"soccerback");
	AudioAsset::Unregister(U"whistle");
	AudioAsset::Unregister(U"drum");
	AudioAsset::Unregister(U"kick");
	AudioAsset::Unregister(U"goal");
	AudioAsset::Unregister(U"miss");
	AudioAsset::Unregister(U"clear");
	AudioAsset::Unregister(U"zannen");

	delete backAudio;
}
bool Soccer::isReady(void) {	//ロード終了してもいいかどうか
	return true;
}
void Soccer::start(void) {	//ロード空けた後に実行されるもの
	delete backAudio;
	backAudio = new Audio(U"resources/musics/backs/soccer/title.mp3");
	backAudio->setLoop(true);
	backAudio->setVolume(0.1);
	backAudio->play();	
}
void Soccer::update(void) {	//計算処理
	frameCount();
	if (nowScene != nextScene) {//シーンの変更要求が行われていれば切り替える
		changeScene();
	}
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
		case Soccer::BEFORE_THINKING:
			updateBeforeThiking();
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
		case Soccer::BEFORE_THINKING:
			drawBeforeThiking();
			break;
		case Soccer::THINKING:
			drawThinking();
			break;
		case Soccer::PRACTICAL_SKILL:
			drawPractical_skill();
			break;
		case Soccer::RESULT:
			drawResult();
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
	gachasoccer;
	maxpoint;
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
		//BGM再生開始
		delete backAudio;
		backAudio = new Audio(U"resources/musics/backs/soccer/title.mp3");
		backAudio->setLoop(true);
		backAudio->setVolume(0.1);
		backAudio->play();
		break;
	case Soccer::SELECT_MODE:
		//BGM再生開始
		delete backAudio;
		backAudio = new Audio(U"resources/musics/backs/soccer/game.mp3");
		backAudio->setLoop(true);
		backAudio->setVolume(0.1);
		backAudio->play();
		break;
	case Soccer::THINKING:
		break;
	case Soccer::PRACTICAL_SKILL:
		break;
	case Soccer::RESULT:
		//BGM再生開始
		delete backAudio;
		backAudio = new Audio(U"resources/musics/backs/soccer/result.mp3");
		backAudio->setLoop(true);
		backAudio->setVolume(0.1);
		backAudio->play();

		endMusic = false;
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


void Soccer::updateTitle() {//できるならエンター押してにしたい
	if (MyKey::getLeftKeyDown()) {
		inputUBotton = 2;
	}
	else if (MyKey::getRightKeyDown()) {
		inputUBotton = 1;
	}

	if (MyKey::getDecisionKey()) {
		if (inputUBotton == 1) {
			setNextScene(SELECT_MODE);
		}
		else if (inputUBotton == 2) {
			MySceneManager::setNextScene(SCENE::SELECT_MODE);
		}
		GeneralSoundEffects::play(SE_NAME::DECISION);
	}

}

void Soccer::drawTitle() {
	//TextureAsset(U"soccertitle").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	TextureAsset(U"titlemesse").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	if (inputUBotton == 1) {
		TextureAsset(U"startgame2").drawAt(1400, 700);
		TextureAsset(U"backgameselect1").drawAt(600, 700);
	}
	else if (inputUBotton == 2) {
		TextureAsset(U"backgameselect2").drawAt(600, 700);
		TextureAsset(U"startgame1").drawAt(1400, 700);
	}
}


void Soccer::updateSelect() {      //キーパーかどっちかえらびたい
	static int flag = 0;
	if (MyKey::getLeftKeyDown()) {  //キッカー
		flag = 1;
		selecttype = 0;
	}
	else if (MyKey::getRightKeyDown()) {//キーパー
		flag = 1;
		//selecttype = 1;

	}
	if (MyKey::getDecisionKey()) {
		setNextScene(BEFORE_THINKING);
		GeneralSoundEffects::play(SE_NAME::DECISION);
	}

}

void Soccer::updateBeforeThiking()
{
	if (MyKey::getDecisionKey()) {
		if (readflag == 0) {
			readflag = 1;
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
		else if (readflag == 1) {
			readflag = 2;
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
		else if (readflag == 2) {
			readflag = 3;
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
		else if (readflag == 3) {
			readflag = 4;
			GeneralSoundEffects::play(SE_NAME::CURSOR);
		}
		else if (readflag == 4) {
			setNextScene(THINKING);
			GeneralSoundEffects::play(SE_NAME::DECISION);
		}
		
	}
}

void Soccer::updateThinking() {
	readflag = 0;
	if (countdownflag == 0) {
		coutdown--;
	}

	if (coutdown == 239) {
		AudioAsset(U"drum").setVolume(0.3);
		AudioAsset(U"drum").setPosSec(0);
		AudioAsset(U"drum").play();
	}
	else if (coutdown == 180) {
		AudioAsset(U"drum").setVolume(0.3);
		AudioAsset(U"drum").setPosSec(0);
		AudioAsset(U"drum").play();
	}
	else if (coutdown == 120) {
		AudioAsset(U"drum").setVolume(0.3);
		AudioAsset(U"drum").setPosSec(0);
		AudioAsset(U"drum").play();
	}
	else if (coutdown == 60) {
		AudioAsset(U"whistle").setVolume(0.3);
		AudioAsset(U"whistle").setPosSec(0);
		AudioAsset(U"whistle").play();
	}
	else if (coutdown == 0) {
		AudioAsset(U"kick").setVolume(0.3);
		AudioAsset(U"kick").setPosSec(0);
		AudioAsset(U"kick").play();
	}
	
	if (coutdown >= 180 && thinkdrawflag == 0) {
		thinkdrawflag = 0;
	}
	else if (coutdown >= 120) {
		thinkdrawflag = 1;
	}
	else if (coutdown >= 60) {
		thinkdrawflag = 2;
	}
	else if (coutdown >= 0) {
		thinkdrawflag = 3;

		//センサ接続時コメントアウトを外す
		/////センサーからの値取得/////
		Vec3 vec = Sensor::getAcceleration();	//加速度取得
		int vecter_z;
		vecter_z = vec.z;
		Print(U"vecter_z" + Format(vecter_z));
		if (vecter_z < 0) {
			shootpower = abs(vecter_z);
		}
		else {
			shootpower = vecter_z;
		}
		if (highshootpower < shootpower) {
			highshootpower = shootpower;
		}

		Vec3 accel = Sensor::getDirection();	//方向取得
		int accel_x;
		accel_x = accel.x;
		Print(U"accel_x" + Format(accel_x));
		acex = accel_x;
		if (accel_x > -10) {
			xplus++;
		}
		else if (accel_x <= -9) {
			xminus++;
		}
		if (MyKey::getRightKeyDown()) {
			direction_flag = 1;
		}
		else if (MyKey::getLeftKeyDown()) {
			direction_flag = -1;
		}
	}
	else {
		thinkdrawflag = 4;
		countdownflag = 1;
		setNextScene(PRACTICAL_SKILL);
	}

}
void Soccer::updatePractical_skill() { //けったとき
	countdownflag = 0;
	coutdown = 240;
	thinkdrawflag = 0;
	static int sugoi;
	/*
	Vec3 vec = Sensor::getAcceleration();//加速度取得
	int x, y, z, flag = 0;
	x = vec.x;
	y = vec.y;
	z = vec.z;
	//Print(U"SensorData" + Format(x));
	*/
	
	if (xplus >= xminus) {
		direction_flag = 1;
	}
	else {
		direction_flag = -1;
	}
	
	
	
	
	

	//センサ接続時コメントアウト
	/*
	direction_flag = 1;
	shootpower = 30;
	shootdirection = 1;
	*/
	
	
	
	if (end_flag == 0) {
		////値をもとに計算処理/////
		if (direction_flag == 1) {
			if (shootpower < 40) {
				shootdirection = 4;
				end_flag = 1;
			}
			else if (shootpower >= 40) {
				shootdirection = 2;
				end_flag = 1;
			}
		}
		else if (direction_flag == -1) {
			if (shootpower < 40) {
				shootdirection = 3;
				end_flag = 1;
			}
			else if (shootpower >= 40) {
				shootdirection = 1;
				end_flag = 1;
			}
		}
		else if (direction_flag == 0) {	//１秒以内にキックされなかった場合
			shootdirection = 5;
			end_flag = 1;
		}
	}
	

	//どっちが勝ったか
	flykeeper = Random(1, 4);	//GKの飛ぶ方向を決める
	if (flykeeper == shootdirection) {	//GKの飛んだ先にボールをけっていたら
		winflag = 1;				//シュートストップ
	}
	else {
		reactionspeed = Random(minaccel, maxaccel);
		if (reactionspeed > highshootpower) {
			winflag = 1;
		}
		else {
			winflag = 2;
		}
	}
	
	if (end_flag == 2) {
		if (endcount == 0) {
			if (winflag == 2) {
				AudioAsset(U"goal").setVolume(0.3);
				AudioAsset(U"goal").play();
			}
			else {
				AudioAsset(U"miss").setVolume(0.3);
				AudioAsset(U"miss").play();
			}
		}
		endcount++;
		if (endcount >= 60) {
			endcount = 0;
			end_flag = 0;
			soccerboalcount = 120;
			//highshootpower = 0;
			setNextScene(RESULT);
		}
		
	}


	

	


	//xがーのときと
	//yがーのときではんていかえるｘとｙで四つ方向きめて、あとは足した値のでかいほうで決める？？？
	//

		/*vec.x//X方向の加速度
		vec.y//Y方向の加速度
		vec.z//Z方向の加速度*/

}

void Soccer::updateResult() {  //つづけるかいなか
	if (!endMusic) {
		if (winflag == 2) {
			AudioAsset(U"clear").setVolume(0.3);
			AudioAsset(U"clear").play();
		}
		else if (winflag == 1) {
			AudioAsset(U"zannen").setVolume(0.3);
			AudioAsset(U"zannen").play();
		}
		endMusic = true;
	}
	if (MyKey::getLeftKeyDown()) {
		inputRBotton = 2;

	}
	else if (MyKey::getRightKeyDown()) {
		inputRBotton = 1;

	}
	if (MyKey::getDecisionKey()) {
		if (inputRBotton == 1) {
			setNextScene(SELECT_MODE);
		}
		else if (inputRBotton == 2) {
			outputResult();
			MySceneManager::setNextScene(SCENE::SELECT_MODE);
		}
		GeneralSoundEffects::play(SE_NAME::DECISION);
		highshootpower = 0;
	}

}

void Soccer::whichWin(int direction, int power) {  //どっちがかったか判断する関数
	/*方向の判定*/
	



	/*
	int keepnumber, kicknumber;
	keepnumber = total;
	kicknumber = total;


	Random(maxaccel, minaccel);

	if (keepnumber > kicknumber) {
		return false;
	}

	return true;
	*/
}



//描画



void Soccer::drawSelect() {
	//TextureAsset(U"soccerchoice").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	TextureAsset(U"selectpoji").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 4 - 200);
	if (selecttype == 0) {
		TextureAsset(U"soccerkicker2").drawAt(600, 700);
		TextureAsset(U"soccerkeeper1").drawAt(1400, 700);
	}
	else if (selecttype == 1) {
		TextureAsset(U"soccerkicker1").drawAt(600, 700);
		TextureAsset(U"soccerkeeper2").drawAt(1400, 700);
	}
}

void Soccer::drawBeforeThiking()
{
	if (readflag == 1) {
		TextureAsset(U"s_setu0").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	}
	else if (readflag == 2) {
		TextureAsset(U"s_setu1").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	}
	else if (readflag == 3) {
		TextureAsset(U"s_setu2").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	}
	else if (readflag == 4) {
		TextureAsset(U"s_setu3").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	}
	else {
		if (selecttype == 0) {
			TextureAsset(U"wearleg").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
			readflag = 0;
		}
		else if (selecttype == 1) {
			TextureAsset(U"wearhand").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
			readflag = 0;
		}
	}
	
	
}

void Soccer::drawThinking() {
	//TextureAsset(U"gameback").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	switch (thinkdrawflag) {
	case 0:
		TextureAsset(U"three").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() - 400);
		break;
		
	case 1:
		TextureAsset(U"two").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() - 400);
		break;

	case 2:
		TextureAsset(U"one").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() - 400);
		break;

	case 3:
		TextureAsset(U"shoot").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() - 400);
		break;
	}
}

void Soccer::drawPractical_skill() {
	TextureAsset(U"soccerback1").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	static int boal_x = Window::ClientWidth() / 2;
	static int boal_y = Window::ClientHeight() - 150;

	if (end_flag == 1) {
		soccerboalcount--;
		switch (direction_flag) {
		case -1:
			if (soccerboalcount >= 120 - 15) {
				TextureAsset(U"soccerboal1").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() - 100);
			}
			else if (soccerboalcount >= 120 - 30) {
				TextureAsset(U"soccerboal2").drawAt(Window::ClientWidth() / 2 - 10, Window::ClientHeight() / 2 - 105);
			}
			else if (soccerboalcount >= 120 - 45) {
				TextureAsset(U"soccerboal3").drawAt(Window::ClientWidth() / 2 - 50, Window::ClientHeight() / 2 - 110);
			}
			else if (soccerboalcount >= 120 - 60) {
				TextureAsset(U"soccerboal4").drawAt(Window::ClientWidth() / 2 - 90, Window::ClientHeight() / 2 - 115);
			}
			else if (soccerboalcount >= 120 - 75) {
				TextureAsset(U"soccerboal5").drawAt(Window::ClientWidth() / 2 - 120, Window::ClientHeight() / 2 - 125);
			}
			else if (soccerboalcount >= 120 - 90) {
				TextureAsset(U"soccerboal6").drawAt(Window::ClientWidth() / 2 - 160, Window::ClientHeight() / 2 - 140);
			}
			else if (soccerboalcount >= 120 - 105) {
				TextureAsset(U"soccerboal7").drawAt(Window::ClientWidth() / 2 - 200, Window::ClientHeight() / 2 - 155);
			}
			else if (soccerboalcount >= -30) {
				TextureAsset(U"soccerboal8").drawAt(Window::ClientWidth() / 2 - 300, Window::ClientHeight() / 2 - 170);
			}
			else {
				end_flag = 2;
			}
			break;

		case 1:
			if (soccerboalcount >= 120 - 15) {
				TextureAsset(U"soccerboal1").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() - 100);
			}
			else if (soccerboalcount >= 120 - 30) {
				TextureAsset(U"soccerboal2").drawAt(Window::ClientWidth() / 2 + 10, Window::ClientHeight() / 2 - 105);
			}
			else if (soccerboalcount >= 120 - 45) {
				TextureAsset(U"soccerboal3").drawAt(Window::ClientWidth() / 2 + 50, Window::ClientHeight() / 2 - 110);
			}
			else if (soccerboalcount >= 120 - 60) {
				TextureAsset(U"soccerboal4").drawAt(Window::ClientWidth() / 2 + 90, Window::ClientHeight() / 2 - 115);
			}
			else if (soccerboalcount >= 120 - 75) {
				TextureAsset(U"soccerboal5").drawAt(Window::ClientWidth() / 2 + 120, Window::ClientHeight() / 2 - 125);
			}
			else if (soccerboalcount >= 120 - 90) {
				TextureAsset(U"soccerboal6").drawAt(Window::ClientWidth() / 2 + 160, Window::ClientHeight() / 2 - 140);
			}
			else if (soccerboalcount >= 120 - 105) {
				TextureAsset(U"soccerboal7").drawAt(Window::ClientWidth() / 2 + 200, Window::ClientHeight() / 2 - 155);
			}
			else if (soccerboalcount >= -30) {
				TextureAsset(U"soccerboal8").drawAt(Window::ClientWidth() / 2 + 300, Window::ClientHeight() / 2 - 170);
			}
			else {
				end_flag = 2;
			}
			break;
		}
		
	}
	
}


void Soccer::drawResult() {
	//TextureAsset(U"soccerresult").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 4 - 200);
	if (winflag == 1) {
		if (direction_flag == 1) {
			TextureAsset(U"saveright").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		}
		else {
			TextureAsset(U"saveleft").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		}
		TextureAsset(U"gatya50").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2 + 60);

	}
	else if (winflag == 2) {
		if (direction_flag == 1) {
			TextureAsset(U"goaright").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		}
		else {
			TextureAsset(U"goalleft").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
		}
		TextureAsset(U"gatya200").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	}
	switch (inputRBotton)
	{
	case 1:
		TextureAsset(U"replay2").drawAt(1400, 950);
		TextureAsset(U"backgameselect1").drawAt(600, 950);
		break;
	case 2:
		TextureAsset(U"replay1").drawAt(1400, 950);
		TextureAsset(U"backgameselect2").drawAt(600, 950);
		break;
	}

	/*
	Print(U"flykeeper" + Format(flykeeper));
	Print(U"direction" + Format(shootdirection));
	Print(U"power" + Format(shootpower));
	Print(U"reaction" + Format(reactionspeed));
	Print(U"win" + Format(winflag));
	Print(U"highshootpower" + Format(highshootpower));
	Print(U"accel_z" + Format(acex));
	*/
	

}

void Soccer::frameCount() {
	framecount++;
	if (framecount > 60 * 3000) {//上限値チェック
		framecount = 0;
	}

}

void Soccer::restartGame() {
	static int gameStart;

	//リスタートの関数いるね
}

void Soccer::soccerGachaPoint() {
	gachasoccer += gachapo;

}

void Soccer::soccerHighScore(int sugoi) {
	//ポイントのあて振りの計算
	maxpoint = sugoi;

	maxpoint = (maxpoint / highScorepoint) * 100;

	//割合＊１００ マックスポイントの割合最大速度を100パーセントにしてそっからの割合で点数
}

void Soccer::itemCheck() {
	//もしガチャで特定のアイテム持ってたらエフェクト入れるやつする
}

void Soccer::stopGame() {	//ゲームを一時中断する
	TextureAsset(U"inter").drawAt(Window::ClientWidth() / 2, Window::ClientHeight() / 2);
	isStop = true;

}

//フレーム管理～～～～


