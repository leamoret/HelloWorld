#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

struct Item {
	Item(int v, Item* n) {val = v; next = n; }
	int val;
	Item* next;
};

Item* concatenate(Item* head1, Item* head2);
Item* helper_concatenate(Item* head, Item* curr);
void removeEvens(Item*& head);
Item* helper_remove(Item* head);
double findAverage(Item* head);
double helper_sum(Item* head, double sum);
double helper_amount(Item* head, double amount);
void readLists (Item*& head1, Item*& head2, char* file); 
void printList(std::ostream& ofile, Item* head);
void delete_list(Item* head);


int main (int argc, char* argv[2]) {
	ofstream ofile;
	ofile.open(argv[2]);
	Item* h1 = NULL;
	Item* h2 = NULL;
	readLists(h1, h2, argv[1]);
	ostringstream l1, l2, l3, l4, l5;
	printList(l1, h1);
	printList(l2, h2);
	Item* head3 = concatenate(h1, h2);
	printList(l3, head3);
	ofile << l3.str() << endl;
	removeEvens(head3);
	printList(l4, head3);
	ofile << l4.str() << endl;
	ofile << findAverage(head3) << endl;
	printList(l5, head3);
	ofile << l5.str() << endl;
	
	while(h1!=NULL)  {
		Item* del = h1->next;
		delete h1; 
		h1 = del;
	} 

	while(h2!=NULL)  {
		Item* del = h2->next;
		delete h2;
		h2 = del;
	} 

	while(head3!=NULL) {
		Item* del = head3->next;
		delete head3;
		head3 = del;
	} 	
		
}

void printList(std::ostream& ofile, Item* head)
{
	if(head == NULL) {
		ofile << std::endl;
	}
	else {
		ofile << head->val << " ";
		printList(ofile, head->next);
	}
}

void readLists (Item*& head1, Item*& head2, char* file) 
{ 
	ifstream myfile (file);
	if (myfile.fail()) {
		return;
	}
	else {
		// get lists from file 
		string list1;
		string list2;
		getline(myfile, list1);
		getline(myfile, list2);
		stringstream ss1;
		stringstream ss2;
		ss1 << list1;
		ss2 << list2;
		// create a linked list 
		int number1;
		int number2;	
		while (ss1 >> number1) {
			if(head1 == NULL) {			
				head1 = new Item(number1, NULL);
			}
			else {
				Item* tail = head1;
				while (tail->next != NULL) {
					tail = tail->next;
				}
				tail->next = new Item(number1, NULL);
				tail = tail->next;
			}
		}
		while (ss2 >> number2) {
			if(head2 == NULL) {			
				head2 = new Item(number2, NULL);
			}
			else {
				Item* tail = head2;
				while (tail->next != NULL) {
					tail = tail->next;
				}
				tail->next = new Item(number2, NULL);
			}
		}
	}
}

Item* concatenate(Item* head1, Item* head2)
{
	helper_concatenate(head2, head2);
	helper_concatenate(head2, head1);
}
 
Item* helper_concatenate(Item* head, Item* curr)
{
	if (curr == NULL) {
		return head;
	}
	else {
		return new Item (curr->val, helper_concatenate(head, curr->next));
	}
}

void removeEvens(Item*& head)
{	
	head = helper_remove(head);
}

Item* helper_remove(Item* head)
{
	if(head == NULL) {
		return NULL;
	}

	if((head->val)%2 == 0) {
		Item* temp = head->next;
		delete head;
		return helper_remove(temp);
	}

	head->next = helper_remove(head->next);
	return head;
	
}
double findAverage(Item* head)
{
	double i_sum = 0;
	double i_amount = 0;
	double sum = helper_sum(head, i_sum);
	double amount = helper_amount(head, i_amount);
	return (sum/amount);
}

double helper_sum(Item* head, double sum)
{
	if (head == NULL) 
		return sum;
	else {
		sum += head->val;
		return helper_sum(head->next, sum);
	}
}

double helper_amount(Item* head, double amount)
{
	if (head == NULL) 
		return amount;
	else {
		amount ++;
		return helper_amount(head->next, amount);
	}
}

