#include <iostream>
#include "Ex14.h"
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

node* makeNode(bookData book){
    node* newNode = new node;
    newNode -> data = book;
    newNode -> next = NULL;
    return newNode;
}

void inputBookInfor(bookData &book){
    cout << "Title: ";
    getline(cin, book.title);
    cout << "ID: ";
    getline(cin, book.ID);
    cout << "Author name: ";
    getline(cin, book.author);
    cout << "Language: ";
    getline(cin, book.language);
    cout << "Release year: ";
    cin >> book.year;
    cout << "Price: ";
    cin >> book.price;
    book.stolk++;
}

void pushBack(node* &head, bookData book){
    node* newNode = makeNode(book);
    if (head == NULL)
    {
        head = newNode;
        return;
    }
    node* tmp = head;
    while (tmp -> next != NULL)
    {
        tmp = tmp -> next;
    }
    tmp -> next = newNode;
}

bool checkExistBook(node* head, bookData book){
    node* tmp = head;
    if (head == NULL) return 0;
    while (tmp != NULL)
    {
        if (tmp -> data.title == book.title && tmp -> data.ID == book.ID && tmp -> data.author == book.author && tmp -> data.language == book.language && tmp -> data.year == book.year && tmp -> data.price == book.price) return 1;
        tmp = tmp -> next;
    }
    return 0;
}

bool isFileEmpty(string& filename) {
    ifstream file(filename);
    return file.peek() == ifstream::traits_type::eof();
}

int countElement(){
    ifstream input("database.txt");
    if (!input.is_open())
    {
        cout << "File does not exist";
        return -1;
    }
    int count = 0;
    string s;
    getline(input, s, '\0');
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '\n') count++;
    }
    input.close();
    return count;
}

void getInitInforFromFile(node* &head){
    ifstream input("database.txt");
    if (!input.is_open())
    {
        cout << "File does not exist";
        return;
    }
    input.ignore(100, '\n');
    int n = countElement();
    bookData *bookArr = new bookData[n];
    for (int i = 0; i < n; i++)
    {
        getline(input, bookArr[i].title, '|');
        getline(input, bookArr[i].ID, '|');
        getline(input, bookArr[i].author, '|');
        getline(input, bookArr[i].language, '|');
        input >> bookArr[i].year;
        input.ignore(2, '|');
        input >> bookArr[i].price;
        input.ignore(2, '|');
        input >> bookArr[i].stolk;
        input.ignore(2, '\n');
        pushBack(head, bookArr[i]);
    }
    input.close();
}

void printListToScreen(node* head){
    node* tmp = head;
    if (tmp == NULL) return;
    cout << "Title|ID|Author's name|Language|Release year|Price|Stolk level\n";
    do
    {
        cout << tmp -> data.title << '|';
        cout << tmp -> data.ID << '|';
        cout << tmp -> data.author << '|';
        cout << tmp -> data.language << '|';
        cout << tmp -> data.year << '|';
        cout << tmp -> data.price << '|';
        cout << tmp -> data.stolk << '\n';
        tmp = tmp -> next;
    }
    while (tmp != NULL);
}

void printListToFile(node* head){
    ofstream output("database.txt");
    if (!output.is_open())
    {
        cout << "File does not exist";
        return;
    }
    output << "Title|ID|Author's name|Language|Release year|Price|Stolk level\n";
    node* tmp = head;
    if (tmp == NULL) return;
    // use it to avoid the line 148 create a new line without content
    do
    {
        output << tmp -> data.title << '|';
        output << tmp -> data.ID << '|';
        output << tmp -> data.author << '|';
        output << tmp -> data.language << '|';
        output << tmp -> data.year << '|';
        output << tmp -> data.price << '|';
        output << tmp -> data.stolk;
        if (tmp -> next != NULL)
        {
            output << '\n';
        }
        tmp = tmp -> next;
    }
    while (tmp != NULL);
    output.close();
}
