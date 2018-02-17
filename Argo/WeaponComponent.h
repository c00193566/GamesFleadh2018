#pragma once
#include <iostream>
#include "ECS.h"

/// <class>WeaponComponent</class>
/// <summary>
/// This class will control variables for
/// a weapon such as reload time, time between
/// firing and clip size.
/// </summary>
/// <author>Jack Keogh</author>

using namespace std;

class WeaponComponent : public Component
{
private:
	bool m_reload;
	bool m_fire;
	int m_clip;
	int m_maxclip;
	float m_timer;
	float m_firetime;
	float m_reloadtime;

public:
	/// <summary>
	/// Default contructor with overload parameters
	/// </summary>
	/// <param name="c">int defining clip size.</param>
	/// <param name="ft">float defining time between firing.</param>
	/// <param name="rt">float defining reload time.</param>
	WeaponComponent(int c = 0, float ft = 0.0f, float rt = 0.0f);

	/// <summary>
	/// Override initialiser inherited from component class.
	/// </summary>
	void Init() override;

	/// <summary>
	/// Override update inherited from component class.
	/// </summary>
	void Update() override;

	/// <summary>
	/// getter functions
	/// </summary>
	bool getReload() { return m_reload; };
	bool getFire() { return m_fire; };
	int getClip() { return m_clip; };

	/// <summary>
	/// setter functions.
	/// </summary>
	void setReload(bool set) { m_reload = set; };
	void setFire(bool set) { m_fire = set; };
	void setTimer(float set) { m_timer = set; };
	void setClip(int set) { m_clip = set; };
};