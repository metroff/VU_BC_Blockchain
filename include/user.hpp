#pragma once
#include "myLib.hpp"
#include "hash.hpp"
#include "generator.hpp"
#include "transaction_output.hpp"

class User {
    private:
        string name;
        string public_key;
        vector<std::shared_ptr<TransactionOutput> > outputs;

    public:
        User(string, int);

        void add_output(std::shared_ptr<TransactionOutput> const&);
        string get_name();
        string get_public_key();
        vector<std::shared_ptr<TransactionOutput> > get_unspent_outputs();
        int get_balance();
};