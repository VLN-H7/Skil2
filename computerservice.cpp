#include "computerservice.h"

ComputerService::ComputerService()
{
    computerRepository = ComputerRepository();
}

void ComputerService::add(Computer s) {
    computerRepository.add(s);
}

void ComputerService::remove(Computer s){
    computerRepository.remove(s);
}

void ComputerService::update(Computer& s, Computer& replace){
    computerRepository.update(s, replace);
}

vector<Computer> ComputerService::list(ComputerFields::Field field, Order order){
    return computerRepository.list(field,order);
}

vector<Computer> ComputerService::search(ComputerFields::Field field, int rows, string query){
    return computerRepository.search(field, rows, query);
}
