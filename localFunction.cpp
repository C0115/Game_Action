#include <DxLib.h>
#include "localFunction.h"


// �L�[�̓��͏�Ԃ��X�V����֐��B���͂��ꂽ�u�Ԃ��擾�������ꍇ�� Key[�L�[�R�[�h] == 1 �Ƃ���B
int gpUpdateKey(int Key[256])
{
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			Key[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			Key[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}
