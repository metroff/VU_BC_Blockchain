#include "user.hpp"

User::User(string name, int balance) : name{name} {
    this->public_key = myHash(name + std::to_string(generateIntInRange(1, 999999999)));
    
    add_output(std::shared_ptr<TransactionOutput>(new TransactionOutput(balance, nullptr)));
}

string User::get_name() {
    return name;
}

string User::get_public_key() {
    return public_key;
}

void User::add_output(std::shared_ptr<TransactionOutput> const& otx) {
    outputs.push_back(otx);
}

vector<std::shared_ptr<TransactionOutput>> User::get_unspent_outputs() {
    vector<std::shared_ptr<TransactionOutput>> out;
    for (auto otx : outputs) {
        if (otx->spent == false)
        {
            out.push_back(otx);
        }
    }
    return out;
}

int User::get_balance() {
    int output = 0;
    for (auto otx : outputs) {
        if (otx->spent == false){
            output += otx->amount;
        }
    }
    return output;
}