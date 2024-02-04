#ifndef DA_T1_G113_ORDER_H
#define DA_T1_G113_ORDER_H


class Order {
private:
    unsigned int volume, weight, time;
    int reward;
    enum type { Normal, Express };

public:
    Order(unsigned int volume, unsigned int weight, int reward, unsigned int time) : volume(volume), weight(weight), reward(reward), time(time){}
    unsigned int getVolume() const;
    unsigned int getWeight() const;
    int getReward() const;
    unsigned int getTime() const;

};


#endif //DA_T1_G113_ORDER_H
