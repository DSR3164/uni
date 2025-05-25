#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Car {
public:
    string company; //Марка
    string model; //Модель
    int year; //Год производст

    Car(string company, string model, int year) {
        this->company = company;
        this->model = model;
        this->year = year;
    }
};

void BubbleSort(vector<Car>& arr) { //Сортировка пузырьком
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j].year < arr[j + 1].year) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    const int Year = 2009; //Критерий для фильтра

    Car car_1("Tesla", "Plaid", 2021);
    Car car_2("Toyota", "Mark II", 1992);
    Car car_3("Toyota", "Supra", 2002);
    Car car_4("Toyota", "Chaser", 2000);
    Car car_5("Toyota", "Soarer", 2001);
    Car car_6("Toyota", "Altezza", 2003);
    Car car_7("Toyota", "Celica", 2004);
    Car car_8("Toyota", "MR2", 2005);
    Car car_9("Tesla", "Model S", 2020);
    Car car_10("Tesla", "Model X", 2019);
    Car car_11("Tesla", "Model 3", 2018);
    Car car_12("Tesla", "Roadster", 2008);
    Car car_13("Tesla", "Model Y", 2022);
    Car car_14("Tesla", "Cybertruck", 2023);
    Car car_15("Tesla", "Semi", 2024);


    vector<Car> list;

    list.push_back(car_1);
    list.push_back(car_2);
    list.push_back(car_3);
    list.push_back(car_4);
    list.push_back(car_5);
    list.push_back(car_6);
    list.push_back(car_7);
    list.push_back(car_8);
    list.push_back(car_9);
    list.push_back(car_10);
    list.push_back(car_11);
    list.push_back(car_12);
    list.push_back(car_13);
    list.push_back(car_14);
    list.push_back(car_15);

    vector<Car> newlist;

    for (auto it = list.begin(); it != list.end();) {
        if (((it->company == "Tesla") && it->year < Year) || ((it->company == "Toyota") && it->year < Year)) {
            newlist.push_back(*it);
            it = list.erase(it);
        } else {
            ++it;
        }
    }

    BubbleSort(list);
    BubbleSort(newlist);

    cout << "Список старых (крутых) моделей машин:\n" << endl;
    for (auto it = newlist.begin(); it != newlist.end(); it++) {
        cout << it->company << "\t" << it->model << "\t" << it->year << endl;
    }

    cout << "\nСписок новых моделей машин:\n" << endl;
    for (auto it = list.begin(); it != list.end(); it++) {
        cout << it->company << "\t" << it->model << "\t" << it->year << endl;
    }

    return 0;
}
