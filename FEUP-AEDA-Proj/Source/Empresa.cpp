//
// Created by maruba on 14/10/19.
//

#include "../Header/Empresa.h"
#include <fstream>


void headerServInfor();

bool novo;
size_t Empresa::nCam = 0;
size_t Empresa::nCli = 0;
size_t Empresa::nSer = 0;


void Empresa::gravaWor() {
    ifstream file("../AEDA_Proj1/Ficheiros/workshops");
    string name;                        //stores the name of the client
    string brand;                         //auxiliar variable to read lines
    string aux;
    int disp, total, k;
    string delimiter = " ";
    //vector<string> empty;
    vector<string> brands;
    while (!file.eof()) {
        brands.clear();
        getline(file, name);            //get name
        getline(file, aux);
        istringstream f(aux);
        f >> total;
        k = 0;
        while (k < total) {
            getline(file, brand);
            brands.push_back(brand);
            k++;
        }
        getline(file, aux);
        istringstream is(aux);
        is >> disp;
        Workshop nani(name, brands, disp);
        wor.push_back(nani);
        //pq.emplace(name,brands,disp);
    }
    file.close();
    fillQueue();
}


/**
 * @file Empresa.cpp
 * @brief It contains the Empresa class implementation, resposable for the management of the enterprise
 */

//modified
void Empresa::gravaCli() {
    ifstream file("../AEDA_Proj1/Ficheiros/clientes");
    string name;                        //stores the name of the client
    string aux;                         //auxiliar variable to read lines
    long long int nif;
    while (!file.eof()) {
        getline(file, name);            //get name
        getline(file, aux);             //get string nif
        istringstream is(aux);                  //get unsigned int nif
        is >> nif;
        getline(file, aux);
        addClientes(name, nif, aux);         //add client
    }
}

void Empresa::gravaSer(Empresa &e, const int &month) {
    string fileName = "../AEDA_Proj1/Ficheiros/servicos" + to_string(month) + ".txt";
    ifstream file(fileName.c_str());
    string local, aux, type;
    long long int aux_int, carga, cliNif;
    double cordx, cordy;
    vector<long long int> trucks;
    if (!file.fail())
        while (!file.eof()) {

            //get the first local (the departure)
            getline(file, local);                           //get the local of departure
            getline(file, aux);                             //get the first coordinate
            istringstream is(aux);
            is >> cordx;

            getline(file, aux);                             //get the second coordinate
            is.clear();
            is.str(aux);
            is >> cordy;
            Local *l1 = new Local(local, cordx, cordy);     //crete the local class for departure

            //get the second local (the arrival)
            getline(file, local);                           //get the local of arrival
            getline(file, aux);                             //get the first coordinate
            is.clear();
            is.str(aux);
            is >> cordx;

            getline(file, aux);                             //get the second coordinate
            is.clear();
            is.str(aux);
            is >> cordy;
            Local *l2 = new Local(local, cordx, cordy);     //create the local class for arrival

            //get the type of service
            getline(file, type);

            //get the client nif
            getline(file, aux);
            is.clear();
            is.str(aux);
            is >> cliNif;

            //get the storage
            getline(file, aux);
            is.clear();
            is.str(aux);
            is >> carga;

            //get the type
            getline(file, aux);

            Servicos *s = new Servicos(*l1, *l2, ++Empresa::nSer, type, carga, aux);

            //get camioes id
            getline(file, aux);
            is.clear();
            is.str(aux);
            while (!is.eof() && aux != "0") {                   //get the list of trucks id
                is >> aux_int;
                this->addCamiaoId_Servico(aux_int, s);
            }

            try {
                e.addServico(s, cliNif);                        //associate the service to a client
            }
            catch (NoClient &error) {
                cliNif = -cliNif;
                e.addServico(s, cliNif);
            }
        }
    else novo = true;                                           //if there's nothing to read, it means that this is a new file
}

void Empresa::gravaCam() {
    fstream file("../AEDA_Proj1/Ficheiros/camioes");
    long long int carga;
    string type;
    string auxString;
    string brand;
    while (!file.eof()) {
        getline(file, brand);
        getline(file, auxString);                           //get cargaMax
        //if (brand == "") break;                                 //end line
        istringstream is(auxString);
        is >> carga;
        ++nCam;
        getline(file, type);                                //get the type
        if (type == "Animal") {
            Animals *c = new Animals(carga, cam.size() + 1, brand);
            cam.push_back(c);
        } else if (type == "Congelado") {
            Congelado *c = new Congelado(carga, cam.size() + 1, brand);
            cam.push_back(c);
        } else if (type == "Perigoso") {
            Perigoso *c = new Perigoso(carga, cam.size() + 1, brand);
            cam.push_back(c);
        } else {
            Base *c = new Base(carga, cam.size() + 1, brand);
            cam.push_back(c);
        }
    }
}

void Empresa::readMotorista() {
    w.readMotorista();
}
//------------------------------------------------------------------------------------

Empresa::Empresa() {
    inactive.clear();
}

Empresa::~Empresa() {
    vector<Clientes *> tempX;
    vector<Camiao *> tempY;
    vector<Servicos *> tempZ;
    cli.clear();
    cam.clear();
    ser.clear();
    cli.swap(tempX);
    cam.swap(tempY);
    ser.swap(tempZ);
}

double Empresa::getLucro_mes() const {
    double lucro = 0;
    for (auto it = ser.begin(); it < ser.end(); it++)                       //profit of each service done
        lucro += (*it)->get_profit();
    return lucro;
}

Workers Empresa::getBST() const {
    return w;
}

long long int Empresa::get_cam_num() {
    return cam.size();
}

//modified
void Empresa::addClientes(const string &name, const long long int &nif, const string &date) {
    long int pos = SearchCli(nif);                                          //check if the client already exists
    if (pos != -1) throw RepeatedClient(name);                              // if so, throw a exception
    auto c = new Clientes(name, nif);
    c->setDate(date);                                                       //update date from the last service request
    if (nif > 0)
        nCli++;                                                             //increase the number of clients
    cli.push_back(c);
    inactive.insert(
            c);                                                    //add client to the hash. It's automatically inactive
}

//modified
Servicos *Empresa::addServico(Servicos *s, const long long int cliNif) {
    long int pos = SearchCli(cliNif);
    if (pos == -1) throw NoClient(to_string(cliNif));               //check if the services already exists
    ser.push_back(s);
    (cli[pos])->addService(s);
    return s;
}

//modified
Servicos *Empresa::requestService(class Servicos *s, const long long cliNif) {
    long int pos = SearchCli(cliNif);
    if (pos == -1) throw NoClient(to_string(cliNif));

    //Remove person from inactive hashtable
    inactive.erase(cli[pos]);

    //Now add the service to the client and update the date of the last request
    ser.push_back(s);
    (cli[pos])->addService(s);
    (cli[pos])->setDate(getTimeNow());
    rewriteClients();
    return s;
}

long int Empresa::SearchCli(const long long int &nif) const {
    for (int i = 0; i < cli.size(); i++) {                          //Linear search O^n
        if (cli[i]->get_nif() == nif) return i;
    }
    return -1;                                                      // if doesnt exist returns -1
}

size_t Empresa::SearchSer(const long long int &id) const {
    for (int i = 0; i < ser.size(); i++) {                          //Linear search O^n
        if (ser[i]->get_id() == id) return i;
    }
    throw NoService(to_string(id));                                 //if it doenst exist throw an exception
}

void Empresa::display_lucro_mes() {
    cout << fixed << setprecision(2);
    cout << "Total profit of the month: " << this->getLucro_mes() << endl;
}

void Empresa::display_CamiaoProfit() {
    headerCamInfor();
    cout << left << setw(20) << getLucro_camiaoMes("Base")
         << setw(20) << getLucro_camiaoMes("Congelado")
         << setw(20) << getLucro_camiaoMes("Perigoso")
         << getLucro_camiaoMes("Animals") << endl;

}


void
Empresa::display_clientesInfo(const long long int &nif, long int n, bool (*f)(const Clientes *c, const Clientes *c1)) {
    ostringstream os;
    os << fixed << setprecision(2);
    if (nif) {                                                      //Case just one client to be shown
        long int pos = SearchCli(nif);
        if (pos == -1)
            throw NoClient(to_string(nif));

        os << left << setw(30) << "NAME" << setw(20) << "NIF" << setw(20) << "PROFIT" << setw(20) << "DATE"
           << "SERVICES" << endl;
        os << "=========================================================="
              "=============================================================" << endl;
        os << *cli[pos];
    } else {                                                        //Case n clients to be shown
        vector<Clientes *> c(cli);
        sort(c.begin(), c.end(), f);
        os << left << setw(30) << "NAME" << setw(20) << "NIF" << setw(20) << "PROFIT" << setw(20) << "DATE"
           << "SERVICES" << endl;
        os << "=========================================================="
              "=============================================================" << endl;
        for (auto it = c.begin(); it < c.end(); it++) {
            if ((*it)->get_nif() > 0) {                                   //the negative nifs are from deleted clients
                os << *(*it);
                n--;                                                    //When n == 0, n clients has already been displayed
            }
            if (n == 0) break;
        }
    }
    cout << os.str();
}


void Empresa::display_servicoStatus(const long long int &id, long int n, bool (*f)(const Servicos *, const Servicos *),
                                    const string &type) const {
    ostringstream os;
    os << fixed << setprecision(2);

    if (id) {                                                       //Case just one service to be displayed
        size_t pos = SearchSer(id);
        os << *ser[pos];
    } else {                                                        //Case n services to be shown
        vector<Servicos *> s(ser);
        sort(s.begin(), s.end(), f);                                //Sorting according with the request
        if (type.empty()) {                                         //If there is no preference of types
            for (auto &it : s) {
                os << *it;
                n--;
                if (n == 0) break;
            }
        } else {                                                       //If there is preference of type of service
            for (auto &it : s) {
                if (it->get_tipo() == type) {                        //Check the type
                    os << *it;
                    n--;
                }
                if (n == 0) break;                                  //n Services has already been displayed
            }
        }
    }
    headerServInfor();                                              //Show header of the list
    cout << os.str();
}

void Empresa::displayWorkers(int option, int n) {
    switch (option) {
        case 1:
            w.printBST(n);
            break;
        case 2:
            w.printBST_reversed(n);
            break;
        case 3:
            w.printBST_alphabetic(n);
            break;
    }
}

void headerServInfor() {
    cout << left << setw(10) << "ID"
         << setw(15) << "TIPO"
         << setw(10) << "TEMPO"
         << setw(30) << "PARTIDA"
         << setw(30) << "CHEGADA"
         << setw(15) << "N CAMIOES"
         << setw(15) << "PRECO"
         << setw(15) << "CARGA"
         << "CARACTERISTICA" << endl;
    cout << "=========================================================="
            "=========================================================="
            "===========================================" << endl;

}


void headerCamInfor() {
    cout << left << setw(20) << "BASE"
         << setw(20) << "FROZEN"
         << setw(20) << "DANGEROUS"
         << "ANIMALS" << endl;
    cout << "=========================================================="
            "=======================" << endl;

}

void headerWorkersInfor() {
    cout << left << setw(30) << "NAME" << setw(20) << "NIF" << "HOURS" << endl;
    cout << "==================================================================" << endl;
}


void Empresa::addCamiao(const int &type, const long long int &cargaMax, string brand) {
    map<unsigned int, string> temp = {{0, "Base"},
                                      {1, "Congelado"},
                                      {2, "Perigoso"},
                                      {3, "Animal"}};
    string sType = temp[type];                                          //Get the type
    unsigned int id = cam.size() + 1;                                     //Increase ne number of trucks
    if (sType == "Base") {
        Camiao *c = new Base(cargaMax, id, brand);
        cam.push_back(c);
    } else if (sType == "Congelado") {
        Camiao *c = new Congelado(cargaMax, id, brand);
        cam.push_back(c);
    } else if (sType == "Perigoso") {
        Camiao *c = new Perigoso(cargaMax, id, brand);
        cam.push_back(c);
    } else if (sType == "Animal") {
        Camiao *c = new Animals(cargaMax, id, brand);
        cam.push_back(c);
    }
    ++nCam;

}


void Empresa::addCamiaoId_Servico(const int &id, Servicos *s) {
    for (auto it = cam.begin(); it != cam.end(); it++) {                //Linear Search O^n to find the id
        if ((*it)->getId() == id)
            s->addCamiao((*it));

    }
}

double Empresa::getLucro_camiaoMes(const string &type) const {
    double lucro = 0;
    for (auto const &it : cam) {                                        //Linear Search to group the profit by type
        if (it->getType() == type)
            lucro += it->getProfit();
    }
    return lucro;
}

bool Empresa::allocateCamiao(Servicos *s) {
    vector<Camiao *> cam_copy(cam);
    int carga = s->get_carga();
    sort(cam_copy.begin(), cam_copy.end(), Compare);                    //Sort by ascender order of profit
    for (const auto &x: cam_copy) {
        string m = x->getType();
        if (x->getType() == s->get_tipo() && x->getCargaMax() > 0) {      //If it has the same type of the service
            carga -= x->getCargaMax();
            s->addCamiao(x);
        }
        if (carga <= 0)                                                 //If enought trucks
            break;
    }
    return carga <= 0;

}

//modified
void Empresa::changeClientName(const long long int &nif) {
    string name;
    //get the position of the client
    long long int pos = SearchCli(nif);
    cin.ignore();
    cout << "Type the new name [EXIT -1]: ";
    getline(cin, name);
    if (name == "-1") return;

    //We must change it's in the hash table too.
    //First we must know if it's in the hash
    //tabHCli::iterator it = inactive.find(cli[pos]);

    //Change the client name
    cli[pos]->setName(name);

    //If the element is in the hash table, change it's name too, else do nothing
    /*if (it != inactive.end()){
        inactive.erase(it);
        inactive.insert(cli[pos]);
    }*/

    //we need to rewrite the file
    rewriteClients();
}

//modified
void Empresa::rewriteClients() {
    ofstream file("../AEDA_Proj1/Ficheiros/clientes");
    for (long int i = 0; i < cli.size(); i++)
        if (i != cli.size() - 1)
            file << cli[i]->getName() << endl << cli[i]->get_nif() << endl << string(cli[i]->getDate()) << endl;

    //avoid to create a last line on the file
    file << cli[cli.size() - 1]->getName() << endl << cli[cli.size() - 1]->get_nif() << endl
         << cli[cli.size() - 1]->getDate();
    file.close();

}


void Empresa::removeClient(const long long int &nif) {
    long int pos = SearchCli(nif);                                      //get the position of the client
    if (pos == -1) {
        cout << "No such cliente! " << endl;
        return;
    }
    //First we must see if the client is in the hash table.
    tabHCli::iterator it = inactive.find(cli[pos]);

    cli[pos]->setNif((-1) * nif);                                         //change the nif to a negative one
    nCli--;
    //If the client is in the hash table, update it
    if (it != inactive.end()) {
        inactive.erase(it);
        inactive.insert(cli[pos]);
    }

    rewriteClients();                                                   //we need to rewrite the file
    cout << "Client removed successfully! ";
}

void Empresa::reAcceptClient(const long int &pos) {
    cli[pos]->setNif((-1) * cli[pos]->get_nif());
    rewriteClients();
}

void Empresa::removeTruck(const long long int &id) {
    for (auto const &t: cam) {
        if (t->getId() == id) {
            if (t->getCargaMax() < 0) {
                cout << "Truck has already been removed ";
                return;
            }
            t->removeTruck();
            nCam--;
            cout << "Truck removed successufully ";
            break;
        }
    }
    //now we need to write the information at the file camioes
    rewriteTruck();

}

void Empresa::rewriteTruck() {
    ofstream o("../AEDA_Proj1/Ficheiros/camioes");
    for (auto i = 0; i < cam.size() - 1; i++) {
        o << cam[i]->getBrand() << "\n" << cam[i]->getCargaMax() << "\n" << cam[i]->getType() << "\n";
    }
    o << cam[cam.size() - 1]->getBrand() << "\n" << cam[cam.size() - 1]->getCargaMax() << "\n"
      << cam[cam.size() - 1]->getType();
    o.close();

}

// MOTORISTA ---------------------------------------------------
bool Empresa::addMotorista(class Motorista m) {
    return w.addMotorista(m);
}

bool Empresa::removeMotorista(class Motorista m) {
    bool b = w.removeMotorista(m);
    w.rewrite_file();
    return b;
}

bool Empresa::setMotoristaName(Motorista m, const string &name) {
    bool b = w.setName(m, name);
    if (b) {
        w.rewrite_file();
        return true;
    }
    return false;
}

bool Empresa::allocateMotorista(float tempo) {
    return w.allocateMotorista(tempo);
}

void Empresa::resetHours() {
    w.resetHours();
}

void Empresa::rewriteWorkshops() {
    ofstream out("../AEDA_Proj1/Ficheiros/workshops");
    int aux, k;
    for (auto i = 0; i < wor.size() - 1; i++) {
        out << wor[i].getName() << endl;
        out << wor[i].getBrands().size() << endl;
        for (auto &elem : wor[i].getBrands()) {
            out << elem << endl;
        }
        //out<<endl;
        out << wor[i].get_unavailability() << endl;

    }
    int i = wor.size() - 1;
    out << wor[i].getName() << endl;
    out << wor[i].getBrands().size() << endl;
    for (auto &elem : wor[i].getBrands()) {
        out << elem << endl;
    }
    //out<<endl;
    out << wor[i].get_unavailability();
    out.close();
}


bool Empresa::removeWorkshop(string name) {
    bool verify = false;
    for (auto it = wor.begin(); it != wor.end(); it++) {
        if (it->getName() == name) {
            wor.erase(it);
            verify = true;
            break;
        }
    }
    if (!verify) return false;
    else {
        rewriteWorkshops();
        return true;
    }
}

void Empresa::fillQueue() {
    for (auto &elem : wor) {
        pq.push(elem);
    }
}

// HASH TABLE ----------------------------------------

void Empresa::update_hash() {
    inactive.clear();
    for (auto const &c: cli) {
        Date date(c->getDate());                    //date of the last client request order
        Date date_today(getTimeNow());              //today's date
        //compare  if it has passed one year since the last request
        date_today.setYear(date_today.getYear() - 1);
        //case date_today is after date, means that the request was done more than a year
        if (date.isAfter(date_today))
            inactive.insert(c);
    }
}

void Empresa::display_hash(long int x) {
    for (auto it = inactive.begin(); it != inactive.end(); it++) {
        cout << *(*it);
        x--;
        if (!x) break;
    }
}

Clientes Empresa::SearchInactiveClient_hash(const long long &nif) {
    for (auto it = inactive.begin(); it != inactive.end(); it++) {
        if ((*it)->get_nif() == nif)
            return *(*it);
    }
    throw NoClient(to_string(nif));
}

void Empresa::display_dateOrdered_hash(long x) {
    vector<Clientes> c;
    for (auto it = inactive.begin(); it != inactive.end(); it++) {
        c.push_back(*(*it));
        x--;
        if (!x) break;
    }
    sort(c.begin(), c.end(), [](Clientes c1, Clientes c2) {
        Date d1 = c1.getDate();
        Date d2 = c2.getDate();
        return d1.isAfter(d2);
    });
    headerClientes();
    for (auto const &it: c) {
        cout << it;
    }
}