#pragma once
#include <memory>
#include <string>

#include <components/bbox.h>
#include <components/collision.h>
#include <components/input.h>
#include <components/lifespan.h>
#include <components/name.h>
#include <components/score.h>
#include <components/shape.h>
#include <components/transform.h>

namespace mtt
{
class Entity {
    friend class EntityManager;

private:
    const std::string m_tag = "default";
    const size_t m_id = 0;
    bool m_active = true;

private:
    Entity(const std::string& tag, size_t id);

public:
    // Components
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape> cShape;
    std::shared_ptr<CCollision> cCollision;
    std::shared_ptr<CInput> cInput;
    std::shared_ptr<CScore> cScore;
    std::shared_ptr<CLifespan> cLifespan;

public:
    bool isActive() const { return m_active; }
    const std::string & tag() const { return m_tag; }
    const size_t id() const { return m_id; }
    void destroy() { m_active = false; }

    /// @brief  will return true if both entities are capable of colliding,
    ///         that is both have a CCollision component and the distance
    ///         between their center is less then the sum of their
    ///         respective radiuses
    /// @param  `entity`    the entity to check against for collision
    /// @return bool
    bool colliding(const Entity & entity) const;
};
    
}
