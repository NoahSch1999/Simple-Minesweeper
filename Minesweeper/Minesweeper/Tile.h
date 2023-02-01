#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include <Windows.h>

// Class containing everything a tile needs
class Tile
{
private:
	sf::RectangleShape shape;
	sf::Text text;				// Text showing the num mines surrounding the tile
	bool isMine = false;		// Whether the tile is a mine or not
	bool isShown = false;		// Whether the tile is shown/opened or not
	bool isFlagged = false;		// Whether the tile is flagged or not
	int numMines = 0;			// Num mines surrounding the tile
	int xIndex = -1;			// X index of the tile hit within the Board 2D vector
	int yIndex = -1;			// Y index of the tile hit within the Board 2D vector

public:

	Tile() = default;

	Tile(const sf::Vector2f& _dimensions, const sf::Vector2f& _position, const sf::Font& _font, int _xIndex, int _yIndex, int _charSize)
		:xIndex(_xIndex), yIndex(_yIndex)
	{
		shape.setSize(_dimensions);
		shape.setPosition(_position);
		shape.setFillColor(sf::Color(175, 175, 175));

		text.setString("");
		text.setFont(_font);
		text.setCharacterSize(_charSize);
		text.setPosition(_position.x + 15, _position.y + 5);
		text.setFillColor(sf::Color::Black);
	}

	// Show/hide the tile, which changes the color and text of the tile accordingly
	void SetShown(bool _show)
	{
		if (_show)
		{
			if (!isMine)
			{
				shape.setFillColor(sf::Color::White);
				if (numMines != 0)
				{
					text.setString(std::to_string(numMines));
				}
			}
			else
			{
				shape.setFillColor(sf::Color(150, 0, 0));
				text.setString("");
			}
		}
		else
		{
			shape.setFillColor(sf::Color::Green);
			text.setString("");
		}

		isShown = _show;
	}

	// Some get and set methods
	void SetFlagged(bool _flagged) { isFlagged = _flagged; }
	bool GetFlagged() { return isFlagged; }

	bool IsShown() { return isShown; }

	void SetIsMine(bool _isMine) { isMine = _isMine; }
	bool IsMine() { return isMine; }

	void SetNumMines(int _numMines) { numMines = _numMines; }
	int NumMines() { return numMines; }

	const sf::Vector2i GetBoardIndices() const { return sf::Vector2i(xIndex, yIndex); }

	sf::RectangleShape& GetShape() { return shape; }
	sf::Text& GetText() { return text; }
};