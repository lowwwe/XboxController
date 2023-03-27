#include "Game.h"
#include <iostream>

/// <summary>
/// @author Peter Lowe
/// @date Oct 2017
/// </summary>


/// <summary>
/// constructor cant initialise musch else cause of the lack of a font
/// object
/// </summary>
Game::Game() : 
	m_window(sf::VideoMode(900, 600), "360 Controller Test")
{
}


Game::~Game()
{
}

void	Game::loadContent()
{
	m_controller.connect();
	m_controller2.connect();	
	
	if (!m_font.loadFromFile("c:\\windows\\fonts\\arial.ttf"))
	{
		// error...
		std::cout << "Font failure";
	}	
	if (!m_backgroundTrexture.loadFromFile("ASSETS\\Images\\controller.jpg"))
	{
		std::cout << "problem loading texture";
	}
	m_backgroundSprite.setTexture(m_backgroundTrexture);
	m_backgroundSprite.setPosition(0.0f, 0.0f);
	setupText(m_AbuttonText, 752.0, 426.0, "Pressed");
	setupText(m_BbuttonText, 752.0, 364.0, "Pressed");
	setupText(m_XbuttonText, 752.0, 303.0, "Pressed");
	setupText(m_YbuttonText, 752.0, 243.0, "Pressed");
	setupText(m_LBText, 43.0, 130.0, "Pressed");
	setupText(m_RBText, 694.0, 130.0, "Pressed");
	setupText(m_rightThumbStickText, 516.0, 522.0, "");
	setupText(m_leftThumbStickText, 30.0, 210.0, "");
	setupText(m_dpadLeftRightText, 370.0, 520.0, "");
	setupText(m_dpadUpDownText, 370.0, 540.0, "");
	setupText(m_leftTriggerText, 192.0, 40.0, "");
	setupText(m_rightTriggerText, 560.0, 40.0, "");
	setupText(m_startText, 760.0, 510.0, "Pressed");
	setupText(m_lastFaceButton, 620.0, 190.0, "");
	setupText(m_controllerNo, 306, 120, "No controller connected");
	setupText(m_leftThumbStickClickText, 30, 320, "Left ThumbStick \npressed");
	setupText(m_rightThumbStickClickText, 440, 570, "Right ThumbStick pressed");
}

/// <summary>
/// setup the defaults for a text object
/// </summary>
/// <param name="text">text object to setup</param>
/// <param name="x">location x</param>
/// <param name="y">location y</param>
/// <param name="message">initial string</param>
void Game::setupText(sf::Text & text, float x, float y, std::string message)
{
	text.setFillColor(sf::Color::Black);
	text.setFont(m_font);
	text.setPosition(x, y);
	text.setString(message);
	text.setCharacterSize(20);
}

/// <summary>
/// run our game
/// load the content
/// run the game loop
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 100.f);


	loadContent();

	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

/// <summary>
/// process windows events
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

/// <summary>
/// update the controller and exit game if back from main menu
/// </summary>
/// <param name="time">delta update time</param>
void Game::update(sf::Time time)
{
	if (m_controller.isConnected())
	{
		m_controllerNo.setString("Controller No " + std::to_string(m_controller.sf_Joystick_index));
		m_controller.update();
		if (m_controller.m_currentState.Back && !m_controller.m_previousState.Back)
		{
			m_window.close();
		}
		std::string coodinates;
		coodinates += std::to_string(m_controller.m_currentState.RightThumbStick.x);
		coodinates += "\n";
		coodinates += std::to_string(m_controller.m_currentState.RightThumbStick.y);
		m_rightThumbStickText.setString(coodinates);
		coodinates = std::to_string(m_controller.m_currentState.LeftThumbStick.x);
		coodinates += "\n";
		coodinates += std::to_string(m_controller.m_currentState.LeftThumbStick.y);
		m_leftThumbStickText.setString(coodinates);


		coodinates = std::to_string(m_controller.m_currentState.LTrigger);
		m_leftTriggerText.setString(coodinates);
		coodinates = std::to_string(m_controller.m_currentState.RTrigger);
		m_rightTriggerText.setString(coodinates);
		m_dpadUpDownText.setString("");
		if (m_controller.m_currentState.DpadUp)
		{
			m_dpadUpDownText.setString("up");
		}
		if (m_controller.m_currentState.DpadDown)
		{
			m_dpadUpDownText.setString("Down");
		}
		m_dpadLeftRightText.setString("");
		if (m_controller.m_currentState.DpadLeft)
		{
			m_dpadLeftRightText.setString("Left");
		}
		if (m_controller.m_currentState.DpadRight)
		{
			m_dpadLeftRightText.setString("Right");
		}
		if (m_controller.m_currentState.A && !m_controller.m_previousState.A)
		{
			m_lastFaceButton.setString("Last face button was A");
		}
		if (m_controller.m_currentState.B && !m_controller.m_previousState.B)
		{
			m_lastFaceButton.setString("Last face button was B");
		}
		if (m_controller.m_currentState.X && !m_controller.m_previousState.X)
		{
			m_lastFaceButton.setString("Last face button was X");
		}
		if (m_controller.m_currentState.Y && !m_controller.m_previousState.Y)
		{
			m_lastFaceButton.setString("Last face button was Y");
		}
	}
	else
	{
		if (!m_controller.connect())
		{
			m_controllerNo.setString("No controller connected");
		}
	}
	if (m_controller.m_currentState.LB)
	{
		
		ZeroMemory(&vib, sizeof(XINPUT_VIBRATION));

		vib.wLeftMotorSpeed = static_cast <WORD> (0.2f * 65535.0f);
		vib.wRightMotorSpeed = static_cast <WORD> (0.1f * 65535.0f);

		XInputSetState(0, &vib);
	}
	if (m_controller.m_currentState.RB)
	{
		vib.wLeftMotorSpeed = static_cast <WORD> (0.0f * 65535.0f);
		vib.wRightMotorSpeed = static_cast <WORD> (0.0f * 65535.0f);

		XInputSetState(0, &vib);
	}
}

/// <summary>
/// display the relevant text strings
/// </summary>
void Game::render() 
{
	m_window.clear();
	m_window.draw(m_backgroundSprite);
	if (m_controller.m_currentState.A)
	{
		m_window.draw(m_AbuttonText);
	}
	if (m_controller.m_currentState.B)
	{
		m_window.draw(m_BbuttonText);
	}
	if (m_controller.m_currentState.X)
	{
		m_window.draw(m_XbuttonText);
	}
	if (m_controller.m_currentState.Y)
	{
		m_window.draw(m_YbuttonText);
	}
	if (m_controller.m_currentState.LB)
	{
		m_window.draw(m_LBText);
	}
	if (m_controller.m_currentState.RB)
	{
		m_window.draw(m_RBText);
	}
	int threshold = 15;
	if (m_controller.m_currentState.RightThumbStick.x > threshold || m_controller.m_currentState.RightThumbStick.y > threshold
		|| m_controller.m_currentState.RightThumbStick.x < -threshold || m_controller.m_currentState.RightThumbStick.y < -threshold)
	{
		m_window.draw(m_rightThumbStickText);
	}
	if (m_controller.m_currentState.LeftThumbStick.x > threshold || m_controller.m_currentState.LeftThumbStick.y > threshold
		|| m_controller.m_currentState.LeftThumbStick.x < -threshold || m_controller.m_currentState.LeftThumbStick.y < -threshold)
	{
		m_window.draw(m_leftThumbStickText);
	}
	m_window.draw(m_dpadUpDownText);
	m_window.draw(m_dpadLeftRightText);
	if (m_controller.m_currentState.LTrigger > 1)
	{
		m_window.draw(m_leftTriggerText);
	}
	if (m_controller.m_currentState.RTrigger > 1)
	{
		m_window.draw(m_rightTriggerText);
	}
	if (m_controller.m_currentState.Start)
	{
		m_window.draw(m_startText);
	}
	if (m_controller.m_currentState.LeftThumbStickClick)
	{
		m_window.draw(m_leftThumbStickClickText);
	}
	if (m_controller.m_currentState.RightThumbStickClick)
	{
		m_window.draw(m_rightThumbStickClickText);
	}
	m_window.draw(m_controllerNo);
	m_window.draw(m_lastFaceButton);
	m_window.display();
}