/*----------------------------------------------------------------------------*\
							rGutils - Include
Description:
	This include contains several functions and macros
	to make scripting faster.
Version:
	1.0 - 02:41 08/07/2012 - lines: 693 - length: 27200
	1.1 - 17:42 08/07/2012 - lines: 694 - length: 27212
Changelog:
	-
Author:
	RuiGy.
Thanks to:
	SuperViper - Show me how to return a Float in a function.
\*----------------------------------------------------------------------------*/

#include <a_samp>

#if defined _rgut_included
	#endinput
#endif
#define _rgut_included

/*
native SetPlayerPosEx(playerid, Float:x, Float:y, Float:z, Float:a);
native IsPlayerInRangeOfVehicle(playerid, vehicleid, Float: radius);
native GetPlayerDistanceFromVehicle(playerid, vehicleid);
native GetPlayerDistanceFromPlayer(playerid, targetid);
native TeleportPlayerToVehicle(playerid, vehicleid);
native TeleportPlayerToPlayer(playerid, targetid);
native SendAdminMessage(color, const message[]);
native SetVehicleInterior(vehicleid, interior);
native GivePlayerWantedLevel(playerid, level);
native RemovePlayerWeapon(playerid, weaponid);
native GetVehicleEngineStatus(vehicleid);
native SetPlayerMoney(playerid, money);
native GetPlayerFacingAnglef(playerid);
native GetPlayerWeaponName(playerid);
native GetVehicleHealthf(vehicleid);
native GetVehicleZAnglef(vehicleid);
native FreezePlayer(playerid, time);
native IsVehicleOccupied(vehicleid);
native ClearPlayerScreen(playerid);
native GetPlayerArmourf(playerid);
native GetPlayerHealthf(playerid);
native IsPlayerSwimming(playerid);
native IsVehicleLocked(vehicleid);
native GetVehicleName(vehicleid);
native UnlockVehicle(vehicleid);
native GetWeaponNamef(weaponid);
native GetPlayerNamef(playerid);
native IsPlayerDriver(playerid);
native GetPlayerIpf(playerid);
native LockVehicle(vehicleid);
native FlipVehicle(vehicleid);
*/

forward OnPlayerUnfreeze(playerid);

#define SetVehicleInterior LinkVehicleToInterior

/*----------------------------------------------------------------------------*\
				This function checks if a player is a driver.
	Params:
		* playerid: id of the player to check.
\*----------------------------------------------------------------------------*/
stock IsPlayerDriver(playerid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) return true;
    return false;
}

/*----------------------------------------------------------------------------*\
				This function checks if a player is Swimming(check by anim).
	Params:
		* playerid: id of the player to check.
\*----------------------------------------------------------------------------*/
stock IsPlayerSwimming(playerid)
{
	if(IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return 0;
	new animlib[32], animname[32];
	GetAnimationName(GetPlayerAnimationIndex(playerid),animlib,32,animname,32);
	if(!strcmp(animlib, "SWIM", true) && !strcmp(animname, "SWIM_GLIDE", true))	return 1;
	else if(!strcmp(animlib, "SWIM", true) && !strcmp(animname, "SWIM_BREAST", true)) return 1;
	else if(!strcmp(animlib, "SWIM", true) && !strcmp(animname, "SWIM_CRAWL", true)) return 1;
	else if(!strcmp(animlib, "SWIM", true) && !strcmp(animname, "SWIM_DIVE_UNDER", true)) return 1;
	else if(!strcmp(animlib, "SWIM", true) && !strcmp(animname, "SWIM_DIVE_GLIDE", true)) return 1;
	else if(!strcmp(animlib, "SWIM", true) && !strcmp(animname, "SWIM_UNDER", true)) return 1;
	else if(!strcmp(animlib, "SWIM", true) && !strcmp(animname, "SWIM_TREAD", true)) return 1;
	return 0;
}

/*----------------------------------------------------------------------------*\
				This function returns the name of a player.
	Params:
		* playerid: id of the player to get the name.
\*----------------------------------------------------------------------------*/
stock GetPlayerNamef(playerid)
{
    new e_PLAYER_NAME[MAX_PLAYER_NAME];
    GetPlayerName(playerid, e_PLAYER_NAME, MAX_PLAYER_NAME);
	if(isnull(e_PLAYER_NAME)) e_PLAYER_NAME = "unknown";
    return e_PLAYER_NAME;
}

/*----------------------------------------------------------------------------*\
				This function returns the armour of a player .
	Params:
		* playerid: id of the player to get the armour.
\*----------------------------------------------------------------------------*/
stock Float:GetPlayerArmourf(playerid)
{
	new	Float:f_PLAYER_AMOUR;
	GetPlayerArmour(playerid, f_PLAYER_AMOUR);
	return f_PLAYER_AMOUR;
}

/*----------------------------------------------------------------------------*\
				This function returns the health of a player .
	Params:
		* playerid: id of the player to get the health.
\*----------------------------------------------------------------------------*/
stock Float:GetPlayerHealthf(playerid)
{
	new	Float:f_PLAYER_HEALTH;
	GetPlayerHealth(playerid, f_PLAYER_HEALTH);
	return f_PLAYER_HEALTH;
}

/*----------------------------------------------------------------------------*\
				This function returns the facing angle of a player
				.
	Params:
		* playerid: id of the player to get the f. angle.
\*----------------------------------------------------------------------------*/
stock Float:GetPlayerFacingAnglef(playerid)
{
	new	Float:f_PLAYER_ANGLE;
	GetPlayerFacingAngle(playerid, f_PLAYER_ANGLE);
	return f_PLAYER_ANGLE;
}

/*----------------------------------------------------------------------------*\
				This function returns the distance of a player from
				another player .
	Params:
		* playerid: id of the player to be the point.
		* targetid: id of the player to check the distance.
\*----------------------------------------------------------------------------*/
stock Float:GetPlayerDistanceFromPlayer(playerid, targetid)
{
	new	Float:fDist[3];
	GetPlayerPos(playerid, fDist[0], fDist[1], fDist[2]);
	return GetPlayerDistanceFromPoint(targetid, fDist[0], fDist[1], fDist[2]);
}

/*----------------------------------------------------------------------------*\
				This function returns the distance of a player from
				a vehicle .
	Params:
		* playerid: id of the player to be the point.
		* vehicleid: id of the player to check the distance.
\*----------------------------------------------------------------------------*/
stock Float:GetPlayerDistanceFromVehicle(playerid, vehicleid)
{
	new	Float:fDist[3];
	GetPlayerPos(playerid, fDist[0], fDist[1], fDist[2]);
	return GetVehicleDistanceFromPoint(vehicleid, fDist[0], fDist[1], fDist[2]);
}

/*----------------------------------------------------------------------------*\
				This function teleports a player to	an vehicle.
	Params:
		* playerid: id of the player to be teleported.
		* vehicleid: id of the vehicle to be the destination.
\*----------------------------------------------------------------------------*/
stock TeleportPlayerToVehicle(playerid, vehicleid)
{
	new	Float:fDist[3];
	GetVehiclePos(vehicleid, fDist[0], fDist[1], fDist[2]);
	SetPlayerPos(playerid, fDist[0], fDist[1], fDist[2]);
	return 1;
}

/*----------------------------------------------------------------------------*\
				This function teleports a player to	another player.
	Params:
		* playerid: id of the player to be teleported.
		* targetid: id of the player to be the destination.
\*----------------------------------------------------------------------------*/
stock TeleportPlayerToPlayer(playerid, targetid)
{
	new	Float:fDist[3];
	GetPlayerPos(targetid, fDist[0], fDist[1], fDist[2]);
	SetPlayerPos(playerid, fDist[0], fDist[1], fDist[2]);
	return 1;
}

/*----------------------------------------------------------------------------*\
				This function returns the if a player is in range of
				a vehicle.
	Params:
		* playerid:  id of the player to be the point.
		* vehicleid: id of the vehicle to check the distance.
		* radius: 	 the radius to check.
\*----------------------------------------------------------------------------*/
stock IsPlayerInRangeOfVehicle(playerid, vehicleid, Float: radius)
{
	new	Float:fDist[3];
	GetVehiclePos(vehicleid, fDist[0], fDist[1], fDist[2]);
	return IsPlayerInRangeOfPoint(playerid, radius, fDist[0], fDist[1], fDist[2]);
}

/*----------------------------------------------------------------------------*\
				This function returns the player's IP.
	Params:
		* playerid: id of the player to get the IP.
\*----------------------------------------------------------------------------*/
stock GetPlayerIpf(playerid)
{
	new e_PLAYER_IP[18];
	GetPlayerIp(playerid, e_PLAYER_IP, sizeof(e_PLAYER_IP));
    return e_PLAYER_IP;
}

/*----------------------------------------------------------------------------*\
				This function returns the player's weapon name.
	Params:
		* playerid: id of the player to get the weapon name.
\*----------------------------------------------------------------------------*/
stock GetPlayerWeaponName(playerid)
{	
    new e_WEAPON_NAME[21];
    GetWeaponName(GetPlayerWeapon(playerid), e_WEAPON_NAME, sizeof(e_WEAPON_NAME));
	if(isnull(e_WEAPON_NAME)) e_WEAPON_NAME = "unknown";
    return e_WEAPON_NAME;
}

/*----------------------------------------------------------------------------*\
				This function clear the player's screen.
	Params:
		* playerid: id of the player to clear screen.
\*----------------------------------------------------------------------------*/
stock ClearPlayerScreen(playerid)
{
	for(new i = 0; i < 100; i++){SendClientMessage(playerid, -1, " ");}
	return 0;
}

/*----------------------------------------------------------------------------*\
				This function sets the player's money.
	Params:
		* playerid: id of the player to set the money.
		* money:	the amount of money.
\*----------------------------------------------------------------------------*/
stock SetPlayerMoney(playerid, money)
{
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, money);
	return 1;
}

/*----------------------------------------------------------------------------*\
				This function sets the player's position and facing angle.
	Params:
		* playerid: id of the player to set the position and angle.
		* Float:x:	the position X.
		* Float:y:	the position Y.
		* Float:z:	the position Z.
		* Float:a:	the Angle.
\*----------------------------------------------------------------------------*/
stock SetPlayerPosEx(playerid, Float:x, Float:y, Float:z, Float:a)
{
	SetPlayerPos(playerid, x, y, z);
	SetPlayerFacingAngle(playerid, a);
	return 1;
}

/*----------------------------------------------------------------------------*\
				This function gives wanted level to player.
	Params:
		* playerid: id of the player to gain wanted level.
		* level:	the amount of levels.
\*----------------------------------------------------------------------------*/
stock GivePlayerWantedLevel(playerid, level)
{
	if(level + GetPlayerWantedLevel(playerid) > 6) return SetPlayerWantedLevel(playerid, 6);
	SetPlayerWantedLevel(playerid, GetPlayerWantedLevel(playerid)+level);
	return 1;
}

/*----------------------------------------------------------------------------*\
				This function freezes a player for a period.
	Params:
		* playerid: id of the player to freeze.
		* time:	the amount of time in miliseconds.
\*----------------------------------------------------------------------------*/
stock FreezePlayer(playerid, time = 5000)
{
	TogglePlayerControllable(playerid, false);
	SetTimerEx("OnPlayerUnfreeze", time, false, "i", playerid);
	return 1;
}

/*----------------------------------------------------------------------------*\
				This function remove an especific player's weapon.
	Params:
		* playerid:	 the id of the player to remove weapon.
		* weaponid:	 the id of the weapon to remove of.
\*----------------------------------------------------------------------------*/
stock RemovePlayerWeapon(playerid, weaponid)
{
	if(!IsPlayerConnected(playerid) || weaponid < 0 || weaponid > 46) return 0;

	new e_OLD_WEAPON[13], e_OLD_AMMO[13];

	for(new slot = 0; slot < 13; slot++) {
		GetPlayerWeaponData(playerid, slot, e_OLD_WEAPON[slot], e_OLD_AMMO[slot]);
	}

	ResetPlayerWeapons(playerid);

	for(new slot; slot < 13; slot++) {

		if(e_OLD_WEAPON[slot] == weaponid || e_OLD_AMMO[slot] == 0) {
			continue;
		}

		GivePlayerWeapon(playerid, e_OLD_WEAPON[slot], e_OLD_AMMO[slot]);
	}
	GivePlayerWeapon(playerid, 0, 1);
}

/*----------------------------------------------------------------------------*\
				This function return if a vehicle is occupied.
	Params:
		* vehicleid: id of the vehicle to check.
\*----------------------------------------------------------------------------*/
stock IsVehicleOccupied(vehicleid)
{
	for(new i = 0; i < MAX_PLAYERS; i++){if(IsPlayerInVehicle(i, vehicleid)) return 1;}
	return 0;
}

/*----------------------------------------------------------------------------*\
				This function returns the vehicle's name from modelid.
	Params:
		* vehicleid: id of the vehicle to get the the name.
\*----------------------------------------------------------------------------*/
stock GetVehicleName(vehicleid)
{
	new e_VEHICLE_NAME[22];
	switch(GetVehicleModel(vehicleid)) {
		case 400: e_VEHICLE_NAME = "Landstalker";
		case 401: e_VEHICLE_NAME = "Bravura";
		case 402: e_VEHICLE_NAME = "Buffalo";
		case 403: e_VEHICLE_NAME = "Linerunner";
		case 404: e_VEHICLE_NAME = "Perenniel";
		case 405: e_VEHICLE_NAME = "Sentinel";
		case 406: e_VEHICLE_NAME = "Dumper";
		case 407: e_VEHICLE_NAME = "Firetruck";
		case 408: e_VEHICLE_NAME = "Trashmaster";
		case 409: e_VEHICLE_NAME = "Stretch";
		case 410: e_VEHICLE_NAME = "Manana";
		case 411: e_VEHICLE_NAME = "Infernus";
		case 412: e_VEHICLE_NAME = "Voodoo";
		case 413: e_VEHICLE_NAME = "Pony";
		case 414: e_VEHICLE_NAME = "Mule";
		case 415: e_VEHICLE_NAME = "Cheetah";
		case 416: e_VEHICLE_NAME = "Ambulance";
		case 417: e_VEHICLE_NAME = "Leviathan";
		case 418: e_VEHICLE_NAME = "Moonbeam";
		case 419: e_VEHICLE_NAME = "Esperanto";
		case 420: e_VEHICLE_NAME = "Taxi";
		case 421: e_VEHICLE_NAME = "Washigton";
		case 422: e_VEHICLE_NAME = "Bobcat";
		case 423: e_VEHICLE_NAME = "Mr Whoopee";
		case 424: e_VEHICLE_NAME = "BF Injection";
		case 425: e_VEHICLE_NAME = "Hunter";
		case 426: e_VEHICLE_NAME = "Premier";
		case 427: e_VEHICLE_NAME = "Enforcer";
		case 428: e_VEHICLE_NAME = "Securicar";
		case 429: e_VEHICLE_NAME = "Banshee";
		case 430: e_VEHICLE_NAME = "Predator";
		case 431: e_VEHICLE_NAME = "Bus";
		case 432: e_VEHICLE_NAME = "Rhino";
		case 433: e_VEHICLE_NAME = "Barracks";
		case 434: e_VEHICLE_NAME = "Hotknife";
		case 435: e_VEHICLE_NAME = "Article Trailer";
		case 436: e_VEHICLE_NAME = "Previon";
		case 437: e_VEHICLE_NAME = "Coach";
		case 438: e_VEHICLE_NAME = "Cabbie";
		case 439: e_VEHICLE_NAME = "Stallion";
		case 440: e_VEHICLE_NAME = "Rumpo";
		case 441: e_VEHICLE_NAME = "RC Bandit";
		case 442: e_VEHICLE_NAME = "Romero";
		case 443: e_VEHICLE_NAME = "Packer";
		case 444: e_VEHICLE_NAME = "Monster";
		case 445: e_VEHICLE_NAME = "Admiral";
		case 446: e_VEHICLE_NAME = "Squallo";
		case 447: e_VEHICLE_NAME = "Seasparrow";
		case 448: e_VEHICLE_NAME = "Pizzaboy";
		case 449: e_VEHICLE_NAME = "Tram";
		case 450: e_VEHICLE_NAME = "Article Trailer 2";
		case 451: e_VEHICLE_NAME = "Turismo";
		case 452: e_VEHICLE_NAME = "Speeder";
		case 453: e_VEHICLE_NAME = "Reefer";
		case 454: e_VEHICLE_NAME = "Tropic";
		case 455: e_VEHICLE_NAME = "Flatbed";
		case 456: e_VEHICLE_NAME = "Yankee";
		case 457: e_VEHICLE_NAME = "Caddy";
		case 458: e_VEHICLE_NAME = "Solair";
		case 459: e_VEHICLE_NAME = "Topfun Van";
		case 460: e_VEHICLE_NAME = "Skimmer";
		case 461: e_VEHICLE_NAME = "PCJ-600";
		case 462: e_VEHICLE_NAME = "Faggio";
		case 463: e_VEHICLE_NAME = "Freeway";
		case 464: e_VEHICLE_NAME = "RC Baron";
		case 465: e_VEHICLE_NAME = "RC Raider";
		case 466: e_VEHICLE_NAME = "Glendale";
		case 467: e_VEHICLE_NAME = "Oceanic";
		case 468: e_VEHICLE_NAME = "Sanchez";
		case 469: e_VEHICLE_NAME = "Sparrow";
		case 470: e_VEHICLE_NAME = "Patriot";
		case 471: e_VEHICLE_NAME = "Quad";
		case 472: e_VEHICLE_NAME = "Coastguard";
		case 473: e_VEHICLE_NAME = "Dinghy";
		case 474: e_VEHICLE_NAME = "Hermes";
		case 475: e_VEHICLE_NAME = "Sabre";
		case 476: e_VEHICLE_NAME = "Rustler";
		case 477: e_VEHICLE_NAME = "ZR-350";
		case 478: e_VEHICLE_NAME = "Walton";
		case 479: e_VEHICLE_NAME = "Regina";
		case 480: e_VEHICLE_NAME = "Comet";
		case 481: e_VEHICLE_NAME = "BMX";
		case 482: e_VEHICLE_NAME = "Burrito";
		case 483: e_VEHICLE_NAME = "Camper";
		case 484: e_VEHICLE_NAME = "Marquis";
		case 485: e_VEHICLE_NAME = "Baggage";
		case 486: e_VEHICLE_NAME = "Dozer";
		case 487: e_VEHICLE_NAME = "Maverick";
		case 488: e_VEHICLE_NAME = "San News Maverick";
		case 489: e_VEHICLE_NAME = "Rancher";
		case 490: e_VEHICLE_NAME = "FBI Rancher";
		case 491: e_VEHICLE_NAME = "Virgo";
		case 492: e_VEHICLE_NAME = "Greenwood";
		case 493: e_VEHICLE_NAME = "Jetmax";
		case 494: e_VEHICLE_NAME = "Hotring Racer";
		case 495: e_VEHICLE_NAME = "Sandking";
		case 496: e_VEHICLE_NAME = "Blista Compact";
		case 497: e_VEHICLE_NAME = "Police Maverick";
		case 498: e_VEHICLE_NAME = "Boxville";
		case 499: e_VEHICLE_NAME = "Benson";
		case 500: e_VEHICLE_NAME = "Mesa";
		case 501: e_VEHICLE_NAME = "RC Goblin";
		case 502: e_VEHICLE_NAME = "Hotring Racer";
		case 503: e_VEHICLE_NAME = "Hotring Racer";
		case 504: e_VEHICLE_NAME = "Bloodring Banger";
		case 505: e_VEHICLE_NAME = "Rancher";
		case 506: e_VEHICLE_NAME = "Super GT";
		case 507: e_VEHICLE_NAME = "Elegant";
		case 508: e_VEHICLE_NAME = "Journey";
		case 509: e_VEHICLE_NAME = "Bike";
		case 510: e_VEHICLE_NAME = "Mountain Bike";
		case 511: e_VEHICLE_NAME = "Beagle";
		case 512: e_VEHICLE_NAME = "Cropduster";
		case 513: e_VEHICLE_NAME = "Stuntplane";
		case 514: e_VEHICLE_NAME = "Tanker";
		case 515: e_VEHICLE_NAME = "Roadtrain";
		case 516: e_VEHICLE_NAME = "Nebula";
		case 517: e_VEHICLE_NAME = "Majestic";
		case 518: e_VEHICLE_NAME = "Buccaneer";
		case 519: e_VEHICLE_NAME = "Shamal";
		case 520: e_VEHICLE_NAME = "Hydra";
		case 521: e_VEHICLE_NAME = "FCR-900";
		case 522: e_VEHICLE_NAME = "NRG-500";
		case 523: e_VEHICLE_NAME = "HPV-1000";
		case 524: e_VEHICLE_NAME = "Cement Truck";
		case 525: e_VEHICLE_NAME = "TowTruck";
		case 526: e_VEHICLE_NAME = "Fortune";
		case 527: e_VEHICLE_NAME = "Cadrona";
		case 528: e_VEHICLE_NAME = "FBI Truck";
		case 529: e_VEHICLE_NAME = "Willard";
		case 530: e_VEHICLE_NAME = "Forklift";
		case 531: e_VEHICLE_NAME = "Tractor";
		case 532: e_VEHICLE_NAME = "Combine Harvester";
		case 533: e_VEHICLE_NAME = "Feltzer";
		case 534: e_VEHICLE_NAME = "Remington";
		case 535: e_VEHICLE_NAME = "Slamvan";
		case 536: e_VEHICLE_NAME = "Blade";
		case 537: e_VEHICLE_NAME = "Freight (Train)";
		case 538: e_VEHICLE_NAME = "Brownstreak (Train)";
		case 539: e_VEHICLE_NAME = "Vortex";
		case 540: e_VEHICLE_NAME = "Vincent";
		case 541: e_VEHICLE_NAME = "Bullet";
		case 542: e_VEHICLE_NAME = "Clover";
		case 543: e_VEHICLE_NAME = "Sadler";
		case 544: e_VEHICLE_NAME = "Firetruck LA";
		case 545: e_VEHICLE_NAME = "Hustler";
		case 546: e_VEHICLE_NAME = "Intruder";
		case 547: e_VEHICLE_NAME = "Primo";
		case 548: e_VEHICLE_NAME = "Cargobob";
		case 549: e_VEHICLE_NAME = "Tampa";
		case 550: e_VEHICLE_NAME = "Sunrise";
		case 551: e_VEHICLE_NAME = "Merit";
		case 552: e_VEHICLE_NAME = "Utility Van";
		case 553: e_VEHICLE_NAME = "Nevada";
		case 554: e_VEHICLE_NAME = "Yosemite";
		case 555: e_VEHICLE_NAME = "Windsor";
		case 556: e_VEHICLE_NAME = "Monster ''A''";
		case 557: e_VEHICLE_NAME = "Monster ''B''";
		case 558: e_VEHICLE_NAME = "Uranus";
		case 559: e_VEHICLE_NAME = "Jester";
		case 560: e_VEHICLE_NAME = "Sultan";
		case 561: e_VEHICLE_NAME = "Stratum";
		case 562: e_VEHICLE_NAME = "Elegy";
		case 563: e_VEHICLE_NAME = "Raindance";
		case 564: e_VEHICLE_NAME = "RC Tiger";
		case 565: e_VEHICLE_NAME = "Flash";
		case 566: e_VEHICLE_NAME = "Tahoma";
		case 567: e_VEHICLE_NAME = "Savanna";
		case 568: e_VEHICLE_NAME = "Bandito";
		case 569: e_VEHICLE_NAME = "Freight Flat Trailer";
		case 570: e_VEHICLE_NAME = "Streak Trailer";
		case 571: e_VEHICLE_NAME = "Kart";
		case 572: e_VEHICLE_NAME = "Mower";
		case 573: e_VEHICLE_NAME = "Dune";
		case 574: e_VEHICLE_NAME = "Sweeper";
		case 575: e_VEHICLE_NAME = "Broadway";
		case 576: e_VEHICLE_NAME = "Tornado";
		case 577: e_VEHICLE_NAME = "AT400";
		case 578: e_VEHICLE_NAME = "DFT-30";
		case 579: e_VEHICLE_NAME = "Huntley";
		case 580: e_VEHICLE_NAME = "Stafford";
		case 581: e_VEHICLE_NAME = "BF-400";
		case 582: e_VEHICLE_NAME = "Newsvan";
		case 583: e_VEHICLE_NAME = "Tug";
		case 584: e_VEHICLE_NAME = "Petrol Trailer";
		case 585: e_VEHICLE_NAME = "Emperor";
		case 586: e_VEHICLE_NAME = "Wayfarer";
		case 587: e_VEHICLE_NAME = "Euros";
		case 588: e_VEHICLE_NAME = "Hotdog";
		case 589: e_VEHICLE_NAME = "Club";
		case 590: e_VEHICLE_NAME = "Freight Box Trailer";
		case 591: e_VEHICLE_NAME = "Article Trailer 3";
		case 592: e_VEHICLE_NAME = "Andromada";
		case 593: e_VEHICLE_NAME = "Dodo";
		case 594: e_VEHICLE_NAME = "RC Cam";
		case 595: e_VEHICLE_NAME = "Launch";
		case 596: e_VEHICLE_NAME = "Police Car (LSPD)";
		case 597: e_VEHICLE_NAME = "Police Car (SFPD)";
		case 598: e_VEHICLE_NAME = "Police Car (LVPD)";
		case 599: e_VEHICLE_NAME = "Police Ranger";
		case 600: e_VEHICLE_NAME = "Picador";
		case 601: e_VEHICLE_NAME = "S.W.A.T";
		case 602: e_VEHICLE_NAME = "Alpha";
		case 603: e_VEHICLE_NAME = "Phoenix";
		case 604: e_VEHICLE_NAME = "Glendale Shit";
		case 605: e_VEHICLE_NAME = "Sadler Shit";
		case 606: e_VEHICLE_NAME = "Baggage Trailer ''A''";
		case 607: e_VEHICLE_NAME = "Baggage Trailer ''B''";
		case 608: e_VEHICLE_NAME = "Tug Stairs Trailer";
		case 609: e_VEHICLE_NAME = "Boxville";
		case 610: e_VEHICLE_NAME = "Farm Trailer";
		case 611: e_VEHICLE_NAME = "Utility Trailer";
		default: e_VEHICLE_NAME = "unknown";
	}
	return e_VEHICLE_NAME;
}

/*----------------------------------------------------------------------------*\
				This function returns the vehicle Z angle .
	Params:
		* vehicleid: id of the vehicle to get the Z angle.
\*----------------------------------------------------------------------------*/
stock Float:GetVehicleZAnglef(vehicleid)
{
	new	Float:f_VEHICLE_ANGLE;
	GetVehicleZAngle(vehicleid, f_VEHICLE_ANGLE);
	return f_VEHICLE_ANGLE;
}

/*----------------------------------------------------------------------------*\
				This function returns the health of a vehicle .
	Params:
		* vehicleid: id of the vehicle to get the health.
\*----------------------------------------------------------------------------*/
stock Float:GetVehicleHealthf(vehicleid)
{
	new	Float:f_VEHICLE_HEALTH;
	GetVehicleHealth(vehicleid, f_VEHICLE_HEALTH);
	return f_VEHICLE_HEALTH;
}

/*----------------------------------------------------------------------------*\
				This function checks vehicle's engine status.
	Params:
		* vehicleid: id of the vehicle to check.
\*----------------------------------------------------------------------------*/
stock GetVehicleEngineStatus(vehicleid)
{
	new v_ENGINE, v_LIGHTS, v_ALARM, v_DOORS, v_BONNET, v_BOOT, v_OBJECTIVE;
    GetVehicleParamsEx(vehicleid, v_ENGINE, v_LIGHTS, v_ALARM, v_DOORS, v_BONNET, v_BOOT, v_OBJECTIVE);
	if(v_ENGINE == VEHICLE_PARAMS_ON) return 1;
	return 0;
}

/*----------------------------------------------------------------------------*\
				This function checks if a vehicle is locked.
	Params:
		* vehicleid: id of the vehicle to check.
\*----------------------------------------------------------------------------*/
stock IsVehicleLocked(vehicleid)
{
	new v_ENGINE, v_LIGHTS, v_ALARM, v_DOORS, v_BONNET, v_BOOT, v_OBJECTIVE;
    GetVehicleParamsEx(vehicleid, v_ENGINE, v_LIGHTS, v_ALARM, v_DOORS, v_BONNET, v_BOOT, v_OBJECTIVE);
	if(v_DOORS == true) return 1;
	return 0;
}

/*----------------------------------------------------------------------------*\
				This function flips a vehicle.
	Params:
		* vehicleid: id of the vehicle to flip.
\*----------------------------------------------------------------------------*/
stock FlipVehicle(vehicleid)
{
	SetVehicleZAngle(vehicleid, GetVehicleZAnglef(vehicleid));
	return 0;
}

/*----------------------------------------------------------------------------*\
				This function locks a vehicle.
	Params:
		* vehicleid: id of the vehicle to lock.
\*----------------------------------------------------------------------------*/
stock LockVehicle(vehicleid)
{
	new v_ENGINE, v_LIGHTS, v_ALARM, v_DOORS, v_BONNET, v_BOOT, v_OBJECTIVE;
    GetVehicleParamsEx(vehicleid, v_ENGINE, v_LIGHTS, v_ALARM, v_DOORS, v_BONNET, v_BOOT, v_OBJECTIVE);
	SetVehicleParamsEx(vehicleid, v_ENGNIE, v_LIGHTS, v_ALARM, true, v_BONNET, v_BOOT, v_OBJECTIVE);
	return 0;
}

/*----------------------------------------------------------------------------*\
				This function unlocks a vehicle.
	Params:
		* vehicleid: id of the vehicle to unlock.
\*----------------------------------------------------------------------------*/
stock UnlockVehicle(vehicleid)
{
	new v_ENGINE, v_LIGHTS, v_ALARM, v_DOORS, v_BONNET, v_BOOT, v_OBJECTIVE;
    GetVehicleParamsEx(vehicleid, v_ENGINE, v_LIGHTS, v_ALARM, v_DOORS, v_BONNET, v_BOOT, v_OBJECTIVE);
	SetVehicleParamsEx(vehicleid, v_ENGNIE, v_LIGHTS, v_ALARM, false, v_BONNET, v_BOOT, v_OBJECTIVE);
	return 0;
}

/*----------------------------------------------------------------------------*\
				This function return the name of a weapon.
	Params:
		* weaponid: id of the weapon to get the name.
\*----------------------------------------------------------------------------*/
stock GetWeaponNamef(weaponid)
{	
    new e_WEAPON_NAME[21];
    GetWeaponName(weaponid, e_WEAPON_NAME, sizeof(e_WEAPON_NAME));
	if(isnull(e_WEAPON_NAME)) e_WEAPON_NAME = "unknown";
    return e_WEAPON_NAME;
}

/*----------------------------------------------------------------------------*\
				This function sends a message to rcon admins.
	Params:
		* color:		 the color.
		* const message: the message to send.
\*----------------------------------------------------------------------------*/
stock SendAdminMessage(color, const message[])
{	
    for(new i = 0; i < MAX_PLAYERS; i++){
		if(IsPlayerAdmin(i)){
			SendClientMessage(i, color, message);
		}
	}
    return 1;
}

/*----------------------------------------------------------------------------*\
				This callback is called when a player is un-frozen.
	Params:
		* playerid:	 the id of the player who was frozen.
\*----------------------------------------------------------------------------*/
public OnPlayerUnfreeze(playerid)
{
	TogglePlayerControllable(playerid, true);
	return 1;
}