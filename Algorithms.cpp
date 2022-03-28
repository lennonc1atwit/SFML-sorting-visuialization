#include "Algorithms.h"

void Algorithms::Util::swap(int arr[], int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void Algorithms::Util::shuffle(int num_array[], int size)
{
	for (int i = 0; i < size; i++) {
		int r = rand() % size;

		if (i != r)
			Util::swap(num_array, i, r);
	}
}

bool Algorithms::Sort::insertionSort(Bar* bar_arr[], int num_arr[], int size, std::atomic<bool>* thread_cancel_sort)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = i; j > 0 && num_arr[j - 1] > num_arr[j]; j--)
		{
			bar_arr[j-1]->setColor(sf::Color::White); // element being evaluated is red

			Util::swap(num_arr, j, j - 1);

			// Set elements not sorted to black
			for (int k = i; k < size; k++) {
				bar_arr[k]->setColor(sf::Color::Black);
			}
			// Set sorted elements to green
			for (int k = i; k >= 0; k--) {
				bar_arr[k]->setColor(sf::Color::Green);
			}

			// Check if we are canceling
			if (thread_cancel_sort->load() == true)
				return false;
			
			Sleep(1);
		}
	}
	return true;
}

bool Algorithms::Sort::selectionSort(Bar* bar_arr[], int num_arr[], int size, std::atomic<bool>* thread_cancel_sort)
{
	for (int i = 0; i < size - 1; i++) {
		int min_idx = i;
		for (int j = i + 1; j < size; j++) {

			if (num_arr[j] < num_arr[min_idx]) {
				min_idx = j;
			}
			
			// Set elements not sorted to black
			for (int k = i; k < size; k++) {
				bar_arr[k]->setColor(sf::Color::Black);
			}
			// Set sorted elements to green
			for (int k = i; k >= 0; k--) {
				bar_arr[k]->setColor(sf::Color::Green);
			}

			// Color min red
			bar_arr[min_idx]->setColor(sf::Color::Red);

			// Color current element yellow
			bar_arr[j]->setColor(sf::Color::White);

			// Check if we are canceling
			if (thread_cancel_sort->load() == true)
				return false;
			
			Sleep(1);
		}
		Util::swap(num_arr, i, min_idx);
	}
	return true;
}

bool Algorithms::Sort::bubbleSort(Bar* bar_arr[], int num_arr[], int size, std::atomic<bool>* thread_cancel_sort)
{
	return true;
}

bool Algorithms::Sort::quickSort(Bar* bar_arr[], int num_arr[], int size, std::atomic<bool>* thread_cancel_sort)
{
	return true;
}

bool Algorithms::Sort::mergeSort(Bar* bar_arr[], int num_arr[], int size, std::atomic<bool>* thread_cancel_sort)
{
	return true;
}

