#pragma once
#include <iostream>
#include "Components.h"
#include "PathFinding.h"
#include "GameData.h"

/// <class>AI System</class>
/// <summary>
/// This class will be used to deal
/// with the updating of NPCs.
/// </summary>
/// <author>Jack Keogh</author>

class AISystem
{
private:
	PathFinder * m_pathfinder;

	float m_timer;
	float m_startTime;

	/// <summary>
	/// Used to find the target for the AI.
	/// </summary>
	/// <param name="AI">vector Entity ptr of NPCs.</param>
	/// <param name="Targets">vector Entity of PCs.</param>
	void FindTarget(vector<Entity*> AI, vector<Entity*> Targets);

	/// <summary>
	/// Alternate find target method.
	/// </summary>
	/// <param name="AI">A single entity ptr.</param>
	/// <param name="Targets">vector entity of PCs.</param>
	void FindTarget(Entity * AI, vector<Entity*> Targets);

	/// <summary>
	/// Updates the entity to seek the target.
	/// </summary>
	/// <param name="e"></param>
	/// <param name="Target"></param>
	void Seek(Entity * e, Vector2f Target);

public:
	/// <summary>
	/// Default constructor with an overload parameter available
	/// </summary>
	/// <param name="Level"></param>
	AISystem(int Level = 0);

	/// <summary>
	/// Will update the relative functions for the npcs.
	/// </summary>
	/// <param name="entities">vector of entity ptrs.</param>
	void Update(vector<Entity*> AI, vector<Entity*> Targets);

	/// <summary>
	/// Update function for AI of type melee
	/// </summary>
	/// <param name="e">Entity ptr to melee entity.</param>
	void MeleeUpdate(Entity * e);
};