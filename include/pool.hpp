#pragma once
#include "myLib.hpp"
#include "transaction.hpp"
#include "users.hpp"
#include "user.hpp"
#include <algorithm>

class Pool {
    private:
        vector<Transaction> transaction_pool;
    public:
        void generate_transaction_pool(Users&, int);
        Transaction get_transaction(int);
        vector<Transaction> get_transactions(int);
        int get_transaction_count();
        stringstream to_sstream();
        void remove_transaction(Transaction&);
        void remove_transactions(vector<Transaction>&);
};