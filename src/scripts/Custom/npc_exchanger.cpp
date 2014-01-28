/* ScriptData
+SDName: Titles Giver NPC
+SD%Complete: 100
+SDComment: By Evrial
+SDCategory: NPC
+EndScriptData */

#include "ScriptPCH.h"

bool GossipHello_npc_exchanger(Player* pPlayer, Creature* pCreature)
{
	pPlayer->ADD_GOSSIP_ITEM( 0, "5000 Honor Points to 50 Arena Points", GOSSIP_SENDER_MAIN, 1000);
	pPlayer->ADD_GOSSIP_ITEM( 0, "30 Warsong Marks to 50 Arena points", GOSSIP_SENDER_MAIN, 2000);
	pPlayer->ADD_GOSSIP_ITEM( 0, "10 Coins of Voting to 150 Arena Points", GOSSIP_SENDER_MAIN, 3000);

	pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
	return true;
}

void SendDefaultMenu_npc_exchanger(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    // Not allowed if in combat.
    if (pPlayer->isInCombat())
    {
      pPlayer->CLOSE_GOSSIP_MENU();
      pCreature->MonsterSay("You are in combat!", LANG_UNIVERSAL, NULL);
      return;
    }

	int32 ap = 50;
	int32 honor = (-1)*5000;
    // Process menu selection
    switch(uiAction)
    { 
        case 1000:
			if (pPlayer->GetHonorPoints() < 5000)
			{
				pCreature->MonsterSay("You have not 5000 Honor points!", LANG_UNIVERSAL, NULL);
				pPlayer->CLOSE_GOSSIP_MENU();
				return;
			}
			pPlayer->ModifyHonorPoints(honor);
			pPlayer->ModifyArenaPoints(ap);
			pCreature->MonsterSay("5000 Honor Points EXCHANGED to 50 Arena Points!", LANG_UNIVERSAL, NULL);
            
            break;
        case 2000:
			if (!pPlayer->HasItemCount(20558, 30, true))
			{
				pCreature->MonsterSay("You have not 30 Warsong Marks!", LANG_UNIVERSAL, NULL);
				pPlayer->CLOSE_GOSSIP_MENU();
				return;
			}

			pPlayer->DestroyItemCount(20558, 30, true);
			pPlayer->ModifyArenaPoints(ap);
			pCreature->MonsterSay("30 Warsong Marks EXCHANGED to 50 Arena Points!", LANG_UNIVERSAL, NULL);

            break;
        case 3000:
			if (!pPlayer->HasItemCount(2021994, 10, true))
			{
				pCreature->MonsterSay("You have not 10 Coins of Voting!", LANG_UNIVERSAL, NULL);
				pPlayer->CLOSE_GOSSIP_MENU();
				return;
			}

			pPlayer->DestroyItemCount(2021994, 10, true);
			pPlayer->ModifyArenaPoints(ap);
			pPlayer->ModifyArenaPoints(ap);
			pPlayer->ModifyArenaPoints(ap);
			pCreature->MonsterSay("10 Coins of Voting EXCHANGED to 150 Arena Points!", LANG_UNIVERSAL, NULL);
            
            break;
	}
}

bool GossipSelect_npc_exchanger(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    // Show menu
    if (uiSender == GOSSIP_SENDER_MAIN)
        SendDefaultMenu_npc_exchanger(pPlayer, pCreature, uiAction);
    return true;
}

void AddSC_npc_exchanger()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "npc_exchanger";
    newscript->pGossipHello = &GossipHello_npc_exchanger;
    newscript->pGossipSelect = &GossipSelect_npc_exchanger;
    newscript->RegisterSelf();
}
