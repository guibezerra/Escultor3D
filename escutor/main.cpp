#include <iostream>
#include<sculptor.h>

using namespace std;

int main(void)
{
    // metodo box
    Sculptor trono (10,10,10);
    trono.setColor(0,0,1,1);
    trono.putBox(0,9,0,9,0,9);
    trono.cutBox(1,8,1,9,1,9);
    trono.writeOFF((char*)"trono.off");

    // metodo elipsoide
    Sculptor el(31,31,51);
    el.setColor(0,1,0,1);
    el.putEllipsoid(15,15,15,10,10,15);
    el.setColor(1,0,0,1);
    el.putEllipsoid(15,15,15,9,9,14);
    el.cutEllipsoid(15,15,15,8,8,13);
    el.cutBox(0,30,0,30,0,5);
    el.writeOFF((char*)"vaso.off");

    // metodo sphere
    Sculptor sol (31,31,31);
    sol.setColor(1,1,0,1);
    sol.putSphere(0,0,0,10);
    sol.putVoxel(30,30,30);
    sol.writeOFF((char*)"sol.off");
}
