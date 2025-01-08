#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

//temat 1.1
class interfejs {
private:
    sf::Font font;
    sf::Text wynik;
    sf::Text zycia;
    int liczba_wynik;
    int liczba_zycia;

public:
    interfejs() : liczba_wynik(0), liczba_zycia(3) {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Nie udalo sie zaladowac czcionki!" << std::endl;
        }
        wynik.setFont(font);
        wynik.setCharacterSize(24);
        wynik.setFillColor(sf::Color::White);
        wynik.setPosition(10, 10); // Pozycja w lewym górnym rogu


        zycia.setFont(font);
        zycia.setCharacterSize(24);
        zycia.setFillColor(sf::Color::White);
        zycia.setPosition(10, 40); // Pozycja w lewym górnym rogu

        updateText();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(wynik);
        window.draw(zycia);
    }

    void updateText() {
        wynik.setString("Wynik: " + std::to_string(liczba_wynik));
        zycia.setString("Zycia: " + std::to_string(liczba_zycia));
    }

    void updateScore() {
        liczba_wynik++;
        updateText();
    }

    void updateLives() {
        liczba_zycia--;
        updateText();
    }

    int getLives() const {
        return liczba_zycia;
    }
};

class gracz {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;

public:
    gracz(float x_in, float y_in) {
        if (!texture.loadFromFile("Player.png")) {
            std::cerr << "Nie udalo sie zaladowac tekstury gracza!" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(0.1f, 0.1f); // zmniejsz rozmiar gracza
        sprite.setPosition(x_in, y_in);
        speed = 1.0f; // prêdkoœæ gracza
    }

    void ruch() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sprite.move(-speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sprite.move(speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sprite.move(0, -speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sprite.move(0, speed);
        }
    }

    const sf::Sprite& getSprite() const { return sprite; }
    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }
};

class pocisk {
private:
    sf::Vector2f position; // wspolrzedne
    float xVel; // predkosc w poziomie
    float yVel; // predkosc w pionie
    sf::CircleShape ball; // pilka
    sf::Texture texture; // tekstura

public:
    pocisk(float x_in, float y_in) {
        if (!texture.loadFromFile("pocisk.jpg")) {
            std::cerr << "Nie udalo sie zaladowac tekstury!" << std::endl;
        }
        ball.setTexture(&texture);
        position = sf::Vector2f(x_in, y_in);
        ball.setPosition(position);
        ball.setRadius(10.f); // Zwiêksz promieñ pocisku
        ball.setFillColor(sf::Color::Red);

        // Inicjalizuj generator liczb losowych
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        xVel = static_cast<float>((std::rand() % 3) - 1) * 0.2f; // zmniejszona losowa predkosc w poziomie (-0.2, 0, 0.2)
        yVel = static_cast<float>((std::rand() % 3) + 1) * 0.2f; // zmniejszona losowa predkosc w pionie (0.2, 0.4, 0.6)
    }

    void przesun() {
        // przesun pilke w dol i w poziomie
        position.x += xVel;
        position.y += yVel;
        ball.setPosition(position);

        // Zmien kierunek poziomy losowo
        if (std::rand() % 100 < 20) { // 20% szans na zmiane kierunku
            xVel = static_cast<float>((std::rand() % 3) - 1) * 0.2f; // zmniejszona losowa predkosc w poziomie (-0.2, 0, 0.2)
        }
    }

    const sf::CircleShape& getPocisk() const { return ball; } // zwroc pilke jako const referencje
    sf::Vector2f getPos() const { return ball.getPosition(); }
    bool isOutOfScreen() const { return position.y > 800; } // sprawdz, czy pocisk wyszedl poza ekran
    sf::FloatRect getBounds() const { return ball.getGlobalBounds(); }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Zadanie projektowe 1.1");
    std::vector<pocisk> pociski;
    gracz player(800.f, 400.f); // Utwórz gracza na œrodku ekranu
    interfejs interfejs; // Utwórz obiekt interfejsu

    // Inicjalizuj generator liczb losowych
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Zegar do œledzenia czasu
    sf::Clock clock;
    float timeToNextPocisk = static_cast<float>((std::rand() % 500 + 100) * std::pow(1.5, std::rand() % 3)); // bardziej nieregularny czas do nastêpnego pocisku

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // SprawdŸ, czy min¹³ czas do nastêpnego pocisku
        if (clock.getElapsedTime().asMilliseconds() >= timeToNextPocisk) {
            pociski.emplace_back(static_cast<float>(std::rand() % 1600), 0.f);
            timeToNextPocisk = static_cast<float>((std::rand() % 500 + 100) * std::pow(1.5, std::rand() % 3)); // ustaw nowy bardziej nieregularny czas do nastêpnego pocisku
            clock.restart(); // zrestartuj zegar
        }

        // Przesun kazdy pocisk
        for (auto& p : pociski) {
            p.przesun();
        }

        // Usun pociski, ktore wyszly poza ekran
        pociski.erase(std::remove_if(pociski.begin(), pociski.end(), [](const pocisk& p) { return p.isOutOfScreen(); }), pociski.end());

        // Ruch gracza
        player.ruch();

        // SprawdŸ kolizje miêdzy graczem a pociskami
        for (auto& p : pociski) {
            if (player.getBounds().intersects(p.getBounds())) {
                interfejs.updateLives();
                // Mo¿esz usun¹æ pocisk po kolizji, jeœli chcesz
                p = pociski.back();
                pociski.pop_back();
                break; // WyjdŸ z pêtli, aby unikn¹æ wielokrotnych kolizji w jednej klatce
            }
        }

        // Aktualizuj wynik i ¿ycie 
        interfejs.updateScore();

        window.clear();
        // Narysuj kazdy pocisk
        for (const auto& p : pociski) {
            window.draw(p.getPocisk());
        }
        // Narysuj gracza
        window.draw(player.getSprite());
        // Narysuj interfejs
        interfejs.draw(window);
        window.display();

        // SprawdŸ, czy gracz ma jeszcze ¿ycie
        if (interfejs.getLives() <= 0) {
            std::cout << "Koniec gry!" << std::endl;
            window.close();
        }
    }

    return 0;
}
