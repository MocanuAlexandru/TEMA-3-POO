#include<bits/stdc++.h>
#include "Hotel.h"
using namespace std;

int main()
{
    vector<Rezervare<5> > v_rez5;
    vector<Rezervare<6> > v_rez6;
    vector<Rezervare<7> > v_rez7;
    Rezervare<5> rez5;
    Rezervare<6> rez6;
    Rezervare<7> rez7;
    int optiune,ID,i,NrZile;
    ifstream fin("hotel.in");
    ///ofstream fout("rezervare.out");
    fin>>Hotel::getInstance();
    cout<<Hotel::getInstance()<<'\n';
    while(1)
    {
        cout<<"Alegeti una dintre urmatoarele optiuni: \n";
        cout<<"(0) Exit\n";
        cout<<"(1) Introduceti detaliile unei rezervari\n";
        cout<<"(2) Anulati o rezervare deja existenta\n";
        cin>>optiune;
        if(optiune==0)
            break;
        switch(optiune)
        {
        case 1:
            cout<<"Pe cate zile doriti sa faceti rezervarea? ";
            cin>>NrZile;
            switch(NrZile)
            {
            case 5:
                cin>>rez5;
                rez5.set_Hotel(&Hotel::getInstance());
                Hotel::getInstance().Rezerva(rez5);
                v_rez5.push_back(rez5);
                break;
            case 6:
                cin>>rez6;
                rez6.set_Hotel(&Hotel::getInstance());
                Hotel::getInstance().Rezerva(rez6);
                v_rez6.push_back(rez6);
                break;
            case 7:
                cin>>rez7;
                rez7.set_Hotel(&Hotel::getInstance());
                Hotel::getInstance().Rezerva(rez7);
                v_rez7.push_back(rez7);
                break;
            default:
                cout<<"Nu puteti face o rezervarea pentru un numar de zile mai mic ca 5 sau mai mare ca 7.\n";
            }
            break;
        case 2:
            cout<<"Va rugam introduceti ID-ul rezervarii dumneavoastra: ";
            cin>>ID;
            for(i=0; i<v_rez5.size(); ++i)
                if(v_rez5[i].get_ID()==ID)
                    break;
            if(i==v_rez5.size())
            {
                goto anulare_6;
            }
            Hotel::getInstance().AnuleazaRezervare(v_rez5[i]);
            for(;i<v_rez5.size()-1;--i)
                v_rez5[i]=v_rez5[i+1];
            v_rez5.pop_back();
            cout<<"Rezervare anulata cu succes.\n";
            break;

            anulare_6:
            for(i=0; i<v_rez6.size(); ++i)
                if(v_rez6[i].get_ID()==ID)
                    break;
            if(i==v_rez6.size())
            {
                goto anulare_7;
            }
            Hotel::getInstance().AnuleazaRezervare(v_rez6[i]);
            for(;i<v_rez6.size()-1;--i)
                v_rez6[i]=v_rez6[i+1];
            v_rez6.pop_back();
            cout<<"Rezervare anulata cu succes.\n";
            break;

            anulare_7:
            for(i=0; i<v_rez7.size(); ++i)
                if(v_rez7[i].get_ID()==ID)
                    break;
            if(i==v_rez7.size())
            {
                cout<<"Rezervarea cu acest ID nu exista. Reincercati operatiunea cu un ID valid.\n";
                break;
            }
            Hotel::getInstance().AnuleazaRezervare(v_rez7[i]);
            for(;i<v_rez7.size()-1;--i)
                v_rez7[i]=v_rez7[i+1];
            v_rez7.pop_back();
            cout<<"Rezervare anulata cu succes.\n";
            break;
        default:
            cout<<"Optiune invalida.Alegeti o alta optiune.\n";
            continue;
        }
        system("pause");
        system("cls");
        cout<<Hotel::getInstance()<<'\n';
    }
    return 0;
}
