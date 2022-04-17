#include "calculate.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Calculate calculator;
    calculator.show();

    return a.exec();
}
