#include <iostream>
#include <string>
#include <random>
using namespace std;

class people{
protected:
    string name;
    int health;
    int velocity;
public:
    people(string name, int health, int velocity){
        this -> name = name;
        this -> health = health;
        this -> velocity = velocity;
    }
    ~people(){
        delete[] & name;
        delete[] & health;
        delete[] & velocity;
    }
    void accept_interaction(int interaction_measure){
        this -> health -= interaction_measure;
        if (this -> health <= 0){
            this -> ~people();
        }
    }
    virtual void interaction(people *people) {}
};

class main_character : public people{
protected:
public:
    main_character(string name, int health, int velocity): people(name, health, velocity){}
};

class people_around : public people{
protected:
public:
};

class professors: public people_around{
protected:
public:
};

class fuckers: public professors{
protected:
    int level_of_fucking;
public:
    fuckers(string name, int health, int velocity, int level_of_fucking) : professors(name, health, velocity){
        this -> level_of_fucking = level_of_fucking;
    }  
    void interaction(people *people){
        people -> accept_interaction(this -> level_of_fucking);
    }
};

class normal_professors : public professors{
protected:
public:
    normal_professors(string name, int health, int velocity) : professors(name, health, velocity){} 
        void interaction(people *people){
            int randomInRange(int min, int max) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(min, max);
            return dist(gen);
        }
        mark = randomInRange(-5, 5);
        people -> accept_interaction(this -> mark);
    }
};

class groopmates : public people_around{
protected:
    int friend_points;
public:
    groopmates(string name, int health, int velocity, int friend_points) : people_around(name, health, velocity){
    this -> friend_points = friend_points;
    } 
    void interaction(people *people){
        people -> accept_interaction(this -> - friend_points);
    } 
};
