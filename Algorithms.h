#pragma once
#include "Bar.h"
#include <Windows.h>

namespace Algorithms
{
	namespace Sort
	{
		bool insertionSort(Bar* bar_arr[], int num_arr[], int size, std::atomic<bool>* thread_exit);
		bool selectionSort(Bar* bar_arr[], int num_arr[], int size, std::atomic<bool>* thread_exit);
		bool bubbleSort(Bar* bar_arr[], int num_arr[], int size, std::atomic<bool>* thread_exit);
		bool quickSort(Bar* bar_arr[], int num_arr[], int size, std::atomic<bool>* thread_exit);
		bool mergeSort(Bar* bar_arr[], int num_arr[], int size, std::atomic<bool>* thread_exit);
	};
	namespace Util
	{
		void swap(int arr[], int i, int j);
		void shuffle(int num_array[], int size);
	};
};

