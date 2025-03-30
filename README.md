# cub3d_correction

## 🎮 Description

`cub3d_correction` est un mini-moteur de rendu 3D basé sur le principe du raycasting, développé dans le cadre du projet [Cub3D](https://github.com/42Paris/42cursus) à l'école 42.  
Il s'agit d'une simulation de type "Wolfenstein 3D", permettant au joueur de naviguer dans un environnement en 3D à partir d'une carte `.cub`.

Ce projet permet d'appliquer des concepts comme :
- La manipulation graphique via MiniLibX
- Le parsing de fichiers personnalisés
- Le raycasting pour générer une vue pseudo-3D à partir d'une carte 2D

---

## 🔧 Installation

### Prérequis
- `make`
- `gcc`
- MiniLibX (déjà inclus dans le projet en général)
- Système Linux (ou macOS avec adaptation)

---

## 🚀 Utilisation

Compiler le programme avec :

```bash
make
```

Lancer le jeu avec une carte .cub :

./cub3d exec/map.cub

    ⚠️ Assurez-vous que la carte est bien formée et respecte les règles du sujet Cub3D.

---

## 🗺️ Format de la carte .cub

Une carte .cub contient :

    Les textures (Nord, Sud, Est, Ouest)

    Les couleurs du sol et du plafond

    La carte en ASCII avec des 1 pour les murs, des 0 pour les zones libres, et une lettre (N, S, E, W) pour la position et direction initiale du joueur.

---

## 🎯 Objectifs techniques

    Implémentation d'un moteur de raycasting

    Détection de collision et mouvements fluides

    Lecture et validation d’un fichier .cub

    Rendu temps réel avec MiniLibX

---

## 📁 Structure typique
``` bash
cub3d_correction/
├── exec/              # Cartes .cub, fichiers source
├── Libft/             # Fonctions de base
├── includes/          # Fichiers d'en-tête
├── minilib/               # MiniLibX
├── parsing/           
├── Makefile
└── README.md
```

👨‍💻 Auteurs

Projet réalisé dans le cadre du cursus 42 par :

    👤 @Dadou1910
    👤 @fwong

📄 Licence

Projet pédagogique de l'école 42.
Toute reproduction ou diffusion doit respecter les règles de l’école.

