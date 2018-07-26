#include <iostream>
#include "Askaryan.h"
#include "Askaryan_ARVZ.h"
#include "Askaryan_RB.h"
#include "Askaryan_ZHS.h"
using namespace std;

int main()
{
Askaryan *a;
Askaryan_ZHS *zhs = new Askaryan_ZHS();
Askaryan_ARVZ *arvz = new Askaryan_ARVZ();
Askaryan_RB *rb = new Askaryan_RB();
rb->setAskE(1.0e9);
a = rb;
}

