#pragma once
#include "InputManager.h"
#include "Agent.h"
#include <vector>

class DragAndDrop
{
private:
	InputManager* inputManager;
	std::vector<Agent*> agents;
	Agent* selectedAgent = nullptr;
	bool clicked = false;
public:
	void addAgent(Agent* _agent);
	bool colitionWithAgent(Agent* _agent);
	void verify();
	void update();
	DragAndDrop(InputManager* _inputManager);
	~DragAndDrop();
};

