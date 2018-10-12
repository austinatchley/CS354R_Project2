#include <ECS/ECSManager.h>
#include <ECS/System.h>

#include <cstdint>

namespace ECS
{

System::System (ECSManager& manager) : mManager (manager)
{
}

System::~System ()
{
}

size_t System::updateEntities (float dt)
{
    std::size_t updatedEntities = 0;

    for (auto entity = mMatchingEntities.begin (); entity != mMatchingEntities.end (); ++entity)
    {
        updateEntity (dt, *entity);
        ++updatedEntities;
    }

    return updatedEntities;
}

/* virtual pure method to be specialized by user classes
void System::updateEntity(float aElapsedTime, Entity aEntity) {
}
*/

} // namespace ECS
