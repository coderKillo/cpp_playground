#include <iostream>
#include <chrono>
#include <thread>
#include <cstdint>
#include <string>

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

std::ostream& operator<<(std::ostream& stream, const Tile& tile)
{
    std::string out(7, '-');
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
    std::string spaces()
    {
        return std::string(7, '-');
    }
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
        drawLine('+');
        for(int i = 0 ; i < MAX_HEIGHT ; ++i)
        {
            drawLine('|');   
            drawTileLine(i);
            drawLine('|');   
            drawLine('+');
        }
    }    
    bool Running()
    {
        static int i = 0;
        ++i;
        if(i > 3) return false;
        draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        return true;
    }

private:
    Tile m_tileMap[MAX_WIDTH][MAX_HEIGHT];
};

int main(int argc, char const *argv[])
{
    G2048 game;
    while(game.Running())
    {
    }
    return 0;
}
