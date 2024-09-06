#include "MyCamera.hpp"

// Конструктор с начальным размером вида
MyCamera::MyCamera(float width, float height)
    : speed(0.0f), targetPosition(width / 2, height / 2), currentPosition(width / 2, height / 2), cameraFollowHero(true) {
    view.setSize(width, height);
    view.setCenter(currentPosition);
}

// Установить скорость камеры
void MyCamera::setSpeed(float newSpeed) {
    speed = newSpeed;
}

// Установить флаг следования за героем
void MyCamera::setFollowHero(bool follow) {
    cameraFollowHero = follow;
}

bool MyCamera::getFollowHero() const {
    return cameraFollowHero;
}

float MyCamera::getSpeed() const {
    return speed;
}

// Обновить положение камеры с учетом времени
void MyCamera::update(float deltaTime, const sf::Vector2f& heroPosition) {
    if (cameraFollowHero) {
        // Если камера следует за героем, обновляем целевую позицию
        targetPosition = heroPosition;
    }

    // Рассчитываем перемещение камеры с учетом времени и скорости
    sf::Vector2f direction = targetPosition - currentPosition;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0) {
        direction /= distance; // Нормализуем вектор направления
        currentPosition += direction * speed * deltaTime; // Перемещаем камеру
        view.setCenter(currentPosition);
    }
}

// Переместить камеру на заданное смещение
void MyCamera::move(float offsetX, float offsetY) {
    targetPosition += sf::Vector2f(offsetX, offsetY);
}

// Установить центр камеры
void MyCamera::setCenter(float x, float y) {
    targetPosition = sf::Vector2f(x, y);
}

// Получить текущее представление камеры
const sf::View& MyCamera::getView() const {
    return view;
}
