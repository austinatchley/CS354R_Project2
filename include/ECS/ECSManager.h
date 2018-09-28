#pragma once

#include <map>
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"
#include "System.h"

namespace ECS {
class ECSManager {
  public:
    ECSManager();
    virtual ~ECSManager();

    template <typename C> bool createComponentStore() {
        // clang-format off
        static_assert(std::is_base_of<Component, C>::value,
                      "C must be a descendant of Component");
        static_assert(C::mType != InvalidComponentType,
                      "C's types must not be InvalidComponentType");
        // clang-format on

        return mComponentStores
            .insert(std::make_pair(
                C::mType, AbstractComponentStore::Ptr(new ComponentStore<C>())))
            .second;
    }

    template <typename C> ComponentStore<C> &getComponentStore() {
        // clang-format off
        static_assert(std::is_base_of<Component, C>::value,
                      "C must be a descendant of Component");
        static_assert(C::mType != InvalidComponentType,
                      "C's types must not be invalidcomponent");
        // clang-format on

        auto componentStoreIt = mComponentStores.find(C::mType);
        if (componentStoreIt == mComponentStores.end()) {
            throw std::runtime_error("The ComponentStore does not exist");
        }

        return reinterpret_cast<ComponentStore<C> &>(*componentStoreIt->second);
    }

    void addSystem(const System::Ptr &systemPtr);

    Entity createEntity() {
        mEntities.insert(std::make_pair(mLastEntity + 1, ComponentTypeSet()));
        return ++mLastEntity;
    }

    template <typename C>
    bool addComponent(const Entity entity, C &&component) {
        static_assert(std::is_base_of<Component, C>::value,
                      "C must inherit from Component");
        static_assert(C::mType != InvalidComponentType,
                      "C's types must not be InvalidComponent");

        auto entityIt = mEntities.find(entity);
        if (entityIt == mEntities.end()) {
            throw std::runtime_error("The entity does not exist");
        }

        entityIt->second.insert(C::mType);
        return getComponentStore<C>().add(entity, std::move(component));
    }

    std::size_t registerEntity(const Entity entity);
    std::size_t unregisterEntity(const Entity entity);
    std::size_t updateEntities(float dt);

  private:
    Entity mLastEntity;
    std::unordered_map<Entity, ComponentTypeSet> mEntities;
    std::map<ComponentType, AbstractComponentStore::Ptr> mComponentStores;
    std::vector<System::Ptr> mSystems;
};
}
