#pragma once
#include <vector>
#include <SDL.h>

// Visualization helper function
void draw_state(
    std::vector<int>& v,
    SDL_Renderer* renderer,
    unsigned int red,
    unsigned int blue);

// Sorting algorithms
void bubble_sort(std::vector<int> v, SDL_Renderer* renderer, const size_t& sort_speed);
void merge(std::vector<int>& arr, int left, int mid, int right);
void mergeSort(std::vector<int>& arr, int left, int right); 