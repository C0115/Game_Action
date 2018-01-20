#include <DxLib.h>
#include "localFunction.h"
#include "mainLoop.h"


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�L��

	SetGraphMode(1280, 720, 32); //��ʂ̃T�C�Y�Ȃǂ�ݒ肷��

	SetDrawScreen(DX_SCREEN_BACK); //�����(�v���C���[�Ɍ����Ȃ�)��ǉ�����

	if (DxLib_Init() == -1) return -1; // �c�w���C�u��������������(�G���[���N�����璼���ɏI��)

	int Key[256];

	/* ------------------------------
	Esc�L�[��������Ă�����Q�[���I��
	���ɂ��Q�[���������I�����������R�}���h�Ƃ�����ΒǋL���Ă�������
	------------------------------ */
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		if(Loop() == 0) break; // �����Q�[�����I�������烋�[�v�𔲂���

	}

	DxLib_End(); // �c�w���C�u�����g�p�̏I������

	return 0; // �\�t�g�̏I�� 
}