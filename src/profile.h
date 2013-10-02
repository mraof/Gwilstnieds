#ifndef PROFILE_H
#define PROFILE_H
#include <string>


class Profile
{
    public:
        std::string name;
        int money;

        Profile(std::string name);
        virtual ~Profile();
        void loadProfile(std::string name);
        void saveProfile();
};

#endif // PROFILE_H
