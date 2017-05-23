#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Structure "deed" where five types of data are stored
typedef struct {
    int id;
    char name[55];
    int deed_points;
    int total_times_done;
    int total_points_earned;
} deed;

// Sorting the records using Bubble Sort
void bubbleSortByTotalTimes(deed *x[], int size) {
	int i, j;
		for (i = 0; i < size - 1; i++) {
			int swapped=0;
			for (j = 0; j < size - 1 - i; j++) {
				if (x[j]->total_times_done > x[j+1]->total_times_done) {
					deed *temp = x[j + 1];
					x[j + 1] = x[j];
					x[j] = temp;
					swapped=1;
				}
			} if (!swapped){
	            return;
			  }
		}
}


// Sorting the records using Selection Sort
void selectionSortByDeedPoints(deed *x[], int size) {
	int i;
	for(i = 0; i < size-1; i++) {
	    int j, mindex = i;
        for (j = i+1; j < size; j++) {
	        if ((x[j]->deed_points)*(x[j]->total_times_done) < (x[mindex]->deed_points)*(x[mindex]->total_times_done)) {
	            mindex = j;
	        }
	    }
	     deed *temp = x[i];
	     x[i]= x[mindex];
	     x[mindex] =temp;
	}
}

// A function used to compare two strings
_Bool nameCompare(char name1[], char name2[]) {
	int i = 0;
	do {
		if (name1[i] < name2[i]) {
			return 1;
		} else if(name1[i] > name2[i]) {
			return 0;
		}
		i++;
	} while(name1[i] != '\0' || name2[i] != '\0');

	return 0;
}

// Sorting the records using Insertion Sort
void insertionSortByName(deed *x[], int size) {
	int i;
	for (i = 0; i < size; i++) {
	 	 int j;
	 	 deed *toinsert=x[i];
		 for (j = i; j >= 0; j--) {
			  if (j == 0 || !nameCompare(toinsert->name,x[j-1]->name)){
				  x[j] = toinsert;
				  break;
			  } else {
					x[j] = x[j - 1];
				}
		 }
    }
}

// Printing the records to the Console window
void printArray1(deed *deed_list[], int size) {
	int i, j=0;
	for (i = 0; i < size; i++) {
		if(deed_list[i]->total_times_done != 0) {
		printf("%3i  %5i  %-54s  %5i  %12i  %12i \n",j,deed_list[i]->id, deed_list[i]->name, deed_list[i]->deed_points, deed_list[i]->total_times_done, deed_list[i]->total_points_earned);
		j++;
		}
	}
	printf("\n");
}

// Printing the records to the Console window
void printArray2(deed *deed_list[], int size) {
	int i, j=0; // j is an order number
	for (i = size-1; i>=0; i--) {
		if(deed_list[i]->total_times_done != 0) {
		printf("%3i  %5i  %-54s  %5i  %12i  %12i \n",j,deed_list[i]->id, deed_list[i]->name, deed_list[i]->deed_points, deed_list[i]->total_times_done, deed_list[i]->total_points_earned);
		j++;
		}
	}
	printf("\n");
}

// Printing the records to the Console window
void printArray3(deed *deed_list[], int size) {
	int i, sum1=0, sum2=0;
	for (i = 0; i < size; i++) {
		 sum1+=deed_list[i]->total_times_done; // Adding the amounts of total times the deeds were done over the week
		 sum2+=deed_list[i]->total_points_earned; // Adding the amounts of total points earned over the week
	}
	printf("task 3: Total number of deeds performed over the week: %i deeds\n", sum1);
	printf("task 4: Total number of deed points accumulated over the week: %i points\n", sum2);
}

// Using Binary Search method to search the name of the deed
void binarySearch(deed *deed_list[], int size) {
	int min = 0;
    int max = size-1;
    char nameofdeed[55]; // Array that stores strings (names of deeds)

    int k=1;
    do {
    	printf("Please,enter the name of the deed:\n");
    	printf("task 6: search case %i:", k);
    	scanf("%s", nameofdeed);
		_Bool exist=0;
		while (min <= max) {

				int guess = (min + max) / 2;

				// Using a built-in library function strcmp() to compare two strings
				if (strcmp(deed_list[guess]->name, nameofdeed)==0){
					printf("%s  %i   %i\n", nameofdeed, deed_list[guess]->total_times_done, deed_list[guess]->total_points_earned);
					exist=1;
					break;
				} else if (strcmp(deed_list[guess]->name, nameofdeed)> 0){
							max = guess-1;
           	   	  } else {
           	   		  	  min = guess+1;
           	   	  	}
	}
	if (!exist){
	 printf("No such deed\n");
		break;
	}
	 k++;
    } while (1);
}


int main(){
	setvbuf(stdout, NULL, _IONBF, 0);

	// Opening the first input file
	FILE *file1 = fopen("deed_list.txt", "r");
	if (file1 == NULL) {
		printf("Cannot find file.");
		exit(1);
	}

	// Reading the size of the records
	int size;
	fscanf(file1,"%i", &size);

	deed **deed_list=(deed**)malloc(size*sizeof(deed*)); //Array of pointers to the "deed" structure items

	printf("No|      --------- deed_name ---------                               |deed           |total       |points\n"
		   "  |                                                                  |point          |times       |earned\n");

	// Reading the records into the deed_list from the first file
	int i;
	for(i=0; i<size; i++){
		deed_list[i]=(deed*)malloc(size*sizeof(deed));
		fscanf(file1, "%i   %s    %i\n", &deed_list[i]->id, deed_list[i]->name, &deed_list[i]->deed_points);
	}

	// Closing the first input file
	fclose(file1);

	for(i=0; i<size; i++){
		deed_list[i]->total_times_done = 0;
		deed_list[i]->total_points_earned = 0;
	}

	// Opening the second input file
	FILE *file2 = fopen("daylog.txt", "r");
		if (file2 == NULL) {
			printf("Cannot find file.");
			exit(1);
		}

	// Reading the records into the deed_list from the second file
	do {
		int key, t; // key is the ID number, t shows how many times the deed is done
		fscanf(file2, "%i  %i \n", &key, &t);
		deed_list[key-1]->total_times_done += t; // key-1 shows that an array index starts from 0
		deed_list[key-1]->total_points_earned = deed_list[key-1]->total_times_done*deed_list[key-1]->deed_points;
	} while(!feof(file2));

	// Closing the second input file
	fclose(file2);

	// Calling the function to print the records that were read
	printArray1(deed_list, size);

	// Calling the function to sort the records by the total number of times
	bubbleSortByTotalTimes(deed_list, size);

	printf("task1: after sort by deeds_total_times_done:\n");
	printf("No|      --------- deed_name ---------                               |deed           |total       |points\n"
		   "  |                                                                  |point          |times       |earned\n");
	// Calling the function to print the sorted records
	printArray2(deed_list, size);

	// Calling the function to sort the records by the total deed points
	selectionSortByDeedPoints(deed_list, size);

	printf("task2: after sort by deeds_total_points_earned:\n");
	printf("No|      --------- deed_name ---------                               |deed           |total       |points\n"
		   "  |                                                                  |point          |times       |earned\n");
	// Calling the function to print the sorted records
	printArray2(deed_list, size);

	// Calling the function to print the total number of deeds and deed points accumulated over the week
	printArray3(deed_list, size);

	// Calling the function to sort the records in alphabetical order
	insertionSortByName(deed_list, size);

	printf("\ntask5: after sort alphabetically:\n");
	printf("No|      --------- deed_name ---------                               |deed           |total       |points\n"
		   "  |                                                                  |point          |times       |earned\n");
	// Calling the function to print the sorted records
	printArray1(deed_list, size);

	// Calling the function to search for the deed name
	binarySearch(deed_list, size);

	return 0;
}

