#include <iostream>
#include <string>
#include <cstring>
#include <windows.h>
#include <vector>
#include <thread>
#include <ctime>
#include <algorithm>

using namespace std;

void curata()
{
    system("cls");
}

bool verificaParola()
{
    cout<<"Introduceti parola pentru a accesa meniul(1234)";
    string parola = "1234";
    string parolaIntrodusa;
    cin >>parolaIntrodusa;

    if(parolaIntrodusa==parola)
    {
        cout<<"Autentificarea s-a realizat cu succes!";
        cin.ignore();
        cin.get();
        return true;
    }
    else
    {
        cout<<"Parola incorecta. Veti reveni la meniul anterior!";
        cin.ignore();
        cin.get();
        return false;
    }
}

///Clasa Utilizator
class Utilizator
{
private:
    char* numeUtilizator;
    int varsta;
    char sex;
    string genPreferat;
    int aniCard;
    const int id;
    static int idContor;

public:
    Utilizator();

    Utilizator(char*, int, char, string, int);

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
    void setAniCard(int aniCard) {this -> aniCard = aniCard;}

    ///getteri
    const char* getNumeUtilizator() const{return this -> numeUtilizator;}
    int getVarsta() {return this -> varsta;}
    char getSex() {return this -> sex;}
    string getGenPreferat() {return this -> genPreferat;}
    int getAniCard() {return this -> aniCard;}
    static int getIdContor() {return Utilizator::idContor;}
    const int getId() {return Utilizator::id;}

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
    this -> aniCard =0;
}
///Constructor cu toti parametrii
Utilizator::Utilizator(char* numeUtilizator, int varsta, char sex, string genPreferat, int aniCard):id(idContor++), varsta(varsta), sex(sex), genPreferat(genPreferat), aniCard(aniCard)
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
    this -> aniCard = 0;
}

Utilizator::Utilizator(int varsta):id(idContor++)
{
    this -> numeUtilizator = new char[strlen("Necunoscut")+1];
    strcpy(this -> numeUtilizator, "Necunoscut");
    this -> varsta = varsta;
    this -> sex = 'X';
    this -> genPreferat = "gol";
    this -> aniCard = 0;
}

///Constructor de copiere
Utilizator::Utilizator(const Utilizator& obj):id(idContor++)
{
    this -> numeUtilizator = new char[strlen(obj.numeUtilizator)+1];
    strcpy(this -> numeUtilizator, obj.numeUtilizator);
    this -> varsta = obj.varsta;
    this -> sex = obj.sex;
    this -> genPreferat = obj.genPreferat;
    this -> aniCard = obj.aniCard;
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
        this -> aniCard = obj.aniCard;
    }
    return *this;
}
///Supraincarcarea operatorului <<
ostream& operator <<(ostream& out, const Utilizator& pers)
{
    out<<"Numele de utilizator este: "<<pers.numeUtilizator<<endl;
    out<<"Varsta utilizatorului este: "<<pers.varsta<<endl;
    out<<"Sexul utilizatorului este: "<<pers.sex<<endl;
    out<<"Genul preferat al utilizatorului este: "<<pers.genPreferat<<endl;
    out<<"Utilizatorul are un card bibliotecar de "<<pers.aniCard<<" ani."<<endl<<endl;
    out<<"Id-ul de utilizator este: "<<pers.id<<endl;
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

    cout<<"Introduceti genul vostru preferat(science, fiction): ";
    cin.ignore();
    getline(in, pers.genPreferat, '\n');
    cout<<endl;

    cout<<"Introduceti de cat timp aveti card bibliotecar: ";
    in>>pers.aniCard;
    cout<<endl;
    return in;
}

int Utilizator::idContor = 0;


class IOInterface
{
public:
    virtual ostream& afisare(ostream&)const = 0;
    virtual istream& citire(istream&) = 0;
};
class Carte:public IOInterface
{
protected:
    string numeAutor;
    string numeCarte;
    string genCarte;
    string recenzie;
    float rating;
    bool imprumutata;
    int vechimeaCartii;
    const int id;
    static int idContor;
public:
    ///Constructorul fara parametrii, cu toti parametrii si copy-constructer, operatorul egal
    Carte();
    Carte(string, string, string, string, float, bool, int);
    Carte(const Carte& a);
    Carte& operator =(const Carte& a);

    ///operatorii <<, >>
    ostream& afisare(ostream& out)const
    {
        out<<"Numele autorului este: "<<this ->numeAutor<<endl;

        out<<"Numele cartii este: "<< this ->numeCarte<<endl;

        out<<"Genul cartii este: "<<this ->genCarte<<endl;

        out<<"Recenzia cartii este: "<<this ->recenzie<<endl;

        out<<"Rating-ul cartii este: "<<this ->rating<<endl;

        if(this ->imprumutata != true)
            out<<"Cartea poate fi imprumutata."<<endl;
        else
            out<<"Cartea nu poate fi imprumutata."<<endl;

        out<<"Id-ul cartii este: "<<this ->id<<endl;

        return out;
    }

    istream& citire(istream& in)
    {
        cout<<"Introduceti numele autorului: ";
        cin.ignore();
        getline(in, this -> numeAutor, '\n');
        cout<<endl;

        cout<<"Introduceti numele cartii: ";
        getline(in, this -> numeCarte, '\n');
        cout<<endl;

        cout<<"Introduceti genul cartii: ";
        cin.ignore();
        getline(in, this -> genCarte, '\n');
        cout<<endl;

        cout<<"Introduceti o recenzie: ";
        getline(in, this -> recenzie, '\n');
        cout<<endl;

        cout<<"Introduceti rating: ";
        in>>this -> rating;
        cout<<endl;
        return in;
    }

    friend ostream& operator <<(ostream& out,const Carte& c);
    friend istream& operator >>(istream& in,Carte& c);
    ///setteri
    void setNumeAutor(string numeAutor) {this -> numeAutor = numeAutor;}
    void setNumeCarte(string numeCarte) {this -> numeCarte = numeCarte;}
    void setGenCarte(string genCarte) {this -> genCarte = genCarte;}
    void setRecenzie(string recenzie) {this -> recenzie = recenzie;}
    void setRating(float rating) {this -> rating = rating;}
    void setImprumutata(bool imprumutata) {this -> imprumutata = imprumutata;}
    void setVarstaRecomandata(int vechimeaCartii) {this -> vechimeaCartii = vechimeaCartii;}

    ///getteri
    const string getNumeAutor() {return this -> numeAutor;}
    const string getNumeCarte() const{return this -> numeCarte;}
    string getGenCarte() const {return this -> genCarte;}
    string getRecenzie() {return this -> recenzie;}
    float getRating() {return this -> rating;}
    bool getImprumutata() {return this -> imprumutata;}
    int getVarstaRecomandata() {return this -> vechimeaCartii;}
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

    virtual ~Carte(){}

    ///functia mostenita
    virtual float gradCautare() =0;
};

int Carte::idContor = 0;

///Constructorul de initializare
Carte::Carte():id(idContor++)
{
    this -> numeAutor = "anonim";
    this -> numeCarte = "anonim";
    this -> genCarte = "nimic";
    this -> recenzie = "nimic";
    this -> rating =0;
    this -> imprumutata = false;
    this -> vechimeaCartii = 0;
}

///Constructorul cu toti parametrii
Carte::Carte(string numeAutor, string numeCarte, string genCarte, string recenzie, float rating, bool imprumutata, int vechimeaCartii):id(idContor++), numeAutor(numeAutor),
        numeCarte(numeCarte), genCarte(genCarte), recenzie(recenzie), rating(rating), imprumutata(imprumutata), vechimeaCartii(vechimeaCartii) {}

///Copy-Constructor
Carte::Carte(const Carte& a):id(idContor++)
{
    this -> numeAutor = a.numeAutor;
    this -> numeCarte = a.numeCarte;
    this -> genCarte = a.genCarte;
    this -> recenzie = a.recenzie;
    this -> rating = a.rating;
    this -> imprumutata = a.imprumutata;
    this -> vechimeaCartii = a.vechimeaCartii;
}

///Supraincarcarea operatorului egal
Carte& Carte::operator =(const Carte& a)
{
    if(this != &a)
    {
        this -> numeAutor = a.numeAutor;
        this -> numeCarte = a.numeCarte;
        this -> genCarte = a.genCarte;
        this -> recenzie = a.recenzie;
        this -> rating = a.rating;
        this -> imprumutata = a.imprumutata;
        this -> vechimeaCartii = a.vechimeaCartii;
    }
    return *this;
}

///Operatorii >>, <<
ostream& operator <<(ostream& out, const Carte& c)
{
    return c.afisare(out);
}

istream& operator >>(istream& in, Carte& c)
{
    return c.citire(in);
}

class Science:virtual public Carte
{
private:
    string domeniu;
    float dificultate;
public:
    ///constructorii care vor mosteni din clasa Carte celelalte atribute
    Science():Carte()
    {
        this -> domeniu = "nimic";
    }

    Science(string numeAutor, string numeCarte, string genCarte, string recenzie, float rating, bool imprumutata, int vechimeaCartii, string domeniu, float dificultate):
        Carte(numeAutor, numeCarte, genCarte, recenzie, rating, imprumutata, vechimeaCartii)
    {
        this -> domeniu = domeniu;
        this -> dificultate = dificultate;
    }

    Science(const Science& s):Carte(s)
    {
        this -> domeniu = s.domeniu;
        this -> dificultate = s.dificultate;
    }

    Science& operator =(const Science& s)
    {
        if(this != &s)
        {
            Carte::operator=(s);
            this -> domeniu = s.domeniu;
            this -> dificultate;
        }
        return *this;
    }

    void setDomeniu(string domeniu) {this -> domeniu = domeniu;}
    string getDomeniu() const{return this -> domeniu;}

    ///operatorii >>, <<
    ostream& afisare(ostream& out)const
    {
        Carte::afisare(out);
        out<<"Domeniul de cercetare al cartii este: "<<this -> domeniu<<endl;
        out<<"Dificultatea de citire a cartii pe o scara de la 1 la 10 este de: "<<this -> dificultate<<endl;
        return out;
    }

    istream& citire(istream& in)
    {
        Carte::citire(in);
        cout<<"Dati domeniul de cercetare: ";
        cin.ignore();
        getline(in, this -> domeniu, '\n');

        cout<<"Dati gradul de dificultate de citire a cartii: ";
        in>>this->dificultate;
        cout<<endl;
    }

    float gradCautare() override
    {
       return (rating*vechimeaCartii)/dificultate;
    }

    virtual ~Science() {};
};

class Fiction: virtual public Carte
{
private:
    string genLiterar; //fantezie, aventura
public:
    Fiction():Carte()
    {
        this -> genLiterar = "nimic";
    }
    Fiction(string numeAutor, string numeCarte, string genCarte, string recenzie, float rating, bool imprumutata, int vechimeaCartii, string genLiterar):
        Carte(numeAutor, numeCarte, genCarte, recenzie, rating, imprumutata, vechimeaCartii)
    {
        this -> genLiterar = genLiterar;
    }
    Fiction(const Fiction& f): Carte(f)
    {
        this -> genLiterar = f.genLiterar;
    }
    Fiction& operator=(const Fiction& f)
    {
        if(this != &f)
        {
            Carte::operator =(f);
            this -> genLiterar = f.genLiterar;
        }
        return *this;
    }

    void setGenLiterar(string genLiterar) {this -> genLiterar = genLiterar;}
    string getGenLiterar() const{return this -> genLiterar;}

    ostream& afisare(ostream& out) const
    {
        Carte::afisare(out);
        out<<"Specializarea cartii este: "<<this -> genLiterar<<endl;
        return out;
    }

    istream& citire(istream& in)
    {
        Carte::citire(in);

        cout<<"Dati genul literar: ";
        in>>this -> genLiterar;
        cout<<endl;
        return in;
    }

    float gradCautare() override
    {
        return rating;
    }
    virtual ~Fiction() {};
};

class Science_Fiction: public Science, public Fiction
{
private:
    float popularitate;
public:
    Science_Fiction(): Carte(), Science(), Fiction() {popularitate =0;}
    Science_Fiction(string numeAutor, string numeCarte, string genCarte, string recenzie, float rating, bool imprumutata, int vechimeaCartii, string domeniu, string genLiterar, float dificultate, float popularitate):
        Carte(numeAutor, numeCarte, genCarte, recenzie, rating, imprumutata, vechimeaCartii),
        Science(numeAutor, numeCarte, genCarte, recenzie, rating, imprumutata, vechimeaCartii, domeniu, dificultate),
        Fiction(numeAutor, numeCarte, genCarte, recenzie, rating, imprumutata, vechimeaCartii, genLiterar)
    {
        this -> popularitate = popularitate;
    }
    Science_Fiction(const Science_Fiction& sf): Carte(sf), Science(sf), Fiction(sf) {this -> popularitate = sf.popularitate;}
    Science_Fiction& operator =(const Science_Fiction& sf)
    {
        if(this != &sf)
        {
           Carte::operator =(sf);
           Science::operator =(sf);
           this -> popularitate = sf.popularitate;
        }
        return *this;
    }

    ostream& afisare(ostream& out) const
    {
        Carte::afisare(out);
        out<<"Cartea combina elemente din "<< getDomeniu() <<" si "<<getGenLiterar()<<".\n";
        out<<"Popularitatea cartii pe o scara de la 1 la 10: "<<this -> popularitate<<endl;
        return out;
    }
    istream& citire(istream& in)
    {
        Carte::citire(in);
        cout<<"Popularitatea cartii pe o scara de la 1 la 10: ";
        in>>this -> popularitate;
        cout<<endl;
        return in;
    }

    float gradCautare()
    {
        return rating*popularitate;
    }
    virtual ~Science_Fiction() {};
};

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


public:
    Imprumut();
    Imprumut(string, int, data, data);
    Imprumut(int durata);
    Imprumut(string esteImprumutata);
    Imprumut(const Imprumut& imp);
    Imprumut& operator =(const Imprumut&);
    friend ostream& operator<<(ostream& out, const Imprumut& imp);
    friend istream& operator>>(istream& in, Imprumut& imp);

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

    ///getteri
    string getEsteImprumutata() {return this -> esteImprumutata;}
    int getDurata() {return this -> durata = durata;}
    int getDataImprumutZi() {return this -> dataImprumut.zi;}
    int getDataImprumutLuna() {return this -> dataImprumut.luna;}
    int getDataImprumutAn() {return this -> dataImprumut.an;}
    int getDataScadentaZi() {return this -> dataScadenta.zi;}
    int getDataScadentaLuna() {return this -> dataScadenta.luna;}
    int getDataScadentaAn() {return this -> dataScadenta.an;}


    ~Imprumut()
    {
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

}

///Constructorul cu toti parametrii
Imprumut::Imprumut(string esteImprumutata, int durata, data dataImprumut, data dataScadenta): esteImprumutata(esteImprumutata), durata(durata)
{
    this -> dataImprumut.zi = dataImprumut.zi;
    this -> dataImprumut.luna = dataImprumut.luna;
    this -> dataImprumut.an = dataImprumut.an;
    this -> dataScadenta.zi = dataScadenta.zi;
    this -> dataScadenta.luna = dataScadenta.luna;
    this -> dataScadenta.an = dataScadenta.an;
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
    }
    return *this;
}
///Supraincarcarea operatorului <<
ostream& operator <<(ostream& out, const Imprumut& imp)
{
    out<<"Vedeti daca cartea este imprumutata."<<imp.esteImprumutata<<endl;
    out<<"Cartea s-a imprumutat la data de: "<<imp.dataImprumut.zi<<"/"<<imp.dataImprumut.luna<<"/"<<imp.dataImprumut.an<<endl;
    out<<"Data scadenta este: "<<imp.dataScadenta.zi<<"/"<<imp.dataScadenta.luna<<"/"<<imp.dataScadenta.an<<endl;
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

void meniuPrincipal()
{
    cout<<"1. Cont\n";
    cout<<"2. Imprumut Carti\n";
    cout<<"3. Bibliotecar\n";
    cout<<"4. Iesire\n";

}

void meniuCont()
{
    curata();
    cout<<"1. Creeaza un cont nou.\n";
    cout<<"2. Contul meu.\n";
    cout<<"3. Inapoi\n";
}

void meniuImprumut()
{
    curata();
    cout<<"1. Imprumuta Carti.\n";
    cout<<"2. Returneaza Carti.\n";
    cout<<"3. Carti recomandate.\n";
    cout<<"4. Sortate dupa popularitate, dificultate.\n";
    cout<<"5. Inapoi.\n";
}

void meniuBibliotecar()
{
    curata();
    cout<<"1.  Adauga carte.\n";
    cout<<"2.  Adauga utilizator.\n";
    cout<<"3.  Adauga bibliotecar.\n";
    cout<<"4.  Vezi lista de carti.\n";
    cout<<"5.  Vezi lista de cititori.\n";
    cout<<"6.  Vezi lista de bibliotecari.\n";
    cout<<"7.  Sterge carte.\n";
    cout<<"8.  Sterge utilizator.\n";
    cout<<"9.  Sterge bibliotecar.\n";
    cout<<"10. Adaugati o marire bibliotecarului.\n";
    cout<<"11. Inapoi\n";
}

void comandaDefault()
{
    curata();
    cout<<"Comanda incorecta! Va rugam incercati din nou.\n";
}

void apasaEnter()
{
    cout<<"Apasati Enter pentru a continua\n";
    cin.ignore();
    cin.get(); // Asteapta pana cand utilizatorul apasa Enter
    curata();
}

bool compararePopularitate(Carte* a, Carte* b) {
    return a->gradCautare() > b->gradCautare();
}

int main()
{
    Imprumut imprumut;
    int durataImprumut = 21;
    vector<Carte> listaCartiImprumutate;

    vector<Carte*> listaCarti(6);
    Carte* A1 = new Fiction("Elena Vasilescu", "Lumina in pustiu", "fiction", "recenzia cartii", 7.5, false, 16, "fantezie");
    listaCarti[0] = A1;
    Carte* A2 = new Fiction("Cristian Radu", "Noaptea strigoilor", "fiction", "recenzia cartii", 6.8, false, 24, "aventura");
    listaCarti[1] = A2;
    Carte* A3 = new Science("Gabriel Mihai", "Umbrele trecutului", "science", "recenzia cartii", 5.9, false, 18, "istorie", 7);
    listaCarti[2] = A3;
    Carte* A4 = new Science("Ioana Stoica", "In cautarea adevarului", "science", "recenzia cartii", 10, false, 30, "fizica",10);
    listaCarti[3] = A4;
    Carte* A5 = new Science_Fiction("Adriana Neagu", "Cercul de foc", "science fiction", "recenzia cartii", 9.8, false, 12, "fizica", "aventura", 6, 9);
    listaCarti[4] = A5;
    Carte* A6 = new Science_Fiction("Andrei Popescu", "Calatoria in timp", "science fiction", "recenzia cartii", 8, false, 20, "istorie", "fantezie", 4, 7);
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
    Utilizator C1("Andreea", 26, 'F', "aventura", 2);
    listaUtilizatori[0] = C1;
    Utilizator C2("Ioana", 22, 'F', "groaza", 1);
    listaUtilizatori[1] = C2;
    Utilizator C3("Alex", 17, 'M', "science fiction", 0);
    listaUtilizatori[2] = C3;

    int optiune = 0;
    bool parolaRet = 0;

    while(optiune != 4)
    {
        meniuPrincipal();

        cin>>optiune;
        switch(optiune)
        {
        case 1:
            {
                int optiuneCont = 0;

                while(optiuneCont != 3)
                {
                    meniuCont();

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
                            if(listaUtilizatori.size() >= 4)
                                {
                                    Utilizator u = listaUtilizatori.back();

                                    cout<<u;
                                    cin.ignore();
                                    cin.get();
                                }
                            else
                                cout<<"Va rugam sa creati un cont inainte de a accesa meniul.\n";
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
                            comandaDefault();
                            break;
                        }
                    }
                }
                break;
            }
        case 2:
            {
                curata();
                if(listaUtilizatori.size()<=3)
                {
                    cout<<"Va rugam sa creati un cont inainte de a accesa meniul 'Imprumut Carti'.\n";
                    cin.ignore();
                    cin.get();
                    curata();
                }
                else
                {
                    int optiuneImprumut = 0;

                    while(optiuneImprumut != 5)
                    {
                        meniuImprumut();

                        cin>>optiuneImprumut;

                        switch(optiuneImprumut)
                        {
                        case 1:
                            {
                                curata();

                                for(int i =0; i<listaCarti.size();i++)
                                {
                                    cout<<*listaCarti[i]<<endl;
                                }

                                cout<<"Introduceti ID-ul cartii pe care doriti sa o imprumutati: ";
                                int idCarte;
                                cin>>idCarte;
                                Carte* carteDeImprumut = NULL;
                                for(int i = 0; i<listaCarti.size();i++)
                                {
                                    if(idCarte == listaCarti[i]->getId())
                                    {
                                        carteDeImprumut = listaCarti[i];
                                        break;
                                    }
                                }

                                if(carteDeImprumut && !carteDeImprumut -> getImprumutata())
                                {
                                    carteDeImprumut -> imprumuta();
                                    curata();
                                    cout<<"Ati imprumutat cartea cu succes!"<<endl;
                                    data dataScadenta = imprumut.returnare(durataImprumut);
                                    cout << "Data scadenta pentru returnarea cartii este: " << dataScadenta.zi << "/"<< dataScadenta.luna << "/" << dataScadenta.an << endl;
                                }
                                else
                                    cout<<"Aceasta carte nu poate fi imprumutata momentan."<<endl;

                                apasaEnter();

                                break;
                            }

                            case 2:
                                {
                                    curata();
                                    cout << "Lista de carti imprumutate: " << endl;
                                    bool existaCarteImprumutata = false;

                                    for (int i = 0; i < listaCarti.size(); i++)
                                    {
                                        if (listaCarti[i]->getImprumutata())
                                        {
                                            cout << "ID: " << listaCarti[i]->getId() << " - " << listaCarti[i]->getNumeCarte() << endl;
                                            existaCarteImprumutata = true;
                                        }
                                    }

                                    if (!existaCarteImprumutata)
                                    {
                                        cout << "Nu aveti nicio carte imprumutata momentan." << endl;
                                        cin.ignore();
                                        cin.get();
                                        continue;
                                    }

                                    else
                                    {
                                        cout << "Introduceti ID-ul cartii pe care doriti sa o returnati: ";
                                        int idCarteDeReturnat;
                                        cin >> idCarteDeReturnat;

                                        bool carteGasita = false;
                                        for (int i = 0; i < listaCarti.size(); i++)
                                        {
                                            if (idCarteDeReturnat == listaCarti[i]->getId())
                                            {
                                                listaCarti[i]->returneaza();
                                                cout << "Ati returnat cartea cu succes!" << endl;
                                                carteGasita = true;
                                                break;
                                            }
                                        }

                                        if (!carteGasita)
                                            cout << "Nu exista nicio carte imprumutata cu ID-ul introdus." << endl;
                                    apasaEnter();
                                    break;
                                    }
                              }
                        case 3:
                            {
                                curata();
                                string genPreferat;
                                cout<<"Introduceti genul vostru preferat(Science/Fiction): ";
                                cin>>genPreferat;
                                bool existaCartiGenPreferat = false;
                                for(Carte* carte : listaCarti)
                                {
                                    if(carte -> getGenCarte() == genPreferat)
                                    {
                                        cout<<*carte<<endl;
                                        existaCartiGenPreferat = true;
                                    }
                                }
                                if(existaCartiGenPreferat != true)
                                    cout<<"Nu avem nicio recomandare!\n";

                                apasaEnter();
                                break;
                            }
                        case 4:
                            {
                                ///const auto& is used to avoid making unnecessary copies of the pointers.
                                ///With pointers, there is no danger that you make accidental copies of the data, but there are other issues with omitting the *.
                                sort(listaCarti.begin(), listaCarti.end(), compararePopularitate);

                                /*for(Carte* carte: listaCarti)
                                {cout<<*carte<<"\n"; } */

                                for (const auto* carte : listaCarti)
                                {
                                    cout << *carte << "\n";
                                }

                                apasaEnter();

                                break;
                            }
                        case 5:
                            {
                                curata();
                                optiuneImprumut = 5;
                                cout<<"Se revine la meniul anterior!\n";
                                apasaEnter();
                                break;
                            }
                        default:
                            {
                                comandaDefault();
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
                while((optiuneBibliotecar != 11) && (parolaRet == true))
                {
                    meniuBibliotecar();

                    cin>>optiuneBibliotecar;
                    switch(optiuneBibliotecar)
                    {
                    case 1:
                        {
                                curata();
                                int tipCarte;
                                cout << "Alegeti tipul cartii:\n";
                                cout << "1. Fiction\n";
                                cout << "2. Science\n";
                                cout << "3. Science Fiction\n";
                                cout << "Introduceti optiunea: ";
                                cin >> tipCarte;

                                switch (tipCarte)
                                {
                                case 1:
                                    {
                                        Carte* c = new Fiction();
                                        cin>> *c;
                                        listaCarti.push_back(c);
                                        apasaEnter();
                                        break;
                                    }
                                case 2:
                                    {
                                        Carte* c = new Science();
                                        cin>> *c;
                                        listaCarti.push_back(c);
                                        apasaEnter();
                                        break;
                                    }
                                case 3:
                                    {
                                        Carte* c = new Science_Fiction();
                                        cin>> *c;
                                        listaCarti.push_back(c);
                                        apasaEnter();
                                        break;
                                    }
                                default:
                                    {
                                        comandaDefault();
                                        apasaEnter();
                                        break;
                                    }
                                }

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
                                cout<<*listaCarti[i];
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
                            apasaEnter();
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
                                cout << *listaCarti[i] << endl;

                            cout << "Introduceti ID-ul cartii pe care doriti sa o stergeti: ";
                            int id;
                            cin >> id;

                            for (int i = 0; i < listaCarti.size(); i++)
                            {
                                if (id == listaCarti[i]->getId())
                                {
                                    listaCarti.erase(listaCarti.begin() + i);
                                    cout << "Cartea cu ID-ul " << id << " a fost stearsa cu succes!" << endl;
                                    break;
                                }
                            }
                            apasaEnter();
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
                                {
                                    listaUtilizatori.erase(listaUtilizatori.begin()+i);
                                    cout<<"Utilizatorul a fost sters cu succes!\n";
                                }

                            apasaEnter();
                            break;
                        }
                    case 9:
                        {
                            curata();
                            for(int i = 0; i<listaBibliotecari.size();i++)
                                cout<<listaBibliotecari[i]<<endl;
                            cout<<"Introduceti id-ul bibliotecarului pe care doriti sa il stergeti: ";
                            int id;
                            cin>> id;
                            for(int i = 0; i<listaBibliotecari.size();i++)
                                if(id == listaBibliotecari[i].getId())
                                {
                                    listaBibliotecari.erase(listaBibliotecari.begin()+i);
                                    cout<<"Angajatul a fost sters cu succes!";
                                }

                            apasaEnter();
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
                            optiuneBibliotecar = 11;
                            cout<<"Se revine la meniul anterior.\n";
                            apasaEnter();
                            break;
                        }
                    default:
                        {
                            comandaDefault();
                            break;
                        }
                    }

                }
                optiuneBibliotecar = 0;
                break;
            }

        case 4:
            {
                for (Carte* carte : listaCarti)
                {
                    delete carte;
                }
                listaCarti.clear();
                optiune = 4;
                break;
            }

        default:
            {
               comandaDefault();
                break;
            }

        }
    }
    return 0;
}
