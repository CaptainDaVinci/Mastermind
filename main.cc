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
#define esc "\x13";
void printCode(const std::string &code);
bool isMatching(const std::string &code, std::string &userCode);
inline void showMoves(std::vector<std::string> &prevMoves);
void readCode(std::string &code);
void setup(unsigned int &maxGames, unsigned int &maxGuess);

const unsigned int PEGS = 4;

int main()
{
    unsigned int maxGuess, maxGames, p1score(0), p2score(0);
    setup(maxGames, maxGuess);

    for (int game = 0; game != maxGames; ++game)
    {
        bool won = false;
        int score = 0;
        std::string secretCode;
        //keeps track of all the previous moves and feedback.
        std::vector<std::string> prevMoves;

        std::cout << "New Game\nSet secret code: ";
        readCode(secretCode);

        for (int guess = 0; guess != maxGuess; ++guess)
        {
            std::cout << "Remaining guesses: " 
                      << maxGuess - guess << "\n";

            std::string userCode;
            std::cout << "Code: ";
            readCode(userCode);

            if (isMatching(secretCode, userCode))
            {
                won = true;
                std::cout << WHITE << "Code successfully broken!\n";
                printCode(secretCode);
                break;
            }
            score++;

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

        if (score == maxGuess + 1)
            score++;

        // if current game is an even number then update
        // player 1's score.
        if (game % 2 != 0)
        {
            p1score += score;
            std::cout << "Player 1: " << p1score << "\n\n";
        }

        else
        {
            p2score += score;
            std::cout << "Player 2: " << p2score << "\n\n";
        }
    }

    std::cout << "\n\nPlayer 1: " << p1score << '\n'
              << "Player 2: " << p2score << '\n';
    return 0;
}

void setup(unsigned int &maxGames, unsigned int &maxGuess)
{
    std::cout << "Max Games: ";
    std::cin >> maxGames;
    std::cout << "Max turns: ";
    std::cin >> maxGuess;

    try
    {
        if(maxGames % 2 != 0 || maxGuess % 2 != 0)
            throw std::range_error("Invalid number!");
        
        if(maxGames > 12 || maxGuess > 12)
            throw std::overflow_error("Number too high!");
    }

    catch(std::range_error err)
    {
        std::cout << err.what()
                  << "\nNumber should be even!\n"
                  << "Try again\n\n";
                  
        setup(maxGames, maxGuess);
    }

    catch(std::overflow_error err)
    {
        std::cout << err.what()
                  << "\nNumber should be less than 13\n"
                  << "Try again\n\n";

        setup(maxGames, maxGuess);
    }
}
inline void showMoves(std::vector<std::string> &prevMoves)
{
    for (std::vector<std::string>::const_iterator i = prevMoves.begin();
         i != prevMoves.end(); ++i)
        printCode(*i);
}

void readCode(std::string &code)
{
    std::cin >> code;
    try
    {
        if(code.size() != PEGS)
            throw std::length_error("Invalid number of characters!");
        
        for(std::string::size_type i = 0; i != PEGS; ++i)
            if(code[i] != 'R' && code[i] != 'G' && code[i] != 'B' &&
               code[i] != 'Y' &&code[i] != 'M' && code[i] != 'C' && code[i] != '-')
               throw std::range_error("Invalid colours!");
    }

    catch(std::length_error err)
    {
        std::cout << "\n\n" << err.what() << '\n'
                  << "Permitted characters " << PEGS
                  << "\nTry again: ";
        
        readCode(code);
    }

    catch(std::range_error err)
    {
        std::cout << "\n\n" << err.what() << '\n'
                   << "Permitted colours: "
                   << "R G B Y M C -\n"
                   << "Try again: ";
        
        readCode(code);
    }
    system("clear");
    return ;
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

bool isMatching(const std::string &secretCode, std::string &userCode)
{
    // keeps track of the duplicates, so that feedback
    // is not provided twice for a single colour.
    std::vector<bool> seenCode(4, false);
    std::vector<bool> seenUserCode(seenCode);

    std::string feedback;
    std::string::size_type i, j;

    // for each character in the userCode, update the feedback
    // with the character 'P' if they match both in colour
    // and position with the code. 
    for (i = 0; i != PEGS; ++i)
    {
        if (secretCode[i] == userCode[i])
        {
            feedback += 'P';
            seenCode[i] = seenUserCode[i] = true;
        }
    }

    // for each character in the userCode, update the feedback
    // with the character 'O' if they match in color but not in
    // position.
    for (i = 0; i != PEGS; ++i)
    {
        if (!seenCode[i])
        {
            for (j = 0; j != PEGS; ++j)
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