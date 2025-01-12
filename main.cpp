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

        std::vector<std::string> poziomyTekst = { "Bardzo latwy","Latwy", "Sredni", "Trudny", "Bardzo Trudny", "Niemozliwy", ""};
        for (int i = 0; i < 6; ++i) {
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
        wynik.setPosition(10, 10); // Pozycja w lewym gÛrnym rogu


        zycia.setFont(font);
        zycia.setCharacterSize(24);
        zycia.setFillColor(sf::Color::White);
        zycia.setPosition(10, 40); // Pozycja w lewym gÛrnym rogu

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

class przeciwnik_zero {
private:
    std::vector<sf::Sprite> sprites;
    sf::Texture texture;
    float speed;

    


public:
    przeciwnik_zero(float windowWidth) {
        if (!texture.loadFromFile("przeciwnik.png")) {
            std::cerr << "Nie udalo sie zaladowac tekstury przeciwnika!" << std::endl;
        }
        speed = 0.4f; // prÍdkoúÊ przeciwnika

        // Tworzenie 5 sprite'Ûw przeciwnikÛw
        for (int i = 0; i < 5; ++i) {
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setScale(0.3f, 0.3f); // zmniejsz rozmiar przeciwnika
            sprite.setPosition(100.0f + i * 150.0f, 50.0f); // ustawienie pozycji przeciwnikÛw w gÛrnej czÍúci ekranu
            sprites.push_back(sprite);
        }
    }

    void ruch() {
        for (auto& sprite : sprites) {
            sprite.move(0, speed);
        }
        // Update projectiles
        
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& sprite : sprites) {
            window.draw(sprite);
        }
    }

    
    
    const std::vector<sf::Sprite>& getSprites() const { return sprites; }
};

class przeciwnik_jeden {
private:
    std::vector<sf::Sprite> sprites;
    sf::Texture texture;
    float speed;
    
public:
    przeciwnik_jeden(float windowWidth) {
        if (!texture.loadFromFile("przeciwnik1.png")) {
            std::cerr << "Nie udalo sie zaladowac tekstury przeciwnika!" << std::endl;
        }
        speed = 0.5f; // prÍdkoúÊ przeciwnika

        // Tworzenie 5 sprite'Ûw przeciwnikÛw
        for (int i = 0; i < 6; ++i) {
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setScale(0.3f, 0.3f); // zmniejsz rozmiar przeciwnika
            sprite.setPosition(100.0f + i * 150.0f, 50.0f); // ustawienie pozycji przeciwnikÛw w gÛrnej czÍúci ekranu
            sprites.push_back(sprite);
        }
    }

    void ruch() {
        for (auto& sprite : sprites) {
            sprite.move(speed, 0);

            // Odbijanie od krawÍdzi ekranu
            if (sprite.getPosition().x + sprite.getGlobalBounds().width > 1600.0f || sprite.getPosition().x < 0) {
                speed = -speed;
                sprite.move(speed, 0); // cofniÍcie ruchu po odbiciu
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& sprite : sprites) {
            window.draw(sprite);
        }
    }
   

    const std::vector<sf::Sprite>& getSprites() const { return sprites; }
};

class przeciwnik_dwa {
private:
    std::vector<sf::Sprite> sprites;
    sf::Texture texture;
    float speed;
	
public:
    przeciwnik_dwa(float windowWidth) {
        if (!texture.loadFromFile("przeciwnik2.png")) {
            std::cerr << "Nie udalo sie zaladowac tekstury przeciwnika!" << std::endl;
        }
        speed = 0.6f; // prÍdkoúÊ przeciwnika

        // Tworzenie 5 sprite'Ûw przeciwnikÛw
        for (int i = 0; i < 7; ++i) {
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setScale(0.3f, 0.3f); // zmniejsz rozmiar przeciwnika
            sprite.setPosition(100.0f + i * 150.0f, 50.0f); // ustawienie pozycji przeciwnikÛw w gÛrnej czÍúci ekranu
            sprites.push_back(sprite);
        }
    }

    void ruch() {
        for (auto& sprite : sprites) {
            sprite.move(speed, 0);

            // Odbijanie od krawÍdzi ekranu
            if (sprite.getPosition().x + sprite.getGlobalBounds().width > 1600.0f || sprite.getPosition().x < 0) {
                speed = -speed;
                sprite.move(speed, 0); // cofniÍcie ruchu po odbiciu
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& sprite : sprites) {
            window.draw(sprite);
        }
    }
  

    const std::vector<sf::Sprite>& getSprites() const { return sprites; }
};

class przeciwnik_trzy {
private:
    std::vector<sf::Sprite> sprites;
    sf::Texture texture;
    float speed;
	

public:
    przeciwnik_trzy(float windowWidth) {
        if (!texture.loadFromFile("przeciwnik3.png")) {
            std::cerr << "Nie udalo sie zaladowac tekstury przeciwnika!" << std::endl;
        }
        speed = 0.8f; // prÍdkoúÊ przeciwnika

        // Tworzenie 5 sprite'Ûw przeciwnikÛw
        for (int i = 0; i < 8; ++i) {
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setScale(0.2f, 0.2f); // zmniejsz rozmiar przeciwnika
            sprite.setPosition(100.0f + i * 150.0f, 50.0f); // ustawienie pozycji przeciwnikÛw w gÛrnej czÍúci ekranu
            sprites.push_back(sprite);
        }
    }

    void ruch() {
        for (auto& sprite : sprites) {
            sprite.move(speed, 0);

            // Odbijanie od krawÍdzi ekranu
            if (sprite.getPosition().x + sprite.getGlobalBounds().width > 1600.0f || sprite.getPosition().x < 0) {
                speed = -speed;
                sprite.move(speed, 0); // cofniÍcie ruchu po odbiciu
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& sprite : sprites) {
            window.draw(sprite);
        }
    }


    const std::vector<sf::Sprite>& getSprites() const { return sprites; }
};

class przeciwnik_cztery {
private:
    std::vector<sf::Sprite> sprites;
    sf::Texture texture;
    float speed;

public:
    przeciwnik_cztery(float windowWidth) {
        if (!texture.loadFromFile("przeciwnik4.gif")) {
            std::cerr << "Nie udalo sie zaladowac tekstury przeciwnika!" << std::endl;
        }
        speed = 0.9f; // prÍdkoúÊ przeciwnika

        // Tworzenie 5 sprite'Ûw przeciwnikÛw
        for (int i = 0; i < 9; ++i) {
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setScale(0.3f, 0.3f); // zmniejsz rozmiar przeciwnika
            sprite.setPosition(100.0f + i * 150.0f, 50.0f); // ustawienie pozycji przeciwnikÛw w gÛrnej czÍúci ekranu
            sprites.push_back(sprite);
        }
    }

    void ruch() {
        for (auto& sprite : sprites) {
            sprite.move(speed, 0);

            // Odbijanie od krawÍdzi ekranu
            if (sprite.getPosition().x + sprite.getGlobalBounds().width > 1600.0f || sprite.getPosition().x < 0) {
                speed = -speed;
                sprite.move(speed, 0); // cofniÍcie ruchu po odbiciu
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& sprite : sprites) {
            window.draw(sprite);
        }
    }

    const std::vector<sf::Sprite>& getSprites() const { return sprites; }
};

class przeciwnik_piec {
private:
    std::vector<sf::Sprite> sprites;
    sf::Texture texture;
    float speed;

public:
    przeciwnik_piec(float windowWidth) {
        if (!texture.loadFromFile("przeciwnik5.png")) {
            std::cerr << "Nie udalo sie zaladowac tekstury przeciwnika!" << std::endl;
        }
        speed = 0.9f; // prÍdkoúÊ przeciwnika

        // Tworzenie 5 sprite'Ûw przeciwnikÛw
        for (int i = 0; i < 7; ++i) {
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setScale(0.07f, 0.07f); // zmniejsz rozmiar przeciwnika
            sprite.setPosition(100.0f + i * 150.0f, 50.0f); // ustawienie pozycji przeciwnikÛw w gÛrnej czÍúci ekranu
            sprites.push_back(sprite);
        }

        for (int i = 0; i < 7; ++i) {
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setScale(0.07f, 0.07f); // zmniejsz rozmiar przeciwnika
            sprite.setPosition(150.0f + i * 150.0f, 150.0f); // ustawienie pozycji przeciwnikÛw w gÛrnej czÍúci ekranu
            sprites.push_back(sprite);
        }
    }

    void ruch() {
        for (auto& sprite : sprites) {
            sprite.move(speed, 0);

            // Odbijanie od krawÍdzi ekranu
            if (sprite.getPosition().x + sprite.getGlobalBounds().width > 1600.0f || sprite.getPosition().x < 0) {
                speed = -speed;
                sprite.move(speed, 0); // cofniÍcie ruchu po odbiciu
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& sprite : sprites) {
            window.draw(sprite);
        }
    }

    const std::vector<sf::Sprite>& getSprites() const { return sprites; }
};

class pocisk {
private:
    sf::Vector2f position; // wspolrzedne
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
        ball.setRadius(10.f); // ZwiÍksz promieÒ pocisku
        ball.setFillColor(sf::Color::Red);

        yVel = -0.5f; // prÍdkoúÊ pocisku w gÛrÍ
    }

    void przesun() {
        // przesun pilke w gore
        position.y += yVel;
        ball.setPosition(position);
    }

    const sf::CircleShape& getPocisk() const { return ball; } // zwroc pilke jako const referencje
    sf::Vector2f getPos() const { return ball.getPosition(); }
    bool isOutOfScreen() const { return position.y < 0; } // sprawdz, czy pocisk wyszedl poza ekran
    sf::FloatRect getBounds() const { return ball.getGlobalBounds(); }
};

class gracz {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    sf::Clock shootClock; // Zegar do úledzenia czasu miÍdzy strza≥ami
    float shootInterval; // Interwa≥ czasowy miÍdzy strza≥ami
    float windowWidth; // SzerokoúÊ okna
    float windowHeight; // WysokoúÊ okna

public:
    gracz(float x_in, float y_in) {
        if (!texture.loadFromFile("Player.png")) {
            std::cerr << "Nie udalo sie zaladowac tekstury gracza!" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(0.1f, 0.1f); // zmniejsz rozmiar gracza
        sprite.setPosition(x_in, y_in);
        speed = 1.0f; // prÍdkoúÊ gracza
        shootInterval = 1.0f; // interwa≥ czasowy miÍdzy strza≥ami w sekundach
        windowWidth = 1600.0f; // SzerokoúÊ okna
        windowHeight = 800.0f; // WysokoúÊ okna
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

        // Ograniczenia ruchu gracza do granic okna
        sf::Vector2f position = sprite.getPosition();
        if (position.x < 0) {
            sprite.setPosition(0, position.y);
        }
        if (position.x + sprite.getGlobalBounds().width > windowWidth) {
            sprite.setPosition(windowWidth - sprite.getGlobalBounds().width, position.y);
        }
        if (position.y < 0) {
            sprite.setPosition(position.x, 0);
        }
        if (position.y + sprite.getGlobalBounds().height > windowHeight) {
            sprite.setPosition(position.x, windowHeight - sprite.getGlobalBounds().height);
        }
    }

    bool canShoot() {
        if (shootClock.getElapsedTime().asSeconds() >= shootInterval) {
            shootClock.restart();
            return true;
        }
        return false;
    }

    pocisk shoot() {
        return pocisk(sprite.getPosition().x + sprite.getGlobalBounds().width / 2, sprite.getPosition().y);
    }

    const sf::Sprite& getSprite() const { return sprite; }
    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Zadanie projektowe 1.1");
    interfejs interfejs; // UtwÛrz obiekt interfejsu
    std::vector<pocisk> pociski;
    gracz player(800.f, 400.f); // UtwÛrz gracza na úrodku ekranu
    menu menu; // UtwÛrz obiekt menu
    wybor_poziomu wyborPoziomu; // UtwÛrz obiekt wyboru poziomu
	

    // Inicjalizuj generator liczb losowych
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    enum GameState { MENU, LEVEL_SELECTION, GAME, END_SCREEN };
    GameState gameState = MENU;

    std::vector<std::pair<std::string, int>> wyniki; // Przechowuj wyniki
    std::string nick; // Przechowuj nick gracza

	

	przeciwnik_zero* przeciwnik0 = nullptr; // Wskaünik na przeciwnika
    przeciwnik_jeden* przeciwnik1 = nullptr; // Wskaünik na przeciwnika
	przeciwnik_dwa* przeciwnik2 = nullptr; // Wskaünik na przeciwnika
	przeciwnik_trzy* przeciwnik3 = nullptr; // Wskaünik na przeciwnika
	przeciwnik_cztery* przeciwnik4 = nullptr; // Wskaünik na przeciwnika
	przeciwnik_piec* przeciwnik5 = nullptr; // Wskaünik na przeciwnika
    


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

                    
                    if (wyborPoziomu.getSelectedLevel() == 0) {
                        przeciwnik0 = new przeciwnik_zero(1600.0f);
                    }
                    if(wyborPoziomu.getSelectedLevel() == 1) {
                        przeciwnik1 = new przeciwnik_jeden(1600.0f);
                    }
                    if(wyborPoziomu.getSelectedLevel() == 2) {
                        przeciwnik2 = new przeciwnik_dwa(1600.0f);
				    }
				    if
                    (wyborPoziomu.getSelectedLevel() == 3) {
                        przeciwnik3 = new przeciwnik_trzy(1600.0f);
                    }
                    if(wyborPoziomu.getSelectedLevel() == 4) {
                        przeciwnik4 = new przeciwnik_cztery(1600.0f);
                    }
                    if(wyborPoziomu.getSelectedLevel() == 5) {
                        przeciwnik5 = new przeciwnik_piec(1600.0f);
                    }
                }
                break;
            case GAME:
                // Obs≥uga zdarzeÒ w grze
                break;
            case END_SCREEN:
                // Obs≥uga zdarzeÒ na ekranie koÒcowym
                break;
            }
        }

        if (gameState == GAME) {
            // Sprawdü, czy gracz moøe wystrzeliÊ pocisk
            if (player.canShoot()) {
                pociski.push_back(player.shoot());
            }

          
            // Ruch gracza
            player.ruch();

			
            for (auto& pocisk : pociski) {
                pocisk.przesun();
            }
            // Aktualizuj wynik i øycie 
            interfejs.updateScore();

            window.clear();
            // Narysuj kazdy pocisk
            for (const auto& p : pociski) {
                window.draw(p.getPocisk());
            }
            // Narysuj gracza
            window.draw(player.getSprite());
            // Narysuj przeciwnikÛw
            if (przeciwnik0 != nullptr) {
                przeciwnik0->ruch();
                przeciwnik0->draw(window);
            }
            else {
                std::cerr << "przeciwnik0 is nullptr!" << std::endl;
            }
			if (przeciwnik1 != nullptr) {
				przeciwnik1->ruch();
				przeciwnik1->draw(window);
			}
			else {
				std::cerr << "przeciwnik1 is nullptr!" << std::endl;
			}
			if (przeciwnik2 != nullptr) { 
				przeciwnik2->ruch();
				przeciwnik2->draw(window);
			}
			else {
				std::cerr << "przeciwnik2 is nullptr!" << std::endl;
			}
			if (przeciwnik3 != nullptr) {
				przeciwnik3->ruch();
				przeciwnik3->draw(window);
			}
			else {
				std::cerr << "przeciwnik3 is nullptr!" << std::endl;
			}
			if (przeciwnik4 != nullptr) {
				przeciwnik4->ruch();
				przeciwnik4->draw(window);
			}
			else {
				std::cerr << "przeciwnik4 is nullptr!" << std::endl;
			}
			if (przeciwnik5 != nullptr) {
				przeciwnik5->ruch();
				przeciwnik5->draw(window);
			}
			else {
				std::cerr << "przeciwnik5 is nullptr!" << std::endl;
			}

                    
                          
			
            // Narysuj interfejs
            interfejs.draw(window);

            // Sprawdü, czy gracz ma jeszcze øycie
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

    // Zwolnij pamiÍÊ
    delete przeciwnik0;
	delete przeciwnik1;
	delete przeciwnik2;
	delete przeciwnik3;
	delete przeciwnik4;
	delete przeciwnik5;

    return 0;
}

