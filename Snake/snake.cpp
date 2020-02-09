/* Import */
#include <iostream>

#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library
#include <string.h> // String
#include "snake.hpp" // Snake

/* Declaration > ... --- NOTE (Lapys) -> Decided to keep the game logic here to keep things somewhat clean. */
bool AllowUserControlledSnake(void);
void ParseHighscores(void);
void SpawnFruits(void);
void SpawnSnake(void);
void SpawnTiles(void);

/* Functions */
    // Parse High Scores
    void ParseHighscores(void) {
        // Initialization > High Scores File Record
        FILE *highscoresFileRecord = ::fopen("highscores.txt", "r");

        // Logic
        if (highscoresFileRecord) {
            // Assertion > Continue Parsing
            bool continueParsing = true;

            // Loop
            for (
                char field[20] {0}, fieldLength = 0,
                    score[20] {0}, username[20] {0};
                continueParsing && (*(field + fieldLength) = ::fgetc(highscoresFileRecord)) != EOF;
            ) {
                // Constant > Character
                const char character = *(field + fieldLength++);

                // Logic
                if (character == '\b' || character == '\t' || character == ' ')
                    // Update > Field Length
                    fieldLength--;

                else if (character == '\n' || character == '\r' || character == '\v') {
                    // Logic
                    if (fieldLength) {
                        // Logic
                        if (*username) {
                            // Update > (High Scores, Score)
                            Game::Statistics::highscores = (Highscore*) (Game::Statistics::highscores ? std::realloc(Game::Statistics::highscores, (Game::Statistics::highscoreCount + 1u) * sizeof(Highscore)) : std::malloc(sizeof(Highscore)));

                            ::memcpy(&score, field, fieldLength * sizeof(char));
                            *(score + --fieldLength) = '\0';

                            // Modification > [High Score] > Score
                            (Game::Statistics::highscores + Game::Statistics::highscoreCount) -> score = 0u;

                            // Loop
                            for (std::size_t exponent = 1u; fieldLength--; exponent *= 10u) {
                                // Logic > ...
                                switch (*(score + fieldLength)) {
                                    // Modification > [High Score] > Score
                                    case '0': (Game::Statistics::highscores + Game::Statistics::highscoreCount) -> score += (exponent * 0u); break;
                                    case '1': (Game::Statistics::highscores + Game::Statistics::highscoreCount) -> score += (exponent * 1u); break;
                                    case '2': (Game::Statistics::highscores + Game::Statistics::highscoreCount) -> score += (exponent * 2u); break;
                                    case '3': (Game::Statistics::highscores + Game::Statistics::highscoreCount) -> score += (exponent * 3u); break;
                                    case '4': (Game::Statistics::highscores + Game::Statistics::highscoreCount) -> score += (exponent * 4u); break;
                                    case '5': (Game::Statistics::highscores + Game::Statistics::highscoreCount) -> score += (exponent * 5u); break;
                                    case '6': (Game::Statistics::highscores + Game::Statistics::highscoreCount) -> score += (exponent * 6u); break;
                                    case '7': (Game::Statistics::highscores + Game::Statistics::highscoreCount) -> score += (exponent * 7u); break;
                                    case '8': (Game::Statistics::highscores + Game::Statistics::highscoreCount) -> score += (exponent * 8u); break;
                                    case '9': (Game::Statistics::highscores + Game::Statistics::highscoreCount) -> score += (exponent * 9u); break;

                                    // Error
                                    default: continueParsing = false; fieldLength = 0; break;
                                }
                            }

                            // Logic
                            if (continueParsing) {
                                // Modification > [High Score] > Username
                                // : Update > Username
                                ::memcpy(&((Game::Statistics::highscores + Game::Statistics::highscoreCount++) -> username), username, 20u * sizeof(char));
                                *username = '\0';
                            }
                        }

                        else {
                            // Update > Username
                            ::memcpy(&username, field, fieldLength * sizeof(char));
                            *(username + --fieldLength) = '\0';
                        }

                        // Update > Field Length
                        fieldLength = 0;
                    }
                }

                else if (fieldLength == 21)
                    /* Terminate --- NOTE (Lapys) -> Silence the exception and terminate the parsing.
                            - Would recommend manually clearing the file at this point.
                    */
                    continueParsing = false;
            }

            // Logic
            if (!continueParsing) {
                // Update > High Scores
                std::free(Game::Statistics::highscores);
                Game::Statistics::highscores = (Highscore*) std::malloc(0u);
            }

            // Deletion
            ::fclose(highscoresFileRecord);
        }

        else
            // Update > High Scores
            Game::Statistics::highscores = (Highscore*) std::malloc(0u);
    }

    // Spawn Fruits
    void SpawnFruits(void) {
        // Initialization > (High Score, Occupied Tile ...)
        std::size_t highscore = 0u; // NOTE (Lapys) -> Get the highest score.

        unsigned char occupiedTileCount = 0u;
        Tile **occupiedTiles = 0x0;

        // Loop > Logic > Update > High Score
        for (std::size_t highscoreIterator = 0u; highscoreIterator ^ Game::Statistics::highscoreCount; highscoreIterator++)
        if (highscore < (Game::Statistics::highscores + highscoreIterator) -> score)
            highscore = (Game::Statistics::highscores + highscoreIterator) -> score;

        // Modification > Game
            // Statistics > Fruit (Spawn) Count
            Game::Statistics::fruitSpawnCount = highscore > Game::Statistics::score || Game::Statistics::score < 200u ? 1u : ::rand() % (::rand() % 10 > 3 ? 3 : 5);
            Game::Statistics::fruitCount = Game::Statistics::fruitSpawnCount;

            // Map > Fruits
            Game::Map::fruits = (Block*) std::malloc(Game::Statistics::fruitCount * sizeof(Block));

        // Update > Occupied Tiles
        occupiedTiles = (Tile**) std::malloc(Game::Statistics::fruitCount * sizeof(Tile*))

        // Loop
        for (unsigned char fruitIterator = 0u; fruitIterator ^ Game::Statistics::fruitCount; fruitIterator++) {
            // Update > (Game > Map) > Fruits
            *(Game::Map::fruits + fruitIterator) = Block(Block::FRUIT, Tile::getAtCoordinate({(unsigned short) (::rand() % Tile::rowCount), (unsigned short) (::rand() % Tile::columnCount)}));

            // Logic > Loop > Logic
            if (occupiedTileCount)
            for (unsigned char occupiedTileIterator = 0u; occupiedTileCount ^ occupiedTileIterator; occupiedTileIterator++)
            if (
                ((*(occupiedTiles + occupiedTileIterator)) -> x == (Game::Map::fruits + fruitIterator) -> tile -> x) &&
                ((*(occupiedTiles + occupiedTileIterator)) -> y == (Game::Map::fruits + fruitIterator) -> tile -> y)
            ) {
                // Modification > [Tile] > (X, Y); Continue
                (Game::Map::fruits + fruitIterator) -> tile -> x = ::rand() % Tile::rowCount;
                (Game::Map::fruits + fruitIterator) -> tile -> y = ::rand() % Tile::columnCount;

                occupiedTileIterator = 0u;
            }

            // Update > Occupied Tiles
            *(occupiedTiles + occupiedTileCount++) = (Game::Map::fruits + fruitIterator) -> tile;
        }

        // Deletion
        std::free(occupiedTiles);
    }

    void SpawnSnake(void) {
        // Game::Map::snakes = 0x0;
        // Game::Statistics::snakeCount = 0u;
    }

    // Spawn Tiles
    void SpawnTiles(void) {
        // Modification > (Game > Map) > ...
        Game::Map::tiles = (Tile*) std::malloc((Tile::columnCount * Tile::rowCount) * sizeof(Tile));

        // Loop > ...
        for (std::size_t tileRowIndex = 0u; tileRowIndex ^ Tile::rowCount; tileRowIndex++)
        for (std::size_t tileColumnIndex = 0u; tileColumnIndex ^ Tile::columnCount; tileColumnIndex++)
        *(Game::Map::tiles + Game::Statistics::tileCount++) = Tile(tileColumnIndex, tileRowIndex);
    }

/* Phases */
    /* Initiate --- NOTE (Lapys) -> This only invokes once. */
    void Game::Initiate(HWND) {
        // ...
        ::ParseHighscores();
    }

    /* Reset --- NOTE (Lapys) -> Resets the game. */
    void Game::Reset(HWND gameWindowHandle) {
        /* [Terminate] Deletion */ {
            std::free(Game::Map::boosters);
            std::free(Game::Map::fruits);
            std::free(Game::Map::walls);
            std::free(Game::Map::snakes);
            std::free(Game::Map::tiles);
        }

        /* [Reset] */ {
            // Initialization > Game Window (Client Area) Bounding Box
            RECT gameWindowClientAreaBoundingBox {};
            RECT gameWindowBoundingBox {};

            // ...
            ::GetClientRect(gameWindowHandle, &gameWindowClientAreaBoundingBox);
            ::GetWindowRect(gameWindowHandle, &gameWindowBoundingBox);

            // ...
            ::InvalidateRect(gameWindowHandle, 0x0, true);

            // Modification > Game
                // Map > ...
                Game::Map::boosters = 0x0;
                Game::Map::fruits = 0x0;
                Game::Map::walls = 0x0;
                Game::Map::snakes = 0x0;
                Game::Map::tiles = 0x0;

                Game::Map::height = ((double) (gameWindowClientAreaBoundingBox.bottom - gameWindowClientAreaBoundingBox.top)) * (70.0 / 100.0);
                Game::Map::width = ((double) (gameWindowBoundingBox.right - gameWindowBoundingBox.left)) * (70.0 / 100.0);
                Game::Map::coordinates.x = ((double) Game::Map::width) * (5.0 / 100.0);
                Game::Map::coordinates.y = ((double) Game::Map::height) * (5.0 / 100.0);

                // Statistics > ...
                Game::Statistics::boosterCount = 0u;
                Game::Statistics::fruitCount = 0u;
                Game::Statistics::fruitsEaten = 0u;
                Game::Statistics::fruitSpawnCount = 1u;
                Game::Statistics::score = 0u;
                Game::Statistics::snakeCount = 0u;
                Game::Statistics::tileCount = 0u;
                Game::Statistics::wallCount = 0u;
        }

        /* [Initiate] */ {
            // Spawn ...
            ::SpawnTiles();
            ::SpawnFruits();
        }
    }

    /* Update */
    void Game::Update(HWND gameWindowHandle) {
        // Initialization > Game Window (Graphics Device Context Handle, Paint Information)
        HDC gameWindowGraphicsDeviceContextHandle;
        PAINTSTRUCT gameWindowPaintInformation;

        // (Block, Snake, Tile) > Paint All
        Block::paintAll(gameWindowHandle);
        Tile::paintAll(gameWindowHandle);

        // [Initiate] ...
        gameWindowGraphicsDeviceContextHandle = ::BeginPaint(gameWindowHandle, &gameWindowPaintInformation);

        // (Block, Snake, Tile) > Draw All
        Tile::drawAll(gameWindowGraphicsDeviceContextHandle);
        Block::drawAll(gameWindowGraphicsDeviceContextHandle);

        // [Terminate] Deletion
        ::ReleaseDC(gameWindowHandle, gameWindowGraphicsDeviceContextHandle);
        ::EndPaint(gameWindowHandle, &gameWindowPaintInformation);
    }

/* Main */
int WinMain(HINSTANCE instanceHandle, HINSTANCE, LPSTR, int windowAppearance) {
    // Initiate; Terminate
    Game::Initiate(instanceHandle, windowAppearance);
    Game::Terminate();

    // Return
    return PROGRAM_STATUS;
}
