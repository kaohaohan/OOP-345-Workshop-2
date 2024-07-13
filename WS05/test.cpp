#include<string>

#include<vector>
#include <iostream>
     std::string removeHeadTailSpace(const std::string &s)
    {
        // 去頭尾space
        size_t start = s.find_first_not_of(' ');
        size_t last = s.find_last_not_of(' ');
        return s.substr(start, last - start + 1);
    }
int main() {

    std::string test="Miguel de Cervantes,     Don Quixote,     Spain,    9.99,    1612,   The story follows a Hidalgo, Alonso Quixano, who proves that chivalry will in fact never die.";
   

    std::vector<std::string> data;
        std::string word;
        int count =0;
        //size()會return size_t
        for ( size_t i=0;i<test.size();i++){
            char c =test[i]; 
            if(c!=','&& count<5){
                word+=c;
            }else{
                if (count<5) {
                    word= removeHeadTailSpace(word);
                    data.push_back(word);
                    count++;
                    word.clear();
                } else {
                     word+=c;
                }

            }

        }
        
        word= removeHeadTailSpace(word);
        data.push_back(word);
        

        
   for(size_t i=0;i<data.size();i++){
        std::cout<< data[i]<<   std::endl;

   }
         
    return 0;
}