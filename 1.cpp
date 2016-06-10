#include<iostream>
#include<string>
using namespace std;

struct payment
{
    string name;
    char service[50];
    int amount;
};

struct person
{
    string name;
    int amount;
    person *next;
};

void addPersonAndPayment(person*&first, person*&last, person*&p, struct payment paymentRecord)
{
    p = new person;
    p->name = paymentRecord.name;
    p->amount = paymentRecord.amount;
    p->next = NULL;
    if (first == NULL)
    {
        first = last = p;
    }
    else {
        last->next = p;
        last = last -> next;
    }
}

void printExpenses(person*&p, person*&first, int *personCount)
{
   cout<<endl<<"Expenses: "<<endl;
    for (p = first; p!= NULL; p=p->next){
        cout<< p->name <<": "<< p->amount<<"$"<<endl;
        *personCount = *personCount+1;
    }
}

void combinePaymentsByOnePerson(person*&first, person*&temp)
{
    person *previous = first;
    person *current = previous->next;
    while (current != NULL)
    {
        person *runner = first;
        while (current != runner)
        {
            if (current->name == runner->name) {
                person *temp = current->next;
                runner->amount = runner->amount+current->amount;
                previous-> next = temp;
                current = temp;
                break;
            }
            runner = runner->next;
        }
        if (runner == current)
        {
            previous = current;
            current = current->next;
        }
    }
}

void findPersonWithMaxAmount(person*&first, person*&maxAmount, person*&p)
{
    maxAmount = first;
    for (p = first; p!= NULL; p=p->next)
    {
        if (p->amount > maxAmount->amount)
        {
            maxAmount = p;
        }
    }
}

void printTransactionToBeMade(person*&first, person*&maxAmount, person*&p, int average)
{
    if (first->next != NULL && (first->next->next!=NULL && first->amount != first->next->next->amount))
    {
        cout<<endl<<"Transactions to be made: "<<endl;
        for (p = first; p!= NULL; p=p->next)
        {
            if (p->amount<average)
            {
                cout<<p->name<<"-> "<<maxAmount->name<<": "<<average-p->amount<<"$"<<endl;
            }
        }
    }
}

void doTransactions(person*&first, person*&p, int average)
{
    for (p = first; p!= NULL; p=p->next)
    {
        p->amount=average;
    }
}

void deleteList(person*&first)
{
    person *p = first;
    while (p!=NULL)
    {
        first = first->next;
        delete p;
        p = first;
    }
}

int main()
{
    payment paymentRecord;
    int choice = 0;
    int total = 0;
    int personCount = 0;
    int average = 0;

    person *first = NULL, *last = NULL, *p, *temp, *maxAmount;

    cout << "Please follow the instructions below" << endl;
    do {
        cout << endl << "Enter name of your friend: ";
        cin>>paymentRecord.name;
        cin.ignore();
        cout << "Enter service your friend has paid for: ";
        cin.getline(paymentRecord.service, 50);
        cout << "Enter the amount: ";
        cin>>paymentRecord.amount;
        cin.ignore();

        cout << endl << "(1)Enter another one payment details"<<endl<<"(2)Calculate the sum of all payments by the person"<<endl;
        cin>>choice;

        addPersonAndPayment(first, last, p, paymentRecord);
        total = total + paymentRecord.amount;
    } while (choice!=2);

    combinePaymentsByOnePerson(first, temp);
    printExpenses(p, first, &personCount);
    average = total/personCount;
    findPersonWithMaxAmount(first, maxAmount, p);
    printTransactionToBeMade(first, maxAmount, p, average);
    doTransactions(first, p, average);
    deleteList(first);
    return 0;
}
