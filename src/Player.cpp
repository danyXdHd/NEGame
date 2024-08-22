#include <Player.hpp>

void Player::Start() {
	hp = 10;
	width = 60;
	height = 60;
	x = 0;
	y = 0;
	speed = 64 * 5;
	maxBullets = 20;
	delayBullet = 0;

	Gun.Start();

	LoadTextures();
}

void Player::Update(sf::RenderWindow& Window, sf::View &View, 
					int width, int height, float dTime, 
					std::vector<Wall>& Walls, std::vector<Enemy> &Enemys) {
	// Handle player movement
	
	HandleMovement(Walls, dTime);

	// Handle gun rotation
	HandleGun(Window);

	// Draw player
	Window.draw(sprite);
	Window.draw(Gun.sprite);
	View.setCenter(sf::Vector2f(x + Player::width/2, y + Player::height/2));
	Window.setView(View);

	// Handle bullets
	HandleBullets(Window, width, height, dTime, Walls);
	HandleDamage(Enemys);
}

void Player::LoadTextures() {
	if (!texture.loadFromFile("Assets\\Images\\RedBox.png"))
	{
		std::cout << "Player texture not rendered";
	}
	if (!gunTexture.loadFromFile("Assets\\Images\\Gun.png"))
	{
		std::cout << "Player`s gun texture not rendered";
	}
	if (!bulletTexture.loadFromFile("Assets\\Images\\Bullet.png"))
	{
		std::cout << "Bullet texture not rendered";
	}

	sprite.setTexture(texture);
	sprite.setScale(0.5, 0.5);
	Gun.sprite.setTexture(gunTexture);

	Gun.sprite.setOrigin(sf::Vector2f(width / 4, width / 4));
}

void Player::HandleMovement(std::vector<Wall>& Walls, float dTime) {
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		x -= speed * dTime;
		for (int i = 0; i < Walls.size(); i++) {
			if (Walls[i].isColiding(x, y, width, height)) {
				// Atingem peretele, ajustăm poziția
				x = Walls[i].x * Walls[i].TextureWidth + Walls[i].width * Walls[i].TextureWidth;
				break;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		x += speed * dTime;
		for (int i = 0; i < Walls.size(); i++) {
			if (Walls[i].isColiding(x, y, width, height)) {
				// Atingem peretele, ajustăm poziția
				x = Walls[i].x * Walls[i].TextureWidth - width;
				break;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		y -= speed * dTime;
		for (int i = 0; i < Walls.size(); i++) {
			if (Walls[i].isColiding(x, y, width, height)) {
				// Atingem peretele, ajustăm poziția
				y = Walls[i].y * Walls[i].TextureHeight + Walls[i].height * Walls[i].TextureHeight;
				break;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		y += speed * dTime;
		for (int i = 0; i < Walls.size(); i++) {
			if (Walls[i].isColiding(x, y, width, height)) {
				// Atingem peretele, ajustăm poziția
				y = Walls[i].y * Walls[i].TextureHeight - height;
				break;
			}
		}
	}

	// Actualizăm poziția jucătorului
	sprite.setPosition(x, y);
}

void Player::HandleGun(sf::RenderWindow& Window) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(Window);
	sf::Vector2f worldPos = Window.mapPixelToCoords(mousePos);

	Gun.HandleAngle(x, y, width, height, angleWithXAxis(
		x + width / 2, y + width / 2, worldPos.x, worldPos.y));
}

void Player::HandleDamage(std::vector<Enemy> &Enemys)
{
	for (int j = 0; j < Enemys.size(); j++) {
		// Colision between player`s bullets and the enemys
		for (int i = 0; i < Bullets.size(); i++) {
			if (Bullets[i].isColiding(Enemys[j].x, Enemys[j].y, 
				Enemys[j].width, Enemys[j].height) && 
				Enemys[j].iFrame <= 0)
			{
				Enemys[j].iFrame = Enemys[j].maxIFrame;
				Enemys[j].hp -= Bullets[i].damage;
				if (Enemys[j].hp <= 0) {
					Enemys.erase(Enemys.begin() + j);
				}
				Bullets[i].pierce--;
				if (Bullets[i].pierce <= 0) {
					Bullets.erase(Bullets.begin() + i);
				}
			}
		}
		// Colision between enemy`s bullets and the player
	}
}

void Player::HandleBullets(sf::RenderWindow& Window, int width, int height, float dTime, std::vector<Wall>& Walls)
{
	if(Bullets.size() < maxBullets && delayBullet <= 0)
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			Gun.Shoot(Bullets , bulletTexture, Gun.sprite.getPosition().x,
				Gun.sprite.getPosition().y, Gun.sprite.getRotation());

			delayBullet = Gun.maxDelayBullet;
		}
	if (delayBullet > 0)
		delayBullet -= dTime;
	
	for (int i = 0; i < Bullets.size(); i++) {
		Window.draw(Bullets[i].sprite);
		if (Bullets[i].Update(x, y, width, height, dTime, Walls))
			Bullets.erase(Bullets.begin() + i);
	}
}

