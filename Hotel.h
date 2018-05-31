#ifndef HOTEL_H_INCLUDED
#define HOTEL_H_INCLUDED
#include "IncaperiHotel.h"
#include "GrupuriPersoane.h"
using namespace std;

class Hotel
{
protected:
    string nume;
    vector<CameraLocuit> m_Camere;
    Restaurant m_Restaurant;
    vector<SalaConferinta> m_SaliConferinta;

    Hotel()=default;
    Hotel(const Hotel&)=delete;

    int VerificaDisponibilitateCamere(int,int,int,vector<int>&);
    bool VerificaExistentaSalaConf(bool,TipSalaConferinta,int);
    int CapacitateCamere(const vector<int>&,int);
    int VerificaDisponibilitateRestaurant(int,int,int);
    int VerificaDisponibilitateSalaConf(int,int,bool,TipSalaConferinta,int);
    template<int x>
    void Ocupa(const Rezervare<x>&);
public:
    friend istream& operator>>(istream& in, Hotel& object);
    friend ostream& operator<<(ostream& out, Hotel& object);
    template<int x>
    void Rezerva(Rezervare<x>&);
    unsigned int CapacitateTotalaCamere();
    template<int x>
    void AnuleazaRezervare(const Rezervare<x>&);
    static Hotel& getInstance();
};

Hotel& Hotel::getInstance()
{
    static Hotel object;
    return object;
}
template<int x>
void Hotel::AnuleazaRezervare(const Rezervare<x>& rez)
{
    for(int i=rez.ZiInceput; i<rez.ZiSfarsit; ++i)
    {
        for(int j=0; j<rez.Camere.size(); ++j)
            m_Camere[rez.Camere[j]].CameraOcupata[i]=false;
        m_Restaurant.LocuriOcupate[i]-=rez.Grup.NrPersMicDejun;
        for(int j=0; j<m_SaliConferinta.size(); ++j)
            if(m_SaliConferinta[j].SalaOcupata[i]==true && m_SaliConferinta[j].Proiector==rez.Proiector && m_SaliConferinta[j].Tip==rez.Tip)
            {
                m_SaliConferinta[j].SalaOcupata[i]=false;
                break;
            }
    }
}
template<int x>
void Hotel::Ocupa(const Rezervare<x>& rez)
{
    for(int i=rez.ZiInceput; i<rez.ZiSfarsit; ++i)
    {
        for(int j=0; j<rez.Camere.size(); ++j)
            m_Camere[rez.Camere[j]].CameraOcupata[i]=true;
        m_Restaurant.LocuriOcupate[i]+=rez.Grup.NrPersMicDejun;
        for(int j=0; j<m_SaliConferinta.size(); ++j)
            if(m_SaliConferinta[j].SalaOcupata[i]==false && m_SaliConferinta[j].Proiector==rez.Proiector && m_SaliConferinta[j].Tip==rez.Tip && m_SaliConferinta[j].LocuriTotale<=rez.Grup.Membrii.size())
            {
                m_SaliConferinta[j].SalaOcupata[i]=true;
                break;
            }
    }
}

int Hotel::VerificaDisponibilitateSalaConf(int zi_start,int nr_zile,bool proiector,TipSalaConferinta tip,int nr_pers)
{
    int curr=zi_start+nr_zile-1,dim_veche=m_SaliConferinta[0].SalaOcupata.size(),nr_zile_verificate=0;
    while(1)
    {
        if(curr>=m_SaliConferinta[0].SalaOcupata.size())
        {
            dim_veche=m_SaliConferinta[0].SalaOcupata.size();
            for(unsigned int i=0; i<m_SaliConferinta.size(); ++i)
                m_SaliConferinta[i].SalaOcupata.resize(curr+1,false);
        }
        int i;
        for(i=curr; i>curr-nr_zile+nr_zile_verificate; --i)
        {
            if(i>=dim_veche)
            {
                continue;
            }
            bool ok2=0;
            for(unsigned int j=0; j<m_SaliConferinta.size(); ++j)
                if(m_SaliConferinta[j].SalaOcupata[i]==true && m_SaliConferinta[j].Proiector==proiector && m_SaliConferinta[j].Tip==tip && m_SaliConferinta[j].LocuriTotale<=nr_pers)
                    ok2=1;
            if(!ok2)
                break;
        }
        if(i==curr-nr_zile+nr_zile_verificate)
            break;
        else
        {
            nr_zile_verificate=curr-i;
            curr=i+nr_zile;
        }
    }
    return curr-nr_zile+1;
}

int Hotel::VerificaDisponibilitateRestaurant(int zi_start,int nr_zile,int nr_pers)
{
    int curr=zi_start+nr_zile-1,dim_veche=m_Restaurant.LocuriOcupate.size(),nr_zile_verificate=0;
    while(1)
    {
        if(curr>=m_Restaurant.LocuriOcupate.size())
        {
            dim_veche=m_Restaurant.LocuriOcupate.size();
            m_Restaurant.LocuriOcupate.resize(curr+1,0);
        }
        int i;
        for(i=curr; i>curr-nr_zile+nr_zile_verificate; --i)
        {
            if(i>=dim_veche)
            {
                continue;
            }
            if(m_Restaurant.LocuriTotale-m_Restaurant.LocuriOcupate[i]<nr_pers)
                break;
        }
        if(i==curr-nr_zile+nr_zile_verificate)
            break;
        else
        {
            nr_zile_verificate=curr-i;
            curr=i+nr_zile;
        }
    }
    return curr-nr_zile+1;
}

int Hotel::CapacitateCamere(const vector<int>& v,int n)
{
    int s=0;
    for(unsigned int i=0; i<v.size(); ++i)
        if(v[i]==n)
            s+=m_Camere[i].LocuriTotale;
    return s;
}

int Hotel::VerificaDisponibilitateCamere(int zi_start,int nr_zile,int nr_pers,vector<int>& nr_camere)
{
    int curr=zi_start;
    vector<int> zile_libere_camera;
    zile_libere_camera.resize(m_Camere.size(),0);
    for(int i=zi_start; i<zi_start+nr_zile; ++i)
    {
        if(i>=m_Camere[0].CameraOcupata.size())
        {
            for(int j=0; j<m_Camere.size(); ++j)
                m_Camere[j].CameraOcupata.resize(i+1,false);
        }
        for(int j=0; j<m_Camere.size(); ++j)
            if(m_Camere[j].CameraOcupata[i]==false)
                zile_libere_camera[j]++;
    }
    while(CapacitateCamere(zile_libere_camera,nr_zile)<nr_pers)
    {
        if(curr+nr_zile>=m_Camere[0].CameraOcupata.size())
        {
            for(int j=0; j<m_Camere.size(); ++j)
                m_Camere[j].CameraOcupata.resize(curr+nr_zile+1,false);
        }
        for(int j=0; j<m_Camere.size(); ++j)
        {
            if(m_Camere[j].CameraOcupata[curr]==false)
                zile_libere_camera[j]--;
            if(m_Camere[j].CameraOcupata[curr+nr_zile]==false)
                zile_libere_camera[j]++;
        }
        curr++;
    }
    nr_camere.clear();
    int cap=0;
    for(int i=0; i<zile_libere_camera.size() && cap<nr_pers; ++i)
        if(zile_libere_camera[i]==nr_zile)
        {
            nr_camere.push_back(i);
            cap+=m_Camere[i].LocuriTotale;
        }
    return curr;
}

bool Hotel::VerificaExistentaSalaConf(bool proiector,TipSalaConferinta tip,int nr_pers)
{
    for(unsigned int i=0; i<m_SaliConferinta.size(); ++i)
        if(m_SaliConferinta[i].Proiector==proiector && m_SaliConferinta[i].Tip==tip && m_SaliConferinta[i].LocuriTotale>=nr_pers)
            return true;
    return false;
}

unsigned int Hotel::CapacitateTotalaCamere()
{
    int cap=0;
    for(unsigned int i=0; i<m_Camere.size(); ++i)
        cap+=m_Camere[i].get_locuri();
    return cap;
}
template<int x>
void Hotel::Rezerva(Rezervare<x>& rez)
{
    int curent1=-1,curent2=-1,curent3=-1,curent=0;
    if(rez.Grup.Membrii.size()>CapacitateTotalaCamere())
    {
        cout<<"Nu se poate efectua rezervarea.Grup de persoane prea mare.\n";
        return ;
    }
    if(rez.Grup.NrPersMicDejun>m_Restaurant.get_locuri())
    {
        cout<<"Nu se poate efectua rezervarea.Restaurantul nu poate servi toate persoanele cu mic dejun inclus.\n";
        return ;
    }
    if(rez.SalaConf==1 && VerificaExistentaSalaConf(rez.Proiector,rez.Tip,rez.Grup.Membrii.size())==0)
    {
        cout<<"Nu se poate efectua rezervarea.Hotelul nu dispune de o sala de conferinte care sa corespunda cerintelor dorite.\n";
        return ;
    }
    do
    {
        if(curent!=curent1)
            curent=curent1=VerificaDisponibilitateCamere(curent,rez.NrZile,rez.Grup.Membrii.size(),rez.Camere);
        if(curent!=curent2)
            curent=curent2=VerificaDisponibilitateRestaurant(curent,rez.NrZile,rez.Grup.NrPersMicDejun);
        //if(aux>curent) {curent=aux;goto step_1;}
        if(rez.SalaConf && curent!=curent3)
            curent=curent3=VerificaDisponibilitateSalaConf(curent,rez.NrZile,rez.Proiector,rez.Tip,rez.Grup.Membrii.size());
    }
    while(curent!=curent1 || curent!=curent2 ||  (rez.SalaConf && curent!=curent3));
    rez.ZiInceput=curent;
    rez.ZiSfarsit=curent+rez.NrZile;
    Ocupa(rez);
    cout<<"\nRezervare a fost efectuata cu succes.\n";
    cout<<"Camerele dumneavoastra sunt:";
    for(int i=0; i<rez.Camere.size(); ++i)
        cout<<rez.Camere[i]+1<<' ';
    cout<<"\nRezervarea a fost efectuata incepand cu data de "<<rez.ZiInceput+1<<" pana pe data de "<<rez.ZiSfarsit<<'\n';
    rez.ID=++rez.count_ID;
    cout<<"ID-ul rezervarii dumneavostra este:"<<rez.ID;
    cout<<"\nVa rugam sa pastrati acest ID in cazul unei anulari.\n";
}

istream& operator>>(istream& in, Hotel& object)
{
    int n;
    in>>object.nume;
    in>>n;
    object.m_Camere.resize(n);
    for(int i=0; i<n; ++i)
    {
        in>>object.m_Camere[i];
    }
    in>>object.m_Restaurant;
    in>>n;
    object.m_SaliConferinta.resize(n);
    for(int i=0; i<n; ++i)
    {
        in>>object.m_SaliConferinta[i];
    }
    return in;
}

ostream& operator<<(ostream& out, Hotel& object)
{
    out<<"Hotel "<< object.nume<<"\n\n";
    out<<"Numarul de camere este: "<<object.m_Camere.size()<<'\n';
    out<<"Detalii despre camere: \n";
    for(int i=0; i<object.m_Camere.size(); ++i)
    {
        out<<"Camera nr."<<i+1<<": "<< object.m_Camere[i]<<'\n';
    }
    out<<"\nDetalii despre restaurant: "<<object.m_Restaurant<<'\n';
    out<<"\nNumarul de sali de conferinta este: "<<object.m_SaliConferinta.size()<<'\n';
    out<<"Detalii despre salile de conferinta: \n";
    for(int i=0; i<object.m_SaliConferinta.size(); ++i)
    {
        out<<"Sala de conferinta nr."<<i+1<<": "<< object.m_SaliConferinta[i]<<'\n';
    }
    return out;
}


#endif // HOTEL_H_INCLUDED
