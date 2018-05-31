#ifndef GRUPURIPERSOANE_H_INCLUDED
#define GRUPURIPERSOANE_H_INCLUDED
#include<iostream>
#include<vector>
using namespace std;
enum TipSalaConferinta
{
    individual,
    scena,
    Count_Tip_Sala_Conferinta
};

class Hotel;
class GrupPersoane;

class Persoana
{
    string nume;
    bool MicDejun;
    friend istream& operator>>(istream&,Persoana&);
    friend istream& operator>>(istream&,GrupPersoane&);
};

istream& operator>>(istream& in,Persoana& object)
{
    if(in==cin) cout<<"Introduceti nume:";
    in>>object.nume;
    if(in==cin) cout<<"Doriti mic dejun?(DA/NU) ";
    string raspuns;
    do
    {
        in>>raspuns;
        if(raspuns=="DA")
        {
            object.MicDejun=true;
            break;
        }
        else if(raspuns=="NU")
        {
            object.MicDejun=false;
            break;
        }
        else
        {
            if(in==cin) cout<<"Raspuns invalid. Raspundeti doar cu DA sau NU.\n";
            continue;
        }
    }
    while(1);
    return in;
}

class GrupPersoane
{
    friend class Hotel;
    vector<Persoana> Membrii;
    int NrPersMicDejun;
    friend istream& operator>>(istream&,GrupPersoane&);
};

istream& operator>>(istream& in,GrupPersoane& object)
{
    object.Membrii.clear();
    object.NrPersMicDejun=0;
    int nr_membrii;
    if(in==cin) cout<<"Introduceti numarul de membrii ai grupului:";
    in>>nr_membrii;
    if(in==cin) cout<<"Introduceti pe rand informatiile celor "<<nr_membrii<<" membrii:\n";
    object.Membrii.resize(nr_membrii);
    for(int i=0; i<nr_membrii; ++i)
    {
        in>>object.Membrii[i];
        object.NrPersMicDejun+=object.Membrii[i].MicDejun;
    }
    return in;
}

template<int x>
class Rezervare;

template<int x>
istream& operator>>(istream&, Rezervare<x>&);

template<int x>
class Rezervare
{
    friend class Hotel;
protected:
    static int count_ID;
    GrupPersoane Grup;
    int NrZile;
    bool SalaConf;
    bool Proiector;
    TipSalaConferinta Tip;
    int ZiInceput,ZiSfarsit;
    vector<int> Camere;
    int ID;
    Hotel* p_Hotel;
public:
    friend istream& operator>><>(istream&, Rezervare<x>&);
    void set_Hotel(Hotel* _Hotel) {p_Hotel=_Hotel;}
    int get_ID(){return ID;}
};

template<int x>
int Rezervare<x>::count_ID=0;

template<int x>
istream& operator>>(istream& in, Rezervare<x>& object)
{
    in>>object.Grup;
    //if(in==cin) cout<<"Pe cate zile doriti sa faceti rezervarea? ";
    //in>>object.NrZile;
    if(in==cin) cout<<"Doriti sa rezervati si o sala de conferinte?(DA/NU) ";
    string raspuns;
    do
    {
        in>>raspuns;
        if(raspuns=="DA")
        {
            object.SalaConf=true;
            if(in==cin) cout<<"Doriti ca sala sa fie dotata cu un proiector?(DA/NU) ";
            do
            {
                in>>raspuns;
                if(raspuns=="DA")
                {
                    object.Proiector=true;
                    break;
                }
                else if(raspuns=="NU")
                {
                    object.Proiector=false;
                    break;
                }
                else
                {
                    if(in==cin) cout<<"Raspuns invalid. Raspundeti doar cu DA sau NU.";
                    continue;
                }
            }
            while(1);
            if(in==cin) cout<<"Ce tip de sala doriti?(scena/individual) ";
            do
            {
                in>>raspuns;
                if(raspuns=="scena")
                {
                    object.Tip=scena;
                    break;
                }
                else if(raspuns=="individual")
                {
                    object.Tip=individual;
                    break;
                }
                else
                {
                    if(in==cin) cout<<"Raspuns invalid. Raspundeti doar cu scena sau individual. ";
                    continue;
                }
            }
            while(1);
            break;
        }
        else if(raspuns=="NU")
        {
            object.SalaConf=false;
            break;
        }
        else
        {
            if(in==cin) cout<<"Raspuns invalid. Raspundeti doar cu DA sau NU. ";
            continue;
        }
    }
    while(1);
    return in;
}

#endif // GRUPURIPERSOANE_H_INCLUDED
