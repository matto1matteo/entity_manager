/**
*   COMP4300 Assignemnt 2: Entity Manager
*
*   Author: Matteo Maria Emanule Cialei
*   Version: 0.0.0
*   Date: 18/05/2023
*/

#include <entity/entity.h>
#include <game/game.h>
#include <iostream>

int main (int argc, char *argv[]) {
    
    try
    {
        Game g ("/home/mattomatteo/Projects/entity_manager/config.conf");
        return g.run();
    }
    catch (ConfigException e)
    {
        std::cerr << e.Message << "\n";
        return 1;
    }
    
}
