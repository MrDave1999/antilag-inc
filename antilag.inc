#if !defined _INC_antilag
	#define _INC_antilag

#define SetPlayerAntiLag(%0,%1) \
	AntiLag[%0] = (%1)
	
#define IsPlayerAntiLag(%0) \
	(AntiLag[%0])

#if defined DS_OnPlayerGiveDamage
	forward DS_OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart);
#endif

#if defined DS_OnPlayerConnect
	forward DS_OnPlayerConnect(playerid);
#endif

new bool:AntiLag[MAX_PLAYERS];

public OnPlayerConnect(playerid)
{
	//printf("DEBUG: hook de OnPlayerConnect (antilag.inc)");
	SetPlayerAntiLag(playerid, false);
	#if !defined DS_OnPlayerConnect
	    return 1;
	#else
	    return DS_OnPlayerConnect(playerid);
	#endif
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	//printf("DEBUG: hook de OnPlayerGiveDamage (antilag.inc)");
	if(IsPlayerAntiLag(playerid))
	{
		new Float:armour;
		GetPlayerArmour(damagedid, armour);
		if(armour > 0)
		{
	    	SetPlayerArmour(damagedid, ((armour > amount) ? (armour-amount) : (0.0)));
			if(armour < amount)
				SetPlayerHealth(damagedid, 100.0-(amount-armour));
		}
		else
		{
			new Float:health;
			GetPlayerHealth(damagedid, health);
			SetPlayerHealth(damagedid, ((health > amount) ? (health-amount) : (0.0)));
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
#endif /* FIN _INC_antilag */
