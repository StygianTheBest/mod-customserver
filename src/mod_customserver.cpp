/*

# Custom Server Modifications #

### Description ###
------------------------------------------------------------------------------------------------------------------
- I built this module to makes testing and compiling features faster
- It is also is a place for smaller scripts that don't need their own module
- Config: Enable/Disable sub-scripts


### Data ###
------------------------------------------------------------------------------------------------------------------
- Type: Server/Player
- Script: CustomServer
- Config: Yes
- SQL: No


### Version ###
------------------------------------------------------------------------------------------------------------------
- v2017.09.03 - Release

### Credits ###
------------------------------------------------------------------------------------------------------------------
#### A module for AzerothCore by StygianTheBest ([stygianthebest.github.io](http://stygianthebest.github.io)) ####

###### Additional Credits include:
- [Blizzard Entertainment](http://blizzard.com)
- [TrinityCore](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/THANKS)
- [SunwellCore](http://www.azerothcore.org/pages/sunwell.pl/)
- [AzerothCore](https://github.com/AzerothCore/azerothcore-wotlk/graphs/contributors)
- [AzerothCore Discord](https://discord.gg/gkt4y2x)
- [EMUDevs](https://youtube.com/user/EmuDevs)
- [AC-Web](http://ac-web.org/)
- [ModCraft.io](http://modcraft.io/)
- [OwnedCore](http://ownedcore.com/)
- [OregonCore](https://wiki.oregon-core.net/)
- [Wowhead.com](http://wowhead.com)
- [AoWoW](https://wotlk.evowow.com/)


### License ###
------------------------------------------------------------------------------------------------------------------
- This code and content is released under the [GNU AGPL v3](https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3).

*/

#include "Config.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include <cstring>

bool CustomServerEnable = 1;
bool CustomServerAnnounceModule = 1;
bool CustomFireworkLevels = 1;

class CustomServerConfig : public WorldScript
{
public:
    CustomServerConfig() : WorldScript("CustomServerConfig_conf") { }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload) {
            std::string conf_path = _CONF_DIR;
            std::string cfg_file = conf_path + "/mod_customserver.conf";
#ifdef WIN32
            cfg_file = "mod_customserver.conf";
#endif
            std::string cfg_def_file = cfg_file + ".dist";
            sConfigMgr->LoadMore(cfg_def_file.c_str());
            sConfigMgr->LoadMore(cfg_file.c_str());

            CustomServerAnnounceModule = sConfigMgr->GetBoolDefault("CustomServer.Announce", 1);
            CustomFireworkLevels = sConfigMgr->GetIntDefault("CustomServer.FireworkLevels", 1);
        }
    }
};

class CustomServerAnnounce : public PlayerScript
{

public:

    CustomServerAnnounce() : PlayerScript("CustomServerAnnounce") {}

    void OnLogin(Player* player)
    {
        // Announce Module
        if (CustomServerAnnounceModule = true)
        {
            ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00CustomServer |rmodule.");
        }

    }
};

class CustomServer : public PlayerScript
{

public:

    CustomServer() : PlayerScript("CustomServer") { }

    void OnLevelChanged(Player * player, uint8 oldLevel)
    {
        // Shoot fireworks into the air when a player levels
        if (CustomFireworkLevels)
        {
            if (oldLevel == 4)
                player->CastSpell(player, 11541, true);

            if (oldLevel == 9)
                player->CastSpell(player, 11541, true);

            if (oldLevel == 14)
                player->CastSpell(player, 11541, true);

            if (oldLevel == 19)
                player->CastSpell(player, 11541, true);

            if (oldLevel == 29)
                player->CastSpell(player, 11541, true);

            if (oldLevel == 39)
                player->CastSpell(player, 11541, true);

            if (oldLevel == 49)
                player->CastSpell(player, 11541, true);

            if (oldLevel == 59)
                player->CastSpell(player, 11541, true);

            if (oldLevel == 69)
                player->CastSpell(player, 11541, true);

            if (oldLevel == 79)
                player->CastSpell(player, 11541, true);
        }

    }
};

void AddCustomServerScripts()
{
    new CustomServerConfig();
    new CustomServerAnnounce();
    new CustomServer();
}
