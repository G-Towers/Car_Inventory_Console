#include "Record.h"

// Class Definitions.
void Record::SetRecord(string id, string mod, int quant, float pr)
{
    ID = id;
    model = mod;
    quantity = quant;
    price = pr;
}

void Record::SetRecord(Record rec)
{
    ID = rec.ID;
    model = rec.model;
    quantity = rec.quantity;
    price = rec.price;
}

void Record::operator=(const Record& obj)
{
    ID = obj.ID;
    model = obj.model;
    quantity = obj.quantity;
    price = obj.price;
}

ostream& operator<<(ostream& output, const Record& rec)
{
    output << rec.ID << rec.model << rec.quantity << rec.price;

    return output;
}

istream& operator>>(istream& input, Record& rec)
{
    input >> rec.ID >> rec.model >> rec.quantity >> rec.price;

    return input;
}

bool Record::operator<(const Record& rhs)const
{
    if (ID < rhs.ID || model < rhs.model || quantity < rhs.quantity || price < rhs.price)
        return true;
    return false;
}

bool Record::operator>(const Record& rhs)const
{
    if (ID > rhs.ID || model > rhs.model || quantity > rhs.quantity || price > rhs.price)
        return true;
    return false;
}


