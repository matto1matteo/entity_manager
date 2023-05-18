#pragma once

class EntityManager {
public:
    EntityManager() = default;
    EntityManager(EntityManager &&) = default;
    EntityManager(const EntityManager &) = default;
    EntityManager &operator=(EntityManager &&) = default;
    EntityManager &operator=(const EntityManager &) = default;
    ~EntityManager() = default;

private:
    
};
