#include <iostream>
#include <string>
#include <limits>
#include <chrono>
#include <windows.h>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include <thread>

using namespace std;

class OptiuneInvalida : public exception{
public:
    const char* what() const throw(){
        return "Optiune invalida!";
    }
};

void pauza(int secunde)
{
    this_thread::sleep_for(chrono::seconds(secunde));
}

void curata()
{
    system("cls");
}

bool parola()
{
    cout<<"Introduceti parola pentru a accesa meniul!\n";
    string parola = "1234";
    string parolaIntrodusa;
    cin>>parolaIntrodusa;

    if(parolaIntrodusa == parola)
    {
        curata();
        cout<<"Autentificarea s-a realizat cu succes!\n";
        cin.ignore();
        cin.get();
        curata();
        return true;
    }
    else
    {
        cout<<"Parola introdusa este gresita! Accesul este restrictionat.";
        cin.ignore();
        cin.get();
        curata();
        return false;
    }
}

class IOInterface
{
public:
    virtual ostream& afisare(ostream& out)const = 0;
    virtual istream& citire(istream& in) = 0;
};
///Clasa abstracta Cont, clasa Bibliotecar si Utilizator vor mosteni din ea
class Cont : public IOInterface
{
protected:
    string nume;
    int varsta;
    char sex;
    const int id;
    static int idContor;
public:
    /// Construct de init
    Cont();
    /// Construct cu toti param
    Cont(string, int, char);
    /// CC
    Cont(const Cont& c);
    /// Op =
    Cont& operator =(const Cont& c);
    ///Op <<
    ostream& afisare(ostream& out)const;
    friend ostream& operator<<(ostream& out, const Cont& c);
    ///Op >>
    istream& citire(istream& in);
    friend istream& operator>>(istream& in, Cont& c);
    virtual void vechime() = 0;
    ///getter
    const int getId() {return this -> id;}
    virtual ~Cont();
};

Cont::Cont():id(idContor++), nume("Anonim"), varsta(0), sex('X') {}

Cont::Cont(string nume, int varsta, char sex):id(idContor++), nume(nume), varsta(varsta), sex(sex) {}

Cont::Cont(const Cont& c):id(idContor++), nume(c.nume), varsta(c.varsta), sex(c.sex) {}

Cont& Cont::operator=(const Cont& c)
{
    if(this != &c)
    {
        this -> nume = c.nume;
        this -> varsta = c.varsta;
        this -> sex = c.sex;
    }
    return *this;
}
Cont:: ~Cont()
{
    if(!this -> nume.empty()) this -> nume.clear();
}

ostream& Cont::afisare(ostream& out) const
{
    out<<"\t Contul cu id: "<<this -> id<<endl;
    out<<"Numele: "<<this -> nume<<endl;
    out<<"Varsta: "<<this -> varsta<<endl;
    out<<"Sexul: "<<this -> sex<<endl;
    return out;
}

ostream& operator<<(ostream& out, const Cont& c)
{
    return c.afisare(out);
}

istream& Cont::citire(istream& in)
{
    cout<<"Introdu nume: "<<endl;
    cin.get();
    getline(in, this -> nume, '\n');
    cout<<endl;

    while(true)
    {
        try
        {
            cout<<"Introdu varsta: "<<endl;
            in>>this -> varsta;

            ///verifica daca operatia a esuat
            if(in.fail())
            {
                throw runtime_error("INVALID! Introduceti un numar!\n");
            }
            else
                break;
        }
        ///prinde exceptia si afiseaza mesajul, ignora caracterele ramase in buffer din input pana la '\n', pentru a ne asigura ca stergem inputul invalid care a creat exceptia
        catch(const runtime_error& e)
        {
            cout<<e.what();
            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while(true)
    {
        try
        {
            cout<<"Introdu genul(M/F): ";
            in>>this -> sex;
            cout<<endl;

            if(in.fail() || (toupper(this -> sex)!= 'M' && toupper(this -> sex) != 'F'))
            {
                throw runtime_error("Genul introdus este invalid. Introduceti 'M' pentru masculin sau 'F' pentru feminin!\n");
            }
            else
            {
                this -> sex = toupper(this -> sex);
                break;
            }

        }

        catch(const runtime_error& e)
        {
            cout<<e.what();
            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return in;
}

istream& operator>>(istream& in, Cont& c)
{
    return c.citire(in);
}

int Cont::idContor = 0;

/// Clasa Bibliotecar, ea mosteneste din clasa Cont
class Bibliotecar : public Cont
{
private:
    double salar;
    int nrAniActivitate;
    int* aniActivitate;

public:
    /// Construct de init
    Bibliotecar() : Cont()
    {
        this -> salar = 0;
        this -> nrAniActivitate = 0;
        this -> aniActivitate = nullptr;
    }
    /// Construct cu toti param
    Bibliotecar(string nume, int varsta, char sex, double salar, int nrAniActivitate, int* aniActivitate) : Cont(nume, varsta, sex)
    {
        this -> salar = salar;
        this -> nrAniActivitate = nrAniActivitate;
        this -> aniActivitate = new int[this -> nrAniActivitate];
        for(int i = 0; i< this -> nrAniActivitate; i++)
            this -> aniActivitate[i] = aniActivitate[i];
    }

    /// CC
    Bibliotecar(const Bibliotecar& b) : Cont(b)
    {
        this -> salar = b.salar;
        this -> nrAniActivitate = b.nrAniActivitate;
        this -> aniActivitate = new int[this -> nrAniActivitate];
        for(int i = 0; i< b.nrAniActivitate; i++)
            this -> aniActivitate[i] = b.aniActivitate[i];
    }

    /// Operatorul egal
    Bibliotecar& operator =(const Bibliotecar& b)
    {
        if(this != &b)
        {
            Cont::operator =(b);
            this -> salar = b.salar;
            this -> nrAniActivitate = b.nrAniActivitate;
            this -> aniActivitate = new int[this -> nrAniActivitate];
            for(int i = 0; i< nrAniActivitate; i++)
                this -> aniActivitate[i] = aniActivitate[i];
        }
        return *this;
    }

    /// Op <<
    ostream& afisare(ostream& out)const
    {
        Cont::afisare(out);
        out<<"Salariul angajatului: "<< this -> salar<<endl;
        return out;
    }

    /// Op >>
    istream& citire(istream& in)
    {
        Cont::citire(in);
        while(true)
        {
            try
            {
                cout<<"Dati salariul bibliotecarului: "<<endl;
                in>> this -> salar;

                if(in.fail())
                    throw runtime_error("INVALID! Introduceti un numar!\n");
                else
                    break;
            }

            catch(const runtime_error& e)
            {
                cout<<e.what();
                in.clear();
                in.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        return in;
    }

    /// functia mea
    void vechime() override
    {
        int maxim = aniActivitate[0];
        int minim = aniActivitate[0];

        for(int i = 0; i< this -> nrAniActivitate; i++)
        {
            if(maxim < aniActivitate[i])
                maxim = aniActivitate[i];
            if(minim > aniActivitate[i])
                minim = aniActivitate[i];
        }
        cout<<"Experienta in domeniu a bibliotecarului "<<this -> nume<<" este de "<< maxim - minim+1<<" ani.";
    }

    /// Destructor
    ~Bibliotecar()
    {
        if(this -> aniActivitate != nullptr)
        {
            delete[] this -> aniActivitate;
            this -> aniActivitate = nullptr;
        }
    }
};

///Clasa Utilizator, ea mosteneste din clasa Cont
class Utilizator : public Cont
{
private:
    string genPreferat;
    int aniCardMembru;
    int timestampCreareCont;

public:
    /// Construct de init
    Utilizator() : Cont()
    {
        this -> genPreferat = "Anonim";
        this -> aniCardMembru = 0;
        this -> timestampCreareCont = time(NULL);
    }

    ///Construct cu toti param
    Utilizator(string nume, int varsta, char sex, string genPreferat, int aniCardMembru, int timestampCreareCont) : Cont(nume, varsta, sex)
    {
        this -> genPreferat = genPreferat;
        this -> aniCardMembru = aniCardMembru;
        this -> timestampCreareCont = timestampCreareCont;
    }

    /// CC
    Utilizator(const Utilizator& u) : Cont(u)
    {
        this -> genPreferat = u.genPreferat;
        this -> aniCardMembru = u.aniCardMembru;
        this -> timestampCreareCont = u.timestampCreareCont;
    }

    /// Op =
    Utilizator& operator =(const Utilizator& u)
    {
        if(this != &u)
        {
            Cont::operator=(u);
            this -> genPreferat = u.genPreferat;
            this -> aniCardMembru = u.aniCardMembru;
            this -> timestampCreareCont = u.timestampCreareCont;
        }
        return *this;
    }

    /// Op <<
    ostream& afisare(ostream& out)const
    {
        Cont::afisare(out);
        out<<"Genul preferat de carti este: "<<this -> genPreferat<<endl;
        return out;
    }

    /// Op >>
    istream& citire(istream& in)
    {
        Cont::citire(in);
        cout<<"Introduceti genul preferat de carti: ";
        cin.ignore();
        getline(in, this -> genPreferat, '\n');
        cout<<endl;
        return in;
    }

    ///getter pt functia mea
    int getTimestampCreareCont() const{return this -> timestampCreareCont;}

    /// functia mea
    void vechime()override
    {
        int timestampInregistrare = getTimestampCreareCont();
        int diferentaTimp = time(nullptr) - timestampInregistrare;

        int minute = diferentaTimp / 60;
        int secunde = diferentaTimp % 60;

        cout << "Vechimea contului este de " << minute << " minute si " << secunde << " secunde." <<endl;
    }


    ///setteri ca sa pot actualiza contul meu
    void setNumeUtilizator(string nume) {this -> nume = nume;}
    void setVarsta(int varsta) {this -> varsta= varsta;}
    void setSex(char sex) {this -> sex = sex;}
    void setGenPreferat(string genPreferat) {this-> genPreferat = genPreferat;}


    ~Utilizator() {}

};

///Clasa Carte, vor mosteni clasa Science si clasa Fiction din ea
class Carte : public IOInterface
{
protected:
    string autor;
    string titlu;
    string genCarte;
    int rating;
    bool esteImprumutata;
    int popularitate;
    const int id;
    static int idContor;
public:
    ///Construct de init
    Carte();
    ///Construct cu toti param
    Carte(string, string, string, int, bool, int);
    /// CC
    Carte(const Carte& c);
    ///Op =
    Carte& operator =(const Carte& c);

    ///Op <<
    ostream& afisare(ostream& out)const;
    friend ostream& operator<<(ostream& out, const Carte& c);

    /// Op >>
    istream& citire(istream& in);
    friend istream& operator>>(istream& in, Carte& c);

    ///functia mea
    virtual string popularitateaCartii() = 0;
    virtual void imprumuta() = 0;
    virtual void returneaza() = 0;

    ///getteri
    const int getId() {return this ->id;}
    string getAutor() const{return this -> autor;}
    string getTitlu() const{return this -> titlu;}
    string getGenCarte() const{return this -> genCarte;}
    int getRating() const{return this -> rating;}
    bool getEsteImprumutata() const{return this -> esteImprumutata;}
    int getPopularitate() const{return this -> popularitate;}

    ///Destructor
    virtual ~Carte() {};

};
///Construct de init
Carte::Carte():id(idContor++), autor("Anonim"), titlu("Anonim"), genCarte("Anonim"), rating(0), esteImprumutata(false), popularitate(0) {}
///Construct cu toti param
Carte::Carte(string autor, string titlu, string genCarte, int rating, bool esteImprumutata, int popularitate):id(idContor++),
    autor(autor), titlu(titlu), genCarte(genCarte), rating(rating), esteImprumutata(esteImprumutata), popularitate(popularitate) {}
/// CC
Carte::Carte(const Carte& c):id(idContor++), autor(c.autor), titlu(c.titlu), genCarte(c.genCarte), rating(c.rating), esteImprumutata(c.esteImprumutata), popularitate(c.popularitate) {}
///Op =
Carte& Carte::operator =(const Carte& c)
{
    if(this != &c)
    {
        this -> autor = c.autor;
        this -> titlu = c.titlu;
        this -> genCarte = genCarte;
        this -> rating = rating;
        this -> esteImprumutata = c.esteImprumutata;
        this -> popularitate;
    }
    return *this;
}

ostream& Carte::afisare(ostream& out)const
{
    out<<"\tDatele despre cartea cu ID-ul:"<< this-> id<<endl;
    out<<"Numele autorului este: "<<this ->autor<<endl;
    out<<"Titlul cartii este: "<<this -> titlu<<endl;
    out<<"Genul cartii este: "<<this -> genCarte<<endl;
    out<<"Rating-ul cartii este: "<<this -> rating<<endl;
    out<<"Este cartea valabila?: "<<(this -> esteImprumutata ? "Nu" : "Da")<<endl;
    if(this -> esteImprumutata != true)
        out<<"Cartea poate fi imprumutata"<<endl;
    else
        out<<"Cartea nu poate fi imprumutata"<<endl;
    out<<"Popularitatea cartii: "<<this -> popularitate<<endl;
    return out;
}
ostream& operator<<(ostream& out, const Carte& c)
{
    return c.afisare(out);
}

istream& Carte::citire(istream& in)
{
    cout<<"Introduceti numele autorului: ";
    cin.ignore();
    getline(in, this -> autor, '\n');
    cout<<endl;

    cout<<"Introduceti titlul cartii: ";
    getline(in, this -> titlu, '\n');
    cout<<endl;

    cout<<"Introduceti genul cartii: ";
    getline(in, this ->genCarte, '\n');
    cout<<endl;

    while(true)
    {
        try
        {
            cout<<"Introduceti rating-ul cartii ";
            in>>this -> rating;
            cout<<endl;

            if(in.fail())
            {
                throw runtime_error("INVALID! Introduceti un numar!\n");
            }
            else
                break;
        }

        catch(const runtime_error& e)
        {
            cout<<e.what();
            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while(true)
    {
        try
        {
            cout<<"Introduceti un numar intre 1-3 pentru o carte mai putin populara, 4-6 pentru o carte populara si 7-9 pentru o carte foarte populara ";
            in>>this -> popularitate;
            cout<<endl;

            if(in.fail())
                throw runtime_error("INVALID! Introduceti un numar!\n");
            else
                break;
        }

        catch(const runtime_error& e)
        {
            cout<<e.what();
            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return in;
}

istream& operator>>(istream& in, Carte& c)
{
    return c.citire(in);
}

int Carte::idContor = 0;

class Science : virtual public Carte
{
protected:
    string domeniu;
public:
    ///Construct de init
    Science() : Carte(), domeniu("Anonim") {}
    ///Construct cu toti param
    Science(string autor, string titlu, string genCarte, int rating, bool esteImprumutata, int popularitate, string domeniu) :
         Carte(autor, titlu, genCarte, rating, esteImprumutata, popularitate), domeniu(domeniu) {}
    /// CC
    Science(const Science& s) : Carte(s), domeniu(s.domeniu) {}
    ///Op =
    Science& operator =(const Science& s)
    {
        if(this != &s)
        {
            Carte::operator =(s);
            this -> domeniu = s.domeniu;
        }
        return *this;
    }
    ///Op <<
    ostream& afisare(ostream& out) const
    {
        Carte::afisare(out);
        out<<"Domeniul studiat in carte este: "<<this -> domeniu<<endl;;
        return out;
    }

    ///Op >>
    istream& citire(istream& in)
    {
        Carte::citire(in);
        cout<<"Introduceti domeniul studiat in carte: ";
        in.ignore();
        getline(in, this -> domeniu, '\n');
        cout<<endl;
        return in;
    }

    ///getter
    string getDomeniu() const{return this -> domeniu;}

    ///functia mea rescrisa
    string popularitateaCartii()override
    {
        if(this -> popularitate >= 1 && this -> popularitate <= 3)
            return "Cartea este mai putin populara\n";
        else if (this -> popularitate >= 4 && this -> popularitate <= 6)
            return "Cartea este populara\n";
        else if(this -> popularitate >= 7 && this -> popularitate <= 9)
            return "Cartea este foarte populara\n";
        else
            return "Numar invalid. Setarea popularitatii nu s-a putut realiza.\n";

    }
    void imprumuta()
    {
        if(esteImprumutata != true)
            esteImprumutata = true;
        else
        {
            cout<<"Aceasta carte este deja imprumutata"<<endl;
        }
    }

    void returneaza()
    {
        esteImprumutata = false;
    }


    virtual ~Science() {}
};

class Fiction : virtual public Carte
{
protected:
    int varstaRec;
public:
    ///Construct de init
    Fiction() : Carte(), varstaRec(0) {}
    ///Construct cu toti param
    Fiction(string autor, string titlu, string genCarte, int rating, bool esteImprumutata, int popularitate, int varstaRec) :
            Carte(autor, titlu, genCarte, rating, esteImprumutata, popularitate), varstaRec(varstaRec) {}
    /// CC
    Fiction(const Fiction& f) : Carte(f)
    {
        this -> varstaRec = f.varstaRec;
    }
    ///Op =
    Fiction& operator =(const Fiction& f)
    {
        if(this != &f)
        {
            this -> varstaRec = f.varstaRec;
        }
        return *this;
    }

    ///Op <<
    ostream& afisare(ostream& out) const
    {
        Carte::afisare(out);
        out<<"Varsta recomandata pentru a citi cartea este de: "<<this -> varstaRec<<"+ ani."<<endl;
        return out;
    }

    ///Op >>
    istream& citire(istream& in)
    {
        Carte::citire(in);
        while(true)
        {
            try
            {
                cout<<"Care este varsta recomandata pentru a citi cartea: ";
                in>>this -> varstaRec;

                if(in.fail())
                    throw runtime_error("INVALID! Introduceti un numar!\n");
                else
                    break;
            }

            catch(const runtime_error& e)
            {
                cout<<e.what();
                in.clear();
                in.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        return in;
    }

    ///getter
    int getVarstaRec() const{return this -> varstaRec;}

    ///functia mostenita
    string popularitateaCartii()override
    {
        if(this -> popularitate >= 1 && this -> popularitate <= 3)
            return "Cartea este mai putin populara\n";
        else if (this -> popularitate >= 4 && this -> popularitate <= 6)
            return "Cartea este populara\n";
        else if(this -> popularitate >= 7 && this -> popularitate <= 9)
            return "Cartea este foarte populara\n";
        else
            return "Numar invalid. Setarea popularitatii nu s-a putut realiza.\n";

    }

    void imprumuta()
    {
        if(esteImprumutata != true)
            esteImprumutata = true;
        else
        {
            cout<<"Aceasta carte este deja imprumutata"<<endl;
        }
    }

    void returneaza()
    {
        esteImprumutata = false;
    }

    ///Destructor
    virtual ~Fiction() {}
};

class Sf : public Science, public Fiction
{
protected:
    bool film;
public:
    ///Construct de init
    Sf() : Carte(), Science(), Fiction(), film(false) {}
    ///Construct cu toti param
    Sf(string autor, string titlu, string genCarte, int rating, bool esteImprumutata, int popularitate, string domeniu, int varstaRec, bool film) :
            Carte(autor, titlu, genCarte, rating, esteImprumutata, popularitate),
            Science(autor, titlu, genCarte, rating, esteImprumutata, popularitate, domeniu),
            Fiction(autor, titlu, genCarte, rating, esteImprumutata, popularitate, varstaRec), film(film) {}
    /// CC
    Sf(const Sf& sf) : Carte(sf), Science(sf), Fiction(sf), film(sf.film) {}
    ///Op =
    Sf& operator =(const Sf& sf)
    {
        if(this != &sf)
        {
            Carte::operator=(sf);
            this -> film = film;
        }
        return *this;
    }

    ///Op <<
    ostream& afisare(ostream& out) const
    {
        Carte::afisare(out);
        if(this -> film != true)
            out<<"Nu este film dupa carte!"<<endl;
        else
            out<<"Este film dupa carte!"<<endl;
        return out;
    }

    ///Op >>
    istream& citire(istream& in)
    {
        Carte::citire(in);
    }

    ///getter
    bool getFilm() const{return this -> film;}

    ///functia rescrisa
    string popularitateaCartii()override
    {
        string popular = Fiction::popularitateaCartii();

        if(film)
            return "Cartea este foarte populara si are un film dupa ea!\n";
        else
            return popular;
    }

    void imprumuta()
    {
        if(esteImprumutata != true)
            esteImprumutata = true;
        else
        {
            cout<<"Aceasta carte este deja imprumutata"<<endl;
        }
    }

    void returneaza()
    {
        esteImprumutata = false;
    }

    ///Destructor
    virtual ~Sf() {}
};

void meniu()
{
    cout<<"1. Pagina Principala."<<endl;
    cout<<"2. Meniu Admin."<<endl;
    cout<<"3. Iesire."<<endl;
}

void meniuPaginaPrincipala()
{
    cout<<"--------------- Pagina Principala ---------------"<<endl<<endl;
    cout<<"1. Contul meu."<<endl;
    cout<<"2. Informatii carti."<<endl;
    cout<<"3. Imprumut carti."<<endl;
    cout<<"4. Inapoi."<<endl;
}

void meniuCont()
{
    cout<<"--------------- Contul meu ---------------"<<endl<<endl;
    cout<<"1. Creare cont."<<endl;
    cout<<"2. Vizualizare cont."<<endl;
    cout<<"3. Actualizare cont."<<endl;
    cout<<"4. Cartile mele."<<endl;
    cout<<"5. Stergere cont."<<endl;
    cout<<"6. Inapoi."<<endl;
}

void meniuCarti()
{
    cout<<"--------------- Cartile bibliotecii ---------------"<<endl<<endl;
    cout<<"1. Vezi cartile din biblioteca."<<endl;
    cout<<"2. Vezi cartile stiintifice."<<endl;
    cout<<"3. Vezi cartile fiction."<<endl;
    cout<<"4. Vezi cartile science-fiction."<<endl;
    cout<<"5. Inapoi."<<endl;
}

void meniuImprumut()
{
    cout<<"--------------- Imprumut carti ---------------"<<endl<<endl;
    cout<<"1. Imprumuta carti."<<endl;
    cout<<"2. Returneaza carti."<<endl;
    cout<<"3. Inapoi."<<endl;
}

void meniuAdmin()
{
    cout<<"--------------- Meniu Admin ---------------"<<endl<<endl;
    cout<<"1.  Adauga carte.\n";
    cout<<"2.  Adauga utilizator.\n";
    cout<<"3.  Adauga bibliotecar.\n";
    cout<<"4.  Vezi lista de carti.\n";
    cout<<"5.  Vezi lista de cititori.\n";
    cout<<"6.  Vezi lista de bibliotecari.\n";
    cout<<"7.  Sterge carte.\n";
    cout<<"8.  Sterge utilizator.\n";
    cout<<"9.  Sterge bibliotecar.\n";
    cout<<"10. Import carti stiintifice.\n";
    cout<<"11. Import carti fiction\n";
    cout<<"12. Import carti sf.\n";
    cout<<"13. Export carti.\n";
    cout<<"14. Inapoi\n";
}

void apasaEnter()
{
    cout<<"Apasati Enter pentru a continua\n";
    cin.ignore();
    cin.get(); // Asteapta pana cand utilizatorul apasa Enter
    curata();
}

void comandaDefault()
{
    cout<<"Comanda incorecta! Va rugam incercati din nou.\n";
    cin.ignore();
    cin.get();
    curata();
}

void asteaptaImportExport() {
    cout << "Va rugam asteptati cat se efectueaza transferul";
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        cout.flush(); //ma asigur ca punctul e afisat si ca nu este tinut in buffer
        this_thread::sleep_for(chrono::seconds(2));
    }
    cout << endl;
}

vector<Carte*> listaCarti(14);
void importCartiScience(const string& filename)
{
    ifstream file(filename);
    if(!file.is_open())
    {
        cerr<<"A intervenit o eroare!"<<endl;
        return;
    }

    string line;
    while(getline(file, line))
    {
        stringstream ss(line);
        string autor;
        string titlu;
        string genCarte;
        int rating;
        bool esteImprumutata;
        int popularitate;
        string domeniu;

        getline(ss, autor, ',');
        getline(ss, titlu, ',');
        getline(ss, genCarte, ',');
        ss >> rating;
        ss.ignore(); ///sa ignore , dupa rating
        ss>>boolalpha >> esteImprumutata; /// sa imi citeasca bine valoarea booleana
        ss.ignore();
        ss >> popularitate;
        ss.ignore();
        getline(ss >> ws, domeniu); ///ws consuma spatiile albe

        Carte* carteScience = new Science(autor, titlu, genCarte, rating, esteImprumutata, popularitate, domeniu);
        listaCarti.push_back(carteScience);
    }

    file.close();
}

void importCartiFiction(const string& filename)
{
    ifstream file(filename);
    if(!file.is_open())
    {
        cerr<<"A intervenit o eroare!"<<endl;
        return;
    }

    string line;
    while(getline(file, line))
    {
        stringstream ss(line);
        string autor;
        string titlu;
        string genCarte;
        int rating;
        bool esteImprumutata;
        int popularitate;
        int varstaRec;

        getline(ss, autor, ',');
        getline(ss, titlu, ',');
        getline(ss, genCarte, ',');
        ss >> rating;
        ss.ignore(); ///sa ignore , dupa rating
        ss>>boolalpha >> esteImprumutata; /// sa imi citeasca bine valoarea booleana
        ss.ignore();
        ss >> popularitate;
        ss.ignore();
        ss >> varstaRec;

        Carte* carteFiction = new Fiction(autor, titlu, genCarte, rating, esteImprumutata, popularitate, varstaRec);
        listaCarti.push_back(carteFiction);
    }

    file.close();
}

void importCartiSF(const string& filename)
{
    ifstream file(filename);
    if(!file.is_open())
    {
        cerr<<"A intervenit o eroare!"<<endl;
        return;
    }

    string line;
    while(getline(file, line))
    {
        stringstream ss(line);
        string autor;
        string titlu;
        string genCarte;
        int rating;
        bool esteImprumutata;
        int popularitate;
        string domeniu;
        int varstaRec;
        bool film;

        getline(ss, autor, ',');
        getline(ss, titlu, ',');
        getline(ss, genCarte, ',');
        ss >> rating;
        ss.ignore(); ///sa ignore , dupa rating
        ss>>boolalpha >> esteImprumutata; /// sa imi citeasca bine valoarea booleana
        ss.ignore();
        ss >> popularitate;
        ss.ignore();
        getline(ss >> ws, domeniu); ///ws consuma spatiile albe
        ss.ignore();
        ss >> varstaRec;
        ss.ignore();
        ss >> boolalpha >> film;

        Carte* carteSF = new Sf(autor, titlu, genCarte, rating, esteImprumutata, popularitate, domeniu, varstaRec, film);
        listaCarti.push_back(carteSF);
    }

    file.close();
}

void exportCarti(const string& filename, Carte* carteExport)
{
    ofstream file(filename, ios::app);  // Deschide fisierul in modul de adaugare pentru a pastra continutul existent, ios::app e mod append
    if (!file.is_open())
    {
        cerr << "A intervenit o eroare la deschiderea fisierului!" << endl;
        return;
    }

    Science* scienceBook = dynamic_cast<Science*>(carteExport);
    Fiction* fictionBook = dynamic_cast<Fiction*>(carteExport);
    Sf* sfBook = dynamic_cast<Sf*>(carteExport);
    if (scienceBook)
    {
        file << scienceBook->getAutor() << ","
             << scienceBook->getTitlu() << ","
             << scienceBook->getGenCarte() << ","
             << scienceBook->getRating() << ","
             << boolalpha << scienceBook->getEsteImprumutata() << ","
             << scienceBook->getPopularitate() << ","
             << scienceBook->getDomeniu() << endl;
    }


    else if(fictionBook)
    {
        file << fictionBook->getAutor() << ","
                 << fictionBook->getTitlu() << ","
                 << fictionBook->getGenCarte() << ","
                 << fictionBook->getRating() << ","
                 << boolalpha << fictionBook->getEsteImprumutata() << ","
                 << fictionBook->getPopularitate() << ","
                 << fictionBook->getVarstaRec() << endl;
    }

    else if(sfBook)
    {
        file << sfBook -> getAutor() << ","
                 << sfBook -> getTitlu() << ","
                 << sfBook -> getGenCarte() << ","
                 << sfBook -> getRating() << ","
                 << boolalpha << sfBook->getEsteImprumutata() << ","
                 << sfBook -> getPopularitate() << ","
                 << sfBook -> getDomeniu() << ","
                 <<sfBook -> getVarstaRec() << ","
                 <<boolalpha <<sfBook -> getFilm() << endl;
    }

    file.close();
}

class Meniu
{
private:
    ///Constructorul este private, astfel impiedica crearea de instante ale clasei din exterior
    Meniu() {}

public:
    ///Sterg CC si Op = ca sa ma asigur ca nu am din greseala copii ale clasei mele singleton
    Meniu(const Meniu&) = delete;
    void operator=(Meniu const&) = delete;

    static Meniu& getInstance()
    {
        static Meniu instance;
        return instance;
    }

    void startMeniu();
};

void Meniu::startMeniu()
{
    vector<Carte*> listaCartiImprumutate;


    Carte* S1 = new Science("Carl Sagan", "Cosmos", "Science", 5, false, 8, "Astronomie");
    Carte* S2 = new Science("Richard Dawkins", "The Selfish Gene", "Science", 4, false, 7, "Biologie");
    Carte* S3 = new Science("Stephen Hawking", "A Brief History of Time", "Science", 5, false, 9, "Fizica");
    Carte* S4 = new Science("Neil deGrasse Tyson", "Astrophysics for Young People in a Hurry", "Science", 4, false, 6, "Astrofizica");

    Carte* F1 = new Fiction("Jane Austen", "Pride and Prejudice", "Fiction", 5, false, 8, 14);
    Carte* F2 = new Fiction("George Orwell", "1984", "Fiction", 4, false, 7, 16);
    Carte* F3 = new Fiction("Harper Lee", "To Kill a Mockingbird", "Fiction", 5, false, 9, 12);
    Carte* F4 = new Fiction("J.K. Rowling", "Harry Potter and the Sorcerer's Stone", "Fiction", 4, false, 6, 15);
    Carte* F5 = new Fiction("Mark Twain", "The Adventures of Tom Sawyer", "Fiction", 4, false, 7, 13);

    Carte* Sf1 = new Sf("Isaac Asimov", "Fundatia", "Science Fiction", 5, false, 8, "Space Opera", 14, true);
    Carte* Sf2 = new Sf("Philip K. Dick", "Blade Runner", "Science Fiction", 4, false, 7, "Cyberpunk", 16, true);
    Carte* Sf3 = new Sf("Arthur C. Clarke", "2001: A Space Odyssey", "Science Fiction", 5, false, 9, "Hard Science Fiction", 12, true);
    Carte* Sf4 = new Sf("Ursula K. Le Guin", "The Left Hand of Darkness", "Science Fiction", 4, false, 6, "Social Science Fiction", 15, false);
    Carte* Sf5 = new Sf("H.G. Wells", "The War of the Worlds", "Science Fiction", 4, false, 7, "Invasion Fiction", 13, true);

    listaCarti[0] = S1;
    listaCarti[1] = S2;
    listaCarti[2] = S3;
    listaCarti[3] = S4;

    listaCarti[4] = F1;
    listaCarti[5] = F2;
    listaCarti[6] = F3;
    listaCarti[7] = F4;
    listaCarti[8] = F5;

    listaCarti[9] = Sf1;
    listaCarti[10] = Sf2;
    listaCarti[11] = Sf3;
    listaCarti[12] = Sf4;
    listaCarti[13] = Sf5;

    vector<Cont*> listaBibliotecari(3);
    int v0[]= {2000, 2001, 2003, 2005, 2010, 2011, 2015, 2017, 2020, 2021, 2023};
    Cont* Bibliotecar1 = new Bibliotecar("Adrian Cristescu", 34, 'M', 7300.0, 11, v0);
    listaBibliotecari[0] = Bibliotecar1;

    int v1[]= { 2011, 2015, 2017, 2020, 2021, 2022, 2023};
    Cont* Bibliotecar2 = new Bibliotecar("Ion Dumitrescu", 27, 'M', 5700.50, 7, v1);
    listaBibliotecari[1] = Bibliotecar2;

    int v2[]= {2017, 2020, 2021, 2023};
    Cont* Bibliotecar3 = new Bibliotecar("Gabriela Marin", 40, 'F', 3245.78, 4, v2);
    listaBibliotecari[2] = Bibliotecar3;

    vector<Utilizator> listaUtilizatori;
    cout<<"Bine ati venit! Alegeti o optiune pentru a incepe!"<<endl<<endl;
    int comandaMeniuPrincipal = 0;
    bool parolaRet = 0;
    while(comandaMeniuPrincipal != 3)
    {
        meniu();
        cout<<"Alegeti optiunea: ";
        cin>>comandaMeniuPrincipal;

        switch(comandaMeniuPrincipal)
        {
        case 1:
            {
                curata();
                int comandaPaginaPrincipala = 0;
                while(comandaPaginaPrincipala != 4)
                {
                    try
                    {
                        meniuPaginaPrincipala();
                        cout<<"Alegeti optiunea: ";
                        cin>>comandaPaginaPrincipala;
                        if(cin.fail())
                        {
                            throw invalid_argument("Input invalid! Introdu o comanda valida!\n");
                        }
                    }

                    catch(const invalid_argument& e)
                    {
                        cout<<e.what();
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    }

                    switch(comandaPaginaPrincipala)
                    {
                    case 1:
                        {
                            curata();
                            int comandaCont = 0;
                            while(comandaCont != 6)
                            {
                                try
                                {
                                    meniuCont();
                                    cout<<"Alegeti optiunea: ";
                                    cin>>comandaCont;
                                    if(cin.fail())
                                    {
                                        throw invalid_argument("\nInput invalid! Introdu o comanda valida!\n");
                                    }
                                }

                                catch(const invalid_argument& e)
                                {
                                    cout<<e.what();
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }

                                switch(comandaCont)
                                {
                                case 1:
                                    {
                                        curata();
                                        if(listaUtilizatori.empty())
                                        {
                                             Utilizator u;
                                            cin>>u;
                                            listaUtilizatori.push_back(u);
                                        }

                                        else
                                        {
                                            cout<<"Deja exista un cont creat? Daca doriti sa creati unul nou contul vechi va fi sters!\n";
                                            cout << "Doriti sa continuati? (da/nu): ";
                                            string dorinta;
                                            cin>>dorinta;
                                            if(dorinta == "da")
                                            {
                                                listaUtilizatori.clear(); // Clear the existing user list
                                                Utilizator u;
                                                cin >> u;
                                                listaUtilizatori.push_back(u);
                                                cout << "Cont creat cu succes!\n";
                                            }

                                            else
                                            {
                                                 cout << "Crearea contului a fost anulata.\n";
                                                 cin.ignore();
                                                 cin.get();
                                            }

                                        }

                                        curata();
                                        break;
                                    }
                                case 2:
                                    {
                                        curata();
                                        if(listaUtilizatori.size() != 0)
                                        {
                                            Utilizator& u = listaUtilizatori.back();
                                            cout<<u;

                                            u.vechime();
                                        }

                                        else
                                        {
                                            cout<<"Creati un cont pentru a va putea vedea datele!\n";
                                            cin.ignore();
                                            cin.get();
                                            curata();
                                        }
                                        cin.ignore();
                                        cin.get();
                                        curata();
                                        break;
                                    }
                                case 3:
                                   {
                                       curata();
                                       if(listaUtilizatori.size() != 0)
                                       {
                                           int comandaActualizare = 0;
                                           while(comandaActualizare != 5)
                                           {
                                                cout << "Selectati ce doriti sa actualizati:" << endl;
                                                cout << "1. Nume" << endl;
                                                cout << "2. Varsta" << endl;
                                                cout << "3. Sex" << endl;
                                                cout << "4. Gen Preferat" << endl;
                                                cout << "5. Confirma actualizarea" << endl;
                                                cin>>comandaActualizare;

                                                switch(comandaActualizare)
                                                {
                                                case 1:
                                                    {
                                                        curata();
                                                        string numeNou;
                                                        cout << "Introduceti noul nume: ";
                                                        cin >> numeNou;
                                                        listaUtilizatori.back().setNumeUtilizator(numeNou);
                                                        cin.ignore();
                                                        cin.get();
                                                        curata();
                                                        break;
                                                    }
                                                case 2:
                                                    {
                                                        curata();
                                                        int varstaNoua;
                                                        cout << "Introduceti noua varsta: ";
                                                        cin >> varstaNoua;
                                                        listaUtilizatori.back().setVarsta(varstaNoua);
                                                        cin.ignore();
                                                        cin.get();
                                                        curata();
                                                        break;
                                                    }
                                                case 3:
                                                    {
                                                        curata();
                                                        try
                                                        {
                                                            char sexNou;
                                                            cout<<"Introdu genul(M/F): ";
                                                            cin>>sexNou;

                                                            if(cin.fail() || (toupper(sexNou)!= 'M' && toupper(sexNou) != 'F'))
                                                            {
                                                                throw runtime_error("Genul introdus este invalid. Introduceti 'M' pentru masculin sau 'F' pentru feminin!\n");
                                                            }
                                                            else
                                                            {
                                                                 listaUtilizatori.back().setSex(toupper(sexNou));
                                                            }
                                                                break;
                                                        }

                                                        catch(const runtime_error& e)
                                                        {
                                                            cout<<e.what();
                                                            cin.clear();
                                                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                                        }
                                                        cin.ignore();
                                                        cin.get();
                                                        curata();
                                                        break;
                                                    }
                                                case 4:
                                                    {
                                                        curata();
                                                        string nouGenPreferat;
                                                        cout << "Introduceti noul gen preferat: ";
                                                        cin >> nouGenPreferat;
                                                        listaUtilizatori.back().setGenPreferat(nouGenPreferat);
                                                        cin.ignore();
                                                        cin.get();
                                                        curata();
                                                        break;
                                                    }
                                                case 5:
                                                    {
                                                        curata();
                                                        cout << "Actualizarile au fost realizate cu succes!";
                                                        cin.ignore();
                                                        cin.get();
                                                        curata();
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

                                       else
                                       {
                                            cout<<"Creati un cont pentru a putea accesa meniul!\n";
                                            cin.ignore();
                                            cin.get();
                                            curata();
                                       }

                                       break;
                                   }
                                case 4:
                                    {
                                        curata();
                                        if(listaUtilizatori.size() != 0)
                                        {
                                            if(listaCartiImprumutate.size()!= 0)
                                            {
                                                for(int i =0; i<listaCartiImprumutate.size();i++)
                                                {
                                                    cout<<*listaCartiImprumutate[i];
                                                }
                                            }
                                            else
                                            {
                                                cout<<"Nu aveti carti imprumutate!";
                                                cin.ignore();
                                                cin.get();
                                                curata();
                                            }

                                        }
                                        else
                                        {
                                            cout<<"Creati un cont pentru a putea accesa meniul!\n";
                                            cin.ignore();
                                            cin.get();
                                            curata();
                                        }
                                        cin.ignore();
                                        cin.get();
                                        curata();

                                        break;
                                    }
                                case 5:
                                    {
                                        curata();
                                        string raspuns;
                                        cout<<"Doriti sa stergeti contul dvs? (da/nu) ";
                                        cin>>raspuns;

                                        if(raspuns == "da" && !listaUtilizatori.empty())
                                        {
                                            cout<<"Sunteti sigur? ";
                                            cin>>raspuns;

                                            if(raspuns == "da")
                                            {
                                                listaUtilizatori.erase(listaUtilizatori.end()-1);
                                                cout<<"Contul a fost sters cu succes!";
                                            }
                                            else
                                                cout<<"Stergerea contului a fost anulata.";
                                        }
                                        else
                                            cout<<"Stergerea contului a fost anulata sau nu exista conturi de sters.\n";
                                            cin.ignore();
                                            cin.get();
                                            curata();
                                        break;
                                    }
                                case 6:
                                    {
                                        curata();
                                        comandaCont = 6;
                                        cout<<"Se revine la meniul anterior!\n";
                                        cin.ignore();
                                        cin.get();
                                        curata();
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
                            int comandaCarti = 0;
                            while(comandaCarti != 5)
                            {
                                try
                                {
                                    meniuCarti();
                                    cout<<"Alegeti optiunea: ";
                                    cin>>comandaCarti;
                                    if(cin.fail())
                                    {
                                        throw invalid_argument("\nInput invalid! Introdu o comanda valida!\n");
                                    }
                                }

                                catch(const invalid_argument& e)
                                {
                                    cout<<e.what();
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }

                                switch(comandaCarti)
                                {
                                case 1:
                                    {
                                        curata();
                                        for(int i = 0; i<listaCarti.size(); i++)
                                        {
                                            cout<<*listaCarti[i]<<endl;
                                        }
                                        cin.ignore();
                                        cin.get();
                                        curata();
                                        break;
                                    }
                                case 2:
                                    {
                                        curata();
                                        try
                                        {
                                            bool carteGasita;

                                            for(Carte* carte: listaCarti)
                                            {
                                                Science* scienceBook = dynamic_cast<Science*>(carte);

                                                if(scienceBook && !dynamic_cast<Sf*>(carte))
                                                {
                                                    carteGasita = true;
                                                    cout<<*scienceBook<<endl;
                                                }
                                            }
                                        if(!carteGasita)
                                            throw runtime_error("Nu s-au găsit cărți științifice în lista de cărți.");


                                        }

                                        catch(const runtime_error& e)
                                        {
                                            cout<<e.what()<<endl;
                                        }
                                        cin.ignore();
                                        cin.get();
                                        curata();
                                        break;
                                    }
                                case 3:
                                    {
                                        curata();
                                        try
                                        {
                                            bool carteGasita;

                                            for(Carte* carte: listaCarti)
                                            {
                                                Fiction* fictionBook = dynamic_cast<Fiction*>(carte);

                                                if(fictionBook && !dynamic_cast<Sf*>(carte))
                                                {
                                                    carteGasita = true;
                                                    cout<<*fictionBook<<endl;
                                                }
                                            }
                                        if(!carteGasita)
                                            throw runtime_error("Nu s-au găsit cărți fiction în lista de cărți.");


                                        }

                                        catch(const exception& e)
                                        {
                                            cout<<e.what()<<endl;
                                        }
                                        cin.ignore();
                                        cin.get();
                                        curata();
                                        break;
                                    }
                                case 4:
                                    {
                                        curata();
                                        try
                                        {
                                            bool carteGasita;

                                            for(Carte* carte: listaCarti)
                                            {
                                                Sf* sciencefictionBook = dynamic_cast<Sf*>(carte);

                                                if(sciencefictionBook)
                                                {
                                                    carteGasita = true;
                                                    cout<<*sciencefictionBook<<endl;
                                                }
                                            }
                                        if(!carteGasita)
                                            throw runtime_error("Nu s-au găsit cărți SF în lista de cărți.");
                                        }

                                        catch(const exception& e)
                                        {
                                            cout<<e.what()<<endl;
                                        }
                                        cin.ignore();
                                        cin.get();
                                        curata();
                                        break;
                                    }
                                case 5:
                                    {
                                        curata();
                                        comandaCarti = 5;
                                        cout<<"Se revine la meniul anterior!\n";
                                        cin.ignore();
                                        cin.get();
                                        curata();
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
                    case 3:
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
                                while(optiuneImprumut != 3)
                                {
                                    try
                                    {
                                        meniuImprumut();
                                        cout<<"Alegeti optiunea: ";
                                        cin>>optiuneImprumut;
                                        if(cin.fail())
                                        {
                                            throw invalid_argument("\nInput invalid! Introdu o comanda valida!\n");
                                        }

                                        switch(optiuneImprumut)
                                        {
                                        case 1:
                                            {
                                                curata();
                                                for (int i = 0; i < listaCarti.size(); i++)
                                                {
                                                    cout << *listaCarti[i] << endl;
                                                }

                                                cout << "Introduceti ID-ul cartii pe care doriti sa o imprumutati: ";
                                                int idCarte;
                                                cin >> idCarte;

                                                if(cin.fail())
                                                {
                                                    throw invalid_argument("\nInput invalid! Introdu o comanda valida!\n");
                                                }

                                                bool carteGasita = false;

                                                Carte *carteDeImprumut = NULL;
                                                for (int i = 0; i < listaCarti.size(); i++)
                                                {
                                                    if (idCarte == listaCarti[i]->getId())
                                                    {
                                                        carteDeImprumut = listaCarti[i];
                                                        carteGasita = true;
                                                        break;
                                                    }
                                                }

                                                if (carteGasita && !carteDeImprumut->getEsteImprumutata())
                                                {
                                                    carteDeImprumut->imprumuta();
                                                    listaCartiImprumutate.push_back(carteDeImprumut);
                                                    curata();
                                                    cout << "Ati imprumutat cartea cu succes!" << endl;
                                                }
                                                else if (carteGasita && carteDeImprumut->getEsteImprumutata())
                                                {
                                                    cout << "Aceasta carte nu poate fi imprumutata momentan, deoarece este deja imprumutata." << endl;
                                                }
                                                else
                                                {
                                                    cout << "Nu exista nicio carte cu ID-ul introdus." << endl;
                                                }

                                                cin.ignore();
                                                cin.get();
                                                curata();
                                                break;
                                            }
                                        case 2:
                                            {
                                                curata();
                                                cout << "Lista de carti imprumutate: " << endl;
                                                bool existaCarteImprumutata = false;

                                                for (int i = 0; i < listaCarti.size(); i++)
                                                {
                                                    if (listaCarti[i]->getEsteImprumutata())
                                                    {
                                                        cout << "ID: " << listaCarti[i]->getId() << " - " << listaCarti[i]->getTitlu() << endl;
                                                        existaCarteImprumutata = true;
                                                    }
                                                }

                                                if (!existaCarteImprumutata)
                                                {
                                                    cout << "Nu aveti nicio carte imprumutata momentan." << endl;
                                                    cin.ignore();
                                                    cin.get();
                                                    curata();
                                                    continue;
                                                }

                                                else
                                                {
                                                    cout << "Introduceti ID-ul cartii pe care doriti sa o returnati: ";
                                                    int idCarteDeReturnat;
                                                    cin >> idCarteDeReturnat;

                                                    if(cin.fail())
                                                    {
                                                        throw invalid_argument("\nInput invalid! Introdu o comanda valida!\n");
                                                    }

                                                    bool carteGasita = false;
                                                    for (int i = 0; i < listaCarti.size(); i++)
                                                    {
                                                        if (idCarteDeReturnat == listaCarti[i]->getId()&& listaCarti[i] -> getEsteImprumutata())
                                                        {
                                                            listaCarti[i]->returneaza();
                                                            cout << "Ati returnat cartea cu succes!" << endl;
                                                            listaCartiImprumutate.clear();
                                                            carteGasita = true;
                                                            cin.ignore();
                                                            cin.get();
                                                            curata();
                                                            break;
                                                        }
                                                    }

                                                    if (!carteGasita)
                                                    {
                                                        cout << "Nu exista nicio carte imprumutata cu ID-ul introdus." << endl;
                                                        cin.ignore();
                                                        cin.get();
                                                        curata();
                                                    }
                                                }
                                                break;
                                            }
                                        case 3:
                                            {
                                                curata();
                                                optiuneImprumut = 3;
                                                cout<<"Se revine la meniul anterior!\n";
                                                cin.ignore();
                                                cin.get();
                                                curata();
                                                break;
                                            }
                                        default:
                                            {
                                                comandaDefault();
                                                break;
                                            }
                                        }
                                    }
                                    catch(const invalid_argument& e)
                                    {
                                        cout<<e.what();
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cin.get();
                                        curata();
                                    }
                                }
                            }
                            break;
                        }
                    case 4:
                        {
                            curata();
                            cout<<"Se revine la meniul anterior!\n";
                            cin.ignore();
                            cin.get();
                            curata();
                            comandaPaginaPrincipala = 4;
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
                int comandaMeniuAdmin = 0;
                parolaRet = parola();
                while((comandaMeniuAdmin != 14) && (parolaRet == true))
                {
                    try
                    {
                        meniuAdmin();
                        cout<<"Alegeti optiunea: ";
                        cin>> comandaMeniuAdmin;

                        if(cin.fail())
                        {
                            throw invalid_argument("Input invalid. Te rog introdu o comanda valida!\n");
                        }
                    }

                    catch(const invalid_argument& e)
                    {
                        cout<<e.what();
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    }

                    switch(comandaMeniuAdmin)
                    {
                    case 1:
                        {
                            curata();
                            bool stop = false;
                            while(stop!=true)
                            {
                                cout<<"Apasati 1 pentru a introduce o carte Science.\n";
                                cout<<"Apasati 2 pentru a introduce o carte Fiction.\n";
                                cout<<"Apasati 3 pentru a introduce o carte Science-Fiction.\n";
                                cout<<"Apasati 4 pentru a reveni la meniul anterior.\n";

                                int comandaAdaugaCarti = 0;
                                cin>>comandaAdaugaCarti;
                                switch(comandaAdaugaCarti)
                                {
                                case 1:
                                    {
                                        curata();
                                        Carte* c1 = new Science();
                                        cin>>*c1;
                                        listaCarti.push_back(c1);
                                        cin.ignore();
                                        cin.get();
                                        curata();
                                        break;
                                    }
                                case 2:
                                    {
                                        curata();
                                        Carte* c2 = new Fiction();
                                        cin>>*c2;
                                        listaCarti.push_back(c2);
                                        cin.ignore();
                                        cin.get();
                                        curata();
                                        break;
                                    }
                                case 3:
                                    {
                                        curata();
                                        Carte* c3 = new Sf();
                                        cin>>*c3;
                                        listaCarti.push_back(c3);
                                        cin.ignore();
                                        cin.get();
                                        curata();
                                        break;
                                    }
                                case 4:
                                    {
                                        curata();
                                        stop = true;
                                        cout<<"Se revine la meniul anterior";
                                        cin.ignore();
                                        cin.get();
                                        curata();
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
                            Utilizator u;
                            cin>>u;
                            listaUtilizatori.push_back(u);
                            curata();
                            cout<<"Ati adaugat un nou utilizator cu succes!\n";
                            cin.ignore();
                            cin.get();
                            curata();
                            break;
                        }
                    case 3:
                        {
                            curata();
                            Cont* b = new Bibliotecar();
                            cin>>*b;
                            listaBibliotecari.push_back(b);
                            cout<<"Ati adaugat un nou bibliotecar cu succes!\n";
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
                                cout<<*listaCarti[i]<<endl;
                            }
                            cin.ignore();
                            cin.get();
                            curata();
                            break;
                        }
                    case 5:
                        {
                            curata();
                            if(listaUtilizatori.size() != 0)
                            {
                                curata();
                                for(int i = 0; i<listaUtilizatori.size(); i++)
                                {
                                    cout<<listaUtilizatori[i];
                                }
                                cin.ignore();
                                cin.get();
                                curata();
                            }
                            else
                            {
                                cout<<"Nu exista utilizatori in lista!\n";
                                cin.ignore();
                                cin.get();
                                curata();
                            }

                            break;
                        }
                    case 6:
                        {
                            curata();
                            for(int i = 0; i<listaBibliotecari.size(); i++)
                            {
                                cout<<*listaBibliotecari[i];
                                listaBibliotecari[i]->vechime();
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
                            try
                            {
                                if(!listaCarti.empty())
                                {
                                    for (int i = 0; i < listaCarti.size(); i++)
                                    cout << *listaCarti[i] << endl;

                                    cout << "Introduceti ID-ul cartii pe care doriti sa o stergeti: ";
                                    int id;
                                    cin >> id;

                                    curata();
                                    bool carteGasita = false;
                                    for (int i = 0; i < listaCarti.size(); i++)
                                    {
                                        if (id == listaCarti[i]->getId())
                                        {
                                            listaCarti.erase(listaCarti.begin() + i);
                                            cout << "Cartea cu ID-ul " << id << " a fost stearsa cu succes!" << endl;
                                            cin.ignore();
                                            cin.get();
                                            curata();
                                            carteGasita = true;
                                            break;
                                        }
                                    }
                                    if(!carteGasita)
                                    {
                                        throw logic_error("Cartea cu Id-ul respectiv nu exista!\n");
                                    }
                                }
                                else throw logic_error("Nu exista carti care sa poata fi sterse!\n");
                            }
                            catch(const logic_error& e)
                            {
                                cout<<e.what();
                                cin.ignore();
                                cin.get();
                                curata();
                            }
                            break;
                        }
                    case 8:
                        {
                            curata();
                            try
                            {
                                if(!listaUtilizatori.empty())
                                {
                                    for(int i = 0; i<listaUtilizatori.size();i++)
                                        cout<<listaUtilizatori[i]<<endl;

                                    cout<<"Introduceti ID-ul utilizatorului pe care doriti sa il stergeti: ";
                                    int id;
                                    cin>> id;

                                    bool utilizatorGasit = false;

                                    for(int i = 0; i<listaUtilizatori.size();i++)
                                    {
                                        if(id == listaUtilizatori[i].getId())
                                        {
                                            listaUtilizatori.erase(listaUtilizatori.begin()+i);
                                            cout<<"Utilizatorul a fost sters cu succes!\n";
                                            cin.ignore();
                                            cin.get();
                                            curata();
                                            utilizatorGasit = true;
                                        }
                                    }
                                    if(!utilizatorGasit)
                                    {
                                        throw logic_error("Utilizatorul cu ID-ul respectiv nu exista!\n");
                                    }
                                }
                                else
                                {
                                    throw logic_error("Nu exista utilizatori care sa poata fi stersi!\n");
                                }
                            }
                            catch(const logic_error& e)
                            {
                                cout<<e.what();
                                cin.ignore();
                                cin.get();
                                curata();
                            }
                            break;
                        }
                    case 9:
                        {
                            curata();
                            try
                            {
                                if(!listaBibliotecari.empty())
                                {
                                    for(int i = 0; i<listaBibliotecari.size();i++)
                                        cout<<*listaBibliotecari[i]<<endl;
                                    cout<<"Introduceti ID-ul bibliotecarului pe care doriti sa il stergeti: ";
                                    int id;
                                    cin>> id;
                                    curata();
                                    bool angajatGasit = false;
                                    for(int i = 0; i<listaBibliotecari.size();i++)
                                    {
                                        if(id == listaBibliotecari[i] ->getId())
                                        {
                                            listaBibliotecari.erase(listaBibliotecari.begin()+i);
                                            cout<<"Angajatul cu ID-ul "<<id<< " a fost sters cu succes!"<<endl;
                                            cin.ignore();
                                            cin.get();
                                            curata();
                                            angajatGasit = true;
                                        }
                                    }
                                    if(!angajatGasit)
                                    {
                                        throw logic_error("Bibliotecarul cu ID-ul respectiv nu exista!\n");
                                    }
                                }
                                else throw logic_error("Nu exista bibliotecari care sa poata fi stersi!\n");
                            }
                            catch(const logic_error& e)
                            {
                                cout<<e.what();
                                cin.ignore();
                                cin.get();
                                curata();
                            }
                            break;
                        }
                    case 10:
                        {
                            curata();
                            cout<<"Fisierul trebuie sa aiba urmatorul format pe fiecare linie: Autor, Titlu, Genul Cartii, Rating, Este Imprumutata, Popularitate, Domeniu "<<endl;
                            cout<<"Daca fisierul nu va avea formatul specificat asta va duce la coruptia datelor!\n";
                            string fileName;
                            cout<<"Introduceti numele fisierului: ";
                            cin.ignore();
                            getline(cin, fileName);
                            importCartiScience(fileName);

                            curata();
                            asteaptaImportExport();

                            cout<<"Importul s-a realizat cu succes!";
                            cin.get();

                            curata();
                            break;
                        }
                    case 11:
                        {
                            curata();
                            cout<<"Fisierul trebuie sa aiba urmatorul format pe fiecare linie: Autor, Titlu, Genul Cartii, Rating, Este Imprumutata, Popularitate, Varsta Recomandata "<<endl;
                            cout<<"Daca fisierul nu va avea formatul specificat asta va duce la coruptia datelor!\n";

                            string fileName;
                            cout<<"Introduceti numele fisierului: ";
                            cin.ignore();
                            getline(cin, fileName);
                            importCartiFiction(fileName);

                            curata();
                            asteaptaImportExport();

                            cout<<"Importul s-a realizat cu succes!";
                            cin.get();

                            curata();
                            break;
                        }
                    case 12:
                        {
                            curata();
                            cout<<"Fisierul trebuie sa aiba urmatorul format pe fiecare linie: Autor, Titlu, Genul Cartii, Rating, Este Imprumutata, Popularitate, Domeniu, Varsta Recomandata, Exista Film "<<endl;
                            cout<<"Daca fisierul nu va avea formatul specificat asta va duce la coruptia datelor!\n";

                            string fileName;
                            cout<<"Introduceti numele fisierului: ";
                            cin.ignore();
                            getline(cin, fileName);
                            importCartiSF(fileName);

                            curata();
                            asteaptaImportExport();

                            cout<<"Importul s-a realizat cu succes!";
                            cin.get();

                            curata();
                            break;
                        }
                    case 13:
                        {
                            curata();

                            try
                            {
                                bool carteGasita = false;

                                for (int i = 0; i < listaCarti.size(); i++)
                                {
                                    cout << *listaCarti[i] << endl;
                                    carteGasita = true;
                                }

                                if(!carteGasita)
                                {
                                    throw runtime_error("Nu exista carti!");
                                }
                            }
                            catch(const runtime_error& e)
                            {
                                cout<<e.what();
                                pauza(3);
                                curata();
                            }

                            cout << "Introduceti ID-ul cartii pe care doriti sa o exportati: ";
                            int id;

                            while(true)
                            {
                                try
                                {
                                    string input;
                                    cin>>input;
                                    stringstream ss(input);

                                    ss>>id;

                                    if(ss.fail())
                                    {
                                        throw invalid_argument("ID invalid. Te rog introdu un ID valid.");
                                    }
                                    break;
                                }
                                catch(const invalid_argument& e)
                                {
                                    cout<<e.what();
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            }

                            try
                            {
                                if (id >= 0 && id < listaCarti.size())
                                {
                                    bool found = false;

                                    for (int i = 0; i < listaCarti.size(); i++)
                                    {
                                        if (id == listaCarti[i]->getId())
                                        {
                                            Carte* carteExport = listaCarti[i];
                                            string numeFisierOutput;
                                            cout << "Introduceti numele fisierului pentru export: ";
                                            cin.ignore();  // Ignore newline character from previous input
                                            getline(cin, numeFisierOutput);
                                            exportCarti(numeFisierOutput, carteExport);
                                            found = true;
                                            curata();
                                            asteaptaImportExport();
                                            cout<<"Exportul s-a realizat cu succes!";
                                            cin.get();
                                            break;
                                        }
                                    }

                                    if (!found)
                                    {
                                        cout << "Nu exista carte cu ID-ul specificat!" << endl;
                                        cin.ignore();
                                        cin.get();
                                    }
                                }
                                else
                                {
                                    throw out_of_range("ID-ul introdus nu exista!");
                                }
                            }
                            catch (const out_of_range& e)
                            {
                                cout << e.what();
                                pauza(3);
                                curata();
                            }

                            curata();
                            break;
                        }
                    case 14:
                        {
                            curata();
                            comandaMeniuAdmin = 14;
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
        case 3:
            {
                curata();
                for (Carte* carte : listaCarti)
                {
                    delete carte;
                }
                listaCarti.clear();
                comandaMeniuPrincipal = 3;
                cout<<"La revedere!";
                break;
            }
        default:
            {
                curata();
                comandaDefault();
                break;
            }
        }
    }
}

int main()
{
    Meniu& m = Meniu::getInstance();
    m.startMeniu();
    return 0;
}
