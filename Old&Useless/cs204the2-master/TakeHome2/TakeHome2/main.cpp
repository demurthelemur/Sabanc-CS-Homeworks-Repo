#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//creating a struct for the linked list;
struct node{
    int data;
    node* next;
    
    node()
    : data(NULL), next(nullptr){
        
    };
    
    node(int val, node* nxt)
    : data(val), next(nxt){
        
    };
};

//Functions
string getString(string & input);
int itterrateList(node *head);
bool checkIfInList(node *head, int currentNum);
void deleteAscending(node *head, int newNum);
void deleteDescending(node *head, int searchValue);
void addEndOfList(node** head_ref, int newNum);
void ClearList(node *head);


int main(){
    string input;
    //gets the input from the user and finds if it is A for ascending or D for descending
    string sortingMethod = getString(input);
    //get the input for numbers from the user
    string numbers;
    cout << "Please enter the numbers in a line: ";
    getline(cin, numbers);
    //create the ifstream function for finding the seperate numbers
    istringstream iss (numbers);
    
    //create the head node
    node *head;
    head = nullptr;
    int num;
    //converting the string to seperate numbers
    while(iss>>num){
        //checking if the input is ascending or descending
        if(input == "A"){
            //checking if this number has been inserted to the node before
            if(checkIfInList(head, num)){
                cout << "This number is already in the list" << endl;
                continue;
            }
            //print the number that is going to be inserted into the list
            cout << "Next number: " << num << endl;
            //insert the node at the end of the list
            addEndOfList(&head, num);
            //print the deleted notes to insert the node
            cout << "Deleted nodes: ";
            //delete the numbers mentioned above
            deleteAscending(head, num);
            //print the number that has been added to the list
            cout << "Appended: " << num << endl;
            //print the list from the start
            cout << "List Content: " << itterrateList(head) << endl;;
            
        } else if(input == "D"){
            //checking if this number has been inserted to the node before
            if(checkIfInList(head, num)){
                cout << "This number is already in the list" << endl;
                continue;
            }
            //print the number that is going to be inserted into the list
            cout << "Next number: " << num << endl;
            //insert the node at the end of the list
            addEndOfList(&head, num);
            //print the deleted notes to insert the node
            cout << "Deleted nodes: ";
            //delete the numbers mentioned above
            deleteDescending(head, num);
            //print the number that has been added to the list
            cout << "Appended: " << num << endl;
            //print the list from the start
            cout << "List Content: " << itterrateList(head) << endl;;
        }
        
    }
    //Delete the remaining nodes at the end of the program
    if(numbers == ""){
        cout << "The list is empty at the end of the program and nothing is deleted" << endl;
    }
    cout << "All the nodes are deleted at the end of the program: ";
    ClearList(head);
    
    
    return 0;
}

string getString(string & input){
    //get the input as a string
    cout << "Please enter the order mode (A/D): ";
    getline(cin, input);
    //find the first input
    string firstInput = input.substr(0, input.find(' '));
    bool correctInput = false;
    //check if it is A or D
    if(firstInput == "A" || firstInput == "D"){
        correctInput = true;
    }
    // if not ask till it is A or D
    while(correctInput == false){
        cout << "Please enter the order mode again (A/D): ";
        getline(cin, input);
        string firstInput = input.substr(0, input.find(' '));
        if(firstInput == "A" || firstInput == "D"){
            correctInput = true;
        }
    }
    return firstInput;
}
/* BEGIN: CODE TAKEN FROM PTRFUNC.CPP (MODIFIED)*/
//iterate over the list printing all of the members
int itterrateList(node *head){
    //create a temporary node
    node *temp;
    temp = head;
    //iterate over the list
    while(temp != NULL){
        if(temp->data != 0){
            cout << temp->data << " ";
        }
        temp = temp->next;
    }
    return 0;
}

//check if the item is in the list works just like the iterrate list function
//only differance is the return bool type
bool checkIfInList(node *head, int currentNum){
    node *temp;
    temp = head;
    while(temp != NULL){
        if(temp->data == currentNum){
            return true;
        }
        temp = temp->next;
    }
    return false;
   
}
/* END: CODE TAKEN FROM PTRFUNC.CPP (MODIFIED)*/

//delete function for ascending list
void deleteAscending(node *head, int newNum){
    //if the list is empty delete nothing and print NULL
    if(head == NULL){
        cout << "NONE " << endl;
        return;
    }
    //if the head needs to be deleted delete the node and print the number
    else if(head->data > newNum){
        cout << head->data;
        head->data = newNum;
        head->next = NULL;
    } else{
        //if there is no problem with the head and the list is not empty itterate over the list
        node * temp = head;
        node * previous = NULL;
        //Stop if the number is bigger then the data in the data list
        while(temp->next != nullptr && temp->data < newNum){
            previous = temp;
            temp = temp->next;
        }
        //if at the end of the list delete nothing
        if(temp->next == NULL){
            cout << "NONE " << endl;
            return;
        }
        else{
            //else delete the whole rest of the list and print the numbers
            
            node * printNode = temp;
            while(printNode->next != nullptr){
                cout <<printNode->data << " " << endl;
                printNode = printNode->next;
            }
            previous = previous->next;
            previous->data = newNum;
            previous->next = nullptr;
            return;
        }
    }
    
}

//works the same way as the deleteAscending but checks for a bigger number
void deleteDescending(node *head, int newNum){
    if(head == NULL){
        cout << "NONE " << endl;
        return;
    }
    //if the head needs to be deleted delete the node and print the number
    else if(head->data < newNum){
        cout << head->data;
        head->data = newNum;
        head->next = NULL;
    } else{
        //if there is no problem with the head and the list is not empty itterate over the list
        node * temp = head;
        node * previous = NULL;
        //Stop if the number is smaller then the data in the data list
        while(temp->next != nullptr && temp->data > newNum){
            previous = temp;
            temp = temp->next;
        }
        //if at the end of the list delete nothing
        if(temp->next == NULL){
            cout << "NONE " << endl;
            return;
        }
        else{
            //else delete the whole rest of the list and print the numbers
            
            node * printNode = temp;
            while(printNode->next != nullptr){
                cout <<printNode->data << " " << endl;
                printNode = printNode->next;
            }
            previous = previous->next;
            previous->data = newNum;
            previous->next = nullptr;
            return;
        }
    }
}

void addEndOfList(node** headRef, int newNum){
    //creating all the nodes neccesarry
    node *temp = new node();
    node *last = *headRef;
    temp->data = newNum;
  
    //Making the last pointer first
    temp->next = NULL;
  
    //if the list is empty make the new node as head
    if (*headRef == NULL){
        *headRef = temp;
        return;
    }
  
    //find the last node
    while (last->next != NULL){
        last = last->next;
    }
    //change the last node to our new node
    last->next = temp;
    return;
}

/* BEGIN: CODE TAKEN FROM PTRFUNC.CPP (MODIFIED)*/
void ClearList(node *head)
{
    node *ptr;
    while(head!=NULL)
    {
        ptr=head;
        cout << head->data << " ";
        head=head->next;
        delete ptr;
    }
}
/* BEGIN: CODE TAKEN FROM PTRFUNC.CPP (MODIFIED)*/
