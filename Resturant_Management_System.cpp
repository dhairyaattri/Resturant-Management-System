#include <string.h>
#include <iostream>
using namespace std;

class Node
{   
    public:
    char foodName[50];
    int quantity;
    float price;
    int data;
    Node *next;
    Node *prev;
    Node(int data){
        this ->data = data;
        next = prev = NULL;
    }
};

Node *headC = NULL, *newNode, *tailC = NULL;
Node *headA = NULL, *tailA = NULL;
Node *headS;

void adminMenu()
{   
    cout << "\n\t\t\t\t\t\t1. View total sales\n";
    cout << "\n\t\t\t\t\t\t2. Add new items in the order menu\n";
    cout << "\n\t\t\t\t\t\t3. Delete items from the order menu\n";
    cout << "\n\t\t\t\t\t\t4. Display order menu\n";
    cout << "\n\t\t\t\t\t\t5. Back to main menu \n\n";
    cout << "\n\t\t\t\t\t\t   Enter your choice ->  ";
}

void customerMenu()
{
    cout << "\n\t\t\t\t\t\t\t1. Place your order\n";
    cout << "\t\t\t\t\t\t\t2. View your ordered items\n";
    cout << "\t\t\t\t\t\t\t3. Delete an item from order\n";
    cout << "\t\t\t\t\t\t\t4. Display final bill\n";
    cout << "\t\t\t\t\t\t\t5. Back to main menu \n\n";
    cout << "\n\t\t\t\t\t\t   Enter your choice ->  ";
}

Node *createAdmin(Node *head, int data, char foodName[25], float price)
{
    Node *newNode = new Node(data);

    newNode->data = data;
    newNode->price = price;
    newNode->quantity = 0;
    strcpy(newNode->foodName, foodName);
    newNode->next = NULL;
    newNode->prev = NULL;

    Node *temp = head;

    if (temp == NULL)
        headA = tailA = newNode;
    else
    {
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
        newNode->prev = tailA;
        tailA = newNode;
    }

    return headA;
}

Node *createCustomer(Node *head, int data, int quantity)
{
    Node *newNode = new Node(data);

    Node *temp1 = headA;
    int flag = 0;
    while (temp1 != NULL)
    {
        if (temp1->data == data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if (flag == 1)
    {
        newNode->data = data;
        newNode->price = quantity * (temp1->price);
        newNode->quantity = quantity;
        strcpy(newNode->foodName, temp1->foodName);
        newNode->next = NULL;
        newNode->prev = NULL;

        Node *temp = head;

        if (temp == NULL)
            headC = tailC = newNode;
        else
        {
            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newNode;
            newNode->prev = tailC;
            tailC = newNode;
        }
    }
    else
    {   
        cout << "\n\t\t\t\t\t\t\tThis item is not present in the menu!\n";
    }
    return headC;
}

void displayList(Node *head)
{
    Node *temp1 = head;
    if (temp1 == NULL)
    {   
        cout << "\n\t\t\t\t\t\t\t\tList is empty!!\n\n";
    }
    else
    {
        cout << "\n";
        while (temp1 != NULL)
        {
            if (temp1->quantity == 0)
                cout << "\t\t\t\t\t\t\t" << temp1->data << "\t" << temp1->foodName << "\t" << temp1->price << "\n";
            else
            {
                cout << "\t\t\t\t\t\t\t" << temp1->data << "\t" << temp1->foodName << "\t" << temp1->price << "\n";
            }

            temp1 = temp1->next;
        }
        cout << "\n";
    }
}

Node *totalSales(int data, int quantity)
{
    Node *newNode = new Node(data);
    int flag = 0;

    Node *temp1 = headA;
    while (temp1->data != data)
    {
        temp1 = temp1->next;
    }

    newNode->data = data;
    newNode->price = quantity * (temp1->price);
    newNode->quantity = quantity;
    strcpy(newNode->foodName, temp1->foodName);
    newNode->next = NULL;
    newNode->prev = NULL;

    Node *temp = headS;

    if (temp == NULL)
        headS = newNode;
    else
    {
        while (temp->next != NULL)
        {
            if (temp->data == data)
            {
                flag = 1;
                break;
            }
            temp = temp->next;
        }

        if (flag == 1)
        {
            temp->quantity += newNode->quantity;
            temp->price += newNode->price;
        }
        else
        {
            temp->next = newNode;
        }
    }

    return headS;
}

void calculateTotalSales()
{
    Node *temp = headC;
    while (temp != NULL)
    {
        headS = totalSales(temp->data, temp->quantity);
        temp = temp->next;
    }
}

Node *del(int data, Node *head, Node *tail)
{
    if (head == NULL)
    {
        cout << "\n\t\t\t\t\t\t\tList is empty\n";
    }
    else
    {
        Node *temp;
        if (data == head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            free(temp);
        }
        else if (data == tail->data)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while (data != temp->data)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}

int deleteAdmin()
{
    cout << "\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin >> num;

    Node *temp = headA;
    while (temp != NULL)
    {
        if (temp->data == num)
        {
            headA = del(num, headA, tailA);
            return 1;
        }
        temp = temp->next;
    }

    return 0;
}

int deletecustomer()
{
    cout << "\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin >> num;

    Node *temp = headC;
    while (temp != NULL)
    {
        if (temp->data == num)
        {
            headC = del(num, headC, tailC);
            return 1;
        }
        temp = temp->next;
    }

    return 0;
}

void displayBill()
{
    displayList(headC);
    Node *temp = headC;
    float totalPrice = 0;
    while (temp != NULL)
    {
        totalPrice += temp->price;
        temp = temp->next;
    }

    cout << "\t\t\t\t\t\t\tTotal price: " << totalPrice << "\n";
}

Node *deleteList(Node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        Node *temp = head;
        while (temp->next != 0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}

void admin()
{
    cout << "\n\t\t\t\t\t   ----------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t    ADMIN SECTION\n";
    cout << "\t\t\t\t\t   ----------------------------------------------\n";
    while (1)
    {
        adminMenu();

        int opt;
        cin >> opt;

        if (opt == 5)
            break;

        switch (opt)
        {
        case 1:
        {
            displayList(headS);
            break;
        }
        case 2:
        {

            cout << "\n\t\t\t\t\t\t\tEnter serial no. of the food item: ";
            int num, flag = 0;
            char name[50];
            float price;
            cin >> num;

            Node *temp = headA;

            while (temp != NULL)
            {
                if (temp->data == num)
                {
                    cout << "\n\t\t\t\t\t\tFood item with given serial number already exists!!\n\n";
                    flag = 1;
                    break;
                }
                temp = temp->next;
            }

            if (flag == 1)
                break;

            cout << "\t\t\t\t\t\t\tEnter food item name: ";
            cin >> name;
            cout << "\t\t\t\t\t\t\tEnter price: ";
            cin >> price;
            headA = createAdmin(headA, num, name, price);
            cout << "\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n";
            break;
        }
        case 3:
        {
            if (deleteAdmin())
            {
                cout << "\n\t\t\t\t\t\t### Updated list of food items menu ###\n";
                displayList(headA);
            }
            else
                cout << "\n\t\t\t\t\t\tFood item with given serial number doesn't exist!\n\n";

            break;
        }
        case 4:
        {
            cout << "\n\t\t\t\t\t\t\t\t   ### Order Menu ###\n";
            displayList(headA);
            break;
        }

        default:
        {
            cout << "\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n";
            break;
        }
        }
    }
}

void customer()
{
    int flag = 0, j = 1;
    char ch;
    cout << "\n\t\t\t\t\t   ----------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t    CUSTOMER SECTION\n";
    cout << "\t\t\t\t\t   ----------------------------------------------\n";
    while (1)
    {
        customerMenu();

        int opt;
        cin >> opt;

        if (opt == 5)
            break;

        switch (opt)
        {
        case 1:
            displayList(headA);
            cout << "\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ";
            int n;
            cin >> n;
            cout << "\t\t\t\t\t\tEnter quantity: ";
            int quantity;
            cin >> quantity;
            headC = createCustomer(headC, n, quantity);
            break;
        case 2:
            cout << "\n\t\t\t\t\t\t\t  ### List of ordered items ###\n";
            displayList(headC);
            break;
        case 3:
            if (deletecustomer())
            {
                cout << "\n\t\t\t\t\t\t### Updated list of your ordered food items ###\n";
                displayList(headC);
            }
            else
                cout << "\n\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n";
            break;
        case 4:
            calculateTotalSales();
            cout << "\n\t\t\t\t\t\t\t  ### Final Bill ###\n";
            displayBill();
            headC = deleteList(headC);
            cout << "\n\t\t\t\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t";
            fflush(stdin);
            ch = fgetc(stdin);
            flag = 1;
            break;

        default:
            cout << "\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n";
            break;
        }
        if (flag == 1)
            break;
    }
}

void mainMenu()
{
    cout << "\n                                 **************************************************************************\n";
    cout << "                                                     WELCOME TO RESTAURANT MANAGEMENT SYSTEM\n";
    cout << "                                 **************************************************************************\n\n\n";
    cout << "\t\t\t\t\t\t\t1. ADMIN SECTION\n";
    cout << "\t\t\t\t\t\t\t2. CUSTOMER SECTION\n";
    cout << "\t\t\t\t\t\t\t3. Exit\n\n";
    cout << "\t\t\t\t\t\t\tEnter your choice: ";
}

int main()
{
    headA = createAdmin(headA, 1, "Hot and Sour Soup ", 100);
    headA = createAdmin(headA, 2, "Manchow Soup      ", 200);
    headA = createAdmin(headA, 3, "Manchurian Noodles", 150);
    headA = createAdmin(headA, 4, "Fried Rice        ", 180);
    headA = createAdmin(headA, 5, "Hakka Noodles     ", 80);

    while (1)
    {
        mainMenu();
        int choice;
        cin >> choice;

        if (choice == 3)
        {
            cout << "\n\n\t\t\t\t\t\t\t**********Thank you!!**********\n";
            break;
        }

        switch (choice)
        {
        case 1:
            admin();
            break;
        case 2:
            customer();
            break;
        case 3:
            break;

        default:
            cout << "\n\t\t\t\t\t\tWrong Input !! Please choose valid option\n";
            break;
        }
    }
}