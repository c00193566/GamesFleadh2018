#pragma once
#include <map>
#include <SDL.h>
#include "ECS.h"
#include "TransformComponent.h"
#include "Factory.h"

///<class>CommandComponent</class>
/// <summary>
/// This component will be used as a command
/// pattern. It will handle if the user is 
/// using a joypad or keyboard and set the
/// key codes accordingly.
/// </summary>
/// <author>Jack Keogh</author>

class PlayerBulletFactory;
class Fire;

class Command
{
public:
	virtual ~Command() {};
	virtual void Execute(TransformComponent * T) {};

protected:
	Command() {};
};

class CommandComponent : public Component
{
private:
	map<string, Command *> m_commands;

public:
	/// <summary>
	/// Default constructor for the command component.
	/// </summary>
	CommandComponent();

	/// <summary>
	/// Override initaliser for command component.
	/// </summary>
	void Init() override;

	/// <summary>
	/// This method is used to get the command to execute.
	/// </summary>
	/// <param name="Tag">string defining the command to return.</param>
	/// <returns>A command.</returns>
	Command * getCommand(string Tag);
	Fire * getFireCommand();
};

class MoveRight : public Command
{
public:
	void Execute(TransformComponent * T) override;
};

class MoveLeft : public Command
{
public:
	void Execute(TransformComponent * T) override;
};

class MoveUp : public Command
{
public:
	void Execute(TransformComponent * T) override;
};

class MoveDown : public Command
{
public:
	void Execute(TransformComponent * T) override;
};

class Fire : public Command
{
public:
	void Execute(TransformComponent * T, PlayerBulletFactory * F, SDL_Texture * Texture, EntityManager * Manager);
};