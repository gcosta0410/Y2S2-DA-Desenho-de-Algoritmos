#include "Order.h"

/**
 * Gets order volume
 * @return volume
 */
unsigned int Order::getVolume() const {
    return volume;
}

/**
 * Gets order weight
 * @return weight
 */
unsigned int Order::getWeight() const {
    return weight;
}

/**
 * Gets order reward
 * @return reward
 */
int Order::getReward() const {
    return reward;
}

/**
 * Gets order time to complete
 * @return time
 */
unsigned int Order::getTime() const {
    return time;
}