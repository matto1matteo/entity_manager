#include <algorithm>
#include <entity/entity_manager.h>

EntityManager::EntityManager()
{
    init();
}

void EntityManager::init()
{
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    auto entity = std::shared_ptr<Entity>(new Entity(tag, id));
    id++;

    m_entitiesToAdd.push_back(entity);

    return entity;
}

void EntityManager::update()
{
    // remove all dead entites from array and map
    auto i = std::remove_if(
        m_entities.begin(),
        m_entities.end(),
        [](std::shared_ptr<Entity> & e) {
            return !e.get()->isActive();
        }
    );
    m_entities.erase(i, m_entities.end());

    for(auto & entites : m_entitiesMap)
    {
        i = std::remove_if(
            entites.second.begin(),
            entites.second.end(),
            [](const std::shared_ptr<Entity> & e) {
                return !e.get()->isActive();
            }
        );
        entites.second.erase(i, entites.second.end());
    }
    for(auto it = m_entitiesMap.begin(); it != m_entitiesMap.end(); )
    {
        if (it->second.size() == 0)
        {
            auto here = it++;
            m_entitiesMap.erase(here);
        }
        else
        {
            ++it;
        }
    }

    // add entites that are inside m_entitiesToAdd
    for (auto e : m_entitiesToAdd) {
        m_entities.push_back(e);
        if (m_entitiesMap.find(e->tag()) != m_entitiesMap.end()) {
            m_entitiesMap.at(e->tag()).push_back(e);
        } else {
            m_entitiesMap.insert({ e->tag(), { e } });
        }
    }
    m_entitiesToAdd.clear();
}

EntityVec & EntityManager::getEntities()
{
    return m_entities;
}

EntityVec & EntityManager::getEntities(const std::string & tag)
{
    return m_entitiesMap.at(tag);
}
