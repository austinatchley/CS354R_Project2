#pragma once

#include <cstdint>
#include <memory>
#include <set>

#include "Component.h"
#include "Entity.h"

namespace ECS
{
class ECSManager;

class System
{
    public:
    using Ptr = std::shared_ptr<System>;

    explicit System (ECSManager& manager);
    virtual ~System ();

    const ComponentTypeSet& getRequiredComponents () const
    {
        return mRequiredComponents;
    }

    bool registerEntity (Entity entity)
    {
        return mMatchingEntities.insert (entity).second;
    }

    std::size_t unregisterEntity (Entity entity)
    {
        return mMatchingEntities.erase (entity);
    }

    bool hasEntity (Entity entity) const
    {
        return mMatchingEntities.find (entity) != mMatchingEntities.end ();
    }

    std::size_t updateEntities (float dt);

    virtual void updateEntity (float dt, Entity entity) = 0;

    protected:
    void setRequiredComponents (ComponentTypeSet&& requiredComponents)
    {
        mRequiredComponents = std::move (requiredComponents);
    }

    ECSManager& mManager;

    private:
    ComponentTypeSet mRequiredComponents;
    std::set<Entity> mMatchingEntities;
};
} // namespace ECS
