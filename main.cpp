#include <iostream>
#include <string>
#include <set>
#include <deque>
#include <list>
#include <map>
#include <algorithm>
#include <ctime>

using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

class Utilisateur {
private:
    int id;
    string email;
    string nom;
    string adresse;
    set<int> paiements; // IDs des paiements associés à l'utilisateur
public:
    // Constructeur
    Utilisateur(int _id, const string& _email, const string& _nom, const string& _adresse)
        : id(_id), email(_email), nom(_nom), adresse(_adresse) {}

    // Destructeur
    ~Utilisateur() {}

    // Getters
    int getId() const {return id; }
    string getEmail() const { return email; }
    string getNom() const { return nom; }
    string getAdresse() const { return adresse; }

    // Setters
    void setEmail(const string& _email) { email = _email; }
    void setNom(const string& _nom) { nom = _nom; }
    void setAdresse(const string& _adresse) { adresse = _adresse; }


    // Autres méthodes
    void ajouterPaiement(int paiement_id) { paiements.insert(paiement_id); }
    void supprimerPaiement(int paiement_id) { paiements.erase(paiement_id); }
    int nombrePaiements() const { return paiements.size(); }
     // Surcharge de l'opérateur < pour comparer les Utilisateur par leur ID
    bool operator<(const Utilisateur& other) const {
        return id < other.id;
    }
};


class Paiement {
protected:
    int id_paiement;
    Date date;
    int utilisateur_id;
    int facture_id;
public:
    // Constructeur
    Paiement(int _id_paiement, const Date& _date, int _utilisateur_id, int _facture_id)
        : id_paiement(_id_paiement), date(_date), utilisateur_id(_utilisateur_id), facture_id(_facture_id) {}

    // Destructeur
    virtual ~Paiement() {}

    // Getters
    int getIdPaiement() const { return id_paiement; }
    Date getDate() const { return date; }
    int getUtilisateurId() const { return utilisateur_id; }
    int getFactureId() const { return facture_id; }

    // Setters
    void setDate(const Date& _date) { date = _date; }

    // Méthode virtuelle pure
    virtual void afficherDetails() const = 0;
};


class Cheque : public Paiement {
private:
    int numero_cheque;
    string proprietaire;
    Date date_encaissement;
public:
    // Constructeur
    Cheque(int _id_paiement, const Date& _date, int _utilisateur_id, int _facture_id,
           int _numero_cheque, const string& _proprietaire, const Date& _date_encaissement)
        : Paiement(_id_paiement, _date, _utilisateur_id, _facture_id),
          numero_cheque(_numero_cheque), proprietaire(_proprietaire), date_encaissement(_date_encaissement) {}

    // Destructeur
    ~Cheque() {}

    // Getters
    int getNumeroCheque() const { return numero_cheque; }
    string getProprietaire() const { return proprietaire; }
    Date getDateEncaissement() const { return date_encaissement; }

    // Setters
    void setNumeroCheque(int _numero_cheque) { numero_cheque = _numero_cheque; }
    void setProprietaire(const string& _proprietaire) { proprietaire = _proprietaire; }
    void setDateEncaissement(const Date& _date_encaissement) { date_encaissement = _date_encaissement; }

    // Implémentation de la méthode virtuelle pure
    void afficherDetails() const override {
        cout << "Paiement par chèque : "
                  << "Numéro de chèque : " << numero_cheque
                  << ", Propriétaire : " << proprietaire
                  << ", Date d'encaissement : " << date_encaissement.day << "/" << date_encaissement.month << "/" << date_encaissement.year
                  << endl;
    }
};


class Paypal : public Paiement {
private:
    string email_compte;
public:
    // Constructeur
    Paypal(int _id_paiement, const Date& _date, int _utilisateur_id, int _facture_id,
           const string& _email_compte)
        : Paiement(_id_paiement, _date, _utilisateur_id, _facture_id), email_compte(_email_compte) {}

    // Destructeur
    ~Paypal() {}

    // Getter
    string getEmailCompte() const { return email_compte; }

    // Setter
    void setEmailCompte(const string& _email_compte) { email_compte = _email_compte; }

    // Implémentation de la méthode virtuelle pure
    void afficherDetails() const override {
        cout << "Paiement par Paypal : "
                  << "Email du compte : " << email_compte
                  << endl;
    }
};


class Cartes : public Paiement {
private:
    string numero_carte;
    string nom_proprietaire;
    string CSV;
    Date date_expiration;
public:
    // Constructeur
    Cartes(int _id_paiement, const Date& _date, int _utilisateur_id, int _facture_id,
           const string& _numero_carte, const string& _nom_proprietaire,
           const string& _CSV, const Date& _date_expiration)
        : Paiement(_id_paiement, _date, _utilisateur_id, _facture_id),
          numero_carte(_numero_carte), nom_proprietaire(_nom_proprietaire),
          CSV(_CSV), date_expiration(_date_expiration) {}

    // Destructeur
    ~Cartes() {}

    // Getters
    string getNumeroCarte() const { return numero_carte; }
    string getNomProprietaire() const { return nom_proprietaire; }
    string getCSV() const { return CSV; }
    Date getDateExpiration() const { return date_expiration; }

    // Setters
    void setNumeroCarte(const string& _numero_carte) { numero_carte = _numero_carte; }
    void setNomProprietaire(const string& _nom_proprietaire) { nom_proprietaire = _nom_proprietaire; }
    void setCSV(const string& _CSV) { CSV = _CSV; }
    void setDateExpiration(const Date& _date_expiration) { date_expiration = _date_expiration; }

    // Implémentation de la méthode virtuelle pure
    void afficherDetails() const override {
        cout << "Paiement par carte : "
                  << "Numéro de carte : " << numero_carte
                  << ", Nom du propriétaire : " << nom_proprietaire
                  << ", Date d'expiration : " << date_expiration.day << "/" << date_expiration.month << "/" << date_expiration.year
                  << endl;
    }
};

// Surcharge de l'opérateur << pour afficher une Date
ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.day << "/" << date.month << "/" << date.year;
    return os;
}

class Facture {
private:
    int numero_facture;
    Date date;
    double total;
    map<int, double> services; // ID du service -> Prix
    int identifiant_fournisseur;
    string nom_utilisateur;
    string type_paiement;
public:
    // Constructeur
   Facture(int _numero_facture, const Date& _date, double _prixHT, int _identifiant_fournisseur, const std::string& _nom_utilisateur, const std::string& _type_paiement)
        : numero_facture(_numero_facture), date(_date), total(_prixHT), identifiant_fournisseur(_identifiant_fournisseur), nom_utilisateur(_nom_utilisateur), type_paiement(_type_paiement) {}
    // Constructeur prenant un int, un objet Date et un double
Facture(int _numero_facture, Date _date, double _prixHT)
    : numero_facture(_numero_facture), date(_date), total(_prixHT) {}
    // Destructeur
    ~Facture() {}

    // Getters
    int getNumeroFacture() const { return numero_facture; }
    Date getDate() const { return date; }
    double getTotal() const { return total; }
    map<int, double> getServices() const { return services; }

    Facture() : numero_facture(0), total(0.0) {
    // Initialisation des autres membres si nécessaire
}


    // Autres méthodes
    void ajouterService(int service_id, double prix) { services[service_id] = prix; }
    void supprimerService(int service_id) { services.erase(service_id); } // Méthode pour supprimer un service

    void appliquerTVA() {
        // Implémentez la logique pour appliquer la TVA de 20% sur les prix des services
        for (auto& service : services) {
            service.second *= 1.20;
        }
        total *= 1.20;
    }

    void appliquerReduction() {
        // Implémentez la logique pour appliquer une réduction de 15% sur les factures dont le total est supérieur à 25000dh
        if (total > 25000) {
            total *= 0.85;
        }
    }

    void imprimerFacture() const {
        // Afficher les informations de la facture
        cout << "Numéro facture: " << numero_facture << endl;
        cout << "Date facture: " << date.day << "/" << date.month << "/" << date.year << std::endl;
        cout << "Identifiant fournisseur: " << identifiant_fournisseur << endl;
        cout << "Nom utilisateur: " << nom_utilisateur << endl;
        cout << "Type de paiement: " << type_paiement << endl;

        // Afficher la liste des services
        cout << "Liste des services:" << endl;
        cout << "Référence service\tDate\tType\tPrix" << endl;
        for (const auto& service : services) {
            cout << service.first << "\t"; // ID du service
            cout << date << "\t";
            cout << "Type\t"; // Type (à définir)
            cout << service.second << endl; // Prix
        }

        // Afficher le total à payer
        cout << "Total à payer: " << total << endl;
    }
};

class Service {
private:
    int reference_service;
    Date date;
    double prixHT;
    string type_service;
public:
    // Constructeur
    Service(int _reference_service, const Date& _date, double _prixHT, const string& _type_service)
        : reference_service(_reference_service), date(_date), prixHT(_prixHT), type_service(_type_service) {}

    // Destructeur
    ~Service() {}

    // Getters
    int getReferenceService() const { return reference_service; }
    Date getDate() const { return date; }
    double getPrixHT() const { return prixHT; }
    string getTypeService() const { return type_service; }

    // Setters
    void setReferenceService(int _reference_service) { reference_service = _reference_service; }
    void setDate(const Date& _date) { date = _date; }
    void setPrixHT(double _prixHT) { prixHT = _prixHT; }
    void setTypeService(const string& _type_service) { type_service = _type_service; }

    // Autres méthodes
    void afficherService() const {
        cout << "Référence service : " << reference_service << endl;
        cout << "Date : " << date.day << "/" << date.month << "/" << date.year << endl;
        cout << "Prix HT : " << prixHT << endl;
        cout << "Type service : " << type_service << endl;
    }
};

// Fonction de gestion des utilisateurs
void gestionUtilisateur(set<Utilisateur>& utilisateurs) {
    int choix;
    do {
        cout << "Menu Gestion Utilisateur" << endl;
        cout << "1. Ajouter un utilisateur" << endl;
        cout << "2. Supprimer un utilisateur" << endl;
        cout << "3. Afficher le nombre de paiements de chaque utilisateur" << endl;
        cout << "0. Retour au menu principal" << endl;
        cout << "Choix : ";
        cin >> choix;

        switch (choix) {
            case 1: {
                // Ajouter un utilisateur
                int id;
                string email, nom, adresse;
                cout << "ID : ";
                cin >> id;
                cout << "Email : ";
                cin >> email;
                cout << "Nom : ";
                cin >> nom;
                cout << "Adresse : ";
                cin >> adresse;
                utilisateurs.insert(Utilisateur(id, email, nom, adresse));
                break;
            }
            case 2: {
                // Supprimer un utilisateur
                int id;
                cout << "ID de l'utilisateur à supprimer : ";
                cin >> id;
                auto it = utilisateurs.begin();
                while (it != utilisateurs.end()) {
                    if (it->getId() == id) {
                        it = utilisateurs.erase(it);
                        cout << "Utilisateur supprimé avec succès." << endl;
                        break;
                    } else {
                        ++it;
                    }
                }
                if (it == utilisateurs.end()) {
                    cout << "Utilisateur non trouvé." << endl;
                }
                break;
            }
            case 3: {
                // Afficher le nombre de paiements de chaque utilisateur
                for (const auto& utilisateur : utilisateurs) {
                    cout << "Utilisateur ID : " << utilisateur.getId() << ", Nombre de paiements : " << utilisateur.nombrePaiements() << endl;
                }
                break;
            }
            case 0:
                cout << "Retour au menu principal." << endl;
                break;
            default:
                cout << "Choix invalide. Veuillez réessayer." << endl;
        }
    } while (choix != 0);
}

// Fonction pour ajouter un paiement
void ajouterPaiement(deque<Paiement*>& paiements) {
    int choix;
    do {
        int id, utilisateur_id, facture_id;
        Date date;

        cout << "ID du paiement : ";
        cin >> id;

        cout << "Date du paiement (jj mm aaaa) : ";
        cin >> date.day >> date.month >> date.year;

        cout << "ID de l'utilisateur : ";
        cin >> utilisateur_id;

        cout << "ID de la facture : ";
        cin >> facture_id;

        // Sélectionner le type de paiement
        cout << "Choisissez le type de paiement : " << endl;
        cout << "1. Chèque" << endl;
        cout << "2. Paypal" << endl;
        cout << "3. Carte" << endl;
        cout << "0. Annuler l'ajout de paiement" << endl;
        cin >> choix;

        switch (choix) {
            case 1: {
                int numero_cheque;
                string proprietaire;
                Date date_encaissement;

                cout << "Numéro du chèque : ";
                cin >> numero_cheque;

                cout << "Propriétaire : ";
                cin >> proprietaire;

                cout << "Date d'encaissement (jj mm aaaa) : ";
                cin >> date_encaissement.day >> date_encaissement.month >> date_encaissement.year;

                paiements.push_back(new Cheque(id, date, utilisateur_id, facture_id, numero_cheque, proprietaire, date_encaissement));
                break;
            }
            case 2: {
                string email_compte;

                cout << "Email du compte Paypal : ";
                cin >> email_compte;

                paiements.push_back(new Paypal(id, date, utilisateur_id, facture_id, email_compte));
                break;
            }
            case 3: {
                string numero_carte, nom_proprietaire, CSV;
                Date date_expiration;

                cout << "Numéro de carte : ";
                cin >> numero_carte;

                cout << "Nom du propriétaire : ";
                cin >> nom_proprietaire;

                cout << "CSV : ";
                cin >> CSV;

                cout << "Date d'expiration (jj mm aaaa) : ";
                cin >> date_expiration.day >> date_expiration.month >> date_expiration.year;

                paiements.push_back(new Cartes(id, date, utilisateur_id, facture_id, numero_carte, nom_proprietaire, CSV, date_expiration));
                break;
            }
            case 0:
                cout << "Annulation de l'ajout de paiement." << endl;
                break;
            default:
                cout << "Choix de type de paiement invalide." << endl;
        }
    } while (choix != 0);
}


// Fonction pour modifier un paiement dans la deque
void modifierPaiement(deque<Paiement*>& paiements) {
    int id;
    cout << "Entrez l'ID du paiement à modifier : ";
    cin >> id;
    for (auto& paiement : paiements) {
        if (paiement->getIdPaiement() == id) {
            Date date;
            cout << "Entrez la nouvelle date du paiement (jour mois année) : ";
            cin >> date.day >> date.month >> date.year;
            paiement->setDate(date);
            cout << "Paiement modifié avec succès." << endl;
            return;
        }
    }
    cout << "Paiement non trouvé." << endl;
}

// Fonction pour supprimer un paiement dans la deque
void supprimerPaiement(deque<Paiement*>& paiements) {
    int id;
    cout << "Entrez l'ID du paiement à supprimer : ";
    cin >> id;
    for (auto it = paiements.begin(); it != paiements.end(); ++it) {
        if ((*it)->getIdPaiement() == id) {
            delete *it;
            paiements.erase(it);
            cout << "Paiement supprimé avec succès." << endl;
            return;
        }
    }
    cout << "Paiement non trouvé." << endl;
}

// Fonction pour afficher tous les paiements dans la deque
void afficherPaiements(const deque<Paiement*>& paiements) {
    if (paiements.empty()) {
        cout << "Aucun paiement à afficher." << endl;
        return;
    }
    cout << "Liste des paiements : " << endl;
    for (const auto& paiement : paiements) {
        paiement->afficherDetails();
    }
}

// Fonction de gestion des paiements
void gestionPaiement(deque<Paiement*>& paiements) {
    int choix;
    do {
        cout << "Menu Gestion Paiement" << endl;
        cout << "1. Ajouter un paiement" << endl;
        cout << "2. Modifier un paiement" << endl;
        cout << "3. Supprimer un paiement" << endl;
        cout << "4. Afficher tous les paiements" << endl;
        cout << "0. Retour au menu principal" << endl;
        cout << "Choix : ";
        cin >> choix;

        switch (choix) {
            case 1:
                ajouterPaiement(paiements);
                break;
            case 2:
                modifierPaiement(paiements);
                break;
            case 3:
                supprimerPaiement(paiements);
                break;
            case 4:
                afficherPaiements(paiements);
                break;
            case 0:
                cout << "Retour au menu principal." << endl;
                break;
            default:
                cout << "Choix invalide. Veuillez réessayer." << endl;
        }
    } while (choix != 0);
}

// Fonction pour gérer les services
void gestionService(list<Service>& services) {
    int choix;
    do {
        cout << "Menu Gestion Service" << endl;
        cout << "1. Ajouter un service" << endl;
        cout << "2. Modifier un service" << endl;
        cout << "3. Supprimer un service" << endl;
        cout << "4. Afficher les services dont le prix dépasse 200dh" << endl;
        cout << "5. Afficher le nombre des services effectués dans les 6 derniers mois" << endl;
        cout << "0. Retour au menu principal" << endl;
        cout << "Choix : ";
        cin >> choix;

        switch (choix) {
            case 1: {
                // Ajouter un service
                int reference;
                Date date;
                double prix;
                string type;

                cout << "Référence : ";
                cin >> reference;
                cout << "Date (jj mm aaaa) : ";
                cin >> date.day >> date.month >> date.year;
                cout << "Prix HT : ";
                cin >> prix;
                cout << "Type de service : ";
                cin >> type;

                services.push_back(Service(reference, date, prix, type));
                break;
            }
            case 2:
                {
                // Modifier un service
                int reference;
                cout << "Entrez la référence du service à modifier : ";
                cin >> reference;

                // Recherche du service à modifier
                auto it = find_if(services.begin(), services.end(), [reference](const Service& s) { return s.getReferenceService() == reference; });

                if (it != services.end()) {
                    // Service trouvé, demander les nouvelles informations
                    Date date;
                    double prix;
                    string type;

                    cout << "Nouvelle date (jj mm aaaa) : ";
                    cin >> date.day >> date.month >> date.year;
                    cout << "Nouveau prix HT : ";
                    cin >> prix;
                    cout << "Nouveau type de service : ";
                    cin >> type;

                    // Mettre à jour les informations du service
                    it->setDate(date);
                    it->setPrixHT(prix);
                    it->setTypeService(type);
                    cout << "Service modifié avec succès." << endl;
                } else {
                    cout << "Service introuvable." << endl;
                }
                break;
            }
                break;
            case 3:
                {
                // Supprimer un service
                int reference;
                cout << "Entrez la référence du service à supprimer : ";
                cin >> reference;

                // Recherche du service à supprimer
                auto it = find_if(services.begin(), services.end(), [reference](const Service& s) { return s.getReferenceService() == reference; });

                if (it != services.end()) {
                    services.erase(it);
                    cout << "Service supprimé avec succès." << endl;
                } else {
                    cout << "Service introuvable." << endl;
                }
                break;
            }
                break;
            case 4: {
                // Afficher les services dont le prix dépasse 200dh
                cout << "Services dont le prix dépasse 200dh :" << endl;
                for (const auto& service : services) {
                    if (service.getPrixHT() > 200) {
                        service.afficherService();
                    }
                }
                break;
            }
            case 5: {
                // Afficher le nombre des services effectués dans les 6 derniers mois
                time_t now = time(nullptr);
                tm* localTime = localtime(&now);
                int currentMonth = localTime->tm_mon + 1;
                int currentYear = localTime->tm_year + 1900;

                int servicesCount = 0;
                for (const auto& service : services) {
                    if ((currentYear - service.getDate().year) * 12 + currentMonth - service.getDate().month <= 6) {
                        servicesCount++;
                    }
                }
                cout << "Nombre des services effectués dans les 6 derniers mois : " << servicesCount << endl;
                break;
            }
            case 0:
                cout << "Retour au menu principal." << endl;
                break;
            default:
                cout << "Choix invalide. Veuillez réessayer." << endl;
        }
    } while (choix != 0);
}

void modifierServiceDansFacture(map<int, Facture>& factures) {
    int numero_facture;
    cout << "Entrez le numéro de la facture que vous souhaitez modifier : ";
    cin >> numero_facture;

    auto it = factures.find(numero_facture);
    if (it != factures.end()) {
        int reference_service;
        cout << "Entrez la référence du service à modifier dans la facture : ";
        cin >> reference_service;

        // Recherche du service dans la facture
        auto service_it = it->second.getServices().find(reference_service);
        if (service_it != it->second.getServices().end()) {
            // Service trouvé, demander les nouvelles informations
            double nouveau_prix;
            cout << "Entrez le nouveau prix du service : ";
            cin >> nouveau_prix;

            // Mettre à jour le prix du service dans la facture
            service_it->second = nouveau_prix;
            cout << "Service modifié avec succès dans la facture." << endl;
        } else {
            cout << "Service introuvable dans la facture." << endl;
        }
    } else {
        cout << "Facture non trouvée." << endl;
    }
}


void modifierFacture(map<int, Facture>& factures, const list<Service>& services) {
    int numero_facture;
    cout << "Entrez le numéro de la facture que vous souhaitez modifier : ";
    cin >> numero_facture;

    auto it = factures.find(numero_facture);
    if (it != factures.end()) {
        int choix;
        do {
            cout << "Menu Modification Facture" << endl;
            cout << "1. Ajouter un service" << endl;
            cout << "2. Modifier un service" << endl;
            cout << "3. Supprimer un service" << endl;
            cout << "0. Retour au menu principal" << endl;
            cout << "Choix : ";
            cin >> choix;

            switch (choix) {
                case 1: {
                    // Ajouter un service à la facture
                    int reference_service;
                    cout << "Entrez la référence du service à ajouter : ";
                    cin >> reference_service;
                    auto service_it = find_if(services.begin(), services.end(), [reference_service](const Service& s) { return s.getReferenceService() == reference_service; });
                    if (service_it != services.end()) {
                        it->second.ajouterService(service_it->getReferenceService(), service_it->getPrixHT());
                        cout << "Service ajouté avec succès à la facture." << endl;
                    } else {
                        cout << "Service non trouvé." << endl;
                    }
                    break;
                }
                case 2: {
                    // Modifier un service dans la facture
                    modifierServiceDansFacture(factures); // Appel de la fonction
                break;
                        }
                case 3: {
                    // Supprimer un service de la facture
                    int reference_service;
                    cout << "Entrez la référence du service à supprimer : ";
                    cin >> reference_service;
                    it->second.supprimerService(reference_service);
                    cout << "Service supprimé avec succès de la facture." << endl;
                    break;
                }
                case 0:
                    cout << "Retour au menu principal." << endl;
                    break;
                default:
                    cout << "Choix invalide. Veuillez réessayer." << endl;
            }
        } while (choix != 0);
    } else {
        cout << "Facture non trouvée." << endl;
    }
}

void gestionFactures(const list<Service>& services, const deque<Paiement*>& paiements) {
    map<int, Facture> factures; // Numéro de facture -> Facture

    // Demander à l'utilisateur de remplir les factures
    int numero_facture = 1;
    for (const auto& service : services) {
        // Générer une facture pour chaque service
        Facture nouvelle_facture(numero_facture++, Date{2, 1, 2024}, service.getPrixHT());
        nouvelle_facture.ajouterService(service.getReferenceService(), service.getPrixHT());

        // Appliquer la TVA sur la facture
        nouvelle_facture.appliquerTVA();

        // Ajouter la facture au map
        factures[nouvelle_facture.getNumeroFacture()] = nouvelle_facture;
    }

    // Permettre à l'utilisateur d'ajouter/modifier/supprimer un service pour une facture donnée
    int choix;
    do {
        cout << "Menu Gestion Factures" << endl;
        cout << "1. Ajouter/Modifier/Supprimer un service pour une facture donnée" << endl;
        cout << "2. Afficher les details de la facture" << endl;
        cout << "0. Retour au menu principal" << endl;
        cout << "Choix : ";
        cin >> choix;

        switch (choix) {
            case 1: {
                // Modifier une facture
                modifierFacture(factures, services);
                break;
            }
            case 2:
                 // Afficher les détails de chaque facture
                   for (const auto& facture : factures) {
                        facture.second.imprimerFacture();
                        cout << endl;
                   }
                break;
            case 0:
                cout << "Retour au menu principal." << endl;
                break;
            default:
                cout << "Choix invalide. Veuillez réessayer." << endl;
        }
    } while (choix != 0);

    // Appliquer une réduction de 15% sur les factures dont le total est supérieur à 25000dh
    for (auto& facture : factures) {
        facture.second.appliquerReduction();
    }

    // Afficher pour chaque facture l'imprimé facture
    for (const auto& facture : factures) {
        facture.second.imprimerFacture();
        cout << endl;
    }
}


int main() {
    set<Utilisateur> utilisateurs;

     // Simuler des données pour les services et les paiements
    list<Service> services;
    services.push_back(Service(1, {1, 1, 2024}, 30000, "Service A"));
    services.push_back(Service(2, {15, 3, 2024}, 15000, "Service B"));

    deque<Paiement*> paiements;
    paiements.push_back(new Cheque(1, {2, 1, 2024}, 1, 1, 1234, "Propriétaire", {2, 1, 2024}));
    paiements.push_back(new Paypal(2, {5, 4, 2024}, 2, 2, "example@example.com"));
    paiements.push_back(new Cartes(3, {10, 6, 2024}, 3, 3, "1234567890123456", "Propriétaire", "123", {2, 1, 2024}));

    map<int, Facture> factures;

    int choix;
    do {
        cout << "Menu Principal" << endl;
        cout << "1. Gestion Utilisateur" << endl;
        cout << "2. Gestion Paiement" << endl;
        cout << "3. Gestion Service" << endl;
        cout << "4. Gestion Factures" << endl;
        cout << "0. Quitter" << endl;
        cout << "Choix : ";
        cin >> choix;

        switch (choix) {
            case 1:
                 // Appel de la fonction de gestion des utilisateurs
                  gestionUtilisateur(utilisateurs);
                break;
            case 2:
                 // Appel de la fonction de gestion des paiements
                  gestionPaiement(paiements);
                break;
            case 3:
                 // Appel de la fonction de gestion des services
                  gestionService(services);
                break;
            case 4:
                 // Appeler la fonction de gestion des factures
                  gestionFactures(services, paiements);
                break;
            case 0:
                cout << "Programme terminé." << endl;
                break;
            default:
                cout << "Choix invalide. Veuillez réessayer." << endl;
        }
    } while (choix != 0);

    // Nettoyage de la mémoire pour les paiements
    for (auto& paiement : paiements) {
        delete paiement;
    }

    return 0;
}
