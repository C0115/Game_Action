/*---------------------------------------------
Character�N���X:�S�ẴL�����̊�ƂȂ�N���X
-------------------------------------------------*/
class Character {
public:
	int HP; //�L�����̗̑�
	int Gh; //�L�����̃O���t�B�b�N�n���h��
	int characterHeight; //�L�����̏c��
	int characterWidth; //�L�����̉���
	int X, Y; //�L�����̍��W(�^��)
	int X1, Y1, X2, Y2, X3, Y3, X4, Y4; //���ɍ���E��E������
	int G = 10; //�d�͉����x
	bool JUMP; //�W�����v�t���O�i�W�����v������true�j

	Character(int hp, int x, int y, int gh); //�L�����̃R���X�g���N�^
	void setGh(int graphicHandle); //�O���t�B�b�N�n���h���̐ݒ�
	void move(int distance); //�L�����̈ړ�
	void gravity(int GRAVITY); //�������ւ̏d��
	void jump(); //�W�����v�֐�
	void setPoint(); //�S�_�̍��W�̐ݒ�
};

/*--------------------------------------
Character�̃R���X�g���N�^
HP�ƒ��S���W��ݒ肷��
�����ăO���t�B�b�N�n���h����ݒ肵
�L�����̕������ꂼ��
characterHeight��characterWidth�ɑ��
-------------------------------------------*/
Character::Character(int hp, int x, int y, int gh) {
	HP = hp;
	JUMP = false;
	Gh = gh;
	GetGraphSize(Gh, &characterWidth, &characterHeight);
	X = x;
	Y = y;
	setPoint();
}

/*--------------------------------------------
�L�����N�^�[�̃O���t�B�b�N�n���h����ύX����
-----------------------------------------------*/
void Character::setGh(int graphicHandle) {
	Gh = graphicHandle;
}

/*--------------------------------------------
�L�[���������ƉE�����Ɉړ�����
�܂��A�ړ���Ƀu���b�N������ꍇ�͉������Ȃ�
----------------------------------------------*/
void Character::move(int distance) {
	X += distance;
	setPoint();

	/*-----------------------------------------------
	�u���b�N�Ƀv���C���[�������Ă���ƈړ��������߂�
	------------------------------------------------*/
	if (map[Y4 / Height][X4 / Width] >= ungoable) {
		X -= distance;
		setPoint();
	}
	else if (map[Y3 / Height][X3 / Width] >= ungoable) {
		X -= distance;
		setPoint();
	}
	else if (map[Y2 / Height][X2 / Width] >= ungoable) {
		X -= distance;
		setPoint();
	}
	else if (map[Y1 / Height][X1 / Width] >= ungoable) {
		X -= distance;
		setPoint();
	}
}


/*-------------------------------------------
�d�͊֐�
��ɉ������Ɉړ���������
�W�����v���ɂ͏�Ɉړ����A���������ɖ߂�
���Ƀu���b�N������ꍇ�͈ړ����Ȃ�
----------------------------------------------*/
void Character::gravity(int GRAVITY) {
	if (JUMP) {
		G += 1;
	}

	if (G >= 20) {
		G = 20;
	}

	Y += GRAVITY;
	setPoint();

	/*--------------------------------------
	�L�������u���b�N���ɂ���Əd�͕���ɖ߂�
	-----------------------------------------*/
	if (map[Y4/ Height][X4/Width] >= ungoable) {
		Y -= GRAVITY;
		setPoint();
		G = 20;
		JUMP = false;
	}
	else if (map[Y3 / Height][X3 / Width] >= ungoable) {
		Y -= GRAVITY;
		setPoint();
		G = 20;
		JUMP = false;
	}

	if (JUMP) {
		if (map[Y1 / Height][X1 / Width] >= ungoable) {
			Y -= GRAVITY;
			G = 20;
			setPoint();
		}
		else if (map[Y2 / Height][X2 / Width] >= ungoable) {
			Y -= GRAVITY;
			G = 20;
			setPoint();
		}
	}

}

/*---------------------------------
�W�����v���i�X�y�[�X�L�[�j
�d�͂̌������t�ɂ��W�����v����
-----------------------------------*/
void Character::jump() {
	if (!JUMP) {
		G = -20;
		JUMP = true;
	}
}

/*----------------------------------
�L�����N�^�[�̂S���̍��W���X�V����
-------------------------------------*/
void Character::setPoint() {
	X1 = X - characterWidth / 2;
	Y1 = Y - characterHeight / 2;
	X2 = X + characterWidth / 2;
	Y2 = Y - characterHeight / 2;
	X3 = X + characterWidth / 2;
	Y3 = Y + characterHeight / 2;
	X4 = X - characterWidth / 2;
	Y4 = Y + characterHeight / 2;
}



