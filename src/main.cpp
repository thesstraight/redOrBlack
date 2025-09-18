#include <iostream>
#include <string_view>

#include "random.h"

namespace enums
{
    enum class colors
    {
        NONE,
        RED,
        BLACK,
    };
}

constexpr std::string_view getColorName(const enums::colors& color)
{
    switch (color)
    {
        case enums::colors::BLACK:
            return "Black";
            
        case enums::colors::RED:
            return "Red";

        default:
            return "None";
    }
}

std::istream& operator>>(std::istream& istream, enums::colors& color)
{
    int var;
    istream >> var;

    color = static_cast<enums::colors>(var);

    return istream;
}

std::ostream& operator<<(std::ostream& ostream, const enums::colors& color)
{
    ostream << ::getColorName(color);;

    return ostream;
}

int main()
{
    float money{ 200.f };
    float bet{ 10.f };

    enums::colors pickedColor{};

    bool gameInProgress{ true };
    do
    {
        if (money == 0.f)
        {
            std::cout << "Out of money!\n";

            return 0;
        }

        std::cout << "\nMoney " << money << '\n';
        std::cout << "Bet " << bet << '\n';
        std::cout << "Red or black (1 or 2)\n\n";

        std::cout << "Enter bet ";
        std::cin >> bet;
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }

        if (bet == 0.f)
        {
            std::cerr << "Invalid bet!\n";

            continue;
        }

        if (bet > money)
        {
            std::cout << "Please lower your bet!\n";

            continue;
        }

        std::cout << "Enter color ";
        std::cin >> pickedColor;
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }

        if (pickedColor != enums::colors::RED && pickedColor != enums::colors::BLACK)
        {
            std::cerr << "Invalid color!\n";

            continue;
        }

        money -= bet;

        const enums::colors randomColor{ static_cast<const enums::colors>(Random::get(1, 2)) };

        std::cout << "-----\nYou picked " << pickedColor << '\n';
        std::cout << "Color generated " << randomColor << '\n';

        if (pickedColor == randomColor)
        {
            std::cout << "-----\nYou win!\n";
            money += bet * 1.98f;
        }
        else
        {
            std::cout << "-----\nYou lose!\n";
        }

    } while (gameInProgress);

    return 0;
}