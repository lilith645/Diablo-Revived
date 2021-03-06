/**
 * @file revived.h
 *
 * Revived features
 */
#ifndef __REVIVED_H__
#define __REVIVED__

#include <vector>
#include <string>

DEVILUTION_BEGIN_NAMESPACE

#define COLOR_PLAYER_1 (PAL8_BLUE + 1)
#define COLOR_PLAYER_2 (PAL8_ORANGE + 1)
#define COLOR_PLAYER_3 (PAL8_YELLOW + 1)
#define COLOR_PLAYER_4 (PAL8_RED + 1)

#define COLOUR_CUSTOM_BROWN 2
#define COLOUR_CUSTOM_ORANGE_RED 50
#define COLOUR_CUSTOM_GRAY 100

#define COLOUR_CUSTOM_PAL16_GRAY 32
#define COLOUR_CUSTOM_PAL16_RED 48
#define COLOUR_CUSTOM_PAL16_GREEN 64
#define COLOUR_CUSTOM_PAL16_MERKY_GREEN_GRAY 96
#define COLOUR_CUSTOM_PAL16_LIGHT_GRAY 112

#define XPBAR_WIDTH 296
#define XPBAR_HEIGHT 6
#define XPBAR_X SCREEN_WIDTH*0.5-XPBAR_WIDTH*0.5+5
#define XPBAR_Y SCREEN_HEIGHT-10
#define XPBAR_SEGMENTS 10
#define XPBAR_SEGMENT_PERC 1/XPBAR_SEGMENTS
#define XPBAR_SEGMENT_SPACING 2
#define XPBAR_SEGMENT_SIZE XPBAR_WIDTH*XPBAR_SEGMENT_PERC-XPBAR_SEGMENT_SPACING

#define LIFE_FLASK_X PANEL_LEFT+PANEL_WIDTH*0.17
#define LIFE_FLASK_Y SCREEN_HEIGHT-PANEL_HEIGHT-5
#define LIFE_FLASK_WIDTH PANEL_WIDTH*0.1
#define LIFE_FLASK_HEIGHT PANEL_WIDTH*0.1

#define MANA_FLASK_X PANEL_LEFT+PANEL_WIDTH*0.74
#define MANA_FLASK_Y LIFE_FLASK_Y
#define MANA_FLASK_WIDTH SPANEL_WIDTH*0.20
#define MANA_FLASK_HEIGHT SPANEL_WIDTH*0.2

class FloatingText {
  public:
    std::string text;
    int color;
    int iterations;
    int angle;//0-360
    int posX, posY;
    bool showOnCenter;
    int callerID;
    int value;
    std::string description;

    void doStuff(std::string s, int c, int px, int py, bool center, int cc, std::string desc, int v) {
      text = s;
      color = c;
      iterations = 0;
      angle = -60 + (rand() % 121) + 180 * (rand() % 2); //angle = 60 + rand() % 61;
      showOnCenter = center;
      posX = px;
      posY = py;
      callerID = cc;
      description = desc;
      value = v;
    }

    FloatingText(std::string s, int c, int px, int py, bool center, int cc, std::string desc, int v) {
      doStuff(s, c, px, py, center, cc, desc, v);
    }

    FloatingText(std::string s, int c, std::string desc) {
      doStuff(s, c, 0, 0, true, -1, desc, -1);
    }

    void IncreaseIterations() { iterations++; }
};

#ifdef __cplusplus
extern "C" {
#endif

extern char pcursxp;
extern char pcurslife;
extern char pcursmana;
extern bool show_life;
extern bool show_mana;
extern bool drawitems;
extern bool unique_item_bug_fix;
extern bool run_in_town;
extern bool automatically_pickup_gold;
extern bool show_rogue_traps;
extern bool projectiles_break_barrels;
extern bool play_levelup_sound;
extern bool autoheal_when_talk_to_pepin;
extern bool drop_items_on_death;
extern float xp_percentage_per_player;
extern bool friendly_fire_fix;

extern std::vector<FloatingText> floating_text_queue;

extern BYTE sgbIsScrolling;
extern BOOL sgbIsWalking;
extern DWORD sgdwLastWalk;

void parse_revived_config();
int bug_fix_check_unique(int j, int numu, BOOLEAN uok[128], int uok_size);
void track_process_continuous_attacks();
void track_lmb_loc(BYTE bCmd, BYTE x, BYTE y);
void track_lmb_param1(BYTE bCmd, WORD wParam1);
void play_lvlup_sound();
int xp_share(int exp, int totalplrs);
bool shouldnt_drop_items(int pnum);
const char* get_monster_type_text(const MonsterData& monsterData);
void escape_closes_windows();
void pack_player_weapon_switch(PkPlayerStruct *pPack, PlayerStruct* pPlayer);
void unpack_player_weapon_switch(PkPlayerStruct *pPack, PlayerStruct* pPlayer);
void create_weapon_switch(int pnum);
void switch_weapons();
void auto_pickup_gold(int pnum);
bool is_rogue_detect_trap(int trapFlag);
void set_player_max_life_and_mana();
void repair_alternate_weapons(BOOL *repairok);
void recharge_alternate_staff(BOOL *rechargeok);
void shift_click_potion();
void control_click_drop_item();
int belt_has_open_slot();
/*void repair_equipped_items();
int calculate_repair_equipped_items_cost();
bool add_repair_all_equipped_items_option(int x, int y);*/

void enable_mana_life_info();

void highlight_items_on_map();
void draw_trap_if_rogue(int bv, int sx, int sy);
void draw_xp_bar();
void draw_life_info();
void draw_mana_info();
void draw_monster_health_bar(int monsterID);
void check_if_projectile_hit_barrel(int *oi, int mx, int my);
void draw_floating_text_above_player();
void draw_floating_gold(int goldGain, int row, int col);
void draw_weapon_switch_icons();
void store_auto_place_no_belt();

#ifdef __cplusplus
}
#endif

DEVILUTION_END_NAMESPACE

#endif /* __REVIVED_H__ */
