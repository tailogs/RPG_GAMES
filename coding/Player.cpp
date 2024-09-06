#include <iostream>
#include "Player.hpp"
#include "my_resource.hpp"

// Конструктор
Player::Player(const std::string& textureFileName)
    : currentStamina(100.0f),
      maxStamina(100.0f),
      runStaminaDrainRate(10.0f),
      stepStaminaDrainRate(2.0f),
      normalRecoveryRate(2.0f),
      fastRecoveryRate(normalRecoveryRate * 10.0f),
      position(960.0f, 540.0f) {

    if (!texture.loadFromFile(getResource(textureFileName, "img"))) {
        std::cerr << "Ошибка загрузки текстуры из файла: " << textureFileName << std::endl;
        // Вы можете обработать ошибку более надежным способом
    } else {
        sprite.setTexture(texture);
        sprite.setPosition(position); // Установите позицию спрайта при создании
    }
}

// Геттеры
float Player::getCurrentStamina() const {
    return currentStamina;
}

float Player::getCurrentSpeed() const {
    return currentSpeed;
}

float Player::getMaxStamina() const {
    return maxStamina;
}

float Player::getRunStaminaDrainRate() const {
    return runStaminaDrainRate;
}

float Player::getStepStaminaDrainRate() const {
    return stepStaminaDrainRate;
}

float Player::getNormalRecoveryRate() const {
    return normalRecoveryRate;
}

float Player::getFastRecoveryRate() const {
    return fastRecoveryRate;
}

float Player::getPositionX() const {
    return position.x;
}

float Player::getPositionY() const {
    return position.y;
}

const sf::Vector2f& Player::getPosition() const {
    return position;
}

const sf::Sprite& Player::getSprite() const {
    return sprite;
}

float Player::getWalkSpeed() const {
    return walkSpeed;
}

float Player::getRunSpeed() const {
    return runSpeed;
}

// Сеттеры
void Player::setCurrentStamina(float stamina) {
    currentStamina = std::clamp(stamina, 0.0f, maxStamina);
}

void Player::setPosition(float x, float y) {
    position = sf::Vector2f(x, y);
    sprite.setPosition(position); // Обновите позицию спрайта
}

void Player::setWalkSpeed(float walkSpeed) {
    this->walkSpeed = walkSpeed;
}

void Player::setRunSpeed(float runSpeed) {
    this->runSpeed = runSpeed;
}

void Player::setCurrentSpeed(float speed) {
    currentSpeed = speed;
}

void Player::setPositionX(float x) {
    position.x = x;
    sprite.setPosition(position); // Обновите позицию спрайта
}

// Сеттер для координаты Y
void Player::setPositionY(float y) {
    position.y = y;
    sprite.setPosition(position); // Обновите позицию спрайта
}

void Player::setPositionVector(const sf::Vector2f& newPosition) {
    position = newPosition;
    sprite.setPosition(position); // Обновите позицию спрайта
}

// Обновление состояния игрока
void Player::update(float deltaTime) {
    // Пример обновления выносливости
    recoverStamina(deltaTime);
}

// Рисование игрока
void Player::draw(sf::RenderWindow& window) const {
    window.draw(sprite); // Рисуйте непосредственно спрайт, без дополнительного создания
}

// Восстановление выносливости
void Player::recoverStamina(float deltaTime) {
    if (currentStamina < maxStamina) {
        float recoveryRate = (getElapsedTime() > 1.0f) ? fastRecoveryRate : normalRecoveryRate;
        currentStamina = std::min(currentStamina + recoveryRate * deltaTime, maxStamina);
        restartClock();
    }
}

// Получение времени с последнего сброса
float Player::getElapsedTime() {
    return staminaClock.getElapsedTime().asSeconds();
}

// Сброс часов
void Player::restartClock() {
    staminaClock.restart();
}
