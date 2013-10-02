#include "profile.h"
#include <fstream>


Profile::Profile(std::string name)
{
    loadProfile(name);
}

Profile::~Profile()
{
    //dtor
}
void Profile::loadProfile(std::string name)
{
    this->name = name;
    std::ifstream(("saves" + name + ".sav").c_str());
}
void Profile::saveProfile()
{
    ;
}

