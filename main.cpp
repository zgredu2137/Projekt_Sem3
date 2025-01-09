#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

//temat 1.1
class ekran_koncowy {
private:
    sf::Font font;
    sf::Text Tytul;
    sf::Text TwojWynik;
    sf::Text KoniecGry;
    std::vector<sf::Text> NickiWyniki;

public:
    ekran_koncowy(const std::vector<std::pair<std::string, int>>& wyniki, const std::string& twojNick, int twojWynik) {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Nie udalo sie zaladowac czcionki!" << std::endl;
        }

        Tytul.setFont(font);
        Tytul.setCharacterSize(48);
        Tytul.setFillColor(sf::Color::White);
        Tytul.setString("Najlepsze Wyniki");
        Tytul.setPosition(800 - Tytul.getGlobalBounds().width / 2, 50);

        TwojWynik.setFont(font);
        TwojWynik.setCharacterSize(36);
        TwojWynik.setFillColor(sf::Color::White);
        TwojWynik.setString("Twoj wynik (" + twojNick + "): " + std::to_string(twojWynik));
        TwojWynik.setPosition(800 - TwojWynik.getGlobalBounds().width / 2, 150);

        KoniecGry.setFont(font);
        KoniecGry.setCharacterSize(36);
        KoniecGry.setFillColor(sf::Color::White);
        KoniecGry.setString("Koniec gry!");
        KoniecGry.setPosition(800 - KoniecGry.getGlobalBounds().width / 2, 200);

        int yOffset = 250;
        for (const auto& wynik : wyniki) {
            sf::Text nickWynik;
            nickWynik.setFont(font);
            nickWynik.setCharacterSize(24);
            nickWynik.setFillColor(sf::Color::White);
            nickWynik.setString(wynik.first + ": " + std::to_string(wynik.second));
            nickWynik.setPosition(800 - nickWynik.getGlobalBounds().width / 2, yOffset);
            NickiWyniki.push_back(nickWynik);
            yOffset += 50;
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(Tytul);
        window.draw(TwojWynik);
        window.draw(KoniecGry);
        for (const auto& nickWynik : NickiWyniki) {
            window.draw(nickWynik);
        }
    }
};


class wybor_poziomu {
private:
    sf::Font font;
    sf::Text Tytul;
    std::vector<sf::Text> poziomy;
    int selectedLevel;

public:
    wybor_poziomu() : selectedLevel(-1) {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Nie udalo sie zaladowac czcionki!" << std::endl;
        }

        Tytul.setFont(font);
        Tytul.setCharacterSize(48);
        Tytul.setFillColor(sf::Color::White);
        Tytul.setString("Wybierz Poziom Trudnosci");
        Tytul.setPosition(800 - Tytul.getGlobalBounds().width / 2, 100);

        std::vector<std::string> poziomyTekst = { "Latwy", "Sredni", "Trudny", "Bardzo Trudny", "Niemozliwy" };
        for (int i = 0; i < 5; ++i) {
            sf::Text poziom;
            poziom.setFont(font);
            poziom.setCharacterSize(36);
            poziom.setFillColor(sf::Color::White);
            poziom.setString(poziomyTekst[i]);
            poziom.setPosition(800 - poziom.getGlobalBounds().width / 2, 200 + i * 100);
            poziomy.push_back(poziom);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(Tytul);
        for (const auto& poziom : poziomy) {
            window.draw(poziom);
        }
    }

    void handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            for (int i = 0; i < poziomy.size(); ++i) {
                if (poziomy[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    selectedLevel = i;
                    break;
                }
            }
        }
    }

    int getSelectedLevel() const {
        return selectedLevel;
    }
};

class menu {
private:
    sf::Font font;
    sf::Text Tytul;
    sf::Text StartButton;
    sf::Text NickLabel;
    sf::RectangleShape NickInputBox;
    sf::String NickString;
    sf::Text NickText;
    bool isNickInputActive;

public:
    menu() : isNickInputActive(false) {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Nie udalo sie zaladowac czcionki!" << std::endl;
        }

        Tytul.setFont(font);
        Tytul.setCharacterSize(48);
        Tytul.setFillColor(sf::Color::White);
        Tytul.setString("Tytul Gry");
        Tytul.setPosition(800 - Tytul.getGlobalBounds().width / 2, 100);

        StartButton.setFont(font);
        StartButton.setCharacterSize(36);
        StartButton.setFillColor(sf::Color::White);
        StartButton.setString("Start");
        StartButton.setPosition(800 - StartButton.getGlobalBounds().width / 2, 300);

        NickLabel.setFont(font);
        NickLabel.setCharacterSize(24);
        NickLabel.setFillColor(sf::Color::White);
        NickLabel.setString("Nick:");
        NickLabel.setPosition(800 - NickLabel.getGlobalBounds().width / 2, 500);

        NickInputBox.setSize(sf::Vector2f(300, 50));
        NickInputBox.setFillColor(sf::Color::White);
        NickInputBox.setPosition(800 - NickInputBox.getSize().x / 2, 550);

        NickText.setFont(font);
        NickText.setCharacterSize(24);
        NickText.setFillColor(sf::Color::Black);
        NickText.setPosition(NickInputBox.getPosition().x + 10, NickInputBox.getPosition().y + 10);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(Tytul);
        window.draw(StartButton);
        window.draw(NickLabel);
        window.draw(NickInputBox);
        window.draw(NickText);
    }

    void handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (NickInputBox.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                isNickInputActive = true;
            }
            else {
                isNickInputActive = false;
            }
        }

        if (isNickInputActive && event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b' && !NickString.isEmpty()) {
                NickString.erase(NickString.getSize() - 1, 1);
            }
            else if (event.text.unicode < 128 && event.text.unicode != '\b') {
                NickString += event.text.unicode;
            }
            NickText.setString(NickString);
        }
    }
    bool isStartButtonPressed(const sf::Event& event) const {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (StartButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                return true;
            }
        }
        return false;
    }

    std::string getNick() const {
        return NickString.toAnsiString();
    }
};

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
    menu menu; // Utwórz obiekt menu
    wybor_poziomu wyborPoziomu; // Utwórz obiekt wyboru poziomu

    // Inicjalizuj generator liczb losowych
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Zegar do œledzenia czasu
    sf::Clock clock;
    float timeToNextPocisk = static_cast<float>((std::rand() % 500 + 100) * std::pow(1.5, std::rand() % 3)); // bardziej nieregularny czas do nastêpnego pocisku

    enum GameState { MENU, LEVEL_SELECTION, GAME, END_SCREEN };
    GameState gameState = MENU;

    std::vector<std::pair<std::string, int>> wyniki; // Przechowuj wyniki
    std::string nick; // Przechowuj nick gracza

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            switch (gameState) {
            case MENU:
                menu.handleEvent(event);
                if (menu.isStartButtonPressed(event)) {
                    gameState = LEVEL_SELECTION;
                }
                break;
            case LEVEL_SELECTION:
                wyborPoziomu.handleEvent(event);
                if (wyborPoziomu.getSelectedLevel() != -1) {
                    gameState = GAME;
                    nick = menu.getNick();
                    std::cout << "Wybrany poziom: " << wyborPoziomu.getSelectedLevel() << std::endl;
                    std::cout << "Nick: " << nick << std::endl;
                }
                break;
            case GAME:
                // Obs³uga zdarzeñ w grze
                break;
            case END_SCREEN:
                // Obs³uga zdarzeñ na ekranie koñcowym
                break;
            }
        }

        if (gameState == GAME) {
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

            // SprawdŸ, czy gracz ma jeszcze ¿ycie
            if (interfejs.getLives() <= 0) {
                std::cout << "Koniec gry!" << std::endl;
                wyniki.push_back({ nick, interfejs.getLives() });
                ekran_koncowy ekranKoncowy(wyniki, nick, interfejs.getLives());
                gameState = END_SCREEN;
            }
        }
        else if (gameState == END_SCREEN) {
            window.clear();
            ekran_koncowy ekranKoncowy(wyniki, nick, interfejs.getLives());
            ekranKoncowy.draw(window);
        }
        else {
            window.clear();
            if (gameState == MENU) {
                menu.draw(window);
            }
            else if (gameState == LEVEL_SELECTION) {
                wyborPoziomu.draw(window);
            }
        }

        window.display();
    }

    return 0;
}

