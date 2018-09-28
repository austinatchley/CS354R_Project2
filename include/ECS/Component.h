#pragma once

#include <cstdint>
#include <memory>
#include <set>

#include "Entity.h"

namespace ECS {
using ComponentType = std::size_t;
using ComponentTypeSet = std::set<ComponentType>;

static const ComponentType InvalidComponentType = 0;

struct Component {
    static const ComponentType mType = InvalidComponentType;
};

class AbstractComponentStore {
  public:
    using Ptr = std::unique_ptr<AbstractComponentStore>;
};

template <typename C> class ComponentStore : public AbstractComponentStore {
    static_assert(std::is_base_of<Component, C>::value,
                  "C must be a Component or be derived from Component");
    static_assert(C::mType != InvalidComponentType,
                  "C must not be of invalid component type");

  public:
    ComponentStore() {}
    ~ComponentStore() {}

    bool add(const Entity entity, C &&component) {
        return mStore.insert(std::make_pair(entity, std::move(component)))
            .second;
    }

    bool remove(Entity entity) { return mStore.erase(entity) > 0; }

    bool has(Entity entity) const {
        return mStore.find(entity) != mStore.end();
    }

    C &get(Entity entity) { return mStore.at(entity); }

    C extract(Entity entity) {
        C component = std::move(mStore.at(entity));
        mStore.erase(entity);
        return component;
    }

    const std::unordered_map<Entity, C> &getComponents() { return mStore; }

  private:
    std::unordered_map<Entity, C> mStore;
    static const ComponentType mType = C::mType;
};
}
