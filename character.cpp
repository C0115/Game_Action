/*---------------------------------------------
Characterクラス:全てのキャラの基となるクラス
-------------------------------------------------*/
class Character {
public:
	int HP; //キャラの体力
	int Gh; //キャラのグラフィックハンドル
	int characterHeight; //キャラの縦幅
	int characterWidth; //キャラの横幅
	int X, Y; //キャラの座標(真ん中)
	int X1, Y1, X2, Y2, X3, Y3, X4, Y4; //順に左上右上右下左下
	int G = 10; //重力加速度
	bool JUMP; //ジャンプフラグ（ジャンプしたらtrue）

	Character(int hp, int x, int y, int gh); //キャラのコンストラクタ
	void setGh(int graphicHandle); //グラフィックハンドルの設定
	void move(int distance); //キャラの移動
	void gravity(int GRAVITY); //下方向への重力
	void jump(); //ジャンプ関数
	void setPoint(); //４点の座標の設定
};

/*--------------------------------------
Characterのコンストラクタ
HPと中心座標を設定する
そしてグラフィックハンドルを設定し
キャラの幅をそれぞれ
characterHeightとcharacterWidthに代入
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
キャラクターのグラフィックハンドルを変更する
-----------------------------------------------*/
void Character::setGh(int graphicHandle) {
	Gh = graphicHandle;
}

/*--------------------------------------------
キーが押されると右か左に移動する
また、移動先にブロックがある場合は何もしない
----------------------------------------------*/
void Character::move(int distance) {
	X += distance;
	setPoint();

	/*-----------------------------------------------
	ブロックにプレイヤーが入っていると移動距離分戻る
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
重力関数
常に下向きに移動し続ける
ジャンプ時には上に移動し、少しずつ下に戻る
下にブロックがある場合は移動しない
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
	キャラがブロック内にいると重力分上に戻る
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
ジャンプ時（スペースキー）
重力の向きを逆にしジャンプする
-----------------------------------*/
void Character::jump() {
	if (!JUMP) {
		G = -20;
		JUMP = true;
	}
}

/*----------------------------------
キャラクターの４隅の座標を更新する
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



