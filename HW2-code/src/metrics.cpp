#include "methods.h"

int getMax(std::vector<Item>& items, const std::string& attribute){
  if (attribute == "age"){
    int m_age = 0;

    for (size_t i = 0; i < items.size()-1; i++){
      m_age = std::max(m_age, items[i].age);
    }
    return m_age;

  }else if (attribute == "rarity"){
    double m_rarity = 0;

    for (size_t i = 0; i < items.size()-1; i++){
      m_rarity = std::max(m_rarity, items[i].rarityScore);
    }
    return m_rarity;
    
  }else{    // it isn't meaningful to get the maximum value of another attribute
    std::cout << "Wrong attribute input!" << std::endl;
    return -1;
  }
}

// min = age - ageWindow
// max = age + ageWindow
// rarityScore = (1 - probability) * (1 + item.age/ageMax)
void calculateRarityScores(std::vector<Item>& items, int ageWindow){
  int m_age = getMax(items, "age");

  for (size_t i = 0; i < items.size(); i++){
    int leftb = (items[i].age - ageWindow > 0) ? items[i].age - ageWindow : 0;            // lower bound for age
    int rightb = (items[i].age + ageWindow < m_age) ? items[i].age + ageWindow : m_age;   // upper bound for age
    int countSimilar = 0;
    int countTotal = 0;

    for (size_t j = 0; j < items.size(); j++){
      if (items[j].age >= leftb && items[j].age <= rightb){
        countTotal++;
        if (items[i].type == items[j].type && items[i].origin == items[j].origin){
          countSimilar++;
        }
      }
    }
    
    // calculate rarity score and assign here
    if (countTotal>0){
      double prob = static_cast<double>(countSimilar) / static_cast<double>(countTotal);
      items[i].rarityScore = (1.0 - prob) * (1.0 + (static_cast<double>(items[i].age) / static_cast<double>(m_age)));
    }
    else{
      items[i].rarityScore = 1.0 + (static_cast<double>(items[i].age) / static_cast<double>(m_age));
    }
  }
}
