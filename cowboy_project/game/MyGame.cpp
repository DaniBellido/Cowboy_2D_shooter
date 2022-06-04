#include "stdafx.h"
#include "MyGame.h"

CMyGame::CMyGame(void) // to initialise more sprites here use a comma-separated list
{
	// TODO: add initialisation here
	level = 0;
	scene = 0;
	score = 0;
	lives = 6;
	facingLeft = false;
	gamewon = false;
	respawn = true;
	respawnB1 = true;
	respawnB2 = true;
	respawnB3 = true;
	target;
	alea;
	superX;
	flickerTime = 0;
	flickerTime2 = 0;

}

CMyGame::~CMyGame(void)
{
	// TODO: add destruction code here
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	if (IsMenuMode() || IsGameOver()) return; 

	Uint32 t = GetTime();

	//Updating
	player.Update(t);
	bullet.Update(t);
	vulture.Update(t);
	skull.Update(t);
	gameOver.Update(t);
	if (level == 1) setUpLevel1();
	if (level == 2 )setUpLevel2();
	if (level == 3)setUpLevel3();




	//UPDATING LISTS
	for (CSprite* shot : shotList) shot->Update(t);
	for (CSprite* RollingBarrel : barrelList) RollingBarrel->Update(t);
	for (CSprite* superBarrel : superBarrelList) superBarrel->Update(t);
	for (CSprite* explosion : explosionList) explosion->Update(t);
	for (CSprite* vulture : vultureList) vulture->Update(t);
	for (CSprite* skull : skullList) skull->Update(t);
	for (CSprite* enemy : enemyList) enemy->Update(t);
	for (CSprite* enemyR : enemyList2) enemyR->Update(t);
	for (CSprite* enemyR : enemyList3) enemyR->Update(t);
	for (CSprite* enemyR : enemyList4) enemyR->Update(t);
	for (CSprite* enemy : dieList) enemy->Update(t);
	for (CSprite* shot : enemyShotList) shot->Update(t);
	for (CSprite* shot2 : enemyShotList2) shot2->Update(t);
	for (CSprite* shot2 : enemyShotList3) shot2->Update(t);
	for (CSprite* shot2 : enemyShotList4) shot2->Update(t);
	for (CSprite* balcony : balconyList) balcony->Update(t);
	for (CSprite* boss1 : bossList) boss1->Update(t);
	for (CSprite* boss2 : bossList2) boss2->Update(t);
	for (CSprite* bossShot : bossShotList) bossShot->Update(t);
	for (CSprite* torch : torchList) torch->Update(t);
	for (CSprite* cart : mineCartList) cart->Update(t);
	for (CSprite* boss : finalBossList) boss->Update(t);

	//-----------------------GAME RULES-------------------------------

	SkullMovement();
	BalconyControl();
	BarrelControl();
	BossBarrelControl();
	Enemy1Control();
	Enemy2Control();
	Enemy3Control();

	if (level == 1)Boss1Control();
	if (level == 2)Boss2Control(); 
	if (level == 3) Boss3Control();

	


	player.SetYVelocity(-350); //Velocity Y after Player Jump

	if (player.GetX() >= Rect_x && player.GetX() <= Rect_w) //Groundfloor collision check
	{
		if (player.GetY() >= Rect_y && player.GetY() <= Rect_h)
		{
			
			player.SetYVelocity(0);
		}
	}

	if (player.GetX() <= Rect_x) //limitation of movement. Player can't go back to the previous screen
	{ 
		player.SetPosition(Rect_x, Rect_h); 
	}

	if ((scene == 3 || scene == 6 || scene == 9) && player.GetX() >= 1277) //Limits of the rightside of the screen
	{
		player.SetX(1277); // if scene = 3 || 6 || 9, Player X position CAN'T be grater than 1277
	}

	
	for (CSprite* shot : shotList)// delete a shot if outside of the screen area
	{
		if (shot->GetY() < 0 || shot->GetY() > 720 || shot->GetX() < 0 || shot->GetX() > 1280) shot->Delete();
	}
	shotList.delete_if(deleted);// remove deleted sprites from list   

	for (CSprite* cart : mineCartList) //AT LEVEL 2, SCENE 6, MINECART IS SOLID AND PLAYER&BULLETS COLLIDE WITH IT. 
	{
		for (CSprite* shot : shotList)
		{
			if (shot->HitTest(cart))
			{
				shot->Delete();
				//ADDSOUNDFX
			}
		}

		if (cart->HitTest(&player) && player.GetX() <= cart->GetX()) 
		{
			player.SetX(755);
		}
	}
	shotList.delete_if(deleted);

	//LOADING SPRITE FOR LIVES COUNTER

	bullet.LoadImage("bullet.bmp", CColor::Red());
	bullet.SetImage("bullet.bmp");

	if (lives <= 0) //GAME OVER CONDITION
	{
		gameOver.LoadImage("gameOver.bmp", CColor::White());
		gameOver.SetImage("gameOver.bmp");
		gameOver.SetPosition(640, 360);
		GameOver();
	}

	if (gamewon == true) 
	{
		gameOver.LoadImage("gameWon.bmp", CColor::White());
		gameOver.SetImage("gameWon.bmp");
		gameOver.SetPosition(640, 360);
		GameOver();
	}


}
//PLAYER AND ENEMIES CONTROL
void CMyGame::PlayerControl() 
{

	//PLAYER SPRITES
	player.LoadImage("cowboy.bmp", "stand", 4, 1, 0, 0, CColor::Red());
	player.AddImage("cowboy.bmp", "walk_right", 4, 1, 0, 0, 3, 0, CColor::Red());
	player.AddImage("cowboy_left.bmp", "walk_left", 4, 1, 0, 0, 3, 0, CColor::Red());
	player.SetImage("stand");
	player.AddImage("cowboy_sit.bmp", "down", 1, 1, 0, 0, 0, 0, CColor::Red());
	player.AddImage("cowboy_sit_left.bmp", "downL", 1, 1, 0, 0, 0, 0, CColor::Red());
	player.AddImage("cowboy_up.bmp", "up", 1, 1, 0, 0, 0, 0, CColor::Red());
	player.AddImage("cowboy_jump.bmp", "jump", 1, 1, 0, 0, 0, 0, CColor::Red());
	player.AddImage("cowboy_jump_left.bmp", "jumpL", 1, 1, 0, 0, 0, 0, CColor::Red());
	player.AddImage("stand_left.bmp", "standL", 1, 1, 0, 0, 0, 0, CColor::Red());
	player.AddImage("cowboy_diagonal_right.bmp", "diagonalR", 4, 1, 0, 0, 3, 0, CColor::Red());
	player.AddImage("cowboy_diagonal_left.bmp", "diagonalL", 4, 1, 0, 0, 3, 0, CColor::Red());


}

void CMyGame::Enemy1Control() 
{
	if (scene == 0)
	{
		//vulture single sprite for the first scene of the game
		vulture.LoadImage("vulture.bmp", "nomovement", 3, 1, 0, 0, CColor::Red());
		vulture.SetImage("nomovement");
		vulture.SetPosition(1000, 350);
		

		if (scene == 0 && player.GetX() >= 150) //condition that triggers vulture movement
		{
			//vulture moves towards player
			vulture.AddImage("vulture.bmp", "movement", 3, 1, 1, 0, 2, 0, CColor::Red());
			vulture.SetAnimation("movement");
			vulture.SetVelocity(-150, 60);
			scene++;
		}
	}

	if (scene == 0 || scene == 1)
	{
		for (CSprite* shot : shotList)
		{
			if (shot->HitTest(&vulture))
			{
				shot->Delete();
				CSprite* explosion = new CSprite(vulture.GetX(), vulture.GetY(), 0, 0, GetTime());
				explosion->AddImage("explosion.bmp", "explode", 5, 5, 0, 0, 4, 4, CColor::Black()); 
				explosion->SetAnimation("explode", 25);
				explosionList.push_back(explosion);
				explosionFX.Play("tntexplosion.wav");
				explosionFX.Volume(1.0);
				explosion->Die(1000);
				vulture.SetPosition(0, 0);
				skull.SetPosition(-100,0);
				score++;

			}
		}
	}shotList.delete_if(deleted);

	if (scene == 2 || scene == 3 || scene == 4 || scene == 7 || scene == 8 || scene == 9)
	{
		if (scene == 2 || scene == 3 || scene == 4 || scene == 9)
		{
			numVult = 500;
		}
		else 
		{
			numVult = 100;
		}

		if (rand() % numVult == 0)
		{
			CSprite* vulture = new CSprite(1285, 650, "vulture.bmp", CColor::Red(), GetTime()); // Enemy vulture coming from the right side of the screen
			vulture->AddImage("vulture.bmp", "flying", 3, 1, 1, 0, 2, 0, CColor::Red());
			vulture->SetAnimation("flying");
			vulture->SetVelocity(-100, 0);
			vultureList.push_back(vulture);
		}

		if (rand() % numVult == 0)
		{
			CSprite* vulture = new CSprite(0, 650, "vultureL.bmp", CColor::Red(), GetTime()); // Enemy vulture coming from the left side of the screen
			vulture->AddImage("vultureL.bmp", "flying", 3, 1, 1, 0, 2, 0, CColor::Red());
			vulture->SetAnimation("flying");
			vulture->SetVelocity(100, 0);
			vultureList.push_back(vulture);
		}

		for (CSprite* vulture : vultureList) //Checking collision between player shoots and vulture
		{
			for (CSprite* shot : shotList)
			{
				if (shot->HitTest(vulture))
				{
					shot->Delete();
					vulture->Delete();
					score = score + 25;

					//explosion animation
					CSprite* explosion = new CSprite(vulture->GetX(), vulture->GetY(), 0, 0, GetTime());
					explosion->AddImage("explosion.bmp", "explode", 5, 5, 0, 0, 4, 4, CColor::Black()); 
					explosion->SetAnimation("explode", 25);
					explosionList.push_back(explosion);
					explosionFX.Play("tntexplosion.wav");
					explosionFX.Volume(1.0);
					explosion->Die(1000);
				}
			}
			if (vulture->GetX() < -5 || vulture->GetX() > 1300) vulture->Delete();
		}
		shotList.delete_if(deleted);
		vultureList.delete_if(deleted);
	}  


}
void CMyGame::SkullMovement() //THIS FUNCTION IS RELATED TO THE Enemy1Control()
{
	//SKULL SINGLE SPRITE FOR SCENE 1
	skull.LoadImage("skull.bmp", CColor::Red());
	skull.SetImage("skull.bmp"); 

	if (fabs(player.GetX() - vulture.GetX()) < 5) //vulture drops a skull on the same X position of the player
	{
		skull.SetPosition(vulture.GetPosition());
		skull.SetYVelocity(-300);

		//TODO: Add sound FX
	}

	if (skull.HitTest(&player) && scene >= 1 && GetTime() > flickerTime)
	{
		skull.SetPosition(-10, -10);
		playerDies.Play("playerdies.wav");
		player.SetPosition(100, 375);
		lives--;
		flickerTime = GetTime() + 3000;
	}

	if (skull.GetY() < 100) skull.SetPosition(-100,0);

	//SKULL LIST
	for (CSprite* pvulture : vultureList)
	{
		if (fabs(player.GetX() - pvulture->GetX()) < 1)
		{
			CSprite* pskull = new CSprite(pvulture->GetX(), pvulture->GetY(), "skull.bmp", CColor::Red(), GetTime());
			pskull->SetYVelocity(-300);

			skullList.push_back(pskull);
		}
	}

	for (CSprite* pskull : skullList)
	{
		if (pskull->GetY() <= 100) pskull->Delete(); //try to add sound and "explosion FX"

		if (player.HitTest(pskull) && GetTime() > flickerTime)  
		{
			pskull->Delete();
			playerDies.Play("playerdies.wav"); 
			player.SetPosition(100, 375);
			lives--;
			flickerTime = GetTime() + 3000;
			
		}

	}
	skullList.delete_if(deleted);



}
void CMyGame::Enemy2Control()
{
	if (scene == 2 || scene == 3 || scene == 5 || scene == 6 || scene == 7 || scene == 8)
	{
		if (scene == 2 || scene == 3 || scene == 5 || scene == 6) //Different X position depending of the scene
		{
			numEnemy = 300;
		}
		else 
		{
			numEnemy = 100;
		}
		if (scene != 6) 
		{
			if (rand() % numEnemy == 0)
			{
				CSprite* enemy = new CSprite(1285, 175, "enemy_1.bmp", CColor::Red(), GetTime()); // Enemy 1 coming from the right side of the screen but not in scene 6
				enemy->AddImage("enemy_1.bmp", "enemyShotsL", 5, 2, 4, 1, 4, 1, CColor::Red());
				enemy->AddImage("enemy_1.bmp", "enemyWalkL", 5, 2, 0, 1, 3, 1, CColor::Red());
				enemy->SetHealth(1);
				enemy->SetAnimation("enemyWalkL");
				enemy->SetVelocity(-120, 0);
				enemyList.push_back(enemy);
			}
			for (CSprite* enemy : enemyList) //generating shot animation at random frame
			{
				if (rand() % 100 == 0)
				{
					enemy->SetVelocity(0, 0);
					enemy->SetAnimation("enemyShotsL");
					CSprite* enemyshot = new CSprite(enemy->GetX() - 50, enemy->GetY() + 35, "shot2.bmp", CColor::White(), GetTime());
					enemyshot->SetDirection(-88);
					enemyshot->SetSpeed(250);
					enemyShot.Play("enemyshot.wav");
					enemyShot.Volume(1.0);
					enemyShotList.push_back(enemyshot);
				}

				for (CSprite* shot : shotList) //player shoots collision check
				{
					if (shot->HitTest(enemy))
					{
						shot->Delete();
						enemy->Delete();
						score = score + 100;

						//die animation
						CSprite* enemyDie = new CSprite(enemy->GetX(), enemy->GetY(), 0, 0, GetTime());
						enemyDie->AddImage("enemy_1_die.bmp", "enemyDiesL", 4, 1, 0, 0, 1, 0, CColor::Red());
						enemyDie->SetAnimation("enemyDiesL");
						dieList.push_back(enemyDie);
						enemyDies.Play("enemydies.wav");
						enemyDies.Volume(1.0);
						enemyDie->Die(500);
					}

				}
			}
			enemyList.delete_if(deleted);
			shotList.delete_if(deleted);
			dieList.delete_if(deleted);

			for (CSprite* enemyShot : enemyShotList) //enemy shots check collision
			{
				if (enemyShot->HitTest(&player) && GetTime() > flickerTime)  
				{
					enemyShot->Delete();
					playerDies.Play("playerdies.wav");
					lives--;
					player.SetPosition(100, 375);
					flickerTime = GetTime() + 3000;
				}
				if (enemyShot->GetX() < 0) enemyShot->Delete();
			}
			enemyShotList.delete_if(deleted);

		}

		if (rand() % numEnemy == 0)
		{
			CSprite* enemyR = new CSprite(0, 175, "enemy_1.bmp", CColor::Red(), GetTime()); // Enemy 1 coming from the LEFT side of the screen
			enemyR->AddImage("enemy_1.bmp", "enemyShotsR", 5, 2, 4, 0, 4, 0, CColor::Red());
			enemyR->AddImage("enemy_1.bmp", "enemyWalkR", 5, 2, 0, 0, 3, 0, CColor::Red());
			enemyR->SetHealth(2);
			enemyR->SetAnimation("enemyWalkR");
			enemyR->SetVelocity(120, 0);
			enemyList2.push_back(enemyR);
		}

		for (CSprite* enemyR : enemyList2)
		{
			if (rand() % 100 == 0)
			{
				enemyR->SetVelocity(0, 0);
				enemyR->SetAnimation("enemyShotsR");
				CSprite* enemyshot2 = new CSprite(enemyR->GetX() + 50, enemyR->GetY() + 35, "shot2.bmp", CColor::White(), GetTime());
				enemyshot2->SetDirection(88);
				enemyshot2->SetSpeed(250);
				enemyShot.Play("enemyshot.wav");
				enemyShot.Volume(1.0);
				enemyShotList2.push_back(enemyshot2);
			}
			
			for (CSprite* shot : shotList)
			{
				if (shot->HitTest(enemyR))
				{
					shot->Delete();
					enemyR->Delete();
					score = score + 100;

					//die animation
					CSprite* enemyDie = new CSprite(enemyR->GetX(), enemyR->GetY(), 0, 0, GetTime());
					enemyDie->AddImage("enemy_1_die.bmp", "enemyDiesR", 4, 1, 2, 0, 3, 0, CColor::Red());
					enemyDie->SetAnimation("enemyDiesR");
					dieList.push_back(enemyDie);
					enemyDies.Play("enemydies.wav");
					enemyDies.Volume(1.0);
					enemyDie->Die(500);
				}

			}
		}
		enemyList2.delete_if(deleted);
		shotList.delete_if(deleted);
		dieList.delete_if(deleted);

		for (CSprite* enemyShot2 : enemyShotList2)
		{
			if (enemyShot2->HitTest(&player) && GetTime() > flickerTime)  
			{
				enemyShot2->Delete();
				playerDies.Play("playerdies.wav");
				lives--;
				player.SetPosition(100, 375);
				flickerTime = GetTime() + 3000;
			}
			if (enemyShot2->GetX() > 1280) enemyShot2->Delete(); 
		}
		enemyShotList2.delete_if(deleted);
	
	}


}

void CMyGame::Enemy3Control()
{
	if (scene == 5 || scene == 8 || scene == 9) 
	{
		if (scene == 8 || scene == 9) 
		{
			enemyPos = 491;
		}
		else 
		{
			enemyPos = 415;
		}
		if (rand() % 350 == 0)
		{ 
			CSprite* enemy = new CSprite(1285, enemyPos, "enemy_2.bmp", CColor::Red(), GetTime()); // Enemy coming from the right side of the screen
			enemy->AddImage("enemy_2.bmp", "enemyShotsL", 5, 2, 4, 1, 4, 1, CColor::Red());
			enemy->AddImage("enemy_2.bmp", "enemyWalkL", 5, 2, 0, 1, 3, 1, CColor::Red());
			enemy->SetHealth(1);
			enemy->SetAnimation("enemyWalkL");
			enemy->SetVelocity(-120, 0);
			enemyList3.push_back(enemy);
		}
		for (CSprite* enemy : enemyList3)
		{
			if (rand() % 200 == 0)
			{
				enemy->SetVelocity(0, 0);
				enemy->SetAnimation("enemyShotsL");
				CSprite* enemyshot = new CSprite(enemy->GetX() - 50, enemy->GetY() + 35, "shot2.bmp", CColor::White(), GetTime());
				enemyshot->SetDirection(225);
				enemyshot->SetSpeed(275);
				enemyShot.Play("enemyshot.wav");
				enemyShot.Volume(1.0);
				enemyShotList3.push_back(enemyshot);
			}

			for (CSprite* shot : shotList)
			{
				if (shot->HitTest(enemy))
				{
					shot->Delete();
					enemy->Delete();
					score = score + 100;

					//die animation
					CSprite* enemyDie = new CSprite(enemy->GetX(), enemy->GetY(), 0, 0, GetTime());
					enemyDie->AddImage("enemy_2_die.bmp", "enemyDiesL", 4, 1, 0, 0, 1, 0, CColor::Red());
					enemyDie->SetAnimation("enemyDiesL");
					dieList.push_back(enemyDie);
					enemyDies.Play("enemydies.wav");
					enemyDies.Volume(1.0);
					enemyDie->Die(500);
				}

			}
		}
		enemyList3.delete_if(deleted);
		shotList.delete_if(deleted);
		dieList.delete_if(deleted);

		for (CSprite* enemyShot : enemyShotList3) 
		{
			if (enemyShot->HitTest(&player) && GetTime() > flickerTime)  
			{
				enemyShot->Delete();
				playerDies.Play("playerdies.wav");
				lives--;
				player.SetPosition(100, 375);
				flickerTime = GetTime() + 3000;
			}
			if (enemyShot->GetY() < 0) enemyShot->Delete();
		}
		enemyShotList3.delete_if(deleted);

	}
	if (scene == 5 || scene == 6 || scene == 8 || scene == 9)
	{

		if (rand() % 350 == 0)
		{
			CSprite* enemyR = new CSprite(0, enemyPos, "enemy_2.bmp", CColor::Red(), GetTime()); // Enemy coming from the LEFT side of the screen
			enemyR->AddImage("enemy_2.bmp", "enemyShotsR", 5, 2, 4, 0, 4, 0, CColor::Red());
			enemyR->AddImage("enemy_2.bmp", "enemyWalkR", 5, 2, 0, 0, 3, 0, CColor::Red());
			enemyR->SetHealth(2);
			enemyR->SetAnimation("enemyWalkR");
			enemyR->SetVelocity(120, 0);
			enemyList4.push_back(enemyR);
		}

		for (CSprite* enemyR : enemyList4)
		{
			if (rand() % 200 == 0)
			{
				enemyR->SetVelocity(0, 0);
				enemyR->SetAnimation("enemyShotsR");
				CSprite* enemyshot2 = new CSprite(enemyR->GetX() + 50, enemyR->GetY() + 35, "shot2.bmp", CColor::White(), GetTime());
				enemyshot2->SetDirection(135);
				enemyshot2->SetSpeed(275);
				enemyShot.Play("enemyshot.wav");
				enemyShot.Volume(1.0);
				enemyShotList4.push_back(enemyshot2);
			}

			for (CSprite* shot : shotList)
			{
				if (shot->HitTest(enemyR))
				{
					shot->Delete();
					enemyR->Delete();
					score = score + 100;

					//die animation
					CSprite* enemyDie = new CSprite(enemyR->GetX(), enemyR->GetY(), 0, 0, GetTime());
					enemyDie->AddImage("enemy_2_die.bmp", "enemyDiesR", 4, 1, 2, 0, 3, 0, CColor::Red());
					enemyDie->SetAnimation("enemyDiesR");
					dieList.push_back(enemyDie);
					enemyDies.Play("enemydies.wav");
					enemyDies.Volume(1.0);
					enemyDie->Die(500);
				}

			}
		}
		enemyList4.delete_if(deleted);
		shotList.delete_if(deleted);
		dieList.delete_if(deleted);

		for (CSprite* enemyShot2 : enemyShotList4)
		{
			if (enemyShot2->HitTest(&player) && GetTime() > flickerTime) 
			{
				enemyShot2->Delete();
				playerDies.Play("playerdies.wav");
				lives--;
				player.SetPosition(100, 375);
				flickerTime = GetTime() + 3000;
			}
			if (enemyShot2->GetY() < 0) enemyShot2->Delete();
		}
		enemyShotList4.delete_if(deleted);
	}
}
void CMyGame::BarrelControl()
{

	if ((scene == 1 || scene == 2 || scene == 3 || scene == 4 || scene == 5)) //BARRELS COMING FROM THE RIGHT SIDE
	{
		if (rand() % 150 == 0)
		{
			CSprite* RollingBarrel = new CSprite(1285, 140, "rollingbarrel.bmp", CColor::Red(), GetTime());  
			RollingBarrel->SetVelocity(-150,0);    
			RollingBarrel->SetOmega(-150);
			barrelList.push_back(RollingBarrel);
		}

		for (CSprite* barrel : barrelList) 
		{
			for (CSprite* shot : shotList)
			{
				if (shot->HitTest(barrel)) //player shots collision check
				{
					shot->Delete();
					barrel->Delete();
					score = score + 25;

					//explosion animation
					CSprite* explosion = new CSprite(barrel->GetX(), barrel->GetY(), 0, 0, GetTime());
					explosion->AddImage("explosion.bmp", "explode", 5, 5, 0, 0, 4, 4, CColor::Black());        
					explosion->SetAnimation("explode", 25);
					explosionList.push_back(explosion);
					explosionFX.Play("tntexplosion.wav");
					explosionFX.Volume(1.0);
					explosion->Die(1000);
				}

			}
			if (player.HitTest(barrel) && GetTime() > flickerTime)  
			{
				barrel->Delete();
				//explosion animation
				CSprite* explosion = new CSprite(barrel->GetX(), barrel->GetY(), 0, 0, GetTime());
				explosion->AddImage("explosion.bmp", "explode", 5, 5, 0, 0, 4, 4, CColor::Black());
				explosion->SetAnimation("explode", 25);
				explosionList.push_back(explosion);
				explosionFX.Play("tntexplosion.wav");
				explosionFX.Volume(1.0);
				explosion->Die(1000);
				playerDies.Play("playerdies.wav");
				lives--;
				player.SetPosition(100, 375);
				flickerTime = GetTime() + 3000;
			}
		}
		barrelList.delete_if(deleted);
		shotList.delete_if(deleted);
		explosionList.delete_if(deleted);
	}

	if (scene == 3 || scene == 6 ) //BARRELS COMING FROM THE LEFT SIDE
	{
		if (rand() % 150 == 0)
		{
			CSprite* RollingBarrel = new CSprite(0, 140, "rollingbarrel.bmp", CColor::Red(), GetTime());
			RollingBarrel->SetVelocity(150, 0);
			RollingBarrel->SetOmega(150);
			barrelList.push_back(RollingBarrel);
		}

		for (CSprite* barrel : barrelList)
		{
			for (CSprite* shot : shotList)
			{
				if (shot->HitTest(barrel))
				{
					shot->Delete();
					barrel->Delete();
					score = score + 25;

					//explosion animation
					CSprite* explosion = new CSprite(barrel->GetX(), barrel->GetY(), 0, 0, GetTime());
					explosion->AddImage("explosion.bmp", "explode", 5, 5, 0, 0, 4, 4, CColor::Black());
					explosion->SetAnimation("explode", 25);
					explosion->Die(1000);
					explosionList.push_back(explosion);
					explosionFX.Play("tntexplosion.wav");
					explosionFX.Volume(1.0);
				}

			}
			if (player.HitTest(barrel) && GetTime() > flickerTime)  
			{
				barrel->Delete();
				//explosion animation
				CSprite* explosion = new CSprite(barrel->GetX(), barrel->GetY(), 0, 0, GetTime());
				explosion->AddImage("explosion.bmp", "explode", 5, 5, 0, 0, 4, 4, CColor::Black());
				explosion->SetAnimation("explode", 25);
				explosion->Die(1000);
				explosionList.push_back(explosion);
				explosionFX.Play("tntexplosion.wav");
				explosionFX.Volume(1.0);
				playerDies.Play("playerdies.wav");
				lives--;
				player.SetPosition(100, 375);
				flickerTime = GetTime() + 3000;
			}
		}
		barrelList.delete_if(deleted);
		shotList.delete_if(deleted);
		explosionList.delete_if(deleted);
	}
	
	if (scene == 5 || scene == 6) 	//barrels from the top side
	{
		vultureList.delete_all();
		skullList.delete_all();

		if (rand() % 150 == 0)
		{
			CSprite* topBarrel = new CSprite(rand()%1280, 720, "lyingbarrel.bmp", CColor::Red(), GetTime());
			topBarrel->SetVelocity(0, -200);
			barrelList.push_back(topBarrel);
		}
		for (CSprite* topBarrel : barrelList) 
		{
			if (topBarrel->GetY() <= 97) 
			{
				topBarrel->Delete();
				CSprite* explosion = new CSprite(topBarrel->GetX(), topBarrel->GetY(), 0, 0, GetTime());
				explosion->AddImage("explosion.bmp", "explode", 5, 5, 0, 0, 4, 4, CColor::Black());
				explosion->SetAnimation("explode", 25);
				explosion->Die(1000);
				explosionList.push_back(explosion);
				explosionFX.Play("tntexplosion.wav");
				explosionFX.Volume(1.0);
			}

		}
		barrelList.delete_if(deleted);
		explosionList.delete_if(deleted);
	
	}
}

void CMyGame::BossBarrelControl()   //GAME SOMETIMES CRASHES FIGHTING FINAL BOSS
{
	if (scene == 9) 
	{
		if (superBarrelList.size() == 0) 
		{

			if (rand() % 900 == 0)
			{
				alea = rand() % 3 + 1; //bossBarrels spawn at 3 different X positions
				if (alea == 1)
				{
					superX = 225;
				}
				else if (alea == 2)
				{
					superX = 625;
				}
				else if (alea == 3)
				{
					superX = 1035;
				}

				CSprite* superBarrel = new CSprite(superX, 375, "barrel.bmp", CColor::Red(), GetTime());   
				superBarrel->SetVelocity(0, -150);
				superBarrelList.push_back(superBarrel);
			}
		}

		for (CSprite* superBarrel : superBarrelList) 
		{
			if (superBarrel->GetY() <= 175) superBarrel->SetVelocity(0, 0); //setting final position for barrel

			float X = superBarrel->GetX(), Y = superBarrel->GetY();

			for (CSprite* shot : shotList) 
			{
				if (shot->HitTest(superBarrel) && superBarrel->GetYVelocity() == 0) //player shots collision check
				{
					shot->Delete();
					superBarrel->Delete();

					CSprite* explosion = new CSprite(X, Y+200, 0, 0, GetTime());
					explosion->AddImage("superExplosion.bmp", "supEx", 10, 1, 0, 0, 9, 0, CColor::Red());        
					explosion->SetAnimation("supEx");
					explosionList.push_back(explosion);
					explosionFX.Play("tntexplosion.wav");
					explosionFX.Volume(1.0);
					explosion->Die(1000);
				}
			}

		}

		for (CSprite* explosion : explosionList)  //GAME SOMETIMES CRASHES
		{
			for (CSprite* boss : finalBossList)
			{
				if (explosion->HitTest(boss) && GetTime() > flickerTime2)
				{
					boss->SetHealth(boss->GetHealth() - 500);
					explosion->Delete();
					flickerTime2 = GetTime() + 2000;

					if (boss->GetHealth() <= 0)
					{
						boss->Delete();
						vultureList.delete_all();
						enemyList3.delete_all();
						enemyList4.delete_all();
						barrelList.delete_all();
						enemyShotList3.delete_all();
						enemyShotList4.delete_all();
						balconyList.delete_all();
						bossShotList.delete_all();
						skullList.delete_all();
						//add sound FX
						score = score + 30000;
						gamewon = true;

					}
				}
			}

		}
		explosionList.delete_if(deleted);
		shotList.delete_if(deleted);
		superBarrelList.delete_if(deleted);
	}

}

void CMyGame::Boss1Control()
{
	if (scene == 3)
	{

		if (bossList.size() == 0 && respawnB1 == true) //Creating one boss sprite
		{
			CSprite* boss1 = new CSprite(640, 472, "boss1.bmp", CColor::Red(), GetTime());
			boss1->AddImage("boss1.bmp", "boss1", 1, 1, 0, 0, 0, 0, CColor::Red());
			boss1->SetAnimation("boss1");
			boss1->SetHealth(750);
			boss1->SetVelocity(50, 0);
			bossList.push_back(boss1);
		}
		respawnB1 = false;

		for (CSprite* boss1 : bossList) //Creating Boss movement and shots at 3 different angles
		{

			if (boss1->GetX() >= 780)
			{
				boss1->SetVelocity(-50, 0);

			}
			if (boss1->GetX() <= 520)
			{
				boss1->SetVelocity(50, 0);

			}

			if (rand() % 200 == 0)
			{
				CSprite* bossShot = new CSprite(boss1->GetX(), boss1->GetY(), "shot2.bmp", CColor::White(), GetTime());
				bossShot->SetDirection(180);
				bossShot->SetSpeed(250);
				enemyShot.Play("enemyshot.wav");
				enemyShot.Volume(1.0);
				bossShotList.push_back(bossShot);

			}
			if (rand() % 200 == 0)
			{
				CSprite* bossShot = new CSprite(boss1->GetX(), boss1->GetY(), "shot2.bmp", CColor::White(), GetTime());
				bossShot->SetDirection(225);
				bossShot->SetSpeed(250);
				enemyShot.Play("enemyshot.wav");
				enemyShot.Volume(1.0);
				bossShotList.push_back(bossShot);

			}
			if (rand() % 200 == 0)
			{
				CSprite* bossShot = new CSprite(boss1->GetX(), boss1->GetY(), "shot2.bmp", CColor::White(), GetTime());
				bossShot->SetDirection(135);
				bossShot->SetSpeed(250);
				enemyShot.Play("enemyshot.wav");
				enemyShot.Volume(1.0);
				bossShotList.push_back(bossShot);
			}
			for (CSprite* shot : shotList) //player shots collision check
			{
				if (shot->HitTest(boss1))
				{
					shot->Delete();
					boss1->SetHealth(boss1->GetHealth() - 10);
					//soundFX

					if (boss1->GetHealth() <= 0)
					{
						boss1->Delete();
						vultureList.delete_all();
						enemyList.delete_all();
						enemyList2.delete_all();
						barrelList.delete_all();
						enemyShotList.delete_all();
						enemyShotList2.delete_all();
						balconyList.delete_all();
						bossShotList.delete_all();
						skullList.delete_all();
						//add sound FX
						score = score + 10000;
						level++;

					}
				}
			}
		}
		shotList.delete_if(deleted);
		bossList.delete_if(deleted);

		for (CSprite* bossShot : bossShotList)
		{
			if (bossShot->HitTest(&player) && GetTime() > flickerTime)  
			{
				bossShot->Delete();
				playerDies.Play("playerdies.wav");
				lives--;
				player.SetPosition(100, 375);
				flickerTime = GetTime() + 3000;
			}
			if (bossShot->GetY() < 100)
			{
				bossShot->Delete();
				sBullet.Play("strayBullet.wav"); 
				sBullet.Volume(0.5);
			}

		}
	}
	bossShotList.delete_if(deleted);
}

void CMyGame::Boss2Control()
{
	if (scene == 6) 
	{
		if (bossList.size() == 0 && respawnB2 == true) //Creating two different boss sprites
		{
			CSprite* boss2R = new CSprite(1050, 155, "boss2.bmp", CColor::Red(), GetTime());
			boss2R->AddImage("boss2.bmp", "redDown", 3, 2, 2, 1, 2, 1, CColor::Red());
			boss2R->AddImage("boss2.bmp", "redShot", 3, 2, 1, 1, 0, 1, CColor::Red());
			boss2R->SetAnimation("redDown");
			boss2R->SetHealth(1000);
			bossList.push_back(boss2R);

			CSprite* boss2G = new CSprite(1050, 455, "boss2.bmp", CColor::Red(), GetTime());
			boss2G->AddImage("boss2.bmp", "greenDown", 3, 2, 2, 0, 2, 0, CColor::Red());
			boss2G->AddImage("boss2.bmp", "greenShot", 3, 2, 1, 0, 0, 0, CColor::Red());
			boss2G->SetAnimation("greenDown");
			boss2G->SetHealth(1200);
			bossList2.push_back(boss2G);
			
		}
		respawnB2 = false;

		for (CSprite* boss2R : bossList) //implementing basic AI for the second bosses which got two different animations each one
		{
			do 
			{
				
				if (rand() % 50 == 0)
				{
					boss2R->SetAnimation("redDown");

					if (rand() % 2 == 0)
					{
						boss2R->SetAnimation("redShot", 10);
						CSprite* bossShot = new CSprite(boss2R->GetX() - 50, boss2R->GetY() + 35, "shot2.bmp", CColor::White(), GetTime());
						bossShot->SetDirection(274);
						bossShot->SetSpeed(250);
						enemyShot.Play("enemyshot.wav");
						enemyShot.Volume(1.0);
						bossShotList.push_back(bossShot);
					}
				}

			} while (boss2R->GetHealth() == 0);
			
			for (CSprite* bossShot : bossShotList)
			{
				if (bossShot->HitTest(&player) && GetTime() > flickerTime)  //boss shots collision check
				{
					bossShot->Delete();
					playerDies.Play("playerdies.wav");
					lives--;
					player.SetPosition(100, 375);
					flickerTime = GetTime() + 3000;
				}
				if (bossShot->GetX() < 0)
				{
					bossShot->Delete();
				}
			}
			for (CSprite* shot : shotList) //player shots collision check
			{
				if (shot->HitTest(boss2R))
				{
					shot->Delete();
					boss2R->SetHealth(boss2R->GetHealth() - 10);
					//soundFX

					if (boss2R->GetHealth() <= 0)
					{
						boss2R->Delete();
						//add sound FX
						score = score + 10000;
					}
				}
			}
		}
		bossShotList.delete_if(deleted);
		shotList.delete_if(deleted);
		bossList.delete_if(deleted);

		for (CSprite* boss2G : bossList2) //implementing basic AI for the second bosses which got two different animations each one
		{
			do
			{

				if (rand() % 50 == 0)
				{
					boss2G->SetAnimation("greenDown");
					target = false; //boolean that provides inmunity to hitTest while the boss hides behind a sprite image (not an object)

					if (rand() % 2 == 0)
					{
						target = true;
						boss2G->SetAnimation("greenShot", 10);
						CSprite* bossShot = new CSprite(boss2G->GetX() - 50, boss2G->GetY() + 35, "shot2.bmp", CColor::White(), GetTime());
						bossShot->SetDirection(230);
						bossShot->SetSpeed(250);
						enemyShot.Play("enemyshot.wav");
						enemyShot.Volume(1.0);
						bossShotList.push_back(bossShot);
					}
				}

			} while (boss2G->GetHealth() == 0);

			for (CSprite* bossShot : bossShotList)
			{
				if (bossShot->HitTest(&player) && GetTime() > flickerTime)
				{
					bossShot->Delete();
					playerDies.Play("playerdies.wav");
					lives--;
					player.SetPosition(100, 375);
					flickerTime = GetTime() + 3000;
				}
				if (bossShot->GetX() < 0)
				{
					bossShot->Delete();
				}
			}
			for (CSprite* shot : shotList)
			{
				if (shot->HitTest(boss2G) && target == true)
				{
					shot->Delete();
					boss2G->SetHealth(boss2G->GetHealth() - 10);
					//soundFX

					if (boss2G->GetHealth() <= 0)
					{
						boss2G->Delete();
						//add sound FX
						score = score + 10000;
					}
				}
			}
		}
		bossShotList.delete_if(deleted);
		shotList.delete_if(deleted);
		bossList2.delete_if(deleted);


		if (bossList.size() == 0 && bossList2.size() == 0) //clearing the stage once the boss is defeated
		{
			enemyList.delete_all();
			enemyList2.delete_all();
			enemyList3.delete_all();
			enemyList4.delete_all();
			barrelList.delete_all();
			enemyShotList.delete_all();
			enemyShotList2.delete_all();
			balconyList.delete_all();
			bossShotList.delete_all();
			shotList.delete_all();
			torchList.delete_all();
			mineCartList.delete_all();
			lives = lives + 2;
			level++;
			
		}
	}

}

void CMyGame::Boss3Control()
{
	if (scene == 9)
	{
		if (finalBossList.size() == 0) //Creating one boss sprite
		{
			CSprite* finalBoss = new CSprite(1200, 510, "boss3t.bmp", CColor::Red(), GetTime());
			finalBoss->AddImage("boss3t.bmp", "walkingLeft", 4, 2, 0, 0, 4, 0, CColor::Red());
			finalBoss->AddImage("boss3t.bmp", "walkingRight", 4, 2, 0, 1, 4, 1, CColor::Red());
			finalBoss->SetAnimation("walkingLeft");
			finalBoss->SetVelocity(-120,0);
			finalBoss->SetHealth(2500);
			finalBossList.push_back(finalBoss);

		}
		for (CSprite* finalBoss : finalBossList) 
		{

			for (CSprite* shot : shotList)
			{
				if (shot->HitTest(finalBoss)) 
				{
					shot->Delete();
					metalJ.Play("metalJacket.wav");
				}
			}

			if (finalBoss->GetX() < 100) //implementing simple AI for the final boss, while less health, more velocity
			{
				finalBoss->SetAnimation("walkingRight");

				if (finalBoss->GetHealth() <= 1500 && finalBoss->GetHealth() > 500)
				{
					finalBoss->SetVelocity(170, 0);
				}
				else if (finalBoss->GetHealth() == 500) 
				{
					finalBoss->SetVelocity(200, 0);
				}
				else 
				{
					finalBoss->SetVelocity(120, 0);
				}
				
			}
			if (finalBoss->GetX() > 1200)
			{
				finalBoss->SetAnimation("walkingLeft");

				if (finalBoss->GetHealth() <= 1500 && finalBoss->GetHealth() > 500)
				{
					finalBoss->SetVelocity(-170, 0);
				}
				else if (finalBoss->GetHealth() == 500)
				{
					finalBoss->SetVelocity(-200, 0);
				}
				else
				{
					finalBoss->SetVelocity(-120, 0);
				}

			}

			if (finalBoss->GetXVelocity() > 0) //setting boss shots at random frame with specific direction for shots
			{
				if (rand() % 50 == 0)
				{
					CSprite* bossShot = new CSprite(finalBoss->GetX()+40, finalBoss->GetY()-15, "shot2.bmp", CColor::White(), GetTime());
					bossShot->SetDirection(135);
					bossShot->SetSpeed(350);
					enemyShot.Play("enemyshot.wav");
					bossShotList.push_back(bossShot);

				}
				if (rand() % 50 == 0)
				{
					CSprite* bossShot = new CSprite(finalBoss->GetX()+65, finalBoss->GetY()-2, "shot2.bmp", CColor::White(), GetTime());
					bossShot->SetDirection(130);
					bossShot->SetSpeed(350);
					enemyShot.Play("enemyshot.wav");
					bossShotList.push_back(bossShot);

				}
			}
			if (finalBoss->GetXVelocity() < 0) 
			{
				if (rand() % 50 == 0)
				{
					CSprite* bossShot = new CSprite(finalBoss->GetX() - 40, finalBoss->GetY() - 15, "shot2.bmp", CColor::White(), GetTime());
					bossShot->SetDirection(-135);
					bossShot->SetSpeed(350);
					enemyShot.Play("enemyshot.wav");
					bossShotList.push_back(bossShot);

				}
				if (rand() % 50 == 0)
				{
					CSprite* bossShot = new CSprite(finalBoss->GetX() - 65, finalBoss->GetY() - 2, "shot2.bmp", CColor::White(), GetTime());
					bossShot->SetDirection(-130);
					bossShot->SetSpeed(350);
					enemyShot.Play("enemyshot.wav");
					bossShotList.push_back(bossShot);

				}
			}
		}
		for (CSprite* bossShot : bossShotList) //boss shots collision check
		{
			if (bossShot->GetY() < 100) 
			{
				bossShot->Delete();
				sBullet.Play("strayBullet.wav");
				sBullet.Volume(0.2);
			}
			if (bossShot->HitTest(&player) && GetTime() > flickerTime)
			{
				bossShot->Delete();
				playerDies.Play("playerdies.wav");
				lives--;
				player.SetPosition(100, 375);
				flickerTime = GetTime() + 3000;
			}
		}
		

	}
	bossShotList.delete_if(deleted);
	shotList.delete_if(deleted);
}

void CMyGame::OnDraw(CGraphics* g)
{

	if (IsMenuMode())
	{
		startScreen.Draw(g);
		return;
	}

	//Drawing background, sprites and additional information on the screen
	if (level == 1 || level == 2 || level == 3) 
	{
		background.Draw(g);
	}
	
	for (CSprite* boss2 : bossList2) boss2->Draw(g);
	for (CSprite* torch : torchList) torch->Draw(g);
	for (CSprite* explosion : explosionList) explosion->Draw(g);
	for (CSprite* boss1 : bossList) boss1->Draw(g);
	for (CSprite* balcony : balconyList) balcony->Draw(g);
	for (CSprite* vulture : vultureList) vulture->Draw(g);
	for (CSprite* skull : skullList) skull->Draw(g);
	for (CSprite* enemy : enemyList) enemy->Draw(g);
	for (CSprite* enemyR : enemyList2) enemyR->Draw(g);
	for (CSprite* enemyR : enemyList3) enemyR->Draw(g);
	for (CSprite* enemyR : enemyList4) enemyR->Draw(g);
	for (CSprite* enemy : dieList) enemy->Draw(g);
	for (CSprite* shot : enemyShotList) shot->Draw(g);
	for (CSprite* shot2 : enemyShotList2) shot2->Draw(g);
	for (CSprite* shot2 : enemyShotList3) shot2->Draw(g);
	for (CSprite* shot2 : enemyShotList4) shot2->Draw(g);
	for (CSprite* bossShot : bossShotList) bossShot->Draw(g);
	for (CSprite* shot : shotList) shot->Draw(g);
	for (CSprite* cart : mineCartList) cart->Draw(g);
	for (CSprite* RollingBarrel : barrelList) RollingBarrel->Draw(g);
	for (CSprite* superBarrel : superBarrelList) superBarrel->Draw(g);


	//flickering visual effect after any collision against player (any hitTest against player provides a short inmunity time)
	if (GetTime() < flickerTime  && (rand() % 10 > 5))
		player.Draw(g);

	if (GetTime() > flickerTime)
		player.Draw(g);

	if (GetTime() < flickerTime2 && (rand() % 10 > 5))
		for (CSprite* boss : finalBossList) boss->Draw(g);

	if (GetTime() > flickerTime2)
		for (CSprite* boss : finalBossList) boss->Draw(g);


	
	background_cover.Draw(g);
	if (level == 1)vulture.Draw(g);
	if (level == 1)skull.Draw(g);




		

	//DRAWING LIVES COUNTER
	for (int n = 50; n <= lives * 50; n += 50)
	{
		bullet.SetX(float(n));
		bullet.SetY(30);
		bullet.Draw(g);
	}

	*g << font(28) << color(CColor::Green()) << xy (400, 20)<< "$: ";
	*g << font(28) << color(CColor::Green()) << xy(425, 20) << score; 


	/*for (CSprite* boss : finalBossList) 
	{
		*g << font(28) << color(CColor::Red()) << xy(1000, 50) << boss->GetHealth();
	}*/
	
	if (IsGameOver())
	{
		if (gamewon)
		{
			gameOver.Draw(g);
			*g << font(46) << color(CColor::Green()) << vcenter << center << endl << endl << "FINAL SCORE : " << score;
			*g << font(30) << color(CColor::Green()) << vcenter << center << endl << endl << endl << endl << endl << "PRESS  F2  TO  CONTINUE";
			player.SetPosition(-500, 0);
			shotList.delete_all();
		}
		else
		{
			gameOver.Draw(g);
			*g << font(46) << color(CColor::Green()) << vcenter << center << endl << endl << "FINAL SCORE : " << score;
			*g << font(30) << color(CColor::Green()) << vcenter << center << endl << endl << endl << endl << endl << "PRESS  F2  TO  CONTINUE";
			player.SetPosition(-500,0);
			shotList.delete_all();
		}
	}
	

}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{	
	startScreen.LoadImage("StartScreen.bmp", CColor::White());
	startScreen.SetImage("StartScreen.bmp");
	startScreen.SetPosition(640, 360);

	PlayerControl();

	target;
	alea;
	superX;

}


// called when a new game is requested (e.g. when F2 pressed)
// use this function to prepare a menu or a welcome screen
void CMyGame::OnDisplayMenu()
{
	sGameOver.Stop();
	backgroundTheme.Stop();
	bossTheme.Stop();
	finalBossTheme.Stop();
	levelSelect.Play("levelSelect.wav", -1);
	// exits the menu mode and starts the game mode
}

void CMyGame::setUpLevel1()
{

	if (scene == 0) //scene 1 of level 1
	{
		
		background.LoadImage("background_1.bmp");
		background.SetImage("background_1.bmp");
		Enemy1Control(); //THIS FUNCTION TRIGGERS SCENE 1
		
	}
	
	if (player.GetX() >= 1280 && scene == 1) //scene 2 of level 1
	{

		background.LoadImage("background_2.bmp");
		background.SetImage("background_2.bmp");
		barrelList.delete_all();
		player.SetPosition(100, 175);
		scene++;
		
	}

	if (player.GetX() >= 1280 && scene == 2) // scene 3 of level 1
	{
		backgroundTheme.Stop();
		bossTheme.Play("bossTheme.wav", -1);
		bossTheme.Volume(0.3);
		background.LoadImage("background_3.bmp");
		background.SetImage("background_3.bmp");
		Boss1Control();
		BalconyControl();
		barrelList.delete_all();
		vultureList.delete_all();
		shotList.delete_all();
		enemyList.delete_all();
		enemyList2.delete_all();
		enemyShotList.delete_all();
		enemyShotList2.delete_all();
		player.SetPosition(100, 175);
		scene++;
	}
}

void CMyGame::BalconyControl() 
{
	if (scene == 3)  //setting objects on scene 3 (protecting first boss)
	{	

		if (balconyList.size() == 0 && respawn == true)
		{
			int startPoint = 345;
			for (int times = 0; times < 3; times++)
			{
				CSprite* balcony = new CSprite(startPoint, 432, "balcony.bmp", CColor::Red(), GetTime());
				balcony->AddImage("balcony.bmp", "balcony", 1, 1, 0, 0, 0, 0, CColor::Red());
				balcony->SetAnimation("balcony");
				balcony->SetHealth(1000);
				balconyList.push_back(balcony);
				startPoint = startPoint + 300;
			}
		}
		respawn = false;

		for (CSprite* balcony : balconyList)
		{
			for (CSprite* shot : shotList)
			{
				if (shot->HitTest(balcony))
				{
					shot->Delete();
					balcony->SetHealth(balcony->GetHealth() -10);
					//soundFX

					if (balcony->GetHealth() <= 0) 
					{
						balcony->Delete();
						brokenBalcony.Play("brokenRock.wav");
						brokenBalcony.Volume(0.2);
					}
				}
			}
		}
		shotList.delete_if(deleted);
		balconyList.delete_if(deleted);
	}

}

void CMyGame::setUpLevel2()
{
	respawnB1 = true;
	
	if (level == 2 && scene == 3) //scene 1 of level 2
	{
		shotList.delete_all();
		scene++;
		bossTheme.Stop();
		backgroundTheme.Play("backgroundTheme.wav", -1);
		background.LoadImage("background_4.bmp");
		background.SetImage("background_4.bmp");
		background_cover.LoadImage("background_4_cover.bmp", "cover", 1, 1, 0, 0, CColor::Red());
		background_cover.SetImage("cover");
		background_cover.SetPosition(640, 360);
		player.SetPosition(100, 375);
	}

	if (player.GetX() >= 1150 && scene == 4)
	{
		
		background.LoadImage("background_5.bmp");
		background.SetImage("background_5.bmp");
		background_cover.SetPosition(-1000, -1000);
		player.SetPosition(100, 175);
		scene++;
		
		//torches
		int startPoint = 200;
		for (int times = 0; times < 3; times++)
		{
			if (times == 1)
			{
				startPoint = 622;
			}
			if (times == 2)
			{
				startPoint = 1050;
			}

			CSprite* torch = new CSprite(startPoint, 560, "torch.bmp", CColor::Red(), GetTime());
			torch->AddImage("torch.bmp", "torchOn", 4, 1, 0, 0, 4, 0, CColor::Red());                               
			torch->SetAnimation("torchOn");
			torchList.push_back(torch);

		}
		
		
		for (int times = 0; times < 2; times++)
		{
			int startPoint = 420;

			if (times == 1)
			{
				startPoint = 833;
			}

			CSprite* torch = new CSprite(startPoint, 235, "torch.bmp", CColor::Red(), GetTime());
			torch->AddImage("torch.bmp", "torchOn", 4, 1, 0, 0, 4, 0, CColor::Red()); //4 imagenes 1 fila, empieza en 00 acaba en 
			torch->SetAnimation("torchOn");
			torchList.push_back(torch);

		}

	}

	if (player.GetX() >= 1280 && scene == 5) //SETTING UP SCENE 6
	{
		for (CSprite* torch : torchList)
		{
			torch->Delete();
		}
		torchList.delete_if(deleted);

		backgroundTheme.Stop();
		bossTheme.Play("bossTheme.wav", -1);
		bossTheme.Volume(0.3);
		background.LoadImage("background_6.bmp");
		background.SetImage("background_6.bmp");
		shotList.delete_all();
		barrelList.delete_all();
		enemyList.delete_all();
		enemyList2.delete_all();
		enemyList3.delete_all();
		enemyList4.delete_all();
		enemyShotList.delete_all();
		enemyShotList2.delete_all();
		enemyShotList3.delete_all();
		enemyShotList4.delete_all();
		player.SetPosition(100, 175);
		scene++;

		//DRAWING TORCHES LIST WITH DIFFERENT X POSITION
		int startPoint = 200;
		for (int times = 0; times < 4; times++)
		{
			if (times == 1)
			{
				startPoint = 520;
			}
			if (times == 2)
			{
				startPoint = 793;
			}
			if (times == 3) 
			{
				startPoint = 1050;
			}

			CSprite* torch = new CSprite(startPoint, 560, "torch.bmp", CColor::Red(), GetTime());
			torch->AddImage("torch.bmp", "torchOn", 4, 1, 0, 0, 4, 0, CColor::Red());
			torch->SetAnimation("torchOn");
			torchList.push_back(torch);

		}
		
		for (int times = 0; times < 2; times++)
		{
			int startPoint = 420;

			if (times == 1)
			{
				startPoint = 833;
			}

			CSprite* torch = new CSprite(startPoint, 235, "torch.bmp", CColor::Red(), GetTime());
			torch->AddImage("torch.bmp", "torchOn", 4, 1, 0, 0, 4, 0, CColor::Red());  
			torch->SetAnimation("torchOn");
			torchList.push_back(torch);

		}
		//MINECART AND WOODSTACK

		for (int times = 0; times < 1; times++)
		{

			CSprite* mineCart = new CSprite(900, 135, "mineCart.bmp", CColor::Red(), GetTime());
			mineCart->AddImage("mineCart.bmp", "mineCart", 1, 1, 0, 0, 0, 0, CColor::Red()); 
			mineCart->SetAnimation("mineCart");
			mineCartList.push_back(mineCart);
		}
		
		for (int times = 0; times < 1; times++)
		{

			CSprite* mineCart = new CSprite(940, 390, "woodStack.bmp", CColor::Red(), GetTime());
			mineCart->AddImage("woodStack.bmp", "wood", 1, 1, 0, 0, 0, 0, CColor::Red()); 
			mineCart->SetAnimation("wood");
			torchList.push_back(mineCart);
		}
	}


}

void CMyGame::setUpLevel3()
{
	if (level == 3 && scene == 6) //scene 1 of level 2
	{
		scene++;
		bossTheme.Stop();
		backgroundTheme.Play("backgroundTheme.wav", -1);
		background.LoadImage("background_7.bmp");
		background.SetImage("background_7.bmp");
		player.SetPosition(100, 375);
	}

	if (player.GetX() >= 1280 && scene == 7) 
	{
		background.LoadImage("background_8.bmp");
		background.SetImage("background_8.bmp");
		vultureList.delete_all();
		skullList.delete_all();
		enemyList.delete_all();
		enemyList2.delete_all();
		enemyShotList.delete_all();
		enemyShotList2.delete_all();
		enemyShotList3.delete_all();
		enemyShotList4.delete_all();
		player.SetPosition(100, 175);
		scene++;
		
	}
	if (player.GetX() >= 1280 && scene == 8) 
	{
		backgroundTheme.Stop();
		finalBossTheme.Play("finalBossTheme.wav", -1);
		bossTheme.Volume(0.3);
		background.LoadImage("background_9.bmp");
		background.SetImage("background_9.bmp");
		vultureList.delete_all();
		skullList.delete_all();
		enemyList.delete_all();
		enemyList2.delete_all();
		enemyList3.delete_all();
		enemyList4.delete_all();
		enemyShotList.delete_all();
		enemyShotList2.delete_all();
		enemyShotList3.delete_all();
		enemyShotList4.delete_all();
		player.SetPosition(100, 175);
		scene++;
	}


}

// called when a new game is started
// as a second phase after a menu or a welcome screen
void CMyGame::OnStartGame()
{
	sGameOver.Stop();
	levelSelect.Stop();
	bossTheme.Stop();
	finalBossTheme.Stop();
	backgroundTheme.Play("backgroundTheme.wav", -1);
	backgroundTheme.Volume(0.3);

	//resetting all values
	background.SetPosition(640, 360);
	background_cover.SetPosition(400, -1000);
	player.SetPosition(100, 175);
	player.SetYVelocity(-500);
	score = 0;
	lives = 6;
	flickerTime = 0;
	flickerTime2 = 0;
	respawn = true;
	respawnB1 = true;
	respawnB2 = true;
	respawnB3 = true;
	facingLeft = false;
	gamewon = false;


	//deleting all sprites
	shotList.delete_all();
	barrelList.delete_all();
	explosionList.delete_all();
	vultureList.delete_all();
	enemyList.delete_all();
	enemyList2.delete_all();
	enemyShotList.delete_all();
	enemyShotList2.delete_all();
	enemyList3.delete_all();
	enemyShotList3.delete_all();
	enemyList4.delete_all();
	enemyShotList4.delete_all();
	balconyList.delete_all();
	bossList.delete_all();
	bossList2.delete_all();
	bossShotList.delete_all();
	torchList.delete_all();
	mineCartList.delete_all();
	dieList.delete_all();
	superBarrelList.delete_all();
	finalBossList.delete_all();

	if (level == 1) setUpLevel1();
	if (level == 2) setUpLevel2();
	if (level == 3) setUpLevel3();

}

// called when a new level started - first call for nLevel = 1  STILL DO NOT KNOW WHAT IS THE USE F THIS
void CMyGame::OnStartLevel(Sint16 nLevel)
{	
}

// called when the game is over
void CMyGame::OnGameOver()
{
	bossTheme.Stop();
	finalBossTheme.Stop();
	backgroundTheme.Stop();

	if (lives == 0) 
	{
		sGameOver.Play("gameOver.wav");
		sGameOver.Volume(1.5);
	}
	else 
	{
		sGameWon.Play("gameWon.wav");
		sGameWon.Volume(2.0);
	}
	
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	//GAME CONTROLS
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_F3)
		PauseGame();
	if (sym == SDLK_F2)
		NewGame();
	if (IsMenuMode()) //keyboard input to select level 
	{
		if (sym == SDLK_1)
		{
			level = 1;
			scene = 0;
			sBullet.Play("strayBullet.wav");
			StartGame();
		}
		if (sym == SDLK_2)
		{
			level = 2;
			scene = 3;
			sBullet.Play("strayBullet.wav");
			StartGame();
		}
		if (sym == SDLK_3)
		{
			level = 3;
			scene = 6;
			sBullet.Play("strayBullet.wav");
			StartGame();
		}
	}

	//PLAYER KEYBOARD CONTROL
	if (sym == SDLK_RIGHT)
	{
		facingLeft = false;
		player.SetVelocity(150, 0);
		player.SetAnimation("walk_right");  

	}

	if (sym == SDLK_LEFT)
	{
		facingLeft = true;
		player.SetVelocity(-150, 0);
		player.SetAnimation("walk_left");
	}
	if (sym == SDLK_DOWN)
	{
		if (facingLeft == false)
		{
			player.SetVelocity(0, 0);
			player.SetAnimation("down"); 
		}
		else 
		{
			facingLeft = true;
			player.SetVelocity(0, 0);
			player.SetAnimation("downL");
		}
	}
	if (sym == SDLK_UP)
	{
		facingLeft = false;
		player.SetVelocity(0, 0);
		player.SetAnimation("up");

	}

	if (sym == SDLK_RCTRL && player.GetYVelocity() == 0)
	{
		//JUMP 
		player.SetYVelocity(8000);
		player.SetAnimation("jump");
		if (facingLeft == true) 
		{
			player.SetAnimation("jumpL");
		}
	}

	if (IsKeyDown(SDLK_RIGHT) && IsKeyDown(SDLK_UP)) //WALKING TO THE RIGHT SIDE AND FACING TOP SIDE
	{
		facingLeft = false;
		player.SetVelocity(150, 0);
		player.SetAnimation("diagonalR");
	}

	if (IsKeyDown(SDLK_LEFT) && IsKeyDown(SDLK_UP)) //WALKING TO THE LEFT SIDE AND FACING TOP SIDE
	{
		facingLeft = true;
		player.SetVelocity(-150, 0);
		player.SetAnimation("diagonalL");
	}

	//PLAYER SHOOTING EVENTS
	if (sym == SDLK_SPACE && IsKeyDown(SDLK_UP) == false && IsKeyDown(SDLK_DOWN) == false && facingLeft == false) //SHOOTING TO THE RIGHT SIDE
	{
		CSprite* newShot = new CSprite(player.GetX() + 50, player.GetY() + 5, "shot.bmp", CColor::White(), GetTime());
		newShot->SetDirection(90);
		newShot->SetSpeed(500);
		shotList.push_back(newShot);
		sShot.Play("gunshot.wav");
		sShot.Volume(1.0);
	}
	if (sym == SDLK_SPACE && IsKeyDown(SDLK_UP) == false && IsKeyDown(SDLK_DOWN) == false && facingLeft == false) //SECOND SHOT TO THE RIGHT SIDE
	{
		CSprite* newShot = new CSprite(player.GetX() + 70, player.GetY() + 15, "shot.bmp", CColor::White(), GetTime());
		newShot->SetDirection(89);
		newShot->SetSpeed(500);
		shotList.push_back(newShot);
		sShot.Play("gunshot.wav");
		sShot.Volume(1.0);
	}

	if (sym == SDLK_SPACE && IsKeyDown(SDLK_UP) == false && IsKeyDown(SDLK_DOWN) == false && facingLeft == true) // SHOOTING TO THE LEFT SIDE
	{
		CSprite* newShot = new CSprite(player.GetX() -50, player.GetY() + 5, "shot.bmp", CColor::White(), GetTime());
		newShot->SetDirection(270);
		newShot->SetSpeed(500);
		shotList.push_back(newShot);
		sShot.Play("gunshot.wav");
		sShot.Volume(1.0);
	}

	if (sym == SDLK_SPACE && IsKeyDown(SDLK_UP) == false && IsKeyDown(SDLK_DOWN) == false && facingLeft == true) // SECOND SHOT TO THE LEFT SIDE
	{
		CSprite* newShot = new CSprite(player.GetX() -70, player.GetY() + 15, "shot.bmp", CColor::White(), GetTime());
		newShot->SetDirection(271);
		newShot->SetSpeed(500);
		shotList.push_back(newShot);
		sShot.Play("gunshot.wav");
		sShot.Volume(1.0);
	}
	
	if (IsKeyDown(SDLK_UP) && sym == SDLK_SPACE && IsKeyDown(SDLK_RIGHT) == false && IsKeyDown(SDLK_LEFT) == false) //SHOOTING TO THE UPPER SIDE
	{
		player.SetVelocity(0, 0);
		player.SetAnimation("up");
		CSprite* newShot = new CSprite(player.GetX() + 20, player.GetY() + 25, "shot.bmp", CColor::White(), GetTime());
		newShot->SetDirection(0);
		newShot->SetSpeed(500);
		shotList.push_back(newShot);
		sShot.Play("gunshot.wav");
		sShot.Volume(1.0);
	}

	if (IsKeyDown(SDLK_UP) && sym == SDLK_SPACE && IsKeyDown(SDLK_RIGHT) == false && IsKeyDown(SDLK_LEFT) == false) //SECOND SHOT TO THE UPPER SIDE
	{
		player.SetVelocity(0, 0);
		player.SetAnimation("up");
		CSprite* newShot = new CSprite(player.GetX() - 35, player.GetY() + 25, "shot.bmp", CColor::White(), GetTime());
		newShot->SetDirection(0);
		newShot->SetSpeed(500);
		shotList.push_back(newShot);
		sShot.Play("gunshot.wav");
		sShot.Volume(1.0);
	}

	if (IsKeyDown(SDLK_DOWN) && sym == SDLK_SPACE && facingLeft == false) //SHOT WHILE CROUCHING TO THE RIGHT SIDE
	{
		player.SetVelocity(0, 0);
		player.SetAnimation("down");
		CSprite* newShot = new CSprite(player.GetX() + 50, player.GetY() -8, "shot.bmp", CColor::White(), GetTime());
		newShot->SetDirection(89);
		newShot->SetSpeed(500);
		shotList.push_back(newShot);
		sShot.Play("gunshot.wav");
		sShot.Volume(1.0);
	}

	if (IsKeyDown(SDLK_DOWN) && sym == SDLK_SPACE && facingLeft == false) //SECOND SHOT WHILE CROUCHING TO THE RIGHT SIDE
	{
		player.SetVelocity(0, 0);
		player.SetAnimation("down");
		CSprite* newShot = new CSprite(player.GetX() + 40, player.GetY() - 18, "shot.bmp", CColor::White(), GetTime());
		newShot->SetDirection(90);
		newShot->SetSpeed(500);
		shotList.push_back(newShot);
		sShot.Play("gunshot.wav");
		sShot.Volume(1.0);
	}

	if (IsKeyDown(SDLK_DOWN) && sym == SDLK_SPACE && facingLeft == true) //SHOT WHILE CROUCHING TO THE LEFT SIDE
	{
		player.SetVelocity(0, 0);
		player.SetAnimation("downL");
		CSprite* newShot = new CSprite(player.GetX() -70, player.GetY() - 8, "shot.bmp", CColor::White(), GetTime());
		newShot->SetDirection(271);
		newShot->SetSpeed(500);
		shotList.push_back(newShot);
		sShot.Play("gunshot.wav");
		sShot.Volume(1.0);
	}

	if (IsKeyDown(SDLK_DOWN) && sym == SDLK_SPACE && facingLeft == true) //SECOND SHOT WHILE CROUCHING TO THE LEFT SIDE
	{
		player.SetVelocity(0, 0);
		player.SetAnimation("downL");
		CSprite* newShot = new CSprite(player.GetX() -50, player.GetY() - 18, "shot.bmp", CColor::White(), GetTime());
		newShot->SetDirection(270);
		newShot->SetSpeed(500);
		shotList.push_back(newShot);
		sShot.Play("gunshot.wav");
		sShot.Volume(1.0);
	}

	if (IsKeyDown(SDLK_UP) && IsKeyDown(SDLK_RIGHT) && sym == SDLK_SPACE) //SHOOTING IN DIAGONAL TO THE TOP/RIGHT SIDE
	{
		player.SetVelocity(150, 0);
		player.SetAnimation("diagonalR");
		CSprite* newShot = new CSprite(player.GetX() + 20, player.GetY() + 25, "shot.bmp", CColor::White(), GetTime());
		newShot->SetDirection(50);
		newShot->SetSpeed(500);
		shotList.push_back(newShot);
		sShot.Play("gunshot.wav");
		sShot.Volume(1.0);
	}
	if (IsKeyDown(SDLK_UP) && IsKeyDown(SDLK_RIGHT) && sym == SDLK_SPACE) //SECOND SHOT AT 45 DEGREES TO THE TOP/RIGHT SIDE
	{
		
		player.SetVelocity(150, 0);
		player.SetAnimation("diagonalR");
		CSprite* newShot = new CSprite(player.GetX() + 25, player.GetY() + 40, "shot.bmp", CColor::White(), GetTime());
		newShot->SetDirection(44);
		newShot->SetSpeed(500);
		shotList.push_back(newShot);
		sShot.Play("gunshot.wav");
		sShot.Volume(1.0);
	}

	if (IsKeyDown(SDLK_UP) && IsKeyDown(SDLK_LEFT) && sym == SDLK_SPACE && IsKeyDown(SDLK_RIGHT) == false) //SHOOTING IN DIAGONAL TO THE TOP/LEFT SIDE
	{
		
		player.SetVelocity(-150, 0);
		player.SetAnimation("diagonalL");
		CSprite* newShot = new CSprite(player.GetX() + 20, player.GetY() + 25, "shot.bmp", CColor::White(), GetTime());
		newShot->SetDirection(-50);
		newShot->SetSpeed(500);
		shotList.push_back(newShot);
		sShot.Play("gunshot.wav");
		sShot.Volume(1.0);
	}

	if (IsKeyDown(SDLK_UP) && IsKeyDown(SDLK_LEFT) && sym == SDLK_SPACE && IsKeyDown(SDLK_RIGHT) == false) //SHOOTING IN DIAGONAL TO THE TOP/LEFT SIDE
	{
		player.SetVelocity(-150, 0);
		player.SetAnimation("diagonalL");
		CSprite* newShot = new CSprite(player.GetX() + 20, player.GetY() + 25, "shot.bmp", CColor::White(), GetTime());
		newShot->SetDirection(-44);
		newShot->SetSpeed(500);
		shotList.push_back(newShot);
		sShot.Play("gunshot.wav");
		sShot.Volume(1.0);
	}
}


void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym != SDLK_SPACE) 
	{
		if (sym == SDLK_LEFT)
		{
			facingLeft = true;
			player.SetSpeed(0);
			player.SetAnimation("standL");
		}
		if (sym == SDLK_RIGHT || sym == SDLK_UP || sym == SDLK_DOWN || sym == SDLK_RCTRL)
		{
			// immobilise the sprite
			player.SetSpeed(0);
			// set the static image as stored in "stand" property
			player.SetImage("stand");  
			if (facingLeft == true) 
			{
				player.SetAnimation("standL");
			}
			if (IsKeyDown(SDLK_RIGHT)) 
			{
				player.SetVelocity(150, 0);
				player.SetAnimation("walk_right");
			}
			if (IsKeyDown(SDLK_LEFT)) 
			{
				player.SetVelocity(-150, 0);
				player.SetAnimation("walk_left");
			}
		}
	}

}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
	
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}