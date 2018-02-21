#include "AISystem.h"

void AISystem::FindTarget(vector<Entity*> AI, vector<Entity*> Targets)
{
	for (Entity * e : AI)
	{
		e->getComponent<AIComponent>().findTarget(Targets);
	}
}

void AISystem::FindTarget(Entity * AI, vector<Entity*> Targets)
{
	AI->getComponent<AIComponent>().findTarget(Targets);
}

void AISystem::Seek(Entity * e, Vector2f Target)
{
	Vector2f position = e->getComponent<TransformComponent>().getPosition();

	if (Target.x < position.x - 4)
	{
		e->getComponent<CommandComponent>().getCommand("Left")->Execute(&e->getComponent<TransformComponent>());
	}
	else if (Target.x > position.x + 4)
	{
		e->getComponent<CommandComponent>().getCommand("Right")->Execute(&e->getComponent<TransformComponent>());
	}

	if (Target.y < position.y - 4)
	{
		e->getComponent<CommandComponent>().getCommand("Up")->Execute(&e->getComponent<TransformComponent>());
	}
	else if (Target.y > position.y + 4)
	{
		e->getComponent<CommandComponent>().getCommand("Down")->Execute(&e->getComponent<TransformComponent>());
	}

	if (position.x + 4 >= Target.x && position.x - 4 <= Target.x + 6)
	{
		if (position.y + 4 >= Target.y && position.y - 4 <= Target.y + 6)
		{
			e->getComponent<AIComponent>().setAtTarget(true);
		}
	}
}

AISystem::AISystem(int Level)
{
	m_pathfinder = new PathFinder(GameData::m_roomLayout.at(Level));
	m_pathfinder->AddLinks();

	m_timer = 0.0f;
	m_startTime = 12.0f;
}

void AISystem::Update(vector<Entity*> AI, vector<Entity*> Targets)
{
	// Call find target every 20 seconds.
	m_timer -= 1.0f / 60.0f;

	if (m_timer <= 0.0f)
	{
		m_timer = m_startTime;
		FindTarget(AI, Targets);
	}

	for (Entity * e : AI)
	{
		if (e->getComponent<AIComponent>().getType() == AITypes::Melee)
		{
			if (e->getComponent<AIComponent>().getAtTarget())
			{
				e->getComponent<AIComponent>().setAtTarget(false);
				FindTarget(e, Targets);
			}
			MeleeUpdate(e);
		}
	}
}

void AISystem::MeleeUpdate(Entity * e)
{
	Vector2f position = e->getComponent<TransformComponent>().getPosition();
	Vector2f target = e->getComponent<AIComponent>().getTarget();

	if (e->getComponent<AIComponent>().getPath().empty() || m_pathfinder->GetNearestCell(position) != m_pathfinder->GetNearestCell(e->getComponent<AIComponent>().getPath().back()))
	{
		e->getComponent<AIComponent>().setPath(m_pathfinder->AStar(m_pathfinder->GetNearestCell(position),
			m_pathfinder->GetNearestCell(target)));
	}
	
	if (e->getComponent<AIComponent>().getPath().size() > 2)
	{
		Vector2f cell = e->getComponent<AIComponent>().getPath()[e->getComponent<AIComponent>().getPath().size() - 2];
		cell.x -= CELL_WIDTH / 4;
		cell.y -= CELL_HEIGHT / 4;
		Seek(e, cell);
	}
	else
	{
		Seek(e, target);
	}
}
