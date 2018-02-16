#include "ColliderComponent.h"

void ColliderComponent::Init()
{
	m_transform = &m_entity->getComponent<TransformComponent>();

	m_central.w = m_transform->width;
	m_central.h = m_transform->height;
	m_left.w = m_transform->width;
	m_left.h = m_transform->height;
	m_right.w = m_transform->width;
	m_right.h = m_transform->height;
	m_top.w = m_transform->width;
	m_top.h = m_transform->height;
	m_bottom.w = m_transform->width;
	m_bottom.h = m_transform->height;
}

void ColliderComponent::Update()
{
	//Central Collider
	m_central.x = m_transform->position.x;
	m_central.y = m_transform->position.y;
	m_central.w = m_transform->width * m_transform->scale;
	m_central.h = m_transform->height * m_transform->scale;

	//Left Collider
	m_left.x = m_transform->position.x - 2;
	m_left.y = m_transform->position.y;
	m_left.w = m_transform->width * m_transform->scale;
	m_left.h = m_transform->height * m_transform->scale;

	//Right Collider
	m_right.x = m_transform->position.x + 2;
	m_right.y = m_transform->position.y;
	m_right.w = m_transform->width * m_transform->scale;
	m_right.h = m_transform->height * m_transform->scale;

	//Top Collider
	m_top.x = m_transform->position.x;
	m_top.y = m_transform->position.y - 2;
	m_top.w = m_transform->width * m_transform->scale;
	m_top.h = m_transform->height * m_transform->scale;

	//Bottom Collider
	m_bottom.x = m_transform->position.x;
	m_bottom.y = m_transform->position.y + 2;
	m_bottom.w = m_transform->width * m_transform->scale;
	m_bottom.h = m_transform->height * m_transform->scale;

}
