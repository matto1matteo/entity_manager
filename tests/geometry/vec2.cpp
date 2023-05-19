/// Tests for Vec2

#include <geometry/vec2.h>
#include <catch2/catch_test_macros.hpp>
#include <iostream>

TEST_CASE("vec2 op") {
    Vec2 v1(2.0, 3.0);
    Vec2 v2(2.0, 3.0);
    Vec2 v3(2.5, 3.0);
    Vec2 v4(2.0, 2.0);
    Vec2 v5(5.0, 7.0);
    Vec2 v6(3, 4);
    Vec2 unit(1,1);

    SECTION("Equalities") {
        REQUIRE( v1 == v2 );
        REQUIRE( v1 != v3 );
        REQUIRE( v1 != v4 );
    }

    SECTION("Sum and subract") {
        // sum
        REQUIRE( (v1 + Vec2(0.5, 0)) == v3 );
        REQUIRE( (v1 + Vec2(3.0, 4)) == v5 );

        // subtract
        REQUIRE( (v1 - Vec2(0, 1)) == v4 );
        REQUIRE( (v5 - Vec2(3.0, 4)) == v1 );

        v1 += Vec2(3, 4);
        v2 -= Vec2(0, 1);
        REQUIRE( v2 == v4 );
        REQUIRE( v1 == v5 );
    }

    SECTION("Multiplication and division") {
        // division
        REQUIRE( (v1 / 2) == Vec2(1, 1.5));
        REQUIRE( (v5 / 5) == Vec2(1, 1.4));

        // Multiplication
        // TODO: select a better way to test floating number
        REQUIRE( (v1 * 1.5) == Vec2(3, 4.5));
        Vec2 v = Vec2(10.5, 14.7);
        Vec2 mult = (v5 * 2.1);
        std::cout << "v.x - mult.x = " << v.x - mult.x << std::endl;
        std::cout << "v.x - mult.x = " << v.y - mult.y << std::endl;
        //REQUIRE(  mult == v );

    }

    SECTION("Mesurments") {
        REQUIRE(v6.length() == 5);

        float dist = v1.dist(v2);
        REQUIRE( dist == 0 );
        dist = v1.dist(v3);
        REQUIRE( dist == 0.5 );
        REQUIRE( v1.dist(v4) == 1 );
        REQUIRE( v1.dist(v5) == 5 );
    }

    SECTION("Normalization") {
        Vec2 v = v1.normalized();
        std::cout << "Non normalized vec: (" << v.x << ", " << v.y << ")\n";
        //REQUIRE( v == Vec2(0.5547, 0.83205) );
        v1.normalize();
        REQUIRE( v1 == v );
    }

    SECTION("angle operations") {
        REQUIRE(unit.getAngle() == 45);
        Vec2 fromAngle = Vec2::FromSpeedAndAngle(1, 30);
        Vec2 v (0.5, 0.866025);

        //REQUIRE(v.getAngle() == 30);
        REQUIRE(fromAngle.getAngle() == 30);
    }
}
