#include "entity/entity.h"

namespace mtt {
Entity::Entity(const std::string& tag, size_t id)
    : m_tag(tag)
    , m_id(id)
{
}

bool Entity::colliding(const Entity& entity) const
{
    if (
        cCollision == nullptr
        || entity.cCollision == nullptr
        || cTransform == nullptr
        || entity.cTransform == nullptr
    )
    {
        return false;
    }

    float xdist = cTransform->position.x - entity.cTransform->position.x;
    float ydist = cTransform->position.y - entity.cTransform->position.y;
    return cCollision->radius * cCollision->radius >= (xdist * xdist) + (ydist * ydist);
}
}
