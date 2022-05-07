#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROW 3
#define COL 7
#define MENUSIZE 7

typedef struct{
	int row;
	int col;
}TableDetails;

typedef struct{
	char mealCode[5];
	char mealName[65];
	float price;
}MenuItem;

typedef struct{
	MenuItem meal[MENUSIZE];
	int count;				/* contains the actual number of meals on the menu */
}MenuArrList;

typedef struct{
	int tableNum[ROW][COL];	/* Multidimensional Array representation of the tables in a restaurant 
								Values of each index are as follows:
								0 - if table is unoccupied.
								1 - if table is occupied and is still waiting for their order.
								2 - if table is occupied and has already received their order.
							*/
	int numAvailTables; 	/* contains the number of unoccupied tables. */
}Seating;

typedef struct OrderNode{
	MenuItem meal;
	TableDetails tableNum;
	struct OrderNode* nextOrd;
}OrderNode, *OrderList;

typedef struct{
	MenuArrList menu;
	Seating table;
	OrderList orders;
	float sales;			/* contains the amount of money earned by the restaurant. Starts at 0.*/
}Restaurant;

/* Completed Functions */
void pause(void);
void generateMenuList(void);
void generateSales(void);

/* Problem 1 */
MenuItem* readMenuFromFile(void);
void populateMenu(MenuArrList* ML, MenuItem* M);
void initSeating(Seating* S);
void initResto(Restaurant* R);
void dispSeating(Seating S);
void dispRestaurant(Restaurant R);

/* Problem 2 */
int isVacant(Restaurant R, TableDetails tNum);
void purchaseMeal(Restaurant* R, char mealCode[], TableDetails tNum);

/* Problem 3 */
void deliverMeal(Restaurant* R);

/* Problem 4 */
void cleanTables(Restaurant* R);

/* Problem 5 */
void closeRestaurant(Restaurant* R);

int main(void)
{
	Restaurant resto;
	TableDetails tables[22] = {{0,0}, {0,1}, {0,2}, {0,3}, {0,4}, {0,5}, {0,6},
							   {1,0}, {1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6},
							   {2,0}, {2,1}, {2,2}, {2,3}, {2,4}, {2,5}, {2,6},
							   {9,9}
							  };
	char meal[][5] = {"BRGA", "CSPS", "FRRL", "HRDB", "PFCB", "RRPL", "SBFW", "AAAA"};
	
	generateSales();
	
	/* Problem 1 */
	/* Instructions:
		1) Initialize variable resto by calling the initResto() function.
		2) Call the dispRestaurant() function.
		3) Call the pause() function.
	*/
	printf("Problem 1\n");

	
	/* Problem 2 */
	/* Instructions:
		1)  Call the purchaseMeal() function, passing meal[0] and tables[4] as the parameters.
		2)  Call the purchaseMeal() function, passing meal[3] and tables[9] as the parameters.
		3)  Call the purchaseMeal() function, passing meal[2] and tables[3] as the parameters.
		4)  Call the purchaseMeal() function, passing meal[5] and tables[15] as the parameters.
		5)  Call the purchaseMeal() function, passing meal[4] and tables[7] as the parameters.
		6)  Call the purchaseMeal() function, passing meal[3] and tables[14] as the parameters.
		7)  Call the purchaseMeal() function, passing meal[6] and tables[17] as the parameters.
		8)  Call the purchaseMeal() function, passing meal[1] and tables[13] as the parameters.
		9)  Call the purchaseMeal() function, passing meal[4] and tables[6] as the parameters.
		10) Call the purchaseMeal() function, passing meal[2] and tables[6] as the parameters.
		11) Call the purchaseMeal() function, passing meal[7] and tables[2] as the parameters.
		12) Call the purchaseMeal() function, passing meal[5] and tables[21] as the parameters.
		13) Call the dispRestaurant() function.
		14) Call the pause() function.
	*/
	printf("Problem 2\n");

	
	/* Problem 3 */
	/* Instructions:
		1) Call the deliverMeal() function 5 times.
		2) Call the dispRestaurant() function.
		3) Call the pause() function.
	*/
	printf("Problem 3\n");

	
	/* Problem 4 */
	/* Instructions:
		1) Call the cleanTables() function.
		2) Call the dispRestaurant() function.
		3) Call the pause() function.
	*/
	printf("Problem 4\n");

	
	/* Problem 5 */
	/* Instructions:
		1) Call the closeRestaurant() function.
		2) Call the dispRestaurant() function.
		3) Call the pause() function.
	*/
	printf("Problem 5\n");

	
	return 0;
}

void pause(void)
{
	printf("\n\nPress any key to continue...");
	getch();
	system("CLS");
}

void generateMenuList(void)
{
	MenuItem meals[MENUSIZE] = {{"BRGA", "Beef Ribeye with Grilled Artichokes", 35.95},
							    {"CSPS", "Crispy Salt and Pepper Squid", 18.95},
							    {"FRRL", "Fennel Rubbed Rack of Lamb", 49.95},
						   		{"HRDB", "Honey Roast Duck with Green Beans", 33.95},
							 	{"PFCB", "Pan Fried Chicken Breast with Morel Sauce", 26.95},	    
								{"RRPL", "Roasted Rolled Pork Loin with Lemon and Sage", 22.95},				    
							    {"SBFW", "Signature Beef Wellington", 58.95}
							   };
							   
	FILE* fp = fopen("menu.bin", "wb");
	if(fp != NULL){
		fwrite(meals, sizeof(MenuItem), MENUSIZE, fp);
		fclose(fp);
	}
}

void generateSales(void)
{
	float initialSales = 606.15;
	generateMenuList();
	FILE* fp = fopen("sales.txt", "w");
	if(fp != NULL){
		fwrite(&initialSales, sizeof(float), 1, fp);
		fclose(fp);
	}
}

/****************************************************************************************************************************************
* readMenuFromFile() - This function will access a file called "menu.bin" and read ALL of the MenuItem records in the file. The records *
* 	 				   are then stored into a dynamically allocated array of MenuItems and returned to the calling function.		    *
****************************************************************************************************************************************/
MenuItem* readMenuFromFile(void)
{

}

/***************************************************************************************************************************************
* populateMenu() - The function will populate a MenuArrList given an array of MenuItems.											   *
***************************************************************************************************************************************/
void populateMenu(MenuArrList* ML, MenuItem* M)
{

}

/***************************************************************************************************************************************
* initSeating() - The function will initialize the tableNum and numAvailTires of the passed parameter.								   *
***************************************************************************************************************************************/
void initSeating(Seating* S)
{

}

/***************************************************************************************************************************************
* initResto() - The function will initialize ALL of the fields inside the Restaurant. This function will call the 3 functions 		   *
*				previously defined (readMenufromFile(), populateMenu(), initSeating()).							   					   *
***************************************************************************************************************************************/
void initResto(Restaurant* R)
{

}

/***************************************************************************************************************************************
* dispSeating() - The function will display by row and column, the current status of the seating arrangements in the restaurant. It    *
*				  will also display the remaining available tables.						   					   						   *
***************************************************************************************************************************************/
void dispSeating(Seating S)
{

}

/***************************************************************************************************************************************
* dispRestaurant() - Partial Code is provided. The function will display all of the details of the restaurant. Specifically, it will   *
*					 display the menu, the seating arrangement, and the current total sales for the day.					   		   *		   						   *
***************************************************************************************************************************************/
void dispRestaurant(Restaurant R)
{

}

/***************************************************************************************************************************************
* isVacant() - The function will first check if the passed table number is a valid table number. If it is, the function will then 	   *
*			   check if the table is unoccupied. If table is unnoccupied, then return 1. Else, return 0.							   *
***************************************************************************************************************************************/
int isVacant(Restaurant R, TableDetails tNum)
{

}

/***************************************************************************************************************************************
* purchaseMeal() - The function allows the customer to purchase a meal with the passed mealCode, and stay at the passed table number.  *
*				   The function first checks if there are still any available tables in the restaurant. If there are, it then 		   *
*				   checks if the meal being ordered is on the menu. If the meal is found, the function calls isVacant() to check 	   *
*				   if the table the user wants to book is unoccupied. If it is, insert a new node after the LAST node of the OrderList.* 
*				   Update the necessary values (tableNum, availTables, sales).							   							   *
***************************************************************************************************************************************/
void purchaseMeal(Restaurant* R, char mealCode[], TableDetails tNum)
{

}

/***************************************************************************************************************************************
* deliverMeal() - The function will check if there are any orders in the restaurant's orderlist. If there are, it will delete the 	   *
*				  FIRST node on the list, and set the tableNum of that order to be 2 (delivered).							   		   *
***************************************************************************************************************************************/
void deliverMeal(Restaurant* R)
{

}

/***************************************************************************************************************************************
* cleanTables() - The function will check Restaurant's Seating for any tableNum that has a status of 2.								   *
				  The function will then set that table's status back to zero, thus making the table available for occupancy once more.*
				  Finally, display a message that the table has been cleaned. Do not forget to update the necessary fields.			   *
***************************************************************************************************************************************/
void cleanTables(Restaurant* R)
{

}

/***************************************************************************************************************************************
* recordSales() - The function will open a file called "sales.txt", which simply contains the previous sales of the restaurant. 	   *
*				  It will then read that value, and add it to the current sales. The sum is then written back into the file, making    *
*				  sure to OVERWRITE the previous amount on the file. Finally, set the current sales back to 0.						   *
***************************************************************************************************************************************/
void recordSales(Restaurant* R)
{
	
}

/***************************************************************************************************************************************
* closeRestaurant() - The function will keep calling deliverMeal() until all of the orders have been successfully delivered. 		   *
*					  After which it will call cleanTables(), and recordSales() to prepare the restaurant for another new day.		   *
***************************************************************************************************************************************/
void closeRestaurant(Restaurant* R)
{

}
