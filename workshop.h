#pragma once
#include <queue>
#include <string>
#include <utility>

#include "date.h"
#include "truck.h"
#include "company.h"
#include "misc.h"

using namespace std;

class Date;
class Truck;

enum class car_brand { Mercedes, Man, Ford, Volvo, Iveco, Scania, Volkswagen, Mitsubishi, None}; /// Enum representing the possibile Workshop's specialization

// TODO: falta comentar as funcoes e fazer as funcoes de pesquisa com static
// Fazer funcoes de load e save

class Workshop {
private:
    string name; /// Workshop's name
    car_brand brand; /// Workshop's brand specialization
    unsigned int unavailability; /// Unavailability duration in days
    queue<pair<Truck*, Date*>> waiting_line; /// Queue of pointers to Trucks assigned to the given Workshop (ordered by FIFO)
public:
    Workshop(string n, car_brand b, unsigned unavailability, queue<pair<Truck*, Date*>> wl);
    
    string getName() const;
    car_brand getBrand() const;
    unsigned int getUnavailability() const;
    queue<pair<Truck*, Date*>> getWaitingLine() const;
    
    void setName(string n);
    void setBrand(car_brand b);
    void setUnavailability(unsigned int ua);
    void setWaitingLine(queue<pair<Truck*, Date*>> wl);

    static void loadFromFile();
    static void saveToFile();

    void info();

    bool operator<(Workshop w1);

};