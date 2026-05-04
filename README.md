# minishell_CYBERPUNK_themed
Mini-shell interactif theme CYBERPUNK2077 en C, capable d'exécuter des commandes Unix avec support commandes internes, des redirections, pipes multiples et historique des commandes.

##  Prérequis Techniques

- **Bibliothèque GNU Readline**  
  Essentielle pour l’historique des commandes et la navigation fluide avec les flèches.
Installez-la sur Ubuntu/Debian avec :

  ```bash
  sudo apt update
  sudo apt install libreadline-dev
  ```

- **Compilateur GCC**  
  Pour compiler le code source C et le transformer en un exécutable fonctionnel. Assurez-vous que GCC est installé :

```bash
  gcc --version
  ```

---

# Fonctionnalités Clés

## Prompt Cyberpunk
Un prompt néon dynamique qui affiche votre répertoire actuel.  
## Exécution de Commandes
- Prend en charge toutes les commandes Unix standard via `execvp()`.
- Compatible avec des processus en arrière-plan grâce à l'opérateur `&`.

## Redirections et Pipes

### Redirections :
- **Entrée (`<`)** : Lire depuis un fichier.
- **Sortie (`>`)** : Écrire dans un fichier.
- **Ajout (`>>`)** : Ajouter du contenu à un fichier existant.

### Pipes :
- **(`|`)** : Chaînez plusieurs commandes pour créer des workflows puissants.

## Commandes Internes
Un ensemble de commandes intégrées pour simplifier votre expérience :

| Commande     | Description                                   |
|--------------|-----------------------------------------------|
| `cd`         | Changer de répertoire.                        |
| `pwd`        | Afficher le répertoire courant.               |
| `clear`      | Effacez l’écran pour un terminal propre.      |
| `exit`       | Quitter le shellavec une animation de sortie. |
| `help`       | Afficher les commandes internes disponibles   |
| `history`    | Consultez vos commandes précédentes.          |

---

##  Compilation et exécution

### Compiler le Projet :

```bash
gcc main.c parsing.c utils.c builtins.c commandexe.c -o cybershell -lreadline
```

### Lancer CyberShell :

```bash
./cybershell
```


---

##  Exemples d'utilisation

```bash
# Liste tous les fichiers dans le répertoire courant
ls -l

# Utilisez un pipe pour filtrer les fichiers .c
ls | grep ".c"

# Redirigez la sortie d'une commande vers un fichier
echo "Hack the Planet" > message.txt

# Lisez le contenu d'un fichier en entrée
cat < message.txt

# Lancez un processus en arrière-plan
sleep 10 &
```
 Les flèches ↑ ↓ pour parcourir l’historique  
 Combinez les redirections et les pipes efficacement (`cat input.txt | grep "important" > filtered_output.txt`)

---

##  Structure du Projet

```
cybershell/
├── main.c         # Boucle principale et gestion des animations
├── parsing.c      # Analyse syntaxique des commandes utilisateur
├── utils.c        # Fonctions utilitaires (gestion des erreurs, etc.)
├── builtins.c     # Implémentation des commandes internes
├── commandexe.c   # Exécution des commandes externes et pipelines
├── cyber.h        # Fichier d’en-tête contenant les macros et prototypes
├── Makefile       # Script de compilation automatisé
├── .gitignore     # Ignorer les fichiers temporaires et binaires
└── README.md      # Documentation du projet
```

---
