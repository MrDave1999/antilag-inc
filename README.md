# antilag-inc

Con esta librería podrás crear zonas donde puedan disparar directamente al skin del jugador.

## Instalación

Debes agregar el fichero `antilag.inc` en el directorio `/pawno/include/`
```pawn
#include <a_samp>
#include <antilag> 
```

## Macros

- `SetPlayerAntiLag` = Con esta macro podrás activar/desactivar el skinshoot a un determinado jugador.

   **Ejemplo 1**:
   ```pawn
   SetPlayerAntiLag(playerid, true); //Esto activa el skinshoot
   ```
   **Ejemplo 2**:
   ```pawn
   SetPlayerAntiLag(playerid, false); //Esto desactiva el skinshoot
   ```

- `IsPlayerAntiLag` = Con esta macro podrás detectar sí el jugador está en una zona de skinshoot.

  **Ejemplo 1**:
  ```pawn
  if(IsPlayerAntiLag(playerid))
  {
	  print("El jugador está en una zona de skinshoot");
  }
  ```
   **Ejemplo 2**:
  ```pawn
  if(!IsPlayerAntiLag(playerid))
  {
	  print("El jugador no está en una zona de skinshoot");
  }
  ```

## Uso

Aquí te dejo un ejemplo completo usando el procesador de comandos [Pawn.CMD](https://github.com/urShadow/Pawn.CMD/releases)

```pawn
#include <a_samp>
#include <antilag>
#include <Pawn.CMD>

public OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
	if(IsPlayerAntiLag(playerid) && strcmp(cmd, "saliral", true) != 0)
	{
	    SendClientMessage(playerid, -1, "ERROR: Debes usar /saliral para poder salir de la zona");
	    return 0;
	}
	return 1;
}

cmd:antilag(playerid)
{
	if(IsPlayerAntiLag(playerid))
	    return SendClientMessage(playerid, -1, "ERROR: Usted ya está en una zona de antilag");
	SetPlayerAntiLag(playerid, true);
	SendClientMessage(playerid, -1, "Haz entrado a una área de skinshoot.");
	GivePlayerWeapon(playerid, 24, 500);
	return 1;
}

cmd:saliral(playerid)
{
	if(!IsPlayerAntiLag(playerid))
	    return SendClientMessage(playerid, -1, "ERROR: Usted no está en una zona de antilag");
	SetPlayerAntiLag(playerid, false);
	SpawnPlayer(playerid);
	return 1;
}
```

## Creditos

- [MrDave](https://github.com/MrDave1999)
- SA-MP Team
