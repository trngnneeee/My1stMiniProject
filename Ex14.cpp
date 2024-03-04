#include <iostream>
#include "Ex14.h"
#include <fstream>
#include <string>
using namespace std;

int main(){
    string fileName = "database.txt";
    if (isFileEmpty(fileName))
    {
        ofstream output("database.txt");
        if (!output.is_open())
        {
            cout << "File does not exist";
            return 1;
        }
        output << "Title|ID|Author's name|Language|Release year|Price|Stolk level";
        output.close();
    }
    node* head = NULL;
    getInitInforFromFile(head);

    int choice;
    do
    {
        cout << "1. Enter information for a book\n";
        cout << "2. Show book list\n";
        cout << "3. Purchase book\n";
        cout << "4. Find book\n";
        cout << "5. Remove all book whose stock level is greater than k\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
            case 1:
            {
                bookData book;
                inputBookInfor(book);
                if (checkExistBook(head, book))
                {
                    node* tmp = head;
                    while (tmp != NULL)
                    {
                        if (tmp -> data.title == book.title)
                        {
                            tmp -> data.stolk++;
                            break;
                        }
                        tmp = tmp -> next;
                    }
                }
                if (!checkExistBook(head, book)) pushBack(head, book);
                cout << "\n";
            }
            break;
            case 2:
            {
                printListToScreen(head);
            }
            break;
            case 3:
            {
                string tmpID;
                cout << "Enter ID of book want to buy: ";
                getline(cin, tmpID);
                node* tmp = head;
                if (head == NULL) cout << "OUT OF STOCK!\n";
                else
                {
                    while (tmp != NULL)
                    {
                        if (tmp -> data.ID == tmpID)
                        {
                            if (tmp -> data.stolk == 0) cout << "OUT OF STOCK\n";
                            else 
                            {
                                tmp -> data.stolk--;
                                std:: cout << "Purchasing successfully!\n";
                                break;
                            }
                        }
                        tmp = tmp -> next;
                    }
                }
            }
            case 4:
            {
                string tmpName;
                cout << "Enter the book's name: ";
                getline(cin, tmpName);
                if (head == NULL) break;
                node* tmp = head;
                while (tmp != NULL)
                {
                    if (tmp -> data.title == tmpName)
                    {
                        cout << "Your book: " << tmp -> data.title << "|" << tmp -> data.ID << "\n";
                        break;
                    }
                    tmp = tmp -> next;
                }   
                if (tmp == NULL) cout << "Book doesn't exist\n";
            }
            break;
            case 5:
            {
                int k;
                cout << "Enter k: ";
                cin >> k;
                node* tmp = head;
                node* pre = NULL;
                if (head == NULL) break;
                while (tmp != NULL)
                {
                    if (tmp -> data.stolk > k)
                    {
                        node* tmp1 = tmp;
                        tmp = tmp -> next;
                        pre -> next = tmp;
                        delete tmp1;
                        continue;
                    }
                    tmp = tmp -> next;
                }
            }
            break;
            case 0:
            {
                cout << "Thank you for using our service!\n";
            }
            break;
        }
    }   
    while (choice != 0);
    printListToFile(head);
    return 0;   
}