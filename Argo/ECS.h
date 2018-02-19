#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

using namespace std;

class Component;
class Entity;
class EntityManager;

enum Groups : size_t
{
	PlayerGroup,
	WallGroup,
	EnemyGroup,
	TileGroup,
	PlayerBulletGroup,
};

using ComponentID = size_t;
using Group = size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr size_t maxComponents = 32;
constexpr size_t maxGroups = 32;

using GroupBitSet = bitset<maxGroups>;

using ComponentBitSet = bitset<maxComponents>;
using ComponentArray = array<Component*, maxComponents>;

class Component
{
public:
	virtual void Init() {};
	virtual void Update() {};
	virtual void Draw() {};

	Entity * m_entity;
};

class Entity
{
private:
	EntityManager & m_manager;
	bool m_active;
	vector<unique_ptr<Component>> m_components;

	ComponentArray m_componentArray;
	ComponentBitSet m_componentBitSet;
	GroupBitSet m_groupBitSet;

public:
	Entity(EntityManager & Manager) :
		m_manager(Manager)
	{
		m_active = true;
	};

	virtual ~Entity() {};

	void Update()
	{
		for (auto& c : m_components)
		{
			c->Update();
		}
	}

	void Draw()
	{
		for (auto& c : m_components)
		{
			c->Draw();
		}
	}

	bool isActive() { return m_active; };
	void setActive(bool set) { m_active = set; };

	bool hasGroup(Group group)
	{
		return m_groupBitSet[group];
	}

	void addGroup(Group group);

	void delGroup(Group group)
	{
		m_groupBitSet[group] = false;
	}

	/// <summary>
	/// Adds a component with multiple arguments
	/// to the entity
	/// </summary>
	template<typename T, typename... Targs>
	T& addComponent(Targs&&... args)
	{
		T* c(new T(forward<Targs>(args)...));
		c->m_entity = this;

		unique_ptr<Component> Uptr{ c };
		m_components.emplace_back(move(Uptr));

		m_componentArray[getComponentTypeID<T>()] = c;
		m_componentBitSet[getComponentTypeID<T>()] = true;

		c->Init();
		return *c;
	}

	/// <summary>
	/// This method gets a component of type T
	/// </summary>
	template<typename T>
	T& getComponent()
	{
		auto ptr(m_componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	/// <summary>
	/// This method checks if a component exists
	/// </summary>
	template<typename T>
	bool hasComponent() const
	{
		return m_componentBitSet[getComponentTypeID<T>()];
	}
};

class EntityManager
{
private:
	vector<unique_ptr<Entity>> m_entities;
	array<vector<Entity*>, maxGroups> m_groupedEntities;

public:
	EntityManager()
	{
		m_entities = vector<unique_ptr<Entity>>();
	}

	void Update()
	{
		for (auto& e : m_entities)
		{
			e->Update();
		}
	}

	void Draw()
	{
		for (auto& e : m_entities)
		{
			e->Draw();
		}
	}

	void Refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(m_groupedEntities[i]);

			v.erase(std::remove_if(std::begin(v), std::end(v),[i](Entity* mEntity)
			{
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}),
				std::end(v));
		}

		m_entities.erase(std::remove_if(std::begin(m_entities), std::end(m_entities),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),
			std::end(m_entities));
	}

	void addToGroup(Entity * ent, Group group)
	{
		m_groupedEntities[group].emplace_back(ent);
	}

	vector<Entity*>& getGroup(Group group)
	{
		return m_groupedEntities[group];
	}

	Entity& addEntity()
	{
		Entity * e = new Entity(*this);
		unique_ptr<Entity> Uptr{ e };
		m_entities.emplace_back(move(Uptr));
		return *e;
	}

	vector<unique_ptr<Entity>> const& getEntities() const
	{
		return m_entities;
	}
};