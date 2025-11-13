# Plantamitz 2025

Un jeu console Match-3 inspiré de FarmHeroes/CandyCrush, écrit en C99.

## Description

Plantamitz est un jeu de type match-3 où vous devez remplir des contrats en collectant des items spécifiques (Soleil, Fraise, Pomme, Oignon, Mandarine) dans un nombre limité de coups et de temps. Le jeu propose plusieurs niveaux de difficulté croissante avec un système de vies et de sauvegarde de progression.

## Règles du jeu

### Plateau
- Grille de 25 lignes × 45 colonnes
- 5 types d'items : S (Soleil), F (Fraise), P (Pomme), O (Oignon), M (Mandarine)

### Contrôles
- **Z/Q/S/D** : Déplacer le curseur
- **ESPACE** : Sélectionner une case, puis déplacer pour échanger avec une case adjacente
- **ESC** : Quitter

### Objectif
Remplir le contrat en collectant les quantités demandées de chaque item avant la fin du temps ou des coups disponibles.

### Règles de scoring spéciales
- **Groupe de 4** : +4 points bonus au contrat
- **Groupe de 6+** : Supprime tous les items de ce type sur le plateau
- **Forme H** : 2× points (nombre d'items dans le H)
- **Rectangle** : 2× points (largeur × hauteur)

### Système de vies
- 5 vies au départ
- Perte d'une vie en cas d'échec d'un niveau
- Réinitialisation des vies à 5 après avoir terminé un niveau ou à 0 vies

## Compilation

### Windows (MinGW)
```bash
make
```

### Linux/macOS
```bash
make
```

Le jeu utilisera les fonctionnalités Windows natives sous Windows et un fallback ANSI sous Linux/macOS.

## Exécution

```bash
./plantamitz        # Linux/macOS
plantamitz.exe      # Windows
```

## Tests

Pour compiler et exécuter les tests unitaires :

```bash
make tests
```

Les tests vérifient :
- Génération de plateau stable (sans matchs initiaux)
- Détection de matchs (lignes de 3, 4, 6+, formes H, rectangles)
- Gravité et remplissage

## Structure du code

```
/src
  main.c          - Point d'entrée principal
  game.h/c        - Logique de jeu et état
  board.h/c       - Représentation et manipulation du plateau
  match.h/c       - Détection et résolution des matchs
  input.h/c       - Gestion des entrées (curseur, sélection)
  contracts.h/c   - Définitions des niveaux
  save.h/c        - Sauvegarde/chargement de progression
  utils.h/c       - Utilitaires divers
  platform.h/c    - Abstraction plateforme (curseur, couleurs, timing)
/tests
  test_board.c    - Tests du plateau
  test_match.c    - Tests de détection de matchs
  test_gravity.c  - Tests de gravité et remplissage
```

## Sauvegarde

La progression est sauvegardée automatiquement dans le fichier `save.dat` lorsque vous terminez un niveau. Le jeu charge automatiquement votre progression au démarrage en fonction de votre nom.

## Portabilité

- **Windows** : Utilise l'API Windows native pour le curseur et les couleurs
- **Linux/macOS** : Utilise des séquences ANSI (fonctionnalités limitées)

## Configuration requise

- Compilateur C99 (GCC, MinGW, Clang)
- Terminal avec support ANSI ou console Windows
- Windows : MinGW ou Code::Blocks recommandé

## Niveaux

Le jeu propose actuellement 3 niveaux avec difficulté croissante :

1. **Niveau 1** : 20F, 50O, 20M en 30 coups et 120 secondes
2. **Niveau 2** : 55S, 35P, 30F, 45O en 40 coups et 150 secondes
3. **Niveau 3** : 70S, 60F, 50P, 60O, 40M en 50 coups et 180 secondes

## Améliorations futures

- Taille de plateau paramétrable
- Nouvel item "bombe" avec effets spéciaux
- Musique et effets sonores activables/désactivables
- Menu d'options
- Plus de niveaux
- Système de score global

## Crédits

Développé comme démonstration d'un jeu console en C avec architecture modulaire.

## Licence

Code fourni à titre éducatif et de démonstration.
