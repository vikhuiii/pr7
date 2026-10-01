#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#define DEBUG_MODE
#define NAME_F "f.txt"

class Sclad {
    private:
    int art=0;
    std::string name="";
    std::string category="";
    double price=0;
    int count=0;
    int minOst=0;
public:
    void setArt(int value) {
        art = value;
    }
    void setName(std::string value) { 
        name = value;
    }
    void setCat(std::string value) { 
        category = value; }
    void setPrice(double value) { 
        price = value; }
    void setCount(int value) { 
        count = value; }
    void setMinOst(int value) { 
        minOst = value; }
    std::string GetName() { return name; }
    std::string GetCat() { return category; }
    int GetCount() { return count; }
    int GetMinOst() { return minOst; }
    double GetPrice() { return price; }
   
    void printInfo() {
        std::cout << "Артикул: " << art << std::endl;
        std::cout << "Название: " << name << std::endl;
        std::cout << "Категория: " << category << std::endl;
        std::cout << "Цена: " << price << std::endl;
        std::cout << "Количество: " << count << std::endl;
        std::cout << "Минимальный остаток: " << minOst << std::endl;
    }

};



void SetObj(Sclad sc, std::string str) {
    std::size_t razd = str.find(";");
    if (razd != std::string::npos)
        sc.setArt(std::stoi(str.substr(0, razd - 1)));
    std::string  s = str.substr(razd + 1);
    std::size_t razd2 = s.find(";");
    if (razd2 != std::string::npos)
        sc.setName(s.substr(0, razd2 - 1));
    s = s.substr(razd2 + 1);
    razd = s.find(";");
    if (razd != std::string::npos)
        sc.setCat(s.substr(0, razd - 1));
    s = s.substr(razd + 1);
    razd2 = s.find(";");
    if (razd2 != std::string::npos)
        sc.setPrice(std::stod(s.substr(0, razd2 - 1)));
    s = s.substr(razd2 + 1);
    razd = s.find(";");
    if (razd != std::string::npos)
        sc.setCount(std::stoi(s.substr(0, razd - 1)));
    s = s.substr(razd + 1);
    razd2 = s.find(";");
    if (razd2 != std::string::npos)
        sc.setMinOst(std::stoi(s.substr(0, razd2 - 1)));
}


int main()
{
    setlocale(LC_ALL, "Russian");

    try {

        std::ifstream file(NAME_F, std::ios::in);
        if (!file.is_open())
        {
           throw std::runtime_error( "Ошибка открытия файла");
            return 1;
        }

        Sclad sc;
        std::string str = "";
        Sclad allT[10];
        int count = 0;
       // try {
            while (std::getline(file, str)) {
                SetObj(sc, str);
                allT[count] = sc;
                count++;
            }
            file.close();
       // } catch (std::invalid_argument& e) { std::cout << "Ошибка формата\n" << e.what(); }

#ifdef DEBUG_MODE
        std::cout << "Загружено записей: " << count << std::endl;
        for (int i = 0; i < count; i++) {
            std::cout << allT[i].GetName();
        }
#endif //DEBUG_MODE

        std::string findN = "";
        std::cout << "Введите название товара, который хотите найти:";
        std::cin >> findN;
        std::cout << "\nРезультат:\n";
        for (int i = 0; i < count; i++) {
            if (allT[i].GetName() == findN)
            {
                allT[i].printInfo();
                std::cout << std::endl;
            }
        }

        std::cout << "Введите название категории: ";
        std::string findC = "";
        std::cin >> findC;

        std::cout << "\nТовары категории " << findC << ":\n";
        for (int i = 0; i < count; i++) {
            if (allT[i].GetCat() == findC)
            {
                allT[i].printInfo();
                std::cout << std::endl;
            }
        }

        std::cout << "Товары, запас которых ниже минимального: \n";
        for (int i = 0; i < count; i++) {
            if (allT[i].GetCount() < allT[i].GetMinOst())
            {
                allT[i].printInfo();
                std::cout << std::endl;
            }
        }

        std::string newS;
        std::cout << "Поступление товара\nВведите артикул\n";

        int art;
        std::cin >> art;
        newS += art + ";";
        std::cout << "Введите название\n";
        std::string name;

        std::cin >> name; newS += name + ";";
        std::cout << "Введите категорию\n";
        std::string cat;

        std::cin >> cat;  newS += cat + ";";
        std::cout << "Введите цену\n";
        double price;

        std::cin >> price; newS += std::to_string(price) + ";";
        std::cout << "Введите количество\n";
        int c;
        std::cin >> c;
        newS += c + ";";
        std::cout << "Минимальный допустимый остаток\n";
        int min;
        std::cin >> min;
        newS += min;

        std::ofstream dob(NAME_F, std::ios::app);
        if (!dob.is_open()) {
            std::cout << "Ошибка открытия";
            return 1;
        }
        dob << newS;
        dob.close();
#ifdef DEBUG_MODE
        std::cout << "\nВсе записи:\n";
        while (std::getline(file, str)) {
            std::cout << str << std::endl;
        }
        file.close();
#endif // DEBUG_MODE

        double allPr = 0;
        for (int i = 0; i < count; i++) {
            allPr += allT[i].GetPrice() * allT[i].GetMinOst();
        }
        std::cout << "Общая стоимость остатков = " << allPr;
    }
    catch (std::runtime_error& e) {
        std::cout << e.what();
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
}

