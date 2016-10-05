#include <SFML/Graphics.hpp>
#include "TransformNode.h"

int main(int argc, char* argv)
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Purple");
	sf::CircleShape head(5.0f, 30);
	sf::RectangleShape body(sf::Vector2<float>(15.0f, 25.0f));
	sf::RectangleShape neck(sf::Vector2<float>(3.0f, 7.5f));
	
	sf::RectangleShape lowerArmRect1(sf::Vector2<float>(15.0f, 5.0f));
	sf::RectangleShape upperArmRect1(sf::Vector2<float>(15.0f, 5.0f));
	sf::RectangleShape lowerArmRect2(sf::Vector2<float>(15.0f, 5.0f));
	sf::RectangleShape upperArmRect2(sf::Vector2<float>(15.0f, 5.0f));

	body.setFillColor(sf::Color::Green);
	neck.setFillColor(sf::Color::Magenta);
	head.setFillColor(sf::Color::Yellow);
	lowerArmRect1.setFillColor(sf::Color::Blue);
	upperArmRect1.setFillColor(sf::Color::Red);
	lowerArmRect2.setFillColor(sf::Color::Blue);
	upperArmRect2.setFillColor(sf::Color::Red);

	bool keyHeld = false;

	bool growing = true;
	float scaleFactor = 1.001;

	float growthFactor = 1.001f;
	float shrinkFactor = 0.999f;

	//body.setOrigin(10, 10);
	body.setOrigin((body.getLocalBounds().width  / 2), 0.0f);
	body.setPosition(300, 300);
	body.setScale(4, 4);

	sf::Vector2<float> armPosition((body.getLocalBounds().width / 1.1f), (body.getLocalBounds().height / 7.5f));
	sf::Vector2<float> armPosition2((body.getLocalBounds().width / 10.0f), (body.getLocalBounds().height / 7.5f));
	sf::Vector2<float> neckPosition((body.getLocalBounds().width / 2.5f), (body.getLocalBounds().height)/ 5.0f);
	/*sf::Vector2<float> headPosition((15.0), (neck.getLocalBounds().height * 2));*/

	sf::Vector2<float> armOrigin(0.0f, 2.5f);
	sf::Vector2<float> armOrigin2(15.0, 2.5f);
	sf::Vector2<float> neckOrigin(0.0f, 10.0f);


	upperArmRect1.setOrigin(armOrigin);
	lowerArmRect1.setOrigin(armOrigin);
	upperArmRect2.setOrigin(armOrigin2);
	lowerArmRect2.setOrigin(armOrigin2);
	neck.setOrigin(neckOrigin);
	head.setOrigin((0.0), (neck.getLocalBounds().height / 5.0f));

	lowerArmRect1.setPosition(15.0f, 2.5f);
	upperArmRect1.setPosition(armPosition);
	lowerArmRect2.setPosition(0.0f, 2.5f);
	upperArmRect2.setPosition(armPosition2);
	neck.setPosition(neckPosition);
	head.setPosition((head.getLocalBounds().width / -3.0f),-5.0);

	TransformNode bodyTrans(&body);
	TransformNode neckTrans(&neck);
	TransformNode headTrans(&head);
	TransformNode upperArm(&upperArmRect1);
	TransformNode lowerArm(&lowerArmRect1);
	TransformNode upperArm2(&upperArmRect2);
	TransformNode lowerArm2(&lowerArmRect2);

	upperArm.AddChild(&lowerArm);
	neckTrans.AddChild(&headTrans);
	bodyTrans.AddChild(&upperArm);
	bodyTrans.AddChild(&neckTrans);
	upperArm2.AddChild(&lowerArm2);
	bodyTrans.AddChild(&upperArm2);

	sf::Clock deltaTime;
	while (window.isOpen())
	{
		float elaspedTime = deltaTime.restart().asSeconds();

		sf::Transform transform = body.getTransform();

		/*body.scale(scaleFactor, scaleFactor);
		float currentScale = body.getScale().x;
		if (currentScale >= 4.0f) {
		scaleFactor = shrinkFactor;
		}
		else if (currentScale <= 1.0f)
		{
		scaleFactor = growthFactor;
		}*/

		sf::Event sfEvent;
		while (window.pollEvent(sfEvent))
		{
			if (sfEvent.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (sfEvent.type == sf::Event::KeyReleased)
			{
				keyHeld = false;
			}
			else if (sfEvent.type == sf::Event::KeyPressed)
			{
				keyHeld = true;
			}
		}

		if (keyHeld)
		{
			float angleAmount = 100.0f;
			float angleAmount2 = -100.0f;
			lowerArmRect1.rotate(angleAmount * elaspedTime);
			upperArmRect1.rotate(angleAmount * elaspedTime);
			lowerArmRect2.rotate(angleAmount2 * elaspedTime);
			upperArmRect2.rotate(angleAmount2 * elaspedTime);
			neck.rotate(angleAmount * elaspedTime);
			body.rotate(angleAmount * elaspedTime);
		}

		window.clear(); // draw fullscreen graphic

		/*sf::Transform hierarchy = sf::Transform::Identity;

		window.draw(body);
		hierarchy = hierarchy * body.getTransform();

		window.draw(lowerArmRect1, hierarchy); // DRAWING with the body's transform.
		hierarchy = hierarchy * lowerArmRect1.getTransform();

		window.draw(upperArmRect1, hierarchy); // DRAWING*/

		bodyTrans.Draw(&window);

		window.display();
	}

	return 0;
}