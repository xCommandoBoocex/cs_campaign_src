//=============================================================================//
//
// Purpose: CS:S weapons recreated from scratch in Source SDK 2013 for usage in a Half-Life 2 setting.
//
// Author: Blixibon
//
//=============================================================================//

#include "cbase.h"
#include "weapon_css_base.h"

//-----------------------------------------------------------------------------
// CWeapon_CSS_HL2_M3
//-----------------------------------------------------------------------------
class CWeapon_CSS_HL2_M3 : public CBase_CSS_HL2_Shotgun
{
public:
	DECLARE_CLASS( CWeapon_CSS_HL2_M3, CBase_CSS_HL2_Shotgun );
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();
	DECLARE_DATADESC();

	CWeapon_CSS_HL2_M3(void);
	
	virtual const Vector& GetBulletSpread( void )
	{
		static const Vector cone = VECTOR_CONE_10DEGREES;
		return cone;
	}

	virtual bool PumpsInOtherAnims() { return true; }

	virtual int GetNumPellets() const { return 9; }
	
	// No secondary attack
	void SecondaryAttack( void ) {}
	
	virtual int	GetMinBurst() { return 1; }
	virtual int	GetMaxBurst() { return 3; }

	virtual float GetFireRate( void ) { return 0.88f; }
};

IMPLEMENT_NETWORKCLASS_DT( CWeapon_CSS_HL2_M3, DT_Weapon_CSS_HL2_M3 )
END_NETWORK_TABLE()

LINK_ENTITY_TO_CLASS( weapon_css_m3, CWeapon_CSS_HL2_M3 );
PRECACHE_WEAPON_REGISTER( weapon_css_m3 );

BEGIN_DATADESC( CWeapon_CSS_HL2_M3 )
END_DATADESC()

#ifdef CLIENT_DLL
BEGIN_PREDICTION_DATA( CWeapon_CSS_HL2_M3 )
END_PREDICTION_DATA()
#endif

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CWeapon_CSS_HL2_M3::CWeapon_CSS_HL2_M3( void )
{
	m_bFiresUnderwater	= true;
}

//-----------------------------------------------------------------------------
// CWeapon_CSS_HL2_XM1014
//-----------------------------------------------------------------------------
class CWeapon_CSS_HL2_XM1014 : public CBase_CSS_HL2_Shotgun
{
public:
	DECLARE_CLASS( CWeapon_CSS_HL2_XM1014, CBase_CSS_HL2_Shotgun );
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();
	DECLARE_DATADESC();

	CWeapon_CSS_HL2_XM1014(void);
	
	virtual const Vector& GetBulletSpread( void )
	{
		static const Vector cone = VECTOR_CONE_9DEGREES;
		return cone;
	}

	virtual bool CanPump() { return false; }

	virtual int GetNumPellets() const { return 6; }

	// No secondary attack
	void SecondaryAttack( void ) {}
	
	virtual int	GetMinBurst() { return 1; }
	virtual int	GetMaxBurst() { return 3; }

	virtual float GetFireRate( void ) { return 0.25f; }
};

IMPLEMENT_NETWORKCLASS_DT( CWeapon_CSS_HL2_XM1014, DT_Weapon_CSS_HL2_XM1014 )
END_NETWORK_TABLE()

LINK_ENTITY_TO_CLASS( weapon_css_xm1014, CWeapon_CSS_HL2_XM1014 );
PRECACHE_WEAPON_REGISTER( weapon_css_xm1014 );

BEGIN_DATADESC( CWeapon_CSS_HL2_XM1014 )
END_DATADESC()

#ifdef CLIENT_DLL
BEGIN_PREDICTION_DATA( CWeapon_CSS_HL2_XM1014 )
END_PREDICTION_DATA()
#endif

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CWeapon_CSS_HL2_XM1014::CWeapon_CSS_HL2_XM1014( void )
{
	m_bFiresUnderwater	= true;
}
