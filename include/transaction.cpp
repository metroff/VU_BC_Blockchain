#include "transaction.hpp"

Transaction::Transaction(User *sender, User *receiver, int amount) : sender{sender}, receiver{receiver}, amount{amount} {
    this->transaction_id = myHash(sender->get_name() + receiver->get_name() + std::to_string(amount));
}

void Transaction::execute() {
    sender->set_balance(sender->get_balance() - amount);
    receiver->set_balance(receiver->get_balance() + amount);
}

string Transaction::get_id() {
    return transaction_id;
}

User* Transaction::get_sender() {
    return sender;
}

User* Transaction::get_receiver() {
    return receiver;
}

string Transaction::get_senders_hash() {
    return sender->get_public_key();
}

string Transaction::get_reveivers_hash() {
    return receiver->get_public_key();
}

int Transaction::get_amount() {
    return amount;
}

stringstream Transaction::to_sstream() {
    stringstream ss;
    ss << "Transaction ID: " << get_id() << endl
        << "Sender public key: " << get_senders_hash() << endl
        << "Receiver public key: " << get_reveivers_hash() << endl
        << "Amount: " << get_amount() << endl;
        ss << string(50, '-') << endl;
    return ss;
}