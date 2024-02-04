#ifndef DA_T1_G113_MENU_H
#define DA_T1_G113_MENU_H

#include "Ctcp.h"
#include "EdmondsKarpGraph.h"

#define FILENAME "input/in01_b.txt"

class Menu {
private:
    Ctcp* ctcp;
    int n,t;
    void load(const string &filename = FILENAME);
    void setNAndT(int &nodes, int &lines, const string& filename);
    int loadEdmondKarp(const string &filename);
public:
    void mainMenu();
    void cen1();
    void cen1_1();
    void cen1_2();
    void cen2(EdmondsKarpGraph &edmondsKarpGraph);
    void cen21(EdmondsKarpGraph &edmondsKarpGraph);
    void cen22(EdmondsKarpGraph &edmondsKarpGraph);
    void cen23(EdmondsKarpGraph &edmondsKarpGraph);
    void cen24(EdmondsKarpGraph &edmondsKarpGraph);
    void cen25(EdmondsKarpGraph &edmondsKarpGraph);
    static void exitMenu();

};

#endif //DA_T1_G113_MENU_H
