#include <stdint.h>

#define SRAM_START 0x20000000U                /* Inicio da SRAM CORTEX-M */
#define SRAM_SIZE (128U * 1024U)              /* Tam. SRAM STM32F411 128K (STM32F411)*/
#define SRAM_END ((SRAM_START) + (SRAM_SIZE)) /* Final da SRAM STM32F411 */
#define STACK_START SRAM_END                  /* Inicio da Stack */

void reset_handler(void);

uint32_t vectors[] __attribute__((section(".isr_vectors"))) = {
    // Definimos que este vetor deverá ser armazenado em uma nova seção chamada .isr_vectors
    STACK_START,             /* 0x0000 0000 */
    (uint32_t)reset_handler, /* 0x0000 0004 */
    0,                       /* 0x0000 0008 */
    0,                       /* 0x0000 000c */
    0,                       /* 0x0000 0010 */
    0,                       /* 0x0000 0014 */
    0,                       /* 0x0000 0018 */
    0,                       /* 0x0000 001c */
    0,                       /* 0x0000 0020 */
    0,                       /* 0x0000 0024 */
    0,                       /* 0x0000 0028 */
    0,                       /* 0x0000 002c */
    0,                       /* 0x0000 0030 */
    0,                       /* 0x0000 0034 */
    0,                       /* 0x0000 0038 */
    0,                       /* 0x0000 003c */
};

void reset_handler(void)
{
}