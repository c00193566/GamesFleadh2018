#pragma once
#include <iostream>
#include "Components.h"

/// <struct>Collision</struct>
/// <summary>
/// Collision struct will contain a series
/// of static methods for different types
/// of collisions. 
/// </summary>
/// <author>Jack Keogh</author>

struct Collision
{
	/// <summary>
	/// Checks collision between characters and the walls.
	/// </summary>
	/// <param name="characters">vector ptr of entity defining the characters to check.</param>
	/// <param name="walls">vector ptr of entity defining the walls.</param>
	static void BounceCollision(vector<Entity*> characters, vector<Entity*> other);

	/// <summary>
	/// Checks collision between bullets and walls.
	/// </summary>
	/// <param name="bullets">vector ptr of entity defining the bullets.</param>
	/// <param name="others">vector ptr of entity defining walls to collide with.</param>
	static void BulletWallCollision(vector<Entity*> bullets, vector<Entity*> walls);

	/// <summary>
	/// Checks collision between bullets and other entities.
	/// </summary>
	/// <param name="bullets"></param>
	/// <param name="entities"></param>
	static void BulletEntityCollision(vector<Entity*> bullets, vector<Entity*> entities);

	/// <summary>
	/// Simple box collision method.
	/// </summary>
	/// <param name="obj1">SDL_Rect of object 1.</param>
	/// <param name="obj2">SDL_Rect of object 2.</param>
	/// <returns></returns>
	static bool AABB(SDL_Rect obj1, SDL_Rect obj2);
};