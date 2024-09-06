#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <utility>

class Player {
public:
    // Конструктор
    Player(const std::string& textureFileName);

    // Геттеры
    float getCurrentStamina() const;
    float getMaxStamina() const;
    float getRunStaminaDrainRate() const;
    float getStepStaminaDrainRate() const;
    float getNormalRecoveryRate() const;
    float getFastRecoveryRate() const;
    float getPositionX() const; // Получение координаты X
    float getPositionY() const; // Получение координаты Y
    const sf::Vector2f& getPosition() const;
    const sf::Sprite& getSprite() const;
    float getWalkSpeed() const;
    float getRunSpeed() const;
    float getCurrentSpeed() const;

    // Сеттеры
    void setCurrentStamina(float stamina);
    void setPosition(float x, float y);
    void setPositionVector(const sf::Vector2f& newPosition);
    void setWalkSpeed(float walkSpeed);
    void setRunSpeed(float runSpeed);
    void setCurrentSpeed(float speed);
    void setPositionX(float x); // Сеттер для координаты X
    void setPositionY(float y); // Сеттер для координаты Y

    // Методы для обновления состояния
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;

    // Дополнительные методы для работы с временем
    float getElapsedTime(); // Получение времени с последнего сброса
    void restartClock(); // Сброс часов

private:
    // Переменные состояния игрока
    float currentStamina;
    const float maxStamina;
    const float runStaminaDrainRate;
    const float stepStaminaDrainRate;
    const float normalRecoveryRate;
    const float fastRecoveryRate;
    float walkSpeed = 5.0f;
    float runSpeed = walkSpeed * 2.0f;
    float currentSpeed = 5.0f;

    // Позиция и спрайт игрока
    sf::Vector2f position;
    sf::Sprite sprite;
    sf::Texture texture;

    // Часы для отслеживания времени
    sf::Clock staminaClock;

    // Метод для восстановления выносливости
    void recoverStamina(float deltaTime);
};

#endif // PLAYER_HPP
