//
// 2024.07.14
// Hao Han Kao
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.

#include "Bakery.h"
#include <numeric>
namespace seneca {

std::string trim(const std::string &line) {
  size_t start = line.find_first_not_of(' ');
  size_t end = line.find_last_not_of(' ');
  // substr second arg is length of string. so end-start-1;
  return line.substr(start, end - start + 1);
}
void extractLineToBackGood(const std::string &line, BakedGood &bakeGood) {
  // Bread   Pumpernickel Loaf   5              12      4.55
  std::string typeStr = trim(line.substr(0, 8));
  std::string description = trim(line.substr(8, 20));
  std::string shelfLife = trim(line.substr(28, 14));
  std::string stock = trim(line.substr(42, 8));
  std::string price = trim(line.substr(50, 6));
  // Find if Bread or Pastry!!!! typeStr is string. I can't assign to m_type
  if (typeStr == "Bread") {
    // get BREAD from BakedType:: !!! plz remember it
    bakeGood.m_type = BakedType::BREAD;
  } else if (typeStr == "Pastry") {
    bakeGood.m_type = BakedType::PASTERY;
  } else {
    throw std::invalid_argument("Someting went Wrong...");
  }
  // casting!! use stoi or stod

  bakeGood.m_description = description;
  bakeGood.m_shelfLife = std::stoi(shelfLife);
  bakeGood.m_stock = std::stoi(stock);
  bakeGood.m_price = std::stod(price);
}

Bakery::Bakery(const std::string fileName) {
  // 讀檔案
  std::ifstream inputFile(fileName);
  if (!inputFile) {
    throw std::runtime_error("Could not open file!!");
  } else {
    std::string line;
    while (std::getline(inputFile, line)) {
      BakedGood bakeGood;
      extractLineToBackGood(line, bakeGood);
      // put the bakeGood to vecotr m_goods;
      m_goods.push_back(bakeGood);
    }
  }
}
std::ostream &operator<<(std::ostream &out, const BakedGood &b) {
  std::string type;
  switch (b.m_type) {
  case BakedType::PASTERY:
    type = "Pastry";
    break;
  case BakedType::BREAD:
    type = "Bread";
    break;
  default:
    type = "UNKNOWN";
    break;
  }

  out << "* ";
  out.width(10);
  out << std::left << type;
  out << " * ";
  out.width(20);
  out << b.m_description;
  out << " * ";
  out.width(5);
  out << b.m_shelfLife;
  out << " * ";
  out.width(5);
  out << b.m_stock;
  out << " * ";
  out.width(8);
  out << std::setprecision(2) << std::fixed << std::right << b.m_price;
  out << " * ";

  return out;
};

void Bakery::showGoods(std::ostream &os) const {
  // I can't not use for
  // use for each
  std::for_each(m_goods.begin(), m_goods.end(), [&os](BakedGood good) {
    os << good << std::endl;
    // stock
  });
  // use lambda
  int stockSum = std::accumulate(
      m_goods.begin(), m_goods.end(), 0,
      [](int total, BakedGood current) { return total + current.m_stock; });
  double priceSum = std::accumulate(
      m_goods.begin(), m_goods.end(), 0.0,
      [](double total, BakedGood current) { return total + current.m_price; });
  os << "Total Stock: " << stockSum << std::endl;
  os << "Total Price: " << priceSum << std::endl;
}

void Bakery::sortBakery(const std::string field) {
  std::sort(m_goods.begin(), m_goods.end(), [&field](BakedGood a, BakedGood b) {
    if (field == "Description") {
      return a.m_description < b.m_description;
    } else if (field == "Shelf") {
      return a.m_shelfLife < b.m_shelfLife;

    } else if (field == "Stock") {
      return a.m_stock < b.m_stock;
    } else if (field == "Price") {
      return a.m_price < b.m_price;
    } else {
      throw std::invalid_argument("Invalid field name for sorting");
    }
  });
}
std::vector<BakedGood> Bakery::combine(const Bakery &b) {
  // it need to sort first before merge
  // this one killing mw, I spend 2 hours to figure out how to use merge to
  // match the output
  std::vector<BakedGood> backery1 = m_goods;
  std::sort(backery1.begin(), backery1.end(),
            [](const BakedGood &a, const BakedGood &b) {
              return a.m_price < b.m_price;
            });

  std::vector<BakedGood> backery2 = b.m_goods;
  std::sort(backery2.begin(), backery2.end(),
            [](const BakedGood &a, const BakedGood &b) {
              return a.m_price < b.m_price;
            });

  std::vector<BakedGood> combined;
  std::merge(backery1.begin(), backery1.end(), backery2.begin(), backery2.end(),
             std::back_inserter(combined),
             [](const BakedGood &a, const BakedGood &b) {
               return a.m_price < b.m_price;
             });

  return combined;
}

bool Bakery::inStock(const std::string description,
                     const BakedType type) const {

  auto it = std::find_if(m_goods.begin(), m_goods.end(),
                         [&description, &type](BakedGood good) {
                           return good.m_description == description &&
                                  good.m_type == type && good.m_stock > 0;
                         });

  if (it != m_goods.end()) {
    return true;
  } else {
    return false;
  }
}
std::list<BakedGood> Bakery::outOfStock(const BakedType type) const {
  std::list<BakedGood> result;

  std::copy_if(m_goods.begin(), m_goods.end(), std::back_inserter(result),
               [&type](BakedGood good) {
                 return good.m_stock == 0 && good.m_type == type;
               });

  result.sort([](const BakedGood &a, const BakedGood &b) {
    return a.m_price < b.m_price;
  });

  return result;
}

} // namespace seneca