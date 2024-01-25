#include <iostream>
#include <SFML/Graphics.hpp>
#include "libjoc.h"

using namespace sf;

int main() {
    Vector2f viewSize(x_max, y_max);
    VideoMode vm(viewSize.x, viewSize.y);
    RenderWindow window(vm, title, Style::Default);
    window.setFramerateLimit(60);

    CircleShape bola(radi);
    bola.setFillColor(Color::White);
    bola.setOrigin(bola.getRadius(), bola.getRadius());
    bola.setPosition(viewSize.x / 2, viewSize.y / 2);

    RectangleShape player;
    player.setFillColor(Color::White);
    player.setSize(Vector2f(longitut, amplada));
    FloatRect playerRect = player.getLocalBounds();
    player.setOrigin(playerRect.left + playerRect.width / 2.0f,
        playerRect.top + playerRect.height / 2.0f);
    player.setPosition(viewSize.x / 2, viewSize.y - 50);

    float ballSpeedX = ballSpeedBase * 1.7;
    float ballSpeedY = ballSpeedBase * 1;

    std::vector<Bloque> bloques;
    for (int j = 0; j < 3; ++j) { // Agregamos dos filas más
        for (int i = 0; i < 5; ++i) {
            Bloque bloque;
            bloque.shape.setSize(Vector2f(80, 30));
            bloque.shape.setFillColor(Color::Green);
            bloque.shape.setPosition(i * 160, 50 + j * 40); // Ajustamos la posición en Y
            bloque.activo = true;
            bloques.push_back(bloque);
        }
    }

    Clock reloj;
    while (window.isOpen()) {
        UpdateInput(window, player);

        sf::Time dt = reloj.restart();
        Update(dt.asSeconds(), bola, player, ballSpeedX, ballSpeedY, bloques);

        CheckGameOver(window, bola);

        Draw(window, bola, player, bloques);
    }
    return 0;
}