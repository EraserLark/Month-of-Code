#include <iostream>
#include <vector>

using namespace std;

struct Item{
    string name;
    int quantity;
};

class GroceryList{
    public:
        vector<Item>& getList();
        Item& getListItem(int);
        int getListSize();
    private:
        vector<Item> list;
};

void sortList(vector<Item>&);

int main()
{
    GroceryList gList;
    Item i;

    cout << "Enter the grocery name and quantity: " << endl;
    while(cin >> i.name >> i.quantity)
    {
        gList.getList().push_back(i);    
    }

    //sort list
    sortList(gList.getList());

    int listSize = gList.getListSize();
    for(int i = 0; i < listSize; i++)
    {
        cout << "Groceries: " << gList.getListItem(i).name << '\t' << gList.getListItem(i).quantity << endl;
    }
}

void sortList(vector<Item>& grocList)
{
    //Selection Sort
    Item temp;

    for(int i = 0; i < grocList.size(); i++)
    {
        int jIndex = i;
        temp = grocList[i];

        for(int j = i; j < grocList.size(); j++)
        {
            if(grocList[j].name < temp.name)
            {
                temp = grocList[j];
                jIndex = j;
            }
        }

        grocList[jIndex] = grocList[i];
        grocList[i] = temp;
    }
}

vector<Item>& GroceryList::getList()
{
    return list;
}

Item& GroceryList::getListItem(int i)
{
    return list[i];
}

int GroceryList::getListSize()
{
    return list.size();
}