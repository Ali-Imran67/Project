#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <memory>

using namespace std;
using namespace sf;

class SoundManager {
    private:
    map<string, SoundBuffer> buffers;
    map<string, unique_ptr<Sound>> sounds;

    public:

    void loadSound(string name, string directory);
    void play(string name);
    void stop(string name);
    void setLoop(string name, bool state);
    bool IsPlaying(string name);

};