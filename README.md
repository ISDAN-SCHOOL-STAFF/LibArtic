# LibArtic

LibArtic est une bibliothèque graphique en C/C++ qui facilite la création d'applications graphiques en utilisant SFML. Elle fournit une interface en C pour interagir avec les fonctionnalités graphiques implémentées en C++.

## Caractéristiques

- **Création de fenêtres graphiques** : Ouvrez facilement des fenêtres pour vos applications.
- **Gestion des événements clavier** : Gérez les entrées utilisateur via le clavier.
- **Manipulation de tableaux de pixels** : Manipulez directement les pixels pour un contrôle précis du rendu.
- **Boucle principale personnalisable** : Contrôlez le flux de votre application avec des fonctions de boucle personnalisées.
- **Intégration avec SFML** : Profitez des performances et de la simplicité de SFML pour le rendu graphique.

## Prérequis

- **SFML** : La bibliothèque SFML doit être installée sur votre système.
  - Pour Ubuntu/Debian :
    ```sh
    sudo apt-get install libsfml-dev
    ```
  - Pour d'autres systèmes, veuillez consulter le site officiel de SFML : [https://www.sfml-dev.org/](https://www.sfml-dev.org/)

- **Compilateur C/C++** : Assurez-vous que GCC et G++ sont installés.
  - Pour Ubuntu/Debian :
    ```sh
    sudo apt-get install build-essential
    ```

## Installation de LibArtic

### 1. Cloner le dépôt

```sh
git clone https://votre-repo-git/LibArtic.git
cd LibArtic
```

### 2. Compiler la bibliothèque

```sh
make clean
make
```

### 3. Installer la bibliothèque

```sh
sudo make install
```

- La bibliothèque statique libartic.a sera installée dans /usr/local/lib.
- Les fichiers d'en-tête seront installés dans /usr/local/include/artic.


## Utilisation de LibArtic
Vous pouvez désormais lier `libartic` dans vos projets et inclure les en-têtes nécessaires.

## Exemple : Projet de test

Un projet de test est fourni pour démontrer l'utilisation de la bibliothèque.

### 1. Naviguer vers le projet de test

```sh
cd test_project/
```

2. Compiler le projet de test

```sh

make clean
make
```

3. Exécuter le projet de test

```sh
./bin/main
```


4. Résultat attendu

    Une fenêtre intitulée "ArticWindow" s'ouvre avec un fond rose.
    Appuyez sur la touche Échap pour fermer la fenêtre.

Structure du Projet

```css

LibArtic/
├── include/
│   ├── artic.h
│   └── graphic.h
├── src/
│   ├── artic.c           # Si nécessaire
│   └── graphics/
│       ├── graphic.cpp
│       └── graphic.hpp
├── Makefile
└── test_project/
    ├── include/
    │   └── my_module.h
    ├── src/
    │   └── main.c
    └── Makefile
```


## Détails Techniques
### Fonctionnalités Principales
```css
    Création de fenêtre : new_window(const char* title, int width, int height, int fullscreen)
    Création de pixelarray : new_pixelarray(int width, int height)
    Gestion des événements : artic_set_key_response(t_artic_window* win, t_artic_event_func func)
    Boucle principale : artic_loop(t_artic_window* win, int fps, void* data)
    Affichage : artic_display(t_artic_window* win)
```

### Types et Structures
```c
    t_artic_window : Représente une fenêtre SFML.
    t_artic_pixelarray : Représente un tableau de pixels pour le rendu.
    t_artic_response : Enumération pour les réponses des fonctions (GO_ON, EXIT_ON_SUCCESS).
    t_artic_event_state : Enumération pour l'état des événements (GO_DOWN, GO_UP).
    t_artic_keysym : Enumération pour les codes de touches (par exemple, BKS_ESCAPE).
```

#### Exemple de Code
##### main.c

```c

#include <stdio.h>
#include "my_module.h"
#include <artic.h>

typedef struct {
    t_artic_window* win;
    t_artic_pixelarray* pix;
} t_artic_data;

t_artic_response display(void *data)
{
    t_artic_data *d = (t_artic_data *) data;

    // Blit le pixelarray sur lui-même (pour cet exemple)
    artic_blit(d->pix, d->pix, NULL);

    // Définit le pixelarray de la fenêtre
    artic_set_window_pixelarray(d->win, d->pix);

    // Affiche la fenêtre
    artic_display(d->win);
    return GO_ON;
}

t_artic_response event_handler(t_artic_event_state state, t_artic_keysym key, void *data)
{
    (void)data;  // Supprime l'avertissement de paramètre inutilisé
    if (state == GO_DOWN && key == BKS_ESCAPE)
        return EXIT_ON_SUCCESS;
    return GO_ON;
}

t_artic_response loop(void *data)
{
    (void) data;
    return GO_ON;
}

int main(void)
{
    t_artic_window *win = new_window("ArticWindow", 800, 600, 0);
    t_artic_pixelarray *pix = new_pixelarray(800, 600);

    int width = artic_get_pixelarray_width(pix);
    int height = artic_get_pixelarray_height(pix);
    uint8_t* pixels = artic_get_pixelarray_pixels(pix);

    // Remplit le pixelarray avec la couleur rose
    for (int i = 0; i < width * height * 4; i += 4)
    {
        pixels[i] = 255;       // R
        pixels[i + 1] = 192;   // G
        pixels[i + 2] = 203;   // B
        pixels[i + 3] = 255;   // A
    }

    // Met à jour la texture avec les nouvelles données de pixels
    artic_update_pixelarray_texture(pix);

    t_artic_data data = {win, pix};

    artic_set_loop_main_function(win, loop);
    artic_set_key_response(win, event_handler);
    artic_set_display_function(win, display);
    artic_loop(win, 60, &data);

    // Nettoyage
    delete_pixelarray(pix);
    delete_window(win);
    return 0;
}
```

##### my_module.h

```c

#ifndef MY_MODULE_H
#define MY_MODULE_H

#include <artic.h>

// Autres déclarations si nécessaire

#endif /* MY_MODULE_H */
```

##### Makefile

```makefile

# Variables
CC := gcc
CXX := g++
CFLAGS := -Iinclude -I/usr/local/include/artic -Wall -Wextra -O2
CXXFLAGS := -Iinclude -I/usr/local/include/artic -Wall -Wextra -O2
LDFLAGS := -L/usr/local/lib -lartic -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR := src
INCLUDEDIR := include
BUILDDIR := build
BINDIR := bin
TARGET := $(BINDIR)/main

SOURCES_C := $(wildcard $(SRCDIR)/*.c)
SOURCES_CPP := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS_C := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES_C))
OBJECTS_CPP := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES_CPP))
OBJECTS := $(OBJECTS_C) $(OBJECTS_CPP)

# Cible par défaut
all: $(TARGET)

# Construction de l'exécutable cible
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Build successful: $(TARGET)"

# Compilation des fichiers source C
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation des fichiers source C++ (s'il y en a)
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	rm -rf $(BUILDDIR)
	@echo "Cleaned object files."

# Nettoyage complet
fclean: clean
	rm -rf $(BINDIR)
	@echo "Cleaned binaries."

# Reconstruction du projet
re: fclean all

.PHONY: all clean fclean re
```


### Contributions

Les contributions sont les bienvenues ! N'hésitez pas à ouvrir des issues ou des pull requests pour améliorer la bibliothèque.
Licence

Ce projet est sous licence MIT. Voir le fichier LICENSE pour plus de détails.


### Auteurs

    Baptiste Renneson - Développeur principal - Elania-Marvers