#ifndef DA_T1_G113_DELIVERYSERVICE_H
#define DA_T1_G113_DELIVERYSERVICE_H

#include "Order.h"
#include "Van.h"
#include "Courier.h"
#include <vector>
#include <string>

#define WORKING_HOURS_IN_SECONDS 28800 // 9h - 17h = 8h = 28800 seconds

class DeliveryService {
private:
    void loadOrders(const std::string& fileName = "input/encomendas.txt");
    void loadVans(const std::string& fileName  = "input/carrinhas.txt");
    void clearOrders();
    void clearVans();
    void sortOrderByTime();
    void sortOrderByHighestWeight();
    void sortOrderByHighestVolume();
    void sortOrderByHighestDensity();
    void sortOrderByHighestWeightVolume();
    void sortOrderByHighestWeightAndVolume();
    void sortVansByHighestWeight();
    void sortVansByHighestVolume();
    void sortVansByHighestDensity();
    void sortVansByHighestWeightVolume();
    void sortVansByHighestWeightAndVolume();
    void sortOrderByReward();
    void sortVansByProfit();
    void sortVansByPureProfit();
    std::vector<Order*> orders;
    std::vector<Van*> vans;
    std::vector<Courier*> couriers;
    int dp[451][400]; //396
public:
    void load(const std::string& ordersFileName = "input/encomendas.txt", const std::string& vansFileName = "input/carrinhas.txt");
    void clear();
    unsigned long long getNumOrders();
    unsigned long long getNumVans();
    const std::vector<Order *> &getOrders() const;
    const std::vector<Van *> &getVans() const;
    float optimizeExpressDeliveries();
    unsigned long long optimizeNormalDeliveries(int &ordersDelivered);
    unsigned long long optimizeNormalDeliveriesByVolume();
    unsigned long long optimizeNormalDeliveriesByDensity();
    int optimizeProfit(); // Dynamic programing
    int optimizeProfit2(); // Naïve
    int optimizeProfit3(); // Dynamic programing em matriz tridimensional com memoization
    int knapsack(int item, int weight, int volume, int W_max,int Vol_max, int n);
    void prepareKnapsack(int i);
    std::vector<int> getItens(int profit);
    void addOrdersToVan(int vanInt, std::vector<int> ordersForDeliver);
    int checkItems(std::vector<int> &ordersForDelivery, int vanId);
    int addOrders(int i);
    void sortOrderByPureReward();
};

#endif //DA_T1_G113_DELIVERYSERVICE_H
