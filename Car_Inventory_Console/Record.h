
#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <cctype>

using namespace std;

// Global variables.
const int MAX_SIZE = 100;    // Maximum size of objects in array(max items in record).
const int MAX_INPUT_SIZE = 50;  // Maximum size of input array.
const int MAX_ID_LENGTH = 7;    // Maximum length for ID number.
const int MAX_PRICE_LENGTH = 10; // Maximum length for price.
const int MIN_PRICE_LENGTH = 4; // Minimum length for price.
const int MAX_ERR_MSG = 100;  // Maximum amount of error message strings.

class Record
{
public:
    // Constructors.
    Record() { SetRecord("", "", 0, 0.00f); }
    Record(string id, string mod) { SetRecord(id, mod, 0, 0.0f); }
    Record(string id, string mod, int quant, float pr) { SetRecord(id, mod, quant, pr); }

    // Copy constructor.
    Record(const Record& obj)
        :
        ID(obj.ID),
        model(obj.model),
        quantity(obj.quantity),
        price(obj.price)

    {}

    // Operator overloads.
    void operator=(const Record& obj);
    friend ostream& operator<<(ostream& output, const Record& rec);
    friend istream& operator>>(istream& input, Record& rec);
    bool operator<(const Record& rhs)const;
    bool operator>(const Record& rhs)const;

    // Destructor.
    ~Record() { }

    // Getters:
    string GetID() const { return ID; }
    string GetModel() const { return model; }
    int GetQuantity() const { return quantity; }
    float GetPrice() const { return price; }
    Record GetRecord() const {}

    // Setters:
    void SetRecord(string id, string mod, int quant, float pr);
    void SetRecord(Record rec);
    void SetID(string id) { SetRecord(id, model, quantity, price); }
    void SetModel(string mod) { SetRecord(ID, mod, quantity, price); }
    void SetQuantity(int quant) { SetRecord(ID, model, quant, price); }
    void SetPrice(float pr) { SetRecord(ID, model, quantity, pr); }

private:
    // Member variables:
    string ID = "";
    string model = "";
    int quantity = 0;
    float price = 0.00f;

};

#endif // !RECORD_H
