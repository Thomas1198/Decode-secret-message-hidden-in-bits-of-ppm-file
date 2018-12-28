/**
* @date 14.3.2018
* @file bit-array.h
* @author Tomas Dorda (xdorda00)
* @brief Used for work with bits
* GCC 6.4.0
*/

#include <limits.h>
#include "error.h"

//  Typ bitoveho pole (pro predavani parametru do funkce odkazem)
typedef unsigned long bit_array_t[];

/*
 * @brief Ziska velikost bitoveho pole
 * @param	jmeno_pole	Jmeno bitoveho pole typu BiArray_t
 */
#ifdef USE_INLINE
static inline unsigned long bit_array_size(bit_array_t jmeno_pole)
  {
		return jmeno_pole[0];
	}
#else
#define bit_array_size(jmeno_pole) jmeno_pole[0]

#define BIT_SHIFT(name, index) (((CHAR_BIT * sizeof(name[0]))-(index % (CHAR_BIT * sizeof(name[0]))))-1)

#endif

/*
 * @brief Nastavi zadany bit v poli na pozadovanou hodnotu
 * @param	jmeno_pole	Jmeno bitoveho pole
 * @param	index	index bitu
 * @param	vyraz	nastavit na tuto hodnotu 0 nastavi na 0, jakekoli nenulove cislo nastavi na 1
 */
#ifdef USE_INLINE
static inline void bit_array_setbit(bit_array_t jmeno_pole, long index, int vyraz)
  {
		if(index > bit_array_size(jmeno_pole)-1 || index < 0)
			{
				error_exit("Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bit_array_size(jmeno_pole)-1);
			}
		if (vyraz) {
			jmeno_pole[index/(sizeof(jmeno_pole[0])*CHAR_BIT)+1] = jmeno_pole[index/(sizeof(jmeno_pole[0])*CHAR_BIT)+1] | (unsigned long)1<<index%(sizeof(jmeno_pole[0])*CHAR_BIT);
		}
		else
		{
			jmeno_pole[index/(sizeof(jmeno_pole[0])*CHAR_BIT)+1] = jmeno_pole[index/(sizeof(jmeno_pole[0])*CHAR_BIT)+1] &(~((unsigned long)1<<index%(sizeof(jmeno_pole[0])*CHAR_BIT)));
		}
  }
#else
#define bit_array_setbit_continue(name, index, expression) (expression) != 0 ? (name[(index) / (CHAR_BIT * sizeof(name[0]))] |= (1UL << (BIT_SHIFT(name, (index)))))\
                                                                : (name[(index) / (CHAR_BIT * sizeof(name[0]))] &= ~(1UL << (BIT_SHIFT(name, (index)))))

#define bit_array_setbit(name, index, expression) ( (index) >= bit_array_size(name) ? error_exit("Index %ld out of range 0..%ld", (index), bit_array_size(name)-1), 0 /* , 0 Ternary operator trick to force evaluating */ \
                                                         : bit_array_setbit_continue(name, index+(CHAR_BIT * sizeof(unsigned long)), expression) )

#endif


/*
 * @brief Ziska hodnotu zadaneho bitu, vraci 1 nebo 0
 * @param	jmeno_pole	Jmeno bitoveho pole
 * @param	index	Index bitu
 */
#ifdef USE_INLINE
static inline int bit_array_getbit(bit_array_t jmeno_pole, long index)
	{
		if(index > bit_array_size(jmeno_pole)-1 || index < 0)
			{
				error_exit("Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bit_array_size(jmeno_pole)-1);
				return 0;
			}
		return ( jmeno_pole[index/(sizeof(jmeno_pole[0])*CHAR_BIT)+1] & ((unsigned long)1 << (index%(sizeof(jmeno_pole[0])*CHAR_BIT)) ) ) > 0;
	}
#else
#define get_bit_continue(name, index) ((((name)[(index) / (CHAR_BIT * sizeof(name[0]))]) & (1UL << (BIT_SHIFT(name, (index))))) >> (BIT_SHIFT(name, (index))))

#define bit_array_getbit(name, index) ( (index) >= bit_array_size(name) ? error_exit("Index %ld out of range 0..%ld", (index), bit_array_size(name)-1), 0 \
                                                         : get_bit_continue(name, index+(CHAR_BIT * sizeof(unsigned long))) )

#endif



/*
 * @brief Inicializuje a nuluje bitove pole
 * @param	jmeno_pole	jmeno pole
 * @param	velikost	pozadovana velikost
 */
#define get_aray_size(size) ((size) % (CHAR_BIT * sizeof(unsigned long)) == 0 ? (size)/(CHAR_BIT * sizeof(unsigned long)) : ((size)/(CHAR_BIT * sizeof(unsigned long)))+1)
#define bit_array_create(name, size) unsigned long name[get_aray_size(size)+1] = {(size), 0}