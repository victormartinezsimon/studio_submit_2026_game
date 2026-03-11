#pragma once
#include <functional>
#include <utility>

class InputManager;

class ButtonA
{

public:
	ButtonA(InputManager* inputManager);

public:
	void Update(const float deltaTime);
private:
	void UpdateSelectInPosition(const float deltaTime);
	void UpdateSelectAfterTime(const float deltaTime);

public:
	void SelectInPosition(float duration, std::pair<int, int> marginA, std::pair<int, int> marginB, std::function<void(int)> callback);
	void SelectAfterTime(float duration, std::function<void(int)> callback);

private:
	InputManager* _inputManager;
	bool _enabled = false;
	bool _isSelectInPosition = false;
	float _duration;
	std::pair<int, int> _marginA;
	std::pair<int, int> _marginB;
	std::function<void(int)> _callback;
	float _acumTime;
};