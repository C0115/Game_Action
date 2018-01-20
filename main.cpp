#include <DxLib.h>
#include "map.h"
#include "localFunction.h"
#include "character.cpp"


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	SetGraphMode(1280, 720, 32); //画面のサイズなどを設定する

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	int gh[12];

	LoadDivGraph(TEXT("images/charall.png"), 12, 3, 4, 49, 66, gh); //ghに主人公の絵を分割して格納

	Character *player = new Character(200, 150, 0, gh[7]);

	SetDrawScreen(DX_SCREEN_BACK); //裏画面(プレイヤーに見せない)を追加する

	int Key[256];
	int Sx, Sy, Cb;//スクリーンサイズ


				   /*--------------------------------------------------
				   Windowsでエラーメッセージがでなかったら
				   裏画面をプレイヤーに見せた後にエラーがでなかったら
				   キー入力の際にエラーが出なかったら
				   裏画面の消去でエラーが出なかったら
				   --------------------------------------------------*/
	while (ProcessMessage() != -1 && 
		ScreenFlip() != -1 && 
		gpUpdateKey(Key) == 0 &&
		ClearDrawScreen() != -1) {

		for (int i = 0; i < Map_Y; i++) {
			for (int j = 0; j < Map_X; j++) {
				if (map[i][j] == ungoable) {
					DrawBox(j * Width - player->X1 + Sx / 2, i*Height, (j + 1) * Width - player->X1 + Sx / 2 - 1, (i + 1)*Height - 1, GetColor(0, 0, 255), TRUE);
				}
			}
		}

		GetScreenState(&Sx, &Sy, &Cb); //画面の大きさなどをそれぞれの変数に格納

		if (Key[KEY_INPUT_ESCAPE] == 1) { //Escキーを押すと
			break;
		}
		if (Key[KEY_INPUT_RIGHT] >= 1) {
			player->move(10);
		}
		if (Key[KEY_INPUT_LEFT] >= 1) {
			player->move(-10);
		}
		if (Key[KEY_INPUT_SPACE] == 1) {
			player->jump();
		}

		player->gravity(player->G);

		//DrawGraph(player->X1, player->Y1, player->Gh, TRUE);
		DrawGraph(Sx / 2, player->Y1, player->Gh, TRUE);


		if (player->Y >= Sy) {
			break;
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}