#include "PerlinNoise.hpp"

// Линейная интерполяция
float PerlinNoise::lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

// Градиентный вектор
float PerlinNoise::grad(int hash, float x, float y)
{
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : (h == 12 || h == 14 ? x : 0);

    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

// Функция для генерации шума Перлина
float PerlinNoise::perlinNoise(float x, float y)
{
    int xi = static_cast<int>(x) & 255;
    int yi = static_cast<int>(y) & 255;
    float xf = x - static_cast<int>(x);
    float yf = y - static_cast<int>(y);

    float u = xf * xf * (3 - 2 * xf);
    float v = yf * yf * (3 - 2 * yf);

    int aa = (xi + yi) % 256;
    int bb = (aa + 1) % 256;
    int ab = (aa + 1) % 256;
    int ba = (bb + 1) % 256;

    float x1 = lerp(grad(aa, xf, yf), grad(bb, xf - 1, yf), u);
    float x2 = lerp(grad(ab, xf, yf - 1), grad(ba, xf - 1, yf - 1), u);

    return (lerp(x1, x2, v) + 1.0f) / 2.0f;
}
