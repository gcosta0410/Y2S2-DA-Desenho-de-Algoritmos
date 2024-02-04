#include "Menu.h"
#include "AuxiliaryFunctions.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <iomanip>
#include <fstream>


/**
 * @brief Main menu
 */
void Menu::mainMenu() {

    std::string option;

    // Ask for a valid input
    while (true) {

        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "|            Welcome to CTCP Transports           |" << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "1. Cenario 1" << std::endl;
        std::cout << "2. Cenario 2" << std::endl;
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
            load();
            cen1();
            break;

        case 2 :{
            EdmondsKarpGraph edmondsKarpGraph(loadEdmondKarp(FILENAME), FILENAME);
            cen2(edmondsKarpGraph);
            break;
        }
        case 0:
            exitMenu();
    }
}
/**
 * @brief Cenário 1
 */
void Menu::cen1() {
    std::string option;

    // Ask for a valid input
    while (true) {

        std::cout << "\n1. Maximizar a dimensao do grupo e indicar um qualquer encaminhamento." << std::endl;
        std::cout << "2. Maximizar a dimensao do grupo e minimizar o numero de transbordos apresentando alternativas nao comparaveis" << std::endl;
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
            cen1_1();
            break;
        case 2:
            cen1_2();
            break;
        case 0:
            exitMenu();
    }
}

/**
 * @brief Cenário 1.1
 */
void Menu::cen1_1() {
    list<int> path;
    list<int> path2;
    int start = 1;
    int end = n;
    int capacity = -1;
    capacity = ctcp->getMaxCapacityPath(start,end, &path);
    if(capacity < 0 || path.empty()){
        cout << endl;
        cout << "We couldn't find a path for you!" << endl;
        return;
    }
    cout << endl;
    cout << "Maximum number of passengers: " <<  capacity << endl;
    cout << "Transbordos: " << path.size()-1 << endl;

    cout << "PATH: ";
    for(auto e = path.begin() ; e != path.end() ; e++ ) {
        if(e == --path.end()){
            cout << *e;
        }
        else {
            cout << *e << " -> ";
        }
    }
    cout << endl << endl;
}

/**
 * @brief Cenário 1.2
 */
void Menu::cen1_2() {
    list<int> path;
    int start = 1;
    int end = n;
    ctcp->getMaxCapacityOrLeastChanges(start ,end, &path);
}

/**
  * @brief Cenário 2
  */
void Menu::cen2(EdmondsKarpGraph &edmondsKarpGraph) {
    std::string option;

    // Ask for a valid input
    while (true) {

        std::cout << "\n1. Determinar um encaminhamento para um grupo, dada a sua dimensao" << std::endl;
        std::cout << "2. Corrigir um encaminhamento, se necessario, para que a dimensao do grupo possa aumentar de um numero de unidades dado" << std::endl;
        std::cout << "3. Determinar a dimensao maxima do grupo e um encaminhamento." << std::endl;
        std::cout << "4. Partindo de um encaminhamento que constitui um grafo aciclico, determinar quando e que o grupo se reuniria novamente no destino, no minimo." << std::endl;
        std::cout << "5. Nas condicoes anteriores, admitindo que os elementos que saem de um mesmo local partem desse local a mesma hora (e o mais cedo possivel), indicar o tempo maximo de espera e os locais em que haveria elementos que esperam esse tempo." << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option);
        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }
        bool stop = parseInput(5,option);
        if (stop) break;
    }
    switch (std::stoi(option)) {
        case 1:
            cen21(edmondsKarpGraph);
            break;
        case 2:
            cen22(edmondsKarpGraph);
            break;
        case 3:
            cen23(edmondsKarpGraph);
            break;
        case 4:
            cen24(edmondsKarpGraph);
            break;
        case 5:
            cen25(edmondsKarpGraph);
            break;
        case 0:
            exitMenu();
    }

}
/**
 * @brief Loads input
 */
void Menu::load(const string& filename) {
    if(this->ctcp){
        free(ctcp);
        ctcp = nullptr;
    }
    setNAndT(this->n, this->t, filename);
    this->ctcp = new Ctcp(n,t);
    //ctcp->clear();
    ctcp->load(filename);
}

/**
 * @brief Closes program
 */
void Menu::exitMenu() {
    std::cout << "Come back any time soon!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Waits for 1 seconds before closing the window
    exit(EXIT_SUCCESS); // Closes the terminal window
}

/**
 * @brief Sets number of nodes n and number of edges t
 * @param nodes
 * @param lines
 * @param filename
 */
void Menu::setNAndT(int &nodes, int &lines, const string& filename) {
    std::string line, word;
    std::vector<std::string> row;
    std::fstream file (filename, std::ios::in);
    if(file.is_open()){
        getline(file, line);
        std::stringstream str(line);
        row.clear();
        while (getline(str, word, ' ')) {
            row.push_back(word);
        }
        n = stoi(row[0]); t = stoi(row[1]);
        file.close();

    }
    else
        std::cerr<<"Could not open the file\n";
}

/**
 * Loads a graph ready for edmond's karp algorithm from a given file
 * @param filename
 * @return
 */
int Menu::loadEdmondKarp(const string &filename) {
    std::string line, word;
    std::vector<std::string> row;
    std::fstream file (filename, std::ios::in);
    if(file.is_open()){
        getline(file, line);
        std::stringstream str(line);
        row.clear();
        while (getline(str, word, ' ')) {
            row.push_back(word);
        }
        n = stoi(row[0]);
        file.close();
        return n;
    }
    else
        std::cerr<<"Could not open the file\n";
    return -1;
}

/**
 * Cenário 2.1
 * @param edmondsKarpGraph
 */
void Menu::cen21(EdmondsKarpGraph &edmondsKarpGraph) {
    std::string option;
    while(true){
        std::cout << "Choose a group size: ";
        std::getline(std::cin, option);
        if(isAllDigits(option)){
            if(stoi(option) > 0)
                break;
        }
    }

    int grpSize = stoi(option);
    edmondsKarpGraph.edmondsKarpFixedFlow(grpSize);
    int maxFlow = edmondsKarpGraph.getMaxFlow();
    std::cout << "Group size: " << grpSize << endl;
    std::cout << "Max amount of people that path supports: " << maxFlow << endl;
    std::cout << "People that couldn't get transport: " << ((grpSize > maxFlow)? to_string(grpSize - maxFlow):"0") << endl;
    std::cout << std::endl;
    edmondsKarpGraph.printPath();
    std::cout << std::endl;
}

/**
 * Cenário 2.2
 * @param edmondsKarpGraph
 */
void Menu::cen22(EdmondsKarpGraph &edmondsKarpGraph) {
    std::string option;
    while(true){
        std::cout << "Choose a group size: ";
        std::getline(std::cin, option);
        if(isAllDigits(option)){
            if(stoi(option) > 0)
                break;
        }
    }

    int grpSize = stoi(option);
    edmondsKarpGraph.edmondsKarpFixedFlow(grpSize);
    int maxFlow = edmondsKarpGraph.getMaxFlow();
    std::cout << "Group size: " << grpSize << endl
    << " Max amount of people that path supports: " << maxFlow << endl
    << " People that couldn't get transport: " << ((grpSize > maxFlow)? to_string(grpSize - maxFlow):"0") << endl;
    std::cout << std::endl;
    edmondsKarpGraph.printPath();
    std::cout << std::endl;

    std::string option2;

    // Ask for a valid input
    while (true) {

        std::cout << "Deseja alterar o tamanho do grupo inicial? " << std::endl;
        std::cout << "1. Sim" << std::endl;
        std::cout << "2. Nao" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option from the above: ";

        std::getline(std::cin, option2);
        // Check for CTRL + Z or CTRL + D input to close the program
        if (std::cin.eof()) {
            exitMenu();
        }
        bool stop = parseInput(2,option2);
        if (stop) break;
    }
    switch (std::stoi(option2)) {

        case 1:{
            bool repeat = true;
            EdmondsKarpGraph edmondsKarpGraph2(loadEdmondKarp(FILENAME), FILENAME);
            std::string option3;
            while(true){
                std::cout << "Choose a new group size: ";
                std::getline(std::cin, option3);
                if(isAllDigits(option3)){
                    if(stoi(option3) > 0) {
                        if (stoi(option3) <= maxFlow) {
                            cout << "Path stays the same as it supports " << stoi(option3) << " people" << endl;
                            repeat = false;
                            break;
                        } else
                            break;
                    }
                }
            }
            if(repeat){
                grpSize = stoi(option3);
                edmondsKarpGraph2.edmondsKarpFixedFlow(grpSize);
                maxFlow = edmondsKarpGraph2.getMaxFlow();
                std::cout << "Group size: " << grpSize << "\nMax amount of people that path supports: " << maxFlow << "\nPeople that couldn't get transport: " << ((grpSize > maxFlow)? to_string(grpSize - maxFlow):"0");
                std::cout << std::endl;
                edmondsKarpGraph2.printPath();
                std::cout << std::endl;
            }
            break;
        }
        case 2 :
            break;
        case 0:
            exitMenu();
    }

}

/**
 * Cenário 2.3
 * @param edmondsKarpGraph
 */
void Menu::cen23(EdmondsKarpGraph &edmondsKarpGraph) {
    edmondsKarpGraph.edmondsKarp();
    std::cout << "Max flow: " << edmondsKarpGraph.getMaxFlow();
    std::cout << std::endl;
    edmondsKarpGraph.printPath();
    std::cout << std::endl;
}

/**
 * Cenário 2.4
 * @param edmondsKarpGraph
 */
void Menu::cen24(EdmondsKarpGraph &edmondsKarpGraph) {
    cout << "O grupo reunir-se-ia passado " << edmondsKarpGraph.criticalPath() << " unidades de tempo!" << endl;
}

/**
 * Cenário 2.5
 * @param edmondsKarpGraph
 */
void Menu::cen25(EdmondsKarpGraph &edmondsKarpGraph) {
    edmondsKarpGraph.latestFinish();
}

