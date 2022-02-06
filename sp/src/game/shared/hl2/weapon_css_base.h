//=============================================================================//
//
// Purpose: CS:S weapons recreated from scratch in Source SDK 2013 for usage in a Half-Life 2 setting.
//
// Author: Blixibon
//
//=============================================================================//

#ifndef WEAPON_CSS_BASE_H
#define WEAPON_CSS_BASE_H

#ifdef CLIENT_DLL
#include "c_basehlcombatweapon.h"
#define CHLMachineGun C_HLMachineGun
#else
#include "basehlcombatweapon.h"
#endif

// Makes all CS:S weapons precache on map load, just like HL2's weapons.
// This means CS:S weapons are always precached even when not in use by the current level.
// This is left off by default to save resources.
#define PRECACHE_REGISTER_CSS_WEAPONS 0

// TODO: Enables code linking classes to the original CS:S classnames
#define ALLOW_ORIGINAL_CSS_CLASSNAMES 1

template <class BASE_WEAPON>
class CBase_CSS_HL2_Weapon : public BASE_WEAPON
{
	DECLARE_CLASS_NOFRIEND( CBase_CSS_HL2_Weapon, BASE_WEAPON );

public:

	// This is used to replicate CS:S's damage differences between weapons
	virtual float GetDamageMultiplier() const { return 1.0f; }
	virtual float GetNPCDamageMultiplier() const { return 1.0f; }

	virtual bool	IsSilenced() const { return false; }
	virtual void	SetSilenced( bool bSilenced ) {}
	bool CanToggleSilencer() const { return this->m_bCanToggleSilencer; }

	virtual bool	InBurst() const { return false; }
	bool CanUseBurstMode() const { return this->m_bCanUseBurstMode; }

	bool ShouldDisplayAltFireHUDHint()
	{
		return BaseClass::ShouldDisplayAltFireHUDHint() && (this->CanToggleSilencer() || this->CanUseBurstMode());
	}

public:
	CNetworkVar( bool, m_bCanToggleSilencer );
	CNetworkVar( bool, m_bCanUseBurstMode );
};

#define DEFINE_CSS_WEAPON_DATADESC() \
	DEFINE_KEYFIELD( m_bCanToggleSilencer, FIELD_BOOLEAN, "CanToggleSilencer" ),	\
	DEFINE_KEYFIELD( m_bCanUseBurstMode, FIELD_BOOLEAN, "CanUseBurstMode" ),	\

#ifdef CLIENT_DLL

#define DEFINE_CSS_WEAPON_NETWORK_TABLE() \
	RecvPropBool( RECVINFO( m_bCanToggleSilencer ) ),	\
	RecvPropBool( RECVINFO( m_bCanUseBurstMode ) ),	\

#else

#define DEFINE_CSS_WEAPON_NETWORK_TABLE() \
	SendPropBool( SENDINFO( m_bCanToggleSilencer ) ),	\
	SendPropBool( SENDINFO( m_bCanUseBurstMode ) ),	\

#endif

//=============================================================================
//=============================================================================

template <class BASE_WEAPON>
class CBase_CSS_HL2_SilencedWeapon : public BASE_WEAPON
{
	DECLARE_CLASS_NOFRIEND( CBase_CSS_HL2_SilencedWeapon, BASE_WEAPON );

public:

	virtual bool IsSilenced() const { return this->m_bSilenced; }
	virtual void SetSilenced( bool bSilenced ) { this->m_bSilenced = bSilenced; }

	void Spawn()
	{
		BaseClass::Spawn();
		this->Activate();
	}

	void Activate()
	{
		BaseClass::Activate();

		// Get the silenced model
		if (this->CanToggleSilencer())
		{
			V_StripExtension( this->GetWorldModel(), m_szSilencedModel, sizeof( m_szSilencedModel ) );
			V_strncat( m_szSilencedModel, "_silencer.mdl", sizeof( m_szSilencedModel ), sizeof( m_szSilencedModel ) );

			if ( m_szSilencedModel[0] )
			{
				m_iSilencedModelIndex = CBaseEntity::PrecacheModel( m_szSilencedModel );
			}
		}
	}

	bool SendWeaponAnim( int iActivity )
	{
		if (this->IsSilenced())
		{
			switch (iActivity)
			{
				case ACT_VM_PRIMARYATTACK:
					iActivity = ACT_VM_PRIMARYATTACK_SILENCED;
					break;

				case ACT_VM_RELOAD:
					iActivity = ACT_VM_RELOAD_SILENCED;
					break;

				case ACT_VM_DRYFIRE:
					iActivity = ACT_VM_DRYFIRE_SILENCED;
					break;

				case ACT_VM_IDLE:
					iActivity = ACT_VM_IDLE_SILENCED;
					break;

				case ACT_VM_DRAW:
					iActivity = ACT_VM_DRAW_SILENCED;
					break;
			}
		}

		return BaseClass::SendWeaponAnim( iActivity );
	}

	void WeaponSound( WeaponSound_t sound_type, float soundtime = 0.0f )
	{
		if (this->IsSilenced())
		{
			switch (sound_type)
			{
				case SINGLE:
				case SINGLE_NPC:
					sound_type = SPECIAL1;
					break;
			}
		}

		BaseClass::WeaponSound( sound_type, soundtime );
	}

	void SecondaryAttack( void )
	{
		if (this->CanToggleSilencer() && this->m_flNextSecondaryAttack <= gpGlobals->curtime)
		{
			if (IsSilenced())
			{
				this->SendWeaponAnim( ACT_VM_DETACH_SILENCER );
				this->m_bSilenced = false;
			}
			else
			{
				this->SendWeaponAnim( ACT_VM_ATTACH_SILENCER );
				this->m_bSilenced = true;
			}

			this->m_flNextSecondaryAttack = gpGlobals->curtime + SequenceDuration();
			this->m_flNextPrimaryAttack = gpGlobals->curtime + SequenceDuration();
		}
	}

	const char *GetWorldModel( void ) const
	{
		if (IsSilenced())
		{
			return this->m_szSilencedModel;
		}
		else
		{
			return BaseClass::GetWorldModel();
		}
	}

	int GetWorldModelIndex( void )
	{
		if (IsSilenced())
		{
			return this->m_iSilencedModelIndex;
		}
		else
		{
			return BaseClass::GetWorldModelIndex();
		}
	}

	void InputSetSilencer( inputdata_t &inputdata )
	{
		m_bSilenced = inputdata.value.Bool();
	}

	void InputToggleSilencer( inputdata_t &inputdata )
	{
		m_bSilenced = !m_bSilenced;
	}

public:
	CNetworkVar( bool, m_bSilenced );
	CNetworkVar( int, m_iSilencedModelIndex ); // Not saved

	char	m_szSilencedModel[MAX_WEAPON_STRING]; // Not saved
};

#ifdef CLIENT_DLL

#define DEFINE_CSS_WEAPON_SILENCED_NETWORK_TABLE() \
	RecvPropBool( RECVINFO( m_bSilenced ) ), \
	RecvPropInt( RECVINFO(m_iSilencedModelIndex) ), \

#define DEFINE_CSS_WEAPON_SILENCED_DATADESC() \
	DEFINE_KEYFIELD( m_bSilenced, FIELD_BOOLEAN, "Silenced" ), \

#else

#define DEFINE_CSS_WEAPON_SILENCED_NETWORK_TABLE() \
	SendPropBool( SENDINFO( m_bSilenced ) ), \
	SendPropModelIndex( SENDINFO(m_iSilencedModelIndex) ), \

#define DEFINE_CSS_WEAPON_SILENCED_DATADESC() \
	DEFINE_KEYFIELD( m_bSilenced, FIELD_BOOLEAN, "Silenced" ), \
	DEFINE_INPUTFUNC( FIELD_BOOLEAN, "SetSilencer", InputSetSilencer ),	\
	DEFINE_INPUTFUNC( FIELD_VOID, "ToggleSilencer", InputToggleSilencer ),	\

#endif

//=============================================================================
//=============================================================================

template <class BASE_WEAPON>
class CBase_CSS_HL2_BurstableWeapon : public BASE_WEAPON
{
	DECLARE_CLASS_NOFRIEND( CBase_CSS_HL2_BurstableWeapon, BASE_WEAPON );

public:

	virtual bool	InBurst() const { return this->m_iBurstSize > 0 || (this->m_bInBurstMode && this->GetOwner() && this->GetOwner()->IsNPC()); }

	//virtual float	GetBurstCycleRate( void ) { return 1.0f; }
	virtual int		GetBurstSize( void ) { return 3; };

	bool Deploy( void )
	{
		// Forget about any bursts this weapon was firing when holstered
		this->m_iBurstSize = 0;
		return BaseClass::Deploy();
	}

	void PrimaryAttack( void )
	{
		if (this->m_bFireOnEmpty)
		{
			return;
		}

		if (this->m_bInBurstMode)
		{
			// Don't continue if we're already burst firing
			if (InBurst())
				return;

			this->SendWeaponAnim( ACT_VM_IDLE ); // HACKHACK: Ensures that the burst animation begins

			this->m_iBurstSize = this->GetBurstSize();

			// Call the think function directly so that the first round gets fired immediately.
			this->BurstThink();
			SetThink( &CBase_CSS_HL2_BurstableWeapon<BASE_WEAPON>::BurstThink );

			// Pick up the rest of the burst through the think function.
			this->SetNextThink( gpGlobals->curtime + GetFireRate() );
		}
		else
		{
			BaseClass::PrimaryAttack();
		}
	}

	void SecondaryAttack( void )
	{
		if (this->CanUseBurstMode())
		{
			if (this->m_bInBurstMode)
			{
				// Burst off
				this->m_bInBurstMode = false;
				this->WeaponSound( SPECIAL1 );
			}
			else
			{
				// Burst on
				this->m_bInBurstMode = true;
				this->WeaponSound( SPECIAL2 );
			}

			this->m_flNextSecondaryAttack = gpGlobals->curtime + 0.5f; // TODO: Real cooldown?
		}
	}

	virtual void FinishBurst( void )
	{
		this->m_flNextPrimaryAttack = gpGlobals->curtime + this->SequenceDuration(); // TODO: Proper cooldown?
		//this->m_flSoonestPrimaryAttack = gpGlobals->curtime + this->SequenceDuration(); // TODO: Proper cooldown?
	}

	void BurstThink( void )
	{
		this->m_flNextPrimaryAttack = gpGlobals->curtime; // HACK?
		BaseClass::PrimaryAttack();

		this->m_iBurstSize--;

		if( this->m_iBurstSize == 0 )
		{
			// The burst is over!
			SetThink(NULL);

			FinishBurst();

			// idle immediately to stop the firing animation
			//SetWeaponIdleTime( gpGlobals->curtime );
			return;
		}

		SetNextThink( gpGlobals->curtime + this->GetFireRate() );
	}

	void InputSetBurstMode( inputdata_t &inputdata )
	{
		m_bInBurstMode = inputdata.value.Bool();
	}

	void InputToggleBurstMode( inputdata_t &inputdata )
	{
		m_bInBurstMode = !m_bInBurstMode;
	}

public:
	CNetworkVar( bool, m_bInBurstMode );
	CNetworkVar( int, m_iBurstSize );
};

#ifdef CLIENT_DLL

#define DEFINE_CSS_WEAPON_BURSTABLE_NETWORK_TABLE() \
	RecvPropBool( RECVINFO( m_bInBurstMode ) ),	\
	RecvPropInt( RECVINFO( m_iBurstSize ) ),	\

#define DEFINE_CSS_WEAPON_BURSTABLE_DATADESC() \
	DEFINE_FIELD( m_bInBurstMode, FIELD_BOOLEAN ),	\
	DEFINE_FIELD( m_iBurstSize, FIELD_INTEGER ),	\

#define DEFINE_CSS_WEAPON_BURSTABLE_PREDICTDESC() \
	DEFINE_PRED_FIELD( m_bInBurstMode, FIELD_BOOLEAN, FTYPEDESC_INSENDTABLE ),	\
	DEFINE_PRED_FIELD( m_iBurstSize, FIELD_INTEGER, FTYPEDESC_INSENDTABLE ),	\

#else

#define DEFINE_CSS_WEAPON_BURSTABLE_NETWORK_TABLE() \
	SendPropBool( SENDINFO( m_bInBurstMode ) ), \
	SendPropInt( SENDINFO( m_iBurstSize ) ), \

#define DEFINE_CSS_WEAPON_BURSTABLE_DATADESC() \
	DEFINE_KEYFIELD( m_bInBurstMode, FIELD_BOOLEAN, "InBurstMode" ),	\
	DEFINE_FIELD( m_iBurstSize, FIELD_INTEGER ),	\
	DEFINE_FUNCTION( BurstThink ),	\
	DEFINE_INPUTFUNC( FIELD_BOOLEAN, "SetBurstMode", InputSetBurstMode ),	\
	DEFINE_INPUTFUNC( FIELD_VOID, "ToggleBurstMode", InputToggleBurstMode ),	\

#endif

//=============================================================================
//=============================================================================

template <class BASE_ITEM>
class CBase_CSS_HL2_Item : public BASE_ITEM
{
	DECLARE_CLASS_NOFRIEND( CBase_CSS_HL2_Item, BASE_ITEM );

public:
};

//---------------------------------------------------

#if MAPBASE_VER_INT >= 7000 && !defined(CLIENT_DLL)
extern acttable_t *GetPistolActtable();
extern int GetPistolActtableCount();
#endif

class CBase_CSS_HL2_Pistol : public CBase_CSS_HL2_Weapon<CBaseHLCombatWeapon>
{
public:
	DECLARE_CLASS( CBase_CSS_HL2_Pistol, CBase_CSS_HL2_Weapon<CBaseHLCombatWeapon> );
	DECLARE_DATADESC();
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();

	CBase_CSS_HL2_Pistol(void);

	void	Precache( void );
	void	ItemPostFrame( void );
	void	ItemPreFrame( void );
	void	ItemBusyFrame( void );
	void	PrimaryAttack( void );
	void	SecondaryAttack( void );
	void	AddViewKick( void );
	void	DryFire( void );
#ifndef CLIENT_DLL
	void	Operator_HandleAnimEvent( animevent_t *pEvent, CBaseCombatCharacter *pOperator );
	void	FireNPCPrimaryAttack( CBaseCombatCharacter *pOperator, Vector &vecShootOrigin, Vector &vecShootDir );
	void	Operator_ForceNPCFire( CBaseCombatCharacter  *pOperator, bool bSecondary );
#endif

	void	UpdatePenaltyTime( void );

#ifndef CLIENT_DLL
	int		CapabilitiesGet( void ) { return bits_CAP_WEAPON_RANGE_ATTACK1; }
#endif
	Activity	GetPrimaryAttackActivity( void );

	virtual bool Reload( void );

	//-----------------------------------------------------------------------------

	inline float GetAccuracyPenalty() { return m_flAccuracyPenalty; }

	virtual float GetViewKickBase() { return 0.0f; }

	virtual float GetRefireRate() { return 0.1f; }
	virtual float GetDryRefireRate() { return 0.2f; }

	virtual float GetShotPenaltyTime() { return 0.2f; }
	
	//-----------------------------------------------------------------------------

#ifndef CLIENT_DLL
	DECLARE_ACTTABLE();
#endif

protected:
	CNetworkVar( float,	m_flSoonestPrimaryAttack );
private:
	CNetworkVar( float,	m_flLastAttackTime );
	CNetworkVar( float,	m_flAccuracyPenalty );
	CNetworkVar( int,	m_nNumShotsFired );
};

//---------------------------------------------------

#if MAPBASE_VER_INT >= 7000 && !defined(CLIENT_DLL)
extern acttable_t *GetSMG1Acttable();
extern int GetSMG1ActtableCount();

extern acttable_t *GetAR2Acttable();
extern int GetAR2ActtableCount();

extern acttable_t *GetShotgunActtable();
extern int GetShotgunActtableCount();
#endif

class CBase_CSS_HL2_MachineGun : public CBase_CSS_HL2_Weapon<CHLMachineGun>
{
public:
	DECLARE_CLASS( CBase_CSS_HL2_MachineGun, CBase_CSS_HL2_Weapon<CHLMachineGun> );
	DECLARE_DATADESC();
	DECLARE_NETWORKCLASS();

	CBase_CSS_HL2_MachineGun(void);
	
	void	Precache( void );
	void	AddViewKick( void );

	int		GetMinBurst() { return 2; }
	int		GetMaxBurst() { return 5; }

	float	GetFireRate( void ) { return 0.075f; }	// 13.3hz
#ifndef CLIENT_DLL
	int		CapabilitiesGet( void ) { return bits_CAP_WEAPON_RANGE_ATTACK1; }
#endif
	Activity	GetPrimaryAttackActivity( void );

	virtual float GetViewKickBase() { return 0.0f; }

	virtual const Vector& GetBulletSpread( void )
	{
		static const Vector cone = VECTOR_CONE_5DEGREES;
		return cone;
	}

	const WeaponProficiencyInfo_t *GetProficiencyValues();

#ifndef CLIENT_DLL
	void FireNPCPrimaryAttack( CBaseCombatCharacter *pOperator, Vector &vecShootOrigin, Vector &vecShootDir );
	void Operator_ForceNPCFire( CBaseCombatCharacter  *pOperator, bool bSecondary );
	void Operator_HandleAnimEvent( animevent_t *pEvent, CBaseCombatCharacter *pOperator );
#endif
	
	//-----------------------------------------------------------------------------

#ifndef CLIENT_DLL
	DECLARE_ACTTABLE();
#endif

private:
};

//=============================================================================
//=============================================================================

class CBase_CSS_HL2_SMG : public CBase_CSS_HL2_MachineGun
{
public:
	DECLARE_CLASS( CBase_CSS_HL2_SMG, CBase_CSS_HL2_MachineGun );

private:
};

//=============================================================================
//=============================================================================

class CBase_CSS_HL2_Rifle : public CBase_CSS_HL2_MachineGun
{
public:
	DECLARE_CLASS( CBase_CSS_HL2_Rifle, CBase_CSS_HL2_MachineGun );

#if MAPBASE_VER_INT >= 7000 && !defined(CLIENT_DLL)
	virtual acttable_t		*GetBackupActivityList() { return GetSMG1Acttable(); }
	virtual int				GetBackupActivityListCount() { return GetSMG1ActtableCount(); }
#endif

#ifndef CLIENT_DLL
	DECLARE_ACTTABLE();
#endif

private:
};

//=============================================================================
//=============================================================================

// TODO: Scope, etc.
class CBase_CSS_HL2_SniperRifle : public CBase_CSS_HL2_Rifle
{
public:
	DECLARE_CLASS( CBase_CSS_HL2_Rifle, CBase_CSS_HL2_Rifle );

private:
};

//=============================================================================
//=============================================================================

class CBase_CSS_HL2_Shotgun : public CBase_CSS_HL2_Weapon<CBaseHLCombatWeapon>
{
public:
	DECLARE_CLASS( CBase_CSS_HL2_Shotgun, CBase_CSS_HL2_Weapon<CBaseHLCombatWeapon> );
	DECLARE_DATADESC();
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();

	CBase_CSS_HL2_Shotgun(void);

	virtual const Vector& GetBulletSpread( void )
	{
		static Vector cone = VECTOR_CONE_10DEGREES;
		return cone;
	}

	virtual float			GetMinRestTime();
	virtual float			GetMaxRestTime();

	bool StartReload( void );
	bool Reload( void );
	void FillClip( void );
	void FinishReload( void );
	void CheckHolsterReload( void );
	void Pump( void );
//	void WeaponIdle( void );
	void ItemHolsterFrame( void );
	void ItemPostFrame( void );
	void PrimaryAttack( void );
	void SecondaryAttack( void );
	void DryFire( void );
	bool Deploy( void );

	virtual int GetNumPellets() const { return 8; }
	virtual int GetNumDoublePellets() const { return 12; }

	virtual bool CanPump() { return true; }
	virtual bool PumpsInOtherAnims() { return false; }

#ifndef CLIENT_DLL
	int CapabilitiesGet( void ) { return bits_CAP_WEAPON_RANGE_ATTACK1; }

	void FireNPCPrimaryAttack( CBaseCombatCharacter *pOperator, bool bUseWeaponAngles );
	void Operator_ForceNPCFire( CBaseCombatCharacter  *pOperator, bool bSecondary );
	void Operator_HandleAnimEvent( animevent_t *pEvent, CBaseCombatCharacter *pOperator );
#endif

#ifndef CLIENT_DLL
	DECLARE_ACTTABLE();
#endif

private:
	CNetworkVar( bool,	m_bNeedPump );		// When emptied completely
	CNetworkVar( bool,	m_bDelayedFire1 );	// Fire primary when finished reloading
	CNetworkVar( bool,	m_bDelayedFire2 );	// Fire secondary when finished reloading
	CNetworkVar( bool,	m_bDelayedReload );	// Reload when finished pump
};

#endif // WEAPON_CSS_BASE_H
