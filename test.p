#include <a_samp>
#include <antilag>
#include <Pawn.CMD>

const AMMO = 99999;

main()
{
	//code
}

public OnPlayerSpawn(playerid)
{
	SetPlayerPos(playerid, 1360.5299, -24.5914, 1000.9219);
	SetPlayerInterior(playerid, 1);
	SetPlayerVirtualWorld(playerid, 0);
	GivePlayerWeapon(playerid, WEAPON_DEAGLE, AMMO);
	GivePlayerWeapon(playerid, WEAPON_SAWEDOFF, AMMO);
	GivePlayerWeapon(playerid, WEAPON_UZI, AMMO);
	GivePlayerWeapon(playerid, WEAPON_M4, AMMO);
	return 1;
}

cmd:test(playerid)
{
	SetPlayerAntiLag(playerid, true);
	return 1;
}
