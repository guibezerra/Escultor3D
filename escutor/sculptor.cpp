#include "sculptor.h"
#include<iostream>
#include<cmath>
#include<fstream>

using namespace std;

//chamada do construtor e criação do objeto
Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    nx = _nx;
    ny = _ny;
    nz = _nz;
// tratamento de execeções

// Criação da Matriz3d
    v = new Voxel **[nx];
    for(int i = 0; i < nx; i++)
    {
        v[i] = new Voxel *[ny];
        for(int j=0; j < ny; j++)
        {
            v[i][j] = new Voxel [nz];
        }
     }
// Inicialização da Matriz3d
    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            for(int k = 0; k < nz; k++)
            {
                v[i][j][k].isOn = false;
                v[i][j][k].r = 0;
                v[i][j][k].g = 0;
                v[i][j][k].b = 0;
                v[i][j][k].a = 0;
            }
        }
    }
}

//chamada do destrutor
Sculptor::~Sculptor()
{

    for(int i = 0; i < nx; i++)
    {
        for(int j=0; j < ny; j++)
        {
            delete [] v[i][j];
        }
    }
    for (int i = 0; i < nx; i++)
    {
        delete [] v[i];
    }
     delete [] v;
}
//Recebe cores e opacidade da figura
void Sculptor::setColor(float r, float g, float b, float alpha)
{
    if (r>1 || g>1 || b>1 || alpha>1)
    {
        cout<<"Um dos valores é maior que o permitido"<< endl;
    }
    else if(r<0 || g<0 || b<0 || alpha<0)
    {
        cout<<"Um dos valores é menor que o permitido"<< endl;
    }
    else
    {
        this->r = r;
        this->g = g;
        this->b = b;
        a = alpha;
    }
}

void Sculptor::putVoxel(int x, int y, int z)
{
         v[x][y][z].r = r;
         v[x][y][z].g = g;
         v[x][y][z].b = b;
         v[x][y][z].a = a;
         v[x][y][z].isOn = true;
}

void Sculptor::cutVoxel(int x, int y, int z)
{
        v[x][y][z].isOn = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{ 
    for(int i = x0; i < x1; i++)
    {
        for(int j = y0; j < y1; j++)
        {
            for(int k = z0; k < z1; k++)
            {
               putVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for(int i = x0; i < x1; i++)
    {
        for(int j = y0; j < y1; j++)
        {
            for(int k = z0; k < z1; k++)
            {
               cutVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    double distancia = 0;

/* Subtrai-se o raio da coordenada central para que o laço comece a percorrer desde os menores valores possiveis para x,y e z até os maiores possíveis. Pois
 * caso essa opreação de subtração não seja feita, ira ser considerada apenas metade da esfera.
 */
        for(int i = 0; i < nx; i++)
           {
               for(int j= 0; j < ny; j++)
               {
                   for(int k = 0; k < nz; k++)
                   {
                       distancia = sqrt(pow(i - xcenter,2) + pow(j - ycenter,2) + pow(k - zcenter,2));
                       if (distancia <= radius)
                       {
                            putVoxel(i,j,k);
                       }

                   }
               }
           }
        /*
        // IMPRESÃO DA MATRIZ
           for (int i = 0; i < nx; i++)
           {
               for (int j = 0; j < ny; j++)
               {
                   for (int k = 0; k < nz; k++)
                   {
                     cout << v[i][j][k].r << " ";
                    //cout << v[i][j][k].g << " ";
                     //cout << v[i][j][k].b << " ";
                    // cout << v[i][j][k].a << " ";
                    // cout << v[i][j][k].isOn << " ";
                   }
                   cout<<endl;
               }
               cout<<endl;
           }
           */
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    double distancia = 0;
    float cordX = 0, cordY = 0, cordZ = 0;

    cordX = xcenter + radius;
    cordY = ycenter + radius;
    cordZ = zcenter + radius;

    for(int i = xcenter - radius; i < cordX; i++)
       {
           for(int j= ycenter - radius; j < cordY; j++)
           {
               for(int k = zcenter - radius; k < cordZ; k++)
               {
                   distancia = sqrt(pow(i - xcenter,2) + pow(j - ycenter,2) + pow(k - zcenter,2));
                   if (distancia <= radius)
                   {
                        cutVoxel(i,j,k);
                   }

               }
           }
       }

}

/* Implementação da elpisoide:
 * intervalos das estruturas de repetição possuem o mesmo critério do método da esfera.
*/
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    double auxiliar = 0;

    for(int i = 0; i < nx; i++)
       {
           for(int j= 0; j < ny; j++)
           {
               for(int k = 0; k < nz; k++)
               {
                  auxiliar = ((float)pow((i-xcenter),2)/pow(rx,2)) + ((float)pow((j-ycenter),2)/pow(ry,2)) + ((float)pow((k-zcenter),2)/pow(rz,2));

                  if (auxiliar <= 1.0)
                   {
                        putVoxel(i,j,k);
                   }

               }
           }
       }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    double auxiliar = 0;

    for(int i = 0; i < nx; i++)
       {
           for(int j= 0; j < ny; j++)
           {
               for(int k = 0; k < nz; k++)
               {
                  auxiliar = ((float)pow((i-xcenter),2)/pow(rx,2)) + ((float)pow((j-ycenter),2)/pow(ry,2)) + ((float)pow((k-zcenter),2)/pow(rz,2));

                  if (auxiliar <= 1.0)
                   {
                        cutVoxel(i,j,k);
                   }

               }
           }
       }
}

void Sculptor::writeOFF(char *filename)
{   // 8 6 0
    int NVertices = 0, Nfaces = 0, NArestas = 0, ContVoxel = 0;
    ofstream fout;

    fout.open(filename);
    fout<< "OFF" <<endl;
 /*
  * As estruturas de repetição varrem a matriz em busca dos elementos que estão com a propri. isOn=true. Isso
  * indica a presença de um cubo, permitindo assim contabilizar o total de cubos que compõem a figura.
  */
    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            for(int k = 0; k < nz; k++)
            {
                if (v[i][j][k].isOn == true) {
                    ContVoxel++;
                }
            }
        }
    }
    NVertices = ContVoxel * 8; // Retorna a quantidade total de vertices presentes na figura.
    Nfaces = ContVoxel * 6; // Retorna a qtd. total de faces presentes na figura.
    fout<< NVertices<< " " << " " << Nfaces << " " << NArestas << endl;


    for(int k=0; k<nz; k++)
    {
             for(int j=0; j<ny; j++)
             {
                 for (int i=0;i<nx;i++)
                 {
                     if(v[i][j][k].isOn)
                     {
                             fout << -0.5+i << " " << 0.5+j << " " << -0.5+k << endl;
                             fout << -0.5+i << " " << -0.5+j << " " << -0.5+k << endl;
                             fout << 0.5+i << " " << -0.5+j << " " << -0.5+k << endl;
                             fout << 0.5+i << " " << 0.5+j << " " << -0.5+k << endl;
                             fout << -0.5+i << " " << 0.5+j << " " << 0.5+k << endl;
                             fout << -0.5+i << " "<< -0.5+j << " " << 0.5+k << endl;
                             fout << 0.5+i << " " << -0.5+j << " " << 0.5+k << endl;
                             fout << 0.5+i << " " << 0.5+j << " " << 0.5+k << endl;
                     }
                 }
             }

         }


     int nf = 0;
          for(int k=0;k<nz; k++){
               for(int j=0;j<ny;j++){
                   for (int i=0;i<nx;i++) {
                       if(v[i][j][k].isOn){
                           fout<<"4 "<<0+nf*8<<" "<<3+nf*8<<" "<<2+nf*8<<" "<<1+nf*8<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl
                               <<"4 "<<4+nf*8<<" "<<5+nf*8<<" "<<6+nf*8<<" "<<7+nf*8<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl
                               <<"4 "<<0+nf*8<<" "<<1+nf*8<<" "<<5+nf*8<<" "<<4+nf*8<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl
                               <<"4 "<<0+nf*8<<" "<<4+nf*8<<" "<<7+nf*8<<" "<<3+nf*8<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl
                               <<"4 "<<3+nf*8<<" "<<7+nf*8<<" "<<6+nf*8<<" "<<2+nf*8<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl
                               <<"4 "<<1+nf*8<<" "<<2+nf*8<<" "<<6+nf*8<<" "<<5+nf*8<<" "<<v[i][j][k].r<<" "<<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<endl;
                           nf++;
                       }


                   }
               }

           }
  fout.close();
}


