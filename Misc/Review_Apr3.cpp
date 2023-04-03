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

int main()
{
    GroceryList gList;
    Item i;

    cout << "Enter the grocery name and quantity: " << endl;
    while(cin >> i.name >> i.quantity)
    {
        gList.getList().push_back(i);    
    }

    int listSize = gList.getListSize();
    for(int i = 0; i < listSize; i++)
    {
        cout << "Groceries: " << gList.getListItem(i).name << '\t' << gList.getListItem(i).quantity << endl;
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