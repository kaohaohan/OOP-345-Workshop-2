#ifndef SENECA_BAKERY_H
#define SENECA_BAKERY_H
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <algorithm>
namespace seneca
{
   enum class BakedType {
    BREAD,
    PASTERY
};

    struct BakedGood {
    BakedType m_type; //either BREAD or PASTERY from the above enum
    std::string m_description;
    int m_shelfLife;
    int m_stock;
    double m_price;
};
std::ostream& operator<<(std::ostream& out, const BakedGood& b);

    class Bakery{
        //Lastly define a class called Bakery that manages a collection of objects of type BakedGood......
        //fuck..
        std::vector<BakedGood> m_goods;
        public:
            
        // receives as a parameter the name of the file containing the information about the
        // BakedGoods to be added to the collection.
            Bakery(const std::string fileName);
        // print the content of the collection into the parameter. 
            void showGoods(std::ostream& os) const;
    };


}

#endif
