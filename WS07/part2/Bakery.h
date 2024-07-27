// 151593225
// 2024.07.11
// Tzu Han Chao
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.

#ifndef SENECA_BAKERY_H
#define SENECA_BAKERY_H
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
namespace seneca {
enum class BakedType { BREAD, PASTERY };

struct BakedGood {
  BakedType m_type; // either BREAD or PASTERY from the above enum
  std::string m_description;
  int m_shelfLife;
  int m_stock;
  double m_price;
};
std::ostream &operator<<(std::ostream &out, const BakedGood &b);

class Bakery {
  // Lastly define a class called Bakery that manages a collection of objects of
  // type BakedGood...... fuck..
  std::vector<BakedGood> m_goods;

public:
  // receives as a parameter the name of the file containing the information
  // about the BakedGoods to be added to the collection.
  Bakery(const std::string fileName);
  // print the content of the collection into the parameter.
  void showGoods(std::ostream &os) const;
  // sort
  void sortBakery(const std::string field);
  // combne
  std::vector<BakedGood> combine(const Bakery &b);

  bool inStock(const std::string description, const BakedType type) const;
  std::list<BakedGood> outOfStock(const BakedType type) const;
};

} // namespace seneca

#endif
