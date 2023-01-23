#include <iostream>
#include <iterator>
#include <list>

using namespace std;

class ClotheInterface {
public:
    // Empty virtual destructor for proper cleanup
    virtual ~ClotheInterface() {}

    virtual string CheckSize() = 0;
    virtual void TryItIn() = 0;
    virtual void Change() = 0;
    virtual int GetPrice() = 0;
};

class Clothes : public ClotheInterface {
public:
    Clothes(string size, int price, int weight = 1) {
        this->size = size;
        this->price = price;
        this->weight = weight;
    }

    string CheckSize() {
        return size;
    }
    int GetPrice() {
        return price;
    }
    int GetWeight() {
        return weight;
    }
    void TryItIn() {

    }
    void Change() {

    }

private:
    string size;
    int price;
    int weight;
};

class ToolsAbstract {
public:


    void ChargeIt() {};

    virtual int GetPrice() = 0; // make ToolsAbstract not instantiable

};

class Tools : public ToolsAbstract {
public:
    Tools(int price, int weight = 0) {
        this->price = price;
        this->weight = weight;
    }

    void Check() {

    }
    void TryItOut() {

    }

    int GetPrice() {
        return price;
    }

    int GetWeight() {
        return weight;
    }
private:
    int price;
    int weight;
};





class Closet {
public:
    Closet() {
        maxWeight = 0;
        elementCapacity = 0;
    }
protected:
    int maxWeight;
    int elementCapacity;

};

class ClothesCloset : public Closet {
public:
    ClothesCloset(int maxWeight, int elementCapacity) {
        this->maxWeight = maxWeight;
        this->elementCapacity = elementCapacity;
    }

    void addClothes(Clothes clothes) {
        clothesList.push_back(clothes);
    }

    list<Clothes> getClothesList () {
        return clothesList;
    }

private:
    list<Clothes> clothesList;
};

class ToolsCloset : public Closet {
public:
    ToolsCloset(int maxWeight, int elementCapacity) {
        this->maxWeight = maxWeight;
        this->elementCapacity = elementCapacity;
    }

    bool addTools(Tools tools) {
        bool succesfullyAdded = false;

        if (elementCapacity - 1 > 0 && maxWeight - tools.GetWeight() > 0) {
            toolsList.push_back(tools);
            elementCapacity--;
            maxWeight -= tools.GetWeight();
            succesfullyAdded = true;
        }

        return succesfullyAdded;
    }

    list<Tools> getToolsList() {
        return toolsList;
    }

private:
    list<Tools> toolsList;
};


class SizeClotheFunctor {
public: 
    void operator() (Clothes clothes) {
        if (clothes.CheckSize() == "S") sizeS++;
        if (clothes.CheckSize() == "M") sizeM++;
        if (clothes.CheckSize() == "L") sizeL++;
        if (clothes.CheckSize() == "XL") sizeXL++;
    }

    void printSizes() {
        cout << "Size S amount:" << sizeS <<endl;
        cout << "Size M amount:" << sizeM << endl;
        cout << "Size L amount:" << sizeL << endl;
        cout << "Size XL amount:" << sizeXL << endl;
    }
private:
    int sizeS = 0;
    int sizeM = 0;
    int sizeL = 0;
    int sizeXL = 0;
};

template<typename T>
int TotalAmountOfCloset(list<T> closet) {
    int totalAmount = 0;

    for (auto stuf : closet) {
        totalAmount = stuf.GetPrice();
    }

    return totalAmount;
}

template<typename T>
int TotalWeightOfCloset(list<T> closet) {
    int totalWeight = 0;

    for (auto stuf : closet) {
        totalWeight = stuf.GetWeight();
    }

    return totalWeight;
}


int main()
{
#pragma region PrepareData
    ToolsCloset toolsCloset = ToolsCloset(10, 20);
    ClothesCloset clothesCloset = ClothesCloset(10, 20);

    toolsCloset.addTools(Tools(20));
    toolsCloset.addTools(Tools(20));
    toolsCloset.addTools(Tools(20));
    toolsCloset.addTools(Tools(20));

    clothesCloset.addClothes(Clothes("S", 10));
    clothesCloset.addClothes(Clothes("M", 10));
    clothesCloset.addClothes(Clothes("L", 10));
    clothesCloset.addClothes(Clothes("XL", 10));
#pragma endregion PrepareData

#pragma region Functor
    SizeClotheFunctor sizeclothesFunctor;

    for (auto clothes : clothesCloset.getClothesList()) {
        sizeclothesFunctor(clothes);
    }

    sizeclothesFunctor.printSizes();
    cout << endl;
#pragma endregion

#pragma region Template
    cout << "Tools" << endl;
    cout<< "Total Amount of tools:"<< TotalAmountOfCloset(toolsCloset.getToolsList()) << endl;
    cout<< "Total Weight of tools:"<< TotalWeightOfCloset(toolsCloset.getToolsList()) << endl;
    cout << endl;

    cout << "Clothes" << endl;
    cout << "Total Amount:" << TotalAmountOfCloset(clothesCloset.getClothesList()) << endl;
    cout << "Total Weight:" << TotalWeightOfCloset(clothesCloset.getClothesList()) << endl;
    cout << endl;
#pragma endregion


}
