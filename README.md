# ft_pipex

![alt tag](https://github.com/thomaue/ft_pipex/blob/main/errorcmd.png)


## Description

Ce projet implémente un programme appelé `pipex` qui simule le comportement de la commande shell `< file1 cmd1 | cmd2 > file2`. Il prend quatre arguments : `file1`, `cmd1`, `cmd2`, et `file2`, où `file1` et `file2` sont des noms de fichiers, et `cmd1` et `cmd2` sont des commandes shell avec leurs paramètres respectifs.

Le programme doit être exécuté comme suit :
```
./pipex file1 cmd1 cmd2 file2
```

## Exemples

### Exemple 1
```
$> ./pipex infile "ls -l" "wc -l" outfile
```
Devrait être identique à `< infile ls -l | wc -l > outfile`.

### Exemple 2
```
$> ./pipex infile "grep a1" "wc -w" outfile
```
Devrait être identique à `< infile grep a1 | wc -w > outfile`.

![alt tag](https://github.com/thomaue/ft_pipex/blob/main/basic.png)

## Fonctionnalités

- Gestion des entrées/sorties avec les fichiers et les tubes.
- Exécution des commandes shell spécifiées avec leurs paramètres.
- Gestion des erreurs avec du bon sens pour éviter les interruptions inattendues.
- Pas de fuites de mémoire.
- Gestion de plusieurs pipes pour des points supplémentaires.

## Fonctions Principales

### `pipex`

La fonction principale qui dirige le flux du programme en vérifiant les erreurs, en déterminant s'il faut exécuter la commande de sauvetage et en appelant les fonctions appropriées.

### `choose_proccess`

Choisit le processus enfant ou parent à exécuter en fonction du PID retourné par la fonction `fork`.

### `forker`

Crée un nouveau processus enfant pour exécuter une commande.

### `bonus`

Implémente la fonctionnalité bonus de gestion de plusieurs pipes.

## Bonus

- Gestion de plusieurs pipes.
- Validation du projet à 115%.

## Compilation

Le projet est compilé à l'aide d'un Makefile qui compile les fichiers sources sans relink.

Le projet peut être compilé en utilisant les règles du Makefile suivantes :

### Règles de Compilation

- `make` ou `make all`: Compile le projet principal.
- `make bonus`: Compile le projet avec les fonctionnalités bonus.
- `make clean`: Supprime les fichiers objets et les dossiers de compilation.
- `make fclean`: Supprime les fichiers objets, les dossiers de compilation et l'exécutable.
- `make re`: Effectue une remise à zéro complète du projet en supprimant tous les fichiers générés et en recompilant tout depuis le début.

## Prérequis

- Gestion des erreurs sans interruption inattendue.
- Pas de fuites de mémoire.

## Remarques

Le programme a été validé avec succès à 115%. ✅

---




