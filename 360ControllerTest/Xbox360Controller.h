#ifndef XBOX360CONTROLLER
#define XBOX360CONTROLLER

/// <summary>
/// @author Peter Lowe
/// @date Oct 2017
/// </summary>

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <Xinput.h>


enum class  ButtonMask{
	DPAD_UP = 0x0001,
	DPAD_DOWN = 0x0002,
	DPAD_LEFT = 0x0004,
	DPAD_RIGHT = 0x0008,
	START = 0x0010,
	BACK = 0x0020,
	LEFT_THUMB = 0x0040,
	RIGHT_THUMB = 0x0080,
	LB = 0x0100,
	RB = 0x0200,
	A = 0x1000,
	B = 0x2000,
	X = 0x4000,
	Y = 0x8000,
};
inline ButtonMask operator &(WORD a, ButtonMask b)
{
	return static_cast<ButtonMask>(static_cast<int>(a) & static_cast<int>(b));
}
/// <summary>
/// data to store the current state of the controller
/// </summary>
struct GamePadState
{
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;
	bool LeftThumbStickClick;
	bool RightThumbStickClick;
	bool DpadUp;
	bool DpadDown;
	bool DpadLeft;
	bool DpadRight;
	bool Start;
	bool Back;
	bool Xbox;
	float RTrigger;
	float LTrigger;
	sf::Vector2f RightThumbStick;
	sf::Vector2f LeftThumbStick;
};

/// <summary>
/// Xbox controiller class to query current state of controller
/// to mimic the controller states like XNA
/// </summary>
class Xbox360Controller
{
private: 
	// deadzone for the dpad (really a joystick)
	const int dpadThreshold = 50;
	
public:
	// newly added for multiple controller support not required in your project
	// number of connected controllers
	static int s_noOfControllers;
	// index count for multiple controllers if connected
	int sf_Joystick_index;
	// the current state of all the buttons
	GamePadState m_currentState;
	// the previous state to use to check for the moment a button is pressed
	GamePadState m_previousState;

	XINPUT_STATE state;
	

	Xbox360Controller();	
	~Xbox360Controller();
	void Xbox360Controller::update();
	bool isConnected();
	bool connect();	
};

#endif // !XBOX360CONTROLLER


