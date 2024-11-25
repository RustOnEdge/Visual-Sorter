#define SDL_MAIN_HANDLED
#include<SDL2/SDL.h>
#include<iostream>
#include<random>
#include<ranges>
#include<algorithm>

void draw_state(
	std::vector<int>& v,
	SDL_Renderer* renderer,
	unsigned int red,
	unsigned int blue)
{
	int index = 0;
	for (int &i : v) {
		if (index == red) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		else if (index == blue) SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, index, 99, index, i);
		index++;
	}
}

void bubble_sort(std::vector<int> v, SDL_Renderer* renderer, const size_t &sort_speed) {
	for (unsigned int i = 0; i < v.size(); i++) {
		for (unsigned int j = i+1; j < v.size(); j++) {
			if (v[j] < v[i]) {
				std::swap(v[j], v[i]);
			}
			// clear screen
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			// draw state of the sort
			draw_state(v, renderer, i, j);

			// show to window
			SDL_RenderPresent(renderer);
			SDL_Delay(3);
		}
	}
}

void merge(std::vector<int>& arr, int left,
    int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    std::vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back 
    // into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], 
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], 
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(std::vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}


int main() {

	std::random_device rd;
	std::mt19937 gen(rd()); // standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<int> d(1, 99); // specify the distribution range
	std::vector<int> v;

	// populating vector with random numbers
	for (int i = 0; i < 100; i++) {
		v.push_back(d(rd));
        std::cout << v[i] <<" ";
	}

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	SDL_CreateWindowAndRenderer(1000, 1000, 0, &window, &renderer);
	SDL_RenderSetScale(renderer, 10, 10);

	size_t sort_speed = 10;

	bubble_sort(v, renderer, sort_speed);

	return 0;
}