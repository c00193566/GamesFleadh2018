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

using ComponentID = size_t;

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
public:
	Entity() {};

	Entity(string tag)
	{
		m_tag = tag;
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

	string ID()
	{
		return m_tag;
	};

private:
	bool m_active = true;
	string m_tag;
	vector<unique_ptr<Component>> m_components;
	ComponentArray m_componentArray;
	ComponentBitSet m_componentBitSet;
};

class EntityManager
{
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
		m_entities.erase(std::remove_if(std::begin(m_entities), std::end(m_entities),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),
			std::end(m_entities));
	}

	Entity& addEntity(string tag)
	{
		Entity * e = new Entity(tag);
		unique_ptr<Entity> Uptr{ e };
		m_entities.emplace_back(move(Uptr));
		return *e;
	}

	vector<unique_ptr<Entity>> const& getEntities() const
	{
		return m_entities;
	}

private:
	vector<unique_ptr<Entity>> m_entities;
};