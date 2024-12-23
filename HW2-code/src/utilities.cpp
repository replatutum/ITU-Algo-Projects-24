#include "methods.h"

std::vector<Item> readItemsFromFile(const std::string& filename) {
  std::vector<Item> items;
  std::ifstream file(filename);

  if(!file.is_open()){
    std::cerr << "File could not be opened" << std::endl;
  }

  std::string line;
  std::getline(file, line);     // Ignore header

  while (std::getline(file, line)){
    Item item;
    int pos = 0;

    pos = line.find(',');
    item.age = std::stoi(line.substr(0, pos));
    line.erase(0, pos + 1);

    pos = line.find(',');
    item.type = std::stoi(line.substr(0, pos));
    line.erase(0, pos + 1);

    pos = line.find(',');
    item.origin = std::stoi(line.substr(0, pos));
    line.erase(0, pos + 1);

    item.rarityScore = std::stod(line);

    items.push_back(item);
  }
  
  file.close();
  return items;
}

void writeItemsToFile(const std::string& filename, const std::vector<Item>& items) {
  FILE* file = fopen(filename.c_str(), "w");

  if (file == nullptr){
    std::cerr << "File could not be opened" << std::endl;
  }

  fprintf(file, "age,type,origin,rarity\n");      // Write header

  for (size_t i = 0; i < items.size(); i++){
    fprintf(file, "%d,%d,%d,%.1lf\n", items[i].age, items[i].type, items[i].origin, items[i].rarityScore);
  }

  fclose(file);
}