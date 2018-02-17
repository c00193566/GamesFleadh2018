#include "InputSystem.h"

InputSystem::InputSystem()
{
	m_asset = AssetHandler::Instance();
	up = down = left = right = false;
	MouseX = 0;
	MouseY = 0;
}

void InputSystem::KeyPressed(SDL_Event e, vector<Entity*> &entity)
{
	if (e.type == SDL_KEYDOWN)
	{
		for (int i = 0; i < entity.size(); i++)
		{
			auto& ent = entity.at(i);
			if (e.key.keysym.sym == ent->getComponent<KeyComponent>().Up())
			{
				up = true;
			}

			if (e.key.keysym.sym == ent->getComponent<KeyComponent>().Down())
			{
				down = true;
			}

			if (e.key.keysym.sym == ent->getComponent<KeyComponent>().Left())
			{
				left = true;
			}

			if (e.key.keysym.sym == ent->getComponent<KeyComponent>().Right())
			{
				right = true;
			}
		}
	}
}

void InputSystem::KeyReleased(SDL_Event e, vector<Entity*> &entity)
{
	if (e.type == SDL_KEYUP)
	{
		for (int i = 0; i < entity.size(); i++)
		{
			auto& ent = entity.at(i);

			if (e.key.keysym.sym == ent->getComponent<KeyComponent>().Up())
			{
				up = false;
			}

			if (e.key.keysym.sym == ent->getComponent<KeyComponent>().Down())
			{
				down = false;
			}

			if (e.key.keysym.sym == ent->getComponent<KeyComponent>().Left())
			{
				left = false;
			}

			if (e.key.keysym.sym == ent->getComponent<KeyComponent>().Right())
			{
				right = false;
			}
		}
	}
}

void InputSystem::MouseButton(SDL_Event e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			fire = true;
		}
	}

	if (e.type == SDL_MOUSEBUTTONUP)
	{
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			fire = false;
		}
	}
}

void InputSystem::MouseMove(SDL_Event e)
{
	if (e.type == SDL_MOUSEMOTION)
	{
		SDL_GetMouseState(&MouseX, &MouseY);
	}
}

void InputSystem::Update(EntityManager * Manager, vector<Entity*> &entity, PlayerBulletFactory * BulletFactory)
{
	for (int i = 0; i < entity.size(); i++)
	{
		auto& ent = entity.at(i);

		// Commands for relative inputs
		if (up)
		{
			ent->getComponent<CommandComponent>().getCommand("Up")->Execute(&ent->getComponent<TransformComponent>());
		}

		if (down)
		{
			ent->getComponent<CommandComponent>().getCommand("Down")->Execute(&ent->getComponent<TransformComponent>());
		}

		if (left)
		{
			ent->getComponent<CommandComponent>().getCommand("Left")->Execute(&ent->getComponent<TransformComponent>());
		}

		if (right)
		{
			ent->getComponent<CommandComponent>().getCommand("Right")->Execute(&ent->getComponent<TransformComponent>());
		}

		// Rotation
		float rot = ent->getComponent<TransformComponent>().rotation;

		Vector2f RotVec = Vector2f(MouseX - (ent->getComponent<TransformComponent>().position.x + ent->getComponent<TransformComponent>().width / 2),
			MouseY - (ent->getComponent<TransformComponent>().position.y + ent->getComponent<TransformComponent>().height / 2));

		rot = atan2f(RotVec.x, -RotVec.y);

		rot = (rot * 180) / 3.14;

		ent->getComponent<TransformComponent>().rotation = rot;

		// Fire
		if (fire)
		{
			ent->getComponent<CommandComponent>().getFireCommand()->Execute(&ent->getComponent<TransformComponent>(),
				BulletFactory, m_asset->getTexture("RedBullet"), Manager);
		}
	}
}
