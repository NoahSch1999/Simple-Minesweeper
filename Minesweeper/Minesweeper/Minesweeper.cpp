#include "FlagManager.h"

int main()
{
    FreeConsole();

    // Initializes the window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Minesweeper");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    // Used to control the gamestate
    bool gameOver = false;

    // Loads font from file (first if-statement fails if you run from VS)
    sf::Font font;
    if (!font.loadFromFile("8BitFontBold.ttf"))
    {
        font.loadFromFile("../8BitFontBold.ttf");
    }

    // Initializes the board and flag manager
    Board board(sf::Vector2f(200, 200), 400, 7, font);
    FlagManager fManager;

    // Start of the game-loop
    while (window.isOpen())
    {
        // Checks for user input
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed())
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left && !gameOver)
                {
                    gameOver = board.HandleTileHit(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                    for (int i = 0; i < board.tiles.size(); i++)
                    {
                        for (int j = 0; j < board.tiles[i].size(); j++)
                        {
                            if (board.tiles[i][j].IsShown())
                            {
                                fManager.RemoveFlag(&board.tiles[i][j]);
                            }
                        }
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right && !gameOver)
                {
                    fManager.Update(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), board);
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Key::Space && gameOver)
                {
                    gameOver = false;
                    board = Board(sf::Vector2f(200, 200), 400, 7, font);
                    fManager = FlagManager();
                }
            }
        }

        // Updates timer text as long as the user hasn't lost
        if(!gameOver)
            board.HandleTimer();

        // Clear, draw, and display
		window.clear();
		board.DrawTiles(window);
        fManager.DrawFlags(window);
        board.DrawTextInfo(window);
		window.display();
    }
}
