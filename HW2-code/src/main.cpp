#include "methods.h"
// #include <chrono>

int main() {

  // std::vector<Item> items = readItemsFromFile("data/items_s.csv");

  // const auto start1{std::chrono::steady_clock::now()};
  // std::vector<Item> sorted = countingSort(items, "age", true);
  // const auto end1{std::chrono::steady_clock::now()};
  // const std::chrono::duration<double> elapsed_seconds1{end1 - start1};
  // writeItemsToFile("data/items_l_sorted.csv", sorted);

  // const auto start2{std::chrono::steady_clock::now()};
  // calculateRarityScores(sorted, 50);
  // const auto end2{std::chrono::steady_clock::now()};
  // const std::chrono::duration<double> elapsed_seconds2{end2 - start2};
  // writeItemsToFile("data/items_l_rarity.csv", sorted);

  // const auto start3{std::chrono::steady_clock::now()};
  // sorted = heapSortByRarity(sorted, true);
  // const auto end3{std::chrono::steady_clock::now()};
  // const std::chrono::duration<double> elapsed_seconds3{end3 - start3};
  // writeItemsToFile("data/items_l_rarity_sorted.csv", sorted);

  // // sorted = heapSortByRarity(sorted, false);
  // // writeItemsToFile("data/items_l_rarity_sorted_ascending.csv", sorted);

  // std::cout << "Time for countingSort: " << elapsed_seconds1.count() << " seconds" << std::endl;
  // std::cout << "Time for calculateRarityScores: " << elapsed_seconds2.count() << " seconds" << std::endl;
  // std::cout << "Time for heapSortRarity: " << elapsed_seconds3.count() << " seconds" << std::endl;

  return 0;
}