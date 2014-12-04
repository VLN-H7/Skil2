#include "consoleui.h"


using namespace std;
ConsoleUI::ConsoleUI()
{
    scientistService = ScientistService();
}
void ConsoleUI::butiful(){
   cout << " ----------------------------------------------------- " << endl
        << "|      __    __     _                                 |" << endl
        << "|     / / /\\ \\ \\___| | ___ ___  _ __ ___   ___        |" << endl
        << "|     \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\       |" << endl
        << "|      \\  /\\  /  __/ | (_| (_) | | | | | |  __/       |" << endl
        << "|       \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|       |" << endl
        << "|  --- to an awesome computer scientist program! ---  |" << endl
        << "|                                                     |" << endl
        << " ----------------------------------------------------- " << endl;
}

void ConsoleUI::start(){
    butiful();
    help();
    do{
        menu();
    } while(1);
}

void ConsoleUI::menu() {
    string input;
    cout << "Please enter a command: ";
    getline(cin,input);
    if (input == "add"){
        add();
    } else if (input == "list") {
        list();
    } else if (input == "help") {
        help();
    } else if (input == "search"){
        search();
    } else if (input == "remove"){
        remove();
    } else if (input == "edit"){
        edit();
    } else if (input == "quit"){
        quit();
    } else if (input == "clear"){
        clear();
    }
    cout << endl;
}

void ConsoleUI::quit(){
    exit(1);
}

void ConsoleUI::clear(){
#ifdef Q_OS_WIN32
    system("cls");
#else
    system("clear");
#endif
    help();
}

void ConsoleUI::help(){

    cout << "The available commands are: " << endl <<
            "\t list - List all computer scientists" << endl <<
            "\t add - Add a computer scientist" << endl <<
            "\t search - Search for a computer scientist" << endl <<
            "\t remove - Remove a computer scientist" << endl <<
            "\t edit - Edit a computer scientist" << endl <<
            "\t quit - Quit the program" << endl <<
            "\t clear - Clear screen"<< endl;
}

void ConsoleUI::add(){

    Scientist s;
    string str;

    readFirstName(s);

    readLastName(s);

    readGender(s);

    readBirthDate(s);

    readDeathDate(s);

    readNationality(s);

    scientistService.add(s);
}

void ConsoleUI::remove(){
    char inp = 'L';
    stringstream ss;
    vector<Scientist> vec;
    int id = -1;
    bool cont = true;

    cout << "Would you either like to: "                <<endl<<
            "\tList of all the computer scientists (L)"   <<endl<<
            "\tSearch for a specific computer scientist? (S)"         <<endl<<
            "(L/S): ";
    if(readline(ss))
        ss >> inp;

    if(toupper(inp) == 'S') vec = search();
    else vec = list();
    if(vec.empty()){
        cout << "No results found." << endl;
        return;
    }

    do{
        cout << "Enter the ID of the scientist you would like to remove or Q to cancel: ";
        cont = readline(ss);

        if(cont && toupper(ss.str()[0]) == 'Q')
            return;
        ss >> id;
    } while(!cont || id <= 0 || static_cast<size_t>(id) > vec.size());
    id--;

    scientistService.remove(vec[id]);

    cout << "The scientist " << vec[id].firstName << " " << vec[id].lastName << " was successfully removed from the list. " << endl;
}


void ConsoleUI::edit(){
    int field = 1;
    char inp = 'L';
    stringstream ss;
    vector<Scientist> vec;
    int id = -1;
    bool cont = true;

    cout << "Would you either like to: "                <<endl<<
            "\tList of all the computer scientists (L)"   <<endl<<
            "\tSearch for a specific computer scientist? (S)"         <<endl<<
            "(L/S): ";
    if(readline(ss))
        ss >> inp;

    if(toupper(inp) == 'S') vec = search();
    else vec = list();
    if(vec.empty()){
        cout << "No results found." << endl;
        return;
    }

    do{
        cout << "Enter the ID of the scientist you would like to remove or Q to cancel: ";
        cont = readline(ss);

        if(cont && toupper(ss.str()[0]) == 'Q')
            return;
        ss >> id;
    } while(!cont || id <= 0 || static_cast<size_t>(id) > vec.size());
    id--;

    cout << "Available fields:" << endl
         << "\tFirst Name (1)" << endl
         << "\tLast Name (2)" << endl
         << "\tGender (3)" << endl
         << "\tBirthdate (4)" << endl
         << "\tDeathdate (5)" << endl
         << "\tNationality (6)" << endl;
    do {
        cout << "What would you like to change? (Default 1): ";
        if(readline(ss))
            ss >> field;
        else
            field = 1;
    } while(field <= 0 || field > 6);
    Scientist s = Scientist(vec[id]);
    switch(static_cast<ScientistSort::Field>(field)){

        case ScientistSort::FIRST_NAME:
            readFirstName(s);
            cout << "Successfully changed the first name to " << s.firstName << endl;
            break;

        case ScientistSort::LAST_NAME:
            readLastName(s);
            cout << "Successfully changed the last name to " << s.lastName << endl;
            break;

        case ScientistSort::GENDER:
            s.gender = s.gender ^ ( 'M' ^ 'F' );
            cout << "Successfully changed the gender to " << s.gender << endl;
            break;

        case ScientistSort::BIRTH_DATE:
            readBirthDate(s);
            cout << "Successfully changed the birthdate to " << s.birthdate << endl;
            break;

        case ScientistSort::DEATH_DATE:
            readDeathDate(s);
            cout << "Successfully changed the deathdate to " << s.deathdate << endl;
            break;

        case ScientistSort::NATIONALITY:
            readNationality(s);
            cout << "Successfully changed the nationality to " << s.nationality << endl;
            break;

        default:
            break;
    }

    scientistService.update(vec[id], s);
}


vector<Scientist> ConsoleUI::list(){
    int field = 1, order = 1;
    char sort = 'N';
    stringstream ss;
    cout << "The default sort order is by the first name, ascending" << endl;
    cout << "Would you like to change the sort order of the list? (Y/N) (Default N): ";
    if(readline(ss))
        ss >> sort;
    if(toupper(sort) == 'Y') {
        cout << "Available fields:" << endl
             << "\tFirst Name (1)" << endl
             << "\tLast Name (2)" << endl
             << "\tGender (3)" << endl
             << "\tBirthdate (4)" << endl
             << "\tDeathdate (5)" << endl
             << "\tNationality (6)" << endl;
        do {
            cout << "How would you like to sort the list? (Default 1): ";
            if(readline(ss))
                ss >> field;
            else
                field = 1;
        } while(field <= 0 || field > 6);

        cout << "Available orderings:" << endl
             << "\tAscending (1)" << endl
             << "\tDescending (2)" << endl;
        do {
            cout << "How would you like to order the list? (Default 1): ";
            if(readline(ss))
                ss >> order;
            else
                order = 1;
        } while(order <= 0 || order > 2);
    }
    header();

    vector<Scientist> vec = scientistService.list(static_cast<ScientistSort::Field>(field), static_cast<ScientistSort::Order>(order));

    for(size_t i = 0; i < vec.size(); i++){
        cout << left
             << setw(4)  << (i+1)
             << setw(12) << vec[i].firstName
             << setw(12) << vec[i].lastName
             << setw(8) << vec[i].gender
             << setw(12) << vec[i].birthdate
             << setw(12) << vec[i].deathdate
             << setw(12) << vec[i].nationality << endl;
    }
    return vec;
}

vector<Scientist> ConsoleUI::search(){
    stringstream ss;
    int field = 1, rows = 1;
    bool fuzzy = false;
    string query;
    cout << "Available fields:" << endl
         << "\tFirst Name (1)" << endl
         << "\tLast Name (2)" << endl
         << "\tGender (3)" << endl
         << "\tBirthdate (4)" << endl
         << "\tDeathdate (5)" << endl
         << "\tNationality (6)" << endl
         << "\tFirst Name (Fuzzy) (7)" << endl
         << "\tLast Name (Fuzzy) (8)" << endl
         << "\tBirthdate (Fuzzy) (9)" << endl
         << "\tDeathdate (Fuzzy) (10)" << endl
         << "\tNationality (Fuzzy) (11)" << endl;
    do{
        cout << "What would you like to search by? (Default 1): ";
        if(readline(ss))
            ss >> field;
        else
            field = 1;
    } while(field <= 0 || field > 12);

    if (field > 6) {
        if (field > 8) field++; // Shift before the modulo operation (because gender cannot be fuzzy)
        field = (field % 7) + 1; // Bound the fuzzy choices
        fuzzy = true;
    }
    cout << "What is the maximum number of entries you want? (Default 1): ";
    if(readline(ss))
        ss >> rows;
    vector<Scientist> vec;
    if(rows <= 0)
        return vec; // Why go through a search if the user doesnt want results?
    cout << "Enter your query: ";
    getline(cin, query);
    vec = scientistService.search(static_cast<ScientistSort::Field>(field), fuzzy, rows, query);
    header();
    for(size_t i = 0; i<vec.size(); i++){
        cout << left 
            << setw(4)  << (i+1) 
            << setw(12) << vec[i].firstName
            << setw(12) << vec[i].lastName
            << setw(8)  << vec[i].gender 
            << setw(12) << vec[i].birthdate
            << setw(12) << vec[i].deathdate
            << setw(12) << vec[i].nationality <<  endl;
    }
    return vec;
}

bool ConsoleUI::readline(stringstream &ss){
    // A function to read a line and return a stringstream to it, or return false otherwise.
    // This is useful for example to read
    string s;
    ss.str(string());
    ss.clear();
    getline(cin, s);
    if(s.empty()) return false;
    ss.str(s);
    return true;

}

void ConsoleUI::header(){
    cout << endl;
    cout << left 
         << setw(4)  << "No."
         << setw(12) << "First Name"
         << setw(12) << "Last Name"
         << setw(8)  << "Gender"
         << setw(12) << "Birthdate"
         << setw(12) << "Deathdate"
         << setw(12) << "Nationality" << endl;
    cout << "=======================================================================" << endl;
}

string ConsoleUI::readString(string msg){
    string s;
    do{
        cout << msg;
        getline(cin,s);
    }while(s.empty());
    return s;

}

void ConsoleUI::readFirstName(Scientist& s){
    s.firstName = readString("First Name: ");
}

void ConsoleUI::readLastName(Scientist& s){
    s.lastName = readString("Last Name: ");
}

void ConsoleUI::readGender(Scientist& s){
    do{
        cout << "Gender (M/F): ";
        cin >> s.gender;
        s.gender = toupper(s.gender);
        if(s.gender != 'M' && s.gender != 'F')
            cout << "Invalid gender, please enter either M or F." << endl;
    } while(s.gender != 'M' && s.gender != 'F');
    cin.ignore();
}

void ConsoleUI::readBirthDate(Scientist& s){
    string str;
    do{
        cout << "Date of birth(DD.MM.YYYY): ";
        getline(cin, str);
        s.birthdate = Date::fromString(str);
        if (!s.birthdate.isValid())
            cout << "Invalid Date." << endl;
        else if (s.birthdate>Date::now())
            cout << "Date of birth cannot be in the future." << endl;
    } while(!s.birthdate.isValid() || s.birthdate>Date::now());
}

void ConsoleUI::readDeathDate(Scientist& s){
    string str;
    do{
        cout << "Date of death(DD.MM.YYYY)(Leave empty for no date): ";
        getline(cin, str);
        if(str.empty()){
            s.deathdate.setDate(0,1,1);
            break;
        }
        s.deathdate = Date::fromString(str);
        if (!s.deathdate.isValid())
         cout << "Invalid Date." << endl;
        else if (s.deathdate<s.birthdate)
            cout << "Date of death needs to be after date of birth." << endl;
    } while(!s.deathdate.isValid()||s.deathdate<s.birthdate);
}

void ConsoleUI::readNationality(Scientist& s){
    s.nationality = readString("Nationality: ");
}

