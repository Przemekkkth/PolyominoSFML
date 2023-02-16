#ifndef RESOURCE_IDENTIFIERS_H
#define RESOURCE_IDENTIFIERS_H
// Forward declaration of SFML classes
namespace sf
{
    class Texture;
    class Font;
    class Shader;
    class SoundBuffer;
}

namespace Textures
{
    enum ID
    {
        PolyominoString,
        Buttons,
        SFMLlogo,
        Blocks
    };
}

namespace Fonts
{
    enum ID
    {
        Main,
    };
}

namespace SoundEffect
{
    enum ID
    {
        AlliedGunfire,
        EnemyGunfire,
        Explosion1,
        Explosion2,
        LaunchMissile,
        CollectPickup,
        Button,
    };
}

namespace Music
{
    enum ID
    {
        MenuTheme,
        MissionTheme,
    };
}
// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	        TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			        FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;

#endif // RESOURCE_IDENTIFIERS_H
