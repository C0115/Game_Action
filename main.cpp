#include <DxLib.h>
#include "localFunction.h"
#include "mainLoop.h"


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); // ウィンドウモード有効

	SetGraphMode(1280, 720, 32); //画面のサイズなどを設定する

	SetDrawScreen(DX_SCREEN_BACK); //裏画面(プレイヤーに見せない)を追加する

	if (DxLib_Init() == -1) return -1; // ＤＸライブラリ初期化処理(エラーが起きたら直ちに終了)

	int Key[256];

	/* ------------------------------
	Escキーが押されていたらゲーム終了
	他にもゲームを強制終了させたいコマンドとかあれば追記してください
	------------------------------ */
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		if(Loop() == 0) break; // もしゲームが終了したらループを抜ける

	}

	DxLib_End(); // ＤＸライブラリ使用の終了処理

	return 0; // ソフトの終了 
}