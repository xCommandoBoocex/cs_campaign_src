//=============================================================================//
//
// Purpose: CS:S weapons recreated from scratch in Source SDK 2013 for usage in a Half-Life 2 setting.
//
// Author: Blixibon
//
//=============================================================================//

#include "cbase.h"
#include "weapon_css_base.h"

//=============================================================================
// ASSAULT RIFLES
//=============================================================================

//-----------------------------------------------------------------------------
// CWeapon_CSS_HL2_FAMAS
//-----------------------------------------------------------------------------
class CWeapon_CSS_HL2_FAMAS : public CBase_CSS_HL2_BurstableWeapon<CBase_CSS_HL2_Rifle>
{
public:
	DECLARE_CLASS( CWeapon_CSS_HL2_FAMAS, CBase_CSS_HL2_BurstableWeapon<CBase_CSS_HL2_Rifle> );
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();
	DECLARE_DATADESC();

	CWeapon_CSS_HL2_FAMAS(void);

	virtual void FinishBurst( void )
	{
		m_flNextPrimaryAttack = gpGlobals->curtime + 0.2f; // TODO: Proper cooldown?
	}

	virtual float GetViewKickBase() { return InBurst() ? 6.25f : 7.1f; }
	
	virtual const Vector& GetBulletSpread( void )
	{
		static const Vector cone = VECTOR_CONE_3DEGREES;
		return cone;
	}
	
	virtual int	GetMinBurst() { return 1; }
	virtual int	GetMaxBurst() { return 3; }

	virtual float GetFireRate( void ) { return InBurst() ? 0.075f : 0.09f; }

	// Tries to replicate CS:S's lessened damage
	// Player damage: 7 -> 6.3 (6)
	// NPC damage: 3 -> 3
	virtual float GetDamageMultiplier() const { return 0.9f; }
	virtual float GetNPCDamageMultiplier() const { return 1.0f; }
};

IMPLEMENT_NETWORKCLASS_DT( CWeapon_CSS_HL2_FAMAS, DT_Weapon_CSS_HL2_FAMAS )

	DEFINE_CSS_WEAPON_BURSTABLE_NETWORK_TABLE()

END_NETWORK_TABLE()

LINK_ENTITY_TO_CLASS( weapon_css_famas, CWeapon_CSS_HL2_FAMAS );
#if PRECACHE_REGISTER_CSS_WEAPONS == 1
PRECACHE_WEAPON_REGISTER( weapon_css_famas );
#endif

BEGIN_DATADESC( CWeapon_CSS_HL2_FAMAS )

	DEFINE_CSS_WEAPON_BURSTABLE_DATADESC()

END_DATADESC()

#ifdef CLIENT_DLL
BEGIN_PREDICTION_DATA( CWeapon_CSS_HL2_FAMAS )

	DEFINE_CSS_WEAPON_BURSTABLE_PREDICTDESC()

END_PREDICTION_DATA()
#endif

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CWeapon_CSS_HL2_FAMAS::CWeapon_CSS_HL2_FAMAS( void )
{
	m_fMinRange1		= 24;
	m_fMaxRange1		= 1500;
	m_fMinRange2		= 24;
	m_fMaxRange2		= 200;

	m_bFiresUnderwater	= true;

	m_bCanUseBurstMode	= true;
}

//-----------------------------------------------------------------------------
// CWeapon_CSS_HL2_M4A1
//-----------------------------------------------------------------------------
class CWeapon_CSS_HL2_M4A1 : public CBase_CSS_HL2_SilencedWeapon<CBase_CSS_HL2_Rifle>
{
public:
	DECLARE_CLASS( CWeapon_CSS_HL2_M4A1, CBase_CSS_HL2_SilencedWeapon<CBase_CSS_HL2_Rifle> );
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();
	DECLARE_DATADESC();

	CWeapon_CSS_HL2_M4A1(void);

	virtual float GetViewKickBase() { return 7.0f; }
	
	virtual const Vector& GetBulletSpread( void )
	{
		static const Vector cone = VECTOR_CONE_3DEGREES;
		return cone;
	}
	
	virtual int	GetMinBurst() { return 1; }
	virtual int	GetMaxBurst() { return 3; }

	virtual float GetFireRate( void ) { return 0.09f; }
};

IMPLEMENT_NETWORKCLASS_DT( CWeapon_CSS_HL2_M4A1, DT_Weapon_CSS_HL2_M4A1 )

	DEFINE_CSS_WEAPON_SILENCED_NETWORK_TABLE()

END_NETWORK_TABLE()

LINK_ENTITY_TO_CLASS( weapon_css_m4a1, CWeapon_CSS_HL2_M4A1 );
#if PRECACHE_REGISTER_CSS_WEAPONS == 1
PRECACHE_WEAPON_REGISTER( weapon_css_m4a1 );
#endif

BEGIN_DATADESC( CWeapon_CSS_HL2_M4A1 )

	DEFINE_CSS_WEAPON_SILENCED_DATADESC()

END_DATADESC()

#ifdef CLIENT_DLL
BEGIN_PREDICTION_DATA( CWeapon_CSS_HL2_M4A1 )
END_PREDICTION_DATA()
#endif

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CWeapon_CSS_HL2_M4A1::CWeapon_CSS_HL2_M4A1( void )
{
	m_fMinRange1		= 24;
	m_fMaxRange1		= 1500;
	m_fMinRange2		= 24;
	m_fMaxRange2		= 200;

	m_bFiresUnderwater	= true;

	m_bCanToggleSilencer = true;
}

//-----------------------------------------------------------------------------
// CWeapon_CSS_HL2_AUG
//-----------------------------------------------------------------------------
class CWeapon_CSS_HL2_AUG : public CBase_CSS_HL2_Rifle
{
public:
	DECLARE_CLASS( CWeapon_CSS_HL2_AUG, CBase_CSS_HL2_Rifle );
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();
	DECLARE_DATADESC();

	CWeapon_CSS_HL2_AUG(void);

	// TODO
	bool IsScoped() { return false; }

	virtual float GetViewKickBase() { return 6.7f; }
	
	virtual const Vector& GetBulletSpread( void )
	{
		static Vector cone;
		if (IsScoped())
			cone = VECTOR_CONE_1DEGREES;
		else
			cone = VECTOR_CONE_2DEGREES;
		return cone;
	}
	
	virtual int	GetMinBurst() { return 1; }
	virtual int	GetMaxBurst() { return 3; }

	virtual float GetFireRate( void ) { return 0.09f; }
};

IMPLEMENT_NETWORKCLASS_DT( CWeapon_CSS_HL2_AUG, DT_Weapon_CSS_HL2_AUG )
END_NETWORK_TABLE()

LINK_ENTITY_TO_CLASS( weapon_css_aug, CWeapon_CSS_HL2_AUG );
#if PRECACHE_REGISTER_CSS_WEAPONS == 1
PRECACHE_WEAPON_REGISTER( weapon_css_aug );
#endif

BEGIN_DATADESC( CWeapon_CSS_HL2_AUG )
END_DATADESC()

#ifdef CLIENT_DLL
BEGIN_PREDICTION_DATA( CWeapon_CSS_HL2_AUG )
END_PREDICTION_DATA()
#endif

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CWeapon_CSS_HL2_AUG::CWeapon_CSS_HL2_AUG( void )
{
	m_fMinRange1		= 24;
	m_fMaxRange1		= 1500;
	m_fMinRange2		= 24;
	m_fMaxRange2		= 200;

	m_bFiresUnderwater	= true;
}

//-----------------------------------------------------------------------------
// CWeapon_CSS_HL2_SG552
//-----------------------------------------------------------------------------
class CWeapon_CSS_HL2_SG552 : public CBase_CSS_HL2_Rifle
{
public:
	DECLARE_CLASS( CWeapon_CSS_HL2_SG552, CBase_CSS_HL2_Rifle );
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();
	DECLARE_DATADESC();

	CWeapon_CSS_HL2_SG552(void);

	// TODO
	bool IsScoped() { return false; }

	virtual float GetViewKickBase() { return IsScoped() ? 6.4f : 7.0f; }
	
	virtual const Vector& GetBulletSpread( void )
	{
		static Vector cone;
		if (IsScoped())
			cone = VECTOR_CONE_2DEGREES;
		else
			cone = VECTOR_CONE_3DEGREES;
		return cone;
	}
	
	virtual int	GetMinBurst() { return 1; }
	virtual int	GetMaxBurst() { return 3; }

	virtual float GetFireRate( void ) { return 0.09f; }

	// Tries to replicate CS:S's boosted damage
	// Player damage: 7 -> 7.7 (8)
	// NPC damage: 3 -> 3
	virtual float GetDamageMultiplier() const { return 1.1f; }
	virtual float GetNPCDamageMultiplier() const { return 1.0f; }
};

IMPLEMENT_NETWORKCLASS_DT( CWeapon_CSS_HL2_SG552, DT_Weapon_CSS_HL2_SG552 )
END_NETWORK_TABLE()

LINK_ENTITY_TO_CLASS( weapon_css_sg552, CWeapon_CSS_HL2_SG552 );
#if PRECACHE_REGISTER_CSS_WEAPONS == 1
PRECACHE_WEAPON_REGISTER( weapon_css_sg552 );
#endif

BEGIN_DATADESC( CWeapon_CSS_HL2_SG552 )
END_DATADESC()

#ifdef CLIENT_DLL
BEGIN_PREDICTION_DATA( CWeapon_CSS_HL2_SG552 )
END_PREDICTION_DATA()
#endif

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CWeapon_CSS_HL2_SG552::CWeapon_CSS_HL2_SG552( void )
{
	m_fMinRange1		= 24;
	m_fMaxRange1		= 1500;
	m_fMinRange2		= 24;
	m_fMaxRange2		= 200;

	m_bFiresUnderwater	= true;
}

//-----------------------------------------------------------------------------
// CWeapon_CSS_HL2_Galil
//-----------------------------------------------------------------------------
class CWeapon_CSS_HL2_Galil : public CBase_CSS_HL2_Rifle
{
public:
	DECLARE_CLASS( CWeapon_CSS_HL2_Galil, CBase_CSS_HL2_Rifle );
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();
	DECLARE_DATADESC();

	CWeapon_CSS_HL2_Galil(void);

	virtual float GetViewKickBase() { return 6.5f; }
	
	virtual const Vector& GetBulletSpread( void )
	{
		static const Vector cone = VECTOR_CONE_4DEGREES;
		return cone;
	}
	
	virtual int	GetMinBurst() { return 1; }
	virtual int	GetMaxBurst() { return 3; }

	virtual float GetFireRate( void ) { return 0.09f; }
};

IMPLEMENT_NETWORKCLASS_DT( CWeapon_CSS_HL2_Galil, DT_Weapon_CSS_HL2_Galil )
END_NETWORK_TABLE()

LINK_ENTITY_TO_CLASS( weapon_css_galil, CWeapon_CSS_HL2_Galil );
#if PRECACHE_REGISTER_CSS_WEAPONS == 1
PRECACHE_WEAPON_REGISTER( weapon_css_galil );
#endif

BEGIN_DATADESC( CWeapon_CSS_HL2_Galil )
END_DATADESC()

#ifdef CLIENT_DLL
BEGIN_PREDICTION_DATA( CWeapon_CSS_HL2_Galil )
END_PREDICTION_DATA()
#endif

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CWeapon_CSS_HL2_Galil::CWeapon_CSS_HL2_Galil( void )
{
	m_fMinRange1		= 24;
	m_fMaxRange1		= 1500;
	m_fMinRange2		= 24;
	m_fMaxRange2		= 200;

	m_bFiresUnderwater	= true;
}

//-----------------------------------------------------------------------------
// CWeapon_CSS_HL2_AK47
//-----------------------------------------------------------------------------
class CWeapon_CSS_HL2_AK47 : public CBase_CSS_HL2_Rifle
{
public:
	DECLARE_CLASS( CWeapon_CSS_HL2_AK47, CBase_CSS_HL2_Rifle );
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();
	DECLARE_DATADESC();

	CWeapon_CSS_HL2_AK47(void);

	virtual float GetViewKickBase() { return 6.75f; }
	
	virtual const Vector& GetBulletSpread( void )
	{
		static const Vector cone = VECTOR_CONE_3DEGREES;
		return cone;
	}
	
	virtual int	GetMinBurst() { return 1; }
	virtual int	GetMaxBurst() { return 3; }

	virtual float GetFireRate( void ) { return 0.1f; }
};

IMPLEMENT_NETWORKCLASS_DT( CWeapon_CSS_HL2_AK47, DT_Weapon_CSS_HL2_AK47 )
END_NETWORK_TABLE()

LINK_ENTITY_TO_CLASS( weapon_css_ak47, CWeapon_CSS_HL2_AK47 );
#if PRECACHE_REGISTER_CSS_WEAPONS == 1
PRECACHE_WEAPON_REGISTER( weapon_css_ak47 );
#endif

BEGIN_DATADESC( CWeapon_CSS_HL2_AK47 )
END_DATADESC()

#ifdef CLIENT_DLL
BEGIN_PREDICTION_DATA( CWeapon_CSS_HL2_AK47 )
END_PREDICTION_DATA()
#endif

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CWeapon_CSS_HL2_AK47::CWeapon_CSS_HL2_AK47( void )
{
	m_fMinRange1		= 24;
	m_fMaxRange1		= 1500;
	m_fMinRange2		= 24;
	m_fMaxRange2		= 200;

	m_bFiresUnderwater	= true;
}

//=============================================================================
// SNIPER RIFLES
//=============================================================================

//-----------------------------------------------------------------------------
// CWeapon_CSS_HL2_Scout (WIP)
//-----------------------------------------------------------------------------
/*
class CWeapon_CSS_HL2_Scout : public CBase_CSS_HL2_SniperRifle
{
public:
	DECLARE_CLASS( CWeapon_CSS_HL2_Scout, CBase_CSS_HL2_SniperRifle );
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();
	DECLARE_DATADESC();

	CWeapon_CSS_HL2_Scout(void);
	
	virtual const Vector& GetBulletSpread( void )
	{
		static const Vector cone = VECTOR_CONE_5DEGREES;
		return cone;
	}
	
	virtual int	GetMinBurst() { return 1; }
	virtual int	GetMaxBurst() { return 3; }

	virtual float GetFireRate( void ) { return 1.25f; }
};

IMPLEMENT_NETWORKCLASS_DT( CWeapon_CSS_HL2_Scout, DT_Weapon_CSS_HL2_Scout )
END_NETWORK_TABLE()

LINK_ENTITY_TO_CLASS( weapon_css_scout, CWeapon_CSS_HL2_Scout );
#if PRECACHE_REGISTER_CSS_WEAPONS == 1
PRECACHE_WEAPON_REGISTER( weapon_css_scout );
#endif

BEGIN_DATADESC( CWeapon_CSS_HL2_Scout )
END_DATADESC()

#ifdef CLIENT_DLL
BEGIN_PREDICTION_DATA( CWeapon_CSS_HL2_Scout )
END_PREDICTION_DATA()
#endif

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CWeapon_CSS_HL2_AK47::CWeapon_CSS_HL2_AK47( void )
{
	m_fMinRange1		= 24;
	m_fMaxRange1		= 1500;
	m_fMinRange2		= 24;
	m_fMaxRange2		= 200;

	m_bFiresUnderwater	= true;
}
*/
