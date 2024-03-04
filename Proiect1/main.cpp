#include <iostream>
#include <string>
#include <cstring>
#include <windows.h>
#include <vector>
#include <thread>
#include <ctime>

using namespace std;

void curata()
{
    system("cls");
}

bool verificaParola()
{
    string parola = "1234";
    curata();
    cout<<"Introduceti parola pentru a accesa meniul(1234): \n";
    string parolaIntrodusa;
    cin>>parolaIntrodusa;

    if(parolaIntrodusa == parola)
    {
        curata();
        cout<<"Autentificarea s-a realizat cu succes!\n";
        cin.ignore();
        cin.get();
        return true;
    }
    else
    {
        curata();
        cout<<"Parola incorecta. Accesul este interzis!\n";
        this_thread::sleep_for(chrono::seconds(2)); //pune programul in asteptare 2 sec ca sa se vada mesajul anterior
        curata();
        return false;
    }
}

///Clasa Carte
class Carte
{
private:
    char* numeAutor;
    char* numeCarte;
    string genCarte;
    string recenzie;
    float rating;
    bool imprumutata;
    const int id;
    static int idContor;

public:
    Carte();

    Carte(char*, char*, string, string, float, bool);

    Carte(bool);

    Carte(float);

    Carte(const Carte& a);

    Carte& operator =(const Carte&);

    friend ostream& operator <<(ostream& out, const Carte& obj);
    friend istream& operator >>(istream& in, Carte& obj);

    void setNumeAutor(char* numeAutor)
    {
        if(this -> numeAutor != NULL)
            delete[] this -> numeAutor;
        this -> numeAutor = new char[strlen(numeAutor)+1];
        strcpy(this -> numeAutor, numeAutor);
    }
    void setNumeCarte(char* numeCarte)
    {
        if(this -> numeCarte != NULL)
            delete[] this-> numeCarte;
        this -> numeCarte = new char[strlen(numeCarte)+1];
        strcpy(this -> numeCarte, numeCarte);
    }
    void setGenCarte(string genCarte) {this -> genCarte = genCarte;}
    void setRecenzie(string recenzie) {this -> recenzie = recenzie;}
    void setRating(float rating) {this -> rating = rating;}
    void setImprumutata(bool imprumutata) {this -> imprumutata = imprumutata;}

    const char* getNumeAutor() {return this -> numeAutor;}
    const char* getNumeCarte() const{return this -> numeCarte;}
    string getGenCarte() const {return this -> genCarte;}
    string getRecenzie() {return this -> recenzie;}
    float getRating() {return this -> rating;}
    bool getImprumutata() {return this -> imprumutata;}
    static int getIdContor() {return Carte::idContor;}
    const int getId() {return this ->id;}

    ///functionalitate
    void imprumuta()
    {
        if(imprumutata != true)
            imprumutata = true;
        else
        {
            cout<<"Aceasta carte este deja imprumutata"<<endl;
        }
    }

    void returneaza()
    {
        imprumutata = false;
    }

    ~Carte()
    {
        if(this -> numeAutor != NULL)
        {
            delete[] this -> numeAutor;
            this -> numeAutor = NULL;
        }

        if(this -> numeCarte != NULL)
        {
            delete[] this -> numeCarte;
            this -> numeCarte = NULL;
        }
    }
};
///Constructor de initializare
Carte::Carte():id(idContor++)
{
    this -> numeAutor = new char[strlen("anonim")+1];
    strcpy(this -> numeAutor, "Anonim");
    this -> numeCarte = new char[strlen("anonim")+1];
    strcpy(this -> numeCarte, "Anonim");
    this -> genCarte = "nimic";
    this -> recenzie = "nimic";
    this -> rating =0;
    this -> imprumutata = false;
}
///Constructor cu toti parametrii
Carte::Carte(char* numeAutor, char* numeCarte, string genCarte, string recenzie, float rating, bool imprumutata):id(idContor), genCarte(genCarte), recenzie(recenzie), rating(rating), imprumutata(imprumutata)
{
    this -> numeAutor = new char[strlen(numeAutor)+1];
    strcpy(this -> numeAutor, numeAutor);

    this -> numeCarte = new char[strlen(numeCarte)+1];
    strcpy(this -> numeCarte, numeCarte);
}

Carte::Carte(bool imprumutata):id(idContor++)
{
    this -> numeAutor = new char[strlen("anonim")+1];
    strcpy(this -> numeAutor, "Anonim");
    this -> numeCarte = new char[strlen("anonim")+1];
    strcpy(this -> numeCarte, "Anonim");
    this -> genCarte = "nimic";
    this -> recenzie = "nimic";
    this -> rating =0;
    this -> imprumutata = imprumutata;
}

Carte::Carte(float rating):id(idContor++)
{
    this -> numeAutor = new char[strlen("anonim")+1];
    strcpy(this -> numeAutor, "Anonim");
    this -> numeCarte = new char[strlen("anonim")+1];
    strcpy(this -> numeCarte, "Anonim");
    this -> genCarte = "nimic";
    this -> recenzie = "nimic";
    this -> rating =rating;
    this -> imprumutata = false;
}

///Constructor de copiere
Carte::Carte(const Carte& a):id(idContor++)
{
    this -> numeAutor = new char[strlen(a.numeAutor)+1];
    strcpy(this -> numeAutor, a.numeAutor);

    this -> numeCarte = new char[strlen(a.numeCarte)+1];
    strcpy(this -> numeCarte, a.numeCarte);

    this -> genCarte = a.genCarte;
    this -> recenzie = a.recenzie;
    this -> rating = a.rating;
    this -> imprumutata = a.imprumutata;
}
///Supraincarcarea operatorului =
Carte& Carte::operator = (const Carte& a)
{
    if(this != &a)
    {
        if(this -> numeAutor != NULL)
        {
            delete[] this -> numeAutor;
            this -> numeAutor = NULL;
        }
        this -> numeAutor = new char[strlen(a.numeAutor)+1];
        strcpy(this -> numeAutor, a.numeAutor);

        if(this -> numeCarte != NULL)
        {
            delete[] this -> numeCarte;
            this -> numeCarte = NULL;
        }
        this -> numeCarte = new char[strlen(a.numeCarte)+1];
        strcpy(this -> numeCarte, a.numeCarte);
        this -> genCarte = a.genCarte;
        this -> recenzie = a.recenzie;
        this -> rating = a.rating;
        this -> imprumutata = a.imprumutata;
    }
    return *this;
}
///Supraincarcarea operatorului <<
ostream& operator <<(ostream& out, const Carte& obj)
{
    out<<"Numele autorului este: "<<obj.numeAutor<<endl;

    out<<"Numele cartii este: "<< obj.numeCarte<<endl;

    out<<"Genul cartii este: "<<obj.genCarte<<endl;

    out<<"Recenzia cartii este: "<<obj.recenzie<<endl;

    out<<"Rating-ul cartii este: "<<obj.rating<<endl;

    if(obj.imprumutata != true)
        out<<"Cartea poate fi imprumutata."<<endl;
    else
        out<<"Cartea nu poate fi imprumutata."<<endl;

    out<<"Id-ul cartii este: "<<obj.id<<endl;

    return out;
}
///Supraincarcarea operatorului >>
istream& operator >>(istream& in, Carte& obj)
{
    char aux1[100];
    cout<<"Introduceti numele autorului: ";
    in>>aux1;
    if(obj.numeAutor != NULL)
        delete[] obj.numeAutor;
    obj.numeAutor = new char[strlen(aux1)+1];
    strcpy(obj.numeAutor, aux1);
    cout<<endl;

    char aux[100];
    cout<<"Introduceti numele cartii: ";
    in>> aux;
    if(obj.numeCarte != NULL)
        delete[] obj.numeCarte;
    obj.numeCarte = new char[strlen(aux)+1];
    strcpy(obj.numeCarte, aux);
    cout<<endl;

    cout<<"Introduceti genul cartii: ";
    cin.ignore(100, '\n');
    getline(in, obj.genCarte);
    cout<<endl;

    cout<<"Introduceti o recenzie: ";
    cin.ignore(100, '\n');
    getline(in, obj.recenzie);
    cout<<endl;

    cout<<"Introduceti rating: ";
    cin.ignore(100, '\n');
    getline(in, obj.genCarte);
    cout<<endl;
    return in;
}

int Carte::idContor = 0;

///Clasa Bibliotecar
class Bibliotecar
{
private:
    char* nume;
    double salariu;
    int nrAniActivitate;
    int* aniActivitate;
    const int id;
    static int idContor;

public:
    Bibliotecar(); ///constructorul fara parametrii

    Bibliotecar(char*, double, int, int*); ///constructorul cu toti parametrii

    Bibliotecar(double);

    Bibliotecar(int);

    Bibliotecar(const Bibliotecar& pers); ///constructorul de copiere

    ///operatori
    Bibliotecar& operator = (const Bibliotecar&); /// forma supraincarcata a operatorului =

    friend ostream& operator <<(ostream& out, const Bibliotecar& pers); ///supraincarcarea operatorului <<

    friend istream& operator >>(istream& in, Bibliotecar& pers); ///supraincarcarea operatorului >>

    int operator [](int i) /// operatorul de indexare
    {
        if(i<0 || i > this -> nrAniActivitate-1)
            throw runtime_error("Out of range");
        else
            return this -> aniActivitate[i];
    }

    Bibliotecar& operator ++() ///operatorul ++
    {
        this -> salariu++;
        return *this;
    }

    Bibliotecar operator ++(int) ///operatorul ++
    {
        Bibliotecar a(*this);
        this -> salariu++;
        return a;
    }

    Bibliotecar operator +(const Bibliotecar& a) ///operator +
    {
        Bibliotecar aux(*this);
        aux.salariu = aux.salariu + a.salariu;
        return aux;
    }

    Bibliotecar operator +(int salariu) ///operator +
    {
        Bibliotecar aux(*this);
        aux.salariu = aux.salariu + salariu;
        return aux;
    }

    friend Bibliotecar operator +(int salariu, const Bibliotecar& a1) ///operator +
    {
        Bibliotecar aux(a1);
        aux.salariu = aux.salariu+salariu;
        return aux;
    }

    bool operator <=(const Bibliotecar& obj) ///operator conditional
    {
        return this -> salariu <= obj.salariu;
    }

    ///setteri
    void setNume(char* nume)
    {
        if(this -> nume != NULL)
            delete[] this -> nume;
        this -> nume = new char[strlen(nume)+1];
        strcpy(this -> nume, nume);

    }

    void setAniActivitate(int* aniActivitate, int nrAniActivitate)
    {

        if(this -> aniActivitate != NULL)
            delete[] this -> aniActivitate;
        this -> nrAniActivitate = nrAniActivitate;
        this -> aniActivitate = new int[this -> nrAniActivitate];
        for(int i = 0; i< this -> nrAniActivitate; i++)
            this -> aniActivitate[i] = aniActivitate[i];
    }


    void setSalariu(double salariu) {this -> salariu = salariu;}


    ///getteri
    const char* getNume() {return this -> nume;}
    double getSalariu() {return this -> salariu;}
    const int* getAniActivitate() {return this -> aniActivitate;}
    static int getIdContor() {return Bibliotecar::idContor;}
    const int getId() {return Bibliotecar::id;}

    ///functionalitate
    void vechime()
    {
        int maxim = aniActivitate[0];
        int minim = aniActivitate[0];
        for(int i = 1; i<this -> nrAniActivitate; i++)
        {
            if(maxim < aniActivitate[i])
                maxim = aniActivitate[i];
            if(minim > aniActivitate[i])
                minim = aniActivitate[i];
        }
        cout<<"Experienta in domeniu a bibliotecarului "<<this -> nume<<" este de "<< maxim - minim+1<<" ani.";
    }

    ///destructor
    ~Bibliotecar()
    {
        if(this -> nume != NULL)
        {
            delete[] this -> nume;
            this -> nume = NULL;
        }

        if(this -> aniActivitate != NULL)
        {
            delete[] this -> aniActivitate;
            this -> aniActivitate = NULL;
        }
    }
};
///Constructor de initializare
Bibliotecar::Bibliotecar():id(idContor++)
{
    this -> nume = new char[strlen("anonim")+1];
    strcpy(this -> nume, "Anonim");
    this -> salariu = 0;
    this -> nrAniActivitate = 0;
    this -> aniActivitate = NULL;
}
///Constructor cu toti parametrii
Bibliotecar::Bibliotecar(char* nume, double salariu, int nrAniActivitate, int* aniActivitate):id(idContor++), salariu(salariu), nrAniActivitate(nrAniActivitate)
{
    this -> nume = new char[strlen(nume)+1];
    strcpy(this -> nume, nume);

    this -> aniActivitate = new int[this -> nrAniActivitate];
    for (int i = 0; i< this -> nrAniActivitate; i++)
        this -> aniActivitate[i] = aniActivitate[i];
}

Bibliotecar::Bibliotecar(double salariu):id(idContor++)
{
    this -> nume = new char[strlen("anonim")+1];
    strcpy(this -> nume, "Anonim");
    this -> salariu = salariu;
    this -> nrAniActivitate = 0;
    this -> aniActivitate = NULL;
}

Bibliotecar::Bibliotecar(int nrAniActivitate):id(idContor++)
{
    this -> nume = new char[strlen("anonim")+1];
    strcpy(this -> nume, "Anonim");
    this -> salariu = 0;
    this -> nrAniActivitate = nrAniActivitate;
    this -> aniActivitate = NULL;
}

///Constructor de copiere
Bibliotecar::Bibliotecar(const Bibliotecar& pers):id(idContor++)
{
    this -> nume = new char[strlen(pers.nume)+1];
    strcpy(this -> nume,pers.nume);
    this -> salariu = pers.salariu;
    this -> nrAniActivitate = pers.nrAniActivitate;
    this -> aniActivitate = new int[this -> nrAniActivitate];
    for(int i =0; i< pers.nrAniActivitate; i++)  ///nu avem nevoie de this-> deoarece aici ne referim la membrii obiectului curent, iar acesti membri sunt aceiasi cu membrii obiectului pers pe care încercam sa-l copiem.
        this -> aniActivitate[i] = pers.aniActivitate[i];
}
///Supraincarcarea operatorului =
Bibliotecar& Bibliotecar::operator = (const Bibliotecar& pers)
{
    if(this != &pers)
    {
        if(this -> nume != NULL)
        {
            delete[] this -> nume;
            this -> nume = NULL;
        }
        this -> nume = new char[strlen(pers.nume)+1];
        strcpy(this -> nume, pers.nume);
        this -> salariu = pers.salariu;
        this -> nrAniActivitate = pers.nrAniActivitate;
        this -> aniActivitate = new int[this -> nrAniActivitate];
        for(int i =0; i< pers.nrAniActivitate; i++)
            this -> aniActivitate[i] = pers.aniActivitate[i];
    }
    return *this;
}
///Supraincarcarea operatorului <<
ostream& operator <<(ostream& out, const Bibliotecar& pers)
{
    out<<"Numele bibliotecarului este: "<<pers.nume<<endl;
    out<<"Salariul bibliotecarului este: "<<pers.salariu<<endl;
    out<<"Id-ul bibliotecarului este: "<<pers.id<<endl;
    return out;
}
///Supraincarcarea operatorului >>
istream& operator >>(istream& in, Bibliotecar& pers)
{
    char aux[100];
    cout<<"Introduceti numele bibliotecarului: ";
    in>>aux;
    if(pers.nume != NULL)
        delete[] pers.nume;
    pers.nume = new char[strlen(aux)+1];
    strcpy(pers.nume, aux);
    cout<<endl;

    cout<<"Introduceti salariul bibliotecarului: ";
    in>>pers.salariu;
    cout<<endl;
    return in;
}

int Bibliotecar::idContor = 0;

///Clasa Utilizator
class Utilizator
{
private:
    char* numeUtilizator;
    int varsta;
    char sex;
    string genPreferat;
    const int id;
    static int idContor;

public:
    Utilizator();

    Utilizator(char*, int, char, string);

    Utilizator(char);

    Utilizator(int);

    Utilizator(const Utilizator& obj);

    Utilizator& operator = (const Utilizator&);

    friend ostream& operator <<(ostream& out, const Utilizator& pers);
    friend istream& operator >>(istream& in, Utilizator& pers);

    ///setteri
    void setNumeUtilizator(char* numeUtilizator)
    {
        if(this -> numeUtilizator != NULL)
            delete[] this -> numeUtilizator;
        this -> numeUtilizator = new char[strlen(numeUtilizator)+1];
        strcpy(this -> numeUtilizator, numeUtilizator);
    }

    void setVarsta(int varsta) {this -> varsta = varsta;}
    void setSex(char sex) {this -> sex = sex;}
    void setGenPreferat(string genPreferat) {this -> genPreferat = genPreferat;}

    ///getteri
    const char* getNumeUtilizator() const{return this -> numeUtilizator;}
    int getVarsta() {return this -> varsta;}
    char getSex() {return this -> sex;}
    string getGenPreferat() {return this -> genPreferat;}
    static int getIdContor() {return Utilizator::idContor;}
    const int getId() {return Utilizator::id;}

    ///functionalitate
    void recomandaCarti(const vector<Carte>& listaCarti) const {
        cout << "Cartile recomandate pentru " << genPreferat << " sunt:" << endl;
        for (const Carte& carte : listaCarti) {
            if (genPreferat == carte.getGenCarte()) {
                cout << carte << endl;
            }
        }
    }

    ///destructor
    ~Utilizator()
    {
        if(this -> numeUtilizator != NULL)
            {
                delete[] this -> numeUtilizator;
                this -> numeUtilizator = NULL;
            }
    }
};
///Constructor de initializare
Utilizator::Utilizator():id(idContor++)
{
    this -> numeUtilizator = new char[strlen("Necunoscut")+1];
    strcpy(this -> numeUtilizator, "Necunoscut");
    this -> varsta = 0;
    this -> sex = 'X';
    this -> genPreferat = "gol";
}
///Constructor cu toti parametrii
Utilizator::Utilizator(char* numeUtilizator, int varsta, char sex, string genPreferat):id(idContor++), varsta(varsta), sex(sex), genPreferat(genPreferat)
{
    this -> numeUtilizator = new char[strlen(numeUtilizator)+1];
    strcpy(this -> numeUtilizator, numeUtilizator);
}
Utilizator::Utilizator(char sex):id(idContor++)
{
    this -> numeUtilizator = new char[strlen("Necunoscut")+1];
    strcpy(this -> numeUtilizator, "Necunoscut");
    this -> varsta = 0;
    this -> sex = sex;
    this -> genPreferat = "gol";
}

Utilizator::Utilizator(int varsta):id(idContor++)
{
    this -> numeUtilizator = new char[strlen("Necunoscut")+1];
    strcpy(this -> numeUtilizator, "Necunoscut");
    this -> varsta = varsta;
    this -> sex = 'X';
    this -> genPreferat = "gol";
}

///Constructor de copiere
Utilizator::Utilizator(const Utilizator& obj):id(idContor++)
{
    this -> numeUtilizator = new char[strlen(obj.numeUtilizator)+1];
    strcpy(this -> numeUtilizator, obj.numeUtilizator);
    this -> varsta = obj.varsta;
    this -> sex = obj.sex;
    this -> genPreferat = obj.genPreferat;
}
///Supraincarcarea operatorului =
Utilizator& Utilizator::operator=(const Utilizator& obj)
{
    if(this != &obj)
    {
        if(this -> numeUtilizator != NULL)
        {
            delete[] this -> numeUtilizator;
            this -> numeUtilizator = NULL;
        }
        this -> numeUtilizator = new char[strlen(obj.numeUtilizator)+1];
        strcpy(this -> numeUtilizator, obj.numeUtilizator);

        this -> varsta = obj.varsta;
        this -> sex = obj.sex;
        this -> genPreferat = obj.genPreferat;
    }
    return *this;
}
///Supraincarcarea operatorului <<
ostream& operator <<(ostream& out, const Utilizator& pers)
{
    out<<"Numele de utilizator este: "<<pers.numeUtilizator<<endl;
    out<<"Id-ul de utilizator este: "<<pers.id<<endl;
    out<<"Varsta utilizatorului este: "<<pers.varsta<<endl;
    out<<"Sexul utilizatorului este: "<<pers.sex<<endl;
    out<<"Genul preferat al utilizatorului este: "<<pers.genPreferat<<endl;
    return out;
}
///Supraincarcarea operatorului >>
istream& operator >>(istream& in, Utilizator& pers)
{
    char aux2[100];
    cout<<"Introduceti numele de utilizator: ";
    in>>aux2;
    if(pers.numeUtilizator != NULL)
        delete[] pers.numeUtilizator;
    pers.numeUtilizator = new char[strlen(aux2)+1];
    strcpy(pers.numeUtilizator, aux2);
    cout<<endl;

    cout<<"Introduceti varsta dumneavoastra: ";
    in>> pers.varsta;
    cout<<endl;

    bool valid = false;
    while(valid != true)
    {
        cout<<"Introduceti genul dumneavoastra(M/F): ";
        in>> pers.sex;
        cout<<endl;

        if(pers.sex == 'M' || pers.sex == 'F')
            valid = true;
        else
            cout<<"Va rugam introduceti 'M' pentru masculin sau 'F' pentru feminin!\n";
    }

    cout<<"Introduceti genul vostru preferat(aventura, science fiction, groaza): ";
    cin.ignore(100, '\n');
    getline(in, pers.genPreferat);
    cout<<endl;
    return in;
}

int Utilizator::idContor = 0;

struct data
{
    int zi;
    int luna;
    int an;
};
///Clasa imprumut
class Imprumut
{
private:

    string esteImprumutata;
    int durata;
    data dataImprumut;
    data dataScadenta;
    Carte* carte;
    Utilizator* utilizator;

public:
    Imprumut();
    Imprumut(string, int, data, data, Carte*, Utilizator*);
    Imprumut(int durata);
    Imprumut(string esteImprumutata);
    Imprumut(const Imprumut& imp);
    Imprumut& operator =(const Imprumut&);
    friend ostream& operator<<(ostream& out, const Imprumut& imp);
    friend istream& operator>>(istream& in, Imprumut& imp);
    friend Imprumut operator+(const Imprumut& rezervare, const Carte& client);
    friend Imprumut operator+(const Carte& client, const Imprumut& rezervare);

    ///functionalitate
    data returnare(int durata)
    {
        time_t now = time(NULL);
        struct tm scadenta_tm = *localtime(&now);
        scadenta_tm.tm_mday += durata;
        time_t scadenta = mktime(&scadenta_tm);

        data dataScadenta;
        dataScadenta.zi = scadenta_tm.tm_mday;
        dataScadenta.luna = scadenta_tm.tm_mon + 1;
        dataScadenta.an = scadenta_tm.tm_year + 1900;

        return dataScadenta;
    }


    ///setteri
    void setEsteImprumutata(string esteImprumutata) {this -> esteImprumutata = esteImprumutata;}
    void setDurata(int durata) {this -> durata = durata;}
    void setDataImprumutZi(int zi) {this -> dataImprumut.zi = zi;}
    void setDataImprumutLuna(int luna) {this -> dataImprumut.luna = luna;}
    void setDataImprumutAn(int an) {this -> dataImprumut.an = an;}
    void setDataScadentaZi(int zi) {this -> dataScadenta.zi = zi;}
    void setDataScadentaLuna(int luna) {this -> dataScadenta.luna = luna;}
    void setDataScadentaAn(int an) {this -> dataScadenta.an = an;}
    void setCarte(Carte* carte) {this -> carte = carte;}
    void setCititor(Utilizator* utilizator) {this -> utilizator = utilizator;}

    ///getteri
    string getEsteImprumutata() {return this -> esteImprumutata;}
    int getDurata() {return this -> durata = durata;}
    int getDataImprumutZi() {return this -> dataImprumut.zi;}
    int getDataImprumutLuna() {return this -> dataImprumut.luna;}
    int getDataImprumutAn() {return this -> dataImprumut.an;}
    int getDataScadentaZi() {return this -> dataScadenta.zi;}
    int getDataScadentaLuna() {return this -> dataScadenta.luna;}
    int getDataScadentaAn() {return this -> dataScadenta.an;}
    Carte* getCarte() {return this -> carte;}
    Utilizator* getCititor() {return this -> utilizator;}

    ~Imprumut()
    {
        this -> carte = NULL;
        this -> utilizator = NULL;
    }

};

///Constructorul de initializare
Imprumut::Imprumut()
{
    this -> esteImprumutata = "a imprumutat";
    this -> durata = 0;
    this -> dataImprumut.zi = 0;
    this -> dataImprumut.luna = 0;
    this -> dataImprumut.an = 0;
    this -> dataScadenta.zi = 0;
    this -> dataScadenta.luna = 0;
    this -> dataScadenta.an = 0;
    carte = NULL;
    utilizator = NULL;

}

///Constructorul cu toti parametrii
Imprumut::Imprumut(string esteImprumutata, int durata, data dataImprumut, data dataScadenta, Carte* carte, Utilizator* utilizator): esteImprumutata(esteImprumutata), durata(durata)
{
    this -> dataImprumut.zi = dataImprumut.zi;
    this -> dataImprumut.luna = dataImprumut.luna;
    this -> dataImprumut.an = dataImprumut.an;
    this -> dataScadenta.zi = dataScadenta.zi;
    this -> dataScadenta.luna = dataScadenta.luna;
    this -> dataScadenta.an = dataScadenta.an;
    this -> carte = carte;
    this -> utilizator = utilizator;
}
///Constructor cu parametrii
Imprumut::Imprumut(int durata)
{
    this -> durata = durata;
    this -> esteImprumutata = "a imprumutat";
    this -> dataImprumut.zi = 0;
    this -> dataImprumut.luna = 0;
    this -> dataImprumut.an = 0;
    this -> dataScadenta.zi = 0;
    this -> dataScadenta.luna = 0;
    this -> dataScadenta.an = 0;
    carte = NULL;
    utilizator = NULL;
}
///Constructor cu parametrii
Imprumut::Imprumut(string esteImprumutata)
{
    this -> esteImprumutata = esteImprumutata;
    this -> durata = 0;
    this -> dataImprumut.zi = 0;
    this -> dataImprumut.luna = 0;
    this -> dataImprumut.an = 0;
    this -> dataScadenta.zi = 0;
    this -> dataScadenta.luna = 0;
    this -> dataScadenta.an = 0;
    carte = NULL;
    utilizator = NULL;
}

///Constructorul de copiere
Imprumut::Imprumut(const Imprumut& imp)
{
    this -> esteImprumutata = imp.esteImprumutata;
    this -> durata = imp.durata;
    this -> dataImprumut.zi = imp.dataImprumut.zi;
    this -> dataImprumut.luna = imp.dataImprumut.luna;
    this -> dataImprumut.an = imp.dataImprumut.an;
    this -> dataScadenta.zi = imp.dataScadenta.zi;
    this -> dataScadenta.luna = imp.dataScadenta.luna;
    this -> dataScadenta.an = imp.dataScadenta.an;
    this -> carte = imp.carte;
    this -> utilizator = imp.utilizator;
}

///Supraincarcarea operatorului =
Imprumut& Imprumut::operator=(const Imprumut& imp)
{
    if(this != &imp)
    {
        this -> esteImprumutata = imp.esteImprumutata;
        this -> durata = imp.durata;
        this -> dataImprumut.zi = imp.dataImprumut.zi;
        this -> dataImprumut.luna = imp.dataImprumut.luna;
        this -> dataImprumut.an = imp.dataImprumut.an;
        this -> dataScadenta.zi = imp.dataScadenta.zi;
        this -> dataScadenta.luna = imp.dataScadenta.luna;
        this -> dataScadenta.an = imp.dataScadenta.an;
        this -> carte = imp.carte;
        this -> utilizator = imp.utilizator;
    }
    return *this;
}
///Supraincarcarea operatorului <<
ostream& operator <<(ostream& out, const Imprumut& imp)
{
    out<<"Vedeti daca cartea este imprumutata."<<imp.esteImprumutata<<endl;
    out<<"Cartea s-a imprumutat la data de: "<<imp.dataImprumut.zi<<"/"<<imp.dataImprumut.luna<<"/"<<imp.dataImprumut.an<<endl;
    out<<"Data scadenta este: "<<imp.dataScadenta.zi<<"/"<<imp.dataScadenta.luna<<"/"<<imp.dataScadenta.an<<endl;
    if(imp.carte !=NULL)
        out<<"Cartea "<<imp.carte -> getNumeCarte()<<endl;
    else
        out<<"Nu avem carte."<<endl;
    if(imp.utilizator != NULL)
        out<<"Cititorul "<<imp.utilizator -> getNumeUtilizator()<<endl;
    else
        out<<"Nu avem utilizator."<<endl;

    return out;
}
///Supraincarcarea operatorului >>
istream& operator >>(istream& in, Imprumut& imp)
{
    cout<<"Data imprumutului este: ";
    in>>imp.dataImprumut.zi>>imp.dataImprumut.luna>>imp.dataImprumut.an;

    cout<<"Data scadenta este: ";
    in>>imp.dataScadenta.zi>>imp.dataScadenta.luna>>imp.dataScadenta.an;

    return in;
}
///Adunarea a doua clase diferite
Imprumut operator+(const Imprumut& obj1, const Carte& obj2)
{
     Imprumut x(obj1);
     string str = obj2.getNumeCarte();
     x.esteImprumutata=x.esteImprumutata+" "+str;
     return x;

}
Imprumut operator+(const Carte& obj1, const Imprumut& obj2)
{
    Imprumut x(obj2);
    string str;
    str=obj1.getNumeCarte();
    x.esteImprumutata=x.esteImprumutata+" "+str;
    return x;

}

int main()
{
    Imprumut imprumut;
    int durataImprumut = 21;
    vector<Carte> listaCartiImprumutate;

    vector <Carte> listaCarti(6);
    Carte A1("Elena Vasilescu", "Lumina in pustiu", "aventura", "recenzia cartii", 7.5, false);
    listaCarti[0] = A1;
    Carte A2("Andrei Popescu", "Calatoria in timp", "science fiction", "recenzia cartii", 8, false);
    listaCarti[1] = A2;
    Carte A3("Gabriel Mihai", "Umbrele trecutului", "groaza", "recenzia cartii", 5.9, false);
    listaCarti[2] = A3;
    Carte A4("Adriana Neagu", "Cercul de foc", "science fiction", "recenzia cartii", 9.8, false);
    listaCarti[3] = A4;
    Carte A5("Cristian Radu", "Noaptea strigoilor", "groaza", "recenzia cartii", 6.8, false);
    listaCarti[4] = A5;
    Carte A6("Ioana Stoica", "In cautarea adevarului", "aventura", "recenzia cartii", 10, false);
    listaCarti[5] = A6;

    vector <Bibliotecar> listaBibliotecari(3);
    int v0[]= {2000, 2001, 2003, 2005, 2010, 2011, 2015, 2017, 2020, 2021, 2023};
    Bibliotecar B1("Adrian Cristescu", 7300.0, 11, v0);
    listaBibliotecari[0] = B1;

    int v1[]= { 2011, 2015, 2017, 2020, 2021, 2022, 2023};
    Bibliotecar B2("Ion Dumitrescu", 5700.50, 7, v1);
    listaBibliotecari[1] = B2;

    int v2[]= {2017, 2020, 2021, 2023};
    Bibliotecar B3("Gabriela Marin", 3245.78, 4,v2);
    listaBibliotecari[2] = B3;

    cout<<"Bine ati venit la Biblioteca Povestilor!\n";
    cout<<"Alegeti una dintre optiunile de mai jos pentru a incepe!\n";

    vector <Utilizator> listaUtilizatori(3);
    Utilizator C1("Andreea", 26, 'F', "aventura");
    listaUtilizatori[0] = C1;
    Utilizator C2("Ioana", 22, 'F', "groaza");
    listaUtilizatori[1] = C2;
    Utilizator C3("Alex", 17, 'M', "science fiction");
    listaUtilizatori[2] = C3;

    int optiune = 0;
    bool parolaRet = 0;

    while(optiune != 4)
    {
        cout<<"1.Cont\n";
        cout<<"2.Imprumut Carti\n";
        cout<<"3.Bibliotecar\n";
        cout<<"4.Iesire\n";

        cin>>optiune;
        switch(optiune)
        {
        case 1:
            {
                int optiuneCont = 0;

                while(optiuneCont != 3)
                {
                    curata();
                    cout<<"1.Creeaza un cont nou.\n";
                    cout<<"2.Contul meu.\n";
                    cout<<"3.Inapoi\n";

                    cin>>optiuneCont;

                    switch(optiuneCont)
                    {
                    case 1:
                        {
                            curata();
                            Utilizator u;
                            cin>>u;
                            listaUtilizatori.push_back(u);
                            break;
                        }
                    case 2:
                        {
                            curata();
                            if(listaUtilizatori.empty() != true)
                                {
                                    Utilizator u = listaUtilizatori.back(); ///acceseaza ultimul utilizator din lista
                                    cout<<u;
                                    cin.ignore();
                                    cin.get();
                                }
                            else
                                cout<<"Nu exista utilizatori in lista\n";
                                cin.ignore();
                                cin.get();

                            break;
                        }
                    case 3:
                        {
                            curata();
                            optiuneCont = 3;
                            break;
                        }
                    default:
                        {
                            curata();
                            cout<<"Comanda incorecta! Va rugam incercati din nou.\n";
                            break;
                        }
                    }
                }
                break;
            }
        case 2:
            {
                curata();
                if(listaUtilizatori.empty())
                {
                    cout<<"Va rugam sa creati un cont inainte de a accesa meniul 'Imprumut Carti'.\n";
                    cin.ignore();
                    cin.get();
                    curata();
                }
                else
                {
                    int optiuneImprumut = 0;

                    while(optiuneImprumut != 4)
                    {
                        cout<<"1.Imprumuta Carti.\n";
                        cout<<"2.Returneaza Carti.\n";
                        cout<<"3.Carti recomandate.\n";
                        cout<<"4.Inapoi.\n";

                        cin>>optiuneImprumut;

                        switch(optiuneImprumut)
                        {
                        case 1:
                            {
                                curata();

                                for(int i =0; i<listaCarti.size();i++)
                                {
                                    cout<<listaCarti[i]<<endl;
                                }

                                cout<<"Introduceti ID-ul cartii pe care doriti sa o imprumutati: ";
                                int idCarte;
                                cin>>idCarte;
                                Carte* carteDeImprumut = NULL;
                                for(int i = 0; i<listaCarti.size();i++)
                                {
                                    if(idCarte == listaCarti[i].getId())
                                    {
                                        carteDeImprumut = &listaCarti[i];
                                        break;
                                    }
                                }

                                if(carteDeImprumut && !carteDeImprumut -> getImprumutata())
                                {
                                    carteDeImprumut -> imprumuta();
                                    cout<<"Ati imprumutat cartea cu succes!"<<endl;
                                    data dataScadenta = imprumut.returnare(durataImprumut);
                                    cout << "Data scadenta pentru returnarea cartii este: " << dataScadenta.zi << "/"<< dataScadenta.luna << "/" << dataScadenta.an << endl;
                                }
                                else
                                    cout<<"Aceasta carte nu poate fi imprumutata momentan."<<endl;

                                cout<<"Apasati Enter pentru a continua\n";
                                cin.ignore();
                                cin.get(); // Asteapta pana cand utilizatorul apasa Enter
                                curata();

                                break;
                            }

                        case 2:
                            {
                                curata();
                                cout<<"Lista de carti imprumutate: "<<endl;
                                for(int i = 0; i<listaCarti.size(); i++)
                                {
                                    if(listaCarti[i].getImprumutata())
                                        cout<<"ID: "<< listaCarti[i].getId()<< " - "<<listaCarti[i].getNumeCarte()<<endl;
                                }
                                cout<<"Introduceti ID-ul cartii pe care doriti sa o returnati: ";
                                int idCarteDeReturnat;
                                cin>>idCarteDeReturnat;
                                for(int i = 0; i<listaCarti.size(); i++)
                                {
                                    if(idCarteDeReturnat == listaCarti[i].getId())
                                    {
                                        listaCarti[i].returneaza();
                                        cout<<"Ati returnat cartea cu succes!"<<endl;
                                    }
                                }

                                cout<<"Apasati Enter pentru a continua\n";
                                cin.ignore();
                                cin.get();
                                curata();
                                break;
                            }
                        case 3:
                            {
                                curata();
                                if (!listaUtilizatori.empty())
                                {
                                    Utilizator& ultimulUtilizator = listaUtilizatori.back();
                                    ultimulUtilizator.recomandaCarti(listaCarti);
                                }
                                else
                                {
                                    cout << "Nu exista utilizatori in lista. Va rugam sa creati un cont inainte de a accesa meniul 'Imprumut Carti'." << endl;
                                }
                                cin.ignore();
                                cin.get();
                                curata();
                                break;
                            }
                        case 4:
                            {
                                curata();
                                optiuneImprumut = 4;
                                cout<<"Se revine la meniul anterior!\n";
                                cout<<"Apasati Enter pentru a continua!\n";
                                cin.ignore();
                                cin.get();
                                break;
                            }
                        default:
                            {
                                curata();
                                cout<<"Comanda incorecta! Va rugam incercati din nou.\n";
                                break;
                            }
                        }
                    }
                }
                break;
            }
        case 3:
            {
                int optiuneBibliotecar = 0;
                curata();
                parolaRet = verificaParola();
                while((optiuneBibliotecar != 12) && (parolaRet == true))
                {
                    cout<<"1.Adauga carte.\n";
                    cout<<"2.Adauga utilizator.\n";
                    cout<<"3.Adauga bibliotecar.\n";
                    cout<<"4.Vezi lista de carti.\n";
                    cout<<"5.Vezi lista de cititori.\n";
                    cout<<"6.Vezi lista de bibliotecari.\n";
                    cout<<"7.Sterge carte.\n";
                    cout<<"8.Sterge utilizator.\n";
                    cout<<"9.Sterge bibliotecar.\n";
                    cout<<"10.Adaugati o marire bibliotecarului.\n";
                    cout<<"11.Realizeaza un imprumut pentru cititor.\n";
                    cout<<"12.Inapoi\n";

                    cin>>optiuneBibliotecar;
                    switch(optiuneBibliotecar)
                    {
                    case 1:
                        {
                            curata();
                            Carte c;
                            cin>>c;
                            listaCarti.push_back(c);
                            cin.ignore();
                            cin.get();
                            curata();
                            break;
                        }
                    case 2:
                        {
                            curata();
                            Utilizator u;
                            cin>>u;
                            listaUtilizatori.push_back(u);
                            cin.ignore();
                            cin.get();
                            curata();
                            break;
                        }
                    case 3:
                        {
                            curata();
                            Bibliotecar a;
                            cin>>a;
                            listaBibliotecari.push_back(a);
                            cin.ignore();
                            cin.get();
                            curata();
                            break;
                        }
                    case 4:
                        {
                            curata();
                            for(int i = 0; i<listaCarti.size(); i++)
                            {
                                cout<<listaCarti[i];
                                cout<<endl;
                            }
                            cin.ignore();
                            cin.get();
                            curata();
                            break;
                        }
                    case 5:
                        {
                            curata();
                            for(int i = 0; i<listaUtilizatori.size(); i++)
                            {
                                cout<<listaUtilizatori[i];
                                cout<<endl;
                            }
                            break;
                        }
                    case 6:
                        {
                            curata();

                            for(int i=0; i<listaBibliotecari.size(); i++)
                            {
                                cout<<listaBibliotecari[i];
                                listaBibliotecari[i].vechime();
                                cout<<endl<<endl;
                            }
                            cin.ignore();
                            cin.get();
                            curata();
                            break;
                        }
                    case 7:
                        {
                            curata();
                            for (int i = 0; i < listaCarti.size(); i++)
                                cout << listaCarti[i] << endl;

                            cout << "Introduceti ID-ul cartii pe care doriti sa o stergeti: ";
                            int id;
                            cin >> id;

                            for (int i = 0; i < listaCarti.size(); i++)
                            {
                                if (id == listaCarti[i].getId())
                                {
                                    listaCarti.erase(listaCarti.begin() + i);
                                    cout << "Cartea cu ID-ul " << id << " a fost stearsa cu succes!" << endl;
                                    break;
                                }
                            }
                            break;
                        }


                    case 8:
                        {
                            curata();
                            for(int i = 0; i<listaUtilizatori.size();i++)
                                cout<<listaUtilizatori[i]<<endl;
                            cout<<"Introduceti id-ul utilizatorului pe care doriti sa il stergeti: ";
                            int id;
                            cin>> id;
                            for(int i = 0; i<listaUtilizatori.size();i++)
                                if(id == listaUtilizatori[i].getId())
                                    listaUtilizatori.erase(listaUtilizatori.begin()+i);
                            cin.ignore();
                            cin.get();
                            curata();
                            break;
                        }
                    case 9:
                        {
                            curata();
                            for(int i = 0; i<listaBibliotecari.size();i++)
                                cout<<listaBibliotecari[i]<<endl;
                            cout<<"Introduceti id-ul utilizatorului pe care doriti sa il stergeti: ";
                            int id;
                            cin>> id;
                            for(int i = 0; i<listaBibliotecari.size();i++)
                                if(id == listaBibliotecari[i].getId())
                                    listaBibliotecari.erase(listaBibliotecari.begin()+i);
                            cin.ignore();
                            cin.get();
                            curata();
                            break;
                        }
                    case 10:
                        {
                            curata();
                            for(int i = 0; i<listaBibliotecari.size(); i++)
                                cout<<listaBibliotecari[i]<<endl;
                            cout<<"Introduceti id-ul bibliotecarului caruia doriti sa ii modificati salariul. ";
                            int id;
                            cin>>id;
                            cout<<endl;

                            cout<<"Introduceti suma pe care doriti sa o adaugati la salariu: ";
                            int suma;
                            cin>>suma;
                            cout<<endl;

                            for(int i =0; i<listaBibliotecari.size(); i++)
                                if(id == listaBibliotecari[i].getId())
                                    listaBibliotecari[i] = listaBibliotecari[i] + suma;
                            curata();
                            break;
                        }
                  case 11:
                        {
                            curata();
                            Imprumut a;
                            if (listaUtilizatori.empty() || listaCarti.empty()) {
                                cout << "Nu exista suficiente utilizatori sau carti pentru a efectua un imprumut." << endl;
                            } else {
                                // Afisare liste de utilizatori si carti pentru referinta
                                cout << "Lista de utilizatori existenti:\n";
                                for (int i = 0; i < listaUtilizatori.size(); i++) {
                                    cout << "ID: " << listaUtilizatori[i].getId() << " - " << listaUtilizatori[i].getNumeUtilizator() << endl;
                                }

                                cout << "\nLista de carti existente:\n";
                                for (int i = 0; i < listaCarti.size(); i++) {
                                    cout << "ID: " << listaCarti[i].getId() << " - " << listaCarti[i].getNumeCarte() << endl;
                                }

                                int idUtilizator, idCarte;
                                cout << "Introduceti ID-ul utilizatorului care a imprumutat: ";
                                cin >> idUtilizator;
                                cout << "Introduceti ID-ul cartii imprumutate: ";
                                cin >> idCarte;

                                // Gasiti utilizatorul si cartea corespunzatoare
                                Utilizator utilizatorImprumutat;
                                Carte carteImprumutata;

                                for (int i = 0; i < listaUtilizatori.size(); i++) {
                                    if (listaUtilizatori[i].getId() == idUtilizator) {
                                        a.setCititor(&listaUtilizatori[i]);
                                        break;
                                    }
                                }

                                for (int i = 0; i < listaCarti.size(); i++) {
                                    if (listaCarti[i].getId() == idCarte) {
                                        a.setCarte(&listaCarti[i]);
                                        break;
                                    }
                                }

                                // Creati un obiect Imprumut utilizand operatorul +
                                a = a + *(a.getCarte());
                                a.getCarte() -> setImprumutata(true);

                                // Afisati cine a efectuat imprumutul si ce carte a fost imprumutata

                                cout<<a.getCititor() -> getNumeUtilizator() <<" "<<a.getEsteImprumutata()<<"."<<endl;
                                ///cout << "Imprumut efectuat de: " << a.getCititor() -> getNumeUtilizator<< endl;

                            }

                            cout << "Apasati Enter pentru a continua\n";
                            cin.ignore();
                            cin.get();
                            curata();
                            break;
                        }


                    case 12:
                        {
                            curata();
                            optiuneBibliotecar = 12;
                            cout<<"Se revine la meniul anterior.\n";
                            cin.ignore();
                            cin.get();
                            break;
                        }
                    default:
                        {
                            cout<<"Comanda incorecta! Va rugam incercati din nou.\n";
                            break;
                        }
                    }

                }
                optiuneBibliotecar = 0;
                break;
            }

        case 4:
            {
                optiune = 4;
                break;
            }

        default:
            {
                curata();
                cout<<"Comanda incorecta! Va rugam incercati din nou.\n\n";
                break;
            }

        }
    }
    return 0;
}
