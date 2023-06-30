#define OFFSET_RENDER            	0x0743ca00 - 0x1F60 		// [NetworkedStringTables]->EffectDispatch - 0x1F60
#define OFFSET_VISIBLE_TIME      	0x1a6d + 0x3        		// [RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3
#define OFFSET_ZOOM              	0x00b8              		// [DataMap.WeaponPlayerData]->m_curZoomFOV 
#define OFFSET_ZOOM_FOV          	0x16b0 + OFFSET_ZOOM		// [RecvTable.DT_WeaponX]->m_playerData + OFFSET_ZOOM
#define OFFSET_HANG_ON_WALL      	0x2b60              		// [DataMap.C_Player]->m_traversalStartTime 
#define OFFSET_HANG_TIME         	0x2b5c              		// [DataMap.C_Player]->m_traversalProgress 
#define OFFSET_INPUTSYSTEM       	0x17a4400           		// [Miscellaneous]->InputSystem 
#define OFFSET_ENTITYLIST        	0x1e53c68           		// [Miscellaneous]->cl_entitylist 
#define OFFSET_GLOBALVAR         	0x16f9d80           		// [Miscellaneous]->GlobalVars 
#define OFFSET_LOCAL_ENT         	err                 		// [Globals]->.?AVC_GameMovement@@ + 0x8
#define OFFSET_GAMEMODE          	0x0223c7e0 + 0x58   		// [ConVars]->mp_gamemode + 0x58
#define OFFSET_NAME_LIST         	0xbe94b60           		// [Miscellaneous]->NameList 
#define OFFSET_THIRDPERSON       	0x01de35b0 + 0x6c   		// [ConVars]->thirdperson_override + 0x6c
#define OFFSET_TIMESCALE         	0x01798b90          		// [ConVars]->host_timescale 
#define OFFSET_LEVEL_NAME        	0x16fa230           		// [Miscellaneous]->LevelName 
#define OFFSET_TEAM              	0x044c              		// [RecvTable.DT_BaseEntity]->m_iTeamNum 
#define OFFSET_HEALTH            	0x043c              		// [RecvTable.DT_Player]->m_iHealth 
#define OFFSET_SHIELD            	0x0170              		// [RecvTable.DT_BaseEntity]->m_shieldHealth 
#define OFFSET_SHIELD_TYPE       	0x4654              		// [RecvTable.DT_Player]->m_armorType 
#define OFFSET_NAME              	0x0589              		// [RecvTable.DT_BaseEntity]->m_iName 
#define OFFSET_MODEL_NAME        	0x0030              		// [DataMap.C_BaseEntity]->m_ModelName 
#define OFFSET_SIGN_NAME         	0x0580              		// [RecvTable.DT_BaseEntity]->m_iSignifierName 
#define OFFSET_ABS_VELOCITY      	0x0140              		// [DataMap.C_BaseEntity]->m_vecAbsVelocity 
#define OFFSET_ZOOMING           	0x1c51              		// [DataMap.C_Player]->m_bZooming 
#define OFFSET_THIRDPERSON_SV    	0x36e8              		// [RecvTable.DT_LocalPlayerExclusive]->m_thirdPersonShoulderView 
#define OFFSET_YAW               	0x22bc - 0x8        		// [DataMap.C_Player]->m_currentFramePlayer.m_ammoPoolCount - 0x8
#define OFFSET_LIFE_STATE        	0x0798              		// [RecvTable.DT_Player]->m_lifeState 
#define OFFSET_BLEED_OUT_STATE   	0x2750              		// [RecvTable.DT_Player]->m_bleedoutState 
#define OFFSET_ORIGIN            	0x014c              		// [DataMap.C_BaseEntity]->m_vecAbsOrigin 
#define OFFSET_BONES             	0x0e98 + 0x48       		// [RecvTable.DT_BaseAnimating]->m_nForceBone + 0x48
#define OFFSET_STUDIOHDR         	0x10e8              		// [Miscellaneous]->CBaseAnimating!m_pStudioHdr 
#define OFFSET_AIMPUNCH          	0x24b8              		// [DataMap.C_Player]->m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle 
#define OFFSET_CAMERAPOS         	0x1f50              		// [Miscellaneous]->CPlayer!camera_origin 
#define OFFSET_VIEWANGLES        	0x25b4 - 0x14       		// [RecvTable.DT_Player]->m_ammoPoolCapacity - 0x14
#define OFFSET_OBSERVER_MODE     	0x34f4              		// [RecvTable.DT_LocalPlayerExclusive]->m_iObserverMode 
#define OFFSET_OBSERVING_TARGET  	0x3500              		// [RecvTable.DT_LocalPlayerExclusive]->m_hObserverTarget 
#define OFFSET_WEAPON            	0x1a14              		// [RecvTable.DT_BaseCombatCharacter]->m_latestPrimaryWeapons 
#define OFFSET_AMMO              	0x1660              		// [DataMap.CWeaponX]->m_ammoInClip 
#define OFFSET_ITEM_ID           	0x1638              		// [RecvTable.DT_PropSurvival]->m_customScriptInt 
#define OFFSET_ITEM_GLOW         	0x02c0              		// [RecvTable.DT_HighlightSettings]->m_highlightFunctionBits 
#define GLOW_TYPE                	0x02c0 + 0x4        		// [RecvTable.DT_HighlightSettings]->m_highlightFunctionBits + 0x4
#define GLOW_DISTANCE            	0x0380 + 0x34       		// [RecvTable.DT_HighlightSettings]->m_highlightServerFadeEndTimes + 0x34
#define OFFSET_VIEWMODEL         	0x2d80              		// [DataMap.C_Player]->m_hViewModels 
#define OFFSET_IN_JUMP           	0x0743d3a0          		// [Buttons]->in_jump 
#define OFFSET_IN_DUCK           	0x0be955c8          		// [Buttons]->in_duck 
