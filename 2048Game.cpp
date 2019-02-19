#include <iostream>
#include <chrono>
#include <thread>
#include <cstdint>
#include <string>
#include <random>
#include <ctime>

#define DEBUG

constexpr uint8_t MAX_WIDTH = 4;
constexpr uint8_t MAX_HEIGHT = 4;


void clrscr()
{
    std::cout << "\033[2J\033[1;1H";
}


struct Tile
{
    int value = 0;
};

enum class Direction:int
{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

std::string spaces()
{
    return std::string(7, '-');
}

std::ostream& operator<<(std::ostream& stream, const Tile& tile)
{
    std::string out = spaces();
    if(tile.value != 0)
    {
        std::string value = std::to_string(tile.value);
        out.replace(out.end() - value.size() - 1, out.end() - 1 ,value.c_str());
    }
    stream << out;
    return stream;
}

class G2048
{
public:

    void drawLine(char seperator)
    {
        std::cout << seperator;
        for(int i = 0 ; i < MAX_WIDTH; ++i)
        {
            std::cout << spaces(); 
            std::cout << seperator;
        }
        std::cout << "\n";
    }

    void drawTileLine(int line)
    {
        std::cout << "|";
        for(int i = 0 ; i < MAX_WIDTH; ++i)
        {
            std::cout << m_tileMap[i][line];
            std::cout << "|";
        }
        std::cout << "\n";
    }
    void draw()
    {
        clrscr();
        std::cout << "GAME 2048\n";
        std::cout << "Score: " << m_score << "\n";
        drawLine('+');
        for(int i = 0 ; i < MAX_HEIGHT ; ++i)
        {
            drawLine('|');   
            drawTileLine(i);
            drawLine('|');   
            drawLine('+');
        }
    }    
    void addTile()
    {
        m_tileMap[0][3].value = 2;
    }

    bool moveTile(Tile& from, Tile& to)
    {
        if(from.value == 0)
            return false;
        if(from.value != to.value && to.value != 0)
            return false;
        
        to.value += from.value;
        from.value = 0;
        return true;
    }

    void move()
    {
        switch(m_moveDir)
        {
        case Direction::UP:
            for (int i = 0; i < MAX_WIDTH; ++i)
                for(int j = MAX_HEIGHT - 1; j >= 0; --j)
                    moveTile(m_tileMap[i][j],m_tileMap[i][j - 1]);
            break;
        case Direction::DOWN:

            break;
        case Direction::RIGHT:

            break;
        case Direction::LEFT:

            break;
        
        default:
            break;
        }
    }

    void waitForInput()
    {
        char in;
        std::cin >> in;

        if(in == 'e')
            m_gameover = true;
        if(in == 'w')
            m_moveDir = Direction::UP;
        if(in == 's')
            m_moveDir = Direction::DOWN;
        if(in == 'a')
            m_moveDir = Direction::RIGHT;
        if(in == 'd')
            m_moveDir = Direction::LEFT;
    }

    bool Running()
    {
        addTile();
        draw();
        waitForInput();
        move();

    #ifdef DEBUG
        std::cout << "\n##########\n DEBUG CONSOLE:\n";
        std::cout << "random Number:" << static_cast<float>(rand()) << std::endl;
        std::cout << "last move: " << static_cast<int>(m_moveDir) << std::endl;
        std::cout << "##########\n";
    #endif // DEBUG

        return !m_gameover;
    }

private:

    Tile m_tileMap[MAX_WIDTH][MAX_HEIGHT];
    int m_score = 0;
    bool m_gameover = false;
    Direction m_moveDir = Direction::NONE;
};

int main(int argc, char const *argv[])
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    G2048 game;
    while(game.Running())
    {
    }
    return 0;
}
