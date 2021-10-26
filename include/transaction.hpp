#pragma once
#include "myLib.hpp"
#include "user.hpp"
#include "hash.hpp"

class Transaction {
    private:
        string transaction_id;
        User* sender;
        User* receiver;
        int amount;

    public:
        Transaction(User*, User*, int);
        void execute();

        string get_id() const;
        User* get_sender();
        User* get_receiver();
        string get_senders_hash();
        string get_reveivers_hash();
        int get_amount();
        stringstream to_sstream();
};