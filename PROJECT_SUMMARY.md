# Plantamitz 2025 - Résumé du projet

## ✅ Statut: Projet complet et fonctionnel

### Structure générée

```
plantamitz/
├── src/
│   ├── main.c              (Point d'entrée, boucle principale)
│   ├── platform.h/c        (Abstraction Windows/ANSI: curseur, couleurs, input)
│   ├── board.h/c           (Plateau 25×45, génération stable, gravité, refill)
│   ├── match.h/c           (Détection lignes 3/4/6+, formes H, rectangles)
│   ├── input.h/c           (Curseur, sélection, permutation ZQSD+ESPACE)
│   ├── contracts.h/c       (3 niveaux de difficulté croissante)
│   ├── save.h/c            (Sauvegarde/chargement progression joueur)
│   ├── game.h/c            (Logique de jeu, état, timer, vies)
│   └── utils.h/c           (Utilitaires: clear screen, input nom)
├── tests/
│   ├── test_board.c        (Tests génération stable, swap)
│   ├── test_match.c        (Tests détection matchs)
│   └── test_gravity.c      (Tests gravité et refill)
├── Makefile                (Compilation multi-plateforme)
├── build.sh                (Script de build automatique)
├── .gitignore              (Fichiers à ignorer)
├── README.md               (Documentation utilisateur complète)
└── plantamitz.code-workspace (Configuration VSCode/Code::Blocks)
```

### Fonctionnalités implémentées

#### ✅ Plateau et génération
- Plateau 25 lignes × 45 colonnes
- 5 items: S (Soleil), F (Fraise), P (Pomme), O (Oignon), M (Mandarine)
- Génération stable intelligente (évite matches initiaux)
- Couleurs distinctes par item (jaune, rouge, vert, violet, bleu)

#### ✅ Mécaniques de jeu
- Déplacement curseur: Z/Q/S/D
- Sélection/permutation: ESPACE
- Détection automatique des matchs:
  - Lignes horizontales/verticales ≥3
  - Groupe de 4: bonus +4 points
  - Groupe de 6+: suppression globale du type
  - Forme H: 2× points
  - Rectangle: 2× points
- Gravité automatique (chute items)
- Refill automatique depuis le haut
- Cascades multiples jusqu'à stabilisation

#### ✅ Système de progression
- 3 niveaux de difficulté croissante
- Contrats avec objectifs par item
- Limite de coups et temps (compte à rebours)
- 5 vies (réinitialisées après succès/game over)
- Sauvegarde automatique de progression

#### ✅ Interface console
- UI claire: contrat, coups, temps, vies
- Curseur visible avec highlight
- Sélection en surbrillance cyan
- Contrôles affichés en bas
- Pas de clignotement (utilisation curseur)

#### ✅ Multi-plateforme
- Windows: API native (SetConsoleCursorPosition, couleurs)
- Linux/macOS: Séquences ANSI + fallback
- Détection automatique via `#ifdef _WIN32`

### Compilation et tests

```bash
# Compilation
make                  # Compile le jeu
make tests           # Compile et exécute les tests unitaires
make clean           # Nettoie les fichiers de build
./build.sh           # Script de build avec feedback

# Exécution
./plantamitz         # Lance le jeu (Linux/macOS)
plantamitz.exe       # Lance le jeu (Windows)
```

### Tests unitaires
Tous les tests passent ✅:
- `test_board`: Génération stable, swap
- `test_match`: Détection lignes 3/4, verticales, contrat
- `test_gravity`: Gravité, refill

### Qualité du code

#### ✅ Conformité spécifications
- Code modulaire (9 modules séparés)
- Headers propres avec documentation Doxygen-like
- Commentaires sur tous les prototypes (IN/OUT params)
- Séparation logique/affichage (testabilité)
- Pas de magic numbers (constantes nommées)
- Pas d'allocation anarchique

#### ✅ Compilation
- Compilation clean avec `-Wall -Wextra`
- Compatible C (sans mode strict C99 pour portabilité)
- Aucun warning (sauf unused-variable résolu)

#### ✅ Lisibilité
- snake_case cohérent
- Fonctions < 80 lignes
- Structure claire et documentée

### Niveaux disponibles

1. **Niveau 1** (Facile)
   - Objectif: 20F, 50O, 20M
   - 30 coups, 120 secondes

2. **Niveau 2** (Moyen)
   - Objectif: 55S, 35P, 30F, 45O
   - 40 coups, 150 secondes

3. **Niveau 3** (Difficile)
   - Objectif: 70S, 60F, 50P, 60O, 40M
   - 50 coups, 180 secondes

### Fichiers de données
- `save.dat`: Sauvegarde binaire (nom joueur + niveau suivant)

### Notes techniques

#### Algorithme de génération stable
Au lieu de générer aléatoirement et vérifier (trop lent), le code génère cellule par cellule en excluant les items qui créeraient des matchs immédiats. Efficacité garantie en O(n).

#### Détection de matchs
Priorisée: H > Rectangle > Ligne6 > Ligne4 > Ligne3.
Chaque type a son scoring spécial selon les règles du jeu.

#### Gravité et cascades
Après chaque permutation valide, boucle jusqu'à stabilisation:
1. Détecter matchs
2. Supprimer items
3. Appliquer gravité
4. Refill
5. Répéter si nouveaux matchs

### Améliorations futures possibles
- Taille plateau paramétrable
- Item "bombe" avec effets spéciaux
- Musique/sons activables
- Menu options
- Plus de niveaux
- Système de scoring global
- Hints (indices) pour coups possibles
- Animations ASCII pour les matchs spéciaux

### Crédits
Projet Plantamitz 2025 - Jeu console Match-3 en C
Développé selon cahier des charges complet avec architecture modulaire.

---
**Statut final**: ✅ Tous les deliverables générés et fonctionnels
