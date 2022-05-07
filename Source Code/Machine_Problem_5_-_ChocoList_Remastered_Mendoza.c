/***************************************/
/* Accomplished by: Dhony Mark Mendoza */
/* Date: March 7, 2022                 */
/***************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  NAME_SIZE  30
#define  ARRAY_SIZE  15
#define  ID_SIZE     10
#define  CHOCO_SIZE 15

 typedef struct {
 	char name[NAME_SIZE];  /* Chocolate name */  
 	int  weight;          /*  Chocolate weight in grams */
}ChocoDesc;
 
typedef struct {
  char chocoID[ID_SIZE];   /*  product ID, uniquely identifies each product */ 
  ChocoDesc chocoDesc;     /*  product description*/  
  float chocoPrice;        /*  product price*/  
  int chocoQty;            /* product count or quantity  */
}Chocolate;                 /* product record */

typedef struct ChocoNode{
   Chocolate chocoProd;
   struct ChocoNode* nextChoco;          /* Actual number of choco records in the array */               
}ChocoNode, *CLL;              /*  Definition of the ADT List */  

typedef struct{
	CLL choco;				/* Linked list of chocolate records. */
	int numChoco;			/* Total number of chocolates in the list */
}ChocoList;

/**********************************************************
 * Function Prototypes                                    *
 *********************************************************/
 
void pause(void);

/* Problem 1 */
ChocoList initChocoList(void);
void generateChocoRecords(void);
void populateChocoList(ChocoList* CL);
void displayChocoList(ChocoList CL, char listDesc[]);

/* Problem 2 */
void insertLastUnique(ChocoList *CL, Chocolate X);

/* Problem 3 */
void insertSortedName(ChocoList *CL, Chocolate X);
ChocoList populateSorted(ChocoList CL);

/* Problem 4 */
int deleteAllChoco(ChocoList *CL, char chocoName[]);

/* Problem 5 */
void sortChocoList(ChocoList CL);

int main(void){	
    ChocoList A, B;           /* Unsorted List variables */
    ChocoList sortedList;     /* Sorted list variable */
    Chocolate uniqueChoco1 = {"CR1388", {"Crunch", 50}, 88, 88};
    Chocolate uniqueChoco2 = {"CR1399", {"Crunch", 100}, 159, 159};
    Chocolate duplicateChoco =	{"KI1201", {"Kitkat", 75}, 99.99, 99};
    int count; 
    char deletedChoco_01[NAME_SIZE] = "Toblerone";
    char deletedChoco_02[NAME_SIZE] = "Ferrero";
  	generateChocoRecords();
  
/* Problem 1
	Instructions:
	 1) Initialize ChocoList A by calling initChocoList().
	 2) Populate ChocoList A by calling populateChocoList().
	 3) Display the contents of A by calling displayChocoList(). Pass "A (unsorted)" as the list description.
	 4) Call the pause() function.
*/
	printf("Problem 1\n");
	A = initChocoList();
	populateChocoList(&A);
	displayChocoList(A, "A (unsorted)");
 	pause(); 
  

/* Problem 2
	Instructions:
	 1) Call insertLastUnique() passing A and uniqueChoco1 as parameters.
	 2) Call insertLastUnique() passing A and duplicateChoco as parameters.
	 3) Call insertLastUnique() passing A and uniqueChoco2 as parameters.
	 4) Display the contents of A by calling displayChocoList(). Pass "A (unsorted)" as the list description.
	 5) Call the pause() function.
*/
	printf("Problem 2\n");
	insertLastUnique(&A, uniqueChoco1);
	insertLastUnique(&A, duplicateChoco);
	insertLastUnique(&A, uniqueChoco2);
	displayChocoList(A, "A (unsorted)");
    pause();

/* Problem 3
	Instructions:
	 1) Populate sortedList by calling populateSorted() function, and passing A as the parameter.
	 2) Display the contents of A by calling displayChocoList(). Pass "A (Sorted List)" as the list description.
	 3) Call the pause() function.
*/
 	printf("Problem 3\n");
 	sortedList = populateSorted(A);
	displayChocoList(sortedList, "A (Sorted List)");
 	pause();
	
/* Problem 4
	Instructions:
	 1) Call the deleteAllChoco() function, passing A and deletedChoco_01 as parameters.
	 2) Call the deleteAllChoco() function, passing A and deletedChoco_02 as parameters.
	 3) Display the contents of A by calling displayChocoList(). Pass "A (After deletion)" as the list description.
	 4) Call the pause() function.
*/	 
	printf("Problem 4\n");
	deleteAllChoco(&A, deletedChoco_01);
	deleteAllChoco(&A, deletedChoco_02);
	displayChocoList(A, "A (After deletion)");
    pause();
	     
 
/*---------------------------------------------------------------------------------
 * 	Problem #5 ::  Initialize and populate an unsorted chocoList B, then arrange   *
 *                 the choco records of chocoList B in ascending order according   *
 *                 to ID by calling arrangeChocoID. Display the list by calling    *
 *                 displayList() BEFORE and AFTER the call to arrangeChocoID().    *                                               *
 *  printf("\n\n\nProblem #5:: ");                                                 *
 *---------------------------------------------------------------------------------*/
/* Problem 5
	Instructions:
	 1) Initialize ChocoList B by calling initChocoList().
	 2) Populate ChocoList B by calling populateChocoList().
	 3) Display the contents of B by calling displayChocoList(). Pass "B (unsorted)" as the list description.
	 4) Sort ChocoList B by calling the sortChocoList() function.
	 5) Display the contents of B by calling displayChocoList(). Pass "B (sorted)" as the list description.
	 
*/	 		     
	printf("Problem 5\n");
	B = initChocoList();
	populateChocoList(&B);
	displayChocoList(B, "B (unsorted)");
	sortChocoList(B);
	displayChocoList(B, "B (sorted)");
	pause();

  return 0;
}

/************************************************************
 *  Problem 0 Completed Functions                           *
 ************************************************************/
 
void pause(void){
	printf("\n\nPress any key to continue...");
	getch();
	system("CLS");
}

void generateChocoRecords(void){
	Chocolate data[] = { 	{"TO1701", {"Toblerone", 135}, 150.75, 20},
						{"TO1703", {"Toblerone", 100}, 125.75, 60},
						{"TO1715", {"Toblerone", 50}, 90.75, 80},
						{"CA1550", {"Cadbury", 120}, 200.00, 30},
						{"HE1501", {"Hersheys", 100}, 100.50, 10},
						{"MA1801", {"Mars", 100}, 150.75, 20},
						{"KI1201", {"Kitkat", 50}, 97.75, 40},
						{"FE1450", {"Ferrero", 100},150.50, 50},
						{"ME1601", {"Meiji", 75}, 75.50, 60},
						{"NE1301", {"Nestle", 100}, 124.50, 70},
						{"LI1525", {"Lindt", 100}, 175.50, 80},
						{"VA1545", {"Valor", 120}, 149.50, 90},
						{"TA1455", {"Tango", 75}, 49.50, 100},
						{"FE1356", {"Ferrero", 200}, 250.75, 85},};
    
             /**********************************************************************
              * Write the variable declaration and code fragment that will accomplish the task   *
              * below this comment.                                                                                                            *
             ***********************************************************************/  
    FILE* fp = fopen("chocoRecords.bin", "wb");
    if(fp != NULL){
    	fwrite(data, sizeof(Chocolate), 14, fp);
    	fclose(fp);
	}
    
} 


/************************************************************
 *  Problem 1 Function Definitions                          *
 ************************************************************/

/*********************************************************************************************************
*  initChocoList() - The function will initialize a new ChocoList to be empty. The new ChocoList is then *
* 					  returned to the calling function.                  								 *		
**********************************************************************************************************/ 
ChocoList initChocoList(void){
	ChocoList C;
	C.choco = NULL;
	C.numChoco = 0;
	return C;
}

/************************************************************************************************************
*  populateChocoList() - The function will read a file called "chocoRecords.bin", and populate the ChocoList*
*						 with the records inside the file.	                 								*		
************************************************************************************************************/

void populateChocoList(ChocoList* CL){
	FILE *fp = fopen("chocoRecords.bin", "rb");
	ChocoList readChoco;
	CLL temp, *trav;
	
	if(fp != NULL){
		readChoco.choco = malloc(sizeof(ChocoNode));
		while(fread(&readChoco.choco->chocoProd, sizeof(Chocolate), 1, fp) != 0){
			for(trav = &CL->choco; *trav != NULL; trav = &(*trav)->nextChoco){}
			*trav = malloc(sizeof(ChocoNode));
			if(*trav != NULL){
				(*trav)->chocoProd = readChoco.choco->chocoProd;
				(*trav)->nextChoco = NULL;
			}
			CL->numChoco++;
		}
	}
	fclose(fp);
}

/************************************************************************************************************
*  displayChocoList() - The function will display the contents of the ChocoList	                 			*
************************************************************************************************************/
void displayChocoList(ChocoList CL, char *listDesc) {
	printf("\n\nElements of the Chocolate Product List :: %s", listDesc);
	printf("\n\n%-10s","ID");
	printf("%-15s","Description");
	printf("%10s","Weight");
	printf("%10s","Price");
	printf("%10s\n","Quantity");
		     /**********************************************************************
		      * Write the variable declaration and code fragment that will accomplish the task   *
		      * below this comment.                                                *
		     ***********************************************************************/  
	for(; CL.choco != NULL; CL.choco = CL.choco->nextChoco){
		printf("%-10s", CL.choco->chocoProd.chocoID);
		printf("%-15s", CL.choco->chocoProd.chocoDesc.name);
		printf("%10d", CL.choco->chocoProd.chocoDesc.weight);
		printf("%10.2f", CL.choco->chocoProd.chocoPrice);
		printf("%10d\n", CL.choco->chocoProd.chocoQty);
	}	
	printf("\n\nTOTAL NUMBER OF CHOCO RECORDS:: %d", CL.numChoco);
}


/************************************************************
 *  Problem 2 Function Definition                           *
 ************************************************************/

/*************************************************************************************************************
*  insertLastUnique() - The function will insertLast into the ChocoList a new Chocolate X if the chocoID of X*
*						still does not exist in the list. If this is true, and there is still space inside   *
*						the ChocoList (denoted by the CHOCO_SIZE), then insert into the list.		 		 *
*						Else if the chocoID already exists, then update the price and weight of the record	 *
*						to be equal to the new Chocolate X. Also update the qty to be the sum of the old	 *
*						and new qty.											                 			 *
*************************************************************************************************************/
void insertLastUnique(ChocoList *CL, Chocolate X){
	CLL *trav;
	
	for(trav = &CL->choco; *trav != NULL && strcmp((*trav)->chocoProd.chocoID, X.chocoID) != 0; trav = &(*trav)->nextChoco){}
	if(*trav != NULL){
		(*trav)->chocoProd.chocoPrice = X.chocoPrice;
		(*trav)->chocoProd.chocoDesc.weight = X.chocoDesc.weight;
		(*trav)->chocoProd.chocoQty += X.chocoQty;
		printf("\nChoco Record: [%s] has been successfully updated!", X.chocoID);
	} else{
		if(CL->numChoco < CHOCO_SIZE){
			*trav = malloc(sizeof(ChocoNode));
			if(*trav != NULL){
				(*trav)->chocoProd = X;
				(*trav)->nextChoco = NULL;
			}
			CL->numChoco++;
			printf("\nChoco Record: [%s] has been successfully inserted!", X.chocoID);
		} else{
			printf("\nThere is no more space to add chocolate [%s] to our ChocoList.", X.chocoID);
		}
	}
}

/************************************************************
 *  Problem 3 Function Definition                           *
 ************************************************************/
 
/****************************************************************************************************************
*  insertSortedName() - The function will insert into the ChocoList a new Chocolate X. Insertion will be done   *
*						in ascending order, sorted by the name of the Chocolate. Insertion can only be possible *
*						if there is still space in the Chocolist (max elements is denoted by CHOCO_SIZE).		*									                 			 *
*****************************************************************************************************************/
void insertSortedName(ChocoList *CL, Chocolate X){
	CLL *trav, temp;
	
	if(CL->numChoco < CHOCO_SIZE){
		for(trav = &CL->choco; *trav != NULL && strcmp((*trav)->chocoProd.chocoDesc.name, X.chocoDesc.name) < 0; trav = &(*trav)->nextChoco){}
		temp = malloc(sizeof(ChocoNode));
		if(temp != NULL){
			temp->chocoProd = X;
			temp->nextChoco = *trav;
			*trav = temp;
		}
		CL->numChoco++;
	}
}

/*********************************************************************************************************************
*  populateSorted() - The function will go through an unsorted ChocoList, and insert all if its elements into a new  *
*					  sorted ChocoList. This new list is returned to the calling function. This function will insert *
*					  using insertSortedName().																		 *									                 			 
*********************************************************************************************************************/
ChocoList populateSorted(ChocoList CL){
	ChocoList S;
	S.choco = NULL;
	S.numChoco = 0;
	
	while(CL.choco != NULL){
		insertSortedName(&S, CL.choco->chocoProd);
		CL.choco = CL.choco->nextChoco;
	}
	
	return S;
}

 /************************************************************
 *  Problem 4 Function Definition                           *
 ************************************************************/
/*********************************************************************************************************************
*  deleteAllChoco() - The function will go through the ChocoList, and delete all the elements with the same name as  *
*					  the passed chocoName. At the end of the function, display the total number of deleted nodes,   *
*					  and return that number to the calling function.												 *																		 *									                 			 
*********************************************************************************************************************/
int deleteAllChoco(ChocoList *CL, char chocoName[]){
	CLL *trav, temp;
	int count = 0;
	
	if(CL->choco != NULL){
		for(trav = &CL->choco; *trav != NULL;){
			if(strcmp((*trav)->chocoProd.chocoDesc.name, chocoName) == 0){
				temp = *trav;
				*trav = temp->nextChoco;
				free(temp);
				count++;
				CL->numChoco--;
			} else{
				trav = &(*trav)->nextChoco;
			}
		}
	}
	printf("Number of %s records deleted: %d\n", chocoName, count);
	return count;
}
 
 /************************************************************
 *  Problem 5 Function Definition                           *
 ************************************************************/
/*************************************************************************************************************************
*  sortChocoList() - The function will go through a ChocoList and sort the values in ascending order using selectionSort.*												 *																		 *									                 			 
*************************************************************************************************************************/
void sortChocoList(ChocoList CL){
	CLL trav1, trav2;
	CLL min;
	Chocolate x;

	for(trav1 = CL.choco; trav1 != NULL; trav1 = trav1->nextChoco){
		min = trav1;
		for(trav2 = trav1; trav2 != NULL; trav2 = trav2->nextChoco){
			if(strcmp(trav2->chocoProd.chocoID, min->chocoProd.chocoID) < 0){
				min = trav2;
			}
		}
		x = trav1->chocoProd;
		trav1->chocoProd = min->chocoProd;
		min->chocoProd = x;
	}
}

