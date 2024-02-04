#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "DeliveryService.h"

/**
 * @brief Loads orders from dataset to the vector orders
 * @param fileName
 */
void DeliveryService::loadOrders(const std::string& fileName) {
    std::string line, word;
    std::vector<std::string> row;
    std::fstream file (fileName, std::ios::in);
    if(file.is_open()){
        getline(file, line);
        while(getline(file, line)) {
            std::stringstream str(line);
            row.clear();
            while (getline(str, word, ' ')) {
                row.push_back(word);
            }
            orders.push_back(new Order(stoi(row.at(0)), stoi(row.at(1)),stoi(row.at(2)),stoi(row.at(3))));

        }
        file.close();

    }
    else
        std::cerr<<"Could not open the file\n";

}

/**
 * @brief Loads vans from dataset to the vector vans
 * @param fileName
 */
void DeliveryService::loadVans(const std::string& fileName) {
    std::string line, word;
    std::vector<std::string> row;
    std::fstream file (fileName, std::ios::in);
    if(file.is_open()){
        getline(file, line);
        while(getline(file, line)) {
            std::stringstream str(line);
            row.clear();
            while (getline(str, word, ' ')) {
                row.push_back(word);
            }
            Van *v = new Van(stoi(row.at(0)), stoi(row.at(1)),stoi(row.at(2)));
            vans.push_back(v);
            couriers.push_back(new Courier(v));
        }
        file.close();

    }
    else
        std::cerr<<"Could not open the file\n";

}

/**
 * @brief Calls loadOrders() and loadVans()
 * @param ordersFileName
 * @param vansFileName
 */
void DeliveryService::load(const std::string& ordersFileName, const std::string& vansFileName) {
    loadOrders(ordersFileName);
    loadVans(vansFileName);
}

/**
 * @brief gets total number of orders
 * @return total number of orders
 */
unsigned long long DeliveryService::getNumOrders() {
    return orders.size();
}

/**
 * @brief gets total number of vans
 * @return total number of vans
 */
unsigned long long DeliveryService::getNumVans() {
    return vans.size();
}

/**
 * @brief Gets orders vector
 * @return orders vector
 */
const std::vector<Order *> &DeliveryService::getOrders() const {
    return orders;
}

/**
 * @brief Gets vans vector
 * @return vans vector
 */
const std::vector<Van *> &DeliveryService::getVans() const {
    return vans;
}

/**
 * @brief Empties orders vector and vans vector
 *
 */
void DeliveryService::clear() {
    clearVans();
    clearOrders();
}

/**
 * @brief Empties vans vector
 */
void DeliveryService::clearVans() {
    if(vans.empty()) return
    vans.clear();
}

/**
 * @brief Empties orders vector
 */
void DeliveryService::clearOrders() {
    if(orders.empty()) return
    orders.clear();
}
/**
 * @brief Sorts orders by completion time
 */
void DeliveryService::sortOrderByTime() {
    std::sort(orders.begin(), orders.end(), [](Order *a, Order *b) { return (*a).getTime() < (*b).getTime(); });
}

/**
 * @brief Optimizes express deliveries (cen 3) by minimizing the average time for each express delivery. Then calculates the average time.
 * @return average time
 */
float DeliveryService::optimizeExpressDeliveries(){
    int time = 0;
    int counter = 0;
    float avgtime = 0;

    sortOrderByTime();
    auto courier = couriers.front();
    courier->clearOrders();

    for(auto order: orders){
        if(time + order->getTime() > WORKING_HOURS_IN_SECONDS) break;
        else{
            courier->addOrder(order);
            time += order->getTime();
            counter++;
            avgtime += time;
        }
    }
    orders.erase(orders.begin(),orders.begin()+counter);

    avgtime = avgtime / counter;
    return avgtime;
}

/**
 * @brief Sorts orders by highest weight
 */
void DeliveryService::sortOrderByHighestWeight() {
    std::sort(orders.begin(), orders.end(), [](Order *a, Order *b) { return (*a).getWeight() > (*b).getWeight(); });
}

/**
 * @brief Sorts orders by highest volume
 */
void DeliveryService::sortOrderByHighestVolume() {
    std::sort(orders.begin(), orders.end(), [](Order *a, Order *b) { return (*a).getVolume() > (*b).getVolume(); });
}

/**
 * @brief Sorts orders by highest weight/volume
 */
void DeliveryService::sortOrderByHighestDensity() {
    std::sort(orders.begin(), orders.end(), [](Order *a, Order *b) { return ((*a).getWeight() / (*a).getVolume()) > ((*b).getWeight() / (*b).getVolume()); });
}

/**
 * @brief Sorts orders by highest weight + volume
 */
void DeliveryService::sortOrderByHighestWeightVolume() {
    std::sort(orders.begin(), orders.end(), [](Order *a, Order *b) { return ((*a).getWeight() + (*a).getVolume()) > ((*b).getWeight() + (*b).getVolume()); });
}

/**
 * @brief Sorts orders by highest weight * volume
 */
void DeliveryService::sortOrderByHighestWeightAndVolume() {
    std::sort(orders.begin(), orders.end(), [](Order *a, Order *b) { return ((*a).getWeight() * (*a).getVolume()) > ((*b).getWeight() * (*b).getVolume()); });
}

/**
 * @brief Sorts orders by highest reward
 */
void DeliveryService::sortOrderByReward(){
    std::sort(orders.begin(), orders.end(), [](Order *a, Order *b) { return ((*a).getReward()/((*a).getWeight() * (*a).getVolume())) > ((*b).getReward()/((*b).getWeight() * (*b).getVolume())); });
}

/**
 * @brief Sorts orders by highest pure reward
 */
void DeliveryService::sortOrderByPureReward(){
    std::sort(orders.begin(), orders.end(), [](Order *a, Order *b) { return (*a).getReward() > (*b).getReward(); });
}

/**
 * @brief Sorts vans by highest max weight
 */
void DeliveryService::sortVansByHighestWeight() {
    std::sort(vans.begin(), vans.end(), [](Van *a, Van *b) { return (*a).getMaxWeight() > (*b).getMaxWeight(); });
}

/**
 * @brief Sorts vans by highest max volume
 */
void DeliveryService::sortVansByHighestVolume() {
    std::sort(vans.begin(), vans.end(), [](Van *a, Van *b) { return (*a).getVolMax() > (*b).getVolMax(); });
}

/**
 * @brief Sorts vans by highest max weight / max volume
 */
void DeliveryService::sortVansByHighestDensity() {
    std::sort(vans.begin(), vans.end(), [](Van *a, Van *b) { return ((*a).getMaxWeight() / (*a).getVolMax()) > ((*b).getMaxWeight() / (*b).getVolMax()); });
}

/**
 * @brief Sorts vans by highest max weight + max volume
 */
void DeliveryService::sortVansByHighestWeightVolume() {
    std::sort(vans.begin(), vans.end(), [](Van *a, Van *b) { return ((*a).getMaxWeight() + (*a).getVolMax()) > ((*b).getMaxWeight() + (*b).getVolMax()); });
}

/**
 * @brief Sorts vans by highest max weight * max volume
 */
void DeliveryService::sortVansByHighestWeightAndVolume() {
    std::sort(vans.begin(), vans.end(), [](Van *a, Van *b) { return ((*a).getMaxWeight() * (*a).getVolMax()) > ((*b).getMaxWeight() * (*b).getVolMax()); });
}

/**
 * @brief Sorts vans by highest profit with weight and volume
 */
void DeliveryService::sortVansByProfit() {
    std::sort(vans.begin(),vans.end(), [](Van *a, Van *b){return((*a).getMaxWeight() * (*a).getVolMax()/(*a).getCost() > (*b).getMaxWeight() * (*b).getVolMax()/(*b).getCost()); });
}

/**
 * @brief Sorts vans by highest profit purely
 */
void DeliveryService::sortVansByPureProfit() {
    std::sort(vans.begin(),vans.end(), [](Van *a, Van *b){return (*a).getCost() > (*b).getCost(); });
}

/**
 * @brief Attempts to optimize normal deliveries by bin-packing pre-sorted orders into pre-sorted vans
 * @param ordersDelivered
 * @return number of used vans
 */
unsigned long long DeliveryService::optimizeNormalDeliveries(int &ordersDelivered) {

    //22
    //sortOrderByHighestWeightVolume();
    //sortVansByHighestWeightVolume();

    //21
    sortOrderByHighestWeightAndVolume();
    sortVansByHighestWeightAndVolume();

    std::vector<Order *> used_orders;
    std::vector<Van *> used_vans;
    used_vans.push_back(vans[0]);
    int next_van = 1;
    for(int i = 0; i < getNumOrders(); i++){
        bool added = false;
        for(auto van : used_vans){
            if(van->canAddOrder(orders[i])){
                van->addOrder(orders[i]);
                used_orders.push_back(orders[i]);
                added = true;
                break;
            }
        }
        if(!added){
            if(used_vans.size() == vans.size()){
                break;
            }
            used_vans.push_back(vans[next_van]);
            next_van++;
            i--;
        }
    }
    ordersDelivered = used_orders.size();
    return used_vans.size();
}

/**
 * @brief Calculates profit
 * @param item
 * @param weight
 * @param volume
 * @param W_max maximum weight capacity of van
 * @param Vol_max maximum volume capacity of van
 * @param n
 * @return
 */
int DeliveryService::knapsack(int item, int weight, int volume,int W_max,int Vol_max, int n) {
    // See if we have calculated this item before
    if (dp[item][weight] == -1) {
        // Set initial value to -2 (invalid result)
        int max = -2;
        // Iterate though all items past current item
        for (int i = item; i < n; i++) {
            // Make sure we don't go over max weight
            if (volume + orders.at(i)->getVolume() <= Vol_max && weight + orders.at(i)->getWeight() <= W_max) {
                // Get the result of taking ith item
                int res = knapsack(i + 1, weight + orders.at(i)->getWeight(), volume + orders.at(i)->getVolume(),W_max, Vol_max, n );
                // Make sure result is valid (Total volume is greater than
                // Vol_min)
                if (res != -2) {
                    // If the result is valid take the max
                    max = std::max(res + orders.at(i)->getReward(), max);
                }
            }
        }

        if (max == -2 && volume <= Vol_max)// No other items taken and over
            // Vol_min
            dp[item][weight] = 0;
        else // Eveything else
            dp[item][weight]= max;
    }
    // Return the value
    return dp[item][weight];
}

/**
 * @brief Recursive dynamic programming approach to solve the need to maximize profit
 * @return
 */
int DeliveryService::optimizeProfit() {
    sortOrderByReward();
    sortVansByProfit();
    int profit = 0, p;
    int ordersReceived = orders.size();
    for(int i = 0; i < vans.size(); i++){
        prepareKnapsack(i);
        int d = knapsack(0,0,0,vans.at(i)->getMaxWeight(),vans.at(i)->getVolMax(),orders.size());
        std::vector<int> ordersForDelivery = getItens(d);
        p = checkItems(ordersForDelivery,i);

        if(p>0){
            addOrdersToVan(i, ordersForDelivery);
        }


    }
    for(auto van : vans){
        if(!van->getOrders().empty()){
            for(auto order : van->getOrders()){
                profit += order->getReward();
            }
            profit -= van->getCost();
        }
    }
    int ordersDelivered = ordersReceived - orders.size();
    std::cout << "Total profit was: " << profit <<  std::endl;
    std::cout << ordersReceived << " orders were received and a total of " << ordersDelivered << " were delivered." << std::endl;
    std::cout << "Efficiency: " << std::fixed << std::setprecision(3) << double(ordersDelivered)/double(ordersReceived)  << std::endl;
    return 1;
}

/**
 * @brief A more linear approach to solve the need to maximize profit
 * @return profit
 */
int DeliveryService::optimizeProfit2() {
    sortVansByProfit();
    sortOrderByReward();
    int profit = 0;
    int numberVansUsed = 0;
    int ordersReceived = orders.size();
    for(int i = 0 ; i < vans.size() ; i++){
        int profitPositive = addOrders(i);
        if(profitPositive>0) {profit += profitPositive;numberVansUsed++;}
    }
    int ordersDelivered = ordersReceived - orders.size();
    std::cout << "Number of vans used: " << numberVansUsed <<  std::endl;
    std::cout << "Total profit was: " << profit <<  std::endl;
    std::cout << ordersReceived << " orders were received and a total of " << ordersDelivered << " were delivered." << std::endl;
    std::cout << "Efficiency: " << std::fixed << std::setprecision(3) << double(ordersDelivered)/double(ordersReceived)  << std::endl;
    return profit;
}

/**
 * @brief Prepares the data that will be used in the algorithms
 * @param l
 */
void DeliveryService::prepareKnapsack(int l) {
//best van volMax 391 maxW 395
    for (int i = 0;i < orders.size(); i++) {
        for (int j = 0; j < vans.at(l)->getMaxWeight(); j++) {

                dp[i][j] = -1;

        }
    }
}

/**
 * @brief Returns the orders that have a certain profit
 * @param profit
 * @return items
 */
std::vector<int> DeliveryService::getItens(int profit) {
    int i = 1;
    std::vector<int> itens;
    int peso = 0;
    int volume = 0;
    while(profit!=0&&i<=orders.size()){
        if(dp[i][peso+orders.at(i-1)->getWeight()]+orders.at(i-1)->getReward() == profit) {
            itens.push_back(i);
            peso += orders.at(i-1)->getWeight();
            volume += orders.at(i-1)->getVolume();
            profit -= orders.at(i-1)->getReward();
        }
        i++;
    }
    return itens;
}

/**
 * @brief Adds orders to a certain van
 * @param vanInt
 * @param ordersForDelivery
 */
void DeliveryService::addOrdersToVan(int vanInt, std::vector<int> ordersForDelivery){
    std::reverse(ordersForDelivery.begin(), ordersForDelivery.end());
    for(auto orderId : ordersForDelivery){
        if(vans.at(vanInt)->canAddOrder(orders.at(orderId-1))){
            vans.at(vanInt)->addOrder(orders.at(orderId-1));
            orders.erase(orders.begin()+orderId-1);
        }
    }
    std::reverse(ordersForDelivery.begin(), ordersForDelivery.end());



}

/**
 * @brief Checks if the applied algorithm worked
 * @param ordersForDelivery
 * @param vanId
 * @return profit
 */
int DeliveryService::checkItems(std::vector<int> &ordersForDelivery, int vanId) {
    int peso = 0; int volume = 0, profit = 0;
    for(int i = 0; i< ordersForDelivery.size(); i++){
        if(peso + orders.at(ordersForDelivery[i]-1)->getWeight() <= this->vans.at(vanId)->getMaxWeight() && volume + orders.at(ordersForDelivery[i]-1)->getVolume() <= this->vans.at(vanId)->getVolMax() ){
            peso += orders.at(ordersForDelivery[i]-1)->getWeight();
            volume += orders.at(ordersForDelivery[i]-1)->getVolume();
            profit += orders.at(ordersForDelivery[i]-1)->getReward();
        }
        else{
            ordersForDelivery.erase(ordersForDelivery.begin()+i, ordersForDelivery.end());
            break;
        }
    }
    if(!ordersForDelivery.empty()){profit -= vans.at(vanId)->getCost();}

    return profit;
}

/**
 * @brief Another way to add orders to a certain van
 * @param vanId
 * @return
 */
int DeliveryService::addOrders(int vanId){
    int peso = 0;
    int volume = 0;
    int profit = 0;
    int i = 0;
    for(; i< orders.size(); i++){
        if(peso + orders.at(i)->getWeight() <= this->vans.at(vanId)->getMaxWeight() && volume + orders.at(orders.at(i)->getVolume() <= this->vans.at(vanId)->getVolMax())){
            peso += orders.at(i)->getWeight();
            volume += orders.at(i)->getVolume();
            profit += orders.at(i)->getReward();
        }
        else{
            break;
        }
    }
    if(profit > vans.at(vanId)->getCost()){
        for(int d = 0; d < i; d++){
            vans.at(vanId)->addOrder(orders.at(d));
        }
        orders.erase(orders.begin(),orders.begin()+i);
        return profit - vans.at(vanId)->getCost();
    }
    return 0;
}

/**
 * A valiant effort at a recursive DP approach, sadly the program crashes out of nowhere, probably because of the sheer size of the DP vector.
 * For some reason the code runs if we isolate the conditions into variables first
 * Also, can't even run the debugger as it instantly crashes upon loading the DP vector
 * If someone, in the future, tries to fix this function, please increment the following counter
 * hours wasted here: 6
 * @return
 */
int DeliveryService::optimizeProfit3() {
    sortVansByPureProfit();

    //orders used  //weight                 //volume
    std::vector<std::vector<std::vector<int>>> DP(orders.size()+1, std::vector<std::vector<int>>(vans[0]->getMaxWeight()+1, std::vector<int>(vans[0]->getVolMax()+1, 0)));
    for(int o = 1; o < orders.size(); o++){
        for (int w = 0; w <= vans[0]->getMaxWeight(); w++) {
            for (int v = 0; v <= vans[0]->getVolMax(); v++) {
                if(orders[o]->getWeight() > vans[0]->getMaxWeight() || orders[o]->getVolume() > vans[0]->getVolMax() || w < orders[o]->getWeight() || v < orders[o]->getVolume())
                    DP[o][w][v] = DP[o-1][w][v];
                else {
                    /*
                    int x1 = w - orders[o]->getWeight();
                    int x2= v - orders[o]->getVolume();
                    if ( x1 < 0 || x2 < 0) DP[o][w][v] = DP[o - 1][w][v];
                    else{*/
                        int i1 = DP[o - 1][w][v];
                        int i2 = DP[o - 1][w - orders[o]->getWeight()][v - orders[o]->getVolume()] + orders[o]->getReward();
                        DP[o][w][v] = std::max(i1, i2);
                    //}
                }
            }
        }
    }
    int max_profit = DP[DP.size()-1][DP[0].size()-1][DP[0][0].size()-1]; //last element
    std::cout<<max_profit;
    std::vector<int> used_orders_binary(orders.size(), 0);
    /*
    for(int o = 1; o < orders.size(); o++){
        for (int w = 0; w <= vans[0]->getMaxWeight(); w++) {
            for (int v = 0; v <= vans[0]->getVolMax(); v++) {
                printf("%d ",DP[o][w][v]);
                if(v%3 == 0)
                {
                    printf("\n");
                }
            }
        }
        printf("\n");
    }*/
    return 0;
}

