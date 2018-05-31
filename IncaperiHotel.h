#ifndef INCAPERIHOTEL_H_INCLUDED
#define INCAPERIHOTEL_H_INCLUDED
#include "GrupuriPersoane.h"

class Incapere
{
protected:
    int LocuriTotale;
    friend istream& operator>>(istream& in,Incapere& object)
    {
        return object.citire(in);
    }
    friend ostream& operator<<(ostream& out,const Incapere& object)
    {
        return object.afisare(out);
    }
    virtual istream& citire(istream&)=0;
    virtual ostream& afisare(ostream&) const=0;
    virtual ~Incapere(){}
    get_locuri(){return LocuriTotale;}
//public:
    //Incapere(int x=0):LocuriTotale(x){};
    //Incapere(const Incapere& other)=default;
};

class CameraLocuit: public Incapere
{
    friend class Hotel;
protected:
    vector<bool> CameraOcupata;///pentru fiecare zi;
    istream& citire(istream&);
    ostream& afisare(ostream&) const;
};

istream& CameraLocuit::citire(istream& in)
{
    CameraOcupata.clear();
    return in>>LocuriTotale;
}

ostream& CameraLocuit::afisare(ostream& out) const
{
    return out<<"Capacitate de "<<LocuriTotale<<" locuri";
}

class Restaurant: public Incapere
{
    friend class Hotel;
protected:
    vector<int> LocuriOcupate;
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
};

istream& Restaurant::citire(istream& in)
{
    LocuriOcupate.clear();
    return in>>LocuriTotale;
}

ostream& Restaurant::afisare(ostream& out) const
{
    return out<<"Capacitate de "<<LocuriTotale<<" locuri";
}

class SalaConferinta: public Incapere
{
    friend class Hotel;
protected:
    vector<bool> SalaOcupata;
    bool Proiector;
    TipSalaConferinta Tip;
    istream& citire(istream&);
    ostream& afisare(ostream&) const;
};

istream& SalaConferinta::citire(istream& in)
{
    SalaOcupata.clear();
    in>>LocuriTotale;
    in>>Proiector;
    string s;
    in>>s;
    if(s=="scena")
        Tip=scena;
    else if(s=="individual")
        Tip=individual;
    else
    {
        try
        {
            throw s;
        }
        catch(string sir)
        {
            cout<<"Tipul de scena "<<s<<" este invalid\nVa rog corectati datele.\n";
        }
    }
    return in;
}

ostream& SalaConferinta::afisare(ostream& out) const
{
    out<<"Capacitate de "<<LocuriTotale<<" locuri,";
    if(Proiector) out<<"cu proiector,";
    out<<"de tip ";
    if(Tip==scena)
        out<<"scena";
    else if(Tip==individual)
        out<<"individual";
    return out;
}

#endif // INCAPERIHOTEL_H_INCLUDED
