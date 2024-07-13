#include "Bakery.h"
namespace seneca{

     std::string trim(const std::string &line){
        size_t start= line.find_first_not_of(' ');
        size_t end= line.find_last_not_of(' ');
        //substr second arg is length of string. so end-start-1;
        return line.substr(start,end-start+1);

     }
     void extractLineToBackGood(const std::string &line, BakedGood &bakeGood ){
            //Bread   Pumpernickel Loaf   5              12      4.55  
            std::string typeStr = trim(line.substr(0, 8));
            std::string description = trim(line.substr(8, 20));
            std::string shelfLife = trim(line.substr(28, 14));
            std::string stock = trim(line.substr(42, 8));
            std::string price = trim(line.substr(50, 6));
            //Find if Bread or Pastry!!!! typeStr is string. I can't assign to m_type
            if(typeStr=="Bread"){
                //get BREAD from BakedType:: !!! plz remember it 
                bakeGood.m_type =BakedType::BREAD;
            }else if(typeStr=="Pastry"){
                bakeGood.m_type = BakedType::PASTERY;
            }else{
                throw std::invalid_argument("Someting went Wrong...");
            }
            //casting!! use stoi or stod 

            bakeGood.m_description =description;
            bakeGood.m_shelfLife= std::stoi(shelfLife);
            bakeGood.m_stock =std::stoi(stock);
            bakeGood.m_price = std::stod(price);
            
     }


     Bakery::Bakery(const std::string fileName){
        //讀檔案
        std::ifstream inputFile(fileName);
        if (!inputFile){
            throw std::runtime_error("Could not open file!!");
        }else{
            std::string line;
            while( std::getline(inputFile,line)){
                 BakedGood bakeGood;
                 extractLineToBackGood(line,bakeGood);
                 //put the bakeGood to vecotr m_goods;
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


     void Bakery::showGoods(std::ostream& os) const{
            //I can't not use for 
            //use for each 
             std::for_each(m_goods.begin(), m_goods.end(), [&os](BakedGood good) {
             os<< good << std::endl;
        });
     }
}