#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Header/TaxTable.h"
#include "Header/Camiao.h"
#include "Header/utils.h"
#include "Header/Clientes.h"
#include "Header/Servicos.h"
#include "Header/Empresa.h"
#include "Header/Workshop.h"
using namespace std;

/**
 * @file main.cpp
 * @brief This is the main page of the project that contains the implementation of it
 *
 */

ifstream in("../AEDA_Proj1/Ficheiros/tax.txt"); //NAO MUDA!
TaxTable *table = new TaxTable(in);




void mainMenu(Empresa &e);              /**<Handle the main mennu*/
void printMainMenu();                   /**<Prints the main menu to the user*/
void printMenuStatus();                 /**<Prints the menu status to the user that includes visualization for clients and services*/
void printMenuMotorista();              /**<Prints the Motorista menu*/
void printMenuWork();                    /**<Prints the Workshop menu*/
void handleWorkersMenu(Empresa &e);     /**<Handle the workers (Motorista) menu*/
void handleMenuStatus(Empresa &e);      /**<Handle the menu status and the user inputs*/ 
void handleAddClient(Empresa &e);       /**<Handle the operation of adding a new client*/
void handleAddService(Empresa &e);      /**<Handle the operation of adding a new service*/
void handleAddTruck(Empresa &e);        /**<Handle the operation of adding a new truck*/
void handleAddWorker(Empresa & e);      /**<Handle the operation of adding a new worker*/
void handleRemoveWorker(Empresa &e);    /**<Handle the operation of removing a new worker*/
void handleChangeNameWorker(Empresa &e);/**<Handle the operation of adding a new worker name*/



int month;
extern bool novo;

int main(){
    Empresa e;
    cout << "Type the month to be analyzed [EXIT 0] ";
    month = checkOption(0,12);
    if (month != 0){
        e.gravaWor();
        e.gravaCli();
        e.gravaCam();
        e.gravaSer(e, month);
        e.readMotorista();
        e.update_hash();
        mainMenu(e);
    }
}

void handleWorkshop(Empresa &e) {
    int option;
    string name, brand;
    vector<string> brands;
    int disp, number, k = 0;
    priority_queue<Workshop> aux;
    while(true) {
        k = 0;
        brands.clear();
        brand.clear();
        name.clear();
        clear_screen();
        printMenuWork();
        option = checkOption(1, 7);
        if (option == 1) {
            cout << "Enter Workshop name: ";
            cin.ignore();
            getline(cin, name);
            if(name == "exit") continue;
            cout << "Enter number of brands: ";
            number = checkNumber();
            if(number == -1) continue;
            while (k < number) {
                cin >> brand;
                brands.push_back(brand);
                k++;
            }
            cin.ignore();
            cout << "Enter initial unavailability: ";
            disp = checkNumber();
            if(disp == -1) continue;
            e.addWorkshop(name, brands, disp);
            e.updateWor();
            cout << "Workshop added successfully!" << endl;
            wait();
            continue;
        }
        if (option == 2) {
            string name;
            bool verify;
            cout << "Workshop name: ";
            cin.ignore();
            getline(cin, name);
            if(name == "exit"){
                cout<<"Operation cancelled successfully!"<<endl;
                continue;
            }
            verify = e.removeWorkshop(name);
            if (verify) cout << "Workshop removed successfully!" << endl;
            else cout << "Workshop not found" << endl;
            wait();
            continue;
        }
        if (option == 3) {
            headerWorkshop();
            for (auto &el : e.getWor()) cout << el;
            wait();
            continue;
        }
        if (option == 4) {
            aux = e.getPQ();
            long long int id;
            cout << "Enter truck id:";
            id = checkNumber();
            if(id == -1) continue;
            vector < Camiao * > cam_copy(e.getCamiao());
            for (auto it = cam_copy.begin(); it != cam_copy.end(); it++) {
                if ((*it)->getId() == id) {
                    Workshop d = (*it)->requestGenericService(aux);
                    e.swap_pq(aux);
                    cout << "Found Workshop: " << endl;
                    cout << d;
                    cout << "New earliest workshop: " << "\n" << e.getPQ().top() << endl;
                    e.rewriteWorkshops();
                    break;
                }
            }
            wait();
            continue;
        }
        if (option == 5) {
            aux = e.getPQ();
            long long int id;
            cout << "Enter truck id:";
            id = checkNumber();
            if(id == -1) continue;
            vector < Camiao * > cam_copy(e.getCamiao());
            for (auto it = cam_copy.begin(); it != cam_copy.end(); it++) {
                if ((*it)->getId() == id) {
                    Workshop d = (*it)->requestSpecificService(aux);
                    e.swap_pq(aux);
                    cout << "Found Workshop: " << endl;
                    cout << d;
                    e.rewriteWorkshops();
                    break;
                }
            }
            wait();
            continue;
        }
        if (option == 6) {
            headerWorkshop();
            cout << e.getPQ().top() << endl;
            wait();
            continue;
        }
        if (option == 7) return;
    }

}

void mainMenu(Empresa &e){
    string nome;
    while (true) {
        int option;
        printMainMenu();
        option = checkOption(1, 12);
        clear_screen();
        
        if (option == 5)                    //exit option 
            break;
        switch(option){
            case 1:
                handleMenuStatus(e);
                break;
            case 12:
                handleWorkshop(e);
                break;
            case 2:
                e.display_lucro_mes();
                e.display_CamiaoProfit();
                wait();
                break;
            case 6:
                handleAddClient(e);
                break;

            case 9: {
                handleAddService(e);
                break;
            }
            case 3:
                handleAddTruck(e);
                break;
            case 7:{
                long int nif = validClientNif(e);
                if (nif == -1) continue;
                e.changeClientName(nif);
                cout << "Name changed successfully! ";
                wait();
                break;
            }
            case 8:{
                long long nif = validClientNif(e);
                if (nif == -1) continue;
                e.removeClient(nif);
                wait();
                break;
            }
            case 4:{
                cout << "Type the id [EXIT 0]: ";
                long long int id = checkOption(0,e.get_cam_num());
                if (id == 0) continue;
                e.removeTruck(id);
                wait();
                break;
            }
            case 10:{
                handleWorkersMenu(e);
                break;
            }
            default:
                break;
        }
        clear_screen();
    }

}

void printMainMenu(){
    cout    << "      TRANSPORTATION ENTERPRISE                        CLIENTS MANAGEMENT                                WORKER MENU            " << endl
            << "======================================      =======================================      =======================================" << endl
            << "Status info. service and client    [1]      Add new client                      [6]      Workers MENU and visualization     [10]" << endl
            << "Profit info.                       [2]      Change client name                  [7]      Workshops menu and visualization   [12]" << endl
            << "Add truck                          [3]      Remove a client                     [8]                                             " << endl
            << "Remove truck                       [4]      New service request                 [9]                                             " << endl
            << "Exit                               [5]                                                                                          " << endl
            << "Number of trucks: " << Empresa::nCam << endl; 
}

void printMenuStatus(){
    cout    << "            SEARCH SERVICES                                                     SEARCH CLIENTS                  " << endl
            << "============================================                     ============================================   " << endl
            << "First x most profitable services         [1]                     First x most profitable clients          [6]   " << endl
            << "First x least profitable services        [2]                     First x least profitable clients         [7]   " << endl
            << "First x services of a specific type      [3]                     First x clients in alphabetic order      [8]   " << endl
            << "Specific service by id                   [4]                     Specific client status by nif            [9]   " << endl
            << "Cancel                                   [5]                     Show x inactive clients                 [10]   " << endl
            << "                                                                 Show x inactive clients by date         [11]   " << endl
            << "                                                                 Specific inactive status by nif         [12]   " << endl
            << "Option:                                                                                                         " << endl;

}

void printMenuMotorista(){
    cout<< "        WORKERS MENU VISUALIZATION                                              WORKERS MANAGEMENT              "<< endl
        << "============================================                        ============================================"<< endl
        << "First x workers - ascending hours         [1]                       Add a worker                             [6]"<< endl
        << "First x workers - descending hours        [2]                       Remove a worker                          [7]"<< endl
        << "First x workers - alphabetic order        [3]                       Change a worker name                     [8]"<< endl
        << "Search a specific worker by nif           [4]                       Reset hours of work                      [9] "<< endl
        << "Cancel                                    [5]                                                                   "<< endl;

}
void printMenuWork(){
    cout<< "        WORKSHOPS MENU VISUALIZATION                                              SERVICE MANAGEMENT            "<< endl
        << "============================================                        ============================================"<< endl
        << "Show all workshops                        [3]                       Add a workshop                           [1]"<< endl
        << "Show earliest available workshop          [6]                       Remove a workshop                        [2]"<< endl
        << "                                                                    Request generic service for a truck      [4]"<< endl
        << "                                                                    Request specific service for a truck     [5]"<< endl
        << "Cancel                                    [7]                                                                    "<< endl;

}
void handleMenuStatus(Empresa &e){
    int option, id, nif, type;
    long int n;
    map<unsigned int,string> temp = { {0,"Base"},{1,"Congelado"},{2,"Perigoso"},{3,"Animal"}};

    while(true) {
        clear_screen();
        printMenuStatus();

        option = checkOption(1, 12);

        if (option == 5) return;
        switch(option){
            case 1: {
                cout << "Type x [EXIT - 0][1~10000] ";
                n = checkOption(0, 10000);
                if (n == 0) continue;
                e.display_servicoStatus(0, n);
                wait();
                break;
            }
            case 4:
                id = validServiceId(e);
                e.display_servicoStatus(id);
                wait();
                break;
            case 6:
                cout << "Type x [EXIT - 0][1~10000] ";
                n = checkOption(0, 10000);
                if (n == 0) continue;
                e.display_clientesInfo(0,n);
                wait();
                break;
            case 9:
                nif = validClientNif(e);
                if (nif != -1) {
                    e.display_clientesInfo(nif);
                    wait();
                }
                break;
            case 2:
                cout << "Type x [EXIT - 0][1~10000] ";
                n = checkOption(0, 10000);
                if (n == 0) continue;
                e.display_servicoStatus(0, n, Compare_servico_Leastprofit);
                wait();
                break;
            case 3:
                cout << "Type x [EXIT - 0][1~10000] ";
                n = checkOption(0, 10000);
                if (n == 0) continue; 
                cout << "Enter type of package (0 BASE | 1 FROZEN | 2 DANGEROUS | 3 ANIMAL) [EXIT -1] ";
                type = checkOption(-1, 3);
                if (type == -1) continue;
                e.display_servicoStatus(0, n, Compare_servico_Leastprofit, temp[type]);
                wait();
                break;
            case 7:
                cout << "Type x [EXIT - 0][1~10000] ";
                n = checkOption(0, 10000);
                if (n == 0) continue;
                e.display_clientesInfo(0,n,Compare_clientesLeast);
                wait();
                break;
            case 8:
                cout << "Type x [EXIT - 0][1~10000] ";
                n = checkOption(0, 10000);
                if (n == 0) continue;
                e.display_clientesInfo(0,n,Compare_clientesAlphabetic);
                wait();
                break;
            case 10:
                cout << "Type x [EXIT - 0][1~10000] ";
                n = checkOption(0, 10000);
                if (n == 0) continue;
                headerClientes();
                e.display_hash(n);
                wait();
                break;
            case 11:
                cout << "Type x [EXIT - 0][1~10000] ";
                n = checkOption(0, 10000);
                if (n == 0) continue;
                e.display_dateOrdered_hash(n);
                wait();
                break;
            case 12:
                nif = validClientNif(e);
                if (nif != -1) {
                    try {
                        headerClientes();
                        cout <<  e.SearchInactiveClient_hash(nif) << endl;
                    }catch(NoClient &noclient) {
                        clear_screen();
                        cout << "The client is not inactive!" << endl;
                    }

                    wait();
                }
        }

    }
}

void handleWorkersMenu(Empresa &e){
    int option, n;
    Motorista m;

    while(true){
        clear_screen();
        printMenuMotorista();
        option = checkOption(1,9);
        if (option == 5) return;

        switch(option){
            case 4: {
                cout << "NIF: ";
                long long int nif = checkNumber();
                if (nif == 0 || nif < -1) {
                    cout << "Invalid NIF. Try again." << endl;
                    wait();
                    break;
                }
                if (nif == -1) break;

                //check if there's a worker with this NIF
                try {
                    m = e.getBST().check_nif(nif);
                } catch (NoWorker &e) {
                    cout << e.getInfo() << endl;
                    wait();
                    break;
                }

                //case there's a worker with the given nif
                headerWorkersInfor();
                cout << m;
                wait();
                break;
            }
            case 6:
                handleAddWorker(e);
                break;
            case 7:
                handleRemoveWorker(e);
                break;
            case 8:
                handleChangeNameWorker(e);
                break;
            case 9:
                e.resetHours();
                cout << "Hours reseted successfully"<< endl;
                wait();
                break;
            default:
                cout << "Type x [EXIT - 0][1~10000] ";
                n = checkOption(0, 10000);
                if (n == 0) continue;

                headerWorkersInfor();
                e.displayWorkers(option, n);
                wait();
                break;

        }

    }
}

void handleAddClient(Empresa &e){
    long long int nif;
    string nome;
    cout<<"Number of clients: "<< Empresa::nCli <<endl;

    while (true) {
        cout<<"NIF: ";
        nif = checkNumber();
        if (nif == 0 || nif < -1){
            cout << "Invalid NIF. Try again." << endl; 
             continue;                                                      //do not accept negative nifs
        }
        if (nif == -1) return;

        //case it was a ex-client
        long int pos = e.SearchCli((-1) * nif);
        if (pos != -1){
            e.reAcceptClient(pos);
            cout << "Client reaccepted! ";
            wait();
            return;
        }

        cout<<"Nome [EXIT -1]: ";
        cin.ignore();
        getline(cin,nome);
        if (nome == "-1") return;                                           //abort operation


        try {
            e.addClientes(nome, nif);
            ofstream o("../AEDA_Proj1/Ficheiros/clientes", ios_base::app);
            o << "\n" << nome << "\n" << nif << "\n" << "1500/01/01";      //adding client with default date
            o.close();
            cout << "Client added successfully! ";
            wait();
            return;
        }
        catch (RepeatedClient &a) {
            cout << "There is already a client with nif "<< nif << endl;
            cout << "Try again:" << endl;
            continue;
        }
    }
}

void handleAddService(Empresa &e){
    map<unsigned int,string> temp = { {0,"Base"},{1,"Congelado"},{2,"Perigoso"},{3,"Animal"}};
    map<unsigned int,string> temp_carac = { {0,"Frio"},{1,"Medio"},{2,"Quente"}, {3,"Toxico"},{4,"Inflamavel"},{5,"Quebravel"}, {6,"Pequeno"},{7,"Medio"},{8,"Grande"},{9,"None"}};
    double l1x, l1y, l2x,l2y;
    string partida,chegada,tipo;
    long int anif, type;
    int carga;

    while (true) {
        clear_screen();
        cout << "Enter the number of products ";
        carga = checkNumber();
        if (carga == -1) return;
        if (carga < -1 || carga == 0) {
            cout << "Only positive numbers! Try again." << endl;
            continue;
        }

        cout << "Enter place of departure [EXIT -1] ";
        cin.ignore();
        getline(cin, partida);
        if (partida == "-1") return;

        cout << "Enter place of arrival [EXIT -1] ";
        getline(cin, chegada);
        if (chegada == "-1") return;

        cout << "Enter type of package (0 BASE | 1 FROZEN | 2 DANGEROUS | 3 ANIMAL) [EXIT -1] ";
        type = checkOption(-1, 3);
        if (type == -1) return;
        tipo = temp[type];

        anif = validClientNif(e);
        if (anif == -1) return;

        cout << "Partida coordenada x (latitude) ";
        l1x = checkNumber();
        if (l1x == -1) return;
        cout << "Partida coordenada y (Longitude) ";
        l1y = checkNumber();
        if (l1y == -1) return;
        cout << "Chegada coordenada x (Latitude) ";
        l2x = checkNumber();
        if (l2x == -1) return;
        cout << "Chegada coordenada y (Longitude) ";
        l2y = checkNumber();
        if (l2y == -1) return;

        int opt = 9;
        if (tipo == "Congelado"){
            cout << "Enter type temperature of the products (0 COLD | 1 AMBIENT | 2 HOT) [EXIT -1]";
            opt = checkOption(-1,2);
            if (opt == -1) return;
        }
        else if (tipo == "Perigoso"){
            cout << "Enter how dangerous the products are (3 TOXIC | 4 FLAMBLE | 5 SENSIBLE) [EXIT 2]";
            opt = checkOption(2,5);
            if (opt == 2) return;
        }
        else if(tipo == "Animal"){
            cout << "Enter the size of the animals (6 LITTLE | 7 MEDIO | 8 BIG) [EXIT 5]";
            opt = checkOption(5,8);
            if (opt == 5) return;
        }

        Servicos *s = new Servicos(Local(partida, l1x, l1y), Local(chegada, l2x, l2y), ++Empresa::nSer, tipo, carga, temp_carac[opt]);


        if (!e.allocateCamiao(s)){
            cout << "Not enough trucks " << endl;
            wait();
            return;
        }
        for (int i = 0; i < s->num_camiao(); i++) {
            if (!e.allocateMotorista(s->cal_tempo())){
                cout << "Not enought workers\n";
                return;
            }
        }
        e.requestService(s,anif);
        string fileName = "../AEDA_Proj1/Ficheiros/servicos"+to_string(month)+".txt"; 
        ofstream o(fileName.c_str(), ios_base::app);

        if (novo)  novo = false;
        else o << "\n";

        o << partida << "\n" << l1x << "\n" << l1y;
        o << "\n" << chegada << "\n" << l2x << "\n" << l2y;
        o << "\n" << tipo << "\n" << anif<< "\n" << carga << "\n";
        o << temp_carac[opt] << "\n";
        o << s->get_camioes_id();
        o.close();
        cout << "Service added successfully! ";
        wait();

        return;
    }
}

void handleAddTruck(Empresa &e){
    int type, carg;
    double caract;
    string brand;
    map<unsigned int,string> temp = { {0,"Base"},{1,"Congelado"},{2,"Perigoso"},{3,"Animal"}};
    while (true) {
        cout<<"Brand: ";
        cin>>brand;
        cout << "Max carg: ";
        carg = checkNumber();
        if (carg == -1) return;
        if (carg < 1){
            cout << "Only positive numbers." << endl;
            continue; 
        }
        else break;
    }

    cout << "[EXIT -1] Enter type of package (0 BASE | 1 FROZEN | 2 DANGEROUS | 3 ANIMAL): ";
    type = checkOption(-1, 3);
    if (type == -1) return;

    if(type == 0){
        e.addCamiao(0, carg,brand);
    }
    else if (type == 1){
        e.addCamiao(1, carg,brand);
    }
    else if (type == 2){
        e.addCamiao(2, carg,brand);
    }
    else if (type == 3){
        e.addCamiao(3, carg,brand);
    }

    cout << "Truck added successfully ";
    wait(); 

    e.rewriteTruck();

}

void handleAddWorker(Empresa & e){
    string name;
    long long int nif;

    //get the name
    cout << "[EXIT -1] Type the name: ";
    cin.ignore();
    getline(cin, name);
    if (name == "-1") return;

    while(true) {
        //get the nif
        cout << "Type NIF: ";
        nif = checkNumber();

        if (nif == 0 || nif < -1) {
            cout << "Invalid NIF. Try again." << endl;
            wait();
            continue;                                                      //do not accept negative nifs
        }
        if (nif == -1) return;  //cancel the operation
        else break;
    }
    Motorista m(name, nif, 0);
    if (!e.addMotorista(m))
        cout << "There is already a worker with the specific nif";
    else {
        cout << "Worker added successfully";
        //write the content on the file
        fstream file;
        file.open("../AEDA_Proj1/Ficheiros/Motoristas",  ios_base::app);
        file<<"\n"<< m.getName() << "\n"
            << m.getNif() << "\n"
            << m.getHours();
        file.close();

    }
    wait();

}

void handleRemoveWorker(Empresa &e){
    //To remove a worker, due the tree implementation, we must know the number of hours worked
    long long int nif;
    while(true) {
        cout << "NIF: ";
        nif = checkNumber();
        if (nif == 0 || nif < -1) {
            cout << "Invalid NIF. Try again." << endl;
            continue;                                                      //do not accept negative nifs
        }
        if (nif == -1) return;
        break;
    }
    if(!e.removeMotorista(Motorista("", nif, 0)))
        cout << "No worker with the given NIF" << endl;
    else cout<< "Worker removed successfully!" << endl;
    wait();
}

void handleChangeNameWorker(Empresa &e){
    long long int nif;
    while(true) {
        cout << "NIF: ";
        nif = checkNumber();
        if (nif == 0 || nif < -1) {
            cout << "Invalid NIF. Try again." << endl;
            continue;                                                      //do not accept negative nifs
        }
        if (nif == -1) return;
        break;
    }
    //get the name
    string name;
    cout << "[EXIT -1] NAME: ";
    cin.ignore();
    getline(cin, name);
    if (name == "-1") return;

    if(!e.setMotoristaName(Motorista("", nif, 0), name))
        cout << "No worker with the given NIF" << endl;
    else cout<< "Worker name changed successfully!" << endl;
    wait();

}