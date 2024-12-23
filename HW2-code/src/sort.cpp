#include "methods.h"

// Sort by age
std::vector<Item> countingSort(std::vector<Item>& items, const std::string& attribute, bool ascending){
  if (attribute != "age"){
    std::cout << "Wrong attribute input!" << std::endl;
    return items;
  }

  // auxillary array for counting age values of items
  std::vector<int> aux(getMax(items, "age")+1, 0);

  // loop to count each value
  for (size_t i = 0; i < items.size(); i++){
    aux[items[i].age]++;
  }

  // increment by previous value to obtain indexes
  for (size_t i = 1; i < aux.size(); i++){
    aux[i] = aux[i] + aux[i-1];
  }

  std::vector<Item> sortedItems(items.size());

  for (int i = items.size()-1; i >= 0 ; i--){
    sortedItems[aux[items[i].age]-1] = items[i];
    aux[items[i].age]--;
  }

  // if descending, reverse the array sorted in ascending order to keep stability
  if (!ascending){
    Item temp;

    for (size_t i = 0; i < sortedItems.size()/2; i++){
      temp = sortedItems[i];
      sortedItems[i] = sortedItems[sortedItems.size() - 1 - i];
      sortedItems[sortedItems.size() - 1 - i] = temp;
    }
  }

  return sortedItems;
}

// Function to heapify a subtree rooted with node i in the array of items
void heapify(std::vector<Item>& items, int n, int i, bool descending){

  if (descending){    // max-heapify
    // define indexes
    int l = i*2 + 1;
    int r = i*2 + 2;
    int largest = i;

    if (l < n && items[l].rarityScore > items[i].rarityScore){
      largest = l;
    }
    if (r < n && items[r].rarityScore > items[largest].rarityScore){
      largest = r;
    }

    if (largest != i){
      Item temp;
      temp = items[i];
      items[i] = items[largest];
      items[largest] = temp;

      heapify(items, n, largest, true);
    }
  }
  else{   // min-heapify
    // define indexes
    int l = i*2 + 1;
    int r = i*2 + 2;
    int smallest = i;

    if (l < n && items[l].rarityScore < items[i].rarityScore){
      smallest = l;
    }
    if (r < n && items[r].rarityScore < items[smallest].rarityScore){
      smallest = r;
    }

    if (smallest != i){
      Item temp;
      temp = items[i];
      items[i] = items[smallest];
      items[smallest] = temp;

      heapify(items, n, smallest, false);
    }
  }
}

// Function to perform heap sort on rarityScore scores of items
std::vector<Item> heapSortByRarity(std::vector<Item>& items, bool descending){
  if (!descending){
    // build min-heap
    int n = items.size();
    for (int i = (n-1)/2; i >= 0; i--){
      heapify(items, n, i, true);
    }

    for (int i = n-1; i >= 1; i--){
      // exchange
      Item temp;
      temp = items[0];
      items[0] = items[i];
      items[i] = temp;

      heapify(items, i, 0, true);
    }
  }
  else{
    // build max-heap
    int n = items.size();
    for (int i = (n-1)/2; i >= 0; i--){
      heapify(items, n, i, false);
    }

    for (int i = n-1; i >= 1; i--){
      // exchange
      Item temp;
      temp = items[0];
      items[0] = items[i];
      items[i] = temp;

      heapify(items, i, 0, false);
    }
  }

  return items;
}
