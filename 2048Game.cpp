#include <iostream>
#include <chrono>
#include <thread>
#include <cstdint>
#include <string>
#include <random>
#include <ctime>
#include <vector>

//#define DEBUG

constexpr uint8_t MAX_WIDTH = 4;
constexpr uint8_t MAX_HEIGHT = 4;


void clrscr()
{
    std::cout << "\033[2J\033[1;1H";
}

struct Point
{
    Point(int px, int py):x(px),y(py){}
    Point(int pos):x(pos / MAX_WIDTH), y(pos % MAX_WIDTH){}
    friend std::ostream& operator<<(std::ostream& ostr, const Point& p)
    {
        ostr << "x: " << p.x << "y: " << p.y;
        return ostr;
    }
    int x;
    int y;
};

struct Tile
{
    int value = 0;
};

class TileMap
{
public:
    Tile& get(int x, int y){return m_TileMap[x][y];}
    Tile& get(const Point& p){return m_TileMap[p.x][p.y];}

private:
    Tile m_TileMap[MAX_WIDTH][MAX_HEIGHT];
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
            std::cout << m_tileMap.get(i, line);
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
        std::cout << "Keys: ^(W) <(A) V(S) >(D) quit(E)";
    #ifdef DEBUG
        std::cout << "\n##########\n DEBUG CONSOLE:\n";
        std::cout << "last move: " << static_cast<int>(m_moveDir) << std::endl;
        std::cout << "##########\n";
    #endif // DEBUG
    }    
    void addTile()
    {
        std::vector<int> vec;
        vec.reserve(MAX_WIDTH * MAX_HEIGHT);
        for (int i = 0; i < MAX_WIDTH; i++)
            for (int j = 0; j < MAX_HEIGHT; j++)
                if(m_tileMap.get(i, j).value == 0)
                    vec.push_back(i*MAX_WIDTH + j);
        vec.shrink_to_fit();
        
        if(vec.empty())
        {
            m_gameover = true;
            return;
        }
        
        int rnd = rand();
        int value = ((rnd % 2) != 0) ? 2 : 4;
        int pos = vec[rnd % vec.size()];
        std::cout << Point(pos) << std::endl;
        m_tileMap.get(Point(pos)).value = value;
    }

    void moveTile(Tile& from, Tile& to)
    {
        if(from.value != to.value && to.value != 0)
            return;
        if(from.value == to.value) 
            m_score += from.value;
        to.value += from.value;
        from.value = 0;
    }

    void move()
    {
        switch(m_moveDir)
        {
        case Direction::UP:
            for (int i = 0; i < MAX_WIDTH; ++i)
                for(int j = MAX_HEIGHT - 1; j > 0; --j)
                    moveTile(m_tileMap.get(i, j), m_tileMap.get(i, j-1));
            break;
        case Direction::DOWN:
            for (int i = 0; i < MAX_WIDTH; ++i)
                for(int j = 0; j < MAX_HEIGHT - 1; ++j)
                    moveTile(m_tileMap.get(i, j), m_tileMap.get(i, j+1));
            break;
        case Direction::RIGHT:
            for (int j = 0; j < MAX_HEIGHT; ++j)
                for(int i = 0; i < MAX_WIDTH - 1; ++i)
                    moveTile(m_tileMap.get(i, j), m_tileMap.get(i+1, j));
            break;
        case Direction::LEFT:
            for (int j = 0; j < MAX_HEIGHT; ++j)
                for(int i = MAX_WIDTH - 1; i > 0; --i)
                    moveTile(m_tileMap.get(i, j), m_tileMap.get(i-1, j));
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
        if(in == 'd')
            m_moveDir = Direction::RIGHT;
        if(in == 'a')
            m_moveDir = Direction::LEFT;
    }

    bool Running()
    {
        addTile();
        draw();
        waitForInput();
        move();
        return !m_gameover;
    }

private:

    TileMap m_tileMap;
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
    std::cout << "You Lose!" << std::endl;
    return 0;
}
