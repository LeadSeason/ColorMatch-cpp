#include "raylib-cpp.hpp"
#include <array>
#include <climits>
#include <ctime>
#include <iostream>
#include <string>
#include <time.h>

// Catppuccin mocha color scheme
#define COLOR_ARRAY_SIZE 26
std::array<raylib::Color, COLOR_ARRAY_SIZE> colorList = {
    raylib::Color(245, 224, 220), // #f5e0dc
    raylib::Color(242, 205, 205), // #f2cdcd
    raylib::Color(245, 194, 231), // #f5c2e7
    raylib::Color(203, 166, 247), // #cba6f7
    raylib::Color(243, 139, 168), // #f38ba8
    raylib::Color(235, 160, 172), // #eba0ac
    raylib::Color(250, 179, 135), // #fab387
    raylib::Color(249, 226, 175), // #f9e2af
    raylib::Color(166, 227, 161), // #a6e3a1
    raylib::Color(148, 226, 213), // #94e2d5
    raylib::Color(137, 220, 235), // #89dceb
    raylib::Color(116, 199, 236), // #74c7ec
    raylib::Color(137, 180, 250), // #89b4fa
    raylib::Color(180, 190, 254), // #b4befe
    raylib::Color(205, 214, 244), // #cdd6f4
    raylib::Color(186, 194, 222), // #bac2de
    raylib::Color(166, 173, 200), // #a6adc8
    raylib::Color(147, 153, 178), // #9399b2
    raylib::Color(127, 132, 156), // #7f849c
    raylib::Color(108, 112, 134), // #6c7086
    raylib::Color(88, 91, 112),   // #585b70
    raylib::Color(69, 71, 90),    // #45475a
    raylib::Color(49, 50, 68),    // #313244
    raylib::Color(30, 30, 46),    // #1e1e2e
    raylib::Color(24, 24, 37),    // #181825
    raylib::Color(17, 17, 27)     // #11111b
};

int GetDistance(raylib::Color current, raylib::Color match)
{
    int rDiff = current.GetR() - match.GetR();
    int gDiff = current.GetG() - match.GetG();
    int bDiff = current.GetB() - match.GetB();

    return (rDiff * rDiff) + (gDiff * gDiff) + (bDiff * bDiff);
}

raylib::Color FindNearestColor(std::array<raylib::Color, COLOR_ARRAY_SIZE>& colorList,
                     raylib::Color current)
{
    int shortestDistance = INT_MAX;
	raylib::Color closestColor;

    for (raylib::Color color : colorList)
    {
        int distance = GetDistance(current, color);

        if (distance < shortestDistance)
        {
			closestColor = color;
            shortestDistance = distance;
        }
    }
    return closestColor;
}

raylib::Image ConvertImage(std::string imagePath)
{
    std::cout << imagePath << std::endl;
    raylib::Image burger(imagePath);
    int screenWidth = burger.GetWidth();
    int screenHeight = burger.GetHeight();
    // Make argument
    burger.ColorContrast(30);

    for (int x = 0; x < screenWidth - 1; x++)
        for (int y = 0; y < screenHeight - 1; y++)
        {
            // Todo: add dithering
            // Todo: Learn to use pointer,
            // 104 bytes is too much for me to handel. UwU
            raylib::Vector2 pixelPosition(x, y);
            raylib::Color pixelColor = burger.GetColor(pixelPosition);
            burger.DrawPixel(
                pixelPosition,
                FindNearestColor(colorList, pixelColor)
			);
        }
    return burger;
}

void ShowImage(raylib::Image burger)
{
    int screenWidth = burger.GetWidth();
    int screenHeight = burger.GetHeight();
    raylib::Window window(screenWidth, screenHeight, "Burger🍔👍");
    raylib::Texture logo = burger.LoadTexture();

    SetTargetFPS(60);
    while (!window.ShouldClose())
    {
        BeginDrawing();

        window.ClearBackground(RAYWHITE);

        logo.Draw(0, 0);

        EndDrawing();
    }
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::cout << "No Image specified, exiting ..." << std::endl;
        return 1;
    }

	raylib::Image img = ConvertImage(argv[1]);

	ShowImage(img);
	img.Export("frame-converted.png");

    // Todo: save to file
    // same nameking system as in python
    // --show argument to show image
    // --show only works with one image
    // export works with multiple
    // burger.Export("frame-converted.png");

    return 0;
}
