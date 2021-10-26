#pragma once
#include "myLib.hpp"
#include "transaction.hpp"
#include "users.hpp"
#include "user.hpp"
#include <algorithm>
#include <unordered_map>

class Pool {
    private:
        vector<Transaction> transaction_pool;
        void shuffle(int);
    public:
        void generate_transaction_pool(Users&, int);
        void add_transaction(Transaction&);
        Transaction get_transaction(int);
        vector<Transaction> get_transactions(int);
        int get_transaction_count();
        stringstream to_sstream();
        void remove_transaction(const Transaction&);
        void remove_transactions(const vector<Transaction>&);
};