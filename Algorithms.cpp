#include "Algorithms.h"

void colorBar(Bar* bar, sf::Color clr)
{
	bar->getRectPtr()->setFillColor(clr);
}

void Algorithms::swap(int arr[], int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void Algorithms::shuffle(int num_array[], int size)
{

	for (int i = 0; i < size; i++) {
		int r = rand() % size;

		if (i != r)
			swap(num_array, i, r);
	}
}

void Algorithms::insertionSort(Bar* bar_arr[], int num_arr[], int size) 
{
	for (int i = 0; i < size; i++)
	{
		for (int j = i; j > 0 && num_arr[j - 1] > num_arr[j]; j--)
		{
			colorBar(bar_arr[j-1], sf::Color::White); // element being evaluated is red

			swap(num_arr, j, j - 1);

			Sleep(10);

			// Set elements not sorted to black
			for (int k = i; k < size; k++) {
				colorBar(bar_arr[k], sf::Color::Black);
			}
			// Set sorted elements to green
			for (int k = i; k >= 0; k--) {
				colorBar(bar_arr[k], sf::Color::Green);
			}
		}
	}
}

void Algorithms::selectionSort(Bar* bar_arr[], int num_arr[], int size)
{
	for (int i = 0; i < size - 1; i++) {
		int min_idx = i;
		for (int j = i + 1; j < size; j++) {

			if (num_arr[j] < num_arr[min_idx]) {
				min_idx = j;
			}

			Sleep(5);
			
			// Set elements not sorted to black
			for (int k = i; k < size; k++) {
				colorBar(bar_arr[k], sf::Color::Black);
			}
			// Set sorted elements to green
			for (int k = i; k >= 0; k--) {
				colorBar(bar_arr[k], sf::Color::Green);
			}

			// Color min red
			colorBar(bar_arr[min_idx], sf::Color::Red);

			// Color current element yellow
			colorBar(bar_arr[j], sf::Color::White);

		}
		swap(num_arr, i, min_idx);
	}

}

void Algorithms::bubbleSort(Bar* bar_arr[], int num_arr[], int size) 
{

}

void Algorithms::quickSort(Bar* bar_arr[], int num_arr[], int size) 
{

}

void Algorithms::mergeSort(Bar* bar_arr[], int num_arr[], int size) 
{

}

