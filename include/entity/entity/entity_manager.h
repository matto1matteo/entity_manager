#pragma once

#include <memory>
#include <vector>
#include <map>
#include <entity/entity.h>

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager {
#ifdef BUILD_TEST
    friend class TestEntityManager;
#endif
private:
    EntityVec m_entities;
    EntityMap m_entitiesMap;
    EntityVec m_entitiesToAdd;

public:
    EntityManager();
    EntityManager(EntityManager &&) = default;
    EntityManager(const EntityManager &) = default;
    EntityManager &operator=(EntityManager &&) = default;
    EntityManager &operator=(const EntityManager &) = default;
    ~EntityManager() = default;

private:
    void init();

public:
    void update();

    /// @brief This method adds up an entity to the stored entities
    std::shared_ptr<Entity> addEntity(const std::string& tag, size_t id);

    /// @brief  Accessor methods for stored entities
    EntityVec & getEntities();

    /// @brief  return the vector of entities with the given tag
    ///         If no entity inside the EntityManager has a key `tag` will
    ///         throw an exception
    /// 
    /// @param  entityTag The tag of the desired entities
    /// @return A reference to the vector of entites with the desired tag
    /// @throw  `std::out_of_range`
    EntityVec & getEntities(const std::string & entityTag);
    
};
