enum unique_base_item
{
	UITYPE_NONE = 0x0,
	UITYPE_SHORTBOW = 0x1,
	UITYPE_LONGBOW = 0x2,
	UITYPE_HUNTBOW = 0x3,
	UITYPE_COMPBOW = 0x4,
	UITYPE_WARBOW = 0x5,
	UITYPE_BATTLEBOW = 0x6,
	UITYPE_DAGGER = 0x7,
	UITYPE_FALCHION = 0x8,
	UITYPE_CLAYMORE = 0x9,
	UITYPE_BROADSWR = 0xA,
	UITYPE_SABRE = 0xB,
	UITYPE_SCIMITAR = 0xC,
	UITYPE_LONGSWR = 0xD,
	UITYPE_BASTARDSWR = 0xE,
	UITYPE_TWOHANDSWR = 0xF,
	UITYPE_GREATSWR = 0x10,
	UITYPE_CLEAVER = 0x11,
	UITYPE_LARGEAXE = 0x12,
	UITYPE_BROADAXE = 0x13,
	UITYPE_SMALLAXE = 0x14,
	UITYPE_BATTLEAXE = 0x15,
	UITYPE_GREATAXE = 0x16,
	UITYPE_MACE = 0x17,
	UITYPE_MORNSTAR = 0x18,
	UITYPE_SPIKCLUB = 0x19,
	UITYPE_MAUL = 0x1A,
	UITYPE_WARHAMMER = 0x1B,
	UITYPE_FLAIL = 0x1C,
	UITYPE_LONGSTAFF = 0x1D,
	UITYPE_SHORTSTAFF = 0x1E,
	UITYPE_COMPSTAFF = 0x1F,
	UITYPE_QUARSTAFF = 0x20,
	UITYPE_WARSTAFF = 0x21,
	UITYPE_SKULLCAP = 0x22,
	UITYPE_HELM = 0x23,
	UITYPE_GREATHELM = 0x24,
	UITYPE_CROWN = 0x25,
	UITYPE_38 = 0x26,
	UITYPE_RAGS = 0x27,
	UITYPE_STUDARMOR = 0x28,
	UITYPE_CLOAK = 0x29,
	UITYPE_ROBE = 0x2A,
	UITYPE_CHAINMAIL = 0x2B,
	UITYPE_LEATHARMOR = 0x2C,
	UITYPE_BREASTPLATE = 0x2D,
	UITYPE_CAPE = 0x2E,
	UITYPE_PLATEMAIL = 0x2F,
	UITYPE_FULLPLATE = 0x30,
	UITYPE_BUCKLER = 0x31,
	UITYPE_SMALLSHIELD = 0x32,
	UITYPE_LARGESHIELD = 0x33,
	UITYPE_KITESHIELD = 0x34,
	UITYPE_GOTHSHIELD = 0x35,
	UITYPE_RING = 0x36,
	UITYPE_55 = 0x37,
	UITYPE_AMULET = 0x38,
	UITYPE_SKCROWN = 0x39,
	UITYPE_INFRARING = 0x3A,
	UITYPE_OPTAMULET = 0x3B,
	UITYPE_TRING = 0x3C,
	UITYPE_HARCREST = 0x3D,
	UITYPE_MAPOFDOOM = 0x3E,
	UITYPE_ELIXIR = 0x3F,
	UITYPE_ARMOFVAL = 0x40,
	UITYPE_STEELVEIL = 0x41,
	UITYPE_GRISWOLD = 0x42,
	UITYPE_LGTFORGE = 0x43,
	UITYPE_LAZSTAFF = 0x44,
	UITYPE_INVALID = -1,
};

enum item_effect_type
{
	IPL_TOHIT = 0x0,
	IPL_TOHIT_CURSE = 0x1,
	IPL_DAMP = 0x2,
	IPL_DAMP_CURSE = 0x3,
	IPL_TOHIT_DAMP = 0x4,
	IPL_TOHIT_DAMP_CURSE = 0x5,
	IPL_ACP = 0x6,
	IPL_ACP_CURSE = 0x7,
	IPL_FIRERES = 0x8,
	IPL_LIGHTRES = 0x9,
	IPL_MAGICRES = 0xA,
	IPL_ALLRES = 0xB,
	IPL_SPLCOST = 0xC,
	IPL_SPLDUR = 0xD,
	IPL_SPLLVLADD = 0xE,
	IPL_CHARGES = 0xF,
	IPL_FIREDAM = 0x10,
	IPL_LIGHTDAM = 0x11,
	IPL_RNDSPL_5MIN = 0x12,
	IPL_STR = 0x13,
	IPL_STR_CURSE = 0x14,
	IPL_MAG = 0x15,
	IPL_MAG_CURSE = 0x16,
	IPL_DEX = 0x17,
	IPL_DEX_CURSE = 0x18,
	IPL_VIT = 0x19,
	IPL_VIT_CURSE = 0x1A,
	IPL_ATTRIBS = 0x1B,
	IPL_ATTRIBS_CURSE = 0x1C,
	IPL_GETHIT_CURSE = 0x1D,
	IPL_GETHIT = 0x1E,
	IPL_LIFE = 0x1F,
	IPL_LIFE_CURSE = 0x20,
	IPL_MANA = 0x21,
	IPL_MANA_CURSE = 0x22,
	IPL_DUR = 0x23,
	IPL_DUR_CURSE = 0x24,
	IPL_INDESTRUCTIBLE = 0x25,
	IPL_LIGHT = 0x26,
	IPL_LIGHT_CURSE = 0x27,
	IPL_INVISIBILITY = 0x28,
	IPL_MULT_ARROWS = 0x29, /* only used in hellfire */
	IPL_FIRE_ARROWS = 0x2A,
	IPL_LIGHT_ARROWS = 0x2B,
	IPL_INVCURS = 0x2C,
	IPL_THORNS = 0x2D,
	IPL_NOMANA = 0x2E,
	IPL_NOHEALPLR = 0x2F,
	IPL_SCAREMONST = 0x30,
	IPL_ATTACKTWICE = 0x31,
	IPL_EXPONENTIALDMG = 0x32,
	IPL_SEEINVISIBLE = 0x33,
	IPL_ABSHALFTRAP = 0x34,
	IPL_KNOCKBACK = 0x35,
	IPL_NOHEALMON = 0x36,
	IPL_STEALMANA = 0x37,
	IPL_STEALLIFE = 0x38,
	IPL_TARGAC = 0x39,
	IPL_FASTATTACK = 0x3A,
	IPL_FASTRECOVER = 0x3B,
	IPL_FASTBLOCK = 0x3C,
	IPL_DAMMOD = 0x3D,
	IPL_RNDARROWVEL = 0x3E,
	IPL_SETDAM = 0x3F,
	IPL_SETDUR = 0x40,
	IPL_NOMINSTR = 0x41,
	IPL_SPELL = 0x42,
	IPL_FASTSWING = 0x43,
	IPL_ONEHAND = 0x44,
	IPL_3XDAMVDEM = 0x45,
	IPL_ALLRESZERO = 0x46,
	IPL_DRAINLIFE = 0x48,
	IPL_RNDSTEALLIFE = 0x49,
	IPL_INFRAVISION = 0x4A,
	IPL_SETAC = 0x4B,
	IPL_ADDACLIFE = 0x4C,
	IPL_ADDMANAAC = 0x4D,
	IPL_FIRERESCLVL = 0x4E,
	IPL_AC_CURSE = 0x4F,
	IPL_INVALID = -1,
};

enum affix_item_type
{
	PLT_MISC = 0x1,
	PLT_BOW = 0x10,
	PLT_STAFF = 0x100,
	PLT_WEAP = 0x1000,
	PLT_SHLD = 0x10000,
	PLT_ARMO = 0x100000,
};

#include "Source/Data/xl_sfx.h"

enum item_equip_type
{
	ILOC_NONE = 0x0,
	ILOC_ONEHAND = 0x1,
	ILOC_TWOHAND = 0x2,
	ILOC_ARMOR = 0x3,
	ILOC_HELM = 0x4,
	ILOC_RING = 0x5,
	ILOC_AMULET = 0x6,
	ILOC_UNEQUIPABLE = 0x7,
	ILOC_BELT = 0x8,
	ILOC_INVALID = -1,
};

#include "Source/Data/xl_mis.h"

#include "Source/Data/xl_mfile.h"

enum _mai_id
{
	AI_ZOMBIE = 0,
	AI_FAT = 1,
	AI_SKELSD = 2,
	AI_SKELBOW = 3,
	AI_SCAV = 4,
	AI_RHINO = 5,
	AI_GOATMC = 6,
	AI_GOATBOW = 7,
	AI_FALLEN = 8,
	AI_MAGMA = 9,
	AI_SKELKING = 10,
	AI_BAT = 11,
	AI_GARG = 12,
	AI_CLEAVER = 13,
	AI_SUCC = 14,
	AI_SNEAK = 15,
	AI_STORM = 16,
	AI_FIREMAN = 17,
	AI_GARBUD = 18,
	AI_ACID = 19,
	AI_ACIDUNIQ = 20,
	AI_GOLUM = 21,
	AI_ZHAR = 22,
	AI_SNOTSPIL = 23,
	AI_SNAKE = 24,
	AI_COUNSLR = 25,
	AI_MEGA = 26,
	AI_DIABLO = 27,
	AI_LAZURUS = 28,
	AI_LAZHELP = 29,
	AI_LACHDAN = 30,
	AI_WARLORD = 31,
};

enum _mc_id
{
	MC_UNDEAD = 0,
	MC_DEMON = 1,
	MC_ANIMAL = 2,
};

#include "Source/Data/xl_monst.h"

#include "Source/Data/speech.h"

enum object_graphic_id
{
	OFILE_L1BRAZ = 0x0,
	OFILE_L1DOORS = 0x1,
	OFILE_LEVER = 0x2,
	OFILE_CHEST1 = 0x3,
	OFILE_CHEST2 = 0x4,
	OFILE_BANNER = 0x5,
	OFILE_SKULPILE = 0x6,
	OFILE_SKULFIRE = 0x7,
	OFILE_SKULSTIK = 0x8,
	OFILE_CRUXSK1 = 0x9,
	OFILE_CRUXSK2 = 0xA,
	OFILE_CRUXSK3 = 0xB,
	OFILE_BOOK1 = 0xC,
	OFILE_BOOK2 = 0xD,
	OFILE_ROCKSTAN = 0xE,
	OFILE_ANGEL = 0xF,
	OFILE_CHEST3 = 0x10,
	OFILE_BURNCROS = 0x11,
	OFILE_CANDLE2 = 0x12,
	OFILE_NUDE2 = 0x13,
	OFILE_SWITCH4 = 0x14,
	OFILE_TNUDEM = 0x15,
	OFILE_TNUDEW = 0x16,
	OFILE_TSOUL = 0x17,
	OFILE_L2DOORS = 0x18,
	OFILE_WTORCH4 = 0x19,
	OFILE_WTORCH3 = 0x1A,
	OFILE_SARC = 0x1B,
	OFILE_FLAME1 = 0x1C,
	OFILE_PRSRPLT1 = 0x1D,
	OFILE_TRAPHOLE = 0x1E,
	OFILE_MINIWATR = 0x1F,
	OFILE_WTORCH2 = 0x20,
	OFILE_WTORCH1 = 0x21,
	OFILE_BCASE = 0x22,
	OFILE_BSHELF = 0x23,
	OFILE_WEAPSTND = 0x24,
	OFILE_BARREL = 0x25,
	OFILE_BARRELEX = 0x26,
	OFILE_LSHRINEG = 0x27,
	OFILE_RSHRINEG = 0x28,
	OFILE_BLOODFNT = 0x29,
	OFILE_DECAP = 0x2A,
	OFILE_PEDISTL = 0x2B,
	OFILE_L3DOORS = 0x2C,
	OFILE_PFOUNTN = 0x2D,
	OFILE_ARMSTAND = 0x2E,
	OFILE_GOATSHRN = 0x2F,
	OFILE_CAULDREN = 0x30,
	OFILE_MFOUNTN = 0x31,
	OFILE_TFOUNTN = 0x32,
	OFILE_ALTBOY = 0x33,
	OFILE_MCIRL = 0x34,
	OFILE_BKSLBRNT = 0x35,
	OFILE_MUSHPTCH = 0x36,
	OFILE_LZSTAND = 0x37,
};

enum dungeon_type
{
	DTYPE_TOWN = 0x0,
	DTYPE_CATHEDRAL = 0x1,
	DTYPE_CATACOMBS = 0x2,
	DTYPE_CAVES = 0x3,
	DTYPE_HELL = 0x4,
	DTYPE_NONE = 0xFF,
};

enum magic_type
{
	STYPE_FIRE = 0x0,
	STYPE_LIGHTNING = 0x1,
	STYPE_MAGIC = 0x2,
};

enum theme_id
{
	THEME_BARREL = 0x0,
	THEME_SHRINE = 0x1,
	THEME_MONSTPIT = 0x2,
	THEME_SKELROOM = 0x3,
	THEME_TREASURE = 0x4,
	THEME_LIBRARY = 0x5,
	THEME_TORTURE = 0x6,
	THEME_BLOODFOUNTAIN = 0x7,
	THEME_DECAPITATED = 0x8,
	THEME_PURIFYINGFOUNTAIN = 0x9,
	THEME_ARMORSTAND = 0xA,
	THEME_GOATSHRINE = 0xB,
	THEME_CAULDRON = 0xC,
	THEME_MURKYFOUNTAIN = 0xD,
	THEME_TEARFOUNTAIN = 0xE,
	THEME_BRNCROSS = 0xF,
	THEME_WEAPONRACK = 0x10,
	THEME_NONE = 0xFF,
};

enum event_type
{
	EVENT_TYPE_PLAYER_CREATE_GAME = 1,
	EVENT_TYPE_2 = 2,
	EVENT_TYPE_PLAYER_LEAVE_GAME = 3,
	EVENT_TYPE_PLAYER_MESSAGE = 4,
	EVENT_TYPE_5 = 5,
	EVENT_TYPE_6 = 6,
	EVENT_TYPE_7 = 7,
	EVENT_TYPE_8 = 8,
	EVENT_TYPE_9 = 9,
	EVENT_TYPE_10 = 10,
	EVENT_TYPE_11 = 11,
	EVENT_TYPE_12 = 12,
	EVENT_TYPE_13 = 13,
	EVENT_TYPE_14 = 14,
	EVENT_TYPE_15 = 15,
};

enum _copyprot_results
{
	COPYPROT_OK = 1,
	COPYPROT_CANCEL = 2,
};

enum text_color
{
	COL_WHITE = 0x0,
	COL_BLUE = 0x1,
	COL_RED = 0x2,
	COL_GOLD = 0x3,
};

enum _difficulty
{
	DIFF_NORMAL = 0x0,
	DIFF_NIGHTMARE = 0x1,
	DIFF_HELL = 0x2,
	NUM_DIFFICULTIES = 0x3,
};

enum MON_MODE
{
	MM_STAND = 0,
	MM_WALK = 1,
	MM_WALK2 = 2,
	MM_WALK3 = 3,
	MM_ATTACK = 4,
	MM_GOTHIT = 5,
	MM_DEATH = 6,
	MM_SATTACK = 7,
	MM_FADEIN = 8,
	MM_FADEOUT = 9,
	MM_RATTACK = 10,
	MM_SPSTAND = 11,
	MM_RSPATTACK = 12,
	MM_DELAY = 13,
	MM_CHARGE = 14,
	MM_STONE = 15,
	MM_HEAL = 16,
	MM_TALK = 17,
};

enum PLR_MODE
{
	PM_STAND = 0,
	PM_WALK = 1,
	PM_WALK2 = 2,
	PM_WALK3 = 3,
	PM_ATTACK = 4,
	PM_RATTACK = 5,
	PM_BLOCK = 6,
	PM_GOTHIT = 7,
	PM_DEATH = 8,
	PM_SPELL = 9,
	PM_NEWLVL = 10,
	PM_QUIT = 11,
};

enum spell_type
{
	RSPLTYPE_SKILL = 0x0,
	RSPLTYPE_SPELL = 0x1,
	RSPLTYPE_SCROLL = 0x2,
	RSPLTYPE_CHARGES = 0x3,
	RSPLTYPE_INVALID = 0x4,
};

enum cursor_id
{
	CURSOR_NONE = 0x0,
	CURSOR_HAND = 0x1,
	CURSOR_IDENTIFY = 0x2,
	CURSOR_REPAIR = 0x3,
	CURSOR_RECHARGE = 0x4,
	CURSOR_DISARM = 0x5,
	CURSOR_OIL = 0x6,
	CURSOR_TELEKINESIS = 0x7,
	CURSOR_RESURRECT = 0x8,
	CURSOR_TELEPORT = 0x9,
	CURSOR_HEALOTHER = 0xA,
	CURSOR_HOURGLASS = 0xB,
	CURSOR_FIRSTITEM = 0xC,
};

enum direction
{
	DIR_S = 0x0,
	DIR_SW = 0x1,
	DIR_W = 0x2,
	DIR_NW = 0x3,
	DIR_N = 0x4,
	DIR_NE = 0x5,
	DIR_E = 0x6,
	DIR_SE = 0x7,
	DIR_OMNI = 0x8,
};

enum interface_mode
{
	WM_DIABNEXTLVL = 0x402, // WM_USER+2
	WM_DIABPREVLVL = 0x403,
	WM_DIABRTNLVL = 0x404,
	WM_DIABSETLVL = 0x405,
	WM_DIABWARPLVL = 0x406,
	WM_DIABTOWNWARP = 0x407,
	WM_DIABTWARPUP = 0x408,
	WM_DIABRETOWN = 0x409,
	WM_DIABNEWGAME = 0x40A,
	WM_DIABLOADGAME = 0x40B
	// WM_LEIGHSKIP = 0x40C, // psx only
	// WM_DIAVNEWLVL = 0x40D, // psx only
};

enum game_info
{
	GAMEINFO_NAME           = 1,
	GAMEINFO_PASSWORD       = 2,
	GAMEINFO_STATS          = 3,
	GAMEINFO_MODEFLAG       = 4,
	GAMEINFO_GAMETEMPLATE   = 5,
	GAMEINFO_PLAYERS        = 6,
};

#include "Source/Data/xl_spell.h"

enum _cmd_id
{
	CMD_STAND = 0,
	CMD_WALKXY = 1,
	CMD_ACK_PLRINFO = 2,
	CMD_ADDSTR = 3,
	CMD_ADDMAG = 4,
	CMD_ADDDEX = 5,
	CMD_ADDVIT = 6,
	CMD_SBSPELL = 7,
	CMD_GETITEM = 8,
	CMD_AGETITEM = 9,
	CMD_PUTITEM = 10,
	CMD_RESPAWNITEM = 11,
	CMD_ATTACKXY = 12,
	CMD_RATTACKXY = 13,
	CMD_SPELLXY = 14,
	CMD_TSPELLXY = 15,
	CMD_OPOBJXY = 16,
	CMD_DISARMXY = 17,
	CMD_ATTACKID = 18,
	CMD_ATTACKPID = 19,
	CMD_RATTACKID = 20,
	CMD_RATTACKPID = 21,
	CMD_SPELLID = 22,
	CMD_SPELLPID = 23,
	CMD_TSPELLID = 24,
	CMD_TSPELLPID = 25,
	CMD_RESURRECT = 26,
	CMD_OPOBJT = 27,
	CMD_KNOCKBACK = 28,
	CMD_TALKXY = 29,
	CMD_NEWLVL = 30,
	CMD_WARP = 31,
	CMD_CHEAT_EXPERIENCE = 32,
	CMD_CHEAT_SPELL_LEVEL = 33,
	CMD_DEBUG = 34,
	CMD_SYNCDATA = 35,
	CMD_MONSTDEATH = 36,
	CMD_MONSTDAMAGE = 37,
	CMD_PLRDEAD = 38,
	CMD_REQUESTGITEM = 39,
	CMD_REQUESTAGITEM = 40,
	CMD_GOTOGETITEM = 41,
	CMD_GOTOAGETITEM = 42,
	CMD_OPENDOOR = 43,
	CMD_CLOSEDOOR = 44,
	CMD_OPERATEOBJ = 45,
	CMD_PLROPOBJ = 46,
	CMD_BREAKOBJ = 47,
	CMD_CHANGEPLRITEMS = 48,
	CMD_DELPLRITEMS = 49,
	CMD_PLRDAMAGE = 50,
	CMD_PLRLEVEL = 51,
	CMD_DROPITEM = 52,
	CMD_PLAYER_JOINLEVEL = 53,
	CMD_SEND_PLRINFO = 54,
	CMD_SATTACKXY = 55,
	CMD_ACTIVATEPORTAL = 56,
	CMD_DEACTIVATEPORTAL = 57,
	CMD_DLEVEL_0 = 58,
	CMD_DLEVEL_1 = 59,
	CMD_DLEVEL_2 = 60,
	CMD_DLEVEL_3 = 61,
	CMD_DLEVEL_4 = 62,
	CMD_DLEVEL_5 = 63,
	CMD_DLEVEL_6 = 64,
	CMD_DLEVEL_7 = 65,
	CMD_DLEVEL_8 = 66,
	CMD_DLEVEL_9 = 67,
	CMD_DLEVEL_10 = 68,
	CMD_DLEVEL_11 = 69,
	CMD_DLEVEL_12 = 70,
	CMD_DLEVEL_13 = 71,
	CMD_DLEVEL_14 = 72,
	CMD_DLEVEL_15 = 73,
	CMD_DLEVEL_16 = 74,
	CMD_DLEVEL_JUNK = 75,
	CMD_DLEVEL_END = 76,
	CMD_HEALOTHER = 77,
	CMD_STRING = 78,
	CMD_SETSTR = 79,
	CMD_SETMAG = 80,
	CMD_SETDEX = 81,
	CMD_SETVIT = 82,
	CMD_RETOWN = 83,
	CMD_SPELLXYD = 84,
	CMD_ITEMEXTRA = 85,
	CMD_SYNCPUTITEM = 86,
	CMD_KILLGOLEM = 87,
	CMD_SYNCQUEST = 88,
	CMD_ENDSHIELD = 89,
	CMD_AWAKEGOLEM = 90,
	CMD_NOVA = 91,
	CMD_SETSHIELD = 92,
	CMD_REMSHIELD = 93,
	FAKE_CMD_SETID = 94,
	FAKE_CMD_DROPID = 95,
	NUM_CMDS = 96,
};

enum _talker_id
{
	TOWN_SMITH = 0x0,
	TOWN_HEALER = 0x1,
	TOWN_DEADGUY = 0x2,
	TOWN_TAVERN = 0x3,
	TOWN_STORY = 0x4,
	TOWN_DRUNK = 0x5,
	TOWN_WITCH = 0x6,
	TOWN_BMAID = 0x7,
	TOWN_PEGBOY = 0x8,
	TOWN_COW = 0x9,
	TOWN_PRIEST = 0xA,
};

enum _music_id
{
	TMUSIC_TOWN = 0,
	TMUSIC_L1 = 1,
	TMUSIC_L2 = 2,
	TMUSIC_L3 = 3,
	TMUSIC_L4 = 4,
	TMUSIC_INTRO = 5,
	NUM_MUSIC = 6,
};

enum _mainmenu_selections
{
	MAINMENU_SINGLE_PLAYER = 1,
	MAINMENU_MULTIPLAYER = 2,
	MAINMENU_REPLAY_INTRO = 3,
	MAINMENU_SHOW_CREDITS = 4,
	MAINMENU_EXIT_DIABLO = 5,
	MAINMENU_ATTRACT_MODE = 6,
};

enum panel_button_id
{
	PANBTN_CHARINFO = 0,
	PANBTN_QLOG = 1,
	PANBTN_AUTOMAP = 2,
	PANBTN_MAINMENU = 3,
	PANBTN_INVENTORY = 4,
	PANBTN_SPELLBOOK = 5,
	PANBTN_SENDMSG = 6,
	PANBTN_FRIENDLY = 7,
};

enum attribute_id
{
	ATTRIB_STR = 0,
	ATTRIB_MAG = 1,
	ATTRIB_DEX = 2,
	ATTRIB_VIT = 3,
};

#include "Source/Data/xl_obj.h"

enum item_misc_id
{
	IMISC_NONE = 0x0,
	IMISC_USEFIRST = 0x1,
	IMISC_FULLHEAL = 0x2,
	IMISC_HEAL = 0x3,
	IMISC_OLDHEAL = 0x4,
	IMISC_DEADHEAL = 0x5,
	IMISC_MANA = 0x6,
	IMISC_FULLMANA = 0x7,
	IMISC_POTEXP = 0x8, /* add experience */
	IMISC_POTFORG = 0x9, /* remove experience */
	IMISC_ELIXSTR = 0xA,
	IMISC_ELIXMAG = 0xB,
	IMISC_ELIXDEX = 0xC,
	IMISC_ELIXVIT = 0xD,
	IMISC_ELIXWEAK = 0xE, /* double check with alpha */
	IMISC_ELIXDIS = 0xF,
	IMISC_ELIXCLUM = 0x10,
	IMISC_ELIXSICK = 0x11,
	IMISC_REJUV = 0x12,
	IMISC_FULLREJUV = 0x13,
	IMISC_USELAST = 0x14,
	IMISC_SCROLL = 0x15,
	IMISC_SCROLLT = 0x16,
	IMISC_STAFF = 0x17,
	IMISC_BOOK = 0x18,
	IMISC_RING = 0x19,
	IMISC_AMULET = 0x1A,
	IMISC_UNIQUE = 0x1B,
	IMISC_MEAT = 0x1C,
	IMISC_OILFIRST = 0x1D,
	IMISC_OILOF = 0x1E, /* oils are beta or hellfire only */
	IMISC_OILACC = 0x1F,
	IMISC_OILMAST = 0x20,
	IMISC_OILSHARP = 0x21,
	IMISC_OILDEATH = 0x22,
	IMISC_OILSKILL = 0x23,
	IMISC_OILBSMTH = 0x24,
	IMISC_OILFORT = 0x25,
	IMISC_OILPERM = 0x26,
	IMISC_OILHARD = 0x27,
	IMISC_OILIMP = 0x28,
	IMISC_OILLAST = 0x29,
	IMISC_MAPOFDOOM = 0x2A,
	IMISC_EAR = 0x2B,
	IMISC_SPECELIX = 0x2C,
	IMISC_INVALID = 0xFFFFFFFF,
};

enum item_type
{
	ITYPE_MISC = 0x0,
	ITYPE_SWORD = 0x1,
	ITYPE_AXE = 0x2,
	ITYPE_BOW = 0x3,
	ITYPE_MACE = 0x4,
	ITYPE_SHIELD = 0x5,
	ITYPE_LARMOR = 0x6,
	ITYPE_HELM = 0x7,
	ITYPE_MARMOR = 0x8,
	ITYPE_HARMOR = 0x9,
	ITYPE_STAFF = 0xA,
	ITYPE_GOLD = 0xB,
	ITYPE_RING = 0xC,
	ITYPE_AMULET = 0xD,
	ITYPE_MEAT = 0xE, /* used in demo */
	ITYPE_NONE = 0xFFFFFFFF,
};

enum _item_indexes
{
	IDI_GOLD = 0x0,
	IDI_WARRIOR = 0x1,
	IDI_WARRSHLD = 0x2,
	IDI_WARRCLUB = 0x3,
	IDI_ROGUE = 0x4,
	IDI_SORCEROR = 0x5,
	IDI_CLEAVER = 0x6,
	IDI_FIRSTQUEST = 0x6,
	IDI_SKCROWN = 0x7,
	IDI_INFRARING = 0x8,
	IDI_ROCK = 0x9,
	IDI_OPTAMULET = 0xA,
	IDI_TRING = 0xB,
	IDI_BANNER = 0xC,
	IDI_HARCREST = 0xD,
	IDI_STEELVEIL = 0xE,
	IDI_GLDNELIX = 0xF,
	IDI_ANVIL = 0x10,
	IDI_MUSHROOM = 0x11,
	IDI_BRAIN = 0x12,
	IDI_FUNGALTM = 0x13,
	IDI_SPECELIX = 0x14,
	IDI_BLDSTONE = 0x15,
	IDI_LASTQUEST = 0x16,
	IDI_MAPOFDOOM = 0x16,
	IDI_EAR = 0x17,
	IDI_HEAL = 0x18,
	IDI_MANA = 0x19,
	IDI_IDENTIFY = 0x1A,
	IDI_PORTAL = 0x1B,
	IDI_ARMOFVAL = 0x1C,
	IDI_FULLHEAL = 0x1D,
	IDI_FULLMANA = 0x1E,
	IDI_GRISWOLD = 0x1F,
	IDI_LGTFORGE = 0x20,
	IDI_LAZSTAFF = 0x21,
	IDI_RESURRECT = 0x22,
};

enum _setlevels
{
	//SL_BUTCHCHAMB = 0x0,
	SL_SKELKING = 0x1,
	SL_BONECHAMB = 0x2,
	SL_MAZE = 0x3,
	SL_POISONWATER = 0x4,
	SL_VILEBETRAYER = 0x5,
};

#include "Source/Data/xl_quest.h"

enum quest_state
{
	QUEST_NOTAVAIL = 0,
	QUEST_INIT = 1,
	QUEST_ACTIVE = 2,
	QUEST_DONE = 3
};

enum talk_id
{
	STORE_NONE = 0x0,
	STORE_SMITH = 0x1,
	STORE_SBUY = 0x2,
	STORE_SSELL = 0x3,
	STORE_SREPAIR = 0x4,
	STORE_WITCH = 0x5,
	STORE_WBUY = 0x6,
	STORE_WSELL = 0x7,
	STORE_WRECHARGE = 0x8,
	STORE_NOMONEY = 0x9,
	STORE_NOROOM = 0xA,
	STORE_CONFIRM = 0xB,
	STORE_BOY = 0xC,
	STORE_BBOY = 0xD,
	STORE_HEALER = 0xE,
	STORE_STORY = 0xF,
	STORE_HBUY = 0x10,
	STORE_SIDENTIFY = 0x11,
	STORE_SPBUY = 0x12,
	STORE_GOSSIP = 0x13,
	STORE_IDSHOW = 0x14,
	STORE_TAVERN = 0x15,
	STORE_DRUNK = 0x16,
	STORE_BARMAID = 0x17,
};

enum _unique_items
{
	UITEM_CLEAVER = 0x0,
	UITEM_SKCROWN = 0x1,
	UITEM_INFRARING = 0x2,
	UITEM_OPTAMULET = 0x3,
	UITEM_TRING = 0x4,
	UITEM_HARCREST = 0x5,
	UITEM_STEELVEIL = 0x6,
	UITEM_ARMOFVAL = 0x7,
	UITEM_GRISWOLD = 0x8,
	UITEM_LGTFORGE = 0x9,
	UITEM_RIFTBOW = 0xA,
	UITEM_NEEDLER = 0xB,
	UITEM_CELESTBOW = 0xC,
	UITEM_DEADLYHUNT = 0xD,
	UITEM_BOWOFDEAD = 0xE,
	UITEM_BLKOAKBOW = 0xF,
	UITEM_FLAMEDART = 0x10,
	UITEM_FLESHSTING = 0x11,
	UITEM_WINDFORCE = 0x12,
	UITEM_EAGLEHORN = 0x13,
	UITEM_GONNAGALDIRK = 0x14,
	UITEM_DEFENDER = 0x15,
	UITEM_GRYPHONCLAW = 0x16,
	UITEM_BLACKRAZOR = 0x17,
	UITEM_GIBBOUSMOON = 0x18,
	UITEM_ICESHANK = 0x19,
	UITEM_EXECUTIONER = 0x1A,
	UITEM_BONESAW = 0x1B,
	UITEM_SHADHAWK = 0x1C,
	UITEM_WIZSPIKE = 0x1D,
	UITEM_LGTSABRE = 0x1E,
	UITEM_FALCONTALON = 0x1F,
	UITEM_INFERNO = 0x20,
	UITEM_DOOMBRINGER = 0x21,
	UITEM_GRIZZLY = 0x22,
	UITEM_GRANDFATHER = 0x23,
	UITEM_MANGLER = 0x24,
	UITEM_SHARPBEAK = 0x25,
	UITEM_BLOODLSLAYER = 0x26,
	UITEM_CELESTAXE = 0x27,
	UITEM_WICKEDAXE = 0x28,
	UITEM_STONECLEAV = 0x29,
	UITEM_AGUHATCHET = 0x2A,
	UITEM_HELLSLAYER = 0x2B,
	UITEM_MESSERREAVER = 0x2C,
	UITEM_CRACKRUST = 0x2D,
	UITEM_JHOLMHAMM = 0x2E,
	UITEM_CIVERBS = 0x2F,
	UITEM_CELESTSTAR = 0x30,
	UITEM_BARANSTAR = 0x31,
	UITEM_GNARLROOT = 0x32,
	UITEM_CRANBASH = 0x33,
	UITEM_SCHAEFHAMM = 0x34,
	UITEM_DREAMFLANGE = 0x35,
	UITEM_STAFFOFSHAD = 0x36,
	UITEM_IMMOLATOR = 0x37,
	UITEM_STORMSPIRE = 0x38,
	UITEM_GLEAMSONG = 0x39,
	UITEM_THUNDERCALL = 0x3A,
	UITEM_PROTECTOR = 0x3B,
	UITEM_NAJPUZZLE = 0x3C,
	UITEM_MINDCRY = 0x3D,
	UITEM_RODOFONAN = 0x3E,
	UITEM_SPIRITSHELM = 0x3F,
	UITEM_THINKINGCAP = 0x40,
	UITEM_OVERLORDHELM = 0x41,
	UITEM_FOOLSCREST = 0x42,
	UITEM_GOTTERDAM = 0x43,
	UITEM_ROYCIRCLET = 0x44,
	UITEM_TORNFLESH = 0x45,
	UITEM_GLADBANE = 0x46,
	UITEM_RAINCLOAK = 0x47,
	UITEM_LEATHAUT = 0x48,
	UITEM_WISDWRAP = 0x49,
	UITEM_SPARKMAIL = 0x4A,
	UITEM_SCAVCARAP = 0x4B,
	UITEM_NIGHTSCAPE = 0x4C,
	UITEM_NAJPLATE = 0x4D,
	UITEM_DEMONSPIKE = 0x4E,
	UITEM_DEFLECTOR = 0x4F,
	UITEM_SKULLSHLD = 0x50,
	UITEM_DRAGONBRCH = 0x51,
	UITEM_BLKOAKSHLD = 0x52,
	UITEM_HOLYDEF = 0x53,
	UITEM_STORMSHLD = 0x54,
	UITEM_BRAMBLE = 0x55,
	UITEM_REGHA = 0x56,
	UITEM_BLEEDER = 0x57,
	UITEM_CONSTRICT = 0x58,
	UITEM_ENGAGE = 0x59,
	UITEM_INVALID = 0x5A,
};

enum _plr_classes
{
	PC_WARRIOR = 0x0,
	PC_ROGUE = 0x1,
	PC_SORCERER = 0x2,
	NUM_CLASSES = 0x3,
};

enum _ui_classes
{
	UI_WARRIOR = 0x0,
	UI_ROGUE = 0x1,
	UI_SORCERER = 0x2,
	UI_NUM_CLASSES = 0x3,
};

enum _walk_path
{
	WALK_NONE = 0x0,
	WALK_NE = 0x1,
	WALK_NW = 0x2,
	WALK_SE = 0x3,
	WALK_SW = 0x4,
	WALK_N = 0x5,
	WALK_E = 0x6,
	WALK_S = 0x7,
	WALK_W = 0x8,
};

typedef enum {
	ICLASS_NONE = 0,
	ICLASS_WEAPON = 1,
	ICLASS_ARMOR = 2,
	ICLASS_MISC = 3,
	ICLASS_GOLD = 4,
	ICLASS_QUEST = 5,
} item_class;

typedef enum {
	IDROP_NEVER   = 0,
	IDROP_REGULAR = 1,
	IDROP_DOUBLE  = 2,
} item_drop_rate;

typedef enum {
	ISPL_NONE = 0x00000000,
	ISPL_INFRAVISION = 0x00000001,
	ISPL_RNDSTEALLIFE = 0x00000002,
	ISPL_RNDARROWVEL = 0x00000004,
	ISPL_FIRE_ARROWS = 0x00000008,
	ISPL_FIREDAM = 0x00000010,
	ISPL_LIGHTDAM = 0x00000020,
	ISPL_DRAINLIFE = 0x00000040,
	ISPL_UNKNOWN_1 = 0x00000080,
	ISPL_NOHEALPLR = 0x00000100,
	ISPL_MULT_ARROWS = 0x00000200,
	ISPL_UNKNOWN_3 = 0x00000400,
	ISPL_KNOCKBACK = 0x00000800,
	ISPL_NOHEALMON = 0x00001000,
	ISPL_STEALMANA_3 = 0x00002000,
	ISPL_STEALMANA_5 = 0x00004000,
	ISPL_STEALLIFE_3 = 0x00008000,
	ISPL_STEALLIFE_5 = 0x00010000,
	ISPL_QUICKATTACK = 0x00020000,
	ISPL_FASTATTACK = 0x00040000,
	ISPL_FASTERATTACK = 0x00080000,
	ISPL_FASTESTATTACK = 0x00100000,
	ISPL_FASTRECOVER = 0x00200000,
	ISPL_FASTERRECOVER = 0x00400000,
	ISPL_FASTESTRECOVER = 0x00800000,
	ISPL_FASTBLOCK = 0x01000000,
	ISPL_LIGHT_ARROWS = 0x02000000,
	ISPL_THORNS = 0x04000000,
	ISPL_NOMANA = 0x08000000,
	ISPL_ABSHALFTRAP = 0x10000000,
	ISPL_UNKNOWN_4 = 0x20000000,
	ISPL_3XDAMVDEM = 0x40000000,
	ISPL_ALLRESZERO = 0x80000000,
} item_special_effect;

typedef enum _selhero_selections {
	SELHERO_NEW_DUNGEON = 1,
	SELHERO_CONTINUE = 2,
	SELHERO_CONNECT = 3,
	SELHERO_PREVIOUS = 4
} _selhero_selections;

enum automap_flags {
	AFLAG_VERTDOOR = 1,
	AFLAG_HORZDOOR = 2,
	AFLAG_VERTARCH = 4,
	AFLAG_HORZARCH = 8,
	AFLAG_VERTGRATE = 0x10,
	AFLAG_HORZGRATE = 0x20,
	AFLAG_DIRT = 0x40,
	AFLAG_STAIRS = 0x80
};
