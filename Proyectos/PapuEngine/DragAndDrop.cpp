#include "DragAndDrop.h"


void DragAndDrop::addAgent(Agent * _agent)
{
	agents.push_back(_agent);
}

bool DragAndDrop::colitionWithAgent(Agent * _agent)
{
	glm::vec2 _position = inputManager->getMouseCoords();
	bool result = (_position.x > _agent->getPosition().x)
		&& (_position.x < _agent->getPosition().x + _agent->getHeight())
		&& (500 - _position.y > _agent->getPosition().y)
		&& (500 - _position.y < _agent->getPosition().y + _agent->getWidth());
	return result;
}

void DragAndDrop::verify()
{
	if (clicked)
	{
		selectedAgent = nullptr;
		clicked = false;
	}
	else
	{
		for (size_t i = 0; i < agents.size(); i++)
		{
			if (colitionWithAgent(agents[i]))
			{
				clicked = true;
				selectedAgent = agents[i];
				return;
			}
		}
	}
}

void DragAndDrop::update()
{
	if (clicked)
		selectedAgent->setPosition(glm::vec2(inputManager->getMouseCoords().x, 500 - inputManager->getMouseCoords().y) - glm::vec2(selectedAgent->getHeight()/2,selectedAgent->getWidth()/2));

	return;
}

DragAndDrop::DragAndDrop(InputManager * _inputManager): inputManager(_inputManager)
{
}

DragAndDrop::~DragAndDrop()
{
}
