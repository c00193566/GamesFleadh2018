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
	m_commands["Fire"] = new Fire;
	m_commands["Reload"] = new Reload;
}

Command * CommandComponent::getCommand(string Tag)
{
	return m_commands[Tag];
}

Fire * CommandComponent::getFireCommand()
{
	return static_cast<Fire*>(m_commands["Fire"]);
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

//////////////////////////////////////////////////////////////

void Fire::Execute(TransformComponent * T, PlayerBulletFactory * F, SDL_Texture * Texture, EntityManager * Manager)
{
	Vector2f pos = T->position;
	pos.x += T->width / 2;
	pos.y += T->height / 2;
	F->CreateEntity(Manager, Texture, pos.x, pos.y, 5, 10, T->rotation);
}

//////////////////////////////////////////////////////////////

void Reload::Execute(WeaponComponent * W)
{
	W->setReload(true);
}
