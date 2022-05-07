/***************************************/
/* Accomplished by: Dhony Mark Mendoza */
/* Date: March 7, 2022                 */
/***************************************/

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
							   {9,9}};
	char meal[][5] = {"BRGA", "CSPS", "FRRL", "HRDB", "PFCB", "RRPL", "SBFW", "AAAA"};
	
	generateSales();
	
	/* Problem 1 */
	/* Instructions:
		1) Initialize variable resto by calling the initResto() function.
		2) Call the dispRestaurant() function.
		3) Call the pause() function.
	*/
	printf("Problem 1\n");
	initResto(&resto);
	dispRestaurant(resto);
	pause();
	
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
	purchaseMeal(&resto, meal[0], tables[4]);
	purchaseMeal(&resto, meal[3], tables[9]);
	purchaseMeal(&resto, meal[2], tables[3]);
	purchaseMeal(&resto, meal[5], tables[15]);
	purchaseMeal(&resto, meal[4], tables[7]);
	purchaseMeal(&resto, meal[3], tables[14]);
	purchaseMeal(&resto, meal[6], tables[17]);
	purchaseMeal(&resto, meal[1], tables[13]);
	purchaseMeal(&resto, meal[4], tables[6]);
	purchaseMeal(&resto, meal[2], tables[6]);
	purchaseMeal(&resto, meal[7], tables[2]);
	purchaseMeal(&resto, meal[5], tables[21]);
	dispRestaurant(resto);
	pause();
	
	/* Problem 3 */
	/* Instructions:
		1) Call the deliverMeal() function 5 times.
		2) Call the dispRestaurant() function.
		3) Call the pause() function.
	*/
	printf("Problem 3\n");
	deliverMeal(&resto);
	deliverMeal(&resto);
	deliverMeal(&resto);
	deliverMeal(&resto);
	deliverMeal(&resto);
	dispRestaurant(resto);
	pause();
	
	/* Problem 4 */
	/* Instructions:
		1) Call the cleanTables() function.
		2) Call the dispRestaurant() function.
		3) Call the pause() function.
	*/
	printf("Problem 4\n");
	cleanTables(&resto);
	dispRestaurant(resto);
	pause();
	
	/* Problem 5 */
	/* Instructions:
		1) Call the closeRestaurant() function.
		2) Call the dispRestaurant() function.
		3) Call the pause() function.
	*/
	printf("Problem 5\n");
	closeRestaurant(&resto);
	dispRestaurant(resto);
	pause();
	
	return 0;
}

void pause(void){
	printf("\n\nPress any key to continue...");
	getch();
	system("CLS");
}

void generateMenuList(void){
	MenuItem meals[MENUSIZE] = {{"BRGA", "Beef Ribeye with Grilled Artichokes", 35.95},
							    {"CSPS", "Crispy Salt and Pepper Squid", 18.95},
							    {"FRRL", "Fennel Rubbed Rack of Lamb", 49.95},
						   		{"HRDB", "Honey Roast Duck with Green Beans", 33.95},
							 	{"PFCB", "Pan Fried Chicken Breast with Morel Sauce", 26.95},	    
								{"RRPL", "Roasted Rolled Pork Loin with Lemon and Sage", 22.95},				    
							    {"SBFW", "Signature Beef Wellington", 58.95}};
							   
	FILE* fp = fopen("menu.bin", "wb");
	if(fp != NULL){
		fwrite(meals, sizeof(MenuItem), MENUSIZE, fp);
		fclose(fp);
	}
}

void generateSales(void){
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
MenuItem* readMenuFromFile(void){
	MenuItem *mi = malloc(sizeof(MenuItem)*MENUSIZE);
	FILE *fp = fopen("menu.bin", "rb");
	int i = 0;
	
	if(fp != NULL){
		while(fread(&mi[i++], sizeof(MenuItem), 1, fp) != 0){}
	}
	fclose(fp);
	
	return mi;
}

/***************************************************************************************************************************************
* populateMenu() - The function will populate a MenuArrList given an array of MenuItems.											   *
***************************************************************************************************************************************/
void populateMenu(MenuArrList* ML, MenuItem* M){
	int i;
	for(i = 0; i < MENUSIZE; i++){
		ML->meal[ML->count++] = M[i];
	}
}

/***************************************************************************************************************************************
* initSeating() - The function will initialize the tableNum and numAvailTires of the passed parameter.								   *
***************************************************************************************************************************************/
void initSeating(Seating* S){
	int i, j;
	S->numAvailTables = 0;
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			S->tableNum[i][j] = 0;
			S->numAvailTables++;
		}
	}
}

/***************************************************************************************************************************************
* initResto() - The function will initialize ALL of the fields inside the Restaurant. This function will call the 3 functions 		   *
*				previously defined (readMenufromFile(), populateMenu(), initSeating()).							   					   *
***************************************************************************************************************************************/
void initResto(Restaurant* R){
	R->menu.count = 0;
	R->orders = NULL;
	R->sales = 0.0;
	
	MenuItem *mi = readMenuFromFile();
	populateMenu(&R->menu, mi);
	initSeating(&R->table);
}

/***************************************************************************************************************************************
* dispSeating() - The function will display by row and column, the current status of the seating arrangements in the restaurant. It    *
*				  will also display the remaining available tables.						   					   						   *
***************************************************************************************************************************************/
void dispSeating(Seating S){
	printf(" Seating Arrangement\n");
	int i, j;
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			printf("|%d|", S.tableNum[i][j]);
		} 
		printf("\n");
	}
	printf("Available tables: %d", S.numAvailTables);
}

/***************************************************************************************************************************************
* dispRestaurant() - Partial Code is provided. The function will display all of the details of the restaurant. Specifically, it will   *
*					 display the menu, the seating arrangement, and the current total sales for the day.					   		   *		   						   *
***************************************************************************************************************************************/
void dispRestaurant(Restaurant R){
	printf("\n\n******************************************************************\n\n");
	printf("\t\tGordon Ramsey's Hell's Kitchen Menu");
	printf("\n\n******************************************************************\n\n");
	int i;
	printf("%-10s", "Code");
	printf("%-50s", "Name");
	printf("%-15s\n", "Price");
	for(i = 0; i < R.menu.count; i++){
		printf("%-10s", R.menu.meal[i].mealCode);
		printf("%-50s", R.menu.meal[i].mealName);
		printf("$%-15.2f\n", R.menu.meal[i].price);
	}
	printf("\n******************************************************************\n\n");
	dispSeating(R.table);
	printf("\n\nTotal Sales for today: $%.2f\n\n", R.sales);
}

/***************************************************************************************************************************************
* isVacant() - The function will first check if the passed table number is a valid table number. If it is, the function will then 	   *
*			   check if the table is unoccupied. If table is unnoccupied, then return 1. Else, return 0.							   *
***************************************************************************************************************************************/
int isVacant(Restaurant R, TableDetails tNum){
	int flag = 1;
	int i, j;
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			if(R.table.tableNum[tNum.row][tNum.col] != 0){
				flag = 0;
			}
		}
	}
	return flag;
}

/***************************************************************************************************************************************
* purchaseMeal() - The function allows the customer to purchase a meal with the passed mealCode, and stay at the passed table number.  *
*				   The function first checks if there are still any available tables in the restaurant. If there are, it then 		   *
*				   checks if the meal being ordered is on the menu. If the meal is found, the function calls isVacant() to check 	   *
*				   if the table the user wants to book is unoccupied. If it is, insert a new node after the LAST node of the OrderList.* 
*				   Update the necessary values (tableNum, availTables, sales).							   							   *
***************************************************************************************************************************************/
void purchaseMeal(Restaurant* R, char mealCode[], TableDetails tNum){
	int flag = isVacant(*R, tNum);
	OrderList *trav = &R->orders;
	int i;
	
	if(tNum.row > ROW || tNum.col > COL){
		printf("\nThe table [%d][%d] does not exist in our restaurant.", tNum.row, tNum.col);
	}
	if(R->table.numAvailTables > 0){
		for(i = 0; i < R->menu.count && strcmp(R->menu.meal[i].mealCode, mealCode) != 0; i++){}
		if(i < R->menu.count){
			if(flag == 1){
				for(; *trav != NULL; trav = &(*trav)->nextOrd){}
				*trav = malloc(sizeof(OrderNode));
				if(*trav != NULL){
					(*trav)->meal = R->menu.meal[i];
					(*trav)->tableNum = tNum;
					(*trav)->nextOrd = NULL;
				}
				
				R->table.numAvailTables--;
				R->sales = R->sales+R->menu.meal[i].price;
				R->table.tableNum[tNum.row][tNum.col] = flag;
			}
		} else{
			printf("\nSorry, we don't have that on our menu. Can we recommend you something else?");
		}
	}
}

/***************************************************************************************************************************************
* deliverMeal() - The function will check if there are any orders in the restaurant's orderlist. If there are, it will delete the 	   *
*				  FIRST node on the list, and set the tableNum of that order to be 2 (delivered).							   		   *
***************************************************************************************************************************************/
void deliverMeal(Restaurant* R){
	OrderList *trav = &R->orders, temp;
	if(*trav != NULL){
		temp = *trav;
		R->table.tableNum[temp->tableNum.row][temp->tableNum.col] = 2;
		*trav = temp->nextOrd;
		printf("\n%s has been delivered to table [%d][%d]", temp->meal.mealName, temp->tableNum.row, temp->tableNum.col);
		free(temp);
	}
}

/***************************************************************************************************************************************
* cleanTables() - The function will check Restaurant's Seating for any tableNum that has a status of 2.								   *
				  The function will then set that table's status back to zero, thus making the table available for occupancy once more.*
				  Finally, display a message that the table has been cleaned. Do not forget to update the necessary fields.			   *
***************************************************************************************************************************************/
void cleanTables(Restaurant* R){
	int i, j;

	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			if(R->table.tableNum[i][j] == 2){
				R->table.tableNum[i][j] = 0;
				printf("\nTable [%d][%d] has been cleaned.", i, j);
				R->table.numAvailTables++;
			}
		}
	}
}

/***************************************************************************************************************************************
* recordSales() - The function will open a file called "sales.txt", which simply contains the previous sales of the restaurant. 	   *
*				  It will then read that value, and add it to the current sales. The sum is then written back into the file, making    *
*				  sure to OVERWRITE the previous amount on the file. Finally, set the current sales back to 0.						   *
***************************************************************************************************************************************/
void recordSales(Restaurant* R){
	FILE *openSale = fopen("sales.txt", "r+");
	float newSales = 0.0;
	if(openSale != NULL){
		if(fread(&newSales, sizeof(float), 1, openSale) != 0){}
		printf("\nYour previous sales: $%.2f", newSales);
		printf("\nYour current sales: $%.2f\n", R->sales);
		R->sales = R->sales+newSales;
		fwrite(&R->sales, sizeof(float), 1, openSale);
	}
	printf("\nYour total lifetime sales is: $%.2f\n", R->sales);

	fclose(openSale);
}

/***************************************************************************************************************************************
* closeRestaurant() - The function will keep calling deliverMeal() until all of the orders have been successfully delivered. 		   *
*					  After which it will call cleanTables(), and recordSales() to prepare the restaurant for another new day.		   *
***************************************************************************************************************************************/
void closeRestaurant(Restaurant* R){
	int i;
	for(i = 0; i < MENUSIZE; i++){
		deliverMeal(R);
	}
	cleanTables(R);
	recordSales(R);
	R->sales = 0.0;
}
