#include <catch2/catch_test_macros.hpp>
#include <entity/entity_manager.h>
#include <iostream>

using namespace mtt;
class TestEntityManager
{
public:
    static EntityVec getToAdd(EntityManager manager) { return manager.m_entitiesToAdd; }
    static EntityMap getEntityMap(EntityManager manager) { return manager.m_entitiesMap; }
};

TEST_CASE("EntityManager add entities") {
    TestEntityManager friendTester;
    EntityManager manager;
    SECTION("Adding entities") {
        manager.addEntity("hello");
        REQUIRE(manager.getEntities().size() == 0);
        REQUIRE(friendTester.getToAdd(manager).size() == 1);
    }

    SECTION("Adding entities and update") {
        manager.addEntity("hello");
        manager.update();

        REQUIRE(manager.getEntities().size() == 1);
        REQUIRE(friendTester.getToAdd(manager).size() == 0);
        REQUIRE(friendTester.getEntityMap(manager).size() == 1);
    }

    SECTION("Checking tagged entities")
    {
        manager.addEntity("hello");
        manager.addEntity("hello");
        manager.addEntity("hello");
        manager.addEntity("Culo");
        manager.update();
        REQUIRE(manager.getEntities().size() == 4);
        REQUIRE(friendTester.getEntityMap(manager).size() == 2);
        REQUIRE(manager.getEntities("hello").size() == 3);
        REQUIRE(manager.getEntities("Culo").size() == 1);
    }


}

TEST_CASE("Removing entities") {
    TestEntityManager friendTester;
    EntityManager manager;
    std::shared_ptr<Entity> e = manager.addEntity("hello");
    REQUIRE(manager.getEntities().size() == 0);
    manager.update();
    REQUIRE(manager.getEntities().size() == 1);

    SECTION("check entities vec") {
        e.get()->destroy();
        manager.update();
        REQUIRE(manager.getEntities().empty());
    }

    SECTION("check entities map") {
        e.get()->destroy();
        manager.update();
        REQUIRE(friendTester.getEntityMap(manager).size() == 0);
    }

}
