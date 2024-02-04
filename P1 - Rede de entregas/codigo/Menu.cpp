#include "Menu.h"
#include "AuxiliaryFunctions.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <iomanip>

/**
 * @brief Main menu
 */
void Menu::mainMenu() {
    this->deliveryService = DeliveryService();

    std::string option;

    // Ask for a valid input
    while (true) {

        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "|         Welcome to Send Packets Courier        |" << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "1. Cenario 1" << std::endl;
        std::cout << "2. Cenario 2" << std::endl;
        std::cout << "3. Cenario 3" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);
        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }
        bool stop = parseInput(3,option);
        if (stop) break;
    }
    switch (std::stoi(option)) {

        case 1:
            load();
            cen1();
            break;

        case 2:
            load();
            cen2();
            break;

        case 3:
            load();
            cen3();
            break;

        case 0:
            exitMenu();
    }
}

/**
 * @brief Cenário 1
 */
void Menu::cen1() {
    unsigned long long ordersReceived = deliveryService.getNumOrders();
    int ordersDelivered;
    unsigned long long nr_vans = deliveryService.optimizeNormalDeliveries(ordersDelivered);
    std::cout << "Number of used vans: " << nr_vans << std::endl;
    std::cout << ordersReceived << " orders were received and a total of " << ordersDelivered << " were delivered." << std::endl;
    std::cout << "Efficiency: " << std::fixed << std::setprecision(3) << double(ordersDelivered)/double(ordersReceived) << std::endl;
}

/**
 * @brief Cenário 2
 */
void Menu::cen2() {
    std::string option;
    while (true) {


        std::cout << "1. Method (Using Dynamic Programming)" << std::endl;
        std::cout << "2. Method (Recommended)" << std::endl;
        //std::cout << "3. Method (Experimental)" << std::endl; -We dont talk about this one
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);
        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }
        bool stop = parseInput(2,option);
        if (stop) break;
    }
    switch (std::stoi(option)) {

        case 1:
            deliveryService.optimizeProfit();
            break;
        case 2:
            deliveryService.optimizeProfit2();
            break;
        //case 3:
            //deliveryService.optimizeProfit3(); - pretend this doesn't exist
            //break;
        case 0:
            exitMenu();
    }

}

/**
 * @brief Cenário 3
 */
void Menu::cen3() {

    float avgtime;
    unsigned long long ordersLeft = deliveryService.getNumOrders(), ordersDelivered, ordersPostponed;
    unsigned long long ordersStart = ordersLeft;
    //ordersLeft > 0 - Passar orders para o dia seguinte?
    for(int i = 1; i == 1; i++){
        avgtime  = deliveryService.optimizeExpressDeliveries();
        std::cout << "Day " << i << std::endl;
        std::cout << "-Orders to be delivered at start of day: " << ordersLeft << std::endl;

        ordersPostponed = deliveryService.getNumOrders();
        ordersDelivered = ordersLeft - ordersPostponed;

        std::cout << "-Orders delivered: " << ordersDelivered << std::endl;
        std::cout << "-Orders postponed: " << ordersPostponed << std::endl;
        std::cout << "-Average completion time: " << avgtime << std::endl;
        ordersLeft = ordersPostponed;
        std::cout << "Efficiency: " << std::fixed << std::setprecision(3) << double(ordersDelivered)/double(ordersStart) << std::endl;
    }
}

/**
 * @brief Loads input
 */
void Menu::load() {
    clear();
    deliveryService.load("input/encomendas.txt", "input/carrinhas.txt");
}

/**
 * @brief Clears vectors for reloading
 */
void Menu::clear(){
    deliveryService.clear();
}

/**
 * @brief Closes program
 */
void Menu::exitMenu() {
    std::cout << "Come back any time soon!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Waits for 1 seconds before closing the window
    exit(EXIT_SUCCESS); // Closes the terminal window
}
