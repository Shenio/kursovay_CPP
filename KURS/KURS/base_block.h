#include <SFML/Graphics.hpp>
#pragma once
class GameContext;

class base_block {
protected:
	bool active = true;
	sf::Vector2f position;
	int health;
public:
	base_block(float x, float y, int hp);
	~base_block() = default;

	virtual void activate(GameContext& context)=0;

	bool isActive() const { return active; }
	void deactivate() { active = false; }

	virtual void draw(sf::RenderWindow& window) const =0;

	virtual sf::FloatRect getBounds() const = 0;


	void setPosition(const sf::Vector2f& pos) { position = pos; }
	sf::Vector2f getPosition() const { return position; }

};