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

enum class car_brand { Mercedes, Man, Ford, Volvo, Iveco, Scania, Volkswagen, Mitsubishi, None }; /// Enum representing the possibile Workshop's specialization

// TODO: 
// Falta fazer update das cenas no clearScreen()
// Falta fazer as funcoes de pesquisa indicadas no pdf
// Falta corrigir os bugs reportados no todolist.txt

class Workshop {
private:
	string name; /// Workshop's name
	car_brand brand; /// Workshop's brand specialization
	int unavailability; /// Unavailability duration in days
	queue<pair<Truck*, Date*>> waiting_line; /// Queue of Services, indicated by pairs of pointers to the truck and date the service finishes 
    Date* last_date;
public:
    ~Workshop();
    Date *getLastDate();
/**
 * @brief Constructor with all data necessary
 *
 * Receives all the data it needs to construct a Workshop properly
 *
 * @param n - Name of the workshops
 * @param b - Brand of car_brand type
 * @param unavailability - Number of days until available
 * @param wl - Queue of Services, indicated by pairs of pointers to the truck and date the service finishes 
 */
    Workshop(string n, car_brand b, int unavailability, queue<pair<Truck*, Date*>> wl,Date date);
/**
* @brief Gets name
*
* Retrieves name of the Workshop
*
* @return Returns a string containing the name of the Workshop
*/
	string getName() const;
/**
* @brief Gets brand
*
* Retrieves brand of the Workshop
*
* @return Returns a car_brand type containing the brand of the Workshop
*/
	car_brand getBrand() const;
/**
* @brief Gets unavailability
*
* Retrieves unavailablilty of the Workshop
*
* @return Returns an unsigned int representing the unavailability of the Workshop
*/
	int getUnavailability() const;
/**
* @brief Gets waiting line
*
* Retrieves waiting line of the Workshop
*
* @return Returns a queue of pairs to Truck pointers and Date pointers containing the waiting line of the Workshop
*/
	queue<pair<Truck*, Date*>>* getWaitingLine();
/**
* @brief Sets name
*
* Sets name of the Workshop
*
* @param n - Name of the workshop
* @return Returns nothing
*/
	void setName(string n);
/**
* @brief Sets brand
*
* Sets brand of the Workshop
*
* @param b - Brand of type car_brand of the workshop
* @return Returns nothing
*/
	void setBrand(car_brand b);
/**
* @brief Sets unavailability
*
* Sets unavailability of the Workshop
*
* @param ua - Unavailability of the workshop
* @return Returns nothing
*/
	void setUnavailability(int ua);
/**
* @brief Sets waiting line
*
* Sets waiting line of the Workshop
*
* @param wl - waiting line of the workshop
* @return Returns nothing
*/
	void setWaitingLine(queue<pair<Truck*, Date*>> wl);
/**
 * @brief Loads the clients
 *
 * Loads the clients into the program by pushing them to the priority_queue
 *
 * @param workshopLine - pointer to the priority_queue where the pointers to the Workshops are stored
 * @return Returns nothing
 */
    static void loadFromFile(priority_queue<Workshop>* workshopLine);
/**
* @brief Saves the workshops
*
* Saves the workshops the user has added by writing to the workshops.txt file in the specified format
*
* @param workshopLine - pointer to the priority_queue where the pointers to the Workshops are stored
* @return Returns nothing
*/
    static void saveToFile(priority_queue<Workshop>* workshopLine);
/**
* @brief Adds a workshop
*
* Adds a workshop to the priority_queue
*
* @param workshopLine - pointer to the priority_queue where the pointers to the Workshops are stored
* @return Returns nothing
*/
    static void addWorkshop(priority_queue<Workshop>* workshop_line);
/**
* @brief Edits a workshop
*
* Edits the information of a workshop from the priority_queue
*
* @param workshopLine - pointer to the priority_queue where the pointers to the Workshops are stored
* @return Returns nothing
*/
    static void editWorkshop(priority_queue<Workshop>* workshop_line);
/**
* @brief Deletes a workshop
*
* Deletes a workshop from the priority_queue
*
* @param workshopLine - pointer to the priority_queue where the pointers to the Workshops are stored
* @return Returns nothing
*/
    static void deleteWorkshop(priority_queue<Workshop>* workshop_line);
/**
* @brief Calculates unavailability
*
* Calculates unavailability by checking the date (which will be the most recent date in the priority_queue)
*
* @param d1 - Date to calculate difference in minutes
* @return Returns an unsigned int representing the difference in days (converted from minutes)
*/
	static int calculateUnavailability(Date d1);
/**
* @brief Adds service
*
* Adds service to a given Workshop
*
* @param truck - pointer to the Truck to be added in service
* @param date - pointer to the Date it finishes the service
* @return Returns nothing
*/
    void addService(Truck* truck, Date date);
/**
*
* Prints the information of the Workshop
* @return Returns nothing
*/
	void info();
/**
* @brief Gets Workshops
*
* Retrieves a Workshop by searching the name
*
* @param name - name of the Workshop to look for
* @return Returns a pointer to the Workshop with name name and NULL if not found
*/
    static Workshop getWorkshop(string name);
/**
* @brief Operator < overloading
*
* Overload of < operator for comparisons. A Workshop is < if its unavailability is less than another Workshop's unavailability 
*
* @param w1 - Workshop Object containing the unavailability to be compared
* @return Returns true if the Workshop has a smaller unavailability
*/

    /**
* @brief Verifies if truck isn't in workshop
*
* Checks if the truck passsed as argument isn't in any Workshop getting a service
*
* @param truck - Truck Object to verify
* @return Returns true if the truck is in no Workshop
*/
static bool notInWorkshop(Truck* truck);

};

bool operator<(const Workshop &w1,const Workshop &w2);
