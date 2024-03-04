#include <string>
using namespace std;
struct bookData
{
    string title;
    string ID;
    string author;
    string language;
    int year;
    double price;
    int stolk = 0;
};

struct node
{   
    bookData data;
    node* next;
};

node* makeNode(bookData);
void pushBack(node*&, bookData);
void inputBookInfor(bookData&);
bool checkExistBook(node*, bookData);
bool isFileEmpty(string&);
int countElement();
void getInitInforFromFile(node*&);
void printListToScreen(node*);
void printListToFile(node*);
