#pragma once

class CMyGame : public CGame
{
	//GAME VARIABLES
	Uint32 flickerTime;
	Uint32 flickerTime2;
	int score;
	int level;
	int scene;
	int lives; 
	int numVult;
	int numEnemy;
	int enemyPos;
	int superX;
	int alea;
	bool facingLeft;
	bool gamewon;
	bool respawn;
	bool respawnB1;
	bool respawnB2;
	bool respawnB3;
	bool target;

	//GROUNDFLOOR VARIABLES
	int Rect_x = 0;
	int Rect_y = 0;
	int Rect_w = 1380;
	int Rect_h = 175;

	// SINGLE SPRITES 
	CSprite player;
	CSprite startScreen;
	CSprite background;
	CSprite background_cover;
	CSprite gameOver;
	CSprite vulture;
	CSprite skull;
	CSprite bullet;


	//SPRITE LISTS
	CSpriteList shotList;
	CSpriteList barrelList;
	CSpriteList explosionList;
	CSpriteList vultureList;
	CSpriteList skullList;
	CSpriteList enemyList;
	CSpriteList enemyList2;
	CSpriteList enemyList3;
	CSpriteList enemyList4;
	CSpriteList enemyShotList;
	CSpriteList enemyShotList2;
	CSpriteList enemyShotList3;
	CSpriteList enemyShotList4;
	CSpriteList bossShotList;
	CSpriteList dieList;
	CSpriteList balconyList;
	CSpriteList torchList;
	CSpriteList mineCartList;
	CSpriteList bossList;
	CSpriteList bossList2;
	CSpriteList finalBossList;
	CSpriteList superBarrelList;

	//SOUNDS

	CSoundPlayer sShot;
	CSoundPlayer enemyShot;
	CSoundPlayer sBullet;
	CSoundPlayer metalJ;
	CSoundPlayer brokenBalcony;
	CSoundPlayer playerDies;
	CSoundPlayer enemyDies;
	CSoundPlayer explosionFX;
	CSoundPlayer backgroundTheme;
	CSoundPlayer bossTheme;
	CSoundPlayer finalBossTheme;
	CSoundPlayer levelSelect;
	CSoundPlayer sGameOver;
	CSoundPlayer sGameWon;
	

	//MY NEW MEMBER FUNCTIONS
	void setUpLevel1();     //LEVEL1
	void setUpLevel2();     //LEVEL2
	void setUpLevel3();     //LEVEL3
	void PlayerControl();
	void BarrelControl();
	void BossBarrelControl();
	void Enemy1Control();
	void SkullMovement();
	void BalconyControl();
	void Enemy2Control();
	void Enemy3Control();
	void Boss1Control();
	void Boss2Control();
	void Boss3Control();


public:
	CMyGame(void);
	~CMyGame(void);

	// Per-Frame Callback Funtions (must be implemented!)
	virtual void OnUpdate();
	virtual void OnDraw(CGraphics* g);

	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnStartGame();
	virtual void OnStartLevel(Sint16 nLevel);
	virtual void OnGameOver();
	virtual void OnTerminate();

	// Keyboard Event Handlers
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse Events Handlers
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
};
