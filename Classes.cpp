#include <iostream>
#include <string>
#include <random>
using namespace std;

class people_in_military_office {
protected:
    string name;
    int force;
    int velocity;
public:
    int health;
    people_in_military_office(string name, int force, int velocity, int health) {
        this -> name = name;
        this -> force = force;
        this -> velocity = velocity;
        this -> health = health;
    }
    ~people_in_military_office(){
        delete[] & name;
        delete[] & force;
        delete[] & velocity;
        delete[] & health;
    }
    void accept_hit(int force){
        this -> health -= force;
        if (this -> health <= 0){
            this -> ~people_in_military_office();
        }
    }
    void hit(people_in_military_office *people_in_military_office){
        people_in_military_office -> accept_hit(this -> force);
    }




};

class workers : public people_in_military_office {
protected:


public:
        workers(string name, int force, int velocity, int health): people_in_military_office(name, force, velocity, health) { }



};

class visitors : public people_in_military_office {
protected:

public:
    int money;
    visitors(string name, int force, int velocity, int health, int money): people_in_military_office(name, force, velocity, health) {
        this -> money = money;
    }
    ~visitors(){
        delete[] & money;
    }
    void accept_fine(int fine) {
        this -> money -= fine;
        if (this -> money <= 0){
            cout << "No money left. The military office won.";
            this -> ~visitors();
        }
    }


};

class comissar : public workers {
protected:

public:
    comissar(string name, int force, int velocity, int health): workers(name, force, velocity, health) { }

};

class civil_workers : public workers {
protected:
    int fine;
public:
    civil_workers(string name, int force, int velocity, int health, int fine): workers(name, force, velocity, health) {
    this -> fine = fine;
    }
    void big_fine(visitors *visitors){
        visitors -> accept_fine(this -> fine);
    }
};


class Phystech_fuckers : public workers{
protected:
    int level_of_fucking;
public:
    Phystech_fuckers(string name, int force, int velocity, int health, int level_of_fucking):  workers(name, force, velocity, health) {
    this -> level_of_fucking =  level_of_fucking;
    }

};

class Phystech_students : public visitors {
protected:
    int intelligence;
public:
    Phystech_students(string name, int force, int velocity, int health, int money, int intelligence): visitors(name, force, velocity, health, money) {
    this -> intelligence = intelligence;
    }
};

class other_creatures : public visitors {
protected:

public:
    other_creatures(string name, int force, int velocity, int health, int money): visitors(name, force, velocity, health, money) { }

};

int randint(int low, int high) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

int main() {
    Phystech_students* Sanya_Gogus = new Phystech_students("Sanya", 25, 10, 100, 20000, 100);
    civil_workers* comissar_assistant = new civil_workers("Ershov", 6, 9, 13, 10000);
    Phystech_fuckers* Umnov = new Phystech_fuckers("Umnov", 30, 50, 1000, 10000);
    for (int i = 0; i < 3; i++) {
        int random_number = randint(0, 1);
        if (random_number == 1) {
            cout << "Sanya hits Umnov!" << endl;
            Sanya_Gogus->hit(Umnov);
        } else {
            cout << "Umnov hits Sanya!" << endl;
            Umnov->hit(Sanya_Gogus);
        }
        if (Sanya_Gogus->health <= 0 || Umnov->health <= 0) {
            break;
        }
    }
    cout << "Applying fines to Sanya..." << endl;
    comissar_assistant->big_fine(Sanya_Gogus);
    cout << "Sanya's money after first fine: " << Sanya_Gogus->money << endl;

    comissar_assistant->big_fine(Sanya_Gogus);
    cout << "Sanya's money after second fine: " << Sanya_Gogus->money << endl;
    delete Sanya_Gogus;
    delete comissar_assistant;
    delete Umnov;

    return 0;
}
