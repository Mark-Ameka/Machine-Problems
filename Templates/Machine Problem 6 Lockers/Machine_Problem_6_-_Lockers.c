#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LROWS 4
#define LCOLS 4
#define VACANT '-'
#define OCCUPIED 'X'
#define MAXITEMS 9		/* represents the max number of items inside each locker */

typedef struct{
	char studID[9];		/* default value of studID is "00000000" */
	char studName[65];  /* default value of studName is "UNOCCUPIED" */
	char course[5];		/* default value of course is "NONE" */
}Student;

typedef struct{
	int r;				/* default value is -1 */
	int c;				/* default value is -1 */
}LockerNumber;

typedef struct LNumNode{
	Student owner;					/* represents the student who owns the locker */
	LockerNumber lockerNum;			/* represents the locker number of the locker the student owns */
	struct LNumNode* nextLocker;
}LNumNode, *LNList;

typedef struct{
	char itemName[33];	/* default value is "XXX" */
	int qty;			/* default value is 0 */
}ItemDetails;

typedef struct ItemNode{
	ItemDetails item;
	struct ItemNode* nextItem;
}ItemNode, *ItemList;

typedef struct{
	Student owner;
	ItemList IL;			/* Linked list representation of all the items inside a certain locker */
	LockerNumber lockerNum;
	int numItems;			/* default value is 0 */
	char lockerStat;		/* default value is VACANT */
}Locker;

typedef struct{
	Locker lockList[LROWS][LCOLS];	/* 2D Array of Lockers */
	LNList lockerNumList;			/* Linked List containing ALL the currently occupied lockers in the 2D array of Lockers, SORTED in ascending order by the student's ID Number
									   This allows us to quickly find for a student's locker without having to go through the 2D array of Lockers. */
	int numOccupied;				/* default value is 0 */
}LockerList;

/* Completed Functions */
void pause(void);

/* Problem 1 */
void initLockerList(LockerList* L);
void displayLockerMap(LockerList L);
void displayLockerContents(LockerList L);

/* Problem 2 */
LockerNumber hasLocker(LNList LN, char idNum[9]);
int occupyLocker(Locker L[LROWS][LCOLS], LockerNumber LN, Student stud);
void insertLNList(LNList* L, LockerNumber LN, Student stud);
void rentLocker(LockerList* L, Student stud);

/* Problem 3 */
void depositItem(LockerList* L, Student stud, ItemDetails newItem);

/* Problem 4 */
ItemDetails retrieveItem(LockerList* L, Student stud);

/* Problem 5 */
void saveLockerEntries(LockerList* L);

int main(void)
{
	LockerList lockers;
	Student stud1 = {"14101941", "Cris Militante",	 "BSCS"};
	Student stud2 = {"14102020", "Patrick Woogue", "BSCS"};
	Student stud3 = {"14101943", "Gabriel Pineda", "BSCS"};
	ItemDetails item1 = {"Notebook", 3};
	ItemDetails item2 = {"Shoes", 1};
	ItemDetails item3 = {"Basketball", 1};
	ItemDetails item4 = {"Prog1 Book", 1};
	ItemDetails item5 = {"Calc Book", 1};
	
	/* Problem 1 */
	/* Instructions:
		1) Initialize variable lockers by calling the initLockerList() function.
		2) Call the displayLockerMap() function.
		3) Call the displayLockerContents() function.
		4) Call the pause() function.
	*/
	printf("Problem 1\n");
	initLockerList(&lockers);
	displayLockerMap(lockers);
	displayLockerContents(lockers);
	pause();
	
	/* Problem 2 */
	/* Instructions:
		1) Rent a locker for stud1 using the rentLocker() function.
		2) Rent a locker for stud2 using the rentLocker() function.
		3) Rent a locker for stud3 using the rentLocker() function.
		4) Rent a locker for stud2 using the rentLocker() function. This should fail since stud2 already has a locker.
		5) Call the displayLockerMap() function.
		6) Call the displayLockerContents() function.
		7) Call the pause() function.
	*/
	printf("Problem 2\n");
	rentLocker(&lockers, stud1);
	rentLocker(&lockers, stud2);
	rentLocker(&lockers, stud3);
	rentLocker(&lockers, stud2);
	displayLockerMap(lockers);
	displayLockerContents(lockers);
	pause();
	
	/* Problem 3 */
	/* Instructions:
		1)  Deposit item1 into stud1's locker using the depositItem() function.
		2)  Deposit item2 into stud1's locker using the depositItem() function.
		3)  Deposit item3 into stud1's locker using the depositItem() function.
		4)  Deposit item1 into stud1's locker using the depositItem() function. This should UPDATE the qty of the item. Does not insert a new item into the ItemList.
		5)  Deposit item3 into stud2's locker using the depositItem() function.
		6)  Deposit item2 into stud2's locker using the depositItem() function.
		7)  Deposit item4 into stud3's locker using the depositItem() function.
		8)  Deposit item1 into stud3's locker using the depositItem() function.
		9)  Deposit item3 into stud3's locker using the depositItem() function.
		10) Deposit item1 into stud1's locker using the depositItem() function. This should fail since there is not enough space in the locker.
		11) Call the displayLockerMap() function.
		12) Call the displayLockerContents() function.
		13) Call the pause() function.
	*/
	printf("Problem 3\n");
	depositItem(&lockers, stud1, item1);
	depositItem(&lockers, stud1, item2);
	depositItem(&lockers, stud1, item3);
	depositItem(&lockers, stud1, item1);
	depositItem(&lockers, stud2, item3);
	depositItem(&lockers, stud2, item2);
	depositItem(&lockers, stud3, item4);
	depositItem(&lockers, stud3, item1);
	depositItem(&lockers, stud3, item3);
	depositItem(&lockers, stud1, item1);
	displayLockerMap(lockers);
	displayLockerContents(lockers);
	pause();
	
	/* Problem 4 */
	/* Instructions:
		1) Retrieve an item from stud1's locker using the retrieveItem() function. Ignore the function's return value.
		2) Retrieve an item from stud2's locker using the retrieveItem() function. Ignore the function's return value.
		3) Retrieve an item from stud3's locker using the retrieveItem() function. Ignore the function's return value.
		4) Retrieve an item from stud1's locker using the retrieveItem() function. Ignore the function's return value.
		5) Call the displayLockerMap() function.
		6) Call the displayLockerContents() function.
		7) Call the pause() function.
	*/
	printf("Problem 4\n");
	retrieveItem(&lockers, stud1);
	retrieveItem(&lockers, stud2);
	retrieveItem(&lockers, stud3);
	retrieveItem(&lockers, stud1);
	displayLockerMap(lockers);
	displayLockerContents(lockers);
	pause();
	
	/* Problem 5 */
	/* Instructions:
		1) Save all of the items in all the lockers using the saveLockerEntries() function.
		5) Call the displayLockerMap() function.
		6) Call the displayLockerContents() function.
		7) Call the pause() function.
	*/
	printf("Problem 5\n");
	saveLockerEntries(&lockers);
	displayLockerMap(lockers);
	displayLockerContents(lockers);
	pause();
	
	return 0;
}


void pause(void)
{
	printf("\n\nPress any key to continue...");
	getch();
	system("CLS");
}


/***********************************************************************************************************************************************************
* initLockerList() = This function will initialize the LockerList by setting ALL of the fields 															   *
*					 within the LockerList (2D Array of Lockers, LNList, numOccupied) to be their default values. 										   * 
************************************************************************************************************************************************************/
void initLockerList(LockerList* L)
{

}


/***********************************************************************************************************************************************************
* displayLockerMap() = This function will display the 2D Array of Lockers inside the LockerList. 														   *
*					   If the lockerStat of a Locker inside the 2D Array is VACANT, display the VACANT character.										   *
*					   Else, display the number of items inside that Locker.																			   * 
*					   Finally, display the total number of occupied lockers over the TOTAl number of lockers											   *		
************************************************************************************************************************************************************/
void displayLockerMap(LockerList L)
{
	
}


/***********************************************************************************************************************************************************
* displayLockerContents() = This function will display the contents of ALL of the OCCUPIED Lockers in the LockerList 									   *
*					   		If there are no items inside the occupied locker, display "Locker is EMPTY.".												   *
*					   		Else, display all of the items inside that locker.																			   * 
*					   		Finally, display the total number of items inside each locker.										 						   *		
************************************************************************************************************************************************************/
void displayLockerContents(LockerList L)
{

}


/***********************************************************************************************************************************************************
* hasLocker() = This function will traverse through the LNList and check whether or not the student with the passed ID number already has a locker. 	   *
*				If the student has a locker, return the LockerNumber.																					   *			
*				Else, return a LockerNumber with values -1, and -1 and display the message "Student with ID Number: %s does not own a locker."			   *		
************************************************************************************************************************************************************/
LockerNumber hasLocker(LNList LN, char idNum[9])
{
	
}


/***************************************************************************************************************************************************************
* occupyLocker() = This function is used to occupy a Locker inside the 2D Array of Lockers.				 									   			       *
*				   The function will first check if the passed LockerNumber is valid.																	   	   *
*				   If the LockerNumber is valid, then check if the Locker with that LockerNumber is still VACANT.											   *
*				   If it is still VACANT, set the lockerStat to OCCUPIED, update the necessary fields, and display "Locker[%d][%d] is now ready for your use." *
*				   Finally, return 1 if you have successfully occupied a Locker. Else, return 0.															   *
*																																							   *
*				   The ff: error messages are to be displayed when the ff: scenarios are encountered:														   *
*				       -LockerNumber is invalid = "You have entered an invalid locker number."																   *
*				       -LockerNumber is already occupied = "Locker[%d][%d] is already occupied."		  								 					   *		
****************************************************************************************************************************************************************/
int occupyLocker(Locker L[LROWS][LCOLS], LockerNumber LN, Student stud)
{

}


/***********************************************************************************************************************************************************
* insertLNList() = This function will insert a new node containing the passed LockerNumber and Student into the LNList. 	  							   *
*				   The LNList is SORTED in ASCENDING order by studID, so make sure to insert the new node into its proper positing in the LNList		   *
************************************************************************************************************************************************************/
void insertLNList(LNList* L, LockerNumber LN, Student stud)
{

}


/***********************************************************************************************************************************************************
* rentLocker() = This function will make use of the 3 previous functions in order to allow a Student to rent a locker.	 	  							   *
*				 The function will first check if all of the lockers are not yet occupied.																   *
*				 If there are still available lockers, check if the passed Student does not yet have a Locker.											   *
*				 If the Student still does not yet own a locker, do the ff: until the Student successfully rents a Locker.								   *
*				     -Display the Locker Map.																											   *
*				     -Ask the user to input what locker he/she wants to rent.																			   *
*					 -Try to occupy the locker with that lockerNumber.																					   *
*					 -If the locker is successfully occupied, insert that lockerNumber into the LNList, and updated the total number of occupied lockers.  *
*																																						   *
*				 The ff: error messages are to be displayed when the ff: scenarios are encountered:														   *
*				       -Student already owns a locker = "%s already owns a locker!"																      	   *
*				       -There are no more vacant lockers = "Sorry there are no available lockers for you to rent!"										   *	
************************************************************************************************************************************************************/
void rentLocker(LockerList* L, Student stud)
{

}


/**************************************************************************************************************************************************************
* depositItem() = This function will store into the passed Student's locker the item that was passed.					 	  							      *
*				  The function first checks if the Student has a locker.																				      *
*				  If he/she does, then the function will check if there is still enough space inside the locker to store the item passed				      *
*				  If this is true, then the function will go through that Locker's items and see if the item already exists inside the Locker.			      *
*				  If the item already exists, then just update the qty of that item to be the sum of the old quantity, and the new quantity.			      *
*				  Else, insertFirst into the ItemList for that locker.																					      *
*				  Finally, update the numItems field of that Locker by adding its current value to the qty of the new item.								      *
*																																						      *
*				 The ff: error messages are to be displayed when the ff: scenarios are encountered:														      *
*				       -There is not enough space inside the locker to store the item passed = "There is not enough room in Locker[%d][%d] to fit the stuff!" *
***************************************************************************************************************************************************************/
void depositItem(LockerList* L, Student stud, ItemDetails newItem)
{

}


/**************************************************************************************************************************************************************
* retrieveItem() = This function will return the FIRST item in the ItemList for the passed Student's Locker.				 	  						      *
*				   The function first checks if the Student has a locker.																				      *
*				   If he/she does, then the function will check if there are items inside the Locker													      *
*				   If the locker isn't empty, then delete the FIRST item from the ItemList of that Locker, update the necessary fields,						  *
*				   and display message "Withdrew %dx qty of %s from %s's Locker"				    														  *
*				   Finally, return the deleted item to the calling function.																				  *
*																																							  *
*				   The ff: error messages are to be displayed when the ff: scenarios are encountered:														  *
*				       -There are no items inside the locker = "Locker[%d][%d] is empty." 																	  *
***************************************************************************************************************************************************************/
ItemDetails retrieveItem(LockerList* L, Student stud)
{

}


/**************************************************************************************************************************************************************
* saveLockerEntries() = This function will write into external files the items inside each student's lockers.				 	  						      *
*				   		The function will first traverse through the list of occupied lockers.															      *
*				   		For each locker in the list, keep calling the retrieveItem function until the locker is empty.									      *
*						Then, write each retrieved item into an external file with the name "ID Number's Locker.txt".										  *
*						After writing each item, print out the message "Writing item to file: %s".															  *
***************************************************************************************************************************************************************/
void saveLockerEntries(LockerList* L)
{

}
