#include <Player.hpp>

void Player::Start() {
	width = 60;
	height = 60;
	x = 0;
	y = 0;
	speed = 64 * 5;
	gunAngle = 0;
	maxBullets = 20;
	delayBullet = 0;
	maxDelayBullet = .2;

	
	LoadTextures();
}

void Player::Update(sf::RenderWindow& Window, sf::View View, 
					int width, int height, float dTime, 
					std::vector<Wall>& Walls) {
	// Handle player movement
	
	HandleMovement(Walls, dTime);

	// Handle gun rotation
	HandleGun(Window);

	// Draw player
	Window.draw(sprite);
	Window.draw(gunSprite);
	View.setCenter(sf::Vector2f(x + Player::width/2, y + Player::height/2));
	Window.setView(View);

	// Handle bullets
	HandleBullets(Window, width, height, dTime, Walls);

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
	gunSprite.setTexture(gunTexture);

	gunSprite.setOrigin(sf::Vector2f(width / 4, width / 4));
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

	gunAngle = angleWithXAxis(x + width / 2, y + width / 2, worldPos.x, worldPos.y);

	if (gunAngle > 90 && gunAngle < 270)
		gunSprite.setScale(1.f, -1.f);
	else
		gunSprite.setScale(1.f, 1.f);

	gunSprite.setRotation(gunAngle);
	std::pair<double, double> newPos = calculatePointInDirection(x + width / 2, y + width / 2, gunAngle, width / 2);
	gunSprite.setPosition(newPos.first, newPos.second);
}

void Player::HandleBullets(sf::RenderWindow& Window, int width, int height, float dTime, std::vector<Wall>& Walls)
{
	if(Bullets.size() < maxBullets && delayBullet <= 0)
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			Bullet newBullet(gunSprite.getPosition().x, gunSprite.getPosition().y,
							 gunSprite.getRotation());

			Player::Bullets.push_back(newBullet);
			int i = Bullets.size() - 1;
			//Bullets[i].sprite.setOrigin(sf::Vector2f(Bullets[i].width/2, Bullets[i].height/2));
			Bullets[i].sprite.setRotation(gunSprite.getRotation());
			Bullets[i].sprite.setTexture(bulletTexture);
			Bullets[i].sprite.setPosition(Bullets[i].x, Bullets[i].y);

			delayBullet = maxDelayBullet;
		}
	if (delayBullet > 0)
		delayBullet -= dTime;
	
	for (int i = 0; i < Bullets.size(); i++) {
		Window.draw(Bullets[i].sprite);
		if (Bullets[i].Update(x, y, width, height, dTime, Walls))
			Bullets.erase(Bullets.begin() + i);
	}
}

