#include <iostream>
#include <string>
#include <vector>
#include <cctype>

constexpr auto RED     = "\x1b[31;1m";
constexpr auto GREEN   = "\x1b[32;1m"; 
constexpr auto YELLOW  = "\x1b[33;1m"; 
constexpr auto BLUE    = "\x1b[34;1m"; 
constexpr auto MAGENTA = "\x1b[35;1m"; 
constexpr auto CYAN    = "\x1b[36;1m"; 
constexpr auto WHITE   = "\x1b[37;1m"; 
constexpr auto RESET   = "\x1b[0m";

constexpr auto CLEAR = "clear";

bool getFeedback(const std::string &code, std::string &userCode);
void setup(unsigned int &maxGames, unsigned int &maxGuess);
void showMoves(const std::vector<std::string> &prevMoves);
void printCode(const std::string &code);
std::string getCode(void);

const unsigned int pegs = 4;

int main()
{
    unsigned int maxGuess(0), maxGames(0), p1score(0), p2score(0);
    setup(maxGames, maxGuess);

    for (unsigned int game = 0; game < maxGames; ++game)
    {
        bool won = false;
        std::vector<std::string> prevMoves; //keeps track of all the previous moves and feedback.

        std::cout << "New Game\nSet secret code: ";
        std::string secretCode = getCode();

        for (unsigned int guess = 0; guess < maxGuess; ++guess)
        {
            std::cout << "Guesses remaining: "
                      << maxGuess - guess << "\n";

            std::cout << "Code: ";
            std::string userCode = getCode();

            if (getFeedback(secretCode, userCode))
            {
                won = true;
                std::cout << WHITE << "Code successfully broken!\n";
                printCode(secretCode);
                break;
            }

            // Update previous moves and display them.
            prevMoves.push_back(userCode);
            showMoves(prevMoves);
        }

        if (!won)
        {
            std::cout << "Oops! You were unable"
                      << " to crack the code\n";
            printCode(secretCode);
        }
    }
    return 0;
}

void setup(unsigned int &maxGames, unsigned int &maxGuess)
{

    while (true)
    {
        std::cout << "Max Games: ";
        std::cin >> maxGames;
        std::cout << "Max turns: ";
        std::cin >> maxGuess;

        try
        {
            if (maxGames % 2 != 0 || maxGuess % 2 != 0)
                throw std::range_error("Invalid number!");

            if (maxGames > 12 || maxGuess > 12)
                throw std::overflow_error("Number too high!");

            break;
        }

        catch (std::range_error err)
        {
            std::cout << err.what()
                      << "\nNumber should be even!\n"
                      << "Try again\n\n";
        }

        catch (std::overflow_error err)
        {
            std::cout << err.what()
                      << "\nNumber should be less than 13\n"
                      << "Try again\n\n";
        }
    }
}

void showMoves(const std::vector<std::string> &prevMoves)
{
    for (const auto &i : prevMoves)
        printCode(i);
}

std::string getCode(void)
{
    std::string code;   
    while (true)
    {
        std::cin >> code;
        try
        {
            if (code.size() != pegs)
                throw std::length_error("Invalid number of characters!");

            for (std::string::size_type i = 0; i != pegs; ++i)
            {
                code[i] = toupper(code[i]);\

                if (code[i] != 'R' && code[i] != 'G' && code[i] != 'B' &&
                    code[i] != 'Y' && code[i] != 'M' && code[i] != 'C' && code[i] != '-')
                    throw std::range_error("Invalid colours!");
            }

            break;
        }

        catch (std::length_error err)
        {
            std::cout << "\n"
                      << err.what() << '\n'
                      << "Permitted characters " << pegs
                      << "\nTry again: ";
        }

        catch (std::range_error err)
        {
            std::cout << "\n"
                      << err.what() << '\n'
                      << "Permitted colours: "
                      << "R G B Y M C -\n"
                      << "Try again: ";
        }
    }

    system(CLEAR);
    return code;
}

void printCode(const std::string &code)
{
    std::size_t i = 0;
    std::cout << '\t';

    while (i != code.size())
    {
        switch (toupper(code[i++]))
        {
        case 'R':
            std::cout << RED << "# ";
            break;
        case 'G':
            std::cout << GREEN << "# ";
            break;
        case 'Y':
            std::cout << YELLOW << "# ";
            break;
        case 'B':
            std::cout << BLUE << "# ";
            break;
        case 'M':
            std::cout << MAGENTA << "# ";
            break;
        case 'C':
            std::cout << CYAN << "# ";
            break;
        case 'P':
            std::cout << WHITE << " P";
            break;
        case 'O':
            std::cout << WHITE << " O";
            break;
        default:
            std::cout << "  ";
        }
    }

    std::cout << RESET << '\n';
}

bool getFeedback(const std::string &secretCode, std::string &userCode)
{
    // keeps track of the duplicates, so that feedback
    // is not provided twice for a single colour.
    std::vector<bool> seenSecretCode(4, false);
    std::vector<bool> seenUserCode(seenSecretCode);
    std::string feedback;

    // for each character in the userCode, update the feedback
    // with the character 'P' if they match both in colour
    // and position with the code.
    for (std::size_t i = 0; i != pegs; ++i)
    {
        if (secretCode[i] == userCode[i])
        {
            feedback += 'P';
            seenSecretCode[i] = seenUserCode[i] = true;
        }
    }

    // for each character in the userCode, update the feedback
    // with the character 'O' if they match in color but not in
    // position.
    for (std::size_t i = 0; i != pegs; ++i)
    {
        if (!seenSecretCode[i])
        {
            for (std::size_t j = 0; j != pegs; ++j)
            {
                if (!seenUserCode[j] && secretCode[i] == userCode[j])
                {
                    seenUserCode[j] = true;
                    feedback += 'O';
                    break;
                }
            }
        }
    }

    // concatenate the userCode with feedback.
    userCode += feedback;

    // if the userCode did not match the code.
    if (feedback != "PPPP")
        return false;

    return true;
}