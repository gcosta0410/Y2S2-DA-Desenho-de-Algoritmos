#include "Van.h"

/**
 * @brief Returns the max volume supported by the van
 * @return volMax
 */
unsigned int Van::getVolMax() const {
    return volMax;
}

/**
 * @brief Returns the max weight supported by the van
 * @return maxWeight
 */
unsigned int Van::getMaxWeight() const {
    return maxWeight;
}

/**
 * @brief Returns the cost of a van
 * @return cost
 */
unsigned int Van::getCost() const {
    return cost;
}

/**
 * @brief Checks if two vans are equal, by having the same attributes
 * @param v2
 * @return
 */
bool Van::operator==(const Van &v2) const {
    return volMax == v2.volMax && maxWeight == v2.maxWeight && cost == v2.cost;
}

/**
 * @brief Checks if two vans are different
 * @param v2
 * @return
 */
bool Van::operator!=(const Van &v2) const {
    return !(*this == v2);
}

/**
 * @brief Increments the current weight
 * @param weight
 */
void Van::addToCurrentWeight(int weight) {
    currentWeight += weight;
}

/**
 * @brief Increments the current volume
 * @param volume
 */
void Van::addToCurrentVol(int volume) {
    currentVol += volume;
}

/**
 * @brief Adds an order to the van's current orders
 * @param order
 */
void Van::addOrder(Order *order) {
    orders.push_back(order);
    addToCurrentVol(order->getVolume());
    addToCurrentWeight(order->getWeight());
}

/**
 * @brief Returns van's current orders
 * @return orders
 */
std::vector<Order *> Van::getOrders() {
    return orders;
}

/**
 * @brief Checks if an order can be added, by calculating the new current weight and volume
 * @param order
 * @return
 */
bool Van::canAddOrder(Order* order) const {
    return (currentWeight + order->getWeight() <= maxWeight) && (currentVol + order->getVolume() <= volMax);
}


