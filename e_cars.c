#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VOITURES_PARC_FILE "parc_auto.txt"
#define LOCATIONS_FILE "historique_locations.txt"
#define BLACKLIST_FILE "blacklist_clientstxt"
#define TARIFS_FILE "tarifs.txt"

int idLoc=1;
// Fonction pour lire une date depuis l'entrée
void lireDate(char date[]) {
    while (1) {
        if (scanf("%10s", date) == 1) {
            // Input is a valid date
            // Clear the input buffer
            while (getchar() != '\n');
            break;
        } else {
            // Input is not a valid date
            printf("Format de date invalide. Veuillez utiliser le format JJ/MM/AAAA.\n");
            // Clear the input buffer
            while (getchar() != '\n');
        }
    }
}
struct voiture {
  char modele[20];
  char matricule[20];
  char assurance[50];
  int kilometrage;
  char etat[20];
  int annee;
  float caution;
  float tarif_journalier;
  struct voiture* suivante;

};

struct location {
    struct voiture* voiture;
    int id_loc;
    char date_debut[20];
    char date_fin[20];
    char cin_client[20];
    int duree;
    double montant;
    int paiement_effectue;
    double acompte;
    struct location* suivante;
};
struct Blacklist {
    char cin_client[20];
    char raison[255];
    struct Blacklist* suivant;
};

// Déclaration de la liste chaînée pour les voitures
struct voiture* parcAuto = NULL;
// Déclaration de la liste chaînée pour l'historique des locations
struct location* historiqueLocations = NULL;
// Déclaration de la liste chaînée pour la blacklist des clients
struct Blacklist* blacklistClients = NULL;
struct CarRentalSystem {
    struct voiture* parcAuto;
    struct location* historiqueLocations;
    struct Blacklist* blacklistClients;
    int idLoc;
};
// Fonction pour créer une nouvelle voiture
struct voiture* creerVoiture(char matricule[], char modele[],char etat[],   char ass[], int km, int annee, float tarif_journalier, float caution) {
    struct voiture* nouvelleVoiture = (struct voiture*)malloc(sizeof(struct voiture));
    strcpy(nouvelleVoiture->modele, modele);
    strcpy(nouvelleVoiture->matricule, matricule);
    strcpy(nouvelleVoiture->etat, etat);
    strcpy(nouvelleVoiture->assurance, ass);
    nouvelleVoiture->kilometrage = km;
    nouvelleVoiture->annee = annee;
    nouvelleVoiture->tarif_journalier = tarif_journalier;
    nouvelleVoiture->caution = caution;
    nouvelleVoiture->suivante = NULL;
    return nouvelleVoiture;
}
struct location* creerLocation(struct voiture* voiture, char date_debut[],char date_fin[], char cin_client[], int duree, float montant,int paiement_effectue, double acompte) {
    struct location* nouvelleLocation = (struct location*)malloc(sizeof(struct location));
    nouvelleLocation->id_loc = idLoc++;
    nouvelleLocation->voiture = voiture;
    lireDate(date_debut);
    strcpy(nouvelleLocation->date_debut, date_debut);
    lireDate(date_fin);
    strcpy(nouvelleLocation->date_fin, date_fin);
    strcpy(nouvelleLocation->cin_client, cin_client);
    nouvelleLocation->duree = duree;
    nouvelleLocation->montant = montant;
    nouvelleLocation->paiement_effectue = paiement_effectue;
    nouvelleLocation->acompte = acompte;;
    nouvelleLocation->suivante = NULL;
    return nouvelleLocation;
}
// Fonction pour ajouter une voiture au parc
void ajouterVoitureAuParc(struct voiture* nouvelleVoiture) {
    nouvelleVoiture->suivante = parcAuto;
    parcAuto = nouvelleVoiture;

    printf("Voiture ajoutee avec succes au parc.\n");
}
void ajouterVoiture() {
    char matricule[20], modele[20], marque[20], etat[20]="disponible", assurance[50];
    int kilometrage, annee;
    float caution, tarif_journalier;
    printf("Entrez la matricule de la voiture : ");
    scanf("%s", matricule);
    printf("Entrez le modele de la voiture : ");
    scanf("%s", modele);
    printf("Entrez la marque de la voiture : ");
    scanf("%s", marque);
    printf("Entrez l'assurance de la voiture : ");
    scanf("%s", assurance);
    printf("Entrez le kilometrage de la voiture : ");
    scanf("%d", &kilometrage);
    printf("Entrez l'annee de la voiture : ");
    scanf("%d", &annee);
    printf("Entrez la caution de la voiture : ");
    scanf("%f", &caution);
    printf("Entrez le tarif journalier de la voiture : ");
    scanf("%f", &tarif_journalier);
    struct voiture* nouvelleVoiture = creerVoiture(matricule, modele, etat, assurance, kilometrage, annee, tarif_journalier, caution);
    ajouterVoitureAuParc(nouvelleVoiture);
};
void supprimerVoiturePanne() {
    struct voiture* voitureActuelle = parcAuto;
    struct voiture* voiturePrecedente = NULL;

    while (voitureActuelle != NULL) {
        if (strcmp(voitureActuelle->etat, "panne") == 0) {
            // La voiture est en panne, la supprimer du parc
            if (voiturePrecedente == NULL) {
                // La voiture en panne est la première dans la liste
                parcAuto = voitureActuelle->suivante;
                free(voitureActuelle);
                printf("Voiture en panne supprimee avec succes.\n");
                return;
            } else {
                voiturePrecedente->suivante = voitureActuelle->suivante;
                free(voitureActuelle);
                printf("Voiture en panne supprimee avec succes.\n");
                return;
            }
        }

        voiturePrecedente = voitureActuelle;
        voitureActuelle = voitureActuelle->suivante;
    }

    printf("Aucune voiture en panne trouvee dans le parc.\n");
};
void modifierDescriptionEtat() {
    char mat[10];
    printf("Entrez la matricule de la voiture a modifier : ");
    scanf("%s", mat);

    struct voiture* voitureActuelle = parcAuto;

    while (voitureActuelle != NULL) {
        if (strcmp(voitureActuelle->matricule, mat) == 0) {
            // La voiture est trouvée, modifier la description et l'état
            printf("Nouvelle description : ");
            scanf("%s", voitureActuelle->matricule);
            printf("Nouvel etat (disponible, louee, panne) : ");
            scanf("%s", voitureActuelle->etat);
            printf("Description et etat modifies avec succes.\n");
            return;
        }

        voitureActuelle = voitureActuelle->suivante;
    }

    printf("La voiture n'a pas ete trouvee dans le parc.\n");

};
int calculerDuree(char date_debut[], char date_fin[]) {
    int jours_debut, mois_debut, annee_debut;
    int jours_fin, mois_fin, annee_fin;

    // Extraire les jours, mois et années de la date de début
    sscanf(date_debut, "%d/%d/%d", &jours_debut, &mois_debut, &annee_debut);

    // Extraire les jours, mois et années de la date de fin
    sscanf(date_fin, "%d/%d/%d", &jours_fin, &mois_fin, &annee_fin);

    // Convertir les deux dates en jours depuis une référence commune (par exemple, 1 janvier 1)
    int jours_total_debut = jours_debut + mois_debut * 30 + annee_debut * 365;
    int jours_total_fin = jours_fin + mois_fin * 30 + annee_fin * 365;

    // Calculer la différence en jours
    int duree = jours_total_fin - jours_total_debut;

    return duree;
}
int estVoitureDisponible(struct voiture* voiture, char date_debut[], char date_fin[]) {
    struct location* locationActuelle = historiqueLocations;

    while (locationActuelle != NULL) {
        // Vérifier s'il y a un chevauchement de dates avec la location actuelle
        if (strcmp(locationActuelle->voiture->matricule, voiture->matricule) == 0) {
            if ((strcmp(locationActuelle->date_fin, date_debut) >= 0) || (strcmp(locationActuelle->date_debut, date_fin) <= 0)) {
                // La voiture est déjà louée pour une partie de la période spécifiée
                return 0; // Non disponible
            }
        }

        locationActuelle = locationActuelle->suivante;
    }

    return 1; // Disponible
}

// Fonction pour ajouter un client à la blacklist
void ajouterClientBlacklist(char cin_client[], char raison[]) {
    struct Blacklist* nouveauClientBlacklist = (struct Blacklist*)malloc(sizeof(struct Blacklist));
    strcpy(nouveauClientBlacklist->cin_client, cin_client);
    strcpy(nouveauClientBlacklist->raison, raison);
    nouveauClientBlacklist->suivant = NULL;

    // Ajouter le client blacklisté à la liste
    if (blacklistClients == NULL) {
        blacklistClients = nouveauClientBlacklist;
    } else {
        struct Blacklist* dernierClient = blacklistClients;
        while (dernierClient->suivant != NULL) {
            dernierClient = dernierClient->suivant;
        }
        dernierClient->suivant = nouveauClientBlacklist;
    }

    printf("Client ajoute a la blacklist avec succes.\n");
}

// Fonction pour vérifier si un client est dans la blacklist
int estClientBlackliste(char cin_client[]) {
    struct Blacklist* clientActuel = blacklistClients;
    while (clientActuel != NULL) {
        if (strcmp(clientActuel->cin_client, cin_client) == 0) {
            printf("Ce client est blacklisté pour la raison suivante : %s\n", clientActuel->raison);
            return 1; // Le client est blacklisté
        }
        clientActuel = clientActuel->suivant;
    }
    return 0; // Le client n'est pas blacklisté
}
void afficherBlackliste() {
    struct Blacklist* blacklistClientsActuelle = blacklistClients;

    while (blacklistClientsActuelle != NULL) {
        printf("CIN du client : %s\n", blacklistClientsActuelle->cin_client);
        printf("Raison : %s\n", blacklistClientsActuelle->raison);
        printf("---------------------------\n");

        blacklistClientsActuelle = blacklistClientsActuelle->suivant;
    }
}

// Fonction pour louer une voiture
void louerVoiture() {
    char mat[20];
    char datedeb[20];
    char datefin[20];
    char cin_client[20];
    int duree;
    double acompte;

    // Demander à l'utilisateur le modèle de la voiture à louer
    printf("Entrez La matricule de la voiture a louer : ");
    scanf("%s", mat);

    struct voiture* voitureActuelle = parcAuto;
    while (voitureActuelle != NULL) {
        if (strcmp(voitureActuelle->matricule,mat) == 0) {

            printf("Entrez le CIN du client : ");
            scanf("%s", cin_client);

            if (estClientBlackliste(cin_client)) {
                printf("Impossible de louer une voiture à un client blacklisté.\n");
                return;
            }

            printf("Entrez la date de début de la location (JJ/MM/AAAA) : ");
            scanf("%s", datedeb);
            printf("Entrez la date de fin de la location (JJ/MM/AAAA) : ");
            scanf("%s", datefin);//should I add a function to calculate date fin ??????????????
            if (estVoitureDisponible(voitureActuelle,datedeb,datefin)){
                    int duree=calculerDuree(datedeb,datefin);
            // Demander l'acompte à l'utilisateur
            printf("Entrez le montant de l'acompte : ");
            scanf("%lf", &acompte);

            // Calculer le montant total de la location
            double montant = (duree * voitureActuelle->tarif_journalier);

            // Vérifier si l'acompte est suffisant
            if (acompte <=montant / 3) {
                printf("L'acompte doit être au moins la moitié du montant total de la location.\n");
                return;
            }

            struct Location* nouvelleLocation = creerLocation(voitureActuelle, datedeb,datefin, cin_client, duree, montant,paiement_effectue, acompte);
            if (historiqueLocations == NULL) {
                historiqueLocations = nouvelleLocation;
            } else {
                struct location* derniereLocation = historiqueLocations;
                while (derniereLocation->suivante != NULL) {
                    derniereLocation = derniereLocation->suivante;
                }
                derniereLocation->suivante = nouvelleLocation;
            }

            // Mettre à jour l'état de la voiture (par exemple, "louée")
            strcpy(voitureActuelle->etat, "louee");

            printf("La voiture a ete louee avec succes.\n");
            return;
        }
        voitureActuelle = voitureActuelle->suivante;
    }
            }


    // Si la voiture n'est pas trouvée dans le parc
    printf("La voiture n'est pas disponible dans le parc.\n");
};
void retourVoitureReclamation() {
    char mat[10];
    printf("Entrez la matricule de la voiture a retourner suite a une reclamation : ");
    scanf("%s", mat);

    struct voiture* voitureActuelle = parcAuto;

    while (voitureActuelle != NULL) {
        if (strcmp(voitureActuelle->matricule, mat) == 0) {
            // La voiture est trouvée, mettre à jour son état
            strcpy(voitureActuelle->etat, "disponible");
            printf("La voiture a ete retournee avec succes suite a une reclamation.\n");
            return;
        }

        voitureActuelle = voitureActuelle->suivante;
    }

    printf("La voiture n'a pas ete trouvee dans le parc.\n");
};
void effectuerPaiement() {
    int id_location;
    printf("Entrez l'identifiant de la location : ");
    scanf("%d", &id_location);

    // Recherche de la location dans l'historique
    struct location* locationActuelle = historiqueLocations;

    while (locationActuelle != NULL) {
        if (locationActuelle->id_loc == id_location) {
            if (locationActuelle->paiement_effectue) {
                printf("Le paiement a deja ete effectue pour cette location.\n");
            } else {
                // Logique pour effectuer le paiement (par exemple, marquer la location comme payée)
                locationActuelle->paiement_effectue = 1;
                printf("Le paiement a ete effectue avec succes pour la location %d.\n", id_location);
            }
            return;
        }

        locationActuelle = locationActuelle->suivante;
    }

    printf("Aucune location trouvee avec l'identifiant %d dans l'historique.\n", id_location);
};
void afficher_tarifs() {
    char mat[20];
    printf("Donner La Matricule : ");
    scanf("%s",mat);
    struct voiture* voitureActuelle = parcAuto;

    while (voitureActuelle != NULL) {
        if (strcmp(voitureActuelle->matricule, mat) == 0) {
            // La voiture avec la matricule spécifiée a été trouvée
              printf("Caution : %.2f\n",voitureActuelle->caution);
              printf("Tarif journalier : %.2f\n", voitureActuelle->tarif_journalier);
            return;
        }

        voitureActuelle = voitureActuelle->suivante;
    }

    printf("La voiture avec la matricule %s n'a pas ete trouvee dans le parc.\n", mat);


};
void modifier_tarif() {
    char mat[20];
    float caut, tar;
    printf("Donner La Matricule : ");
    fgets(mat, sizeof(mat), stdin);
    mat[strcspn(mat, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    printf("Donner La Nouvelle Caution : ");
    scanf("%f", &caut);

    printf("Donner le Nouveau Tarif Journalier : ");
    scanf("%f", &tar);

    struct voiture* voitureActuelle = parcAuto;

    while (voitureActuelle != NULL) {
        if (strcmp(voitureActuelle->matricule, mat) == 0) {
            // La voiture avec la matricule spécifiée a été trouvée
            voitureActuelle->caution = caut;
            voitureActuelle->tarif_journalier = tar;
            return;
        }

        voitureActuelle = voitureActuelle->suivante;
    }

    // Si la matricule spécifiée n'est pas trouvée
    printf("La voiture avec la matricule %s n'a pas été trouvée dans le parc.\n", mat);
};
void afficherHistoriqueTousJours(struct location* listeLocations) {
    struct location* locationActuelle = listeLocations;
    while (locationActuelle != NULL) {
        printf("Historique des locations pour le jour %s :\n", locationActuelle->date_debut);
        printf("Identifiant : %d\n", locationActuelle->id_loc);
        printf("Date de début : %s\n", locationActuelle->date_debut);
        printf("Date de fin : %s\n", locationActuelle->date_fin);
        printf("CIN du client : %s\n", locationActuelle->cin_client);
        printf("Durée : %d jours\n", locationActuelle->duree);
        printf("Montant : %.2f\n", locationActuelle->montant);
        printf("Paiement effectué : %d\n", locationActuelle->paiement_effectue);
        printf("Acompte : %.2f\n", locationActuelle->acompte);
        printf("-----------------------------\n");
        locationActuelle = locationActuelle->suivante;
    }
};
void afficherHistoriqueTousMois(struct location* listeLocations) {
    for (int mois = 1; mois <= 12; mois++) {
        printf("Historique des locations pour le mois %d :\n", mois);
        struct location* locationActuelle = listeLocations;
        while (locationActuelle != NULL) {
            int moisLocation;
            sscanf(locationActuelle->date_debut, "%*d/%d/%*d", &moisLocation);
            if (moisLocation == mois) {
                printf("Identifiant : %d\n", locationActuelle->id_loc);
                printf("Date de début : %s\n", locationActuelle->date_debut);
                printf("Date de fin : %s\n", locationActuelle->date_fin);
                printf("CIN du client : %s\n", locationActuelle->cin_client);
                printf("Durée : %d jours\n", locationActuelle->duree);
                printf("Montant : %.2f\n", locationActuelle->montant);
                printf("Paiement effectué : %d\n", locationActuelle->paiement_effectue);
                printf("Acompte : %.2f\n", locationActuelle->acompte);
                printf("-----------------------------\n");
            }

            locationActuelle = locationActuelle->suivante;
        }

        printf("\n");
    }
};
// Fonction pour afficher la description des voitures disponibles
void afficherVoituresDisponibles() {
    struct voiture* voitureActuelle = parcAuto;

    while (voitureActuelle != NULL) {
        if (strcmp(voitureActuelle->etat, "disponible") == 0) {
            // Afficher les détails de la voiture disponible
            printf("Matricule : %s\n", voitureActuelle->matricule);
            printf("Modele : %s\n", voitureActuelle->modele);
            printf("Etat : %s\n", voitureActuelle->etat);
            printf("Assurance : %s\n", voitureActuelle->assurance);
            printf("Kilometrage : %d\n", voitureActuelle->kilometrage);
            printf("Annee : %d\n", voitureActuelle->annee);
            printf("Tarif journalier : %.2f\n", voitureActuelle->tarif_journalier);
            printf("Caution : %.2f\n", voitureActuelle->caution);
            printf("---------------------------\n");
        }

        voitureActuelle = voitureActuelle->suivante;
    }
}

// Fonction pour afficher les voitures en panne
void afficherVoituresEnPanne() {
    struct voiture* voitureActuelle = parcAuto;

    while (voitureActuelle != NULL) {
        if (strcmp(voitureActuelle->etat, "panne") == 0) {
            // Afficher les détails de la voiture en panne
            printf("Matricule : %s\n", voitureActuelle->matricule);
            printf("Modele : %s\n", voitureActuelle->modele);
            printf("Etat : %s\n", voitureActuelle->etat);
            printf("Assurance : %s\n", voitureActuelle->assurance);
            printf("Kilometrage : %d\n", voitureActuelle->kilometrage);
            printf("Annee : %d\n", voitureActuelle->annee);
            printf("Tarif journalier : %.2f\n", voitureActuelle->tarif_journalier);
            printf("Caution : %.2f\n", voitureActuelle->caution);
            printf("---------------------------\n");
        }

        voitureActuelle = voitureActuelle->suivante;
    }
}

// Fonction pour afficher les voitures disponibles d'un modèle spécifique
void afficherVoituresParModele(char modeleRecherche[]) {
    struct voiture* voitureActuelle = parcAuto;

    while (voitureActuelle != NULL) {
        if (strcmp(voitureActuelle->modele, modeleRecherche) == 0 && strcmp(voitureActuelle->etat, "disponible") == 0) {
            // Afficher les détails de la voiture disponible du modèle spécifié
            printf("Matricule : %s\n", voitureActuelle->matricule);
            printf("Modele : %s\n", voitureActuelle->modele);
            printf("Etat : %s\n", voitureActuelle->etat);
            printf("Assurance : %s\n", voitureActuelle->assurance);
            printf("Kilometrage : %d\n", voitureActuelle->kilometrage);
            printf("Annee : %d\n", voitureActuelle->annee);
            printf("Tarif journalier : %.2f\n", voitureActuelle->tarif_journalier);
            printf("Caution : %.2f\n", voitureActuelle->caution);
            printf("---------------------------\n");
        }

        voitureActuelle = voitureActuelle->suivante;
    }
}
// Fonction pour calculer le nombre de locations effectuées par une voiture spécifique
int nombreLocationsParVoiture(char matriculeRecherche[]) {
    int nombreLocations = 0;
    struct location* locationActuelle = historiqueLocations;

    while (locationActuelle != NULL) {
        if (strcmp(locationActuelle->voiture->matricule, matriculeRecherche) == 0) {
            // La location concerne la voiture spécifiée
            nombreLocations++;
        }

        locationActuelle = locationActuelle->suivante;
    }

    return nombreLocations;
}


void sauvegarderInformationsDansFichier() {
    char matricule[20];
char modele[50];
char etat[20];
char assurance[20];
int kilometrage;
int annee;
double tarif_journalier;
double caution;
char date_debut[20];
char date_fin[20];
char cin_client[20];
int duree;
double montant;
int paiement_effectue;
double acompte;
char raison[100];
    FILE* fichierParc = fopen("parc_auto.txt", "w");
    FILE* fichierLocations = fopen("historique_locations.txt", "w");
    FILE* fichierBlacklist = fopen("blacklist_clients.txt", "w");

    if (fichierParc == NULL || fichierLocations == NULL || fichierBlacklist == NULL) {
        perror("Erreur lors de l'ouverture des fichiers de sauvegarde");
        exit(EXIT_FAILURE);
    }

    struct voiture* voitureActuelle = parcAuto;
    while (voitureActuelle != NULL) {
        fprintf(fichierParc, "%s %s %s %s %d %d %.2f %.2f\n", voitureActuelle->matricule, voitureActuelle->modele,
            voitureActuelle->etat, voitureActuelle->assurance, voitureActuelle->kilometrage, voitureActuelle->annee,
            voitureActuelle->tarif_journalier, voitureActuelle->caution);
        voitureActuelle = voitureActuelle->suivante;
    }

    struct location* locationActuelle = historiqueLocations;
    while (locationActuelle != NULL) {
        fprintf(fichierLocations, "%d %s %s %s %d %.2f %d %.2f\n", locationActuelle->id_loc, locationActuelle->date_debut,
            locationActuelle->date_fin, locationActuelle->cin_client, locationActuelle->duree, locationActuelle->montant,
            locationActuelle->paiement_effectue, locationActuelle->acompte);
        locationActuelle = locationActuelle->suivante;
    }

    struct Blacklist* clientBlacklistActuel = blacklistClients;
    while (clientBlacklistActuel != NULL) {
        fprintf(fichierBlacklist, "%s %s\n", clientBlacklistActuel->cin_client, clientBlacklistActuel->raison);
        clientBlacklistActuel = clientBlacklistActuel->suivant;
    }

    fclose(fichierParc);
    fclose(fichierLocations);
    fclose(fichierBlacklist);
};
struct voiture* trouverVoitureParMatricule(char* matricule) {
    struct voiture* voitureActuelle = parcAuto;

    while (voitureActuelle != NULL) {
        if (strcmp(voitureActuelle->matricule, matricule) == 0) {
            return voitureActuelle;
        }
        voitureActuelle = voitureActuelle->suivante;
    }

    return NULL;
}


void chargerInformationsDepuisFichier() {
    FILE* fichierParc = fopen("parc_auto.txt", "r");
    FILE* fichierLocations = fopen("historique_locations.txt", "r");
    FILE* fichierBlacklist = fopen("blacklist_clients.txt", "r");

    if (fichierParc == NULL || fichierLocations == NULL || fichierBlacklist == NULL) {
        perror("Erreur lors de l'ouverture des fichiers de chargement");
        exit(EXIT_FAILURE);
    }

    while (fscanf(fichierParc, "%s %s %s %s %d %d %lf %lf", matricule, modele, etat, assurance, &kilometrage, &annee, &tarif_journalier, &caution) != EOF) {
        struct voiture* nouvelleVoiture = creerVoiture(matricule, modele, etat, assurance, kilometrage, annee, tarif_journalier, caution);
        ajouterVoitureAuParc(nouvelleVoiture);
    }

    while (fscanf(fichierLocations, "%d %s %s %s %d %lf %d %lf", &idLoc, date_debut, date_fin, cin_client, &duree, &montant, &paiement_effectue, &acompte) != EOF) {
        struct voiture* voitureLocation = trouverVoitureParMatricule(matricule);
        struct location* nouvelleLocation = creerLocation(voitureLocation, date_debut, date_fin, cin_client, duree, montant, paiement_effectue, acompte);
        struct location* derniereLocation = historiqueLocations;
                while (derniereLocation->suivante != NULL) {
                    derniereLocation = derniereLocation->suivante;
                }
                derniereLocation->suivante = nouvelleLocation;
    }

    while (fscanf(fichierBlacklist, "%s %s", cin_client, raison) != EOF) {
        ajouterClientBlacklist(cin_client, raison);
    }

    fclose(fichierParc);
    fclose(fichierLocations);
    fclose(fichierBlacklist);
};
void afficherMenu() {
    printf("____Menu____\n");
    printf("1. Louer une voiture\n");
    printf("2. Afficher la description du parc\n");
    printf("3. Ajouter une Voiture\n");
    printf("4. Supprimer une voiture en panne\n");
    printf("5. Modifier la description ou l'etat d'une voiture\n");
    printf("6. Afficher l'historique des locations Jour par Jour\n");
    printf("7. Afficher l'historique des locations mois par mois\n");
    printf("8. Retourner une voiture suite à une reclamation\n");
    printf("9. Effectuer un paiement\n");
    printf("10. Afficher Tarifs\n");
    printf("11. Modifier Tarifs\n");
    printf("12. Ajouter un client a la blackliste\n");
    printf("13. Afficher La Blackliste\n");
    printf("14. Afficher les Voitures Disponibles\n");
    printf("15. Afficher les Voitures en Panne\n");
    printf("16. Recherche des voitures Par modele\n");
    printf("17. Le nombre de locations effectuees par une voiture specifique\n");
    printf("0. Quitter\n");
};
void afficherdescription(char *matricule) {

    struct voiture* voit = parcAuto;

    voit = trouverVoitureParMatricule(matricule);

    if (voit != NULL) {
        printf("Description de la voiture avec le numéro de matricule %s:\n", voit->matricule);
        printf("- Modèle: %s\n", voit->modele);
        printf("- Kilomètres parcourus: %.2f\n", voit->kilometrage);
        printf("- Assurance: %s\n", voit->assurance);
        printf("- État: %s\n", voit->etat);
        printf("- Année: %d\n", voit->annee);
        printf("- Caution: %.2f\n", voit->caution);
        printf("- Tarif journalier: %.2f\n", voit->tarif_journalier);
    } else {
        printf("Aucune voiture trouvée avec le numéro de matricule %s.\n", matricule);
    }
}
void traiter_choix(int choix){


        switch (choix) {
            case 1:
                louerVoiture();
                break;
            case 2:
                printf("Donner la matricule de votre Voiture : ");
                scanf("%s",matricule);
                afficherdescription(matricule);
                break;
            case 3:
                ajouterVoiture();
                break;
            case 4:
                supprimerVoiturePanne();
                break;
            case 5:
                modifierDescriptionEtat();
                break;
            case 6:
                afficherHistoriqueTousJours(historiqueLocations);
                break;
            case 7:
                afficherHistoriqueTousMois(historiqueLocations);
            case 8:
                retourVoitureReclamation();
                break;
            case 9:
                effectuerPaiement();
                break;
            case 10:
                afficher_tarifs();
                break;
            case 11:
                modifier_tarif();
                break;
            case 12:
                {char id;
                char ch[20];
                printf("Donner le numéro de CIN du client : \n");
                scanf("%lf",&id);
                printf("Raison (<=255 mots) : \n");
                scanf("%s",ch);
                ajouterClientBlacklist(id,ch);
                break;}
            case 13:
                afficherBlackliste();
                break;
            case 14:
                afficherVoituresDisponibles();
                break;
            case 15:
                afficherVoituresEnPanne();
                break;
            case 16:
                {char modeleRecherche[20];
                printf("Entrez le modèle de voiture à rechercher : ");
                scanf("%s", modeleRecherche);
                afficherVoituresParModele(modeleRecherche);
                break;}
            case 17:
                {char matriculeRecherche[20];
                printf("Entrez le matricule de voiture à rechercher : ");
                scanf("%s", matriculeRecherche);
                int nombre = nombreLocationsParVoiture(matriculeRecherche);
                printf("Nombre de locations pour la voiture %s : %d\n", matriculeRecherche, nombre);
                break;}



        }

}
int main(){
    struct CarRentalSystem system = { NULL, NULL, NULL, 1 };

    int choix;
    chargerInformationsDepuisFichier();
    do {
        afficherMenu();
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        traiter_choix(choix);

    } while (choix != 0);


    sauvegarderInformationsDansFichier();
    return 0;
}





