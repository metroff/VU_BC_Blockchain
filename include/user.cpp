#include "user.hpp"

User::User(string name, int balance) : name{name}, balance{balance} {
    this->public_key = myHash(name + std::to_string(generateIntInRange(1, 999999999)));
}

string User::get_name() {
    return name;
}

string User::get_public_key() {
    return public_key;
}

int User::get_balance() {
    return balance;
}

void User::set_balance(int value) {
    this->balance = value;
}