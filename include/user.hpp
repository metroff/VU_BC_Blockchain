#pragma once
#include "myLib.hpp"
#include "hash.hpp"
#include "generator.hpp"

class User {
    private:
        string name;
        string public_key;
        int balance;

    public:
        User(string, int);

        string get_name();
        string get_public_key();
        int get_balance();
        void set_balance(int);
};