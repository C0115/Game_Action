#include <DxLib.h>
#include "map.h"
#include "localFunction.h"
#include "character.cpp"


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	SetGraphMode(1280, 720, 32); //��ʂ̃T�C�Y�Ȃǂ�ݒ肷��

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	int gh[12];

	LoadDivGraph(TEXT("images/charall.png"), 12, 3, 4, 49, 66, gh); //gh�Ɏ�l���̊G�𕪊����Ċi�[

	Character *player = new Character(200, 150, 0, gh[7]);

	SetDrawScreen(DX_SCREEN_BACK); //�����(�v���C���[�Ɍ����Ȃ�)��ǉ�����

	int Key[256];
	int Sx, Sy, Cb;//�X�N���[���T�C�Y


				   /*--------------------------------------------------
				   Windows�ŃG���[���b�Z�[�W���łȂ�������
				   ����ʂ��v���C���[�Ɍ�������ɃG���[���łȂ�������
				   �L�[���͂̍ۂɃG���[���o�Ȃ�������
				   ����ʂ̏����ŃG���[���o�Ȃ�������
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

		GetScreenState(&Sx, &Sy, &Cb); //��ʂ̑傫���Ȃǂ����ꂼ��̕ϐ��Ɋi�[

		if (Key[KEY_INPUT_ESCAPE] == 1) { //Esc�L�[��������
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

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}