#pragma once

namespace ECS
{
    using ComponentId = unsigned long;

    class Component
    {
        friend class ComponentManager;
        static const ComponentId Invalid = 0;

    public:

    private:
        Component(EntityId parentEntityId) {}
        virtual ~Component() {}

        ComponentId mID;
        EntityId mEntity;
    };

    class ComponentManager
    {
    public:
        ComponentId create(EntityId parentEntityId);
        void destroy(ComponentId componentId);

        Component* get(ComponentId componentId) const;
        ComponentId getId(Component* component) const;
    };
}
