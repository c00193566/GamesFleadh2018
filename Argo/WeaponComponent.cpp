#include "WeaponComponent.h"

WeaponComponent::WeaponComponent(int c, float ft, float rt)
{
	m_maxclip = c;
	m_clip = m_maxclip;

	m_firetime = ft;
	m_reloadtime = rt;
	m_timer = ft;

	m_reload = false;
	m_fire = false;
}

void WeaponComponent::Init()
{
}

void WeaponComponent::Update()
{
	m_timer += 1.0f / 60.0f;

	if (m_reload)
	{
		if (m_timer >= m_reloadtime)
		{
			m_reload = false;
			m_clip = m_maxclip;
		}
	}
	else
	{
		if (m_timer >= m_firetime)
		{
			m_fire = true;
		}
	}

	if (m_clip <= 0)
	{
		m_reload = true;
		m_fire = false;
	}
}
