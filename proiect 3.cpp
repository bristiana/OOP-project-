
#include<bits/stdc++.h>
using namespace std;

class Eveniment;
class Concert;
class Festival;
class Conferinta;


// excepții personalizate
class FileException : public exception
{
private:
    string message;
public:
    FileException(const string& msg) : message(msg) {}
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

class InvalidDataException : public exception
{
private:
    string message;
public:
    InvalidDataException(const string& msg) : message(msg) {}
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

class NotFoundException : public exception
{
private:
    string message;
public:
    NotFoundException(const string& msg) : message(msg) {}
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

// Clasa Template - Container generic pentru orice tip de date
template <typename T>
class Container
{
private:
    vector<T> elements;
public:

    Container() {}

    Container(const vector<T>& elems) : elements(elems) {}

    Container(const Container& other) : elements(other.elements) {}

    Container& operator=(const Container& other)
    {
        if (this != &other)
        {
            elements = other.elements;
        }
        return *this;
    }


    ~Container() {}


    void add(const T& elem)
    {
        elements.push_back(elem);
    }


    vector<T> getAll() const
    {
        return elements;
    }

    // Metode template
    template <typename Func>
    void forEach(Func operation)
    {
        for (auto& elem : elements)
        {
            operation(elem);
        }
    }

    template <typename Predicate>
    vector<T> filter(Predicate condition)
    {
        vector<T> result;
        for (const auto& elem : elements)
        {
            if (condition(elem))
            {
                result.push_back(elem);
            }
        }
        return result;
    }
};

// Clasa de baza - Eveniment (Parinte)
class Eveniment
{
protected:
    string nume;
    string organizator;
    string data;
    double pretBilet;

public:

    Eveniment() : nume(""), organizator(""), data(""), pretBilet(0.0) {}


    Eveniment(const string& n, const string& org, const string& d, double pret)
        : nume(n), organizator(org), data(d), pretBilet(pret)
    {
        if (pret < 0)
        {
            throw InvalidDataException("Pretul biletului nu poate fi negativ!");
        }
    }


    Eveniment(const Eveniment& other)
        : nume(other.nume), organizator(other.organizator), data(other.data), pretBilet(other.pretBilet) {}


    Eveniment& operator=(const Eveniment& other)
    {
        if (this != &other)
        {
            nume = other.nume;
            organizator = other.organizator;
            data = other.data;
            pretBilet = other.pretBilet;
        }
        return *this;
    }


    virtual ~Eveniment() {}


    friend istream& operator>>(istream& is, Eveniment& ev)
    {
        cout << "Nume eveniment: ";
        is.ignore();
        getline(is, ev.nume);
        cout << "Organizator: ";
        getline(is, ev.organizator);
        cout << "Data (DD/MM/YYYY): ";
        getline(is, ev.data);
        cout << "Pret bilet: ";
        is >> ev.pretBilet;

        if (ev.pretBilet < 0)
        {
            throw InvalidDataException("Pretul biletului nu poate fi negativ!");
        }

        return is;
    }


    friend ostream& operator<<(ostream& os, const Eveniment& ev)
    {
        os << "Nume: " << ev.nume << "\n";
        os << "Organizator: " << ev.organizator << "\n";
        os << "Data: " << ev.data << "\n";
        os << "Pret bilet: " << ev.pretBilet << " LEI\n";
        return os;
    }


    virtual void afisare() const
    {
        cout << *this;
    }

    virtual string getTip() const
    {
        return "Eveniment";
    }


    string getNume() const
    {
        return nume;
    }
    string getOrganizator() const
    {
        return organizator;
    }
    string getData() const
    {
        return data;
    }
    double getPretBilet() const
    {
        return pretBilet;
    }
};

// Clasa derivata - Concert (Copil)
class Concert : public Eveniment
{
protected:
    string artist;
    string gen;
    int durata;

public:

    Concert() : Eveniment(), artist(""), gen(""), durata(0) {}


    Concert(const string& n, const string& org, const string& d, double pret,
            const string& art, const string& g, int dur)
        : Eveniment(n, org, d, pret), artist(art), gen(g), durata(dur)
    {
        if (dur <= 0)
        {
            throw InvalidDataException("Durata concertului trebuie sa fie pozitiva!");
        }
    }


    Concert(const Concert& other)
        : Eveniment(other), artist(other.artist), gen(other.gen), durata(other.durata) {}


    Concert& operator=(const Concert& other)
    {
        if (this != &other)
        {
            Eveniment::operator=(other);
            artist = other.artist;
            gen = other.gen;
            durata = other.durata;
        }
        return *this;
    }


    ~Concert() override {}


    friend istream& operator>>(istream& is, Concert& concert)
    {
        is >> static_cast<Eveniment&>(concert);
        cout << "Artist: ";
        is.ignore();
        getline(is, concert.artist);
        cout << "Gen muzical: ";
        getline(is, concert.gen);
        cout << "Durata (minute): ";
        is >> concert.durata;

        if (concert.durata <= 0)
        {
            throw InvalidDataException("Durata concertului trebuie sa fie pozitiva!");
        }

        return is;
    }


    friend ostream& operator<<(ostream& os, const Concert& concert)
    {
        os << static_cast<const Eveniment&>(concert);
        os << "Artist: " << concert.artist << "\n";
        os << "Gen muzical: " << concert.gen << "\n";
        os << "Durata: " << concert.durata << " minute\n";
        return os;
    }


    void afisare() const override
    {
        cout << *this;
    }

    string getTip() const override
    {
        return "Concert";
    }


    string getArtist() const
    {
        return artist;
    }
    string getGen() const
    {
        return gen;
    }
    int getDurata() const
    {
        return durata;
    }
};

// Clasa derivata - Festival (Nepot)
class Festival : public Concert
{
private:
    int numarZile;
    string locatie;

public:

    Festival() : Concert(), numarZile(0), locatie("") {}


    Festival(const string& n, const string& org, const string& d, double pret,
             const string& art, const string& g, int dur, int zile, const string& loc)
        : Concert(n, org, d, pret, art, g, dur), numarZile(zile), locatie(loc)
    {
        if (zile <= 0)
        {
            throw InvalidDataException("Numarul de zile trebuie sa fie pozitiv!");
        }
    }


    Festival(const Festival& other)
        : Concert(other), numarZile(other.numarZile), locatie(other.locatie) {}


    Festival& operator=(const Festival& other)
    {
        if (this != &other)
        {
            Concert::operator=(other);
            numarZile = other.numarZile;
            locatie = other.locatie;
        }
        return *this;
    }


    ~Festival() override {}


    friend istream& operator>>(istream& is, Festival& festival)
    {
        is >> static_cast<Concert&>(festival);
        cout << "Numar zile: ";
        is >> festival.numarZile;
        cout << "Locatie: ";
        is.ignore();
        getline(is, festival.locatie);

        if (festival.numarZile <= 0)
        {
            throw InvalidDataException("Numarul de zile trebuie sa fie pozitiv!");
        }

        return is;
    }

    friend ostream& operator<<(ostream& os, const Festival& festival)
    {
        os << static_cast<const Concert&>(festival);
        os << "Numar zile: " << festival.numarZile << "\n";
        os << "Locatie: " << festival.locatie << "\n";
        return os;
    }


    void afisare() const override
    {
        cout << *this;
    }

    string getTip() const override
    {
        return "Festival";
    }


    int getNumarZile() const
    {
        return numarZile;
    }
    string getLocatie() const
    {
        return locatie;
    }
};

// Clasa derivata - Conferinta (Copil)
class Conferinta : public Eveniment
{
private:
    string subiect;
    int numarParticipanti;

public:

    Conferinta() : Eveniment(), subiect(""), numarParticipanti(0) {}


    Conferinta(const string& n, const string& org, const string& d, double pret,
               const string& sub, int nr)
        : Eveniment(n, org, d, pret), subiect(sub), numarParticipanti(nr)
    {
        if (nr <= 0)
        {
            throw InvalidDataException("Numarul de participanti trebuie sa fie pozitiv!");
        }
    }


    Conferinta(const Conferinta& other)
        : Eveniment(other), subiect(other.subiect), numarParticipanti(other.numarParticipanti) {}


    Conferinta& operator=(const Conferinta& other)
    {
        if (this != &other)
        {
            Eveniment::operator=(other);
            subiect = other.subiect;
            numarParticipanti = other.numarParticipanti;
        }
        return *this;
    }


    ~Conferinta() override {}


    friend istream& operator>>(istream& is, Conferinta& conf)
    {
        is >> static_cast<Eveniment&>(conf);
        cout << "Subiect: ";
        is.ignore();
        getline(is, conf.subiect);
        cout << "Numar participanti: ";
        is >> conf.numarParticipanti;

        if (conf.numarParticipanti <= 0)
        {
            throw InvalidDataException("Numarul de participanti trebuie sa fie pozitiv!");
        }

        return is;
    }


    friend ostream& operator<<(ostream& os, const Conferinta& conf)
    {
        os << static_cast<const Eveniment&>(conf);
        os << "Subiect: " << conf.subiect << "\n";
        os << "Numar participanti: " << conf.numarParticipanti << "\n";
        return os;
    }


    void afisare() const override
    {
        cout << *this;
    }

    string getTip() const override
    {
        return "Conferinta";
    }


    string getSubiect() const
    {
        return subiect;
    }
    int getNumarParticipanti() const
    {
        return numarParticipanti;
    }
};



// Clasa Singleton
class Meniu
{
private:
    static Meniu* instance;
    Container<shared_ptr<Eveniment>> evenimente;
    map<string, list<shared_ptr<Eveniment>>> organizatorEventMap;

    set<string> numeEventSet;

    Meniu() {}


    void adaugaEveniment(shared_ptr<Eveniment> ev)
    {
        evenimente.add(ev);
        organizatorEventMap[ev->getOrganizator()].push_back(ev);
        numeEventSet.insert(ev->getNume());
    }

public:

    static Meniu* getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Meniu();
        }
        return instance;
    }


    static void deleteInstance()
    {
        if (instance != nullptr)
        {
            delete instance;
            instance = nullptr;
        }
    }


    ~Meniu()
    {

    }


    Meniu(const Meniu&) = delete;
    Meniu& operator=(const Meniu&) = delete;


    void citireEvenimentNou()
    {
        cout << "Alegeti tipul evenimentului:\n";
        cout << "1. Eveniment general\n";
        cout << "2. Concert\n";
        cout << "3. Festival\n";
        cout << "4. Conferinta\n";

        int optiune;
        cin >> optiune;

        try
        {
            shared_ptr<Eveniment> eveniment;

            switch (optiune)
            {
            case 1:
            {
                eveniment = make_shared<Eveniment>();
                cin >> *eveniment;
                break;
            }
            case 2:
            {
                auto concert = make_shared<Concert>();
                cin >> *concert;
                eveniment = concert;
                break;
            }
            case 3:
            {
                auto festival = make_shared<Festival>();
                cin >> *festival;
                eveniment = festival;
                break;
            }
            case 4:
            {
                auto conferinta = make_shared<Conferinta>();
                cin >> *conferinta;
                eveniment = conferinta;
                break;
            }
            default:
                throw InvalidDataException("Optiune invalida!");
            }


            if (numeEventSet.find(eveniment->getNume()) != numeEventSet.end())
            {
                throw InvalidDataException("Un eveniment cu acest nume exista deja!");
            }

            adaugaEveniment(eveniment);
            cout << "Eveniment adaugat cu succes!\n";
        }
        catch (const exception& e)
        {
            cout << "Eroare: " << e.what() << "\n";
        }
    }


    void afisareEvenimente()
    {
        cout << "Lista evenimentelor:\n";
        int index = 1;

        if (evenimente.getAll().empty())
        {
            cout << "Nu exista evenimente inregistrate.\n";
            return;
        }

        evenimente.forEach([&index](const shared_ptr<Eveniment>& ev)
        {
            cout << "\n#" << index++ << " - " << ev->getTip() << ":\n";
            ev->afisare();
        });
    }


    void cautareDupaOrganizator()
    {
        string organizator;
        cout << "Introduceti numele organizatorului: ";
        cin.ignore();
        getline(cin, organizator);

        try
        {
            if (organizatorEventMap.find(organizator) == organizatorEventMap.end())
            {
                throw NotFoundException("Nu s-au gasit evenimente pentru acest organizator!");
            }

            cout << "Evenimentele organizatorului " << organizator << ":\n";
            int index = 1;

            for (const auto& ev : organizatorEventMap[organizator])
            {
                cout << "\n#" << index++ << " - " << ev->getTip() << ":\n";
                ev->afisare();
            }
        }
        catch (const exception& e)
        {
            cout << "Eroare: " << e.what() << "\n";
        }
    }


    void demonstrareUpDownCasting()
    {
        cout << "Demonstrare Upcasting si Downcasting:\n";

        if (evenimente.getAll().empty())
        {
            cout << "Nu exista evenimente pentru demonstrare. Adaugati mai intai un eveniment.\n";
            return;
        }

        try
        {
            cout << "Upcasting - Evenimentele sunt stocate ca referinte la clasa de baza:\n";

            bool found = false;

            for (const auto& ev : evenimente.getAll())
            {
                if (ev->getTip() == "Concert" || ev->getTip() == "Festival")
                {
                    cout << "Eveniment: " << ev->getNume() << " (tip: " << ev->getTip() << ")\n";

                    cout << "Downcasting:\n";


                    auto concert = dynamic_pointer_cast<Concert>(ev);
                    if (concert)
                    {
                        cout << "Conversie reusita la Concert: Artist = " << concert->getArtist() << "\n";


                        auto festival = dynamic_pointer_cast<Festival>(ev);
                        if (festival)
                        {
                            cout << "Conversie reusita la Festival: Locatie = " << festival->getLocatie() << "\n";
                        }
                        else
                        {
                            cout << "Conversie la Festival esuata - nu este un Festival\n";
                        }
                    }
                    else
                    {
                        cout << "Conversie la Concert esuata\n";
                    }

                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "Nu s-a gasit niciun Concert sau Festival pentru demonstratie.\n";
            }
        }
        catch (const exception& e)
        {
            cout << "Eroare: " << e.what() << "\n";
        }
    }


    void salvareDateInFisier()
    {
        string numeFisier;
        cout << "Introduceti numele fisierului pentru export: ";
        cin >> numeFisier;

        try
        {
            ofstream fisier(numeFisier);

            if (!fisier.is_open())
            {
                throw FileException("Nu s-a putut deschide fisierul pentru scriere!");
            }

            fisier << evenimente.getAll().size() << "\n";

            for (const auto& ev : evenimente.getAll())
            {
                fisier << ev->getTip() << "\n";

                if (ev->getTip() == "Eveniment")
                {
                    fisier << ev->getNume() << "\n";
                    fisier << ev->getOrganizator() << "\n";
                    fisier << ev->getData() << "\n";
                    fisier << ev->getPretBilet() << "\n";
                }
                else if (ev->getTip() == "Concert")
                {
                    auto concert = dynamic_pointer_cast<Concert>(ev);
                    if (concert)
                    {
                        fisier << concert->getNume() << "\n";
                        fisier << concert->getOrganizator() << "\n";
                        fisier << concert->getData() << "\n";
                        fisier << concert->getPretBilet() << "\n";
                        fisier << concert->getArtist() << "\n";
                        fisier << concert->getGen() << "\n";
                        fisier << concert->getDurata() << "\n";
                    }
                }
                else if (ev->getTip() == "Festival")
                {
                    auto festival = dynamic_pointer_cast<Festival>(ev);
                    if (festival)
                    {
                        fisier << festival->getNume() << "\n";
                        fisier << festival->getOrganizator() << "\n";
                        fisier << festival->getData() << "\n";
                        fisier << festival->getPretBilet() << "\n";
                        fisier << festival->getArtist() << "\n";
                        fisier << festival->getGen() << "\n";
                        fisier << festival->getDurata() << "\n";
                        fisier << festival->getNumarZile() << "\n";
                        fisier << festival->getLocatie() << "\n";
                    }
                }
                else if (ev->getTip() == "Conferinta")
                {
                    auto conferinta = dynamic_pointer_cast<Conferinta>(ev);
                    if (conferinta)
                    {
                        fisier << conferinta->getNume() << "\n";
                        fisier << conferinta->getOrganizator() << "\n";
                        fisier << conferinta->getData() << "\n";
                        fisier << conferinta->getPretBilet() << "\n";
                        fisier << conferinta->getSubiect() << "\n";
                        fisier << conferinta->getNumarParticipanti() << "\n";
                    }
                }
            }

            fisier.close();
            cout << "Date salvate cu succes in fisierul " << numeFisier << "!\n";
        }
        catch (const exception& e)
        {
            cout << "Eroare: " << e.what() << "\n";
        }
    }


    void incarcareDate()
    {
        string numeFisier;
        cout << "Introduceti numele fisierului pentru import: ";
        cin >> numeFisier;

        try
        {
            ifstream fisier(numeFisier);

            if (!fisier.is_open())
            {
                throw FileException("Nu s-a putut deschide fisierul pentru citire!");
            }

            int numarEvenimente;
            fisier >> numarEvenimente;
            fisier.ignore();

            for (int i = 0; i < numarEvenimente; i++)
            {
                string tip;
                getline(fisier, tip);

                if (tip == "Eveniment")
                {
                    string nume, organizator, data;
                    double pret;

                    getline(fisier, nume);
                    getline(fisier, organizator);
                    getline(fisier, data);
                    fisier >> pret;
                    fisier.ignore();

                    adaugaEveniment(make_shared<Eveniment>(nume, organizator, data, pret));
                }
                else if (tip == "Concert")
                {
                    string nume, organizator, data, artist, gen;
                    double pret;
                    int durata;

                    getline(fisier, nume);
                    getline(fisier, organizator);
                    getline(fisier, data);
                    fisier >> pret;
                    fisier.ignore();
                    getline(fisier, artist);
                    getline(fisier, gen);
                    fisier >> durata;
                    fisier.ignore();

                    adaugaEveniment(make_shared<Concert>(nume, organizator, data, pret, artist, gen, durata));
                }
                else if (tip == "Festival")
                {
                    string nume, organizator, data, artist, gen, locatie;
                    double pret;
                    int durata, numarZile;

                    getline(fisier, nume);
                    getline(fisier, organizator);
                    getline(fisier, data);
                    fisier >> pret;
                    fisier.ignore();
                    getline(fisier, artist);
                    getline(fisier, gen);
                    fisier >> durata;
                    fisier >> numarZile;
                    fisier.ignore();
                    getline(fisier, locatie);

                    adaugaEveniment(make_shared<Festival>(nume, organizator, data, pret, artist, gen, durata, numarZile, locatie));
                }
                else if (tip == "Conferinta")
                {
                    string nume, organizator, data, subiect;
                    double pret;
                    int numarParticipanti;

                    getline(fisier, nume);
                    getline(fisier, organizator);
                    getline(fisier, data);
                    fisier >> pret;
                    fisier.ignore();
                    getline(fisier, subiect);
                    fisier >> numarParticipanti;
                    fisier.ignore();

                    adaugaEveniment(make_shared<Conferinta>(nume, organizator, data, pret, subiect, numarParticipanti));
                }
            }

            fisier.close();
            cout << "Date incarcate cu succes din fisierul " << numeFisier << "!\n";
        }
        catch (const exception& e)
        {
            cout << "Eroare: " << e.what() << "\n";
        }
    }


    void filtrareEvenimente()
    {
        cout << "Alegeti criteriul de filtrare:\n";
        cout << "1. Evenimente dupa pretul biletului\n";
        cout << "2. Concerte dupa durata minima\n";

        int optiune;
        cin >> optiune;

        try
        {
            if (optiune == 1)
            {
                double pretMax;
                cout << "Introduceti pretul maxim: ";
                cin >> pretMax;

                auto rezultat = evenimente.filter([pretMax](const shared_ptr<Eveniment>& ev)
                {
                    return ev->getPretBilet() <= pretMax;
                });

                cout << "Evenimente cu pretul <= " << pretMax << " LEI:\n";
                int index = 1;

                if (rezultat.empty())
                {
                    cout << "Nu s-au gasit evenimente care sa indeplineasca criteriul.\n";
                    return;
                }

                for (const auto& ev : rezultat)
                {
                    cout << "\n#" << index++ << " - " << ev->getTip() << ":\n";
                    ev->afisare();
                }
            }
            else if (optiune == 2)
            {
                int durataMin;
                cout << "Introduceti durata minima (minute): ";
                cin >> durataMin;

                auto rezultat = evenimente.filter([durataMin](const shared_ptr<Eveniment>& ev)
                {
                    auto concert = dynamic_pointer_cast<Concert>(ev);
                    return concert && concert->getDurata() >= durataMin;
                });

                cout << "Concerte cu durata >= " << durataMin << " minute:\n";
                int index = 1;

                if (rezultat.empty())
                {
                    cout << "Nu s-au gasit concerte care sa indeplineasca criteriul.\n";
                    return;
                }

                for (const auto& ev : rezultat)
                {
                    cout << "\n#" << index++ << " - " << ev->getTip() << ":\n";
                    ev->afisare();
                }
            }
            else
            {
                throw InvalidDataException("Optiune invalida!");
            }
        }
        catch (const exception& e)
        {
            cout << "Eroare: " << e.what() << "\n";
        }
    }


    void afisareMeniu()
    {
        int optiune = 0;

        do
        {
            cout << "\n===== MENIU EVENIMENTE =====\n";
            cout << "1. Adauga eveniment nou\n";
            cout << "2. Afiseaza toate evenimentele\n";
            cout << "3. Cauta evenimente dupa organizator\n";
            cout << "4. Filtrare evenimente\n";
            cout << "5. Salveaza date in fisier\n";
            cout << "6. Incarca date din fisier\n";
            cout << "7. Demonstrare Upcasting si Downcasting\n";
            cout << "0. Iesire\n";
            cout << "Alegeti o optiune: ";
            cin >> optiune;

            try
            {
                switch (optiune)
                {
                case 1:
                    citireEvenimentNou();
                    break;
                case 2:
                    afisareEvenimente();
                    break;
                case 3:
                    cautareDupaOrganizator();
                    break;
                case 4:
                    filtrareEvenimente();
                    break;
                case 5:
                    salvareDateInFisier();
                    break;
                case 6:
                    incarcareDate();
                    break;
                case 7:
                    demonstrareUpDownCasting();
                    break;
                case 0:
                    cout << "La revedere!\n";
                    break;
                default:
                    throw InvalidDataException("Optiune invalida!");
                }
            }
            catch (const exception& e)
            {
                cout << "Eroare: " << e.what() << "\n";
            }
        }
        while (optiune != 0);
    }
};


Meniu* Meniu::instance = nullptr;


int main()
{
    try
    {
        // (Singleton)
        Meniu* meniu = Meniu::getInstance();
        meniu->afisareMeniu();
        Meniu::deleteInstance();
    }
    catch (const exception& e)
    {
        cout << "eroare : " << e.what() << endl;
        return 1;
    }

    return 0;
}
