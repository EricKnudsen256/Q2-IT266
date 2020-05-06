/*
Copyright (C) 1997-2001 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
/*
==============================================================================

tower

==============================================================================
*/

#include "g_local.h"
#include "m_soldier.h"


static int	sound_idle;
static int	sound_sight1;
static int	sound_sight2;
static int	sound_pain_light;
static int	sound_pain;
static int	sound_pain_ss;
static int	sound_death_light;
static int	sound_death;
static int	sound_death_ss;
static int	sound_cock;


void tower_idle(edict_t *self)
{
	if (random() > 0.8)
		gi.sound(self, CHAN_VOICE, sound_idle, 1, ATTN_IDLE, 0);
}

void tower_cock(edict_t *self)
{
	if (self->s.frame == FRAME_stand322)
		gi.sound(self, CHAN_WEAPON, sound_cock, 1, ATTN_IDLE, 0);
	else
		gi.sound(self, CHAN_WEAPON, sound_cock, 1, ATTN_NORM, 0);
}


// STAND

void tower_stand(edict_t *self);

mframe_t tower_frames_stand1[] =
{
	ai_stand, 0, tower_idle,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
mmove_t tower_move_stand1 = { FRAME_stand101, FRAME_stand130, tower_frames_stand1, tower_stand };

mframe_t tower_frames_stand3[] =
{
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, tower_cock,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
mmove_t tower_move_stand3 = { FRAME_stand301, FRAME_stand339, tower_frames_stand3, tower_stand };

#if 0
mframe_t tower_frames_stand4[] =
{
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 4, NULL,
	ai_stand, 1, NULL,
	ai_stand, -1, NULL,
	ai_stand, -2, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
mmove_t tower_move_stand4 = { FRAME_stand401, FRAME_stand452, tower_frames_stand4, NULL };
#endif

void tower_stand(edict_t *self)
{
	if ((self->monsterinfo.currentmove == &tower_move_stand3) || (random() < 0.8))
		self->monsterinfo.currentmove = &tower_move_stand1;
	else
		self->monsterinfo.currentmove = &tower_move_stand3;
}


//
// WALK
//



mframe_t tower_frames_walk1[] =
{
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL,
	ai_walk, 0, NULL
};
mmove_t tower_move_walk1 = { FRAME_walk101, FRAME_walk133, tower_frames_walk1, NULL };



void tower_walk(edict_t *self)
{
	self->monsterinfo.currentmove = &tower_move_walk1;
}


//
// RUN
//

void tower_run(edict_t *self);

mframe_t tower_frames_start_run[] =
{
	ai_run, 0, NULL,
	ai_run, 0, NULL
};
mmove_t tower_move_start_run = { FRAME_stand101, FRAME_stand101, tower_frames_start_run, tower_run };

mframe_t tower_frames_run[] =
{
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL
};
mmove_t tower_move_run = { FRAME_stand101, FRAME_stand101, tower_frames_run, NULL };

void tower_run(edict_t *self)
{
	
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
	{
		self->monsterinfo.currentmove = &tower_move_stand1;
		return;
	}

	if (self->monsterinfo.currentmove == &tower_move_walk1 ||
		self->monsterinfo.currentmove == &tower_move_start_run)
	{
		self->monsterinfo.currentmove = &tower_move_run;
	}
	else
	{
		self->monsterinfo.currentmove = &tower_move_start_run;
	}
	

}


//
// PAIN
//

mframe_t tower_frames_pain1[] =
{
	ai_move, -3, NULL,
	ai_move, 4, NULL,
	ai_move, 1, NULL,
	ai_move, 1, NULL,
	ai_move, 0, NULL
};
mmove_t tower_move_pain1 = { FRAME_pain101, FRAME_pain105, tower_frames_pain1, tower_run };

mframe_t tower_frames_pain2[] =
{
	ai_move, -13, NULL,
	ai_move, -1, NULL,
	ai_move, 2, NULL,
	ai_move, 4, NULL,
	ai_move, 2, NULL,
	ai_move, 3, NULL,
	ai_move, 2, NULL
};
mmove_t tower_move_pain2 = { FRAME_pain201, FRAME_pain207, tower_frames_pain2, tower_run };

mframe_t tower_frames_pain3[] =
{
	ai_move, -8, NULL,
	ai_move, 10, NULL,
	ai_move, -4, NULL,
	ai_move, -1, NULL,
	ai_move, -3, NULL,
	ai_move, 0, NULL,
	ai_move, 3, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 1, NULL,
	ai_move, 0, NULL,
	ai_move, 1, NULL,
	ai_move, 2, NULL,
	ai_move, 4, NULL,
	ai_move, 3, NULL,
	ai_move, 2, NULL
};
mmove_t tower_move_pain3 = { FRAME_pain301, FRAME_pain318, tower_frames_pain3, tower_run };

mframe_t tower_frames_pain4[] =
{
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, -10, NULL,
	ai_move, -6, NULL,
	ai_move, 8, NULL,
	ai_move, 4, NULL,
	ai_move, 1, NULL,
	ai_move, 0, NULL,
	ai_move, 2, NULL,
	ai_move, 5, NULL,
	ai_move, 2, NULL,
	ai_move, -1, NULL,
	ai_move, -1, NULL,
	ai_move, 3, NULL,
	ai_move, 2, NULL,
	ai_move, 0, NULL
};
mmove_t tower_move_pain4 = { FRAME_pain401, FRAME_pain417, tower_frames_pain4, tower_run };


void tower_pain(edict_t *self, edict_t *other, float kick, int damage)
{

	self->health = 100000;
}


//
// ATTACK
//

static int blaster_flash[] = { MZ2_SOLDIER_BLASTER_1, MZ2_SOLDIER_BLASTER_2, MZ2_SOLDIER_BLASTER_3, MZ2_SOLDIER_BLASTER_4, MZ2_SOLDIER_BLASTER_5, MZ2_SOLDIER_BLASTER_6, MZ2_SOLDIER_BLASTER_7, MZ2_SOLDIER_BLASTER_8 };
static int shotgun_flash[] = { MZ2_SOLDIER_SHOTGUN_1, MZ2_SOLDIER_SHOTGUN_2, MZ2_SOLDIER_SHOTGUN_3, MZ2_SOLDIER_SHOTGUN_4, MZ2_SOLDIER_SHOTGUN_5, MZ2_SOLDIER_SHOTGUN_6, MZ2_SOLDIER_SHOTGUN_7, MZ2_SOLDIER_SHOTGUN_8 };
static int machinegun_flash[] = { MZ2_SOLDIER_MACHINEGUN_1, MZ2_SOLDIER_MACHINEGUN_2, MZ2_SOLDIER_MACHINEGUN_3, MZ2_SOLDIER_MACHINEGUN_4, MZ2_SOLDIER_MACHINEGUN_5, MZ2_SOLDIER_MACHINEGUN_6, MZ2_SOLDIER_MACHINEGUN_7, MZ2_SOLDIER_MACHINEGUN_8 };

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

		r = crandom() * 1;
		u = crandom() * 1;
		VectorMA(start, 8192, forward, end);
		VectorMA(end, r, right, end);
		VectorMA(end, u, up, end);

		VectorSubtract(end, start, aim);
		VectorNormalize(aim);
	}

	if (self->s.skinnum <= 1)
	{
		monster_fire_blaster(self, start, aim, 100, 600, flash_index, EF_BLASTER);
	}
	else if (self->s.skinnum <= 3)
	{
		monster_fire_shotgun(self, start, aim, 2, 1, DEFAULT_SHOTGUN_HSPREAD, DEFAULT_SHOTGUN_VSPREAD, DEFAULT_SHOTGUN_COUNT, flash_index);
	}
	else
	{
		if (!(self->monsterinfo.aiflags & AI_HOLD_FRAME))
			self->monsterinfo.pausetime = level.time + (3 + rand() % 8) * FRAMETIME;

		monster_fire_bullet(self, start, aim, 2, 4, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, flash_index);

		if (level.time >= self->monsterinfo.pausetime)
			self->monsterinfo.aiflags &= ~AI_HOLD_FRAME;
		else
			self->monsterinfo.aiflags |= AI_HOLD_FRAME;
	}
}

// ATTACK1 (blaster/shotgun)

void tower_fire1(edict_t *self)
{
	tower_fire(self, 0);
}

void tower_attack1_refire1(edict_t *self)
{

	if (self->enemy->health <= 0)
		return;

	if ((range(self, self->enemy) <= RANGE_NEAR))
		self->monsterinfo.nextframe = FRAME_attak102;

}

void tower_attack1_refire2(edict_t *self)
{


	if (self->enemy->health <= 0)
		return;

	//if (((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE))
		//self->monsterinfo.nextframe = FRAME_attak102;
}

mframe_t tower_frames_attack1[] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, tower_fire1,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, tower_attack1_refire1,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t tower_move_attack1 = { FRAME_attak101, FRAME_attak112, tower_frames_attack1, tower_run };

// ATTACK2 (blaster/shotgun)

void tower_fire2(edict_t *self)
{
	tower_fire(self, 1);
}

void tower_attack2_refire1(edict_t *self)
{
	if (self->s.skinnum > 1)
		return;

	if (self->enemy->health <= 0)
		return;

	if (((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_NEAR))
		self->monsterinfo.nextframe = FRAME_attak204;
	else
		self->monsterinfo.nextframe = FRAME_attak216;
}

void tower_attack2_refire2(edict_t *self)
{
	if (self->s.skinnum < 2)
		return;

	if (self->enemy->health <= 0)
		return;

	if (((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) <= RANGE_FAR))
		self->monsterinfo.nextframe = FRAME_attak204;
}

mframe_t tower_frames_attack2[] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, tower_fire2,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, tower_attack2_refire1,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, tower_cock,
	ai_charge, 0, NULL,
	ai_charge, 0, tower_attack2_refire2,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t tower_move_attack2 = { FRAME_attak201, FRAME_attak218, tower_frames_attack2, tower_run };

// ATTACK3 (duck and shoot)

void tower_duck_down(edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_DUCKED)
		return;
	self->monsterinfo.aiflags |= AI_DUCKED;
	self->maxs[2] -= 32;
	self->takedamage = DAMAGE_YES;
	self->monsterinfo.pausetime = level.time + 1;
	gi.linkentity(self);
}

void tower_duck_up(edict_t *self)
{
	self->monsterinfo.aiflags &= ~AI_DUCKED;
	self->maxs[2] += 32;
	self->takedamage = DAMAGE_AIM;
	gi.linkentity(self);
}

void tower_fire3(edict_t *self)
{
	tower_duck_down(self);
	tower_fire(self, 2);
}

void tower_attack3_refire(edict_t *self)
{
	if ((level.time + 0.4) < self->monsterinfo.pausetime)
		self->monsterinfo.nextframe = FRAME_attak303;
}

mframe_t tower_frames_attack3[] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, tower_fire3,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, tower_attack3_refire,
	ai_charge, 0, tower_duck_up,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t tower_move_attack3 = { FRAME_attak301, FRAME_attak309, tower_frames_attack3, tower_run };

// ATTACK4 (machinegun)

void tower_fire4(edict_t *self)
{
	tower_fire(self, 3);
	//
	//	if (self->enemy->health <= 0)
	//		return;
	//
	//	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
	//		self->monsterinfo.nextframe = FRAME_attak402;
}

mframe_t tower_frames_attack4[] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, tower_fire4,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t tower_move_attack4 = { FRAME_attak401, FRAME_attak406, tower_frames_attack4, tower_run };

#if 0
// ATTACK5 (prone)

void tower_fire5(edict_t *self)
{
	tower_fire(self, 4);
}

void tower_attack5_refire(edict_t *self)
{
	if (self->enemy->health <= 0)
		return;

	if (((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE))
		self->monsterinfo.nextframe = FRAME_attak505;
}

mframe_t tower_frames_attack5[] =
{
	ai_charge, 8, NULL,
	ai_charge, 8, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, tower_fire5,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, tower_attack5_refire
};
mmove_t tower_move_attack5 = { FRAME_attak501, FRAME_attak508, tower_frames_attack5, tower_run };
#endif

// ATTACK6 (run & shoot)

void tower_fire8(edict_t *self)
{
	tower_fire(self, 7);
}

void tower_attack6_refire(edict_t *self)
{
	if (self->enemy->health <= 0)
		return;

	if (range(self, self->enemy) < RANGE_MID)
		return;

	if (skill->value == 3)
		self->monsterinfo.nextframe = FRAME_runs03;
}

mframe_t tower_frames_attack6[] =
{
	ai_charge, 10, NULL,
	ai_charge, 4, NULL,
	ai_charge, 12, NULL,
	ai_charge, 11, tower_fire8,
	ai_charge, 13, NULL,
	ai_charge, 18, NULL,
	ai_charge, 15, NULL,
	ai_charge, 14, NULL,
	ai_charge, 11, NULL,
	ai_charge, 8, NULL,
	ai_charge, 11, NULL,
	ai_charge, 12, NULL,
	ai_charge, 12, NULL,
	ai_charge, 17, tower_attack6_refire
};
mmove_t tower_move_attack6 = { FRAME_runs01, FRAME_runs14, tower_frames_attack6, tower_run };

void tower_attack(edict_t *self)
{

	self->monsterinfo.currentmove = &tower_move_attack1;

}


//
// SIGHT
//

void tower_sight(edict_t *self, edict_t *other)
{
	
	if ((range(self, self->enemy) <= RANGE_NEAR))
	{
		self->monsterinfo.currentmove = &tower_move_attack1;
	}
	
}

//
// DUCK
//

void tower_duck_hold(edict_t *self)
{
	if (level.time >= self->monsterinfo.pausetime)
		self->monsterinfo.aiflags &= ~AI_HOLD_FRAME;
	else
		self->monsterinfo.aiflags |= AI_HOLD_FRAME;
}

mframe_t tower_frames_duck[] =
{
	ai_move, 5, tower_duck_down,
	ai_move, -1, tower_duck_hold,
	ai_move, 1, NULL,
	ai_move, 0, tower_duck_up,
	ai_move, 5, NULL
};
mmove_t tower_move_duck = { FRAME_duck01, FRAME_duck05, tower_frames_duck, tower_run };

void tower_dodge(edict_t *self, edict_t *attacker, float eta)
{
	/*
	float	r;

	r = random();
	if (r > 0.25)
		return;

	if (!self->enemy)
		self->enemy = attacker;

	if (skill->value == 0)
	{
		self->monsterinfo.currentmove = &tower_move_duck;
		return;
	}

	self->monsterinfo.pausetime = level.time + eta + 0.3;
	r = random();

	if (skill->value == 1)
	{
		if (r > 0.33)
			self->monsterinfo.currentmove = &tower_move_duck;
		else
			self->monsterinfo.currentmove = &tower_move_attack3;
		return;
	}

	if (skill->value >= 2)
	{
		if (r > 0.66)
			self->monsterinfo.currentmove = &tower_move_duck;
		else
			self->monsterinfo.currentmove = &tower_move_attack3;
		return;
	}

	self->monsterinfo.currentmove = &tower_move_attack3;
	*/
}


//
// DEATH
//

void tower_fire6(edict_t *self)
{
	tower_fire(self, 5);
}

void tower_fire7(edict_t *self)
{
	tower_fire(self, 6);
}

void tower_dead(edict_t *self)
{
	VectorSet(self->mins, -16, -16, -24);
	VectorSet(self->maxs, 16, 16, -8);
	self->movetype = MOVETYPE_TOSS;
	self->svflags |= SVF_DEADMONSTER;
	self->nextthink = 0;
	gi.linkentity(self);
}

mframe_t tower_frames_death1[] =
{
	ai_move, 0, NULL,
	ai_move, -10, NULL,
	ai_move, -10, NULL,
	ai_move, -10, NULL,
	ai_move, -5, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, tower_fire6,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, tower_fire7,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t tower_move_death1 = { FRAME_death101, FRAME_death136, tower_frames_death1, tower_dead };

mframe_t tower_frames_death2[] =
{
	ai_move, -5, NULL,
	ai_move, -5, NULL,
	ai_move, -5, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t tower_move_death2 = { FRAME_death201, FRAME_death235, tower_frames_death2, tower_dead };

mframe_t tower_frames_death3[] =
{
	ai_move, -5, NULL,
	ai_move, -5, NULL,
	ai_move, -5, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
};
mmove_t tower_move_death3 = { FRAME_death301, FRAME_death345, tower_frames_death3, tower_dead };

mframe_t tower_frames_death4[] =
{
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t tower_move_death4 = { FRAME_death401, FRAME_death453, tower_frames_death4, tower_dead };

mframe_t tower_frames_death5[] =
{
	ai_move, -5, NULL,
	ai_move, -5, NULL,
	ai_move, -5, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,

	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t tower_move_death5 = { FRAME_death501, FRAME_death524, tower_frames_death5, tower_dead };

mframe_t tower_frames_death6[] =
{
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t tower_move_death6 = { FRAME_death601, FRAME_death610, tower_frames_death6, tower_dead };

void tower_die(edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
	int		n;


	// check for gib

	if (self->deadflag == DEAD_DEAD)
		return;

	// regular death
	self->deadflag = DEAD_DEAD;
	self->takedamage = DAMAGE_YES;
	self->s.skinnum |= 1;

	if (self->s.skinnum == 1)
		gi.sound(self, CHAN_VOICE, sound_death_light, 1, ATTN_NORM, 0);
	else if (self->s.skinnum == 3)
		gi.sound(self, CHAN_VOICE, sound_death, 1, ATTN_NORM, 0);
	else // (self->s.skinnum == 5)
		gi.sound(self, CHAN_VOICE, sound_death_ss, 1, ATTN_NORM, 0);

	if (fabs((self->s.origin[2] + self->viewheight) - point[2]) <= 4)
	{
		// head shot
		self->monsterinfo.currentmove = &tower_move_death3;
		return;
	}

	n = rand() % 5;
	if (n == 0)
		self->monsterinfo.currentmove = &tower_move_death1;
	else if (n == 1)
		self->monsterinfo.currentmove = &tower_move_death2;
	else if (n == 2)
		self->monsterinfo.currentmove = &tower_move_death4;
	else if (n == 3)
		self->monsterinfo.currentmove = &tower_move_death5;
	else
		self->monsterinfo.currentmove = &tower_move_death6;
}



//
// SPAWN
//

void SP_tower_x(edict_t *self)
{

	self->s.modelindex = gi.modelindex("models/monsters/soldier/tris.md2");
	
	self->monsterinfo.scale = 3;
	VectorSet(self->mins, -16, -16, -24);
	VectorSet(self->maxs, 16, 16, 32);
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;

	self->monsterinfo.aiflags = AI_TOWER;
	


	self->mass = 100;


	self->pain = tower_pain;
	self->die = tower_die;


	self->monsterinfo.stand = tower_stand;
	self->monsterinfo.walk = tower_walk;
	self->monsterinfo.run = tower_run;
	self->monsterinfo.dodge = NULL;
	self->monsterinfo.attack = tower_attack;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = tower_sight;

	gi.linkentity(self);

	self->monsterinfo.stand(self);

	tower_start(self);

}


/*QUAKED monster_tower_light (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight
*/
void SP_tower_1(edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict(self);
		return;
	}

	SP_tower_x(self);


	gi.modelindex("models/objects/laser/tris.md2");
	gi.soundindex("misc/lasfly.wav");
	gi.soundindex("tower/solatck2.wav");

	self->s.skinnum = 0;
	self->health = 100000;
	self->gib_health = -30;
}
void SP_tower_2(edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict(self);
		return;
	}

	SP_tower_x(self);


	gi.modelindex("models/objects/laser/tris.md2");
	gi.soundindex("misc/lasfly.wav");
	gi.soundindex("tower/solatck2.wav");

	self->s.skinnum = 2;
	self->health = 100000;
	self->gib_health = -30;
}
void SP_tower_3(edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict(self);
		return;
	}

	SP_tower_x(self);


	gi.modelindex("models/objects/laser/tris.md2");
	gi.soundindex("misc/lasfly.wav");
	gi.soundindex("tower/solatck2.wav");

	self->s.skinnum = 4;
	self->health = 100000;;
	self->gib_health = -30;
}
void SP_tower_4(edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict(self);
		return;
	}

	SP_tower_x(self);


	gi.modelindex("models/objects/laser/tris.md2");
	gi.soundindex("misc/lasfly.wav");
	gi.soundindex("tower/solatck2.wav");

	self->s.skinnum = 1;
	self->health = 100000;
	self->gib_health = -30;
}
