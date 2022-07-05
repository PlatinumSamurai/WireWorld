#include <iostream>
#include <SFML/Graphics.hpp>

#include "field.hpp"


const int WIDTH = 1920;
const int HEIGHT = 1080;
const int SQUARES_HORIZONTAL = 128;
const int SQUARES_VERTICAL = 69;
const int SQUARE_SIZE = 14;
const int BUTTON_OFFSET = 600;

const sf::Color HEAD_COLOR = sf::Color::Blue;
const sf::Color TAIL_COLOR = sf::Color::Red;
const sf::Color EMPTY_COLOR = sf::Color(35, 35, 35);
const sf::Color CONDUCTOR_COLOR = sf::Color::Yellow;


int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "WireWorld");
    window.setFramerateLimit(60);

    Field field(SQUARES_HORIZONTAL, SQUARES_VERTICAL, SQUARE_SIZE, EMPTY_COLOR);

    bool isPlay = false;
    sf::Clock timer;
    sf::Texture play;
    sf::Texture pause;
    sf::Texture restart;
    sf::Texture faster;
    sf::Texture slower;
    sf::Sprite playPauseSprite;
    sf::Sprite restartSprite;
    sf::Sprite fasterSprite;
    sf::Sprite slowerSprite;
    float deltaTime = 0.15;
    sf::Color activeColor = CONDUCTOR_COLOR;


    play.loadFromFile("src\\play.png");
    pause.loadFromFile("src\\pause.png");
    restart.loadFromFile("src\\restart.png");
    faster.loadFromFile("src\\faster.png");
    slower.loadFromFile("src\\slower.png");

    playPauseSprite.setTexture(play);
    playPauseSprite.setScale(0.35, 0.35);
    playPauseSprite.setPosition(BUTTON_OFFSET, HEIGHT - SQUARE_SIZE * 3);
    restartSprite.setTexture(restart);
    restartSprite.setScale(0.35, 0.35);
    restartSprite.setPosition(playPauseSprite.getPosition().x + playPauseSprite.getGlobalBounds().width + 20,
                              HEIGHT - SQUARE_SIZE * 3);

    fasterSprite.setTexture(faster);
    fasterSprite.setScale(0.35, 0.35);
    fasterSprite.setPosition(WIDTH - BUTTON_OFFSET - fasterSprite.getGlobalBounds().width,
                             HEIGHT - SQUARE_SIZE * 3);
    slowerSprite.setTexture(slower);
    slowerSprite.setScale(0.35, 0.35);
    slowerSprite.setPosition(fasterSprite.getPosition().x - fasterSprite.getGlobalBounds().width - 20,
                             HEIGHT - SQUARE_SIZE * 3);


    while(window.isOpen()) {
        sf::Event event{};
        while(window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::KeyPressed:
                    switch(event.key.code) {
                        case sf::Keyboard::E:
                            std::cout << "I go home by button E" << std::endl;
                            window.close();

                            break;

                        case sf::Keyboard::Escape:
                            std::cout << "I go home by button Esc" << std::endl;
                            window.close();

                            break;

                        case sf::Keyboard::Space:
                            if(!isPlay) {
                                isPlay = !isPlay;
                                playPauseSprite.setTexture(pause);
                            } else {
                                isPlay = !isPlay;
                                playPauseSprite.setTexture(play);
                            }
                            timer.restart();

                            break;

                        case sf::Keyboard::Num1:
                            activeColor = CONDUCTOR_COLOR;

                            break;

                        case sf::Keyboard::Num2:
                            activeColor = HEAD_COLOR;

                            break;

                        case sf::Keyboard::Num3:
                            activeColor = TAIL_COLOR;

                            break;

                        default:
                            break;
                    }

                    break;

                case sf::Event::MouseButtonPressed:
                    switch(event.mouseButton.button) {
                        case sf::Mouse::Left:
                            field.updateColors(activeColor, window);

                            if(playPauseSprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,
                                                                          sf::Mouse::getPosition(window).y)) {
                                if(!isPlay) {
                                    isPlay = !isPlay;
                                    playPauseSprite.setTexture(pause);
                                } else {
                                    isPlay = !isPlay;
                                    playPauseSprite.setTexture(play);
                                }
                            }
                            if(restartSprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,
                                                                        sf::Mouse::getPosition(window).y)) {
                                field.resetField(EMPTY_COLOR);
                            }

                            if(fasterSprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,
                                                                       sf::Mouse::getPosition(window).y)) {
                                if(deltaTime >= 2) {
                                    deltaTime -= 1;
                                } else if(deltaTime >= 1) {
                                    deltaTime -= 0.5;
                                } else if(deltaTime >= 0.7) {
                                    deltaTime -= 0.1;
                                } else if(deltaTime >= 0.5) {
                                    deltaTime -= 0.05;
                                } else if( deltaTime >= 0.03) {
                                    deltaTime -= 0.01;
                                }
                            }

                            if(slowerSprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,
                                                                       sf::Mouse::getPosition(window).y)) {
                                if(deltaTime <= 0.15) {
                                    deltaTime += 0.01;
                                } else if(deltaTime <= 0.5) {
                                    deltaTime += 0.05;
                                } else if(deltaTime <= 0.7) {
                                    deltaTime += 0.1;
                                } else if(deltaTime <= 1) {
                                    deltaTime += 0.5;
                                } else {
                                    deltaTime += 1;
                                }
                            }

                            break;

                        case sf::Mouse::Right:
                            field.updateColors(EMPTY_COLOR, window);

                            break;

                        default:
                            break;
                    }

                    break;

                default:
                    break;
            }
        }


        if(isPlay and timer.getElapsedTime() >= sf::seconds(deltaTime)) {
            timer.restart();
            field.updateCells(HEAD_COLOR, TAIL_COLOR, EMPTY_COLOR, CONDUCTOR_COLOR);
        }

        field.highlightMousePosition(HEAD_COLOR, TAIL_COLOR, EMPTY_COLOR, CONDUCTOR_COLOR, window);

        window.clear(sf::Color(150, 150, 255));

        for(const auto &item : field.getField()) {
            for(const auto &elem : item) {
                window.draw(elem);
            }
        }

        window.draw(playPauseSprite);
        window.draw(restartSprite);
        window.draw(fasterSprite);
        window.draw(slowerSprite);

        window.display();
    }

    return 0;
}