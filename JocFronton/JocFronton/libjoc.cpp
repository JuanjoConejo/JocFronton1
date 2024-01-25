#include "libjoc.h"

int puntos = 0;  // Inicializa el contador de puntos

void Draw(RenderWindow& finestre, CircleShape& bola, RectangleShape& player, const std::vector<Bloque>& bloques) {
    finestre.clear(sf::Color::Magenta);
    finestre.draw(bola);
    finestre.draw(player);

    // Dibuja bloques
    bool todosBloquesDesactivados = true;  // Variable para verificar si todos los bloques están desactivados

    for (const auto& bloque : bloques) {
        if (bloque.activo) {
            finestre.draw(bloque.shape);
            todosBloquesDesactivados = false;  // Aún hay bloques activos
        }
    }

    // Muestra el contador de puntos
    Font font;
    if (font.loadFromFile("./fonts/KOMIKAP_.ttf")) {
        Text puntosText("Puntos: " + std::to_string(puntos), font, 20);
        puntosText.setPosition(finestre.getView().getCenter().x + finestre.getView().getSize().x / 2 - 150, 10);
        puntosText.setFillColor(Color::White);
        finestre.draw(puntosText);
    }

    finestre.display();

    // Verifica la condición de victoria
    if (todosBloquesDesactivados) {
        // El jugador ha destruido todos los bloques, se considera una victoria
        // Puedes agregar aquí la lógica que desees para indicar que el jugador ha ganado
        std::cout << "¡Has ganado la partida!" << std::endl;
        finestre.close();  // Cierra la ventana del juego (puedes modificar esto según tus necesidades)
    }
}

void Update(float dt, CircleShape& bola, RectangleShape& player, float& ballSpeedX, float& ballSpeedY, std::vector<Bloque>& bloques) {
    bola.move(ballSpeedX * dt, ballSpeedY * dt);

    if (bola.getPosition().x - bola.getRadius() < x_min || bola.getPosition().x + bola.getRadius() > x_max) {
        ballSpeedX = -ballSpeedX; // Invierte la dirección en X
    }

    if (bola.getPosition().y - bola.getRadius() < y_min || bola.getPosition().y + bola.getRadius() > y_max) {
        ballSpeedY = -ballSpeedY; // Invierte la dirección en Y
    }

    if (bola.getPosition().y + bola.getRadius() > player.getPosition().y - player.getSize().y / 2 &&
        bola.getPosition().x > player.getPosition().x - player.getSize().x / 2 &&
        bola.getPosition().x < player.getPosition().x + player.getSize().x / 2) {
        ballSpeedY = -ballSpeedY;
    }

    // Actualiza la colisión con bloques
    CheckColisionBloques(bola, bloques);
}

void UpdateInput(RenderWindow& finestre, RectangleShape& player) {
    if (Keyboard::isKeyPressed(Keyboard::Left) && player.getPosition().x - player.getSize().x / 2 > x_min) {
        player.move(-playerSpeed, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::Right) && player.getPosition().x + player.getSize().x / 2 < x_max) {
        player.move(playerSpeed, 0);
    }
}

void CheckGameOver(RenderWindow& window, CircleShape& bola) {
    if (bola.getPosition().y + bola.getRadius() > y_max) {
        window.close(); // Cierra la ventana del juego
    }
}

void CheckColisionBloques(CircleShape& bola, std::vector<Bloque>& bloques) {
    for (auto& bloque : bloques) {
        if (bloque.activo) {
            FloatRect bloqueRect = bloque.shape.getGlobalBounds();
            if (bola.getGlobalBounds().intersects(bloqueRect)) {
                bloque.activo = false;  // Desactiva el bloque al colisionar
                puntos += 5;           // Suma 5 puntos al contador
            }
        }
    }
}