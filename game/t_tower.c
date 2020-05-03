/*
==============================================================================

Tower

==============================================================================
*/

#include "g_local.h"



//
// ATTACK
//

static int blaster_flash[] = { MZ2_SOLDIER_BLASTER_1, MZ2_SOLDIER_BLASTER_2, MZ2_SOLDIER_BLASTER_3, MZ2_SOLDIER_BLASTER_4, MZ2_SOLDIER_BLASTER_5, MZ2_SOLDIER_BLASTER_6, MZ2_SOLDIER_BLASTER_7, MZ2_SOLDIER_BLASTER_8 };
static int shotgun_flash[] = { MZ2_SOLDIER_SHOTGUN_1, MZ2_SOLDIER_SHOTGUN_2, MZ2_SOLDIER_SHOTGUN_3, MZ2_SOLDIER_SHOTGUN_4, MZ2_SOLDIER_SHOTGUN_5, MZ2_SOLDIER_SHOTGUN_6, MZ2_SOLDIER_SHOTGUN_7, MZ2_SOLDIER_SHOTGUN_8 };
static int machinegun_flash[] = { MZ2_SOLDIER_MACHINEGUN_1, MZ2_SOLDIER_MACHINEGUN_2, MZ2_SOLDIER_MACHINEGUN_3, MZ2_SOLDIER_MACHINEGUN_4, MZ2_SOLDIER_MACHINEGUN_5, MZ2_SOLDIER_MACHINEGUN_6, MZ2_SOLDIER_MACHINEGUN_7, MZ2_SOLDIER_MACHINEGUN_8 };


void tower_pain(edict_t *self, edict_t *other, float kick, int damage)
{
	float	r;
	int		n;

	if (self->health < (self->max_health / 2))
		self->s.skinnum |= 1;


	self->pain_debounce_time = level.time + 3;

}
void tower_fire(edict_t *self, int flash_number)
{
	vec3_t	start;
	vec3_t	forward, right, up;
	vec3_t	aim;
	vec3_t	dir;
	vec3_t	end;
	float	r, u;
	int		flash_index;

	if (self->s.skinnum < 2)
		flash_index = blaster_flash[flash_number];
	else if (self->s.skinnum < 4)
		flash_index = shotgun_flash[flash_number];
	else
		flash_index = machinegun_flash[flash_number];

	AngleVectors(self->s.angles, forward, right, NULL);
	G_ProjectSource(self->s.origin, monster_flash_offset[flash_index], forward, right, start);

	if (flash_number == 5 || flash_number == 6)
	{
		VectorCopy(forward, aim);
	}
	else
	{
		VectorCopy(self->enemy->s.origin, end);
		end[2] += self->enemy->viewheight;
		VectorSubtract(end, start, aim);
		vectoangles(aim, dir);
		AngleVectors(dir, forward, right, up);

		r = crandom() * 1000;
		u = crandom() * 500;
		VectorMA(start, 8192, forward, end);
		VectorMA(end, r, right, end);
		VectorMA(end, u, up, end);

		VectorSubtract(end, start, aim);
		VectorNormalize(aim);
	}


	monster_fire_blaster(self, start, aim, 5, 600, flash_index, EF_BLASTER);
	

}

void tower_fire1(edict_t *self)
{
	tower_fire(self, 0);
}

mframe_t tower_frames_attack1[] =
{
	ai_charge, 0, NULL,
	//ai_charge, 0, NULL,
	ai_charge, 0, tower_fire1,
	//ai_charge, 0, NULL,
	//ai_charge, 0, NULL,
	//ai_charge, 0, NULL,
	//ai_charge, 0, NULL,
	//ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t tower_attack1 = { 0, 10, tower_frames_attack1, NULL};

void tower_attack(edict_t *self)
{
	if (random() < 0.5)
		self->monsterinfo.currentmove = &tower_attack1;
}

//
// SIGHT
//

void tower_sight(edict_t *self, edict_t *other)
{
	if ((skill->value > 0) && (range(self, self->enemy) >= RANGE_MID))
	{
		if (random() > 0.5)
			self->monsterinfo.currentmove = &tower_attack;
	}
}

//
// DEATH
//

void tower_dead(edict_t *self)
{
	VectorSet(self->mins, -16, -16, -24);
	VectorSet(self->maxs, 16, 16, -8);
	self->movetype = MOVETYPE_TOSS;
	self->svflags |= SVF_DEADMONSTER;
	self->nextthink = 0;
	gi.linkentity(self);
}


void tower_die(edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
	int		n;

	// regular death
	self->deadflag = DEAD_DEAD;
	self->takedamage = DAMAGE_YES;
	self->s.skinnum |= 1;


}


//
// SPAWN
//

void SP_tower_x(edict_t *self)
{

	
	self->s.modelindex = gi.modelindex("models/objects/barrels/tris.md2");
	
	self->monsterinfo.scale = 3;
	VectorSet(self->mins, -16, -16, -24);
	VectorSet(self->maxs, 16, 16, 32);
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	

	self->mass = 100;

	self->die = tower_die;
	self->monsterinfo.attack = tower_attack;
	self->monsterinfo.sight = tower_sight;

	/*

	self->monsterinfo.stand = NULL;
	self->monsterinfo.walk = NULL;
	self->monsterinfo.run = NULL;
	self->monsterinfo.dodge = NULL;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = NULL;

	*/
	gi.linkentity(self);

	self->monsterinfo.attack(self);


}


/*QUAKED monster_soldier_light (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight
*/
void SP_tower_1(edict_t *self)
{

	if (deathmatch->value)
	{
		G_FreeEdict(self);
		return;
	}

	SP_tower_x(self);


	self->health = 20;
	self->gib_health = -30;
}
