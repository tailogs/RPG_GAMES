#ifndef PERLIN_NOISE_HPP
#define PERLIN_NOISE_HPP

class PerlinNoise
{
public:
    // Статическая функция для генерации шума Перлина
    static float perlinNoise(float x, float y);

private:
    // Статическая функция для линейной интерполяции
    static float lerp(float a, float b, float t);

    // Статическая функция для вычисления градиентного вектора
    static float grad(int hash, float x, float y);

    // Запрещаем создание и уничтожение экземпляров этого класса
    PerlinNoise() = delete;
    ~PerlinNoise() = delete;
};

#endif // PERLIN_NOISE_HPP
