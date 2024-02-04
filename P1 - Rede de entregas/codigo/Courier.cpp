#include "Courier.h"

int Courier::idCounter = 1;

/**
 * @brief Gets Courier ID
 * @return id
 */
int Courier::getId() const {
    return id;
}

/**
 * @brief Gets Courier Van
 * @return Van
 */
Van *Courier::getVan() const {
    return van;
}

/**
 * @brief Gets Courier orders
 * @return vector that contains the orders
 */
const std::vector<Order *> &Courier::getOrders() const {
    return orders;
}

/**
 * @brief Sets Courier ID
 * @return
 */
void Courier::setId(int id) {
    Courier::id = id;
}

/**
 * @brief Sets Courier Van
 * @return
 */
void Courier::setVan(Van *van) {
    Courier::van = van;
}

/**
 * @brief Sets Courier orders
 * @return
 */
void Courier::setOrders(const std::vector<Order *> &orders) {
    Courier::orders = orders;
}

/**
 * @brief Adds an order to the Courier's orders
 * @return
 */
void Courier::addOrder(Order *order) {
    orders.push_back(order);
    current_volume += order->getVolume();
    current_weight += order->getWeight();
}

/**
 * @brief Empties Courier's orders
 * @return
 */
void Courier::clearOrders() {
    if(orders.empty()) return;
    orders.clear();
}

/**
 * @brief Gets Courier current orders total volume
 * @return current volume
 */
int Courier::getCurrentVolume() const {
    return current_volume;
}

/**
 * @brief Gets Courier current orders total weight
 * @return current weight
 */
int Courier::getCurrentWeight() const {
    return current_weight;
}
