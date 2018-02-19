#pragma once
#include "RenderSystem.h"

class Scene
{
public:
	virtual ~Scene() {};
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Event() = 0;
	virtual bool Running() = 0;
	virtual void Initialise() = 0;
	virtual void LoadLevel() = 0;

protected:
	bool IsRunning;

};