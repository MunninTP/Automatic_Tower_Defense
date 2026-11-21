# 🏰 An Automatic Tower Defense Written in C

## 📌 Présentation du projet

**Tower Defense automatisé** est un jeu de type Tower Defense développé en langage C à l'aide de la bibliothèque graphique SDL.

Le principe du jeu repose sur un système de placement automatique des tours de défense. Contrairement à un Tower Defense classique dans lequel le joueur choisit lui-même où placer ses tours, un algorithme analyse le chemin emprunté par les ennemis afin de déterminer les meilleurs emplacements pour construire les défenses.

Des ennemis apparaissent aléatoirement au début du chemin qui est lui aussi créer aléatoirement et progressent en direction de la tour du Roi. Le but est de les empêcher d'atteindre leur destination grâce au placement stratégique et automatique des tours.

Le jeu introduit progressivement de nouvelles vagues d'ennemis à intervalles réguliers.

## 🎯 Objectif du jeu

L'objectif principal est de défendre la tour du Roi contre les vagues successives d'ennemis.

Pour cela, le programme doit :

- Analyser le chemin emprunté par les ennemis.
- Déterminer les emplacements les plus intéressants pour installer les tours.
- Placer automatiquement les tours selon un algorithme de recherche du meilleur emplacement.
- Permettre aux tours de défendre le chemin contre les ennemis.
- Gérer l'apparition des ennemis et leur progression sur le parcours.
- Résister aux différentes vagues d'ennemis.

## ⚙️ Fonctionnement du jeu

### 1. Apparition des ennemis

Les ennemis apparaissent aléatoirement au début du chemin.

Chaque ennemi suit le parcours prédéfini jusqu'à la tour du Roi.

### 2. Déplacement des ennemis

Les ennemis avancent progressivement sur le chemin en direction de leur objectif et au fur et à mesure que le temps passe, ils deviennent plus forts.

Leur progression est gérée automatiquement par le programme.

### 3. Placement automatique des tours

Le système de défense repose sur un algorithme capable de rechercher les meilleurs emplacements pour placer les tours.

L'algorithme analyse notamment le chemin afin d'identifier les positions permettant de maximiser l'efficacité des défenses.

### 4. Gestion des vagues

Les ennemis apparaissent par vagues successives.

Chaque nouvelle vague est déclenchée à intervalles de temps réguliers, ce qui permet de maintenir une progression continue de la difficulté.

### 5. Défense de la tour du Roi

Les tours ont pour objectif d'éliminer les ennemis avant qu'ils n'atteignent la tour du Roi.

Si les ennemis parviennent à atteindre leur destination, la défense est compromise.

## 🛠️ Technologies utilisées

| Technologie      | Utilisation                                                 |
| ---------------- | ----------------------------------------------------------- |
| **Langage C**    | Développement de la logique et des mécanismes du jeu        |
| **SDL**          | Gestion de l'affichage graphique et des éléments visuels    |
| **Code::Blocks** | IDE utilisé pour développer, compiler et exécuter le projet |

## 💻 Environnement de développement

- **IDE :** Code::Blocks
- **Langage :** C
- **Bibliothèque graphique :** SDL

⚠️ **Important :** Ce projet est conçu pour fonctionner avec Code::Blocks. L'utilisation de cet IDE est nécessaire pour ouvrir, compiler et exécuter correctement le projet dans son environnement prévu.

## 🚀 Installation et lancement

Pour lancer le projet :

1. Télécharger ou cloner le dépôt.
2. Installer Code::Blocks.
3. Vérifier que la bibliothèque SDL est correctement installée et configurée.
4. Ouvrir le fichier du projet Code::Blocks (`.cbp`).
5. Compiler le projet.
6. Exécuter le programme depuis Code::Blocks.

## 🧠 Objectifs techniques

Ce projet permet de mettre en pratique plusieurs notions de programmation :

- Programmation en langage C.
- Utilisation d'une bibliothèque graphique avec SDL.
- Gestion des déplacements et des positions des entités.
- Génération aléatoire d'ennemis.
- Gestion du temps et des vagues successives.
- Conception d'un algorithme de recherche du meilleur emplacement.
- Organisation et structuration d'un projet informatique.

## 👨‍💻 Auteur

Projet réalisé dans le cadre d'un projet de développement informatique pour l'université de Poitiers.

Auteurs : Stefanel Munteanu et Maxime Mimault

---

**An Automatic Tower Defense Written in C**
*Un système de défense automatisé où l'algorithme prend les décisions stratégiques à votre place.* 🏰

