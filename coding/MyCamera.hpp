#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

class MyCamera {
public:
    // Конструктор с начальным размером вида
    MyCamera(float width, float height);

    // Установить скорость камеры
    void setSpeed(float speed);

    // Установить флаг следования за героем
    void setFollowHero(bool follow);

    // Обновить положение камеры с учетом времени
    void update(float deltaTime, const sf::Vector2f& heroPosition);

    // Переместить камеру на заданное смещение
    void move(float offsetX, float offsetY);

    // Установить центр камеры
    void setCenter(float x, float y);

    // Получить текущее представление камеры
    const sf::View& getView() const;

    bool getFollowHero() const;

    float getSpeed() const;

private:
    sf::View view;
    float speed; // Скорость перемещения камеры
    sf::Vector2f targetPosition; // Целевая позиция камеры
    sf::Vector2f currentPosition; // Текущая позиция камеры
    bool cameraFollowHero = true; // Флаг следования за героем
};

#endif // CAMERA_HPP
