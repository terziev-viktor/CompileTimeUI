#include <iostream>
#include "Commands/Print.h"
#include "Commands/Calc.h"
#include "Commands/Say.h"
#include "UI.hpp"

int main(int argc, char ** argv)
{
    UI<Print, Calc, Say> ui;
    ui.CallByTrigger("Calc", nullptr, 0);

    char c[50];
    std::cout << "Enter the command:";
    std::cin >> c;

    ui.CallByTrigger(c, nullptr, 0);
    return 0;
}