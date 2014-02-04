#include "../include/Database.h"
#include <cmath>
#define INITIAL_SIZE 100000

using namespace std;

Database::Database()
{
    //ctorc
    theDatabase = new Node*[INITIAL_SIZE];

    capacity = INITIAL_SIZE;
    for(int i =0; i<capacity; ++i)
    {
        theDatabase[i] = nullptr;
    }

    sizeOfDatabase = 0;
}

Database::~Database()
{
    //dtor
    delete(theDatabase);
    theDatabase = nullptr;
    capacity = 0;
    sizeOfDatabase = 0;
}

// public

int Database::hashFunction(int key)
{
    int result = 0;
    int myIterator = 0;
    int pos = 0;
    if (key<0)
        return -1;

    pos = hashFunction(key, myIterator);
    while (theDatabase[pos]!=nullptr && theDatabase[pos]->getID()!=key)
        pos = hashFunction(key, ++myIterator);
    //cout << "pos=" << pos << endl;
    return pos;

}

int Database::hashFunction(int key, int iteration)
{
    return (auxHashFunction1(key)+iteration*auxHashFunction2(key))%capacity;
}

int Database::auxHashFunction1(int key)
{
    return key%capacity;
}

int Database::auxHashFunction2(int key)
{
    return 1+key%(capacity-1);
}


/* inserts a new Node to the Database Array
 * to the position to remain sorted
*/
bool Database::insertNewLink(int leftId, int rightId, int weight)
{
    bool toBeReturned = false;
    /*
    for (int i=0;i<=1;++i)
    {
        Node** resultNode = searchNodeByID(leftId);
        if (*resultNode == nullptr)
        {
            *resultNode = new Node(leftId);
        }
        toBeReturned = toBeReturned || (*resultNode)->addNewNode(rightId, weight);
        cout << **resultNode << endl;
        int temp = leftId;
        leftId = rightId;
        rightId = temp;
    }
    //cout << *theDatabase[21] << endl;
    return toBeReturned;
    */
    for (int i=0;i<=1;++i)
    {

        if (theDatabase[hashFunction(leftId)] != nullptr)
        {
            theDatabase[hashFunction(leftId)]->addNewNode(rightId, weight);
        }
        else
        {
            Node* nodeToInsert = new Node(leftId);
            ++(this->sizeOfDatabase);
            nodeToInsert->addNewNode(rightId, weight);
            theDatabase[hashFunction(leftId)] = nodeToInsert;
        }
        int temp = leftId;
        leftId = rightId;
        rightId = temp;

    }
    //cout << *theDatabase[hashFunction(leftId)] << endl;
    cout << *this << endl;
}


bool Database::deleteExistingLink(int leftId, int rightId)
{
    for (int i=0;i<=1;++i)
    {
        if (theDatabase[hashFunction(leftId)] != nullptr)
        {
            theDatabase[hashFunction(leftId)]->deleteNode(rightId);
        }
        int temp = leftId;
        leftId = rightId;
        rightId = temp;
    }
}



Node ** Database::searchNodeByID(int idToSearch)
{
    int res = hashFunction(idToSearch);
    cout << "res=" << res << endl;
    return &(theDatabase[res]);
}



