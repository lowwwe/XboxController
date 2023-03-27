#include "Xbox360Controller.h"
#include <iostream>

/// <summary>
/// @author Peter Lowe
/// @date Oct 2017
/// </summary>


// initialise the number of controller to zero
int Xbox360Controller::s_noOfControllers = 0;

/// <summary>
/// set the privious values to the cuirrent and then set
/// the current values to the live data from the controller
/// </summary>
void Xbox360Controller::update()
{
	m_previousState = m_currentState;
	DWORD result = XInputGetState(0, &state);
	if (isConnected())
	{

		m_currentState.A = sf::Joystick::isButtonPressed(sf_Joystick_index, 0);
		m_currentState.A = ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) == XINPUT_GAMEPAD_A);
		m_currentState.B = sf::Joystick::isButtonPressed(sf_Joystick_index, 1);
		m_currentState.X = sf::Joystick::isButtonPressed(sf_Joystick_index, 2);
		m_currentState.Y = sf::Joystick::isButtonPressed(sf_Joystick_index, 3);
		m_currentState.LB = sf::Joystick::isButtonPressed(sf_Joystick_index, 4);
		m_currentState.RB = sf::Joystick::isButtonPressed(sf_Joystick_index, 5);
		m_currentState.Back = sf::Joystick::isButtonPressed(sf_Joystick_index, 6);
		m_currentState.Start = sf::Joystick::isButtonPressed(sf_Joystick_index, 7);

		m_currentState.LeftThumbStickClick = sf::Joystick::isButtonPressed(sf_Joystick_index, 8);
		m_currentState.RightThumbStickClick = sf::Joystick::isButtonPressed(sf_Joystick_index, 9);

		m_currentState.Xbox = sf::Joystick::isButtonPressed(sf_Joystick_index, 10);
		m_currentState.DpadRight = (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovX) > dpadThreshold) ? true : false;
		m_currentState.DpadLeft = (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovX) < -dpadThreshold) ? true : false;
		m_currentState.DpadUp = (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovY) > dpadThreshold) ? true : false;
		m_currentState.DpadDown = (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovY) < -dpadThreshold) ? true : false;

		m_currentState.LTrigger = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Z);
		m_currentState.RTrigger = -sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Z);
		m_currentState.LTrigger = state.Gamepad.bLeftTrigger / 2.55f;
		m_currentState.RTrigger = state.Gamepad.bRightTrigger / 2.55f;
		m_currentState.LeftThumbStick = sf::Vector2f(sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::X),
			sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Y));
		m_currentState.RightThumbStick = sf::Vector2f(sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::U),
			sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::R));
	}
}

/// <summary>
/// constructor find the first available controller
/// and set the index to be the controller number
/// </summary>
Xbox360Controller::Xbox360Controller()
{	
}



/// <summary>
/// check if the controller is connected
/// </summary>
/// <returns>true is controller is still detected by system</returns>
bool Xbox360Controller::isConnected()
{
	if (sf_Joystick_index < 0 || sf_Joystick_index > sf::Joystick::Count)
		return false;
	else
		return sf::Joystick::isConnected(sf_Joystick_index);
}


// try each controller slot starting wiht the number of already connected controllers 
// until we find one assumes sequential controllers
bool Xbox360Controller::connect()
{
	for (int j = s_noOfControllers; j < sf::Joystick::Count; j++)
	{
		if (sf::Joystick::isConnected(j))
		{
			sf_Joystick_index = j;
			s_noOfControllers++;
#ifdef _DEBUG
			std::cout << "connected controller id:" << j ;
			sf::Joystick::Identification id = sf::Joystick::getIdentification(0);
			std::cout << "\nVendor ID: " << id.vendorId << "\nProduct ID: " << id.productId << std::endl;
#endif // _DEBUG
			return true;
		}
	}
	return false;
}

/// <summary>
/// empty destructor
/// </summary>
Xbox360Controller::~Xbox360Controller()
{
}
