#pragma once
#include "Bar.h"
#include <Windows.h>

static class Algorithms
{
public:
	static void insertionSort(Bar* bar_arr[], int num_arr[], int size);
	static void selectionSort(Bar* bar_arr[], int num_arr[], int size);
	static void bubbleSort(Bar* bar_arr[], int num_arr[], int size);
	static void quickSort(Bar* bar_arr[], int num_arr[], int size);
	static void mergeSort(Bar* bar_arr[], int num_arr[], int size);

	static void swap(int arr[], int i, int j);
	static void shuffle(int num_array[], int size);
};

