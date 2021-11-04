#include "transaction.hpp"

Transaction::Transaction() : confirmed{false} { }

void Transaction::execute() {
    for (auto input : inputs) {
        input.prev_transaction->spent = true;
    }
    for (auto output : outputs) {
        output->receiver->add_output(output);
    }
}

void Transaction::confirm() {
    confirmed = true;
    for (auto tx : outputs) {
        tx->confirmed = true;
    }
}

void Transaction::add_input(TransactionInput itx) {
    itx.index = inputs.size();
    inputs.push_back(itx);
}

void Transaction::add_output(std::shared_ptr<TransactionOutput> const& otx) {
    otx->index = outputs.size();
    outputs.push_back(otx);
}

string Transaction::get_id() const {
    return transaction_id;
}

int Transaction::get_amount() {
    int sum = 0;
    for (auto otx : outputs) {
        sum += otx->amount;
    }
    return sum;
}

int Transaction::get_input_amount() {
    int sum = 0;
    for (auto itx : inputs) {
        sum += itx.prev_transaction->amount;
    }
    return sum;
}

void Transaction::set_id() {
    transaction_id = generate_id();
    for (auto output : outputs) {
        output->id = transaction_id;
    }
}

string Transaction::generate_id() {
    stringstream ss;
    for (auto input : inputs) {
        auto obj = input.prev_transaction;
        ss << obj->amount << obj->receiver;
    }
    for (auto output : outputs) {
        ss << output->amount << output->receiver;
    }
    return myHash(ss.str());
}

stringstream Transaction::inputs_to_sstream() {
    stringstream ss;
    ss << "INPUTS" << endl <<
        string(50, '-') << endl;
    for (auto input : inputs) {
        auto obj = input.prev_transaction;
        ss << "Index: " << obj->index << endl;
        if (obj->receiver != NULL)
        {
            ss << "Adress: " << obj->receiver->get_public_key() << endl;
        }
        else {
            ss << "Adress: NULL" << endl;
        }
        ss << "Value: " << obj->amount << endl
        << string(50, '-') << endl;
    }
    return ss;
}

stringstream Transaction::outputs_to_sstream() {
    stringstream ss;
    ss << "OUTPUTS" << endl <<
        string(50, '-') << endl;
    for (auto output : outputs) {
        ss << "Index: " << output->index << endl;
        if (output->receiver != NULL)
        {
            ss << "Adress: " << output->receiver->get_public_key() << endl;
        }
        else {
            ss << "Adress: NULL" << endl;
        }  
        ss << "Value: " << output->amount << endl
        << string(50, '-') << endl;
    }
    return ss;
}

stringstream Transaction::to_sstream() {
   stringstream ss;
   ss << "Transaction ID: " << get_id() << endl;
   if (confirmed)
       ss << "Status: Confirmed" << endl;
   else
       ss << "Status: Unconfirmed" << endl;

   ss << "Total input: " << get_input_amount() << endl
      << "Total output: " << get_amount() << endl
      << inputs_to_sstream().rdbuf()
      << outputs_to_sstream().rdbuf();
   ss << endl << endl;
    return ss;
}