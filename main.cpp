#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

struct User {
    int id;
    string login, password;
};

struct Person {
    int id, whichUser;
    string name = "", surname = "", phoneNumber = "", email = "", address = "";
};

string loadLine() {
    string textEntered = "";
    getline(cin, textEntered);
    return textEntered;
}

char loadSign() {
    char sign = {0};
    string signEntered = "";

    while (true) {
        getline(cin, signEntered);
        if (signEntered.length() == 1) {
            sign = signEntered[0];
            break;
        } else {
            cout << "Wpisz pojedynczy znak!" << endl;
        }
    }
    return sign;
}

void loadUsersFromFile (vector<User> &users) {
    string line;
    User user;

    ifstream file;
    file.open("Uzytkownicy.txt");

    if (file.good()) {
        while (getline(file,line)) {
            string login = "", password = "", buforId = "";
            int lineLength = line.length(), typeOfData = 1;

            for (int i = 0; i < lineLength; i++) {
                if (line[i] == '|') {
                    typeOfData++;
                } else if (line[i] != '|') {
                    switch (typeOfData) {
                    case 1:
                        buforId += line[i];
                        break;
                    case 2:
                        login += line[i];
                        break;
                    case 3:
                        password += line[i];
                        break;
                    }
                }
            }
            user.id = atoi(buforId.c_str());
            user.login = login;
            user.password = password;

            users.push_back(user);
        }
        file.close();

    } else {
        cout << endl << "Wczytanie uzytkownikow z pliku zakonczone niepowodzeniem!" << endl << endl;
    }
}

int loadPersonsFromFile(vector<Person> &persons, int loggedInUser) {
    int id = 0;
    string line;
    Person person;

    ifstream file;
    file.open("Adresaci.txt");

    if (file.good()) {
        while (getline(file,line)) {
            string name = "", surname = "", phoneNumber = "", email = "", address = "";
            string buforId = "", buforUserId = "";
            int lineLength = line.length(), typeOfData = 1;

            for (int i = 0; i < lineLength; i++) {
                if (line[i] == '|') {
                    typeOfData++;
                } else if (line[i] != '|') {
                    switch (typeOfData) {
                    case 1:
                        buforId += line[i];
                        break;
                    case 2:
                        buforUserId += line[i];
                        break;
                    case 3:
                        name += line[i];
                        break;
                    case 4:
                        surname += line[i];
                        break;
                    case 5:
                        phoneNumber += line[i];
                        break;
                    case 6:
                        email += line[i];
                        break;
                    case 7:
                        address += line[i];
                        break;
                    }
                }
            }
            person.id = atoi(buforId.c_str());
            person.whichUser = atoi(buforUserId.c_str());
            person.name = name;
            person.surname = surname;
            person.phoneNumber = phoneNumber;
            person.email = email;
            person.address = address;

            if (person.whichUser == loggedInUser) {
                persons.push_back(person);
            }
            id++;
        }
        file.close();
    } else {
        cout << "Wczytanie adresatow z pliku zakonczone niepowodzeniem!" << endl << endl;
    }
    if (id > 0) {
        id = person.id;
    }
    return id;
}

void saveUserToTxtFile(User user) {
    ofstream file;
    file.open("Uzytkownicy.txt", ios::app);

    if (file.good()) {
        file << user.id << "|";
        file << user.login << "|";
        file << user.password << "|" << endl;
        file.close();
    } else {
        cout << "Rejestracja uzytkownika zakonczona niepowodzeniem!" << endl << endl;
    }
    cout << endl << "Rejestracja uzytkownika zakonczona powodzeniem!" << endl << endl;
}

void userRegistration(vector<User> &users) {
    string login, password;
    int numberOfUsers = users.size();
    int i = 0, id;
    User user;

    system("cls");
    cout << "    |Rejestracja|" << endl << endl;
    cout << "Podaj nazwe uzytkownika: ";
    login = loadLine();

    while (i < numberOfUsers) {
        if (users[i].login == login) {
            cout << endl << "Podana nazwa uzytkownika jest juz zajeta! Podaj inna nazwe uzytkownika: ";
            login = loadLine();
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    password = loadLine();

    if (numberOfUsers == 0) {
        id = 1;
    } else {
        id = users[numberOfUsers - 1].id + 1;
    }
    user.login = login;
    user.password = password;
    user.id = id;

    users.push_back(user);

    saveUserToTxtFile(user);
}

int userLogin(vector<User> users) {
    string login, password;
    int i = 0, numberOfPersons = users.size();

    system("cls");
    cout << "    |Logowanie|" << endl << endl;
    cout << "Podaj nazwe uzytkownika: ";
    login = loadLine();

    while (i < numberOfPersons) {
        if (users[i].login == login) {
            for (int attempts = 0; attempts < 3; attempts++) {
                cout << "Podaj haslo (Pozostalo prob " << 3 - attempts << "): ";
                password = loadLine();

                if (users[i].password == password) {
                    cout << endl << "Uzytkownik zostal zalogowany!" << endl << endl;
                    system("pause");
                    return users[i].id;
                }
            }
            cout << endl << "Podales 3 razy bledne haslo! Sprobuj ponownie za 3 sekundy." << endl << endl;
            Sleep(3000);
        } else {
            i++;
        }
    }
    cout << endl << "Uzytkownik o podanym loginie nie istnieje!" << endl << endl;
    system("pause");
    return 0;
}

void savePersonToTxtFile(Person person) {
    ofstream file;
    file.open("Adresaci.txt", ios::app);

    if (file.good()) {
        file << person.id << "|";
        file << person.whichUser << "|";
        file << person.name << "|";
        file << person.surname << "|";
        file << person.phoneNumber << "|";
        file << person.email << "|";
        file << person.address << "|" << endl;
        file.close();
    } else {
        cout << "Zapis danych zakonczony niepowodzeniem!" << endl << endl;
    }
    cout << endl << "Zapis danych zakonczony powodzeniem!" << endl << endl;
}

int addPerson(vector<Person> &persons, int loggedInUser, int highestId, int lastDeletedId) {
    Person person;
    int id;
    string name, surname, phoneNumber, email, address;

    if (highestId == 0 && lastDeletedId == 0) {
        id = 1;
    } else if (highestId <= lastDeletedId) {
        id = lastDeletedId + 1;
    } else {
        id = highestId + 1;
    }

    system("cls");
    cout << "  |Dodaj adresata|" << endl << endl;
    cout << "Podaj imie: ";
    name = loadLine();
    cout << "Podaj nazwisko: ";
    surname = loadLine();
    cout << "Podaj numer telefonu: ";
    phoneNumber = loadLine();
    cout << "Podaj email: ";
    email = loadLine();
    cout << "Podaj adres: ";
    address = loadLine();

    person.id = id;
    person.whichUser = loggedInUser;
    person.name = name;
    person.surname = surname;
    person.phoneNumber = phoneNumber;
    person.email = email;
    person.address = address;

    persons.push_back(person);

    savePersonToTxtFile(person);

    highestId = person.id;

    return highestId;
}

void searchByName(vector<Person> persons) {
    int vectorLength = persons.size();
    int noMatch = 0;
    string name;

    system("cls");
    cout << "  |Wyszukaj po imieniu|" << endl << endl;

    if (vectorLength == 0) {
        cout << "Ksiazka adresowa jest pusta!" << endl << endl;
    } else {
        cout << "Podaj imie: ";
        name = loadLine();
        cout << endl;

        for (int i = 0; i < vectorLength; i++) {
            if (persons[i].name == name) {
                cout << "ID:               " << persons[i].id << endl;
                cout << "Imie:             " << persons[i].name << endl;
                cout << "Nazwisko:         " << persons[i].surname << endl;
                cout << "Numer telefonu:   " << persons[i].phoneNumber << endl;
                cout << "Email:            " << persons[i].email << endl;
                cout << "Adres:            " << persons[i].address << endl;
                cout << endl;
            }   else {
                noMatch++;
            }
        }
        if (noMatch == vectorLength) {
            cout << "W ksiazce adresowej nie ma osoby o podanym imieniu!" << endl << endl;
        }
    }
}

void searchBySurname(vector<Person> persons) {
    int vectorLength = persons.size();
    int noMatch = 0;
    string surname;

    system("cls");
    cout << "  |Wyszukaj po nazwisku|" << endl << endl;

    if (vectorLength == 0) {
        cout << "Ksiazka adresowa jest pusta!" << endl << endl;
    } else {
        cout << "Podaj nazwisko: ";
        surname = loadLine();
        cout << endl;

        for (int i = 0; i < vectorLength; i++) {
            if (persons[i].surname == surname) {
                cout << "ID:               " << persons[i].id << endl;
                cout << "Imie:             " << persons[i].name << endl;
                cout << "Nazwisko:         " << persons[i].surname << endl;
                cout << "Numer telefonu:   " << persons[i].phoneNumber << endl;
                cout << "Email:            " << persons[i].email << endl;
                cout << "Adres:            " << persons[i].address << endl;
                cout << endl;
            } else {
                noMatch++;
            }
        }
        if (noMatch == vectorLength) {
            cout << "W ksiazce adresowej nie ma osoby o podanym nazwisku!" << endl << endl;
        }
    }
}

void viewAllPersons(vector<Person> persons) {
    int vectorLength = persons.size();

    system("cls");
    cout << "  |Wyswietl wszystkich adresatow|" << endl << endl;

    if (vectorLength == 0) {
        cout << "Ksiazka adresowa jest pusta!" << endl << endl;
    } else {
        for (int i = 0; i < vectorLength; i++) {
            cout << "ID:               " << persons[i].id << endl;
            cout << "Imie:             " << persons[i].name << endl;
            cout << "Nazwisko:         " << persons[i].surname << endl;
            cout << "Numer telefonu:   " << persons[i].phoneNumber << endl;
            cout << "Email:            " << persons[i].email << endl;
            cout << "Adres:            " << persons[i].address << endl;
            cout << endl;
        }
    }
}

void removePersonDataFromTxtFile(int idToRemove) {
    string line = "", idFromLine = "";
    int idFromLineInt = 0;

    ifstream file;
    file.open("Adresaci.txt");

    ofstream temp;
    temp.open("Przejsciowy plik adresaci.txt");

    if (file.good()) {
        while (getline(file,line)) {
            int lineLength = line.length();

            for (int i = 0; i < lineLength; i++) {
                if (line[i] != '|') {
                    idFromLine += line[i];
                } else {
                    break;
                }
            }
            idFromLineInt = atoi(idFromLine.c_str());

            if (idFromLineInt != idToRemove) {
                temp << line << endl;
            }
            idFromLineInt = 0;
            idFromLine = "";
        }
        temp.close();
        file.close();

        remove("Adresaci.txt");
        rename("Przejsciowy plik adresaci.txt", "Adresaci.txt");
    } else {
        cout << "Usuwanie danych z pliku zakonczone niepowodzeniem!" << endl << endl;
    }
}

int removePersonData(vector<Person> &persons) {
    int idToRemove, noMatch = 0, vectorLength = persons.size();
    string idStr;
    char sign;

    system("cls");
    cout << "       |Usun adresata|" << endl << endl;

    if (vectorLength == 0) {
        cout << "Ksiazka adresowa jest pusta!" << endl << endl;
    } else {
        cout << "Podaj numer identyfikacyjny osoby, ktora chcesz usunac: ";
        idStr = loadLine();

        idToRemove = atoi(idStr.c_str());

        for (int i = 0; i < vectorLength; i++) {
            if (persons[i].id == idToRemove) {
                cout << endl;
                cout << "ID:               " << persons[i].id << endl;
                cout << "Imie:             " << persons[i].name << endl;
                cout << "Nazwisko:         " << persons[i].surname << endl;
                cout << "Numer telefonu:   " << persons[i].phoneNumber << endl;
                cout << "Email:            " << persons[i].email << endl;
                cout << "Adres:            " << persons[i].address << endl;
                cout << endl;
                cout << "Czy na pewno chcesz usunac dana osobe? [t/n] ";
                sign = loadSign();

                if (sign == 't') {
                    auto iterator = persons.begin() + i;
                    persons.erase(iterator);

                    removePersonDataFromTxtFile(idToRemove);

                    cout << endl << "Usuwanie danych zakonczone powodzeniem!" << endl << endl;
                    break;
                } else if (sign == 'n') {
                    cout << endl << "Wstrzymano usuwanie danych!" << endl << endl;
                } else {
                    cout << endl << "Musisz wpisac tak[t] lub nie[n]!" << endl << endl;
                }
            }  else {
                noMatch++;
            }
        }
        if (noMatch == vectorLength) {
            cout << endl << "W ksiazce adresowej nie ma osoby o podanym numerze identyfikacyjnym!" << endl << endl;
        } else if (persons.size() == 0) {
            cout << "Ksiazka adresowa jest teraz pusta!" << endl << endl;
        }
    }
    return idToRemove;
}

void changeDataInTxtFile(vector<string> dataToChange, int idToEdit) {
    string oldData = dataToChange[0], newData = dataToChange[1];
    int oldDataLength = oldData.length(), idFromLineInt = 0;
    string line = "", idFromLine = "";

    ifstream file;
    file.open("Adresaci.txt");
    ofstream temp;
    temp.open("Przejsciowy plik adresaci.txt");

    while (getline(file,line)) {
        int lineLength = line.length();

        for (int i = 0; i < lineLength; i++) {
            if (line[i] != '|') {
                idFromLine += line[i];
            } else {
                break;
            }
        }
        idFromLineInt = atoi(idFromLine.c_str());

        if (idFromLineInt == idToEdit) {
            line.replace(line.find(oldData), oldDataLength, newData);
            temp << line << endl;
        } else {
            temp << line << endl;
        }
        idFromLineInt = 0;
        idFromLine = "";
    }
    temp.close();
    file.close();

    remove("Adresaci.txt");
    rename("Przejsciowy plik adresaci.txt", "Adresaci.txt");
}

void selectDataToEdit(vector<Person> &persons, int idToEdit) {
    char choice;
    int vectorLength = persons.size();
    string name, surname, phoneNumber, email, address;
    vector<string> dataToChange;

    system ("cls");
    cout << "  |Edytuj dana adresata|" << endl << endl;
    cout << "Wybierz dane do edycji: " << endl;
    cout << "1. Imie" << endl;
    cout << "2. Nazwisko" << endl;
    cout << "3. Numer telefonu" << endl;
    cout << "4. Email" << endl;
    cout << "5. Adres" << endl;
    cout << "6. Powrot do menu" << endl;
    cout << endl << "Twoj wybor: ";
    choice = loadSign();
    cout << endl;

    switch (choice) {
    case '1':
        system("cls");
        cout << "  |Imie|" << endl << endl;

        for (int i = 0; i < vectorLength; i++) {
            if (persons[i].id == idToEdit) {
                cout << "Stare: " << persons[i].name << endl;
                cout << "Nowe: ";
                name = loadLine();

                dataToChange.push_back(persons[i].name);
                dataToChange.push_back(name);

                persons[i].name = name;
            }
        }
        changeDataInTxtFile(dataToChange, idToEdit);
        cout << endl << "Edycja danych zakonczona powodzeniem!" << endl << endl;
        system("pause");
        break;
    case '2':
        system("cls");
        cout << "  |Nazwisko|" << endl << endl;

        for (int i = 0; i < vectorLength; i++) {
            if (persons[i].id == idToEdit) {
                cout << "Stare: " << persons[i].surname << endl;
                cout << "Nowe: ";
                surname = loadLine();

                dataToChange.push_back(persons[i].surname);
                dataToChange.push_back(surname);

                persons[i].surname = surname;
            }
        }
        changeDataInTxtFile(dataToChange, idToEdit);

        cout << endl << "Edycja danych zakonczona powodzeniem!" << endl << endl;
        system("pause");
        break;
    case '3':
        system("cls");
        cout << "  |Numer telefonu|" << endl << endl;

        for (int i = 0; i < vectorLength; i++) {
            if (persons[i].id == idToEdit) {
                cout << "Stary: " << persons[i].phoneNumber << endl;
                cout << "Nowy: ";
                phoneNumber = loadLine();

                dataToChange.push_back(persons[i].phoneNumber);
                dataToChange.push_back(phoneNumber);

                persons[i].phoneNumber = phoneNumber;
            }
        }
        changeDataInTxtFile(dataToChange, idToEdit);

        cout << endl << "Edycja danych zakonczona powodzeniem!" << endl << endl;
        system("pause");
        break;
    case '4':
        system("cls");
        cout << "  |Email|" << endl << endl;

        for (int i = 0; i < vectorLength; i++) {
            if (persons[i].id == idToEdit) {
                cout << "Stary: " << persons[i].email << endl;
                cout << "Nowy: ";
                email = loadLine();

                dataToChange.push_back(persons[i].email);
                dataToChange.push_back(email);

                persons[i].email = email;
            }
        }
        changeDataInTxtFile(dataToChange, idToEdit);

        cout << endl << "Edycja danych zakonczona powodzeniem!" << endl << endl;
        system("pause");
        break;
    case '5':
        system("cls");
        cout << "  |Adres|" << endl << endl;

        for (int i = 0; i < vectorLength; i++) {
            if (persons[i].id == idToEdit) {
                cout << "Stary: " << persons[i].address << endl;
                cout << "Nowy: ";
                address = loadLine();

                dataToChange.push_back(persons[i].address);
                dataToChange.push_back(address);

                persons[i].address = address;
            }
        }
        changeDataInTxtFile(dataToChange, idToEdit);

        cout << endl << "Edycja danych zakonczona powodzeniem!" << endl << endl;
        system("pause");
        break;
    case '6':
        break;
    default:
        cout << "Musisz wybrac cyfre od 1 do 6!" << endl;
        Sleep(1500);
        break;
    }
}

void editPersonData(vector<Person> &persons) {
    string idStr;
    int idToEdit, noMatch = 0, vectorLength = persons.size();
    char sign;

    system("cls");
    cout << "        |Edytuj dane adresata|" << endl << endl;

    if (vectorLength == 0) {
        cout << "Ksiazka adresowa jest pusta!" << endl << endl;
        system("pause");
    } else {
        cout << "Podaj numer identyfikacyjny osoby, ktorej chcesz edytowac dane: ";
        idStr = loadLine();
        idToEdit = atoi(idStr.c_str());

        for (int i = 0; i < vectorLength; i++) {
            if (persons[i].id == idToEdit) {
                cout << endl;
                cout << "ID:               " << persons[i].id << endl;
                cout << "Imie:             " << persons[i].name << endl;
                cout << "Nazwisko:         " << persons[i].surname << endl;
                cout << "Numer telefonu:   " << persons[i].phoneNumber << endl;
                cout << "Email:            " << persons[i].email << endl;
                cout << "Adres:            " << persons[i].address << endl;
                cout << endl;
                cout << "Czy chcesz edytowac dane podanej osoby? [t/n] ";
                sign = loadSign();

                if (sign == 't') {
                    selectDataToEdit(persons, idToEdit);
                    break;
                } else if (sign == 'n') {
                    cout << endl << "Wstrzymano edycje danych!" << endl << endl;
                    system("pause");
                } else {
                    cout << endl << "Musisz wpisac tak[t] lub nie[n]!" << endl << endl;
                    Sleep(1500);
                }
            }  else {
                noMatch++;
            }
        }
        if (noMatch == vectorLength) {
            cout << endl << "W ksiazce adresowej nie ma osoby o podanym numerze identyfikacyjnym!" << endl << endl;
            system("pause");
        }
    }
}

void changeUserPasswordInTxtFile(int loggedInUser, vector<string> dataToChange) {
    string oldData = dataToChange[0], newData = dataToChange[1];
    int oldDataLength = oldData.length();
    string line = "", idFromLine = "";
    int idFromLineInt = 0;

    ifstream file;
    file.open("Uzytkownicy.txt");
    ofstream temp;
    temp.open("Przejsciowy plik uzytkownicy.txt");

    if (file.good()) {
        while (getline(file,line)) {
            int lineLength = line.length();
            for (int i = 0; i < lineLength; i++) {
                if (line[i] != '|') {
                    idFromLine += line[i];
                } else {
                    break;
                }
            }
            idFromLineInt = atoi(idFromLine.c_str());

            if (idFromLineInt == loggedInUser) {
                line.replace(line.find(oldData), oldDataLength, newData);
                temp << line << endl;
            } else {
                temp << line << endl;
            }
            idFromLineInt = 0;
            idFromLine = "";
        }
        temp.close();
        file.close();

        remove("Uzytkownicy.txt");
        rename("Przejsciowy plik uzytkownicy.txt", "Uzytkownicy.txt");

        cout << endl << "Zmiana hasla zakonczona powodzeniem!" << endl << endl;
    } else {
        cout << endl << "Zmiana hasla zakonczona niepowodzeniem!" << endl << endl;
    }
}

void editUserPassword(vector<User> &users, int &loggedInUser) {
    string newPassword, oldPassword;
    vector<string> dataToChange;

    system("cls");
    cout << "   |Zmien haslo|" << endl << endl;

    cout << "Podaj aktualne haslo: ";
    oldPassword = loadLine();

    if (users[loggedInUser - 1].password == oldPassword) {
        cout << "Podaj nowe haslo: ";
        newPassword = loadLine();

        users[loggedInUser - 1].password = newPassword;

        dataToChange.push_back(oldPassword);
        dataToChange.push_back(newPassword);

        changeUserPasswordInTxtFile(loggedInUser, dataToChange);
    } else {
        cout << endl<< "Podales bledne haslo uzytkownika! Uzytkownik zostal wylogowany!" << endl << endl;
        loggedInUser = 0;
    }
}

int logOut() {
    system("cls");
    cout << endl << "Uzytkownik zostal wylogowany!" << endl << endl;
    return 0;
}

int main() {
    char choice;
    vector<Person> persons;
    vector<User> users;
    int loggedInUser = 0;
    int highestId = 0, lastDeletedId = 0;

    loadUsersFromFile(users);

    while (true) {
        if (loggedInUser == 0) {
            system ("cls");
            cout << "  |Menu glowne|" << endl << endl;
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "3. Zakoncz program" << endl;
            cout << endl << "Twoj wybor: ";
            choice = loadSign();
            cout << endl;

            switch (choice) {
            case '1':
                userRegistration(users);
                system("pause");
                break;
            case '2':
                loggedInUser = userLogin(users);
                highestId = loadPersonsFromFile(persons, loggedInUser);
                break;
            case '3':
                system("cls");
                cout << endl << "Do zobaczenia!" << endl;
                exit(0);
            default:
                cout << "Musisz wpisac cyfre od 1 do 3!" << endl << endl;
                Sleep(1500);
                break;
            }
        } else {
            system ("cls");
            cout << "  |Menu uzytkownika|" << endl << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj dane adresata" << endl;
            cout << "------------------------" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "9. Wyloguj sie" << endl;
            cout << endl << "Twoj wybor: ";
            choice = loadSign();
            cout << endl;

            switch (choice) {
            case '1':
                highestId = addPerson(persons, loggedInUser, highestId, lastDeletedId);
                system("pause");
                break;
            case '2':
                searchByName(persons);
                system("pause");
                break;
            case '3':
                searchBySurname(persons);
                system("pause");
                break;
            case '4':
                viewAllPersons(persons);
                system("pause");
                break;
            case '5':
                lastDeletedId = removePersonData(persons);
                system("pause");
                break;
            case '6':
                editPersonData(persons);
                break;
            case '7':
                editUserPassword(users, loggedInUser);
                system("pause");
                break;
            case '9':
                loggedInUser = logOut();
                persons.clear();
                system("pause");
                break;
            default:
                cout << "Musisz wpisac cyfre od 1 do 9 z pominieciem 8!" << endl << endl;
                Sleep(1500);
                break;
            }
        }
    }
    return 0;
}
