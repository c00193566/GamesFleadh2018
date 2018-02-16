#pragma once
#include <iostream>
#include "Components.h"

/// <struct>MovementSystem</struct>
/// <summary>
/// Movement system will be a struct
/// containing movement update methods
/// for player and ai entities. These
/// methods will be built as static
/// methods so MovementSystem does not need
/// to be initialised.
/// </summary>
/// <author>Jack Keogh</author>

struct MovementSystem
{
	static void ControlledMovement(vector<unique_ptr<Entity>> const &entity, float DT);
};