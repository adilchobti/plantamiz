# Plantamitz 2025 - Démarrage rapide

## Compilation

### Linux/macOS
```bash
make
```

### Windows (MinGW)
```bash
mingw32-make
```

Ou utilisez Code::Blocks avec le fichier `plantamitz.code-workspace`.

## Exécution

### Linux/macOS
```bash
./plantamitz
```

### Windows
```bash
plantamitz.exe
```

## Tests unitaires
```bash
make tests
```

## Contrôles du jeu

- **Z** : Déplacer curseur vers le haut
- **Q** : Déplacer curseur vers la gauche
- **S** : Déplacer curseur vers le bas
- **D** : Déplacer curseur vers la droite
- **ESPACE** : Sélectionner/Permuter une case
- **ESC** : Quitter

## Règles rapides

1. Déplacez le curseur sur une case
2. Appuyez sur ESPACE pour la sélectionner (fond cyan)
3. Déplacez le curseur sur une case adjacente
4. Appuyez sur ESPACE ou utilisez ZQSD pour permuter

Les items identiques alignés par 3+ sont automatiquement retirés.

### Matchs spéciaux
- **4 alignés** : +4 points bonus
- **6+ alignés** : Supprime tous les items de ce type
- **Forme H** : Double les points
- **Rectangle** : Double les points

## Objectif

Remplir le contrat (quantités d'items demandées) avant la fin :
- Du temps imparti (compte à rebours)
- Des coups disponibles

## Système de vies

- 5 vies au départ
- Perte d'1 vie par échec
- Réinitialisation à 5 vies après un succès ou game over

## Sauvegarde

Votre progression est automatiquement sauvegardée dans `save.dat`.
Au prochain lancement, entrez le même nom pour continuer.

## Nettoyage

```bash
make clean
```

Supprime tous les fichiers de build.

---

**Astuce** : Les items tombent par gravité après chaque match, créant des cascades automatiques !
