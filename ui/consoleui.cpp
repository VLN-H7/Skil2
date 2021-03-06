#include "consoleui.h"

const vector<const char*> COMMANDS = {
    "help",
    "clear",
    "about",
    "add",
    "list",
    "search",
    "remove",
    "edit",
    "link",
    "unlink",
    "view",
    "exit",
    "quit"
};

ConsoleUI::ConsoleUI()
{
    // Separate the UI into parts that handle computer bits, and parts that handle scientist bits.
    // This class also interfaces the two, for example the link function
    scientistUI = ScientistUI();
    computerUI = ComputerUI();
}

void ConsoleUI::butiful() {
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

void ConsoleUI::start() {
    butiful();
    help();
    do{
        try{
            menu();
        } catch (runtime_error &e) {
            cout << "Command caused an error: " << e.what() << endl;
            cout << "Please either report this to your nearest monkey or try another command " << endl;
        }
    } while(1);
}

void ConsoleUI::menu() {
    string command;
    do {
        cout << "Please enter a command: ";
        getline(cin,command);
    } while(command.empty());

    // Split the input into command and argument, trim each segment, and then remove all empty strings.
    auto input = Utils::split(command, ' ');
    Utils::vtrim(input);

    command = input[0];
    vector<string> arguments(next(input.begin()), input.end());
    // Check if the command exists, this is done before handling them,
    // because if it doesn't exist, we might want to replace it with one that does.
    bool found = false;
    for(size_t i = 0; i < COMMANDS.size(); i++) {
        if(command == COMMANDS[i]) {
            found = true;
            break;
        }
    }
    if (!found) {
        for(size_t i = 0; i < COMMANDS.size(); i++) {
            if(Utils::levenshtein_distance<string>(command,COMMANDS[i]) < 3) {
                found = true;
                command = COMMANDS[i];
                break;
            }
        }
    }
    if (command == "help") {
        help();
    } else if (command == "quit" || command == "exit") {
        quit();
    } else if (command == "clear") {
        clear();
    } else if (command == "about") {
        about();
    } else if (command == "add") {
        add(arguments);
    } else if (command == "list") {
        list(arguments);
    } else if (command == "search") {
        search(arguments);
    } else if (command == "remove") {
        remove(arguments);
    } else if (command == "edit") {
        edit(arguments);
    } else if (command == "link") {
        link(arguments);
    } else if (command == "unlink") {
        unlink(arguments);
    } else if (command == "view") {
        view(arguments);
    } else {
        cout << "Unknown command \"" << command << "\"." << endl;
    }
    cout << endl;
}

void ConsoleUI::quit() {
    exit(1);
}

void ConsoleUI::clear() {
#ifdef Q_OS_WIN32
    system("cls");
#else
    system("clear");
#endif
    help();
}

void ConsoleUI::about() {
    cout << endl <<"     ABOUT" << endl
         << "\tName of program: An Awesome Computer Scientist Program ( AACSP for short )" << endl
         << "\tVersion: 1.2.0" << endl
         << "\tYear: 2014" << endl
         << "\tObjective: -To store and work with a SQlite based database" << endl
         << "\t            for computer scientists and computers." << endl
         << "\t           -To be able to connect a computer scientist" << endl
         << "\t            to a computer and vice versa." << endl
         << "\tCreated by: Group 7" << endl
         << "\tMembers of production: Ari Thorlacius Sigurdsson" << endl
         << "\t                       Egill Anton Hlodversson" << endl
         << "\t                       James Elias Sigurdarson" << endl
         << "\t                       Sara Arnadottir" << endl
         << "\t                       Unnar Freyr Erlendsson"<< endl << endl;
}

void ConsoleUI::help() {

    cout << "The available commands are: " << endl << endl
         << "    LIST"<< endl
         << "\t list scientists   - List all scientists" << endl
         << "\t list computers    - List all computers" << endl << endl
         << "    ADD"<< endl
         << "\t add scientist     - Add a scientist" << endl
         << "\t add computer      - Add a computer" << endl << endl
         << "    SEARCH"<< endl
         << "\t search scientists - Search for a scientist" << endl
         << "\t search computers  - Search for a computer" << endl << endl
         << "    REMOVE"<< endl
         << "\t remove scientist  - Remove a scientist" << endl
         << "\t remove computer   - Remove a computer" << endl << endl
         << "    EDIT"<< endl
         << "\t edit scientist    - Edit a scientist" << endl
         << "\t edit computer     - Edit a computer" << endl << endl
         << "    VIEW"<< endl
         << "\t view computer     - View a computer's connections" << endl
         << "\t view scientist    - View a scientist's connections" << endl << endl
         << "    LINK" << endl
         << "\t link              - Link a scientist and a computer" << endl
         << "\t unlink            - Unlink a scientist and a computer" << endl << endl
         << "    OTHER" << endl
         << "\t quit              - Quit the program" << endl
         << "\t clear             - Clear screen" << endl
         << "\t about             - About the program"<< endl
         << "\t help              - View help" << endl << endl;
}

void ConsoleUI::add(vector<string> &arguments) {
    if (arguments.size() == 0) {
        cout << endl <<"The available 'add' commands are: " << endl << endl <<
                       "\tadd computer  - Add a computer" << endl <<
                       "\tadd scientist - Add a scientist" << endl << endl;
        return;
    }
    if (arguments[0] == "scientist" || arguments[0] == "s")
        scientistUI.add();
    else if (arguments[0] == "computer" || arguments[0] == "c")
        computerUI.add();
}

void ConsoleUI::remove(vector<string> &arguments) {
    if (arguments.size() == 0) {
        cout << endl <<"The available 'remove' commands are: " << endl << endl <<
                "\tremove computer   - Remove a computer" << endl <<
                "\tremove scientist  - Remove a scientist" << endl << endl;
        return;
    }
    if (arguments[0] == "scientist" || arguments[0] == "s")
        scientistUI.remove();
    else if (arguments[0] == "computer" || arguments[0] == "c")
        computerUI.remove();
}

void ConsoleUI::edit(vector<string> &arguments) {
    if (arguments.size() == 0) {
        cout << endl <<"The available 'edit' commands are: " << endl << endl <<
                "\tedit computer  - Edit a computer" << endl <<
                "\tedit scientist - Edit a scientist" << endl << endl;
        return;
    }
    if (arguments[0] == "scientist" || arguments[0] == "s")
        scientistUI.edit();
    else if (arguments[0] == "computer" || arguments[0] == "c")
        computerUI.edit();
}

void ConsoleUI::list(vector<string> &arguments) {
    if (arguments.size() == 0) {
        cout << endl <<"The available 'list' commands are: " << endl << endl <<
                "\tlist computer  - List all computers" << endl <<
                "\tlist scientist - List all scientists" << endl << endl;
        return;
    }
    if (arguments[0] == "scientists" || arguments[0] == "s")
        scientistUI.list();
    else if (arguments[0] == "computers" || arguments[0] == "c")
        computerUI.list();
}

void ConsoleUI::search(vector<string> &arguments) {
    if (arguments.size() == 0) {
        cout << endl <<"The available 'search' commands are: " << endl << endl <<
                "\tsearch computer  - Search a computer" << endl <<
                "\tsearch scientist - Search a scientist" << endl << endl;
        return;
    }
    if (arguments[0] == "scientists" || arguments[0] == "s")
        scientistUI.search();
    else if (arguments[0] == "computers" || arguments[0] == "c")
        computerUI.search();
}

void ConsoleUI::link(vector<string> &arguments) {
    // Handle selecting a scientist first, then pass it to the computer UI for further processing
    cout << "Please select a scientist" << endl;
    Scientist sci;
    if(!scientistUI.select(sci))
        return;
    computerUI.link(sci);

}

void ConsoleUI::unlink(vector<string> &arguments) {
    // Handle selecting a scientist first, then pass it to the computer UI for further processing
    cout << "Please select a scientist" << endl;
    Scientist sci;
    if(!scientistUI.select(sci))
        return;
    computerUI.unlink(sci);

}

void ConsoleUI::view(vector<string> &arguments) {
    if (arguments.size() == 0) {
        cout << endl <<"The available 'view' commands are: " << endl << endl <<
                "\tview computer  - View a computer and its connections" << endl <<
                "\tview scientist - View a scientist and its connections" << endl << endl;
        return;
    }
    if(arguments[0] == "scientist" || arguments[0] == "s") {
        Scientist s;
        if(!scientistUI.select(s)) return;

        computerUI.listComputers(s);
    } else if(arguments[0] == "computer" || arguments[0] == "c") {
        Computer c;
        if(!computerUI.select(c)) return;
        scientistUI.listScientists(c);
    }
}


