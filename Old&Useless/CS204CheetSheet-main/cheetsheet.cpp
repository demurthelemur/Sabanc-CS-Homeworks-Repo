vector<vector< type >> matrix_variable_name(rows, vector<int>(cols, init_value));   //Matrix definition
int * pa = new int[100]; //dynamic array 
struct node	  //example node for dynamic array
{
	string 	word;
	node 	*next;  //  pointer for the next node
};
node *  p = new node;
//constructor with initilizator list
  node::node(int n, string w, node * p)
		   : num(n),word(w),next(p)
  {};
//Printing a list
ptr = head;
while (ptr != NULL) 
{
    cout << ptr ->info << endl;
    ptr = ptr->next;
}
//Adding a node to the end of list
void Add2End(node * tail, int id)
{
   node *nn = new node(id, NULL);
   tail->next = nn;
}

//building a linked list
int storage[] = {1,2,3,4};
node *head = NULL;
node *temp = NULL;

for (int k=0; k < 4; k++)  
{
	temp = new node();
	temp->info = storage[k];
	temp->next = head;
	head = temp;
}

//delete list
void DeleteList (node *head) {		
  node *temp;				
  while (head != NULL) {				
      temp = head->next;			
      delete head;
      head = temp;
  }
}

//Adding a node to a sorted list
node * AddInOrder(node * head, int newkey){
   node *  ptr = head; 
    if (head == NULL || newkey < head->info)        
    {   
		node * temp = new node;   
		temp->info = newkey;
		temp->next = head; 
		return temp;
    }
    while (ptr->next != NULL && ptr->next->info < newkey)    {    
		ptr = ptr->next;
    }
	node * temp = new node; 
	temp->info = newkey;
	temp->next = ptr->next;
	ptr->next = temp;
	return head;
}

//Deleting a single node
void DeleteOneNode (node * toBeDeleted, node * & head){
	node * ptr;
	if (toBeDeleted == head) {     
        head = head->next;
		delete toBeDeleted;
	}
	else{     
        ptr = head;
		while (ptr->next != toBeDeleted)
		ptr = ptr->next;
		ptr->next = toBeDeleted->next;
		delete toBeDeleted;
	}
}

//Circular list
int countCircular (node * last){
	if (last == NULL)
		return 0; 
	
	int count = 0;
	node * ptr = last;
	do {
		count++;
		ptr = ptr->next;
	} while (ptr != last);
	return count;
}

// 2D dynamic array with 1D array
data = new int [rows * columns];
data[x,y] is found using data[x*columns+y];

//desturctor for linked list
LinkedList::~LinkedList ()
{
	node * ptr = head;
	while (ptr != NULL) 
	{
		 node * temp = ptr->next;
		 delete ptr;
		 ptr = temp;
	}
}

//deep copy constructor:
LinkedList::LinkedList (const LinkedList & copy)
{
	head = copy.createClone();
	size = copy.size;
}
node * LinkedList::createClone () const
{
	if (head == NULL)  
		return NULL;   
	
	node * headClone = new node (head->info, NULL);
	node * ptr = head->next; 
	node * ptrClone = headClone; 
   while (ptr != NULL) 
	{
		ptrClone->next = new node (ptr->info, NULL);
		ptr = ptr->next;
		ptrClone = ptrClone->next;
	}
	return headClone;
}

//Operator Overloading
Return_Type  classname::operator Operator_Symbol (parameters)

//Asignment operator
const LinkedList & LinkedList::operator = (const LinkedList & rhs)
{
	if (this != &rhs)
	{
		deleteList(); 
		head = rhs.createClone();
		size = rhs.size;
	}
	return *this;
}

ostream &     operator << 	(ostream & os, const ClockTime & ct);
istream &      operator >>    (istream & is, ClockTime & ct);

ClockTime    operator + 	(const ClockTime & lhs, const ClockTime & rhs);

bool 	operator == 	(const ClockTime& lhs, const ClockTime& rhs);
bool 	operator !=  	(const ClockTime& lhs, const ClockTime& rhs);
bool 	operator <   	(const ClockTime& lhs, const ClockTime& rhs);
bool 	operator >  	(const ClockTime& lhs, const ClockTime& rhs);
bool 	operator <=  	(const ClockTime& lhs, const ClockTime& rhs);
bool 	operator >=  	(const ClockTime& lhs, const ClockTime& rhs);

//Overloading I/O
istream &  operator >> (istream & is, ClockTime & ct)
{	
	is >> ct.myHours >> ct.myMinutes >> ct.mySeconds;			ct.Normalize();	
	return is;
}



