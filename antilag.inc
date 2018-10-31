#if !defined _INC_antilag
	#define _INC_antilag

#pragma warning push
#pragma warning disable 213
#pragma warning disable 217

#define SetPlayerAntiLag(%0,%1) \
	a_Data[%0][AntiLag] = (%1)

#define IsPlayerAntiLag(%0) \
	(a_Data[%0][AntiLag])
	
#define TogglePlayerAntiLag(%0) \
	(a_Data[%0][AntiLag] = !a_Data[%0][AntiLag])
	
#define SetAllPlayersAntiLag(%0) for (new i = 0; i < MAX_PLAYERS; ++i) if (IsPlayerConnected(i)) if (!IsPlayerNPC(i)) SetPlayerAntiLag(i, %0)

#define ToggleAllPlayersAntiLag() for (new i = 0; i < MAX_PLAYERS; ++i) if (IsPlayerConnected(i)) if (!IsPlayerNPC(i)) TogglePlayerAntiLag(i)

#if defined DS_OnPlayerGiveDamage
	forward DS_OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart);
#endif

#if defined DS_OnPlayerConnect
	forward DS_OnPlayerConnect(playerid);
#endif

forward sPlayerArmour(playerid, float:armour);
forward sPlayerHealth(playerid, float:health);


enum aStruct
{
	bool:AntiLag,
	float:Armour,
	float:Health
};
new a_Data[MAX_PLAYERS][aStruct];

public OnPlayerConnect(playerid)
{
	SetPlayerAntiLag(playerid, false);
	#if !defined DS_OnPlayerConnect
	    return 1;
	#else
	    return DS_OnPlayerConnect(playerid);
	#endif
}

public sPlayerHealth(playerid, float:health)
{
	a_Data[playerid][Health] = health;
	SetPlayerHealth(playerid, a_Data[playerid][Health]);
}

public sPlayerArmour(playerid, float:armour)
{
	a_Data[playerid][Armour] = armour;
	SetPlayerArmour(playerid, a_Data[playerid][Armour]);
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	if(IsPlayerAntiLag(playerid))
	{
		new float:cArmour;
		GetPlayerArmour(damagedid, cArmour);
		if (cArmour != a_Data[damagedid][Armour]) SetPlayerArmour(damagedid, a_Data[damagedid][Armour]);
		
		if(a_Data[damagedid][Armour] > 0)
		{
	    	a_Data[damagedid][Armour] = ((a_Data[damagedid][Armour] > amount) ? (a_Data[damagedid][Armour] - amount) : (0.0));
	    	
	    	SetPlayerArmour(damagedid, a_Data[damagedid][Armour]);
	    	
			if(a_Data[damagedid][Armour] < amount)
				a_Data[damagedid][Health] = 100.0 - (amount - a_Data[damagedid][Armour]);
				SetPlayerHealth(damagedid, a_Data[damagedid][Health]);
		}
		else
		{
			new Float:cHealth;
			GetPlayerHealth(damagedid, cHealth);
			
			if (cHealth != a_Data[damagedid][Health]) SetPlayerHealth(damagedid, a_Data[damagedid][Health]);
			
			a_Data[damagedid][Health] = ((a_Data[damagedid][Health] > amount) ? (a_Data[damagedid][Health] - amount) : (0.0));
			SetPlayerHealth(damagedid, a_Data[damagedid][Health]);
		}
	}
	#if !defined DS_OnPlayerGiveDamage
	    return 1;
	#else
		return DS_OnPlayerGiveDamage(playerid, damagedid, amount, weaponid, bodypart);
	#endif
}
//================================================
#if !defined _ALS_OnPlayerGiveDamage
	#define _ALS_OnPlayerGiveDamage
#else
	#undef OnPlayerGiveDamage
#endif
#define OnPlayerGiveDamage DS_OnPlayerGiveDamage
//================================================
#if !defined _ALS_OnPlayerConnect
	#define _ALS_OnPlayerConnect
#else
	#undef OnPlayerConnect
#endif
#define OnPlayerConnect DS_OnPlayerConnect
//================================================
#if !defined _ALS_SetPlayerArmour
	#define _ALS_SetPlayerArmour
#else
	#undef SetPlayerArmour
#endif
#define SetPlayerArmour sPlayerArmour
//================================================
#if !defined _ALS_SetPlayerHealth
	#define _ALS_SetPlayerHealth
#else
	#undef SetPlayerHealth
#endif
#define SetPlayerHealth sPlayerHealth
//===============================================
#pragma warning pop
#endif /* FIN _INC_antilag */
