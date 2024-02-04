#ifndef DA_T1_G113_MENU_H
#define DA_T1_G113_MENU_H

#include "DeliveryService.h"

class Menu {
private:
    DeliveryService deliveryService;
    void load();
    void clear();
public:
    void mainMenu();
    void cen1();
    void cen2();
    void cen3();
    void exitMenu();
};

#endif //DA_T1_G113_MENU_H
