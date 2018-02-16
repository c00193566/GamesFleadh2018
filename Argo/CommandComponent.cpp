#include "CommandComponent.h"

CommandComponent::CommandComponent()
{

}

void CommandComponent::Init()
{
	m_commands["Left"] = new MoveLeft;
	m_commands["Right"] = new MoveRight;
	m_commands["Up"] = new MoveUp;
	m_commands["Down"] = new MoveDown;
}

Command * CommandComponent::getCommand(string Tag)
{
	return m_commands[Tag];
}

//////////////////////////////////////////////////////////////

void MoveRight::Execute(TransformComponent * T)
{
	if (T->acceleration.x < T->MaxAccel)
	{
		T->acceleration.x += 0.2f;
	}
}

//////////////////////////////////////////////////////////////

void MoveLeft::Execute(TransformComponent * T)
{
	if (T->acceleration.x > -T->MaxAccel)
	{
		T->acceleration.x -= 0.2f;
	}
}

//////////////////////////////////////////////////////////////

void MoveUp::Execute(TransformComponent * T)
{
	if (T->acceleration.y > -T->MaxAccel)
	{
		T->acceleration.y -= 0.2f;
	}
}

//////////////////////////////////////////////////////////////

void MoveDown::Execute(TransformComponent * T)
{
	if (T->acceleration.y < T->MaxAccel)
	{
		T->acceleration.y += 0.2f;
	}
}
