#include <iostream>
#include<sculptor.h>

using namespace std;

int main()
{

    // esfera
    Sculptor sol(20,20,20);
    sol.setColor(1,1,1,1);
    sol.putSphere(10,10,10,5);

    return 0;
}
