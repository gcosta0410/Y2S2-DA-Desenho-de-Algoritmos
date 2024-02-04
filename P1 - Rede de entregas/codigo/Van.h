#ifndef DA_T1_G113_VAN_H
#define DA_T1_G113_VAN_H

#include "Order.h"
#include <vector>

class Van {
private:
    unsigned int volMax, maxWeight, cost, currentWeight = 0, currentVol = 0;
    std::vector<Order *> orders;
public:
    Van(unsigned int volMax,unsigned int maxWeight, unsigned int cost) : volMax(volMax), maxWeight(maxWeight), cost(cost){}
    unsigned int getVolMax() const;
    unsigned int getMaxWeight() const;
    unsigned int getCost() const;
    bool operator== (const Van& v2) const;
    bool operator!= (const Van& v2) const;
    void addToCurrentWeight(int weight);
    void addToCurrentVol(int volume);
    void addOrder(Order* order);
    std::vector<Order *> getOrders();
    bool canAddOrder(Order* order) const;
};


#endif //DA_T1_G113_VAN_H
