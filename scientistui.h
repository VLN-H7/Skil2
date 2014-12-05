#ifndef SCIENTISTUI_H
#define SCIENTISTUI_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "scientist.h"
#include "scientistservice.h"
#include "utils.h"

using namespace std;


class ScientistUI
{
public:
    ScientistUI();
    vector<Scientist> list();
    void add();
    vector<Scientist> search();
    void header();
    void remove();
    void edit();
private:
    ScientistService scientistService;

    string readString(string msg);
    void readFirstName(Scientist &s);
    void readLastName(Scientist &s);
    void readBirthDate(Scientist &s);
    void readDeathDate(Scientist &s);
    void readNationality(Scientist &s);
    void readGender(Scientist &s);
};

#endif // SCIENTISTUI_H
