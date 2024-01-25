#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

// Constants globals
const std::string title = "Fronton";
const float ballSpeedBase = 100.0f;
const float playerSpeed = 9.0f;
const int x_min = 0, x_max = 800;
const int y_min = 0, y_max = 600;
const int incre_xr = 10, incre_yr = 10;
const int longitut = 100, amplada = 20, radi = 25;

// Estructura para representar un bloque
struct Bloque {
    RectangleShape shape;
    bool activo;  // Indica si el bloque está activo o no
};

// Variable global para almacenar los puntos
extern int puntos;

// Prototipos de funciones
void UpdateInput(RenderWindow& finestre, RectangleShape& player);
void Update(float dt, CircleShape& bola, RectangleShape& player,
    float& ballSpeedX, float& ballSpeedY, std::vector<Bloque>& bloques);
void Draw(RenderWindow& finestre, CircleShape& bola, RectangleShape& player, const std::vector<Bloque>& bloques);
int ColisioAmbBola(CircleShape& bola, RectangleShape& player, int incre_yc);
void CheckGameOver(RenderWindow& window, CircleShape& bola);
void CheckColisionBloques(CircleShape& bola, std::vector<Bloque>& bloques);