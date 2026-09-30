#include <iostream>
#include <fstream>
#include <string>

#define DEBUG_MODE
#define NAME_F "f.txt"

class Sclad {
    private:
    int art;
    std::string name;
    std::string category;
    double price;
    int count;
    int minOst;
public:
    void setArt(int value) { art = value; }
    void setName(std::string value) { name = value; }
    void setCat(std::string value) { category = value; }
    void setPrice(double value) { price = value; }
    void setCount(int value) { count = value; }
    void setMinOst(int value) { minOst = value; }
    std::string GetName() { return name; }
    std::string GetCat() { return category; }
    int GetCount() { return count; }
    int GetMinOst() { return minOst; }
   
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
  int razd = str.find(";");
        if (razd != std::string::npos)
            sc.setArt(std::stoi(str.substr(0, razd-1)));
        int razd2 = str.find(";", razd);
        if (razd2 != std::string::npos)
            sc.setName(str.substr(razd + 1, razd2 - 1));
        razd = str.find(";", razd2);
        if (razd != std::string::npos)
            sc.setCat(str.substr(razd2 + 2, razd - 1));
        razd2 = str.find(";", razd);
        if (razd2 != std::string::npos)
            sc.setPrice(std::stod(str.substr(razd + 1, razd2 - 1)));
        razd = str.find(";", razd2);
        if (razd != std::string::npos)
            sc.setCount(std::stoi(str.substr(razd2 + 1, razd - 1)));
        razd2 = str.find(";", razd);
        if (razd2 != std::string::npos)
            sc.setMinOst(std::stoi(str.substr(razd + 1, razd2 - 1)));
}


int main()
{
    setlocale(LC_ALL, "Russian");
    std::ifstream file(NAME_F, std::ios::in);
    if (!file.is_open())
    {
        std::cout << "Ошибка открытия файла";
        return 1;
    }

    Sclad sc;
    std::string str = "";
    Sclad allT[10];
    int count;

    while (std::getline(file, str)) {
        SetObj(sc, str);
        allT[0] = sc;
        count++;
    }

#ifdef DEBUG_MODE
    std::cout << "Загружено записей: " << count << std::endl;
#endif

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
    std::string findC="";
    std::cin >> findC;

    std::cout << "\nТовары категории "<<findC<<":\n";
    for (int i = 0; i < count; i++) {
        if (allT[i].GetCat() == findC)
        {
            allT[i].printInfo();
            std::cout << std::endl;
        }
    }

    std::cout << "Товары, запас которых ниже минимального: \n";
    for (int i = 0; i < count; i++) {
        if(allT[i].GetCount()<allT[i].GetMinOst())
        {
            allT[i].printInfo();
            std::cout << std::endl;
        }
    }

}
