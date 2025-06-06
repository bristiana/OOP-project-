
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <vector>
using namespace std;
#define nullptr NULL
class Participant
{
private:
    char* nume;
    int varsta;
    float scor;
    bool prezent;
    int* rezultate;
    int nrRezultate;
    char gen;


    static int numarTotalParticipanti;
    const int id;

public:
    /// constructor fara parametri
    Participant() : id(numarTotalParticipanti + 1)
    {
        this->nume = new char[strlen("Anonim") + 1];
        strcpy(this->nume, "Anonim");
        this->varsta = 0;
        this->scor = 0.0;
        this->prezent = false;
        this->nrRezultate = 0;
        this->rezultate = nullptr;
        this->gen = 'N';
        numarTotalParticipanti++;
    }

    /// constructor cu toti parametrii
    Participant(const char* nume, int varsta, float scor, bool prezent, const int* rezultate, int nrRezultate, char gen) : id(numarTotalParticipanti + 1)
    {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->varsta = varsta;
        this->scor = scor;
        this->prezent = prezent;
        this->nrRezultate = nrRezultate;
        if (nrRezultate > 0 && rezultate != nullptr)
        {
            this->rezultate = new int[nrRezultate];
            for (int i = 0; i < nrRezultate; i++)
            {
                this->rezultate[i] = rezultate[i];
            }
        }
        else
        {
            this->rezultate = nullptr;
            this->nrRezultate = 0;
        }
        this->gen = gen;
        numarTotalParticipanti++;
    }

    /// constructor cu 2 parametri
    Participant(const char* nume, int varsta) : id(numarTotalParticipanti + 1)
    {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->varsta = varsta;
        this->scor = 0.0;
        this->prezent = false;
        this->nrRezultate = 0;
        this->rezultate = nullptr;
        this->gen = 'N';
        numarTotalParticipanti++;
    }

    /// Constructor cu 3 parametri
    Participant(const char* nume, float scor, char gen) : id(numarTotalParticipanti + 1)
    {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->varsta = 18;
        this->scor = scor;
        this->prezent = true;
        this->nrRezultate = 0;
        this->rezultate = nullptr;
        this->gen = gen;
        numarTotalParticipanti++;
    }

    /// copy constructor
    Participant(const Participant& p) : id(numarTotalParticipanti + 1)
    {
        this->nume = new char[strlen(p.nume) + 1];
        strcpy(this->nume, p.nume);
        this->varsta = p.varsta;
        this->scor = p.scor;
        this->prezent = p.prezent;
        this->nrRezultate = p.nrRezultate;
        if (p.nrRezultate > 0 && p.rezultate != nullptr)
        {
            this->rezultate = new int[p.nrRezultate];
            for (int i = 0; i < p.nrRezultate; i++)
            {
                this->rezultate[i] = p.rezultate[i];
            }
        }
        else
        {
            this->rezultate = nullptr;
        }
        this->gen = p.gen;
        numarTotalParticipanti++;
    }

    /// destructor
    ~Participant()
    {
        if (this->nume != nullptr)
        {
            delete[] this->nume;
        }
        if (this->rezultate != nullptr)
        {
            delete[] this->rezultate;
        }
        numarTotalParticipanti--;
    }

    /// operator de atribuire (=)
    Participant& operator=(const Participant& p)
    {
        if (this != &p)
        {
            if (this->nume != nullptr)
            {
                delete[] this->nume;
            }
            if (this->rezultate != nullptr)
            {
                delete[] this->rezultate;
            }

            this->nume = new char[strlen(p.nume) + 1];
            strcpy(this->nume, p.nume);
            this->varsta = p.varsta;
            this->scor = p.scor;
            this->prezent = p.prezent;
            this->nrRezultate = p.nrRezultate;
            if (p.nrRezultate > 0 && p.rezultate != nullptr)
            {
                this->rezultate = new int[p.nrRezultate];
                for (int i = 0; i < p.nrRezultate; i++)
                {
                    this->rezultate[i] = p.rezultate[i];
                }
            }
            else
            {
                this->rezultate = nullptr;
            }
            this->gen = p.gen;
        }
        return *this;
    }

    /// operator de indexare []
    int& operator[](int index)
    {
        if (index >= 0 && index < nrRezultate && rezultate != nullptr)
        {
            return rezultate[index];
        }
        throw std::runtime_error("Index invalid!");
    }

    /// operator prefix ++
    Participant& operator++()
    {
        this->varsta++;
        return *this;
    }

    /// operator postfix ++
    Participant operator++(int)
    {
        Participant temp = *this;
        this->varsta++;
        return temp;
    }

    /// operator +
    Participant operator+(const Participant& p) const
    {
        Participant rezultat = *this;
        rezultat.scor = this->scor + p.scor;
        return rezultat;
    }

    /// operator + (comutativitate)
    friend Participant operator+(float valoare, const Participant& p)
    {
        Participant rezultat = p;
        rezultat.scor = valoare + p.scor;
        return rezultat;
    }

    /// operator *
    Participant operator*(const Participant& p) const
    {
        Participant rezultat = *this;
        rezultat.scor = this->scor * p.scor;
        return rezultat;
    }

    /// operator * (comutativitate)
    friend Participant operator*(float valoare, const Participant& p)
    {
        Participant rezultat = p;
        rezultat.scor = valoare * p.scor;
        return rezultat;
    }

    /// operator ==
    bool operator==(const Participant& p) const
    {
        return this->varsta == p.varsta;
    }

    /// operator >
    bool operator>(const Participant& p) const
    {
        return this->scor > p.scor;
    }

    /// operatori pentru stream << si >>
    friend ostream& operator<<(ostream& out, const Participant& p);
    friend istream& operator>>(istream& in, Participant& p);

    /// getteri
    const char* getNume() const
    {
        return nume;
    }

    int getVarsta() const
    {
        return varsta;
    }

    float getScor() const
    {
        return scor;
    }

    bool isPrezent() const
    {
        return prezent;
    }

    int* getRezultate() const
    {
        return rezultate;
    }

    int getNrRezultate() const
    {
        return nrRezultate;
    }

    char getGen() const
    {
        return gen;
    }

    int getId() const
    {
        return id;
    }

    static int getNumarTotalParticipanti()
    {
        return numarTotalParticipanti;
    }

    /// setteri
    void setNume(const char* numeNou)
    {
        if (numeNou != nullptr)
        {
            if (this->nume != nullptr)
            {
                delete[] this->nume;
            }
            this->nume = new char[strlen(numeNou) + 1];
            strcpy(this->nume, numeNou);
        }
    }

    void setVarsta(int varstaNoua)
    {
        if (varstaNoua >= 0)
        {
            this->varsta = varstaNoua;
        }
    }

    void setScor(float scorNou)
    {
        if (scorNou >= 0)
        {
            this->scor = scorNou;
        }
    }

    void setPrezent(bool prezentNou)
    {
        this->prezent = prezentNou;
    }

    void setRezultate(const int* rezultateNoi, int nrRezultateNoi)
    {
        if (rezultateNoi != nullptr && nrRezultateNoi > 0)
        {
            if (this->rezultate != nullptr)
            {
                delete[] this->rezultate;
            }
            this->nrRezultate = nrRezultateNoi;
            this->rezultate = new int[nrRezultateNoi];
            for (int i = 0; i < nrRezultateNoi; i++)
            {
                this->rezultate[i] = rezultateNoi[i];
            }
        }
    }

    void setGen(char genNou)
    {
        if (genNou == 'M' || genNou == 'F' || genNou == 'N')
        {
            this->gen = genNou;
        }
    }

    /// functionalitate - afisare rezultate
    void afisareRezultate() const
    {
        cout << "Rezultatele participantului " << nume << ":" << endl;
        if (nrRezultate == 0 || rezultate == nullptr)
        {
            cout << "Nu exista rezultate inregistrate" << endl;
            return;
        }
        for (int i = 0; i < nrRezultate; i++)
        {
            cout << "Rezultatul " << i + 1 << ": " << rezultate[i] << endl;
        }
    }

    /// functionalitate - calcul scor mediu
    float calculareScoruMediu() const
    {
        if (nrRezultate == 0 || rezultate == nullptr)
        {
            return 0;
        }
        float suma = 0;
        for (int i = 0; i < nrRezultate; i++)
        {
            suma += rezultate[i];
        }
        return suma / nrRezultate;
    }
};

/// initializare variabila statica
int Participant::numarTotalParticipanti = 0;

/// implementare operator <<
ostream& operator<<(ostream& out, const Participant& p)
{
    out << "ID: " << p.id << endl;
    out << "Nume: " << p.nume << endl;
    out << "Varsta: " << p.varsta << endl;
    out << "Scor: " << p.scor << endl;
    out << "Prezent: " << (p.prezent ? "Da" : "Nu") << endl;
    out << "Gen: " << p.gen << endl;
    out << "Numar rezultate: " << p.nrRezultate << endl;
    if (p.nrRezultate > 0 && p.rezultate != nullptr)
    {
        out << "Rezultate: ";
        for (int i = 0; i < p.nrRezultate; i++)
        {
            out << p.rezultate[i] << " ";
        }
        out << endl;
    }
    return out;
}

/// implementare operator >>
istream& operator>>(istream& in, Participant& p)
{
    char numeBuffer[100];
    cout << "Nume: ";
    in >> numeBuffer;

    if (p.nume != nullptr)
    {
        delete[] p.nume;
    }
    p.nume = new char[strlen(numeBuffer) + 1];
    strcpy(p.nume, numeBuffer);

    cout << "Varsta: ";
    in >> p.varsta;

    cout << "Scor: ";
    in >> p.scor;

    int prezentInt;
    cout << "Prezent (1-Da, 0-Nu): ";
    in >> prezentInt;
    p.prezent = (prezentInt == 1);

    cout << "Gen (M/F/N): ";
    in >> p.gen;

    if (p.rezultate != nullptr)
    {
        delete[] p.rezultate;
        p.rezultate = nullptr;
    }

    cout << "Numar rezultate: ";
    in >> p.nrRezultate;

    if (p.nrRezultate > 0)
    {
        p.rezultate = new int[p.nrRezultate];
        cout << "Introduceti rezultatele: " << endl;
        for (int i = 0; i < p.nrRezultate; i++)
        {
            cout << "Rezultatul " << i + 1 << ": ";
            in >> p.rezultate[i];
        }
    }

    return in;
}







///    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////










class Eveniment
{
private:
    char* nume;
    int durata;
    float pretBilet;
    bool esteOnline;

    const int cod;
    static int nrEvenimente;

public:
    /// constructor fara paramteri
    Eveniment() : cod(++nrEvenimente)
    {
        nume = new char[strlen("Necunoscut") + 1];
        strcpy(nume, "Necunoscut");
        durata = 0;
        pretBilet = 0.0f;
        esteOnline = false;
    }

    /// constructor cu toti parametri
    Eveniment(const char* nume, int durata, float pretBilet, bool esteOnline) : cod(++nrEvenimente)
    {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->durata = durata;
        this->pretBilet = pretBilet;
        this->esteOnline = esteOnline;
    }

    /// constructor cu 2 parameteri
    Eveniment(const char* nume, int durata) : cod(++nrEvenimente)
    {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->durata = durata;
        this->pretBilet = 50.0f;
        this->esteOnline = false;
    }

    /// constructor cu 3 paramterii
    Eveniment(const char* nume, float pretBilet, bool esteOnline) : cod(++nrEvenimente)
    {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->durata = 90;
        this->pretBilet = pretBilet;
        this->esteOnline = esteOnline;
    }

    /// copy constructor
    Eveniment(const Eveniment& e) : cod(++nrEvenimente)
    {
        nume = new char[strlen(e.nume) + 1];
        strcpy(nume, e.nume);
        durata = e.durata;
        pretBilet = e.pretBilet;
        esteOnline = e.esteOnline;
    }

    ///destructor
    ~Eveniment()
    {
        if (nume != nullptr)
        {
            delete[] nume;
        }
    }


    ///operator de atribuire (=)
    Eveniment& operator=(const Eveniment& e)
    {
        if (this != &e)
        {
            if (nume != nullptr) delete[] nume;
            nume = new char[strlen(e.nume) + 1];
            strcpy(nume, e.nume);
            durata = e.durata;
            pretBilet = e.pretBilet;
            esteOnline = e.esteOnline;
        }
        return *this;
    }


    /// operator de indexare []

    char operator[](int index) const
    {
        if (index >= 0 && index < strlen(nume))
        {
            return nume[index];
        }
        throw runtime_error("Index invalid pentru nume");
    }


    /// operator prefix ++ -incrementeaza durata
    Eveniment& operator++()
    {
        durata++;
        return *this;
    }

    /// operator postfix ++ -incrementeaza durata
    Eveniment operator++(int)
    {
        Eveniment temp = *this;
        durata++;
        return temp;
    }


    /// operator + , pretBilet +=ceva
    Eveniment operator+(float valoare) const
    {
        Eveniment rezultat = *this;
        rezultat.pretBilet += valoare;
        return rezultat;
    }


    ///operator + comutativitate
    friend Eveniment operator+(float valoare, const Eveniment& e)
    {
        return e + valoare;
    }


    ///operator * - multiplica pretBilet cu un factor
    Eveniment operator*(float factor) const
    {
        Eveniment rezultat = *this;
        rezultat.pretBilet *= factor;
        return rezultat;
    }


    ///operator * - asigura comutativitatea inmultirii
    friend Eveniment operator*(float factor, const Eveniment& e)
    {
        return e * factor;
    }


    /// operator == -compara 2 evenimnete daca au aceeasi durata
    bool operator==(const Eveniment& e) const
    {
        return durata == e.durata;
    }


    /// operator > -verifica daca pretb1 > pretb2
    bool operator>(const Eveniment& e) const
    {
        return pretBilet > e.pretBilet;
    }



    /// getteri

    const char* getNume() const
    {
        return nume;
    }
    int getDurata() const
    {
        return durata;
    }
    float getPretBilet() const
    {
        return pretBilet;
    }
    bool getEsteOnline() const
    {
        return esteOnline;
    }
    int getCod() const
    {
        return cod;
    }
    static int getNrEvenimente()
    {
        return nrEvenimente;
    }


    /// setteri
    void setNume(const char* numeNou)
    {
        if (numeNou != nullptr)
        {
            if (nume != nullptr) delete[] nume;
            nume = new char[strlen(numeNou) + 1];
            strcpy(nume, numeNou);
        }
    }

    void setDurata(int durataNoua)
    {
        if (durataNoua > 0) durata = durataNoua;
    }

    void setPretBilet(float pretNou)
    {
        if (pretNou >= 0) pretBilet = pretNou;
    }

    void setEsteOnline(bool online)
    {
        esteOnline = online;
    }


    ///fucntionalitate -afisare eveniment
    void afisareTipEveniment() const
    {
        cout << "Evenimentul \"" << nume << "\" este " << (esteOnline ? "online" : "fizic") << "." << endl;
    }


    ///implementare operator <<  - friend pt acces membri privati
    friend ostream& operator<<(ostream& out, const Eveniment& e)
    {
        out << "Cod: " << e.cod << "\n";
        out << "Nume: " << e.nume << "\n";
        out << "Durata: " << e.durata << " minute\n";
        out << "Pret bilet: " << e.pretBilet << " lei\n";
        out << "Online: " << (e.esteOnline ? "Da" : "Nu") << endl;
        return out;
    }

    ///implementare operator >>
    friend istream& operator>>(istream& in, Eveniment& e)
    {
        char buffer[100];
        cout << "Nume: ";
        in >> ws;
        in.getline(buffer, 100);
        if (e.nume != nullptr) delete[] e.nume;
        e.nume = new char[strlen(buffer) + 1];
        strcpy(e.nume, buffer);

        cout << "Durata (minute): ";
        in >> e.durata;

        cout << "Pret bilet: ";
        in >> e.pretBilet;

        int online;
        cout << "Este online (1-Da, 0-Nu): ";
        in >> online;
        e.esteOnline = (online == 1);

        return in;
    }
};










///    //////////////////////////////////////////////////////////////////////////////////////////////










class Locatie
{
private:
    char* nume;
    char* adresa;
    int capacitate;
    bool inAerLiber;
    const int cod;
    static int nrLocatii;

public:

    ///constructor fara paramteri
    Locatie() : cod(++nrLocatii)
    {
        nume = new char[strlen("Necunoscuta") + 1];
        strcpy(nume, "Necunoscuta");
        adresa = new char[strlen("Necunoscuta") + 1];
        strcpy(adresa, "Necunoscuta");
        capacitate = 0;
        inAerLiber = false;
    }


    ///constructor cu toti parametri
    Locatie(const char* nume, const char* adresa, int capacitate, bool inAerLiber) : cod(++nrLocatii)
    {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->adresa = new char[strlen(adresa) + 1];
        strcpy(this->adresa, adresa);
        this->capacitate = capacitate;
        this->inAerLiber = inAerLiber;
    }

    ///constructor cu 2 parametri
    Locatie(const char* nume, int capacitate) : cod(++nrLocatii)
    {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->adresa = new char[strlen("Adresa necunoscuta") + 1];
        strcpy(this->adresa, "Adresa necunoscuta");
        this->capacitate = capacitate;
        this->inAerLiber = false;
    }

    ///constructor cu 3 parametri
    Locatie(const char* nume, const char* adresa) : cod(++nrLocatii)
    {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->adresa = new char[strlen(adresa) + 1];
        strcpy(this->adresa, adresa);
        this->capacitate = 100;
        this->inAerLiber = true;
    }

    /// copy constructor
    Locatie(const Locatie& l) : cod(++nrLocatii)
    {
        nume = new char[strlen(l.nume) + 1];
        strcpy(nume, l.nume);
        adresa = new char[strlen(l.adresa) + 1];
        strcpy(adresa, l.adresa);
        capacitate = l.capacitate;
        inAerLiber = l.inAerLiber;
    }

    ///destructor
    ~Locatie()
    {
        delete[] nume;
        delete[] adresa;
    }

    ///operator de atribuire (=)
    Locatie& operator=(const Locatie& l)
    {
        if (this != &l)
        {
            delete[] nume;
            delete[] adresa;
            nume = new char[strlen(l.nume) + 1];
            strcpy(nume, l.nume);
            adresa = new char[strlen(l.adresa) + 1];
            strcpy(adresa, l.adresa);
            capacitate = l.capacitate;
            inAerLiber = l.inAerLiber;
        }
        return *this;
    }

    ///operator de indexare []
    char operator[](int index) const
    {
        if (index >= 0 && index < strlen(nume))
        {
            return nume[index];
        }
        throw runtime_error("Index invalid pentru nume");
    }

    ///operator prefix ++
    Locatie& operator++()
    {
        capacitate++;
        return *this;
    }

    /// operator postfix ++
    Locatie operator++(int)
    {
        Locatie temp = *this;
        capacitate++;
        return temp;
    }

    /// operator +
    Locatie operator+(int locuri) const
    {
        Locatie rezultat = *this;
        rezultat.capacitate += locuri;
        return rezultat;
    }

    /// Operator + (comutativitate)
    friend Locatie operator+(int locuri, const Locatie& l)
    {
        return l + locuri;
    }

    /// operator *
    Locatie operator*(int factor) const
    {
        Locatie rezultat = *this;
        rezultat.capacitate *= factor;
        return rezultat;
    }

    /// operator * (comutativitate)
    friend Locatie operator*(int factor, const Locatie& l)
    {
        return l * factor;
    }

    /// operator ==
    bool operator==(const Locatie& l) const
    {
        return capacitate == l.capacitate;
    }

    /// operator >=
    bool operator>=(const Locatie& l) const
    {
        return capacitate >= l.capacitate;
    }


    ///getteri

    const char* getNume() const
    {
        return nume;
    }

    const char* getAdresa() const
    {
        return adresa;
    }

    int getCapacitate() const
    {
        return capacitate;
    }

    bool getInAerLiber() const
    {
        return inAerLiber;
    }

    int getCod() const
    {
        return cod;
    }

    static int getNrLocatii()
    {
        return nrLocatii;
    }

/// Setteri
    void setNume(const char* numeNou)
    {
        if (numeNou != nullptr)
        {
            delete[] nume;
            nume = new char[strlen(numeNou) + 1];
            strcpy(nume, numeNou);
        }
    }

    void setAdresa(const char* adresaNoua)
    {
        if (adresaNoua != nullptr)
        {
            delete[] adresa;
            adresa = new char[strlen(adresaNoua) + 1];
            strcpy(adresa, adresaNoua);
        }
    }

    void setCapacitate(int capacitateNoua)
    {
        if (capacitateNoua >= 0)
            capacitate = capacitateNoua;
    }

    void setInAerLiber(bool esteInAerLiber)
    {
        inAerLiber = esteInAerLiber;
    }


    ///functionalitate
    void afisareDescriere() const
    {
        cout << "Locatia \"" << nume << "\" se afla la adresa " << adresa << " si are o capacitate de " << capacitate;
        cout << " locuri. Este " << (inAerLiber ? "in aer liber." : "in interior.") << endl;
    }


    ///operator <<
    friend ostream& operator<<(ostream& out, const Locatie& l)
    {
        out << "Cod: " << l.cod << "\n";
        out << "Nume: " << l.nume << "\n";
        out << "Adresa: " << l.adresa << "\n";
        out << "Capacitate: " << l.capacitate << "\n";
        out << "Aer liber: " << (l.inAerLiber ? "Da" : "Nu") << endl;
        return out;
    }

    ///operator >>
    friend istream& operator>>(istream& in, Locatie& l)
    {
        char buffer[100];
        cout << "Nume locatie: ";
        in >> ws;
        in.getline(buffer, 100);
        delete[] l.nume;
        l.nume = new char[strlen(buffer) + 1];
        strcpy(l.nume, buffer);

        cout << "Adresa locatiei: ";
        in.getline(buffer, 100);
        delete[] l.adresa;
        l.adresa = new char[strlen(buffer) + 1];
        strcpy(l.adresa, buffer);

        cout << "Capacitate: ";
        in >> l.capacitate;
        int liber;
        cout << "Este in aer liber? (1-Da, 0-Nu): ";
        in >> liber;
        l.inAerLiber = (liber == 1);

        return in;
    }
};






///    //////////////////////////////////////////////////////////////////////////////////////////////







class Bilet
{
private:
    char* tip;
    float pret;
    bool valid;
    float* reduceri;
    int nrReduceri;
    const int id;
    static int nrBilete;

public:
    /// constructor fara parametri
    Bilet() : id(++nrBilete)
    {
        tip = new char[strlen("Standard") + 1];
        strcpy(tip, "Standard");
        pret = 50.0;
        valid = true;
        nrReduceri = 0;
        reduceri = nullptr;
    }

    /// constructor cu toti parametrii
    Bilet(const char* tip, float pret, bool valid, float* reduceri, int nrReduceri) : id(++nrBilete)
    {
        this->tip = new char[strlen(tip) + 1];
        strcpy(this->tip, tip);
        this->pret = pret;
        this->valid = valid;
        this->nrReduceri = nrReduceri;
        if (nrReduceri > 0 && reduceri != nullptr)
        {
            this->reduceri = new float[nrReduceri];
            for (int i = 0; i < nrReduceri; i++)
                this->reduceri[i] = reduceri[i];
        }
        else
        {
            this->reduceri = nullptr;
        }
    }


    /// constructor cu doi parametri
    Bilet(const char* tip, float pret) : id(++nrBilete)
    {
        this->tip = new char[strlen(tip) + 1];
        strcpy(this->tip, tip);
        this->pret = pret;
        this->valid = true;
        this->nrReduceri = 0;
        this->reduceri = nullptr;
    }

    /// constructor cu trei parametri
    Bilet(const char* tip, float pret, bool valid) : id(++nrBilete)
    {
        this->tip = new char[strlen(tip) + 1];
        strcpy(this->tip, tip);
        this->pret = pret;
        this->valid = valid;
        this->nrReduceri = 0;
        this->reduceri = nullptr;
    }

    ///copy constructor
    Bilet(const Bilet& b) : id(++nrBilete)
    {
        tip = new char[strlen(b.tip) + 1];
        strcpy(tip, b.tip);
        pret = b.pret;
        valid = b.valid;
        nrReduceri = b.nrReduceri;
        if (nrReduceri > 0 && b.reduceri != nullptr)
        {
            reduceri = new float[nrReduceri];
            for (int i = 0; i < nrReduceri; i++)
                reduceri[i] = b.reduceri[i];
        }
        else
        {
            reduceri = nullptr;
        }
    }


    ///destructor
    ~Bilet()
    {
        delete[] tip;
        delete[] reduceri;
    }

    /// Operator de atribuire (=)
    Bilet& operator=(const Bilet& b)
    {
        if (this != &b)
        {
            delete[] tip;
            delete[] reduceri;
            tip = new char[strlen(b.tip) + 1];
            strcpy(tip, b.tip);
            pret = b.pret;
            valid = b.valid;
            nrReduceri = b.nrReduceri;
            if (nrReduceri > 0 && b.reduceri != nullptr)
            {
                reduceri = new float[nrReduceri];
                for (int i = 0; i < nrReduceri; i++)
                    reduceri[i] = b.reduceri[i];
            }
            else
            {
                reduceri = nullptr;
            }
        }
        return *this;
    }


    /// operator de indexare[]
    char operator[](int index) const
    {
        if (index >= 0 && index < strlen(tip))
        {
            return tip[index];
        }
        throw out_of_range("Index invalid pentru tip bilet");
    }

    ///operator prefix ++
    Bilet& operator++()
    {
        pret += 10;
        return *this;
    }

    /// operator postfix ++
    Bilet operator++(int)
    {
        Bilet temp = *this;
        pret += 10;
        return temp;
    }

    /// operator +
    Bilet operator+(float valoare) const
    {
        return Bilet(tip, pret + valoare, valid, reduceri, nrReduceri);
    }

    /// operator + (comutativitate)
    friend Bilet operator+(float valoare, const Bilet& b)
    {
        return b + valoare;
    }

    /// operator *
    Bilet operator*(int factor) const
    {
        return Bilet(tip, pret * factor, valid, reduceri, nrReduceri);
    }

    /// operator * (comutativitate)
    friend Bilet operator*(int factor, const Bilet& b)
    {
        return b * factor;
    }

    /// operator ==
    bool operator==(const Bilet& b) const
    {
        return strcmp(tip, b.tip) == 0 && pret == b.pret && valid == b.valid;
    }

    /// Operator >=
    bool operator>=(const Bilet& b) const
    {
        return pret >= b.pret;
    }

    ///operator <<
    friend ostream& operator<<(ostream& out, const Bilet& b)
    {
        out << "ID: " << b.id << "\nTip: " << b.tip << "\nPret: " << b.pret << "\nValid: " << (b.valid ? "Da" : "Nu") << endl;
        out << "Nr reduceri: " << b.nrReduceri << "\n";
        if (b.nrReduceri > 0 && b.reduceri != nullptr)
        {
            out << "Reducerile sunt: ";
            for (int i = 0; i < b.nrReduceri; i++)
            {
                out << b.reduceri[i] << "% ";
            }
            out << endl;
        }
        return out;
    }

    /// operator >>
    friend istream& operator>>(istream& in, Bilet& b)
    {
        char buffer[100];
        cout << "Tip bilet: ";
        in >> ws;
        in.getline(buffer, 100);
        delete[] b.tip;
        b.tip = new char[strlen(buffer) + 1];
        strcpy(b.tip, buffer);

        cout << "Pret: ";
        in >> b.pret;
        cout << "Valid (1-Da, 0-Nu): ";
        in >> b.valid;

        cout << "Nr reduceri: ";
        in >> b.nrReduceri;
        delete[] b.reduceri;
        if (b.nrReduceri > 0)
        {
            b.reduceri = new float[b.nrReduceri];
            for (int i = 0; i < b.nrReduceri; i++)
            {
                cout << "Reducere " << i + 1 << ": ";
                in >> b.reduceri[i];
            }
        }
        else
        {
            b.reduceri = nullptr;
        }
        return in;
    }


    ///getteri
    float getPret() const
    {
        return pret;
    }
    const char* getTip() const
    {
        return tip;
    }
    bool isValid() const
    {
        return valid;
    }
    int getId() const
    {
        return id;
    }
    static int getNrBilete()
    {
        return nrBilete;
    }


    /// setteri
    void setTip(const char* newTip) {
        delete[] tip;
        tip = new char[strlen(newTip) + 1];
        strcpy(tip, newTip);
    }

    void setPret(float newPret) {
        pret = newPret;
    }

    void setValid(bool newValid) {
        valid = newValid;
    }

    void setReduceri(float* newReduceri, int newNrReduceri) {
        delete[] reduceri;
        if (newNrReduceri > 0 && newReduceri != nullptr) {
            nrReduceri = newNrReduceri;
            reduceri = new float[nrReduceri];
            for (int i = 0; i < nrReduceri; i++) {
                reduceri[i] = newReduceri[i];
            }
        } else {
            nrReduceri = 0;
            reduceri = nullptr;
        }
    }

    void setNrReduceri(int newNrReduceri) {
        delete[] reduceri;
        if (newNrReduceri > 0) {
            nrReduceri = newNrReduceri;
            reduceri = new float[nrReduceri]();
        } else {
            nrReduceri = 0;
            reduceri = nullptr;
        }
    }


};







///    //////////////////////////////////////////////////////////////////////////////////////////////





void meniu_participant();
void meniu_eveniment();
void meniu_bilet();
void meniu_locatie();

void meniu_participant()
{
    Participant* participanti = nullptr;
    int nrParticipanti = 0;
    int optiune = 0;

    do
    {
        cout << "\n===== MENIU PARTICIPANTI =====\n";
        cout << "1. Adauga participant nou\n";
        cout << "2. Afiseaza toti participantii\n";
        cout << "3. Modifica un participant\n";
        cout << "4. Sterge un participant\n";
        cout << "5. Afiseaza rezultatele unui participant\n";
        cout << "6. Calculeaza scorul mediu pentru un participant\n";
        cout << "7. Compara doi participanti (dupa varsta)\n";
        cout << "8. Compara doi participanti (dupa scor)\n";
        cout << "9. Adauga 1 an la varsta unui participant\n";
        cout << "10. Aduna scorurile a doi participanti\n";
        cout << "11. Inmulteste scorul unui participant\n";
        cout << "0. Iesire\n";
        cout << "Optiunea ta: ";
        cin >> optiune;

        switch (optiune)
        {
        case 1:
        {
            // Creaza un array mai mare
            Participant* temp = new Participant[nrParticipanti + 1];

            // Copiaza participantii existenti
            for (int i = 0; i < nrParticipanti; i++)
            {
                temp[i] = participanti[i];
            }

            // Citeste noul participant
            cout << "\nIntroduceti datele pentru noul participant:\n";
            cin >> temp[nrParticipanti];

            // Sterge array-ul vechi
            if (participanti != nullptr)
            {
                delete[] participanti;
            }

            // Actualizeaza array-ul si numarul de participanti
            participanti = temp;
            nrParticipanti++;

            cout << "\nParticipant adaugat cu succes!" << endl;
            break;
        }
        case 2:
        {
            if (nrParticipanti == 0)
            {
                cout << "\nNu exista participanti inregistrati." << endl;
                break;
            }

            cout << "\nLista de participanti (" << nrParticipanti << "):" << endl;
            for (int i = 0; i < nrParticipanti; i++)
            {
                cout << "\n--- Participant " << i + 1 << " ---\n";
                cout << participanti[i] << endl;
            }
            break;
        }
        case 3:
        {
            if (nrParticipanti == 0)
            {
                cout << "\nNu exista participanti inregistrati." << endl;
                break;
            }

            int index;
            cout << "\nIntroduceti indexul participantului de modificat (1-" << nrParticipanti << "): ";
            cin >> index;

            if (index < 1 || index > nrParticipanti)
            {
                cout << "Index invalid!" << endl;
                break;
            }

            cout << "\nIntroduceti noile date pentru participant:\n";
            cin >> participanti[index - 1];

            cout << "\nParticipant modificat cu succes!" << endl;
            break;
        }
        case 4:
        {
            if (nrParticipanti == 0)
            {
                cout << "\nNu exista participanti inregistrati." << endl;
                break;
            }

            int index;
            cout << "\nIntroduceti indexul participantului de sters (1-" << nrParticipanti << "): ";
            cin >> index;

            if (index < 1 || index > nrParticipanti)
            {
                cout << "Index invalid!" << endl;
                break;
            }

            // Creaza un array mai mic
            Participant* temp = new Participant[nrParticipanti - 1];

            // Copiaza participantii, cu exceptia celui care trebuie sters
            int j = 0;
            for (int i = 0; i < nrParticipanti; i++)
            {
                if (i != index - 1)
                {
                    temp[j++] = participanti[i];
                }
            }

            // Sterge array-ul vechi
            delete[] participanti;

            // Actualizeaza array-ul si numarul de participanti
            participanti = temp;
            nrParticipanti--;

            cout << "\nParticipant sters cu succes!" << endl;
            break;
        }
        case 5:
        {
            if (nrParticipanti == 0)
            {
                cout << "\nNu exista participanti inregistrati." << endl;
                break;
            }

            int index;
            cout << "\nIntroduceti indexul participantului (1-" << nrParticipanti << "): ";
            cin >> index;

            if (index < 1 || index > nrParticipanti)
            {
                cout << "Index invalid!" << endl;
                break;
            }

            participanti[index - 1].afisareRezultate();
            break;
        }
        case 6:
        {
            if (nrParticipanti == 0)
            {
                cout << "\nNu exista participanti inregistrati." << endl;
                break;
            }

            int index;
            cout << "\nIntroduceti indexul participantului (1-" << nrParticipanti << "): ";
            cin >> index;

            if (index < 1 || index > nrParticipanti)
            {
                cout << "Index invalid!" << endl;
                break;
            }

            float scorMediu = participanti[index - 1].calculareScoruMediu();
            cout << "Scorul mediu al participantului " << participanti[index - 1].getNume() << " este: " << scorMediu << endl;
            break;
        }
        case 7:
        {
            if (nrParticipanti < 2)
            {
                cout << "\nAu nevoie de cel putin 2 participanti inregistrati." << endl;
                break;
            }

            int index1, index2;
            cout << "\nIntroduceti indexul primului participant (1-" << nrParticipanti << "): ";
            cin >> index1;
            cout << "Introduceti indexul celui de-al doilea participant (1-" << nrParticipanti << "): ";
            cin >> index2;

            if (index1 < 1 || index1 > nrParticipanti || index2 < 1 || index2 > nrParticipanti)
            {
                cout << "Index invalid!" << endl;
                break;
            }

            if (participanti[index1 - 1] == participanti[index2 - 1])
            {
                cout << "Participantii au aceeasi varsta." << endl;
            }
            else
            {
                cout << "Participantii au varste diferite." << endl;
            }
            break;
        }
        case 8:
        {
            if (nrParticipanti < 2)
            {
                cout << "\nAu nevoie de cel putin 2 participanti inregistrati." << endl;
                break;
            }

            int index1, index2;
            cout << "\nIntroduceti indexul primului participant (1-" << nrParticipanti << "): ";
            cin >> index1;
            cout << "Introduceti indexul celui de-al doilea participant (1-" << nrParticipanti << "): ";
            cin >> index2;

            if (index1 < 1 || index1 > nrParticipanti || index2 < 1 || index2 > nrParticipanti)
            {
                cout << "Index invalid!" << endl;
                break;
            }

            if (participanti[index1 - 1] > participanti[index2 - 1])
            {
                cout << participanti[index1 - 1].getNume() << " are un scor mai mare decat " << participanti[index2 - 1].getNume() << "." << endl;
            }
            else
            {
                cout << participanti[index1 - 1].getNume() << " are un scor mai mic sau egal cu " << participanti[index2 - 1].getNume() << "." << endl;
            }
            break;
        }
        case 9:
        {
            if (nrParticipanti == 0)
            {
                cout << "\nNu exista participanti inregistrati." << endl;
                break;
            }

            int index;
            cout << "\nIntroduceti indexul participantului (1-" << nrParticipanti << "): ";
            cin >> index;

            if (index < 1 || index > nrParticipanti)
            {
                cout << "Index invalid!" << endl;
                break;
            }

            ++participanti[index - 1]; // Foloseste operatorul prefix
            cout << "Varsta a fost incrementata. Noua varsta: " << participanti[index - 1].getVarsta() << endl;
            break;
        }
        case 10:
        {
            if (nrParticipanti < 2)
            {
                cout << "\nAu nevoie de cel putin 2 participanti inregistrati." << endl;
                break;
            }

            int index1, index2;
            cout << "\nIntroduceti indexul primului participant (1-" << nrParticipanti << "): ";
            cin >> index1;
            cout << "Introduceti indexul celui de-al doilea participant (1-" << nrParticipanti << "): ";
            cin >> index2;

            if (index1 < 1 || index1 > nrParticipanti || index2 < 1 || index2 > nrParticipanti)
            {
                cout << "Index invalid!" << endl;
                break;
            }

            Participant rezultat = participanti[index1 - 1] + participanti[index2 - 1];
            cout << "Suma scorurilor: " << rezultat.getScor() << endl;
            break;
        }
        case 11:
        {
            if (nrParticipanti == 0)
            {
                cout << "\nNu exista participanti inregistrati." << endl;
                break;
            }

            int index;
            float factor;
            cout << "\nIntroduceti indexul participantului (1-" << nrParticipanti << "): ";
            cin >> index;

            if (index < 1 || index > nrParticipanti)
            {
                cout << "Index invalid!" << endl;
                break;
            }

            cout << "Introduceti factorul de inmultire: ";
            cin >> factor;

            Participant rezultat = factor * participanti[index - 1]; // Foloseste comutativitatea
            cout << "Rezultatul inmultirii: " << rezultat.getScor() << endl;
            break;
        }
        case 0:
            cout << "\nLa revedere!" << endl;
            break;
        default:
            cout << "\nOptiune invalida. Va rugam incercati din nou." << endl;
        }
    }
    while (optiune != 0);

    // Eliberare memorie
    if (participanti != nullptr)
    {
        delete[] participanti;
    }
}


int Eveniment::nrEvenimente = -1;

void meniu_eveniment()
{
    Eveniment* evenimente = nullptr;
    int nrEvenimente = 0;
    int optiune = 0;

    do
    {
        cout << "\n===== MENIU EVENIMENT =====\n";
        cout << "1. Adauga eveniment nou\n";
        cout << "2. Afiseaza toate evenimentele\n";
        cout << "3. Modifica un eveniment\n";
        cout << "4. Sterge un eveniment\n";
        cout << "5. Afiseaza tipul unui eveniment\n";
        cout << "6. Compara doua evenimente (pret bilet)\n";
        cout << "7. Compara doua evenimente (durata)\n";
        cout << "8. Incrementeaza durata unui eveniment\n";
        cout << "9. Aduna valoare la pretul unui eveniment\n";
        cout << "10. Inmulteste pretul unui eveniment\n";
        cout << "11. Inapoi la meniul principal\n";
        cout << "Optiunea ta: ";
        cin >> optiune;

        switch (optiune)
        {
        case 1:
        {
            Eveniment* temp = new Eveniment[nrEvenimente + 1];
            for (int i = 0; i < nrEvenimente; i++) temp[i] = evenimente[i];
            cout << "\nIntroduceti datele pentru noul eveniment:\n";
            cin >> temp[nrEvenimente];
            delete[] evenimente;
            evenimente = temp;
            nrEvenimente++;
            cout << "\nEveniment adaugat cu succes!\n";
            break;
        }
        case 2:
        {
            if (nrEvenimente == 0) cout << "\nNu exista evenimente.\n";
            for (int i = 0; i < nrEvenimente; i++)
            {
                cout << "\n--- Eveniment " << i + 1 << " ---\n";
                cout << evenimente[i];
            }
            break;
        }
        case 3:
        {
            int index;
            cout << "\nIntroduceti indexul evenimentului de modificat (1-" << nrEvenimente << "): ";
            cin >> index;
            if (index < 1 || index > nrEvenimente)
            {
                cout << "Index invalid!\n";
                break;
            }
            cout << "\nIntroduceti noile date pentru eveniment:\n";
            cin >> evenimente[index - 1];
            break;
        }
        case 4:
        {
            int index;
            cout << "\nIntroduceti indexul evenimentului de sters (1-" << nrEvenimente << "): ";
            cin >> index;
            if (index < 1 || index > nrEvenimente)
            {
                cout << "Index invalid!\n";
                break;
            }
            Eveniment* temp = new Eveniment[nrEvenimente - 1];
            for (int i = 0, j = 0; i < nrEvenimente; i++)
            {
                if (i != index - 1) temp[j++] = evenimente[i];
            }
            delete[] evenimente;
            evenimente = temp;
            nrEvenimente--;
            cout << "\nEveniment sters cu succes!\n";
            break;
        }
        case 5:
        {
            int index;
            cout << "\nIntroduceti indexul evenimentului: ";
            cin >> index;
            evenimente[index - 1].afisareTipEveniment();
            break;
        }
        case 6:
        case 7:
        {
            int i1, i2;
            cout << "Index 1: ";
            cin >> i1;
            cout << "Index 2: ";
            cin >> i2;
            if (optiune == 6)
            {
                if (evenimente[i1 - 1] > evenimente[i2 - 1])
                    cout << evenimente[i1 - 1].getNume() << " este mai scump.\n";
                else
                    cout << evenimente[i2 - 1].getNume() << " este mai scump sau egal.\n";
            }
            else
            {
                if (evenimente[i1 - 1] == evenimente[i2 - 1])
                    cout << "Evenimentele au aceeasi durata.\n";
                else
                    cout << "Evenimentele au durate diferite.\n";
            }
            break;
        }
        case 8:
        {
            int index;
            cout << "Indexul evenimentului: ";
            cin >> index;
            ++evenimente[index - 1];
            cout << "Durata noua: " << evenimente[index - 1].getDurata() << " minute\n";
            break;
        }
        case 9:
        {
            int index;
            float val;
            cout << "Indexul evenimentului: ";
            cin >> index;
            cout << "Valoare de adunat: ";
            cin >> val;
            Eveniment rez = evenimente[index - 1] + val;
            cout << "Pret nou: " << rez.getPretBilet() << " lei\n";
            break;
        }
        case 10:
        {
            int index;
            float val;
            cout << "Indexul evenimentului: ";
            cin >> index;
            cout << "Factor: ";
            cin >> val;
            Eveniment rez = val * evenimente[index - 1];
            cout << "Pret nou: " << rez.getPretBilet() << " lei\n";
            break;
        }
        case 11:
            cout << "\nRevenire la meniul principal...\n";
            break;
        default:
            cout << "\nOptiune invalida.\n";
        }
    }
    while (optiune != 11);

    delete[] evenimente;
}

int Locatie::nrLocatii = 0;

void meniu_locatie()
{
    Locatie* locatii = nullptr;
    int nrLocatii = 0;
    int optiune = 0;

    do
    {
        cout << "\n===== MENIU LOCATII =====\n";
        cout << "1. Adauga locatie noua\n";
        cout << "2. Afiseaza toate locatiile\n";
        cout << "3. Modifica o locatie\n";
        cout << "4. Sterge o locatie\n";
        cout << "5. Afiseaza descriere locatie\n";
        cout << "6. Compara doua locatii (capacitate)\n";
        cout << "7. Verifica egalitate capacitate\n";
        cout << "8. Incrementeaza capacitate locatie\n";
        cout << "9. Aduna locuri la capacitate\n";
        cout << "10. Inmulteste capacitate\n";
        cout << "11. Inapoi la meniul principal\n";
        cout << "Optiunea ta: ";
        cin >> optiune;

        switch (optiune)
        {
        case 1:
        {
            Locatie* temp = new Locatie[nrLocatii + 1];
            for (int i = 0; i < nrLocatii; i++) temp[i] = locatii[i];
            cout << "\nIntroduceti datele pentru noua locatie:\n";
            cin >> temp[nrLocatii];
            delete[] locatii;
            locatii = temp;
            nrLocatii++;
            cout << "\nLocatie adaugata cu succes!\n";
            break;
        }
        case 2:
        {
            if (nrLocatii == 0) cout << "\nNu exista locatii.\n";
            for (int i = 0; i < nrLocatii; i++)
            {
                cout << "\n--- Locatie " << i + 1 << " ---\n";
                cout << locatii[i];
            }
            break;
        }
        case 3:
        {
            int index;
            cout << "\nIntroduceti indexul locatiei de modificat (1-" << nrLocatii << "): ";
            cin >> index;
            if (index < 1 || index > nrLocatii)
            {
                cout << "Index invalid!\n";
                break;
            }
            cout << "\nIntroduceti noile date pentru locatie:\n";
            cin >> locatii[index - 1];
            break;
        }
        case 4:
        {
            int index;
            cout << "\nIntroduceti indexul locatiei de sters (1-" << nrLocatii << "): ";
            cin >> index;
            if (index < 1 || index > nrLocatii)
            {
                cout << "Index invalid!\n";
                break;
            }
            Locatie* temp = new Locatie[nrLocatii - 1];
            for (int i = 0, j = 0; i < nrLocatii; i++)
            {
                if (i != index - 1) temp[j++] = locatii[i];
            }
            delete[] locatii;
            locatii = temp;
            nrLocatii--;
            cout << "\nLocatie stearsa cu succes!\n";
            break;
        }
        case 5:
        {
            int index;
            cout << "\nIntroduceti indexul locatiei: ";
            cin >> index;
            if (index < 1 || index > nrLocatii)
            {
                cout << "Index invalid!\n";
                break;
            }
            locatii[index - 1].afisareDescriere();
            break;
        }
        case 6:
        case 7:
        {
            int i1, i2;
            cout << "Index 1: ";
            cin >> i1;
            cout << "Index 2: ";
            cin >> i2;
            if (i1 < 1 || i1 > nrLocatii || i2 < 1 || i2 > nrLocatii)
            {
                cout << "Index invalid!\n";
                break;
            }
            if (optiune == 6)
            {
                if (locatii[i1 - 1] >= locatii[i2 - 1])
                    cout << "Locatia " << locatii[i1 - 1].getNume() << " are capacitate mai mare sau egala.\n";
                else
                    cout << "Locatia " << locatii[i2 - 1].getNume() << " are capacitate mai mare.\n";
            }
            else
            {
                if (locatii[i1 - 1] == locatii[i2 - 1])
                    cout << "Locatiile au aceeasi capacitate.\n";
                else
                    cout << "Capacitatile sunt diferite.\n";
            }
            break;
        }
        case 8:
        {
            int index;
            cout << "Indexul locatiei: ";
            cin >> index;
            if (index < 1 || index > nrLocatii)
            {
                cout << "Index invalid!\n";
                break;
            }
            ++locatii[index - 1];
            cout << "Capacitate noua: " << locatii[index - 1].getCapacitate() << " locuri\n";
            break;
        }
        case 9:
        {
            int index, val;
            cout << "Indexul locatiei: ";
            cin >> index;
            cout << "Locuri de adaugat: ";
            cin >> val;
            if (index < 1 || index > nrLocatii)
            {
                cout << "Index invalid!\n";
                break;
            }
            Locatie rez = locatii[index - 1] + val;
            cout << "Capacitate noua: " << rez.getCapacitate() << " locuri\n";
            break;
        }
        case 10:
        {
            int index, val;
            cout << "Indexul locatiei: ";
            cin >> index;
            cout << "Factor de inmultire: ";
            cin >> val;
            if (index < 1 || index > nrLocatii)
            {
                cout << "Index invalid!\n";
                break;
            }
            Locatie rez = val * locatii[index - 1];
            cout << "Capacitate noua: " << rez.getCapacitate() << " locuri\n";
            break;
        }
        case 11:
            cout << "\nRevenire la meniul principal...\n";
            break;
        default:
            cout << "\nOptiune invalida.\n";
        }
    }
    while (optiune != 11);

    delete[] locatii;
}

int Bilet::nrBilete = -1;

void meniu_bilet()
{
    vector<Bilet> bilete;
    int opt;
    do
    {
        cout << "\n===== MENIU BILETE =====\n";
        cout << "1. Adauga bilet\n2. Afiseaza bilete\n3. Modifica bilet\n4. Sterge bilet\n";
        cout << "5. Incrementare pret bilet (++ operator)\n";
        cout << "6. Aduna valoare la pret (+ operator)\n";
        cout << "7. Inmulteste pretul cu factor (* operator)\n";
        cout << "8. Verifica egalitatea intre doua bilete (==)\n";
        cout << "9. Compara doua bilete (pret >=)\n";
        cout << "10. Afiseaza litera din tipul biletului ([] operator)\n";
        cout << "0. Iesire\n";
        cout << "Optiune: ";
        cin >> opt;
        switch (opt)
        {
        case 1:
        {
            Bilet b;
            cin >> b;
            bilete.push_back(b);
            break;
        }
        case 2:
        {
            for (size_t i = 0; i < bilete.size(); i++)
            {
                cout << bilete[i] << endl;
            }
            break;
        }
        case 3:
        {
            int i;
            cout << "Index bilet: ";
            cin >> i;
            if (i >= 1 && i <= (int)bilete.size()) cin >> bilete[i - 1];
            break;
        }
        case 4:
        {
            int i;
            cout << "Index bilet: ";
            cin >> i;
            if (i >= 1 && i <= (int)bilete.size()) bilete.erase(bilete.begin() + i - 1);
            break;
        }
        case 5:
        {
            int i;
            cout << "Index bilet: ";
            cin >> i;
            if (i >= 1 && i <= (int)bilete.size())
            {
                ++bilete[i - 1];
                cout << "Pret nou: " << bilete[i - 1].getPret() << " RON\n";
            }
            break;
        }
        case 6:
        {
            int i;
            float val;
            cout << "Index bilet: ";
            cin >> i;
            cout << "Valoare de adaugat: ";
            cin >> val;
            if (i >= 1 && i <= (int)bilete.size())
            {
                Bilet rezultat = bilete[i - 1] + val;
                cout << "Pret nou: " << rezultat.getPret() << " RON\n";
            }
            break;
        }
        case 7:
        {
            int i, factor;
            cout << "Index bilet: ";
            cin >> i;
            cout << "Factor: ";
            cin >> factor;
            if (i >= 1 && i <= (int)bilete.size())
            {
                Bilet rezultat = factor * bilete[i - 1];
                cout << "Pret nou: " << rezultat.getPret() << " RON\n";
            }
            break;
        }
        case 8:
        {
            int i1, i2;
            cout << "Index bilet 1: ";
            cin >> i1;
            cout << "Index bilet 2: ";
            cin >> i2;
            if (i1 >= 1 && i1 <= (int)bilete.size() && i2 >= 1 && i2 <= (int)bilete.size())
            {
                if (bilete[i1 - 1] == bilete[i2 - 1]) cout << "Biletele sunt egale.\n";
                else cout << "Biletele sunt diferite.\n";
            }
            break;
        }
        case 9:
        {
            int i1, i2;
            cout << "Index bilet 1: ";
            cin >> i1;
            cout << "Index bilet 2: ";
            cin >> i2;
            if (i1 >= 1 && i1 <= (int)bilete.size() && i2 >= 1 && i2 <= (int)bilete.size())
            {
                if (bilete[i1 - 1] >= bilete[i2 - 1]) cout << "Biletul 1 are pret mai mare sau egal.\n";
                else cout << "Biletul 2 are pret mai mare.\n";
            }
            break;
        }
        case 10:
        {
            int i, poz;
            cout << "Index bilet: ";
            cin >> i;
            cout << "Pozitie caracter in tip: ";
            cin >> poz;
            if (i >= 1 && i <= (int)bilete.size())
            {
                try
                {
                    cout << "Caracterul este: " << bilete[i - 1][poz] << endl;
                }
                catch (const out_of_range& e)
                {
                    cout << e.what() << endl;
                }
            }
            break;
        }
        }
    }
    while (opt != 0);
}



//////////////////////////////////PARTEA 2////////////////////////////////////////////////





// Clasa abstracta (interfata) IActivitate
class IActivitate {
public:
    virtual void afiseazaActivitate() const = 0;
    virtual void modificaActivitate() = 0;
    virtual ~IActivitate() { cout << "Destructor IActivitate" << endl; }
};

// Clasa Cultural – deriva virtual din IActivitate
class Cultural : virtual public IActivitate {
protected:
    char* numeArtist;
    string tipEveniment;
    double durata;
    int popularitate;

public:
    // Constructor fara parametri
    Cultural() {
        numeArtist = new char[strlen("Anonim") + 1];
        strcpy(numeArtist, "Anonim");
        tipEveniment = "Necunoscut";
        durata = 0.0;
        popularitate = 0;
        cout << "Constructor fara parametri Cultural" << endl;
    }

    // Constructor cu toti parametrii
    Cultural(const char* numeArtist, const string& tipEveniment, double durata, int popularitate) {
        this->numeArtist = new char[strlen(numeArtist) + 1];
        strcpy(this->numeArtist, numeArtist);
        this->tipEveniment = tipEveniment;
        this->durata = durata;
        this->popularitate = popularitate;
        cout << "Constructor cu toti parametrii Cultural" << endl;
    }

    // Constructor cu doi parametri
    Cultural(const char* numeArtist, const string& tipEveniment) {
        this->numeArtist = new char[strlen(numeArtist) + 1];
        strcpy(this->numeArtist, numeArtist);
        this->tipEveniment = tipEveniment;
        this->durata = 2.0;
        this->popularitate = 50;
        cout << "Constructor cu doi parametri Cultural" << endl;
    }

    // Constructor cu trei parametri
    Cultural(const char* numeArtist, double durata, int popularitate) {
        this->numeArtist = new char[strlen(numeArtist) + 1];
        strcpy(this->numeArtist, numeArtist);
        this->tipEveniment = "Spectacol";
        this->durata = durata;
        this->popularitate = popularitate;
        cout << "Constructor cu trei parametri Cultural" << endl;
    }

    // Constructor de copiere
    Cultural(const Cultural& other) {
        this->numeArtist = new char[strlen(other.numeArtist) + 1];
        strcpy(this->numeArtist, other.numeArtist);
        this->tipEveniment = other.tipEveniment;
        this->durata = other.durata;
        this->popularitate = other.popularitate;
        cout << "Constructor de copiere Cultural" << endl;
    }

    // Destructor
    virtual ~Cultural() {
        delete[] numeArtist;
        cout << "Destructor Cultural" << endl;
    }

    // Operator =
    Cultural& operator=(const Cultural& other) {
        if (this != &other) {
            delete[] numeArtist;
            numeArtist = new char[strlen(other.numeArtist) + 1];
            strcpy(numeArtist, other.numeArtist);
            tipEveniment = other.tipEveniment;
            durata = other.durata;
            popularitate = other.popularitate;
        }
        return *this;
    }

    // Implementarea functiei virtuale
    virtual void afiseazaActivitate() const {
        cout << "Activitate culturala: " << numeArtist << endl;
        cout << "Tip eveniment: " << tipEveniment << endl;
        cout << "Durata: " << durata << " ore" << endl;
        cout << "Popularitate: " << popularitate << "/100" << endl;
    }

    virtual void modificaActivitate() {
        char numeTemp[100];
        cout << "Noul nume al artistului: ";
        cin >> ws;
        cin.getline(numeTemp, 100);

        delete[] numeArtist;
        numeArtist = new char[strlen(numeTemp) + 1];
        strcpy(numeArtist, numeTemp);

        cout << "Noul tip de eveniment: ";
        getline(cin, tipEveniment);

        cout << "Noua durata (ore): ";
        cin >> durata;

        cout << "Noua popularitate (0-100): ";
        cin >> popularitate;
    }

    // Supraincarcare operatori pentru stream
    friend ostream& operator<<(ostream& out, const Cultural& c) {
        out << "Nume artist: " << c.numeArtist << endl;
        out << "Tip eveniment: " << c.tipEveniment << endl;
        out << "Durata: " << c.durata << " ore" << endl;
        out << "Popularitate: " << c.popularitate << "/100" << endl;
        return out;
    }

    friend istream& operator>>(istream& in, Cultural& c) {
        char numeTemp[100];
        cout << "Numele artistului: ";
        in >> ws;
        in.getline(numeTemp, 100);

        delete[] c.numeArtist;
        c.numeArtist = new char[strlen(numeTemp) + 1];
        strcpy(c.numeArtist, numeTemp);

        cout << "Tipul evenimentului: ";
        getline(in, c.tipEveniment);

        cout << "Durata (ore): ";
        in >> c.durata;

        cout << "Popularitate (0-100): ";
        in >> c.popularitate;

        return in;
    }
};

// Clasa Sportiv – deriva virtual din IActivitate
class Sportiv : virtual public IActivitate {
protected:
    string tipSport;
    int numarParticipanti;
    bool esteCompetitie;
    double durataSport;

public:
    // Constructor fara parametri
    Sportiv() : tipSport("Necunoscut"), numarParticipanti(0), esteCompetitie(false), durataSport(0.0) {
        cout << "Constructor fara parametri Sportiv" << endl;
    }

    // Constructor cu toti parametrii
    Sportiv(const string& tipSport, int numarParticipanti, bool esteCompetitie, double durataSport)
        : tipSport(tipSport), numarParticipanti(numarParticipanti), esteCompetitie(esteCompetitie), durataSport(durataSport) {
        cout << "Constructor cu toti parametrii Sportiv" << endl;
    }

    // Constructor cu doi parametri
    Sportiv(const string& tipSport, int numarParticipanti)
        : tipSport(tipSport), numarParticipanti(numarParticipanti), esteCompetitie(true), durataSport(2.0) {
        cout << "Constructor cu doi parametri Sportiv" << endl;
    }

    // Constructor cu trei parametri
    Sportiv(const string& tipSport, bool esteCompetitie, double durataSport)
        : tipSport(tipSport), numarParticipanti(20), esteCompetitie(esteCompetitie), durataSport(durataSport) {
        cout << "Constructor cu trei parametri Sportiv" << endl;
    }

    // Constructor de copiere
    Sportiv(const Sportiv& other)
        : tipSport(other.tipSport), numarParticipanti(other.numarParticipanti),
          esteCompetitie(other.esteCompetitie), durataSport(other.durataSport) {
        cout << "Constructor de copiere Sportiv" << endl;
    }

    // Destructor
    virtual ~Sportiv() {
        cout << "Destructor Sportiv" << endl;
    }

    // Operator =
    Sportiv& operator=(const Sportiv& other) {
        if (this != &other) {
            tipSport = other.tipSport;
            numarParticipanti = other.numarParticipanti;
            esteCompetitie = other.esteCompetitie;
            durataSport = other.durataSport;
        }
        return *this;
    }

    // Implementarea functiei virtuale
    virtual void afiseazaActivitate() const {
        cout << "Activitate sportiva: " << tipSport << endl;
        cout << "Numar participanti: " << numarParticipanti << endl;
        cout << "Este competitie: " << (esteCompetitie ? "Da" : "Nu") << endl;
        cout << "Durata: " << durataSport << " ore" << endl;
    }

    virtual void modificaActivitate() {
        cout << "Noul tip de sport: ";
        cin >> ws;
        getline(cin, tipSport);

        cout << "Noul numar de participanti: ";
        cin >> numarParticipanti;

        cout << "Este competitie (1-Da, 0-Nu): ";
        cin >> esteCompetitie;

        cout << "Noua durata (ore): ";
        cin >> durataSport;
    }

    // Supraincarcare operatori pentru stream
    friend ostream& operator<<(ostream& out, const Sportiv& s) {
        out << "Tip sport: " << s.tipSport << endl;
        out << "Numar participanti: " << s.numarParticipanti << endl;
        out << "Este competitie: " << (s.esteCompetitie ? "Da" : "Nu") << endl;
        out << "Durata: " << s.durataSport << " ore" << endl;
        return out;
    }

    friend istream& operator>>(istream& in, Sportiv& s) {
        cout << "Tipul sportului: ";
        in >> ws;
        getline(in, s.tipSport);

        cout << "Numarul de participanti: ";
        in >> s.numarParticipanti;

        cout << "Este competitie (1-Da, 0-Nu): ";
        in >> s.esteCompetitie;

        cout << "Durata (ore): ";
        in >> s.durataSport;

        return in;
    }
};

// Clasa EvenimentSpecial – mosteneste din Cultural si Sportiv (diamond inheritance)
class EvenimentSpecial : public Cultural, public Sportiv {
private:
    string numeEveniment;
    string data;
    double pret;
    bool vizibilitate;

public:
    // Constructor cu patru parametri: numeEveniment, data, pret, vizibilitate
    EvenimentSpecial(const char* numeEveniment, const char* data, double pret, bool vizibilitate)
        : Cultural(), Sportiv(),  // se folosesc constructorii default pentru Cultural si Sportiv
          numeEveniment(numeEveniment), data(data), pret(pret), vizibilitate(vizibilitate) {
        cout << "Constructor cu patru parametri EvenimentSpecial" << endl;
    }

    // Constructor fara parametri
    EvenimentSpecial() : Cultural(), Sportiv(), numeEveniment("Eveniment Special"), data("01.01.2025"), pret(0.0), vizibilitate(true) {
        cout << "Constructor fara parametri EvenimentSpecial" << endl;
    }

    // Constructor cu toti parametrii
    EvenimentSpecial(const char* numeArtist, const string& tipEveniment, double durata, int popularitate,
                    const string& tipSport, int numarParticipanti, bool esteCompetitie, double durataSport,
                    const string& numeEveniment, const string& data, double pret, bool vizibilitate)
        : Cultural(numeArtist, tipEveniment, durata, popularitate),
          Sportiv(tipSport, numarParticipanti, esteCompetitie, durataSport),
          numeEveniment(numeEveniment), data(data), pret(pret), vizibilitate(vizibilitate) {
        cout << "Constructor cu toti parametrii EvenimentSpecial" << endl;
    }

    // Constructor cu doi parametri
    EvenimentSpecial(const string& numeEveniment, const string& data)
        : Cultural(), Sportiv(), numeEveniment(numeEveniment), data(data), pret(100.0), vizibilitate(true) {
        cout << "Constructor cu doi parametri EvenimentSpecial" << endl;
    }

    // Constructor cu trei parametri
    EvenimentSpecial(const string& numeEveniment, double pret, bool vizibilitate)
        : Cultural(), Sportiv(), numeEveniment(numeEveniment), data("01.01.2025"), pret(pret), vizibilitate(vizibilitate) {
        cout << "Constructor cu trei parametri EvenimentSpecial" << endl;
    }

    // Constructor de copiere
    EvenimentSpecial(const EvenimentSpecial& other)
        : Cultural(other), Sportiv(other),
          numeEveniment(other.numeEveniment), data(other.data), pret(other.pret), vizibilitate(other.vizibilitate) {
        cout << "Constructor de copiere EvenimentSpecial" << endl;
    }

    // Destructor
    virtual ~EvenimentSpecial() {
        cout << "Destructor EvenimentSpecial" << endl;
    }

    // Operator =
    EvenimentSpecial& operator=(const EvenimentSpecial& other) {
        if (this != &other) {
            Cultural::operator=(other);
            Sportiv::operator=(other);
            numeEveniment = other.numeEveniment;
            data = other.data;
            pret = other.pret;
            vizibilitate = other.vizibilitate;
        }
        return *this;
    }

    // Suprascrierea functiei virtuale din IActivitate
    virtual void afiseazaActivitate() const {
        cout << "\n===== EVENIMENT SPECIAL =====" << endl;
        cout << "Nume eveniment: " << numeEveniment << endl;
        cout << "Data: " << data << endl;
        cout << "Pret: " << pret << " lei" << endl;
        cout << "Vizibilitate: " << (vizibilitate ? "Public" : "Privat") << endl;
        cout << "\n--- Componenta culturala ---" << endl;
        cout << "Artist: " << numeArtist << endl;
        cout << "Tip eveniment: " << tipEveniment << endl;
        cout << "Durata culturala: " << durata << " ore" << endl;
        cout << "Popularitate: " << popularitate << "/100" << endl;
        cout << "\n--- Componenta sportiva ---" << endl;
        cout << "Sport: " << tipSport << endl;
        cout << "Participanti: " << numarParticipanti << endl;
        cout << "Este competitie: " << (esteCompetitie ? "Da" : "Nu") << endl;
        cout << "Durata sportiva: " << durataSport << " ore" << endl;
    }

    virtual void modificaActivitate() {
        cout << "Modificare eveniment special:" << endl;
        cout << "Noul nume al evenimentului: ";
        cin >> ws;
        getline(cin, numeEveniment);

        cout << "Noua data (format: ZZ.LL.AAAA): ";
        getline(cin, data);

        cout << "Noul pret: ";
        cin >> pret;

        cout << "Vizibilitate (1-Public, 0-Privat): ";
        cin >> vizibilitate;

        cout << "\nModificare componenta culturala:" << endl;
        Cultural::modificaActivitate();

        cout << "\nModificare componenta sportiva:" << endl;
        Sportiv::modificaActivitate();
    }

    // Supraincarcarea operatorului << pentru EvenimentSpecial
    friend ostream& operator<<(ostream& out, const EvenimentSpecial& es) {
        out << "=== EVENIMENT SPECIAL ===" << endl;
        out << "Nume eveniment: " << es.numeEveniment << endl;
        out << "Data: " << es.data << endl;
        out << "Pret: " << es.pret << " lei" << endl;
        out << "Vizibilitate: " << (es.vizibilitate ? "Public" : "Privat") << endl;
        out << "\n--- Componenta culturala ---" << endl;
        out << static_cast<const Cultural&>(es);
        out << "\n--- Componenta sportiva ---" << endl;
        out << static_cast<const Sportiv&>(es);
        return out;
    }

    // Supraincarcarea operatorului >> pentru EvenimentSpecial
    friend istream& operator>>(istream& in, EvenimentSpecial& es) {
        cout << "=== ADAUGARE EVENIMENT SPECIAL ===" << endl;

        cout << "Numele evenimentului: ";
        in >> ws;
        getline(in, es.numeEveniment);

        cout << "Data evenimentului (format: ZZ.LL.AAAA): ";
        getline(in, es.data);

        cout << "Pretul biletului: ";
        in >> es.pret;

        cout << "Vizibilitate (1-Public, 0-Privat): ";
        in >> es.vizibilitate;

        cout << "\n=== COMPONENTA CULTURALA ===" << endl;
        in >> static_cast<Cultural&>(es);

        cout << "\n=== COMPONENTA SPORTIVA ===" << endl;
        in >> static_cast<Sportiv&>(es);

        return in;
    }

    // Getteri
    string getNumeEveniment() const { return numeEveniment; }
    string getData() const { return data; }
    double getPret() const { return pret; }
    bool getVizibilitate() const { return vizibilitate; }

    // Setteri
    void setNumeEveniment(const string& numeEveniment) { this->numeEveniment = numeEveniment; }
    void setData(const string& data) { this->data = data; }
    void setPret(double pret) { this->pret = pret; }
    void setVizibilitate(bool vizibilitate) { this->vizibilitate = vizibilitate; }
};

// Meniu pentru Eveniment Special
void meniu_eveniment_special() {
    vector<EvenimentSpecial*> evenimente;
    int opt;

    do {
        cout << "\n===== MENIU EVENIMENT SPECIAL =====\n";
        cout << "1. Adauga eveniment special\n";
        cout << "2. Afiseaza evenimente speciale\n";
        cout << "3. Modifica eveniment special\n";
        cout << "4. Sterge eveniment special\n";
        cout << "5. Afiseaza activitatea evenimentului special (polimorfism)\n";
        cout << "6. Exemplu de utilizare vector de pointeri la interfata IActivitate\n";
        cout << "0. Revenire la meniul principal\n";
        cout << "Optiune: ";
        cin >> opt;

        switch(opt) {
            case 1: {
                EvenimentSpecial* es = new EvenimentSpecial();
                cin >> *es;
                evenimente.push_back(es);
                cout << "Eveniment special adaugat cu succes!" << endl;
                break;
            }
            case 2: {
                if (evenimente.empty()) {
                    cout << "Nu exista evenimente speciale inregistrate!" << endl;
                } else {
                    cout << "\n=== LISTA EVENIMENTE SPECIALE ===" << endl;
                    for (size_t i = 0; i < evenimente.size(); i++) {
                        cout << "\nEvenimentul #" << i + 1 << endl;
                        cout << *evenimente[i] << endl;
                    }
                }
                break;
            }
            case 3: {
                if (evenimente.empty()) {
                    cout << "Nu exista evenimente speciale de modificat!" << endl;
                } else {
                    int index;
                    cout << "Introduceti indexul evenimentului special (1-" << evenimente.size() << "): ";
                    cin >> index;

                    if (index >= 1 && index <= (int)evenimente.size()) {
                        evenimente[index - 1]->modificaActivitate();
                        cout << "Eveniment special modificat cu succes!" << endl;
                    } else {
                        cout << "Index invalid!" << endl;
                    }
                }
                break;
            }
            case 4: {
                if (evenimente.empty()) {
                    cout << "Nu exista evenimente speciale de sters!" << endl;
                } else {
                    int index;
                    cout << "Introduceti indexul evenimentului special (1-" << evenimente.size() << "): ";
                    cin >> index;

                    if (index >= 1 && index <= (int)evenimente.size()) {
                        delete evenimente[index - 1]; // Eliberare memorie
                        evenimente.erase(evenimente.begin() + index - 1);
                        cout << "Eveniment special sters cu succes!" << endl;
                    } else {
                        cout << "Index invalid!" << endl;
                    }
                }
                break;
            }
            case 5: {
                if (evenimente.empty()) {
                    cout << "Nu exista evenimente speciale!" << endl;
                } else {
                    int index;
                    cout << "Introduceti indexul evenimentului special (1-" << evenimente.size() << "): ";
                    cin >> index;

                    if (index >= 1 && index <= (int)evenimente.size()) {
                        // Demonstratie de polimorfism - apelarea functiei virtuale
                        IActivitate* act = evenimente[index - 1];
                        cout << "\nAfisare prin intermediul interfetei IActivitate:" << endl;
                        act->afiseazaActivitate();
                    } else {
                        cout << "Index invalid!" << endl;
                    }
                }
                break;
            }
            case 6: {
                // Exemplu de utilizare a polimorfismului cu vector de pointeri la interfata
                cout << "\n=== Demonstartie polimorfism cu vector de interfete ===" << endl;

                //  Obiecte create pentru demonstratie
                Cultural* c = new Cultural("Mozart", "Concert", 3.5, 95);
                Sportiv* s = new Sportiv("Fotbal", 22, true, 2.0);
                EvenimentSpecial* es = new EvenimentSpecial("Festival Sport-Cultura", "15.06.2025", 150.0, true);

                // Vector de pointeri la interfata IActivitate
                vector<IActivitate*> activitati;
                activitati.push_back(c);
                activitati.push_back(s);
                activitati.push_back(es);

                // Demonstrare polimorfismului apeland aceeasi metoda pentru obiecte diferite
                for (size_t i = 0; i < activitati.size(); i++) {
                    cout << "\nActivitatea #" << i + 1 << ":" << endl;
                    activitati[i]->afiseazaActivitate();
                    cout << endl;
                }

                // Eliberare memorie
                for (size_t i = 0; i < activitati.size(); i++) {
                    delete activitati[i];
                }


                break;
            }
            case 0:
                // Curatare memorie
                for (size_t i = 0; i < evenimente.size(); i++) {
                    delete evenimente[i];
                }
                evenimente.clear();
                cout << "Revenire la meniul principal..." << endl;
                break;
            default:
                cout << "Optiune invalida! Incercati din nou." << endl;
        }
    } while (opt != 0);
}

////////////////////////////////////PARTEA 2//////////////////////////////////////////////////

void meniu_principal() {
    int optiune = 0;
    do {
        cout << "\n===== MENIU PRINCIPAL =====" << endl;
        cout << "1. Meniu Participant" << endl;
        cout << "2. Meniu Eveniment" << endl;
        cout << "3. Meniu Bilet" << endl;
        cout << "4. Meniu Locatie" << endl;
        cout << "5. Meniu Eveniment Special" << endl;
        cout << "6. Iesire" << endl;
        cout << "Alege optiunea: ";
        cin >> optiune;
        switch(optiune) {
            case 1:
                meniu_participant();
                break;
            case 2:
                meniu_eveniment();
                break;
            case 3:
                meniu_bilet();
                break;
            case 4:
                meniu_locatie();
                break;
            case 5:
                meniu_eveniment_special();
                break;
            case 6:
                cout << "\nLa revedere!" << endl;
                break;
            default:
                cout << "\nOptiune invalida. Incercati din nou." << endl;
        }
    } while(optiune != 6);
}

int main()
{
    meniu_principal();
    return 0;
}
