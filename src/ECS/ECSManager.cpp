#include "ECS/ECSManager.h"

#include <algorithm>
#include <cstdint>

namespace ECS {

ECSManager::ECSManager()
    : mLastEntity(InvalidEntity), mEntities(), mComponentStores(), mSystems() {}

ECSManager::~ECSManager() {}

void ECSManager::addSystem(const System::Ptr &systemPtr) {
    if ((!systemPtr) || (systemPtr->getRequiredComponents().empty())) {
        throw std::runtime_error("System shall specified required Components");
    }

    mSystems.push_back(systemPtr);
}

size_t ECSManager::registerEntity(const Entity entity) {
    std::size_t associatedSystems = 0;

    auto entityIt = mEntities.find(entity);
    if (entityIt == mEntities.end()) {
        throw std::runtime_error("The Entity does not exist");
    }
    auto entityComponents = entityIt->second;

    for (auto system = mSystems.begin(); system != mSystems.end(); ++system) {
        auto systemRequiredComponents = (*system)->getRequiredComponents();

        if (std::includes(entityComponents.begin(), entityComponents.end(),
                          systemRequiredComponents.begin(),
                          systemRequiredComponents.end())) {
            (*system)->registerEntity(entity);
            ++associatedSystems;
        }
    }

    return associatedSystems;
}

std::size_t ECSManager::unregisterEntity(const Entity entity) {
    std::size_t associatedSystems = 0;

    auto entityIt = mEntities.find(entity);
    if (entityIt == mEntities.end()) {
        throw std::runtime_error("The Entity does not exist");
    }
    auto entityComponents = (*entityIt).second;

    for (auto system = mSystems.begin(); system != mSystems.end(); ++system) {
        associatedSystems += (*system)->unregisterEntity(entity);
    }

    return associatedSystems;
}

size_t ECSManager::updateEntities(float abElapsedTime) {
    size_t updatedEntities = 0;

    for (auto system = mSystems.begin(); system != mSystems.end(); ++system) {
        updatedEntities += (*system)->updateEntities(abElapsedTime);
    }

    return updatedEntities;
}
}
