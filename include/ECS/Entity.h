#pragma once

#include <unordered_map>

namespace ECS {
using Entity = std::size_t;

static const Entity InvalidEntity = 0;

/*
using EntityId = unsigned long;

class Entity
{
    friend class EntityManager;
    static const EntityId InvalidId = 0;

public:
    Entity() = default;
    Entity(EntityId id)
        : mID(id)
    {}

    bool valid() const
    {
        return mID != InvalidId;
    }

    void invalidate()
    {
        mID = InvalidId;
    }

    //Component management
    template <typename C, typename... Types>
    void addComponent(Types&&... args)
    {
    }

    template <typename C>
    void removeComponent();

    template <typename C>
    bool hasComponent() const;

    // Operators
    operator bool() const
    {
        return valid();
    }

    bool operator==(const Entity& other)
    {
        return mID == other.mID;
    }

    bool operator!=(const Entity& other)
    {
        return !(*this == other);
    }

    bool operator<(const Entity& other)
    {
        return other.mID < mID;
    }

private:
    EntityId mID = InvalidId;
};

class EntityManager
{

public:
    static EntityManager* getInstance()
    {
        if (!mInstance)
        {
            mInstance = new EntityManager();
        }

        return mInstance;
    }

    // Creates a new Entity and assigns an ID to it
    EntityId create();

    // Destroys a Entity and invalidates its ID
    void destroy(EntityId entityId);

    // Returns the Entity with entityId
    Entity* get(EntityId entityId) const;

    // Returns the EntityId associated with this entity
    EntityId getId(Entity* entity) const;

private:
    static EntityManager* mInstance;

    std::unordered_map<EntityId, Entity*> mEntityTable;
};
*/
}
