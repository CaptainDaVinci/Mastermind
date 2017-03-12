#include <iostream>
#include <string>
#include <vector>

#define RED "\x1b[31;1m"
#define GREEN "\x1b[32;1m"
#define YELLOW "\x1b[33;1m"
#define BLUE "\x1b[34;1m"
#define MAGENTA "\x1b[35;1m"
#define CYAN "\x1b[36;1m"
#define WHITE "\x1b[37;1m"
#define RESET "\x1b[0m"
#define BLANK "\x1b[30m"

void printCode(const std::string &code);
bool isMatching(const std::string &code, std::string &userCode);
void showMoves(std::vector<std::string> &prevMoves);
void readCode(std::string &code);

const unsigned int PEGS = 4;

int main()
{
    unsigned int maxTurns, maxGames, p1score, p2score;

    do
    {
        std::cout << "Number of games (even number): ";
        std::cin >> maxGames;
    } while (maxGames % 2 != 0 || maxGames < 0);

    do
    {
        std::cout << "Number of turns (even number): ";
        std::cin >> maxTurns;
    } while (maxTurns % 2 != 0 || maxTurns < 0);

    for (int game = 0; game != maxGames; ++game)
    {
        bool won = false;
        int score = 0;
        std::string code;
        std::vector<std::string> prevMoves;

        std::cout << "New Game, Set ";
        readCode(code);

        for (int turn = 1; turn != maxTurns + 1; ++turn)
        {
            std::cout << "Turn: " << turn << " / "
                      << maxTurns << "\n";

            std::string userCode;
            readCode(userCode);
            score++;

            if (isMatching(code, userCode))
            {
                won = true;
                std::cout << WHITE << "Code successfully broken!\n";
                printCode(code);
                break;
            }

            prevMoves.push_back(userCode);
            showMoves(prevMoves);
        }

        if (!won)
        {
            std::cout << "Oops! You were unable"
                      << " to crack the code\n";
            printCode(code);
        }

        if (score == maxTurns)
            score++;

        if (game % 2 != 0)
        {
            p1score = score;
            std::cout << "Player 1: " << p1score << "\n\n";
        }

        else
        {
            p2score = score;
            std::cout << "Player 2: " << p2score << "\n\n";
        }
    }

    std::cout << "Player 1: " << p1score << '\n'
              << "Player 2: " << p2score << '\n';
    return 0;
}

inline void showMoves(std::vector<std::string> &prevMoves)
{
    for (std::vector<std::string>::const_iterator i = prevMoves.begin();
         i != prevMoves.end(); ++i)
        printCode(*i);
}

void readCode(std::string &code)
{
    do
    {
        std::cout << "Code: ";
        std::cin >> code;
    } while (code.size() != PEGS);

    system("clear");
}

void printCode(std::string const &code)
{
    std::string::size_type i = 0;

    while (i != code.size())
    {
        switch (code[i++])
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

bool isMatching(const std::string &code, std::string &userCode)
{
    std::vector<bool> seenCode(4, false);
    std::vector<bool> seenUserCode(seenCode);
    std::string keyPegs;
    std::string::size_type i, j;

    for (i = 0; i != PEGS; ++i)
    {
        if (code[i] == userCode[i])
        {
            keyPegs += 'P';
            seenCode[i] = seenUserCode[i] = true;
        }
    }

    for (i = 0; i != PEGS; ++i)
    {
        if (!seenCode[i])
        {
            for (j = 0; j != PEGS; ++j)
            {
                if (!seenUserCode[j] && code[i] == userCode[j])
                {
                    seenUserCode[j] = true;
                    keyPegs += 'O';
                    break;
                }
            }
        }
    }

    userCode += keyPegs;

    if (keyPegs != "PPPP")
        return false;

    return true;
}