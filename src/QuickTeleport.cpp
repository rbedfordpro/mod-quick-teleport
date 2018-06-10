#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"

class QuickTeleport : public CommandScript{
public:

    QuickTeleport() : CommandScript("QuickTeleport") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> TeleportTable =
        {

            { "home", SEC_PLAYER, false, &HandleHomeTeleportCommand, "" },
            { "arena", SEC_PLAYER, false, &HandleArenaTeleportCommand, ""}

        };
        return TeleportTable;
    }

    static bool HandleHomeTeleportCommand(ChatHandler* handler, char const* args)
    {
        Player* me = handler->GetSession()->GetPlayer();
        QueryResult result = WorldDatabase.PQuery("SELECT `map`, `position_x`, `position_y`, `position_z`, `orientation` FROM game_tele WHERE name = 'Goldshire'");

        if (!me)
            return false;

        if (me->IsInCombat())
            return false;

        if (!result)
            return false;

        do
        {
            Field* fields = result->Fetch();
            uint32 map = fields[0].GetUInt32();
            float position_x = fields[1].GetFloat();
            float position_y = fields[2].GetFloat();
            float position_z = fields[3].GetFloat();
            float orientation = fields[4].GetFloat();

            me->TeleportTo(map, position_x, position_y, position_z, orientation);
        } while (result->NextRow());
    }

    static bool HandleArenaTeleportCommand(ChatHandler* handler, char const* args)
    {
        QueryResult result = WorldDatabase.PQuery("SELECT `map`, `position_x`, `position_y`, `position_z`, `orientation` FROM game_tele WHERE name = 'TheGreatArena'");
        Player* p = handler->GetSession()->GetPlayer();

        if (!p)
            return false;

        if (p->IsInCombat())
            return false;

        if (!result)
            return false;
            
        do
        {
            Field* fields = result->Fetch();
            uint32 map = fields[0].GetUInt32();
            float position_x = fields[1].GetFloat();
            float position_y = fields[2].GetFloat();
            float position_z = fields[3].GetFloat();
            float orientation = fields[4].GetFloat();

            p->TeleportTo(map, position_x, position_y, position_z, orientation);
        } while (result->NextRow());

    }

};

void AddQuickTeleportScripts() {
    new QuickTeleport();
}

