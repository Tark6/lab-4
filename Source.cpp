#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int DICT_SIZE = 5;

class HashTable
{
private:
    class Node {
    public:
        string element;
        Node* next;

        Node()
        {
            element = "";
            next = nullptr;
        }

        Node(string data)
        {
            element = data;
            next = nullptr;
        }
    };

    Node dictionary[DICT_SIZE];

    int FindI(string data)
    {
        int AscciSum = 0;
        for (int i = 0; i < data.size(); i++)
        {
            AscciSum += int(data[i]);
        }
        return AscciSum % DICT_SIZE;
    }

public:
    void MAKENULL()
    {
        for (int i = 0; i < DICT_SIZE; i++)
        {
            dictionary[i].element = "";
            dictionary[i].next = nullptr;
        }
    }

    bool MEMBER(string data)
    {
        int i = FindI(data);

        Node* current = dictionary;

        while (current != nullptr)
        {
            if (data == current->element)
                return true;
            else
                current = current->next;
        }
        return false;
    }

    void INSERT(string data)
    {
        int AscciSum = FindI(data);

        int i = AscciSum % DICT_SIZE;

        Node* current = &dictionary[i];

        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = new Node(data);
    }

    void DELETE(string data)
    {
        int AscciSum = FindI(data);

        int i = AscciSum % DICT_SIZE;

        Node* current = &dictionary[i];

        while (current != nullptr)
        {
            if (current->next->element == data)
            {
                Node* temp = current->next;
                current->next = temp->next;
                delete temp;
                break;
            }
            current = current->next;
        }
    }

    void PRINT()
    {
        Node* current;
        for (int i = 0; i < DICT_SIZE; i++)
        {
            cout << "[" << i << "]: ";
            current = &dictionary[i];
            while (current != nullptr)
            {
                cout << current->element << " ";
                current = current->next;
            }
            cout << endl;
        }
    }
};


int main()
{
    HashTable HT;

    HT.MAKENULL();

    string company;
    fstream file("companies.txt", ios::in);
    while (!file.eof())
    {
        file >> company;
        HT.INSERT(company);
        company = "";
    }

    file.close();

    HT.PRINT();

    cout << endl;

    cout.setf(ios::boolalpha);

    cout << "Is Sony in the dictionary? - " << HT.MEMBER("Sony") << endl;

    HT.DELETE("Sony");

    cout << endl;

    HT.PRINT();

    cout << endl;

    cout << "Is Sony in the dictionary? - " << HT.MEMBER("Sony");

    return 0;
}
