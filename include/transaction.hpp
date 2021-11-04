#pragma once
#include "myLib.hpp"
#include "user.hpp"
#include "hash.hpp"
#include "transaction_output.hpp"

struct TransactionInput {
    int index;
    std::shared_ptr<TransactionOutput> prev_transaction;
    User* owner;
};

class Transaction {
    private:
        string transaction_id;
        vector<TransactionInput> inputs;
        vector<std::shared_ptr<TransactionOutput>> outputs;
        bool confirmed;

        stringstream inputs_to_sstream();
        stringstream outputs_to_sstream();

    public:
        Transaction();
        void execute();
        void confirm();
        void add_input(TransactionInput);
        void add_output(std::shared_ptr<TransactionOutput> const&);
        int get_amount();
        int get_input_amount();

        string get_id() const;
        void set_id();
        string generate_id();
        stringstream to_sstream();
};