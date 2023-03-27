#ifndef GAME
#define GAME

/// <summary>
/// @author Peter Lowe
/// @date Oct 2017
/// </summary>


#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include "Xbox360Controller.h"

class Game
{
public:
	Game();
	~Game();
	void run();
private:

	void	processEvents();
	void    update(sf::Time);
	void    render();
	void	loadContent();
	void	setupText(sf::Text& text, float x, float y, std::string message);
	


	XINPUT_VIBRATION vib;
	// sfml window for drawing
	sf::RenderWindow m_window;
	// font used in the game
	sf::Font m_font;
	// background Texture 
	sf::Texture m_backgroundTrexture;
	// background sprite
	sf::Sprite m_backgroundSprite;
	// 360 controller
	Xbox360Controller m_controller;
	//second controller
	Xbox360Controller m_controller2;
	
	// A button Text
	sf::Text m_AbuttonText;
	// B button Text
	sf::Text m_BbuttonText;
	// X button Text
	sf::Text m_XbuttonText;
	// Y button Text
	sf::Text m_YbuttonText;
	// right bum,per text
	sf::Text m_RBText;
	// left bumper text
	sf::Text m_LBText;
	// rightThumbStick
	sf::Text m_rightThumbStickText;
	// left thumbstick
	sf::Text m_leftThumbStickText;
	// dpad up/down
	sf::Text m_dpadUpDownText;
	// dpad right left
	sf::Text m_dpadLeftRightText;
	// right trigger
	sf::Text m_rightTriggerText;
	// left trigger
	sf::Text m_leftTriggerText;
	// start
	sf::Text m_startText;
	// last face button
	sf::Text m_lastFaceButton;
	// text for controller number
	sf::Text m_controllerNo;
	// tect for left thumbstick button
	sf::Text m_leftThumbStickClickText;
	// tect for right thumbstick button
	sf::Text m_rightThumbStickClickText;

};

#endif // !GAME


//end
