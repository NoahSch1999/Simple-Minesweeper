#pragma once
#include "Board.h"

// Contains necessary data for a flag object
class Flag
{
private:
    int xIndex = -1;    // Used to search for the flag when removing it
    int yIndex = -1;    // Used to search for the flag when removing it
    sf::Sprite sprite;

public:
    Flag() = default;
    Flag(const sf::Texture& _texture, const sf::Vector2f& _position, int _xIndex, int _yIndex)
        :xIndex(_xIndex), yIndex(_yIndex)
    {
        sprite.setTexture(_texture);
        sprite.setPosition(_position);
    }

    // Some get methods
    sf::Sprite& GetSprite() { return sprite; }
    const sf::Vector2i GetIndices() const { return sf::Vector2i(xIndex, yIndex); }
};

// Handles everything related to flags
class FlagManager
{
private:
    std::vector<Flag>flags; // Vector of flags that are placed
    sf::Texture flagTexture;
public:
    FlagManager()
    {
        if (!flagTexture.loadFromFile("flag.png"))
        {
            flagTexture.loadFromFile("../flag.png");
        }
    }

    // Checks tile clicking and adds/removes a flag from the tile if it isn't shown/opened
    void Update(const sf::Vector2f& _mousePosition, Board& _board)
    {
        Tile* hitTile = _board.GetTileClickInfo(_mousePosition.x, _mousePosition.y);
        if (hitTile != nullptr)
        {
            if (hitTile->GetFlagged())
            {
                RemoveFlag(hitTile);
            }
            else
            {
                AddFlag(hitTile);
            }
        }
    }

    // Draws all the flags
    void DrawFlags(sf::RenderWindow& _window)
    {
        for (Flag flag : flags)
        {
            _window.draw(flag.GetSprite());
        }
    }

    // Adds a flag to the flag-vector member variable
    void AddFlag(Tile* _tile)
    {
        flags.emplace_back(Flag(flagTexture, _tile->GetShape().getPosition(), _tile->GetBoardIndices().x, _tile->GetBoardIndices().y));
        _tile->SetFlagged(true);
    }

    // Searches for a flag with the same board indices as the input tile argument and removes it by overwriting it with the flag on the last index within the vector
    void RemoveFlag(Tile* _tile)
    {
        for (int i = 0; i < flags.size(); i++)
        {
            if (flags[i].GetIndices().x == _tile->GetBoardIndices().x && flags[i].GetIndices().y == _tile->GetBoardIndices().y)
            {
                flags[i] = flags[flags.size() - 1];
                flags.resize(flags.size() - 1);
                _tile->SetFlagged(false);
            }
        }
    }
};