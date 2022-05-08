/***************************************/
/* Accomplished by: Dhony Mark Mendoza */
/* Date: March 8, 2022                 */
/***************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct bookstoreDetails{
	char storeName[33];
	char address[65];
	char telephone[8];
}bsDetails;

typedef struct bookRecord{
	char bookID[9];
	char bookName[33];
	float price;
	int stocks;
	char shelf[5];
}bookRecord;

typedef struct bookNode{
	bookRecord bkRec;
	struct bookNode* nextBook;
}bookNode, *BookList;

typedef struct bookStore{
	bsDetails details;
	BookList bList;
	int count;
}bookStore;

typedef struct customerDetails{
	char custName[33];
	char telephone[8];
	char email[65];
}custDetails;

typedef struct personalBkNode{
	char bookName[33];
	struct personalBkNode* nextBk;
}personalBkNode, *PersonalBkList;

typedef struct custBkCollection{
	custDetails customer;
	PersonalBkList bkList;
	int count;
}custBkCollection;

/*THESE FUNCTIONS HAVE ALREADY BEEN WRITTEN FOR YOUR CONVENIENCE*/
void populateBookStore(bookStore*);
void displayCustBooks(custBkCollection);
void displayBooksInBS(bookStore);

/*Instructions: Write the code of the given function prototypes
				1) initBookStore() - Initializes a given bookstore
				2) findBook() - Given a bookstore and a book ID, the function will return 1 if the book is found in the bookstore
								and 0 if it is not in the bookstore.
				3) insertBookBS() - Function will insert a new book record into the bookstore if and only if the book record still does
									not exist in the bookstore. Also, the inserted record is inserted in its proper place in the booklist
									sorted in ascending order by book ID.
				4) deleteBooksNoStock() - Function will go through all the book records in a bookstore and delete any book record that 
										  has zero stocks.
				5) initCustBkCollection() - Initializes a customer's book collection.
				6) purchaseBook() - Function will go through the list of book records in a bookstore and check if the certain book the customer
									wants to purchase exists in the bookstore. If it does exist, insert that book into the customer's book collection
									if and only if the book still does not exist in the customer's collection. The book is inserted at the last
									part of the customer's collection. Do the necessary increments and decrements. Finally, if insertion was successful,
									call function deleteBooksNoStock() to remove any books in the bookstore that have no more stocks.
				*/
void initBookStore(bookStore*);
int findBook(bookStore, char[]);
void insertBookBS(bookStore*, bookRecord);
void deleteBooksNoStock(bookStore*);

custBkCollection initCustBkCollection();
void purchaseBook(bookStore*, custBkCollection*, char[]);

int main(void){
	/*Expected output: The list of books with their respective values should have been displayed based on the populate function*/
	bookStore NBS;
	initBookStore(&NBS);
	populateBookStore(&NBS);
	displayBooksInBS(NBS);
	getch();
	system("CLS");
	
	/*Expected output: Error messages: You already have this book in your collection and Book does not exist in the store should have been displayed.
					   Then, display Harry Potter Books 1-4.*/
	custBkCollection myBooks = initCustBkCollection();
	purchaseBook(&NBS, &myBooks, "HP000001");
	purchaseBook(&NBS, &myBooks, "HP000002");
	purchaseBook(&NBS, &myBooks, "HP000003");
	purchaseBook(&NBS, &myBooks, "HP000003");
	purchaseBook(&NBS, &myBooks, "HP000004");
	purchaseBook(&NBS, &myBooks, "HP000004");
	displayCustBooks(myBooks);
	getch();
	system("CLS");
	
	/*Expected output: Harry Potter Book 4 should have been deleted. HP Books 1, 2 and 3 should have 6, 3, and 5 stocks respectively*/
	displayBooksInBS(NBS);
	getch();
	system("CLS");
	
	return 0;
	
}

void populateBookStore(bookStore* BS){
	int i;
	bookRecord initialBooks[10] = { {"HP000001", "Harry Potter Book 1", 399.99, 7, "H001"},
									{"HP000002", "Harry Potter Book 2", 499.99, 4, "H001"},
									{"HP000003", "Harry Potter Book 3", 499.99, 6, "H001"},
									{"HP000004", "Harry Potter Book 4", 599.99, 1, "H001"},
									{"HP000005", "Harry Potter Book 5", 699.99, 3, "H001"},
									{"HP000006", "Harry Potter Book 6", 599.99, 4, "H001"},
									{"HP000007", "Harry Potter Book 7", 799.99, 5, "H001"},
									{"TL000001", "Twilight", 299.99, 2, "TW01"},
									{"TL000002", "New Moon", 399.99, 14, "TW01"},
									{"TL000003", "Eclipse", 399.99, 7, "TW01"} };	
	for(i = 0 ; i < 10; i++){
		insertBookBS(BS, initialBooks[i]);
	}
}

void initBookStore(bookStore* BS){
	BS->count = 0;
	BS->bList = NULL;
	strcpy(BS->details.storeName, "Dhony's Book Store");
}

int findBook(bookStore BS, char bookID[]){
	for(; BS.bList != NULL && strcmp(BS.bList->bkRec.bookID, bookID) != 0; BS.bList = BS.bList->nextBook){}
	return BS.bList != NULL ? 1 : 0;
}

void insertBookBS(bookStore* BS, bookRecord newBk){
	BookList *trav, temp;
	for(trav = &BS->bList; *trav != NULL && strcmp((*trav)->bkRec.bookID, newBk.bookID) < 0; trav = &(*trav)->nextBook){}
	temp = malloc(sizeof(bookNode));
	if(*trav == NULL){
		for(trav = &BS->bList; *trav != NULL && strcmp((*trav)->bkRec.bookID, newBk.bookID) < 0; trav = &(*trav)->nextBook){}
		if(temp != NULL){
			temp->bkRec = newBk;
			temp->nextBook = *trav;
			*trav = temp;
			BS->count++;
		}
	} else{
		printf("Book[%s] is already in the list.\n", newBk.bookID);
	}
}

void deleteBooksNoStocks(bookStore* BS){
	BookList *trav, temp;
	for(trav = &BS->bList; *trav != NULL && (*trav)->bkRec.stocks != 0; trav = &(*trav)->nextBook){}
	if(*trav != NULL){
		printf("%s has no stocks.\n", (*trav)->bkRec.bookName);
		BS->count--;
		temp = *trav;
		*trav = temp->nextBook;
		free(temp);
	}
}

void displayBooksInBS(bookStore BS){
	printf("Bookstore Name: %s\n\n", BS.details.storeName);
	printf("%-15s", "Book ID");	
	printf("%-25s", "Book Name");	
	printf("%-15s", "Book Price");	
	printf("%-15s", "Book Stock");
	printf("%-15s\n", "Book Shelf");
	for(; BS.bList != NULL; BS.bList = BS.bList->nextBook){
		printf("%-15s", BS.bList->bkRec.bookID);
		printf("%-25s", BS.bList->bkRec.bookName);
		printf("$%-15.2f", BS.bList->bkRec.price);
		printf("%-15d", BS.bList->bkRec.stocks);
		printf("%-15s\n", BS.bList->bkRec.shelf);
	}
	printf("\nTotal Book Count: %d", BS.count);
}

custBkCollection initCustBkCollection(){
	custBkCollection cb;
	cb.count = 0;
	cb.bkList = NULL;
	strcpy(cb.customer.custName, "Stacy");
	return cb;
}

void purchaseBook(bookStore* BS, custBkCollection* CBC, char bookID[]){
	BookList *trav, temp;
	PersonalBkList *cus;
	
	for(trav = &BS->bList; *trav != NULL && strcmp((*trav)->bkRec.bookID, bookID) != 0; trav = &(*trav)->nextBook){}
	if(*trav != NULL){
		for(cus = &CBC->bkList; *cus != NULL && strcmp((*cus)->bookName, (*trav)->bkRec.bookName) != 0; cus = &(*cus)->nextBk){}
		if(*cus == NULL){
			*cus = malloc(sizeof(bookNode));
			if(*cus != NULL){
				strcpy((*cus)->bookName, (*trav)->bkRec.bookName);
				(*cus)->nextBk = NULL;
			}
			CBC->count++;
			(*trav)->bkRec.stocks--;
			printf("Book[%s] has been purchased by: %s\n", bookID, CBC->customer.custName);
			deleteBooksNoStocks(BS);
		} else{
			printf("You already have this book [%s] in your collection and\n", bookID);
			printf("[%s] does not exist in the store should have been displayed.\n", bookID);
		}
	}
}

void displayCustBooks(custBkCollection CBC){
	PersonalBkList trav;
	
	printf("\n\nCustomer Name: %s\n\n", CBC.customer.custName);
	printf("Owned Books:\n", CBC.customer.custName);

	for(trav = CBC.bkList; trav != NULL; trav = trav->nextBk){
		printf("%s\n", trav->bookName);
	}
}
