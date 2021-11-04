#pragma once

class User;

class TransactionOutput {
public:
    string id;
    int index;
    int amount;
    User* receiver;
    bool spent;
    bool confirmed;
    TransactionOutput(int amount, User* user) :amount{ amount }, spent{ false }, confirmed{ false }, index{ 0 }, receiver{user} {}
};