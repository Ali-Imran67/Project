#include "audio.hpp"

void SoundManager::loadSound(string name, string directory)
{
    SoundBuffer buffer;
    if (buffers[name].loadFromFile(directory))
    {
        sounds[name] = make_unique<Sound>(buffers[name]);
    }
}

void SoundManager::play(string name, float volume)
{
    if (sounds.count(name))
    {
        sounds[name]->setVolume(volume);
        sounds[name]->play();
    }
}

bool SoundManager::IsPlaying(string name) // modify to check for playing, stopped and paused.
{
    if (sounds.count(name))
    {
        return sounds[name]->getStatus() == SoundSource::Status::Playing;
    }
    return false;
}

void SoundManager::stop(string name)
{
    if (sounds.count(name))
    {
        sounds[name]->stop();
    }
}

void SoundManager::setLoop(string name, bool state)
{
    if (sounds.count(name))
    {
        sounds[name]->setLooping(state);
    }
}