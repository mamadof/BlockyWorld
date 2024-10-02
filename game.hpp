#ifndef GAME_HPP
#define GAME_HPP

class CGame{
    public:
    void run();

    private:
    void init();
    void tick();
    void render();
    void close();
};
#endif //GAME_HPP