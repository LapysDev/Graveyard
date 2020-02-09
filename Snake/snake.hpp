/* Import */
#include <windows.h> // Windows

/* Global > Program Status */
int PROGRAM_STATUS = EXIT_SUCCESS;

/* Namespace > Game */
namespace Game {
    /* Global > Phase */
    namespace Phases { enum Phase {INITIATING, RESETTING, TERMINATING, UPDATING} PHASE; }
    using Phases::PHASE;

    /* Phases > ...
        --- NOTE ---
            #Lapys:
                - Only the Reset and Update phases are allowed to be user-defined.

                - The Reset phase is invoked at the beginning of the program right before the Update phase.
                - The Terminate phase may be invoked by the user.

        --- WARN (Lapys) -> Do not invoke the Reset phase from within the Update phase (or vice-versa).
    */
    void Initiate(HINSTANCE, const int); void Initiate(HWND);
    void Reset(HWND);
    void Terminate(HWND, const char[], const int); void Terminate(void);
    void Update(HWND);

    /* Class */
        // Color --- NOTE (Lapys) -> In RGB format.
        struct Color {
            // [...]
            public:
                // Definition > Channels
                unsigned char channels[3];

                // Initialization > (Red, Green, Blue)
                struct ColorBlueChannelAccessor { friend Color; private: Color *color; public: constexpr explicit inline ColorBlueChannelAccessor(const Color* color) : color{(Color*) color} {} constexpr explicit inline ColorBlueChannelAccessor(void) : color{0x0} {} inline unsigned char operator =(const unsigned char value) { *(this -> color -> channels + 2) = value; return value; } inline operator unsigned char(void) const { return *(this -> color -> channels + 2); } } blue;
                struct ColorGreenChannelAccessor { friend Color; private: Color *color; public: constexpr explicit inline ColorGreenChannelAccessor(const Color* color) : color{(Color*) color} {} constexpr explicit inline ColorGreenChannelAccessor(void) : color{0x0} {} inline unsigned char operator =(const unsigned char value) { *(this -> color -> channels + 1) = value; return value; } inline operator unsigned char(void) const { return *(this -> color -> channels + 1); } } green;
                struct ColorRedChannelAccessor { friend Color; private: Color *color; public: constexpr explicit inline ColorRedChannelAccessor(const Color* color) : color{(Color*) color} {} constexpr explicit inline ColorRedChannelAccessor(void) : color{0x0} {} inline unsigned char operator =(const unsigned char value) { *(this -> color -> channels) = value; return value; } inline operator unsigned char(void) const { return *(this -> color -> channels); } } red;

                // [Constructor]
                constexpr inline Color(const unsigned color) : channels{GetRValue(color), GetGValue(color), GetBValue(color)}, blue{this}, green{this}, red{this} {}
                constexpr explicit inline Color(const unsigned char redChannel, const unsigned char greenChannel, const unsigned char blueChannel) : channels{redChannel, greenChannel, blueChannel}, blue{this}, green{this}, red{this} {}
                constexpr explicit inline Color(void) : channels{0u, 0u, 0u}, blue{this}, green{this}, red{this} {}
                constexpr inline Color(Color&& color) : channels{*(color.channels), *(color.channels + 1), *(color.channels + 2)}, blue{this}, green{this}, red{this} {}
                constexpr inline Color(const Color& color) : channels{*(color.channels), *(color.channels + 1), *(color.channels + 2)}, blue{this}, green{this}, red{this} {}

                // [Operator] > ...
                inline Color& operator =(Color&& color) noexcept { this -> blue.color = this -> green.color = this -> red.color = this; *(this -> channels) = *(color.channels); *(this -> channels + 1) = *(color.channels + 1); *(this -> channels + 2) = *(color.channels + 2); return *this; }
                inline Color& operator =(const Color& color) noexcept { this -> blue.color = this -> green.color = this -> red.color = this; *(this -> channels) = *(color.channels); *(this -> channels + 1) = *(color.channels + 1); *(this -> channels + 2) = *(color.channels + 2); return *this; }
                inline operator unsigned(void) const { return RGB(*(this -> channels), *(this -> channels + 1), *(this -> channels + 2)); }
        };

        // Coordinate --- NOTE (Lapys) -> Simple 2D rectangular Cartesian coordinates.
        struct Coordinate {
            // [...]
            public:
                // Definition > (X, Y)
                unsigned short x, y;

                // [Constructor]
                constexpr inline Coordinate(const unsigned short x, const unsigned short y) : x{x}, y{y} {}
        };

    /* Namespace > ... */
    namespace Map { class Block; class Snake; class Tile; }
    namespace Settings {}
    namespace Statistics { struct Highscore; }

    /* Modification */
        /* Statistics */
        namespace Statistics {
            /* ... */
            unsigned char boosterCount;
            unsigned char fruitCount;
            std::size_t fruitsEaten;
            unsigned char fruitSpawnCount;
            std::size_t highscoreCount;
            Highscore *highscores = 0x0;
            std::size_t score;
            std::size_t snakeCount;
            std::size_t tileCount;
            std::size_t wallCount;

            // High Score
            struct Highscore {
                // [...]
                public:
                    // Definition > ...
                    std::size_t score;
                    char username[20];

                    // [Constructor]
                    constexpr explicit inline Highscore(const char username[], const std::size_t score) : score{score}, username{0} { if (username) { unsigned char usernameLength = 0u; for (; *(username + usernameLength) && (usernameLength ^ 20u); usernameLength++) continue; ::memcpy(&(this -> username), username, usernameLength * sizeof(char)); } }
                    constexpr inline Highscore(Highscore&& highscore) : score{highscore.score}, username{*(highscore.username), *(highscore.username + 1), *(highscore.username + 2), *(highscore.username + 3), *(highscore.username + 4), *(highscore.username + 5), *(highscore.username + 6), *(highscore.username + 7), *(highscore.username + 8), *(highscore.username + 9), *(highscore.username + 10), *(highscore.username + 11), *(highscore.username + 12), *(highscore.username + 13), *(highscore.username + 14), *(highscore.username + 15), *(highscore.username + 16), *(highscore.username + 17), *(highscore.username + 18), *(highscore.username + 19)} {}
                    constexpr inline Highscore(const Highscore& highscore) : score{highscore.score}, username{*(highscore.username), *(highscore.username + 1), *(highscore.username + 2), *(highscore.username + 3), *(highscore.username + 4), *(highscore.username + 5), *(highscore.username + 6), *(highscore.username + 7), *(highscore.username + 8), *(highscore.username + 9), *(highscore.username + 10), *(highscore.username + 11), *(highscore.username + 12), *(highscore.username + 13), *(highscore.username + 14), *(highscore.username + 15), *(highscore.username + 16), *(highscore.username + 17), *(highscore.username + 18), *(highscore.username + 19)} {}

                    // [Operator] > [=]
                    inline Highscore& operator =(Highscore&& highscore) noexcept { this -> score = highscore.score; ::memcpy(&(this -> username), highscore.username, 20u * sizeof(char)); return *this; }
                    inline Highscore& operator =(const Highscore& highscore) noexcept { this -> score = highscore.score; ::memcpy(&(this -> username), highscore.username, 20u * sizeof(char)); return *this; }
            };
        }

        /* Map */
        inline namespace Map {
            // Boosters, Fruits, Snakes, Tiles, Walls
            Block *boosters = 0x0;
            Block *fruits = 0x0;
            Snake *snakes = 0x0;
            Tile *tiles = 0x0;
            Block *walls = 0x0;

            /* Coordinates, Height, Width */
            namespace { Coordinate coordinates {0u, 0u}; std::size_t height; std::size_t width; }

            /* Class */
                // Snake
                class Snake : public Coordinate {
                    // [...]
                    public:
                        // Definition > (..., Color, Score, State, Tail)
                        enum State {ALIVE, DEAD};

                        Color color;
                        std::size_t score;
                        State state;
                        struct Tail { public: Coordinate *coordinates; std::size_t length; constexpr explicit inline Tail(void) : coordinates{0x0}, length{0u} {} } tail;

                        // [Constructor]
                        constexpr explicit inline Snake(const unsigned short initialX, const unsigned short initialY) : Coordinate{initialX, initialY}, score{0u}, state{Snake::ALIVE}, tail{} {}
                        constexpr inline Snake(Snake&& snake) : Coordinate{snake.x, snake.y}, score{snake.score}, state{snake.state}, tail{} { this -> tail.coordinates = (Coordinate*) std::malloc(snake.tail.length * sizeof(Coordinate)); for (std::size_t iterator = 0u; iterator ^ snake.tail.length; iterator++) { (this -> tail.coordinates + iterator) -> x = (snake.tail.coordinates + iterator) -> x; (this -> tail.coordinates + iterator) -> y = (snake.tail.coordinates + iterator) -> y; } }
                        constexpr inline Snake(const Snake& snake) : Coordinate{snake.x, snake.y}, score{snake.score}, state{snake.state}, tail{} { this -> tail.coordinates = (Coordinate*) std::malloc(snake.tail.length * sizeof(Coordinate)); for (std::size_t iterator = 0u; iterator ^ snake.tail.length; iterator++) { (this -> tail.coordinates + iterator) -> x = (snake.tail.coordinates + iterator) -> x; (this -> tail.coordinates + iterator) -> y = (snake.tail.coordinates + iterator) -> y; } }

                        // [Destructor]
                        ~Snake(void) { std::free(this -> tail.coordinates); }
                };

                // Tile
                class Tile : public Coordinate {
                    // [...]
                    private:
                        // Definition > ...
                        static HBITMAP bitmapHandle;
                        static HGDIOBJ dummyObject;
                        static HDC graphicsDeviceContextHandle;

                    // [...]
                    public:
                        // Definition > ...
                        static Color boosterColor;
                        static Color defaultColor;
                        static Color fruitColor;
                        static Color snakeColor;
                        static Color wallColor;

                        static std::size_t columnCount;
                        static std::size_t rowCount;

                        // Initialization > (Color, Height, Width)
                        Color color;
                        const struct TileHeightAccessor { public: constexpr explicit inline TileHeightAccessor(void) {} inline operator unsigned short(void) const { return Tile::getHeight(); } } height;
                        const struct TileWidthAccessor { public: constexpr explicit inline TileWidthAccessor(void) {} inline operator unsigned short(void) const { return Tile::getWidth(); } } width;

                        // [Constructor]
                        explicit inline Tile(const unsigned short x, const unsigned short y) : Coordinate{x, y}, color{Tile::defaultColor}, height{}, width{} {}
                        inline Tile(Tile&& tile) : Coordinate{tile.x, tile.y}, color{tile.color}, height{}, width{} {}
                        inline Tile(const Tile& tile) : Coordinate{tile.x, tile.y}, color{tile.color}, height{}, width{} {}

                        // [Operator] > [=]
                        inline Tile& operator =(Tile&& tile) noexcept { this -> color = tile.color; this -> x = tile.x; this -> y = tile.y; return *this; }
                        inline Tile& operator =(const Tile& tile) noexcept { this -> color = tile.color; this -> x = tile.x; this -> y = tile.y; return *this; }

                        // Function
                            // Draw (All)
                            inline void draw(HDC graphicsDeviceContextHandle, const Coordinate offset = Coordinate(Game::Map::coordinates.x, Game::Map::coordinates.y)) const noexcept {
                                // Initialization > ...
                                HBITMAP tileBitmapHandle;
                                HGDIOBJ tileDummyObject;
                                HDC tileGraphicsDeviceContextHandle;

                                // Update > ...
                                tileBitmapHandle = Tile::getBitmapHandle(graphicsDeviceContextHandle, this -> color);

                                tileGraphicsDeviceContextHandle = ::CreateCompatibleDC(graphicsDeviceContextHandle);
                                tileDummyObject = ::SelectObject(tileGraphicsDeviceContextHandle, tileBitmapHandle);

                                // ...
                                ::BitBlt(graphicsDeviceContextHandle, offset.x + ((this -> x) * (this -> width)), offset.y + ((this -> height) * (this -> y)), this -> width, this -> height, tileGraphicsDeviceContextHandle, 0, 0, SRCCOPY);

                                // Deletion
                                ::SelectObject(tileGraphicsDeviceContextHandle, tileDummyObject);
                                ::DeleteObject(tileDummyObject);
                                ::DeleteDC(tileGraphicsDeviceContextHandle);
                                if (tileBitmapHandle != Tile::bitmapHandle) ::DeleteObject(tileBitmapHandle);
                            }
                            inline static void drawAll(HDC graphicsDeviceContextHandle) noexcept {
                                // Initialization > ...
                                HBITMAP tilesBitmapHandle;
                                HGDIOBJ tilesDummyObject;
                                HDC tilesGraphicsDeviceContextHandle;

                                // Update > ...
                                tilesBitmapHandle = ::CreateCompatibleBitmap(graphicsDeviceContextHandle, Tile::rowCount * Tile::getWidth(), Tile::columnCount * Tile::getHeight());
                                tilesGraphicsDeviceContextHandle = ::CreateCompatibleDC(graphicsDeviceContextHandle);
                                tilesDummyObject = ::SelectObject(tilesGraphicsDeviceContextHandle, tilesBitmapHandle);

                                // Loop > ...; ...
                                for (std::size_t tileIterator = 0u; tileIterator ^ Game::Statistics::tileCount; tileIterator++) (Game::Map::tiles + tileIterator) -> draw(tilesGraphicsDeviceContextHandle, {0u, 0u});
                                ::BitBlt(graphicsDeviceContextHandle, Game::Map::coordinates.x, Game::Map::coordinates.y, Tile::rowCount * Tile::getWidth(), Tile::columnCount * Tile::getHeight(), tilesGraphicsDeviceContextHandle, 0, 0, SRCCOPY);

                                // Deletion
                                ::SelectObject(tilesGraphicsDeviceContextHandle, tilesDummyObject);
                                ::DeleteObject(tilesDummyObject);
                                ::DeleteDC(tilesGraphicsDeviceContextHandle);
                                ::DeleteObject(tilesBitmapHandle);
                            }

                            // Get ..
                            inline static Tile* getAtCoordinate(const Coordinate coordinate) noexcept { return Game::Map::tiles + (coordinate.x + (Tile::columnCount * coordinate.y)); }
                            inline static HBITMAP getBitmapHandle(HDC graphicsDeviceContextHandle, const Color tileColor = Tile::defaultColor) noexcept {
                                // Evaluation > Tile Bitmap Handle
                                HBITMAP tileBitmapHandle = Tile::bitmapHandle;

                                // Logic --- NOTE (Lapys) -> Programatically draw a default bitmap.
                                if (0x0 == tileBitmapHandle) {
                                    // Initialization > (Tile Bitmap (Brush, Graphics Device Context Handle, Rectangular Region), ...)
                                    HBRUSH tileBitmapBrush;
                                    HDC tileBitmapGraphicsDeviceContextHandle;
                                    RECT tileBitmapRectangularRegion {};

                                    HGDIOBJ tileDummyObject;

                                    // Update > (Tile (Bitmap, Graphics Device Context) Handle, ...)
                                    tileBitmapHandle = ::CreateCompatibleBitmap(graphicsDeviceContextHandle, Tile::getWidth(), Tile::getHeight());
                                    tileBitmapGraphicsDeviceContextHandle = ::CreateCompatibleDC(0x0);

                                    tileDummyObject = ::SelectObject(tileBitmapGraphicsDeviceContextHandle, tileBitmapHandle);

                                    /* ... */ {
                                        // [Border]
                                        tileBitmapRectangularRegion.bottom = Tile::getHeight(); tileBitmapRectangularRegion.left = 0L; tileBitmapRectangularRegion.right = Tile::getWidth(); tileBitmapRectangularRegion.top = 0L;
                                        ::FillRect(tileBitmapGraphicsDeviceContextHandle, &tileBitmapRectangularRegion, tileBitmapBrush = (HBRUSH) ::CreateSolidBrush(Color(((double) tileColor.red) * (10.0 / 100.0), ((double) tileColor.green) * (10.0 / 100.0), ((double) tileColor.blue) * (10.0 / 100.0))));
                                        ::DeleteObject(tileBitmapBrush);

                                        // [Inner (Bottom-Left) Bevel]
                                        tileBitmapRectangularRegion.bottom = ((double) Tile::getHeight()) * (99.0 / 100.0); tileBitmapRectangularRegion.left = ((double) Tile::getWidth()) * (1.0 / 100.0); tileBitmapRectangularRegion.right = ((double) Tile::getWidth()) * (99.0 / 100.0); tileBitmapRectangularRegion.top = ((double) Tile::getHeight()) * (1.0 / 100.0);
                                        ::FillRect(tileBitmapGraphicsDeviceContextHandle, &tileBitmapRectangularRegion, tileBitmapBrush = (HBRUSH) ::CreateSolidBrush(Color(((double) tileColor.red) * (80.0 / 100.0), ((double) tileColor.green) * (80.0 / 100.0), ((double) tileColor.blue) * (80.0 / 100.0))));
                                        ::DeleteObject(tileBitmapBrush);

                                        // [Surface]
                                        tileBitmapRectangularRegion.bottom = ((double) Tile::getHeight()) * (95.0 / 100.0); tileBitmapRectangularRegion.left = ((double) Tile::getWidth()) * (5.0 / 100.0); tileBitmapRectangularRegion.right = ((double) Tile::getWidth()) * (99.0 / 100.0); tileBitmapRectangularRegion.top = ((double) Tile::getHeight()) * (1.0 / 100.0);
                                        ::FillRect(tileBitmapGraphicsDeviceContextHandle, &tileBitmapRectangularRegion, tileBitmapBrush = (HBRUSH) ::CreateSolidBrush(tileColor));
                                        ::DeleteObject(tileBitmapBrush);

                                        // [Edge Outline]
                                        for (short tileBitmapXCoordinate = (short) tileBitmapRectangularRegion.left, tileBitmapYCoordinate = (short) tileBitmapRectangularRegion.bottom; tileBitmapXCoordinate; (tileBitmapXCoordinate--, tileBitmapYCoordinate++)) {
                                            // Initialization > Color
                                            Color color = tileColor;

                                            // (Logic > )Modification > Color > (Red, Green, Blue)
                                            color.blue = ((double) tileColor.blue) * (150.0 / 100.0) > 255.0 ? 255.0 : ((double) tileColor.blue) * (150.0 / 100.0);
                                            color.green = ((double) tileColor.green) * (150.0 / 100.0) > 255.0 ? 255.0 : ((double) tileColor.green) * (150.0 / 100.0);
                                            color.red = ((double) tileColor.red) * (150.0 / 100.0) > 255.0 ? 255.0 : ((double) tileColor.red) * (150.0 / 100.0);

                                            if (((double) color.blue) < (255.0 * (16.7777 / 100.0))) { color.blue = 255.0 * (16.7777 / 100.0); }
                                            if (((double) color.green) < (255.0 * (16.7777 / 100.0))) { color.green = 255.0 * (16.7777 / 100.0); }
                                            if (((double) color.red) < (255.0 * (16.7777 / 100.0))) { color.red = 255.0 * (16.7777 / 100.0); }

                                            // ...
                                            ::SetPixelV(tileBitmapGraphicsDeviceContextHandle, tileBitmapXCoordinate, tileBitmapYCoordinate, color);
                                        }
                                    }

                                    // Deletion
                                    ::SelectObject(tileBitmapGraphicsDeviceContextHandle, tileDummyObject);
                                    ::DeleteObject(tileDummyObject);
                                    ::DeleteDC(tileBitmapGraphicsDeviceContextHandle);
                                }

                                // Return
                                return tileBitmapHandle;
                            }
                            inline static unsigned short getHeight(void) noexcept { return (Game::Map::height < Game::Map::width ? Game::Map::height : Game::Map::width) / Tile::columnCount; }
                            inline static unsigned short getWidth(void) noexcept { return (Game::Map::height < Game::Map::width ? Game::Map::height : Game::Map::width) / Tile::rowCount; }

                            // Paint (All)
                            inline void paint(HWND windowHandle) noexcept { RECT tileBoundingBox {}; tileBoundingBox.left = Game::Map::coordinates.x + ((this -> width) * (this -> x)); tileBoundingBox.top = Game::Map::coordinates.y + ((this -> height) * (this -> y)); tileBoundingBox.bottom = this -> height + tileBoundingBox.left; tileBoundingBox.right = this -> width + tileBoundingBox.top; ::InvalidateRect(windowHandle, &tileBoundingBox, true); }
                            inline static void paintAll(HWND windowHandle) noexcept { RECT tileBoundingBox {}; tileBoundingBox.left = Game::Map::coordinates.x; tileBoundingBox.top = Game::Map::coordinates.y; tileBoundingBox.bottom = tileBoundingBox.top + (Tile::columnCount * Tile::getHeight()); tileBoundingBox.right = tileBoundingBox.left + (Tile::rowCount * Tile::getWidth()); ::InvalidateRect(windowHandle, &tileBoundingBox, true); }
                };
                    /* ... */
                    HBITMAP Tile::bitmapHandle = 0x0;
                    HGDIOBJ Tile::dummyObject = 0x0;
                    HDC Tile::graphicsDeviceContextHandle = 0x0;

                    Color Tile::boosterColor {255u, 255u, 255u};
                    Color Tile::defaultColor {255u, 255u, 255u};
                    Color Tile::fruitColor {255u, 255u, 255u};
                    Color Tile::snakeColor {255u, 255u, 255u};
                    Color Tile::wallColor {255u, 255u, 255u};

                    std::size_t Tile::columnCount = 10u;
                    std::size_t Tile::rowCount = 10u;

                // Block
                class Block {
                    // [...]
                    private:
                        // Definition > ...
                        static HBITMAP boosterBitmapHandle;
                        static HBITMAP fruitBitmapHandle;
                        static HBITMAP wallBitmapHandle;

                    // [...]
                    public:
                        // Definition > (..., Tile, Type)
                        enum Type {BOOSTER, FRUIT, WALL};

                        Tile *tile;
                        Type type;

                        // Initialization > (Height, Width)
                        struct BlockHeightAccessor { friend Block; private: Block *block; public: constexpr explicit inline BlockHeightAccessor(const Block* block) : block{(Block*) block} {} constexpr explicit inline BlockHeightAccessor(void) : block{0x0} {} inline operator unsigned short(void) const { return Block::getHeight(this -> block -> type); } } height;
                        struct BlockWidthAccessor { friend Block; private: Block *block; public: constexpr explicit inline BlockWidthAccessor(const Block* block) : block{(Block*) block} {} constexpr explicit inline BlockWidthAccessor(void) : block{0x0} {} inline operator unsigned short(void) const { return Block::getWidth(this -> block -> type); } } width;

                        // [Constructor]
                        constexpr explicit inline Block(const Type type, Tile* tile) : tile{tile}, type{type}, height{this}, width{this} {}
                        constexpr explicit inline Block(const Type type, const Tile* tile) : tile{(Tile*) tile}, type{type}, height{this}, width{this} {}
                        constexpr inline Block(Block&& block) : tile{block.tile}, type{block.type}, height{this}, width{this} {}
                        constexpr inline Block(const Block& block) : tile{block.tile}, type{block.type}, height{this}, width{this} {}

                        // [Operator] > [=]
                        inline Block& operator =(Block&& block) noexcept { this -> height.block = this -> width.block = (Block*) this; this -> tile = block.tile; this -> type = block.type; return *this; }
                        inline Block& operator =(const Block& block) noexcept { this -> height.block = this -> width.block = (Block*) this; this -> tile = block.tile; this -> type = block.type; return *this; }

                        // Function
                            // Draw (All)
                            inline void draw(HDC graphicsDeviceContextHandle) const noexcept {
                                // Initialization > Block ...
                                HBITMAP blockBitmapHandle;
                                HGDIOBJ blockDummyObject;
                                HDC blockGraphicsDeviceContextHandle;

                                // Constant > Tile ...
                                const Color tileColor = this -> tile -> color;

                                // ...
                                switch (this -> type) { case Block::BOOSTER: tile -> color = Color(127u, 200u, 255u); break; case Block::FRUIT: tile -> color = Color(172u, 255u, 172u); break; case Block::WALL: tile -> color = Color(225u, 225u, 225u); break; }
                                tile -> draw(graphicsDeviceContextHandle);
                                tile -> color = tileColor;

                                // Update > ...
                                blockBitmapHandle = Block::getBitmapHandle(graphicsDeviceContextHandle, this -> type);

                                blockGraphicsDeviceContextHandle = ::CreateCompatibleDC(graphicsDeviceContextHandle);
                                blockDummyObject = ::SelectObject(blockGraphicsDeviceContextHandle, blockBitmapHandle);

                                // ... --- UPDATE (Lapys)
                                // for (unsigned short columnIndex = 0; columnIndex ^ this -> width; columnIndex++)
                                // for (unsigned short rowIndex = 0; rowIndex ^ this -> width; rowIndex++)
                                // ::BitBlt(graphicsDeviceContextHandle, ((Game::Map::coordinates.x + ((this -> tile -> x) * (this -> tile -> width))) + (this -> tile -> width - this -> width) / 2u) - 1u, ((Game::Map::coordinates.y + ((this -> tile -> y) * (this -> tile -> height))) + (this -> tile -> height - this -> height) / 2u) - 1u, this -> width, this -> height, blockGraphicsDeviceContextHandle, 0, 0, SRCCOPY);

                                // Deletion
                                ::SelectObject(blockGraphicsDeviceContextHandle, blockDummyObject);
                                ::DeleteObject(blockDummyObject);
                                ::DeleteDC(blockGraphicsDeviceContextHandle);
                                if (
                                    blockBitmapHandle != Block::boosterBitmapHandle &&
                                    blockBitmapHandle != Block::fruitBitmapHandle &&
                                    blockBitmapHandle != Block::wallBitmapHandle
                                ) ::DeleteObject(blockBitmapHandle);
                            }
                            inline static void drawAll(HDC graphicsDeviceContextHandle) noexcept {
                                for (std::size_t blockIterator = 0u; blockIterator ^ Game::Statistics::boosterCount; blockIterator++) (Game::Map::boosters + blockIterator) -> draw(graphicsDeviceContextHandle);
                                for (std::size_t blockIterator = 0u; blockIterator ^ Game::Statistics::fruitCount; blockIterator++) (Game::Map::fruits + blockIterator) -> draw(graphicsDeviceContextHandle);
                                for (std::size_t blockIterator = 0u; blockIterator ^ Game::Statistics::wallCount; blockIterator++) (Game::Map::walls + blockIterator) -> draw(graphicsDeviceContextHandle);
                            }

                            // Get (Bitmap Handle, Height, Width)
                            inline static HBITMAP getBitmapHandle(HDC graphicsDeviceContextHandle, const Type type) noexcept {
                                // Evaluation > Block Bitmap Handle
                                HBITMAP blockBitmapHandle = 0x0;

                                // Logic > Update > Block Bitmap Handle
                                switch (type) {
                                    case Block::BOOSTER: blockBitmapHandle = Block::boosterBitmapHandle; break;
                                    case Block::FRUIT: blockBitmapHandle = Block::fruitBitmapHandle; break;
                                    case Block::WALL: blockBitmapHandle = Block::wallBitmapHandle; break;
                                }

                                // Logic --- NOTE (Lapys) -> Programatically draw a default bitmap.
                                if (0x0 == blockBitmapHandle) {
                                    // Initialization > (Block Bitmap Graphics Device Context Handle, ...)
                                    HDC blockBitmapGraphicsDeviceContextHandle;
                                    HGDIOBJ blockDummyObject;

                                    // Initialization > Block Bitmap (Height, Width)
                                    const unsigned short blockBitmapHeight = Block::getHeight(type);
                                    const unsigned short blockBitmapWidth = Block::getWidth(type);

                                    // (Logic > )Update > Block ...
                                    switch (type) {
                                        case Block::BOOSTER: blockBitmapHandle = ::CreateCompatibleBitmap(graphicsDeviceContextHandle, blockBitmapWidth, blockBitmapHeight); break;
                                        case Block::FRUIT: blockBitmapHandle = ::CreateCompatibleBitmap(graphicsDeviceContextHandle, blockBitmapWidth, blockBitmapHeight); break;
                                        case Block::WALL: blockBitmapHandle = ::CreateCompatibleBitmap(graphicsDeviceContextHandle, blockBitmapWidth, blockBitmapHeight); break;
                                    }
                                    blockBitmapGraphicsDeviceContextHandle = ::CreateCompatibleDC(0x0);
                                    blockDummyObject = ::SelectObject(blockBitmapGraphicsDeviceContextHandle, blockBitmapHandle);

                                    /* ... --- NOTE (Lapys) -> Try optimizing this, lol... */ switch (type) {
                                        // [Booster]
                                        case Block::BOOSTER: {
                                            for (unsigned char iterator = 0u; blockBitmapHeight ^ iterator; iterator++)
                                            for (unsigned char subiterator = 0u; blockBitmapWidth ^ subiterator; subiterator++)
                                                ::SetPixelV(blockBitmapGraphicsDeviceContextHandle, subiterator, iterator, Color(0u, 127u, 255u));
                                        } break;

                                        // [Fruit]
                                        case Block::FRUIT: {
                                            for (unsigned char iterator = 0u; blockBitmapHeight ^ iterator; iterator++)
                                            for (unsigned char subiterator = 0u; blockBitmapWidth ^ subiterator; subiterator++)
                                                ::SetPixelV(blockBitmapGraphicsDeviceContextHandle, subiterator, iterator, Color(255u, 0u, 0u));
                                        } break;

                                        // [Wall]
                                        case Block::WALL: {
                                            for (unsigned char iterator = 0u; blockBitmapHeight ^ iterator; iterator++)
                                            for (unsigned char subiterator = 0u; blockBitmapWidth ^ subiterator; subiterator++)
                                                ::SetPixelV(blockBitmapGraphicsDeviceContextHandle, subiterator, iterator, Color(127u, 127u, 127u));
                                        } break;
                                    }

                                    // Deletion
                                    ::SelectObject(blockBitmapGraphicsDeviceContextHandle, blockDummyObject);
                                    ::DeleteObject(blockDummyObject);
                                    ::DeleteDC(blockBitmapGraphicsDeviceContextHandle);
                                }

                                // Return
                                return blockBitmapHandle;
                            }
                            inline static unsigned short getHeight(const Type type) noexcept { switch (type) { case Block::BOOSTER: return ((double) Tile::getHeight()) * (50.0 / 100.0); case Block::FRUIT: return ((double) Tile::getHeight()) * (75.0 / 100.0); case Block::WALL: return ((double) Tile::getHeight()) * (95.0 / 100.0); } return 0u; }
                            inline static unsigned short getWidth(const Type type) noexcept { switch (type) { case Block::BOOSTER: return ((double) Tile::getWidth()) * (50.0 / 100.0); case Block::FRUIT: return ((double) Tile::getWidth()) * (75.0 / 100.0); case Block::WALL: return ((double) Tile::getWidth()) * (95.0 / 100.0); } return 0u; }

                            // Paint (All)
                            inline void paint(HWND windowHandle) noexcept {
                                RECT blockBoundingBox {};
                                blockBoundingBox.left = Game::Map::coordinates.x + ((this -> tile -> width) * (this -> tile -> x));
                                blockBoundingBox.top = Game::Map::coordinates.y + ((this -> tile -> height) * (this -> tile -> y));
                                blockBoundingBox.bottom = (this -> height) + blockBoundingBox.left;
                                blockBoundingBox.right = (this -> width) + blockBoundingBox.top;
                                ::InvalidateRect(windowHandle, &blockBoundingBox, true);
                            }
                            inline static void paintAll(HWND windowHandle) noexcept {
                                for (std::size_t blockIterator = 0u; blockIterator ^ Game::Statistics::boosterCount; blockIterator++) (Game::Map::boosters + blockIterator) -> paint(windowHandle);
                                for (std::size_t blockIterator = 0u; blockIterator ^ Game::Statistics::fruitCount; blockIterator++) (Game::Map::fruits + blockIterator) -> paint(windowHandle);
                                for (std::size_t blockIterator = 0u; blockIterator ^ Game::Statistics::wallCount; blockIterator++) (Game::Map::walls + blockIterator) -> paint(windowHandle);
                            }
                };
                    /* ... */
                    HBITMAP Block::boosterBitmapHandle = 0x0;
                    HBITMAP Block::fruitBitmapHandle = 0x0;
                    HBITMAP Block::wallBitmapHandle = 0x0;
        }

        /* Settings */
        namespace Settings {
            // ...
            bool allowHumanInput = true;
            bool borders = false;
        }
} using Game::Color; using Game::Coordinate; using Game::Map::Block; using Game::Map::Snake; using Game::Map::Tile; using Game::Statistics::Highscore;

/* Function > Game Window Procedure */
LRESULT CALLBACK gameWindowProcedure(HWND gameWindowHandle, UINT message, WPARAM messageParameter, LPARAM additionalMessageParameter) { return ::DefWindowProc(gameWindowHandle, message, messageParameter, additionalMessageParameter); }

/* Phases */
    /* Initiate */
    void Game::Initiate(HINSTANCE gameInstanceHandle = 0x0, const int gameWindowAppearance = SW_SHOW) {
        /* ... */
        Game::PHASE = Game::Phases::INITIATING;

        /* Global > (... Console ..., Game Window Class) */
        HANDLE activeScreenConsoleBufferHandle = ::CreateFile("CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, 0x0, OPEN_ALWAYS, 0, 0x0);
        CONSOLE_SCREEN_BUFFER_INFO activeScreenConsoleBufferInformation;

        const WNDCLASS gameWindowClass {CS_HREDRAW | CS_VREDRAW, &gameWindowProcedure, 0, 0, 0x0, 0x0, (HCURSOR) ::LoadCursor(0x0, IDC_ARROW), (HBRUSH) COLOR_WINDOW, 0x0, "Snake"};

        // Initialization > ...
        DWORD bytesWritten;

        // Update > ... Console (Buffer Information, Handle)
        ::SetConsoleActiveScreenBuffer(activeScreenConsoleBufferHandle);
        ::SetConsoleTitle("Snake");
        ::ShowWindow(::GetConsoleWindow(), SW_SHOW);

        ::GetConsoleScreenBufferInfo(activeScreenConsoleBufferHandle, &activeScreenConsoleBufferInformation);
        ::FillConsoleOutputCharacter(activeScreenConsoleBufferHandle, ' ', activeScreenConsoleBufferInformation.dwSize.X * activeScreenConsoleBufferInformation.dwSize.Y, {0, 0}, &bytesWritten);
        ::SetConsoleCursorPosition(activeScreenConsoleBufferHandle, {0, 0});

        ::WriteConsoleOutputCharacter(activeScreenConsoleBufferHandle, "[PROGRAM INITIATED]", 19, {0, 0}, &bytesWritten);

        // Logic
        if (::RegisterClass(&gameWindowClass)) {
            // Constant
                // Game Window (Height, Width, (Left, Top) Position)
                const long gameWindowHeight = ((double) ::GetSystemMetrics(SM_CYSCREEN)) * (75.0 / 100.0);
                const long gameWindowWidth = ((double) ::GetSystemMetrics(SM_CXSCREEN)) * (75.0 / 100.0);

                const long gameWindowLeftPosition = (::GetSystemMetrics(SM_CXSCREEN) - gameWindowWidth) / 2L;
                const long gameWindowTopPosition = (::GetSystemMetrics(SM_CYSCREEN) - gameWindowHeight) / 2L;

                /* Game Window Handle */
                const HWND gameWindowHandle = ::CreateWindowEx(
                    0, gameWindowClass.lpszClassName, "Snake",
                    WS_CAPTION | WS_OVERLAPPED | WS_SYSMENU,
                    gameWindowLeftPosition, gameWindowTopPosition,
                    gameWindowWidth, gameWindowHeight,
                    0x0, 0x0, gameInstanceHandle, 0x0
                );

            // Logic
            if (gameWindowHandle) {
                // Global > Game Window Procedure Message
                MSG gameWindowProcedureMessage {};

                // Update > Game Window Handle
                ::ShowWindow(gameWindowHandle, gameWindowAppearance);
                ::UpdateWindow(gameWindowHandle);

                // ...; Loop
                Game::Initiate(gameWindowHandle);
                Game::PHASE = Game::Phases::RESETTING;
                Game::Reset(gameWindowHandle);
                Game::PHASE = Game::Phases::UPDATING;

                while (Game::PHASE == Game::Phases::UPDATING) {
                    // Logic
                    if (::PeekMessage(&gameWindowProcedureMessage, 0x0, 0, 0, PM_REMOVE)) {
                        // Logic > ... --- UPDATE (Lapys) -> Close procedure not working for some reason.
                        if (gameWindowProcedureMessage.message == WM_CLOSE) {
                            ::DestroyWindow(gameWindowHandle); ::PostQuitMessage(0);
                            Game::PHASE = Game::Phases::TERMINATING;
                        }

                        else if (
                            (gameWindowProcedureMessage.message == WM_DESTROY || gameWindowProcedureMessage.message == WM_QUIT) ||
                            (gameWindowProcedureMessage.message == WM_KEYDOWN && gameWindowProcedureMessage.wParam == VK_ESCAPE)
                        ) Game::PHASE = Game::Phases::TERMINATING;
                        else { ::TranslateMessage(&gameWindowProcedureMessage); ::DispatchMessage(&gameWindowProcedureMessage); }

                        // Logic > Update
                        if (Game::PHASE == Game::Phases::UPDATING) Game::Update(gameWindowHandle);
                    }

                    else {
                        // Update; ...
                        Game::Update(gameWindowHandle);
                        ::Sleep(50u); // NOTE (Lapys) -> Do not hog the processor.
                    }
                }

                // Update > Program Status
                PROGRAM_STATUS = gameWindowProcedureMessage.wParam;
            }

            else
                // Terminate
                Game::Terminate(gameWindowHandle, "Unable to create window", EXIT_FAILURE);

            // Deletion
            ::UnregisterClass(gameWindowClass.lpszClassName, gameWindowClass.hInstance);
        }

        else
            // Terminate
            Game::Terminate(0x0, "Unable to create window (due to failing window class)", EXIT_FAILURE);
    }

    /* Terminate */
    void Game::Terminate(void) { // NOTE (Lapys) -> Normal game termination.
        // Deletion
        std::free(Game::Map::boosters);
        std::free(Game::Map::fruits);
        std::free(Game::Map::walls);
        std::free(Game::Map::snakes);
        std::free(Game::Map::tiles);

        /* ... */
        Game::PHASE = Game::Phases::TERMINATING;

        // Global > ... Console ...
        // : Initialization > Bytes Written
        HANDLE activeScreenConsoleBufferHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO activeScreenConsoleBufferInformation;

        DWORD bytesWritten;

        // Update > ... Console ...
        ::SetConsoleActiveScreenBuffer(activeScreenConsoleBufferHandle);

        ::GetConsoleScreenBufferInfo(activeScreenConsoleBufferHandle, &activeScreenConsoleBufferInformation);
        ::FillConsoleOutputCharacter(activeScreenConsoleBufferHandle, ' ', activeScreenConsoleBufferInformation.dwSize.X * activeScreenConsoleBufferInformation.dwSize.Y, {0, 0}, &bytesWritten);
        ::SetConsoleCursorPosition(activeScreenConsoleBufferHandle, {0, 0});

        ::WriteConsoleOutputCharacter(activeScreenConsoleBufferHandle, "[PROGRAM TERMINATED]", 20, {0, 0}, &bytesWritten);

        // Deletion
        ::CloseHandle(activeScreenConsoleBufferHandle);
    }
    void Game::Terminate(HWND gameWindowHandle, const char message[], const int programStatus) { // NOTE (Lapys) -> Termination due to errors (Can retroactively be exploited to terminate the game without prompting the console).
        // Deletion
        std::free(Game::Map::boosters);
        std::free(Game::Map::fruits);
        std::free(Game::Map::walls);
        std::free(Game::Map::snakes);
        std::free(Game::Map::tiles);

        /* ...; Logic */
        Game::PHASE = Game::Phases::TERMINATING;
        if (message) {
            // Global > (Former) ... Console ...
            // : Initialization > Bytes Written
            HANDLE activeScreenConsoleBufferHandle = ::CreateFile("CONERR$", GENERIC_WRITE, FILE_SHARE_WRITE, 0x0, OPEN_ALWAYS, 0, 0x0);
            CONSOLE_SCREEN_BUFFER_INFO activeScreenConsoleBufferInformation;
            HANDLE formerActiveScreenConsoleBufferHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);

            DWORD bytesWritten;

            // Update > ... Console ...
            ::SetConsoleActiveScreenBuffer(activeScreenConsoleBufferHandle);
            ::GetConsoleScreenBufferInfo(activeScreenConsoleBufferHandle, &activeScreenConsoleBufferInformation);

            ::FillConsoleOutputCharacter(activeScreenConsoleBufferHandle, ' ', activeScreenConsoleBufferInformation.dwSize.X * activeScreenConsoleBufferInformation.dwSize.Y, {0, 0}, &bytesWritten);
            ::SetConsoleCursorPosition(activeScreenConsoleBufferHandle, {0, 0});

            // ...
            ::MessageBox(gameWindowHandle, message, "Error", MB_ICONERROR | MB_OK | MB_SETFOREGROUND);
            for (long iterator = 0L; *message; iterator++) ::WriteConsoleOutputCharacter(activeScreenConsoleBufferHandle, message++, 1, {(SHORT) iterator++, 0}, &bytesWritten);

            // Deletion; Update > Former ... Console ...
            ::CloseHandle(activeScreenConsoleBufferHandle);
            ::SetConsoleActiveScreenBuffer(formerActiveScreenConsoleBufferHandle);
        }

        // Terminate
        ::exit(PROGRAM_STATUS = programStatus);
    }
