#pragma once

#include <memory>
#include <entity/entity.h>

using EntityVec = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<std::string, Entity>;

class EntityManager {
private:
    EntityVec m_entities;
    EntityMap m_entitiesMap;
    EntityVec m_entitiesToAdd;

public:
    EntityManager() = default;
    EntityManager(EntityManager &&) = default;
    EntityManager(const EntityManager &) = default;
    EntityManager &operator=(EntityManager &&) = default;
    EntityManager &operator=(const EntityManager &) = default;
    ~EntityManager() = default;

private:
    void init();

public:
    void update();
    std::shared_ptr<Entity> addEntity(const std::string& tag, size_t id);
    EntityVec & getEntities();
    EntityVec & getEntities(const std::string & entityTag);
    
};
