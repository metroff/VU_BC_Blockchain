#pragma once
#include "myLib.hpp"
#include "user.hpp"
#include "generator.hpp"
#include <algorithm>

#define MIN_BALANCE 100
#define MAX_BALANCE 1000000

class Users {
    private:
        vector<User> users;

    public:
        void generate_users(int);
        stringstream to_sstream();
        User* get_random_user();

};