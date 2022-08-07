#include "global.h"
#include "constants/abilities.h"
//#include "constants/heal_locations.h"
#include "constants/hold_effects.h"
#include "constants/items.h"
//#include "constants/layouts.h"
//#include "constants/rogue.h"
#include "data.h"
//
//#include "battle.h"
//#include "battle_setup.h"
//#include "event_data.h"
#include "item.h"
//#include "money.h"
//#include "overworld.h"
#include "pokedex.h"
#include "pokemon.h"
//#include "random.h"
//#include "strings.h"
//#include "string_util.h"
//#include "text.h"

#include "rogue_query.h"
#include "rogue_baked.h"
//#include "rogue_controller.h"

#ifdef ROGUE_EXPANSION
#define QUERY_BUFFER_COUNT 128
#define QUERY_NUM_SPECIES FORMS_START
#else
#define QUERY_BUFFER_COUNT 96
#define QUERY_NUM_SPECIES NUM_SPECIES
#endif

#define MAX_QUERY_BIT_COUNT (max(ITEMS_COUNT, QUERY_NUM_SPECIES))

EWRAM_DATA u16 gRogueQueryBufferSize = 0;
EWRAM_DATA u8 gRogueQueryBits[1 + MAX_QUERY_BIT_COUNT / 8];
EWRAM_DATA u16 gRogueQueryBuffer[QUERY_BUFFER_COUNT];

//extern struct Evolution gEvolutionTable[][EVOS_PER_MON];

static void SetQueryState(u16 elem, bool8 state)
{
    u16 idx = elem / 8;
    u16 bit = elem % 8;

    u8 bitMask = 1 << bit;
    if(state)
    {
        gRogueQueryBits[idx] |= bitMask;
    }
    else
    {
        gRogueQueryBits[idx] &= ~bitMask;
    }
}

static bool8 GetQueryState(u16 elem)
{
    u16 idx = elem / 8;
    u16 bit = elem % 8;

    u8 bitMask = 1 << bit;
    return gRogueQueryBits[idx] & bitMask;
}

void RogueQuery_Clear(void)
{
    gRogueQueryBufferSize = 0;
    memset(&gRogueQueryBits[0], 255, sizeof(bool8) * ARRAY_COUNT(gRogueQueryBits));
}

void RogueQuery_CollapseSpeciesBuffer(void)
{
    u16 species;
    gRogueQueryBufferSize = 0;
    
    for(species = SPECIES_NONE + 1; species < QUERY_NUM_SPECIES && gRogueQueryBufferSize < (QUERY_BUFFER_COUNT - 1); ++species)
    {
        if(GetQueryState(species))
        {
            gRogueQueryBuffer[gRogueQueryBufferSize++] = species;
        }
    }
}

void RogueQuery_CollapseItemBuffer(void)
{
    u16 itemId;
    gRogueQueryBufferSize = 0;
    
    for(itemId = ITEM_NONE + 1; itemId < ITEMS_COUNT && gRogueQueryBufferSize < (QUERY_BUFFER_COUNT - 1); ++itemId)
    {
        if(GetQueryState(itemId))
        {
            gRogueQueryBuffer[gRogueQueryBufferSize++] = itemId;
        }
    }
}

u16* RogueQuery_BufferPtr(void)
{
    return &gRogueQueryBuffer[0];
}

u16 RogueQuery_BufferSize(void)
{
    return gRogueQueryBufferSize;
}

u16 RogueQuery_UncollapsedSpeciesSize(void)
{
    u16 species;
    u16 count = 0;
    
    for(species = SPECIES_NONE + 1; species < QUERY_NUM_SPECIES; ++species)
    {
        if(GetQueryState(species))
        {
            ++count;
        }
    }

    return count;
}

u16 RogueQuery_UncollapsedItemSize(void)
{
    u16 itemId;
    u16 count = 0;
    
    for(itemId = ITEM_NONE + 1; itemId < ITEMS_COUNT; ++itemId)
    {
        if(GetQueryState(itemId))
        {
            ++count;
        }
    }

    return count;
}

u16 RogueQuery_AtUncollapsedIndex(u16 idx)
{
    u16 i;
    u16 counter = 0;
    
    for(i = 1; i < MAX_QUERY_BIT_COUNT; ++i)
    {
        if(GetQueryState(i))
        {
            if(idx == counter++)
                return i;
        }
    }

    return 0;
}

void RogueQuery_Exclude(u16 idx)
{
    SetQueryState(idx, FALSE);
}

// Species
//

static bool8 IsSpeciesType(u16 species, u8 type)
{
    return gBaseStats[species].type1 == type || gBaseStats[species].type2 == type;
}

static bool8 IsFinalEvolution(u16 species)
{
    u16 s, e;
    struct Evolution evo;

    for (e = 0; e < EVOS_PER_MON; e++)
    {
        Rogue_ModifyEvolution(species, e, &evo);

        if (evo.targetSpecies != SPECIES_NONE)
        {
            return FALSE;
        }
    }

    return TRUE;
}

static bool8 IsSpeciesIsLegendary(u16 species)
{
    switch(species)
    {
        case SPECIES_ARTICUNO:
        case SPECIES_ZAPDOS:
        case SPECIES_MOLTRES:
        case SPECIES_MEWTWO:
        case SPECIES_MEW:

        case SPECIES_RAIKOU:
        case SPECIES_ENTEI:
        case SPECIES_SUICUNE:
        case SPECIES_LUGIA:
        case SPECIES_HO_OH:
        case SPECIES_CELEBI:

        case SPECIES_REGIROCK:
        case SPECIES_REGICE:
        case SPECIES_REGISTEEL:
        case SPECIES_KYOGRE:
        case SPECIES_GROUDON:
        case SPECIES_RAYQUAZA:
        case SPECIES_LATIAS:
        case SPECIES_LATIOS:
        case SPECIES_JIRACHI:
        case SPECIES_DEOXYS:
#ifdef ROGUE_EXPANSION

        case SPECIES_UXIE:
        case SPECIES_MESPRIT:
        case SPECIES_AZELF:
        case SPECIES_DIALGA:
        case SPECIES_PALKIA:
        case SPECIES_HEATRAN:
        case SPECIES_REGIGIGAS:
        case SPECIES_GIRATINA:
        case SPECIES_CRESSELIA:
        case SPECIES_PHIONE:
        case SPECIES_MANAPHY:
        case SPECIES_DARKRAI:
        case SPECIES_SHAYMIN:
        case SPECIES_ARCEUS:

        case SPECIES_VICTINI:
        case SPECIES_COBALION:
        case SPECIES_TERRAKION:
        case SPECIES_VIRIZION:
        case SPECIES_TORNADUS:
        case SPECIES_THUNDURUS:
        case SPECIES_RESHIRAM:
        case SPECIES_ZEKROM:
        case SPECIES_LANDORUS:
        case SPECIES_KYUREM:
        case SPECIES_KELDEO:
        case SPECIES_MELOETTA:
        case SPECIES_GENESECT:

        case SPECIES_XERNEAS:
        case SPECIES_YVELTAL:
        case SPECIES_ZYGARDE:
        case SPECIES_DIANCIE:
        case SPECIES_HOOPA:
        case SPECIES_VOLCANION:
        
        case SPECIES_TYPE_NULL:
        case SPECIES_SILVALLY:
        case SPECIES_TAPU_KOKO:
        case SPECIES_TAPU_LELE:
        case SPECIES_TAPU_BULU:
        case SPECIES_TAPU_FINI:
        case SPECIES_COSMOG:
        case SPECIES_COSMOEM:
        case SPECIES_SOLGALEO:
        case SPECIES_LUNALA:
        case SPECIES_NIHILEGO:
        case SPECIES_BUZZWOLE:
        case SPECIES_PHEROMOSA:
        case SPECIES_XURKITREE:
        case SPECIES_CELESTEELA:
        case SPECIES_KARTANA:
        case SPECIES_GUZZLORD:
        case SPECIES_NECROZMA:
        case SPECIES_MAGEARNA:
        case SPECIES_MARSHADOW:
        case SPECIES_POIPOLE:
        case SPECIES_NAGANADEL:
        case SPECIES_STAKATAKA:
        case SPECIES_BLACEPHALON:
        case SPECIES_ZERAORA:
        case SPECIES_MELTAN:
        case SPECIES_MELMETAL:

        case SPECIES_ZACIAN:
        case SPECIES_ZAMAZENTA:
        case SPECIES_ETERNATUS:
        case SPECIES_KUBFU:
        case SPECIES_URSHIFU:
        case SPECIES_ZARUDE:
        case SPECIES_REGIELEKI:
        case SPECIES_REGIDRAGO:
        case SPECIES_GLASTRIER:
        case SPECIES_SPECTRIER:
        case SPECIES_CALYREX:
#endif
            return TRUE;
    };

    return FALSE;
}

void RogueQuery_SpeciesIsValid(void)
{
    // Handle for ?? species mainly
    // Just going to base this off ability 1 being none as that seems safest whilst allowing new mons
    u16 species;

    for(species = SPECIES_NONE + 1; species < QUERY_NUM_SPECIES; ++species)
    {
        if(GetQueryState(species))
        {
            if(gBaseStats[species].abilities[0] == ABILITY_NONE)
            {
                SetQueryState(species, FALSE);
            }
        }
    }
}

void RogueQuery_SpeciesInPokedex(void)
{
    u16 species;

    for(species = SPECIES_NONE + 1; species < QUERY_NUM_SPECIES; ++species)
    {
        if(GetQueryState(species))
        {
            if (!GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_CAUGHT))
            {
                SetQueryState(species, FALSE);
            }
        }
    }
}

void RogueQuery_SpeciesOfType(u8 type)
{
    u16 species;

    for(species = SPECIES_NONE + 1; species < QUERY_NUM_SPECIES; ++species)
    {
        if(GetQueryState(species))
        {
            if(!IsSpeciesType(species, type))
            {
                SetQueryState(species, FALSE);
            }
        }
    }
}

void RogueQuery_SpeciesOfTypes(const u8* types, u8 count)
{
    u8 t;
    bool8 isValid;
    u16 species;

    for(species = SPECIES_NONE + 1; species < QUERY_NUM_SPECIES; ++species)
    {
        if(GetQueryState(species))
        {
            isValid = FALSE;
            for(t = 0; t < count; ++t)
            {
                if(types[t] == TYPE_NONE)
                    continue;

                if(IsSpeciesType(species, types[t]))
                {
                    isValid = TRUE;
                    break;
                }
            }

            if(!isValid)
            {
                SetQueryState(species, FALSE);
            }
        }
    }
}

void RogueQuery_SpeciesIsFinalEvolution(void)
{
    u16 species;

    for(species = SPECIES_NONE + 1; species < QUERY_NUM_SPECIES; ++species)
    {
        if(GetQueryState(species))
        {
            if(!IsFinalEvolution(species))
            {
                SetQueryState(species, FALSE);
            }
        }
    }
}

void RogueQuery_TransformToEggSpecies(void)
{
    u16 species;
    u16 eggSpecies;

    for(species = SPECIES_NONE + 1; species < QUERY_NUM_SPECIES; ++species)
    {
        if(GetQueryState(species))
        {
            eggSpecies = Rogue_GetEggSpecies(species);
            if(eggSpecies != species)
            {
                SetQueryState(eggSpecies, TRUE);
                SetQueryState(species, FALSE);
            }
        }
    }
}

void RogueQuery_SpeciesWithAtLeastEvolutionStages(u8 count)
{
    u8 evo;
    u16 species;
    bool8 removeChild = TRUE;

    for(species = SPECIES_NONE + 1; species < QUERY_NUM_SPECIES; ++species)
    {
        if(GetQueryState(species))
        {
            if(Rogue_GetEvolutionCount(species) < count)
            {
                SetQueryState(species, FALSE);
            }
        }
    }
}

void RogueQuery_EvolveSpeciesToLevel(u8 level)
{
    u8 e;
    u16 species;
    bool8 removeChild = TRUE;
    struct Evolution evo;

    for(species = SPECIES_NONE + 1; species < QUERY_NUM_SPECIES; ++species)
    {
        if(GetQueryState(species))
        {
            for(e = 0; e < EVOS_PER_MON; ++e)
            {
                Rogue_ModifyEvolution(species, e, &evo);

                switch(evo.method)
                {
                case EVO_LEVEL:
                case EVO_LEVEL_ATK_GT_DEF:
                case EVO_LEVEL_ATK_EQ_DEF:
                case EVO_LEVEL_ATK_LT_DEF:
                case EVO_LEVEL_SILCOON:
                case EVO_LEVEL_CASCOON:
                case EVO_LEVEL_NINJASK:
                case EVO_LEVEL_SHEDINJA:
#ifdef ROGUE_EXPANSION
                case EVO_LEVEL_FEMALE:
                case EVO_LEVEL_MALE:
                case EVO_LEVEL_DAY:
                case EVO_LEVEL_DUSK:
                case EVO_LEVEL_NATURE_AMPED:
                case EVO_LEVEL_NATURE_LOW_KEY:
                case EVO_CRITICAL_HITS:
#endif
                if (evo.param <= level)
                {
                    SetQueryState(evo.targetSpecies, TRUE);
                    if(removeChild)
                    {
                        SetQueryState(species, FALSE);
                    }
                }
                break;
                };
            }
        }
    }
}

void RogueQuery_EvolveSpeciesByItem()
{
    u8 e;
    u16 species;
    bool8 removeChild = TRUE;
    struct Evolution evo;

    for(species = SPECIES_NONE + 1; species < QUERY_NUM_SPECIES; ++species)
    {
        if(GetQueryState(species))
        {
            for(e = 0; e < EVOS_PER_MON; ++e)
            {
                Rogue_ModifyEvolution(species, e, &evo);

                switch(evo.method)
                {
                case EVO_ITEM:
                case EVO_LEVEL_ITEM:
#ifdef ROGUE_EXPANSION
                case EVO_ITEM_HOLD_DAY:
                case EVO_ITEM_HOLD_NIGHT:
                case EVO_MOVE:
                case EVO_MOVE_TYPE:
                case EVO_MAPSEC:
                case EVO_ITEM_MALE:
                case EVO_ITEM_FEMALE:
                case EVO_LEVEL_RAIN:
                case EVO_SPECIFIC_MON_IN_PARTY:
                case EVO_LEVEL_DARK_TYPE_MON_IN_PARTY:
                case EVO_SPECIFIC_MAP:
                case EVO_SCRIPT_TRIGGER_DMG:
                case EVO_DARK_SCROLL:
                case EVO_WATER_SCROLL:
#endif
                {
                    SetQueryState(evo.targetSpecies, TRUE);
                    if(removeChild)
                    {
                        SetQueryState(species, FALSE);
                    }
                }
                break;
                };
            }
        }
    }
}

void RogueQuery_SpeciesIsLegendary(void)
{
    u16 species;

    for(species = SPECIES_NONE + 1; species < QUERY_NUM_SPECIES; ++species)
    {
        if(GetQueryState(species))
        {
            if(!IsSpeciesIsLegendary(species))
            {
                SetQueryState(species, FALSE);
            }
        }
    }
}

void RogueQuery_SpeciesIsNotLegendary(void)
{
    u16 species;

    for(species = SPECIES_NONE + 1; species < QUERY_NUM_SPECIES; ++species)
    {
        if(GetQueryState(species))
        {
            if(IsSpeciesIsLegendary(species))
            {
                SetQueryState(species, FALSE);
            }
        }
    }
}

// Items
//

void RogueQuery_ItemsIsValid(void)
{
    u16 itemId;
    struct Item item;

    for(itemId = ITEM_NONE + 1; itemId < ITEMS_COUNT; ++itemId)
    {
        if(GetQueryState(itemId))
        {
            Rogue_ModifyItem(itemId, &item);

            if(item.itemId != itemId)
            {
                SetQueryState(itemId, FALSE);
            }
        }
    }
}

void RogueQuery_ItemsInPocket(u8 pocket)
{
    u16 itemId;
    struct Item item;

    for(itemId = ITEM_NONE + 1; itemId < ITEMS_COUNT; ++itemId)
    {
        if(GetQueryState(itemId))
        {
            Rogue_ModifyItem(itemId, &item);

            if(item.pocket != pocket)
            {
                SetQueryState(itemId, FALSE);
            }
        }
    }
}

void RogueQuery_ItemsNotInPocket(u8 pocket)
{
    u16 itemId;
    struct Item item;

    for(itemId = ITEM_NONE + 1; itemId < ITEMS_COUNT; ++itemId)
    {
        if(GetQueryState(itemId))
        {
            Rogue_ModifyItem(itemId, &item);

            if(item.pocket == pocket)
            {
                SetQueryState(itemId, FALSE);
            }
        }
    }
}

void RogueQuery_ItemsInPriceRange(u16 minPrice, u16 maxPrice)
{
    u16 itemId;
    struct Item item;

    for(itemId = ITEM_NONE + 1; itemId < ITEMS_COUNT; ++itemId)
    {
        if(GetQueryState(itemId))
        {
            Rogue_ModifyItem(itemId, &item);

            if(item.price < minPrice || item.price > maxPrice)
            {
                SetQueryState(itemId, FALSE);
            }
        }
    }
}

void RogueQuery_ItemsHeldItem(void)
{
    u16 itemId;
    struct Item item;

    for(itemId = ITEM_NONE + 1; itemId < ITEMS_COUNT; ++itemId)
    {
        if(GetQueryState(itemId))
        {
            Rogue_ModifyItem(itemId, &item);

            if(item.holdEffect == HOLD_EFFECT_NONE)
            {
                SetQueryState(itemId, FALSE);
            }
        }
    }
}

void RogueQuery_ItemsNotHeldItem(void)
{
    u16 itemId;
    struct Item item;

    for(itemId = ITEM_NONE + 1; itemId < ITEMS_COUNT; ++itemId)
    {
        if(GetQueryState(itemId))
        {
            Rogue_ModifyItem(itemId, &item);

            if(item.holdEffect != HOLD_EFFECT_NONE)
            {
                SetQueryState(itemId, FALSE);
            }
        }
    }
}

void RogueQuery_ItemsExcludeRange(u16 fromId, u16 toId)
{
    u16 itemId;

    for(itemId = ITEM_NONE + 1; itemId < ITEMS_COUNT; ++itemId)
    {
        if(GetQueryState(itemId))
        {
            if(itemId >= fromId && itemId <= toId)
            {
                SetQueryState(itemId, FALSE);
            }
        }
    }
}
