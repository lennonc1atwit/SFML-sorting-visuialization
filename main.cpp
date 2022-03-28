#include "Bar.h"
#include "Algorithms.h"

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>
#include <Windows.h>
#include <thread>

// Thread info
HANDLE hSorting_thread = 0;
std::atomic<int> thread_status = 0;
std::atomic<bool> thread_exit = false;
std::atomic<bool> thread_cancel_sort = false;

// List of sorting algos
typedef   bool (*SortFunc)(Bar* bar_arr[], int num_arr[], int size, std::atomic<bool>* thread_cancel_sort);
SortFunc sorting_funcs[] {
	Algorithms::Sort::insertionSort,
	Algorithms::Sort::selectionSort,
	Algorithms::Sort::bubbleSort,
	Algorithms::Sort::quickSort,
	Algorithms::Sort::mergeSort,
};

// ImGui vars
static int selected_sort = 0; // Invalid index to start
static const char* implmented_sorts[]{
	"Insertion",
	"Selection"
};

// Sorting vars
const int num_elements = 250;
int num_array[num_elements]{};
Bar* bar_array[num_elements]{};

DWORD WINAPI SortingThreadEntry(LPVOID param)
{
	// Call selected sorting function 
	while (!thread_exit.load()) {
		bool finished = sorting_funcs[selected_sort](bar_array, num_array, num_elements, &thread_cancel_sort);
		// If we finished sort wait for next one
		while (finished && !thread_cancel_sort.load()) {}
		thread_cancel_sort = false;
	}

	return 1;
}

void SuspendSort()
{
	while (thread_status.load() > 0) {
		SuspendThread(hSorting_thread);
		thread_status -= 1;
	}
}

void ResumeSort()
{
	while (thread_status.load() <= 0) {
		ResumeThread(hSorting_thread);
		thread_status += 1;
	}
}

void ResetSort()
{
	Algorithms::Util::shuffle(num_array, num_elements);
	for (int i = 0; i < num_elements; i++) {
		bar_array[i]->setColor(sf::Color::Black);
	}
	thread_cancel_sort = true;
}

void updateBars()
{
	// Set bars to match num array state
	for (int i = 0; i < num_elements; i++) {
		bar_array[i]->setValue(num_array[i]);
	}
}

void drawBars(sf::RenderWindow &window)
{
	// Update position and display color
	for (int i = 0; i < num_elements; i++) {
		bar_array[i]->getRectPtr()->setPosition(static_cast<float>(window.getSize().x) / num_elements * i, window.getSize().y);
		window.draw(*bar_array[i]->getRectPtr());
	}
}

void updateMenu()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::Button("Shuffle")) { ResetSort(); }

		if (ImGui::BeginMenu("Algorithm"))
		{
			if (ImGui::ListBox("Sorting Algorithms", &selected_sort, implmented_sorts, ARRAYSIZE(implmented_sorts))) { ResetSort(); }
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Animations"))
		{
			if (ImGui::MenuItem("Play", "resume sorting thread") && hSorting_thread != 0) { ResumeSort(); }
			if (ImGui::MenuItem("Pause", "pause sorting thread") && hSorting_thread != 0) { SuspendSort(); }
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

int main()
{
	// Create our SFML window and a clock to keep track of frame times
	sf::RenderWindow window(sf::VideoMode(1280, 640), "SFML sorting visuialization!");
	sf::Clock clock;

	// Init ImGUI to our window with default font
	ImGui::SFML::Init(window, true);

	// Generate our bars based on screen size
	int dx = window.getSize().x / num_elements;
	int dy = window.getSize().y / num_elements;

	for (int i = 0; i < num_elements; i++) {
		bar_array[i] = new Bar(dx, dy, i);
		num_array[i] = i;
	}

	// Create the sorting thread in suspended mode
	DWORD sorting_thread_id;
	hSorting_thread = CreateThread(NULL, 0, SortingThreadEntry, NULL, CREATE_SUSPENDED, &sorting_thread_id);

	while (window.isOpen())
	{
		// Clear for new frame
		window.clear(sf::Color(51, 51, 255));

		// Event handling
		sf::Event event;
		while (window.pollEvent(event)) {
			// Handle ImGUI events
			ImGui::SFML::ProcessEvent(event);
			// Handle SFML window events
			switch (event.type)
			{
			case sf::Event::Closed:
				thread_exit = true;
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			}
		}
		// clock.restart() resets clock to 0 and returns time since last frame
		// essentially frame time
		ImGui::SFML::Update(window, clock.restart());
		
		updateMenu(); // Get any updates from menu input
		updateBars(); // Update bars accordingly
		
		// Render ImGUI last so it never becomes occluded by other drawn elements
		drawBars(window);
		ImGui::SFML::Render(window);

		window.display();
	}

	ImGui::SFML::Shutdown();

	return 0;
}