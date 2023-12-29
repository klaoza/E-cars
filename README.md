#E-cars
# Système de Location de Voitures

Il s'agit d'un système simple de location de voitures implémenté en langage C. Le système permet aux utilisateurs de gérer une flotte de voitures, d'effectuer des opérations de location, de suivre l'historique des locations et de gérer les clients placés sur liste noire.

## Fonctionnalités

- **Louer une Voiture :** Les utilisateurs peuvent louer une voiture en fournissant les détails de la voiture, les informations du client et la période de location.

- **Gérer la Flotte de Voitures :** Ajouter de nouvelles voitures à la flotte, retirer les voitures nécessitant des réparations et modifier la description ou l'état d'une voiture.

- **Historique des Locations :** Afficher l'historique des locations quotidiennes ou mensuelles, y compris des détails tels que la durée de la location, l'état du paiement et la caution.

- **Clients sur Liste Noire :** Ajouter des clients à une liste noire avec une raison, les empêchant de louer des voitures.

- **Informations Tarifaires :** Afficher et modifier les informations tarifaires pour chaque voiture.

## Démarrage

Suivez ces instructions pour obtenir une copie du projet et le faire fonctionner sur votre machine locale.

### Prérequis

- [GCC](https://gcc.gnu.org/) (GNU Compiler Collection) installé

### Exécution du Programme

1. Clonez le dépôt :

   ```bash
   git clone https://github.com/klaoza/E-cars
   ```

2. Accédez au répertoire du projet :

   ```bash
   cd utilitaire-location-voitures
   ```

3. Compilez le programme :

   ```bash
   gcc car_rental_system.c -o car_rental_system
   ```

4. Exécutez le programme :

   ```bash
   ./car_rental_system
   ```

## Structure des Fichiers

- `E-cars.c` : Le fichier source principal contenant le code du système de location de voitures.
- `parc_auto.txt` : Fichier contenant les informations sur la flotte de voitures.
- `tarifs.txt` : Fichier contenant les tarifs de Location.
- `historique_locations.txt` : Fichier contenant l'historique des locations.
- `blacklist_clients.txt` : Fichier contenant la liste noire des clients avec les raisons associées.

## Utilisation

1. Choisissez une option dans le menu affiché.
2. Suivez les invites pour effectuer diverses opérations.

