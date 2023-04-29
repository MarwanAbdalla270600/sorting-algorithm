#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

const int MAX = 32767; // globale Variablen für die untere und obere Grenze der Werte
const int MIN = -32768;

struct listItem {	// Struct für die verkettete Liste (ein Element der Liste)
	int value;
	struct listItem *nextItem;
};

// globale Liste
struct listItem *first = NULL; //Pointer, der auf das erste Element der Liste zeigt
struct listItem *added = NULL; // Pointer, der immer auf das nächste Element der Liste zeigt
struct listItem *sorted = NULL;	// Pointer, der zum Sortieren der Liste benötigt wird

// INSERTIONSORT
double insertionSort(int *array, int length, int sort) {
	clock_t t = clock();
	int temp = 0;
	for (int i = 1; i < length; i++) {
		int j = i;
		if (sort == 0) { // asc
			// verschiebt Elemente von arr[j], die kleiner als array[j - 1] sind, eine Stelle zurück (von ihrer aktuellen Position)
			while (j > 0 && array[j] < array[j - 1]) { //  asc
				temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;
				j--;
			}
		}
		if (sort == 1) {
			// verschiebt Elemente von arr[j], die größer als array[j - 1] sind, eine Stelle zurück (von ihrer aktuellen Position)
			while (j > 0 && array[j] > array[j - 1]) { // desc
				temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;
				j--;
			}
		}
	}
	double time_taken = (((double) t) / CLOCKS_PER_SEC) * 1000; // in miliseconds
	return time_taken;
}

// QUICKSORT
double quickSort(int *array, int first, int last, int sort) {
	clock_t t = clock();
	int i, j, pivot, temp;
	if (first < last) {
		pivot = first;		//erstes Element im Array wird zum pivot 
		i = first;
		j = last;

		if (sort == 0) {	 // asc
			while (i < j) {		
				while (array[i] <= array[pivot] && i < last)   
					i++;		// i nähert sich von links dem pivot Element an 
				while (array[j] > array[pivot])	
					j--;		// j nähert sich von rechts dem pivot Element an 
				if (i < j) {	// Elemente werden links und rechts vom pivot sortiert
					temp = array[i];		
					array[i] = array[j];
					array[j] = temp;
				}
			}
		}
		if (sort == 1) {	// desc		
			while (i < j) {
				while (array[i] >= array[pivot] && i < last)
					i++;
				while (array[j] < array[pivot])
					j--;
				if (i < j) {
					temp = array[i];
					array[i] = array[j];
					array[j] = temp;
				}
			}
		}
		temp = array[pivot];		// pivot wird in temp gespeichert
		array[pivot] = array[j];	
		array[j] = temp;			// pivot wird an der richtigen Stelle des sortierten Arrays eingefügt
		quickSort(array, first, j - 1, sort);	// rekusiver Aufruf der selben Funktion mit den Werten links vom pivot
		quickSort(array, j + 1, last, sort);	// rekusiver Aufruf der selben Funktion mit den Werten rechts vom pivot

	}
	double time_taken = (((double) t) / CLOCKS_PER_SEC) * 1000; // in miliseconds
	return time_taken;
}

// BUBBLESORT
double bubbleSort(int *array, int length, int sort) {
	clock_t t = clock();
	for (int i = 1; i < length; i++) {
		for (int j = 0; j < length - i; j++) {
			if (sort == 0) { // asc
				// vergleicht zwei benachbarte Elemente und vertauscht sie, wenn arr[j]>arr[j+1]
				if (array[j] > array[j + 1]) {
					int tmp = array[j];
					array[j] = array[j + 1];
					array[j + 1] = tmp;
				}
			}
			if (sort == 1) { // desc
				// vergleicht zwei benachbarte Elemente und vertauscht sie, wenn arr[j]<arr[j+1] 
				if (array[j] < array[j + 1]) {
					int tmp = array[j];
					array[j] = array[j + 1];
					array[j + 1] = tmp;
				}
			}

		}
	}
	double time_taken = (((double) t) / CLOCKS_PER_SEC) * 1000; // in miliseconds
	return time_taken;
}

// MERGESORT
// Funktion zum richtigen Zusammenfügen der einzelnen Elemente (Hilfsfunktion für die eigentlichen Sortierfunktion)
void merge(int *arr, int l, int m, int r, int sort) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// erstellt temp Arrays
	int L[n1], R[n2];

	// Array wird in der Mitte aufgeteilt und die linke Seite wird in n1, die rechte Seite in n2 gespeichert
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];		
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];
	// merget temp Arrays zurück in arr[l..r]
	i = 0; // Initial index erstes Subarray
	j = 0; // Initial index zweites Subarray
	k = l; // Initial index merged Subarray

	if (sort == 0) {	// asc
		while (i < n1 && j < n2) {
			if (L[i] <= R[j]) {    
				arr[k] = L[i]; // fügt erstes Element linke Liste in die neue Liste hinten ein  
				i++;
			} else {
				arr[k] = R[j]; // fügt erstes Element rechte Liste in die neue Liste hinten ein 
				j++;
			}
			k++;
		}
	}
					
	if (sort == 1) {	// desc
		while (i < n1 && j < n2) {
			if (L[i] >= R[j]) { 
				arr[k] = L[i];
				i++;
			} else {
				arr[k] = R[j];
				j++;
			}
			k++;
		}
	}

	// kopiert übrige Elemente von L[], falls es welche gibt
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	// kopiert übrige Elemente von R[], falls es welche gibt
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}
// l=left index, r=right index vom Subarray vom Array, das sortiert werden soll
double mergeSort(int *arr, int l, int r, int sort) {
	clock_t t = clock();
	if (l < r) {
		// sowie (l+r)/2, aber but vermeidet Overflow bei großen l und h
		int m = l + (r - l) / 2;

		// halbiert die linke Seite und rechte Seite 
		mergeSort(arr, l, m, sort);
		mergeSort(arr, m + 1, r, sort);

		
		// linke und rechte Seite werden richtig zusammengefügt
		merge(arr, l, m, r, sort);
	}
	t = clock() - t;
	double time_taken = (((double) t) / CLOCKS_PER_SEC) * 1000; // in miliseconds
	return time_taken;
}

// befüllt das Array mit Length zufälligen Elementen zwischen MIN und MAX
void fillArray(int *array, int length) {
	srand(time(0));
	for (int i = 0; i < length; i++) {
		array[i] = (rand() % (MAX - MIN + 1)) + MIN;
	}
	array[length] = INT_MAX;
}

// gibt das Array in der Konsole aus
void printArray(int *array, int length) {
	int i;
	for (i = 0; i < length; i++) {
		i % 15 == 0 ? printf("\n") : printf(" ");
		printf("%6d", array[i]);
	}
	printf("\n");
}

// liefert die Anzahl der Elemente in einem Array
int getLengthOfArray(int *array) {
	int counter = 0;
	while (array[counter] != INT_MAX) {
		counter++;
	}
	return counter;
}

// Prüffunktion, die eine Fehlermeldung ausgibt, wenn die Sortierung fehlgeschlagen ist
int checkIfSorted(int *array, int length, int sort) {
	if (sort == 0) {
		for (int i = 0; i < length - 1; i++) {
			if (array[i] > array[i + 1]) {
				printf("Sortierung fehlgeschlagen\n");
				return 0;
			}
		}
	}
	if (sort == 1) {
		for (int i = length - 1; i <= 0; i++) {
			if (array[i] < array[i + 1]) {
				printf("Sortierung fehlgeschlagen\n");
				return 0;
			}
		}
	}
	return 1;
}

// dupliziert Array A in Array B
void setBtoA(int *array1, int *array2, int length) {
	for (int i = 0; i < length; i++) {
		array2[i] = array1[i];
	}
}

// liefert eine zufällige Zahl zwischen 0 und 1 zurück
int getRandom() {
	srand(time(0));
	return rand() % 2;
}

// gibt abhängig vom Operator (0,1 oder 2) das min, max oder den avg eines Arrays zurück
float getMinMaxAvg(float *array, int length, int operator) {
	float min = array[0];
	float max = array[0];
	float sum = 0;
	for (int i = 0; i < length; i++) {
		sum += array[i];
		min = (min > array[i] ? array[i] : min);
		max = (max < array[i] ? array[i] : max);
	}
	switch (operator) {
		case 0:
		return min;
		break;
		case 1:
		return max;
		break;
		case 2:
		return sum / length;
		break;
		default:
		return 0;
	}
}

// liefert den Pointer eines neuen Elementes
struct listItem* getNewItem(const int value) {
	struct listItem *newItem = NULL;
	newItem = malloc(sizeof(struct listItem));
	if (newItem != NULL) {
		newItem->nextItem = NULL;
		newItem->value = value;
	} else {
		printf("Reservierung fehlgeschlagen");
	}
	return newItem;
}

// gibt ein Element der Liste aus mit der Adresse und der Adresse zum nächsten Element
void printListItem(const struct listItem *item) {
	if (item == NULL) {
		printf("Item is NULL\n");
	} else {
		printf("value: %6d 		address: %p 	nextInLine: %p\n", item->value, item,
				item->nextItem); // -> dereferenzieren pointer
	}
}

// erstellt eine verkettete Liste mit zufälligen Zahlen und length Elementen
void createList(int length, int *randomNumberArray) {
	for (int i = 0; i < length; i++) {
		if (first == NULL) {
			first = getNewItem(randomNumberArray[0]);
			if (first != NULL) {
				added = first;
			}
		} else {
			added->nextItem = getNewItem(randomNumberArray[i]);
			if (added->nextItem != NULL) {
				added = added->nextItem;
			}
		}
	}
}

// gibt die einzelnen Elemente der Liste aus
void printList(struct listItem *list) {
	struct listItem *tmp;
	tmp = list;
	if (tmp == NULL) {
		printf("Die Liste ist leer");
	} else {
		while (tmp) {
			printListItem(tmp);
			tmp = tmp->nextItem;
		}
	}
}

// Insertionsort bei Liste
void sortedInsert(struct listItem *newnode) {
	// Abfrage: newnode links platzieren
	if (sorted == NULL || sorted->value >= newnode->value) { // wenn Wert von sorted > newnode
		newnode->nextItem = sorted; // newnode zeigt auf sorted (wird links von sorted platziert)
		sorted = newnode; // fügt Element in richtige Stelle ein
	}
	// Abfrage: newnode rechts platzieren
	else {
		struct listItem *current = sorted;
		// lokalisiert Element links vom newnode und ändert dessen nextItem-Pointer auf newnode
		while (current->nextItem != NULL
				&& current->nextItem->value < newnode->value) {
			current = current->nextItem;
		}
		newnode->nextItem = current->nextItem;
		current->nextItem = newnode;
	}
}

// Insertionsort bei Liste
double insertionsortList() {
	clock_t t = clock();
	struct listItem *current = first;
	// geht current durch und inserted jedes Element an der richtigen Stelle
	while (current != NULL) {
		// speichert Pointer auf nächstes Element
		struct listItem *next = current->nextItem;
		// inserted current in richtige Position in der Liste
		sortedInsert(current);
		// update current
		current = next;
	}
	// erstes Element zeigt auf sortierte Liste (auf Elemente, die sortiert aufeinander zeigen)
	first = sorted;
	t = clock() - t;
	double time_taken = (((double) t) / CLOCKS_PER_SEC) * 1000; // in miliseconds
	return time_taken;
}

// setzt den Speicherplatz der Liste frei
void freeList(struct listItem *first) {
	struct listItem *currentNode;
	while (first != NULL) {
		currentNode = first;
		first = first->nextItem;
		free(currentNode);
	}
}

// Ausgabe der Basisimplementierung
void printBasisimplementierung(int size) {
	int *array = NULL;
	array = malloc(size * sizeof(int));
	int *arrayreset = NULL;
	arrayreset = malloc(size * sizeof(int));
	fillArray(array, size);
	setBtoA(array, arrayreset, getLengthOfArray(array));
	printf("\nArray mit %i Elementen\n", size);
	printf("\n");
	printf("unsortiert:");
	printArray(array, getLengthOfArray(array));
	printf("\n");
	printf("Quicksort:");
	quickSort(array, 0, getLengthOfArray(array) - 1, 0);
	checkIfSorted(array, getLengthOfArray(array), 0);
	printArray(array, getLengthOfArray(array));
	setBtoA(arrayreset, array, getLengthOfArray(array));
	printf("\n");
	printf("Bubblesort:");
	bubbleSort(array, getLengthOfArray(array), 0);
	checkIfSorted(array, getLengthOfArray(array), 0);
	printArray(array, getLengthOfArray(array));
	setBtoA(arrayreset, array, getLengthOfArray(array));
	printf("\n");
	printf("Mergesort:");
	mergeSort(array, 0, getLengthOfArray(array) - 1, 0);
	checkIfSorted(array, getLengthOfArray(array), 0);
	printArray(array, getLengthOfArray(array));
	setBtoA(arrayreset, array, getLengthOfArray(array));
	printf("\n");
	printf("Insertionsort:");
	insertionSort(array, getLengthOfArray(array), 0);
	checkIfSorted(array, getLengthOfArray(array), 0);
	printArray(array, getLengthOfArray(array));
	setBtoA(arrayreset, array, getLengthOfArray(array));
	printf("\n");
	free(array);
	free(arrayreset);
}

// Ausgabe des Leistungsvergleich
void printLeistungsvergleich(int size) {
	int *array = NULL;
	array = malloc(size * sizeof(int));
	int *arrayreset = NULL;
	arrayreset = malloc(size * sizeof(int));

	fillArray(array, size);
	setBtoA(array, arrayreset, getLengthOfArray(array));
	printf("\n				Array mit %i Elementen\n\n ", size);
	printf("		aufsteigend		absteigend		zufällig\n\n");

	// Quicksort
	printf("Quicksort: ");

	printf("	%fms", quickSort(array, 0, getLengthOfArray(array) - 1, 0));
	setBtoA(arrayreset, array, getLengthOfArray(array));
	printf("		%fms", quickSort(array, 0, getLengthOfArray(array) - 1, 1));
	setBtoA(arrayreset, array, getLengthOfArray(array));
	printf("		%fms",
			quickSort(array, 0, getLengthOfArray(array) - 1, getRandom()));
	setBtoA(arrayreset, array, getLengthOfArray(array));

	// Bubblesort
	printf("\nBubblesort: ");
	printf("	%fms", bubbleSort(array, getLengthOfArray(array), 0));
	setBtoA(arrayreset, array, getLengthOfArray(array));
	printf("		%fms", bubbleSort(array, getLengthOfArray(array), 1));
	setBtoA(arrayreset, array, getLengthOfArray(array));
	printf("		%fms", bubbleSort(array, getLengthOfArray(array), getRandom()));
	setBtoA(arrayreset, array, getLengthOfArray(array));

	// Mergesort
	printf("\nMergesort: ");
	printf("	%fms", mergeSort(array, 0, getLengthOfArray(array) - 1, 0));
	setBtoA(arrayreset, array, getLengthOfArray(array));
	printf("		%fms", mergeSort(array, 0, getLengthOfArray(array) - 1, 1));
	setBtoA(arrayreset, array, getLengthOfArray(array));
	printf("		%fms",
			mergeSort(array, 0, getLengthOfArray(array) - 1, getRandom()));
	setBtoA(arrayreset, array, getLengthOfArray(array));

	// Insertsort
	printf("\nInsertionsort: ");
	printf("	%fms", insertionSort(array, getLengthOfArray(array), 0));
	setBtoA(arrayreset, array, getLengthOfArray(array));
	printf("		%fms", insertionSort(array, getLengthOfArray(array), 1));
	setBtoA(arrayreset, array, getLengthOfArray(array));
	printf("		%fms",
			insertionSort(array, getLengthOfArray(array), getRandom()));
	printf("\n\n");
	setBtoA(arrayreset, array, getLengthOfArray(array));
	free(array);
	free(arrayreset);
}

// Ausgabe der Bubblesort Analyse
void printBubbleSortAnalyse(int size) {
	int *array = NULL;
	array = malloc(size * sizeof(int));
	int *arrayreset = NULL;
	arrayreset = malloc(size * sizeof(int));
	fillArray(array, size);
	setBtoA(array, arrayreset, getLengthOfArray(array));
	float laufzeiten[20] = { 0 };
	printf("\nBubblesortlaufzeit mit Array der Größe %i\n", size);
	for (int i = 0; i < 20; i++) {
		i % 5 == 0 ? printf("\n") : printf(" ");
		laufzeiten[i] = bubbleSort(array, size, 0);
		setBtoA(arrayreset, array, getLengthOfArray(array));
		printf("%08.3fms", laufzeiten[i]);
	}
	printf("\n\nDie schnellste Sortierung: %08.3fms\n",
			getMinMaxAvg(laufzeiten, 20, 0));
	printf("Die langsamste Sortierung: %08.3fms\n",
			getMinMaxAvg(laufzeiten, 20, 1));
	printf("Die durschnittliche Sortierung: %08.3fms\n",
			getMinMaxAvg(laufzeiten, 20, 2));
	printf("\n");
	free(array);
	free(arrayreset);
}

// Ausgabe der Sortierung der verketteten Liste
void verketteteListe(int length) {
	int *randomNumberArray = NULL;
	randomNumberArray = malloc(length * sizeof(int));
	int *unsortedArray = NULL;
	unsortedArray = malloc(length * sizeof(int));
	fillArray(randomNumberArray, length);
	setBtoA(randomNumberArray, unsortedArray, length);
	createList(length, randomNumberArray);
	printf("\nArray[%i] unsortiert", length);
	printArray(unsortedArray, length);
	printf("\nArray[%i] sortiert", length);
	float arrtime = insertionSort(unsortedArray, length, 0);
	printArray(unsortedArray, length);

	printf("\nListe[%i] unsortiert\n", length);
	printList(first);
	printf("\nListe[%i] sortiert\n", length);
	float listtime = insertionsortList(first, sorted);
	printList(first);

	printf("\n			Dauer\nArray[%i]		%.3fms\nListe[%i]		%.3fms\n\n", length,
			arrtime, length, listtime);

	free(randomNumberArray);
	free(unsortedArray);
	freeList(first);
}

int main() {

	printf("Anleitung für das Programm\n"
			"1: Basisimplementierung\n"
			"2: Leistungsvergleich Sortieralgorithmen\n"
			"3: Vergleichbarkeit bezüglich Daten\n"
			"4: Verkettete Liste und Insertionsort\n"
			"q: Beenden des Programms\n\n");

	while (1) {
		printf("Eingabe: ");
		char input;
		input = getchar();
		getchar();
		if (input == 'q') {
			printf("Programm beendet\n");
			break;
		}
		switch (input) {
		case '1':
			printBasisimplementierung(8);
			printf("\n\n\n\n");
			printBasisimplementierung(16);
			printf("\n\n\n\n");
			printBasisimplementierung(64);
			break;
		case '2':
			printLeistungsvergleich(32);
			printf("\n\n\n\n");
			printLeistungsvergleich(128);
			printf("\n\n\n\n");
			printLeistungsvergleich(512);
			printf("\n\n\n\n");
			printLeistungsvergleich(2048);
			printf("\n\n\n\n");
			printLeistungsvergleich(8192);
			printf("\n\n\n\n");
			printLeistungsvergleich(32768);
			break;
		case '3':
			printBubbleSortAnalyse(20000);
			break;
		case '4':
			verketteteListe(2048);
			break;
		default:
			printf("Ungültige Eingabe\n");
			break;
		}
	}
	return 0;
}
