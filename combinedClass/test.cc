#include <iostream>
#include "Askaryan.h"
#include "HansonConnolly.h"

int main()
{
	Askaryan *h = new HansonConnolly();
    delete h;
	return 0;
}
