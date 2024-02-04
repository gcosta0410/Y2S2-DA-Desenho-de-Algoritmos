#ifndef DA_T1_G113_COURIER_H
#define DA_T1_G113_COURIER_H

#include "Van.h"
#include "Order.h"
#include <vector>

class Courier {
private:
    static int idCounter;
    int id, current_weight, current_volume;
    Van *van;
    std::vector<Order*> orders;


public:
    Courier(Van *van): van(van){this->id = idCounter; idCounter++;}
    int getId() const;
    Van *getVan() const;
    const std::vector<Order *> &getOrders() const;
    void setId(int id);
    void setVan(Van *van);
    void setOrders(const std::vector<Order *> &orders);
    void addOrder(Order* order);
    void clearOrders();
    int getCurrentWeight() const;
    int getCurrentVolume() const;

};

#endif //DA_T1_G113_COURIER_H
