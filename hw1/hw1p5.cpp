#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Item {
 	Item(int v, Item* n) {
 	 val = v;
 	 next = n; 
 	}
 	int val;
 	Item* next;
};

//function prototypes
Item* concatenate(Item* head1, Item* head2);
void _cHelper(Item* head1, Item* head2);

void _removeEvensHelper(Item* curr);
void removeEvens(Item*& head, Item *prev);

double _findAverageHelper(Item* head);
double findAverage(Item* head);

void readLists(Item*& head1, Item*& head2, string list1, string list2);

//concatenate helper
void _cHelper(Item* head3, Item* head2){
	//if there is still something in head 3, do nothing
	if(head3->next != NULL){
		_cHelper(head3->next, head2);
	}
	//if reached the end of head 3, link to head 2
	else if(head3->next == NULL)
		head3->next = head2;
}

Item* concatenate(Item* head1, Item* head2){
	//if given two empty lists
	if(head1==NULL && head2==NULL){
		return NULL;
	}
	//if given head2 as empty
	else if (head2==NULL){
		Item *head3 = head1;
		return head3;
	}
	//if given head1 as empty
	else if(head1==NULL){
		Item *head3 = head2;
		return head3;
	}
	//if given 2 full lists
	else{
		Item *head3 = head1;
		_cHelper(head3,head2);
		return head3;
	}
}

void _removeEvensHelper(Item* curr, Item *prev){
	//base case
	if(curr==NULL){
		return;
	}
	//if current is even and is the head with a next
	else if(curr->val%2==0 && prev==NULL){
		Item *temp = curr->next;
		delete curr;
		_removeEvensHelper(temp, prev);
	}
	//if current is even and in the middle of the list
	else if(curr->val%2==0 && prev!=NULL){
		Item *temp = curr->next;
		delete curr;
		prev->next = temp;
		curr = prev->next;
		_removeEvensHelper(curr, prev);
	}
	//if current is even and at the end of the list
	else if(curr->val%2==0 && curr->next==NULL){
		delete curr;
	}
	//if current is odd
	else
		_removeEvensHelper(curr->next, curr);
}

void removeEvens(Item*& head){
	//if given empty list
	if(head==NULL)
		return;
	else{
		//if only head in list is even
		if(head->val%2==0 && head->next==NULL){
			delete head;
		}
		//if only head in list is odd
		else if(head->val%2==1 && head->next==NULL){
			return;
		}
		//if head is even
		else if(head->val%2==0 && head->next!=NULL){
			Item* temp = head->next;
			delete head;
			head = temp;
			//next item
			Item *current = head;
			//original item
			Item *prevItem = NULL;
			_removeEvensHelper(current, prevItem);
		}
		//if head is not even
		else{
			Item *current = head->next;
			Item *prevItem = head;
			_removeEvensHelper(current, prevItem);
		}

	}
}

double _findAverageHelper(Item* head, int &ct){ //count is passed by ref
	if(head==NULL) //base case
		return 0;
	else{//increment count and add the value to total
		ct++;
		return head->val + _findAverageHelper(head->next, ct);
	}
}

double findAverage(Item* head){
	double total = 0; //to keep sum of values
	int count = 0; //to keep track of iterations
	if(head==NULL) //if empty
		return 0;
	else{
		total+=head->val;
		count++;
		total +=_findAverageHelper(head->next, count); //add values to total
		return total/count; //final average
	}
}

void readLists(Item*& head1, Item*& head2, string list1, string list2){
	
	stringstream ss1(list1);
	stringstream ss2(list2);

	int temp;
	ss1 >> temp;
	//check if temp returns valid number
	if(!ss1.fail()){
		head1 = new Item (temp, NULL);
		ss1 >> temp;
		if(!ss1.fail()){
			Item *nextItem = new Item(temp, NULL);
			head1->next = nextItem;
			ss1 >> temp;
			while(!ss1.fail()){
				//loop through until temp no longer works
				Item *n = new Item(temp, NULL);
				nextItem->next = n;
				nextItem = n;
				ss1 >> temp;
			}
		}
	}
	else
		head1=NULL;
	

	//same as about but for list 2
	int temp2;
	ss2 >>temp2;
	if(!ss2.fail()){
		head2 = new Item (temp2, NULL);
		ss2 >> temp2;
		if(!ss2.fail()){
			Item *nextItem2 = new Item(temp2, NULL);
			head2->next = nextItem2;
			ss2 >> temp2;
			while(!ss2.fail()){
				Item *n = new Item(temp2, NULL);
				nextItem2->next = n;
				nextItem2 = n;
				ss2 >> temp2;
			}
		}
	}
	else
		head2 = NULL;

	ss1.clear();
	ss2.clear();
}

void printList(std::ostream& ofile, Item* head)                                
{
  if(head == NULL)
    ofile << std::endl;
  else {
    ofile << head->val << " ";

    printList(ofile, head->next);    
  }
}

int main (int argc, char* argv[]){

	if(argc<2){
		cout << "Please enter an input file." << endl;
		return 0;
	}

	if(argc<3){
		cout << "Please enter an output file." << endl;
		return 0;
	}

	ifstream infile (argv[1]);
	
	string list1, list2;

	getline(infile, list1);
	getline(infile, list2);

	Item *head1 = NULL;
	Item *head2 = NULL;

	readLists(head1, head2, list1, list2);

	ofstream outfile (argv[2]);

	printList(outfile ,head1);
	printList(outfile, head2);

	Item *head3 = NULL;
	head3 = concatenate(head1, head2);
	printList(outfile, head3);

	removeEvens(head3);
	printList(outfile, head3);
	
	outfile << findAverage(head3) << endl;

	infile.close();
	outfile.close();

	//deallocate memory
	while(head1->next!=NULL){
		Item* temp = head1->next;
		delete head1;
		head1 = temp;
	}

	while(head2->next!=NULL){ 
		Item* temp = head2->next;
		delete head2;
		head2 = temp;
	}

	while(head3->next!=NULL){
		Item* temp = head3->next;
		delete head3;
		head3 = temp;
	}

	delete head1;
	delete head2;
	delete head3;
	
	return 0;
}