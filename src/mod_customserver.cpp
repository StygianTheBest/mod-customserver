/*

# Custom Server Modifications #

### Description ###
------------------------------------------------------------------------------------------------------------------
- Configuration settings for core modifications.
- Smaller scripts and features that aren't a module. 

### Data ###
------------------------------------------------------------------------------------------------------------------
- Type: Server/Player
- Script: CustomServer
- Config: Yes
- SQL: No


### Version ###
------------------------------------------------------------------------------------------------------------------
- v2018.12.18 - Add Dungeon Checkpoint, Time Cycle config options
- v2017.09.03 - Release


### Credits ###
------------------------------------------------------------------------------------------------------------------
#### An original module for AzerothCore by StygianTheBest ([stygianthebest.github.io](http://stygianthebest.github.io)) ####

- [Callmephil](https://github.com/callmephil)
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

#include <cstring>
#include "Config.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "DungeonCheckpoints.h"

bool AnnounceModule = true;
bool FireworkLevels = true;

bool Dynamic_Resurrection::IsInDungeonOrRaid(Player* player)
{
    if (sMapStore.LookupEntry(player->GetMapId())->Instanceable())
        return true; // boolean need to return to a value
    return false;
}

bool Dynamic_Resurrection::CheckForSpawnPoint(Player* player)
{
    // Find Nearest Creature And Teleport.
    if (Creature* creature = player->FindNearestCreature(C_Resurrection_ENTRY, C_DISTANCE_CHECK_RANGE))
        return true;
    return false;

}

class Dynamic_Resurrections : public PlayerScript
{
public:
    Dynamic_Resurrections() : PlayerScript("Dynamic_Resurrections") {}

    void OnCreatureKill(Player* player, Creature* boss) override
    {
        if (sDynRes->IsInDungeonOrRaid(player) && (boss->isWorldBoss() || boss->IsDungeonBoss()))
            player->SummonCreature(C_Resurrection_ENTRY, boss->GetPositionX(), boss->GetPositionY(), boss->GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, C_SPAWN_TIMER_TWO_HOURS);
    }
};

class CustomServerConfig : public WorldScript
{
public:
    CustomServerConfig() : WorldScript("CustomServerConfig") { }

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

            // Load Configuration Settings
            SetInitialWorldSettings();
        }
    }

    // Load Configuration Settings
    void SetInitialWorldSettings()
    {
        AnnounceModule = sConfigMgr->GetBoolDefault("CustomServer.Announce", true);
        FireworkLevels = sConfigMgr->GetBoolDefault("CustomServer.FireworkLevels", true);
    }
};

class CustomServerAnnounce : public PlayerScript
{

public:

    CustomServerAnnounce() : PlayerScript("CustomServerAnnounce") {}

    void OnLogin(Player* player)
    {
        // Announce Module
        if (AnnounceModule)
        {
            ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00CustomServer |rmodule.");
        }

    }
};

class CustomServer : public PlayerScript
{

public:

    CustomServer() : PlayerScript("CustomServer") { }

    void OnLogin(Player * player)
    {
        // #SCMOD#
        // Alter player run speed
        //player->SetSpeed(MOVE_RUN, 4.0, 1);

    }
    void OnLevelChanged(Player * player, uint8 oldLevel)
    {
        // Shoot fireworks into the air when a player levels
        if (FireworkLevels)
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
    new Dynamic_Resurrections();
    new CustomServerConfig();
    new CustomServerAnnounce();
    new CustomServer();
}
